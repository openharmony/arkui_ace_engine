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

#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "core/interfaces/arkoala/utility/validators.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace {
const int32_t YEAR_MIN = 1900;
const int32_t YEAR_MAX = 2100;
const int32_t MONTH_MIN = 1;
const int32_t MONTH_MAX = 12;
const int32_t DAY_MIN = 1;
const int32_t DAY_MAX = 31;
const std::string YEAR = "year";
const std::string MONTH = "month";
const std::string DAY = "day";

bool g_checkValidDateValues(std::unique_ptr<OHOS::Ace::JsonValue>& sourceJson)
{
    if (!sourceJson || sourceJson->IsNull()) {
        return false;
    }
    auto year = sourceJson->GetValue(YEAR);
    auto month = sourceJson->GetValue(MONTH);
    auto day = sourceJson->GetValue(DAY);

    if (!year || !year->IsNumber() || year->GetInt() < YEAR_MIN || year->GetInt() > YEAR_MAX) {
        return false;
    }
    if (!month || !month->IsNumber() || month->GetInt() < MONTH_MIN || month->GetInt() > MONTH_MAX) {
        return false;
    }
    if (!day || !day->IsNumber() || day->GetInt() < DAY_MIN || day->GetInt() > DAY_MAX) {
        return false;
    }
    return true;
}
} // namespace

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DatePickerInterfaceModifier {
void SetDatePickerOptionsImpl(Ark_NativePointer node,
                              const Opt_DatePickerOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA DatePickerInterface::SetDatePickerOptionsImpl -> Method is not "
        "implemented.");
}
} // DatePickerInterfaceModifier
namespace DatePickerAttributeModifier {
void LunarImpl(Ark_NativePointer node,
               Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetShowLunar(frameNode, Converter::Convert<bool>(value));
}
void DisappearTextStyleImpl(Ark_NativePointer node,
                            const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    PickerTextStyle textStyle = Converter::Convert<PickerTextStyle>(*value);
    DatePickerModelNG::SetDisappearTextStyle(frameNode, theme, textStyle);
}
void TextStyleImpl(Ark_NativePointer node,
                   const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    PickerTextStyle textStyle = Converter::Convert<PickerTextStyle>(*value);
    DatePickerModelNG::SetNormalTextStyle(frameNode, theme, textStyle);
}
void SelectedTextStyleImpl(Ark_NativePointer node,
                           const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    PickerTextStyle textStyle = Converter::Convert<PickerTextStyle>(*value);
    DatePickerModelNG::SetSelectedTextStyle(frameNode, theme, textStyle);
}
void OnChangeImpl(Ark_NativePointer node,
                  const Callback_DatePickerResult_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto onChange = [frameNode](const BaseEventInfo* event) {
        CHECK_NULL_VOID(event);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(event);
        CHECK_NULL_VOID(eventInfo);
        auto selectedStr = eventInfo->GetSelectedStr();
        auto sourceJson = JsonUtil::ParseJsonString(selectedStr);

        auto year = YEAR_MIN;
        auto month = MONTH_MIN;
        auto day = DAY_MIN;
        if (g_checkValidDateValues(sourceJson)) {
            year = sourceJson->GetValue(::YEAR)->GetInt();
            month = sourceJson->GetValue(::MONTH)->GetInt();
            day = sourceJson->GetValue(::DAY)->GetInt();
        }
        Ark_DatePickerResult result = {
            .year = Converter::ArkValue<Opt_Number>(year),
            .month = Converter::ArkValue<Opt_Number>(month),
            .day = Converter::ArkValue<Opt_Number>(day),
        };
        GetFullAPI()->getEventsAPI()->getDatePickerEventsReceiver()->onChange(
            frameNode->GetId(), result);
    };
    DatePickerModelNG::SetOnChange(frameNode, std::move(onChange));
}
void OnDateChangeImpl(Ark_NativePointer node,
                      const Callback_Date_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("ARKOALA DatePickerInterface::SetDatePickerOptionsImp ->"
        "Ark_CustomObject is not implemented yet");
}
} // DatePickerAttributeModifier
const GENERATED_ArkUIDatePickerModifier* GetDatePickerModifier()
{
    static const GENERATED_ArkUIDatePickerModifier ArkUIDatePickerModifierImpl {
        DatePickerInterfaceModifier::SetDatePickerOptionsImpl,
        DatePickerAttributeModifier::LunarImpl,
        DatePickerAttributeModifier::DisappearTextStyleImpl,
        DatePickerAttributeModifier::TextStyleImpl,
        DatePickerAttributeModifier::SelectedTextStyleImpl,
        DatePickerAttributeModifier::OnChangeImpl,
        DatePickerAttributeModifier::OnDateChangeImpl,
    };
    return &ArkUIDatePickerModifierImpl;
}

}
