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

#include "core/components_ng/base/node_render_status_monitor.h"

#include "ui/base/utils/utils.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
namespace {
constexpr size_t MAX_NODE_RENDER_STATE_LISTENERS = 64;
} // namespace

bool NodeRenderStatusMonitor::IsRegisterNodeRenderStateChangeCallbackExceedLimit()
{
    return nodeRenderStatusListeners_.size() >= MAX_NODE_RENDER_STATE_LISTENERS;
}

MonitorRegisterResult NodeRenderStatusMonitor::RegisterNodeRenderStatusListener(
    FrameNode* frameNode, NodeRenderStatusHandleFunc&& func, MonitorSourceType type)
{
    MonitorRegisterResult result;
    CHECK_NULL_RETURN(frameNode, result);
    CHECK_NULL_RETURN(func, result);
    if (nodeRenderStatusListeners_.size() >= MAX_NODE_RENDER_STATE_LISTENERS) {
        return result;
    }
    auto state = GetNodeCurrentRenderState(frameNode);
    auto iter = nodeRenderStatusListeners_.find(frameNode);
    if (iter == nodeRenderStatusListeners_.end()) {
        auto id = NodeRenderStatusMonitor::GenerateId();
        auto listener = std::make_shared<NodeRenderStatusListener>(type, id, std::move(func));
        auto sourceListener = std::make_shared<NodeRenderStatusSourceListener>(
            state, std::list<std::shared_ptr<NodeRenderStatusListener>>({ listener }));
        nodeRenderStatusListeners_.emplace(frameNode, std::move(sourceListener));
        return { id, state };
    }
    CHECK_NULL_RETURN(iter->second, result);
    auto& holder = iter->second->nodeRenderStatusListeners;
    // OBSERVER can only be registered once
    if (type == MonitorSourceType::OBSERVER &&
        std::any_of(holder.begin(), holder.end(), [](const std::shared_ptr<NodeRenderStatusListener>& listener) {
            return listener->sourceType == MonitorSourceType::OBSERVER;
        })) {
        return result;
    }

    auto id = NodeRenderStatusMonitor::GenerateId();
    holder.emplace_back(std::make_shared<NodeRenderStatusListener>(type, id, std::move(func)));
    return { id, state };
}

void NodeRenderStatusMonitor::UnRegisterNodeRenderStatusListener(FrameNode* frameNode, int32_t id)
{
    CHECK_NULL_VOID(frameNode);
    auto iter = nodeRenderStatusListeners_.find(frameNode);
    if (iter == nodeRenderStatusListeners_.end()) {
        return;
    }
    CHECK_NULL_VOID(iter->second);
    auto& holder = iter->second->nodeRenderStatusListeners;

    holder.erase(
        std::remove_if(
            holder.begin(),
            holder.end(),
            [id](const std::shared_ptr<NodeRenderStatusListener>& registeredListener) {
                return registeredListener->id == id;
            }),
        holder.end());
    if (holder.empty()) {
        nodeRenderStatusListeners_.erase(frameNode);
    }
}

void NodeRenderStatusMonitor::WalkThroughAncestorForStateListener()
{
    ACE_FUNCTION_TRACE();
    std::vector<std::pair<FrameNode*, NodeRenderStatusHandleFunc>> inCallbacks;
    std::vector<std::pair<FrameNode*, NodeRenderStatusHandleFunc>> outCallbacks;
    for (const auto& [frameNode, sourceListener] : nodeRenderStatusListeners_) {
        CHECK_NULL_VOID(frameNode);
        auto state = GetNodeCurrentRenderState(frameNode);
        if (sourceListener->nodeRenderState == state) {
            continue;
        }
        sourceListener->nodeRenderState = state;
        for (const auto& listener : sourceListener->nodeRenderStatusListeners) {
            if (!listener || !listener->func) {
                continue;
            }

            if (state == NodeRenderState::ABOUT_TO_RENDER_IN) {
                inCallbacks.emplace_back(frameNode, listener->func);
            } else if (state == NodeRenderState::ABOUT_TO_RENDER_OUT) {
                outCallbacks.emplace_back(frameNode, listener->func);
            }
        }
    }

    for (const auto& [frameNode, func] : inCallbacks) {
        CHECK_NULL_VOID(func);
        func(frameNode, NodeRenderState::ABOUT_TO_RENDER_IN, RenderMonitorReason::RENDER_CHANGE);
    }
    
    for (const auto& [frameNode, func] : outCallbacks) {
        CHECK_NULL_VOID(func);
        func(frameNode, NodeRenderState::ABOUT_TO_RENDER_OUT, RenderMonitorReason::RENDER_CHANGE);
    }
}

void NodeRenderStatusMonitor::NotifyFrameNodeRelease(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto it = nodeRenderStatusListeners_.find(frameNode);
    if (it != nodeRenderStatusListeners_.end()) {
        auto& sourceListener = it->second;
        CHECK_NULL_VOID(sourceListener);
        for (const auto& listener : sourceListener->nodeRenderStatusListeners) {
            if (listener && listener->func) {
                listener->func(frameNode, NodeRenderState::ABOUT_TO_RENDER_OUT, RenderMonitorReason::NODE_RELEASE);
            }
        }
        nodeRenderStatusListeners_.erase(it);
    }
}

bool NodeRenderStatusMonitor::IsNodeRenderOut(FrameNode* node)
{
    CHECK_NULL_RETURN(node, true);
    return (!node->IsVisible() || !node->IsActive() || !node->IsOnMainTree());
}

NodeRenderState NodeRenderStatusMonitor::GetNodeCurrentRenderState(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, NodeRenderState::ABOUT_TO_RENDER_OUT);
    if (IsNodeRenderOut(frameNode)) {
        return NodeRenderState::ABOUT_TO_RENDER_OUT;
    }
    auto parent = frameNode->GetParent();
    CHECK_NULL_RETURN(parent, NodeRenderState::ABOUT_TO_RENDER_OUT);
    while (parent) {
        if (AceType::InstanceOf<FrameNode>(parent)) {
            auto node = AceType::DynamicCast<FrameNode>(parent);
            if (node->IsRootNode()) {
                return NodeRenderState::ABOUT_TO_RENDER_IN;
            }
            if (IsNodeRenderOut(AceType::RawPtr(node))) {
                return NodeRenderState::ABOUT_TO_RENDER_OUT;
            }
        }
        parent = parent->GetParent();
    }
    return NodeRenderState::ABOUT_TO_RENDER_OUT;
}

int32_t NodeRenderStatusMonitor::GenerateId()
{
    static std::atomic<int32_t> gInstanceId;
    int32_t id = gInstanceId.fetch_add(1);
    return id;
}

} // namespace OHOS::Ace::NG