/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/jsview/models/view_abstract_model_impl.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_view.h"
#include "core/interfaces/native/node/calendar_picker_modifier.h"
#include "bridge/declarative_frontend/jsview/models/calendar_picker_model_impl.h"
#include "frameworks/core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"

#ifndef CROSS_PLATFORM
namespace OHOS::Ace {
Framework::CalendarPickerModelImpl* GetCalendarPickerImpl()
{
    static Framework::CalendarPickerModelImpl instance;
    return &instance;
}

namespace {
Framework::ViewAbstractModelImpl* GetViewAbstractModelImpl()
{
    static Framework::ViewAbstractModelImpl instance;
    return &instance;
}
} // namespace
} // namespace OHOS::Ace
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_12 = 12;
constexpr int DATE_SIZE = 3;
const bool DEFAULT_MARK_TODAY = false;
thread_local std::string g_strValue;
constexpr int TEXT_STYLE_FONT_INFO_SIZE = 2;
constexpr int TEXT_STYLE_FONT_SIZE_INDEX = 0;
constexpr int TEXT_STYLE_FONT_WEIGHT_INDEX = 1;
const char DEFAULT_DELIMITER = '|';
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

void SetStartDate(ArkUINodeHandle node, uint32_t year, uint32_t month, uint32_t day)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalendarPickerModelNG::SetStartDateWithNode(frameNode, year, month, day);
}

ArkUI_CharPtr GetStartDate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    auto pickDate = CalendarPickerModelNG::GetStartDateWithNode(frameNode);
    if (pickDate.ToDays() <= 0) {
        return "";
    }
    g_strValue = std::to_string(static_cast<uint32_t>(pickDate.GetYear())) + "-";
    g_strValue = g_strValue + std::to_string(static_cast<uint32_t>(pickDate.GetMonth())) + "-";
    g_strValue = g_strValue + std::to_string(static_cast<uint32_t>(pickDate.GetDay()));
    return g_strValue.c_str();
}

void ResetStartDate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PickerDate defaultDate;
    CalendarPickerModelNG::SetStartDateWithNode(
        frameNode, defaultDate.GetYear(), defaultDate.GetMonth(), defaultDate.GetDay());
}

void SetEndDate(ArkUINodeHandle node, uint32_t year, uint32_t month, uint32_t day)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalendarPickerModelNG::SetEndDateWithNode(frameNode, year, month, day);
}

ArkUI_CharPtr GetEndDate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    auto pickDate = CalendarPickerModelNG::GetEndDateWithNode(frameNode);
    if (pickDate.ToDays() <= 0) {
        return "";
    }
    g_strValue = std::to_string(static_cast<uint32_t>(pickDate.GetYear())) + "-";
    g_strValue = g_strValue + std::to_string(static_cast<uint32_t>(pickDate.GetMonth())) + "-";
    g_strValue = g_strValue + std::to_string(static_cast<uint32_t>(pickDate.GetDay()));
    return g_strValue.c_str();
}

void ResetEndDate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PickerDate defaultDate;
    CalendarPickerModelNG::SetEndDateWithNode(
        frameNode, defaultDate.GetYear(), defaultDate.GetMonth(), defaultDate.GetDay());
}

void SetTextStyleWithWeightEnumBase(ArkUINodeHandle node, uint32_t color, float fontSize, int32_t fontSizeUnit,
    int32_t fontWeight, bool isNeedGetResObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PickerTextStyle textStyle;
    textStyle.textColor = Color(color);
    if (SystemProperties::ConfigChangePerform() && isNeedGetResObj) {
        textStyle.textColorSetByUser = true;
        RefPtr<ResourceObject> colorResObj;
        Color result = Color(color);
        ResourceParseUtils::CompleteResourceObjectFromColor(colorResObj, result, frameNode->GetTag());
        if (colorResObj) {
            textStyle.textColor = result;
            textStyle.textColorResObj = colorResObj;
        }
    }

    Dimension fontSizeDimension(fontSize, DimensionUnit::FP);
    textStyle.fontSize = fontSizeDimension;
    textStyle.fontWeight = static_cast<Ace::FontWeight>(fontWeight);
    CalendarPickerModelNG::SetTextStyle(frameNode, textStyle);
}

void SetTextStyleWithWeightEnum(
    ArkUINodeHandle node, uint32_t color, float fontSize, int32_t fontSizeUnit, int32_t fontWeight)
{
    SetTextStyleWithWeightEnumBase(node, color, fontSize, fontSizeUnit, fontWeight, false);
}

