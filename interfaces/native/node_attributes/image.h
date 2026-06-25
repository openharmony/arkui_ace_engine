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
 * @brief Provides Image type definitions of ArkUI on the native side.
 *
 * @since 12
 */

/**
 * @file image.h
 *
 * @brief Defines the common types for the Image component.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the image repeat patterns.
 *
 * @since 12
 */
typedef enum {
    /**
     * The image is not repeatedly drawn.
     *
     * @since 12
     */
    ARKUI_IMAGE_REPEAT_NONE = 0,
    /**
     * The image is repeatedly drawn only along the x-axis.
     *
     * @since 12
     */
    ARKUI_IMAGE_REPEAT_X = 1,
    /**
     * The image is repeatedly drawn only along the y-axis.
     *
     * @since 12
     */
    ARKUI_IMAGE_REPEAT_Y = 2,
    /**
     * The image is repeatedly drawn along both axes.
     *
     * @since 12
     */
    ARKUI_IMAGE_REPEAT_XY = 3,
} ArkUI_ImageRepeat;

/**
 * @brief Defines the image size.
 *
 * @since 12
 */
typedef enum {
    /**
     * The original image aspect ratio is retained.
     *
     * @since 12
     */
    ARKUI_IMAGE_SIZE_AUTO = 0,
    /**
     * The image is scaled with its aspect ratio retained for both sides to be greater than or equal
     *     to the display boundaries.
     *
     * @since 12
     */
    ARKUI_IMAGE_SIZE_COVER = 1,
    /**
     * The image is scaled with its aspect ratio retained for the content to be completely displayed
     *     within the display boundaries.
     *
     * @since 12
     */
    ARKUI_IMAGE_SIZE_CONTAIN = 2,
} ArkUI_ImageSize;

/**
 * @brief Defines how the image is resized to fit its container.
 *
 * @since 12
 */
typedef enum {
    /**
     * The image is scaled with its aspect ratio retained for the content to be completely displayed
     *     within the display boundaries.
     *
     * @since 12
     */
    ARKUI_OBJECT_FIT_CONTAIN = 0,
    /**
     * The image is scaled with its aspect ratio retained for both sides to be greater than or
     *     equal to the display boundaries.
     *
     * @since 12
     */
    ARKUI_OBJECT_FIT_COVER = 1,
    /**
     * The image is scaled automatically to fit the display area.
     *
     * @since 12
     */
    ARKUI_OBJECT_FIT_AUTO = 2,
    /**
     * The image is scaled to fill the display area, and its aspect ratio is not retained.
     *
     * @since 12
     */
    ARKUI_OBJECT_FIT_FILL = 3,
    /**
     * The image content is displayed with its aspect ratio retained. The size is smaller than or
     * equal to the original size.
     *
     * @since 12
     */
    ARKUI_OBJECT_FIT_SCALE_DOWN = 4,
    /**
     * The original size is retained.
     *
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE = 5,
    /**
     * Not resized, the image is aligned with the start edge of the top of the container.
     *
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_TOP_START = 6,
    /**
     * Not resized, the image is horizontally centered at the top of the container.
     *
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_TOP = 7,
    /**
     * Not resized, the image is aligned with the end edge at the top of the container.
     *
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_TOP_END = 8,
    /**
     * Not resized, the image is vertically centered on the start edge of the container.
     *
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_START = 9,
    /**
     * Not resized, the image is horizontally and vertically centered in the container.
     *
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_CENTER = 10,
    /**
     * Not resized, the image is vertically centered on the end edge of the container.
     *
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_END = 11,
    /**
     * Not resized, the image is aligned with the start edge at the bottom of the container.
     *
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_BOTTOM_START = 12,
    /**
     * Not resized, the image is horizontally centered at the bottom of the container.
     *
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_BOTTOM = 13,
    /**
     * Not resized, the image is aligned with the end edge at the bottom of the container.
     *
     * @since 12
     */
    ARKUI_OBJECT_FIT_NONE_AND_ALIGN_BOTTOM_END = 14,
    /**
     * Not resized, and is used in conjunction with NODE_IMAGE_IMAGE_MATRIX.
     *
     * @since 21
     */
    ARKUI_OBJECT_FIT_NONE_MATRIX = 15,
} ArkUI_ObjectFit;

