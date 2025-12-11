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
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const std::string AM = "AM ";
const std::string PM = "PM ";
const double OFFSET_X = 6.0;
const float EXTRA_WIDTH = 50.0f;
const Dimension PICKER_PRESS_RADIUS = 3.0_vp;
const Dimension PRESS_INTERVAL = 4.0_vp;
const Dimension PRESS_RADIUS = 8.0_vp;
const uint32_t DEFAULT_YEAR = 1;
const uint32_t DEFAULT_MONTH = 2;
const uint32_t DEFAULT_DAY = 5;
constexpr uint32_t AM_PM_HOUR_12 = 12;
constexpr int32_t CHILD_WITH_AMPM_SIZE = 3;
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
class TimePickerRowPatternTestNg : public testing::Test {
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

void TimePickerRowPatternTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TimePickerRowPatternTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TimePickerRowPatternTestNg::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TimePickerRowPatternTestNg::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

/**
 * @tc.name: TimePickerRowPattern001
 * @tc.desc: Test TimePickerRowPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern001, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    frameNode->GetGeometryNode()->frame_.rect_.SetWidth(EXTRA_WIDTH);
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    DirtySwapConfig config;
    config.frameSizeChange = true;
    EXPECT_TRUE(timePickerRowPattern->OnDirtyLayoutWrapperSwap(dirty, config));

    auto children = frameNode->GetChildren();
    auto height = theme->GetDividerSpacing();
    auto width = frameNode->GetGeometryNode()->GetFrameSize().Width() / static_cast<float>(children.size());
    auto defaultWidth = height.ConvertToPx() * 2;
    EXPECT_LT(width, defaultWidth);

    for (const auto& child : children) {
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        ASSERT_NE(childNode, nullptr);
        auto newWidth = childNode->GetGeometryNode()->GetFrameSize().Width();
        auto buttonNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
        auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        EXPECT_EQ(buttonLayoutProperty->GetMeasureType(), MeasureType::MATCH_PARENT_MAIN_AXIS);
        EXPECT_EQ(buttonLayoutProperty->GetTypeValue(), ButtonType::NORMAL);
        auto calcSize = buttonLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize.value();
        EXPECT_EQ(calcSize.Width().value(), CalcLength(newWidth - PRESS_INTERVAL.ConvertToPx()));
        EXPECT_EQ(calcSize.Height().value(), CalcLength(0.0f));
        auto buttonConfirmRenderContext = buttonNode->GetRenderContext();
        EXPECT_EQ(buttonConfirmRenderContext->GetBackgroundColorValue(), Color::TRANSPARENT);
    }
}

/**
 * @tc.name: TimePickerRowPattern002
 * @tc.desc: Test TimePickerRowPattern OnModifyDone while HasTitleNode
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern002, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto titleNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    timePickerRowPattern->titleId_ = titleNodeId;
    auto* stack = ViewStackProcessor::GetInstance();
    auto textFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, titleNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    stack->Push(textFrameNode);
    PickerDate pickerDate(DEFAULT_YEAR, DEFAULT_MONTH, DEFAULT_DAY);
    timePickerRowPattern->SetDialogTitleDate(pickerDate);

    timePickerRowPattern->OnModifyDone();
    auto textTitleNode = FrameNode::GetOrCreateFrameNode(
        V2::TEXT_ETS_TAG, titleNodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto textLayoutProperty = textTitleNode->GetLayoutProperty<TextLayoutProperty>();
}

/**
 * @tc.name: TimePickerRowPattern003
 * @tc.desc: Test TimePickerRowPattern CreateAmPmNode while AmPmButtonIdeaSize > 0
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern003, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto children = frameNode->GetChildren();
    for (const auto& child : children) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(child->GetFirstChild());
        buttonNode->GetGeometryNode()->frame_.rect_.SetWidth(EXTRA_WIDTH);
    }
    timePickerRowPattern->SetHour24(false);
    std::optional<int32_t> amPmId;
    timePickerRowPattern->amPmId_ = amPmId;

    timePickerRowPattern->CreateAmPmNode();
    EXPECT_GT(timePickerRowPattern->SetAmPmButtonIdeaSize(), 0);
}

/**
 * @tc.name: TimePickerRowPattern004
 * @tc.desc: Test TimePickerRowPattern GetCurrentTime using 12-hour system
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern004, TestSize.Level0)
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
    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(amPmPickerColumnPattern, nullptr);
    auto hourColumn = allChildNode["hour"].Upgrade();
    ASSERT_NE(hourColumn, nullptr);
    auto hourPickerColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(hourPickerColumnPattern, nullptr);
    auto minuteColumn = allChildNode["minute"].Upgrade();
    ASSERT_NE(minuteColumn, nullptr);
    auto minutePickerColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(minutePickerColumnPattern, nullptr);

    amPmPickerColumnPattern->SetCurrentIndex(0);
    hourPickerColumnPattern->SetCurrentIndex(AM_PM_HOUR_12 - 1);
    EXPECT_EQ(timePickerRowPattern->GetCurrentTime().GetHour(), 0);
    EXPECT_EQ(timePickerRowPattern->GetCurrentTime().GetMinute(), minutePickerColumnPattern->GetCurrentIndex());

    hourPickerColumnPattern->SetCurrentIndex(AM_PM_HOUR_12 - 2);
    EXPECT_EQ(timePickerRowPattern->GetCurrentTime().GetHour(), AM_PM_HOUR_12 - 1);

    amPmPickerColumnPattern->SetCurrentIndex(1);
    EXPECT_EQ(timePickerRowPattern->GetCurrentTime().GetHour(), AM_PM_HOUR_12 * 2 - 1);

    hourPickerColumnPattern->SetCurrentIndex(AM_PM_HOUR_12 - 1);
    EXPECT_EQ(timePickerRowPattern->GetCurrentTime().GetHour(), AM_PM_HOUR_12);
}

/**
 * @tc.name: TimePickerRowPattern005
 * @tc.desc: Test TimePickerRowPattern HandleColumnChange
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern005, TestSize.Level0)
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
    auto amPmColumn = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPmColumn, nullptr);
    auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(amPmPickerColumnPattern, nullptr);
    amPmPickerColumnPattern->SetCurrentIndex(0);
    auto tag = allChildNode["hour"].Upgrade();
    ASSERT_NE(tag, nullptr);
    timePickerRowPattern->HandleColumnChange(tag, true, 11, true);
    std::vector<RefPtr<FrameNode>> tags;
    timePickerRowPattern->OnDataLinking(tag, true, 11, tags);
    EXPECT_EQ(tags.size(), 1);
}

/**
 * @tc.name: TimePickerRowPattern006
 * @tc.desc: Test TimePickerRowPattern HandleHourColumnBuilding while AM PM column is null
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern006, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->SetHour24(false);
    frameNode->RemoveChildAtIndex(0);
    timePickerRowPattern->HandleHourBuildTimeRange(0);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    EXPECT_EQ(allChildNode["amPm"].Upgrade(), nullptr);
}

/**
 * @tc.name: TimePickerRowPattern007
 * @tc.desc: Test TimePickerRowPattern GetAllChildNode while using 24-hour system but has 3 child node
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern007, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->SetHour24(true);
    EXPECT_EQ(frameNode->GetChildren().size(), CHILD_WITH_AMPM_SIZE);
    timePickerRowPattern->GetAllChildNode();
    EXPECT_EQ(frameNode->children_.size(), CHILD_WITH_AMPM_SIZE);
    EXPECT_TRUE(timePickerRowPattern->amPmId_.has_value());
}

/**
 * @tc.name: TimePickerRowPattern008
 * @tc.desc: Test TimePickerRowPattern HandleHour12Change
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern008, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    std::vector<RefPtr<FrameNode>> tags;
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto amPm = allChildNode["amPm"].Upgrade();
    ASSERT_NE(amPm, nullptr);
    auto amPmPickerColumnPattern = amPm->GetPattern<TimePickerColumnPattern>();

    amPmPickerColumnPattern->SetCurrentIndex(0);
    timePickerRowPattern->HandleHour12Change(true, 11, tags);
    EXPECT_EQ(amPmPickerColumnPattern->GetCurrentIndex(), 1);
    EXPECT_EQ(tags.size(), 1);

    timePickerRowPattern->HandleHour12Change(true, 11, tags);
    EXPECT_EQ(amPmPickerColumnPattern->GetCurrentIndex(), 0);
    EXPECT_EQ(tags.size(), 2);

    timePickerRowPattern->HandleHour12Change(false, 10, tags);
    EXPECT_EQ(amPmPickerColumnPattern->GetCurrentIndex(), 1);
    EXPECT_EQ(tags.size(), 3);

    timePickerRowPattern->HandleHour12Change(false, 10, tags);
    EXPECT_EQ(amPmPickerColumnPattern->GetCurrentIndex(), 0);
    EXPECT_EQ(tags.size(), 4);
}

/**
 * @tc.name: TimePickerRowPattern009
 * @tc.desc: Test TimePickerRowPattern GetAmPmHour
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern009, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    EXPECT_EQ(timePickerRowPattern->GetAmPmHour(0), AM_PM_HOUR_12);
    EXPECT_EQ(timePickerRowPattern->GetAmPmHour(AM_PM_HOUR_12), AM_PM_HOUR_12);
}

/**
 * @tc.name: TimePickerRowPattern010
 * @tc.desc: Test TimePickerRowPattern GetAmPmFormatString and AddZeroPrefix
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern010, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    timePickerRowPattern->vecAmPm_.emplace_back("AM");
    timePickerRowPattern->vecAmPm_.emplace_back("PM");
    EXPECT_EQ(timePickerRowPattern->GetAmFormatString(), "AM");
    EXPECT_EQ(timePickerRowPattern->GetPmFormatString(), "PM");
    EXPECT_EQ(timePickerRowPattern->AddZeroPrefix("5"), "05");
}

/**
 * @tc.name: TimePickerRowPattern011
 * @tc.desc: Test TimePickerRowPattern InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern011, TestSize.Level1)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto focusHub = eventHub->GetOrCreateFocusHub();
    timePickerRowPattern->InitOnKeyEvent(focusHub);
    auto getInnerFocusRectFunc = focusHub->getInnerFocusRectFunc_;

    KeyEvent keyEvent;
    keyEvent.action = KeyAction::UNKNOWN;
    keyEvent.code = KeyCode::KEY_DPAD_UP;
    EXPECT_FALSE(focusHub->ProcessOnKeyEventInternal(keyEvent));

    keyEvent.action = KeyAction::DOWN;
    auto stackChild = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(timePickerRowPattern->focusKeyID_));
    ASSERT_NE(stackChild, nullptr);
    auto blendChild = AceType::DynamicCast<FrameNode>(stackChild->GetLastChild());
    ASSERT_NE(blendChild, nullptr);
    auto pickerChild = AceType::DynamicCast<FrameNode>(blendChild->GetLastChild());
    ASSERT_NE(pickerChild, nullptr);
    auto pattern = pickerChild->GetPattern<TimePickerColumnPattern>();
    ASSERT_NE(pattern, nullptr);
    timePickerRowPattern->options_[pickerChild].clear();
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));

    timePickerRowPattern->options_[pickerChild][0] = "AM";
    timePickerRowPattern->options_[pickerChild][1] = "PM";
    auto currentIndex = pattern->GetCurrentIndex();
    auto totalOptionCount = timePickerRowPattern->GetOptionCount(pickerChild);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(pattern->GetCurrentIndex(), (totalOptionCount + currentIndex - 1) % totalOptionCount);

    keyEvent.code = KeyCode::KEY_DPAD_DOWN;
    currentIndex = pattern->GetCurrentIndex();
    totalOptionCount = timePickerRowPattern->GetOptionCount(pickerChild);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(pattern->GetCurrentIndex(), (totalOptionCount + currentIndex + 1) % totalOptionCount);

    keyEvent.code = KeyCode::KEY_MOVE_HOME;
    currentIndex = pattern->GetCurrentIndex();
    totalOptionCount = timePickerRowPattern->GetOptionCount(pickerChild);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(pattern->GetCurrentIndex(), 0);

    keyEvent.code = KeyCode::KEY_MOVE_END;
    currentIndex = pattern->GetCurrentIndex();
    totalOptionCount = timePickerRowPattern->GetOptionCount(pickerChild);
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(pattern->GetCurrentIndex(), (totalOptionCount - 1));

    keyEvent.code = KeyCode::KEY_DPAD_RIGHT;
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(timePickerRowPattern->focusKeyID_, 1);

    keyEvent.code = KeyCode::KEY_DPAD_LEFT;
    EXPECT_TRUE(focusHub->ProcessOnKeyEventInternal(keyEvent));
    EXPECT_EQ(timePickerRowPattern->focusKeyID_, 0);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto pickerTheme = AceType::MakeRefPtr<PickerTheme>();
    ASSERT_NE(pickerTheme, nullptr);
    pickerTheme->dividerSpacing_ = Dimension(OFFSET_X);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(pickerTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(pickerTheme));
    auto dividerSpacing = pickerTheme->GetDividerSpacing().ConvertToPx();

    // default focusWidth < columnWidth, focusWidth = columnWidth
    RoundRect paintRect;
    getInnerFocusRectFunc(paintRect);
    auto rect = paintRect.GetRect();
    Dimension offset = 2.0_vp;
    Dimension focusLineWidth = 1.5_vp;
    EXPECT_EQ(rect.GetX(), offset.ConvertToPx() + focusLineWidth.ConvertToPx());

    auto centerY =
        (frameNode->GetGeometryNode()->GetFrameSize().Height() - dividerSpacing) / 2 + offset.ConvertToPx() +
        focusLineWidth.ConvertToPx();
    EXPECT_EQ(rect.GetY(), centerY);

    auto expectWidth = pickerChild->GetGeometryNode()->GetFrameSize().Width() - offset.ConvertToPx() * 2 -
        focusLineWidth.ConvertToPx() * 2;
    EXPECT_EQ(rect.Width(), expectWidth);

    EXPECT_EQ(rect.Height(), dividerSpacing - offset.ConvertToPx() * 2 - focusLineWidth.ConvertToPx() * 2);

    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).x,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).y,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS).x,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS).y,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS).x,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS).y,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS).x,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS).y,
        static_cast<RSScalar>(PRESS_RADIUS.ConvertToPx()));

    // default focusWidth < columnWidth
    pickerChild->GetGeometryNode()->frame_.rect_.SetWidth(EXTRA_WIDTH);
    RoundRect paintRect2;
    timePickerRowPattern->GetInnerFocusPaintRect(paintRect2);
    auto rect2 = paintRect2.GetRect();
    
    EXPECT_EQ(rect2.GetX(), offset.ConvertToPx() + focusLineWidth.ConvertToPx());

    auto expectWidth2 = pickerChild->GetGeometryNode()->GetFrameSize().Width() - offset.ConvertToPx() * 2 -
        focusLineWidth.ConvertToPx() * 2;
    EXPECT_EQ(rect2.Width(), expectWidth2);
}

/**
 * @tc.name: TimePickerRowPattern012
 * @tc.desc: Test TimePickerRowPattern OnKeyEvent and HandleDirectionKey false
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern012, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    KeyEvent keyEvent;
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_DPAD_CENTER;
    EXPECT_FALSE(timePickerRowPattern->OnKeyEvent(keyEvent));
    EXPECT_FALSE(timePickerRowPattern->HandleDirectionKey(KeyCode::KEY_DPAD_CENTER));
}

/**
 * @tc.name: TimePickerRowPattern013
 * @tc.desc: Test TimePickerRowPattern SetFocusDisable and SetFocusEnable
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern013, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto host = timePickerRowPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto focusHub = host->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    timePickerRowPattern->SetFocusDisable();
    timePickerRowPattern->SetFocusEnable();
}

/**
 * @tc.name: TimePickerRowPattern014
 * @tc.desc: Test OnLanguageConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern014, TestSize.Level0)
{
    const std::string language = "en";
    const std::string countryOrRegion = "US";
    std::string nodeInfo = "";
    const std::string script = "Latn";
    const std::string keywordsAndValues = "";
    auto dialogTheme = MockPipelineContext::GetCurrent()->GetTheme<DialogTheme>();
    auto contentColumn = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TIME_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });
    auto timePickerPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerPattern, nullptr);
    timePickerNode->MountToParent(contentColumn);
    auto buttonConfirmNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NG::ButtonPattern>(); });
    auto timeConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(buttonConfirmNode, nullptr);
    ASSERT_NE(timeConfirmNode, nullptr);
    timeConfirmNode->MountToParent(buttonConfirmNode);
    timePickerPattern->SetConfirmNode(buttonConfirmNode);
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ASSERT_NE(buttonCancelNode, nullptr);
    auto timeCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(timeCancelNode, nullptr);
    timeCancelNode->MountToParent(buttonCancelNode);
    timePickerPattern->SetCancelNode(buttonCancelNode);
    timePickerPattern->OnLanguageConfigurationUpdate();
    auto cancelNode = dialogTheme->GetCancelText();
    EXPECT_EQ(cancelNode, nodeInfo);
}

/**
 * @tc.name: TimePickerRowPattern015
 * @tc.desc: Test Column Pattern Init Haptic Controller
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern015, TestSize.Level0)
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
     * @tc.steps: step2. call SetIsEnableHaptic.
     * @tc.expected: isHapticChanged is false.
     */
    bool value = true;
    timePickerRowPattern->SetIsEnableHaptic(value);
    EXPECT_FALSE(timePickerRowPattern->isHapticChanged_);
    /**
     * @tc.steps: step3. call SetIsEnableHaptic.
     * @tc.expected: isHapticChanged is true.
     */
    value = false;
    timePickerRowPattern->SetIsEnableHaptic(value);
    bool isEnableHaptic = timePickerRowPattern->GetIsEnableHaptic();
    EXPECT_FALSE(isEnableHaptic);
    EXPECT_TRUE(timePickerRowPattern->isHapticChanged_);
}

