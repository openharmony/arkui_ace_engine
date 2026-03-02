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
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_model_ng.h"
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_node.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_pattern.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_property.h"
#include "core/pipeline/base/element_register.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#undef protected
#undef private

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
const std::string TEST_TAG = "DynamicLayout";
constexpr float TEST_ROW_GAP = 15.0f;
constexpr float TEST_COLUMN_GAP = 20.0f;
}

class DynamicLayoutGridTestNg : public testing::Test {
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
        ViewStackProcessor::GetInstance()->ClearStack();
    }
    void TearDown() override
    {
        ViewStackProcessor::GetInstance()->ClearStack();
        ElementRegister::GetInstance()->Clear();
    }
};

/**
 * @tc.name: DynamicLayoutModelNG_Create_GridLayout_001
 * @tc.desc: Test Create with GRID_LAYOUT type
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutGridTestNg, DynamicLayoutModelNG_Create_GridLayout_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GridLayoutAlgorithmParam
     */
    auto gridParams = AceType::MakeRefPtr<GridLayoutAlgorithmParam>();
    gridParams->SetColumnsTemplate("1fr 1fr");

    /**
     * @tc.steps: step2. Call DynamicLayoutModelNG::Create with GRID_LAYOUT
     */
    DynamicLayoutModelNG model;
    model.Create(gridParams, DynamicLayoutType::GRID_LAYOUT);

    /**
     * @tc.steps: step3. Verify frameNode is created and pushed to stack
     * @tc.expected: FrameNode should be created with LazyGridLayoutPattern
     */
    auto frameNode = AceType::DynamicCast<DynamicLayoutNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);

    auto layoutType = frameNode->GetLayoutType();
    EXPECT_EQ(layoutType, DynamicLayoutType::GRID_LAYOUT);

    /**
     * @tc.steps: step4. Verify pattern is LazyGridLayoutPattern
     * @tc.expected: Pattern should be LazyGridLayoutPattern with dynamic layout flag set
     */
    auto pattern = frameNode->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->IsDynamicLayout());
}

/**
 * @tc.name: DynamicLayoutModelNG_Create_GridLayout_WithItemFillPolicy_001
 * @tc.desc: Test Create with GRID_LAYOUT type and ItemFillPolicy
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutGridTestNg, DynamicLayoutModelNG_Create_GridLayout_WithItemFillPolicy_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GridLayoutAlgorithmParam with ItemFillPolicy
     */
    auto gridParams = AceType::MakeRefPtr<GridLayoutAlgorithmParam>();
    gridParams->SetItemFillPolicy(PresetFillType::BREAKPOINT_SM2MD3LG5);

    /**
     * @tc.steps: step2. Call DynamicLayoutModelNG::Create with GRID_LAYOUT
     */
    DynamicLayoutModelNG model;
    model.Create(gridParams, DynamicLayoutType::GRID_LAYOUT);

    /**
     * @tc.steps: step3. Verify frameNode is created
     * @tc.expected: FrameNode should be created with LazyGridLayoutPattern
     */
    auto frameNode = AceType::DynamicCast<DynamicLayoutNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetLayoutType(), DynamicLayoutType::GRID_LAYOUT);

    auto pattern = frameNode->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->IsDynamicLayout());
}

/**
 * @tc.name: DynamicLayoutModelNG_Create_GridLayout_WithGaps_001
 * @tc.desc: Test Create with GRID_LAYOUT type and gaps
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutGridTestNg, DynamicLayoutModelNG_Create_GridLayout_WithGaps_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GridLayoutAlgorithmParam with gaps
     */
    auto gridParams = AceType::MakeRefPtr<GridLayoutAlgorithmParam>();
    gridParams->SetColumnsTemplate("1fr 1fr 1fr");
    CalcDimension rowsGap(TEST_ROW_GAP, DimensionUnit::VP);
    gridParams->SetRowsGap(rowsGap);
    CalcDimension columnsGap(TEST_COLUMN_GAP, DimensionUnit::VP);
    gridParams->SetColumnsGap(columnsGap);

    /**
     * @tc.steps: step2. Call DynamicLayoutModelNG::Create with GRID_LAYOUT
     */
    DynamicLayoutModelNG model;
    model.Create(gridParams, DynamicLayoutType::GRID_LAYOUT);

    /**
     * @tc.steps: step3. Verify frameNode is created
     * @tc.expected: FrameNode should be created with correct layout type
     */
    auto frameNode = AceType::DynamicCast<DynamicLayoutNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetLayoutType(), DynamicLayoutType::GRID_LAYOUT);

    auto pattern = frameNode->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->IsDynamicLayout());
}

