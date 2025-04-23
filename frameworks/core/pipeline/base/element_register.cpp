/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/common/multi_thread_build_manager.h"
#include "core/components_v2/common/element_proxy.h"

namespace OHOS::Ace {
thread_local ElementRegister* ElementRegister::instance_ = nullptr;
ElementRegister* ElementRegister::globalInstance_ = nullptr;
std::recursive_mutex ElementRegister::mutex_;

ElementRegister* ElementRegister::GetGlobalInstance()
{
    if (ElementRegister::globalInstance_ == nullptr) {
        std::lock_guard<std::recursive_mutex> lock(mutex_);
        if (!ElementRegister::globalInstance_) {
            ElementRegister::globalInstance_ = new ElementRegister();
        }
    }
    return (ElementRegister::globalInstance_);
}

ElementRegister* ElementRegister::GetInstance()
{
    if (MultiThreadBuildManager::IsThreadSafeScope()) {
        return GetGlobalInstance();
    }
    if (ElementRegister::instance_ == nullptr) {
        std::lock_guard<std::recursive_mutex> lock(mutex_);
        if (!ElementRegister::instance_) {
            ElementRegister::instance_ =
                MultiThreadBuildManager::IsOnUIThread() ? GetGlobalInstance() : new ElementRegister();
        }
    }
    return (ElementRegister::instance_);
}

RefPtr<Element> ElementRegister::GetElementById(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return nullptr;
    }
    auto position = itemMap_.find(elementId);
    return position == itemMap_.end() ? nullptr : AceType::DynamicCast<Element>(position->second).Upgrade();
}

RefPtr<AceType> ElementRegister::GetNodeById(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return nullptr;
    }
    if (!MultiThreadBuildManager::IsThreadSafeScopeOnSubThread()) {
        auto position = itemMap_.find(elementId);
        if (position != itemMap_.end()) {
            return position->second.Upgrade();
        }
    }
    std::lock_guard<std::mutex> lock(itemSafeMapMutex_);
    auto position = itemSafeMap_.find(elementId);
    return position == itemSafeMap_.end() ? nullptr : position->second.Upgrade();
}

RefPtr<V2::ElementProxy> ElementRegister::GetElementProxyById(ElementIdType elementId)
{
    auto position = itemMap_.find(elementId);
    return (position == itemMap_.end()) ? nullptr : AceType::DynamicCast<V2::ElementProxy>(position->second).Upgrade();
}

bool ElementRegister::Exists(ElementIdType elementId)
{
    return ExistsUnSafely(elementId) || ExistsSafely(elementId);
}

bool ElementRegister::ExistsUnSafely(ElementIdType elementId)
{
    return (itemMap_.find(elementId) != itemMap_.end());
}

bool ElementRegister::ExistsSafely(ElementIdType elementId)
{
    std::lock_guard<std::mutex> lock(itemSafeMapMutex_);
    return (itemSafeMap_.find(elementId) != itemSafeMap_.end());
}

void ElementRegister::UpdateRecycleElmtId(int32_t oldElmtId, int32_t newElmtId)
{
    auto node = GetNodeById(oldElmtId);
    if (!node) {
        return;
    }
    if (ExistsUnSafely(oldElmtId)) {
        itemMap_.erase(oldElmtId);
        AddReferenced(newElmtId, node);
    } else {
        std::lock_guard<std::mutex> lock(itemSafeMapMutex_);
        itemSafeMap_.erase(oldElmtId);
        AddReferencedSafely(newElmtId, node);
    }
}

bool ElementRegister::AddReferencedSafely(ElementIdType elmtId, const WeakPtr<AceType>& referenced)
{
    std::lock_guard<std::mutex> lock(itemSafeMapMutex_);
    auto result = itemSafeMap_.emplace(elmtId, referenced);
    if (!result.second) {
        LOGE("Duplicate elmtId %{public}d error.", elmtId);
    }
    return result.second;
}

