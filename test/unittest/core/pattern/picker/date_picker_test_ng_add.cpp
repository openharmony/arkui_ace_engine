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

#include "gtest/gtest.h"
#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr double PATTERN_OFFSET = 1000;
constexpr double TEST_FONT_SIZE = 10.0;
constexpr int32_t START_YEAR_BEFORE = 1990;
constexpr int32_t START_YEAR = 1980;
constexpr int32_t SELECTED_YEAR = 2000;
constexpr int32_t END_YEAR = 2090;
constexpr int32_t CURRENT_DAY = 5;
const int ENORMOUS_SHOWCOUNT = 7;
const int HUGE_SHOWCOUNT = 6;
const int BIG_SHOWCOUNT = 5;
const int MEDIUM_SHOWCOUNT = 4;
const int SMALL_SHOWCOUNT = 3;
const vector<int> DEFAULT_DATE = { 1999, 9, 9 };
const std::string CONNECTER = "-";
const std::vector<int> DEFAULT_VALUE = { 1970, 1971, 1972 };
const SizeF TEST_FRAME_SIZE1 { 20, 50 };
const SizeF TEST_FRAME_SIZE2 { 0, 0 };
const std::string SELECTED_DATE_STRING = R"({"year":2000,"month":5,"day":6,"hour":1,"minute":1,"status":-1})";
const std::string AM = "AM ";
const std::string COLON = ":";
const std::string ZERO = "0";
const std::string SPACE = " ";
void InitDatePickerSettingData(DatePickerSettingData& settingData)
{
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(END_YEAR, 1, 1);
    settingData.datePickerProperty["selected"] = PickerDate(SELECTED_YEAR, 1, 1);
    settingData.isLunar = false;
    settingData.showTime = true;
    settingData.useMilitary = false;
}

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

class DatePickerTestNgAdd : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateDatePickerColumnNode();

    RefPtr<FrameNode> columnNode_;
    RefPtr<DatePickerColumnPattern> columnPattern_;
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

void DatePickerTestNgAdd::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void DatePickerTestNgAdd::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void DatePickerTestNgAdd::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void DatePickerTestNgAdd::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void DatePickerTestNgAdd::CreateDatePickerColumnNode()
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto stackNode = AceType::DynamicCast<FrameNode>(frameNode->GetFirstChild());
    ASSERT_NE(stackNode, nullptr);
    auto blendNode = AceType::DynamicCast<FrameNode>(stackNode->GetLastChild());
    ASSERT_NE(blendNode, nullptr);
    columnNode_ = AceType::DynamicCast<FrameNode>(blendNode->GetLastChild());
    ASSERT_NE(columnNode_, nullptr);
    columnNode_->MarkModifyDone();
    columnPattern_ = columnNode_->GetPattern<DatePickerColumnPattern>();
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->OnAttachToFrameNode();
}

