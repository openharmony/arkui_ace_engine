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
 * @brief ArkUI Slider Node type definitions on the native side.
 *
 * @since 12
 */

/**
 * @file slider.h
 *
 * @brief Provides slider node type definitions for <b>NativeNode</b> APIs.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_SLIDER_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_SLIDER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the styles of the slider in the block direction.
 *
 * @since 12
 */
typedef enum {
    /**
     * Round slider.
     * @since 12
     */
    ARKUI_SLIDER_BLOCK_STYLE_DEFAULT = 0,
    /**
     * Slider with an image background.
     * @since 12
     */
    ARKUI_SLIDER_BLOCK_STYLE_IMAGE,
    /**
     * Slider in a custom shape.
     * @since 12
     */
    ARKUI_SLIDER_BLOCK_STYLE_SHAPE,
} ArkUI_SliderBlockStyle;

/**
 * @brief Enumerates the scroll directions of the slider.
 *
 * @since 12
 */
typedef enum {
    /**
     * Vertical direction.
     * @since 12
     */
    ARKUI_SLIDER_DIRECTION_VERTICAL = 0,
    /**
     * Horizontal direction.
     * @since 12
     */
    ARKUI_SLIDER_DIRECTION_HORIZONTAL,
} ArkUI_SliderDirection;

/**
 * @brief Enumerates the slider styles.
 *
 * @since 12
 */
typedef enum {
    /**
     * The slider is on the slider rail.
     * @since 12
     */
    ARKUI_SLIDER_STYLE_OUT_SET = 0,
    /**
     * The slider is in the slider rail.
     * @since 12
     */
    ARKUI_SLIDER_STYLE_IN_SET,
    /**
     * There is no thumb.
     * @since 12
     */
    ARKUI_SLIDER_STYLE_NONE,
} ArkUI_SliderStyle;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_SLIDER_H
/** @} */
