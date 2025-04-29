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

#include <optional>

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/text/text_theme.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr Dimension DEFAULT_STEP = 6.0_vp;
}
void MarqueeModelImpl::Create()
{
    auto marqueeComponent = AceType::MakeRefPtr<MarqueeComponent>();
    CHECK_NULL_VOID(marqueeComponent);
    ViewStackProcessor::GetInstance()->ClaimElementId(marqueeComponent);
    ViewStackProcessor::GetInstance()->Push(marqueeComponent);
}

void MarqueeModelImpl::SetValue(const std::optional<std::string>& srcValue)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetValue(srcValue.value_or(""));
}

void MarqueeModelImpl::SetPlayerStatus(const std::optional<bool>& playerStatus)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetPlayerStatus(playerStatus.value_or(false));
}

void MarqueeModelImpl::SetScrollAmount(const std::optional<double>& scrollAmount)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetScrollAmount(scrollAmount.value_or(DEFAULT_STEP.ConvertToPx()));
}

void MarqueeModelImpl::SetLoop(const std::optional<int32_t>& loop)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetLoop(loop.value_or(-1));
}

void MarqueeModelImpl::SetDirection(const std::optional<MarqueeDirection>& direction)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    component->SetDirection(direction.value_or(MarqueeDirection::LEFT));
}

void MarqueeModelImpl::SetTextColor(const std::optional<Color>& textColor)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    textStyle.SetTextColor(textColor.value_or(theme->GetTextStyle().GetTextColor()));
    component->SetTextStyle(textStyle);
}

void MarqueeModelImpl::SetFontSize(const std::optional<Dimension>& fontSize)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    textStyle.SetFontSize(fontSize.value_or(theme->GetTextStyle().GetFontSize()));
    component->SetTextStyle(textStyle);
}

void MarqueeModelImpl::SetFontWeight(const std::optional<FontWeight>& fontWeight)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    textStyle.SetFontWeight(fontWeight.value_or(FontWeight::NORMAL));
    component->SetTextStyle(textStyle);
}

void MarqueeModelImpl::SetFontFamily(const std::optional<std::vector<std::string>>& fontFamilies)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    if (fontFamilies.has_value()) {
        textStyle.SetFontFamilies(fontFamilies.value());
    }
    component->SetTextStyle(textStyle);
}

void MarqueeModelImpl::SetAllowScale(const std::optional<bool>& allowScale)
{
    auto component = GetComponent();
    CHECK_NULL_VOID(component);
    auto textStyle = component->GetTextStyle();
    textStyle.SetAllowScale(allowScale.value_or(false));
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
