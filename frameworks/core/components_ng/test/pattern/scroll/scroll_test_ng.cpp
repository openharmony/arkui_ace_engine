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

#define private public
#define protected public
#include <cstdint>
#include <memory>
#include <utility>

#include "gtest/gtest-test-part.h"
#include "gtest/gtest.h"

#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll/effect/scroll_fade_effect.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_paint_property.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float DEVICE_WIDTH = 720.0f;
constexpr float DEVICE_HEIGHT = 1136.0f;
constexpr float SCROLL_FLOAT_10 = 10.0f;
constexpr float SCROLL_FLOAT_50 = 50.0f;
constexpr float SCROLL_FLOAT_98 = 98.0f;
constexpr float SCROLL_FLOAT_100 = 100.0f;
constexpr float SCROLL_FLOAT_NEGATIVE_10 = -10.0f;
constexpr float SCROLL_FLOAT_NEGATIVE_100 = -100.0f;
constexpr float SCROLL_FLOAT_NEGATIVE_200 = -200.0f;
constexpr float SCROLL_DOUBLE_10 = 10.0;
constexpr double SCROLL_DOUBLE_99 = 99.0;
constexpr double SCROLL_DOUBLE_100 = 100.0;
constexpr double SCROLL_DOUBLE_200 = 200.0;
constexpr double SCROLL_DOUBLE_NEGATIVE_10 = -10.0;
constexpr double SCROLL_DOUBLE_NEGATIVE_99 = -99.0;
constexpr double SCROLL_DOUBLE_NEGATIVE_100 = -100.0;
constexpr int32_t SCROLL_INT32_1000 = 1000;
const SizeF CONTAINER_SIZE(DEVICE_WIDTH, DEVICE_HEIGHT);
const SizeF SCROLL_CHILD_SIZE(500.0f, 1000.0f);
const SizeF SCROLL_VIEW_PORT(1.0f, 1.0f);
const Dimension SCROLL_BAR_WIDTH = Dimension(20.1, DimensionUnit::PX);
const Color SCROLL_BAR_COLOR = Color::FromRGB(255, 100, 100);
const Offset SCROLL_OFFSET_ZERO = Offset(0.0, 0.0);
const Offset SCROLL_OFFSET_ONE = Offset(1.0, 1.0);
const Size SCROLL_SIZE_100 = Size(100.0, 100.0);
const Rect SCROLLBAR_RECT_LEFT = Rect(0.0, -9900.0, 0.0, 10000.0);
const Rect SCROLLBAR_RECT_BOTTOM = Rect(-9899.0, 100.0, 9999.0, 0.0);
const Rect SCROLLBAR_RECT_RIGHT = Rect(100.0, -9899.0, 0.0, 9999.0);
} // namespace

class ScrollTestNg : public testing::Test {};

/**
 * @tc.name: ScrollTest001
 * @tc.desc: When setting a fixed length and width, verify the Measure and Layout functions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties.
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::VERTICAL);
    scrollModel.SetDisplayMode(0); // DisplayMode::OFF
    scrollModel.SetScrollBarWidth(SCROLL_BAR_WIDTH);
    scrollModel.SetScrollBarColor(SCROLL_BAR_COLOR);
    scrollModel.SetEdgeEffect(EdgeEffect::FADE);

    /**
     * @tc.steps: step2. Get scroll frameNode to create scroll layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. Create grid layoutWrapper and add it to scroll frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SCROLL_CHILD_SIZE);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(childFrameNode, childGeometryNode, childLayoutProperty);
    layoutWrapper.AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Get scroll pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step4. related function is called.
     */
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    EXPECT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    scrollLayoutAlgorithm->Measure(&layoutWrapper);
    scrollLayoutAlgorithm->Layout(&layoutWrapper);

    /**
     * @tc.steps: step5. After the layout is completed, check the framesize of the scroll and child nodes.
     * @tc.expected: step5. Compare whether the return value is expected to be the same.
     */
    auto childLayout = layoutWrapper.GetOrCreateChildByIndex(0);
    EXPECT_NE(childLayout, nullptr);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), CONTAINER_SIZE);
    EXPECT_EQ(childLayout->GetGeometryNode()->GetFrameSize(), SCROLL_CHILD_SIZE);
}

/**
 * @tc.name: ScrollTest002
 * @tc.desc: When the fixed length and width are not set, verify the Measure and Layout functions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties.
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::HORIZONTAL);
    scrollModel.SetDisplayMode(1); // DisplayMode::AUTO
    scrollModel.SetScrollBarWidth(SCROLL_BAR_WIDTH);
    scrollModel.SetScrollBarColor(SCROLL_BAR_COLOR);
    scrollModel.SetEdgeEffect(EdgeEffect::SPRING);

    /**
     * @tc.steps: step2. Get scroll frameNode to create scroll layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. Create grid layoutWrapper and add it to scroll frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SCROLL_CHILD_SIZE);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(childFrameNode, childGeometryNode, childLayoutProperty);
    layoutWrapper.AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Get scroll pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step4. related function is called.
     */
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    EXPECT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    scrollLayoutAlgorithm->Measure(&layoutWrapper);
    scrollLayoutAlgorithm->Layout(&layoutWrapper);

    /**
     * @tc.steps: step5. After the layout is completed, check the framesize of the scroll and child nodes.
     * @tc.expected: step5. Compare whether the return value is expected to be the same.
     */
    auto childLayout = layoutWrapper.GetOrCreateChildByIndex(0);
    EXPECT_NE(childLayout, nullptr);
    EXPECT_EQ(layoutWrapper.GetGeometryNode()->GetFrameSize(), SCROLL_CHILD_SIZE);
    EXPECT_EQ(childLayout->GetGeometryNode()->GetFrameSize(), SCROLL_CHILD_SIZE);
}

