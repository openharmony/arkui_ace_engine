/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_PROPERTIES_VECTORF_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_PROPERTIES_VECTORF_H

#include "base/utils/utils.h"

namespace OHOS::Ace::NG {
    
struct VectorF {
    VectorF(float xF, float yF) : x(xF), y(yF) {}

    bool operator==(const VectorF& other) const
    {
        return NearEqual(x, other.x) && NearEqual(y, other.y);
    }

    VectorF operator*(float value) const
    {
        return VectorF(x * value, y * value);
    }

    float x = 0.0f;
    float y = 0.0f;
};

struct Vector3F {
    Vector3F() = default;
    Vector3F(float xF, float yF, float zF) : x(xF), y(yF), z(zF) {}

    bool operator==(const Vector3F& other) const
    {
        return NearEqual(x, other.x) && NearEqual(y, other.y) && NearEqual(z, other.z);
    }

    float operator[](int32_t index) const
    {
        switch (index) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                return 0.0f;
        }
    }

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct Vector4F {
    Vector4F(float xF, float yF, float zF, float wF) : x(xF), y(yF), z(zF), w(wF) {}

    bool operator==(const Vector4F& other) const
    {
        return NearEqual(x, other.x) && NearEqual(y, other.y) && NearEqual(z, other.z) && NearEqual(w, other.w);
    }

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;
};

struct Vector5F {
    Vector5F(float xF, float yF, float zF, float wF, float vF) : x(xF), y(yF), z(zF), w(wF), v(vF) {}

    bool operator==(const Vector5F& other) const
    {
        return NearEqual(x, other.x) && NearEqual(y, other.y) && NearEqual(z, other.z) &&
            NearEqual(w, other.w) && NearEqual(v, other.v);
    }

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;
    float v = 0.0f;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_PROPERTIES_VECTORF_H