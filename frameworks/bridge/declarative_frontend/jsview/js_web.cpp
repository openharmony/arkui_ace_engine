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

#include <optional>
#include <string>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components/web/web_component.h"
#include "core/components/web/web_event.h"
#include "core/components_ng/pattern/web/web_view.h"
#include "core/pipeline/pipeline_base.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_key_function.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_web_controller.h"

namespace OHOS::Ace::Framework {

class JSWebDialog : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebDialog>::Declare("WebDialog");
        JSClass<JSWebDialog>::CustomMethod("handleConfirm", &JSWebDialog::Confirm);
        JSClass<JSWebDialog>::CustomMethod("handleCancel", &JSWebDialog::Cancel);
        JSClass<JSWebDialog>::CustomMethod("handlePromptConfirm", &JSWebDialog::PromptConfirm);
        JSClass<JSWebDialog>::Bind(globalObj, &JSWebDialog::Constructor, &JSWebDialog::Destructor);
    }

    void SetResult(const RefPtr<Result>& result)
    {
        result_ = result;
    }

    void Confirm(const JSCallbackInfo& args)
    {
        if (result_) {
            result_->Confirm();
        }
    }

    void PromptConfirm(const JSCallbackInfo& args)
    {
        std::string message;
        if (!result_) {
            return;
        }
        if (args.Length() == 1 && args[0]->IsString()) {
            message = args[0]->ToString();
            result_->Confirm(message);
        }
    }

    void Cancel(const JSCallbackInfo& args)
    {
        if (result_) {
            result_->Cancel();
        }
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsWebDialog = Referenced::MakeRefPtr<JSWebDialog>();
        jsWebDialog->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsWebDialog));
    }

    static void Destructor(JSWebDialog* jsWebDialog)
    {
        if (jsWebDialog != nullptr) {
            jsWebDialog->DecRefCount();
        }
    }

    RefPtr<Result> result_;
};

class JSWebHttpAuth : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebHttpAuth>::Declare("WebHttpAuthResult");
        JSClass<JSWebHttpAuth>::CustomMethod("confirm", &JSWebHttpAuth::Confirm);
        JSClass<JSWebHttpAuth>::CustomMethod("cancel", &JSWebHttpAuth::Cancel);
        JSClass<JSWebHttpAuth>::CustomMethod("isHttpAuthInfoSaved", &JSWebHttpAuth::IsHttpAuthInfoSaved);
        JSClass<JSWebHttpAuth>::Bind(globalObj, &JSWebHttpAuth::Constructor, &JSWebHttpAuth::Destructor);
    }

    void SetResult(const RefPtr<AuthResult>& result)
    {
        result_ = result;
    }

    void Confirm(const JSCallbackInfo& args)
    {
        if (args.Length() < 2 || !args[0]->IsString() || !args[1]->IsString()) {
            LOGW("web http auth confirm list is not string");
            auto code = JSVal(ToJSValue(false));
            auto descriptionRef = JSRef<JSVal>::Make(code);
            args.SetReturnValue(descriptionRef);
            return;
        }
        std::string userName = args[0]->ToString();
        std::string password = args[1]->ToString();
        bool ret = false;
        if (result_) {
            result_->Confirm(userName, password);
            ret = true;
        }
        auto code = JSVal(ToJSValue(ret));
        auto descriptionRef = JSRef<JSVal>::Make(code);
        args.SetReturnValue(descriptionRef);
    }

    void Cancel(const JSCallbackInfo& args)
    {
        if (result_) {
            result_->Cancel();
        }
    }

    void IsHttpAuthInfoSaved(const JSCallbackInfo& args)
    {
        bool ret = false;
        if (result_) {
            ret = result_->IsHttpAuthInfoSaved();
        }
        auto code = JSVal(ToJSValue(ret));
        auto descriptionRef = JSRef<JSVal>::Make(code);
        args.SetReturnValue(descriptionRef);
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsWebHttpAuth = Referenced::MakeRefPtr<JSWebHttpAuth>();
        jsWebHttpAuth->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsWebHttpAuth));
    }

    static void Destructor(JSWebHttpAuth* jsWebHttpAuth)
    {
        if (jsWebHttpAuth != nullptr) {
            jsWebHttpAuth->DecRefCount();
        }
    }

    RefPtr<AuthResult> result_;
};

class JSWebSslError : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebSslError>::Declare("WebSslErrorResult");
        JSClass<JSWebSslError>::CustomMethod("handleConfirm", &JSWebSslError::HandleConfirm);
        JSClass<JSWebSslError>::CustomMethod("handleCancel", &JSWebSslError::HandleCancel);
        JSClass<JSWebSslError>::Bind(globalObj, &JSWebSslError::Constructor, &JSWebSslError::Destructor);
    }

    void SetResult(const RefPtr<SslErrorResult>& result)
    {
        result_ = result;
    }

    void HandleConfirm(const JSCallbackInfo& args)
    {
        if (result_) {
            result_->HandleConfirm();
        }
    }

    void HandleCancel(const JSCallbackInfo& args)
    {
        if (result_) {
            result_->HandleCancel();
        }
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsWebSslError = Referenced::MakeRefPtr<JSWebSslError>();
        jsWebSslError->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsWebSslError));
    }

    static void Destructor(JSWebSslError* jsWebSslError)
    {
        if (jsWebSslError != nullptr) {
            jsWebSslError->DecRefCount();
        }
    }

    RefPtr<SslErrorResult> result_;
};

class JSWebSslSelectCert : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebSslSelectCert>::Declare("WebSslSelectCertResult");
        JSClass<JSWebSslSelectCert>::CustomMethod("confirm", &JSWebSslSelectCert::HandleConfirm);
        JSClass<JSWebSslSelectCert>::CustomMethod("cancel", &JSWebSslSelectCert::HandleCancel);
        JSClass<JSWebSslSelectCert>::CustomMethod("ignore", &JSWebSslSelectCert::HandleIgnore);
        JSClass<JSWebSslSelectCert>::Bind(globalObj, &JSWebSslSelectCert::Constructor, &JSWebSslSelectCert::Destructor);
    }

    void SetResult(const RefPtr<SslSelectCertResult>& result)
    {
        result_ = result;
    }

    void HandleConfirm(const JSCallbackInfo& args)
    {
        LOGW("JSWebSslSelectCert::HandleConfirm");
        std::string privateKeyFile = args[0]->ToString();
        std::string certChainFile = args[1]->ToString();
        if (result_) {
            result_->HandleConfirm(privateKeyFile, certChainFile);
        }
    }

    void HandleCancel(const JSCallbackInfo& args)
    {
        if (result_) {
            result_->HandleCancel();
        }
    }

    void HandleIgnore(const JSCallbackInfo& args)
    {
        if (result_) {
            result_->HandleIgnore();
        }
    }
private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsWebSslSelectCert = Referenced::MakeRefPtr<JSWebSslSelectCert>();
        jsWebSslSelectCert->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsWebSslSelectCert));
    }

    static void Destructor(JSWebSslSelectCert* jsWebSslSelectCert)
    {
        if (jsWebSslSelectCert != nullptr) {
            jsWebSslSelectCert->DecRefCount();
        }
    }

    RefPtr<SslSelectCertResult> result_;
};

class JSWebConsoleLog : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebConsoleLog>::Declare("ConsoleMessage");
        JSClass<JSWebConsoleLog>::CustomMethod("getLineNumber", &JSWebConsoleLog::GetLineNumber);
        JSClass<JSWebConsoleLog>::CustomMethod("getMessage", &JSWebConsoleLog::GetLog);
        JSClass<JSWebConsoleLog>::CustomMethod("getMessageLevel", &JSWebConsoleLog::GetLogLevel);
        JSClass<JSWebConsoleLog>::CustomMethod("getSourceId", &JSWebConsoleLog::GetSourceId);
        JSClass<JSWebConsoleLog>::Bind(globalObj, &JSWebConsoleLog::Constructor, &JSWebConsoleLog::Destructor);
    }

    void SetMessage(const RefPtr<WebConsoleLog>& message)
    {
        message_ = message;
    }

    void GetLineNumber(const JSCallbackInfo& args)
    {
        auto code = JSVal(ToJSValue(message_->GetLineNumber()));
        auto descriptionRef = JSRef<JSVal>::Make(code);
        args.SetReturnValue(descriptionRef);
    }

    void GetLog(const JSCallbackInfo& args)
    {
        auto code = JSVal(ToJSValue(message_->GetLog()));
        auto descriptionRef = JSRef<JSVal>::Make(code);
        args.SetReturnValue(descriptionRef);
    }

    void GetLogLevel(const JSCallbackInfo& args)
    {
        auto code = JSVal(ToJSValue(message_->GetLogLevel()));
        auto descriptionRef = JSRef<JSVal>::Make(code);
        args.SetReturnValue(descriptionRef);
    }

    void GetSourceId(const JSCallbackInfo& args)
    {
        auto code = JSVal(ToJSValue(message_->GetSourceId()));
        auto descriptionRef = JSRef<JSVal>::Make(code);
        args.SetReturnValue(descriptionRef);
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsWebConsoleLog = Referenced::MakeRefPtr<JSWebConsoleLog>();
        jsWebConsoleLog->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsWebConsoleLog));
    }

    static void Destructor(JSWebConsoleLog* jsWebConsoleLog)
    {
        if (jsWebConsoleLog != nullptr) {
            jsWebConsoleLog->DecRefCount();
        }
    }

    RefPtr<WebConsoleLog> message_;
};

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
        if (webGeolocation_) {
            webGeolocation_->Invoke(origin, allow, retain);
        }
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

