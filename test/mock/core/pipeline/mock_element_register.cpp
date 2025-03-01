/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/pipeline/base/element.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace {
thread_local ElementRegister* ElementRegister::instance_ = nullptr;
std::mutex ElementRegister::mutex_;

ElementRegister* ElementRegister::GetInstance()
{
    if (ElementRegister::instance_ == nullptr) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!ElementRegister::instance_) {
            ElementRegister::instance_ = new ElementRegister();
        }
    }
    return (ElementRegister::instance_);
}

RefPtr<Element> ElementRegister::GetElementById(ElementIdType elementId)
{
    return nullptr;
}

RefPtr<AceType> ElementRegister::GetNodeById(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return nullptr;
    }
    auto position = itemMap_.find(elementId);
    return position == itemMap_.end() ? nullptr : position->second.Upgrade();
}

RefPtr<V2::ElementProxy> ElementRegister::GetElementProxyById(ElementIdType /* elementId */)
{
    return nullptr;
}

bool ElementRegister::Exists(ElementIdType elementId)
{
    return (itemMap_.find(elementId) != itemMap_.end());
}

void ElementRegister::UpdateRecycleElmtId(int32_t oldElmtId, int32_t newElmtId)
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

bool ElementRegister::AddReferenced(ElementIdType elmtId, const WeakPtr<AceType>& referenced)
{
    auto result = itemMap_.emplace(elmtId, referenced);
    return result.second;
}

bool ElementRegister::AddElement(const RefPtr<Element>& element)
{
    if ((element == nullptr) || (element->GetElementId() == ElementRegister::UndefinedElementId)) {
        return false;
    }
    return AddReferenced(element->GetElementId(), element);
}

bool ElementRegister::AddElementProxy(const WeakPtr<V2::ElementProxy>& /* elementProxy */)
{
    return false;
}

RefPtr<NG::UINode> ElementRegister::GetUINodeById(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return nullptr;
    }
    auto iter = itemMap_.find(elementId);
    return iter == itemMap_.end() ? nullptr : AceType::DynamicCast<NG::UINode>(iter->second).Upgrade();
}

NG::FrameNode* ElementRegister::GetFrameNodePtrById(ElementIdType elementId)
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

bool ElementRegister::AddUINode(const RefPtr<NG::UINode>& node)
{
    if (!node || (node->GetId() == ElementRegister::UndefinedElementId)) {
        return false;
    }
    return AddReferenced(node->GetId(), node);
}

bool ElementRegister::RemoveItem(ElementIdType elementId)
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

bool ElementRegister::RemoveItemSilently(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return false;
    }
    return itemMap_.erase(elementId);
}

void ElementRegister::MoveRemovedItems(RemovedElementsType& removedItems)
{
    removedItems = removedItems_;
    removedItems_ = std::unordered_set<ElementIdType>();
}

void ElementRegister::Clear()
{
    itemMap_.clear();
    removedItems_.clear();
    geometryTransitionMap_.clear();
    pendingRemoveNodes_.clear();
}

RefPtr<NG::GeometryTransition> ElementRegister::GetOrCreateGeometryTransition(
    const std::string& id, bool followWithoutTransition, bool doRegisterSharedTransition)
{
    if (id.empty()) {
        return nullptr;
    }
    RefPtr<NG::GeometryTransition> geometryTransition;
    if (geometryTransitionMap_.find(id) == geometryTransitionMap_.end()) {
        geometryTransition = AceType::MakeRefPtr<NG::GeometryTransition>(
            id, followWithoutTransition, doRegisterSharedTransition);
        geometryTransitionMap_.emplace(id, geometryTransition);
    } else {
        geometryTransition = geometryTransitionMap_[id];
    }
    return geometryTransition;
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
    for (const auto& [itemId, item] : geometryTransitionMap_) {
        if (item) {
            item->OnReSync(trigger, option);
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
    CHECK_NULL_RETURN(it != inspectorIdMap_.end(), nullptr);
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
    auto it = inspectorIdMap_.find(key);
    if (it != inspectorIdMap_.end()) {
        it->second.push_back(node);
    } else {
        std::list<WeakPtr<NG::FrameNode>> nodeList = { node };
        inspectorIdMap_.try_emplace(key, nodeList);
    }
}

void ElementRegister::RemoveFrameNodeByInspectorId(const std::string& key, int32_t nodeId)
{
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
