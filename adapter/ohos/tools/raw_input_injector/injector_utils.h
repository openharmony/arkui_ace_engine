/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ARKUI_INPUT_RAW_INPUT_INJECTOR_RAW_INPUT_INJECTOR_UTILS_H
#define ARKUI_INPUT_RAW_INPUT_INJECTOR_RAW_INPUT_INJECTOR_UTILS_H

#include <cstdint>
#include <vector>

namespace OHOS {
namespace Ace {

// coordinate calculation function curve, used for point calculation of touch move
// [Note]: only LINEAR is supported for now
enum class CoordinateCurve : size_t { LINEAR = 0, EASE_IN_OUT, EASE_IN, EASE_OUT };

enum class EaseAlgorithm : size_t { CUBIC = 0, QUART };

struct Point {
    double x = 0; // use double for high precision
    double y = 0;
};

class InjectorUtils final {
public:
    static bool IsDebugOn()
    {
        return debugEnabled_;
    }

    static void SetDebugEnabled(bool debug)
    {
        debugEnabled_ = debug;
    }

    static int64_t GetSysClockTime();

    // calculate one point value in linear way
    static int32_t CalculateNextPosValueWithLinear(
        int32_t startPoint, int32_t targetPoint, int32_t currentIndex, int32_t totalCount);
    static Point CalculateNextPosValueWithBezier(
        std::vector<Point>& controlPoints, int32_t currentIndex, int32_t totalCount, CoordinateCurve curve);

private:
    InjectorUtils() = default;
    ~InjectorUtils() = default;
    // bezier curve calculation
    static Point BezierCurve(const std::vector<Point>& controlPoints, double t);
    static int Combination(int n, int k);
    static double EaseInOut(double t, EaseAlgorithm algorithm);
    static bool debugEnabled_;
};
} // namespace Ace
} // namespace OHOS
#endif // ARKUI_INPUT_RAW_INPUT_INJECTOR_RAW_INPUT_INJECTOR_H