/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TRANSITION_PROXY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TRANSITION_PROXY_H

#include "base/memory/ace_type.h"
#include "frameworks/core/components_ng/pattern/navigation/navigation_declaration.h"
#include "frameworks/core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "frameworks/core/components_ng/pattern/navrouter/navdestination_pattern.h"
namespace OHOS::Ace::NG {

namespace {
std::atomic<uint64_t> g_proxyNextAutoGenId = 0;
}

using namespace Framework;
class NavigationTransitionProxy : public AceType {
    DECLARE_ACE_TYPE(NavigationTransitionProxy, AceType);

public:
    NavigationTransitionProxy()
    {
        proxyId_ = g_proxyNextAutoGenId.fetch_add(1);
    }
    ~NavigationTransitionProxy() = default;

    RefPtr<NG::NavDestinationContext> GetPreDestinationContext() const
    {
        return preContext_;
    }

    RefPtr<NG::NavDestinationContext> GetTopDestinationContext() const
    {
        return topContext_;
    }

    void SetPreDestination(const RefPtr<NavDestinationGroupNode>& preDestination)
    {
        CHECK_NULL_VOID(preDestination);
        auto pattern = AceType::DynamicCast<NavDestinationPattern>(preDestination->GetPattern());
        CHECK_NULL_VOID(pattern);
        preContext_ = pattern->GetNavDestinationContext();
        CHECK_NULL_VOID(preContext_);
        preContext_->SetNavPathInfo(pattern->GetNavPathInfo());
    }

    void SetTopDestination(const RefPtr<NavDestinationGroupNode>& topDestination)
    {
        CHECK_NULL_VOID(topDestination);
        auto pattern = AceType::DynamicCast<NavDestinationPattern>(topDestination->GetPattern());
        CHECK_NULL_VOID(pattern);
        topContext_ = pattern->GetNavDestinationContext();
        CHECK_NULL_VOID(topContext_);
        topContext_->SetNavPathInfo(pattern->GetNavPathInfo());
    }

    void SetFinishTransitionEvent(std::function<void()>&& event)
    {
        finishCallback_ = std::move(event);
    }

    void FireFinishCallback()
    {
        if (interactive_) {
            FinishInteractiveAnimation();
            return;
        }
        if (hasFinished_ || !finishCallback_) {
            TAG_LOGE(AceLogTag::ACE_NAVIGATION, "not support to finish custom animation more than once");
            return;
        }
        hasFinished_ = true;
        finishCallback_();
        if (endCallback_) {
            endCallback_(true);
        }
    }

    void SetIsSuccess(bool isSuccess)
    {
        isSuccess_ = isSuccess;
    }

    void SetIsFinished(bool isFinished)
    {
        hasFinished_ = isFinished;
    }

    bool GetIsFinished() const
    {
        return hasFinished_;
    }

    void SetNavigationOperation(NavigationOperation operation)
    {
        operation_ = operation;
    }

    void SetCancelAnimationCallback(std::function<void()>&& cancelAnimation)
    {
        cancelAnimation_ = std::move(cancelAnimation);
    }

    void FireCancelAnimation()
    {
        if (!cancelAnimation_ || hasFinished_ || !interactive_) {
            return;
        }
        cancelAnimation_();
    }

    void SetInteractive(bool interactive)
    {
        interactive_ = interactive;
    }

    bool GetInteractive() const
    {
        return interactive_;
    }

    void SetEndCallback(std::function<void(bool)>&& callback)
    {
        endCallback_ = std::move(callback);
    }

    void FireEndCallback()
    {
        if (endCallback_) {
            endCallback_(isSuccess_);
        }
    }

    bool GetIsSuccess()
    {
        return isSuccess_;
    }

    void SetInteractiveAnimation(
        std::shared_ptr<AnimationUtils::InteractiveAnimation> interactiveAnimation,
        const std::function<void()>& finishCallback)
    {
        interactiveAnimation_ = interactiveAnimation;
        interactiveFinishCallback_ = finishCallback;
    }

    void StartAnimation()
    {
        if (!interactiveAnimation_) {
            return;
        }
        // if error code is 0, start interactive success
        int32_t errorCode = AnimationUtils::StartInteractiveAnimation(interactiveAnimation_);
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "update start interactive animation code is %{public}d", errorCode);
        isStartAnimation_ = errorCode == 0;
    }

    void UpdateTransition(float progress)
    {
        if (!interactive_ || hasFinished_) {
            return;
        }
        AnimationUtils::UpdateInteractiveAnimation(interactiveAnimation_, progress);
    }

    void FinishInteractiveAnimation()
    {
        if (!interactive_ || hasFinished_) {
            TAG_LOGE(AceLogTag::ACE_NAVIGATION, "not support to finish interactive animation more than once");
            return;
        }
        hasFinished_ = true;
        isSuccess_ = true;
        if (!isStartAnimation_) {
            interactiveFinishCallback_();
            if (endCallback_) {
                endCallback_(true);
            }
            return;
        }
        AnimationUtils::ContinueInteractiveAnimation(interactiveAnimation_);
    }

    void CancelInteractiveAnimation()
    {
        if (!interactive_ || hasFinished_) {
            TAG_LOGE(AceLogTag::ACE_NAVIGATION, "not support to cancel interactive animation more than once");
            return;
        }
        hasFinished_ = true;
        isSuccess_ = false;
        if (!isStartAnimation_) {
            interactiveFinishCallback_();
            if (endCallback_) {
                endCallback_(false);
            }
            return;
        }
        AnimationUtils::ReverseInteractiveAnimation(interactiveAnimation_);
    }

    void AddInteractiveAnimation(const std::function<void()>& callback)
    {
        if (!interactive_) {
            return;
        }
        AnimationUtils::AddInteractiveAnimation(interactiveAnimation_, callback);
    }

    uint64_t GetProxyId() const
    {
        return proxyId_;
    }

private:
    uint64_t proxyId_ = 0;
    RefPtr<NavDestinationContext> preContext_;
    RefPtr<NavDestinationContext> topContext_;
    std::function<void()> finishCallback_; // finish transition callback to continue animation
    std::function<void()> cancelAnimation_; // cancel transition callback to reverse animation
    std::function<void(bool)> endCallback_;
    std::function<void()> interactiveFinishCallback_;
    NavigationOperation operation_;
    std::shared_ptr<AnimationUtils::InteractiveAnimation> interactiveAnimation_;
    bool hasFinished_ = false; // current transition is finish or not
    bool isSuccess_ = true; // set current custom transition is start success or not
    bool interactive_ = false; // set current interactive animation
    bool isStartAnimation_ = false;
};

struct NavigationTransition {
    int32_t timeout = 1000;
    std::function<void(const RefPtr<NavigationTransitionProxy>&)> transition;
    std::function<void(bool)> endCallback;
    bool isValid = true;
    bool interactive = false;
};
} // namespace OHOS::Ace::NG
#endif