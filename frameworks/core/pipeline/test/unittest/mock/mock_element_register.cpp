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
    return nullptr;
}

RefPtr<AceType> ElementRegister::GetNodeById(ElementIdType elementId)
{
    return nullptr;
}

RefPtr<V2::ElementProxy> ElementRegister::GetElementProxyById(ElementIdType elementId)
{
    return nullptr;
}

bool ElementRegister::Exists(ElementIdType elementId)
{
    return false;
}

bool ElementRegister::AddReferenced(ElementIdType elmtId, const WeakPtr<AceType>& referenced)
{
    return false;
}

bool ElementRegister::AddElement(const RefPtr<Element>& element)
{
    return false;
}

bool ElementRegister::AddElementProxy(const WeakPtr<V2::ElementProxy>& elementProxy)
{
    return false;
}

RefPtr<NG::UINode> ElementRegister::GetUINodeById(ElementIdType elementId)
{
    return nullptr;
}

bool ElementRegister::AddUINode(const RefPtr<NG::UINode>& node)
{
    return false;
}

bool ElementRegister::RemoveItem(ElementIdType elementId)
{
    return false;
}

bool ElementRegister::RemoveItemSilently(ElementIdType elementId)
{
    return false;
}

std::unordered_set<ElementIdType>& ElementRegister::GetRemovedItems()
{
    return removedItems_;
}

void ElementRegister::Clear()
{
    itemMap_.clear();
    removedItems_.clear();
}
} // namespace OHOS::Ace
