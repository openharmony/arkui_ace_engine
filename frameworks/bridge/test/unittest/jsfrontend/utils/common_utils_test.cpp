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

#include "base/utils/string_utils.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/js_frontend/engine/common/base_animation_bridge.h"
#include "frameworks/bridge/js_frontend/engine/common/js_constants.h"
#include "frameworks/core/animation/curve.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::Framework {
namespace {
constexpr double SIZE_VALUE_ZERO = 0;
constexpr double SIZE_VALUE_TEN = 10;
constexpr double SIZE_VALUE_FIFTY = 50;
constexpr double SIZE_VALUE_HUNDRED = 100;
constexpr float ANIMATION_ZERO_VALUE = 0.0f;
constexpr float ANIMATION_ONE_VALUE = 1.0f;
constexpr float ANIMATION_CUBIC_VALUE_ONE = 0.000295256f;
constexpr float ANIMATION_CUBIC_VALUE_TWO = 0.801992f;
constexpr float ANIMATION_SPRING_VALUE = -0.193207f;
const std::string ANIMATION_EASING_CUBIC_EASE = "cubic-bezier(0.25, 0.1, 0.25, 1.0)";
const std::string ANIMATION_EASING_SPRING = "spring(1.0, 1.0, 1.0, 1.0)";
const std::string ANIMATION_EASING_SPRING_MOTION = "spring-motion(1.0, 1.0, 1.0)";
const std::string ANIMATION_EASING_RESPONSIVE = "responsive-spring-motion(1.0, 1.0, 1.0)";
const std::string ANIMATION_EASING_EASE = "ease";
const std::string ANIMATION_EASING_STEPS_START = "steps(1, start)";
const std::string ANIMATION_EASING_STEPS_END = "steps(1, end)";
const std::string ANIMATION_EASING_CUSTOM = "customCallback";
} // namespace

class CommonUtilsTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CommonUtilsTest::SetUpTestCase() {}
void CommonUtilsTest::TearDownTestCase() {}
void CommonUtilsTest::SetUp() {}
void CommonUtilsTest::TearDown() {}

/**
 * @tc.name: CommonUtilsTest001
 * @tc.desc: BackgroundPosition parse
 * @tc.type: FUNC
 */
HWTEST_F(CommonUtilsTest, CommonUtilsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parse the param contain "top".
     * @tc.expected: step1. The value of the params are as expected.
     */
    BackgroundImagePosition backgroundImagePosition;
    EXPECT_TRUE(ParseBackgroundImagePosition("top", backgroundImagePosition));
    EXPECT_EQ(backgroundImagePosition.GetSizeValueX(), SIZE_VALUE_FIFTY);
    EXPECT_EQ(BackgroundImagePositionType::PERCENT, backgroundImagePosition.GetSizeTypeX());
    EXPECT_EQ(backgroundImagePosition.GetSizeValueY(), SIZE_VALUE_ZERO);
    EXPECT_EQ(BackgroundImagePositionType::PERCENT, backgroundImagePosition.GetSizeTypeY());

    /**
     * @tc.steps: step2. parse the param which is null.
     * @tc.expected: step2. The value of the params are as expected.
     */
    EXPECT_TRUE(ParseBackgroundImagePosition("", backgroundImagePosition));
    EXPECT_EQ(backgroundImagePosition.GetSizeValueX(), SIZE_VALUE_FIFTY);
    EXPECT_EQ(BackgroundImagePositionType::PERCENT, backgroundImagePosition.GetSizeTypeX());
    EXPECT_EQ(backgroundImagePosition.GetSizeValueY(), SIZE_VALUE_FIFTY);
    EXPECT_EQ(BackgroundImagePositionType::PERCENT, backgroundImagePosition.GetSizeTypeY());
}

/**
 * @tc.name: CommonUtilsTest002
 * @tc.desc: Animation steps parse check
 * @tc.type: FUNC
 */
