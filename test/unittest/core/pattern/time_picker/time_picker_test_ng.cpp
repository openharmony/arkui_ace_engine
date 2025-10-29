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
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components/theme/icon_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"
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
constexpr double TOSS_DELTA = 20.0;
const int MIDDLE_OF_COUNTS = 2;
const int SHOW_COUNT = 7;
const PickerTime TIME_PICKED = PickerTime(14, 9, 10);
const int32_t AM_PM_PICKED = 1;
const int32_t HOUR_PICKED = 1;
const int32_t HOUR24_PICKED = 14;
const int32_t MINUTE_PICKED = 9;
const int32_t SECOND_PICKED = 10;
const uint32_t MINUTE_59 = 59;
constexpr int32_t CHILD_WITH_AMPM_SIZE = 3;
const double YOFFSET_START1 = 0.0;
const double YOFFSET_END1 = 1000.0;
const SizeF TEST_FRAME_SIZE { 20, 30 };
constexpr double COLUMN_VELOCITY = 2000.0;
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
class TimePickerPatternTestNg : public testing::Test {
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

void TimePickerPatternTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TimePickerPatternTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TimePickerPatternTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TimePickerPatternTestNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void TimePickerPatternTestNg::CreateTimePickerColumnNode()
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
 * @tc.name: TimePickerPatternOnAttachToFrameNode001
 * @tc.desc: Test TimePickerRowPattern OnAttachToFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGCreateTimePicker001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto timePickerPattern = AceType::MakeRefPtr<TimePickerRowPattern>();
    timePickerPattern->AttachToFrameNode(frameNode);
    timePickerPattern->OnAttachToFrameNode();
    auto host = timePickerPattern->GetHost();
    EXPECT_NE(host, nullptr);
}

