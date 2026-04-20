/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 * @brief 提供ArkUI在Native侧的UI能力，如UI组件创建销毁、树节点操作，属性设置，事件监听等。
 *
 * @since 12
 */

/**
 * @file native_styled_string_descriptor.h
 *
 * @brief 提供ArkUI在Native侧的属性字符串数据存储及转换的能力。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 14
 */

#ifndef ARKUI_NATIVE_STYLED_STRING_DESCRIPTOR_H
#define ARKUI_NATIVE_STYLED_STRING_DESCRIPTOR_H

// should be careful this path is not same in SDK.
#include "native_type.h"
#include "native_node.h"
#include "native_gesture.h"
#include "drawing_types.h"
#include "core/interfaces/arkoala/arkoala_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create a ArkUI_StyledString_Descriptor object.
 *
 * @return Pointer to the ArkUI_StyledString_Descriptor object.。
 * @since 14
 */
ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_Create();

/**
 * @brief Release the memory occupied by the ArkUI_StyledString_Descriptor object.
 *
 * @param descriptor Pointer to the ArkUI_StyledString_Descriptor object.
 * @since 14
 */
void OH_ArkUI_StyledString_Descriptor_Destroy(ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief Unmarshall the byte array that stores styled string information into a styled string.
 *
 * @param buffer The byte array that stores the unmarshalled information of the styled string.
 * @param bufferSize Indicate the length of the byte array.
 * @param descriptor Pointer to the ArkUI_StyledString_Descriptor object.
 * @return Error code.。
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 * @since 14
 */
int32_t OH_ArkUI_UnmarshallStyledStringDescriptor(
    uint8_t* buffer, size_t bufferSize, ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief Marshall the styled string into a byte array。
 *
 * @param buffer The byte array that stores the unmarshalled information of the styled string.
 * @param bufferSize Indicate the length of the byte array.
 * @param descriptor Pointer to the ArkUI_StyledString_Descriptor object.
 * @return Error code.
 *         {@link ARKUI_ERROR_CODE_NO_ERROR} Success.
 *         {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function parameter exception.
 *         {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} Invalid styled string
 * @since 14
 */
int32_t OH_ArkUI_MarshallStyledStringDescriptor(
    uint8_t* buffer, size_t bufferSize, ArkUI_StyledString_Descriptor* descriptor, size_t* resultSize);

/**
 * @brief Convert the styled string into html.
 *
 * @param descriptor Pointer to the ArkUI_StyledString_Descriptor object.
 * @return The converted html.
 * @since 14
 */
const char* OH_ArkUI_ConvertToHtml(ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief Defines span style.
 * @since 24
 */
typedef struct OH_ArkUI_SpanStyle OH_ArkUI_SpanStyle;
 
/**
 * @brief Defines image attachment.
 * @since 24
 */
typedef struct OH_ArkUI_ImageAttachment OH_ArkUI_ImageAttachment;
 
/**
 * @brief Defines custom span.
 * @since 24
 */
typedef struct OH_ArkUI_CustomSpan OH_ArkUI_CustomSpan;
 
/**
 * @brief Enumerates the attribute type of the styled string.
 *
 * @since 24
 */
typedef enum {
    /**
     * The key of unspecified style.
     *
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_UNSPECIFIED = -1,

    /**
     * The key of <b>OH_ArkUI_TextStyle</b>.
     *
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_FONT = 0,

    /**
     * The key of <b>OH_ArkUI_DecorationStyle</b>.
     *
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_DECORATION = 1,

    /**
     * The key of <b>OH_ArkUI_BaselineOffsetStyle</b>.
     *
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_BASELINE_OFFSET = 2,

    /**
     * The key of <b>OH_ArkUI_LetterSpacingStyle</b>.
     *
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_LETTER_SPACING = 3,

    /**
     * The key of <b>OH_ArkUI_TextShadowStyle</b>.
     *
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_TEXT_SHADOW = 4,

    /**
     * The key of <b>OH_ArkUI_LineHeightStyle</b>.
     *
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_LINE_HEIGHT = 5,

    /**
     * The key of <b>OH_ArkUI_BackgroundColorStyle</b>.
     *
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_BACKGROUND_COLOR = 6,

    /**
     * The key of <b>OH_ArkUI_UrlStyle</b>.
     *
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_URL = 7,

    /**
     * The key of <b>OH_ArkUI_GestureStyle</b>.
     *
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_GESTURE = 100,

    /**
     * The key of <b>OH_ArkUI_ParagraphStyle</b>.
     *
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_PARAGRAPH_STYLE = 200,

    /**
     * The key of <b>OH_ArkUI_ImageAttachment</b>.
     *
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_IMAGE = 300,

    /**
     * The key of <b>OH_ArkUI_CustomSpan</b>.
     *
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_CUSTOM_SPAN = 400,

    /**
     * The key of <b>OH_ArkUI_UserDataSpan</b>.
     *
     * @since 24
     */
    OH_ARKUI_STYLEDSTRINGKEY_USER_DATA = 500
} OH_ArkUI_StyledStringKey;

/**
 * @brief Creates an <b>ArkUI_StyledString_Descriptor</b> object about text.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_StyledString_Descriptor_Destroy </b> to destroy it.
 * All input pointer parameters must be allocated, managed, and released by the caller.
 * @param value Pointer to the text content.
 * @param styles Data set about span style.
 * @param length The length of data set about span style.
 * @return The pointer to the <b>ArkUI_StyledString_Descriptor</b> object created. If the result is a null pointer,
 *         it may be params is invalid.
 * @since 24
 */
ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_CreateWithString(const char* value,
    const OH_ArkUI_SpanStyle** styles, int32_t length);

/**
 * @brief Creates an <b>ArkUI_StyledString_Descriptor</b> object about image.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_StyledString_Descriptor_Destroy </b> to destroy it.
 * All input pointer parameters must be allocated, managed, and released by the caller.
 * @param value Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @return The pointer to the <b>ArkUI_StyledString_Descriptor</b> object created. If the result is a null pointer,
 *         it may be params is invalid.
 * @since 24
 */
ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_CreateWithImageAttachment(
    const OH_ArkUI_ImageAttachment* value);

/**
 * @brief Creates an <b>ArkUI_StyledString_Descriptor</b> object about custom span.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_StyledString_Descriptor_Destroy </b> to destroy it.
 * All input pointer parameters must be allocated, managed, and released by the caller.
 * @param value Pointer to the <b>OH_ArkUI_CustomSpan</b> object.
 * @return The pointer to the <b>ArkUI_StyledString_Descriptor</b> object created. If the result is a null pointer,
 *         it may be params is invalid.
 * @since 24
 */
ArkUI_StyledString_Descriptor* OH_ArkUI_StyledString_Descriptor_CreateWithCustomSpan(const OH_ArkUI_CustomSpan* value);

/**
 * @brief Get the characters length of styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @param length The characters length.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_GetLength(const ArkUI_StyledString_Descriptor* descriptor,
    int32_t* length);

/**
 * @brief Get the literal content of the styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @param buffer The buffer to which text content writes to the memory,
 *               memory space needs to be allocated by the developer.
 * @param bufferSize The buffer size
 * @param writeLength Indicates the string length actually written to the buffer
 *                    when returning {@link ARKUI_ERROR_CODE_NO_ERROR}.
 *                    Indicates the minimum buffer size that can accommodate the target
 *                    when {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 *         Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_GetString(
    const ArkUI_StyledString_Descriptor* descriptor, char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Judge if two styled strings are equal.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param firstDescriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @param secondDescriptor Pointer to another <b>ArkUI_StyledString_Descriptor</b> object.
 * @param isEqual If two objects about the <b>ArkUI_StyledString_Descriptor</b> are equal.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_IsEqual(const ArkUI_StyledString_Descriptor* firstDescriptor,
    const ArkUI_StyledString_Descriptor* secondDescriptor, bool* isEqual);

/**
 * @brief Get the substring of the styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @param subDescriptor Pointer to the substring of <b>ArkUI_StyledString_Descriptor</b> object.
 * @param start The start position of the sub styled string.
 * @param length The characters length of the sub styled string.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_SubStyledString(const ArkUI_StyledString_Descriptor* descriptor,
    ArkUI_StyledString_Descriptor* subDescriptor, uint32_t start, uint32_t length);

/**
 * @brief Get span styles within a specified range of the styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @param start The start position of the range.
 * @param length The length of the range.
 * @param styledKey The specified style type.
 * @param styles The span styles.
 * @param stylesSize Buffer size for span styles.
 * @param writeLength The actual size of span styles in styled string.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 *         Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_GetStyles(const ArkUI_StyledString_Descriptor* descriptor,
    uint32_t start, uint32_t length, OH_ArkUI_StyledStringKey styledKey, OH_ArkUI_SpanStyle** styles,
    uint32_t stylesSize, uint32_t* writeLength);

/**
 * @brief Get styled string from the provided HTML string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @param html The html text will be converted to a StyledString.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_FromHtml(ArkUI_StyledString_Descriptor* descriptor, const char* html);

/**
 * @brief Replace the string of the specified range of styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @param start The start position of the replaced string.
 * @param length The characters length of the replaced string.
 * @param string Replaced string.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_ReplaceString(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, uint32_t length, const char* string);

/**
 * @brief Insert the string at the specified location in styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @param start The start position of the inserted string.
 * @param string Inserted string.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_InsertString(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, const char* string);

/**
 * @brief Remove the string of the specified range of styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @param start The start position of the removed string.
 * @param length The characters length of the removed string.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_RemoveString(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, uint32_t length);

/**
 * @brief Replace span style in the specified range of styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_ReplaceStyle(
    ArkUI_StyledString_Descriptor* descriptor, const OH_ArkUI_SpanStyle* spanStyle);

/**
 * @brief Add span style to the specified range string of styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_SetStyle(
    ArkUI_StyledString_Descriptor* descriptor, const OH_ArkUI_SpanStyle* spanStyle);

/**
 * @brief Delete the specified type span style from the specified range of styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @param start The start position in styled string.
 * @param length The length in styled string.
 * @param styledKey The key of the specified span style type.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_RemoveStyle(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, uint32_t length, OH_ArkUI_StyledStringKey styledKey);

/**
 * @brief Clear all span style in the styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_ClearStyles(ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief Replace the styled string of the specified range.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @param start The start position of the replaced styled string.
 * @param length The characters length of the replaced styled string.
 * @param other The other pointer to <b>ArkUI_StyledString_Descriptor</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_ReplaceStyledString(ArkUI_StyledString_Descriptor* descriptor,
    uint32_t start, uint32_t length, const ArkUI_StyledString_Descriptor* other);

/**
 * @brief Insert new styled string at the specified location of styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @param start The start position of the inserted styled string.
 * @param other The other pointer to <b>ArkUI_StyledString_Descriptor</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_InsertStyledString(
    ArkUI_StyledString_Descriptor* descriptor, uint32_t start, const ArkUI_StyledString_Descriptor* other);

/**
 * @brief Append new styled string at the end.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @param other The other pointer to <b>ArkUI_StyledString_Descriptor</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_AppendStyledString(
    ArkUI_StyledString_Descriptor* descriptor, const ArkUI_StyledString_Descriptor* other);

/**
 * @brief Invalidate custom span drawing in the styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter error occurs.
 *         Returns {@link ARKUI_ERROR_CODE_INVALID_STYLED_STRING} if the styled string is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_StyledString_Descriptor_InvalidateCustomSpan(const ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief Defines text style.
 * @since 24
 */
typedef struct OH_ArkUI_TextStyle OH_ArkUI_TextStyle;

/**
 * @brief Enumerates the superscript style type.
 *
 * @since 24
 */
typedef enum {
    /**
     * Normal font style.
     *
     * @since 24
     */
    OH_ARKUI_SUPERSCRIPTSTYLE_NORMAL = 0,

    /**
     * Superscript font style.
     *
     * @since 24
     */
    OH_ARKUI_SUPERSCRIPTSTYLE_SUPERSCRIPT,

    /**
     * Subscript font style.
     *
     * @since 24
     */
    OH_ARKUI_SUPERSCRIPTSTYLE_SUBSCRIPT
} OH_ArkUI_SuperscriptStyle;

/**
 * @brief Create an <b>OH_ArkUI_TextStyle</b> object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_TextStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @since 24
 */
OH_ArkUI_TextStyle* OH_ArkUI_TextStyle_Create();

/**
 * @brief Release the memory occupied by the <b>OH_ArkUI_TextStyle</b> object.
 *
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @since 24
 */
void OH_ArkUI_TextStyle_Destroy(OH_ArkUI_TextStyle* textStyle);

/**
 * @brief Set font color in the text style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @param fontColor Font color.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontColor(OH_ArkUI_TextStyle* textStyle, uint32_t fontColor);

/**
 * @brief Get font color in the text style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @param fontColor Font color.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontColor(const OH_ArkUI_TextStyle* textStyle, uint32_t* fontColor);

/**
 * @brief Set font family in the text style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @param fontFamily Font family.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontFamily(OH_ArkUI_TextStyle* textStyle, const char* fontFamily);

/**
 * @brief Get font family in the text style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @param buffer The buffer to which font family writes to the memory,
 *               memory space needs to be allocated by the developer.
 * @param bufferSize The buffer size
 * @param writeLength Indicates the string length actually written to the buffer
 *                    when returning {@link ARKUI_ERROR_CODE_NO_ERROR}.
 *                    Indicates the minimum buffer size that can accommodate the target
 *                    when {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *         Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontFamily(const OH_ArkUI_TextStyle* textStyle,
    char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Set font size in the text style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @param fontSize Font size.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontSize(OH_ArkUI_TextStyle* textStyle, float fontSize);

/**
 * @brief Get font size in the text style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @param fontSize Font size.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontSize(const OH_ArkUI_TextStyle* textStyle, float* fontSize);

/**
 * @brief Set Font weight in the text style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @param fontWeight Font weight.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontWeight(OH_ArkUI_TextStyle* textStyle, uint32_t fontWeight);

/**
 * @brief Get font weight in the text style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @param fontWeight Font weight.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontWeight(const OH_ArkUI_TextStyle* textStyle, uint32_t* fontWeight);

/**
 * @brief Set font style in the text style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @param fontStyle Font style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetFontStyle(OH_ArkUI_TextStyle* textStyle, ArkUI_FontStyle fontStyle);

/**
 * @brief Get font style in the text style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @param fontStyle Font style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetFontStyle(const OH_ArkUI_TextStyle* textStyle, ArkUI_FontStyle* fontStyle);

/**
 * @brief Set stroke width in the text style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @param strokeWidth Stroke width.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetStrokeWidth(OH_ArkUI_TextStyle* textStyle, float strokeWidth);

/**
 * @brief Get stroke width in the text style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @param strokeWidth Stroke width.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetStrokeWidth(const OH_ArkUI_TextStyle* textStyle, float* strokeWidth);

/**
 * @brief Set stroke color in the text style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @param strokeColor Stroke color.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetStrokeColor(OH_ArkUI_TextStyle* textStyle, uint32_t strokeColor);

/**
 * @brief Get stroke color in the text style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @param strokeColor Stroke color.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetStrokeColor(const OH_ArkUI_TextStyle* textStyle, uint32_t* strokeColor);

/**
 * @brief Set superscript style in the text style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @param superscript Superscript style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_SetSuperscript(OH_ArkUI_TextStyle* textStyle,
    OH_ArkUI_SuperscriptStyle superscript);

/**
 * @brief Get superscript style in the text style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @param superscript Superscript style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextStyle_GetSuperscript(const OH_ArkUI_TextStyle* textStyle,
    OH_ArkUI_SuperscriptStyle* superscript);

/**
 * @brief Create an <b>OH_ArkUI_SpanStyle</b> object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_SpanStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_SpanStyle</b> object.
 * @since 24
 */
OH_ArkUI_SpanStyle* OH_ArkUI_SpanStyle_Create();

/**
 * @brief Release the memory occupied by the <b>OH_ArkUI_SpanStyle</b> object.
 *
 * @param spanStyle Pointer to the <b>OH_ArkUI_SpanStyle</b> object.
 * @since 24
 */
void OH_ArkUI_SpanStyle_Destroy(OH_ArkUI_SpanStyle* spanStyle);

/**
 * @brief Get styled string key of span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the <b>OH_ArkUI_SpanStyle</b> object.
 * @param styledKey The styled string key of span style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetStyledKey(const OH_ArkUI_SpanStyle* spanStyle,
    OH_ArkUI_StyledStringKey* styledKey);

/**
 * @brief Set start position of span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the <b>OH_ArkUI_SpanStyle</b> object.
 * @param start The start position of span style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetStart(OH_ArkUI_SpanStyle* spanStyle, int32_t start);

/**
 * @brief Get start position of span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the <b>OH_ArkUI_SpanStyle</b> object.
 * @param start The start position of span style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetStart(const OH_ArkUI_SpanStyle* spanStyle, int32_t* start);

/**
 * @brief Set length of span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the <b>OH_ArkUI_SpanStyle</b> object.
 * @param length The length of span style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetLength(OH_ArkUI_SpanStyle* spanStyle, int32_t length);

/**
 * @brief Get length of span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the <b>OH_ArkUI_SpanStyle</b> object.
 * @param length The length of span style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetLength(const OH_ArkUI_SpanStyle* spanStyle, int32_t* length);

/**
 * @brief Set text style of span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the <b>OH_ArkUI_SpanStyle</b> object.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetTextStyle(OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_TextStyle* textStyle);

/**
 * @brief Get text style of span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the <b>OH_ArkUI_SpanStyle</b> object.
 * @param textStyle Pointer to the <b>OH_ArkUI_TextStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetTextStyle(const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_TextStyle* textStyle);

/**
 * @brief Defines paragraph style.
 * @since 24
 */
typedef struct OH_ArkUI_ParagraphStyle OH_ArkUI_ParagraphStyle;

/**
 * @brief Set the paragraph style of span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the <b>OH_ArkUI_SpanStyle</b> object.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetParagraphStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_ParagraphStyle* paragraphStyle);

/**
 * @brief Get paragraph style with span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to the <b>OH_ArkUI_SpanStyle</b> object.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetParagraphStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_ParagraphStyle* paragraphStyle);

/**
 * @brief Defines gesture style.
 * @since 24
 */
typedef struct OH_ArkUI_GestureStyle OH_ArkUI_GestureStyle;

/**
 * @brief Set the gesture style of span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param gestureStyle Pointer to the <b>OH_ArkUI_GestureStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetGestureStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_GestureStyle* gestureStyle);

/**
 * @brief Get gesture style with span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param gestureStyle Pointer to the <b>OH_ArkUI_GestureStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetGestureStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_GestureStyle* gestureStyle);

/**
 * @brief Defines text shadow style.
 * @since 24
 */
typedef struct OH_ArkUI_TextShadowStyle OH_ArkUI_TextShadowStyle;

/**
 * @brief Set text shadow style of span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param textShadowStyle Pointer to the <b>OH_ArkUI_TextShadowStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetTextShadowStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_TextShadowStyle* textShadowStyle);

/**
 * @brief Get text shadow style with span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param textShadowStyle Pointer to the <b>OH_ArkUI_TextShadowStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetTextShadowStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_TextShadowStyle* textShadowStyle);

/**
 * @brief Defines decoration style.
 * @since 24
 */
typedef struct OH_ArkUI_DecorationStyle OH_ArkUI_DecorationStyle;

/**
 * @brief Set decoration style of span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param decorationStyle Pointer to the <b>OH_ArkUI_DecorationStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetDecorationStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_DecorationStyle* decorationStyle);

/**
 * @brief Get decoration style with span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param decorationStyle Pointer to the <b>OH_ArkUI_DecorationStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetDecorationStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_DecorationStyle* decorationStyle);

/**
 * @brief Defines baseline offset style.
 * @since 24
 */
typedef struct OH_ArkUI_BaselineOffsetStyle OH_ArkUI_BaselineOffsetStyle;

/**
 * @brief Set baseline offset style of span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param baselineOffsetStyle Pointer to the <b>OH_ArkUI_BaselineOffsetStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetBaselineOffsetStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle);

/**
 * @brief Get baseline offset style with span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param baselineOffsetStyle Pointer to the <b>OH_ArkUI_BaselineOffsetStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetBaselineOffsetStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle);

/**
 * @brief Defines letter spacing style.
 * @since 24
 */
typedef struct OH_ArkUI_LetterSpacingStyle OH_ArkUI_LetterSpacingStyle;

/**
 * @brief Set letter spacing style of span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param letterSpacingStyle Pointer to the <b>OH_ArkUI_LetterSpacingStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetLetterSpacingStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_LetterSpacingStyle* letterSpacingStyle);

/**
 * @brief Get letter spacing style with span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param letterSpacingStyle Pointer to the <b>OH_ArkUI_LetterSpacingStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetLetterSpacingStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_LetterSpacingStyle* letterSpacingStyle);

/**
 * @brief Defines line height style.
 * @since 24
 */
typedef struct OH_ArkUI_LineHeightStyle OH_ArkUI_LineHeightStyle;

/**
 * @brief Set line height style of span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param lineHeightStyle Pointer to the <b>OH_ArkUI_LineHeightStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetLineHeightStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_LineHeightStyle* lineHeightStyle);

/**
 * @brief Get line height style with span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param lineHeightStyle Pointer to the <b>OH_ArkUI_LineHeightStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetLineHeightStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_LineHeightStyle* lineHeightStyle);

/**
 * @brief Defines url style.
 * @since 24
 */
typedef struct OH_ArkUI_UrlStyle OH_ArkUI_UrlStyle;

/**
 * @brief Set url style of span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param urlStyle Pointer to the <b>OH_ArkUI_UrlStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetUrlStyle(OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_UrlStyle* urlStyle);

/**
 * @brief Get url style with span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param urlStyle Pointer to the <b>OH_ArkUI_UrlStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetUrlStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_UrlStyle* urlStyle);

/**
 * @brief Defines background color style.
 * @since 24
 */
typedef struct OH_ArkUI_BackgroundColorStyle OH_ArkUI_BackgroundColorStyle;

/**
 * @brief Set background color style with span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param backgroundColorStyle Pointer to the <b>OH_ArkUI_BackgroundColorStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetBackgroundColorStyle(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_BackgroundColorStyle* backgroundColorStyle);

/**
 * @brief Get background color style with span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param backgroundColorStyle Pointer to the <b>OH_ArkUI_BackgroundColorStyle</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetBackgroundColorStyle(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_BackgroundColorStyle* backgroundColorStyle);

/**
 * @brief Defines user data span.
 * @since 24
 */
typedef struct OH_ArkUI_UserDataSpan OH_ArkUI_UserDataSpan;

/**
 * @brief Set user data style of span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param userDataSpan Pointer to the <b>OH_ArkUI_UserDataSpan</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetUserDataSpan(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_UserDataSpan* userDataSpan);

/**
 * @brief Get user data style with span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param userDataSpan Pointer to the <b>OH_ArkUI_UserDataSpan</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetUserDataSpan(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_UserDataSpan* userDataSpan);

/**
 * @brief Set custom span with span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param customSpan Pointer to the <b>OH_ArkUI_CustomSpan</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetCustomSpan(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_CustomSpan* customSpan);

/**
 * @brief Get custom span with span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param customSpan Pointer to the <b>OH_ArkUI_CustomSpan</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetCustomSpan(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_CustomSpan* customSpan);

/**
 * @brief Set image attachment with span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_SetImageAttachment(
    OH_ArkUI_SpanStyle* spanStyle, const OH_ArkUI_ImageAttachment* imageAttachment);

/**
 * @brief Get image attachment with span style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param spanStyle Pointer to an <b>OH_ArkUI_SpanStyle</b> object.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_SpanStyle_GetImageAttachment(
    const OH_ArkUI_SpanStyle* spanStyle, OH_ArkUI_ImageAttachment* imageAttachment);

/**
 * @brief Defines drawing info about leading margin.
 * @since 24
 */
typedef struct OH_ArkUI_LeadingMarginSpanDrawInfo OH_ArkUI_LeadingMarginSpanDrawInfo;

/**
 * @brief Create an <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_LeadingMarginSpanDrawInfo_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @since 24
 */
OH_ArkUI_LeadingMarginSpanDrawInfo* OH_ArkUI_LeadingMarginSpanDrawInfo_Create();

/**
 * @brief Release the memory occupied by the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 *
 * @param drawInfo Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @since 24
 */
void OH_ArkUI_LeadingMarginSpanDrawInfo_Destroy(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo);

/**
 * @brief Set the x offset of the line with leading margin span draw info.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @param x The x offset of the line.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetX(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, float x);

/**
 * @brief Get the x offset of the line with leading margin span draw info.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @param x The x offset of the line.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetX(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, float* x);

/**
 * @brief Set the top position of the line with leading margin span draw info.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @param top The top position of the line.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetTop(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, float top);

/**
 * @brief Get the top position of the line with leading margin span draw info.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @param top The top position of the line.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetTop(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float* top);

/**
 * @brief Set the bottom position of the line with leading margin span draw info.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @param bottom The bottom position of the line.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetBottom(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float bottom);

/**
 * @brief Get the bottom position of the line with leading margin span draw info.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @param bottom The bottom position of the line.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetBottom(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float* bottom);

/**
 * @brief Set the baseline offset of the line with leading margin span draw info.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @param baseline The baseline offset of the line.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetBaseline(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float baseline);

/**
 * @brief Get the baseline offset of the line with leading margin span draw info.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @param baseline The baseline offset of the line.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetBaseline(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    float* baseline);

/**
 * @brief Set the direction of text with leading margin span draw info.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @param direction The direction of text.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetTextDirection(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    ArkUI_TextDirection direction);

/**
 * @brief Get the direction of text with leading margin span draw info.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @param direction The direction of text.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetTextDirection(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    ArkUI_TextDirection* direction);

/**
 * @brief Set start index of the first character in the current line relative to the component text content.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @param start The start index.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetStart(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    uint32_t start);

/**
 * @brief Get start index of the first character in the current line relative to the component text content.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @param start The start index.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetStart(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    uint32_t* start);

/**
 * @brief Set end index of the last character in the current line relative to the component text content.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @param end The end index.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetEnd(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, uint32_t end);

/**
 * @brief Get end index of the last character in the current line relative to the component text content.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @param end The end index.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetEnd(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    uint32_t* end);

/**
 * @brief Set whether current line is first line of a paragraph.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @param first Whether current line is first line of a paragraph.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_SetFirst(OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo, bool first);

/**
 * @brief Get whether current line is first line of a paragraph.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param drawInfo Pointer to the <b>OH_ArkUI_LeadingMarginSpanDrawInfo</b> object.
 * @param first Whether current line is first line of a paragraph.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LeadingMarginSpanDrawInfo_GetFirst(const OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo,
    bool* first);

/**
 * @brief Create an <b>OH_ArkUI_ParagraphStyle</b> object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_ParagraphStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @since 24
 */
OH_ArkUI_ParagraphStyle* OH_ArkUI_ParagraphStyle_Create();

/**
 * @brief Release the memory occupied by the <b>OH_ArkUI_ParagraphStyle</b> object.
 *
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @since 24
 */
void OH_ArkUI_ParagraphStyle_Destroy(OH_ArkUI_ParagraphStyle* paragraphStyle);

/**
 * @brief Set text align of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param align The text align of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTextAlign(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextAlignment align);

/**
 * @brief Get text align of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param align The text align of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTextAlign(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextAlignment* align);

/**
 * @brief Set text indent of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param textIndent The text indent of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTextIndent(OH_ArkUI_ParagraphStyle* paragraphStyle, float textIndent);

/**
 * @brief Get text indent of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param textIndent The text indent of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTextIndent(const OH_ArkUI_ParagraphStyle* paragraphStyle, float* textIndent);

/**
 * @brief Set max lines of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param maxLines The max lines of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetMaxLines(OH_ArkUI_ParagraphStyle* paragraphStyle, int32_t maxLines);

/**
 * @brief Get max lines of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param maxLines The max lines of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetMaxLines(const OH_ArkUI_ParagraphStyle* paragraphStyle, int32_t* maxLines);

/**
 * @brief Set overflow of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param overflow The overflow of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetOverflow(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextOverflow overflow);

/**
 * @brief Get overflow of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param overflow The overflow of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetOverflow(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextOverflow* overflow);

/**
 * @brief Set word break of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param wordBreak The word break of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetWordBreak(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_WordBreak wordBreak);

/**
 * @brief Get word break of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param wordBreak The word break of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetWordBreak(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_WordBreak* wordBreak);

/**
 * @brief Set leading margin pixelmap of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param pixelmap The leading margin pixelmap of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetLeadingMarginPixelMap(OH_ArkUI_ParagraphStyle* paragraphStyle,
    struct OH_PixelmapNative* pixelmap);

/**
 * @brief Get leading margin pixelmap of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param pixelmap The leading margin pixelmap of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetLeadingMarginPixelMap(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    struct OH_PixelmapNative** pixelmap);

/**
 * @brief Set leading margin width of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param width The leading margin width of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetLeadingMarginWidth(OH_ArkUI_ParagraphStyle* paragraphStyle, uint32_t width);

/**
 * @brief Get leading margin width of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param width The leading margin width of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetLeadingMarginWidth(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t* width);

/**
 * @brief Set leading margin height of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param height The leading margin height of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetLeadingMarginHeight(OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t height);

/**
 * @brief Get leading margin height of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param height The leading margin height of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetLeadingMarginHeight(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t* height);

/**
 * @brief Set paragraph spacing of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param paragraphSpacing The paragraph spacing of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetParagraphSpacing(OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t paragraphSpacing);

/**
 * @brief Get paragraph spacing of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param paragraphSpacing The paragraph spacing of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetParagraphSpacing(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    uint32_t* paragraphSpacing);

/**
 * @brief Set text vertical align of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param verticalAlignment The text vertical align of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTextVerticalAlign(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextVerticalAlignment verticalAlignment);

/**
 * @brief Get text vertical align of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param verticalAlignment The text vertical align of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTextVerticalAlign(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextVerticalAlignment* verticalAlignment);

/**
 * @brief Set a callback function for drawing leading margin.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param onDraw The callback function for drawing leading margin.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_RegisterOnDrawLeadingMarginCallback(OH_ArkUI_ParagraphStyle* paragraphStyle,
    void(*onDraw)(ArkUI_DrawContext* context, OH_ArkUI_LeadingMarginSpanDrawInfo* drawInfo));

/**
 * @brief Register a callback function for obtaining the indentation distance of a text paragraph.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param leadingMargin The callback function for obtaining the indentation distance of a text paragraph.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_RegisterOnGetLeadingMarginCallback(OH_ArkUI_ParagraphStyle* paragraphStyle,
    float(*leadingMargin)());

/**
 * @brief Set text direction of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param textDirection The text direction of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_SetTextDirection(OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextDirection textDirection);

/**
 * @brief Get text direction of paragraph style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param paragraphStyle Pointer to the <b>OH_ArkUI_ParagraphStyle</b> object.
 * @param textDirection The text direction of paragraph style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ParagraphStyle_GetTextDirection(const OH_ArkUI_ParagraphStyle* paragraphStyle,
    ArkUI_TextDirection* textDirection);

/**
 * @brief Create an <b>OH_ArkUI_GestureStyle</b> object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_GestureStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_GestureStyle</b> object.
 * @since 24
 */
OH_ArkUI_GestureStyle* OH_ArkUI_GestureStyle_Create();

/**
 * @brief Release the memory occupied by the <b>OH_ArkUI_GestureStyle</b> object.
 *
 * @param gestureStyle Pointer to the <b>OH_ArkUI_GestureStyle</b> object.
 * @since 24
 */
void OH_ArkUI_GestureStyle_Destroy(OH_ArkUI_GestureStyle* gestureStyle);

/**
 * @brief Set click callback of gesture style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param gestureStyle Pointer to the <b>OH_ArkUI_GestureStyle</b> object.
 * @param onClick The callback of click event.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_GestureStyle_RegisterOnClickCallback(
    OH_ArkUI_GestureStyle* gestureStyle, void(*onClick)(ArkUI_NodeEvent*));

/**
 * @brief Set long press callback of gesture style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param gestureStyle Pointer to the <b>OH_ArkUI_GestureStyle</b> object.
 * @param onLongPress The callback of long press event.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_GestureStyle_RegisterOnLongPressCallback(
    OH_ArkUI_GestureStyle* gestureStyle, void(*onLongPress)(ArkUI_GestureEvent*));

/**
 * @brief Set touch callback of gesture style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param gestureStyle Pointer to the <b>OH_ArkUI_GestureStyle</b> object.
 * @param onTouch The callback of touch event.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_GestureStyle_RegisterOnTouchCallback(
    OH_ArkUI_GestureStyle* gestureStyle, void(*onTouch)(ArkUI_NodeEvent*));

/**
 * @brief Create an <b>OH_ArkUI_TextShadowStyle</b> object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_TextShadowStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_TextShadowStyle</b> object.
 * @since 24
 */
OH_ArkUI_TextShadowStyle* OH_ArkUI_TextShadowStyle_Create();

/**
 * @brief Release the memory occupied by the <b>OH_ArkUI_TextShadowStyle</b> object.
 *
 * @param textShadowStyle Pointer to the <b>OH_ArkUI_TextShadowStyle</b> object.
 * @since 24
 */
void OH_ArkUI_TextShadowStyle_Destroy(OH_ArkUI_TextShadowStyle* textShadowStyle);

/**
 * @brief Set text shadow options of text shadow style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textShadowStyle Pointer to the <b>OH_ArkUI_TextShadowStyle</b> object.
 * @param options The text shadow options.
 * @param length The length of text shadow options.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextShadowStyle_SetTextShadow(OH_ArkUI_TextShadowStyle* textShadowStyle,
    const OH_ArkUI_ShadowOptions** options, uint32_t length);

/**
 * @brief Get text shadow options of text shadow style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param textShadowStyle Pointer to the <b>OH_ArkUI_TextShadowStyle</b> object.
 * @param shadowOptions The text shadow options.
 * @param shadowOptionsSize The size of text shadow options.
 * @param writeLength The real size of text shadow options in text shadow style.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *         Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextShadowStyle_GetTextShadow(const OH_ArkUI_TextShadowStyle* textShadowStyle,
    OH_ArkUI_ShadowOptions** shadowOptions, uint32_t shadowOptionsSize, uint32_t* writeLength);

/**
 * @brief Create an <b>OH_ArkUI_DecorationStyle</b> object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_DecorationStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_DecorationStyle</b> object.
 * @since 24
 */
OH_ArkUI_DecorationStyle* OH_ArkUI_DecorationStyle_Create();

/**
 * @brief Release the memory occupied by the <b>OH_ArkUI_DecorationStyle</b> object.
 *
 * @param decorationStyle Pointer to the <b>OH_ArkUI_DecorationStyle</b> object.
 * @since 24
 */
void OH_ArkUI_DecorationStyle_Destroy(OH_ArkUI_DecorationStyle* decorationStyle);

/**
 * @brief Set the decoration type of decoration style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the <b>OH_ArkUI_DecorationStyle</b> object.
 * @param type The decoration type {@link ArkUI_TextDecorationType}.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetTextDecorationType(OH_ArkUI_DecorationStyle* decorationStyle,
    ArkUI_TextDecorationType type);

/**
 * @brief Get the decoration type of decoration style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the <b>OH_ArkUI_DecorationStyle</b> object.
 * @param type The decoration type {@link ArkUI_TextDecorationType}.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetTextDecorationType(const OH_ArkUI_DecorationStyle* decorationStyle,
    ArkUI_TextDecorationType* type);

/**
 * @brief Set the color of decoration line.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the <b>OH_ArkUI_DecorationStyle</b> object.
 * @param color Color of decoration line.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetColor(OH_ArkUI_DecorationStyle* decorationStyle, uint32_t color);

/**
 * @brief Get the color of decoration line.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the <b>OH_ArkUI_DecorationStyle</b> object.
 * @param color Color of decoration line.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetColor(const OH_ArkUI_DecorationStyle* decorationStyle, uint32_t* color);

/**
 * @brief Set the style of decoration line.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the <b>OH_ArkUI_DecorationStyle</b> object.
 * @param style Style of decoration line.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetTextDecorationStyle(OH_ArkUI_DecorationStyle* decorationStyle,
    ArkUI_TextDecorationStyle style);

/**
 * @brief Get the style of decoration line.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the <b>OH_ArkUI_DecorationStyle</b> object.
 * @param style Style of decoration line.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetTextDecorationStyle(const OH_ArkUI_DecorationStyle* decorationStyle,
    ArkUI_TextDecorationStyle* style);

/**
 * @brief Set the thickness scale of decoration line.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the <b>OH_ArkUI_DecorationStyle</b> object.
 * @param thicknessScale Thickness of decoration line.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetThicknessScale(OH_ArkUI_DecorationStyle* decorationStyle,
    float thicknessScale);

/**
 * @brief Get the thickness scale of decoration line.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the <b>OH_ArkUI_DecorationStyle</b> object.
 * @param thicknessScale Thickness of decoration line.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetThicknessScale(const OH_ArkUI_DecorationStyle* decorationStyle,
    float* thicknessScale);

/**
 * @brief Set the enable flag about multiple type in decoration line.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the <b>OH_ArkUI_DecorationStyle</b> object.
 * @param enableMultiType The enable flag about multiple type.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_SetEnableMultiType(
    OH_ArkUI_DecorationStyle* decorationStyle, bool enableMultiType);

/**
 * @brief Get the enable flag about multiple type in decoration line.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param decorationStyle Pointer to the <b>OH_ArkUI_DecorationStyle</b> object.
 * @param enableMultiType The enable flag about multiple type.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_DecorationStyle_GetEnableMultiType(
    const OH_ArkUI_DecorationStyle* decorationStyle, bool* enableMultiType);

/**
 * @brief Create an <b>OH_ArkUI_BaselineOffsetStyle</b> object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_BaselineOffsetStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_BaselineOffsetStyle</b> object.
 * @since 24
 */
OH_ArkUI_BaselineOffsetStyle* OH_ArkUI_BaselineOffsetStyle_Create();

/**
 * @brief Release the memory occupied by the <b>OH_ArkUI_BaselineOffsetStyle</b> object.
 *
 * @param baselineOffsetStyle Pointer to the <b>OH_ArkUI_BaselineOffsetStyle</b> object.
 * @since 24
 */
void OH_ArkUI_BaselineOffsetStyle_Destroy(OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle);

/**
 * @brief Set baseline offset of the baseline offset style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param baselineOffsetStyle Pointer to the <b>OH_ArkUI_BaselineOffsetStyle</b> object.
 * @param baselineOffset The baseline offset.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BaselineOffsetStyle_SetBaselineOffset(
    OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle, float baselineOffset);

/**
 * @brief Get baseline offset of the baseline offset style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param baselineOffsetStyle Pointer to the <b>OH_ArkUI_BaselineOffsetStyle</b> object.
 * @param baselineOffset The baseline offset.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BaselineOffsetStyle_GetBaselineOffset(
    const OH_ArkUI_BaselineOffsetStyle* baselineOffsetStyle, float* baselineOffset);

/**
 * @brief Create an <b>OH_ArkUI_LetterSpacingStyle</b> object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_LetterSpacingStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_LetterSpacingStyle</b> object.
 * @since 24
 */
OH_ArkUI_LetterSpacingStyle* OH_ArkUI_LetterSpacingStyle_Create();

/**
 * @brief Release the memory occupied by the <b>OH_ArkUI_LetterSpacingStyle</b> object.
 *
 * @param letterSpacingStyle Pointer to the <b>OH_ArkUI_LetterSpacingStyle</b> object.
 * @since 24
 */
void OH_ArkUI_LetterSpacingStyle_Destroy(OH_ArkUI_LetterSpacingStyle* letterSpacingStyle);

/**
 * @brief Set letter spacing of the letter spacing style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param letterSpacingStyle Pointer to the <b>OH_ArkUI_LetterSpacingStyle</b> object.
 * @param letterSpacing The letter spacing.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LetterSpacingStyle_SetLetterSpacing(
    OH_ArkUI_LetterSpacingStyle* letterSpacingStyle, float letterSpacing);

/**
 * @brief Get letter spacing of the letter spacing style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param letterSpacingStyle Pointer to the <b>OH_ArkUI_LetterSpacingStyle</b> object.
 * @param letterSpacing The letter spacing.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LetterSpacingStyle_GetLetterSpacing(
    const OH_ArkUI_LetterSpacingStyle* letterSpacingStyle, float* letterSpacing);

/**
 * @brief Create an <b>OH_ArkUI_LineHeightStyle</b> object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_LineHeightStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_LineHeightStyle</b> object.
 * @since 24
 */
OH_ArkUI_LineHeightStyle* OH_ArkUI_LineHeightStyle_Create();

/**
 * @brief Release the memory occupied by the <b>OH_ArkUI_LineHeightStyle</b> object.
 *
 * @param lineHeightStyle Pointer to the <b>OH_ArkUI_LineHeightStyle</b> object.
 * @since 24
 */
void OH_ArkUI_LineHeightStyle_Destroy(OH_ArkUI_LineHeightStyle* lineHeightStyle);

/**
 * @brief Set line height of the line height style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param lineHeightStyle Pointer to the <b>OH_ArkUI_LineHeightStyle</b> object.
 * @param lineHeight The line height.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LineHeightStyle_SetLineHeight(OH_ArkUI_LineHeightStyle* lineHeightStyle,
    float lineHeight);

/**
 * @brief Get line height of the line height style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param lineHeightStyle Pointer to the <b>OH_ArkUI_LineHeightStyle</b> object.
 * @param lineHeight The line height.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_LineHeightStyle_GetLineHeight(const OH_ArkUI_LineHeightStyle* lineHeightStyle,
    float* lineHeight);

/**
 * @brief Create a <b>OH_ArkUI_BackgroundColorStyle</b> object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_BackgroundColorStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_BackgroundColorStyle</b> object.
 * @since 24
 */
OH_ArkUI_BackgroundColorStyle* OH_ArkUI_BackgroundColorStyle_Create();

/**
 * @brief Release the memory occupied by the <b>OH_ArkUI_BackgroundColorStyle</b> object.
 *
 * @param style Pointer to the <b>OH_ArkUI_BackgroundColorStyle</b> object.
 * @since 24
 */
void OH_ArkUI_BackgroundColorStyle_Destroy(OH_ArkUI_BackgroundColorStyle* style);

/**
 * @brief Set color of the background color style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param style Pointer to the <b>OH_ArkUI_BackgroundColorStyle</b> object.
 * @param color The background color.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BackgroundColorStyle_SetColor(OH_ArkUI_BackgroundColorStyle* style, uint32_t color);

/**
 * @brief Get color of the background color style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param style Pointer to the <b>OH_ArkUI_BackgroundColorStyle</b> object.
 * @param color The background color.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BackgroundColorStyle_GetColor(const OH_ArkUI_BackgroundColorStyle* style, uint32_t* color);

/**
 * @brief Set radius of the background color style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param style Pointer to the <b>OH_ArkUI_BackgroundColorStyle</b> object.
 * @param topLeft The top left radius.
 * @param topRight The top right radius.
 * @param bottomLeft The bottom left radius.
 * @param bottomRight The bottom right radius.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BackgroundColorStyle_SetRadius(OH_ArkUI_BackgroundColorStyle* style, float topLeft,
    float topRight, float bottomLeft, float bottomRight);

/**
 * @brief Get radius of the background color style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param style Pointer to the <b>OH_ArkUI_BackgroundColorStyle</b> object.
 * @param topLeft The top left radius.
 * @param topRight The top right radius.
 * @param bottomLeft The bottom left radius.
 * @param bottomRight The bottom right radius.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_BackgroundColorStyle_GetRadius(const OH_ArkUI_BackgroundColorStyle* style, float* topLeft,
    float* topRight, float* bottomLeft, float* bottomRight);

/**
 * @brief Create an <b>OH_ArkUI_UrlStyle</b> object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_UrlStyle_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_UrlStyle</b> object.
 * @since 24
 */
OH_ArkUI_UrlStyle* OH_ArkUI_UrlStyle_Create();

/**
 * @brief Release the memory occupied by the ArkUI_UrlStyle object.
 *
 * @param style Pointer to the <b>OH_ArkUI_UrlStyle</b> object.
 * @since 24
 */
void OH_ArkUI_UrlStyle_Destroy(OH_ArkUI_UrlStyle* style);

/**
 * @brief Set url of the url style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param style Pointer to the <b>OH_ArkUI_UrlStyle</b> object.
 * @param url The url.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_UrlStyle_SetUrl(OH_ArkUI_UrlStyle* style, const char* url);

/**
 * @brief Get url of the url style.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param style Pointer to the <b>OH_ArkUI_UrlStyle</b> object.
 * @param buffer The buffer to which url content writes to the memory,
 *               memory space needs to be allocated by the developer.
 * @param bufferSize The buffer size.
 * @param writeLength Indicates the string length actually written to the buffer
 *                    when returning {@link ARKUI_ERROR_CODE_NO_ERROR}.
 *                    Indicates the minimum buffer size that can accommodate the target
 *                    when {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *         Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_UrlStyle_GetUrl(const OH_ArkUI_UrlStyle* style, char* buffer, int32_t bufferSize,
    int32_t* writeLength);

/**
 * @brief Create an <b>OH_ArkUI_UserDataSpan</b> object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_UserDataSpan_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_UserDataSpan</b> object.
 * @since 24
 */
OH_ArkUI_UserDataSpan* OH_ArkUI_UserDataSpan_Create();

/**
 * @brief Release the memory occupied by the <b>OH_ArkUI_UserDataSpan</b> object.
 *
 * @param userDataSpan Pointer to the <b>OH_ArkUI_UserDataSpan</b> object.
 * @since 24
 */
void OH_ArkUI_UserDataSpan_Destroy(OH_ArkUI_UserDataSpan* userDataSpan);

/**
 * @brief Set user data of the user data span.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param userDataSpan Pointer to the <b>OH_ArkUI_UserDataSpan</b> object.
 * @param userData The user data.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_UserDataSpan_SetUserData(OH_ArkUI_UserDataSpan* userDataSpan, void* userData);

/**
 * @brief Get user data of the user data span.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param userDataSpan Pointer to the <b>OH_ArkUI_UserDataSpan</b> object.
 * @param userData The user data.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_UserDataSpan_GetUserData(const OH_ArkUI_UserDataSpan* userDataSpan, void** userData);

/**
 * @brief Create an <b>OH_ArkUI_CustomSpan</b> object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_CustomSpan_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_CustomSpan</b> object.
 * @since 24
 */
OH_ArkUI_CustomSpan* OH_ArkUI_CustomSpan_Create();

/**
 * @brief Release the memory occupied by the <b>OH_ArkUI_CustomSpan</b> object.
 *
 * @param customSpan Pointer to the <b>OH_ArkUI_CustomSpan</b> object.
 * @since 24
 */
void OH_ArkUI_CustomSpan_Destroy(OH_ArkUI_CustomSpan* customSpan);

/**
 * @brief register measure callback of the custom span.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param customSpan Pointer to the <b>OH_ArkUI_CustomSpan</b> object.
 * @param onMeasure The callback function for measuring the size of custom span.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_CustomSpan_RegisterOnMeasureCallback(
    OH_ArkUI_CustomSpan* customSpan, ArkUI_CustomSpanMetrics*(*onMeasure)(float));

/**
 * @brief register draw callback of the custom span.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param customSpan Pointer to the <b>OH_ArkUI_CustomSpan</b> object.
 * @param onDraw The callback function for drawing the custom span.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_CustomSpan_RegisterOnDrawCallback(
    OH_ArkUI_CustomSpan* customSpan, void(*onDraw)(ArkUI_DrawContext*, ArkUI_CustomSpanDrawInfo*));

/**
 * @brief Create an <b>OH_ArkUI_ImageAttachment</b> object.
 *
 * @note When the object is no longer in use, invoke <b> OH_ArkUI_ImageAttachment_Destroy </b> to destroy it.
 * @return Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @since 24
 */
OH_ArkUI_ImageAttachment* OH_ArkUI_ImageAttachment_Create();

/**
 * @brief Release the memory occupied by the <b>OH_ArkUI_ImageAttachment</b> object.
 *
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @since 24
 */
void OH_ArkUI_ImageAttachment_Destroy(OH_ArkUI_ImageAttachment* imageAttachment);

/**
 * @brief Set pixelmap of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param pixelmap The pixelmap of the image attachment.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetPixelMap(OH_ArkUI_ImageAttachment* imageAttachment,
    struct OH_PixelmapNative* pixelmap);

/**
 * @brief Get pixelmap of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param pixelmap The pixelmap of the image attachment.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetPixelMap(const OH_ArkUI_ImageAttachment* imageAttachment,
    struct OH_PixelmapNative** pixelmap);

/**
 * @brief Set string about image src in the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param resource The string about image src in the image attachment.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetResource(OH_ArkUI_ImageAttachment* imageAttachment, const char* resource);

/**
 * @brief Get string about image src in the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param buffer The buffer to which string about image src writes to the memory,
 *               memory space needs to be allocated by the developer.
 * @param bufferSize The buffer size
 * @param writeLength Indicates the string length actually written to the buffer
 *                    when returning {@link ARKUI_ERROR_CODE_NO_ERROR}.
 *                    Indicates the minimum buffer size that can accommodate the target
 *                    when {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} is returned.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *         Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetResource(const OH_ArkUI_ImageAttachment* imageAttachment,
    char* buffer, int32_t bufferSize, int32_t* writeLength);

/**
 * @brief Set image width of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param width The image width of the image attachment.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetSizeWidth(OH_ArkUI_ImageAttachment* imageAttachment, float width);

/**
 * @brief Get image width of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param width The image width of the image attachment.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetSizeWidth(const OH_ArkUI_ImageAttachment* imageAttachment, float* width);

/**
 * @brief Set image height of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param height The image height of the image attachment.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetSizeHeight(OH_ArkUI_ImageAttachment* imageAttachment, float height);

/**
 * @brief Get image height of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param height The image height of the image attachment.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetSizeHeight(const OH_ArkUI_ImageAttachment* imageAttachment, float* height);

/**
 * @brief Set image alignment of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param verticalAlign The image alignment of the image attachment.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetVerticalAlign(
    OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_ImageSpanAlignment verticalAlign);

/**
 * @brief Get image alignment of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param verticalAlign The image alignment of the image attachment.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetVerticalAlign(const OH_ArkUI_ImageAttachment* imageAttachment,
    ArkUI_ImageSpanAlignment* verticalAlign);

/**
 * @brief Set image object fit of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param objectFit The image object fit of the image attachment.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetObjectFit(
    OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_ObjectFit objectFit);

/**
 * @brief Get image object fit of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param objectFit The image object fit of the image attachment.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetObjectFit(
    const OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_ObjectFit* objectFit);

/**
 * @brief Set image margin of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param margin The image margin of the image attachment.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetMargin(OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_Margin margin);

/**
 * @brief Get image margin of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param margin The image margin of the image attachment.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetMargin(const OH_ArkUI_ImageAttachment* imageAttachment,
    ArkUI_Margin* margin);

/**
 * @brief Set image padding of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param padding The image padding of the image attachment.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetPadding(OH_ArkUI_ImageAttachment* imageAttachment, ArkUI_Margin padding);

/**
 * @brief Get image padding of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param padding The image padding of the image attachment.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetPadding(const OH_ArkUI_ImageAttachment* imageAttachment,
    ArkUI_Margin* padding);

/**
 * @brief Set image border radius of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param topLeft The top left radius.
 * @param topRight The top right radius.
 * @param bottomLeft The bottom left radius.
 * @param bottomRight The bottom right radius.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetBorderRadiuses(OH_ArkUI_ImageAttachment* imageAttachment,
    float topLeft, float topRight, float bottomLeft, float bottomRight);

/**
 * @brief Get image border radius of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param topLeft The top left radius.
 * @param topRight The top right radius.
 * @param bottomLeft The bottom left radius.
 * @param bottomRight The bottom right radius.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetBorderRadiuses(const OH_ArkUI_ImageAttachment* imageAttachment,
    float* topLeft, float* topRight, float* bottomLeft, float* bottomRight);

/**
 * @brief Set image colorFilter of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param colorFilter The image colorFilter.
 * @param size The size of colorFilter.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetColorFilter(
    OH_ArkUI_ImageAttachment* imageAttachment, const float* colorFilter, uint32_t size);

/**
 * @brief Get image colorFilter of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param colorFilter The image colorFilter.
 * @param colorFilterSize The size of colorFilter.
 * @param writeLength the real size of colorFilter in the image attachment.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *         Returns {@link ARKUI_ERROR_CODE_BUFFER_SIZE_ERROR} If the buffer size is less than the minimum buffer size.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetColorFilter(const OH_ArkUI_ImageAttachment* imageAttachment,
    float** colorFilter, uint32_t colorFilterSize, uint32_t* writeLength);

/**
 * @brief Set image colorFilter of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param drawingColorFilter The image colorFilter.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetDrawingColorFilter(
    OH_ArkUI_ImageAttachment* imageAttachment, const OH_Drawing_ColorFilter* drawingColorFilter);

/**
 * @brief Get image colorFilter of the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param drawingColorFilter The image colorFilter.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetDrawingColorFilter(
    const OH_ArkUI_ImageAttachment* imageAttachment, OH_Drawing_ColorFilter* drawingColorFilter);

/**
 * @brief Set the flag about image sync load in the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param syncLoad The flag about image sync load.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetSyncLoad(OH_ArkUI_ImageAttachment* imageAttachment, bool syncLoad);

/**
 * @brief Get the flag about image sync load in the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param syncLoad The flag about image sync load.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetSyncLoad(const OH_ArkUI_ImageAttachment* imageAttachment, bool* syncLoad);

/**
 * @brief Set the flag about image support svg in the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param supportSvg The flag about image support svg.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_SetSupportSvg(OH_ArkUI_ImageAttachment* imageAttachment, bool supportSvg);

/**
 * @brief Get the flag about image support svg in the image attachment.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param imageAttachment Pointer to the <b>OH_ArkUI_ImageAttachment</b> object.
 * @param supportSvg The flag about image support svg.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_ImageAttachment_GetSupportSvg(const OH_ArkUI_ImageAttachment* imageAttachment,
    bool* supportSvg);

/**
 * @brief Obtains the range of content that will be replaced.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param event Pointer to an <b>OH_ArkUI_TextEditorChangeEvent</b> object.
 * @param start Range start offset.
 * @param end Range end offset.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function params is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorChangeEvent_GetRangeBefore(const OH_ArkUI_TextEditorChangeEvent* event,
    uint32_t* start, uint32_t* end);

/**
 * @brief Obtains the styled string used for replacement.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param event Pointer to an <b>OH_ArkUI_TextEditorChangeEvent</b> object.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function params is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorChangeEvent_GetReplacementStyledString(
    const OH_ArkUI_TextEditorChangeEvent* event, ArkUI_StyledString_Descriptor* descriptor);

/**
 * @brief Obtains the preview styled string.
 *
 * @note All input pointer parameters must be allocated, managed, and released by the caller.
 * @param event Pointer to an <b>OH_ArkUI_TextEditorChangeEvent</b> object.
 * @param descriptor Pointer to an <b>ArkUI_StyledString_Descriptor</b> object.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} Function params is invalid.
 * @since 24
 */
ArkUI_ErrorCode OH_ArkUI_TextEditorChangeEvent_GetPreviewStyledString(
    const OH_ArkUI_TextEditorChangeEvent* event, ArkUI_StyledString_Descriptor* descriptor);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_STYLED_STRING_DESCRIPTOR_H