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
#include "core/components_v2/inspector/inspector_composed_element.h"

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
    if (GetVersion() == AccessibilityVersion::JS_DECLARATIVE_VERSION) {
        auto domDocument = page ? page->GetDomDocument() : nullptr;
        if (domDocument) {
            return SetRootNodeId(domDocument->GetRootNodeId());
        } else {
            LOGE("domDocument is null");
        }
    }
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
        LOGE("add node with id failed");
        return;
    }
    nodeWithIdMap_[key] = node;
}

void AccessibilityNodeManager::AddNodeWithTarget(const std::string& key, const RefPtr<AccessibilityNode>& node)
{
    if (!node) {
        LOGE("add node with target failed");
        return;
    }
    nodeWithTargetMap_[key] = node;
}

void AccessibilityNodeManager::AddComposedElement(const std::string& key, const RefPtr<ComposedElement>& node)
{
    if (!node) {
        LOGE("add composed element failed");
        return;
    }
    composedElementIdMap_[key] = node;
}

void AccessibilityNodeManager::RemoveComposedElementById(const std::string& key)
{
    LOGD("remove composed element id:%{public}s", key.c_str());
    auto it = composedElementIdMap_.find(key);
    if (it != composedElementIdMap_.end()) {
        composedElementIdMap_.erase(it);
    }
}

WeakPtr<ComposedElement> AccessibilityNodeManager::GetComposedElementFromPage(NodeId nodeId)
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

    const auto itNode = composedElementIdMap_.find(std::to_string(nodeId));
    if (itNode == composedElementIdMap_.end()) {
        LOGW("Failed to get ComposedElement from Page, id:%{public}d", nodeId);
        return nullptr;
    }
    return itNode->second;
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
    if (IsDeclarative()) {
        return CreateDeclarativeAccessibilityNode(tag, nodeId, parentNodeId, itemIndex);
    } else {
        return CreateCommonAccessibilityNode(tag, nodeId, parentNodeId, itemIndex);
    }
}

RefPtr<AccessibilityNode> AccessibilityNodeManager::CreateDeclarativeAccessibilityNode(
    const std::string& tag, int32_t nodeId, int32_t parentNodeId, int32_t itemIndex)
{
    LOGD("create AccessibilityNode %{public}s, id %{public}d, parent id %{public}d, itemIndex %{public}d", tag.c_str(),
        nodeId, parentNodeId, itemIndex);
    RefPtr<AccessibilityNode> parentNode;
    if (parentNodeId != -1) {
        parentNode = GetAccessibilityNodeById(parentNodeId);
    } else {
        // create accessibility root stack node
        auto rootStackId = rootNodeId_ + ROOT_STACK_BASE;
        parentNode = GetAccessibilityNodeById(rootStackId);
        if (!parentNode) {
            parentNode = AceType::MakeRefPtr<AccessibilityNode>(rootStackId, ROOT_STACK_TAG);
            std::lock_guard<std::mutex> lock(mutex_);
            auto result = accessibilityNodes_.try_emplace(rootStackId, parentNode);

            if (!result.second) {
                LOGW("the accessibility node has already in the map");
                return nullptr;
            }
        }
    }

    auto accessibilityNode = AceType::MakeRefPtr<AccessibilityNode>(nodeId, tag);
    accessibilityNode->SetIsRootNode(nodeId == rootNodeId_);
    accessibilityNode->SetPageId(rootNodeId_ - DOM_ROOT_NODE_ID_BASE);
    accessibilityNode->SetFocusableState(true);
    if (parentNode) {
        accessibilityNode->SetParentNode(parentNode);
        accessibilityNode->Mount(itemIndex);
    }
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto result = accessibilityNodes_.try_emplace(nodeId, accessibilityNode);

        if (!result.second) {
            LOGW("the accessibility node has already in the map");
            return nullptr;
        }
    }
    return accessibilityNode;
}

