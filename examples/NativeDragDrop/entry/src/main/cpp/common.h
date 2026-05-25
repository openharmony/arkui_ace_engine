/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef DRAGANDDROP_COMMON_H
#define DRAGANDDROP_COMMON_H

#include "container.h"
#include <arkui/drag_and_drop.h>
#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <database/udmf/udmf.h>
#include <hilog/log.h>
#include <sstream>

#define BORDER_WIDTH_1 1.0
#define DEFAULT_RADIUS 10.0
#define DEFAULT_OPACITY 0.1

#define SIZE_20 20
#define SIZE_50 50
#define SIZE_80 80
#define SIZE_120 120
#define SIZE_140 140
#define SIZE_170 170
#define SIZE_200 200
#define SIZE_240 240
#define SIZE_300 300
#define BLANK_5 5.0
#define BLANK_10 10.0
#define BLANK_20 20.0

#define DRAG_COUNT 10
#define DEFAULT_TEXT_FONT_SIZE 12
#define TEXT_FONT_SIZE_15 15
#define TEXT_FONT_SIZE_20 20

#define POINT_POS 200

#define MAX_LENGTH 128

namespace NativeXComponentSample {

ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;
ArkUI_ContextHandle context;
enum ArkUIModifierKeyName {
    ARKUI_MODIFIER_KEY_CTRL = 1 << 0,  // Ctrl 键
    ARKUI_MODIFIER_KEY_SHIFT = 1 << 1, // Shift 键
    ARKUI_MODIFIER_KEY_ALT = 1 << 2,   // Alt 键
    ARKUI_MODIFIER_KEY_FN = 1 << 3     // Fn 键（如适用）
};
char key[UDMF_KEY_BUFFER_LEN];
int32_t g_requestIdentify = 0;
ArkUI_DragAction *action;
std::stringstream g_ss;

void GetDragResult(ArkUI_DragEvent* dragEvent);
void GetDragMoveInfos(ArkUI_DragEvent* dragEvent);

void SetWidthPercent(ArkUI_NodeHandle &node, float width = 1)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue widthValue[] = {width};
    ArkUI_AttributeItem widthItem = {widthValue, 1};
    nodeAPI->setAttribute(node, NODE_WIDTH_PERCENT, &widthItem);
}

void SetHeightPercent(ArkUI_NodeHandle &node, float height = 1)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue heightValue[] = {height};
    ArkUI_AttributeItem heightItem = {heightValue, 1};
    nodeAPI->setAttribute(node, NODE_HEIGHT_PERCENT, &heightItem);
}

// [Start set_common]
#define DEFAULT_WIDTH 200.0
// 设置节点宽度
void SetWidth(ArkUI_NodeHandle &node, float width = DEFAULT_WIDTH)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue widthValue[] = {width};
    ArkUI_AttributeItem widthItem = {widthValue, 1};
    nodeAPI->setAttribute(node, NODE_WIDTH, &widthItem);
}

#define DEFAULT_HEIGHT 200.0
// 设置节点高度
void SetHeight(ArkUI_NodeHandle &node, float height = DEFAULT_HEIGHT)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue heightValue[] = {height};
    ArkUI_AttributeItem heightItem = {heightValue, 1};
    nodeAPI->setAttribute(node, NODE_HEIGHT, &heightItem);
}

#define DEFAULT_BG_COLOR 0xFFFFFFFF
// 设置节点背景颜色
void SetBackgroundColor(ArkUI_NodeHandle &node, uint32_t color = DEFAULT_BG_COLOR)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue colorValue[] = {{.u32 = color}};
    ArkUI_AttributeItem colorItem = {colorValue, 1};
    nodeAPI->setAttribute(node, NODE_BACKGROUND_COLOR, &colorItem);
}

#define DEFAULT_MARGIN 5.0
// 设置节点外边距
void SetMargin(ArkUI_NodeHandle &node, float margin = DEFAULT_MARGIN)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue marginValue[] = {margin};
    ArkUI_AttributeItem marginItem = {marginValue, 1};
    nodeAPI->setAttribute(node, NODE_MARGIN, &marginItem);
}

// 设置Button节点标签
void SetButtonLabel(ArkUI_NodeHandle &node, const char *label)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_AttributeItem NODE_Button_SRC_Item = {.string = label};
    nodeAPI->setAttribute(node, NODE_BUTTON_LABEL, &NODE_Button_SRC_Item);
}

