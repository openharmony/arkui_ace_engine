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

namespace NativeModule {

ArkUINode::ArkUINode(ArkUI_NodeHandle handle) : ArkUIBaseNode(handle)
{
    nativeModule_ = NativeModuleInstance::GetInstance()->GetNativeNodeAPI();
    nativeModule_->setUserData(handle_, this);
    nativeModule_->addNodeEventReceiver(handle_, ArkUINode::NodeEventReceiver);
}

ArkUINode::~ArkUINode()
{
    for (auto &pair : registeredEvents_) { nativeModule_->unregisterNodeEvent(handle_, pair.first); }
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
    for (auto v : values) { nv.push_back({.i32 = v}); }
    ArkUI_AttributeItem item = {nv.data(), static_cast<int32_t>(nv.size())};
    nativeModule_->setAttribute(handle_, attr, &item);
}
void ArkUINode::SetF32ArrayAttribute(ArkUI_NodeAttributeType attr, const std::vector<float> &values)
{
    std::vector<ArkUI_NumberValue> nv;
    for (auto v : values) { nv.push_back({.f32 = v}); }
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
    if (node) { node->ProcessNodeEvent(event); }
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
        if (onScrollStopEvent_) { onScrollStopEvent_(); }
    }
}

void PickerTextNode::HandleChangeEvent(ArkUI_NodeEvent *event)
{
    auto *compEvent = OH_ArkUI_NodeEvent_GetComponentEvent(event);
    if (compEvent) {
        lastSelectedText_ = compEvent->string;
        lastSelectedIndex_ = compEvent->number.i32;
    }
    OH_LOG_INFO(LOG_APP, "TextPicker onChange: text=%{public}s, index=%{public}d",
        lastSelectedText_.c_str(), lastSelectedIndex_);
    if (onChangeEvent_) { onChangeEvent_(lastSelectedText_, lastSelectedIndex_); }
}

void DatePickerNode::OnNodeEvent(ArkUI_NodeEvent *event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    if (eventType == NODE_DATE_PICKER_EVENT_ON_DATE_CHANGE) {
        auto *compEvent = OH_ArkUI_NodeEvent_GetComponentEvent(event);
        if (compEvent) { lastDateStr_ = std::to_string(compEvent->number.i32); }
        OH_LOG_INFO(LOG_APP, "DatePicker onDateChange: %{public}s", lastDateStr_.c_str());
        if (onDateChangeEvent_) { onDateChangeEvent_(lastDateStr_); }
    }
}

void TimePickerNode::OnNodeEvent(ArkUI_NodeEvent *event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    if (eventType == NODE_TIME_PICKER_EVENT_ON_CHANGE) {
        OH_LOG_INFO(LOG_APP, "TimePicker onChange triggered");
        if (onChangeEvent_) { onChangeEvent_(lastTimeStr_); }
    }
}

void CalendarPickerNode::OnNodeEvent(ArkUI_NodeEvent *event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    if (eventType == NODE_CALENDAR_PICKER_EVENT_ON_CHANGE) {
        OH_LOG_INFO(LOG_APP, "CalendarPicker onChange triggered");
        if (onChangeEvent_) { onChangeEvent_(); }
    }
}

void PickerContainerNode::OnNodeEvent(ArkUI_NodeEvent *event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    if (eventType == NODE_PICKER_EVENT_ON_CHANGE) {
        OH_LOG_INFO(LOG_APP, "PickerContainer onChange");
        if (onChangeEvent_) { onChangeEvent_(); }
    } else if (eventType == NODE_PICKER_EVENT_ON_SCROLL_STOP) {
        OH_LOG_INFO(LOG_APP, "PickerContainer onScrollStop");
    }
}

std::string EventLogNode::GetTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(now);
    struct tm tmStruct;
    localtime_r(&timeT, &tmStruct);
    char buf[32];
    if (strftime(buf, sizeof(buf), "%H:%M:%S", &tmStruct) == 0) {
        buf[0] = '\0';
    }
    return std::string(buf);
}

