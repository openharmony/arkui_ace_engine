/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"

#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
void CalendarPickerModelNG::Create(const CalendarSettingData& settingData)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto pickerNode = FrameNode::GetOrCreateFrameNode(
        V2::CALENDAR_PICKER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CalendarPickerPattern>(); });
    auto pickerPattern = pickerNode->GetPattern<CalendarPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    RefPtr<CalendarTheme> theme = pipelineContext->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(theme);
    pickerPattern->SetCalendarData(settingData);
    pickerNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(std::nullopt, CalcLength(theme->GetEntryHeight())));
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(theme->GetEntryBorderWidth());
    pickerNode->GetLayoutProperty()->UpdateBorderWidth(borderWidth);
    CHECK_NULL_VOID(pickerNode->GetRenderContext());
    BorderColorProperty borderColor;
    borderColor.SetColor(theme->GetEntryBorderColor());
    pickerNode->GetRenderContext()->UpdateBorderColor(borderColor);
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(theme->GetEntryBorderRadius());
    pickerNode->GetRenderContext()->UpdateBorderRadius(borderRadius);
    pickerNode->GetRenderContext()->SetClipToFrame(true);
    CHECK_NULL_VOID(pickerNode->GetLayoutProperty<LinearLayoutProperty>());
    pickerNode->GetLayoutProperty<LinearLayoutProperty>()->UpdateMainAxisAlign(FlexAlign::CENTER);
    pickerNode->GetLayoutProperty<LinearLayoutProperty>()->UpdateCrossAxisAlign(FlexAlign::CENTER);
    pickerNode->GetLayoutProperty<LinearLayoutProperty>()->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    LayoutPicker(pickerPattern, pickerNode, settingData, theme);

    pickerNode->MarkModifyDone();
    stack->Push(pickerNode);
}

void CalendarPickerModelNG::LayoutPicker(const RefPtr<CalendarPickerPattern>& pickerPattern,
    RefPtr<FrameNode>& pickerNode, const CalendarSettingData& settingData, const RefPtr<CalendarTheme>& theme)
{
    if (!pickerPattern->HasContentNode()) {
        auto contentNode = CreateCalendarNodeChild(pickerPattern->GetContentId(), settingData, theme);
        CHECK_NULL_VOID(contentNode);
        contentNode->MountToParent(pickerNode);
    }
    auto flexNode = CreateButtonFlexChild(pickerPattern->GetButtonFlexId(), theme);
    CHECK_NULL_VOID(flexNode);
    flexNode->MountToParent(pickerNode);
    if (!pickerPattern->HasAddNode()) {
        auto addNode = CreateButtonChild(pickerPattern->GetAddId(), true, theme);
        CHECK_NULL_VOID(addNode);
        addNode->MountToParent(flexNode, 0, true);
    }
    if (!pickerPattern->HasSubNode()) {
        auto subNode = CreateButtonChild(pickerPattern->GetSubId(), false, theme);
        CHECK_NULL_VOID(subNode);
        subNode->MountToParent(flexNode, 1, true);
    }
}

