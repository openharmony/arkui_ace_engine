/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License SwiperComponent::Is distributed on an "AS SwiperComponent::Is" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components/swiper/swiper_component.h"

#include "core/components/swiper/render_swiper.h"

namespace OHOS::Ace {

SwiperComponent::SwiperComponent(const std::list<RefPtr<Component>>& children) : ComponentGroup(children)
{
    if (!declaration_) {
        declaration_ = AceType::MakeRefPtr<SwiperDeclaration>();
        declaration_->Init();
    }
}

SwiperComponent::SwiperComponent(const std::list<RefPtr<Component>>& children, bool showIndicator)
    : SwiperComponent(children)
{
    SetShowIndicator(showIndicator);
}

void SwiperComponent::AppendChild(const RefPtr<Component>& child)
{
    if (AceType::InstanceOf<V2::LazyForEachComponent>(child)) {
        auto lazyForEach = AceType::DynamicCast<V2::LazyForEachComponent>(child);
        lazyForEachComponent_ = lazyForEach;
        return;
    }
    ComponentGroup::AppendChild(child);
}

RefPtr<RenderNode> SwiperComponent::CreateRenderNode()
{
    return RenderSwiper::Create();
}

uint32_t SwiperComponent::GetIndex() const
{
    return declaration_->GetIndex();
}

void SwiperComponent::SetIndex(uint32_t index)
{
    declaration_->SetIndex(index);
}

Axis SwiperComponent::GetAxis() const
{
    return declaration_->GetAxis();
}
void SwiperComponent::SetAxis(Axis axis)
{
    declaration_->SetAxis(axis);
}

bool SwiperComponent::IsLoop() const
{
    return declaration_->IsLoop();
}

void SwiperComponent::SetLoop(bool loop)
{
    declaration_->SetLoop(loop);
}

bool SwiperComponent::IsAutoPlay() const
{
    return declaration_->IsAutoPlay();
}
void SwiperComponent::SetAutoPlay(bool autoPlay)
{
    declaration_->SetAutoPlay(autoPlay);
}

bool SwiperComponent::IsShow() const
{
    return show_;
}
void SwiperComponent::SetShow(bool show)
{
    show_ = show;
}

double SwiperComponent::GetAutoPlayInterval() const
{
    return declaration_->GetAutoPlayInterval();
}
void SwiperComponent::SetAutoPlayInterval(double autoPlayInterval)
{
    declaration_->SetAutoPlayInterval(autoPlayInterval);
}

void SwiperComponent::SetChangeEventId(const EventMarker& changeEventId)
{
    declaration_->SetChangeEventId(changeEventId);
}
const EventMarker& SwiperComponent::GetChangeEventId() const
{
    return declaration_->GetChangeEventId();
}

const EventMarker& SwiperComponent::GetRotationEventId() const
{
    return declaration_->GetRotationEventId();
}
void SwiperComponent::SetRotationEventId(const EventMarker& rotationEventId)
{
    declaration_->SetRotationEventId(rotationEventId);
}

const EventMarker& SwiperComponent::GetClickEventId() const
{
    return declaration_->GetClickEventId();
}

void SwiperComponent::SetClickEventId(const EventMarker& clickEventId)
{
    declaration_->SetClickEventId(clickEventId);
}

void SwiperComponent::SetDuration(double duration)
{
    declaration_->SetDuration(duration);
}
double SwiperComponent::GetDuration() const
{
    return declaration_->GetDuration();
}

void SwiperComponent::SetShowIndicator(bool showIndicator)
{
    declaration_->SetShowIndicator(showIndicator);
}

RefPtr<SwiperIndicator> SwiperComponent::GetIndicator() const
{
    if (declaration_->IsShowIndicator()) {
        return declaration_->GetIndicator();
    }
    return nullptr;
}

void SwiperComponent::SetIndicator(const RefPtr<SwiperIndicator>& indicator)
{
    declaration_->SetIndicator(indicator);
}

RefPtr<SwiperController> SwiperComponent::GetSwiperController() const
{
    return declaration_->GetSwiperController();
}

const RefPtr<RotationController>& SwiperComponent::GetRotationController() const
{
    return declaration_->GetRotationController();
}

void SwiperComponent::SetDigitalIndicator(bool digitalIndicator)
{
    return declaration_->SetDigitalIndicator(digitalIndicator);
}

bool SwiperComponent::GetDigitalIndicator() const
{
    return declaration_->GetDigitalIndicator();
}

AnimationCurve SwiperComponent::GetAnimationCurve() const
{
    return declaration_->GetAnimationCurve();
}

void SwiperComponent::SetAnimationCurve(AnimationCurve animationCurve)
{
    declaration_->SetAnimationCurve(animationCurve);
}

bool SwiperComponent::IsAnimationOpacity() const
{
    return declaration_->IsAnimationOpacity();
}

void SwiperComponent::SetAnimationOpacity(bool animationOpacity)
{
    declaration_->SetAnimationOpacity(animationOpacity);
}

} // namespace OHOS::Ace
