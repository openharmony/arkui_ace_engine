/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"

#include <functional>
#include <utility>

#include "base/geometry/dimension.h"
#include "base/i18n/date_time_sequence.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/picker/picker_date_component.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_column_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/common/resource/resource_object.h"
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float PICKER_MAXFONTSCALE = 1.0f;
constexpr int32_t BUFFER_NODE_NUMBER = 2;
using DataPickerGetTextStyleFunc = const std::unique_ptr<FontStyle>& (DataPickerRowLayoutProperty::*)() const;
void ResetDataPickerTextStyleColor(FrameNode* frameNode, DataPickerGetTextStyleFunc getTextStyleFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto property = frameNode->GetLayoutPropertyPtr<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(property);
    auto& textStyle = (property->*getTextStyleFunc)();
    CHECK_NULL_VOID(textStyle);
    if (textStyle->HasTextColor()) {
        textStyle->ResetTextColor();
        property->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE_SELF);
    }
}
} // namespace
void DatePickerModelNG::CreateDatePicker(RefPtr<PickerTheme> pickerTheme)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::DATE_PICKER_ETS_TAG, nodeId);
    RefPtr<FrameNode> dateNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetPickerTag(true);
    auto language = AceApplicationInfo::GetInstance().GetLanguage();
    OrderResult orderResult;
    DateTimeSequence sequence;
    orderResult = sequence.GetDateOrder(language);
    dateOrder = orderResult.dateOrder;
    dateTimeOrder = orderResult.dateTimeOrder;
    if (language == "ug") {
        datePickerPattern->SetDateOrder("y-d-M");
    } else {
        datePickerPattern->SetDateOrder(dateOrder);
    }
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();

    auto yearId = datePickerPattern->GetYearId();
    auto monthId = datePickerPattern->GetMonthId();
    auto dayId = datePickerPattern->GetDayId();
    CHECK_NULL_VOID(pickerTheme);
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    RefPtr<FrameNode> yearColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, yearId, []() { return AceType::MakeRefPtr<DatePickerColumnPattern>(); });
    CHECK_NULL_VOID(yearColumnNode);
    if (!hasYearNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_VOID(textNode);
            textNode->MountToParent(yearColumnNode);
        }
        yearColumnNode->MarkModifyDone();
        datePickerPattern->SetColumn(yearColumnNode);
    }

    RefPtr<FrameNode> monthColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, monthId, []() { return AceType::MakeRefPtr<DatePickerColumnPattern>(); });
    CHECK_NULL_VOID(monthColumnNode);
    if (!hasMonthNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_VOID(textNode);
            textNode->MountToParent(monthColumnNode);
        }
        monthColumnNode->MarkModifyDone();
        datePickerPattern->SetColumn(monthColumnNode);
    }

    RefPtr<FrameNode> dayColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, dayId, []() { return AceType::MakeRefPtr<DatePickerColumnPattern>(); });
    CHECK_NULL_VOID(dayColumnNode);
    if (!hasDayNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_VOID(textNode);
            textNode->MountToParent(dayColumnNode);
        }
        dayColumnNode->MarkModifyDone();
        datePickerPattern->SetColumn(dayColumnNode);
    }

    if (dateOrder == "M-d-y") {
        if (!hasMonthNode) {
            CreateDateColumn(monthColumnNode, dateNode);
        }
        if (!hasDayNode) {
            CreateDateColumn(dayColumnNode, dateNode);
        }
        if (!hasYearNode) {
            CreateDateColumn(yearColumnNode, dateNode);
        }
    } else {
        if (!hasYearNode) {
            CreateDateColumn(yearColumnNode, dateNode);
        }
        if (!hasMonthNode) {
            CreateDateColumn(monthColumnNode, dateNode);
        }
        if (!hasDayNode) {
            CreateDateColumn(dayColumnNode, dateNode);
        }
    }
    stack->Push(dateNode);

    if (pickerTheme->IsCircleDial()) {
        auto renderContext = dateNode->GetRenderContext();
        renderContext->UpdateBackgroundColor(pickerTheme->GetBackgroundColor());
    }
}

