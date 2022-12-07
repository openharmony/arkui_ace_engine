/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <optional>
#include <string>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/bubble/bubble_layout_algorithm.h"
#include "core/components_ng/pattern/bubble/bubble_layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/bubble/bubble_render_property.h"
#include "core/components_ng/pattern/bubble/bubble_view.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr bool BUBBLE_PROPERTY_SHOW = true;
const std::string BUBBLE_MESSAGE = "Hello World";
const std::string BUBBLE_NEW_MESSAGE = "Good";
constexpr bool BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW = true;
constexpr bool BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_TRUE = true;
constexpr bool BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE = false;
constexpr bool BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE = true;
constexpr bool BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_FALSE = false;
constexpr float ZERO = 0.0f;
constexpr float NOPADDING = 0.0f;
constexpr float BUBBLE_WIDTH = 100.0f;
constexpr float BUBBLE_HEIGHT = 50.0f;
constexpr float TARGET_WIDTH = 100.0f;
constexpr float TARGET_HEIGHT = 200.0f;
const OffsetF ORIGIN_POINT(ZERO, ZERO);
const SizeF TARGET_SIZE(TARGET_WIDTH, TARGET_HEIGHT);
constexpr float TARGET_X = 100.0f;
constexpr float TARGET_Y = 150.0f;
const OffsetF TARGET_OFFSET(TARGET_X, TARGET_Y);
constexpr float CONTAINER_WIDTH = 600.0f;
constexpr float CONTAINER_HEIGHT = 1000.0f;
const SizeF CONTAINER_SIZE(CONTAINER_WIDTH, CONTAINER_HEIGHT);
constexpr Placement BUBBLE_LAYOUT_PROPERTY_PLACEMENT = Placement::LEFT;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const OffsetF OFFSET_TOP_LEFT = OffsetF(ZERO, ZERO);

const std::vector<Placement> BUBBLE_LAYOUT_PROPERTY_PLACEMENTS = {
    Placement::LEFT,
    Placement::RIGHT,
    Placement::TOP,
    Placement::BOTTOM,
    Placement::TOP_LEFT,
    Placement::TOP_RIGHT,
    Placement::BOTTOM_LEFT,
    Placement::BOTTOM_RIGHT,
    Placement::LEFT_BOTTOM,
    Placement::LEFT_TOP,
    Placement::RIGHT_BOTTOM,
    Placement::RIGHT_TOP,
};
} // namespace

class BubbleLayoutTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
    void SetUp() override;
    void TearDown() override;

protected:
    static RefPtr<FrameNode> GetTargetNode();
};

void BubbleLayoutTestNg::SetUp() {}
void BubbleLayoutTestNg::TearDown() {}

PaddingProperty GetPadding(float left, float top, float right, float bottom)
{
    PaddingProperty padding;
    padding.left = CalcLength(left);
    padding.right = CalcLength(right);
    padding.top = CalcLength(top);
    padding.bottom = CalcLength(bottom);
    return padding;
}

RefPtr<FrameNode> BubbleLayoutTestNg::GetTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

/**
 * @tc.name: BubbleLayoutTest001
 * @tc.desc: Test BubbleNode layout
 * @tc.type: FUNC
 */
HWTEST_F(BubbleLayoutTestNg, BubbleLayoutTest001, TestSize.Level1)
{
    // create targetNode and popupNode
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    auto targetNode = GetTargetNode();
    EXPECT_NE(targetNode, nullptr);
    auto targetTag = targetNode->GetTag();
    auto targetId = targetNode->GetId();
    auto popupNode = BubbleView::CreateBubbleNode(targetTag, targetId, popupParam);
    EXPECT_NE(popupNode, nullptr);

    // create layoutWrapper and update it
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapper> layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
        popupNode, geometryNode, AceType::DynamicCast<BubbleLayoutProperty>(popupNode->GetLayoutProperty()));
    auto layoutProperty = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    // update layoutProperty
    layoutProperty->UpdateEnableArrow(true);
    layoutProperty->UpdateUseCustom(false);
    layoutProperty->UpdatePlacement(Placement::BOTTOM);
    layoutProperty->UpdateShowInSubWindow(false);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(BUBBLE_WIDTH), CalcLength(BUBBLE_HEIGHT)));
    auto popupLayoutAlgorithm = popupNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_NE(popupLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(popupLayoutAlgorithm));

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    parentLayoutConstraint.percentReference = CONTAINER_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(CONTAINER_WIDTH, CONTAINER_HEIGHT));

    PaddingProperty noPadding;
    noPadding.left = CalcLength(NOPADDING);
    noPadding.right = CalcLength(NOPADDING);
    noPadding.top = CalcLength(NOPADDING);
    noPadding.bottom = CalcLength(NOPADDING);
    layoutWrapper->GetLayoutProperty()->UpdatePadding(noPadding);
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);
}

/**
 * @tc.name: BubbleLayoutTest002
 * @tc.desc: Test Bubble Layout
 * @tc.type: FUNC
 */
