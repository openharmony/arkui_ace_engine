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

#include "base/log/ace_scoring_log.h"
#include "base/utils/linear_map.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_webview_function.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::Framework {
namespace {
panda::Local<panda::JSValueRef> ToJsValueHelper(const EcmaVM* vm, std::shared_ptr<WebJSValue> argument)
{
    if (!argument || !vm) {
        TAG_LOGE(AceLogTag::ACE_WEB, "ToJsValueHelper: argument or vm is null");
        return panda::JSValueRef::Undefined(vm);
    }
    switch (argument->GetType()) {
        case WebJSValue::Type::INTEGER:
            return ToJSValue(argument->GetInt());
        case WebJSValue::Type::DOUBLE:
            return ToJSValue(argument->GetDouble());
        case WebJSValue::Type::BOOLEAN:
            return ToJSValue(argument->GetBoolean());
        case WebJSValue::Type::STRING:
            return ToJSValue(argument->GetString());
        case WebJSValue::Type::LIST: {
            size_t length = argument->GetListValueSize();
            auto arr = panda::ArrayRef::New(vm, length);
            for (size_t i = 0; i < length; ++i) {
                auto nPtr = std::make_shared<WebJSValue>(argument->GetListValue(i));
                if (!panda::ArrayRef::SetValueAt(vm, arr, i, ToJsValueHelper(vm, nPtr))) {
                    TAG_LOGE(AceLogTag::ACE_WEB, "ToJsValueHelper: SetValueAt api call failed");
                    return panda::JSValueRef::Undefined(vm);
                }
            }
            return arr;
        }
        case WebJSValue::Type::DICTIONARY: {
            auto obj = panda::ObjectRef::New(vm);
            auto dict = argument->GetDictionaryValue();
            for (auto& item : dict) {
                auto nPtr = std::make_shared<WebJSValue>(item.second);
                obj->Set(vm, panda::StringRef::NewFromUtf8(vm, item.first.c_str()), ToJsValueHelper(vm, nPtr));
            }
            return obj;
        }
        case WebJSValue::Type::BINARY: {
            auto size = argument->GetBinaryValueSize();
            auto buff = argument->GetBinaryValue();
            return panda::ArrayBufferRef::New(vm, (void*)buff, (int32_t)size, nullptr, (void*)buff);
        }
        case WebJSValue::Type::NONE:
            return panda::JSValueRef::Undefined(vm);
        default:
            TAG_LOGE(AceLogTag::ACE_WEB, "ToJsValueHelper: jsvalue type not support!");
            break;
    }
    return panda::JSValueRef::Undefined(vm);
}

void ParseWebViewValueToJsValue(std::shared_ptr<WebJSValue> value, std::vector<JSRef<JSVal>>& argv)
{
    if (!value) {
        return;
    }
    auto vm = GetEcmaVm();
    argv.push_back(JSRef<JSVal>::Make(ToJsValueHelper(vm, value)));
}

std::shared_ptr<WebJSValue> ParseValue(const JSRef<JSVal>& resultValue, std::shared_ptr<WebJSValue> webviewValue)
{
    if (!webviewValue) {
        TAG_LOGE(AceLogTag::ACE_WEB, "ParseValue: webviewValue or resultValue is null");
        return std::make_shared<WebJSValue>();
    }

    webviewValue->error_ = static_cast<int>(WebJavaScriptBridgeError::NO_ERROR0);
    if (resultValue->IsBoolean()) {
        webviewValue->SetType(WebJSValue::Type::BOOLEAN);
        webviewValue->SetBoolean(resultValue->ToBoolean());
    } else if (resultValue->IsNull()) {
        webviewValue->SetType(WebJSValue::Type::NONE);
    } else if (resultValue->IsString()) {
        webviewValue->SetType(WebJSValue::Type::STRING);
        webviewValue->SetString(resultValue->ToString());
    } else if (resultValue->IsNumber()) {
        webviewValue->SetType(WebJSValue::Type::DOUBLE);
        webviewValue->SetDouble(resultValue->ToNumber<double>());
    } else if (resultValue->IsArray()) {
        webviewValue->SetType(WebJSValue::Type::LIST);
        JSRef<JSArray> array = JSRef<JSArray>::Cast(resultValue);
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> value = array->GetValueAt(i);
            auto nVal = std::make_shared<WebJSValue>();
            webviewValue->AddListValue(*ParseValue(value, nVal));
        }
    } else if (resultValue->IsObject()) {
        webviewValue->SetType(WebJSValue::Type::DICTIONARY);
        JSRef<JSObject> dic = JSRef<JSObject>::Cast(resultValue);
        auto names = dic->GetPropertyNames();
        for (size_t i = 0; i < names->Length(); i++) {
            JSRef<JSVal> key = names->GetValueAt(i);
            if (!(key->IsString())) {
                continue;
            }
            JSRef<JSVal> property = dic->GetProperty(key->ToString().c_str());
            auto nwebValueTmp = std::make_shared<WebJSValue>();
            auto nwebKeyTmp = std::make_shared<WebJSValue>();
            ParseValue(key, nwebKeyTmp);
            ParseValue(property, nwebValueTmp);
            webviewValue->AddDictionaryValue(nwebKeyTmp->GetString(), *nwebValueTmp);
        }
    } else if (resultValue->IsFunction()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "ParseValue: object is not supported");
        webviewValue->SetType(WebJSValue::Type::NONE);
    } else if (resultValue->IsUndefined()) {
        webviewValue->SetType(WebJSValue::Type::NONE);
        webviewValue->error_ = static_cast<int>(WebJavaScriptBridgeError::OBJECT_IS_GONE);
    }
    return webviewValue;
}
} // namespace

