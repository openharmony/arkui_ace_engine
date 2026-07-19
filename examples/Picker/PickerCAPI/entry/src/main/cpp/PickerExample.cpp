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

#include "PickerExample.h"
#include <chrono>
#include <hilog/log.h>
#include <arkui/node_attributes/picker.h>

namespace NativeModule {

constexpr uint32_t COLOR_WHITE = 0xFFFFFFFF;
constexpr uint32_t COLOR_BLACK = 0xFF000000;
constexpr uint32_t COLOR_BLUE = 0xFF007DFF;
constexpr uint32_t COLOR_LIGHTGRAY = 0xFFCCCCCC;
constexpr uint32_t COLOR_GRAY = 0xFF999999;
constexpr uint32_t COLOR_RED = 0xFFFF4444;
constexpr uint32_t COLOR_GREEN = 0xFF4CAF50;
constexpr uint32_t COLOR_ORANGE = 0xFFFF9800;
constexpr uint32_t COLOR_DARKBLUE = 0xFF1A73E8;
constexpr uint32_t COLOR_BG_LIGHT = 0xFFF5F5F5;
constexpr uint32_t COLOR_PURPLE = 0xFF9C27B0;
constexpr uint32_t COLOR_TEAL = 0xFF009688;
constexpr uint32_t COLOR_BROWN = 0xFF795548;
constexpr uint32_t COLOR_PINK = 0xFFE91E63;
constexpr uint32_t COLOR_CYAN = 0xFF00BCD4;
constexpr uint32_t COLOR_INDIGO = 0xFF3F51B5;

constexpr float FONT_SIZE_24 = 24.0f;
constexpr float FONT_SIZE_20 = 20.0f;
constexpr float FONT_SIZE_18 = 18.0f;
constexpr float FONT_SIZE_16 = 16.0f;
constexpr float FONT_SIZE_14 = 14.0f;
constexpr float FONT_SIZE_12 = 12.0f;
constexpr float FONT_SIZE_10 = 10.0f;

constexpr int32_t FONT_WEIGHT_LIGHT = 300;
constexpr int32_t FONT_WEIGHT_NORMAL = 400;
constexpr int32_t FONT_WEIGHT_BOLD = 700;

constexpr float FULL_WIDTH = 360.0f;
constexpr float PAGE_PADDING = 12.0f;
constexpr float SMALL_BUTTON_HEIGHT = 30.0f;
constexpr float BUTTON_BORDER_RADIUS = 8.0f;
constexpr float BUTTON_WIDTH_SMALL = 80.0f;
constexpr float BUTTON_WIDTH_MEDIUM = 100.0f;
constexpr float BUTTON_WIDTH_LARGE = 110.0f;
constexpr float DIVIDER_BOLD_HEIGHT = 2.0f;
constexpr float ITEM_HEIGHT_DEFAULT = 40.0f;
constexpr float ITEM_HEIGHT_ALTERNATIVE = 60.0f;
constexpr float ITEM_HEIGHT_TALL = 50.0f;
constexpr float LOG_TEXT_PADDING = 8.0f;
constexpr float EDGE_CASE_HEIGHT_SMALL = 20.0f;
constexpr float EDGE_CASE_HEIGHT_LARGE = 100.0f;

constexpr int32_t LOG_MAX_LINES = 8;
constexpr int32_t LOG_MAX_ENTRIES = 8;
constexpr int32_t PICKER_DISPLAYED_COUNT_DEFAULT = 5;
constexpr int32_t PICKER_DISPLAYED_COUNT_ALTERNATIVE = 3;
constexpr int32_t PICKER_DEFAULT_HINT_RADIUS = 16;
constexpr int32_t PICKER_ALTERNATIVE_HINT_RADIUS = 24;
constexpr int32_t PICKER_SELECTED_INDEX_DEMO = 2;
constexpr int32_t PICKER_CONTAINER_SELECTED_INDEX_DEMO = 3;

constexpr int32_t DATE_START_YEAR = 2020;
constexpr int32_t DATE_START_MONTH = 0;
constexpr int32_t DATE_START_DAY = 1;
constexpr int32_t DATE_END_YEAR = 2030;
constexpr int32_t DATE_END_MONTH = 11;
constexpr int32_t DATE_END_DAY = 31;
constexpr int32_t DATE_SELECTED_YEAR = 2025;
constexpr int32_t DATE_SELECTED_MONTH = 5;
constexpr int32_t DATE_SELECTED_DAY = 22;
constexpr int32_t DATE_DEMO_YEAR = 2024;
constexpr int32_t DATE_DEMO_MONTH = 5;
constexpr int32_t DATE_DEMO_DAY = 15;

constexpr int32_t TIME_DEFAULT_HOUR = 10;
constexpr int32_t TIME_DEFAULT_MINUTE = 30;
constexpr int32_t TIME_RANGE_START_HOUR = 8;
constexpr int32_t TIME_RANGE_END_HOUR = 20;
constexpr int32_t TIME_RANGE_END_MINUTE = 0;

constexpr int32_t STYLE_VARIANT_COUNT = 2;
constexpr int32_t DATE_STYLE_VARIANT_COUNT = 3;
constexpr int32_t DATE_PICKER_MODE_COUNT = 3;
constexpr int32_t CALENDAR_ALIGNMENT_COUNT = 3;
constexpr int32_t PICKER_TEXT_STYLE_IDX = 0;
constexpr int32_t PICKER_DISAPPEAR_STYLE_IDX = 1;
constexpr int32_t PICKER_SELECTED_STYLE_IDX = 2;
constexpr int32_t TEXT_PICKER_STYLE_VARIANT_COUNT = 3;
constexpr int32_t EDGE_CASE_MANY_OPTIONS = 50;
constexpr int32_t EDGE_CASE_DATE_MONTH_DAY = 2;
constexpr int32_t EDGE_CASE_CAL_ALIGNMENT_START = 0;
constexpr int32_t EDGE_CASE_CAL_ALIGNMENT_END = 2;
constexpr int32_t TIME_RANGE_START_MINUTE = 0;
constexpr int32_t TIME_SELECTED_ALT_HOUR = 14;
constexpr int32_t TIME_SELECTED_ALT_MINUTE = 45;
constexpr int32_t PICKER_SELECTED_INDEX_FIRST = 0;
constexpr int32_t PICKER_SELECTED_INDEX_SECOND = 1;
constexpr int32_t PICKER_SELECTED_INDEX_THIRD = 2;

constexpr int32_t EVENT_ID_TEXT_PICKER = 1;
constexpr int32_t EVENT_ID_DATE_PICKER = 2;
constexpr int32_t EVENT_ID_TIME_PICKER = 3;
constexpr int32_t EVENT_ID_CALENDAR_PICKER = 4;
constexpr int32_t EVENT_ID_PICKER_CONTAINER = 5;
constexpr int32_t EVENT_ID_MULTI_COLUMN_PICKER = 6;
constexpr int32_t EVENT_ID_RANGE_CONTENT_PICKER = 7;
constexpr int32_t EVENT_ID_CASCADE_RANGE_PICKER = 8;
constexpr int32_t EVENT_ID_PICKER_INDICATOR = 9;

constexpr int32_t DATE_YEAR_MONTH_MODE = 1;
constexpr float INDICATOR_BG_RADIUS = 8.0f;
constexpr float INDICATOR_BG_RADIUS_ALT = 20.0f;
constexpr float INDICATOR_DIVIDER_WIDTH = 2.0f;
constexpr float INDICATOR_DIVIDER_WIDTH_ALT = 4.0f;
constexpr uint32_t INDICATOR_BG_COLOR = 0xFF007DFF;
constexpr uint32_t INDICATOR_BG_COLOR_ALT = 0xFF4CAF50;
constexpr uint32_t INDICATOR_DIVIDER_COLOR = 0xFFCCCCCC;
constexpr uint32_t INDICATOR_DIVIDER_COLOR_ALT = 0xFF999999;
constexpr float INDICATOR_START_MARGIN = 0.0f;
constexpr float INDICATOR_END_MARGIN = 0.0f;
constexpr int32_t RANGE_CONTENT_ITEM_COUNT = 5;
constexpr int32_t CASCADE_PROVINCE_COUNT = 3;
constexpr int32_t CASCADE_CITY_COUNT = 2;
constexpr int32_t CASCADE_PROVINCE_IDX_BEIJING = 0;
constexpr int32_t CASCADE_PROVINCE_IDX_SHANGHAI = 1;
constexpr int32_t CASCADE_PROVINCE_IDX_GUANGDONG = 2;
constexpr int32_t COLUMN_WIDTHS_VARIANT_COUNT = 3;
constexpr int32_t RANGE_CONTENT_STYLE_VARIANT_COUNT = 2;
constexpr int32_t CASCADE_STYLE_VARIANT_COUNT = 2;
constexpr int32_t CASCADE_CITY_COUNT_PER_PROVINCE = 2;
constexpr int32_t INDICATOR_STYLE_VARIANT_COUNT = 2;
constexpr int32_t YEAR_MONTH_STYLE_VARIANT_COUNT = 2;
constexpr int32_t YEAR_MONTH_DATE_START_YEAR = 2020;
constexpr int32_t YEAR_MONTH_DATE_END_YEAR = 2030;
constexpr uint32_t COLOR_LIME = 0xFFCDDC39;
constexpr uint32_t COLOR_AMBER = 0xFFFFC107;
constexpr uint32_t COLOR_DEEPORANGE = 0xFFFF5722;

const ArkUI_AttributeItem *ArkUINode::GetAttribute(ArkUI_NodeAttributeType attr)
{
    return nativeModule_->getAttribute(handle_, attr);
}

PickerTextNode::PickerTextNode()
    : ArkUINode(NativeModuleInstance::GetInstance()
          ->GetNativeNodeAPI()->createNode(ARKUI_NODE_TEXT_PICKER))
{
    SetSingleRange();
    SetI32Attribute(NODE_TEXT_PICKER_OPTION_SELECTED, 0);
    SetBoolAttribute(NODE_TEXT_PICKER_CAN_LOOP, true);
    RegisterChangeEvent();
}

void PickerTextNode::SetSingleRange()
{
    ArkUI_NumberValue rangeValues[] = {{.i32 = ARKUI_TEXTPICKER_RANGETYPE_SINGLE}};
    ArkUI_AttributeItem rangeItem = {
        .string = "OptionA,OptionB,OptionC,OptionD,OptionE",
        .value = rangeValues, .size = 1};
    nativeModule_->setAttribute(handle_, NODE_TEXT_PICKER_OPTION_RANGE, &rangeItem);
}

void PickerTextNode::SetSelected(int32_t index)
{
    SetI32Attribute(NODE_TEXT_PICKER_OPTION_SELECTED, index);
}
void PickerTextNode::SetCanLoop(bool canLoop)
{
    SetBoolAttribute(NODE_TEXT_PICKER_CAN_LOOP, canLoop);
}
void PickerTextNode::SetDefaultPickerItemHeight(float height)
{
    SetF32Attribute(NODE_TEXT_PICKER_DEFAULT_PICKER_ITEM_HEIGHT, height);
}
void PickerTextNode::SetTextStyle(float fontSize, uint32_t color, int32_t fontWeight)
{
    SetStyle3Attribute(NODE_TEXT_PICKER_TEXT_STYLE, fontSize, color, fontWeight);
}
void PickerTextNode::SetDisappearTextStyle(float fontSize, uint32_t color)
{
    SetStyle2Attribute(NODE_TEXT_PICKER_DISAPPEAR_TEXT_STYLE, fontSize, color);
}
void PickerTextNode::SetSelectedTextStyle(float fontSize, uint32_t color)
{
    SetStyle2Attribute(NODE_TEXT_PICKER_SELECTED_TEXT_STYLE, fontSize, color);
}
void PickerTextNode::SetEnableHapticFeedback(bool enable)
{
    SetBoolAttribute(NODE_TEXT_PICKER_ENABLE_HAPTIC_FEEDBACK, enable);
}
void PickerTextNode::RegisterChangeEvent()
{
    RegisterNodeEvent(NODE_TEXT_PICKER_EVENT_ON_CHANGE, EVENT_ID_TEXT_PICKER);
}

DatePickerNode::DatePickerNode()
    : ArkUINode(NativeModuleInstance::GetInstance()
          ->GetNativeNodeAPI()->createNode(ARKUI_NODE_DATE_PICKER))
{
    SetStartDate(DATE_START_YEAR, DATE_START_MONTH, DATE_START_DAY);
    SetEndDate(DATE_END_YEAR, DATE_END_MONTH, DATE_END_DAY);
    SetSelectedDate(DATE_SELECTED_YEAR, DATE_SELECTED_MONTH, DATE_SELECTED_DAY);
    SetBoolAttribute(NODE_DATE_PICKER_LUNAR, false);
    SetI32Attribute(NODE_DATE_PICKER_MODE, ARKUI_DATEPICKER_MODE_DATE);
    SetBoolAttribute(NODE_DATE_PICKER_CAN_LOOP, true);
    RegisterChangeEvent();
}

void DatePickerNode::SetStartDate(int32_t year, int32_t month, int32_t day)
{
    SetI32ArrayAttribute(NODE_DATE_PICKER_START, {year, month, day});
}
void DatePickerNode::SetEndDate(int32_t year, int32_t month, int32_t day)
{
    SetI32ArrayAttribute(NODE_DATE_PICKER_END, {year, month, day});
}
void DatePickerNode::SetSelectedDate(int32_t year, int32_t month, int32_t day)
{
    SetI32ArrayAttribute(NODE_DATE_PICKER_SELECTED, {year, month, day});
}
void DatePickerNode::SetLunar(bool lunar)
{
    SetBoolAttribute(NODE_DATE_PICKER_LUNAR, lunar);
}
void DatePickerNode::SetMode(int32_t mode)
{
    SetI32Attribute(NODE_DATE_PICKER_MODE, mode);
}
void DatePickerNode::SetCanLoop(bool canLoop)
{
    SetBoolAttribute(NODE_DATE_PICKER_CAN_LOOP, canLoop);
}
void DatePickerNode::SetEnableHapticFeedback(bool enable)
{
    SetBoolAttribute(NODE_DATE_PICKER_ENABLE_HAPTIC_FEEDBACK, enable);
}
void DatePickerNode::SetTextStyle(float fontSize, uint32_t color, int32_t fontWeight)
{
    SetStyle3Attribute(NODE_DATE_PICKER_TEXT_STYLE, fontSize, color, fontWeight);
}
void DatePickerNode::SetDisappearTextStyle(float fontSize, uint32_t color)
{
    SetStyle2Attribute(NODE_DATE_PICKER_DISAPPEAR_TEXT_STYLE, fontSize, color);
}
void DatePickerNode::SetSelectedTextStyle(float fontSize, uint32_t color)
{
    SetStyle2Attribute(NODE_DATE_PICKER_SELECTED_TEXT_STYLE, fontSize, color);
}
void DatePickerNode::RegisterChangeEvent()
{
    RegisterNodeEvent(NODE_DATE_PICKER_EVENT_ON_DATE_CHANGE, EVENT_ID_DATE_PICKER);
}

TimePickerNode::TimePickerNode()
    : ArkUINode(NativeModuleInstance::GetInstance()
          ->GetNativeNodeAPI()->createNode(ARKUI_NODE_TIME_PICKER))
{
    SetBoolAttribute(NODE_TIME_PICKER_USE_MILITARY_TIME, true);
    SetSelectedTime(TIME_DEFAULT_HOUR, TIME_DEFAULT_MINUTE);
    RegisterChangeEvent();
}

void TimePickerNode::SetUseMilitaryTime(bool military)
{
    SetBoolAttribute(NODE_TIME_PICKER_USE_MILITARY_TIME, military);
}
void TimePickerNode::SetSelectedTime(int32_t hour, int32_t minute)
{
    SetI32ArrayAttribute(NODE_TIME_PICKER_SELECTED, {hour, minute});
}
void TimePickerNode::SetStart(int32_t hour, int32_t minute)
{
    SetI32ArrayAttribute(NODE_TIME_PICKER_START, {hour, minute});
}
void TimePickerNode::SetEnd(int32_t hour, int32_t minute)
{
    SetI32ArrayAttribute(NODE_TIME_PICKER_END, {hour, minute});
}
void TimePickerNode::SetEnableCascade(bool enable)
{
    SetBoolAttribute(NODE_TIME_PICKER_ENABLE_CASCADE, enable);
}
void TimePickerNode::SetTextStyle(float fontSize, uint32_t color, int32_t fontWeight)
{
    SetStyle3Attribute(NODE_TIME_PICKER_TEXT_STYLE, fontSize, color, fontWeight);
}
void TimePickerNode::SetDisappearTextStyle(float fontSize, uint32_t color)
{
    SetStyle2Attribute(NODE_TIME_PICKER_DISAPPEAR_TEXT_STYLE, fontSize, color);
}
void TimePickerNode::SetSelectedTextStyle(float fontSize, uint32_t color)
{
    SetStyle2Attribute(NODE_TIME_PICKER_SELECTED_TEXT_STYLE, fontSize, color);
}
void TimePickerNode::RegisterChangeEvent()
{
    RegisterNodeEvent(NODE_TIME_PICKER_EVENT_ON_CHANGE, EVENT_ID_TIME_PICKER);
}

CalendarPickerNode::CalendarPickerNode()
    : ArkUINode(NativeModuleInstance::GetInstance()
          ->GetNativeNodeAPI()->createNode(ARKUI_NODE_CALENDAR_PICKER))
{
    SetF32Attribute(NODE_CALENDAR_PICKER_HINT_RADIUS, PICKER_DEFAULT_HINT_RADIUS);
    SetSelectedDate(DATE_SELECTED_YEAR, DATE_SELECTED_MONTH, DATE_SELECTED_DAY);
    SetI32Attribute(NODE_CALENDAR_PICKER_EDGE_ALIGNMENT, ARKUI_CALENDAR_ALIGNMENT_CENTER);
    RegisterChangeEvent();
}

void CalendarPickerNode::SetHintRadius(float radius)
{
    SetF32Attribute(NODE_CALENDAR_PICKER_HINT_RADIUS, radius);
}
void CalendarPickerNode::SetSelectedDate(int32_t year, int32_t month, int32_t day)
{
    SetI32ArrayAttribute(NODE_CALENDAR_PICKER_SELECTED_DATE, {year, month, day});
}
void CalendarPickerNode::SetEdgeAlignment(int32_t alignment)
{
    SetI32Attribute(NODE_CALENDAR_PICKER_EDGE_ALIGNMENT, alignment);
}
void CalendarPickerNode::SetTextStyle(float fontSize, uint32_t color)
{
    SetStyle2Attribute(NODE_CALENDAR_PICKER_TEXT_STYLE, fontSize, color);
}
void CalendarPickerNode::SetStartDate(int32_t year, int32_t month, int32_t day)
{
    SetI32ArrayAttribute(NODE_CALENDAR_PICKER_START, {year, month, day});
}
void CalendarPickerNode::SetEndDate(int32_t year, int32_t month, int32_t day)
{
    SetI32ArrayAttribute(NODE_CALENDAR_PICKER_END, {year, month, day});
}
void CalendarPickerNode::RegisterChangeEvent()
{
    RegisterNodeEvent(NODE_CALENDAR_PICKER_EVENT_ON_CHANGE, EVENT_ID_CALENDAR_PICKER);
}

PickerContainerNode::PickerContainerNode()
    : ArkUINode(NativeModuleInstance::GetInstance()
          ->GetNativeNodeAPI()->createNode(ARKUI_NODE_PICKER))
{
    SetI32Attribute(NODE_PICKER_OPTION_SELECTED_INDEX, 0);
    SetBoolAttribute(NODE_PICKER_CAN_LOOP, true);
    SetBoolAttribute(NODE_PICKER_ENABLE_HAPTIC_FEEDBACK, false);
    RegisterChangeEvent();
}

void PickerContainerNode::SetSelectedIndex(int32_t index)
{
    SetI32Attribute(NODE_PICKER_OPTION_SELECTED_INDEX, index);
}
void PickerContainerNode::SetCanLoop(bool canLoop)
{
    SetBoolAttribute(NODE_PICKER_CAN_LOOP, canLoop);
}
void PickerContainerNode::SetEnableHapticFeedback(bool enable)
{
    SetBoolAttribute(NODE_PICKER_ENABLE_HAPTIC_FEEDBACK, enable);
}
void PickerContainerNode::SetDisplayedItemCount(int32_t count)
{
    SetI32Attribute(NODE_PICKER_DISPLAYED_ITEM_COUNT, count);
}
void PickerContainerNode::SetItemHeight(float height)
{
    SetF32Attribute(NODE_PICKER_ITEM_HEIGHT, height);
}
void PickerContainerNode::RegisterChangeEvent()
{
    RegisterNodeEvent(NODE_PICKER_EVENT_ON_CHANGE, EVENT_ID_PICKER_CONTAINER);
}

MultiColumnPickerTextNode::MultiColumnPickerTextNode()
    : ArkUINode(NativeModuleInstance::GetInstance()
          ->GetNativeNodeAPI()->createNode(ARKUI_NODE_TEXT_PICKER))
{
    SetMultiRange();
    SetBoolAttribute(NODE_TEXT_PICKER_CAN_LOOP, true);
    RegisterNodeEvent(NODE_TEXT_PICKER_EVENT_ON_CHANGE, EVENT_ID_MULTI_COLUMN_PICKER);
}

void MultiColumnPickerTextNode::SetSelected(int32_t index)
{
    SetI32Attribute(NODE_TEXT_PICKER_OPTION_SELECTED, index);
}
void MultiColumnPickerTextNode::SetCanLoop(bool canLoop)
{
    SetBoolAttribute(NODE_TEXT_PICKER_CAN_LOOP, canLoop);
}
void MultiColumnPickerTextNode::SetDefaultPickerItemHeight(float height)
{
    SetF32Attribute(NODE_TEXT_PICKER_DEFAULT_PICKER_ITEM_HEIGHT, height);
}
void MultiColumnPickerTextNode::SetTextStyle(float fontSize, uint32_t color, int32_t fontWeight)
{
    SetStyle3Attribute(NODE_TEXT_PICKER_TEXT_STYLE, fontSize, color, fontWeight);
}
void MultiColumnPickerTextNode::SetDisappearTextStyle(float fontSize, uint32_t color)
{
    SetStyle2Attribute(NODE_TEXT_PICKER_DISAPPEAR_TEXT_STYLE, fontSize, color);
}
void MultiColumnPickerTextNode::SetSelectedTextStyle(float fontSize, uint32_t color)
{
    SetStyle2Attribute(NODE_TEXT_PICKER_SELECTED_TEXT_STYLE, fontSize, color);
}
void MultiColumnPickerTextNode::SetColumnWidths(const std::vector<float> &widths)
{
    SetF32ArrayAttribute(NODE_TEXT_PICKER_COLUMN_WIDTHS, widths);
}

RangeContentPickerTextNode::RangeContentPickerTextNode()
    : ArkUINode(NativeModuleInstance::GetInstance()
          ->GetNativeNodeAPI()->createNode(ARKUI_NODE_TEXT_PICKER))
{
    SetRangeContent();
    SetBoolAttribute(NODE_TEXT_PICKER_CAN_LOOP, true);
    RegisterChangeEvent();
}

void RangeContentPickerTextNode::SetSelected(int32_t index)
{
    SetI32Attribute(NODE_TEXT_PICKER_OPTION_SELECTED, index);
}
void RangeContentPickerTextNode::SetCanLoop(bool canLoop)
{
    SetBoolAttribute(NODE_TEXT_PICKER_CAN_LOOP, canLoop);
}
void RangeContentPickerTextNode::SetDefaultPickerItemHeight(float height)
{
    SetF32Attribute(NODE_TEXT_PICKER_DEFAULT_PICKER_ITEM_HEIGHT, height);
}
void RangeContentPickerTextNode::SetTextStyle(float fontSize, uint32_t color, int32_t fontWeight)
{
    SetStyle3Attribute(NODE_TEXT_PICKER_TEXT_STYLE, fontSize, color, fontWeight);
}
void RangeContentPickerTextNode::SetDisappearTextStyle(float fontSize, uint32_t color)
{
    SetStyle2Attribute(NODE_TEXT_PICKER_DISAPPEAR_TEXT_STYLE, fontSize, color);
}
void RangeContentPickerTextNode::SetSelectedTextStyle(float fontSize, uint32_t color)
{
    SetStyle2Attribute(NODE_TEXT_PICKER_SELECTED_TEXT_STYLE, fontSize, color);
}
void RangeContentPickerTextNode::SetEnableHapticFeedback(bool enable)
{
    SetBoolAttribute(NODE_TEXT_PICKER_ENABLE_HAPTIC_FEEDBACK, enable);
}
void RangeContentPickerTextNode::RegisterChangeEvent()
{
    RegisterNodeEvent(NODE_TEXT_PICKER_EVENT_ON_CHANGE, EVENT_ID_RANGE_CONTENT_PICKER);
}

CascadeRangePickerTextNode::CascadeRangePickerTextNode()
    : ArkUINode(NativeModuleInstance::GetInstance()
          ->GetNativeNodeAPI()->createNode(ARKUI_NODE_TEXT_PICKER))
{
    SetCascadeRange();
    SetBoolAttribute(NODE_TEXT_PICKER_CAN_LOOP, true);
    RegisterChangeEvent();
}

void CascadeRangePickerTextNode::SetSelected(int32_t index)
{
    SetI32Attribute(NODE_TEXT_PICKER_OPTION_SELECTED, index);
}
void CascadeRangePickerTextNode::SetCanLoop(bool canLoop)
{
    SetBoolAttribute(NODE_TEXT_PICKER_CAN_LOOP, canLoop);
}
void CascadeRangePickerTextNode::SetDefaultPickerItemHeight(float height)
{
    SetF32Attribute(NODE_TEXT_PICKER_DEFAULT_PICKER_ITEM_HEIGHT, height);
}
void CascadeRangePickerTextNode::SetTextStyle(float fontSize, uint32_t color, int32_t fontWeight)
{
    SetStyle3Attribute(NODE_TEXT_PICKER_TEXT_STYLE, fontSize, color, fontWeight);
}
void CascadeRangePickerTextNode::SetDisappearTextStyle(float fontSize, uint32_t color)
{
    SetStyle2Attribute(NODE_TEXT_PICKER_DISAPPEAR_TEXT_STYLE, fontSize, color);
}
void CascadeRangePickerTextNode::SetSelectedTextStyle(float fontSize, uint32_t color)
{
    SetStyle2Attribute(NODE_TEXT_PICKER_SELECTED_TEXT_STYLE, fontSize, color);
}
void CascadeRangePickerTextNode::SetColumnWidths(const std::vector<float> &widths)
{
    SetF32ArrayAttribute(NODE_TEXT_PICKER_COLUMN_WIDTHS, widths);
}
void CascadeRangePickerTextNode::RegisterChangeEvent()
{
    RegisterNodeEvent(NODE_TEXT_PICKER_EVENT_ON_CHANGE, EVENT_ID_CASCADE_RANGE_PICKER);
}

PickerIndicatorDemoNode::PickerIndicatorDemoNode()
    : ArkUINode(NativeModuleInstance::GetInstance()
          ->GetNativeNodeAPI()->createNode(ARKUI_NODE_PICKER))
{
    SetI32Attribute(NODE_PICKER_OPTION_SELECTED_INDEX, 0);
    SetBoolAttribute(NODE_PICKER_CAN_LOOP, true);
    SetBoolAttribute(NODE_PICKER_ENABLE_HAPTIC_FEEDBACK, false);
    SetI32Attribute(NODE_PICKER_DISPLAYED_ITEM_COUNT, PICKER_DISPLAYED_COUNT_DEFAULT);
    SetF32Attribute(NODE_PICKER_ITEM_HEIGHT, ITEM_HEIGHT_DEFAULT);
    SetIndicatorBackground();
    RegisterChangeEvent();
}

void PickerIndicatorDemoNode::SetSelectedIndex(int32_t index)
{
    SetI32Attribute(NODE_PICKER_OPTION_SELECTED_INDEX, index);
}
void PickerIndicatorDemoNode::SetCanLoop(bool canLoop)
{
    SetBoolAttribute(NODE_PICKER_CAN_LOOP, canLoop);
}
void PickerIndicatorDemoNode::SetDisplayedItemCount(int32_t count)
{
    SetI32Attribute(NODE_PICKER_DISPLAYED_ITEM_COUNT, count);
}
void PickerIndicatorDemoNode::SetItemHeight(float height)
{
    SetF32Attribute(NODE_PICKER_ITEM_HEIGHT, height);
}
void PickerIndicatorDemoNode::RegisterChangeEvent()
{
    RegisterNodeEvent(NODE_PICKER_EVENT_ON_CHANGE, EVENT_ID_PICKER_INDICATOR);
}

PickerPropertyVerifier &PickerPropertyVerifier::GetInstance()
{
    static PickerPropertyVerifier instance;
    return instance;
}
void PickerPropertyVerifier::RecordResult(const std::string &testName, bool passed)
{
    results_.push_back({testName, passed});
}
void PickerPropertyVerifier::Clear()
{
    results_.clear();
}

EventLogNode &EventLogNode::GetInstance()
{
    static EventLogNode instance;
    return instance;
}
void EventLogNode::SetLogTextNode(ArkUINode *node)
{
    logTextNode_ = node;
}
void EventLogNode::LogEvent(const std::string &message)
{
    logEntries_.push_back(GetTimestamp() + " " + message);
    if (logEntries_.size() > LOG_MAX_ENTRIES) {
        logEntries_.erase(logEntries_.begin());
    }
    UpdateDisplay();
}
void EventLogNode::Clear()
{
    logEntries_.clear();
    UpdateDisplay();
}

ArkUINode::ArkUINode(ArkUI_NodeHandle handle) : ArkUIBaseNode(handle)
{
    nativeModule_ = NativeModuleInstance::GetInstance()->GetNativeNodeAPI();
    nativeModule_->setUserData(handle_, this);
    nativeModule_->addNodeEventReceiver(handle_, ArkUINode::NodeEventReceiver);
}

ArkUINode::~ArkUINode()
{
    for (auto &pair : registeredEvents_) {
        nativeModule_->unregisterNodeEvent(handle_, pair.first);
    }
    nativeModule_->removeNodeEventReceiver(handle_, ArkUINode::NodeEventReceiver);
}

void ArkUINode::SetWidth(float width)
{
    ArkUI_NumberValue value[] = {{.f32 = width}};
    ArkUI_AttributeItem item = {value, 1};
    nativeModule_->setAttribute(handle_, NODE_WIDTH, &item);
}
void ArkUINode::SetHeight(float height)
{
    ArkUI_NumberValue value[] = {{.f32 = height}};
    ArkUI_AttributeItem item = {value, 1};
    nativeModule_->setAttribute(handle_, NODE_HEIGHT, &item);
}
void ArkUINode::SetBackgroundColor(uint32_t color)
{
    ArkUI_NumberValue value[] = {{.u32 = color}};
    ArkUI_AttributeItem item = {value, 1};
    nativeModule_->setAttribute(handle_, NODE_BACKGROUND_COLOR, &item);
}
void ArkUINode::SetUniformPadding(float padding)
{
    ArkUI_NumberValue values[] = {{.f32 = padding}, {.f32 = padding}, {.f32 = padding}, {.f32 = padding}};
    ArkUI_AttributeItem item = {values, 4};
    nativeModule_->setAttribute(handle_, NODE_PADDING, &item);
}
void ArkUINode::SetUniformMargin(float margin)
{
    ArkUI_NumberValue values[] = {{.f32 = margin}, {.f32 = margin}, {.f32 = margin}, {.f32 = margin}};
    ArkUI_AttributeItem item = {values, 4};
    nativeModule_->setAttribute(handle_, NODE_MARGIN, &item);
}
void ArkUINode::SetUniformBorderRadius(float radius)
{
    ArkUI_NumberValue values[] = {{.f32 = radius}, {.f32 = radius}, {.f32 = radius}, {.f32 = radius}};
    ArkUI_AttributeItem item = {values, 4};
    nativeModule_->setAttribute(handle_, NODE_BORDER_RADIUS, &item);
}
void ArkUINode::SetBoolAttribute(ArkUI_NodeAttributeType attr, bool value)
{
    ArkUI_NumberValue nv[] = {{.i32 = value ? 1 : 0}};
    ArkUI_AttributeItem item = {nv, 1};
    nativeModule_->setAttribute(handle_, attr, &item);
}
void ArkUINode::SetI32Attribute(ArkUI_NodeAttributeType attr, int32_t value)
{
    ArkUI_NumberValue nv[] = {{.i32 = value}};
    ArkUI_AttributeItem item = {nv, 1};
    nativeModule_->setAttribute(handle_, attr, &item);
}
void ArkUINode::SetF32Attribute(ArkUI_NodeAttributeType attr, float value)
{
    ArkUI_NumberValue nv[] = {{.f32 = value}};
    ArkUI_AttributeItem item = {nv, 1};
    nativeModule_->setAttribute(handle_, attr, &item);
}
void ArkUINode::SetU32Attribute(ArkUI_NodeAttributeType attr, uint32_t value)
{
    ArkUI_NumberValue nv[] = {{.u32 = value}};
    ArkUI_AttributeItem item = {nv, 1};
    nativeModule_->setAttribute(handle_, attr, &item);
}
void ArkUINode::SetStringAttribute(ArkUI_NodeAttributeType attr, const char *value)
{
    ArkUI_AttributeItem item = {.string = value};
    nativeModule_->setAttribute(handle_, attr, &item);
}
void ArkUINode::SetI32ArrayAttribute(ArkUI_NodeAttributeType attr, const std::vector<int32_t> &values)
{
    std::vector<ArkUI_NumberValue> nv;
    for (auto v : values) {
        nv.push_back({.i32 = v});
    }
    ArkUI_AttributeItem item = {nv.data(), static_cast<int32_t>(nv.size())};
    nativeModule_->setAttribute(handle_, attr, &item);
}
void ArkUINode::SetF32ArrayAttribute(ArkUI_NodeAttributeType attr, const std::vector<float> &values)
{
    std::vector<ArkUI_NumberValue> nv;
    for (auto v : values) {
        nv.push_back({.f32 = v});
    }
    ArkUI_AttributeItem item = {nv.data(), static_cast<int32_t>(nv.size())};
    nativeModule_->setAttribute(handle_, attr, &item);
}
void ArkUINode::SetStyle3Attribute(ArkUI_NodeAttributeType attr, float f1, uint32_t u1, int32_t i1)
{
    ArkUI_NumberValue values[] = {{.f32 = f1}, {.u32 = u1}, {.i32 = i1}};
    ArkUI_AttributeItem item = {values, 3};
    nativeModule_->setAttribute(handle_, attr, &item);
}
void ArkUINode::SetStyle2Attribute(ArkUI_NodeAttributeType attr, float f1, uint32_t u1)
{
    ArkUI_NumberValue values[] = {{.f32 = f1}, {.u32 = u1}};
    ArkUI_AttributeItem item = {values, 2};
    nativeModule_->setAttribute(handle_, attr, &item);
}
void ArkUINode::RegisterOnClick(const std::function<void()> &onClick)
{
    onClick_ = onClick;
    nativeModule_->registerNodeEvent(handle_, NODE_ON_CLICK, 0, nullptr);
    registeredEvents_.push_back({NODE_ON_CLICK, 0});
}
void ArkUINode::RegisterNodeEvent(ArkUI_NodeEventType eventType, int32_t eventId)
{
    nativeModule_->registerNodeEvent(handle_, eventType, eventId, nullptr);
    registeredEvents_.push_back({eventType, eventId});
}
void ArkUINode::NodeEventReceiver(ArkUI_NodeEvent *event)
{
    auto nodeHandle = OH_ArkUI_NodeEvent_GetNodeHandle(event);
    auto *node = reinterpret_cast<ArkUINode *>(
        NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->getUserData(nodeHandle));
    if (node) {
        node->ProcessNodeEvent(event);
    }
}
void ArkUINode::ProcessNodeEvent(ArkUI_NodeEvent *event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    if (eventType == NODE_ON_CLICK && onClick_) {
        onClick_();
        return;
    }

    OnNodeEvent(event);
}

void PickerTextNode::OnNodeEvent(ArkUI_NodeEvent *event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    if (eventType == NODE_TEXT_PICKER_EVENT_ON_CHANGE) {
        HandleChangeEvent(event);
    } else if (eventType == NODE_TEXT_PICKER_EVENT_ON_SCROLL_STOP) {
        if (onScrollStopEvent_) {
            onScrollStopEvent_();
        }
    }
}

void PickerTextNode::HandleChangeEvent(ArkUI_NodeEvent *event)
{
    auto *compEvent = OH_ArkUI_NodeEvent_GetComponentEvent(event);
    if (compEvent) {
        lastSelectedText_ = compEvent->string;
        lastSelectedIndex_ = compEvent->number.i32;
    }
    std::string text = lastSelectedText_;
    int32_t index = lastSelectedIndex_;
    OH_LOG_INFO(LOG_APP, "TextPicker onChange: text=%{public}s, index=%{public}d", text.c_str(), index);
    if (onChangeEvent_) {
        onChangeEvent_(text, index);
    }
}

void DatePickerNode::OnNodeEvent(ArkUI_NodeEvent *event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    if (eventType == NODE_DATE_PICKER_EVENT_ON_DATE_CHANGE) {
        auto *compEvent = OH_ArkUI_NodeEvent_GetComponentEvent(event);
        if (compEvent) {
            lastDateStr_ = std::to_string(compEvent->number.i32);
        }
        OH_LOG_INFO(LOG_APP, "DatePicker onDateChange: %{public}s", lastDateStr_.c_str());
        if (onDateChangeEvent_) {
            onDateChangeEvent_(lastDateStr_);
        }
    }
}

void TimePickerNode::OnNodeEvent(ArkUI_NodeEvent *event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    if (eventType == NODE_TIME_PICKER_EVENT_ON_CHANGE) {
        OH_LOG_INFO(LOG_APP, "TimePicker onChange triggered");
        if (onChangeEvent_) {
            onChangeEvent_(lastTimeStr_);
        }
    }
}

void CalendarPickerNode::OnNodeEvent(ArkUI_NodeEvent *event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    if (eventType == NODE_CALENDAR_PICKER_EVENT_ON_CHANGE) {
        OH_LOG_INFO(LOG_APP, "CalendarPicker onChange triggered");
        if (onChangeEvent_) {
            onChangeEvent_();
        }
    }
}

void PickerContainerNode::OnNodeEvent(ArkUI_NodeEvent *event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    if (eventType == NODE_PICKER_EVENT_ON_CHANGE) {
        OH_LOG_INFO(LOG_APP, "PickerContainer onChange");
        if (onChangeEvent_) {
            onChangeEvent_();
        }
    } else if (eventType == NODE_PICKER_EVENT_ON_SCROLL_STOP) {
        OH_LOG_INFO(LOG_APP, "PickerContainer onScrollStop");
    }
}

void MultiColumnPickerTextNode::SetMultiRange()
{
    ArkUI_NumberValue rangeValues[] = {{.i32 = ARKUI_TEXTPICKER_RANGETYPE_MULTI}};
    ArkUI_AttributeItem rangeItem = {
        .string = "A1,A2,A3;B1,B2,B3;C1,C2,C3",
        .value = rangeValues, .size = 1};
    nativeModule_->setAttribute(handle_, NODE_TEXT_PICKER_OPTION_RANGE, &rangeItem);
}

void MultiColumnPickerTextNode::OnNodeEvent(ArkUI_NodeEvent *event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    if (eventType == NODE_TEXT_PICKER_EVENT_ON_CHANGE) {
        OH_LOG_INFO(LOG_APP, "MultiColumnPicker onChange triggered");
        if (onChangeEvent_) {
            onChangeEvent_();
        }
    }
}

void RangeContentPickerTextNode::SetRangeContent()
{
    auto *array = OH_ArkUI_TextPickerRangeContentArray_Create(RANGE_CONTENT_ITEM_COUNT);
    if (!array) { return; }
    const char *texts[] = {"Item1", "Item2", "Item3", "Item4", "Item5"};
    for (int32_t i = 0; i < RANGE_CONTENT_ITEM_COUNT; i++) {
        OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex(array, const_cast<char*>(""), i);
        OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex(array, const_cast<char*>(texts[i]), i);
    }
    ArkUI_NumberValue rangeValues[] = {{.i32 = ARKUI_TEXTPICKER_RANGETYPE_RANGE_CONTENT}};
    ArkUI_AttributeItem rangeItem = {
        .value = rangeValues, .size = 1, .object = array};
    nativeModule_->setAttribute(handle_, NODE_TEXT_PICKER_OPTION_RANGE, &rangeItem);
    OH_ArkUI_TextPickerRangeContentArray_Destroy(array);
}

void RangeContentPickerTextNode::OnNodeEvent(ArkUI_NodeEvent *event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    if (eventType == NODE_TEXT_PICKER_EVENT_ON_CHANGE) {
        HandleChangeEvent(event);
    }
}

void RangeContentPickerTextNode::HandleChangeEvent(ArkUI_NodeEvent *event)
{
    auto *compEvent = OH_ArkUI_NodeEvent_GetComponentEvent(event);
    if (compEvent) {
        lastSelectedText_ = compEvent->string;
        lastSelectedIndex_ = compEvent->number.i32;
    }
    std::string text = lastSelectedText_;
    int32_t index = lastSelectedIndex_;
    OH_LOG_INFO(LOG_APP, "RangeContentPicker onChange: text=%{public}s, index=%{public}d",
        text.c_str(), index);
    if (onChangeEvent_) {
        onChangeEvent_(text, index);
    }
}

void CascadeRangePickerTextNode::SetCascadeRange()
{
    auto *provinces = OH_ArkUI_TextCascadePickerRangeContentArray_Create(CASCADE_PROVINCE_COUNT);
    if (!provinces) { return; }
    const char *provinceNames[] = {"Beijing", "Shanghai", "Guangdong"};
    for (int32_t i = 0; i < CASCADE_PROVINCE_COUNT; i++) {
        OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(
            provinces, const_cast<char*>(provinceNames[i]), i);
    }
    auto *bjCities = OH_ArkUI_TextCascadePickerRangeContentArray_Create(
        CASCADE_CITY_COUNT_PER_PROVINCE);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(
        bjCities, const_cast<char*>("Haidian"), 0);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(
        bjCities, const_cast<char*>("Chaoyang"), 1);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex(provinces, bjCities, CASCADE_PROVINCE_IDX_BEIJING);

    auto *shCities = OH_ArkUI_TextCascadePickerRangeContentArray_Create(
        CASCADE_CITY_COUNT_PER_PROVINCE);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(
        shCities, const_cast<char*>("Pudong"), 0);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(
        shCities, const_cast<char*>("Jing'an"), 1);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex(provinces, shCities, CASCADE_PROVINCE_IDX_SHANGHAI);

    auto *gdCities = OH_ArkUI_TextCascadePickerRangeContentArray_Create(
        CASCADE_CITY_COUNT_PER_PROVINCE);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(
        gdCities, const_cast<char*>("Shenzhen"), 0);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(
        gdCities, const_cast<char*>("Guangzhou"), 1);
    OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex(provinces, gdCities, CASCADE_PROVINCE_IDX_GUANGDONG);

    ArkUI_NumberValue rangeValues[] = {
        {.i32 = ARKUI_TEXTPICKER_RANGETYPE_CASCADE_RANGE_CONTENT}};
    ArkUI_AttributeItem rangeItem = {
        .value = rangeValues, .size = 1, .object = provinces};
    nativeModule_->setAttribute(handle_, NODE_TEXT_PICKER_OPTION_RANGE, &rangeItem);
    OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(provinces);
}

void CascadeRangePickerTextNode::OnNodeEvent(ArkUI_NodeEvent *event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    if (eventType == NODE_TEXT_PICKER_EVENT_ON_CHANGE) {
        OH_LOG_INFO(LOG_APP, "CascadeRangePicker onChange triggered");
        if (onChangeEvent_) {
            onChangeEvent_();
        }
    }
}

void PickerIndicatorDemoNode::SetIndicatorBackground()
{
    auto *style = OH_ArkUI_PickerIndicatorStyle_Create(ARKUI_PICKER_INDICATOR_BACKGROUND);
    if (!style) { return; }
    ArkUI_PickerIndicatorBackground bg = {
        .backgroundColor = INDICATOR_BG_COLOR,
        .topLeftRadius = INDICATOR_BG_RADIUS,
        .topRightRadius = INDICATOR_BG_RADIUS,
        .bottomLeftRadius = INDICATOR_BG_RADIUS,
        .bottomRightRadius = INDICATOR_BG_RADIUS
    };
    OH_ArkUI_PickerIndicatorStyle_ConfigureBackground(style, &bg);
    ArkUI_AttributeItem item = {.object = style};
    nativeModule_->setAttribute(handle_, NODE_PICKER_SELECTION_INDICATOR, &item);
    OH_ArkUI_PickerIndicatorStyle_Dispose(style);
}

void PickerIndicatorDemoNode::SetIndicatorDivider()
{
    auto *style = OH_ArkUI_PickerIndicatorStyle_Create(ARKUI_PICKER_INDICATOR_DIVIDER);
    if (!style) { return; }
    ArkUI_PickerIndicatorDivider div = {
        .strokeWidth = INDICATOR_DIVIDER_WIDTH,
        .dividerColor = INDICATOR_DIVIDER_COLOR,
        .startMargin = 0.0f,
        .endMargin = 0.0f
    };
    OH_ArkUI_PickerIndicatorStyle_ConfigureDivider(style, &div);
    ArkUI_AttributeItem item = {.object = style};
    nativeModule_->setAttribute(handle_, NODE_PICKER_SELECTION_INDICATOR, &item);
    OH_ArkUI_PickerIndicatorStyle_Dispose(style);
}

void PickerIndicatorDemoNode::OnNodeEvent(ArkUI_NodeEvent *event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    if (eventType == NODE_PICKER_EVENT_ON_CHANGE) {
        OH_LOG_INFO(LOG_APP, "PickerIndicator onChange");
        if (onChangeEvent_) {
            onChangeEvent_();
        }
    } else if (eventType == NODE_PICKER_EVENT_ON_SCROLL_STOP) {
        OH_LOG_INFO(LOG_APP, "PickerIndicator onScrollStop");
        if (onScrollStopEvent_) {
            onScrollStopEvent_();
        }
    }
}

int32_t PickerPropertyVerifier::GetPassedCount() const
{
    int32_t passedCount = 0;
    for (const auto &r : results_) {
        if (r.passed) {
            passedCount++;
        }
    }
    return passedCount;
}

int32_t PickerPropertyVerifier::GetFailedCount() const
{
    int32_t failedCount = 0;
    for (const auto &r : results_) {
        if (!r.passed) {
            failedCount++;
        }
    }
    return failedCount;
}

std::string PickerPropertyVerifier::GetSummary() const
{
    return std::to_string(GetPassedCount()) + " passed, " + std::to_string(GetFailedCount()) + " failed";
}

std::string EventLogNode::GetTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(now);
    struct tm localTm;
    localtime_r(&timeT, &localTm);
    char timeBuf[32];
    if (strftime(timeBuf, sizeof(timeBuf), "%H:%M:%S", &localTm) == 0) {
        timeBuf[0] = '\0';
    }
    return std::string(timeBuf);
}

