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

#include "pixel_map.h"
#include "pixel_map_napi.h"

#include "base/log/ace_scoring_log.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "base/web/webview/ohos_nweb/include/nweb.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/web/web_model_ng.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {
namespace {
const std::string RAWFILE_PREFIX = "resource://RAWFILE/";
const std::string BUNDLE_NAME_PREFIX = "bundleName:";
const std::string MODULE_NAME_PREFIX = "moduleName:";
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
bool JSWeb::webDebuggingAccess_ = false;
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
            TAG_LOGD(AceLogTag::ACE_WEB, "Web certificate information processing handle, obtaining information failed");
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
            response_->SetFileHandle(fd);
            return;
        }
        if (args[0]->IsString()) {
            auto data = args[0]->ToString();
            response_->SetData(data);
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
            TAG_LOGD(AceLogTag::ACE_WEB, "intercept set data url %{public}s", url.c_str());
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
            TAG_LOGD(AceLogTag::ACE_WEB, "Set Response Header %{public}s:%{public}s", keystr.c_str(), valstr.c_str());
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
    JSClass<JSWeb>::StaticMethod("onUrlLoadIntercept", &JSWeb::OnUrlLoadIntercept);
    JSClass<JSWeb>::StaticMethod("onLoadIntercept", &JSWeb::OnLoadIntercept);
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
    JSClass<JSWeb>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSWeb>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSWeb>::StaticMethod("onWindowNew", &JSWeb::OnWindowNew);
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
    JSClass<JSWeb>::StaticMethod("horizontalScrollBarAccess", &JSWeb::HorizontalScrollBarAccess);
    JSClass<JSWeb>::StaticMethod("verticalScrollBarAccess", &JSWeb::VerticalScrollBarAccess);
    JSClass<JSWeb>::StaticMethod("onAudioStateChanged", &JSWeb::OnAudioStateChanged);
    JSClass<JSWeb>::StaticMethod("mediaOptions", &JSWeb::MediaOptions);
    JSClass<JSWeb>::StaticMethod("onFirstContentfulPaint", &JSWeb::OnFirstContentfulPaint);
    JSClass<JSWeb>::StaticMethod("onControllerAttached", &JSWeb::OnControllerAttached);
    JSClass<JSWeb>::StaticMethod("onOverScroll", &JSWeb::OnOverScroll);
    JSClass<JSWeb>::StaticMethod("copyOptions", &JSWeb::CopyOption);
    JSClass<JSWeb>::StaticMethod("onScreenCaptureRequest", &JSWeb::OnScreenCaptureRequest);
    JSClass<JSWeb>::StaticMethod("layoutMode", &JSWeb::SetLayoutMode);
    JSClass<JSWeb>::StaticMethod("nestedScroll", &JSWeb::SetNestedScroll);
    JSClass<JSWeb>::StaticMethod("javaScriptOnDocumentStart", &JSWeb::JavaScriptOnDocumentStart);
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
    JSWebSslSelectCert::JSBind(globalObj);
    JSWebPermissionRequest::JSBind(globalObj);
    JSContextMenuParam::JSBind(globalObj);
    JSContextMenuResult::JSBind(globalObj);
    JSWebWindowNewHandler::JSBind(globalObj);
    JSDataResubmitted::JSBind(globalObj);
    JSScreenCaptureRequest::JSBind(globalObj);
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

JSRef<JSVal> ContextMenuHideEventToJSValue(const ContextMenuHideEvent& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    obj->SetProperty("info", eventInfo.GetInfo());
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
    return JSRef<JSVal>::Cast(obj);
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
        (bundleName != AceApplicationInfo::GetInstance().GetPackageName() ||
        moduleName != container->GetModuleName())) {
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
    TAG_LOGD(AceLogTag::ACE_WEB, "Web Create src:%{public}s", dstSrc->c_str());

    auto controllerObj = paramObject->GetProperty("controller");
    if (!controllerObj->IsObject()) {
        return;
    }
    auto type = paramObject->GetProperty("type");
    WebType webType = WebType::SURFACE;
    if (type->IsNumber() && (type->ToNumber<int32_t>() >= 0) && (type->ToNumber<int32_t>() <= 1)) {
        webType = static_cast<WebType>(type->ToNumber<int32_t>());
    }
    auto controller = JSRef<JSObject>::Cast(controllerObj);
    auto setWebIdFunction = controller->GetProperty("setWebId");
    if (setWebIdFunction->IsFunction()) {
        auto setIdCallback = [webviewController = controller, func = JSRef<JSFunc>::Cast(setWebIdFunction)](
                                 int32_t webId) {
            JSRef<JSVal> argv[] = { JSRef<JSVal>::Make(ToJSValue(webId)) };
            func->Call(webviewController, 1, argv);
        };

        auto setHapPathFunction = controller->GetProperty("innerSetHapPath");
        std::function<void(const std::string&)> setHapPathCallback = nullptr;
        if (setHapPathFunction->IsFunction()) {
            setHapPathCallback = [webviewController = controller, func = JSRef<JSFunc>::Cast(setHapPathFunction)](
                                     const std::string& hapPath) {
                JSRef<JSVal> argv[] = { JSRef<JSVal>::Make(ToJSValue(hapPath)) };
                func->Call(webviewController, 1, argv);
            };
        }

        int32_t parentNWebId = -1;
        bool isPopup = JSWebWindowNewHandler::ExistController(controller, parentNWebId);
        WebModel::GetInstance()->Create(
            dstSrc.value(), std::move(setIdCallback), std::move(setHapPathCallback), parentNWebId, isPopup, webType);

        auto getCmdLineFunction = controller->GetProperty("getCustomeSchemeCmdLine");
        std::string cmdLine = JSRef<JSFunc>::Cast(getCmdLineFunction)->Call(controller, 0, {})->ToString();
        if (!cmdLine.empty()) {
            WebModel::GetInstance()->SetCustomScheme(cmdLine);
        }

        auto getWebDebugingFunction = controller->GetProperty("getWebDebuggingAccess");
        bool webDebuggingAccess = JSRef<JSFunc>::Cast(getWebDebugingFunction)->Call(controller, 0, {})->ToBoolean();
        if (webDebuggingAccess == JSWeb::webDebuggingAccess_) {
            return;
        }
        WebModel::GetInstance()->SetWebDebuggingAccessEnabled(webDebuggingAccess);
        JSWeb::webDebuggingAccess_ = webDebuggingAccess;
        return;

    } else {
        auto* jsWebController = controller->Unwrap<JSWebController>();
        WebModel::GetInstance()->Create(dstSrc.value(), jsWebController->GetController(), webType);
    }

    WebModel::GetInstance()->SetFocusable(true);
    WebModel::GetInstance()->SetFocusNode(true);
}

void JSWeb::WebRotate(const JSCallbackInfo& args)
{
    TAG_LOGD(AceLogTag::ACE_WEB, "Web rotate is not supported.");
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
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc =
        AceType::MakeRefPtr<JsEventFunction<WebDialogEvent, 1>>(JSRef<JSFunc>::Cast(args[0]), WebDialogEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) -> bool {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, false);
        pipelineContext->UpdateCurrentActiveNode(node);
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

    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) -> bool {
        bool result = false;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, result);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, false);
        pipelineContext->UpdateCurrentActiveNode(node);
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

    auto instanceId = Container::CurrentId();
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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

    auto instanceId = Container::CurrentId();
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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

    auto instanceId = Container::CurrentId();
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebTitleReceiveEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebTitleReceiveEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<FullScreenExitEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), FullScreenExitEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<FullScreenEnterEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), FullScreenEnterEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        CHECK_NULL_VOID(func);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebGeolocationHideEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebGeolocationHideEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebGeolocationShowEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebGeolocationShowEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<LoadWebRequestFocusEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), LoadWebRequestFocusEventToJSValue);
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                          const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<DownloadStartEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), DownloadStartEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebHttpAuthEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), WebHttpAuthEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) -> bool {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, false);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebSslErrorEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), WebSslErrorEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) -> bool {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, false);
        pipelineContext->UpdateCurrentActiveNode(node);
        auto* eventInfo = TypeInfoHelper::DynamicCast<WebSslErrorEvent>(info);
        func->Execute(*eventInfo);
        return true;
    };
    WebModel::GetInstance()->SetOnSslErrorRequest(jsCallback);
}

