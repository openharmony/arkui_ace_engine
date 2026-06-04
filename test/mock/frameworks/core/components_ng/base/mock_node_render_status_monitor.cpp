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

#include "core/components_ng/base/node_render_status_monitor.h"

namespace OHOS::Ace::NG {
MonitorRegisterResult NodeRenderStatusMonitor::RegisterNodeRenderStatusListener(
    FrameNode* frameNode, NodeRenderStatusHandleFunc&& func, MonitorSourceType type, int32_t resourceId)
{
    (void)frameNode;
    (void)func;
    (void)type;
    (void)resourceId;
    return {};
}

void NodeRenderStatusMonitor::UnRegisterNodeRenderStatusListener(FrameNode* frameNode, int32_t id)
{
    (void)frameNode;
    (void)id;
}

void NodeRenderStatusMonitor::WalkThroughAncestorForStateListener() {}

bool NodeRenderStatusMonitor::IsRegisterNodeRenderStateChangeCallbackExceedLimit()
{
    return false;
}

NodeRenderState NodeRenderStatusMonitor::GetNodeCurrentRenderState(FrameNode* frameNode)
{
    (void)frameNode;
    return NodeRenderState::ABOUT_TO_RENDER_OUT;
}

void NodeRenderStatusMonitor::NotifyFrameNodeRelease(FrameNode* frameNode)
{
    (void)frameNode;
}
} // namespace OHOS::Ace::NG