class JSWebCookie : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebCookie>::Declare("WebCookie");
        JSClass<JSWebCookie>::CustomMethod("setCookie", &JSWebCookie::SetCookie);
        JSClass<JSWebCookie>::CustomMethod("getCookie", &JSWebCookie::GetCookie);
        JSClass<JSWebCookie>::CustomMethod("deleteEntireCookie", &JSWebCookie::DeleteEntirelyCookie);
        JSClass<JSWebCookie>::CustomMethod("saveCookie", &JSWebCookie::SaveCookieSync);
        JSClass<JSWebCookie>::Bind(globalObj, JSWebCookie::Constructor, JSWebCookie::Destructor);
    }

    void SetWebCookie(WebCookie* manager)
    {
        if (manager != nullptr) {
            manager_ = manager;
        }
    }

    void SetCookie(const JSCallbackInfo& args)
    {
        std::string url;
        std::string value;
        bool result = false;
        if (args.Length() >= 2 && args[0]->IsString() && args[1]->IsString()) {
            url = args[0]->ToString();
            value = args[1]->ToString();
            if (manager_ != nullptr) {
                result = manager_->SetCookie(url, value);
            }
        }
        auto jsVal = JSVal(ToJSValue(result));
        auto returnValue = JSRef<JSVal>::Make(jsVal);
        args.SetReturnValue(returnValue);
    }

    void GetCookie(const JSCallbackInfo& args)
    {
        std::string result = "";
        if (manager_ != nullptr && args.Length() >= 1 && args[0]->IsString()) {
            std::string url = args[0]->ToString();
            result = manager_->GetCookie(url);
        }
        auto jsVal = JSVal(ToJSValue(result));
        auto returnValue = JSRef<JSVal>::Make(jsVal);
        args.SetReturnValue(returnValue);
    }

    void DeleteEntirelyCookie(const JSCallbackInfo& args)
    {
        if (manager_ == nullptr) {
            return;
        }
        manager_->DeleteEntirelyCookie();
    }

    void SaveCookieSync(const JSCallbackInfo& args)
    {
        bool result = false;
        if (manager_ != nullptr) {
            result = manager_->SaveCookieSync();
        }
        auto jsVal = JSVal(ToJSValue(result));
        auto returnValue = JSRef<JSVal>::Make(jsVal);
        args.SetReturnValue(returnValue);
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsWebCookie = Referenced::MakeRefPtr<JSWebCookie>();
        jsWebCookie->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsWebCookie));
    }

    static void Destructor(JSWebCookie* jsWebCookie)
    {
        if (jsWebCookie != nullptr) {
            jsWebCookie->DecRefCount();
        }
    }
    WebCookie* manager_;
};