// 设置节点标识符
void SetId(ArkUI_NodeHandle &node, const char *id)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_AttributeItem idItem = {.string = id};
    nodeAPI->setAttribute(node, NODE_ID, &idItem);
}

#define DEFAULT_BORDER_WIDTH 0.0
// 设置节点边框宽度
void SetBorderWidth(ArkUI_NodeHandle &node, float width = DEFAULT_BORDER_WIDTH)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue borderWidthValue[] = {width};
    ArkUI_AttributeItem borderWidthItem = {borderWidthValue, 1};
    nodeAPI->setAttribute(node, NODE_BORDER_WIDTH, &borderWidthItem);
}

#define DEFAULT_BORDER_COLOR 0xFF000000
// 设置节点边框颜色
void SetBorderColor(ArkUI_NodeHandle &node, uint32_t color = DEFAULT_BORDER_COLOR)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue borderColorValue[] = {{.u32 = color}};
    ArkUI_AttributeItem borderColorItem = {borderColorValue, 1};
    nodeAPI->setAttribute(node, NODE_BORDER_COLOR, &borderColorItem);
}

// 设置节点常用属性（宽高、背景色、外边距、边框样式）
void SetCommonAttribute(ArkUI_NodeHandle &node, float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT,
                        unsigned int color = DEFAULT_BG_COLOR, float margin = DEFAULT_MARGIN)
{
    SetWidth(node, width);
    SetHeight(node, height);
    SetBackgroundColor(node, color);
    SetMargin(node, margin);
    SetBorderWidth(node, DEFAULT_BORDER_WIDTH);
    SetBorderColor(node);
}
// [End set_common]

void SetPadding(ArkUI_NodeHandle &node, float padding)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue paddingValue[] = {padding};
    ArkUI_AttributeItem paddingItem = {paddingValue, 1};
    nodeAPI->setAttribute(node, NODE_PADDING, &paddingItem);
}

void SetBorderStyle(ArkUI_NodeHandle &node, int32_t style = ARKUI_BORDER_STYLE_DASHED, float radius = 10.0)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue borderStyleValue[] = {{.i32 = style}};
    ArkUI_AttributeItem borderStyleItem = {borderStyleValue, 1};
    nodeAPI->setAttribute(node, NODE_BORDER_STYLE, &borderStyleItem);

    ArkUI_NumberValue borderRadiusValue[] = {{.f32 = radius}};
    ArkUI_AttributeItem borderRadiusItem = {borderRadiusValue, 1};
    nodeAPI->setAttribute(node, NODE_BORDER_RADIUS, &borderRadiusItem);
}

void SetText(ArkUI_NodeHandle &node, const char *str, float size = DEFAULT_TEXT_FONT_SIZE)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_AttributeItem textValueItem = {.string = str};
    ArkUI_NumberValue fontSize[] = {size};
    ArkUI_AttributeItem fontItem = {fontSize, 1};
    nodeAPI->setAttribute(node, NODE_TEXT_CONTENT, &textValueItem);
    nodeAPI->setAttribute(node, NODE_TEXT_FONT, &fontItem);
}

// [Start set_imageSrc]
void SetImageSrc(ArkUI_NodeHandle &node, const char *src)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_AttributeItem imageSrcItem = {.string = src};
    nodeAPI->setAttribute(node, NODE_IMAGE_SRC, &imageSrcItem);
}
// [End set_imageSrc]

void SetTextAttribute(ArkUI_NodeHandle &node, const char *str, float size = DEFAULT_TEXT_FONT_SIZE,
                      float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT)
{
    SetCommonAttribute(node, width, height, 0);
    SetText(node, str, size);
}

void SetColumnJustifyContent(ArkUI_NodeHandle &node, int32_t alignment)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue justifyValue[] = {{.i32 = alignment}};
    ArkUI_AttributeItem justifyItem = {justifyValue, 1};
    nodeAPI->setAttribute(node, NODE_COLUMN_JUSTIFY_CONTENT, &justifyItem);
}

void SetColumnAlignItem(ArkUI_NodeHandle &node, int32_t alignment)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue alignValue[] = {{.i32 = alignment}};
    ArkUI_AttributeItem alignItem = {alignValue, 1};
    nodeAPI->setAttribute(node, NODE_COLUMN_ALIGN_ITEMS, &alignItem);
}

