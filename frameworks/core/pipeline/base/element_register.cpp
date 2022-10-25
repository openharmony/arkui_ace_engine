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

#include "base/log/log.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_v2/common/element_proxy.h"
#include "frameworks/base/memory/ace_type.h"
#include "frameworks/core/pipeline/base/element.h"

namespace OHOS::Ace {
thread_local ElementRegister* ElementRegister::instance_ = nullptr;

ElementRegister* ElementRegister::GetInstance()
{
    if (ElementRegister::instance_ == nullptr) {
        ElementRegister::instance_ = new ElementRegister();
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
    auto position = itemMap_.find(elementId);
    return position == itemMap_.end() ? nullptr : position->second.Upgrade();
}

RefPtr<V2::ElementProxy> ElementRegister::GetElementProxyById(ElementIdType elementId)
{
    auto position = itemMap_.find(elementId);
    return (position == itemMap_.end()) ? nullptr : AceType::DynamicCast<V2::ElementProxy>(position->second).Upgrade();
}

bool ElementRegister::Exists(ElementIdType elementId)
{
    LOGD("ElementRegister::Exists(%{public}d) returns %{public}s", elementId,
        (itemMap_.find(elementId) != itemMap_.end()) ? "true" : "false");
    return (itemMap_.find(elementId) != itemMap_.end());
}

bool ElementRegister::AddReferenced(ElementIdType elmtId, const WeakPtr<AceType>& referenced)
{
    auto result = itemMap_.emplace(elmtId, referenced);
    if (!result.second) {
        LOGE("Duplicate elmtId %{public}d error.", elmtId);
    }
    return result.second;
}

bool ElementRegister::AddElement(const RefPtr<Element>& element)
{
    if ((element == nullptr) || (element->GetElementId() == ElementRegister::UndefinedElementId)) {
        return false;
    }

    LOGD("Add %{public}s with elmtId %{public}d", AceType::TypeName(element), element->GetElementId());
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

    LOGD("Add %{public}s with elmtId %{public}d", AceType::TypeName(elmt), elmt->GetElementId());
    return AddReferenced(elmt->GetElementId(), elementProxy);
}

RefPtr<NG::UINode> ElementRegister::GetUINodeById(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return nullptr;
    }
    auto iter = itemMap_.find(elementId);
    return iter == itemMap_.end() ? nullptr : AceType::DynamicCast<NG::UINode>(iter->second).Upgrade();
}

bool ElementRegister::AddUINode(const RefPtr<NG::UINode>& node)
{
    if (!node || (node->GetId() == ElementRegister::UndefinedElementId)) {
        return false;
    }

    LOGD("Add %{public}s with elmtId %{public}d", AceType::TypeName(node), node->GetId());
    return AddReferenced(node->GetId(), node);
}

bool ElementRegister::RemoveItem(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return false;
    }

    auto removed = itemMap_.erase(elementId);
    if (removed) {
        LOGD("ElmtId %{public}d successfully removed from registry, added to list of removed Elements.", elementId);
        removedItems_.insert(elementId);
        LOGD("Size of removedItems_ removedItems_ %{public}d", static_cast<int32_t>(removedItems_.size()));
    } else {
        LOGD("ElmtId %{public}d not found. Cannot be removed.", elementId);
    }
    return removed;
}

bool ElementRegister::RemoveItemSilently(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return false;
    }

    auto removed = itemMap_.erase(elementId);
    if (removed) {
        LOGD("ElmtId %{public}d successfully removed from registry, NOT added to list of removed Elements.", elementId);
    } else {
        LOGD("ElmtId %{public}d not found. Cannot be removed.", elementId);
    }

    return removed;
}

std::unordered_set<ElementIdType>& ElementRegister::GetRemovedItems()
{
    LOGD("return set of %{public}d elmtIds", static_cast<int32_t>(removedItems_.size()));
    return removedItems_;
}

void ElementRegister::Clear()
{
    LOGD("Empty the ElementRegister");
    itemMap_.clear();
    removedItems_.clear();
}
} // namespace OHOS::Ace
