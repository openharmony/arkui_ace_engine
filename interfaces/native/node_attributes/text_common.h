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
 * @brief Defines a set of text common enum and interface.
 *
 * @since 12
 */

/**
 * @file text_common.h
 *
 * @brief Defines a set of text common enum and interface.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_COMMON_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_COMMON_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief Define the data objects of styled string supported by text components.
*
* @since 14
*/
typedef struct ArkUI_StyledString_Descriptor ArkUI_StyledString_Descriptor;
/**
 * @brief Defines the textField's counter configuration.
 *
 * @since 22
 */
typedef struct ArkUI_ShowCounterConfig ArkUI_ShowCounterConfig;
/**
 * @brief Defines the text content base controller.
 *
 * @since 23
 */
typedef struct ArkUI_TextContentBaseController ArkUI_TextContentBaseController;
/**
 * @brief Enumerates the text alignment mode.
 *
 * @since 12
 */
typedef enum {
    /** Aligned with the start. */
    ARKUI_TEXT_ALIGNMENT_START = 0,
    /** Horizontally centered. */
    ARKUI_TEXT_ALIGNMENT_CENTER,
    /** Aligned with the end. */
    ARKUI_TEXT_ALIGNMENT_END,
    /** Aligned with both margins. */
    ARKUI_TEXT_ALIGNMENT_JUSTIFY,
    /** Aligned with left to right.
     * @since 23
     */
    ARKUI_TEXT_ALIGNMENT_LEFT_TO_RIGHT = 4,
    /** Aligned with right to left.
     * @since 23
     */
    ARKUI_TEXT_ALIGNMENT_RIGHT_TO_LEFT = 5,
} ArkUI_TextAlignment;
/**
 * @brief Enumerates text vertical alignment styles.
 *
 * @since 20
 */
typedef enum {
    /** Aligned to the baseline. */
    ARKUI_TEXT_VERTICAL_ALIGNMENT_BASELINE = 0,
    /** Bottom aligned. */
    ARKUI_TEXT_VERTICAL_ALIGNMENT_BOTTOM,
    /** Center aligned. */
    ARKUI_TEXT_VERTICAL_ALIGNMENT_CENTER,
    /** Top aligned. */
    ARKUI_TEXT_VERTICAL_ALIGNMENT_TOP,
} ArkUI_TextVerticalAlignment;
/**
 * @brief Enumerates text content align styles.
 *
 * @since 21
 */
typedef enum {
    /** Top aligned. */
    ARKUI_TEXT_CONTENT_ALIGN_TOP = 0,
    /** Center aligned. */
    ARKUI_TEXT_CONTENT_ALIGN_CENTER = 1,
    /** Bottom aligned. */
    ARKUI_TEXT_CONTENT_ALIGN_BOTTOM = 2,
} ArkUI_TextContentAlign;
/**
 * @brief Enumerates the text text direction.
 *
 * @since 23
 */
typedef enum {
    /** The text direction is left to right. */
    ARKUI_TEXT_DIRECTION_LTR = 0,
    /** The text direction is right to left. */
    ARKUI_TEXT_DIRECTION_RTL = 1,
    /** The text direction follows the component layout. */
    ARKUI_TEXT_DIRECTION_DEFAULT = 2,
    /** The text direction follows the actual text. */
    ARKUI_TEXT_DIRECTION_AUTO = 3,
} ArkUI_TextDirection;
/**
 * @brief Enumerates the types of the Enter key for a single-line text box.
 *
 * @since 12
 */
typedef enum {
    /** The Enter key is labeled "Go." */
    ARKUI_ENTER_KEY_TYPE_GO = 2,
    /** The Enter key is labeled "Search." */
    ARKUI_ENTER_KEY_TYPE_SEARCH = 3,
    /** The Enter key is labeled "Send." */
    ARKUI_ENTER_KEY_TYPE_SEND,
    /** The Enter key is labeled "Next." */
    ARKUI_ENTER_KEY_TYPE_NEXT,
    /** The Enter key is labeled "Done." */
    ARKUI_ENTER_KEY_TYPE_DONE,
    /** The Enter key is labeled "Previous." */
    ARKUI_ENTER_KEY_TYPE_PREVIOUS,
    /** The Enter key is labeled "New Line." */
    ARKUI_ENTER_KEY_TYPE_NEW_LINE,
} ArkUI_EnterKeyType;
/**
 * @brief Enumerates the text decoration types.
 *
 * @since 12
 */