void SetTextStyleWithWeightEnumPtr(
    ArkUINodeHandle node, uint32_t color, float fontSize, int32_t fontSizeUnit, int32_t fontWeight, bool isDefaultColor)
{
    SetTextStyleWithWeightEnumBase(node, color, fontSize, fontSizeUnit, fontWeight, !isDefaultColor);
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

void SetCalendarPickerTextStyleResObj(NG::PickerTextStyle& textStyle, void* fontSizeRawPtr, void* textColorRawPtr)
{
    auto* fontSizePtr = reinterpret_cast<ResourceObject*>(fontSizeRawPtr);
    if (fontSizePtr) {
        textStyle.fontSizeResObj = AceType::Claim(fontSizePtr);
    }

    auto* textColorPtr = reinterpret_cast<ResourceObject*>(textColorRawPtr);
    if (textColorPtr) {
        textStyle.textColorResObj = AceType::Claim(textColorPtr);
    }
}

void SetJSTextStyle(ArkUINodeHandle node, void* textStyleResPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PickerTextStyle textStyle;
    if (textStyleResPtr) {
        textStyle = *reinterpret_cast<NG::PickerTextStyle*>(textStyleResPtr);
    }
    CalendarPickerModelNG::SetTextStyle(frameNode, textStyle);
}

void SetTextStyleWithResObj(ArkUINodeHandle node, const struct ArkUIPickerTextStyleStruct* textStyleStruct)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(textStyleStruct->fontInfo);
    StringUtils::StringSplitter(fontValues, DEFAULT_DELIMITER, res);
    if (res.size() != TEXT_STYLE_FONT_INFO_SIZE) {
        return;
    }
    CalcDimension fontSizeDimension =
        StringUtils::StringToCalcDimension(res[TEXT_STYLE_FONT_SIZE_INDEX], false, DimensionUnit::FP);
    if (fontSizeDimension.Unit() == DimensionUnit::PERCENT) {
        textStyle.fontSize = Dimension(-1);
    } else {
        textStyle.fontSize = fontSizeDimension;
    }
    textStyle.fontWeight = StringUtils::StringToFontWeight(res[TEXT_STYLE_FONT_WEIGHT_INDEX], FontWeight::NORMAL);
    textStyle.textColor = Color(textStyleStruct->textColor);
    textStyle.textColorSetByUser = textStyleStruct->textColorSetByUser;

    SetCalendarPickerTextStyleResObj(textStyle, textStyleStruct->fontSizeRawPtr, textStyleStruct->textColorRawPtr);
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

void SetEdgeAlignWithResObj(ArkUINodeHandle node, const struct ArkUIPickerEdgeAlignStruct* edgeAlignStruct)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    Dimension dx = Dimension(edgeAlignStruct->dxValue, static_cast<OHOS::Ace::DimensionUnit>(edgeAlignStruct->dxUnit));
    Dimension dy = Dimension(edgeAlignStruct->dyValue, static_cast<OHOS::Ace::DimensionUnit>(edgeAlignStruct->dyUnit));
    NG::CalendarEdgeAlign align = static_cast<NG::CalendarEdgeAlign>(edgeAlignStruct->alignType);
    DimensionOffset offset = DimensionOffset(dx, dy);

    auto* dxPtr = reinterpret_cast<ResourceObject*>(edgeAlignStruct->dxRawPtr);
    auto dxResObj = AceType::Claim(dxPtr);
    auto* dyPtr = reinterpret_cast<ResourceObject*>(edgeAlignStruct->dyRawPtr);
    auto dyResObj = AceType::Claim(dyPtr);
    if (dxResObj || dyResObj) {
        std::vector<RefPtr<ResourceObject>> resArray = { dxResObj, dyResObj };
        CalendarPickerModelNG::ParseEdgeAlignResObj(frameNode, resArray);
    }

    CalendarPickerModelNG::SetEdgeAlign(frameNode, align, offset);
}

void SetJsEdgeAlign(ArkUINodeHandle node, void* offset, int32_t alignType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::CalendarEdgeAlign align = static_cast<NG::CalendarEdgeAlign>(alignType);
    if (offset) {
        DimensionOffset* offsetPtr = reinterpret_cast<DimensionOffset*>(offset);
        CalendarPickerModelNG::SetEdgeAlign(frameNode, align, *offsetPtr);
        return;
    }
    DimensionOffset defaultOffset;
    CalendarPickerModelNG::SetEdgeAlign(frameNode, align, defaultOffset);
}

void ParseJSEdgeAlignResObjArray(ArkUINodeHandle node, void* edgeAlignResObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<RefPtr<ResourceObject>> resArray;
    if (edgeAlignResObj) {
        resArray = *reinterpret_cast<std::vector<RefPtr<ResourceObject>>*>(edgeAlignResObj);
    }
    CalendarPickerModelNG::ParseEdgeAlignResObj(frameNode, resArray);
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
    CalendarPickerModelNG::CalendarPickerRemoveResObj(frameNode, "CalendarPicker.EdgeAlign");
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
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension radius = Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
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

void JSCreateCalendarPicker(void* createParams)
{
    NG::CalendarSettingData* settingData = static_cast<NG::CalendarSettingData*>(createParams);
    CalendarPickerModelNG::CreateCalendarPicker(*settingData);
}

ArkUINodeHandle JSCreateCalendarPickerById(ArkUI_Int32 nodeId)
{
    auto frameNode = CalendarPickerModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

bool IsPaddingValid(
    NG::PaddingProperty& paddings, CalcLength topDim, CalcLength rightDim, CalcLength bottomDim, CalcLength leftDim)
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

void SetJSPaddingProperty(ArkUINodeHandle node, void* padding)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PaddingProperty paddingProp;
    if (padding) {
        paddingProp = *(reinterpret_cast<NG::PaddingProperty*>(padding));
    }
    CalendarPickerModelNG::SetPadding(frameNode, paddingProp);
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

void SetCalendarPickerMarkToday(ArkUINodeHandle node, ArkUI_Bool isMarkToday)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalendarPickerModelNG::SetMarkToday(frameNode, isMarkToday);
}

void ResetCalendarPickerMarkToday(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalendarPickerModelNG::SetMarkToday(frameNode, DEFAULT_MARK_TODAY);
}

ArkUI_Bool GetCalendarPickerMarkToday(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, DEFAULT_MARK_TODAY);
    auto isMarkToday = CalendarPickerModelNG::GetMarkToday(frameNode);
    return isMarkToday;
}

bool IsValidDate(uint32_t year, uint32_t month, uint32_t day)
{
    if (year <= 0) {
        return false;
    }
    if (month < NUM_1 || month > NUM_12) {
        return false;
    }
    uint32_t daysInMonth[] = { 31, PickerDate::IsLeapYear(year) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (day < 1 || day > daysInMonth[month - 1]) {
        return false;
    }
    return true;
}

PickerDate ParseDateFromString(const std::string& dateStr)
{
    std::vector<std::string> dateVec;
    StringUtils::StringSplitter(dateStr, '-', dateVec);
    PickerDate date;
    if (dateVec.size() != DATE_SIZE) {
        return date;
    }
    auto year = StringUtils::StringToInt(dateVec[NUM_0].c_str());
    auto month = StringUtils::StringToInt(dateVec[NUM_1].c_str());
    auto day = StringUtils::StringToInt(dateVec[NUM_2].c_str());
    if (!IsValidDate(year, month, day)) {
        return date;
    }
    date.SetYear(year);
    date.SetMonth(month);
    date.SetDay(day);
    return date;
}

void SetCalendarPickerDisabledDateRange(ArkUINodeHandle node, ArkUI_CharPtr disabledDateRangeStr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> dateStrVector;
    StringUtils::StringSplitter(std::string(disabledDateRangeStr), ',', dateStrVector);
    std::vector<std::pair<PickerDate, PickerDate>> disabledDateRange;
    for (size_t i = 0; i + 1 < dateStrVector.size(); i += 2) { // 2 pair size
        std::pair<PickerDate, PickerDate> pickerDateRange;
        auto start = ParseDateFromString(dateStrVector[i]);
        auto end = ParseDateFromString(dateStrVector[i + 1]);
        if (start.GetYear() == 0 || end.GetYear() == 0 || end < start) {
            continue;
        }
        pickerDateRange.first = start;
        pickerDateRange.second = end;
        disabledDateRange.emplace_back(pickerDateRange);
    }
    PickerDate::SortAndMergeDisabledDateRange(disabledDateRange);
    CalendarPickerModelNG::SetDisabledDateRange(frameNode, disabledDateRange);
}

void ResetCalendarPickerDisabledDateRange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::pair<PickerDate, PickerDate>> disabledDateRange;
    CalendarPickerModelNG::SetDisabledDateRange(frameNode, disabledDateRange);
}