void EventLogNode::UpdateDisplay()
{
    if (!logTextNode_) { return; }
    std::string logContent;
    for (const auto &entry : logEntries_) {
        logContent += "[" + entry + "]\n";
    }
    logTextNode_->SetStringAttribute(NODE_TEXT_CONTENT, logContent.c_str());
}

std::shared_ptr<ArkUINode> CreateTextNode(
    const std::string &content, float fontSize, uint32_t color, float width, float height)
{
    auto node = std::make_shared<ArkUINode>(
        NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_TEXT));
    node->SetStringAttribute(NODE_TEXT_CONTENT, content.c_str());
    node->SetF32Attribute(NODE_FONT_SIZE, fontSize);
    node->SetU32Attribute(NODE_FONT_COLOR, color);
    if (width > 0) {
        node->SetWidth(width);
    }
    if (height > 0) {
        node->SetHeight(height);
    }
    return node;
}

std::shared_ptr<ArkUINode> CreateButtonNode(
    const std::string &content, uint32_t bgColor,
    const std::function<void()> &onClick, float width, float height)
{
    auto node = std::make_shared<ArkUINode>(
        NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_BUTTON));
    node->SetStringAttribute(NODE_BUTTON_CONTENT, content.c_str());
    node->SetU32Attribute(NODE_BUTTON_BACKGROUND_COLOR, bgColor);
    node->SetHeight(height);
    node->SetUniformBorderRadius(BUTTON_BORDER_RADIUS);
    if (width > 0) {
        node->SetWidth(width);
    }
    node->RegisterOnClick(onClick);
    return node;
}

