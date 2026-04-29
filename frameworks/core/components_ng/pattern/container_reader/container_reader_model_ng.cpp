/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/container_reader/container_reader_model_ng.h"

#include "base/geometry/ng/size_t.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/container_reader/container_reader_event_hub.h"
#include "core/components_ng/pattern/container_reader/container_reader_layout_property.h"
#include "core/components_ng/pattern/container_reader/container_reader_pattern.h"

namespace OHOS::Ace::NG {

void ContainerReaderModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", "ContainerReader", nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        "ContainerReader", nodeId, []() { return AceType::MakeRefPtr<ContainerReaderPattern>(); });
    stack->Push(frameNode);
}

void ContainerReaderModelNG::SetBreakPointConfig(const std::vector<double>& widthBreakpoints,
    const std::vector<double>& heightBreakpoints)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetBreakPointConfig(frameNode.GetRawPtr(), widthBreakpoints, heightBreakpoints);
}

void ContainerReaderModelNG::SetOnSizeChange(std::function<void(const SizeF&)>&& event)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetOnSizeChange(frameNode.GetRawPtr(), std::move(event));
}

void ContainerReaderModelNG::SetOnWidthBreakpointChange(std::function<void(WidthBreakpoint)>&& event)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetOnWidthBreakpointChange(frameNode.GetRawPtr(), std::move(event));
}

void ContainerReaderModelNG::SetOnHeightBreakpointChange(std::function<void(HeightBreakpoint)>&& event)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetOnHeightBreakpointChange(frameNode.GetRawPtr(), std::move(event));
}

void ContainerReaderModelNG::SetBreakPointConfig(FrameNode* frameNode,
    const std::vector<double>& widthBreakpoints, const std::vector<double>& heightBreakpoints)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerReaderLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    BreakPointConfig config;
    config.widthBreakpoints = widthBreakpoints;
    config.heightBreakpoints = heightBreakpoints;
    layoutProperty->UpdateBreakPointConfig(config);
}

void ContainerReaderModelNG::ResetBreakPointConfig(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerReaderLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    BreakPointConfig config;
    layoutProperty->UpdateBreakPointConfig(config);
}

void ContainerReaderModelNG::SetOnSizeChange(FrameNode* frameNode, std::function<void(const SizeF&)>&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSizeChange(std::move(event));
}

void ContainerReaderModelNG::SetOnWidthBreakpointChange(FrameNode* frameNode,
    std::function<void(WidthBreakpoint)>&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWidthBreakpointChange(std::move(event));
}

void ContainerReaderModelNG::SetOnHeightBreakpointChange(FrameNode* frameNode,
    std::function<void(HeightBreakpoint)>&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnHeightBreakpointChange(std::move(event));
}

void ContainerReaderModelNG::SetRenderFunction(const ContainerReaderRenderFunction& renderFunction)
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetRenderFunction(renderFunction);
}
void ContainerReaderModelNG::SetRenderFunction(FrameNode* frameNode,
    const ContainerReaderRenderFunction& renderFunction)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetRenderFunction(renderFunction);
}

RefPtr<FrameNode> ContainerReaderModelNG::GetFrameNode()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto node = stack->GetMainFrameNode();
    if (!node) {
        return nullptr;
    }
    if (node->GetTag() != "ContainerReader") {
        return nullptr;
    }
    return AceType::Claim(node);
}

} // namespace OHOS::Ace::NG
