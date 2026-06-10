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
 * @brief Defines a set of Text enum and interface.
 *
 * @since 12
 */

/**
 * @file text.h
 *
 * @brief Defines a set of Text enum and interface.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_H

#include <stdint.h>
#include <stdbool.h>
#include "text_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the font styles.
 *
 * @since 12
 */
typedef enum {
    /** Standard font style. */
    ARKUI_FONT_STYLE_NORMAL = 0,
    /** Italic font style. */
    ARKUI_FONT_STYLE_ITALIC
} ArkUI_FontStyle;
/**
 * @brief Enumerates the font weights.
 *
 * @since 12
 */
typedef enum {
    /** 100 */
    ARKUI_FONT_WEIGHT_W100 = 0,
    /** 200 */
    ARKUI_FONT_WEIGHT_W200,
    /** 300 */
    ARKUI_FONT_WEIGHT_W300,
    /** 400 */
    ARKUI_FONT_WEIGHT_W400,
    /** 500 */
    ARKUI_FONT_WEIGHT_W500,
    /** 600 */
    ARKUI_FONT_WEIGHT_W600,
    /** 700 */
    ARKUI_FONT_WEIGHT_W700,
    /** 800 */
    ARKUI_FONT_WEIGHT_W800,
    /** 900 */
    ARKUI_FONT_WEIGHT_W900,
    /** The font weight is bold. */
    ARKUI_FONT_WEIGHT_BOLD,
    /** The font weight is normal. */
    ARKUI_FONT_WEIGHT_NORMAL,
    /** The font weight is bolder. */
    ARKUI_FONT_WEIGHT_BOLDER,
    /** The font weight is lighter. */
    ARKUI_FONT_WEIGHT_LIGHTER,
    /** The font weight is medium. */
    ARKUI_FONT_WEIGHT_MEDIUM,
    /** The font weight is normal. */
    ARKUI_FONT_WEIGHT_REGULAR,
} ArkUI_FontWeight;
/**
 * @brief Defines how the adaptive height is determined for the text.
 *
 * @since 12
 */
typedef enum {
    /** Prioritize the <b>maxLines</b> settings. */
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MAX_LINES_FIRST = 0,
    /** Prioritize the <b>minFontSize</b> settings. */
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_MIN_FONT_SIZE_FIRST,
    /** Prioritize the layout constraint settings in terms of height. */
    ARKUI_TEXT_HEIGHT_ADAPTIVE_POLICY_LAYOUT_CONSTRAINT_FIRST,
} ArkUI_TextHeightAdaptivePolicy;
/**
 * @brief Defines the entity type for text recognition.
 *
 * @since 12
 */
typedef enum {
    /** Phone Number.*/
    ARKUI_TEXT_DATA_DETECTOR_TYPE_PHONE_NUMBER = 0,
    /** Link. */
    ARKUI_TEXT_DATA_DETECTOR_TYPE_URL,
    /** Mailbox. */
    ARKUI_TEXT_DATA_DETECTOR_TYPE_EMAIL,
    /** Address. */
    ARKUI_TEXT_DATA_DETECTOR_TYPE_ADDRESS,
} ArkUI_TextDataDetectorType;
/**
 * @brief Defines the configuration of text entity recognition.
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextDataDetectorConfig OH_ArkUI_TextDataDetectorConfig;
/**
 * @brief Enumerates the MarqueeStartPolicy.
 *
 * @since 23
 */
typedef enum {
    /** Start marquee in any case. This is the default policy. */
    ARKUI_MARQUEESTARTPOLICY_DEFAULT = 0,
    /** Start marquee only when get focus. */
    ARKUI_MARQUEESTARTPOLICY_ONFOCUS = 1
} ArkUI_MarqueeStartPolicy;
/**
 * @brief Enumerates the MarqueeUpdatePolicy.
 *
 * @since 23
 */
typedef enum {
    /** Reset scroll position and restart scroll. */
    ARKUI_MARQUEEUPDATEPOLICY_DEFAULT = 0,
    /** Preserve scroll position, just change to new text. */
    ARKUI_MARQUEEUPDATEPOLICY_PRESERVEPOSITION = 1
} ArkUI_MarqueeUpdatePolicy;
/**
 * @brief Defines the marquee options of text.
 *
 * @since 23
 */
typedef struct ArkUI_TextMarqueeOptions ArkUI_TextMarqueeOptions;
/**
 * @brief Defines controller for text.
 * @since 26.0.0
 */
typedef struct OH_ArkUI_TextController OH_ArkUI_TextController;
/**
 * @brief Defines the font weight configuration of text.
 *
 * @since 24
 */
typedef struct OH_ArkUI_FontWeightConfigs OH_ArkUI_FontWeightConfigs;
/**
 * @brief Defines the font configuration of text.
 *
 * @since 24
 */
