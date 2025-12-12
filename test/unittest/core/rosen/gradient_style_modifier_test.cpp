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
#include "ui/properties/ui_material.h"

#include "core/components_ng/render/adapter/gradient_style_modifier.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
constexpr double MAX_COLOR_STOP = 100.0;
constexpr double COLOR_STOP_SECOND = 101.0;
constexpr double COLOR_STOP_EPSILON_1 = 0.00001;
constexpr double COLOR_STOP_EPSILON_2 = 0.00002;
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
    EXPECT_EQ(outputGradient.GetColors().at(0).GetColor().GetColorSpace(), ColorSpace::SRGB);
}

/**
 * @tc.name: GetGradient001
 * @tc.desc: GetGradient
 * @tc.type: FUNC
 */
HWTEST_F(GradientStyleModifierTest, GetGradient001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and init Gradient.
     */
    Gradient gradient;
    GradientColor colorBegin;
    GradientColor colorEnd;
    colorBegin.SetColor(Color::BLUE);
    colorBegin.SetDimension(Dimension(0, DimensionUnit::PERCENT));
    colorEnd.SetColor(Color::RED);
    colorEnd.SetDimension(Dimension(COLOR_STOP_SECOND, DimensionUnit::PERCENT));
    gradient.AddColor(colorBegin);
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

    /**
     * @tc.steps: step4. check last stop.
     * @tc.expected: last stop dimension is 100
     */
    auto curGradient = modifier->GetGradient();
    auto gradientColor = curGradient.GetColors();
    auto lastColorStop = gradientColor[1].GetDimension().Value();
    EXPECT_EQ(lastColorStop, 100);
}

/**
 * @tc.name: ColorStopAnimatableArithmeticIsEqual001
 * @tc.desc: ColorStopAnimatableArithmetic::IsEqual
 * @tc.type: FUNC
 */
HWTEST_F(GradientStyleModifierTest, ColorStopAnimatableArithmeticIsEqual001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and init Gradient1.
     */
    Gradient gradient_1;
    GradientColor colorBegin;
    GradientColor colorEnd;
    colorBegin.SetDimension(Dimension(COLOR_STOP_EPSILON_1, DimensionUnit::PERCENT));
    colorEnd.SetDimension(Dimension(COLOR_STOP_EPSILON_1, DimensionUnit::PERCENT));
    gradient_1.AddColor(colorBegin);
    gradient_1.AddColor(colorEnd);
    ColorStopAnimatableArithmetic colorStop_1(gradient_1);

    /**
     * @tc.steps: step2. Create and init Gradient2.
     */
    Gradient gradient_2;
    GradientColor colorFirst;
    GradientColor colorLast;
    colorFirst.SetDimension(Dimension(COLOR_STOP_EPSILON_2, DimensionUnit::PERCENT));
    colorLast.SetDimension(Dimension(COLOR_STOP_EPSILON_2, DimensionUnit::PERCENT));
    gradient_2.AddColor(colorFirst);
    gradient_2.AddColor(colorLast);
    ColorStopAnimatableArithmetic colorStop_2(gradient_2);
    
    /**
     * @tc.steps: step3. check isEqual.
     * @tc.expected: isEqual is false
     */
    auto isEqual = true;
    isEqual = colorStop_1.IsEqual(colorStop_2);
    EXPECT_EQ(isEqual, false);
}
} // namespace OHOS::Ace::NG