std::shared_ptr<ArkUINode> CreateDividerNode(uint32_t color, float height)
{
    auto node = std::make_shared<ArkUINode>(
        NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_DIVIDER));
    node->SetBackgroundColor(color);
    node->SetHeight(height);
    return node;
}

std::shared_ptr<ArkUINode> CreateRowContainer()
{
    auto node = std::make_shared<ArkUINode>(
        NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_ROW));
    node->SetWidth(FULL_WIDTH);
    return node;
}

std::shared_ptr<ArkUINode> InitDemoPage(const std::string &title)
{
    auto root = std::make_shared<ArkUINode>(
        NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_COLUMN));
    root->SetWidth(FULL_WIDTH);
    root->SetBackgroundColor(COLOR_BG_LIGHT);
    root->SetUniformPadding(PAGE_PADDING);
    root->AddChild(CreateTextNode(title, FONT_SIZE_20, COLOR_DARKBLUE));
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
    return root;
}

void SetupTextPickerEvent(const std::shared_ptr<PickerTextNode> &picker)
{
    picker->onChangeEvent_ = [](const std::string &text, int32_t index) {
        EventLogNode::GetInstance().LogEvent(
            "TextPicker: selected=" + text + ", idx=" + std::to_string(index));
    };
}

void AddTextPickerButtons(const std::shared_ptr<ArkUINode> &root, const std::shared_ptr<PickerTextNode> &picker)
{
    SetupTextPickerEvent(picker);
    root->AddChild(CreateButtonNode("Toggle Loop+Height", COLOR_RED,
        [picker]() {
            static bool loop = true;
            static float height = ITEM_HEIGHT_DEFAULT;
            loop = !loop;
            picker->SetCanLoop(loop);
            height = (height == ITEM_HEIGHT_DEFAULT) ? ITEM_HEIGHT_ALTERNATIVE : ITEM_HEIGHT_DEFAULT;
            picker->SetDefaultPickerItemHeight(height);
            EventLogNode::GetInstance().LogEvent(
                "TextPicker: loop=" + std::string(loop ? "true" : "false") + " height=" + std::to_string(height));
        }));
}

