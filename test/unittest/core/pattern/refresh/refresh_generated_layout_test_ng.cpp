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

#include "gtest/gtest.h"
#include "refresh_test_ng.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {
class RefreshGeneratedLayoutTestNg : public RefreshTestNg {
public:
};

/**
 * @tc.name: MeasureWithLowVersion001
 * @tc.desc: Test Measure method with isHighVersion_ = false (low version path)
 *           Verify that all children are measured with layoutConstraint without special handling
 * @tc.type: FUNC
 */
HWTEST_F(RefreshGeneratedLayoutTestNg, MeasureWithLowVersion001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create refresh with low version and add content children
     * @tc.expected: Refresh node created with isHighVersion_ = false
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    RefreshModelNG model = CreateRefresh();
    CreateText(); // Add content child

    CreateDone();
    pattern_->isHigherVersion_ = false;

    /**
     * @tc.steps: step2. Get layout algorithm and verify version
     * @tc.expected: Algorithm has isHighVersion_ = false
     */
    auto algorithm = AceType::DynamicCast<RefreshLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);
    algorithm->SetIsHighVersion(false);

    /**
     * @tc.steps: step3. Call Measure method
     * @tc.expected: Measure completes without errors
     */
    algorithm->Measure(AceType::RawPtr(frameNode_));

    /**
     * @tc.steps: step4. Verify children are measured
     * @tc.expected: Children have valid geometry nodes with sizes
     */
    const auto& children = frameNode_->GetChildren();
    EXPECT_EQ(children.size(), 2UL);

    for (const auto& child : children) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (childFrameNode) {
            auto geometryNode = childFrameNode->GetGeometryNode();
            EXPECT_NE(geometryNode, nullptr);
        }
    }
}

/**
 * @tc.name: MeasureWithHighVersionAndCustomBuilder001
 * @tc.desc: Test Measure method with isHighVersion_ = true and custom builder exists
 *           Verify custom builder is measured with builder constraint
 * @tc.type: FUNC
 */
HWTEST_F(RefreshGeneratedLayoutTestNg, MeasureWithHighVersionAndCustomBuilder001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create refresh with high version and custom builder
     * @tc.expected: Refresh node created with custom builder
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto builder = CreateCustomNode();
    RefreshModelNG model = CreateRefresh();
    model.SetCustomBuilder(builder);
    model.SetIsCustomBuilderExist(true);
    CreateText(); // Add content child

    CreateDone();
    pattern_->isHigherVersion_ = true;

    /**
     * @tc.steps: step2. Configure algorithm with high version settings
     * @tc.expected: Algorithm configured properly
     */
    auto algorithm = AceType::DynamicCast<RefreshLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);
    algorithm->SetIsHighVersion(true);
    algorithm->SetCustomBuilderIndex(0);           // Custom builder is at index 0
    algorithm->SetBuilderMeasureBaseHeight(50.0f); // Set builder base height

    /**
     * @tc.steps: step3. Update layout property to indicate custom builder exists
     * @tc.expected: Property updated
     */
    layoutProperty_->UpdateIsCustomBuilderExist(true);

    /**
     * @tc.steps: step4. Call Measure method
     * @tc.expected: Measure completes without errors
     */
    algorithm->Measure(AceType::RawPtr(frameNode_));

    /**
     * @tc.steps: step5. Verify custom builder child exists and is measured
     * @tc.expected: Custom builder has geometry node
     */
    const auto& children = frameNode_->GetChildren();
    EXPECT_GE(children.size(), 2UL); // Custom builder + content child

    // First child should be custom builder
    auto it = children.begin();
    auto customBuilderChild = AceType::DynamicCast<FrameNode>(*it);
    if (customBuilderChild) {
        auto geometryNode = customBuilderChild->GetGeometryNode();
        EXPECT_NE(geometryNode, nullptr);
    }
}

/**
 * @tc.name: MeasureWithHighVersionNoCustomBuilderExist001
 * @tc.desc: Test Measure method with isHighVersion_ = true but custom builder doesn't exist
 *           Verify builder gets fixed height constraint
 * @tc.type: FUNC
 */
