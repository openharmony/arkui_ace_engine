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
namespace ImageSpanInterfaceModifier {
void SetImageSpanOptionsImpl(Ark_NativePointer node,
                             const Type_ImageSpanInterface_setImageSpanOptions_Arg0* value)
{
}
} // ImageSpanInterfaceModifier
namespace ImageSpanAttributeModifier {
void VerticalAlignImpl(Ark_NativePointer node,
                       enum Ark_ImageSpanAlignment value)
{
}
void ColorFilterImpl(Ark_NativePointer node,
                     const Type_ImageSpanAttribute_colorFilter_Arg0* filter)
{
}
void ObjectFitImpl(Ark_NativePointer node,
                   enum Ark_ImageFit value)
{
}
void OnCompleteImpl(Ark_NativePointer node,
                    Ark_Function callback)
{
}
void OnErrorImpl(Ark_NativePointer node,
                 Ark_Function callback)
{
}
void AltImpl(Ark_NativePointer node,
             const Ark_CustomObject* value)
{
}
} // ImageSpanAttributeModifier
const GENERATED_ArkUIImageSpanModifier* GetImageSpanModifier()
{
    static const GENERATED_ArkUIImageSpanModifier ArkUIImageSpanModifierImpl {
        ImageSpanInterfaceModifier::SetImageSpanOptionsImpl,
        ImageSpanAttributeModifier::VerticalAlignImpl,
        ImageSpanAttributeModifier::ColorFilterImpl,
        ImageSpanAttributeModifier::ObjectFitImpl,
        ImageSpanAttributeModifier::OnCompleteImpl,
        ImageSpanAttributeModifier::OnErrorImpl,
        ImageSpanAttributeModifier::AltImpl,
    };
    return &ArkUIImageSpanModifierImpl;
}

}
