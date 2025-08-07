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

#include "core/components_ng/pattern/grid/grid_model_ng.h"

#include "base/utils/system_properties.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/manager/scroll_adjust/scroll_adjust_manager.h"

namespace OHOS::Ace::NG {

void GridModelNG::Create(const RefPtr<ScrollControllerBase>& positionController, const RefPtr<ScrollProxy>& scrollProxy)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::GRID_ETS_TAG, nodeId);
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::GRID_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<GridPattern>(); });
    stack->Push(frameNode);
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    if (positionController) {
        auto controller = AceType::DynamicCast<ScrollableController>(positionController);
        pattern->SetPositionController(controller);
    }
    if (scrollProxy) {
        auto scrollBarProxy = AceType::DynamicCast<NG::ScrollBarProxy>(scrollProxy);
        pattern->SetScrollBarProxy(scrollBarProxy);
    }
    pattern->AddScrollableFrameInfo(SCROLL_FROM_NONE);
}

RefPtr<ScrollControllerBase> GridModelNG::GetOrCreateController(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetOrCreatePositionController();
}

RefPtr<ScrollProxy> GridModelNG::GetOrCreateScrollBarProxy(FrameNode* frameNode)
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

RefPtr<FrameNode> GridModelNG::CreateGrid(int32_t nodeId)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::GRID_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<GridPattern>(); });
    return frameNode;
}

void GridModelNG::Pop()
{
    NG::ViewStackProcessor::GetInstance()->PopContainer();
}

void GridModelNG::SetLayoutOptions(GridLayoutOptions options)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, LayoutOptions, options);
}

void GridModelNG::SetColumnsTemplate(const std::string& value)
{
    if (value.empty()) {
        TAG_LOGW(AceLogTag::ACE_GRID, "Columns Template [%{public}s] is not valid.", value.c_str());
        ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, ColumnsTemplate, "1fr");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, ColumnsTemplate, value);
}

void GridModelNG::SetRowsTemplate(const std::string& value)
{
    if (value.empty()) {
        TAG_LOGW(AceLogTag::ACE_GRID, "Rows Template [%{public}s] is not valid.", value.c_str());
        ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, RowsTemplate, "1fr");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, RowsTemplate, value);
}

void GridModelNG::SetColumnsGap(const Dimension& value)
{
    if (value.IsNonNegative()) {
        ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, ColumnsGap, value);
    }
}

void GridModelNG::SetRowsGap(const Dimension& value)
{
    if (value.IsNonNegative()) {
        ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, RowsGap, value);
    }
}

void GridModelNG::SetGridHeight(const Dimension& value)
{
    ViewAbstract::SetHeight(NG::CalcLength(value));
}

void GridModelNG::SetScrollBarMode(DisplayMode value)
{
    ACE_UPDATE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarMode, value);
}

void GridModelNG::SetScrollBarColor(const std::string& value)
{
    ACE_UPDATE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarColor, Color::FromString(value));
}

void GridModelNG::SetScrollBarWidth(const std::string& value)
{
    ACE_UPDATE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarWidth, StringUtils::StringToDimensionWithUnit(value));
}

void GridModelNG::SetCachedCount(int32_t value, bool show)
{
    int32_t count = value;
    if (SystemProperties::IsWhiteBlockEnabled()) {
        count = ScrollAdjustmanager::GetInstance().AdjustCachedCount(count);
    }
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, CachedCount, count);
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, ShowCachedItems, show);
}

void GridModelNG::SetEditable(bool value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, Editable, value);
}

void GridModelNG::SetIsRTL(TextDirection direction)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, LayoutDirection, direction);
}

void GridModelNG::SetLayoutDirection(FlexDirection value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, GridDirection, value);
}

void GridModelNG::SetMaxCount(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, MaxCount, value);
}

void GridModelNG::SetMinCount(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, MinCount, value);
}

void GridModelNG::SetCellLength(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, CellLength, value);
}

void GridModelNG::SetMultiSelectable(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMultiSelectable(value);
}

void GridModelNG::SetSupportAnimation(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSupportAnimation(value);
}

void GridModelNG::SetSupportDragAnimation(bool value) {}