/**
 * @tc.name: ScrollTest003
 * @tc.desc: When the fixed length and width are not set, verify the Measure and Layout functions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties.
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::VERTICAL);
    scrollModel.SetDisplayMode(2); // DisplayMode::On
    scrollModel.SetScrollBarWidth(SCROLL_BAR_WIDTH);
    scrollModel.SetScrollBarColor(SCROLL_BAR_COLOR);
    scrollModel.SetEdgeEffect(EdgeEffect::NONE);

    /**
     * @tc.steps: step2. Get scroll frameNode to create scroll layoutWrapper and set layoutAlgorithm.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    EXPECT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    RefPtr<LayoutWrapper> layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(scrollLayoutAlgorithm));

    /**
     * @tc.steps: step3. Create grid layoutWrapper and add it to scroll frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SCROLL_CHILD_SIZE);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(childFrameNode, childGeometryNode, childLayoutProperty);
    auto childLayoutAlgorithm = childFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_NE(childLayoutAlgorithm, nullptr);
    childLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(childLayoutAlgorithm));
    layoutWrapper->AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. call the measure and layout function of scroll to calculate the size and offset.
     */
    scrollLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    scrollLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step5. Verify the OnDirtyLayoutWrapperSwap function of scroll.
     * @tc.expected: step5. Compare return value with expected value.
     */
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = false;
    auto dirty = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(dirty, false);
    config.skipMeasure = true;
    config.skipLayout = true;
    dirty = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(dirty, false);

    /**
     * @tc.steps: step6. When Axis is VERTICAL and EdgeEffect is NONE, verify the callback function in the
     * scrollableEvent under different conditions.
     * @tc.expected: step6. Check whether the return value is as expected.
     */
    auto callback = pattern->scrollableEvent_->GetScrollPositionCallback();
    auto ret = callback(0.0, SCROLL_FROM_START);
    EXPECT_EQ(ret, true);
    ret = callback(0.0, SCROLL_FROM_UPDATE);
    EXPECT_EQ(ret, false);

    pattern->currentOffset_ = SCROLL_FLOAT_100;
    pattern->scrollableDistance_ = SCROLL_FLOAT_100;
    pattern->viewPortLength_ = SCROLL_FLOAT_100;
    ret = callback(SCROLL_DOUBLE_10, SCROLL_FROM_UPDATE);
    EXPECT_EQ(ret, false);

    pattern->currentOffset_ = SCROLL_FLOAT_100;
    pattern->scrollableDistance_ = SCROLL_FLOAT_NEGATIVE_100;
    pattern->viewPortLength_ = SCROLL_FLOAT_100;
    ret = callback(SCROLL_DOUBLE_NEGATIVE_10, SCROLL_FROM_UPDATE);
    EXPECT_EQ(ret, false);

    /**
     * @tc.steps: step7. Call the ResetPosition function.
     * @tc.expected: step7. Check whether relevant parameters are correct.
     */
    pattern->ResetPosition();
    EXPECT_EQ(pattern->currentOffset_, 0.0f);
    EXPECT_EQ(pattern->lastOffset_, 0.0f);
}

/**
 * @tc.name: ScrollTest004
 * @tc.desc: When setting a fixed length and width, verify the related functions in the scroll pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties.
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::VERTICAL);
    scrollModel.SetDisplayMode(0);
    scrollModel.SetScrollBarWidth(SCROLL_BAR_WIDTH);
    scrollModel.SetScrollBarColor(SCROLL_BAR_COLOR);
    scrollModel.SetEdgeEffect(EdgeEffect::FADE);

    /**
     * @tc.steps: step2. Get scroll frameNode to create scroll layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    RefPtr<LayoutWrapper> layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, layoutProperty);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(scrollLayoutAlgorithm));

    /**
     * @tc.steps: step3. Create grid layoutWrapper and add it to scroll frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SCROLL_CHILD_SIZE);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(childFrameNode, childGeometryNode, childLayoutProperty);
    auto childLayoutAlgorithm = childFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    EXPECT_NE(childLayoutAlgorithm, nullptr);
    childLayoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(childLayoutAlgorithm));
    layoutWrapper->AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. call the measure and layout function of scroll to calculate the size and offset.
     */
    scrollLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    scrollLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step5. Verify the OnDirtyLayoutWrapperSwap function of scroll.
     * @tc.expected: step5. Compare return value with expected value.
     */
    DirtySwapConfig config;
    config.skipMeasure = false;
    config.skipLayout = false;
    auto dirty = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(dirty, false);
    config.skipMeasure = true;
    config.skipLayout = true;
    dirty = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(dirty, false);

    /**
     * @tc.steps: step6. When Axis is VERTICAL and EdgeEffect is FADE, verify the callback function in the
     * scrollableEvent under different conditions.
     * @tc.expected: step6. Check whether the return value is as expected.
     */
    auto callback = pattern->scrollableEvent_->GetScrollPositionCallback();
    EXPECT_NE(callback, nullptr);
    auto ret = callback(0.0, SCROLL_FROM_UPDATE);
    EXPECT_EQ(ret, false);
    ret = callback(1.0, SCROLL_FROM_ANIMATION);
    EXPECT_EQ(ret, false);
    ret = callback(-1.0, SCROLL_FROM_ANIMATION_SPRING);
    EXPECT_EQ(ret, false);
    pattern->viewPortLength_ = 0.0f;
    ret = callback(1.0, SCROLL_FROM_BAR);
    EXPECT_EQ(ret, false);

    pattern->currentOffset_ = SCROLL_FLOAT_100;
    pattern->scrollableDistance_ = SCROLL_FLOAT_100;
    pattern->viewPortLength_ = SCROLL_FLOAT_10;
    pattern->viewPortLength_ = SCROLL_FLOAT_100;
    ret = callback(SCROLL_DOUBLE_10, SCROLL_FROM_JUMP);
    EXPECT_EQ(ret, false);

    pattern->currentOffset_ = 0.0f;
    pattern->scrollableDistance_ = SCROLL_FLOAT_NEGATIVE_100;
    pattern->viewPortLength_ = SCROLL_FLOAT_100;
    ret = callback(SCROLL_DOUBLE_100, SCROLL_FROM_ROTATE);
    EXPECT_EQ(ret, false);

    pattern->currentOffset_ = SCROLL_FLOAT_100;
    pattern->scrollableDistance_ = SCROLL_FLOAT_NEGATIVE_100;
    pattern->viewPortLength_ = SCROLL_FLOAT_100;
    ret = callback(SCROLL_DOUBLE_200, SCROLL_FROM_UPDATE);
    EXPECT_EQ(ret, false);

    pattern->currentOffset_ = 0.0f;
    pattern->scrollableDistance_ = 0.0f;
    pattern->viewPortLength_ = SCROLL_FLOAT_100;
    ret = callback(SCROLL_DOUBLE_NEGATIVE_100, SCROLL_FROM_ANIMATION_SPRING);
    EXPECT_EQ(ret, false);

    pattern->currentOffset_ = SCROLL_FLOAT_100;
    pattern->scrollableDistance_ = SCROLL_FLOAT_NEGATIVE_100;
    pattern->viewPortLength_ = SCROLL_FLOAT_100;
    ret = callback(SCROLL_DOUBLE_NEGATIVE_100, SCROLL_FROM_UPDATE);
    EXPECT_EQ(ret, false);
}

