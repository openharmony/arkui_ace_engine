/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"

#include <string>
#include "base/geometry/dimension.h"
#include "base/utils/system_properties.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_controller.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/manager/scroll_adjust/scroll_adjust_manager.h"

namespace OHOS::Ace::NG {

void WaterFlowModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::WATERFLOW_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::WATERFLOW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WaterFlowPattern>(); });
    stack->Push(frameNode);
}

RefPtr<FrameNode> WaterFlowModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::WATERFLOW_ETS_TAG, nodeId, AceType::MakeRefPtr<WaterFlowPattern>());
    return frameNode;
}

RefPtr<ScrollControllerBase> WaterFlowModelNG::GetOrCreateController(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    if (!pattern->GetPositionController()) {
        auto controller = AceType::MakeRefPtr<ScrollableController>();
        pattern->SetPositionController(controller);
        controller->SetScrollPattern(pattern);
        pattern->TriggerModifyDone();
    }
    return pattern->GetPositionController();
}

void WaterFlowModelNG::SetFooter(std::function<void()>&& footer)
{
    RefPtr<NG::UINode> footerNode;
    if (footer) {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        footer();
        footerNode = NG::ViewStackProcessor::GetInstance()->Finish();
    }
    CHECK_NULL_VOID(footerNode);
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddFooter(footerNode);
}

void WaterFlowModelNG::SetFooterWithFrameNode(const RefPtr<NG::UINode>& footer)
{
    auto* frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddFooter(footer);
}

RefPtr<ScrollControllerBase> WaterFlowModelNG::CreateScrollController()
{
    return AceType::MakeRefPtr<ScrollableController>();
}

RefPtr<ScrollProxy> WaterFlowModelNG::CreateScrollBarProxy()
{
    return AceType::MakeRefPtr<NG::ScrollBarProxy>();
}

void WaterFlowModelNG::SetScroller(RefPtr<ScrollControllerBase> scroller, RefPtr<ScrollProxy> proxy)
{
    auto waterFlow = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WaterFlowPattern>();
    CHECK_NULL_VOID(waterFlow);
    waterFlow->SetPositionController(AceType::DynamicCast<ScrollableController>(scroller));
    waterFlow->SetScrollBarProxy(AceType::DynamicCast<ScrollBarProxy>(proxy));
}

void WaterFlowModelNG::SetLayoutMode(WaterFlowLayoutMode mode)
{
    auto waterFlow = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WaterFlowPattern>();
    CHECK_NULL_VOID(waterFlow);
    waterFlow->SetLayoutMode(mode);
}

void WaterFlowModelNG::SetColumnsTemplate(const std::string& value)
{
    if (value.empty()) {
        TAG_LOGW(AceLogTag::ACE_WATERFLOW, "Columns Template [%{public}s] is not valid.", value.c_str());
        ACE_UPDATE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ColumnsTemplate, "1fr");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ColumnsTemplate, value);
}

void WaterFlowModelNG::SetRowsTemplate(const std::string& value)
{
    if (value.empty()) {
        TAG_LOGW(AceLogTag::ACE_WATERFLOW, "Rows Template [%{public}s] is not valid.", value.c_str());
        ACE_UPDATE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, RowsTemplate, "1fr");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, RowsTemplate, value);
}

void WaterFlowModelNG::SetItemMinWidth(const Dimension& minWidth)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateItemMinSize(CalcSize(CalcLength(minWidth), std::nullopt));
}

void WaterFlowModelNG::SetItemMinHeight(const Dimension& minHeight)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateItemMinSize(CalcSize(std::nullopt, CalcLength(minHeight)));
}

void WaterFlowModelNG::SetItemMaxWidth(const Dimension& maxWidth)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateItemMaxSize(CalcSize(CalcLength(maxWidth), std::nullopt));
}

void WaterFlowModelNG::SetItemMaxHeight(const Dimension& maxHeight)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateItemMaxSize(CalcSize(std::nullopt, CalcLength(maxHeight)));
}

void WaterFlowModelNG::SetColumnsGap(const Dimension& value)
{
    if (value.IsNonNegative()) {
        ACE_UPDATE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ColumnsGap, value);
    }
}

void WaterFlowModelNG::SetRowsGap(const Dimension& value)
{
    if (value.IsNonNegative()) {
        ACE_UPDATE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, RowsGap, value);
    }
}

