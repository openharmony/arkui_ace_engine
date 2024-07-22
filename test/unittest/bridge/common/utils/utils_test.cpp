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

#include "gtest/gtest.h"

#define private public
#define protected public
#include "frameworks/bridge/common/utils/transform_convertor.h"
#include "frameworks/bridge/common/utils/utils.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Framework {
class UtilsTest : public testing::Test {
public:
    static void SetUpTestSuite() {}
    static void TearDownTestSuite() {}
};

/**
 * @tc.name: UtilsTest001
 * @tc.desc: StepsCurveCreator
 * @tc.type: FUNC
 */
HWTEST_F(UtilsTest, UtilsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a string container.
     */
    std::string curve = "";

    /**
     * @tc.steps: step2. Testing illegal values.
     * @tc.expected: return Curves::EASE_IN_OUT.
     */
    EXPECT_EQ(CreateCurve(curve), Curves::EASE_IN_OUT);
    curve = "123)";
    EXPECT_EQ(CreateCurve(curve, false), nullptr);
    curve = "123)";
    EXPECT_EQ(CreateCurve(curve), Curves::EASE_IN_OUT);
    curve = "()";
    EXPECT_EQ(CreateCurve(curve), Curves::EASE_IN_OUT);
    curve = "steps()";
    EXPECT_EQ(CreateCurve(curve), Curves::EASE_IN_OUT);
    curve = "(test)";
    EXPECT_EQ(CreateCurve(curve), Curves::EASE_IN_OUT);
    curve = "steps(1,2,3,4,5)";
    EXPECT_EQ(CreateCurve(curve), Curves::EASE_IN_OUT);
    curve = "steps(0,aaaa)";
    EXPECT_EQ(CreateCurve(curve), Curves::EASE_IN_OUT);
    curve = "abc(1,aaaa)";
    EXPECT_EQ(CreateCurve(curve), Curves::EASE_IN_OUT);
    curve = "steps(1,aaaa)";
    EXPECT_EQ(CreateCurve(curve), Curves::EASE_IN_OUT);
    curve = "steps(1)";
    EXPECT_NE(CreateCurve(curve), nullptr);
    /**
     * @tc.steps: step3. Normal testing
     * @tc.expected: return Curve.
     */
    curve = "steps(1,start)";
    EXPECT_NE(CreateCurve(curve), nullptr);
    curve = "steps(1,end)";
    EXPECT_NE(CreateCurve(curve), nullptr);
    curve = "ease";
    EXPECT_NE(CreateCurve(curve), nullptr);
}

/**
 * @tc.name: UtilsTest002
 * @tc.desc: CubicCurveCreator、 SpringCurveCreator and InterpolatingSpringCreator
 * @tc.type: FUNC
 */
HWTEST_F(UtilsTest, UtilsTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a string container.
     */

    std::string curve = "";
    /**
     * @tc.steps: step2. Testing illegal values.
     * @tc.expected: return Curves::EASE_IN_OUT.
     */

    curve = "cubic-bezier(1,2,3,4,5)";
    EXPECT_EQ(CreateCurve(curve), Curves::EASE_IN_OUT);
    curve = "spring(1,2,3,4,5)";
    EXPECT_EQ(CreateCurve(curve), Curves::EASE_IN_OUT);
    curve = "interpolating-spring(1,2,3,4,5)";
    EXPECT_EQ(CreateCurve(curve), Curves::EASE_IN_OUT);
    curve = "spring-motion(1,2,3,4,5)";
    EXPECT_EQ(CreateCurve(curve), Curves::EASE_IN_OUT);
    curve = "responsive-spring-motion(1,2,3,4,5)";
    EXPECT_EQ(CreateCurve(curve), Curves::EASE_IN_OUT);
    /**
     * @tc.steps: step3. Normal testing
     * @tc.expected: return Curve.
     */

    curve = "cubic-bezier(10,10,10,10)";
    EXPECT_NE(CreateCurve(curve), nullptr);
    curve = "spring(10,10,10,10)";
    EXPECT_NE(CreateCurve(curve), nullptr);
    curve = "interpolating-spring(10,10,10,10)";
    EXPECT_NE(CreateCurve(curve), nullptr);
    curve = "spring-motion(10,10)";
    EXPECT_NE(CreateCurve(curve), nullptr);
    curve = "responsive-spring-motion(10,10)";
    EXPECT_NE(CreateCurve(curve), nullptr);
}