void SetRowJustifyContent(ArkUI_NodeHandle &node, int32_t alignment)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue justifyValue[] = {{.i32 = alignment}};
    ArkUI_AttributeItem justifyItem = {justifyValue, 1};
    nodeAPI->setAttribute(node, NODE_ROW_JUSTIFY_CONTENT, &justifyItem);
}

void SetRowAlignItem(ArkUI_NodeHandle &node, int32_t alignment)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue alignValue[] = {{.i32 = alignment}};
    ArkUI_AttributeItem alignItem = {alignValue, 1};
    nodeAPI->setAttribute(node, NODE_ROW_ALIGN_ITEMS, &alignItem);
}

// [Start prepare_dragAction]
void SetPixelMap(std::vector<OH_PixelmapNative *> &pixelVector)
{
    uint8_t data[960000];
    size_t dataSize = 960000;
    for (int i = 0; i < dataSize; i++) {
        data[i] = i + 1;
    }
    // 创建参数结构体实例，并设置参数
    OH_Pixelmap_InitializationOptions *createOpts;
    OH_PixelmapInitializationOptions_Create(&createOpts);
    OH_PixelmapInitializationOptions_SetWidth(createOpts, 200U);
    OH_PixelmapInitializationOptions_SetHeight(createOpts, 300U);
    OH_PixelmapInitializationOptions_SetPixelFormat(createOpts, PIXEL_FORMAT_BGRA_8888);
    OH_PixelmapInitializationOptions_SetAlphaType(createOpts, PIXELMAP_ALPHA_TYPE_UNKNOWN);
    // 创建Pixelmap实例
    OH_PixelmapNative *pixelmap = nullptr;
    OH_PixelmapNative_CreatePixelmap(data, dataSize, createOpts, &pixelmap);
    OH_PixelmapNative_Flip(pixelmap, true, true);
    pixelVector.push_back(pixelmap);
    int returnValue = OH_ArkUI_DragAction_SetPixelMaps(action, pixelVector.data(), pixelVector.size());
    OH_LOG_Print(LOG_APP, LOG_INFO, 0xFF00U, "dragTest",
        "OH_ArkUI_DragAction_SetPixelMaps returnValue = %{public}d", returnValue);
}

void SetDragPreviewOption()
{
    auto *previewOptions = OH_ArkUI_CreateDragPreviewOption();
    OH_ArkUI_DragPreviewOption_SetScaleMode(previewOptions,
        ArkUI_DragPreviewScaleMode::ARKUI_DRAG_PREVIEW_SCALE_DISABLED);
    OH_ArkUI_DragPreviewOption_SetDefaultShadowEnabled(previewOptions, true);
    OH_ArkUI_DragPreviewOption_SetDefaultRadiusEnabled(previewOptions, true);
    int returnValue = OH_ArkUI_DragAction_SetDragPreviewOption(action, previewOptions);
    OH_ArkUI_DragPreviewOption_Dispose(previewOptions);
    OH_LOG_Print(LOG_APP, LOG_INFO, 0xFF00U, "dragTest",
        "OH_ArkUI_DragAction_SetDragPreviewOption returnValue = %{public}d", returnValue);
}

void PrintDragActionInfos()
{
    // 设置pointerId
    int returnValue = OH_ArkUI_DragAction_SetPointerId(action, 0);
    OH_LOG_Print(LOG_APP, LOG_INFO, 0xFF00U, "dragTest",
        "OH_ArkUI_DragAction_SetPointerId returnValue = %{public}d", returnValue);
    // 设置touchPoint
    returnValue = OH_ArkUI_DragAction_SetTouchPointX(action, 200.0f);
    OH_LOG_Print(LOG_APP, LOG_INFO, 0xFF00U, "dragTest",
        "OH_ArkUI_DragAction_SetTouchPointX returnValue = %{public}d", returnValue);
    returnValue = OH_ArkUI_DragAction_SetTouchPointY(action, 200.0f);
    OH_LOG_Print(LOG_APP, LOG_INFO, 0xFF00U, "dragTest",
        "OH_ArkUI_DragAction_SetTouchPointY returnValue = %{public}d", returnValue);
}
// [End prepare_dragAction]

} // namespace NativeXComponentSample

#endif // DRAGANDDROP_COMMON_H