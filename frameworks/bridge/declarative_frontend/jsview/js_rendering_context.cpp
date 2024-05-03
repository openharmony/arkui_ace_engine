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

#include "js_rendering_context.h"

#include <cstdint>

#include "interfaces/inner_api/ace/ai/image_analyzer.h"
#include "js_native_api.h"
#include "js_native_api_types.h"
#include "js_utils.h"

#include "base/error/error_code.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_offscreen_rendering_context.h"
#include "bridge/declarative_frontend/jsview/models/canvas/canvas_rendering_context_2d_model_impl.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/canvas/canvas_rendering_context_2d_model_ng.h"

namespace OHOS::Ace {
struct CanvasAsyncCxt {
    napi_env env = nullptr;
    napi_deferred deferred = nullptr;
};
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

JSRenderingContext::JSRenderingContext()
{
#ifdef NG_BUILD
    renderingContext2DModel_ = AceType::MakeRefPtr<NG::CanvasRenderingContext2DModelNG>();
#else
    if (Container::IsCurrentUseNewPipeline()) {
        renderingContext2DModel_ = AceType::MakeRefPtr<NG::CanvasRenderingContext2DModelNG>();
    } else {
        renderingContext2DModel_ = AceType::MakeRefPtr<Framework::CanvasRenderingContext2DModelImpl>();
    }
#endif
}

void JSRenderingContext::JSBind(BindingTarget globalObj)
{
    // Define the class "CanvasRenderingContext2D"
    JSClass<JSRenderingContext>::Declare("CanvasRenderingContext2D");

    // Define all properties of the "CanvasRenderingContext2D"
    JSClass<JSRenderingContext>::CustomProperty(
        "width", &JSRenderingContext::JsGetWidth, &JSRenderingContext::JsSetWidth);
    JSClass<JSRenderingContext>::CustomProperty(
        "height", &JSRenderingContext::JsGetHeight, &JSRenderingContext::JsSetHeight);
    JSClass<JSRenderingContext>::CustomProperty(
        "filter", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetFilter);
    JSClass<JSRenderingContext>::CustomProperty(
        "direction", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetDirection);
    JSClass<JSRenderingContext>::CustomProperty(
        "fillStyle", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetFillStyle);
    JSClass<JSRenderingContext>::CustomProperty(
        "strokeStyle", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetStrokeStyle);
    JSClass<JSRenderingContext>::CustomProperty(
        "lineCap", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetLineCap);
    JSClass<JSRenderingContext>::CustomProperty(
        "lineJoin", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetLineJoin);
    JSClass<JSRenderingContext>::CustomProperty(
        "miterLimit", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetMiterLimit);
    JSClass<JSRenderingContext>::CustomProperty(
        "lineWidth", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetLineWidth);
    JSClass<JSRenderingContext>::CustomProperty("font", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetFont);
    JSClass<JSRenderingContext>::CustomProperty(
        "textAlign", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetTextAlign);
    JSClass<JSRenderingContext>::CustomProperty(
        "textBaseline", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetTextBaseline);
    JSClass<JSRenderingContext>::CustomProperty(
        "globalAlpha", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetGlobalAlpha);
    JSClass<JSRenderingContext>::CustomProperty(
        "globalCompositeOperation", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetGlobalCompositeOperation);
    JSClass<JSRenderingContext>::CustomProperty(
        "lineDashOffset", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetLineDashOffset);
    JSClass<JSRenderingContext>::CustomProperty(
        "shadowBlur", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetShadowBlur);
    JSClass<JSRenderingContext>::CustomProperty(
        "shadowColor", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetShadowColor);
    JSClass<JSRenderingContext>::CustomProperty(
        "shadowOffsetX", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetShadowOffsetX);
    JSClass<JSRenderingContext>::CustomProperty(
        "shadowOffsetY", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetShadowOffsetY);
    JSClass<JSRenderingContext>::CustomProperty(
        "imageSmoothingEnabled", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetImageSmoothingEnabled);
    JSClass<JSRenderingContext>::CustomProperty(
        "imageSmoothingQuality", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetImageSmoothingQuality);

    // Define all methods of the "CanvasRenderingContext2D"
    JSClass<JSRenderingContext>::CustomMethod("toDataURL", &JSCanvasRenderer::JsToDataUrl);
    JSClass<JSRenderingContext>::CustomMethod("createRadialGradient", &JSCanvasRenderer::JsCreateRadialGradient);
    JSClass<JSRenderingContext>::CustomMethod("fillRect", &JSCanvasRenderer::JsFillRect);
    JSClass<JSRenderingContext>::CustomMethod("strokeRect", &JSCanvasRenderer::JsStrokeRect);
    JSClass<JSRenderingContext>::CustomMethod("clearRect", &JSCanvasRenderer::JsClearRect);
    JSClass<JSRenderingContext>::CustomMethod("createLinearGradient", &JSCanvasRenderer::JsCreateLinearGradient);
    JSClass<JSRenderingContext>::CustomMethod("fillText", &JSCanvasRenderer::JsFillText);
    JSClass<JSRenderingContext>::CustomMethod("strokeText", &JSCanvasRenderer::JsStrokeText);
    JSClass<JSRenderingContext>::CustomMethod("measureText", &JSCanvasRenderer::JsMeasureText);
    JSClass<JSRenderingContext>::CustomMethod("moveTo", &JSCanvasRenderer::JsMoveTo);
    JSClass<JSRenderingContext>::CustomMethod("lineTo", &JSCanvasRenderer::JsLineTo);
    JSClass<JSRenderingContext>::CustomMethod("bezierCurveTo", &JSCanvasRenderer::JsBezierCurveTo);
    JSClass<JSRenderingContext>::CustomMethod("quadraticCurveTo", &JSCanvasRenderer::JsQuadraticCurveTo);
    JSClass<JSRenderingContext>::CustomMethod("arcTo", &JSCanvasRenderer::JsArcTo);
    JSClass<JSRenderingContext>::CustomMethod("arc", &JSCanvasRenderer::JsArc);
    JSClass<JSRenderingContext>::CustomMethod("ellipse", &JSCanvasRenderer::JsEllipse);
    JSClass<JSRenderingContext>::CustomMethod("fill", &JSCanvasRenderer::JsFill);
    JSClass<JSRenderingContext>::CustomMethod("stroke", &JSCanvasRenderer::JsStroke);
    JSClass<JSRenderingContext>::CustomMethod("clip", &JSCanvasRenderer::JsClip);
    JSClass<JSRenderingContext>::CustomMethod("rect", &JSCanvasRenderer::JsRect);
    JSClass<JSRenderingContext>::CustomMethod("beginPath", &JSCanvasRenderer::JsBeginPath);
    JSClass<JSRenderingContext>::CustomMethod("closePath", &JSCanvasRenderer::JsClosePath);
    JSClass<JSRenderingContext>::CustomMethod("restore", &JSCanvasRenderer::JsRestore);
    JSClass<JSRenderingContext>::CustomMethod("save", &JSCanvasRenderer::JsSave);
    JSClass<JSRenderingContext>::CustomMethod("rotate", &JSCanvasRenderer::JsRotate);
    JSClass<JSRenderingContext>::CustomMethod("scale", &JSCanvasRenderer::JsScale);
    JSClass<JSRenderingContext>::CustomMethod("getTransform", &JSCanvasRenderer::JsGetTransform);
    JSClass<JSRenderingContext>::CustomMethod("setTransform", &JSCanvasRenderer::JsSetTransform);
    JSClass<JSRenderingContext>::CustomMethod("resetTransform", &JSCanvasRenderer::JsResetTransform);
    JSClass<JSRenderingContext>::CustomMethod("transform", &JSCanvasRenderer::JsTransform);
    JSClass<JSRenderingContext>::CustomMethod("translate", &JSCanvasRenderer::JsTranslate);
    JSClass<JSRenderingContext>::CustomMethod("setLineDash", &JSCanvasRenderer::JsSetLineDash);
    JSClass<JSRenderingContext>::CustomMethod("getLineDash", &JSCanvasRenderer::JsGetLineDash);
    JSClass<JSRenderingContext>::CustomMethod("drawImage", &JSCanvasRenderer::JsDrawImage);
    JSClass<JSRenderingContext>::CustomMethod("createPattern", &JSCanvasRenderer::JsCreatePattern);
    JSClass<JSRenderingContext>::CustomMethod("createImageData", &JSCanvasRenderer::JsCreateImageData);
    JSClass<JSRenderingContext>::CustomMethod("putImageData", &JSCanvasRenderer::JsPutImageData);
    JSClass<JSRenderingContext>::CustomMethod("getImageData", &JSCanvasRenderer::JsGetImageData);
    JSClass<JSRenderingContext>::CustomMethod("getJsonData", &JSCanvasRenderer::JsGetJsonData);
    JSClass<JSRenderingContext>::CustomMethod("getPixelMap", &JSCanvasRenderer::JsGetPixelMap);
    JSClass<JSRenderingContext>::CustomMethod("setPixelMap", &JSCanvasRenderer::JsSetPixelMap);
    JSClass<JSRenderingContext>::CustomMethod("drawBitmapMesh", &JSCanvasRenderer::JsDrawBitmapMesh);
    JSClass<JSRenderingContext>::CustomMethod(
        "transferFromImageBitmap", &JSRenderingContext::JsTransferFromImageBitmap);
    JSClass<JSRenderingContext>::CustomMethod("createConicGradient", &JSCanvasRenderer::JsCreateConicGradient);
    JSClass<JSRenderingContext>::CustomMethod("saveLayer", &JSCanvasRenderer::JsSaveLayer);
    JSClass<JSRenderingContext>::CustomMethod("restoreLayer", &JSCanvasRenderer::JsRestoreLayer);
    JSClass<JSRenderingContext>::CustomMethod("reset", &JSCanvasRenderer::JsReset);
    JSClass<JSRenderingContext>::CustomMethod("startImageAnalyzer", &JSRenderingContext::JsStartImageAnalyzer);
    JSClass<JSRenderingContext>::CustomMethod("stopImageAnalyzer", &JSRenderingContext::JsStopImageAnalyzer);

    // Register the "CanvasRenderingContext2D" to the golbal object of the vm
    JSClass<JSRenderingContext>::Bind(globalObj, JSRenderingContext::Constructor, JSRenderingContext::Destructor);
}

void JSRenderingContext::Constructor(const JSCallbackInfo& args)
{
    auto jsRenderContext = Referenced::MakeRefPtr<JSRenderingContext>();
    jsRenderContext->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(jsRenderContext));