class JSHitTestValue : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSHitTestValue>::Declare("HitTestValue");
        JSClass<JSHitTestValue>::CustomMethod("getType", &JSHitTestValue::GetType);
        JSClass<JSHitTestValue>::CustomMethod("getExtra", &JSHitTestValue::GetExtra);
        JSClass<JSHitTestValue>::Bind(globalObj, JSHitTestValue::Constructor, JSHitTestValue::Destructor);
    }

    void SetType(int type)
    {
        type_ = type;
    }

    void SetExtra(const std::string& extra)
    {
        extra_ = extra;
    }

    void GetType(const JSCallbackInfo& args)
    {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(type_)));
    }

    void GetExtra(const JSCallbackInfo& args)
    {
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(extra_)));
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jSHitTestResult = Referenced::MakeRefPtr<JSHitTestValue>();
        jSHitTestResult->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jSHitTestResult));
    }

    static void Destructor(JSHitTestValue* jSHitTestResult)
    {
        if (jSHitTestResult != nullptr) {
            jSHitTestResult->DecRefCount();
        }
    }

    std::string extra_;
    int type_ = static_cast<int>(WebHitTestType::UNKNOWN);
};

JSWebController::JSWebController()
{
    instanceId_ = Container::CurrentId();
}

std::shared_ptr<WebJSValue> JSWebController::GetJavaScriptResult(const std::string& objectName,
    const std::string& objectMethod, const std::vector<std::shared_ptr<WebJSValue>>& args)
{
    std::vector<JSRef<JSVal>> argv = {};
    std::shared_ptr<WebJSValue> jsResult = std::make_shared<WebJSValue>(WebJSValue::Type::NONE);
    auto iter = objectorMap_.find(objectName);
    if (iter == objectorMap_.end()) {
        return jsResult;
    }
    auto jsObject = iter->second;
    if (jsObject->IsEmpty()) {
        return jsResult;
    }
    for (std::shared_ptr<WebJSValue> input : args) {
        ParseWebViewValueToJsValue(input, argv);
    }

    if (jsObject->GetProperty(objectMethod.c_str())->IsEmpty() ||
        !(jsObject->GetProperty(objectMethod.c_str())->IsFunction())) {
        return jsResult;
    }

    JSRef<JSFunc> func = JSRef<JSFunc>::Cast(jsObject->GetProperty(objectMethod.c_str()));
    if (func->IsEmpty()) {
        jsResult->error_ = static_cast<int>(WebJavaScriptBridgeError::OBJECT_IS_GONE);
        return jsResult;
    }
    JSRef<JSVal> result = argv.empty() ? func->Call(jsObject, 0, {}) : func->Call(jsObject, argv.size(), &argv[0]);
    return ParseValue(result, jsResult);
}

class JSWebMessageEvent;
class JSWebMessagePort : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebMessagePort>::Declare("WebMessagePort");
        JSClass<JSWebMessagePort>::CustomMethod("close", &JSWebMessagePort::Close);
        JSClass<JSWebMessagePort>::CustomMethod("postMessageEvent", &JSWebMessagePort::PostMessage);
        JSClass<JSWebMessagePort>::CustomMethod("onMessageEvent", &JSWebMessagePort::SetWebMessageCallback);
        JSClass<JSWebMessagePort>::Bind(globalObj, JSWebMessagePort::Constructor, JSWebMessagePort::Destructor);
    }

    void PostMessage(const JSCallbackInfo& args);

    void Close(const JSCallbackInfo& args)
    {
        if (port_ != nullptr) {
            port_->Close();
        }
    }

    void SetWebMessageCallback(const JSCallbackInfo& args)
    {
        if (args.Length() < 1 || !args[0]->IsObject()) {
            return;
        }

        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        JSRef<JSVal> tsCallback = JSRef<JSVal>::Cast(obj);
        std::function<void(std::string)> callback = nullptr;
        if (tsCallback->IsFunction()) {
            auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            auto jsCallback = AceType::MakeRefPtr<JsWebViewFunction>(JSRef<JSFunc>::Cast(tsCallback));
            callback = [execCtx = args.GetExecutionContext(), func = std::move(jsCallback), node = frameNode](
                            std::string result) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("onMessageEvent CallBack");
                auto pipelineContext = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(pipelineContext);
                pipelineContext->UpdateCurrentActiveNode(node);
                func->Execute(result);
            };
            if (port_ != nullptr) {
                port_->SetWebMessageCallback(std::move(callback));
            }
        }
    }

    void SetWebMessagePort(const RefPtr<WebMessagePort>& port)
    {
        port_ = port;
    }

    RefPtr<WebMessagePort> GetWebMessagePort()
    {
        return port_;
    }

