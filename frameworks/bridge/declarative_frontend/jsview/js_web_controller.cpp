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

#include "frameworks/bridge/declarative_frontend/jsview/js_web_controller.h"

#include "base/utils/linear_map.h"
#include "base/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {
void JSWebController::JSBind(BindingTarget globalObj)
{
    JSClass<JSWebController>::Declare("WebController");
    JSClass<JSWebController>::CustomMethod("loadUrl", &JSWebController::LoadUrl);
    JSClass<JSWebController>::CustomMethod("runJavaScript", &JSWebController::ExecuteTypeScript);
    JSClass<JSWebController>::CustomMethod("loadData", &JSWebController::LoadDataWithBaseUrl);
    JSClass<JSWebController>::CustomMethod("backward", &JSWebController::Backward);
    JSClass<JSWebController>::CustomMethod("forward", &JSWebController::Forward);
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
    if (webController_) {
        webController_->LoadUrl(url);
    }
}

void JSWebController::ExecuteTypeScript(const JSCallbackInfo& args)
{
    std::string jscode;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], jscode)) {
        return;
    }
    if (webController_) {
        webController_->ExecuteTypeScript(jscode);
    }
}

void JSWebController::LoadDataWithBaseUrl(const JSCallbackInfo& args)
{
    if (args.Length() >= 1 && args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);

        std::string baseUrl;
        if (!ConvertFromJSValue(obj->GetProperty("baseUrl"), baseUrl)) {
            return;
        }

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

        std::string historyUrl;
        if (!ConvertFromJSValue(obj->GetProperty("historyUrl"), historyUrl)) {
            return;
        }
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

} // namespace OHOS::Ace::Framework