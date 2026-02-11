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

#include "bridge/declarative_frontend/jsview/models/counter_model_impl.h"

#include "core/components/counter/counter_component.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

namespace {

constexpr Dimension COUNTER_DEFAULT_HEIGHT = 32.0_vp;
constexpr Dimension COUNTER_DEFAULT_WIDTH = 100.0_vp;
constexpr Dimension COUNTER_DEFAULT_CONTROL_WIDTH = 32.0_vp;
constexpr Dimension COUNTER_DEFAULT_RADIUS = 4.0_vp;

} // namespace

void CounterModelImpl::Create()
{
    std::list<RefPtr<Component>> children;
    RefPtr<OHOS::Ace::CounterComponent> component = AceType::MakeRefPtr<CounterComponent>(children);
    ViewStackProcessor::GetInstance()->ClaimElementId(component);
    ViewStackProcessor::GetInstance()->Push(component);

    component->SetHeight(COUNTER_DEFAULT_HEIGHT);
    component->SetWidth(COUNTER_DEFAULT_WIDTH);
    component->SetControlWidth(COUNTER_DEFAULT_CONTROL_WIDTH);
    component->SetControlRadius(COUNTER_DEFAULT_RADIUS);
}
void CounterModelImpl::SetOnInc(CounterEventFunc&& onInc)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto counterComponent = AceType::DynamicCast<CounterComponent>(component);
    counterComponent->SetOnInc(std::move(onInc));
}
void CounterModelImpl::SetOnDec(CounterEventFunc&& onDec)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto counterComponent = AceType::DynamicCast<CounterComponent>(component);
    counterComponent->SetOnDec(std::move(onDec));
}
void CounterModelImpl::SetHeight(const Dimension& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto counterComponent = AceType::DynamicCast<CounterComponent>(component);
    counterComponent->SetHeight(value);
}
void CounterModelImpl::SetWidth(const Dimension& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto counterComponent = AceType::DynamicCast<CounterComponent>(component);
    counterComponent->SetWidth(value);
}
void CounterModelImpl::SetControlWidth(const Dimension& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto counterComponent = AceType::DynamicCast<CounterComponent>(component);
    counterComponent->SetControlWidth(value);
}
void CounterModelImpl::SetStateChange(bool value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto counterComponent = AceType::DynamicCast<CounterComponent>(component);
    counterComponent->SetState(value);
}
void CounterModelImpl::SetBackgroundColor(const Color& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto counterComponent = AceType::DynamicCast<CounterComponent>(component);
    counterComponent->SetBackgroundColor(value);
}
void CounterModelImpl::SetEnableDec(bool enableDec) {};
void CounterModelImpl::SetEnableInc(bool enableInc) {};
} // namespace OHOS::Ace::Framework
