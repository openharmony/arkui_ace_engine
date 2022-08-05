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

#include "frameworks/bridge/declarative_frontend/jsview/js_if_else.h"

#include "base/log/ace_trace.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/ifelse/if_else_component.h"
#include "core/components/ifelse/if_else_element.h"
#include "core/components_v2/common/element_proxy.h"

namespace OHOS::Ace::Framework {

void JSIfElse::Create(const JSCallbackInfo& info)
{
    auto component = AceType::MakeRefPtr<IfElseComponent>(std::string(), "IfElse");
    ViewStackProcessor::GetInstance()->ClaimElementId(component);
    ViewStackProcessor::GetInstance()->Push(component);
}

void JSIfElse::Pop()
{
    ViewStackProcessor::GetInstance()->PopContainer();
}

void JSIfElse::SetBranchId(int32_t value)
{
    if (value < 0) {
        LOGE("IfElse: branchId(%{public}d) expected positive number", value);
        return;
    }

    auto component = AceType::DynamicCast<IfElseComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    component->SetBranchId(value);
}

void JSIfElse::JSBind(BindingTarget globalObj)
{
    JSClass<JSIfElse>::Declare("If");
    JSClass<JSIfElse>::StaticMethod("create", &JSIfElse::Create);
    JSClass<JSIfElse>::StaticMethod("pop", &JSIfElse::Pop);
    JSClass<JSIfElse>::StaticMethod("branchId", &JSIfElse::SetBranchId);
    JSClass<JSIfElse>::Bind<>(globalObj);
}

void JSIfElse::ComponentToElementLocalizedUpdate(
    const RefPtr<Component>& component, RefPtr<Element>& element)
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

    if (ifElseComponent->BranchId() == ifElseElement->BranchId()) {
        LOGD("Unchanged branchId. No updates to be done.");
        return;
    }

    // even though the IfElement will be deleted, do not put to list of deleted elements
    // because new Element with same elmtId will be created
    ElementRegister::GetInstance()->RemoveItemSilently(ifElseElement->GetElementId());
    ifElseElement->UnregisterChildrenForPartialUpdates();

    auto ifElseParentElement = ifElseElement->GetElementParent().Upgrade();
    LOGD("Doing a deep update IfElseElement <- %{public}s ...", AceType::TypeName(ifElseComponent));
    LOGD("IfElse element slot: %{public}d, renderSlot: %{public}d",
        ifElseElement->GetSlot(), ifElseElement->GetRenderSlot());
    LOGD("   IfElseElement parent Element is %{public}s", AceType::TypeName(ifElseParentElement));

    ifElseParentElement->UpdateChildWithSlot(
        ifElseElement, ifElseComponent, ifElseElement->GetSlot(), ifElseElement->GetRenderSlot());

    LOGD("Doing a deep update on IfElseElement - DONE");
}

} // namespace OHOS::Ace::Framework
