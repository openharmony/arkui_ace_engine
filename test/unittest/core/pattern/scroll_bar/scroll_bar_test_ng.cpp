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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_layout_algorithm.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_model_ng.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float DEVICE_WIDTH = 720.0f;
constexpr float DEVICE_HEIGHT = 1136.0f;
constexpr float SCROLL_BAR_FLOAT_10 = 10.0f;
constexpr float SCROLL_BAR_FLOAT_100 = 100.0f;
constexpr float SCROLL_BAR_FLOAT_NEGATIVE_100 = -100.0f;
constexpr double SCROLL_BAR_CHILD_WIDTH = 30.0;
constexpr double SCROLL_BAR_CHILD_HEIGHT = 100.0;
const SizeF CONTAINER_SIZE(DEVICE_WIDTH, DEVICE_HEIGHT);
const SizeF SCROLL_BAR_CHILD_SIZE(SCROLL_BAR_CHILD_WIDTH, SCROLL_BAR_CHILD_HEIGHT);
const SizeF SCROLL_BAR_SELF_SIZE(30.0f, DEVICE_HEIGHT);
} // namespace

class ScrollBarTestNg : public testing::Test {
protected:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void GetInstance();

    void CreateScrollBarWithoutChild(bool infoFlag, bool proxyFlag, int directionValue, int stateValue);
    void CreateScrollBar(
        bool infoFlag, bool proxyFlag, int directionValue, int stateValue, const LayoutConstraintF& layoutConstraint);

    RefPtr<FrameNode> frameNode_;
    RefPtr<ScrollBarPattern> pattern_;
    RefPtr<ScrollBarLayoutProperty> layoutProperty_;
    RefPtr<ScrollBarAccessibilityProperty> accessibilityProperty_;
    RefPtr<LayoutAlgorithm> layoutAlgorithm_;
    RefPtr<LayoutWrapperNode> layoutWrapper_;
};

void ScrollBarTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void ScrollBarTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void ScrollBarTestNg::SetUp() {}

void ScrollBarTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    layoutAlgorithm_ = nullptr;
    layoutWrapper_ = nullptr;
}

void ScrollBarTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<ScrollBarPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<ScrollBarLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<ScrollBarAccessibilityProperty>();
    layoutAlgorithm_ = pattern_->CreateLayoutAlgorithm();
}

void ScrollBarTestNg::CreateScrollBarWithoutChild(bool infoFlag, bool proxyFlag, int directionValue, int stateValue)
{
    ScrollBarModelNG model;
    RefPtr<ScrollProxy> scrollProxy;
    auto proxy = model.GetScrollBarProxy(scrollProxy);
    model.Create(proxy, infoFlag, proxyFlag, directionValue, stateValue);
    GetInstance();
}

void ScrollBarTestNg::CreateScrollBar(
    bool infoFlag, bool proxyFlag, int directionValue, int stateValue, const LayoutConstraintF& layoutConstraint)
{
    ScrollBarModelNG model;
    RefPtr<ScrollProxy> scrollProxy;
    auto proxy = model.GetScrollBarProxy(scrollProxy);
    model.Create(proxy, infoFlag, proxyFlag, directionValue, stateValue);
    GetInstance();

    layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty_->UpdateContentConstraint();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    layoutWrapper_ = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode_, geometryNode, layoutProperty_);
    layoutWrapper_->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm_));

    auto childFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childFrameNode, childGeometryNode, childLayoutProperty);
    childLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SCROLL_BAR_CHILD_WIDTH), CalcLength(SCROLL_BAR_CHILD_HEIGHT)));
    auto childLayoutAlgorithm = childFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    childLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(childLayoutAlgorithm));
    layoutWrapper_->AppendChild(childLayoutWrapper);

    layoutAlgorithm_->Measure(AceType::RawPtr(layoutWrapper_));
    layoutAlgorithm_->Layout(AceType::RawPtr(layoutWrapper_));
}

