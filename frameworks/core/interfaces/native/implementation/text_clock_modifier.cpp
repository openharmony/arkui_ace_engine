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
namespace TextClockModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // TextClockModifier
namespace TextClockInterfaceModifier {
void SetTextClockOptionsImpl(Ark_NativePointer node,
                             const Opt_TextClockOptions* options)
{
}
} // TextClockInterfaceModifier
namespace TextClockAttributeModifier {
void FormatImpl(Ark_NativePointer node,
                const Opt_String* value)
{
}
void OnDateChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_Number_Void* value)
{
}
void FontColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
}
void FontSizeImpl(Ark_NativePointer node,
                  const Opt_Length* value)
{
}
void FontStyleImpl(Ark_NativePointer node,
                   const Opt_FontStyle* value)
{
}
void FontWeightImpl(Ark_NativePointer node,
                    const Opt_Union_Number_FontWeight_String* value)
{
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Opt_ResourceStr* value)
{
}
void TextShadowImpl(Ark_NativePointer node,
                    const Opt_Union_ShadowOptions_Array_ShadowOptions* value)
{
}
void FontFeatureImpl(Ark_NativePointer node,
                     const Opt_String* value)
{
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Opt_ContentModifier* value)
{
}
void DateTimeOptionsImpl(Ark_NativePointer node,
                         const Opt_DateTimeOptions* value)
{
}
} // TextClockAttributeModifier
const GENERATED_ArkUITextClockModifier* GetTextClockModifier()
{
    static const GENERATED_ArkUITextClockModifier ArkUITextClockModifierImpl {
        TextClockModifier::ConstructImpl,
        TextClockInterfaceModifier::SetTextClockOptionsImpl,
        TextClockAttributeModifier::FormatImpl,
        TextClockAttributeModifier::OnDateChangeImpl,
        TextClockAttributeModifier::FontColorImpl,
        TextClockAttributeModifier::FontSizeImpl,
        TextClockAttributeModifier::FontStyleImpl,
        TextClockAttributeModifier::FontWeightImpl,
        TextClockAttributeModifier::FontFamilyImpl,
        TextClockAttributeModifier::TextShadowImpl,
        TextClockAttributeModifier::FontFeatureImpl,
        TextClockAttributeModifier::ContentModifierImpl,
        TextClockAttributeModifier::DateTimeOptionsImpl,
    };
    return &ArkUITextClockModifierImpl;
}

}
