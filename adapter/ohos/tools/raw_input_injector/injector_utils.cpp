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

#include "injector_utils.h"

#include <cmath>
#include <ctime>
#include <iostream>
#include <map>

namespace OHOS {
namespace Ace {
namespace {
constexpr int32_t TIME_TRANSITION = 1000;
} // namespace

bool InjectorUtils::debugEnabled_ = false;

int64_t InjectorUtils::GetSysClockTime()
{
    struct timespec ts = { 0, 0 };
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) {
        return 0;
    }
    return (ts.tv_sec * TIME_TRANSITION * TIME_TRANSITION) + (ts.tv_nsec / TIME_TRANSITION);
}

int32_t InjectorUtils::CalculateNextPosValueWithLinear(
    int32_t startPoint, int32_t targetPoint, int32_t currentIndex, int32_t totalCount)
{
    if (totalCount < 1) {
        std::cout << "too few total count" << std::endl;
        return -1;
    }

    if (targetPoint == startPoint) {
        // no moving
        return targetPoint;
    }

    auto distance = targetPoint - startPoint;
    auto possitive = (distance > 0) ? 1 : -1; // possitive means increasing
    // distance step
    float absStep = static_cast<float>(std::abs(distance)) / totalCount;
    // one px at least
    absStep = (absStep == 0) ? 1 : absStep;
    int32_t result = startPoint + static_cast<float>((absStep * (currentIndex + 1)) * possitive);
    if (possitive > 0) {
        result = (result > targetPoint) ? targetPoint : result;
    } else {
        result = (result < targetPoint) ? targetPoint : result;
    }
    return result;
}

int InjectorUtils::Combination(int n, int k)
{
    double result = 1.0;
    for (int i = 1; i <= k; ++i) {
        result *= static_cast<double>(n - i + 1) / i;
    }
    return result;
}

Point InjectorUtils::BezierCurve(const std::vector<Point>& controlPoints, double t)
{
    Point result = { 0.0, 0.0 };
    size_t count = controlPoints.size();
    if (count <= 1) {
        std::cout << "too few control points" << std::endl;
        return result;
    }

    size_t n = count - 1;

    for (size_t i = 0; i <= n; ++i) {
        double coeff = static_cast<double>(Combination(n, i)) * pow(t, i) * pow(1 - t, n - i);
        result.x += coeff * controlPoints[i].x;
        result.y += coeff * controlPoints[i].y;
    }

    return result;
}

// cubic: x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2
static double EaseInOutCubic(double t)
{
    const double c1 = 0.5;
    const int c2 = 4;
    const int c3 = -2;
    const int c4 = 2;
    const int c5 = 3;
    const int c6 = 2;
    return (t < c1) ? (c2 * t * t * t) : (1 - pow(c3 * t + c4, c5) / c6);
}

// quart: x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2
static double EaseInOutQuart(double t)
{
    const double c1 = 0.5;
    const int c2 = 8;
    const int c3 = -2;
    const int c4 = 2;
    const int c5 = 4;
    const int c6 = 2;
    return (t < c1) ? (c2 * t * t * t * t) : (1 - pow(c3 * t + c4, c5) / c6);
}

double InjectorUtils::EaseInOut(double t, EaseAlgorithm algorithm)
{
    static const std::map<EaseAlgorithm, double (*)(double)> easeAlgorithmMap = {
        { EaseAlgorithm::CUBIC, EaseInOutCubic }, { EaseAlgorithm::QUART, EaseInOutQuart }
    };
    return easeAlgorithmMap.at(algorithm)(t);
}

Point InjectorUtils::CalculateNextPosValueWithBezier(
    std::vector<Point>& controlPoints, int32_t currentIndex, int32_t totalCount, CoordinateCurve curve)
{
    Point result;
    if (currentIndex < 0 || currentIndex > totalCount || totalCount < 1) {
        std::cout << "wrong count given: currentIndex " << currentIndex << ", totalCount " << totalCount << std::endl;
        return result;
    }

    if (controlPoints.empty()) {
        std::cout << "start and target point need be given at least" << std::endl;
        return result;
    }

    double t = static_cast<double>(currentIndex) / totalCount;
    if (curve == CoordinateCurve::EASE_IN_OUT) {
        t = EaseInOut(t, EaseAlgorithm::QUART);
    }
    return BezierCurve(controlPoints, t);
}
} // namespace Ace
} // namespace OHOS
