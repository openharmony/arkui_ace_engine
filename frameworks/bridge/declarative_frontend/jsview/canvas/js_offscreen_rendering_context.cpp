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

#include "bridge/declarative_frontend/jsview/canvas/js_offscreen_rendering_context.h"

#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/jsview/models/canvas/offscreen_canvas_rendering_context_2d_model_impl.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_pattern.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_rendering_context_2d_model_ng.h"

namespace OHOS::Ace::Framework {
std::mutex JSOffscreenRenderingContext::mutex_;
std::unordered_map<uint32_t, RefPtr<AceType>> JSOffscreenRenderingContext::offscreenPatternMap_;
uint32_t JSOffscreenRenderingContext::offscreenPatternCount_ = 0;

JSOffscreenRenderingContext::JSOffscreenRenderingContext()
{
    id = offscreenPatternCount_;
#ifdef NG_BUILD
    renderingContext2DModel_ = AceType::MakeRefPtr<NG::OffscreenCanvasRenderingContext2DModelNG>();
#else
    if (Container::IsCurrentUseNewPipeline()) {
        renderingContext2DModel_ = AceType::MakeRefPtr<NG::OffscreenCanvasRenderingContext2DModelNG>();
    } else {
        renderingContext2DModel_ = AceType::MakeRefPtr<Framework::OffscreenCanvasRenderingContext2DModelImpl>();
    }
#endif
}

void JSOffscreenRenderingContext::JSBind(BindingTarget globalObj)
{
    // Define the class "OffscreenCanvasRenderingContext2D"
    JSClass<JSOffscreenRenderingContext>::Declare("OffscreenCanvasRenderingContext2D");

    // Define all properties of the "OffscreenCanvasRenderingContext2D"
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "filter", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetFilter);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "direction", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetDirection);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "fillStyle", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetFillStyle);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "strokeStyle", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetStrokeStyle);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "lineCap", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetLineCap);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "lineJoin", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetLineJoin);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "miterLimit", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetMiterLimit);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "lineWidth", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetLineWidth);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "font", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetFont);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "textAlign", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetTextAlign);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "textBaseline", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetTextBaseline);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "globalAlpha", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetGlobalAlpha);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "globalCompositeOperation", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetGlobalCompositeOperation);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "lineDashOffset", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetLineDashOffset);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "shadowBlur", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetShadowBlur);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "shadowColor", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetShadowColor);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "shadowOffsetX", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetShadowOffsetX);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "shadowOffsetY", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetShadowOffsetY);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "imageSmoothingEnabled", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetImageSmoothingEnabled);
    JSClass<JSOffscreenRenderingContext>::CustomProperty(
        "imageSmoothingQuality", &JSCanvasRenderer::JSGetEmpty, &JSCanvasRenderer::JsSetImageSmoothingQuality);

    // Define all methods of the "OffscreenCanvasRenderingContext2D"
    JSClass<JSOffscreenRenderingContext>::CustomMethod(
        "transferToImageBitmap", &JSOffscreenRenderingContext::JsTransferToImageBitmap);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("toDataURL", &JSCanvasRenderer::JsToDataUrl);
    JSClass<JSOffscreenRenderingContext>::CustomMethod(
        "createRadialGradient", &JSCanvasRenderer::JsCreateRadialGradient);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("fillRect", &JSCanvasRenderer::JsFillRect);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("strokeRect", &JSCanvasRenderer::JsStrokeRect);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("clearRect", &JSCanvasRenderer::JsClearRect);
    JSClass<JSOffscreenRenderingContext>::CustomMethod(
        "createLinearGradient", &JSCanvasRenderer::JsCreateLinearGradient);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("fillText", &JSCanvasRenderer::JsFillText);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("strokeText", &JSCanvasRenderer::JsStrokeText);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("measureText", &JSCanvasRenderer::JsMeasureText);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("moveTo", &JSCanvasRenderer::JsMoveTo);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("lineTo", &JSCanvasRenderer::JsLineTo);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("bezierCurveTo", &JSCanvasRenderer::JsBezierCurveTo);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("quadraticCurveTo", &JSCanvasRenderer::JsQuadraticCurveTo);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("arcTo", &JSCanvasRenderer::JsArcTo);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("arc", &JSCanvasRenderer::JsArc);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("ellipse", &JSCanvasRenderer::JsEllipse);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("fill", &JSCanvasRenderer::JsFill);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("stroke", &JSCanvasRenderer::JsStroke);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("clip", &JSCanvasRenderer::JsClip);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("rect", &JSCanvasRenderer::JsRect);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("beginPath", &JSCanvasRenderer::JsBeginPath);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("closePath", &JSCanvasRenderer::JsClosePath);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("restore", &JSCanvasRenderer::JsRestore);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("save", &JSCanvasRenderer::JsSave);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("rotate", &JSCanvasRenderer::JsRotate);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("scale", &JSCanvasRenderer::JsScale);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("getTransform", &JSCanvasRenderer::JsGetTransform);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("setTransform", &JSCanvasRenderer::JsSetTransform);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("resetTransform", &JSCanvasRenderer::JsResetTransform);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("transform", &JSCanvasRenderer::JsTransform);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("translate", &JSCanvasRenderer::JsTranslate);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("setLineDash", &JSCanvasRenderer::JsSetLineDash);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("getLineDash", &JSCanvasRenderer::JsGetLineDash);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("drawImage", &JSCanvasRenderer::JsDrawImage);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("createPattern", &JSCanvasRenderer::JsCreatePattern);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("createImageData", &JSCanvasRenderer::JsCreateImageData);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("putImageData", &JSCanvasRenderer::JsPutImageData);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("getImageData", &JSCanvasRenderer::JsGetImageData);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("getJsonData", &JSCanvasRenderer::JsGetJsonData);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("getPixelMap", &JSCanvasRenderer::JsGetPixelMap);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("setPixelMap", &JSCanvasRenderer::JsSetPixelMap);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("createConicGradient", &JSCanvasRenderer::JsCreateConicGradient);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("saveLayer", &JSCanvasRenderer::JsSaveLayer);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("restoreLayer", &JSCanvasRenderer::JsRestoreLayer);
    JSClass<JSOffscreenRenderingContext>::CustomMethod("reset", &JSCanvasRenderer::JsReset);

    // Register the "OffscreenCanvasRenderingContext2D" to the golbal object of the vm
    JSClass<JSOffscreenRenderingContext>::Bind(
        globalObj, JSOffscreenRenderingContext::Constructor, JSOffscreenRenderingContext::Destructor);
}