/**
 * @tc.name: TimePickerModelNGSetDisappearTextStyle001
 * @tc.desc: Test TimePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetDisappearTextStyle001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    TimePickerModelNG::GetInstance()->SetDisappearTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasDisappearFontSize());
    EXPECT_FALSE(pickerProperty->HasDisappearColor());
    EXPECT_TRUE(pickerProperty->HasDisappearWeight());
}

/**
 * @tc.name: TimePickerModelNGSetDisappearTextStyle002
 * @tc.desc: Test TimePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetDisappearTextStyle002, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TimePickerModelNG::GetInstance()->SetDisappearTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetDisappearColor().value());
    EXPECT_EQ(Dimension(10), pickerProperty->GetDisappearFontSize().value());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetDisappearWeight().value());
}

/**
 * @tc.name: TimePickerModelNGSetDisappearTextStyle003
 * @tc.desc: Test TimePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetDisappearTextStyle003, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    TimePickerModelNG::GetInstance()->SetDisappearTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasDisappearFontSize());
}

/**
 * @tc.name: TimePickerModelNGSetDisappearTextStyle004
 * @tc.desc: Test TimePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetDisappearTextStyle004, TestSize.Level0)
{
    TimePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::RED;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(10);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    auto isUserSet = TimePickerDialogView::GetIsUserSetTextProperties(settingData.properties);
    EXPECT_EQ(isUserSet, true);
}

/**
 * @tc.name: TimePickerModelNGSetDisappearTextStyle005
 * @tc.desc: Test TimePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetDisappearTextStyle005, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    TimePickerModelNG::GetInstance()->SetDisappearTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_FALSE(pickerProperty->HasFontStyle());
}

/**
 * @tc.name: TimePickerModelNGSetNormalTextStyle001
 * @tc.desc: Test TimePickerModelNG SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetNormalTextStyle001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    TimePickerModelNG::GetInstance()->SetNormalTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasFontSize());
    EXPECT_FALSE(pickerProperty->HasColor());
    EXPECT_TRUE(pickerProperty->HasWeight());
}

/**
 * @tc.name: TimePickerModelNGSetNormalTextStyle002
 * @tc.desc: Test TimePickerModelNG SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetNormalTextStyle002, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TimePickerModelNG::GetInstance()->SetNormalTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetColor().value());
    EXPECT_EQ(Dimension(10), pickerProperty->GetFontSize().value());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetWeight().value());
}

/**
 * @tc.name: TimePickerModelNGSetNormalTextStyle003
 * @tc.desc: Test TimePickerModelNG SetNormalTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetNormalTextStyle003, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    TimePickerModelNG::GetInstance()->SetNormalTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasFontSize());
}

/**
 * @tc.name: TimePickerModelNGSetNormalTextStyle004
 * @tc.desc: Test TimePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetNormalTextStyle004, TestSize.Level0)
{
    TimePickerSettingData settingData;
    settingData.properties.normalTextStyle_.textColor = Color::RED;
    settingData.properties.normalTextStyle_.fontSize = Dimension(10);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    auto isUserSet = TimePickerDialogView::GetIsUserSetTextProperties(settingData.properties);
    EXPECT_EQ(isUserSet, true);
}

/**
 * @tc.name: TimePickerModelNGSetSelectedTextStyle001
 * @tc.desc: Test TimePickerModelNG SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetSelectedTextStyle001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    TimePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasSelectedFontSize());
    EXPECT_FALSE(pickerProperty->HasSelectedColor());
    EXPECT_TRUE(pickerProperty->HasSelectedWeight());
}

/**
 * @tc.name: TimePickerModelNGSetSelectedTextStyle002
 * @tc.desc: Test TimePickerModelNG SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetSelectedTextStyle002, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(10);
    data.textColor = Color::RED;
    data.fontWeight = Ace::FontWeight::BOLD;
    TimePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_EQ(Color::RED, pickerProperty->GetSelectedColor().value());
    EXPECT_EQ(Dimension(10), pickerProperty->GetSelectedFontSize().value());
    EXPECT_EQ(Ace::FontWeight::BOLD, pickerProperty->GetSelectedWeight().value());
}

/**
 * @tc.name: TimePickerModelNGSetSelectedTextStyle003
 * @tc.desc: Test TimePickerModelNG SetSelectedTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetSelectedTextStyle003, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    PickerTextStyle data;
    data.fontSize = Dimension(0);
    TimePickerModelNG::GetInstance()->SetSelectedTextStyle(theme, data);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_TRUE(pickerProperty->HasSelectedFontSize());
}

/**
 * @tc.name: TimePickerModelNGSetSelectedTextStyle004
 * @tc.desc: Test TimePickerModelNG SetDisappearTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGSetSelectedTextStyle004, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create TimePickerSettingData and call GetIsUserSetTextProperties.
     * @tc.expected: the third if condition is true and return true.
     */
    TimePickerSettingData settingData;
    settingData.properties.selectedTextStyle_.textColor = Color::RED;
    settingData.properties.selectedTextStyle_.fontSize = Dimension(10);
    settingData.properties.normalTextStyle_.fontWeight = Ace::FontWeight::BOLD;
    settingData.isUseMilitaryTime = false;
    auto isUserSet = TimePickerDialogView::GetIsUserSetTextProperties(settingData.properties);
    EXPECT_EQ(isUserSet, true);
    /**
     * @tc.steps: step1+. set TimePickerSettingData and call GetIsUserSetTextProperties.
     * @tc.expected: all of if conditions are false and return false.
     */
    settingData.properties.selectedTextStyle_.fontSize = Dimension(0);
    settingData.properties.normalTextStyle_.fontSize = Dimension(0);
    settingData.properties.disappearTextStyle_.fontSize = Dimension(0);
    isUserSet = TimePickerDialogView::GetIsUserSetTextProperties(settingData.properties);
    EXPECT_EQ(isUserSet, false);
}