ArkUI_CharPtr GetCalendarPickerDisabledDateRange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");

    g_strValue = CalendarPickerModelNG::GetDisabledDateRange(frameNode);
    return g_strValue.c_str();
}

void SetCalendarPickerOnChangeExt(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange = reinterpret_cast<std::function<void(const std::string&)>*>(callback);
    CalendarPickerModelNG::SetOnChangeWithNode(frameNode, std::move(*onChange));
}

void ResetCalendarPickerOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalendarPickerModelNG::SetOnChangeWithNode(frameNode, nullptr);
}

ArkUINodeHandle JSShowCalendarPicker(
    void* dialogProperties, void* settingData, void* buttonInfos, void* dialogEvent, void* dialogCancelEvent)
{
    auto* dialogPropertiesPtr = reinterpret_cast<const DialogProperties*>(dialogProperties);
    auto* settingDataPtr = reinterpret_cast<const CalendarSettingData*>(settingData);
    auto* buttonInfosPtr = reinterpret_cast<const std::vector<ButtonInfo>*>(buttonInfos);
    auto* dialogEventPtr = reinterpret_cast<std::map<std::string, NG::DialogEvent>*>(dialogEvent);
    auto* dialogCancelEventPtr = reinterpret_cast<std::map<std::string, NG::DialogGestureEvent>*>(dialogCancelEvent);

    auto frameNode = CalendarDialogView::Show(*dialogPropertiesPtr, *settingDataPtr, *buttonInfosPtr,
        std::move(*dialogEventPtr), std::move(*dialogCancelEventPtr));
    CHECK_NULL_RETURN(frameNode, nullptr);
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void JSCalendarPickerRemoveResObj(ArkUINodeHandle node, const ArkUI_CharPtr key)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }

    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pickerPattern = frameNode->GetPattern<CalendarPickerPattern>();
    CHECK_NULL_VOID(pickerPattern);
    auto keyStr = std::string(key);
    pickerPattern->RemoveResObj(keyStr);
}

void JSResetResObj(ArkUINodeHandle node, ArkUI_CharPtr key)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    auto keyStr = std::string(key);
    pattern->RemoveResObj(keyStr);
}

void JSRemoveResObj(ArkUINodeHandle node, ArkUI_CharPtr key)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj(key);
}

void SetJSBorderColor(ArkUINodeHandle node, const uint32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color color = Color(value);
    ViewAbstract::SetBorderColor(frameNode, color);
}

void SetJSBorderColorResObj(ArkUINodeHandle node, void* colorResPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<ResourceObject> borderColorResObj;
    if (colorResPtr != nullptr) {
        borderColorResObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorResPtr));
    }
    ViewAbstract::SetBorderColor(frameNode, borderColorResObj);
}

void SetJSBorderColorProperty(ArkUINodeHandle node, void* colorProperty)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::BorderColorProperty borderColorProperty;
    if (colorProperty != nullptr) {
        borderColorProperty = *(reinterpret_cast<NG::BorderColorProperty*>(colorProperty));
    }
    ViewAbstract::SetBorderColor(frameNode, borderColorProperty);
}

void SetJSBorderWidth(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension borderWidth;
    if (static_cast<OHOS::Ace::DimensionUnit>(unit) != OHOS::Ace::DimensionUnit::INVALID) {
        borderWidth = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
        ViewAbstract::SetBorderWidth(frameNode, borderWidth);
    }
}
void SetJSBorderWidthArray(ArkUINodeHandle node, const ArkUIBorderWidthOption* values, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (length == NUM_1) {
        Dimension borderWidth;
        if (values != nullptr && values[NUM_0].hasValue &&
            static_cast<OHOS::Ace::DimensionUnit>(values[NUM_0].unit) != OHOS::Ace::DimensionUnit::INVALID) {
            borderWidth = Dimension(values[NUM_0].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_0].unit));
        }
        ViewAbstract::SetBorderWidth(frameNode, borderWidth);
    } else if (length == NUM_4) {
        std::optional<Dimension> leftDimen;
        std::optional<Dimension> rightDimen;
        std::optional<Dimension> topDimen;
        std::optional<Dimension> bottomDimen;

        if (values != nullptr) {
            if (values[NUM_0].hasValue &&
                static_cast<OHOS::Ace::DimensionUnit>(values[NUM_0].unit) != OHOS::Ace::DimensionUnit::INVALID) {
                leftDimen = Dimension(values[NUM_0].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_0].unit));
            }
            if (values[NUM_1].hasValue &&
                static_cast<OHOS::Ace::DimensionUnit>(values[NUM_1].unit) != OHOS::Ace::DimensionUnit::INVALID) {
                rightDimen = Dimension(values[NUM_1].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_1].unit));
            }
            if (values[NUM_2].hasValue &&
                static_cast<OHOS::Ace::DimensionUnit>(values[NUM_2].unit) != OHOS::Ace::DimensionUnit::INVALID) {
                topDimen = Dimension(values[NUM_2].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_2].unit));
            }
            if (values[NUM_3].hasValue &&
                static_cast<OHOS::Ace::DimensionUnit>(values[NUM_3].unit) != OHOS::Ace::DimensionUnit::INVALID) {
                bottomDimen = Dimension(values[NUM_3].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_3].unit));
            }
        }
        ViewAbstract::SetBorderWidth(frameNode, leftDimen, rightDimen, topDimen, bottomDimen);
    }
}

void SetJSBorderWidthResObj(ArkUINodeHandle node, void* widthResObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<ResourceObject> borderWidthResObj;
    if (widthResObj != nullptr) {
        borderWidthResObj = AceType::Claim(reinterpret_cast<ResourceObject*>(widthResObj));
    }
    ViewAbstract::SetBorderWidth(frameNode, borderWidthResObj);
}

