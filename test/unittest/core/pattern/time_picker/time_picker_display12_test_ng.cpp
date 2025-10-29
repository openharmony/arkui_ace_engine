/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const int CURRENT_INDEX_VALUE1 = 3;
const int CURRENT_INDEX_VALUE2 = 4;
const int CURRENT_INDEX_VALUE3 = 5;
const std::string AM = "AM ";
const std::string PM = "PM ";
const std::string COLON = ":";
const std::string ZERO = "0";
const PickerTime TIME_PICKED_PREFIXZERO = PickerTime(3, 3, 3);
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
class TimePickerDisplay12TestNg : public testing::Test {
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

void TimePickerDisplay12TestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TimePickerDisplay12TestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TimePickerDisplay12TestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TimePickerDisplay12TestNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg001
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(showType, showType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_INDEX_VALUE1 + 1) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE1));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + ZERO + std::to_string(CURRENT_INDEX_VALUE1 + 1) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg002
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(hideType, showType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_INDEX_VALUE1 + 1) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE1));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + std::to_string(CURRENT_INDEX_VALUE1 + 1) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg003
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(hideType, hideType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_INDEX_VALUE1 + 1) + COLON + std::to_string(CURRENT_INDEX_VALUE1));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + std::to_string(CURRENT_INDEX_VALUE1 + 1) + COLON + std::to_string(CURRENT_INDEX_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg004
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(showType, hideType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE2);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_INDEX_VALUE1 + 1) + COLON + std::to_string(CURRENT_INDEX_VALUE2));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + ZERO + std::to_string(CURRENT_INDEX_VALUE1 + 1) + COLON + std::to_string(CURRENT_INDEX_VALUE2));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg005
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(showType, showType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE2);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_INDEX_VALUE1 + 1) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE2));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + ZERO + std::to_string(CURRENT_INDEX_VALUE1 + 1) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE2));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg006
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(hideType, showType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE2);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_INDEX_VALUE1 + 1) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE2));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + std::to_string(CURRENT_INDEX_VALUE1 + 1) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE2));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg007
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(hideType, hideType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE2);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_INDEX_VALUE1 + 1) + COLON + std::to_string(CURRENT_INDEX_VALUE2));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + std::to_string(CURRENT_INDEX_VALUE1 + 1) + COLON + std::to_string(CURRENT_INDEX_VALUE2));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg008
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(showType, hideType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_INDEX_VALUE2) + COLON + std::to_string(CURRENT_INDEX_VALUE1));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + ZERO + std::to_string(CURRENT_INDEX_VALUE2) + COLON + std::to_string(CURRENT_INDEX_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg009
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(showType, showType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE2);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_INDEX_VALUE2 + 1) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE1));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + ZERO + std::to_string(CURRENT_INDEX_VALUE2 + 1) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg010
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(hideType, showType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE2);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_INDEX_VALUE2 + 1) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE1));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + std::to_string(CURRENT_INDEX_VALUE2 + 1) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg011
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(hideType, hideType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_INDEX_VALUE2) + COLON + std::to_string(CURRENT_INDEX_VALUE1));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + std::to_string(CURRENT_INDEX_VALUE2) + COLON + std::to_string(CURRENT_INDEX_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg012
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(showType, hideType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE2);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE2);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_INDEX_VALUE2 + 1) + COLON + std::to_string(CURRENT_INDEX_VALUE2));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + ZERO + std::to_string(CURRENT_INDEX_VALUE2 + 1) + COLON + std::to_string(CURRENT_INDEX_VALUE2));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg013
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(showType, showType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE2);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_INDEX_VALUE2) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE2));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + ZERO + std::to_string(CURRENT_INDEX_VALUE2) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE2));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg014
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(hideType, showType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE2);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_INDEX_VALUE2) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE2));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + std::to_string(CURRENT_INDEX_VALUE2) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE2));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg015
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(hideType, hideType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE2);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_INDEX_VALUE2) + COLON + std::to_string(CURRENT_INDEX_VALUE2));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + std::to_string(CURRENT_INDEX_VALUE2) + COLON + std::to_string(CURRENT_INDEX_VALUE2));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg016
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(showType, hideType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE2);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE3);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_INDEX_VALUE2 + 1) + COLON + std::to_string(CURRENT_INDEX_VALUE3));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + ZERO + std::to_string(CURRENT_INDEX_VALUE2 + 1) + COLON + std::to_string(CURRENT_INDEX_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg017
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(showType, showType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE2);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE3);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_INDEX_VALUE2 + 1) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE3));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + ZERO + std::to_string(CURRENT_INDEX_VALUE2 + 1) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg018
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(hideType, showType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE2);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE3);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_INDEX_VALUE2 + 1) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE3));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + std::to_string(CURRENT_INDEX_VALUE2 + 1) + COLON + ZERO + std::to_string(CURRENT_INDEX_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg019
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(hideType, hideType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE1);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE3);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_INDEX_VALUE2) + COLON + std::to_string(CURRENT_INDEX_VALUE3));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + std::to_string(CURRENT_INDEX_VALUE2) + COLON + std::to_string(CURRENT_INDEX_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerTextDisplayHour12TestNg020
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerDisplay12TestNg, TimePickerTextDisplayHour12TestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create timepicker with options.
     */
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(showType, hideType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    /**
     * @tc.steps: step2. Get all child nodes and check text in column.
     * @tc.expected: has zero when DateTimeOption is showType.
     */
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE3);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_INDEX_VALUE3);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_INDEX_VALUE3 + 1) + COLON + std::to_string(CURRENT_INDEX_VALUE3));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + ZERO + std::to_string(CURRENT_INDEX_VALUE3 + 1) + COLON + std::to_string(CURRENT_INDEX_VALUE3));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}
} // namespace OHOS::Ace::NG