void GridModelNG::SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled, EffectEdge edge)
{
    ScrollableModelNG::SetEdgeEffect(edgeEffect, alwaysEnabled, edge);
}

void GridModelNG::SetNestedScroll(const NestedScrollOptions& nestedOpt)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNestedScroll(nestedOpt);
}

void GridModelNG::SetScrollEnabled(bool scrollEnabled)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, ScrollEnabled, scrollEnabled);
}

void GridModelNG::SetFriction(double friction)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFriction(friction);
}

void GridModelNG::SetFocusWrapMode(const std::optional<FocusWrapMode>& focusWrapMode)
{
    if (focusWrapMode) {
        ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, FocusWrapMode, focusWrapMode.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY(GridLayoutProperty, FocusWrapMode);
    }
}

FocusWrapMode GridModelNG::GetFocusWrapMode(FrameNode* frameNode)
{
    FocusWrapMode focusWrapMode = FocusWrapMode::DEFAULT;
    CHECK_NULL_RETURN(frameNode, focusWrapMode);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        GridLayoutProperty, FocusWrapMode, focusWrapMode, frameNode, focusWrapMode);
    return focusWrapMode;
}

void GridModelNG::SetAlignItems(GridItemAlignment itemAlign)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, AlignItems, itemAlign);
}

void GridModelNG::SetOnScrollToIndex(ScrollToIndexFunc&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollToIndex(std::move(value));
}

void GridModelNG::SetOnScrollBarUpdate(ScrollBarUpdateFunc&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollBarUpdate(std::move(value));
}

void GridModelNG::SetOnItemDragStart(std::function<void(const ItemDragInfo&, int32_t)>&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
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

    GridModelNG::AddDragFrameNodeToManager(frameNode);
}

void GridModelNG::SetOnItemDragEnter(ItemDragEnterFunc&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragEnter(std::move(value));

    GridModelNG::AddDragFrameNodeToManager(frameNode);
}

void GridModelNG::SetOnItemDragMove(ItemDragMoveFunc&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragMove(std::move(value));

    GridModelNG::AddDragFrameNodeToManager(frameNode);
}

void GridModelNG::SetOnItemDragLeave(ItemDragLeaveFunc&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragLeave(std::move(value));

    GridModelNG::AddDragFrameNodeToManager(frameNode);
}

void GridModelNG::SetOnItemDrop(ItemDropFunc&& value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDrop(std::move(value));

    GridModelNG::AddDragFrameNodeToManager(frameNode);
}

void GridModelNG::SetOnScroll(OnScrollEvent&& onScroll)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScroll(std::move(onScroll));
}

void GridModelNG::SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& onScrollFrameBegin)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollFrameBegin(std::move(onScrollFrameBegin));
}

void GridModelNG::SetOnScrollStart(OnScrollStartEvent&& onScrollStart)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStart(std::move(onScrollStart));
}

void GridModelNG::SetOnScrollStop(OnScrollStopEvent&& onScrollStop)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStop(std::move(onScrollStop));
}

void GridModelNG::SetOnScrollIndex(ScrollIndexFunc&& onScrollIndex)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollIndex(std::move(onScrollIndex));
}

void GridModelNG::SetOnReachStart(OnReachEvent&& onReachStart)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachStart(std::move(onReachStart));
}

void GridModelNG::SetOnReachEnd(OnReachEvent&& onReachEnd)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachEnd(std::move(onReachEnd));
}

RefPtr<FrameNode> GridModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::GRID_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<GridPattern>(); });

    return frameNode;
}

void GridModelNG::SetOnScrollIndex(FrameNode* frameNode, ScrollIndexFunc&& onScrollIndex)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollIndex(std::move(onScrollIndex));
}

void GridModelNG::SetColumnsTemplate(FrameNode* frameNode, const std::string& columnsTemplate)
{
    if (columnsTemplate.empty()) {
        TAG_LOGW(AceLogTag::ACE_GRID, "Columns Template [%{public}s] is not valid.", columnsTemplate.c_str());
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, ColumnsTemplate, "1fr", frameNode);
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, ColumnsTemplate, columnsTemplate, frameNode);
}

