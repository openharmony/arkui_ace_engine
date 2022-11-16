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

#define private public
#include "frameworks/bridge/common/utils/transform_convertor.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/core/components/common/properties/tween_option.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::Framework {
namespace {
const std::string X_POINT = "500";
const std::string Y_POINT = "500";
const std::string Z_POINT = "500";
const std::string X_Y_POINT = "500 500";
const std::string X_Y_Z_POINT = "500 500 500";
const std::string PARAM_FOUR_POINT = "500 500 500 500";
const std::string PARAM_SIX_POINT = "500 500 500 500 500 500";
const std::string PARAM_SIXTEEN_POINT = "500 500 500 500 "
                                        "500 500 500 500 "
                                        "500 500 500 500 "
                                        "500 500 500 500";
const std::string CURVE_STRING = "curve";
const size_t ANIMATION_FIVE_SIZE = 5;
const size_t ANIMATION_THREE_SIZE = 3;
const double KEY_FRAME_TIME = 1.0f;
const double DOUBLE_VALUE = 500;
const double DOUBLE_ONE_VALUE = 1;
const float FLOAT_VALUE = 500;
const float FLOAT_ONE_VALUE = 1;
const Dimension DIMENSION_VALUE = StringUtils::StringToDimension("500");
} // namespace

class TransformConvertorTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void TransformConvertorTest::SetUpTestCase() {}
void TransformConvertorTest::TearDownTestCase() {}
void TransformConvertorTest::SetUp() {}
void TransformConvertorTest::TearDown() {}

/**
 * @tc.name: TransformConvertorTest001
 * @tc.desc: Test the animation can add into TweenOption successfully
 * @tc.type: FUNC
 */
HWTEST_F(TransformConvertorTest, TransformConvertorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add some kinds of keyframes
     * @tc.expected: step1. Get the value of keyframes as expected
     */
    TransformConvertor convertor;
    TweenOption option;
    convertor.Convert(convertor.TransformKey[0], X_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[0], X_Y_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[1], X_Y_Z_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[2], X_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[3], Y_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[4], Z_POINT, KEY_FRAME_TIME);
    convertor.InsertIdentityKeyframe(KEY_FRAME_TIME);
    EXPECT_EQ(convertor.noneKeyframeTimes_.size(), 1);
    EXPECT_EQ(convertor.operationList_.size(), ANIMATION_FIVE_SIZE);
    EXPECT_EQ(convertor.operationMap_.size(), ANIMATION_FIVE_SIZE);
    EXPECT_EQ(convertor.noneKeyframeTimes_.front(), KEY_FRAME_TIME);
    auto operatorMapValue =
        convertor.operationMap_[AnimationType::TRANSLATE]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.translateOperation_.dx, DIMENSION_VALUE);
    operatorMapValue =
        convertor.operationMap_[AnimationType::TRANSLATE]->GetKeyframes().back()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.translateOperation_.dx, DIMENSION_VALUE);
    EXPECT_EQ(operatorMapValue.translateOperation_.dy, DIMENSION_VALUE);
    operatorMapValue =
        convertor.operationMap_[AnimationType::TRANSLATE_X]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.translateOperation_.dx, DIMENSION_VALUE);
    operatorMapValue =
        convertor.operationMap_[AnimationType::TRANSLATE_Y]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.translateOperation_.dy, DIMENSION_VALUE);
    operatorMapValue =
        convertor.operationMap_[AnimationType::TRANSLATE_Z]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.translateOperation_.dz, DIMENSION_VALUE);
    operatorMapValue =
        convertor.operationMap_[AnimationType::TRANSLATE_3D]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.translateOperation_.dx, DIMENSION_VALUE);
    EXPECT_EQ(operatorMapValue.translateOperation_.dy, DIMENSION_VALUE);
    EXPECT_EQ(operatorMapValue.translateOperation_.dz, DIMENSION_VALUE);
    /**
     * @tc.steps: step2. Add animations to tween option
     * @tc.expected: step2. Get the Transform animations as expected
     */
    convertor.AddAnimationToTweenOption(option);
    EXPECT_EQ(option.GetTransformAnimations().size(), ANIMATION_FIVE_SIZE);
}

/**
 * @tc.name: TransformConvertorTest002
 * @tc.desc: Test the animation can add into TweenOption successfully
 * @tc.type: FUNC
 */
