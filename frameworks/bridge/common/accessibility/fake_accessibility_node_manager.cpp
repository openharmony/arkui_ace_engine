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

#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"

#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "base/log/log.h"
#include "base/utils/linear_map.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "frameworks/bridge/common/dom/dom_type.h"

namespace OHOS::Ace::Framework {

AccessibilityNodeManager::~AccessibilityNodeManager() = default;

void AccessibilityNodeManager::InitializeCallback() {}

void AccessibilityNodeManager::SetPipelineContext(const RefPtr<PipelineContext>& context) {}

void AccessibilityNodeManager::SetRunningPage(const RefPtr<JsAcePage>& page) {}

std::string AccessibilityNodeManager::GetNodeChildIds(const RefPtr<AccessibilityNode>& node)
{
    return "";
}

void AccessibilityNodeManager::AddNodeWithId(const std::string& key, const RefPtr<AccessibilityNode>& node) {}

void AccessibilityNodeManager::AddNodeWithTarget(const std::string& key, const RefPtr<AccessibilityNode>& node) {}

RefPtr<AccessibilityNode> AccessibilityNodeManager::GetAccessibilityNodeFromPage(NodeId nodeId) const
{
    return nullptr;
}

void AccessibilityNodeManager::ClearNodeRectInfo(RefPtr<AccessibilityNode>& node, bool isPopDialog) {}

void AccessibilityNodeManager::SendAccessibilityAsyncEvent(const AccessibilityEvent& accessibilityEvent) {}

int32_t AccessibilityNodeManager::GenerateNextAccessibilityId()
{
    return 0;
}

// combined components which pop up through js api, such as dialog/toast
RefPtr<AccessibilityNode> AccessibilityNodeManager::CreateSpecializedNode(
    const std::string& tag, int32_t nodeId, int32_t parentNodeId)
{
    return nullptr;
}

RefPtr<AccessibilityNode> AccessibilityNodeManager::CreateAccessibilityNode(
    const std::string& tag, int32_t nodeId, int32_t parentNodeId, int32_t itemIndex)
{
    return nullptr;
}

RefPtr<AccessibilityNode> AccessibilityNodeManager::GetAccessibilityNodeById(NodeId nodeId) const
{
    return nullptr;
}

void AccessibilityNodeManager::RemoveAccessibilityNodes(RefPtr<AccessibilityNode>& node) {}

void AccessibilityNodeManager::RemoveAccessibilityNodeById(NodeId nodeId) {}

void AccessibilityNodeManager::ClearPageAccessibilityNodes(int32_t pageId) {}

void AccessibilityNodeManager::TrySaveTargetAndIdNode(
    const std::string& id, const std::string& target, const RefPtr<AccessibilityNode>& node) {}

void AccessibilityNodeManager::HandleComponentPostBinding() {}

void AccessibilityNodeManager::DumpHandleEvent(const std::vector<std::string>& params) {}

void AccessibilityNodeManager::DumpProperty(const std::vector<std::string>& params) {}

void AccessibilityNodeManager::DumpTree(int32_t depth, NodeId nodeID) {}

void AccessibilityNodeManager::SetCardViewParams(const std::string& key, bool focus) {}

void AccessibilityNodeManager::SetCardViewPosition(int id, float offsetX, float offsetY) {}

} // namespace OHOS::Ace::Framework
