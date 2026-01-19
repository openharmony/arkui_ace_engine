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

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/picker/picker_data.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
std::unique_ptr<TimePickerModel> TimePickerModel::timePickerInstance_ = nullptr;
std::unique_ptr<TimePickerDialogModel> TimePickerDialogModel::timePickerDialogInstance_ = nullptr;
std::once_flag TimePickerModel::onceFlag_;
std::once_flag TimePickerDialogModel::onceFlag_;

TimePickerModel* TimePickerModel::GetInstance()
{
    std::call_once(onceFlag_, []() {
        timePickerInstance_.reset(new NG::TimePickerModelNG());
    });
    return timePickerInstance_.get();
}

TimePickerDialogModel* TimePickerDialogModel::GetInstance()
{
    std::call_once(onceFlag_, []() {
        timePickerDialogInstance_.reset(new NG::TimePickerDialogModelNG());
    });
    return timePickerDialogInstance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const int CURRENT_VALUE1 = 3;
const int CURRENT_VALUE2 = 10;
const int MIDDLE_OF_COUNTS = 2;
const int SHOW_COUNT = 7;
const int DEFAULT_INDEX = -1;
const std::string AM = "AM ";
const std::string PM = "PM ";
const std::string COLON = ":";
const std::string ZERO = "0";
const PickerTime TIME_PICKED_PREFIXZERO = PickerTime(3, 3, 3);
const std::vector<int> DEFAULT_VALUE = { 0, 1, 2, 3, 4 };
const uint32_t INDEX = 7;
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
class TimePickerAccessibilityTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    void CreateTimePickerColumnNode();

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

void TimePickerAccessibilityTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TimePickerAccessibilityTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TimePickerAccessibilityTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TimePickerAccessibilityTestNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void TimePickerAccessibilityTestNg::CreateTimePickerColumnNode()
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);
    pickerFrameNode->MarkModifyDone();

    auto timePickerRowPattern = pickerFrameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    columnNode_ = allChildNode["minute"].Upgrade();
    ASSERT_NE(columnNode_, nullptr);
    columnPattern_ = columnNode_->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->SetShowCount(SHOW_COUNT);
    columnPattern_->OnAttachToFrameNode();
    auto host = timePickerRowPattern->GetHost();
    EXPECT_NE(host, nullptr);
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg001
 * @tc.desc: Test the ItemCounts property of TimePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerAccessibilityTestNg, TimePickerAccessibilityPropertyTestNg001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumnNode = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumnNode, nullptr);
    auto minuteColumnPattern = minuteColumnNode->GetPattern<TimePickerColumnPattern>();
    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumnNode] = DEFAULT_VALUE.size();
    minuteColumnPattern->SetOptions(options);
    auto accessibilityProperty = minuteColumnNode->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetCollectionItemCounts(), static_cast<int32_t>(DEFAULT_VALUE.size()));

    options.erase(minuteColumnNode);
    minuteColumnPattern->SetOptions(options);
    EXPECT_EQ(accessibilityProperty->GetCollectionItemCounts(), 0);
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg002
 * @tc.desc: Test the IsScrollable property of TimePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerAccessibilityTestNg, TimePickerAccessibilityPropertyTestNg002, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);

    auto accessibilityProperty = minuteColumn->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_TRUE(accessibilityProperty->IsScrollable());

    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumn] = 0;
    minuteColumnPattern->SetOptions(options);
    EXPECT_FALSE(accessibilityProperty->IsScrollable());
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg003
 * @tc.desc: Test the Index properties of TimePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerAccessibilityTestNg, TimePickerAccessibilityPropertyTestNg003, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);

    auto accessibilityProperty = minuteColumn->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetShowCount(SHOW_COUNT);
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);
    EXPECT_EQ(accessibilityProperty->GetCurrentIndex(), CURRENT_VALUE1);

    auto itemCount = accessibilityProperty->GetCollectionItemCounts();
    EXPECT_EQ(accessibilityProperty->GetBeginIndex(),
        (itemCount + CURRENT_VALUE1 - SHOW_COUNT / MIDDLE_OF_COUNTS) % itemCount);
    EXPECT_EQ(
        accessibilityProperty->GetEndIndex(), (itemCount + CURRENT_VALUE1 + SHOW_COUNT / MIDDLE_OF_COUNTS) % itemCount);

    minuteColumnPattern->SetShowCount(itemCount + itemCount);
    EXPECT_EQ(accessibilityProperty->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty->GetEndIndex(), itemCount - 1);

    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumn] = 0;
    minuteColumnPattern->SetOptions(options);

    EXPECT_EQ(accessibilityProperty->GetBeginIndex(), DEFAULT_INDEX);
    EXPECT_EQ(accessibilityProperty->GetEndIndex(), DEFAULT_INDEX);
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg004
 * @tc.desc: Test the Text property of TimePickerColumnPattern
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerAccessibilityTestNg, TimePickerAccessibilityPropertyTestNg004, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumnNode = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumnNode, nullptr);
    auto minuteColumnPattern = minuteColumnNode->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumnNode] = 0;
    minuteColumnPattern->SetOptions(options);
    auto accessibilityProperty = minuteColumnNode->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetText(), "");

    options[minuteColumnNode] = DEFAULT_VALUE.size();
    minuteColumnPattern->SetOptions(options);
    EXPECT_NE(accessibilityProperty->GetText(), "");

    options.erase(minuteColumnNode);
    minuteColumnPattern->SetOptions(options);
    EXPECT_EQ(accessibilityProperty->GetText(), "");
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg005
 * @tc.desc: Test the SupportAction property of TimePickerPattern
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerAccessibilityTestNg, TimePickerAccessibilityPropertyTestNg005, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumnNode = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumnNode, nullptr);
    auto minuteColumnPattern = minuteColumnNode->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumnNode] = DEFAULT_VALUE.size();
    minuteColumnPattern->SetOptions(options);
    auto accessibilityProperty = minuteColumnNode->GetAccessibilityProperty<TimePickerColumnAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    accessibilityProperty->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty->GetSupportAction();
    uint64_t actions = 0;
    uint64_t exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg006
 * @tc.desc: Test the Text property for of TimePickerRowPattern if it is MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerAccessibilityTestNg, TimePickerAccessibilityPropertyTestNg006, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->SetHour24(true);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    EXPECT_EQ(accessibilityProperty->GetText(),
        ZERO + std::to_string(CURRENT_VALUE1) + COLON + ZERO + std::to_string(CURRENT_VALUE1));

    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE2);
    hourColumnPattern->SetCurrentIndex(CURRENT_VALUE2);
    EXPECT_EQ(accessibilityProperty->GetText(),
        std::to_string(CURRENT_VALUE2) + COLON + std::to_string(CURRENT_VALUE2));
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg007
 * @tc.desc: Test the Text property of TimePickerRowPattern if it is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerAccessibilityTestNg, TimePickerAccessibilityPropertyTestNg007, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->SetHour24(false);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_VALUE1);
    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE1 + 1) + COLON + ZERO + std::to_string(CURRENT_VALUE1));
    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + ZERO + std::to_string(CURRENT_VALUE1 + 1) + COLON + ZERO + std::to_string(CURRENT_VALUE1));

    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE2);
    hourColumnPattern->SetCurrentIndex(CURRENT_VALUE2);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + std::to_string(CURRENT_VALUE2 + 1) + COLON + std::to_string(CURRENT_VALUE2));
    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + std::to_string(CURRENT_VALUE2 + 1) + COLON + std::to_string(CURRENT_VALUE2));
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg008
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerAccessibilityTestNg, TimePickerAccessibilityPropertyTestNg008, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(true);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(hideType, showType, hideType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();

    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto secondColumn = allChildNode["second"].Upgrade();
    ASSERT_NE(secondColumn, nullptr);
    auto secondColumnPattern = secondColumn->GetPattern<TimePickerColumnPattern>();
    secondColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    EXPECT_EQ(accessibilityProperty->GetText(),
        std::to_string(CURRENT_VALUE1) + COLON +
        ZERO + std::to_string(CURRENT_VALUE1) + COLON +
        std::to_string(CURRENT_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}

/**
 * @tc.name: TimePickerAccessibilityPropertyTestNg009
 * @tc.desc: Test the Text property for leading zero of TimePickerRowPattern when time is not MilitaryTime.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerAccessibilityTestNg, TimePickerAccessibilityPropertyTestNg009, TestSize.Level0)
{
    int32_t setApiVersion = 12;
    int32_t rollbackApiVersion = MockContainer::Current()->GetApiTargetVersion();
    ZeroPrefixType showType = ZeroPrefixType::SHOW;
    ZeroPrefixType hideType = ZeroPrefixType::HIDE;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED_PREFIXZERO);
    TimePickerModelNG::GetInstance()->SetDateTimeOptions(showType, hideType, showType);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();

    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    hourColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(CURRENT_VALUE1);

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();

    auto accessibilityProperty = frameNode->GetAccessibilityProperty<TimePickerRowAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    EXPECT_EQ(accessibilityProperty->GetText(),
        AM + ZERO + std::to_string(CURRENT_VALUE1 + 1) + COLON + std::to_string(CURRENT_VALUE1));

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(accessibilityProperty->GetText(),
        PM + ZERO + std::to_string(CURRENT_VALUE1 + 1) + COLON + std::to_string(CURRENT_VALUE1));
    MockContainer::Current()->SetApiTargetVersion(rollbackApiVersion);
}


/**
 * @tc.name: PerformActionTest001
 * @tc.desc: TimePicker accessibilityProperty PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerAccessibilityTestNg, PerformActionTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create timePicker and initialize related properties.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto pickerFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(pickerFrameNode, nullptr);

    /**
     * @tc.steps: step2. Get timePickerColumn frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto timePickerRowPattern = pickerFrameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    auto options = minuteColumnPattern->GetOptions();
    options[minuteColumn] = 0;
    minuteColumnPattern->SetOptions(options);
    minuteColumnPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get blendNode accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto blendNode = AceType::DynamicCast<FrameNode>(minuteColumn->GetParent());
    ASSERT_NE(blendNode, nullptr);
    auto accessibilityProperty = blendNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When timePickerColumn can move, call the callback function in accessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(accessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(accessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When timePickerColumn can not move, call the callback function in accessibilityProperty.
     * @tc.expected: Related function is called.
     */
    options = minuteColumnPattern->GetOptions();
    options[minuteColumn] = INDEX;
    minuteColumnPattern->SetOptions(options);
    minuteColumnPattern->SetCurrentIndex(1);
}
} // namespace OHOS::Ace::NG