class JSWebPermissionRequest : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebPermissionRequest>::Declare("WebPermissionRequest");
        JSClass<JSWebPermissionRequest>::CustomMethod("deny", &JSWebPermissionRequest::Deny);
        JSClass<JSWebPermissionRequest>::CustomMethod("getOrigin", &JSWebPermissionRequest::GetOrigin);
        JSClass<JSWebPermissionRequest>::CustomMethod("getAccessibleResource", &JSWebPermissionRequest::GetResources);
        JSClass<JSWebPermissionRequest>::CustomMethod("grant", &JSWebPermissionRequest::Grant);
        JSClass<JSWebPermissionRequest>::Bind(
            globalObj, &JSWebPermissionRequest::Constructor, &JSWebPermissionRequest::Destructor);
    }

    void SetEvent(const WebPermissionRequestEvent& eventInfo)
    {
        webPermissionRequest_ = eventInfo.GetWebPermissionRequest();
    }

    void Deny(const JSCallbackInfo& args)
    {
        if (webPermissionRequest_) {
            webPermissionRequest_->Deny();
        }
    }

    void GetOrigin(const JSCallbackInfo& args)
    {
        std::string origin;
        if (webPermissionRequest_) {
            origin = webPermissionRequest_->GetOrigin();
        }
        auto originJs = JSVal(ToJSValue(origin));
        auto originJsRef = JSRef<JSVal>::Make(originJs);
        args.SetReturnValue(originJsRef);
    }

    void GetResources(const JSCallbackInfo& args)
    {
        JSRef<JSArray> result = JSRef<JSArray>::New();
        if (webPermissionRequest_) {
            std::vector<std::string> resources = webPermissionRequest_->GetResources();
            uint32_t index = 0;
            for (auto iterator = resources.begin(); iterator != resources.end(); ++iterator) {
                auto valueStr = JSVal(ToJSValue(*iterator));
                auto value = JSRef<JSVal>::Make(valueStr);
                result->SetValueAt(index++, value);
            }
        }
        args.SetReturnValue(result);
    }

    void Grant(const JSCallbackInfo& args)
    {
        if (args.Length() < 1) {
            if (webPermissionRequest_) {
                webPermissionRequest_->Deny();
            }
        }
        std::vector<std::string> resources;
        if (args[0]->IsArray()) {
            JSRef<JSArray> array = JSRef<JSArray>::Cast(args[0]);
            for (size_t i = 0; i < array->Length(); i++) {
                JSRef<JSVal> val = array->GetValueAt(i);
                if (!val->IsString()) {
                    LOGW("resources list is not string at index %{public}zu", i);
                    continue;
                }
                std::string res;
                if (!ConvertFromJSValue(val, res)) {
                    LOGW("can't convert resource at index %{public}zu of JSWebPermissionRequest, so skip it.", i);
                    continue;
                }
                resources.push_back(res);
            }
        }

        if (webPermissionRequest_) {
            webPermissionRequest_->Grant(resources);
        }
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsWebPermissionRequest = Referenced::MakeRefPtr<JSWebPermissionRequest>();
        jsWebPermissionRequest->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsWebPermissionRequest));
    }

    static void Destructor(JSWebPermissionRequest* jsWebPermissionRequest)
    {
        if (jsWebPermissionRequest != nullptr) {
            jsWebPermissionRequest->DecRefCount();
        }
    }

    RefPtr<WebPermissionRequest> webPermissionRequest_;
};

class JSWebResourceError : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebResourceError>::Declare("WebResourceError");
        JSClass<JSWebResourceError>::CustomMethod("getErrorCode", &JSWebResourceError::GetErrorCode);
        JSClass<JSWebResourceError>::CustomMethod("getErrorInfo", &JSWebResourceError::GetErrorInfo);
        JSClass<JSWebResourceError>::Bind(globalObj, &JSWebResourceError::Constructor, &JSWebResourceError::Destructor);
    }

    void SetEvent(const ReceivedErrorEvent& eventInfo)
    {
        error_ = eventInfo.GetError();
    }

    void GetErrorCode(const JSCallbackInfo& args)
    {
        auto code = JSVal(ToJSValue(error_->GetCode()));
        auto descriptionRef = JSRef<JSVal>::Make(code);
        args.SetReturnValue(descriptionRef);
    }

    void GetErrorInfo(const JSCallbackInfo& args)
    {
        auto info = JSVal(ToJSValue(error_->GetInfo()));
        auto descriptionRef = JSRef<JSVal>::Make(info);
        args.SetReturnValue(descriptionRef);
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jSWebResourceError = Referenced::MakeRefPtr<JSWebResourceError>();
        jSWebResourceError->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jSWebResourceError));
    }

    static void Destructor(JSWebResourceError* jSWebResourceError)
    {
        if (jSWebResourceError != nullptr) {
            jSWebResourceError->DecRefCount();
        }
    }

    RefPtr<WebError> error_;
};

class JSWebResourceResponse : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebResourceResponse>::Declare("WebResourceResponse");
        JSClass<JSWebResourceResponse>::CustomMethod("getResponseData", &JSWebResourceResponse::GetResponseData);
        JSClass<JSWebResourceResponse>::CustomMethod(
            "getResponseEncoding", &JSWebResourceResponse::GetResponseEncoding);
        JSClass<JSWebResourceResponse>::CustomMethod(
            "getResponseMimeType", &JSWebResourceResponse::GetResponseMimeType);
        JSClass<JSWebResourceResponse>::CustomMethod("getReasonMessage", &JSWebResourceResponse::GetReasonMessage);
        JSClass<JSWebResourceResponse>::CustomMethod("getResponseCode", &JSWebResourceResponse::GetResponseCode);
        JSClass<JSWebResourceResponse>::CustomMethod("getResponseHeader", &JSWebResourceResponse::GetResponseHeader);
        JSClass<JSWebResourceResponse>::CustomMethod("setResponseData", &JSWebResourceResponse::SetResponseData);
        JSClass<JSWebResourceResponse>::CustomMethod(
            "setResponseEncoding", &JSWebResourceResponse::SetResponseEncoding);
        JSClass<JSWebResourceResponse>::CustomMethod(
            "setResponseMimeType", &JSWebResourceResponse::SetResponseMimeType);
        JSClass<JSWebResourceResponse>::CustomMethod("setReasonMessage", &JSWebResourceResponse::SetReasonMessage);
        JSClass<JSWebResourceResponse>::CustomMethod("setResponseCode", &JSWebResourceResponse::SetResponseCode);
        JSClass<JSWebResourceResponse>::CustomMethod("setResponseHeader", &JSWebResourceResponse::SetResponseHeader);
        JSClass<JSWebResourceResponse>::CustomMethod("setResponseIsReady", &JSWebResourceResponse::SetResponseIsReady);
        JSClass<JSWebResourceResponse>::Bind(
            globalObj, &JSWebResourceResponse::Constructor, &JSWebResourceResponse::Destructor);
    }

    JSWebResourceResponse()
    {
        response_ = AceType::MakeRefPtr<WebResponse>();
    }

    void SetEvent(const ReceivedHttpErrorEvent& eventInfo)
    {
        response_ = eventInfo.GetResponse();
    }

    void GetResponseData(const JSCallbackInfo& args)
    {
        auto data = JSVal(ToJSValue(response_->GetData()));
        auto descriptionRef = JSRef<JSVal>::Make(data);
        args.SetReturnValue(descriptionRef);
    }

    void GetResponseEncoding(const JSCallbackInfo& args)
    {
        auto encoding = JSVal(ToJSValue(response_->GetEncoding()));
        auto descriptionRef = JSRef<JSVal>::Make(encoding);
        args.SetReturnValue(descriptionRef);
    }

    void GetResponseMimeType(const JSCallbackInfo& args)
    {
        auto mimeType = JSVal(ToJSValue(response_->GetMimeType()));
        auto descriptionRef = JSRef<JSVal>::Make(mimeType);
        args.SetReturnValue(descriptionRef);
    }

    void GetReasonMessage(const JSCallbackInfo& args)
    {
        auto reason = JSVal(ToJSValue(response_->GetReason()));
        auto descriptionRef = JSRef<JSVal>::Make(reason);
        args.SetReturnValue(descriptionRef);
    }

    void GetResponseCode(const JSCallbackInfo& args)
    {
        auto code = JSVal(ToJSValue(response_->GetStatusCode()));
        auto descriptionRef = JSRef<JSVal>::Make(code);
        args.SetReturnValue(descriptionRef);
    }

    void GetResponseHeader(const JSCallbackInfo& args)
    {
        auto map = response_->GetHeaders();
        std::map<std::string, std::string>::iterator iterator;
        uint32_t index = 0;
        JSRef<JSArray> headers = JSRef<JSArray>::New();
        for (iterator = map.begin(); iterator != map.end(); ++iterator) {
            JSRef<JSObject> header = JSRef<JSObject>::New();
            header->SetProperty("headerKey", iterator->first);
            header->SetProperty("headerValue", iterator->second);
            headers->SetValueAt(index++, header);
        }
        args.SetReturnValue(headers);
    }

    RefPtr<WebResponse> GetResponseObj() const
    {
        return response_;
    }

    void SetResponseData(const JSCallbackInfo& args)
    {
        if (args.Length() <= 0) {
            return;
        }
        if (args[0]->IsNumber()) {
            auto fd = args[0]->ToNumber<int32_t>();
            LOGI("intercept set data file handle %{public}d", fd);
            response_->SetFileHandle(fd);
            return;
        }
        if (args[0]->IsString()) {
            LOGI("intercept set data string");
            auto data = args[0]->ToString();
            response_->SetData(data);
            return;
        }
    }

    void SetResponseEncoding(const JSCallbackInfo& args)
    {
        if ((args.Length() <= 0) || !(args[0]->IsString())) {
            return;
        }
        auto encode = args[0]->ToString();
        response_->SetEncoding(encode);
    }

    void SetResponseMimeType(const JSCallbackInfo& args)
    {
        if ((args.Length() <= 0) || !(args[0]->IsString())) {
            return;
        }
        auto mineType = args[0]->ToString();
        response_->SetMimeType(mineType);
    }

    void SetReasonMessage(const JSCallbackInfo& args)
    {
        if ((args.Length() <= 0) || !(args[0]->IsString())) {
            return;
        }
        auto reason = args[0]->ToString();
        response_->SetReason(reason);
    }

    void SetResponseCode(const JSCallbackInfo& args)
    {
        if ((args.Length() <= 0) || !(args[0]->IsNumber())) {
            return;
        }
        auto statusCode = args[0]->ToNumber<int32_t>();
        response_->SetStatusCode(statusCode);
    }

    void SetResponseHeader(const JSCallbackInfo& args)
    {
        if ((args.Length() <= 0) || !(args[0]->IsArray())) {
            return;
        }
        JSRef<JSArray> array = JSRef<JSArray>::Cast(args[0]);
        for (size_t i = 0; i < array->Length(); i++) {
            auto obj = JSRef<JSObject>::Cast(array->GetValueAt(i));
            auto headerKey = obj->GetProperty("headerKey");
            auto headerValue = obj->GetProperty("headerValue");
            if (!headerKey->IsString() || !headerValue->IsString()) {
                LOGE("headerKey or headerValue is undefined");
                return;
            }
            auto keystr = headerKey->ToString();
            auto valstr = headerValue->ToString();
            LOGI("Set Response Header %{public}s:%{public}s", keystr.c_str(), valstr.c_str());
            response_->SetHeadersVal(keystr, valstr);
        }
    }

    void SetResponseIsReady(const JSCallbackInfo& args)
    {
        if ((args.Length() <= 0) || !(args[0]->IsBoolean())) {
            return;
        }
        bool isReady = false;
        if (!ConvertFromJSValue(args[0], isReady)) {
            LOGE("get response status fail");
            return;
        }
        LOGI("intercept set response status is %{public}d", isReady);
        response_->SetResponseStatus(isReady);
    }
