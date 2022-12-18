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

#include "bridge/declarative_frontend/jsview/models/marquee_model_impl.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void MarqueeModelImpl::Create()
{
    auto marqueeComponent = AceType::MakeRefPtr<MarqueeComponent>();
    CHECK_NULL_VOID(marqueeComponent);
    ViewStackProcessor::GetInstance()->ClaimElementId(marqueeComponent);
    ViewStackProcessor::GetInstance()->Push(marqueeComponent);
}

void MarqueeModelImpl::SetValue(const std::string& value)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetValue(value);
}

void MarqueeModelImpl::SetPlayerStatus(bool playerStatus)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetPlayerStatus(playerStatus);
}

void MarqueeModelImpl::SetScrollAmount(double scrollAmount)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetScrollAmount(scrollAmount);
}

void MarqueeModelImpl::SetLoop(int32_t loop)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetLoop(loop);
}

void MarqueeModelImpl::SetDirection(MarqueeDirection direction)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetDirection(direction);
}

void MarqueeModelImpl::SetTextColor(const Color& textColor)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    textStyle.SetTextColor(textColor);
    component->SetTextStyle(textStyle);
}

void MarqueeModelImpl::SetFontSize(const Dimension& fontSize)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    textStyle.SetFontSize(fontSize);
    component->SetTextStyle(textStyle);
}

void MarqueeModelImpl::SetFontWeight(const FontWeight& fontWeight)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    textStyle.SetFontWeight(fontWeight);
    component->SetTextStyle(textStyle);
}

void MarqueeModelImpl::SetFontFamily(const std::vector<std::string>& fontFamilies)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    textStyle.SetFontFamilies(fontFamilies);
    component->SetTextStyle(textStyle);
}

void MarqueeModelImpl::SetAllowScale(bool allowScale)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    textStyle.SetAllowScale(allowScale);
    component->SetTextStyle(textStyle);
}

void MarqueeModelImpl::SetOnStart(std::function<void()>&& onChange)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetOnStart(move(onChange));
}

void MarqueeModelImpl::SetOnBounce(std::function<void()>&& onChange)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetOnBounce(move(onChange));
}

void MarqueeModelImpl::SetOnFinish(std::function<void()>&& onChange)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetOnFinish(move(onChange));
}

RefPtr<MarqueeComponent> MarqueeModelImpl::GetComponent()
{
    auto* stack = ViewStackProcessor::GetInstance();
    if (!stack) {
        return nullptr;
    }
    auto component = AceType::DynamicCast<MarqueeComponent>(stack->GetMainComponent());
    return component;
}
} // namespace OHOS::Ace::Framework
