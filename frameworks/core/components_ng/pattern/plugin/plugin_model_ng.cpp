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

#include "core/components_ng/pattern/plugin/plugin_model_ng.h"

#include "core/components/plugin/plugin_sub_container.h"
#include "core/components/plugin/resource/plugin_manager_delegate.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/plugin/plugin_layout_property.h"
#include "core/components_ng/pattern/plugin/plugin_node.h"
#include "core/components_ng/pattern/plugin/plugin_pattern.h"
#include "core/components_ng/property/calc_length.h"

namespace OHOS::Ace::NG {
void PluginModelNG::Create(const RequestPluginInfo& pluginInfo)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::PLUGIN_ETS_TAG, nodeId);
    auto frameNode = PluginNode::GetOrCreatePluginNode(
        V2::PLUGIN_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<PluginPattern>(); });
    stack->Push(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(PluginLayoutProperty, RequestPluginInfo, pluginInfo);
};

void PluginModelNG::SetOnComplete(std::function<void(const std::string&)>&& OnComplete)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<PluginEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnComplete(std::move(OnComplete));
};

void PluginModelNG::SetOnError(std::function<void(const std::string&)>&& OnError)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<PluginEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnError(std::move(OnError));
};

void PluginModelNG::SetPluginSize(const Dimension& width, const Dimension& height)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pluginLayoutProperty = frameNode->GetLayoutProperty<PluginLayoutProperty>();
    CHECK_NULL_VOID(pluginLayoutProperty);
    auto pluginInfo = pluginLayoutProperty->GetRequestPluginInfo().value_or(RequestPluginInfo());
    pluginInfo.width = width;
    pluginInfo.height = height;
    pluginLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), CalcLength(height)));
    ACE_UPDATE_LAYOUT_PROPERTY(PluginLayoutProperty, RequestPluginInfo, pluginInfo);
};

void PluginModelNG::SetWidth(const Dimension& width)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pluginLayoutProperty = frameNode->GetLayoutProperty<PluginLayoutProperty>();
    CHECK_NULL_VOID(pluginLayoutProperty);
    auto pluginInfo = pluginLayoutProperty->GetRequestPluginInfo().value_or(RequestPluginInfo());
    pluginInfo.width = width;
    pluginLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), std::nullopt));
    ACE_UPDATE_LAYOUT_PROPERTY(PluginLayoutProperty, RequestPluginInfo, pluginInfo);
};

void PluginModelNG::SetHeight(const Dimension& height)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pluginLayoutProperty = frameNode->GetLayoutProperty<PluginLayoutProperty>();
    CHECK_NULL_VOID(pluginLayoutProperty);
    auto pluginInfo = pluginLayoutProperty->GetRequestPluginInfo().value_or(RequestPluginInfo());
    pluginInfo.height = height;
    pluginLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(height)));
    ACE_UPDATE_LAYOUT_PROPERTY(PluginLayoutProperty, RequestPluginInfo, pluginInfo);
};

void PluginModelNG::SetData(const std::string& data)
{
    ACE_UPDATE_LAYOUT_PROPERTY(PluginLayoutProperty, Data, data);
};

void PluginModelNG::SetPluginSize(FrameNode* frameNode, const Dimension& width, const Dimension& height)
{
    CHECK_NULL_VOID(frameNode);
    auto pluginLayoutProperty = frameNode->GetLayoutProperty<PluginLayoutProperty>();
    CHECK_NULL_VOID(pluginLayoutProperty);
    auto pluginInfo = pluginLayoutProperty->GetRequestPluginInfo().value_or(RequestPluginInfo());
    pluginInfo.width = width;
    pluginInfo.height = height;
    pluginLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), CalcLength(height)));
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(PluginLayoutProperty, RequestPluginInfo, pluginInfo, frameNode);
};

void PluginModelNG::SetWidth(FrameNode* frameNode, const Dimension& width)
{
    CHECK_NULL_VOID(frameNode);
    auto pluginLayoutProperty = frameNode->GetLayoutProperty<PluginLayoutProperty>();
    CHECK_NULL_VOID(pluginLayoutProperty);
    auto pluginInfo = pluginLayoutProperty->GetRequestPluginInfo().value_or(RequestPluginInfo());
    pluginInfo.width = width;
    pluginLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(width), std::nullopt));
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(PluginLayoutProperty, RequestPluginInfo, pluginInfo, frameNode);
};

void PluginModelNG::SetHeight(FrameNode* frameNode, const Dimension& height)
{
    CHECK_NULL_VOID(frameNode);
    auto pluginLayoutProperty = frameNode->GetLayoutProperty<PluginLayoutProperty>();
    CHECK_NULL_VOID(pluginLayoutProperty);
    auto pluginInfo = pluginLayoutProperty->GetRequestPluginInfo().value_or(RequestPluginInfo());
    pluginInfo.height = height;
    pluginLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(height)));
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(PluginLayoutProperty, RequestPluginInfo, pluginInfo, frameNode);
};
} // namespace OHOS::Ace::NG