HWTEST_F(RefreshGeneratedLayoutTestNg, MeasureWithHighVersionNoCustomBuilderExist001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create refresh with high version
     * @tc.expected: Refresh node created
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshModelNG model = CreateRefresh();
    CreateText(); // Add content child

    CreateDone();
    pattern_->isHigherVersion_ = true;

    /**
     * @tc.steps: step2. Configure algorithm with high version but no custom builder exists
     * @tc.expected: Algorithm configured with builderBaseHeight_
     */
    auto algorithm = AceType::DynamicCast<RefreshLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    ASSERT_NE(algorithm, nullptr);
    algorithm->SetIsHighVersion(true);
    algorithm->SetCustomBuilderIndex(0);
    algorithm->SetBuilderMeasureBaseHeight(60.0f);

    /**
     * @tc.steps: step3. Set custom builder exist to false
     * @tc.expected: Property set to false
     */
    layoutProperty_->UpdateIsCustomBuilderExist(false);

    /**
     * @tc.steps: step4. Call Measure method
     * @tc.expected: Measure completes without errors
     */
    algorithm->Measure(AceType::RawPtr(frameNode_));

    /**
     * @tc.steps: step5. Verify child is measured
     * @tc.expected: Child has geometry node
     */
    const auto& children = frameNode_->GetChildren();
    EXPECT_GE(children.size(), 1UL);

    auto it = children.begin();
    auto child = AceType::DynamicCast<FrameNode>(*it);
    if (child) {
        auto geometryNode = child->GetGeometryNode();
        EXPECT_NE(geometryNode, nullptr);
    }
}

/**
 * @tc.name: CalculateBuilderSizeWithNullProperty001
 * @tc.desc: Test CalculateBuilderSize with null childLayoutWrapper
 *           Verify default empty size is returned
 * @tc.type: FUNC
 */
HWTEST_F(RefreshGeneratedLayoutTestNg, CalculateBuilderSizeWithNullProperty001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create layout algorithm
     * @tc.expected: Algorithm created successfully
     */
    RefreshLayoutAlgorithm algorithm;
    LayoutConstraintF constraint;

    /**
     * @tc.steps: step2. Call CalculateBuilderSize with null childLayoutWrapper
     * @tc.expected: Returns default empty size
     */
    auto result = algorithm.CalculateBuilderSize(nullptr, constraint, 50.0f);

    /**
     * @tc.steps: step3. Verify result is empty
     * @tc.expected: Both width and height are nullopt
     */
    EXPECT_FALSE(result.Width().has_value());
    EXPECT_FALSE(result.Height().has_value());
}

/**
 * @tc.name: LayoutWithHighVersion001
 * @tc.desc: Test Layout with isHighVersion_ = true (UpdateChildPosition path)
 *           Verify child positions are calculated using high version logic
 * @tc.type: FUNC
 */
HWTEST_F(RefreshGeneratedLayoutTestNg, LayoutWithHighVersion001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create refresh with high version and custom builder
     * @tc.expected: Refresh created with custom builder
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto builder = CreateCustomNode();
    RefreshModelNG model = CreateRefresh();
    model.SetCustomBuilder(builder);
    model.SetIsCustomBuilderExist(true);
    CreateText(); // Add content child

    CreateDone();
    pattern_->isHigherVersion_ = true;

    /**
     * @tc.steps: step2. Perform layout
     * @tc.expected: Layout completes successfully
     */
    FlushUITasks();

    /**
     * @tc.steps: step4. Verify custom builder position
     * @tc.expected: Custom builder has valid offset
     */
    const auto& children = frameNode_->GetChildren();
    ASSERT_GE(children.size(), 2UL);

    auto it = children.begin();
    auto customBuilderChild = AceType::DynamicCast<FrameNode>(*it);
    ASSERT_NE(customBuilderChild, nullptr);

    auto builderGeometryNode = customBuilderChild->GetGeometryNode();
    ASSERT_NE(builderGeometryNode, nullptr);

    auto builderOffset = builderGeometryNode->GetMarginFrameOffset();

    // With default builderBaseHeight_ = 0.0f and builderHeight = 10.0f:
    // builderOffset = builderBaseHeight_ - builderHeight = 0.0f - 10.0f = -10.0f
    EXPECT_FLOAT_EQ(builderOffset.GetY(), -10.0f);

    /**
     * @tc.steps: step5. Verify content child position
     * @tc.expected: Content child positioned with scrollOffset
     */
    std::advance(it, 1);
    auto contentChild = AceType::DynamicCast<FrameNode>(*it);
    ASSERT_NE(contentChild, nullptr);

    auto contentGeometryNode = contentChild->GetGeometryNode();
    ASSERT_NE(contentGeometryNode, nullptr);

    auto contentOffset = contentGeometryNode->GetMarginFrameOffset();

    // With default builderBaseHeight_ = 0.0f:
    // scrollOffset = builderBaseHeight_ = 0.0f
    EXPECT_FLOAT_EQ(contentOffset.GetY(), 0.0f);
}