private:
    RefPtr<WebMessagePort> port_;

    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsWebMessagePort = Referenced::MakeRefPtr<JSWebMessagePort>();
        jsWebMessagePort->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsWebMessagePort));
    }

    static void Destructor(JSWebMessagePort* jsWebMessagePort)
    {
        if (jsWebMessagePort != nullptr) {
            jsWebMessagePort->DecRefCount();
        }
    }
};

class JSWebMessageEvent : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebMessageEvent>::Declare("WebMessageEvent");
        JSClass<JSWebMessageEvent>::CustomMethod("getData", &JSWebMessageEvent::GetData);
        JSClass<JSWebMessageEvent>::CustomMethod("setData", &JSWebMessageEvent::SetData);
        JSClass<JSWebMessageEvent>::CustomMethod("getPorts", &JSWebMessageEvent::GetPorts);
        JSClass<JSWebMessageEvent>::CustomMethod("setPorts", &JSWebMessageEvent::SetPorts);
        JSClass<JSWebMessageEvent>::Bind(globalObj, JSWebMessageEvent::Constructor, JSWebMessageEvent::Destructor);
    }

    void GetData(const JSCallbackInfo& args)
    {
        auto jsVal = JSVal(ToJSValue(data_));
        auto retVal = JSRef<JSVal>::Make(jsVal);
        args.SetReturnValue(retVal);
    }

    void SetData(const JSCallbackInfo& args)
    {
        if (args.Length() < 1 || !args[0]->IsString()) {
            return;
        }
        data_ = args[0]->ToString();
    }

    void SetPorts(const JSCallbackInfo& args)
    {
        if (args.Length() <= 0) {
            return;
        }
        if (!args[0]->IsArray()) {
            return;
        }
        JSRef<JSArray> jsPorts = JSRef<JSArray>::Cast(args[0]);
        std::vector<RefPtr<WebMessagePort>> sendPorts;
        if (jsPorts->IsArray()) {
            JSRef<JSArray> array = JSRef<JSArray>::Cast(jsPorts);
            for (size_t i = 0; i < array->Length(); i++) {
                JSRef<JSVal> jsValue = array->GetValueAt(i);
                if (!jsValue->IsObject()) {
                    continue;
                }
                JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
                RefPtr<JSWebMessagePort> jswebPort = Referenced::Claim(jsObj->Unwrap<JSWebMessagePort>());
                if (jswebPort) {
                    ports_.push_back(jswebPort);
                }
            }
        }
    }

    void GetPorts(const JSCallbackInfo& args)
    {
        JSRef<JSArray> jsPorts = JSRef<JSArray>::New();
        JSRef<JSObject> jsObj;
        RefPtr<JSWebMessagePort> jswebPort;
        for (size_t i = 0; i < ports_.size(); i++) {
            jsObj = JSClass<JSWebMessagePort>::NewInstance();
            jswebPort = Referenced::Claim(jsObj->Unwrap<JSWebMessagePort>());
            jswebPort->SetWebMessagePort(ports_[i]->GetWebMessagePort());
            jsPorts->SetValueAt(i, jsObj);
        }
        args.SetReturnValue(jsPorts);
    }

    std::string GetDataInternal()
    {
        return data_;
    }

    std::vector<RefPtr<JSWebMessagePort>> GetPortsInternal()
    {
        return ports_;
    }

