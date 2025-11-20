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

#include "arkoala_api_generated.h"

#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/view_context/view_context_model_static.h"
#include "core/components_ng/pattern/view_context/view_context_model.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
constexpr uint32_t DEFAULT_DURATION = 1000; // ms
constexpr int64_t MICROSEC_TO_MILLISEC = 1000;
constexpr int32_t MAX_FLUSH_COUNT = 2;
int64_t GetFormAnimationTimeInterval(const RefPtr<PipelineBase>& pipelineContext)
{
    CHECK_NULL_RETURN(pipelineContext, 0);
    return (GetMicroTickCount() - pipelineContext->GetFormAnimationStartTime()) / MICROSEC_TO_MILLISEC;
}
void ConvertAnimateParam(std::optional<AnimationOption>& result, const Opt_AnimateParam& optParam, bool isForm)
{
    if (optParam.tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    const auto& src = optParam.value;
    // If the attribute does not exist, the default value is used.
    auto duration = Converter::OptConvert<int32_t>(src.duration).value_or(DEFAULT_DURATION);
    auto delay = Converter::OptConvert<int32_t>(src.delay).value_or(0);
    auto iterations = Converter::OptConvert<int32_t>(src.iterations).value_or(1);
    auto tempo = static_cast<double>(Converter::OptConvert<float>(src.tempo).value_or(1.0f));
    if (SystemProperties::GetRosenBackendEnabled() && NearZero(tempo)) {
        // set duration to 0 to disable animation.
        duration = 0;
    }
    auto direction = Converter::OptConvert<AnimationDirection>(src.playMode).value_or(AnimationDirection::NORMAL);
    auto finishCallbackType = Converter::OptConvert<FinishCallbackType>(src.finishCallbackType)
        .value_or(FinishCallbackType::REMOVED);
    auto curve = Converter::OptConvert<RefPtr<Curve>>(src.curve).value_or(Curves::EASE_IN_OUT);
    auto frameRateRange = Converter::OptConvert<RefPtr<FrameRateRange>>(src.expectedFrameRateRange)
        .value_or(AceType::MakeRefPtr<FrameRateRange>(0, 0, 0));

    // limit animation for ArkTS Form
    if (isForm) {
        if (duration > static_cast<int32_t>(DEFAULT_DURATION)) {
            duration = static_cast<int32_t>(DEFAULT_DURATION);
        }
        if (delay != 0) {
            delay = 0;
        }
        if (SystemProperties::IsFormAnimationLimited() && iterations != 1) {
            iterations = 1;
        }
        if (!NearEqual(tempo, 1.0)) {
            tempo = 1.0;
        }
    }
    result = AnimationOption();

    result->SetDuration(duration);
    result->SetDelay(delay);
    result->SetIteration(iterations);
    result->SetTempo(tempo);
    result->SetAnimationDirection(direction);
    result->SetFinishCallbackType(finishCallbackType);
    result->SetCurve(curve);
    result->SetFrameRateRange(frameRateRange);
}
void PrintAnimationInfo(const AnimationOption& option, AnimationInterface interface, const std::optional<int32_t>& cnt)
{
    auto animationInterfaceName = GetAnimationInterfaceName(interface);
    CHECK_NULL_VOID(animationInterfaceName);
    if (option.GetIteration() == ANIMATION_REPEAT_INFINITE) {
        if (interface == AnimationInterface::KEYFRAME_ANIMATE_TO) {
            TAG_LOGI(AceLogTag::ACE_ANIMATION,
                "keyframeAnimateTo iteration is infinite, remember to stop it. total duration:%{public}d",
                option.GetDuration());
        } else {
            TAG_LOGI(AceLogTag::ACE_ANIMATION,
                "%{public}s iteration is infinite. duration:%{public}d, curve:%{public}s",
                animationInterfaceName, option.GetDuration(), option.GetCurve()->ToString().c_str());
        }
        return;
    }
    if (cnt) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "%{public}s starts, [%{public}s], finish cnt:%{public}d",
            animationInterfaceName, option.ToString().c_str(), cnt.value());
    }
}
} // namespace
namespace AnimationExtenderAccessor {
void SetClipRectImpl(Ark_NativePointer node,
                     Ark_Float32 x,
                     Ark_Float32 y,
                     Ark_Float32 width,
                     Ark_Float32 height)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    renderContext->ClipWithRRect(RectF(x, y, width, height), RadiusF(EdgeF(0.0f, 0.0f)));
}