void GridModelNG::SetRowsTemplate(FrameNode* frameNode, const std::string& rowsTemplate)
{
    if (rowsTemplate.empty()) {
        TAG_LOGW(AceLogTag::ACE_GRID, "Rows Template [%{public}s] is not valid.", rowsTemplate.c_str());
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, RowsTemplate, "1fr", frameNode);
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, RowsTemplate, rowsTemplate, frameNode);
}

void GridModelNG::SetColumnsGap(FrameNode* frameNode, const Dimension& columnsGap)
{
    if (columnsGap.IsNonNegative()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, ColumnsGap, columnsGap, frameNode);
    }
}

void GridModelNG::SetRowsGap(FrameNode* frameNode, const Dimension& rowsGap)
{
    if (rowsGap.IsNonNegative()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, RowsGap, rowsGap, frameNode);
    }
}

void GridModelNG::SetScrollBarMode(FrameNode* frameNode, const std::optional<DisplayMode>& scrollBarMode)
{
    if (scrollBarMode) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarMode, scrollBarMode.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarMode, frameNode);
    }
}

void GridModelNG::SetScrollBarWidth(FrameNode* frameNode, const std::optional<Dimension>& scrollBarWidth)
{
    if (scrollBarWidth &&
        GreatOrEqual(scrollBarWidth.value().Value(), 0.0f) &&
        scrollBarWidth.value().Unit() != DimensionUnit::PERCENT) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarWidth, scrollBarWidth.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarWidth, frameNode);
    }
}

void GridModelNG::SetScrollBarColor(FrameNode* frameNode, const std::optional<Color>& scrollBarColor)
{
    if (scrollBarColor) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarColor, scrollBarColor.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarColor, frameNode);
    }
}

void GridModelNG::SetCachedCount(FrameNode* frameNode, int32_t cachedCount)
{
    if (cachedCount >= 0) {
        int32_t count = cachedCount;
        if (SystemProperties::IsWhiteBlockEnabled()) {
            count = ScrollAdjustmanager::GetInstance().AdjustCachedCount(count);
        }
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, CachedCount, count, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridLayoutProperty, CachedCount, frameNode);
    }
}

void GridModelNG::SetShowCached(FrameNode* frameNode, bool show)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, ShowCachedItems, show, frameNode);
}

void GridModelNG::SetEditable(FrameNode* frameNode, bool editMode)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, Editable, editMode, frameNode);
}

void GridModelNG::SetMultiSelectable(FrameNode* frameNode, bool multiSelectable)
{
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMultiSelectable(multiSelectable);
}

void GridModelNG::SetMaxCount(FrameNode* frameNode, int32_t maxCount)
{
    if (maxCount >= 1) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, MaxCount, maxCount, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridLayoutProperty, MaxCount, frameNode);
    }
}

void GridModelNG::SetMinCount(FrameNode* frameNode, int32_t minCount)
{
    if (minCount >= 1) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, MinCount, minCount, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridLayoutProperty, MinCount, frameNode);
    }
}

void GridModelNG::SetCellLength(FrameNode* frameNode, int32_t cellLength)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, CellLength, cellLength, frameNode);
}

void GridModelNG::SetLayoutDirection(FrameNode* frameNode, const std::optional<FlexDirection>& layoutDirection)
{
    if (layoutDirection) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, GridDirection, layoutDirection.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridLayoutProperty, GridDirection, frameNode);
    }
}

void GridModelNG::SetSupportAnimation(FrameNode* frameNode, bool supportAnimation)
{
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSupportAnimation(supportAnimation);
}

EdgeEffect GridModelNG::GetEdgeEffect(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, EdgeEffect::NONE);
    return static_cast<EdgeEffect>(ScrollableModelNG::GetEdgeEffect(frameNode));
}

bool GridModelNG::GetAlwaysEnabled(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<bool>(ScrollableModelNG::GetAlwaysEnabled(frameNode));
}

void GridModelNG::SetEdgeEffect(
    FrameNode* frameNode, const std::optional<EdgeEffect>& edgeEffect, const std::optional<bool>& alwaysEnabled,
    EffectEdge edge)
{
    ScrollableModelNG::SetEdgeEffect(frameNode,
        edgeEffect.value_or(GetEdgeEffect(frameNode)), alwaysEnabled.value_or(GetAlwaysEnabled(frameNode)), edge);
}

