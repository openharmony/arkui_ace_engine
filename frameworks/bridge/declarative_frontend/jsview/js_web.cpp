/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_web.h"

#include <string>
#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/web/web_component.h"
#include "core/components/web/web_event.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_web_controller.h"

namespace OHOS::Ace::Framework {

class JSWebGeolocation : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebGeolocation>::Declare("WebGeolocation");
        JSClass<JSWebGeolocation>::CustomMethod("invoke", &JSWebGeolocation::Invoke);
        JSClass<JSWebGeolocation>::Bind(globalObj, &JSWebGeolocation::Constructor, &JSWebGeolocation::Destructor);
    }

    void SetEvent(const LoadWebGeolocationShowEvent& eventInfo)
    {
        webGeolocation_ = eventInfo.GetWebGeolocation();
    }

    void Invoke(const JSCallbackInfo& args)
    {
        std::string origin;
        bool allow = false;
        bool retain = false;
        if (args[0]->IsString()) {
            origin = args[0]->ToString();
        }
        if (args[1]->IsBoolean()) {
            allow = args[1]->ToBoolean();
        }
        if (args[2]->IsBoolean()) {
            retain = args[2]->ToBoolean();
        }
        webGeolocation_->Invoke(origin, allow, retain);
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsWebGeolocation = Referenced::MakeRefPtr<JSWebGeolocation>();
        jsWebGeolocation->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsWebGeolocation));
    }

    static void Destructor(JSWebGeolocation* jsWebGeolocation)
    {
        if (jsWebGeolocation != nullptr) {
            jsWebGeolocation->DecRefCount();
        }
    }

    RefPtr<WebGeolocation> webGeolocation_;
};
    
void JSWeb::JSBind(BindingTarget globalObj)
{
    JSClass<JSWeb>::Declare("Web");
    JSClass<JSWeb>::StaticMethod("create", &JSWeb::Create);
    JSClass<JSWeb>::StaticMethod("onPageBegin", &JSWeb::OnPageStart);
    JSClass<JSWeb>::StaticMethod("onPageEnd", &JSWeb::OnPageFinish);
    JSClass<JSWeb>::StaticMethod("onProgressChange", &JSWeb::OnProgressChange);
    JSClass<JSWeb>::StaticMethod("onTitleReceive", &JSWeb::OnTitleReceive);
    JSClass<JSWeb>::StaticMethod("onGeolocationHide", &JSWeb::OnGeolocationHide);
    JSClass<JSWeb>::StaticMethod("onGeolocationShow", &JSWeb::OnGeolocationShow);
    JSClass<JSWeb>::StaticMethod("onRequestSelected", &JSWeb::OnRequestFocus);
    JSClass<JSWeb>::StaticMethod("javaScriptAccess", &JSWeb::JsEnabled);
    JSClass<JSWeb>::StaticMethod("fileExtendAccess", &JSWeb::ContentAccessEnabled);
    JSClass<JSWeb>::StaticMethod("fileAccess", &JSWeb::FileAccessEnabled);

    JSClass<JSWeb>::StaticMethod("onFocus", &JSWeb::OnFocus);
    JSClass<JSWeb>::StaticMethod("onDownloadStart", &JSWeb::OnDownloadStart);
    JSClass<JSWeb>::StaticMethod("onlineImageAccess", &JSWeb::OnLineImageAccessEnabled);
    JSClass<JSWeb>::StaticMethod("domStorageAccess", &JSWeb::DomStorageAccessEnabled);
    JSClass<JSWeb>::StaticMethod("imageAccess", &JSWeb::ImageAccessEnabled);
    JSClass<JSWeb>::StaticMethod("mixedMode", &JSWeb::MixedMode);
    JSClass<JSWeb>::StaticMethod("zoomAccess", &JSWeb::ZoomAccessEnabled);
    JSClass<JSWeb>::StaticMethod("geolocationAccess", &JSWeb::GeolocationAccessEnabled);
    JSClass<JSWeb>::Inherit<JSViewAbstract>();
    JSClass<JSWeb>::Bind(globalObj);
    JSWebGeolocation::JSBind(globalObj);
}