void SetJSBorderWidthProperty(ArkUINodeHandle node, void* widthPropertyPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::BorderWidthProperty borderWidth;
    if (widthPropertyPtr != nullptr) {
        borderWidth = *(reinterpret_cast<NG::BorderWidthProperty*>(widthPropertyPtr));
    }
    ViewAbstract::SetBorderWidth(frameNode, borderWidth);
}

void SetJSBorderWidthIsLocalized(
    ArkUINodeHandle node, const ArkUIBorderWidthOption* values, ArkUI_Int32 length, bool isLocalized)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (!isLocalized) {
        return;
    }

    std::optional<CalcDimension> left;
    std::optional<CalcDimension> right;
    std::optional<CalcDimension> top;
    std::optional<CalcDimension> bottom;
    if (values != nullptr) {
        if (values[NUM_0].hasValue &&
            static_cast<OHOS::Ace::DimensionUnit>(values[NUM_0].unit) != OHOS::Ace::DimensionUnit::INVALID) {
            left = Dimension(values[NUM_0].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_0].unit));
        }
        if (values[NUM_1].hasValue &&
            static_cast<OHOS::Ace::DimensionUnit>(values[NUM_1].unit) != OHOS::Ace::DimensionUnit::INVALID) {
            right = Dimension(values[NUM_1].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_1].unit));
        }
        if (values[NUM_2].hasValue &&
            static_cast<OHOS::Ace::DimensionUnit>(values[NUM_2].unit) != OHOS::Ace::DimensionUnit::INVALID) {
            top = Dimension(values[NUM_2].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_2].unit));
        }
        if (values[NUM_3].hasValue &&
            static_cast<OHOS::Ace::DimensionUnit>(values[NUM_3].unit) != OHOS::Ace::DimensionUnit::INVALID) {
            bottom = Dimension(values[NUM_3].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_3].unit));
        }
    }
    NG::BorderWidthProperty borderWidth {
        .topDimen = top, .bottomDimen = bottom, .startDimen = left, .endDimen = right, .multiValued = true
    };
    ViewAbstract::SetBorderWidth(frameNode, borderWidth);
}

void SetJSHeight(ArkUINodeHandle node, const ArkUI_Float32 value, const ArkUI_Int32 unit, const std::string calcValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (static_cast<OHOS::Ace::DimensionUnit>(unit) == DimensionUnit::CALC) {
        ViewAbstract::SetHeight(frameNode, NG::CalcLength(calcValue));
    } else {
        auto height = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
        ViewAbstract::SetHeight(frameNode, NG::CalcLength(height));
    }
}

void SetJSHeightResObj(ArkUINodeHandle node, void* heightResPtr)
{
    RefPtr<ResourceObject> heightResObj;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (heightResPtr != nullptr) {
        heightResObj = AceType::Claim(reinterpret_cast<ResourceObject*>(heightResPtr));
    }
    ViewAbstract::SetHeight(frameNode, heightResObj);
}

void SetJSBorderRadius(ArkUINodeHandle node, const ArkUI_Float32 value, const ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension borderRadius;

    if (static_cast<OHOS::Ace::DimensionUnit>(unit) != OHOS::Ace::DimensionUnit::INVALID) {
        borderRadius = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    }
    ViewAbstract::SetBorderRadius(frameNode, borderRadius);
}

void SetJSBorderRadiusArray(ArkUINodeHandle node, const ArkUIBorderRadiusOption* values, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (length == NUM_1) {
        Dimension borderRadius;
        if (values != nullptr && values[NUM_0].hasValue &&
            static_cast<OHOS::Ace::DimensionUnit>(values[NUM_0].unit) != OHOS::Ace::DimensionUnit::INVALID) {
            borderRadius = Dimension(values[NUM_0].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_0].unit));
        }
        ViewAbstract::SetBorderRadius(frameNode, borderRadius);
    } else if (length == NUM_4) {
        std::optional<Dimension> topLeft;
        std::optional<Dimension> topRight;
        std::optional<Dimension> bottomLeft;
        std::optional<Dimension> bottomRight;
        if (values != nullptr) {
            if (values[NUM_0].hasValue &&
                static_cast<OHOS::Ace::DimensionUnit>(values[NUM_0].unit) != OHOS::Ace::DimensionUnit::INVALID) {
                topLeft = Dimension(values[NUM_0].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_0].unit));
            }
            if (values[NUM_1].hasValue &&
                static_cast<OHOS::Ace::DimensionUnit>(values[NUM_1].unit) != OHOS::Ace::DimensionUnit::INVALID) {
                topRight = Dimension(values[NUM_1].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_1].unit));
            }
            if (values[NUM_2].hasValue &&
                static_cast<OHOS::Ace::DimensionUnit>(values[NUM_2].unit) != OHOS::Ace::DimensionUnit::INVALID) {
                bottomLeft = Dimension(values[NUM_2].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_2].unit));
            }
            if (values[NUM_3].hasValue &&
                static_cast<OHOS::Ace::DimensionUnit>(values[NUM_3].unit) != OHOS::Ace::DimensionUnit::INVALID) {
                bottomRight = Dimension(values[NUM_3].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_3].unit));
            }
        }
        ViewAbstract::SetBorderRadius(frameNode, topLeft, topRight, bottomLeft, bottomRight);
    }
}

void SetJSBorderRadiusResObj(ArkUINodeHandle node, void* radiusResPtrs)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<ResourceObject> radiusResObj;
    if (radiusResPtrs != nullptr) {
        radiusResObj = AceType::Claim(reinterpret_cast<ResourceObject*>(radiusResPtrs));
    }
    ViewAbstract::SetBorderRadius(frameNode, radiusResObj);
}

void SetJSBorderRadiusProperty(ArkUINodeHandle node, void* radiusProperty)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::BorderRadiusProperty borderRadiusProperty;
    if (radiusProperty != nullptr) {
        borderRadiusProperty = *(reinterpret_cast<BorderRadiusProperty*>(radiusProperty));
    }
    ViewAbstract::SetBorderRadius(frameNode, borderRadiusProperty);
}

BorderStyle ConvertBorderStyle(int32_t value)
{
    auto style = static_cast<BorderStyle>(value);
    if (style < BorderStyle::SOLID || style > BorderStyle::NONE) {
        style = BorderStyle::SOLID;
    }
    return style;
}

