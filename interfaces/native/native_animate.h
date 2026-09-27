/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

/**
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Provides animation callbacks of ArkUI on the native side.
 *
 * @since 12
 */

/**
 * @file native_animate.h
 *
 * @brief Defines a set of animation APIs of ArkUI on the native side. The APIs in **native_animate.h** must be called
 * in the main thread.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_ANIMATE_H
#define ARKUI_NATIVE_ANIMATE_H

#ifdef __cplusplus
#include <cstdint>
#else
#include <stdint.h>
#include <stdbool.h>
#endif

#include "native_type.h"
#include "native_render.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the expected frame rate range of the animation.
 *
 * @since 12
 */
typedef struct {
    /**
     * Expected minimum frame rate, in fps.
     */
    uint32_t min;
    /**
     * Expected maximum frame rate, in fps.
     */
    uint32_t max;
    /**
     * Expected optimal frame rate, in fps.
     */
    uint32_t expected;
} ArkUI_ExpectedFrameRateRange;

/**
 * @brief Defines the callback type for when the animation playback is complete.
 *
 * @since 12
 */
typedef struct {
    /**
     * Callback type for when the animation playback is complete.
     */
    ArkUI_FinishCallbackType type;
    /**
     * Invoked when the animation playback is complete.
     */
    void (*callback)(void* userData);
    /**
     * Custom data passed upon animation end callback.
     */
    void* userData;
} ArkUI_AnimateCompleteCallback;

/**
 * @brief Defines the animation configuration.
 *
 * @since 12
 */
typedef struct ArkUI_AnimateOption ArkUI_AnimateOption;

/**
 * @brief Defines an interpolation curve.
 *
 * @since 12
 */
typedef struct ArkUI_Curve ArkUI_Curve;

/**
 * @brief Defines the pointer to an interpolation curve.
 *
 * @since 12
 */
typedef struct ArkUI_Curve* ArkUI_CurveHandle;

/**
 * @brief Defines the keyframe animation parameter object.
 *
 * @since 12
 */
typedef struct ArkUI_KeyframeAnimateOption ArkUI_KeyframeAnimateOption;

/**
 * @brief Defines the animator parameter object.
 *
 * @since 12
 */
typedef struct ArkUI_AnimatorOption ArkUI_AnimatorOption;

/**
 * @brief Defines the pointer to an animator object.
 *
 * @since 12
 */
typedef struct ArkUI_Animator* ArkUI_AnimatorHandle;

/**
 * @brief Defines the animator callback event object.
 *
 * @since 12
 */
typedef struct ArkUI_AnimatorEvent ArkUI_AnimatorEvent;

/**
 * @brief Defines the callback object when the animator receives a frame.
 *
 * @since 12
 */
typedef struct ArkUI_AnimatorOnFrameEvent ArkUI_AnimatorOnFrameEvent;

/**
 * @brief Defines the transition parameter object for transition property configuration.
 *
 * @since 12
 */
typedef struct ArkUI_TransitionEffect ArkUI_TransitionEffect;

/**
 * @brief Defines the handle to a property animation.
 *
 * @since 26.0.1
 */
typedef struct OH_ArkUI_PropertyAnimation *OH_ArkUI_PropertyAnimationHandle;

/**
 * @brief Defines the handle to a keyframe animation.
 *
 * @since 26.0.1
 */
typedef struct OH_ArkUI_KeyframeAnimation *OH_ArkUI_KeyframeAnimationHandle;

/**
 * @brief Defines the handle to a path animation.
 *
 * @since 26.0.1
 */
typedef struct OH_ArkUI_PathAnimation *OH_ArkUI_PathAnimationHandle;

/**
 * @brief Defines the handle to an animation group.
 *
 * @since 26.0.1
 */
typedef struct OH_ArkUI_AnimationGroup *OH_ArkUI_AnimationGroupHandle;

/**
 * @brief Declares the native animation APIs provided by ArkUI.
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
     * @param context **UIContext** instance.
     * @param option Defines the animation configuration.
     * @param update Closure function for the animation. The system automatically inserts the transition animation if
     *     the state changes in the closure function.
     *     <br>Note: Make sure the component attributes to be set in the closure function have been set before.
     * @param complete Callback invoked when the animation playback is complete.
     * @return <ul>
     *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
     *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
     *         </ul>
     */
    int32_t (*animateTo)(ArkUI_ContextHandle context, ArkUI_AnimateOption* option, ArkUI_ContextCallback* update,
        ArkUI_AnimateCompleteCallback* complete);

    /**
     * @brief Defines a keyframe animation.
     *
     * @param context **UIContext** instance.
     * @param option Keyframe animation parameter.
     * @return <ul>
     *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
     *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
     *         </ul>
     */
    int32_t (*keyframeAnimateTo)(ArkUI_ContextHandle context, ArkUI_KeyframeAnimateOption* option);

    /**
     * @brief Creates an animator object.
     *
     * @param context **UIContext** instance.
     * @param option Animator parameter.
     * @return Returns the pointer to the animator object; returns **NULL** if a parameter error occurs.
     */
    ArkUI_AnimatorHandle (*createAnimator)(ArkUI_ContextHandle context, ArkUI_AnimatorOption* option);

    /**
     * @brief Disposes of an animator object.
     *
     * @param animatorHandle Animator object.
     */
    void (*disposeAnimator)(ArkUI_AnimatorHandle animatorHandle);
} ArkUI_NativeAnimateAPI_1;

/**
 * @brief Creates an animation configuration.
 *
 * @return Pointer to the created animation configuration.
 * @since 12
 */
ArkUI_AnimateOption* OH_ArkUI_AnimateOption_Create();

/**
 * @brief Disposes of an animation configuration.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @since 12
 */
void OH_ArkUI_AnimateOption_Dispose(ArkUI_AnimateOption* option);

/**
 * @brief Obtains the animation duration, in milliseconds.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, **0** is returned.
 * @return Animation duration, in milliseconds. If **option** is invalid, **0** is returned.
 * @since 12
 */
uint32_t OH_ArkUI_AnimateOption_GetDuration(ArkUI_AnimateOption* option);

/**
 * @brief Obtains the playback speed of an animation.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, **0.0** is returned.
 * @return Animation playback speed. Value range: [0, +∞). If **option** is invalid, **0.0** is returned.
 * @since 12
 */
float OH_ArkUI_AnimateOption_GetTempo(ArkUI_AnimateOption* option);

/**
 * @brief Obtains an animation curve.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, **-1** is returned.
 * @return Animation curve. If **option** is invalid,**-1** is returned.
 * @since 12
 */
ArkUI_AnimationCurve OH_ArkUI_AnimateOption_GetCurve(ArkUI_AnimateOption* option);

/**
 * @brief Obtains the animation delay, in milliseconds.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, **0** is returned.
 * @return Delay of animation playback. If **option** is invalid, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_AnimateOption_GetDelay(ArkUI_AnimateOption* option);

/**
 * @brief Obtains the number of times that an animation is played.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, **0** is returned.
 * @return Number of times that the animation is played. If **option** is invalid, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_AnimateOption_GetIterations(ArkUI_AnimateOption* option);

/**
 * @brief Obtains the playback mode of an animation.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, **-1** is returned.
 * @return Animation playback mode. If **option** is invalid,**-1** is returned.
 * @since 12
 */
ArkUI_AnimationPlayMode OH_ArkUI_AnimateOption_GetPlayMode(ArkUI_AnimateOption* option);

/**
 * @brief Obtains the expected frame rate range of an animation.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, **NULL** is returned.
 * @return Expected frame rate range of the animation, in fps. If **option** is invalid, **NULL** is returned.
 * @since 12
 */
ArkUI_ExpectedFrameRateRange* OH_ArkUI_AnimateOption_GetExpectedFrameRateRange(ArkUI_AnimateOption* option);

/**
 * @brief Sets the animation duration, in milliseconds.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @param value Animation duration, in milliseconds. Value range: [0, +∞).
 *     <br>If the value is less than 0, **0** is used.
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetDuration(ArkUI_AnimateOption* option, int32_t value);

/**
 * @brief Sets the playback speed of an animation.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @param value Animation playback speed. Value range: [0, +∞).
 *     <br>**NOTE**
 *     <br>If the value is less than 0, the default value **1** is used.
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetTempo(ArkUI_AnimateOption* option, float value);

/**
 * @brief Animation curve.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @param value Animation curve. Default value: {@link ARKUI_CURVE_LINEAR}. You are advised to use
 *     {@link ARKUI_CURVE_EASE_IN_OUT} to obtain a smoother animation effect.
 *     <br>If the value is abnormal, the setting is invalid.
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetCurve(ArkUI_AnimateOption* option, ArkUI_AnimationCurve value);

/**
 * @brief Sets the animation delay, in milliseconds.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @param value Animation delay, in milliseconds. Value range: (-∞, +∞). Default value: **0**, indicating no animation
 *     delay. A value greater than 0 means to begin the animation after the specified amount of time has elapsed. A
 *     value less than 0 means to begin the animation in advance. If **value** is less than **0** and the absolute value
 *     of **value** is less than the actual animation duration, the animation starts its first frame from the state at
 *     the absolute value. If the absolute value of **value** is greater than or equal to the actual animation duration,
 *     the animation starts its first frame from the end state. The actual animation duration is equal to the duration
 *     of a single animation multiplied by the number of animation playback times.
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetDelay(ArkUI_AnimateOption* option, int32_t value);

/**
 * @brief Sets the number of times that an animation is played.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @param value Number of times that the animation is played. Value range: [-1, +∞). If this parameter is set to **0**,
 *     the animation is not played. If this parameter is set to **-1**, the animation is played for an infinite number
 *     of times. Default value: **1** (played once).
 *     <br>If the value is less than -1, the operation is invalid.
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetIterations(ArkUI_AnimateOption* option, int32_t value);

/**
 * @brief Sets the playback mode for an animation.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @param value Animation playback mode. Default value: {@link ARKUI_ANIMATION_PLAY_MODE_NORMAL}.
 *     <br>If the value is abnormal, the operation is invalid.
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetPlayMode(ArkUI_AnimateOption* option, ArkUI_AnimationPlayMode value);

/**
 * @brief Defines a struct for the expected frame rate range of the animation.
 *
 * @param option Pointer to an animation configuration.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @param value Expected frame rate range of the animation, in fps.
 *     <br>If **value** is set to **NULL**, the operation is invalid.
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetExpectedFrameRateRange(ArkUI_AnimateOption* option, ArkUI_ExpectedFrameRateRange* value);

/**
 * @brief Sets the animation curve for an animation.
 *
 * @note This method is better than the value set by OH_ArkUI_AnimateOption_SetCurve.
 * @param option Animator animation parameters.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @param value Animation curve parameters.
 *     <br>If **value** is set to **NULL**, the operation is invalid.
 * @since 12
 */
void OH_ArkUI_AnimateOption_SetICurve(ArkUI_AnimateOption* option, ArkUI_CurveHandle value);

/**
 * @brief Obtains the animation curve of an animation.
 *
 * @param option Animator animation parameters.
 *     <br>If **option** is set to **NULL**, **NULL** is returned.
 * @return Animation curve parameters. Returns **NULL** if the option parameter is invalid.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_AnimateOption_GetICurve(ArkUI_AnimateOption* option);

/**
 * @brief Creates a keyframe animation parameter object.
 *
 * @param size Number of keyframe animation states.
 *     <br>Returns **NULL** if the value of **size** is less than 0.
 * @return Keyframe animation parameter object. If the value of **size** is less than 0 or if **option** is abnormal, **
 *     NULL** is returned.
 * @since 12
 */
ArkUI_KeyframeAnimateOption* OH_ArkUI_KeyframeAnimateOption_Create(int32_t size);

/**
 * @brief Disposes of a keyframe animation parameter object.
 *
 * @param option Keyframe animation parameter object.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @since 12
 */
void OH_ArkUI_KeyframeAnimateOption_Dispose(ArkUI_KeyframeAnimateOption* option);