void DatePickerModelNG::CreateDateColumn(const RefPtr<FrameNode>& columnNode, const RefPtr<FrameNode>& dateNode)
{
    auto stackNode = CreateStackNode();
    auto blendNode = CreateColumnNode();
    auto buttonNode = CreateButtonNode();
    buttonNode->MountToParent(stackNode);
    columnNode->MountToParent(blendNode);
    blendNode->MountToParent(stackNode);
    auto layoutProperty = stackNode->GetLayoutProperty<LayoutProperty>();
    layoutProperty->UpdateAlignment(Alignment::CENTER);
    layoutProperty->UpdateLayoutWeight(1);
    stackNode->MountToParent(dateNode);
}

RefPtr<FrameNode> DatePickerModelNG::CreateStackNode()
{
    auto stackId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, stackId, []() { return AceType::MakeRefPtr<StackPattern>(); });
}

RefPtr<FrameNode> DatePickerModelNG::CreateColumnNode()
{
    auto columnId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, columnId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
}

RefPtr<FrameNode> DatePickerModelNG::CreateButtonNode()
{
    auto buttonId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
}

RefPtr<FrameNode> DatePickerModelNG::CreateFrameNode(int32_t nodeId)
{
    auto dateNode = FrameNode::GetOrCreateFrameNode(
        V2::DATE_PICKER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<DatePickerPattern>(); });
    auto datePickerPattern = dateNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(datePickerPattern, dateNode);
    datePickerPattern->SetPickerTag(true);
    bool hasYearNode = datePickerPattern->HasYearNode();
    bool hasMonthNode = datePickerPattern->HasMonthNode();
    bool hasDayNode = datePickerPattern->HasDayNode();

    auto yearId = datePickerPattern->GetYearId();
    auto monthId = datePickerPattern->GetMonthId();
    auto dayId = datePickerPattern->GetDayId();

    auto pipeline = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, dateNode);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>(dateNode->GetThemeScopeId());
    CHECK_NULL_RETURN(pickerTheme, dateNode);
    uint32_t showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    datePickerPattern->SetShowCount(showCount);
    SetDefaultAttributes(dateNode, pickerTheme);

    auto yearColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, yearId, []() { return AceType::MakeRefPtr<DatePickerColumnPattern>(); });
    CHECK_NULL_RETURN(yearColumnNode, dateNode);
    if (!hasYearNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, dateNode);
            textNode->MountToParent(yearColumnNode);
        }
        yearColumnNode->MarkModifyDone();
        datePickerPattern->SetColumn(yearColumnNode);
    }

    auto monthColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, monthId, []() { return AceType::MakeRefPtr<DatePickerColumnPattern>(); });
    CHECK_NULL_RETURN(monthColumnNode, dateNode);
    if (!hasMonthNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, dateNode);
            textNode->MountToParent(monthColumnNode);
        }
        monthColumnNode->MarkModifyDone();
        datePickerPattern->SetColumn(monthColumnNode);
    }

    auto dayColumnNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, dayId, []() { return AceType::MakeRefPtr<DatePickerColumnPattern>(); });
    CHECK_NULL_RETURN(dayColumnNode, dateNode);
    if (!hasDayNode) {
        for (uint32_t index = 0; index < showCount; index++) {
            auto textNode = FrameNode::CreateFrameNode(
                V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
            CHECK_NULL_RETURN(textNode, dateNode);
            textNode->MountToParent(dayColumnNode);
        }
        dayColumnNode->MarkModifyDone();
        datePickerPattern->SetColumn(dayColumnNode);
    }

    if (!hasYearNode) {
        auto stackYearNode = CreateStackNode();
        auto blendYearNode = CreateColumnNode();
        auto buttonYearNode = CreateButtonNode();
        buttonYearNode->MountToParent(stackYearNode);
        yearColumnNode->MountToParent(blendYearNode);
        blendYearNode->MountToParent(stackYearNode);
        auto layoutProperty = stackYearNode->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        layoutProperty->UpdateLayoutWeight(1);
        stackYearNode->MountToParent(dateNode);
    }
    if (!hasMonthNode) {
        auto stackMonthNode = CreateStackNode();
        auto blendMonthNode = CreateColumnNode();
        auto buttonMonthNode = CreateButtonNode();
        buttonMonthNode->GetRenderContext()->UpdateBackgroundColor(Color::BLUE);
        buttonMonthNode->MountToParent(stackMonthNode);
        monthColumnNode->MountToParent(blendMonthNode);
        blendMonthNode->MountToParent(stackMonthNode);
        auto layoutProperty = stackMonthNode->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        layoutProperty->UpdateLayoutWeight(1);
        stackMonthNode->MountToParent(dateNode);
    }
    if (!hasDayNode) {
        auto stackDayNode = CreateStackNode();
        auto blendDayNode = CreateColumnNode();
        auto buttonDayNode = CreateButtonNode();
        buttonDayNode->GetRenderContext()->UpdateBackgroundColor(Color::GRAY);
        buttonDayNode->MountToParent(stackDayNode);
        dayColumnNode->MountToParent(blendDayNode);
        blendDayNode->MountToParent(stackDayNode);
        auto layoutProperty = stackDayNode->GetLayoutProperty<LayoutProperty>();
        layoutProperty->UpdateAlignment(Alignment::CENTER);
        layoutProperty->UpdateLayoutWeight(1);
        stackDayNode->MountToParent(dateNode);
    }
    return dateNode;
}

