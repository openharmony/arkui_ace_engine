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

/**
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Provides UI capabilities of ArkUI on the native side, such as UI component creation and destruction,
 * tree node operations, attribute setting, and event listening.
 *
 * @since 12
 */

/**
 * @file drawable_descriptor.h
 *
 * @brief Defines theNativeDrawableDescriptor for the native module.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef ARKUI_NATIVE_DRAWABLE_DESCRIPTOR_H
#define ARKUI_NATIVE_DRAWABLE_DESCRIPTOR_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the drawable descriptor.
 *
 * @since 12
 */
typedef struct ArkUI_DrawableDescriptor ArkUI_DrawableDescriptor;

/**
 * @brief Introduces the native pixel map information defined by Image Kit.
 *
 * @since 12
 */
struct OH_PixelmapNative;

/**
 * @brief Defines the pointer to OH_PixelmapNative.
 *
 * @since 12
 */
typedef struct OH_PixelmapNative* OH_PixelmapNativeHandle;

/**
 * @brief Defines the ArkUI native component object.
 *
 * @since 22
 */
struct ArkUI_Node;

/**
 * @brief Defines the pointer to the ArkUI native component object.
 *
 * @since 22
 */
typedef struct ArkUI_Node* ArkUI_NodeHandle;

/**
 * @brief Defines the animation controller of arkui drawable descriptor.
 *
 * @since 22
 */
typedef struct ArkUI_DrawableDescriptor_AnimationController ArkUI_DrawableDescriptor_AnimationController;

/**
 * @brief Defines the animation status of the drawable descriptor.
 *
 * @since 22
 */
typedef enum {
    /** animation is initial. */
    DRAWABLE_DESCRIPTOR_ANIMATION_STATUS_INITIAL = 0,
    /** animation is playing. */
    DRAWABLE_DESCRIPTOR_ANIMATION_STATUS_RUNNING = 1,
    /** animation is paused. */
    DRAWABLE_DESCRIPTOR_ANIMATION_STATUS_PAUSED = 2,
    /** animation is stopped. */
    DRAWABLE_DESCRIPTOR_ANIMATION_STATUS_STOPPED = 3,
} DrawableDescriptor_AnimationStatus;

/**
 * @brief Creates a DrawableDescriptor from a Pixelmap.
 *
 * @param pixelMap Indicates the pointer to a Pixelmap
 * @return Returns the pointer to the drawableDescriptor.
 * @since 12
*/
ArkUI_DrawableDescriptor* OH_ArkUI_DrawableDescriptor_CreateFromPixelMap(OH_PixelmapNativeHandle pixelMap);

/**
 * @brief Creates a DrawableDescriptor from a Pixelmap array.
 *
 * @param array Indicates the pointer to a Pixelmap array.
 * @param size Indicates the size of the Pixelmap array.
 * @return Returns the pointer to the drawableDescriptor.
 * @since 12
*/
ArkUI_DrawableDescriptor* OH_ArkUI_DrawableDescriptor_CreateFromAnimatedPixelMap(
    OH_PixelmapNativeHandle* array, int32_t size);

