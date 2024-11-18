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
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"

namespace OHOS::Ace::NG {
namespace Converter {
template<>
void AssignCast(std::optional<CalendarEdgeAlign>& dst, const Ark_CalendarAlign& src)
{
    switch (src) {
        case ARK_CALENDAR_ALIGN_START: dst = CalendarEdgeAlign::EDGE_ALIGN_START; break;
        case ARK_CALENDAR_ALIGN_CENTER: dst = CalendarEdgeAlign::EDGE_ALIGN_CENTER; break;
        case ARK_CALENDAR_ALIGN_END: dst = CalendarEdgeAlign::EDGE_ALIGN_END; break;
        default: LOGE("Unexpected enum value in Ark_CalendarAlign: %{public}d", src);
    }
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CalendarPickerInterfaceModifier {
void SetCalendarPickerOptionsImpl(Ark_NativePointer node,
                                  const Opt_CalendarOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    LOGE("ARKOALA CalendarPickerInterface::SetCalendarPickerOptionsImpl is not implemented yet");
}
} // CalendarPickerInterfaceModifier
namespace CalendarPickerAttributeModifier {
void TextStyleImpl(Ark_NativePointer node,
                   const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto textStyle = Converter::Convert<PickerTextStyle>(*value);
    CalendarPickerModelNG::SetTextStyle(frameNode, textStyle);
}
void OnChangeImpl(Ark_NativePointer node,
                  const Callback_Date_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("ARKOALA CalendarPickerInterface::OnChangeImpl is not implemented yet");
    auto onChange = [frameNode](const std::string& param) {
        Ark_Date eventInfo{};
        GetFullAPI()->getEventsAPI()->getCalendarPickerEventsReceiver()->
                      onChange(frameNode->GetId(), eventInfo);
    };
    CalendarPickerModelNG::SetOnChangeWithNode(frameNode, std::move(onChange));
}
void EdgeAlignImpl(Ark_NativePointer node,
                   Ark_CalendarAlign alignType,
                   const Opt_Offset* offset)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<DimensionOffset> convOffset;
    if (offset) {
        convOffset = Converter::OptConvert<DimensionOffset>(*offset);
    }
    auto convAlignType = Converter::OptConvert<CalendarEdgeAlign>(alignType);
    CalendarPickerModelNG::SetEdgeAlign(frameNode, convAlignType, convOffset);
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