    auto* jsContextSetting = args.UnwrapArg<JSRenderingContextSettings>(0);
    CHECK_NULL_VOID(jsContextSetting);
    bool anti = jsContextSetting->GetAntialias();
    jsRenderContext->SetAnti(anti);

    int32_t unit = 0;
    if (args.GetInt32Arg(1, unit) && (static_cast<CanvasUnit>(unit) == CanvasUnit::PX)) {
        jsRenderContext->SetUnit(CanvasUnit::PX);
    }
}

void JSRenderingContext::Destructor(JSRenderingContext* controller)
{
    if (controller != nullptr) {
        controller->DecRefCount();
    }
}

void JSRenderingContext::JsGetWidth(const JSCallbackInfo& info)
{
    double width = 0.0;
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_VOID(canvasRenderingContext2DModel);
    canvasRenderingContext2DModel->GetWidth(canvasPattern_, width);
    double density = GetDensity();
    density = (density == 0.0 ? 1.0 : density);
    width /= density;
    auto returnValue = JSVal(ToJSValue(width));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSRenderingContext::JsSetWidth(const JSCallbackInfo& info)
{
    return;
}

void JSRenderingContext::JsSetHeight(const JSCallbackInfo& info)
{
    return;
}

void JSRenderingContext::JsGetHeight(const JSCallbackInfo& info)
{
    double height = 0.0;
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_VOID(canvasRenderingContext2DModel);
    canvasRenderingContext2DModel->GetHeight(canvasPattern_, height);
    double density = GetDensity();
    density = (density == 0.0 ? 1.0 : density);
    height /= density;
    auto returnValue = JSVal(ToJSValue(height));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
}

void JSRenderingContext::JsTransferFromImageBitmap(const JSCallbackInfo& info)
{
    ContainerScope scope(Container::CurrentIdSafely());
    if (info.Length() == 0) {
        return;
    }
    if (!info[0]->IsObject()) {
        return;
    }
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    panda::Local<JsiValue> value = info[0].Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;
    napi_value napiValue = nativeEngine->ValueToNapiValue(valueWrapper);
    void* nativeObj = nullptr;
    auto status = napi_unwrap(env, napiValue, &nativeObj);
    if (status != napi_ok) {
        return;
    }
    auto jsImage = (JSRenderImage*)nativeObj;
    uint32_t id = jsImage->GetContextId();

    RefPtr<AceType> offscreenPattern = JSOffscreenRenderingContext::GetOffscreenPattern(id);
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_VOID(canvasRenderingContext2DModel);
    canvasRenderingContext2DModel->SetTransferFromImageBitmap(canvasPattern_, offscreenPattern);
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

void HandleDeferred(const shared_ptr<CanvasAsyncCxt>& asyncCtx, ImageAnalyzerState state)
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

void JSRenderingContext::JsStartImageAnalyzer(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    auto env = reinterpret_cast<napi_env>(nativeEngine);

    auto asyncCtx = std::make_shared<CanvasAsyncCxt>();
    asyncCtx->env = env;
    napi_value promise = nullptr;
    napi_create_promise(env, &asyncCtx->deferred, &promise);
    if (info.Length() < 1 || !info[0]->IsObject()) {
        ReturnPromise(info, promise);
        return;
    }

    ScopeRAII scopeRaii(env);
    panda::Local<JsiValue> value = info[0].Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;
    napi_value configNativeValue = nativeEngine->ValueToNapiValue(valueWrapper);
    if (isImageAnalyzing_) {
        napi_value result = CreateErrorValue(env, ERROR_CODE_AI_ANALYSIS_IS_ONGOING);
        napi_reject_deferred(env, asyncCtx->deferred, result);
        ReturnPromise(info, promise);
        return;
    }

    onAnalyzedCallback onAnalyzed_ = [asyncCtx, weakCtx = WeakClaim(this)](ImageAnalyzerState state) {
        CHECK_NULL_VOID(asyncCtx);
        HandleDeferred(asyncCtx, state);
        auto ctx = weakCtx.Upgrade();
        CHECK_NULL_VOID(ctx);
        ctx->isImageAnalyzing_ = false;
    };
    isImageAnalyzing_ = true;
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_VOID(canvasRenderingContext2DModel);
    canvasRenderingContext2DModel->StartImageAnalyzer(canvasPattern_, configNativeValue, onAnalyzed_);
    ReturnPromise(info, promise);
}

void JSRenderingContext::JsStopImageAnalyzer(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_VOID(canvasRenderingContext2DModel);
    canvasRenderingContext2DModel->StopImageAnalyzer(canvasPattern_);
}
} // namespace OHOS::Ace::Framework