HWTEST_F(CommonUtilsTest, CommonUtilsTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parse the param of steps curve.
     * @tc.expected: step1. steps curve parsed success.
     */
    auto stepsCurve = AceType::DynamicCast<StepsCurve>(CreateCurve(ANIMATION_EASING_STEPS_START));
    EXPECT_TRUE(NearEqual(stepsCurve->MoveInternal(0.0), ANIMATION_ONE_VALUE));
    EXPECT_TRUE(NearEqual(stepsCurve->MoveInternal(0.5), ANIMATION_ONE_VALUE));
    stepsCurve = AceType::DynamicCast<StepsCurve>(CreateCurve(ANIMATION_EASING_STEPS_END));
    EXPECT_TRUE(NearEqual(stepsCurve->MoveInternal(0.0), ANIMATION_ZERO_VALUE));
    EXPECT_TRUE(NearEqual(stepsCurve->MoveInternal(1.0), ANIMATION_ONE_VALUE));

    /**
     * @tc.steps: step2. parse the param of cubic curve.
     * @tc.expected: step2. cubic curve parsed success.
     */
    auto cubicCurve = AceType::DynamicCast<CubicCurve>(CreateCurve(ANIMATION_EASING_CUBIC_EASE));
    EXPECT_TRUE(NearEqual(cubicCurve->MoveInternal(0.0), ANIMATION_CUBIC_VALUE_ONE));
    EXPECT_TRUE(NearEqual(cubicCurve->MoveInternal(0.5), ANIMATION_CUBIC_VALUE_TWO));
    cubicCurve = AceType::DynamicCast<CubicCurve>(CreateCurve(ANIMATION_EASING_EASE));
    EXPECT_TRUE(NearEqual(cubicCurve->MoveInternal(0.0), ANIMATION_CUBIC_VALUE_ONE));
    EXPECT_TRUE(NearEqual(cubicCurve->MoveInternal(1.0), ANIMATION_ONE_VALUE));

    /**
     * @tc.steps: step3. parse the param of responsive spring motion.
     * @tc.expected: step3. responsive spring motion parsed success.
     */
    auto responsiveSpringMotion =
        AceType::DynamicCast<ResponsiveSpringMotion>(CreateCurve(ANIMATION_EASING_RESPONSIVE));
    EXPECT_EQ(responsiveSpringMotion->GetResponse(), ANIMATION_ONE_VALUE);
    EXPECT_EQ(responsiveSpringMotion->GetDampingRatio(), ANIMATION_ONE_VALUE);
    EXPECT_EQ(responsiveSpringMotion->GetBlendDuration(), ANIMATION_ONE_VALUE);

    /**
     * @tc.steps: step4. parse the param of spring curve.
     * @tc.expected: step4. spring curve parsed success.
     */
    auto springCurve = AceType::DynamicCast<SpringCurve>(CreateCurve(ANIMATION_EASING_SPRING));
    EXPECT_TRUE(NearEqual(springCurve->MoveInternal(0.0), ANIMATION_ZERO_VALUE));
    EXPECT_TRUE(NearEqual(springCurve->MoveInternal(1.0), ANIMATION_SPRING_VALUE));

    /**
     * @tc.steps: step5. parse the param of spring motion.
     * @tc.expected: step5. spring motion parsed success.
     */
    auto springMotion = AceType::DynamicCast<ResponsiveSpringMotion>(CreateCurve(ANIMATION_EASING_SPRING_MOTION));
    EXPECT_EQ(springMotion->GetResponse(), ANIMATION_ONE_VALUE);
    EXPECT_EQ(springMotion->GetDampingRatio(), ANIMATION_ONE_VALUE);
    EXPECT_EQ(springMotion->GetBlendDuration(), ANIMATION_ONE_VALUE);
}

/**
 * @tc.name: CommonUtilsTest003
 * @tc.desc: BackgroundImageSize parse
 * @tc.type: FUNC
 */
