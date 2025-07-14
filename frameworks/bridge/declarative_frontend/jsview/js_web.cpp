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

#include "frameworks/bridge/declarative_frontend/jsview/js_web.h"

#include <optional>
#include <string>

#include "adapter/ohos/osal/pixel_map_ohos.h"
#include "pixel_map.h"
#include "pixel_map_napi.h"
#include "securec.h"

#include "base/log/ace_scoring_log.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
#include "base/web/webview/ohos_interface/include/ohos_nweb/nweb.h"
#endif
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/functions/js_common_utils.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/engine/functions/js_event_function.h"
#include "bridge/declarative_frontend/engine/functions/js_key_function.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_web_controller.h"
#include "bridge/declarative_frontend/jsview/models/web_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components/web/web_event.h"
#include "core/components_ng/pattern/web/web_model_ng.h"

namespace OHOS::Ace {
namespace {
const std::string RAWFILE_PREFIX = "resource://RAWFILE/";
const std::string BUNDLE_NAME_PREFIX = "bundleName:";
const std::string MODULE_NAME_PREFIX = "moduleName:";

const int32_t SELECTION_MENU_OPTION_PARAM_INDEX = 3;
const int32_t SELECTION_MENU_CONTENT_PARAM_INDEX = 2;
const int32_t PARAM_ZERO = 0;
const int32_t PARAM_ONE = 1;
const int32_t PARAM_TWO = 2;
constexpr Dimension PREVIEW_MENU_MARGIN_LEFT = 16.0_vp;
constexpr Dimension PREVIEW_MENU_MARGIN_RIGHT = 16.0_vp;
const int32_t WEB_AUDIO_SESSION_TYPE_AMBIENT = 3;

void EraseSpace(std::string& data)
{
    auto iter = data.begin();
    while (iter != data.end()) {
        if (isspace(*iter)) {
            iter = data.erase(iter);
        } else {
            ++iter;
        }
    }
}
}

std::unique_ptr<WebModel> WebModel::instance_ = nullptr;
std::mutex WebModel::mutex_;
WebModel* WebModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::WebModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::WebModelNG());
            } else {
                instance_.reset(new Framework::WebModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
using namespace OHOS::Ace::Framework::CommonUtils;
bool JSWeb::webDebuggingAccess_ = false;
int32_t JSWeb::webDebuggingPort_ = 0;
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

class JSFullScreenExitHandler : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSFullScreenExitHandler>::Declare("FullScreenExitHandler");
        JSClass<JSFullScreenExitHandler>::CustomMethod("exitFullScreen", &JSFullScreenExitHandler::ExitFullScreen);
        JSClass<JSFullScreenExitHandler>::Bind(
            globalObj, &JSFullScreenExitHandler::Constructor, &JSFullScreenExitHandler::Destructor);
    }

    void SetHandler(const RefPtr<FullScreenExitHandler>& handler)
    {
        fullScreenExitHandler_ = handler;
    }

    void ExitFullScreen(const JSCallbackInfo& args)
    {
        if (fullScreenExitHandler_) {
            fullScreenExitHandler_->ExitFullScreen();
        }
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsFullScreenExitHandler = Referenced::MakeRefPtr<JSFullScreenExitHandler>();
        jsFullScreenExitHandler->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsFullScreenExitHandler));
    }

    static void Destructor(JSFullScreenExitHandler* jsFullScreenExitHandler)
    {
        if (jsFullScreenExitHandler != nullptr) {
            jsFullScreenExitHandler->DecRefCount();
        }
    }
    RefPtr<FullScreenExitHandler> fullScreenExitHandler_;
};

class JSWebKeyboardController : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebKeyboardController>::Declare("WebKeyboardController");
        JSClass<JSWebKeyboardController>::CustomMethod("insertText", &JSWebKeyboardController::InsertText);
        JSClass<JSWebKeyboardController>::CustomMethod("deleteForward", &JSWebKeyboardController::DeleteForward);
        JSClass<JSWebKeyboardController>::CustomMethod("deleteBackward", &JSWebKeyboardController::DeleteBackward);
        JSClass<JSWebKeyboardController>::CustomMethod("sendFunctionKey", &JSWebKeyboardController::SendFunctionKey);
        JSClass<JSWebKeyboardController>::CustomMethod("close", &JSWebKeyboardController::Close);
        JSClass<JSWebKeyboardController>::Bind(
            globalObj, &JSWebKeyboardController::Constructor, &JSWebKeyboardController::Destructor);
    }

    void SeWebKeyboardController(const RefPtr<WebCustomKeyboardHandler>& controller)
    {
        webKeyboardController_ = controller;
    }

    void InsertText(const JSCallbackInfo& args)
    {
        if (!webKeyboardController_) {
            return;
        }

        if (args.Length() < 1 || !(args[0]->IsString())) {
            return;
        }

        webKeyboardController_->InsertText(args[0]->ToString());
    }

    void DeleteForward(const JSCallbackInfo& args)
    {
        if (!webKeyboardController_) {
            return;
        }

        if (args.Length() < 1 || !(args[0]->IsNumber())) {
            return;
        }

        webKeyboardController_->DeleteForward(args[0]->ToNumber<int32_t>());
    }

    void DeleteBackward(const JSCallbackInfo& args)
    {
        if (!webKeyboardController_) {
            return;
        }

        if (args.Length() < 1 || !(args[0]->IsNumber())) {
            return;
        }

        webKeyboardController_->DeleteBackward(args[0]->ToNumber<int32_t>());
    }

    void SendFunctionKey(const JSCallbackInfo& args)
    {
        if (!webKeyboardController_) {
            return;
        }

        if (args.Length() < 1 || !(args[0]->IsNumber())) {
            return;
        }

        webKeyboardController_->SendFunctionKey(args[0]->ToNumber<int32_t>());
    }

    void Close(const JSCallbackInfo& args)
    {
        webKeyboardController_->Close();
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jSWebKeyboardController = Referenced::MakeRefPtr<JSWebKeyboardController>();
        jSWebKeyboardController->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jSWebKeyboardController));
    }

    static void Destructor(JSWebKeyboardController* jSWebKeyboardController)
    {
        if (jSWebKeyboardController != nullptr) {
            jSWebKeyboardController->DecRefCount();
        }
    }
    RefPtr<WebCustomKeyboardHandler> webKeyboardController_;
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

class JSWebAllSslError : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebAllSslError>::Declare("WebAllSslErrorResult");
        JSClass<JSWebAllSslError>::CustomMethod("handleConfirm", &JSWebAllSslError::HandleConfirm);
        JSClass<JSWebAllSslError>::CustomMethod("handleCancel", &JSWebAllSslError::HandleCancel);
        JSClass<JSWebAllSslError>::Bind(globalObj, &JSWebAllSslError::Constructor, &JSWebAllSslError::Destructor);
    }

    void SetResult(const RefPtr<AllSslErrorResult>& result)
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
        bool abortLoading = false;
        if (args.Length() >= 1 && args[0]->IsBoolean()) {
            abortLoading = args[0]->ToBoolean();
        }
        if (result_) {
            result_->HandleCancel(abortLoading);
        }
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsWebAllSslError = Referenced::MakeRefPtr<JSWebAllSslError>();
        jsWebAllSslError->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsWebAllSslError));
    }

    static void Destructor(JSWebAllSslError* jsWebAllSslError)
    {
        if (jsWebAllSslError != nullptr) {
            jsWebAllSslError->DecRefCount();
        }
    }

    RefPtr<AllSslErrorResult> result_;
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
        std::string privateKeyFile;
        std::string certChainFile;
        if (args.Length() == 1 && args[0]->IsString()) {
            privateKeyFile = args[0]->ToString();
        } else if (args.Length() == 2 && args[0]->IsString() && args[1]->IsString()) {
            privateKeyFile = args[0]->ToString();
            certChainFile = args[1]->ToString();
        } else {
            return;
        }

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
                    continue;
                }
                std::string res;
                if (!ConvertFromJSValue(val, res)) {
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

class JSScreenCaptureRequest : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSScreenCaptureRequest>::Declare("ScreenCaptureRequest");
        JSClass<JSScreenCaptureRequest>::CustomMethod("deny", &JSScreenCaptureRequest::Deny);
        JSClass<JSScreenCaptureRequest>::CustomMethod("getOrigin", &JSScreenCaptureRequest::GetOrigin);
        JSClass<JSScreenCaptureRequest>::CustomMethod("grant", &JSScreenCaptureRequest::Grant);
        JSClass<JSScreenCaptureRequest>::Bind(
            globalObj, &JSScreenCaptureRequest::Constructor, &JSScreenCaptureRequest::Destructor);
    }

    void SetEvent(const WebScreenCaptureRequestEvent& eventInfo)
    {
        request_ = eventInfo.GetWebScreenCaptureRequest();
    }

    void Deny(const JSCallbackInfo& args)
    {
        if (request_) {
            request_->Deny();
        }
    }

    void GetOrigin(const JSCallbackInfo& args)
    {
        std::string origin;
        if (request_) {
            origin = request_->GetOrigin();
        }
        auto originJs = JSVal(ToJSValue(origin));
        auto originJsRef = JSRef<JSVal>::Make(originJs);
        args.SetReturnValue(originJsRef);
    }

    void Grant(const JSCallbackInfo& args)
    {
        if (!request_) {
            return;
        }
        if (args.Length() < 1 || !args[0]->IsObject()) {
            request_->Deny();
            return;
        }
        JSRef<JSObject> paramObject = JSRef<JSObject>::Cast(args[0]);
        auto captureModeObj = paramObject->GetProperty("captureMode");
        if (!captureModeObj->IsNumber()) {
            request_->Deny();
            return;
        }
        int32_t captureMode = captureModeObj->ToNumber<int32_t>();
        request_->SetCaptureMode(captureMode);
        request_->SetSourceId(-1);
        request_->Grant();
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsScreenCaptureRequest = Referenced::MakeRefPtr<JSScreenCaptureRequest>();
        jsScreenCaptureRequest->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsScreenCaptureRequest));
    }

    static void Destructor(JSScreenCaptureRequest* jsScreenCaptureRequest)
    {
        if (jsScreenCaptureRequest != nullptr) {
            jsScreenCaptureRequest->DecRefCount();
        }
    }

    RefPtr<WebScreenCaptureRequest> request_;
};

class JSNativeEmbedGestureRequest : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSNativeEmbedGestureRequest>::Declare("NativeEmbedGesture");
        JSClass<JSNativeEmbedGestureRequest>::CustomMethod(
            "setGestureEventResult", &JSNativeEmbedGestureRequest::SetGestureEventResult);
        JSClass<JSNativeEmbedGestureRequest>::Bind(
            globalObj, &JSNativeEmbedGestureRequest::Constructor, &JSNativeEmbedGestureRequest::Destructor);
    }

    void SetResult(const RefPtr<GestureEventResult>& result)
    {
        eventResult_ = result;
    }

    void SetGestureEventResult(const JSCallbackInfo& args)
    {
        if (eventResult_) {
            bool result = true;
            bool stopPropagation = true;
            if (args.Length() == PARAM_ONE && args[PARAM_ZERO]->IsBoolean()) {
                result = args[PARAM_ZERO]->ToBoolean();
                eventResult_->SetGestureEventResult(result);
            } else if (args.Length() == PARAM_TWO && args[PARAM_ZERO]->IsBoolean() && args[PARAM_ONE]->IsBoolean()) {
                result = args[PARAM_ZERO]->ToBoolean();
                stopPropagation = args[PARAM_ONE]->ToBoolean();
                eventResult_->SetGestureEventResult(result, stopPropagation);
            }
        }
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jSNativeEmbedGestureRequest = Referenced::MakeRefPtr<JSNativeEmbedGestureRequest>();
        jSNativeEmbedGestureRequest->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jSNativeEmbedGestureRequest));
    }

    static void Destructor(JSNativeEmbedGestureRequest* jSNativeEmbedGestureRequest)
    {
        if (jSNativeEmbedGestureRequest != nullptr) {
            jSNativeEmbedGestureRequest->DecRefCount();
        }
    }

    RefPtr<GestureEventResult> eventResult_;
};

class JSNativeEmbedMouseRequest : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSNativeEmbedMouseRequest>::Declare("NativeEmbedMouse");
        JSClass<JSNativeEmbedMouseRequest>::CustomMethod(
            "setMouseEventResult", &JSNativeEmbedMouseRequest::SetMouseEventResult);
        JSClass<JSNativeEmbedMouseRequest>::Bind(
            globalObj, &JSNativeEmbedMouseRequest::Constructor, &JSNativeEmbedMouseRequest::Destructor);
    }

    void SetResult(const RefPtr<MouseEventResult>& result)
    {
        eventResult_ = result;
    }
    
    void SetMouseEventResult(const JSCallbackInfo& args)
    {
        if (eventResult_) {
            bool result = true;
            bool stopPropagation = true;
            if (args.Length() == PARAM_ONE && args[PARAM_ZERO]->IsBoolean()) {
                result = args[PARAM_ZERO]->ToBoolean();
            } else if (args.Length() == PARAM_TWO && args[PARAM_ZERO]->IsBoolean() && args[PARAM_ONE]->IsBoolean()) {
                result = args[PARAM_ZERO]->ToBoolean();
                stopPropagation = args[PARAM_ONE]->ToBoolean();
            }
            eventResult_->SetMouseEventResult(result, stopPropagation);
        }
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jSNativeEmbedMouseRequest = Referenced::MakeRefPtr<JSNativeEmbedMouseRequest>();
        jSNativeEmbedMouseRequest->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jSNativeEmbedMouseRequest));
    }

    static void Destructor(JSNativeEmbedMouseRequest* jSNativeEmbedMouseRequest)
    {
        if (jSNativeEmbedMouseRequest != nullptr) {
            jSNativeEmbedMouseRequest->DecRefCount();
        }
    }

    RefPtr<MouseEventResult> eventResult_;
};

class JSWebWindowNewHandler : public Referenced {
public:
    struct ChildWindowInfo {
        int32_t parentWebId_ = -1;
        JSRef<JSObject> controller_;
    };

    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebWindowNewHandler>::Declare("WebWindowNewHandler");
        JSClass<JSWebWindowNewHandler>::CustomMethod("setWebController", &JSWebWindowNewHandler::SetWebController);
        JSClass<JSWebWindowNewHandler>::Bind(
            globalObj, &JSWebWindowNewHandler::Constructor, &JSWebWindowNewHandler::Destructor);
    }

    void SetEvent(const WebWindowNewEvent& eventInfo)
    {
        handler_ = eventInfo.GetWebWindowNewHandler();
    }

    static JSRef<JSObject> PopController(int32_t id, int32_t* parentId = nullptr)
    {
        auto iter = controller_map_.find(id);
        if (iter == controller_map_.end()) {
            return JSRef<JSVal>::Make();
        }
        auto controller = iter->second.controller_;
        if (parentId) {
            *parentId = iter->second.parentWebId_;
        }
        controller_map_.erase(iter);
        return controller;
    }

    static bool ExistController(JSRef<JSObject>& controller, int32_t& parentWebId)
    {
        auto getThisVarFunction = controller->GetProperty("innerGetThisVar");
        if (!getThisVarFunction->IsFunction()) {
            parentWebId = -1;
            return false;
        }
        auto func = JSRef<JSFunc>::Cast(getThisVarFunction);
        auto thisVar = func->Call(controller, 0, {});
        int64_t thisPtr = thisVar->ToNumber<int64_t>();
        for (auto iter = controller_map_.begin(); iter != controller_map_.end(); iter++) {
            auto getThisVarFunction1 = iter->second.controller_->GetProperty("innerGetThisVar");
            if (getThisVarFunction1->IsFunction()) {
                auto func1 = JSRef<JSFunc>::Cast(getThisVarFunction1);
                auto thisVar1 = func1->Call(iter->second.controller_, 0, {});
                if (thisPtr == thisVar1->ToNumber<int64_t>()) {
                    parentWebId = iter->second.parentWebId_;
                    return true;
                }
            }
        }
        parentWebId = -1;
        return false;
    }

    void SetWebController(const JSCallbackInfo& args)
    {
        if (handler_) {
            int32_t parentNWebId = handler_->GetParentNWebId();
            if (parentNWebId == -1) {
                TAG_LOGE(AceLogTag::ACE_WEB, "SetWebController parent's web isn't inited");
                return;
            }
            if (args.Length() < 1 || !args[0]->IsObject()) {
                WebModel::GetInstance()->NotifyPopupWindowResult(parentNWebId, false);
                return;
            }
            auto controller = JSRef<JSObject>::Cast(args[0]);
            if (controller.IsEmpty()) {
                WebModel::GetInstance()->NotifyPopupWindowResult(parentNWebId, false);
                return;
            }
            auto getWebIdFunction = controller->GetProperty("innerGetWebId");
            if (!getWebIdFunction->IsFunction()) {
                WebModel::GetInstance()->NotifyPopupWindowResult(parentNWebId, false);
                return;
            }
            auto func = JSRef<JSFunc>::Cast(getWebIdFunction);
            auto webId = func->Call(controller, 0, {});
            int32_t childWebId = webId->ToNumber<int32_t>();
            if (childWebId == parentNWebId || childWebId != -1) {
                WebModel::GetInstance()->NotifyPopupWindowResult(parentNWebId, false);
                return;
            }
            controller_map_.insert(
                std::pair<int32_t, ChildWindowInfo>(handler_->GetId(), { parentNWebId, controller }));
        } else {
            TAG_LOGE(AceLogTag::ACE_WEB, "SetWebController handler is empty");
        }
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsWebWindowNewHandler = Referenced::MakeRefPtr<JSWebWindowNewHandler>();
        jsWebWindowNewHandler->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsWebWindowNewHandler));
    }

    static void Destructor(JSWebWindowNewHandler* jsWebWindowNewHandler)
    {
        if (jsWebWindowNewHandler != nullptr) {
            jsWebWindowNewHandler->DecRefCount();
        }
    }

    RefPtr<WebWindowNewHandler> handler_;
    static std::unordered_map<int32_t, ChildWindowInfo> controller_map_;
};
std::unordered_map<int32_t, JSWebWindowNewHandler::ChildWindowInfo> JSWebWindowNewHandler::controller_map_;

