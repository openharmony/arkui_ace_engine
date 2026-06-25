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
 * @brief Defines a set of Progress enum and interface.
 *
 * @since 12
 */

/**
 * @file progress.h
 *
 * @brief Defines a set of Progress enum and interface.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_PROGRESS_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_PROGRESS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Set the linear progress indicator style.
 *
 * @since 15
 */
typedef struct ArkUI_ProgressLinearStyleOption ArkUI_ProgressLinearStyleOption;
/**
 * @brief Enumerates the styles of the progress indicator.
 *
 * @since 12
 */
typedef enum {
    /** Linear style. */
    ARKUI_PROGRESS_TYPE_LINEAR = 0,
    /** Indeterminate ring style. */
    ARKUI_PROGRESS_TYPE_RING,
    /** Eclipse style. */
    ARKUI_PROGRESS_TYPE_ECLIPSE,
    /** Determinate ring style. */
    ARKUI_PROGRESS_TYPE_SCALE_RING,
    /** Capsule style. */
    ARKUI_PROGRESS_TYPE_CAPSULE,
} ArkUI_ProgressType;
/**
 * @brief Destroy linear progress indicator style information.
 *
 * @param option Linear progress indicator style information.
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_Destroy(ArkUI_ProgressLinearStyleOption* option);
/**
 * @brief Set whether the scan effect is enabled.
 *
 * @param option Linear progress indicator style information.
 * @param enabled Whether to enable the scan effect. Default value: false.
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_SetScanEffectEnabled(ArkUI_ProgressLinearStyleOption* option, bool enabled);
/**
 * @brief Set whether smoothing effect is enabled.
 *
 * @param option Linear progress indicator style information.
 * @param enabled Whether to enable the smooth effect. When this effect is enabled, the progress change to
 * the set value takes place gradually. Otherwise, it takes place immediately. Default value: true.
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_SetSmoothEffectEnabled(ArkUI_ProgressLinearStyleOption* option, bool enabled);
/**
 * @brief Set linear progress indicator stroke width.
 *
 * @param option Linear progress indicator style information.
 * @param strokeWidth Stroke width of the progress indicator. It cannot be set in percentage.
 * Default value: 4.0vp.
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_SetStrokeWidth(ArkUI_ProgressLinearStyleOption* option, float strokeWidth);
/**
 * @brief Set linear progress indicator stroke radius.
 *
 * @param option Linear progress indicator style information.
 * @param strokeRadius Rounded corner radius of the progress indicator. Value range: [0, strokeWidth/2].
 * Default value: strokeWidth/2.
 * @since 15
 */
void OH_ArkUI_ProgressLinearStyleOption_SetStrokeRadius(ArkUI_ProgressLinearStyleOption* option, float strokeRadius);
/**
 * @brief Get whether scan effect is enable.
 *
 * @param option Linear progress indicator style information.
 * @return Whether to enable the scan effect.
 * @since 15
 */
bool OH_ArkUI_ProgressLinearStyleOption_GetScanEffectEnabled(ArkUI_ProgressLinearStyleOption* option);
/**
 * @brief Get whether smoothing effect is enabled.
 *
 * @param option Linear progress indicator style information.
 * @return Whether to enable the smooth effect.
 * @since 15
 */
bool OH_ArkUI_ProgressLinearStyleOption_GetSmoothEffectEnabled(ArkUI_ProgressLinearStyleOption* option);
/**
 * @brief Get linear progress indicator stroke width.
 *
 * @param option Linear progress indicator style information.
 * @return Stroke width of the progress indicator.
 * @since 15
 */
float OH_ArkUI_ProgressLinearStyleOption_GetStrokeWidth(ArkUI_ProgressLinearStyleOption* option);
/**
 * @brief Get linear progress indicator stroke radius.
 *
 * @param option Linear progress indicator style information.
 * @return Rounded corner radius of the progress indicator.
 * @since 15
 */
float OH_ArkUI_ProgressLinearStyleOption_GetStrokeRadius(ArkUI_ProgressLinearStyleOption* option);


/**
 * @brief Create linear progress indicator style information.
 *
 * @return Returns a <b>ProgressLinearStyleOption</b> instance.
 * <br> If the result returns nullptr, there may be out of memory.
 * @since 15
 */
ArkUI_ProgressLinearStyleOption* OH_ArkUI_ProgressLinearStyleOption_Create(void);
#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_PROGRESS_H
/** @} */