typedef enum {
    /** No text decoration. */
    ARKUI_TEXT_DECORATION_TYPE_NONE = 0,
    /** Line under the text. */
    ARKUI_TEXT_DECORATION_TYPE_UNDERLINE,
    /** Line over the text. */
    ARKUI_TEXT_DECORATION_TYPE_OVERLINE,
    /** Line through the text. */
    ARKUI_TEXT_DECORATION_TYPE_LINE_THROUGH,
} ArkUI_TextDecorationType;
/**
 * @brief Enumerates the text decoration styles.
 *
 * @since 12
 */
typedef enum {
    /** Single solid line. */
    ARKUI_TEXT_DECORATION_STYLE_SOLID = 0,
    /** Double solid line. */
    ARKUI_TEXT_DECORATION_STYLE_DOUBLE,
    /** Dotted line. */
    ARKUI_TEXT_DECORATION_STYLE_DOTTED,
    /** Dashed line. */
    ARKUI_TEXT_DECORATION_STYLE_DASHED,
    /** Wavy line. */
    ARKUI_TEXT_DECORATION_STYLE_WAVY,
} ArkUI_TextDecorationStyle;
/**
 * @brief Enumerates the text cases.
 *
 * @since 12
 */
typedef enum {
    /** The original case of the text is retained. */
    ARKUI_TEXT_CASE_NORMAL = 0,
    /** All letters in the text are in lowercase. */
    ARKUI_TEXT_CASE_LOWER,
    /** All letters in the text are in uppercase. */
    ARKUI_TEXT_CASE_UPPER,
} ArkUI_TextCase;
/**
 * @brief Defines whether copy and paste is allowed for text content.
 *
 * @since 12
 */
typedef enum {
    /** Copy is not allowed. */
    ARKUI_TEXT_COPY_OPTIONS_NONE = 0,
    /** Intra-application copy is allowed. */
    ARKUI_TEXT_COPY_OPTIONS_IN_APP,
    /** Intra-device copy is allowed. */
    ARKUI_TEXT_COPY_OPTIONS_LOCAL_DEVICE,
    /** Cross-device copy is allowed. */
    ARKUI_TEXT_COPY_OPTIONS_CROSS_DEVICE,
} ArkUI_TextCopyOptions;
/**
 * @brief Enumerates the display modes when the text is too long.
 *
 * @since 12
 */
typedef enum {
    /** Extra-long text is not clipped. */
    ARKUI_TEXT_OVERFLOW_NONE = 0,
    /** Extra-long text is clipped. */
    ARKUI_TEXT_OVERFLOW_CLIP,
    /** An ellipsis (...) is used to represent text overflow. */
    ARKUI_TEXT_OVERFLOW_ELLIPSIS,
    /** Text continuously scrolls when text overflow occurs. */
    ARKUI_TEXT_OVERFLOW_MARQUEE,
} ArkUI_TextOverflow;
/**
 * @brief Enumerates the word break rules.
 *
 * @since 12
 */
typedef enum {
    /** Word breaks can occur between any two characters for Chinese, Japanese, and Korean (CJK) text, but can occur
     *  only at a space character for non-CJK text (such as English). */
    ARKUI_WORD_BREAK_NORMAL = 0,
    /** Word breaks can occur between any two characters for non-CJK text. CJK text behavior is the same as for
     *  <b>NORMAL</b>. */
    ARKUI_WORD_BREAK_BREAK_ALL,
    /** This option has the same effect as <b>BREAK_ALL</b> for non-CJK text, except that if it preferentially wraps
     *  lines at appropriate characters (for example, spaces) whenever possible.
        CJK text behavior is the same as for <b>NORMAL</b>. */
    ARKUI_WORD_BREAK_BREAK_WORD,
    /**
     * @brief Line breaks can occur between any two syllabic units for non-CJK text.
     * CJK text behavior is the same as for <b>NORMAL</b>.
     * @since 18
     */
    ARKUI_WORD_BREAK_HYPHENATION,
} ArkUI_WordBreak;
/**
 * @brief Enumerates the ellipsis positions.
 *
 * @since 12
 */