void GridModelNG::SetNestedScroll(FrameNode* frameNode, const NestedScrollOptions& nestedOpt)
{
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNestedScroll(nestedOpt);
}

void GridModelNG::SetScrollEnabled(FrameNode* frameNode, bool scrollEnabled)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, ScrollEnabled, scrollEnabled, frameNode);
}

void GridModelNG::SetFriction(FrameNode* frameNode, const std::optional<double>& value)
{
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    std::optional<double> friction = value;
    if (friction.has_value() && LessOrEqual(friction.value(), 0.0f)) {
        friction.reset();
    }
    pattern->SetFriction(friction.value_or(-1.0f));
}

void GridModelNG::SetFocusWrapMode(FrameNode* frameNode, const std::optional<FocusWrapMode>& focusWrapMode)
{
    if (focusWrapMode) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, FocusWrapMode, focusWrapMode.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridLayoutProperty, FocusWrapMode, frameNode);
    }
}

void GridModelNG::SetAlignItems(FrameNode* frameNode, const std::optional<GridItemAlignment>& itemAlign)
{
    if (itemAlign) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, AlignItems, itemAlign.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(GridLayoutProperty, AlignItems, frameNode);
    }
}

RefPtr<ScrollControllerBase> GridModelNG::CreatePositionController()
{
    return AceType::MakeRefPtr<ScrollableController>();
}

RefPtr<ScrollProxy> GridModelNG::CreateScrollBarProxy()
{
    return AceType::MakeRefPtr<NG::ScrollBarProxy>();
}

DisplayMode GridModelNG::GetDisplayMode() const
{
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<GridPattern>();
    CHECK_NULL_RETURN(pattern, DisplayMode::AUTO);
    return pattern->GetDefaultScrollBarDisplayMode();
}

std::string GridModelNG::GetColumnsTemplate(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    std::string value = "1fr";
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(GridLayoutProperty, ColumnsTemplate, value, frameNode, value);
    return value;
}

std::string GridModelNG::GetRowsTemplate(FrameNode* frameNode)
{
    std::string value = "1fr";
    CHECK_NULL_RETURN(frameNode, nullptr);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(GridLayoutProperty, RowsTemplate, value, frameNode, value);
    return value;
}

float GridModelNG::GetColumnsGap(FrameNode* frameNode)
{
    Dimension value;
    CHECK_NULL_RETURN(frameNode, value.Value());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(GridLayoutProperty, ColumnsGap, value, frameNode, value);
    return value.Value();
}

float GridModelNG::GetRowsGap(FrameNode* frameNode)
{
    Dimension value;
    CHECK_NULL_RETURN(frameNode, value.Value());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(GridLayoutProperty, RowsGap, value, frameNode, value);
    return value.Value();
}

int32_t GridModelNG::GetCachedCount(FrameNode* frameNode)
{
    int32_t cachedCount = 1;
    CHECK_NULL_RETURN(frameNode, cachedCount);
    auto pattern = frameNode->GetPattern<GridPattern>();
    int32_t defCachedCount = pattern != nullptr ? pattern->GetDefaultCachedCount() : 1;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(GridLayoutProperty, CachedCount, cachedCount, frameNode,
        defCachedCount);
    return cachedCount;
}

bool GridModelNG::GetShowCached(FrameNode* frameNode)
{
    bool show = false;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(GridLayoutProperty, ShowCachedItems, show, frameNode, false);
    return show;
}

void GridModelNG::InitScroller(FrameNode* frameNode, const RefPtr<ScrollControllerBase>& positionController,
    const RefPtr<ScrollProxy>& scrollProxy)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    if (positionController) {
        auto controller = AceType::DynamicCast<ScrollableController>(positionController);
        pattern->SetPositionController(controller);
    } else {
        pattern->SetPositionController(nullptr);
    }
    if (scrollProxy) {
        auto scrollBarProxy = AceType::DynamicCast<NG::ScrollBarProxy>(scrollProxy);
        pattern->SetScrollBarProxy(scrollBarProxy);
    } else {
        pattern->SetScrollBarProxy(nullptr);
    }
    pattern->AddScrollableFrameInfo(SCROLL_FROM_NONE);
}