private:
    std::string data_;
    std::vector<RefPtr<JSWebMessagePort>> ports_;

    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsWebMessageEvent = Referenced::MakeRefPtr<JSWebMessageEvent>();
        jsWebMessageEvent->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsWebMessageEvent));
    }

    static void Destructor(JSWebMessageEvent* jsWebMessageEvent)
    {
        if (jsWebMessageEvent != nullptr) {
            jsWebMessageEvent->DecRefCount();
        }
    }
};

void JSWebMessagePort::PostMessage(const JSCallbackInfo& args)
{
    if (args.Length() <= 0 || !(args[0]->IsObject())) {
        return;
    }
    // get ports
    JSRef<JSVal> jsPorts = JSRef<JSVal>::Cast(args[0]);
    if (!jsPorts->IsObject()) {
        return;
    }
    auto jsRes = Referenced::Claim(JSRef<JSObject>::Cast(jsPorts)->Unwrap<JSWebMessageEvent>());
    std::string data = jsRes->GetDataInternal();
    if (port_) {
        port_->PostMessage(data);
    }
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
    JSClass<JSWebController>::CustomMethod("zoom", &JSWebController::Zoom);
    JSClass<JSWebController>::CustomMethod("requestFocus", &JSWebController::RequestFocus);
    JSClass<JSWebController>::CustomMethod("loadData", &JSWebController::LoadDataWithBaseUrl);
    JSClass<JSWebController>::CustomMethod("backward", &JSWebController::Backward);
    JSClass<JSWebController>::CustomMethod("forward", &JSWebController::Forward);
    JSClass<JSWebController>::CustomMethod("accessStep", &JSWebController::AccessStep);
    JSClass<JSWebController>::CustomMethod("accessForward", &JSWebController::AccessForward);
    JSClass<JSWebController>::CustomMethod("accessBackward", &JSWebController::AccessBackward);
    JSClass<JSWebController>::CustomMethod("clearHistory", &JSWebController::ClearHistory);
    JSClass<JSWebController>::CustomMethod("clearSslCache", &JSWebController::ClearSslCache);
    JSClass<JSWebController>::CustomMethod(
        "clearClientAuthenticationCache", &JSWebController::ClearClientAuthenticationCache);
    JSClass<JSWebController>::CustomMethod("getCookieManager", &JSWebController::GetCookieManager);
    JSClass<JSWebController>::CustomMethod("getHitTestValue", &JSWebController::GetHitTestValue);
    JSClass<JSWebController>::CustomMethod("backOrForward", &JSWebController::BackOrForward);
    JSClass<JSWebController>::CustomMethod("zoomIn", &JSWebController::ZoomIn);
    JSClass<JSWebController>::CustomMethod("zoomOut", &JSWebController::ZoomOut);
    JSClass<JSWebController>::CustomMethod("getPageHeight", &JSWebController::GetPageHeight);
    JSClass<JSWebController>::CustomMethod("getTitle", &JSWebController::GetTitle);
    JSClass<JSWebController>::CustomMethod("createWebMessagePorts", &JSWebController::CreateWebMessagePorts);
    JSClass<JSWebController>::CustomMethod("postMessage", &JSWebController::PostWebMessage);
    JSClass<JSWebController>::CustomMethod("getWebId", &JSWebController::GetWebId);
    JSClass<JSWebController>::CustomMethod("getDefaultUserAgent", &JSWebController::GetDefaultUserAgent);
    JSClass<JSWebController>::CustomMethod("searchAllAsync", &JSWebController::SearchAllAsync);
    JSClass<JSWebController>::CustomMethod("clearMatches", &JSWebController::ClearMatches);
    JSClass<JSWebController>::CustomMethod("searchNext", &JSWebController::SearchNext);
    JSClass<JSWebController>::CustomMethod("getUrl", &JSWebController::GetUrl);
    JSClass<JSWebController>::Bind(globalObj, JSWebController::Constructor, JSWebController::Destructor);
    JSWebCookie::JSBind(globalObj);
    JSHitTestValue::JSBind(globalObj);
    JSWebMessagePort::JSBind(globalObj);
    JSWebMessageEvent::JSBind(globalObj);
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

void JSWebController::CreateWebMessagePorts(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        std::vector<RefPtr<WebMessagePort>> ports;
        webController_->CreateMsgPorts(ports);
        JSRef<JSObject> jsPort0 = JSClass<JSWebMessagePort>::NewInstance();
        auto port0 = Referenced::Claim(jsPort0->Unwrap<JSWebMessagePort>());
        port0->SetWebMessagePort(ports.at(0));

        JSRef<JSObject> jsPort1 = JSClass<JSWebMessagePort>::NewInstance();
        auto port1 = Referenced::Claim(jsPort1->Unwrap<JSWebMessagePort>());
        port1->SetWebMessagePort(ports.at(1));

        JSRef<JSArray> result = JSRef<JSArray>::New();
        result->SetValueAt(0, jsPort0);
        result->SetValueAt(1, jsPort1);
        args.SetReturnValue(result);
    }
}

