/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_pattern.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#undef protected
#undef private

#include "test/unittest/core/pattern/dynamiclayout/mock_layout_wrapper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TEST_TAG = "LazyDynamicLayout";
constexpr int32_t TEST_PARENT_NODE_ID = -100;
constexpr int32_t TEST_HOST_NODE_ID = -101;
constexpr int32_t TEST_CHILD_NODE_ID = -102;
constexpr int32_t TEST_CHILD_COUNT = 2;

struct LazyDynamicMeasureState {
    int32_t count = 0;
    bool sawEstimateReference = false;
    std::optional<ViewPosReference> measuredReference;
};

struct LazyDynamicLayoutTestContext {
    RefPtr<FrameNode> parent;
    RefPtr<FrameNode> host;
    RefPtr<LayoutWrapperNode> wrapper;
    RefPtr<LayoutProperty> layoutProperty;
    RefPtr<LazyDynamicLayoutAlgorithm> algorithm;
    LayoutConstraintF constraint;
};

void SetMeasureCallback(
    const RefPtr<LazyCustomLayoutAlgorithmParam>& params, LazyDynamicMeasureState& state)
{
    params->SetOnMeasureSize([&state](LayoutWrapper* wrapper) {
        ++state.count;
        auto property = wrapper ? wrapper->GetLayoutProperty() : nullptr;
        auto contentConstraint = property ? property->GetContentLayoutConstraint() : std::nullopt;
        state.measuredReference = contentConstraint.has_value() ? contentConstraint->viewPosRef : std::nullopt;
        state.sawEstimateReference = state.measuredReference.has_value() &&
            NearEqual(state.measuredReference->viewPosStart, 0.0f) &&
            NearEqual(state.measuredReference->viewPosEnd, 1.0f);
    });
}

LazyDynamicLayoutTestContext CreateLazyDynamicLayoutTestContext(
    const RefPtr<LazyCustomLayoutAlgorithmParam>& params)
{
    LazyDynamicLayoutTestContext context;
    context.parent = FrameNode::CreateFrameNode(
        V2::LIST_ETS_TAG, TEST_PARENT_NODE_ID, AceType::MakeRefPtr<ListPattern>());
    context.host = FrameNode::CreateFrameNode(
        TEST_TAG, TEST_HOST_NODE_ID, AceType::MakeRefPtr<LazyDynamicLayoutPattern>(params));
    if (!context.parent || !context.host) {
        return context;
    }
    for (int32_t index = 0; index < TEST_CHILD_COUNT; ++index) {
        auto child = FrameNode::CreateFrameNode(
            "LazyDynamicLayoutChild", TEST_CHILD_NODE_ID - index, AceType::MakeRefPtr<Pattern>());
        if (!child) {
            return context;
        }
        child->MountToParent(context.host);
    }
    context.wrapper = context.host->CreateLayoutWrapper();
    if (!context.wrapper) {
        return context;
    }
    context.layoutProperty = context.wrapper->GetLayoutProperty();
    if (!context.layoutProperty) {
        return context;
    }
    context.constraint.maxSize = SizeF(480.0f, 1000.0f);
    context.constraint.percentReference = context.constraint.maxSize;
    context.layoutProperty->UpdateLayoutConstraint(context.constraint);
    context.layoutProperty->UpdateContentConstraint();
    context.algorithm = AceType::MakeRefPtr<LazyDynamicLayoutAlgorithm>(params);
    return context;
}

void UpdateViewPosReference(
    const LazyDynamicLayoutTestContext& context, const std::optional<ViewPosReference>& viewPosRef)
{
    auto constraint = context.constraint;
    constraint.viewPosRef = viewPosRef;
    context.layoutProperty->UpdateLayoutConstraint(constraint);
    context.layoutProperty->UpdateContentConstraint();
}
}

class LazyDynamicLayoutPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};
};