private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jSWebResourceResponse = Referenced::MakeRefPtr<JSWebResourceResponse>();
        jSWebResourceResponse->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jSWebResourceResponse));
    }

    static void Destructor(JSWebResourceResponse* jSWebResourceResponse)
    {
        if (jSWebResourceResponse != nullptr) {
            jSWebResourceResponse->DecRefCount();
        }
    }

    RefPtr<WebResponse> response_;
};

class JSWebResourceRequest : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebResourceRequest>::Declare("WebResourceRequest");
        JSClass<JSWebResourceRequest>::CustomMethod("getRequestUrl", &JSWebResourceRequest::GetRequestUrl);
        JSClass<JSWebResourceRequest>::CustomMethod("getRequestHeader", &JSWebResourceRequest::GetRequestHeader);
        JSClass<JSWebResourceRequest>::CustomMethod("isRequestGesture", &JSWebResourceRequest::IsRequestGesture);
        JSClass<JSWebResourceRequest>::CustomMethod("isMainFrame", &JSWebResourceRequest::IsMainFrame);
        JSClass<JSWebResourceRequest>::CustomMethod("isRedirect", &JSWebResourceRequest::IsRedirect);
        JSClass<JSWebResourceRequest>::Bind(
            globalObj, &JSWebResourceRequest::Constructor, &JSWebResourceRequest::Destructor);
    }

    void SetErrorEvent(const ReceivedErrorEvent& eventInfo)
    {
        request_ = eventInfo.GetRequest();
    }

    void SetHttpErrorEvent(const ReceivedHttpErrorEvent& eventInfo)
    {
        request_ = eventInfo.GetRequest();
    }

    void SetOnInterceptRequestEvent(const OnInterceptRequestEvent& eventInfo)
    {
        request_ = eventInfo.GetRequest();
    }

    void IsRedirect(const JSCallbackInfo& args)
    {
        auto isRedirect = JSVal(ToJSValue(request_->IsRedirect()));
        auto descriptionRef = JSRef<JSVal>::Make(isRedirect);
        args.SetReturnValue(descriptionRef);
    }

    void GetRequestUrl(const JSCallbackInfo& args)
    {
        auto url = JSVal(ToJSValue(request_->GetUrl()));
        auto descriptionRef = JSRef<JSVal>::Make(url);
        args.SetReturnValue(descriptionRef);
    }

    void IsRequestGesture(const JSCallbackInfo& args)
    {
        auto isRequestGesture = JSVal(ToJSValue(request_->HasGesture()));
        auto descriptionRef = JSRef<JSVal>::Make(isRequestGesture);
        args.SetReturnValue(descriptionRef);
    }

    void IsMainFrame(const JSCallbackInfo& args)
    {
        auto isMainFrame = JSVal(ToJSValue(request_->IsMainFrame()));
        auto descriptionRef = JSRef<JSVal>::Make(isMainFrame);
        args.SetReturnValue(descriptionRef);
    }

    void GetRequestHeader(const JSCallbackInfo& args)
    {
        auto map = request_->GetHeaders();
        std::map<std::string, std::string>::iterator iterator;
        uint32_t index = 0;
        JSRef<JSArray> headers = JSRef<JSArray>::New();
        for (iterator = map.begin(); iterator != map.end(); ++iterator) {
            JSRef<JSObject> header = JSRef<JSObject>::New();
            header->SetProperty("headerKey", iterator->first);
            header->SetProperty("headerValue", iterator->second);
            headers->SetValueAt(index++, header);
        }
        args.SetReturnValue(headers);
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jSWebResourceRequest = Referenced::MakeRefPtr<JSWebResourceRequest>();
        jSWebResourceRequest->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jSWebResourceRequest));
    }

    static void Destructor(JSWebResourceRequest* jSWebResourceRequest)
    {
        if (jSWebResourceRequest != nullptr) {
            jSWebResourceRequest->DecRefCount();
        }
    }

    RefPtr<WebRequest> request_;
};

class JSFileSelectorParam : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSFileSelectorParam>::Declare("FileSelectorParam");
        JSClass<JSFileSelectorParam>::CustomMethod("getTitle", &JSFileSelectorParam::GetTitle);
        JSClass<JSFileSelectorParam>::CustomMethod("getMode", &JSFileSelectorParam::GetMode);
        JSClass<JSFileSelectorParam>::CustomMethod("getAcceptType", &JSFileSelectorParam::GetAcceptType);
        JSClass<JSFileSelectorParam>::CustomMethod("isCapture", &JSFileSelectorParam::IsCapture);
        JSClass<JSFileSelectorParam>::Bind(
            globalObj, &JSFileSelectorParam::Constructor, &JSFileSelectorParam::Destructor);
    }

    void SetParam(const FileSelectorEvent& eventInfo)
    {
        param_ = eventInfo.GetParam();
    }

    void GetTitle(const JSCallbackInfo& args)
    {
        auto title = JSVal(ToJSValue(param_->GetTitle()));
        auto descriptionRef = JSRef<JSVal>::Make(title);
        args.SetReturnValue(descriptionRef);
    }

    void GetMode(const JSCallbackInfo& args)
    {
        auto mode = JSVal(ToJSValue(param_->GetMode()));
        auto descriptionRef = JSRef<JSVal>::Make(mode);
        args.SetReturnValue(descriptionRef);
    }

    void IsCapture(const JSCallbackInfo& args)
    {
        auto isCapture = JSVal(ToJSValue(param_->IsCapture()));
        auto descriptionRef = JSRef<JSVal>::Make(isCapture);
        args.SetReturnValue(descriptionRef);
    }

    void GetAcceptType(const JSCallbackInfo& args)
    {
        auto acceptTypes = param_->GetAcceptType();
        JSRef<JSArray> result = JSRef<JSArray>::New();
        std::vector<std::string>::iterator iterator;
        uint32_t index = 0;
        for (iterator = acceptTypes.begin(); iterator != acceptTypes.end(); ++iterator) {
            auto valueStr = JSVal(ToJSValue(*iterator));
            auto value = JSRef<JSVal>::Make(valueStr);
            result->SetValueAt(index++, value);
        }
        args.SetReturnValue(result);
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jSFilerSelectorParam = Referenced::MakeRefPtr<JSFileSelectorParam>();
        jSFilerSelectorParam->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jSFilerSelectorParam));
    }

    static void Destructor(JSFileSelectorParam* jSFilerSelectorParam)
    {
        if (jSFilerSelectorParam != nullptr) {
            jSFilerSelectorParam->DecRefCount();
        }
    }

    RefPtr<WebFileSelectorParam> param_;
};