/**
 * @tc.name: TimePickerLayoutPropertyReset001
 * @tc.desc: Test TimePickerLayoutProperty Reset.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerLayoutPropertyReset001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->Reset();
}

/**
 * @tc.name: TimePickerLayoutPropertyClone001
 * @tc.desc: Test TimePickerLayoutProperty Clone.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerLayoutPropertyClone001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();

    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    EXPECT_NE(pickerProperty->Clone(), nullptr);
}

/**
 * @tc.name: TimePickerFireChangeEventTest001
 * @tc.desc: Test SetSelectedDate.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerFireChangeEventTest001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    auto changeEvent = [](const BaseEventInfo* info) { EXPECT_EQ(info->GetType(), "DatePickerChangeEvent"); };
    TimePickerModelNG::GetInstance()->SetChangeEvent(std::move(changeEvent));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->FireChangeEvent(true);
}

/**
 * @tc.name: TimePickerHasSecond001
 * @tc.desc: Test TimePickerRowPattern SetHasSecond true.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerHasSecond001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(true);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    std::vector<RefPtr<FrameNode>> tags;
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();

    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(hourColumnPattern, nullptr);
    EXPECT_EQ(hourColumnPattern->GetCurrentIndex(), HOUR24_PICKED);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    EXPECT_EQ(minuteColumnPattern->GetCurrentIndex(), MINUTE_PICKED);

    auto secondColumn = allChildNode["second"].Upgrade();
    ASSERT_NE(secondColumn, nullptr);
    auto secondColumnPattern = secondColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(secondColumnPattern, nullptr);
    EXPECT_EQ(secondColumnPattern->GetCurrentIndex(), SECOND_PICKED);
}

/**
 * @tc.name: TimePickerHasSecond002
 * @tc.desc: Test TimePickerRowPattern SetHasSecond false.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerHasSecond002, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, false);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();

    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(amPmColumnPattern, nullptr);
    EXPECT_EQ(amPmColumnPattern->GetCurrentIndex(), AM_PM_PICKED);

    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(hourColumnPattern, nullptr);
    EXPECT_EQ(hourColumnPattern->GetCurrentIndex(), HOUR_PICKED);

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minuteColumnPattern, nullptr);
    EXPECT_EQ(minuteColumnPattern->GetCurrentIndex(), MINUTE_PICKED);

    auto secondColumn = allChildNode["second"].Upgrade();
    ASSERT_EQ(secondColumn, nullptr);
}

/**
 * @tc.name: TimePickerHasSecond003
 * @tc.desc: Test TimePickerRowPattern SetHasSecond true first then false.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerHasSecond003, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    /**
     * @tc.steps: step1. create FrameNode and SetHasSecond(true).
     */
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme, true);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    TimePickerModelNG::GetInstance()->SetSelectedTime(TIME_PICKED);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    std::vector<RefPtr<FrameNode>> tags;
    /**
     * @tc.steps: step2. check the secondColumn has been created.
     */
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto secondColumn = allChildNode["second"].Upgrade();
    ASSERT_NE(secondColumn, nullptr);
    /**
     * @tc.steps: step3. SetHasSecond(false) then check the secondColumn has been deleted.
     */
    timePickerRowPattern->SetHasSecond(false);
    frameNode->MarkModifyDone();
    EXPECT_EQ(frameNode->GetChildren().size(), CHILD_WITH_AMPM_SIZE);
}