/**
 * @tc.name: ScrollTest005
 * @tc.desc: When setting a fixed length and width, verify the related functions in the scroll pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties.
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::HORIZONTAL);
    scrollModel.SetDisplayMode(0);
    scrollModel.SetScrollBarWidth(SCROLL_BAR_WIDTH);
    scrollModel.SetScrollBarColor(SCROLL_BAR_COLOR);
    scrollModel.SetEdgeEffect(EdgeEffect::SPRING);
    auto scrollProxy = scrollModel.CreateScrollBarProxy();
    scrollModel.SetScrollBarProxy(scrollProxy);

    /**
     * @tc.steps: step2. Get scroll frameNode to create scroll layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. Create grid layoutWrapper and add it to scroll frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SCROLL_CHILD_SIZE);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(childFrameNode, childGeometryNode, childLayoutProperty);
    layoutWrapper.AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Get scroll pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step4. related function is called.
     */
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    EXPECT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    scrollLayoutAlgorithm->Measure(&layoutWrapper);
    scrollLayoutAlgorithm->Layout(&layoutWrapper);

    /**
     * @tc.steps: step5. When Axis is HORIZONTAL and EdgeEffect is SPRING, verify the callback function in the
     * scrollableEvent under different conditions.
     * @tc.expected: step5. Check whether the return value is as expected.
     */
    auto callback = pattern->scrollableEvent_->GetScrollPositionCallback();
    EXPECT_NE(callback, nullptr);
    pattern->currentOffset_ = SCROLL_FLOAT_NEGATIVE_10;
    pattern->scrollableDistance_ = SCROLL_FLOAT_100;
    pattern->viewPortLength_ = SCROLL_FLOAT_100;
    auto ret = callback(SCROLL_DOUBLE_100, SCROLL_FROM_BAR);
    EXPECT_EQ(ret, true);

    pattern->currentOffset_ = SCROLL_FLOAT_NEGATIVE_100;
    pattern->scrollableDistance_ = SCROLL_FLOAT_NEGATIVE_10;
    pattern->viewPortLength_ = SCROLL_FLOAT_100;
    ret = callback(SCROLL_DOUBLE_200, SCROLL_FROM_ROTATE);
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step5. When Axis is HORIZONTAL, Verify the callback function registered in scrollBarProxy.
     * @tc.expected: step5. Check whether the return value is as expected.
     */
    auto scrollBarProxy = AceType::DynamicCast<ScrollBarProxy>(scrollProxy);
    EXPECT_NE(scrollBarProxy, nullptr);
    EXPECT_EQ(scrollBarProxy->scrollableNodes_.empty(), false);
    ret = scrollBarProxy->scrollableNodes_.back().onPositionChanged(0.0, SCROLL_FROM_BAR);
    EXPECT_EQ(ret, false);
    ret = scrollBarProxy->scrollableNodes_.back().onPositionChanged(0.0, SCROLL_FROM_START);
    EXPECT_EQ(ret, true);
}

/**
 * @tc.name: ScrollTest006
 * @tc.desc: When setting a fixed length and width, Verify the related functions in the scroll pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties.
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::HORIZONTAL);
    scrollModel.SetDisplayMode(0);
    scrollModel.SetScrollBarWidth(SCROLL_BAR_WIDTH);
    scrollModel.SetScrollBarColor(SCROLL_BAR_COLOR);
    scrollModel.SetScrollBarProxy(scrollModel.CreateScrollBarProxy());

    /**
     * @tc.steps: step2. Get scroll frameNode to create scroll layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. Create grid layoutWrapper and add it to scroll frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SCROLL_CHILD_SIZE);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(childFrameNode, childGeometryNode, childLayoutProperty);
    layoutWrapper.AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Get scroll pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step4. related function is called.
     */
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    EXPECT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    scrollLayoutAlgorithm->Measure(&layoutWrapper);
    scrollLayoutAlgorithm->Layout(&layoutWrapper);

    /**
     * @tc.steps: step5. When not set EdgeEffect, verify the callback function in the scrollableEvent under different
     *            conditions.
     * @tc.expected: step5. Check whether the return value is as expected.
     */
    auto callback = pattern->scrollableEvent_->GetScrollPositionCallback();
    EXPECT_NE(callback, nullptr);
    pattern->currentOffset_ = SCROLL_FLOAT_100;
    pattern->scrollableDistance_ = SCROLL_FLOAT_100;
    pattern->viewPortLength_ = SCROLL_FLOAT_100;
    auto ret = callback(SCROLL_DOUBLE_10, SCROLL_FROM_JUMP);
    EXPECT_EQ(ret, false);

    pattern->currentOffset_ = SCROLL_FLOAT_100;
    pattern->scrollableDistance_ = SCROLL_FLOAT_NEGATIVE_100;
    pattern->viewPortLength_ = SCROLL_FLOAT_100;
    ret = callback(SCROLL_DOUBLE_NEGATIVE_10, SCROLL_FROM_ROTATE);
    EXPECT_EQ(ret, false);

    pattern->currentOffset_ = SCROLL_FLOAT_NEGATIVE_200;
    pattern->scrollableDistance_ = SCROLL_FLOAT_100;
    pattern->viewPortLength_ = SCROLL_FLOAT_100;
    ret = callback(SCROLL_DOUBLE_10, SCROLL_FROM_BAR);
    EXPECT_EQ(ret, true);

    /**
     * @tc.steps: step6. Call the ResetPosition function.
     * @tc.expected: step6. Check whether relevant parameters are correct.
     */
    pattern->ResetPosition();
    EXPECT_EQ(pattern->currentOffset_, 0.0f);
    EXPECT_EQ(pattern->lastOffset_, 0.0f);
}

/**
 * @tc.name: ScrollTest007
 * @tc.desc: When setting a fixed length and width, verify the related functions in the scroll pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties.
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::NONE);
    scrollModel.SetDisplayMode(0);
    scrollModel.SetScrollBarWidth(SCROLL_BAR_WIDTH);
    scrollModel.SetScrollBarColor(SCROLL_BAR_COLOR);
    scrollModel.SetEdgeEffect(EdgeEffect::SPRING);
    scrollModel.SetScrollBarProxy(scrollModel.CreateScrollBarProxy());
    auto controller = scrollModel.GetOrCreateController();
    EXPECT_NE(controller, nullptr);

    /**
     * @tc.steps: step2. Get scroll frameNode to create scroll layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. Create grid layoutWrapper and add it to scroll frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SCROLL_CHILD_SIZE);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(childFrameNode, childGeometryNode, childLayoutProperty);
    layoutWrapper.AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Get scroll pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step4. related function is called.
     */
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    EXPECT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    scrollLayoutAlgorithm->Measure(&layoutWrapper);
    scrollLayoutAlgorithm->Layout(&layoutWrapper);

    /**
     * @tc.steps: step5. When Axis is NONE and set scrollProxy, verify the callback function.
     * @tc.expected: step5. Check whether the return value is as expected.
     */
    auto callback = pattern->scrollableEvent_->GetScrollPositionCallback();
    EXPECT_NE(callback, nullptr);
    auto ret = callback(1.0, SCROLL_FROM_BAR);
    EXPECT_EQ(ret, false);
    auto scrollableNode = pattern->scrollBarProxy_->scrollableNodes_.back();
    ret = scrollableNode.onPositionChanged(1.0, SCROLL_FROM_BAR);
    EXPECT_EQ(ret, false);

    /**
     * @tc.steps: step6. When Axis is NONE, verify the correlation function in positionController.
     * @tc.expected: step6. Check whether the return value and related parameters are correct.
     */
    auto positionController = AceType::DynamicCast<ScrollPositionController>(controller);
    EXPECT_NE(positionController, nullptr);
    positionController->JumpTo(0, SCROLL_FROM_START);
    positionController->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_EQ(pattern->animator_, nullptr);
    int32_t temp = 0;
    auto func = [&temp]() { temp = 1.0; };
    pattern->AnimateTo(0.0f, 0.0f, Curves::LINEAR, true, func);
    pattern->animator_->NotifyStopListener();
    EXPECT_EQ(temp, 1.0);
    positionController->ScrollPage(false, false);
    positionController->ScrollBy(0, 0, false);
    auto axis = positionController->GetScrollDirection();
    EXPECT_EQ(axis, Axis::NONE);
    auto position = positionController->GetCurrentPosition();
    EXPECT_EQ(position, 0.0f);
    auto offset = positionController->GetCurrentOffset();
    EXPECT_EQ(offset, Offset::Zero());
    Dimension dimension(0, DimensionUnit::VP);
    auto animate = positionController->AnimateTo(dimension, 0.0f, Curves::LINEAR);
    EXPECT_EQ(animate, false);
}