class JSFileSelectorResult : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSFileSelectorResult>::Declare("FileSelectorResult");
        JSClass<JSFileSelectorResult>::CustomMethod("handleFileList", &JSFileSelectorResult::HandleFileList);
        JSClass<JSFileSelectorResult>::Bind(
            globalObj, &JSFileSelectorResult::Constructor, &JSFileSelectorResult::Destructor);
    }

    void SetResult(const FileSelectorEvent& eventInfo)
    {
        result_ = eventInfo.GetFileSelectorResult();
    }

    void HandleFileList(const JSCallbackInfo& args)
    {
        std::vector<std::string> fileList;
        if (args[0]->IsArray()) {
            JSRef<JSArray> array = JSRef<JSArray>::Cast(args[0]);
            for (size_t i = 0; i < array->Length(); i++) {
                JSRef<JSVal> val = array->GetValueAt(i);
                if (!val->IsString()) {
                    LOGW("file selector list is not string at index %{public}zu", i);
                    continue;
                }
                std::string fileName;
                if (!ConvertFromJSValue(val, fileName)) {
                    LOGW("can't convert file name at index %{public}zu of JSFileSelectorResult, so skip it.", i);
                    continue;
                }
                fileList.push_back(fileName);
            }
        }

        if (result_) {
            result_->HandleFileList(fileList);
        }
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsFileSelectorResult = Referenced::MakeRefPtr<JSFileSelectorResult>();
        jsFileSelectorResult->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsFileSelectorResult));
    }

    static void Destructor(JSFileSelectorResult* jsFileSelectorResult)
    {
        if (jsFileSelectorResult != nullptr) {
            jsFileSelectorResult->DecRefCount();
        }
    }

    RefPtr<FileSelectorResult> result_;
};

class JSContextMenuParam : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSContextMenuParam>::Declare("WebContextMenuParam");
        JSClass<JSContextMenuParam>::CustomMethod("x", &JSContextMenuParam::GetXCoord);
        JSClass<JSContextMenuParam>::CustomMethod("y", &JSContextMenuParam::GetYCoord);
        JSClass<JSContextMenuParam>::CustomMethod("getLinkUrl", &JSContextMenuParam::GetLinkUrl);
        JSClass<JSContextMenuParam>::CustomMethod("getUnfilterendLinkUrl", &JSContextMenuParam::GetUnfilteredLinkUrl);
        JSClass<JSContextMenuParam>::CustomMethod("getSourceUrl", &JSContextMenuParam::GetSourceUrl);
        JSClass<JSContextMenuParam>::CustomMethod("existsImageContents", &JSContextMenuParam::HasImageContents);
        JSClass<JSContextMenuParam>::Bind(globalObj, &JSContextMenuParam::Constructor, &JSContextMenuParam::Destructor);
    }

    void SetParam(const ContextMenuEvent& eventInfo)
    {
        param_ = eventInfo.GetParam();
    }

    void GetXCoord(const JSCallbackInfo& args)
    {
        int32_t ret = -1;
        if (param_) {
            ret = param_->GetXCoord();
        }
        auto xCoord = JSVal(ToJSValue(ret));
        auto descriptionRef = JSRef<JSVal>::Make(xCoord);
        args.SetReturnValue(descriptionRef);
    }

    void GetYCoord(const JSCallbackInfo& args)
    {
        int32_t ret = -1;
        if (param_) {
            ret = param_->GetYCoord();
        }
        auto yCoord = JSVal(ToJSValue(ret));
        auto descriptionRef = JSRef<JSVal>::Make(yCoord);
        args.SetReturnValue(descriptionRef);
    }

    void GetLinkUrl(const JSCallbackInfo& args)
    {
        std::string url;
        if (param_) {
            url = param_->GetLinkUrl();
        }
        auto linkUrl = JSVal(ToJSValue(url));
        auto descriptionRef = JSRef<JSVal>::Make(linkUrl);
        args.SetReturnValue(descriptionRef);
    }

    void GetUnfilteredLinkUrl(const JSCallbackInfo& args)
    {
        std::string url;
        if (param_) {
            url = param_->GetUnfilteredLinkUrl();
        }
        auto unfilteredLinkUrl = JSVal(ToJSValue(url));
        auto descriptionRef = JSRef<JSVal>::Make(unfilteredLinkUrl);
        args.SetReturnValue(descriptionRef);
    }

    void GetSourceUrl(const JSCallbackInfo& args)
    {
        std::string url;
        if (param_) {
            url = param_->GetSourceUrl();
        }
        auto sourceUrl = JSVal(ToJSValue(url));
        auto descriptionRef = JSRef<JSVal>::Make(sourceUrl);
        args.SetReturnValue(descriptionRef);
    }

    void HasImageContents(const JSCallbackInfo& args)
    {
        bool ret = false;
        if (param_) {
            ret = param_->HasImageContents();
        }
        auto hasImageContents = JSVal(ToJSValue(ret));
        auto descriptionRef = JSRef<JSVal>::Make(hasImageContents);
        args.SetReturnValue(descriptionRef);
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jSContextMenuParam = Referenced::MakeRefPtr<JSContextMenuParam>();
        jSContextMenuParam->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jSContextMenuParam));
    }

    static void Destructor(JSContextMenuParam* jSContextMenuParam)
    {
        if (jSContextMenuParam != nullptr) {
            jSContextMenuParam->DecRefCount();
        }
    }

    RefPtr<WebContextMenuParam> param_;
};

class JSContextMenuResult : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSContextMenuResult>::Declare("WebContextMenuResult");
        JSClass<JSContextMenuResult>::CustomMethod("closeContextMenu", &JSContextMenuResult::Cancel);
        JSClass<JSContextMenuResult>::CustomMethod("copyImage", &JSContextMenuResult::CopyImage);
        JSClass<JSContextMenuResult>::Bind(
            globalObj, &JSContextMenuResult::Constructor, &JSContextMenuResult::Destructor);
    }

    void SetResult(const ContextMenuEvent& eventInfo)
    {
        result_ = eventInfo.GetContextMenuResult();
    }

    void Cancel(const JSCallbackInfo& args)
    {
        if (result_) {
            result_->Cancel();
        }
    }

    void CopyImage(const JSCallbackInfo& args)
    {
        if (result_) {
            result_->CopyImage();
        }
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsContextMenuResult = Referenced::MakeRefPtr<JSContextMenuResult>();
        jsContextMenuResult->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsContextMenuResult));
    }

    static void Destructor(JSContextMenuResult* jsContextMenuResult)
    {
        if (jsContextMenuResult != nullptr) {
            jsContextMenuResult->DecRefCount();
        }
    }

    RefPtr<ContextMenuResult> result_;
};

