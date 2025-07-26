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

RefPtr<FrameNode> GridModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::GRID_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<GridPattern>(); });

    return frameNode;
}

void GridModelStatic::SetLayoutOptions(FrameNode* frameNode, GridLayoutOptions& options)
{
    // only support regularSize(1, 1)
    options.regularSize.rows = 1;
    options.regularSize.columns = 1;

    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, LayoutOptions, options, frameNode);
}

void GridModelStatic::SetColumnsTemplate(FrameNode* frameNode, const std::string& columnsTemplate)
{
    if (columnsTemplate.empty()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, ColumnsTemplate, "1fr", frameNode);
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, ColumnsTemplate, columnsTemplate, frameNode);
}

void GridModelStatic::SetRowsTemplate(FrameNode* frameNode, const std::string& rowsTemplate)
{
    if (rowsTemplate.empty()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, RowsTemplate, "1fr", frameNode);
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, RowsTemplate, rowsTemplate, frameNode);
}

void GridModelStatic::SetOnScrollBarUpdate(FrameNode* frameNode, ScrollBarUpdateFunc&& value)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollBarUpdate(std::move(value));
}

void GridModelStatic::SetOnScrollIndex(FrameNode* frameNode, ScrollIndexFunc&& onScrollIndex)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollIndex(std::move(onScrollIndex));
}

void GridModelStatic::SetCachedCount(FrameNode* frameNode, int32_t cachedCount)
{
    if (cachedCount >= 0) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, CachedCount, cachedCount, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridLayoutProperty, CachedCount, frameNode);
    }
}

void GridModelStatic::SetShowCached(FrameNode* frameNode, bool show)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, ShowCachedItems, show, frameNode);
}

void GridModelStatic::SetEditable(FrameNode* frameNode, bool editMode)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, Editable, editMode, frameNode);
}

void GridModelStatic::SetMultiSelectable(FrameNode* frameNode, bool multiSelectable)
{
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMultiSelectable(multiSelectable);
}

void GridModelStatic::SetMaxCount(FrameNode* frameNode, int32_t maxCount)
{
    if (maxCount >= 1) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, MaxCount, maxCount, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridLayoutProperty, MaxCount, frameNode);
    }
}

void GridModelStatic::SetMinCount(FrameNode* frameNode, int32_t minCount)
{
    if (minCount >= 1) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, MinCount, minCount, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridLayoutProperty, MinCount, frameNode);
    }
}

void GridModelStatic::SetCellLength(FrameNode* frameNode, int32_t cellLength)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, CellLength, cellLength, frameNode);
}

void GridModelStatic::SetSupportAnimation(FrameNode* frameNode, bool supportAnimation)
{
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSupportAnimation(supportAnimation);
}

EdgeEffect GridModelStatic::GetEdgeEffect(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, EdgeEffect::NONE);
    return static_cast<EdgeEffect>(ScrollableModelNG::GetEdgeEffect(frameNode));
}

bool GridModelStatic::GetAlwaysEnabled(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<bool>(ScrollableModelNG::GetAlwaysEnabled(frameNode));
}

void GridModelStatic::SetEdgeEffect(
    FrameNode* frameNode, const std::optional<EdgeEffect>& edgeEffect, const std::optional<bool>& alwaysEnabled,
    EffectEdge edge)
{
    ScrollableModelNG::SetEdgeEffect(frameNode,
        edgeEffect.value_or(EdgeEffect::NONE), alwaysEnabled.value_or(false), edge);
}

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

void GridModelStatic::SetNestedScroll(FrameNode* frameNode, const NestedScrollOptions& nestedOpt)
{
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNestedScroll(nestedOpt);
}

void GridModelStatic::SetScrollEnabled(FrameNode* frameNode, bool scrollEnabled)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, ScrollEnabled, scrollEnabled, frameNode);
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

void GridModelStatic::SetOnItemDragStart(
    FrameNode* frameNode, std::function<void(const ItemDragInfo&, int32_t)>&& value)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto onDragStart = [func = std::move(value)](const ItemDragInfo& dragInfo, int32_t index) -> RefPtr<UINode> {
        ScopedViewStackProcessor builderViewStackProcessor;
        {
            func(dragInfo, index);
        }
        return ViewStackProcessor::GetInstance()->Finish();
    };
    eventHub->SetOnItemDragStart(std::move(onDragStart));

    auto gestureEventHub = eventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    eventHub->InitItemDragEvent(gestureEventHub);

    AddDragFrameNodeToManager(frameNode);
}

void GridModelStatic::SetOnItemDragEnter(FrameNode* frameNode, ItemDragEnterFunc&& value)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragEnter(std::move(value));

    AddDragFrameNodeToManager(frameNode);
}

void GridModelStatic::SetOnItemDragMove(FrameNode* frameNode, ItemDragMoveFunc&& value)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragMove(std::move(value));

    AddDragFrameNodeToManager(frameNode);
}

void GridModelStatic::SetOnItemDragLeave(FrameNode* frameNode, ItemDragLeaveFunc&& value)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragLeave(std::move(value));

    AddDragFrameNodeToManager(frameNode);
}

void GridModelStatic::SetOnItemDrop(FrameNode* frameNode, ItemDropFunc&& value)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDrop(std::move(value));

    AddDragFrameNodeToManager(frameNode);
}

void GridModelStatic::AddDragFrameNodeToManager(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);

    dragDropManager->AddGridDragFrameNode(frameNode->GetId(), AceType::WeakClaim(frameNode));
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

void GridModelStatic::SetColumnsGap(FrameNode* frameNode, const std::optional<Dimension>& columnsGap)
{
    if (columnsGap && GreatOrEqual(columnsGap.value().Value(), 0.0f)) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, ColumnsGap, columnsGap.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridLayoutProperty, ColumnsGap, frameNode);
    }
}

void GridModelStatic::SetRowsGap(FrameNode* frameNode, const std::optional<Dimension>& rowsGap)
{
    if (rowsGap && GreatOrEqual(rowsGap.value().Value(), 0.0f)) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, RowsGap, rowsGap.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridLayoutProperty, RowsGap, frameNode);
    }
}

RefPtr<ScrollControllerBase> GridModelStatic::GetOrCreateController(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetOrCreatePositionController();
}

RefPtr<ScrollProxy> GridModelStatic::GetOrCreateScrollBarProxy(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto scrollBarProxy = pattern->GetScrollBarProxy();
    if (scrollBarProxy == nullptr) {
        scrollBarProxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
        pattern->SetScrollBarProxy(scrollBarProxy);
    }
    return scrollBarProxy;
}

void GridModelStatic::SetOnScroll(FrameNode* frameNode, OnScrollEvent&& onScroll)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScroll(std::move(onScroll));
}
} // namespace OHOS::Ace::NG