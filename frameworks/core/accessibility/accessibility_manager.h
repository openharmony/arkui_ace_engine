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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_ACCESSIBILITY_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_ACCESSIBILITY_MANAGER_H

#include "base/memory/ace_type.h"
#include "core/accessibility/accessibility_node.h"

namespace OHOS::Ace {

struct AccessibilityEvent {
    int32_t nodeId = 0;
    std::string eventType;
    std::string componentType;
    double currentItemIndex = 0.0;
    double itemCount = 0.0;
};

class AccessibilityManager : public AceType {
    DECLARE_ACE_TYPE(AccessibilityManager, AceType);

public:
    AccessibilityManager() = default;
    ~AccessibilityManager() override = default;

    virtual void SendAccessibilityAsyncEvent(const AccessibilityEvent& accessibilityEvent) = 0;
    virtual int32_t GenerateNextAccessibilityId() = 0;
    virtual RefPtr<AccessibilityNode> CreateSpecializedNode(
        const std::string& tag, int32_t nodeId, int32_t parentNodeId) = 0;
    virtual RefPtr<AccessibilityNode> CreateAccessibilityNode(
        const std::string& tag, int32_t nodeId, int32_t parentNodeId, int32_t itemIndex) = 0;
    virtual RefPtr<AccessibilityNode> GetAccessibilityNodeById(NodeId nodeId) const = 0;
    virtual void RemoveAccessibilityNodes(RefPtr<AccessibilityNode>& node) = 0;
    virtual void RemoveAccessibilityNodeById(NodeId nodeId) = 0;
    virtual void ClearPageAccessibilityNodes(int32_t pageId) = 0;
    virtual void SetRootNodeId(int32_t nodeId) = 0;
    virtual void TrySaveTargetAndIdNode(
        const std::string& id, const std::string& target, const RefPtr<AccessibilityNode>& node) = 0;
    virtual void HandleComponentPostBinding() = 0;
    virtual void DumpHandleEvent(const std::vector<std::string>& params) = 0;
    virtual void DumpProperty(const std::vector<std::string>& params) = 0;
    virtual void DumpTree(int32_t depth, NodeId nodeID) = 0;
    virtual void SetCardViewPosition(int id, float offsetX, float offsetY) = 0;
    virtual void SetCardViewParams(const std::string& key, bool focus) = 0;
    virtual void ClearNodeRectInfo(RefPtr<AccessibilityNode>& node, bool isPopDialog) = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_ACCESSIBILITY_MANAGER_H
