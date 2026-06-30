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

constexpr float BUTTON_HEIGHT = 40.0f;
constexpr float DIVIDER_HEIGHT = 1.0f;

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
    const ArkUI_AttributeItem *GetAttribute(ArkUI_NodeAttributeType attr);

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
    PickerTextNode();

    void SetSingleRange();
    void SetSelected(int32_t index);
    void SetCanLoop(bool canLoop);
    void SetDefaultPickerItemHeight(float height);
    void SetTextStyle(float fontSize, uint32_t color, int32_t fontWeight);
    void SetDisappearTextStyle(float fontSize, uint32_t color);
    void SetSelectedTextStyle(float fontSize, uint32_t color);
    void SetEnableHapticFeedback(bool enable);
    void RegisterChangeEvent();

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
    DatePickerNode();

    void SetStartDate(int32_t year, int32_t month, int32_t day);
    void SetEndDate(int32_t year, int32_t month, int32_t day);
    void SetSelectedDate(int32_t year, int32_t month, int32_t day);
    void SetLunar(bool lunar);
    void SetMode(int32_t mode);
    void SetCanLoop(bool canLoop);
    void SetEnableHapticFeedback(bool enable);
    void SetTextStyle(float fontSize, uint32_t color, int32_t fontWeight);
    void SetDisappearTextStyle(float fontSize, uint32_t color);
    void SetSelectedTextStyle(float fontSize, uint32_t color);
    void RegisterChangeEvent();

protected:
    void OnNodeEvent(ArkUI_NodeEvent *event) override;

public:
    std::function<void(const std::string &)> onDateChangeEvent_;

private:
    std::string lastDateStr_;
};

class TimePickerNode : public ArkUINode {
public:
    TimePickerNode();

    void SetUseMilitaryTime(bool military);
    void SetSelectedTime(int32_t hour, int32_t minute);
    void SetStart(int32_t hour, int32_t minute);
    void SetEnd(int32_t hour, int32_t minute);
    void SetEnableCascade(bool enable);
    void SetTextStyle(float fontSize, uint32_t color, int32_t fontWeight);
    void SetDisappearTextStyle(float fontSize, uint32_t color);
    void SetSelectedTextStyle(float fontSize, uint32_t color);
    void RegisterChangeEvent();

protected:
    void OnNodeEvent(ArkUI_NodeEvent *event) override;

public:
    std::function<void(const std::string &)> onChangeEvent_;

private:
    std::string lastTimeStr_;
};

class CalendarPickerNode : public ArkUINode {
public:
    CalendarPickerNode();

    void SetHintRadius(float radius);
    void SetSelectedDate(int32_t year, int32_t month, int32_t day);
    void SetEdgeAlignment(int32_t alignment);
    void SetTextStyle(float fontSize, uint32_t color);
    void SetStartDate(int32_t year, int32_t month, int32_t day);
    void SetEndDate(int32_t year, int32_t month, int32_t day);
    void RegisterChangeEvent();

protected:
    void OnNodeEvent(ArkUI_NodeEvent *event) override;

public:
    std::function<void()> onChangeEvent_;
};

class PickerContainerNode : public ArkUINode {
public:
    PickerContainerNode();

    void SetSelectedIndex(int32_t index);
    void SetCanLoop(bool canLoop);
    void SetEnableHapticFeedback(bool enable);
    void SetDisplayedItemCount(int32_t count);
    void SetItemHeight(float height);
    void RegisterChangeEvent();

protected:
    void OnNodeEvent(ArkUI_NodeEvent *event) override;

public:
    std::function<void()> onChangeEvent_;
};

class MultiColumnPickerTextNode : public ArkUINode {
public:
    MultiColumnPickerTextNode();

    void SetMultiRange();
    void SetSelected(int32_t index);
    void SetCanLoop(bool canLoop);
    void SetDefaultPickerItemHeight(float height);
    void SetTextStyle(float fontSize, uint32_t color, int32_t fontWeight);
    void SetDisappearTextStyle(float fontSize, uint32_t color);
    void SetSelectedTextStyle(float fontSize, uint32_t color);
    void SetColumnWidths(const std::vector<float> &widths);

protected:
    void OnNodeEvent(ArkUI_NodeEvent *event) override;

public:
    std::function<void()> onChangeEvent_;
};

