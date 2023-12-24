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

#include "bridge/declarative_frontend/jsview/js_view_context.h"

#include <functional>
#include <memory>
#include <sstream>

#include "base/log/ace_trace.h"
#include "base/log/jank_frame_report.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/models/view_context_model_impl.h"
#include "core/common/ace_engine.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/view_context/view_context_model_ng.h"

#ifdef USE_ARK_ENGINE
#include "bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#endif

namespace OHOS::Ace {

std::unique_ptr<ViewContextModel> ViewContextModel::instance_ = nullptr;
std::mutex ViewContextModel::mutex_;

ViewContextModel* ViewContextModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::ViewContextModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::ViewContextModelNG());
            } else {
                instance_.reset(new Framework::ViewContextModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {

constexpr uint32_t DEFAULT_DURATION = 1000; // ms
constexpr int64_t MICROSEC_TO_MILLISEC = 1000;

void AnimateToForStageMode(const RefPtr<PipelineBase>& pipelineContext, AnimationOption& option,
    JSRef<JSFunc> jsAnimateToFunc, std::function<void()>& onFinishEvent, bool immediately)
{
    auto triggerId = Container::CurrentId();
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
    pipelineContext->OpenImplicitAnimation(option, option.GetCurve(), onFinishEvent);
    pipelineContext->SetSyncAnimationOption(option);
    // Execute the function.
    jsAnimateToFunc->Call(jsAnimateToFunc);
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
    pipelineContext->SetSyncAnimationOption(AnimationOption());
    pipelineContext->CloseImplicitAnimation();
    if (immediately) {
        pipelineContext->FlushMessages();
    }
}

void AnimateToForFaMode(const RefPtr<PipelineBase>& pipelineContext, AnimationOption& option,
    const JSCallbackInfo& info, std::function<void()>& onFinishEvent, bool immediately)
{
    pipelineContext->FlushBuild();
    pipelineContext->OpenImplicitAnimation(option, option.GetCurve(), onFinishEvent);
    pipelineContext->SetSyncAnimationOption(option);
    JSRef<JSFunc> jsAnimateToFunc = JSRef<JSFunc>::Cast(info[1]);
    jsAnimateToFunc->Call(info[1]);
    pipelineContext->FlushBuild();
    pipelineContext->SetSyncAnimationOption(AnimationOption());
    pipelineContext->CloseImplicitAnimation();
    if (immediately) {
        pipelineContext->FlushMessages();
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

std::function<float(float)> ParseCallBackFunction(const JSRef<JSObject>& curveObj)
{
    std::function<float(float)> customCallBack = nullptr;
    JSRef<JSVal> onCallBack = curveObj->GetProperty("__curveCustomFunc");
    if (onCallBack->IsFunction()) {
        WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        RefPtr<JsFunction> jsFuncCallBack =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onCallBack));
        customCallBack = [func = std::move(jsFuncCallBack), id = Container::CurrentId(), node = frameNode](
                             float time) -> float {
            ContainerScope scope(id);
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_RETURN(pipelineContext, 1.0f);
            pipelineContext->UpdateCurrentActiveNode(node);
            JSRef<JSVal> params[1];
            params[0] = JSRef<JSVal>::Make(ToJSValue(time));
            auto result = func->ExecuteJS(1, params);
            return result->IsNumber() ? result->ToNumber<float>() : 1.0f;
        };
    }
    return customCallBack;
}

struct KeyframeParam {
    int32_t duration = 0;
    float fraction = 0.0f;
    RefPtr<Curve> curve;
    std::function<void()> animationClosure;
};

AnimationOption ParseKeyframeOverallParam(const JSExecutionContext& executionContext, const JSRef<JSObject>& obj)
{
    JSRef<JSVal> onFinish = obj->GetProperty("onFinish");
    AnimationOption option;
    if (onFinish->IsFunction()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onFinish));
        std::function<void()> onFinishEvent = [execCtx = executionContext, func = std::move(jsFunc),
                            id = Container::CurrentId()]() mutable {
            CHECK_NULL_VOID(func);
            ContainerScope scope(id);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute();
            func = nullptr;
        };
        option.SetOnFinishEvent(onFinishEvent);
    }
    auto delay = obj->GetPropertyValue<int32_t>("delay", 0);
    auto iterations = obj->GetPropertyValue<int32_t>("iterations", 1);
    option.SetDelay(delay);
    option.SetIteration(iterations);
    return option;
}

std::vector<KeyframeParam> ParseKeyframes(const JSExecutionContext& executionContext, const JSRef<JSArray>& arr)
{
    std::vector<KeyframeParam> params;
    for (size_t index = 0; index != arr->Length(); ++index) {
        if (!arr->GetValueAt(index)->IsObject()) {
            continue;
        }
        auto info = JSRef<JSObject>::Cast(arr->GetValueAt(index));
        KeyframeParam param;

        auto jsEventValue = info->GetProperty("event");
        if (!jsEventValue->IsFunction()) {
            continue;
        }
        param.duration = info->GetPropertyValue<int32_t>("duration", DEFAULT_DURATION);
        if (param.duration < 0) {
            param.duration = 0;
        }
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(jsEventValue));
        param.animationClosure = [execCtx = executionContext, func = std::move(jsFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute();
        };
        auto curveArgs = info->GetProperty("curve");
        param.curve = JSViewContext::ParseCurve(curveArgs, true);
        params.emplace_back(param);
    }
    return params;
}
} // namespace