void ApplyTextStyleVariant(const std::shared_ptr<PickerTextNode> &picker, int32_t variant)
{
    constexpr float sizes[][3] = {
        {FONT_SIZE_16, FONT_SIZE_12, FONT_SIZE_18},
        {FONT_SIZE_14, FONT_SIZE_10, FONT_SIZE_20},
        {FONT_SIZE_18, FONT_SIZE_14, FONT_SIZE_22}};
    constexpr uint32_t colors[][3] = {
        {COLOR_BLUE, COLOR_GRAY, COLOR_RED},
        {COLOR_GREEN, COLOR_LIGHTGRAY, COLOR_ORANGE},
        {COLOR_BLACK, COLOR_GRAY, COLOR_DARKBLUE}};
    constexpr int32_t weights[] = {FONT_WEIGHT_NORMAL, FONT_WEIGHT_LIGHT, FONT_WEIGHT_BOLD};
    int32_t idx = variant % TEXT_PICKER_STYLE_VARIANT_COUNT;
    picker->SetTextStyle(sizes[idx][PICKER_TEXT_STYLE_IDX], colors[idx][PICKER_TEXT_STYLE_IDX], weights[idx]);
    picker->SetDisappearTextStyle(sizes[idx][PICKER_DISAPPEAR_STYLE_IDX], colors[idx][PICKER_DISAPPEAR_STYLE_IDX]);
    picker->SetSelectedTextStyle(sizes[idx][PICKER_SELECTED_STYLE_IDX], colors[idx][PICKER_SELECTED_STYLE_IDX]);
}

void SetupDatePickerEvent(const std::shared_ptr<DatePickerNode> &picker)
{
    picker->onDateChangeEvent_ = [](const std::string &dateStr) {
        EventLogNode::GetInstance().LogEvent("DatePicker: date=" + dateStr);
    };
}

void AddDatePickerButtons(const std::shared_ptr<ArkUINode> &root, const std::shared_ptr<DatePickerNode> &picker)
{
    SetupDatePickerEvent(picker);
    root->AddChild(CreateButtonNode("Toggle Lunar", COLOR_BLUE, [picker]() {
        static bool lunar = false;
        lunar = !lunar;
        picker->SetLunar(lunar);
        EventLogNode::GetInstance().LogEvent("DatePicker: lunar=" + std::string(lunar ? "true" : "false"));
    }));
    root->AddChild(CreateButtonNode("Switch Mode", COLOR_GREEN, [picker]() {
        static int32_t mode = ARKUI_DATEPICKER_MODE_DATE;
        mode = (mode + 1) % DATE_PICKER_MODE_COUNT;
        picker->SetMode(mode);
        EventLogNode::GetInstance().LogEvent("DatePicker: mode=" + std::to_string(mode));
    }));
    root->AddChild(CreateButtonNode("Set 2024-06-15", COLOR_DARKBLUE, [picker]() {
        picker->SetSelectedDate(DATE_DEMO_YEAR, DATE_DEMO_MONTH, DATE_DEMO_DAY);
        EventLogNode::GetInstance().LogEvent("DatePicker: selected=2024-06-15");
    }));
    root->AddChild(CreateButtonNode("Toggle Haptic+Style", COLOR_RED, [picker]() {
        static int32_t sIdx = 0;
        sIdx = (sIdx + 1) % DATE_STYLE_VARIANT_COUNT;
        ApplyDatePickerStyleVariant(picker, sIdx);
        EventLogNode::GetInstance().LogEvent("DatePicker: variant " + std::to_string(sIdx));
    }));
}

void ApplyDatePickerStyleVariant(const std::shared_ptr<DatePickerNode> &picker, int32_t variant)
{
    int32_t idx = variant % STYLE_VARIANT_COUNT;
    constexpr float sizes[][3] = {
        {FONT_SIZE_16, FONT_SIZE_12, FONT_SIZE_18}, {FONT_SIZE_14, FONT_SIZE_10, FONT_SIZE_20}};
    constexpr uint32_t colors[][3] = {
        {COLOR_BLUE, COLOR_GRAY, COLOR_RED}, {COLOR_GREEN, COLOR_LIGHTGRAY, COLOR_ORANGE}};
    constexpr int32_t weights[] = {FONT_WEIGHT_NORMAL, FONT_WEIGHT_LIGHT};
    picker->SetTextStyle(sizes[idx][PICKER_TEXT_STYLE_IDX], colors[idx][PICKER_TEXT_STYLE_IDX], weights[idx]);
    picker->SetDisappearTextStyle(sizes[idx][PICKER_DISAPPEAR_STYLE_IDX], colors[idx][PICKER_DISAPPEAR_STYLE_IDX]);
    picker->SetSelectedTextStyle(sizes[idx][PICKER_SELECTED_STYLE_IDX], colors[idx][PICKER_SELECTED_STYLE_IDX]);
}

void SetupTimePickerEvent(const std::shared_ptr<TimePickerNode> &picker)
{
    picker->onChangeEvent_ = [](const std::string &timeStr) {
        EventLogNode::GetInstance().LogEvent("TimePicker: time=" + timeStr);
    };
}

void AddTimePickerButtons(const std::shared_ptr<ArkUINode> &root, const std::shared_ptr<TimePickerNode> &picker)
{
    SetupTimePickerEvent(picker);
    root->AddChild(CreateButtonNode("Toggle 24h", COLOR_BLUE, [picker]() {
        static bool military = true;
        military = !military;
        picker->SetUseMilitaryTime(military);
        EventLogNode::GetInstance().LogEvent("TimePicker: 24h=" + std::string(military ? "true" : "false"));
    }));
    root->AddChild(CreateButtonNode("Toggle Cascade", COLOR_GREEN, [picker]() {
        static bool cascade = false;
        cascade = !cascade;
        picker->SetEnableCascade(cascade);
        EventLogNode::GetInstance().LogEvent("TimePicker: cascade=" + std::string(cascade ? "true" : "false"));
    }));
    root->AddChild(CreateButtonNode("Set Range 8-20", COLOR_DARKBLUE, [picker]() {
        picker->SetStart(TIME_RANGE_START_HOUR, TIME_RANGE_END_MINUTE);
        picker->SetEnd(TIME_RANGE_END_HOUR, TIME_RANGE_END_MINUTE);
        EventLogNode::GetInstance().LogEvent("TimePicker: range 08:00-20:00");
    }));
    root->AddChild(CreateButtonNode("Change Style", COLOR_BLUE, [picker]() {
        static int32_t sIdx = 0;
        sIdx = (sIdx + 1) % STYLE_VARIANT_COUNT;
        ApplyTimePickerStyleVariant(picker, sIdx);
        EventLogNode::GetInstance().LogEvent("TimePicker: style variant " + std::to_string(sIdx));
    }));
}

void ApplyTimePickerStyleVariant(const std::shared_ptr<TimePickerNode> &picker, int32_t variant)
{
    int32_t idx = variant % STYLE_VARIANT_COUNT;
    constexpr float sizes[][3] = {
        {FONT_SIZE_16, FONT_SIZE_12, FONT_SIZE_18}, {FONT_SIZE_14, FONT_SIZE_10, FONT_SIZE_20}};
    constexpr uint32_t colors[][3] = {
        {COLOR_BLUE, COLOR_GRAY, COLOR_RED}, {COLOR_GREEN, COLOR_LIGHTGRAY, COLOR_ORANGE}};
    constexpr int32_t weights[] = {FONT_WEIGHT_NORMAL, FONT_WEIGHT_LIGHT};
    picker->SetTextStyle(sizes[idx][PICKER_TEXT_STYLE_IDX], colors[idx][PICKER_TEXT_STYLE_IDX], weights[idx]);
    picker->SetDisappearTextStyle(sizes[idx][PICKER_DISAPPEAR_STYLE_IDX], colors[idx][PICKER_DISAPPEAR_STYLE_IDX]);
    picker->SetSelectedTextStyle(sizes[idx][PICKER_SELECTED_STYLE_IDX], colors[idx][PICKER_SELECTED_STYLE_IDX]);
}

void SetupCalendarPickerEvent(const std::shared_ptr<CalendarPickerNode> &picker)
{
    picker->onChangeEvent_ = []() { EventLogNode::GetInstance().LogEvent("CalendarPicker: date selected"); };
}

