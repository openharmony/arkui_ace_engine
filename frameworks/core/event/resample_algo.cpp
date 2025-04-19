/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "core/event/resample_algo.h"

#include <algorithm>
#include <chrono>
#include <cinttypes>

#include "core/event/touch_event.h"

namespace OHOS::Ace {
AvgPoint ResampleAlgo::GetAvgPoint(const std::vector<PointerEvent>&& events,
    bool isScreen)
{
    float avgX = 0.0f;
    float avgY = 0.0f;
    uint64_t avgTime = 0;
    int32_t i = 0;
    uint64_t lastTime = 0;
    for (auto iter = events.begin(); iter != events.end(); iter++) {
        if (lastTime == 0 || static_cast<uint64_t>(iter->time.time_since_epoch().count()) != lastTime) {
            if (!isScreen) {
                avgX += iter->x;
                avgY += iter->y;
            } else {
                avgX += iter->screenX;
                avgY += iter->screenY;
            }
            avgTime += static_cast<uint64_t>(iter->time.time_since_epoch().count());
            i++;
            lastTime = static_cast<uint64_t>(iter->time.time_since_epoch().count());
        }
    }
    if (i > 0) {
        avgX /= i;
        avgY /= i;
        avgTime /= static_cast<uint64_t>(i);
    }
    return {
        avgX,
        avgY,
        avgTime,
        0.0f,
        0.0f
    };
}

ResamplePoint ResampleAlgo::LinearInterpolation(const AvgPoint& history, const AvgPoint& current,
    uint64_t nanoTimeStamp)
{
    if ((nanoTimeStamp == history.time || nanoTimeStamp == current.time) ||
        (current.time <= history.time) ||
        (current.time - history.time > INTERPOLATION_THRESHOLD) ||
        (nanoTimeStamp < history.time)) {
        return {};
    }
    auto inputXDeltaSlope = (current.x - history.x) * ONE_S_IN_NS /
                        (float)(current.time - history.time);
    auto inputYDeltaSlope = (current.y - history.y) * ONE_S_IN_NS /
                        (float)(current.time - history.time);
    if (nanoTimeStamp < current.time) {
        float alpha = (float)(nanoTimeStamp - history.time) /
                (float)(current.time - history.time);
        float x = history.x + alpha * (current.x - history.x);
        float y = history.y + alpha * (current.y - history.y);
        return {
            x,
            y,
            inputXDeltaSlope,
            inputYDeltaSlope
        };
    } else if (nanoTimeStamp > current.time) {
        float alpha = (float)(nanoTimeStamp - current.time) /
                (float)(current.time - history.time);
        float x = current.x + alpha * (current.x - history.x);
        float y = current.y + alpha * (current.y - history.y);
        return {
            x,
            y,
            inputXDeltaSlope,
            inputYDeltaSlope
        };
    }
    return {};
}

ResamplePoint ResampleAlgo::GetResampleCoord(const std::vector<PointerEvent>&& history,
    const std::vector<PointerEvent>&& current, uint64_t nanoTimeStamp,
    bool isScreen)
{
    if (history.empty() || current.empty()) {
        return {};
    }
    uint64_t lastNanoTime = 0;
    float x = 0.0f;
    float y = 0.0f;
    for (const auto& item : current) {
        uint64_t currentNanoTime = static_cast<uint64_t>(item.time.time_since_epoch().count());
        if (lastNanoTime < currentNanoTime) {
            lastNanoTime = currentNanoTime;
            x = item.x;
            y = item.y;
        }
    }
    if (nanoTimeStamp > RESAMPLE_COORD_TIME_THRESHOLD + lastNanoTime) {
        return {
            x,
            y,
            0.0f,
            0.0f
        };
    }
    auto historyPoint = GetAvgPoint(std::move(history), isScreen);
    auto currentPoint = GetAvgPoint(std::move(current), isScreen);
    return LinearInterpolation(historyPoint, currentPoint, nanoTimeStamp);
}

inline float Lerp(float a, float b, float alpha)
{
    return a + alpha * (b - a);
}

template<typename T>
typename std::vector<T>::iterator FindSampleRightBefore(std::vector<T>& events, uint64_t resampleTime)
{
    std::chrono::nanoseconds nanoseconds(resampleTime);
    TimeStamp ts(nanoseconds);
    auto iter = events.rbegin(); // events must not be empty
    do {
        if (iter->time < ts) {
            return --iter.base();
        }
    } while (++iter != events.rend());
    return events.end();
}

bool IsRebound(TouchEvent& prev, TouchEvent& mid, TouchEvent& next)
{
    float deltaXA = mid.x - prev.x;
    float deltaXB = next.x - mid.x;
    float deltaYA = mid.y - prev.y;
    float deltaYB = next.y - mid.y;
    // dot product of the recent 2 deltas
    // if negtive, it is definitely a rebound
    // if it is a very small positive,
    float dotProduct = deltaXA * deltaXB + deltaYA * deltaYB;
    return (dotProduct < 0.5f);
}

template<class T>
bool ResampleAlgo::GetResamplePointerEvent(std::vector<T>& events,
    uint64_t resampleTime, PointerEvent& resample, ResamplePoint& slope)
{
    constexpr int64_t MAX_EXTERNAL_INTERPOLATE_TIME = 8 * 1000 * 1000; // 8ms
    constexpr int64_t MIN_DELTA_TIME = 2 * 1000 * 1000; // 2ms
    constexpr int64_t MAX_DELTA_TIME = 20 * 1000 * 1000; // 20ms

    if (events.size() < 2) { // resample need at least 2 points.
        return false;
    }
    auto iter = FindSampleRightBefore(events, resampleTime);
    if (iter == events.end()) { // no event before resample
        return false;
    }
    auto nextIter = std::next(iter);
    int64_t delta = 0;
    uint64_t iterTime = iter->time.time_since_epoch().count();
    if (nextIter == events.end()) {
        // external interpolation
        nextIter = std::prev(iter);
        if (nextIter != events.begin()) {
            auto prepre = std::prev(nextIter);
            if (IsRebound(*prepre, *nextIter, *iter)) {
                return false;
            }
        }
        uint64_t nextTime = nextIter->time.time_since_epoch().count();
        delta = iterTime - nextTime;
        if (delta > MAX_DELTA_TIME || delta < MIN_DELTA_TIME) {
            return false;
        }
        uint64_t maxPredict = std::min(delta / 2, MAX_EXTERNAL_INTERPOLATE_TIME) + iterTime;
        resampleTime = std::min(resampleTime, maxPredict);
        delta = -delta;
    } else if (nextIter->time.time_since_epoch().count() == static_cast<int64_t>(resampleTime)) {
        return false;
    } else {
        // internal interpolation
        delta = std::chrono::duration_cast<std::chrono::nanoseconds>(nextIter->time - iter->time).count();
        if (delta < MIN_DELTA_TIME) {
            return false;
        }
    }
    float alpha = (static_cast<float>(resampleTime) - iterTime) / delta;
    resample.x = Lerp(iter->x, nextIter->x, alpha);
    resample.y = Lerp(iter->y, nextIter->y, alpha);
    resample.screenX = Lerp(iter->screenX, nextIter->screenX, alpha);
    resample.screenY = Lerp(iter->screenY, nextIter->screenY, alpha);
    std::chrono::nanoseconds nanoseconds(resampleTime);
    resample.time = TimeStamp(nanoseconds);
    slope.inputXDeltaSlope = (nextIter->x - iter->x) / delta;
    slope.inputYDeltaSlope = (nextIter->y - iter->y) / delta;
    return true;
}

template bool ResampleAlgo::GetResamplePointerEvent<TouchEvent>(
    std::vector<TouchEvent>&, uint64_t, PointerEvent&, ResamplePoint&);
} // namespace OHOS::Ace