void SetJsBorderStyle(ArkUINodeHandle node, const ArkUI_Int32 style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBorderStyle(frameNode, ConvertBorderStyle(style));
}

void SetJSBorderStyleArray(ArkUINodeHandle node, const ArkUI_Int32* styles, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length == NUM_1) {
        ViewAbstract::SetBorderStyle(frameNode, ConvertBorderStyle(styles[NUM_0]));
        return;
    }
    if (length == NUM_4) {
        NG::BorderStyleProperty borderStyles;
        borderStyles.styleLeft = ConvertBorderStyle(styles[NUM_0]);
        borderStyles.styleRight = ConvertBorderStyle(styles[NUM_1]);
        borderStyles.styleTop = ConvertBorderStyle(styles[NUM_2]);
        borderStyles.styleBottom = ConvertBorderStyle(styles[NUM_3]);
        borderStyles.multiValued = true;
        ViewAbstract::SetBorderStyle(frameNode, borderStyles);
    }
}

void SetJSRenderStrategy(ArkUINodeHandle node, ArkUI_Int32 renderStrategy)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetRenderStrategy(frameNode, static_cast<RenderStrategy>(renderStrategy));
}

void ClearJSWidthOrHeight(ArkUINodeHandle node, bool isWidth)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, isWidth);
}

void ClearJSHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalendarPickerModelNG::ClearJSHeight(frameNode);
}

void UpdateOnlyLayoutPolicyProperty(ArkUINodeHandle node, ArkUI_Int32 layoutPolicy, bool isWidth)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto policy = static_cast<LayoutCalPolicy>(layoutPolicy);
    ViewAbstract::UpdateOnlyLayoutPolicyProperty(frameNode, policy, isWidth);
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

void SetCalendarPickerOnChangeExtraParam(ArkUINodeHandle node, void* extraParam)
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
        SendArkUISyncEvent(&event);
    };
    CalendarPickerModelNG::SetOnChangeWithNode(frameNode, std::move(onEvent));
}

#ifndef CROSS_PLATFORM
void SetJSBorderColorImpl(ArkUINodeHandle node, const uint32_t value)
{
    GetViewAbstractModelImpl()->SetBorderColor(Color(value));
}

void SetJSBorderRadiusImpl(ArkUINodeHandle node, const ArkUI_Float32 value, const ArkUI_Int32 unit)
{
    Dimension radiusValue  = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    GetViewAbstractModelImpl()->SetBorderRadius(radiusValue);
}

void SetJSBorderRadiusArrayImpl(ArkUINodeHandle node, const ArkUIBorderRadiusOption* values, ArkUI_Int32 length)
{
    std::optional<Dimension> topLeft;
    std::optional<Dimension> topRight;
    std::optional<Dimension> bottomLeft;
    std::optional<Dimension> bottomRight;
    if (length == NUM_4) {
        if (values != nullptr) {
            if (values[NUM_0].hasValue &&
                static_cast<OHOS::Ace::DimensionUnit>(values[NUM_0].unit) != OHOS::Ace::DimensionUnit::INVALID) {
                topLeft =
                    Dimension(values[NUM_0].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_0].unit));
            }

            if (values[NUM_1].hasValue &&
                static_cast<OHOS::Ace::DimensionUnit>(values[NUM_1].unit) != OHOS::Ace::DimensionUnit::INVALID) {
                topRight =
                    Dimension(values[NUM_1].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_1].unit));
            }

            if (values[NUM_2].hasValue &&
                static_cast<OHOS::Ace::DimensionUnit>(values[NUM_2].unit) != OHOS::Ace::DimensionUnit::INVALID) {
                bottomLeft =
                    Dimension(values[NUM_2].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_2].unit));
            }

            if (values[NUM_3].hasValue &&
                static_cast<OHOS::Ace::DimensionUnit>(values[NUM_3].unit) != OHOS::Ace::DimensionUnit::INVALID) {
                bottomRight =
                    Dimension(values[NUM_3].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_3].unit));
            }
        }
    }
    GetViewAbstractModelImpl()->SetBorderRadius(topLeft, topRight, bottomLeft, bottomRight);
}

void SetJSBorderRadiusPropertyImpl(ArkUINodeHandle node, void* radiusProperty)
{
    NG::BorderRadiusProperty borderRadiusProperty;
    if (radiusProperty != nullptr) {
        borderRadiusProperty = *(reinterpret_cast<BorderRadiusProperty*>(radiusProperty));
    }
    GetViewAbstractModelImpl()->SetBorderRadius(borderRadiusProperty);
}

void SetJsBorderStyleImpl(ArkUINodeHandle node,  const ArkUI_Int32 style)
{
    BorderStyle borderStyle = ConvertBorderStyle(style);
    GetViewAbstractModelImpl()->SetBorderStyle(borderStyle);
}

void SetJSBorderStyleArrayImpl(ArkUINodeHandle node, const ArkUI_Int32* styles, ArkUI_Int32 length)
{
    std::optional<BorderStyle> left;
    std::optional<BorderStyle> right;
    std::optional<BorderStyle> top;
    std::optional<BorderStyle> bottom;
    if (styles != nullptr && length == NUM_4) {
        if (styles[NUM_0]) {
            left = ConvertBorderStyle(styles[NUM_0]);
        }
        
        if (styles[NUM_1]) {
            right = ConvertBorderStyle(styles[NUM_1]);
        }
        
        if (styles[NUM_2]) {
            top = ConvertBorderStyle(styles[NUM_2]);
        }
        if (styles[NUM_3]) {
            bottom = ConvertBorderStyle(styles[NUM_3]);
        }
    }
    GetViewAbstractModelImpl()->SetBorderStyle(left, right, top, bottom);
}

void SetJSBorderWidthImpl(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    Dimension borderWidth;
    if (static_cast<OHOS::Ace::DimensionUnit>(unit) != OHOS::Ace::DimensionUnit::INVALID) {
        borderWidth = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    }
    GetViewAbstractModelImpl()->SetBorderWidth(borderWidth);
}

