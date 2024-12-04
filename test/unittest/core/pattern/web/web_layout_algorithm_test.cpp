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

#include <memory>

#define private public

#include "gtest/gtest.h"

#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/render/mock_render_surface.h"
#include "test/mock/core/render/mock_rosen_render_surface.h"

#include "base/geometry/ng/rect_t.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/property/geometry_property.h"
#include "core/components_ng/property/measure_property.h"

#include "core/components_ng/pattern/web/web_paint_method.h"
#include "core/components_ng/pattern/web/web_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
    constexpr float FULL_SCREEN_WIDTH = 720.0f;
    constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
    const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
}

class WebLayoutAlgorithmTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebLayoutAlgorithmTest::SetUpTestCase()
{
}

void WebLayoutAlgorithmTest::TearDownTestCase()
{
}

void WebLayoutAlgorithmTest::SetUp() {}
void WebLayoutAlgorithmTest::TearDown() {}

/**
 * @tc.name: MeasureTest001
 * @tc.desc: Test Web Measure.
 * @tc.type: FUNC
 */
HWTEST_F(WebLayoutAlgorithmTest, MeasureTest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);

    auto mockSurface = AceType::MakeRefPtr<MockRosenRenderSurface>();
    webPattern->renderSurface_ = mockSurface;

    auto webLayoutAlgorithm = AceType::DynamicCast<WebLayoutAlgorithm>(webPattern->CreateLayoutAlgorithm());
    EXPECT_NE(webLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProperty = frameNode->GetLayoutProperty();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, layoutProperty);

    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    
    webLayoutAlgorithm->Measure(nullptr);
#endif
}

/**
 * @tc.name: IsValidRootLayer001
 * @tc.desc: Test Web IsValidRootLayer.
 * @tc.type: FUNC
 */
HWTEST_F(WebLayoutAlgorithmTest, IsValidRootLayer001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);

    auto mockSurface = AceType::MakeRefPtr<MockRosenRenderSurface>();
    webPattern->renderSurface_ = mockSurface;

    auto webLayoutAlgorithm = AceType::DynamicCast<WebLayoutAlgorithm>(webPattern->CreateLayoutAlgorithm());
    EXPECT_NE(webLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
    bool result = webLayoutAlgorithm->IsValidRootLayer(-1, RenderMode::SYNC_RENDER);
    EXPECT_FALSE(result);

    result = webLayoutAlgorithm->IsValidRootLayer(10000, RenderMode::SYNC_RENDER);
    EXPECT_TRUE(result);

    result = webLayoutAlgorithm->IsValidRootLayer(500000, RenderMode::ASYNC_RENDER);
    EXPECT_FALSE(result);

    result = webLayoutAlgorithm->IsValidRootLayer(-1, RenderMode::ASYNC_RENDER);
    EXPECT_FALSE(result);

    result = webLayoutAlgorithm->IsValidRootLayer(1000, RenderMode::ASYNC_RENDER);
    EXPECT_TRUE(result);

    result = webLayoutAlgorithm->IsValidRootLayer(9000, RenderMode::ASYNC_RENDER);
    EXPECT_FALSE(result);
#endif
}
}