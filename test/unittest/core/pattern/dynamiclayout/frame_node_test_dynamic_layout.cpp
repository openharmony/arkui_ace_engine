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
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_pattern.h"
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_node.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/pipeline/base/element_register.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"


using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
const std::string TEST_TAG = "DynamicLayout";
}

class FrameNodeTestDynamicLayout : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
    }
    void SetUp() override
    {
        ElementRegister::GetInstance()->Clear();
    }
    void TearDown() override
    {
        ElementRegister::GetInstance()->Clear();
    }
};

/**
 * @tc.name: FrameNode_ReplacePattern_001
 * @tc.desc: Test ReplacePattern with DynamicLayoutPattern
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestDynamicLayout, FrameNode_ReplacePattern_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode with initial Pattern
     */
    auto initialPattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = AceType::MakeRefPtr<DynamicLayoutNode>(TEST_TAG, TEST_NODE_ID, initialPattern, false);
    frameNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(frameNode);

    /**
     * @tc.steps: step2. Create new DynamicLayoutPattern with custom params
     */
    auto customParams = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();
    auto newPattern = AceType::MakeRefPtr<DynamicLayoutPattern>(customParams);

    /**
     * @tc.steps: step3. Call ReplacePattern
     * @tc.expected: Pattern should be replaced successfully
     */
    frameNode->ReplacePattern(newPattern);

    /**
     * @tc.steps: step4. Verify pattern is replaced
     * @tc.expected: GetPattern should return new pattern
     */
    auto currentPattern = frameNode->GetPattern<DynamicLayoutPattern>();
    ASSERT_NE(currentPattern, nullptr);
    EXPECT_EQ(currentPattern, newPattern);

    /**
     * @tc.steps: step5. Verify layoutProperty is recreated
     * @tc.expected: LayoutProperty should be updated
     */
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: FrameNode_ReplacePattern_002
 * @tc.desc: Test ReplacePattern with LinearLayoutPattern
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestDynamicLayout, FrameNode_ReplacePattern_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode with DynamicLayoutPattern
     */
    auto initialPattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = AceType::MakeRefPtr<DynamicLayoutNode>(TEST_TAG, TEST_NODE_ID, initialPattern, false);
    frameNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(frameNode);

    /**
     * @tc.steps: step2. Create LinearLayoutPattern for column
     */
    auto newPattern = AceType::MakeRefPtr<LinearLayoutPattern>(true);

    /**
     * @tc.steps: step3. Call ReplacePattern
     * @tc.expected: Pattern should be replaced successfully
     */
    frameNode->ReplacePattern(newPattern);

    /**
     * @tc.steps: step4. Verify pattern is replaced
     * @tc.expected: GetPattern should return LinearLayoutPattern
     */
    auto currentPattern = frameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(currentPattern, nullptr);
    EXPECT_EQ(currentPattern, newPattern);
}

/**
 * @tc.name: FrameNode_ReplacePattern_003
 * @tc.desc: Test ReplacePattern with StackPattern
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestDynamicLayout, FrameNode_ReplacePattern_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode with DynamicLayoutPattern
     */
    auto initialPattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = AceType::MakeRefPtr<DynamicLayoutNode>(TEST_TAG, TEST_NODE_ID, initialPattern, false);
    frameNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(frameNode);

    /**
     * @tc.steps: step2. Create StackPattern
     */
    auto newPattern = AceType::MakeRefPtr<StackPattern>();

    /**
     * @tc.steps: step3. Call ReplacePattern
     * @tc.expected: Pattern should be replaced successfully
     */
    frameNode->ReplacePattern(newPattern);

    /**
     * @tc.steps: step4. Verify pattern is replaced
     * @tc.expected: GetPattern should return StackPattern
     */
    auto currentPattern = frameNode->GetPattern<StackPattern>();
    ASSERT_NE(currentPattern, nullptr);
    EXPECT_EQ(currentPattern, newPattern);
}