void AnimateToForStageMode(const RefPtr<PipelineBase>& pipelineContext, const AnimationOption& option,
    std::function<void()> jsAnimateToFunc, int32_t triggerId, const std::optional<int32_t>& count)
{
    pipelineContext->StartImplicitAnimation(option, option.GetCurve(), option.GetOnFinishEvent(), count);
    auto previousOption = pipelineContext->GetSyncAnimationOption();
    pipelineContext->SetSyncAnimationOption(option);
    // Execute the function.
    jsAnimateToFunc();
    pipelineContext->FlushOnceVsyncTask();
    AceEngine::Get().NotifyContainersOrderly([triggerId](const RefPtr<Container>& container) {
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
    std::function<void()> jsAnimateToFunc, const std::optional<int32_t>& count, bool immediately)
{
    auto triggerId = pipelineContext->GetInstanceId();
    ACE_SCOPED_TRACE("%s, instanceId:%d, finish cnt:%d", option.ToString().c_str(), triggerId, count.value_or(-1));
    NG::ScopedViewStackProcessor scopedProcessor;
    AceEngine::Get().NotifyContainersOrderly([triggerId](const RefPtr<Container>& container) {
        auto context = container->GetPipelineContext();
        ContainerScope scope(container->GetInstanceId());
        context->FlushBuild();
        if (context->GetInstanceId() == triggerId) {
            return;
        }
        context->PrepareOpenImplicitAnimation();
    });
    pipelineContext->PrepareOpenImplicitAnimation();
    if (!pipelineContext->CatchInteractiveAnimations([pipelineContext, option, jsAnimateToFunc, triggerId, count]() {
        AnimateToForStageMode(pipelineContext, option, jsAnimateToFunc, triggerId, count);
    })) {
        AnimateToForStageMode(pipelineContext, option, jsAnimateToFunc, triggerId, count);
    }
    pipelineContext->FlushAfterLayoutCallbackInImplicitAnimationTask();
    if (immediately) {
        pipelineContext->FlushModifier();
        pipelineContext->FlushMessages();
    } else {
        pipelineContext->RequestFrame();
    }
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
        auto context = container->GetPipelineContext();
        isLayouting |= context->IsLayouting();
    });
    return isLayouting;
}

void ExecuteSharedRuntimeAnimation(const RefPtr<Container>& container, const RefPtr<PipelineBase>& pipelineContextBase,
    const AnimationOption& option, std::function<void()> onEventFinish, const std::optional<int32_t>& count,
    bool immediately)
{
    if (GetAnyContextIsLayouting(pipelineContextBase)) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION,
            "Pipeline layouting, post animateTo, dur:%{public}d, curve:%{public}s",
            option.GetDuration(), option.GetCurve() ? option.GetCurve()->ToString().c_str() : "");
        pipelineContextBase->GetTaskExecutor()->PostTask(
            [id = Container::CurrentIdSafely(), option, func = std::move(onEventFinish), count, immediately]
            () mutable {
                ContainerScope scope(id);
                auto container = Container::CurrentSafely();
                CHECK_NULL_VOID(container);
                auto pipelineContext = container->GetPipelineContext();
                CHECK_NULL_VOID(pipelineContext);
                StartAnimationForStageMode(pipelineContext, option, func, count, immediately);
            },
            TaskExecutor::TaskType::UI, "ArkUIAnimateToForStageMode", PriorityType::IMMEDIATE);
        return;
    }
    StartAnimationForStageMode(pipelineContextBase, option, onEventFinish, count, true);
}

