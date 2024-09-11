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
namespace DividerInterfaceModifier {
void SetDividerOptionsImpl(Ark_NativePointer node)
{
}
} // DividerInterfaceModifier
namespace DividerAttributeModifier {
void VerticalImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
}
void ColorImpl(Ark_NativePointer node,
               const ResourceColor* value)
{
}
void StrokeWidthImpl(Ark_NativePointer node,
                     const Type_DividerAttribute_strokeWidth_Arg0* value)
{
}
void LineCapImpl(Ark_NativePointer node,
                 enum Ark_LineCapStyle value)
{
}
} // DividerAttributeModifier
const GENERATED_ArkUIDividerModifier* GetDividerModifier()
{
    static const GENERATED_ArkUIDividerModifier ArkUIDividerModifierImpl {
        DividerInterfaceModifier::SetDividerOptionsImpl,
        DividerAttributeModifier::VerticalImpl,
        DividerAttributeModifier::ColorImpl,
        DividerAttributeModifier::StrokeWidthImpl,
        DividerAttributeModifier::LineCapImpl,
    };
    return &ArkUIDividerModifierImpl;
}

}