/**
 * @tc.name: TimePickerRowPattern016
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern016, TestSize.Level0)
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
     * @tc.steps: step2. call OnModifyDone.
     * @tc.expected: set isHapticChanged is true and isForceUpdate_ is false and isFiredTimeChange_ is false.
     */
    timePickerRowPattern->isFiredTimeChange_ = true;
    timePickerRowPattern->isForceUpdate_ = false;
    timePickerRowPattern->isFiredTimeChange_ = false;
    timePickerRowPattern->OnModifyDone();
    EXPECT_FALSE(timePickerRowPattern->isFiredTimeChange_);
    /**
     * @tc.steps: step3. call SetIsEnableHaptic.
     * @tc.expected: set isHapticChanged is true and isForceUpdate_ is true and isFiredTimeChange_ is false.
     */
    timePickerRowPattern->isFiredTimeChange_ = true;
    timePickerRowPattern->isForceUpdate_ = true;
    timePickerRowPattern->isFiredTimeChange_ = false;
    timePickerRowPattern->OnModifyDone();
    EXPECT_FALSE(timePickerRowPattern->isFiredTimeChange_);
    /**
     * @tc.steps: step4. call SetIsEnableHaptic.
     * @tc.expected: set isHapticChanged is true and isForceUpdate_ is false and isFiredTimeChange_ is true.
     */
    timePickerRowPattern->isFiredTimeChange_ = true;
    timePickerRowPattern->isForceUpdate_ = false;
    timePickerRowPattern->isFiredTimeChange_ = true;
    timePickerRowPattern->OnModifyDone();
    EXPECT_FALSE(timePickerRowPattern->isFiredTimeChange_);
}

