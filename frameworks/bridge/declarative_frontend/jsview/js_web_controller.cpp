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

#include "frameworks/bridge/declarative_frontend/jsview/js_web_controller.h"

#include "base/utils/linear_map.h"
#include "base/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_webview_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {
namespace {
const int32_t WEBVIEW_PARAM_NUMS_EXCUTEJS = 2;
const int32_t WEBVIEW_PARAM_NUMS_LOADURL = 2;
}

void JSWebController::JSBind(BindingTarget globalObj)
{
    JSClass<JSWebController>::Declare("WebController");
    JSClass<JSWebController>::CustomMethod("loadUrl", &JSWebController::LoadUrl);
    JSClass<JSWebController>::CustomMethod("runJavaScript", &JSWebController::ExecuteTypeScript);
    JSClass<JSWebController>::CustomMethod("refresh", &JSWebController::Refresh);
    JSClass<JSWebController>::CustomMethod("stop", &JSWebController::StopLoading);
    JSClass<JSWebController>::CustomMethod("getHitTest", &JSWebController::GetHitTestResult);
    JSClass<JSWebController>::CustomMethod("registerJavaScriptProxy", &JSWebController::AddJavascriptInterface);
    JSClass<JSWebController>::CustomMethod("deleteJavaScriptRegister", &JSWebController::RemoveJavascriptInterface);
    JSClass<JSWebController>::CustomMethod("onInactive", &JSWebController::OnInactive);
    JSClass<JSWebController>::CustomMethod("onActive", &JSWebController::OnActive);
    JSClass<JSWebController>::CustomMethod("requestFocus", &JSWebController::RequestFocus);
    JSClass<JSWebController>::CustomMethod("loadData", &JSWebController::LoadDataWithBaseUrl);
    JSClass<JSWebController>::CustomMethod("backward", &JSWebController::Backward);
    JSClass<JSWebController>::CustomMethod("forward", &JSWebController::Forward);
    JSClass<JSWebController>::CustomMethod("accessStep", &JSWebController::AccessStep);
    JSClass<JSWebController>::CustomMethod("accessForward", &JSWebController::AccessForward);
    JSClass<JSWebController>::CustomMethod("accessBackward", &JSWebController::AccessBackward);
    JSClass<JSWebController>::Bind(globalObj, JSWebController::Constructor, JSWebController::Destructor);
}

void JSWebController::Constructor(const JSCallbackInfo& args)
{
    auto webController = Referenced::MakeRefPtr<JSWebController>();
    webController->IncRefCount();
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    webController->SetController(controller);
    args.SetReturnValue(Referenced::RawPtr(webController));
}

void JSWebController::Destructor(JSWebController* webController)
{
    if (webController != nullptr) {
        webController->DecRefCount();
    }
}

void JSWebController::Reload() const
{
    if (webController_) {
        webController_->Reload();
    }
}

void JSWebController::LoadUrl(const JSCallbackInfo& args)
{
    std::string url;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], url)) {
        return;
    }

    std::map<std::string, std::string> httpHeaders;
    if (args.Length() >= WEBVIEW_PARAM_NUMS_LOADURL && args[1]->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(args[1]);
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> jsValue = array->GetValueAt(i);
            if (!jsValue->IsObject()) {
                continue;
            }

            JSRef<JSObject> obj = JSRef<JSObject>::Cast(jsValue);
            std::string key;
            if (!ConvertFromJSValue(obj->GetProperty("key"), key)) {
                LOGW("can't find key at index %{public}d of additionalHttpHeaders, so skip it.", i);
                continue;
            }
            std::string value;
            if (!ConvertFromJSValue(obj->GetProperty("value"), value)) {
                LOGW("can't find value at index %{public}d of additionalHttpHeaders, so skip it.", i);
                continue;
            }
            httpHeaders[key] = value;
        }
        LOGD("httpHeaders size:%{public}d", (int)httpHeaders.size());
    }

    if (webController_) {
        webController_->LoadUrl(url, httpHeaders);
    }
}

void JSWebController::ExecuteTypeScript(const JSCallbackInfo& args)
{
    std::string jscode;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], jscode)) {
        return;
    }

    std::function<void(std::string)> callback = nullptr;
    if (args.Length() >= WEBVIEW_PARAM_NUMS_EXCUTEJS && args[1]->IsFunction()) {
        auto jsCallback =
            AceType::MakeRefPtr<JsWebViewFunction>(JSRef<JSFunc>::Cast(args[1]));
        callback = [execCtx = args.GetExecutionContext(), func = std::move(jsCallback)](std::string result) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("ExecuteTypeScript CallBack");
            LOGI("About to call ExecuteTypeScript callback method on js");
            func->Execute(result);
        };
    }

    if (webController_) {
        webController_->ExecuteTypeScript(jscode, std::move(callback));
    }
}