/**
 * @tc.name: UtilsTest003
 * @tc.desc: ParseBackgroundImagePosition
 * @tc.type: FUNC
 */
HWTEST_F(UtilsTest, UtilsTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a string container.
     */

    std::string value = "";
    BackgroundImagePosition backgroundImagePosition;
    /**
     * @tc.steps: step2. Testing illegal values.
     * @tc.expected: return true or false.
     */
    ParseImageObjectPosition(value);
    EXPECT_TRUE(ParseBackgroundImagePosition(value, backgroundImagePosition));
    value = "10";
    ParseImageObjectPosition(value);
    EXPECT_TRUE(ParseBackgroundImagePosition(value, backgroundImagePosition));
    value = "top";
    ParseImageObjectPosition(value);
    EXPECT_TRUE(ParseBackgroundImagePosition(value, backgroundImagePosition));
    value = "10 10";
    ParseImageObjectPosition(value);
    EXPECT_FALSE(ParseBackgroundImagePosition(value, backgroundImagePosition));
    value = "top 10";
    ParseImageObjectPosition(value);
    EXPECT_FALSE(ParseBackgroundImagePosition(value, backgroundImagePosition));
    value = "10 left";
    ParseImageObjectPosition(value);
    EXPECT_FALSE(ParseBackgroundImagePosition(value, backgroundImagePosition));
    value = "top left";
    ParseImageObjectPosition(value);
    EXPECT_TRUE(ParseBackgroundImagePosition(value, backgroundImagePosition));
    value = "left top";
    ParseImageObjectPosition(value);
    value = "center center";
    ParseImageObjectPosition(value);
    EXPECT_TRUE(ParseBackgroundImagePosition(value, backgroundImagePosition));
    /**
     * @tc.steps: step3. Normal testing
     * @tc.expected: return true or false.
     */
    value = "10% 10%";
    ParseImageObjectPosition(value);
    EXPECT_TRUE(ParseBackgroundImagePosition(value, backgroundImagePosition));
    value = "10px 10px";
    ParseImageObjectPosition(value);
    EXPECT_TRUE(ParseBackgroundImagePosition(value, backgroundImagePosition));
}

/**
 * @tc.name: UtilsTest004
 * @tc.desc: ParseRadialGradientSize
 * @tc.type: FUNC
 */
HWTEST_F(UtilsTest, UtilsTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a string container.
     */
    std::string value = "";
    /**
     * @tc.steps: step2. Testing illegal values.
     * @tc.expected: return std::nullopt.
     */
    EXPECT_EQ(ParseRadialGradientSize(value), std::nullopt);
    value = "10 10";
    EXPECT_EQ(ParseRadialGradientSize(value), std::nullopt);
    /**
     * @tc.steps: step3. Normal testing
     * @tc.expected: return RadialSizeType.
     */
    value = "closest-corner";
    EXPECT_EQ(ParseRadialGradientSize(value), RadialSizeType::CLOSEST_CORNER);
}

/**
 * @tc.name: UtilsTest005
 * @tc.desc: ParseRadialGradientSize
 * @tc.type: FUNC
 */
HWTEST_F(UtilsTest, UtilsTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a string container.
     */
    std::string value = "";
    /**
     * @tc.steps: step2. Testing illegal values.
     * @tc.expected: return nullptr.
     */
    EXPECT_EQ(CreateClipPath(value), nullptr);
    value = "test";
    EXPECT_EQ(CreateClipPath(value), nullptr);
    /**
     * @tc.steps: step3. Normal testing
     * @tc.expected: return ClipPath.
     */
    value = "border-box circle(";
    EXPECT_NE(CreateClipPath(value), nullptr);
}

/**
 * @tc.name: UtilsTest006
 * @tc.desc: ParseRadialGradientSize
 * @tc.type: FUNC
 */
HWTEST_F(UtilsTest, UtilsTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a string container.
     */
    std::string value = "";
    BackgroundImageSize bgImgSize;
    /**
     * @tc.steps: step2. Testing illegal values.
     * @tc.expected: return true.
     */
    EXPECT_TRUE(ParseBackgroundImageSize(value, bgImgSize));
    value = "10 10";
    EXPECT_TRUE(ParseBackgroundImageSize(value, bgImgSize));
    value = "10% 10%";
    EXPECT_TRUE(ParseBackgroundImageSize(value, bgImgSize));
    value = "10px 10px";
    EXPECT_TRUE(ParseBackgroundImageSize(value, bgImgSize));
    /**
     * @tc.steps: step3. Normal testing
     * @tc.expected: return true or false.
     */
    value = "contain";
    EXPECT_TRUE(ParseBackgroundImageSize(value, bgImgSize));
    value = "10";
    EXPECT_TRUE(ParseBackgroundImageSize(value, bgImgSize));
    value = "10%";
    EXPECT_TRUE(ParseBackgroundImageSize(value, bgImgSize));
    value = "10px";
    EXPECT_TRUE(ParseBackgroundImageSize(value, bgImgSize));
}

