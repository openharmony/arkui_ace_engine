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
 * See the License for the language governing permissions and
 * limitations under the License.
 */

#ifndef PICKEREXAMPLE_H
#define PICKEREXAMPLE_H

#include <memory>
#include <functional>
#include <string>
#include <vector>
#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include "ArkUIBaseNode.h"
#include "NativeModule.h"

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
constexpr float BUTTON_HEIGHT = 40.0f;
constexpr float SMALL_BUTTON_HEIGHT = 30.0f;
constexpr float BUTTON_BORDER_RADIUS = 8.0f;
constexpr float BUTTON_WIDTH_SMALL = 80.0f;
constexpr float BUTTON_WIDTH_MEDIUM = 100.0f;
constexpr float BUTTON_WIDTH_LARGE = 110.0f;
constexpr float DIVIDER_HEIGHT = 1.0f;
constexpr float DIVIDER_BOLD_HEIGHT = 2.0f;
constexpr float ITEM_HEIGHT_DEFAULT = 40.0f;
constexpr float ITEM_HEIGHT_ALTERNATIVE = 60.0f;
constexpr float ITEM_HEIGHT_TALL = 50.0f;
constexpr float LOG_TEXT_PADDING = 8.0f;

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

constexpr int32_t STYLE_VARIANT_COUNT = 2;
constexpr int32_t DATE_STYLE_VARIANT_COUNT = 3;
constexpr int32_t DATE_PICKER_MODE_COUNT = 3;
constexpr int32_t CALENDAR_ALIGNMENT_COUNT = 3;
constexpr int32_t PICKER_TEXT_STYLE_IDX = 0;
constexpr int32_t PICKER_DISAPPEAR_STYLE_IDX = 1;
constexpr int32_t PICKER_SELECTED_STYLE_IDX = 2;
constexpr int32_t TEXT_PICKER_STYLE_VARIANT_COUNT = 3;

constexpr int32_t EVENT_ID_TEXT_PICKER = 1;
constexpr int32_t EVENT_ID_DATE_PICKER = 2;
constexpr int32_t EVENT_ID_TIME_PICKER = 3;
constexpr int32_t EVENT_ID_CALENDAR_PICKER = 4;
constexpr int32_t EVENT_ID_PICKER_CONTAINER = 5;

class ArkUINode : public ArkUIBaseNode {
public:
    explicit ArkUINode(ArkUI_NodeHandle handle);
    ~ArkUINode() override;
    void SetWidth(float width);
    void SetHeight(float height);
    void SetBackgroundColor(uint32_t color);
    void SetUniformPadding(float padding);
    void SetUniformMargin(float margin);
    void SetUniformBorderRadius(float radius);
    void SetBoolAttribute(ArkUI_NodeAttributeType attr, bool value);
    void SetI32Attribute(ArkUI_NodeAttributeType attr, int32_t value);
    void SetF32Attribute(ArkUI_NodeAttributeType attr, float value);
    void SetU32Attribute(ArkUI_NodeAttributeType attr, uint32_t value);
    void SetStringAttribute(ArkUI_NodeAttributeType attr, const char *value);
    void SetI32ArrayAttribute(ArkUI_NodeAttributeType attr, const std::vector<int32_t> &values);
    void SetF32ArrayAttribute(ArkUI_NodeAttributeType attr, const std::vector<float> &values);
    void SetStyle3Attribute(ArkUI_NodeAttributeType attr, float f1, uint32_t u1, int32_t i1);
    void SetStyle2Attribute(ArkUI_NodeAttributeType attr, float f1, uint32_t u1);
    void RegisterOnClick(const std::function<void()> &onClick);
    void RegisterNodeEvent(ArkUI_NodeEventType eventType, int32_t eventId);

protected:
    static void NodeEventReceiver(ArkUI_NodeEvent *event);
    void ProcessNodeEvent(ArkUI_NodeEvent *event);
    virtual void OnNodeEvent(ArkUI_NodeEvent *event) {}

