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

#ifndef ARKUI_NATIVE_ANIMATE_H
#define ARKUI_NATIVE_ANIMATE_H

#include <cstdint>

#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief Defines the expected frame rate range of the animation.
*
* @since 12
*/
typedef struct {
    /** Expected minimum frame rate. */
    uint32_t min;
    /** Expected maximum frame rate. */
    uint32_t max;
    /** Expected optimal frame rate. */
    uint32_t expected;
} ArkUI_ExpectedFrameRateRange;

/**
* @brief Defines the callback type for when the animation playback is complete.
*
* @since 12
*/
typedef struct {
    /** Type of the <b>onFinish</b> callback. */
    ArkUI_FinishCallbackType type;
    /** Callback invoked when the animation playback is complete. */
    void (*callback)(void* userData);
    /** Custom type. */
    void* userData;
} ArkUI_AnimateCompleteCallback;

/**
* @brief Defines the animation configuration.
*
* @since 12
*/
typedef struct ArkUI_AnimateOption ArkUI_AnimateOption;

typedef struct ArkUI_Curve ArkUI_Curve;
typedef struct ArkUI_Curve* ArkUI_CurveHandle;

typedef struct ArkUI_KeyframeAnimateOption ArkUI_KeyframeAnimateOption;
typedef struct ArkUI_AnimatorOption ArkUI_AnimatorOption;
typedef struct ArkUI_Animator* ArkUI_AnimatorHandle;

typedef struct ArkUI_AnimatorEvent ArkUI_AnimatorEvent;
typedef struct ArkUI_AnimatorOnFrameEvent ArkUI_AnimatorOnFrameEvent;


typedef struct ArkUI_TransitionEffect ArkUI_TransitionEffect;

/**
 * @brief Implements the native animation APIs provided by ArkUI.
 *
 * @version 1
 * @since 12
 */
typedef struct {
    /**
    * @brief Defines an explicit animation.
    *
    * @note Make sure the component attributes to be set in the event closure have been set before.
    *
    * @param context UIContext。
    * @param option Indicates the pointer to an animation configuration.
    * @param update Indicates the animation closure. The system automatically inserts a transition animation
    * for the state change caused by the closure.
    * @param complete Indicates the callback to be invoked when the animation playback is complete.
    * @return Returns <b>0</b> if the operation is successful; returns <b>401</b> if a parameter error occurs.
    */
    int32_t (*animateTo)(ArkUI_ContextHandle context, ArkUI_AnimateOption* option, ArkUI_ContextCallback* update,
        ArkUI_AnimateCompleteCallback* complete);

    int32_t (*keyframeAnimateTo)(ArkUI_ContextHandle context, ArkUI_KeyframeAnimateOption* option);
    ArkUI_AnimatorHandle (*createAnimator)(ArkUI_ContextHandle context, ArkUI_AnimatorOption* option);
    void (*disposeAnimator)(ArkUI_AnimatorHandle animator);
} ArkUI_NativeAnimateAPI_1;

/**
* @brief Creates an animation configuration.
*
* @return Returns the pointer to the created animation configuration.
* @since 12
*/
ArkUI_AnimateOption* OH_ArkUI_AnimateOption_Create(void);

/**
* @brief Destroys an animation configuration.
*
* @since 12
*/
void OH_ArkUI_AnimateOption_Dispose(ArkUI_AnimateOption* option);

/**
* @brief Obtains the animation duration, in milliseconds.
*
* @param option Indicates the pointer to an animation configuration.
* @return Returns the duration.
* @since 12
*/
uint32_t OH_ArkUI_AnimateOption_GetDuration(ArkUI_AnimateOption* option);

/**
* @brief Obtains the animation playback speed.
*
* @param option Indicates the pointer to an animation configuration.
* @return Returns the animation playback speed.
* @since 12
*/
float OH_ArkUI_AnimateOption_GetTempo(ArkUI_AnimateOption* option);

/**
* @brief Obtains the animation curve.
*
* @param option Indicates the pointer to an animation configuration.
* @return Returns the animated curve.
* @since 12
*/
ArkUI_AnimationCurve OH_ArkUI_AnimateOption_GetCurve(ArkUI_AnimateOption* option);

