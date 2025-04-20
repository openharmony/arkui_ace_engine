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
namespace DividerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // DividerModifier
namespace DividerInterfaceModifier {
void SetDividerOptionsImpl(Ark_NativePointer node)
{
}
} // DividerInterfaceModifier
namespace DividerAttributeModifier {
void VerticalImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
}
void ColorImpl(Ark_NativePointer node,
               const Opt_ResourceColor* value)
{
}
void StrokeWidthImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String* value)
{
}
void LineCapImpl(Ark_NativePointer node,
                 const Opt_LineCapStyle* value)
{
}
} // DividerAttributeModifier
const GENERATED_ArkUIDividerModifier* GetDividerModifier()
{
    static const GENERATED_ArkUIDividerModifier ArkUIDividerModifierImpl {
        DividerModifier::ConstructImpl,
        DividerInterfaceModifier::SetDividerOptionsImpl,
        DividerAttributeModifier::VerticalImpl,
        DividerAttributeModifier::ColorImpl,
        DividerAttributeModifier::StrokeWidthImpl,
        DividerAttributeModifier::LineCapImpl,
    };
    return &ArkUIDividerModifierImpl;
}

}
