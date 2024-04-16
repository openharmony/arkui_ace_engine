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

#include "bridge/declarative_frontend/jsview/js_drawing_rendering_context.h"

#include "canvas_napi/js_canvas.h"

#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/jsview/js_offscreen_rendering_context.h"
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
    auto returnValue = JSVal(ToJSValue(size_));
    auto returnPtr = JSRef<JSVal>::Make(returnValue);
    info.SetReturnValue(returnPtr);
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
        context->size_.SetHeight(PipelineBase::Px2VpWithCurrentDensity(height));
        context->size_.SetWidth(PipelineBase::Px2VpWithCurrentDensity(width));
        auto jsCanvas = OHOS::Rosen::Drawing::JsCanvas::CreateJsCanvas(env, canvas);
        JsiRef<JsiValue> jsCanvasVal = JsConverter::ConvertNapiValueToJsVal(jsCanvas);
        context->jsCanvasVal_ = JSRef<JSVal>::Cast(jsCanvasVal);
    };
    std::function<void(RSCanvas*, double, double)> callback = func;
    auto customPaintPattern = AceType::DynamicCast<NG::CustomPaintPattern>(canvasPattern);
    if (customPaintPattern) {
        customPaintPattern->SetRSCanvasCallback(callback);
    }
}

void JSDrawingRenderingContext::SetInvalidate(const JSCallbackInfo& info)
{
    auto customPaintPattern = AceType::DynamicCast<NG::CustomPaintPattern>(canvasPattern_);
    CHECK_NULL_VOID(customPaintPattern);
    customPaintPattern->SetInvalidate();
}
} // namespace OHOS::Ace::Framework
