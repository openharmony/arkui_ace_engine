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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CalendarPickerInterfaceModifier {
void SetCalendarPickerOptionsImpl(Ark_NativePointer node,
                                  const Opt_CalendarOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //CalendarPickerModelNG::SetSetCalendarPickerOptions(frameNode, convValue);
}
} // CalendarPickerInterfaceModifier
namespace CalendarPickerAttributeModifier {
void TextStyleImpl(Ark_NativePointer node,
                   const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CalendarPickerModelNG::SetTextStyle(frameNode, convValue);
}
void OnChangeImpl(Ark_NativePointer node,
                  const Ark_Callback_Date_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CalendarPickerModelNG::SetOnChange(frameNode, convValue);
}
void EdgeAlignImpl(Ark_NativePointer node,
                   Ark_CalendarAlign alignType,
                   const Opt_Offset* offset)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(alignType);
    //auto convValue = Converter::OptConvert<type>(alignType); // for enums
    //CalendarPickerModelNG::SetEdgeAlign(frameNode, convValue);
}
} // CalendarPickerAttributeModifier
const GENERATED_ArkUICalendarPickerModifier* GetCalendarPickerModifier()
{
    static const GENERATED_ArkUICalendarPickerModifier ArkUICalendarPickerModifierImpl {
        CalendarPickerInterfaceModifier::SetCalendarPickerOptionsImpl,
        CalendarPickerAttributeModifier::TextStyleImpl,
        CalendarPickerAttributeModifier::OnChangeImpl,
        CalendarPickerAttributeModifier::EdgeAlignImpl,
    };
    return &ArkUICalendarPickerModifierImpl;
}

}
