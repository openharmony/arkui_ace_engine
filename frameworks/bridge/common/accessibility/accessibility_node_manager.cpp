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
namespace {

const char PAGE_CHANGE_EVENT[] = "pagechange";
const char ROOT_STACK_TAG[] = "rootstacktag";
constexpr int32_t ROOT_STACK_BASE = 1100000;
constexpr int32_t CARD_NODE_ID_RATION = 10000;
constexpr int32_t CARD_ROOT_NODE_ID = 21000;
constexpr int32_t CARD_BASE = 100000;
constexpr int32_t CARD_MAX_AGP_ID = 20000;

std::atomic<int32_t> g_accessibilityId(ROOT_STACK_BASE);

inline int32_t GetRootNodeIdFromPage(const RefPtr<JsAcePage>& page)
{
    auto domDocument = page ? page->GetDomDocument() : nullptr;
    if (domDocument) {
        return domDocument->GetRootNodeId();
    }
    LOGW("Failed to get root dom node");
    return -1;
}

int32_t ConvertToNodeId(int32_t cardAccessibilityId)
{
    // cardAccessibilityId is integer total ten digits, top five for agp virtualViewId, end five for ace nodeId,
    // for example 00032 10001 convert to result is 1000001
    int result = 0;
    int32_t nodeId = cardAccessibilityId % CARD_BASE;
    if (nodeId >= CARD_ROOT_NODE_ID) {
        return 0;
    }
    result =
        (static_cast<int32_t>(nodeId / CARD_NODE_ID_RATION)) * DOM_ROOT_NODE_ID_BASE + nodeId % CARD_NODE_ID_RATION;
    return result;
}

} // namespace

AccessibilityNodeManager::~AccessibilityNodeManager()
{
    auto rootNode = GetAccessibilityNodeById(rootNodeId_ + ROOT_STACK_BASE);
    if (rootNode) {
        RemoveAccessibilityNodes(rootNode);
    }
}

void AccessibilityNodeManager::InitializeCallback() {}

void AccessibilityNodeManager::SetPipelineContext(const RefPtr<PipelineContext>& context)
{
    context_ = context;
}

void AccessibilityNodeManager::SetRunningPage(const RefPtr<JsAcePage>& page)
{
    indexPage_ = page;
    // send page change event to barrier free when page change.
    AccessibilityEvent accessibilityEvent;
    accessibilityEvent.eventType = PAGE_CHANGE_EVENT;
    SendAccessibilityAsyncEvent(accessibilityEvent);
}

std::string AccessibilityNodeManager::GetNodeChildIds(const RefPtr<AccessibilityNode>& node)
{
    std::string ids;
    if (node) {
        const auto& children = node->GetChildList();
        if ((node->GetNodeId() == rootNodeId_ + ROOT_STACK_BASE) && !children.empty()) {
            ids.append(std::to_string(children.back()->GetNodeId()));
        } else {
            for (const auto& child : children) {
                if (!ids.empty()) {
                    ids.append(",");
                }
                ids.append(std::to_string(child->GetNodeId()));
            }
        }
    }
    return ids;
}

void AccessibilityNodeManager::AddNodeWithId(const std::string& key, const RefPtr<AccessibilityNode>& node)
{
    if (!node) {
        return;
    }
    nodeWithIdMap_[key] = node;
}

void AccessibilityNodeManager::AddNodeWithTarget(const std::string& key, const RefPtr<AccessibilityNode>& node)
{
    if (!node) {
        return;
    }
    nodeWithTargetMap_[key] = node;
}

RefPtr<AccessibilityNode> AccessibilityNodeManager::GetAccessibilityNodeFromPage(NodeId nodeId) const
{
    if (isOhosHostCard_) {
        nodeId = ConvertToNodeId(nodeId);
    }
    auto indexPage = indexPage_.Upgrade();
    if (nodeId == 0 && indexPage) {
        auto rootNode = GetRootNodeIdFromPage(indexPage);
        if (rootNode < 0) {
            LOGW("Failed to get page root node");
            return nullptr;
        }
        nodeId = rootNode + ROOT_STACK_BASE;
    }

    return GetAccessibilityNodeById(nodeId);
}

