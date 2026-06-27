/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * @brief Provides ImageAnimator type definitions of ArkUI on the native side.
 *
 * @since 12
 */

/**
 * @file image_animator.h
 *
 * @brief Defines the common types and APIs for the ImageAnimator component.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_ANIMATOR_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_ANIMATOR_H

#include <stdint.h>

#include "../drawable_descriptor.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the playback status for the image animator.
 *
 * @since 12
*/
typedef enum {
    /**
     * The animation is in the initial state.
     *
     * @since 12
     */
    ARKUI_ANIMATION_STATUS_INITIAL = 0,
    /**
     * The animation is being played.
     *
     * @since 12
     */
    ARKUI_ANIMATION_STATUS_RUNNING = 1,
    /**
     * The animation is paused.
     *
     * @since 12
     */
    ARKUI_ANIMATION_STATUS_PAUSED = 2,
    /**
     * The animation is stopped.
     *
     * @since 12
     */
    ARKUI_ANIMATION_STATUS_STOPPED = 3,
} ArkUI_AnimationStatus;

/**
 * @brief Defines the image frame.
 *
 * @since 12
*/
typedef struct ArkUI_ImageAnimatorFrameInfo ArkUI_ImageAnimatorFrameInfo;

/**
 * @brief Create a image frame from the image path.
 * @param src Indicates the image path.
 * @return Returns the pointer to the image frame object.
 * If a null pointer is returned, the object fails to be created. The possible cause is that
 * the src parameter is abnormal, for example, the pointer is null.
 * @since 12
*/
ArkUI_ImageAnimatorFrameInfo* OH_ArkUI_ImageAnimatorFrameInfo_CreateFromString(char* src);

/**
 * @brief Create a image frame from the drawable descriptor.
 *
 * @param drawable Indicates the pointer to the drawable descriptor.
 * @return Returns the pointer to the image frame object. If a null pointer is returned, the object fails to be created.
 *     The possible cause is that the drawable parameter is abnormal, for example, the pointer is null.
 * @since 12
*/
ArkUI_ImageAnimatorFrameInfo* OH_ArkUI_ImageAnimatorFrameInfo_CreateFromDrawableDescriptor(
    ArkUI_DrawableDescriptor* drawable);

/**
 * @brief Destroy the pointer to the image frame.
 *
 * @param imageInfo Indicates the pointer to the image frame.
 * @since 12
*/
void OH_ArkUI_ImageAnimatorFrameInfo_Dispose(ArkUI_ImageAnimatorFrameInfo* imageInfo);

/**
 * @brief Set the width of the image frame.
 *
 * @param imageInfo Indicates the pointer to the image frame.
 * @param width Indicates the width of the image frame, and the unit is PX.
 * @since 12
*/
void OH_ArkUI_ImageAnimatorFrameInfo_SetWidth(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t width);

/**
 * @brief Get the width of the image frame.
 *
 * @param imageInfo Indicates the pointer to the image frame.
 * @return Return the width of the image frame, and the unit is PX. Return 0 when the imageInfo is null.
 * @since 12
*/
int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetWidth(ArkUI_ImageAnimatorFrameInfo* imageInfo);

/**
 * @brief Set the height of the image frame.
 *
 * @param imageInfo Indicates the pointer to the image frame.
 * @param height Indicates the height of the image frame, and the unit is PX.
 * @since 12
*/
void OH_ArkUI_ImageAnimatorFrameInfo_SetHeight(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t height);

/**
 * @brief Get the height of the image frame.
 *
 * @param imageInfo Indicates the pointer to the image frame.
 * @return Return the height of the image frame, and the unit is PX. Return 0 when the imageInfo is null.
 * @since 12
*/
int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetHeight(ArkUI_ImageAnimatorFrameInfo* imageInfo);

/**
 * @brief Set the vertical coordinate of the image relative to the upper left corner of the widget.
 *
 * @param imageInfo Indicates the pointer to the image frame.
 * @param top Indicates the vertical coordinate of the image relative to the upper left corner of the widget,
 * and the unit is PX.
 * @since 12
*/
void OH_ArkUI_ImageAnimatorFrameInfo_SetTop(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t top);

/**
 * @brief Get the vertical coordinate of the image relative to the upper left corner of the widget.
 *
 * @param imageInfo Indicates the pointer to the image frame.
 * @return Returns the vertical coordinate of the image relative to the upper left corner of the widget,
 * and the unit is PX. Return 0 when the imageInfo is null.
 * @since 12
*/
int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetTop(ArkUI_ImageAnimatorFrameInfo* imageInfo);

/**
 * @brief Set the horizontal coordinate of the image relative to the upper left corner of the widget.
 *
 * @param imageInfo Indicates the pointer to the image frame.
 * @param left Indicates the horizontal coordinate of the image relative to the upper left corner of the widget,
 * and the unit is PX.
 * @since 12
*/
void OH_ArkUI_ImageAnimatorFrameInfo_SetLeft(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t left);

/**
 * @brief Get the horizontal coordinate of the image relative to the upper left corner of the widget.
 *
 * @param imageInfo Indicates the pointer to the image frame.
 * @return Returns the horizontal coordinate of the image relative to the upper left corner of the widget,
 * and the unit is PX. Return 0 when the imageInfo is null.
 * @since 12
*/
int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetLeft(ArkUI_ImageAnimatorFrameInfo* imageInfo);

/**
 * @brief Set the playback duration of the image frame.
 *
 * @param imageInfo Indicates the pointer to the image frame.
 * @param duration Indicates the playback duration of each image frame, and the unit is milliseconds.
 * @since 12
*/
void OH_ArkUI_ImageAnimatorFrameInfo_SetDuration(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t duration);

/**
 * @brief Get the playback duration of the image frame.
 *
 * @param imageInfo Indicates the pointer to the image frame.
 * @return Returns the playback duration of the image frame, and the unit is milliseconds.
 * Return 0 when the imageInfo is null.
 * @since 12
*/
int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetDuration(ArkUI_ImageAnimatorFrameInfo* imageInfo);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_ANIMATOR_H
/** @} */
