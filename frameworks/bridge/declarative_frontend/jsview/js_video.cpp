/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_video.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_video_controller.h"
#include "bridge/declarative_frontend/jsview/models/video_model_impl.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/video/video_model_ng.h"
#ifdef SUPPORT_JSSTACK
#include "xpower_event_jsvm.h"
#endif

namespace OHOS::Ace {
VideoModel* VideoModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::VideoModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::VideoModelNG instance;
        return &instance;
    } else {
        static Framework::VideoModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSVideo::Create(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    JSRef<JSObject> videoObj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> srcValue = videoObj->GetProperty("src");
    JSRef<JSVal> previewUriValue = videoObj->GetProperty("previewUri");
    JSRef<JSVal> currentProgressRateValue = videoObj->GetProperty("currentProgressRate");

    auto controllerObj = videoObj->GetProperty("controller");
    RefPtr<VideoControllerV2> videoController = nullptr;
    if (controllerObj->IsObject()) {
        auto* jsVideoController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSVideoController>();
        if (jsVideoController) {
            jsVideoController->SetInstanceId(Container::CurrentId());
            videoController = jsVideoController->GetController();
        }
    }
    VideoModel::GetInstance()->Create(videoController);

    // Parse the src, if it is invalid, use the empty string.
    std::string bundleNameSrc;
    std::string moduleNameSrc;
    std::string src;
    int32_t resId = 0;
    ParseJsMediaWithBundleName(srcValue, src, bundleNameSrc, moduleNameSrc, resId);
    VideoModel::GetInstance()->SetSrc(src, bundleNameSrc, moduleNameSrc);

    // Parse the rate, if it is invalid, set it as 1.0.
    double currentProgressRate = 1.0;
    ParseJsDouble(currentProgressRateValue, currentProgressRate);
    VideoModel::GetInstance()->SetProgressRate(currentProgressRate);

    auto aiOptions = videoObj->GetProperty("imageAIOptions");
    if (aiOptions->IsObject()) {
        auto engine = EngineHelper::GetCurrentEngine();
        CHECK_NULL_VOID(engine);
        NativeEngine* nativeEngine = engine->GetNativeEngine();
        CHECK_NULL_VOID(nativeEngine);
        panda::Local<JsiValue> value = aiOptions.Get().GetLocalHandle();
        JSValueWrapper valueWrapper = value;
        ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
        napi_value optionsValue = nativeEngine->ValueToNapiValue(valueWrapper);
        VideoModel::GetInstance()->SetImageAIOptions(optionsValue);
    }

    std::string previewUri;
    std::string bundleName;
    std::string moduleName;
    GetJsMediaBundleInfo(previewUriValue, bundleName, moduleName);
    if (previewUriValue->IsUndefined() || previewUriValue->IsNull()) {
        // When it is undefined, just set the empty image.
        VideoModel::GetInstance()->SetPosterSourceInfo(previewUri, "", "");
        return;
    }
    auto noPixMap = ParseJsMedia(previewUriValue, previewUri);
    if (noPixMap) {
        // Src is a string or resource
        VideoModel::GetInstance()->SetPosterSourceInfo(previewUri, bundleName, moduleName);
    } else {
        // Src is a pixelmap.
#if defined(PIXEL_MAP_SUPPORTED)
        RefPtr<PixelMap> pixMap = CreatePixelMapFromNapiValue(previewUriValue);
        VideoModel::GetInstance()->SetPosterSourceByPixelMap(pixMap);
#endif
    }
}

void JSVideo::JsMuted(const JSCallbackInfo& info)
{
    bool muted = false;
    if (info[0]->IsBoolean()) {
        muted = info[0]->ToBoolean();
#ifdef SUPPORT_JSSTACK
        HiviewDFX::ReportXPowerJsStackSysEvent(info.GetVm(), "VOLUME_CHANGE", "SRC=Video");
#endif
    }
    VideoModel::GetInstance()->SetMuted(muted);
}

void JSVideo::JsAutoPlay(const JSCallbackInfo& info)
{
    bool autoPlay = false;
    if (info[0]->IsBoolean()) {
        autoPlay = info[0]->ToBoolean();
#ifdef SUPPORT_JSSTACK
        HiviewDFX::ReportXPowerJsStackSysEvent(info.GetVm(), "STREAM_CHANGE", "SRC=Video");
#endif
    }
    VideoModel::GetInstance()->SetAutoPlay(autoPlay);
}

void JSVideo::JsControls(const JSCallbackInfo& info)
{
    bool controls = true;
    if (info[0]->IsBoolean()) {
        controls = info[0]->ToBoolean();
    }
    VideoModel::GetInstance()->SetControls(controls);
}

void JSVideo::JsLoop(const JSCallbackInfo& info)
{
    bool loop = false;
    if (info[0]->IsBoolean()) {
        loop = info[0]->ToBoolean();
    }
    VideoModel::GetInstance()->SetLoop(loop);
}

void JSVideo::JsObjectFit(const JSCallbackInfo& info)
{
    ImageFit imageFit = ImageFit::COVER;
    // The default value of Imagefit is FILL, but in the video the default value is COVER.
    // So the default value need to be converted.
    if (info[0]->IsUndefined()) {
        VideoModel::GetInstance()->SetObjectFit(imageFit);
        return;
    }
    if (info[0]->IsNumber()) {
        imageFit = static_cast<ImageFit>(info[0]->ToNumber<int>());
    }
    VideoModel::GetInstance()->SetObjectFit(imageFit);
}

void JSVideo::JsOnStart(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onStart = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                       const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.onStart");
        PipelineContext::SetCallBackNode(node);
        std::vector<std::string> keys = { "start" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnStart(std::move(onStart));
}

void JSVideo::JsOnPause(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onPause = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                       const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.onPause");
        PipelineContext::SetCallBackNode(node);
        std::vector<std::string> keys = { "pause" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnPause(std::move(onPause));
}

void JSVideo::JsOnFinish(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onFinish = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                        const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.onFinish");
        PipelineContext::SetCallBackNode(node);
        std::vector<std::string> keys = { "finish" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnFinish(std::move(onFinish));
}

void JSVideo::JsOnStop(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onStop = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                        const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.onStop");
        PipelineContext::SetCallBackNode(node);
        std::vector<std::string> keys = { "stop" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnStop(std::move(onStop));
}

void JSVideo::JsOnFullscreenChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto OnFullScreenChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                                  const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.OnFullScreenChange");
        PipelineContext::SetCallBackNode(node);
        std::vector<std::string> keys = { "fullscreen" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnFullScreenChange(std::move(OnFullScreenChange));
}

void JSVideo::JsOnPrepared(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onPrepared = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                          const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.onPrepared");
        PipelineContext::SetCallBackNode(node);
        std::vector<std::string> keys = { "duration" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnPrepared(std::move(onPrepared));
}

void JSVideo::JsOnSeeking(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onSeeking = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                         const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.onSeeking");
        PipelineContext::SetCallBackNode(node);
        std::vector<std::string> keys = { "time" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnSeeking(std::move(onSeeking));
}

void JSVideo::JsOnSeeked(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onSeeked = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                        const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.onSeeked");
        PipelineContext::SetCallBackNode(node);
        std::vector<std::string> keys = { "time" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnSeeked(std::move(onSeeked));
}

void JSVideo::JsOnUpdate(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onUpdate = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                        const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.onUpdate");
        PipelineContext::SetCallBackNode(node);
        std::vector<std::string> keys = { "time" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnUpdate(std::move(onUpdate));
}

void JSVideo::JsOnError(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onError = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                       const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.onError");
        PipelineContext::SetCallBackNode(node);
        std::vector<std::string> keys = { "error" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnError(std::move(onError));
}

EventMarker JSVideo::GetEventMarker(const JSCallbackInfo& info, const std::vector<std::string>& keys)
{
    if (!info[0]->IsFunction()) {
        return EventMarker();
    }

    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto eventMarker = EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc), keys,
                                       node = targetNode](const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        PipelineContext::SetCallBackNode(node);
        func->Execute(keys, param);
    });
    return eventMarker;
}

void JSVideo::EnableAnalyzer(bool enable)
{
    VideoModel::GetInstance()->EnableAnalyzer(enable);
}

void JSVideo::AnalyzerConfig(const JSCallbackInfo& info)
{
    auto configParams = info[0];
    if (configParams->IsNull() || !configParams->IsObject()) {
        return;
    }
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    panda::Local<JsiValue> value = configParams.Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;
    ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
    napi_value nativeValue = nativeEngine->ValueToNapiValue(valueWrapper);
    VideoModel::GetInstance()->SetImageAnalyzerConfig(nativeValue);
}

void JSVideo::JSBind(BindingTarget globalObj)
{
    JSClass<JSVideo>::Declare("Video");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSVideo>::StaticMethod("create", &JSVideo::Create, opt);
    JSClass<JSVideo>::StaticMethod("muted", &JSVideo::JsMuted, opt);
    JSClass<JSVideo>::StaticMethod("autoPlay", &JSVideo::JsAutoPlay, opt);
    JSClass<JSVideo>::StaticMethod("controls", &JSVideo::JsControls, opt);
    JSClass<JSVideo>::StaticMethod("loop", &JSVideo::JsLoop, opt);
    JSClass<JSVideo>::StaticMethod("objectFit", &JSVideo::JsObjectFit, opt);

    JSClass<JSVideo>::StaticMethod("onStart", &JSVideo::JsOnStart);
    JSClass<JSVideo>::StaticMethod("onPause", &JSVideo::JsOnPause);
    JSClass<JSVideo>::StaticMethod("onFinish", &JSVideo::JsOnFinish);
    JSClass<JSVideo>::StaticMethod("onFullscreenChange", &JSVideo::JsOnFullscreenChange);
    JSClass<JSVideo>::StaticMethod("onPrepared", &JSVideo::JsOnPrepared);
    JSClass<JSVideo>::StaticMethod("onSeeking", &JSVideo::JsOnSeeking);
    JSClass<JSVideo>::StaticMethod("onSeeked", &JSVideo::JsOnSeeked);
    JSClass<JSVideo>::StaticMethod("onUpdate", &JSVideo::JsOnUpdate);
    JSClass<JSVideo>::StaticMethod("onError", &JSVideo::JsOnError);
    JSClass<JSVideo>::StaticMethod("onStop", &JSVideo::JsOnStop);
    JSClass<JSVideo>::StaticMethod("enableAnalyzer", &JSVideo::EnableAnalyzer);
    JSClass<JSVideo>::StaticMethod("analyzerConfig", &JSVideo::AnalyzerConfig);

    JSClass<JSVideo>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSVideo>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSVideo>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSVideo>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSVideo>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSVideo>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSVideo>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSVideo>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSVideo>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSVideo>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    // override method
    JSClass<JSVideo>::StaticMethod("opacity", &JSViewAbstract::JsOpacityPassThrough);
    JSClass<JSVideo>::StaticMethod("transition", &JSViewAbstract::JsTransitionPassThrough);
    JSClass<JSVideo>::InheritAndBind<JSViewAbstract>(globalObj);
}

} // namespace OHOS::Ace::Framework
