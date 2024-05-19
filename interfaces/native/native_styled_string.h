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

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_STYLED_STRING_H