void JSWeb::OnSslSelectCertRequest(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebSslSelectCertEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), WebSslSelectCertEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) -> bool {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, false);
        pipelineContext->UpdateCurrentActiveNode(node);
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

    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    RefPtr<JsKeyFunction> jsOnKeyEventFunc = AceType::MakeRefPtr<JsKeyFunction>(JSRef<JSFunc>::Cast(args[0]));
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsOnKeyEventFunc), node = frameNode](
                          KeyEventInfo& keyEventInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ReceivedErrorEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ReceivedErrorEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ReceivedHttpErrorEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ReceivedHttpErrorEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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

void JSWeb::OnInterceptRequest(const JSCallbackInfo& args)
{
    if ((args.Length() <= 0) || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<OnInterceptRequestEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), OnInterceptRequestEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) -> RefPtr<WebResponse> {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, nullptr);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, nullptr);
        pipelineContext->UpdateCurrentActiveNode(node);
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

void JSWeb::OnUrlLoadIntercept(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<UrlLoadInterceptEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), UrlLoadInterceptEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) -> bool {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, false);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    auto instanceId = Container::CurrentId();
    
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) -> bool {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, false);
        pipelineContext->UpdateCurrentActiveNode(node);
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

void JSWeb::OnFileSelectorShow(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<FileSelectorEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), FileSelectorEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) -> bool {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, false);
        pipelineContext->UpdateCurrentActiveNode(node);
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