typedef enum {
    /** An ellipsis is used at the start of the line of text. */
    ARKUI_ELLIPSIS_MODE_START = 0,
    /** An ellipsis is used at the center of the line of text. */
    ARKUI_ELLIPSIS_MODE_CENTER,
    /** An ellipsis is used at the end of the line of text. */
    ARKUI_ELLIPSIS_MODE_END,
    /**
     *@brief An ellipsis is used at the start of the line of text for multiline and single line.
     *@since 24
     */
    ARKUI_ELLIPSIS_MODE_MULTILINE_START,
    /**
     *@brief An ellipsis is used at the center of the line of text for multiline and single line.
     *@since 24
     */
    ARKUI_ELLIPSIS_MODE_MULTILINE_CENTER,
} ArkUI_EllipsisMode;
/**
 * @brief Defines the keyboard style of input box
 *
 * @since 15
 */
typedef enum {
    /**
     * Default appearance mode, won't adopt immersive styles.
     * @since 15
     */
    ARKUI_KEYBOARD_APPEARANCE_NONE_IMMERSIVE = 0,
    /**
     * Immersive mode.
     * @since 15
     */
    ARKUI_KEYBOARD_APPEARANCE_IMMERSIVE = 1,
    /**
     * Light immersive style.
     * @since 15
     */
    ARKUI_KEYBOARD_APPEARANCE_LIGHT_IMMERSIVE = 2,
    /**
     * Dark immersive style.
     * @since 15
     */
    ARKUI_KEYBOARD_APPEARANCE_DARK_IMMERSIVE = 3,
} ArkUI_KeyboardAppearance;
/**
 * @brief Defines the text menu item for edit menu item.
 *
 * @since 22
 */
typedef struct ArkUI_TextMenuItem ArkUI_TextMenuItem;
/**
 * @brief Defines text menu item array.
 *
 * @since 22
 */
typedef struct ArkUI_TextMenuItemArray ArkUI_TextMenuItemArray;
/**
 * @brief Enumerates the text menu item id.
 *
 * @since 22
 */
