/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "frameworks/core/pipeline/base/element_register.h"

#include <atomic>

#include "base/utils/multi_thread.h"
#include "core/common/layout_inspector.h"
#include "core/components_v2/common/element_proxy.h"
#include "frameworks/core/pipeline/base/element_register_multi_thread.h"

namespace OHOS::Ace {
class ElementRegisterImpl {
public:
    RefPtr<Element> GetElementById(ElementIdType elementId);
    RefPtr<V2::ElementProxy> GetElementProxyById(ElementIdType elementId);

    RefPtr<AceType> GetNodeById(ElementIdType elementId);

    bool AddElementProxy(const WeakPtr<V2::ElementProxy>& element);
    bool AddElement(const RefPtr<Element>& element);

    RefPtr<NG::UINode> GetUINodeById(ElementIdType elementId);
    NG::FrameNode* GetFrameNodePtrById(ElementIdType elementId);

    bool AddUINode(const RefPtr<NG::UINode>& node);
    bool Exists(ElementIdType elementId);
    std::vector<RefPtr<NG::UINode>> GetUINodesFromItemMap(const std::vector<std::int32_t>& keys);

    /**
     * When a custom node is created from recycle, update its element id.
     */
    void UpdateRecycleElmtId(int32_t oldElmtId, int32_t newElmtId);

    /**
     * remove Element with given elmtId from the Map
     * means GetElementById on this elmtId no longer returns an Element
     * method adds the elmtId to the removed Element Set
     */
    bool RemoveItem(ElementIdType elementId);

    /**
     * remove Element with given elmtId from the Map
     * means GetElementById on this elmtId no longer returns an Element
     * method does NOT add the elmtId to the removed Element Set
     * Use with caution: e.g. only use when knowing the Element will
     * be added with new ElementId shortly
     */
    bool RemoveItemSilently(ElementIdType elementId);

    void MoveRemovedItems(RemovedElementsType& removedItems);

    /**
     * does a complete reset
     * clears the Map of Elements and Set of removed Elements
     */
    void Clear();

    ElementIdType MakeUniqueId();

    /**
     * For ArkTS 1.2
     *
     * Based on the incoming capacity, generate the starting value for arkoala node IDs
     * and adjust the nextUniqueElementId_ value.
     */
    ElementIdType RequireArkoalaNodeId(int32_t capacity);

    RefPtr<NG::GeometryTransition> GetOrCreateGeometryTransition(
        const std::string& id, bool followWithoutTransition = false, bool doRegisterSharedTransition = true);
    void DumpGeometryTransition();

    void ReSyncGeometryTransition(
        const WeakPtr<NG::FrameNode>& trigger = nullptr, const AnimationOption& option = AnimationOption());

    void AddPendingRemoveNode(const RefPtr<NG::UINode>& node);
    void ClearPendingRemoveNodes();
    uint32_t GetNodeNum() const
    {
        return itemMap_.size();
    }

    ElementIdType GetLatestElementId() const
    {
        return latestElementId_;
    }

    RefPtr<NG::FrameNode> GetAttachedFrameNodeById(
        const std::string& key, bool willGetAll = false, int32_t instanceId = -1);

    void AddFrameNodeByInspectorId(const std::string& key, const WeakPtr<NG::FrameNode>& node, int32_t nodeId);

    void RemoveFrameNodeByInspectorId(const std::string& key, int32_t nodeId);

    void RegisterEmbedNode(const uint64_t surfaceId, const WeakPtr<NG::FrameNode>& node);

    void UnregisterEmbedNode(const uint64_t surfaceId, const WeakPtr<NG::FrameNode>& node);

    WeakPtr<NG::FrameNode> GetEmbedNodeBySurfaceId(const uint64_t surfaceId);

    bool IsEmbedNode(NG::FrameNode* node);

    uint64_t GetSurfaceIdByEmbedNode(NG::FrameNode* node);

    bool AddReferenced(ElementIdType elmtId, const WeakPtr<AceType>& referenced);

