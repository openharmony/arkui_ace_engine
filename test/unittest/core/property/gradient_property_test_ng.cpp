/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#define private public
#define protected public
#include "frameworks/core/components_ng/property/gradient_property.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const Dimension TEST_LENGTH1 = 10.0_vp;
const Dimension TEST_LENGTH2 = 15.0_vp;
const Dimension TEST_LENGTH3 = 20.0_vp;
const Dimension TEST_LENGTH4 = 25.0_vp;
const Dimension TEST_LENGTH5 = 30.0_vp;
const Dimension TEST_LENGTH6 = 35.0_vp;

void Result(const GradientDirection x, const GradientDirection y, const Gradient gradient)
{
    std::string str = "";
    if (x == GradientDirection::LEFT) {
        if (y == GradientDirection::TOP) {
            str = GradientJsonUtils::LinearGradientToJson(gradient)->GetString("direction");
            EXPECT_EQ(str, "GradientDirection.LeftTop");
        } else if (y == GradientDirection::BOTTOM) {
            str = GradientJsonUtils::LinearGradientToJson(gradient)->GetString("direction");
            EXPECT_EQ(str, "GradientDirection.LeftBottom");
        } else {
            str = GradientJsonUtils::LinearGradientToJson(gradient)->GetString("direction");
            EXPECT_EQ(str, "GradientDirection.Left");
        }
    } else if (x == GradientDirection::RIGHT) {
        if (y == GradientDirection::TOP) {
            str = GradientJsonUtils::LinearGradientToJson(gradient)->GetString("direction");
            EXPECT_EQ(str, "GradientDirection.RightTop");
        } else if (y == GradientDirection::BOTTOM) {
            str = GradientJsonUtils::LinearGradientToJson(gradient)->GetString("direction");
            EXPECT_EQ(str, "GradientDirection.RightBottom");
        } else {
            str = GradientJsonUtils::LinearGradientToJson(gradient)->GetString("direction");
            EXPECT_EQ(str, "GradientDirection.Right");
        }
    } else {
        if (y == GradientDirection::TOP) {
            str = GradientJsonUtils::LinearGradientToJson(gradient)->GetString("direction");
            EXPECT_EQ(str, "GradientDirection.Top");
        } else if (y == GradientDirection::BOTTOM) {
            str = GradientJsonUtils::LinearGradientToJson(gradient)->GetString("direction");
            EXPECT_EQ(str, "GradientDirection.Bottom");
        } else {
            str = GradientJsonUtils::LinearGradientToJson(gradient)->GetString("direction");
            EXPECT_EQ(str, "GradientDirection.None");
        }
    }
}
} // namespace

class GradientPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: AccessibilityPropertyTest001
 * @tc.desc: LinearGradientToJson
 * @tc.type: FUNC
 */
HWTEST_F(GradientPropertyTestNg, gradientPropertyTest001, TestSize.Level1)
{
    Gradient gradient = Gradient();
    gradient.type_ = GradientType::RADIAL;
    auto linearJson = GradientJsonUtils::LinearGradientToJson(gradient);
    EXPECT_TRUE(linearJson);
    
    gradient.type_ = GradientType::LINEAR;
    linearJson = GradientJsonUtils::LinearGradientToJson(gradient);
    auto str = linearJson->GetString("angle");
    EXPECT_EQ(str, "");

    LinearGradient linearGradient;
    linearGradient.angle = std::make_optional(2.00_vp);
    linearGradient.linearX = std::make_optional(GradientDirection::TOP);
    linearGradient.linearY = std::make_optional(GradientDirection::LEFT);
    linearGradient.x1 = std::make_optional(TEST_LENGTH1);
    linearGradient.y1 = std::make_optional(TEST_LENGTH2);
    linearGradient.x2 = std::make_optional(TEST_LENGTH3);
    linearGradient.y2 = std::make_optional(TEST_LENGTH4);
    gradient.SetLinearGradient(linearGradient);

    std::vector<GradientDirection> linearX;
    linearX.push_back(GradientDirection::LEFT);
    linearX.push_back(GradientDirection::RIGHT);
    linearX.push_back(GradientDirection::TOP);
    std::vector<GradientDirection> linearY;
    linearY.push_back(GradientDirection::TOP);
    linearY.push_back(GradientDirection::BOTTOM);
    linearY.push_back(GradientDirection::LEFT);
    for (auto x : linearX) {
        gradient.linearGradient_->linearX = x;
        for (auto y : linearY) {
            gradient.linearGradient_->linearY = y;
            Result(x, y, gradient);
        }
    }
}

