/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_previewer_mock.h"

#include "base/log/ace_trace.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/preview_mock_model_impl.h"
#include "frameworks/core/components_ng/pattern/preview_mock/preview_mock_model.h"
#include "frameworks/core/components_ng/pattern/preview_mock/preview_mock_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<PreviewMockModel> PreviewMockModel::instance_ = nullptr;
std::mutex PreviewMockModel::mutex_;

PreviewMockModel* PreviewMockModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::PreviewMockModelNG());
            } else {
                instance_.reset(new Framework::PreviewMockModelImpl());
            }
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void CreateMockComponent(const std::string& inspectorTag)
{
    OHOS::Ace::PreviewMockModel::GetInstance()->Create(inspectorTag);
}

void JSForm::Create(const JSCallbackInfo& info)
{
    if (info.Length() == 0 || !info[0]->IsObject()) {
        return;
    }

    CreateMockComponent("FormComponent");
}

void JSForm::Mock(const JSCallbackInfo& info) {}

void JSForm::JSBind(BindingTarget globalObj)
{
    JSClass<JSForm>::Declare("FormComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSForm>::StaticMethod("create", &JSForm::Create, opt);
    JSClass<JSForm>::StaticMethod("size", &JSForm::Mock, opt);
    JSClass<JSForm>::StaticMethod("dimension", &JSForm::Mock, opt);
    JSClass<JSForm>::StaticMethod("allowUpdate", &JSForm::Mock, opt);
    JSClass<JSForm>::StaticMethod("visibility", &JSForm::Mock, opt);
    JSClass<JSForm>::StaticMethod("clip", &JSForm::Mock, opt);

    JSClass<JSForm>::StaticMethod("onAcquired", &JSForm::Mock);
    JSClass<JSForm>::StaticMethod("onError", &JSForm::Mock);
    JSClass<JSForm>::StaticMethod("onUninstall", &JSForm::Mock);
    JSClass<JSForm>::StaticMethod("onRouter", &JSForm::Mock);
    JSClass<JSForm>::StaticMethod("onAppear", &JSForm::Mock);
    JSClass<JSForm>::StaticMethod("onDisAppear", &JSForm::Mock);
    JSClass<JSForm>::StaticMethod("onAttach", &JSForm::Mock);
    JSClass<JSForm>::StaticMethod("onDetach", &JSForm::Mock);
    JSClass<JSForm>::StaticMethod("onTouch", &JSForm::Mock);
    JSClass<JSForm>::StaticMethod("onKeyEvent", &JSForm::Mock);
    JSClass<JSForm>::StaticMethod("onDeleteEvent", &JSForm::Mock);
    JSClass<JSForm>::StaticMethod("onClick", &JSForm::Mock);

    JSClass<JSForm>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSRichText::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CreateMockComponent("RichText");
}

void JSRichText::Mock(const JSCallbackInfo& info) {}

void JSRichText::JSBind(BindingTarget globalObj)
{
    JSClass<JSRichText>::Declare("RichText");
    JSClass<JSRichText>::StaticMethod("create", &JSRichText::Create);
    JSClass<JSRichText>::StaticMethod("onStart", &JSRichText::Mock);
    JSClass<JSRichText>::StaticMethod("onComplete", &JSRichText::Mock);
    JSClass<JSRichText>::InheritAndBind<JSViewAbstract>(globalObj);
}

class JSWebDialog : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebDialog>::Declare("WebDialog");
        JSClass<JSWebDialog>::StaticMethod("handleConfirm", &JSWeb::Mock);
        JSClass<JSWebDialog>::StaticMethod("handleCancel", &JSWeb::Mock);
        JSClass<JSWebDialog>::StaticMethod("handlePromptConfirm", &JSWeb::Mock);
        JSClass<JSWebDialog>::Bind(globalObj);
    }
};

class JSWebHttpAuth : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebHttpAuth>::Declare("WebHttpAuthResult");
        JSClass<JSWebHttpAuth>::StaticMethod("confirm", &JSWeb::Mock);
        JSClass<JSWebHttpAuth>::StaticMethod("cancel", &JSWeb::Mock);
        JSClass<JSWebHttpAuth>::StaticMethod("isHttpAuthInfoSaved", &JSWeb::Mock);
        JSClass<JSWebHttpAuth>::Bind(globalObj);
    }
};