/**
 * @tc.name: TimePickerWheelMode001
 * @tc.desc: Test TimePickerRowPattern SetWheelModeEnabled false.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerWheelMode001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetWheelModeEnabled(false);
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
    ASSERT_NE(hourColumnPattern, nullptr);
    EXPECT_EQ(hourColumnPattern->GetCanLoopFromLayoutProperty(), false);
}

/**
 * @tc.name: TimePickerWheelMode002
 * @tc.desc: Test TimePickerRowPattern default wheelmode.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerWheelMode002, TestSize.Level0)
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

    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(hourColumnPattern, nullptr);
    EXPECT_EQ(hourColumnPattern->GetCanLoopFromLayoutProperty(), true);
}

/**
 * @tc.name: TimePickerWheelMode003
 * @tc.desc: Test TimePickerColumnPattern UpdateColumnChildPosition while wheelmode off.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerWheelMode003, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetWheelModeEnabled(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(0);
    minuteColumnPattern->UpdateColumnChildPosition(TOSS_DELTA);
    EXPECT_EQ(minuteColumnPattern->GetCurrentIndex(), 0);
}

/**
 * @tc.name: TimePickerWheelMode004
 * @tc.desc: Test TimePickerColumnPattern UpdateColumnChildPosition while wheelmode on.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerWheelMode004, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetWheelModeEnabled(true);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();

    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    minuteColumnPattern->SetCurrentIndex(0);
    minuteColumnPattern->UpdateColumnChildPosition(TOSS_DELTA);
    EXPECT_EQ(minuteColumnPattern->GetCurrentIndex(), MINUTE_59);
}

/**
 * @tc.name: TimePickerWheelMode005
 * @tc.desc: Test TimePickerRowPattern wheelmode is false when start end is set.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerWheelMode005, TestSize.Level0)
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

    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(hourColumnPattern, nullptr);

    PickerTime startTime = PickerTime(0, 1, 1);
    PickerTime endTime = PickerTime(22, 58, 58);
    timePickerRowPattern->SetStartTime(startTime);
    timePickerRowPattern->SetEndTime(endTime);
    EXPECT_EQ(hourColumnPattern->GetCanLoopFromLayoutProperty(), false);
}

/**
 * @tc.name: TimePickerAlgorithmTest001
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerAlgorithmTest001, TestSize.Level0)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    /**
     * @tc.cases: case. cover branch DeviceOrientation is LANDSCAPE.
     */
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    auto layoutConstraint = LayoutConstraintF();
    layoutConstraint.selfIdealSize.SetWidth(20);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_TRUE(timePickerRowPattern);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_TRUE(minuteColumnPattern);
    auto columnBlend = AceType::DynamicCast<FrameNode>(minuteColumn->GetParent());
    ASSERT_TRUE(columnBlend);
    auto blendLayoutProperty = columnBlend->GetLayoutProperty();
    blendLayoutProperty->UpdateLayoutConstraint(layoutConstraint);
    blendLayoutProperty->UpdateContentConstraint();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(minuteColumn, minuteColumn->GetGeometryNode(), pickerProperty);
    RefPtr<LayoutWrapperNode> subLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subLayoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> subTwoLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, nullptr, nullptr);
    EXPECT_NE(subTwoLayoutWrapper, nullptr);
    layoutWrapper.AppendChild(std::move(subLayoutWrapper));
    layoutWrapper.AppendChild(std::move(subTwoLayoutWrapper));
    EXPECT_EQ(layoutWrapper.GetTotalChildCount(), 2);


    /**
     * @tc.step: step2. initialize TimePickerColumnLayoutAlgorithm and call Measure
     *                  and Layout function.
     */
    TimePickerColumnLayoutAlgorithm timePickerColumnLayoutAlgorithm;
    timePickerColumnLayoutAlgorithm.Measure(&layoutWrapper);
    timePickerColumnLayoutAlgorithm.Layout(&layoutWrapper);
    auto frameSize = layoutWrapper.geometryNode_->GetFrameSize();
    EXPECT_EQ(frameSize, TEST_FRAME_SIZE);

    /**
     * @tc.step: step3. set SetDeviceOrientation and call Measure.
     * @tc.expected: call Measure and frameSize valus meet expectation.
     */
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    timePickerColumnLayoutAlgorithm.Measure(&layoutWrapper);
    timePickerColumnLayoutAlgorithm.Layout(&layoutWrapper);
    frameSize = layoutWrapper.geometryNode_->GetFrameSize();
    EXPECT_EQ(frameSize, TEST_FRAME_SIZE);
}

