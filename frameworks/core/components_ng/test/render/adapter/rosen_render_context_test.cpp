/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#define protected public
#define private public

#include "render_service_client/core/ui/rs_canvas_node.h"

#include "base/geometry/ng/vector.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/test/mock/pattern/mock_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const float SHADOW_RADIUS_NEGATIVE = -5.0f;
const float SHADOW_RADIUS_ZERO = 0.0f;
const float SHADOW_RADIUS_FIVE = 5.0f;
const float SHADOW_RADIUS_TEN = 10.0f;
} // namespace

class RosenRenderContextTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();
};

void RosenRenderContextTest::SetUpTestCase() {}

void RosenRenderContextTest::TearDownTestCase() {}

void RosenRenderContextTest::SetUp() {}

void RosenRenderContextTest::TearDown() {}

/**
 * @tc.name: RosenRenderContextTest001
 * @tc.desc: Test RosenRenderContext method
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest001, TestSize.Level1)
{
    auto rosenRenderContext = AceType::MakeRefPtr<RosenRenderContext>();
    rosenRenderContext->rsNode_ = Rosen::RSCanvasNode::Create(true);

    rosenRenderContext->OnFrontBlurRadiusUpdate(Dimension(1.0));
    rosenRenderContext->OnOpacityUpdate(1.0);
    rosenRenderContext->OnTransformScaleUpdate(VectorF(1.0f, 1.0f));
    rosenRenderContext->OnTransformTranslateUpdate(Vector3F(1.0f, 1.0f, 1.0f));
    rosenRenderContext->OnTransformRotateUpdate(Vector4F(1.0f, 1.0f, 1.0f, 1.0f));
    rosenRenderContext->OnTransformCenterUpdate(DimensionOffset(Dimension(1.0), Dimension(1.0)));
    EXPECT_NE(rosenRenderContext->rsNode_, nullptr);
}

/**
 * @tc.name: RosenRenderContextTest002
 * @tc.desc: Test RosenRenderContext shadow radius
 * @tc.type: FUNC
 */
HWTEST_F(RosenRenderContextTest, RosenRenderContextTest002, TestSize.Level1)
{
    auto rosenRenderContext = AceType::MakeRefPtr<RosenRenderContext>();
    auto pattern = AceType::MakeRefPtr<MockPattern>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test", 1, pattern);
    rosenRenderContext->SetHostNode(frameNode);
    rosenRenderContext->rsNode_ = Rosen::RSCanvasNode::Create(true);

    // change shadow radius value
    Shadow shadow;
    shadow.SetBlurRadius(SHADOW_RADIUS_FIVE);

    rosenRenderContext->UpdateBackShadow(shadow);
    EXPECT_NE(rosenRenderContext->rsNode_, nullptr);
    EXPECT_TRUE(rosenRenderContext->HasBackShadow());
    EXPECT_EQ(rosenRenderContext->GetBackShadow()->blurRadius_, SHADOW_RADIUS_FIVE);
    EXPECT_EQ(rosenRenderContext->GetBackShadow()->color_, Color::BLACK);
    EXPECT_EQ(rosenRenderContext->GetBackShadow()->offset_, Offset());

    shadow.SetBlurRadius(SHADOW_RADIUS_ZERO);
    rosenRenderContext->UpdateBackShadow(shadow);

    shadow.SetBlurRadius(SHADOW_RADIUS_TEN);
    rosenRenderContext->UpdateBackShadow(shadow);

    shadow.SetBlurRadius(SHADOW_RADIUS_NEGATIVE);
    rosenRenderContext->UpdateBackShadow(shadow);
    EXPECT_TRUE(rosenRenderContext->HasBackShadow());
    EXPECT_EQ(rosenRenderContext->GetBackShadow()->blurRadius_, SHADOW_RADIUS_NEGATIVE);
}
} // namespace OHOS::Ace::NG