void DatePickerModelNG::SetShowLunar(bool lunar)
{
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, Lunar, lunar);
}

void DatePickerModelNG::SetCanLoop(bool isLoop)
{
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, CanLoop, isLoop);
}

void DatePickerModelNG::SetCanLoop(FrameNode* frameNode, bool isLoop)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, CanLoop, isLoop, frameNode);
}

bool DatePickerModelNG::GetCanLoop(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, true);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(datePickerPattern, true);
    return datePickerPattern->GetCanLoop();
}

void DatePickerModelNG::SetStartDate(const PickerDate& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetStartDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, StartDate, datePickerPattern->GetStartDateLunar());
}

void DatePickerModelNG::SetEndDate(const PickerDate& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetEndDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, EndDate, datePickerPattern->GetEndDateLunar());
}

void DatePickerModelNG::SetSelectedDate(const PickerDate& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetSelectDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, SelectedDate, datePickerPattern->GetSelectDate());
}

void DatePickerModelNG::SetMode(const DatePickerMode& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetMode(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, Mode, value);
}

bool DatePickerModelNG::GetEnableHapticFeedback(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, true);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(datePickerPattern, true);
    return datePickerPattern->GetEnableHapticFeedback();
}

void DatePickerModelNG::SetEnableHapticFeedback(bool isEnableHapticFeedback)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetEnableHapticFeedback(frameNode, isEnableHapticFeedback);
}

void DatePickerModelNG::SetEnableHapticFeedback(FrameNode* frameNode, bool isEnableHapticFeedback)
{
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetEnableHapticFeedback(isEnableHapticFeedback);
}

void DatePickerModelNG::SetOnChange(DateChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void DatePickerModelNG::SetOnChange(FrameNode* frameNode, DateChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void DatePickerModelNG::SetOnDateChange(DateChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDateChange(std::move(onChange));
}

void DatePickerModelNG::SetOnDateChange(FrameNode* frameNode, DateChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDateChange(std::move(onChange));
}

PickerTextStyle DatePickerModelNG::getDisappearTextStyle(FrameNode* frameNode)
{
    PickerTextStyle pickerTextStyle;
    CHECK_NULL_RETURN(frameNode, pickerTextStyle);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, pickerTextStyle);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, pickerTextStyle);
    auto style = theme->GetDisappearOptionStyle();
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        DataPickerRowLayoutProperty, DisappearFontSize, pickerTextStyle.fontSize, frameNode, style.GetFontSize());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        DataPickerRowLayoutProperty, DisappearColor, pickerTextStyle.textColor, frameNode, style.GetTextColor());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        DataPickerRowLayoutProperty, DisappearWeight, pickerTextStyle.fontWeight, frameNode, style.GetFontWeight());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(DataPickerRowLayoutProperty, DisappearFontFamily,
        pickerTextStyle.fontFamily, frameNode, style.GetFontFamilies());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(DataPickerRowLayoutProperty, DisappearFontStyle,
        pickerTextStyle.fontStyle, frameNode, style.GetFontStyle());
    return pickerTextStyle;
}