RefPtr<Curve> JSViewContext::ParseCurve(const JSRef<JSVal>& curveArgs, bool exceptSpring)
{
    RefPtr<Curve> curve;
    if (curveArgs->IsString()) {
        auto curveString = curveArgs->ToString();
        if (exceptSpring) {
            curve = CreateCurveExceptSpring(curveString);
        } else {
            curve = CreateCurve(curveString);
        }
    } else if (curveArgs->IsObject()) {
        JSRef<JSObject> curveObject = JSRef<JSObject>::Cast(curveArgs);
        JSRef<JSVal> curveString = curveObject->GetProperty("__curveString");
        if (!curveString->IsString()) {
            return Curves::EASE_IN_OUT;
        }
        auto aniTimFunc = curveString->ToString();
        std::string customFuncName(DOM_ANIMATION_TIMING_FUNCTION_CUSTOM);
        if (aniTimFunc == customFuncName) {
            auto customCurveFunc = ParseCallBackFunction(curveObject);
            curve = CreateCurve(customCurveFunc);
        } else if (exceptSpring) {
            curve = CreateCurveExceptSpring(aniTimFunc);
        } else {
            curve = CreateCurve(aniTimFunc);
        }
    } else {
        curve = Curves::EASE_IN_OUT;
    }
    return curve;
}

const AnimationOption JSViewContext::CreateAnimation(const JSRef<JSObject>& animationArgs, bool isForm)
{
    AnimationOption option;
    // If the attribute does not exist, the default value is used.
    auto duration = animationArgs->GetPropertyValue<int32_t>("duration", DEFAULT_DURATION);
    auto delay = animationArgs->GetPropertyValue<int32_t>("delay", 0);
    auto iterations = animationArgs->GetPropertyValue<int32_t>("iterations", 1);
    auto tempo = animationArgs->GetPropertyValue<double>("tempo", 1.0);
    if (SystemProperties::GetRosenBackendEnabled() && NearZero(tempo)) {
        // set duration to 0 to disable animation.
        duration = 0;
    }
    auto direction = StringToAnimationDirection(animationArgs->GetPropertyValue<std::string>("playMode", "normal"));
    auto finishCallbackType = static_cast<FinishCallbackType>(
        animationArgs->GetPropertyValue<int32_t>("finishCallbackType", 0));
    auto curve = ParseCurve(animationArgs->GetProperty("curve"));

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

    int32_t fRRmin = 0;
    int32_t fRRmax = 0;
    int32_t fRRExpected = 0;
    JSRef<JSVal> rateRangeObjectArgs = animationArgs->GetProperty("expectedFrameRateRange");
    if (rateRangeObjectArgs->IsObject()) {
        JSRef<JSObject> rateRangeObj = JSRef<JSObject>::Cast(rateRangeObjectArgs);
        fRRmin = rateRangeObj->GetPropertyValue<int32_t>("min", -1);
        fRRmax = rateRangeObj->GetPropertyValue<int32_t>("max", -1);
        fRRExpected = rateRangeObj->GetPropertyValue<int32_t>("expected", -1);
    }
    RefPtr<FrameRateRange> frameRateRange = AceType::MakeRefPtr<FrameRateRange>(fRRmin, fRRmax, fRRExpected);

    option.SetDuration(duration);
    option.SetDelay(delay);
    option.SetIteration(iterations);
    option.SetTempo(tempo);
    option.SetAnimationDirection(direction);
    option.SetCurve(curve);
    option.SetFinishCallbackType(finishCallbackType);
    option.SetFrameRateRange(frameRateRange);
    return option;
}