    ArkUI_NativeNodeAPI_1 *nativeModule_ = nullptr;
    std::function<void()> onClick_;
    std::vector<std::pair<ArkUI_NodeEventType, int32_t>> registeredEvents_;
};

class PickerTextNode : public ArkUINode {
public:
    PickerTextNode()
        : ArkUINode(NativeModuleInstance::GetInstance()
              ->GetNativeNodeAPI()->createNode(ARKUI_NODE_TEXT_PICKER))
    {
        SetSingleRange();
        SetI32Attribute(NODE_TEXT_PICKER_OPTION_SELECTED, 0);
        SetBoolAttribute(NODE_TEXT_PICKER_CAN_LOOP, true);
        RegisterChangeEvent();
    }

    void SetSingleRange()
    {
        ArkUI_NumberValue rangeValues[] = {{.i32 = ARKUI_TEXTPICKER_RANGETYPE_SINGLE}};
        ArkUI_AttributeItem rangeItem = {
            .string = "OptionA,OptionB,OptionC,OptionD,OptionE",
            .value = rangeValues, .size = 1};
        nativeModule_->setAttribute(handle_, NODE_TEXT_PICKER_OPTION_RANGE, &rangeItem);
    }
    void SetSelected(int32_t index) { SetI32Attribute(NODE_TEXT_PICKER_OPTION_SELECTED, index); }
    void SetCanLoop(bool canLoop) { SetBoolAttribute(NODE_TEXT_PICKER_CAN_LOOP, canLoop); }
    void SetDefaultPickerItemHeight(float height)
    { SetF32Attribute(NODE_TEXT_PICKER_DEFAULT_PICKER_ITEM_HEIGHT, height); }
    void SetTextStyle(float fontSize, uint32_t color, int32_t fontWeight)
    { SetStyle3Attribute(NODE_TEXT_PICKER_TEXT_STYLE, fontSize, color, fontWeight); }
    void SetDisappearTextStyle(float fontSize, uint32_t color)
    { SetStyle2Attribute(NODE_TEXT_PICKER_DISAPPEAR_TEXT_STYLE, fontSize, color); }
    void SetSelectedTextStyle(float fontSize, uint32_t color)
    { SetStyle2Attribute(NODE_TEXT_PICKER_SELECTED_TEXT_STYLE, fontSize, color); }
    void SetEnableHapticFeedback(bool enable) { SetBoolAttribute(NODE_TEXT_PICKER_ENABLE_HAPTIC_FEEDBACK, enable); }
    void RegisterChangeEvent() { RegisterNodeEvent(NODE_TEXT_PICKER_EVENT_ON_CHANGE, EVENT_ID_TEXT_PICKER); }

protected:
    void OnNodeEvent(ArkUI_NodeEvent *event) override;
    void HandleChangeEvent(ArkUI_NodeEvent *event);

public:
    std::function<void(const std::string &, int32_t)> onChangeEvent_;
    std::function<void()> onScrollStopEvent_;

private:
    std::string lastSelectedText_;
    int32_t lastSelectedIndex_ = 0;
};

class DatePickerNode : public ArkUINode {
public:
    DatePickerNode()
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