void WaterFlowModelNG::SetLayoutDirection(FlexDirection value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, WaterflowDirection, value);
}

void WaterFlowModelNG::SetNestedScroll(const NestedScrollOptions& nestedOpt)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNestedScroll(nestedOpt);
}

void WaterFlowModelNG::SetScrollEnabled(bool scrollEnabled)
{
    ACE_UPDATE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ScrollEnabled, scrollEnabled);
}

void WaterFlowModelNG::SetOnReachStart(OnReachEvent&& onReachStart)
{
    ScrollableModelNG::SetOnReachStart(std::move(onReachStart));
}

void WaterFlowModelNG::SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart)
{
    ScrollableModelNG::SetOnReachStart(frameNode, std::move(onReachStart));
}

void WaterFlowModelNG::SetOnReachEnd(OnReachEvent&& onReachEnd)
{
    ScrollableModelNG::SetOnReachEnd(std::move(onReachEnd));
}

void WaterFlowModelNG::SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd)
{
    ScrollableModelNG::SetOnReachEnd(frameNode, std::move(onReachEnd));
}

void WaterFlowModelNG::SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& ScrollFrameBegin)
{
    ScrollableModelNG::SetOnScrollFrameBegin(std::move(ScrollFrameBegin));
}

void WaterFlowModelNG::SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& ScrollFrameBegin)
{
    ScrollableModelNG::SetOnScrollFrameBegin(frameNode, std::move(ScrollFrameBegin));
}

void WaterFlowModelNG::SetOnScroll(std::function<void(Dimension, ScrollState)>&& onScroll)
{
    ScrollableModelNG::SetOnScroll(std::move(onScroll));
}

void WaterFlowModelNG::SetOnScroll(FrameNode* frameNode, std::function<void(Dimension, ScrollState)>&& onScroll)
{
    ScrollableModelNG::SetOnScroll(frameNode, std::move(onScroll));
}

void WaterFlowModelNG::SetOnScrollStart(OnScrollStartEvent&& onScrollStart)
{
    ScrollableModelNG::SetOnScrollStart(std::move(onScrollStart));
}

void WaterFlowModelNG::SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& onScrollStart)
{
    ScrollableModelNG::SetOnScrollStart(frameNode, std::move(onScrollStart));
}

void WaterFlowModelNG::SetOnScrollStop(OnScrollStopEvent&& onScrollStop)
{
    ScrollableModelNG::SetOnScrollStop(std::move(onScrollStop));
}

void WaterFlowModelNG::SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& onScrollStop)
{
    ScrollableModelNG::SetOnScrollStop(frameNode, std::move(onScrollStop));
}

void WaterFlowModelNG::SetOnScrollIndex(ScrollIndexFunc&& onScrollIndex)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<WaterFlowEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollIndex(std::move(onScrollIndex));
}

void WaterFlowModelNG::SetOnScrollIndex(FrameNode* frameNode, ScrollIndexFunc&& onScrollIndex)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<WaterFlowEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollIndex(std::move(onScrollIndex));
}

void WaterFlowModelNG::SetFriction(double friction)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFriction(friction);
}

void WaterFlowModelNG::SetCachedCount(int32_t value, bool show)
{
    int32_t count = value;
    if (SystemProperties::IsWhiteBlockEnabled()) {
        count = ScrollAdjustmanager::GetInstance().AdjustCachedCount(count);
    }
    ACE_UPDATE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, CachedCount, count);
    ACE_UPDATE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ShowCachedItems, show);
}

void WaterFlowModelNG::SetCachedCount(FrameNode* frameNode, const std::optional<int32_t>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        int32_t count = value.value();
        if (SystemProperties::IsWhiteBlockEnabled()) {
            count = ScrollAdjustmanager::GetInstance().AdjustCachedCount(count);
        }
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, CachedCount, count, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, CachedCount, frameNode);
    }
}

int32_t WaterFlowModelNG::GetCachedCount(FrameNode* frameNode)
{
    int32_t cachedCount = 1;
    CHECK_NULL_RETURN(frameNode, cachedCount);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    int32_t defCachedCount = pattern != nullptr ? pattern->GetDefaultCachedCount() : 1;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(WaterFlowLayoutProperty, CachedCount, cachedCount, frameNode,
        defCachedCount);
    return cachedCount;
}

