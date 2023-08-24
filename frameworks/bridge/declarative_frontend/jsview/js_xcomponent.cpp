/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent.h"

#include "base/log/ace_scoring_log.h"
#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/js_xcomponent_controller.h"
#include "bridge/declarative_frontend/jsview/models/xcomponent_model_impl.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"

namespace OHOS::Ace {
namespace {
XComponentType ConvertToXComponentType(const std::string& type)
{
    if (type == "surface") {
        return XComponentType::SURFACE;
    }
    if (type == "component") {
        return XComponentType::COMPONENT;
    }
    LOGW("type: %{public}s is not valid, use 'surface' type as default", type.c_str());
    return XComponentType::SURFACE;
}
} // namespace

std::unique_ptr<XComponentModel> XComponentModel::instance_ = nullptr;
std::mutex XComponentModel::mutex_;

XComponentModel* XComponentModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::XComponentModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::XComponentModelNG());
            } else {
                instance_.reset(new Framework::XComponentModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSXComponent::JSBind(BindingTarget globalObj)
{
    JSClass<JSXComponent>::Declare("XComponent");
    JSClass<JSXComponent>::StaticMethod("create", &JSXComponent::Create);
    JSClass<JSXComponent>::StaticMethod("onLoad", &JSXComponent::JsOnLoad);
    JSClass<JSXComponent>::StaticMethod("onDestroy", &JSXComponent::JsOnDestroy);

    JSClass<JSXComponent>::StaticMethod("onAppear", &JSXComponent::OmitEvent);
    JSClass<JSXComponent>::StaticMethod("onDisAppear", &JSXComponent::OmitEvent);
    JSClass<JSXComponent>::StaticMethod("onTouch", &JSXComponent::OmitEvent);
    JSClass<JSXComponent>::StaticMethod("onClick", &JSXComponent::OmitEvent);
    JSClass<JSXComponent>::StaticMethod("onKeyEvent", &JSXComponent::OmitEvent);
    JSClass<JSXComponent>::StaticMethod("onMouse", &JSXComponent::OmitEvent);
    JSClass<JSXComponent>::StaticMethod("onHover", &JSXComponent::OmitEvent);
    JSClass<JSXComponent>::StaticMethod("onFocus", &JSXComponent::OmitEvent);
    JSClass<JSXComponent>::StaticMethod("onBlur", &JSXComponent::OmitEvent);

    JSClass<JSXComponent>::StaticMethod("backgroundColor", &JSXComponent::JsBackgroundColor);
    JSClass<JSXComponent>::StaticMethod("backgroundImage", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("backgroundImageSize", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("backgroundImagePosition", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("opacity", &JSXComponent::JsOpacity);
    JSClass<JSXComponent>::StaticMethod("blur", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("backdropBlur", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("grayscale", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("brightness", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("saturate", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("contrast", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("invert", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("sepia", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("hueRotate", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("colorBlend", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("sphericalEffect", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("lightUpEffect", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("pixelStretchEffect", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("linearGradientBlur", &JSXComponent::OmitAttribute);

    JSClass<JSXComponent>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSXComponent::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGI("xcomponent create error, info is invalid");
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto id = paramObject->GetProperty("id");
    if (!id->IsString()) {
        LOGI("xcomponent create error, id is invalid");
        return;
    }

    auto type = paramObject->GetProperty("type");
    auto libraryname = paramObject->GetProperty("libraryname");
    auto controllerObj = paramObject->GetProperty("controller");
    RefPtr<XComponentController> xcomponentController = nullptr;
    if (controllerObj->IsObject()) {
        auto* jsXComponentController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSXComponentController>();
        if (jsXComponentController) {
            XComponentClient::GetInstance().AddControllerToJSXComponentControllersMap(
                id->ToString(), jsXComponentController);
            xcomponentController = jsXComponentController->GetController();
        }
    }
    XComponentType xcomponentType = XComponentType::SURFACE;
    if (type->IsString()) {
        xcomponentType = ConvertToXComponentType(type->ToString());
    } else if (type->IsNumber()) {
        xcomponentType = static_cast<XComponentType>(type->ToNumber<int32_t>());
    }
    XComponentModel::GetInstance()->Create(
        id->ToString(), xcomponentType, libraryname->ToString(), xcomponentController);

    if (info.Length() > 1 && info[1]->IsString()) {
        auto soPath = info[1]->ToString();
        XComponentModel::GetInstance()->SetSoPath(soPath);
    }
}

void JSXComponent::JsOnLoad(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 argument.");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    auto onLoad = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const std::string& xcomponentId) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("XComponent.onLoad");
        std::vector<std::string> keys = { "load", xcomponentId };
        func->ExecuteNew(keys, "");
    };
    XComponentModel::GetInstance()->SetOnLoad(std::move(onLoad));
}

void JSXComponent::JsOnDestroy(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 argument.");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    auto onDestroy = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("XComponent.onDestroy");
        std::vector<std::string> keys = { "destroy" };
        func->Execute(keys, "");
    };
    XComponentModel::GetInstance()->SetOnDestroy(std::move(onDestroy));
}

void JSXComponent::JsBackgroundColor(const JSCallbackInfo& args)
{
    if (!XComponentModel::GetInstance()->IsTexture()) {
        LOGW("not support backgroundColor attribute");
        return;
    }
    JSViewAbstract::JsBackgroundColor(args);
}

void JSXComponent::JsOpacity(const JSCallbackInfo& args)
{
    if (!XComponentModel::GetInstance()->IsTexture()) {
        LOGW("not support opacity attribute");
        return;
    }
    JSViewAbstract::JsOpacity(args);
}

void JSXComponent::OmitEvent(const JSCallbackInfo& /*args*/)
{
    LOGW("This event is omitted, please use apis of native_xcomponent instead");
}

void JSXComponent::OmitAttribute(const JSCallbackInfo& /* args */)
{
    LOGW("This attribute is omitted.");
}
} // namespace OHOS::Ace::Framework
