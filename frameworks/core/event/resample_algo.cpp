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
} // namespace OHOS::Ace