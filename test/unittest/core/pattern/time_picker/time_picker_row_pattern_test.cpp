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
#include <cstdint>
#include <functional>
#include <optional>
#include <utility>

#include "gtest/gtest-message.h"
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/theme/icon_theme.h"
#include "core/components/button/button_theme.h"
#include "core/components/dialog/dialog_theme.h"

#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
namespace {
    const std::string COMMAND_SET_TIME_PICKER_TIME = "setTimePickerTime";
    const std::string COMMAND_INVALID = "invalidCommand";
    const std::string TIME_STR_VALID = "{\"hour\":10,\"minute\":30,\"second\":45}";
    const std::string TIME_STR_HOUR_12 = "{\"hour\":12,\"minute\":0,\"second\":0}";
    const std::string TIME_STR_HOUR_23 = "{\"hour\":23,\"minute\":59,\"second\":59}";
    const std::string TIME_STR_HOUR_0 = "{\"hour\":0,\"minute\":0,\"second\":0}";
    const std::string TIME_STR_HOUR_25 = "{\"hour\":25,\"minute\":0,\"second\":0}";
    const std::string TIME_STR_MINUTE_60 = "{\"hour\":10,\"minute\":60,\"second\":0}";
    const std::string TIME_STR_SECOND_60 = "{\"hour\":10,\"minute\":30,\"second\":60}";
    const std::string JSON_INVALID = "invalid json";
    const std::string JSON_NOT_OBJECT = "123";
    const std::string JSON_WITHOUT_CMD = "{\"params\":{\"hour\":10,\"minute\":30,\"second\":45}}";
    const std::string JSON_WITHOUT_PARAMS = "{\"cmd\":\"setTimePickerTime\"}";
    const std::string JSON_PARAMS_NOT_OBJECT = "{\"cmd\":\"setTimePickerTime\",\"params\":123}";
    const std::string JSON_PARAMS_WITHOUT_HOUR =
        "{\"cmd\":\"setTimePickerTime\",\"params\":{\"minute\":30,\"second\":45}}";
    const std::string JSON_PARAMS_WITHOUT_MINUTE =
        "{\"cmd\":\"setTimePickerTime\",\"params\":{\"hour\":10,\"second\":45}}";
    const std::string JSON_PARAMS_WITHOUT_SECOND =
        "{\"cmd\":\"setTimePickerTime\",\"params\":{\"hour\":10,\"minute\":30}}";
    const std::string JSON_PARAMS_INVALID_HOUR =
        "{\"cmd\":\"setTimePickerTime\",\"params\":{\"hour\":\"abc\",\"minute\":30,\"second\":45}}";
    const std::string JSON_VALID =
        "{\"cmd\":\"setTimePickerTime\",\"params\":{\"hour\":10,\"minute\":30,\"second\":45}}";
    const std::string DEFAULT_EVENT = "";
    const std::string DEFAULT_RESULT_SUCCESS = "success";
    const std::string DEFAULT_RESULT_FAIL = "fail";
    const std::string DEFAULT_REASON = "";
    } // namespace
namespace OHOS::Ace::NG {
const InspectorFilter filter;
class TimePickerRowPatternTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateTimePickerColumnNode();
    RefPtr<Theme> GetThemeByType(ThemeType type);