/**
 * @tc.name: ScrollBarTest001
 * @tc.desc: When setting a fixed length and width, and axis is VERTICAL, verify the Measure and Layout functions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar and initialize related properties.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(SCROLL_BAR_SELF_SIZE);
    CreateScrollBar(
        true, false, static_cast<int>(Axis::VERTICAL), static_cast<int>(DisplayMode::OFF), layoutConstraint);

    auto childLayout = layoutWrapper_->GetOrCreateChildByIndex(0);
    EXPECT_NE(childLayout, nullptr);
    auto scrollBarSize = layoutWrapper_->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(scrollBarSize, SCROLL_BAR_SELF_SIZE) << "scrollBarSize: " << scrollBarSize.ToString()
                                                   << " SCROLL_BAR_SELF_SIZE: " << SCROLL_BAR_SELF_SIZE.ToString();
    auto childSize = childLayout->GetGeometryNode()->GetFrameSize();
    auto expectChildSize = SizeF(SCROLL_BAR_CHILD_WIDTH, SCROLL_BAR_CHILD_HEIGHT);
    EXPECT_EQ(childSize, expectChildSize)
        << "childSize: " << childSize.ToString() << " expectChildSize: " << expectChildSize.ToString();

    /**
     * @tc.steps: step2. Verify the OnDirtyLayoutWrapperSwap function of scrollBar.
     * @tc.expected: step2. Compare return value with expected value.
     */
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    auto ret = pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper_, config);
    EXPECT_EQ(ret, false);
    config.skipMeasure = true;
    config.skipLayout = true;
    ret = pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper_, config);
    EXPECT_EQ(ret, false);
    config.skipMeasure = false;
    config.skipLayout = false;
    ret = pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper_, config);
    EXPECT_EQ(ret, false);
    auto expectDistance = SCROLL_BAR_SELF_SIZE.Height() - SCROLL_BAR_CHILD_HEIGHT; // 1036
    EXPECT_EQ(pattern_->scrollableDistance_, expectDistance);
}