void JSWebController::LoadDataWithBaseUrl(const JSCallbackInfo& args)
{
    if (args.Length() >= 1 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);

        std::string data;
        if (!ConvertFromJSValue(obj->GetProperty("data"), data)) {
            return;
        }

        std::string mimeType;
        if (!ConvertFromJSValue(obj->GetProperty("mimeType"), mimeType)) {
            return;
        }

        std::string encoding;
        if (!ConvertFromJSValue(obj->GetProperty("encoding"), encoding)) {
            return;
        }

        std::string baseUrl;
        std::string historyUrl;
        ConvertFromJSValue(obj->GetProperty("baseUrl"), baseUrl);
        ConvertFromJSValue(obj->GetProperty("historyUrl"), historyUrl);
        if (webController_) {
            webController_->LoadDataWithBaseUrl(baseUrl, data, mimeType, encoding, historyUrl);
        }
    }
}

void JSWebController::Backward(const JSCallbackInfo& args)
{
    LOGI("JSWebController Start backward.");
    if (webController_) {
        webController_->Backward();
    }
}

void JSWebController::Forward(const JSCallbackInfo& args)
{
    LOGI("JSWebController Start forward.");
    if (webController_) {
        webController_->Forward();
    }
}

void JSWebController::AccessStep(const JSCallbackInfo& args)
{
    LOGI("JSWebController start accessStep.");
    int32_t step = 0;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], step)) {
        LOGE("AccessStep parameter is invalid.");
        return;
    }
    if (webController_) {
        auto canAccess = webController_->AccessStep(step);
        auto jsVal = JSVal(ToJSValue(canAccess));
        auto returnValue = JSRef<JSVal>::Make(jsVal);
        args.SetReturnValue(returnValue);
    }
}

void JSWebController::AccessBackward(const JSCallbackInfo& args)
{
    LOGI("JSWebController start accessBackward.");
    if (webController_) {
        auto canAccess = webController_->AccessBackward();
        auto jsVal = JSVal(ToJSValue(canAccess));
        auto returnValue = JSRef<JSVal>::Make(jsVal);
        args.SetReturnValue(returnValue);
    }
}

void JSWebController::AccessForward(const JSCallbackInfo& args)
{
    LOGI("JSWebController start accessForward.");
    if (webController_) {
        auto canAccess = webController_->AccessForward();
        auto jsVal = JSVal(ToJSValue(canAccess));
        auto returnValue = JSRef<JSVal>::Make(jsVal);
        args.SetReturnValue(returnValue);
    }
}

void JSWebController::Refresh(const JSCallbackInfo& args)
{
    LOGI("JSWebController Refresh");
    if (webController_) {
        webController_->Refresh();
    }
}

void JSWebController::StopLoading(const JSCallbackInfo& args)
{
    LOGI("JSWebController StopLoading");
    if (webController_) {
        webController_->StopLoading();
    }
}

void JSWebController::GetHitTestResult(const JSCallbackInfo& args)
{
    LOGI("JSWebController get his test result");
    if (webController_) {
        int result = webController_->GetHitTestResult();
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
    }
}

void JSWebController::AddJavascriptInterface(const JSCallbackInfo& args)
{
    LOGI("JSWebController add js interface");
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }
    if (webController_ == nullptr) {
        LOGW("JSWebController not ready");
        return;
    }

    // options
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    // options.name
    std::string objName;
    if (!ConvertFromJSValue(obj->GetProperty("name"), objName)) {
        return;
    }
    // options.methodList
    std::vector<std::string> methods;
    JSRef<JSVal> methodList = obj->GetProperty("methodList");
    JSRef<JSArray> array = JSRef<JSArray>::Cast(methodList);
    if (array->IsArray()) {
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> method = array->GetValueAt(i);
            if (method->IsString()) {
                methods.push_back(method->ToString());
            }
        }
    }

    webController_->AddJavascriptInterface(objName, methods);
}
void JSWebController::RemoveJavascriptInterface(const JSCallbackInfo& args)
{
    LOGI("JSWebController remove js interface");
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }

    // options
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    // options.name
    std::string objName;
    if (!ConvertFromJSValue(obj->GetProperty("name"), objName)) {
        return;
    }
    // options.methodList
    std::vector<std::string> methods;
    JSRef<JSVal> methodList = obj->GetProperty("methodList");
    JSRef<JSArray> array = JSRef<JSArray>::Cast(methodList);
    if (array->IsArray()) {
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> method = array->GetValueAt(i);
            if (method->IsString()) {
                methods.push_back(method->ToString());
            }
        }
    }

    if (webController_) {
        webController_->RemoveJavascriptInterface(objName, methods);
    }
}

void JSWebController::OnInactive(const JSCallbackInfo& args)
{
    if (webController_) {
        webController_->OnInactive();
    }
}

void JSWebController::OnActive(const JSCallbackInfo& args)
{
    if (webController_) {
        webController_->OnActive();
    }
}

void JSWebController::RequestFocus(const JSCallbackInfo& args)
{
    LOGI("JSWebController request focus");
    if (webController_) {
        webController_->RequestFocus();
    }
}
} // namespace OHOS::Ace::Framework