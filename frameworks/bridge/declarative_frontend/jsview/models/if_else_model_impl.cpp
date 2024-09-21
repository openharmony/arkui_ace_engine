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

#include "frameworks/bridge/declarative_frontend/jsview/models/if_else_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/ifelse/if_else_component.h"
#include "core/components/ifelse/if_else_element.h"

namespace OHOS::Ace::Framework {

void IfElseModelImpl::Create()
{
    auto component = AceType::MakeRefPtr<IfElseComponent>(std::string(), "IfElse");
    ViewStackProcessor::GetInstance()->ClaimElementId(component);
    ViewStackProcessor::GetInstance()->Push(component);
}

void IfElseModelImpl::Pop()
{
    ViewStackProcessor::GetInstance()->PopContainer();
}

void IfElseModelImpl::SetBranchId(int32_t value, std::list<int32_t>& removedElmtId)
{
    auto component = AceType::DynamicCast<IfElseComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    component->SetBranchId(value);
}

int32_t IfElseModelImpl::GetBranchId()
{
    auto component = AceType::DynamicCast<IfElseComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());

    auto forEachElement = (component != nullptr) ? ElementRegister::GetInstance()->GetSpecificItemById<IfElseElement>(
                                                       component->GetElementId())
                                                 : nullptr;

    return (forEachElement != nullptr) ? forEachElement->GetBranchId() : -1;
}

} // namespace OHOS::Ace::Framework