/**
 * @tc.name: ScrollBarTest002
 * @tc.desc: When the fixed length and width are not set, and axis is HORIZONTAL, verify the Measure and Layout, and
 * related functions in the scrollbar pattern. functions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar and initialize related properties.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    CreateScrollBar(
        true, false, static_cast<int>(Axis::HORIZONTAL), static_cast<int>(DisplayMode::AUTO), layoutConstraint);

    /**
     * @tc.steps: step2. After the layout is completed, check the framesize of the scrollBar and child nodes.
     * @tc.expected: step2. Compare whether the return value is expected to be the same.
     */
    auto childLayout = layoutWrapper_->GetOrCreateChildByIndex(0);
    EXPECT_NE(childLayout, nullptr);
    auto scrollBarSize = layoutWrapper_->GetGeometryNode()->GetFrameSize();
    // has no idealSize, scrollBarSize.height is child.height
    EXPECT_EQ(scrollBarSize, SizeF(DEVICE_WIDTH, SCROLL_BAR_CHILD_HEIGHT))
        << "scrollBarSize: " << scrollBarSize.ToString()
        << " SizeF(DEVICE_WIDTH, SCROLL_BAR_CHILD_HEIGHT): " << SizeF(DEVICE_WIDTH, SCROLL_BAR_CHILD_HEIGHT).ToString();
    auto childSize = childLayout->GetGeometryNode()->GetFrameSize();
    auto expectChildSize = SizeF(SCROLL_BAR_CHILD_WIDTH, SCROLL_BAR_CHILD_HEIGHT);
    EXPECT_EQ(childSize, expectChildSize)
        << "childSize: " << childSize.ToString() << " expectChildSize: " << expectChildSize.ToString();

    /**
     * @tc.steps: step3. Verify the callback function in scrollBar under different conditions.
     * @tc.expected: step3. Compare return value with expected value.
     */
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->axis_, Axis::HORIZONTAL);
    auto callback = pattern_->scrollPositionCallback_;
    EXPECT_NE(callback, nullptr);
    auto ret = callback(0.0, SCROLL_FROM_START);
    EXPECT_EQ(ret, true);
    ret = callback(0.0, SCROLL_FROM_BAR);
    EXPECT_EQ(ret, false);
    ret = callback(1.0, SCROLL_FROM_UPDATE);
    EXPECT_EQ(ret, false);
    ret = callback(-1.0, SCROLL_FROM_ANIMATION);
    EXPECT_EQ(ret, false);

    pattern_->scrollableDistance_ = SCROLL_BAR_FLOAT_100;
    ret = callback(1.0, SCROLL_FROM_BAR);
    EXPECT_EQ(ret, true);
    EXPECT_EQ(pattern_->lastOffset_, 0.0f);
    EXPECT_EQ(pattern_->currentOffset_, 1.0f);
    pattern_->axis_ = Axis::NONE;
    ret = callback(1.0, SCROLL_FROM_BAR);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: ScrollBarTest003
 * @tc.desc: When setting a fixed length and width, and axis is HORIZONTAL, verify the Measure and Layout functions, and
 * related functions in the scrollbar pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar and initialize related properties.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutConstraint.selfIdealSize.SetSize(SCROLL_BAR_SELF_SIZE);
    CreateScrollBar(
        true, false, static_cast<int>(Axis::HORIZONTAL), static_cast<int>(DisplayMode::ON), layoutConstraint);

    /**
     * @tc.steps: step2. After the layout is completed, check the framesize of the scrollBar and child nodes.
     * @tc.expected: step2. Compare whether the return value is expected to be the same.
     */
    auto childLayout = layoutWrapper_->GetOrCreateChildByIndex(0);
    EXPECT_NE(childLayout, nullptr);
    auto scrollBarSize = layoutWrapper_->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(scrollBarSize, SCROLL_BAR_SELF_SIZE) << "scrollBarSize: " << scrollBarSize.ToString()
                                                   << " SCROLL_BAR_SELF_SIZE: " << SCROLL_BAR_SELF_SIZE.ToString();
    auto childSize = childLayout->GetGeometryNode()->GetFrameSize();
    auto expectChildSize = SizeF(SCROLL_BAR_CHILD_WIDTH, SCROLL_BAR_CHILD_HEIGHT);
    EXPECT_EQ(childSize, expectChildSize)
        << "childSize: " << childSize.ToString() << " expectChildSize: " << expectChildSize.ToString();

    /**
     * @tc.steps: step3. Verify the callback function in scrollBar under different conditions.
     * @tc.expected: step3. Compare return value with expected value.
     */
    auto scrollBarProxy = AceType::MakeRefPtr<ScrollBarProxy>();
    EXPECT_NE(scrollBarProxy, nullptr);
    pattern_->SetScrollBarProxy(scrollBarProxy);
    EXPECT_NE(pattern_->scrollBarProxy_, nullptr);
    auto callback = pattern_->scrollPositionCallback_;
    EXPECT_NE(callback, nullptr);
    pattern_->scrollableDistance_ = SCROLL_BAR_FLOAT_100;
    auto ret = callback(1.0, SCROLL_FROM_BAR);
    EXPECT_EQ(ret, true);
    pattern_->currentOffset_ = SCROLL_BAR_FLOAT_10;
    ret = callback(1.0, SCROLL_FROM_BAR);
    EXPECT_EQ(ret, true);
    pattern_->currentOffset_ = -1.0f;
    pattern_->scrollableDistance_ = 0.0f;
    ret = callback(1.0, SCROLL_FROM_BAR);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: ScrollBarTest004
 * @tc.desc: When the fixed length and width are not set, and axis is VERTICAL, verify the Measure and Layout functions,
 * and related functions in the scrollbar proxy.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar and initialize related properties.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    CreateScrollBar(true, false, static_cast<int>(Axis::VERTICAL), -1, layoutConstraint);

    /**
     * @tc.steps: step2. After the layout is completed, check the framesize of the scrollBar and child nodes.
     * @tc.expected: step2. Compare whether the return value is expected to be the same.
     */
    auto childLayout = layoutWrapper_->GetOrCreateChildByIndex(0);
    EXPECT_NE(childLayout, nullptr);
    auto scrollBarSize = layoutWrapper_->GetGeometryNode()->GetFrameSize();
    auto expectScrollBarSize = SizeF(SCROLL_BAR_CHILD_WIDTH, DEVICE_HEIGHT);
    // has no idealSize, scrollBarSize.width is child.width
    EXPECT_EQ(scrollBarSize, expectScrollBarSize)
        << "scrollBarSize: " << scrollBarSize.ToString() << " expectScrollBarSize: " << expectScrollBarSize.ToString();
    auto childSize = childLayout->GetGeometryNode()->GetFrameSize();
    auto expectChildSize = SizeF(SCROLL_BAR_CHILD_WIDTH, SCROLL_BAR_CHILD_HEIGHT);
    EXPECT_EQ(childSize, expectChildSize)
        << "childSize: " << childSize.ToString() << " expectChildSize: " << expectChildSize.ToString();

    /**
     * @tc.steps: step3. Create scrollbar proxy and verify the RegisterScrollableNode function and NotifyScrollableNode
     * function.
     * @tc.expected: step3. Check whether relevant parameters are correct.
     */
    RefPtr<ScrollProxy> ScrollProxy = AceType::MakeRefPtr<ScrollBarProxy>();
    EXPECT_NE(ScrollProxy, nullptr);
    auto distance = -1.0;
    auto source = SCROLL_FROM_START;
    auto scrollFunction = [&distance, &source](double parameter1, int32_t parameter2) {
        distance = parameter1;
        source = parameter2;
        return true;
    };
    auto scrollBarProxy = AceType::DynamicCast<ScrollBarProxy>(ScrollProxy);
    EXPECT_NE(scrollBarProxy, nullptr);
    auto scrollPattern1 = AceType::MakeRefPtr<ScrollPattern>();
    EXPECT_NE(scrollPattern1, nullptr);
    auto* scrollRaw1 = AceType::RawPtr(scrollPattern1);
    EXPECT_NE(scrollRaw1, nullptr);
    scrollBarProxy->RegisterScrollableNode({ AceType::WeakClaim(scrollRaw1), std::move(scrollFunction) });
    EXPECT_EQ(scrollBarProxy->scrollableNodes_.size(), 1);
    auto* scrollBarPatternRaw = AceType::RawPtr(pattern_);
    EXPECT_NE(scrollBarPatternRaw, nullptr);
    scrollBarProxy->NotifyScrollableNode(1.0, AceType::WeakClaim(scrollBarPatternRaw));
    EXPECT_EQ(distance, 0.0);
    EXPECT_EQ(source, SCROLL_FROM_BAR);

    /**
     * @tc.steps: step4. When calling RegisterScrollableNode multiple times, verify the relevant parameters.
     * @tc.expected: step4. Check whether relevant parameters are correct.
     */
    auto scrollPattern2 = AceType::MakeRefPtr<ScrollPattern>();
    EXPECT_NE(scrollPattern2, nullptr);
    auto* scrollRaw2 = AceType::RawPtr(scrollPattern2);
    EXPECT_NE(scrollRaw2, nullptr);
    scrollBarProxy->RegisterScrollableNode({ AceType::WeakClaim(scrollRaw1), std::move(scrollFunction) });
    EXPECT_EQ(scrollBarProxy->scrollableNodes_.size(), 1);
    scrollBarProxy->RegisterScrollableNode({ AceType::WeakClaim(scrollRaw2), nullptr });
    EXPECT_EQ(scrollBarProxy->scrollableNodes_.size(), 2);
    scrollBarProxy->RegisterScrollableNode({ nullptr, std::move(scrollFunction) });
    EXPECT_EQ(scrollBarProxy->scrollableNodes_.size(), 3);
    scrollPattern1->estimatedHeight_ = SCROLL_BAR_FLOAT_100;
    pattern_->scrollableDistance_ = SCROLL_BAR_FLOAT_100;
    scrollBarProxy->NotifyScrollableNode(1.0, AceType::WeakClaim(scrollBarPatternRaw));
    EXPECT_EQ(distance, 1.0);
    EXPECT_EQ(source, SCROLL_FROM_BAR);

    /**
     * @tc.steps: step5. Repeatedly call UnRegisterScrollableNode to delete the relevant ScrollableNode.
     * @tc.expected: step5. Check the size of the list container.
     */
    scrollBarProxy->UnRegisterScrollableNode(AceType::WeakClaim(scrollRaw2));
    EXPECT_EQ(scrollBarProxy->scrollableNodes_.size(), 2);
    scrollBarProxy->UnRegisterScrollableNode(AceType::WeakClaim(scrollRaw2));
    EXPECT_EQ(scrollBarProxy->scrollableNodes_.size(), 2);
}