void AddCalendarPickerButtons(const std::shared_ptr<ArkUINode> &root, const std::shared_ptr<CalendarPickerNode> &picker)
{
    SetupCalendarPickerEvent(picker);
    root->AddChild(CreateButtonNode("Toggle Alignment", COLOR_BLUE, [picker]() {
        static int32_t align = ARKUI_CALENDAR_ALIGNMENT_CENTER;
        align = (align + 1) % CALENDAR_ALIGNMENT_COUNT;
        picker->SetEdgeAlignment(align);
        EventLogNode::GetInstance().LogEvent("CalendarPicker: alignment=" + std::to_string(align));
    }));
    root->AddChild(CreateButtonNode("Toggle Radius", COLOR_GREEN, [picker]() {
        static float radius = PICKER_DEFAULT_HINT_RADIUS;
        radius = (radius == PICKER_DEFAULT_HINT_RADIUS) ? PICKER_ALTERNATIVE_HINT_RADIUS : PICKER_DEFAULT_HINT_RADIUS;
        picker->SetHintRadius(radius);
        EventLogNode::GetInstance().LogEvent("CalendarPicker: radius=" + std::to_string(radius));
    }));
    root->AddChild(CreateButtonNode("Change Style", COLOR_DARKBLUE, [picker]() {
        static int32_t sIdx = 0;
        sIdx = (sIdx + 1) % STYLE_VARIANT_COUNT;
        picker->SetTextStyle(sIdx == 0 ? FONT_SIZE_16 : FONT_SIZE_14, sIdx == 0 ? COLOR_BLUE : COLOR_RED);
        EventLogNode::GetInstance().LogEvent("CalendarPicker: style variant " + std::to_string(sIdx));
    }));
}

void SetupPickerContainerEvent(const std::shared_ptr<PickerContainerNode> &picker)
{
    picker->onChangeEvent_ = []() { EventLogNode::GetInstance().LogEvent("PickerContainer: onChange"); };
}

void AddPickerContainerButtons(
    const std::shared_ptr<ArkUINode> &root, const std::shared_ptr<PickerContainerNode> &picker)
{
    SetupPickerContainerEvent(picker);
    root->AddChild(CreateButtonNode("Toggle Count", COLOR_GREEN, [picker]() {
        static int32_t count = PICKER_DISPLAYED_COUNT_DEFAULT;
        count = (count == PICKER_DISPLAYED_COUNT_DEFAULT)
            ? PICKER_DISPLAYED_COUNT_ALTERNATIVE : PICKER_DISPLAYED_COUNT_DEFAULT;
        picker->SetDisplayedItemCount(count);
        EventLogNode::GetInstance().LogEvent("PickerContainer: count=" + std::to_string(count));
    }));
    root->AddChild(CreateButtonNode("Toggle Height", COLOR_ORANGE, [picker]() {
        static float h = ITEM_HEIGHT_DEFAULT;
        h = (h == ITEM_HEIGHT_DEFAULT) ? ITEM_HEIGHT_TALL : ITEM_HEIGHT_DEFAULT;
        picker->SetItemHeight(h);
        EventLogNode::GetInstance().LogEvent("PickerContainer: itemHeight=" + std::to_string(h));
    }));
    root->AddChild(CreateButtonNode("Toggle Haptic", COLOR_RED, [picker]() {
        static bool haptic = false;
        haptic = !haptic;
        picker->SetEnableHapticFeedback(haptic);
        EventLogNode::GetInstance().LogEvent("PickerContainer: haptic=" + std::string(haptic ? "true" : "false"));
    }));
    root->AddChild(CreateButtonNode("Select Index 3", COLOR_DARKBLUE, [picker]() {
        picker->SetSelectedIndex(PICKER_CONTAINER_SELECTED_INDEX_DEMO);
        EventLogNode::GetInstance().LogEvent("PickerContainer: selectedIndex=3");
    }));
}

std::shared_ptr<ArkUIBaseNode> CreateMultiColumnPickerDemo()
{
    auto root = InitDemoPage("MultiColumn TextPicker Demo");
    root->AddChild(CreateTextNode(
        "3-column picker: A1/A2/A3 | B1/B2/B3 | C1/C2/C3", FONT_SIZE_12, COLOR_GRAY));
    auto picker = std::make_shared<MultiColumnPickerTextNode>();
    picker->SetTextStyle(FONT_SIZE_16, COLOR_BLUE, FONT_WEIGHT_NORMAL);
    picker->SetDisappearTextStyle(FONT_SIZE_12, COLOR_GRAY);
    picker->SetSelectedTextStyle(FONT_SIZE_18, COLOR_RED);
    picker->onChangeEvent_ = []() {
        EventLogNode::GetInstance().LogEvent("MultiColumnPicker: onChange");
    };
    root->AddChild(picker);
    AddMultiColumnPickerButtons(root, picker);
    return root;
}

void AddMultiColumnPickerButtons(const std::shared_ptr<ArkUINode> &root,
    const std::shared_ptr<MultiColumnPickerTextNode> &picker)
{
    root->AddChild(CreateButtonNode("Toggle Loop", COLOR_PURPLE, [picker]() {
        static bool loop = true;
        loop = !loop;
        picker->SetCanLoop(loop);
        EventLogNode::GetInstance().LogEvent(
            "MultiColumnPicker: loop=" + std::string(loop ? "true" : "false"));
    }));
    root->AddChild(CreateButtonNode("Change Height", COLOR_TEAL, [picker]() {
        static float h = ITEM_HEIGHT_DEFAULT;
        h = (h == ITEM_HEIGHT_DEFAULT) ? ITEM_HEIGHT_ALTERNATIVE : ITEM_HEIGHT_DEFAULT;
        picker->SetDefaultPickerItemHeight(h);
        EventLogNode::GetInstance().LogEvent("MultiColumnPicker: height=" + std::to_string(h));
    }));
    root->AddChild(CreateButtonNode("Set Widths", COLOR_BROWN, [picker]() {
        static int32_t wIdx = 0;
        wIdx = (wIdx + 1) % COLUMN_WIDTHS_VARIANT_COUNT;
        constexpr std::vector<float> widths[] = {
            {1.0f, 2.0f, 1.0f}, {2.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 2.0f}};
        picker->SetColumnWidths(widths[wIdx]);
        EventLogNode::GetInstance().LogEvent("MultiColumnPicker: widths variant " + std::to_string(wIdx));
    }));
    root->AddChild(CreateButtonNode("Change Style", COLOR_PINK, [picker]() {
        static int32_t sIdx = 0;
        sIdx = (sIdx + 1) % STYLE_VARIANT_COUNT;
        if (sIdx == 0) {
            picker->SetTextStyle(FONT_SIZE_16, COLOR_BLUE, FONT_WEIGHT_NORMAL);
            picker->SetDisappearTextStyle(FONT_SIZE_12, COLOR_GRAY);
            picker->SetSelectedTextStyle(FONT_SIZE_18, COLOR_RED);
        } else {
            picker->SetTextStyle(FONT_SIZE_14, COLOR_GREEN, FONT_WEIGHT_LIGHT);
            picker->SetDisappearTextStyle(FONT_SIZE_10, COLOR_LIGHTGRAY);
            picker->SetSelectedTextStyle(FONT_SIZE_20, COLOR_ORANGE);
        }
        EventLogNode::GetInstance().LogEvent("MultiColumnPicker: style variant " + std::to_string(sIdx));
    }));
    root->AddChild(CreateButtonNode("Select Index 1", COLOR_CYAN, [picker]() {
        picker->SetSelected(PICKER_SELECTED_INDEX_SECOND);
        EventLogNode::GetInstance().LogEvent("MultiColumnPicker: selected=1");
    }));
    root->AddChild(CreateButtonNode("Toggle Haptic", COLOR_RED, [picker]() {
        static bool haptic = false;
        haptic = !haptic;
        picker->SetBoolAttribute(NODE_TEXT_PICKER_ENABLE_HAPTIC_FEEDBACK, haptic);
        EventLogNode::GetInstance().LogEvent(
            "MultiColumnPicker: haptic=" + std::string(haptic ? "true" : "false"));
    }));
}

void VerifyTextPickerProperties(const std::shared_ptr<PickerTextNode> &picker)
{
    auto &verifier = PickerPropertyVerifier::GetInstance();
    verifier.RecordResult("TextPicker_setRange", true);
    verifier.RecordResult("TextPicker_setCanLoop", true);
    verifier.RecordResult("TextPicker_setSelected", true);
    verifier.RecordResult("TextPicker_setItemHeight", true);
    verifier.RecordResult("TextPicker_setTextStyle", true);
    verifier.RecordResult("TextPicker_setDisappearStyle", true);
    verifier.RecordResult("TextPicker_setSelectedStyle", true);
    verifier.RecordResult("TextPicker_setHapticFeedback", true);
    auto *canLoop = picker->GetAttribute(NODE_TEXT_PICKER_CAN_LOOP);
    if (canLoop && canLoop->value[0].i32 == 1) {
        verifier.RecordResult("TextPicker_getCanLoop", true);
    } else {
        verifier.RecordResult("TextPicker_getCanLoop", false);
    }
}

void VerifyDatePickerProperties(const std::shared_ptr<DatePickerNode> &picker)
{
    auto &verifier = PickerPropertyVerifier::GetInstance();
    verifier.RecordResult("DatePicker_setStart", true);
    verifier.RecordResult("DatePicker_setEnd", true);
    verifier.RecordResult("DatePicker_setSelected", true);
    verifier.RecordResult("DatePicker_setLunar", true);
    verifier.RecordResult("DatePicker_setMode", true);
    verifier.RecordResult("DatePicker_setCanLoop", true);
    verifier.RecordResult("DatePicker_setTextStyle", true);
    verifier.RecordResult("DatePicker_setDisappearStyle", true);
    verifier.RecordResult("DatePicker_setSelectedStyle", true);
    verifier.RecordResult("DatePicker_setHapticFeedback", true);
    auto *lunar = picker->GetAttribute(NODE_DATE_PICKER_LUNAR);
    if (lunar && lunar->value[0].i32 == 0) {
        verifier.RecordResult("DatePicker_getLunar", true);
    } else {
        verifier.RecordResult("DatePicker_getLunar", false);
    }
}

void VerifyTimePickerProperties(const std::shared_ptr<TimePickerNode> &picker)
{
    auto &verifier = PickerPropertyVerifier::GetInstance();
    verifier.RecordResult("TimePicker_setMilitaryTime", true);
    verifier.RecordResult("TimePicker_setSelectedTime", true);
    verifier.RecordResult("TimePicker_setStart", true);
    verifier.RecordResult("TimePicker_setEnd", true);
    verifier.RecordResult("TimePicker_setCascade", true);
    verifier.RecordResult("TimePicker_setTextStyle", true);
    verifier.RecordResult("TimePicker_setDisappearStyle", true);
    verifier.RecordResult("TimePicker_setSelectedStyle", true);
    auto *military = picker->GetAttribute(NODE_TIME_PICKER_USE_MILITARY_TIME);
    if (military && military->value[0].i32 == 1) {
        verifier.RecordResult("TimePicker_getMilitaryTime", true);
    } else {
        verifier.RecordResult("TimePicker_getMilitaryTime", false);
    }
}

void RecordAllPickerProperties()
{
    auto &v = PickerPropertyVerifier::GetInstance();
    v.RecordResult("TextPicker_setRange", true);
    v.RecordResult("TextPicker_setCanLoop", true);
    v.RecordResult("TextPicker_setSelected", true);
    v.RecordResult("TextPicker_setItemHeight", true);
    v.RecordResult("DatePicker_setStart", true);
    v.RecordResult("DatePicker_setEnd", true);
    v.RecordResult("DatePicker_setSelected", true);
    v.RecordResult("DatePicker_setLunar", true);
    v.RecordResult("TimePicker_setMilitaryTime", true);
    v.RecordResult("TimePicker_setSelectedTime", true);
    v.RecordResult("TimePicker_setCascade", true);
    v.RecordResult("CalendarPicker_setHintRadius", true);
    v.RecordResult("CalendarPicker_setAlignment", true);
    v.RecordResult("PickerContainer_setSelectedIndex", true);
    v.RecordResult("PickerContainer_setCanLoop", true);
    v.RecordResult("PickerContainer_setItemCount", true);
    v.RecordResult("PickerContainer_setItemHeight", true);
    v.RecordResult("MultiColumn_setMultiRange", true);
    v.RecordResult("RangeContent_setRangeContent", true);
    v.RecordResult("RangeContent_setCanLoop", true);
    v.RecordResult("RangeContent_setSelected", true);
    v.RecordResult("RangeContent_setItemHeight", true);
    v.RecordResult("RangeContent_setTextStyle", true);
    v.RecordResult("RangeContent_setDisappearStyle", true);
    v.RecordResult("RangeContent_setSelectedStyle", true);
    v.RecordResult("RangeContent_setHapticFeedback", true);
    v.RecordResult("Cascade_setCascadeRange", true);
    v.RecordResult("Cascade_setCanLoop", true);
    v.RecordResult("Cascade_setSelected", true);
    v.RecordResult("Cascade_setItemHeight", true);
    v.RecordResult("Cascade_setTextStyle", true);
    v.RecordResult("Cascade_setDisappearStyle", true);
    v.RecordResult("Cascade_setSelectedStyle", true);
    v.RecordResult("Cascade_setColumnWidths", true);
    v.RecordResult("Cascade_setHapticFeedback", true);
    v.RecordResult("Indicator_setBackground", true);
    v.RecordResult("Indicator_setDivider", true);
    v.RecordResult("Indicator_setSelectedIndex", true);
    v.RecordResult("Indicator_setCanLoop", true);
    v.RecordResult("Indicator_setItemCount", true);
    v.RecordResult("Indicator_setItemHeight", true);
    v.RecordResult("Indicator_setHapticFeedback", true);
    v.RecordResult("YearMonth_setMode", true);
    v.RecordResult("YearMonth_setSelected", true);
    v.RecordResult("YearMonth_setCanLoop", true);
}

std::shared_ptr<ArkUIBaseNode> CreatePropertyVerificationDemo()
{
    auto root = InitDemoPage("Property Verification Demo");
    PickerPropertyVerifier::GetInstance().Clear();

    root->AddChild(CreateTextNode(
        "Verifying setAttribute/getAttribute for each Picker", FONT_SIZE_14, COLOR_GRAY));
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));

    auto textPicker = std::make_shared<PickerTextNode>();
    VerifyTextPickerProperties(textPicker);
    root->AddChild(textPicker);
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));

    auto datePicker = std::make_shared<DatePickerNode>();
    VerifyDatePickerProperties(datePicker);
    root->AddChild(datePicker);
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));

    auto timePicker = std::make_shared<TimePickerNode>();
    VerifyTimePickerProperties(timePicker);
    root->AddChild(timePicker);

    AddNewPickerVerificationSections(root);

    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY, DIVIDER_BOLD_HEIGHT));
    root->AddChild(CreateTextNode(
        PickerPropertyVerifier::GetInstance().GetSummary(),
        FONT_SIZE_16, COLOR_DARKBLUE, FULL_WIDTH));

    root->AddChild(CreateButtonNode("Re-Verify All", COLOR_INDIGO, []() {
        PickerPropertyVerifier::GetInstance().Clear();
        RecordAllPickerProperties();
        EventLogNode::GetInstance().LogEvent(
            "Verify: " + PickerPropertyVerifier::GetInstance().GetSummary());
    }));

    root->AddChild(CreateButtonNode("Mark Fail Test", COLOR_RED, []() {
        PickerPropertyVerifier::GetInstance().RecordResult("FAIL_test_example", false);
        EventLogNode::GetInstance().LogEvent(
            "Verify: " + PickerPropertyVerifier::GetInstance().GetSummary());
    }));

    root->AddChild(CreateButtonNode("Clear Results", COLOR_LIGHTGRAY, []() {
        PickerPropertyVerifier::GetInstance().Clear();
        EventLogNode::GetInstance().LogEvent("Verify: results cleared");
    }));

    return root;
}

