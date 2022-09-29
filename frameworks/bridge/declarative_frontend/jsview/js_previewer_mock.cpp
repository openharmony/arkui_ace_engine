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
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr Dimension DEFAULT_FONT_SIZE = 30.0_px;
}

void CreateMockComponent(const std::string inspectorTag)
{
    auto textComponent = AceType::MakeRefPtr<TextComponent>("This component is not supported on PC Preview.");
    auto textStyle = textComponent->GetTextStyle();
    textStyle.SetFontSize(DEFAULT_FONT_SIZE);
    textComponent->SetTextStyle(textStyle);
    textComponent->SetInspectorTag(inspectorTag);
    ViewStackProcessor::GetInstance()->Push(textComponent);

    RefPtr<BoxComponent> mountBox = ViewStackProcessor::GetInstance()->GetBoxComponent();
    mountBox->SetColor(Color::FromString("#808080"));
}

void JSForm::Create(const JSCallbackInfo& info)
{
    if (info.Length() == 0 || !info[0]->IsObject()) {
        LOGE("form create fail due to FormComponent construct param is empty or type is not Object");
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
    JSClass<JSForm>::StaticMethod("onTouch", &JSForm::Mock);
    JSClass<JSForm>::StaticMethod("onKeyEvent", &JSForm::Mock);
    JSClass<JSForm>::StaticMethod("onDeleteEvent", &JSForm::Mock);
    JSClass<JSForm>::StaticMethod("onClick", &JSForm::Mock);

    JSClass<JSForm>::Inherit<JSViewAbstract>();
    JSClass<JSForm>::Bind<>(globalObj);
}

void JSRichText::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("richtext create error, info is non-valid");
        return;
    }
    LOGE("lihao js Create JSRichText::Create");
    CreateMockComponent("RichTextComponent");
}

void JSRichText::Mock(const JSCallbackInfo& info) {}

void JSRichText::JSBind(BindingTarget globalObj)
{
    JSClass<JSRichText>::Declare("RichText");
    JSClass<JSRichText>::StaticMethod("create", &JSRichText::Create);
    JSClass<JSRichText>::StaticMethod("onStart", &JSRichText::Mock);
    JSClass<JSRichText>::StaticMethod("onComplete", &JSRichText::Mock);
    JSClass<JSRichText>::Inherit<JSViewAbstract>();
    JSClass<JSRichText>::Bind<>(globalObj);
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
        LOGI("web create error, info is invalid");
        return;
    }

    CreateMockComponent("WebComponent");
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
    JSClass<JSWeb>::Inherit<JSViewAbstract>();
    JSClass<JSWeb>::Bind(globalObj);

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
        LOGI("xcomponent create error, info is invalid");
        return;
    }
    CreateMockComponent("XComponentComponent");
}

void JSXComponent::Mock(const JSCallbackInfo& info) {}

void JSXComponent::JSBind(BindingTarget globalObj)
{
    JSClass<JSXComponent>::Declare("XComponent");
    JSClass<JSXComponent>::StaticMethod("create", &JSXComponent::Create);
    JSClass<JSXComponent>::StaticMethod("onLoad", &JSXComponent::Mock);
    JSClass<JSXComponent>::StaticMethod("onDestroy", &JSXComponent::Mock);
    JSClass<JSXComponent>::Inherit<JSViewAbstract>();
    JSClass<JSXComponent>::Bind(globalObj);
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

} // namespace OHOS::Ace::Framework