void JSWebController::PostWebMessage(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    std::string uri;
    if (!ConvertFromJSValue(obj->GetProperty("uri"), uri)) {
        return;
    }

    JSRef<JSVal> jsPorts = obj->GetProperty("message");
    if (!jsPorts->IsObject()) {
        return;
    }
    auto jsRes = Referenced::Claim(JSRef<JSObject>::Cast(jsPorts)->Unwrap<JSWebMessageEvent>());
    std::string eventData = jsRes->GetDataInternal();
    std::vector<RefPtr<JSWebMessagePort>> eventPorts = jsRes->GetPortsInternal();
    std::vector<RefPtr<WebMessagePort>> sendPorts;
    for (auto jsport : eventPorts) {
        auto webPort = jsport->GetWebMessagePort();
        if (webPort) {
            sendPorts.push_back(webPort);
        }
    }

    if (webController_ && sendPorts.size() >= 1) {
        webController_->PostWebMessage(eventData, sendPorts, uri);
    }
}

void JSWebController::LoadUrl(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    JSRef<JSVal> valUrl = obj->GetProperty("url");
    std::string url;
    if (valUrl->IsObject()) {
        // same as src process of JSWeb::Create
        std::string webSrc;
        if (!JSViewAbstract::ParseJsMedia(valUrl, webSrc)) {
            return;
        }
        auto np = webSrc.find_first_of("/");
        url = (np == std::string::npos) ? webSrc : webSrc.erase(np, 1);
    } else if (!ConvertFromJSValue(valUrl, url)) {
        return;
    }

    JSRef<JSVal> headers = obj->GetProperty("headers");
    std::map<std::string, std::string> httpHeaders;
    if (headers->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(headers);
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> jsValue = array->GetValueAt(i);
            if (!jsValue->IsObject()) {
                continue;
            }
            JSRef<JSObject> obj = JSRef<JSObject>::Cast(jsValue);
            std::string key;
            if (!ConvertFromJSValue(obj->GetProperty("headerKey"), key)) {
                continue;
            }
            std::string value;
            if (!ConvertFromJSValue(obj->GetProperty("headerValue"), value)) {
                continue;
            }
            httpHeaders[key] = value;
        }
    }
    if (webController_) {
        webController_->LoadUrl(url, httpHeaders);
    }
}

void JSWebController::ExecuteTypeScript(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    std::string script;
    if (!ConvertFromJSValue(obj->GetProperty("script"), script)) {
        return;
    }
    JSRef<JSVal> tsCallback = obj->GetProperty("callback");
    std::function<void(std::string)> callback = nullptr;
    if (tsCallback->IsFunction()) {
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto jsCallback = AceType::MakeRefPtr<JsWebViewFunction>(JSRef<JSFunc>::Cast(tsCallback));
        callback = [execCtx = args.GetExecutionContext(), func = std::move(jsCallback), node = frameNode](
                        std::string result) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("ExecuteTypeScript CallBack");
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            func->Execute(result);
        };
    }
    if (webController_) {
        webController_->ExecuteTypeScript(script, std::move(callback));
    }
}