/**
 * @tc.name: ScrollTest008
 * @tc.desc: When setting a fixed length and width, verify the related callback functions in the scroll pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties and event.
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::HORIZONTAL);
    scrollModel.SetDisplayMode(1);
    scrollModel.SetScrollBarWidth(SCROLL_BAR_WIDTH);
    scrollModel.SetScrollBarColor(SCROLL_BAR_COLOR);
    scrollModel.SetEdgeEffect(EdgeEffect::SPRING);
    scrollModel.SetScrollBarProxy(scrollModel.CreateScrollBarProxy());
    Dimension dim1(0, DimensionUnit::VP);
    Dimension dim2(0, DimensionUnit::VP);
    auto onScroll = [&dim1, &dim2](Dimension dimension1, Dimension dimension2) {
        dim1 = dimension1;
        dim2 = dimension2;
    };
    scrollModel.SetOnScroll(std::move(onScroll));
    auto onScrollBegin = [](Dimension /* dimension1 */, Dimension /* dimension2 */) { return ScrollInfo {}; };
    scrollModel.SetOnScrollBegin(std::move(onScrollBegin));
    auto onScrollEnd = []() {};
    scrollModel.SetOnScrollEnd(std::move(onScrollEnd));
    ScrollEdge scrollEdge = ScrollEdge::BOTTOM;
    auto onScrollEdge = [&scrollEdge](ScrollEdge edge) { scrollEdge = edge; };
    scrollModel.SetOnScrollEdge(std::move(onScrollEdge));

    /**
     * @tc.steps: step2. Get scroll frameNode to create scroll layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. Create grid layoutWrapper and add it to scroll frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SCROLL_CHILD_SIZE);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(childFrameNode, childGeometryNode, childLayoutProperty);
    layoutWrapper.AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Get scroll pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step4. related function is called.
     */
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    EXPECT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    scrollLayoutAlgorithm->Measure(&layoutWrapper);
    scrollLayoutAlgorithm->Layout(&layoutWrapper);
    pattern->OnModifyDone();

    /**
     * @tc.steps: step5. When Axis is HORIZONTAL, verify the set callback function.
     * @tc.expected: step5. Check whether the return value is as expected.
     */
    pattern->HandleCrashTop();
    EXPECT_EQ(scrollEdge, ScrollEdge::LEFT);
    pattern->HandleCrashBottom();
    EXPECT_EQ(scrollEdge, ScrollEdge::RIGHT);
    pattern->HandleScrollPosition(1.0f, SCROLL_FROM_BAR);
    auto scrollVp = Dimension(1.0, DimensionUnit::PX).ConvertToVp();
    EXPECT_EQ(dim1, Dimension(scrollVp, DimensionUnit::VP));
}

/**
 * @tc.name: ScrollTest009
 * @tc.desc: When setting a fixed length and width, verify the related callback functions in the scroll pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties and event.
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::VERTICAL);
    scrollModel.SetDisplayMode(1);
    scrollModel.SetScrollBarWidth(SCROLL_BAR_WIDTH);
    scrollModel.SetScrollBarColor(SCROLL_BAR_COLOR);
    scrollModel.SetEdgeEffect(EdgeEffect::SPRING);
    Dimension dim1(0, DimensionUnit::VP);
    Dimension dim2(0, DimensionUnit::VP);
    auto onScroll = [&dim1, &dim2](Dimension dimension1, Dimension dimension2) {
        dim1 = dimension1;
        dim2 = dimension2;
    };
    scrollModel.SetOnScroll(std::move(onScroll));
    auto onScrollBegin = [](Dimension /* dimension1 */, Dimension /* dimension2 */) { return ScrollInfo {}; };
    scrollModel.SetOnScrollBegin(std::move(onScrollBegin));
    auto onScrollEnd = []() {};
    scrollModel.SetOnScrollEnd(std::move(onScrollEnd));
    ScrollEdge scrollEdge = ScrollEdge::BOTTOM;
    auto onScrollEdge = [&scrollEdge](ScrollEdge edge) { scrollEdge = edge; };
    scrollModel.SetOnScrollEdge(std::move(onScrollEdge));

    /**
     * @tc.steps: step2. Get scroll frameNode to create scroll layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. Create grid layoutWrapper and add it to scroll frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SCROLL_CHILD_SIZE);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(childFrameNode, childGeometryNode, childLayoutProperty);
    layoutWrapper.AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Get scroll pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step4. related function is called.
     */
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    EXPECT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    scrollLayoutAlgorithm->Measure(&layoutWrapper);
    scrollLayoutAlgorithm->Layout(&layoutWrapper);
    pattern->OnModifyDone();

    /**
     * @tc.steps: step5. When Axis is VERTICAL, verify the set callback function.
     * @tc.expected: step5. Check whether the return value is as expected.
     */
    pattern->HandleCrashTop();
    EXPECT_EQ(scrollEdge, ScrollEdge::TOP);
    pattern->HandleCrashBottom();
    EXPECT_EQ(scrollEdge, ScrollEdge::BOTTOM);
    pattern->HandleScrollPosition(1.0f, SCROLL_FROM_BAR);
    auto scrollVp = Dimension(1.0, DimensionUnit::PX).ConvertToVp();
    EXPECT_EQ(dim2, Dimension(scrollVp, DimensionUnit::VP));
}

