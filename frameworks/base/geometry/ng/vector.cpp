/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "base/geometry/ng/vector.h"

#include <cstdint>

#include "base/utils/utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t X_INDEX = 0;
constexpr int32_t Y_INDEX = 1;
constexpr int32_t Z_INDEX = 2;

}

bool VectorF::operator==(const VectorF& other) const
{
    return NearEqual(x, other.x, 1e-5) && NearEqual(y, other.y, 1e-5);
}

VectorF VectorF::operator*(float value) const
{
    return VectorF(x * value, y * value);
}

bool Vector3F::operator==(const Vector3F& other) const
{
    return NearEqual(x, other.x) && NearEqual(y, other.y) && NearEqual(z, other.z);
}

float Vector3F::operator[](int32_t index) const
{
    switch (index) {
        case X_INDEX:
            return x;
        case Y_INDEX:
            return y;
        case Z_INDEX:
            return z;
        default:
            return 0.0f;
    }
}

bool Vector4F::operator==(const Vector4F& other) const
{
    return NearEqual(x, other.x) && NearEqual(y, other.y) && NearEqual(z, other.z) && NearEqual(w, other.w);
}

bool Vector5F::operator==(const Vector5F& other) const
{
    return NearEqual(x, other.x) && NearEqual(y, other.y) && NearEqual(z, other.z) &&
        NearEqual(w, other.w) && NearEqual(v, other.v);
}

} // namespace OHOS::Ace::NG