    void IterateElements(const std::function<bool(ElementIdType, const RefPtr<AceType>&)>& visitor) const
    {
        for (auto& [k, v] : itemMap_) {
            if (visitor(k, v.Upgrade())) {
                break;
            }
        }
    }
private:
    // ElementID assigned during initial render
    // first to Component, then synced to Element
    static std::atomic<ElementIdType> nextUniqueElementId_;

    ElementIdType latestElementId_ = 0;

    // Map for created elements
    std::unordered_map<ElementIdType, WeakPtr<AceType>> itemMap_;

    // Map for inspectorId
    std::unordered_map<std::string, std::unordered_map<int32_t, WeakPtr<NG::FrameNode>>> inspectorIdMap_;

    RemovedElementsType removedItems_;

    std::unordered_map<std::string, RefPtr<NG::GeometryTransition>> geometryTransitionMap_;

    std::list<RefPtr<NG::UINode>> pendingRemoveNodes_;

    std::unordered_map<uint64_t, WeakPtr<NG::FrameNode>> surfaceIdEmbedNodeMap_;

    std::unordered_map<NG::FrameNode*, uint64_t> embedNodeSurfaceIdMap_;
};

static thread_local ElementRegisterImpl* g_instance;

class ElementRegisterHolder {
public:
    ElementRegisterHolder()
    {
        g_instance = new ElementRegisterImpl();
    }
    ~ElementRegisterHolder()
    {
        if (g_instance) {
            delete g_instance;
            g_instance = nullptr;
        }
    }
};

std::atomic<ElementIdType> ElementRegisterImpl::nextUniqueElementId_ = 0;

ElementRegister* ElementRegister::GetInstance()
{
    thread_local ElementRegisterHolder instanceHolder;
    static_assert(sizeof(ElementRegister) == 1, "");
    static ElementRegister instance;
    return &instance;
}

ElementIdType ElementRegisterImpl::MakeUniqueId()
{
    return ElementRegisterImpl::nextUniqueElementId_++;
}

ElementIdType ElementRegisterImpl::RequireArkoalaNodeId(int32_t capacity)
{
    return ElementRegisterImpl::nextUniqueElementId_.fetch_add(capacity);
}

RefPtr<Element> ElementRegisterImpl::GetElementById(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return nullptr;
    }
    auto position = itemMap_.find(elementId);
    return position == itemMap_.end() ? nullptr : AceType::DynamicCast<Element>(position->second).Upgrade();
}

RefPtr<AceType> ElementRegisterImpl::GetNodeById(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return nullptr;
    }
    auto position = itemMap_.find(elementId);
    return position == itemMap_.end() ? nullptr : position->second.Upgrade();
}

RefPtr<V2::ElementProxy> ElementRegisterImpl::GetElementProxyById(ElementIdType elementId)
{
    auto position = itemMap_.find(elementId);
    return (position == itemMap_.end()) ? nullptr : AceType::DynamicCast<V2::ElementProxy>(position->second).Upgrade();
}

bool ElementRegisterImpl::Exists(ElementIdType elementId)
{
    return (itemMap_.find(elementId) != itemMap_.end());
}

void ElementRegisterImpl::UpdateRecycleElmtId(int32_t oldElmtId, int32_t newElmtId)
{
    if (!Exists(oldElmtId)) {
        return;
    }
    auto node = GetNodeById(oldElmtId);
    if (node) {
        itemMap_.erase(oldElmtId);
        AddReferenced(newElmtId, node);
    }
}

bool ElementRegisterImpl::AddReferenced(ElementIdType elmtId, const WeakPtr<AceType>& referenced)
{
    auto result = itemMap_.emplace(elmtId, referenced);
    if (!result.second) {
        LOGE("Duplicate elmtId %{public}d error.", elmtId);
    }
    latestElementId_ = elmtId;
    return result.second;
}

bool ElementRegisterImpl::AddElement(const RefPtr<Element>& element)
{
    if ((element == nullptr) || (element->GetElementId() == ElementRegister::UndefinedElementId)) {
        return false;
    }

    return AddReferenced(element->GetElementId(), element);
}

