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

#include "base/log/ace_scoring_log.h"
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
    JSRef<JSVal> previewUriValue = videoObj->GetProperty("previewUri");
    JSRef<JSVal> currentProgressRateValue = videoObj->GetProperty("currentProgressRate");

    auto controllerObj = videoObj->GetProperty("controller");
    RefPtr<VideoControllerV2> videoController = nullptr;
    if (controllerObj->IsObject()) {
        auto* jsVideoController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSVideoController>();
        if (jsVideoController) {
            videoController = jsVideoController->GetController();
        }
    }
    VideoModel::GetInstance()->Create(videoController);

    // Parse the src, if it is invalid, use the empty string.
    std::string videoSrc;
    if (!ParseJsMedia(srcValue, videoSrc)) {
        LOGW("Video parse src failed.");
    }
    VideoModel::GetInstance()->SetSrc(videoSrc);

    // Parse the rate, if it is invalid, set it as 1.0.
    double currentProgressRate = 1.0;
    if (ParseJsDouble(currentProgressRateValue, currentProgressRate)) {
        LOGW("Video parse currentProgressRate failed.");
    }
    VideoModel::GetInstance()->SetProgressRate(currentProgressRate);

    std::string previewUri;
    if (previewUriValue->IsUndefined() || previewUriValue->IsNull()) {
        // When it is undefined, just set the empty image.
        LOGW("Video parse previewUri failed, it is null.");
        VideoModel::GetInstance()->SetPosterSourceInfo(previewUri);
        return;
    }
    auto noPixMap = ParseJsMedia(previewUriValue, previewUri);
    if (noPixMap) {
        // Src is a string or resource
        VideoModel::GetInstance()->SetPosterSourceInfo(previewUri);
    } else {
        // Src is a pixelmap.
        LOGE("can not support pixel map");
    }
}

void JSVideo::JsMuted(const JSCallbackInfo& info)
{
    bool muted = false;
    if (info[0]->IsBoolean()) {
        muted = info[0]->ToBoolean();
    }
    VideoModel::GetInstance()->SetMuted(muted);
}

void JSVideo::JsAutoPlay(const JSCallbackInfo& info)
{
    bool autoPlay = false;
    if (info[0]->IsBoolean()) {
        autoPlay = info[0]->ToBoolean();
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
        LOGW("JSVideo: objectfit is undefined.");
        VideoModel::GetInstance()->SetObjectFit(imageFit);
        return;
    }
    if (info[0]->IsNumber()) {
        imageFit = static_cast<ImageFit>(info[0]->ToNumber<int>());
    }
    VideoModel::GetInstance()->SetObjectFit(imageFit);
}

void JSVideo::JsOnStart(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 argument.");
        return;
    }
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
    if (!args[0]->IsFunction()) {
        LOGE("OnPause args need a function.");
        return;
    }
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
    if (!args[0]->IsFunction()) {
        LOGE("OnFinish args need a function.");
        return;
    }
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
    if (!args[0]->IsFunction()) {
        LOGE("OnFullscreenChange args need a function.");
        return;
    }
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
    if (!args[0]->IsFunction()) {
        LOGE("OnPrepared args need a function.");
        return;
    }
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
    if (!args[0]->IsFunction()) {
        LOGE("OnSeeking args need a function.");
        return;
    }
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
    if (!args[0]->IsFunction()) {
        LOGE("OnSeeked args need a function.");
        return;
    }
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
    if (!args[0]->IsFunction()) {
        LOGE("OnUpdate args need a function.");
        return;
    }
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
    if (!args[0]->IsFunction()) {
        LOGE("OnError args need a function.");
        return;
    }
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