/**
 * @tc.name: TossAnimationControllerSetStart001
 * @tc.desc: Test SetStart.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TossAnimationControllerSetStart001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TimePickerColumn.
     */
    CreateTimePickerColumnNode();

    /**
     * @tc.steps: step2. Set velocity and call SetStart .
     */
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->SetMainVelocity(COLUMN_VELOCITY);
    columnPattern_->touchBreak_ = true;
    auto toss = columnPattern_->GetToss();
    ASSERT_NE(toss, nullptr);
    toss->SetStart(YOFFSET_START1);
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
}

/**
 * @tc.name: TossAnimationControllerSetStart002
 * @tc.desc: Test SetStart.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TossAnimationControllerSetStart002, TestSize.Level0)
{
    /**
    * @tc.steps: step1. Create TimePickerColumn.
    */
    CreateTimePickerColumnNode();

    /**
    * @tc.steps: step2. Set velocity and call SetStart .
    */
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->SetMainVelocity(COLUMN_VELOCITY);
    columnPattern_->touchBreak_ = true;
    auto toss = columnPattern_->GetToss();
    ASSERT_NE(toss, nullptr);

    /**
    * @tc.steps: step3. init property_.
    */
    auto propertyCallback = [](float offset) {};
    toss->property_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    toss->SetStart(YOFFSET_START1);
    EXPECT_EQ(toss->yStart_, YOFFSET_START1);
    EXPECT_FALSE(columnPattern_->GetTossStatus());
}

/**
 * @tc.name: TossAnimationControllerSetEnd001
 * @tc.desc: Test SetEnd.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TossAnimationControllerSetEnd001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create TimePickerColumn.
     */
    CreateTimePickerColumnNode();

    /**
     * @tc.steps: step2. Set velocity and toss offset .
     */
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->SetMainVelocity(COLUMN_VELOCITY);
    auto toss = columnPattern_->GetToss();
    ASSERT_NE(toss, nullptr);
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
}

/**
 * @tc.name: TossAnimationControllerSetEnd002
 * @tc.desc: Test SetEnd.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TossAnimationControllerSetEnd002, TestSize.Level0)
{
    /**
    * @tc.steps: step1. Create TimePickerColumn.
    */
    CreateTimePickerColumnNode();

    /**
    * @tc.steps: step2. Set velocity and toss offset .
    */
    ASSERT_NE(columnPattern_, nullptr);
    columnPattern_->SetMainVelocity(COLUMN_VELOCITY);
    auto toss = columnPattern_->GetToss();
    ASSERT_NE(toss, nullptr);
    toss->SetStart(YOFFSET_START1);
    toss->SetEnd(YOFFSET_END1);

    /**
    * @tc.steps: step3. init property_ .
    */
    auto propertyCallback = [](float offset) {};
    toss->property_ =
        AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    EXPECT_EQ(toss->yEnd_, YOFFSET_END1);
    EXPECT_FALSE(columnPattern_->GetTossStatus());
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: Test TimePickerRowPattern OnColorConfigurationUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, OnColorConfigurationUpdate001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    /**
     * @tc.cases: case. cover branch dialogTheme pass non null check .
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto pickerTheme = AceType::MakeRefPtr<PickerTheme>();
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(pickerTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(pickerTheme));

    auto pickerPattern = frameNode->GetPattern<TimePickerRowPattern>();

    /**
     * @tc.cases: case. cover branch isPicker_ == false.
     */
    pickerPattern->SetPickerTag(false);

    /**
     * @tc.cases: case. cover branch contentRowNode_ is not null.
     */
    pickerPattern->OnColorConfigurationUpdate();
    ASSERT_EQ(Color::BLACK, dialogTheme->GetBackgroundColor());
}

/**
 * @tc.name: OnColorConfigurationUpdate002
 * @tc.desc: Test TimePickerRowPattern OnColorConfigurationUpdate().
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, OnColorConfigurationUpdate002, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();

    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);
    timePickerRowPattern->UpdateAllChildNode();

    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    ASSERT_NE(pickerProperty, nullptr);
    pickerProperty->contentConstraint_ = pickerProperty->CreateContentConstraint();

    /**
     * @tc.cases: case. cover branch dialogTheme pass non null check .
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto pickerTheme = AceType::MakeRefPtr<PickerTheme>();
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(pickerTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(pickerTheme));

    auto pickerPattern = frameNode->GetPattern<TimePickerRowPattern>();

    /**
     * @tc.cases: case. cover branch isPicker_ == true.
     */
    pickerPattern->SetPickerTag(true);

    pickerPattern->OnColorConfigurationUpdate();
    ASSERT_EQ(Color::BLACK, dialogTheme->GetBackgroundColor());
}