/**
 * @tc.name: ScrollTest0010
 * @tc.desc: When setting a fixed length and width, verify the related callback functions in the scroll pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties and event.
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::VERTICAL);
    scrollModel.SetDisplayMode(1);
    scrollModel.SetScrollBarWidth(SCROLL_BAR_WIDTH);
    scrollModel.SetScrollBarColor(SCROLL_BAR_COLOR);
    scrollModel.SetEdgeEffect(EdgeEffect::SPRING);
    auto controller = scrollModel.GetOrCreateController();
    EXPECT_NE(controller, nullptr);

    /**
     * @tc.steps: step2. Get scroll frameNode to create scroll layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. Create grid layoutWrapper and add it to scroll frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SCROLL_CHILD_SIZE);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(childFrameNode, childGeometryNode, childLayoutProperty);
    layoutWrapper.AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Get scroll pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step4. related function is called.
     */
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    EXPECT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    scrollLayoutAlgorithm->Measure(&layoutWrapper);
    scrollLayoutAlgorithm->Layout(&layoutWrapper);

    /**
     * @tc.steps: step5. When Axis is VERTICAL, verify the correlation function in positionController.
     * @tc.expected: step5. Check whether the return value and related parameters are correct.
     */
    auto positionController = AceType::DynamicCast<ScrollPositionController>(controller);
    EXPECT_NE(positionController, nullptr);
    positionController->JumpTo(0, SCROLL_FROM_START);
    positionController->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    positionController->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, true);
    pattern->currentOffset_ = SCROLL_FLOAT_100;
    positionController->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_NE(pattern->animator_, nullptr);
    pattern->CreateOrStopAnimator();
    EXPECT_EQ(pattern->animator_->status_, Animator::Status::STOPPED);
    pattern->animator_->NotifyStopListener();
    pattern->viewPortLength_ = 1.0f;
    positionController->ScrollPage(true, false);
    pattern->animator_->status_ = Animator::Status::IDLE;
    positionController->ScrollPage(false, false);
    pattern->animator_ = nullptr;
    positionController->ScrollPage(false, false);
    positionController->ScrollBy(0, 0, false);
    auto axis = positionController->GetScrollDirection();
    EXPECT_EQ(axis, Axis::VERTICAL);
    auto position = positionController->GetCurrentPosition();
    EXPECT_EQ(position, SCROLL_FLOAT_98);
    auto offset = positionController->GetCurrentOffset();
    EXPECT_EQ(offset, Offset::Zero());
    Dimension dimension(0, DimensionUnit::VP);
    auto animate = positionController->AnimateTo(dimension, 0.0f, Curves::LINEAR);
    EXPECT_EQ(animate, true);
}

/**
 * @tc.name: ScrollTest0011
 * @tc.desc: When setting a fixed length and width, verify the related callback functions in the scroll pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest0011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties and event.
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::VERTICAL);
    scrollModel.SetDisplayMode(1);
    scrollModel.SetScrollBarWidth(SCROLL_BAR_WIDTH);
    scrollModel.SetScrollBarColor(SCROLL_BAR_COLOR);

    /**
     * @tc.steps: step2. Get scroll frameNode to create scroll layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. Create grid layoutWrapper and add it to scroll frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SCROLL_CHILD_SIZE);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(childFrameNode, childGeometryNode, childLayoutProperty);
    layoutWrapper.AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Get scroll pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step4. related function is called.
     */
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    EXPECT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    scrollLayoutAlgorithm->Measure(&layoutWrapper);
    scrollLayoutAlgorithm->Layout(&layoutWrapper);

    /**
     * @tc.steps: step5. Set ScrollSpringEffect and call relevant callback functions.
     * @tc.expected: step5. Check whether the return value is correct.
     */
    pattern->SetEdgeEffect(EdgeEffect::SPRING);
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern->GetScrollEdgeEffect();
    EXPECT_NE(scrollEdgeEffect, nullptr);
    auto springEffect = AceType::DynamicCast<ScrollSpringEffect>(scrollEdgeEffect);
    EXPECT_NE(springEffect, nullptr);
    pattern->currentOffset_ = SCROLL_FLOAT_100;
    pattern->scrollableDistance_ = SCROLL_FLOAT_100;
    auto isOutBoundary = springEffect->outBoundaryCallback_();
    EXPECT_EQ(isOutBoundary, true);
    auto currentPosition = scrollEdgeEffect->currentPositionCallback_();
    EXPECT_EQ(currentPosition, SCROLL_DOUBLE_100);

    /**
     * @tc.steps: step6. When direction is the default value, call the relevant callback function.
     * @tc.expected: step6. Check whether the return value is correct.
     */
    auto leading = scrollEdgeEffect->leadingCallback_();
    EXPECT_EQ(leading, SCROLL_FLOAT_NEGATIVE_100);
    auto trailing = scrollEdgeEffect->trailingCallback_();
    EXPECT_EQ(trailing, 0.0);
    auto initLeading = scrollEdgeEffect->initLeadingCallback_();
    EXPECT_EQ(initLeading, SCROLL_FLOAT_NEGATIVE_100);
    auto initTrailing = scrollEdgeEffect->initTrailingCallback_();
    EXPECT_EQ(initTrailing, 0.0);

    /**
     * @tc.steps: step7. When direction is ROW_REVERSE, call the relevant callback function.
     * @tc.expected: step7. Check whether the return value is correct.
     */
    pattern->direction_ = FlexDirection::ROW_REVERSE;
    leading = scrollEdgeEffect->leadingCallback_();
    EXPECT_EQ(leading, 0.0);
    trailing = scrollEdgeEffect->trailingCallback_();
    EXPECT_EQ(trailing, SCROLL_FLOAT_100);
    initLeading = scrollEdgeEffect->initLeadingCallback_();
    EXPECT_EQ(initLeading, 0.0);
    initTrailing = scrollEdgeEffect->initTrailingCallback_();
    EXPECT_EQ(initTrailing, SCROLL_FLOAT_100);

    /**
     * @tc.steps: step8. When direction is COLUMN_REVERSE, call the relevant callback function.
     * @tc.expected: step8. Check whether the return value is correct.
     */
    pattern->direction_ = FlexDirection::COLUMN_REVERSE;
    leading = scrollEdgeEffect->leadingCallback_();
    EXPECT_EQ(leading, 0.0);
    trailing = scrollEdgeEffect->trailingCallback_();
    EXPECT_EQ(trailing, SCROLL_FLOAT_100);
    initLeading = scrollEdgeEffect->initLeadingCallback_();
    EXPECT_EQ(initLeading, 0.0);
    initTrailing = scrollEdgeEffect->initTrailingCallback_();
    EXPECT_EQ(initTrailing, SCROLL_FLOAT_100);
}

