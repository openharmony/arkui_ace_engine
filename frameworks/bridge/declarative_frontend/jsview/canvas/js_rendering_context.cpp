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

#include "base/error/error_code.h"
#include "base/memory/referenced.h"
#include "base/log/ace_scoring_log.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/canvas/js_offscreen_rendering_context.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
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
        auto onAttach = [weakCtx = WeakClaim(this)]() {
            auto ctx = weakCtx.Upgrade();
            CHECK_NULL_VOID(ctx);
            ctx->OnAttachToCanvas();
        };
        auto onDetach = [weakCtx = WeakClaim(this)]() {
            auto ctx = weakCtx.Upgrade();
            CHECK_NULL_VOID(ctx);
            ctx->OnDetachFromCanvas();
        };
        auto canvasRenderingContext2DModel =
            AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
        CHECK_NULL_VOID(canvasRenderingContext2DModel);
        canvasRenderingContext2DModel->SetOnAttach(onAttach);
        canvasRenderingContext2DModel->SetOnDetach(onDetach);
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
        "canvas", &JSRenderingContext::JsGetCanvas, &JSRenderingContext::JsSetCanvas);
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
    JSClass<JSRenderingContext>::CustomMethod("on", &JSRenderingContext::JsOn);
    JSClass<JSRenderingContext>::CustomMethod("off", &JSRenderingContext::JsOff);

    // Register the "CanvasRenderingContext2D" to the global object of the vm
    JSClass<JSRenderingContext>::Bind(globalObj, JSRenderingContext::Constructor, JSRenderingContext::Destructor);
}

void JSRenderingContext::Constructor(const JSCallbackInfo& args)
{
    auto jsRenderContext = Referenced::MakeRefPtr<JSRenderingContext>();
    jsRenderContext->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(jsRenderContext));

    auto* jsContextSetting = args.UnwrapArg<JSRenderingContextSettings>(0);
    if (jsContextSetting) {
        bool anti = jsContextSetting->GetAntialias();
        jsRenderContext->SetAnti(anti);

        int32_t unit = 0;
        if (args.GetInt32Arg(1, unit) && (static_cast<CanvasUnit>(unit) == CanvasUnit::PX)) {
            jsRenderContext->SetUnit(CanvasUnit::PX);
        }
    }
}

void JSRenderingContext::Destructor(JSRenderingContext* controller)
{
    if (controller != nullptr) {
        controller->DecRefCount();
    }
}

void JSRenderingContext::OnAttachToCanvas()
{
    ContainerScope scope(instanceId_);
    for (const auto& iter : attachCallback_) {
        auto callback = iter.second;
        if (callback) {
            callback();
        }
    }
}

void JSRenderingContext::OnDetachFromCanvas()
{
    ContainerScope scope(instanceId_);
    for (const auto& iter : detachCallback_) {
        auto callback = iter.second;
        if (callback) {
            callback();
        }
    }
    ResetPaintState();
}

void JSRenderingContext::JsGetCanvas(const JSCallbackInfo& info)
{
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_VOID(canvasRenderingContext2DModel);
    auto nodeId = canvasRenderingContext2DModel->GetId();

    auto vm = info.GetVm();
    auto globalObj = JSNApi::GetGlobalObject(vm);
    auto globalFunc = globalObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "__getFrameNodeByNodeId__"));
    JsiValue jsiValue(globalFunc);
    JsiRef<JsiValue> globalFuncRef = JsiRef<JsiValue>::Make(jsiValue);
    if (!globalFuncRef->IsFunction()) {
        return;
    }
    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(globalFuncRef));
    JSRef<JSVal> params[2]; // The count of the function's params is 2.
    params[0] = JSRef<JSVal>::Make(ToJSValue(instanceId_));
    params[1] = JSRef<JSVal>::Make(ToJSValue(nodeId));
    auto returnPtr = jsFunc->ExecuteJS(2, params);
    info.SetReturnValue(returnPtr);
    return;
}

void JSRenderingContext::JsSetCanvas(const JSCallbackInfo& info)
{
    return;
}

void JSRenderingContext::JsGetWidth(const JSCallbackInfo& info)
{
    double width = 0.0;
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_VOID(canvasRenderingContext2DModel);
    canvasRenderingContext2DModel->GetWidth(width);
    double density = GetDensity();
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
    canvasRenderingContext2DModel->GetHeight(height);
    double density = GetDensity();
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
    CHECK_NULL_VOID(jsImage);
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_VOID(canvasRenderingContext2DModel);
#ifdef PIXEL_MAP_SUPPORTED
    auto pixelMap = jsImage->GetPixelMap();
    CHECK_NULL_VOID(pixelMap);
    canvasRenderingContext2DModel->TransferFromImageBitmap(pixelMap);
#else
    auto imageData = jsImage->GetImageData();
    CHECK_NULL_VOID(imageData);
    canvasRenderingContext2DModel->TransferFromImageBitmap(imageData);
#endif
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

    OnAnalyzedCallback onAnalyzed_ = [asyncCtx, weakCtx = WeakClaim(this)](ImageAnalyzerState state) {
        CHECK_NULL_VOID(asyncCtx);
        HandleDeferred(asyncCtx, state);
        auto ctx = weakCtx.Upgrade();
        CHECK_NULL_VOID(ctx);
        ctx->isImageAnalyzing_ = false;
    };
    isImageAnalyzing_ = true;
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_VOID(canvasRenderingContext2DModel);
    canvasRenderingContext2DModel->StartImageAnalyzer(configNativeValue, onAnalyzed_);
    ReturnPromise(info, promise);
}