HWTEST_F(GradientPropertyTestNg, gradientPropertyTest002, TestSize.Level1)
{
    Gradient gradient = Gradient();
    gradient.type_ = GradientType::RADIAL;
    auto sweepJson = GradientJsonUtils::SweepGradientToJson(gradient);
    EXPECT_TRUE(sweepJson);
    
    gradient.type_ = GradientType::SWEEP;
    sweepJson = GradientJsonUtils::SweepGradientToJson(gradient);
    auto str = sweepJson->GetString("start");
    EXPECT_EQ(str, "");

    SweepGradient sweepGradient;
    sweepGradient.centerX = std::make_optional(TEST_LENGTH1);
    sweepGradient.centerY = std::make_optional(TEST_LENGTH2);
    sweepGradient.startAngle = std::make_optional(TEST_LENGTH3);
    sweepGradient.endAngle = std::make_optional(TEST_LENGTH4);
    sweepGradient.rotation = std::make_optional(TEST_LENGTH5);
    gradient.SetSweepGradient(sweepGradient);
    sweepJson = GradientJsonUtils::SweepGradientToJson(gradient);
    str = sweepJson->GetString("start");
    EXPECT_EQ(str, TEST_LENGTH3.ToString());
    str = sweepJson->GetString("end");
    EXPECT_EQ(str, TEST_LENGTH4.ToString());
}

HWTEST_F(GradientPropertyTestNg, gradientPropertyTest003, TestSize.Level1)
{
    Gradient gradient = Gradient();
    gradient.type_ = GradientType::SWEEP;
    auto radialJson = GradientJsonUtils::RadialGradientToJson(gradient);
    EXPECT_TRUE(radialJson);
    
    gradient.type_ = GradientType::RADIAL;
    radialJson = GradientJsonUtils::RadialGradientToJson(gradient);
    auto str = radialJson->GetString("radius");
    EXPECT_EQ(str, "");

    GradientColor color(Color::BLACK);
    gradient.AddColor(color);
    RadialGradient radialGradient;
    radialGradient.radialSizeType = std::make_optional(RadialSizeType::CLOSEST_CORNER);
    radialGradient.radialShape = std::make_optional(RadialShapeType::CIRCLE);
    radialGradient.radialHorizontalSize = std::make_optional(TEST_LENGTH1);
    radialGradient.radialVerticalSize = std::make_optional(TEST_LENGTH2);
    radialGradient.radialCenterX = std::make_optional(TEST_LENGTH3);
    radialGradient.radialCenterY = std::make_optional(TEST_LENGTH4);
    radialGradient.fRadialCenterX = std::make_optional(TEST_LENGTH5);
    radialGradient.fRadialCenterY = std::make_optional(TEST_LENGTH6);
    gradient.SetRadialGradient(radialGradient);
    radialJson = GradientJsonUtils::RadialGradientToJson(gradient);
    str = radialJson->GetString("radius");
    EXPECT_EQ(str, TEST_LENGTH2.ToString());
    EXPECT_EQ(gradient.colors_.size(), 1);
    gradient.ClearColors();
}

/**
 * @tc.name: gradientPropertyTest004
 * @tc.desc: LinearGradientToJson
 * @tc.type: FUNC
 */
HWTEST_F(GradientPropertyTestNg, gradientPropertyTest004, TestSize.Level1)
{
    Gradient gradient = Gradient();
    gradient.type_ = GradientType::RADIAL;
    auto linearJson = GradientJsonUtils::LinearGradientToJson(gradient);
    EXPECT_TRUE(linearJson);

    gradient.type_ = GradientType::LINEAR;
    linearJson = GradientJsonUtils::LinearGradientToJson(gradient);
    auto str = linearJson->GetString("angle");
    EXPECT_EQ(str, "");

    LinearGradient linearGradient;
    gradient.SetLinearGradient(linearGradient);
    linearJson = GradientJsonUtils::LinearGradientToJson(gradient);
    str = linearJson->GetString("angle");
    EXPECT_EQ(str, "");
    str = linearJson->GetString("direction");
    EXPECT_EQ(str, "GradientDirection.None");
}

/**
 * @tc.name: gradientPropertyTest005
 * @tc.desc: LinearGradientToJson
 * @tc.type: FUNC
 */
