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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_NODE_RENDER_STATUS_MONITOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_NODE_RENDER_STATUS_MONITOR_H

#include <functional>
#include <list>
#include <memory>

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {
constexpr int32_t MONITOR_INVALID_ID = -1;
class FrameNode;
enum class NodeRenderState {
    ABOUT_TO_RENDER_IN = 0,
    ABOUT_TO_RENDER_OUT = 1,
};

enum class RenderMonitorReason {
    RENDER_CHANGE = 0,
    NODE_RELEASE = 1,
};
enum class MonitorSourceType {
    OBSERVER = 1,
};

struct MonitorRegisterResult {
    int32_t id = MONITOR_INVALID_ID;
    NodeRenderState state = NodeRenderState::ABOUT_TO_RENDER_OUT;
};

class ACE_FORCE_EXPORT NodeRenderStatusMonitor final : public AceType {
public:
    NodeRenderStatusMonitor() = default;
    ~NodeRenderStatusMonitor() override = default;

    using NodeRenderStatusHandleFunc = std::function<void(FrameNode*, NodeRenderState, RenderMonitorReason)>;

    MonitorRegisterResult RegisterNodeRenderStatusListener(
        FrameNode* frameNode, NodeRenderStatusHandleFunc&& func, MonitorSourceType type);
    void UnRegisterNodeRenderStatusListener(FrameNode* frameNode, int32_t id = MONITOR_INVALID_ID);
    void WalkThroughAncestorForStateListener();
    bool IsRegisterNodeRenderStateChangeCallbackExceedLimit();
    NodeRenderState GetNodeCurrentRenderState(FrameNode* frameNode);
    void NotifyFrameNodeRelease(FrameNode* frameNode);

private:
    static int32_t GenerateId();

    struct NodeRenderStatusListener {
        MonitorSourceType sourceType;
        int32_t id;
        NodeRenderStatusHandleFunc func;
        NodeRenderStatusListener(MonitorSourceType sourceType, int32_t id, NodeRenderStatusHandleFunc func)
            : sourceType(sourceType), id(id), func(std::move(func)) {};
    };

    struct NodeRenderStatusSourceListener {
        NodeRenderState nodeRenderState;
        std::list<std::shared_ptr<NodeRenderStatusListener>> nodeRenderStatusListeners;
        NodeRenderStatusSourceListener(NodeRenderState nodeRenderState,
            std::list<std::shared_ptr<NodeRenderStatusListener>> nodeRenderStatusListeners)
            : nodeRenderState(nodeRenderState), nodeRenderStatusListeners(std::move(nodeRenderStatusListeners)) {};
    };
    bool IsNodeRenderOut(FrameNode* frameNode);
    std::unordered_map<FrameNode*, std::shared_ptr<NodeRenderStatusSourceListener>> nodeRenderStatusListeners_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_NODE_RENDER_STATUS_MONITOR_H