/**
 * @tc.name: TimePickerRowPattern017
 * @tc.desc: Test OnModifyDone2
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern017, TestSize.Level0)
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
     * @tc.steps: step2. call OnModifyDone.
     * @tc.expected: set isHapticChanged is false and isForceUpdate_ is true and isFiredTimeChange_ is true.
     */
    timePickerRowPattern->isFiredTimeChange_ = false;
    timePickerRowPattern->isForceUpdate_ = true;
    timePickerRowPattern->isFiredTimeChange_ = true;
    timePickerRowPattern->OnModifyDone();
    EXPECT_TRUE(timePickerRowPattern->isFiredTimeChange_);
    /**
     * @tc.steps: step2. call OnModifyDone.
     * @tc.expected: set isHapticChanged is false and isForceUpdate_ is false and isFiredTimeChange_ is false.
     */
    timePickerRowPattern->isFiredTimeChange_ = false;
    timePickerRowPattern->isForceUpdate_ = false;
    timePickerRowPattern->isFiredTimeChange_ = false;
    timePickerRowPattern->OnModifyDone();
    EXPECT_FALSE(timePickerRowPattern->isFiredTimeChange_);
    /**
     * @tc.steps: step2. call OnModifyDone.
     * @tc.expected: set isHapticChanged is true and isForceUpdate_ is true and isFiredTimeChange_ is true.
     */
    timePickerRowPattern->isFiredTimeChange_ = true;
    timePickerRowPattern->isForceUpdate_ = true;
    timePickerRowPattern->isFiredTimeChange_ = true;
    timePickerRowPattern->OnModifyDone();
    EXPECT_TRUE(timePickerRowPattern->isFiredTimeChange_);
}

