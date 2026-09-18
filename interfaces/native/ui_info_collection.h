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
 * @brief Provides page text query capabilities for ArkUI on the native side.
 *
 * @since 26.2.0
 */

/**
 * @file ui_info_collection.h
 * @brief Provides synchronous access to ArkUI page information.
 * @include <arkui/ui_info_collection.h>
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 26.2.0
 */
#ifndef ARKUI_NATIVE_UI_INFO_COLLECTION_H
#define ARKUI_NATIVE_UI_INFO_COLLECTION_H

#include "native_type.h"
#include "ui_json_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Collects texts from the current ArkUI page synchronously as JSON.
 * The returned JSON contains a "texts" array, for example:
 * @code{.json}
 * {"texts":[
 *     {"id":101,"rect":[0,0,120,32],"content":"hello"},
 *     {"id":102,"rect":[0,40,160,32],"content":"world"}
 * ]}
 * @endcode
 * Each item contains an integer "id" identifying the text carrier in the
 * snapshot, a numeric "rect" array [x, y, w, h], and a string "content".
 * All four rectangle values are in px. x and y use the same window
 * coordinates as the text carrier's "windowOffset" in hidumper -default,
 * relative to the top-left of the target window, with x increasing rightward
 * and y increasing downward. w and h are the carrier's layout width and
 * height, matching "FrameRect" in the same dump. Positioning, scaling and
 * rotation follow the existing windowOffset behavior; the rectangle is not
 * recomputed as a transformed bounding box or clipped to visible regions.
 * Values may be fractional; x and y may be negative. All values are finite,
 * and w and h are non-negative.
 * @details Calling outside the UI thread of uiContext terminates the process.
 * For a nonzero return, error information is recorded through the existing
 * error-message facility. When that facility is available and recording and
 * formatting succeed, immediately read OH_ArkUI_NativeModule_GetErrorMessage
 * on the same thread for the code, query name, and fixed failure reason.
 * Its existing empty result when unavailable and allocation behavior apply;
 * this query adds no low-memory diagnostic guarantee or fallback.
 * Text is collected from eligible ArkUI text components in the UI instance
 * specified by uiContext. Web content is excluded. Eligible content during
 * page transitions and in overlays may be included. Results are not clipped
 * to the viewport or filtered by pixel occlusion.
 * Collection depends on the component's available text, active state,
 * active and visible ancestors, and positive transformed width and height.
 * This function does not flush layout, wait for drawing, instantiate lazy
 * content, or change the page state. It requires no prior collection call.
 * On success, the immutable wrapper uses schema version 1 and contains a
 * JSON object with a required "texts" array. Each eligible text component
 * produces one item in ascending node ID order. Text uses the component's
 * available source content and text representation, including Span/Symbol
 * content. Input fields and rich editors provide eligible placeholder text;
 * their entered body text is not collected.
 * Independently eligible child text components are evaluated separately.
 * Different components have distinct IDs within a snapshot, even if their
 * text is identical. With no eligible text, the result is {"texts":[]}.
 * A missing page alone is not an error.
 * Use OH_ArkUI_NativeModule_UIJsonWrapper_GetData,
 * OH_ArkUI_NativeModule_UIJsonWrapper_GetSize, and
 * OH_ArkUI_NativeModule_UIJsonWrapper_GetSchemaVersion to read the JSON and
 * its metadata. The size is the UTF-8 byte length of the entire JSON payload,
 * excluding its terminating null character. Release the result with
 * OH_ArkUI_NativeModule_UIJsonWrapper_Destroy.
 * @param uiContext A valid framework-provided context of the calling app.
 * @param pageText Writable output slot, initialized to NULL by the caller.
 * A valid slot is set to NULL on failure; an empty page still returns a
 * wrapper.
 * @return ARKUI_ERROR_CODE_NO_ERROR on success.
 * ARKUI_ERROR_CODE_PARAM_INVALID if pageText is NULL.
 * ARKUI_ERROR_CODE_UI_CONTEXT_INVALID if uiContext is NULL or no longer
 * valid.
 * ARKUI_ERROR_CODE_CAPI_INIT_ERROR if the native implementation is
 * unavailable.
 * ARKUI_ERROR_CODE_INTERNAL_ERROR if the JSON payload
 * cannot be represented by uint32_t size, or collection/serialization fails.
 * @release ui_json_wrapper/OH_ArkUI_NativeModule_UIJsonWrapper_Destroy {pageText}
 * @since 26.2.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_GetPageText(
    ArkUI_ContextHandle uiContext, OH_ArkUI_NativeModule_UIJsonWrapper** pageText);

#ifdef __cplusplus
}
#endif

#endif /* ARKUI_NATIVE_UI_INFO_COLLECTION_H */
/** @} */