/**
* @brief Obtains the animation delay, in milliseconds.
*
* @param option Indicates the pointer to an animation configuration.
* @return Returns the animation delay.
* @since 12
*/
int32_t OH_ArkUI_AnimateOption_GetDelay(ArkUI_AnimateOption* option);

/**
* @brief Obtains the number of times that an animation is played.
*
* @param option Indicates the pointer to an animation configuration.
* @return Returns the number of times that the animation is played.
* @since 12
*/
int32_t OH_ArkUI_AnimateOption_GetIterations(ArkUI_AnimateOption* option);

/**
* @brief Obtains the animation playback mode.
*
* @param option Indicates the pointer to an animation configuration.
* @return Returns the animation playback mode.
* @since 12
*/
ArkUI_AnimationPlayMode OH_ArkUI_AnimateOption_GetPlayMode(ArkUI_AnimateOption* option);

/**
* @brief Obtains the expected frame rate range of an animation.
*
* @param option Indicates the pointer to an animation configuration.
* @return Returns the expected frame rate range.
* @since 12
*/
ArkUI_ExpectedFrameRateRange* OH_ArkUI_AnimateOption_GetExpectedFrameRateRange(ArkUI_AnimateOption* option);

/**
* @brief Sets the animation duration.
*
* @param option Indicates the pointer to an animation configuration.
* @param value Indicates the duration, in milliseconds.
* @since 12
*/
void OH_ArkUI_AnimateOption_SetDuration(ArkUI_AnimateOption* option, int32_t value);

/**
* @brief Sets the animation playback speed.
*
* @param option Indicates the pointer to an animation configuration.
* @param value Indicates the animation playback speed.
* @since 12
*/
void OH_ArkUI_AnimateOption_SetTempo(ArkUI_AnimateOption* option, float value);

/**
* @brief Sets the animation curve.
*
* @param option Indicates the pointer to an animation configuration.
* @param value Indicates the animated curve.
* @since 12
*/
void OH_ArkUI_AnimateOption_SetCurve(ArkUI_AnimateOption* option, ArkUI_AnimationCurve value);

/**
* @brief Sets the animation delay.
*
* @param option Indicates the pointer to an animation configuration.
* @param value Indicates the animation delay.
* @since 12
*/
void OH_ArkUI_AnimateOption_SetDelay(ArkUI_AnimateOption* option, int32_t value);

/**
* @brief Sets the number of times that an animation is played.
*
* @param option Indicates the pointer to an animation configuration.
* @param value Indicates the number of times that the animation is played.
* @since 12
*/
void OH_ArkUI_AnimateOption_SetIterations(ArkUI_AnimateOption* option, int32_t value);

/**
* @brief Sets the animation playback mode.
*
* @param option Indicates the pointer to an animation configuration.
* @param value Indicates the animation playback mode.
* @since 12
*/
void OH_ArkUI_AnimateOption_SetPlayMode(ArkUI_AnimateOption* option, ArkUI_AnimationPlayMode value);

/**
* @brief Sets the expected frame rate range of an animation.
*
* @param option Indicates the pointer to an animation configuration.
* @param value Indicates the expected frame rate range.
* @since 12
*/
void OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(ArkUI_AnimateOption* option, ArkUI_ExpectedFrameRateRange* value);

void OH_ArkUI_AnimateOption_SetICurve(ArkUI_AnimateOption* option, ArkUI_CurveHandle value);
ArkUI_CurveHandle OH_ArkUI_AnimateOption_GetICurve(ArkUI_AnimateOption* option);

ArkUI_KeyframeAnimateOption* OH_ArkUI_KeyframeAnimateOption_Create(int32_t size);
void OH_ArkUI_KeyframeAnimateOption_Dispose(ArkUI_KeyframeAnimateOption* option);
int32_t OH_ArkUI_KeyframeAnimateOption_SetDelay(ArkUI_KeyframeAnimateOption* option, int32_t value);
int32_t OH_ArkUI_KeyframeAnimateOption_SetIterations(ArkUI_KeyframeAnimateOption* option, int32_t value);
int32_t OH_ArkUI_KeyframeAnimateOption_RegisterOnFinishCallback(
    ArkUI_KeyframeAnimateOption* option, void* userData, void (*onFinish)(void* userData));
