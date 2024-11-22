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
#include "frameworks/base/utils/time_util.h"
#include "core/interfaces/arkoala/utility/callback_helper.h"

namespace OHOS::Ace::NG {
namespace {
const std::string YEAR = "year";
const std::string MONTH = "month";
const std::string DAY = "day";
const int64_t SEC_TO_MILLISEC = 1000;
const auto DATE_MIN = PickerDate(1970, 1, 1);
const auto DATE_MAX = PickerDate(2100, 12, 31);

struct DatePickerOptions {
    std::optional<PickerDate> start;
    std::optional<PickerDate> end;
    std::optional<PickerDate> selected;
};

bool IsDateValid(uint32_t year, uint32_t month, uint32_t day)
{
    auto maxDay = PickerDate::GetMaxDay(year, month);
    if (year < DATE_MIN.GetYear() || year > DATE_MAX.GetYear()) {
        return false;
    } else if (month < DATE_MIN.GetMonth() || month > DATE_MAX.GetMonth()) {
        return false;
    } else if (day < DATE_MIN.GetDay() || day > maxDay) {
        return false;
    }
    return true;
}

bool g_checkValidDateValues(std::unique_ptr<OHOS::Ace::JsonValue>& sourceJson)
{
    if (!sourceJson || sourceJson->IsNull()) {
        return false;
    }
    auto year = sourceJson->GetValue(YEAR);
    auto month = sourceJson->GetValue(MONTH);
    auto day = sourceJson->GetValue(DAY);
    if (!year || !year->IsNumber() || !month || !month->IsNumber() || !day || !day->IsNumber()) {
        return false;
    }
    if (!IsDateValid(year->GetInt(), month->GetInt(), day->GetInt())) {
        return false;
    }
    return true;
}
} // namespace
namespace Converter {
template<>
void AssignCast(std::optional<DatePickerOptions>& dst, const Ark_DatePickerOptions& src)
{
    dst->start = Converter::OptConvert<PickerDate>(src.start);
    dst->end = Converter::OptConvert<PickerDate>(src.end);
    dst->selected = Converter::OptConvert<PickerDate>(src.selected);
}

} // namespace  OHOS::Ace:NG:Converter
} // namespace  OHOS::Ace:NG
namespace OHOS::Ace::NG::GeneratedModifier {
namespace DatePickerInterfaceModifier {
void SetDatePickerOptionsImpl(Ark_NativePointer node,
                              const Opt_DatePickerOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto opt = Converter::OptConvert<DatePickerOptions>(*options);
    auto p = opt->start;
    auto p2 = opt->end;
    auto p3 = opt->selected;
    std::printf("\nmodifier:    %d-%d-%d ", p->GetYear(), p->GetMonth(), p->GetDay());
    std::printf("%d-%d-%d ", p2->GetYear(), p2->GetMonth(), p2->GetDay());
    std::printf("%d-%d-%d", p3->GetYear(), p3->GetMonth(), p3->GetDay());
    if (opt->start.has_value()) {
        std::printf("\nmodifier: 1");
        DatePickerModelNG::SetStartDate(frameNode, *(opt->start));
    }
    if (opt->end.has_value()) {
        std::printf("\nmodifier: 2");
        DatePickerModelNG::SetEndDate(frameNode, *(opt->end));
    }
    if (opt->selected.has_value()) {
        std::printf("\nmodifier: 3");
        DatePickerModelNG::SetSelectedDate(frameNode, *(opt->selected));
    }
    auto s = DatePickerModelNG::getStartDate(frameNode);
    auto s2 = DatePickerModelNG::getEndDate(frameNode);
    auto s3 = DatePickerModelNG::getSelectedDate(frameNode);
    std::printf("\nmodifier: 4 %d-%d-%d ", s.year, s.month, s.day);
    std::printf(" %d-%d-%d ", s2.year, s2.month, s2.day);
    std::printf(" %d-%d-%d\n", s3.year, s3.month, s.day);
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

        auto year = DATE_MIN.GetYear();
        auto month = DATE_MIN.GetMonth();
        auto day = DATE_MIN.GetDay();
        if (g_checkValidDateValues(sourceJson)) {
            year = sourceJson->GetValue(YEAR)->GetInt();
            month = sourceJson->GetValue(MONTH)->GetInt();
            day = sourceJson->GetValue(DAY)->GetInt();
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
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto onChange = [arkCallback = CallbackHelper(*value)](const BaseEventInfo* event) {
        CHECK_NULL_VOID(event);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(event);
        CHECK_NULL_VOID(eventInfo);
        auto selectedStr = eventInfo->GetSelectedStr();
        auto sourceJson = JsonUtil::ParseJsonString(selectedStr);

        auto year = DATE_MIN.GetYear();
        auto month = DATE_MIN.GetMonth();
        auto day = DATE_MIN.GetDay();
        if (g_checkValidDateValues(sourceJson)) {
            year = sourceJson->GetValue(YEAR)->GetInt();
            month = sourceJson->GetValue(MONTH)->GetInt();
            day = sourceJson->GetValue(DAY)->GetInt();
        }
        auto pickerDate = PickerDate(year, month, day);
        auto result = Converter::ArkValue<Ark_Date>(pickerDate);
        arkCallback.Invoke(result);
    };
    DatePickerModelNG::SetOnDateChange(frameNode, std::move(onChange));
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