/**
 * @tc.name: UtilsTest007
 * @tc.desc: ParseTransitionType
 * @tc.type: FUNC
 */
HWTEST_F(UtilsTest, UtilsTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a string container.
     */
    std::string value = "";

    /**
     * @tc.steps: step2. Testing illegal values.
     * @tc.expected: return TransitionType::ALL.
     */

    EXPECT_EQ(ParseTransitionType(value), TransitionType::ALL);
    /**
     * @tc.steps: step3. Normal testing
     * @tc.expected: return TransitionType.
     */

    value = "All";
    EXPECT_EQ(ParseTransitionType(value), TransitionType::ALL);
    value = "Insert";
    EXPECT_EQ(ParseTransitionType(value), TransitionType::APPEARING);
    value = "Delete";
    EXPECT_EQ(ParseTransitionType(value), TransitionType::DISAPPEARING);
}

/**
 * @tc.name: UtilsTest008
 * @tc.desc: ParseTransitionType
 * @tc.type: FUNC
 */
HWTEST_F(UtilsTest, UtilsTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a string container.
     */
    std::string value = "";

    /**
     * @tc.steps: step2. Testing illegal values.
     * @tc.expected: return nullptr.
     */
    std::function<float(float)> fun;

    EXPECT_EQ(CreateCurve(fun), Curves::EASE_IN_OUT);
    EXPECT_NE(CreateCurveExceptSpring(value, fun), nullptr);
    /**
     * @tc.steps: step3. Normal testing
     * @tc.expected: return Curve.
     */

    value = "ease";
    EXPECT_NE(CreateCurveExceptSpring(value, fun), nullptr);
    value = "cubic-bezier";
    EXPECT_NE(CreateCurveExceptSpring(value, fun), nullptr);
    fun = [](float num) { return num; };
    EXPECT_NE(CreateCurveExceptSpring(value, fun), nullptr);
    EXPECT_NE(CreateCurve(fun), nullptr);
}

/**
 * @tc.name: UtilsTest009
 * @tc.desc: CreateCurveExceptSpring
 * @tc.type: FUNC
 */
HWTEST_F(UtilsTest, UtilsTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct params
     */
    std::string value = "aaa(int a,int b)";
    std::function<float(float)> fun = nullptr;
    EXPECT_EQ(CreateCurveExceptSpring(value, fun) == Curves::EASE_IN_OUT, true);
}

/**
 * @tc.name: transformConvertorTest001
 * @tc.desc: test func Convert
 * @tc.type: FUNC
 */
HWTEST_F(UtilsTest, transformConvertorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct params for Convert
     */
    TransformConvertor transformConvertor;
    std::string key = "aaa";
    std::string value = "bbb";
    double time = 0.0;
    transformConvertor.Convert(key, value, time);
    key = "translate";
    transformConvertor.Convert(key, value, time);

    /**
     * @tc.steps: step2. construct params for AddAnimationToTweenOption
     */
    TweenOption tweenOption;
    transformConvertor.AddAnimationToTweenOption(tweenOption);
    EXPECT_EQ(tweenOption.GetTransformAnimations().size(), 1);
    transformConvertor.InsertIdentityKeyframe(time);
    EXPECT_EQ(transformConvertor.noneKeyframeTimes_.size() == 1, true);
    transformConvertor.AddAnimationToTweenOption(tweenOption);
    EXPECT_EQ(tweenOption.GetTransformAnimations().size(), 2);
    AnimationType type = AnimationType::TRANSLATE;
    RefPtr<Keyframe<TransformOperation>> keyframe;
    transformConvertor.AddKeyframe(type, keyframe);

    /**
     * @tc.steps: step3. construct params for ApplyCurve
     */
    RefPtr<Curve> curve;
    transformConvertor.ApplyCurve(curve);
    EXPECT_EQ(transformConvertor.operationList_.size(), 1);
}
} // namespace OHOS::Ace::Framework