class RangeContentPickerTextNode : public ArkUINode {
public:
    RangeContentPickerTextNode();

    void SetRangeContent();
    void SetSelected(int32_t index);
    void SetCanLoop(bool canLoop);
    void SetDefaultPickerItemHeight(float height);
    void SetTextStyle(float fontSize, uint32_t color, int32_t fontWeight);
    void SetDisappearTextStyle(float fontSize, uint32_t color);
    void SetSelectedTextStyle(float fontSize, uint32_t color);
    void SetEnableHapticFeedback(bool enable);
    void RegisterChangeEvent();

protected:
    void OnNodeEvent(ArkUI_NodeEvent *event) override;
    void HandleChangeEvent(ArkUI_NodeEvent *event);

public:
    std::function<void(const std::string &, int32_t)> onChangeEvent_;

private:
    std::string lastSelectedText_;
    int32_t lastSelectedIndex_ = 0;
};

class CascadeRangePickerTextNode : public ArkUINode {
public:
    CascadeRangePickerTextNode();

    void SetCascadeRange();
    void SetSelected(int32_t index);
    void SetCanLoop(bool canLoop);
    void SetDefaultPickerItemHeight(float height);
    void SetTextStyle(float fontSize, uint32_t color, int32_t fontWeight);
    void SetDisappearTextStyle(float fontSize, uint32_t color);
    void SetSelectedTextStyle(float fontSize, uint32_t color);
    void SetColumnWidths(const std::vector<float> &widths);
    void RegisterChangeEvent();

protected:
    void OnNodeEvent(ArkUI_NodeEvent *event) override;

public:
    std::function<void()> onChangeEvent_;
};

class PickerIndicatorDemoNode : public ArkUINode {
public:
    PickerIndicatorDemoNode();

    void SetIndicatorBackground();
    void SetIndicatorDivider();
    void SetSelectedIndex(int32_t index);
    void SetCanLoop(bool canLoop);
    void SetDisplayedItemCount(int32_t count);
    void SetItemHeight(float height);
    void RegisterChangeEvent();

protected:
    void OnNodeEvent(ArkUI_NodeEvent *event) override;

public:
    std::function<void()> onChangeEvent_;
};

class PickerPropertyVerifier {
public:
    static PickerPropertyVerifier &GetInstance();
    void RecordResult(const std::string &testName, bool passed);
    int32_t GetPassedCount() const;
    int32_t GetFailedCount() const;
    std::string GetSummary() const;
    void Clear();

private:
    struct TestResult {
        std::string testName;
        bool passed;
    };
    std::vector<TestResult> results_;
};

class EventLogNode {
public:
    static EventLogNode &GetInstance();