bool ElementRegister::AddReferenced(ElementIdType elmtId, const WeakPtr<AceType>& referenced)
{
    auto result = itemMap_.emplace(elmtId, referenced);
    if (!result.second) {
        LOGE("Duplicate elmtId %{public}d error.", elmtId);
    }
    lastestElementId_ = elmtId;
    return result.second;
}

bool ElementRegister::AddElement(const RefPtr<Element>& element)
{
    if ((element == nullptr) || (element->GetElementId() == ElementRegister::UndefinedElementId)) {
        return false;
    }

    return AddReferenced(element->GetElementId(), element);
}

bool ElementRegister::AddElementProxy(const WeakPtr<V2::ElementProxy>& elementProxy)
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

RefPtr<NG::UINode> ElementRegister::GetUINodeById(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return nullptr;
    }
    if (!MultiThreadBuildManager::IsThreadSafeScopeOnSubThread()) {
        auto iter = itemMap_.find(elementId);
        if (iter != itemMap_.end()) {
            return AceType::DynamicCast<NG::UINode>(iter->second).Upgrade();
        }
    }
    std::lock_guard<std::mutex> lock(itemSafeMapMutex_);
    auto iter = itemSafeMap_.find(elementId);
    return iter == itemSafeMap_.end() ? nullptr : AceType::DynamicCast<NG::UINode>(iter->second).Upgrade();
}

NG::FrameNode* ElementRegister::GetFrameNodePtrById(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return nullptr;
    }
    if (!MultiThreadBuildManager::IsThreadSafeScopeOnSubThread()) {
        auto iter = itemMap_.find(elementId);
        if (iter != itemMap_.end()) {
            auto node = AceType::DynamicCast<NG::FrameNode>(iter->second.Upgrade());
            return AceType::RawPtr(node);
        }
    }
    std::lock_guard<std::mutex> lock(itemSafeMapMutex_);
    auto iter = itemSafeMap_.find(elementId);
    auto node = AceType::DynamicCast<NG::FrameNode>(iter->second.Upgrade());
    return AceType::RawPtr(node); // warning: returning an unsafe rawptr !!!
}

bool ElementRegister::AddUINode(const RefPtr<NG::UINode>& node)
{
    if (!node || (node->GetId() == ElementRegister::UndefinedElementId)) {
        return false;
    }

    if (node->IsMultiThreadNode()) {
        return AddReferencedSafely(node->GetId(), node);
    } else {
        return AddReferenced(node->GetId(), node);
    }
}

bool ElementRegister::RemoveItem(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return false;
    }
    bool removed = false;
    if (!MultiThreadBuildManager::IsThreadSafeScopeOnSubThread()) {
        removed = itemMap_.erase(elementId);
        if (removed) {
            removedItems_.insert(elementId);
            return removed;
        }
    }
    std::lock_guard<std::mutex> lock(itemSafeMapMutex_);
    removed = itemSafeMap_.erase(elementId);
    if (removed) {
        removedSafelyItems_.insert(elementId);
    }
    return removed;
}

bool ElementRegister::RemoveItemSilently(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return false;
    }
    bool removed = false;
    if (!MultiThreadBuildManager::IsThreadSafeScopeOnSubThread()) {
        removed = itemMap_.erase(elementId);
    }
    if (!removed) {
        std::lock_guard<std::mutex> lock(itemSafeMapMutex_);
        removed = itemSafeMap_.erase(elementId);
    }
    return removed;
}

void ElementRegister::MoveRemovedItems(RemovedElementsType& removedItems)
{
    if (!MultiThreadBuildManager::IsThreadSafeScopeOnSubThread()) {
        removedItems = removedItems_;
        removedItems_.clear();
    }
    std::lock_guard<std::mutex> lock(itemSafeMapMutex_);
    removedItems.insert(removedSafelyItems_.begin(), removedSafelyItems_.end());
    removedSafelyItems_.clear();
}

void ElementRegister::Clear()
{
    itemMap_.clear();
    removedItems_.clear();
    geometryTransitionMap_.clear();
    pendingRemoveNodes_.clear();
    {
        std::lock_guard<std::mutex> lock(itemSafeMapMutex_);
        itemSafeMap_.clear();
        removedSafelyItems_.clear();
    }
}

