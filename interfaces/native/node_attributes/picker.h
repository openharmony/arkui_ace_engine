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
 * @brief Provides picker type definitions of ArkUI on the native side.
 *
 * @since 12
 */

/**
 * @file picker.h
 *
 * @brief Defines the common types and APIs for picker components.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */

#ifndef ARKUI_NATIVE_NODE_ATTRIBUTES_PICKER_H
#define ARKUI_NATIVE_NODE_ATTRIBUTES_PICKER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the modes of the date picker.
 *
 * @since 18
 */
typedef enum {
    /**
     * A mode that displays the date in months, days of month, and years.
     *
     * @since 18
     */
    ARKUI_DATEPICKER_MODE_DATE = 0,
    /**
     * A mode that displays the date in months and years.
     *
     * @since 18
     */
    ARKUI_DATEPICKER_YEAR_AND_MONTH = 1,
    /**
     * A mode that displays the date in months and days of the month.
     *
     * @since 18
     */
    ARKUI_DATEPICKER_MONTH_AND_DAY = 2,
} ArkUI_DatePickerMode;

/**
 * @brief Enumerates the types of the text picker.
 *
 * @since 12
 */
typedef enum {
    /**
     * Single-column text picker.
     *
     * @since 12
     */
    ARKUI_TEXTPICKER_RANGETYPE_SINGLE = 0,
    /**
     * Multi-column text picker.
     *
     * @since 12
     */
    ARKUI_TEXTPICKER_RANGETYPE_MULTI = 1,
    /**
     * Single-column text picker with image resources.
     *
     * @since 12
     */
    ARKUI_TEXTPICKER_RANGETYPE_RANGE_CONTENT = 2,
    /**
     * Interconnected multi-column text picker.
     *
     * @since 12
     */
    ARKUI_TEXTPICKER_RANGETYPE_CASCADE_RANGE_CONTENT = 3,
} ArkUI_TextPickerRangeType;

/**
 * @brief Defines the input structure of the single-column text picker with image resources.
 *
 * @since 12
 */
typedef struct {
    /**
     * Image resource.
     *
     * @since 12
     */
    const char* icon;
    /**
     * Text information.
     *
     * @since 12
     */
    const char* text;
} ARKUI_TextPickerRangeContent;

/**
 * @brief Defines the input structure of the interconnected multi-column text picker.
 *
 * @since 12
 */
typedef struct {
    /**
     * Text information.
     *
     * @since 12
     */
    const char* text;
    /**
     * Interconnected data.
     *
     * @since 12
     */
    const ARKUI_TextPickerRangeContent* children;
    /**
     * Size of the interconnected data array.
     *
     * @since 12
     */
    int32_t size;
} ARKUI_TextPickerCascadeRangeContent;

/**
 * @brief Enumerates the alignment modes between the calendar picker and the entry component.
 *
 * @since 12
 */
typedef enum {
    /**
     * Left aligned.
     *
     * @since 12
     */
    ARKUI_CALENDAR_ALIGNMENT_START = 0,
    /**
     * Center aligned.
     *
     * @since 12
     */
    ARKUI_CALENDAR_ALIGNMENT_CENTER = 1,
    /**
     * Right aligned.
     *
     * @since 12
     */
    ARKUI_CALENDAR_ALIGNMENT_END = 2,
} ArkUI_CalendarAlignment;

/**
 * @brief Enumerates the selected indicator type of picker.
 *
 * @since 23
 */
typedef enum {
    /**
     * background.
     *
     * @since 23
     */
    ARKUI_PICKER_INDICATOR_BACKGROUND = 0,
    /**
     * divider.
     *
     * @since 23
     */
    ARKUI_PICKER_INDICATOR_DIVIDER = 1,
} ArkUI_PickerIndicatorType;

/**
 * @brief Style parameters of background indicator.
 *
 * @since 23
 */
typedef struct {
    /**
     * background color, 0xARGB format for example <b>0xFF1122FF</b>
     *
     * @since 23
     */
    uint32_t backgroundColor;
    /**
     * radius of the top left corner.
     *
     * @since 23
     */
    float topLeftRadius;
    /**
     * radius of the top right corner
     *
     * @since 23
     */
    float topRightRadius;
    /**
     * radius of the bottom left corner
     *
     * @since 23
     */
    float bottomLeftRadius;
    /**
     * radius of the bottom right corner.
     *
     * @since 23
     */
    float bottomRightRadius;
} ArkUI_PickerIndicatorBackground;

/**
 * @brief Style parameters of divider indicator.
 *
 * @since 23
 */