void SetJSBorderWidthArrayImpl(ArkUINodeHandle node, const ArkUIBorderWidthOption* values, ArkUI_Int32 length)
{
    std::optional<Dimension> leftDimen;
    std::optional<Dimension> rightDimen;
    std::optional<Dimension> topDimen;
    std::optional<Dimension> bottomDimen;
    if (length == NUM_4 && values != nullptr) {
        if (values[NUM_0].hasValue &&
            static_cast<OHOS::Ace::DimensionUnit>(values[NUM_0].unit) != OHOS::Ace::DimensionUnit::INVALID) {
            leftDimen = Dimension(values[NUM_0].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_0].unit));
        }

        if (values[NUM_1].hasValue &&
            static_cast<OHOS::Ace::DimensionUnit>(values[NUM_1].unit) != OHOS::Ace::DimensionUnit::INVALID) {
            rightDimen = Dimension(values[NUM_1].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_1].unit));
        }

        if (values[NUM_2].hasValue &&
            static_cast<OHOS::Ace::DimensionUnit>(values[NUM_2].unit) != OHOS::Ace::DimensionUnit::INVALID) {
            topDimen = Dimension(values[NUM_2].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_2].unit));
        }

        if (values[NUM_3].hasValue &&
            static_cast<OHOS::Ace::DimensionUnit>(values[NUM_3].unit) != OHOS::Ace::DimensionUnit::INVALID) {
            bottomDimen = Dimension(values[NUM_3].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_3].unit));
        }
    }
    GetViewAbstractModelImpl()->SetBorderWidth(leftDimen, rightDimen, topDimen, bottomDimen);
}

void SetJSBorderWidthIsLocalizedImpl(ArkUINodeHandle node, const ArkUIBorderWidthOption *values, ArkUI_Int32 length,
    bool isLocalized)
{
    std::optional<CalcDimension> left;
    std::optional<CalcDimension> right;
    std::optional<CalcDimension> top;
    std::optional<CalcDimension> bottom;
    if (values != nullptr) {
        if (values[NUM_0].hasValue &&
            static_cast<OHOS::Ace::DimensionUnit>(values[NUM_0].unit) != OHOS::Ace::DimensionUnit::INVALID) {
            left = Dimension(values[NUM_0].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_0].unit));
        }
        if (values[NUM_1].hasValue &&
            static_cast<OHOS::Ace::DimensionUnit>(values[NUM_1].unit) != OHOS::Ace::DimensionUnit::INVALID) {
            right = Dimension(values[NUM_1].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_1].unit));
        }
        if (values[NUM_2].hasValue &&
            static_cast<OHOS::Ace::DimensionUnit>(values[NUM_2].unit) != OHOS::Ace::DimensionUnit::INVALID) {
            top = Dimension(values[NUM_2].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_2].unit));
        }
        if (values[NUM_3].hasValue &&
            static_cast<OHOS::Ace::DimensionUnit>(values[NUM_3].unit) != OHOS::Ace::DimensionUnit::INVALID) {
            bottom = Dimension(values[NUM_3].value, static_cast<OHOS::Ace::DimensionUnit>(values[NUM_3].unit));
        }
    }
    GetViewAbstractModelImpl()->SetBorderWidth(left, right, top, bottom, isLocalized);
}

void SetJsEdgeAlignImpl(ArkUINodeHandle node, void* offset, int32_t alignType)
{
    NG::CalendarEdgeAlign align = static_cast<NG::CalendarEdgeAlign>(alignType);
    if (offset) {
        DimensionOffset* offsetPtr = reinterpret_cast<DimensionOffset*>(offset);
        GetCalendarPickerImpl()->SetEdgeAlign(align, *offsetPtr);
        return;
    }
    DimensionOffset defaultOffset;
    GetCalendarPickerImpl()->SetEdgeAlign(align, defaultOffset);
}

void SetJSHeightImpl(
    ArkUINodeHandle node, const ArkUI_Float32 value, const ArkUI_Int32 unit, const std::string calcValue)
{
    CalcDimension height = CalcDimension(value, static_cast<DimensionUnit>(unit));
    GetViewAbstractModelImpl()->SetHeight(height);
}

void SetJSPaddingPropertyImpl(ArkUINodeHandle node, void* padding)
{
    NG::PaddingProperty paddingProp;
    if (padding) {
        paddingProp = *(reinterpret_cast<NG::PaddingProperty*>(padding));
    }
    GetCalendarPickerImpl()->SetPadding(paddingProp);
}

void SetJSTextStyleImpl(ArkUINodeHandle node, void* textStyleResPtr)
{
    NG::PickerTextStyle textStyle;
    if (textStyleResPtr) {
        textStyle = *reinterpret_cast<NG::PickerTextStyle*>(textStyleResPtr);
    }
    GetCalendarPickerImpl()->SetTextStyle(textStyle);
}

void UpdateOnlyLayoutPolicyPropertyImpl(ArkUINodeHandle node, ArkUI_Int32 layoutPolicy, bool isWidth)
{
    auto policy = static_cast<LayoutCalPolicy>(layoutPolicy);
    GetViewAbstractModelImpl()->UpdateLayoutPolicyProperty(policy, isWidth);
}

void SetJSRenderStrategyImpl(ArkUINodeHandle node, ArkUI_Int32 renderStrategy)
{
    GetViewAbstractModelImpl()->SetRenderStrategy(static_cast<RenderStrategy>(renderStrategy));
}

void ClearJSWidthOrHeightImpl(ArkUINodeHandle node, bool isWidth)
{
    GetViewAbstractModelImpl()->ClearWidthOrHeight(isWidth);
}

void ClearJSHeightImpl(ArkUINodeHandle node)
{
    GetCalendarPickerImpl()->ClearHeight();
}
#endif

