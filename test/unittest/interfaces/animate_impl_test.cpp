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

#include "animate_impl.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "error_code.h"
#include "event_converter.h"
#include "gtest/gtest.h"
#include "native_animate.h"
#include "native_interface.h"
#include "native_node.h"
#include "node_extened.h"
#include "node_model.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::AnimateModel;

class AnimateImplTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

float InterpolateCallback(float fraction, void* userData)
{
    return fraction;
}

void AnimateCompleteCallback(void* userData) {}

/**
 * @tc.name: AnimateImplTest001
 * @tc.desc: Test InitCurve function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest001, TestSize.Level1)
{
    ArkUI_CurveHandle curve = InitCurve(ArkUI_AnimationCurve::ARKUI_CURVE_EASE);
    ASSERT_EQ(curve, nullptr);
    
    DisposeCurve(curve);
}

/**
 * @tc.name: AnimateImplTest002
 * @tc.desc: Test CubicBezierCurve function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest002, TestSize.Level1)
{
    ArkUI_CurveHandle curve = CubicBezierCurve(0.0f, 0.0f, 0.0f, 0.0f);
    ASSERT_EQ(curve, nullptr);
}

/**
 * @tc.name: AnimateImplTest003
 * @tc.desc: Test SpringCurve function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest003, TestSize.Level1)
{
    ArkUI_CurveHandle curve = SpringCurve(0.0f, 0.0f, 0.0f, 0.0f);
    ASSERT_EQ(curve, nullptr);
}

/**
 * @tc.name: AnimateImplTest004
 * @tc.desc: Test SpringMotion function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest004, TestSize.Level1)
{
    ArkUI_CurveHandle curve = SpringMotion(0.0f, 0.0f, 0.0f);
    ASSERT_EQ(curve, nullptr);
}

/**
 * @tc.name: AnimateImplTest005
 * @tc.desc: Test InterpolatingSpring function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest005, TestSize.Level1)
{
    ArkUI_CurveHandle curve = InterpolatingSpring(0.0f, 0.0f, 0.0f, 0.0f);
    ASSERT_EQ(curve, nullptr);
}

/**
 * @tc.name: AnimateImplTest006
 * @tc.desc: Test ResponsiveSpringMotion function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest006, TestSize.Level1)
{
    ArkUI_CurveHandle curve = ResponsiveSpringMotion(0.0f, 0.0f, 0.0f);
    ASSERT_EQ(curve, nullptr);
}

/**
 * @tc.name: AnimateImplTest007
 * @tc.desc: Test CustomCurve function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest007, TestSize.Level1)
{
    ArkUI_CurveHandle curve = CustomCurve(nullptr, InterpolateCallback);
    ASSERT_EQ(curve, nullptr);
}

/**
 * @tc.name: AnimateImplTest008
 * @tc.desc: Test InitCurve function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest008, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_CurveHandle curve = InitCurve(ArkUI_AnimationCurve::ARKUI_CURVE_EASE);
    ASSERT_NE(curve, nullptr);

    DisposeCurve(curve);
    curve = nullptr;
}

/**
 * @tc.name: AnimateImplTest009
 * @tc.desc: Test StepsCurve function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest009, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_CurveHandle curve = StepsCurve(0, true);
    ASSERT_EQ(curve, nullptr);
}

/**
 * @tc.name: AnimateImplTest010
 * @tc.desc: Test StepsCurve function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest010, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_CurveHandle curve = StepsCurve(1, true);
    ASSERT_NE(curve, nullptr);

    DisposeCurve(curve);
    curve = nullptr;
}

/**
 * @tc.name: AnimateImplTest011
 * @tc.desc: Test CubicBezierCurve function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest011, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_CurveHandle curve = CubicBezierCurve(0.0f, 0.0f, 0.0f, 0.0f);
    ASSERT_NE(curve, nullptr);

    DisposeCurve(curve);
    curve = nullptr;
}

/**
 * @tc.name: AnimateImplTest012
 * @tc.desc: Test SpringCurve function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest012, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_CurveHandle curve = SpringCurve(0.0f, 0.0f, 0.0f, 0.0f);
    ASSERT_NE(curve, nullptr);

    DisposeCurve(curve);
    curve = nullptr;
}

/**
 * @tc.name: AnimateImplTest013
 * @tc.desc: Test SpringCurve function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest013, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_CurveHandle curve = SpringCurve(0.5f, 0.5f, 0.5f, 0.5f);
    ASSERT_NE(curve, nullptr);

    DisposeCurve(curve);
    curve = nullptr;
}

/**
 * @tc.name: AnimateImplTest014
 * @tc.desc: Test SpringMotion function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest014, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_CurveHandle curve = SpringMotion(0.5f, 0.5f, 0.5f);
    ASSERT_NE(curve, nullptr);

    DisposeCurve(curve);
    curve = nullptr;
}

/**
 * @tc.name: AnimateImplTest015
 * @tc.desc: Test SpringMotion function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest015, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_CurveHandle curve = SpringMotion(-1.0f, -1.0f, -1.0f);
    ASSERT_NE(curve, nullptr);

    DisposeCurve(curve);
    curve = nullptr;
}

/**
 * @tc.name: AnimateImplTest016
 * @tc.desc: Test ResponsiveSpringMotion function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest016, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_CurveHandle curve = ResponsiveSpringMotion(-1.0f, -1.0f, -1.0f);
    ASSERT_NE(curve, nullptr);

    DisposeCurve(curve);
    curve = nullptr;
}

/**
 * @tc.name: AnimateImplTest017
 * @tc.desc: Test ResponsiveSpringMotion function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest017, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_CurveHandle curve = ResponsiveSpringMotion(0.5f, 0.5f, 0.5f);
    ASSERT_NE(curve, nullptr);

    DisposeCurve(curve);
    curve = nullptr;
}

/**
 * @tc.name: AnimateImplTest018
 * @tc.desc: Test InterpolatingSpring function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest018, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_CurveHandle curve = InterpolatingSpring(0.5f, 0.5f, 0.5f, 0.5f);
    ASSERT_NE(curve, nullptr);

    DisposeCurve(curve);
    curve = nullptr;
}

/**
 * @tc.name: AnimateImplTest019
 * @tc.desc: Test InterpolatingSpring function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest019, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_CurveHandle curve = InterpolatingSpring(0.0f, 0.0f, 0.0f, 0.0f);
    ASSERT_NE(curve, nullptr);

    DisposeCurve(curve);
    curve = nullptr;
}

/**
 * @tc.name: AnimateImplTest020
 * @tc.desc: Test CustomCurve function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest020, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_CurveHandle curve = CustomCurve(nullptr, InterpolateCallback);
    ASSERT_NE(curve, nullptr);

    DisposeCurve(curve);
    curve = nullptr;
}

/**
 * @tc.name: AnimateImplTest021
 * @tc.desc: Test CreateAnimator function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest021, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    struct ArkUI_Context context= {1};
    ArkUI_AnimatorOption* option = new ArkUI_AnimatorOption();
    ArkUI_AnimatorHandle animatorHandle = CreateAnimator(&context, option);
    ASSERT_NE(animatorHandle, nullptr);

    DisposeAnimator(animatorHandle);
    animatorHandle = nullptr;
    delete option;
}

/**
 * @tc.name: AnimateImplTest022
 * @tc.desc: Test CreateAnimator function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest022, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_AnimatorHandle animatorHandle = CreateAnimator(nullptr, nullptr);
    ASSERT_EQ(animatorHandle, nullptr);

    DisposeAnimator(animatorHandle);
}

/**
 * @tc.name: AnimateImplTest023
 * @tc.desc: Test AnimatorReset function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest023, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    int32_t ret = AnimatorReset(nullptr, nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: AnimateImplTest024
 * @tc.desc: Test AnimatorReset function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest024, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    struct ArkUI_Context context= {1};
    ArkUI_AnimatorOption* option = new ArkUI_AnimatorOption();
    ArkUI_AnimatorHandle animatorHandle = CreateAnimator(&context, option);
    ASSERT_NE(animatorHandle, nullptr);
    ArkUIAnimatorHandle animator = new ArkUIAnimator();
    animatorHandle->animator = animator;
    int32_t ret = AnimatorReset(animatorHandle, option);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);

    DisposeAnimator(animatorHandle);
    animatorHandle = nullptr;
    delete option;
}

/**
 * @tc.name: AnimateImplTest025
 * @tc.desc: Test AnimatorReset function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest025, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    struct ArkUI_Context context= {1};
    ArkUI_AnimatorOption* option = new ArkUI_AnimatorOption();
    struct ArkUI_Keyframe keyframe = {0.0f, 0.0f, nullptr};
    option->keyframes.push_back(keyframe);
    ArkUI_AnimatorHandle animatorHandle = CreateAnimator(&context, option);
    ASSERT_NE(animatorHandle, nullptr);
    ArkUIAnimatorHandle animator = new ArkUIAnimator();
    animatorHandle->animator = animator;
    int32_t ret = AnimatorReset(animatorHandle, option);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);

    DisposeAnimator(animatorHandle);
    animatorHandle = nullptr;
    delete option;
}

/**
 * @tc.name: AnimateImplTest026
 * @tc.desc: Test AnimatorPlay function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest026, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    int32_t ret = AnimatorPlay(nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: AnimateImplTest027
 * @tc.desc: Test AnimatorPlay function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest027, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    struct ArkUI_Context context= {1};
    ArkUI_AnimatorOption* option = new ArkUI_AnimatorOption();
    ArkUI_AnimatorHandle animatorHandle = CreateAnimator(&context, option);
    ASSERT_NE(animatorHandle, nullptr);
    ArkUIAnimatorHandle animator = new ArkUIAnimator();
    animatorHandle->animator = animator;
    int32_t ret = AnimatorPlay(animatorHandle);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);

    DisposeAnimator(animatorHandle);
    animatorHandle = nullptr;
    delete option;
}

/**
 * @tc.name: AnimateImplTest028
 * @tc.desc: Test AnimatorFinish function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest028, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    int32_t ret = AnimatorFinish(nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: AnimateImplTest029
 * @tc.desc: Test AnimatorFinish function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest029, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    struct ArkUI_Context context= {1};
    ArkUI_AnimatorOption* option = new ArkUI_AnimatorOption();
    ArkUI_AnimatorHandle animatorHandle = CreateAnimator(&context, option);
    ASSERT_NE(animatorHandle, nullptr);
    ArkUIAnimatorHandle animator = new ArkUIAnimator();
    animatorHandle->animator = animator;
    int32_t ret = AnimatorFinish(animatorHandle);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);

    DisposeAnimator(animatorHandle);
    animatorHandle = nullptr;
    delete option;
}

/**
 * @tc.name: AnimateImplTest030
 * @tc.desc: Test AnimatorPause function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest030, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    int32_t ret = AnimatorPause(nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: AnimateImplTest031
 * @tc.desc: Test AnimatorPause function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest031, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    struct ArkUI_Context context= {1};
    ArkUI_AnimatorOption* option = new ArkUI_AnimatorOption();
    ArkUI_AnimatorHandle animatorHandle = CreateAnimator(&context, option);
    ASSERT_NE(animatorHandle, nullptr);
    ArkUIAnimatorHandle animator = new ArkUIAnimator();
    animatorHandle->animator = animator;
    int32_t ret = AnimatorPause(animatorHandle);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);

    DisposeAnimator(animatorHandle);
    animatorHandle = nullptr;
    delete option;
}

/**
 * @tc.name: AnimateImplTest032
 * @tc.desc: Test AnimatorCancel function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest032, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    int32_t ret = AnimatorCancel(nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: AnimateImplTest033
 * @tc.desc: Test AnimatorCancel function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest033, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    struct ArkUI_Context context= {1};
    ArkUI_AnimatorOption* option = new ArkUI_AnimatorOption();
    ArkUI_AnimatorHandle animatorHandle = CreateAnimator(&context, option);
    ASSERT_NE(animatorHandle, nullptr);
    ArkUIAnimatorHandle animator = new ArkUIAnimator();
    animatorHandle->animator = animator;
    int32_t ret = AnimatorCancel(animatorHandle);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);

    DisposeAnimator(animatorHandle);
    animatorHandle = nullptr;
    delete option;
}

/**
 * @tc.name: AnimateImplTest034
 * @tc.desc: Test AnimatorReverse function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest034, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    int32_t ret = AnimatorReverse(nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: AnimateImplTest035
 * @tc.desc: Test AnimatorReverse function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest035, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    struct ArkUI_Context context= {1};
    ArkUI_AnimatorOption* option = new ArkUI_AnimatorOption();
    ArkUI_AnimatorHandle animatorHandle = CreateAnimator(&context, option);
    ASSERT_NE(animatorHandle, nullptr);
    ArkUIAnimatorHandle animator = new ArkUIAnimator();
    animatorHandle->animator = animator;
    int32_t ret = AnimatorReverse(animatorHandle);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);

    DisposeAnimator(animatorHandle);
    animatorHandle = nullptr;
    delete option;
}

/**
 * @tc.name: AnimateImplTest036
 * @tc.desc: Test KeyframeAnimateTo function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest036, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    int32_t ret = KeyframeAnimateTo(nullptr, nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: AnimateImplTest037
 * @tc.desc: Test KeyframeAnimateTo function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest037, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    struct ArkUI_Context context= {1};
    ArkUI_KeyframeAnimateOption* option = new ArkUI_KeyframeAnimateOption();
    struct ArkUI_KeyframeState keyframe = {0, nullptr, nullptr, nullptr};
    option->keyframes.push_back(keyframe);
    int32_t ret = KeyframeAnimateTo(&context, option);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    delete option;
}

/**
 * @tc.name: AnimateImplTest038
 * @tc.desc: Test AnimateTo function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest038, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    int32_t ret = AnimateTo(nullptr, nullptr, nullptr, nullptr);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: AnimateImplTest039
 * @tc.desc: Test AnimateTo function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest039, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    struct ArkUI_Context context= {1};
    ArkUI_AnimateOption* option = new ArkUI_AnimateOption();
    ArkUI_ContextCallback* update = new ArkUI_ContextCallback();
    update->callback = AnimateCompleteCallback;
    ArkUI_AnimateCompleteCallback* complete = new ArkUI_AnimateCompleteCallback();
    int32_t ret = AnimateTo(&context, option, update, complete);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    delete option;
    delete update;
    delete complete;
}

/**
 * @tc.name: AnimateImplTest040
 * @tc.desc: Test AnimateTo function.
 * @tc.type: FUNC
 */
HWTEST_F(AnimateImplTest, AnimateImplTest040, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    struct ArkUI_Context context= {1};
    ArkUI_AnimateOption* option = new ArkUI_AnimateOption();
    ArkUI_CurveHandle curve = new ArkUI_Curve();
    ArkUI_ExpectedFrameRateRange* expectedFrameRateRange = new ArkUI_ExpectedFrameRateRange();
    option->iCurve = curve;
    option->expectedFrameRateRange = expectedFrameRateRange;
    ArkUI_ContextCallback* update = new ArkUI_ContextCallback();
    update->callback = AnimateCompleteCallback;
    ArkUI_AnimateCompleteCallback* complete = new ArkUI_AnimateCompleteCallback();
    complete->type = ARKUI_FINISH_CALLBACK_LOGICALLY;
    complete->callback = AnimateCompleteCallback;
    void* userData = malloc(100);
    complete->userData = userData;
    int32_t ret = AnimateTo(&context, option, update, complete);
    ASSERT_EQ(ret, OHOS::Ace::ERROR_CODE_NO_ERROR);
    free(userData);
    delete option;
    delete curve;
    delete update;
    delete complete;
}