/**
 * @brief Enumerates the image interpolation effect.
 *
 * @since 12
 */
typedef enum {
    /**
     * No image interpolation.
     *
     * @since 12
     */
    ARKUI_IMAGE_INTERPOLATION_NONE = 0,
    /**
     * Low quality interpolation.
     *
     * @since 12
     */
    ARKUI_IMAGE_INTERPOLATION_LOW = 1,
    /**
     * Medium quality interpolation.
     *
     * @since 12
     */
    ARKUI_IMAGE_INTERPOLATION_MEDIUM = 2,
    /**
     * High quality interpolation. This mode produces scaled images of the highest possible quality.
     *
     * @since 12
     */
    ARKUI_IMAGE_INTERPOLATION_HIGH = 3,
} ArkUI_ImageInterpolation;

/**
 * @brief Enumerates the image dynamic range mode.
 *
 * @since 21
 */
typedef enum {
    /**
     * high dynamic range mode.
     *
     * @since 21
     */
    ARKUI_DYNAMIC_RANGE_MODE_HIGH = 0,
    /**
     * constraint dynamic range mode.
     *
     * @since 21
     */
    ARKUI_DYNAMIC_RANGE_MODE_CONSTRAINT = 1,
    /**
     * standard dynamic range mode.
     *
     * @since 21
     */
    ARKUI_DYNAMIC_RANGE_MODE_STANDARD = 2,
} ArkUI_DynamicRangeMode;

/**
 * @brief Enumerates the image rotate orientation.
 *
 * @since 21
 */
typedef enum {
    /**
     * Use EXIF metadata for display orientation, with support for rotation and mirroring.
     *
     * @since 21
     */
    ARKUI_ORIENTATION_AUTO = 0,
    /**
     * Display original pixel data without transformation.
     *
     * @since 21
     */
    ARKUI_ORIENTATION_UP = 1,
    /**
     * Display the image after rotating it 90 degrees clockwise.
     *
     * @since 21
     */
    ARKUI_ORIENTATION_RIGHT = 2,
    /**
     * Display the image after rotating it 180 degrees clockwise.
     *
     * @since 21
     */
    ARKUI_ORIENTATION_DOWN = 3,
    /**
     * Display the image after rotating it 270 degrees clockwise.
     *
     * @since 21
     */
    ARKUI_ORIENTATION_LEFT = 4,
    /**
     * Display the image after flipping it horizontally.
     *
     * @since 21
     */
    ARKUI_ORIENTATION_UP_MIRRORED = 5,
    /**
     * Display the image after flipping it horizontally and then rotating it 90 degrees clockwise.
     *
     * @since 21
     */
    ARKUI_ORIENTATION_RIGHT_MIRRORED = 6,
    /**
     * Display the image after flipping it vertically.
     *
     * @since 21
     */
    ARKUI_ORIENTATION_DOWN_MIRRORED = 7,
    /**
     * Display the image after flipping it horizontally and then rotating it 270 degrees clockwise.
     *
     * @since 21
     */
    ARKUI_ORIENTATION_LEFT_MIRRORED = 8,
} ArkUI_ImageRotateOrientation;

/**
 * @brief Enumerates the image rendering modes.
 *
 * @since 12
 */
typedef enum {
    /**
     * Render image pixels as they are in the original source image.
     *
     * @since 12
     */
    ARKUI_IMAGE_RENDER_MODE_ORIGINAL = 0,
    /**
     * Render image pixels to create a monochrome template image.
     *
     * @since 12
     */
    ARKUI_IMAGE_RENDER_MODE_TEMPLATE = 1,
} ArkUI_ImageRenderMode;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_H
/** @} */