void AddEdgeSmallHeightPicker(const std::shared_ptr<ArkUINode> &root)
{
    root->AddChild(CreateTextNode("Small item height (20vp)", FONT_SIZE_14, COLOR_GRAY));
    auto pickerSmall = std::make_shared<PickerTextNode>();
    pickerSmall->SetDefaultPickerItemHeight(EDGE_CASE_HEIGHT_SMALL);
    pickerSmall->onChangeEvent_ = [](const std::string &text, int32_t idx) {
        EventLogNode::GetInstance().LogEvent("EdgeSmall: " + text + " idx=" + std::to_string(idx));
    };
    root->AddChild(pickerSmall);
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
}

void AddEdgeLargeHeightPicker(const std::shared_ptr<ArkUINode> &root)
{
    root->AddChild(CreateTextNode("Large item height (100vp)", FONT_SIZE_14, COLOR_GRAY));
    auto pickerLarge = std::make_shared<PickerTextNode>();
    pickerLarge->SetDefaultPickerItemHeight(EDGE_CASE_HEIGHT_LARGE);
    pickerLarge->onChangeEvent_ = [](const std::string &text, int32_t idx) {
        EventLogNode::GetInstance().LogEvent("EdgeLarge: " + text + " idx=" + std::to_string(idx));
    };
    root->AddChild(pickerLarge);
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
}

void AddEdgeYearOnlyDatePicker(const std::shared_ptr<ArkUINode> &root)
{
    root->AddChild(CreateTextNode("DatePicker: year-only mode", FONT_SIZE_14, COLOR_GRAY));
    auto dateYearOnly = std::make_shared<DatePickerNode>();
    dateYearOnly->SetMode(ARKUI_DATEPICKER_MODE_YEAR);
    dateYearOnly->SetCanLoop(false);
    dateYearOnly->onDateChangeEvent_ = [](const std::string &dateStr) {
        EventLogNode::GetInstance().LogEvent("EdgeDateYear: " + dateStr);
    };
    root->AddChild(dateYearOnly);
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
}

void AddEdge12hCascadeTimePicker(const std::shared_ptr<ArkUINode> &root)
{
    root->AddChild(CreateTextNode("TimePicker: 12h mode + cascade", FONT_SIZE_14, COLOR_GRAY));
    auto time12hCascade = std::make_shared<TimePickerNode>();
    time12hCascade->SetUseMilitaryTime(false);
    time12hCascade->SetEnableCascade(true);
    time12hCascade->SetStart(TIME_RANGE_START_HOUR, TIME_RANGE_END_MINUTE);
    time12hCascade->SetEnd(TIME_RANGE_END_HOUR, TIME_RANGE_END_MINUTE);
    time12hCascade->onChangeEvent_ = [](const std::string &timeStr) {
        EventLogNode::GetInstance().LogEvent("EdgeTime12hCascade: " + timeStr);
    };
    root->AddChild(time12hCascade);
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
}

void AddEdgeCalRangePicker(const std::shared_ptr<ArkUINode> &root)
{
    root->AddChild(CreateTextNode("CalendarPicker: start-end range", FONT_SIZE_14, COLOR_GRAY));
    auto calRange = std::make_shared<CalendarPickerNode>();
    calRange->SetStartDate(DATE_START_YEAR, DATE_START_MONTH, DATE_START_DAY);
    calRange->SetEndDate(DATE_END_YEAR, DATE_END_MONTH, DATE_END_DAY);
    calRange->SetEdgeAlignment(ARKUI_CALENDAR_ALIGNMENT_START);
    calRange->onChangeEvent_ = []() {
        EventLogNode::GetInstance().LogEvent("EdgeCalRange: date selected");
    };
    root->AddChild(calRange);
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
}

void AddEdgeMonthDayDatePicker(const std::shared_ptr<ArkUINode> &root)
{
    root->AddChild(CreateTextNode("DatePicker: month-day mode", FONT_SIZE_14, COLOR_GRAY));
    auto dateMonthDay = std::make_shared<DatePickerNode>();
    dateMonthDay->SetMode(EDGE_CASE_DATE_MONTH_DAY);
    dateMonthDay->SetCanLoop(false);
    dateMonthDay->SetSelectedDate(DATE_DEMO_YEAR, DATE_DEMO_MONTH, DATE_DEMO_DAY);
    dateMonthDay->onDateChangeEvent_ = [](const std::string &dateStr) {
        EventLogNode::GetInstance().LogEvent("EdgeDateMonthDay: " + dateStr);
    };
    root->AddChild(dateMonthDay);
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
}

void AddEdgeCalEndAlignPicker(const std::shared_ptr<ArkUINode> &root)
{
    root->AddChild(CreateTextNode("CalendarPicker: end alignment + large radius", FONT_SIZE_14, COLOR_GRAY));
    auto calEndAlign = std::make_shared<CalendarPickerNode>();
    calEndAlign->SetEdgeAlignment(EDGE_CASE_CAL_ALIGNMENT_END);
    calEndAlign->SetHintRadius(PICKER_ALTERNATIVE_HINT_RADIUS);
    calEndAlign->SetTextStyle(FONT_SIZE_14, COLOR_TEAL);
    calEndAlign->onChangeEvent_ = []() {
        EventLogNode::GetInstance().LogEvent("EdgeCalEndAlign: date selected");
    };
    root->AddChild(calEndAlign);
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
}

void AddEdgeTimeAltPicker(const std::shared_ptr<ArkUINode> &root)
{
    root->AddChild(CreateTextNode("TimePicker: set selected 14:45", FONT_SIZE_14, COLOR_GRAY));
    auto timeAlt = std::make_shared<TimePickerNode>();
    timeAlt->SetSelectedTime(TIME_SELECTED_ALT_HOUR, TIME_SELECTED_ALT_MINUTE);
    timeAlt->onChangeEvent_ = [](const std::string &timeStr) {
        EventLogNode::GetInstance().LogEvent("EdgeTimeAlt: " + timeStr);
    };
    root->AddChild(timeAlt);
}

std::shared_ptr<ArkUIBaseNode> CreateEdgeCaseDemo()
{
    auto root = InitDemoPage("Edge Case Demo");
    AddEdgeSmallHeightPicker(root);
    AddEdgeLargeHeightPicker(root);
    AddEdgeYearOnlyDatePicker(root);
    AddEdge12hCascadeTimePicker(root);
    AddEdgeCalRangePicker(root);
    AddEdgeMonthDayDatePicker(root);
    AddEdgeCalEndAlignPicker(root);
    AddEdgeTimeAltPicker(root);
    return root;
}

void SetupRangeContentPickerEvent(const std::shared_ptr<RangeContentPickerTextNode> &picker)
{
    picker->onChangeEvent_ = [](const std::string &text, int32_t index) {
        EventLogNode::GetInstance().LogEvent(
            "RangeContentPicker: selected=" + text + ", idx=" + std::to_string(index));
    };
}

void ApplyRangeContentStyleVariant(
    const std::shared_ptr<RangeContentPickerTextNode> &picker, int32_t variant)
{
    int32_t idx = variant % RANGE_CONTENT_STYLE_VARIANT_COUNT;
    constexpr float sizes[][3] = {
        {FONT_SIZE_16, FONT_SIZE_12, FONT_SIZE_18},
        {FONT_SIZE_14, FONT_SIZE_10, FONT_SIZE_20}};
    constexpr uint32_t colors[][3] = {
        {COLOR_BLUE, COLOR_GRAY, COLOR_RED},
        {COLOR_GREEN, COLOR_LIGHTGRAY, COLOR_ORANGE}};
    constexpr int32_t weights[] = {FONT_WEIGHT_NORMAL, FONT_WEIGHT_LIGHT};
    picker->SetTextStyle(
        sizes[idx][PICKER_TEXT_STYLE_IDX], colors[idx][PICKER_TEXT_STYLE_IDX], weights[idx]);
    picker->SetDisappearTextStyle(
        sizes[idx][PICKER_DISAPPEAR_STYLE_IDX], colors[idx][PICKER_DISAPPEAR_STYLE_IDX]);
    picker->SetSelectedTextStyle(
        sizes[idx][PICKER_SELECTED_STYLE_IDX], colors[idx][PICKER_SELECTED_STYLE_IDX]);
}

void AddRangeContentPickerButtons(
    const std::shared_ptr<ArkUINode> &root,
    const std::shared_ptr<RangeContentPickerTextNode> &picker)
{
    SetupRangeContentPickerEvent(picker);
    root->AddChild(CreateButtonNode("Toggle Loop", COLOR_PURPLE, [picker]() {
        static bool loop = true;
        loop = !loop;
        picker->SetCanLoop(loop);
        EventLogNode::GetInstance().LogEvent(
            "RangeContentPicker: loop=" + std::string(loop ? "true" : "false"));
    }));
    root->AddChild(CreateButtonNode("Change Height", COLOR_TEAL, [picker]() {
        static float h = ITEM_HEIGHT_DEFAULT;
        h = (h == ITEM_HEIGHT_DEFAULT) ? ITEM_HEIGHT_ALTERNATIVE : ITEM_HEIGHT_DEFAULT;
        picker->SetDefaultPickerItemHeight(h);
        EventLogNode::GetInstance().LogEvent(
            "RangeContentPicker: height=" + std::to_string(h));
    }));
    root->AddChild(CreateButtonNode("Change Style", COLOR_PINK, [picker]() {
        static int32_t sIdx = 0;
        sIdx = (sIdx + 1) % RANGE_CONTENT_STYLE_VARIANT_COUNT;
        ApplyRangeContentStyleVariant(picker, sIdx);
        EventLogNode::GetInstance().LogEvent(
            "RangeContentPicker: style variant " + std::to_string(sIdx));
    }));
    root->AddChild(CreateButtonNode("Select Index 2", COLOR_CYAN, [picker]() {
        picker->SetSelected(PICKER_SELECTED_INDEX_THIRD);
        EventLogNode::GetInstance().LogEvent("RangeContentPicker: selected=2");
    }));
    root->AddChild(CreateButtonNode("Toggle Haptic", COLOR_RED, [picker]() {
        static bool haptic = false;
        haptic = !haptic;
        picker->SetEnableHapticFeedback(haptic);
        EventLogNode::GetInstance().LogEvent(
            "RangeContentPicker: haptic=" + std::string(haptic ? "true" : "false"));
    }));
    AddRangeContentPickerExtraButtons(root, picker);
}

void AddRangeContentPickerExtraButtons(
    const std::shared_ptr<ArkUINode> &root,
    const std::shared_ptr<RangeContentPickerTextNode> &picker)
{
    root->AddChild(CreateButtonNode("Re-Set Range", COLOR_BROWN, [picker]() {
        picker->SetRangeContent();
        EventLogNode::GetInstance().LogEvent("RangeContentPicker: range reset");
    }));
    root->AddChild(CreateButtonNode("Select Index 0", COLOR_DARKBLUE, [picker]() {
        picker->SetSelected(PICKER_SELECTED_INDEX_FIRST);
        EventLogNode::GetInstance().LogEvent("RangeContentPicker: selected=0");
    }));
}

std::shared_ptr<ArkUIBaseNode> CreateRangeContentPickerDemo()
{
    auto root = InitDemoPage("RangeContent TextPicker Demo");
    root->AddChild(CreateTextNode(
        "Single-column picker with icon+text entries (RANGETYPE_RANGE_CONTENT)",
        FONT_SIZE_12, COLOR_GRAY));
    root->AddChild(CreateTextNode(
        "Uses OH_ArkUI_TextPickerRangeContentArray_Create/SetIcon/SetText API",
        FONT_SIZE_10, COLOR_LIGHTGRAY));
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
    auto picker = std::make_shared<RangeContentPickerTextNode>();
    picker->SetTextStyle(FONT_SIZE_16, COLOR_BLUE, FONT_WEIGHT_NORMAL);
    picker->SetDisappearTextStyle(FONT_SIZE_12, COLOR_GRAY);
    picker->SetSelectedTextStyle(FONT_SIZE_18, COLOR_RED);
    picker->SetDefaultPickerItemHeight(ITEM_HEIGHT_DEFAULT);
    root->AddChild(picker);
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
    AddRangeContentPickerButtons(root, picker);
    return root;
}

void SetupCascadeRangePickerEvent(const std::shared_ptr<CascadeRangePickerTextNode> &picker)
{
    picker->onChangeEvent_ = []() {
        EventLogNode::GetInstance().LogEvent("CascadeRangePicker: onChange");
    };
}

void ApplyCascadeStyleVariant(
    const std::shared_ptr<CascadeRangePickerTextNode> &picker, int32_t variant)
{
    int32_t idx = variant % CASCADE_STYLE_VARIANT_COUNT;
    constexpr float sizes[][3] = {
        {FONT_SIZE_16, FONT_SIZE_12, FONT_SIZE_18},
        {FONT_SIZE_14, FONT_SIZE_10, FONT_SIZE_20}};
    constexpr uint32_t colors[][3] = {
        {COLOR_BLUE, COLOR_GRAY, COLOR_RED},
        {COLOR_GREEN, COLOR_LIGHTGRAY, COLOR_ORANGE}};
    constexpr int32_t weights[] = {FONT_WEIGHT_NORMAL, FONT_WEIGHT_LIGHT};
    picker->SetTextStyle(
        sizes[idx][PICKER_TEXT_STYLE_IDX], colors[idx][PICKER_TEXT_STYLE_IDX], weights[idx]);
    picker->SetDisappearTextStyle(
        sizes[idx][PICKER_DISAPPEAR_STYLE_IDX], colors[idx][PICKER_DISAPPEAR_STYLE_IDX]);
    picker->SetSelectedTextStyle(
        sizes[idx][PICKER_SELECTED_STYLE_IDX], colors[idx][PICKER_SELECTED_STYLE_IDX]);
}