void JSWeb::OnContextMenuShow(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ContextMenuEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ContextMenuEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) -> bool {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, false);
        pipelineContext->UpdateCurrentActiveNode(node);
        auto* eventInfo = TypeInfoHelper::DynamicCast<ContextMenuEvent>(info);
        JSRef<JSVal> message = func->ExecuteWithValue(*eventInfo);
        if (message->IsBoolean()) {
            return message->ToBoolean();
        }
        return false;
    };
    WebModel::GetInstance()->SetOnContextMenuShow(jsCallback);
}

void JSWeb::OnContextMenuHide(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ContextMenuHideEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ContextMenuHideEventToJSValue);

    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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

void JSWeb::GeolocationAccessEnabled(bool isGeolocationAccessEnabled)
{
    WebModel::GetInstance()->SetGeolocationAccessEnabled(isGeolocationAccessEnabled);
}

void JSWeb::JavaScriptProxy(const JSCallbackInfo& args)
{
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(args[0]);
    auto controllerObj = paramObject->GetProperty("controller");
    auto object = JSRef<JSVal>::Cast(paramObject->GetProperty("object"));
    auto name = JSRef<JSVal>::Cast(paramObject->GetProperty("name"));
    auto methodList = JSRef<JSVal>::Cast(paramObject->GetProperty("methodList"));
    if (!controllerObj->IsObject()) {
        return;
    }
    auto controller = JSRef<JSObject>::Cast(controllerObj);
    auto jsProxyFunction = controller->GetProperty("jsProxy");
    if (jsProxyFunction->IsFunction()) {
        auto jsProxyCallback = [webviewController = controller, func = JSRef<JSFunc>::Cast(jsProxyFunction), object,
                                   name, methodList]() {
            JSRef<JSVal> argv[] = { object, name, methodList };
            func->Call(webviewController, 3, argv);
        };

        WebModel::GetInstance()->SetJsProxyCallback(jsProxyCallback);
    }
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<RenderExitedEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), RenderExitedEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<RefreshAccessedHistoryEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), RefreshAccessedHistoryEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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

    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    RefPtr<JsClickFunction> jsOnMouseFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(args[0]));
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsOnMouseFunc), node = frameNode](
                          MouseInfo& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ResourceLoadEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ResourceLoadEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<ScaleChangeEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ScaleChangeEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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

    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc =
        AceType::MakeRefPtr<JsEventFunction<WebOnScrollEvent, 1>>(JSRef<JSFunc>::Cast(args[0]), ScrollEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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

void JSWeb::OnPermissionRequest(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebPermissionRequestEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), PermissionRequestEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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

void JSWeb::OnScreenCaptureRequest(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebScreenCaptureRequestEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), ScreenCaptureRequestEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
        return;
    }
    WebModel::GetInstance()->SetBackgroundColor(backgroundColor);
}

void JSWeb::InitialScale(float scale)
{
    WebModel::GetInstance()->InitialScale(scale);
}

void JSWeb::Password(bool password)
{
    TAG_LOGD(AceLogTag::ACE_WEB, "Sets the Web should save the password.");
}

void JSWeb::TableData(bool tableData)
{
    TAG_LOGD(AceLogTag::ACE_WEB, "Sets the Web should save the table data.");
}

void JSWeb::OnFileSelectorShowAbandoned(const JSCallbackInfo& args)
{
    TAG_LOGD(AceLogTag::ACE_WEB, "Set whether to discard the file abandoned.");
}

void JSWeb::WideViewModeAccess(const JSCallbackInfo& args)
{
    TAG_LOGD(AceLogTag::ACE_WEB, "Sets the Web access meta 'viewport' in HTML.");
}

void JSWeb::WebDebuggingAccess(const JSCallbackInfo& args)
{
    TAG_LOGD(AceLogTag::ACE_WEB, "Set up web debugging access.");
}

