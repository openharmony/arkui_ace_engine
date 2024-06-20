/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/node_animate.h"

#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
namespace OHOS::Ace::NG::ViewAnimate {
namespace {
const std::vector<OHOS::Ace::RefPtr<OHOS::Ace::Curve>> CURVES_LIST = {
    OHOS::Ace::Curves::LINEAR,
    OHOS::Ace::Curves::EASE,
    OHOS::Ace::Curves::EASE_IN,
    OHOS::Ace::Curves::EASE_OUT,
    OHOS::Ace::Curves::EASE_IN_OUT,
    OHOS::Ace::Curves::FAST_OUT_SLOW_IN,
    OHOS::Ace::Curves::LINEAR_OUT_SLOW_IN,
    OHOS::Ace::Curves::FAST_OUT_LINEAR_IN,
    OHOS::Ace::Curves::EXTREME_DECELERATION,
    OHOS::Ace::Curves::SHARP,
    OHOS::Ace::Curves::RHYTHM,
    OHOS::Ace::Curves::SMOOTH,
    OHOS::Ace::Curves::FRICTION,
};

const std::vector<AnimationDirection> DIRECTION_LIST = {
    AnimationDirection::NORMAL,
    AnimationDirection::REVERSE,
    AnimationDirection::ALTERNATE,
    AnimationDirection::ALTERNATE_REVERSE,
};
} // namespace

void AnimateToInner(ArkUIContext* context, AnimationOption& option, const std::function<void()>& animateToFunc,
    const std::function<void()>& onFinishFunc, bool immediately)
{
    CHECK_NULL_VOID(context);
    ContainerScope scope(context->id);
    auto containerSafely = Container::GetContainer(context->id);
    CHECK_NULL_VOID(containerSafely);
    auto pipelineContext = containerSafely->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);

    ACE_SCOPED_TRACE("duration:%d, curve:%s, iteration:%d", option.GetDuration(), option.GetCurve()->ToString().c_str(),
        option.GetIteration());
    auto triggerId = context->id;
    AceEngine::Get().NotifyContainers([triggerId, option](const RefPtr<Container>& container) {
        auto context = container->GetPipelineContext();
        if (!context) {
            // pa container do not have pipeline context.
            return;
        }
        if (!container->GetSettings().usingSharedRuntime) {
            return;
        }
        if (!container->IsFRSCardContainer() && !container->WindowIsShow()) {
            return;
        }
        ContainerScope scope(container->GetInstanceId());
        context->FlushBuild();
        if (context->GetInstanceId() == triggerId) {
            return;
        }
        context->PrepareOpenImplicitAnimation();
    });
    pipelineContext->OpenImplicitAnimation(option, option.GetCurve(), onFinishFunc);
    pipelineContext->SetSyncAnimationOption(option);
    // Execute the function.
    animateToFunc();
    pipelineContext->FlushOnceVsyncTask();
    AceEngine::Get().NotifyContainers([triggerId](const RefPtr<Container>& container) {
        auto context = container->GetPipelineContext();
        if (!context) {
            // pa container do not have pipeline context.
            return;
        }
        if (!container->GetSettings().usingSharedRuntime) {
            return;
        }
        if (!container->IsFRSCardContainer() && !container->WindowIsShow()) {
            return;
        }
        ContainerScope scope(container->GetInstanceId());
        context->FlushBuild();
        if (context->GetInstanceId() == triggerId) {
            return;
        }
        context->PrepareCloseImplicitAnimation();
    });
    pipelineContext->CloseImplicitAnimation();
    pipelineContext->SetSyncAnimationOption(AnimationOption());
    if (immediately) {
        pipelineContext->FlushMessages();
    } else {
        pipelineContext->RequestFrame();
    }
}

void AnimateTo(ArkUIContext* context, ArkUIAnimateOption option, void (*event)(void* userData), void* user)
{
    AnimationOption animationOption;
    animationOption.SetDuration(NearZero(static_cast<double>(option.tempo)) ? 0 : option.duration);
    animationOption.SetTempo(option.tempo);
    animationOption.SetCurve(CURVES_LIST[option.curve > CURVES_LIST.size() ? 0 : option.curve]);
    animationOption.SetDelay(option.delay);
    animationOption.SetIteration(option.iterations);
    animationOption.SetAnimationDirection(
        DIRECTION_LIST[option.playMode > DIRECTION_LIST.size() ? 0 : option.playMode]);
    animationOption.SetFinishCallbackType(static_cast<FinishCallbackType>(option.finishCallbackType));

    if (option.expectedFrameRateRange) {
        RefPtr<FrameRateRange> frameRateRange = AceType::MakeRefPtr<FrameRateRange>(option.expectedFrameRateRange->min,
            option.expectedFrameRateRange->max, option.expectedFrameRateRange->expected);
        animationOption.SetFrameRateRange(frameRateRange);
    }

    auto onEvent = [event, user]() {
        if (event) {
            event(user);
        }
    };

    auto onFinishEvent = [option]() {
        if (option.onFinishCallback) {
            auto* onFinishFunc = reinterpret_cast<void (*)(void*)>(option.onFinishCallback);
            onFinishFunc(option.user);
        }
    };

    AnimateToInner(context, animationOption, onEvent, onFinishEvent, false);
}

} // namespace OHOS::Ace::NG::ViewAnimate
