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

#include "bridge/declarative_frontend/jsview/models/text_timer_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
RefPtr<TextTimerController> TextTimerModelImpl::Create()
{
    auto timerComponent = AceType::MakeRefPtr<TextTimerComponent>();
    CHECK_NULL_RETURN(timerComponent, nullptr);
    ViewStackProcessor::GetInstance()->Push(timerComponent);
    return timerComponent->GetTextTimerController();
}

void TextTimerModelImpl::SetIsCountDown(bool isCountDown)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetIsCountDown(isCountDown);
}

void TextTimerModelImpl::SetInputCount(double count)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetInputCount(count);
}

void TextTimerModelImpl::SetFormat(const std::string& format)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetFormat(format);
}

void TextTimerModelImpl::SetOnTimer(std::function<void(int64_t, int64_t)> && onChange)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetOnTimer(std::move(onChange));
}

void TextTimerModelImpl::SetFontSize(const Dimension& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetFontSize(value);
    component->SetTextStyle(textStyle);
}

void TextTimerModelImpl::SetTextColor(const Color& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetTextColor(value);
    component->SetTextStyle(textStyle);
}

void TextTimerModelImpl::SetItalicFontStyle(Ace::FontStyle value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetFontStyle(value);
    component->SetTextStyle(textStyle);
}

void TextTimerModelImpl::SetFontWeight(FontWeight value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetFontWeight(value);
    component->SetTextStyle(textStyle);
}

void TextTimerModelImpl::SetFontFamily(const std::vector<std::string>& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);

    auto textStyle = component->GetTextStyle();
    textStyle.SetFontFamilies(value);
    component->SetTextStyle(textStyle);
}

RefPtr<TextTimerComponent> TextTimerModelImpl::GetComponent()
{
    auto* stack = ViewStackProcessor::GetInstance();
    if (!stack) {
        return nullptr;
    }
    auto component = AceType::DynamicCast<TextTimerComponent>(stack->GetMainComponent());
    return component;
}
} // namespace OHOS::Ace::Framework