void JSRenderingContext::JsStopImageAnalyzer(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_VOID(canvasRenderingContext2DModel);
    canvasRenderingContext2DModel->StopImageAnalyzer();
}

CanvasCallbackFuncPairList::const_iterator JSRenderingContext::FindCbList(
    napi_env env, napi_value cb, CanvasCallbackFuncPairList& callbackFuncPairList)
{
    return std::find_if(callbackFuncPairList.begin(), callbackFuncPairList.end(), [env, cb](const auto& item) -> bool {
        bool result = false;
        napi_value refItem;
        napi_get_reference_value(env, item.first, &refItem);
        napi_strict_equals(env, refItem, cb, &result);
        return result;
    });
}

void JSRenderingContext::AddCallbackToList(
    napi_env env, napi_value cb, CanvasCallbackType type, const std::function<void()>&& onFunc)
{
    if (type == CanvasCallbackType::ON_ATTACH) {
        auto iter = FindCbList(env, cb, attachCallback_);
        if (iter == attachCallback_.end()) {
            napi_ref ref = nullptr;
            napi_create_reference(env, cb, 1, &ref);
            attachCallback_.emplace_back(ref, onFunc);
        }
    } else if (type == CanvasCallbackType::ON_DETACH) {
        auto iter = FindCbList(env, cb, detachCallback_);
        if (iter == detachCallback_.end()) {
            napi_ref ref = nullptr;
            napi_create_reference(env, cb, 1, &ref);
            detachCallback_.emplace_back(ref, onFunc);
        }
    }
}

void JSRenderingContext::DeleteCallbackFromList(int argc, napi_env env, napi_value cb, CanvasCallbackType type)
{
    if (argc == 1) {
        if (type == CanvasCallbackType::ON_ATTACH) {
            for (const auto& item : attachCallback_) {
                napi_delete_reference(env, item.first);
            }
            attachCallback_.clear();
        } else if (type == CanvasCallbackType::ON_DETACH) {
            for (const auto& item : detachCallback_) {
                napi_delete_reference(env, item.first);
            }
            detachCallback_.clear();
        }
    } else if (argc == 2) { // The count of params is 2.
        if (type == CanvasCallbackType::ON_ATTACH) {
            auto iter = FindCbList(env, cb, attachCallback_);
            if (iter != attachCallback_.end()) {
                napi_delete_reference(env, iter->first);
                attachCallback_.erase(iter);
            }
        } else if (type == CanvasCallbackType::ON_DETACH) {
            auto iter = FindCbList(env, cb, detachCallback_);
            if (iter != detachCallback_.end()) {
                napi_delete_reference(env, iter->first);
                detachCallback_.erase(iter);
            }
        }
    }
}

CanvasCallbackType JSRenderingContext::GetCanvasCallbackType(const std::string& strType)
{
    CanvasCallbackType type = CanvasCallbackType::UNKNOWN;
    static constexpr char attachType[] = "onAttach";
    static constexpr char detachType[] = "onDetach";
    if (strType.compare(attachType) == 0) {
        type = CanvasCallbackType::ON_ATTACH;
    } else if (strType.compare(detachType) == 0) {
        type = CanvasCallbackType::ON_DETACH;
    }
    return type;
}

void JSRenderingContext::JsOn(const JSCallbackInfo& info)
{
    if (!info[0]->IsString() || !info[1]->IsFunction()) {
        return;
    }
    const CanvasCallbackType type = GetCanvasCallbackType(info[0]->ToString());
    if (type == CanvasCallbackType::UNKNOWN) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter error.");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[1]));
    std::function<void()> onFunc = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
                                       id = instanceId_]() {
        ContainerScope scope(id);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        func->Execute();
    };
    ContainerScope scope(instanceId_);
#if !defined(PREVIEW)
    auto engine = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
#else
    auto engine = EngineHelper::GetCurrentEngineSafely();
#endif
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    ScopeRAII scopeNapi(env);
    panda::Local<JsiValue> value = info[1].Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;
    napi_value cb = nativeEngine->ValueToNapiValue(valueWrapper);
    napi_handle_scope napiScope = nullptr;
    napi_open_handle_scope(env, &napiScope);
    CHECK_NULL_VOID(napiScope);

    AddCallbackToList(env, cb, type, std::move(onFunc));
    napi_close_handle_scope(env, napiScope);
}

void JSRenderingContext::JsOff(const JSCallbackInfo& info)
{
    if (!info[0]->IsString()) {
        return;
    }
    const CanvasCallbackType type = GetCanvasCallbackType(info[0]->ToString());
    if (type == CanvasCallbackType::UNKNOWN) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter error.");
        return;
    }
    ContainerScope scope(instanceId_);
#if !defined(PREVIEW)
    auto engine = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
#else
    auto engine = EngineHelper::GetCurrentEngineSafely();
#endif
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    ScopeRAII scopeNapi(env);
    napi_value cb = nullptr;
    if (info[1]->IsFunction()) {
        panda::Local<JsiValue> value = info[1].Get().GetLocalHandle();
        JSValueWrapper valueWrapper = value;
        cb = nativeEngine->ValueToNapiValue(valueWrapper);
    }

    DeleteCallbackFromList(info.Length(), env, cb, type);
}
} // namespace OHOS::Ace::Framework