/**
 * @tc.name: TimePickerDialogViewUpdateButtonDefaultFocus001
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewUpdateButtonDefaultFocus001, TestSize.Level0)
{
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    info1.isAcceptButton = true;
    buttonInfos.push_back(info1);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);

    TimePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: TimePickerDialogViewUpdateButtonDefaultFocus002
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewUpdateButtonDefaultFocus002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create ButtonInfos[2] and Create Button Node.
     */
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    buttonInfos.push_back(info1);
    ButtonInfo info2;
    info2.isPrimary = true;
    buttonInfos.push_back(info2);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    /**
     * @tc.steps: step2. call UpdateButtonDefaultFocus expect defaultfocus is false.
     */
    TimePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, false);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), false);
    /**
     * @tc.steps: step2+. set buttoninfos isPrimary is false call UpdateButtonDefaultFocus
     *  and set buttonnode is nullptr. IsDefaultFocus expects false.
     */
    buttonInfos[0].isPrimary = false;
    buttonInfos[1].isPrimary = false;
    TimePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, nullptr, false);
    EXPECT_EQ(focusHub->IsDefaultFocus(), false);
}

/**
 * @tc.name: TimePickerDialogViewUpdateButtonDefaultFocus003
 * @tc.desc: Test UpdateButtonDefaultFocus.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewUpdateButtonDefaultFocus003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create ButtonInfos[2] and Create Button Node set isPrimary true.
     */
    std::vector<ButtonInfo> buttonInfos;
    ButtonInfo info1;
    info1.isPrimary = true;
    info1.isAcceptButton = true;
    buttonInfos.push_back(info1);

    ButtonInfo info2;
    buttonInfos.push_back(info2);

    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonNode, nullptr);
    /**
     * @tc.steps: step2. call UpdateButtonDefaultFocus and isConfirm is true.
     * @tc.expected: button1.isPrimary = true and IsDefaultFocus expects true.
     */
    TimePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, true);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
    /**
     * @tc.steps: step2+. call UpdateButtonDefaultFocus and isConfirm is false.
     * @tc.expected: button2.isPrimary = true and IsDefaultFocus expects true.
     */
    buttonInfos[0].isPrimary = false;
    buttonInfos[1].isPrimary = true;
    TimePickerDialogView::UpdateButtonDefaultFocus(buttonInfos, buttonNode, false);
    focusHub = buttonNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->IsDefaultFocus(), true);
}

