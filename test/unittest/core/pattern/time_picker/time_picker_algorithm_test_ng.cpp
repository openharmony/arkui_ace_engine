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
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_theme_default.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/dimension.h"
#include "base/geometry/offset.h"
#include "base/geometry/point.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/animation/curves.h"
#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_data.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include "core/components_ng/pattern/time_picker/toss_animation_controller.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_info.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const int MIDDLE_OF_COUNTS = 2;
const int SHOW_COUNT = 7;
const std::string AM = "上午";
const std::string PM = "下午";
constexpr double SECLECTED_TEXTNODE_HEIGHT = 84.0;
constexpr double OTHER_TEXTNODE_HEIGHT = 54.0;

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
class TimePickerAlgorithmTest : public testing::Test {
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

void TimePickerAlgorithmTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void TimePickerAlgorithmTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TimePickerAlgorithmTest::SetUp()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void TimePickerAlgorithmTest::TearDown()
{
    MockPipelineContext::GetCurrent()->themeManager_ = nullptr;
    ViewStackProcessor::GetInstance()->ClearStack();
}

void TimePickerAlgorithmTest::CreateTimePickerColumnNode()
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
 * @tc.name: TimePickerAlgorithmTest001
 * @tc.desc: Test GetPickerMaxHeight.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerAlgorithmTest, TimePickerAlgorithmTest001, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and pattern.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);

    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    auto layoutConstraint = LayoutConstraintF();
    layoutConstraint.selfIdealSize.SetWidth(20);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_TRUE(timePickerRowPattern);
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto minuteColumn = allChildNode["minute"].Upgrade();
    EXPECT_TRUE(minuteColumn);
    auto minuteColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    EXPECT_TRUE(minuteColumnPattern);
    auto columnBlend = AceType::DynamicCast<FrameNode>(minuteColumn->GetParent());
    EXPECT_TRUE(columnBlend);
    auto blendLayoutProperty = columnBlend->GetLayoutProperty();
    blendLayoutProperty->UpdateLayoutConstraint(layoutConstraint);
    blendLayoutProperty->UpdateContentConstraint();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(minuteColumn, minuteColumn->GetGeometryNode(), pickerProperty);
    /**
     * @tc.steps: step2. call GetPickerMaxHeight.
     * @tc.expected: set show lunar switch.
     */
    TimePickerColumnLayoutAlgorithm timePickerColumnLayoutAlgorithm;
    timePickerColumnLayoutAlgorithm.Layout(&layoutWrapper);
    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        V2::TIME_PICKER_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });
    auto timePickerPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    timePickerPattern->SetIsShowInDialog(true);
    timePickerPattern->SetShowLunarSwitch(true);
    float res = timePickerColumnLayoutAlgorithm.GetPickerMaxHeight(layoutConstraint, timePickerNode);
    EXPECT_TRUE(timePickerPattern->GetShowLunarSwitch());
    timePickerPattern->SetShowLunarSwitch(false);
    res = timePickerColumnLayoutAlgorithm.GetPickerMaxHeight(layoutConstraint, timePickerNode);
    EXPECT_FALSE(timePickerPattern->GetShowLunarSwitch());
}

/**
 * @tc.name: TimePickerAlgorithmTest002
 * @tc.desc: Test ChangeAmPmTextStyle.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerAlgorithmTest, TimePickerAlgorithmTest002, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and timePickerColumnLayoutAlgorithm.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto layoutConstraint = LayoutConstraintF();
    layoutConstraint.selfIdealSize.SetWidth(20);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_TRUE(timePickerRowPattern);
    TimePickerColumnLayoutAlgorithm timePickerColumnLayoutAlgorithm;
    /**
     * @tc.steps: step2. call ChangeAmPmTextStyle.
     * @tc.expected: change AmPm text style.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    auto weakNode = AceType::WeakClaim(AceType::RawPtr(buttonNode));
    auto layoutWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        weakNode, AceType::MakeRefPtr<GeometryNode>(), AceType::MakeRefPtr<LayoutProperty>());

    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));
    auto customNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(customNode, nullptr);
    auto childLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        customNode, customNode->GetGeometryNode(), customNode->GetLayoutProperty());
    EXPECT_NE(childLayoutWrapper, nullptr);
    auto layoutChildConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto res = layoutChildConstraint.selfIdealSize.Height();

    uint32_t index = 2;
    uint32_t showOptionCount = 4;
    SizeF size(4, 6);
    timePickerColumnLayoutAlgorithm.ChangeAmPmTextStyle(index, showOptionCount, size,
        childLayoutWrapper, layoutWrapper);
    EXPECT_EQ(res, std::nullopt);

    index = 3;
    timePickerColumnLayoutAlgorithm.ChangeAmPmTextStyle(index, showOptionCount, size,
        childLayoutWrapper, layoutWrapper);
    EXPECT_EQ(res, std::nullopt);
}

/**
 * @tc.name: TimePickerAlgorithmTest003
 * @tc.desc: Test NeedAdaptForAging.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerAlgorithmTest, TimePickerAlgorithmTest003, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and timePickerColumnLayoutAlgorithm.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto layoutConstraint = LayoutConstraintF();
    layoutConstraint.selfIdealSize.SetWidth(20);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_TRUE(timePickerRowPattern);
    TimePickerColumnLayoutAlgorithm timePickerColumnLayoutAlgorithm;
    /**
     * @tc.steps: step2. call NeedAdaptForAging.
     * @tc.expected: set NeedAdaptForAging return false.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    EXPECT_TRUE(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    EXPECT_TRUE(pickerTheme);
    pipeline->SetFollowSystem(true);
    pipeline->SetMaxAppFontScale(10.0f);
    pipeline->SetFontScale(0);
    pickerTheme->pickerDialogMaxOneFontScale_ = 5;
    bool res = timePickerColumnLayoutAlgorithm.NeedAdaptForAging();
    EXPECT_FALSE(res);
    /**
     * @tc.steps: step3. call NeedAdaptForAging.
     * @tc.expected: set NeedAdaptForAging return true.
     */
    pipeline->SetFontScale(10);
    pipeline->rootHeight_ = 1000;
    res = timePickerColumnLayoutAlgorithm.NeedAdaptForAging();
    EXPECT_TRUE(res);
}