    void SetStartDate(int32_t year, int32_t month, int32_t day)
    { SetI32ArrayAttribute(NODE_DATE_PICKER_START, {year, month, day}); }
    void SetEndDate(int32_t year, int32_t month, int32_t day)
    { SetI32ArrayAttribute(NODE_DATE_PICKER_END, {year, month, day}); }
    void SetSelectedDate(int32_t year, int32_t month, int32_t day)
    { SetI32ArrayAttribute(NODE_DATE_PICKER_SELECTED, {year, month, day}); }
    void SetLunar(bool lunar) { SetBoolAttribute(NODE_DATE_PICKER_LUNAR, lunar); }
    void SetMode(int32_t mode) { SetI32Attribute(NODE_DATE_PICKER_MODE, mode); }
    void SetCanLoop(bool canLoop) { SetBoolAttribute(NODE_DATE_PICKER_CAN_LOOP, canLoop); }
    void SetEnableHapticFeedback(bool enable) { SetBoolAttribute(NODE_DATE_PICKER_ENABLE_HAPTIC_FEEDBACK, enable); }
    void SetTextStyle(float fontSize, uint32_t color, int32_t fontWeight)
    { SetStyle3Attribute(NODE_DATE_PICKER_TEXT_STYLE, fontSize, color, fontWeight); }
    void SetDisappearTextStyle(float fontSize, uint32_t color)
    { SetStyle2Attribute(NODE_DATE_PICKER_DISAPPEAR_TEXT_STYLE, fontSize, color); }
    void SetSelectedTextStyle(float fontSize, uint32_t color)
    { SetStyle2Attribute(NODE_DATE_PICKER_SELECTED_TEXT_STYLE, fontSize, color); }
    void RegisterChangeEvent() { RegisterNodeEvent(NODE_DATE_PICKER_EVENT_ON_DATE_CHANGE, EVENT_ID_DATE_PICKER); }

protected:
    void OnNodeEvent(ArkUI_NodeEvent *event) override;

public:
    std::function<void(const std::string &)> onDateChangeEvent_;

private:
    std::string lastDateStr_;
};

class TimePickerNode : public ArkUINode {
public:
    TimePickerNode()
        : ArkUINode(NativeModuleInstance::GetInstance()
              ->GetNativeNodeAPI()->createNode(ARKUI_NODE_TIME_PICKER))
    {
        SetBoolAttribute(NODE_TIME_PICKER_USE_MILITARY_TIME, true);
        SetSelectedTime(TIME_DEFAULT_HOUR, TIME_DEFAULT_MINUTE);
        RegisterChangeEvent();
    }

    void SetUseMilitaryTime(bool military) { SetBoolAttribute(NODE_TIME_PICKER_USE_MILITARY_TIME, military); }
    void SetSelectedTime(int32_t hour, int32_t minute)
    { SetI32ArrayAttribute(NODE_TIME_PICKER_SELECTED, {hour, minute}); }
    void SetStart(int32_t hour, int32_t minute) { SetI32ArrayAttribute(NODE_TIME_PICKER_START, {hour, minute}); }
    void SetEnd(int32_t hour, int32_t minute) { SetI32ArrayAttribute(NODE_TIME_PICKER_END, {hour, minute}); }
    void SetEnableCascade(bool enable) { SetBoolAttribute(NODE_TIME_PICKER_ENABLE_CASCADE, enable); }
    void SetTextStyle(float fontSize, uint32_t color, int32_t fontWeight)
    { SetStyle3Attribute(NODE_TIME_PICKER_TEXT_STYLE, fontSize, color, fontWeight); }
    void SetDisappearTextStyle(float fontSize, uint32_t color)
    { SetStyle2Attribute(NODE_TIME_PICKER_DISAPPEAR_TEXT_STYLE, fontSize, color); }
    void SetSelectedTextStyle(float fontSize, uint32_t color)
    { SetStyle2Attribute(NODE_TIME_PICKER_SELECTED_TEXT_STYLE, fontSize, color); }
    void RegisterChangeEvent() { RegisterNodeEvent(NODE_TIME_PICKER_EVENT_ON_CHANGE, EVENT_ID_TIME_PICKER); }

protected:
    void OnNodeEvent(ArkUI_NodeEvent *event) override;

public:
    std::function<void(const std::string &)> onChangeEvent_;

private:
    std::string lastTimeStr_;
};

