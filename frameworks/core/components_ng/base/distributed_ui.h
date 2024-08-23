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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_DISTRIBUTE_UI_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_DISTRIBUTE_UI_H

#include <cstdint>
#include <functional>
#include <set>

#include "interfaces/inner_api/ace/serializeable_object.h"

#include "base/json/node_object.h"
#include "core/components_ng/base/ui_node.h"
#include "core/event/touch_event.h"

#define CHECK_NULL_BREAK(ptr)                                       \
    if (!(ptr)) {                                                   \
        break;                                                      \
    }

#define CHECK_NULL_CONTINUE(ptr)                                    \
    if (!(ptr)) {                                                   \
        continue;                                                   \
    }

namespace OHOS::Ace::NG {
class DistributedUI {
public:
    enum UpdateType : uint8_t {
        PAGE_UPDATE = 0,
        PAGE_CHANGE = 1,
    };

    enum StateMachine : uint8_t {
        INIT = 0,
        SOURCE_START = 1,
        SINK_START = 2,
        STOP = 3,
    };

    enum OperationType : uint8_t {
        OP_ADD = 0,
        OP_MODIFY = 1,
        OP_DELETE = 2,
    };

    DistributedUI() = default;
    ~DistributedUI() = default;

    // for distribute UI source
    SerializeableObjectArray DumpUITree();
    void SubscribeUpdate(const std::function<void(int32_t, SerializeableObjectArray&)>& onUpdate);
    void UnSubscribeUpdate();
    void ProcessSerializeableInputEvent(const SerializeableObjectArray& array);

    // for distribute UI sink
    void RestoreUITree(const SerializeableObjectArray& array);
    void UpdateUITree(const SerializeableObjectArray& array);
    void SubscribeInputEventProcess(const std::function<void(SerializeableObjectArray&)>& onEvent);
    void UnSubscribeInputEventProcess();

    // internal APIs for distribute UI source
    void AddDeletedNode(int32_t nodeId);
    void AddNewNode(int32_t nodeId);
    void AddDirtyCustomNode(int32_t nodeId);
    void AddDirtyRenderNode(int32_t nodeId);
    void AddDirtyLayoutNode(int32_t nodeId);
    void OnTreeUpdate();
    void OnPageChanged(int32_t pageId);
    int32_t GetCurrentPageId();

    // internal APIs for distribute UI sink
    void BypassEvent(const TouchEvent& point, bool isSubPipe);
    bool IsSinkMode();
    void ApplyOneUpdate();

private:
    void DumpDirtyRenderNodes(SerializeableObjectArray& objectArray);
    void DumpDirtyLayoutNodes(SerializeableObjectArray& objectArray);
    void DumpNewNodes(SerializeableObjectArray& objectArray);
    void DumpDelNodes(SerializeableObjectArray& objectArray);
    SerializeableObjectArray DumpUpdate();
    void ResetDirtyNodes();
    bool IsNewNode(int32_t nodeId);
    bool ReadyToDumpUpdate();

    void SetIdMapping(int32_t srcNodeId, int32_t sinkNodeId);
    int32_t GetIdMapping(int32_t srcNodeId);
    void AddNodeHash(int32_t nodeId, std::size_t hashValue);
    void DelNodeHash(int32_t nodeId);
    bool IsRecordHash(int32_t nodeId, std::size_t hashValue);
    void DumpNode(const RefPtr<NG::UINode>& node, int depth, OperationType op, std::unique_ptr<NodeObject>& nodeObject);
    void DumpTreeInner(const RefPtr<NG::UINode>& node, SerializeableObjectArray& objectArray, int depth);
    RefPtr<UINode> RestoreNode(const std::unique_ptr<NodeObject>& nodeObject);
    void AttachToTree(RefPtr<UINode> root, RefPtr<UINode> uiNode, const std::unique_ptr<NodeObject>& nodeObject);
    void AddNode(const std::unique_ptr<NodeObject>& nodeObject, RefPtr<FrameNode> pageRootNode);
    void ModNode(const std::unique_ptr<NodeObject>& nodeObject);
    void DelNode(const std::unique_ptr<NodeObject>& nodeObject);
    void UpdateUITreeInner(SerializeableObjectArray& nodeArray);
    void RestoreUITreeInner(const SerializeableObjectArray& nodeArray);
    bool IsInCurrentPage(RefPtr<NG::UINode> node, int32_t pageId);

    std::set<int32_t, std::greater<int32_t>> deletedNodes_;
    std::set<int32_t> newNodes_;
    std::set<int32_t> dirtyCustomNodes_;
    std::set<int32_t> dirtyLayoutNodes_;
    std::set<int32_t> dirtyRenderNodes_;
    bool pageChangeFlag_ = false;
    int32_t currentPageId_ = 0;
    std::function<void(UpdateType, SerializeableObjectArray&)> onUpdateCb_;
    std::function<void(SerializeableObjectArray&)> onEventCb_;
    StateMachine status_ = StateMachine::INIT;
    std::list<SerializeableObjectArray> pendingUpdates_;

    std::unordered_map<int32_t, int32_t> nodeIdMapping_;
    std::unordered_map<int32_t, std::size_t> nodeHashs_;
    std::list<RefPtr<NG::UINode>> sinkPageChildren_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_DISTRIBUTE_UI_H
