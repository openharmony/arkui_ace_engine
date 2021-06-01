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

#include "core/animation/shared_transition_controller.h"

#include "core/components/common/properties/tween_option.h"
#include "core/components/overlay/overlay_element.h"
#include "core/components/page/page_element.h"
#include "core/components/page_transition/page_transition_element.h"

namespace OHOS::Ace {
namespace {

RefPtr<SharedTransitionEffect> GetSharedEffect(const ShareId& shareId, const WeakPtr<SharedTransitionElement>& destWeak,
    const WeakPtr<SharedTransitionElement>& srcWeak)
{
    auto dest = destWeak.Upgrade();
    auto src = srcWeak.Upgrade();
    if ((!src) && (!dest)) {
        LOGE("No Shared element found. share id: %{public}s", shareId.c_str());
        return nullptr;
    }
    RefPtr<SharedTransitionEffect> effect = dest ? dest->GetEffect() : nullptr;
    if (!effect) {
        effect = src ? src->GetEffect() : nullptr;
    }
    if (!effect) {
        // use default effect.
        effect = SharedTransitionEffect::GetSharedTransitionEffect(
            SharedTransitionEffectType::SHARED_EFFECT_EXCHANGE, shareId);
    }
    return effect;
}

} // namespace

SharedTransitionController::SharedTransitionController(const WeakPtr<PipelineContext>& context) : context_(context)
{
    controller_ = AceType::MakeRefPtr<Animator>(context);
};

void SharedTransitionController::RegisterTransitionListener()
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Register Transition listener to stage failed. pipeline context is null.");
        return;
    }
    auto weak = AceType::WeakClaim(this);
    pipelineContext->AddPageTransitionListener(
        [weak](const TransitionEvent& event, const WeakPtr<PageElement>& in, const WeakPtr<PageElement>& out) {
            if ((event != TransitionEvent::POP_START) && (event != TransitionEvent::PUSH_START)) {
                LOGD("handle event: %{public}d failed. unknown event.", event);
                return;
            }
            auto controller = weak.Upgrade();
            if (!controller) {
                LOGE("handle event: %{public}d failed. controller is null.", event);
                return;
            }
            auto context = controller->context_.Upgrade();
            if (!context) {
                LOGE("Add shared transition to pipeline failed. context is null.");
                return;
            }
            if (event == TransitionEvent::PUSH_START) {
                controller->pageDest_ = in;
                controller->pageSrc_ = out;
            } else {
                controller->pageDest_ = out;
                controller->pageSrc_ = in;
            }
            controller->event_ = event;
            LOGD("Add shared transition controller to pipeline. event: %{public}d.", event);

            // when page pushed in, new pushed page's layout parameters is valid after perform layout.
            // And shared transition needs new pushed page's layout parameters.
            // So start shared transition in prepare animation.
            controller->StartSharedTransition();
        });
}

void SharedTransitionController::StartSharedTransition()
{
    // finish previous transition
    controller_->Finish();
    // clear controller
    controller_->ClearAllListeners();
    controller_->ClearInterpolators();
    controller_->ClearProxyControllers();
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Start shared transition failed. pipeline is null.");
        return;
    }
    auto overlay = pipelineContext->GetOverlayElement();
    if (!overlay) {
        LOGE("Start shared transition failed. overlay is null.");
        return;
    }
    KickoffSharedTransition(event_, overlay);
}

void SharedTransitionController::KickoffSharedTransition(TransitionEvent event, RefPtr<OverlayElement>& overlay)
{
    auto pageDest = pageDest_.Upgrade();
    if (!pageDest) {
        LOGE("Kickoff shared transition failed. page dest is null. event: %{public}d", event);
        return;
    }
    auto destTransition = PageTransitionElement::GetTransitionElement(pageDest);
    auto pageId = pageDest->GetPageId();
    if (!destTransition) {
        LOGE("Kickoff shared transition failed. page transition is null. page id: %{public}d", pageId);
        return;
    }
    hasSharedTransition_ = PrepareTransition(overlay);
    if (!hasSharedTransition_) {
        LOGI("No shared elements found. event: %{public}d. dest page id: %{public}d", event_, pageId);
        return;
    }
    controller_->AddStopListener([overlayWeak = WeakClaim(RawPtr(overlay))]() {
        auto overlay = overlayWeak.Upgrade();
        if (overlay) {
            // shared element will be removed when get off shuttle, just make sure no shared left on the overlay
            overlay->Clear();
        }
    });
    controller_->SetFillMode(FillMode::FORWARDS);
    // Play together with page transition in stage element.
}

