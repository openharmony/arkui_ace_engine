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

#include "gtest/gtest.h"
#include "core/components_ng/render/adapter/gradient_style_modifier.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
constexpr double MAX_COLOR_STOP = 100.0;
}

class GradientStyleModifierTest : public testing::Test {
};

/**
 * @tc.name: gradientPropertyTest007
 * @tc.desc: LinearGradientToJson
 * @tc.type: FUNC
 */
HWTEST_F(GradientStyleModifierTest, gradientStyleModifierTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and init Gradient.
     */
    Gradient gradient;
    GradientColor colorBegin;
    GradientColor colorEnd;
    colorBegin.SetColor(Color::BLACK);
    colorBegin.SetDimension(Dimension(0, DimensionUnit::PERCENT));
    colorEnd.SetColor(Color::RED);
    colorEnd.SetDimension(Dimension(MAX_COLOR_STOP, DimensionUnit::PERCENT));
    gradient.AddColor(colorEnd);
    /**
     * @tc.steps: step2. create animatable color and color stop .
     */
    ColorAnimatableArithmetic colors(gradient);
    ColorStopAnimatableArithmetic colorStops(gradient);
    /**
     * @tc.steps: step3. padding color and color stop .
     */
    auto context = RosenRenderContext();
    auto modifier = std::make_shared<GradientStyleModifier>(AceType::WeakClaim(&context));
    modifier->SetGradient(gradient);
    modifier->PaddingColorStops(colorStops, true);
    auto outputGradient = modifier->GetGradient();
    /**
     * @tc.steps: step4. check data size.
     */
    EXPECT_EQ(outputGradient.GetColors().size(), gradient.GetColors().size());
}
} // namespace OHOS::Ace::NG