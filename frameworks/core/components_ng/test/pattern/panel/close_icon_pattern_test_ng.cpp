/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <cstddef>
#include <optional>

#include "gtest/gtest.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "core/components/common/layout/constants.h"

#define private public
#include "base/geometry/dimension.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/panel/close_icon_layout_algorithm.h"
#include "core/components_ng/pattern/panel/close_icon_layout_property.h"
#include "core/components_ng/pattern/panel/close_icon_pattern.h"
#include "core/components_ng/pattern/panel/sliding_panel_layout_property.h"
#include "core/components_ng/pattern/panel/sliding_panel_model_ng.h"
#include "core/components_ng/pattern/panel/sliding_panel_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr bool SLIDING_PANEL_SHOW = true;
constexpr float ZERO = 0.0f;
constexpr Dimension PANEL_CLOSE_ICON_WIDTH = 24.0_vp;
constexpr Dimension PANEL_CLOSE_ICON_Height = 24.0_vp;
constexpr Dimension PANEL_CLOSE_ICON_MARGIN_TOP = 20.0_vp;
constexpr Dimension PANEL_CLOSE_ICON_MARGIN_RIGHT = 24.0_vp;
constexpr Dimension PANEL_CLOSE_ICON_RADIUS = 12.0_vp;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
const OffsetF ORIGIN_POINT(ZERO, ZERO);
const SizeF CONTAINER_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
} // namespace

class CloseIconPatternTestNg : public testing::Test {
public:
    PaddingProperty CreatePadding(float left, float top, float right, float bottom)
    {
        PaddingProperty padding;
        padding.left = CalcLength(left);
        padding.right = CalcLength(right);
        padding.top = CalcLength(top);
        padding.bottom = CalcLength(bottom);
        return padding;
    }
};

/**
 * @tc.name: CloseIconPatternTest001
 * @tc.desc: Verify whether the layout property, layoutAlgorithm functions are created.
 * @tc.type: FUNC
 */
HWTEST_F(CloseIconPatternTestNg, CloseIconPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. add closeIcon to slidingPanel.
     */
    auto closeIcon = FrameNode::GetOrCreateFrameNode(V2::PANEL_CLOSE_ICON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<CloseIconPattern>(); });
    closeIcon->MountToParent(frameNode, 1);
    auto layoutproperty = closeIcon->GetLayoutProperty<CloseIconLayoutProperty>();
    layoutproperty->UpdateCloseIconWidth(PANEL_CLOSE_ICON_WIDTH);
    layoutproperty->UpdateCloseIconHeight(PANEL_CLOSE_ICON_Height);
    layoutproperty->UpdateCloseIconRadius(PANEL_CLOSE_ICON_RADIUS);
    closeIcon->MarkModifyDone();
    /**
     * @tc.steps: step3. get pattern and create layout property, layoutAlgorithm.
     * @tc.expected: step3. related function is called.
     */
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    auto closeIconNode = slidingPanelPattern->GetCloseIconNode();
    EXPECT_EQ(closeIcon, closeIconNode);
    auto pattern = closeIconNode->GetPattern<CloseIconPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutProPerty = pattern->CreateLayoutProperty();
    ASSERT_NE(layoutProPerty, nullptr);
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
}

/**
 * @tc.name: CloseIconPatternTest002
 * @tc.desc: Test closeIcon onModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(CloseIconPatternTestNg, CloseIconPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. add closeIcon to slidingPanel.
     */
    auto closeIcon = FrameNode::GetOrCreateFrameNode(V2::PANEL_CLOSE_ICON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<CloseIconPattern>(); });
    closeIcon->MountToParent(frameNode, 1);
    auto layoutproperty = closeIcon->GetLayoutProperty<CloseIconLayoutProperty>();
    layoutproperty->UpdateCloseIconWidth(PANEL_CLOSE_ICON_WIDTH);
    layoutproperty->UpdateCloseIconHeight(PANEL_CLOSE_ICON_Height);
    layoutproperty->UpdateCloseIconRadius(PANEL_CLOSE_ICON_RADIUS);
    closeIcon->MarkModifyDone();

    /**
     * @tc.steps: step3. get closeIconNode, buttonNode, imageNode.
     * @tc.expected: node is not nullptr.
     */
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    auto closeIconNode = slidingPanelPattern->GetCloseIconNode();
    auto pattern = closeIconNode->GetPattern<CloseIconPattern>();
    ASSERT_NE(pattern, nullptr);
    auto buttonNode = AceType::DynamicCast<FrameNode>(closeIconNode->GetChildren().front());
    ASSERT_NE(buttonNode, nullptr);
    auto imageNode = AceType::DynamicCast<FrameNode>(buttonNode->GetChildren().front());
    ASSERT_NE(imageNode, nullptr);
}

/**
 * @tc.name: CloseIconPatternTest003
 * @tc.desc: Test closeIcon click Callback.
 * @tc.type: FUNC
 */
