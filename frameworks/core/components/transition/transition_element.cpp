/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/transition/transition_element.h"

#include "core/components/transition/transition_component.h"
#include "core/components/tween/tween_component.h"
#include "core/components/tween/tween_element.h"

namespace OHOS::Ace {

void TransitionElement::Update()
{
    ComposedElement::Update();
    if (!component_) {
        LOGE("Update failed. component is null");
        return;
    }
    const auto transitionComponent = AceType::DynamicCast<TransitionComponent>(component_);
    if (!transitionComponent) {
        LOGE("transition element update failed. transition component is null.");
        return;
    }
    optionMap_[TransitionOptionType::TRANSITION_IN] = transitionComponent->GetTransitionInOption();
    optionMap_[TransitionOptionType::TRANSITION_OUT] = transitionComponent->GetTransitionOutOption();
}

void TransitionElement::SetController(const RefPtr<Animator>& controller)
{
    auto tween = GetChildTween();
    if (!tween) {
        LOGE("set controller failed. no tween found.");
        return;
    }
    tween->SetController(controller);
}

RefPtr<Animator> TransitionElement::GetController() const
{
    auto tween = GetChildTween();
    if (!tween) {
        LOGE("get controller failed. no tween found.");
        return nullptr;
    }
    return tween->GetController();
}

void TransitionElement::SetTouchable(bool enable)
{
    auto tween = GetChildTween();
    if (!tween) {
        LOGE("set touchable failed. no tween found. enable: %{public}d", enable);
        return;
    }
    tween->SetTouchable(enable);
}

void TransitionElement::SwitchTransitionOption(TransitionOptionType type, bool needApplyOption)
{
    auto tween = GetChildTween();
    if (!tween) {
        LOGE("Switch transition option failed. no tween found. direction: %{public}d", type);
        return;
    }
    optionMap_[type].ClearListeners();
    // If never set before, use empty option instead.
    tween->SetOption(optionMap_[type]);
    if (!tween->ApplyKeyframes()) {
        LOGW("Apply transition option failed. tween apply option fail.");
    }
    if (needApplyOption) {
        tween->ApplyOptions();
    }
}

RefPtr<Component> TransitionElement::BuildChild()
{
    RefPtr<TransitionComponent> transition = AceType::DynamicCast<TransitionComponent>(component_);
    if (transition) {
        RefPtr<TweenComponent> tweenComponent =
            AceType::MakeRefPtr<TweenComponent>(TweenComponent::AllocTweenComponentId(), transition->GetName());
        tweenComponent->SetChild(ComposedElement::BuildChild());
        tweenComponent->SetIsFirstFrameShow(transition->IsFirstFrameShow());
        return tweenComponent;
    } else {
        LOGE("no transition component found. return empty child.");
        return nullptr;
    }
}

void TransitionElement::SetVisible(VisibleType visible)
{
    auto tween = GetChildTween();
    if (!tween) {
        LOGE("set visible failed. no tween found. visible: %{public}d", visible);
        return;
    }
    tween->SetVisible(visible);
}

RefPtr<TweenElement> TransitionElement::GetChildTween() const
{
    if (children_.empty()) {
        LOGW("get child tween failed. no child yet.");
        return nullptr;
    }
    const auto& child = children_.front();
    if (!child) {
        LOGW("get child tween failed. null child.");
        return nullptr;
    }
    auto tween = AceType::DynamicCast<TweenElement>(child);
    if (!tween) {
        LOGW("get child tween failed. null tween.");
        return nullptr;
    }
    return tween;
}

void TransitionElement::SetTransition(const TweenOption& inOption, const TweenOption& outOption)
{
    optionMap_[TransitionOptionType::TRANSITION_IN] = inOption;
    optionMap_[TransitionOptionType::TRANSITION_OUT] = outOption;
}

void TransitionElement::SetSharedTransition(const TweenOption& inOption, const TweenOption& outOption)
{
    optionMap_[TransitionOptionType::TRANSITION_SHARED_IN] = inOption;
    optionMap_[TransitionOptionType::TRANSITION_SHARED_OUT] = outOption;
}

RefPtr<Element> TransitionElement::GetContentElement() const
{
    auto tween = GetChildTween();
    if (!tween) {
        LOGE("get content element failed. no tween found.");
        return nullptr;
    }
    return tween->GetContentElement();
}

} // namespace OHOS::Ace
