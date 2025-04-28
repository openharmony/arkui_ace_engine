/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/calendar_picker/calendar_picker_model_static.h"

#include "core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_pattern.h"

namespace OHOS::Ace::NG {
void CalendarPickerModelStatic::SetCalendarData(FrameNode* pickerNode, const std::optional<CalendarSettingData>& data)
{
    CHECK_NULL_VOID(pickerNode);
    if (data) {
        CalendarPickerModelStatic::InitCalendarPicker(pickerNode, data.value());
    } else {
        CalendarSettingData emptyData;
        CalendarPickerModelStatic::InitCalendarPicker(pickerNode, emptyData);
    }
}

void CalendarPickerModelStatic::InitCalendarPicker(FrameNode* pickerNode, const CalendarSettingData& settingData)
{
    CHECK_NULL_VOID(pickerNode);
    auto pickerPattern = pickerNode->GetPattern<CalendarPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
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
    pickerNode->GetRenderContext()->SetClipToBounds(true);
    pickerNode->GetRenderContext()->UpdateClipEdge(true);
    CHECK_NULL_VOID(pickerNode->GetLayoutProperty<LinearLayoutProperty>());
    pickerNode->GetLayoutProperty<LinearLayoutProperty>()->UpdateMainAxisAlign(FlexAlign::FLEX_START);
    pickerNode->GetLayoutProperty<LinearLayoutProperty>()->UpdateCrossAxisAlign(FlexAlign::CENTER);
    pickerNode->GetLayoutProperty<LinearLayoutProperty>()->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    RefPtr<FrameNode> pickerNodeRef = AceType::Claim<FrameNode>(pickerNode);
    CalendarPickerModelNG::LayoutPicker(pickerPattern, pickerNodeRef, settingData, theme);

    pickerNode->MarkModifyDone();
}

void CalendarPickerModelStatic::SetTextStyle(FrameNode* frameNode, const std::optional<PickerTextStyle>& textStyle)
{
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    RefPtr<CalendarTheme> calendarTheme = pipeline->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);
    if (textStyle.has_value()) {
        auto style = textStyle.value();
        if (style.fontSize.has_value() && style.fontSize->IsValid()) {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(CalendarPickerLayoutProperty, FontSize, style.fontSize.value(), frameNode);
        } else {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(
                CalendarPickerLayoutProperty, FontSize, calendarTheme->GetEntryFontSize(), frameNode);
        }
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(CalendarPickerLayoutProperty, Color,
            style.textColor.value_or(calendarTheme->GetEntryFontColor()), frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            CalendarPickerLayoutProperty, Weight, style.fontWeight.value_or(FontWeight::NORMAL), frameNode);
    } else {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(CalendarPickerLayoutProperty, FontSize,
            calendarTheme->GetEntryFontSize(), frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(CalendarPickerLayoutProperty, Color,
            calendarTheme->GetEntryFontColor(), frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(CalendarPickerLayoutProperty, Weight,
            FontWeight::NORMAL, frameNode);
    }
}

void CalendarPickerModelStatic::SetEdgeAlign(
    FrameNode* frameNode, const std::optional<CalendarEdgeAlign>& alignType,
    const std::optional<DimensionOffset>& offset)
{
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);
    if (offset) {
        pickerPattern->SetCalendarDialogOffset(offset.value());
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(CalendarPickerLayoutProperty, DialogOffset, offset.value(), frameNode);
    } else {
        pickerPattern->SetCalendarDialogOffset(DimensionOffset());
        ACE_RESET_NODE_LAYOUT_PROPERTY(CalendarPickerLayoutProperty, DialogOffset, frameNode);
    }
    if (alignType) {
        pickerPattern->SetCalendarEdgeAlign(alignType.value());
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(CalendarPickerLayoutProperty, DialogAlignType, alignType.value(), frameNode);
    } else {
        pickerPattern->SetCalendarEdgeAlign(CalendarEdgeAlign::EDGE_ALIGN_END);
        ACE_RESET_NODE_LAYOUT_PROPERTY(CalendarPickerLayoutProperty, DialogAlignType, frameNode);
    }
}

void CalendarPickerModelStatic::SetMarkToday(FrameNode* frameNode, const std::optional<bool>& isMarkToday)
{
    CHECK_NULL_VOID(frameNode);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);
    pickerPattern->SetMarkToday(isMarkToday.value_or(false));
}
} // namespace OHOS::Ace::NG
  
