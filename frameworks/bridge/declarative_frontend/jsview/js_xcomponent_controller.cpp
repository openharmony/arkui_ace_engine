/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent_controller.h"

#include "interfaces/inner_api/ace/ai/image_analyzer.h"
#include "js_utils.h"

#include "base/error/error_code.h"
#include "base/memory/referenced.h"
#include "base/utils/linear_map.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "core/components/xcomponent/xcomponent_controller_impl.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_controller_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {
struct XComponentAsyncCxt {
    napi_env env = nullptr;
    napi_deferred deferred = nullptr;
};
namespace {
bool ParseSurfaceRectParam(const JSRef<JSVal>& jsValue, CalcDimension& result)
{
    if (!jsValue->IsNumber()) {
        return false;
    }
    result = CalcDimension(jsValue->ToNumber<double>(), DimensionUnit::PX);
    return true;
}

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

void HandleDeferred(const shared_ptr<XComponentAsyncCxt>& asyncCtx, ImageAnalyzerState state)
{
    auto env = asyncCtx->env;
    CHECK_NULL_VOID(env);
    auto deferred = asyncCtx->deferred;
    CHECK_NULL_VOID(deferred);

    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }

    napi_value result = nullptr;
    switch (state) {
        case ImageAnalyzerState::UNSUPPORTED:
            result = CreateErrorValue(env, ERROR_CODE_AI_ANALYSIS_UNSUPPORTED);
            napi_reject_deferred(env, deferred, result);
            break;
        case ImageAnalyzerState::ONGOING:
            result = CreateErrorValue(env, ERROR_CODE_AI_ANALYSIS_IS_ONGOING);
            napi_reject_deferred(env, deferred, result);
            break;
        case ImageAnalyzerState::STOPPED:
            result = CreateErrorValue(env, ERROR_CODE_AI_ANALYSIS_IS_STOPPED);
            napi_reject_deferred(env, deferred, result);
            break;
        case ImageAnalyzerState::FINISHED:
            napi_get_null(env, &result);
            napi_resolve_deferred(env, deferred, result);
            break;
        default:
            break;
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
void JSXComponentController::JSBind(BindingTarget globalObj)
{
    JSClass<JSXComponentController>::Declare("XComponentController");
    JSClass<JSXComponentController>::CustomMethod("getXComponentSurfaceId", &JSXComponentController::GetSurfaceId);
    JSClass<JSXComponentController>::CustomMethod(
        "getXComponentContext", &JSXComponentController::GetXComponentContext);
    JSClass<JSXComponentController>::CustomMethod(
        "setXComponentSurfaceSize", &JSXComponentController::SetSurfaceConfig);
    JSClass<JSXComponentController>::CustomMethod(
        "getXComponentSurfaceRect", &JSXComponentController::GetXComponentSurfaceRect);
    JSClass<JSXComponentController>::CustomMethod(
        "setXComponentSurfaceRect", &JSXComponentController::SetXComponentSurfaceRect);
    JSClass<JSXComponentController>::CustomMethod("startImageAnalyzer", &JSXComponentController::StartImageAnalyzer);
    JSClass<JSXComponentController>::CustomMethod("stopImageAnalyzer", &JSXComponentController::StopImageAnalyzer);
    JSClass<JSXComponentController>::CustomMethod(
        "setXComponentSurfaceRotation", &JSXComponentController::SetXComponentSurfaceRotation);
    JSClass<JSXComponentController>::CustomMethod(
        "getXComponentSurfaceRotation", &JSXComponentController::GetXComponentSurfaceRotation);
    JSClass<JSXComponentController>::Bind(
        globalObj, JSXComponentController::Constructor, JSXComponentController::Destructor);
}

void JSXComponentController::Constructor(const JSCallbackInfo& args)
{
    auto xcomponentController = Referenced::MakeRefPtr<JSXComponentController>();
    xcomponentController->IncRefCount();
    std::shared_ptr<InnerXComponentController> controller;
#ifdef NG_BUILD
    controller = std::make_shared<NG::XComponentControllerNG>();
#else
    if (Container::IsCurrentUseNewPipeline()) {
        controller = std::make_shared<NG::XComponentControllerNG>();
    } else {
        controller = std::make_shared<XComponentControllerImpl>();
    }
#endif
    xcomponentController->SetController(controller);
    args.SetReturnValue(Referenced::RawPtr(xcomponentController));
}

void JSXComponentController::Destructor(JSXComponentController* xcomponentController)
{
    if (xcomponentController) {
        xcomponentController->DecRefCount();
    }
}

void JSXComponentController::GetSurfaceId(const JSCallbackInfo& args)
{
    if (xcomponentController_) {
        auto surfaceId = xcomponentController_->GetSurfaceId();
        auto returnValue = JSVal(ToJSValue(surfaceId));
        auto returnPtr = JSRef<JSVal>::Make(returnValue);
        args.SetReturnValue(returnPtr);
    }
}

void JSXComponentController::SetSurfaceConfig(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        LOGW("Invalid params");
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    uint32_t surfaceWidth;
    uint32_t surfaceHeight;
    if (!ConvertFromJSValue(obj->GetProperty("surfaceWidth"), surfaceWidth) ||
        !ConvertFromJSValue(obj->GetProperty("surfaceHeight"), surfaceHeight)) {
        LOGW("Failed to parse param 'surfaceWidth' or 'surfaceHeight'");
        return;
    }

    if (xcomponentController_) {
        xcomponentController_->ConfigSurface(surfaceWidth, surfaceHeight);
    }
}

void JSXComponentController::GetXComponentSurfaceRect(const JSCallbackInfo& args)
{
    if (!xcomponentController_) {
        return;
    }
    auto retObj = JSRef<JSObject>::New();
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    xcomponentController_->GetSurfaceOffset(offsetX, offsetY);
    xcomponentController_->GetSurfaceSize(width, height);
    retObj->SetProperty("offsetX", offsetX);
    retObj->SetProperty("offsetY", offsetY);
    retObj->SetProperty("surfaceWidth", width);
    retObj->SetProperty("surfaceHeight", height);
    args.SetReturnValue(retObj);
}

void JSXComponentController::SetXComponentSurfaceRect(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }
    if (!xcomponentController_) {
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    auto jsSurfaceWidth = obj->GetProperty("surfaceWidth");
    CalcDimension surfaceWidth;
    if (!ParseSurfaceRectParam(jsSurfaceWidth, surfaceWidth) || !surfaceWidth.IsValid()) {
        return;
    }
    auto jsSurfaceHeight = obj->GetProperty("surfaceHeight");
    CalcDimension surfaceHeight;
    if (!ParseSurfaceRectParam(jsSurfaceHeight, surfaceHeight) || !surfaceHeight.IsValid()) {
        return;
    }
    xcomponentController_->SetIdealSurfaceWidth(static_cast<float>(surfaceWidth.ConvertToPx()));
    xcomponentController_->SetIdealSurfaceHeight(static_cast<float>(surfaceHeight.ConvertToPx()));

    auto jsOffsetX = obj->GetProperty("offsetX");
    CalcDimension offsetX;
    if (ParseSurfaceRectParam(jsOffsetX, offsetX)) {
        xcomponentController_->SetIdealSurfaceOffsetX(static_cast<float>(offsetX.ConvertToPx()));
    } else {
        xcomponentController_->ClearIdealSurfaceOffset(true);
    }
    auto jsOffsetY = obj->GetProperty("offsetY");
    CalcDimension offsetY;
    if (ParseSurfaceRectParam(jsOffsetY, offsetY)) {
        xcomponentController_->SetIdealSurfaceOffsetY(static_cast<float>(offsetY.ConvertToPx()));
    } else {
        xcomponentController_->ClearIdealSurfaceOffset(false);
    }

    xcomponentController_->UpdateSurfaceBounds();
}

void JSXComponentController::StartImageAnalyzer(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    auto env = reinterpret_cast<napi_env>(nativeEngine);

    auto asyncCtx = std::make_shared<XComponentAsyncCxt>();
    asyncCtx->env = env;
    napi_value promise = nullptr;
    napi_create_promise(env, &asyncCtx->deferred, &promise);
    if (args.Length() < 1 || !args[0]->IsObject()) {
        ReturnPromise(args, promise);
        return;
    }

    ScopeRAII scopeRaii(env);
    panda::Local<JsiValue> value = args[0].Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;
    napi_value configNativeValue = nativeEngine->ValueToNapiValue(valueWrapper);
    if (isImageAnalyzing_) {
        napi_value result = CreateErrorValue(env, ERROR_CODE_AI_ANALYSIS_IS_ONGOING);
        napi_reject_deferred(env, asyncCtx->deferred, result);
        ReturnPromise(args, promise);
        return;
    }

    OnAnalyzedCallback onAnalyzed_ = [asyncCtx, weakCtx = WeakClaim(this)](ImageAnalyzerState state) {
        CHECK_NULL_VOID(asyncCtx);
        HandleDeferred(asyncCtx, state);
        auto ctx = weakCtx.Upgrade();
        CHECK_NULL_VOID(ctx);
        ctx->isImageAnalyzing_ = false;
    };
    isImageAnalyzing_ = true;
    CHECK_NULL_VOID(xcomponentController_);
    xcomponentController_->StartImageAnalyzer(configNativeValue, onAnalyzed_);
    ReturnPromise(args, promise);
}

void JSXComponentController::StopImageAnalyzer(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(xcomponentController_);
    xcomponentController_->StopImageAnalyzer();
}

void JSXComponentController::SetXComponentSurfaceRotation(const JSCallbackInfo& args)
{
    if (!args[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    bool lock = false;
    ConvertFromJSValue(obj->GetProperty("lock"), lock);
    CHECK_NULL_VOID(xcomponentController_);
    xcomponentController_->SetSurfaceRotation(lock);
}

void JSXComponentController::GetXComponentSurfaceRotation(const JSCallbackInfo& args)
{
    auto retObj = JSRef<JSObject>::New();
    CHECK_NULL_VOID(xcomponentController_);
    bool lock = xcomponentController_->GetSurfaceRotation();
    retObj->SetProperty("lock", lock);
    args.SetReturnValue(retObj);
}
} // namespace OHOS::Ace::Framework