RefPtr<AccessibilityNode> AccessibilityNodeManager::CreateCommonAccessibilityNode(
    const std::string& tag, int32_t nodeId, int32_t parentNodeId, int32_t itemIndex)
{
    LOGD("create AccessibilityNode %{public}s, id %{public}d, parent id %{public}d, itemIndex %{public}d", tag.c_str(),
        nodeId, parentNodeId, itemIndex);
    RefPtr<AccessibilityNode> parentNode;
    if (parentNodeId != -1) {
        parentNode = GetAccessibilityNodeById(parentNodeId);
        if (!parentNode) {
            LOGD("Parent node %{private}d not exists", parentNodeId);
            EventReport::SendAccessibilityException(AccessibilityExcepType::CREATE_ACCESSIBILITY_NODE_ERR);
            return nullptr;
        }
    } else {
        // create accessibility root stack node
        auto rootStackId = rootNodeId_ + ROOT_STACK_BASE;
        parentNode = GetAccessibilityNodeById(rootStackId);
        if (!parentNode) {
            parentNode = AceType::MakeRefPtr<AccessibilityNode>(rootStackId, ROOT_STACK_TAG);
            std::lock_guard<std::mutex> lock(mutex_);
            auto result = accessibilityNodes_.try_emplace(rootStackId, parentNode);

            if (!result.second) {
                LOGW("the accessibility node has already in the map");
                return nullptr;
            }
        }
    }

    auto accessibilityNode = AceType::MakeRefPtr<AccessibilityNode>(nodeId, tag);
    accessibilityNode->SetIsRootNode(nodeId == rootNodeId_);
    accessibilityNode->SetPageId(rootNodeId_ - DOM_ROOT_NODE_ID_BASE);
    accessibilityNode->SetParentNode(parentNode);
    accessibilityNode->Mount(itemIndex);
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto result = accessibilityNodes_.try_emplace(nodeId, accessibilityNode);

        if (!result.second) {
            LOGW("the accessibility node has already in the map");
            return nullptr;
        }
    }
    return accessibilityNode;
}

