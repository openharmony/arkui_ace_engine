/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_OFFSCREEN_CANVAS_H
#define FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_OFFSCREEN_CANVAS_H

#include "bridge/declarative_frontend/jsview/canvas/js_offscreen_rendering_context.h"
#include "core/common/ace_engine.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/pattern/canvas/offscreen_canvas_pattern.h"

namespace OHOS::Ace::Framework {

class JSOffscreenCanvas : public AceType, public JSInteractableView, public JSViewAbstract {
    DECLARE_ACE_TYPE(JSOffscreenCanvas, AceType);
public:
    JSOffscreenCanvas() = default;
    ~JSOffscreenCanvas() override = default;

    static void JSBind(BindingTarget globalObj, void* nativeEngine);
    static napi_value Constructor(napi_env env, napi_callback_info info);
    static napi_value InitOffscreenCanvas(napi_env env);
    static napi_value JsTransferToImageBitmap(napi_env env, napi_callback_info info);
    static napi_value JsGetContext(napi_env env, napi_callback_info info);
    static napi_value JsGetWidth(napi_env env, napi_callback_info info);
    static napi_value JsGetHeight(napi_env env, napi_callback_info info);
    static napi_value JsSetHeight(napi_env env, napi_callback_info info);
    static napi_value JsSetWidth(napi_env env, napi_callback_info info);
    napi_value OnGetWidth(napi_env env);
    napi_value OnGetHeight(napi_env env);

    void JsCreateRadialGradient(const JSCallbackInfo& info) {}
    void JsFillRect(const JSCallbackInfo& info) {}
    void JsStrokeRect(const JSCallbackInfo& info) {}
    void JsClearRect(const JSCallbackInfo& info) {}
    void JsCreateLinearGradient(const JSCallbackInfo& info) {}
    void JsFillText(const JSCallbackInfo& info) {}
    void JsStrokeText(const JSCallbackInfo& info) {}
    void JsMeasureText(const JSCallbackInfo& info) {}
    void JsMoveTo(const JSCallbackInfo& info) {}
    void JsLineTo(const JSCallbackInfo& info) {}
    void JsBezierCurveTo(const JSCallbackInfo& info) {}
    void JsQuadraticCurveTo(const JSCallbackInfo& info) {}
    void JsArcTo(const JSCallbackInfo& info) {}
    void JsArc(const JSCallbackInfo& info) {}
    void JsEllipse(const JSCallbackInfo& info) {}
    void JsFill(const JSCallbackInfo& info) {}
    void JsStroke(const JSCallbackInfo& info) {}
    void JsClip(const JSCallbackInfo& info) {}
    void JsRect(const JSCallbackInfo& info) {}
    void JsBeginPath(const JSCallbackInfo& info) {}
    void JsClosePath(const JSCallbackInfo& info) {}
    void JsRestore(const JSCallbackInfo& info) {}
    void JsSave(const JSCallbackInfo& info) {}
    void JsRotate(const JSCallbackInfo& info) {}
    void JsScale(const JSCallbackInfo& info) {}
    void JsGetTransform(const JSCallbackInfo& info) {}
    void JsSetTransform(const JSCallbackInfo& info) {}
    void JsResetTransform(const JSCallbackInfo& info) {}
    void JsTransform(const JSCallbackInfo& info) {}
    void JsTranslate(const JSCallbackInfo& info) {}
    void JsSetLineDash(const JSCallbackInfo& info) {}
    void JsGetLineDash(const JSCallbackInfo& info) {}
    void JsDrawImage(const JSCallbackInfo& info) {}
    void JsCreatePattern(const JSCallbackInfo& info) {}
    void JsCreateImageData(const JSCallbackInfo& info) {}
    void JsPutImageData(const JSCallbackInfo& info) {}
    void JsGetImageData(const JSCallbackInfo& info) {}
    void JsGetJsonData(const JSCallbackInfo& info) {}
    void JsGetPixelMap(const JSCallbackInfo& info) {}
    void JsSetPixelMap(const JSCallbackInfo& info) {}
    void JsCreateConicGradient(const JSCallbackInfo& info) {}
    void JsSetFilter(const JSCallbackInfo& info) {}
    void JsGetFilter(const JSCallbackInfo& info) {}
    void JsSetDirection(const JSCallbackInfo& info) {}
    void JsGetDirection(const JSCallbackInfo& info) {}
    void JsSetFillStyle(const JSCallbackInfo& info) {}
    void JsGetFillStyle(const JSCallbackInfo& info) {}
    void JsSetStrokeStyle(const JSCallbackInfo& info) {}
    void JsGetStrokeStyle(const JSCallbackInfo& info) {}
    void JsSetLineCap(const JSCallbackInfo& info) {}
    void JsGetLineCap(const JSCallbackInfo& info) {}
    void JsSetLineJoin(const JSCallbackInfo& info) {}
    void JsGetLineJoin(const JSCallbackInfo& info) {}
    void JsSetMiterLimit(const JSCallbackInfo& info) {}
    void JsGetMiterLimit(const JSCallbackInfo& info) {}
    void JsSetLineWidth(const JSCallbackInfo& info) {}
    void JsGetLineWidth(const JSCallbackInfo& info) {}
    void JsSetFont(const JSCallbackInfo& info) {}
    void JsGetFont(const JSCallbackInfo& info) {}
    void JsSetTextAlign(const JSCallbackInfo& info) {}
    void JsGetTextAlign(const JSCallbackInfo& info) {}
    void JsSetTextBaseline(const JSCallbackInfo& info) {}
    void JsGetTextBaseline(const JSCallbackInfo& info) {}
    void JsSetGlobalAlpha(const JSCallbackInfo& info) {}
    void JsGetGlobalAlpha(const JSCallbackInfo& info) {}
    void JsSetGlobalCompositeOperation(const JSCallbackInfo& info) {}
    void JsGetGlobalCompositeOperation(const JSCallbackInfo& info) {}
    void JsSetLineDashOffset(const JSCallbackInfo& info) {}
    void JsGetLineDashOffset(const JSCallbackInfo& info) {}
    void JsSetShadowBlur(const JSCallbackInfo& info) {}
    void JsGetShadowBlur(const JSCallbackInfo& info) {}
    void JsSetShadowColor(const JSCallbackInfo& info) {}
    void JsGetShadowColor(const JSCallbackInfo& info) {}
    void JsSetShadowOffsetX(const JSCallbackInfo& info) {}
    void JsGetShadowOffsetX(const JSCallbackInfo& info) {}
    void JsSetShadowOffsetY(const JSCallbackInfo& info) {}
    void JsGetShadowOffsetY(const JSCallbackInfo& info) {}
    void JsSetImageSmoothingEnabled(const JSCallbackInfo& info) {}
    void JsGetImageSmoothingEnabled(const JSCallbackInfo& info) {}
    void JsSetImageSmoothingQuality(const JSCallbackInfo& info) {}
    void JsGetImageSmoothingQuality(const JSCallbackInfo& info) {}
    void JSTransferFromImageBitmap(const JSCallbackInfo& info) {}
    void JsSaveLayer(const JSCallbackInfo& info) {}
    void JsRestoreLayer(const JSCallbackInfo& info) {}