    RefPtr<IconTheme> iconThem_;
    RefPtr<DialogTheme> dialogTheme_;
    RefPtr<PickerTheme> pickerThem_;
    RefPtr<ButtonTheme> buttonTheme_;
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

void TimePickerRowPatternTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TimePickerRowPatternTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TimePickerRowPatternTest::SetUp()
{
    iconThem_ = AceType::MakeRefPtr<IconTheme>();
    dialogTheme_ = AceType::MakeRefPtr<DialogTheme>();
    pickerThem_ = MockThemeDefault::GetPickerTheme();
    buttonTheme_ = AceType::MakeRefPtr<ButtonTheme>();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);

    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly([this](ThemeType type) -> RefPtr<Theme> {return GetThemeByType(type);});

    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([this](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> {return GetThemeByType(type);});
}

void TimePickerRowPatternTest::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

RefPtr<Theme> TimePickerRowPatternTest::GetThemeByType(ThemeType type)
{
    if (type == IconTheme::TypeId()) {
        return iconThem_;
    } else if (type == DialogTheme::TypeId()) {
        return dialogTheme_;
    } else if (type == PickerTheme::TypeId()) {
        return pickerThem_;
    } else if (type == ButtonTheme::TypeId()) {
        return buttonTheme_;
    } else {
        return nullptr;
    }
}

/**
 * @tc.name: HandleHourBuildTimeRange001
 * @tc.desc: Test HandleHourBuildTimeRange when hour24 is true.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, HandleHourBuildTimeRange001, TestSize.Level0)
{
    /**
     * @tc.step: step1. create timepicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);

    /**
     * @tc.step: step2. set hour24 true.
     */
    timePickerRowPattern->SetHour24(true);
    timePickerRowPattern->RecordHourOptions();

    /**
     * @tc.step: step3. HandleHourBuildTimeRange.
     * @tc.expected: hour option size is 24.
     */
    timePickerRowPattern->HandleHourBuildTimeRange(1);
    auto options = timePickerRowPattern->options_[hourColumn];
    EXPECT_EQ(options.size(), 24);
}

/**
 * @tc.name: HandleHourBuildTimeRange002
 * @tc.desc: Test HandleHourBuildTimeRange when hour24 is false.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, HandleHourBuildTimeRange002, TestSize.Level0)
{
    /**
     * @tc.step: step1. create timepicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);

    /**
     * @tc.step: step2. set hour24 false.
     */
    timePickerRowPattern->SetHour24(false);
    timePickerRowPattern->RecordHourOptions();

    /**
     * @tc.step: step3. HandleHourBuildTimeRange.
     * @tc.expected: hour option size is 12.
     */
    timePickerRowPattern->HandleHourBuildTimeRange(1);
    auto options = timePickerRowPattern->options_[hourColumn];
    EXPECT_EQ(options.size(), 12);
}

/**
 * @tc.name: HandleMinuteBuildTimeRange001
 * @tc.desc: Test HandleMinuteBuildTimeRange at start hour.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, HandleMinuteBuildTimeRange001, TestSize.Level0)
{
    /**
     * @tc.step: step1. create timepicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);

    /**
     * @tc.step: step2. set start time.
     */
    PickerTime startTime = PickerTime(0, 1, 1);
    timePickerRowPattern->SetStartTime(startTime);

    /**
     * @tc.step: step3. test HandleMinuteBuildTimeRange at start hour.
     * @tc.expected: minute options size is 59 and starts from 1.
     */
    timePickerRowPattern->HandleMinuteBuildTimeRange(0, 0);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto options = timePickerRowPattern->options_[minuteColumn];
    EXPECT_EQ(options.size(), 59);
    EXPECT_EQ(options[0], "01");
}

/**
 * @tc.name: HandleMinuteBuildTimeRange002
 * @tc.desc: Test HandleMinuteBuildTimeRange at middle hour.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, HandleMinuteBuildTimeRange002, TestSize.Level0)
{
    /**
     * @tc.step: step1. create timepicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);

    /**
     * @tc.step: step2. test HandleMinuteBuildTimeRange at middle hour.
     * @tc.expected: minute options size is 60 and starts from 0.
     */
    timePickerRowPattern->HandleMinuteBuildTimeRange(12, 0);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto options = timePickerRowPattern->options_[minuteColumn];
    EXPECT_EQ(options.size(), 60);
    EXPECT_EQ(options[0], "00");
}

