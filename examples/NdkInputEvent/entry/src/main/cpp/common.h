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

#include <arkui/native_node.h>
#include <arkui/native_type.h>

const unsigned int LOG_PRINT_DOMAIN = 0xFF00;

// 默认宽度
#define DEFAULT_WIDTH 200.0
// 默认高度
#define DEFAULT_HEIGHT 200.0
// 默认背景颜色（白色）
#define DEFAULT_BG_COLOR 0xFFFFFFFF
// 默认边框宽度
#define DEFAULT_BORDER_WIDTH 0.0
// 边框宽度1
#define BORDER_WIDTH_1 1.0
// 默认边距
#define DEFAULT_MARGIN 5.0
// 默认边框颜色（黑色）
#define DEFAULT_BORDER_COLOR 0xFF000000
// 默认圆角半径
#define DEFAULT_RADIUS 10.0

// 小按钮宽度比例
#define BUTTON_WIDTH_S 0.3
// 大按钮宽度比例
#define BUTTON_WIDTH_L 0.55

// 尺寸50
#define SIZE_50 50
// 尺寸80
#define SIZE_80 80
// 尺寸100
#define SIZE_100 100
// 尺寸300
#define SIZE_300 300
// 空白间距10
#define BLANK_10 10.0

// 默认文本字体大小
#define DEFAULT_TEXT_FONT_SIZE 12
// 文本字体大小15
#define TEXT_FONT_SIZE_15 15
// 文本字体大小20
#define TEXT_FONT_SIZE_20 20

// 按钮长度
#define BUTTON_LENGTH 10
// 最大长度
#define MAX_LENGTH 128

namespace NativeXComponentSample {

// ArkUI节点API指针
ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;
// ArkUI上下文句柄
ArkUI_ContextHandle context;

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

// 设置节点宽度百分比
void SetWidthPercent(ArkUI_NodeHandle &node, float width = 1)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue widthValue[] = {width};
    ArkUI_AttributeItem widthItem = {widthValue, 1};
    nodeAPI->setAttribute(node, NODE_WIDTH_PERCENT, &widthItem);
}

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

// 设置节点高度百分比
void SetHeightPercent(ArkUI_NodeHandle &node, float height = 1)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue heightValue[] = {height};
    ArkUI_AttributeItem heightItem = {heightValue, 1};
    nodeAPI->setAttribute(node, NODE_HEIGHT_PERCENT, &heightItem);
}

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

// 设置节点边距
void SetMargin(ArkUI_NodeHandle &node, float margin = DEFAULT_MARGIN)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue marginValue[] = {margin};
    ArkUI_AttributeItem marginItem = {marginValue, 1};
    nodeAPI->setAttribute(node, NODE_MARGIN, &marginItem);
}

// 设置节点内边距
void SetPadding(ArkUI_NodeHandle &node, float padding)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue paddingValue[] = {padding};
    ArkUI_AttributeItem paddingItem = {paddingValue, 1};
    nodeAPI->setAttribute(node, NODE_PADDING, &paddingItem);
}

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

// 设置节点边框样式和圆角
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

// 设置节点文本内容和字体大小
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

// 设置节点通用属性（宽度、高度、背景色、边距、边框）
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

// 设置节点通用百分比属性
void SetCommonPercentAttribute(ArkUI_NodeHandle &node, float width = 1, float height = 1,
    unsigned int color = DEFAULT_BG_COLOR, float margin = DEFAULT_MARGIN)
{
    SetWidthPercent(node, width);
    SetHeightPercent(node, height);
    SetBackgroundColor(node, color);
    SetMargin(node, margin);
    SetBorderWidth(node, DEFAULT_BORDER_WIDTH);
    SetBorderColor(node);
}

// 设置节点文本属性
void SetTextAttribute(ArkUI_NodeHandle &node, const char *str, float size = DEFAULT_TEXT_FONT_SIZE,
    float width = DEFAULT_WIDTH, float height = DEFAULT_HEIGHT)
{
    SetCommonAttribute(node, width, height, 0);
    SetText(node, str, size);
}

// 设置Column组件的内容对齐方式
void SetColumnJustifyContent(ArkUI_NodeHandle &node, int32_t alignment)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue justifyValue[] = {{.i32 = alignment}};
    ArkUI_AttributeItem justifyItem = {justifyValue, 1};
    nodeAPI->setAttribute(node, NODE_COLUMN_JUSTIFY_CONTENT, &justifyItem);
}

// 设置Column组件的子元素对齐方式
void SetColumnAlignItem(ArkUI_NodeHandle &node, int32_t alignment)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue alignValue[] = {{.i32 = alignment}};
    ArkUI_AttributeItem alignItem = {alignValue, 1};
    nodeAPI->setAttribute(node, NODE_COLUMN_ALIGN_ITEMS, &alignItem);
}

// 设置Row组件的内容对齐方式
void SetRowJustifyContent(ArkUI_NodeHandle &node, int32_t alignment)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue justifyValue[] = {{.i32 = alignment}};
    ArkUI_AttributeItem justifyItem = {justifyValue, 1};
    nodeAPI->setAttribute(node, NODE_ROW_JUSTIFY_CONTENT, &justifyItem);
}

// 设置Row组件的子元素对齐方式
void SetRowAlignItem(ArkUI_NodeHandle &node, int32_t alignment)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue alignValue[] = {{.i32 = alignment}};
    ArkUI_AttributeItem alignItem = {alignValue, 1};
    nodeAPI->setAttribute(node, NODE_ROW_ALIGN_ITEMS, &alignItem);
}

// 设置节点的点击测试模式
void SetHitTestMode(ArkUI_NodeHandle &node, int32_t mode)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue modeValue[] = {{.i32 = mode}};
    ArkUI_AttributeItem modeItem = {modeValue, 1};
    nodeAPI->setAttribute(node, NODE_HIT_TEST_BEHAVIOR, &modeItem);
}

// 设置按钮标签文本
void SetButtonLabel(ArkUI_NodeHandle &node, const char *label)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_AttributeItem NODE_Button_SRC_Item = {.string = label};
    nodeAPI->setAttribute(node, NODE_BUTTON_LABEL, &NODE_Button_SRC_Item);
}

// 设置节点ID
void SetId(ArkUI_NodeHandle &node, const char *id)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_AttributeItem idItem = {.string = id};
    nodeAPI->setAttribute(node, NODE_ID, &idItem);
}

} // namespace NativeXComponentSample

#endif // DRAGANDDROP_COMMON_H