/*
* Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid/grid_model_static.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"

namespace OHOS::Ace::NG {

void GridModelStatic::SetScrollBarMode(FrameNode* frameNode, const std::optional<DisplayMode>& scrollBarMode)
{
    if (scrollBarMode) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarMode, scrollBarMode.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarMode, frameNode);
    }
}

void GridModelStatic::SetScrollBarWidth(FrameNode* frameNode, const std::optional<Dimension>& scrollBarWidth)
{
    if (scrollBarWidth &&
        GreatOrEqual(scrollBarWidth.value().Value(), 0.0f) &&
        scrollBarWidth.value().Unit() != DimensionUnit::PERCENT) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarWidth, scrollBarWidth.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarWidth, frameNode);
    }
}

void GridModelStatic::SetScrollBarColor(FrameNode* frameNode, const std::optional<Color>& scrollBarColor)
{
    if (scrollBarColor) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarColor, scrollBarColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarColor, frameNode);
    }
}

void GridModelStatic::SetLayoutDirection(FrameNode* frameNode, const std::optional<FlexDirection>& layoutDirection)
{
    if (layoutDirection) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, GridDirection, layoutDirection.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridLayoutProperty, GridDirection, frameNode);
    }
}

void GridModelStatic::SetFriction(FrameNode* frameNode, const std::optional<double>& value)
{
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    std::optional<double> friction = value;
    if (friction.has_value() && LessOrEqual(friction.value(), 0.0f)) {
        friction.reset();
    }
    pattern->SetFriction(friction.value_or(-1.0f));
}

void GridModelStatic::SetAlignItems(FrameNode* frameNode, const std::optional<GridItemAlignment>& itemAlign)
{
    if (itemAlign) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, AlignItems, itemAlign.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridLayoutProperty, AlignItems, frameNode);
    }
}

void GridModelStatic::SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& onScrollFrameBegin)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollFrameBegin(std::move(onScrollFrameBegin));
}

void GridModelStatic::SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachStart(std::move(onReachStart));
}

void GridModelStatic::SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachEnd(std::move(onReachEnd));
}

void GridModelStatic::SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& onScrollStart)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStart(std::move(onScrollStart));
}

void GridModelStatic::SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& onScrollStop)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStop(std::move(onScrollStop));
}
} // namespace OHOS::Ace::NG