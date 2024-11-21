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

#include "bridge/declarative_frontend/jsview/js_tabs_controller.h"

#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {
namespace {

#ifndef NG_BUILD
// dismiss unused warning in NG_BUILD
int32_t g_tabControllerId = 0;
#endif

struct TabsControllerAsyncContext {
    napi_env env = nullptr;
    napi_deferred deferred = nullptr;
};

napi_value CreateErrorValue(napi_env env, int32_t errCode, const std::string& errMsg = "")
{
    napi_value code = nullptr;
    std::string codeStr = std::to_string(errCode);
    napi_create_string_utf8(env, codeStr.c_str(), codeStr.length(), &code);
    napi_value msg = nullptr;
    napi_create_string_utf8(env, errMsg.c_str(), errMsg.length(), &msg);
    napi_value error = nullptr;
    napi_create_error(env, code, msg, &error);
    return error;
}

void HandleDeferred(const shared_ptr<TabsControllerAsyncContext>& asyncContext, int32_t errorCode, std::string message)
{
    auto env = asyncContext->env;
    CHECK_NULL_VOID(env);
    auto deferred = asyncContext->deferred;
    CHECK_NULL_VOID(deferred);

    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }

    napi_value result = nullptr;
    if (errorCode == ERROR_CODE_NO_ERROR) {
        napi_get_null(env, &result);
        napi_resolve_deferred(env, deferred, result);
    } else {
        result = CreateErrorValue(env, errorCode, message);
        napi_reject_deferred(env, deferred, result);
    }
    napi_close_handle_scope(env, scope);
}

void ReturnPromise(const JSCallbackInfo& info, napi_value result)
{
    CHECK_NULL_VOID(result);
    auto jsPromise = JsConverter::ConvertNapiValueToJsVal(result);
    if (!jsPromise->IsObject()) {
        return;
    }
    info.SetReturnValue(JSRef<JSObject>::Cast(jsPromise));
}
} // namespace

JSTabsController::JSTabsController()
{
    controller_ = CreateController();
    tabsController_ = MakeRefPtr<NG::TabsControllerNG>();
}

void JSTabsController::JSBind(BindingTarget globalObj)
{
    JSClass<JSTabsController>::Declare("TabsController");
    JSClass<JSTabsController>::Method("changeIndex", &JSTabsController::ChangeIndex);
    JSClass<JSTabsController>::CustomMethod("preloadItems", &JSTabsController::PreloadItems);
    JSClass<JSTabsController>::CustomMethod("setTabBarTranslate", &JSTabsController::SetTabBarTranslate);
    JSClass<JSTabsController>::CustomMethod("setTabBarOpacity", &JSTabsController::SetTabBarOpacity);
    JSClass<JSTabsController>::Bind(globalObj, JSTabsController::Constructor, JSTabsController::Destructor);
}

void JSTabsController::Constructor(const JSCallbackInfo& args)
{
    auto jsCalendarController = Referenced::MakeRefPtr<JSTabsController>();
    jsCalendarController->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(jsCalendarController));
}

void JSTabsController::Destructor(JSTabsController* controller)
{
    if (controller != nullptr) {
        controller->DecRefCount();
    }
}

RefPtr<TabController> JSTabsController::CreateController()
{
#ifdef NG_BUILD
    return nullptr;
#else
    return TabController::GetController(++g_tabControllerId);
#endif
}

void JSTabsController::ChangeIndex(int32_t index)
{
    ContainerScope scope(instanceId_);
    if (tabsController_) {
        const auto& updateCubicCurveCallback = tabsController_->GetUpdateCubicCurveCallback();
        if (updateCubicCurveCallback != nullptr) {
            updateCubicCurveCallback();
        }
        tabsController_->SwipeTo(index);
    }

#ifndef NG_BUILD
    if (controller_) {
        controller_->SetIndexByController(index, false);
    }
#endif
}

void JSTabsController::PreloadItems(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    auto asyncContext = std::make_shared<TabsControllerAsyncContext>();
    asyncContext->env = env;
    napi_value promise = nullptr;
    napi_create_promise(env, &asyncContext->deferred, &promise);
    if (!tabsController_) {
        ReturnPromise(args, promise);
        return;
    }

    ScopeRAII scopeRaii(env);
    std::set<int32_t> indexSet;
    if (args.Length() > 0 && args[0]->IsArray()) {
        auto indexArray = JSRef<JSArray>::Cast(args[0]);
        size_t size = indexArray->Length();
        for (size_t i = 0; i < size; i++) {
            int32_t index = -1;
            JSViewAbstract::ParseJsInt32(indexArray->GetValueAt(i), index);
            indexSet.emplace(index);
        }
    }

    auto onPreloadFinish = [asyncContext](int32_t errorCode, std::string message) {
        CHECK_NULL_VOID(asyncContext);
        HandleDeferred(asyncContext, errorCode, message);
    };
    tabsController_->SetPreloadFinishCallback(onPreloadFinish);
    tabsController_->PreloadItems(indexSet);
    ReturnPromise(args, promise);
}

void JSTabsController::SetTabBarTranslate(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(tabsController_);
    if (args.Length() <= 0) {
        return;
    }
    auto translate = args[0];
    if (translate->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(translate);
        if (jsObj->HasProperty(static_cast<int32_t>(ArkUIIndex::X)) ||
            jsObj->HasProperty(static_cast<int32_t>(ArkUIIndex::Y)) ||
            jsObj->HasProperty(static_cast<int32_t>(ArkUIIndex::Z))) {
            CalcDimension translateX;
            CalcDimension translateY;
            CalcDimension translateZ;
            JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::X)), translateX);
            JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::Y)), translateY);
            JSViewAbstract::ParseJsDimensionVp(jsObj->GetProperty(static_cast<int32_t>(ArkUIIndex::Z)), translateZ);
            auto options = NG::TranslateOptions(translateX, translateY, translateZ);
            tabsController_->SetTabBarTranslate(options);
            return;
        }
    }
    CalcDimension value;
    if (JSViewAbstract::ParseJsDimensionVp(translate, value)) {
        auto options = NG::TranslateOptions(value, value, value);
        tabsController_->SetTabBarTranslate(options);
    } else {
        auto options = NG::TranslateOptions(0.0f, 0.0f, 0.0f);
        tabsController_->SetTabBarTranslate(options);
    }
}

void JSTabsController::SetTabBarOpacity(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(tabsController_);
    if (args.Length() <= 0) {
        return;
    }
    double opacity = 0.0;
    if (JSViewAbstract::ParseJsDouble(args[0], opacity)) {
        opacity = std::clamp(opacity, 0.0, 1.0);
        tabsController_->SetTabBarOpacity(opacity);
    } else {
        tabsController_->SetTabBarOpacity(1.0f);
    }
}

} // namespace OHOS::Ace::Framework