RefPtr<FrameNode> CalendarPickerModelNG::CreateButtonChild(int32_t id, bool isAdd, const RefPtr<CalendarTheme>& theme)
{
    auto buttonNode =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, id, []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    CHECK_NULL_RETURN(buttonNode, nullptr);
    auto buttonEventHub = buttonNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(buttonEventHub, nullptr);
    buttonEventHub->SetStateEffect(true);

    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_RETURN(buttonLayoutProperty, nullptr);
    buttonLayoutProperty->UpdateType(ButtonType::NORMAL);

    auto buttonPattern = buttonNode->GetPattern<ButtonPattern>();
    CHECK_NULL_RETURN(buttonPattern, nullptr);

    buttonNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(theme->GetEntryButtonWidth()), CalcLength(theme->GetEntryHeight() / 2)));
    BorderRadiusProperty borderRadius;
    BorderWidthProperty borderWidth;
    if (isAdd) {
        borderWidth.leftDimen = theme->GetEntryBorderWidth();
        borderWidth.bottomDimen = theme->GetEntryBorderWidth() / 2;
        borderRadius.radiusTopRight = theme->GetEntryBorderRadius();
    } else {
        borderWidth.leftDimen = theme->GetEntryBorderWidth();
        borderWidth.topDimen = theme->GetEntryBorderWidth() / 2;
        borderRadius.radiusBottomRight = theme->GetEntryBorderRadius();
    }
    buttonLayoutProperty->UpdateBorderRadius(borderRadius);
    buttonNode->GetLayoutProperty()->UpdateBorderWidth(borderWidth);
    BorderColorProperty borderColor;
    borderColor.SetColor(theme->GetEntryBorderColor());
    buttonNode->GetRenderContext()->UpdateBorderColor(borderColor);
    buttonNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    buttonNode->MarkModifyDone();

    auto imageNode = CreateButtonImageChild(isAdd, theme);
    CHECK_NULL_RETURN(imageNode, nullptr);
    imageNode->MountToParent(buttonNode);
    return buttonNode;
}

RefPtr<FrameNode> CalendarPickerModelNG::CreateButtonImageChild(bool isAdd, const RefPtr<CalendarTheme>& theme)
{
    auto imageNode = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    CHECK_NULL_RETURN(imageNode, nullptr);
    imageNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(theme->GetEntryArrowWidth()), CalcLength(theme->GetEntryArrowHeight())));
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto iconTheme = pipeline->GetTheme<IconTheme>();
    std::string iconPath;
    ImageSourceInfo imageSourceInfo;
    if (isAdd) {
        imageSourceInfo.SetResourceId(InternalResource::ResourceId::IC_PUBLIC_ARROW_UP_SVG);
        iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::IC_PUBLIC_ARROW_UP_SVG);
    } else {
        imageSourceInfo.SetResourceId(InternalResource::ResourceId::IC_PUBLIC_ARROW_DOWN_SVG);
        iconPath = iconTheme->GetIconPath(InternalResource::ResourceId::IC_PUBLIC_ARROW_DOWN_SVG);
    }
    imageSourceInfo.SetSrc(iconPath, theme->GetEntryArrowColor());
    imageNode->GetLayoutProperty<ImageLayoutProperty>()->UpdateImageSourceInfo(imageSourceInfo);
    imageNode->MarkModifyDone();
    return imageNode;
}

RefPtr<FrameNode> CalendarPickerModelNG::CreateButtonFlexChild(int32_t buttonFlexId, const RefPtr<CalendarTheme>& theme)
{
    auto flexNode = FrameNode::GetOrCreateFrameNode(
        V2::FLEX_ETS_TAG, buttonFlexId, []() { return AceType::MakeRefPtr<FlexLayoutPattern>(); });
    CHECK_NULL_RETURN(flexNode, nullptr);
    flexNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(theme->GetEntryButtonWidth()), CalcLength(theme->GetEntryHeight())));
    auto flexLayoutProperty = flexNode->GetLayoutProperty<FlexLayoutProperty>();
    CHECK_NULL_RETURN(flexLayoutProperty, nullptr);
    flexLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
    flexLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    return flexNode;
}

