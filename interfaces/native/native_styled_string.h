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
 * @file styled_string.h
 *
 * @brief 提供ArkUI在Native侧的属性字符串能力。
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 12
 */

#ifndef ARKUI_NATIVE_STYLED_STRING_H
#define ARKUI_NATIVE_STYLED_STRING_H

// should be careful this path is not same in SDK.
#include "drawing_text_typography.h"
#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 定义文本组件支持的格式化字符串数据对象。
 *
 * @since 12
 */
typedef struct ArkUI_StyledString ArkUI_StyledString;

/**
 * @brief 创建指向ArkUI_StyledString对象的指针。
 *
 * @param style 指向OH_Drawing_TypographyStyle的指针，由{@link OH_Drawing_CreateTypographyStyle}获取。
 * @param collection 指向OH_Drawing_FontCollection的指针，由{@link OH_Drawing_CreateFontCollection}获取。
 * @return 创建指向ArkUI_StyledString对象的指针，异常返回空指针。
 * @since 12
 */
ArkUI_StyledString* OH_ArkUI_StyledString_Create(
    OH_Drawing_TypographyStyle* style, OH_Drawing_FontCollection* collection);

/**
 * @brief 释放被ArkUI_StyledString对象占据的内存。
 *
 * @param handle 指向ArkUI_StyledString对象的指针。
 * @since 12
 */
void OH_ArkUI_StyledString_Destroy(ArkUI_StyledString* handle);

/**
 * @brief 将新的排版风格设置到当前格式化字符串样式栈顶。
 *
 * @param handle 指向ArkUI_StyledString对象的指针。
 * @param style 指向OH_Drawing_TextStyle对象的指针。
 * @since 12
 */
void OH_ArkUI_StyledString_PushTextStyle(ArkUI_StyledString* handle, OH_Drawing_TextStyle* style);

/**
 * @brief 基于当前格式化字符串样式设置对应的文本内容。
 *
 * @param handle 指向ArkUI_StyledString对象的指针。
 * @param content 指向文本内容的指针。
 * @since 12
 */
void OH_ArkUI_StyledString_AddText(ArkUI_StyledString* handle, const char* content);

/**
 * @brief 将当前格式化字符串对象中栈顶样式出栈。
 *
 * @param handle 指向ArkUI_StyledString对象的指针。
 * @since 12
 */
void OH_ArkUI_StyledString_PopTextStyle(ArkUI_StyledString* handle);

/**
 * @brief 基于格式字符串对象创建指向OH_Drawing_Typography对象的指针，用于提前进行文本测算排版。
 *
 * @param handle 指向ArkUI_StyledString对象的指针。
 * @return 指向OH_Drawing_Typography对象的指针。
 * @since 12
 */
OH_Drawing_Typography* OH_ArkUI_StyledString_CreateTypography(ArkUI_StyledString* handle);

/**
 * @brief 设置占位符。
 *
 * @param handle 指向ArkUI_StyledString对象的指针。
 * @param placeholder 指向OH_Drawing_PlaceholderSpan对象的指针。
 * @since 12
 */
void OH_ArkUI_StyledString_AddPlaceholder(ArkUI_StyledString* handle, OH_Drawing_PlaceholderSpan* placeholder);

/**
 * @brief Defines the layout manager of text.
 *
 * @since 23
 */
typedef struct ArkUI_TextLayoutManager ArkUI_TextLayoutManager;

/**
 * @brief Dispose an object of the text layout manager.
 *
 * @param layoutManager Pointer to the ArkUI_TextLayoutManager object to be disposed.
 * @since 23
 */
void OH_ArkUI_TextLayoutManager_Dispose(ArkUI_TextLayoutManager* layoutManager);

/**
 * @brief Gets the line count.
 *
 * @param layoutManager Indicates the pointer to an <b>ArkUI_TextLayoutManager</b> object.
 * @param outLineCount Returns the line count.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetLineCount(ArkUI_TextLayoutManager* layoutManager, int32_t* outLineCount);

/**
 * @brief Gets the rects for range.
 *
 * @param layoutManager Indicates the pointer to an <b>ArkUI_TextLayoutManager</b> object.
 * @param start Indicates the start of range to set.
 * @param end Indicates the end of range to set.
 * @param widthStyle Indicates the width style to set.
 *     For details, see the enum <b>OH_Drawing_RectWidthStyle</b>.
 * @param heightStyle Indicates the height style to set.
 *     For details, see the enum <b>OH_Drawing_RectHeightStyle</b>.
 * @param outTextBoxes Returns the array of rects for range.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetRectsForRange(ArkUI_TextLayoutManager* layoutManager,
    int32_t start, int32_t end, OH_Drawing_RectWidthStyle widthStyle, OH_Drawing_RectHeightStyle heightStyle,
    OH_Drawing_TextBox** outTextBoxes);

/**
 * @brief Gets the glyph position at coordinate.
 *
 * @param layoutManager Indicates the pointer to an <b>ArkUI_TextLayoutManager</b> object.
 * @param dx Indicates the positionX of typography to set.
 * @param dy Indicates the positionY of typography to set.
 * @param outPos Returns the glyph position at coordinate.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetGlyphPositionAtCoordinate(
    ArkUI_TextLayoutManager* layoutManager, double dx, double dy, OH_Drawing_PositionAndAffinity** outPos);

/**
 * @brief Get line metrics information.
 *
 * @param layoutManager Indicates the pointer to a typography object <b>ArkUI_TextLayoutManager</b>.
 * @param lineNumber Indicates the number of line.
 * @param outMetrics Indicates the pointer to a line metrics object <b>OH_Drawing_LineMetrics</b>.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 23
 */
ArkUI_ErrorCode OH_ArkUI_TextLayoutManager_GetLineMetrics(ArkUI_TextLayoutManager* layoutManager,
    int32_t lineNumber, OH_Drawing_LineMetrics* outMetrics);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_STYLED_STRING_H