/**
 * @tc.name: TimePickerRowPattern018
 * @tc.desc: Test Init Disabled
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern018, TestSize.Level0)
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
     * @tc.steps: step2. call InitDisabled.
     * @tc.expected: set eventHub is disenabled.
     */
    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->enabled_ = false;
    timePickerRowPattern->InitDisabled();
    bool res = eventHub->IsEnabled();
    EXPECT_FALSE(res);
}

/**
 * @tc.name: TimePickerRowPattern019
 * @tc.desc: Test mount second Node
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern019, TestSize.Level0)
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
     * @tc.steps: step2. call MountSecondNode.
     * @tc.expected: set HasAmPmNode is true and language_ is not "ug".
     */
    std::optional<int32_t> temp;
    temp.emplace(100);
    timePickerRowPattern->secondId_ = temp;
    bool hasValue = timePickerRowPattern->secondId_.has_value();
    std::string tag = "testNode";
    int32_t nodeId = 212;
    RefPtr<FrameNode> stackSecondNode = FrameNode::CreateFrameNode(tag, nodeId, timePickerRowPattern);
    timePickerRowPattern->amPmTimeOrder_ = "01";
    timePickerRowPattern->MountSecondNode(stackSecondNode);
    bool res = timePickerRowPattern->HasAmPmNode();
    EXPECT_TRUE(hasValue);
    EXPECT_TRUE(res);
    /**
     * @tc.steps: step2. call RemoveSecondNode.
     * @tc.expected: set HasAmPmNode is true and language_ is "ug".
     */
    timePickerRowPattern->amPmTimeOrder_ = "02";
    timePickerRowPattern->language_ = "ug";
    timePickerRowPattern->MountSecondNode(stackSecondNode);
    res = timePickerRowPattern->HasAmPmNode();
    EXPECT_TRUE(res);
}

