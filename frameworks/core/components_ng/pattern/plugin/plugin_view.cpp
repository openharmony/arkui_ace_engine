/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/plugin/plugin_view.h"

#include <optional>

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/plugin/plugin_sub_container.h"
#include "core/components/plugin/resource/plugin_manager_delegate.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/plugin/plugin_layout_property.h"
#include "core/components_ng/pattern/plugin/plugin_node.h"
#include "core/components_ng/pattern/plugin/plugin_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void PluginView::Create(const RequestPluginInfo& pluginInfo)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = PluginNode::GetOrCreatePluginNode(
        V2::PLUGIN_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<PluginPattern>(); });
    stack->Push(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(PluginLayoutProperty, RequestPluginInfo, pluginInfo);
}

void PluginView::SetOnComplete(PluginCallback&& OnComplete)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<PluginEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnComplete(std::move(OnComplete));
}

void PluginView::SetOnError(PluginCallback&& OnError)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<PluginEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnError(std::move(OnError));
}

} // namespace OHOS::Ace::NG
