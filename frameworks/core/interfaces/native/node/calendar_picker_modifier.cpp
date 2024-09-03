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

#include "core/interfaces/native/node/calendar_picker_modifier.h"

#include "core/components_ng/base/view_abstract.h"
#include "frameworks/core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
} // namespace
void SetHintRadius(ArkUINodeHandle node, float radius, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension radiusDimension(radius, static_cast<DimensionUnit>(unit));
    CalendarPickerModelNG::SetHintRadiusWithNode(frameNode, radiusDimension);
}

float GetHintRadius(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0.0f);
    return CalendarPickerModelNG::GetHintRadius(frameNode).Value();
}

void SetSelectedDate(ArkUINodeHandle node, uint32_t year, uint32_t month, uint32_t day)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalendarPickerModelNG::SetSelectDateWithNode(frameNode, year, month, day);
}

ArkUISelectedDateType GetSelectedDate(ArkUINodeHandle node)
{
    ArkUISelectedDateType selectedDate = { 0, 0, 0 };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, selectedDate);
    auto pickDate = CalendarPickerModelNG::GetSelectDateWithNode(frameNode);
    selectedDate.year = static_cast<uint32_t>(pickDate.GetYear());
    selectedDate.month = static_cast<uint32_t>(pickDate.GetMonth());
    selectedDate.day = static_cast<uint32_t>(pickDate.GetDay());
    return selectedDate;
}

void ResetSelectedDate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto currentDate = PickerDate::Current();
    CalendarPickerModelNG::SetSelectDateWithNode(
        frameNode, currentDate.GetYear(), currentDate.GetMonth(), currentDate.GetDay());
}

void SetTextStyleWithWeightEnum(
    ArkUINodeHandle node, uint32_t color, float fontSize, int32_t fontSizeUnit, int32_t fontWeight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PickerTextStyle textStyle;
    textStyle.textColor = Color(color);
    Dimension fontSizeDimension(fontSize, DimensionUnit::FP);
    textStyle.fontSize = fontSizeDimension;
    textStyle.fontWeight = static_cast<Ace::FontWeight>(fontWeight);
    CalendarPickerModelNG::SetTextStyle(frameNode, textStyle);
}

void SetTextStyle(ArkUINodeHandle node, uint32_t color, const char* fontSize, const char* fontweight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PickerTextStyle textStyle;
    textStyle.textColor = Color(color);
    CalcDimension fontSizeDimension =
        StringUtils::StringToCalcDimension(std::string(fontSize), false, DimensionUnit::FP);
    if (fontSizeDimension.Unit() == DimensionUnit::PERCENT) {
        textStyle.fontSize = Dimension(-1);
    } else {
        textStyle.fontSize = fontSizeDimension;
    }
    textStyle.fontWeight = StringUtils::StringToFontWeight(fontweight, FontWeight::NORMAL);
    CalendarPickerModelNG::SetTextStyle(frameNode, textStyle);
}

ArkUICalendarTextStyleType GetTextStyle(ArkUINodeHandle node)
{
    ArkUICalendarTextStyleType textStyle = { Color::BLACK.GetValue(), 0.0f, 0 };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, textStyle);
    auto currentTextStyle = CalendarPickerModelNG::GetTextStyle(frameNode);
    textStyle.fontColor = currentTextStyle.textColor.has_value() ? currentTextStyle.textColor.value().GetValue()
                                                                        : Color::BLACK.GetValue();
    textStyle.fontSize = currentTextStyle.fontSize.has_value() ? currentTextStyle.fontSize.value().Value() : 0.0f;
    textStyle.fontWeight = currentTextStyle.fontWeight.has_value()
                                      ? static_cast<int32_t>(currentTextStyle.fontWeight.value())
                                      : static_cast<int32_t>(FontWeight::NORMAL);
    return textStyle;
}

void ResetTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    RefPtr<CalendarTheme> calendarTheme = pipeline->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);
    NG::PickerTextStyle textStyle;
    textStyle.fontSize = calendarTheme->GetEntryFontSize();
    textStyle.textColor = calendarTheme->GetEntryFontColor();
    textStyle.fontWeight = FontWeight::NORMAL;
    CalendarPickerModelNG::SetTextStyle(frameNode, textStyle);
}

