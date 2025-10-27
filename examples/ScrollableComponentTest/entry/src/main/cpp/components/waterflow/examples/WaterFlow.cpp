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

#include "components/waterflow/WaterFlow1.h"

namespace ArkUICApiDemo {

void WaterFlowSectionOption::SetSection(int32_t index, WaterFlowSection section)
{
    OH_ArkUI_WaterFlowSectionOption_SetItemCount(_option, index, section.itemsCount);
    OH_ArkUI_WaterFlowSectionOption_SetCrossCount(_option, index, section.crossCount);
    OH_ArkUI_WaterFlowSectionOption_SetColumnGap(_option, index, section.columnsGap);
    OH_ArkUI_WaterFlowSectionOption_SetRowGap(_option, index, section.rowsGap);
    OH_ArkUI_WaterFlowSectionOption_SetMargin(
        _option, index, section.margin.top, section.margin.right, section.margin.bottom, section.margin.left);
    OH_ArkUI_WaterFlowSectionOption_RegisterGetItemMainSizeCallbackByIndex(
        _option, index, section.onGetItemMainSizeByIndex);
}
WaterFlowSection WaterFlowSectionOption::GetSection(int32_t index)
{
    return { OH_ArkUI_WaterFlowSectionOption_GetItemCount(_option, index),
        OH_ArkUI_WaterFlowSectionOption_GetCrossCount(_option, index),
        OH_ArkUI_WaterFlowSectionOption_GetColumnGap(_option, index),
        OH_ArkUI_WaterFlowSectionOption_GetRowGap(_option, index),
        OH_ArkUI_WaterFlowSectionOption_GetMargin(_option, index) };
}

void WaterFlowSectionOption::SetSize(int32_t size)
{
    OH_ArkUI_WaterFlowSectionOption_SetSize(_option, size);
}
int32_t WaterFlowSectionOption::GetSize()
{
    return OH_ArkUI_WaterFlowSectionOption_GetSize(_option);
}

void WaterFlowComponent::SetLayoutDirection(int32_t layoutDirection)
{
    ArkUI_NumberValue value[] = { { .i32 = layoutDirection } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_WATER_FLOW_LAYOUT_DIRECTION, &item);
}

void WaterFlowComponent::SetColumnsTemplate(const std::string& str)
{
    ArkUI_AttributeItem item = { .string = str.c_str() };
    _nodeAPI->setAttribute(_component, NODE_WATER_FLOW_COLUMN_TEMPLATE, &item);
}

void WaterFlowComponent::SetRowsTemplate(const std::string& str)
{
    ArkUI_AttributeItem item = { .string = str.c_str() };
    _nodeAPI->setAttribute(_component, NODE_WATER_FLOW_ROW_TEMPLATE, &item);
}

void WaterFlowComponent::SetWaterFlowColumnsGap(float val)
{
    ArkUI_NumberValue value[] = { { .f32 = val } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_WATER_FLOW_COLUMN_GAP, &item);
}

void WaterFlowComponent::SetWaterFlowRowsGap(float val)
{
    ArkUI_NumberValue value[] = { { .f32 = val } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_WATER_FLOW_ROW_GAP, &item);
}

void WaterFlowComponent::SetWaterFlowSectionOption(int32_t start, const std::shared_ptr<WaterFlowSectionOption>& option)
{
    ArkUI_NumberValue value[] = { { .i32 = start } };
    ArkUI_AttributeItem item = { value, 1, nullptr, option->GetOption() };
    _nodeAPI->setAttribute(_component, NODE_WATER_FLOW_SECTION_OPTION, &item);
    _sectionsOption = option;
}

void WaterFlowComponent::SetWaterFlowCachedCount(int32_t cachedCount)
{
    ArkUI_NumberValue value[] = { { .i32 = cachedCount } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_WATER_FLOW_CACHED_COUNT, &item);
}

void WaterFlowComponent::SetWaterFlowFooter(ArkUI_NodeHandle node)
{
    ArkUI_AttributeItem item = { .object = node };
    _nodeAPI->setAttribute(_component, NODE_WATER_FLOW_FOOTER, &item);
}

void WaterFlowComponent::SetWaterFlowScrollToIndex(int32_t index)
{
    ArkUI_NumberValue value[] = { { .i32 = index } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_WATER_FLOW_SCROLL_TO_INDEX, &item);
}

void WaterFlowComponent::SetWaterFlowScrollToIndex(int32_t index, int32_t animation)
{
    ArkUI_NumberValue value[] = { { .i32 = index }, { .i32 = animation } };
    ArkUI_AttributeItem item = { value, 2 };
    _nodeAPI->setAttribute(_component, NODE_WATER_FLOW_SCROLL_TO_INDEX, &item);
}

void WaterFlowComponent::SetWaterFlowScrollToIndex(int32_t index, int32_t animation, int32_t alignment)
{
    ArkUI_NumberValue value[] = { { .i32 = index }, { .i32 = animation }, { .i32 = alignment } };
    ArkUI_AttributeItem item = { value, 3 };
    _nodeAPI->setAttribute(_component, NODE_WATER_FLOW_SCROLL_TO_INDEX, &item);
}

void WaterFlowComponent::SetItemConstraintSize(float minWidth, float maxWidth, float minHeight, float maxHeight)
{
    ArkUI_NumberValue value[] = { { .f32 = minWidth }, { .f32 = maxWidth }, { .f32 = minHeight },
        { .f32 = maxHeight } };
    ArkUI_AttributeItem item = { value, 4 };
    _nodeAPI->setAttribute(_component, NODE_WATER_FLOW_ITEM_CONSTRAINT_SIZE, &item);
}
void WaterFlowComponent::SetWaterFlowNestedScroll(int32_t forward, int32_t backward)
{
    ArkUI_NumberValue value[] = { { .i32 = forward }, { .i32 = backward } };
    ArkUI_AttributeItem item = { value, 2 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_NESTED_SCROLL, &item);
}
void WaterFlowComponent::SetWaterFlowScrollBar(int32_t barState)
{
    ArkUI_NumberValue value[] = { { .i32 = barState } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_BAR_DISPLAY_MODE, &item);
}
void WaterFlowComponent::SetWaterFlowScrollBarWidth(float width)
{
    ArkUI_NumberValue value[] = { { .f32 = width } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_BAR_WIDTH, &item);
}
void WaterFlowComponent::SetWaterFlowScrollBarColor(uint32_t color)
{
    ArkUI_NumberValue value[] = { { .u32 = color } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_BAR_COLOR, &item);
}
void WaterFlowComponent::SetWaterFlowEnableScrollInteraction(bool enableScrollInteraction)
{
    ArkUI_NumberValue value[] = { { .i32 = enableScrollInteraction } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_ENABLE_SCROLL_INTERACTION, &item);
}
void WaterFlowComponent::SetWaterFlowFriction(float friction)
{
    ArkUI_NumberValue value[] = { { .f32 = friction } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_FRICTION, &item);
}
void WaterFlowComponent::SetWaterFlowEdgeEffect(int32_t edgeEffect, bool alwaysEnabled)
{
    ArkUI_NumberValue value[] = { { .i32 = edgeEffect }, { .i32 = alwaysEnabled } };
    ArkUI_AttributeItem item = { value, 2 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_EDGE_EFFECT, &item);
}
void WaterFlowComponent::SetScrollTo(float hOffset, float vOffset, const std::vector<int32_t>& optionalParams)
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
void WaterFlowComponent::SetScrollEdge(int32_t type)
{
    ArkUI_NumberValue value[] = { { .i32 = type } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_EDGE, &item);
}
void WaterFlowComponent::SetScrollPage(bool next)
{
    ArkUI_NumberValue value[] = { { .i32 = next } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_PAGE, &item);
}
void WaterFlowComponent::SetScrollPage(bool next, bool animation)
{
    ArkUI_NumberValue value[] = { { .i32 = next }, { .i32 = animation } };
    ArkUI_AttributeItem item = { value, 2 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_PAGE, &item);
}
void WaterFlowComponent::SetScrollBy(float hDistance, float vDistance)
{
    ArkUI_NumberValue value[] = { { .f32 = hDistance }, { .f32 = vDistance } };
    ArkUI_AttributeItem item = { value, 2 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_BY, &item);
}
void WaterFlowComponent::OnNodeEvent(ArkUI_NodeEvent* event)
{
    auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
    if (eventMap_.find(eventType) != eventMap_.end()) {
        eventMap_[eventType](event);
    }
}
void WaterFlowComponent::SetOnWillScroll(OnWillScroll onWillScroll)
{
    auto onWillScrollCallback = [onWillScroll](ArkUI_NodeEvent* event) {
        ArkUI_NodeComponentEvent* result = OH_ArkUI_NodeEvent_GetNodeComponentEvent(event);
        float offset = result->data[0].f32;
        int32_t state = result->data[1].i32;
        int32_t source = result->data[2].i32;
        if (onWillScroll) {
            onWillScroll(offset, state, source);
        }
    };
    eventMap_[NODE_ON_WILL_SCROLL] = onWillScrollCallback;
    _nodeAPI->registerNodeEvent(_component, NODE_ON_WILL_SCROLL, 0, nullptr);
}
void WaterFlowComponent::SetOnReachStart(OnReachStart onReachStart)
{
    auto onReachStartCallback = [onReachStart](ArkUI_NodeEvent*) {
        if (onReachStart) {
            onReachStart();
        }
    };
    eventMap_[NODE_SCROLL_EVENT_ON_REACH_START] = onReachStartCallback;
    _nodeAPI->registerNodeEvent(_component, NODE_SCROLL_EVENT_ON_REACH_START, 0, nullptr);
}
void WaterFlowComponent::SetOnReachEnd(OnReachEnd onReachEnd)
{
    auto onReachEndCallback = [onReachEnd](ArkUI_NodeEvent*) {
        if (onReachEnd) {
            onReachEnd();
        }
    };
    eventMap_[NODE_SCROLL_EVENT_ON_REACH_END] = onReachEndCallback;
    _nodeAPI->registerNodeEvent(_component, NODE_SCROLL_EVENT_ON_REACH_END, 0, nullptr);
}
void WaterFlowComponent::SetOnScrollStop(OnScrollStop onScrollStop)
{
    auto onScrollStopCallback = [onScrollStop](ArkUI_NodeEvent*) {
        if (onScrollStop) {
            onScrollStop();
        }
    };
    eventMap_[NODE_SCROLL_EVENT_ON_SCROLL_STOP] = onScrollStopCallback;
    _nodeAPI->registerNodeEvent(_component, NODE_SCROLL_EVENT_ON_SCROLL_STOP, 0, nullptr);
}
void WaterFlowComponent::SetOnDidScroll(OnDidScroll onDidScroll)
{
    auto onDidScrollCallback = [onDidScroll](ArkUI_NodeEvent* event) {
        ArkUI_NodeComponentEvent* result = OH_ArkUI_NodeEvent_GetNodeComponentEvent(event);
        if (onDidScroll) {
            float offset = result->data[0].f32;
            int32_t state = result->data[1].i32;
            onDidScroll(offset, state);
        }
    };
    eventMap_[NODE_WATER_FLOW_ON_DID_SCROLL] = onDidScrollCallback;
    _nodeAPI->registerNodeEvent(_component, NODE_WATER_FLOW_ON_DID_SCROLL, 0, nullptr);
}
void WaterFlowComponent::SetOnScrollFrameBegin(OnScrollFrameBegin onScrollFrameBegin)
{
    auto onScrollFrameBeginCallback = [onScrollFrameBegin](ArkUI_NodeEvent* event) {
        ArkUI_NodeComponentEvent* result = OH_ArkUI_NodeEvent_GetNodeComponentEvent(event);
        if (onScrollFrameBegin) {
            float offset = result->data[0].f32;
            int32_t state = result->data[1].i32;
            result->data[0].f32 = onScrollFrameBegin(offset, state);
        }
    };
    eventMap_[NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN] = onScrollFrameBeginCallback;
    _nodeAPI->registerNodeEvent(_component, NODE_SCROLL_EVENT_ON_SCROLL_FRAME_BEGIN, 0, nullptr);
}
void WaterFlowComponent::SetOnScrollIndex(OnScrollIndex onScrollIndex)
{
    auto onScrollIndexCallback = [onScrollIndex](ArkUI_NodeEvent* event) {
        ArkUI_NodeComponentEvent* result = OH_ArkUI_NodeEvent_GetNodeComponentEvent(event);
        if (onScrollIndex) {
            int32_t first = result->data[0].i32;
            int32_t last = result->data[1].i32;
            onScrollIndex(first, last);
        }
    };
    eventMap_[NODE_WATER_FLOW_ON_SCROLL_INDEX] = onScrollIndexCallback;
    _nodeAPI->registerNodeEvent(_component, NODE_WATER_FLOW_ON_SCROLL_INDEX, 0, nullptr);
}
} // namespace ArkUICApiDemo