void JSWeb::JSBind(BindingTarget globalObj)
{
    JSClass<JSWeb>::Declare("Web");
    JSClass<JSWeb>::StaticMethod("create", &JSWeb::Create);
    JSClass<JSWeb>::StaticMethod("onAlert", &JSWeb::OnAlert);
    JSClass<JSWeb>::StaticMethod("onBeforeUnload", &JSWeb::OnBeforeUnload);
    JSClass<JSWeb>::StaticMethod("onConfirm", &JSWeb::OnConfirm);
    JSClass<JSWeb>::StaticMethod("onPrompt", &JSWeb::OnPrompt);
    JSClass<JSWeb>::StaticMethod("onConsole", &JSWeb::OnConsoleLog);
    JSClass<JSWeb>::StaticMethod("onPageBegin", &JSWeb::OnPageStart);
    JSClass<JSWeb>::StaticMethod("onPageEnd", &JSWeb::OnPageFinish);
    JSClass<JSWeb>::StaticMethod("onProgressChange", &JSWeb::OnProgressChange);
    JSClass<JSWeb>::StaticMethod("onTitleReceive", &JSWeb::OnTitleReceive);
    JSClass<JSWeb>::StaticMethod("onGeolocationHide", &JSWeb::OnGeolocationHide);
    JSClass<JSWeb>::StaticMethod("onGeolocationShow", &JSWeb::OnGeolocationShow);
    JSClass<JSWeb>::StaticMethod("onRequestSelected", &JSWeb::OnRequestFocus);
    JSClass<JSWeb>::StaticMethod("onShowFileSelector", &JSWeb::OnFileSelectorShow);
    JSClass<JSWeb>::StaticMethod("javaScriptAccess", &JSWeb::JsEnabled);
    JSClass<JSWeb>::StaticMethod("fileExtendAccess", &JSWeb::ContentAccessEnabled);
    JSClass<JSWeb>::StaticMethod("fileAccess", &JSWeb::FileAccessEnabled);
    JSClass<JSWeb>::StaticMethod("onDownloadStart", &JSWeb::OnDownloadStart);
    JSClass<JSWeb>::StaticMethod("onErrorReceive", &JSWeb::OnErrorReceive);
    JSClass<JSWeb>::StaticMethod("onHttpErrorReceive", &JSWeb::OnHttpErrorReceive);
    JSClass<JSWeb>::StaticMethod("onInterceptRequest", &JSWeb::OnInterceptRequest);
    JSClass<JSWeb>::StaticMethod("onUrlLoadIntercept", &JSWeb::OnUrlLoadIntercept);
    JSClass<JSWeb>::StaticMethod("onlineImageAccess", &JSWeb::OnLineImageAccessEnabled);
    JSClass<JSWeb>::StaticMethod("domStorageAccess", &JSWeb::DomStorageAccessEnabled);
    JSClass<JSWeb>::StaticMethod("imageAccess", &JSWeb::ImageAccessEnabled);
    JSClass<JSWeb>::StaticMethod("mixedMode", &JSWeb::MixedMode);
    JSClass<JSWeb>::StaticMethod("zoomAccess", &JSWeb::ZoomAccessEnabled);
    JSClass<JSWeb>::StaticMethod("geolocationAccess", &JSWeb::GeolocationAccessEnabled);
    JSClass<JSWeb>::StaticMethod("javaScriptProxy", &JSWeb::JavaScriptProxy);
    JSClass<JSWeb>::StaticMethod("userAgent", &JSWeb::UserAgent);
    JSClass<JSWeb>::StaticMethod("onRenderExited", &JSWeb::OnRenderExited);
    JSClass<JSWeb>::StaticMethod("onRefreshAccessedHistory", &JSWeb::OnRefreshAccessedHistory);
    JSClass<JSWeb>::StaticMethod("cacheMode", &JSWeb::CacheMode);
    JSClass<JSWeb>::StaticMethod("overviewModeAccess", &JSWeb::OverviewModeAccess);
    JSClass<JSWeb>::StaticMethod("fileFromUrlAccess", &JSWeb::FileFromUrlAccess);
    JSClass<JSWeb>::StaticMethod("databaseAccess", &JSWeb::DatabaseAccess);
    JSClass<JSWeb>::StaticMethod("textZoomRatio", &JSWeb::TextZoomRatio);
    JSClass<JSWeb>::StaticMethod("textZoomAtio", &JSWeb::TextZoomRatio);
    JSClass<JSWeb>::StaticMethod("webDebuggingAccess", &JSWeb::WebDebuggingAccessEnabled);
    JSClass<JSWeb>::StaticMethod("initialScale", &JSWeb::InitialScale);
    JSClass<JSWeb>::StaticMethod("backgroundColor", &JSWeb::BackgroundColor);
    JSClass<JSWeb>::StaticMethod("onKeyEvent", &JSWeb::OnKeyEvent);
    JSClass<JSWeb>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSWeb>::StaticMethod("onMouse", &JSWeb::OnMouse);
    JSClass<JSWeb>::StaticMethod("onResourceLoad", &JSWeb::OnResourceLoad);
    JSClass<JSWeb>::StaticMethod("onScaleChange", &JSWeb::OnScaleChange);
    JSClass<JSWeb>::StaticMethod("password", &JSWeb::Password);
    JSClass<JSWeb>::StaticMethod("tableData", &JSWeb::TableData);
    JSClass<JSWeb>::StaticMethod("onFileSelectorShow", &JSWeb::OnFileSelectorShowAbandoned);
    JSClass<JSWeb>::StaticMethod("onHttpAuthRequest", &JSWeb::OnHttpAuthRequest);
    JSClass<JSWeb>::StaticMethod("onSslErrorEventReceive", &JSWeb::OnSslErrorRequest);
    JSClass<JSWeb>::StaticMethod("onClientAuthenticationRequest", &JSWeb::OnSslSelectCertRequest);
    JSClass<JSWeb>::StaticMethod("onPermissionRequest", &JSWeb::OnPermissionRequest);
    JSClass<JSWeb>::StaticMethod("onContextMenuShow", &JSWeb::OnContextMenuShow);
    JSClass<JSWeb>::StaticMethod("onSearchResultReceive", &JSWeb::OnSearchResultReceive);
    JSClass<JSWeb>::StaticMethod("mediaPlayGestureAccess", &JSWeb::MediaPlayGestureAccess);
    JSClass<JSWeb>::StaticMethod("onDragStart", &JSWeb::JsOnDragStart);
    JSClass<JSWeb>::StaticMethod("onDragEnter", &JSWeb::JsOnDragEnter);
    JSClass<JSWeb>::StaticMethod("onDragMove", &JSWeb::JsOnDragMove);
    JSClass<JSWeb>::StaticMethod("onDragLeave", &JSWeb::JsOnDragLeave);
    JSClass<JSWeb>::StaticMethod("onDrop", &JSWeb::JsOnDrop);
    JSClass<JSWeb>::StaticMethod("onScroll", &JSWeb::OnScroll);
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
    JSWebPermissionRequest::JSBind(globalObj);
    JSContextMenuParam::JSBind(globalObj);
    JSContextMenuResult::JSBind(globalObj);
}

