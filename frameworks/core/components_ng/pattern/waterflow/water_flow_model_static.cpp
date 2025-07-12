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

#include "core/components_ng/pattern/waterflow/water_flow_model_static.h"

#include "base/geometry/dimension.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/scrollable/scrollable_controller.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> WaterFlowModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::WATERFLOW_ETS_TAG, nodeId, AceType::MakeRefPtr<WaterFlowPattern>());
    return frameNode;
}

RefPtr<ScrollControllerBase> WaterFlowModelStatic::GetOrCreateController(FrameNode* frameNode)
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

RefPtr<ScrollProxy> WaterFlowModelStatic::GetOrCreateScrollBarProxy(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    if (!pattern->GetScrollBarProxy()) {
        auto proxy = AceType::MakeRefPtr<NG::ScrollBarProxy>();
        pattern->SetScrollBarProxy(proxy);
        pattern->TriggerModifyDone();
    }
    return pattern->GetScrollBarProxy();
}

void WaterFlowModelStatic::SetFooter(FrameNode* frameNode, const RefPtr<NG::UINode>& footer)
{
    CHECK_NULL_VOID(footer);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddFooter(footer);
}

void WaterFlowModelStatic::SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart)
{
    ScrollableModelNG::SetOnReachStart(frameNode, std::move(onReachStart));
}

void WaterFlowModelStatic::SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd)
{
    ScrollableModelNG::SetOnReachEnd(frameNode, std::move(onReachEnd));
}

void WaterFlowModelStatic::SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& ScrollFrameBegin)
{
    ScrollableModelNG::SetOnScrollFrameBegin(frameNode, std::move(ScrollFrameBegin));
}

void WaterFlowModelStatic::SetOnScrollIndex(FrameNode* frameNode, ScrollIndexFunc&& onScrollIndex)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<WaterFlowEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollIndex(std::move(onScrollIndex));
}

void WaterFlowModelStatic::SetCachedCount(FrameNode* frameNode, const std::optional<int32_t>& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, CachedCount, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, CachedCount, frameNode);
    }
}

void WaterFlowModelStatic::SetShowCached(FrameNode* frameNode, bool show)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ShowCachedItems, show, frameNode);
}

RefPtr<WaterFlowSections> WaterFlowModelStatic::GetOrCreateWaterFlowSections(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetOrCreateWaterFlowSections();
}

void WaterFlowModelStatic::ResetSections(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ResetSections();
}

void WaterFlowModelStatic::SetColumnsTemplate(FrameNode* frameNode, const std::string& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.empty()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ColumnsTemplate, "1fr", frameNode);
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ColumnsTemplate, value, frameNode);
}

void WaterFlowModelStatic::SetRowsTemplate(FrameNode* frameNode, const std::string& value)
{
    CHECK_NULL_VOID(frameNode);
    if (value.empty()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, RowsTemplate, "1fr", frameNode);
        return;
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, RowsTemplate, value, frameNode);
}

void WaterFlowModelStatic::SetScrollEnabled(FrameNode* frameNode, bool scrollEnabled)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ScrollEnabled, scrollEnabled, frameNode);
}

void WaterFlowModelStatic::SetColumnsGap(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ColumnsGap, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ColumnsGap, frameNode);
    }
}

void WaterFlowModelStatic::SetRowsGap(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, RowsGap, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, RowsGap, frameNode);
    }
}

void WaterFlowModelStatic::SetItemMinWidth(FrameNode* frameNode, const std::optional<Dimension>& minWidth)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateItemMinSize(CalcSize(CalcLength(minWidth.value_or(0.00_vp)), std::nullopt));
}

void WaterFlowModelStatic::SetItemMinHeight(FrameNode* frameNode, const std::optional<Dimension>& minHeight)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateItemMinSize(CalcSize(std::nullopt, CalcLength(minHeight.value_or(0.00_vp))));
}

void WaterFlowModelStatic::SetItemMaxWidth(FrameNode* frameNode, const std::optional<Dimension>& maxWidth)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateItemMaxSize(CalcSize(CalcLength(maxWidth.value_or(0.00_vp)), std::nullopt));
}

void WaterFlowModelStatic::SetItemMaxHeight(FrameNode* frameNode, const std::optional<Dimension>& maxHeight)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<WaterFlowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateItemMaxSize(CalcSize(std::nullopt, CalcLength(maxHeight.value_or(0.00_vp))));
}

void WaterFlowModelStatic::SetLayoutDirection(FrameNode* frameNode, const std::optional<FlexDirection>& value)
{
    if (value) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, WaterflowDirection, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, WaterflowDirection, frameNode);
    }
}

void WaterFlowModelStatic::SetNestedScroll(FrameNode* frameNode, const NestedScrollOptions& nestedOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNestedScroll(nestedOpt);
}

void WaterFlowModelStatic::SetFriction(FrameNode* frameNode, const std::optional<double>& friction)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetFriction(friction.value_or(-1.0f));
}

void WaterFlowModelStatic::SetLayoutMode(FrameNode* frameNode, WaterFlowLayoutMode mode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetLayoutMode(mode);
}
} // namespace OHOS::Ace::NG