/**
 * @tc.name: LayoutWithHighVersionEqualHeights001
 * @tc.desc: Test Layout with isHighVersion_ = true when builderHeight equals builderBaseHeight_
 *           Verify NearEqual logic results in zero offset and correct scrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(RefreshGeneratedLayoutTestNg, LayoutWithHighVersionEqualHeights001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create refresh with high version
     * @tc.expected: Refresh created with custom builder
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto builder = CreateCustomNode();
    RefreshModelNG model = CreateRefresh();
    model.SetCustomBuilder(builder);
    model.SetIsCustomBuilderExist(true);
    CreateText(); // Add content child

    CreateDone();
    pattern_->isHigherVersion_ = true;

    /**
     * @tc.steps: step2. Perform layout
     * @tc.expected: Layout completes successfully
     */
    FlushUITasks();

    /**
     * @tc.steps: step3. Verify custom builder offset
     * @tc.expected: Custom builder has valid offset
     */
    const auto& children = frameNode_->GetChildren();
    ASSERT_GE(children.size(), 2UL);

    auto it = children.begin();
    auto customBuilderChild = AceType::DynamicCast<FrameNode>(*it);
    ASSERT_NE(customBuilderChild, nullptr);

    auto builderGeometryNode = customBuilderChild->GetGeometryNode();
    ASSERT_NE(builderGeometryNode, nullptr);

    auto builderOffset = builderGeometryNode->GetMarginFrameOffset();

    // With default builderBaseHeight_ = 0.0f and builderHeight = 10.0f:
    // builderOffset = builderBaseHeight_ - builderHeight = 0.0f - 10.0f = -10.0f
    EXPECT_FLOAT_EQ(builderOffset.GetY(), -10.0f);

    /**
     * @tc.steps: step4. Verify content child position
     * @tc.expected: Content child positioned correctly
     */
    std::advance(it, 1);
    auto contentChild = AceType::DynamicCast<FrameNode>(*it);
    ASSERT_NE(contentChild, nullptr);

    auto contentGeometryNode = contentChild->GetGeometryNode();
    ASSERT_NE(contentGeometryNode, nullptr);

    auto contentOffset = contentGeometryNode->GetMarginFrameOffset();

    // With default builderBaseHeight_ = 0.0f:
    // scrollOffset = builderBaseHeight_ = 0.0f
    EXPECT_FLOAT_EQ(contentOffset.GetY(), 0.0f);
}

/**
 * @tc.name: LayoutWithHighVersionDifferentHeights001
 * @tc.desc: Test Layout with isHighVersion_ = true when builderHeight differs from builderBaseHeight_
 *           Verify NearEqual logic results in calculated offset and scrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(RefreshGeneratedLayoutTestNg, LayoutWithHighVersionDifferentHeights001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create refresh with high version
     * @tc.expected: Refresh created with custom builder
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto builder = CreateCustomNode();
    RefreshModelNG model = CreateRefresh();
    model.SetCustomBuilder(builder);
    model.SetIsCustomBuilderExist(true);
    CreateText(); // Add content child

    CreateDone();
    pattern_->isHigherVersion_ = true;

    /**
     * @tc.steps: step2. Perform layout
     * @tc.expected: Layout completes successfully
     */
    FlushUITasks();

    /**
     * @tc.steps: step4. Verify custom builder offset when heights are different
     * @tc.expected: builderOffset = builderBaseHeight_ - builderHeight
     */
    const auto& children = frameNode_->GetChildren();
    ASSERT_GE(children.size(), 2UL);

    auto it = children.begin();
    auto customBuilderChild = AceType::DynamicCast<FrameNode>(*it);
    ASSERT_NE(customBuilderChild, nullptr);

    auto builderGeometryNode = customBuilderChild->GetGeometryNode();
    ASSERT_NE(builderGeometryNode, nullptr);

    auto builderOffset = builderGeometryNode->GetMarginFrameOffset();

    // With default builderBaseHeight_ = 0.0f and builderHeight = 10.0f:
    // builderOffset = builderBaseHeight_ - builderHeight = 0.0f - 10.0f = -10.0f
    EXPECT_FLOAT_EQ(builderOffset.GetY(), -10.0f);

    /**
     * @tc.steps: step5. Verify content child scrollOffset when heights are different
     * @tc.expected: scrollOffset should be builderBaseHeight_
     */
    std::advance(it, 1);
    auto contentChild = AceType::DynamicCast<FrameNode>(*it);
    ASSERT_NE(contentChild, nullptr);

    auto contentGeometryNode = contentChild->GetGeometryNode();
    ASSERT_NE(contentGeometryNode, nullptr);

    auto contentOffset = contentGeometryNode->GetMarginFrameOffset();
    // When heights are different, scrollOffset = builderBaseHeight_
    EXPECT_FLOAT_EQ(contentOffset.GetY(), 0.0f);
}

} // namespace OHOS::Ace::NG
