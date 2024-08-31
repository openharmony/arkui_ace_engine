/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/swiper/swiper_component.h"

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

void SwiperModelImpl::SetOnChange(std::function<void(const BaseEventInfo* info)>&& onChange)
{
    auto onChangeEvent = EventMarker(std::move(onChange));
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetChangeEventId(onChangeEvent);
    }
}

void SwiperModelImpl::SetOnAnimationStart(std::function<void(const BaseEventInfo* info)>&& onAnimationStart)
{
    auto onAnimationStartEvent = EventMarker(std::move(onAnimationStart));
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetAnimationStartEventId(onAnimationStartEvent);
    }
}

void SwiperModelImpl::SetOnAnimationEnd(std::function<void(const BaseEventInfo* info)>&& onAnimationEnd)
{
    auto onAnimationEndEvent = EventMarker(std::move(onAnimationEnd));
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        swiper->SetAnimationEndEventId(onAnimationEndEvent);
    }
}

void SwiperModelImpl::SetRemoteMessageEventId(RemoteCallback&& remoteCallback)
{
    EventMarker remoteMessageEventId(std::move(remoteCallback));
    auto* stack = ViewStackProcessor::GetInstance();
    auto swiperComponent = AceType::DynamicCast<SwiperComponent>(stack->GetMainComponent());
    if (!swiperComponent) {
        LOGE("swiperComponent is null");
        return;
    }
    swiperComponent->SetRemoteMessageEventId(remoteMessageEventId);
}

void SwiperModelImpl::SetIndicatorStyle(const SwiperParameters& swiperParameters)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        auto indicator = swiper->GetIndicator();
        if (!indicator) {
            return;
        }

        if (swiperParameters.dimLeft.has_value()) {
            indicator->SetLeft(swiperParameters.dimLeft.value());
        }
        if (swiperParameters.dimTop.has_value()) {
            indicator->SetTop(swiperParameters.dimTop.value());
        }
        if (swiperParameters.dimRight.has_value()) {
            indicator->SetRight(swiperParameters.dimRight.value());
        }
        if (swiperParameters.dimBottom.has_value()) {
            indicator->SetBottom(swiperParameters.dimBottom.value());
        }
        if (swiperParameters.itemWidth.has_value()) {
            indicator->SetSize(swiperParameters.itemWidth.value());
        }
        if (swiperParameters.itemHeight.has_value()) {
            indicator->SetSize(swiperParameters.itemHeight.value());
        }
        if (swiperParameters.maskValue.has_value()) {
            indicator->SetIndicatorMask(swiperParameters.maskValue.value());
        }
        if (swiperParameters.colorVal.has_value()) {
            indicator->SetColor(swiperParameters.colorVal.value());
        }
        if (swiperParameters.selectedColorVal.has_value()) {
            indicator->SetSelectedColor(swiperParameters.selectedColorVal.value());
        }
    }
}

void SwiperModelImpl::SetOnClick(
    std::function<void(const BaseEventInfo* info, const RefPtr<V2::InspectorFunctionImpl>& impl)>&& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
    if (!inspector) {
        LOGE("fail to get inspector for on get click event marker");
        if (swiper) {
            swiper->SetClickEventId(EventMarker());
        }
        return;
    }
    auto impl = inspector->GetInspectorFunctionImpl();
    auto onClick = [func = std::move(value), impl](const BaseEventInfo* info) {
        {
            func(info, impl);
        }
    };
    if (swiper) {
        swiper->SetClickEventId(EventMarker(onClick));
    }
}

void SwiperModelImpl::SetMainSwiperSizeWidth()
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        if (swiper->GetMainSwiperSize() == MainSwiperSize::MAX ||
            swiper->GetMainSwiperSize() == MainSwiperSize::MAX_Y) {
            swiper->SetMainSwiperSize(MainSwiperSize::MAX);
        } else {
            swiper->SetMainSwiperSize(MainSwiperSize::MAX_X);
        }
    }
}

void SwiperModelImpl::SetMainSwiperSizeHeight()
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto swiper = AceType::DynamicCast<OHOS::Ace::SwiperComponent>(component);
    if (swiper) {
        if (swiper->GetMainSwiperSize() == MainSwiperSize::MAX ||
            swiper->GetMainSwiperSize() == MainSwiperSize::MAX_X) {
            swiper->SetMainSwiperSize(MainSwiperSize::MAX);
        } else {
            swiper->SetMainSwiperSize(MainSwiperSize::MAX_Y);
        }
    }
}

} // namespace OHOS::Ace::Framework