/**
 * @tc.name: DynamicLayoutModelNG_UpdatePropertyFromGridParam_WithColumnsTemplate_001
 * @tc.desc: Test UpdatePropertyFromAlgorithmParams for GRID_LAYOUT with ColumnsTemplate
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutGridTestNg, DynamicLayoutModelNG_UpdatePropertyFromGridParam_WithColumnsTemplate_001,
    TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode with LazyGridLayoutPattern
     */
    auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create GridLayoutAlgorithmParam with ColumnsTemplate
     */
    auto gridParams = AceType::MakeRefPtr<GridLayoutAlgorithmParam>();
    gridParams->SetColumnsTemplate("1fr 2fr 1fr");

    /**
     * @tc.steps: step3. Call UpdatePropertyFromAlgorithmParams with GRID_LAYOUT type
     */
    DynamicLayoutModelNG::UpdatePropertyFromAlgorithmParams(frameNode, gridParams, DynamicLayoutType::GRID_LAYOUT);

    /**
     * @tc.steps: step4. Verify properties are updated
     * @tc.expected: LazyGridLayoutProperty should exist and pattern should have dynamic layout flag
     */
    auto layoutProperty = frameNode->GetLayoutProperty<LazyGridLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(pattern->IsDynamicLayout());
}

/**
 * @tc.name: DynamicLayoutModelNG_UpdatePropertyFromGridParam_WithItemFillPolicy_001
 * @tc.desc: Test UpdatePropertyItemFillPolicy for GRID_LAYOUT with ItemFillPolicy
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutGridTestNg, DynamicLayoutModelNG_UpdatePropertyFromGridParam_WithItemFillPolicy_001,
    TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode with LazyGridLayoutPattern
     */
    auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create GridLayoutAlgorithmParam with ItemFillPolicy
     */
    auto gridParams = AceType::MakeRefPtr<GridLayoutAlgorithmParam>();
    gridParams->SetItemFillPolicy(PresetFillType::BREAKPOINT_SM2MD3LG5);

    /**
     * @tc.steps: step3. Call UpdatePropertyFromAlgorithmParams with GRID_LAYOUT type
     */
    DynamicLayoutModelNG::UpdatePropertyFromAlgorithmParams(frameNode, gridParams, DynamicLayoutType::GRID_LAYOUT);

    /**
     * @tc.steps: step4. Verify properties are updated
     * @tc.expected: LazyGridLayoutProperty should exist
     */
    auto layoutProperty = frameNode->GetLayoutProperty<LazyGridLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(pattern->IsDynamicLayout());
}

/**
 * @tc.name: DynamicLayoutModelNG_UpdatePropertyFromGridParam_WithGaps_001
 * @tc.desc: Test UpdatePropertyFromAlgorithmParams for GRID_LAYOUT with gaps
 * @tc.type: FUNC

 */
HWTEST_F(DynamicLayoutGridTestNg, DynamicLayoutModelNG_UpdatePropertyFromGridParam_WithGaps_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode with LazyGridLayoutPattern
     */
    auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create GridLayoutAlgorithmParam with gaps
     */
    auto gridParams = AceType::MakeRefPtr<GridLayoutAlgorithmParam>();
    CalcDimension rowsGap(TEST_ROW_GAP, DimensionUnit::VP);
    gridParams->SetRowsGap(rowsGap);
    CalcDimension columnsGap(TEST_COLUMN_GAP, DimensionUnit::VP);
    gridParams->SetColumnsGap(columnsGap);

    /**
     * @tc.steps: step3. Call UpdatePropertyFromAlgorithmParams with GRID_LAYOUT type
     */
    DynamicLayoutModelNG::UpdatePropertyFromAlgorithmParams(frameNode, gridParams, DynamicLayoutType::GRID_LAYOUT);

    /**
     * @tc.steps: step4. Verify properties are updated
     * @tc.expected: LazyGridLayoutProperty should exist
     */
    auto layoutProperty = frameNode->GetLayoutProperty<LazyGridLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(pattern->IsDynamicLayout());
}