/**
 * @tc.name: HandleMinuteBuildTimeRange003
 * @tc.desc: Test HandleMinuteBuildTimeRange at end hour.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, HandleMinuteBuildTimeRange003, TestSize.Level0)
{
    /**
     * @tc.step: step1. create timepicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);

    /**
     * @tc.step: step2. set end time.
     */
    PickerTime endTime = PickerTime(22, 58, 58);
    timePickerRowPattern->SetEndTime(endTime);

    /**
     * @tc.step: step3. test HandleMinuteBuildTimeRange at end hour.
     * @tc.expected: minute options size is 59 and starts from 0.
     */
    timePickerRowPattern->HandleMinuteBuildTimeRange(22, 0);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto options = timePickerRowPattern->options_[minuteColumn];
    EXPECT_EQ(options.size(), 59);
    EXPECT_EQ(options[0], "00");
}

/**
 * @tc.name: GetHourColumnFormatString
 * @tc.desc: Test GetHourColumnFormatString zero prefix.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, GetHourColumnFormatString, TestSize.Level0)
{
    /**
     * @tc.step: step1. create timepicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    MockContainer::Current()->SetApiTargetVersion(20);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType autoType = ZeroPrefixType::AUTO;

    /**
     * @tc.step: step2. test GetHourColumnFormatString has zero prefix.
     * @tc.expected: GetHourColumnFormatString has zero prefix.
     */
    timePickerRowPattern->SetPrefixHour(showType);
    EXPECT_EQ(timePickerRowPattern->GetHourColumnFormatString(1), "01");

    /**
     * @tc.step: step3. test GetHourColumnFormatString dosen't have zero prefix.
     * @tc.expected: GetHourColumnFormatString dosen't have zero prefix.
     */
    timePickerRowPattern->SetPrefixHour(autoType);
    EXPECT_EQ(timePickerRowPattern->GetHourColumnFormatString(1), "1");

    /**
     * @tc.step: step4. test GetHourColumnFormatString has zero prefix when auto hour24 is true.
     * @tc.expected: GetHourColumnFormatString has zero prefix.
     */
    timePickerRowPattern->SetHour24(true);
    EXPECT_EQ(timePickerRowPattern->GetHourColumnFormatString(1), "01");
}

/**
 * @tc.name: GetSecondColumnFormatString
 * @tc.desc: Test GetSecondColumnFormatString zero prefix.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, GetSecondColumnFormatString, TestSize.Level0)
{
    /**
     * @tc.step: step1. create timepicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    MockContainer::Current()->SetApiTargetVersion(20);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    /**
     * @tc.step: step2. test GetSecondColumnFormatString has zero prefix.
     * @tc.expected: GetSecondColumnFormatString has zero prefix.
     */
    pickerProperty->UpdatePrefixSecond(2);
    EXPECT_EQ(timePickerRowPattern->GetSecondColumnFormatString(1), "01");

    /**
     * @tc.step: step3. test GetSecondColumnFormatString dosen't have zero prefix.
     * @tc.expected: GetSecondColumnFormatString dosen't have zero prefix.
     */
    pickerProperty->UpdatePrefixSecond(1);
    EXPECT_EQ(timePickerRowPattern->GetSecondColumnFormatString(1), "1");
}

/**
 * @tc.name: GetMinuteColumnFormatString
 * @tc.desc: Test GetMinuteColumnFormatString zero prefix.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, GetMinuteColumnFormatString, TestSize.Level0)
{
    /**
     * @tc.step: step1. create timepicker.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    MockContainer::Current()->SetApiTargetVersion(20);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);

    /**
     * @tc.step: step2. test GetMinuteColumnFormatString has zero prefix.
     * @tc.expected: GetMinuteColumnFormatString has zero prefix.
     */
    pickerProperty->UpdatePrefixMinute(2);
    EXPECT_EQ(timePickerRowPattern->GetMinuteColumnFormatString(1), "01");

    /**
     * @tc.step: step3. test GetMinuteColumnFormatString dosen't have zero prefix.
     * @tc.expected: GetMinuteColumnFormatString dosen't have zero prefix.
     */
    pickerProperty->UpdatePrefixMinute(1);
    EXPECT_EQ(timePickerRowPattern->GetMinuteColumnFormatString(1), "1");
}

