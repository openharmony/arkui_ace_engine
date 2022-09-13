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

#include "base/log/ace_trace.h"
#include "core/common/ace_application_info.h"
#include "core/components/video/resource/player.h"
#include "core/components/video/resource/texture.h"
#include "core/components/video/video_component_v2.h"
#include "core/components_ng/pattern/video/video_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_video_controller.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

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

    if (Container::IsCurrentUseNewPipeline()) {
        NG::VideoView::Create(videoController);
        if (ParseJsMedia(srcValue, videoPath)) {
            NG::VideoView::SetSrc(videoPath);
        }
        if (ParseJsDouble(currentProgressRateValue, currentProgressRate)) {
            NG::VideoView::SetProgressRate(currentProgressRate);
        }
        if (!previewUriValue->IsUndefined() && !previewUriValue->IsNull()) {
            std::string previewUri;
            if (ParseJsMedia(previewUriValue, previewUri)) {
                NG::VideoView::SetPosterSourceInfo(previewUri);
            } else {
                // handle pixel map
                LOGE("can not support pixel map");
            }
        }
        return;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto videoComponent = AceType::MakeRefPtr<OHOS::Ace::VideoComponentV2>();
    videoComponent->SetSaveComponentEvent([videoComponent](std::unordered_map<std::string, RefPtr<Component>> map) {
        videoComponent->SetGestureComponentMap(map);
    });
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        videoComponent->SetTextDirection(TextDirection::RTL);
    }

    ViewStackProcessor::GetInstance()->ClaimElementId(videoComponent);
    ViewStackProcessor::GetInstance()->Push(videoComponent);

    if (ParseJsMedia(srcValue, videoPath)) {
        videoComponent->SetSrc(videoPath);
    }

    if (ParseJsDouble(currentProgressRateValue, currentProgressRate)) {
        videoComponent->SetSpeed(currentProgressRate);
    }

    if (!previewUriValue->IsUndefined() && !previewUriValue->IsNull()) {
        std::string previewUri;
        auto noPixMap = ParseJsMedia(previewUriValue, previewUri);
        videoComponent->SetPoster(previewUri);
        if (!noPixMap) {
#if defined(VIDEO_SUPPORTED)
            auto pixelMap = CreatePixelMapFromNapiValue(previewUriValue);
            if (pixelMap) {
                RefPtr<ImageComponent> imageComponent = AceType::MakeRefPtr<OHOS::Ace::ImageComponent>(previewUri);
                imageComponent->SetUseSkiaSvg(false);
                imageComponent->SetPixmap(pixelMap);
                videoComponent->SetPosterImage(imageComponent);
            }
#endif
        }
    }

    if (videoController) {
        videoComponent->SetVideoControllerV2(videoController);
    }
    stack->GetFlexItemComponent();
}

void JSVideo::JsMuted(bool isMuted)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::VideoView::SetMuted(isMuted);
        return;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(stack->GetMainComponent());
    if (!videoComponent) {
        LOGE("JSVideo: MainComponent is null.");
        return;
    }

    videoComponent->SetMute(isMuted);
}

void JSVideo::JsAutoPlay(bool autoPlay)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::VideoView::SetAutoPlay(autoPlay);
        return;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(stack->GetMainComponent());
    if (!videoComponent) {
        LOGE("JSVideo: MainComponent is null.");
        return;
    }

    videoComponent->SetAutoPlay(autoPlay);
}

void JSVideo::JsControls(bool controls)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::VideoView::SetControls(controls);
        return;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(stack->GetMainComponent());
    if (!videoComponent) {
        LOGE("JSVideo: MainComponent is null.");
        return;
    }

    videoComponent->SetNeedControls(controls);
}

void JSVideo::JsLoop(bool loop)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::VideoView::SetLoop(loop);
        return;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(stack->GetMainComponent());
    if (!videoComponent) {
        LOGE("JSVideo: MainComponent is null.");
        return;
    }
    videoComponent->SetLoop(loop);
}

void JSVideo::JsObjectFit(int32_t objectFit)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::VideoView::SetObjectFit(static_cast<ImageFit>(objectFit));
        return;
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(stack->GetMainComponent());
    if (!videoComponent) {
        LOGE("JSVideo: MainComponent is null.");
        return;
    }

    videoComponent->SetFit(static_cast<ImageFit>(objectFit));
}