HWTEST_F(BubbleLayoutTestNg, BubbleLayoutTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetUseCustomComponent(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);
    auto targetNode = GetTargetNode();
    EXPECT_NE(targetNode, nullptr);
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = FrameNode::CreateFrameNode(
        V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetNode->GetId(), targetNode->GetTag()));
    EXPECT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    EXPECT_FALSE(bubblePattern == nullptr);
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_FALSE(bubbleLayoutProperty == nullptr);
    auto bubbleLayoutAlgorithm = bubblePattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(bubbleLayoutAlgorithm == nullptr);

    /**
     * @tc.steps: step3. update layoutWrapper and layoutProperty.
     */
    bubbleLayoutProperty->UpdateEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE);
    bubbleLayoutProperty->UpdateUseCustom(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);
    bubbleLayoutProperty->UpdatePlacement(BUBBLE_LAYOUT_PROPERTY_PLACEMENT);
    bubbleLayoutProperty->UpdateUseCustom(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    /**
     * @tc.steps: step3. use layoutAlgorithm to measure and layout.
     * @tc.expected: step3. check whether the value of geometry's frameSize and frameOffset is correct.
     */
    bubbleLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    bubbleLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameSize(), FULL_SCREEN_SIZE);
    EXPECT_EQ(layoutWrapper->GetGeometryNode()->GetFrameOffset(), ORIGIN_POINT);
}

/**
 * @tc.name: BubbleLayoutTest003
 * @tc.desc: Test the Bubble created by message Measure and Layout
 * @tc.type: FUNC
 */
HWTEST_F(BubbleLayoutTestNg, BubbleLayoutTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetUseCustomComponent(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);
    auto targetNode = GetTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    EXPECT_FALSE(frameNode == nullptr);

    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    EXPECT_FALSE(bubblePattern == nullptr);
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_FALSE(bubbleLayoutProperty == nullptr);
    auto bubbleLayoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(bubbleLayoutAlgorithm == nullptr);
    bubbleLayoutAlgorithm->targetTag_ = targetTag;
    bubbleLayoutAlgorithm->targetNodeId_ = targetId;

    /**
     * @tc.steps: step3. update layoutWrapper and layoutProperty.
     */
    bubbleLayoutProperty->UpdateEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE);
    bubbleLayoutProperty->UpdateUseCustom(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_FALSE);
    bubbleLayoutProperty->UpdatePlacement(BUBBLE_LAYOUT_PROPERTY_PLACEMENT);
    bubbleLayoutProperty->UpdateUseCustom(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM_TRUE);
    bubbleLayoutProperty->UpdateShowInSubWindow(BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = CONTAINER_SIZE;
    childLayoutConstraint.minSize = SizeF(ZERO, ZERO);

    /**
     * @tc.steps: step4. create bubble child and child's layoutWrapper.
     */
    auto textFrameNode = BubbleView::CreateMessage(popupParam->GetMessage(), popupParam->IsUseCustom());
    EXPECT_FALSE(textFrameNode == nullptr);
    RefPtr<GeometryNode> textGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    textGeometryNode->Reset();
    RefPtr<LayoutWrapper> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
    textLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    textLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(BUBBLE_WIDTH), CalcLength(BUBBLE_HEIGHT)));
    auto boxLayoutAlgorithm = textFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_FALSE(boxLayoutAlgorithm == nullptr);
    textLayoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    frameNode->AddChild(textFrameNode);
    layoutWrapper->AppendChild(textLayoutWrapper);

    /**
     * @tc.steps: step5. use layoutAlgorithm to measure and layout.
     * @tc.expected: step5. check whether the value of the bubble child's frameSize and frameOffset is correct.
     */
    bubbleLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    bubbleLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(textLayoutWrapper->GetGeometryNode()->GetFrameSize(), SizeF(0, 0));
    EXPECT_EQ(textLayoutWrapper->GetGeometryNode()->GetFrameOffset(), OFFSET_TOP_LEFT);
}

/**
 * @tc.name: BubbleLayoutTest004
 * @tc.desc: Test  Bubble UpdateTouchRegion in different arrowPlacement
 * @tc.type: FUNC
 */
HWTEST_F(BubbleLayoutTestNg, BubbleLayoutTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto targetNode = GetTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    /**
     * @tc.steps: step2. get pattern and layoutAlgorithm.
     * @tc.expected: step2. related function is called.
     */
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    EXPECT_FALSE(bubblePattern == nullptr);
    auto bubbleLayoutProperty = bubblePattern->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_FALSE(bubbleLayoutProperty == nullptr);
    auto bubbleLayoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    EXPECT_FALSE(bubbleLayoutAlgorithm == nullptr);

    /**
     * @tc.steps: step3. update layoutProp and arrowPlacement.
     * @tc.expected: step3. check whether the function is executed.
     */
    for (int32_t i = 0; i < BUBBLE_LAYOUT_PROPERTY_PLACEMENTS.size(); ++i) {
        if (i % 2 == 0) {
            bubbleLayoutProperty->UpdateEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_TRUE);
        } else {
            bubbleLayoutProperty->UpdateEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW_FALSE);
        }
        bubbleLayoutAlgorithm->arrowPlacement_ = BUBBLE_LAYOUT_PROPERTY_PLACEMENTS[i];
        bubbleLayoutAlgorithm->UpdateTouchRegion();
        bubbleLayoutAlgorithm->UpdateCustomChildPosition(bubbleLayoutProperty);
    }
}
} // namespace OHOS::Ace::NG