/**
 * @tc.name: TimePickerPatterntest001
 * @tc.desc: Test ColumnPatternInitHapticController.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, TimePickerPatterntest001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    timePickerRowPattern->isHapticChanged_ = true;
    timePickerRowPattern->UpdateAllChildNode();
    timePickerRowPattern->ColumnPatternInitHapticController();
    EXPECT_FALSE(timePickerRowPattern->isHapticChanged_);
}
 
 /**
  * @tc.name: TimePickerPatterntest002
  * @tc.desc: Test ColumnPatternStopHaptic.
  * @tc.type: FUNC
  */
HWTEST_F(TimePickerRowPatternTest, TimePickerPatterntest002, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    timePickerRowPattern->isEnableHaptic_ = true;
    timePickerRowPattern->UpdateAllChildNode();
    timePickerRowPattern->ColumnPatternStopHaptic();
    auto host = timePickerRowPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto children = host->GetChildren();
    for (const auto& child : children) {
        auto stackNode = AceType::DynamicCast<FrameNode>(child);
        ASSERT_NE(stackNode, nullptr);
        auto blendNode = AceType::DynamicCast<FrameNode>(stackNode->GetLastChild());
        ASSERT_NE(blendNode, nullptr);
        auto childNode = blendNode->GetLastChild();
        ASSERT_NE(childNode, nullptr);
        auto datePickerColumnPattern =
            AceType::DynamicCast<FrameNode>(childNode)->GetPattern<TimePickerColumnPattern>();
        ASSERT_NE(datePickerColumnPattern, nullptr);
        datePickerColumnPattern->StopHaptic();
        ASSERT_TRUE(datePickerColumnPattern->stopHaptic_);
    }
}

/**
 * @tc.name: TimePickerPatternToJsonValue001
 * @tc.desc: Test TimePickerRowPattern ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, TimePickerRowPatternToJsonValue001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    /**
     * @tc.steps: step1. set option value.
     */
    PickerTime startTime = PickerTime(0, 1, 1);
    PickerTime endTime = PickerTime(22, 58, 58);
    bool isEnableHaptic = true;
    timePickerRowPattern->SetStartTime(startTime);
    timePickerRowPattern->SetEndTime(endTime);
    timePickerRowPattern->SetIsEnableHaptic(isEnableHaptic);

    /**
     * @tc.steps: step2. call tojsonvalue funtion.
     */
    auto json = JsonUtil::Create(true);
    timePickerRowPattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("start"), startTime.ToString(false, false).c_str());
    EXPECT_EQ(json->GetString("end"), endTime.ToString(false, false).c_str());
    EXPECT_TRUE(json->GetBool("enableHapticFeedback"));
}

/**
 * @tc.name: TimePickerPatternToJsonValue002
 * @tc.desc: Test TimePickerRowPattern ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, TimePickerRowPatternToJsonValue002, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    auto pickerTheme = MockThemeDefault::GetPickerTheme();
    ASSERT_NE(pickerTheme, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    /**
     * @tc.steps: step1. set option value.
     */
    PickerTime startTime = PickerTime(0, 0, 0);
    PickerTime endTime = PickerTime(23, 59, 59);
    bool isEnableHaptic = true;

    /**
     * @tc.steps: step2. call tojsonvalue funtion and judge default value.
     */
    auto json = JsonUtil::Create(true);
    timePickerRowPattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("start"), startTime.ToString(false, false).c_str());
    EXPECT_EQ(json->GetString("end"), endTime.ToString(false, false).c_str());
    EXPECT_EQ(json->GetBool("enableHapticFeedback"), isEnableHaptic);
}


