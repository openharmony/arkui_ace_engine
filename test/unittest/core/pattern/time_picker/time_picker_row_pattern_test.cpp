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
#include "core/components/picker/picker_theme.h"
#include "core/components/button/button_theme.h"
#include "core/components/dialog/dialog_theme.h"

#include "core/components/picker/picker_data.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

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
} // namespace OHOS::Ace::NG
