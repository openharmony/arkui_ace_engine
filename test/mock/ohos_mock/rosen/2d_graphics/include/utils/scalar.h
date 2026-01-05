/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef SCALAR_H
#define SCALAR_H

#include <cmath>
#include <limits>

namespace OHOS {
namespace Rosen {
namespace Drawing {
typedef float scalar;
static const scalar SCALAR_ONE = 1.0f;
static const scalar BLUR_SIGMA_SCALE = 0.57735f;
static const scalar FLOAT_PI = 3.14159265f;

inline bool IsScalarAlmostEqual(scalar a, scalar b)
{
    return fabs(a - b) < std::numeric_limits<scalar>::min();
}

inline scalar ConvertRadiusToSigma(scalar radius)
{
    return radius > 0 ? BLUR_SIGMA_SCALE * radius + 0.5f : 0.0f;
}

inline scalar ConvertSigmaToRadius(scalar sigma)
{
    return sigma > 0.5f ? (sigma - 0.5f) / BLUR_SIGMA_SCALE : 0.0f;
}

/**
 * @param radians Radians values.
 * @return Return degrees values.
 */
inline scalar ConvertRadiansToDegrees(scalar radians)
{
    return radians * (180 / FLOAT_PI);
}
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