int32_t OH_ArkUI_KeyframeAnimateOption_SetDuration(ArkUI_KeyframeAnimateOption* option, int32_t value, int32_t index);
int32_t OH_ArkUI_KeyframeAnimateOption_SetCurve(
    ArkUI_KeyframeAnimateOption* option, ArkUI_CurveHandle value, int32_t index);
int32_t OH_ArkUI_KeyframeAnimateOption_RegisterOnEventCallback(
    ArkUI_KeyframeAnimateOption* option, void* userData, void (*event)(void* userData), int32_t index);
int32_t OH_ArkUI_KeyframeAnimateOption_GetDelay(ArkUI_KeyframeAnimateOption* option);
int32_t OH_ArkUI_KeyframeAnimateOption_GetIterations(ArkUI_KeyframeAnimateOption* option);
int32_t OH_ArkUI_KeyframeAnimateOption_GetDuration(ArkUI_KeyframeAnimateOption* option, int32_t index);
ArkUI_CurveHandle OH_ArkUI_KeyframeAnimateOption_GetCurve(ArkUI_KeyframeAnimateOption* option, int32_t index);
ArkUI_AnimatorOption* OH_ArkUI_AnimatorOption_Create(int32_t keyframeSize);
void OH_ArkUI_AnimatorOption_Dispose(ArkUI_AnimatorOption* option);
int32_t OH_ArkUI_AnimatorOption_SetDuration(ArkUI_AnimatorOption* option, int32_t value);
int32_t OH_ArkUI_AnimatorOption_SetDelay(ArkUI_AnimatorOption* option, int32_t value);
int32_t OH_ArkUI_AnimatorOption_SetIterations(ArkUI_AnimatorOption* option, int32_t value);
int32_t OH_ArkUI_AnimatorOption_SetFill(ArkUI_AnimatorOption* option, ArkUI_AnimationFillMode value);
int32_t OH_ArkUI_AnimatorOption_SetDirection(ArkUI_AnimatorOption* option, ArkUI_AnimationDirection value);
int32_t OH_ArkUI_AnimatorOption_SetCurve(ArkUI_AnimatorOption* option, ArkUI_CurveHandle value);
int32_t OH_ArkUI_AnimatorOption_SetBegin(ArkUI_AnimatorOption* option, float value);
int32_t OH_ArkUI_AnimatorOption_SetEnd(ArkUI_AnimatorOption* option, float value);
int32_t OH_ArkUI_AnimatorOption_SetExpectedFrameRateRange(
    ArkUI_AnimatorOption* option, ArkUI_ExpectedFrameRateRange* value);
