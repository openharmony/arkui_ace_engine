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

#include <cstdint>
#include <functional>
#include <optional>
#include <utility>

#include "gtest/gtest-message.h"
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const int CURRENT_VALUE3 = 4;
const int CURRENT_VALUE4 = 5;
const int CURRENT_VALUE5 = 6;
const std::string AM = "AM ";
const std::string COLON = ":";
const std::string ZERO = "0";
RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == IconTheme::TypeId()) {
        return AceType::MakeRefPtr<IconTheme>();
    } else if (type == DialogTheme::TypeId()) {
        return AceType::MakeRefPtr<DialogTheme>();
    } else if (type == PickerTheme::TypeId()) {
        return MockThemeDefault::GetPickerTheme();
    } else if (type == ButtonTheme::TypeId()) {
        return AceType::MakeRefPtr<ButtonTheme>();
    } else {
        return nullptr;
    }
}
} // namespace
class TimePickerDialogViewShowTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

    RefPtr<FrameNode> columnNode_;
    RefPtr<TimePickerColumnPattern> columnPattern_;
};

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto spanNode = MakeRefPtr<TestNode>(nodeId);
        return spanNode;
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
};

void TimePickerDialogViewShowTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TimePickerDialogViewShowTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TimePickerDialogViewShowTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TimePickerDialogViewShowTestNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: TimePickerDialogViewShow026
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow026, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 4, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE3) + COLON + ZERO + std::to_string(CURRENT_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow027
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow027, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 4, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE3) + COLON + std::to_string(CURRENT_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow028
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow028, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE3) + COLON + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow029
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow029, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE3) + COLON + ZERO + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow030
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow030, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE3) + COLON + ZERO + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow031
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow031, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE3) + COLON + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow032
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow032, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE3) + COLON + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow033
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow033, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE3) + COLON + ZERO + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow034
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow034, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE3) + COLON + ZERO + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow035
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow035, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(4, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE3) + COLON + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow036
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow036, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(5, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE4) + COLON + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow037
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow037, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(5, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE4) + COLON + ZERO + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow038
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow038, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(5, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE4) + COLON + ZERO + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow039
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow039, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(5, 5, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE4) + COLON + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow040
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow040, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(6, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE5) + COLON + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow041
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow041, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(6, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE5) + COLON + ZERO + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow042
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow042, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(6, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE5) + COLON + ZERO + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow043
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTestNg, TimePickerDialogViewShow043, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(6, 6, 1);
    DialogProperties dialogProperties;
    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;
    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE5) + COLON + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}
} // namespace OHOS::Ace::NG