bool ElementRegisterImpl::AddElementProxy(const WeakPtr<V2::ElementProxy>& elementProxy)
{
    auto elmt = elementProxy.Upgrade();
    if (!elmt) {
        LOGE("Add: No ElementProxy or invalid id");
        return false;
    }

    if (elmt->GetElementId() == ElementRegister::UndefinedElementId) {
        // this is not an error case, because only main Elements have defined elmtIds
        return false;
    }

    return AddReferenced(elmt->GetElementId(), elementProxy);
}

RefPtr<NG::UINode> ElementRegisterImpl::GetUINodeById(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return nullptr;
    }
    auto iter = itemMap_.find(elementId);
    return iter == itemMap_.end() ? nullptr : AceType::DynamicCast<NG::UINode>(iter->second).Upgrade();
}

NG::FrameNode* ElementRegisterImpl::GetFrameNodePtrById(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return nullptr;
    }
    auto iter = itemMap_.find(elementId);
    if (iter == itemMap_.end()) {
        return nullptr;
    }
    auto node = AceType::DynamicCast<NG::FrameNode>(iter->second.Upgrade());
    return AceType::RawPtr(node); // warning: returning an unsafe rawptr !!!
}

std::vector<RefPtr<NG::UINode>> ElementRegisterImpl::GetUINodesFromItemMap(
    const std::vector<std::int32_t>& keys)
{
    std::vector<RefPtr<NG::UINode>> children;
    for (auto& iter : itemMap_) {
        if (std::find(keys.begin(), keys.end(), iter.first) == keys.end()) {
            auto uiNode = GetUINodeById(iter.first);
            CHECK_NULL_CONTINUE(uiNode);
            children.emplace_back(uiNode);
        }
    }
    return children;
}
 
void TriggerRsProfilerNodeMountCallbackIfExist(const RefPtr<NG::UINode>& node)
{
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
    auto callback = LayoutInspector::GetRsProfilerNodeMountCallback();
    if (callback) {
        int32_t parentId = -1;
        if (node->GetParent()) {
            parentId = node->GetParent()->GetId();
        }
        uint64_t rsNodeId = 0;
        auto frameNode = AceType::DynamicCast<NG::FrameNode>(node);
        if (frameNode != nullptr) {
            CHECK_NULL_VOID(frameNode->GetRenderContext());
            rsNodeId = frameNode->GetRenderContext()->GetNodeId();
        }
        FrameNodeInfo info { rsNodeId, node->GetId(), node->GetTag(), node->GetDebugLine(), parentId };
        callback(info);
    }
#endif
}

bool ElementRegisterImpl::AddUINode(const RefPtr<NG::UINode>& node)
{
    FREE_NODE_CHECK(node, ElementRegisterMultiThread::GetInstance()->AddUINode, node);
    if (!node || (node->GetId() == ElementRegister::UndefinedElementId)) {
        return false;
    }
    TriggerRsProfilerNodeMountCallbackIfExist(node);
    return AddReferenced(node->GetId(), node);
}

bool ElementRegisterImpl::RemoveItem(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return false;
    }
    auto removed = itemMap_.erase(elementId);
    if (removed) {
        removedItems_.insert(elementId);
    }
    return removed;
}

bool ElementRegisterImpl::RemoveItemSilently(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return false;
    }

    auto removed = itemMap_.erase(elementId);
    return removed;
}

void ElementRegisterImpl::MoveRemovedItems(RemovedElementsType& removedItems)
{
    removedItems = removedItems_;
    removedItems_.clear();
}

void ElementRegisterImpl::Clear()
{
    itemMap_.clear();
    removedItems_.clear();
    geometryTransitionMap_.clear();
    pendingRemoveNodes_.clear();
}

