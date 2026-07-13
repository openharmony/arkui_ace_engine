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

#include "core/components_ng/pattern/container_reader/container_reader_model_static.h"

#include "core/components_ng/pattern/container_reader/container_reader_event_hub.h"
#include "core/components_ng/pattern/container_reader/container_reader_layout_property.h"
#include "core/components_ng/pattern/container_reader/container_reader_pattern.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> ContainerReaderModelStatic::CreateFrameNode(int32_t nodeId)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[ContainerReader][self:%d]", nodeId);
    ACE_UINODE_TRACE(nodeId);
    return FrameNode::CreateFrameNode("ContainerReader", nodeId, AceType::MakeRefPtr<ContainerReaderPattern>());
}

void ContainerReaderModelStatic::SetBreakPointConfig(FrameNode* frameNode,
                                                     const std::vector<double>& widthBreakpoints,
                                                     const std::vector<double>& heightBreakpoints)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerReaderLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    BreakPointConfig config;
    config.widthBreakpoints = widthBreakpoints;
    config.heightBreakpoints = heightBreakpoints;
    layoutProperty->UpdateBreakPointConfig(config);
}

void ContainerReaderModelStatic::ResetBreakPointConfig(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<ContainerReaderLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    BreakPointConfig config;
    layoutProperty->UpdateBreakPointConfig(config);
}

void ContainerReaderModelStatic::SetOnSizeChange(FrameNode* frameNode,
                                                  std::function<void(const SizeF&)>&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSizeChange(std::move(event));
}

void ContainerReaderModelStatic::SetOnWidthBreakpointChange(FrameNode* frameNode,
                                                             std::function<void(WidthBreakpoint)>&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWidthBreakpointChange(std::move(event));
}

void ContainerReaderModelStatic::SetOnHeightBreakpointChange(FrameNode* frameNode,
                                                              std::function<void(HeightBreakpoint)>&& event)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ContainerReaderEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnHeightBreakpointChange(std::move(event));
}

void ContainerReaderModelStatic::SetRenderFunction(FrameNode* frameNode,
                                                    const ContainerReaderRenderFunction& renderFunction)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ContainerReaderPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetRenderFunction(renderFunction);
}

} // namespace OHOS::Ace::NG