void GridModelNG::SetLayoutOptions(FrameNode* frameNode, GridLayoutOptions& options)
{
    // only support regularSize(1, 1)
    options.regularSize.rows = 1;
    options.regularSize.columns = 1;

    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, LayoutOptions, options, frameNode);
}

void GridModelNG::SetOnScrollBarUpdate(FrameNode* frameNode, ScrollBarUpdateFunc&& value)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollBarUpdate(std::move(value));
}

void GridModelNG::SetOnItemDragStart(FrameNode* frameNode, std::function<void(const ItemDragInfo&, int32_t)>&& value)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
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

    GridModelNG::AddDragFrameNodeToManager(frameNode);
}

void GridModelNG::SetOnItemDragEnter(FrameNode* frameNode, ItemDragEnterFunc&& value)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragEnter(std::move(value));

    GridModelNG::AddDragFrameNodeToManager(frameNode);
}

void GridModelNG::SetOnItemDragMove(FrameNode* frameNode, ItemDragMoveFunc&& value)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragMove(std::move(value));

    AddDragFrameNodeToManager(frameNode);
}

void GridModelNG::SetOnItemDragLeave(FrameNode* frameNode, ItemDragLeaveFunc&& value)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDragLeave(std::move(value));

    AddDragFrameNodeToManager(frameNode);
}

void GridModelNG::SetOnItemDrop(FrameNode* frameNode, ItemDropFunc&& value)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnItemDrop(std::move(value));

    AddDragFrameNodeToManager(frameNode);
}

void GridModelNG::AddDragFrameNodeToManager(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto dragDropManager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);

    dragDropManager->AddGridDragFrameNode(frameNode->GetId(), AceType::WeakClaim(frameNode));
}

void GridModelNG::CreateWithResourceObjFriction(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("GridFriction");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern))](const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        double friction = -1.0;
        ResourceParseUtils::ParseResDouble(resObj, friction);
        pattern->SetFriction(friction);
    };
    pattern->AddResObj("GridFriction", resObj, std::move(updateFunc));
}

void GridModelNG::CreateWithResourceObjScrollBarColor(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithResourceObjScrollBarColor(frameNode, resObj);
}

void GridModelNG::SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& onScrollFrameBegin)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollFrameBegin(std::move(onScrollFrameBegin));
}

void GridModelNG::SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachStart(std::move(onReachStart));
}

void GridModelNG::SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachEnd(std::move(onReachEnd));
}

void GridModelNG::SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& onScrollStart)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStart(std::move(onScrollStart));
}

void GridModelNG::SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& onScrollStop)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStop(std::move(onScrollStop));
}

void GridModelNG::SetOnScroll(FrameNode* frameNode, OnScrollEvent&& onScroll)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<GridEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScroll(std::move(onScroll));
}

void GridModelNG::CreateWithResourceObjFriction(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("GridFriction");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern))](const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        double friction = -1.0;
        ResourceParseUtils::ParseResDouble(resObj, friction);
        pattern->SetFriction(friction);
    };
    pattern->AddResObj("GridFriction", resObj, std::move(updateFunc));
}

void GridModelNG::CreateWithResourceObjScrollBarColor(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    ScrollableModelNG::CreateWithResourceObjScrollBarColor(frameNode, resObj);
}

void GridModelNG::SetSyncLoad(bool syncLoad)
{
    ACE_UPDATE_LAYOUT_PROPERTY(GridLayoutProperty, SyncLoad, syncLoad);
}

void GridModelNG::SetSyncLoad(FrameNode* frameNode, bool syncLoad)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(GridLayoutProperty, SyncLoad, syncLoad, frameNode);
}

bool GridModelNG::GetSyncLoad(FrameNode* frameNode)
{
    bool result = true;
    CHECK_NULL_RETURN(frameNode, result);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(GridLayoutProperty, SyncLoad, result, frameNode, true);
    return result;
}
} // namespace OHOS::Ace::NG