/**
 * @tc.name: LazyDynamicLayoutPattern_CreateLayoutAlgorithm_001
 * @tc.desc: Test CreateLayoutAlgorithm with CustomLayoutAlgorithmParam
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutPatternTestNg, LazyDynamicLayoutPattern_CreateLayoutAlgorithm_001, TestSize.Level1)
{
    auto customParams = AceType::MakeRefPtr<LazyCustomLayoutAlgorithmParam>();
    LazyDynamicLayoutPattern pattern(customParams);

    auto algorithm = pattern.CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    auto lazyDynamicLayoutAlgorithm = AceType::DynamicCast<LazyDynamicLayoutAlgorithm>(algorithm);
    EXPECT_NE(lazyDynamicLayoutAlgorithm, nullptr);
}

/**
 * @tc.name: LazyDynamicLayoutPattern_CreateLayoutAlgorithm_002
 * @tc.desc: Test CreateLayoutAlgorithm without CustomLayoutAlgorithmParam
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutPatternTestNg, LazyDynamicLayoutPattern_CreateLayoutAlgorithm_002, TestSize.Level1)
{
    LazyDynamicLayoutPattern pattern;

    auto algorithm = pattern.CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
    auto lazyDynamicLayoutAlgorithm = AceType::DynamicCast<LazyDynamicLayoutAlgorithm>(algorithm);
    EXPECT_NE(lazyDynamicLayoutAlgorithm, nullptr);
}

/**
 * @tc.name: LazyDynamicLayoutPattern_IsAtomicNode_001
 * @tc.desc: Test IsAtomicNode returns false
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutPatternTestNg, LazyDynamicLayoutPattern_IsAtomicNode_001, TestSize.Level1)
{
    LazyDynamicLayoutPattern pattern;
    EXPECT_FALSE(pattern.IsAtomicNode());
}

/**
 * @tc.name: LazyLayoutUtils_CalculateViewRange_001
 * @tc.desc: Test that parent prediction expands LazyDynamicLayout's local range by half a viewport
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutPatternTestNg, LazyLayoutUtils_CalculateViewRange_001, TestSize.Level1)
{
    ViewPosReference viewPosRef {
        .viewPosStart = 100.0f,
        .viewPosEnd = 1100.0f,
        .viewExtStart = 10.0f,
        .viewExtEnd = 20.0f,
        .referencePos = 1200.0f,
        .referenceEdge = ReferenceEdge::START,
        .axis = Axis::VERTICAL,
    };

    auto visibleRange = LazyLayoutUtils::CalculateViewRange(viewPosRef, 0.0f);
    EXPECT_FLOAT_EQ(visibleRange.start, -1110.0f);
    EXPECT_FLOAT_EQ(visibleRange.end, -80.0f);

    viewPosRef.deadline = 1;
    auto predictRange = LazyLayoutUtils::CalculateViewRange(viewPosRef, 0.0f);
    EXPECT_FLOAT_EQ(predictRange.start, -1610.0f);
    EXPECT_FLOAT_EQ(predictRange.end, 420.0f);
}

/**
 * @tc.name: LazyLayoutUtils_CalculateEstimateSampleCount_001
 * @tc.desc: Test detached estimation samples at most two complete lines and fully measures shorter content
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutPatternTestNg, LazyLayoutUtils_CalculateEstimateSampleCount_001, TestSize.Level1)
{
    EXPECT_EQ(LazyLayoutUtils::CalculateEstimateSampleCount(100, 1), 2);
    EXPECT_EQ(LazyLayoutUtils::CalculateEstimateSampleCount(2, 1), 2);
    EXPECT_EQ(LazyLayoutUtils::CalculateEstimateSampleCount(100, 3), 6);
    EXPECT_EQ(LazyLayoutUtils::CalculateEstimateSampleCount(5, 3), 5);
    EXPECT_EQ(LazyLayoutUtils::CalculateEstimateSampleCount(0, 3), 0);
}

/**
 * @tc.name: LazyLayoutUtils_EstimateTotalMainSize_001
 * @tc.desc: Test estimated total main size includes every sampled entry and the gaps between entries.
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutPatternTestNg, LazyLayoutUtils_EstimateTotalMainSize_001, TestSize.Level1)
{
    EXPECT_FLOAT_EQ(LazyLayoutUtils::EstimateTotalMainSize(50.0f, 10, 4.0f), 536.0f);
    EXPECT_FLOAT_EQ(LazyLayoutUtils::EstimateTotalMainSize(50.0f, 1, 4.0f), 50.0f);
    EXPECT_FLOAT_EQ(LazyLayoutUtils::EstimateTotalMainSize(50.0f, 0, 4.0f), 0.0f);
}

/**
 * @tc.name: LazyDynamicLayoutAlgorithm_EstimatePass_001
 * @tc.desc: Test detached and parent-range estimation for a fresh LazyDynamicLayout.
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutPatternTestNg, LazyDynamicLayoutAlgorithm_EstimatePass_001, TestSize.Level1)
{
    LazyDynamicMeasureState state;
    auto params = AceType::MakeRefPtr<LazyCustomLayoutAlgorithmParam>();
    SetMeasureCallback(params, state);
    const auto context = CreateLazyDynamicLayoutTestContext(params);
    ASSERT_NE(context.host, nullptr);
    ASSERT_NE(context.wrapper, nullptr);
    ASSERT_NE(context.layoutProperty, nullptr);
    ASSERT_NE(context.algorithm, nullptr);

    context.algorithm->Measure(AceType::RawPtr(context.wrapper));
    EXPECT_TRUE(context.algorithm->isEstimatePass_);
    EXPECT_FALSE(state.sawEstimateReference);
    ASSERT_TRUE(state.measuredReference.has_value());
    EXPECT_EQ(state.measuredReference->viewPosStart, -1.0f);
    EXPECT_EQ(state.measuredReference->viewPosEnd, -1.0f);
    EXPECT_FALSE(context.layoutProperty->GetContentLayoutConstraint()->viewPosRef.has_value());

    context.host->MountToParent(context.parent, DEFAULT_NODE_SLOT, true);
    ViewPosReference viewPosRef {
        .viewPosStart = 0.0f,
        .viewPosEnd = 1000.0f,
        .referencePos = 1000.0f,
        .referenceEdge = ReferenceEdge::START,
        .axis = Axis::VERTICAL,
        .deadline = 1,
    };
    UpdateViewPosReference(context, viewPosRef);
    context.algorithm->Measure(AceType::RawPtr(context.wrapper));
    EXPECT_TRUE(context.algorithm->isEstimatePass_);
    EXPECT_TRUE(state.sawEstimateReference);
    EXPECT_EQ(state.count, 2);

    context.wrapper->GetGeometryNode()->SetFrameSize(SizeF(480.0f, 100.0f));
    state.sawEstimateReference = false;
    context.algorithm->Measure(AceType::RawPtr(context.wrapper));
    EXPECT_FALSE(context.algorithm->isEstimatePass_);
    EXPECT_FALSE(state.sawEstimateReference);
    EXPECT_EQ(state.count, 3);
}

/**
 * @tc.name: LazyDynamicLayoutAlgorithm_DetachedReuse_001
 * @tc.desc: Test detached reuse preserves geometry and out-of-range prediction stays on the normal path.
 * @tc.type: FUNC
 */
