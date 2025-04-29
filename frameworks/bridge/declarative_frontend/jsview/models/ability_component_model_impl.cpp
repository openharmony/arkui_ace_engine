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

#include "frameworks/bridge/declarative_frontend/jsview/models/ability_component_model_impl.h"

#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void AbilityComponentModelImpl::Create(const std::string& bundleName, const std::string& abilityName)
{
    auto abilityComponent = AceType::MakeRefPtr<OHOS::Ace::V2::AbilityComponent>();
    ViewStackProcessor::GetInstance()->ClaimElementId(abilityComponent);
    ViewStackProcessor::GetInstance()->Push(abilityComponent);
}

RefPtr<OHOS::Ace::V2::AbilityComponent> AbilityComponentModelImpl::GetComponent()
{
    auto* stack = ViewStackProcessor::GetInstance();
    if (!stack) {
        return nullptr;
    }
    auto component = AceType::DynamicCast<OHOS::Ace::V2::AbilityComponent>(stack->GetMainComponent());
    return component;
}

void AbilityComponentModelImpl::SetWant(const std::string& want)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetWant(want);
}

void AbilityComponentModelImpl::SetWidth(Dimension value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetWidth(value);
}

void AbilityComponentModelImpl::SetHeight(Dimension value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    component->SetHeight(value);
}

void AbilityComponentModelImpl::SetOnConnect(std::function<void()>&& onConnect)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetOnConnected(std::move(onConnect));
}

void AbilityComponentModelImpl::SetOnDisConnect(std::function<void()>&& onDisConnect)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetOnDisconnected(std::move(onDisConnect));
}

} // namespace OHOS::Ace::Framework