JSRef<JSVal> LoadWebConsoleLogEventToJSValue(const LoadWebConsoleLogEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();

    JSRef<JSObject> messageObj = JSClass<JSWebConsoleLog>::NewInstance();
    auto jsWebConsoleLog = Referenced::Claim(messageObj->Unwrap<JSWebConsoleLog>());
    jsWebConsoleLog->SetMessage(eventInfo.GetMessage());

    obj->SetPropertyObject("message", messageObj);

    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> WebDialogEventToJSValue(const WebDialogEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();

    JSRef<JSObject> resultObj = JSClass<JSWebDialog>::NewInstance();
    auto jsWebDialog = Referenced::Claim(resultObj->Unwrap<JSWebDialog>());
    jsWebDialog->SetResult(eventInfo.GetResult());

    obj->SetProperty("url", eventInfo.GetUrl());
    obj->SetProperty("message", eventInfo.GetMessage());
    if (eventInfo.GetType() == DialogEventType::DIALOG_EVENT_PROMPT) {
        obj->SetProperty("value", eventInfo.GetValue());
    }
    obj->SetPropertyObject("result", resultObj);

    return JSRef<JSVal>::Cast(obj);
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

JSRef<JSVal> UrlLoadInterceptEventToJSValue(const UrlLoadInterceptEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("data", eventInfo.GetData());
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

JSRef<JSVal> WebHttpAuthEventToJSValue(const WebHttpAuthEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSObject> resultObj = JSClass<JSWebHttpAuth>::NewInstance();
    auto jsWebHttpAuth = Referenced::Claim(resultObj->Unwrap<JSWebHttpAuth>());
    if (!jsWebHttpAuth) {
        LOGE("jsWebHttpAuth is nullptr");
        return JSRef<JSVal>::Cast(obj);
    }
    jsWebHttpAuth->SetResult(eventInfo.GetResult());
    obj->SetPropertyObject("handler", resultObj);
    obj->SetProperty("host", eventInfo.GetHost());
    obj->SetProperty("realm", eventInfo.GetRealm());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> WebSslErrorEventToJSValue(const WebSslErrorEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSObject> resultObj = JSClass<JSWebSslError>::NewInstance();
    auto jsWebSslError = Referenced::Claim(resultObj->Unwrap<JSWebSslError>());
    if (!jsWebSslError) {
        LOGE("jsWebSslError is nullptr");
        return JSRef<JSVal>::Cast(obj);
    }
    jsWebSslError->SetResult(eventInfo.GetResult());
    obj->SetPropertyObject("handler", resultObj);
    obj->SetProperty("error", eventInfo.GetError());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> WebSslSelectCertEventToJSValue(const WebSslSelectCertEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSObject> resultObj = JSClass<JSWebSslSelectCert>::NewInstance();
    auto jsWebSslSelectCert = Referenced::Claim(resultObj->Unwrap<JSWebSslSelectCert>());
    if (!jsWebSslSelectCert) {
        LOGE("jsWebSslSelectCert is nullptr");
        return JSRef<JSVal>::Cast(obj);
    }
    jsWebSslSelectCert->SetResult(eventInfo.GetResult());
    obj->SetPropertyObject("handler", resultObj);
    obj->SetProperty("host", eventInfo.GetHost());
    obj->SetProperty("port", eventInfo.GetPort());

    JSRef<JSArray> keyTypesArr = JSRef<JSArray>::New();
    const std::vector<std::string>& keyTypes = eventInfo.GetKeyTypes();
    for (int32_t idx = 0; idx < static_cast<int32_t>(keyTypes.size()); ++idx) {
        JSRef<JSVal> keyType = JSRef<JSVal>::Make(ToJSValue(keyTypes[idx]));
        keyTypesArr->SetValueAt(idx, keyType);
    }
    obj->SetPropertyObject("keyTypes", keyTypesArr);

    JSRef<JSArray> issuersArr = JSRef<JSArray>::New();
    const std::vector<std::string>& issuers = eventInfo.GetIssuers_();
    for (int32_t idx = 0; idx < static_cast<int32_t>(issuers.size()); ++idx) {
        JSRef<JSVal> issuer = JSRef<JSVal>::Make(ToJSValue(issuers[idx]));
        issuersArr->SetValueAt(idx, issuer);
    }

    obj->SetPropertyObject("issuers", issuersArr);

    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> SearchResultReceiveEventToJSValue(const SearchResultReceiveEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("activeMatchOrdinal", eventInfo.GetActiveMatchOrdinal());
    obj->SetProperty("numberOfMatches", eventInfo.GetNumberOfMatches());
    obj->SetProperty("isDoneCounting", eventInfo.GetIsDoneCounting());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGI("web create error, info is invalid");
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);

    JSRef<JSVal> srcValue = paramObject->GetProperty("src");
    std::string webSrc;
    std::optional<std::string> dstSrc;
    RefPtr<WebComponent> webComponent;
    if (ParseJsMedia(srcValue, webSrc)) {
        int np = static_cast<int>(webSrc.find_first_of("/"));
        if (np < 0) {
            dstSrc = webSrc;
        } else {
            dstSrc = webSrc.erase(np, 1);
        }
        LOGI("JSWeb::Create src:%{public}s", dstSrc->c_str());
    }

    if (!dstSrc) {
        LOGE("Web component failed to parse src");
        return;
    }

    auto controllerObj = paramObject->GetProperty("controller");
    if (!controllerObj->IsObject()) {
        LOGI("web create error, controllerObj is invalid");
        return;
    }
    auto* controller = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSWebController>();
    if (!controller) {
        LOGI("web create error, controller is invalid");
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        NG::WebView::Create(dstSrc.value(), controller->GetController());
        return;
    }

    webComponent = AceType::MakeRefPtr<WebComponent>(dstSrc.value());
    webComponent->SetSrc(dstSrc.value());
    webComponent->SetWebController(controller->GetController());

    ViewStackProcessor::GetInstance()->Push(webComponent);
    JSInteractableView::SetFocusable(true);
    JSInteractableView::SetFocusNode(true);
}

void JSWeb::OnAlert(const JSCallbackInfo& args)
{
    JSWeb::OnCommonDialog(args, DialogEventType::DIALOG_EVENT_ALERT);
}

void JSWeb::OnBeforeUnload(const JSCallbackInfo& args)
{
    JSWeb::OnCommonDialog(args, DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD);
}

void JSWeb::OnConfirm(const JSCallbackInfo& args)
{
    JSWeb::OnCommonDialog(args, DialogEventType::DIALOG_EVENT_CONFIRM);
}

void JSWeb::OnPrompt(const JSCallbackInfo& args)
{
    JSWeb::OnCommonDialog(args, DialogEventType::DIALOG_EVENT_PROMPT);
}

void JSWeb::OnCommonDialog(const JSCallbackInfo& args, int dialogEventType)
{
    LOGI("OnCommonDialog, event type is %{public}d", dialogEventType);
    if (!args[0]->IsFunction()) {
        LOGW("param is not funtion.");
        return;
    }
    auto jsFunc =
        AceType::MakeRefPtr<JsEventFunction<WebDialogEvent, 1>>(JSRef<JSFunc>::Cast(args[0]), WebDialogEventToJSValue);
    auto jsCallback = [func = std::move(jsFunc)](const BaseEventInfo* info) -> bool {
        ACE_SCORING_EVENT("OnCommonDialog CallBack");
        if (func == nullptr) {
            LOGW("function is null");
            return false;
        }
        auto eventInfo = TypeInfoHelper::DynamicCast<WebDialogEvent>(info);
        JSRef<JSVal> result = func->ExecuteWithValue(*eventInfo);
        if (result->IsBoolean()) {
            return result->ToBoolean();
        }
        return false;
    };
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetOnCommonDialogImpl(std::move(jsCallback), static_cast<DialogEventType>(dialogEventType));
}

void JSWeb::OnConsoleLog(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebConsoleLogEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebConsoleLogEventToJSValue);
    if (Container::IsCurrentUseNewPipeline()) {
        auto instanceId = Container::CurrentId();
        auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId](
                              const std::shared_ptr<BaseEventInfo>& info) -> bool {
            ContainerScope scope(instanceId);
            auto context = PipelineBase::GetCurrentContext();
            CHECK_NULL_RETURN(context, false);
            // need to execute in ui.
            bool result = false;
            context->PostSyncEvent([execCtx, func = func, info, &result]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebConsoleLogEvent>(info.get());
                JSRef<JSVal> message = func->ExecuteWithValue(*eventInfo);
                if (message->IsBoolean()) {
                    result = message->ToBoolean();
                } else {
                    result = false;
                }
            });
            return result;
        };
        NG::WebView::SetOnConsole(std::move(uiCallback));
        return;
    }
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](
                          const BaseEventInfo* info) -> bool {
        auto eventInfo = TypeInfoHelper::DynamicCast<LoadWebConsoleLogEvent>(info);
        JSRef<JSVal> message = func->ExecuteWithValue(*eventInfo);
        if (message->IsBoolean()) {
            return message->ToBoolean();
        }
        return false;
    };
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetOnConsoleImpl(std::move(jsCallback));
}

void JSWeb::OnPageStart(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebPageStartEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebPageStartEventToJSValue);

    if (Container::IsCurrentUseNewPipeline()) {
        auto instanceId = Container::CurrentId();
        auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId](
                              const std::shared_ptr<BaseEventInfo>& info) {
            ContainerScope scope(instanceId);
            auto context = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(context);
            // need to execute in ui.
            context->PostAsyncEvent([execCtx, func = func, info]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebPageStartEvent>(info.get());
                func->Execute(*eventInfo);
            });
        };
        NG::WebView::SetOnPageStart(std::move(uiCallback));
        return;
    }
    auto eventMarker =
        EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
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

    if (Container::IsCurrentUseNewPipeline()) {
        auto instanceId = Container::CurrentId();
        auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId](
                              const std::shared_ptr<BaseEventInfo>& info) {
            ContainerScope scope(instanceId);
            auto context = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(context);
            // need to execute in ui.
            context->PostAsyncEvent([execCtx, func = func, info]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebPageFinishEvent>(info.get());
                func->Execute(*eventInfo);
            });
        };
        NG::WebView::SetOnPageFinish(std::move(uiCallback));
        return;
    }
    auto eventMarker =
        EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<LoadWebPageFinishEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!webComponent) {
        LOGE("webComponent is null");
        return;
    }
    webComponent->SetPageFinishedEventId(eventMarker);
}

void JSWeb::OnProgressChange(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebProgressChangeEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebProgressChangeEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto eventInfo = TypeInfoHelper::DynamicCast<LoadWebProgressChangeEvent>(info);
        func->Execute(*eventInfo);
    };
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetProgressChangeImpl(std::move(jsCallback));
}

void JSWeb::OnTitleReceive(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebTitleReceiveEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebTitleReceiveEventToJSValue);
    auto eventMarker =
        EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
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
    auto eventMarker =
        EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
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
    auto eventMarker =
        EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
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
    auto eventMarker =
        EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
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
    auto eventMarker =
        EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<DownloadStartEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetDownloadStartEventId(eventMarker);
}

void JSWeb::OnHttpAuthRequest(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("param is invalid.");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebHttpAuthEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), WebHttpAuthEventToJSValue);
    auto jsCallback = [func = std::move(jsFunc)](const BaseEventInfo* info) -> bool {
        ACE_SCORING_EVENT("onHttpAuthRequest CallBack");
        if (func == nullptr) {
            LOGW("function is null");
            return false;
        }
        auto eventInfo = TypeInfoHelper::DynamicCast<WebHttpAuthEvent>(info);
        if (eventInfo == nullptr) {
            LOGW("eventInfo is null");
            return false;
        }
        JSRef<JSVal> result = func->ExecuteWithValue(*eventInfo);
        if (result->IsBoolean()) {
            return result->ToBoolean();
        }
        return false;
    };
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetOnHttpAuthRequestImpl(std::move(jsCallback));
}

void JSWeb::OnSslErrorRequest(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("param is invalid.");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebSslErrorEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), WebSslErrorEventToJSValue);
    auto jsCallback = [func = std::move(jsFunc)](const BaseEventInfo* info) -> bool {
        ACE_SCORING_EVENT("OnSslErrorRequest CallBack");
        if (func == nullptr) {
            LOGW("function is null");
            return false;
        }
        auto eventInfo = TypeInfoHelper::DynamicCast<WebSslErrorEvent>(info);
        if (eventInfo == nullptr) {
            LOGW("eventInfo is null");
            return false;
        }
        JSRef<JSVal> result = func->ExecuteWithValue(*eventInfo);
        if (result->IsBoolean()) {
            return result->ToBoolean();
        }
        return false;
    };
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetOnSslErrorRequestImpl(std::move(jsCallback));
}

void JSWeb::OnSslSelectCertRequest(const JSCallbackInfo& args)
{
    LOGI("JSWeb::OnSslSelectCertRequest");
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("param is invalid.");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebSslSelectCertEvent, 1>>(JSRef<JSFunc>::Cast(args[0]),
        WebSslSelectCertEventToJSValue);
    auto jsCallback = [func = std::move(jsFunc)]
        (const BaseEventInfo* info) -> bool {
            ACE_SCORING_EVENT("OnSslSelectCertRequest CallBack");
            if (func == nullptr) {
                LOGW("function is null");
                return false;
            }
            auto eventInfo = TypeInfoHelper::DynamicCast<WebSslSelectCertEvent>(info);
            if (eventInfo == nullptr) {
                LOGW("eventInfo is null");
                return false;
            }
            JSRef<JSVal> result = func->ExecuteWithValue(*eventInfo);
            if (result->IsBoolean()) {
                return result->ToBoolean();
            }
            return false;
        };
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetOnSslSelectCertRequestImpl(std::move(jsCallback));
}

void JSWeb::MediaPlayGestureAccess(bool isNeedGestureAccess)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    webComponent->SetMediaPlayGestureAccess(isNeedGestureAccess);
}

