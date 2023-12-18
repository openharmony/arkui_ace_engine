/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"
#include "core/components_ng/pattern/scrollable/scrollable_controller.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

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

void WaterFlowModelNG::SetFooter(std::function<void()>&& footer)
{
    RefPtr<NG::UINode> footerNode;
    if (footer) {
        NG::ScopedViewStackProcessor builderViewStackProcessor;
        footer();
        footerNode = NG::ViewStackProcessor::GetInstance()->Finish();
    }
    CHECK_NULL_VOID(footerNode);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddFooter(footerNode);
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

void WaterFlowModelNG::SetOnReachEnd(OnReachEvent&& onReachEnd)
{
    ScrollableModelNG::SetOnReachEnd(std::move(onReachEnd));
}

void WaterFlowModelNG::SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& ScrollFrameBegin)
{
    ScrollableModelNG::SetOnScrollFrameBegin(std::move(ScrollFrameBegin));
}

void WaterFlowModelNG::SetOnScroll(std::function<void(Dimension, ScrollState)>&& onScroll)
{
    ScrollableModelNG::SetOnScroll(std::move(onScroll));
}

void WaterFlowModelNG::SetOnScrollStart(OnScrollStartEvent&& onScrollStart)
{
    ScrollableModelNG::SetOnScrollStart(std::move(onScrollStart));
}

void WaterFlowModelNG::SetOnScrollStop(OnScrollStopEvent&& onScrollStop)
{
    ScrollableModelNG::SetOnScrollStop(std::move(onScrollStop));
}

void WaterFlowModelNG::SetOnScrollIndex(ScrollIndexFunc&& onScrollIndex)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<WaterFlowEventHub>();
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

void WaterFlowModelNG::SetCachedCount(int32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, CachedCount, value);
}

void WaterFlowModelNG::SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled)
{
    ScrollableModelNG::SetEdgeEffect(edgeEffect, alwaysEnabled);
}

void WaterFlowModelNG::SetScrollBarMode(DisplayMode value)
{
    ScrollableModelNG::SetScrollBarMode(value);
}
void WaterFlowModelNG::SetScrollBarColor(const std::string& value)
{
    ScrollableModelNG::SetScrollBarColor(value);
}
void WaterFlowModelNG::SetScrollBarWidth(const std::string& value)
{
    ScrollableModelNG::SetScrollBarWidth(value);
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
void WaterFlowModelNG::SetRowsGap(FrameNode* frameNode, const Dimension& value)
{
    if (value.IsNonNegative()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, RowsGap, value, frameNode);
    }
}

void WaterFlowModelNG::SetItemMinWidth(FrameNode* frameNode, const Dimension& minWidth)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateItemMinSize(CalcSize(CalcLength(minWidth), std::nullopt));
}

void WaterFlowModelNG::SetItemMinHeight(FrameNode* frameNode, const Dimension& minHeight)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateItemMinSize(CalcSize(std::nullopt, CalcLength(minHeight)));
}

void WaterFlowModelNG::SetItemMaxWidth(FrameNode* frameNode, const Dimension& maxWidth)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateItemMaxSize(CalcSize(CalcLength(maxWidth), std::nullopt));
}

void WaterFlowModelNG::SetItemMaxHeight(FrameNode* frameNode, const Dimension& maxHeight)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateItemMaxSize(CalcSize(std::nullopt, CalcLength(maxHeight)));
}

void WaterFlowModelNG::SetLayoutDirection(FrameNode* frameNode, FlexDirection value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, WaterflowDirection, value, frameNode);
}

void WaterFlowModelNG::SetNestedScroll(FrameNode* frameNode, const NestedScrollOptions& nestedOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNestedScroll(nestedOpt);
}

void WaterFlowModelNG::SetFriction(FrameNode* frameNode, double friction)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFriction(friction);
}
} // namespace OHOS::Ace::NG
