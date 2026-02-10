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

#define private public
#define protected public

#include "test/unittest/core/layout/layout_algorithm_test_ng.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/property/layout_constraint.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

// Helper function to get layout constraint from optional
inline LayoutConstraintF GetLayoutConstraint(const std::optional<LayoutConstraintF>& constraint)
{
    if (constraint.has_value()) {
        return constraint.value();
    }
    return LayoutConstraintF();
}

/**
 * @tc.name: PostponeForIgnoreTagFuncs
 * @tc.desc: test Get/SetPostponeForIgnore
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, PostponeForIgnoreTagFuncs, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    EXPECT_EQ(layoutAlgorithm->GetNeedPostponeForIgnore(), false);
    layoutAlgorithm->SetNeedPostponeForIgnore(true);
    EXPECT_EQ(layoutAlgorithm->GetNeedPostponeForIgnore(), true);
}


/**
 * @tc.name: GetLayoutConstraintTest001
 * @tc.desc: test GetLayoutConstraint with contentConstraint
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, GetLayoutConstraintTest001, TestSize.Level0)
{
    LayoutConstraintF contentConstraint;
    contentConstraint.minSize = SizeF(10.0f, 10.0f);
    contentConstraint.maxSize = SizeF(100.0f, 100.0f);
    contentConstraint.percentReference = SizeF(200.0f, 200.0f);

    auto result = GetLayoutConstraint(contentConstraint);
    EXPECT_EQ(result.minSize.Width(), 10.0f);
    EXPECT_EQ(result.minSize.Height(), 10.0f);
    EXPECT_EQ(result.maxSize.Width(), 100.0f);
    EXPECT_EQ(result.maxSize.Height(), 100.0f);
    EXPECT_EQ(result.percentReference.Width(), 200.0f);
    EXPECT_EQ(result.percentReference.Height(), 200.0f);
}

/**
 * @tc.name: GetLayoutConstraintTest002
 * @tc.desc: test GetLayoutConstraint with empty contentConstraint
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, GetLayoutConstraintTest002, TestSize.Level0)
{
    std::optional<LayoutConstraintF> contentConstraint = std::nullopt;

    auto result = GetLayoutConstraint(contentConstraint);
    EXPECT_EQ(result.minSize.Width(), 0.0f);
    EXPECT_EQ(result.minSize.Height(), 0.0f);
    EXPECT_EQ(result.maxSize.Width(), 1000000.0f);
    EXPECT_EQ(result.maxSize.Height(), 1000000.0f);
    EXPECT_EQ(result.percentReference.Width(), 0.0f);
    EXPECT_EQ(result.percentReference.Height(), 0.0f);
}

/**
 * @tc.name: CollectOverflowFromFrameNodeTest002
 * @tc.desc: test CollectOverflowFromFrameNode with null hostNode
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, CollectOverflowFromFrameNodeTest002, TestSize.Level0)
{
    auto result = LayoutAlgorithm::CollectOverflowFromFrameNode(nullptr, false);
    EXPECT_FALSE(result.overflowDisabled);
    EXPECT_FALSE(result.totalChildFrameRect.has_value());
}

/**
 * @tc.name: IsContentOverflowShouldDoOverflowWorkFalseTest001
 * @tc.desc: test IsContentOverflow when ShouldDoOverflowWork returns false
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, IsContentOverflowShouldDoOverflowWorkFalseTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = false;

    auto frameNode = FrameNode::CreateFrameNode("test", 9, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    OverflowCollector collector(false);

    // Without FeatureParam enabled, ShouldDoOverflowWork returns false
    auto result = layoutAlgorithm->IsContentOverflow(AceType::RawPtr(layoutWrapper), collector);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsContentOverflowIsOverflowWarningEnabledFalseTest001
 * @tc.desc: test IsContentOverflow when isOverflowWarningEnabled is false
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, IsContentOverflowIsOverflowWarningEnabledFalseTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = false;

    auto frameNode = FrameNode::CreateFrameNode("test", 10, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    OverflowCollector collector(false);

    auto result = layoutAlgorithm->IsContentOverflow(AceType::RawPtr(layoutWrapper), collector);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: HandleContentOverflowTest001
 * @tc.desc: test HandleContentOverflow with valid layoutWrapper (non-overflow component returns early)
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, HandleContentOverflowTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    // Test with a non-overflow component (Pattern without specific pattern type)
    // FrameNode with default Pattern is not in OVERFLOW_ENABLED_COMPONENTS
    auto frameNode = FrameNode::CreateFrameNode("test", 11, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    // HandleContentOverflow should not crash and should return early for non-overflow components
    // The method should execute without crash and return without processing
    layoutAlgorithm->HandleContentOverflow(AceType::RawPtr(layoutWrapper));
    // For non-overflow components, the method returns early without processing vOverflowHandler
    SUCCEED();
}

/**
 * @tc.name: HandleContentOverflowNullLayoutWrapperTest001
 * @tc.desc: test HandleContentOverflow with null layoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, HandleContentOverflowNullLayoutWrapperTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    // Should not crash with null layoutWrapper
    layoutAlgorithm->HandleContentOverflow(nullptr);
    SUCCEED();
}

/**
 * @tc.name: HandleContentOverflowNullHostNodeTest001
 * @tc.desc: test HandleContentOverflow with null hostNode
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, HandleContentOverflowNullHostNodeTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, nullptr);

    // Should not crash with null hostNode
    layoutAlgorithm->HandleContentOverflow(AceType::RawPtr(layoutWrapper));
    SUCCEED();
}

/**
 * @tc.name: HandleContentOverflowNonOverflowComponentTest001
 * @tc.desc: test HandleContentOverflow with non-overflow component
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, HandleContentOverflowNonOverflowComponentTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    // Button is not in OVERFLOW_ENABLED_COMPONENTS
    auto frameNode = FrameNode::CreateFrameNode("Button", 12, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    // Should not crash and return early
    layoutAlgorithm->HandleContentOverflow(AceType::RawPtr(layoutWrapper));
    SUCCEED();
}

/**
 * @tc.name: HandleStackContentOverflowNullLayoutWrapperTest001
 * @tc.desc: test HandleStackContentOverflow with null layoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, HandleStackContentOverflowNullLayoutWrapperTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    // Should not crash with null layoutWrapper
    layoutAlgorithm->HandleStackContentOverflow(nullptr);
    SUCCEED();
}

/**
 * @tc.name: HandleStackContentOverflowNullHostNodeTest001
 * @tc.desc: test HandleStackContentOverflow with null hostNode
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, HandleStackContentOverflowNullHostNodeTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, nullptr);

    // Should not crash with null hostNode
    layoutAlgorithm->HandleStackContentOverflow(AceType::RawPtr(layoutWrapper));
    SUCCEED();
}

/**
 * @tc.name: HandleStackContentOverflowNonStackComponentTest001
 * @tc.desc: test HandleStackContentOverflow with non-Stack component
 * @tc.type: FUNC
 */
HWTEST_F(LayoutAlgorithmTestNg, HandleStackContentOverflowNonStackComponentTest001, TestSize.Level0)
{
    auto layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutAlgorithm->isOverflowWarningEnabled_ = true;

    // Column is in OVERFLOW_ENABLED_COMPONENTS but not Stack
    auto frameNode = FrameNode::CreateFrameNode("Column", 14, AceType::MakeRefPtr<Pattern>());
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    // Should not crash and return early (not Stack)
    layoutAlgorithm->HandleStackContentOverflow(AceType::RawPtr(layoutWrapper));
    SUCCEED();
}
} // namespace OHOS::Ace::NG