/**
 * @tc.name: TimePickerRowPattern020
 * @tc.desc: Test mount second Node2
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern020, TestSize.Level0)
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
     * @tc.steps: step2. call MountSecondNode.
     * @tc.expected: set HasAmPmNode is false and language_ is "ug".
     */
    timePickerRowPattern->amPmId_ = std::nullopt;
    bool hasValue = timePickerRowPattern->amPmId_.has_value();
    bool res = timePickerRowPattern->HasAmPmNode();

    std::string tag = "testNode";
    int32_t nodeId = 212;
    RefPtr<FrameNode> stackSecondNode = FrameNode::CreateFrameNode(tag, nodeId, timePickerRowPattern);
    timePickerRowPattern->amPmTimeOrder_ = "02";
    timePickerRowPattern->language_ = "ug";
    timePickerRowPattern->MountSecondNode(stackSecondNode);
    EXPECT_FALSE(hasValue);
    /**
     * @tc.steps: step2. call MountSecondNode.
     * @tc.expected: set HasAmPmNode is false and language_ is "ug".
     */
    timePickerRowPattern->language_ = "test";
    timePickerRowPattern->MountSecondNode(stackSecondNode);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: TimePickerRowPattern021
 * @tc.desc: Test remove second Node
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern021, TestSize.Level0)
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
     * @tc.steps: step2. call RemoveSecondNode.
     * @tc.expected: set HasAmPmNode is false and language_ is "ug".
     */
    timePickerRowPattern->amPmId_ = std::nullopt;
    bool hasValue = timePickerRowPattern->amPmId_.has_value();
    bool res = timePickerRowPattern->HasAmPmNode();
    timePickerRowPattern->amPmTimeOrder_ = "02";
    timePickerRowPattern->language_ = "ug";
    EXPECT_FALSE(hasValue);
    /**
     * @tc.steps: step2. call RemoveSecondNode.
     * @tc.expected: set language_ is not "ug".
     */
    timePickerRowPattern->RemoveSecondNode();
    timePickerRowPattern->language_ = "test";
    timePickerRowPattern->RemoveSecondNode();
    EXPECT_FALSE(res);
}

/**
 * @tc.name: TimePickerRowPattern022
 * @tc.desc: Test remove second Node
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern022, TestSize.Level0)
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
     * @tc.steps: step2. call RemoveSecondNode.
     * @tc.expected: set HasAmPmNode is true and language_ is not "ug".
     */
    std::optional<int32_t> temp;
    temp.emplace(100);
    timePickerRowPattern->secondId_ = temp;
    bool hasValue = timePickerRowPattern->amPmId_.has_value();
    bool res = timePickerRowPattern->HasAmPmNode();
    timePickerRowPattern->amPmTimeOrder_ = "01";
    timePickerRowPattern->RemoveSecondNode();
    EXPECT_TRUE(hasValue);
    /**
     * @tc.steps: step2. call RemoveSecondNode.
     * @tc.expected: set language_ is "ug".
     */
    timePickerRowPattern->amPmTimeOrder_ = "02";
    timePickerRowPattern->language_ = "ug";
    timePickerRowPattern->RemoveSecondNode();
    EXPECT_TRUE(res);
}