class JSDataResubmitted : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSDataResubmitted>::Declare("DataResubmissionHandler");
        JSClass<JSDataResubmitted>::CustomMethod("resend", &JSDataResubmitted::Resend);
        JSClass<JSDataResubmitted>::CustomMethod("cancel", &JSDataResubmitted::Cancel);
        JSClass<JSDataResubmitted>::Bind(globalObj, &JSDataResubmitted::Constructor, &JSDataResubmitted::Destructor);
    }

    void SetHandler(const RefPtr<DataResubmitted>& handler)
    {
        dataResubmitted_ = handler;
    }

    void Resend(const JSCallbackInfo& args)
    {
        if (dataResubmitted_) {
            dataResubmitted_->Resend();
        }
    }

    void Cancel(const JSCallbackInfo& args)
    {
        if (dataResubmitted_) {
            dataResubmitted_->Cancel();
        }
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsDataResubmitted = Referenced::MakeRefPtr<JSDataResubmitted>();
        jsDataResubmitted->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsDataResubmitted));
    }

    static void Destructor(JSDataResubmitted* jsDataResubmitted)
    {
        if (jsDataResubmitted != nullptr) {
            jsDataResubmitted->DecRefCount();
        }
    }
    RefPtr<DataResubmitted> dataResubmitted_;
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

    void SetOverrideErrorPageEvent(const OnOverrideErrorPageEvent& eventInfo)
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
        JSClass<JSWebResourceResponse>::CustomMethod("getResponseDataEx", &JSWebResourceResponse::GetResponseDataEx);
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
        JSClass<JSWebResourceResponse>::CustomMethod("getResponseIsReady", &JSWebResourceResponse::GetResponseIsReady);
        JSClass<JSWebResourceResponse>::Bind(
            globalObj, &JSWebResourceResponse::Constructor, &JSWebResourceResponse::Destructor);
    }

    JSWebResourceResponse() : response_(AceType::MakeRefPtr<WebResponse>()) {}

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

    void GetResponseDataEx(const JSCallbackInfo& args)
    {
        args.SetReturnValue(responseData_);
    }

    void GetResponseIsReady(const JSCallbackInfo& args)
    {
        auto status = JSVal(ToJSValue(response_->GetResponseStatus()));
        auto descriptionRef = JSRef<JSVal>::Make(status);
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

        responseData_ = args[0];
        if (args[0]->IsNumber()) {
            auto fd = args[0]->ToNumber<int32_t>();
            response_->SetFileHandle(fd);
            return;
        }
        if (args[0]->IsString()) {
            auto data = args[0]->ToString();
            response_->SetData(data);
            return;
        }
        if (args[0]->IsArrayBuffer()) {
            JsiRef<JsiArrayBuffer> arrayBuffer = JsiRef<JsiArrayBuffer>::Cast(args[0]);
            int32_t bufferSize = arrayBuffer->ByteLength();
            void* buffer = arrayBuffer->GetBuffer();
            const char* charPtr = static_cast<const char*>(buffer);
            std::string data(charPtr, bufferSize);
            response_->SetData(data);
            response_->SetBuffer(static_cast<char*>(buffer), bufferSize);
            return;
        }
        if (args[0]->IsObject()) {
            std::string resourceUrl;
            std::string url;
            if (!JSViewAbstract::ParseJsMedia(args[0], resourceUrl)) {
                return;
            }
            auto np = resourceUrl.find_first_of("/");
            url = (np == std::string::npos) ? resourceUrl : resourceUrl.erase(np, 1);
            response_->SetResourceUrl(url);
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
        if (statusCode == -1) {
            TAG_LOGE(AceLogTag::ACE_WEB, "SetResponseCode: arg value is not supported!");
        }

        response_->SetStatusCode(statusCode);
    }

    void SetResponseHeader(const JSCallbackInfo& args)
    {
        if ((args.Length() <= 0) || !(args[0]->IsArray())) {
            return;
        }
        JSRef<JSArray> array = JSRef<JSArray>::Cast(args[0]);
        for (size_t i = 0; i < array->Length(); i++) {
            if (!(array->GetValueAt(i)->IsObject())) {
                return;
            }
            auto obj = JSRef<JSObject>::Cast(array->GetValueAt(i));
            auto headerKey = obj->GetProperty("headerKey");
            auto headerValue = obj->GetProperty("headerValue");
            if (!headerKey->IsString() || !headerValue->IsString()) {
                return;
            }
            auto keystr = headerKey->ToString();
            auto valstr = headerValue->ToString();
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
            return;
        }
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
    JSRef<JSVal> responseData_;
};

class JSWebResourceRequest : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebResourceRequest>::Declare("WebResourceRequest");
        JSClass<JSWebResourceRequest>::CustomMethod("getRequestUrl", &JSWebResourceRequest::GetRequestUrl);
        JSClass<JSWebResourceRequest>::CustomMethod("getRequestHeader", &JSWebResourceRequest::GetRequestHeader);
        JSClass<JSWebResourceRequest>::CustomMethod("getRequestMethod", &JSWebResourceRequest::GetRequestMethod);
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

    void SetOnOverrideErrorPageEvent(const OnOverrideErrorPageEvent& eventInfo)
    {
        request_ = eventInfo.GetWebResourceRequest();
    }

    void SetLoadInterceptEvent(const LoadInterceptEvent& eventInfo)
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

    void GetRequestMethod(const JSCallbackInfo& args)
    {
        auto method = JSVal(ToJSValue(request_->GetMethod()));
        auto descriptionRef = JSRef<JSVal>::Make(method);
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

    void SetLoadOverrideEvent(const LoadOverrideEvent& eventInfo)
    {
        request_ = eventInfo.GetRequest();
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
        JSClass<JSFileSelectorParam>::CustomMethod("getMimeTypes", &JSFileSelectorParam::GetMimeType);
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

    void GetMimeType(const JSCallbackInfo& args)
    {
        auto mimeTypes = param_->GetMimeType();
        JSRef<JSArray> result = JSRef<JSArray>::New();
        std::vector<std::string>::iterator iterator;
        uint32_t index = 0;
        for (iterator = mimeTypes.begin(); iterator != mimeTypes.end(); ++iterator) {
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
                    continue;
                }
                std::string fileName;
                if (!ConvertFromJSValue(val, fileName)) {
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
        JSClass<JSContextMenuParam>::CustomMethod("getUnfilteredLinkUrl", &JSContextMenuParam::GetUnfilteredLinkUrl);
        JSClass<JSContextMenuParam>::CustomMethod("getSourceUrl", &JSContextMenuParam::GetSourceUrl);
        JSClass<JSContextMenuParam>::CustomMethod("existsImageContents", &JSContextMenuParam::HasImageContents);
        JSClass<JSContextMenuParam>::CustomMethod("getSelectionText", &JSContextMenuParam::GetSelectionText);
        JSClass<JSContextMenuParam>::CustomMethod("isEditable", &JSContextMenuParam::IsEditable);
        JSClass<JSContextMenuParam>::CustomMethod("getEditStateFlags", &JSContextMenuParam::GetEditStateFlags);
        JSClass<JSContextMenuParam>::CustomMethod("getSourceType", &JSContextMenuParam::GetSourceType);
        JSClass<JSContextMenuParam>::CustomMethod("getInputFieldType", &JSContextMenuParam::GetInputFieldType);
        JSClass<JSContextMenuParam>::CustomMethod("getMediaType", &JSContextMenuParam::GetMediaType);
        JSClass<JSContextMenuParam>::CustomMethod("getPreviewWidth", &JSContextMenuParam::GetPreviewWidth);
        JSClass<JSContextMenuParam>::CustomMethod("getPreviewHeight", &JSContextMenuParam::GetPreviewHeight);
        JSClass<JSContextMenuParam>::Bind(globalObj, &JSContextMenuParam::Constructor, &JSContextMenuParam::Destructor);
    }

    void UpdatePreviewSize()
    {
        if (previewWidth_ >= 0 && previewHeight_ >= 0) {
            return;
        }
        if (param_) {
            int32_t x = 0;
            int32_t y = 0;
            param_->GetImageRect(x, y, previewWidth_, previewHeight_);
        }
    }

    void GetPreviewWidth(const JSCallbackInfo& args)
    {
        auto ret = JSVal(ToJSValue(previewWidth_));
        auto descriptionRef = JSRef<JSVal>::Make(ret);
        args.SetReturnValue(descriptionRef);
    }

    void GetPreviewHeight(const JSCallbackInfo& args)
    {
        auto ret = JSVal(ToJSValue(previewHeight_));
        auto descriptionRef = JSRef<JSVal>::Make(ret);
        args.SetReturnValue(descriptionRef);
    }

    void SetParam(const ContextMenuEvent& eventInfo)
    {
        param_ = eventInfo.GetParam();
        UpdatePreviewSize();
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

    void GetSelectionText(const JSCallbackInfo& args)
    {
        std::string text;
        if (param_) {
            text = param_->GetSelectionText();
        }
        auto jsText = JSVal(ToJSValue(text));
        auto descriptionRef = JSRef<JSVal>::Make(jsText);
        args.SetReturnValue(descriptionRef);
    }

    void IsEditable(const JSCallbackInfo& args)
    {
        bool flag = false;
        if (param_) {
            flag = param_->IsEditable();
        }
        auto jsFlag = JSVal(ToJSValue(flag));
        auto descriptionRef = JSRef<JSVal>::Make(jsFlag);
        args.SetReturnValue(descriptionRef);
    }

    void GetEditStateFlags(const JSCallbackInfo& args)
    {
        int32_t flags = 0;
        if (param_) {
            flags = param_->GetEditStateFlags();
        }
        auto jsFlags = JSVal(ToJSValue(flags));
        auto descriptionRef = JSRef<JSVal>::Make(jsFlags);
        args.SetReturnValue(descriptionRef);
    }

    void GetSourceType(const JSCallbackInfo& args)
    {
        int32_t type = 0;
        if (param_) {
            type = param_->GetSourceType();
        }
        auto jsType = JSVal(ToJSValue(type));
        auto descriptionRef = JSRef<JSVal>::Make(jsType);
        args.SetReturnValue(descriptionRef);
    }

    void GetInputFieldType(const JSCallbackInfo& args)
    {
        int32_t type = 0;
        if (param_) {
            type = param_->GetInputFieldType();
        }
        auto jsType = JSVal(ToJSValue(type));
        auto descriptionRef = JSRef<JSVal>::Make(jsType);
        args.SetReturnValue(descriptionRef);
    }

    void GetMediaType(const JSCallbackInfo& args)
    {
        int32_t type = 0;
        if (param_) {
            type = param_->GetMediaType();
        }
        auto jsType = JSVal(ToJSValue(type));
        auto descriptionRef = JSRef<JSVal>::Make(jsType);
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

    int32_t previewWidth_ = -1;

    int32_t previewHeight_ = -1;
};

class JSContextMenuResult : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSContextMenuResult>::Declare("WebContextMenuResult");
        JSClass<JSContextMenuResult>::CustomMethod("closeContextMenu", &JSContextMenuResult::Cancel);
        JSClass<JSContextMenuResult>::CustomMethod("copyImage", &JSContextMenuResult::CopyImage);
        JSClass<JSContextMenuResult>::CustomMethod("copy", &JSContextMenuResult::Copy);
        JSClass<JSContextMenuResult>::CustomMethod("paste", &JSContextMenuResult::Paste);
        JSClass<JSContextMenuResult>::CustomMethod("cut", &JSContextMenuResult::Cut);
        JSClass<JSContextMenuResult>::CustomMethod("selectAll", &JSContextMenuResult::SelectAll);
        JSClass<JSContextMenuResult>::CustomMethod("undo", &JSContextMenuResult::Undo);
        JSClass<JSContextMenuResult>::CustomMethod("redo", &JSContextMenuResult::Redo);
        JSClass<JSContextMenuResult>::CustomMethod("pasteAndMatchStyle", &JSContextMenuResult::PasteAndMatchStyle);
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

    void Copy(const JSCallbackInfo& args)
    {
        if (result_) {
            result_->Copy();
        }
    }

    void Paste(const JSCallbackInfo& args)
    {
        if (result_) {
            result_->Paste();
        }
    }

    void Cut(const JSCallbackInfo& args)
    {
        if (result_) {
            result_->Cut();
        }
    }

    void SelectAll(const JSCallbackInfo& args)
    {
        if (result_) {
            result_->SelectAll();
        }
    }

    void Undo(const JSCallbackInfo& args)
    {
        if (result_) {
            result_->Undo();
        }
    }

    void Redo(const JSCallbackInfo& args)
    {
        if (result_) {
            result_->Redo();
        }
    }

    void PasteAndMatchStyle(const JSCallbackInfo& args)
    {
        if (result_) {
            result_->PasteAndMatchStyle();
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

class JSWebAppLinkCallback : public Referenced {
public:
    static void JSBind(BindingTarget globalObj)
    {
        JSClass<JSWebAppLinkCallback>::Declare("WebAppLinkCallback");
        JSClass<JSWebAppLinkCallback>::CustomMethod("continueLoad", &JSWebAppLinkCallback::ContinueLoad);
        JSClass<JSWebAppLinkCallback>::CustomMethod("cancelLoad", &JSWebAppLinkCallback::CancelLoad);
        JSClass<JSWebAppLinkCallback>::Bind(
            globalObj, &JSWebAppLinkCallback::Constructor, &JSWebAppLinkCallback::Destructor);
    }

    void SetEvent(const WebAppLinkEvent& eventInfo)
    {
        callback_ = eventInfo.GetCallback();
    }

    void ContinueLoad(const JSCallbackInfo& args)
    {
        if (callback_) {
            callback_->ContinueLoad();
        }
    }

    void CancelLoad(const JSCallbackInfo& args)
    {
        if (callback_) {
            callback_->CancelLoad();
        }
    }

private:
    static void Constructor(const JSCallbackInfo& args)
    {
        auto jsWebAppLinkCallback = Referenced::MakeRefPtr<JSWebAppLinkCallback>();
        jsWebAppLinkCallback->IncRefCount();
        args.SetReturnValue(Referenced::RawPtr(jsWebAppLinkCallback));
    }

    static void Destructor(JSWebAppLinkCallback* jsWebAppLinkCallback)
    {
        if (jsWebAppLinkCallback != nullptr) {
            jsWebAppLinkCallback->DecRefCount();
        }
    }

    RefPtr<WebAppLinkCallback> callback_;
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
    JSClass<JSWeb>::StaticMethod("onFullScreenEnter", &JSWeb::OnFullScreenEnter);
    JSClass<JSWeb>::StaticMethod("onFullScreenExit", &JSWeb::OnFullScreenExit);
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
    JSClass<JSWeb>::StaticMethod("onOverrideErrorPage", &JSWeb::OnOverrideErrorPage);
    JSClass<JSWeb>::StaticMethod("onUrlLoadIntercept", &JSWeb::OnUrlLoadIntercept);
    JSClass<JSWeb>::StaticMethod("onLoadIntercept", &JSWeb::OnLoadIntercept);
    JSClass<JSWeb>::StaticMethod("onlineImageAccess", &JSWeb::OnLineImageAccessEnabled);
    JSClass<JSWeb>::StaticMethod("domStorageAccess", &JSWeb::DomStorageAccessEnabled);
    JSClass<JSWeb>::StaticMethod("imageAccess", &JSWeb::ImageAccessEnabled);
    JSClass<JSWeb>::StaticMethod("mixedMode", &JSWeb::MixedMode);
    JSClass<JSWeb>::StaticMethod("enableNativeEmbedMode", &JSWeb::EnableNativeEmbedMode);
    JSClass<JSWeb>::StaticMethod("nativeEmbedOptions", &JSWeb::NativeEmbedOptions);
    JSClass<JSWeb>::StaticMethod("registerNativeEmbedRule", &JSWeb::RegisterNativeEmbedRule);
    JSClass<JSWeb>::StaticMethod("zoomAccess", &JSWeb::ZoomAccessEnabled);
    JSClass<JSWeb>::StaticMethod("geolocationAccess", &JSWeb::GeolocationAccessEnabled);
    JSClass<JSWeb>::StaticMethod("javaScriptProxy", &JSWeb::JavaScriptProxy);
    JSClass<JSWeb>::StaticMethod("userAgent", &JSWeb::UserAgent);
    JSClass<JSWeb>::StaticMethod("onRenderExited", &JSWeb::OnRenderExited);
    JSClass<JSWeb>::StaticMethod("onRefreshAccessedHistory", &JSWeb::OnRefreshAccessedHistory);
    JSClass<JSWeb>::StaticMethod("cacheMode", &JSWeb::CacheMode);
    JSClass<JSWeb>::StaticMethod("overviewModeAccess", &JSWeb::OverviewModeAccess);
    JSClass<JSWeb>::StaticMethod("webDebuggingAccess", &JSWeb::WebDebuggingAccess);
    JSClass<JSWeb>::StaticMethod("wideViewModeAccess", &JSWeb::WideViewModeAccess);
    JSClass<JSWeb>::StaticMethod("fileFromUrlAccess", &JSWeb::FileFromUrlAccess);
    JSClass<JSWeb>::StaticMethod("databaseAccess", &JSWeb::DatabaseAccess);
    JSClass<JSWeb>::StaticMethod("textZoomRatio", &JSWeb::TextZoomRatio);
    JSClass<JSWeb>::StaticMethod("textZoomAtio", &JSWeb::TextZoomRatio);
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
    JSClass<JSWeb>::StaticMethod("onSslErrorReceive", &JSWeb::OnSslErrRequest);
    JSClass<JSWeb>::StaticMethod("onSslErrorEventReceive", &JSWeb::OnSslErrorRequest);
    JSClass<JSWeb>::StaticMethod("onSslErrorEvent", &JSWeb::OnAllSslErrorRequest);
    JSClass<JSWeb>::StaticMethod("onClientAuthenticationRequest", &JSWeb::OnSslSelectCertRequest);
    JSClass<JSWeb>::StaticMethod("onPermissionRequest", &JSWeb::OnPermissionRequest);
    JSClass<JSWeb>::StaticMethod("onContextMenuShow", &JSWeb::OnContextMenuShow);
    JSClass<JSWeb>::StaticMethod("onContextMenuHide", &JSWeb::OnContextMenuHide);
    JSClass<JSWeb>::StaticMethod("onSearchResultReceive", &JSWeb::OnSearchResultReceive);
    JSClass<JSWeb>::StaticMethod("mediaPlayGestureAccess", &JSWeb::MediaPlayGestureAccess);
    JSClass<JSWeb>::StaticMethod("onDragStart", &JSWeb::JsOnDragStart);
    JSClass<JSWeb>::StaticMethod("onDragEnter", &JSWeb::JsOnDragEnter);
    JSClass<JSWeb>::StaticMethod("onDragMove", &JSWeb::JsOnDragMove);
    JSClass<JSWeb>::StaticMethod("onDragLeave", &JSWeb::JsOnDragLeave);
    JSClass<JSWeb>::StaticMethod("onDrop", &JSWeb::JsOnDrop);
    JSClass<JSWeb>::StaticMethod("onScroll", &JSWeb::OnScroll);
    JSClass<JSWeb>::StaticMethod("rotate", &JSWeb::WebRotate);
    JSClass<JSWeb>::StaticMethod("pinchSmooth", &JSWeb::PinchSmoothModeEnabled);
    JSClass<JSWeb>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSWeb>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSWeb>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSWeb>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSWeb>::StaticMethod("onWindowNew", &JSWeb::OnWindowNew);
    JSClass<JSWeb>::StaticMethod("onActivateContent", &JSWeb::OnActivateContent);
    JSClass<JSWeb>::StaticMethod("onWindowExit", &JSWeb::OnWindowExit);
    JSClass<JSWeb>::StaticMethod("multiWindowAccess", &JSWeb::MultiWindowAccessEnabled);
    JSClass<JSWeb>::StaticMethod("allowWindowOpenMethod", &JSWeb::AllowWindowOpenMethod);
    JSClass<JSWeb>::StaticMethod("webCursiveFont", &JSWeb::WebCursiveFont);
    JSClass<JSWeb>::StaticMethod("webFantasyFont", &JSWeb::WebFantasyFont);
    JSClass<JSWeb>::StaticMethod("webFixedFont", &JSWeb::WebFixedFont);
    JSClass<JSWeb>::StaticMethod("webSansSerifFont", &JSWeb::WebSansSerifFont);
    JSClass<JSWeb>::StaticMethod("webSerifFont", &JSWeb::WebSerifFont);
    JSClass<JSWeb>::StaticMethod("webStandardFont", &JSWeb::WebStandardFont);
    JSClass<JSWeb>::StaticMethod("defaultFixedFontSize", &JSWeb::DefaultFixedFontSize);
    JSClass<JSWeb>::StaticMethod("defaultFontSize", &JSWeb::DefaultFontSize);
    JSClass<JSWeb>::StaticMethod("defaultTextEncodingFormat", &JSWeb::DefaultTextEncodingFormat);
    JSClass<JSWeb>::StaticMethod("minFontSize", &JSWeb::MinFontSize);
    JSClass<JSWeb>::StaticMethod("minLogicalFontSize", &JSWeb::MinLogicalFontSize);
    JSClass<JSWeb>::StaticMethod("blockNetwork", &JSWeb::BlockNetwork);
    JSClass<JSWeb>::StaticMethod("onPageVisible", &JSWeb::OnPageVisible);
    JSClass<JSWeb>::StaticMethod("onInterceptKeyEvent", &JSWeb::OnInterceptKeyEvent);
    JSClass<JSWeb>::StaticMethod("onDataResubmitted", &JSWeb::OnDataResubmitted);
    JSClass<JSWeb>::StaticMethod("onFaviconReceived", &JSWeb::OnFaviconReceived);
    JSClass<JSWeb>::StaticMethod("onTouchIconUrlReceived", &JSWeb::OnTouchIconUrlReceived);
    JSClass<JSWeb>::StaticMethod("darkMode", &JSWeb::DarkMode);
    JSClass<JSWeb>::StaticMethod("forceDarkAccess", &JSWeb::ForceDarkAccess);
    JSClass<JSWeb>::StaticMethod("overScrollMode", &JSWeb::OverScrollMode);
    JSClass<JSWeb>::StaticMethod("blurOnKeyboardHideMode", &JSWeb::BlurOnKeyboardHideMode);
    JSClass<JSWeb>::StaticMethod("horizontalScrollBarAccess", &JSWeb::HorizontalScrollBarAccess);
    JSClass<JSWeb>::StaticMethod("verticalScrollBarAccess", &JSWeb::VerticalScrollBarAccess);
    JSClass<JSWeb>::StaticMethod("onAudioStateChanged", &JSWeb::OnAudioStateChanged);
    JSClass<JSWeb>::StaticMethod("mediaOptions", &JSWeb::MediaOptions);
    JSClass<JSWeb>::StaticMethod("onFirstContentfulPaint", &JSWeb::OnFirstContentfulPaint);
    JSClass<JSWeb>::StaticMethod("onFirstMeaningfulPaint", &JSWeb::OnFirstMeaningfulPaint);
    JSClass<JSWeb>::StaticMethod("onLargestContentfulPaint", &JSWeb::OnLargestContentfulPaint);
    JSClass<JSWeb>::StaticMethod("onSafeBrowsingCheckResult", &JSWeb::OnSafeBrowsingCheckResult);
    JSClass<JSWeb>::StaticMethod("onNavigationEntryCommitted", &JSWeb::OnNavigationEntryCommitted);
    JSClass<JSWeb>::StaticMethod("onIntelligentTrackingPreventionResult",
        &JSWeb::OnIntelligentTrackingPreventionResult);
    JSClass<JSWeb>::StaticMethod("onControllerAttached", &JSWeb::OnControllerAttached);
    JSClass<JSWeb>::StaticMethod("onOverScroll", &JSWeb::OnOverScroll);
    JSClass<JSWeb>::StaticMethod("onNativeEmbedLifecycleChange", &JSWeb::OnNativeEmbedLifecycleChange);
    JSClass<JSWeb>::StaticMethod("onNativeEmbedVisibilityChange", &JSWeb::OnNativeEmbedVisibilityChange);
    JSClass<JSWeb>::StaticMethod("onNativeEmbedGestureEvent", &JSWeb::OnNativeEmbedGestureEvent);
    JSClass<JSWeb>::StaticMethod("onNativeEmbedMouseEvent", &JSWeb::OnNativeEmbedMouseEvent);
    JSClass<JSWeb>::StaticMethod("copyOptions", &JSWeb::CopyOption);
    JSClass<JSWeb>::StaticMethod("onScreenCaptureRequest", &JSWeb::OnScreenCaptureRequest);
    JSClass<JSWeb>::StaticMethod("layoutMode", &JSWeb::SetLayoutMode);
    JSClass<JSWeb>::StaticMethod("nestedScroll", &JSWeb::SetNestedScroll);
    JSClass<JSWeb>::StaticMethod("metaViewport", &JSWeb::SetMetaViewport);
    JSClass<JSWeb>::StaticMethod("javaScriptOnDocumentStart", &JSWeb::JavaScriptOnDocumentStart);
    JSClass<JSWeb>::StaticMethod("javaScriptOnDocumentEnd", &JSWeb::JavaScriptOnDocumentEnd);
    JSClass<JSWeb>::StaticMethod("onOverrideUrlLoading", &JSWeb::OnOverrideUrlLoading);
    JSClass<JSWeb>::StaticMethod("textAutosizing", &JSWeb::TextAutosizing);
    JSClass<JSWeb>::StaticMethod("enableNativeMediaPlayer", &JSWeb::EnableNativeVideoPlayer);
    JSClass<JSWeb>::StaticMethod("onRenderProcessNotResponding", &JSWeb::OnRenderProcessNotResponding);
    JSClass<JSWeb>::StaticMethod("onRenderProcessResponding", &JSWeb::OnRenderProcessResponding);
    JSClass<JSWeb>::StaticMethod("selectionMenuOptions", &JSWeb::SelectionMenuOptions);
    JSClass<JSWeb>::StaticMethod("onViewportFitChanged", &JSWeb::OnViewportFitChanged);
    JSClass<JSWeb>::StaticMethod("onInterceptKeyboardAttach", &JSWeb::OnInterceptKeyboardAttach);
    JSClass<JSWeb>::StaticMethod("onAdsBlocked", &JSWeb::OnAdsBlocked);
    JSClass<JSWeb>::StaticMethod("forceDisplayScrollBar", &JSWeb::ForceDisplayScrollBar);
    JSClass<JSWeb>::StaticMethod("keyboardAvoidMode", &JSWeb::KeyboardAvoidMode);
    JSClass<JSWeb>::StaticMethod("editMenuOptions", &JSWeb::EditMenuOptions);
    JSClass<JSWeb>::StaticMethod("enableHapticFeedback", &JSWeb::EnableHapticFeedback);
    JSClass<JSWeb>::StaticMethod("bindSelectionMenu", &JSWeb::BindSelectionMenu);
    JSClass<JSWeb>::StaticMethod("optimizeParserBudget", &JSWeb::OptimizeParserBudgetEnabled);
    JSClass<JSWeb>::StaticMethod("runJavaScriptOnHeadEnd", &JSWeb::RunJavaScriptOnHeadEnd);
    JSClass<JSWeb>::StaticMethod("runJavaScriptOnDocumentStart", &JSWeb::RunJavaScriptOnDocumentStart);
    JSClass<JSWeb>::StaticMethod("runJavaScriptOnDocumentEnd", &JSWeb::RunJavaScriptOnDocumentEnd);
    JSClass<JSWeb>::StaticMethod("enableWebAVSession", &JSWeb::EnableWebAVSession);
    JSClass<JSWeb>::StaticMethod("enableDataDetector", &JSWeb::EnableDataDetector);
    JSClass<JSWeb>::StaticMethod("dataDetectorConfig", &JSWeb::DataDetectorConfig);
    JSClass<JSWeb>::StaticMethod("bypassVsyncCondition", &JSWeb::BypassVsyncCondition);
    JSClass<JSWeb>::StaticMethod("enableFollowSystemFontWeight", &JSWeb::EnableFollowSystemFontWeight);
    JSClass<JSWeb>::StaticMethod("gestureFocusMode", &JSWeb::GestureFocusMode);
    JSClass<JSWeb>::StaticMethod("onPdfScrollAtBottom", &JSWeb::OnPdfScrollAtBottom);
    JSClass<JSWeb>::StaticMethod("onPdfLoadEvent", &JSWeb::OnPdfLoadEvent);
    JSClass<JSWeb>::InheritAndBind<JSViewAbstract>(globalObj);
    JSWebDialog::JSBind(globalObj);
    JSWebGeolocation::JSBind(globalObj);
    JSWebResourceRequest::JSBind(globalObj);
    JSWebResourceError::JSBind(globalObj);
    JSWebResourceResponse::JSBind(globalObj);
    JSWebConsoleLog::JSBind(globalObj);
    JSFileSelectorParam::JSBind(globalObj);
    JSFileSelectorResult::JSBind(globalObj);
    JSFullScreenExitHandler::JSBind(globalObj);
    JSWebHttpAuth::JSBind(globalObj);
    JSWebSslError::JSBind(globalObj);
    JSWebAllSslError::JSBind(globalObj);
    JSWebSslSelectCert::JSBind(globalObj);
    JSWebPermissionRequest::JSBind(globalObj);
    JSContextMenuParam::JSBind(globalObj);
    JSContextMenuResult::JSBind(globalObj);
    JSWebWindowNewHandler::JSBind(globalObj);
    JSDataResubmitted::JSBind(globalObj);
    JSScreenCaptureRequest::JSBind(globalObj);
    JSNativeEmbedGestureRequest::JSBind(globalObj);
    JSNativeEmbedMouseRequest::JSBind(globalObj);
    JSWebAppLinkCallback::JSBind(globalObj);
    JSWebKeyboardController::JSBind(globalObj);
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

JSRef<JSVal> JSWeb::CreateConsoleHandler(const LoadWebConsoleLogEvent& eventInfo)
{
    JSRef<JSObject> messageObj = JSClass<JSWebConsoleLog>::NewInstance();
    auto jsWebConsoleLog = Referenced::Claim(messageObj->Unwrap<JSWebConsoleLog>());
    if (!jsWebConsoleLog) {
        return messageObj;
    }
    jsWebConsoleLog->SetMessage(eventInfo.GetMessage());
    return messageObj;
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
    if (eventInfo.GetType() == DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD) {
        obj->SetProperty("isReload", eventInfo.GetIsReload());
    }
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> JSWeb::CreateCommonDialogResultHandler(const WebDialogEvent& eventInfo)
{
    JSRef<JSObject> resultObj = JSClass<JSWebDialog>::NewInstance();
    auto jsWebDialog = Referenced::Claim(resultObj->Unwrap<JSWebDialog>());
    jsWebDialog->SetResult(eventInfo.GetResult());
    return resultObj;
}

JSRef<JSVal> LoadWebPageFinishEventToJSValue(const LoadWebPageFinishEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("url", eventInfo.GetLoadedUrl());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> ContextMenuHideEventToJSValue(const ContextMenuHideEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("info", eventInfo.GetInfo());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> PdfScrollEventToJSValue(const PdfScrollEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("url", eventInfo.GetUrl());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> PdfLoadEventToJSValue(const PdfLoadEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("result", eventInfo.GetResult());
    obj->SetProperty("url", eventInfo.GetUrl());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> FullScreenEnterEventToJSValue(const FullScreenEnterEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSObject> resultObj = JSClass<JSFullScreenExitHandler>::NewInstance();
    auto jsFullScreenExitHandler = Referenced::Claim(resultObj->Unwrap<JSFullScreenExitHandler>());
    if (!jsFullScreenExitHandler) {
        return JSRef<JSVal>::Cast(obj);
    }
    jsFullScreenExitHandler->SetHandler(eventInfo.GetHandler());

    obj->SetPropertyObject("handler", resultObj);
    obj->SetProperty("videoWidth", eventInfo.GetVideoNaturalWidth());
    obj->SetProperty("videoHeight", eventInfo.GetVideoNaturalHeight());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> JSWeb::CreateFullScreenEnterHandler(const FullScreenEnterEvent& eventInfo)
{
    JSRef<JSObject> resultObj = JSClass<JSFullScreenExitHandler>::NewInstance();
    auto jsFullScreenExitHandler = Referenced::Claim(resultObj->Unwrap<JSFullScreenExitHandler>());
    jsFullScreenExitHandler->SetHandler(eventInfo.GetHandler());
    return resultObj;
}

JSRef<JSVal> FullScreenExitEventToJSValue(const FullScreenExitEvent& eventInfo)
{
    return JSRef<JSVal>::Make(ToJSValue(eventInfo.IsFullScreen()));
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
    obj->SetProperty("isRealTitle", eventInfo.GetIsRealTitle());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> UrlLoadInterceptEventToJSValue(const UrlLoadInterceptEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("data", eventInfo.GetData());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> LoadInterceptEventToJSValue(const LoadInterceptEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSObject> requestObj = JSClass<JSWebResourceRequest>::NewInstance();
    auto requestEvent = Referenced::Claim(requestObj->Unwrap<JSWebResourceRequest>());
    requestEvent->SetLoadInterceptEvent(eventInfo);
    obj->SetPropertyObject("data", requestObj);
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> JSWeb::CreateLoadInterceptHandler(const LoadInterceptEvent& eventInfo)
{
    JSRef<JSObject> requestObj = JSClass<JSWebResourceRequest>::NewInstance();
    auto requestEvent = Referenced::Claim(requestObj->Unwrap<JSWebResourceRequest>());
    if (!requestEvent) {
        return requestObj;
    }
    requestEvent->SetLoadInterceptEvent(eventInfo);
    return requestObj;
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

JSRef<JSVal> JSWeb::CreateGeolocationShowHandler(const LoadWebGeolocationShowEvent& eventInfo)
{
    JSRef<JSObject> geolocationObj = JSClass<JSWebGeolocation>::NewInstance();
    auto geolocationEvent = Referenced::Claim(geolocationObj->Unwrap<JSWebGeolocation>());
    geolocationEvent->SetEvent(eventInfo);
    return geolocationObj;
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
        return JSRef<JSVal>::Cast(obj);
    }
    jsWebHttpAuth->SetResult(eventInfo.GetResult());
    obj->SetPropertyObject("handler", resultObj);
    obj->SetProperty("host", eventInfo.GetHost());
    obj->SetProperty("realm", eventInfo.GetRealm());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> JSWeb::CreateHttpAuthRequestHandler(const WebHttpAuthEvent& eventInfo)
{
    JSRef<JSObject> resultObj = JSClass<JSWebHttpAuth>::NewInstance();
    auto jsWebHttpAuth = Referenced::Claim(resultObj->Unwrap<JSWebHttpAuth>());
    if (!jsWebHttpAuth) {
        return resultObj;
    }
    jsWebHttpAuth->SetResult(eventInfo.GetResult());
    return resultObj;
}

JSRef<JSVal> WebSslErrorEventToJSValue(const WebSslErrorEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSObject> resultObj = JSClass<JSWebSslError>::NewInstance();
    auto jsWebSslError = Referenced::Claim(resultObj->Unwrap<JSWebSslError>());
    if (!jsWebSslError) {
        return JSRef<JSVal>::Cast(obj);
    }
    jsWebSslError->SetResult(eventInfo.GetResult());
    obj->SetPropertyObject("handler", resultObj);
    obj->SetProperty("error", eventInfo.GetError());

    auto engine = EngineHelper::GetCurrentEngine();
    if (!engine) {
        return JSRef<JSVal>::Cast(obj);
    }
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    std::vector<std::string> certChainDerData = eventInfo.GetCertChainData();
    JSRef<JSArray> certsArr = JSRef<JSArray>::New();
    for (uint8_t i = 0; i < certChainDerData.size(); i++) {
        if (i == UINT8_MAX) {
            TAG_LOGE(AceLogTag::ACE_WEB, "Cert chain data array reach max.");
            break;
        }

        void *data = nullptr;
        napi_value buffer = nullptr;
        napi_value item = nullptr;
        napi_status status = napi_create_arraybuffer(env, certChainDerData[i].size(), &data, &buffer);
        if (status != napi_ok) {
            TAG_LOGE(AceLogTag::ACE_WEB, "Create array buffer failed, status = %{public}d.", status);
            continue;
        }
        int retCode = memcpy_s(data, certChainDerData[i].size(),
                               certChainDerData[i].data(), certChainDerData[i].size());
        if (retCode != 0) {
            TAG_LOGE(AceLogTag::ACE_WEB, "Cert chain data failed, index = %{public}u.", i);
            continue;
        }
        status = napi_create_typedarray(env, napi_uint8_array, certChainDerData[i].size(), buffer, 0, &item);
        if (status != napi_ok) {
            TAG_LOGE(AceLogTag::ACE_WEB, "Create typed array failed, status = %{public}d.", status);
            continue;
        }
        JSRef<JSVal> cert = JsConverter::ConvertNapiValueToJsVal(item);
        certsArr->SetValueAt(i, cert);
    }
    obj->SetPropertyObject("certChainData", certsArr);
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> JSWeb::CreateSslErrorEventReceiveHandler(const WebSslErrorEvent& eventInfo)
{
    JSRef<JSObject> resultObj = JSClass<JSWebSslError>::NewInstance();
    auto jsWebSslError = Referenced::Claim(resultObj->Unwrap<JSWebSslError>());
    if (!jsWebSslError) {
        return resultObj;
    }
    jsWebSslError->SetResult(eventInfo.GetResult());
    return resultObj;
}

JSRef<JSVal> WebAllSslErrorEventToJSValue(const WebAllSslErrorEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSObject> resultObj = JSClass<JSWebAllSslError>::NewInstance();
    auto jsWebAllSslError = Referenced::Claim(resultObj->Unwrap<JSWebAllSslError>());
    if (!jsWebAllSslError) {
        return JSRef<JSVal>::Cast(obj);
    }
    jsWebAllSslError->SetResult(eventInfo.GetResult());
    obj->SetPropertyObject("handler", resultObj);
    obj->SetProperty("error", eventInfo.GetError());
    obj->SetProperty("url", eventInfo.GetUrl());
    obj->SetProperty("originalUrl", eventInfo.GetOriginalUrl());
    obj->SetProperty("referrer", eventInfo.GetReferrer());
    obj->SetProperty("isFatalError", eventInfo.GetIsFatalError());
    obj->SetProperty("isMainFrame", eventInfo.GetIsMainFrame());

    auto engine = EngineHelper::GetCurrentEngine();
    if (!engine || !engine->GetNativeEngine()) {
        return JSRef<JSVal>::Cast(obj);
    }
    napi_env env = reinterpret_cast<napi_env>(engine->GetNativeEngine());
    std::vector<std::string> certChainDerData = eventInfo.GetCertChainData();
    JSRef<JSArray> certsArr = JSRef<JSArray>::New();
    for (uint8_t i = 0; i < certChainDerData.size(); i++) {
        if (i == UINT8_MAX) {
            TAG_LOGE(AceLogTag::ACE_WEB, "Cert chain data array reach max.");
            break;
        }
        void *data = nullptr;
        napi_value buffer = nullptr;
        napi_value item = nullptr;
        napi_status status = napi_create_arraybuffer(env, certChainDerData[i].size(), &data, &buffer);
        if (status != napi_ok) {
            TAG_LOGE(AceLogTag::ACE_WEB, "Create array buffer failed, status = %{public}d.", status);
            continue;
        }
        if (memcpy_s(data, certChainDerData[i].size(), certChainDerData[i].data(), certChainDerData[i].size()) != 0) {
            TAG_LOGE(AceLogTag::ACE_WEB, "Cert chain data failed, index = %{public}u.", i);
            continue;
        }
        status = napi_create_typedarray(env, napi_uint8_array, certChainDerData[i].size(), buffer, 0, &item);
        if (status != napi_ok) {
            TAG_LOGE(AceLogTag::ACE_WEB, "Create typed array failed, status = %{public}d.", status);
            continue;
        }
        JSRef<JSVal> cert = JsConverter::ConvertNapiValueToJsVal(item);
        certsArr->SetValueAt(i, cert);
    }
    obj->SetPropertyObject("certChainData", certsArr);
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> JSWeb::CreateSslErrorEventHandler(const WebAllSslErrorEvent& eventInfo)
{
    JSRef<JSObject> resultObj = JSClass<JSWebAllSslError>::NewInstance();
    auto jsWebAllSslError = Referenced::Claim(resultObj->Unwrap<JSWebAllSslError>());
    if (!jsWebAllSslError) {
        return resultObj;
    }
    jsWebAllSslError->SetResult(eventInfo.GetResult());
    return resultObj;
}

JSRef<JSVal> WebSslSelectCertEventToJSValue(const WebSslSelectCertEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSObject> resultObj = JSClass<JSWebSslSelectCert>::NewInstance();
    auto jsWebSslSelectCert = Referenced::Claim(resultObj->Unwrap<JSWebSslSelectCert>());
    if (!jsWebSslSelectCert) {
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

JSRef<JSVal> JSWeb::CreateClientAuthenticationRequestHandler(const WebSslSelectCertEvent& eventInfo)
{
    JSRef<JSObject> resultObj = JSClass<JSWebSslSelectCert>::NewInstance();
    auto jsWebSslSelectCert = Referenced::Claim(resultObj->Unwrap<JSWebSslSelectCert>());
    if (!jsWebSslSelectCert) {
        return resultObj;
    }
    jsWebSslSelectCert->SetResult(eventInfo.GetResult());
    return resultObj;
}

JSRef<JSVal> SearchResultReceiveEventToJSValue(const SearchResultReceiveEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("activeMatchOrdinal", eventInfo.GetActiveMatchOrdinal());
    obj->SetProperty("numberOfMatches", eventInfo.GetNumberOfMatches());
    obj->SetProperty("isDoneCounting", eventInfo.GetIsDoneCounting());
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> LoadOverrideEventToJSValue(const LoadOverrideEvent& eventInfo)
{
    JSRef<JSObject> requestObj = JSClass<JSWebResourceRequest>::NewInstance();
    auto requestEvent = Referenced::Claim(requestObj->Unwrap<JSWebResourceRequest>());
    requestEvent->SetLoadOverrideEvent(eventInfo);
    return JSRef<JSVal>::Cast(requestObj);
}

JSRef<JSVal> JSWeb::CreateOverrideUrlLoadingHandler(const LoadOverrideEvent& eventInfo)
{
    JSRef<JSObject> requestObj = JSClass<JSWebResourceRequest>::NewInstance();
    auto requestEvent = Referenced::Claim(requestObj->Unwrap<JSWebResourceRequest>());
    if (!requestEvent) {
        return requestObj;
    }
    requestEvent->SetLoadOverrideEvent(eventInfo);
    return requestObj;
}

JSRef<JSVal> AdsBlockedEventToJSValue(const AdsBlockedEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("url", eventInfo.GetUrl());

    JSRef<JSArray> adsBlockedArr = JSRef<JSArray>::New();
    const std::vector<std::string>& adsBlocked = eventInfo.GetAdsBlocked();
    for (int32_t idx = 0; idx < static_cast<int32_t>(adsBlocked.size()); ++idx) {
        JSRef<JSVal> blockedUrl = JSRef<JSVal>::Make(ToJSValue(adsBlocked[idx]));
        adsBlockedArr->SetValueAt(idx, blockedUrl);
    }
    obj->SetPropertyObject("adsBlocked", adsBlockedArr);

    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::ParseRawfileWebSrc(const JSRef<JSVal>& srcValue, std::string& webSrc)
{
    if (!srcValue->IsObject() || webSrc.substr(0, RAWFILE_PREFIX.size()) != RAWFILE_PREFIX) {
        return;
    }
    std::string bundleName;
    std::string moduleName;
    GetJsMediaBundleInfo(srcValue, bundleName, moduleName);
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    if ((!bundleName.empty() && !moduleName.empty()) &&
        (bundleName != container->GetBundleName() || moduleName != container->GetModuleName())) {
        webSrc = RAWFILE_PREFIX + BUNDLE_NAME_PREFIX + bundleName + "/" + MODULE_NAME_PREFIX + moduleName + "/" +
            webSrc.substr(RAWFILE_PREFIX.size());
    }
}

void JSWeb::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> srcValue = paramObject->GetProperty("src");
    std::string webSrc;
    std::optional<std::string> dstSrc;
    if (srcValue->IsString()) {
        dstSrc = srcValue->ToString();
    } else if (ParseJsMedia(srcValue, webSrc)) {
        ParseRawfileWebSrc(srcValue, webSrc);
        int np = static_cast<int>(webSrc.find_first_of("/"));
        dstSrc = np < 0 ? webSrc : webSrc.erase(np, 1);
    }
    if (!dstSrc) {
        return;
    }
    auto controllerObj = paramObject->GetProperty("controller");
    if (!controllerObj->IsObject()) {
        return;
    }
    JsiRef<JsiValue> type = JsiRef<JsiValue>::Make();
    bool isHasType = paramObject->HasProperty("type");
    if (isHasType) {
        type = paramObject->GetProperty("type");
    } else {
        type = paramObject->GetProperty("renderMode");
    }
    RenderMode renderMode = RenderMode::ASYNC_RENDER;
    if (type->IsNumber() && (type->ToNumber<int32_t>() >= 0) && (type->ToNumber<int32_t>() <= 1)) {
        renderMode = static_cast<RenderMode>(type->ToNumber<int32_t>());
    }
    std::string debugRenderMode = SystemProperties::GetWebDebugRenderMode();
    if (debugRenderMode != "none") {
        if (debugRenderMode == "async") {
            renderMode = RenderMode::ASYNC_RENDER;
        } else if (debugRenderMode == "sync") {
            renderMode = RenderMode::SYNC_RENDER;
        } else {
            TAG_LOGW(AceLogTag::ACE_WEB, "JSWeb::Create unsupport debug render mode: %{public}s",
                debugRenderMode.c_str());
        }
        TAG_LOGI(AceLogTag::ACE_WEB, "JSWeb::Create use debug render mode: %{public}s", debugRenderMode.c_str());
    }

    bool incognitoMode = false;
    ParseJsBool(paramObject->GetProperty("incognitoMode"), incognitoMode);

    std::string sharedRenderProcessToken = "";
    ParseJsString(paramObject->GetProperty("sharedRenderProcessToken"), sharedRenderProcessToken);

    auto controller = JSRef<JSObject>::Cast(controllerObj);
    auto setWebIdFunction = controller->GetProperty("setWebId");
    if (setWebIdFunction->IsFunction()) {
        auto setIdCallback = [webviewController = controller, func = JSRef<JSFunc>::Cast(setWebIdFunction)](
                                 int32_t webId) {
            JSRef<JSVal> argv[] = { JSRef<JSVal>::Make(ToJSValue(webId)) };
            func->Call(webviewController, 1, argv);
        };

        auto setWebDetachFunction = controller->GetProperty("setWebDetach");
        std::function<void(int32_t)> setWebDetachCallback = nullptr;
        if (setWebDetachFunction->IsFunction()) {
            setWebDetachCallback = [webviewController = controller, func = JSRef<JSFunc>::Cast(setWebDetachFunction)](
                                     int32_t webId) {
                JSRef<JSVal> argv[] = { JSRef<JSVal>::Make(ToJSValue(webId)) };
                func->Call(webviewController, 1, argv);
            };
        }

        auto setHapPathFunction = controller->GetProperty("innerSetHapPath");
        std::function<void(const std::string&)> setHapPathCallback = nullptr;
        if (setHapPathFunction->IsFunction()) {
            setHapPathCallback = [webviewController = controller, func = JSRef<JSFunc>::Cast(setHapPathFunction)](
                                     const std::string& hapPath) {
                JSRef<JSVal> argv[] = { JSRef<JSVal>::Make(ToJSValue(hapPath)) };
                func->Call(webviewController, 1, argv);
            };
        }

        auto setRequestPermissionsFromUserFunction = controller->GetProperty("requestPermissionsFromUserWeb");
        std::function<void(const std::shared_ptr<BaseEventInfo>&)> requestPermissionsFromUserCallback = nullptr;
        if (setRequestPermissionsFromUserFunction->IsFunction()) {
            requestPermissionsFromUserCallback = [webviewController = controller,
                func = JSRef<JSFunc>::Cast(setRequestPermissionsFromUserFunction)]
                (const std::shared_ptr<BaseEventInfo>& info) {
                    auto* eventInfo = TypeInfoHelper::DynamicCast<WebPermissionRequestEvent>(info.get());
                    JSRef<JSObject> obj = JSRef<JSObject>::New();
                    JSRef<JSObject> permissionObj = JSClass<JSWebPermissionRequest>::NewInstance();
                    auto permissionEvent = Referenced::Claim(permissionObj->Unwrap<JSWebPermissionRequest>());
                    permissionEvent->SetEvent(*eventInfo);
                    obj->SetPropertyObject("request", permissionObj);
                    JSRef<JSVal> argv[] = { JSRef<JSVal>::Cast(obj) };
                    auto result = func->Call(webviewController, 1, argv);
            };
        }

        auto setOpenAppLinkFunction = controller->GetProperty("openAppLink");
        std::function<void(const std::shared_ptr<BaseEventInfo>&)> openAppLinkCallback = nullptr;
        if (setOpenAppLinkFunction->IsFunction()) {
            openAppLinkCallback = [webviewController = controller,
                func = JSRef<JSFunc>::Cast(setOpenAppLinkFunction)]
                (const std::shared_ptr<BaseEventInfo>& info) {
                    auto* eventInfo = TypeInfoHelper::DynamicCast<WebAppLinkEvent>(info.get());
                    JSRef<JSObject> obj = JSRef<JSObject>::New();
                    JSRef<JSObject> callbackObj = JSClass<JSWebAppLinkCallback>::NewInstance();
                    auto callbackEvent = Referenced::Claim(callbackObj->Unwrap<JSWebAppLinkCallback>());
                    callbackEvent->SetEvent(*eventInfo);
                    obj->SetPropertyObject("result", callbackObj);
                    JSRef<JSVal> urlVal = JSRef<JSVal>::Make(ToJSValue(eventInfo->GetUrl()));
                    obj->SetPropertyObject("url", urlVal);
                    JSRef<JSVal> argv[] = { JSRef<JSVal>::Cast(obj) };
                    auto result = func->Call(webviewController, 1, argv);
            };
        }
        auto fileSelectorShowFromUserFunction = controller->GetProperty("fileSelectorShowFromUserWeb");
        std::function<void(const std::shared_ptr<BaseEventInfo>&)> fileSelectorShowFromUserCallback = nullptr;
        if (fileSelectorShowFromUserFunction->IsFunction()) {
            fileSelectorShowFromUserCallback = [webviewController = controller,
                func = JSRef<JSFunc>::Cast(fileSelectorShowFromUserFunction)]
                (const std::shared_ptr<BaseEventInfo>& info) {
                    auto* eventInfo = TypeInfoHelper::DynamicCast<FileSelectorEvent>(info.get());
                    JSRef<JSObject> obj = JSRef<JSObject>::New();
                    JSRef<JSObject> paramObj = JSClass<JSFileSelectorParam>::NewInstance();
                    auto fileSelectorParam = Referenced::Claim(paramObj->Unwrap<JSFileSelectorParam>());
                    fileSelectorParam->SetParam(*eventInfo);
                    obj->SetPropertyObject("fileparam", paramObj);

                    JSRef<JSObject> resultObj = JSClass<JSFileSelectorResult>::NewInstance();
                    auto fileSelectorResult = Referenced::Claim(resultObj->Unwrap<JSFileSelectorResult>());

                    fileSelectorResult->SetResult(*eventInfo);

                    obj->SetPropertyObject("fileresult", resultObj);
                    JSRef<JSVal> argv[] = { JSRef<JSVal>::Cast(obj) };
                    auto result = func->Call(webviewController, 1, argv);
                };
        }

        int32_t parentNWebId = -1;
        bool isPopup = JSWebWindowNewHandler::ExistController(controller, parentNWebId);
        WebModel::GetInstance()->Create(isPopup ? "" : dstSrc.value(), std::move(setIdCallback),
            std::move(setHapPathCallback), parentNWebId, isPopup, renderMode, incognitoMode, sharedRenderProcessToken);

        WebModel::GetInstance()->SetPermissionClipboard(std::move(requestPermissionsFromUserCallback));
        WebModel::GetInstance()->SetOpenAppLinkFunction(std::move(openAppLinkCallback));
        WebModel::GetInstance()->SetDefaultFileSelectorShow(std::move(fileSelectorShowFromUserCallback));
        WebModel::GetInstance()->SetWebDetachFunction(std::move(setWebDetachCallback));
        auto getCmdLineFunction = controller->GetProperty("getCustomeSchemeCmdLine");
        if (!getCmdLineFunction->IsFunction()) {
            return;
        }
        std::string cmdLine = JSRef<JSFunc>::Cast(getCmdLineFunction)->Call(controller, 0, {})->ToString();
        if (!cmdLine.empty()) {
            WebModel::GetInstance()->SetCustomScheme(cmdLine);
        }

        auto updateInstanceIdFunction = controller->GetProperty("updateInstanceId");
        if (updateInstanceIdFunction->IsFunction()) {
            std::function<void(int32_t)> updateInstanceIdCallback = [webviewController = controller,
                func = JSRef<JSFunc>::Cast(updateInstanceIdFunction)](int32_t newId) {
                auto newIdVal = JSRef<JSVal>::Make(ToJSValue(newId));
                auto result = func->Call(webviewController, 1, &newIdVal);
            };
            NG::WebModelNG::GetInstance()->SetUpdateInstanceIdCallback(std::move(updateInstanceIdCallback));
        }

        auto getWebDebugingFunction = controller->GetProperty("getWebDebuggingAccess");
        if (!getWebDebugingFunction->IsFunction()) {
            return;
        }
        bool webDebuggingAccess = JSRef<JSFunc>::Cast(getWebDebugingFunction)->Call(controller, 0, {})->ToBoolean();
        int32_t webDebuggingPort = 0;
        auto getWebDebuggingPortFunction = controller->GetProperty("getWebDebuggingPort");
        if (getWebDebuggingPortFunction->IsFunction()) {
            webDebuggingPort = JSRef<JSFunc>::Cast(getWebDebuggingPortFunction)
                ->Call(controller, 0, {})
                ->ToNumber<int32_t>();
        }
        if (webDebuggingPort > 0) {
            WebModel::GetInstance()->SetWebDebuggingAccessEnabledAndPort(
                webDebuggingAccess, webDebuggingPort);
        } else {
            WebModel::GetInstance()->SetWebDebuggingAccessEnabled(webDebuggingAccess);
        }
        JSWeb::webDebuggingAccess_ = webDebuggingAccess;
        JSWeb::webDebuggingPort_ = webDebuggingPort;
        return;

    } else {
        auto* jsWebController = controller->Unwrap<JSWebController>();
        CHECK_NULL_VOID(jsWebController);
        WebModel::GetInstance()->Create(
            dstSrc.value(), jsWebController->GetController(), renderMode, incognitoMode, sharedRenderProcessToken);
    }

    WebModel::GetInstance()->SetFocusable(true);
    WebModel::GetInstance()->SetFocusNode(true);
}

void JSWeb::WebRotate(const JSCallbackInfo& args) {}

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
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc =
        AceType::MakeRefPtr<JsEventFunction<WebDialogEvent, 1>>(JSRef<JSFunc>::Cast(args[0]), WebDialogEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) -> bool {
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, false);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<WebDialogEvent>(info);
        JSRef<JSVal> message = func->ExecuteWithValue(*eventInfo);
        if (message->IsBoolean()) {
            return message->ToBoolean();
        } else {
            return false;
        }
    };
    WebModel::GetInstance()->SetOnCommonDialog(jsCallback, dialogEventType);
}

void JSWeb::OnConsoleLog(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebConsoleLogEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebConsoleLogEventToJSValue);

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) -> bool {
        bool result = false;
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, false);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, result);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebConsoleLogEvent>(info);
        JSRef<JSVal> message = func->ExecuteWithValue(*eventInfo);
        if (message->IsBoolean()) {
            result = message->ToBoolean();
        }
        return result;
    };

    WebModel::GetInstance()->SetOnConsoleLog(jsCallback);
}

void JSWeb::OnPageStart(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebPageStartEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebPageStartEventToJSValue);

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebPageStartEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetOnPageStart(jsCallback);
}

void JSWeb::OnPageFinish(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebPageFinishEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebPageFinishEventToJSValue);

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebPageFinishEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetOnPageFinish(jsCallback);
}

void JSWeb::OnProgressChange(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebProgressChangeEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebProgressChangeEventToJSValue);

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebProgressChangeEvent>(info);
        func->ExecuteWithValue(*eventInfo);
    };
    WebModel::GetInstance()->SetOnProgressChange(jsCallback);
}

void JSWeb::OnTitleReceive(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebTitleReceiveEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebTitleReceiveEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebTitleReceiveEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetOnTitleReceive(jsCallback);
}

void JSWeb::OnFullScreenExit(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<FullScreenExitEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), FullScreenExitEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<FullScreenExitEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetOnFullScreenExit(jsCallback);
}

void JSWeb::OnFullScreenEnter(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<FullScreenEnterEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), FullScreenEnterEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        CHECK_NULL_VOID(func);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<FullScreenEnterEvent>(info);
        CHECK_NULL_VOID(eventInfo);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetOnFullScreenEnter(jsCallback);
}

void JSWeb::OnGeolocationHide(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebGeolocationHideEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebGeolocationHideEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebGeolocationHideEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetOnGeolocationHide(jsCallback);
}

void JSWeb::OnGeolocationShow(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebGeolocationShowEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebGeolocationShowEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebGeolocationShowEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetOnGeolocationShow(jsCallback);
}

void JSWeb::OnRequestFocus(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebRequestFocusEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebRequestFocusEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebRequestFocusEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetOnRequestFocus(jsCallback);
}

void JSWeb::OnDownloadStart(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<DownloadStartEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), DownloadStartEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<DownloadStartEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetOnDownloadStart(jsCallback);
}

void JSWeb::OnHttpAuthRequest(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebHttpAuthEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), WebHttpAuthEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) -> bool {
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, false);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<WebHttpAuthEvent>(info);
        JSRef<JSVal> message = func->ExecuteWithValue(*eventInfo);
        if (message->IsBoolean()) {
            return message->ToBoolean();
        }
        return false;
    };
    WebModel::GetInstance()->SetOnHttpAuthRequest(jsCallback);
}

void JSWeb::OnSslErrRequest(const JSCallbackInfo& args)
{
    return;
}

void JSWeb::OnSslErrorRequest(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebSslErrorEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), WebSslErrorEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) -> bool {
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, false);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<WebSslErrorEvent>(info);
        func->Execute(*eventInfo);
        return true;
    };
    WebModel::GetInstance()->SetOnSslErrorRequest(jsCallback);
}

void JSWeb::OnAllSslErrorRequest(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebAllSslErrorEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), WebAllSslErrorEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) -> bool {
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, false);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<WebAllSslErrorEvent>(info);
        func->Execute(*eventInfo);
        return true;
    };
    WebModel::GetInstance()->SetOnAllSslErrorRequest(jsCallback);
}

void JSWeb::OnSslSelectCertRequest(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebSslSelectCertEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), WebSslSelectCertEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) -> bool {
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, false);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<WebSslSelectCertEvent>(info);
        JSRef<JSVal> message = func->ExecuteWithValue(*eventInfo);
        if (message->IsBoolean()) {
            return message->ToBoolean();
        }
        return false;
    };
    WebModel::GetInstance()->SetOnSslSelectCertRequest(jsCallback);
}

