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

#include <cstdint>
#include "gtest/gtest.h"
#include "native_animate.h"
#include "native_node.h"
#include "native_type.h"
#include "node_model.h"
#include "native_interface.h"
#include "error_code.h"
#include "core/interfaces/arkoala/arkoala_api.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace {
class NodeAnimateTest : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

float InterpolateCallback(float fraction, void* userData)
{
    return fraction;
}

void AnimationCallback(void* userData)
{
}

void AnimatorOnFrameEventCallback(ArkUI_AnimatorOnFrameEvent* event)
{
}

void AnimatorEventCallback(ArkUI_AnimatorEvent* event)
{
}

/**
 * @tc.name: NodeAnimateTest001
 * @tc.desc: Test AnimateOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, NodeAnimateTest001, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);

    float negativeFloat = -1.0f;
    float normalFloat = 1.0f;
    int32_t negativeInt = -2;
    int32_t normalInt = 1;
    int32_t largeInt = 1000;
    OH_ArkUI_AnimateOption_SetDuration(animation, negativeInt);
    OH_ArkUI_AnimateOption_SetDuration(animation, normalInt);
    OH_ArkUI_AnimateOption_SetTempo(animation, negativeFloat);
    OH_ArkUI_AnimateOption_SetTempo(animation, normalFloat);
    OH_ArkUI_AnimateOption_SetCurve(animation, static_cast<ArkUI_AnimationCurve>(negativeInt));
    OH_ArkUI_AnimateOption_SetCurve(animation, static_cast<ArkUI_AnimationCurve>(largeInt));
    OH_ArkUI_AnimateOption_SetCurve(animation, ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR);
    OH_ArkUI_AnimateOption_SetDelay(animation, normalInt);
    OH_ArkUI_AnimateOption_SetIterations(animation, negativeInt);
    OH_ArkUI_AnimateOption_SetIterations(animation, normalInt);
    OH_ArkUI_AnimateOption_SetPlayMode(animation, static_cast<ArkUI_AnimationPlayMode>(negativeInt));
    OH_ArkUI_AnimateOption_SetPlayMode(animation, static_cast<ArkUI_AnimationPlayMode>(largeInt));
    OH_ArkUI_AnimateOption_SetPlayMode(animation, ArkUI_AnimationPlayMode::ARKUI_ANIMATION_PLAY_MODE_NORMAL);
    EXPECT_EQ(OH_ArkUI_AnimateOption_GetDuration(nullptr), 0);
    EXPECT_EQ(OH_ArkUI_AnimateOption_GetDuration(animation), normalInt);
    EXPECT_EQ(OH_ArkUI_AnimateOption_GetTempo(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_AnimateOption_GetTempo(animation), normalFloat);
    EXPECT_EQ(OH_ArkUI_AnimateOption_GetCurve(nullptr), static_cast<ArkUI_AnimationCurve>(-1));
    EXPECT_EQ(OH_ArkUI_AnimateOption_GetCurve(animation), ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR);
    EXPECT_EQ(OH_ArkUI_AnimateOption_GetDelay(nullptr), 0);
    EXPECT_EQ(OH_ArkUI_AnimateOption_GetDelay(animation), normalInt);
    EXPECT_EQ(OH_ArkUI_AnimateOption_GetIterations(nullptr), 0);
    EXPECT_EQ(OH_ArkUI_AnimateOption_GetIterations(animation), normalInt);
    EXPECT_EQ(OH_ArkUI_AnimateOption_GetPlayMode(nullptr), static_cast<ArkUI_AnimationPlayMode>(-1));
    EXPECT_EQ(OH_ArkUI_AnimateOption_GetPlayMode(animation), ArkUI_AnimationPlayMode::ARKUI_ANIMATION_PLAY_MODE_NORMAL);
    EXPECT_EQ(OH_ArkUI_AnimateOption_GetExpectedFrameRateRange(nullptr), nullptr);
    EXPECT_EQ(OH_ArkUI_AnimateOption_GetExpectedFrameRateRange(animation), nullptr);

    OH_ArkUI_AnimateOption_Dispose(nullptr);
    OH_ArkUI_AnimateOption_Dispose(animation);
}

/**
 * @tc.name: NodeAnimateTest002
 * @tc.desc: Test ICurve function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, NodeAnimateTest002, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_AnimateOption* animation = OH_ArkUI_AnimateOption_Create();
    ASSERT_NE(animation, nullptr);
    auto icurve = OH_ArkUI_Curve_CreateCurveByType(ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR);
    auto stepCurve = OH_ArkUI_Curve_CreateStepsCurve(1, true);
    auto cubicBezierCurve = OH_ArkUI_Curve_CreateCubicBezierCurve(0.0f, 0.0f, 0.0f, 0.0f);
    auto springCurve = OH_ArkUI_Curve_CreateSpringCurve(0.0f, 0.0f, 0.0f, 0.0f);
    auto springMotion = OH_ArkUI_Curve_CreateSpringMotion(0.5f, 0.5f, 0.5f);
    auto responsiveSpringMotion = OH_ArkUI_Curve_CreateResponsiveSpringMotion(0.5f, 0.5f, 0.5f);
    auto interpolatingSpring = OH_ArkUI_Curve_CreateInterpolatingSpring(0.5f, 0.5f, 0.5f, 0.5f);
    auto customCurve = OH_ArkUI_Curve_CreateCustomCurve(nullptr, InterpolateCallback);
    ASSERT_NE(icurve, nullptr);
    ASSERT_NE(stepCurve, nullptr);
    ASSERT_NE(cubicBezierCurve, nullptr);
    ASSERT_NE(springCurve, nullptr);
    ASSERT_NE(springMotion, nullptr);
    ASSERT_NE(responsiveSpringMotion, nullptr);
    ASSERT_NE(interpolatingSpring, nullptr);
    ASSERT_NE(customCurve, nullptr);
    OH_ArkUI_AnimateOption_SetICurve(animation, icurve);
    EXPECT_EQ(OH_ArkUI_AnimateOption_GetICurve(nullptr), nullptr);
    ASSERT_NE(OH_ArkUI_AnimateOption_GetICurve(animation), nullptr);
    ArkUI_KeyframeAnimateOption* animateOption = OH_ArkUI_KeyframeAnimateOption_Create(1);
    ASSERT_NE(animateOption, nullptr);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetCurve(nullptr, icurve, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetCurve(animateOption, icurve, -1), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetCurve(animateOption, icurve, 1), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetCurve(animateOption, nullptr, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetCurve(animateOption, springMotion, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetCurve(animateOption, responsiveSpringMotion, 0),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetCurve(animateOption, interpolatingSpring, 0),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetCurve(animateOption, icurve, 0), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_NE(OH_ArkUI_KeyframeAnimateOption_GetCurve(animateOption, 0), nullptr);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_GetCurve(nullptr, 0), nullptr);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_GetCurve(animateOption, -1), nullptr);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_GetCurve(animateOption, 1), nullptr);
    OH_ArkUI_AnimateOption_Dispose(animation);
    OH_ArkUI_KeyframeAnimateOption_Dispose(animateOption);
    OH_ArkUI_Curve_DisposeCurve(icurve);
    OH_ArkUI_Curve_DisposeCurve(stepCurve);
    OH_ArkUI_Curve_DisposeCurve(cubicBezierCurve);
    OH_ArkUI_Curve_DisposeCurve(springCurve);
    OH_ArkUI_Curve_DisposeCurve(springMotion);
    OH_ArkUI_Curve_DisposeCurve(responsiveSpringMotion);
    OH_ArkUI_Curve_DisposeCurve(customCurve);
}

/**
 * @tc.name: NodeAnimateTest003
 * @tc.desc: Test KeyframeAnimateOption normalfunction.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, NodeAnimateTest003, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_Create(-1), nullptr);
    ArkUI_KeyframeAnimateOption* animateOption = OH_ArkUI_KeyframeAnimateOption_Create(1);
    ASSERT_NE(animateOption, nullptr);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetDelay(nullptr, 1), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetDelay(animateOption, 1), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_GetDelay(animateOption), 1);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetIterations(nullptr, 1), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetIterations(animateOption, -2), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetIterations(animateOption, 1), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_GetIterations(animateOption), 1);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetDuration(nullptr, 1, 1), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetDuration(animateOption, 1, -1), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetDuration(animateOption, 1, 1), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetDuration(animateOption, -1, 0), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_SetDuration(animateOption, 1, 0), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_GetDuration(animateOption, 0), 1);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_GetDuration(nullptr, 0), 0);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_GetDuration(animateOption, -1), 0);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_GetDuration(animateOption, 1), 0);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_RegisterOnFinishCallback(animateOption, nullptr, AnimationCallback),
        ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_RegisterOnEventCallback(nullptr, nullptr, AnimationCallback, 0),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_RegisterOnEventCallback(animateOption, nullptr, AnimationCallback, -1),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_RegisterOnEventCallback(animateOption, nullptr, AnimationCallback, 1),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_KeyframeAnimateOption_RegisterOnEventCallback(animateOption, nullptr, AnimationCallback, 0),
        ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_KeyframeAnimateOption_Dispose(animateOption);
}

/**
 * @tc.name: NodeAnimateTest004
 * @tc.desc: Test AnimatorOption function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, NodeAnimateTest004, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    EXPECT_EQ(OH_ArkUI_AnimatorOption_Create(-1), nullptr);
    ArkUI_AnimatorOption* animatorOption = OH_ArkUI_AnimatorOption_Create(0);
    ASSERT_NE(animatorOption, nullptr);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetDuration(animatorOption, -1), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetDuration(animatorOption, 1), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetDuration(nullptr), -1);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetDuration(animatorOption), 1);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetDelay(animatorOption, 1), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetDelay(nullptr), -1);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetDelay(animatorOption), 1);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetIterations(animatorOption, -2), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetIterations(animatorOption, 1), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetIterations(nullptr), -1);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetIterations(animatorOption), 1);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetFill(animatorOption, static_cast<ArkUI_AnimationFillMode>(-1)),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetFill(animatorOption, static_cast<ArkUI_AnimationFillMode>(1000)),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetFill(animatorOption, ARKUI_ANIMATION_FILL_MODE_NONE),
        ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetFill(nullptr), static_cast<ArkUI_AnimationFillMode>(-1));
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetFill(animatorOption), ARKUI_ANIMATION_FILL_MODE_NONE);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetDirection(animatorOption, static_cast<ArkUI_AnimationDirection>(-1)),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetDirection(animatorOption, static_cast<ArkUI_AnimationDirection>(1000)),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetDirection(animatorOption, ARKUI_ANIMATION_DIRECTION_NORMAL),
        ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetDirection(nullptr), static_cast<ArkUI_AnimationDirection>(-1));
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetDirection(animatorOption), ARKUI_ANIMATION_DIRECTION_NORMAL);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetBegin(animatorOption, 0.0f), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetBegin(nullptr), 0.0f);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetBegin(animatorOption), 0.0f);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetEnd(animatorOption, 1.0f), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetEnd(nullptr), 1.0f);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetEnd(animatorOption), 1.0f);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetKeyframe(animatorOption, -1.0f, 0.0f, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetKeyframe(animatorOption, 2.0f, 0.0f, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetKeyframe(animatorOption, 0.5f, 0.0f, -1), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetKeyframe(animatorOption, 0.5f, 0.0f, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
    auto range = new ArkUI_ExpectedFrameRateRange({1, 100, 50});
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetExpectedFrameRateRange(animatorOption, range), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetExpectedFrameRateRange(nullptr), nullptr);
    EXPECT_NE(OH_ArkUI_AnimatorOption_GetExpectedFrameRateRange(animatorOption), nullptr);
    OH_ArkUI_AnimatorOption_Dispose(animatorOption);
    delete range;
    range = nullptr;
}

/**
 * @tc.name: NodeAnimateTest005
 * @tc.desc: Test AnimatorOption Curve function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, NodeAnimateTest005, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_AnimatorOption* animatorOption = OH_ArkUI_AnimatorOption_Create(0);
    ArkUI_AnimatorOption* animatorKeyFrameOption = OH_ArkUI_AnimatorOption_Create(1);
    ASSERT_NE(animatorOption, nullptr);
    ASSERT_NE(animatorKeyFrameOption, nullptr);
    auto icurve = OH_ArkUI_Curve_CreateCurveByType(ArkUI_AnimationCurve::ARKUI_CURVE_LINEAR);
    auto springCurve = OH_ArkUI_Curve_CreateSpringCurve(0.0f, 0.0f, 0.0f, 0.0f);
    auto springMotion = OH_ArkUI_Curve_CreateSpringMotion(0.5f, 0.5f, 0.5f);
    auto responsiveSpringMotion = OH_ArkUI_Curve_CreateResponsiveSpringMotion(0.5f, 0.5f, 0.5f);
    auto interpolatingSpring = OH_ArkUI_Curve_CreateInterpolatingSpring(0.5f, 0.5f, 0.5f, 0.5f);
    auto customCurve = OH_ArkUI_Curve_CreateCustomCurve(nullptr, InterpolateCallback);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetCurve(animatorOption, springCurve), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetCurve(animatorOption, springMotion), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetCurve(animatorOption, responsiveSpringMotion), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetCurve(animatorOption, interpolatingSpring), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetCurve(animatorOption, customCurve), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetCurve(animatorOption, icurve), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetCurve(nullptr), nullptr);
    EXPECT_NE(OH_ArkUI_AnimatorOption_GetCurve(animatorOption), nullptr);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetKeyframeCurve(animatorKeyFrameOption, springCurve, 0),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetKeyframeCurve(animatorKeyFrameOption, springMotion, 0),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetKeyframeCurve(animatorKeyFrameOption, responsiveSpringMotion, 0),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetKeyframeCurve(animatorKeyFrameOption, interpolatingSpring, 0),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetKeyframeCurve(animatorKeyFrameOption, customCurve, 0),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetKeyframeCurve(animatorKeyFrameOption, nullptr, -1),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetKeyframeCurve(animatorKeyFrameOption, nullptr, 1),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetKeyframeCurve(animatorKeyFrameOption, icurve, 0), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetKeyframeCurve(nullptr, 0), nullptr);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetKeyframeCurve(nullptr, -1), nullptr);
    OH_ArkUI_Curve_DisposeCurve(icurve);
    OH_ArkUI_Curve_DisposeCurve(springCurve);
    OH_ArkUI_Curve_DisposeCurve(springMotion);
    OH_ArkUI_Curve_DisposeCurve(responsiveSpringMotion);
    OH_ArkUI_Curve_DisposeCurve(customCurve);
    OH_ArkUI_AnimatorOption_Dispose(animatorOption);
    OH_ArkUI_AnimatorOption_Dispose(animatorKeyFrameOption);
}

/**
 * @tc.name: NodeAnimateTest006
 * @tc.desc: Test AnimatorOption Keyframe function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, NodeAnimateTest006, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_AnimatorOption* animatorOption = OH_ArkUI_AnimatorOption_Create(1);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_SetKeyframe(animatorOption, 0.5f, 0.0f, 0), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetKeyframeTime(nullptr, 0), -1.0f);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetKeyframeTime(animatorOption, -1), -1.0f);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetKeyframeTime(animatorOption, 1), -1.0f);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetKeyframeTime(animatorOption, 0), 0.5f);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetKeyframeValue(nullptr, 0), -1.0f);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetKeyframeValue(animatorOption, -1), -1.0f);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetKeyframeValue(animatorOption, 1), -1.0f);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_GetKeyframeValue(animatorOption, 0), 0.0f);
    OH_ArkUI_AnimatorOption_Dispose(animatorOption);
}

/**
 * @tc.name: NodeAnimateTest007
 * @tc.desc: Test Animator function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, NodeAnimateTest007, TestSize.Level1)
{
    auto animateAPI = reinterpret_cast<ArkUI_NativeAnimateAPI_1*>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_ANIMATE, "ArkUI_NativeAnimateAPI_1"));
    struct ArkUI_Context context= {1};
    ArkUI_AnimatorOption* animatorOption = OH_ArkUI_AnimatorOption_Create(1);
    auto handle = animateAPI->createAnimator(&context, animatorOption);
    ASSERT_NE(handle, nullptr);
    EXPECT_EQ(OH_ArkUI_Animator_ResetAnimatorOption(handle, animatorOption), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Animator_Play(handle), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Animator_Finish(handle), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Animator_Pause(handle), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Animator_Cancel(handle), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_Animator_Reverse(handle), ARKUI_ERROR_CODE_PARAM_INVALID);
    OH_ArkUI_AnimatorOption_Dispose(animatorOption);
    animateAPI->disposeAnimator(handle);
}

/**
 * @tc.name: NodeAnimateTest008
 * @tc.desc: Test AnimatorEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, NodeAnimateTest008, TestSize.Level1)
{
    ASSERT_TRUE(OHOS::Ace::NodeModel::InitialFullImpl());
    ArkUI_AnimatorOption* animatorOption = OH_ArkUI_AnimatorOption_Create(1);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_RegisterOnFrameCallback(nullptr, nullptr, nullptr),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_RegisterOnFrameCallback(animatorOption, nullptr, nullptr),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_RegisterOnFrameCallback(animatorOption, nullptr, AnimatorOnFrameEventCallback),
        ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_RegisterOnFinishCallback(nullptr, nullptr, nullptr),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_RegisterOnFinishCallback(animatorOption, nullptr, nullptr),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_RegisterOnFinishCallback(animatorOption, nullptr, AnimatorEventCallback),
        ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_RegisterOnCancelCallback(nullptr, nullptr, nullptr),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_RegisterOnCancelCallback(animatorOption, nullptr, nullptr),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_RegisterOnCancelCallback(animatorOption, nullptr, AnimatorEventCallback),
        ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_RegisterOnRepeatCallback(nullptr, nullptr, nullptr),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_RegisterOnRepeatCallback(animatorOption, nullptr, nullptr),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_AnimatorOption_RegisterOnRepeatCallback(animatorOption, nullptr, AnimatorEventCallback),
        ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_AnimatorOption_Dispose(animatorOption);
}

/**
 * @tc.name: MotionPathOptionsCreate001
 * @tc.desc: Test creation of MotionPathOptions instance, verify default values and path initialization
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, MotionPathOptionsCreate001, TestSize.Level1)
{
    ArkUI_MotionPathOptions* options = OH_ArkUI_MotionPathOptions_Create();
    ASSERT_NE(options, nullptr);
    ASSERT_NE(options->path, nullptr);
    EXPECT_STREQ(options->path, "");
    float fromVal = -1.0f;
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_GetFrom(options, &fromVal), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_FLOAT_EQ(fromVal, 0.0f);
    float toVal = -1.0f;
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_GetTo(options, &toVal), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_FLOAT_EQ(toVal, 1.0f);
    bool rotatableVal = true;
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_GetRotatable(options, &rotatableVal), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(rotatableVal, false);
    OH_ArkUI_MotionPathOptions_Dispose(options);
}

/**
 * @tc.name: MotionPathOptionsDispose001
 * @tc.desc: Test disposal of MotionPathOptions instance, cover null pointer and valid pointer with path branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, MotionPathOptionsDispose001, TestSize.Level1)
{
    OH_ArkUI_MotionPathOptions_Dispose(nullptr);
    ArkUI_MotionPathOptions* tempOptions = OH_ArkUI_MotionPathOptions_Create();
    OH_ArkUI_MotionPathOptions_SetPath(tempOptions, "M10,10");
    OH_ArkUI_MotionPathOptions_Dispose(tempOptions);
}

/**
 * @tc.name: MotionPathOptionsSetPath001
 * @tc.desc: Test setting path of MotionPathOptions, cover all parameter and execution branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, MotionPathOptionsSetPath001, TestSize.Level1)
{
    ArkUI_MotionPathOptions* options = OH_ArkUI_MotionPathOptions_Create();
    ASSERT_NE(options, nullptr);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetPath(nullptr, "M0,0"), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetPath(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_STREQ(options->path, "");
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetPath(options, ""), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_STREQ(options->path, "");
    const char* validPath = "M0,0 L100,100 Z";
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetPath(options, validPath), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_STREQ(options->path, validPath);
    OH_ArkUI_MotionPathOptions_Dispose(options);
}

/**
 * @tc.name: MotionPathOptionsGetPath001
 * @tc.desc: Test getting path of MotionPathOptions, cover all parameter and buffer branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, MotionPathOptionsGetPath001, TestSize.Level1)
{
    ArkUI_MotionPathOptions* options = OH_ArkUI_MotionPathOptions_Create();
    ASSERT_NE(options, nullptr);
    const char* testPath = "M0,0 L200,200 Z";
    OH_ArkUI_MotionPathOptions_SetPath(options, testPath);
    int32_t writeLen = -1;
    char buffer[50] = { 0 };
    EXPECT_EQ(
        OH_ArkUI_MotionPathOptions_GetPath(nullptr, buffer, sizeof(buffer), &writeLen), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_GetPath(options, nullptr, sizeof(buffer), &writeLen),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_GetPath(options, buffer, 0, &writeLen), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_GetPath(options, buffer, -10, &writeLen), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(
        OH_ArkUI_MotionPathOptions_GetPath(options, buffer, sizeof(buffer), nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    int32_t srcLen = static_cast<int32_t>(strlen(testPath));
    EXPECT_EQ(
        OH_ArkUI_MotionPathOptions_GetPath(options, buffer, srcLen, &writeLen), ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR);
    EXPECT_EQ(writeLen, srcLen + 1);
    OH_ArkUI_MotionPathOptions_Dispose(options);
}

/**
 * @tc.name: MotionPathOptionsSetFrom001
 * @tc.desc: Test setting from value of MotionPathOptions, cover all parameter validation branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, MotionPathOptionsSetFrom001, TestSize.Level1)
{
    ArkUI_MotionPathOptions* options = OH_ArkUI_MotionPathOptions_Create();
    ASSERT_NE(options, nullptr);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetFrom(nullptr, 0.5f), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetFrom(options, -0.1f), ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetFrom(options, 1.1f), ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE);
    OH_ArkUI_MotionPathOptions_SetTo(options, 0.3f);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetFrom(options, 0.5f), ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetFrom(options, 0.2f), ARKUI_ERROR_CODE_NO_ERROR);
    float fromVal = -1.0f;
    OH_ArkUI_MotionPathOptions_GetFrom(options, &fromVal);
    EXPECT_FLOAT_EQ(fromVal, 0.2f);
    OH_ArkUI_MotionPathOptions_SetTo(options, 1.0f);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetFrom(options, 1.0f), ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_MotionPathOptions_GetFrom(options, &fromVal);
    EXPECT_FLOAT_EQ(fromVal, 1.0f);
    OH_ArkUI_MotionPathOptions_Dispose(options);
}

/**
 * @tc.name: MotionPathOptionsGetFrom001
 * @tc.desc: Test getting from value of MotionPathOptions, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, MotionPathOptionsGetFrom001, TestSize.Level1)
{
    ArkUI_MotionPathOptions* options = OH_ArkUI_MotionPathOptions_Create();
    ASSERT_NE(options, nullptr);
    float fromVal = -1.0f;
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_GetFrom(nullptr, &fromVal), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_GetFrom(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_FLOAT_EQ(fromVal, -1.0f);
    OH_ArkUI_MotionPathOptions_SetFrom(options, 0.7f);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_GetFrom(options, &fromVal), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_FLOAT_EQ(fromVal, 0.7f);
    OH_ArkUI_MotionPathOptions_Dispose(options);
}

/**
 * @tc.name: MotionPathOptionsSetTo001
 * @tc.desc: Test setting to value of MotionPathOptions, cover all parameter validation branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, MotionPathOptionsSetTo001, TestSize.Level1)
{
    ArkUI_MotionPathOptions* options = OH_ArkUI_MotionPathOptions_Create();
    ASSERT_NE(options, nullptr);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetTo(nullptr, 0.5f), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetTo(options, -0.2f), ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetTo(options, 1.2f), ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE);
    OH_ArkUI_MotionPathOptions_SetFrom(options, 0.6f);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetTo(options, 0.4f), ARKUI_ERROR_CODE_PARAM_OUT_OF_RANGE);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetTo(options, 0.8f), ARKUI_ERROR_CODE_NO_ERROR);
    float toVal = -1.0f;
    OH_ArkUI_MotionPathOptions_GetTo(options, &toVal);
    EXPECT_FLOAT_EQ(toVal, 0.8f);
    OH_ArkUI_MotionPathOptions_SetFrom(options, 0.0f);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetTo(options, 0.0f), ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_MotionPathOptions_GetTo(options, &toVal);
    EXPECT_FLOAT_EQ(toVal, 0.0f);
    OH_ArkUI_MotionPathOptions_Dispose(options);
}

/**
 * @tc.name: MotionPathOptionsGetTo001
 * @tc.desc: Test getting to value of MotionPathOptions, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, MotionPathOptionsGetTo001, TestSize.Level1)
{
    ArkUI_MotionPathOptions* options = OH_ArkUI_MotionPathOptions_Create();
    ASSERT_NE(options, nullptr);
    float toVal = -1.0f;
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_GetTo(nullptr, &toVal), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_GetTo(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_FLOAT_EQ(toVal, -1.0f);
    OH_ArkUI_MotionPathOptions_SetTo(options, 0.4f);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_GetTo(options, &toVal), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_FLOAT_EQ(toVal, 0.4f);
    OH_ArkUI_MotionPathOptions_Dispose(options);
}

/**
 * @tc.name: MotionPathOptionsSetRotatable001
 * @tc.desc: Test setting rotatable property of MotionPathOptions, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, MotionPathOptionsSetRotatable001, TestSize.Level1)
{
    ArkUI_MotionPathOptions* options = OH_ArkUI_MotionPathOptions_Create();
    ASSERT_NE(options, nullptr);

    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetRotatable(nullptr, true), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetRotatable(options, true), ARKUI_ERROR_CODE_NO_ERROR);
    bool rotatableVal = false;
    OH_ArkUI_MotionPathOptions_GetRotatable(options, &rotatableVal);
    EXPECT_EQ(rotatableVal, true);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_SetRotatable(options, false), ARKUI_ERROR_CODE_NO_ERROR);
    OH_ArkUI_MotionPathOptions_GetRotatable(options, &rotatableVal);
    EXPECT_EQ(rotatableVal, false);
    OH_ArkUI_MotionPathOptions_Dispose(options);
}

/**
 * @tc.name: MotionPathOptionsGetRotatable001
 * @tc.desc: Test getting rotatable property of MotionPathOptions, cover null and valid options branches
 * @tc.type: FUNC
 */
HWTEST_F(NodeAnimateTest, MotionPathOptionsGetRotatable001, TestSize.Level1)
{
    ArkUI_MotionPathOptions* options = OH_ArkUI_MotionPathOptions_Create();
    ASSERT_NE(options, nullptr);
    bool rotatableVal = true;
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_GetRotatable(nullptr, &rotatableVal), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_GetRotatable(options, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(rotatableVal, true);
    OH_ArkUI_MotionPathOptions_SetRotatable(options, true);
    EXPECT_EQ(OH_ArkUI_MotionPathOptions_GetRotatable(options, &rotatableVal), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(rotatableVal, true);
    OH_ArkUI_MotionPathOptions_Dispose(options);
}
} // namespace OHOS::Ace