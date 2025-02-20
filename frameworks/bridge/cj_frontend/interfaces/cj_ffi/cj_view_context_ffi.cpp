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


#include "cj_view_context_ffi.h"
#include "cj_lambda.h"
#include "base/log/jank_frame_report.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/view_context/view_context_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::Framework {
namespace {
    constexpr uint32_t DEFAULT_DURATION = 1000; // ms
    constexpr int64_t MICROSEC_TO_MILLISEC = 1000;
}

int64_t GetFormAnimationTimeInterval(const RefPtr<PipelineBase>& pipelineContext)
{
    CHECK_NULL_RETURN(pipelineContext, 0);
    return (GetMicroTickCount() - pipelineContext->GetFormAnimationStartTime()) / MICROSEC_TO_MILLISEC;
}

bool CheckIfSetFormAnimationDuration(const RefPtr<PipelineBase>& pipelineContext, const AnimationOption& option)
{
    CHECK_NULL_RETURN(pipelineContext, false);
    return pipelineContext->IsFormAnimationFinishCallback() && pipelineContext->IsFormRenderExceptDynamicComponent() &&
        option.GetDuration() > (DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContext));
}

bool CheckContainer(const RefPtr<Container>& container)
{
    auto context = container->GetPipelineContext();
    if (!context) {
        return false;
    }
    if (!container->IsFRSCardContainer() && !container->WindowIsShow()) {
        return false;
    }
    auto executor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(executor, false);
    return executor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI);
}

void AnimateToForStageMode(const RefPtr<PipelineBase>& pipelineContext, AnimationOption& option,
    void (*callback)(), const std::function<void()>& onFinishEvent, bool immediately)
{
    auto triggerId = pipelineContext->GetInstanceId();
    AceEngine::Get().NotifyContainers([triggerId, option](const RefPtr<Container>& container) {
        if (!CheckContainer(container)) {
            return;
        }
        ContainerScope scope(container->GetInstanceId());
        auto context = container->GetPipelineContext();
        context->FlushBuild();
        if (context->GetInstanceId() == triggerId) {
            return;
        }
        context->PrepareOpenImplicitAnimation();
    });
    pipelineContext->OpenImplicitAnimation(option, option.GetCurve(), onFinishEvent);
    auto previousOption = pipelineContext->GetSyncAnimationOption();
    pipelineContext->SetSyncAnimationOption(option);
    // Execute the function.
    auto ffiCallback = CJLambda::Create(callback);
    ffiCallback();
    AceEngine::Get().NotifyContainers([triggerId](const RefPtr<Container>& container) {
        if (!CheckContainer(container)) {
            return;
        }
        auto context = container->GetPipelineContext();
        ContainerScope scope(container->GetInstanceId());
        context->FlushBuild();
        if (context->GetInstanceId() == triggerId) {
            return;
        }
        context->PrepareCloseImplicitAnimation();
    });
    pipelineContext->CloseImplicitAnimation();
    pipelineContext->SetSyncAnimationOption(previousOption);
    if (immediately) {
        pipelineContext->FlushMessages();
    } else {
        pipelineContext->RequestFrame();
    }
}

extern "C" {
void FfiOHOSAceFrameworkViewContextAnimation(NativeOptionAnimateParam animateOptParam)
{
    ACE_FUNCTION_TRACE();
    if (ViewStackModel::GetInstance()->CheckTopNodeFirstBuilding()) {
        // the node sets attribute value for the first time. No animation is generated.
        return;
    }
    AnimationOption animateOpt = AnimationOption();
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContextBase = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContextBase);
    if (pipelineContextBase->IsFormAnimationFinishCallback() &&
        pipelineContextBase->IsFormRenderExceptDynamicComponent() &&
        GetFormAnimationTimeInterval(pipelineContextBase) > DEFAULT_DURATION) {
        return;
    }

    NativeAnimateParam animateParam;
    if (animateOptParam.hasValue) {
        animateParam = animateOptParam.value;
    } else {
        ViewContextModel::GetInstance()->closeAnimation(animateOpt, true);
        return;
    }
    ParseCjAnimation(animateParam, animateOpt);
    if (pipelineContextBase->IsFormAnimationFinishCallback() &&
        pipelineContextBase->IsFormRenderExceptDynamicComponent() &&
        animateOpt.GetDuration() > (DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase))) {
        animateOpt.SetDuration(DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase));
        TAG_LOGW(AceLogTag::ACE_FORM, "[Form animation]  Form animation SetDuration: %{public}lld ms",
            static_cast<long long>(DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase)));
    }

    if (SystemProperties::GetRosenBackendEnabled()) {
        animateOpt.SetAllowRunningAsynchronously(true);
    }
    ViewContextModel::GetInstance()->openAnimation(animateOpt);
    JankFrameReport::GetInstance().ReportJSAnimation();
}

void FfiOHOSAceFrameworkViewContextAnimationTo(NativeAnimateParam animateParam, void (*callback)(), bool isImmediately)
{
    ACE_FUNCTION_TRACE();
    auto container = Container::CurrentSafelyWithCheck();
    CHECK_NULL_VOID(container);
    if (!Container::CheckRunOnThreadByThreadId(container->GetInstanceId(), false)) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "animationTo not run on running thread, currentId:%{public}d",
            container->GetInstanceId());
        return;
    }
    ContainerScope scope(container->GetInstanceId());
    auto pipelineContextBase = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContextBase);
    if (pipelineContextBase->IsFormAnimationFinishCallback() &&
        pipelineContextBase->IsFormRenderExceptDynamicComponent() &&
        GetFormAnimationTimeInterval(pipelineContextBase) > DEFAULT_DURATION) {
        return;
    }
    AnimationOption animateOpt;
    ParseCjAnimation(animateParam, animateOpt);
    if (CheckIfSetFormAnimationDuration(pipelineContextBase, animateOpt)) {
        animateOpt.SetDuration(DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase));
        TAG_LOGW(AceLogTag::ACE_FORM, "[Form animation]  Form animation SetDuration: %{public}lld ms",
            static_cast<long long>(DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase)));
    }
    if (SystemProperties::GetRosenBackendEnabled()) {
        if (pipelineContextBase->IsLayouting()) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION,
                "pipeline is layouting, post animateTo, duration:%{public}d, curve:%{public}s",
                animateOpt.GetDuration(), animateOpt.GetCurve() ? animateOpt.GetCurve()->ToString().c_str() : "");
            pipelineContextBase->GetTaskExecutor()->PostTask(
                [id = Container::CurrentIdSafely(), animateOpt, callback, isImmediately]() mutable {
                    ContainerScope scope(id);
                    auto container = Container::CurrentSafely();
                    CHECK_NULL_VOID(container);
                    auto pipelineContext = container->GetPipelineContext();
                    CHECK_NULL_VOID(pipelineContext);
                    AnimateToForStageMode(pipelineContext, animateOpt, callback,
                                          animateOpt.GetOnFinishEvent(), isImmediately);
                },
                TaskExecutor::TaskType::UI, "CJAnimationTo");
            return;
        }
        AnimateToForStageMode(pipelineContextBase, animateOpt, callback, animateOpt.GetOnFinishEvent(), isImmediately);
    } else {
        pipelineContextBase->FlushBuild();
        pipelineContextBase->SaveExplicitAnimationOption(animateOpt);
        // Execute the function.
        auto ffiCallback = CJLambda::Create(callback);
        ffiCallback();
        pipelineContextBase->FlushBuild();
        pipelineContextBase->CreateExplicitAnimator(animateOpt.GetOnFinishEvent());
        pipelineContextBase->ClearExplicitAnimationOption();
    }
}
}
}