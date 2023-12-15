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

#include "frameworks/core/components/ifelse/if_else_element.h"

#include "frameworks/core/components/ifelse/if_else_component.h"

namespace OHOS::Ace {

bool IfElseElement::CanUpdate(const RefPtr<Component>& newComponent)
{
    auto ifElseComponent = AceType::DynamicCast<IfElseComponent>(newComponent);
    return ifElseComponent ? branchId_ == ifElseComponent->GetBranchId() : false;
}

void IfElseElement::Update()
{
    auto ifElseComponent = AceType::DynamicCast<IfElseComponent>(component_);
    if (!ifElseComponent) {
        LOGW("IfElseElement: component MUST be instance of IfElseComponent");
        return;
    }

    MultiComposedElement::Update();
    branchId_ = ifElseComponent->GetBranchId();
}

void IfElseElement::ComponentToElementLocalizedUpdate(const RefPtr<Component>& component, RefPtr<Element>& element)
{
    RefPtr<IfElseElement> ifElseElement = AceType::DynamicCast<IfElseElement>(element);
    if (!ifElseElement) {
        LOGE("%{public}s is not a IfElseElement. Internal Error!", AceType::TypeName(element));
        return;
    }

    RefPtr<IfElseComponent> ifElseComponent = AceType::DynamicCast<IfElseComponent>(component);
    if (!ifElseComponent) {
        LOGE("%{public}s is not a IfElseComponent. Internal Error!", AceType::TypeName(component));
        return;
    }

    if (ifElseComponent->GetBranchId() == ifElseElement->GetBranchId()) {
        return;
    }

    // even though the IfElement will be deleted, do not put to list of deleted elements
    // because new Element with same elmtId will be created
    ElementRegister::GetInstance()->RemoveItemSilently(ifElseElement->GetElementId());
    ifElseElement->UnregisterChildrenForPartialUpdates();

    auto ifElseParentElement = ifElseElement->GetElementParent().Upgrade();

    ifElseParentElement->UpdateChildWithSlot(
        ifElseElement, ifElseComponent, ifElseElement->GetSlot(), ifElseElement->GetRenderSlot());

    ifElseElement->branchId_ = ifElseComponent->GetBranchId();
}
} // namespace OHOS::Ace
