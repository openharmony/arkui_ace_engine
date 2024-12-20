/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
#include "base/utils/macros.h"
#include "core/pipeline/base/composed_element.h"
#include "core/pipeline/pipeline_base.h"
#include "frameworks/bridge/js_frontend/js_ace_page.h"

namespace OHOS::Ace::Framework {

struct VisibleCallbackInfo {
    VisibleRatioCallback callback;
    double visibleRatio = 1.0;
    bool currentVisibleType = false;
};

struct WindowPos {
    int32_t left = 0;
    int32_t top = 0;
};

class ACE_FORCE_EXPORT AccessibilityNodeManager : public AccessibilityManager {
    DECLARE_ACE_TYPE(AccessibilityNodeManager, AccessibilityManager);

public:
    static RefPtr<AccessibilityNodeManager> Create();

    AccessibilityNodeManager() = default;
    ~AccessibilityNodeManager() override;

    // AccessibilityNodeManager functions.
    virtual void InitializeCallback();
    virtual void RegisterSubWindowInteractionOperation(int windowId);
    virtual void SetPipelineContext(const RefPtr<PipelineBase>& context);
    void AddSubPipelineContext(const RefPtr<PipelineBase>& context);
    void SetRunningPage(const RefPtr<JsAcePage>& page);
    std::string GetNodeChildIds(const RefPtr<AccessibilityNode>& node);
    void AddNodeWithId(const std::string& key, const RefPtr<AccessibilityNode>& node);
    void AddNodeWithTarget(const std::string& key, const RefPtr<AccessibilityNode>& node);
    RefPtr<AccessibilityNode> GetAccessibilityNodeFromPage(NodeId nodeId) const;
    void ClearNodeRectInfo(RefPtr<AccessibilityNode>& node, bool isPopDialog) override;
    void AddComposedElement(const std::string& key, const RefPtr<ComposedElement>& node) override;
    void RemoveComposedElementById(const std::string& key) override;
    WeakPtr<ComposedElement> GetComposedElementFromPage(NodeId nodeId) override;
    void TriggerVisibleChangeEvent() override;
    void AddVisibleChangeNode(NodeId nodeId, double ratio, VisibleRatioCallback callback) override;
    void RemoveVisibleChangeNode(NodeId nodeId) override;
    bool IsVisibleChangeNodeExists(NodeId index) override
    {
        if (index == -1) {
            return !visibleChangeNodes_.empty();
        }
        return visibleChangeNodes_.find(index) != visibleChangeNodes_.end();
    }

    int32_t GetRootNodeId() const
    {
        return rootNodeId_;
    }

    const Offset& GetCardOffset()
    {
        return cardOffset_;
    }

    int32_t GetCardId() const
    {
        return cardId_;
    }

    bool isOhosHostCard() const
    {
        return isOhosHostCard_;
    }

    WeakPtr<PipelineBase> GetPipelineContext()
    {
        return context_;
    }

    std::list<WeakPtr<PipelineBase>>& GetSubPipelineContexts()
    {
        return subContexts_;
    }

    // AccessibilityNodeManager overrides functions.
    void SendAccessibilityAsyncEvent(const AccessibilityEvent& accessibilityEvent) override;
    void UpdateVirtualNodeFocus() override {}
    int64_t GenerateNextAccessibilityId() override;
    RefPtr<AccessibilityNode> CreateSpecializedNode(
        const std::string& tag, int32_t nodeId, int32_t parentNodeId) override;
    RefPtr<AccessibilityNode> CreateAccessibilityNode(
        const std::string& tag, int32_t nodeId, int32_t parentNodeId, int32_t itemIndex) override;
    RefPtr<AccessibilityNode> GetAccessibilityNodeById(NodeId nodeId) const override;
    std::string GetInspectorNodeById(NodeId nodeId) const override;
    void RemoveAccessibilityNodes(RefPtr<AccessibilityNode>& node) override;
    void RemoveAccessibilityNodeById(NodeId nodeId) override;
    void ClearPageAccessibilityNodes(int32_t pageId) override;