void JSViewContext::JSAnimation(const JSCallbackInfo& info)
{
    ACE_FUNCTION_TRACE();
    auto scopedDelegate = EngineHelper::GetCurrentDelegate();
    if (!scopedDelegate) {
        // this case usually means there is no foreground container, need to figure out the reason.
        return;
    }
    if (ViewStackModel::GetInstance()->CheckTopNodeFirstBuilding()) {
        // the node sets attribute value for the first time. No animation is generated.
        return;
    }
    AnimationOption option = AnimationOption();
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContextBase = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContextBase);
    if (pipelineContextBase->IsFormAnimationFinishCallback() && pipelineContextBase->IsFormRender() &&
        GetFormAnimationTimeInterval(pipelineContextBase) > DEFAULT_DURATION) {
        TAG_LOGW(
            AceLogTag::ACE_FORM, "[Form animation] Form finish callback triggered animation cannot exceed 1000ms.");
        return;
    }
    if (info[0]->IsNull() || !info[0]->IsObject()) {
        ViewContextModel::GetInstance()->closeAnimation(option, true);
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> onFinish = obj->GetProperty("onFinish");
    std::function<void()> onFinishEvent;
    if (onFinish->IsFunction()) {
        WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onFinish));
        onFinishEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
                            id = Container::CurrentId(), node = frameNode]() mutable {
            CHECK_NULL_VOID(func);
            ContainerScope scope(id);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            func->Execute();
            func = nullptr;
        };
    }

    option = CreateAnimation(obj, pipelineContextBase->IsFormRender());
    if (pipelineContextBase->IsFormAnimationFinishCallback() && pipelineContextBase->IsFormRender() &&
        option.GetDuration() > (DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase))) {
        option.SetDuration(DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase));
        TAG_LOGW(AceLogTag::ACE_FORM, "[Form animation]  Form animation SetDuration: %{public}lld ms",
            static_cast<long long>(DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContextBase)));
    }

    option.SetOnFinishEvent(onFinishEvent);
    if (SystemProperties::GetRosenBackendEnabled()) {
        option.SetAllowRunningAsynchronously(true);
    }
    ViewContextModel::GetInstance()->openAnimation(option);
    JankFrameReport::GetInstance().ReportJSAnimation();
}

void JSViewContext::JSAnimateTo(const JSCallbackInfo& info)
{
    ACE_FUNCTION_TRACE();
    AnimateToInner(info, false);
}

void JSViewContext::JSAnimateToImmediately(const JSCallbackInfo& info)
{
    ACE_FUNCTION_TRACE();
    AnimateToInner(info, true);
}

void JSViewContext::AnimateToInner(const JSCallbackInfo& info, bool immediately)
{
    auto scopedDelegate = EngineHelper::GetCurrentDelegate();
    if (!scopedDelegate) {
        // this case usually means there is no foreground container, need to figure out the reason.
        return;
    }
    if (info.Length() < 2) {
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }
    // 2nd argument should be a closure passed to the animateTo function.
    if (!info[1]->IsFunction()) {
        return;
    }

    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    if (pipelineContext->IsFormAnimationFinishCallback() && pipelineContext->IsFormRender() &&
        GetFormAnimationTimeInterval(pipelineContext) > DEFAULT_DURATION) {
        TAG_LOGW(
            AceLogTag::ACE_FORM, "[Form animation] Form finish callback triggered animation cannot exceed 1000ms.");
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> onFinish = obj->GetProperty("onFinish");
    std::function<void()> onFinishEvent;
    auto traceStreamPtr = std::make_shared<std::stringstream>();
    if (onFinish->IsFunction()) {
        WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onFinish));
        onFinishEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
                            id = Container::CurrentId(), traceStreamPtr, node = frameNode]() mutable {
            CHECK_NULL_VOID(func);
            ContainerScope scope(id);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            func->Execute();
            func = nullptr;
            AceAsyncTraceEnd(0, traceStreamPtr->str().c_str(), true);
        };
    } else {
        onFinishEvent = [traceStreamPtr]() {
            AceAsyncTraceEnd(0, traceStreamPtr->str().c_str(), true);
        };
    }

    AnimationOption option = CreateAnimation(obj, pipelineContext->IsFormRender());
    *traceStreamPtr << "AnimateTo, Options"
                    << " duration:" << option.GetDuration()
                    << ",iteration:" << option.GetIteration()
                    << ",delay:" << option.GetDelay()
                    << ",tempo:" << option.GetTempo()
                    << ",direction:" << (uint32_t) option.GetAnimationDirection()
                    << ",curve:" << (option.GetCurve() ? option.GetCurve()->ToString().c_str() : "");
    AceAsyncTraceBegin(0, traceStreamPtr->str().c_str(), true);
    if (CheckIfSetFormAnimationDuration(pipelineContext, option)) {
        option.SetDuration(DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContext));
        TAG_LOGW(AceLogTag::ACE_FORM, "[Form animation]  Form animation SetDuration: %{public}lld ms",
            static_cast<long long>(DEFAULT_DURATION - GetFormAnimationTimeInterval(pipelineContext)));
    }
    if (SystemProperties::GetRosenBackendEnabled()) {
        bool usingSharedRuntime = container->GetSettings().usingSharedRuntime;
        if (usingSharedRuntime) {
            if (pipelineContext->IsLayouting()) {
                TAG_LOGW(AceLogTag::ACE_ANIMATION,
                    "pipeline is layouting, post animateTo, duration:%{public}d, curve:%{public}s",
                    option.GetDuration(), option.GetCurve() ? option.GetCurve()->ToString().c_str() : "");
                pipelineContext->GetTaskExecutor()->PostTask(
                    [id = Container::CurrentId(), option, func = JSRef<JSFunc>::Cast(info[1]),
                        onFinishEvent, immediately]() mutable {
                        ContainerScope scope(id);
                        auto container = Container::Current();
                        CHECK_NULL_VOID(container);
                        auto pipelineContext = container->GetPipelineContext();
                        CHECK_NULL_VOID(pipelineContext);
                        AnimateToForStageMode(pipelineContext, option, func, onFinishEvent, immediately);
                    },
                    TaskExecutor::TaskType::UI);
                return;
            }
            AnimateToForStageMode(pipelineContext, option, JSRef<JSFunc>::Cast(info[1]), onFinishEvent, immediately);
        } else {
            AnimateToForFaMode(pipelineContext, option, info, onFinishEvent, immediately);
        }
    } else {
        pipelineContext->FlushBuild();
        pipelineContext->SaveExplicitAnimationOption(option);
        // Execute the function.
        JSRef<JSFunc> jsAnimateToFunc = JSRef<JSFunc>::Cast(info[1]);
        jsAnimateToFunc->Call(info[1]);
        pipelineContext->FlushBuild();
        pipelineContext->CreateExplicitAnimator(onFinishEvent);
        pipelineContext->ClearExplicitAnimationOption();
    }
}