/**
 * @brief Destroys the pointer to the drawableDescriptor.
 *
 * @param drawableDescriptor Indicates the pointer to the drawableDescriptor.
 * @since 12
*/
void OH_ArkUI_DrawableDescriptor_Dispose(ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief Obtains the Pixelmap object.
 *
 * @param drawableDescriptor Indicates the pointer to the drawableDescriptor.
 * @return Returns the pointer to the PixelMap.
 * @since 12
*/
OH_PixelmapNativeHandle OH_ArkUI_DrawableDescriptor_GetStaticPixelMap(ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief Obtains the Pixelmap array used to play the animation.
 *
 * @param drawableDescriptor Indicates the pointer to the drawableDescriptor.
 * @return Returns the pointer to the PixelMap array.
 * @since 12
*/
OH_PixelmapNativeHandle* OH_ArkUI_DrawableDescriptor_GetAnimatedPixelMapArray(
    ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief Obtains the size of the Pixelmap array used to play the animation.
 *
 * @param drawableDescriptor Indicates the pointer to the drawableDescriptor.
 * @return Returns the size of the Pixelmap array.
 * @since 12
*/
int32_t OH_ArkUI_DrawableDescriptor_GetAnimatedPixelMapArraySize(ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief Sets the total playback duration.
 *
 * @param drawableDescriptor Indicates the pointer to the drawableDescriptor.
 * @param duration Indicates the total playback duration. The unit is millisecond.
 * @since 12
*/
void OH_ArkUI_DrawableDescriptor_SetAnimationDuration(ArkUI_DrawableDescriptor* drawableDescriptor, int32_t duration);

/**
 * @brief Obtains the total playback duration.
 *
 * @param drawableDescriptor Indicates the pointer to the drawableDescriptor.
 * @return Return the total playback duration. The unit is millisecond.
 * @since 12
*/
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationDuration(ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief Sets the number of playback times.
 *
 * @param drawableDescriptor Indicates the pointer to the drawableDescriptor.
 * @param iterations Indicates the number of playback times.
 * @since 12
*/
void OH_ArkUI_DrawableDescriptor_SetAnimationIteration(
    ArkUI_DrawableDescriptor* drawableDescriptor, int32_t iteration);

/**
 * @brief Obtains the number of playback times.
 *
 * @param drawableDescriptor Indicates the pointer to the drawableDescriptor.
 * @return Returns the number of playback times.
 * @since 12
*/
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationIteration(ArkUI_DrawableDescriptor* drawableDescriptor);

/**
 * @brief Sets the frame duration array.
 *
 * @param drawableDescriptor Indicates the pointer to the drawableDescriptor.
 * @param durations Indicates the pointer to the frame duration array.
 * @param size Indicates the size of the frame duration array.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful;
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_SetAnimationFrameDurations(
    ArkUI_DrawableDescriptor* drawableDescriptor, uint32_t* durations, size_t size);

/**
 * @brief Obtains the frame duration array.
 *
 * @param drawableDescriptor Indicates the pointer to the drawableDescriptor.
 * @param durations Indicates the pointer to the frame duration array.
 * @param size Indicates the size of the frame duration array.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful;
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationFrameDurations(
    ArkUI_DrawableDescriptor* drawableDescriptor, uint32_t* durations, size_t* size);

/**
 * @brief Sets whether to play the animation automatically.
 *
 * @param drawableDescriptor Indicates the pointer to the drawableDescriptor.
 * @param autoPlay Indicates whether to play the animation automatically.
 *                 default value is 1, which means to play the animation automatically.
 *                 value 0 means not to play the animation automatically.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful;
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_SetAnimationAutoPlay(
    ArkUI_DrawableDescriptor* drawableDescriptor, uint32_t autoPlay);

/**
 * @brief Obtains whether to play the animation automatically.
 *
 * @param drawableDescriptor Indicates the pointer to the drawableDescriptor.
 * @param autoPlay Indicates whether to play the animation automatically.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful;
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationAutoPlay(
    ArkUI_DrawableDescriptor* drawableDescriptor, uint32_t* autoPlay);

/**
 * @brief Obtains the animation controller.
 *
 * @param drawableDescriptor Indicates the pointer to the drawableDescriptor.
 * @param node Indicates the node handle.
 * @param controller Indicates the pointer to the animation controller.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful;
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_CreateAnimationController(ArkUI_DrawableDescriptor *drawableDescriptor,
    ArkUI_NodeHandle node, ArkUI_DrawableDescriptor_AnimationController** controller);

/**
 * @brief Releases the animation controller.
 *
 * @param controller Indicates the pointer to the animation controller.
 * @since 22
 */
void OH_ArkUI_DrawableDescriptor_DisposeAnimationController(
    ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief Starts the animation from first frame.
 *
 * @param controller Indicates the pointer to the animation controller.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful;
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_StartAnimation(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief Stops the animation and back to first frame.
 *
 * @param controller Indicates the pointer to the animation controller.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful;
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_StopAnimation(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief Resumes the animation at the current frame.
 *
 * @param controller Indicates the pointer to the animation controller.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful;
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_ResumeAnimation(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief Pauses the animation at the current frame.
 *
 * @param controller Indicates the pointer to the animation controller.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful;
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_PauseAnimation(ArkUI_DrawableDescriptor_AnimationController* controller);

/**
 * @brief Obtains the animation playback status.
 *
 * @param controller Indicates the pointer to the animation controller.
 * @param status Indicates the pointer to the animation playback status.
 * @return Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful;
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 * @since 22
 */
int32_t OH_ArkUI_DrawableDescriptor_GetAnimationStatus(
    ArkUI_DrawableDescriptor_AnimationController* controller, DrawableDescriptor_AnimationStatus* status);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_DRAWABLE_DESCRIPTOR_H
/** @} */
