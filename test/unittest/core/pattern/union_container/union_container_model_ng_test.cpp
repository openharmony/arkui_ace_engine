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

#include "gmock/gmock-actions.h"
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context_creator.h"
#include "test/mock/core/render/mock_rosen_render_context.h"

#include "core/components_ng/pattern/union_container/union_container_model_ng.h"
#include "core/components_ng/pattern/union_container/union_container_pattern.h"
#include "core/components_ng/property/union_container_options.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class UnionContainerModelNgTest : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp();
    void TearDown();
};

void UnionContainerModelNgTest::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void UnionContainerModelNgTest::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void UnionContainerModelNgTest::SetUp()
{
    ViewStackProcessor::GetInstance()->ClearStack();
    RenderContextCreateFunction func = []() -> RefPtr<RenderContext> {
        auto renderContext = AceType::MakeRefPtr<RosenRenderContext>();
        return renderContext;
    };
    MockRenderContextCreator::SetRenderContextCreateFunction(std::move(func));
}

void UnionContainerModelNgTest::TearDown()
{
    ViewStackProcessor::GetInstance()->ClearStack();
    MockRenderContextCreator::ResetRenderContextCreateFunction();
}

/**
 * @tc.name: Create001
 * @tc.desc: Create function with normal spacing.
 * @tc.type: FUNC
 */
HWTEST_F(UnionContainerModelNgTest, Create001, TestSize.Level1)
{
    UnionContainerModelNG model;
    double spacingRaw = 10.0;
    UnionContainerOptions options { .spacing = CalcDimension(spacingRaw, DimensionUnit::PX) };
    model.Create(options);
    auto node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(node, nullptr);
    auto pattern = node->GetPattern<UnionContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    auto spacing = pattern->GetSpacing();
    EXPECT_TRUE(NearEqual(spacing, CalcDimension(spacingRaw, DimensionUnit::PX)));
}

/**
 * @tc.name: Create002
 * @tc.desc: Create function with percent spacing.
 * @tc.type: FUNC
 */
HWTEST_F(UnionContainerModelNgTest, Create002, TestSize.Level1)
{
    /**
     * @tc.steps1: set percent spacing
     * @tc.expected: the spacing should be invalid and equal to default 0.
     */
    UnionContainerModelNG model;
    double spacingPercent = 20;
    UnionContainerOptions options { .spacing = CalcDimension(spacingPercent, DimensionUnit::PERCENT) };
    model.Create(options);
    auto node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(node, nullptr);
    auto pattern = node->GetPattern<UnionContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(NearEqual(pattern->GetSpacing().Value(), 0.0));
}

/**
 * @tc.name: Create003
 * @tc.desc: Create function with negative spacing.
 * @tc.type: FUNC
 */
HWTEST_F(UnionContainerModelNgTest, Create003, TestSize.Level1)
{
    /**
     * @tc.steps1: set negative spacing
     * @tc.expected: the spacing should be invalid and equal to default 0.
     */
    UnionContainerModelNG model;
    double spacingRaw = -20;
    UnionContainerOptions options { .spacing = CalcDimension(spacingRaw, DimensionUnit::PX) };
    model.Create(options);
    auto node = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(node, nullptr);
    auto pattern = node->GetPattern<UnionContainerPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(NearEqual(pattern->GetSpacing().Value(), 0.0));
}
} // namespace OHOS::Ace::NG