void JSViewContext::JSKeyframeAnimateTo(const JSCallbackInfo& info)
{
    ACE_FUNCTION_TRACE();
    auto scopedDelegate = EngineHelper::GetCurrentDelegate();
    if (!scopedDelegate) {
        // this case usually means there is no foreground container, need to figure out the reason.
        return;
    }
    if (info.Length() < 2) {
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }
    if (!info[1]->IsArray()) {
        return;
    }
    JSRef<JSArray> keyframeArr = JSRef<JSArray>::Cast(info[1]);
    if (keyframeArr->Length() == 0) {
        return;
    }

    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    auto overallAnimationOption = ParseKeyframeOverallParam(info.GetExecutionContext(), obj);
    auto keyframes = ParseKeyframes(info.GetExecutionContext(), keyframeArr);
    int32_t totalDuration = 0;
    for (const auto& keyframe : keyframes) {
        totalDuration += keyframe.duration;
    }
    overallAnimationOption.SetDuration(totalDuration);
    // actual curve is in keyframe, this curve will not be effective
    overallAnimationOption.SetCurve(Curves::EASE_IN_OUT);
    int32_t currentDuration = 0;
    for (auto& keyframe : keyframes) {
        currentDuration += keyframe.duration;
        keyframe.fraction = totalDuration > 0 ? static_cast<float>(currentDuration) / totalDuration : 1.0f;
    }
    pipelineContext->FlushBuild();
    pipelineContext->OpenImplicitAnimation(
        overallAnimationOption, overallAnimationOption.GetCurve(), overallAnimationOption.GetOnFinishEvent());
    for (auto& keyframe : keyframes) {
        if (!keyframe.animationClosure) {
            continue;
        }
        AceTraceBeginWithArgs("keyframe %f", keyframe.fraction);
        AnimationUtils::AddKeyFrame(keyframe.fraction, keyframe.curve, [&keyframe, &pipelineContext]() {
            keyframe.animationClosure();
            pipelineContext->FlushBuild();
            if (!pipelineContext->IsLayouting()) {
                pipelineContext->FlushUITasks();
            } else {
                TAG_LOGI(AceLogTag::ACE_ANIMATION, "isLayouting, maybe some layout keyframe animation not generated");
            }
        });
        AceTraceEnd();
    }
    pipelineContext->CloseImplicitAnimation();
}

void JSViewContext::JSBind(BindingTarget globalObj)
{
    JSClass<JSViewContext>::Declare("Context");
    JSClass<JSViewContext>::StaticMethod("animation", JSAnimation);
    JSClass<JSViewContext>::StaticMethod("animateTo", JSAnimateTo);
    JSClass<JSViewContext>::StaticMethod("animateToImmediately", JSAnimateToImmediately);
    JSClass<JSViewContext>::StaticMethod("keyframeAnimateTo", JSKeyframeAnimateTo);
    JSClass<JSViewContext>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