HWTEST_F(TransformConvertorTest, TransformConvertorTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add some kinds of keyframes
     * @tc.expected: step1. Get the value of keyframes as expected
     */
    TransformConvertor convertor;
    TweenOption option;
    convertor.Convert(convertor.TransformKey[5], X_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[6], PARAM_FOUR_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[7], X_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[8], Y_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[9], Z_POINT, KEY_FRAME_TIME);
    convertor.InsertIdentityKeyframe(KEY_FRAME_TIME);
    EXPECT_EQ(convertor.noneKeyframeTimes_.size(), 1);
    EXPECT_EQ(convertor.noneKeyframeTimes_.front(), KEY_FRAME_TIME);
    auto operatorMapValue =
        convertor.operationMap_[AnimationType::ROTATE]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.rotateOperation_.dz, FLOAT_ONE_VALUE);
    operatorMapValue =
        convertor.operationMap_[AnimationType::ROTATE_3D]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.rotateOperation_.dx, FLOAT_VALUE);
    EXPECT_EQ(operatorMapValue.rotateOperation_.dy, FLOAT_VALUE);
    EXPECT_EQ(operatorMapValue.rotateOperation_.dz, FLOAT_VALUE);
    operatorMapValue =
        convertor.operationMap_[AnimationType::ROTATE_X]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.rotateOperation_.dx, FLOAT_ONE_VALUE);
    operatorMapValue =
        convertor.operationMap_[AnimationType::ROTATE_Y]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.rotateOperation_.dy, FLOAT_ONE_VALUE);
    operatorMapValue =
        convertor.operationMap_[AnimationType::ROTATE_Z]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.rotateOperation_.dz, FLOAT_ONE_VALUE);
    EXPECT_EQ(convertor.operationList_.size(), ANIMATION_FIVE_SIZE);
    EXPECT_EQ(convertor.operationMap_.size(), ANIMATION_FIVE_SIZE);
    /**
     * @tc.steps: step2. Add animations to tween option
     * @tc.expected: step2. Get the Transform animations as expected
     */
    convertor.AddAnimationToTweenOption(option);
    EXPECT_EQ(option.GetTransformAnimations().size(), ANIMATION_FIVE_SIZE);
}

/**
 * @tc.name: TransformConvertorTest003
 * @tc.desc: Test the animation can add into TweenOption successfully
 * @tc.type: FUNC
 */
HWTEST_F(TransformConvertorTest, TransformConvertorTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add some kinds of keyframes
     * @tc.expected: step1. Get the value of keyframes as expected
     */
    TransformConvertor convertor;
    TweenOption option;
    convertor.Convert(convertor.TransformKey[10], X_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[10], X_Y_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[11], X_Y_Z_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[12], X_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[13], Y_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[14], Z_POINT, KEY_FRAME_TIME);
    convertor.InsertIdentityKeyframe(KEY_FRAME_TIME);
    EXPECT_EQ(convertor.noneKeyframeTimes_.size(), 1);
    EXPECT_EQ(convertor.noneKeyframeTimes_.front(), KEY_FRAME_TIME);
    auto operatorMapValue =
        convertor.operationMap_[AnimationType::SCALE]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleX, DOUBLE_VALUE);
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleY, DOUBLE_VALUE);
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleZ, DOUBLE_ONE_VALUE);
    operatorMapValue =
        convertor.operationMap_[AnimationType::SCALE]->GetKeyframes().back()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleX, DOUBLE_VALUE);
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleY, DOUBLE_VALUE);
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleZ, DOUBLE_ONE_VALUE);
    operatorMapValue =
        convertor.operationMap_[AnimationType::SCALE_3D]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleX, DOUBLE_VALUE);
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleY, DOUBLE_VALUE);
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleZ, DOUBLE_VALUE);
    operatorMapValue =
        convertor.operationMap_[AnimationType::SCALE_X]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleX, DOUBLE_VALUE);
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleY, DOUBLE_ONE_VALUE);
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleZ, DOUBLE_ONE_VALUE);
    operatorMapValue =
        convertor.operationMap_[AnimationType::SCALE_Y]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleX, DOUBLE_ONE_VALUE);
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleY, DOUBLE_VALUE);
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleZ, DOUBLE_ONE_VALUE);
    operatorMapValue =
        convertor.operationMap_[AnimationType::SCALE_Z]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleX, DOUBLE_ONE_VALUE);
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleY, DOUBLE_ONE_VALUE);
    EXPECT_EQ(operatorMapValue.scaleOperation_.scaleZ, DOUBLE_VALUE);
    EXPECT_EQ(convertor.operationList_.size(), ANIMATION_FIVE_SIZE);
    EXPECT_EQ(convertor.operationMap_.size(), ANIMATION_FIVE_SIZE);
    /**
     * @tc.steps: step2. Add animations to tween option
     * @tc.expected: step2. Get the Transform animations as expected
     */
    convertor.AddAnimationToTweenOption(option);
    EXPECT_EQ(option.GetTransformAnimations().size(), ANIMATION_FIVE_SIZE);
}

/**
 * @tc.name: TransformConvertorTest004
 * @tc.desc: Test the animation can add into TweenOption successfully
 * @tc.type: FUNC
 */