class JSWebSslError : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebSslError>::Declare("WebSslErrorResult");
        JSClass<JSWebSslError>::StaticMethod("handleConfirm", &JSWeb::Mock);
        JSClass<JSWebSslError>::StaticMethod("handleCancel", &JSWeb::Mock);
        JSClass<JSWebSslError>::Bind(globalObj);
    }
};

class JSWebSslSelectCert : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebSslSelectCert>::Declare("WebSelectCertResult");
        JSClass<JSWebSslSelectCert>::StaticMethod("confirm", &JSWeb::Mock);
        JSClass<JSWebSslSelectCert>::StaticMethod("cancel", &JSWeb::Mock);
        JSClass<JSWebSslSelectCert>::StaticMethod("ignore", &JSWeb::Mock);
        JSClass<JSWebSslSelectCert>::Bind(globalObj);
    }
};

class JSWebConsoleLog : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebConsoleLog>::Declare("ConsoleMessage");
        JSClass<JSWebConsoleLog>::StaticMethod("getLineNumber", &JSWeb::Mock);
        JSClass<JSWebConsoleLog>::StaticMethod("getMessage", &JSWeb::Mock);
        JSClass<JSWebConsoleLog>::StaticMethod("getMessageLevel", &JSWeb::Mock);
        JSClass<JSWebConsoleLog>::StaticMethod("getSourceId", &JSWeb::Mock);
        JSClass<JSWebConsoleLog>::Bind(globalObj);
    }
};

class JSWebGeolocation : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebGeolocation>::Declare("WebGeolocation");
        JSClass<JSWebGeolocation>::StaticMethod("invoke", &JSWeb::Mock);
        JSClass<JSWebGeolocation>::Bind(globalObj);
    }
};

class JSWebResourceError : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebResourceError>::Declare("WebResourceError");
        JSClass<JSWebResourceError>::StaticMethod("getErrorCode", &JSWeb::Mock);
        JSClass<JSWebResourceError>::StaticMethod("getErrorInfo", &JSWeb::Mock);
        JSClass<JSWebResourceError>::Bind(globalObj);
    }
};

class JSWebResourceResponse : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebResourceResponse>::Declare("WebResourceResponse");
        JSClass<JSWebResourceResponse>::StaticMethod("getResponseData", &JSWeb::Mock);
        JSClass<JSWebResourceResponse>::StaticMethod("getResponseEncoding", &JSWeb::Mock);
        JSClass<JSWebResourceResponse>::StaticMethod("getResponseMimeType", &JSWeb::Mock);
        JSClass<JSWebResourceResponse>::StaticMethod("getReasonMessage", &JSWeb::Mock);
        JSClass<JSWebResourceResponse>::StaticMethod("getResponseCode", &JSWeb::Mock);
        JSClass<JSWebResourceResponse>::StaticMethod("getResponseHeader", &JSWeb::Mock);
        JSClass<JSWebResourceResponse>::Bind(globalObj);
    }
};

class JSWebResourceRequest : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebResourceRequest>::Declare("WebResourceRequest");
        JSClass<JSWebResourceRequest>::StaticMethod("getRequestUrl", &JSWeb::Mock);
        JSClass<JSWebResourceRequest>::StaticMethod("getRequestHeader", &JSWeb::Mock);
        JSClass<JSWebResourceRequest>::StaticMethod("isRequestGesture", &JSWeb::Mock);
        JSClass<JSWebResourceRequest>::StaticMethod("isMainFrame", &JSWeb::Mock);
        JSClass<JSWebResourceRequest>::StaticMethod("isRedirect", &JSWeb::Mock);
        JSClass<JSWebResourceRequest>::Bind(globalObj);
    }
};

class JSFileSelectorParam : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSFileSelectorParam>::Declare("FileSelectorParam");
        JSClass<JSFileSelectorParam>::StaticMethod("getTitle", &JSWeb::Mock);
        JSClass<JSFileSelectorParam>::StaticMethod("getMode", &JSWeb::Mock);
        JSClass<JSFileSelectorParam>::StaticMethod("getAcceptType", &JSWeb::Mock);
        JSClass<JSFileSelectorParam>::StaticMethod("isCapture", &JSWeb::Mock);
        JSClass<JSFileSelectorParam>::Bind(globalObj);
    }
};