    void SetRootNodeId(int32_t nodeId) override
    {
        rootNodeId_ = nodeId;
    }

    void TrySaveTargetAndIdNode(
        const std::string& id, const std::string& target, const RefPtr<AccessibilityNode>& node) override;
    void HandleComponentPostBinding() override {}
    void OnDumpInfo(const std::vector<std::string>& params) override;
    void OnDumpInfoNG(const std::vector<std::string>& params, uint32_t windowId, bool hasJson = false) override {}
    std::unique_ptr<JsonValue> DumpComposedElementsToJson() const;
    std::unique_ptr<JsonValue> DumpComposedElementToJson(NodeId nodeId);
    void SetCardViewParams(const std::string& key, bool focus) override;
    void SetCardViewPosition(int id, float offsetX, float offsetY) override;

    void SetSupportAction(uint32_t action, bool isEnable) override {}

    void UpdateEventTarget(NodeId id, BaseEventInfo& info) override;

    void SetWindowPos(int32_t left, int32_t top, int32_t windowId) override;
    int32_t GetWindowLeft(int32_t windowId)
    {
        auto windowPos = windowPosMap_.find(windowId);
        if (windowPos != windowPosMap_.end()) {
            return windowPos->second.left;
        }
        return windowPosMap_.begin()->second.left;
    }
    int32_t GetWindowTop(int32_t windowId)
    {
        auto windowPos = windowPosMap_.find(windowId);
        if (windowPos != windowPosMap_.end()) {
            return windowPos->second.top;
        }
        return windowPosMap_.begin()->second.top;
    }

    bool IsDeclarative();

protected:
    virtual void DumpHandleEvent(const std::vector<std::string>& params);
    virtual void DumpProperty(const std::vector<std::string>& params);
    virtual void DumpTree(int32_t depth, int64_t nodeID, bool isDumpSimplify = false);

    static bool GetDefaultAttrsByType(const std::string& type, std::unique_ptr<JsonValue>& jsonDefaultAttrs);
    mutable std::mutex mutex_;
    std::unordered_map<NodeId, RefPtr<AccessibilityNode>> accessibilityNodes_;
    std::unordered_map<std::string, WeakPtr<AccessibilityNode>> nodeWithIdMap_;
    std::unordered_map<std::string, WeakPtr<AccessibilityNode>> nodeWithTargetMap_;
    std::unordered_map<std::string, WeakPtr<ComposedElement>> composedElementIdMap_;
    std::unordered_map<NodeId, std::list<VisibleCallbackInfo>> visibleChangeNodes_;
    WeakPtr<PipelineBase> context_;
    std::list<WeakPtr<PipelineBase>> subContexts_;
    WeakPtr<JsAcePage> indexPage_;
    int32_t rootNodeId_ = -1;
    Offset cardOffset_;
    int32_t cardId_ = 0;
    bool isOhosHostCard_ = false;
    std::map<int32_t, WindowPos> windowPosMap_;

    static const size_t EVENT_DUMP_PARAM_LENGTH_UPPER;
    static const size_t EVENT_DUMP_PARAM_LENGTH_LOWER;
    static const size_t PROPERTY_DUMP_PARAM_LENGTH;
    static const size_t EVENT_DUMP_ORDER_INDEX;
    static const size_t EVENT_DUMP_ID_INDEX;
    static const size_t EVENT_DUMP_ACTION_INDEX;
    static const size_t EVENT_DUMP_ACTION_PARAM_INDEX;

private:
    RefPtr<AccessibilityNode> CreateCommonAccessibilityNode(
        const std::string& tag, int32_t nodeId, int32_t parentNodeId, int32_t itemIndex);
    RefPtr<AccessibilityNode> CreateDeclarativeAccessibilityNode(
        const std::string& tag, int32_t nodeId, int32_t parentNodeId, int32_t itemIndex);
    RefPtr<AccessibilityNode> GetRootAccessibilityNode();
    // decor nodes are created before load page(SetRootNodeId)
    bool IsDecor()
    {
        return rootNodeId_ == -1;
    }
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_ACCESSIBILITY_NODE_MANAGER_H