RefPtr<AccessibilityNode> AccessibilityNodeManager::GetAccessibilityNodeById(NodeId nodeId) const
{
    std::lock_guard<std::mutex> lock(mutex_);
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
    std::lock_guard<std::mutex> lock(mutex_);
    accessibilityNodes_.erase(node->GetNodeId());
    RemoveVisibleChangeNode(node->GetNodeId());
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

void AccessibilityNodeManager::TriggerVisibleChangeEvent()
{
    if (visibleChangeNodes_.empty()) {
        return;
    }
    for (auto& visibleChangeNode : visibleChangeNodes_) {
        auto visibleNodeId = visibleChangeNode.first;
        auto accessibilityNode = GetAccessibilityNodeById(visibleNodeId);
        if (!accessibilityNode) {
            LOGI("No this accessibility node.");
            continue;
        }
        // IntersectionObserver observes size exclude margin.
        auto marginSize = accessibilityNode->GetMarginSize();
        auto visibleRect = accessibilityNode->GetRect() - marginSize;
        auto globalRect = accessibilityNode->GetGlobalRect() - marginSize;
        auto pipeline = context_.Upgrade();
        if (pipeline) {
            pipeline->GetBoundingRectData(visibleNodeId, globalRect);
            globalRect = globalRect * pipeline->GetViewScale() - marginSize;
        }
        auto& nodeCallbackInfoList = visibleChangeNode.second;
        for (auto& nodeCallbackInfo : nodeCallbackInfoList) {
            if (!globalRect.IsValid() || !accessibilityNode->GetVisible()) {
                if (nodeCallbackInfo.currentVisibleType) {
                    nodeCallbackInfo.currentVisibleType = false;
                    if (nodeCallbackInfo.callback) {
                        nodeCallbackInfo.callback(false, 0.0);
                    }
                }
                continue;
            }
            auto visibleRatio = visibleRect.Width() * visibleRect.Height() / (globalRect.Width() * globalRect.Height());
            visibleRatio = std::clamp(visibleRatio, 0.0, 1.0);
            if (GreatNotEqual(visibleRatio, nodeCallbackInfo.visibleRatio) && !nodeCallbackInfo.currentVisibleType) {
                LOGI("Fire visible event %{public}lf", visibleRatio);
                nodeCallbackInfo.currentVisibleType = true;
                if (nodeCallbackInfo.callback) {
                    nodeCallbackInfo.callback(true, visibleRatio);
                }
            }
            if (LessOrEqual(visibleRatio, nodeCallbackInfo.visibleRatio) && nodeCallbackInfo.currentVisibleType) {
                LOGI("Fire invisible event %{public}lf", visibleRatio);
                nodeCallbackInfo.currentVisibleType = false;
                if (nodeCallbackInfo.callback) {
                    nodeCallbackInfo.callback(false, visibleRatio);
                }
            }
        }
    }
}

void AccessibilityNodeManager::AddVisibleChangeNode(NodeId nodeId, double ratio, VisibleRatioCallback callback)
{
    VisibleCallbackInfo info;
    info.callback = callback;
    info.visibleRatio = ratio;
    info.currentVisibleType = false;
    auto iter = visibleChangeNodes_.find(nodeId);
    if (iter != visibleChangeNodes_.end()) {
        auto& callbackList = visibleChangeNodes_[nodeId];
        callbackList.emplace_back(info);
    } else {
        std::list<VisibleCallbackInfo> callbackList;
        callbackList.emplace_back(info);
        visibleChangeNodes_[nodeId] = callbackList;
    }
}

void AccessibilityNodeManager::RemoveVisibleChangeNode(NodeId nodeId)
{
    auto key = visibleChangeNodes_.find(nodeId);
    if (key != visibleChangeNodes_.end()) {
        visibleChangeNodes_.erase(key);
    }
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

void AccessibilityNodeManager::DumpHandleEvent(const std::vector<std::string>& params) {}

void AccessibilityNodeManager::DumpProperty(const std::vector<std::string>& params) {}

void AccessibilityNodeManager::DumpTree(int32_t depth, NodeId nodeID) {}

std::unique_ptr<JsonValue> AccessibilityNodeManager::DumpComposedElementsToJson() const
{
    auto json = JsonUtil::Create(true);
    auto infos = JsonUtil::CreateArray(false);
    for (auto& [id, element] : composedElementIdMap_) {
        auto inspector = element.Upgrade();
        if (inspector) {
            auto info = JsonUtil::Create(false);
            info->Put("id", id.c_str());
            info->Put("type", TypeInfoHelper::TypeName(*inspector));
            infos->Put(info);
        }
    }
    json->Put("inspectors", infos);
    return json;
}

std::unique_ptr<JsonValue> AccessibilityNodeManager::DumpComposedElementToJson(NodeId nodeId)
{
    auto composedElement = GetComposedElementFromPage(nodeId);
    auto inspector = AceType::DynamicCast<V2::InspectorComposedElement>(composedElement.Upgrade());
    if (!inspector) {
        LOGE("this is not Inspector composed element");
        return nullptr;
    }
    return inspector->ToJsonObject();
}

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
    LOGD(
        "setcardview id=%{public}d offsetX=%{public}f, offsetY=%{public}f", id, cardOffset_.GetX(), cardOffset_.GetY());
}

void AccessibilityNodeManager::UpdateEventTarget(NodeId id, BaseEventInfo& info)
{
    auto composedElement = GetComposedElementFromPage(id);
    auto inspector = AceType::DynamicCast<V2::InspectorComposedElement>(composedElement.Upgrade());
    if (!inspector) {
        LOGE("this is not Inspector composed element");
        return;
    }
    auto rectInLocal = inspector->GetRenderRectInLocal();
    auto rectInGlobal = inspector->GetRenderRect();
    auto marginLeft = inspector->GetMargin(AnimatableType::PROPERTY_MARGIN_LEFT).ConvertToPx();
    auto marginRight = inspector->GetMargin(AnimatableType::PROPERTY_MARGIN_RIGHT).ConvertToPx();
    auto marginTop = inspector->GetMargin(AnimatableType::PROPERTY_MARGIN_TOP).ConvertToPx();
    auto marginBottom = inspector->GetMargin(AnimatableType::PROPERTY_MARGIN_BOTTOM).ConvertToPx();
    auto& target = info.GetTargetWichModify();
    target.area.SetOffset(DimensionOffset(
        Offset(rectInLocal.GetOffset().GetX() + marginLeft, rectInLocal.GetOffset().GetY() + marginTop)));
    target.area.SetGlobaleOffset(DimensionOffset(
        Offset(rectInGlobal.GetOffset().GetX() + marginLeft, rectInGlobal.GetOffset().GetY() + marginTop)));
    target.area.SetWidth(Dimension(rectInLocal.Width() - marginLeft - marginRight));
    target.area.SetHeight(Dimension(rectInLocal.Height() - marginTop - marginBottom));
}

bool AccessibilityNodeManager::IsDeclarative()
{
    auto context = context_.Upgrade();
    if (!context) {
        return false;
    }

    return context->GetIsDeclarative();
}

} // namespace OHOS::Ace::Framework