RefPtr<NG::GeometryTransition> ElementRegisterImpl::GetOrCreateGeometryTransition(
    const std::string& id, bool followWithoutTransition, bool doRegisterSharedTransition)
{
    if (id.empty()) {
        return nullptr;
    }
    auto it = geometryTransitionMap_.find(id);
    if (it == geometryTransitionMap_.end()) {
        auto geometryTransition =
            AceType::MakeRefPtr<NG::GeometryTransition>(id, followWithoutTransition, doRegisterSharedTransition);
        geometryTransitionMap_.emplace(id, geometryTransition);
        return geometryTransition;
    } else {
        return it->second;
    }
    return nullptr;
}

void ElementRegisterImpl::DumpGeometryTransition()
{
    auto iter = geometryTransitionMap_.begin();
    while (iter != geometryTransitionMap_.end()) {
        auto [itemId, item] = *iter;
        if (!item || item->IsInAndOutEmpty()) {
            iter = geometryTransitionMap_.erase(iter);
        } else {
            iter++;
        }
    }
}

void ElementRegisterImpl::ReSyncGeometryTransition(const WeakPtr<NG::FrameNode>& trigger, const AnimationOption& option)
{
    for (auto iter = geometryTransitionMap_.begin(); iter != geometryTransitionMap_.end();) {
        if (!iter->second || iter->second->IsInAndOutEmpty()) {
            iter = geometryTransitionMap_.erase(iter);
        } else {
            iter->second->OnReSync(trigger, option);
            ++iter;
        }
    }
}

void ElementRegisterImpl::AddPendingRemoveNode(const RefPtr<NG::UINode>& node)
{
    pendingRemoveNodes_.emplace_back(node);
}

void ElementRegisterImpl::ClearPendingRemoveNodes()
{
    pendingRemoveNodes_.clear();
}

RefPtr<NG::FrameNode> ElementRegisterImpl::GetAttachedFrameNodeById(
    const std::string& key, bool willGetAll, int32_t instanceId)
{
    auto it = inspectorIdMap_.find(key);
    CHECK_NULL_RETURN(it != inspectorIdMap_.end(), nullptr);
    CHECK_NULL_RETURN(!it->second.empty(), nullptr);
    int32_t depth = INT32_MAX;
    RefPtr<NG::FrameNode> frameNode;
    for (const auto& [nodeId, weakNode] : it->second) {
        auto uiNode = weakNode.Upgrade();
        if (!uiNode) {
            continue;
        }
        auto depOfNode = uiNode->GetDepth();
        bool withInScope = willGetAll || uiNode->IsOnMainTree();
        bool checkInstanceId = instanceId == -1 ? true : uiNode->GetInstanceId() == instanceId;
        if (withInScope && uiNode->GetInspectorId().value_or("") == key && depth > depOfNode && checkInstanceId) {
            depth = depOfNode;
            frameNode = uiNode;
        }
    }
    return frameNode;
}

void ElementRegisterImpl::AddFrameNodeByInspectorId(const std::string& key,
    const WeakPtr<NG::FrameNode>& node, int32_t nodeId)
{
    inspectorIdMap_[key][nodeId] = node;
}

void ElementRegisterImpl::RemoveFrameNodeByInspectorId(const std::string& key, int32_t nodeId)
{
    auto it = inspectorIdMap_.find(key);
    CHECK_NULL_VOID(it != inspectorIdMap_.end());
    CHECK_NULL_VOID(!it->second.empty());
    auto& innerMap = it->second;
    innerMap.erase(nodeId);
    if (it->second.empty()) {
        inspectorIdMap_.erase(it);
    }
}

void ElementRegisterImpl::RegisterEmbedNode(const uint64_t surfaceId, const WeakPtr<NG::FrameNode>& node)
{
    surfaceIdEmbedNodeMap_[surfaceId] = node;
    auto nodeRef = node.Upgrade();
    CHECK_NULL_VOID(nodeRef);
    embedNodeSurfaceIdMap_[AceType::RawPtr(nodeRef)] = surfaceId;
}

