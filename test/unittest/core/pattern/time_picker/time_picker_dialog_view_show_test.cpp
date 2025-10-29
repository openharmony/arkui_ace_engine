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
const int CURRENT_VALUE1 = 3;
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
class TimePickerDialogViewShowTest : public testing::Test {
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

void TimePickerDialogViewShowTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TimePickerDialogViewShowTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TimePickerDialogViewShowTest::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TimePickerDialogViewShowTest::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: TimePickerDialogViewShow001
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow001, TestSize.Level0)
{
    TimePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::RED;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(0);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.normalTextStyle_.textColor = Color::RED;
    settingData.properties.normalTextStyle_.fontSize = Dimension(0);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.selectedTextStyle_.textColor = Color::RED;
    settingData.properties.selectedTextStyle_.fontSize = Dimension(0);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.isUseMilitaryTime = false;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(1, 1, 1);

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
}

/**
 * @tc.name: TimePickerDialogViewShow002
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow002, TestSize.Level1)
{
    TimePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::GREEN;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(1);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::NORMAL;

    settingData.properties.normalTextStyle_.textColor = Color::GREEN;
    settingData.properties.normalTextStyle_.fontSize = Dimension(1);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::NORMAL;

    settingData.properties.selectedTextStyle_.textColor = Color::GREEN;
    settingData.properties.selectedTextStyle_.fontSize = Dimension(1);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::NORMAL;
    settingData.isUseMilitaryTime = true;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(2, 2, 2);

    DialogProperties dialogProperties;

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.type = std::make_optional<ButtonType>(ButtonType::CAPSULE);
    buttonInfos.push_back(info1);

    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
}

/**
 * @tc.name: TimePickerDialogViewShow003
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow003, TestSize.Level0)
{
    TimePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::RED;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(0);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.normalTextStyle_.textColor = Color::RED;
    settingData.properties.normalTextStyle_.fontSize = Dimension(0);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.selectedTextStyle_.textColor = Color::RED;
    settingData.properties.selectedTextStyle_.fontSize = Dimension(0);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.isUseMilitaryTime = false;

    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(1, 1, 1);

    DialogProperties dialogProperties;

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.type = std::make_optional<ButtonType>(ButtonType::CAPSULE);
    buttonInfos.push_back(info1);

    auto dialogNode = TimePickerDialogView::Show(
        dialogProperties, settingData, buttonInfos, timePickerProperty, dialogEvent, dialogCancelEvent);
    EXPECT_NE(dialogNode, nullptr);
}

/**
 * @tc.name: TimePickerDialogViewShow004
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow004, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    TimePickerSettingData settingData;
    settingData.isUseMilitaryTime = false;
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    std::map<std::string, PickerTime> timePickerProperty;
    timePickerProperty["selected"] = PickerTime(3, 3, 1);
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
        AM + ZERO + std::to_string(CURRENT_VALUE1) + COLON + std::to_string(CURRENT_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow005
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow005, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(3, 3, 1);
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
        AM + ZERO + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow006
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow006, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(3, 3, 1);
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
        AM + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow007
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow007, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(3, 3, 1);
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
        AM + std::to_string(CURRENT_VALUE1) + COLON + std::to_string(CURRENT_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow008
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow008, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(3, 4, 1);
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
        AM + ZERO + std::to_string(CURRENT_VALUE1) + COLON + std::to_string(CURRENT_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow009
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow009, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(3, 4, 1);
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
        AM + ZERO + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow010
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow010, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(3, 4, 1);
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
        AM + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow011
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow011, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(3, 4, 1);
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
        AM + std::to_string(CURRENT_VALUE1) + COLON + std::to_string(CURRENT_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow012
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow012, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(3, 5, 1);
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
        AM + ZERO + std::to_string(CURRENT_VALUE1) + COLON + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow013
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow013, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(3, 5, 1);
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
        AM + ZERO + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow014
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow014, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(3, 5, 1);
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
        AM + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow015
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow015, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(3, 5, 1);
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
        AM + std::to_string(CURRENT_VALUE1) + COLON + std::to_string(CURRENT_VALUE4));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow016
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow016, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(3, 6, 1);
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
        AM + ZERO + std::to_string(CURRENT_VALUE1) + COLON + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow017
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow017, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(3, 6, 1);
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
        AM + ZERO + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow018
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow018, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(3, 6, 1);
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
        AM + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow019
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow019, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(3, 6, 1);
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
        AM + std::to_string(CURRENT_VALUE1) + COLON + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow020
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow020, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(5, 6, 1);
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
        AM + ZERO + std::to_string(CURRENT_VALUE4) + COLON + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow021
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow021, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(5, 6, 1);
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
        AM + ZERO + std::to_string(CURRENT_VALUE4) + COLON + ZERO + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow022
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow022, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(5, 6, 1);
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
        AM + std::to_string(CURRENT_VALUE4) + COLON + ZERO + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow023
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow023, TestSize.Level0)
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
    timePickerProperty["selected"] = PickerTime(5, 6, 1);
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
        AM + std::to_string(CURRENT_VALUE4) + COLON + std::to_string(CURRENT_VALUE5));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow024
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow024, TestSize.Level0)
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
        AM + ZERO + std::to_string(CURRENT_VALUE3) + COLON + std::to_string(CURRENT_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerDialogViewShow025
 * @tc.desc: Test TimePickerDialogViewShow Show.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDialogViewShowTest, TimePickerDialogViewShow025, TestSize.Level0)
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
        AM + ZERO + std::to_string(CURRENT_VALUE3) + COLON + ZERO + std::to_string(CURRENT_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}
} // namespace OHOS::Ace::NG