/**
 * @tc.name: TimePickerAlgorithmTest004
 * @tc.desc: Test AdjustFontSizeScale.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerAlgorithmTest, TimePickerAlgorithmTest004, TestSize.Level1)
{
    /**
     * @tc.step: step1. create frameNode and timePickerColumnLayoutAlgorithm.
     */
    auto theme = MockPipelineContext::GetCurrent()->GetTheme<PickerTheme>();
    TimePickerModelNG::GetInstance()->CreateTimePicker(theme);
    SystemProperties::SetDeviceOrientation(static_cast<int32_t>(DeviceOrientation::LANDSCAPE));
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_TRUE(frameNode);
    frameNode->MarkModifyDone();
    auto layoutConstraint = LayoutConstraintF();
    layoutConstraint.selfIdealSize.SetWidth(20);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    EXPECT_TRUE(timePickerRowPattern);
    TimePickerColumnLayoutAlgorithm timePickerColumnLayoutAlgorithm;
    /**
     * @tc.steps: step2. call AdjustFontSizeScale.
     * @tc.expected: set fontScale is not zero.
     */
    Dimension fontSizeValue = 50.0_vp;
    double fontScale = 10.75;
    Dimension temp = 0.0_vp;
    auto res = timePickerColumnLayoutAlgorithm.AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_NE(res, temp);
    /**
     * @tc.steps: step3. call AdjustFontSizeScale.
     * @tc.expected: set fontScale is zero.
     */
    fontScale = 0;
    res = timePickerColumnLayoutAlgorithm.AdjustFontSizeScale(fontSizeValue, fontScale);
    EXPECT_EQ(res, temp);
}

/**
 * @tc.name: TimePickerAlgorithmTest005
 * @tc.desc: Test OnWindowShow.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerAlgorithmTest, TimePickerAlgorithmTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnPattern and Set text node height.
     */
    CreateTimePickerColumnNode();
    EXPECT_NE(columnPattern_, nullptr);
    EXPECT_NE(columnNode_, nullptr);
    auto childSize = static_cast<int32_t>(columnNode_->GetChildren().size());
    auto midSize = childSize / MIDDLE_OF_COUNTS;
    columnPattern_->optionProperties_[midSize].height = SECLECTED_TEXTNODE_HEIGHT;
    columnPattern_->optionProperties_[midSize - 1].height = OTHER_TEXTNODE_HEIGHT;
    /**
     * @tc.steps: step2. call OnWindowShow.
     * @tc.expected: set isShow success.
     */
    columnPattern_->OnWindowShow();
    bool isShow = columnPattern_->isShow_;
    EXPECT_TRUE(isShow);
}

/**
 * @tc.name: TimePickerAlgorithmTest006
 * @tc.desc: Test ResetAlgorithmOffset.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerAlgorithmTest, TimePickerAlgorithmTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnPattern and Set text node height.
     */
    CreateTimePickerColumnNode();
    EXPECT_NE(columnPattern_, nullptr);
    EXPECT_NE(columnNode_, nullptr);
    auto childSize = static_cast<int32_t>(columnNode_->GetChildren().size());
    auto midSize = childSize / MIDDLE_OF_COUNTS;
    columnPattern_->optionProperties_[midSize].height = SECLECTED_TEXTNODE_HEIGHT;
    columnPattern_->optionProperties_[midSize - 1].height = OTHER_TEXTNODE_HEIGHT;
    /**
     * @tc.steps: step2. call ResetAlgorithmOffset.
     * @tc.expected: clear algorithmOffset success.
     */
    columnPattern_->ResetAlgorithmOffset();
    auto offset = columnPattern_->algorithmOffset_;
    auto size = offset.size();
    auto count = columnPattern_->GetShowCount();
    EXPECT_EQ(size, count);
}

/**
 * @tc.name: TimePickerAlgorithmTest007
 * @tc.desc: Test UpdateScrollDelta.
 * @tc.type: FUNC
 */
HWTEST_F(TimePickerAlgorithmTest, TimePickerAlgorithmTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create columnPattern and Set text node height.
     */
    CreateTimePickerColumnNode();
    EXPECT_NE(columnPattern_, nullptr);
    EXPECT_NE(columnNode_, nullptr);
    auto childSize = static_cast<int32_t>(columnNode_->GetChildren().size());
    auto midSize = childSize / MIDDLE_OF_COUNTS;
    columnPattern_->optionProperties_[midSize].height = SECLECTED_TEXTNODE_HEIGHT;
    columnPattern_->optionProperties_[midSize - 1].height = OTHER_TEXTNODE_HEIGHT;
    /**
     * @tc.steps: step2. call UpdateScrollDelta.
     * @tc.expected: set current offset success.
     */
    double delta = 5.75;
    columnPattern_->UpdateScrollDelta(delta);
    float offset = columnPattern_->GetCurrentOffset();
    EXPECT_EQ(offset, delta);
}
} // namespace OHOS::Ace::NG
