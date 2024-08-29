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
#include "core/components_ng/pattern/option/option_accessibility_property.h"
#include "core/components_ng/pattern/option/option_layout_algorithm.h"
#include "core/components_ng/pattern/option/option_pattern.h"
#include "core/components_ng/pattern/option/option_view.h"
#include "core/components_ng/property/geometry_property.h"
#include "core/components_ng/property/measure_property.h"

#include "core/components_ng/pattern/web/web_paint_method.h"
#include "core/components_ng/pattern/web/web_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class WebPaintMethodTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPaintMethodTest::SetUpTestCase()
{
}

void WebPaintMethodTest::TearDownTestCase()
{
}

void WebPaintMethodTest::SetUp() {}
void WebPaintMethodTest::TearDown() {}

/**
 * @tc.name: GetForegroundDrawFunction
 * @tc.desc: Test GetForegroundDrawFunction.
 * @tc.type: FUNC
 */
HWTEST_F(WebPaintMethodTest, GetForegroundDrawFunction, TestSize.Level1)
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

    auto paintMethod = AceType::DynamicCast<WebPaintMethod>(webPattern->CreateNodePaintMethod());
    EXPECT_NE(paintMethod, nullptr);
    EXPECT_NE(paintMethod->renderSuface_, nullptr);
    auto paintProperty = webPattern->CreatePaintProperty();
    PaintWrapper paintWrapper(frameNode->GetRenderContext(), frameNode->GetGeometryNode(), paintProperty);
    auto drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(*mockSurface, DrawBuffer(_, _)).WillRepeatedly(Return());
    drawFunction(rsCanvas);
    paintMethod = nullptr;
    drawFunction(rsCanvas);
#endif
}
}