/**
 * @tc.name: ScrollBarTest005
 * @tc.desc: When the fixed length and width are not set, and axis is VERTICAL, verify the Measure and Layout functions,
 * and related functions in the scrollbar proxy.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar and initialize related properties.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    CreateScrollBar(true, false, 3, 3, layoutConstraint);

    /**
     * @tc.steps: step2. Create scrollbar proxy and verify the RegisterScrollBar function and RegisterScrollBar
     * function.
     * @tc.expected: step2. Check whether relevant parameters are correct.
     */
    RefPtr<ScrollProxy> ScrollProxy = AceType::MakeRefPtr<ScrollBarProxy>();
    ASSERT_NE(ScrollProxy, nullptr);
    auto scrollBarProxy = AceType::DynamicCast<ScrollBarProxy>(ScrollProxy);
    ASSERT_NE(scrollBarProxy, nullptr);
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto* scrollRaw = AceType::RawPtr(scrollPattern);
    ASSERT_NE(scrollRaw, nullptr);
    auto* scrollBarPatternRaw1 = AceType::RawPtr(pattern_);
    ASSERT_NE(scrollBarPatternRaw1, nullptr);
    scrollBarProxy->RegisterScrollBar(AceType::WeakClaim(scrollBarPatternRaw1));
    EXPECT_EQ(scrollBarProxy->scrollBars_.size(), 1);
    scrollBarProxy->NotifyScrollBar(AceType::WeakClaim(scrollRaw));
    EXPECT_EQ(pattern_->currentOffset_, 0.0f);

    /**
     * @tc.steps: step3. When calling RegisterScrollBar multiple times, verify the relevant parameters.
     * @tc.expected: step3. Check whether relevant parameters are correct.
     */
    auto scrollBarPattern = AceType::MakeRefPtr<ScrollBarPattern>();
    ASSERT_NE(scrollBarPattern, nullptr);
    auto* scrollBarPatternRaw2 = AceType::RawPtr(scrollBarPattern);
    ASSERT_NE(scrollBarPatternRaw2, nullptr);
    scrollBarProxy->RegisterScrollBar(AceType::WeakClaim(scrollBarPatternRaw1));
    EXPECT_EQ(scrollBarProxy->scrollBars_.size(), 1);
    scrollBarProxy->RegisterScrollBar(AceType::WeakClaim(scrollBarPatternRaw2));
    EXPECT_EQ(scrollBarProxy->scrollBars_.size(), 2);
    scrollBarProxy->RegisterScrollBar(nullptr);
    EXPECT_EQ(scrollBarProxy->scrollBars_.size(), 3);
    scrollBarProxy->StartScrollBarAnimator();
    pattern_->displayMode_ = DisplayMode::AUTO;
    scrollBarProxy->StartScrollBarAnimator();
    scrollBarProxy->StopScrollBarAnimator();
    scrollPattern->estimatedHeight_ = SCROLL_BAR_FLOAT_100;
    scrollPattern->barOffset_ = SCROLL_BAR_FLOAT_NEGATIVE_100;
    pattern_->scrollableDistance_ = 1.0f;
    EXPECT_EQ(pattern_->currentOffset_, 0.0f);

    /**
     * @tc.steps: step4. Repeatedly call UnRegisterScrollBar to delete the relevant scrollableBar.
     * @tc.expected: step4. Check the size of the list container.
     */
    scrollBarProxy->UnRegisterScrollBar(AceType::WeakClaim(scrollBarPatternRaw2));
    EXPECT_EQ(scrollBarProxy->scrollBars_.size(), 2);
    scrollBarProxy->UnRegisterScrollBar(AceType::WeakClaim(scrollBarPatternRaw2));
    EXPECT_EQ(scrollBarProxy->scrollBars_.size(), 2);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: ScrollBar Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar and initialize related properties.
     */
    CreateScrollBarWithoutChild(true, false, 3, 3);

    /**
     * @tc.steps: step2. Get scrollBar frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    pattern_->axis_ = Axis::NONE;
    pattern_->scrollableDistance_ = 0.0;
    pattern_->SetAccessibilityAction();

    /**
     * @tc.steps: step3. When scrollBar Axis is NONE and scrollable distance is 0, call the callback function in
     *                   scrollBarAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollForward());
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollBackward());

    /**
     * @tc.steps: step4. When scrollBar Axis is NONE and scrollable distance is not 0, call the callback function in
     *                   scrollBarAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    pattern_->scrollableDistance_ = SCROLL_BAR_FLOAT_100;
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollForward());
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When scrollBar Axis is VERTICAL and scrollable distance is not 0, call the callback function in
     *                   scrollBarAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    pattern_->axis_ = Axis::VERTICAL;
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollForward());
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollBackward());

    /**
     * @tc.steps: step6. When scrollBar Axis is VERTICAL and scrollable distance is 0, call the callback function in
     *                   scrollBarAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    pattern_->scrollableDistance_ = 0.0;
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollForward());
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollBackward());
}

/**
 * @tc.name: AccessibilityEventTest001
 * @tc.desc: Test the ScrollEndCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, AccessibilityEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar and initialize related properties.
     */
    CreateScrollBarWithoutChild(true, false, static_cast<int>(Axis::VERTICAL), static_cast<int>(DisplayMode::OFF));

    /**
     * @tc.steps: step2. set callback function.
     */
    pattern_->OnModifyDone();
    ASSERT_NE(pattern_->scrollableEvent_, nullptr);
    auto callback = pattern_->scrollEndCallback_;
    ASSERT_NE(callback, nullptr);
    MockPipelineContext::SetUp();
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    MockPipelineContext::GetCurrentContext()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();

    /**
     * @tc.steps: step3. DisplayMode::ON
     * @tc.expected: opacity_ is UINT8_MAX.
     */
    auto scrollBarProxy = AceType::MakeRefPtr<ScrollBarProxy>();
    EXPECT_NE(scrollBarProxy, nullptr);
    pattern_->SetScrollBarProxy(scrollBarProxy);
    EXPECT_NE(pattern_->scrollBarProxy_, nullptr);
    layoutProperty_->UpdateDisplayMode(DisplayMode::ON);
    pattern_->controlDistance_ = 10.f;
    pattern_->OnModifyDone();
    callback();
    EXPECT_EQ(pattern_->disappearAnimation_, nullptr);
    EXPECT_EQ(pattern_->opacity_, UINT8_MAX);

    /**
     * @tc.steps: step4. DisplayMode::AUTO and call callback function and controlDistance_ is 0.
     * @tc.expected: disappearAnimation_ is nullptr.
     */
    pattern_->displayMode_ = DisplayMode::AUTO;
    pattern_->controlDistance_ = 0.f;
    callback();
    EXPECT_EQ(pattern_->disappearAnimation_, nullptr);

    /**
     * @tc.steps: step5. call callback function and controlDistance_ bigger than 0.
     * @tc.expected: disappearAnimation_ is not nullptr.
     */
    pattern_->controlDistance_ = 10.f;
    pattern_->displayMode_ = DisplayMode::AUTO;
    callback();
    ASSERT_NE(pattern_->disappearAnimation_, nullptr);
}

