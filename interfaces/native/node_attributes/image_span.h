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
 * @brief Defines a set of ImageSpan enum and interface.
 *
 * @since 12
 */

/**
 * @file image_span.h
 *
 * @brief Defines a set of ImageSpan enum and interface.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_SPAN_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_SPAN_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the alignment mode of the image with the text.
 *
 * @since 12
 */
typedef enum {
    /** The image is bottom aligned with the text baseline. */
    ARKUI_IMAGE_SPAN_ALIGNMENT_BASELINE = 0,
    /** The image is bottom aligned with the text. */
    ARKUI_IMAGE_SPAN_ALIGNMENT_BOTTOM,
    /** The image is centered aligned with the text. */
    ARKUI_IMAGE_SPAN_ALIGNMENT_CENTER,
    /** The image is top aligned with the text. */
    ARKUI_IMAGE_SPAN_ALIGNMENT_TOP,
    /**
     * The image alignment mode follows the text component's alignment mode.
     *
     * @since 20
     */
    ARKUI_IMAGE_SPAN_ALIGNMENT_FOLLOW_PARAGRAPH,
} ArkUI_ImageSpanAlignment;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_IMAGE_SPAN_H
/** @} */