void JSWeb::MediaPlayGestureAccess(bool isNeedGestureAccess)
{
    WebModel::GetInstance()->SetMediaPlayGestureAccess(isNeedGestureAccess);
}

void JSWeb::OnKeyEvent(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    RefPtr<JsKeyFunction> jsOnKeyEventFunc = AceType::MakeRefPtr<JsKeyFunction>(JSRef<JSFunc>::Cast(args[0]));
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsOnKeyEventFunc), node = frameNode](
                          KeyEventInfo& keyEventInfo) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        func->Execute(keyEventInfo);
    };
    WebModel::GetInstance()->SetOnKeyEvent(jsCallback);
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

JSRef<JSVal> JSWeb::CreateRequestErrorHandler(const ReceivedErrorEvent& eventInfo)
{
    JSRef<JSObject> requestObj = JSClass<JSWebResourceRequest>::NewInstance();
    auto requestEvent = Referenced::Claim(requestObj->Unwrap<JSWebResourceRequest>());
    if (!requestEvent) {
        return requestObj;
    }
    requestEvent->SetErrorEvent(eventInfo);
    return requestObj;
}

JSRef<JSVal> JSWeb::CreateResponseErrorHandler(const ReceivedErrorEvent& eventInfo)
{
    JSRef<JSObject> errorObj = JSClass<JSWebResourceError>::NewInstance();
    auto errorEvent = Referenced::Claim(errorObj->Unwrap<JSWebResourceError>());
    if (!errorEvent) {
        return errorObj;
    }
    errorEvent->SetEvent(eventInfo);
    return errorObj;
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

JSRef<JSVal> JSWeb::CreateHttpErrorReceiveRequestHandler(const ReceivedHttpErrorEvent& eventInfo)
{
    JSRef<JSObject> requestObj = JSClass<JSWebResourceRequest>::NewInstance();
    auto requestEvent = Referenced::Claim(requestObj->Unwrap<JSWebResourceRequest>());
    if (!requestEvent) {
        return requestObj;
    }
    requestEvent->SetHttpErrorEvent(eventInfo);
    return requestObj;
}

JSRef<JSVal> JSWeb::CreateHttpErrorReceiveResponseHandler(const ReceivedHttpErrorEvent& eventInfo)
{
    JSRef<JSObject> responseObj = JSClass<JSWebResourceResponse>::NewInstance();
    auto responseEvent = Referenced::Claim(responseObj->Unwrap<JSWebResourceResponse>());
    if (!responseEvent) {
        return responseObj;
    }
    responseEvent->SetEvent(eventInfo);
    return responseObj;
}

void JSWeb::OnErrorReceive(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ReceivedErrorEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ReceivedErrorEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<ReceivedErrorEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetOnErrorReceive(jsCallback);
}

void JSWeb::OnHttpErrorReceive(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ReceivedHttpErrorEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ReceivedHttpErrorEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<ReceivedHttpErrorEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetOnHttpErrorReceive(jsCallback);
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

JSRef<JSVal> JSWeb::CreateInterceptRequestHandler(const OnInterceptRequestEvent& eventInfo)
{
    JSRef<JSObject> requestObj = JSClass<JSWebResourceRequest>::NewInstance();
    auto requestEvent = Referenced::Claim(requestObj->Unwrap<JSWebResourceRequest>());
    if (!requestEvent) {
        return requestObj;
    }
    requestEvent->SetOnInterceptRequestEvent(eventInfo);
    return requestObj;
}

void JSWeb::OnInterceptRequest(const JSCallbackInfo& args)
{
    if ((args.Length() <= 0) || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<OnInterceptRequestEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), OnInterceptRequestEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) -> RefPtr<WebResponse> {
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, nullptr);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, nullptr);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<OnInterceptRequestEvent>(info);
        JSRef<JSVal> obj = func->ExecuteWithValue(*eventInfo);
        if (!obj->IsObject()) {
            return nullptr;
        }
        auto jsResponse = JSRef<JSObject>::Cast(obj)->Unwrap<JSWebResourceResponse>();
        if (jsResponse) {
            return jsResponse->GetResponseObj();
        }
        return nullptr;
    };
    WebModel::GetInstance()->SetOnInterceptRequest(jsCallback);
}