HWTEST_F(TransformConvertorTest, TransformConvertorTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add some kinds of keyframes
     * @tc.expected: step1. Get the value of keyframes as expected
     */
    TransformConvertor convertor;
    TweenOption option;
    convertor.Convert(convertor.TransformKey[15], X_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[15], X_Y_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[16], X_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[17], Y_POINT, KEY_FRAME_TIME);
    convertor.InsertIdentityKeyframe(KEY_FRAME_TIME);
    EXPECT_EQ(convertor.noneKeyframeTimes_.size(), 1);
    EXPECT_EQ(convertor.noneKeyframeTimes_.front(), KEY_FRAME_TIME);
    auto operatorMapValue =
        convertor.operationMap_[AnimationType::SKEW]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.skewOperation_.skewX, FLOAT_VALUE);
    operatorMapValue =
        convertor.operationMap_[AnimationType::SKEW]->GetKeyframes().back()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.skewOperation_.skewX, FLOAT_VALUE);
    EXPECT_EQ(operatorMapValue.skewOperation_.skewY, FLOAT_VALUE);
    operatorMapValue =
        convertor.operationMap_[AnimationType::SKEW_X]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.skewOperation_.skewX, FLOAT_VALUE);
    operatorMapValue =
        convertor.operationMap_[AnimationType::SKEW_Y]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.skewOperation_.skewY, FLOAT_VALUE);
    EXPECT_EQ(convertor.operationList_.size(), ANIMATION_THREE_SIZE);
    EXPECT_EQ(convertor.operationMap_.size(), ANIMATION_THREE_SIZE);
    /**
     * @tc.steps: step2. Add animations to tween option
     * @tc.expected: step2. Get the Transform animations as expected
     */
    convertor.AddAnimationToTweenOption(option);
    EXPECT_EQ(option.GetTransformAnimations().size(), ANIMATION_THREE_SIZE);
}

/**
 * @tc.name: TransformConvertorTest005
 * @tc.desc: Test the curve can be applied successfully
 * @tc.type: FUNC
 */
HWTEST_F(TransformConvertorTest, TransformConvertorTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Add some kinds of keyframes
     * @tc.expected: step1. Get the value of keyframes as expected
     */
    TransformConvertor convertor;
    convertor.Convert(convertor.TransformKey[18], PARAM_SIX_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[19], PARAM_SIXTEEN_POINT, KEY_FRAME_TIME);
    convertor.Convert(convertor.TransformKey[20], X_POINT, KEY_FRAME_TIME);
    convertor.InsertIdentityKeyframe(KEY_FRAME_TIME);
    EXPECT_EQ(convertor.noneKeyframeTimes_.size(), 1);
    EXPECT_EQ(convertor.noneKeyframeTimes_.front(), KEY_FRAME_TIME);
    auto matrix =
        Matrix4(500, 500, 0.0, 500, 500, 500, 0.0, 500, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    auto operatorMapValue =
        convertor.operationMap_[AnimationType::MATRIX_2D]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.matrix4_, matrix);
    matrix =
        Matrix4(500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500);
    operatorMapValue =
        convertor.operationMap_[AnimationType::MATRIX_3D]->GetKeyframes().back()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.matrix4_, matrix);
    operatorMapValue =
        convertor.operationMap_[AnimationType::PERSPECTIVE]->GetKeyframes().front()->GetKeyValue();
    EXPECT_EQ(operatorMapValue.perspectiveOperation_.distance, DIMENSION_VALUE);
    EXPECT_EQ(convertor.operationList_.size(), ANIMATION_THREE_SIZE);
    EXPECT_EQ(convertor.operationMap_.size(), ANIMATION_THREE_SIZE);
    /**
     * @tc.steps: step2. Add animations to tween option
     * @tc.expected: step2. Get the Transform animations as expected
     */
    TweenOption option;
    TransformOperation operation;
    auto keyFrames = AceType::MakeRefPtr<Keyframe<TransformOperation>>(KEY_FRAME_TIME, operation);
    RefPtr<Curve> curve;
    curve = CreateCurve(CURVE_STRING);
    convertor.ApplyCurve(curve);
    convertor.AddAnimationToTweenOption(option);
    EXPECT_EQ(option.GetTransformAnimations().size(), ANIMATION_THREE_SIZE);
    /**
     * @tc.steps: step3. Apply curve
     * @tc.expected: step3. Get the curve as expected
     */
    EXPECT_EQ(keyFrames->GetCurve(), curve);
    /**
     * @tc.steps: step4. Clear animations
     * @tc.expected: step4. Can not get the Transform animations
     */
    convertor.ClearAnimations();
    TweenOption optionTwo;
    convertor.AddAnimationToTweenOption(option);
    EXPECT_EQ(optionTwo.GetTransformAnimations().size(), 0);
}
} // namespace OHOS::Ace::Framework