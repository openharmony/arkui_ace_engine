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
 * @brief Defines a set of CustomSpan enum and interface.
 *
 * @since 12
 */

/**
 * @file custom_span.h
 *
 * @brief Defines a set of CustomSpan enum and interface.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_CUSTOM_SPAN_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_CUSTOM_SPAN_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines a struct for the measurement information of a custom span.
 *
 * @since 12
 */
typedef struct ArkUI_CustomSpanMeasureInfo ArkUI_CustomSpanMeasureInfo;
/**
 * @brief Defines a struct for the measurement metrics of a custom span.
 *
 * @since 12
 */
typedef struct ArkUI_CustomSpanMetrics ArkUI_CustomSpanMetrics;
/**
 * @brief Defines a struct for the drawing information of a custom span.
 *
 * @since 12
 */
typedef struct ArkUI_CustomSpanDrawInfo ArkUI_CustomSpanDrawInfo;
/**
 * @brief Disposes of measurement information of this custom span.
 *
 * @param info The CustomSpanMeasureInfo instance to be destroyed.
 * @since 12
*/
void OH_ArkUI_CustomSpanMeasureInfo_Dispose(ArkUI_CustomSpanMeasureInfo* info);
/**
 * @brief Obtains the font size of a custom span.
 *
 * @param info Indicates the pointer to the measurement information of a custom span.
 * @return Returns the font size. If a parameter error occurs, <b>0.0f</b> is returned.
 * <br> Possible causes: Parameter verification failed, the parameter should not be nullptr.
 * @since 12
*/
float OH_ArkUI_CustomSpanMeasureInfo_GetFontSize(ArkUI_CustomSpanMeasureInfo* info);
/**
 * @brief Disposes of measurement metrics of this custom span.
 *
 * @param metrics The CustomSpanMetrics instance to be destroyed.
 * @since 12
*/
void OH_ArkUI_CustomSpanMetrics_Dispose(ArkUI_CustomSpanMetrics* metrics);
/**
 * @brief Sets the width for a custom span.
 *
 * @param metrics Indicates the pointer to a <b>CustomSpanMetrics</b> instance.
 * @param width Indicates the width, in px. The width should be greater than 0.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         <br> Possible causes: Parameter verification failed, the parameter should not be nullptr.
 * @since 12
*/
int32_t OH_ArkUI_CustomSpanMetrics_SetWidth(ArkUI_CustomSpanMetrics* metrics, float width);
/**
 * @brief Sets the height for a custom span.
 *
 * @param metrics Indicates the pointer to a <b>CustomSpanMetrics</b> instance.
 * @param width Indicates the height, in px. The width should be greater than 0.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         <br> Possible causes: Parameter verification failed, the parameter should not be nullptr.
 * @since 12
*/
int32_t OH_ArkUI_CustomSpanMetrics_SetHeight(ArkUI_CustomSpanMetrics* metrics, float height);
/**
 * @brief Disposes of drawing information for this custom span.
 *
 * @param info The CustomSpanDrawInfo instance to be destroyed.
 * @since 12
*/
void OH_ArkUI_CustomSpanDrawInfo_Dispose(ArkUI_CustomSpanDrawInfo* info);
/**
 * @brief Obtains the x-axis offset of the custom span relative to the mounted component.
 *
 * @param info Indicates the pointer to the drawing information of a custom span.
 * @return Returns the x-axis offset. If a parameter error occurs, <b>0.0f</b> is returned.
 * <br> Possible causes: Parameter verification failed, the parameter should not be nullptr.
 * @since 12
*/
float OH_ArkUI_CustomSpanDrawInfo_GetXOffset(ArkUI_CustomSpanDrawInfo* info);
/**
 * @brief Obtains the top margin of the custom span relative to the mounted component.
 *
 * @param info Indicates the pointer to the drawing information of a custom span.
 * @return Returns the top margin. If a parameter error occurs, <b>0.0f</b> is returned.
 * <br> Possible causes: Parameter verification failed, the parameter should not be nullptr.
 * @since 12
*/
float OH_ArkUI_CustomSpanDrawInfo_GetLineTop(ArkUI_CustomSpanDrawInfo* info);
/**
 * @brief Obtains the bottom margin of the custom span relative to the mounted component.
 *
 * @param info Indicates the pointer to the drawing information of a custom span.
 * @return Returns the bottom margin. If a parameter error occurs, <b>0.0f</b> is returned.
 * <br> Possible causes: Parameter verification failed, the parameter should not be nullptr.
 * @since 12
*/
float OH_ArkUI_CustomSpanDrawInfo_GetLineBottom(ArkUI_CustomSpanDrawInfo* info);
/**
 * @brief Obtains the baseline offset of the custom span relative to the mounted component.
 *
 * @param info Indicates the pointer to the drawing information of a custom span.
 * @return Returns the baseline offset. If a parameter error occurs, <b>0.0f</b> is returned.
 * <br> Possible causes: Parameter verification failed, the parameter should not be nullptr.
 * @since 12
*/
float OH_ArkUI_CustomSpanDrawInfo_GetBaseline(ArkUI_CustomSpanDrawInfo* info);


/**
 * @brief Creates measurement information for this custom span.
 *
 * @return Returns a <b>CustomSpanMeasureInfo</b> instance.
 * <br> If the result returns nullptr, there may be out of memory.
 * @since 12
*/
ArkUI_CustomSpanMeasureInfo* OH_ArkUI_CustomSpanMeasureInfo_Create(void);
/**
 * @brief Creates measurement metrics for this custom span.
 *
 * @return Returns a <b>CustomSpanMetrics</b> instance.
 * <br> If the result returns nullptr, there may be out of memory.
 * @since 12
*/
ArkUI_CustomSpanMetrics* OH_ArkUI_CustomSpanMetrics_Create(void);
/**
 * @brief Creates drawing information for this custom span.
 *
 * @return Returns a <b>CustomSpanDrawInfo</b> instance.
 * <br> If the result returns nullptr, there may be out of memory.
 * @since 12
*/
ArkUI_CustomSpanDrawInfo* OH_ArkUI_CustomSpanDrawInfo_Create(void);
#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_CUSTOM_SPAN_H
/** @} */