JSRef<JSVal> OnOverrideErrorPageEventToJSValue(const OnOverrideErrorPageEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSObject> requestObj = JSClass<JSWebResourceRequest>::NewInstance();
    auto requestEvent = Referenced::Claim(requestObj->Unwrap<JSWebResourceRequest>());
    requestEvent->SetOnOverrideErrorPageEvent(eventInfo);

    JSRef<JSObject> errorObj = JSClass<JSWebResourceError>::NewInstance();
    auto errorEvent = Referenced::Claim(errorObj->Unwrap<JSWebResourceError>());
    errorEvent->SetOverrideErrorPageEvent(eventInfo);

    obj->SetPropertyObject("request", requestObj);
    obj->SetPropertyObject("error", errorObj);

    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnOverrideErrorPage(const JSCallbackInfo& args)
{
    if ((args.Length() <= 0) || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<OnOverrideErrorPageEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), OnOverrideErrorPageEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) -> std::string {
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, nullptr);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, nullptr);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<OnOverrideErrorPageEvent>(info);
        if (!eventInfo) {
            return "";
        }
        JSRef<JSVal> html = func->ExecuteWithValue(*eventInfo);
        if (html->IsString()) {
            return html->ToString();
        }
        return "";
    };
    WebModel::GetInstance()->SetOnOverrideErrorPage(jsCallback);
}

void JSWeb::OnUrlLoadIntercept(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<UrlLoadInterceptEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), UrlLoadInterceptEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) -> bool {
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, false);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<UrlLoadInterceptEvent>(info);
        JSRef<JSVal> message = func->ExecuteWithValue(*eventInfo);
        if (message->IsBoolean()) {
            return message->ToBoolean();
        }
        return false;
    };
    WebModel::GetInstance()->SetOnUrlLoadIntercept(jsCallback);
}