void ElementRegisterImpl::UnregisterEmbedNode(const uint64_t surfaceId, const WeakPtr<NG::FrameNode>& node)
{
    surfaceIdEmbedNodeMap_.erase(surfaceId);
    auto nodeRef = node.Upgrade();
    CHECK_NULL_VOID(nodeRef);
    NG::FrameNode* nodePtr = AceType::RawPtr(nodeRef);
    embedNodeSurfaceIdMap_.erase(nodePtr);
}

WeakPtr<NG::FrameNode> ElementRegisterImpl::GetEmbedNodeBySurfaceId(const uint64_t surfaceId)
{
    auto it = surfaceIdEmbedNodeMap_.find(surfaceId);
    if (SystemProperties::GetDebugEnabled()) {
        LOGI("[GetEmbedNodeBySurfaceId] surfaceId: %{public}" PRId64 ", result: %{public}s", surfaceId,
            (it == surfaceIdEmbedNodeMap_.end()) ? "false" : "true");
    }
    return (it == surfaceIdEmbedNodeMap_.end()) ? nullptr : it->second;
}

bool ElementRegisterImpl::IsEmbedNode(NG::FrameNode* node)
{
    return (embedNodeSurfaceIdMap_.find(node) != embedNodeSurfaceIdMap_.end());
}

uint64_t ElementRegisterImpl::GetSurfaceIdByEmbedNode(NG::FrameNode* node)
{
    auto it = embedNodeSurfaceIdMap_.find(node);
    if (SystemProperties::GetDebugEnabled()) {
        LOGI("[GetSurfaceIdByEmbedNode] frameNodeId: %{public}d, surfaceId: %{public}" PRId64 "",
            (node == nullptr ? -1 : node->GetId()), (it == embedNodeSurfaceIdMap_.end()) ? 0U : (it->second));
    }
    return (it == embedNodeSurfaceIdMap_.end()) ? 0U : it->second;
}

#define DELEGATE(method, ret...)                     \
    /*(void)instanceHolder; we must keep this line*/ \
    if (g_instance) {                                \
        return g_instance->method;                   \
    }                                                \
    return ret

RefPtr<Element> ElementRegister::GetElementById(ElementIdType elementId)
{
    DELEGATE(GetElementById(elementId), nullptr);
}

RefPtr<V2::ElementProxy> ElementRegister::GetElementProxyById(ElementIdType elementId)
{
    DELEGATE(GetElementProxyById(elementId), nullptr);
}

RefPtr<AceType> ElementRegister::GetNodeById(ElementIdType elementId)
{
    DELEGATE(GetNodeById(elementId), nullptr);
}

bool ElementRegister::AddElementProxy(const WeakPtr<V2::ElementProxy>& element)
{
    DELEGATE(AddElementProxy(element), false);
}

bool ElementRegister::AddElement(const RefPtr<Element>& element)
{
    DELEGATE(AddElement(element), false);
}

RefPtr<NG::UINode> ElementRegister::GetUINodeById(ElementIdType elementId)
{
    DELEGATE(GetUINodeById(elementId), nullptr);
}

NG::FrameNode* ElementRegister::GetFrameNodePtrById(ElementIdType elementId)
{
    DELEGATE(GetFrameNodePtrById(elementId), nullptr);
}

bool ElementRegister::AddUINode(const RefPtr<NG::UINode>& node)
{
    DELEGATE(AddUINode(node), false);
}

std::vector<RefPtr<NG::UINode>> ElementRegister::GetUINodesFromItemMap(const std::vector<std::int32_t>& keys)
{
    std::vector<RefPtr<NG::UINode>> children;
    DELEGATE(GetUINodesFromItemMap(keys), children);
}

bool ElementRegister::Exists(ElementIdType elementId)
{
    DELEGATE(Exists(elementId), false);
}

void ElementRegister::UpdateRecycleElmtId(int32_t oldElmtId, int32_t newElmtId)
{
    DELEGATE(UpdateRecycleElmtId(oldElmtId, newElmtId));
}

bool ElementRegister::RemoveItem(ElementIdType elementId)
{
    DELEGATE(RemoveItem(elementId), false);
}

bool ElementRegister::RemoveItemSilently(ElementIdType elementId)
{
    DELEGATE(RemoveItemSilently(elementId), false);
}