void AccessibilityNodeManager::ClearNodeRectInfo(RefPtr<AccessibilityNode>& node, bool isPopDialog)
{
    if (!node) {
        return;
    }
    auto children = node->GetChildList();
    for (auto it = children.begin(); it != children.end(); it++) {
        ClearNodeRectInfo(*it, isPopDialog);
    }
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    if (isPopDialog) {
        node->SetClearRectInfoFlag(true);
    } else {
        node->SetClearRectInfoFlag(false);
    }
#endif
}

void AccessibilityNodeManager::SendAccessibilityAsyncEvent(const AccessibilityEvent& accessibilityEvent) {}

int32_t AccessibilityNodeManager::GenerateNextAccessibilityId()
{
    return g_accessibilityId.fetch_add(1, std::memory_order_relaxed);
}

// combined components which pop up through js api, such as dialog/toast
RefPtr<AccessibilityNode> AccessibilityNodeManager::CreateSpecializedNode(
    const std::string& tag, int32_t nodeId, int32_t parentNodeId)
{
    if (nodeId < ROOT_STACK_BASE) {
        return nullptr;
    }
    return CreateAccessibilityNode(tag, nodeId, parentNodeId, -1);
}

RefPtr<AccessibilityNode> AccessibilityNodeManager::CreateAccessibilityNode(
    const std::string& tag, int32_t nodeId, int32_t parentNodeId, int32_t itemIndex)
{
    LOGD("create AccessibilityNode %{public}s, id %{public}d, parent id %{public}d, itemIndex %{public}d", tag.c_str(),
         nodeId, parentNodeId, itemIndex);

    RefPtr<AccessibilityNode> parentNode;
    if (parentNodeId != -1) {
        parentNode = GetAccessibilityNodeById(parentNodeId);
        if (!parentNode) {
            LOGE("Parent node %{private}d not exists", parentNodeId);
            EventReport::SendAccessibilityException(AccessibilityExcepType::CREATE_ACCESSIBILITY_NODE_ERR);
            return nullptr;
        }
    } else {
        // create accessibility root stack node
        auto rootStackId = rootNodeId_ + ROOT_STACK_BASE;
        parentNode = GetAccessibilityNodeById(rootStackId);
        if (!parentNode) {
            parentNode = AceType::MakeRefPtr<AccessibilityNode>(rootStackId, ROOT_STACK_TAG);
            auto result = accessibilityNodes_.try_emplace(rootStackId, parentNode);
            if (!result.second) {
                LOGW("the accessibility node has already in the map");
                return nullptr;
            }
        }
    }

    auto accessibilityNode = AceType::MakeRefPtr<AccessibilityNode>(nodeId, tag);
    auto result = accessibilityNodes_.try_emplace(nodeId, accessibilityNode);
    if (!result.second) {
        LOGW("the accessibility node has already in the map");
        return nullptr;
    }

    accessibilityNode->SetIsRootNode(nodeId == rootNodeId_);
    accessibilityNode->SetPageId(rootNodeId_ - DOM_ROOT_NODE_ID_BASE);
    accessibilityNode->SetParentNode(parentNode);
    accessibilityNode->Mount(itemIndex);
    return accessibilityNode;
}

RefPtr<AccessibilityNode> AccessibilityNodeManager::GetAccessibilityNodeById(NodeId nodeId) const
{
    const auto itNode = accessibilityNodes_.find(nodeId);
    if (itNode == accessibilityNodes_.end()) {
        return nullptr;
    }
    return itNode->second;
}