void AnimateToImmediatelyImplImpl(const Ark_AnimateParam* param,
                                  const synthetic_Callback_Void* event)
{
    std::function<void()> onEventFinish;
    if (event) {
        onEventFinish = [arkCallback = CallbackHelper(*event)]() {
            arkCallback.InvokeSync();
        };
    }

    auto currentId = Container::CurrentIdSafelyWithCheck();
    ContainerScope cope(currentId);
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContextBase = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContextBase);
    auto timeInterval = (GetMicroTickCount() - pipelineContextBase->GetFormAnimationStartTime()) / MICROSEC_TO_MILLISEC;
    if (pipelineContextBase->IsFormAnimationFinishCallback() && pipelineContextBase->IsFormRender() &&
        timeInterval > DEFAULT_DURATION) {
        TAG_LOGW(
            AceLogTag::ACE_FORM, "[Form animation] Form finish callback triggered animation cannot exceed 1000ms.");
        return;
    }

    AnimationOption option = Converter::Convert<AnimationOption>(*param);
    auto onFinish = Converter::OptConvert<Callback_Void>(param->onFinish);
    std::optional<int32_t> count;
    if (onFinish) {
        count = GetAnimationFinishCount();
        std::function<void()> onFinishEvent = [arkCallback = CallbackHelper(*onFinish), currentId]() mutable {
            ContainerScope scope(currentId);
            arkCallback.InvokeSync();
        };
        option.SetOnFinishEvent(onFinishEvent);
    }

    ExecuteSharedRuntimeAnimation(container, pipelineContextBase, option, onEventFinish, count, true);
}
void OpenImplicitAnimationImpl(const Ark_AnimateParam* param)
{
    auto currentId = Container::CurrentIdSafelyWithCheck();
    ContainerScope cope(currentId);
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContextBase = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContextBase);
    auto timeInterval = (GetMicroTickCount() - pipelineContextBase->GetFormAnimationStartTime()) / MICROSEC_TO_MILLISEC;
    if (pipelineContextBase->IsFormAnimationFinishCallback() && pipelineContextBase->IsFormRender() &&
        timeInterval > DEFAULT_DURATION) {
        TAG_LOGW(
            AceLogTag::ACE_FORM, "[Form animation] Form finish callback triggered animation cannot exceed 1000ms.");
        return;
    }
    AnimationOption option = Converter::Convert<AnimationOption>(*param);
    if (pipelineContextBase->IsFormAnimationFinishCallback() && pipelineContextBase->IsFormRender() &&
            option.GetDuration() > (DEFAULT_DURATION - timeInterval)) {
        option.SetDuration(DEFAULT_DURATION - timeInterval);
        TAG_LOGW(AceLogTag::ACE_FORM, "[Form animation]  Form animation SetDuration: %{public}lld ms",
            static_cast<long long>(DEFAULT_DURATION - timeInterval));
    }
    auto onFinish = Converter::OptConvert<Callback_Void>(param->onFinish);
    std::function<void()> onFinishEvent = [arkCallback = CallbackHelper(*onFinish), currentId]() mutable {
        ContainerScope scope(currentId);
        arkCallback.InvokeSync();
    };
    option.SetOnFinishEvent(onFinishEvent);
    if (SystemProperties::GetRosenBackendEnabled()) {
        option.SetAllowRunningAsynchronously(true);
    }
#ifndef ARKUI_CAPI_UNITTEST
    ViewContextModel::GetInstance()->openAnimation(option);
#endif
}
void CloseImplicitAnimationImpl()
{
    auto currentId = Container::CurrentIdSafelyWithCheck();
    ContainerScope cope(currentId);
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContextBase = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContextBase);
    auto timeInterval = (GetMicroTickCount() - pipelineContextBase->GetFormAnimationStartTime()) / MICROSEC_TO_MILLISEC;
    if (pipelineContextBase->IsFormAnimationFinishCallback() && pipelineContextBase->IsFormRender() &&
        timeInterval > DEFAULT_DURATION) {
        TAG_LOGW(
            AceLogTag::ACE_FORM, "[Form animation] Form finish callback triggered animation cannot exceed 1000ms.");
        return;
    }
#ifndef ARKUI_CAPI_UNITTEST
    AnimationOption option;
    ViewContextModel::GetInstance()->closeAnimation(option, true);
