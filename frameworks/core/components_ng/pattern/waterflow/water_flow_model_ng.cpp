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
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#include "core/components_ng/pattern/waterflow/water_flow_position_controller.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "frameworks/core/components_ng/pattern/scroll_bar/proxy/scroll_bar_proxy.h"

namespace OHOS::Ace::NG {
void WaterFlowModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
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
    CHECK_NULL_VOID_NOLOG(footerNode);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->AddFooter(footerNode);
}

RefPtr<ScrollControllerBase> WaterFlowModelNG::CreateScrollController()
{
    return AceType::MakeRefPtr<WaterFlowPositionController>();
}

RefPtr<ScrollProxy> WaterFlowModelNG::CreateScrollBarProxy()
{
    return AceType::MakeRefPtr<NG::ScrollBarProxy>();
}

void WaterFlowModelNG::SetScroller(RefPtr<ScrollControllerBase> scroller, RefPtr<ScrollProxy> proxy)
{
    auto waterFlow = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WaterFlowPattern>();
    CHECK_NULL_VOID(waterFlow);
    waterFlow->SetPositionController(AceType::DynamicCast<WaterFlowPositionController>(scroller));
    waterFlow->SetScrollBarProxy(AceType::DynamicCast<ScrollBarProxy>(proxy));
}

void WaterFlowModelNG::SetColumnsTemplate(const std::string& value)
{
    if (value.empty()) {
        LOGE("Columns Template [%{public}s] is not valid.", value.c_str());
        ACE_UPDATE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ColumnsTemplate, "1fr");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, ColumnsTemplate, value);
}

void WaterFlowModelNG::SetRowsTemplate(const std::string& value)
{
    if (value.empty()) {
        LOGE("Rows Template [%{public}s] is not valid.", value.c_str());
        ACE_UPDATE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, RowsTemplate, "1fr");
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(WaterFlowLayoutProperty, RowsTemplate, value);
}

void WaterFlowModelNG::SetItemMinWidth(const Dimension& minWidth)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        LOGD("current state is not processed, return");
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
        LOGD("current state is not processed, return");
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
        LOGD("current state is not processed, return");
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
        LOGD("current state is not processed, return");
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
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<WaterFlowEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachStart(std::move(onReachStart));
}

void WaterFlowModelNG::SetOnReachEnd(OnReachEvent&& onReachEnd)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<WaterFlowEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachEnd(std::move(onReachEnd));
}

void WaterFlowModelNG::SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& ScrollFrameBegin)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<WaterFlowEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollFrameBegin(std::move(ScrollFrameBegin));
}
} // namespace OHOS::Ace::NG
