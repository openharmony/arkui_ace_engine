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
#include "base/geometry/animatable_matrix4.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
const int32_t VALID_ROW0 = 0;
const int32_t VALID_COL0 = 0;
const double DEFAULT_DOUBLE0 = 0.0;
} // namespace

class AnimatableMatrix4Test : public testing::Test {};

/**
 * @tc.name: AnimatableMatrix4Test001
 * @tc.desc: Test the function operator= of the class AnimatableMatrix4.
 * @tc.type: FUNC
 */
HWTEST_F(AnimatableMatrix4Test, AnimatableMatrix4Test001, TestSize.Level1)
{
    /**
     * @tc.steps: Test the function operator= with given Matrix4 object.
     */
    AnimatableMatrix4 animatableMatrix4Obj1;
    Matrix4 matrixObj1 = Matrix4::CreateIdentity();
    animatableMatrix4Obj1 = matrixObj1;
    EXPECT_TRUE(animatableMatrix4Obj1.IsIdentityMatrix());
    matrixObj1.Set(VALID_ROW0, VALID_COL0, DEFAULT_DOUBLE0);

    /**
     * @tc.steps: Test the function MoveTo with given Matrix4 object.
     */
    animatableMatrix4Obj1.MoveTo(matrixObj1);
    EXPECT_DOUBLE_EQ(animatableMatrix4Obj1.Get(VALID_ROW0, VALID_COL0), DEFAULT_DOUBLE0);

    /**
     * @tc.steps: Test the function operator= with given AnimatableMatrix4 object.
     */
    AnimatableMatrix4 animatableMatrix4Obj2;
    animatableMatrix4Obj2 = animatableMatrix4Obj1;
    EXPECT_DOUBLE_EQ(animatableMatrix4Obj2.Get(VALID_ROW0, VALID_COL0), DEFAULT_DOUBLE0);
}

/**
 * @tc.name: AnimatableMatrix4Test002
 * @tc.desc: Test the function AnimateTo of the class AnimatableMatrix4.
 * @tc.type: FUNC
 */
HWTEST_F(AnimatableMatrix4Test, AnimatableMatrix4Test002, TestSize.Level1)
{
    /**
     * @tc.steps: initialize parameters.
     */
    AnimatableMatrix4 animatableMatrix4Obj1;
    Matrix4 endValue = Matrix4::CreateIdentity();
    EXPECT_TRUE(animatableMatrix4Obj1.isFirstAssign_);

    /**
     * @tc.steps: Test the function AnimateTo firstly, enter the first if-branch.
     */
    animatableMatrix4Obj1.AnimateTo(endValue);
    EXPECT_FALSE(animatableMatrix4Obj1.isFirstAssign_);
    EXPECT_TRUE(animatableMatrix4Obj1.IsIdentityMatrix());
    EXPECT_EQ(animatableMatrix4Obj1.animationController_, nullptr);

    /**
     * @tc.steps: Test the function AnimateTo secondly, enter the second if-branch.
     */
    animatableMatrix4Obj1.AnimateTo(animatableMatrix4Obj1);
    EXPECT_EQ(animatableMatrix4Obj1.animationController_, nullptr);

    /**
     * @tc.steps: Test the function AnimateTo thirdly, the function will run until the end of it.
     */
    animatableMatrix4Obj1.AnimateTo(endValue);
    EXPECT_EQ(animatableMatrix4Obj1.animationController_, nullptr);
}

/**
 * @tc.name: AnimatableMatrix4Test003
 * @tc.desc: Test the function ResetController of the class AnimatableMatrix4.
 * @tc.type: FUNC
 */
HWTEST_F(AnimatableMatrix4Test, AnimatableMatrix4Test003, TestSize.Level1)
{
    AnimatableMatrix4 animatableMatrix4Obj1;
    animatableMatrix4Obj1.ResetController();
    animatableMatrix4Obj1.animationController_ = CREATE_ANIMATOR(nullptr);
    EXPECT_NE(animatableMatrix4Obj1.animationController_, nullptr);
    animatableMatrix4Obj1.ResetController();
    EXPECT_EQ(animatableMatrix4Obj1.animationController_, nullptr);
}

/**
 * @tc.name: AnimatableMatrix4Test004
 * @tc.desc: Test the function OnAnimationCallback of the class AnimatableMatrix4.
 * @tc.type: FUNC
 */
HWTEST_F(AnimatableMatrix4Test, AnimatableMatrix4Test004, TestSize.Level1)
{
    /**
     * @tc.steps: initialize parameters.
     */
    TransformOperation transformOperation;
    AnimatableMatrix4 animatableMatrix4Obj1;
    animatableMatrix4Obj1.OnAnimationCallback(transformOperation);
    bool flagEventCbk = false;
    animatableMatrix4Obj1.SetContextAndCallback(nullptr, [&flagEventCbk]() { flagEventCbk = true; });
    /**
     * @tc.steps: Set the animationCallback_ as the function which changes the value of flagEventCbk,
     *            the value will be modified when the onReadyEvent is fired.
     */
    animatableMatrix4Obj1.OnAnimationCallback(transformOperation);
    EXPECT_TRUE(flagEventCbk);
}

/**
 * @tc.name: AnimatableMatrix4Test005
 * @tc.desc: Test the function ResetAnimatableMatrix of the class AnimatableMatrix4.
 * @tc.type: FUNC
 */
HWTEST_F(AnimatableMatrix4Test, AnimatableMatrix4Test005, TestSize.Level1)
{
    AnimatableMatrix4 animatableMatrix4Obj1;
    animatableMatrix4Obj1.isFirstAssign_ = false;
    animatableMatrix4Obj1.ResetAnimatableMatrix();
    EXPECT_TRUE(animatableMatrix4Obj1.isFirstAssign_);
}

/**
 * @tc.name: AnimatableMatrix4Test006
 * @tc.desc: Test the function reload operator=
 * @tc.type: FUNC
 */
HWTEST_F(AnimatableMatrix4Test, AnimatableMatrix4Test006, TestSize.Level1)
{
    AnimatableMatrix4 animatableMatrix4Obj1;
    AnimatableMatrix4 animatableMatrix4Obj2;
    ASSERT_EQ(animatableMatrix4Obj1.animationCallback_, nullptr);
    ASSERT_EQ(animatableMatrix4Obj2.animationCallback_, nullptr);
    // true true, both animationCallback_ and pipelineContext nullptr
    animatableMatrix4Obj2 = animatableMatrix4Obj1;
    ASSERT_EQ(animatableMatrix4Obj2.animationCallback_, nullptr);
    // false true, animationCallback_ not nullptr, pipelineContext  nullptr
    bool flagEventCbk = false;
    animatableMatrix4Obj2.SetContextAndCallback(nullptr, [&flagEventCbk]() { flagEventCbk = true; });
    animatableMatrix4Obj2 = animatableMatrix4Obj1;
    ASSERT_NE(animatableMatrix4Obj2.animationCallback_, nullptr);
}
} // namespace OHOS::Ace