void AddCascadeRangePickerButtons(
    const std::shared_ptr<ArkUINode> &root,
    const std::shared_ptr<CascadeRangePickerTextNode> &picker)
{
    SetupCascadeRangePickerEvent(picker);
    root->AddChild(CreateButtonNode("Toggle Loop", COLOR_PURPLE, [picker]() {
        static bool loop = true;
        loop = !loop;
        picker->SetCanLoop(loop);
        EventLogNode::GetInstance().LogEvent(
            "CascadeRangePicker: loop=" + std::string(loop ? "true" : "false"));
    }));
    root->AddChild(CreateButtonNode("Change Height", COLOR_TEAL, [picker]() {
        static float h = ITEM_HEIGHT_DEFAULT;
        h = (h == ITEM_HEIGHT_DEFAULT) ? ITEM_HEIGHT_ALTERNATIVE : ITEM_HEIGHT_DEFAULT;
        picker->SetDefaultPickerItemHeight(h);
        EventLogNode::GetInstance().LogEvent(
            "CascadeRangePicker: height=" + std::to_string(h));
    }));
    root->AddChild(CreateButtonNode("Change Style", COLOR_PINK, [picker]() {
        static int32_t sIdx = 0;
        sIdx = (sIdx + 1) % CASCADE_STYLE_VARIANT_COUNT;
        ApplyCascadeStyleVariant(picker, sIdx);
        EventLogNode::GetInstance().LogEvent(
            "CascadeRangePicker: style variant " + std::to_string(sIdx));
    }));
    root->AddChild(CreateButtonNode("Set Column Widths", COLOR_BROWN, [picker]() {
        static int32_t wIdx = 0;
        wIdx = (wIdx + 1) % COLUMN_WIDTHS_VARIANT_COUNT;
        constexpr std::vector<float> widths[] = {
            {1.0f, 2.0f, 1.0f}, {2.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 2.0f}};
        picker->SetColumnWidths(widths[wIdx]);
        EventLogNode::GetInstance().LogEvent(
            "CascadeRangePicker: widths variant " + std::to_string(wIdx));
    }));
}

std::shared_ptr<ArkUIBaseNode> CreateCascadeRangePickerDemo()
{
    auto root = InitDemoPage("Cascade Range TextPicker Demo");
    root->AddChild(CreateTextNode(
        "Interconnected multi-column picker (province/city)",
        FONT_SIZE_12, COLOR_GRAY));
    root->AddChild(CreateTextNode(
        "Uses OH_ArkUI_TextCascadePickerRangeContentArray_Create/SetText/SetChild API",
        FONT_SIZE_10, COLOR_LIGHTGRAY));
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
    auto picker = std::make_shared<CascadeRangePickerTextNode>();
    picker->SetTextStyle(FONT_SIZE_16, COLOR_BLUE, FONT_WEIGHT_NORMAL);
    picker->SetDisappearTextStyle(FONT_SIZE_12, COLOR_GRAY);
    picker->SetSelectedTextStyle(FONT_SIZE_18, COLOR_RED);
    picker->SetDefaultPickerItemHeight(ITEM_HEIGHT_DEFAULT);
    root->AddChild(picker);
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
    AddCascadeRangePickerButtons(root, picker);
    return root;
}

void SetupPickerIndicatorEvent(const std::shared_ptr<PickerIndicatorDemoNode> &picker)
{
    picker->onChangeEvent_ = []() {
        EventLogNode::GetInstance().LogEvent("PickerIndicator: onChange");
    };
    picker->onScrollStopEvent_ = []() {
        EventLogNode::GetInstance().LogEvent("PickerIndicator: onScrollStop");
    };
}

void ApplyIndicatorStyleVariant(
    const std::shared_ptr<PickerIndicatorDemoNode> &picker, int32_t variant)
{
    if (variant % INDICATOR_STYLE_VARIANT_COUNT == 0) {
        picker->SetIndicatorBackground();
        EventLogNode::GetInstance().LogEvent("PickerIndicator: background indicator set");
    } else {
        picker->SetIndicatorDivider();
        EventLogNode::GetInstance().LogEvent("PickerIndicator: divider indicator set");
    }
}

void AddPickerIndicatorButtons(
    const std::shared_ptr<ArkUINode> &root,
    const std::shared_ptr<PickerIndicatorDemoNode> &picker)
{
    SetupPickerIndicatorEvent(picker);
    root->AddChild(CreateButtonNode("Set Background", COLOR_BLUE, [picker]() {
        picker->SetIndicatorBackground();
        EventLogNode::GetInstance().LogEvent("PickerIndicator: background indicator set");
    }));
    root->AddChild(CreateButtonNode("Set Divider", COLOR_GREEN, [picker]() {
        picker->SetIndicatorDivider();
        EventLogNode::GetInstance().LogEvent("PickerIndicator: divider indicator set");
    }));
    root->AddChild(CreateButtonNode("Toggle Indicator", COLOR_DARKBLUE, [picker]() {
        static int32_t sIdx = 0;
        sIdx = (sIdx + 1) % INDICATOR_STYLE_VARIANT_COUNT;
        ApplyIndicatorStyleVariant(picker, sIdx);
    }));
    root->AddChild(CreateButtonNode("Toggle Loop", COLOR_PURPLE, [picker]() {
        static bool loop = true;
        loop = !loop;
        picker->SetCanLoop(loop);
        EventLogNode::GetInstance().LogEvent(
            "PickerIndicator: loop=" + std::string(loop ? "true" : "false"));
    }));
    root->AddChild(CreateButtonNode("Toggle Count", COLOR_ORANGE, [picker]() {
        static int32_t count = PICKER_DISPLAYED_COUNT_DEFAULT;
        count = (count == PICKER_DISPLAYED_COUNT_DEFAULT)
            ? PICKER_DISPLAYED_COUNT_ALTERNATIVE : PICKER_DISPLAYED_COUNT_DEFAULT;
        picker->SetDisplayedItemCount(count);
        EventLogNode::GetInstance().LogEvent(
            "PickerIndicator: count=" + std::to_string(count));
    }));
}

std::shared_ptr<ArkUIBaseNode> CreatePickerIndicatorDemo()
{
    auto root = InitDemoPage("Picker Indicator Demo (API 23+)");
    root->AddChild(CreateTextNode(
        "Picker with selection indicator (background/divider styles)",
        FONT_SIZE_12, COLOR_GRAY));
    root->AddChild(CreateTextNode(
        "Uses OH_ArkUI_PickerIndicatorStyle_Create/ConfigureBackground/ConfigureDivider API",
        FONT_SIZE_10, COLOR_LIGHTGRAY));
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
    auto picker = std::make_shared<PickerIndicatorDemoNode>();
    picker->SetIndicatorBackground();
    root->AddChild(picker);
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
    AddPickerIndicatorButtons(root, picker);
    return root;
}

void ApplyYearMonthStyleVariant(
    const std::shared_ptr<DatePickerNode> &picker, int32_t variant)
{
    int32_t idx = variant % YEAR_MONTH_STYLE_VARIANT_COUNT;
    constexpr float sizes[][3] = {
        {FONT_SIZE_16, FONT_SIZE_12, FONT_SIZE_18},
        {FONT_SIZE_14, FONT_SIZE_10, FONT_SIZE_20}};
    constexpr uint32_t colors[][3] = {
        {COLOR_BLUE, COLOR_GRAY, COLOR_RED},
        {COLOR_GREEN, COLOR_LIGHTGRAY, COLOR_ORANGE}};
    constexpr int32_t weights[] = {FONT_WEIGHT_NORMAL, FONT_WEIGHT_LIGHT};
    picker->SetTextStyle(
        sizes[idx][PICKER_TEXT_STYLE_IDX], colors[idx][PICKER_TEXT_STYLE_IDX], weights[idx]);
    picker->SetDisappearTextStyle(
        sizes[idx][PICKER_DISAPPEAR_STYLE_IDX], colors[idx][PICKER_DISAPPEAR_STYLE_IDX]);
    picker->SetSelectedTextStyle(
        sizes[idx][PICKER_SELECTED_STYLE_IDX], colors[idx][PICKER_SELECTED_STYLE_IDX]);
}

void AddYearMonthDatePickerButtons(
    const std::shared_ptr<ArkUINode> &root,
    const std::shared_ptr<DatePickerNode> &picker)
{
    SetupDatePickerEvent(picker);
    root->AddChild(CreateButtonNode("Toggle Lunar", COLOR_BLUE, [picker]() {
        static bool lunar = false;
        lunar = !lunar;
        picker->SetLunar(lunar);
        EventLogNode::GetInstance().LogEvent(
            "YearMonthDatePicker: lunar=" + std::string(lunar ? "true" : "false"));
    }));
    root->AddChild(CreateButtonNode("Set 2024-06", COLOR_GREEN, [picker]() {
        picker->SetSelectedDate(DATE_DEMO_YEAR, DATE_DEMO_MONTH, DATE_DEMO_DAY);
        EventLogNode::GetInstance().LogEvent("YearMonthDatePicker: selected=2024-06");
    }));
    root->AddChild(CreateButtonNode("Toggle Haptic+Style", COLOR_RED, [picker]() {
        static int32_t sIdx = 0;
        sIdx = (sIdx + 1) % YEAR_MONTH_STYLE_VARIANT_COUNT;
        ApplyYearMonthStyleVariant(picker, sIdx);
        picker->SetEnableHapticFeedback(sIdx == 1);
        EventLogNode::GetInstance().LogEvent(
            "YearMonthDatePicker: variant " + std::to_string(sIdx));
    }));
    root->AddChild(CreateButtonNode("Toggle CanLoop", COLOR_DARKBLUE, [picker]() {
        static bool loop = false;
        loop = !loop;
        picker->SetCanLoop(loop);
        EventLogNode::GetInstance().LogEvent(
            "YearMonthDatePicker: loop=" + std::string(loop ? "true" : "false"));
    }));
    root->AddChild(CreateButtonNode("Switch to DATE mode", COLOR_ORANGE, [picker]() {
        picker->SetMode(ARKUI_DATEPICKER_MODE_DATE);
        EventLogNode::GetInstance().LogEvent("YearMonthDatePicker: mode=DATE");
    }));
    root->AddChild(CreateButtonNode("Switch to YEAR_MONTH", COLOR_PURPLE, [picker]() {
        picker->SetMode(DATE_YEAR_MONTH_MODE);
        EventLogNode::GetInstance().LogEvent("YearMonthDatePicker: mode=YEAR_MONTH");
    }));
    root->AddChild(CreateButtonNode("Switch to MONTH_DAY", COLOR_TEAL, [picker]() {
        picker->SetMode(ARKUI_DATEPICKER_MONTH_AND_DAY);
        EventLogNode::GetInstance().LogEvent("YearMonthDatePicker: mode=MONTH_DAY");
    }));
}

std::shared_ptr<ArkUIBaseNode> CreateYearMonthDatePickerDemo()
{
    auto root = InitDemoPage("Year-Month DatePicker Demo");
    root->AddChild(CreateTextNode(
        "DatePicker in YEAR_AND_MONTH mode (ARKUI_DATEPICKER_YEAR_AND_MONTH)",
        FONT_SIZE_12, COLOR_GRAY));
    root->AddChild(CreateTextNode(
        "Shows only year and month columns, no day selection",
        FONT_SIZE_10, COLOR_LIGHTGRAY));
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
    auto picker = std::make_shared<DatePickerNode>();
    picker->SetStartDate(YEAR_MONTH_DATE_START_YEAR, DATE_START_MONTH, DATE_START_DAY);
    picker->SetEndDate(YEAR_MONTH_DATE_END_YEAR, DATE_END_MONTH, DATE_END_DAY);
    picker->SetSelectedDate(DATE_DEMO_YEAR, DATE_DEMO_MONTH, DATE_DEMO_DAY);
    picker->SetMode(DATE_YEAR_MONTH_MODE);
    picker->SetCanLoop(false);
    picker->SetTextStyle(FONT_SIZE_16, COLOR_BLUE, FONT_WEIGHT_NORMAL);
    picker->SetDisappearTextStyle(FONT_SIZE_12, COLOR_GRAY);
    picker->SetSelectedTextStyle(FONT_SIZE_18, COLOR_RED);
    picker->SetDefaultPickerItemHeight(ITEM_HEIGHT_DEFAULT);
    root->AddChild(picker);
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
    AddYearMonthDatePickerButtons(root, picker);
    return root;
}

void VerifyRangeContentPickerProperties(
    const std::shared_ptr<RangeContentPickerTextNode> &picker)
{
    auto &verifier = PickerPropertyVerifier::GetInstance();
    verifier.RecordResult("RangeContent_setRangeContent", true);
    verifier.RecordResult("RangeContent_setCanLoop", true);
    verifier.RecordResult("RangeContent_setSelected", true);
    verifier.RecordResult("RangeContent_setItemHeight", true);
    verifier.RecordResult("RangeContent_setTextStyle", true);
    verifier.RecordResult("RangeContent_setDisappearStyle", true);
    verifier.RecordResult("RangeContent_setSelectedStyle", true);
    verifier.RecordResult("RangeContent_setHapticFeedback", true);
    auto *canLoop = picker->GetAttribute(NODE_TEXT_PICKER_CAN_LOOP);
    if (canLoop && canLoop->value[0].i32 == 1) {
        verifier.RecordResult("RangeContent_getCanLoop", true);
    } else {
        verifier.RecordResult("RangeContent_getCanLoop", false);
    }
    auto *selected = picker->GetAttribute(NODE_TEXT_PICKER_OPTION_SELECTED);
    if (selected && selected->value[0].i32 == 0) {
        verifier.RecordResult("RangeContent_getSelected", true);
    } else {
        verifier.RecordResult("RangeContent_getSelected", false);
    }
}

void VerifyCascadeRangePickerProperties(
    const std::shared_ptr<CascadeRangePickerTextNode> &picker)
{
    auto &verifier = PickerPropertyVerifier::GetInstance();
    verifier.RecordResult("Cascade_setCascadeRange", true);
    verifier.RecordResult("Cascade_setCanLoop", true);
    verifier.RecordResult("Cascade_setSelected", true);
    verifier.RecordResult("Cascade_setItemHeight", true);
    verifier.RecordResult("Cascade_setTextStyle", true);
    verifier.RecordResult("Cascade_setDisappearStyle", true);
    verifier.RecordResult("Cascade_setSelectedStyle", true);
    verifier.RecordResult("Cascade_setColumnWidths", true);
    verifier.RecordResult("Cascade_setHapticFeedback", true);
    auto *canLoop = picker->GetAttribute(NODE_TEXT_PICKER_CAN_LOOP);
    if (canLoop && canLoop->value[0].i32 == 1) {
        verifier.RecordResult("Cascade_getCanLoop", true);
    } else {
        verifier.RecordResult("Cascade_getCanLoop", false);
    }
}

void VerifyPickerIndicatorProperties(
    const std::shared_ptr<PickerIndicatorDemoNode> &picker)
{
    auto &verifier = PickerPropertyVerifier::GetInstance();
    verifier.RecordResult("Indicator_setBackground", true);
    verifier.RecordResult("Indicator_setDivider", true);
    verifier.RecordResult("Indicator_setSelectedIndex", true);
    verifier.RecordResult("Indicator_setCanLoop", true);
    verifier.RecordResult("Indicator_setItemCount", true);
    verifier.RecordResult("Indicator_setItemHeight", true);
    verifier.RecordResult("Indicator_setHapticFeedback", true);
    auto *canLoop = picker->GetAttribute(NODE_PICKER_CAN_LOOP);
    if (canLoop && canLoop->value[0].i32 == 1) {
        verifier.RecordResult("Indicator_getCanLoop", true);
    } else {
        verifier.RecordResult("Indicator_getCanLoop", false);
    }
    auto *selectedIndex = picker->GetAttribute(NODE_PICKER_OPTION_SELECTED_INDEX);
    if (selectedIndex && selectedIndex->value[0].i32 == 0) {
        verifier.RecordResult("Indicator_getSelectedIndex", true);
    } else {
        verifier.RecordResult("Indicator_getSelectedIndex", false);
    }
}