typedef struct OH_ArkUI_FontConfigs OH_ArkUI_FontConfigs;


/**
 * @brief Create an option object for marquee animation of text.
 *
 * @return A pointer to the option object.
 * @since 23
 */
ArkUI_TextMarqueeOptions* OH_ArkUI_TextMarqueeOptions_Create();

/**
 * @brief Dispose the option object for marquee animation of text.
 *
 * @param option Pointer to the option object to be disposed.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_Dispose(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets the start flag of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object to be modified.
 * @param start Flag of is need to start marquee. True means start marquee, false means stop marquee.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetStart(ArkUI_TextMarqueeOptions* option, bool start);

/**
 * @brief Gets the start flag of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object.
 * @return Returns the start flag.
 * @since 23
 */
bool OH_ArkUI_TextMarqueeOptions_GetStart(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets the step size of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object to be modified.
 * @param step The step size of the marquee. The unit is vp.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetStep(ArkUI_TextMarqueeOptions* option, float step);

/**
 * @brief Gets the step size of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object.
 * @return Returns the step size of the marquee. The unit is vp.
 * @since 23
 */
float OH_ArkUI_TextMarqueeOptions_GetStep(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets the spacing between two rounds of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object to be modified.
 * @param spacing The spacing between two rounds of marquee. The unit is vp.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetSpacing(ArkUI_TextMarqueeOptions* option, float spacing);

/**
 * @brief Gets the spacing between two rounds of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object.
 * @return Returns the spacing between two rounds of marquee. The unit is vp.
 * @since 23
 */
float OH_ArkUI_TextMarqueeOptions_GetSpacing(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets the rounds of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object to be modified.
 * @param loop The rounds of the marquee.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetLoop(ArkUI_TextMarqueeOptions* option, int32_t loop);

/**
 * @brief Gets the rounds of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object.
 * @return Returns the rounds of the marquee.
 * @since 23
 */
int32_t OH_ArkUI_TextMarqueeOptions_GetLoop(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets the fromStart flag of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object to be modified.
 * @param fromStart The running direction of the marquee, true means running from start.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetFromStart(ArkUI_TextMarqueeOptions* option, bool fromStart);

/**
 * @brief Gets the fromStart flag of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object.
 * @return Returns the fromStart flag.
 * @since 23
 */
bool OH_ArkUI_TextMarqueeOptions_GetFromStart(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets the delay time between each round of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object to be modified.
 * @param delay The delay time between each round of the marquee.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetDelay(ArkUI_TextMarqueeOptions* option, int32_t delay);

/**
 * @brief Gets the delay time between each round of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object.
 * @return Returns the delay time between each round of the marquee.
 * @since 23
 */
int32_t OH_ArkUI_TextMarqueeOptions_GetDelay(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets the fadeout flag of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object to be modified.
 * @param fadeout The flag of whether the text is faded out.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetFadeout(ArkUI_TextMarqueeOptions* option, bool fadeout);

/**
 * @brief Gets the fadeout flag of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object.
 * @return Returns the fadeout flag.
 * @since 23
 */
bool OH_ArkUI_TextMarqueeOptions_GetFadeout(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets the start policy of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object to be modified.
 * @param startPolicy The start policy for marquee.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetStartPolicy(ArkUI_TextMarqueeOptions* option, ArkUI_MarqueeStartPolicy startPolicy);

/**
 * @brief Gets the start policy of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object.
 * @return Returns the start policy for marquee.
 * @since 23
 */
ArkUI_MarqueeStartPolicy OH_ArkUI_TextMarqueeOptions_GetStartPolicy(ArkUI_TextMarqueeOptions* option);

/**
 * @brief Sets the update policy of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object to be modified.
 * @param updatePolicy The update policy for marquee.
 * @since 23
 */
void OH_ArkUI_TextMarqueeOptions_SetUpdatePolicy(ArkUI_TextMarqueeOptions* option,
    ArkUI_MarqueeUpdatePolicy updatePolicy);

/**
 * @brief Gets the update policy of the option object for marquee animation of text.
 *
 * @param option Pointer to the option object.
 * @return Returns the update policy for marquee.
 * @since 23
 */
ArkUI_MarqueeUpdatePolicy OH_ArkUI_TextMarqueeOptions_GetUpdatePolicy(ArkUI_TextMarqueeOptions* option);
/**
 * @brief Creates a text entity recognition configuration object. When the object is no longer used, call
 * {@link OH_ArkUI_TextDataDetectorConfig_Destroy} to destroy it.
 *
 * @return Pointer to the {@link OH_ArkUI_TextDataDetectorConfig} object.
 * @since 24
 */
OH_ArkUI_TextDataDetectorConfig* OH_ArkUI_TextDataDetectorConfig_Create();

/**
 * @brief Destroys the text entity recognition configuration object.
 *
 * @param config Pointer to the {@link OH_ArkUI_TextDataDetectorConfig} object.
 * @since 24
 */
void OH_ArkUI_TextDataDetectorConfig_Destroy(OH_ArkUI_TextDataDetectorConfig* config);
/**
 * @brief Create a controller object for text.
 * @return A pointer to the text controller object.
 * @since 26.0.0
 */
OH_ArkUI_TextController* OH_ArkUI_TextController_Create();

/**
 * @brief Destroys the text controller.
 *
 * @param controller <b>Text</b> controller.
 * @since 26.0.0
 */
void OH_ArkUI_TextController_Destroy(OH_ArkUI_TextController* controller);
/**
 * @brief Create an option object for font weight configuration of text.
 *
 * @return A pointer to the option object.
 * @since 24
 */
OH_ArkUI_FontWeightConfigs* OH_ArkUI_FontWeightConfigs_Create();

/**
 * @brief Destroy an option object for font weight configuration of text.
 *
 * @param option Pointer to the option object to be destroyed.
 * @since 24
 */
void OH_ArkUI_FontWeightConfigs_Destroy(OH_ArkUI_FontWeightConfigs* option);

/**
 * @brief Sets the enableVariableFontWeight flag of an option object for font weight configuration of text.
 * The flag defines whether VariableFontWeight is supported. The default value is false.
 * True means enable VariableFontWeight, false means disable VariableFontWeight.
 *
 * @param option Pointer to the option object to be modified.
 * @param enable enableVariableFontWeight Flag.
 * @since 24
 */
void OH_ArkUI_FontWeightConfigs_SetEnableVariableFontWeight(OH_ArkUI_FontWeightConfigs* option, bool enable);

/**
 * @brief Gets the enableVariableFontWeight flag of an option object for font weight configuration of text.
 * The flag defines whether VariableFontWeight is supported. The default value is false.
 * True means enable VariableFontWeight, false means disable VariableFontWeight.
 *
 * @param option Pointer to the option object.
 * @return Returns the enableVariableFontWeight flag.
 * @since 24
 */
bool OH_ArkUI_FontWeightConfigs_GetEnableVariableFontWeight(OH_ArkUI_FontWeightConfigs* option);

/**
 * @brief Sets the enableDeviceFontWeightCategory flag of an option object for font weight configuration of text.
 * Defines whether font weight will be automatically updated when the device's font weight category changes.
 * The default value is true.
 * True means font weight will be automatically updated when the device's font weight category changes.
 * False means font weight will not be automatically updated when the device's font weight category changes.
 *
 * @param option Pointer to the option object to be modified.
 * @param enable enableDeviceFontWeightCategory Flag.
 * @since 24
 */
void OH_ArkUI_FontWeightConfigs_SetEnableDeviceFontWeightCategory(OH_ArkUI_FontWeightConfigs* option, bool enable);

/**
 * @brief Gets the enableDeviceFontWeightCategory flag of an option object for font weight configuration of text.
 * Defines whether font weight will be automatically updated when the device's font weight category changes.
 * The default value is true.
 * True means font weight will be automatically updated when the device's font weight category changes.
 * False means font weight will not be automatically updated when the device's font weight category changes.
 *
 * @param option Pointer to the option object.
 * @return Returns the enableDeviceFontWeightCategory flag.
 * @since 24
 */
bool OH_ArkUI_FontWeightConfigs_GetEnableDeviceFontWeightCategory(OH_ArkUI_FontWeightConfigs* option);
/**
 * @brief Create an option object for font configuration of text.
 *
 * @return A pointer to the option object.
 * @since 24
 */
OH_ArkUI_FontConfigs* OH_ArkUI_FontConfigs_Create();

/**
 * @brief Destroy an option object for font configuration of text.
 *
 * @param option Pointer to the option object to be destroyed.
 * @since 24
 */
void OH_ArkUI_FontConfigs_Destroy(OH_ArkUI_FontConfigs* option);

/**
 * @brief Sets the font weight configs of an option object for font configuration of text.
 *
 * @param option Pointer to the option object to be modified.
 * @param fontWeightConfigs font weight configs.
 * @since 24
 */
void OH_ArkUI_FontConfigs_SetFontWeightConfigs(OH_ArkUI_FontConfigs* option,
    OH_ArkUI_FontWeightConfigs* fontWeightConfigs);

/**
 * @brief Gets the font weight configs of an option object for font configuration of text.
 *
 * @param option Pointer to the option object.
 * @return Returns the font weight configs.
 * @since 24
 */
OH_ArkUI_FontWeightConfigs* OH_ArkUI_FontConfigs_GetFontWeightConfigs(OH_ArkUI_FontConfigs* option);
#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_H
/** @} */