void JSWeb::OnSearchResultReceive(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<SearchResultReceiveEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), SearchResultReceiveEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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

    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    RefPtr<JsDragFunction> jsOnDragStartFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragStartId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragStartFunc), node = frameNode](
                             const RefPtr<DragEvent>& info, const std::string& extraParams) -> NG::DragDropBaseInfo {
        NG::DragDropBaseInfo itemInfo;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, itemInfo);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, itemInfo);
        pipelineContext->UpdateCurrentActiveNode(node);
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

    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    RefPtr<JsDragFunction> jsOnDragEnterFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragEnterId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragEnterFunc), node = frameNode](
                             const RefPtr<DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragEnter");
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
        func->Execute(info, extraParams);
    };

    WebModel::GetInstance()->SetOnDragEnter(onDragEnterId);
}

void JSWeb::JsOnDragMove(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    RefPtr<JsDragFunction> jsOnDragMoveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragMoveId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragMoveFunc), node = frameNode](
                            const RefPtr<DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragMove");
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
        func->Execute(info, extraParams);
    };

    WebModel::GetInstance()->SetOnDragMove(onDragMoveId);
}

void JSWeb::JsOnDragLeave(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    RefPtr<JsDragFunction> jsOnDragLeaveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragLeaveId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragLeaveFunc), node = frameNode](
                             const RefPtr<DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragLeave");
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
        func->Execute(info, extraParams);
    };

    WebModel::GetInstance()->SetOnDragLeave(onDragLeaveId);
}

void JSWeb::JsOnDrop(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    RefPtr<JsDragFunction> jsOnDropFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDropId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDropFunc), node = frameNode](
                        const RefPtr<DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDrop");
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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

bool HandleWindowNewEvent(const WebWindowNewEvent* eventInfo)
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

    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebWindowNewEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), WindowNewEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        ContainerScope scope(instanceId);
        ACE_SCORING_EVENT("OnWindowNew CallBack");
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
        auto* eventInfo = TypeInfoHelper::DynamicCast<WebWindowNewEvent>(info.get());
        if (!func || !HandleWindowNewEvent(eventInfo)) {
            return;
        }
        func->Execute(*eventInfo);
    };
    WebModel::GetInstance()->SetWindowNewEvent(jsCallback);
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebWindowExitEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), WindowExitEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<PageVisibleEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), PageVisibleEventToJSValue);

    auto instanceId = Container::CurrentId();
    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        ContainerScope scope(instanceId);
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->UpdateCurrentActiveNode(node);
        context->PostAsyncEvent([execCtx, postFunc = func, info]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto* eventInfo = TypeInfoHelper::DynamicCast<PageVisibleEvent>(info.get());
            postFunc->Execute(*eventInfo);
        });
    };
    WebModel::GetInstance()->SetPageVisibleId(std::move(uiCallback));
}

void JSWeb::OnInterceptKeyEvent(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    RefPtr<JsKeyFunction> jsOnPreKeyEventFunc = AceType::MakeRefPtr<JsKeyFunction>(JSRef<JSFunc>::Cast(args[0]));
    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsOnPreKeyEventFunc), node = frameNode](
                          KeyEventInfo& keyEventInfo) -> bool {
        bool result = false;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, result);
        ACE_SCORING_EVENT("onPreKeyEvent");
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, result);
        pipelineContext->UpdateCurrentActiveNode(node);
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

void JSWeb::OnDataResubmitted(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<DataResubmittedEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), DataResubmittedEventToJSValue);

    auto instanceId = Container::CurrentId();
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        ContainerScope scope(instanceId);
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->UpdateCurrentActiveNode(node);
        context->PostSyncEvent([execCtx, postFunc = func, info]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto* eventInfo = TypeInfoHelper::DynamicCast<DataResubmittedEvent>(info.get());
            postFunc->Execute(*eventInfo);
        });
    };
    WebModel::GetInstance()->SetOnDataResubmitted(uiCallback);
}

Media::PixelFormat GetPixelFormat(NWeb::ImageColorType colorType)
{
    Media::PixelFormat pixelFormat;
    switch (colorType) {
        case NWeb::ImageColorType::COLOR_TYPE_UNKNOWN:
            pixelFormat = Media::PixelFormat::UNKNOWN;
            break;
        case NWeb::ImageColorType::COLOR_TYPE_RGBA_8888:
            pixelFormat = Media::PixelFormat::RGBA_8888;
            break;
        case NWeb::ImageColorType::COLOR_TYPE_BGRA_8888:
            pixelFormat = Media::PixelFormat::BGRA_8888;
            break;
        default:
            pixelFormat = Media::PixelFormat::UNKNOWN;
            break;
    }
    return pixelFormat;
}

