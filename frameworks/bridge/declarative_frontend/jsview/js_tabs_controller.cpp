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

#include "base/log/event_report.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "bridge/declarative_frontend/jsview/js_tabs_controller_binding.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/common/dynamic_module_helper.h"
#ifndef NG_BUILD
#include "compatible/components/tab_bar/modifier/tab_modifier_api.h"
#endif

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

#ifndef NG_BUILD
const ArkUIInnerTabsModifier* GetTabsInnerModifier()
{
    static const ArkUIInnerTabsModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("tabs");
        CHECK_NULL_RETURN(loader, nullptr);
        cachedModifier = reinterpret_cast<const ArkUIInnerTabsModifier*>(loader->GetCustomModifier());
    }
    return cachedModifier;
}
#endif

const NG::NodeModifier::ArkUITabsControllerModifier* GetTabsControllerModifier()
{
    static const NG::NodeModifier::ArkUITabsControllerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Tabs");
        if (module == nullptr) {
            LOGF_ABORT("Can't find tabs dynamic module");
        }
        cachedModifier = reinterpret_cast<const NG::NodeModifier::ArkUITabsControllerModifier*>(
            module->GetCustomModifier("tabsController"));
    }
    return cachedModifier;
}
} // namespace

JSTabsController::JSTabsController()
{
    controller_ = CreateController();
}

void JSTabsControllerBinding::JSBind(BindingTarget globalObj)
{
    JSClass<JSTabsController>::Declare("TabsController");
    JSClass<JSTabsController>::Method("changeIndex", &JSTabsController::ChangeIndex);
    JSClass<JSTabsController>::CustomMethod("preloadItems", &JSTabsControllerBinding::PreloadItems);
    JSClass<JSTabsController>::CustomMethod("setTabBarTranslate", &JSTabsControllerBinding::SetTabBarTranslate);
    JSClass<JSTabsController>::CustomMethod("setTabBarOpacity", &JSTabsControllerBinding::SetTabBarOpacity);
    JSClass<JSTabsController>::Bind(globalObj, JSTabsControllerBinding::Constructor, JSTabsController::Destructor);
}

void JSTabsControllerBinding::Constructor(const JSCallbackInfo& args)
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

RefPtr<AceType> JSTabsController::CreateController()
{
#ifdef NG_BUILD
    return nullptr;
#else
    if (!Container::IsCurrentUseNewPipeline()) {
        if (auto modifier = GetTabsInnerModifier()) {
            return modifier->getController(++g_tabControllerId);
        }
    }
    return nullptr;
#endif
}

void JSTabsController::ChangeIndex(int32_t index)
{
    ContainerScope scope(instanceId_);
    if (auto* modifier = GetTabsControllerModifier()) {
        modifier->changeIndex(controllerHandle_, index);
    }

#ifndef NG_BUILD
    if (controller_) {
        if (auto modifier = GetTabsInnerModifier()) {
            modifier->setIndexByController(controller_, index, false);
        }
    }
#endif
}

void JSTabsControllerBinding::PreloadItems(const JSCallbackInfo& args)
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
    auto* modifier = GetTabsControllerModifier();
    if (!modifier || !controllerHandle_) {
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
    modifier->setPreloadFinishCallback(controllerHandle_, onPreloadFinish);
    std::vector<int32_t> indexVec(indexSet.begin(), indexSet.end());
    modifier->preloadItems(controllerHandle_, indexVec.data(), static_cast<int32_t>(indexVec.size()));
    ReturnPromise(args, promise);
}

void JSTabsControllerBinding::SetTabBarTranslate(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    auto* modifier = GetTabsControllerModifier();
    if (!modifier || !controllerHandle_) {
        return;
    }

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
            modifier->setTabBarTranslate(
                controllerHandle_, translateX.Value(), translateY.Value(), translateZ.Value(),
                static_cast<int32_t>(translateX.Unit()), static_cast<int32_t>(translateY.Unit()),
                static_cast<int32_t>(translateZ.Unit()));
            return;
        }
    }
    CalcDimension value;
    if (JSViewAbstract::ParseJsDimensionVp(translate, value)) {
        modifier->setTabBarTranslate(controllerHandle_, value.Value(), value.Value(), value.Value(),
            static_cast<int32_t>(value.Unit()), static_cast<int32_t>(value.Unit()),
            static_cast<int32_t>(value.Unit()));
    } else {
        modifier->setTabBarTranslate(controllerHandle_, 0.0, 0.0, 0.0,
            static_cast<int32_t>(DimensionUnit::VP), static_cast<int32_t>(DimensionUnit::VP),
            static_cast<int32_t>(DimensionUnit::VP));
    }
}

void JSTabsControllerBinding::SetTabBarOpacity(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    auto* modifier = GetTabsControllerModifier();
    if (!modifier || !controllerHandle_) {
        return;
    }

    if (args.Length() <= 0) {
        return;
    }
    double opacity = 0.0;
    if (JSViewAbstract::ParseJsDouble(args[0], opacity)) {
        opacity = std::clamp(opacity, 0.0, 1.0);
        modifier->setTabBarOpacity(controllerHandle_, opacity);
    } else {
        modifier->setTabBarOpacity(controllerHandle_, 1.0);
    }
}

void JSTabsController::SetControllerHandle(const RefPtr<AceType>& handle)
{
    auto* modifier = GetTabsControllerModifier();
    if (modifier && controllerHandle_) {
        modifier->startShowTabBar(controllerHandle_, 0);
        modifier->setOnChangeImpl(controllerHandle_, std::function<void(int32_t)>());
    }
    controllerHandle_ = handle;
    if (modifier && onChangeImpl_ && controllerHandle_) {
        modifier->setOnChangeImpl(controllerHandle_, onChangeImpl_);
    }
}

void JSTabsController::SetOnChangeImpl(const std::function<void(int32_t)>& onChangeImpl)
{
    onChangeImpl_ = onChangeImpl;
    if (auto* modifier = GetTabsControllerModifier()) {
        modifier->setOnChangeImpl(controllerHandle_, onChangeImpl);
    }
}

void JSTabsController::StartShowTabBar(int32_t delay)
{
    if (auto* modifier = GetTabsControllerModifier()) {
        modifier->startShowTabBar(controllerHandle_, delay);
    }
}

void JSTabsController::CancelShowTabBar()
{
    if (auto* modifier = GetTabsControllerModifier()) {
        modifier->cancelShowTabBar(controllerHandle_);
    }
}

void JSTabsController::UpdateTabBarHiddenOffset(float offset)
{
    if (auto* modifier = GetTabsControllerModifier()) {
        modifier->updateTabBarHiddenOffset(controllerHandle_, static_cast<double>(offset));
    }
}

} // namespace OHOS::Ace::Framework
