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

#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent_controller_binding.h"

#include "canvas_napi/js_canvas.h"
#include "interfaces/inner_api/ace/ai/image_analyzer.h"
#include "js_utils.h"

#include "base/error/error_code.h"
#include "base/memory/referenced.h"
#include "base/utils/linear_map.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "core/common/statistic_event_reporter.h"
#include "core/components/xcomponent/xcomponent_controller_impl.h"
#include "core/interfaces/native/node/node_xcomponent_modifier.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {
extern "C" ACE_FORCE_EXPORT void OHOS_ACE_GetXComponentController(void* jsController, void* controller)
{
    auto* jsXComponentController = static_cast<Framework::JSXComponentController*>(jsController);
    CHECK_NULL_VOID(jsXComponentController);
    auto xComponentController = reinterpret_cast<std::shared_ptr<InnerXComponentController>*>(controller);
    CHECK_NULL_VOID(xComponentController);
    *xComponentController = jsXComponentController->GetController();
}

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

void SendStatisticEvent(StatisticEventType type)
{
    auto context = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    auto StatisticEventReporter = context->GetStatisticEventReporter();
    CHECK_NULL_VOID(StatisticEventReporter);
    StatisticEventReporter->SendEvent(type);
}
} // namespace

void JSXComponentController::Destructor(JSXComponentController* xcomponentController)
{
    CHECK_NULL_VOID(xcomponentController);
    xcomponentController->DecRefCount();
}

void JSXComponentControllerBinding::JSBind(BindingTarget globalObj)
{
    JSClass<JSXComponentController>::Declare("XComponentController");
    JSClass<JSXComponentController>::CustomMethod(
        "getXComponentSurfaceId", &JSXComponentControllerBinding::GetSurfaceId);
    JSClass<JSXComponentController>::CustomMethod(
        "getXComponentContext", &JSXComponentControllerBinding::GetXComponentContext);
    JSClass<JSXComponentController>::CustomMethod(
        "setXComponentSurfaceSize", &JSXComponentControllerBinding::SetSurfaceConfig);
    JSClass<JSXComponentController>::CustomMethod(
        "getXComponentSurfaceRect", &JSXComponentControllerBinding::GetXComponentSurfaceRect);
    JSClass<JSXComponentController>::CustomMethod(
        "setXComponentSurfaceRect", &JSXComponentControllerBinding::SetXComponentSurfaceRect);
    JSClass<JSXComponentController>::CustomMethod(
        "startImageAnalyzer", &JSXComponentControllerBinding::StartImageAnalyzer);
    JSClass<JSXComponentController>::CustomMethod(
        "stopImageAnalyzer", &JSXComponentControllerBinding::StopImageAnalyzer);
    JSClass<JSXComponentController>::CustomMethod(
        "setXComponentSurfaceRotation", &JSXComponentControllerBinding::SetXComponentSurfaceRotation);
    JSClass<JSXComponentController>::CustomMethod(
        "getXComponentSurfaceRotation", &JSXComponentControllerBinding::GetXComponentSurfaceRotation);
    JSClass<JSXComponentController>::CustomMethod("lockCanvas", &JSXComponentControllerBinding::LockCanvas);
    JSClass<JSXComponentController>::CustomMethod(
        "unlockCanvasAndPost", &JSXComponentControllerBinding::UnlockCanvasAndPost);
    JSClass<JSXComponentController>::CustomMethod(
        "setXComponentSurfaceConfig", &JSXComponentControllerBinding::SetXComponentSurfaceConfig);
    JSClass<JSXComponentController>::Bind(
        globalObj, JSXComponentControllerBinding::Constructor, JSXComponentController::Destructor);
}

void JSXComponentControllerBinding::Constructor(const JSCallbackInfo& args)
{
    auto xcomponentController = Referenced::MakeRefPtr<JSXComponentControllerBinding>();
    xcomponentController->IncRefCount();
    std::shared_ptr<InnerXComponentController> controller;
#ifdef NG_BUILD
    auto xcomponentModifier = NG::NodeModifier::GetXComponentCustomModifier();
    if (xcomponentModifier && xcomponentModifier->createController) {
        xcomponentModifier->createController(&controller);
    }
#else
    if (Container::IsCurrentUseNewPipeline()) {
        auto xcomponentModifier = NG::NodeModifier::GetXComponentCustomModifier();
        if (xcomponentModifier && xcomponentModifier->createController) {
            xcomponentModifier->createController(&controller);
        }
    } else {
        controller = std::make_shared<XComponentControllerImpl>();
    }
#endif
    xcomponentController->SetController(controller);
    args.SetReturnValue(Referenced::RawPtr(xcomponentController));
}

void JSXComponentControllerBinding::GetSurfaceId(const JSCallbackInfo& args)
{
    auto innerCtrl = GetController();
    CHECK_NULL_VOID(innerCtrl);
    auto surfaceId = innerCtrl->GetSurfaceId();
    auto returnValue = JSVal(ToJSValue(surfaceId));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "Controller GetSurfaceId:%{public}s", surfaceId.c_str());
    args.SetReturnValue(returnPtr);
}

void JSXComponentControllerBinding::SetSurfaceConfig(const JSCallbackInfo& args)
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
    SendStatisticEvent(StatisticEventType::XCOMPONENT_SET_SURFACE_SIZE);
    auto innerCtrl = GetController();
    CHECK_NULL_VOID(innerCtrl);
    innerCtrl->ConfigSurface(surfaceWidth, surfaceHeight);
}