/**
 * @tc.name: ScrollBarTest006
 * @tc.desc: Test OnModifyDone of ScrollBarPattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar and initialize related properties.
     */
    CreateScrollBarWithoutChild(true, true, -1, -1);

    /**
     * @tc.steps: step2. Get scrollBar accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->GetDisplayMode(), DisplayMode::AUTO);
    EXPECT_EQ(pattern_->GetAxis(), Axis::VERTICAL);

    layoutProperty_->UpdateDisplayMode(DisplayMode::OFF);
    layoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->GetDisplayMode(), DisplayMode::OFF);
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);

    layoutProperty_->UpdateDisplayMode(DisplayMode::AUTO);
    layoutProperty_->UpdateAxis(Axis::VERTICAL);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->GetDisplayMode(), DisplayMode::AUTO);
    EXPECT_EQ(pattern_->GetAxis(), Axis::VERTICAL);

    layoutProperty_->UpdateDisplayMode(DisplayMode::ON);
    layoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->GetDisplayMode(), DisplayMode::ON);
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);
}

/**
 * @tc.name: ScrollBarTest007
 * @tc.desc: Test OnDirtyLayoutWrapperSwap of ScrollBarPattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar and initialize related properties.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(SCROLL_BAR_SELF_SIZE);
    CreateScrollBar(
        true, false, static_cast<int>(Axis::VERTICAL), static_cast<int>(DisplayMode::AUTO), layoutConstraint);

    /**
     * @tc.steps: step2. Verify the OnDirtyLayoutWrapperSwap function of scrollBar.
     * @tc.expected: step4. Compare return value with expected value.
     */
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    pattern_->SetControlDistance(10.0f);
    EXPECT_EQ(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper_, config), true);

    EXPECT_EQ(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper_, config), false);

    pattern_->SetControlDistance(-10.0f);
    EXPECT_EQ(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper_, config), true);

    layoutProperty_->UpdateDisplayMode(DisplayMode::ON);
    pattern_->OnModifyDone();
    pattern_->SetControlDistance(5.0f);
    EXPECT_EQ(pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper_, config), true);
}

