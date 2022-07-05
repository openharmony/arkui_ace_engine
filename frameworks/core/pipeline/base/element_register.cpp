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

RefPtr<Element> ElementRegister::GetElementById(ElementIdType elmtId)
{
    if (elmtId == ElementRegister::UndefinedElementId) {
        return nullptr;
    }
    auto position = ElementRegister::GetInstance()->elementMap_.find(elmtId);
    return position == elementMap_.end() ? nullptr : AceType::DynamicCast<Element>(position->second).Upgrade();
}

RefPtr<V2::ElementProxy> ElementRegister::GetElementProxyById(ElementIdType elmtId)
{
    auto position = ElementRegister::GetInstance()->elementMap_.find(elmtId);
    return (position == elementMap_.end()) ?
        nullptr :
        AceType::DynamicCast<V2::ElementProxy>(position->second).Upgrade();
}

bool ElementRegister::Exists(ElementIdType elementId)
{
    LOGD("ElementRegister::Exists(%{public}d) returns %{public}s", elementId,
        (elementMap_.find(elementId) != elementMap_.end()) ? "true" : "false");
    return (elementMap_.find(elementId) != elementMap_.end());
}

bool ElementRegister::AddReferenced(ElementIdType elmtId, const WeakPtr<AceType>& referenced)
{
    auto result = elementMap_.emplace(elmtId, referenced);
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

bool ElementRegister::RemoveElement(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return false;
    }

    auto removed = elementMap_.erase(elementId);
    if (removed) {
        LOGD("ElmtId %{public}d successfully removed from registry, added to list of removed Elements.", elementId);
    } else {
        LOGD("ElmtId %{public}d not found. Cannot be removed.", elementId);
    }
    removedElements_.insert(elementId);
    LOGD("Size of removedElements_ removedElements_ %{public}d",
        static_cast<int32_t>(ElementRegister::GetInstance()->removedElements_.size()));
    return removed;
}

bool ElementRegister::RemoveElementSilently(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return false;
    }

    auto removed = ElementRegister::GetInstance()->elementMap_.erase(elementId);
    if (removed) {
        LOGD("ElmtId %{public}d successfully removed from registry, NOT added to list of removed Elements.", elementId);
    } else {
        LOGD("ElmtId %{public}d not found. Cannot be removed.", elementId);
    }

    return removed;
}

std::unordered_set<ElementIdType>& ElementRegister::GetRemovedElements()
{
    LOGD("return set of %{public}d elmtIds",
        static_cast<int32_t>(ElementRegister::GetInstance()->removedElements_.size()));
    return ElementRegister::GetInstance()->removedElements_;
}

void ElementRegister::Clear()
{
    LOGD("Empty the ElementRegister");
    ElementRegister::GetInstance()->elementMap_.clear();
    ElementRegister::GetInstance()->removedElements_.clear();
}
} // namespace OHOS::Ace