/**
 * @tc.name: DynamicLayoutModelNG_UpdatePropertyFromGridParam_Complete_001
 * @tc.desc: Test UpdatePropertyFromAlgorithmParams for GRID_LAYOUT with all properties
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutGridTestNg, DynamicLayoutModelNG_UpdatePropertyFromGridParam_Complete_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode with LazyGridLayoutPattern
     */
    auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create GridLayoutAlgorithmParam with all properties
     */
    auto gridParams = AceType::MakeRefPtr<GridLayoutAlgorithmParam>();
    gridParams->SetColumnsTemplate("1fr 1fr 1fr");
    CalcDimension rowsGap(TEST_ROW_GAP, DimensionUnit::VP);
    gridParams->SetRowsGap(rowsGap);
    CalcDimension columnsGap(TEST_COLUMN_GAP, DimensionUnit::VP);
    gridParams->SetColumnsGap(columnsGap);

    /**
     * @tc.steps: step3. Call UpdatePropertyFromAlgorithmParams with GRID_LAYOUT type
     */
    DynamicLayoutModelNG::UpdatePropertyFromAlgorithmParams(frameNode, gridParams, DynamicLayoutType::GRID_LAYOUT);

    /**
     * @tc.steps: step4. Verify properties are updated
     * @tc.expected: LazyGridLayoutProperty should exist with all properties set
     */
    auto layoutProperty = frameNode->GetLayoutProperty<LazyGridLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(pattern->IsDynamicLayout());
}

/**
 * @tc.name: DynamicLayoutModelNG_Create_GridLayout_SwitchType_001
 * @tc.desc: Test Create with GRID_LAYOUT then switch to COLUMN_LAYOUT
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutGridTestNg, DynamicLayoutModelNG_Create_GridLayout_SwitchType_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DynamicLayout with GRID_LAYOUT
     */
    auto gridParams = AceType::MakeRefPtr<GridLayoutAlgorithmParam>();
    gridParams->SetColumnsTemplate("1fr 1fr");

    DynamicLayoutModelNG model;
    model.Create(gridParams, DynamicLayoutType::GRID_LAYOUT);

    auto frameNode = AceType::DynamicCast<DynamicLayoutNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetLayoutType(), DynamicLayoutType::GRID_LAYOUT);

    /**
     * @tc.steps: step2. Switch to COLUMN_LAYOUT
     */
    ViewStackProcessor::GetInstance()->Pop();
    auto columnParams = AceType::MakeRefPtr<LinearLayoutAlgorithmParam>(true);
    model.Create(columnParams, DynamicLayoutType::COLUMN_LAYOUT);

    /**
     * @tc.steps: step3. Verify layout type is switched
     * @tc.expected: FrameNode should have COLUMN_LAYOUT type
     */
    frameNode = AceType::DynamicCast<DynamicLayoutNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetLayoutType(), DynamicLayoutType::COLUMN_LAYOUT);
}

