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
    swiperController_ = MakeRefPtr<SwiperController>();
}

void JSTabsController::JSBind(BindingTarget globalObj)
{
    JSClass<JSTabsController>::Declare("TabsController");
    JSClass<JSTabsController>::Method("changeIndex", &JSTabsController::ChangeIndex);
    JSClass<JSTabsController>::CustomMethod("preloadItems", &JSTabsController::PreloadItems);
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
    if (swiperController_) {
        const auto& updateCubicCurveCallback = swiperController_->GetUpdateCubicCurveCallback();
        if (updateCubicCurveCallback != nullptr) {
            updateCubicCurveCallback();
        }
        swiperController_->SwipeTo(index);
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
    if (!swiperController_) {
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
    swiperController_->SetPreloadFinishCallback(onPreloadFinish);
    swiperController_->PreloadItems(indexSet);
    ReturnPromise(args, promise);
}

} // namespace OHOS::Ace::Framework
