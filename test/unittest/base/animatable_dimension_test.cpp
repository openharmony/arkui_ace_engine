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

#include "base/memory/referenced.h"
// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public
#include "core/animation/animator.h"
#include "base/geometry/animatable_dimension.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const double DEFAULT_DOUBLE1 = 1.0;
constexpr double DEFAULT_DOUBLE2 = 2.0;
const std::string DEFAULT_STR("2.0");
} // namespace

class AnimatableDimensionTest : public testing::Test {};

/**
 * @tc.name: AnimatableDimensionTest001
 * @tc.desc: Test the function operator= of the class AnimatableDimension.
 * @tc.type: FUNC
 */
HWTEST_F(AnimatableDimensionTest, AnimatableDimensionTest001, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    AnimatableDimension animatableDimensionObj1;
    Dimension dimension(DEFAULT_DOUBLE1);
    CalcDimension calcDimension(DEFAULT_STR);

    /**
     * @tc.steps2: Call the function operator= with given Dimension object.
     * @tc.expected: The return value of the function Value() is 1.0.
     */
    animatableDimensionObj1 = dimension;
    EXPECT_DOUBLE_EQ(animatableDimensionObj1.Value(), DEFAULT_DOUBLE1);

    /**
     * @tc.steps3: Call the function operator= with given CalcDimension object.
     * @tc.expected: The return value of the function CalcValue() is DEFAULT_STR.
     */
    AnimatableDimension animatableDimensionObj2;
    animatableDimensionObj2 = calcDimension;
    EXPECT_EQ(animatableDimensionObj2.CalcValue(), DEFAULT_STR);

    /**
     * @tc.steps4: Call the function operator= with given AnimatableDimension object.
     * @tc.expected: The return value of the function Value() is 1.0.
     */
    AnimatableDimension animatableDimensionObj3;
    animatableDimensionObj3 = animatableDimensionObj1;
    EXPECT_DOUBLE_EQ(animatableDimensionObj3.Value(), DEFAULT_DOUBLE1);

    /**
     * @tc.steps5: Call the function operator= with given AnimatableDimension object.
     * @tc.expected: The return value of the function CalcValue() is DEFAULT_STR.
     */
    animatableDimensionObj3 = animatableDimensionObj2;
    EXPECT_EQ(animatableDimensionObj3.CalcValue(), DEFAULT_STR);

    /**
     * @tc.steps6: Call the function MoveTo.
     * @tc.expected: The return value of the function Value() is 2.0.
     */
    animatableDimensionObj1.MoveTo(DEFAULT_DOUBLE2);
    EXPECT_DOUBLE_EQ(animatableDimensionObj1.Value(), DEFAULT_DOUBLE2);
}

/**
 * @tc.name: AnimatableDimensionTest002
 * @tc.desc: Test the function AnimateTo of the class AnimatableDimension.
 * @tc.type: FUNC
 */
HWTEST_F(AnimatableDimensionTest, AnimatableDimensionTest002, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: The value of isFirstAssign_ is true.
     */
    AnimatableDimension animatableDimensionObj1;
    EXPECT_TRUE(animatableDimensionObj1.isFirstAssign_);

    /**
     * @tc.steps2: Test the function AnimateTo firstly, enter the first if-branch.
     * @tc.expected: The value of isFirstAssign_ is set to false and the return value of
     *               the function Value is 2.0
     */
    animatableDimensionObj1.AnimateTo(DEFAULT_DOUBLE2);
    EXPECT_FALSE(animatableDimensionObj1.isFirstAssign_);
    EXPECT_DOUBLE_EQ(animatableDimensionObj1.Value(), DEFAULT_DOUBLE2);

    /**
     * @tc.steps3: Test the function AnimateTo secondly, enter the second if-branch.
     * @tc.expected: The return value of the function Value is 2.0 and the value of
     *               animationController_ is set to null.
     */
    animatableDimensionObj1.AnimateTo(DEFAULT_DOUBLE2);
    EXPECT_DOUBLE_EQ(animatableDimensionObj1.Value(), DEFAULT_DOUBLE2);
    EXPECT_EQ(animatableDimensionObj1.animationController_, nullptr);

    /**
     * @tc.steps4: Test the function AnimateTo thirdly, the function will run until the end of it.
     * @tc.expected: The value of animationController_ is set to non-null.
     */
    animatableDimensionObj1.AnimateTo(DEFAULT_DOUBLE1);
    EXPECT_NE(animatableDimensionObj1.animationController_, nullptr);
}

/**
 * @tc.name: AnimatableDimensionTest003
 * @tc.desc: Test the function ResetController of the class AnimatableDimension.
 * @tc.type: FUNC
 */