class CalendarPickerNode : public ArkUINode {
public:
    CalendarPickerNode()
        : ArkUINode(NativeModuleInstance::GetInstance()
              ->GetNativeNodeAPI()->createNode(ARKUI_NODE_CALENDAR_PICKER))
    {
        SetF32Attribute(NODE_CALENDAR_PICKER_HINT_RADIUS, PICKER_DEFAULT_HINT_RADIUS);
        SetSelectedDate(DATE_SELECTED_YEAR, DATE_SELECTED_MONTH, DATE_SELECTED_DAY);
        SetI32Attribute(NODE_CALENDAR_PICKER_EDGE_ALIGNMENT, ARKUI_CALENDAR_ALIGNMENT_CENTER);
        RegisterChangeEvent();
    }

    void SetHintRadius(float radius) { SetF32Attribute(NODE_CALENDAR_PICKER_HINT_RADIUS, radius); }
    void SetSelectedDate(int32_t year, int32_t month, int32_t day)
    { SetI32ArrayAttribute(NODE_CALENDAR_PICKER_SELECTED_DATE, {year, month, day}); }
    void SetEdgeAlignment(int32_t alignment)
    { SetI32Attribute(NODE_CALENDAR_PICKER_EDGE_ALIGNMENT, alignment); }
    void SetTextStyle(float fontSize, uint32_t color)
    { SetStyle2Attribute(NODE_CALENDAR_PICKER_TEXT_STYLE, fontSize, color); }
    void SetStartDate(int32_t year, int32_t month, int32_t day)
    { SetI32ArrayAttribute(NODE_CALENDAR_PICKER_START, {year, month, day}); }
    void SetEndDate(int32_t year, int32_t month, int32_t day)
    { SetI32ArrayAttribute(NODE_CALENDAR_PICKER_END, {year, month, day}); }
    void RegisterChangeEvent() { RegisterNodeEvent(NODE_CALENDAR_PICKER_EVENT_ON_CHANGE, EVENT_ID_CALENDAR_PICKER); }

protected:
    void OnNodeEvent(ArkUI_NodeEvent *event) override;

public:
    std::function<void()> onChangeEvent_;
};

class PickerContainerNode : public ArkUINode {
public:
    PickerContainerNode()
        : ArkUINode(NativeModuleInstance::GetInstance()
              ->GetNativeNodeAPI()->createNode(ARKUI_NODE_PICKER))
    {
        SetI32Attribute(NODE_PICKER_OPTION_SELECTED_INDEX, 0);
        SetBoolAttribute(NODE_PICKER_CAN_LOOP, true);
        SetBoolAttribute(NODE_PICKER_ENABLE_HAPTIC_FEEDBACK, false);
        RegisterChangeEvent();
    }

    void SetSelectedIndex(int32_t index) { SetI32Attribute(NODE_PICKER_OPTION_SELECTED_INDEX, index); }
    void SetCanLoop(bool canLoop) { SetBoolAttribute(NODE_PICKER_CAN_LOOP, canLoop); }
    void SetEnableHapticFeedback(bool enable) { SetBoolAttribute(NODE_PICKER_ENABLE_HAPTIC_FEEDBACK, enable); }
    void SetDisplayedItemCount(int32_t count) { SetI32Attribute(NODE_PICKER_DISPLAYED_ITEM_COUNT, count); }
    void SetItemHeight(float height) { SetF32Attribute(NODE_PICKER_ITEM_HEIGHT, height); }
    void RegisterChangeEvent() { RegisterNodeEvent(NODE_PICKER_EVENT_ON_CHANGE, EVENT_ID_PICKER_CONTAINER); }

protected:
    void OnNodeEvent(ArkUI_NodeEvent *event) override;

public:
    std::function<void()> onChangeEvent_;
};

class EventLogNode {
public:
    static EventLogNode &GetInstance()
    {
        static EventLogNode instance;
        return instance;
    }