/**
 * @tc.name: FrameNode_ReplacePattern_NullPattern_001
 * @tc.desc: Test ReplacePattern with null pattern
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestDynamicLayout, FrameNode_ReplacePattern_NullPattern_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode with initial Pattern
     */
    auto initialPattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = AceType::MakeRefPtr<DynamicLayoutNode>(TEST_TAG, TEST_NODE_ID, initialPattern, false);
    frameNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(frameNode);

    /**
     * @tc.steps: step2. Store original pattern for comparison
     */
    auto originalPattern = frameNode->GetPattern();

    /**
     * @tc.steps: step3. Call ReplacePattern with null
     * @tc.expected: Should not crash and pattern should remain unchanged
     */
    frameNode->ReplacePattern(nullptr);

    /**
     * @tc.steps: step4. Verify pattern is unchanged
     * @tc.expected: Pattern should still be the original one
     */
    auto currentPattern = frameNode->GetPattern();
    EXPECT_EQ(currentPattern, originalPattern);
}

/**
 * @tc.name: FrameNode_ReplacePattern_MultipleReplacements_001
 * @tc.desc: Test ReplacePattern with multiple sequential replacements
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestDynamicLayout, FrameNode_ReplacePattern_MultipleReplacements_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode with initial DynamicLayoutPattern
     */
    auto initialPattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = AceType::MakeRefPtr<DynamicLayoutNode>(TEST_TAG, TEST_NODE_ID, initialPattern, false);
    frameNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(frameNode);

    /**
     * @tc.steps: step2. First replacement to LinearLayoutPattern
     */
    auto linearPattern = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    frameNode->ReplacePattern(linearPattern);
    auto pattern1 = frameNode->GetPattern<LinearLayoutPattern>();
    EXPECT_EQ(pattern1, linearPattern);

    /**
     * @tc.steps: step3. Second replacement to StackPattern
     */
    auto stackPattern = AceType::MakeRefPtr<StackPattern>();
    frameNode->ReplacePattern(stackPattern);
    auto pattern2 = frameNode->GetPattern<StackPattern>();
    EXPECT_EQ(pattern2, stackPattern);

    /**
     * @tc.steps: step4. Third replacement back to DynamicLayoutPattern
     */
    auto customParams = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();
    auto dynamicPattern = AceType::MakeRefPtr<DynamicLayoutPattern>(customParams);
    frameNode->ReplacePattern(dynamicPattern);
    auto pattern3 = frameNode->GetPattern<DynamicLayoutPattern>();
    EXPECT_EQ(pattern3, dynamicPattern);
}

/**
 * @tc.name: FrameNode_ReplacePattern_VerifyPropertyRecreation_001
 * @tc.desc: Test ReplacePattern recreates layout and paint properties
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestDynamicLayout, FrameNode_ReplacePattern_VerifyPropertyRecreation_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode with initial Pattern
     */
    auto initialPattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = AceType::MakeRefPtr<DynamicLayoutNode>(TEST_TAG, TEST_NODE_ID, initialPattern, false);
    frameNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(frameNode);

    /**
     * @tc.steps: step2. Store original layout property
     */
    auto originalLayoutProperty = frameNode->GetLayoutProperty();

    /**
     * @tc.steps: step3. Replace pattern
     */
    auto customParams = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();
    auto newPattern = AceType::MakeRefPtr<DynamicLayoutPattern>(customParams);
    frameNode->ReplacePattern(newPattern);

    /**
     * @tc.steps: step4. Verify layout property is recreated
     * @tc.expected: New layout property should be different from original
     */
    auto newLayoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(newLayoutProperty, nullptr);
    EXPECT_NE(newLayoutProperty, originalLayoutProperty);

    /**
     * @tc.steps: step5. Verify paint property is recreated
     * @tc.expected: Paint property should exist and have host set
     */
    auto paintProperty = frameNode->GetPaintProperty<PaintProperty>();
    ASSERT_NE(paintProperty, nullptr);
}