HWTEST_F(CommonUtilsTest, CommonUtilsTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parse the param contain "%", "px" and " ".
     * @tc.expected: step1. The value of the params are as expected.
     */
    BackgroundImageSize bgImgSize;
    EXPECT_TRUE(ParseBackgroundImageSize("50% 50px", bgImgSize));
    EXPECT_EQ(bgImgSize.GetSizeValueX(), SIZE_VALUE_FIFTY);
    EXPECT_EQ(bgImgSize.GetSizeTypeX(), BackgroundImageSizeType::PERCENT);
    EXPECT_EQ(bgImgSize.GetSizeValueY(), SIZE_VALUE_FIFTY);
    EXPECT_EQ(bgImgSize.GetSizeTypeY(), BackgroundImageSizeType::LENGTH);

    /**
     * @tc.steps: step2. parse the param contain "px", "%" and " ".
     * @tc.expected: step2. The value of the params are as expected.
     */
    EXPECT_TRUE(ParseBackgroundImageSize("50px 50%", bgImgSize));
    EXPECT_EQ(bgImgSize.GetSizeValueX(), SIZE_VALUE_FIFTY);
    EXPECT_EQ(bgImgSize.GetSizeTypeX(), BackgroundImageSizeType::LENGTH);
    EXPECT_EQ(bgImgSize.GetSizeValueY(), SIZE_VALUE_FIFTY);
    EXPECT_EQ(bgImgSize.GetSizeTypeY(), BackgroundImageSizeType::PERCENT);

    /**
     * @tc.steps: step3. parse the param contain " ".
     * @tc.expected: step3. The value of the params are as expected.
     */
    EXPECT_TRUE(ParseBackgroundImageSize("test test", bgImgSize));
    EXPECT_EQ(bgImgSize.GetSizeValueX(), SIZE_VALUE_FIFTY);
    EXPECT_EQ(bgImgSize.GetSizeTypeX(), BackgroundImageSizeType::AUTO);
    EXPECT_EQ(bgImgSize.GetSizeValueY(), SIZE_VALUE_FIFTY);
    EXPECT_EQ(bgImgSize.GetSizeTypeY(), BackgroundImageSizeType::AUTO);
}

/**
 * @tc.name: CommonUtilsTest004
 * @tc.desc: BackgroundImageSize parse
 * @tc.type: FUNC
 */
HWTEST_F(CommonUtilsTest, CommonUtilsTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parse the param contain "px".
     * @tc.expected: step1. The value of the params are as expected.
     */
    BackgroundImageSize bgImgSize;
    EXPECT_TRUE(ParseBackgroundImageSize("50px", bgImgSize));
    EXPECT_EQ(bgImgSize.GetSizeValueX(), SIZE_VALUE_FIFTY);
    EXPECT_EQ(bgImgSize.GetSizeTypeX(), BackgroundImageSizeType::LENGTH);
    EXPECT_EQ(bgImgSize.GetSizeValueY(), SIZE_VALUE_ZERO);
    EXPECT_EQ(bgImgSize.GetSizeTypeY(), BackgroundImageSizeType::AUTO);

    /**
     * @tc.steps: step2. parse the param contain "%".
     * @tc.expected: step2. The value of the params are as expected.
     */
    EXPECT_TRUE(ParseBackgroundImageSize("50%", bgImgSize));
    EXPECT_EQ(bgImgSize.GetSizeValueX(), SIZE_VALUE_FIFTY);
    EXPECT_EQ(bgImgSize.GetSizeTypeX(), BackgroundImageSizeType::PERCENT);
    EXPECT_EQ(bgImgSize.GetSizeValueY(), SIZE_VALUE_ZERO);
    EXPECT_EQ(bgImgSize.GetSizeTypeY(), BackgroundImageSizeType::AUTO);

    /**
     * @tc.steps: step3. parse the param.
     * @tc.expected: step3. The value of the params are as expected.
     */
    EXPECT_TRUE(ParseBackgroundImageSize("test", bgImgSize));
    EXPECT_EQ(bgImgSize.GetSizeValueX(), SIZE_VALUE_FIFTY);
    EXPECT_EQ(bgImgSize.GetSizeTypeX(), BackgroundImageSizeType::AUTO);
    EXPECT_EQ(bgImgSize.GetSizeValueY(), SIZE_VALUE_ZERO);
    EXPECT_EQ(bgImgSize.GetSizeTypeY(), BackgroundImageSizeType::AUTO);

    /**
     * @tc.steps: step4. parse the param which is "auto".
     * @tc.expected: step4. The value of the params are as expected.
     */
    EXPECT_TRUE(ParseBackgroundImageSize("auto", bgImgSize));
    EXPECT_EQ(bgImgSize.GetSizeValueX(), SIZE_VALUE_FIFTY);
    EXPECT_EQ(bgImgSize.GetSizeTypeX(), BackgroundImageSizeType::AUTO);
    EXPECT_EQ(bgImgSize.GetSizeValueY(), SIZE_VALUE_ZERO);
    EXPECT_EQ(bgImgSize.GetSizeTypeY(), BackgroundImageSizeType::AUTO);

    /**
     * @tc.steps: step5. parse the param which is "contain".
     * @tc.expected: step5. The value of the params are as expected.
     */
    EXPECT_TRUE(ParseBackgroundImageSize("contain", bgImgSize));
    EXPECT_EQ(bgImgSize.GetSizeValueX(), SIZE_VALUE_FIFTY);
    EXPECT_EQ(bgImgSize.GetSizeTypeX(), BackgroundImageSizeType::CONTAIN);
    EXPECT_EQ(bgImgSize.GetSizeValueY(), SIZE_VALUE_ZERO);
    EXPECT_EQ(bgImgSize.GetSizeTypeY(), BackgroundImageSizeType::AUTO);

    /**
     * @tc.steps: step6. parse the param which is "cover".
     * @tc.expected: step6. The value of the params are as expected.
     */
    EXPECT_TRUE(ParseBackgroundImageSize("cover", bgImgSize));
    EXPECT_EQ(bgImgSize.GetSizeValueX(), SIZE_VALUE_FIFTY);
    EXPECT_EQ(bgImgSize.GetSizeTypeX(), BackgroundImageSizeType::COVER);
    EXPECT_EQ(bgImgSize.GetSizeValueY(), SIZE_VALUE_ZERO);
    EXPECT_EQ(bgImgSize.GetSizeTypeY(), BackgroundImageSizeType::AUTO);
}