HWTEST_F(GradientPropertyTestNg, gradientPropertyTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Gradient and set type != SWEEP.
     */
    Gradient gradient = Gradient();
    gradient.type_ = GradientType::RADIAL;
    auto sweepJson = GradientJsonUtils::SweepGradientToJson(gradient);
    EXPECT_TRUE(sweepJson);

    /**
     * @tc.steps: step1. set type == SWEEP.
     */
    gradient.type_ = GradientType::SWEEP;
    sweepJson = GradientJsonUtils::SweepGradientToJson(gradient);
    auto str = sweepJson->GetString("start");
    EXPECT_EQ(str, "");

    /**
     * @tc.steps: step3. set radialCenterX  false and radialCenterY false.
     */
    SweepGradient sweepGradient;
    gradient.SetSweepGradient(sweepGradient);
    sweepJson = GradientJsonUtils::SweepGradientToJson(gradient);
    auto jsonTemp = sweepJson->GetValue("center");
    str = jsonTemp->GetString("0");
    EXPECT_EQ(str, "");
    str = jsonTemp->GetString("1");
    EXPECT_EQ(str, "");

    /**
     * @tc.steps: step4. set radialCenterX  false and radialCenterY true.
     */
    SweepGradient sweepGradient1;
    sweepGradient1.centerY = std::make_optional(TEST_LENGTH2);
    gradient.SetSweepGradient(sweepGradient1);
    sweepJson = GradientJsonUtils::SweepGradientToJson(gradient);
    jsonTemp = sweepJson->GetValue("center");
    str = jsonTemp->GetString("0");
    EXPECT_EQ(str, "");
    str = jsonTemp->GetString("1");
    EXPECT_EQ(str, "");

    /**
     * @tc.steps: step5. set radialCenterX  true and radialCenterY false.
     */
    SweepGradient sweepGradient2;
    sweepGradient2.centerX = std::make_optional(TEST_LENGTH1);
    gradient.SetSweepGradient(sweepGradient2);
    sweepJson = GradientJsonUtils::SweepGradientToJson(gradient);
    jsonTemp = sweepJson->GetValue("center");
    str = jsonTemp->GetString("0");
    EXPECT_EQ(str, "");
    str = jsonTemp->GetString("1");
    EXPECT_EQ(str, "");

    /**
     * @tc.steps: step6. set radialCenterX  true and radialCenterY true.
     */
    sweepGradient.centerX = std::make_optional(TEST_LENGTH1);
    sweepGradient.centerY = std::make_optional(TEST_LENGTH2);
    gradient.SetSweepGradient(sweepGradient);
    sweepJson = GradientJsonUtils::SweepGradientToJson(gradient);
    jsonTemp = sweepJson->GetValue("center");
    str = jsonTemp->GetString("0");
    EXPECT_EQ(str, TEST_LENGTH1.ToString());
    str = jsonTemp->GetString("1");
    EXPECT_EQ(str, TEST_LENGTH2.ToString());
    str = sweepJson->GetString("start");
    EXPECT_EQ(str, "");
    str = sweepJson->GetString("end");
    EXPECT_EQ(str, "");
}

/**
 * @tc.name: gradientPropertyTest006
 * @tc.desc: LinearGradientToJson
 * @tc.type: FUNC
 */
HWTEST_F(GradientPropertyTestNg, gradientPropertyTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Gradient and set type != RADIAL.
     */
    Gradient gradient = Gradient();
    gradient.type_ = GradientType::SWEEP;
    auto radialJson = GradientJsonUtils::RadialGradientToJson(gradient);
    EXPECT_TRUE(radialJson);

    /**
     * @tc.steps: step1. Set type == RADIAL.
     */
    gradient.type_ = GradientType::RADIAL;
    radialJson = GradientJsonUtils::RadialGradientToJson(gradient);
    auto str = radialJson->GetString("radius");
    EXPECT_EQ(str, "");

    /**
     * @tc.steps: step3. set radialCenterX false and radialCenterY false.
     */
    GradientColor color(Color::BLACK);
    gradient.AddColor(color);
    RadialGradient radialGradient;
    gradient.SetRadialGradient(radialGradient);
    radialJson = GradientJsonUtils::RadialGradientToJson(gradient);
    auto jsonTemp = radialJson->GetValue("center");
    str = jsonTemp->GetString("0");
    EXPECT_EQ(str, "");
    str = jsonTemp->GetString("1");
    EXPECT_EQ(str, "");

    /**
     * @tc.steps: step4. set radialCenterX true and radialCenterY false.
     */
    RadialGradient radialGradient1;
    radialGradient1.radialCenterX = std::make_optional(TEST_LENGTH3);
    gradient.SetRadialGradient(radialGradient1);
    radialJson = GradientJsonUtils::RadialGradientToJson(gradient);
    jsonTemp = radialJson->GetValue("center");
    str = jsonTemp->GetString("0");
    EXPECT_EQ(str, "");
    str = jsonTemp->GetString("1");
    EXPECT_EQ(str, "");

    /**
     * @tc.steps: step5. set radialCenterX false and radialCenterY true.
     */
    RadialGradient radialGradient2;
    radialGradient2.radialCenterY = std::make_optional(TEST_LENGTH4);
    gradient.SetRadialGradient(radialGradient2);
    radialJson = GradientJsonUtils::RadialGradientToJson(gradient);
    jsonTemp = radialJson->GetValue("center");
    str = jsonTemp->GetString("0");
    EXPECT_EQ(str, "");
    str = jsonTemp->GetString("1");
    EXPECT_EQ(str, "");

    /**
     * @tc.steps: step6. set radialCenterX true and radialCenterY true.
     */
    radialGradient.radialCenterX = std::make_optional(TEST_LENGTH3);
    radialGradient.radialCenterY = std::make_optional(TEST_LENGTH4);
    gradient.SetRadialGradient(radialGradient);
    radialJson = GradientJsonUtils::RadialGradientToJson(gradient);
    jsonTemp = radialJson->GetValue("center");
    str = jsonTemp->GetString("0");
    EXPECT_EQ(str, TEST_LENGTH3.ToString());
    str = jsonTemp->GetString("1");
    EXPECT_EQ(str, TEST_LENGTH4.ToString());
    str = radialJson->GetString("radius");
    EXPECT_EQ(str, "");
}
} // namespace OHOS::Ace::NG