HWTEST_F(LazyDynamicLayoutPatternTestNg, LazyDynamicLayoutAlgorithm_DetachedReuse_001, TestSize.Level1)
{
    LazyDynamicMeasureState state;
    auto params = AceType::MakeRefPtr<LazyCustomLayoutAlgorithmParam>();
    SetMeasureCallback(params, state);
    const auto context = CreateLazyDynamicLayoutTestContext(params);
    ASSERT_NE(context.parent, nullptr);
    ASSERT_NE(context.host, nullptr);
    ASSERT_NE(context.wrapper, nullptr);
    ASSERT_NE(context.layoutProperty, nullptr);
    ASSERT_NE(context.algorithm, nullptr);
    context.host->MountToParent(context.parent, DEFAULT_NODE_SLOT, true);
    context.wrapper->GetGeometryNode()->SetFrameSize(SizeF(480.0f, 100.0f));
    context.host->AttachToMainTree();
    context.host->DetachFromMainTree();

    context.algorithm->Measure(AceType::RawPtr(context.wrapper));
    EXPECT_TRUE(context.algorithm->needSkipLayout_);
    EXPECT_FALSE(context.algorithm->isEstimatePass_);
    EXPECT_EQ(state.count, 0);
    EXPECT_EQ(context.wrapper->GetGeometryNode()->GetFrameSize(), SizeF(480.0f, 100.0f));

    context.wrapper->GetGeometryNode()->SetFrameSize(SizeF(480.0f, 0.0f));
    ViewPosReference viewPosRef {
        .viewPosStart = 0.0f,
        .viewPosEnd = 1000.0f,
        .referencePos = 2000.0f,
        .referenceEdge = ReferenceEdge::START,
        .axis = Axis::VERTICAL,
        .deadline = 1,
    };
    UpdateViewPosReference(context, viewPosRef);
    context.algorithm->Measure(AceType::RawPtr(context.wrapper));
    EXPECT_FALSE(context.algorithm->isEstimatePass_);
    EXPECT_FALSE(state.sawEstimateReference);
    EXPECT_EQ(state.count, 1);
}
} // namespace OHOS::Ace::NG
