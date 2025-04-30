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
namespace RatingModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // RatingModifier
namespace RatingInterfaceModifier {
void SetRatingOptionsImpl(Ark_NativePointer node,
                          const Opt_RatingOptions* options)
{
}
} // RatingInterfaceModifier
namespace RatingAttributeModifier {
void Stars0Impl(Ark_NativePointer node,
                const Opt_Number* value)
{
}
void Stars1Impl(Ark_NativePointer node,
                const Opt_Number* value)
{
}
void StepSize0Impl(Ark_NativePointer node,
                   const Opt_Number* value)
{
}
void StepSize1Impl(Ark_NativePointer node,
                   const Opt_Number* value)
{
}
void StarStyle0Impl(Ark_NativePointer node,
                    const Opt_StarStyleOptions* value)
{
}
void StarStyle1Impl(Ark_NativePointer node,
                    const Opt_StarStyleOptions* value)
{
}
void OnChange0Impl(Ark_NativePointer node,
                   const Opt_Callback_Number_Void* value)
{
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnRatingChangeCallback* value)
{
}
void ContentModifier0Impl(Ark_NativePointer node,
                          const Opt_ContentModifier* value)
{
}
void ContentModifier1Impl(Ark_NativePointer node,
                          const Opt_ContentModifier* value)
{
}
void _onChangeEvent_ratingImpl(Ark_NativePointer node,
                               const Callback_Number_Void* callback)
{
}
} // RatingAttributeModifier
const GENERATED_ArkUIRatingModifier* GetRatingModifier()
{
    static const GENERATED_ArkUIRatingModifier ArkUIRatingModifierImpl {
        RatingModifier::ConstructImpl,
        RatingInterfaceModifier::SetRatingOptionsImpl,
        RatingAttributeModifier::Stars0Impl,
        RatingAttributeModifier::Stars1Impl,
        RatingAttributeModifier::StepSize0Impl,
        RatingAttributeModifier::StepSize1Impl,
        RatingAttributeModifier::StarStyle0Impl,
        RatingAttributeModifier::StarStyle1Impl,
        RatingAttributeModifier::OnChange0Impl,
        RatingAttributeModifier::OnChange1Impl,
        RatingAttributeModifier::ContentModifier0Impl,
        RatingAttributeModifier::ContentModifier1Impl,
        RatingAttributeModifier::_onChangeEvent_ratingImpl,
    };
    return &ArkUIRatingModifierImpl;
}

}
