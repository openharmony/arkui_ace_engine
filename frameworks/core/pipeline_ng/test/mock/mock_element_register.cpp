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

#include "core/components_ng/base/ui_node.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace {
thread_local ElementRegister* ElementRegister::instance_ = nullptr;

ElementRegister* ElementRegister::GetInstance()
{
    if (ElementRegister::instance_ == nullptr) {
        ElementRegister::instance_ = new ElementRegister();
    }
    return (ElementRegister::instance_);
}

RefPtr<Element> ElementRegister::GetElementById(ElementIdType /*elementId*/)
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

RefPtr<NG::UINode> ElementRegister::GetUINodeById(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return nullptr;
    }
    auto iter = itemMap_.find(elementId);
    return iter == itemMap_.end() ? nullptr : AceType::DynamicCast<NG::UINode>(iter->second).Upgrade();
}

RefPtr<V2::ElementProxy> ElementRegister::GetElementProxyById(ElementIdType /*elementId*/)
{
    return nullptr;
}

bool ElementRegister::Exists(ElementIdType /*elementId*/)
{
    return false;
}

bool ElementRegister::AddReferenced(ElementIdType elementId, const WeakPtr<AceType>& referenced)
{
    auto result = itemMap_.emplace(elementId, referenced);
    return result.second;
}

bool ElementRegister::AddElement(const RefPtr<Element>& /*element*/)
{
    return false;
}

bool ElementRegister::AddElementProxy(const WeakPtr<V2::ElementProxy>& /*elementProxy*/)
{
    return false;
}

bool ElementRegister::AddUINode(const RefPtr<NG::UINode>& node)
{
    if (!node || (node->GetId() == ElementRegister::UndefinedElementId)) {
        return false;
    }
    return AddReferenced(node->GetId(), node);
}

bool ElementRegister::RemoveItem(ElementIdType /*elementId*/)
{
    return true;
}

bool ElementRegister::RemoveItemSilently(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return false;
    }
    return itemMap_.erase(elementId);
}

std::unordered_set<ElementIdType>& ElementRegister::GetRemovedItems()
{
    return removedItems_;
}

void ElementRegister::ClearRemovedItems(ElementIdType elementId) {}

void ElementRegister::Clear()
{
    itemMap_.clear();
    removedItems_.clear();
}

void ElementRegister::AddPendingRemoveNode(const RefPtr<NG::UINode>& node) {}

void ElementRegister::ClearPendingRemoveNodes() {}

void ElementRegister::ReSyncGeometryTransition(const WeakPtr<NG::FrameNode>& trigger, const AnimationOption& option) {}

RefPtr<NG::GeometryTransition> ElementRegister::GetOrCreateGeometryTransition(
    const std::string& id, const WeakPtr<NG::FrameNode>& frameNode, bool followWithoutTransition)
{
    return nullptr;
}

void ElementRegister::DumpGeometryTransition() {}

} // namespace OHOS::Ace