/**
 * @tc.name: ScrollTest0012
 * @tc.desc: When setting a fixed length and width, verify the related functions in the scroll pattern.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest0012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties and event.
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::VERTICAL);
    scrollModel.SetDisplayMode(1);
    scrollModel.SetScrollBarWidth(SCROLL_BAR_WIDTH);
    scrollModel.SetScrollBarColor(SCROLL_BAR_COLOR);

    /**
     * @tc.steps: step2. Get scroll frameNode to create scroll layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. Create grid layoutWrapper and add it to scroll frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SCROLL_CHILD_SIZE);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(childFrameNode, childGeometryNode, childLayoutProperty);
    layoutWrapper.AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Get scroll pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step4. related function is called.
     */
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    EXPECT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    scrollLayoutAlgorithm->Measure(&layoutWrapper);
    scrollLayoutAlgorithm->Layout(&layoutWrapper);

    /**
     * @tc.steps: step5. Verify the ValidateOffset function.
     * @tc.expected: step5. Check whether relevant parameters are correct.
     */
    pattern->scrollableDistance_ = -1.0f;
    pattern->currentOffset_ = 1.0f;
    pattern->ValidateOffset(SCROLL_FROM_BAR);
    EXPECT_EQ(pattern->currentOffset_, 1.0f);
    pattern->scrollableDistance_ = SCROLL_FLOAT_100;
    pattern->ValidateOffset(SCROLL_FROM_JUMP);
    EXPECT_EQ(pattern->currentOffset_, 0.0f);
    pattern->ValidateOffset(SCROLL_FROM_BAR);
    EXPECT_EQ(pattern->currentOffset_, 0.0f);
    pattern->ValidateOffset(SCROLL_FROM_ROTATE);
    EXPECT_EQ(pattern->currentOffset_, 0.0f);

    /**
     * @tc.steps: step6. Set ScrollFadeEffect and call relevant callback functions.
     * @tc.expected: step6. Check whether the return value is correct.
     */
    pattern->SetEdgeEffect(EdgeEffect::FADE);
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern->GetScrollEdgeEffect();
    EXPECT_NE(scrollEdgeEffect, nullptr);
    pattern->currentOffset_ = SCROLL_FLOAT_100;
    pattern->scrollableDistance_ = SCROLL_FLOAT_100;
    auto scrollFade = AceType::DynamicCast<ScrollFadeEffect>(scrollEdgeEffect);
    EXPECT_NE(scrollFade, nullptr);
    scrollFade->handleOverScrollCallback_();
    EXPECT_NE(scrollFade->fadeController_, nullptr);
    pattern->SetEdgeEffect(EdgeEffect::NONE);
    EXPECT_EQ(pattern->scrollEffect_, nullptr);
}

/**
 * @tc.name: ScrollTest0013
 * @tc.desc: Test the correlation function in ScrollSpringEffect under different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest0013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties and event.
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::HORIZONTAL);
    scrollModel.SetDisplayMode(3);
    scrollModel.SetScrollBarWidth(SCROLL_BAR_WIDTH);
    scrollModel.SetScrollBarColor(SCROLL_BAR_COLOR);

    /**
     * @tc.steps: step2. Get scroll frameNode to create scroll layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. Create grid layoutWrapper and add it to scroll frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SCROLL_CHILD_SIZE);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(childFrameNode, childGeometryNode, childLayoutProperty);
    layoutWrapper.AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Get scroll pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step4. related function is called.
     */
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    EXPECT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    scrollLayoutAlgorithm->Measure(&layoutWrapper);
    scrollLayoutAlgorithm->Layout(&layoutWrapper);

    /**
     * @tc.steps: step5. Verify the ValidateOffset function.
     * @tc.expected: step5. Check whether relevant parameters are correct.
     */
    pattern->currentOffset_ = 1.0f;
    pattern->scrollableDistance_ = SCROLL_FLOAT_100;
    pattern->direction_ = FlexDirection::ROW_REVERSE;
    pattern->ValidateOffset(SCROLL_FROM_JUMP);
    EXPECT_EQ(pattern->currentOffset_, 1.0f);
    pattern->ValidateOffset(SCROLL_FROM_BAR);
    EXPECT_EQ(pattern->currentOffset_, 1.0f);
    pattern->ValidateOffset(SCROLL_FROM_ROTATE);
    EXPECT_EQ(pattern->currentOffset_, 1.0f);
    pattern->direction_ = FlexDirection::COLUMN;
    pattern->ValidateOffset(SCROLL_FROM_JUMP);
    EXPECT_EQ(pattern->currentOffset_, 0.0f);

    /**
     * @tc.steps: step6. Verify related functions in ScrollSpringEffect.
     * @tc.expected: step6. Check whether relevant parameters are correct.
     */
    pattern->SetEdgeEffect(EdgeEffect::SPRING);
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern->GetScrollEdgeEffect();
    EXPECT_NE(scrollEdgeEffect, nullptr);
    scrollEdgeEffect->ProcessScrollOver(0.0);
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    EXPECT_NE(scrollable, nullptr);
    scrollable->controller_ = AceType::MakeRefPtr<Animator>();
    scrollable->springController_ = AceType::MakeRefPtr<Animator>();
    scrollEdgeEffect->SetScrollable(scrollable);
    auto scrollSpringEffect = AceType::DynamicCast<ScrollSpringEffect>(scrollEdgeEffect);
    EXPECT_NE(scrollSpringEffect, nullptr);
    EXPECT_NE(scrollSpringEffect->scrollable_, nullptr);
    scrollSpringEffect->InitialEdgeEffect();
    scrollSpringEffect->scrollable_->scrollOverCallback_(0.0);
    EXPECT_NE(scrollSpringEffect->scrollable_->controller_, nullptr);
    EXPECT_NE(scrollSpringEffect->scrollable_->springController_, nullptr);
}