void AccessibilityNodeManager::RemoveAccessibilityNodes(RefPtr<AccessibilityNode>& node)
{
    if (!node) {
        return;
    }
    auto children = node->GetChildList();
    for (auto it = children.begin(); it != children.end();) {
        RemoveAccessibilityNodes(*it++);
    }
    auto parentId = node->GetParentId();
    RefPtr<AccessibilityNode> parentNode;
    if (parentId != -1) {
        parentNode = GetAccessibilityNodeById(parentId);
        if (parentNode) {
            parentNode->RemoveNode(node);
        }
    }
    LOGD("remove accessibility node %{public}d, remain num %{public}zu", node->GetNodeId(), accessibilityNodes_.size());
    accessibilityNodes_.erase(node->GetNodeId());
}

void AccessibilityNodeManager::RemoveAccessibilityNodeById(NodeId nodeId)
{
    auto accessibilityNode = GetAccessibilityNodeById(nodeId);
    if (!accessibilityNode) {
        LOGW("the accessibility node %{public}d is not in the map", nodeId);
        return;
    }
    RemoveAccessibilityNodes(accessibilityNode);
}

void AccessibilityNodeManager::ClearPageAccessibilityNodes(int32_t pageId)
{
    auto rootNodeId = pageId + ROOT_STACK_BASE;
    auto accessibilityNode = GetAccessibilityNodeById(rootNodeId);
    if (!accessibilityNode) {
        LOGW("the accessibility node %{public}d is not in the map", rootNodeId);
        return;
    }
    RemoveAccessibilityNodes(accessibilityNode);
}

void AccessibilityNodeManager::TrySaveTargetAndIdNode(
    const std::string& id, const std::string& target, const RefPtr<AccessibilityNode>& node)
{
    if (!id.empty()) {
        AddNodeWithId(id, node);
    }

    if (!target.empty()) {
        AddNodeWithTarget(target, node);
    }
}

void AccessibilityNodeManager::HandleComponentPostBinding()
{
    for (auto targetIter = nodeWithTargetMap_.begin(); targetIter != nodeWithTargetMap_.end();) {
        auto nodeWithTarget = targetIter->second.Upgrade();
        if (nodeWithTarget) {
            if (nodeWithTarget->GetTag() == ACCESSIBILITY_TAG_POPUP) {
                auto idNodeIter = nodeWithIdMap_.find(targetIter->first);
                if (idNodeIter != nodeWithIdMap_.end()) {
                    auto nodeWithId = idNodeIter->second.Upgrade();
                    if (nodeWithId) {
                        nodeWithId->SetAccessibilityHint(nodeWithTarget->GetText());
                    } else {
                        nodeWithIdMap_.erase(idNodeIter);
                    }
                }
            }
            ++targetIter;
        } else {
            // clear the disabled node in the maps
            nodeWithTargetMap_.erase(targetIter++);
        }
    }

    // clear the disabled node in the maps
    for (auto idItem = nodeWithIdMap_.begin(); idItem != nodeWithIdMap_.end();) {
        if (!idItem->second.Upgrade()) {
            nodeWithIdMap_.erase(idItem++);
        } else {
            ++idItem;
        }
    }
}

void AccessibilityNodeManager::DumpHandleEvent(const std::vector<std::string>& params) {}

void AccessibilityNodeManager::DumpProperty(const std::vector<std::string>& params) {}

void AccessibilityNodeManager::DumpTree(int32_t depth, NodeId nodeID) {}

void AccessibilityNodeManager::SetCardViewParams(const std::string& key, bool focus) {}

void AccessibilityNodeManager::SetCardViewPosition(int id, float offsetX, float offsetY)
{
    cardOffset_ = Offset(offsetX, offsetY);
    if (id < 0 || id > CARD_MAX_AGP_ID) {
        cardId_ = 0;
    } else {
        cardId_ = id;
    }
    isOhosHostCard_ = true;
    LOGD("setcardview id=%{public}d offsetX=%{public}f, offsetY=%{public}f", id, cardOffset_.GetX(),
         cardOffset_.GetY());
}

} // namespace OHOS::Ace::Framework