    void SetLogTextNode(ArkUINode *node);
    void LogEvent(const std::string &message);
    void Clear();

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

void AddMultiColumnPickerButtons(
    const std::shared_ptr<ArkUINode> &root, const std::shared_ptr<MultiColumnPickerTextNode> &picker);
void RecordAllPickerProperties();

void AddEdgeSmallHeightPicker(const std::shared_ptr<ArkUINode> &root);
void AddEdgeLargeHeightPicker(const std::shared_ptr<ArkUINode> &root);
void AddEdgeYearOnlyDatePicker(const std::shared_ptr<ArkUINode> &root);
void AddEdge12hCascadeTimePicker(const std::shared_ptr<ArkUINode> &root);
void AddEdgeCalRangePicker(const std::shared_ptr<ArkUINode> &root);
void AddEdgeMonthDayDatePicker(const std::shared_ptr<ArkUINode> &root);
void AddEdgeCalEndAlignPicker(const std::shared_ptr<ArkUINode> &root);
void AddEdgeTimeAltPicker(const std::shared_ptr<ArkUINode> &root);

void SetupRangeContentPickerEvent(const std::shared_ptr<RangeContentPickerTextNode> &picker);
void AddRangeContentPickerButtons(
    const std::shared_ptr<ArkUINode> &root,
    const std::shared_ptr<RangeContentPickerTextNode> &picker);
void ApplyRangeContentStyleVariant(
    const std::shared_ptr<RangeContentPickerTextNode> &picker, int32_t variant);

void SetupCascadeRangePickerEvent(const std::shared_ptr<CascadeRangePickerTextNode> &picker);
void AddCascadeRangePickerButtons(
    const std::shared_ptr<ArkUINode> &root,
    const std::shared_ptr<CascadeRangePickerTextNode> &picker);
void ApplyCascadeStyleVariant(
    const std::shared_ptr<CascadeRangePickerTextNode> &picker, int32_t variant);

void SetupPickerIndicatorEvent(const std::shared_ptr<PickerIndicatorDemoNode> &picker);
void AddPickerIndicatorButtons(
    const std::shared_ptr<ArkUINode> &root,
    const std::shared_ptr<PickerIndicatorDemoNode> &picker);
void ApplyIndicatorStyleVariant(
    const std::shared_ptr<PickerIndicatorDemoNode> &picker, int32_t variant);

void AddYearMonthDatePickerButtons(
    const std::shared_ptr<ArkUINode> &root,
    const std::shared_ptr<DatePickerNode> &picker);
void ApplyYearMonthStyleVariant(
    const std::shared_ptr<DatePickerNode> &picker, int32_t variant);

void VerifyRangeContentPickerProperties(const std::shared_ptr<RangeContentPickerTextNode> &picker);
void VerifyCascadeRangePickerProperties(const std::shared_ptr<CascadeRangePickerTextNode> &picker);
void VerifyPickerIndicatorProperties(const std::shared_ptr<PickerIndicatorDemoNode> &picker);
void AddNewPickerVerificationSections(const std::shared_ptr<ArkUINode> &root);

enum DemoPageType {
    DEMO_TEXT_PICKER = 0,
    DEMO_DATE_PICKER = 1,
    DEMO_TIME_PICKER = 2,
    DEMO_CALENDAR_PICKER = 3,
    DEMO_PICKER_CONTAINER = 4,
    DEMO_ALL = 5,
    DEMO_MULTI_COLUMN = 6,
    DEMO_PROPERTY_TEST = 7,
    DEMO_EDGE_CASES = 8,
    DEMO_RANGE_CONTENT = 9,
    DEMO_CASCADE_RANGE = 10,
    DEMO_PICKER_INDICATOR = 11,
    DEMO_YEAR_MONTH_DATE = 12,
};

extern std::shared_ptr<ArkUIBaseNode> g_currentDemo;
extern ArkUI_NodeContentHandle g_contentHandle;

void SwitchDemoPage(DemoPageType pageType);
std::shared_ptr<ArkUIBaseNode> CreateTextPickerDemo();
std::shared_ptr<ArkUIBaseNode> CreateDatePickerDemo();
std::shared_ptr<ArkUIBaseNode> CreateTimePickerDemo();
std::shared_ptr<ArkUIBaseNode> CreateCalendarPickerDemo();
std::shared_ptr<ArkUIBaseNode> CreatePickerContainerDemo();
std::shared_ptr<ArkUIBaseNode> CreateMultiColumnPickerDemo();
std::shared_ptr<ArkUIBaseNode> CreatePropertyVerificationDemo();
std::shared_ptr<ArkUIBaseNode> CreateEdgeCaseDemo();
std::shared_ptr<ArkUIBaseNode> CreateRangeContentPickerDemo();
std::shared_ptr<ArkUIBaseNode> CreateCascadeRangePickerDemo();
std::shared_ptr<ArkUIBaseNode> CreatePickerIndicatorDemo();
std::shared_ptr<ArkUIBaseNode> CreateYearMonthDatePickerDemo();
std::shared_ptr<ArkUIBaseNode> CreatePickerExample();
void AddLogArea(const std::shared_ptr<ArkUINode> &root);
void AddMainPageButtonRow1(const std::shared_ptr<ArkUINode> &root);
void AddMainPageButtonRow2(const std::shared_ptr<ArkUINode> &root);
void AddMainPageButtonRow3(const std::shared_ptr<ArkUINode> &root);
void AddMainPageButtonRow4(const std::shared_ptr<ArkUINode> &root);
void AddMainPageButtonRow5(const std::shared_ptr<ArkUINode> &root);
void AddMainPageButtonRow6(const std::shared_ptr<ArkUINode> &root);
std::shared_ptr<ArkUIBaseNode> CreateMainPage();
void SetGlobalContentHandle(ArkUI_NodeContentHandle handle);

} // namespace NativeModule

#endif // PICKEREXAMPLE_H