/**
 * @tc.name: ScrollTest0014
 * @tc.desc: Test UpdateScrollBarRegion function in ScrollBar under different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest0014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When the ShapeMode is RECT and DisplayMode is LEFT, verify the UpdateScrollBarRegion function.
     * @tc.expected: step1. Check whether relevant parameters are correct.
     */
    auto scrollBar = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
    EXPECT_NE(scrollBar, nullptr);
    scrollBar->shapeMode_ = ShapeMode::RECT;
    scrollBar->positionMode_ = PositionMode::LEFT;
    scrollBar->UpdateScrollBarRegion(SCROLL_OFFSET_ZERO, SCROLL_SIZE_100, SCROLL_OFFSET_ONE, 1.0);
    auto barRect = Rect(0.0, 0.0, 0.0, 100.0) + SCROLL_OFFSET_ZERO;
    EXPECT_EQ(scrollBar->barRect_, barRect);
    EXPECT_EQ(scrollBar->activeRect_, SCROLLBAR_RECT_LEFT);
    EXPECT_EQ(scrollBar->touchRegion_, SCROLLBAR_RECT_LEFT);

    /**
     * @tc.steps: step2. When the ShapeMode is RECT and DisplayMode is BOTTOM, verify the UpdateScrollBarRegion
     *            function.
     * @tc.expected: step2. Check whether relevant parameters are correct.
     */
    scrollBar->positionModeUpdate_ = true;
    scrollBar->positionMode_ = PositionMode::BOTTOM;
    scrollBar->SetOutBoundary(1.0);
    scrollBar->UpdateScrollBarRegion(SCROLL_OFFSET_ZERO, SCROLL_SIZE_100, SCROLL_OFFSET_ONE, 1.0);
    barRect = Rect(0.0, 100.0, 100.0, 0.0) + SCROLL_OFFSET_ZERO;
    EXPECT_EQ(scrollBar->barRect_, barRect);
    EXPECT_EQ(scrollBar->activeRect_, SCROLLBAR_RECT_BOTTOM);
    EXPECT_EQ(scrollBar->touchRegion_, SCROLLBAR_RECT_BOTTOM);

    /**
     * @tc.steps: step3. When the ShapeMode is RECT and DisplayMode is RIGHT, verify the UpdateScrollBarRegion function.
     * @tc.expected: step3. Check whether relevant parameters are correct.
     */
    scrollBar->positionModeUpdate_ = true;
    scrollBar->positionMode_ = PositionMode::RIGHT;
    scrollBar->UpdateScrollBarRegion(SCROLL_OFFSET_ZERO, SCROLL_SIZE_100, SCROLL_OFFSET_ONE, 1.0);
    barRect = Rect(100.0, 0.0, 0.0, 100.0) + SCROLL_OFFSET_ZERO;
    EXPECT_EQ(scrollBar->barRect_, barRect);
    EXPECT_EQ(scrollBar->activeRect_, SCROLLBAR_RECT_RIGHT);
    EXPECT_EQ(scrollBar->touchRegion_, SCROLLBAR_RECT_RIGHT);

    /**
     * @tc.steps: step4. When the ShapeMode is ROUND and DisplayMode is LEFT, verify the UpdateScrollBarRegion function.
     * @tc.expected: step4. Check whether relevant parameters are correct.
     */
    scrollBar->positionModeUpdate_ = true;
    scrollBar->shapeMode_ = ShapeMode::ROUND;
    scrollBar->positionMode_ = PositionMode::LEFT;
    scrollBar->UpdateScrollBarRegion(SCROLL_OFFSET_ZERO, SCROLL_SIZE_100, SCROLL_OFFSET_ONE, 1.0);
    EXPECT_EQ(scrollBar->trickStartAngle_, 150);
    EXPECT_EQ(scrollBar->trickSweepAngle_, -6000);

    /**
     * @tc.steps: step5. When the ShapeMode is ROUND and DisplayMode is RIGHT, verify the UpdateScrollBarRegion
     *                   function.
     * @tc.expected: step5. Check whether relevant parameters are correct.
     */
    scrollBar->positionModeUpdate_ = true;
    scrollBar->positionMode_ = PositionMode::RIGHT;
    scrollBar->UpdateScrollBarRegion(SCROLL_OFFSET_ZERO, SCROLL_SIZE_100, SCROLL_OFFSET_ONE, 1.0);
    EXPECT_EQ(scrollBar->trickStartAngle_, 30);
    EXPECT_EQ(scrollBar->trickSweepAngle_, 6000);

    /**
     * @tc.steps: step6. When the ShapeMode is ROUND and DisplayMode is LEFT, verify the UpdateScrollBarRegion function.
     * @tc.expected: step6. Check whether relevant parameters are correct.
     */
    scrollBar->positionModeUpdate_ = true;
    scrollBar->positionMode_ = PositionMode::LEFT;
    scrollBar->bottomAngle_ = SCROLL_FLOAT_50;
    scrollBar->topAngle_ = SCROLL_DOUBLE_100;
    scrollBar->SetOutBoundary(1.0);
    scrollBar->UpdateScrollBarRegion(SCROLL_OFFSET_ZERO, SCROLL_SIZE_100, SCROLL_OFFSET_ONE, SCROLL_DOUBLE_200);
    EXPECT_EQ(scrollBar->trickStartAngle_, -155);
    EXPECT_EQ(scrollBar->trickSweepAngle_, -10);
}

/**
 * @tc.name: ScrollTest0015
 * @tc.desc: Test the correlation function in ScrollFadeEffect under different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest0015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create scroll and initialize related properties and event.
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetAxis(Axis::HORIZONTAL);
    scrollModel.SetDisplayMode(2);
    scrollModel.SetScrollBarWidth(SCROLL_BAR_WIDTH);
    scrollModel.SetScrollBarColor(SCROLL_BAR_COLOR);

    /**
     * @tc.steps: step2. Get scroll frameNode to create scroll layoutWrapper.
     * @tc.expected: step2. related function is called.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(geometryNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize = CONTAINER_SIZE;
    layoutConstraint.selfIdealSize.SetSize(CONTAINER_SIZE);
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();
    LayoutWrapper layoutWrapper = LayoutWrapper(frameNode, geometryNode, layoutProperty);

    /**
     * @tc.steps: step3. Create grid layoutWrapper and add it to scroll frameNode layoutWrapper.
     * @tc.expected: step3. related function is called.
     */
    auto childFrameNode = FrameNode::CreateFrameNode(V2::GRID_ITEM_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(childFrameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(childFrameNode);
    RefPtr<GeometryNode> childGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SCROLL_CHILD_SIZE);
    RefPtr<LayoutProperty> childLayoutProperty = childFrameNode->GetLayoutProperty();
    EXPECT_NE(childLayoutProperty, nullptr);
    RefPtr<LayoutWrapper> childLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(childFrameNode, childGeometryNode, childLayoutProperty);
    layoutWrapper.AppendChild(childLayoutWrapper);

    /**
     * @tc.steps: step4. Get scroll pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step4. related function is called.
     */
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    EXPECT_NE(pattern, nullptr);
    auto scrollLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    EXPECT_NE(scrollLayoutAlgorithm, nullptr);
    scrollLayoutAlgorithm->Measure(&layoutWrapper);
    scrollLayoutAlgorithm->Layout(&layoutWrapper);

    /**
     * @tc.steps: step5. Create ScrollFadeEffect and  verify related callback functions.
     * @tc.expected: step5. Check whether relevant parameters are correct.
     */
    pattern->SetEdgeEffect(EdgeEffect::FADE);
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern->GetScrollEdgeEffect();
    EXPECT_NE(scrollEdgeEffect, nullptr);
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    EXPECT_NE(scrollable, nullptr);
    scrollable->controller_ = AceType::MakeRefPtr<Animator>();
    scrollable->springController_ = AceType::MakeRefPtr<Animator>();
    scrollEdgeEffect->SetScrollable(scrollable);
    auto scrollFadeEffect = AceType::DynamicCast<ScrollFadeEffect>(scrollEdgeEffect);
    scrollEdgeEffect->InitialEdgeEffect();
    EXPECT_NE(scrollFadeEffect->scrollable_, nullptr);
    EXPECT_NE(scrollFadeEffect, nullptr);
    EXPECT_NE(scrollFadeEffect->fadeController_, nullptr);
    EXPECT_NE(scrollFadeEffect->fadePainter_, nullptr);
    EXPECT_EQ(scrollFadeEffect->fadeColor_, Color::GRAY);
    scrollFadeEffect->fadeController_->callback_(1.0f, 1.0f);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->opacity_, 1.0f);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->scaleFactor_, 1.0f);

    /**
     * @tc.steps: step6. Verify the HandleOverScroll function in ScrollFadeEffect under different parameters.
     * @tc.expected: step6. Check whether relevant parameters are correct.
     */
    scrollFadeEffect->HandleOverScroll(Axis::VERTICAL, 0.0f, SCROLL_VIEW_PORT);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::UP);
    scrollFadeEffect->HandleOverScroll(Axis::VERTICAL, -1.0f, SCROLL_VIEW_PORT);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::UP);
    scrollFadeEffect->HandleOverScroll(Axis::VERTICAL, 1.0f, SCROLL_VIEW_PORT);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::DOWN);
    scrollFadeEffect->HandleOverScroll(Axis::HORIZONTAL, -1.0f, SCROLL_VIEW_PORT);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::LEFT);
    scrollFadeEffect->HandleOverScroll(Axis::HORIZONTAL, 1.0f, SCROLL_VIEW_PORT);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::RIGHT);
    scrollFadeEffect->fadeController_ = nullptr;
    scrollFadeEffect->scrollable_->currentVelocity_ = 1.0;
    scrollFadeEffect->HandleOverScroll(Axis::VERTICAL, 1.0f, SCROLL_VIEW_PORT);
    EXPECT_NE(scrollFadeEffect->fadeController_, nullptr);
    scrollFadeEffect->SetPaintDirection(Axis::HORIZONTAL, 0.0f);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::DOWN);

    /**
     * @tc.steps: step7. Verify the CalculateOverScroll function in ScrollFadeEffect under different parameters.
     * @tc.expected: step7. Check whether the return value is correct.
     */
    pattern->currentOffset_ = SCROLL_FLOAT_100;
    pattern->scrollableDistance_ = -1.0f;
    auto ret = scrollFadeEffect->CalculateOverScroll(-1.0, true);
    EXPECT_EQ(ret, SCROLL_DOUBLE_NEGATIVE_99);
    pattern->currentOffset_ = SCROLL_FLOAT_NEGATIVE_100;
    pattern->scrollableDistance_ = -1.0f;
    ret = scrollFadeEffect->CalculateOverScroll(1.0, true);
    EXPECT_EQ(ret, SCROLL_DOUBLE_99);
    pattern->currentOffset_ = SCROLL_FLOAT_100;
    pattern->scrollableDistance_ = -1.0f;
    ret = scrollFadeEffect->CalculateOverScroll(1.0, true);
    EXPECT_EQ(ret, SCROLL_DOUBLE_NEGATIVE_100);
    pattern->currentOffset_ = SCROLL_FLOAT_NEGATIVE_100;
    pattern->scrollableDistance_ = 1.0f;
    ret = scrollFadeEffect->CalculateOverScroll(-1.0, true);
    EXPECT_EQ(ret, SCROLL_DOUBLE_99);
    pattern->currentOffset_ = SCROLL_FLOAT_NEGATIVE_100;
    pattern->scrollableDistance_ = 1.0f;
    ret = scrollFadeEffect->CalculateOverScroll(-1.0, false);
    EXPECT_EQ(ret, 0.0);
}

