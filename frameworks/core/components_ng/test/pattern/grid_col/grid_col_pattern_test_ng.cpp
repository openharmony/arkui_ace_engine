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
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class GridColPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    static RefPtr<FrameNode> CreateDividerNode(TestProperty& testProperty);
};

void GridColPatternTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void GridColPatternTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: GridColDefault001
 * @tc.desc: Test the default values of GridCol's properties.
 * @tc.type: FUNC
 */
HWTEST_F(GridColPatternTestNg, GridColDefault001, TestSize.Level1)
{
    GridColModelNG gridColModelNG;
    gridColModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<GridColLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto span = layoutProperty->GetSpan();
    EXPECT_TRUE(span.has_value());
    auto offset = layoutProperty->GetOffset();
    EXPECT_TRUE(offset.has_value());
    auto order = layoutProperty->GetOrder();
    EXPECT_TRUE(order.has_value());

    constexpr int32_t testVal = 7;
    layoutProperty->UpdateSpan(V2::GridContainerSize(testVal));
    EXPECT_EQ(layoutProperty->GetSpanValue().xs, testVal);
    layoutProperty->UpdateOffset(V2::GridContainerSize(testVal));
    EXPECT_EQ(layoutProperty->GetOffsetValue().md, testVal);
    layoutProperty->UpdateOrder(V2::GridContainerSize(testVal));
    EXPECT_EQ(layoutProperty->GetOrderValue().lg, testVal);

    // rubbish code for coverity
    auto clone = layoutProperty->Clone();
    clone.Reset();
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
}

/**
 * @tc.name: GridColDefault002
 * @tc.desc: Test GridCol's properties.
 * @tc.type: FUNC
 */
HWTEST_F(GridColPatternTestNg, GridColDefault002, TestSize.Level1)
{
    GridColModelNG gridColModelNG;
    RefPtr<V2::GridContainerSize> spanVal = AceType::MakeRefPtr<V2::GridContainerSize>(1);
    RefPtr<V2::GridContainerSize> offsetVal = AceType::MakeRefPtr<V2::GridContainerSize>(0);
    RefPtr<V2::GridContainerSize> orderVal = AceType::MakeRefPtr<V2::GridContainerSize>(0);
    gridColModelNG.Create(spanVal, offsetVal, orderVal);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<GridColLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto span = layoutProperty->GetSpan();
    EXPECT_TRUE(span.has_value());
    auto offset = layoutProperty->GetOffset();
    EXPECT_TRUE(offset.has_value());
    auto order = layoutProperty->GetOrder();
    EXPECT_TRUE(order.has_value());
}
} // namespace OHOS::Ace::NG