void SetEdgeAlign(ArkUINodeHandle node, const ArkUI_Float32* values, const int* units, int32_t size, int32_t alignType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (size < NUM_2) {
        return;
    }

    Dimension dx = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    Dimension dy = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    NG::CalendarEdgeAlign align = static_cast<NG::CalendarEdgeAlign>(alignType);
    DimensionOffset offset = DimensionOffset(dx, dy);
    CalendarPickerModelNG::SetEdgeAlign(frameNode, align, offset);
}

ArkUIEdgeAlignType GetEdgeAlign(ArkUINodeHandle node)
{
    ArkUIEdgeAlignType align = { 0, 0.0f, 0.0f };
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, align);
    auto offset = CalendarPickerModelNG::GetEdgeOffset(frameNode);
    align.alignType = static_cast<int32_t>(CalendarPickerModelNG::GetEdgeAlignType(frameNode));
    align.offsetX = offset.GetX().ConvertToVp();
    align.offsetY = offset.GetY().ConvertToVp();
    return align;
}

void ResetEdgeAlign(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::CalendarEdgeAlign alignType = NG::CalendarEdgeAlign::EDGE_ALIGN_END;
    DimensionOffset offset;
    CalendarPickerModelNG::SetEdgeAlign(frameNode, alignType, offset);
}

void SetCalendarPickerHeight(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DimensionUnit unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    Dimension height = Dimension(value, unitEnum);
    if (height.IsValid()) {
        ViewAbstract::SetHeight(frameNode, CalcLength(height));
    } else {
        CalendarPickerModelNG::ClearHeight(frameNode);
    }
}

void ResetCalendarPickerHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalendarPickerModelNG::ClearHeight(frameNode);
}

void SetCalendarPickerBorderColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBorderColor(frameNode, Color(color));
}

void ResetCalendarPickerBorderColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalendarPickerModelNG::ClearBorderColor(frameNode);
}

void SetCalendarPickerBorderRadius(ArkUINodeHandle node, const ArkUI_Float32 value, const ArkUI_Int32 unit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension radius =
        Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
    ViewAbstract::SetBorderRadius(frameNode, radius);
}

void ResetCalendarPickerBorderRadius(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalendarPickerModelNG::ClearBorderRadius(frameNode);
}

void ResetCalendarPickerBorderWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalendarPickerModelNG::ClearBorderWidth(frameNode);
}

bool IsPaddingValid(NG::PaddingProperty& paddings, CalcLength topDim,
    CalcLength rightDim, CalcLength bottomDim, CalcLength leftDim)
{
    bool hasValue = false;
    if (topDim.IsValid()) {
        paddings.top = std::optional<CalcLength>(topDim);
        hasValue = true;
    }
    if (bottomDim.IsValid()) {
        paddings.bottom = std::optional<CalcLength>(bottomDim);
        hasValue = true;
    }
    if (leftDim.IsValid()) {
        paddings.left = std::optional<CalcLength>(leftDim);
        hasValue = true;
    }
    if (rightDim.IsValid()) {
        paddings.right = std::optional<CalcLength>(rightDim);
        hasValue = true;
    }
    return hasValue;
}

void SetCalendarPickerPadding(ArkUINodeHandle node, const struct ArkUISizeType* top, const struct ArkUISizeType* right,
    const struct ArkUISizeType* bottom, const struct ArkUISizeType* left)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcLength topDim;
    CalcLength rightDim;
    CalcLength bottomDim;
    CalcLength leftDim;
    if (top->string != nullptr) {
        topDim = CalcLength(top->string);
    } else {
        topDim = CalcLength(top->value, static_cast<DimensionUnit>(top->unit));
    }
    if (right->string != nullptr) {
        rightDim = CalcLength(right->string);
    } else {
        rightDim = CalcLength(right->value, static_cast<DimensionUnit>(right->unit));
    }
    if (bottom->string != nullptr) {
        bottomDim = CalcLength(bottom->string);
    } else {
        bottomDim = CalcLength(bottom->value, static_cast<DimensionUnit>(bottom->unit));
    }
    if (left->string != nullptr) {
        leftDim = CalcLength(left->string);
    } else {
        leftDim = CalcLength(left->value, static_cast<DimensionUnit>(left->unit));
    }
    NG::PaddingProperty paddings;
    paddings.top = std::optional<CalcLength>();
    paddings.bottom = std::optional<CalcLength>();
    paddings.left = std::optional<CalcLength>();
    paddings.right = std::optional<CalcLength>();
    
    if (IsPaddingValid(paddings, topDim, rightDim, bottomDim, leftDim)) {
        CalendarPickerModelNG::SetPadding(frameNode, paddings);
    } else {
        CalendarPickerModelNG::ClearPadding(frameNode);
    }
}

