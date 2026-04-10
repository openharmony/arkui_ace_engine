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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_ROSEN_EFFECT_CONVERTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_ROSEN_EFFECT_CONVERTER_H

#include <array>
#include <memory>

namespace OHOS::Rosen {
class RSNGFilterBase;
template<typename T>
class Vector2;
typedef Vector2<float> Vector2f;
template<typename T>
class Vector3;
typedef Vector3<float> Vector3f;
template<typename T>
class Vector4;
typedef Vector4<float> Vector4f;
} // namespace OHOS::Rosen

namespace OHOS::Ace {
struct FrostedGlassParam;
}

namespace OHOS::Ace::NG {
class RosenEffectConverter {
public:
    static std::shared_ptr<Rosen::RSNGFilterBase> ConvertToFrostedGlassFilter(
        const FrostedGlassParam& param, float oneVpValue);
    static Rosen::Vector2f ConvertToVector2f(const std::array<float, 2>& arr);
    static Rosen::Vector3f ConvertToVector3f(const std::array<float, 3>& arr);

private:
    static Rosen::Vector2f ConvertToVector2f(const std::array<float, 2>& arr, float oneVpValue, uint32_t mask);
    static Rosen::Vector3f ConvertToVector3f(const std::array<float, 3>& arr, float oneVpValue, uint32_t mask);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_ROSEN_EFFECT_CONVERTER_H
