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

#include "test/unittest/core/base/view_abstract_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float SPATIAL_EFFECT_LEFT_TOP_X = 1.0f;
constexpr float SPATIAL_EFFECT_LEFT_TOP_Y = 2.0f;
constexpr float SPATIAL_EFFECT_LEFT_TOP_Z = 3.0f;
constexpr float SPATIAL_EFFECT_RIGHT_TOP_X = 4.0f;
constexpr float SPATIAL_EFFECT_RIGHT_TOP_Y = 5.0f;
constexpr float SPATIAL_EFFECT_RIGHT_TOP_Z = 6.0f;
constexpr float SPATIAL_EFFECT_LEFT_BOTTOM_X = 7.0f;
constexpr float SPATIAL_EFFECT_LEFT_BOTTOM_Y = 8.0f;
constexpr float SPATIAL_EFFECT_LEFT_BOTTOM_Z = 9.0f;
constexpr float SPATIAL_EFFECT_RIGHT_BOTTOM_X = 10.0f;
constexpr float SPATIAL_EFFECT_RIGHT_BOTTOM_Y = 11.0f;
constexpr float SPATIAL_EFFECT_RIGHT_BOTTOM_Z = 12.0f;
constexpr float SPATIAL_EFFECT_OCCLUSION_WEIGHT = 0.6f;

SpatialEffectParams CreateSpatialEffectParams()
{
    SpatialEffectParams params;
    DepthPosition position;
    position.leftTop = { SPATIAL_EFFECT_LEFT_TOP_X, SPATIAL_EFFECT_LEFT_TOP_Y, SPATIAL_EFFECT_LEFT_TOP_Z };
    position.rightTop = { SPATIAL_EFFECT_RIGHT_TOP_X, SPATIAL_EFFECT_RIGHT_TOP_Y, SPATIAL_EFFECT_RIGHT_TOP_Z };
    position.leftBottom = { SPATIAL_EFFECT_LEFT_BOTTOM_X, SPATIAL_EFFECT_LEFT_BOTTOM_Y, SPATIAL_EFFECT_LEFT_BOTTOM_Z };
    position.rightBottom = {
        SPATIAL_EFFECT_RIGHT_BOTTOM_X, SPATIAL_EFFECT_RIGHT_BOTTOM_Y, SPATIAL_EFFECT_RIGHT_BOTTOM_Z
    };
    params.position = position;
    params.occlusionWeight = SPATIAL_EFFECT_OCCLUSION_WEIGHT;
    return params;
}
} // namespace

class ViewAbstractSpatialEffectTestNg : public testing::Test {};

/**
 * @tc.name: SetSpatialEffect
 * @tc.desc: Test ViewAbstract stores spatial effect params on render context when frame node is provided.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractSpatialEffectTestNg, SetSpatialEffect, TestSize.Level1)
{
    auto frameNode = AceType::RawPtr(FRAME_NODE_REGISTER);
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    SpatialEffectParams params = CreateSpatialEffectParams();
    ViewAbstract::SetSpatialEffect(frameNode, params);
    ASSERT_TRUE(renderContext->GetSpatialEffect().has_value());
    EXPECT_EQ(renderContext->GetSpatialEffect().value(), params);
}

/**
 * @tc.name: SetSpatialEffectWithNullopt
 * @tc.desc: Test ViewAbstractModelStatic resets spatial effect when the optional value is empty.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractSpatialEffectTestNg, SetSpatialEffectWithNullopt, TestSize.Level1)
{
    auto frameNode = AceType::RawPtr(FRAME_NODE_REGISTER);
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    SpatialEffectParams params = CreateSpatialEffectParams();
    ViewAbstractModelStatic::SetSpatialEffect(frameNode, params);
    ASSERT_TRUE(renderContext->GetSpatialEffect().has_value());
    ViewAbstractModelStatic::SetSpatialEffect(frameNode, std::nullopt);
    EXPECT_FALSE(renderContext->GetSpatialEffect().has_value());
}
} // namespace OHOS::Ace::NG