void WaterFlowModelNG::SetShowCached(FrameNode* frameNode, bool show)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ShowCachedItems, show, frameNode);
}

int32_t WaterFlowModelNG::GetShowCached(FrameNode* frameNode)
{
    bool show = false;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(WaterFlowLayoutProperty, ShowCachedItems, show, frameNode, false);
    return show;
}

void WaterFlowModelNG::SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled, EffectEdge edge)
{
    ScrollableModelNG::SetEdgeEffect(edgeEffect, alwaysEnabled, edge);
}

void WaterFlowModelNG::SetScrollBarMode(DisplayMode value)
{
    ScrollableModelNG::SetScrollBarMode(value);
}

void WaterFlowModelNG::SetScrollBarMode(FrameNode* frameNode, DisplayMode value)
{
    ScrollableModelNG::SetScrollBarMode(frameNode, static_cast<int32_t>(value));
}

int32_t WaterFlowModelNG::GetScrollBarMode(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return static_cast<int32_t>(
        frameNode->GetPaintProperty<ScrollablePaintProperty>()->GetScrollBarMode().value_or(DisplayMode::AUTO));
}

void WaterFlowModelNG::SetScrollBarColor(const std::string& value)
{
    ScrollableModelNG::SetScrollBarColor(value);
}

void WaterFlowModelNG::SetScrollBarColor(FrameNode* frameNode, const std::string& value)
{
    ScrollableModelNG::SetScrollBarColor(frameNode, value);
}

uint32_t WaterFlowModelNG::GetScrollBarColor(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    auto value = frameNode->GetPaintProperty<ScrollablePaintProperty>()->GetBarColor();
    return value.GetValue();
}

void WaterFlowModelNG::SetScrollBarWidth(const std::string& value)
{
    ScrollableModelNG::SetScrollBarWidth(value);
}

void WaterFlowModelNG::SetScrollBarWidth(FrameNode* frameNode, const std::string& value)
{
    ScrollableModelNG::SetScrollBarWidth(frameNode, value);
}

float WaterFlowModelNG::GetScrollBarWidth(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0.0f);
    auto value = frameNode->GetPaintProperty<ScrollablePaintProperty>()->GetBarWidth();
    return value.ConvertToVp();
}

void WaterFlowModelNG::SetSyncLoad(bool syncLoad)
{
    ACE_UPDATE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, SyncLoad, syncLoad);
}

void WaterFlowModelNG::SetSyncLoad(FrameNode* frameNode, bool syncLoad)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, SyncLoad, syncLoad, frameNode);
}

bool WaterFlowModelNG::GetSyncLoad(FrameNode* frameNode)
{
    bool result = true;
    CHECK_NULL_RETURN(frameNode, result);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(WaterFlowLayoutProperty, SyncLoad, result, frameNode, true);
    return result;
}

RefPtr<WaterFlowSections> WaterFlowModelNG::GetOrCreateWaterFlowSections()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetOrCreateWaterFlowSections();
}

RefPtr<WaterFlowSections> WaterFlowModelNG::GetOrCreateWaterFlowSections(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetOrCreateWaterFlowSections();
}

void WaterFlowModelNG::ResetSections()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ResetSections();
}

void WaterFlowModelNG::ResetSections(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ResetSections();
}

void WaterFlowModelNG::SetColumnsTemplate(FrameNode* frameNode, const std::string& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.empty()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ColumnsTemplate, "1fr", frameNode);
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ColumnsTemplate, value, frameNode);
}

void WaterFlowModelNG::SetRowsTemplate(FrameNode* frameNode, const std::string& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.empty()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, RowsTemplate, "1fr", frameNode);
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, RowsTemplate, value, frameNode);
}

void WaterFlowModelNG::SetScrollEnabled(FrameNode* frameNode, bool scrollEnabled)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ScrollEnabled, scrollEnabled, frameNode);
}

void WaterFlowModelNG::SetColumnsGap(FrameNode* frameNode, const Dimension& value)
{
    if (value.IsNonNegative()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ColumnsGap, value, frameNode);
    }
}

void WaterFlowModelNG::SetColumnsGap(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ColumnsGap, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ColumnsGap, frameNode);
    }
}

void WaterFlowModelNG::SetRowsGap(FrameNode* frameNode, const Dimension& value)
{
    if (value.IsNonNegative()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, RowsGap, value, frameNode);
    }
}