// OffscreenCanvasRenderingContext2D(width: number, height: number, settings?: RenderingContextSettings,
//                                   unit?: LengthMetricsUnit)
void JSOffscreenRenderingContext::Constructor(const JSCallbackInfo& args)
{
    auto jsRenderContext = Referenced::MakeRefPtr<JSOffscreenRenderingContext>();
    jsRenderContext->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(jsRenderContext));

    double width = 0.0;
    double height = 0.0;
    double density = jsRenderContext->GetDensity();
    if (args.GetDoubleArg(0, width) && args.GetDoubleArg(1, height)) {
        width *= density;
        height *= density;
        jsRenderContext->SetWidth(width);
        jsRenderContext->SetHeight(height);
        auto renderingContext =
            AceType::DynamicCast<OffscreenCanvasRenderingContext2DModel>(jsRenderContext->renderingContext2DModel_);
        auto offscreenPattern =
            renderingContext->CreateOffscreenPattern(round(width), round(height));
        CHECK_NULL_VOID(offscreenPattern);
        size_t bitmapSize = renderingContext->GetBitmapSize(offscreenPattern);
        args.SetSize(bitmapSize);
        jsRenderContext->SetOffscreenPattern(offscreenPattern);
        std::lock_guard<std::mutex> lock(mutex_);
        offscreenPatternMap_[offscreenPatternCount_++] = offscreenPattern;
    }
    auto* jsContextSetting = args.UnwrapArg<JSRenderingContextSettings>(2);
    if (jsContextSetting) {
        bool anti = jsContextSetting->GetAntialias();
        jsRenderContext->SetAnti(anti);
        jsRenderContext->SetAntiAlias();

        int32_t unit = 0;
        if (args.GetInt32Arg(3, unit) && (static_cast<CanvasUnit>(unit) == CanvasUnit::PX)) { // 3: index of parameter
            jsRenderContext->SetUnit(CanvasUnit::PX);
        }
    }
    jsRenderContext->SetDensity();
}

void JSOffscreenRenderingContext::Destructor(JSOffscreenRenderingContext* context)
{
    CHECK_NULL_VOID(context);
    uint32_t contextId = context->GetId();
    context->DecRefCount();
    std::lock_guard<std::mutex> lock(mutex_);
    offscreenPatternMap_.erase(contextId);
}

void JSOffscreenRenderingContext::JsTransferToImageBitmap(const JSCallbackInfo& info)
{
    ContainerScope scope(instanceId_);
#if !defined(PREVIEW)
    auto engine = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
#else
    auto engine = EngineHelper::GetCurrentEngineSafely();
#endif
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    napi_env env = reinterpret_cast<napi_env>(nativeEngine);
    napi_value global = nullptr;
    napi_status status = napi_get_global(env, &global);
    if (status != napi_ok) {
        return;
    }
    napi_value constructor = nullptr;
    status = napi_get_named_property(env, global, "ImageBitmap", &constructor);
    if (status != napi_ok) {
        return;
    }
    napi_value renderImage = nullptr;
    napi_create_object(env, &renderImage);
    status = napi_new_instance(env, constructor, 0, nullptr, &renderImage);
    if (status != napi_ok) {
        return;
    }
    void* nativeObj = nullptr;
    status = napi_unwrap(env, renderImage, &nativeObj);
    if (status != napi_ok) {
        return;
    }
    auto jsImage = (JSRenderImage*)nativeObj;
    CHECK_NULL_VOID(jsImage);
    auto offscreenCanvasPattern = AceType::DynamicCast<NG::OffscreenCanvasPattern>(GetOffscreenPattern(id));
    CHECK_NULL_VOID(offscreenCanvasPattern);
#ifdef PIXEL_MAP_SUPPORTED
    auto pixelMap = offscreenCanvasPattern->TransferToImageBitmap();
    CHECK_NULL_VOID(pixelMap);
    jsImage->SetPixelMap(pixelMap);
#else
    auto imageData = offscreenCanvasPattern->GetImageData(0, 0, width_, height_);
    CHECK_NULL_VOID(imageData);
    jsImage->SetImageData(std::make_shared<Ace::ImageData>(*imageData));
#endif
    jsImage->SetUnit(GetUnit());
    jsImage->SetWidth(GetWidth());
    jsImage->SetHeight(GetHeight());
    info.SetReturnValue(JsConverter::ConvertNapiValueToJsVal(renderImage));
}

} // namespace OHOS::Ace::Framework
