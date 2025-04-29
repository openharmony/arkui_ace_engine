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

#include "frameworks/bridge/declarative_frontend/jsview/models/page_transition_model_impl.h"

#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void PageTransitionModelImpl::SetSlideEffect(SlideEffect effect)
{
    const auto& pageTransition = GetPageTransition();
    if (pageTransition) {
        pageTransition->SetEffect(effect);
    }
}

void PageTransitionModelImpl::SetTranslateEffect(const NG::TranslateOptions &option)
{
    const auto& pageTransition = GetPageTransition();
    if (pageTransition) {
        pageTransition->AddTranslateAnimation(option.x, option.y, option.z);
    }
}

void PageTransitionModelImpl::SetScaleEffect(const NG::ScaleOptions &option)
{
    const auto& pageTransition = GetPageTransition();
    if (pageTransition) {
        pageTransition->AddScaleAnimation(option.xScale, option.yScale, option.zScale, option.centerX, option.centerY);
    }
}

void PageTransitionModelImpl::SetOpacityEffect(float opacity)
{
    const auto& pageTransition = GetPageTransition();
    if (pageTransition) {
        pageTransition->AddOpacityAnimation(opacity);
    }
}

void PageTransitionModelImpl::SetOnEnter(PageTransitionEventFunc&& handler)
{
    const auto& pageTransition = GetPageTransition();
    if (pageTransition) {
        pageTransition->SetOnEnterHandler(std::move(handler));
    }
}

void PageTransitionModelImpl::SetOnExit(PageTransitionEventFunc&& handler)
{
    const auto& pageTransition = GetPageTransition();
    if (pageTransition) {
        pageTransition->SetOnExitHandler(std::move(handler));
    }
}

void PageTransitionModelImpl::Create()
{
    // create PageTransitionComponent
    auto pageTransitionComponent = ViewStackProcessor::GetInstance()->GetPageTransitionComponent();
    if (pageTransitionComponent) {
        pageTransitionComponent->ClearPageTransition();
    }
}

void PageTransitionModelImpl::Pop()
{
    auto pageTransitionComponent = ViewStackProcessor::GetInstance()->GetPageTransitionComponent();
    if (pageTransitionComponent) {
        pageTransitionComponent->ClearPageTransitionStack();
    }
}

RefPtr<PageTransition> PageTransitionModelImpl::GetPageTransition()
{
    auto pageTransitionComponent = ViewStackProcessor::GetInstance()->GetPageTransitionComponent();
    if (pageTransitionComponent) {
        return pageTransitionComponent->GetTopPageTransition();
    }
    return nullptr;
}

void PageTransitionModelImpl::CreateTransition(PageTransitionType type, const PageTransitionOption& option)
{
    RefPtr<PageTransition> pageTransitionInfo = AceType::MakeRefPtr<PageTransition>(type);
    pageTransitionInfo->SetDuration(option.duration);
    pageTransitionInfo->SetDelay(option.delay);
    pageTransitionInfo->SetCurve(option.curve);
    pageTransitionInfo->SetRouteType(option.routeType);

    auto pageTransitionComponent = ViewStackProcessor::GetInstance()->GetPageTransitionComponent();
    if (pageTransitionComponent) {
        pageTransitionComponent->PushPageTransition(pageTransitionInfo);
    }
}
} // namespace OHOS::Ace::Framework