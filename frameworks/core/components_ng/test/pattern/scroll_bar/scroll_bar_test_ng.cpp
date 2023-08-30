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

#define private public
#define protected public
#include "gtest/gtest.h"

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components/scroll/scrollable.h"
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

class ScrollBarTestNg : public testing::Test {};

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
    RefPtr<ScrollProxy> scrollProxy;
    ScrollBarModelNG scrollBarModelNG;
    auto proxy = scrollBarModelNG.GetScrollBarProxy(scrollProxy);
    scrollBarModelNG.Create(proxy, true, false,
        static_cast<int>(Axis::VERTICAL), static_cast<int>(DisplayMode::OFF));

    /**
     * @tc.steps: step2. Get scrollBar frameNode to create scrollBar layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto pattern = frameNode->GetPattern<ScrollBarPattern>();
    EXPECT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(SCROLL_BAR_SELF_SIZE);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(scrollLayoutAlgorithm));

    /**
     * @tc.steps: step3. Create child layoutWrapper and add it to scrollBar frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childFrameNode, childGeometryNode, childLayoutProperty);
    childLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SCROLL_BAR_CHILD_WIDTH), CalcLength(SCROLL_BAR_CHILD_HEIGHT)));
    auto childLayoutAlgorithm = childFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_NE(childLayoutAlgorithm, nullptr);
    childLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(childLayoutAlgorithm));
    layoutWrapper->AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Call the measure and layout function of scrollBar to calculate the size and offset.
     */
    scrollLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    scrollLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step5. After the layout is completed, check the framesize of the scrollBar and child nodes.
     * @tc.expected: step5. Compare whether the return value is expected to be the same.
     */
    auto childLayout = layoutWrapper->GetOrCreateChildByIndex(0);
    EXPECT_NE(childLayout, nullptr);
    auto scrollBarSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(scrollBarSize, SCROLL_BAR_SELF_SIZE) <<
        "scrollBarSize: " << scrollBarSize.ToString() <<
        " SCROLL_BAR_SELF_SIZE: " << SCROLL_BAR_SELF_SIZE.ToString();
    auto childSize = childLayout->GetGeometryNode()->GetFrameSize();
    auto expectChildSize = SizeF(SCROLL_BAR_CHILD_WIDTH, SCROLL_BAR_CHILD_HEIGHT);
    EXPECT_EQ(childSize, expectChildSize) <<
        "childSize: " << childSize.ToString() <<
        " expectChildSize: " << expectChildSize.ToString();

    /**
     * @tc.steps: step6. Verify the OnDirtyLayoutWrapperSwap function of scrollBar.
     * @tc.expected: step6. Compare return value with expected value.
     */
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    auto ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(ret, false);
    config.skipMeasure = true;
    config.skipLayout = true;
    ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(ret, false);
    config.skipMeasure = false;
    config.skipLayout = false;
    ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(ret, false);
    auto expectDistance = SCROLL_BAR_SELF_SIZE.Height() - SCROLL_BAR_CHILD_HEIGHT; // 1036
    EXPECT_EQ(pattern->scrollableDistance_, expectDistance);
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
    RefPtr<ScrollProxy> scrollProxy;
    ScrollBarModelNG scrollBarModelNG;
    auto proxy = scrollBarModelNG.GetScrollBarProxy(scrollProxy);
    scrollBarModelNG.Create(proxy, true, false,
        static_cast<int>(Axis::HORIZONTAL), static_cast<int>(DisplayMode::AUTO));

    /**
     * @tc.steps: step2. Get scrollBar frameNode to create scrollBar layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto pattern = frameNode->GetPattern<ScrollBarPattern>();
    EXPECT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(scrollLayoutAlgorithm));

    /**
     * @tc.steps: step3. Create child layoutWrapper and add it to scrollBar frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childFrameNode, childGeometryNode, childLayoutProperty);
    childLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SCROLL_BAR_CHILD_WIDTH), CalcLength(SCROLL_BAR_CHILD_HEIGHT)));
    auto childLayoutAlgorithm = childFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_NE(childLayoutAlgorithm, nullptr);
    childLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(childLayoutAlgorithm));
    layoutWrapper->AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Call the measure and layout function of scrollBar to calculate the size and offset.
     */
    scrollLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    scrollLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step5. After the layout is completed, check the framesize of the scrollBar and child nodes.
     * @tc.expected: step5. Compare whether the return value is expected to be the same.
     */
    auto childLayout = layoutWrapper->GetOrCreateChildByIndex(0);
    EXPECT_NE(childLayout, nullptr);
    auto scrollBarSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    // has no idealSize, scrollBarSize.height is child.height
    EXPECT_EQ(scrollBarSize, SizeF(DEVICE_WIDTH, SCROLL_BAR_CHILD_HEIGHT)) <<
        "scrollBarSize: " << scrollBarSize.ToString() <<
        " SizeF(DEVICE_WIDTH, SCROLL_BAR_CHILD_HEIGHT): " <<
        SizeF(DEVICE_WIDTH, SCROLL_BAR_CHILD_HEIGHT).ToString();
    auto childSize = childLayout->GetGeometryNode()->GetFrameSize();
    auto expectChildSize = SizeF(SCROLL_BAR_CHILD_WIDTH, SCROLL_BAR_CHILD_HEIGHT);
    EXPECT_EQ(childSize, expectChildSize) <<
        "childSize: " << childSize.ToString() <<
        " expectChildSize: " << expectChildSize.ToString();

    /**
     * @tc.steps: step6. Verify the callback function in scrollBar under different conditions.
     * @tc.expected: step6. Compare return value with expected value.
     */
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->axis_, Axis::HORIZONTAL);
    auto callback = pattern->scrollPositionCallback_;
    EXPECT_NE(callback, nullptr);
    auto ret = callback(0.0, SCROLL_FROM_START);
    EXPECT_EQ(ret, true);
    ret = callback(0.0, SCROLL_FROM_BAR);
    EXPECT_EQ(ret, false);
    ret = callback(1.0, SCROLL_FROM_UPDATE);
    EXPECT_EQ(ret, false);
    ret = callback(-1.0, SCROLL_FROM_ANIMATION);
    EXPECT_EQ(ret, false);

    pattern->scrollableDistance_ = SCROLL_BAR_FLOAT_100;
    ret = callback(1.0, SCROLL_FROM_BAR);
    EXPECT_EQ(ret, true);
    EXPECT_EQ(pattern->lastOffset_, 0.0f);
    EXPECT_EQ(pattern->currentOffset_, 1.0f);
    pattern->axis_ = Axis::NONE;
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
    RefPtr<ScrollProxy> scrollProxy;
    ScrollBarModelNG scrollBarModelNG;
    auto proxy = scrollBarModelNG.GetScrollBarProxy(scrollProxy);
    scrollBarModelNG.Create(proxy, true, false,
        static_cast<int>(Axis::HORIZONTAL), static_cast<int>(DisplayMode::ON));

    /**
     * @tc.steps: step2. Get scrollBar frameNode to create scrollBar layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto pattern = frameNode->GetPattern<ScrollBarPattern>();
    EXPECT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutConstraint.selfIdealSize.SetSize(SCROLL_BAR_SELF_SIZE);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(scrollLayoutAlgorithm));

    /**
     * @tc.steps: step3. Create child layoutWrapper and add it to scrollBar frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childFrameNode, childGeometryNode, childLayoutProperty);
    childLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SCROLL_BAR_CHILD_WIDTH), CalcLength(SCROLL_BAR_CHILD_HEIGHT)));
    auto childLayoutAlgorithm = childFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_NE(childLayoutAlgorithm, nullptr);
    childLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(childLayoutAlgorithm));
    layoutWrapper->AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Call the measure and layout function of scrollBar to calculate the size and offset.
     */
    scrollLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    scrollLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step5. After the layout is completed, check the framesize of the scrollBar and child nodes.
     * @tc.expected: step5. Compare whether the return value is expected to be the same.
     */
    auto childLayout = layoutWrapper->GetOrCreateChildByIndex(0);
    EXPECT_NE(childLayout, nullptr);
    auto scrollBarSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(scrollBarSize, SCROLL_BAR_SELF_SIZE) <<
        "scrollBarSize: " << scrollBarSize.ToString() <<
        " SCROLL_BAR_SELF_SIZE: " << SCROLL_BAR_SELF_SIZE.ToString();
    auto childSize = childLayout->GetGeometryNode()->GetFrameSize();
    auto expectChildSize = SizeF(SCROLL_BAR_CHILD_WIDTH, SCROLL_BAR_CHILD_HEIGHT);
    EXPECT_EQ(childSize, expectChildSize) <<
        "childSize: " << childSize.ToString() <<
        " expectChildSize: " << expectChildSize.ToString();

    /**
     * @tc.steps: step6. Verify the callback function in scrollBar under different conditions.
     * @tc.expected: step6. Compare return value with expected value.
     */
    auto scrollBarProxy = AceType::MakeRefPtr<ScrollBarProxy>();
    EXPECT_NE(scrollBarProxy, nullptr);
    pattern->SetScrollBarProxy(scrollBarProxy);
    EXPECT_NE(pattern->scrollBarProxy_, nullptr);
    auto callback = pattern->scrollPositionCallback_;
    EXPECT_NE(callback, nullptr);
    pattern->scrollableDistance_ = SCROLL_BAR_FLOAT_100;
    auto ret = callback(1.0, SCROLL_FROM_BAR);
    EXPECT_EQ(ret, true);
    pattern->currentOffset_ = SCROLL_BAR_FLOAT_10;
    ret = callback(1.0, SCROLL_FROM_BAR);
    EXPECT_EQ(ret, true);
    pattern->currentOffset_ = -1.0f;
    pattern->scrollableDistance_ = 0.0f;
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
    RefPtr<ScrollProxy> scrollProxy;
    ScrollBarModelNG scrollBarModelNG;
    auto proxy = scrollBarModelNG.GetScrollBarProxy(scrollProxy);
    scrollBarModelNG.Create(proxy, true, false,
        static_cast<int>(Axis::VERTICAL), -1);

    /**
     * @tc.steps: step2. Get scrollBar frameNode to create scrollBar layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto pattern = frameNode->GetPattern<ScrollBarPattern>();
    EXPECT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(scrollLayoutAlgorithm));

    /**
     * @tc.steps: step3. Create child layoutWrapper and add it to scrollBar frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childFrameNode, childGeometryNode, childLayoutProperty);
    childLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SCROLL_BAR_CHILD_WIDTH), CalcLength(SCROLL_BAR_CHILD_HEIGHT)));
    auto childLayoutAlgorithm = childFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_NE(childLayoutAlgorithm, nullptr);
    childLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(childLayoutAlgorithm));
    layoutWrapper->AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Call the measure and layout function of scrollBar to calculate the size and offset.
     */
    scrollLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    scrollLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step5. After the layout is completed, check the framesize of the scrollBar and child nodes.
     * @tc.expected: step5. Compare whether the return value is expected to be the same.
     */
    auto childLayout = layoutWrapper->GetOrCreateChildByIndex(0);
    EXPECT_NE(childLayout, nullptr);
    auto scrollBarSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto expectScrollBarSize = SizeF(SCROLL_BAR_CHILD_WIDTH, DEVICE_HEIGHT);
    // has no idealSize, scrollBarSize.width is child.width
    EXPECT_EQ(scrollBarSize, expectScrollBarSize) <<
        "scrollBarSize: " << scrollBarSize.ToString() <<
        " expectScrollBarSize: " << expectScrollBarSize.ToString();
    auto childSize = childLayout->GetGeometryNode()->GetFrameSize();
    auto expectChildSize = SizeF(SCROLL_BAR_CHILD_WIDTH, SCROLL_BAR_CHILD_HEIGHT);
    EXPECT_EQ(childSize, expectChildSize) <<
        "childSize: " << childSize.ToString() <<
        " expectChildSize: " << expectChildSize.ToString();

    /**
     * @tc.steps: step6. Create scrollbar proxy and verify the RegisterScrollableNode function and NotifyScrollableNode
     * function.
     * @tc.expected: step6. Check whether relevant parameters are correct.
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
    auto* scrollBarPatternRaw = AceType::RawPtr(pattern);
    EXPECT_NE(scrollBarPatternRaw, nullptr);
    scrollBarProxy->NotifyScrollableNode(1.0, AceType::WeakClaim(scrollBarPatternRaw));
    EXPECT_EQ(distance, 0.0);
    EXPECT_EQ(source, SCROLL_FROM_BAR);

    /**
     * @tc.steps: step7. When calling RegisterScrollableNode multiple times, verify the relevant parameters.
     * @tc.expected: step7. Check whether relevant parameters are correct.
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
    pattern->scrollableDistance_ = SCROLL_BAR_FLOAT_100;
    scrollBarProxy->NotifyScrollableNode(1.0, AceType::WeakClaim(scrollBarPatternRaw));
    EXPECT_EQ(distance, 1.0);
    EXPECT_EQ(source, SCROLL_FROM_BAR);

    /**
     * @tc.steps: step8. Repeatedly call UnRegisterScrollableNode to delete the relevant ScrollableNode.
     * @tc.expected: step8. Check the size of the list container.
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
    RefPtr<ScrollProxy> scrollProxy;
    ScrollBarModelNG scrollBarModelNG;
    auto proxy = scrollBarModelNG.GetScrollBarProxy(scrollProxy);
    scrollBarModelNG.Create(proxy, true, false, 3, 3);

    /**
     * @tc.steps: step2. Get scrollBar frameNode to create scrollBar layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto pattern = frameNode->GetPattern<ScrollBarPattern>();
    ASSERT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(scrollLayoutAlgorithm, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.parentIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    auto wrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(scrollLayoutAlgorithm);
    ASSERT_NE(wrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(wrapper);

    /**
     * @tc.steps: step3. Create child layoutWrapper and add it to scrollBar frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(childGeometryNode, nullptr);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    ASSERT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(childFrameNode, childGeometryNode, childLayoutProperty);
    ASSERT_NE(childLayoutWrapper, nullptr);
    auto funcase = childLayoutWrapper->GetLayoutProperty();
    ASSERT_NE(funcase, nullptr);
    funcase->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SCROLL_BAR_CHILD_WIDTH), CalcLength(SCROLL_BAR_CHILD_HEIGHT)));
    auto childFrameNodepattern = childFrameNode->GetPattern<Pattern>();
    ASSERT_NE(childFrameNodepattern, nullptr);
    auto childLayoutAlgorithm = childFrameNodepattern->CreateLayoutAlgorithm();
    ASSERT_NE(childLayoutAlgorithm, nullptr);
    auto layevent = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(childLayoutAlgorithm);
    ASSERT_NE(layevent, nullptr);
    childLayoutWrapper->SetLayoutAlgorithm(layevent);
    layoutWrapper->AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Call the measure and layout function of scrollBar to calculate the size and offset.
     */
    scrollLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    scrollLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step5. Create scrollbar proxy and verify the RegisterScrollBar function and RegisterScrollBar
     * function.
     * @tc.expected: step5. Check whether relevant parameters are correct.
     */
    RefPtr<ScrollProxy> ScrollProxy = AceType::MakeRefPtr<ScrollBarProxy>();
    ASSERT_NE(ScrollProxy, nullptr);
    auto scrollBarProxy = AceType::DynamicCast<ScrollBarProxy>(ScrollProxy);
    ASSERT_NE(scrollBarProxy, nullptr);
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto* scrollRaw = AceType::RawPtr(scrollPattern);
    ASSERT_NE(scrollRaw, nullptr);
    auto* scrollBarPatternRaw1 = AceType::RawPtr(pattern);
    ASSERT_NE(scrollBarPatternRaw1, nullptr);
    scrollBarProxy->RegisterScrollBar(AceType::WeakClaim(scrollBarPatternRaw1));
    EXPECT_EQ(scrollBarProxy->scrollBars_.size(), 1);
    scrollBarProxy->NotifyScrollBar(AceType::WeakClaim(scrollRaw));
    EXPECT_EQ(pattern->currentOffset_, 0.0f);

    /**
     * @tc.steps: step6. When calling RegisterScrollBar multiple times, verify the relevant parameters.
     * @tc.expected: step6. Check whether relevant parameters are correct.
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
    pattern->displayMode_ = DisplayMode::AUTO;
    scrollBarProxy->StartScrollBarAnimator();
    scrollBarProxy->StopScrollBarAnimator();
    scrollPattern->estimatedHeight_ = SCROLL_BAR_FLOAT_100;
    scrollPattern->barOffset_ = SCROLL_BAR_FLOAT_NEGATIVE_100;
    pattern->scrollableDistance_ = 1.0f;
    EXPECT_EQ(pattern->currentOffset_, 0.0f);

    /**
     * @tc.steps: step7. Repeatedly call UnRegisterScrollBar to delete the relevant scrollableBar.
     * @tc.expected: step7. Check the size of the list container.
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
    RefPtr<ScrollProxy> scrollProxy;
    ScrollBarModelNG scrollBarModelNG;
    auto proxy = scrollBarModelNG.GetScrollBarProxy(scrollProxy);
    scrollBarModelNG.Create(proxy, true, false, 3, 3);

    /**
     * @tc.steps: step2. Get scrollBar frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto scrollBarPattern = frameNode->GetPattern<ScrollBarPattern>();
    ASSERT_NE(scrollBarPattern, nullptr);
    scrollBarPattern->axis_ = Axis::NONE;
    scrollBarPattern->scrollableDistance_ = 0.0;
    scrollBarPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step3. Get scrollBar accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto scrollBarAccessibilityProperty = frameNode->GetAccessibilityProperty<ScrollBarAccessibilityProperty>();
    ASSERT_NE(scrollBarAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step4. When scrollBar Axis is NONE and scrollable distance is 0, call the callback function in
     *                   scrollBarAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(scrollBarAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(scrollBarAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When scrollBar Axis is NONE and scrollable distance is not 0, call the callback function in
     *                   scrollBarAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    scrollBarPattern->scrollableDistance_ = SCROLL_BAR_FLOAT_100;
    EXPECT_TRUE(scrollBarAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(scrollBarAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step6. When scrollBar Axis is VERTICAL and scrollable distance is not 0, call the callback function in
     *                   scrollBarAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    scrollBarPattern->axis_ = Axis::VERTICAL;
    EXPECT_TRUE(scrollBarAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(scrollBarAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step7. When scrollBar Axis is VERTICAL and scrollable distance is 0, call the callback function in
     *                   scrollBarAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    scrollBarPattern->scrollableDistance_ = 0.0;
    EXPECT_TRUE(scrollBarAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(scrollBarAccessibilityProperty->ActActionScrollBackward());
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
    RefPtr<ScrollProxy> scrollProxy;
    ScrollBarModelNG scrollBarModelNG;
    auto proxy = scrollBarModelNG.GetScrollBarProxy(scrollProxy);
    scrollBarModelNG.Create(proxy, true, false,
        static_cast<int>(Axis::VERTICAL), static_cast<int>(DisplayMode::OFF));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollBarPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. set callback function.
     */
    pattern->OnModifyDone();
    ASSERT_NE(pattern->scrollableEvent_, nullptr);
    auto callback = pattern->scrollEndCallback_;
    ASSERT_NE(callback, nullptr);
    EXPECT_EQ(pattern->scrollEndAnimator_, nullptr);

    /**
     * @tc.steps: step3. call callback function and controlDistance_ is 0.
     * @tc.expected: scrollEndAnimator_ is nullptr.
     */
    pattern->displayMode_ = DisplayMode::AUTO;
    callback();
    EXPECT_EQ(pattern->scrollEndAnimator_, nullptr);

    /**
     * @tc.steps: step4. call callback function and controlDistance_ bigger than 0.
     * @tc.expected: scrollEndAnimator_ is not nullptr.
     */
    pattern->controlDistance_ = 10.f;
    pattern->displayMode_ = DisplayMode::AUTO;
    callback();
    EXPECT_NE(pattern->scrollEndAnimator_, nullptr);
}
} // namespace OHOS::Ace::NG
