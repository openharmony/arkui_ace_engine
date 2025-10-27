/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "components/scroll/Scroll1.h"
namespace ArkUICApiDemo {

void ScrollComponent::SetScrollScrollBar(int32_t barState)
{
    ArkUI_NumberValue value[] = { { .i32 = barState } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_BAR_DISPLAY_MODE, &item);
}
void ScrollComponent::SetScrollScrollBarWidth(float width)
{
    ArkUI_NumberValue value[] = { { .f32 = width } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_BAR_WIDTH, &item);
}
void ScrollComponent::SetScrollScrollBarColor(uint32_t color)
{
    ArkUI_NumberValue value[] = { { .u32 = color } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_BAR_COLOR, &item);
}
void ScrollComponent::SetScrollScrollable(int32_t scrollable)
{
    ArkUI_NumberValue value[] = { { .i32 = scrollable } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_SCROLL_DIRECTION, &item);
}
void ScrollComponent::SetScrollEdgeEffect(int32_t edgeEffect, bool alwaysEnabled)
{
    ArkUI_NumberValue value[] = { { .i32 = edgeEffect }, { .i32 = alwaysEnabled } };
    ArkUI_AttributeItem item = { value, 2 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_EDGE_EFFECT, &item);
}
void ScrollComponent::SetScrollEnableScrollInteraction(bool enableScrollInteraction)
{
    ArkUI_NumberValue value[] = { { .i32 = enableScrollInteraction } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_ENABLE_SCROLL_INTERACTION, &item);
}
void ScrollComponent::SetScrollFriction(float friction)
{
    ArkUI_NumberValue value[] = { { .f32 = friction } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_FRICTION, &item);
}
void ScrollComponent::SetScrollScrollSnap(
    int32_t snapAlign, int32_t enableSnapToStart, int32_t enableSnapToEnd, const std::vector<float>& pagination)
{
    auto value = new ArkUI_NumberValue[3 + static_cast<int32_t>(pagination.size())];
    value[0] = { .i32 = snapAlign };
    value[1] = { .i32 = enableSnapToStart };
    value[2] = { .i32 = enableSnapToEnd };
    for (int32_t i = 0; i < pagination.size(); i++) {
        value[3 + i] = { .f32 = pagination[i] };
    }
    ArkUI_AttributeItem item = { value, 3 + static_cast<int32_t>(pagination.size()) };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_SNAP, &item);
}
void ScrollComponent::SetScrollNestedScroll(int32_t forward, int32_t backward)
{
    ArkUI_NumberValue value[] = { { .i32 = forward }, { .i32 = backward } };
    ArkUI_AttributeItem item = { value, 2 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_NESTED_SCROLL, &item);
}
void ScrollComponent::SetScrollTo(float hOffset, float vOffset, const std::vector<int32_t>& optionalParams)
{
    auto value = new ArkUI_NumberValue[2 + static_cast<int32_t>(optionalParams.size())];
    value[0] = { .f32 = hOffset };
    value[1] = { .f32 = vOffset };
    for (int32_t i = 0; i < optionalParams.size(); i++) {
        value[2 + i] = { .i32 = optionalParams[i] };
    }
    ArkUI_AttributeItem item = { value, 2 + static_cast<int32_t>(optionalParams.size()) };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_OFFSET, &item);
}
void ScrollComponent::SetScrollEdge(int32_t type)
{
    ArkUI_NumberValue value[] = { { .i32 = type } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_EDGE, &item);
}
void ScrollComponent::SetScrollEnablePaging(int32_t enablePaging)
{
    ArkUI_NumberValue value[] = { { .i32 = enablePaging } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_ENABLE_PAGING, &item);
}
void ScrollComponent::SetScrollPage(int32_t next)
{
    ArkUI_NumberValue value[] = { { .i32 = next } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_PAGE, &item);
}
void ScrollComponent::SetScrollPage(int32_t next, int32_t animation)
{
    ArkUI_NumberValue value[] = { { .i32 = next }, { .i32 = animation } };
    ArkUI_AttributeItem item = { value, 2 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_PAGE, &item);
}
void ScrollComponent::SetScrollBy(float hDistance, float vDistance)
{
    ArkUI_NumberValue value[] = { { .f32 = hDistance }, { .f32 = vDistance } };
    ArkUI_AttributeItem item = { value, 2 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_BY, &item);
}
void ScrollComponent::SetScrollScrollDirection(int32_t direction)
{
    ArkUI_NumberValue value[] = { { .i32 = direction } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_SCROLL_DIRECTION, &item);
}
void ScrollComponent::AddChildWithNumber(int32_t number, ArkUI_NodeType type)
{
    SetBorderWidth(number);
    auto node = std::make_shared<Component>(type);
    if (type == ARKUI_NODE_LIST) {
        ArkUI_NumberValue value[] = { { .i32 = ARKUI_AXIS_HORIZONTAL } };
        ArkUI_AttributeItem item = { value, 1 };
        node->setAttribute(NODE_LIST_DIRECTION, &item);
        node->SetMargin(DEFAULT_MARGIN);
    }
    for (int32_t i = 0; i < number; ++i) {
        auto column = std::make_shared<Component>(ARKUI_NODE_COLUMN);
        column->SetWidth(SIZE_50);
        column->SetHeight(SIZE_50);
        column->SetMargin(DEFAULT_MARGIN);
        if (number == 0) {
            number = 1;
        }
        column->SetBackgroundColor((i * 0xFFFFFF / number) | 0xFF000000);
        node->AddChild(column);
    }
    AddChild(node);
}
} // namespace ArkUICApiDemo