RefPtr<NG::GeometryTransition> ElementRegister::GetOrCreateGeometryTransition(
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

void ElementRegister::DumpGeometryTransition()
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

void ElementRegister::ReSyncGeometryTransition(const WeakPtr<NG::FrameNode>& trigger, const AnimationOption& option)
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

void ElementRegister::AddPendingRemoveNode(const RefPtr<NG::UINode>& node)
{
    pendingRemoveNodes_.emplace_back(node);
}

void ElementRegister::ClearPendingRemoveNodes()
{
    pendingRemoveNodes_.clear();
}

RefPtr<NG::FrameNode> ElementRegister::GetAttachedFrameNodeById(const std::string& key, bool willGetAll)
{
    auto it = inspectorIdMap_.find(key);
    if (it == inspectorIdMap_.end()) {
        std::lock_guard<std::mutex> lock(inspectorIdSafeMapMutex_);
        it = inspectorIdSafeMap_.find(key);
        CHECK_NULL_RETURN(it != inspectorIdSafeMap_.end(), nullptr);
    }
    CHECK_NULL_RETURN(!it->second.empty(), nullptr);
    int32_t depth = INT32_MAX;
    RefPtr<NG::FrameNode> frameNode;
    for (const auto& node : it->second) {
        auto uiNode = node.Upgrade();
        if (!uiNode) {
            continue;
        }
        auto depOfNode = uiNode->GetDepth();
        bool withInScope = willGetAll || (!willGetAll && uiNode->IsOnMainTree());
        if (withInScope && uiNode->GetInspectorId().value_or("") == key && depth > depOfNode) {
            depth = depOfNode;
            frameNode = uiNode;
        }
    }
    return frameNode;
}

void ElementRegister::AddFrameNodeByInspectorId(const std::string& key, const WeakPtr<NG::FrameNode>& node)
{
    if (node.Upgrade() && node.Upgrade()->IsMultiThreadNode()) {
        std::lock_guard<std::mutex> lock(inspectorIdSafeMapMutex_);
        auto it = inspectorIdSafeMap_.find(key);
        if (it != inspectorIdSafeMap_.end()) {
            it->second.push_back(node);
        } else {
            std::list<WeakPtr<NG::FrameNode>> nodeList = { node };
            inspectorIdSafeMap_.try_emplace(key, nodeList);
        }
        return;
    }
    auto it = inspectorIdMap_.find(key);
    if (it != inspectorIdMap_.end()) {
        it->second.push_back(node);
    } else {
        std::list<WeakPtr<NG::FrameNode>> nodeList = { node };
        inspectorIdMap_.try_emplace(key, nodeList);
    }
}

void ElementRegister::RemoveFrameNodeByInspectorId(const std::string& key, int32_t nodeId, bool isMultiThreadNode)
{
    if (isMultiThreadNode) {
        std::lock_guard<std::mutex> lock(inspectorIdSafeMapMutex_);
        auto it = inspectorIdSafeMap_.find(key);
        CHECK_NULL_VOID(it != inspectorIdSafeMap_.end());
        CHECK_NULL_VOID(!it->second.empty());
        it->second.remove_if([nodeId](const WeakPtr<NG::FrameNode>& node) {
            return (!node.Upgrade()) || (node.Upgrade()->GetId() == nodeId);
        });
        if (it->second.empty()) {
            inspectorIdSafeMap_.erase(it);
        }
        return;
    }
    auto it = inspectorIdMap_.find(key);
    CHECK_NULL_VOID(it != inspectorIdMap_.end());
    CHECK_NULL_VOID(!it->second.empty());
    it->second.remove_if([nodeId](const WeakPtr<NG::FrameNode>& node) {
        return (!node.Upgrade()) || (node.Upgrade()->GetId() == nodeId);
    });
    if (it->second.empty()) {
        inspectorIdMap_.erase(it);
    }
}
} // namespace OHOS::Ace