void JSWebController::LoadDataWithBaseUrl(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
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
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->Backward();
    }
}

void JSWebController::Forward(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->Forward();
    }
}

void JSWebController::AccessStep(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    int32_t step = 0;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], step)) {
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
    ContainerScope scope(instanceId_);
    if (webController_) {
        auto canAccess = webController_->AccessBackward();
        auto jsVal = JSVal(ToJSValue(canAccess));
        auto returnValue = JSRef<JSVal>::Make(jsVal);
        args.SetReturnValue(returnValue);
    }
}

void JSWebController::AccessForward(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        auto canAccess = webController_->AccessForward();
        auto jsVal = JSVal(ToJSValue(canAccess));
        auto returnValue = JSRef<JSVal>::Make(jsVal);
        args.SetReturnValue(returnValue);
    }
}

void JSWebController::ClearHistory(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->ClearHistory();
    }
}

void JSWebController::ClearSslCache(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->ClearSslCache();
    }
}

void JSWebController::ClearClientAuthenticationCache(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->ClearClientAuthenticationCache();
    }
}

void JSWebController::Refresh(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->Refresh();
    }
}

void JSWebController::StopLoading(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->StopLoading();
    }
}

void JSWebController::GetHitTestResult(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        int result = webController_->GetHitTestResult();
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
    }
}

void JSWebController::GetHitTestValue(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (!webController_) {
        return;
    }
    HitTestResult hitResult;
    webController_->GetHitTestValue(hitResult);
    JSRef<JSObject> resultObj = JSClass<JSHitTestValue>::NewInstance();
    auto result = Referenced::Claim(resultObj->Unwrap<JSHitTestValue>());
    result->SetType(hitResult.GetHitType());
    result->SetExtra(hitResult.GetExtraData());
    args.SetReturnValue(resultObj);
}

void JSWebController::GetCookieManager(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        if (!webController_->GetCookieManager()) {
            return;
        }
        if (!jsWebCookieInit_) {
            jsWebCookie_ = JSClass<JSWebCookie>::NewInstance();
            auto jsWebCookieVal = Referenced::Claim(jsWebCookie_->Unwrap<JSWebCookie>());
            jsWebCookieVal->SetWebCookie(webController_->GetCookieManager());
            jsWebCookieInit_ = true;
        }
        args.SetReturnValue(jsWebCookie_);
    }
}

void JSWebController::BackOrForward(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    int32_t step = 0;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], step)) {
        return;
    }
    if (webController_) {
        webController_->BackOrForward(step);
    }
}

void JSWebController::ZoomIn(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        bool result = webController_->ZoomIn();
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
    }
}

void JSWebController::ZoomOut(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        bool result = webController_->ZoomOut();
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
    }
}

void JSWebController::GetPageHeight(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        int result = webController_->GetPageHeight();
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
    }
}

void JSWebController::GetTitle(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        std::string result = webController_->GetTitle();
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
    }
}

void JSWebController::GetWebId(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        int result = webController_->GetWebId();
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
    }
}

void JSWebController::GetDefaultUserAgent(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        std::string result = webController_->GetDefaultUserAgent();
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
    }
}

void JSWebController::SetJavascriptCallBackImpl()
{
    if (!webController_) {
        return;
    }

    WebController::JavaScriptCallBackImpl callback = [weak = WeakClaim(this)](const std::string& objectName,
                                                         const std::string& objectMethod,
                                                         const std::vector<std::shared_ptr<WebJSValue>>& args) {
        auto jsWebController = weak.Upgrade();
        if (jsWebController == nullptr) {
            return std::make_shared<WebJSValue>(WebJSValue::Type::NONE);
        }
        return jsWebController->GetJavaScriptResult(objectName, objectMethod, args);
    };
    webController_->SetJavaScriptCallBackImpl(std::move(callback));
}