    void SetWidth(double width)
    {
        width_ = width;
    }

    double GetWidth() const
    {
        return width_;
    }

    void SetHeight(double height)
    {
        height_ = height;
    }

    double GetHeight() const
    {
        return height_;
    }

    void SetDetachStatus(bool isDetached)
    {
        isDetached_ = isDetached;
    }

    bool IsDetached() const
    {
        return isDetached_;
    }

    void SetUnit(CanvasUnit unit)
    {
        unit_ = unit;
    }

    CanvasUnit GetUnit()
    {
        return unit_;
    }

    double GetDensity()
    {
        double density = PipelineBase::GetCurrentDensity();
        return ((GetUnit() == CanvasUnit::DEFAULT) && !NearZero(density)) ? density : 1.0;
    }

    bool IsGetContext() const
    {
        return isGetContext_;
    }

    void SetOffscreenPattern(const RefPtr<NG::OffscreenCanvasPattern>& offscreenPattern)
    {
        offscreenCanvasPattern_ = offscreenPattern;
    }

    enum class ContextType {
        CONTEXT_2D = 0,
    };

    ACE_DISALLOW_COPY_AND_MOVE(JSOffscreenCanvas);
private:
    napi_value CreateContext2d(napi_env env, double width, double height, const EcmaVM* vm);
    napi_value onTransferToImageBitmap(napi_env env);
    napi_value onGetContext(napi_env env, napi_callback_info info);
    void SetAntiAlias(napi_value argv);
    napi_value OnSetWidth(napi_env env, napi_callback_info info);
    napi_value OnSetHeight(napi_env env, napi_callback_info info);

    RefPtr<NG::OffscreenCanvasPattern> offscreenCanvasPattern_;
    RefPtr<JSOffscreenRenderingContext> offscreenCanvasContext_;
    RefPtr<JSRenderingContextSettings> offscreenCanvasSettings_;
    double width_ = 0.0f;
    double height_ = 0.0f;
    ContextType contextType_;
    CanvasUnit unit_ = CanvasUnit::DEFAULT;
    bool isGetContext_ = false;
    bool isDetached_ = false;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_OFFSCREEN_CANVAS_H