const ArkUICalendarPickerModifier* GetCalendarPickerDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUICalendarPickerModifier modifier = {
            .setHintRadius = nullptr,
            .setSelectDate = nullptr,
            .resetSelectDate = nullptr,
            .setTextStyleWithWeightEnum = nullptr,
            .setTextStyleWithWeightEnumPtr = nullptr,
            .setTextStyle = nullptr,
            .setTextStyleWithResObj = nullptr,
            .resetTextStyle = nullptr,
            .setStartDate = nullptr,
            .resetStartDate = nullptr,
            .setEndDate = nullptr,
            .resetEndDate = nullptr,
            .setCalendarPickerMarkToday = nullptr,
            .resetCalendarPickerMarkToday = nullptr,
            .setCalendarPickerDisabledDateRange = nullptr,
            .resetCalendarPickerDisabledDateRange = nullptr,
            .setEdgeAlign = nullptr,
            .setEdgeAlignWithResObj = nullptr,
            .resetEdgeAlign = nullptr,
            .setCalendarPickerPadding = nullptr,
            .resetCalendarPickerPadding = nullptr,
            .setCalendarPickerBorder = nullptr,
            .resetCalendarPickerBorder = nullptr,
            .getHintRadius = nullptr,
            .getSelectedDate = nullptr,
            .getCalendarPickerTextStyle = nullptr,
            .getStartDate = nullptr,
            .getEndDate = nullptr,
            .getCalendarPickerMarkToday = nullptr,
            .getCalendarPickerDisabledDateRange = nullptr,
            .getEdgeAlign = nullptr,
            .setCalendarPickerHeight = nullptr,
            .resetCalendarPickerHeight = nullptr,
            .setCalendarPickerBorderColor = nullptr,
            .resetCalendarPickerBorderColor = nullptr,
            .setCalendarPickerBorderRadius = nullptr,
            .resetCalendarPickerBorderRadius = nullptr,
            .resetCalendarPickerBorderWidth = nullptr,
            .setCalendarPickerOnChange = nullptr,
            .resetCalendarPickerOnChange = nullptr,
            .jsShowCalendarPicker = JSShowCalendarPicker,
            .jsCreate = JSCreateCalendarPicker,
            .jsCreateById = JSCreateCalendarPickerById,
            .jsCalendarPickerRemoveResObj = nullptr,
            .jsRemoveResObj = nullptr,
            .jSResetResObj = nullptr,
            .parseJSEdgeAlignResObjArray = nullptr,
            .setJSBorderColor = SetJSBorderColorImpl,
            .setJSBorderColorProperty = nullptr,
            .setJSBorderColorResObj = nullptr,
            .setJSBorderRadius = SetJSBorderRadiusImpl,
            .setJSBorderRadiusArray = SetJSBorderRadiusArrayImpl,
            .setJSBorderRadiusProperty = SetJSBorderRadiusPropertyImpl,
            .setJSBorderRadiusResObj = nullptr,
            .setJsBorderStyle = SetJsBorderStyleImpl,
            .setJSBorderStyleArray = SetJSBorderStyleArrayImpl,
            .setJSBorderWidth = SetJSBorderWidth,
            .setJSBorderWidthArray = SetJSBorderWidthArray,
            .setJSBorderWidthIsLocalized = SetJSBorderWidthIsLocalized,
            .setJSBorderWidthProperty = nullptr,
            .setJSBorderWidthResObj = nullptr,
            .setJsEdgeAlign = SetJsEdgeAlignImpl,
            .setJSHeight = SetJSHeightImpl,
            .setJSHeightResObj = nullptr,
            .setJSPaddingProperty = SetJSPaddingPropertyImpl,
            .setJSTextStyle = SetJSTextStyleImpl,
            .updateOnlyLayoutPolicyProperty = UpdateOnlyLayoutPolicyPropertyImpl,
            .setJSRenderStrategy = SetJSRenderStrategyImpl,
            .clearJSWidthOrHeight = ClearJSWidthOrHeightImpl,
            .clearJSHeight = ClearJSHeightImpl,
            .setCalendarPickerOnChangeExtraParam = nullptr,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#endif
    } else {
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUICalendarPickerModifier modifier = {
            .setHintRadius = SetHintRadius,
            .setSelectDate = SetSelectedDate,
            .resetSelectDate = ResetSelectedDate,
            .setTextStyleWithWeightEnum = SetTextStyleWithWeightEnum,
            .setTextStyleWithWeightEnumPtr = SetTextStyleWithWeightEnumPtr,
            .setTextStyle = SetTextStyle,
            .setTextStyleWithResObj = SetTextStyleWithResObj,
            .resetTextStyle = ResetTextStyle,
            .setStartDate = SetStartDate,
            .resetStartDate = ResetStartDate,
            .setEndDate = SetEndDate,
            .resetEndDate = ResetEndDate,
            .setCalendarPickerMarkToday = SetCalendarPickerMarkToday,
            .resetCalendarPickerMarkToday = ResetCalendarPickerMarkToday,
            .setCalendarPickerDisabledDateRange = SetCalendarPickerDisabledDateRange,
            .resetCalendarPickerDisabledDateRange = ResetCalendarPickerDisabledDateRange,
            .setEdgeAlign = SetEdgeAlign,
            .setEdgeAlignWithResObj = SetEdgeAlignWithResObj,
            .resetEdgeAlign = ResetEdgeAlign,
            .setCalendarPickerPadding = SetCalendarPickerPadding,
            .resetCalendarPickerPadding = ResetCalendarPickerPadding,
            .setCalendarPickerBorder = SetCalendarPickerBorder,
            .resetCalendarPickerBorder = ResetCalendarPickerBorder,
            .getHintRadius = GetHintRadius,
            .getSelectedDate = GetSelectedDate,
            .getCalendarPickerTextStyle = GetTextStyle,
            .getStartDate = GetStartDate,
            .getEndDate = GetEndDate,
            .getCalendarPickerMarkToday = GetCalendarPickerMarkToday,
            .getCalendarPickerDisabledDateRange = GetCalendarPickerDisabledDateRange,
            .getEdgeAlign = GetEdgeAlign,
            .setCalendarPickerHeight = SetCalendarPickerHeight,
            .resetCalendarPickerHeight = ResetCalendarPickerHeight,
            .setCalendarPickerBorderColor = SetCalendarPickerBorderColor,
            .resetCalendarPickerBorderColor = ResetCalendarPickerBorderColor,
            .setCalendarPickerBorderRadius = SetCalendarPickerBorderRadius,
            .resetCalendarPickerBorderRadius = ResetCalendarPickerBorderRadius,
            .resetCalendarPickerBorderWidth = ResetCalendarPickerBorderWidth,
            .setCalendarPickerOnChange = SetCalendarPickerOnChangeExt,
            .resetCalendarPickerOnChange = ResetCalendarPickerOnChange,
            .jsShowCalendarPicker = JSShowCalendarPicker,
            .jsCreate = JSCreateCalendarPicker,
            .jsCreateById = JSCreateCalendarPickerById,
            .jsCalendarPickerRemoveResObj = JSCalendarPickerRemoveResObj,
            .jsRemoveResObj = JSRemoveResObj,
            .jSResetResObj = JSResetResObj,
            .parseJSEdgeAlignResObjArray = ParseJSEdgeAlignResObjArray,
            .setJSBorderColor = SetJSBorderColor,
            .setJSBorderColorProperty = SetJSBorderColorProperty,
            .setJSBorderColorResObj = SetJSBorderColorResObj,
            .setJSBorderRadius = SetJSBorderRadius,
            .setJSBorderRadiusArray = SetJSBorderRadiusArray,
            .setJSBorderRadiusProperty = SetJSBorderRadiusProperty,
            .setJSBorderRadiusResObj = SetJSBorderRadiusResObj,
            .setJsBorderStyle = SetJsBorderStyle,
            .setJSBorderStyleArray = SetJSBorderStyleArray,
            .setJSBorderWidth = SetJSBorderWidth,
            .setJSBorderWidthArray = SetJSBorderWidthArray,
            .setJSBorderWidthIsLocalized = SetJSBorderWidthIsLocalized,
            .setJSBorderWidthProperty = SetJSBorderWidthProperty,
            .setJSBorderWidthResObj = SetJSBorderWidthResObj,
            .setJsEdgeAlign = SetJsEdgeAlign,
            .setJSHeight = SetJSHeight,
            .setJSHeightResObj = SetJSHeightResObj,
            .setJSPaddingProperty = SetJSPaddingProperty,
            .setJSTextStyle = SetJSTextStyle,
            .updateOnlyLayoutPolicyProperty = UpdateOnlyLayoutPolicyProperty,
            .setJSRenderStrategy = SetJSRenderStrategy,
            .clearJSWidthOrHeight = ClearJSWidthOrHeight,
            .clearJSHeight = ClearJSHeight,
            .setCalendarPickerOnChangeExtraParam = SetCalendarPickerOnChangeExtraParam,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
    }
}