void JSWeb::OnLoadIntercept(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadInterceptEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadInterceptEventToJSValue);

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) -> bool {
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, false);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<LoadInterceptEvent>(info);
        JSRef<JSVal> message = func->ExecuteWithValue(*eventInfo);
        if (message->IsBoolean()) {
            return message->ToBoolean();
        }
        return false;
    };
    WebModel::GetInstance()->SetOnLoadIntercept(std::move(uiCallback));
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

JSRef<JSVal> JSWeb::CreateFileSelectorResultHandler(const FileSelectorEvent& eventInfo)
{
    JSRef<JSObject> resultObj = JSClass<JSFileSelectorResult>::NewInstance();
    auto fileSelectorResult = Referenced::Claim(resultObj->Unwrap<JSFileSelectorResult>());
    fileSelectorResult->SetResult(eventInfo);
    return resultObj;
}

JSRef<JSVal> JSWeb::CreateFileSelectorParamHandler(const FileSelectorEvent& eventInfo)
{
    JSRef<JSObject> paramObj = JSClass<JSFileSelectorParam>::NewInstance();
    auto fileSelectorParam = Referenced::Claim(paramObj->Unwrap<JSFileSelectorParam>());
    fileSelectorParam->SetParam(eventInfo);
    return paramObj;
}

void JSWeb::OnFileSelectorShow(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<FileSelectorEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), FileSelectorEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) -> bool {
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, false);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<FileSelectorEvent>(info);
        JSRef<JSVal> message = func->ExecuteWithValue(*eventInfo);
        if (message->IsBoolean()) {
            return message->ToBoolean();
        }
        return false;
    };
    WebModel::GetInstance()->SetOnFileSelectorShow(jsCallback);
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

JSRef<JSVal> JSWeb::CreateContextMenuParamHandler(const ContextMenuEvent& eventInfo)
{
    JSRef<JSObject> paramObj = JSClass<JSContextMenuParam>::NewInstance();
    auto contextMenuParam = Referenced::Claim(paramObj->Unwrap<JSContextMenuParam>());
    contextMenuParam->SetParam(eventInfo);
    return paramObj;
}

JSRef<JSVal> JSWeb::CreateContextMenuResultHandler(const ContextMenuEvent& eventInfo)
{
    JSRef<JSObject> resultObj = JSClass<JSContextMenuResult>::NewInstance();
    auto contextMenuResult = Referenced::Claim(resultObj->Unwrap<JSContextMenuResult>());
    contextMenuResult->SetResult(eventInfo);
    return resultObj;
}

void JSWeb::OnContextMenuShow(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ContextMenuEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ContextMenuEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) -> bool {
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, false);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<ContextMenuEvent>(info);
        JSRef<JSVal> message = func->ExecuteWithValue(*eventInfo);
        if (message->IsBoolean()) {
            return message->ToBoolean();
        }
        return false;
    };
    WebModel::GetInstance()->SetOnContextMenuShow(jsCallback);
}

void ParseBindSelectionMenuParam(
    const JSCallbackInfo& info, const JSRef<JSObject>& menuOptions, NG::MenuParam& menuParam)
{
    auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDisappearValue = menuOptions->GetProperty("onDisappear");
    if (onDisappearValue->IsFunction()) {
        RefPtr<JsFunction> jsOnDisAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onDisappearValue));
        auto onDisappear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDisAppearFunc),
                            node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onDisappear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        menuParam.onDisappear = std::move(onDisappear);
    }

    auto onAppearValue = menuOptions->GetProperty("onAppear");
    if (onAppearValue->IsFunction()) {
        RefPtr<JsFunction> jsOnAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onAppearValue));
        auto onAppear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnAppearFunc),
                         node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onAppear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        menuParam.onAppear = std::move(onAppear);
    }
}

void ParseBindSelectionMenuOptionParam(const JSCallbackInfo& info, const JSRef<JSVal>& args,
    NG::MenuParam& menuParam, std::function<void()>& previewBuildFunc)
{
    auto menuOptions = JSRef<JSObject>::Cast(args);
    ParseBindSelectionMenuParam(info, menuOptions, menuParam);

    auto preview = menuOptions->GetProperty("preview");
    if (!preview->IsFunction()) {
        return;
    }
    auto menuType = menuOptions->GetProperty("menuType");
    bool isPreviewMenu = menuType->IsNumber() && menuType->ToNumber<int32_t>() == 1;
    menuParam.hapticFeedbackMode = HapticFeedbackMode::DISABLED;
    if (isPreviewMenu) {
        menuParam.previewMode = MenuPreviewMode::CUSTOM;
        auto previewMenuOptions = menuOptions->GetProperty("previewMenuOptions");
        if (previewMenuOptions->IsObject()) {
            auto previewMenuOptionsObj = JSRef<JSObject>::Cast(previewMenuOptions);
            auto hapticFeedbackMode = previewMenuOptionsObj->GetProperty("hapticFeedbackMode");
            if (hapticFeedbackMode->IsNumber()) {
                menuParam.hapticFeedbackMode = HapticFeedbackMode(hapticFeedbackMode->ToNumber<int32_t>());
            }
        }
        RefPtr<JsFunction> previewBuilderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(preview));
        CHECK_NULL_VOID(previewBuilderFunc);
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        previewBuildFunc = [execCtx = info.GetExecutionContext(), func = std::move(previewBuilderFunc),
                            node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("BindSelectionMenuPreviwer");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
    }
}

NG::MenuParam GetSelectionMenuParam(const JSCallbackInfo &info, ResponseType responseType,
    std::function<void()> &previewBuilder, WebElementType elementType)
{
    NG::MenuParam menuParam;
    if (info.Length() > SELECTION_MENU_OPTION_PARAM_INDEX && info[SELECTION_MENU_OPTION_PARAM_INDEX]->IsObject()) {
        ParseBindSelectionMenuOptionParam(info, info[SELECTION_MENU_OPTION_PARAM_INDEX], menuParam, previewBuilder);
    }

    if (responseType != ResponseType::LONG_PRESS) {
        menuParam.previewMode = MenuPreviewMode::NONE;
        menuParam.menuBindType = MenuBindingType::RIGHT_CLICK;
    }
    menuParam.contextMenuRegisterType = NG::ContextMenuRegisterType::CUSTOM_TYPE;
    menuParam.type = NG::MenuType::CONTEXT_MENU;
    NG::PaddingProperty paddings;
    paddings.start = NG::CalcLength(PREVIEW_MENU_MARGIN_LEFT);
    paddings.end = NG::CalcLength(PREVIEW_MENU_MARGIN_RIGHT);
    menuParam.layoutRegionMargin = paddings;
    menuParam.disappearScaleToTarget = true;
    menuParam.isPreviewContainScale = (elementType == WebElementType::IMAGE);
    menuParam.isShow = true;
    return menuParam;
}

bool CheckSelectionMenuParam(const JSCallbackInfo &info)
{
    if (info.Length() < SELECTION_MENU_OPTION_PARAM_INDEX || !info[0]->IsNumber() || !info[1]->IsObject() ||
        !info[SELECTION_MENU_CONTENT_PARAM_INDEX]->IsNumber()) {
        return false;
    }
    std::vector<WebElementType> supportType = {WebElementType::IMAGE, WebElementType::LINK};
    int32_t elementType = info[0]->ToNumber<int32_t>();
    auto supportType_iter = std::find_if(supportType.begin(), supportType.end(), [elementType](auto &type) {
        return static_cast<int32_t>(type) == elementType;
    });
    if (supportType_iter == supportType.end()) {
        TAG_LOGW(AceLogTag::ACE_WEB, "WebElementType param err");
        return false;
    }
    if (info[SELECTION_MENU_CONTENT_PARAM_INDEX]->ToNumber<int32_t>() !=
        static_cast<int32_t>(ResponseType::LONG_PRESS)) {
        TAG_LOGW(AceLogTag::ACE_WEB, "WebResponseType param err");
        return false;
    }
    return true;
}
void JSWeb::BindSelectionMenu(const JSCallbackInfo& info)
{
    if (!CheckSelectionMenuParam(info)) {
        return;
    }
    WebElementType elementType = static_cast<WebElementType>(info[0]->ToNumber<int32_t>());
    ResponseType responseType =
        static_cast<ResponseType>(info[SELECTION_MENU_CONTENT_PARAM_INDEX]->ToNumber<int32_t>());

    // Builder
    JSRef<JSObject> menuObj = JSRef<JSObject>::Cast(info[1]);
    auto builder = menuObj->GetProperty("builder");
    if (!builder->IsFunction()) {
        TAG_LOGW(AceLogTag::ACE_WEB, "BindSelectionMenu menu builder param err");
        return;
    }
    auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
    CHECK_NULL_VOID(builderFunc);
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    std::function<void()> menuBuilder = [execCtx = info.GetExecutionContext(), func = std::move(builderFunc),
                                         node = frameNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("BindSelectionMenu");
        PipelineContext::SetCallBackNode(node);
        func->Execute();
    };

    std::function<void()> previewBuilder = nullptr;
    NG::MenuParam menuParam = GetSelectionMenuParam(info, responseType, previewBuilder, elementType);
    WebModel::GetInstance()->SetNewDragStyle(true);
    auto previewSelectionMenuParam = std::make_shared<WebPreviewSelectionMenuParam>(
        elementType, responseType, menuBuilder, previewBuilder, menuParam);
    WebModel::GetInstance()->SetPreviewSelectionMenu(previewSelectionMenuParam);
}

void JSWeb::OnContextMenuHide(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ContextMenuHideEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ContextMenuHideEventToJSValue);

    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<ContextMenuHideEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetOnContextMenuHide(jsCallback);
}

void JSWeb::JsEnabled(bool isJsEnabled)
{
    WebModel::GetInstance()->SetJsEnabled(isJsEnabled);
}

void JSWeb::ContentAccessEnabled(bool isContentAccessEnabled)
{
#if !defined(NG_BUILD) && !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
    auto stack = ViewStackProcessor::GetInstance();
    auto webComponent = AceType::DynamicCast<WebComponent>(stack->GetMainComponent());
    if (!webComponent) {
        return;
    }
    webComponent->SetContentAccessEnabled(isContentAccessEnabled);
#else
    TAG_LOGW(AceLogTag::ACE_WEB, "do not support components in new pipeline mode");
#endif
}

void JSWeb::FileAccessEnabled(bool isFileAccessEnabled)
{
    WebModel::GetInstance()->SetFileAccessEnabled(isFileAccessEnabled);
}

void JSWeb::OnLineImageAccessEnabled(bool isOnLineImageAccessEnabled)
{
    WebModel::GetInstance()->SetOnLineImageAccessEnabled(isOnLineImageAccessEnabled);
}

void JSWeb::DomStorageAccessEnabled(bool isDomStorageAccessEnabled)
{
    WebModel::GetInstance()->SetDomStorageAccessEnabled(isDomStorageAccessEnabled);
}

void JSWeb::ImageAccessEnabled(bool isImageAccessEnabled)
{
    WebModel::GetInstance()->SetImageAccessEnabled(isImageAccessEnabled);
}

void JSWeb::MixedMode(int32_t mixedMode)
{
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
    WebModel::GetInstance()->SetMixedMode(mixedContentMode);
}

void JSWeb::ZoomAccessEnabled(bool isZoomAccessEnabled)
{
    WebModel::GetInstance()->SetZoomAccessEnabled(isZoomAccessEnabled);
}

void JSWeb::EnableNativeEmbedMode(bool isEmbedModeEnabled)
{
    WebModel::GetInstance()->SetNativeEmbedModeEnabled(isEmbedModeEnabled);
}

void JSWeb::NativeEmbedOptions(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(args[0]);
    std::optional<bool> enable;
    JSRef<JSVal> enableJsValue = paramObject->GetProperty("supportDefaultIntrinsicSize");
    if (enableJsValue->IsBoolean()) {
        enable = enableJsValue->ToBoolean();
        WebModel::GetInstance()->SetIntrinsicSizeEnabled(*enable);
    }

    auto cssDisplayChangeObj = paramObject->GetProperty("supportCssDisplayChange");
    if (cssDisplayChangeObj->IsBoolean()) {
        bool cssDisplayChange = cssDisplayChangeObj->ToBoolean();
        WebModel::GetInstance()->SetCssDisplayChangeEnabled(cssDisplayChange);
    }
}

void JSWeb::RegisterNativeEmbedRule(const std::string& tag, const std::string& type)
{
    WebModel::GetInstance()->RegisterNativeEmbedRule(tag, type);
}

void JSWeb::GeolocationAccessEnabled(bool isGeolocationAccessEnabled)
{
    WebModel::GetInstance()->SetGeolocationAccessEnabled(isGeolocationAccessEnabled);
}

void JSWeb::JavaScriptProxy(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(args[0]);
    auto controllerObj = paramObject->GetProperty("controller");
    auto object = JSRef<JSVal>::Cast(paramObject->GetProperty("object"));
    auto name = JSRef<JSVal>::Cast(paramObject->GetProperty("name"));
    auto methodList = JSRef<JSVal>::Cast(paramObject->GetProperty("methodList"));
    auto asyncMethodList = JSRef<JSVal>::Cast(paramObject->GetProperty("asyncMethodList"));
    auto permission = JSRef<JSVal>::Cast(paramObject->GetProperty("permission"));
    if (!controllerObj->IsObject()) {
        return;
    }
    auto controller = JSRef<JSObject>::Cast(controllerObj);
    auto jsProxyFunction = controller->GetProperty("jsProxy");
    if (jsProxyFunction->IsFunction()) {
        auto jsProxyCallback = [webviewController = controller, func = JSRef<JSFunc>::Cast(jsProxyFunction), object,
                                   name, methodList, asyncMethodList, permission]() {
            JSRef<JSVal> argv[] = { object, name, methodList, asyncMethodList, permission };
            func->Call(webviewController, 5, argv);
        };

        WebModel::GetInstance()->SetJsProxyCallback(jsProxyCallback);
    }
#if !defined(CROSS_PLATFORM)
    auto jsWebController = controller->Unwrap<JSWebController>();
    if (jsWebController) {
        jsWebController->SetJavascriptInterface(args);
    }
#endif
}

void JSWeb::UserAgent(const std::string& userAgent)
{
    WebModel::GetInstance()->SetUserAgent(userAgent);
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
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<RenderExitedEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), RenderExitedEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<RenderExitedEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetRenderExitedId(jsCallback);
}

void JSWeb::OnRefreshAccessedHistory(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<RefreshAccessedHistoryEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), RefreshAccessedHistoryEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<RefreshAccessedHistoryEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetRefreshAccessedHistoryId(jsCallback);
}

void JSWeb::CacheMode(int32_t cacheMode)
{
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
    WebModel::GetInstance()->SetCacheMode(mode);
}

void JSWeb::OverScrollMode(int overScrollMode)
{
    auto mode = OverScrollMode::NEVER;
    switch (overScrollMode) {
        case 0:
            mode = OverScrollMode::NEVER;
            break;
        case 1:
            mode = OverScrollMode::ALWAYS;
            break;
        default:
            mode = OverScrollMode::NEVER;
            break;
    }
    WebModel::GetInstance()->SetOverScrollMode(mode);
}

void JSWeb::BlurOnKeyboardHideMode(int blurOnKeyboardHideMode)
{
    auto mode = BlurOnKeyboardHideMode::SILENT;
    switch (blurOnKeyboardHideMode) {
        case 0:
            mode = BlurOnKeyboardHideMode::SILENT;
            break;
        case 1:
            mode = BlurOnKeyboardHideMode::BLUR;
            break;
        default:
            mode = BlurOnKeyboardHideMode::SILENT;
            break;
    }
    WebModel::GetInstance()->SetBlurOnKeyboardHideMode(mode);
}

void JSWeb::OverviewModeAccess(bool isOverviewModeAccessEnabled)
{
    WebModel::GetInstance()->SetOverviewModeAccessEnabled(isOverviewModeAccessEnabled);
}

void JSWeb::FileFromUrlAccess(bool isFileFromUrlAccessEnabled)
{
    WebModel::GetInstance()->SetFileFromUrlAccessEnabled(isFileFromUrlAccessEnabled);
}

void JSWeb::DatabaseAccess(bool isDatabaseAccessEnabled)
{
    WebModel::GetInstance()->SetDatabaseAccessEnabled(isDatabaseAccessEnabled);
}

void JSWeb::TextZoomRatio(int32_t textZoomRatioNum)
{
    WebModel::GetInstance()->SetTextZoomRatio(textZoomRatioNum);
}

void JSWeb::WebDebuggingAccessEnabled(bool isWebDebuggingAccessEnabled)
{
    WebModel::GetInstance()->SetWebDebuggingAccessEnabled(isWebDebuggingAccessEnabled);
}

void JSWeb::OnMouse(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    RefPtr<JsClickFunction> jsOnMouseFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(args[0]));
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsOnMouseFunc), node = frameNode](
                          MouseInfo& info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        func->Execute(info);
    };
    WebModel::GetInstance()->SetOnMouseEvent(jsCallback);
}

JSRef<JSVal> ResourceLoadEventToJSValue(const ResourceLoadEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("url", eventInfo.GetOnResourceLoadUrl());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnResourceLoad(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ResourceLoadEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ResourceLoadEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<ResourceLoadEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetResourceLoadId(jsCallback);
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
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ScaleChangeEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ScaleChangeEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<ScaleChangeEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetScaleChangeId(jsCallback);
}

JSRef<JSVal> ScrollEventToJSValue(const WebOnScrollEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("xOffset", eventInfo.GetX());
    obj->SetProperty("yOffset", eventInfo.GetY());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnScroll(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc =
        AceType::MakeRefPtr<JsEventFunction<WebOnScrollEvent, 1>>(JSRef<JSFunc>::Cast(args[0]), ScrollEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<WebOnScrollEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetScrollId(jsCallback);
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

JSRef<JSVal> JSWeb::CreatePermissionRequestHandler(const WebPermissionRequestEvent& eventInfo)
{
    JSRef<JSObject> permissionObj = JSClass<JSWebPermissionRequest>::NewInstance();
    auto permissionEvent = Referenced::Claim(permissionObj->Unwrap<JSWebPermissionRequest>());
    permissionEvent->SetEvent(eventInfo);
    return permissionObj;
}

void JSWeb::OnPermissionRequest(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebPermissionRequestEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), PermissionRequestEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<WebPermissionRequestEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetPermissionRequestEventId(jsCallback);
}

JSRef<JSVal> ScreenCaptureRequestEventToJSValue(const WebScreenCaptureRequestEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSObject> requestObj = JSClass<JSScreenCaptureRequest>::NewInstance();
    auto requestEvent = Referenced::Claim(requestObj->Unwrap<JSScreenCaptureRequest>());
    requestEvent->SetEvent(eventInfo);
    obj->SetPropertyObject("handler", requestObj);
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> JSWeb::CreateScreenCaptureHandler(const WebScreenCaptureRequestEvent& eventInfo)
{
    JSRef<JSObject> requestObj = JSClass<JSScreenCaptureRequest>::NewInstance();
    auto requestEvent = Referenced::Claim(requestObj->Unwrap<JSScreenCaptureRequest>());
    requestEvent->SetEvent(eventInfo);
    return requestObj;
}

void JSWeb::OnScreenCaptureRequest(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebScreenCaptureRequestEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ScreenCaptureRequestEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<WebScreenCaptureRequestEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetScreenCaptureRequestEventId(jsCallback);
}

void JSWeb::BackgroundColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color backgroundColor;
    if (!ParseJsColor(info[0], backgroundColor)) {
        WebModel::GetInstance()->SetDefaultBackgroundColor();
    } else {
        WebModel::GetInstance()->SetBackgroundColor(backgroundColor);
    }
}

void JSWeb::InitialScale(float scale)
{
    WebModel::GetInstance()->InitialScale(scale);
}

void JSWeb::Password(bool password) {}

void JSWeb::TableData(bool tableData) {}

void JSWeb::OnFileSelectorShowAbandoned(const JSCallbackInfo& args) {}

void JSWeb::WideViewModeAccess(const JSCallbackInfo& args) {}

void JSWeb::WebDebuggingAccess(const JSCallbackInfo& args) {}

void JSWeb::OnSearchResultReceive(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<SearchResultReceiveEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), SearchResultReceiveEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<SearchResultReceiveEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetSearchResultReceiveEventId(jsCallback);
}

void JSWeb::JsOnDragStart(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    RefPtr<JsDragFunction> jsOnDragStartFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragStartId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragStartFunc), node = frameNode](
                             const RefPtr<DragEvent>& info, const std::string& extraParams) -> NG::DragDropBaseInfo {
        NG::DragDropBaseInfo itemInfo;
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, itemInfo);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, itemInfo);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto ret = func->Execute(info, extraParams);
        if (!ret->IsObject()) {
            return itemInfo;
        }
        auto component = ParseDragNode(ret);
        if (component) {
            itemInfo.node = component;
            return itemInfo;
        }

        auto builderObj = JSRef<JSObject>::Cast(ret);
