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
#include "core/interfaces/native/generated/interface/ui_node_api.h"
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
struct DatePickerOptions {
    PickerDate start;
    PickerDate end;
    PickerDate selected;
    DatePickerMode mode;
};
} // namespace
namespace Converter {
template<>
void AssignCast(std::optional<DatePickerOptions>& dst, const Ark_DatePickerOptions& src)
{
    DatePickerOptions options;
    auto opt = Converter::OptConvert<PickerDate>(src.start);
    if (opt) {
        options.start = *opt;
    }
    opt = Converter::OptConvert<PickerDate>(src.end);
    if (opt) {
        options.end = *opt;
    }
    opt = Converter::OptConvert<PickerDate>(src.selected);
    if (opt) {
        options.selected = *opt;
    }

    auto mode = Converter::OptConvert<DatePickerMode>(src.mode);
    if (mode) {
        options.mode = *mode;
    }
    dst = options;
}
} // namespace  OHOS::Ace:NG:Converter
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
    CHECK_NULL_VOID(options);
    auto opt = Converter::OptConvert<DatePickerOptions>(*options);
    CHECK_NULL_VOID(opt);

    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto startDate = opt->start;
    auto endDate = opt->end;
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

    DatePickerModelNG::SetStartDate(frameNode, startDate);
    DatePickerModelNG::SetEndDate(frameNode, endDate);
    DatePickerModelNG::SetSelectedDate(frameNode, opt->selected);

    DatePickerModelNG::SetMode(frameNode, opt->mode);
}
} // DatePickerInterfaceModifier
namespace DatePickerAttributeModifier {
void Lunar0Impl(Ark_NativePointer node,
                const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    DatePickerModelNG::SetShowLunar(frameNode, *convValue);
}
void Lunar1Impl(Ark_NativePointer node,
                const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto lunar = Converter::OptConvert<bool>(*value).value_or(false);
    DatePickerModelNG::SetShowLunar(frameNode, lunar);
}
void DisappearTextStyle0Impl(Ark_NativePointer node,
                             const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    auto convValue = Converter::OptConvert<PickerTextStyle>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    DatePickerModelNG::SetDisappearTextStyle(frameNode, theme, *convValue);
}
void DisappearTextStyle1Impl(Ark_NativePointer node,
                             const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    auto textStyle = Converter::OptConvert<PickerTextStyle>(*value).value_or(DEFAULT_DISAPPEAR_TEXT_STYLE);
    DatePickerModelNG::SetDisappearTextStyle(frameNode, theme, textStyle);
}
void TextStyle0Impl(Ark_NativePointer node,
                    const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    auto convValue = Converter::OptConvert<PickerTextStyle>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    DatePickerModelNG::SetNormalTextStyle(frameNode, theme, *convValue);
}
void TextStyle1Impl(Ark_NativePointer node,
                    const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    auto textStyle = Converter::OptConvert<PickerTextStyle>(*value).value_or(DEFAULT_TEXT_STYLE);
    DatePickerModelNG::SetNormalTextStyle(frameNode, theme, textStyle);
}
void SelectedTextStyle0Impl(Ark_NativePointer node,
                            const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    auto convValue = Converter::OptConvert<PickerTextStyle>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    DatePickerModelNG::SetSelectedTextStyle(frameNode, theme, *convValue);
}
void SelectedTextStyle1Impl(Ark_NativePointer node,
                            const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    auto textStyle = Converter::OptConvert<PickerTextStyle>(*value).value_or(DEFAULT_SELECTED_TEXT_STYLE);
    DatePickerModelNG::SetSelectedTextStyle(frameNode, theme, textStyle);
}
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_Callback_DatePickerResult_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onChange = [arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* event) {
        CHECK_NULL_VOID(event);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(event);
        CHECK_NULL_VOID(eventInfo);
        auto selectedStr = eventInfo->GetSelectedStr();
        auto result = Converter::ArkValue<Ark_DatePickerResult>(selectedStr);
        arkCallback.Invoke(result);
    };
    DatePickerModelStatic::SetOnChange(frameNode, std::move(onChange));
}
void OnDateChange0Impl(Ark_NativePointer node,
                       const Opt_Callback_Date_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onChange = [arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* event) {
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
void OnDateChange1Impl(Ark_NativePointer node,
                       const Opt_Callback_Date_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optCallback = Converter::OptConvert<Callback_Date_Void>(*value);
    CHECK_NULL_VOID(optCallback);
    auto onChange = [arkCallback = CallbackHelper(*optCallback)](const BaseEventInfo* event) {
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
void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                 const Opt_CrownSensitivity* value)
{
#ifdef SUPPORT_DIGITAL_CROWN
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto sensitivity = Converter::OptConvert<CrownSensitivity>(*value).value_or(DIGITAL_CROWN_SENSITIVITY_DEFAULT);
    DatePickerModelNG::SetDigitalCrownSensitivity(frameNode, static_cast<int32_t>(sensitivity));
#endif
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        return;
    }
    DatePickerModelNG::SetEnableHapticFeedback(frameNode, *convValue);
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Date_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const BaseEventInfo* event) {
        CHECK_NULL_VOID(event);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(event);
        CHECK_NULL_VOID(eventInfo);
        auto selectedStr = eventInfo->GetSelectedStr();
        auto result = Converter::ArkValue<Ark_Date>(selectedStr);
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(result);
    };
    DatePickerModelStatic::SetChangeEvent(frameNode, std::move(onEvent));
}
} // DatePickerAttributeModifier
const GENERATED_ArkUIDatePickerModifier* GetDatePickerModifier()
{
    static const GENERATED_ArkUIDatePickerModifier ArkUIDatePickerModifierImpl {
        DatePickerModifier::ConstructImpl,
        DatePickerInterfaceModifier::SetDatePickerOptionsImpl,
        DatePickerAttributeModifier::Lunar0Impl,
        DatePickerAttributeModifier::Lunar1Impl,
        DatePickerAttributeModifier::DisappearTextStyle0Impl,
        DatePickerAttributeModifier::DisappearTextStyle1Impl,
        DatePickerAttributeModifier::TextStyle0Impl,
        DatePickerAttributeModifier::TextStyle1Impl,
        DatePickerAttributeModifier::SelectedTextStyle0Impl,
        DatePickerAttributeModifier::SelectedTextStyle1Impl,
        DatePickerAttributeModifier::OnChangeImpl,
        DatePickerAttributeModifier::OnDateChange0Impl,
        DatePickerAttributeModifier::OnDateChange1Impl,
        DatePickerAttributeModifier::DigitalCrownSensitivityImpl,
        DatePickerAttributeModifier::EnableHapticFeedbackImpl,
        DatePickerAttributeModifier::_onChangeEvent_selectedImpl,
    };
    return &ArkUIDatePickerModifierImpl;
}

}