void WaterFlowModelNG::SetRowsGap(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, RowsGap, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, RowsGap, frameNode);
    }
}

void WaterFlowModelNG::SetItemMinWidth(FrameNode* frameNode, const std::optional<Dimension>& minWidth)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateItemMinSize(CalcSize(minWidth ? std::optional(CalcLength(*minWidth)) : std::nullopt,
        std::nullopt));
}

void WaterFlowModelNG::SetItemMinHeight(FrameNode* frameNode, const std::optional<Dimension>& minHeight)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateItemMinSize(CalcSize(std::nullopt,
        minHeight ? std::optional(CalcLength(*minHeight)) : std::nullopt));
}

void WaterFlowModelNG::SetItemMaxWidth(FrameNode* frameNode, const std::optional<Dimension>& maxWidth)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateItemMaxSize(CalcSize(maxWidth ? std::optional(CalcLength(*maxWidth)) : std::nullopt,
        std::nullopt));
}

void WaterFlowModelNG::SetItemMaxHeight(FrameNode* frameNode, const std::optional<Dimension>& maxHeight)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateItemMaxSize(CalcSize(std::nullopt,
        maxHeight ? std::optional(CalcLength(*maxHeight)) : std::nullopt));
}

void WaterFlowModelNG::SetLayoutDirection(FrameNode* frameNode, const std::optional<FlexDirection>& value)
{
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, WaterflowDirection, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, WaterflowDirection, frameNode);
    }
}

void WaterFlowModelNG::SetNestedScroll(FrameNode* frameNode, const NestedScrollOptions& nestedOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNestedScroll(nestedOpt);
}

void WaterFlowModelNG::SetFriction(FrameNode* frameNode, const std::optional<double>& friction)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFriction(friction.value_or(-1.0f));
}

FlexDirection WaterFlowModelNG::GetLayoutDirection(FrameNode* frameNode)
{
    FlexDirection value = FlexDirection::COLUMN;
    CHECK_NULL_RETURN(frameNode, value);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        WaterFlowLayoutProperty, WaterflowDirection, value, frameNode, value);
    return value;
}

std::string WaterFlowModelNG::GetColumnsTemplate(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    std::string value = "1fr";
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(WaterFlowLayoutProperty, ColumnsTemplate, value, frameNode, value);
    return value;
}

std::string WaterFlowModelNG::GetRowsTemplate(FrameNode* frameNode)
{
    std::string value = "1fr";
    CHECK_NULL_RETURN(frameNode, nullptr);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(WaterFlowLayoutProperty, RowsTemplate, value, frameNode, value);
    return value;
}

float WaterFlowModelNG::GetColumnsGap(FrameNode* frameNode)
{
    Dimension value;
    CHECK_NULL_RETURN(frameNode, value.Value());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(WaterFlowLayoutProperty, ColumnsGap, value, frameNode, value);
    return value.Value();
}

float WaterFlowModelNG::GetRowsGap(FrameNode* frameNode)
{
    Dimension value;
    CHECK_NULL_RETURN(frameNode, value.Value());
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(WaterFlowLayoutProperty, RowsGap, value, frameNode, value);
    return value.Value();
}

NestedScrollOptions WaterFlowModelNG::GetNestedScroll(FrameNode* frameNode)
{
    NestedScrollOptions defaultOptions;
    CHECK_NULL_RETURN(frameNode, defaultOptions);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_RETURN(pattern, defaultOptions);
    return pattern->GetNestedScroll();
}

void WaterFlowModelNG::SetEdgeEffect(
    FrameNode* frameNode, EdgeEffect edgeEffect, bool alwaysEnabled, EffectEdge edge)
{
    ScrollableModelNG::SetEdgeEffect(frameNode, edgeEffect, alwaysEnabled, edge);
}
float WaterFlowModelNG::GetFriction(FrameNode* frameNode)
{
    double value = 0.0;
    CHECK_NULL_RETURN(frameNode, value);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_RETURN(pattern, value);
    return pattern->GetFriction();
}

int32_t WaterFlowModelNG::GetEdgeEffect(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    return ScrollableModelNG::GetEdgeEffect(frameNode);
}

int32_t WaterFlowModelNG::GetEdgeEffectAlways(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0.0f);
    return ScrollableModelNG::GetAlwaysEnabled(frameNode);
}