void EventLogNode::UpdateDisplay()
{
    if (!logTextNode_) { return; }
    std::string displayText;
    for (const auto &entry : logEntries_) {
        displayText += "[" + entry + "]\n";
    }
    logTextNode_->SetStringAttribute(NODE_TEXT_CONTENT, displayText.c_str());
}

std::shared_ptr<ArkUINode> CreateTextNode(
    const std::string &content, float fontSize, uint32_t color, float width, float height)
{
    auto node = std::make_shared<ArkUINode>(
        NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_TEXT));
    node->SetStringAttribute(NODE_TEXT_CONTENT, content.c_str());
    node->SetF32Attribute(NODE_FONT_SIZE, fontSize);
    node->SetU32Attribute(NODE_FONT_COLOR, color);
    if (width > 0) { node->SetWidth(width); }
    if (height > 0) { node->SetHeight(height); }
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
    if (width > 0) { node->SetWidth(width); }
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
        picker->SetStart(TIME_RANGE_START_HOUR, TIME_RANGE_START_MINUTE);
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
        case DEMO_ALL: demo = CreatePickerExample(); break;
        default: demo = CreateTextPickerDemo(); break;
    }
    g_currentDemo = demo;
    if (g_contentHandle) { OH_ArkUI_NodeContent_AddNode(g_contentHandle, demo->GetHandle()); }
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

std::shared_ptr<ArkUIBaseNode> CreateMainPage()
{
    auto root = std::make_shared<ArkUINode>(
        NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_COLUMN));
    root->SetWidth(FULL_WIDTH);
    root->SetBackgroundColor(COLOR_WHITE);
    root->SetUniformPadding(PAGE_PADDING);
    root->AddChild(CreateTextNode("Picker CAPI Demo", FONT_SIZE_24, COLOR_DARKBLUE));
    root->AddChild(CreateDividerNode(COLOR_LIGHTGRAY, DIVIDER_BOLD_HEIGHT));
    root->AddChild(CreateTextNode("Select a Picker type below to view its CAPI demo", FONT_SIZE_14, COLOR_GRAY));

    auto btnRow1 = CreateRowContainer();
    btnRow1->AddChild(CreateButtonNode("TextPicker", COLOR_BLUE,
        []() { SwitchDemoPage(DEMO_TEXT_PICKER); }, BUTTON_WIDTH_SMALL, BUTTON_HEIGHT));
    btnRow1->AddChild(CreateButtonNode("DatePicker", COLOR_GREEN,
        []() { SwitchDemoPage(DEMO_DATE_PICKER); }, BUTTON_WIDTH_SMALL, BUTTON_HEIGHT));
    btnRow1->AddChild(CreateButtonNode("TimePicker", COLOR_ORANGE,
        []() { SwitchDemoPage(DEMO_TIME_PICKER); }, BUTTON_WIDTH_SMALL, BUTTON_HEIGHT));
    root->AddChild(btnRow1);

    auto btnRow2 = CreateRowContainer();
    btnRow2->AddChild(CreateButtonNode("CalendarPicker", COLOR_RED,
        []() { SwitchDemoPage(DEMO_CALENDAR_PICKER); }, BUTTON_WIDTH_MEDIUM, BUTTON_HEIGHT));
    btnRow2->AddChild(CreateButtonNode("PickerContainer", COLOR_DARKBLUE,
        []() { SwitchDemoPage(DEMO_PICKER_CONTAINER); }, BUTTON_WIDTH_LARGE, BUTTON_HEIGHT));
    root->AddChild(btnRow2);

    root->AddChild(CreateButtonNode("Show All Pickers", COLOR_DARKBLUE,
        []() { SwitchDemoPage(DEMO_ALL); }, FULL_WIDTH, BUTTON_HEIGHT));
    AddLogArea(root);
    return root;
}

void SetGlobalContentHandle(ArkUI_NodeContentHandle handle) { g_contentHandle = handle; }

} // namespace NativeModule