#if !defined(WINDOWS_PLATFORM) and !defined(MAC_PLATFORM)
        auto pixmap_impl = builderObj->GetProperty("pixelMap");
        itemInfo.pixelMap = CreatePixelMapFromNapiValue(pixmap_impl);
#endif

#if defined(PIXEL_MAP_SUPPORTED)
        auto pixmap_ng = builderObj->GetProperty("pixelMap");
        itemInfo.pixelMap = CreatePixelMapFromNapiValue(pixmap_ng);
#endif
        auto extraInfo = builderObj->GetProperty("extraInfo");
        ParseJsString(extraInfo, itemInfo.extraInfo);
        component = ParseDragNode(builderObj->GetProperty("builder"));
        itemInfo.node = component;
        return itemInfo;
    };

    WebModel::GetInstance()->SetOnDragStart(std::move(onDragStartId));
}

void JSWeb::JsOnDragEnter(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    RefPtr<JsDragFunction> jsOnDragEnterFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragEnterId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragEnterFunc), node = frameNode](
                             const RefPtr<DragEvent>& info, const std::string& extraParams) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragEnter");
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        func->Execute(info, extraParams);
    };

    WebModel::GetInstance()->SetOnDragEnter(onDragEnterId);
}

void JSWeb::JsOnDragMove(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    RefPtr<JsDragFunction> jsOnDragMoveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragMoveId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragMoveFunc), node = frameNode](
                            const RefPtr<DragEvent>& info, const std::string& extraParams) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragMove");
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        func->Execute(info, extraParams);
    };

    WebModel::GetInstance()->SetOnDragMove(onDragMoveId);
}

void JSWeb::JsOnDragLeave(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    RefPtr<JsDragFunction> jsOnDragLeaveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragLeaveId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragLeaveFunc), node = frameNode](
                             const RefPtr<DragEvent>& info, const std::string& extraParams) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragLeave");
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        func->Execute(info, extraParams);
    };

    WebModel::GetInstance()->SetOnDragLeave(onDragLeaveId);
}

void JSWeb::JsOnDrop(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    RefPtr<JsDragFunction> jsOnDropFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDropId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDropFunc), node = frameNode](
                        const RefPtr<DragEvent>& info, const std::string& extraParams) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDrop");
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        func->Execute(info, extraParams);
    };

    WebModel::GetInstance()->SetOnDrop(onDropId);
}

void JSWeb::PinchSmoothModeEnabled(bool isPinchSmoothModeEnabled)
{
    WebModel::GetInstance()->SetPinchSmoothModeEnabled(isPinchSmoothModeEnabled);
}

JSRef<JSVal> WindowNewEventToJSValue(const WebWindowNewEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("isAlert", eventInfo.IsAlert());
    obj->SetProperty("isUserTrigger", eventInfo.IsUserTrigger());
    obj->SetProperty("targetUrl", eventInfo.GetTargetUrl());
    JSRef<JSObject> handlerObj = JSClass<JSWebWindowNewHandler>::NewInstance();
    auto handler = Referenced::Claim(handlerObj->Unwrap<JSWebWindowNewHandler>());
    handler->SetEvent(eventInfo);
    obj->SetPropertyObject("handler", handlerObj);
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> JSWeb::CreateJSWindowNewHandler(const WebWindowNewEvent& eventInfo)
{
    JSRef<JSObject> handlerObj = Framework::JSClass<JSWebWindowNewHandler>::NewInstance();
    auto handler = Referenced::Claim(handlerObj->Unwrap<JSWebWindowNewHandler>());
    handler->SetEvent(eventInfo);
    return handlerObj;
}

bool JSWeb::HandleWindowNewEvent(const WebWindowNewEvent* eventInfo)
{
    if (eventInfo == nullptr) {
        return false;
    }
    auto handler = eventInfo->GetWebWindowNewHandler();
    if (handler && !handler->IsFrist()) {
        int32_t parentId = -1;
        auto controller = JSWebWindowNewHandler::PopController(handler->GetId(), &parentId);
        if (!controller.IsEmpty()) {
            auto getWebIdFunction = controller->GetProperty("innerGetWebId");
            if (getWebIdFunction->IsFunction()) {
                auto func = JSRef<JSFunc>::Cast(getWebIdFunction);
                auto webId = func->Call(controller, 0, {});
                handler->SetWebController(webId->ToNumber<int32_t>());
            }
            auto completeWindowNewFunction = controller->GetProperty("innerCompleteWindowNew");
            if (completeWindowNewFunction->IsFunction()) {
                auto func = JSRef<JSFunc>::Cast(completeWindowNewFunction);
                JSRef<JSVal> argv[] = { JSRef<JSVal>::Make(ToJSValue(parentId)) };
                func->Call(controller, 1, argv);
            }
        }
        return false;
    }
    return true;
}

void JSWeb::OnWindowNew(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebWindowNewEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), WindowNewEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        ACE_SCORING_EVENT("OnWindowNew CallBack");
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<WebWindowNewEvent>(info.get());
        if (!func || !HandleWindowNewEvent(eventInfo)) {
            return;
        }
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetWindowNewEvent(jsCallback);
}

JSRef<JSVal> ActivateContentEventToJSValue(const WebActivateContentEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnActivateContent(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebActivateContentEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ActivateContentEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<WebActivateContentEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetActivateContentEventId(jsCallback);
}

JSRef<JSVal> WindowExitEventToJSValue(const WebWindowExitEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnWindowExit(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebWindowExitEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), WindowExitEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<WebWindowExitEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetWindowExitEventId(jsCallback);
}

void JSWeb::MultiWindowAccessEnabled(bool isMultiWindowAccessEnable)
{
    WebModel::GetInstance()->SetMultiWindowAccessEnabled(isMultiWindowAccessEnable);
}

void JSWeb::AllowWindowOpenMethod(bool isAllowWindowOpenMethod)
{
    WebModel::GetInstance()->SetAllowWindowOpenMethod(isAllowWindowOpenMethod);
}

void JSWeb::WebCursiveFont(const std::string& cursiveFontFamily)
{
    WebModel::GetInstance()->SetWebCursiveFont(cursiveFontFamily);
}

void JSWeb::WebFantasyFont(const std::string& fantasyFontFamily)
{
    WebModel::GetInstance()->SetWebFantasyFont(fantasyFontFamily);
}

void JSWeb::WebFixedFont(const std::string& fixedFontFamily)
{
    WebModel::GetInstance()->SetWebFixedFont(fixedFontFamily);
}

void JSWeb::WebSansSerifFont(const std::string& sansSerifFontFamily)
{
    WebModel::GetInstance()->SetWebSansSerifFont(sansSerifFontFamily);
}

void JSWeb::WebSerifFont(const std::string& serifFontFamily)
{
    WebModel::GetInstance()->SetWebSerifFont(serifFontFamily);
}

void JSWeb::WebStandardFont(const std::string& standardFontFamily)
{
    WebModel::GetInstance()->SetWebStandardFont(standardFontFamily);
}

void JSWeb::DefaultFixedFontSize(int32_t defaultFixedFontSize)
{
    WebModel::GetInstance()->SetDefaultFixedFontSize(defaultFixedFontSize);
}

void JSWeb::DefaultFontSize(int32_t defaultFontSize)
{
    WebModel::GetInstance()->SetDefaultFontSize(defaultFontSize);
}

void JSWeb::DefaultTextEncodingFormat(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsString()) {
        return;
    }
    std::string textEncodingFormat = args[0]->ToString();
    EraseSpace(textEncodingFormat);
    if (textEncodingFormat.empty()) {
        WebModel::GetInstance()->SetDefaultTextEncodingFormat("UTF-8");
        return;
    }
    WebModel::GetInstance()->SetDefaultTextEncodingFormat(textEncodingFormat);
}

void JSWeb::MinFontSize(int32_t minFontSize)
{
    WebModel::GetInstance()->SetMinFontSize(minFontSize);
}

void JSWeb::MinLogicalFontSize(int32_t minLogicalFontSize)
{
    WebModel::GetInstance()->SetMinLogicalFontSize(minLogicalFontSize);
}

void JSWeb::BlockNetwork(bool isNetworkBlocked)
{
    WebModel::GetInstance()->SetBlockNetwork(isNetworkBlocked);
}

JSRef<JSVal> PageVisibleEventToJSValue(const PageVisibleEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("url", eventInfo.GetUrl());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnPageVisible(const JSCallbackInfo& args)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "JSWeb::OnPageVisible init by developer");
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<PageVisibleEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), PageVisibleEventToJSValue);

    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        TAG_LOGI(AceLogTag::ACE_WEB, "JSWeb::OnPageVisible uiCallback enter");
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        auto context = PipelineBase::GetCurrentContext();
        if (context) {
            context->UpdateCurrentActiveNode(node);
        }
        auto executor = Container::CurrentTaskExecutorSafely();
        CHECK_NULL_VOID(executor);
        executor->PostTask([execCtx, postFunc = func, info]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            TAG_LOGI(AceLogTag::ACE_WEB, "JSWeb::OnPageVisible async event execute");
            auto* eventInfo = TypeInfoHelper::DynamicCast<PageVisibleEvent>(info.get());
            postFunc->Execute(*eventInfo);
            }, TaskExecutor::TaskType::UI, "ArkUIWebPageVisible");
    };
    WebModel::GetInstance()->SetPageVisibleId(std::move(uiCallback));
}

void JSWeb::OnInterceptKeyEvent(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    RefPtr<JsKeyFunction> jsOnPreKeyEventFunc = AceType::MakeRefPtr<JsKeyFunction>(JSRef<JSFunc>::Cast(args[0]));
    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsOnPreKeyEventFunc), node = frameNode](
                          KeyEventInfo& keyEventInfo) -> bool {
        bool result = false;
        ACE_SCORING_EVENT("onPreKeyEvent");
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, false);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, result);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        JSRef<JSVal> obj = func->ExecuteWithValue(keyEventInfo);
        if (obj->IsBoolean()) {
            result = obj->ToBoolean();
        }
        return result;
    };
    WebModel::GetInstance()->SetOnInterceptKeyEventCallback(uiCallback);
}

JSRef<JSVal> DataResubmittedEventToJSValue(const DataResubmittedEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSObject> resultObj = JSClass<JSDataResubmitted>::NewInstance();
    auto jsDataResubmitted = Referenced::Claim(resultObj->Unwrap<JSDataResubmitted>());
    if (!jsDataResubmitted) {
        return JSRef<JSVal>::Cast(obj);
    }
    jsDataResubmitted->SetHandler(eventInfo.GetHandler());
    obj->SetPropertyObject("handler", resultObj);
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> JSWeb::CreateDataResubmittedHandler(const DataResubmittedEvent& eventInfo)
{
    JSRef<JSObject> resultObj = JSClass<JSDataResubmitted>::NewInstance();
    auto jsDataResubmitted = Referenced::Claim(resultObj->Unwrap<JSDataResubmitted>());
    if (!jsDataResubmitted) {
        return resultObj;
    }
    jsDataResubmitted->SetHandler(eventInfo.GetHandler());
    return resultObj;
}

void JSWeb::OnDataResubmitted(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<DataResubmittedEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), DataResubmittedEventToJSValue);

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        auto context = PipelineBase::GetCurrentContext();
        if (context) {
            context->UpdateCurrentActiveNode(node);
        }
        auto executor = Container::CurrentTaskExecutorSafely();
        CHECK_NULL_VOID(executor);
        executor->PostSyncTask([execCtx, postFunc = func, info]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto* eventInfo = TypeInfoHelper::DynamicCast<DataResubmittedEvent>(info.get());
            postFunc->Execute(*eventInfo);
            }, TaskExecutor::TaskType::UI, "ArkUIWebDataResubmitted");
    };
    WebModel::GetInstance()->SetOnDataResubmitted(uiCallback);
}

Media::PixelFormat GetPixelFormat(NG::TransImageColorType colorType)
{
    Media::PixelFormat pixelFormat;
    switch (colorType) {
        case NG::TransImageColorType::COLOR_TYPE_UNKNOWN:
            pixelFormat = Media::PixelFormat::UNKNOWN;
            break;
        case NG::TransImageColorType::COLOR_TYPE_RGBA_8888:
            pixelFormat = Media::PixelFormat::RGBA_8888;
            break;
        case NG::TransImageColorType::COLOR_TYPE_BGRA_8888:
            pixelFormat = Media::PixelFormat::BGRA_8888;
            break;
        default:
            pixelFormat = Media::PixelFormat::UNKNOWN;
            break;
    }
    return pixelFormat;
}

Media::AlphaType GetAlphaType(NG::TransImageAlphaType alphaType)
{
    Media::AlphaType imageAlphaType;
    switch (alphaType) {
        case NG::TransImageAlphaType::ALPHA_TYPE_UNKNOWN:
            imageAlphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN;
            break;
        case NG::TransImageAlphaType::ALPHA_TYPE_OPAQUE:
            imageAlphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_OPAQUE;
            break;
        case NG::TransImageAlphaType::ALPHA_TYPE_PREMULTIPLIED:
            imageAlphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL;
            break;
        case NG::TransImageAlphaType::ALPHA_TYPE_POSTMULTIPLIED:
            imageAlphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL;
            break;
        default:
            imageAlphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN;
            break;
    }
    return imageAlphaType;
}

JSRef<JSObject> FaviconReceivedEventToJSValue(const FaviconReceivedEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    auto data = eventInfo.GetHandler()->GetData();
    size_t width = eventInfo.GetHandler()->GetWidth();
    size_t height = eventInfo.GetHandler()->GetHeight();
    int colorType = eventInfo.GetHandler()->GetColorType();
    int alphaType = eventInfo.GetHandler()->GetAlphaType();

    Media::InitializationOptions opt;
    opt.size.width = static_cast<int32_t>(width);
    opt.size.height = static_cast<int32_t>(height);
    opt.pixelFormat = GetPixelFormat(NG::TransImageColorType(colorType));
    opt.alphaType = GetAlphaType(NG::TransImageAlphaType(alphaType));
    opt.editable = true;
    auto pixelMap = Media::PixelMap::Create(opt);
    if (pixelMap == nullptr) {
        return JSRef<JSVal>::Cast(obj);
    }
    uint32_t stride = width << 2;
    uint64_t bufferSize = stride * height;
    pixelMap->WritePixels(static_cast<const uint8_t*>(data), bufferSize);
    std::shared_ptr<Media::PixelMap> pixelMapToJs(pixelMap.release());
    auto engine = EngineHelper::GetCurrentEngine();
    if (!engine) {
        return JSRef<JSVal>::Cast(obj);
    }
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    napi_value napiValue = OHOS::Media::PixelMapNapi::CreatePixelMap(env, pixelMapToJs);
    auto jsPixelMap = JsConverter::ConvertNapiValueToJsVal(napiValue);
    obj->SetPropertyObject("favicon", jsPixelMap);
    return JSRef<JSObject>::Cast(obj);
}

JSRef<JSObject> JSWeb::CreateFaviconReceivedHandler(const FaviconReceivedEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    if (obj.IsEmpty()) {
        return JSRef<JSObject>::Cast(obj);
    }
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
    auto handler = eventInfo.GetHandler();
    CHECK_NULL_RETURN(handler, JSRef<JSObject>::Cast(obj));

    auto data = handler->GetData();
    CHECK_NULL_RETURN(data, JSRef<JSObject>::Cast(obj));
    size_t width = handler->GetWidth();
    size_t height = handler->GetHeight();
    int colorType = handler->GetColorType();
    int alphaType = handler->GetAlphaType();

    Media::InitializationOptions opt;
    opt.size.width = static_cast<int64_t>(width);
    opt.size.height = static_cast<int64_t>(height);
    opt.pixelFormat = GetPixelFormat(NG::TransImageColorType(colorType));
    opt.alphaType = GetAlphaType(NG::TransImageAlphaType(alphaType));
    opt.editable = true;
    auto pixelMap = Media::PixelMap::Create(opt);
    CHECK_NULL_RETURN(pixelMap, JSRef<JSObject>::Cast(obj));
    uint32_t bytesPerPixel = GetBytesPerPixel(PixelMapOhos::PixelFormatConverter(opt.pixelFormat));
    if (width > std::numeric_limits<size_t>::max() / bytesPerPixel) {
        return JSRef<JSObject>::Cast(obj);
    }
    uint64_t stride = static_cast<uint64_t>(width) * bytesPerPixel;
    if (height > std::numeric_limits<size_t>::max() / stride) {
        return JSRef<JSObject>::Cast(obj);
    }
    uint64_t bufferSize = stride * static_cast<uint64_t>(height);
    if (bufferSize > static_cast<uint64_t>(std::numeric_limits<size_t>::max())) {
        return JSRef<JSObject>::Cast(obj);
    }

    pixelMap->WritePixels(static_cast<const uint8_t*>(data), static_cast<size_t>(bufferSize));
    std::shared_ptr<Media::PixelMap> pixelMapToJs(pixelMap.release());
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, JSRef<JSObject>::Cast(obj));
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    napi_value napiValue = OHOS::Media::PixelMapNapi::CreatePixelMap(env, pixelMapToJs);
    if (napiValue == nullptr) {
        return JSRef<JSObject>::Cast(obj);
    }
    auto jsPixelMap = JsConverter::ConvertNapiValueToJsVal(napiValue);
    return jsPixelMap;
#else
    return JSRef<JSObject>::Cast(obj);
#endif
}

uint32_t JSWeb::GetBytesPerPixel(OHOS::Ace::PixelFormat format)
{
    const uint32_t BYTES_PER_PIXEL_2 = 2;
    const uint32_t BYTES_PER_PIXEL_3 = 3;
    const uint32_t BYTES_PER_PIXEL_4 = 4;
    switch (format) {
        case OHOS::Ace::PixelFormat::RGB_565:
            return BYTES_PER_PIXEL_2;
        case OHOS::Ace::PixelFormat::RGBA_8888:
            return BYTES_PER_PIXEL_4;
        case OHOS::Ace::PixelFormat::BGRA_8888:
            return BYTES_PER_PIXEL_4;
        case OHOS::Ace::PixelFormat::RGB_888:
            return BYTES_PER_PIXEL_3;
        default:
            TAG_LOGE(AceLogTag::ACE_WEB, "Unknown PixelFormat: %{public}d, using default 4 bytes per pixel",
                static_cast<int32_t>(format));
            return BYTES_PER_PIXEL_4;
    }
}

void JSWeb::OnFaviconReceived(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<FaviconReceivedEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), FaviconReceivedEventToJSValue);

    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        auto context = PipelineBase::GetCurrentContext();
        if (context) {
            context->UpdateCurrentActiveNode(node);
        }
        auto executor = Container::CurrentTaskExecutorSafely();
        CHECK_NULL_VOID(executor);
        executor->PostTask([execCtx, postFunc = func, info]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto* eventInfo = TypeInfoHelper::DynamicCast<FaviconReceivedEvent>(info.get());
            postFunc->Execute(*eventInfo);
            }, TaskExecutor::TaskType::UI, "ArkUIWebFaviconReceived");
    };
    WebModel::GetInstance()->SetFaviconReceivedId(uiCallback);
}

JSRef<JSVal> TouchIconUrlEventToJSValue(const TouchIconUrlEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("url", eventInfo.GetUrl());
    obj->SetProperty("precomposed", eventInfo.GetPreComposed());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnTouchIconUrlReceived(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<TouchIconUrlEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), TouchIconUrlEventToJSValue);

    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        auto context = PipelineBase::GetCurrentContext();
        if (context) {
            context->UpdateCurrentActiveNode(node);
        }
        auto executor = Container::CurrentTaskExecutorSafely();
        CHECK_NULL_VOID(executor);
        executor->PostTask([execCtx, postFunc = func, info]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto* eventInfo = TypeInfoHelper::DynamicCast<TouchIconUrlEvent>(info.get());
            postFunc->Execute(*eventInfo);
            }, TaskExecutor::TaskType::UI, "ArkUIWebTouchIconUrlReceived");
    };
    WebModel::GetInstance()->SetTouchIconUrlId(uiCallback);
}

void JSWeb::DarkMode(int32_t darkMode)
{
    auto mode = WebDarkMode::Off;
    switch (darkMode) {
        case 0:
            mode = WebDarkMode::Off;
            break;
        case 1:
            mode = WebDarkMode::On;
            break;
        case 2:
            mode = WebDarkMode::Auto;
            break;
        default:
            mode = WebDarkMode::Off;
            break;
    }
    WebModel::GetInstance()->SetDarkMode(mode);
}

void JSWeb::ForceDarkAccess(bool access)
{
    WebModel::GetInstance()->SetForceDarkAccess(access);
}

void JSWeb::HorizontalScrollBarAccess(bool isHorizontalScrollBarAccessEnabled)
{
    WebModel::GetInstance()->SetHorizontalScrollBarAccessEnabled(isHorizontalScrollBarAccessEnabled);
}