    void SetLogTextNode(ArkUINode *node) { logTextNode_ = node; }
    void LogEvent(const std::string &message)
    {
        logEntries_.push_back(GetTimestamp() + " " + message);
        if (logEntries_.size() > LOG_MAX_ENTRIES) {
            logEntries_.erase(logEntries_.begin());
        }
        UpdateDisplay();
    }
    void Clear()
    {
        logEntries_.clear();
        UpdateDisplay();
    }

private:
    std::string GetTimestamp();
    void UpdateDisplay();

    ArkUINode *logTextNode_ = nullptr;
    std::vector<std::string> logEntries_;
};

std::shared_ptr<ArkUINode> CreateTextNode(
    const std::string &content, float fontSize, uint32_t color,
    float width = 0, float height = 0);
std::shared_ptr<ArkUINode> CreateButtonNode(
    const std::string &content, uint32_t bgColor,
    const std::function<void()> &onClick,
    float width = 0, float height = BUTTON_HEIGHT);
std::shared_ptr<ArkUINode> CreateDividerNode(uint32_t color, float height = DIVIDER_HEIGHT);
std::shared_ptr<ArkUINode> CreateRowContainer();
std::shared_ptr<ArkUINode> InitDemoPage(const std::string &title);

void SetupTextPickerEvent(const std::shared_ptr<PickerTextNode> &picker);
void AddTextPickerButtons(const std::shared_ptr<ArkUINode> &root, const std::shared_ptr<PickerTextNode> &picker);
void ApplyTextStyleVariant(const std::shared_ptr<PickerTextNode> &picker, int32_t variant);

void SetupDatePickerEvent(const std::shared_ptr<DatePickerNode> &picker);
void AddDatePickerButtons(const std::shared_ptr<ArkUINode> &root, const std::shared_ptr<DatePickerNode> &picker);
void ApplyDatePickerStyleVariant(const std::shared_ptr<DatePickerNode> &picker, int32_t variant);

void SetupTimePickerEvent(const std::shared_ptr<TimePickerNode> &picker);
void AddTimePickerButtons(const std::shared_ptr<ArkUINode> &root, const std::shared_ptr<TimePickerNode> &picker);
void ApplyTimePickerStyleVariant(const std::shared_ptr<TimePickerNode> &picker, int32_t variant);

void SetupCalendarPickerEvent(const std::shared_ptr<CalendarPickerNode> &picker);
void AddCalendarPickerButtons(
    const std::shared_ptr<ArkUINode> &root, const std::shared_ptr<CalendarPickerNode> &picker);

void SetupPickerContainerEvent(const std::shared_ptr<PickerContainerNode> &picker);
void AddPickerContainerButtons(
    const std::shared_ptr<ArkUINode> &root, const std::shared_ptr<PickerContainerNode> &picker);

enum DemoPageType {
    DEMO_TEXT_PICKER = 0,
    DEMO_DATE_PICKER = 1,
    DEMO_TIME_PICKER = 2,
    DEMO_CALENDAR_PICKER = 3,
    DEMO_PICKER_CONTAINER = 4,
    DEMO_ALL = 5,
};

extern std::shared_ptr<ArkUIBaseNode> g_currentDemo;
extern ArkUI_NodeContentHandle g_contentHandle;

void SwitchDemoPage(DemoPageType pageType);
std::shared_ptr<ArkUIBaseNode> CreateTextPickerDemo();
std::shared_ptr<ArkUIBaseNode> CreateDatePickerDemo();
std::shared_ptr<ArkUIBaseNode> CreateTimePickerDemo();
std::shared_ptr<ArkUIBaseNode> CreateCalendarPickerDemo();
std::shared_ptr<ArkUIBaseNode> CreatePickerContainerDemo();
std::shared_ptr<ArkUIBaseNode> CreatePickerExample();
void AddLogArea(const std::shared_ptr<ArkUINode> &root);
std::shared_ptr<ArkUIBaseNode> CreateMainPage();
void SetGlobalContentHandle(ArkUI_NodeContentHandle handle);

} // namespace NativeModule

#endif // PICKEREXAMPLE_H