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

#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/datepicker_model_static.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/components_ng/base/frame_node.h"
#include "arkoala_api_generated.h"
#include "frameworks/base/utils/time_util.h"

namespace OHOS::Ace::NG {

namespace {
#ifdef SUPPORT_DIGITAL_CROWN
const auto DIGITAL_CROWN_SENSITIVITY_DEFAULT = CrownSensitivity::MEDIUM;
#endif
const auto DEFAULT_DISAPPEAR_TEXT_STYLE = PickerTextStyle { .textColor = Color(0xFF182431),
    .fontSize = Dimension(14, DimensionUnit::FP),
    .fontWeight = FontWeight::REGULAR };
const auto DEFAULT_TEXT_STYLE = PickerTextStyle { .textColor = Color(0xFF182431),
    .fontSize = Dimension(16, DimensionUnit::FP),
    .fontWeight = FontWeight::REGULAR };
const auto DEFAULT_SELECTED_TEXT_STYLE = PickerTextStyle { .textColor = Color(0xFF007DFF),
    .fontSize = Dimension(20, DimensionUnit::FP),
    .fontWeight = FontWeight::MEDIUM };
const bool DEFAULT_SHOW_LUNAR = false;
const bool DEFAULT_ENABLE_HAPTIC = true;

std::optional<PickerDate> ProcessBindableSelected(FrameNode* frameNode, const Opt_Union_Date_Bindable& value)
{
    std::optional<PickerDate> result;
    Converter::VisitUnion(value,
        [&result](const Ark_Date& src) {
            result = Converter::OptConvert<PickerDate>(src);
        },
        [&result, frameNode](const Ark_Bindable_Date& src) {
            result = Converter::OptConvert<PickerDate>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](const BaseEventInfo* event) {
                CHECK_NULL_VOID(event);
                const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(event);
                CHECK_NULL_VOID(eventInfo);
                auto selectedStr = eventInfo->GetSelectedStr();
                std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(selectedStr);
                CHECK_NULL_VOID(argsPtr);
                const auto year = argsPtr->GetValue("year")->GetInt();
                const auto month = argsPtr->GetValue("month")->GetInt() + 1; // 0-11 means 1 to 12 months
                const auto day = argsPtr->GetValue("day")->GetInt();
                PickerDateTime dateTime;
                dateTime.SetDate(PickerDate(year, month, day));
                dateTime.SetTime(PickerTime::Current());

                auto result = Converter::ArkValue<Ark_Date>(dateTime.ToString(true));
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(result);
            };
            DatePickerModelStatic::SetChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}
} // namespace
} // namespace  OHOS::Ace:NG
namespace OHOS::Ace::NG::GeneratedModifier {
namespace DatePickerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = DatePickerModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // DatePickerModifier
namespace DatePickerInterfaceModifier {
void SetDatePickerOptionsImpl(Ark_NativePointer node,
                              const Opt_DatePickerOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto opt = Converter::GetOptPtr(options);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto startDate = OPT_CONVERT_FIELD(PickerDate, opt, start).value_or(theme->GetDefaultStartDate());
    auto endDate = OPT_CONVERT_FIELD(PickerDate, opt, end).value_or(theme->GetDefaultEndDate());
    if (startDate.GetYear() <= 0) {
        startDate = theme->GetDefaultStartDate();
    }
    if (endDate.GetYear() <= 0) {
        endDate = theme->GetDefaultEndDate();
    }
    auto startDays = startDate.ToDays();
    auto endDays = endDate.ToDays();
    if (startDays > endDays) {
        startDate = theme->GetDefaultStartDate();
        endDate = theme->GetDefaultEndDate();
    }
    auto selected = (opt ? ProcessBindableSelected(frameNode, opt->selected) : std::nullopt).value_or(PickerDate{});
    auto mode = OPT_CONVERT_FIELD(DatePickerMode, opt, mode).value_or(DatePickerMode{});
    DatePickerModelNG::SetStartDate(frameNode, startDate);
    DatePickerModelNG::SetEndDate(frameNode, endDate);
    DatePickerModelNG::SetSelectedDate(frameNode, selected);
    DatePickerModelNG::SetMode(frameNode, mode);
}
} // DatePickerInterfaceModifier
namespace DatePickerAttributeModifier {
void SetLunarImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value).value_or(DEFAULT_SHOW_LUNAR);
    DatePickerModelNG::SetShowLunar(frameNode, convValue);
}
void SetDisappearTextStyleImpl(Ark_NativePointer node,
                               const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto convValue = Converter::OptConvertPtr<PickerTextStyle>(value);
    if (!convValue) {
        convValue = std::make_optional(PickerTextStyle());
    }
    DatePickerModelNG::SetDisappearTextStyle(frameNode, theme, *convValue);
}
void SetTextStyleImpl(Ark_NativePointer node,
                      const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto convValue = Converter::OptConvertPtr<PickerTextStyle>(value);
    if (!convValue) {
        convValue = std::make_optional(PickerTextStyle());
    }
    DatePickerModelNG::SetNormalTextStyle(frameNode, theme, *convValue);
}
void SetSelectedTextStyleImpl(Ark_NativePointer node,
                              const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto convValue = Converter::OptConvertPtr<PickerTextStyle>(value);
    if (!convValue) {
        convValue = std::make_optional(PickerTextStyle());
    }
    DatePickerModelNG::SetSelectedTextStyle(frameNode, theme, *convValue);
}
void SetOnDateChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_Date_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto arkCallback = optValue ? CallbackHelper(*optValue) : CallbackHelper<Callback_Date_Void>();
    auto onChange = [arkCallback](const BaseEventInfo* event) {
        CHECK_NULL_VOID(event);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(event);
        CHECK_NULL_VOID(eventInfo);
        auto selectedStr = eventInfo->GetSelectedStr();
        std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(selectedStr);
        CHECK_NULL_VOID(argsPtr);
        const auto year = argsPtr->GetValue("year")->GetInt();
        const auto month = argsPtr->GetValue("month")->GetInt() + 1; // 0-11 means 1 to 12 months
        const auto day = argsPtr->GetValue("day")->GetInt();

        PickerDateTime dateTime;
        dateTime.SetDate(PickerDate(year, month, day));
        dateTime.SetTime(PickerTime::Current());
        auto result = Converter::ArkValue<Ark_Date>(dateTime.ToString(true));
        arkCallback.Invoke(result);
    };
    DatePickerModelNG::SetOnDateChange(frameNode, std::move(onChange));
}
void SetDigitalCrownSensitivityImpl(Ark_NativePointer node,
                                    const Opt_CrownSensitivity* value)
{
#ifdef SUPPORT_DIGITAL_CROWN
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto sensitivity = Converter::OptConvertPtr<CrownSensitivity>(value).value_or(DIGITAL_CROWN_SENSITIVITY_DEFAULT);
    DatePickerModelNG::SetDigitalCrownSensitivity(frameNode, static_cast<int32_t>(sensitivity));
#endif
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value).value_or(DEFAULT_ENABLE_HAPTIC);
    DatePickerModelNG::SetEnableHapticFeedback(frameNode, convValue);
}
} // DatePickerAttributeModifier
const GENERATED_ArkUIDatePickerModifier* GetDatePickerModifier()
{
    static const GENERATED_ArkUIDatePickerModifier ArkUIDatePickerModifierImpl {
        DatePickerModifier::ConstructImpl,
        DatePickerInterfaceModifier::SetDatePickerOptionsImpl,
        DatePickerAttributeModifier::SetLunarImpl,
        DatePickerAttributeModifier::SetDisappearTextStyleImpl,
        DatePickerAttributeModifier::SetTextStyleImpl,
        DatePickerAttributeModifier::SetSelectedTextStyleImpl,
        DatePickerAttributeModifier::SetOnDateChangeImpl,
        DatePickerAttributeModifier::SetDigitalCrownSensitivityImpl,
        DatePickerAttributeModifier::SetEnableHapticFeedbackImpl,
    };
    return &ArkUIDatePickerModifierImpl;
}

}