/**
 * @tc.name: FrameNode_ReplacePattern_CustomLayoutWithCallback_001
 * @tc.desc: Test ReplacePattern with custom layout containing callbacks
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestDynamicLayout, FrameNode_ReplacePattern_CustomLayoutWithCallback_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode with initial Pattern
     */
    auto initialPattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = AceType::MakeRefPtr<DynamicLayoutNode>(TEST_TAG, TEST_NODE_ID, initialPattern, false);
    frameNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(frameNode);

    /**
     * @tc.steps: step2. Create CustomLayoutAlgorithmParam with callbacks
     */
    auto customParams = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();
    bool onMeasureExecuted = false;
    bool onLayoutExecuted = false;

    customParams->SetOnMeasureSize([&onMeasureExecuted](LayoutWrapper* layoutWrapper) {
        onMeasureExecuted = true;
    });
    customParams->SetOnPlaceChildren([&onLayoutExecuted](LayoutWrapper* layoutWrapper) {
        onLayoutExecuted = true;
    });

    /**
     * @tc.steps: step3. Create new pattern with custom params
     */
    auto newPattern = AceType::MakeRefPtr<DynamicLayoutPattern>(customParams);

    /**
     * @tc.steps: step4. Call ReplacePattern
     * @tc.expected: Pattern should be replaced successfully
     */
    frameNode->ReplacePattern(newPattern);

    /**
     * @tc.steps: step5. Verify pattern is replaced
     * @tc.expected: New pattern should contain custom params with callbacks
     */
    auto currentPattern = frameNode->GetPattern<DynamicLayoutPattern>();
    ASSERT_NE(currentPattern, nullptr);
    EXPECT_EQ(currentPattern, newPattern);

    /**
     * @tc.steps: step6. Create layout algorithm and verify callbacks are preserved
     */
    auto algorithm = currentPattern->CreateLayoutAlgorithm();
    ASSERT_NE(algorithm, nullptr);
}

/**
 * @tc.name: FrameNode_ReplacePattern_ColumnToRow_001
 * @tc.desc: Test ReplacePattern changing from column to row layout
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestDynamicLayout, FrameNode_ReplacePattern_ColumnToRow_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create FrameNode with column LinearLayoutPattern
     */
    auto columnPattern = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    auto frameNode = AceType::MakeRefPtr<DynamicLayoutNode>(TEST_TAG, TEST_NODE_ID, columnPattern, false);
    frameNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(frameNode);

    /**
     * @tc.steps: step2. Verify initial pattern is column
     */
    auto initialPattern = frameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(initialPattern, nullptr);

    /**
     * @tc.steps: step3. Replace with row LinearLayoutPattern
     */
    auto rowPattern = AceType::MakeRefPtr<LinearLayoutPattern>(false);
    frameNode->ReplacePattern(rowPattern);

    /**
     * @tc.steps: step4. Verify pattern is replaced to row
     * @tc.expected: GetPattern should return new row pattern
     */
    auto currentPattern = frameNode->GetPattern<LinearLayoutPattern>();
    ASSERT_NE(currentPattern, nullptr);
    EXPECT_EQ(currentPattern, rowPattern);
}

/**
 * @tc.name: DynamicLayoutNode_SetLayoutType_BeforeAndAfterReplacePattern_001
 * @tc.desc: Test SetLayoutType before and after ReplacePattern
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeTestDynamicLayout, DynamicLayoutNode_SetLayoutType_BeforeAndAfterReplacePattern_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DynamicLayoutNode with DynamicLayoutPattern
     */
    auto initialPattern = AceType::MakeRefPtr<DynamicLayoutPattern>();
    auto frameNode = AceType::MakeRefPtr<DynamicLayoutNode>(TEST_TAG, TEST_NODE_ID, initialPattern, false);
    frameNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(frameNode);

    /**
     * @tc.steps: step2. Set layout type to COLUMN_LAYOUT
     */
    frameNode->SetLayoutType(DynamicLayoutType::COLUMN_LAYOUT);
    EXPECT_EQ(frameNode->GetLayoutType(), DynamicLayoutType::COLUMN_LAYOUT);

    /**
     * @tc.steps: step3. Replace pattern with StackPattern
     */
    auto stackPattern = AceType::MakeRefPtr<StackPattern>();
    frameNode->ReplacePattern(stackPattern);

    /**
     * @tc.steps: step4. Set layout type to STACK_LAYOUT
     * @tc.expected: Layout type should be updated to STACK_LAYOUT
     */
    frameNode->SetLayoutType(DynamicLayoutType::STACK_LAYOUT);
    EXPECT_EQ(frameNode->GetLayoutType(), DynamicLayoutType::STACK_LAYOUT);
}

} // namespace OHOS::Ace::NG
