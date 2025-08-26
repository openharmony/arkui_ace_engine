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

#include <optional>

#include "gtest/gtest.h"
#define private public
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/grid_col/grid_col_layout_pattern.h"
#include "core/components_ng/pattern/grid_col/grid_col_model_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
} // namespace

class GridColTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static RefPtr<FrameNode> CreateDividerNode(TestProperty& testProperty);
};

void GridColTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void GridColTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: GridColDefault001
 * @tc.desc: Test the default values of GridCol's properties.
 * @tc.type: FUNC
 */
HWTEST_F(GridColTestNg, GridColDefault001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create gridCol and Set properties.
     */
    GridColModelNG gridColModelNG;
    gridColModelNG.Create();
    auto testVal = V2::GridContainerSize(7);
    gridColModelNG.SetSpan(testVal);
    gridColModelNG.SetOffset(testVal);
    gridColModelNG.SetOrder(testVal);

    /**
     * @tc.steps: step2. Get frameNode, layoutProperty.
     * @tc.expected: step2. Verify properties is correct.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<GridColLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetSpan(), testVal);
    EXPECT_EQ(layoutProperty->GetOffset(), testVal);
    EXPECT_EQ(layoutProperty->GetOrder(), testVal);

    // rubbish code for coverity
    auto clone = layoutProperty->Clone();
    clone.Reset();
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_NE(json->ToString(), "");
}

/**
 * @tc.name: GridColDefault002
 * @tc.desc: Test GetPropValue function.
 * @tc.type: FUNC
 */
HWTEST_F(GridColTestNg, GridColDefault002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create gridCol and get frameNode, layoutProperty.
     */
    GridColModelNG gridColModelNG;
    gridColModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<GridColLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Verify GetPropValue func.
     */
    int32_t propValue;
    const V2::GridContainerSize prop = V2::GridContainerSize(7);
    propValue = layoutProperty->GetPropValue(prop, V2::GridSizeType::XS);
    EXPECT_EQ(propValue, prop.xs);
    propValue = layoutProperty->GetPropValue(prop, V2::GridSizeType::SM);
    EXPECT_EQ(propValue, prop.sm);
    propValue = layoutProperty->GetPropValue(prop, V2::GridSizeType::MD);
    EXPECT_EQ(propValue, prop.md);
    propValue = layoutProperty->GetPropValue(prop, V2::GridSizeType::LG);
    EXPECT_EQ(propValue, prop.lg);
    propValue = layoutProperty->GetPropValue(prop, V2::GridSizeType::XL);
    EXPECT_EQ(propValue, prop.xl);
    propValue = layoutProperty->GetPropValue(prop, V2::GridSizeType::XXL);
    EXPECT_EQ(propValue, prop.xxl);
    propValue = layoutProperty->GetPropValue(prop, V2::GridSizeType::UNDEFINED);
    EXPECT_EQ(propValue, prop.xs);
}
} // namespace OHOS::Ace::NG
