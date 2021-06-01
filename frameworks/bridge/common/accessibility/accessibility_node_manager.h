/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_ACCESSIBILITY_NODE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_ACCESSIBILITY_NODE_MANAGER_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "base/memory/ace_type.h"
#include "core/pipeline/pipeline_context.h"
#include "frameworks/bridge/js_frontend/js_ace_page.h"

namespace OHOS::Ace::Framework {

class AccessibilityNodeManager : public AccessibilityManager {
    DECLARE_ACE_TYPE(AccessibilityNodeManager, AccessibilityManager);

public:
    AccessibilityNodeManager() = default;
    ~AccessibilityNodeManager() override;

    // AccessibilityNodeManager functions.
    virtual void InitializeCallback();
    void SetPipelineContext(const RefPtr<PipelineContext>& context);
    void SetRunningPage(const RefPtr<JsAcePage>& page);
    std::string GetNodeChildIds(const RefPtr<AccessibilityNode>& node);
    void AddNodeWithId(const std::string& key, const RefPtr<AccessibilityNode>& node);
    void AddNodeWithTarget(const std::string& key, const RefPtr<AccessibilityNode>& node);
    RefPtr<AccessibilityNode> GetAccessibilityNodeFromPage(NodeId nodeId) const;
    void ClearNodeRectInfo(RefPtr<AccessibilityNode>& node, bool isPopDialog) override;

    int32_t GetRootNodeId()
    {
        return rootNodeId_;
    }

    const Offset& GetCardOffset()
    {
        return cardOffset_;
    }

    int32_t GetCardId()
    {
        return cardId_;
    }

    bool isOhosHostCard()
    {
        return isOhosHostCard_;
    }

    const WeakPtr<PipelineContext> GetPipelineContext()
    {
        return context_;
    }

    // AccessibilityNodeManager overrides functions.
    virtual void SendAccessibilityAsyncEvent(const AccessibilityEvent& accessibilityEvent) override;
    int32_t GenerateNextAccessibilityId() override;
    RefPtr<AccessibilityNode> CreateSpecializedNode(
        const std::string& tag, int32_t nodeId, int32_t parentNodeId) override;
    RefPtr<AccessibilityNode> CreateAccessibilityNode(
        const std::string& tag, int32_t nodeId, int32_t parentNodeId, int32_t itemIndex) override;
    RefPtr<AccessibilityNode> GetAccessibilityNodeById(NodeId nodeId) const override;
    void RemoveAccessibilityNodes(RefPtr<AccessibilityNode>& node) override;
    void RemoveAccessibilityNodeById(NodeId nodeId) override;
    void ClearPageAccessibilityNodes(int32_t pageId) override;

    void SetRootNodeId(int32_t nodeId) override
    {
        rootNodeId_ = nodeId;
    }

    void TrySaveTargetAndIdNode(
        const std::string& id, const std::string& target, const RefPtr<AccessibilityNode>& node) override;
    void HandleComponentPostBinding() override;
    virtual void DumpHandleEvent(const std::vector<std::string>& params) override;
    virtual void DumpProperty(const std::vector<std::string>& params) override;
    virtual void DumpTree(int32_t depth, NodeId nodeID) override;
    virtual void SetCardViewParams(const std::string& key, bool focus) override;
    void SetCardViewPosition(int id, float offsetX, float offsetY) override;

private:
    std::unordered_map<NodeId, RefPtr<AccessibilityNode>> accessibilityNodes_;
    std::unordered_map<std::string, WeakPtr<AccessibilityNode>> nodeWithIdMap_;
    std::unordered_map<std::string, WeakPtr<AccessibilityNode>> nodeWithTargetMap_;
    WeakPtr<PipelineContext> context_;
    WeakPtr<JsAcePage> indexPage_;
    int32_t rootNodeId_ = -1;
    Offset cardOffset_;
    int32_t cardId_ = 0;
    bool isOhosHostCard_ = false;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_ACCESSIBILITY_NODE_MANAGER_H