Media::AlphaType GetAlphaType(NWeb::ImageAlphaType alphaType)
{
    Media::AlphaType imageAlphaType;
    switch (alphaType) {
        case NWeb::ImageAlphaType::ALPHA_TYPE_UNKNOWN:
            imageAlphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN;
            break;
        case NWeb::ImageAlphaType::ALPHA_TYPE_OPAQUE:
            imageAlphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_OPAQUE;
            break;
        case NWeb::ImageAlphaType::ALPHA_TYPE_PREMULTIPLIED:
            imageAlphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL;
            break;
        case NWeb::ImageAlphaType::ALPHA_TYPE_POSTMULTIPLIED:
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
    opt.pixelFormat = GetPixelFormat(NWeb::ImageColorType(colorType));
    opt.alphaType = GetAlphaType(NWeb::ImageAlphaType(alphaType));
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

void JSWeb::OnFaviconReceived(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<FaviconReceivedEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), FaviconReceivedEventToJSValue);

    auto instanceId = Container::CurrentId();
    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        ContainerScope scope(instanceId);
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->UpdateCurrentActiveNode(node);
        context->PostAsyncEvent([execCtx, postFunc = func, info]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto* eventInfo = TypeInfoHelper::DynamicCast<FaviconReceivedEvent>(info.get());
            postFunc->Execute(*eventInfo);
        });
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<TouchIconUrlEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), TouchIconUrlEventToJSValue);

    auto instanceId = Container::CurrentId();
    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        ContainerScope scope(instanceId);
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->UpdateCurrentActiveNode(node);
        context->PostAsyncEvent([execCtx, postFunc = func, info]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto* eventInfo = TypeInfoHelper::DynamicCast<TouchIconUrlEvent>(info.get());
            postFunc->Execute(*eventInfo);
        });
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
    TAG_LOGD(AceLogTag::ACE_WEB, "Web Audio State Changed.");
    if (!args[0]->IsFunction()) {
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<AudioStateChangedEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), AudioStateChangedEventToJSValue);

    auto instanceId = Container::CurrentId();
    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<FirstContentfulPaintEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), FirstContentfulPaintEventToJSValue);

    auto instanceId = Container::CurrentId();
    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const std::shared_ptr<BaseEventInfo>& info) {
        ContainerScope scope(instanceId);
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->UpdateCurrentActiveNode(node);
        context->PostAsyncEvent([execCtx, postFunc = func, info]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto* eventInfo = TypeInfoHelper::DynamicCast<FirstContentfulPaintEvent>(info.get());
            postFunc->Execute(*eventInfo);
        });
    };
    WebModel::GetInstance()->SetFirstContentfulPaintId(std::move(uiCallback));
}

void JSWeb::OnControllerAttached(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(args[0]));
    auto instanceId = Container::CurrentId();
    auto uiCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId,
                          node = frameNode]() {
        ContainerScope scope(instanceId);
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->UpdateCurrentActiveNode(node);
        context->PostAsyncEvent([execCtx, postFunc = func]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            postFunc->Execute();
        });
    };
    WebModel::GetInstance()->SetOnControllerAttached(std::move(uiCallback));
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
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<WebOnOverScrollEvent, 1>>(
        JSRef<JSFunc>::Cast(args[0]), OverScrollEventToJSValue);
    auto instanceId = Container::CurrentId();
    auto jsCallback = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), instanceId, node = frameNode](
                          const BaseEventInfo* info) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
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
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    if (args.Length() < 1 || !args[0]->IsObject()) {
        WebModel::GetInstance()->SetNestedScroll(nestedOpt);
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    int32_t froward = 0;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollForward"), froward);
    if (froward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        froward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        froward = 0;
    }
    int32_t backward = 0;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollBackward"), backward);
    if (backward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        backward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        backward = 0;
    }
    nestedOpt.forward = static_cast<NestedScrollMode>(froward);
    nestedOpt.backward = static_cast<NestedScrollMode>(backward);
    WebModel::GetInstance()->SetNestedScroll(nestedOpt);
    args.ReturnSelf();
}

void JSWeb::JavaScriptOnDocumentStart(const JSCallbackInfo& args)
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
    ScriptItems scriptItems;
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
        }
    }
    WebModel::GetInstance()->JavaScriptOnDocumentStart(scriptItems);
}

void JSWeb::CopyOption(int32_t copyOption)
{
    auto mode = CopyOptions::Distributed;
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
            mode = CopyOptions::Distributed;
            break;
    }
    WebModel::GetInstance()->SetCopyOptionMode(mode);
}
} // namespace OHOS::Ace::Framework