typedef enum {
    /**
     * Indicates the TextMenuItemId to copy and delete the currently selected text.
     */
    ARKUI_TEXT_MENU_ITEM_ID_CUT = 0,

    /**
     * Indicates the TextMenuItemId to copy the currently selected text to the clipboard.
     */
    ARKUI_TEXT_MENU_ITEM_ID_COPY = 1,

    /**
     * Indicates the TextMenuItemId to copy the current contents of the clipboard into the text view.
     */
    ARKUI_TEXT_MENU_ITEM_ID_PASTE = 2,

    /**
     * Indicates the TextMenuItemId to select all text in a text view.
     */
    ARKUI_TEXT_MENU_ITEM_ID_SELECT_ALL = 3,

    /**
     * Indicates the TextMenuItemId for collaboration service menu items.
     */
    ARKUI_TEXT_MENU_ITEM_ID_COLLABORATION_SERVICE = 4,

    /**
     * Indicates the TextMenuItemId to recognize the text in the picture and input it into the text view.
     */
    ARKUI_TEXT_MENU_ITEM_ID_CAMERA_INPUT = 5,

    /**
     * Indicates the TextMenuItemId to help with text creation by invoking large models.
     */
    ARKUI_TEXT_MENU_ITEM_ID_AI_WRITER = 6,

    /**
     * Indicates the TextMenuItemId to translate the selected content.
     */
    ARKUI_TEXT_MENU_ITEM_ID_TRANSLATE = 7,

    /**
     * Indicates the TextMenuItemId to search the selected content.
     */
    ARKUI_TEXT_MENU_ITEM_ID_SEARCH = 8,

    /**
     * Indicates the TextMenuItemId to share the selected content.
     */
    ARKUI_TEXT_MENU_ITEM_ID_SHARE = 9,

    /**
     * Indicates the TextMenuItemId to open url.
     */
    ARKUI_TEXT_MENU_ITEM_ID_URL = 10,

    /**
     * Indicates the TextMenuItemId to open email.
     */
    ARKUI_TEXT_MENU_ITEM_ID_EMAIL = 11,

    /**
     * Indicates the TextMenuItemId to call the phone number.
     */
    ARKUI_TEXT_MENU_ITEM_ID_PHONE_NUMBER = 12,

    /**
     * Indicates the TextMenuItemId to open map.
     */
    ARKUI_TEXT_MENU_ITEM_ID_ADDRESS = 13,

    /**
     * Indicates the TextMenuItemId to open calendar.
     */
    ARKUI_TEXT_MENU_ITEM_ID_DATA_TIME = 14,

    /**
     * Indicates the TextMenuItemId for asking AI.
     */
    ARKUI_TEXT_MENU_ITEM_ID_ASK_AI = 15,

    /**
     * Autofill. For example, the account and password can be automatically filled.
     * @since 24
     */
    ARKUI_TEXT_MENU_ITEM_ID_AUTO_FILL = 16,

    /**
     * Password vault.
     * @since 24
     */
    ARKUI_TEXT_MENU_ITEM_ID_PASSWORD_VAULT = 17,

    /**
     * Inclusive begin of app-reserved ID range.
     */
    ARKUI_TEXT_MENU_ITEM_ID_APP_RESERVED_BEGIN = 10000,

    /**
     * Inclusive end of app-reserved ID range.
     */
    ARKUI_TEXT_MENU_ITEM_ID_APP_RESERVED_END = 20000,
} ArkUI_TextMenuItemId;
/**
 * @brief Defines the text menu item for edit menu options.
 *
 * @since 22
 */
typedef struct ArkUI_TextEditMenuOptions ArkUI_TextEditMenuOptions;
/**
 * The text menu create callback function.
 *
 * @param items The framework creates and owns the array.
 *     In callback: the developer can modify the array by calling {@link OH_ArkUI_TextMenuItemArray_Insert},
 *     {@link OH_ArkUI_TextMenuItemArray_Erase}, or similar APIs.
 *     The developer must not free the array instance.
 * @param userData User defined data.
 * @since 22
 */
typedef void (*ArkUI_TextCreateMenuCallback)(
    ArkUI_TextMenuItemArray*    items,
    void*                       userData
);
/**
 * The text menu prepare callback function.
 *
 * @param items The framework creates and owns the array.
 *     In callback: the developer can modify the array by calling {@link OH_ArkUI_TextMenuItemArray_Insert},
 *     {@link OH_ArkUI_TextMenuItemArray_Erase}, or similar APIs.
 *     The developer must not free the array instance.
 * @param userData User defined data.
 * @since 22
 */
typedef void (*ArkUI_TextPrepareMenuCallback)(
    ArkUI_TextMenuItemArray*    items,
    void*                       userData
);
/**
 * The text menu item click callback function.
 *
 * @param item The menu item click.
 * @param start The start offset of the selected content.
 * @param end The end offset of the selected content.
 * @param userData The user data.
 * @return bool Return True, the event is consumed, false otherwise.
 * @since 22
 */
typedef bool (*ArkUI_TextMenuItemClickCallback)(
    const ArkUI_TextMenuItem*    item,
    int32_t                      start,
    int32_t                      end,
    void*                        userData
);
/**
 * @brief Defines the selection menu.
 *
 * @since 22
 */
typedef struct ArkUI_TextSelectionMenuOptions ArkUI_TextSelectionMenuOptions;
/**
 * @brief Defines decoration style options.
 *
 * @since 24
 */
typedef struct OH_ArkUI_DecorationStyleOptions OH_ArkUI_DecorationStyleOptions;
/**
 * @brief Enumerates line break policies.
 *
 * @since 24
 */
