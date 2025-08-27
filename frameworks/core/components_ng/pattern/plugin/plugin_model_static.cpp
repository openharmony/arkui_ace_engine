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

#include "core/components_ng/pattern/plugin/plugin_model_static.h"

#ifndef ARKUI_CAPI_UNITTEST
#include "core/components/plugin/plugin_sub_container.h"
#include "core/components/plugin/resource/plugin_manager_delegate.h"
#endif
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/plugin/plugin_layout_property.h"
#include "core/components_ng/pattern/plugin/plugin_node.h"
#include "core/components_ng/pattern/plugin/plugin_pattern.h"
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> PluginModelStatic::CreateFrameNode(int32_t nodeId)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::PLUGIN_ETS_TAG, nodeId);
    auto frameNode = PluginNode::GetOrCreatePluginNode(
        V2::PLUGIN_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<PluginPattern>(); });
    return frameNode;
}

void PluginModelStatic::SetRequestPluginInfo(FrameNode *frameNode, const std::optional<RequestPluginInfo>& pluginInfo)
{
    CHECK_NULL_VOID(frameNode);
    if (pluginInfo) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(PluginLayoutProperty, RequestPluginInfo, *pluginInfo, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(PluginLayoutProperty, RequestPluginInfo, frameNode);
    }
}

void PluginModelStatic::SetData(FrameNode *frameNode, const std::optional<std::string>& data)
{
    CHECK_NULL_VOID(frameNode);
    if (data) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(PluginLayoutProperty, Data, *data, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(PluginLayoutProperty, Data, frameNode);
    }
}

void PluginModelStatic::SetOnComplete(FrameNode *frameNode, std::function<void(const std::string&)>&& OnComplete)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<PluginEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnComplete(std::move(OnComplete));
}

void PluginModelStatic::SetOnError(FrameNode *frameNode, std::function<void(const std::string&)>&& OnError)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<PluginEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnError(std::move(OnError));
}
} // namespace OHOS::Ace::NG