/**
 * @tc.name: DatePickerDialogViewShow0028
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0028, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(3, 6, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        columnValueText + SPACE + AM + std::to_string(SMALL_SHOWCOUNT) + COLON + std::to_string(HUGE_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0029
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0029, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(4, 7, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), columnValueText + SPACE + AM + ZERO + std::to_string(MEDIUM_SHOWCOUNT) +
                                                    COLON + std::to_string(ENORMOUS_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0030
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0030, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(4, 7, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), columnValueText + SPACE + AM + ZERO + std::to_string(MEDIUM_SHOWCOUNT) +
                                                    COLON + ZERO + std::to_string(ENORMOUS_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0031
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0031, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(4, 7, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), columnValueText + SPACE + AM + std::to_string(MEDIUM_SHOWCOUNT) +
                                                    COLON + ZERO + std::to_string(ENORMOUS_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0032
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0032, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(4, 7, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        columnValueText + SPACE + AM + std::to_string(MEDIUM_SHOWCOUNT) + COLON + std::to_string(ENORMOUS_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0033
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0033, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(4, 4, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), columnValueText + SPACE + AM + ZERO + std::to_string(MEDIUM_SHOWCOUNT) +
                                                    COLON + std::to_string(MEDIUM_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0034
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0034, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(4, 4, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), columnValueText + SPACE + AM + ZERO + std::to_string(MEDIUM_SHOWCOUNT) +
                                                    COLON + ZERO + std::to_string(MEDIUM_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0035
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0035, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(4, 4, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), columnValueText + SPACE + AM + std::to_string(MEDIUM_SHOWCOUNT) +
                                                    COLON + ZERO + std::to_string(MEDIUM_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0036
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0036, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(4, 4, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        columnValueText + SPACE + AM + std::to_string(MEDIUM_SHOWCOUNT) + COLON + std::to_string(MEDIUM_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0037
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0037, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(4, 5, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        columnValueText + SPACE + AM + ZERO + std::to_string(MEDIUM_SHOWCOUNT) + COLON + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0038
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0038, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(4, 5, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), columnValueText + SPACE + AM + ZERO + std::to_string(MEDIUM_SHOWCOUNT) +
                                                    COLON + ZERO + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0039
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0039, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(4, 5, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        columnValueText + SPACE + AM + std::to_string(MEDIUM_SHOWCOUNT) + COLON + ZERO + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0040
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0040, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(4, 5, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        columnValueText + SPACE + AM + std::to_string(MEDIUM_SHOWCOUNT) + COLON + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0041
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0041, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(4, 6, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), columnValueText + SPACE + AM + ZERO + std::to_string(MEDIUM_SHOWCOUNT) +
                                                    COLON + std::to_string(HUGE_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0042
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0042, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(4, 6, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), columnValueText + SPACE + AM + ZERO + std::to_string(MEDIUM_SHOWCOUNT) +
                                                    COLON + ZERO + std::to_string(HUGE_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0043
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0043, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(4, 6, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), columnValueText + SPACE + AM + std::to_string(MEDIUM_SHOWCOUNT) +
                                                    COLON + ZERO + std::to_string(HUGE_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0044
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0044, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(4, 6, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        columnValueText + SPACE + AM + std::to_string(MEDIUM_SHOWCOUNT) + COLON + std::to_string(HUGE_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0045
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0045, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(5, 5, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        columnValueText + SPACE + AM + ZERO + std::to_string(BIG_SHOWCOUNT) + COLON + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0046
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0046, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(5, 5, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), columnValueText + SPACE + AM + ZERO + std::to_string(BIG_SHOWCOUNT) +
                                                    COLON + ZERO + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0047
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0047, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(5, 5, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::SHOW;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        columnValueText + SPACE + AM + std::to_string(BIG_SHOWCOUNT) + COLON + ZERO + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0048
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0048, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(5, 5, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);
    /**
     * @tc.steps2: Test the time of timePicker.
     * @tc.expected: The texts of timePicker are equal to selected time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();

    auto timePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(1));
    auto accessibilityProperty = timePickerNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(),
        columnValueText + SPACE + AM + std::to_string(BIG_SHOWCOUNT) + COLON + std::to_string(BIG_SHOWCOUNT));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: DatePickerDialogViewShow0049
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0049, TestSize.Level1)
{
    DatePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::RED;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(TEST_FONT_SIZE);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.normalTextStyle_.textColor = Color::RED;
    settingData.properties.normalTextStyle_.fontSize = Dimension(TEST_FONT_SIZE);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;

    settingData.properties.selectedTextStyle_.textColor = Color::RED;
    settingData.properties.selectedTextStyle_.fontSize = Dimension(TEST_FONT_SIZE);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.datePickerProperty["start"] = PickerDate(START_YEAR_BEFORE, 1, 1);
    settingData.datePickerProperty["end"] = PickerDate(START_YEAR, CURRENT_DAY, 1);
    settingData.datePickerProperty["selected"] = PickerDate(END_YEAR, 1, 1);
    settingData.timePickerProperty["selected"] = PickerTime(1, 1, 1);
    settingData.isLunar = true;
    settingData.showTime = true;
    settingData.useMilitary = false;

    DialogProperties dialogProperties;

    std::map<std::string, NG::DialogEvent> dialogEvent;
    auto eventFunc = [](const std::string& info) { (void)info; };
    dialogEvent["changeId"] = eventFunc;
    dialogEvent["acceptId"] = eventFunc;
    auto cancelFunc = [](const GestureEvent& info) { (void)info; };
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    dialogCancelEvent["cancelId"] = cancelFunc;

    std::vector<ButtonInfo> buttonInfos;
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);

    ASSERT_NE(dialogNode, nullptr);
    auto midStackNode =
        AceType::DynamicCast<FrameNode>(dialogNode->GetFirstChild()->GetFirstChild()->GetChildAtIndex(1));
    auto dateNode = AceType::DynamicCast<FrameNode>(midStackNode->GetLastChild()->GetFirstChild());
    auto columnNode = AceType::DynamicCast<FrameNode>(dateNode->GetFirstChild()->GetChildAtIndex(1)->GetLastChild());
    auto columnPattern = columnNode->GetPattern<DatePickerColumnPattern>();
    columnPattern->SetCurrentIndex(0);
    columnPattern->UpdateToss(PATTERN_OFFSET);

    auto timePickerSwitchEvent =
        DatePickerDialogView::CreateAndSetTimePickerSwitchEvent(midStackNode, dateNode, columnNode);
    int32_t setApiVersion = 11;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto dialogViewNode =
        DatePickerDialogView::CreateNextPrevButtonNode(timePickerSwitchEvent, dateNode, buttonInfos, columnNode);
    ASSERT_NE(dialogNode, nullptr);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
    dialogViewNode =
        DatePickerDialogView::CreateNextPrevButtonNode(timePickerSwitchEvent, dateNode, buttonInfos, columnNode);
    ASSERT_NE(dialogNode, nullptr);
}

/**
 * @tc.name: DatePickerDialogViewShow0050
 * @tc.desc: Test DatePickerDialogView Show.
 * @tc.type: FUNC
 */