typedef enum {
    /**
     * Greedy mode.<br>Places as many words on a line as possible and moves to the next line only if no more words can
     * fit into the same line.
     * @since 24
     */
    OH_ARKUI_LINE_BREAK_STRATEGY_GREEDY = 0,
    /**
     * High-quality mode.<br>Fills in lines as much as possible on the basis of **BALANCED**, which may results in a
     * large blank area on the last line.
     * @since 24
     */
    OH_ARKUI_LINE_BREAK_STRATEGY_HIGH_QUALITY = 1,
    /**
     * Balance mode.<br>Without splitting words, the width of each line in a paragraph is the same as much as possible.
     * @since 24
     */
    OH_ARKUI_LINE_BREAK_STRATEGY_BALANCE = 2,
} OH_ArkUI_LineBreakStrategy;
/**
 * @brief Enumerates the text span type.
 *
 * @since 22
 */
typedef enum {
    /** The span type only contains text. */
    ARKUI_TEXT_SPAN_TYPE_TEXT = 0,
    /** The span type only contains image. */
    ARKUI_TEXT_SPAN_TYPE_IMAGE = 1,
    /** The span type contains both text and image. */
    ARKUI_TEXT_SPAN_TYPE_MIXED = 2,
    /**
     * When no other types are explicitly specified, this type will be matched.
     * When this type is registered but TEXT, IMAGE, or MIXED types are not registered,
     * this type will be triggered and displayed for those registered types.
     */
    ARKUI_TEXT_SPAN_TYPE_DEFAULT = 3,
} ArkUI_TextSpanType;
/**
 * @brief Enumerates the text response type.
 *
 * @since 22
 */
typedef enum {
    /** The response type of right click. */
    ARKUI_TEXT_RESPONSE_TYPE_RIGHT_CLICK = 0,
    /** The response type of long press. */
    ARKUI_TEXT_RESPONSE_TYPE_LONG_PRESS = 1,
    /** The response type of select by mouse. */
    ARKUI_TEXT_RESPONSE_TYPE_SELECT = 2,
    /**
     * When no other types are explicitly specified, this type will be matched.
     * When this type is registered but RIGHT_CLICK, LONG_PRESS, or SELECT types are not registered,
     * this type will be triggered and displayed for right-click, long press, and mouse selection actions.
     */
    ARKUI_TEXT_RESPONSE_TYPE_DEFAULT = 3,
} ArkUI_TextResponseType;

/**
 * @brief Creates a configuration object for textField's counter.
 *
 * @return A pointer to the configuration object.
 * @since 22
 */
ArkUI_ShowCounterConfig* OH_ArkUI_ShowCounterConfig_Create();

/**
 * @brief Disposes a configuration object for textField's counter.
 *
 * @param config Pointer to the configuration object to be disposed.
 * @since 22
 */
void OH_ArkUI_ShowCounterConfig_Dispose(ArkUI_ShowCounterConfig* config);

/**
 * @brief Sets the color of counter when textField hasn't wanted to exceed the maximum character count.
 *
 * @param config Pointer to the configuration object to be modified.
 * @param color The color of the counter when textField hasn't wanted to exceed the maximum character count, in 0xARGB format.
 * @since 22
 */
void OH_ArkUI_ShowCounterConfig_SetCounterTextColor(ArkUI_ShowCounterConfig* config, uint32_t color);

/**
 * @brief Sets the color of counter when textField wants to exceed the maximum character count.
 *
 * @param config Pointer to the configuration object to be modified.
 * @param color The color of the counter when textField wants to exceed the maximum character count, in 0xARGB format.
 * @since 22
 */
void OH_ArkUI_ShowCounterConfig_SetCounterTextOverflowColor(ArkUI_ShowCounterConfig* config, uint32_t color);

/**
 * @brief Gets the color of counter when textField hasn't wanted to exceed the maximum character count.
 *
 * @param config Pointer to the configuration object.
 * @return Returns the color of the counter when textField hasn't wanted to exceed the maximum character count, in 0xARGB format.
 * @since 22
 */
uint32_t OH_ArkUI_ShowCounterConfig_GetCounterTextColor(ArkUI_ShowCounterConfig* config);