/**
 * @tc.name: DynamicLayoutModelNG_Create_GridLayout_DefaultParams_001
 * @tc.desc: Test Create with GRID_LAYOUT using default params
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutGridTestNg, DynamicLayoutModelNG_Create_GridLayout_DefaultParams_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GridLayoutAlgorithmParam with default constructor
     */
    auto gridParams = AceType::MakeRefPtr<GridLayoutAlgorithmParam>();

    /**
     * @tc.steps: step2. Call DynamicLayoutModelNG::Create with GRID_LAYOUT
     */
    DynamicLayoutModelNG model;
    model.Create(gridParams, DynamicLayoutType::GRID_LAYOUT);

    /**
     * @tc.steps: step3. Verify frameNode is created
     * @tc.expected: FrameNode should be created with LazyGridLayoutPattern
     */
    auto frameNode = AceType::DynamicCast<DynamicLayoutNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetLayoutType(), DynamicLayoutType::GRID_LAYOUT);

    auto pattern = frameNode->GetPattern<LazyGridLayoutPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->IsDynamicLayout());
}

/**
 * @tc.name: DynamicLayoutModelNG_UpdatePropertyFromGridParam_NullFrameNode_001
 * @tc.desc: Test UpdatePropertyFromAlgorithmParams with null frameNode
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutGridTestNg, DynamicLayoutModelNG_UpdatePropertyFromGridParam_NullFrameNode_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GridLayoutAlgorithmParam
     */
    auto gridParams = AceType::MakeRefPtr<GridLayoutAlgorithmParam>();
    gridParams->SetColumnsTemplate("1fr 1fr");

    /**
     * @tc.steps: step2. Call UpdatePropertyFromAlgorithmParams with null frameNode
     * @tc.expected: Should not crash
     */
    RefPtr<FrameNode> nullFrameNode = nullptr;
    DynamicLayoutModelNG::UpdatePropertyFromAlgorithmParams(nullFrameNode, gridParams, DynamicLayoutType::GRID_LAYOUT);
}

/**
 * @tc.name: DynamicLayoutModelNG_UpdatePropertyFromGridParam_NullParams_001
 * @tc.desc: Test UpdatePropertyFromAlgorithmParams with null params
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutGridTestNg, DynamicLayoutModelNG_UpdatePropertyFromGridParam_NullParams_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frameNode with LazyGridLayoutPattern
     */
    auto pattern = AceType::MakeRefPtr<LazyGridLayoutPattern>();
    auto frameNode = FrameNode::CreateFrameNode(TEST_TAG, TEST_NODE_ID, pattern, false);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Call UpdatePropertyFromAlgorithmParams with null params
     * @tc.expected: Should not crash
     */
    RefPtr<AlgorithmParamBase> nullParams = nullptr;
    DynamicLayoutModelNG::UpdatePropertyFromAlgorithmParams(frameNode, nullParams, DynamicLayoutType::GRID_LAYOUT);
}

/**
 * @tc.name: DynamicLayoutModelNG_Create_GridLayout_MultipleTimes_001
 * @tc.desc: Test Create with GRID_LAYOUT multiple times
 * @tc.type: FUNC
 */
HWTEST_F(DynamicLayoutGridTestNg, DynamicLayoutModelNG_Create_GridLayout_MultipleTimes_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DynamicLayout with GRID_LAYOUT first time
     */
    auto gridParams1 = AceType::MakeRefPtr<GridLayoutAlgorithmParam>();
    gridParams1->SetColumnsTemplate("1fr 1fr");

    DynamicLayoutModelNG model;
    model.Create(gridParams1, DynamicLayoutType::GRID_LAYOUT);

    auto frameNode1 = AceType::DynamicCast<DynamicLayoutNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode1, nullptr);
    EXPECT_EQ(frameNode1->GetLayoutType(), DynamicLayoutType::GRID_LAYOUT);

    /**
     * @tc.steps: step2. Create DynamicLayout with GRID_LAYOUT second time
     */
    ViewStackProcessor::GetInstance()->Pop();
    auto gridParams2 = AceType::MakeRefPtr<GridLayoutAlgorithmParam>();
    gridParams2->SetColumnsTemplate("1fr 1fr 1fr");

    model.Create(gridParams2, DynamicLayoutType::GRID_LAYOUT);

    auto frameNode2 = AceType::DynamicCast<DynamicLayoutNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode2, nullptr);
    EXPECT_EQ(frameNode2->GetLayoutType(), DynamicLayoutType::GRID_LAYOUT);
}

} // namespace OHOS::Ace::NG