HWTEST_F(DatePickerTestNgAdd, DatePickerDialogViewShow0050, TestSize.Level1)
{
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    /**
     * @tc.steps: steps1. creat timePickerDialog with dateTimeOptions
     */
    DatePickerSettingData settingData;
    InitDatePickerSettingData(settingData);
    settingData.timePickerProperty["selected"] = PickerTime(3, 3, 1);
    settingData.dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    settingData.dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
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
    info1.fontWeight = FontWeight::W400;
    buttonInfos.push_back(info1);
    auto dialogNode =
        DatePickerDialogView::Show(dialogProperties, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
    ASSERT_NE(dialogNode, nullptr);

    /**
     * @tc.steps2: Test the date and time of datePicker.
     * @tc.expected: The texts of datePicker are equal to selected  date and time
     */
    auto dialogPattern = dialogNode->GetPattern<DialogPattern>();
    auto customNode = dialogPattern->GetCustomNode();
    auto pickerStack = AceType::DynamicCast<NG::FrameNode>(customNode->GetChildAtIndex(1));
    auto pickerRow = AceType::DynamicCast<NG::FrameNode>(pickerStack->GetChildAtIndex(1));

    auto datePickerNode = AceType::DynamicCast<NG::FrameNode>(pickerRow->GetChildAtIndex(0));
    ASSERT_NE(datePickerNode, nullptr);
    auto stackMonthDays = AceType::DynamicCast<FrameNode>(datePickerNode->GetFirstChild());
    ASSERT_NE(stackMonthDays, nullptr);
    auto blendMonthDays = AceType::DynamicCast<FrameNode>(stackMonthDays->GetLastChild());
    ASSERT_NE(blendMonthDays, nullptr);
    auto monthDaysColumnNode = AceType::DynamicCast<FrameNode>(blendMonthDays->GetLastChild());
    ASSERT_NE(monthDaysColumnNode, nullptr);
    auto columnAccessibilityProperty =
        monthDaysColumnNode->GetAccessibilityProperty<DatePickerColumnAccessibilityProperty>();
    ASSERT_NE(columnAccessibilityProperty, nullptr);
    auto columnValueText = columnAccessibilityProperty->GetText();
    auto textDateTime =
        columnValueText + SPACE + AM + ZERO + std::to_string(SMALL_SHOWCOUNT) + COLON + std::to_string(SMALL_SHOWCOUNT);
    auto accessibilityPropertyDate = datePickerNode->GetAccessibilityProperty<DatePickerAccessibilityProperty>();
    ASSERT_NE(accessibilityPropertyDate, nullptr);
    EXPECT_EQ(accessibilityPropertyDate->GetText(), textDateTime);
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

} // namespace OHOS::Ace::NG