void DatePickerModelNG::SetDisappearTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(theme);

    if (SystemProperties::ConfigChangePerform()) {
        ParseDisappearTextStyleResObj(value);
    }
    auto disappearStyle = theme->GetDisappearOptionStyle();
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, DisappearFontSize,
            ConvertFontScaleValue(value.fontSize.value()));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, DisappearFontSize,
            ConvertFontScaleValue(disappearStyle.GetFontSize()));
    }
    if (value.textColor.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, DisappearColor, value.textColor.value());
    } else {
        ResetDataPickerTextStyleColor(frameNode, &DataPickerRowLayoutProperty::GetDisappearTextStyle);
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, DisappearWeight, value.fontWeight.value_or(disappearStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, DisappearFontFamily, value.fontFamily.value_or(disappearStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, DisappearFontStyle, value.fontStyle.value_or(disappearStyle.GetFontStyle()));
}

PickerTextStyle DatePickerModelNG::getNormalTextStyle(FrameNode* frameNode)
{
    PickerTextStyle pickerTextStyle;
    CHECK_NULL_RETURN(frameNode, pickerTextStyle);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, pickerTextStyle);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, pickerTextStyle);
    auto style = theme->GetOptionStyle(false, false);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        DataPickerRowLayoutProperty, FontSize, pickerTextStyle.fontSize, frameNode, style.GetFontSize());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        DataPickerRowLayoutProperty, Color, pickerTextStyle.textColor, frameNode, style.GetTextColor());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        DataPickerRowLayoutProperty, Weight, pickerTextStyle.fontWeight, frameNode, style.GetFontWeight());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(DataPickerRowLayoutProperty, FontFamily,
        pickerTextStyle.fontFamily, frameNode, style.GetFontFamilies());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(DataPickerRowLayoutProperty, FontStyle,
        pickerTextStyle.fontStyle, frameNode, style.GetFontStyle());
    return pickerTextStyle;
}

void DatePickerModelNG::SetNormalTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(theme);

    if (SystemProperties::ConfigChangePerform()) {
        ParseNormalTextStyleResObj(value);
    }
    auto normalStyle = theme->GetOptionStyle(false, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, FontSize,
            ConvertFontScaleValue(value.fontSize.value()));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, FontSize,
            ConvertFontScaleValue(normalStyle.GetFontSize()));
    }
    if (value.textColor.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, Color, value.textColor.value());
    } else {
        ResetDataPickerTextStyleColor(frameNode, &DataPickerRowLayoutProperty::GetTextStyle);
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, Weight, value.fontWeight.value_or(normalStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, FontFamily, value.fontFamily.value_or(normalStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, FontStyle, value.fontStyle.value_or(normalStyle.GetFontStyle()));
}

PickerTextStyle DatePickerModelNG::getSelectedTextStyle(FrameNode* frameNode)
{
    PickerTextStyle pickerTextStyle;
    CHECK_NULL_RETURN(frameNode, pickerTextStyle);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, pickerTextStyle);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, pickerTextStyle);
    auto style = theme->GetOptionStyle(true, false);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        DataPickerRowLayoutProperty, SelectedFontSize, pickerTextStyle.fontSize, frameNode, style.GetFontSize());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        DataPickerRowLayoutProperty, SelectedColor, pickerTextStyle.textColor, frameNode, style.GetTextColor());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        DataPickerRowLayoutProperty, SelectedWeight, pickerTextStyle.fontWeight, frameNode, style.GetFontWeight());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(DataPickerRowLayoutProperty, SelectedFontFamily,
        pickerTextStyle.fontFamily, frameNode, style.GetFontFamilies());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(DataPickerRowLayoutProperty, SelectedFontStyle,
        pickerTextStyle.fontStyle, frameNode, style.GetFontStyle());
    return pickerTextStyle;
}

void DatePickerModelNG::SetSelectedTextStyle(const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(theme);

    if (SystemProperties::ConfigChangePerform()) {
        ParseSelectedTextStyleResObj(value);
    }
    auto selectedStyle = theme->GetOptionStyle(true, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, SelectedFontSize,
            ConvertFontScaleValue(value.fontSize.value()));
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, SelectedFontSize,
            ConvertFontScaleValue(selectedStyle.GetFontSize()));
    }
    if (value.textColor.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, SelectedColor, value.textColor.value());
    } else {
        ResetDataPickerTextStyleColor(frameNode, &DataPickerRowLayoutProperty::GetSelectedTextStyle);
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, SelectedWeight, value.fontWeight.value_or(selectedStyle.GetFontWeight()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, SelectedFontFamily, value.fontFamily.value_or(selectedStyle.GetFontFamilies()));
    ACE_UPDATE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, SelectedFontStyle, value.fontStyle.value_or(selectedStyle.GetFontStyle()));
}