/**
 * @tc.name: TimePickerEnableHapticFeedback001
 * @tc.desc: Test property enableHapticFeedback by default.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerEnableHapticFeedback001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_TRUE(TimePickerModelNG::getEnableHapticFeedback(frameNode));
}

/**
 * @tc.name: TimePickerEnableHapticFeedback002
 * @tc.desc: Test property enableHapticFeedback by Setter API
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerEnableHapticFeedback002, TestSize.Level0)
{
    std::vector<bool> testValues = { false, true, true, false, false };
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);

    for (auto testValue : testValues) {
        TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        TimePickerModelNG::GetInstance()->SetIsEnableHapticFeedback(testValue);
        EXPECT_EQ(TimePickerModelNG::getEnableHapticFeedback(frameNode), static_cast<uint32_t>(testValue));
    }
}

/**
 * @tc.name: TimePickerEnableHapticFeedback003
 * @tc.desc: Test property enableHapticFeedback by Setter/Getter API
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerEnableHapticFeedback003, TestSize.Level0)
{
    std::vector<bool> testValues = { false, true, true, false, false };
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    ASSERT_NE(theme, nullptr);

    for (auto testValue : testValues) {
        TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        ASSERT_NE(frameNode, nullptr);
        TimePickerModelNG::GetInstance()->SetIsEnableHapticFeedback(testValue);
        auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
        ASSERT_NE(timePickerRowPattern, nullptr);
        EXPECT_EQ(timePickerRowPattern->GetIsEnableHaptic(), testValue);
    }
}

/**
 * @tc.name: TimePickerDialogViewConvertFontScaleValue001
 * @tc.desc: Test TimePickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewConvertFontScaleValue001, TestSize.Level0)
{
    Dimension fontSizeValue = 50.0_vp;
    Dimension fontSizeLimit = 40.0_vp;

    auto result = TimePickerDialogView::ConvertFontScaleValue(fontSizeValue,
        fontSizeLimit, true);
    EXPECT_EQ(fontSizeLimit.Value(), result.Value());
}

/**
 * @tc.name: TimePickerDialogViewConvertFontScaleValue002
 * @tc.desc: Test TimePickerDialogView ConvertFontScaleValue.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewConvertFontScaleValue002, TestSize.Level0)
{
    Dimension fontSizeValue = 20.0_vp;
    Dimension fontSizeLimit = 40.0_vp;

    auto result = TimePickerDialogView::ConvertFontScaleValue(fontSizeValue,
        fontSizeLimit, true);
    EXPECT_EQ(fontSizeValue.Value(), result.Value());
}

/**
 * @tc.name: TimePickerDialogViewConvertFontSizeLimitTest001
 * @tc.desc: Test TimePickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewConvertFontSizeLimitTest001, TestSize.Level0)
{
    Dimension fontSizeValue(20.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = false;
    Dimension result = TimePickerDialogView::ConvertFontSizeLimit(fontSizeValue,
        fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: TimePickerDialogViewConvertFontSizeLimitTest002
 * @tc.desc: Test TimePickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewConvertFontSizeLimitTest002, TestSize.Level0)
{
    Dimension fontSizeValue(20.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    Dimension result = TimePickerDialogView::ConvertFontSizeLimit(fontSizeValue,
        fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: TimePickerDialogViewConvertFontSizeLimitTest003
 * @tc.desc: Test TimePickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewConvertFontSizeLimitTest003, TestSize.Level0)
{
    Dimension fontSizeValue(40.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    double fontScale = 2.0f;
    MockPipelineContext::GetCurrent()->SetFontScale(fontScale);
    Dimension result = TimePickerDialogView::ConvertFontSizeLimit(fontSizeValue,
        fontSizeLimit, isUserSetFont);
    Dimension expected = fontSizeLimit / fontScale;
    EXPECT_EQ(result, expected);
}

/**
 * @tc.name: TimePickerDialogViewConvertFontSizeLimitTest004
 * @tc.desc: Test TimePickerDialogView ConvertFontSizeLimit.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewConvertFontSizeLimitTest004, TestSize.Level0)
{
    Dimension fontSizeValue(10.0);
    Dimension fontSizeLimit(30.0);
    bool isUserSetFont = true;
    double fontScale = 2.0f;
    MockPipelineContext::GetCurrent()->SetFontScale(fontScale);
    Dimension result = TimePickerDialogView::ConvertFontSizeLimit(fontSizeValue,
        fontSizeLimit, isUserSetFont);
    EXPECT_EQ(result, fontSizeValue);
}

/**
 * @tc.name: TimePickerDialogViewGetUserSettingLimitTest001
 * @tc.desc: Test TimePickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewGetUserSettingLimitTest001, TestSize.Level0)
{
    double fontScale = 1.0f;
    Dimension fontSizeValue(10.0);
    Dimension result = TimePickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: TimePickerDialogViewGetUserSettingLimitTest002
 * @tc.desc: Test TimePickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewGetUserSettingLimitTest002, TestSize.Level0)
{
    double fontScale = 1.75f;
    Dimension fontSizeValue(10.0);
    Dimension result = TimePickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: TimePickerDialogViewGetUserSettingLimitTest003
 * @tc.desc: Test TimePickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewGetUserSettingLimitTest003, TestSize.Level0)
{
    double fontScale = 2.0f;
    Dimension fontSizeValue(10.0);
    Dimension result = TimePickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: TimePickerDialogViewGetUserSettingLimitTest004
 * @tc.desc: Test TimePickerDialogView AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerDialogViewGetUserSettingLimitTest004, TestSize.Level0)
{
    double fontScale = 3.2f;
    Dimension fontSizeValue(10.0);
    Dimension result = TimePickerDialogView::AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_NE(result, fontSizeValue * fontScale);
}

/**
 * @tc.name: TimePickerModelNGBackgroundColor001
 * @tc.desc: Test TimePickerPatternTestNg SetBackgroundColor and getTimepickerBackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerModelNGBackgroundColor001, TestSize.Level0)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);

    auto theme = context->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    TimePickerModelNG::SetBackgroundColor(frameNode, Color::RED);
    EXPECT_EQ(TimePickerModelNG::getTimepickerBackgroundColor(frameNode), Color::RED.GetValue());
}

/**
 * @tc.name: TimePickerRowPatternCheckFocusID001
 * @tc.desc: Test CheckFocusID2.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerRowPatternCheckFocusID001, TestSize.Level0)
{
    /**
     * @tc.step: step1. create row pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step2. call CheckFocusID.
     * @tc.expected: set focusKeyID is less than childSize.
     */
    int32_t value = -1;
    int32_t childSize = 8;
    timePickerRowPattern->SetCurrentFocusKeyID(value);
    bool res = timePickerRowPattern->CheckFocusID(childSize);
    int32_t focusKeyID = timePickerRowPattern->GetCurrentFocusKeyID();
    EXPECT_FALSE(res);
    EXPECT_EQ(focusKeyID, 0);
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    EXPECT_NE(pipeline, nullptr);
    float fontSize = 100.0f;
    pipeline->fontScale_ = fontSize;
    pipeline->rootHeight_ = fontSize;
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_NE(pickerTheme, nullptr);
    double pickerSize = 50.75;
    pickerTheme->pickerDialogMaxOneFontScale_ = pickerSize;
    pickerTheme->deviceHeightLimit_ = pickerSize;
    EXPECT_GT(pipeline->GetFontScale(), pickerTheme->GetMaxOneFontScale());
    timePickerRowPattern->SetCurrentPage(1);
    res = timePickerRowPattern->CheckFocusID(childSize);
    EXPECT_TRUE(res);
    /**
     * @tc.steps: step3. call CheckFocusID.
     * @tc.expected: set focusKeyID is less than childSize.
     */
    timePickerRowPattern->SetCurrentPage(0);
    res = timePickerRowPattern->CheckFocusID(childSize);
    EXPECT_NE(timePickerRowPattern->GetCurrentPage(), 1);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: TimePickerColumnPatternScrollOption001
 * @tc.desc: Test TimePickerColumnPattern ScrollOption and HandleEnterSelectedArea.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerPatternTestNg, TimePickerColumnPatternScrollOption001, TestSize.Level0)
{
    CreateTimePickerColumnNode();
    ASSERT_NE(columnPattern_, nullptr);
    ASSERT_NE(columnNode_, nullptr);
    auto childSize = static_cast<int32_t>(columnNode_->GetChildren().size());
    auto midSize = childSize / MIDDLE_OF_COUNTS;
    columnPattern_->optionProperties_[midSize].prevDistance = 5.0f;
    columnPattern_->optionProperties_[midSize].nextDistance = 7.0f;
    columnPattern_->SetCurrentIndex(2);
    columnPattern_->ScrollOption(10.0f);
    EXPECT_EQ(columnPattern_->GetEnterIndex(), 1);
}
} // namespace OHOS::Ace::NG
