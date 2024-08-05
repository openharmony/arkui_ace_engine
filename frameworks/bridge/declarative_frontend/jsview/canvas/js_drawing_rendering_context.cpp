/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/canvas/js_drawing_rendering_context.h"

#include "canvas_napi/js_canvas.h"

#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/jsview/canvas/js_offscreen_rendering_context.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/base/modifier.h"

namespace OHOS::Ace::Framework {

void JSDrawingRenderingContext::JSBind(BindingTarget globalObj)
{
    JSClass<JSDrawingRenderingContext>::Declare("DrawingRenderingContext");
    JSClass<JSDrawingRenderingContext>::CustomProperty(
        "size", &JSDrawingRenderingContext::JsGetSize, &JSDrawingRenderingContext::JsSetSize);
    JSClass<JSDrawingRenderingContext>::CustomProperty(
        "canvas", &JSDrawingRenderingContext::JsGetCanvas, &JSDrawingRenderingContext::JsSetCanvas);
    JSClass<JSDrawingRenderingContext>::CustomMethod(
        "invalidate", &JSDrawingRenderingContext::SetInvalidate);

    JSClass<JSDrawingRenderingContext>::Bind(
        globalObj, JSDrawingRenderingContext::Constructor, JSDrawingRenderingContext::Destructor);
}

void JSDrawingRenderingContext::Constructor(const JSCallbackInfo& args)
{
    auto jsDrawingRenderContext = Referenced::MakeRefPtr<JSDrawingRenderingContext>();
    jsDrawingRenderContext->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(jsDrawingRenderContext));
    int32_t unit = 0;
    if (args.GetInt32Arg(0, unit) && (static_cast<CanvasUnit>(unit) == CanvasUnit::PX)) {
        jsDrawingRenderContext->SetUnit(CanvasUnit::PX);
    }
}

void JSDrawingRenderingContext::Destructor(JSDrawingRenderingContext* controller)
{
    if (controller != nullptr) {
        controller->DecRefCount();
    }
}

JSDrawingRenderingContext::JSDrawingRenderingContext()
{
    SetInstanceId(Container::CurrentIdSafely());
}

void JSDrawingRenderingContext::JsGetCanvas(const JSCallbackInfo& info)
{
    info.SetReturnValue(jsCanvasVal_);
}

void JSDrawingRenderingContext::JsSetCanvas(const JSCallbackInfo& info)
{
    return;
}

void JSDrawingRenderingContext::JsSetSize(const JSCallbackInfo& info)
{
    return;
}

void JSDrawingRenderingContext::JsGetSize(const JSCallbackInfo& info)
{
    auto retObj = JSRef<JSObject>::New();
    retObj->SetProperty("width", size_.Width().value_or(0.0));
    retObj->SetProperty("height", size_.Height().value_or(0.0));
    info.SetReturnValue(retObj);
}

void JSDrawingRenderingContext::SetRSCanvasCallback(RefPtr<AceType>& canvasPattern)
{
    auto func = [wp = WeakClaim(this)](RSCanvas* canvas, double width, double height) {
        auto context = wp.Upgrade();
        CHECK_NULL_VOID(context);
        auto engine = EngineHelper::GetCurrentEngine();
        CHECK_NULL_VOID(engine);
        NativeEngine* nativeEngine = engine->GetNativeEngine();
        napi_env env = reinterpret_cast<napi_env>(nativeEngine);
        ScopeRAII scope(env);
        double density = context->GetDensity();
        height /= density;
        width /= density;
        context->size_.SetHeight(height);
        context->size_.SetWidth(width);
        auto jsCanvas = OHOS::Rosen::Drawing::JsCanvas::CreateJsCanvas(env, canvas);
        JsiRef<JsiValue> jsCanvasVal = JsConverter::ConvertNapiValueToJsVal(jsCanvas);
        context->jsCanvasVal_ = JSRef<JSVal>::Cast(jsCanvasVal);
    };
    std::function<void(RSCanvas*, double, double)> callback = func;
    auto customPaintPattern = AceType::DynamicCast<NG::CanvasPattern>(canvasPattern);
    if (customPaintPattern) {
        customPaintPattern->SetRSCanvasCallback(callback);
    }
}

void JSDrawingRenderingContext::SetInvalidate(const JSCallbackInfo& info)
{
    auto customPaintPattern = AceType::DynamicCast<NG::CanvasPattern>(canvasPattern_);
    CHECK_NULL_VOID(customPaintPattern);
    customPaintPattern->SetInvalidate();
}
} // namespace OHOS::Ace::Framework