void JSWeb::OnKeyEvent(const JSCallbackInfo& args)
{
    LOGI("JSWeb OnKeyEvent");
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("Param is invalid, it is not a function");
        return;
    }

    RefPtr<JsKeyFunction> jsOnKeyEventFunc = AceType::MakeRefPtr<JsKeyFunction>(JSRef<JSFunc>::Cast(args[0]));
    auto onKeyEventId = [execCtx = args.GetExecutionContext(), func = std::move(jsOnKeyEventFunc)](
                            KeyEventInfo& keyEventInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onKeyEvent");
        func->Execute(keyEventInfo);
    };

    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetOnKeyEventCallback(onKeyEventId);
}

JSRef<JSVal> ReceivedErrorEventToJSValue(const ReceivedErrorEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();

    JSRef<JSObject> requestObj = JSClass<JSWebResourceRequest>::NewInstance();
    auto requestEvent = Referenced::Claim(requestObj->Unwrap<JSWebResourceRequest>());
    requestEvent->SetErrorEvent(eventInfo);

    JSRef<JSObject> errorObj = JSClass<JSWebResourceError>::NewInstance();
    auto errorEvent = Referenced::Claim(errorObj->Unwrap<JSWebResourceError>());
    errorEvent->SetEvent(eventInfo);

    obj->SetPropertyObject("request", requestObj);
    obj->SetPropertyObject("error", errorObj);

    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> ReceivedHttpErrorEventToJSValue(const ReceivedHttpErrorEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();

    JSRef<JSObject> requestObj = JSClass<JSWebResourceRequest>::NewInstance();
    auto requestEvent = Referenced::Claim(requestObj->Unwrap<JSWebResourceRequest>());
    requestEvent->SetHttpErrorEvent(eventInfo);

    JSRef<JSObject> responseObj = JSClass<JSWebResourceResponse>::NewInstance();
    auto responseEvent = Referenced::Claim(responseObj->Unwrap<JSWebResourceResponse>());
    responseEvent->SetEvent(eventInfo);

    obj->SetPropertyObject("request", requestObj);
    obj->SetPropertyObject("response", responseObj);

    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnErrorReceive(const JSCallbackInfo& args)
{
    LOGI("JSWeb OnErrorReceive");
    if (!args[0]->IsFunction()) {
        LOGE("Param is invalid, it is not a function");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ReceivedErrorEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ReceivedErrorEventToJSValue);

    if (Container::IsCurrentUseNewPipeline()) {
        auto instanceId = Container::CurrentId();
        auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId](
                              const std::shared_ptr<BaseEventInfo>& info) {
            ContainerScope scope(instanceId);
            auto context = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(context);
            // need to execute in ui.
            context->PostAsyncEvent([execCtx, func = func, info]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                auto* eventInfo = TypeInfoHelper::DynamicCast<ReceivedErrorEvent>(info.get());
                func->Execute(*eventInfo);
            });
        };
        NG::WebView::SetOnErrorReceive(std::move(uiCallback));
        return;
    }

    auto eventMarker =
        EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<ReceivedErrorEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetPageErrorEventId(eventMarker);
}

void JSWeb::OnHttpErrorReceive(const JSCallbackInfo& args)
{
    LOGI("JSWeb OnHttpErrorReceive");
    if (!args[0]->IsFunction()) {
        LOGE("Param is invalid, it is not a function");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ReceivedHttpErrorEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ReceivedHttpErrorEventToJSValue);

    if (Container::IsCurrentUseNewPipeline()) {
        auto instanceId = Container::CurrentId();
        auto callback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId](
                            const std::shared_ptr<BaseEventInfo>& info) {
            ContainerScope scope(instanceId);
            auto context = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(context);
            // need to execute in ui.
            context->PostAsyncEvent([execCtx, func = func, info]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                auto* eventInfo = TypeInfoHelper::DynamicCast<ReceivedHttpErrorEvent>(info.get());
                func->Execute(*eventInfo);
            });
        };
        NG::WebView::SetOnHttpErrorReceive(std::move(callback));
        return;
    }

    auto eventMarker =
        EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<ReceivedHttpErrorEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetHttpErrorEventId(eventMarker);
}

JSRef<JSVal> OnInterceptRequestEventToJSValue(const OnInterceptRequestEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSObject> requestObj = JSClass<JSWebResourceRequest>::NewInstance();
    auto requestEvent = Referenced::Claim(requestObj->Unwrap<JSWebResourceRequest>());
    requestEvent->SetOnInterceptRequestEvent(eventInfo);
    obj->SetPropertyObject("request", requestObj);
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnInterceptRequest(const JSCallbackInfo& args)
{
    LOGI("JSWeb OnInterceptRequest");
    if ((args.Length() <= 0) || !args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<OnInterceptRequestEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), OnInterceptRequestEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](
                          const BaseEventInfo* info) -> RefPtr<WebResponse> {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, nullptr);
        auto eventInfo = TypeInfoHelper::DynamicCast<OnInterceptRequestEvent>(info);
        if (eventInfo == nullptr) {
            return nullptr;
        }
        JSRef<JSVal> obj = func->ExecuteWithValue(*eventInfo);
        if (!obj->IsObject()) {
            LOGI("hap return value is null");
            return nullptr;
        }
        auto jsResponse = JSRef<JSObject>::Cast(obj)->Unwrap<JSWebResourceResponse>();
        if (jsResponse) {
            return jsResponse->GetResponseObj();
        }
        return nullptr;
    };
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetOnInterceptRequest(std::move(jsCallback));
}

void JSWeb::OnUrlLoadIntercept(const JSCallbackInfo& args)
{
    LOGI("JSWeb OnUrlLoadIntercept");
    if (!args[0]->IsFunction()) {
        LOGE("Param is invalid, it is not a function");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<UrlLoadInterceptEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), UrlLoadInterceptEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](
                          const BaseEventInfo* info) -> bool {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto eventInfo = TypeInfoHelper::DynamicCast<UrlLoadInterceptEvent>(info);
        JSRef<JSVal> message = func->ExecuteWithValue(*eventInfo);
        if (message->IsBoolean()) {
            return message->ToBoolean();
        }
        return false;
    };
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetOnUrlLoadIntercept(std::move(jsCallback));
}

JSRef<JSVal> FileSelectorEventToJSValue(const FileSelectorEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();

    JSRef<JSObject> paramObj = JSClass<JSFileSelectorParam>::NewInstance();
    auto fileSelectorParam = Referenced::Claim(paramObj->Unwrap<JSFileSelectorParam>());
    fileSelectorParam->SetParam(eventInfo);

    JSRef<JSObject> resultObj = JSClass<JSFileSelectorResult>::NewInstance();
    auto fileSelectorResult = Referenced::Claim(resultObj->Unwrap<JSFileSelectorResult>());
    fileSelectorResult->SetResult(eventInfo);

    obj->SetPropertyObject("result", resultObj);
    obj->SetPropertyObject("fileSelector", paramObj);
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnFileSelectorShow(const JSCallbackInfo& args)
{
    LOGI("OnFileSelectorShow");
    if (!args[0]->IsFunction()) {
        return;
    }

    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<FileSelectorEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), FileSelectorEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](
                          const BaseEventInfo* info) -> bool {
        ACE_SCORING_EVENT("OnFileSelectorShow CallBack");
        if (func == nullptr) {
            LOGW("function is null");
            return false;
        }
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto eventInfo = TypeInfoHelper::DynamicCast<FileSelectorEvent>(info);
        JSRef<JSVal> result = func->ExecuteWithValue(*eventInfo);
        if (result->IsBoolean()) {
            return result->ToBoolean();
        }
        return false;
    };
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetOnFileSelectorShow(std::move(jsCallback));
}

JSRef<JSVal> ContextMenuEventToJSValue(const ContextMenuEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();

    JSRef<JSObject> paramObj = JSClass<JSContextMenuParam>::NewInstance();
    auto contextMenuParam = Referenced::Claim(paramObj->Unwrap<JSContextMenuParam>());
    contextMenuParam->SetParam(eventInfo);

    JSRef<JSObject> resultObj = JSClass<JSContextMenuResult>::NewInstance();
    auto contextMenuResult = Referenced::Claim(resultObj->Unwrap<JSContextMenuResult>());
    contextMenuResult->SetResult(eventInfo);

    obj->SetPropertyObject("result", resultObj);
    obj->SetPropertyObject("param", paramObj);
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnContextMenuShow(const JSCallbackInfo& args)
{
    LOGI("JSWeb: OnContextMenuShow");
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("param is invalid.");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ContextMenuEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ContextMenuEventToJSValue);
    auto jsCallback = [func = std::move(jsFunc)](const BaseEventInfo* info) -> bool {
        ACE_SCORING_EVENT("onContextMenuShow CallBack");
        if (func == nullptr) {
            LOGW("function is null");
            return false;
        }
        auto eventInfo = TypeInfoHelper::DynamicCast<ContextMenuEvent>(info);
        if (eventInfo == nullptr) {
            LOGW("eventInfo is null");
            return false;
        }
        JSRef<JSVal> result = func->ExecuteWithValue(*eventInfo);
        if (result->IsBoolean()) {
            return result->ToBoolean();
        }
        return false;
    };
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetOnContextMenuShow(std::move(jsCallback));
}

void JSWeb::JsEnabled(bool isJsEnabled)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::WebView::SetJsEnabled(isJsEnabled);
        return;
    }
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

void JSWeb::JavaScriptProxy(const JSCallbackInfo& args)
{
    LOGI("JSWeb add js interface");
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(args[0]);
    auto controllerObj = paramObject->GetProperty("controller");
    auto controller = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSWebController>();
    if (controller) {
        controller->SetJavascriptInterface(args);
    }
}

