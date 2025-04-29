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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_RESAMPLE_ALGO_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_EVENT_RESAMPLE_ALGO_H
#include <vector>
#include "core/event/axis_event.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t RESAMPLE_COORD_TIME_THRESHOLD = 20 * 1000 * 1000;
constexpr uint64_t INTERPOLATION_THRESHOLD = 100 * 1000 * 1000; // 100ms
constexpr uint64_t ONE_S_IN_NS = 1 * 1000 * 1000 * 1000;
}

struct AvgPoint {
    float x = {};
    float y = {};
    uint64_t time = {};
    float windowX = {};
    float windowY = {};

    AvgPoint& operator+=(const AvgPoint &other)
    {
        x += other.x;
        y += other.y;
        windowX += other.windowX;
        windowY += other.windowY;
        time += other.time;
        return *this;
    }

    AvgPoint& operator/=(float divisor)
    {
        if (NearEqual(divisor, 0.0f)) {
            return *this;
        }
        x /= divisor;
        y /= divisor;
        windowX /= divisor;
        windowY /= divisor;
        time /= static_cast<uint64_t>(divisor);
        return *this;
    }
};

struct ResamplePoint {
    float x{};
    float y{};
    float inputXDeltaSlope{};
    float inputYDeltaSlope{};
};

class ResampleAlgo final {
public:
    ResampleAlgo() = delete;
    
    ~ResampleAlgo() = delete;

    static AvgPoint GetAvgPoint(const std::vector<PointerEvent>&& events,
        bool isScreen);

    static ResamplePoint LinearInterpolation(const AvgPoint& history, const AvgPoint& current,
        uint64_t nanoTimeStamp);

    static ResamplePoint GetResampleCoord(const std::vector<PointerEvent>&& history,
        const std::vector<PointerEvent>&& current, uint64_t nanoTimeStamp,
        bool isScreen);

    template<class T>
    static bool GetResamplePointerEvent(std::vector<T>& events,
        uint64_t resampleTime, PointerEvent& resample, ResamplePoint& slope);
};
} // namespace OHOS::Ace
#endif