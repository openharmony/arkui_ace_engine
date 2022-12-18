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

#include "bridge/declarative_frontend/jsview/models/text_clock_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
RefPtr<TextClockController> TextClockModelImpl::Create()
{
    auto clockComponent = AceType::MakeRefPtr<TextClockComponent>(std::string(""));
    CHECK_NULL_RETURN(clockComponent, nullptr);
    clockComponent->SetTextClockController(AceType::MakeRefPtr<TextClockController>());
    ViewStackProcessor::GetInstance()->Push(clockComponent);
    return clockComponent->GetTextClockController();
}

void TextClockModelImpl::SetFormat(const std::string& format)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetFormat(format);
}

void TextClockModelImpl::SetHoursWest(const int32_t& hoursWest)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetHoursWest(hoursWest);
}

void TextClockModelImpl::SetOnDateChange(std::function<void(const std::string)>&& onChange)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetOnDateChange(std::move(onChange));
}

RefPtr<TextClockComponent> TextClockModelImpl::GetComponent()
{
    auto* stack = ViewStackProcessor::GetInstance();
    if (!stack) {
        return nullptr;
    }
    auto component = AceType::DynamicCast<TextClockComponent>(stack->GetMainComponent());
    return component;
}
} // namespace OHOS::Ace::Framework