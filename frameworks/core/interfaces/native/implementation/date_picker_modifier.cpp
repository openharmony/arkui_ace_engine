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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/components_ng/base/frame_node.h"
#include "arkoala_api_generated.h"
#include "frameworks/base/utils/time_util.h"

namespace OHOS::Ace::NG {

namespace {
struct DatePickerOptions {
    PickerDate start;
    PickerDate end;
    PickerDate selected;
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
    DatePickerModelNG::SetStartDate(frameNode, opt->start);
    DatePickerModelNG::SetEndDate(frameNode, opt->end);
    DatePickerModelNG::SetSelectedDate(frameNode, opt->selected);
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
void Lunar1Impl(Ark_NativePointer node,
                const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto lunar = Converter::OptConvert<bool>(*value).value_or(false);
    DatePickerModelNG::SetShowLunar(frameNode, lunar);
}
void DisappearTextStyleImpl(Ark_NativePointer node,
                            const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
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
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
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
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
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

    auto onChange = [arkCallback = CallbackHelper(*value)](const BaseEventInfo* event) {
        CHECK_NULL_VOID(event);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(event);
        CHECK_NULL_VOID(eventInfo);
        auto selectedStr = eventInfo->GetSelectedStr();
        auto result = Converter::ArkValue<Ark_DatePickerResult>(selectedStr);
        arkCallback.Invoke(result);
    };
    DatePickerModelNG::SetOnChange(frameNode, std::move(onChange));
}
void OnDateChangeImpl(Ark_NativePointer node,
                      const Callback_Date_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto onChange = [arkCallback = CallbackHelper(*value)](const BaseEventInfo* event) {
        CHECK_NULL_VOID(event);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(event);
        CHECK_NULL_VOID(eventInfo);
        auto selectedStr = eventInfo->GetSelectedStr();
        auto result = Converter::ArkValue<Ark_Date>(selectedStr);
        arkCallback.Invoke(result);
    };
    DatePickerModelNG::SetOnDateChange(frameNode, std::move(onChange));
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
    // DatePickerModelNG::SetChangeEvent(frameNode, std::move(onEvent));
}
} // DatePickerAttributeModifier
const GENERATED_ArkUIDatePickerModifier* GetDatePickerModifier()
{
    static const GENERATED_ArkUIDatePickerModifier ArkUIDatePickerModifierImpl {
        DatePickerModifier::ConstructImpl,
        DatePickerInterfaceModifier::SetDatePickerOptionsImpl,
        DatePickerAttributeModifier::LunarImpl,
        DatePickerAttributeModifier::DisappearTextStyleImpl,
        DatePickerAttributeModifier::TextStyleImpl,
        DatePickerAttributeModifier::SelectedTextStyleImpl,
        DatePickerAttributeModifier::OnChangeImpl,
        DatePickerAttributeModifier::OnDateChangeImpl,
        DatePickerAttributeModifier::_onChangeEvent_selectedImpl,
    };
    return &ArkUIDatePickerModifierImpl;
}

}