typedef struct {
    /**
     * stroke width
     *
     * @since 23
     */
    float strokeWidth;
    /**
     * divider color, 0xARGB format for example <b>0xFF1122FF</b>
     *
     * @since 23
     */
    uint32_t dividerColor;
    /**
     * the distance between the divider and the beginning of the side of the picker (unit: vp).
     *
     * @since 23
     */
    float startMargin;
    /**
     * the distance between the divider and the end of the side of the picker (unit: vp).
     *
     * @since 23
     */
    float endMargin;
} ArkUI_PickerIndicatorDivider;

/**
 * @brief Definition of indicator style.
 *
 * @since 23
 */
typedef struct ArkUI_PickerIndicatorStyle ArkUI_PickerIndicatorStyle;

/**
  * @brief TextPicker single column selector, supports mixing text and images.
  *
  * @since 19
  */
typedef struct ArkUI_TextPickerRangeContentArray ArkUI_TextPickerRangeContentArray;

 /**
   * @brief TextPicker multi column selector, supports mixing text and images.
   *
   * @since 19
   */
typedef struct ArkUI_TextCascadePickerRangeContentArray ArkUI_TextCascadePickerRangeContentArray;

/**
 * @brief Creates a TextPickerRangeContent instance.
 *
 * @param length The length of the picker array. Value range: [1, +infinity).
 * @return Returns a pointer to the created instance on success. Initialize each item of the array
 *         as a null pointer;call {@link OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex} and/or
 *         {@link OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex} for each index as needed.
 *         Returns <b>nullptr</b> if <b>length</b> is not in <b>[1, +infinity)</b>.
 *         When the object is no longer used, release it with {@link OH_ArkUI_TextPickerRangeContentArray_Destroy}.
 * @since 19
 */
ArkUI_TextPickerRangeContentArray* OH_ArkUI_TextPickerRangeContentArray_Create(int32_t length);

/**
 * @brief Sets the icon resource path or URI for one item in an {@link ArkUI_TextPickerRangeContentArray}.
 *
 * @param handle Pointer returned by {@link OH_ArkUI_TextPickerRangeContentArray_Create}. If <b>nullptr</b>, this
 *        function has no effect.
 * @param icon Null-terminated C string for the icon (path or URI). The content is copied into the array; the caller
 *        keeps ownership of <b>icon</b>. If <b>nullptr</b>, this function has no effect.
 * @param index Index of the item to set. Valid values are greater than or equal to <b>0</b> and less than the
 *        <b>length</b> argument passed to {@link OH_ArkUI_TextPickerRangeContentArray_Create}. Otherwise this function
 *        does nothing.
 * @note If an icon was already set at <b>index</b>, the previous buffer is released before assigning the new value.
 * @since 19
 */
void OH_ArkUI_TextPickerRangeContentArray_SetIconAtIndex(
    ArkUI_TextPickerRangeContentArray* handle, char* icon, int32_t index);

/**
 * @brief Sets the display text for one item in an {@link ArkUI_TextPickerRangeContentArray}.
 *
 * @param handle Pointer returned by {@link OH_ArkUI_TextPickerRangeContentArray_Create}. If <b>nullptr</b>, this
 *        function has no effect.
 * @param text Null-terminated C string shown for the item. The content is copied into the array; the caller keeps
 *        ownership of <b>text</b>. If <b>nullptr</b>, this function has no effect.
 * @param index Index of the item to set. Valid values are greater than or equal to <b>0</b> and less than the
 *        <b>length</b> argument passed to {@link OH_ArkUI_TextPickerRangeContentArray_Create}. Otherwise this function
 *        does nothing.
 * @note If text was already set at <b>index</b>, the previous buffer is released before assigning the new value.
 * @since 19
 */
void OH_ArkUI_TextPickerRangeContentArray_SetTextAtIndex(
    ArkUI_TextPickerRangeContentArray* handle, char* text, int32_t index);

/**
 * @brief Releases an {@link ArkUI_TextPickerRangeContentArray} created by
 *        {@link OH_ArkUI_TextPickerRangeContentArray_Create}.
 *
 * @param handle Instance to destroy. If <b>nullptr</b>, this function has no effect.
 * @note After this call, <b>handle</b> must not be used. Do not pass pointers that were not returned by
 *       {@link OH_ArkUI_TextPickerRangeContentArray_Create}.
 * @since 19
 */
void OH_ArkUI_TextPickerRangeContentArray_Destroy(ArkUI_TextPickerRangeContentArray* handle);