HWTEST_F(CloseIconPatternTestNg, CloseIconPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. add closeIcon to slidingPanel.
     */
    auto closeIcon = FrameNode::GetOrCreateFrameNode(V2::PANEL_CLOSE_ICON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<CloseIconPattern>(); });
    closeIcon->MountToParent(frameNode, 1);
    auto layoutproperty = closeIcon->GetLayoutProperty<CloseIconLayoutProperty>();
    layoutproperty->UpdateCloseIconWidth(PANEL_CLOSE_ICON_WIDTH);
    layoutproperty->UpdateCloseIconHeight(PANEL_CLOSE_ICON_Height);
    layoutproperty->UpdateCloseIconRadius(PANEL_CLOSE_ICON_RADIUS);
    closeIcon->MarkModifyDone();

    /**
     * @tc.steps: step3. get closeIconNode, closeIconPattern, set lick button callback.
     * @tc.expected: set click button callback correct.
     */
    auto slidingPanelPattern = frameNode->GetPattern<SlidingPanelPattern>();
    ASSERT_NE(slidingPanelPattern, nullptr);
    auto closeIconNode = slidingPanelPattern->GetCloseIconNode();
    auto closeIconPattern = closeIconNode->GetPattern<CloseIconPattern>();
    closeIconPattern->SetClickButtonCallback([]() {});
    bool hasClickButtonCallback = closeIconPattern->HasClickButtonCallback();
    EXPECT_TRUE(hasClickButtonCallback);
}

/**
 * @tc.name: CloseIconPatternTest004
 * @tc.desc: Test closeIcon layout.
 * @tc.type: FUNC
 */
HWTEST_F(CloseIconPatternTestNg, CloseIconPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create slidingPanel.
     */
    SlidingPanelModelNG slidingPanelModelNG;
    slidingPanelModelNG.Create(SLIDING_PANEL_SHOW);
    slidingPanelModelNG.SetIsShow(SLIDING_PANEL_SHOW);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. add closeIcon to slidingPanel.
     */
    auto closeIconNode = FrameNode::GetOrCreateFrameNode(V2::PANEL_CLOSE_ICON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<CloseIconPattern>(); });
    closeIconNode->MountToParent(frameNode, 1);
    auto layoutproperty = closeIconNode->GetLayoutProperty<CloseIconLayoutProperty>();
    layoutproperty->UpdateCloseIconWidth(PANEL_CLOSE_ICON_WIDTH);
    layoutproperty->UpdateCloseIconHeight(PANEL_CLOSE_ICON_Height);
    layoutproperty->UpdateCloseIconRadius(PANEL_CLOSE_ICON_RADIUS);
    closeIconNode->MarkModifyDone();
    /**
     * @tc.steps: step4. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step4. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    auto closeIconPattern = closeIconNode->GetPattern<CloseIconPattern>();
    EXPECT_FALSE(closeIconPattern == nullptr);
    auto layoutProPerty = closeIconPattern->GetLayoutProperty<CloseIconLayoutProperty>();
    EXPECT_FALSE(layoutProPerty == nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<CloseIconLayoutAlgorithm>(closeIconPattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(layoutAlgorithm == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(closeIconNode, geometryNode, closeIconNode->GetLayoutProperty());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    /**
     * @tc.steps: step5. update layoutWrapper.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;

    PaddingProperty noPadding = CreatePadding(ZERO, ZERO, ZERO, ZERO);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    /**
     * @tc.steps: step6. get frame offset.
     * @tc.expected: step6. check frameOffset is correct.
     */
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), ORIGIN_POINT);
}

/**
 * @tc.name: CloseIconPropertyTest001
 * @tc.desc: set property value into CloseIconProperty and get it.
 * @tc.type: FUNC
 */
HWTEST_F(CloseIconPatternTestNg, CloseIconPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat closeIcon.
     */
    auto closeIconNode = FrameNode::GetOrCreateFrameNode(V2::PANEL_CLOSE_ICON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<CloseIconPattern>(); });

    /**
     * @tc.steps: step2. get layoutproperty and set property value.
     */
    auto layoutproperty = closeIconNode->GetLayoutProperty<CloseIconLayoutProperty>();
    layoutproperty->UpdateCloseIconWidth(PANEL_CLOSE_ICON_WIDTH);
    layoutproperty->UpdateCloseIconHeight(PANEL_CLOSE_ICON_Height);
    layoutproperty->UpdateCloseIconRadius(PANEL_CLOSE_ICON_RADIUS);
    layoutproperty->UpdateCloseIconMarginTop(PANEL_CLOSE_ICON_MARGIN_TOP);
    layoutproperty->UpdateCloseIconMarginRight(PANEL_CLOSE_ICON_MARGIN_RIGHT);
    closeIconNode->MarkModifyDone();

    /**
     * @tc.steps: step3. get property value.
     * @tc.expected: step3. check property value is correct.
     */
    auto closeIconWidth = layoutproperty->GetCloseIconWidthValue();
    EXPECT_EQ(closeIconWidth, PANEL_CLOSE_ICON_WIDTH);
    auto closeIconHeigh = layoutproperty->GetCloseIconHeightValue();
    EXPECT_EQ(closeIconHeigh, PANEL_CLOSE_ICON_Height);
    auto closeIconRadius = layoutproperty->GetCloseIconRadiusValue();
    EXPECT_EQ(closeIconRadius, PANEL_CLOSE_ICON_RADIUS);
    auto closeIconMarginTop = layoutproperty->GetCloseIconMarginTopValue();
    EXPECT_EQ(closeIconMarginTop, PANEL_CLOSE_ICON_MARGIN_TOP);
    auto closeIconMarginRight = layoutproperty->GetCloseIconMarginRightValue();
    EXPECT_EQ(closeIconMarginRight, PANEL_CLOSE_ICON_MARGIN_RIGHT);
}
} // namespace OHOS::Ace::NG