/**
 * @tc.name: OnInjectionEvent_InvalidJson
 * @tc.desc: OnInjectionEvent should return RET_FAILED when JSON is invalid.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, OnInjectionEvent_InvalidJson, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto result = timePickerRowPattern->OnInjectionEvent(JSON_INVALID);
    EXPECT_EQ(result, RET_FAILED);
}

/**
 * @tc.name: OnInjectionEvent_JsonNotObject
 * @tc.desc: OnInjectionEvent should return RET_FAILED when JSON is not an object.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, OnInjectionEvent_JsonNotObject, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto result = timePickerRowPattern->OnInjectionEvent(JSON_NOT_OBJECT);
    EXPECT_EQ(result, RET_FAILED);
}

/**
 * @tc.name: OnInjectionEvent_InvalidCommand
 * @tc.desc: OnInjectionEvent should return RET_FAILED when command is not setTimePickerTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, OnInjectionEvent_InvalidCommand, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    std::string invalidCmdJson = "{\"cmd\":\"invalidCommand\",\"params\":{\"hour\":10,\"minute\":30,\"second\":45}}";
    auto result = timePickerRowPattern->OnInjectionEvent(invalidCmdJson);
    EXPECT_EQ(result, RET_FAILED);
}

/**
 * @tc.name: OnInjectionEvent_MissingParams
 * @tc.desc: OnInjectionEvent should return RET_FAILED when params are missing.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, OnInjectionEvent_MissingParams, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto result = timePickerRowPattern->OnInjectionEvent(JSON_WITHOUT_PARAMS);
    EXPECT_EQ(result, RET_FAILED);
}

/**
 * @tc.name: OnInjectionEvent_ParamsNotObject
 * @tc.desc: OnInjectionEvent should return RET_FAILED when params is not an object.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, OnInjectionEvent_ParamsNotObject, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto result = timePickerRowPattern->OnInjectionEvent(JSON_PARAMS_NOT_OBJECT);
    EXPECT_EQ(result, RET_FAILED);
}

/**
 * @tc.name: OnInjectionEvent_MissingHour
 * @tc.desc: OnInjectionEvent should return RET_FAILED when hour is missing.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, OnInjectionEvent_MissingHour, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto result = timePickerRowPattern->OnInjectionEvent(JSON_PARAMS_WITHOUT_HOUR);
    EXPECT_EQ(result, RET_FAILED);
}

/**
 * @tc.name: OnInjectionEvent_MissingMinute
 * @tc.desc: OnInjectionEvent should return RET_FAILED when minute is missing.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, OnInjectionEvent_MissingMinute, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto result = timePickerRowPattern->OnInjectionEvent(JSON_PARAMS_WITHOUT_MINUTE);
    EXPECT_EQ(result, RET_FAILED);
}

/**
 * @tc.name: OnInjectionEvent_MissingSecond
 * @tc.desc: OnInjectionEvent should return RET_FAILED when second is missing.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, OnInjectionEvent_MissingSecond, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto result = timePickerRowPattern->OnInjectionEvent(JSON_PARAMS_WITHOUT_SECOND);
    EXPECT_EQ(result, RET_FAILED);
}

/**
 * @tc.name: OnInjectionEvent_HourOutOfRange
 * @tc.desc: OnInjectionEvent should return RET_FAILED when hour is out of valid range.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, OnInjectionEvent_HourOutOfRange, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    std::string jsonHourOutOfRange =
        "{\"cmd\":\"setTimePickerTime\",\"params\":{\"hour\":25,\"minute\":30,\"second\":45}}";
    auto result = timePickerRowPattern->OnInjectionEvent(jsonHourOutOfRange);
    EXPECT_EQ(result, RET_FAILED);
}

/**
 * @tc.name: OnInjectionEvent_MinuteOutOfRange
 * @tc.desc: OnInjectionEvent should return RET_FAILED when minute is out of valid range.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, OnInjectionEvent_MinuteOutOfRange, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    std::string jsonMinuteOutOfRange =
        "{\"cmd\":\"setTimePickerTime\",\"params\":{\"hour\":10,\"minute\":60,\"second\":45}}";
    auto result = timePickerRowPattern->OnInjectionEvent(jsonMinuteOutOfRange);
    EXPECT_EQ(result, RET_FAILED);
}

/**
 * @tc.name: OnInjectionEvent_SecondOutOfRange
 * @tc.desc: OnInjectionEvent should return RET_FAILED when second is out of valid range.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, OnInjectionEvent_SecondOutOfRange, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    std::string jsonSecondOutOfRange =
        "{\"cmd\":\"setTimePickerTime\",\"params\":{\"hour\":10,\"minute\":30,\"second\":60}}";
    auto result = timePickerRowPattern->OnInjectionEvent(jsonSecondOutOfRange);
    EXPECT_EQ(result, RET_FAILED);
}

/**
 * @tc.name: OnInjectionEvent_TimeBelowStartTime
 * @tc.desc: OnInjectionEvent should return RET_FAILED when time is below start time.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, OnInjectionEvent_TimeBelowStartTime, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->SetStartTime(PickerTime(10, 0, 0));
    timePickerRowPattern->SetEndTime(PickerTime(20, 0, 0));

    std::string jsonTimeBelowStart =
        "{\"cmd\":\"setTimePickerTime\",\"params\":{\"hour\":5,\"minute\":0,\"second\":0}}";
    auto result = timePickerRowPattern->OnInjectionEvent(jsonTimeBelowStart);
    EXPECT_EQ(result, RET_FAILED);
}

/**
 * @tc.name: OnInjectionEvent_TimeAboveEndTime
 * @tc.desc: OnInjectionEvent should return RET_FAILED when time is above end time.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, OnInjectionEvent_TimeAboveEndTime, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->SetStartTime(PickerTime(10, 0, 0));
    timePickerRowPattern->SetEndTime(PickerTime(20, 0, 0));

    std::string jsonTimeAboveEnd = "{\"cmd\":\"setTimePickerTime\",\"params\":{\"hour\":22,\"minute\":0,\"second\":0}}";
    auto result = timePickerRowPattern->OnInjectionEvent(jsonTimeAboveEnd);
    EXPECT_EQ(result, RET_FAILED);
}

/**
 * @tc.name: OnInjectionEvent_ValidTime
 * @tc.desc: OnInjectionEvent should return RET_SUCCESS when all parameters are valid.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, OnInjectionEvent_ValidTime, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->SetStartTime(PickerTime(0, 0, 0));
    timePickerRowPattern->SetEndTime(PickerTime(23, 59, 59));

    auto result = timePickerRowPattern->OnInjectionEvent(JSON_VALID);
    EXPECT_EQ(result, RET_SUCCESS);

    auto selectedTime = timePickerRowPattern->GetSelectedTime();
    EXPECT_EQ(selectedTime.GetHour(), static_cast<uint32_t>(10));
    EXPECT_EQ(selectedTime.GetMinute(), static_cast<uint32_t>(30));
    EXPECT_EQ(selectedTime.GetSecond(), static_cast<uint32_t>(45));
}

/**
 * @tc.name: OnInjectionEvent_ValidTimeBoundaryHour0
 * @tc.desc: OnInjectionEvent should succeed with hour set to minimum valid value (0).
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, OnInjectionEvent_ValidTimeBoundaryHour0, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->SetStartTime(PickerTime(0, 0, 0));
    timePickerRowPattern->SetEndTime(PickerTime(23, 59, 59));

    std::string jsonHour0 = "{\"cmd\":\"setTimePickerTime\",\"params\":{\"hour\":0,\"minute\":0,\"second\":0}}";
    auto result = timePickerRowPattern->OnInjectionEvent(jsonHour0);
    EXPECT_EQ(result, RET_SUCCESS);
}

/**
 * @tc.name: OnInjectionEvent_ValidTimeBoundaryHour23
 * @tc.desc: OnInjectionEvent should succeed with hour set to maximum valid value (23).
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, OnInjectionEvent_ValidTimeBoundaryHour23, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->SetStartTime(PickerTime(0, 0, 0));
    timePickerRowPattern->SetEndTime(PickerTime(23, 59, 59));

    std::string jsonHour23 = "{\"cmd\":\"setTimePickerTime\",\"params\":{\"hour\":23,\"minute\":59,\"second\":59}}";
    auto result = timePickerRowPattern->OnInjectionEvent(jsonHour23);
    EXPECT_EQ(result, RET_SUCCESS);
}

/**
 * @tc.name: ReportTimeChangeEvent_NormalCase
 * @tc.desc: ReportTimeChangeEvent should return true with valid time string.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, ReportTimeChangeEvent_NormalCase, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    int32_t nodeId = frameNode->GetId();
    auto result = timePickerRowPattern->ReportTimeChangeEvent(nodeId, TIME_STR_VALID);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ReportTimeChangeEvent_Hour12
 * @tc.desc: ReportTimeChangeEvent should succeed with hour 12.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, ReportTimeChangeEvent_Hour12, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    int32_t nodeId = frameNode->GetId();
    auto result = timePickerRowPattern->ReportTimeChangeEvent(nodeId, TIME_STR_HOUR_12);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ReportCommandResult_Success
 * @tc.desc: ReportCommandResult should return true when reporting success.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, ReportCommandResult_Success, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    int32_t nodeId = frameNode->GetId();
    auto result = timePickerRowPattern->ReportCommandResult(
        nodeId, COMMAND_SET_TIME_PICKER_TIME, DEFAULT_RESULT_SUCCESS, DEFAULT_REASON);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ReportCommandResult_FailWithReason
 * @tc.desc: ReportCommandResult should return true when reporting failure with reason.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, ReportCommandResult_FailWithReason, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    int32_t nodeId = frameNode->GetId();
    std::string reason = "invalidTimeParameters";
    auto result =
        timePickerRowPattern->ReportCommandResult(nodeId, COMMAND_SET_TIME_PICKER_TIME, DEFAULT_RESULT_FAIL, reason);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ReportCommandResult_EmptyReason
 * @tc.desc: ReportCommandResult should return true when reason is empty.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, ReportCommandResult_EmptyReason, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    int32_t nodeId = frameNode->GetId();
    auto result =
        timePickerRowPattern->ReportCommandResult(nodeId, DEFAULT_EVENT, DEFAULT_RESULT_SUCCESS, DEFAULT_REASON);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ValidateTimeParameters_InvalidJson
 * @tc.desc: ValidateTimeParameters should return false when json is invalid.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, ValidateTimeParameters_InvalidJson, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    int32_t hour = 0;
    int32_t minute = 0;
    int32_t second = 0;
    auto invalidJson = JsonUtil::ParseJsonString(JSON_INVALID);
    auto result = timePickerRowPattern->ValidateTimeParameters(invalidJson, hour, minute, second);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ValidateTimeParameters_ValidTimeInRange
 * @tc.desc: ValidateTimeParameters should return true when time is within valid range.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTest, ValidateTimeParameters_ValidTimeInRange, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->SetStartTime(PickerTime(0, 0, 0));
    timePickerRowPattern->SetEndTime(PickerTime(23, 59, 59));

    int32_t hour = 0;
    int32_t minute = 0;
    int32_t second = 0;
    auto validJson = JsonUtil::ParseJsonString(TIME_STR_VALID);
    auto result = timePickerRowPattern->ValidateTimeParameters(validJson, hour, minute, second);
    EXPECT_TRUE(result);
    EXPECT_EQ(hour, 10);
    EXPECT_EQ(minute, 30);
    EXPECT_EQ(second, 45);
}

} // namespace OHOS::Ace::NG