JSRef<JSVal> LoadWebPageFinishEventToJSValue(const LoadWebPageFinishEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("url", eventInfo.GetLoadedUrl());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> LoadWebPageStartEventToJSValue(const LoadWebPageStartEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("url", eventInfo.GetLoadedUrl());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> LoadWebProgressChangeEventToJSValue(const LoadWebProgressChangeEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("newProgress", eventInfo.GetNewProgress());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> LoadWebTitleReceiveEventToJSValue(const LoadWebTitleReceiveEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("title", eventInfo.GetTitle());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> LoadWebGeolocationHideEventToJSValue(const LoadWebGeolocationHideEvent& eventInfo)
{
    return JSRef<JSVal>::Make(ToJSValue(eventInfo.GetOrigin()));
}

JSRef<JSVal> LoadWebGeolocationShowEventToJSValue(const LoadWebGeolocationShowEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("origin", eventInfo.GetOrigin());
    JSRef<JSObject> geolocationObj = JSClass<JSWebGeolocation>::NewInstance();
    auto geolocationEvent = Referenced::Claim(geolocationObj->Unwrap<JSWebGeolocation>());
    geolocationEvent->SetEvent(eventInfo);
    obj->SetPropertyObject("geolocation", geolocationObj);
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> DownloadStartEventToJSValue(const DownloadStartEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("url", eventInfo.GetUrl());
    obj->SetProperty("userAgent", eventInfo.GetUserAgent());
    obj->SetProperty("contentDisposition", eventInfo.GetContentDisposition());
    obj->SetProperty("mimetype", eventInfo.GetMimetype());
    obj->SetProperty("contentLength", eventInfo.GetContentLength());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> LoadWebRequestFocusEventToJSValue(const LoadWebRequestFocusEvent& eventInfo)
{
    return JSRef<JSVal>::Make(ToJSValue(eventInfo.GetRequestFocus()));
}

JSRef<JSVal> LoadWebOnFocusEventToJSValue(const LoadWebOnFocusEvent& eventInfo)
{
    return JSRef<JSVal>::Make(ToJSValue(eventInfo.GetOnFocus()));
}

void JSWeb::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGI("web create error, info is non-vaild");
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);

    JSRef<JSVal> srcValue = paramObject->GetProperty("src");
    std::string webSrc = "";
    std::string dstSrc = "";
    RefPtr<WebComponent> webComponent;
    if (ParseJsMedia(srcValue, webSrc)) {
        int np = webSrc.find_first_of("/");
        if (np < 0) {
            dstSrc = webSrc;
        } else {
            dstSrc = webSrc.erase(np, 1);
        }
        LOGI("JSWeb::Create src:%{public}s", dstSrc.c_str());
        webComponent = AceType::MakeRefPtr<OHOS::Ace::WebComponent>(dstSrc);
        webComponent->SetSrc(dstSrc);
    } else {
        LOGE("Web component failed to parse src");
        return;
    }

    auto controllerObj = paramObject->GetProperty("controller");
    if (!controllerObj->IsObject()) {
        LOGI("web create error, controller is non-vaild");
        return;
    }
    auto controller = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSWebController>();
    if (controller) {
        webComponent->SetWebController(controller->GetController());
    }
    ViewStackProcessor::GetInstance()->Push(webComponent);
    JSInteractableView::SetFocusNode(true);
}

void JSWeb::OnPageStart(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebPageStartEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebPageStartEventToJSValue);
    auto eventMarker = EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)]
        (const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<LoadWebPageStartEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetPageStartedEventId(eventMarker);
}

void JSWeb::OnPageFinish(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebPageFinishEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebPageFinishEventToJSValue);
    auto eventMarker = EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)]
        (const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<LoadWebPageFinishEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetPageFinishedEventId(eventMarker);
}

