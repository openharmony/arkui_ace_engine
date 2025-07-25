/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace FilterAccessor {
void DestroyPeerImpl(Ark_Filter peer)
{
}
Ark_Filter CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Filter PixelStretchImpl(Ark_Filter peer,
                            const Array_Number* stretchSizes,
                            Ark_TileMode tileMode)
{
    return {};
}
Ark_Filter BlurImpl(Ark_Filter peer,
                    const Ark_Number* blurRadius)
{
    return {};
}
Ark_Filter WaterRippleImpl(Ark_Filter peer,
                           const Ark_Number* progress,
                           const Ark_Number* waveCount,
                           const Ark_Number* x,
                           const Ark_Number* y,
                           Ark_WaterRippleMode rippleMode)
{
    return {};
}
Ark_Filter FlyInFlyOutEffectImpl(Ark_Filter peer,
                                 const Ark_Number* degree,
                                 Ark_FlyMode flyMode)
{
    return {};
}
Ark_Filter DistortImpl(Ark_Filter peer,
                       const Ark_Number* distortionK)
{
    return {};
}
} // FilterAccessor
const GENERATED_ArkUIFilterAccessor* GetFilterAccessor()
{
    static const GENERATED_ArkUIFilterAccessor FilterAccessorImpl {
        FilterAccessor::DestroyPeerImpl,
        FilterAccessor::CtorImpl,
        FilterAccessor::GetFinalizerImpl,
        FilterAccessor::PixelStretchImpl,
        FilterAccessor::BlurImpl,
        FilterAccessor::WaterRippleImpl,
        FilterAccessor::FlyInFlyOutEffectImpl,
        FilterAccessor::DistortImpl,
    };
    return &FilterAccessorImpl;
}

}