void JSWeb::UserAgent(const std::string& userAgent)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    webComponent->SetUserAgent(userAgent);
}

JSRef<JSVal> RenderExitedEventToJSValue(const RenderExitedEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("renderExitReason", eventInfo.GetExitedReason());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> RefreshAccessedHistoryEventToJSValue(const RefreshAccessedHistoryEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("url", eventInfo.GetVisitedUrl());
    obj->SetProperty("isRefreshed", eventInfo.IsRefreshed());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnRenderExited(const JSCallbackInfo& args)
{
    LOGI("JSWeb OnRenderExited");
    if (!args[0]->IsFunction()) {
        LOGE("Param is invalid, it is not a function");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<RenderExitedEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), RenderExitedEventToJSValue);
    auto eventMarker =
        EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<RenderExitedEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetRenderExitedId(eventMarker);
}

void JSWeb::OnRefreshAccessedHistory(const JSCallbackInfo& args)
{
    LOGI("JSWeb OnRefreshAccessedHistory");
    if (!args[0]->IsFunction()) {
        LOGE("Param is invalid, it is not a function");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<RefreshAccessedHistoryEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), RefreshAccessedHistoryEventToJSValue);
    auto eventMarker =
        EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<RefreshAccessedHistoryEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetRefreshAccessedHistoryId(eventMarker);
}

void JSWeb::CacheMode(int32_t cacheMode)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    auto mode = WebCacheMode::DEFAULT;
    switch (cacheMode) {
        case 0:
            mode = WebCacheMode::DEFAULT;
            break;
        case 1:
            mode = WebCacheMode::USE_CACHE_ELSE_NETWORK;
            break;
        case 2:
            mode = WebCacheMode::USE_NO_CACHE;
            break;
        case 3:
            mode = WebCacheMode::USE_CACHE_ONLY;
            break;
        default:
            mode = WebCacheMode::DEFAULT;
            break;
    }
    webComponent->SetCacheMode(mode);
}

void JSWeb::OverviewModeAccess(bool isOverviewModeAccessEnabled)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    webComponent->SetOverviewModeAccessEnabled(isOverviewModeAccessEnabled);
}

void JSWeb::FileFromUrlAccess(bool isFileFromUrlAccessEnabled)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    webComponent->SetFileFromUrlAccessEnabled(isFileFromUrlAccessEnabled);
}

void JSWeb::DatabaseAccess(bool isDatabaseAccessEnabled)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    webComponent->SetDatabaseAccessEnabled(isDatabaseAccessEnabled);
}

void JSWeb::TextZoomRatio(int32_t textZoomRatioNum)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    webComponent->SetTextZoomRatio(textZoomRatioNum);
}

void JSWeb::WebDebuggingAccessEnabled(bool isWebDebuggingAccessEnabled)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    webComponent->SetWebDebuggingAccessEnabled(isWebDebuggingAccessEnabled);
}

void JSWeb::OnMouse(const JSCallbackInfo& args)
{
    LOGI("JSWeb OnMouse");
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("Param is invalid, it is not a function");
        return;
    }

    RefPtr<JsClickFunction> jsOnMouseFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(args[0]));
    auto onMouseId = [execCtx = args.GetExecutionContext(), func = std::move(jsOnMouseFunc)](MouseInfo& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onMouse");
        func->Execute(info);
    };

    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetOnMouseEventCallback(onMouseId);
}

JSRef<JSVal> ResourceLoadEventToJSValue(const ResourceLoadEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("url", eventInfo.GetOnResourceLoadUrl());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnResourceLoad(const JSCallbackInfo& args)
{
    LOGI("JSWeb OnRefreshAccessedHistory");
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("Param is invalid, it is not a function");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ResourceLoadEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ResourceLoadEventToJSValue);
    auto eventMarker =
        EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<ResourceLoadEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetResourceLoadId(eventMarker);
}

JSRef<JSVal> ScaleChangeEventToJSValue(const ScaleChangeEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("oldScale", eventInfo.GetOnScaleChangeOldScale());
    obj->SetProperty("newScale", eventInfo.GetOnScaleChangeNewScale());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnScaleChange(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("Param is invalid, it is not a function");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ScaleChangeEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ScaleChangeEventToJSValue);
    auto eventMarker =
        EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<ScaleChangeEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetScaleChangeId(eventMarker);
}

JSRef<JSVal> ScrollEventToJSValue(const OnScrollEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("xOffset", eventInfo.GetX());
    obj->SetProperty("yOffset", eventInfo.GetY());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnScroll(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("Param is invalid, it is not a function");
        return;
    }
    auto jsFunc =
        AceType::MakeRefPtr<JsEventFunction<OnScrollEvent, 1>>(JSRef<JSFunc>::Cast(args[0]), ScrollEventToJSValue);
    auto eventMarker =
        EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<OnScrollEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetScrollId(eventMarker);
}

JSRef<JSVal> PermissionRequestEventToJSValue(const WebPermissionRequestEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSObject> permissionObj = JSClass<JSWebPermissionRequest>::NewInstance();
    auto permissionEvent = Referenced::Claim(permissionObj->Unwrap<JSWebPermissionRequest>());
    permissionEvent->SetEvent(eventInfo);
    obj->SetPropertyObject("request", permissionObj);
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnPermissionRequest(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("Param is invalid, it is not a function");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebPermissionRequestEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), PermissionRequestEventToJSValue);
    auto eventMarker =
        EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<WebPermissionRequestEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetPermissionRequestEventId(eventMarker);
}

void JSWeb::BackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color backgroundColor;
    if (!ParseJsColor(info[0], backgroundColor)) {
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    webComponent->SetBackgroundColor(backgroundColor.GetValue());
}

void JSWeb::InitialScale(float scale)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        LOGE("JSWeb: MainComponent is null.");
        return;
    }
    webComponent->SetInitialScale(scale);
}

void JSWeb::Password(bool password)
{
    LOGI("JSWeb: Password placeholder");
}

void JSWeb::TableData(bool tableData)
{
    LOGI("JSWeb: TableData placeholder");
}

void JSWeb::OnFileSelectorShowAbandoned(const JSCallbackInfo& args)
{
    LOGI("JSWeb: OnFileSelectorShow Abandoned");
}

void JSWeb::OnSearchResultReceive(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        LOGE("Param is invalid");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<SearchResultReceiveEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), SearchResultReceiveEventToJSValue);
    auto eventMarker =
        EventMarker([execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto eventInfo = TypeInfoHelper::DynamicCast<SearchResultReceiveEvent>(info);
            func->Execute(*eventInfo);
        });
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    webComponent->SetSearchResultReceiveEventId(eventMarker);
}

void JSWeb::JsOnDragStart(const JSCallbackInfo& info)
{
    RefPtr<JsDragFunction> jsOnDragStartFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragStartId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragStartFunc)](
                             const RefPtr<DragEvent>& info, const std::string& extraParams) -> DragItemInfo {
        DragItemInfo itemInfo;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, itemInfo);

        auto ret = func->Execute(info, extraParams);
        if (!ret->IsObject()) {
            LOGE("builder param is not an object.");
            return itemInfo;
        }
        auto component = ParseDragItemComponent(ret);
        if (component) {
            LOGI("use custom builder param.");
            itemInfo.customComponent = component;
            return itemInfo;
        }

        auto builderObj = JSRef<JSObject>::Cast(ret);
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
        auto pixmap = builderObj->GetProperty("pixelMap");
        itemInfo.pixelMap = CreatePixelMapFromNapiValue(pixmap);
#endif
        auto extraInfo = builderObj->GetProperty("extraInfo");
        ParseJsString(extraInfo, itemInfo.extraInfo);
        component = ParseDragItemComponent(builderObj->GetProperty("builder"));
        itemInfo.customComponent = component;
        return itemInfo;
    };
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (webComponent) {
        webComponent->SetOnDragStartId(onDragStartId);
    }
}

void JSWeb::JsOnDragEnter(const JSCallbackInfo& info)
{
    RefPtr<JsDragFunction> jsOnDragEnterFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragEnterId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragEnterFunc)](
                             const RefPtr<DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragEnter");
        func->Execute(info, extraParams);
    };
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (webComponent) {
        webComponent->SetOnDragEnterId(onDragEnterId);
    }
}

void JSWeb::JsOnDragMove(const JSCallbackInfo& info)
{
    RefPtr<JsDragFunction> jsOnDragMoveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragMoveId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragMoveFunc)](
                            const RefPtr<DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragMove");
        func->Execute(info, extraParams);
    };
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (webComponent) {
        webComponent->SetOnDragMoveId(onDragMoveId);
    }
}

void JSWeb::JsOnDragLeave(const JSCallbackInfo& info)
{
    RefPtr<JsDragFunction> jsOnDragLeaveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragLeaveId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragLeaveFunc)](
                             const RefPtr<DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragLeave");
        func->Execute(info, extraParams);
    };
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (webComponent) {
        webComponent->SetOnDragLeaveId(onDragLeaveId);
    }
}

void JSWeb::JsOnDrop(const JSCallbackInfo& info)
{
    RefPtr<JsDragFunction> jsOnDropFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDropId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDropFunc)](
                        const RefPtr<DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDrop");
        func->Execute(info, extraParams);
    };
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (webComponent) {
        webComponent->SetOnDropId(onDropId);
    }
}
} // namespace OHOS::Ace::Framework