/**
 * @brief Sets the overall delay of a keyframe animation, in milliseconds. By default, the keyframe animation starts
 * without any delay.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Animation delay, in milliseconds. Value range: (-∞, +∞). Default value: **0**, indicating no animation
 *     delay. A value greater than 0 means to begin the animation after the specified amount of time has elapsed. A
 *     value less than 0 means to begin the animation in advance. If **value** is less than **0** and the absolute
 *     value of **value** is less than the actual animation duration, the animation starts its first frame from the
 *     state at the absolute value. If the absolute value of **value** is greater than or equal to the actual animation
 *     duration, the animation starts its first frame from the end state. The actual animation duration is equal to the
 *     duration of a single animation multiplied by the number of animation playback times.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_SetDelay(ArkUI_KeyframeAnimateOption* option, int32_t value);

/**
 * @brief Sets the number of times that the keyframe animation is played. By default, the animation is played once. The
 * value **-1** indicates that the animation is played for an unlimited number of times. The value **0** indicates that
 * no animation is played.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Number of times that the animation is played. Value range: [-1, +∞). If this parameter is set to **0**,
 *     the animation is not played. If this parameter is set to **-1**, the animation is played for an infinite number
 *     of times. Default value: **1**, indicating that the animation is played once.
 *     <br>If the value is less than **-1**, the operation is invalid, and the error code
 *     {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_SetIterations(ArkUI_KeyframeAnimateOption* option, int32_t value);

/**
 * @brief Sets the callback invoked when the keyframe animation playback is complete. This function is called after the
 * {@link keyframe animation} has played for the specified number of times.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param userData Pointer to a custom object.
 *     <br>Abnormal value processing is not involved.
 * @param onFinish Indicates the callback.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_RegisterOnFinishCallback(
    ArkUI_KeyframeAnimateOption* option, void* userData, void (*onFinish)(void* userData));

/**
 * @brief Sets the expected frame rate for a keyframe animation.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param frameRate Expected frame rate for the keyframe animation.
 *     <br>If **frameRate** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 19
 */
int32_t OH_ArkUI_KeyframeAnimateOption_SetExpectedFrameRate(
    ArkUI_KeyframeAnimateOption* option, ArkUI_ExpectedFrameRateRange* frameRate);

/**
 * @brief Sets the duration of a keyframe animation, in milliseconds.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
   * @param value Keyframe animation duration, in ms. The default value is 1000 ms. Value range: [0, +∞).
 *     <br>If the value is less than 0, **0** is used.
 * @param index Index of the keyframe state segment.
 *     <br>If the value of **index** is less than 0, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_SetDuration(ArkUI_KeyframeAnimateOption* option, int32_t value, int32_t index);

/**
 * @brief Sets the animation curve for a specific keyframe animation segment.
 *
 * @note Because the <b>springMotion</b>, <b>responsiveSpringMotion</b>, and <b>interpolatingSpring</b> curves do not
 *     have effective duration settings, they are not supported.
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Animation curve to set. Default value: {@link ARKUI_CURVE_EASE_IN_OUT}.
 * @param index Index of the keyframe state segment. Value range: [0, size – 1], where **size** indicates the number of
 *     keyframe animation states.
 *     <br>If the value of **index** is less than 0 or out of range, the error code
 *     {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_SetCurve(
    ArkUI_KeyframeAnimateOption* option, ArkUI_CurveHandle value, int32_t index);

/**
 * @brief Sets the closure function of the state at the time of the keyframe, that is, the state to be reached at the
 * time of the keyframe.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param event Indicates a closure function.
 * @param userData Pointer to a user-defined object.
 *     <br>Abnormal value processing is not involved.
 * @param index Index of the keyframe state segment. Value range: [0, size – 1], where **size** indicates the number of
 *     keyframe animation states.
 *     <br>If the value of **index** is less than 0 or out of range, the error code
 *     {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_RegisterOnEventCallback(
    ArkUI_KeyframeAnimateOption* option, void* userData, void (*event)(void* userData), int32_t index);

/**
 * @brief Obtains the overall delay of a keyframe animation, in milliseconds.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, **0** is returned.
 * @return Overall delay, in milliseconds. If **option** is invalid, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_GetDelay(ArkUI_KeyframeAnimateOption* option);

/**
 * @brief Obtains the number of times that a keyframe animation is played.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, **0** is returned.
 * @return Number of times that the animation is played. If **option** is invalid, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_GetIterations(ArkUI_KeyframeAnimateOption* option);

/**
 * @brief Obtains the expected frame rate from keyframe animation parameters.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, **NULL** is returned.
 * @return Returns the expected frame rate obtained. If **option** is invalid, **NULL** is returned.
 * @since 19
 */
ArkUI_ExpectedFrameRateRange* OH_ArkUI_KeyframeAnimateOption_GetExpectedFrameRate(ArkUI_KeyframeAnimateOption* option);

/**
 * @brief Obtains the duration of a specific state in a keyframe animation, in milliseconds.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, **0** is returned.
 * @param index Index of the keyframe state segment.
 *     <br>If the value of **index** is less than 0, **0** is returned.
 * @return Duration, in milliseconds. If **option** is invalid, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_KeyframeAnimateOption_GetDuration(ArkUI_KeyframeAnimateOption* option, int32_t index);

/**
 * @brief Obtains the animation curve of a specific state in a keyframe animation.
 *
 * @param option Keyframe animation parameters.
 *     <br>If **option** is set to **NULL**, **NULL** is returned.
 * @param index Index of the keyframe state segment.
 *     <br>If the value of **index** is less than 0, **NULL** is returned.
 * @return Animation curve. If the parameter is abnormal, **NULL** is returned.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_KeyframeAnimateOption_GetCurve(ArkUI_KeyframeAnimateOption* option, int32_t index);

/**
 * @brief Creates an **AnimatorOption** object.
 *
 * @note When <b>keyframeSize</b> is greater than 0, the animation interpolation start point is 0, and the animation
 *     interpolation end point is 1; no setting is allowed.
 * @param keyframeSize Number of keyframes.
 *     <br>If the value of **keyframeSize** is less than 0, **NULL** is returned.
 * @return Pointer to the animator parameter object. If the value of **size** is less than 0 or if **option** is
 *     abnormal, **NULL** is returned.
 * @since 12
 */
ArkUI_AnimatorOption* OH_ArkUI_AnimatorOption_Create(int32_t keyframeSize);

/**
 * @brief Disposes of an **AnimatorOption** object.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the operation is invalid.
 * @since 12
 */
void OH_ArkUI_AnimatorOption_Dispose(ArkUI_AnimatorOption* option);

/**
 * @brief Sets the duration of an animator animation, in milliseconds.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Playback duration, in ms. The default value is 0 ms. Value range: [0, +∞).
 *     <br>If the value is less than 0, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetDuration(ArkUI_AnimatorOption* option, int32_t value);

/**
 * @brief Sets the delay time of the animator playback, in milliseconds.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Animation delay, in milliseconds. Value range: (-∞, +∞). Default value: **0**, indicating no animation
 *     delay. A value greater than 0 means to begin the animation after the specified amount of time has elapsed. A
 *     value less than 0 means to begin the animation in advance. If **value** is less than **0** and the absolute
 *     value of **value** is less than the actual animation duration, the animation starts its first frame from the
 *     state at the absolute value. If the absolute value of **value** is greater than or equal to the actual animation
 *     duration, the animation starts its first frame from the end state. The actual animation duration is equal to the
 *     duration of a single animation multiplied by the number of animation playback times.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetDelay(ArkUI_AnimatorOption* option, int32_t value);

/**
 * @brief Sets the number of times that an animator animation is played. By default, the animation is played once. The
 * value **-1** indicates that the animation is played for an unlimited number of times. The value **0** indicates that
 * no animation is played.
 *
 * @note If this parameter is set to a negative value other than <b>-1</b>, the value is invalid. In this case, the
 *     animation is played once.
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Value range: [-1, +∞). If this parameter is set to **0**, the animation is not played. If this
 *     parameter is set to **-1**, the animation is played for an infinite number of times. Default value: **1** (
 *     played once).
 *     <br>If the value is less than -1, the operation is invalid.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetIterations(ArkUI_AnimatorOption* option, int32_t value);

/**
 * @brief Sets the status of the component before and after the animator animation execution.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Status of the component before and after the animator animation execution. Default value:
 *     {@link ARKUI_ANIMATION_FILL_MODE_FORWARDS}.
 *     <br>If the value is less than 0, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetFill(ArkUI_AnimatorOption* option, ArkUI_AnimationFillMode value);

/**
 * @brief Set the playback direction.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Animation playback direction.
 *     <br>If the value is less than 0, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetDirection(ArkUI_AnimatorOption* option, ArkUI_AnimationDirection value);

/**
 * @brief Sets the interpolation curve for the animation of an animator.
 *
 * @note <b>springCurve</b>, <b>springMotion</b>, <b>responsiveSpringMotion</b>, <b>interpolatingSpring</b>,
 *     and <b>customCurve</b> curves are not supported.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Interpolation curve. Default value: {@link ARKUI_CURVE_LINEAR}. You are advised to use
 *     {@link ARKUI_CURVE_EASE_IN_OUT} to obtain a smoother animation effect.
 *     <br>If **value** is set to **NULL**, the default curve {@link ARKUI_CURVE_LINEAR} is used.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetCurve(ArkUI_AnimatorOption* option, ArkUI_CurveHandle value);

/**
 * @brief Sets the interpolation start point of an animation.
 *
 * @note This API does not take effect when the animation is a keyframe animation.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Interpolation start point of the animation. Value range: (-∞, +∞).
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetBegin(ArkUI_AnimatorOption* option, float value);

/**
 * @brief Sets the interpolation end point for the animation of an animator.
 *
 * @note This API does not take effect when the animation is a keyframe animation.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Interpolation end point of the animation. Value range: (-∞, +∞).
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetEnd(ArkUI_AnimatorOption* option, float value);

/**
 * @brief Sets the expected frame rate range of an animation.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Expected frame rate range.
 *     <br>If **value** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetExpectedFrameRateRange(
    ArkUI_AnimatorOption* option, ArkUI_ExpectedFrameRateRange* value);

/**
 * @brief Sets the keyframe parameters of an animator animation.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param time Keyframe time. Value range: [0, 1]. The value must be in ascending order. Default value: evenly
 *     distributed by index (for example, **0.0** for the first frame, **0.5** for the second frame, and **1.0** for
 *     the third frame).
 *     <br>If the value of **time** is less than 0 or greater than 1, the error code
 *     {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Keyframe value. Value range: (-∞, +∞).
 * @param index Keyframe index.
 *     <br>If the value of **index** is less than 0, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetKeyframe(
    ArkUI_AnimatorOption* option, float time, float value, int32_t index);

/**
 * @brief Sets the keyframe curve type for the animation of an animator.
 *
 * @note <b>springCurve</b>, <b>springMotion</b>, <b>responsiveSpringMotion</b>, <b>interpolatingSpring</b>,
 *     and <b>customCurve</b> curves are not supported.
 *
 * @param option Animator parameters.
 *     <br>If **option** is set to **NULL**, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param value Interpolation curve. Default value: **NULL**, indicating linear interpolation.
 * @param index Keyframe index.
 *     <br>If the value of **index** is less than 0, the error code {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_SetKeyframeCurve(ArkUI_AnimatorOption* option, ArkUI_CurveHandle value, int32_t index);
/**
 * @brief Obtains the duration for playing an animation.
 *
 * @param option Animator animation parameters.
 *     <br>If **option** is set to **NULL**, **0** is returned.
 * @return Duration for playing the animation, in milliseconds. If **option** is invalid, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_GetDuration(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the delay for playing an animation.
 *
 * @param option Animator animation parameters. If **option** is set to **NULL**, **0** is returned.
 * @return Delay for playing the animation, in milliseconds. If **option** is invalid, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_GetDelay(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the number of times that an animator animation is played.
 *
 * @param option Animator parameters. If **option** is set to **NULL**, **0** is returned.
 * @return Number of times that the animation is played. If **option** is invalid, **0** is returned.
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_GetIterations(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the status of the component before and after the animator animation execution.
 *
 * @param option Animator animation parameters.
 * @return Status of the component before and after the animator animation execution. If **option** is invalid,**-1**
 *     is returned.
 * @since 12
 */