void JSWeb::VerticalScrollBarAccess(bool isVerticalScrollBarAccessEnabled)
{
    WebModel::GetInstance()->SetVerticalScrollBarAccessEnabled(isVerticalScrollBarAccessEnabled);
}

JSRef<JSVal> AudioStateChangedEventToJSValue(const AudioStateChangedEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("playing", eventInfo.IsPlaying());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnAudioStateChanged(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<AudioStateChangedEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), AudioStateChangedEventToJSValue);

    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<AudioStateChangedEvent>(info.get());
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetAudioStateChangedId(std::move(uiCallback));
}

void JSWeb::MediaOptions(const JSCallbackInfo& args)
{
    if (!args[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(args[0]);
    auto resumeIntervalObj = paramObject->GetProperty("resumeInterval");
    if (resumeIntervalObj->IsNumber()) {
        int32_t resumeInterval = resumeIntervalObj->ToNumber<int32_t>();
        WebModel::GetInstance()->SetAudioResumeInterval(resumeInterval);
    }

    auto audioExclusiveObj = paramObject->GetProperty("audioExclusive");
    if (audioExclusiveObj->IsBoolean()) {
        bool audioExclusive = audioExclusiveObj->ToBoolean();
        WebModel::GetInstance()->SetAudioExclusive(audioExclusive);
    }
    auto audioSessionTypeObj = paramObject->GetProperty("audioSessionType");
    auto audioSessionType = WebAudioSessionType::AUTO;
    if (audioSessionTypeObj->IsNumber()) {
        int32_t audioSessionTypeIntValue = audioSessionTypeObj->ToNumber<int32_t>();
        switch (audioSessionTypeIntValue) {
            case 0:
                audioSessionType = WebAudioSessionType::AUTO;
                break;
            case WEB_AUDIO_SESSION_TYPE_AMBIENT:
                audioSessionType = WebAudioSessionType::AMBIENT;
                break;
            default:
                audioSessionType = WebAudioSessionType::AUTO;
        }
    }
    WebModel::GetInstance()->SetAudioSessionType(audioSessionType);
}

JSRef<JSVal> FirstContentfulPaintEventToJSValue(const FirstContentfulPaintEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty<int64_t>("navigationStartTick", eventInfo.GetNavigationStartTick());
    obj->SetProperty<int64_t>("firstContentfulPaintMs", eventInfo.GetFirstContentfulPaintMs());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnFirstContentfulPaint(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<FirstContentfulPaintEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), FirstContentfulPaintEventToJSValue);

    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        auto context = PipelineBase::GetCurrentContext();
        if (context) {
            context->UpdateCurrentActiveNode(node);
        }
        auto executor = Container::CurrentTaskExecutorSafely();
        CHECK_NULL_VOID(executor);
        executor->PostTask([execCtx, postFunc = func, info]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto* eventInfo = TypeInfoHelper::DynamicCast<FirstContentfulPaintEvent>(info.get());
            postFunc->Execute(*eventInfo);
            }, TaskExecutor::TaskType::UI, "ArkUIWebFirstContentfulPaint");
    };
    WebModel::GetInstance()->SetFirstContentfulPaintId(std::move(uiCallback));
}

JSRef<JSVal> FirstMeaningfulPaintEventToJSValue(const FirstMeaningfulPaintEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("navigationStartTime", eventInfo.GetNavigationStartTime());
    obj->SetProperty("firstMeaningfulPaintTime", eventInfo.GetFirstMeaningfulPaintTime());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnFirstMeaningfulPaint(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || args[0]->IsUndefined() || args[0]->IsNull() || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<FirstMeaningfulPaintEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), FirstMeaningfulPaintEventToJSValue);
    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        auto context = PipelineBase::GetCurrentContext();
        if (context) {
            context->UpdateCurrentActiveNode(node);
        }
        auto executor = Container::CurrentTaskExecutorSafely();
        CHECK_NULL_VOID(executor);
        executor->PostTask([execCtx, postFunc = func, info]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto* eventInfo = TypeInfoHelper::DynamicCast<FirstMeaningfulPaintEvent>(info.get());
            postFunc->Execute(*eventInfo);
            }, TaskExecutor::TaskType::UI, "ArkUIWebFirstMeaningfulPaint");
    };
    WebModel::GetInstance()->SetFirstMeaningfulPaintId(std::move(uiCallback));
}

JSRef<JSVal> LargestContentfulPaintEventToJSValue(const LargestContentfulPaintEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("navigationStartTime", eventInfo.GetNavigationStartTime());
    obj->SetProperty("largestImagePaintTime", eventInfo.GetLargestImagePaintTime());
    obj->SetProperty("largestTextPaintTime", eventInfo.GetLargestTextPaintTime());
    obj->SetProperty("largestImageLoadStartTime", eventInfo.GetLargestImageLoadStartTime());
    obj->SetProperty("largestImageLoadEndTime", eventInfo.GetLargestImageLoadEndTime());
    obj->SetProperty("imageBPP", eventInfo.GetImageBPP());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnLargestContentfulPaint(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || args[0]->IsUndefined() || args[0]->IsNull() || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LargestContentfulPaintEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LargestContentfulPaintEventToJSValue);
    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        auto context = PipelineBase::GetCurrentContext();
        if (context) {
            context->UpdateCurrentActiveNode(node);
        }
        auto executor = Container::CurrentTaskExecutorSafely();
        CHECK_NULL_VOID(executor);
        executor->PostTask([execCtx, postFunc = func, info]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto* eventInfo = TypeInfoHelper::DynamicCast<LargestContentfulPaintEvent>(info.get());
            postFunc->Execute(*eventInfo);
            }, TaskExecutor::TaskType::UI, "ArkUIWebLargestContentfulPaint");
    };
    WebModel::GetInstance()->SetLargestContentfulPaintId(std::move(uiCallback));
}

JSRef<JSVal> SafeBrowsingCheckResultEventToJSValue(const SafeBrowsingCheckResultEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("threatType", eventInfo.GetThreatType());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnSafeBrowsingCheckResult(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<SafeBrowsingCheckResultEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), SafeBrowsingCheckResultEventToJSValue);

    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        auto context = PipelineBase::GetCurrentContext();
        if (context) {
            context->UpdateCurrentActiveNode(node);
        }
        auto executor = Container::CurrentTaskExecutorSafely();
        CHECK_NULL_VOID(executor);
        executor->PostTask([execCtx, postFunc = func, info]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto* eventInfo = TypeInfoHelper::DynamicCast<SafeBrowsingCheckResultEvent>(info.get());
            postFunc->Execute(*eventInfo);
            }, TaskExecutor::TaskType::UI, "ArkUIWebSafeBrowsingCheckResult");
    };
    WebModel::GetInstance()->SetSafeBrowsingCheckResultId(std::move(uiCallback));
}

JSRef<JSVal> NavigationEntryCommittedEventToJSValue(const NavigationEntryCommittedEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("isMainFrame", eventInfo.IsMainFrame());
    obj->SetProperty("isSameDocument", eventInfo.IsSameDocument());
    obj->SetProperty("didReplaceEntry", eventInfo.DidReplaceEntry());
    obj->SetProperty("navigationType", static_cast<int>(eventInfo.GetNavigationType()));
    obj->SetProperty("url", eventInfo.GetUrl());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnNavigationEntryCommitted(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<NavigationEntryCommittedEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), NavigationEntryCommittedEventToJSValue);

    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        auto context = PipelineBase::GetCurrentContext();
        if (context) {
            context->UpdateCurrentActiveNode(node);
        }
        auto executor = Container::CurrentTaskExecutorSafely();
        CHECK_NULL_VOID(executor);
        executor->PostTask([execCtx, postFunc = func, info]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto* eventInfo = TypeInfoHelper::DynamicCast<NavigationEntryCommittedEvent>(info.get());
            postFunc->Execute(*eventInfo);
            }, TaskExecutor::TaskType::UI, "ArkUIWebNavigationEntryCommitted");
    };
    WebModel::GetInstance()->SetNavigationEntryCommittedId(std::move(uiCallback));
}

JSRef<JSVal> IntelligentTrackingPreventionResultEventToJSValue(
    const IntelligentTrackingPreventionResultEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("host", eventInfo.GetHost());
    obj->SetProperty("trackerHost", eventInfo.GetTrackerHost());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnIntelligentTrackingPreventionResult(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<IntelligentTrackingPreventionResultEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), IntelligentTrackingPreventionResultEventToJSValue);

    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        auto context = PipelineBase::GetCurrentContext();
        if (context) {
            context->UpdateCurrentActiveNode(node);
        }
        auto executor = Container::CurrentTaskExecutorSafely();
        CHECK_NULL_VOID(executor);
        executor->PostTask([execCtx, postFunc = func, info]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto* eventInfo = TypeInfoHelper::DynamicCast<IntelligentTrackingPreventionResultEvent>(info.get());
            postFunc->Execute(*eventInfo);
            }, TaskExecutor::TaskType::UI, "ArkUIWebIntelligentTrackingPreventionResult");
    };
    WebModel::GetInstance()->SetIntelligentTrackingPreventionResultId(std::move(uiCallback));
}

void JSWeb::OnControllerAttached(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(args[0]));
    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode]() {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        auto context = PipelineBase::GetCurrentContext();
        if (context) {
            context->UpdateCurrentActiveNode(node);
        }
        auto executor = Container::CurrentTaskExecutorSafely();
        CHECK_NULL_VOID(executor);
        executor->PostSyncTask([execCtx, postFunc = func]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            postFunc->Execute();
            }, TaskExecutor::TaskType::UI, "ArkUIWebControllerAttached");
    };
    WebModel::GetInstance()->SetOnControllerAttached(std::move(uiCallback));
}

JSRef<JSVal> EmbedLifecycleChangeToJSValue(const NativeEmbedDataInfo& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("status", static_cast<int32_t>(eventInfo.GetStatus()));
    obj->SetProperty("surfaceId", eventInfo.GetSurfaceId());
    obj->SetProperty("embedId", eventInfo.GetEmbedId());

    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    JSRef<JSObject> requestObj = objectTemplate->NewInstance();
    requestObj->SetProperty("id", eventInfo.GetEmebdInfo().id);
    requestObj->SetProperty("type", eventInfo.GetEmebdInfo().type);
    requestObj->SetProperty("src", eventInfo.GetEmebdInfo().src);
    requestObj->SetProperty("tag", eventInfo.GetEmebdInfo().tag);
    requestObj->SetProperty("width", eventInfo.GetEmebdInfo().width);
    requestObj->SetProperty("height", eventInfo.GetEmebdInfo().height);
    requestObj->SetProperty("url", eventInfo.GetEmebdInfo().url);

    JSRef<JSObject> positionObj = objectTemplate->NewInstance();
    positionObj->SetProperty("x", eventInfo.GetEmebdInfo().x);
    positionObj->SetProperty("y", eventInfo.GetEmebdInfo().y);
    requestObj->SetPropertyObject("position", positionObj);

    auto params = eventInfo.GetEmebdInfo().params;
    JSRef<JSObject> paramsObj = objectTemplate->NewInstance();
    for (const auto& item : params) {
        paramsObj->SetProperty(item.first.c_str(), item.second.c_str());
    }
    requestObj->SetPropertyObject("params", paramsObj);

    obj->SetPropertyObject("info", requestObj);

    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> EmbedVisibilityChangeToJSValue(const NativeEmbedVisibilityInfo& visibilityInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("visibility", visibilityInfo.GetVisibility());
    obj->SetProperty("embedId", visibilityInfo.GetEmbedId());

    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnNativeEmbedLifecycleChange(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<NativeEmbedDataInfo, 1>>(
        JSRef<JSFunc>::Cast(args[0]), EmbedLifecycleChangeToJSValue);
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                            const BaseEventInfo* info) {
        int32_t instanceId = Container::CurrentIdSafely();
        auto webNode = node.Upgrade();
        if (webNode) {
            instanceId = webNode->GetInstanceId();
        }
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto* eventInfo = TypeInfoHelper::DynamicCast<NativeEmbedDataInfo>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetNativeEmbedLifecycleChangeId(jsCallback);
}

void JSWeb::OnNativeEmbedVisibilityChange(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<NativeEmbedVisibilityInfo, 1>>(
        JSRef<JSFunc>::Cast(args[0]), EmbedVisibilityChangeToJSValue);
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                            const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto* eventInfo = TypeInfoHelper::DynamicCast<NativeEmbedVisibilityInfo>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetNativeEmbedVisibilityChangeId(jsCallback);
}

JSRef<JSObject> CreateTouchInfo(const TouchLocationInfo& touchInfo, TouchEventInfo& info)
{
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    objectTemplate->SetInternalFieldCount(1);
    JSRef<JSObject> touchInfoObj = objectTemplate->NewInstance();
    const OHOS::Ace::Offset& globalLocation = touchInfo.GetGlobalLocation();
    const OHOS::Ace::Offset& localLocation = touchInfo.GetLocalLocation();
    const OHOS::Ace::Offset& screenLocation = touchInfo.GetScreenLocation();
    const OHOS::Ace::Offset& globalDisplayLocation = touchInfo.GetGlobalDisplayLocation();
    touchInfoObj->SetProperty<int32_t>("type", static_cast<int32_t>(touchInfo.GetTouchType()));
    touchInfoObj->SetProperty<int32_t>("id", touchInfo.GetFingerId());
    touchInfoObj->SetProperty<double>("displayX", screenLocation.GetX());
    touchInfoObj->SetProperty<double>("displayY", screenLocation.GetY());
    touchInfoObj->SetProperty<double>("windowX", globalLocation.GetX());
    touchInfoObj->SetProperty<double>("windowY", globalLocation.GetY());
    touchInfoObj->SetProperty<double>("screenX", globalLocation.GetX());
    touchInfoObj->SetProperty<double>("screenY", globalLocation.GetY());
    touchInfoObj->SetProperty<double>("x", localLocation.GetX());
    touchInfoObj->SetProperty<double>("y", localLocation.GetY());
    touchInfoObj->SetProperty<double>("globalDisplayX", globalDisplayLocation.GetX());
    touchInfoObj->SetProperty<double>("globalDisplayY", globalDisplayLocation.GetY());
    touchInfoObj->Wrap<TouchEventInfo>(&info);
    return touchInfoObj;
}

JSRef<JSVal> NativeEmbeadTouchToJSValue(const NativeEmbeadTouchInfo& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("embedId", eventInfo.GetEmbedId());
    auto info = eventInfo.GetTouchEventInfo();
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    JSRef<JSObject> eventObj = objectTemplate->NewInstance();
    JSRef<JSArray> touchArr = JSRef<JSArray>::New();
    JSRef<JSArray> changeTouchArr = JSRef<JSArray>::New();
    eventObj->SetProperty("source", static_cast<int32_t>(info.GetSourceDevice()));
    eventObj->SetProperty("timestamp", static_cast<double>(GetSysTimestamp()));
    auto target = CreateEventTargetObject(info);
    eventObj->SetPropertyObject("target", target);
    eventObj->SetProperty("pressure", info.GetForce());
    eventObj->SetProperty("sourceTool", static_cast<int32_t>(info.GetSourceTool()));
    eventObj->SetProperty("targetDisplayId", static_cast<int32_t>(info.GetTargetDisplayId()));
    eventObj->SetProperty("deviceId", static_cast<int64_t>(info.GetDeviceId()));

    if (info.GetChangedTouches().empty()) {
        return JSRef<JSVal>::Cast(obj);
    }
    uint32_t index = 0;
    TouchLocationInfo changeTouch = info.GetChangedTouches().back();
    JSRef<JSObject> changeTouchElement = CreateTouchInfo(changeTouch, info);
    changeTouchArr->SetValueAt(index, changeTouchElement);
    if (info.GetChangedTouches().size() > 0) {
        eventObj->SetProperty("type", static_cast<int32_t>(changeTouch.GetTouchType()));
    }

    const std::list<TouchLocationInfo>& touchList = info.GetTouches();
    for (const TouchLocationInfo& location : touchList) {
        if (location.GetFingerId() == changeTouch.GetFingerId()) {
            JSRef<JSObject> touchElement = CreateTouchInfo(changeTouch, info);
            touchArr->SetValueAt(index++, touchElement);
        } else {
            JSRef<JSObject> touchElement = CreateTouchInfo(location, info);
            touchArr->SetValueAt(index++, touchElement);
        }
    }
    eventObj->SetPropertyObject("touches", touchArr);
    eventObj->SetPropertyObject("changedTouches", changeTouchArr);
    obj->SetPropertyObject("touchEvent", eventObj);
    JSRef<JSObject> requestObj = JSClass<JSNativeEmbedGestureRequest>::NewInstance();
    auto requestEvent = Referenced::Claim(requestObj->Unwrap<JSNativeEmbedGestureRequest>());
    requestEvent->SetResult(eventInfo.GetResult());
    obj->SetPropertyObject("result", requestObj);
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> NativeEmbeadMouseToJSValue(const NativeEmbeadMouseInfo& eventInfo)
{
    auto info = eventInfo.GetMouseEventInfo();
    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    JSRef<JSObject> eventObj = objectTemplate->NewInstance();
    eventObj->SetProperty("source", static_cast<int32_t>(info.GetSourceDevice()));
    eventObj->SetProperty("timestamp", static_cast<double>(GetSysTimestamp()));
    auto target = CreateEventTargetObject(info);
    eventObj->SetPropertyObject("target", target);
    eventObj->SetProperty("pressure", info.GetForce());
    eventObj->SetProperty("sourceTool", static_cast<int32_t>(info.GetSourceTool()));
    eventObj->SetProperty("targetDisplayId", static_cast<int32_t>(info.GetTargetDisplayId()));
    eventObj->SetProperty("deviceId", static_cast<int64_t>(info.GetDeviceId()));

    eventObj->SetProperty<int32_t>("button", static_cast<int32_t>(info.GetButton()));
    eventObj->SetProperty<int32_t>("action", static_cast<int32_t>(info.GetAction()));
    Offset globalOffset = info.GetGlobalLocation();
    Offset localOffset = info.GetLocalLocation();
    Offset screenOffset = info.GetScreenLocation();
    eventObj->SetProperty<double>("displayX", screenOffset.GetX());
    eventObj->SetProperty<double>("displayY", screenOffset.GetY());
    eventObj->SetProperty<double>("windowX", globalOffset.GetX());
    eventObj->SetProperty<double>("windowY", globalOffset.GetY());
    eventObj->SetProperty<double>("screenX", globalOffset.GetX());
    eventObj->SetProperty<double>("screenY", globalOffset.GetY());
    eventObj->SetProperty<double>("x", localOffset.GetX());
    eventObj->SetProperty<double>("y", localOffset.GetY());

    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("embedId", eventInfo.GetEmbedId());
    obj->SetPropertyObject("mouseEvent", eventObj);
    JSRef<JSObject> requestObj = JSClass<JSNativeEmbedMouseRequest>::NewInstance();
    auto requestEvent = Referenced::Claim(requestObj->Unwrap<JSNativeEmbedMouseRequest>());
    requestEvent->SetResult(eventInfo.GetResult());
    obj->SetPropertyObject("result", requestObj);
    return JSRef<JSVal>::Cast(obj);
}

JSRef<JSVal> JSWeb::CreateNativeEmbedGestureHandler(const NativeEmbeadTouchInfo& eventInfo)
{
    JSRef<JSObject> requestObj = JSClass<JSNativeEmbedGestureRequest>::NewInstance();
    auto requestEvent = Referenced::Claim(requestObj->Unwrap<JSNativeEmbedGestureRequest>());
    requestEvent->SetResult(eventInfo.GetResult());
    return requestObj;
}

void JSWeb::OnNativeEmbedGestureEvent(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<NativeEmbeadTouchInfo, 1>>(
        JSRef<JSFunc>::Cast(args[0]), NativeEmbeadTouchToJSValue);
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                            const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto* eventInfo = TypeInfoHelper::DynamicCast<NativeEmbeadTouchInfo>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetNativeEmbedGestureEventId(jsCallback);
}

void JSWeb::OnNativeEmbedMouseEvent(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<NativeEmbeadMouseInfo, 1>>(
        JSRef<JSFunc>::Cast(args[0]), NativeEmbeadMouseToJSValue);
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                            const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto* eventInfo = TypeInfoHelper::DynamicCast<NativeEmbeadMouseInfo>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetNativeEmbedMouseEventId(jsCallback);
}

JSRef<JSVal> OverScrollEventToJSValue(const WebOnOverScrollEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("xOffset", eventInfo.GetX());
    obj->SetProperty("yOffset", eventInfo.GetY());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnOverScroll(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebOnOverScrollEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), OverScrollEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<WebOnOverScrollEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetOverScrollId(jsCallback);
}

void JSWeb::SetLayoutMode(int32_t layoutMode)
{
    auto mode = WebLayoutMode::NONE;
    switch (layoutMode) {
        case 0:
            mode = WebLayoutMode::NONE;
            break;
        case 1:
            mode = WebLayoutMode::FIT_CONTENT;
            break;
        default:
            mode = WebLayoutMode::NONE;
            break;
    }
    WebModel::GetInstance()->SetLayoutMode(mode);
}

void JSWeb::SetNestedScroll(const JSCallbackInfo& args)
{
    NestedScrollOptionsExt nestedOpt = {
        .scrollUp = NestedScrollMode::SELF_FIRST,
        .scrollDown = NestedScrollMode::SELF_FIRST,
        .scrollLeft = NestedScrollMode::SELF_FIRST,
        .scrollRight = NestedScrollMode::SELF_FIRST,
    };
    if (args.Length() < 1 || !args[0]->IsObject()) {
        WebModel::GetInstance()->SetNestedScrollExt(nestedOpt);
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    int32_t froward = -1;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollForward"), froward);
    if (CheckNestedScrollMode(froward)) {
        nestedOpt.scrollDown = static_cast<NestedScrollMode>(froward);
        nestedOpt.scrollRight = static_cast<NestedScrollMode>(froward);
    }
    int32_t backward = -1;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollBackward"), backward);
    if (CheckNestedScrollMode(backward)) {
        nestedOpt.scrollUp = static_cast<NestedScrollMode>(backward);
        nestedOpt.scrollLeft = static_cast<NestedScrollMode>(backward);
    }
    int32_t scrollUp = -1;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollUp"), scrollUp);
    if (CheckNestedScrollMode(scrollUp)) {
        nestedOpt.scrollUp = static_cast<NestedScrollMode>(scrollUp);
    }
    int32_t scrollDown = -1;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollDown"), scrollDown);
    if (CheckNestedScrollMode(scrollDown)) {
        nestedOpt.scrollDown = static_cast<NestedScrollMode>(scrollDown);
    }
    int32_t scrollLeft = -1;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollLeft"), scrollLeft);
    if (CheckNestedScrollMode(scrollLeft)) {
        nestedOpt.scrollLeft = static_cast<NestedScrollMode>(scrollLeft);
    }
    int32_t scrollRight = -1;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollRight"), scrollRight);
    if (CheckNestedScrollMode(scrollRight)) {
        nestedOpt.scrollRight = static_cast<NestedScrollMode>(scrollRight);
    }
    WebModel::GetInstance()->SetNestedScrollExt(nestedOpt);
    args.ReturnSelf();
}

bool JSWeb::CheckNestedScrollMode(const int32_t& modeValue)
{
    return modeValue >= static_cast<int32_t>(NestedScrollMode::SELF_ONLY) &&
           modeValue <= static_cast<int32_t>(NestedScrollMode::PARALLEL);
}

void JSWeb::SetMetaViewport(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsBoolean()) {
        return;
    }
    bool enabled = args[0]->ToBoolean();
    WebModel::GetInstance()->SetMetaViewport(enabled);
}

void JSWeb::ParseScriptItems(
    const JSCallbackInfo& args, ScriptItems& scriptItems, ScriptItemsByOrder& scriptItemsByOrder)
{
    if (args.Length() != 1 || args[0]->IsUndefined() || args[0]->IsNull() || !args[0]->IsArray()) {
        return;
    }
    auto paramArray = JSRef<JSArray>::Cast(args[0]);
    size_t length = paramArray->Length();
    if (length == 0) {
        return;
    }
    std::string script;
    std::vector<std::string> scriptRules;
    for (size_t i = 0; i < length; i++) {
        auto item = paramArray->GetValueAt(i);
        if (!item->IsObject()) {
            return;
        }
        auto itemObject = JSRef<JSObject>::Cast(item);
        JSRef<JSVal> jsScript = itemObject->GetProperty("script");
        JSRef<JSVal> jsScriptRules = itemObject->GetProperty("scriptRules");
        if (!jsScriptRules->IsArray() || JSRef<JSArray>::Cast(jsScriptRules)->Length() == 0) {
            return;
        }
        if (!JSViewAbstract::ParseJsString(jsScript, script)) {
            return;
        }
        scriptRules.clear();
        if (!JSViewAbstract::ParseJsStrArray(jsScriptRules, scriptRules)) {
            return;
        }
        if (scriptItems.find(script) == scriptItems.end()) {
            scriptItems.insert(std::make_pair(script, scriptRules));
            scriptItemsByOrder.emplace_back(script);
        }
    }
}

void JSWeb::JavaScriptOnDocumentStart(const JSCallbackInfo& args)
{
    ScriptItems scriptItems;
    ScriptItemsByOrder scriptItemsByOrder;
    ParseScriptItems(args, scriptItems, scriptItemsByOrder);

    WebModel::GetInstance()->JavaScriptOnDocumentStart(scriptItems);
}

void JSWeb::JavaScriptOnDocumentEnd(const JSCallbackInfo& args)
{
    ScriptItems scriptItems;
    ScriptItemsByOrder scriptItemsByOrder;
    ParseScriptItems(args, scriptItems, scriptItemsByOrder);

    WebModel::GetInstance()->JavaScriptOnDocumentEnd(scriptItems);
}

void JSWeb::RunJavaScriptOnDocumentStart(const JSCallbackInfo& args)
{
    ScriptItems scriptItems;
    ScriptItemsByOrder scriptItemsByOrder;
    ParseScriptItems(args, scriptItems, scriptItemsByOrder);

    WebModel::GetInstance()->JavaScriptOnDocumentStartByOrder(scriptItems, scriptItemsByOrder);
}

void JSWeb::RunJavaScriptOnDocumentEnd(const JSCallbackInfo& args)
{
    ScriptItems scriptItems;
    ScriptItemsByOrder scriptItemsByOrder;
    ParseScriptItems(args, scriptItems, scriptItemsByOrder);

    WebModel::GetInstance()->JavaScriptOnDocumentEndByOrder(scriptItems, scriptItemsByOrder);
}

void JSWeb::RunJavaScriptOnHeadEnd(const JSCallbackInfo& args)
{
    ScriptItems scriptItems;
    ScriptItemsByOrder scriptItemsByOrder;
    ParseScriptItems(args, scriptItems, scriptItemsByOrder);

    WebModel::GetInstance()->JavaScriptOnHeadReadyByOrder(scriptItems, scriptItemsByOrder);
}

void JSWeb::OnOverrideUrlLoading(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadOverrideEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadOverrideEventToJSValue);

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) -> bool {
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, false);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<LoadOverrideEvent>(info);
        JSRef<JSVal> message = func->ExecuteWithValue(*eventInfo);
        if (message->IsBoolean()) {
            return message->ToBoolean();
        }
        return false;
    };
    WebModel::GetInstance()->SetOnOverrideUrlLoading(std::move(uiCallback));
}

