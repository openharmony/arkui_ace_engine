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

using namespace Framework;
class NavigationTransitionProxy : public AceType {
    DECLARE_ACE_TYPE(NavigationTransitionProxy, AceType);

public:
    NavigationTransitionProxy() = default;
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
        preContext_->SetNavPathInfo(pattern->GetNavPathInfo());
    }

    void SetTopDestination(const RefPtr<NavDestinationGroupNode>& topDestination)
    {
        CHECK_NULL_VOID(topDestination);
        auto pattern = AceType::DynamicCast<NavDestinationPattern>(topDestination->GetPattern());
        CHECK_NULL_VOID(pattern);
        topContext_ = pattern->GetNavDestinationContext();
        topContext_->SetNavPathInfo(pattern->GetNavPathInfo());
    }

    void SetFinishTransitionEvent(std::function<void()>&& event)
    {
        finishCallback_ = std::move(event);
    }

    void FireFinishCallback()
    {
        isSuccess_ = true;
        if (interactive_) {
            FinishInteractiveAnimation();
            return;
        }
        if (hasFinished_ || !finishCallback_) {
            return;
        }
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
        isSuccess_ = false;
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

    void SetInteractiveAnimation(std::shared_ptr<AnimationUtils::InteractiveAnimation> interactiveAnimation)
    {
        interactiveAnimation_ = interactiveAnimation;
    }

    void StartAnimation()
    {
        if (!interactiveAnimation_) {
            return;
        }
        AnimationUtils::StartInteractiveAnimation(interactiveAnimation_);
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
            return;
        }
        AnimationUtils::ContinueInteractiveAnimation(interactiveAnimation_);
    }

    void CancelInteractiveAnimation()
    {
        if (!interactive_ || hasFinished_) {
            return;
        }
        AnimationUtils::ReverseInteractiveAnimation(interactiveAnimation_);
    }

private:
    RefPtr<NavDestinationContext> preContext_;
    RefPtr<NavDestinationContext> topContext_;
    std::function<void()> finishCallback_; // finish transition callback to continue animation
    std::function<void()> cancelAnimation_; // cancel transition callback to reverse animation
    std::function<void(bool)> endCallback_;
    NavigationOperation operation_;
    std::shared_ptr<AnimationUtils::InteractiveAnimation> interactiveAnimation_;
    bool hasFinished_ = false; // current transition is finish or not
    bool isSuccess_ = true; // set current custom transition is start success or not
    bool interactive_ = false; // set current interactive animation
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