void DatePickerModelNG::SetDefaultAttributes(RefPtr<FrameNode>& frameNode, const RefPtr<PickerTheme>& pickerTheme)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(pickerTheme);
    auto selectedStyle = pickerTheme->GetOptionStyle(true, false);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, SelectedFontSize,
        ConvertFontScaleValue(selectedStyle.GetFontSize()), frameNode);
    ResetDataPickerTextStyleColor(Referenced::RawPtr(frameNode), &DataPickerRowLayoutProperty::GetSelectedTextStyle);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, SelectedWeight, selectedStyle.GetFontWeight(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, SelectedFontFamily, selectedStyle.GetFontFamilies(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, SelectedFontStyle, selectedStyle.GetFontStyle(), frameNode);

    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, DisappearFontSize,
        ConvertFontScaleValue(disappearStyle.GetFontSize()), frameNode);
    ResetDataPickerTextStyleColor(Referenced::RawPtr(frameNode), &DataPickerRowLayoutProperty::GetDisappearTextStyle);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, DisappearWeight, disappearStyle.GetFontWeight(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, DisappearFontFamily, disappearStyle.GetFontFamilies(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, DisappearFontStyle, disappearStyle.GetFontStyle(), frameNode);

    auto normalStyle = pickerTheme->GetOptionStyle(false, false);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, FontSize,
        ConvertFontScaleValue(normalStyle.GetFontSize()), frameNode);
    ResetDataPickerTextStyleColor(Referenced::RawPtr(frameNode), &DataPickerRowLayoutProperty::GetTextStyle);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, Weight, normalStyle.GetFontWeight(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, FontFamily, normalStyle.GetFontFamilies(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, FontStyle, normalStyle.GetFontStyle(), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, DigitalCrownSensitivity, pickerTheme->GetDigitalCrownSensitivity(), frameNode);
}

void DatePickerModelNG::HasUserDefinedDisappearFontFamily(bool isUserDefined)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->HasUserDefinedDisappearFontFamily(isUserDefined);
}

void DatePickerModelNG::HasUserDefinedNormalFontFamily(bool isUserDefined)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->HasUserDefinedNormalFontFamily(isUserDefined);
}

void DatePickerModelNG::HasUserDefinedSelectedFontFamily(bool isUserDefined)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->HasUserDefinedSelectedFontFamily(isUserDefined);
}

void DatePickerModelNG::SetBackgroundColor(const Color& color)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetBackgroundColor(color);
}

void DatePickerModelNG::SetBackgroundColor(FrameNode* frameNode, const Color& color)
{
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetBackgroundColor(color);
}

void DatePickerModelNG::SetStartDate(FrameNode* frameNode, const PickerDate& value)
{
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetStartDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, StartDate, datePickerPattern->GetStartDateLunar());
}

void DatePickerModelNG::SetEndDate(FrameNode* frameNode, const PickerDate& value)
{
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetEndDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, EndDate, datePickerPattern->GetEndDateLunar());
}

void DatePickerModelNG::SetSelectedDate(FrameNode* frameNode, const PickerDate& value)
{
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetSelectDate(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, SelectedDate, datePickerPattern->GetSelectDate());
}

void DatePickerModelNG::SetMode(FrameNode* frameNode, const DatePickerMode& value)
{
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetMode(value);
    ACE_UPDATE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, Mode, value);
}

void DatePickerModelNG::SetChangeEvent(DateChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<DatePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(onChange));
}

void DatePickerModelNG::SetDigitalCrownSensitivity(int32_t crownSensitivity)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetDigitalCrownSensitivity(frameNode, crownSensitivity);
}

void DatePickerModelNG::SetDigitalCrownSensitivity(FrameNode* frameNode, int32_t crownSensitivity)
{
    if (crownSensitivity < CROWN_SENSITIVITY_MIN || crownSensitivity > CROWN_SENSITIVITY_MAX) {
        return;
    }

    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->SetDigitalCrownSensitivity(crownSensitivity);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, DigitalCrownSensitivity, crownSensitivity, frameNode);
}

