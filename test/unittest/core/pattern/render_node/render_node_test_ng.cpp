/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include <cmath>
#include <cstdint>
#include <string>

#include "gtest/gtest.h"
#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/render_node/render_node_pattern.h"
#include "core/components_ng/pattern/render_node/render_node_paint_property.h"
#include "core/components_ng/pattern/render_node/render_node_paint_method.h"
#include "core/components_ng/pattern/render_node/render_node_modifier.h"
#include "core/components_ng/pattern/render_node/render_node_layout_property.h"
#include "core/components_ng/pattern/render_node/render_node_layout_algorithm.h"
#include "core/components_ng/base/frame_node.h"
#include "test/mock/core/render/mock_render_context.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/render/paint_wrapper.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RenderNodeTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void RenderNodeTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void RenderNodeTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: RatingCreateTest001
 * @tc.desc: Create Rating.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestNg, RenderNodePattern001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("Pattern", 0, AceType::MakeRefPtr<RenderNodePattern>());
    auto renderNodePattern = frameNode->GetPattern<RenderNodePattern>();

    auto layoutAlgorithm = renderNodePattern->CreateLayoutAlgorithm();
    EXPECT_NE(layoutAlgorithm, nullptr);

    auto layoutProperty = renderNodePattern->CreateLayoutProperty();
    EXPECT_NE(layoutProperty, nullptr);

    auto paintProperty = renderNodePattern->CreatePaintProperty();
    EXPECT_NE(paintProperty, nullptr);

    auto paintMethod = renderNodePattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);

    renderNodePattern->Invalidate();
    EXPECT_EQ(renderNodePattern->renderNodeModifier_->renderNodeFlag_->Get(), 1);
}

/**
 * @tc.name: RatingCreateTest001
 * @tc.desc: Create Rating.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestNg, RenderNodePaintMethod001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("PaintMethod", 0, AceType::MakeRefPtr<RenderNodePattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto renderNodePattern = frameNode->GetPattern<RenderNodePattern>();
    ASSERT_NE(renderNodePattern, nullptr);
    auto renderNodeLayoutProperty = renderNodePattern->GetLayoutProperty<RenderNodeLayoutProperty>();
    ASSERT_NE(renderNodeLayoutProperty, nullptr);

    auto drawCallback = [](DrawingContext& context) {};
    auto renderNodeModifier = AceType::MakeRefPtr<RenderNodeModifier>(drawCallback);
    RenderNodePaintMethod renderNodePaintMethod(renderNodeModifier);

    RefPtr<RenderContext> renderContext = RenderContext::Create();
    auto paintProperty = renderNodePattern->CreatePaintProperty();
    auto renderNodePaintProperty = AceType::DynamicCast<RenderNodePaintProperty>(paintProperty);
    renderNodePaintProperty->UpdateRenderNodeFlag(1);
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    auto modifier = renderNodePaintMethod.GetContentModifier(AceType::RawPtr(paintWrapper));
    EXPECT_NE(modifier, nullptr);

    renderNodePaintMethod.UpdateContentModifier(AceType::RawPtr(paintWrapper));
    EXPECT_EQ(renderNodePaintMethod.renderNodeFlag_, 1);
}

/**
 * @tc.name: RatingCreateTest001
 * @tc.desc: Create Rating.
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeTestNg, RenderNodeLayoutAlgorithm001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("LayoutAlgorithm", 0, AceType::MakeRefPtr<RenderNodePattern>());
    ASSERT_NE(frameNode, nullptr);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    SizeF contentSize(100, 100);
    geometryNode->SetContentSize(contentSize);
    ASSERT_NE(geometryNode, nullptr);
    auto renderNodePattern = frameNode->GetPattern<RenderNodePattern>();
    ASSERT_NE(renderNodePattern, nullptr);
    auto renderNodeLayoutProperty = renderNodePattern->GetLayoutProperty<RenderNodeLayoutProperty>();
    ASSERT_NE(renderNodeLayoutProperty, nullptr);

    auto renderNodeLayoutAlgorithm = AceType::MakeRefPtr<RenderNodeLayoutAlgorithm>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    renderNodeLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(geometryNode->GetFrameSize(), SizeF(0, 0));

    SizeF frameSize(200, 200);
    geometryNode->SetFrameSize(frameSize);
    renderNodeLayoutAlgorithm->Layout(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(geometryNode->GetContentOffset(), OffsetF(0, 0));
}
}
