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
#include <hilog/log.h>
#include <sstream>

#define DEFAULT_WIDTH 200.0
#define DEFAULT_HEIGHT 200.0
#define DEFAULT_BG_COLOR 0xFFFFFFFF
#define DEFAULT_BORDER_WIDTH 0.0
#define BORDER_WIDTH_1 1.0
#define DEFAULT_MARGIN 5.0
#define DEFAULT_BORDER_COLOR 0xFF000000
#define DEFAULT_RADIUS 10.0

#define SIZE_100 100
#define SIZE_300 300
#define BLANK_10 10.0
#define BLANK_20 20.0
#define BLANK_30 30.0

#define DEFAULT_TEXT_FONT_SIZE 12
#define TEXT_FONT_SIZE_15 15
#define TEXT_FONT_SIZE_20 20

#define BUTTON_LENGTH 10
#define MAX_LENGTH 128

namespace NativeModule {
// [Start define_node]
ArkUI_NativeNodeAPI_1 *nodeAPI = nullptr;
// [End define_node]
std::stringstream g_ss;

void SetWidthPercent(ArkUI_NodeHandle &node, float width = 1)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue widthValue[] = {width};
    ArkUI_AttributeItem widthItem = {widthValue, 1};
    nodeAPI->setAttribute(node, NODE_WIDTH_PERCENT, &widthItem);
}

void SetHeight(ArkUI_NodeHandle &node, float height = DEFAULT_HEIGHT)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue heightValue[] = {height};
    ArkUI_AttributeItem heightItem = {heightValue, 1};
    nodeAPI->setAttribute(node, NODE_HEIGHT, &heightItem);
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

void SetPadding(ArkUI_NodeHandle &node, float padding)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue paddingValue[] = {padding};
    ArkUI_AttributeItem paddingItem = {paddingValue, 1};
    nodeAPI->setAttribute(node, NODE_PADDING, &paddingItem);
}

void SetBorderWidth(ArkUI_NodeHandle &node, float width = DEFAULT_BORDER_WIDTH)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_NumberValue borderWidthValue[] = {width};
    ArkUI_AttributeItem borderWidthItem = {borderWidthValue, 1};
    nodeAPI->setAttribute(node, NODE_BORDER_WIDTH, &borderWidthItem);
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

void SetButtonLabel(ArkUI_NodeHandle &node, const char *label)
{
    if (!nodeAPI) {
        return;
    }
    ArkUI_AttributeItem NODE_Button_SRC_Item = {.string = label};
    nodeAPI->setAttribute(node, NODE_BUTTON_LABEL, &NODE_Button_SRC_Item);
}

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