void JSXComponentControllerBinding::GetXComponentSurfaceRect(const JSCallbackInfo& args)
{
    auto innerCtrl = GetController();
    CHECK_NULL_VOID(innerCtrl);
    auto retObj = JSRef<JSObject>::New();
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    innerCtrl->GetSurfaceOffset(offsetX, offsetY);
    innerCtrl->GetSurfaceSize(width, height);
    retObj->SetProperty("offsetX", offsetX);
    retObj->SetProperty("offsetY", offsetY);
    retObj->SetProperty("surfaceWidth", width);
    retObj->SetProperty("surfaceHeight", height);
    args.SetReturnValue(retObj);
}

void JSXComponentControllerBinding::SetXComponentSurfaceRect(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }
    auto innerCtrl = GetController();
    CHECK_NULL_VOID(innerCtrl);

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
    innerCtrl->SetIdealSurfaceWidth(static_cast<float>(surfaceWidth.ConvertToPx()));
    innerCtrl->SetIdealSurfaceHeight(static_cast<float>(surfaceHeight.ConvertToPx()));

    auto jsOffsetX = obj->GetProperty("offsetX");
    CalcDimension offsetX;
    if (ParseSurfaceRectParam(jsOffsetX, offsetX)) {
        innerCtrl->SetIdealSurfaceOffsetX(static_cast<float>(offsetX.ConvertToPx()));
    } else {
        innerCtrl->ClearIdealSurfaceOffset(true);
    }
    auto jsOffsetY = obj->GetProperty("offsetY");
    CalcDimension offsetY;
    if (ParseSurfaceRectParam(jsOffsetY, offsetY)) {
        innerCtrl->SetIdealSurfaceOffsetY(static_cast<float>(offsetY.ConvertToPx()));
    } else {
        innerCtrl->ClearIdealSurfaceOffset(false);
    }

    innerCtrl->UpdateSurfaceBounds();
}

void JSXComponentControllerBinding::StartImageAnalyzer(const JSCallbackInfo& args)
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
    auto innerCtrl = GetController();
    CHECK_NULL_VOID(innerCtrl);
    innerCtrl->StartImageAnalyzer(configNativeValue, onAnalyzed_);
    ReturnPromise(args, promise);
}

void JSXComponentControllerBinding::StopImageAnalyzer(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    auto innerCtrl = GetController();
    CHECK_NULL_VOID(innerCtrl);
    innerCtrl->StopImageAnalyzer();
}

void JSXComponentControllerBinding::SetXComponentSurfaceRotation(const JSCallbackInfo& args)
{
    if (!args[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    bool lock = false;
    ConvertFromJSValue(obj->GetProperty("lock"), lock);
    auto innerCtrl = GetController();
    CHECK_NULL_VOID(innerCtrl);
    innerCtrl->SetSurfaceRotation(lock);
}

void JSXComponentControllerBinding::GetXComponentSurfaceRotation(const JSCallbackInfo& args)
{
    auto retObj = JSRef<JSObject>::New();
    auto innerCtrl = GetController();
    CHECK_NULL_VOID(innerCtrl);
    bool lock = innerCtrl->GetSurfaceRotation();
    retObj->SetProperty("lock", lock);
    args.SetReturnValue(retObj);
}

void JSXComponentControllerBinding::LockCanvas(const JSCallbackInfo& args)
{
    auto innerCtrl = GetController();
    if (innerCtrl == nullptr) {
        args.SetReturnValue(JSVal::Null());
        return;
    }
    auto rsCanvas = innerCtrl->LockCanvas();
    if (rsCanvas == nullptr) {
        args.SetReturnValue(JSVal::Null());
        return;
    }
    auto engine = EngineHelper::GetCurrentEngine();
    if (engine == nullptr) {
        args.SetReturnValue(JSVal::Null());
        return;
    }
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    ScopeRAII scope(env);
    auto jsCanvas = OHOS::Rosen::Drawing::JsCanvas::CreateJsCanvas(env, rsCanvas);
    JSRef<JSVal> jsCanvasVal = JsConverter::ConvertNapiValueToJsVal(jsCanvas);
    args.SetReturnValue(jsCanvasVal);
}

void JSXComponentControllerBinding::UnlockCanvasAndPost(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    ScopeRAII scope(env);
    auto jsCanvas = JsConverter::ConvertJsValToNapiValue(args[0]);
    OHOS::Rosen::Drawing::JsCanvas* unwrapCanvas = nullptr;
    napi_unwrap(env, jsCanvas, reinterpret_cast<void**>(&unwrapCanvas));
    CHECK_NULL_VOID(unwrapCanvas);
    auto rsCanvas = unwrapCanvas->GetCanvas();
    auto innerCtrl = GetController();
    CHECK_NULL_VOID(innerCtrl);
    innerCtrl->UnlockCanvasAndPost(rsCanvas);
}

void JSXComponentControllerBinding::SetXComponentSurfaceConfig(const JSCallbackInfo& args)
{
    if (!args[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    bool isOpaque = false;
    ConvertFromJSValue(obj->GetProperty("isOpaque"), isOpaque);
    auto innerCtrl = GetController();
    CHECK_NULL_VOID(innerCtrl);
    innerCtrl->SetSurfaceConfig(isOpaque);
}
} // namespace OHOS::Ace::Framework