ArkUI_AnimationFillMode OH_ArkUI_AnimatorOption_GetFill(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the playback direction of an animator animation.
 *
 * @param option Animator animation parameters.
 * @return Animation playback direction. If **option** is invalid,**-1** is returned.
 * @since 12
 */
ArkUI_AnimationDirection OH_ArkUI_AnimatorOption_GetDirection(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the interpolation curve of the animation of an animator.
 *
 * @param option Animator animation parameters.
 * @return Interpolation curve. If **option** is invalid, **NULL** is returned.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_AnimatorOption_GetCurve(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the interpolation start point of an animation.
 *
 * @param option Animator animation parameters.
 * @return Interpolation start point of the animation. If **option** is invalid, **0.0** is returned.
 * @since 12
 */
float OH_ArkUI_AnimatorOption_GetBegin(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the interpolation end point of an animation.
 *
 * @param option Animator animation parameters.
 * @return Interpolation end point of the animation. If **option** is invalid, **0.0** is returned.
 * @since 12
 */
float OH_ArkUI_AnimatorOption_GetEnd(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the expected frame rate range of an animator animation.
 *
 * @param option Animator animation parameters.
 * @return Pointer to the expected frame rate range object. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_ExpectedFrameRateRange* OH_ArkUI_AnimatorOption_GetExpectedFrameRateRange(ArkUI_AnimatorOption* option);

/**
 * @brief Obtains the keyframe time of the animator playback, in milliseconds.
 *
 * @param option Animator parameters.
 * @param index Keyframe index.
 * @return Keyframe time, in milliseconds.
 * @since 12
 */
float OH_ArkUI_AnimatorOption_GetKeyframeTime(ArkUI_AnimatorOption* option, int32_t index);

/**
 * @brief Obtains the keyframe value of an animation.
 *
 * @param option Animator parameters.
 * @param index Keyframe index.
 * @return Keyframe value.
 * @since 12
 */
float OH_ArkUI_AnimatorOption_GetKeyframeValue(ArkUI_AnimatorOption* option, int32_t index);

/**
 * @brief Obtains the interpolation curve for a keyframe in the animation of an animator.
 *
 * @param option Animator parameters.
 * @param index Keyframe index.
 * @return Interpolation curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_AnimatorOption_GetKeyframeCurve(ArkUI_AnimatorOption* option, int32_t index);

/**
 * @brief Obtains the user-defined object in an animation event object.
 *
 * @param event Animation event object.
 * @return User-defined object.
 * @since 12
 */
void* OH_ArkUI_AnimatorEvent_GetUserData(ArkUI_AnimatorEvent* event);

/**
 * @brief Obtains the user-defined object in the frame event of an animation.
 *
 * @param event Animation event object.
 * @return User-defined object.
 * @since 12
 */
void* OH_ArkUI_AnimatorOnFrameEvent_GetUserData(ArkUI_AnimatorOnFrameEvent* event);

/**
 * @brief Obtains the interpolation result in the animation frame callback event object.
 *
 * @param event Animation event object.
 * @return Animation interpolation result.
 *     <br>**NOTE**
 *     <br>During the animation, the interpolation result changes between the interpolation start point
 *     {@link OH_ArkUI_AnimatorOption_SetBegin} and the interpolation end point {@link OH_ArkUI_AnimatorOption_SetEnd}
 *     based on the animation parameters.
 * @since 12
 */
float OH_ArkUI_AnimatorOnFrameEvent_GetValue(ArkUI_AnimatorOnFrameEvent* event);

/**
 * @brief Sets the callback invoked when the animator receives a frame.
 *
 * @param option Animator animation parameters.
 * @param userData User-defined parameter.
 * @param callback Indicates the callback to set.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_RegisterOnFrameCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorOnFrameEvent* event));

/**
 * @brief Sets the callback invoked when the animation playback is complete.
 *
 * @param option Animator animation parameters.
 * @param userData User-defined parameter.
 * @param callback Indicates the callback to set.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_RegisterOnFinishCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event));

/**
 * @brief Sets the callback invoked when the animation playback is canceled.
 *
 * @param option Animator animation parameters.
 * @param userData User-defined parameter.
 * @param callback Indicates the callback to set.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_RegisterOnCancelCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event));

/**
 * @brief Sets the callback invoked when the animation playback is repeated.
 *
 * @param option Animator animation parameters.
 * @param userData User-defined parameter.
 * @param callback Indicates the callback to set.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_AnimatorOption_RegisterOnRepeatCallback(
    ArkUI_AnimatorOption* option, void* userData, void (*callback)(ArkUI_AnimatorEvent* event));

/**
 * @brief Resets the animation of an animator.
 *
 * @param animatorHandle Animator object.
 * @param option Animator animation parameters.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_Animator_ResetAnimatorOption(
    ArkUI_AnimatorHandle animatorHandle, ArkUI_AnimatorOption* option);

/**
 * @brief Starts the animation of an animator.
 *
 * @param animatorHandle Animator object.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_Animator_Play(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief Ends the animation of an animator.
 *
 * @param animatorHandle Animator object.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_Animator_Finish(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief Pauses the animation of an animator.
 *
 * @param animatorHandle Animator object.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_Animator_Pause(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief Cancels the animation of an animator.
 *
 * @param animatorHandle Animator object.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_Animator_Cancel(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief Plays this animation in reverse order.
 *
 * @param animatorHandle Animator object.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_Animator_Reverse(ArkUI_AnimatorHandle animatorHandle);

/**
 * @brief Implements initialization for the interpolation curve, which is used to create an interpolation curve based
 * on the input parameter.
 *
 * @param curve Curve type.
 * @return Pointer to the interpolation object of the curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateCurveByType(ArkUI_AnimationCurve curve);

/**
 * @brief Creates a step curve.
 *
 * @param count Number of steps. The value must be a positive integer. Value range: [1, +∞).
 *     <br>If the value of **count** is abnormal, the operation is invalid.
 * @param end Whether the step change occurs at the start or end of each interval. **true**: The step change occurs at
 *     the end of each interval. **false**: The step change occurs at the start of each interval.
 * @return Pointer to the interpolation object of the curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateStepsCurve(int32_t count, bool end);

/**
 * @brief Creates a cubic Bezier curve.
 *
 * @param x1 X-coordinate of the first point on the Bezier curve. Value range: [0, 1]. A value less than 0 is treated
 *     as **0**. A value greater than 1 is treated as **1**.
 * @param y1 Y-coordinate of the first point on the Bezier curve.
 * @param x2 X-coordinate of the second point on the Bezier curve. Value range: [0, 1]. A value less than 0 is treated
 *     as **0**. A value greater than 1 is treated as **1**.
 * @param y2 Y-coordinate of the second point on the Bezier curve.
 * @return Pointer to the interpolation object of the curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateCubicBezierCurve(float x1, float y1, float x2, float y2);

/**
 * @brief Creates a spring curve. The curve shape is determined by the spring parameters, and the animation duration is
 * controlled by the **duration** parameter in {@link animation} and {@link animateTo}.
 *
   * @param velocity Initial velocity. It is applied by external factors to the spring animation, designed to help
 *     ensure the smooth transition from the previous motion state. The velocity is the normalized velocity, and its
 *     value is equal to the actual velocity at the beginning of the animation divided by the animation attribute
 *     change value.
 * @param mass Mass. It describes the inertia of the object in the elastic system, affecting the amplitude of
 *     oscillation and the speed of return to equilibrium. The greater the mass, the greater the amplitude of the
 *     oscillation, and the slower the speed of restoring to the equilibrium position. Value range: [0, +∞).
 *     <br>If the value is less than or equal to 0, **1** is used.
 * @param stiffness Stiffness. It is the degree to which an object deforms by resisting the force applied. In an
 *     elastic system, the greater the stiffness, the stronger the ability to resist deformation, and the faster the
 *     speed of restoring to the equilibrium position. Value range: [0, +∞).
 *     <br>If the value is less than or equal to 0, **1** is used.
 * @param damping Damping. It is used to describe the oscillation and attenuation of the system after being disturbed.
 *     The larger the damping, the smaller the number of oscillations of elastic motion, and the smaller the
 *     oscillation amplitude. Value range: [0, +∞).
 *     <br>If the value is less than or equal to 0, **1** is used.
 * @return Pointer to the interpolation object of the curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateSpringCurve(float velocity, float mass, float stiffness, float damping);

/**
 * @brief Creates a spring animation curve. If multiple spring animations are applied to the same attribute of an
 * object, each animation replaces their predecessor and inherits the velocity.
 *
 * @note The animation duration is subject to the curve parameters, rather than the <b>duration</b> parameter in
 *     <b>animation</b> or <b>animateTo</b>.
 *
 * @param response Duration of one complete oscillation. Value range: (0, +∞).
 *     <br>If the value is less than or equal to 0, **0.55** is used.
 * @param dampingFraction Damping coefficient. > 0 and < 1: underdamped. In this case, the spring overshoots the
 *     equilibrium position. **1**: critically damped. > 1: overdamped. In this case, the spring approaches equilibrium
 *     gradually. Value range: (0, +∞).
 *     <br>If the value is less than or equal to 0, **0.825** is used.
 * @param overlapDuration Duration for animations to overlap, in seconds. When animations overlap, the **response**
 *     values of these animations will transit smoothly over this duration if they are different. Value range: [0, +∞).
 *     <br>If the value is less than 0, **0** is used.
 * @return Pointer to the interpolation object of the curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateSpringMotion(float response, float dampingFraction, float overlapDuration);

/**
 * @brief Creates a responsive spring animation curve. It is a special case of **springMotion**, with the only
 * difference in the default values. It can be used together with **springMotion**.
 *
 * @note The animation duration is subject to the curve parameters, rather than the <b>duration</b> parameter in
 *     <b>animation</b> or <b>animateTo</b>.
 *
 * @param response Duration of one complete oscillation. Value range: (0, +∞).
 *     <br>If the value is less than or equal to 0, **0.15** is used.
 * @param dampingFraction Damping coefficient. > 0 and < 1: underdamped. In this case, the spring overshoots the
 *     equilibrium position. **1**: critically damped. > 1: overdamped. In this case, the spring approaches equilibrium
 *     gradually. Value range: [0, +∞).
 *     <br>If the value is less than 0, **0.86** is used.
 * @param overlapDuration Duration for animations to overlap, in seconds. When animations overlap, the **response**
 *     values of these animations will transit smoothly over this duration if they are different. Value range: [0, +∞).
 *     <br>If the value is less than 0, **0.25** is used.
 * @return Pointer to the interpolation object of the curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateResponsiveSpringMotion(
    float response, float dampingFraction, float overlapDuration);

/**
 * @brief Creates an interpolating spring curve animated from 0 to 1. The actual animation value is calculated based on
 * the curve.
 *
 * @note The animation duration is subject to the curve parameters, rather than the <b>duration</b> parameter in
 *     <b>animation</b> or <b>animateTo</b>.
 *
 *
   * @param velocity Initial velocity. It is applied by external factors to the spring animation, designed to help
 *     ensure the smooth transition from the previous motion state. The velocity is the normalized velocity, and its
 *     value is equal to the actual velocity at the beginning of the animation divided by the animation attribute
 *     change value.
 * @param mass Mass. It describes the inertia of the object in the elastic system, affecting the amplitude of
 *     oscillation and the speed of return to equilibrium. The greater the mass, the greater the amplitude of the
 *     oscillation, and the slower the speed of restoring to the equilibrium position. Value range: [0, +∞).
 *     <br>If the value is less than or equal to 0, **1** is used.
 * @param stiffness Stiffness. It is the degree to which an object deforms by resisting the force applied. The greater
 *     the stiffness, the stronger the ability to resist deformation, and the faster the speed of restoring to the
 *     equilibrium position. Value range: [0, +∞).
 *     <br>If the value is less than or equal to 0, **1** is used.
 * @param damping Damping. It is used to describe the oscillation and attenuation of the system after being disturbed.
 *     The larger the damping, the smaller the number of oscillations of elastic motion, and the smaller the
 *     oscillation amplitude. Value range: [0, +∞).
 *     <br>If the value is less than or equal to 0, **1** is used.
 * @return Pointer to the interpolation object of the curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateInterpolatingSpring(float velocity, float mass, float stiffness, float damping);

/**
 * @brief Creates a custom curve.
 *
 * @param userData Pointer to user-defined data.
 * @param interpolate Indicates the custom interpolation callback. <b>fraction</b> indicates the input x value for
 *     interpolation when the animation starts; value range: [0,1].
 *     The return value is the y value of the curve; value range: [0,1].
 *     If <b>fraction</b> is <b>0</b>, the return value <b>0</b> corresponds to the animation start point; any other
 *     return
 *     value means that the animation jumps at the start point.
 *     If <b>fraction</b> is <b>1</b>, the return value <b>1</b> corresponds to the animation end point; any other
 *     return
 *     value means that the end value of the animation is not the value of the state variable,
 *     which will result in an effect of transition from that end value to the value of the state variable.
 * @return Pointer to the interpolation object of the curve. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_CurveHandle OH_ArkUI_Curve_CreateCustomCurve(
    void* userData, float (*interpolate)(float fraction, void* userdata));

/**
 * @brief Disposes of a custom curve.
 *
 * @param curveHandle Pointer to the interpolation object of the curve.
 * @since 12
 */
void OH_ArkUI_Curve_DisposeCurve(ArkUI_CurveHandle curveHandle);

/**
 * @brief Creates an opacity effect object for component transitions.
 *
 * @note If the value specified is less than 0, the value <b>0</b> is used. If the value specified is greater than 1,
 *     the value <b>1</b> is used.
 * @param opacity Opacity. Value range: [0, 1]. The default value is **1**. A value less than 0 is treated as 0. A
 *     value greater than 1 is treated as 1. The value **1** means fully opaque, and **0** means fully transparent.
 * @return Opacity effect object for component transitions.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateOpacityTransitionEffect(float opacity);

/**
 * @brief Creates a translation effect object for component transitions.
 *
 * @param translate Translation parameter object for component transitions.
 * @return Translation effect object for component transitions. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateTranslationTransitionEffect(ArkUI_TranslationOptions* translate);

/**
 * @brief Creates a scaling effect object for component transitions.
 *
 * @param scale Scaling parameter object for component transitions.
 * @return Scaling effect object for component transitions. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateScaleTransitionEffect(ArkUI_ScaleOptions* scale);

/**
 * @brief Creates a rotation effect object for component transition.
 *
 * @param rotate Rotation parameter object for component transitions.
 * @return Rotation effect object for component transitions. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateRotationTransitionEffect(ArkUI_RotationOptions* rotate);

/**
 * @brief Creates a movement transition effect object for the component.
 *
 * @param edge Movement transition type.
 * @return Translation effect object for component transitions. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateMovementTransitionEffect(ArkUI_TransitionEdge edge);

/**
 * @brief Creates an asymmetric transition effect.
 *
 * @note If the <b>asymmetric</b> function is not used for <b>TransitionEffect</b>, the transition effect takes effect
 *     for both appearance and disappearance of the component.
 * @param appear Transition effect for appearance.
 * @param disappear Transition effect for disappearance.
 * @return Asymmetric transition effect. Returns **NULL** if a parameter error occurs.
 * @since 12
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateAsymmetricTransitionEffect(
    ArkUI_TransitionEffect* appear, ArkUI_TransitionEffect* disappear);

/**
 * @brief Create an identity transition effect.
 * Identity transition effect performs no visual transition animation. It can alse be used as the appear or disappear
 * parameter of OH_ArkUI_CreateAsymmetricTransitionEffect to indicate no animation on one side.
 *
 * @return Returns a pointer to the created transition effect object.
 * @release native_animate/OH_ArkUI_TransitionEffect_Dispose {return}
 * @since 26.0.0
 */
ArkUI_TransitionEffect* OH_ArkUI_CreateIdentityTransitionEffect(void);

/**
 * @brief Disposes of a transition effect.
 *
 * @param effect Pointer to the transition effect to be disposed.
 * @since 12
 */
void OH_ArkUI_TransitionEffect_Dispose(ArkUI_TransitionEffect* effect);

/**
 * @brief Sets a combination of transition effects.
 *
 * @param firstEffect Transition effect.
 * @param secondEffect Combination of transition effects.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_TransitionEffect_Combine(
    ArkUI_TransitionEffect* firstEffect, ArkUI_TransitionEffect* secondEffect);

/**
 * @brief Sets transition effect animation settings.
 *
 * @note If <b>combine</b> is used for combining transition effects, the animation settings of a transition effect are
 *     applicable to the one following it.
 * @param effect Transition effect.
 * @param animation Animation settings.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 12
 */
int32_t OH_ArkUI_TransitionEffect_SetAnimation(
    ArkUI_TransitionEffect* effect, ArkUI_AnimateOption* animation);

/**
 * @brief Creates a property animation for a specific animatable property.
 *
 * <b>propertyType</b> must be a valid {@link OH_ArkUI_AnimationPropertyType};
 * otherwise, this API returns <b>NULL</b>.
 * @param propertyType [in] Indicates the type of the property to animate.
 * @return Returns the handle to the property animation. The caller owns the returned
 *         handle and must release it with {@link OH_ArkUI_NativeModule_PropertyAnimation_Destroy}.
 * @release native_animate/OH_ArkUI_NativeModule_PropertyAnimation_Destroy {return}
 * @since 26.0.1
 */
OH_ArkUI_PropertyAnimationHandle OH_ArkUI_NativeModule_PropertyAnimation_Create(
    OH_ArkUI_AnimationPropertyType propertyType);

/**
 * @brief Destroys a property animation.
 *
 * @param animation [in] Indicates the property animation handle returned by
 *     {@link OH_ArkUI_NativeModule_PropertyAnimation_Create}. Passing <b>NULL</b> has no effect.
 *     After this function returns for a non-NULL handle, the handle is invalid, is not
 *     reference-counted, and must not be used or destroyed again.
 * @since 26.0.1
 */
void OH_ArkUI_NativeModule_PropertyAnimation_Destroy(OH_ArkUI_PropertyAnimationHandle animation);

/**
 * @brief Sets the start value of a property animation.
 *
 * @param animation [in] Indicates the property animation handle.
 * @param value [in] Indicates the start value. The number and type of elements depend on
 *     {@link OH_ArkUI_AnimationPropertyType}. For example, OPACITY requires 1 f32 value,
 *     and TRANSLATION requires 2 f32 values (x, y).
 * @param size [in] Indicates the number of elements in the value array.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetFromValue(
    OH_ArkUI_PropertyAnimationHandle animation, const ArkUI_NumberValue *value, int32_t size);

/**
 * @brief Obtains the start value of a property animation.
 *
 * @param animation [in] Indicates the property animation handle.
 * @param value [out] Indicates the pointer to receive the start value array of {@link ArkUI_NumberValue}. The number
 *     and type of elements depend on {@link OH_ArkUI_AnimationPropertyType}. For example, OPACITY requires
 *     1 f32 value, and TRANSLATION requires 2 f32 values (x, y). The values are written into the memory
 *     pointed to by this pointer.
 *     <br>This pointer must not be **NULL**. If **value** is set to **NULL**, the error code
 *     {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param size [in] Indicates the size of the output array. It must equal the number of elements required by
 *     {@link OH_ArkUI_AnimationPropertyType}; otherwise, the error code {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR}
 *     is returned.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} if the start value has not been set.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         <li>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the buffer size does not equal the required
 *             buffer size.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetFromValue(
    OH_ArkUI_PropertyAnimationHandle animation, ArkUI_NumberValue *value, int32_t size);

/**
 * @brief Sets the end value of a property animation.
 *
 * @param animation [in] Indicates the property animation handle.
 * @param value [in] Indicates the end value. The number and type of elements depend on
 *     {@link OH_ArkUI_AnimationPropertyType}. For example, OPACITY requires 1 f32 value,
 *     and TRANSLATION requires 2 f32 values (x, y).
 * @param size [in] Indicates the number of elements in the value array.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetToValue(
    OH_ArkUI_PropertyAnimationHandle animation, const ArkUI_NumberValue *value, int32_t size);

/**
 * @brief Obtains the end value of a property animation.
 *
 * @param animation [in] Indicates the property animation handle.
 * @param value [out] Indicates the pointer to receive the end value array of {@link ArkUI_NumberValue}. The number
 *     and type of elements depend on {@link OH_ArkUI_AnimationPropertyType}. For example, OPACITY requires
 *     1 f32 value, and TRANSLATION requires 2 f32 values (x, y). The values are written into the memory
 *     pointed to by this pointer.
 *     <br>This pointer must not be **NULL**. If **value** is set to **NULL**, the error code
 *     {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param size [in] Indicates the size of the output array. It must equal the number of elements required by
 *     {@link OH_ArkUI_AnimationPropertyType}; otherwise, the error code {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR}
 *     is returned.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} if the end value has not been set.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         <li>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the buffer size does not equal the required
 *             buffer size.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetToValue(
    OH_ArkUI_PropertyAnimationHandle animation, ArkUI_NumberValue *value, int32_t size);

/**
 * @brief Sets the duration for a property animation.
 *
 * The actual effective animation duration is determined by priority: if the duration is set via this API,
 * that value is used; otherwise, the duration set on the animation group via
 * {@link OH_ArkUI_NativeModule_AnimationGroup_SetDuration} is used; if neither is set, **1000** ms is used.
 * @param animation [in] Indicates the property animation handle.
 * @param duration [in] Indicates the duration, in milliseconds. The value must be greater than 0.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetDuration(
    OH_ArkUI_PropertyAnimationHandle animation, int32_t duration);

/**
 * @brief Obtains the duration of a property animation.
 *
 * This API returns only the duration explicitly set on this animation; the value inherited from the
 * animation group or the default is resolved at runtime and is not stored on this object. If the duration
 * has not been set on this animation, {@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} is returned. The actual
 * effective animation duration used at runtime is determined by priority: if set via
 * {@link OH_ArkUI_NativeModule_PropertyAnimation_SetDuration}, that value is used; otherwise, the group's
 * duration via {@link OH_ArkUI_NativeModule_AnimationGroup_SetDuration} is used; if neither is set,
 * **1000** ms is used.
 * @param animation [in] Indicates the property animation handle.
 * @param duration [out] Indicates the pointer to receive the duration value, in milliseconds.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} if the duration has not been set.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetDuration(
    OH_ArkUI_PropertyAnimationHandle animation, int32_t *duration);

/**
 * @brief Sets the delay for a property animation.
 *
 * @param animation [in] Indicates the property animation handle.
 * @param delay [in] Indicates the delay, in milliseconds. The default value is <b>0</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetDelay(
    OH_ArkUI_PropertyAnimationHandle animation, int32_t delay);

/**
 * @brief Obtains the delay of a property animation.
 *
 * @param animation [in] Indicates the property animation handle.
 * @param delay [out] Indicates the pointer to receive the delay value, in milliseconds.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetDelay(
    OH_ArkUI_PropertyAnimationHandle animation, int32_t *delay);

/**
 * @brief Sets the animation curve for a property animation.
 *
 * The actual effective animation curve is determined by priority: if the curve is set via this API, that
 * value is used; otherwise, the curve set on the animation group via
 * {@link OH_ArkUI_NativeModule_AnimationGroup_SetCurve} is used; if neither is set,
 * {@link ARKUI_CURVE_LINEAR} is used.
 * Spring curves (<b>springMotion</b>, <b>responsiveSpringMotion</b>, and <b>interpolatingSpring</b>) are
 * supported. When a spring curve is set, the duration set via
 * {@link OH_ArkUI_NativeModule_PropertyAnimation_SetDuration} does not take effect; the animation
 * duration is determined by the spring curve.
 * @param animation [in] Indicates the property animation handle.
 * @param curve [in] Indicates the animation curve. This API does not take ownership of
 *     the curve handle; the caller must ensure the curve remains valid when using this handle.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetCurve(
    OH_ArkUI_PropertyAnimationHandle animation, ArkUI_CurveHandle curve);

/**
 * @brief Obtains the animation curve of a property animation.
 *
 * This API returns only the curve explicitly set on this animation; the value inherited from the
 * animation group or the default is resolved at runtime and is not stored on this object. If the curve
 * has not been set on this animation, {@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} is returned. The actual
 * effective animation curve used at runtime is determined by priority: if set via
 * {@link OH_ArkUI_NativeModule_PropertyAnimation_SetCurve}, that value is used; otherwise, the group's
 * curve via {@link OH_ArkUI_NativeModule_AnimationGroup_SetCurve} is used; if neither is set,
 * {@link ARKUI_CURVE_LINEAR} is used.
 * @param animation [in] Indicates the property animation handle.
 * @param outBorrowedCurve [out] Receives a borrowed curve handle; the caller must not destroy it.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} if the curve has not been set.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetCurve(
    OH_ArkUI_PropertyAnimationHandle animation, ArkUI_CurveHandle *outBorrowedCurve);

/**
 * @brief Sets the tempo for a property animation.
 *
 * @param animation [in] Indicates the property animation handle.
 * @param tempo [in] Indicates the animation tempo. Value range: (0, +∞). The default value is <b>1</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetTempo(
    OH_ArkUI_PropertyAnimationHandle animation, float tempo);

/**
 * @brief Obtains the tempo of a property animation.
 *
 * @param animation [in] Indicates the property animation handle.
 * @param tempo [out] Indicates the pointer to receive the animation tempo.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetTempo(
    OH_ArkUI_PropertyAnimationHandle animation, float *tempo);

/**
 * @brief Sets whether to auto-reverse a property animation.
 *
 * When auto-reverse is enabled, the animation plays forward and then backward alternately
 * across iterations. The default value is <b>false</b>.
 *
 * @param animation [in] Indicates the property animation handle.
 * @param autoReverse [in] Indicates whether to enable auto-reverse. The default value is <b>false</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetAutoReverse(
    OH_ArkUI_PropertyAnimationHandle animation, bool autoReverse);

/**
 * @brief Obtains whether auto-reverse is enabled for a property animation.
 *
 * @param animation [in] Indicates the property animation handle.
 * @param autoReverse [out] Indicates the pointer to receive the value. <b>true</b> if auto-reverse is enabled;
 *     <b>false</b> otherwise. The default value is <b>false</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetAutoReverse(
    OH_ArkUI_PropertyAnimationHandle animation, bool *autoReverse);

/**
 * @brief Sets the number of iterations for a property animation.
 *
 * @param animation [in] Indicates the property animation handle.
 * @param iterations [in] Indicates the number of iterations. The value must be -1 or greater than
 *     or equal to 1; a value of <b>0</b> returns {@link ARKUI_ERROR_CODE_PARAM_INVALID}.
 *     The value <b>-1</b> indicates unlimited iterations. The default value is <b>1</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetIterations(
    OH_ArkUI_PropertyAnimationHandle animation, int32_t iterations);

/**
 * @brief Obtains the number of iterations of a property animation.
 *
 * @param animation [in] Indicates the property animation handle.
 * @param iterations [out] Indicates the pointer to receive the number of iterations.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetIterations(
    OH_ArkUI_PropertyAnimationHandle animation, int32_t *iterations);

/**
 * @brief Sets the target render node for a property animation.
 *
 * The target node is the render node animated by this property animation. If <b>NULL</b> (the default),
 * the animation inherits the group's default target set by
 * {@link OH_ArkUI_NativeModule_AnimationGroup_SetTargetNode}. A non-NULL target must belong to
 * the same UIContext that the group is registered on; the check is
 * performed when the group is registered by {@link OH_ArkUI_NativeModule_AddAnimationGroup}.
 *
 * @param animation [in] Indicates the property animation handle.
 * @param targetNode [in] Indicates the render node to animate. <b>NULL</b> means inheriting the group's default
 *     target. The default value is <b>NULL</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_SetTargetNode(
    OH_ArkUI_PropertyAnimationHandle animation, ArkUI_RenderNodeHandle targetNode);

/**
 * @brief Obtains the target render node of a property animation.
 *
 * @param animation [in] Indicates the property animation handle.
 * @param outBorrowedTargetNode [out] Receives a borrowed render-node handle;
 *     the caller must not destroy it. <b>NULL</b> means inheriting the group's default target.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PropertyAnimation_GetTargetNode(
    OH_ArkUI_PropertyAnimationHandle animation, ArkUI_RenderNodeHandle *outBorrowedTargetNode);

/**
 * @brief Creates a keyframe animation for a specific animatable property.
 *
 * The key time of each keyframe defaults to being evenly distributed in [0, 1] by index (for example,
 * when there are 3 keyframes, <b>0.0</b> for the first frame, <b>0.5</b> for the second frame, and
 * <b>1.0</b> for the third frame).
 * Use {@link OH_ArkUI_NativeModule_KeyframeAnimation_SetKeyTimes} or
 * {@link OH_ArkUI_NativeModule_KeyframeAnimation_SetKeyTime} to customize the key time points.
 *
 * <b>propertyType</b> must be a valid {@link OH_ArkUI_AnimationPropertyType}, and <b>size</b> must be at least 2;
 * otherwise, this API returns <b>NULL</b>.
 * @param propertyType [in] Indicates the type of the property to animate.
 * @param size [in] Indicates the number of keyframes. The value must be greater than or equal to 2.
 * @return Returns the handle to the keyframe animation. The caller owns the returned
 *         handle and must release it with {@link OH_ArkUI_NativeModule_KeyframeAnimation_Destroy}.
 * @release native_animate/OH_ArkUI_NativeModule_KeyframeAnimation_Destroy {return}
 * @since 26.0.1
 */
OH_ArkUI_KeyframeAnimationHandle OH_ArkUI_NativeModule_KeyframeAnimation_Create(
    OH_ArkUI_AnimationPropertyType propertyType, int32_t size);

/**
 * @brief Destroys a keyframe animation.
 *
 * @param animation [in] Indicates the keyframe animation handle returned by
 *     {@link OH_ArkUI_NativeModule_KeyframeAnimation_Create}. Passing <b>NULL</b> has no effect.
 *     After this function returns for a non-NULL handle, the handle is invalid, is not
 *     reference-counted, and must not be used or destroyed again.
 * @since 26.0.1
 */
void OH_ArkUI_NativeModule_KeyframeAnimation_Destroy(OH_ArkUI_KeyframeAnimationHandle animation);

/**
 * @brief Sets the keyframe key time points.
 *
 * If this API is not called, the key time of each keyframe defaults to being evenly distributed in [0, 1]
 * by index (for example, when there are 3 keyframes, <b>0.0</b> for the first frame, <b>0.5</b> for the
 * second frame, and <b>1.0</b> for the third frame).
 *
 * The elements in <b>keyTimes</b> must be non-decreasing, and <b>size</b> must equal the number of keyframes
 * of the keyframe animation (the <b>size</b> value specified when the animation was created via
 * {@link OH_ArkUI_NativeModule_KeyframeAnimation_Create}).
 * @param animation [in] Indicates the keyframe animation handle.
 * @param keyTimes [in] Indicates the array of key time points. Value range of each element: [0, 1].
 * @param size [in] Indicates the number of key time points.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetKeyTimes(
    OH_ArkUI_KeyframeAnimationHandle animation, const float *keyTimes, int32_t size);

/**
 * @brief Obtains the key time point of a keyframe at the specified index.
 *
 * @param animation [in] Indicates the keyframe animation handle.
 * @param index [in] Indicates the keyframe index.
 * @param keyTime [out] Indicates the pointer to receive the key time point.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetKeyTime(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t index, float *keyTime);

/**
 * @brief Sets the key time point of a keyframe at the specified index.
 *
 * If this API is not called for a keyframe, its key time defaults to being evenly distributed in [0, 1]
 * by index (for example, when there are 3 keyframes, <b>0.0</b> for the first frame, <b>0.5</b> for the
 * second frame, and <b>1.0</b> for the third frame).
 *
 * @param animation [in] Indicates the keyframe animation handle.
 * @param index [in] Indicates the keyframe index.
 * @param keyTime [in] Indicates the key time point. Value range: [0, 1].
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetKeyTime(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t index, float keyTime);

/**
 * @brief Sets the value of a keyframe at the specified index.
 *
 * @param animation [in] Indicates the keyframe animation handle.
 * @param index [in] Indicates the keyframe index.
 * @param value [in] Indicates the array of {@link ArkUI_NumberValue}. The number and type of elements depend on
 *     {@link OH_ArkUI_AnimationPropertyType}. For example, OPACITY requires 1 f32 value,
 *     and TRANSLATION requires 2 f32 values (x, y).
 * @param size [in] Indicates the number of elements in the value array.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetValue(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t index, const ArkUI_NumberValue *value, int32_t size);

/**
 * @brief Sets the values for all keyframes at once.
 *
 * The values are provided as a flat array. The number of elements per keyframe depends on
 * {@link OH_ArkUI_AnimationPropertyType}. For example, OPACITY requires 1 value per keyframe,
 * and TRANSLATION requires 2 values per keyframe. The total number of elements must equal
 * the number of keyframes multiplied by the number of values per keyframe.
 *
 * @param animation [in] Indicates the keyframe animation handle.
 * @param values [in] Indicates the flat array of {@link ArkUI_NumberValue} for all keyframes.
 * @param size [in] Indicates the total number of elements in the values array.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetValues(
    OH_ArkUI_KeyframeAnimationHandle animation, const ArkUI_NumberValue *values, int32_t size);

/**
 * @brief Obtains the value of a keyframe at the specified index.
 *
 * @param animation [in] Indicates the keyframe animation handle.
 * @param index [in] Indicates the keyframe index.
 * @param value [out] Indicates the pointer to receive the value array of {@link ArkUI_NumberValue}. The number and
 *     type of elements depend on {@link OH_ArkUI_AnimationPropertyType}. For example, OPACITY requires 1 f32
 *     value, and TRANSLATION requires 2 f32 values (x, y). The values are written into the memory pointed
 *     to by this pointer.
 *     <br>This pointer must not be **NULL**. If **value** is set to **NULL**, the error code
 *     {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @param size [in] Indicates the size of the output array. It must equal the number of elements required by
 *     {@link OH_ArkUI_AnimationPropertyType}; otherwise, the error code {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR}
 *     is returned.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} if the value of the keyframe has not been set.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         <li>{@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} if the buffer size does not equal the required
 *             buffer size.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetValue(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t index, ArkUI_NumberValue *value, int32_t size);

/**
 * @brief Sets the animation curves for keyframes.
 *
 * @param animation [in] Indicates the keyframe animation handle.
 * @param value [in] Indicates the array of curve handles. This API does not take ownership of
 *     the curve handles; the caller must ensure all curves remain valid when using this handle.
 * @param size [in] Indicates the number of curves.
 *     The <b>springMotion</b>, <b>responsiveSpringMotion</b>, and <b>interpolatingSpring</b> curves are not
 *     supported because they do not have effective duration settings.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetCurves(
    OH_ArkUI_KeyframeAnimationHandle animation, const ArkUI_CurveHandle *value, int32_t size);

/**
 * @brief Sets the animation curve for a keyframe at the specified index.
 *
 * @param animation [in] Indicates the keyframe animation handle.
 * @param index [in] Indicates the keyframe index.
 * @param curve [in] Indicates the animation curve. This API does not take ownership of
 *     the curve handle; the caller must ensure the curve remains valid when using this handle.
 *     The <b>springMotion</b>, <b>responsiveSpringMotion</b>, and <b>interpolatingSpring</b> curves are not
 *     supported because they do not have effective duration settings.
 *     The actual effective animation curve is determined by priority: if the curve is set for the keyframe
 *     (via this API or {@link OH_ArkUI_NativeModule_KeyframeAnimation_SetCurves}), that value is used;
 *     otherwise, the curve set on the animation group via
 *     {@link OH_ArkUI_NativeModule_AnimationGroup_SetCurve} is used; if neither is set,
 *     {@link ARKUI_CURVE_LINEAR} is used.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetCurve(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t index, ArkUI_CurveHandle curve);

/**
 * @brief Obtains the curve of a keyframe at the specified index.
 *
 * This API returns only the curve explicitly set for the keyframe; the value inherited from the
 * animation group or the default is resolved at runtime and is not stored on this object. If the curve
 * has not been set for the keyframe, {@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} is returned. The actual
 * effective animation curve used at runtime is determined by priority: if set for the keyframe via
 * {@link OH_ArkUI_NativeModule_KeyframeAnimation_SetCurve} or
 * {@link OH_ArkUI_NativeModule_KeyframeAnimation_SetCurves}, that value is used; otherwise, the group's
 * curve via {@link OH_ArkUI_NativeModule_AnimationGroup_SetCurve} is used; if neither is set,
 * {@link ARKUI_CURVE_LINEAR} is used.
 * @param animation [in] Indicates the keyframe animation handle.
 * @param index [in] Indicates the keyframe index.
 * @param outBorrowedCurve [out] Receives a borrowed curve handle; the caller must not destroy it.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} if the curve has not been set.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetCurve(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t index, ArkUI_CurveHandle *outBorrowedCurve);

/**
 * @brief Sets the duration for a keyframe animation.
 *
 * The actual effective animation duration is determined by priority: if the duration is set via this API,
 * that value is used; otherwise, the duration set on the animation group via
 * {@link OH_ArkUI_NativeModule_AnimationGroup_SetDuration} is used; if neither is set, **1000** ms is used.
 * @param animation [in] Indicates the keyframe animation handle.
 * @param duration [in] Indicates the duration, in milliseconds. The value must be greater than 0.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetDuration(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t duration);

/**
 * @brief Obtains the duration of a keyframe animation.
 *
 * This API returns only the duration explicitly set on this animation; the value inherited from the
 * animation group or the default is resolved at runtime and is not stored on this object. If the duration
 * has not been set on this animation, {@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} is returned. The actual
 * effective animation duration used at runtime is determined by priority: if set via
 * {@link OH_ArkUI_NativeModule_KeyframeAnimation_SetDuration}, that value is used; otherwise, the group's
 * duration via {@link OH_ArkUI_NativeModule_AnimationGroup_SetDuration} is used; if neither is set,
 * **1000** ms is used.
 * @param animation [in] Indicates the keyframe animation handle.
 * @param duration [out] Indicates the pointer to receive the duration value, in milliseconds.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} if the duration has not been set.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetDuration(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t *duration);

/**
 * @brief Sets the delay for a keyframe animation.
 *
 * @param animation [in] Indicates the keyframe animation handle.
 * @param delay [in] Indicates the delay, in milliseconds. The default value is <b>0</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetDelay(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t delay);

/**
 * @brief Obtains the delay of a keyframe animation.
 *
 * @param animation [in] Indicates the keyframe animation handle.
 * @param delay [out] Indicates the pointer to receive the delay value, in milliseconds.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetDelay(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t *delay);

/**
 * @brief Sets the tempo for a keyframe animation.
 *
 * @param animation [in] Indicates the keyframe animation handle.
 * @param tempo [in] Indicates the animation tempo. Value range: (0, +∞). The default value is <b>1</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetTempo(
    OH_ArkUI_KeyframeAnimationHandle animation, float tempo);

/**
 * @brief Obtains the tempo of a keyframe animation.
 *
 * @param animation [in] Indicates the keyframe animation handle.
 * @param tempo [out] Indicates the pointer to receive the animation tempo.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetTempo(
    OH_ArkUI_KeyframeAnimationHandle animation, float *tempo);

/**
 * @brief Sets whether to auto-reverse a keyframe animation.
 *
 * When auto-reverse is enabled, the animation plays forward and then backward alternately
 * across iterations. The default value is <b>false</b>.
 *
 * @param animation [in] Indicates the keyframe animation handle.
 * @param autoReverse [in] Indicates whether to enable auto-reverse. The default value is <b>false</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetAutoReverse(
    OH_ArkUI_KeyframeAnimationHandle animation, bool autoReverse);

/**
 * @brief Obtains whether auto-reverse is enabled for a keyframe animation.
 *
 * @param animation [in] Indicates the keyframe animation handle.
 * @param autoReverse [out] Indicates the pointer to receive the value. <b>true</b> if auto-reverse is enabled;
 *     <b>false</b> otherwise.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetAutoReverse(
    OH_ArkUI_KeyframeAnimationHandle animation, bool *autoReverse);

/**
 * @brief Sets the number of iterations for a keyframe animation.
 *
 * @param animation [in] Indicates the keyframe animation handle.
 * @param iterations [in] Indicates the number of iterations. The value must be -1 or greater than
 *     or equal to 1; a value of <b>0</b> returns {@link ARKUI_ERROR_CODE_PARAM_INVALID}.
 *     The value <b>-1</b> indicates unlimited iterations. The default value is <b>1</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetIterations(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t iterations);

/**
 * @brief Obtains the number of iterations of a keyframe animation.
 *
 * @param animation [in] Indicates the keyframe animation handle.
 * @param iterations [out] Indicates the pointer to receive the number of iterations.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetIterations(
    OH_ArkUI_KeyframeAnimationHandle animation, int32_t *iterations);

/**
 * @brief Sets the target render node for a keyframe animation.
 *
 * The target node is the render node animated by this keyframe animation. If <b>NULL</b> (the default),
 * the animation inherits the group's default target set by
 * {@link OH_ArkUI_NativeModule_AnimationGroup_SetTargetNode}. A non-NULL target must belong to
 * the same UIContext that the group is registered on; the check is
 * performed when the group is registered by {@link OH_ArkUI_NativeModule_AddAnimationGroup}.
 *
 * @param animation [in] Indicates the keyframe animation handle.
 * @param targetNode [in] Indicates the render node to animate. <b>NULL</b> means inheriting the group's default
 *     target. The default value is <b>NULL</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_SetTargetNode(
    OH_ArkUI_KeyframeAnimationHandle animation, ArkUI_RenderNodeHandle targetNode);

/**
 * @brief Obtains the target render node of a keyframe animation.
 *
 * @param animation [in] Indicates the keyframe animation handle.
 * @param outBorrowedTargetNode [out] Receives a borrowed render-node handle;
 *     the caller must not destroy it. <b>NULL</b> means inheriting the group's default target.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_KeyframeAnimation_GetTargetNode(
    OH_ArkUI_KeyframeAnimationHandle animation, ArkUI_RenderNodeHandle *outBorrowedTargetNode);

/**
 * @brief Creates a path animation that moves the component along a geometric path.
 *
 * The path animation applies to the TRANSLATION property.
 *
 * @param path [in] Indicates the path string in SVG path syntax. The keywords <b>"start"</b> and <b>"end"</b>
 *     are not supported as position values. Returns <b>NULL</b> if <b>path</b> is <b>NULL</b>, is an empty
 *     string, or contains unsupported values.
 * @return Returns the handle to the path animation. Returns <b>NULL</b> on invalid input.
 *         The caller owns the returned handle and must release it with
 *         {@link OH_ArkUI_NativeModule_PathAnimation_Destroy}.
 * @release native_animate/OH_ArkUI_NativeModule_PathAnimation_Destroy {return}
 * @since 26.0.1
 */
OH_ArkUI_PathAnimationHandle OH_ArkUI_NativeModule_PathAnimation_Create(const char *path);

/**
 * @brief Destroys a path animation.
 *
 * @param animation [in] Indicates the path animation handle returned by
 *     {@link OH_ArkUI_NativeModule_PathAnimation_Create}. Passing <b>NULL</b> has no effect.
 *     After this function returns for a non-NULL handle, the handle is invalid, is not
 *     reference-counted, and must not be used or destroyed again.
 * @since 26.0.1
 */
void OH_ArkUI_NativeModule_PathAnimation_Destroy(OH_ArkUI_PathAnimationHandle animation);

/**
 * @brief Sets the duration for a path animation.
 *
 * The actual effective animation duration is determined by priority: if the duration is set via this API,
 * that value is used; otherwise, the duration set on the animation group via
 * {@link OH_ArkUI_NativeModule_AnimationGroup_SetDuration} is used; if neither is set, **1000** ms is used.
 * @param animation [in] Indicates the path animation handle.
 * @param duration [in] Indicates the duration, in milliseconds. The value must be greater than 0.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_SetDuration(
    OH_ArkUI_PathAnimationHandle animation, int32_t duration);

/**
 * @brief Obtains the duration of a path animation.
 *
 * This API returns only the duration explicitly set on this animation; the value inherited from the
 * animation group or the default is resolved at runtime and is not stored on this object. If the duration
 * has not been set on this animation, {@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} is returned. The actual
 * effective animation duration used at runtime is determined by priority: if set via
 * {@link OH_ArkUI_NativeModule_PathAnimation_SetDuration}, that value is used; otherwise, the group's
 * duration via {@link OH_ArkUI_NativeModule_AnimationGroup_SetDuration} is used; if neither is set,
 * **1000** ms is used.
 * @param animation [in] Indicates the path animation handle.
 * @param duration [out] Indicates the pointer to receive the duration value, in milliseconds.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} if the duration has not been set.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_GetDuration(
    OH_ArkUI_PathAnimationHandle animation, int32_t *duration);

/**
 * @brief Sets the delay for a path animation.
 *
 * @param animation [in] Indicates the path animation handle.
 * @param delay [in] Indicates the delay, in milliseconds. The default value is <b>0</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_SetDelay(OH_ArkUI_PathAnimationHandle animation, int32_t delay);

/**
 * @brief Obtains the delay of a path animation.
 *
 * @param animation [in] Indicates the path animation handle.
 * @param delay [out] Indicates the pointer to receive the delay value, in milliseconds.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_GetDelay(OH_ArkUI_PathAnimationHandle animation, int32_t *delay);

/**
 * @brief Sets the animation curve for a path animation.
 *
 * @param animation [in] Indicates the path animation handle.
 * @param curve [in] Indicates the animation curve that controls the rate of motion along the path.
 *     This API does not take ownership of the curve handle; the caller must ensure the curve remains
 *     valid when using this handle.
 *     The <b>springMotion</b>, <b>responsiveSpringMotion</b>, and <b>interpolatingSpring</b> curves are not
 *     supported because they do not have effective duration settings.
 *     The actual effective animation curve is determined by priority: if the curve is set via this API, that
 *     value is used; otherwise, the curve set on the animation group via
 *     {@link OH_ArkUI_NativeModule_AnimationGroup_SetCurve} is used; if neither is set,
 *     {@link ARKUI_CURVE_LINEAR} is used.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_SetCurve(
    OH_ArkUI_PathAnimationHandle animation, ArkUI_CurveHandle curve);

/**
 * @brief Obtains the animation curve of a path animation.
 *
 * This API returns only the curve explicitly set on this animation; the value inherited from the
 * animation group or the default is resolved at runtime and is not stored on this object. If the curve
 * has not been set on this animation, {@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} is returned. The actual
 * effective animation curve used at runtime is determined by priority: if set via
 * {@link OH_ArkUI_NativeModule_PathAnimation_SetCurve}, that value is used; otherwise, the group's
 * curve via {@link OH_ArkUI_NativeModule_AnimationGroup_SetCurve} is used; if neither is set,
 * {@link ARKUI_CURVE_LINEAR} is used.
 * @param animation [in] Indicates the path animation handle.
 * @param outBorrowedCurve [out] Receives a borrowed curve handle; the caller must not destroy it.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} if the curve has not been set.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_GetCurve(
    OH_ArkUI_PathAnimationHandle animation, ArkUI_CurveHandle *outBorrowedCurve);

/**
 * @brief Sets the tempo for a path animation.
 *
 * @param animation [in] Indicates the path animation handle.
 * @param tempo [in] Indicates the animation tempo. Value range: (0, +∞). The default value is <b>1</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_SetTempo(OH_ArkUI_PathAnimationHandle animation, float tempo);

/**
 * @brief Obtains the tempo of a path animation.
 *
 * @param animation [in] Indicates the path animation handle.
 * @param tempo [out] Indicates the pointer to receive the animation tempo.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_GetTempo(OH_ArkUI_PathAnimationHandle animation, float *tempo);

/**
 * @brief Sets whether to auto-reverse a path animation.
 *
 * When auto-reverse is enabled, the animation plays forward and then backward alternately
 * across iterations. The default value is <b>false</b>.
 *
 * @param animation [in] Indicates the path animation handle.
 * @param autoReverse [in] Indicates whether to enable auto-reverse. The default value is <b>false</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_SetAutoReverse(
    OH_ArkUI_PathAnimationHandle animation, bool autoReverse);

/**
 * @brief Obtains whether auto-reverse is enabled for a path animation.
 *
 * @param animation [in] Indicates the path animation handle.
 * @param autoReverse [out] Indicates the pointer to receive the value. <b>true</b> if auto-reverse is enabled;
 *     <b>false</b> otherwise. The default value is <b>false</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_GetAutoReverse(
    OH_ArkUI_PathAnimationHandle animation, bool *autoReverse);

/**
 * @brief Sets the number of iterations for a path animation.
 *
 * @param animation [in] Indicates the path animation handle.
 * @param iterations [in] Indicates the number of iterations. The value must be -1 or greater than
 *     or equal to 1; a value of <b>0</b> returns {@link ARKUI_ERROR_CODE_PARAM_INVALID}.
 *     The value <b>-1</b> indicates unlimited iterations. The default value is <b>1</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_SetIterations(
    OH_ArkUI_PathAnimationHandle animation, int32_t iterations);

/**
 * @brief Obtains the number of iterations of a path animation.
 *
 * @param animation [in] Indicates the path animation handle.
 * @param iterations [out] Indicates the pointer to receive the number of iterations.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_GetIterations(
    OH_ArkUI_PathAnimationHandle animation, int32_t *iterations);

/**
 * @brief Sets whether the component auto-rotates to align with the path tangent during a path animation.
 *
 * When auto-rotation is enabled, the component rotates so that its heading direction aligns with the
 * tangent of the path at the current position. The default value is <b>false</b>.
 *
 * @param animation [in] Indicates the path animation handle.
 * @param autoRotation [in] Indicates whether to enable auto-rotation. The default value is <b>false</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_SetAutoRotation(
    OH_ArkUI_PathAnimationHandle animation, bool autoRotation);

/**
 * @brief Obtains whether auto-rotation is enabled for a path animation.
 *
 * @param animation [in] Indicates the path animation handle.
 * @param autoRotation [out] Indicates the pointer to receive the value. <b>true</b> if auto-rotation is enabled;
 *     <b>false</b> otherwise. The default value is <b>false</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_GetAutoRotation(
    OH_ArkUI_PathAnimationHandle animation, bool *autoRotation);

/**
 * @brief Sets the target render node for a path animation.
 *
 * The target node is the render node animated by this path animation. If <b>NULL</b> (the default),
 * the animation inherits the group's default target set by
 * {@link OH_ArkUI_NativeModule_AnimationGroup_SetTargetNode}. A non-NULL target must belong to
 * the same UIContext that the group is registered on; the check is
 * performed when the group is registered by {@link OH_ArkUI_NativeModule_AddAnimationGroup}.
 *
 * @param animation [in] Indicates the path animation handle.
 * @param targetNode [in] Indicates the render node to animate. <b>NULL</b> means inheriting the group's default
 *     target. The default value is <b>NULL</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_SetTargetNode(
    OH_ArkUI_PathAnimationHandle animation, ArkUI_RenderNodeHandle targetNode);

/**
 * @brief Obtains the target render node of a path animation.
 *
 * @param animation [in] Indicates the path animation handle.
 * @param outBorrowedTargetNode [out] Receives a borrowed render-node handle;
 *     the caller must not destroy it. <b>NULL</b> means inheriting the group's default target.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PathAnimation_GetTargetNode(
    OH_ArkUI_PathAnimationHandle animation, ArkUI_RenderNodeHandle *outBorrowedTargetNode);

/**
 * @brief Creates an animation group.
 *
 * @return Returns the handle to the animation group. The caller owns the returned
 *         handle and must release it with {@link OH_ArkUI_NativeModule_AnimationGroup_Destroy}.
 * @release native_animate/OH_ArkUI_NativeModule_AnimationGroup_Destroy {return}
 * @since 26.0.1
 */
OH_ArkUI_AnimationGroupHandle OH_ArkUI_NativeModule_AnimationGroup_Create(void);

/**
 * @brief Destroys the frontend handle of an animation group.
 *
 * This releases the frontend handle only. The backend (runtime) objects of a group that has been registered
 * via {@link OH_ArkUI_NativeModule_AddAnimationGroup} are released separately — automatically when the
 * finish callback is invoked, or via {@link OH_ArkUI_NativeModule_RemoveAnimationGroup}.
 *
 * The child animations added to the group are not automatically destroyed. Call
 * OH_ArkUI_NativeModule_PropertyAnimation_Destroy, OH_ArkUI_NativeModule_KeyframeAnimation_Destroy or
 * OH_ArkUI_NativeModule_PathAnimation_Destroy separately.
 * @param group [in] Indicates the animation group handle returned by
 *     {@link OH_ArkUI_NativeModule_AnimationGroup_Create}. Passing <b>NULL</b> has no effect.
 *     After this function returns for a non-NULL handle, the handle is invalid, is not
 *     reference-counted, and must not be used or destroyed again.
 * @since 26.0.1
 */
void OH_ArkUI_NativeModule_AnimationGroup_Destroy(OH_ArkUI_AnimationGroupHandle group);

/**
 * @brief Sets the duration for an animation group.
 *
 * The group's duration serves as the default duration for child animations that do not set their own
 * duration via {@link OH_ArkUI_NativeModule_PropertyAnimation_SetDuration},
 * {@link OH_ArkUI_NativeModule_KeyframeAnimation_SetDuration}, or
 * {@link OH_ArkUI_NativeModule_PathAnimation_SetDuration}.
 * @param group [in] Indicates the animation group handle.
 * @param duration [in] Indicates the duration, in milliseconds. The value must be greater than 0.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_SetDuration(OH_ArkUI_AnimationGroupHandle group, int32_t duration);

/**
 * @brief Obtains the duration of an animation group.
 *
 * This API returns only the duration explicitly set on this animation group, and is not affected by
 * the duration of child animations. If the duration has not been set on this group,
 * {@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} is returned. At runtime, an unset group duration defaults
 * to **1000** ms.
 * @param group [in] Indicates the animation group handle.
 * @param duration [out] Indicates the pointer to receive the duration value, in milliseconds.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} if the duration has not been set.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_GetDuration(
    OH_ArkUI_AnimationGroupHandle group, int32_t *duration);

/**
 * @brief Sets the delay for an animation group.
 *
 * @param group [in] Indicates the animation group handle.
 * @param delay [in] Indicates the delay, in milliseconds. The default value is <b>0</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_SetDelay(OH_ArkUI_AnimationGroupHandle group, int32_t delay);

/**
 * @brief Obtains the delay of an animation group.
 *
 * @param group [in] Indicates the animation group handle.
 * @param delay [out] Indicates the pointer to receive the delay value, in milliseconds.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_GetDelay(OH_ArkUI_AnimationGroupHandle group, int32_t *delay);

/**
 * @brief Sets the animation curve for an animation group.
 *
 * The group's curve serves as the default curve for child animations that do not set their own curve
 * via {@link OH_ArkUI_NativeModule_PropertyAnimation_SetCurve},
 * {@link OH_ArkUI_NativeModule_KeyframeAnimation_SetCurve}, or
 * {@link OH_ArkUI_NativeModule_PathAnimation_SetCurve}.
 * The <b>springMotion</b>, <b>responsiveSpringMotion</b>, and <b>interpolatingSpring</b> curves are not
 * supported because they do not have effective duration settings.
 * @param group [in] Indicates the animation group handle.
 * @param curve [in] Indicates the animation curve. This API does not take ownership of
 *     the curve handle; the caller must ensure the curve remains valid when using this handle.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_SetCurve(
    OH_ArkUI_AnimationGroupHandle group, ArkUI_CurveHandle curve);

/**
 * @brief Obtains the animation curve of an animation group.
 *
 * This API returns only the curve explicitly set on this animation group, and is not affected by
 * the curve of child animations. If the curve has not been set on this group,
 * {@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} is returned. At runtime, an unset group curve defaults
 * to {@link ARKUI_CURVE_LINEAR}.
 * @param group [in] Indicates the animation group handle.
 * @param outBorrowedCurve [out] Receives a borrowed curve handle; the caller must not destroy it.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ATTRIBUTE_FOUND} if the curve has not been set.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_GetCurve(
    OH_ArkUI_AnimationGroupHandle group, ArkUI_CurveHandle *outBorrowedCurve);

/**
 * @brief Sets the tempo for an animation group.
 *
 * @param group [in] Indicates the animation group handle.
 * @param tempo [in] Indicates the animation tempo. Value range: (0, +∞). The default value is <b>1</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_SetTempo(OH_ArkUI_AnimationGroupHandle group, float tempo);

/**
 * @brief Obtains the tempo of an animation group.
 *
 * @param group [in] Indicates the animation group handle.
 * @param tempo [out] Indicates the pointer to receive the animation tempo.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_GetTempo(OH_ArkUI_AnimationGroupHandle group, float *tempo);

/**
 * @brief Sets whether to auto-reverse an animation group.
 *
 * When auto-reverse is enabled, the animation group plays forward and then backward alternately
 * across iterations. The default value is <b>false</b>.
 *
 * @param group [in] Indicates the animation group handle.
 * @param autoReverse [in] Indicates whether to enable auto-reverse. The default value is <b>false</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_SetAutoReverse(
    OH_ArkUI_AnimationGroupHandle group, bool autoReverse);

/**
 * @brief Obtains whether auto-reverse is enabled for an animation group.
 *
 * @param group [in] Indicates the animation group handle.
 * @param autoReverse [out] Indicates the pointer to receive the value. <b>true</b> if auto-reverse is enabled;
 *     <b>false</b> otherwise. The default value is <b>false</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_GetAutoReverse(
    OH_ArkUI_AnimationGroupHandle group, bool *autoReverse);

/**
 * @brief Sets the number of iterations for an animation group.
 *
 * @param group [in] Indicates the animation group handle.
 * @param iterations [in] Indicates the number of iterations. The value must be -1 or greater than
 *     or equal to 1; a value of <b>0</b> returns {@link ARKUI_ERROR_CODE_PARAM_INVALID}.
 *     The value <b>-1</b> indicates unlimited iterations. The default value is <b>1</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_SetIterations(
    OH_ArkUI_AnimationGroupHandle group, int32_t iterations);

/**
 * @brief Obtains the number of iterations of an animation group.
 *
 * @param group [in] Indicates the animation group handle.
 * @param iterations [out] Indicates the pointer to receive the number of iterations.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_GetIterations(
    OH_ArkUI_AnimationGroupHandle group, int32_t *iterations);

/**
 * @brief Sets the expected frame rate range for an animation group.
 *
 * @param group [in] Indicates the animation group handle.
 * @param frameRate [in] Indicates the expected frame rate range.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_SetExpectedFrameRateRange(
    OH_ArkUI_AnimationGroupHandle group, const ArkUI_ExpectedFrameRateRange *frameRate);

/**
 * @brief Obtains the expected frame rate range of an animation group.
 *
 * @param group [in] Indicates the animation group handle.
 * @param frameRate [out] Indicates the pointer used to receive the expected frame rate range. The values of
 *     the {@link ArkUI_ExpectedFrameRateRange} object are written into the memory pointed to by this pointer.
 *     <br>This pointer must not be **NULL**. If **frameRate** is set to **NULL**, the error code
 *     {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_GetExpectedFrameRateRange(
    OH_ArkUI_AnimationGroupHandle group, ArkUI_ExpectedFrameRateRange *frameRate);

/**
 * @brief Registers a callback to be invoked when the animation group playback is complete.
 *
 * An animation group has one finish callback. Registering another callback replaces the
 * previous callback and userData pair. Registering the same callback and userData pair
 * again succeeds without creating an additional registration.
 *
 * @param group [in] Indicates the animation group handle.
 * @param userData [in] Caller-owned data passed unchanged to the callback. It may be <b>NULL</b>,
 *     must remain valid until the callback returns, and is never freed by the library.
 * @param callback [in] Non-NULL finish callback invoked once and serially on the UI main thread.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_RegisterOnFinishCallback(
    OH_ArkUI_AnimationGroupHandle group, void *userData, void (*callback)(void *userData));

/**
 * @brief Sets the default target render node for an animation group.
 *
 * The default target is the render node animated by child animations that do not set their own target
 * via {@link OH_ArkUI_NativeModule_PropertyAnimation_SetTargetNode},
 * {@link OH_ArkUI_NativeModule_KeyframeAnimation_SetTargetNode}, or
 * {@link OH_ArkUI_NativeModule_PathAnimation_SetTargetNode}. Every child must resolve to a non-NULL
 * target (its own, or this group default) when the group is registered by
 * {@link OH_ArkUI_NativeModule_AddAnimationGroup}; any resolved target must belong to the same
 * UIContext that the group is registered on. The default value is <b>NULL</b>.
 *
 * @param group [in] Indicates the animation group handle.
 * @param targetNode [in] Indicates the default render node to animate. <b>NULL</b> means no group-level default.
 *     The default value is <b>NULL</b>.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_SetTargetNode(
    OH_ArkUI_AnimationGroupHandle group, ArkUI_RenderNodeHandle targetNode);

/**
 * @brief Obtains the default target render node of an animation group.
 *
 * @param group [in] Indicates the animation group handle.
 * @param outBorrowedTargetNode [out] Receives a borrowed render-node handle; the caller must not destroy it.
 *     <b>NULL</b> means no group-level default is set.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_GetTargetNode(
    OH_ArkUI_AnimationGroupHandle group, ArkUI_RenderNodeHandle *outBorrowedTargetNode);

/**
 * @brief Adds a property animation to an animation group.
 *
 * The target node of the animation is determined by
 * {@link OH_ArkUI_NativeModule_PropertyAnimation_SetTargetNode}; if not set, the animation inherits the
 * group's default target set by {@link OH_ArkUI_NativeModule_AnimationGroup_SetTargetNode}. Every child
 * must resolve to a non-NULL target when the group is registered.
 *
 * @param group [in] Indicates the animation group handle.
 * @param animation [in] Indicates the property animation to add. This API does not take
 *     ownership of the animation handle; the caller must ensure the animation remains valid when using this group.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         <li>{@link ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID} if the parameters of the
 *             {@link OH_ArkUI_PropertyAnimationHandle} are invalid.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_AddPropertyAnimation(
    OH_ArkUI_AnimationGroupHandle group, OH_ArkUI_PropertyAnimationHandle animation);

/**
 * @brief Adds a keyframe animation to an animation group.
 *
 * The target node of the animation is determined by
 * {@link OH_ArkUI_NativeModule_KeyframeAnimation_SetTargetNode}; if not set, the animation inherits the
 * group's default target set by {@link OH_ArkUI_NativeModule_AnimationGroup_SetTargetNode}. Every child
 * must resolve to a non-NULL target when the group is registered.
 *
 * @param group [in] Indicates the animation group handle.
 * @param animation [in] Indicates the keyframe animation to add. This API does not take
 *     ownership of the animation handle; the caller must ensure the animation remains valid when using this group.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         <li>{@link ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID} if the parameters of the
 *             {@link OH_ArkUI_KeyframeAnimationHandle} are invalid.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_AddKeyframeAnimation(
    OH_ArkUI_AnimationGroupHandle group, OH_ArkUI_KeyframeAnimationHandle animation);

/**
 * @brief Adds a path animation to an animation group.
 *
 * The target node of the animation is determined by
 * {@link OH_ArkUI_NativeModule_PathAnimation_SetTargetNode}; if not set, the animation inherits the
 * group's default target set by {@link OH_ArkUI_NativeModule_AnimationGroup_SetTargetNode}. Every child
 * must resolve to a non-NULL target when the group is registered.
 *
 * @param group [in] Indicates the animation group handle.
 * @param animation [in] Indicates the path animation to add. This API does not take
 *     ownership of the animation handle; the caller must ensure the animation remains valid when using this group.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         <li>{@link ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID} if the parameters of the
 *             {@link OH_ArkUI_PathAnimationHandle} are invalid.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AnimationGroup_AddPathAnimation(
    OH_ArkUI_AnimationGroupHandle group, OH_ArkUI_PathAnimationHandle animation);

/**
 * @brief Registers an animation group on a UIContext with a specified key and starts playback.
 *
 * The UIContext owns the group by <b>key</b>: once registered, the UIContext holds the group's backend
 * (runtime) objects, and the caller may destroy the frontend group handle (and child animation handles)
 * after registration since the backend runs independently by (UIContext, key). Keys are scoped per
 * UIContext (instance): the same key in different UIContexts does not collide. Within one UIContext, if a
 * group is already registered with the same key, the system removes the previous group first (releasing
 * its backend objects) and then registers the new group. The group is later identified and managed by the
 * same (UIContext, key) pair.
 *
 * Each child animation added via {@link OH_ArkUI_NativeModule_AnimationGroup_AddPropertyAnimation},
 * {@link OH_ArkUI_NativeModule_AnimationGroup_AddKeyframeAnimation}, or
 * {@link OH_ArkUI_NativeModule_AnimationGroup_AddPathAnimation} animates the target node set by its own
 * <b>SetTargetNode</b> API; if that target is not set (or is <b>NULL</b>), it inherits the group's default
 * target set by {@link OH_ArkUI_NativeModule_AnimationGroup_SetTargetNode}. At registration, every child
 * must resolve to a non-NULL target node (its own, or the group default), and every resolved target
 * node must belong to the same UIContext as <b>context</b>; otherwise, the error code
 * {@link ARKUI_ERROR_CODE_PARAM_INVALID} is returned.
 *
 * Playback control and lifecycle APIs ({@link OH_ArkUI_NativeModule_RemoveAnimationGroup},
 * {@link OH_ArkUI_NativeModule_GetAnimationGroupState}, {@link OH_ArkUI_NativeModule_HasAnimationGroup},
 * {@link OH_ArkUI_NativeModule_PauseAnimationGroup}, {@link OH_ArkUI_NativeModule_ResumeAnimationGroup},
 * {@link OH_ArkUI_NativeModule_FinishAnimationGroup} are all keyed by the (UIContext, key) pair.
 *
 * The finish callback (see {@link OH_ArkUI_NativeModule_AnimationGroup_RegisterOnFinishCallback})
 * is invoked exactly once after natural completion,
 * {@link OH_ArkUI_NativeModule_FinishAnimationGroup}, or destruction of a target node. If
 * {@link OH_ArkUI_NativeModule_AddAnimationGroup} returns an error, the finish callback is not invoked.
 * After the callback returns, the system automatically removes the group from the UIContext and releases the backend
 * (runtime) objects of the group and its child animations; the frontend handles (the group and its child
 * animations) must still be destroyed by the caller via {@link OH_ArkUI_NativeModule_AnimationGroup_Destroy},
 * {@link OH_ArkUI_NativeModule_PropertyAnimation_Destroy},
 * {@link OH_ArkUI_NativeModule_KeyframeAnimation_Destroy}, or
 * {@link OH_ArkUI_NativeModule_PathAnimation_Destroy}.
 *
 * @param context [in] Indicates the {@link ArkUI_ContextHandle} (UIContext) on which the animation group is
 *     registered and played.
 * @param group [in] Indicates the animation group handle.
 * @param key [in] Indicates the key used to identify the animation group on the UIContext.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs, or a resolved target node
 *             does not belong to the same UIContext as <b>context</b>.</li>
 *         <li>{@link ARKUI_ERROR_CODE_SUB_ANIMATION_INVALID} if a child animation has no resolvable target node.</li>
 *         <li>{@link ARKUI_ERROR_CODE_ANIMATION_GROUP_REENTRANT_CALL} if a re-entrant call is detected on
 *             the same thread.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_AddAnimationGroup(
    ArkUI_ContextHandle context, OH_ArkUI_AnimationGroupHandle group, const char *key);

/**
 * @brief Removes the animation group identified by the specified key from the UIContext.
 *
 * Stops the group (if still running) and releases the backend (runtime) objects of the group and its
 * child animations. The animated target nodes are restored to their state at the start of the animation.
 * The frontend handles (the group and its child animations) are not freed by this call
 * and must be destroyed by the caller via {@link OH_ArkUI_NativeModule_AnimationGroup_Destroy},
 * {@link OH_ArkUI_NativeModule_PropertyAnimation_Destroy},
 * {@link OH_ArkUI_NativeModule_KeyframeAnimation_Destroy}, or
 * {@link OH_ArkUI_NativeModule_PathAnimation_Destroy}. Use this only for a group that has not stopped on its
 * own (for example, a paused group); once the finish callback is invoked, the group is removed
 * automatically.
 *
 * @param context [in] Indicates the UIContext on which the animation group was registered.
 * @param key [in] Indicates the key of the animation group to remove.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         <li>{@link ARKUI_ERROR_CODE_ANIMATION_GROUP_NOT_FOUND} if the animation group identified by
 *             <b>key</b> is not found on the UIContext.</li>
 *         <li>{@link ARKUI_ERROR_CODE_ANIMATION_GROUP_REENTRANT_CALL} if a re-entrant call is detected on
 *             the same thread.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_RemoveAnimationGroup(ArkUI_ContextHandle context, const char *key);

/**
 * @brief Obtains the playback state of an animation group identified by the specified key on the UIContext.
 *
 * @param context [in] Indicates the UIContext.
 * @param key [in] Indicates the key of the animation group.
 * @param state [out] Indicates the pointer to receive the state value.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         <li>{@link ARKUI_ERROR_CODE_ANIMATION_GROUP_NOT_FOUND} if the animation group identified by
 *             <b>key</b> is not found on the UIContext.</li>
 *         <li>{@link ARKUI_ERROR_CODE_ANIMATION_GROUP_REENTRANT_CALL} if a re-entrant call is detected on
 *             the same thread.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_GetAnimationGroupState(
    ArkUI_ContextHandle context, const char *key, OH_ArkUI_AnimationGroupState *state);

/**
 * @brief Checks whether an animation group with the specified key exists on the UIContext.
 *
 * @param context [in] Indicates the UIContext.
 * @param key [in] Indicates the key of the animation group.
 * @param exists [in] Indicates the pointer to receive the value. <b>true</b> if the animation group exists;
 *     <b>false</b> otherwise.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         <li>{@link ARKUI_ERROR_CODE_ANIMATION_GROUP_REENTRANT_CALL} if a re-entrant call is detected on
 *             the same thread.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_HasAnimationGroup(ArkUI_ContextHandle context, const char *key, bool *exists);

/**
 * @brief Pauses the animation group identified by the specified key on the UIContext.
 *
 * The animation group must be in the RUNNING state; otherwise,
 * {@link ARKUI_ERROR_CODE_ANIMATION_GROUP_INVALID_STATE} is returned.
 *
 * @param context [in] Indicates the UIContext.
 * @param key [in] Indicates the key of the animation group.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         <li>{@link ARKUI_ERROR_CODE_ANIMATION_GROUP_NOT_FOUND} if the animation group identified by
 *             <b>key</b> is not found on the UIContext.</li>
 *         <li>{@link ARKUI_ERROR_CODE_ANIMATION_GROUP_INVALID_STATE} if the animation group is not in the
 *             RUNNING state.</li>
 *         <li>{@link ARKUI_ERROR_CODE_ANIMATION_GROUP_REENTRANT_CALL} if a re-entrant call is detected on
 *             the same thread.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_PauseAnimationGroup(ArkUI_ContextHandle context, const char *key);

/**
 * @brief Resumes the animation group identified by the specified key on the UIContext.
 *
 * The animation group must be in the PAUSED state; otherwise,
 * {@link ARKUI_ERROR_CODE_ANIMATION_GROUP_INVALID_STATE} is returned.
 *
 * @param context [in] Indicates the UIContext.
 * @param key [in] Indicates the key of the animation group.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.</li>
 *         <li>{@link ARKUI_ERROR_CODE_ANIMATION_GROUP_NOT_FOUND} if the animation group identified by
 *             <b>key</b> is not found on the UIContext.</li>
 *         <li>{@link ARKUI_ERROR_CODE_ANIMATION_GROUP_INVALID_STATE} if the animation group is not in the
 *             PAUSED state.</li>
 *         <li>{@link ARKUI_ERROR_CODE_ANIMATION_GROUP_REENTRANT_CALL} if a re-entrant call is detected on
 *             the same thread.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ResumeAnimationGroup(ArkUI_ContextHandle context, const char *key);

/**
 * @brief Finishes the animation group identified by the specified key on the UIContext.
 *
 * The animation group is finished according to the specified finish mode:
 * jump to the end state, jump to the start state, or stay at the current value. The animation group must
 * be in the RUNNING or PAUSED state; otherwise,
 * {@link ARKUI_ERROR_CODE_ANIMATION_GROUP_INVALID_STATE} is returned.
 *
 * @param context [in] Indicates the UIContext.
 * @param key [in] Indicates the key of the animation group.
 * @param mode [in] Indicates the finish mode. The value is an enum of {@link OH_ArkUI_AnimationFinishMode}.
 * @return <ul>
 *         <li>{@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.</li>
 *         <li>{@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs,
 *             for example when <b>context</b> or <b>key</b> is invalid, or <b>mode</b> is not a valid
 *             value of {@link OH_ArkUI_AnimationFinishMode}.</li>
 *         <li>{@link ARKUI_ERROR_CODE_ANIMATION_GROUP_NOT_FOUND} if the animation group identified by
 *             <b>key</b> is not found on the UIContext.</li>
 *         <li>{@link ARKUI_ERROR_CODE_ANIMATION_GROUP_INVALID_STATE} if the animation group is not in the
 *             RUNNING or PAUSED state.</li>
 *         <li>{@link ARKUI_ERROR_CODE_ANIMATION_GROUP_REENTRANT_CALL} if a re-entrant call is detected on
 *             the same thread.</li>
 *         </ul>
 * @since 26.0.1
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_FinishAnimationGroup(
    ArkUI_ContextHandle context, const char *key, OH_ArkUI_AnimationFinishMode mode);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_ANIMATE_H
/** @} */
