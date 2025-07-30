/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "global_scope_animation_helper.h"

#include "base/log/jank_frame_report.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/animation/animation_pub.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace {
constexpr uint32_t DEFAULT_DURATION = 1000; // ms
constexpr int64_t MICROSEC_TO_MILLISEC = 1000;
constexpr int32_t MAX_FLUSH_COUNT = 2;
}

namespace OHOS::Ace::NG::GeneratedModifier {
bool CheckRunOnThreadByThreadId(int32_t currentId, bool defaultRes)
{
    auto container = Container::GetContainer(currentId);
    CHECK_NULL_RETURN(container, defaultRes);
    auto executor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(executor, defaultRes);
    return executor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI);
}
void RecordAnimationFinished(int32_t count)
{
    if (Recorder::EventRecorder::Get().IsRecordEnable(Recorder::EventCategory::CATEGORY_ANIMATION)) {
        Recorder::EventParamsBuilder builder;
        builder.SetEventCategory(Recorder::EventCategory::CATEGORY_ANIMATION)
            .SetEventType(Recorder::EventType::ANIMATION_FINISHED)
            .SetExtra(Recorder::KEY_COUNT, std::to_string(count));
        Recorder::EventRecorder::Get().OnEvent(std::move(builder));
    }
}
int64_t GetFormAnimationTimeInterval(const RefPtr<PipelineBase>& pipelineContext)
{
    CHECK_NULL_RETURN(pipelineContext, 0);
    return (GetMicroTickCount() - pipelineContext->GetFormAnimationStartTime()) / MICROSEC_TO_MILLISEC;
}
bool CheckIfSetFormAnimationDuration(const RefPtr<PipelineBase>& pipelineContext, const AnimationOption& option)
{
    CHECK_NULL_RETURN(pipelineContext, false);
    return pipelineContext->IsFormAnimationFinishCallback() && pipelineContext->IsFormRender() &&
        option.GetDuration() > (DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContext));
}
// check whether this container needs to perform animateTo
bool CheckContainer(const RefPtr<Container>& container)
{
    CHECK_NULL_RETURN(container, false);
    auto context = container->GetPipelineContext();
    CHECK_NULL_RETURN(context, false);
    CHECK_NULL_RETURN(container->GetSettings().usingSharedRuntime, false);
    if (!container->IsFRSCardContainer() && !container->WindowIsShow()) {
        return false;
    }
    auto executor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(executor, false);
    return executor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI);
}
bool GetAnyContextIsLayouting(const RefPtr<PipelineBase>& currentPipeline)
{
    if (currentPipeline->IsLayouting()) {
        return true;
    }
    bool isLayouting = false;
    AceEngine::Get().NotifyContainers([&isLayouting](const RefPtr<Container>& container) {
        if (isLayouting) {
            // One container is already in layouting
            return;
        }
        if (!CheckContainer(container)) {
            return;
        }
        auto context = container->GetPipelineContext();
        isLayouting |= context->IsLayouting();
    });
    return isLayouting;
}
void FlushDirtyNodesWhenExist(const RefPtr<PipelineBase>& pipelineContext,
    const AnimationOption& option, const std::optional<int32_t>& count, AnimationInterface interface)
{
    auto animationInterfaceName = GetAnimationInterfaceName(interface);
    CHECK_NULL_VOID(animationInterfaceName);
    int32_t flushCount = 0;
    bool isDirtyNodesEmpty = pipelineContext->IsDirtyNodesEmpty();
    bool isDirtyLayoutNodesEmpty = pipelineContext->IsDirtyLayoutNodesEmpty();
    while ((!isDirtyNodesEmpty || (!isDirtyLayoutNodesEmpty && !pipelineContext->IsLayouting())) &&
       flushCount < MAX_FLUSH_COUNT && option.GetIteration() == ANIMATION_REPEAT_INFINITE) {
        if (!isDirtyNodesEmpty) {
            pipelineContext->FlushBuild();
            isDirtyLayoutNodesEmpty = pipelineContext->IsDirtyLayoutNodesEmpty();
        }
        if (!isDirtyLayoutNodesEmpty && !pipelineContext->IsLayouting()) {
            pipelineContext->FlushUITasks(true);
        }
        isDirtyNodesEmpty = pipelineContext->IsDirtyNodesEmpty();
        isDirtyLayoutNodesEmpty = pipelineContext->IsDirtyLayoutNodesEmpty();
        flushCount++;
    }
}
void AnimateToForStageMode(const RefPtr<PipelineBase>& pipelineContext, const AnimationOption& option,
    const Callback_Void* event, int32_t triggerId, const std::optional<int32_t>& count)
{
    CHECK_NULL_VOID(event);
    pipelineContext->StartImplicitAnimation(option, option.GetCurve(), option.GetOnFinishEvent(), count);
    auto previousOption = pipelineContext->GetSyncAnimationOption();
    pipelineContext->SetSyncAnimationOption(option);
    // Execute the function.
    CallbackHelper(*event).Invoke();
    pipelineContext->FlushOnceVsyncTask();
    AceEngine::Get().NotifyContainersOrderly([triggerId](const RefPtr<Container>& container) {
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
}
void StartAnimationForStageMode(const RefPtr<PipelineBase>& pipelineContext, const AnimationOption& option,
    const Callback_Void* event, const std::optional<int32_t>& count, bool immediately)
{
    auto triggerId = pipelineContext->GetInstanceId();
    NG::ScopedViewStackProcessor scopedProcessor;
    AceEngine::Get().NotifyContainersOrderly([triggerId](const RefPtr<Container>& container) {
        if (!CheckContainer(container)) {
            return;
        }
        auto context = container->GetPipelineContext();
        ContainerScope scope(container->GetInstanceId());
        context->FlushBuild();
        if (context->GetInstanceId() == triggerId) {
            return;
        }
        context->PrepareOpenImplicitAnimation();
    });
    pipelineContext->PrepareOpenImplicitAnimation();
    FlushDirtyNodesWhenExist(pipelineContext, option, count,
        immediately ? AnimationInterface::ANIMATE_TO_IMMEDIATELY : AnimationInterface::ANIMATE_TO);
    if (!pipelineContext->CatchInteractiveAnimations([pipelineContext, option, event, triggerId, count]() {
        AnimateToForStageMode(pipelineContext, option, event, triggerId, count);
    })) {
        AnimateToForStageMode(pipelineContext, option, event, triggerId, count);
    }
    pipelineContext->FlushAfterLayoutCallbackInImplicitAnimationTask();
    if (immediately) {
        pipelineContext->FlushModifier();
        pipelineContext->FlushMessages();
        JankFrameReport::GetInstance().RecordAnimateEnd();
    } else {
        pipelineContext->RequestFrame();
    }
}
void StartAnimateToForFaMode(const RefPtr<PipelineBase>& pipelineContext, AnimationOption& option,
    const Callback_Void* event, const std::optional<int32_t>& count, bool immediately)
{
    NG::ScopedViewStackProcessor scopedProcessor;
    pipelineContext->FlushBuild();
    pipelineContext->OpenImplicitAnimation(option, option.GetCurve(), option.GetOnFinishEvent());
    auto previousOption = pipelineContext->GetSyncAnimationOption();
    pipelineContext->SetSyncAnimationOption(option);
    CallbackHelper(*event).Invoke();
    pipelineContext->FlushBuild();
    pipelineContext->CloseImplicitAnimation();
    pipelineContext->SetSyncAnimationOption(previousOption);
    if (immediately) {
        pipelineContext->FlushModifier();
        pipelineContext->FlushMessages();
        JankFrameReport::GetInstance().RecordAnimateEnd();
    } else {
        pipelineContext->RequestFrame();
    }
}
void StartAnimateTo(AnimationOption& option, const Callback_Void* event, const std::optional<int32_t>& count,
    bool immediately, const std::function<void()>& onFinishEvent)
{
    CHECK_NULL_VOID(event);
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    bool usingSharedRuntime = container->GetSettings().usingSharedRuntime;
    if (usingSharedRuntime) {
        if (GetAnyContextIsLayouting(pipelineContext)) {
            pipelineContext->GetTaskExecutor()->PostTask(
                [id = Container::CurrentIdSafely(), option, event, count, immediately]() mutable {
                    ContainerScope scope(id);
                    auto container = Container::CurrentSafely();
                    CHECK_NULL_VOID(container);
                    auto pipelineContext = container->GetPipelineContext();
                    CHECK_NULL_VOID(pipelineContext);
                    StartAnimationForStageMode(pipelineContext, option, event, count, immediately);
                },
                TaskExecutor::TaskType::UI, "ArkUIAnimateToForStageMode", PriorityType::IMMEDIATE);
            return;
        }
        StartAnimationForStageMode(pipelineContext, option, event, count, immediately);
    } else {
        StartAnimateToForFaMode(pipelineContext, option, event, count, immediately);
    }
}
void FillTraceStream(std::shared_ptr<std::stringstream>& traceStreamPtr, const AnimationOption& option)
{
    *traceStreamPtr << "AnimateTo, Options"
                    << " duration:" << option.GetDuration()
                    << ",iteration:" << option.GetIteration()
                    << ",delay:" << option.GetDelay()
                    << ",tempo:" << option.GetTempo()
                    << ",direction:" << (uint32_t) option.GetAnimationDirection()
                    << ",curve:" << (option.GetCurve() ? option.GetCurve()->ToString().c_str() : "");
}
void AnimateToInner(const Ark_AnimateParam* value,
                    const Callback_Void* event,
                    bool immediately)
{
    CHECK_NULL_VOID(value);
    auto currentId = Container::CurrentIdSafelyWithCheck();
    if (!CheckRunOnThreadByThreadId(currentId, true)) {
        auto localContainerId = ContainerScope::CurrentLocalId();
        if (localContainerId > 0 && CheckRunOnThreadByThreadId(localContainerId, false)) {
            currentId = localContainerId;
        }
    }
    ContainerScope scope(currentId);
    auto scopedDelegate = EngineHelper::GetCurrentDelegateSafely();
    CHECK_NULL_VOID(scopedDelegate);
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext == nullptr || (pipelineContext->IsFormAnimationFinishCallback() &&
        pipelineContext->IsFormRender() && GetFormAnimationTimeInterval(pipelineContext) > DEFAULT_DURATION)) {
        return;
    }
    std::function<void()> onFinishEvent;
    std::optional<int32_t> count;
    auto traceStreamPtr = std::make_shared<std::stringstream>();
    auto onFinish = Converter::OptConvert<Callback_Void>(value->onFinish);
    if (onFinish.has_value()) {
        count = GetAnimationFinishCount();
        onFinishEvent = [arkCallback = CallbackHelper(*onFinish),
                            id = Container::CurrentIdSafely(), traceStreamPtr, count]() mutable {
            RecordAnimationFinished(count.value_or(1));
            ContainerScope scope(id);
            arkCallback.Invoke();
            AceAsyncTraceEnd(0, traceStreamPtr->str().c_str(), true);
        };
    } else {
        onFinishEvent = [traceStreamPtr, count]() {
            RecordAnimationFinished(count.value_or(1));
            AceAsyncTraceEnd(0, traceStreamPtr->str().c_str(), true);
        };
    }
    AnimationOption option = Converter::Convert<AnimationOption>(*value);
    Validator::ValidateAnimationOption(option, pipelineContext->IsFormRender());
    option.SetOnFinishEvent(onFinishEvent);
    FillTraceStream(traceStreamPtr, option);
    AceAsyncTraceBegin(0, traceStreamPtr->str().c_str(), true);
    if (CheckIfSetFormAnimationDuration(pipelineContext, option)) {
        option.SetDuration(DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContext));
    }
    StartAnimateTo(option, event, count, immediately, onFinishEvent);
}
}