Dimension WaterFlowModelNG::GetItemMinWidth(FrameNode* frameNode)
{
    Dimension value = Dimension(0.0f);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, value);
    auto size = layoutProperty->GetItemMinSize();
    if (size.has_value()) {
        auto width = size->Width();
        if (width.has_value()) {
            return width.value().GetDimension();
        }
    }
    return value;
}

Dimension WaterFlowModelNG::GetItemMaxWidth(FrameNode* frameNode)
{
    Dimension value = Dimension(0.0f);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, value);
    auto size = layoutProperty->GetItemMaxSize();
    if (size.has_value()) {
        auto width = size->Width();
        if (width.has_value()) {
            return width.value().GetDimension();
        }
    }
    return value;
}

Dimension WaterFlowModelNG::GetItemMinHeight(FrameNode* frameNode)
{
    Dimension value = Dimension(0.0f);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, value);
    auto size = layoutProperty->GetItemMinSize();
    if (size.has_value()) {
        auto height = size->Height();
        if (height.has_value()) {
            return height.value().GetDimension();
        }
    }
    return value;
}

Dimension WaterFlowModelNG::GetItemMaxHeight(FrameNode* frameNode)
{
    Dimension value = Dimension(0.0f);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, value);
    auto size = layoutProperty->GetItemMaxSize();
    if (size.has_value()) {
        auto height = size->Height();
        if (height.has_value()) {
            return height.value().GetDimension();
        }
    }
    return value;
}

bool WaterFlowModelNG::GetScrollEnabled(FrameNode* frameNode)
{
    bool value = true;
    CHECK_NULL_RETURN(frameNode, value);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(WaterFlowLayoutProperty, ScrollEnabled, value, frameNode, value);
    return value;
}

void WaterFlowModelNG::SetScrollToIndex(FrameNode* frameNode, int32_t index, int32_t animation, int32_t alignment)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ScrollToIndex(index, animation, static_cast<ScrollAlign>(alignment));
}

void WaterFlowModelNG::SetWaterflowFooter(FrameNode* frameNode, FrameNode* footerNode)
{
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddFooter(AceType::Claim<UINode>(footerNode));
}

void WaterFlowModelNG::SetWaterflowFooterWithFrameNode(FrameNode* frameNode, const RefPtr<NG::UINode>& footer)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddFooter(footer);
}

bool WaterFlowModelNG::hasFooter(FrameNode* frameNode)
{
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->hasFooter();
}

void WaterFlowModelNG::SetFlingSpeedLimit(FrameNode* frameNode, double maxSpeed)
{
    ScrollableModelNG::SetMaxFlingSpeed(frameNode, maxSpeed);
}

void WaterFlowModelNG::SetScroller(
    FrameNode* frameNode, RefPtr<ScrollControllerBase> scroller, RefPtr<ScrollProxy> proxy)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetPositionController(AceType::DynamicCast<ScrollableController>(scroller));
    pattern->SetScrollBarProxy(AceType::DynamicCast<ScrollBarProxy>(proxy));
}

void WaterFlowModelNG::SetLayoutMode(FrameNode* frameNode, WaterFlowLayoutMode mode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetLayoutMode(mode);
}

WaterFlowLayoutMode WaterFlowModelNG::GetLayoutMode(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, WaterFlowLayoutMode::TOP_DOWN);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_RETURN(pattern, WaterFlowLayoutMode::TOP_DOWN);
    return pattern->GetLayoutMode();
}

void WaterFlowModelNG::ParseResObjFriction(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    ParseResObjFriction(frameNode, resObj);
}

void WaterFlowModelNG::ParseResObjFriction(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj("waterflow.Friction");
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(pattern))](const RefPtr<ResourceObject>& resObj) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        double friction = -1.0;
        ResourceParseUtils::ParseResDouble(resObj, friction);
        pattern->SetFriction(friction);
    };
    pattern->AddResObj("waterflow.Friction", resObj, std::move(updateFunc));
}

void WaterFlowModelNG::SetFooter(FrameNode* frameNode, std::function<void()>&& footer)
{
    CHECK_NULL_VOID(frameNode);
    RefPtr<NG::UINode> footerNode;
    if (footer) {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        footer();
        footerNode = NG::ViewStackProcessor::GetInstance()->Finish();
    }
    CHECK_NULL_VOID(footerNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddFooter(footerNode);
}
} // namespace OHOS::Ace::NG
