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

#include "frameworks/bridge/declarative_frontend/jsview/js_video.h"

#include "bridge/declarative_frontend/jsview/js_video_controller.h"
#include "bridge/declarative_frontend/jsview/models/video_model_impl.h"
#include "core/components_ng/pattern/video/video_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<VideoModel> VideoModel::instance_ = nullptr;

VideoModel* VideoModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::VideoModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::VideoModelNG());
        } else {
            instance_.reset(new Framework::VideoModelImpl());
        }
#endif
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSVideo::Create(const JSCallbackInfo& info)
{
    if (info.Length() <= 0 || !info[0]->IsObject()) {
        LOGE("JSVideo: info is invalid.");
        return;
    }
    JSRef<JSObject> videoObj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> srcValue = videoObj->GetProperty("src");
    std::string videoPath;
    JSRef<JSVal> currentProgressRateValue = videoObj->GetProperty("currentProgressRate");
    double currentProgressRate;
    JSRef<JSVal> previewUriValue = videoObj->GetProperty("previewUri");

    auto controllerObj = videoObj->GetProperty("controller");
    RefPtr<VideoControllerV2> videoController = nullptr;
    if (controllerObj->IsObject()) {
        auto* jsVideoController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSVideoController>();
        if (jsVideoController) {
            videoController = jsVideoController->GetController();
        }
    }

    VideoModel::GetInstance()->Create(videoController);
    if (ParseJsMedia(srcValue, videoPath)) {
        VideoModel::GetInstance()->SetSrc(videoPath);
    }
    if (ParseJsDouble(currentProgressRateValue, currentProgressRate)) {
        VideoModel::GetInstance()->SetProgressRate(currentProgressRate);
    }
    if (!previewUriValue->IsUndefined() && !previewUriValue->IsNull()) {
        std::string previewUri;
        if (ParseJsMedia(previewUriValue, previewUri)) {
            VideoModel::GetInstance()->SetPosterSourceInfo(previewUri);
        } else {
            // handle pixel map
            LOGE("can not support pixel map");
        }
    }
}

void JSVideo::JsMuted(bool isMuted)
{
    VideoModel::GetInstance()->SetMuted(isMuted);
}

void JSVideo::JsAutoPlay(bool autoPlay)
{
    VideoModel::GetInstance()->SetAutoPlay(autoPlay);
}

void JSVideo::JsControls(bool controls)
{
    VideoModel::GetInstance()->SetControls(controls);
}

void JSVideo::JsLoop(bool loop)
{
    VideoModel::GetInstance()->SetLoop(loop);
}

void JSVideo::JsObjectFit(int32_t objectFit)
{
    VideoModel::GetInstance()->SetObjectFit(static_cast<ImageFit>(objectFit));
}

void JSVideo::JsOnStart(const JSCallbackInfo& args)
{
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    auto onStart = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.onStart");
        std::vector<std::string> keys = { "start" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnStart(std::move(onStart));
}

void JSVideo::JsOnPause(const JSCallbackInfo& args)
{
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    auto onPause = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.onPause");
        std::vector<std::string> keys = { "pause" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnPause(std::move(onPause));
}

void JSVideo::JsOnFinish(const JSCallbackInfo& args)
{
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    auto onFinish = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.onFinish");
        std::vector<std::string> keys = { "finish" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnFinish(std::move(onFinish));
}

void JSVideo::JsOnFullscreenChange(const JSCallbackInfo& args)
{
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    auto OnFullScreenChange = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](
                                  const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.OnFullScreenChange");
        std::vector<std::string> keys = { "fullscreen" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnFullScreenChange(std::move(OnFullScreenChange));
}

void JSVideo::JsOnPrepared(const JSCallbackInfo& args)
{
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    auto onPrepared = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.onPrepared");
        std::vector<std::string> keys = { "duration" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnPrepared(std::move(onPrepared));
}

void JSVideo::JsOnSeeking(const JSCallbackInfo& args)
{
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    auto onSeeking = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.onSeeking");
        std::vector<std::string> keys = { "time" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnSeeking(std::move(onSeeking));
}

void JSVideo::JsOnSeeked(const JSCallbackInfo& args)
{
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    auto onSeeked = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.onSeeked");
        std::vector<std::string> keys = { "time" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnSeeked(std::move(onSeeked));
}

void JSVideo::JsOnUpdate(const JSCallbackInfo& args)
{
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    auto onUpdate = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.onUpdate");
        std::vector<std::string> keys = { "time" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnUpdate(std::move(onUpdate));
}

void JSVideo::JsOnError(const JSCallbackInfo& args)
{
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    auto onError = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Video.onError");
        std::vector<std::string> keys = { "error" };
        func->Execute(keys, param);
    };
    VideoModel::GetInstance()->SetOnError(std::move(onError));
}

EventMarker JSVideo::GetEventMarker(const JSCallbackInfo& info, const std::vector<std::string>& keys)
{
    if (!info[0]->IsFunction()) {
        LOGE("info[0] is not a function.");
        return EventMarker();
    }

    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto eventMarker =
        EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc), keys](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute(keys, param);
        });
    return eventMarker;
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

    JSClass<JSVideo>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSVideo>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSVideo>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSVideo>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSVideo>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSVideo>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSVideo>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSVideo>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSVideo>::Inherit<JSViewAbstract>();
    // override method
    JSClass<JSVideo>::StaticMethod("opacity", &JSViewAbstract::JsOpacityPassThrough);
    JSClass<JSVideo>::StaticMethod("transition", &JSViewAbstract::JsTransitionPassThrough);
    JSClass<JSVideo>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