#endif
}
void OpenImplicitAnimationForAnimationImpl(Ark_NativePointer node,
                                           const Opt_AnimateParam* param)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode && param);
    ACE_SCOPED_TRACE("animationStart node[%d]", frameNode->GetId());
    auto container = Container::CurrentSafelyWithCheck();
    CHECK_NULL_VOID(container);
    auto pipelineContextBase = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContextBase);
    if (pipelineContextBase->IsFormAnimationFinishCallback() &&
        pipelineContextBase->IsFormRenderExceptDynamicComponent() &&
        GetFormAnimationTimeInterval(pipelineContextBase) > DEFAULT_DURATION) {
        TAG_LOGW(
            AceLogTag::ACE_FORM, "[Form animation] Form finish callback triggered animation cannot exceed 1000ms.");
        return;
    }
    std::optional<AnimationOption> option;
    ConvertAnimateParam(option, *param, pipelineContextBase->IsFormRenderExceptDynamicComponent());
    if (option == std::nullopt) {
        ViewContextModelStatic::OpenAnimation(frameNode, std::nullopt);
        return;
    }
    if (pipelineContextBase->IsFormAnimationFinishCallback() &&
        pipelineContextBase->IsFormRenderExceptDynamicComponent() &&
        option->GetDuration() > (DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase))) {
        option->SetDuration(DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase));
        TAG_LOGW(AceLogTag::ACE_FORM, "[Form animation]  Form animation SetDuration: %{public}lld ms",
            static_cast<long long>(DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase)));
    }
    auto arkParam = param->value; // previous check has insured param is not undefined.
    auto onFinish = Converter::OptConvert<Callback_Void>(arkParam.onFinish);
    if (onFinish) {
        auto weakNode = AceType::WeakClaim(frameNode);
        std::function<void()> onFinishEvent = [arkCallback = CallbackHelper(*onFinish),
                                                  currentId = container->GetInstanceId(), weakNode]() {
            ContainerScope scope(currentId);
            auto pipelineContext = PipelineContext::GetCurrentContextSafely();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(weakNode);
            arkCallback.InvokeSync();
        };
        option->SetOnFinishEvent(onFinishEvent);
    }
    option->SetAllowRunningAsynchronously(true);
    PrintAnimationInfo(*option, AnimationInterface::ANIMATION, std::nullopt);
    option->SetAnimationInterface(AnimationInterface::ANIMATION);
    AceScopedTrace paramTrace("%s", option->ToString().c_str());
    ViewContextModelStatic::OpenAnimation(frameNode, option);
}
void CloseImplicitAnimationForAnimationImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ACE_SCOPED_TRACE("animationStop node[%d]", frameNode->GetId());
    ViewContextModelStatic::CloseAnimation(frameNode);
}
void StartDoubleAnimationImpl(Ark_NativePointer node,
                              const Ark_DoubleAnimationParam* param)
{
    auto* frameNode = AceType::DynamicCast<FrameNode>(reinterpret_cast<UINode*>(node));
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(param);

    auto curve = Converter::OptConvert<RefPtr<Curve>>(param->curve).value_or(Framework::CreateCurve(-1, true));
    auto duration = Converter::Convert<int32_t>(param->duration);
    auto delay = Converter::Convert<int32_t>(param->delay);
    auto propertyName = Converter::Convert<std::string>(param->propertyName);
    auto startValue = Converter::Convert<float>(param->startValue);
    auto endValue = Converter::Convert<float>(param->endValue);

    auto progressFunction = Converter::OptConvert<Callback_Extender_OnProgress>(param->onProgress);
    if (progressFunction) {
        auto progressCallbackFn = [cb = CallbackHelper(progressFunction.value())](float progress) {
            cb.Invoke(static_cast<Ark_Float32>(progress));
        };

        frameNode->CreateAnimatablePropertyFloat(propertyName, startValue, progressCallbackFn);
        progressCallbackFn(startValue);
    }

    AnimationOption option(curve, duration);
    option.SetDelay(delay);

    auto finishFunction = Converter::OptConvert<Callback_Extender_OnFinish>(param->onFinish);
    if (finishFunction) {
        auto finishCallbackFn = [cb = CallbackHelper(finishFunction.value()), frameNode, propertyName]() {
            frameNode->DeleteAnimatablePropertyFloat(propertyName);
            cb.Invoke();
        };

        AnimationUtils::OpenImplicitAnimation(option, option.GetCurve(), finishCallbackFn);
    } else {
        AnimationUtils::OpenImplicitAnimation(option, option.GetCurve(), nullptr);
    }

    frameNode->UpdateAnimatablePropertyFloat(propertyName, endValue);
    AnimationUtils::CloseImplicitAnimation();
}
void AnimationTranslateImpl(Ark_NativePointer node,
                            const Ark_TranslateOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);

    TranslateOptions translateOptions = Converter::Convert<TranslateOptions>(*options);

    if (translateOptions.x.Unit() == DimensionUnit::PERCENT) {
        translateOptions.x = Dimension(
            translateOptions.x.Value() * frameNode->GetGeometryNode()->GetMarginFrameOffset().GetX(),
            DimensionUnit::PX);
    }

    if (translateOptions.y.Unit() == DimensionUnit::PERCENT) {
        translateOptions.x = Dimension(
            translateOptions.y.Value() * frameNode->GetGeometryNode()->GetMarginFrameOffset().GetY(),
            DimensionUnit::PX);
    }

    ViewAbstract::SetTranslate(frameNode, translateOptions);
}

