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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RatingInterfaceModifier {
void SetRatingOptionsImpl(Ark_NativePointer node,
                          const Opt_RatingOptions* options)
{
}
} // RatingInterfaceModifier
namespace RatingAttributeModifier {
void StarsImpl(Ark_NativePointer node,
               const Ark_Number* value)
{
}
void StepSizeImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
}
void StarStyleImpl(Ark_NativePointer node,
                   const Ark_StarStyleOptions* options)
{
}
void OnChangeImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* modifier)
{
}
} // RatingAttributeModifier
const GENERATED_ArkUIRatingModifier* GetRatingModifier()
{
    static const GENERATED_ArkUIRatingModifier ArkUIRatingModifierImpl {
        RatingInterfaceModifier::SetRatingOptionsImpl,
        RatingAttributeModifier::StarsImpl,
        RatingAttributeModifier::StepSizeImpl,
        RatingAttributeModifier::StarStyleImpl,
        RatingAttributeModifier::OnChangeImpl,
        RatingAttributeModifier::ContentModifierImpl,
    };
    return &ArkUIRatingModifierImpl;
}

}