void JSWeb::CopyOption(int32_t copyOption)
{
    auto mode = CopyOptions::Local;
    switch (copyOption) {
        case static_cast<int32_t>(CopyOptions::None):
            mode = CopyOptions::None;
            break;
        case static_cast<int32_t>(CopyOptions::InApp):
            mode = CopyOptions::InApp;
            break;
        case static_cast<int32_t>(CopyOptions::Local):
            mode = CopyOptions::Local;
            break;
        case static_cast<int32_t>(CopyOptions::Distributed):
            mode = CopyOptions::Distributed;
            break;
        default:
            mode = CopyOptions::Local;
            break;
    }
    WebModel::GetInstance()->SetCopyOptionMode(mode);
}

void JSWeb::TextAutosizing(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsBoolean()) {
        return;
    }
    bool isTextAutosizing = args[0]->ToBoolean();
    WebModel::GetInstance()->SetTextAutosizing(isTextAutosizing);
}

void JSWeb::EnableNativeVideoPlayer(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(args[0]);
    std::optional<bool> enable;
    std::optional<bool> shouldOverlay;
    JSRef<JSVal> enableJsValue = paramObject->GetProperty("enable");
    if (enableJsValue->IsBoolean()) {
        enable = enableJsValue->ToBoolean();
    }
    JSRef<JSVal> shouldOverlayJsValue = paramObject->GetProperty("shouldOverlay");
    if (shouldOverlayJsValue->IsBoolean()) {
        shouldOverlay = shouldOverlayJsValue->ToBoolean();
    }
    if (!enable || !shouldOverlay) {
        // invalid NativeVideoPlayerConfig
        return;
    }
    WebModel::GetInstance()->SetNativeVideoPlayerConfig(*enable, *shouldOverlay);
}

JSRef<JSVal> RenderProcessNotRespondingToJSValue(const RenderProcessNotRespondingEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("jsStack", eventInfo.GetJsStack());
    obj->SetProperty("pid", eventInfo.GetPid());
    obj->SetProperty("reason", eventInfo.GetReason());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnRenderProcessNotResponding(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<RenderProcessNotRespondingEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), RenderProcessNotRespondingToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<RenderProcessNotRespondingEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetRenderProcessNotRespondingId(jsCallback);
}

JSRef<JSVal> RenderProcessRespondingEventToJSValue(const RenderProcessRespondingEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnRenderProcessResponding(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<RenderProcessRespondingEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), RenderProcessRespondingEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<RenderProcessRespondingEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetRenderProcessRespondingId(jsCallback);
}

void JSWeb::SelectionMenuOptions(const JSCallbackInfo& args)
{
    if (args.Length() != 1 || args[0]->IsUndefined() || args[0]->IsNull() || !args[0]->IsArray()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto menuItamArray = JSRef<JSArray>::Cast(args[0]);
    WebMenuOptionsParam optionParam;
    NG::MenuOptionsParam menuOption;
    for (size_t i = 0; i < menuItamArray->Length(); i++) {
        auto menuItem = menuItamArray->GetValueAt(i);
        if (!menuItem->IsObject()) {
            return;
        }
        auto menuItemObject = JSRef<JSObject>::Cast(menuItem);
        auto jsContent = menuItemObject->GetProperty("content");
        auto jsStartIcon = menuItemObject->GetProperty("startIcon");
        std::string content;
        if (!ParseJsMedia(jsContent, content)) {
            return;
        }
        menuOption.content = content;
        std::string icon;
        menuOption.icon.reset();
        if (ParseJsMedia(jsStartIcon, icon)) {
            menuOption.icon = icon;
        }
        auto jsAction = menuItemObject->GetProperty("action");
        if (jsAction.IsEmpty() || !jsAction->IsFunction()) {
            return;
        }
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(jsAction));
        auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc),
                           node = frameNode](const std::string selectInfo) {
            auto webNode = node.Upgrade();
            CHECK_NULL_VOID(webNode);
            ContainerScope scope(webNode->GetInstanceId());
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto pipelineContext = PipelineContext::GetCurrentContext();
            if (pipelineContext) {
                pipelineContext->UpdateCurrentActiveNode(node);
                pipelineContext->SetCallBackNode(node);
            }
            auto newSelectInfo = JSRef<JSVal>::Make(ToJSValue(selectInfo));
            func->ExecuteJS(1, &newSelectInfo);
        };
        menuOption.action = std::move(jsCallback);
        optionParam.menuOption.push_back(menuOption);
    }
    WebModel::GetInstance()->SetSelectionMenuOptions(std::move(optionParam));
}

JSRef<JSVal> ViewportFitChangedToJSValue(const ViewportFitChangedEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("viewportFit", eventInfo.GetViewportFit());
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::OnViewportFitChanged(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ViewportFitChangedEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ViewportFitChangedToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<ViewportFitChangedEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetViewportFitChangedId(jsCallback);
}

JSRef<JSVal> InterceptKeyboardEventToJSValue(const InterceptKeyboardEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSObject> webKeyboardControllerObj = JSClass<JSWebKeyboardController>::NewInstance();
    auto webKeyboardController = Referenced::Claim(webKeyboardControllerObj->Unwrap<JSWebKeyboardController>());
    webKeyboardController->SeWebKeyboardController(eventInfo.GetCustomKeyboardHandler());
    obj->SetPropertyObject("controller", webKeyboardControllerObj);

    JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
    JSRef<JSObject> attributesObj = objectTemplate->NewInstance();
    for (const auto& item : eventInfo.GetAttributesMap()) {
        attributesObj->SetProperty(item.first.c_str(), item.second.c_str());
    }
    obj->SetPropertyObject("attributes", attributesObj);
    return JSRef<JSVal>::Cast(obj);
}

void JSWeb::ParseJsCustomKeyboardOption(const JsiExecutionContext& context, const JSRef<JSVal>& keyboardOpt,
    WebKeyboardOption& keyboardOption)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebCustomKeyboard ParseJsCustomKeyboardOption enter");
    if (!keyboardOpt->IsObject()) {
        return;
    }

    JSRef<JSObject> keyboradOptObj = JSRef<JSObject>::Cast(keyboardOpt);
    auto useSystemKeyboardObj = keyboradOptObj->GetProperty("useSystemKeyboard");
    if (useSystemKeyboardObj->IsNull() || !useSystemKeyboardObj->IsBoolean()) {
        return;
    }

    bool isSystemKeyboard = useSystemKeyboardObj->ToBoolean();
    keyboardOption.isSystemKeyboard_ = isSystemKeyboard;
    TAG_LOGI(AceLogTag::ACE_WEB, "WebCustomKeyboard ParseJsCustomKeyboardOption isSystemKeyboard is %{public}d",
        isSystemKeyboard);
    if (isSystemKeyboard) {
        auto enterKeyTypeObj = keyboradOptObj->GetProperty("enterKeyType");
        if (enterKeyTypeObj->IsNull() || !enterKeyTypeObj->IsNumber()) {
            return;
        }
        int32_t enterKeyType = enterKeyTypeObj->ToNumber<int32_t>();
        keyboardOption.enterKeyTpye_ = enterKeyType;
        TAG_LOGI(AceLogTag::ACE_WEB, "WebCustomKeyboard ParseJsCustomKeyboardOption \
            isSystemKeyboard is %{public}d, enterKeyType is %{public}d", isSystemKeyboard, enterKeyType);
    } else {
        auto builder = keyboradOptObj->GetProperty("customKeyboard");
        if (builder->IsNull()) {
            TAG_LOGE(AceLogTag::ACE_WEB, "WebCustomKeyboard ParseJsCustomKeyboardOption" \
                ", parse customKeyboard, builder is null");
            return;
        }

        if (!builder->IsFunction()) {
            TAG_LOGE(AceLogTag::ACE_WEB, "WebCustomKeyboard ParseJsCustomKeyboardOption" \
                ", parse customKeyboard, builder is invalid");
            return;
        }

        auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(builder));
        CHECK_NULL_VOID(builderFunc);
        WeakPtr<NG::FrameNode> targetNode =
            AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto buildFunc = [execCtx = context, func = std::move(builderFunc), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("WebCustomKeyboard");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        keyboardOption.customKeyboardBuilder_ = buildFunc;
        TAG_LOGI(AceLogTag::ACE_WEB, "WebCustomKeyboard ParseJsCustomKeyboardOption" \
            ", isSystemKeyboard is %{public}d, parseCustomBuilder end", isSystemKeyboard);
    }
}

void JSWeb::OnInterceptKeyboardAttach(const JSCallbackInfo& args)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebCustomKeyboard OnInterceptKeyboardAttach register enter");
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<InterceptKeyboardEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), InterceptKeyboardEventToJSValue);

    auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) -> WebKeyboardOption {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebCustomKeyboard OnInterceptKeyboardAttach invoke enter");
        WebKeyboardOption opt;
        auto webNode = node.Upgrade();
        CHECK_NULL_RETURN(webNode, opt);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, opt);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<InterceptKeyboardEvent>(info);
        JSRef<JSVal> keyboardOpt = func->ExecuteWithValue(*eventInfo);
        ParseJsCustomKeyboardOption(execCtx, keyboardOpt, opt);
        return opt;
    };
    WebModel::GetInstance()->SetOnInterceptKeyboardAttach(std::move(uiCallback));
}

void JSWeb::OnAdsBlocked(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<AdsBlockedEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), AdsBlockedEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<AdsBlockedEvent>(info);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetAdsBlockedEventId(jsCallback);
}

void JSWeb::ForceDisplayScrollBar(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsBoolean()) {
        return;
    }
    bool isEnabled = args[0]->ToBoolean();
    WebModel::GetInstance()->SetOverlayScrollbarEnabled(isEnabled);
}

void JSWeb::KeyboardAvoidMode(int32_t mode)
{
    if (mode < static_cast<int32_t>(WebKeyboardAvoidMode::RESIZE_VISUAL) ||
        mode > static_cast<int32_t>(WebKeyboardAvoidMode::DEFAULT)) {
        TAG_LOGE(AceLogTag::ACE_WEB, "KeyboardAvoidMode param err");
        return;
    }
    WebKeyboardAvoidMode avoidMode = static_cast<WebKeyboardAvoidMode>(mode);
    WebModel::GetInstance()->SetKeyboardAvoidMode(avoidMode);
}

void JSWeb::EditMenuOptions(const JSCallbackInfo& info)
{
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    NG::OnPrepareMenuCallback onPrepareMenuCallback;
    JSViewAbstract::ParseEditMenuOptions(info, onCreateMenuCallback, onMenuItemClick, onPrepareMenuCallback);
    WebModel::GetInstance()->SetEditMenuOptions(
        std::move(onCreateMenuCallback), std::move(onMenuItemClick), std::move(onPrepareMenuCallback));
}

void JSWeb::EnableHapticFeedback(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsBoolean()) {
        return;
    }
    bool isEnabled = args[0]->ToBoolean();
    WebModel::GetInstance()->SetEnabledHapticFeedback(isEnabled);
}

void JSWeb::OptimizeParserBudgetEnabled(bool enable)
{
    WebModel::GetInstance()->SetOptimizeParserBudgetEnabled(enable);
}

void JSWeb::EnableWebAVSession(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsBoolean()) {
        return;
    }
    bool isEnabled = args[0]->ToBoolean();
    WebModel::GetInstance()->SetWebMediaAVSessionEnabled(isEnabled);
}

void JSWeb::EnableDataDetector(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsBoolean()) {
        return;
    }
    bool isEnabled = args[0]->ToBoolean();
    WebModel::GetInstance()->SetEnableDataDetector(isEnabled);
}

void JSWeb::DataDetectorConfig(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }
    JSRef<JSVal> obj = args[0];
    if (!obj->IsObject()) {
        return;
    }

    TextDetectConfig textDetectConfig;
    if (!JSViewAbstract::ParseDataDetectorConfig(args, textDetectConfig)) {
        return;
    }
    WebModel::GetInstance()->SetDataDetectorConfig(textDetectConfig);
}

void JSWeb::BypassVsyncCondition(int32_t webBypassVsyncCondition)
{
    auto condition = WebBypassVsyncCondition::NONE;
    switch (webBypassVsyncCondition) {
        case 0:
            condition = WebBypassVsyncCondition::NONE;
            break;
        case 1:
            condition = WebBypassVsyncCondition::SCROLLBY_FROM_ZERO_OFFSET;
            break;
        default:
            condition = WebBypassVsyncCondition::NONE;
            break;
    }
    WebModel::GetInstance()->SetBypassVsyncCondition(condition);
}

void JSWeb::EnableFollowSystemFontWeight(bool enableFollowSystemFontWeight)
{
    WebModel::GetInstance()->SetEnableFollowSystemFontWeight(enableFollowSystemFontWeight);
}

void JSWeb::GestureFocusMode(int32_t gestureFocusMode)
{
    if (gestureFocusMode < static_cast<int32_t>(GestureFocusMode::DEFAULT) ||
        gestureFocusMode > static_cast<int32_t>(GestureFocusMode::GESTURE_TAP_AND_LONG_PRESS)) {
        TAG_LOGE(AceLogTag::ACE_WEB, "GestureFocusMode param err");
        return;
    }
    auto mode = static_cast<enum GestureFocusMode>(gestureFocusMode);
    WebModel::GetInstance()->SetGestureFocusMode(mode);
}

void JSWeb::OnPdfScrollAtBottom(const JSCallbackInfo& args)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "JSWeb::OnPdfScrollAtBottom, callback set");
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<PdfScrollEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), PdfScrollEventToJSValue);

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        CHECK_NULL_VOID(func);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<PdfScrollEvent>(info);
        CHECK_NULL_VOID(eventInfo);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetOnPdfScrollAtBottom(jsCallback);
}

void JSWeb::OnPdfLoadEvent(const JSCallbackInfo& args)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "JSWeb::OnPdfLoadEvent, callback set");
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<PdfLoadEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), PdfLoadEventToJSValue);

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        auto webNode = node.Upgrade();
        CHECK_NULL_VOID(webNode);
        ContainerScope scope(webNode->GetInstanceId());
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        CHECK_NULL_VOID(func);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        if (pipelineContext) {
            pipelineContext->UpdateCurrentActiveNode(node);
        }
        auto* eventInfo = TypeInfoHelper::DynamicCast<PdfLoadEvent>(info);
        CHECK_NULL_VOID(eventInfo);
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetOnPdfLoadEvent(jsCallback);
}
} // namespace OHOS::Ace::Framework