/**
 * @tc.name: ScrollBarTest008
 * @tc.desc: Test OnDirtyLayoutWrapperSwap of ScrollBarPattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar and initialize related properties.
     */
    CreateScrollBarWithoutChild(true, false, static_cast<int>(Axis::VERTICAL), static_cast<int>(DisplayMode::AUTO));

    /**
     * @tc.steps: step2. Verify the scrollPositionCallback_ function of scrollBar.
     * @tc.expected: step3. Init panRecognizer_.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(pattern_, nullptr);
    context->SetMinPlatformVersion(10);
    pattern_->InitPanRecognizer();
    EXPECT_NE(pattern_->panRecognizer_, nullptr);
    EXPECT_NE(pattern_->panRecognizer_->onActionStart_, nullptr);
    EXPECT_NE(pattern_->panRecognizer_->onActionEnd_, nullptr);
    EXPECT_NE(pattern_->panRecognizer_->onActionUpdate_, nullptr);
}

/**
 * @tc.name: ScrollBarTest009
 * @tc.desc: Test OnDirtyLayoutWrapperSwap of ScrollBarPattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar and initialize related properties.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(SCROLL_BAR_SELF_SIZE);
    CreateScrollBar(
        true, false, static_cast<int>(Axis::VERTICAL), static_cast<int>(DisplayMode::AUTO), layoutConstraint);

    /**
     * @tc.steps: step2. Verify the scrollPositionCallback_ function of scrollBar.
     * @tc.expected: step2. Compare return value with expected value.
     */
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper_, config);
    auto distance = pattern_->scrollableDistance_;

    EXPECT_EQ(pattern_->scrollPositionCallback_(100, SCROLL_FROM_START), true);
    EXPECT_FLOAT_EQ(pattern_->currentOffset_, 0.f);

    EXPECT_EQ(pattern_->scrollPositionCallback_(distance / 2.0, 1), true);
    EXPECT_FLOAT_EQ(pattern_->currentOffset_, distance / 2.0);

    EXPECT_EQ(pattern_->scrollPositionCallback_(distance - distance / 2.0, 1), true);
    EXPECT_FLOAT_EQ(pattern_->currentOffset_, distance);

    EXPECT_EQ(pattern_->scrollPositionCallback_(100, 1), false);
    EXPECT_FLOAT_EQ(pattern_->currentOffset_, distance);
}