/**
 * @tc.name: TimePickerRowPattern023
 * @tc.desc: On font Configuration Update
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern023, TestSize.Level0)
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
     * @tc.steps: step2. call OnFontConfigurationUpdate.
     * @tc.expected: set close dialog event.
     */
    TimePickerSettingData settingData;
    settingData.properties.disappearTextStyle_.textColor = Color::RED;
    settingData.properties.disappearTextStyle_.fontSize = Dimension(0);
    settingData.properties.disappearTextStyle_.fontWeight = Ace::FontWeight::BOLD;
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
    std::function<void()> closeDialogEvent = [weak = WeakPtr<FrameNode>(dialogNode), timePickerRowPattern]() {
        auto dialogNode = weak.Upgrade();
        auto pipeline = dialogNode->GetContext();
        auto overlayManager = pipeline->GetOverlayManager();
        overlayManager->CloseDialog(dialogNode);
        timePickerRowPattern->SetIsShowInDialog(false);
    };
    timePickerRowPattern->updateFontConfigurationEvent(closeDialogEvent);
    timePickerRowPattern->OnFontConfigurationUpdate();
    EXPECT_NE(closeDialogEvent, nullptr);
}

/**
 * @tc.name: TimePickerRowPattern024
 * @tc.desc: Test UpdateButtonMargin.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern024, TestSize.Level0)
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
     * @tc.steps: step2. call UpdateButtonMargin.
     * @tc.expected: set api version is 10.
     */
    int32_t setApiVersion = 10;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t currApiVersion = MockContainer::Current()->GetApiTargetVersion();
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(buttonCancelNode, nullptr);
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    timePickerRowPattern->UpdateButtonMargin(buttonCancelNode, dialogTheme, true);
    EXPECT_EQ(currApiVersion, setApiVersion);
    /**
     * @tc.steps: step3. call UpdateButtonMargin.
     * @tc.expected: set api version is 16.
     */
    setApiVersion = 16;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    currApiVersion = MockContainer::Current()->GetApiTargetVersion();
    timePickerRowPattern->UpdateButtonMargin(buttonCancelNode, dialogTheme, true);
    EXPECT_EQ(currApiVersion, setApiVersion);
}

/**
 * @tc.name: TimePickerRowPattern025
 * @tc.desc: Test OnLanguageConfigurationUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern025, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_NE(timePickerRowPattern, nullptr);
    /**
     * @tc.steps: step1. call OnLanguageConfigurationUpdate.
     * @tc.expected: set timeOrder is "01" and isAmPmTimeOrderUpdate_ is true.
     */
    bool value = false;
    timePickerRowPattern->SetHour24(value);
    std::string timeOrder = "01";
    timePickerRowPattern->amPmTimeOrder_ = timeOrder;
    timePickerRowPattern->isAmPmTimeOrderUpdate_ = true;
    timePickerRowPattern->OnLanguageConfigurationUpdate();
    bool isHour24 = timePickerRowPattern->GetHour24();
    EXPECT_FALSE(isHour24);
    /**
     * @tc.steps: step2. call OnLanguageConfigurationUpdate.
     * @tc.expected: set timeOrder is "01" and isAmPmTimeOrderUpdate_ is false.
     */
    timePickerRowPattern->amPmTimeOrder_ = timeOrder;
    timePickerRowPattern->isAmPmTimeOrderUpdate_ = value;
    EXPECT_FALSE(timePickerRowPattern->isAmPmTimeOrderUpdate_);
    timePickerRowPattern->OnLanguageConfigurationUpdate();
    EXPECT_TRUE(timePickerRowPattern->isAmPmTimeOrderUpdate_);
    /**
     * @tc.steps: step3. call OnLanguageConfigurationUpdate.
     * @tc.expected: set timeOrder is "10" and isAmPmTimeOrderUpdate_ is true.
     */
    timeOrder = "10";
    timePickerRowPattern->amPmTimeOrder_ = timeOrder;
    EXPECT_EQ(timePickerRowPattern->amPmTimeOrder_, timeOrder);
    timePickerRowPattern->isAmPmTimeOrderUpdate_ = true;
    timePickerRowPattern->OnLanguageConfigurationUpdate();
    EXPECT_NE(timePickerRowPattern->amPmTimeOrder_, timeOrder);
    /**
     * @tc.steps: step4. call OnLanguageConfigurationUpdate.
     * @tc.expected: set timeOrder is "10" and isAmPmTimeOrderUpdate_ is false.
     */
    timePickerRowPattern->amPmTimeOrder_ = timeOrder;
    timePickerRowPattern->isAmPmTimeOrderUpdate_ = value;
    EXPECT_FALSE(timePickerRowPattern->isAmPmTimeOrderUpdate_);
    timePickerRowPattern->OnLanguageConfigurationUpdate();
    EXPECT_TRUE(timePickerRowPattern->isAmPmTimeOrderUpdate_);
}

