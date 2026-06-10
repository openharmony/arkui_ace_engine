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
 * @brief Defines a set of RichEditor enum and interface.
 *
 * @since 24
 */

/**
 * @file rich_editor.h
 *
 * @brief Defines a set of RichEditor enum and interface.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 24
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_RICH_EDITOR_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_RICH_EDITOR_H

#include <stdint.h>
#include <stdbool.h>
#include "text_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Defines the text selection menu options of the text editor.
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextEditorSelectionMenuOptions OH_ArkUI_TextEditorSelectionMenuOptions;
/**
 * @brief Defines the hint text options when no content is entered in the text editor.
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextEditorPlaceholderOptions OH_ArkUI_TextEditorPlaceholderOptions;
/**
 * @brief Defines the attribute string controller of the text editor.
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextEditorStyledStringController OH_ArkUI_TextEditorStyledStringController;
/**
 * @brief Defines the paragraph style of the text editor.
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextEditorParagraphStyle OH_ArkUI_TextEditorParagraphStyle;
/**
 * @brief Defines the text style of the text editor.
 *
 * @since 24
 */
typedef struct OH_ArkUI_TextEditorTextStyle OH_ArkUI_TextEditorTextStyle;
/**
 * @brief Enumerates vibration effect types.
 *
 * @since 24
 */
typedef enum {
    /**
     * No vibration.
     * @since 24
     */
    OH_ARKUI_HAPTIC_FEEDBACK_MODE_DISABLED = 0,
    /**
     * Vibration.
     * @since 24
     */
    OH_ARKUI_HAPTIC_FEEDBACK_MODE_ENABLED = 1,
    /**
     * System vibration.
     * @since 24
     */
    OH_ARKUI_HAPTIC_FEEDBACK_MODE_AUTO = 2,
} OH_ArkUI_HapticFeedbackMode;
/**
 * @brief Enumerates the span types of a custom text selection menu.
 *
 * @since 24
 */
typedef enum {
    /**
     * Text span.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_TEXT = 0,
    /**
     * Image span.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_IMAGE = 1,
    /**
     * Mixed span.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_MIXED = 2,
    /**
     * Custom layout span.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_BUILDER = 3,
    /**
     * Default span.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SPAN_TYPE_DEFAULT = 4
} OH_ArkUI_TextEditorSpanType;
/**
 * @brief Enumerates the response types of a custom text selection menu.
 *
 * @since 24
 */
typedef enum {
    /**
     * The menu is displayed when the component is right-clicked.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_RESPONSE_TYPE_RIGHT_CLICK = 0,
    /**
     * The menu is displayed when the component is long-pressed.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_RESPONSE_TYPE_LONG_PRESS = 1,
    /**
     * The menu is displayed when the component is selected.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_RESPONSE_TYPE_SELECT = 2,
    /**
     * Default response type.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_RESPONSE_TYPE_DEFAULT = 3,
} OH_ArkUI_TextEditorResponseType;
/**
 * @brief Enumerates text menu types.
 *
 * @since 24
 */
typedef enum {
    /**
     * Text selection menu.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_SELECTION_MENU = 0,
    /**
     * Preview menu.
     * @since 24
     */
    OH_ARKUI_TEXT_EDITOR_PREVIEW_MENU = 1,
} OH_ArkUI_TextMenuType;


/**
 * @brief Creates an option object for the placeholder text used when there is no input. When the object is no longer
 * used, call {@link OH_ArkUI_TextEditorPlaceholderOptions_Destroy} to destroy it.
 *
 * @return Pointer to the {@link OH_ArkUI_TextEditorPlaceholderOptions} object.
 * @since 24
 */
OH_ArkUI_TextEditorPlaceholderOptions* OH_ArkUI_TextEditorPlaceholderOptions_Create();

/**
 * @brief Destroys the option object for the placeholder text used when there is no input.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorPlaceholderOptions} object.
 * @since 24
 */
void OH_ArkUI_TextEditorPlaceholderOptions_Destroy(OH_ArkUI_TextEditorPlaceholderOptions* options);
/**
 * @brief Creates a styled string controller object for the text editor. When the object is no longer used, call
 * {@link OH_ArkUI_TextEditorStyledStringController_Destroy} to destroy it.
 *
 * @return Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @since 24
 */
OH_ArkUI_TextEditorStyledStringController* OH_ArkUI_TextEditorStyledStringController_Create();

/**
 * @brief Destroys the styled string controller object.
 *
 * @param controller Pointer to the {@link OH_ArkUI_TextEditorStyledStringController} object.
 * @since 24
 */
void OH_ArkUI_TextEditorStyledStringController_Destroy(OH_ArkUI_TextEditorStyledStringController* controller);
/**
 * @brief Creates a paragraph style object for the text editor. When the object is no longer used, call
 * {@link OH_ArkUI_TextEditorParagraphStyle_Destroy} to destroy it.
 *
 * @return Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @since 24
 */
OH_ArkUI_TextEditorParagraphStyle* OH_ArkUI_TextEditorParagraphStyle_Create();

/**
 * @brief Destroys the paragraph style object.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorParagraphStyle} object.
 * @since 24
 */
void OH_ArkUI_TextEditorParagraphStyle_Destroy(OH_ArkUI_TextEditorParagraphStyle* style);
/**
 * @brief Creates a text style object. When the object is no longer used, call
 * {@link OH_ArkUI_TextEditorTextStyle_Destroy} to destroy it.
 *
 * @return Pointer to the {@link OH_ArkUI_TextEditorTextStyle} object.
 * @since 24
 */
OH_ArkUI_TextEditorTextStyle* OH_ArkUI_TextEditorTextStyle_Create();

/**
 * @brief Destroys the text style object.
 *
 * @param style Pointer to the {@link OH_ArkUI_TextEditorTextStyle} object.
 * @since 24
 */
void OH_ArkUI_TextEditorTextStyle_Destroy(OH_ArkUI_TextEditorTextStyle* style);
/**
 * @brief Creates a text selection menu option object of the text editor. When the object is no longer used, call
 * {@link OH_ArkUI_TextEditorSelectionMenuOptions_Destroy} to destroy it.
 *
 * @return Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @since 24
 */
OH_ArkUI_TextEditorSelectionMenuOptions* OH_ArkUI_TextEditorSelectionMenuOptions_Create();

/**
 * @brief Destroys the text selection menu option object of the text editor.
 *
 * @param options Pointer to the {@link OH_ArkUI_TextEditorSelectionMenuOptions} object.
 * @since 24
 */
void OH_ArkUI_TextEditorSelectionMenuOptions_Destroy(OH_ArkUI_TextEditorSelectionMenuOptions* options);
#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_RICH_EDITOR_H
/** @} */