void DatePickerDialogModelNG::SetDatePickerDialogShow(PickerDialogInfo& pickerDialog,
    NG::DatePickerSettingData& settingData, std::function<void()>&& onCancel,
    std::function<void(const std::string&)>&& onAccept, std::function<void(const std::string&)>&& onChange,
    std::function<void(const std::string&)>&& onDateAccept, std::function<void(const std::string&)>&& onDateChange,
    DatePickerType pickerType, PickerDialogEvent& pickerDialogEvent, const std::vector<ButtonInfo>& buttonInfos)
{
    auto container = Container::Current();
    if (!container) {
        return;
    }
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    if (!pipelineContext) {
        return;
    }

    auto executor = pipelineContext->GetTaskExecutor();
    if (!executor) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);
    std::map<std::string, NG::DialogEvent> dialogEvent;
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    dialogEvent["changeId"] = onChange;
    dialogEvent["acceptId"] = onAccept;
    dialogEvent["dateChangeId"] = onDateChange;
    dialogEvent["dateAcceptId"] = onDateAccept;
    auto func = [onCancel](const GestureEvent& /* info */) {
        if (onCancel) {
            onCancel();
        }
    };
    dialogCancelEvent["cancelId"] = func;
    dialogLifeCycleEvent["didAppearId"] = pickerDialogEvent.onDidAppear;
    dialogLifeCycleEvent["didDisappearId"] = pickerDialogEvent.onDidDisappear;
    dialogLifeCycleEvent["willAppearId"] = pickerDialogEvent.onWillAppear;
    dialogLifeCycleEvent["willDisappearId"] = pickerDialogEvent.onWillDisappear;
    DialogProperties properties;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        properties.alignment = theme->GetAlignment();
    }
    if (pickerDialog.alignment.has_value()) {
        properties.alignment = pickerDialog.alignment.value();
    }
    if (pickerDialog.backgroundColor.has_value()) {
        properties.backgroundColor = pickerDialog.backgroundColor.value();
    }
    if (pickerDialog.backgroundBlurStyle.has_value()) {
        properties.backgroundBlurStyle = pickerDialog.backgroundBlurStyle.value();
    }
    if (pickerDialog.blurStyleOption.has_value()) {
        properties.blurStyleOption = pickerDialog.blurStyleOption.value();
    }
    if (pickerDialog.effectOption.has_value()) {
        properties.effectOption = pickerDialog.effectOption.value();
    }
    if (pickerDialog.shadow.has_value()) {
        properties.shadow = pickerDialog.shadow.value();
    }
    if (pickerDialog.hoverModeArea.has_value()) {
        properties.hoverModeArea = pickerDialog.hoverModeArea.value();
    }
    properties.enableHoverMode = pickerDialog.enableHoverMode;
    properties.customStyle = false;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));
    }
    if (pickerDialog.offset.has_value()) {
        properties.offset = pickerDialog.offset.value();
    }

    properties.maskRect = pickerDialog.maskRect;

    std::map<std::string, PickerDate> datePickerProperty;
    std::map<std::string, PickerTime> timePickerProperty;
    if (pickerDialog.isStartDate == true) {
        settingData.datePickerProperty["start"] = pickerDialog.parseStartDate;
    }
    if (pickerDialog.isEndDate == true) {
        settingData.datePickerProperty["end"] = pickerDialog.parseEndDate;
    }
    if (pickerDialog.isSelectedDate == true) {
        settingData.datePickerProperty["selected"] = pickerDialog.parseSelectedDate;
        settingData.timePickerProperty["selected"] = pickerDialog.pickerTime;
    }
    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    executor->PostTask(
        [properties, settingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent, buttonInfos,
            weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowDateDialog(
                properties, settingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent, buttonInfos);
        },
        TaskExecutor::TaskType::UI, "ArkUIDatePickerShowDateDialog",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}