const CJUICalendarPickerModifier* GetCJUICalendarPickerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUICalendarPickerModifier modifier = {
        .setHintRadius = SetHintRadius,
        .setSelectDate = SetSelectedDate,
        .resetSelectDate = ResetSelectedDate,
        .setTextStyleWithWeightEnum = SetTextStyleWithWeightEnum,
        .setTextStyle = SetTextStyle,
        .resetTextStyle = ResetTextStyle,
        .setStartDate = SetStartDate,
        .resetStartDate = ResetStartDate,
        .setEndDate = SetEndDate,
        .resetEndDate = ResetEndDate,
        .setCalendarPickerMarkToday = SetCalendarPickerMarkToday,
        .resetCalendarPickerMarkToday = ResetCalendarPickerMarkToday,
        .setCalendarPickerDisabledDateRange = SetCalendarPickerDisabledDateRange,
        .resetCalendarPickerDisabledDateRange = ResetCalendarPickerDisabledDateRange,
        .setEdgeAlign = SetEdgeAlign,
        .resetEdgeAlign = ResetEdgeAlign,
        .setCalendarPickerPadding = SetCalendarPickerPadding,
        .resetCalendarPickerPadding = ResetCalendarPickerPadding,
        .setCalendarPickerBorder = SetCalendarPickerBorder,
        .resetCalendarPickerBorder = ResetCalendarPickerBorder,
        .getHintRadius = GetHintRadius,
        .getSelectedDate = GetSelectedDate,
        .getCalendarPickerTextStyle = GetTextStyle,
        .getStartDate = GetStartDate,
        .getEndDate = GetEndDate,
        .getCalendarPickerMarkToday = GetCalendarPickerMarkToday,
        .getCalendarPickerDisabledDateRange = GetCalendarPickerDisabledDateRange,
        .getEdgeAlign = GetEdgeAlign,
        .setCalendarPickerHeight = SetCalendarPickerHeight,
        .resetCalendarPickerHeight = ResetCalendarPickerHeight,
        .setCalendarPickerBorderColor = SetCalendarPickerBorderColor,
        .resetCalendarPickerBorderColor = ResetCalendarPickerBorderColor,
        .setCalendarPickerBorderRadius = SetCalendarPickerBorderRadius,
        .resetCalendarPickerBorderRadius = ResetCalendarPickerBorderRadius,
        .resetCalendarPickerBorderWidth = ResetCalendarPickerBorderWidth,
        .jsShowCalendarPicker = JSShowCalendarPicker,
        .jsCreate = JSCreateCalendarPicker,
        .jsCreateById = JSCreateCalendarPickerById,
        .jsCalendarPickerRemoveResObj = JSCalendarPickerRemoveResObj,
        .jsRemoveResObj = JSRemoveResObj,
        .jSResetResObj = JSResetResObj,
        .parseJSEdgeAlignResObjArray = ParseJSEdgeAlignResObjArray,
        .setJSBorderColor = SetJSBorderColor,
        .setJSBorderColorProperty = SetJSBorderColorProperty,
        .setJSBorderColorResObj = SetJSBorderColorResObj,
        .setJSBorderRadius = SetJSBorderRadius,
        .setJSBorderRadiusArray = SetJSBorderRadiusArray,
        .setJSBorderRadiusProperty = SetJSBorderRadiusProperty,
        .setJSBorderRadiusResObj = SetJSBorderRadiusResObj,
        .setJsBorderStyle = SetJsBorderStyle,
        .setJSBorderStyleArray = SetJSBorderStyleArray,
        .setJSBorderWidth = SetJSBorderWidth,
        .setJSBorderWidthArray = SetJSBorderWidthArray,
        .setJSBorderWidthIsLocalized = SetJSBorderWidthIsLocalized,
        .setJSBorderWidthProperty = SetJSBorderWidthProperty,
        .setJSBorderWidthResObj = SetJSBorderWidthResObj,
        .setJsEdgeAlign = SetJsEdgeAlign,
        .setJSHeight = SetJSHeight,
        .setJSHeightResObj = SetJSHeightResObj,
        .setJSPaddingProperty = SetJSPaddingProperty,
        .setJSTextStyle = SetJSTextStyle,
        .updateOnlyLayoutPolicyProperty = UpdateOnlyLayoutPolicyProperty,
        .setJSRenderStrategy = SetJSRenderStrategy,
        .clearJSWidthOrHeight = ClearJSWidthOrHeight,
        .clearJSHeight = ClearJSHeight,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace OHOS::Ace::NG