/**
 * @tc.name: ScrollBarTest010
 * @tc.desc: Test SetSpecificSupportAction of ScrollBarAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar and initialize related properties.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(SCROLL_BAR_SELF_SIZE);
    CreateScrollBar(true, true, -1, -1, layoutConstraint);

    /**
     * @tc.steps: step2. Verify the IsScrollable function of ScrollBarAccessibilityProperty.
     * @tc.expected: step2. Compare the supportActions_ value with expected value.
     */
    auto supportActions = accessibilityProperty_->supportActions_;
    accessibilityProperty_->SetSpecificSupportAction();
    EXPECT_EQ(accessibilityProperty_->supportActions_, supportActions);

    layoutProperty_->UpdateAxis(Axis::NONE);
    pattern_->OnModifyDone();
    accessibilityProperty_->SetSpecificSupportAction();
    EXPECT_EQ(accessibilityProperty_->supportActions_, supportActions);

    layoutProperty_->UpdateAxis(Axis::VERTICAL);
    pattern_->OnModifyDone();
    accessibilityProperty_->SetSpecificSupportAction();
    EXPECT_EQ(accessibilityProperty_->supportActions_, supportActions);

    pattern_->SetControlDistance(10.f);
    accessibilityProperty_->SetSpecificSupportAction();
    EXPECT_EQ(accessibilityProperty_->supportActions_, supportActions);

    /**
     * @tc.steps: step3. Verify the SetSpecificSupportAction function of ScrollBarAccessibilityProperty.
     * @tc.expected: step3. Compare the supportActions_ value with expected value.
     */
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper_, config);
    auto distance = pattern_->scrollableDistance_;

    accessibilityProperty_->SetSpecificSupportAction();
    EXPECT_EQ(accessibilityProperty_->supportActions_,
        supportActions | (1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD)));

    pattern_->scrollPositionCallback_(distance / 2.0, 1);
    accessibilityProperty_->ResetSupportAction();
    EXPECT_EQ(accessibilityProperty_->supportActions_,
        supportActions | (1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD)) |
            (1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD)));

    pattern_->scrollPositionCallback_(distance, 1);
    accessibilityProperty_->ResetSupportAction();
    EXPECT_EQ(accessibilityProperty_->supportActions_,
        supportActions | (1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD)));
}

/**
 * @tc.name: ScrollBarTest011
 * @tc.desc: Test Create of ScrollBarModelNG.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar.
     */
    ScrollBarModelNG model;
    RefPtr<ScrollProxy> scrollProxy = AceType::MakeRefPtr<ScrollBarProxy>();
    auto proxy = model.GetScrollBarProxy(scrollProxy);
    model.Create(proxy, false, false, -1, -1);
    GetInstance();

    /**
     * @tc.steps: step2. Create scrollBar and initialize related properties.
     * @tc.expected: step2. Compare value with expected value.
     */
    EXPECT_EQ(pattern_->scrollBarProxy_, nullptr);
    EXPECT_EQ(pattern_->opacity_, UINT8_MAX);
    EXPECT_EQ(layoutProperty_->HasAxis(), false);
    EXPECT_EQ(layoutProperty_->HasDisplayMode(), false);
    EXPECT_EQ(layoutProperty_->HasVisibility(), false);
}