/**
 * @tc.name: TimePickerRowPattern026
 * @tc.desc: Test UpdateNodePositionForUg.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern026, TestSize.Level0)
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
     * @tc.steps: step2. call OnLanguageConfigurationUpdate.
     * @tc.expected: set language is "ug" and hasSecond is true.
     */
    std::string language = "ug";
    bool value = true;
    timePickerRowPattern->isPreLanguageUg_ = value;
    timePickerRowPattern->language_ = language;
    timePickerRowPattern->isAmPmTimeOrderUpdate_ = value;
    timePickerRowPattern->SetHasSecond(value);
    bool hasSecond = timePickerRowPattern->GetHasSecond();
    timePickerRowPattern->UpdateNodePositionForUg();
    EXPECT_TRUE(hasSecond);
    /**
     * @tc.steps: step3. call OnLanguageConfigurationUpdate.
     * @tc.expected: set language is "ug" and hasSecond is false.
     */
    timePickerRowPattern->SetHasSecond(false);
    hasSecond = timePickerRowPattern->GetHasSecond();
    timePickerRowPattern->UpdateNodePositionForUg();
    EXPECT_FALSE(hasSecond);
    /**
     * @tc.steps: step3. call OnLanguageConfigurationUpdate.
     * @tc.expected: set isAmPmTimeOrderUpdate_ is false and hasSecond is false.
     */
    timePickerRowPattern->isAmPmTimeOrderUpdate_ = false;
    timePickerRowPattern->SetHasSecond(false);
    timePickerRowPattern->UpdateNodePositionForUg();
    EXPECT_FALSE(timePickerRowPattern->isAmPmTimeOrderUpdate_);
    /**
     * @tc.steps: step3. call OnLanguageConfigurationUpdate.
     * @tc.expected: set isAmPmTimeOrderUpdate_ is false and hasSecond is true.
     */
    timePickerRowPattern->SetHasSecond(value);
    hasSecond = timePickerRowPattern->GetHasSecond();
    timePickerRowPattern->UpdateNodePositionForUg();
    EXPECT_TRUE(hasSecond);
}

/**
 * @tc.name: TimePickerRowPattern027
 * @tc.desc: Test UpdateButtonMargin.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern027, TestSize.Level0)
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
     * @tc.steps: step2. call UpdateButtonMargin.
     * @tc.expected: set api version is 11.
     */
    int32_t setApiVersion = 11;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t currApiVersion = MockContainer::Current()->GetApiTargetVersion();
    auto buttonCancelNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(buttonCancelNode, nullptr);
    auto dialogTheme = AceType::MakeRefPtr<DialogTheme>();
    timePickerRowPattern->UpdateButtonMargin(buttonCancelNode, dialogTheme, false);
    EXPECT_EQ(currApiVersion, setApiVersion);
    /**
     * @tc.steps: step3. call UpdateButtonMargin.
     * @tc.expected: set api version is 16.
     */
    setApiVersion = 16;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    currApiVersion = MockContainer::Current()->GetApiTargetVersion();
    timePickerRowPattern->UpdateButtonMargin(buttonCancelNode, dialogTheme, false);
    EXPECT_EQ(currApiVersion, setApiVersion);
}

/**
 * @tc.name: TimePickerRowPattern028
 * @tc.desc: Test CalcLeftTotalColumnWidth.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern028, TestSize.Level0)
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
     * @tc.steps: step2. call CalcLeftTotalColumnWidth.
     * @tc.expected: set the page layout mode is from right to left.
     */
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    EXPECT_NE(pipeline, nullptr);
    bool isRtl = true;
    pipeline->SetIsRightToLeft(isRtl);
    float leftTotalColumnWidth = 50.0f;
    float childSize = 10.0f;
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    bool res = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    columnNode_ = allChildNode["minute"].Upgrade();
    EXPECT_NE(columnNode_, nullptr);
    timePickerRowPattern->CalcLeftTotalColumnWidth(columnNode_, leftTotalColumnWidth, childSize);
    EXPECT_TRUE(res);
}

/**
 * @tc.name: TimePickerRowPattern029
 * @tc.desc: Test GetSecondColumnFormatString.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern029, TestSize.Level0)
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
     * @tc.steps: step2. call GetSecondColumnFormatString.
     * @tc.expected: set Api Version is 15.
     */
    int32_t setApiVersion = 15;
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    int32_t currApiVersion = MockContainer::Current()->GetApiTargetVersion();
    uint32_t second = 12;
    timePickerRowPattern->GetSecondColumnFormatString(second);
    EXPECT_GT(currApiVersion, second);
}

/**
 * @tc.name: TimePickerRowPattern030
 * @tc.desc: Test CheckFocusID.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern030, TestSize.Level0)
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
     * @tc.expected: set focusKeyID is greater than childSize.
     */
    int32_t value = 5;
    timePickerRowPattern->SetCurrentFocusKeyID(value);
    int32_t focusKeyID = timePickerRowPattern->GetCurrentFocusKeyID();
    EXPECT_EQ(focusKeyID, value);
    int32_t childSize = 3;
    EXPECT_GT(focusKeyID, childSize - 1);
    timePickerRowPattern->CheckFocusID(childSize);
    focusKeyID = timePickerRowPattern->GetCurrentFocusKeyID();
    EXPECT_EQ(focusKeyID, childSize - 1);
    /**
     * @tc.steps: step3. call CheckFocusID.
     * @tc.expected: set focusKeyID is less than childSize.
     */
    value = -1;
    childSize = 8;
    timePickerRowPattern->SetCurrentFocusKeyID(value);
    bool res = timePickerRowPattern->CheckFocusID(childSize);
    focusKeyID = timePickerRowPattern->GetCurrentFocusKeyID();
    EXPECT_FALSE(res);
    EXPECT_EQ(focusKeyID, 0);
}