void JSWebController::AddJavascriptInterface(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }
    if (webController_ == nullptr) {
        return;
    }
    // Init webview callback
    SetJavascriptCallBackImpl();

    // options
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    // options.name
    std::string objName;
    if (!ConvertFromJSValue(obj->GetProperty("name"), objName)) {
        return;
    }
    // options.obj
    JSRef<JSVal> jsClassObj = obj->GetProperty("object");
    if (!jsClassObj->IsObject()) {
        return;
    }
    if (objectorMap_.find(objName) == objectorMap_.end()) {
        objectorMap_[objName] = JSRef<JSObject>::Cast(jsClassObj);
    }
    // options.methodList
    std::vector<std::string> methods;
    JSRef<JSVal> methodList = obj->GetProperty("methodList");
    if (methodList->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::Cast(methodList);
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> method = array->GetValueAt(i);
            if (method->IsString()) {
                methods.push_back(method->ToString());
            }
        }
    }

    webController_->AddJavascriptInterface(objName, methods);
}

void JSWebController::InitJavascriptInterface()
{
    if (!webController_) {
        return;
    }
    // Init webview callback
    SetJavascriptCallBackImpl();
    for (auto& entry : methods_) {
        webController_->AddJavascriptInterface(entry.first, entry.second);
    }
}

void JSWebController::SetJavascriptInterface(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }
    if (!webController_) {
        return;
    }
    // options
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    // options.name
    std::string objName;
    if (!ConvertFromJSValue(obj->GetProperty("name"), objName)) {
        return;
    }
    // options.obj
    JSRef<JSVal> jsClassObj = obj->GetProperty("object");
    if (!jsClassObj->IsObject()) {
        return;
    }
    objectorMap_[objName] = JSRef<JSObject>::Cast(jsClassObj);
    std::vector<std::string> methods;
    methods_.clear();
    JSRef<JSVal> methodList = obj->GetProperty("methodList");
    if (!methodList->IsArray()) {
        return;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(methodList);
    if (array->IsArray()) {
        for (size_t i = 0; i < array->Length(); i++) {
            JSRef<JSVal> method = array->GetValueAt(i);
            if (method->IsString()) {
                methods.emplace_back(method->ToString());
            }
        }
    }

    JSRef<JSVal> asyncMethodList = obj->GetProperty("asyncMethodList");
    if (asyncMethodList->IsArray()) {
        JSRef<JSArray> asyncArray = JSRef<JSArray>::Cast(asyncMethodList);
        for (size_t i = 0; i < asyncArray->Length(); i++) {
            JSRef<JSVal> asyncMethod = asyncArray->GetValueAt(i);
            if (asyncMethod->IsString()) {
                methods.emplace_back(asyncMethod->ToString());
            }
        }
    }
    methods_[objName] = methods;

    webController_->SetInitJavascriptInterface([weak = WeakClaim(this)]() {
        auto jsWebcontroller = weak.Upgrade();
        if (jsWebcontroller) {
            jsWebcontroller->InitJavascriptInterface();
        }
    });
}

void JSWebController::RemoveJavascriptInterface(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    std::string objName;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], objName)) {
        return;
    }
    if (objectorMap_.find(objName) == objectorMap_.end()) {
        return;
    }
    objectorMap_.erase(objName);
    if (webController_) {
        webController_->RemoveJavascriptInterface(objName, {});
    }
}

void JSWebController::OnInactive(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->OnInactive();
    }
}

void JSWebController::OnActive(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->OnActive();
    }
}

void JSWebController::Zoom(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    float factor = 1.0;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], factor)) {
        return;
    }
    if (webController_) {
        webController_->Zoom(factor);
    }
}

void JSWebController::RequestFocus(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->RequestFocus();
    }
}

void JSWebController::SearchAllAsync(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    std::string searchStr;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], searchStr)) {
        return;
    }
    if (webController_) {
        webController_->SearchAllAsync(searchStr);
    }
}
void JSWebController::ClearMatches(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        webController_->ClearMatches();
    }
}
void JSWebController::SearchNext(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    bool forward = false;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], forward)) {
        return;
    }

    if (webController_) {
        webController_->SearchNext(forward);
    }
}
void JSWebController::GetUrl(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (webController_) {
        std::string result = webController_->GetUrl();
        args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(result)));
    }
}

} // namespace OHOS::Ace::Framework