class JSFileSelectorResult : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSFileSelectorResult>::Declare("FileSelectorResult");
        JSClass<JSFileSelectorResult>::StaticMethod("handleFileList", &JSWeb::Mock);
        JSClass<JSFileSelectorResult>::Bind(globalObj);
    }
};

void JSWeb::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }

    CreateMockComponent("Web");
}

void JSWeb::Mock(const JSCallbackInfo& info) {}

void JSWeb::JSBind(BindingTarget globalObj)
{
    JSClass<JSWeb>::Declare("Web");
    JSClass<JSWeb>::StaticMethod("create", &JSWeb::Create);
    JSClass<JSWeb>::StaticMethod("onAlert", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onBeforeUnload", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onConfirm", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onPrompt", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onConsole", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onPageBegin", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onPageEnd", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onProgressChange", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onTitleReceive", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onGeolocationHide", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onGeolocationShow", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onRequestSelected", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onShowFileSelector", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("javaScriptAccess", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("fileExtendAccess", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("fileAccess", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onDownloadStart", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onErrorReceive", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onHttpErrorReceive", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onUrlLoadIntercept", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onlineImageAccess", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("domStorageAccess", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("imageAccess", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("mixedMode", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("zoomAccess", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("geolocationAccess", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("javaScriptProxy", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("userAgent", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onRenderExited", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onRefreshAccessedHistory", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("cacheMode", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("overviewModeAccess", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("fileFromUrlAccess", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("databaseAccess", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("textZoomAtio", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("textZoomRatio", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("webDebuggingAccess", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("initialScale", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("backgroundColor", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onKeyEvent", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onTouch", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onMouse", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onResourceLoad", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onScaleChange", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("password", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("tableData", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onFileSelectorShow", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onHttpAuthRequest", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onSslErrorEventReceive", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onClientAuthenticationRequest", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onRenderProcessNotResponding", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onRenderProcessResponding", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onViewportFitChanged", &JSWeb::Mock);
    JSClass<JSWeb>::StaticMethod("onAdsBlocked", &JSWeb::Mock);

    JSClass<JSWeb>::InheritAndBind<JSViewAbstract>(globalObj);

    JSWebDialog::JSBind(globalObj);
    JSWebGeolocation::JSBind(globalObj);
    JSWebResourceRequest::JSBind(globalObj);
    JSWebResourceError::JSBind(globalObj);
    JSWebResourceResponse::JSBind(globalObj);
    JSWebConsoleLog::JSBind(globalObj);
    JSFileSelectorParam::JSBind(globalObj);
    JSFileSelectorResult::JSBind(globalObj);
    JSWebHttpAuth::JSBind(globalObj);
    JSWebSslError::JSBind(globalObj);
    JSWebSslSelectCert::JSBind(globalObj);
}

class JSWebCookie : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebCookie>::Declare("WebCookie");
        JSClass<JSWebCookie>::StaticMethod("setCookie", &JSWeb::Mock);
        JSClass<JSWebCookie>::StaticMethod("getCookie", &JSWeb::Mock);
        JSClass<JSWebCookie>::StaticMethod("deleteEntireCookie", &JSWeb::Mock);
        JSClass<JSWebCookie>::StaticMethod("saveCookieSync", &JSWeb::Mock);
        JSClass<JSWebCookie>::Bind(globalObj);
    }
};

class JSHitTestValue : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSHitTestValue>::Declare("HitTestValue");
        JSClass<JSHitTestValue>::StaticMethod("getType", &JSWeb::Mock);
        JSClass<JSHitTestValue>::StaticMethod("getExtra", &JSWeb::Mock);
        JSClass<JSHitTestValue>::Bind(globalObj);
    }
};

void JSWebController::JSBind(BindingTarget globalObj)
{
    JSClass<JSWebController>::Declare("WebController");
    JSClass<JSWebController>::StaticMethod("loadUrl", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("runJavaScript", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("refresh", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("stop", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("getHitTest", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("registerJavaScriptProxy", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("deleteJavaScriptRegister", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("onInactive", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("onActive", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("zoom", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("requestFocus", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("loadData", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("backward", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("forward", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("accessStep", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("accessForward", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("accessBackward", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("clearHistory", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("clearSslCache", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("clearClientAuthenticationCache", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("getCookieManager", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("getHitTestValue", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("backOrForward", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("zoomIn", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("zoomOut", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("getPageHeight", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("getTitle", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("getWebId", &JSWeb::Mock);
    JSClass<JSWebController>::StaticMethod("getDefaultUserAgent", &JSWeb::Mock);
    JSClass<JSWebController>::Bind(globalObj);
    JSWebCookie::JSBind(globalObj);
    JSHitTestValue::JSBind(globalObj);
}

void JSXComponent::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    CreateMockComponent("XComponent");
}

void JSXComponent::Mock(const JSCallbackInfo& info) {}

void JSXComponent::JSBind(BindingTarget globalObj)
{
    JSClass<JSXComponent>::Declare("XComponent");
    JSClass<JSXComponent>::StaticMethod("create", &JSXComponent::Create);
    JSClass<JSXComponent>::StaticMethod("onLoad", &JSXComponent::Mock);
    JSClass<JSXComponent>::StaticMethod("onDestroy", &JSXComponent::Mock);
    JSClass<JSXComponent>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSXComponentController::JSBind(BindingTarget globalObj)
{
    JSClass<JSXComponentController>::Declare("XComponentController");
    JSClass<JSXComponentController>::StaticMethod("getXComponentSurfaceId", &JSXComponentController::Mock);
    JSClass<JSXComponentController>::StaticMethod("getXComponentContext", &JSXComponentController::Mock);
    JSClass<JSXComponentController>::StaticMethod("setXComponentSurfaceSize", &JSXComponentController::Mock);
    JSClass<JSXComponentController>::Bind(globalObj);
}

void JSXComponentController::Mock(const JSCallbackInfo& info) {}

void JSVideo::Create(const JSCallbackInfo& info)
{
    if (info.Length() <= 0 || !info[0]->IsObject()) {
        return;
    }
    CreateMockComponent("Video");
}

void JSVideo::Mock(const JSCallbackInfo& info) {}

void JSVideo::JSBind(BindingTarget globalObj)
{
    JSClass<JSVideo>::Declare("Video");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSVideo>::StaticMethod("create", &JSVideo::Create, opt);
    JSClass<JSVideo>::StaticMethod("muted", &JSVideo::Mock, opt);
    JSClass<JSVideo>::StaticMethod("autoPlay", &JSVideo::Mock, opt);
    JSClass<JSVideo>::StaticMethod("controls", &JSVideo::Mock, opt);
    JSClass<JSVideo>::StaticMethod("loop", &JSVideo::Mock, opt);
    JSClass<JSVideo>::StaticMethod("objectFit", &JSVideo::Mock, opt);

    JSClass<JSVideo>::StaticMethod("onStart", &JSVideo::Mock);
    JSClass<JSVideo>::StaticMethod("onPause", &JSVideo::Mock);
    JSClass<JSVideo>::StaticMethod("onFinish", &JSVideo::Mock);
    JSClass<JSVideo>::StaticMethod("onFullscreenChange", &JSVideo::Mock);
    JSClass<JSVideo>::StaticMethod("onPrepared", &JSVideo::Mock);
    JSClass<JSVideo>::StaticMethod("onSeeking", &JSVideo::Mock);
    JSClass<JSVideo>::StaticMethod("onSeeked", &JSVideo::Mock);
    JSClass<JSVideo>::StaticMethod("onUpdate", &JSVideo::Mock);
    JSClass<JSVideo>::StaticMethod("onError", &JSVideo::Mock);

    JSClass<JSVideo>::StaticMethod("onTouch", &JSVideo::Mock);
    JSClass<JSVideo>::StaticMethod("onHover", &JSVideo::Mock);
    JSClass<JSVideo>::StaticMethod("onKeyEvent", &JSVideo::Mock);
    JSClass<JSVideo>::StaticMethod("onDeleteEvent", &JSVideo::Mock);
    JSClass<JSVideo>::StaticMethod("onClick", &JSVideo::Mock);
    JSClass<JSVideo>::StaticMethod("onAppear", &JSVideo::Mock);
    JSClass<JSVideo>::StaticMethod("onDisAppear", &JSVideo::Mock);
    JSClass<JSVideo>::StaticMethod("onAttach", &JSVideo::Mock);
    JSClass<JSVideo>::StaticMethod("onDetach", &JSVideo::Mock);
    JSClass<JSVideo>::StaticMethod("remoteMessage", &JSVideo::Mock);
    JSClass<JSVideo>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSVideoController::JSBind(BindingTarget globalObj)
{
    JSClass<JSVideoController>::Declare("VideoController");
    JSClass<JSVideoController>::StaticMethod("start", &JSVideoController::Mock);
    JSClass<JSVideoController>::StaticMethod("pause", &JSVideoController::Mock);
    JSClass<JSVideoController>::StaticMethod("stop", &JSVideoController::Mock);
    JSClass<JSVideoController>::StaticMethod("setCurrentTime", &JSVideoController::Mock);
    JSClass<JSVideoController>::StaticMethod("requestFullscreen", &JSVideoController::Mock);
    JSClass<JSVideoController>::StaticMethod("exitFullscreen", &JSVideoController::Mock);
    JSClass<JSVideoController>::Bind(globalObj);
}

void JSVideoController::Mock(const JSCallbackInfo& info) {}

void JSPlugin::Create(const JSCallbackInfo& info)
{
    if (info.Length() <= 0 || !info[0]->IsObject()) {
        return;
    }
    CreateMockComponent("PluginComponent");
}

void JSPlugin::Mock(const JSCallbackInfo& info) {}

void JSPlugin::JSBind(BindingTarget globalObj)
{
    JSClass<JSPlugin>::Declare("PluginComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSPlugin>::StaticMethod("create", &JSPlugin::Create, opt);
    JSClass<JSPlugin>::StaticMethod("size", &JSPlugin::Mock, opt);
    JSClass<JSPlugin>::StaticMethod("width", &JSPlugin::Mock);
    JSClass<JSPlugin>::StaticMethod("height", &JSPlugin::Mock);
    JSClass<JSPlugin>::StaticMethod("onComplete", &JSPlugin::Mock);
    JSClass<JSPlugin>::StaticMethod("onError", &JSPlugin::Mock);
    JSClass<JSPlugin>::StaticMethod("onAppear", &JSPlugin::Mock);
    JSClass<JSPlugin>::StaticMethod("onDisAppear", &JSPlugin::Mock);
    JSClass<JSPlugin>::StaticMethod("onAttach", &JSPlugin::Mock);
    JSClass<JSPlugin>::StaticMethod("onDetach", &JSPlugin::Mock);
    JSClass<JSPlugin>::StaticMethod("onTouch", &JSPlugin::Mock);
    JSClass<JSPlugin>::StaticMethod("onKeyEvent", &JSPlugin::Mock);
    JSClass<JSPlugin>::StaticMethod("onDeleteEvent", &JSPlugin::Mock);
    JSClass<JSPlugin>::StaticMethod("onClick", &JSPlugin::Mock);

    JSClass<JSPlugin>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSUIExtension::JSBind(BindingTarget globalObj)
{
    JSClass<JSUIExtension>::Declare("UIExtensionComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSUIExtension>::StaticMethod("create", &JSUIExtension::Create, opt);
    JSClass<JSUIExtension>::StaticMethod("onRemoteReady", &JSUIExtension::Mock);
    JSClass<JSUIExtension>::StaticMethod("onReceive", &JSUIExtension::Mock);
    JSClass<JSUIExtension>::StaticMethod("onResult", &JSUIExtension::Mock);
    JSClass<JSUIExtension>::StaticMethod("onRelease", &JSUIExtension::Mock);
    JSClass<JSUIExtension>::StaticMethod("onError", &JSUIExtension::Mock);
    JSClass<JSUIExtension>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSUIExtension::Create(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    CreateMockComponent("UIExtensionComponent");
}

void JSUIExtension::Mock(const JSCallbackInfo& info) {}

void JSPreviewUIExtension::JSBind(BindingTarget globalObj)
{
    JSClass<JSPreviewUIExtension>::Declare("PreviewUIExtensionComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSPreviewUIExtension>::StaticMethod("create", &JSPreviewUIExtension::Create, opt);
    JSClass<JSPreviewUIExtension>::StaticMethod("onError", &JSPreviewUIExtension::Mock);
    JSClass<JSPreviewUIExtension>::StaticMethod("width", &JSPreviewUIExtension::Mock);
    JSClass<JSPreviewUIExtension>::StaticMethod("height", &JSPreviewUIExtension::Mock);
    JSClass<JSPreviewUIExtension>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSPreviewUIExtension::Create(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    CreateMockComponent("PreviewUIExtensionComponent");
}

void JSPreviewUIExtension::Mock(const JSCallbackInfo& info) {}

void JSSecurityUIExtension::JSBind(BindingTarget globalObj)
{
    JSClass<JSSecurityUIExtension>::Declare("SecurityUIExtensionComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSecurityUIExtension>::StaticMethod("create", &JSSecurityUIExtension::Create, opt);
    JSClass<JSSecurityUIExtension>::StaticMethod("onRemoteReady", &JSSecurityUIExtension::Mock);
    JSClass<JSSecurityUIExtension>::StaticMethod("onReceive", &JSSecurityUIExtension::Mock);
    JSClass<JSSecurityUIExtension>::StaticMethod("onError", &JSSecurityUIExtension::Mock);
    JSClass<JSSecurityUIExtension>::StaticMethod("onTerminated", &JSSecurityUIExtension::Mock);
    JSClass<JSSecurityUIExtension>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSSecurityUIExtension::Create(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    CreateMockComponent("SecurityUIExtensionComponent");
}

void JSSecurityUIExtension::Mock(const JSCallbackInfo& info) {}

void JSAbilityComponent::JSBind(BindingTarget globalObj)
{
    JSClass<JSAbilityComponent>::Declare("AbilityComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSAbilityComponent>::StaticMethod("create", &JSAbilityComponent::Create, opt);
    JSClass<JSAbilityComponent>::StaticMethod("onReady", &JSAbilityComponent::Mock, opt);
    JSClass<JSAbilityComponent>::StaticMethod("onDestroy", &JSAbilityComponent::Mock, opt);
    JSClass<JSAbilityComponent>::StaticMethod("onAbilityCreated", &JSAbilityComponent::Mock, opt);
    JSClass<JSAbilityComponent>::StaticMethod("onAbilityMoveToFront", &JSAbilityComponent::Mock, opt);
    JSClass<JSAbilityComponent>::StaticMethod("onAbilityWillRemove", &JSAbilityComponent::Mock, opt);
    JSClass<JSAbilityComponent>::StaticMethod("onConnect", &JSAbilityComponent::Mock, opt);
    JSClass<JSAbilityComponent>::StaticMethod("onDisconnect", &JSAbilityComponent::Mock, opt);
    JSClass<JSAbilityComponent>::StaticMethod("width", &JSAbilityComponent::Mock, opt);
    JSClass<JSAbilityComponent>::StaticMethod("height", &JSAbilityComponent::Mock, opt);
    JSClass<JSAbilityComponent>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSAbilityComponent::Create(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    CreateMockComponent("AbilityComponent");
}

void JSAbilityComponent::Mock(const JSCallbackInfo& info) {}

void JSSceneView::JSBind(BindingTarget globalObj)
{
    JSClass<JSSceneView>::Declare("Component3D");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSceneView>::StaticMethod("create", &JSSceneView::Create, opt);
    JSClass<JSSceneView>::StaticMethod("gestureAccess", &JSSceneView::Mock);
    JSClass<JSSceneView>::StaticMethod("environment", &JSSceneView::Mock);
    JSClass<JSSceneView>::StaticMethod("customRender", &JSSceneView::Mock);
    JSClass<JSSceneView>::StaticMethod("shader", &JSSceneView::Mock);
    JSClass<JSSceneView>::StaticMethod("renderWidth", &JSSceneView::Mock);
    JSClass<JSSceneView>::StaticMethod("renderHeight", &JSSceneView::Mock);
    JSClass<JSSceneView>::StaticMethod("renderFrameRateHint", &JSSceneView::Mock);
    JSClass<JSSceneView>::StaticMethod("shaderImageTexture", &JSSceneView::Mock);
    JSClass<JSSceneView>::StaticMethod("shaderInputBuffer", &JSSceneView::Mock);
    JSClass<JSSceneView>::StaticMethod("OnError", &JSSceneView::Mock);
    JSClass<JSSceneView>::StaticMethod("onAttach", &JSSceneView::Mock);
    JSClass<JSSceneView>::StaticMethod("onAppear", &JSSceneView::Mock);
    JSClass<JSSceneView>::StaticMethod("onDetach", &JSSceneView::Mock);
    JSClass<JSSceneView>::StaticMethod("onDisAppear", &JSSceneView::Mock);
    JSClass<JSSceneView>::StaticMethod("onClick", &JSSceneView::Mock);
    JSClass<JSSceneView>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSSceneView::Create(const JSCallbackInfo& info)
{
    CreateMockComponent("Component3D");
}

void JSSceneView::Mock(const JSCallbackInfo& info) {}

void JSEmbeddedComponent::JSBind(BindingTarget globalObj)
{
    JSClass<JSEmbeddedComponent>::Declare("EmbeddedComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSEmbeddedComponent>::StaticMethod("create", &JSEmbeddedComponent::Create, opt);
    JSClass<JSEmbeddedComponent>::StaticMethod("onTerminated", &JSEmbeddedComponent::Mock);
    JSClass<JSEmbeddedComponent>::StaticMethod("onError", &JSEmbeddedComponent::Mock);
    JSClass<JSEmbeddedComponent>::StaticMethod("width", &JSEmbeddedComponent::Mock);
    JSClass<JSEmbeddedComponent>::StaticMethod("height", &JSEmbeddedComponent::Mock);
    JSClass<JSEmbeddedComponent>::StaticMethod("constraintSize", &JSEmbeddedComponent::Mock);
    JSClass<JSEmbeddedComponent>::StaticMethod("aspectRatio", &JSEmbeddedComponent::Mock);
    JSClass<JSEmbeddedComponent>::StaticMethod("layoutWeight", &JSEmbeddedComponent::Mock);
    JSClass<JSEmbeddedComponent>::StaticMethod("flexBasis", &JSEmbeddedComponent::Mock);
    JSClass<JSEmbeddedComponent>::StaticMethod("flexGrow", &JSEmbeddedComponent::Mock);
    JSClass<JSEmbeddedComponent>::StaticMethod("flexShrink", &JSEmbeddedComponent::Mock);
    JSClass<JSEmbeddedComponent>::StaticMethod("opacity", &JSEmbeddedComponent::Mock);
    JSClass<JSEmbeddedComponent>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSEmbeddedComponent::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    CreateMockComponent("EmbeddedComponent");
}

void JSEmbeddedComponent::Mock(const JSCallbackInfo& info) {}

void JSIsolatedComponent::JSBind(BindingTarget globalObj)
{
    JSClass<JSIsolatedComponent>::Declare("IsolatedComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSIsolatedComponent>::StaticMethod("create", &JSIsolatedComponent::Create, opt);
    JSClass<JSIsolatedComponent>::StaticMethod("onError", &JSIsolatedComponent::Mock, opt);
    JSClass<JSIsolatedComponent>::StaticMethod("onAppear", &JSIsolatedComponent::Mock);
    JSClass<JSIsolatedComponent>::StaticMethod("onDisAppear", &JSIsolatedComponent::Mock);
    JSClass<JSIsolatedComponent>::StaticMethod("width", &JSIsolatedComponent::Mock, opt);
    JSClass<JSIsolatedComponent>::StaticMethod("height", &JSIsolatedComponent::Mock, opt);
    JSClass<JSIsolatedComponent>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSIsolatedComponent::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    CreateMockComponent("IsolatedComponent");
}

void JSIsolatedComponent::Mock(const JSCallbackInfo& info) {}

void JSRemoteWindow::JSBind(BindingTarget globalObj)
{
    JSClass<JSRemoteWindow>::Declare("RemoteWindow");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSRemoteWindow>::StaticMethod("create", &JSRemoteWindow::Create, opt);

    JSClass<JSRemoteWindow>::StaticMethod("onTouch", &JSRemoteWindow::Mock);
    JSClass<JSRemoteWindow>::StaticMethod("onHover", &JSRemoteWindow::Mock);
    JSClass<JSRemoteWindow>::StaticMethod("onKeyEvent", &JSRemoteWindow::Mock);
    JSClass<JSRemoteWindow>::StaticMethod("onDeleteEvent", &JSRemoteWindow::Mock);
    JSClass<JSRemoteWindow>::StaticMethod("onClick", &JSRemoteWindow::Mock);

    JSClass<JSRemoteWindow>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSRemoteWindow::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CreateMockComponent("RemoteWindow");
}

void JSRemoteWindow::Mock(const JSCallbackInfo& info) {}
} // namespace OHOS::Ace::Framework