void JSVideo::JsOnStart(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
        auto onStart = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Video.onStart");
            std::vector<std::string> keys = { "start" };
            func->Execute(keys, param);
        };
        NG::VideoView::SetOnStart(std::move(onStart));
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(stack->GetMainComponent());
    if (!videoComponent) {
        LOGE("JSVideo: MainComponent is null.");
        return;
    }
    std::vector<std::string> keys = { "start" };
    videoComponent->SetStartEventId(GetEventMarker(args, keys));
}

void JSVideo::JsOnPause(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
        auto onPause = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Video.onPause");
            std::vector<std::string> keys = { "pause" };
            func->Execute(keys, param);
        };
        NG::VideoView::SetOnPause(std::move(onPause));
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(stack->GetMainComponent());
    if (!videoComponent) {
        LOGE("JSVideo: MainComponent is null.");
        return;
    }
    std::vector<std::string> keys = { "pause" };
    videoComponent->SetPauseEventId(GetEventMarker(args, keys));
}

void JSVideo::JsOnFinish(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
        auto onFinish = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Video.onFinish");
            std::vector<std::string> keys = { "finish" };
            func->Execute(keys, param);
        };
        NG::VideoView::SetOnFinish(std::move(onFinish));
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(stack->GetMainComponent());
    if (!videoComponent) {
        LOGE("JSVideo: MainComponent is null.");
        return;
    }
    std::vector<std::string> keys = { "finish" };
    videoComponent->SetFinishEventId(GetEventMarker(args, keys));
}

void JSVideo::JsOnFullscreenChange(const JSCallbackInfo& args)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(stack->GetMainComponent());
    if (!videoComponent) {
        LOGE("JSVideo: MainComponent is null.");
        return;
    }
    std::vector<std::string> keys = { "fullscreen" };
    videoComponent->SetFullscreenChangeEventId(GetEventMarker(args, keys));
}

void JSVideo::JsOnPrepared(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
        auto onPrepared = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Video.onPrepared");
            std::vector<std::string> keys = { "duration" };
            func->Execute(keys, param);
        };
        NG::VideoView::SetOnPrepared(std::move(onPrepared));
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(stack->GetMainComponent());
    if (!videoComponent) {
        LOGE("JSVideo: MainComponent is null.");
        return;
    }
    std::vector<std::string> keys = { "duration" };
    videoComponent->SetPreparedEventId(GetEventMarker(args, keys));
}

void JSVideo::JsOnSeeking(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
        auto onSeeking = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Video.onSeeking");
            std::vector<std::string> keys = { "time" };
            func->Execute(keys, param);
        };
        NG::VideoView::SetOnSeeking(std::move(onSeeking));
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(stack->GetMainComponent());
    if (!videoComponent) {
        LOGE("JSVideo: MainComponent is null.");
        return;
    }
    std::vector<std::string> keys = { "time" };
    videoComponent->SetSeekingEventId(GetEventMarker(args, keys));
}

void JSVideo::JsOnSeeked(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
        auto onSeeked = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Video.onSeeked");
            std::vector<std::string> keys = { "time" };
            func->Execute(keys, param);
        };
        NG::VideoView::SetOnSeeked(std::move(onSeeked));
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(stack->GetMainComponent());
    if (!videoComponent) {
        LOGE("JSVideo: MainComponent is null.");
        return;
    }
    std::vector<std::string> keys = { "time" };
    videoComponent->SetSeekedEventId(GetEventMarker(args, keys));
}

void JSVideo::JsOnUpdate(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
        auto onUpdate = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Video.onUpdate");
            std::vector<std::string> keys = { "time" };
            func->Execute(keys, param);
        };
        NG::VideoView::SetOnUpdate(std::move(onUpdate));
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(stack->GetMainComponent());
    if (!videoComponent) {
        LOGE("JSVideo: MainComponent is null.");
        return;
    }
    std::vector<std::string> keys = { "time" };
    videoComponent->SetTimeUpdateEventId(GetEventMarker(args, keys));
}

void JSVideo::JsOnError(const JSCallbackInfo& args)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
        auto onError = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Video.onError");
            std::vector<std::string> keys = { "error" };
            func->Execute(keys, param);
        };
        NG::VideoView::SetOnError(std::move(onError));
    }
    auto* stack = ViewStackProcessor::GetInstance();
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(stack->GetMainComponent());
    if (!videoComponent) {
        LOGE("JSVideo: MainComponent is null.");
        return;
    }
    std::vector<std::string> keys = { "error" };
    videoComponent->SetErrorEventId(GetEventMarker(args, keys));
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