void ElementRegister::MoveRemovedItems(RemovedElementsType& removedItems)
{
    DELEGATE(MoveRemovedItems(removedItems));
}
void ElementRegister::Clear()
{
    DELEGATE(Clear());
}

ElementIdType ElementRegister::MakeUniqueId()
{
    DELEGATE(MakeUniqueId(), ElementRegister::UndefinedElementId);
}

ElementIdType ElementRegister::RequireArkoalaNodeId(int32_t capacity)
{
    DELEGATE(RequireArkoalaNodeId(capacity), ElementRegister::UndefinedElementId);
}

RefPtr<NG::GeometryTransition> ElementRegister::GetOrCreateGeometryTransition(
    const std::string& id, bool followWithoutTransition, bool doRegisterSharedTransition)
{
    DELEGATE(GetOrCreateGeometryTransition(id, followWithoutTransition, doRegisterSharedTransition), nullptr);
}

void ElementRegister::DumpGeometryTransition()
{
    DELEGATE(DumpGeometryTransition());
}

void ElementRegister::ReSyncGeometryTransition(const WeakPtr<NG::FrameNode>& trigger, const AnimationOption& option)
{
    DELEGATE(ReSyncGeometryTransition(trigger, option));
}

void ElementRegister::AddPendingRemoveNode(const RefPtr<NG::UINode>& node)
{
    DELEGATE(AddPendingRemoveNode(node));
}
void ElementRegister::ClearPendingRemoveNodes()
{
    DELEGATE(ClearPendingRemoveNodes());
}

uint32_t ElementRegister::GetNodeNum() const
{
    DELEGATE(GetNodeNum(), 0);
}

ElementIdType ElementRegister::GetLatestElementId() const
{
    DELEGATE(GetLatestElementId(), ElementRegister::UndefinedElementId);
}

RefPtr<NG::FrameNode> ElementRegister::GetAttachedFrameNodeById(
    const std::string& key, bool willGetAll, int32_t instanceId)
{
    DELEGATE(GetAttachedFrameNodeById(key, willGetAll, instanceId), nullptr);
}

void ElementRegister::AddFrameNodeByInspectorId(const std::string& key,
    const WeakPtr<NG::FrameNode>& node, int32_t nodeId)
{
    DELEGATE(AddFrameNodeByInspectorId(key, node, nodeId));
}

void ElementRegister::RemoveFrameNodeByInspectorId(const std::string& key, int32_t nodeId)
{
    DELEGATE(RemoveFrameNodeByInspectorId(key, nodeId));
}

void ElementRegister::RegisterEmbedNode(const uint64_t surfaceId, const WeakPtr<NG::FrameNode>& node)
{
    DELEGATE(RegisterEmbedNode(surfaceId, node));
}

void ElementRegister::UnregisterEmbedNode(const uint64_t surfaceId, const WeakPtr<NG::FrameNode>& node)
{
    DELEGATE(UnregisterEmbedNode(surfaceId, node));
}

WeakPtr<NG::FrameNode> ElementRegister::GetEmbedNodeBySurfaceId(const uint64_t surfaceId)
{
    DELEGATE(GetEmbedNodeBySurfaceId(surfaceId), nullptr);
}

bool ElementRegister::IsEmbedNode(NG::FrameNode* node)
{
    DELEGATE(IsEmbedNode(node), false);
}

uint64_t ElementRegister::GetSurfaceIdByEmbedNode(NG::FrameNode* node)
{
    DELEGATE(GetSurfaceIdByEmbedNode(node), 0U);
}

bool ElementRegister::AddReferenced(ElementIdType elmtId, const WeakPtr<AceType>& referenced)
{
    DELEGATE(AddReferenced(elmtId, referenced), false);
}

void ElementRegister::IterateElements(const std::function<bool(ElementIdType, const RefPtr<AceType>&)>& visitor) const
{
    DELEGATE(IterateElements(visitor));
}
} // namespace OHOS::Ace