int32_t OH_ArkUI_AnimatorOption_SetKeyframe(ArkUI_AnimatorOption* option, float time, float value, int32_t index);
int32_t OH_ArkUI_AnimatorOption_SetKeyframeCurve(ArkUI_AnimatorOption* option, ArkUI_CurveHandle value, int32_t index);
int32_t OH_ArkUI_AnimatorOption_GetDuration(ArkUI_AnimatorOption* option);
int32_t OH_ArkUI_AnimatorOption_GetDelay(ArkUI_AnimatorOption* option);
int32_t OH_ArkUI_AnimatorOption_GetIterations(ArkUI_AnimatorOption* option);
ArkUI_AnimationFillMode OH_ArkUI_AnimatorOption_GetFill(ArkUI_AnimatorOption* option);
ArkUI_AnimationDirection OH_ArkUI_AnimatorOption_GetDirection(ArkUI_AnimatorOption* option);
ArkUI_CurveHandle OH_ArkUI_AnimatorOption_GetCurve(ArkUI_AnimatorOption* option);
float OH_ArkUI_AnimatorOption_GetBegin(ArkUI_AnimatorOption* option);
float OH_ArkUI_AnimatorOption_GetEnd(ArkUI_AnimatorOption* option);
ArkUI_ExpectedFrameRateRange* OH_ArkUI_AnimatorOption_GetExpectedFrameRateRange(ArkUI_AnimatorOption* option);
float OH_ArkUI_AnimatorOption_GetKeyframeTime(ArkUI_AnimatorOption* option, int32_t index);
float OH_ArkUI_AnimatorOption_GetKeyframeValue(ArkUI_AnimatorOption* option, int32_t index);
ArkUI_CurveHandle OH_ArkUI_AnimatorOption_GetKeyframeCurve(ArkUI_AnimatorOption* option, int32_t index);
void* OH_ArkUI_AnimatorEvent_GetUserData(ArkUI_AnimatorEvent* event);
void* OH_ArkUI_AnimatorOnFrameEvent_GetUserData(ArkUI_AnimatorOnFrameEvent* event);
float OH_ArkUI_AnimatorOnFrameEvent_GetValue(ArkUI_AnimatorOnFrameEvent* event);
int32_t OH_ArkUI_AnimatorOption_RegisterOnFrameCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorOnFrameEvent* event));
int32_t OH_ArkUI_AnimatorOption_RegisterOnFinishCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event));
int32_t OH_ArkUI_AnimatorOption_RegisterOnCancelCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event));
int32_t OH_ArkUI_AnimatorOption_RegisterOnRepeatCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event));
int32_t OH_ArkUI_Animator_ResetAnimatorOption(ArkUI_AnimatorHandle animator, ArkUI_AnimatorOption* option);
int32_t OH_ArkUI_Animator_Play(ArkUI_AnimatorHandle animator);
int32_t OH_ArkUI_Animator_Finish(ArkUI_AnimatorHandle animator);
int32_t OH_ArkUI_Animator_Pause(ArkUI_AnimatorHandle animator);
int32_t OH_ArkUI_Animator_Cancel(ArkUI_AnimatorHandle animator);
int32_t OH_ArkUI_Animator_Reverse(ArkUI_AnimatorHandle animator);
ArkUI_CurveHandle OH_ArkUI_Curve_CreateCurveByType(ArkUI_AnimationCurve curve);
ArkUI_CurveHandle OH_ArkUI_Curve_CreateStepsCurve(int32_t count, bool end);
ArkUI_CurveHandle OH_ArkUI_Curve_CreateCubicBezierCurve(float x1, float y1, float x2, float y2);
ArkUI_CurveHandle OH_ArkUI_Curve_CreateSpringCurve(float velocity, float mass, float stiffness, float damping);
ArkUI_CurveHandle OH_ArkUI_Curve_CreateSpringMotion(float response, float dampingFraction, float overlapDuration);
ArkUI_CurveHandle OH_ArkUI_Curve_CreateResponsiveSpringMotion(
    float response, float dampingFraction, float overlapDuration);
ArkUI_CurveHandle OH_ArkUI_Curve_CreateInterpolatingSpring(float velocity, float mass, float stiffness, float damping);
ArkUI_CurveHandle OH_ArkUI_Curve_CreateCustomCurve(
    void* userData, float (*interpolate)(float fraction, void* userdata));
void OH_ArkUI_Curve_DisposeCurve(ArkUI_CurveHandle curveHandle);

ArkUI_TransitionEffect* OH_ArkUI_CreateOpacityTransitionEffect(float opacity);
ArkUI_TransitionEffect* OH_ArkUI_CreateTranslationTransitionEffect(ArkUI_TranslationOptions* translate);
ArkUI_TransitionEffect* OH_ArkUI_CreateScaleTransitionEffect(ArkUI_ScaleOptions* scale);
ArkUI_TransitionEffect* OH_ArkUI_CreateRotationTransitionEffect(ArkUI_RotationOptions* rotate);
ArkUI_TransitionEffect* OH_ArkUI_CreateMovementTransitionEffect(ArkUI_TransitionEdge move);
ArkUI_TransitionEffect* OH_ArkUI_CreateAsymmetricTransitionEffect(
    ArkUI_TransitionEffect* appear, ArkUI_TransitionEffect* disappear);
void OH_ArkUI_TransitionEffect_Dispose(ArkUI_TransitionEffect* effect);
int32_t OH_ArkUI_TransitionEffect_Combine(ArkUI_TransitionEffect* effect, ArkUI_TransitionEffect* combine);
int32_t OH_ArkUI_TransitionEffect_SetAnimation(ArkUI_TransitionEffect* effect, ArkUI_AnimateOption* animation);
#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_ANIMATE_H