/**
 * @tc.name: ScrollTest0016
 * @tc.desc: Test related functions in ScrollFadeController under different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollTestNg, ScrollTest0016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ScrollFadeController and set callback function.
     */
    auto fadeController = AceType::MakeRefPtr<ScrollFadeController>();
    EXPECT_NE(fadeController, nullptr);
    double param1 = SCROLL_DOUBLE_10;
    double param2 = SCROLL_DOUBLE_NEGATIVE_10;
    auto callback = [&param1, &param2](double parameter1, double parameter2) {
        param1 = parameter1;
        param2 = parameter2;
    };
    fadeController->SetCallback(callback);

    /**
     * @tc.steps: step2. Verify the ProcessAbsorb function and callback function in fadeController.
     * @tc.expected: step2. Check whether relevant parameters are correct.
     */
    fadeController->ProcessAbsorb(SCROLL_DOUBLE_100);
    EXPECT_EQ(fadeController->opacityFloor_, 0.3);
    EXPECT_EQ(fadeController->opacityCeil_, 0.3);
    EXPECT_EQ(fadeController->scaleSizeFloor_, 0.0);
    EXPECT_EQ(fadeController->scaleSizeCeil_, 0.0325);
    EXPECT_EQ(fadeController->state_, OverScrollState::ABSORB);
    fadeController->decele_->NotifyListener(SCROLL_DOUBLE_100);
    EXPECT_EQ(fadeController->opacity_, 0.3);
    EXPECT_EQ(fadeController->scaleSize_, 3.25);
    EXPECT_EQ(param1, fadeController->opacity_);
    EXPECT_EQ(param2, fadeController->scaleSize_);

    /**
     * @tc.steps: step2. When OverScrollState is ABSORB, call the callback function in fadeController.
     * @tc.expected: step2. Check whether relevant parameters are correct.
     */
    fadeController->controller_->NotifyStopListener();
    EXPECT_EQ(fadeController->opacityCeil_, 0.0);
    EXPECT_EQ(fadeController->scaleSizeCeil_, 0.0);
    EXPECT_EQ(fadeController->state_, OverScrollState::RECEDE);

    /**
     * @tc.steps: step3. When OverScrollState is RECEDE, call the ProcessRecede function and callback function in
     *                   fadeController.
     * @tc.expected: step3. Check whether relevant parameters are correct.
     */
    fadeController->ProcessRecede(SCROLL_INT32_1000);
    fadeController->controller_->NotifyStopListener();
    EXPECT_EQ(fadeController->state_, OverScrollState::IDLE);
    EXPECT_EQ(fadeController->pullDistance_, 0.0);
    fadeController->ProcessRecede(SCROLL_INT32_1000);
    EXPECT_EQ(fadeController->pullDistance_, 0.0);

    /**
     * @tc.steps: step4. When OverScrollState is IDLE, call the ProcessPull function and callback function in
     *                   fadeController.
     * @tc.expected: step4. Check whether relevant parameters are correct.
     */
    fadeController->ProcessPull(1.0, 1.0, 1.0);
    EXPECT_EQ(fadeController->opacityFloor_, 0.3);
    EXPECT_EQ(fadeController->opacityCeil_, 0.5);
    EXPECT_EQ(fadeController->scaleSizeFloor_, 3.25);
    EXPECT_EQ(fadeController->scaleSizeCeil_, 3.25);
    EXPECT_EQ(fadeController->state_, OverScrollState::PULL);

    /**
     * @tc.steps: step5. When OverScrollState is PULL, call the ProcessAbsorb function and callback function in
     *                   fadeController.
     * @tc.expected: step5. Check whether relevant parameters are correct.
     */
    fadeController->ProcessAbsorb(SCROLL_DOUBLE_NEGATIVE_10);
    fadeController->decele_->NotifyListener(SCROLL_DOUBLE_100);
    EXPECT_EQ(fadeController->opacity_, 20.3);
    EXPECT_EQ(fadeController->scaleSize_, 3.25);
    fadeController->controller_->NotifyStopListener();
    EXPECT_EQ(fadeController->state_, OverScrollState::PULL);
    fadeController->ProcessAbsorb(SCROLL_DOUBLE_100);
    fadeController->ProcessPull(1.0, 1.0, 1.0);
    fadeController->decele_->NotifyListener(SCROLL_DOUBLE_100);
    EXPECT_EQ(param1, 20.3);
    EXPECT_EQ(param2, 3.25);
}
} // namespace OHOS::Ace::NG