void ResetCalendarPickerPadding(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalendarPickerModelNG::ClearPadding(frameNode);
}

void SetCalendarPickerBorder(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    ViewAbstract::SetBorderColor(frameNode, Color(color));
}

void ResetCalendarPickerBorder(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    RefPtr<CalendarTheme> calendarTheme = pipeline->GetTheme<CalendarTheme>();
    CHECK_NULL_VOID(calendarTheme);
    ViewAbstract::SetBorderWidth(frameNode, calendarTheme->GetEntryBorderWidth());
    ViewAbstract::SetBorderColor(frameNode, calendarTheme->GetEntryBorderColor());
    ViewAbstract::SetBorderRadius(frameNode, calendarTheme->GetEntryBorderRadius());
    ViewAbstract::SetBorderStyle(frameNode, BorderStyle::SOLID);
}

namespace NodeModifier {
const ArkUICalendarPickerModifier* GetCalendarPickerModifier()
{
    static const ArkUICalendarPickerModifier modifier = { SetHintRadius, SetSelectedDate, ResetSelectedDate,
        SetTextStyleWithWeightEnum, SetTextStyle, ResetTextStyle, SetEdgeAlign, ResetEdgeAlign,
        SetCalendarPickerPadding, ResetCalendarPickerPadding, SetCalendarPickerBorder, ResetCalendarPickerBorder,
        GetHintRadius, GetSelectedDate, GetTextStyle, GetEdgeAlign, SetCalendarPickerHeight, ResetCalendarPickerHeight,
        SetCalendarPickerBorderColor, ResetCalendarPickerBorderColor, SetCalendarPickerBorderRadius,
        ResetCalendarPickerBorderRadius, ResetCalendarPickerBorderWidth };

    return &modifier;
}

const CJUICalendarPickerModifier* GetCJUICalendarPickerModifier()
{
    static const CJUICalendarPickerModifier modifier = { SetHintRadius, SetSelectedDate, ResetSelectedDate,
        SetTextStyleWithWeightEnum, SetTextStyle, ResetTextStyle, SetEdgeAlign, ResetEdgeAlign,
        SetCalendarPickerPadding, ResetCalendarPickerPadding, SetCalendarPickerBorder, ResetCalendarPickerBorder,
        GetHintRadius, GetSelectedDate, GetTextStyle, GetEdgeAlign, SetCalendarPickerHeight, ResetCalendarPickerHeight,
        SetCalendarPickerBorderColor, ResetCalendarPickerBorderColor, SetCalendarPickerBorderRadius,
        ResetCalendarPickerBorderRadius, ResetCalendarPickerBorderWidth };

    return &modifier;
}

void ParseDateByStr(const std::string& date, ArkUISelectedDateType& selectedDate)
{
    auto json = JsonUtil::ParseJsonString(date);
    if (!json || json->IsNull()) {
        return;
    }
    auto year = json->GetValue("year");
    if (year && year->IsNumber()) {
        uint32_t yearVal = year->GetInt() > 0 ? static_cast<uint32_t>(year->GetInt()) : 0;
        selectedDate.year = yearVal; // local date start from 1900
    }
    auto month = json->GetValue("month");
    if (month && month->IsNumber()) {
        uint32_t monthVal = month->GetInt() > 0 ? static_cast<uint32_t>(month->GetInt()) : 0;
        selectedDate.month = monthVal;
    }
    auto day = json->GetValue("day");
    if (day && day->IsNumber()) {
        uint32_t dayVal = day->GetInt() > 0 ? static_cast<uint32_t>(day->GetInt()) : 0;
        selectedDate.day = dayVal;
    }
}

void SetCalendarPickerOnChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const std::string& dateStr) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        ArkUISelectedDateType selectedDate;
        selectedDate.year = 0;
        selectedDate.month = 0;
        selectedDate.day = 0;
        ParseDateByStr(dateStr, selectedDate);
        event.componentAsyncEvent.subKind = ON_CALENDAR_PICKER_CHANGE;
        event.componentAsyncEvent.data[NUM_0].u32 = selectedDate.year;
        event.componentAsyncEvent.data[NUM_1].u32 = selectedDate.month;
        event.componentAsyncEvent.data[NUM_2].u32 = selectedDate.day;
        SendArkUIAsyncEvent(&event);
    };
    CalendarPickerModelNG::SetOnChangeWithNode(frameNode, std::move(onEvent));
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