RefPtr<FrameNode> CalendarPickerModelNG::CreateCalendarNodeChild(
    int32_t contentId, const CalendarSettingData& settingData, const RefPtr<CalendarTheme>& theme)
{
    auto contentNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, contentId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    CHECK_NULL_RETURN(contentNode, nullptr);

    PickerDate date = settingData.selectedDate;
    auto linearLayoutProperty = contentNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_RETURN(linearLayoutProperty, nullptr);

    linearLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
    contentNode->GetRenderContext()->SetClipToFrame(true);
    contentNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(std::nullopt, CalcLength(theme->GetEntryHeight())));
    linearLayoutProperty->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = theme->GetEntryBorderRadius();
    borderRadius.radiusBottomLeft = theme->GetEntryBorderRadius();
    borderRadius.radiusTopRight = theme->GetEntryBorderRadius();
    borderRadius.radiusBottomLeft = theme->GetEntryBorderRadius();
    contentNode->GetRenderContext()->UpdateBorderRadius(borderRadius);
    MarginProperty margin;
    margin.top = CalcLength(theme->GetEntryDateTopBottomMargin());
    margin.left = CalcLength(theme->GetEntryDateLeftRightMargin());
    margin.right = CalcLength(theme->GetEntryDateLeftRightMargin());
    margin.bottom = CalcLength(theme->GetEntryDateTopBottomMargin());
    linearLayoutProperty->UpdateMargin(margin);

    auto yearNode = CreateDateTextNode(std::to_string(date.GetYear()));
    CHECK_NULL_RETURN(yearNode, nullptr);
    yearNode->MountToParent(contentNode);

    auto textNode1 = CreateDateTextNode("/");
    CHECK_NULL_RETURN(textNode1, nullptr);
    textNode1->MountToParent(contentNode);

    auto monthString = (date.GetMonth() < 10 ? "0" : "") + std::to_string(date.GetMonth());
    auto monthNode = CreateDateTextNode(monthString);
    CHECK_NULL_RETURN(monthNode, nullptr);
    monthNode->MountToParent(contentNode);

    auto textNode2 = CreateDateTextNode("/");
    CHECK_NULL_RETURN(textNode2, nullptr);
    textNode2->MountToParent(contentNode);

    auto dayString = (date.GetDay() < 10 ? "0" : "") + std::to_string(date.GetDay());
    auto dayNode = CreateDateTextNode(dayString);
    CHECK_NULL_RETURN(dayNode, nullptr);
    dayNode->MountToParent(contentNode);

    contentNode->MarkModifyDone();
    return contentNode;
}

RefPtr<FrameNode> CalendarPickerModelNG::CreateDateTextNode(const std::string& textContent)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    RefPtr<CalendarTheme> calendarTheme = pipeline->GetTheme<CalendarTheme>();
    CHECK_NULL_RETURN(calendarTheme, nullptr);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(textContent);
    textLayoutProperty->UpdateTextColor(calendarTheme->GetEntryFontColor());
    textLayoutProperty->UpdateFontSize(calendarTheme->GetEntryFontSize());
    textNode->MarkModifyDone();
    return textNode;
}

void CalendarPickerModelNG::SetEdgeAlign(const CalendarEdgeAlign& alignType, const DimensionOffset& offset)
{
    ACE_UPDATE_LAYOUT_PROPERTY(CalendarPickerLayoutProperty, DialogAlignType, alignType);
    ACE_UPDATE_LAYOUT_PROPERTY(CalendarPickerLayoutProperty, DialogOffset, offset);
}

void CalendarPickerModelNG::SetTextStyle(const PickerTextStyle& textStyle)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    RefPtr<CalendarTheme> calendarTheme = pipeline->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);
    if (textStyle.fontSize.has_value() && textStyle.fontSize->IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(CalendarPickerLayoutProperty, FontSize, textStyle.fontSize.value());
    } else {
        ACE_UPDATE_LAYOUT_PROPERTY(CalendarPickerLayoutProperty, FontSize, calendarTheme->GetEntryFontSize());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(
        CalendarPickerLayoutProperty, Color,textStyle.textColor.value_or(calendarTheme->GetEntryFontColor()));
    ACE_UPDATE_LAYOUT_PROPERTY(CalendarPickerLayoutProperty, Weight, textStyle.fontWeight.value_or(FontWeight::NORMAL));
}

void CalendarPickerModelNG::SetOnChange(SelectedChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<CalendarPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChange));
}

void CalendarPickerModelNG::SetChangeEvent(SelectedChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<CalendarPickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(onChange));
}
} // namespace OHOS::Ace::NG