/**
 * @brief Allocates one column level of an interconnected (cascade) TextPicker range. Use with range type
 *        {@link ARKUI_TEXTPICKER_RANGETYPE_CASCADE_RANGE_CONTENT}. The returned pointer addresses a contiguous array
 *        of sibling nodes; each node may carry display text and an optional next-level range from
 *        {@link OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex}.
 *
 * @param length Number of sibling entries on this column. Value range: <b>[1, +infinity)</b>.
 * @return Returns a pointer to the first sibling node when <b>length</b> is in <b>[1, +infinity)</b>; returns
 *     <b>nullptr</b> otherwise. The sibling count used for bounds checks equals <b>length</b>.
 * @since 19
 */
ArkUI_TextCascadePickerRangeContentArray* OH_ArkUI_TextCascadePickerRangeContentArray_Create(int32_t length);


/**
 * @brief Sets the display text for one sibling node on a cascade TextPicker level.
 *
 * @param handle Pointer returned by {@link OH_ArkUI_TextCascadePickerRangeContentArray_Create}. If <b>nullptr</b>,
 *        this function has no effect.
 * @param text Null-terminated C string. The content is copied; the caller keeps ownership of <b>text</b>. If
 *        <b>nullptr</b>, this function has no effect.
 * @param index Index of the sibling to set. Valid values are greater than or equal to <b>0</b> and less than the
 *        <b>length</b> argument passed to {@link OH_ArkUI_TextCascadePickerRangeContentArray_Create}. Otherwise this
 *        function does nothing.
 * @note If text was already set at <b>index</b>, the previous buffer is released before assigning the new value.
 * @since 19
 */
void OH_ArkUI_TextCascadePickerRangeContentArray_SetTextAtIndex(
    ArkUI_TextCascadePickerRangeContentArray* handle, char* text, int32_t index);

/**
 * @brief Sets the childs info of items in a multi text picker ranges.
 *
 * @param handle Pointer returned by {@link OH_ArkUI_TextCascadePickerRangeContentArray_Create}. If <b>nullptr</b>,
 *        this function has no effect.
 * @param child Pointer returned by {@link OH_ArkUI_TextCascadePickerRangeContentArray_Create} for the child column.
 *        If <b>nullptr</b>, this function has no effect. If a subtree already exists at <b>index</b>, it is destroyed
 *        with {@link OH_ArkUI_TextCascadePickerRangeContentArray_Destroy} before the new <b>child</b> is stored.
 *        While <b>child</b> stays attached under the parent, the caller must not call
 *        {@link OH_ArkUI_TextCascadePickerRangeContentArray_Destroy} on <b>child</b>.
 * @param index Index of the sibling that owns the subtree. Valid values are greater than or equal to <b>0</b> and less
 *        than the <b>length</b> argument passed to {@link OH_ArkUI_TextCascadePickerRangeContentArray_Create}.
 *        Otherwise this function does nothing.
 * @since 19
 */
void OH_ArkUI_TextCascadePickerRangeContentArray_SetChildAtIndex(
    ArkUI_TextCascadePickerRangeContentArray* handle, ArkUI_TextCascadePickerRangeContentArray* child, int32_t index);


/**
 * @brief Releases a cascade range level allocated with {@link OH_ArkUI_TextCascadePickerRangeContentArray_Create}.
 *
 * @param handle Instance to destroy. If <b>nullptr</b>, this function has no effect.
 * @note After this call, <b>handle</b> must not be used. Do not pass pointers that were not returned by
 *       {@link OH_ArkUI_TextCascadePickerRangeContentArray_Create}.
 * @note Do not call {@link OH_ArkUI_TextCascadePickerRangeContentArray_Destroy} on a <b>child</b> while
 *       it is still stored in a parent's {@code children}.
 * @since 19
 */
void OH_ArkUI_TextCascadePickerRangeContentArray_Destroy(ArkUI_TextCascadePickerRangeContentArray* handle);

/**
 * @brief Create the ArkUI_PickerIndicatorStyle instance.
 *
 * @param type The picker selection indicator enumeration type.
 * @return  ArkUI_PickerIndicatorStyle instance. If the instance returns a null pointer,
 *         it indicates creation failure, and the reason for the failure may be that the address space is full or
 *         the type not supported.
 * @since 23
*/
ArkUI_PickerIndicatorStyle* OH_ArkUI_PickerIndicatorStyle_Create(ArkUI_PickerIndicatorType type);

/**
* @brief Destroy the ArkUI_PickerIndicatorStyle instance.
*
* @param style The ArkUI_PickerIndicatorStyle instance to be destroyed.
* @since 23
*/
void OH_ArkUI_PickerIndicatorStyle_Dispose(ArkUI_PickerIndicatorStyle* style);

#ifdef __cplusplus
}
#endif

#endif // ARKUI_NATIVE_NODE_ATTRIBUTES_PICKER_H
/** @} */