void JSWeb::OnProgressChange(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebProgressChangeEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebProgressChangeEventToJSValue);
    auto eventMarker = EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)]
        (const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<LoadWebProgressChangeEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetProgressChangeEventId(eventMarker);
}

void JSWeb::OnTitleReceive(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebTitleReceiveEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebTitleReceiveEventToJSValue);
    auto eventMarker = EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)]
        (const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<LoadWebTitleReceiveEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetTitleReceiveEventId(eventMarker);
}

void JSWeb::OnGeolocationHide(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebGeolocationHideEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebGeolocationHideEventToJSValue);
    auto eventMarker = EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)]
        (const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<LoadWebGeolocationHideEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetGeolocationHideEventId(eventMarker);
}

void JSWeb::OnGeolocationShow(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebGeolocationShowEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebGeolocationShowEventToJSValue);
    auto eventMarker = EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)]
        (const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<LoadWebGeolocationShowEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetGeolocationShowEventId(eventMarker);
}

void JSWeb::OnRequestFocus(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebRequestFocusEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebRequestFocusEventToJSValue);
    auto eventMarker = EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)]
        (const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<LoadWebRequestFocusEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetRequestFocusEventId(eventMarker);
}

void JSWeb::OnDownloadStart(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        LOGE("Param is invalid");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<DownloadStartEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), DownloadStartEventToJSValue);
    auto eventMarker = EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)]
        (const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<DownloadStartEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetDownloadStartEventId(eventMarker);
}

void JSWeb::OnFocus(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebOnFocusEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebOnFocusEventToJSValue);
    auto eventMarker = EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)]
        (const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<LoadWebOnFocusEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetOnFocusEventId(eventMarker);
}

void JSWeb::JsEnabled(bool isJsEnabled)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    webComponent->SetJsEnabled(isJsEnabled);
}

void JSWeb::ContentAccessEnabled(bool isContentAccessEnabled)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    webComponent->SetContentAccessEnabled(isContentAccessEnabled);
}

void JSWeb::FileAccessEnabled(bool isFileAccessEnabled)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    webComponent->SetFileAccessEnabled(isFileAccessEnabled);
}

void JSWeb::OnLineImageAccessEnabled(bool isOnLineImageAccessEnabled)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    webComponent->SetOnLineImageAccessEnabled(!isOnLineImageAccessEnabled);
}

void JSWeb::DomStorageAccessEnabled(bool isDomStorageAccessEnabled)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    webComponent->SetDomStorageAccessEnabled(isDomStorageAccessEnabled);
}

void JSWeb::ImageAccessEnabled(bool isImageAccessEnabled)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    webComponent->SetImageAccessEnabled(isImageAccessEnabled);
}

void JSWeb::MixedMode(int32_t mixedMode)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    auto mixedContentMode = MixedModeContent::MIXED_CONTENT_NEVER_ALLOW;
    switch (mixedMode) {
        case 0:
            mixedContentMode = MixedModeContent::MIXED_CONTENT_ALWAYS_ALLOW;
            break;
        case 1:
            mixedContentMode = MixedModeContent::MIXED_CONTENT_COMPATIBILITY_MODE;
            break;
        default:
            mixedContentMode = MixedModeContent::MIXED_CONTENT_NEVER_ALLOW;
            break;
    }
    webComponent->SetMixedMode(mixedContentMode);
}

void JSWeb::ZoomAccessEnabled(bool isZoomAccessEnabled)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    webComponent->SetZoomAccessEnabled(isZoomAccessEnabled);
}

void JSWeb::GeolocationAccessEnabled(bool isGeolocationAccessEnabled)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    webComponent->SetGeolocationAccessEnabled(isGeolocationAccessEnabled);
}

} // namespace OHOS::Ace::Framework
