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

#include "bridge/declarative_frontend/jsview/models/swiper_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/swiper/swiper_component.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"

namespace OHOS::Ace::Framework {

RefPtr<SwiperController> SwiperModelImpl::Create()
{
    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;
    RefPtr<OHOS::Ace::SwiperComponent> component = AceType::MakeRefPtr<OHOS::Ace::SwiperComponent>(componentChildren);

    auto indicator = AceType::MakeRefPtr<OHOS::Ace::SwiperIndicator>();
    auto indicatorTheme = JSViewAbstract::GetTheme<SwiperIndicatorTheme>();
    if (indicatorTheme) {
        indicator->InitStyle(indicatorTheme);
    }

    constexpr int32_t DEFAULT_SWIPER_CACHED_COUNT = 1;
    component->SetIndicator(indicator);
    component->SetMainSwiperSize(MainSwiperSize::MIN);
    component->SetCachedSize(DEFAULT_SWIPER_CACHED_COUNT);
    component->SetCurve(Curves::LINEAR);
    ViewStackProcessor::GetInstance()->ClaimElementId(component);
    ViewStackProcessor::GetInstance()->Push(component);
    JSInteractableView::SetFocusNode(true);

    return component->GetSwiperController();
}

void SwiperModelImpl::SetDirection(Axis axis)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetAxis(axis);
    }
}

void SwiperModelImpl::SetIndex(uint32_t index)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetIndex(index);
    }
}

void SwiperModelImpl::SetDisplayMode(SwiperDisplayMode displayMode)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (!swiper) {
        return;
    }

    swiper->SetDisplayMode(displayMode);
}

void SwiperModelImpl::SetDisplayCount(int32_t displayCount)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (!swiper) {
        return;
    }
    swiper->SetDisplayCount(displayCount);
}

void SwiperModelImpl::SetShowIndicator(bool showIndicator)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetShowIndicator(showIndicator);
        if (!showIndicator) {
            swiper->SetIndicator(nullptr);
        }
    }
}

void SwiperModelImpl::SetItemSpace(const Dimension& itemSpace)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetItemSpace(itemSpace);
    }
}

void SwiperModelImpl::SetCachedCount(int32_t cachedCount)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetCachedSize(cachedCount);
    }
}

void SwiperModelImpl::SetAutoPlay(bool autoPlay)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetAutoPlay(autoPlay);
    }
}

void SwiperModelImpl::SetAutoPlayInterval(uint32_t interval)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetAutoPlayInterval(interval);
    }
}

void SwiperModelImpl::SetDuration(uint32_t duration)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetDuration(duration);
    }
}

void SwiperModelImpl::SetLoop(bool loop)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetLoop(loop);
    }
}

void SwiperModelImpl::SetEnabled(bool enabled)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetDisabledStatus(!enabled);
    }
}

void SwiperModelImpl::SetDisableSwipe(bool disableSwipe)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->DisableSwipe(disableSwipe);
    }
}

void SwiperModelImpl::SetEdgeEffect(EdgeEffect edgeEffect)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (!swiper) {
        return;
    }

    if (edgeEffect == EdgeEffect::SPRING) {
        swiper->SetEdgeEffect(EdgeEffect::SPRING);
    } else if (edgeEffect == EdgeEffect::FADE) {
        swiper->SetEdgeEffect(EdgeEffect::FADE);
    } else {
        swiper->SetEdgeEffect(EdgeEffect::NONE);
    }
}

void SwiperModelImpl::SetCurve(const RefPtr<Curve>& curve)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    swiper->SetCurve(curve);
}

void SwiperModelImpl::SetOnChange(NG::ChangeEvent&& onChange)
{
    auto onChangeEvent = EventMarker(std::move(onChange));
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetChangeEventId(onChangeEvent);
    }
}

} // namespace OHOS::Ace::Framework