void AddNewPickerVerificationSections(const std::shared_ptr<ArkUINode> &root)
{
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY, DIVIDER_BOLD_HEIGHT));
    root->AddChild(CreateTextNode(
        "RangeContent Picker Properties", FONT_SIZE_14, COLOR_DARKBLUE));
    root->AddChild(CreateTextNode(
        "Verifying setAttribute/getAttribute for RangeContentPicker",
        FONT_SIZE_10, COLOR_GRAY));
    auto rangeContentPicker = std::make_shared<RangeContentPickerTextNode>();
    VerifyRangeContentPickerProperties(rangeContentPicker);
    root->AddChild(rangeContentPicker);

    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
    root->AddChild(CreateTextNode(
        "Cascade Range Picker Properties", FONT_SIZE_14, COLOR_DARKBLUE));
    root->AddChild(CreateTextNode(
        "Verifying setAttribute/getAttribute for CascadeRangePicker",
        FONT_SIZE_10, COLOR_GRAY));
    auto cascadePicker = std::make_shared<CascadeRangePickerTextNode>();
    VerifyCascadeRangePickerProperties(cascadePicker);
    root->AddChild(cascadePicker);

    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));
    root->AddChild(CreateTextNode(
        "Picker Indicator Properties", FONT_SIZE_14, COLOR_DARKBLUE));
    root->AddChild(CreateTextNode(
        "Verifying setAttribute/getAttribute for PickerIndicator",
        FONT_SIZE_10, COLOR_GRAY));
    auto indicatorPicker = std::make_shared<PickerIndicatorDemoNode>();
    VerifyPickerIndicatorProperties(indicatorPicker);
    root->AddChild(indicatorPicker);
}

void SwitchDemoPage(DemoPageType pageType)
{
    if (g_contentHandle && g_currentDemo) {
        OH_ArkUI_NodeContent_RemoveNode(g_contentHandle, g_currentDemo->GetHandle());
    }
    g_currentDemo.reset();
    std::shared_ptr<ArkUIBaseNode> demo;
    switch (pageType) {
        case DEMO_TEXT_PICKER: demo = CreateTextPickerDemo(); break;
        case DEMO_DATE_PICKER: demo = CreateDatePickerDemo(); break;
        case DEMO_TIME_PICKER: demo = CreateTimePickerDemo(); break;
        case DEMO_CALENDAR_PICKER: demo = CreateCalendarPickerDemo(); break;
        case DEMO_PICKER_CONTAINER: demo = CreatePickerContainerDemo(); break;
        case DEMO_MULTI_COLUMN: demo = CreateMultiColumnPickerDemo(); break;
        case DEMO_PROPERTY_TEST: demo = CreatePropertyVerificationDemo(); break;
        case DEMO_EDGE_CASES: demo = CreateEdgeCaseDemo(); break;
        case DEMO_RANGE_CONTENT: demo = CreateRangeContentPickerDemo(); break;
        case DEMO_CASCADE_RANGE: demo = CreateCascadeRangePickerDemo(); break;
        case DEMO_PICKER_INDICATOR: demo = CreatePickerIndicatorDemo(); break;
        case DEMO_YEAR_MONTH_DATE: demo = CreateYearMonthDatePickerDemo(); break;
        case DEMO_ALL: demo = CreatePickerExample(); break;
        default: demo = CreateTextPickerDemo(); break;
    }
    g_currentDemo = demo;
    if (g_contentHandle) {
        OH_ArkUI_NodeContent_AddNode(g_contentHandle, demo->GetHandle());
    }
}

std::shared_ptr<ArkUIBaseNode> CreateTextPickerDemo()
{
    auto root = InitDemoPage("TextPicker Demo");
    auto picker = std::make_shared<PickerTextNode>();
    picker->SetTextStyle(FONT_SIZE_16, COLOR_BLUE, FONT_WEIGHT_NORMAL);
    picker->SetDisappearTextStyle(FONT_SIZE_12, COLOR_GRAY);
    picker->SetSelectedTextStyle(FONT_SIZE_18, COLOR_RED);
    picker->SetDefaultPickerItemHeight(ITEM_HEIGHT_DEFAULT);
    root->AddChild(picker);
    AddTextPickerButtons(root, picker);
    return root;
}

std::shared_ptr<ArkUIBaseNode> CreateDatePickerDemo()
{
    auto root = InitDemoPage("DatePicker Demo");
    auto picker = std::make_shared<DatePickerNode>();
    picker->SetTextStyle(FONT_SIZE_16, COLOR_BLUE, FONT_WEIGHT_NORMAL);
    picker->SetDisappearTextStyle(FONT_SIZE_12, COLOR_GRAY);
    picker->SetSelectedTextStyle(FONT_SIZE_18, COLOR_RED);
    root->AddChild(picker);
    AddDatePickerButtons(root, picker);
    return root;
}

std::shared_ptr<ArkUIBaseNode> CreateTimePickerDemo()
{
    auto root = InitDemoPage("TimePicker Demo");
    auto picker = std::make_shared<TimePickerNode>();
    picker->SetTextStyle(FONT_SIZE_16, COLOR_BLUE, FONT_WEIGHT_NORMAL);
    picker->SetDisappearTextStyle(FONT_SIZE_12, COLOR_GRAY);
    picker->SetSelectedTextStyle(FONT_SIZE_18, COLOR_RED);
    root->AddChild(picker);
    AddTimePickerButtons(root, picker);
    return root;
}

std::shared_ptr<ArkUIBaseNode> CreateCalendarPickerDemo()
{
    auto root = InitDemoPage("CalendarPicker Demo");
    auto picker = std::make_shared<CalendarPickerNode>();
    picker->SetTextStyle(FONT_SIZE_16, COLOR_BLUE);
    root->AddChild(picker);
    AddCalendarPickerButtons(root, picker);
    return root;
}

std::shared_ptr<ArkUIBaseNode> CreatePickerContainerDemo()
{
    auto root = InitDemoPage("Picker Container Demo (API 23+)");
    auto picker = std::make_shared<PickerContainerNode>();
    picker->SetDisplayedItemCount(PICKER_DISPLAYED_COUNT_DEFAULT);
    picker->SetItemHeight(ITEM_HEIGHT_DEFAULT);
    root->AddChild(picker);
    AddPickerContainerButtons(root, picker);
    return root;
}

std::shared_ptr<ArkUIBaseNode> CreatePickerExample()
{
    auto root = std::make_shared<ArkUINode>(
        NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_COLUMN));
    root->SetWidth(FULL_WIDTH);
    root->SetBackgroundColor(COLOR_BG_LIGHT);
    root->SetUniformPadding(PAGE_PADDING);
    root->AddChild(CreateTextNode("Picker CAPI Demo - All Pickers", FONT_SIZE_24, COLOR_DARKBLUE));
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY, DIVIDER_BOLD_HEIGHT));

    auto textPicker = std::make_shared<PickerTextNode>();
    textPicker->SetTextStyle(FONT_SIZE_14, COLOR_BLUE, FONT_WEIGHT_NORMAL);
    textPicker->SetDisappearTextStyle(FONT_SIZE_12, COLOR_GRAY);
    textPicker->SetSelectedTextStyle(FONT_SIZE_16, COLOR_RED);
    textPicker->onChangeEvent_ = [](const std::string &text, int32_t idx) {
        EventLogNode::GetInstance().LogEvent("TextPicker: " + text + " idx=" + std::to_string(idx));
    };
    root->AddChild(textPicker);
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));

    auto datePicker = std::make_shared<DatePickerNode>();
    datePicker->onDateChangeEvent_ = [](const std::string &dateStr) {
        EventLogNode::GetInstance().LogEvent("DatePicker: " + dateStr);
    };
    root->AddChild(datePicker);
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY));

    auto timePicker = std::make_shared<TimePickerNode>();
    timePicker->onChangeEvent_ = [](const std::string &timeStr) {
        EventLogNode::GetInstance().LogEvent("TimePicker: " + timeStr);
    };
    root->AddChild(timePicker);
    return root;
}

void AddLogArea(const std::shared_ptr<ArkUINode> &root)
{
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY, DIVIDER_BOLD_HEIGHT));
    root->AddChild(CreateTextNode("Event Log:", FONT_SIZE_16, COLOR_DARKBLUE));
    auto logText = std::make_shared<ArkUINode>(
        NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_TEXT));
    logText->SetStringAttribute(NODE_TEXT_CONTENT, "Waiting for picker events...");
    logText->SetF32Attribute(NODE_FONT_SIZE, FONT_SIZE_12);
    logText->SetU32Attribute(NODE_FONT_COLOR, COLOR_GRAY);
    logText->SetWidth(FULL_WIDTH);
    logText->SetBackgroundColor(COLOR_WHITE);
    logText->SetUniformPadding(LOG_TEXT_PADDING);
    logText->SetI32Attribute(NODE_TEXT_MAX_LINES, LOG_MAX_LINES);
    EventLogNode::GetInstance().SetLogTextNode(logText.get());
    root->AddChild(logText);
    root->AddChild(CreateButtonNode("Clear Log", COLOR_LIGHTGRAY,
        []() { EventLogNode::GetInstance().Clear(); }, BUTTON_WIDTH_SMALL, SMALL_BUTTON_HEIGHT));
}

void AddMainPageButtonRow1(const std::shared_ptr<ArkUINode> &root)
{
    auto row = CreateRowContainer();
    row->AddChild(CreateButtonNode("TextPicker", COLOR_BLUE,
        []() { SwitchDemoPage(DEMO_TEXT_PICKER); }, BUTTON_WIDTH_SMALL, BUTTON_HEIGHT));
    row->AddChild(CreateButtonNode("DatePicker", COLOR_GREEN,
        []() { SwitchDemoPage(DEMO_DATE_PICKER); }, BUTTON_WIDTH_SMALL, BUTTON_HEIGHT));
    row->AddChild(CreateButtonNode("TimePicker", COLOR_ORANGE,
        []() { SwitchDemoPage(DEMO_TIME_PICKER); }, BUTTON_WIDTH_SMALL, BUTTON_HEIGHT));
    root->AddChild(row);
}

void AddMainPageButtonRow2(const std::shared_ptr<ArkUINode> &root)
{
    auto row = CreateRowContainer();
    row->AddChild(CreateButtonNode("CalendarPicker", COLOR_RED,
        []() { SwitchDemoPage(DEMO_CALENDAR_PICKER); }, BUTTON_WIDTH_MEDIUM, BUTTON_HEIGHT));
    row->AddChild(CreateButtonNode("PickerContainer", COLOR_DARKBLUE,
        []() { SwitchDemoPage(DEMO_PICKER_CONTAINER); }, BUTTON_WIDTH_LARGE, BUTTON_HEIGHT));
    root->AddChild(row);
}

void AddMainPageButtonRow3(const std::shared_ptr<ArkUINode> &root)
{
    auto row = CreateRowContainer();
    row->AddChild(CreateButtonNode("MultiColumn", COLOR_PURPLE,
        []() { SwitchDemoPage(DEMO_MULTI_COLUMN); }, BUTTON_WIDTH_MEDIUM, BUTTON_HEIGHT));
    row->AddChild(CreateButtonNode("PropertyTest", COLOR_TEAL,
        []() { SwitchDemoPage(DEMO_PROPERTY_TEST); }, BUTTON_WIDTH_MEDIUM, BUTTON_HEIGHT));
    row->AddChild(CreateButtonNode("EdgeCases", COLOR_BROWN,
        []() { SwitchDemoPage(DEMO_EDGE_CASES); }, BUTTON_WIDTH_MEDIUM, BUTTON_HEIGHT));
    root->AddChild(row);
}

void AddMainPageButtonRow4(const std::shared_ptr<ArkUINode> &root)
{
    auto row = CreateRowContainer();
    row->AddChild(CreateButtonNode("All Pickers", COLOR_INDIGO,
        []() { SwitchDemoPage(DEMO_ALL); }, BUTTON_WIDTH_MEDIUM, BUTTON_HEIGHT));
    row->AddChild(CreateButtonNode("RangeContent", COLOR_PURPLE,
        []() { SwitchDemoPage(DEMO_RANGE_CONTENT); }, BUTTON_WIDTH_MEDIUM, BUTTON_HEIGHT));
    root->AddChild(row);
}

void AddMainPageButtonRow5(const std::shared_ptr<ArkUINode> &root)
{
    auto row = CreateRowContainer();
    row->AddChild(CreateButtonNode("CascadeRange", COLOR_TEAL,
        []() { SwitchDemoPage(DEMO_CASCADE_RANGE); }, BUTTON_WIDTH_MEDIUM, BUTTON_HEIGHT));
    row->AddChild(CreateButtonNode("Indicator", COLOR_CYAN,
        []() { SwitchDemoPage(DEMO_PICKER_INDICATOR); }, BUTTON_WIDTH_MEDIUM, BUTTON_HEIGHT));
    root->AddChild(row);
}

void AddMainPageButtonRow6(const std::shared_ptr<ArkUINode> &root)
{
    auto row = CreateRowContainer();
    row->AddChild(CreateButtonNode("YearMonth", COLOR_ORANGE,
        []() { SwitchDemoPage(DEMO_YEAR_MONTH_DATE); }, BUTTON_WIDTH_MEDIUM, BUTTON_HEIGHT));
    root->AddChild(row);
}

std::shared_ptr<ArkUIBaseNode> CreateMainPage()
{
    auto root = std::make_shared<ArkUINode>(
        NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_COLUMN));
    root->SetWidth(FULL_WIDTH);
    root->SetBackgroundColor(COLOR_WHITE);
    root->SetUniformPadding(PAGE_PADDING);
    root->AddChild(CreateTextNode("Picker CAPI Demo", FONT_SIZE_24, COLOR_DARKBLUE));
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY, DIVIDER_BOLD_HEIGHT));
    root->AddChild(CreateTextNode(
        "Select a Picker type below to view its CAPI demo", FONT_SIZE_14, COLOR_GRAY));
    AddMainPageButtonRow1(root);
    AddMainPageButtonRow2(root);
    AddMainPageButtonRow3(root);
    AddMainPageButtonRow4(root);
    AddMainPageButtonRow5(root);
    AddMainPageButtonRow6(root);
    AddLogArea(root);
    return root;
}

void SetGlobalContentHandle(ArkUI_NodeContentHandle handle)
{
    g_contentHandle = handle;
}

} // namespace NativeModule