/**
 * @tc.name: CommonUtilsTest005
 * @tc.desc: ObjectPosition parse
 * @tc.type: FUNC
 */
HWTEST_F(CommonUtilsTest, CommonUtilsTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parse the param contain "px" and "%".
     * @tc.expected: step1. The value of the params are as expected.
     */
    auto imageObjectPosition = ParseImageObjectPosition("10px 10%");
    EXPECT_EQ(imageObjectPosition.GetSizeValueX(), SIZE_VALUE_TEN);
    EXPECT_EQ(imageObjectPosition.GetSizeTypeX(), BackgroundImagePositionType::PX);
    EXPECT_EQ(imageObjectPosition.GetSizeValueY(), SIZE_VALUE_TEN);
    EXPECT_EQ(imageObjectPosition.GetSizeTypeY(), BackgroundImagePositionType::PERCENT);

    /**
     * @tc.steps: step2. parse the param contain "%" and "px".
     * @tc.expected: step2. The value of the params are as expected.
     */
    imageObjectPosition = ParseImageObjectPosition("10% 10px");
    EXPECT_EQ(imageObjectPosition.GetSizeValueX(), SIZE_VALUE_TEN);
    EXPECT_EQ(imageObjectPosition.GetSizeTypeX(), BackgroundImagePositionType::PERCENT);
    EXPECT_EQ(imageObjectPosition.GetSizeValueY(), SIZE_VALUE_TEN);
    EXPECT_EQ(imageObjectPosition.GetSizeTypeY(), BackgroundImagePositionType::PX);

    /**
     * @tc.steps: step3. parse the param.
     * @tc.expected: step3. The value of the params are as expected.
     */
    imageObjectPosition = ParseImageObjectPosition("test");
    EXPECT_EQ(imageObjectPosition.GetSizeValueX(), SIZE_VALUE_FIFTY);
    EXPECT_EQ(imageObjectPosition.GetSizeTypeX(), BackgroundImagePositionType::PERCENT);
    EXPECT_EQ(imageObjectPosition.GetSizeValueY(), SIZE_VALUE_FIFTY);
    EXPECT_EQ(imageObjectPosition.GetSizeTypeY(), BackgroundImagePositionType::PERCENT);

    /**
     * @tc.steps: step4. parse the param contain "left" and "bottom".
     * @tc.expected: step4. The value of the params are as expected.
     */
    imageObjectPosition = ParseImageObjectPosition("left bottom");
    EXPECT_EQ(imageObjectPosition.GetSizeValueX(), SIZE_VALUE_ZERO);
    EXPECT_EQ(imageObjectPosition.GetSizeTypeX(), BackgroundImagePositionType::PERCENT);
    EXPECT_EQ(imageObjectPosition.GetSizeValueY(), SIZE_VALUE_HUNDRED);
    EXPECT_EQ(imageObjectPosition.GetSizeTypeY(), BackgroundImagePositionType::PERCENT);

    /**
     * @tc.steps: step5. parse the param contain "right" and "top".
     * @tc.expected: step5. The value of the params are as expected.
     */
    imageObjectPosition = ParseImageObjectPosition("right top");
    EXPECT_EQ(imageObjectPosition.GetSizeValueX(), SIZE_VALUE_HUNDRED);
    EXPECT_EQ(imageObjectPosition.GetSizeTypeX(), BackgroundImagePositionType::PERCENT);
    EXPECT_EQ(imageObjectPosition.GetSizeValueY(), SIZE_VALUE_ZERO);
    EXPECT_EQ(imageObjectPosition.GetSizeTypeY(), BackgroundImagePositionType::PERCENT);
}