struct Keyframe {
    int32_t duration = 0;
    RefPtr<Curve> curve;
    std::function<void()> animationClosure;
};

void FlushDirtyNodesWhenExist(const RefPtr<PipelineBase>& pipelineContext,
    const AnimationOption& option, const std::optional<int32_t>& count, AnimationInterface interface)
{
    auto animationInterfaceName = GetAnimationInterfaceName(interface);
    CHECK_NULL_VOID(animationInterfaceName);
    int32_t flushCount = 0;
    bool isDirtyNodesEmpty = pipelineContext->IsDirtyNodesEmpty();
    bool isDirtyLayoutNodesEmpty = pipelineContext->IsDirtyLayoutNodesEmpty();
    while (!isDirtyNodesEmpty || (!isDirtyLayoutNodesEmpty && !pipelineContext->IsLayouting())) {
        if (flushCount >= MAX_FLUSH_COUNT || option.GetIteration() != ANIMATION_REPEAT_INFINITE) {
            TAG_LOGD(AceLogTag::ACE_ANIMATION, "%{public}s, option:%{public}s, finish cnt:%{public}d,"
                "dirtyNodes is empty:%{public}d, dirtyLayoutNodes is empty:%{public}d",
                animationInterfaceName, option.ToString().c_str(), count.value_or(-1),
                isDirtyNodesEmpty, isDirtyLayoutNodesEmpty);
            break;
        }
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

void StartKeyframeAnimation(const RefPtr<PipelineBase>& pipelineContext, AnimationOption& overallAnimationOption,
    std::vector<Keyframe>& keyframes, const std::optional<int32_t>& count)
{
    // flush build and flush ui tasks before open animation closure.
    pipelineContext->FlushBuild();
    if (!pipelineContext->IsLayouting()) {
        pipelineContext->FlushUITasks(true);
    }

    // flush build when exist dirty nodes, flush ui tasks when exist dirty layout nodes.
    FlushDirtyNodesWhenExist(pipelineContext,
        overallAnimationOption, count, AnimationInterface::KEYFRAME_ANIMATE_TO);

    // start KeyframeAnimation.
    pipelineContext->StartImplicitAnimation(
        overallAnimationOption, overallAnimationOption.GetCurve(), overallAnimationOption.GetOnFinishEvent(), count);
    for (auto& keyframe : keyframes) {
        if (!keyframe.animationClosure) {
            continue;
        }
        AceTraceBeginWithArgs("keyframe duration%d", keyframe.duration);
        AnimationUtils::AddDurationKeyFrame(keyframe.duration, keyframe.curve, [&keyframe, &pipelineContext]() {
            keyframe.animationClosure();
            pipelineContext->FlushBuild();
            if (!pipelineContext->IsLayouting()) {
                pipelineContext->FlushUITasks(true);
            } else {
                TAG_LOGI(AceLogTag::ACE_ANIMATION, "isLayouting, maybe some layout keyframe animation not generated");
            }
        });
        AceTraceEnd();
    }

    // close KeyframeAnimation.
    AnimationUtils::CloseImplicitAnimation();
}
void KeyframeAnimationImplImpl(const Ark_KeyframeAnimateParam* param,
                               const Array_KeyframeState* keyframes)
{
    auto scopedDelegate = Container::CurrentIdSafelyWithCheck();
    if (!scopedDelegate) {
        return;
    }
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto timeInterval = (GetMicroTickCount() - pipelineContext->GetFormAnimationStartTime()) / MICROSEC_TO_MILLISEC;
    AnimationOption option;
    std::optional<int32_t> count;
    int32_t delay = 0;
    int32_t iterations = 1;
    if (param) {
        delay = Converter::OptConvert<int32_t>(param->delay).value_or(0);
        iterations = Converter::OptConvert<int32_t>(param->iterations).value_or(1);
    }
    option.SetDelay(delay);
    option.SetIteration(iterations);
    if (param && param->onFinish.tag != INTEROP_TAG_UNDEFINED) {
        count = GetAnimationFinishCount();
        auto onFinishEvent = [arkCallback = CallbackHelper(param->onFinish.value),
                                 currentId = Container::CurrentIdSafely()]() mutable {
            ContainerScope scope(currentId);
            arkCallback.InvokeSync();
        };
        option.SetOnFinishEvent(onFinishEvent);
    }
    std::vector<Keyframe> parsedKeyframes;
    int32_t totalDuration = 0;
    if (keyframes && keyframes->array) {
        for (int i = 0; i < keyframes->length; ++i) {
            const auto& arkFrame = keyframes->array[i];
            Keyframe keyframe;
            keyframe.duration = Converter::OptConvert<int32_t>(arkFrame.duration).value_or(DEFAULT_DURATION);
            if (keyframe.duration < 0) {
                keyframe.duration = 0;
            }
            totalDuration += keyframe.duration;
            keyframe.curve = Converter::OptConvert<RefPtr<Curve>>(arkFrame.curve).value_or(Curves::EASE_IN_OUT);
            keyframe.animationClosure = [arkCallback = CallbackHelper(arkFrame.event),
                                            currentId = Container::CurrentIdSafely()]() {
                ContainerScope scope(currentId);
                arkCallback.InvokeSync();
            };

            parsedKeyframes.emplace_back(std::move(keyframe));
        }
    }
    option.SetDuration(totalDuration);
    option.SetCurve(Curves::EASE_IN_OUT);
    StartKeyframeAnimation(pipelineContext, option, parsedKeyframes, count);
    pipelineContext->FlushAfterLayoutCallbackInImplicitAnimationTask();
}
} // AnimationExtenderAccessor
const GENERATED_ArkUIAnimationExtenderAccessor* GetAnimationExtenderAccessor()
{
    static const GENERATED_ArkUIAnimationExtenderAccessor AnimationExtenderAccessorImpl {
        AnimationExtenderAccessor::SetClipRectImpl,
        AnimationExtenderAccessor::OpenImplicitAnimationImpl,
        AnimationExtenderAccessor::CloseImplicitAnimationImpl,
        AnimationExtenderAccessor::OpenImplicitAnimationForAnimationImpl,
        AnimationExtenderAccessor::CloseImplicitAnimationForAnimationImpl,
        AnimationExtenderAccessor::StartDoubleAnimationImpl,
        AnimationExtenderAccessor::AnimationTranslateImpl,
        AnimationExtenderAccessor::AnimateToImmediatelyImplImpl,
        AnimationExtenderAccessor::KeyframeAnimationImplImpl,
    };
    return &AnimationExtenderAccessorImpl;
}

}