HWTEST_F(AnimatableDimensionTest, AnimatableDimensionTest003, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    AnimatableDimension animatableDimensionObj1;
    animatableDimensionObj1.ResetController();
    animatableDimensionObj1.animationController_ = CREATE_ANIMATOR(nullptr);

    /**
     * @tc.steps2: call the function ResetController.
     * @tc.expected: The value of animationController_ is changed from non-null to null.
     */
    EXPECT_NE(animatableDimensionObj1.animationController_, nullptr);
    animatableDimensionObj1.ResetController();
    EXPECT_EQ(animatableDimensionObj1.animationController_, nullptr);
}

/**
 * @tc.name: AnimatableDimensionTest004
 * @tc.desc: Test the function OnAnimationCallback of the class AnimatableDimension.
 * @tc.type: FUNC
 */
HWTEST_F(AnimatableDimensionTest, AnimatableDimensionTest004, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    AnimatableDimension animatableDimensionObj1;
    bool flagCbk = false;

    /**
     * @tc.steps2: Call the function OnAnimationCallback.
     * @tc.expected: The return value of the function Value() is 1.0 and the value of animationCallback_ is null.
     */
    animatableDimensionObj1.OnAnimationCallback(DEFAULT_DOUBLE1);
    EXPECT_DOUBLE_EQ(animatableDimensionObj1.Value(), DEFAULT_DOUBLE1);
    EXPECT_EQ(animatableDimensionObj1.animationCallback_, nullptr);

    /**
     * @tc.steps3: Set the animationCallback_ as the function which changes the value of flagCbk.
     */
    animatableDimensionObj1.SetContextAndCallback(nullptr, [&flagCbk]() { flagCbk = true; });

    /**
     * @tc.steps4: Call the function OnAnimationCallback again.
     * @tc.expected: The callback function is called and the value of flagCbk is set to true.
     */
    animatableDimensionObj1.OnAnimationCallback(DEFAULT_DOUBLE2);
    EXPECT_DOUBLE_EQ(animatableDimensionObj1.Value(), DEFAULT_DOUBLE2);
    EXPECT_NE(animatableDimensionObj1.animationCallback_, nullptr);
    EXPECT_TRUE(flagCbk);
}

/**
 * @tc.name: AnimatableDimensionTest005
 * @tc.desc: Test the function ResetAnimatableDimension of the class AnimatableDimension.
 * @tc.type: FUNC
 */
HWTEST_F(AnimatableDimensionTest, AnimatableDimensionTest005, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    AnimatableDimension animatableDimensionObj1;
    animatableDimensionObj1.isFirstAssign_ = false;

    /**
     * @tc.steps2: call the function ResetAnimatableDimension.
     * @tc.expected: The value of flagCbk isFirstAssign_ is set to true.
     */
    animatableDimensionObj1.ResetAnimatableDimension();
    EXPECT_TRUE(animatableDimensionObj1.isFirstAssign_);
}

/**
 * @tc.name: AnimatableDimensionTest006
 * @tc.desc: Test the function operator=(const AnimatableDimension& newDimension) of the class AnimatableDimension.
 * @tc.type: FUNC
 */
HWTEST_F(AnimatableDimensionTest, AnimatableDimensionTest006, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    AnimatableDimension animatableDimensionObj1;
    bool flagCbk = false;
    animatableDimensionObj1.SetContextAndCallback(nullptr, [&flagCbk]() { flagCbk = true; });
    AnimatableDimension animatableDimensionObj2;
    animatableDimensionObj1 = animatableDimensionObj2;
    ASSERT_NE(animatableDimensionObj1.animationCallback_, nullptr);
    animatableDimensionObj1.SetContextAndCallback(nullptr, nullptr);
    animatableDimensionObj1 = animatableDimensionObj2;
    ASSERT_EQ(animatableDimensionObj1.animationCallback_, nullptr);
}

/**
 * @tc.name: AnimatableDimensionTest007
 * @tc.desc: Test the function GetAnimationStatus.
 * @tc.type: FUNC
 */
HWTEST_F(AnimatableDimensionTest, AnimatableDimensionTest007, TestSize.Level1)
{
    /**
     * @tc.steps1: isFirstAssign_ is null and call the function GetAnimationStatus.
     * @tc.expected: status1 is equal to IDLE.
     */
    AnimatableDimension animatableDimensionObj1;
    animatableDimensionObj1.SetContextAndCallback(nullptr, []() {});
    auto status1 = animatableDimensionObj1.GetAnimationStatus();
    EXPECT_EQ(status1, AnimatorStatus::IDLE);

    /**
     * @tc.steps2: isFirstAssign_ is not null and call the function GetAnimationStatus.
     * @tc.expected: status2 is equal to IDLE.
     */
    animatableDimensionObj1.animationController_ = AceType::MakeRefPtr<Animator>();
    EXPECT_NE(animatableDimensionObj1.animationController_, nullptr);
    auto status2 = animatableDimensionObj1.GetAnimationStatus();
    EXPECT_EQ(status2, AnimatorStatus::IDLE);
}
} // namespace OHOS::Ace
