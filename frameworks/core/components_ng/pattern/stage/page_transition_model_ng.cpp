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

#include "core/components_ng/pattern/stage/page_transition_model_ng.h"

#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<PagePattern> GetCurrentPage()
{
    const auto& pageNode = ViewStackProcessor::GetInstance()->GetPageNode();
    CHECK_NULL_RETURN(pageNode, nullptr);
    return pageNode->GetPattern<PagePattern>();
}
RefPtr<PageTransitionEffect> GetCurrentEffect()
{
    const auto& pageNode = ViewStackProcessor::GetInstance()->GetPageNode();
    CHECK_NULL_RETURN(pageNode, nullptr);
    auto pattern = pageNode->GetPattern<PagePattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetTopTransition();
}
} // namespace

void PageTransitionModelNG::SetSlideEffect(SlideEffect effect)
{
    auto transition = GetCurrentEffect();
    CHECK_NULL_VOID(transition);
    transition->SetSlideEffect(effect);
}

void PageTransitionModelNG::SetTranslateEffect(const NG::TranslateOptions& option)
{
    auto transition = GetCurrentEffect();
    CHECK_NULL_VOID(transition);
    transition->SetTranslateEffect(option);
}

void PageTransitionModelNG::SetScaleEffect(const NG::ScaleOptions& option)
{
    auto transition = GetCurrentEffect();
    CHECK_NULL_VOID(transition);
    transition->SetScaleEffect(option);
}

void PageTransitionModelNG::SetOpacityEffect(float opacity)
{
    auto transition = GetCurrentEffect();
    CHECK_NULL_VOID(transition);
    transition->SetOpacityEffect(opacity);
}

void PageTransitionModelNG::SetOnEnter(PageTransitionEventFunc&& handler)
{
    auto transition = GetCurrentEffect();
    CHECK_NULL_VOID(transition);
    transition->SetUserCallback(std::move(handler));
}

void PageTransitionModelNG::SetOnExit(PageTransitionEventFunc&& handler)
{
    auto transition = GetCurrentEffect();
    CHECK_NULL_VOID(transition);
    transition->SetUserCallback(std::move(handler));
}

void PageTransitionModelNG::CreateTransition(PageTransitionType type, const PageTransitionOption& option)
{
    auto pattern = GetCurrentPage();
    CHECK_NULL_VOID(pattern);
    RefPtr<PageTransitionEffect> transition = AceType::MakeRefPtr<PageTransitionEffect>(type, option);
    pattern->AddPageTransition(transition);
}

void PageTransitionModelNG::Create()
{
    auto pattern = GetCurrentPage();
    CHECK_NULL_VOID(pattern);
    pattern->ClearPageTransitionEffect();
}

void PageTransitionModelNG::Pop()
{}
} // namespace OHOS::Ace::NG