bool SharedTransitionController::PrepareTransition(RefPtr<OverlayElement> overlay, bool preCheck)
{
    auto pageDest = pageDest_.Upgrade();
    auto pageSrc = pageSrc_.Upgrade();
    if ((!pageSrc) || (!pageDest)) {
        LOGD("Prepare shared transition failed. page src / dest is null. event: %{public}d", event_);
        return false;
    }
    LOGD("Kickoff shared transition. event: %{public}d. src page id: %{public}d, dest page id: %{public}d", event_,
        pageSrc->GetPageId(), pageDest->GetPageId());
    const auto& srcMap = pageSrc->GetSharedTransitionMap();
    const auto& destMap = pageDest->GetSharedTransitionMap();
    bool hasShared = false;
    WeakPtr<SharedTransitionElement> srcWeak;
    for (auto& item : destMap) {
        auto shareId = item.first;
        auto& destWeak = item.second;
        auto srcSharedIter = srcMap.find(shareId);
        if (srcSharedIter == srcMap.end()) {
            LOGD("Shared src not found, maybe the effect do not need it. share id: %{public}s", shareId.c_str());
            srcWeak.Reset();
        } else {
            srcWeak = srcSharedIter->second;
        }
        RefPtr<SharedTransitionEffect> effect = GetSharedEffect(shareId, destWeak, srcWeak);
        if (!effect) {
            LOGE("Shared effect is null, maybe no shared element at all. share id: %{public}s", shareId.c_str());
            continue;
        }
        effect->SetSharedElement(srcWeak, destWeak);
        if (!effect->Allow(event_)) {
            LOGD("Shared transition not allowed, event: %{public}d, share id: %{public}s", event_, shareId.c_str());
            continue;
        }
        if (preCheck) {
            // Return true, when find the first shared transition.
            return true;
        }
        if (!PrepareEachTransition(shareId, effect, overlay)) {
            LOGE("Prepare shared transition failed. share id: %{public}s", shareId.c_str());
            continue;
        }
        hasShared = true;
    }
    if (!hasShared) {
        LOGD("No shared elements found. event: %{public}d. Shared size: dest: %{public}zu, src: %{public}zu", event_,
            destMap.size(), srcMap.size());
    }
    return hasShared;
}

bool SharedTransitionController::PrepareEachTransition(
    const ShareId& shareId, RefPtr<SharedTransitionEffect>& effect, RefPtr<OverlayElement>& overlay)
{
    auto destWeak = effect->GetDestSharedElement();
    auto dest = destWeak.Upgrade();
    if (!dest) {
        LOGE("Prepare each transition failed. dest is null. share id: %{public}s", shareId.c_str());
        return false;
    }
    auto option = dest->GetOption();
    if (!effect->CreateAnimation(option, event_, false)) {
        LOGE("Create animation failed. event: %{public}d, share id: %{public}s", event_, shareId.c_str());
        return false;
    }
    if (!effect->ApplyAnimation(overlay, controller_, option, event_)) {
        LOGE("Apply animation failed. event: %{public}d, share id: %{public}s", event_, shareId.c_str());
        return false;
    }
    LOGD("Prepare Shared Transition. event: %{public}d, share id: %{public}s", event_, shareId.c_str());

    dest->SetVisible(false);
    auto weakDestShared = effect->GetDestSharedElement();
    controller_->AddStopListener([destWeak, shareId, event = event_]() {
        auto dest = destWeak.Upgrade();
        if (!dest) {
            LOGE("Stop shared element failed. shared in element is null. event: %{public}d, shareId: %{public}s", event,
                shareId.c_str());
            return;
        }
        dest->SetVisible(true);
    });
    return true;
}

bool SharedTransitionController::HasSharedTransition(TransitionEvent event)
{
    if (event_ == event) {
        return hasSharedTransition_;
    } else {
        auto originEvent = event_;
        event_ = event;
        bool hasSharedTransition = PrepareTransition(nullptr, true);
        event_ = originEvent;
        return hasSharedTransition;
    }
}

} // namespace OHOS::Ace