/**
 * @tc.name: TimePickerRowPattern031
 * @tc.desc: Test TimePickerRowPattern GetAllChildNode while using 24-hour system but has 3 child node
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern031, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    TimePickerModelNG::SetHour24(frameNode, false);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    TimePickerModelNG::SetHour24(frameNode, true);
    EXPECT_EQ(frameNode->GetChildren().size(), CHILD_WITH_AMPM_SIZE);
    timePickerRowPattern->GetAllChildNode();
    EXPECT_EQ(frameNode->children_.size(), CHILD_WITH_AMPM_SIZE);
    EXPECT_TRUE(timePickerRowPattern->amPmId_.has_value());
}

/**
 * @tc.name: TimePickerRowPattern033
 * @tc.desc: Test TimePickerRowPattern InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern033, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    TimePickerModelNG::GetInstance()->SetHour24(false);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto focusHub = eventHub->GetOrCreateFocusHub();
    timePickerRowPattern->InitOnKeyEvent(focusHub);
    auto getInnerFocusRectFunc = focusHub->getInnerFocusRectFunc_;
    timePickerRowPattern->useButtonFocusArea_ = true;
    RoundRect paintRect;
    getInnerFocusRectFunc(paintRect);
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).x,
        static_cast<RSScalar>((theme->GetSelectorItemRadius() + PICKER_PRESS_RADIUS).ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS).y,
        static_cast<RSScalar>((theme->GetSelectorItemRadius() + PICKER_PRESS_RADIUS).ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS).x,
        static_cast<RSScalar>((theme->GetSelectorItemRadius() + PICKER_PRESS_RADIUS).ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS).y,
        static_cast<RSScalar>((theme->GetSelectorItemRadius() + PICKER_PRESS_RADIUS).ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS).x,
        static_cast<RSScalar>((theme->GetSelectorItemRadius() + PICKER_PRESS_RADIUS).ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS).y,
        static_cast<RSScalar>((theme->GetSelectorItemRadius() + PICKER_PRESS_RADIUS).ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS).x,
        static_cast<RSScalar>((theme->GetSelectorItemRadius() + PICKER_PRESS_RADIUS).ConvertToPx()));
    EXPECT_EQ(paintRect.GetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS).y,
        static_cast<RSScalar>((theme->GetSelectorItemRadius() + PICKER_PRESS_RADIUS).ConvertToPx()));
}

/**
 * @tc.name: TimePickerRowPattern034
 * @tc.desc: Test TimePickerRowPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerRowPattern034, TestSize.Level0)
{
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    frameNode->MarkModifyDone();
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    ASSERT_NE(timePickerRowPattern, nullptr);

    frameNode->GetGeometryNode()->frame_.rect_.SetWidth(EXTRA_WIDTH);
    auto dirty = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());
    DirtySwapConfig config;
    config.frameSizeChange = true;
    timePickerRowPattern->useButtonFocusArea_ = true;
    EXPECT_TRUE(timePickerRowPattern->OnDirtyLayoutWrapperSwap(dirty, config));
}

/**
 * @tc.name: TimePickerDialogViewUpdateCancelButtonTextLayoutProperty001
 * @tc.desc: Test TimePickerDialogView UpdateCancelButtonTextLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerDialogViewUpdateCancelButtonTextLayoutProperty001, TestSize.Level1)
{
    auto pickerTheme = AceType::MakeRefPtr<PickerTheme>();
    ASSERT_NE(pickerTheme, nullptr);
    auto textCancelNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textCancelNode, nullptr);
    auto textCancelLayoutProperty = textCancelNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textCancelLayoutProperty, nullptr);
    TimePickerDialogView::useButtonFocusArea_ = true;
    TimePickerDialogView::UpdateCancelButtonTextLayoutProperty(textCancelLayoutProperty, pickerTheme);
    EXPECT_EQ(textCancelLayoutProperty->GetTextColor(), pickerTheme->GetTitleStyle().GetTextColor());
}

/**
 * @tc.name: TimePickerDialogViewUpdateConfirmButtonTextLayoutProperty001
 * @tc.desc: Test TimePickerDialogView UpdateConfirmButtonTextLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerRowPatternTestNg, TimePickerDialogViewUpdateConfirmButtonTextLayoutProperty001, TestSize.Level1)
{
    auto pickerTheme = AceType::MakeRefPtr<PickerTheme>();
    ASSERT_NE(pickerTheme, nullptr);
    auto textConfirmNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textConfirmNode, nullptr);
    auto textLayoutProperty = textConfirmNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    TimePickerDialogView::useButtonFocusArea_ = true;
    TimePickerDialogView::UpdateConfirmButtonTextLayoutProperty(textLayoutProperty, pickerTheme);
    EXPECT_EQ(textLayoutProperty->GetTextColor(), pickerTheme->GetTitleStyle().GetTextColor());
}
} // namespace OHOS::Ace::NG