/**
 * @brief Gets the color of counter when textField wants to exceed the maximum character count.
 *
 * @param config Pointer to the configuration object.
 * @return Returns the color of the counter when textField wants to exceed the maximum character count, in 0xARGB format.
 * @since 22
 */
uint32_t OH_ArkUI_ShowCounterConfig_GetCounterTextOverflowColor(ArkUI_ShowCounterConfig* config);
/**
 * @brief Create an object of the text edit menu item.
 *
 * @return A pointer to the ArkUI_TextMenuItem.
 * @since 22
 */
ArkUI_TextMenuItem* OH_ArkUI_TextMenuItem_Create();

/**
 * @brief Dispose an object of the text edit menu options.
 *
 * @param textMenuItem Pointer to the ArkUI_TextMenuItem object to be disposed.
 * @since 22
 */
void OH_ArkUI_TextMenuItem_Dispose(ArkUI_TextMenuItem* textMenuItem);
/**
 * @brief Create an object of the text edit menu options.
 *
 * @return A pointer to the ArkUI_TextEditMenuOptions.
 * @since 22
 */
ArkUI_TextEditMenuOptions* OH_ArkUI_TextEditMenuOptions_Create();

/**
 * @brief Dispose an object of the text edit menu options.
 *
 * @param editMenuOptions Pointer to the ArkUI_TextEditMenuOptions object to be disposed.
 * @since 22
 */
void OH_ArkUI_TextEditMenuOptions_Dispose(ArkUI_TextEditMenuOptions* editMenuOptions);
/**
 * @brief Create an object of the text selection menu options.
 *
 * @return A pointer to the ArkUI_TextSelectionMenuOptions.
 * @since 22
 */
ArkUI_TextSelectionMenuOptions* OH_ArkUI_TextSelectionMenuOptions_Create();

/**
 * @brief Dispose an object of the text selection menu options.
 *
 * @param selectionMenuOptions Pointer to the ArkUI_TextSelectionMenuOptions object to be disposed.
 * @since 22
 */
void OH_ArkUI_TextSelectionMenuOptions_Dispose(ArkUI_TextSelectionMenuOptions* selectionMenuOptions);
/**
 * @brief Create an object of the text content base controller.
 *
 * @return A pointer to the controller object.
 * @since 23
 */
ArkUI_TextContentBaseController* OH_ArkUI_TextContentBaseController_Create();

/**
 * @brief Dispose an object of the text content base controller.
 *
 * @param {ArkUI_TextContentBaseController*} controller Pointer to the controller object to be disposed.
 * @since 23
 */
void OH_ArkUI_TextContentBaseController_Dispose(ArkUI_TextContentBaseController* controller);

/**
 * @brief Delete the character before the caret of the input field component in editing state.
 *        Otherwise, delete the last character of the input field component.
 *
 * @param {ArkUI_TextContentBaseController*} controller Pointer to the configuration object to be modified.
 * @since 23
 */
void OH_ArkUI_TextContentBaseController_DeleteBackward(ArkUI_TextContentBaseController* controller);

/**
 * @brief Scroll the input field component to make the specified content visible.
 *
 * @param {ArkUI_TextContentBaseController*} controller Pointer to the
 * configuration object to be modified.
 * @param {int32_t} start The start offset of the content to be made visible.
 * @param {int32_t} end The end offset of the content to be made visible
 * @since 23
 */
void OH_ArkUI_TextContentBaseController_ScrollToVisible(
    ArkUI_TextContentBaseController *controller, int32_t start, int32_t end);
/**
 * @brief Creates a decorative line style object. When the object is no longer used, call
 * {@link OH_ArkUI_DecorationStyleOptions_Destroy} to destroy it.
 *
 * @return Pointer to the {@link OH_ArkUI_DecorationStyleOptions} object.
 * @since 24
 */
OH_ArkUI_DecorationStyleOptions* OH_ArkUI_DecorationStyleOptions_Create();

/**
 * @brief Destroys the decorative line style object.
 *
 * @param options Pointer to the option object to be destroyed.
 * @since 24
 */
void OH_ArkUI_DecorationStyleOptions_Destroy(OH_ArkUI_DecorationStyleOptions* options);
#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_TEXT_COMMON_H
/** @} */