void DatePickerModelNG::SetSelectedTextStyle(
    FrameNode* frameNode, const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    CHECK_NULL_VOID(theme);
    if (SystemProperties::ConfigChangePerform()) {
        ParseSelectedTextStyleResObj(value);
    }
    auto selectedStyle = theme->GetOptionStyle(true, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            DataPickerRowLayoutProperty, SelectedFontSize,
            ConvertFontScaleValue(value.fontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            DataPickerRowLayoutProperty, SelectedFontSize,
            ConvertFontScaleValue(selectedStyle.GetFontSize()), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, SelectedColor, value.textColor.value_or(selectedStyle.GetTextColor()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, SelectedWeight,
        value.fontWeight.value_or(selectedStyle.GetFontWeight()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, SelectedFontFamily,
        value.fontFamily.value_or(selectedStyle.GetFontFamilies()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, SelectedFontStyle,
        value.fontStyle.value_or(selectedStyle.GetFontStyle()), frameNode);
}

void DatePickerModelNG::SetNormalTextStyle(
    FrameNode* frameNode, const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    CHECK_NULL_VOID(theme);
    if (SystemProperties::ConfigChangePerform()) {
        ParseNormalTextStyleResObj(value);
    }
    auto normalStyle = theme->GetOptionStyle(false, false);
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, FontSize,
            ConvertFontScaleValue(value.fontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, FontSize,
            ConvertFontScaleValue(normalStyle.GetFontSize()), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, Color, value.textColor.value_or(normalStyle.GetTextColor()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, Weight, value.fontWeight.value_or(normalStyle.GetFontWeight()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, FontFamily, value.fontFamily.value_or(normalStyle.GetFontFamilies()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(
        DataPickerRowLayoutProperty, FontStyle, value.fontStyle.value_or(normalStyle.GetFontStyle()), frameNode);
}

void DatePickerModelNG::SetDisappearTextStyle(
    FrameNode* frameNode, const RefPtr<PickerTheme>& theme, const PickerTextStyle& value)
{
    CHECK_NULL_VOID(theme);
    if (SystemProperties::ConfigChangePerform()) {
        ParseDisappearTextStyleResObj(value);
    }
    auto disappearStyle = theme->GetDisappearOptionStyle();
    if (value.fontSize.has_value() && value.fontSize->IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            DataPickerRowLayoutProperty, DisappearFontSize,
            ConvertFontScaleValue(value.fontSize.value()), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            DataPickerRowLayoutProperty, DisappearFontSize,
            ConvertFontScaleValue(disappearStyle.GetFontSize()), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, DisappearColor,
        value.textColor.value_or(disappearStyle.GetTextColor()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, DisappearWeight,
        value.fontWeight.value_or(disappearStyle.GetFontWeight()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, DisappearFontFamily,
        value.fontFamily.value_or(disappearStyle.GetFontFamilies()), frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, DisappearFontStyle,
        value.fontStyle.value_or(disappearStyle.GetFontStyle()), frameNode);
}

void DatePickerModelNG::SetShowLunar(FrameNode* frameNode, bool lunar)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DataPickerRowLayoutProperty, Lunar, lunar, frameNode);
}

int32_t DatePickerModelNG::getLunar(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return frameNode->GetLayoutProperty<DataPickerRowLayoutProperty>()->GetLunar().value_or(0);
}

LunarDate DatePickerModelNG::getStartDate(FrameNode* frameNode)
{
    LunarDate lunarDate;
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(datePickerPattern, lunarDate);
    auto dateSolar = datePickerPattern->GetStartDateSolar();
    lunarDate.year = dateSolar.GetYear();
    lunarDate.month = dateSolar.GetMonth();
    lunarDate.day = dateSolar.GetDay();
    return lunarDate;
}

LunarDate DatePickerModelNG::getEndDate(FrameNode* frameNode)
{
    LunarDate lunarDate;
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(datePickerPattern, lunarDate);
    auto dateSolar = datePickerPattern->GetEndDateSolar();
    lunarDate.year = dateSolar.GetYear();
    lunarDate.month = dateSolar.GetMonth();
    lunarDate.day = dateSolar.GetDay();
    return lunarDate;
}

LunarDate DatePickerModelNG::getSelectedDate(FrameNode* frameNode)
{
    LunarDate lunarDate;
    CHECK_NULL_RETURN(frameNode, lunarDate);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, lunarDate);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, lunarDate);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(datePickerPattern, lunarDate);
    PickerDate pickerDate = datePickerPattern->GetSelectedDate();
    lunarDate.year = pickerDate.GetYear();
    lunarDate.month = pickerDate.GetMonth();
    lunarDate.day = pickerDate.GetDay();
    return lunarDate;
}

DatePickerMode DatePickerModelNG::getMode(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, DatePickerMode::DATE);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_RETURN(datePickerPattern, DatePickerMode::DATE);
    return datePickerPattern->GetMode();
}

uint32_t DatePickerModelNG::getBackgroundColor(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto paintProperty = frameNode->GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_RETURN(paintProperty, 0);
    auto color = paintProperty->GetScrollBarColor();
    CHECK_NULL_RETURN(color, 0);
    return color->GetValue();
}

const Dimension DatePickerModelNG::ConvertFontScaleValue(const Dimension& fontSizeValue)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto maxAppFontScale = pipeline->GetMaxAppFontScale();
    auto follow = pipeline->IsFollowSystem();
    float fontScale = pipeline->GetFontScale();
    if (NearZero(fontScale) || (fontSizeValue.Unit() == DimensionUnit::VP)) {
        return fontSizeValue;
    }
    if (GreatOrEqualCustomPrecision(fontScale, PICKER_MAXFONTSCALE) && follow) {
        fontScale = std::clamp(fontScale, 0.0f, maxAppFontScale);
        if (fontScale != 0.0f) {
            return Dimension(fontSizeValue / fontScale);
        }
    }
    return fontSizeValue;
}

void DatePickerModelNG::HasUserDefinedOpacity()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    datePickerPattern->SetUserDefinedOpacity(renderContext->GetOpacityValue(1.0));
}

void DatePickerModelNG::UpdateUserSetSelectColor()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto datePickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    datePickerPattern->UpdateUserSetSelectColor();
}

void DatePickerModelNG::ParseResTextStyle(const PickerTextStyle& textStyleOpt, const std::string& textStyleType,
    std::function<void(const PickerTextStyle&)> updateTextStyleFunc)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(pickerPattern);

    auto&& updateFunc = [textStyleOpt, frameNode, updateTextStyleFunc](const RefPtr<ResourceObject> resObj) {
        PickerTextStyle textStyle;
        Color color;
        CalcDimension fontSize;
        std::vector<std::string> families;

        if (textStyleOpt.textColorResObj &&
            ResourceParseUtils::ParseResColor(textStyleOpt.textColorResObj, color)) {
            textStyle.textColor = color;
        }

        if (textStyleOpt.fontSizeResObj &&
            ResourceParseUtils::ParseResDimensionFp(textStyleOpt.fontSizeResObj, fontSize)) {
            textStyle.fontSize = fontSize;
        }

        if (textStyleOpt.fontFamilyResObj &&
            ResourceParseUtils::ParseResFontFamilies(textStyleOpt.fontFamilyResObj, families)) {
            textStyle.fontFamily = families;
        }

        updateTextStyleFunc(textStyle);
    };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
    pickerPattern->AddResObj(textStyleType, resObj, std::move(updateFunc));
}

void DatePickerModelNG::ParseDisappearTextStyleResObj(const PickerTextStyle& textStyleOpt)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(pickerPattern);

    ParseResTextStyle(
        textStyleOpt,
        "DatePickerDisappearTextStyle",
        [pickerPattern](const PickerTextStyle& textStyle) { pickerPattern->UpdateDisappearTextStyle(textStyle); }
    );
}

void DatePickerModelNG::ParseSelectedTextStyleResObj(const PickerTextStyle& textStyleOpt)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(pickerPattern);

    ParseResTextStyle(
        textStyleOpt,
        "DatePickerSelectedTextStyle",
        [pickerPattern](const PickerTextStyle& textStyle) { pickerPattern->UpdateSelectedTextStyle(textStyle); }
    );
}

void DatePickerModelNG::ParseNormalTextStyleResObj(const PickerTextStyle& textStyleOpt)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto pickerPattern = frameNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(pickerPattern);

    ParseResTextStyle(
        textStyleOpt,
        "DatePickerNormalTextStyle",
        [pickerPattern](const PickerTextStyle& textStyle) { pickerPattern->UpdateNormalTextStyle(textStyle); }
    );
}
} // namespace OHOS::Ace::NG