/**
 * @tc.name: CommonUtilsTest006
 * @tc.desc: ClipPath prase
 * @tc.type: FUNC
 */
HWTEST_F(CommonUtilsTest, CommonUtilsTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ClipPath ,input a string which contain "inset()" and "margin-box"
     * @tc.expected: step1. The value of the params are as expected.
     */
    auto clipPath = CreateClipPath("inset(margin-box)");
    EXPECT_NE(clipPath, nullptr);
    EXPECT_EQ(clipPath->GetGeometryBoxType(), GeometryBoxType::MARGIN_BOX);
}

/**
 * @tc.name: CommonUtilsTest007
 * @tc.desc: RadialGradient parse
 * @tc.type: FUNC
 */
HWTEST_F(CommonUtilsTest, CommonUtilsTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parse the param.
     * @tc.expected: step1. The value of the params are as expected.
     */
    auto radialGradient = ParseRadialGradientSize("closest-corner");
    EXPECT_EQ(radialGradient, RadialSizeType::CLOSEST_CORNER);
    radialGradient = ParseRadialGradientSize("closest-side");
    EXPECT_EQ(radialGradient, RadialSizeType::CLOSEST_SIDE);
    radialGradient = ParseRadialGradientSize("farthest-corner");
    EXPECT_EQ(radialGradient, RadialSizeType::FARTHEST_CORNER);
    radialGradient = ParseRadialGradientSize("farthest-side");
    EXPECT_EQ(radialGradient, RadialSizeType::FARTHEST_SIDE);
}

/**
 * @tc.name: CommonUtilsTest008
 * @tc.desc: TransitionType parse
 * @tc.type: FUNC
 */
HWTEST_F(CommonUtilsTest, CommonUtilsTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parse the param.
     * @tc.expected: step1. The value of the params are as expected.
     */
    auto transitionType = ParseTransitionType("All");
    EXPECT_EQ(transitionType, TransitionType::ALL);
    transitionType = ParseTransitionType("Insert");
    EXPECT_EQ(transitionType, TransitionType::APPEARING);
    transitionType = ParseTransitionType("Delete");
    EXPECT_EQ(transitionType, TransitionType::DISAPPEARING);
    transitionType = ParseTransitionType("Modify");
    EXPECT_EQ(transitionType, TransitionType::ALL);
}

/**
 * @tc.name: CommonUtilsTest009
 * @tc.desc: Animation CreateCurve step check
 * @tc.type: FUNC
 */
HWTEST_F(CommonUtilsTest, CommonUtilsTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parse the param of Custom curve.
     * @tc.expected: Custom curve parsed success.
     */
    auto customCallback = [](float time) -> float { return time; };
    auto customCurve = AceType::DynamicCast<CustomCurve>(CreateCurve(customCallback));
    ASSERT_NE(customCurve, nullptr);
    EXPECT_TRUE(NearEqual(customCurve->MoveInternal(0.0), ANIMATION_ZERO_VALUE));
    EXPECT_TRUE(NearEqual(customCurve->MoveInternal(1.0), ANIMATION_ONE_VALUE));
    EXPECT_EQ(customCurve->ToString(), ANIMATION_EASING_CUSTOM);
}
} // namespace OHOS::Ace::Framework