/**
 * @tc.name: ScrollBarTest012
 * @tc.desc: Test OnCollectTouchTarget of ScrollBarPattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar and initialize related properties.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(SCROLL_BAR_SELF_SIZE);
    CreateScrollBar(true, true, -1, -1, layoutConstraint);

    /**
     * @tc.steps: step2. Verify the OnCollectTouchTarget function of ScrollBarPattern.
     * @tc.expected: step2. Compare the value with expected value.
     */
    const RectF& rect = pattern_->childRect_;
    PointF localPoint = PointF(rect.Width() + rect.GetX(), rect.Height() + rect.GetY());
    const SourceType source = SourceType::TOUCH;
    OffsetF coordinateOffset;
    GetEventTargetImpl getEventTargetImpl;
    TouchTestResult result;
    const int32_t size = result.size();
    EXPECT_EQ(pattern_->scrollableEvent_->InBarRegion(localPoint, source), true);

    pattern_->scrollableEvent_->BarCollectTouchTarget(coordinateOffset, getEventTargetImpl, result);
    EXPECT_FLOAT_EQ(pattern_->panRecognizer_->GetCoordinateOffset().GetX(), coordinateOffset.GetX());
    EXPECT_FLOAT_EQ(pattern_->panRecognizer_->GetCoordinateOffset().GetY(), coordinateOffset.GetY());
    EXPECT_EQ(result.size(), size + 1);

    localPoint.SetX(localPoint.GetX() + 1);
    localPoint.SetY(localPoint.GetY() + 1);
    EXPECT_EQ(pattern_->scrollableEvent_->InBarRegion(localPoint, source), false);

    pattern_->panRecognizer_ = nullptr;
    pattern_->scrollableEvent_->BarCollectTouchTarget(coordinateOffset, getEventTargetImpl, result);
    EXPECT_EQ(result.size(), size + 1);
}

/**
 * @tc.name: ScrollBarTest013
 * @tc.desc: Test StartDisappearAnimator of ScrollBarPattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar and initialize related properties.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(SCROLL_BAR_SELF_SIZE);
    CreateScrollBar(true, true, -1, 0, layoutConstraint);

    /**
     * @tc.steps: step2. Verify the StartDisappearAnimator function of ScrollBarPattern.
     * @tc.expected: step2. Compare the value with expected value.
     */
    pattern_->SetControlDistance(10.f);
    layoutProperty_->UpdateDisplayMode(DisplayMode::AUTO);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->GetDisplayMode(), DisplayMode::AUTO);
    EXPECT_EQ(pattern_->opacity_, 0);

    layoutProperty_->UpdateDisplayMode(DisplayMode::OFF);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->GetDisplayMode(), DisplayMode::OFF);

    layoutProperty_->UpdateDisplayMode(DisplayMode::AUTO);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->GetDisplayMode(), DisplayMode::AUTO);
    EXPECT_EQ(pattern_->opacity_, 0);
    EXPECT_NE(pattern_->disappearAnimation_, nullptr);

    /**
     * @tc.steps: step2. Verify the StopDisappearAnimator function of ScrollBarPattern.
     * @tc.expected: step2. Compare the value with expected value.
     */
    layoutProperty_->UpdateDisplayMode(DisplayMode::ON);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->GetDisplayMode(), DisplayMode::ON);
    EXPECT_NE(pattern_->disappearAnimation_, nullptr);
    EXPECT_EQ(pattern_->opacity_, UINT8_MAX);
}

/**
 * @tc.name: ScrollBarTest014
 * @tc.desc: Test ProcessFrictionMotion of ScrollBarPattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ScrollBarTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scrollBar and initialize related properties.
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(SCROLL_BAR_SELF_SIZE);
    CreateScrollBar(true, true, -1, -1, layoutConstraint);

    /**
     * @tc.steps: step2. Verify the ProcessFrictionMotion function of ScrollBarPattern.
     * @tc.expected: step2. Compare the value with expected value.
     */
    pattern_->ProcessFrictionMotion(10.0);
    pattern_->ProcessFrictionMotionStop();
    EXPECT_DOUBLE_EQ(pattern_->frictionPosition_, 10.0);

    pattern_->scrollBarProxy_ = nullptr;
    pattern_->scrollPositionCallback_ = nullptr;
    pattern_->ProcessFrictionMotion(20.0);
    pattern_->ProcessFrictionMotionStop();
    EXPECT_DOUBLE_EQ(pattern_->frictionPosition_, 20.0);

    pattern_->scrollEndCallback_ = nullptr;
    pattern_->scrollableEvent_ = nullptr;
    pattern_->ProcessFrictionMotionStop();
    pattern_->OnModifyDone();
    EXPECT_NE(pattern_->scrollEndCallback_, nullptr);
    EXPECT_NE(pattern_->scrollPositionCallback_, nullptr);
    EXPECT_NE(pattern_->scrollableEvent_, nullptr);
}
} // namespace OHOS::Ace::NG