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

#ifndef FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_CANVAS_RENDERER_H
#define FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_CANVAS_RENDERER_H

#include "base/memory/referenced.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/bindings_defines.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas_gradient.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas_image_data.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas_path.h"
#include "bridge/declarative_frontend/jsview/canvas/js_matrix2d.h"
#include "bridge/declarative_frontend/jsview/canvas/js_path2d.h"
#include "bridge/declarative_frontend/jsview/canvas/js_rendering_context_base.h"
#include "bridge/declarative_frontend/jsview/canvas/js_render_image.h"
#include "bridge/declarative_frontend/jsview/js_container_base.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/components_ng/pattern/canvas/rendering_context_2d_model.h"

namespace OHOS::Ace::Framework {

class JSCanvasRenderer : public JSRenderingContextBase {
    DECLARE_ACE_TYPE(JSCanvasRenderer, JSRenderingContextBase);
public:
    JSCanvasRenderer();
    ~JSCanvasRenderer() override;

    enum class FunctionCode {
        FILL_RECT = 0,
        STROKE_RECT,
        CLEAR_RECT,
        FILL_TEXT,
        STROKE_TEXT,
        FILL_STYLE_SETTER,
        STROKE_STYLE_SETTER,
    };

    static RefPtr<CanvasPath2D> JsMakePath2D(const JSCallbackInfo& info);
    void SetAntiAlias() override;
    void SetDensity() override;

    void ParseImageData(const JSCallbackInfo& info, ImageData& imageData);
    void JsCloseImageBitmap(const std::string& src);

    void JsFillRect(const JSCallbackInfo& info);
    void JsStrokeRect(const JSCallbackInfo& info);
    void JsClearRect(const JSCallbackInfo& info);
    void JsFillText(const JSCallbackInfo& info);
    void JsStrokeText(const JSCallbackInfo& info);
    void JsMeasureText(const JSCallbackInfo& info);
    void JsMoveTo(const JSCallbackInfo& info);
    void JsLineTo(const JSCallbackInfo& info);
    void JsBezierCurveTo(const JSCallbackInfo& info);
    void JsQuadraticCurveTo(const JSCallbackInfo& info);
    void JsArcTo(const JSCallbackInfo& info);
    void JsArc(const JSCallbackInfo& info);
    void JsEllipse(const JSCallbackInfo& info);
    void JsFill(const JSCallbackInfo& info);
    void JsStroke(const JSCallbackInfo& info);
    void JsClip(const JSCallbackInfo& info);
    void JsRect(const JSCallbackInfo& info);
    void JsRoundRect(const JSCallbackInfo& info);
    void JsBeginPath(const JSCallbackInfo& info);
    void JsClosePath(const JSCallbackInfo& info);
    void JsRestore(const JSCallbackInfo& info);
    void JsSave(const JSCallbackInfo& info);
    void JsRotate(const JSCallbackInfo& info);
    void JsScale(const JSCallbackInfo& info);
    void JsGetTransform(const JSCallbackInfo& info);
    void JsSetTransform(const JSCallbackInfo& info);
    void JsResetTransform(const JSCallbackInfo& info);
    void JsTransform(const JSCallbackInfo& info);
    void JsTranslate(const JSCallbackInfo& info);
    void JsSetLineDash(const JSCallbackInfo& info);
    void JsGetLineDash(const JSCallbackInfo& info);
    void JsToDataUrl(const JSCallbackInfo& info);
    void JsCreateLinearGradient(const JSCallbackInfo& info);
    void JsCreateRadialGradient(const JSCallbackInfo& info);
    void JsCreateConicGradient(const JSCallbackInfo& info);
    void JsSaveLayer(const JSCallbackInfo& info);
    void JsRestoreLayer(const JSCallbackInfo& info);
    void JsSetFont(const JSCallbackInfo& info);
    void JsSetFillStyle(const JSCallbackInfo& info);
    void JsSetStrokeStyle(const JSCallbackInfo& info);
    void JsSetLineCap(const JSCallbackInfo& info);
    void JsSetLineJoin(const JSCallbackInfo& info);
    void JsSetMiterLimit(const JSCallbackInfo& info);
    void JsSetLineWidth(const JSCallbackInfo& info);
    void JsSetGlobalAlpha(const JSCallbackInfo& info);
    void JsSetGlobalCompositeOperation(const JSCallbackInfo& info);
    void JsSetLineDashOffset(const JSCallbackInfo& info);
    void JsSetShadowBlur(const JSCallbackInfo& info);
    void JsSetShadowColor(const JSCallbackInfo& info);
    void JsSetShadowOffsetX(const JSCallbackInfo& info);
    void JsSetShadowOffsetY(const JSCallbackInfo& info);
    void JsSetImageSmoothingEnabled(const JSCallbackInfo& info);
    void JsDrawImage(const JSCallbackInfo& info);
    void JsCreatePattern(const JSCallbackInfo& info);
    void JsCreateImageData(const JSCallbackInfo& info);
    void JsPutImageData(const JSCallbackInfo& info);
    void JsGetImageData(const JSCallbackInfo& info);
    void JsGetJsonData(const JSCallbackInfo& info);
    void JsSetTextAlign(const JSCallbackInfo& info);
    void JsSetTextBaseline(const JSCallbackInfo& info);
    void JsSetImageSmoothingQuality(const JSCallbackInfo& info);
    void JsGetPixelMap(const JSCallbackInfo& info);
    void JsSetPixelMap(const JSCallbackInfo& info);
    void JsDrawBitmapMesh(const JSCallbackInfo& info);
    void JsSetFilter(const JSCallbackInfo& info);
    void JsSetDirection(const JSCallbackInfo& info);
    void JsReset(const JSCallbackInfo& info);
    void JsSetLetterSpacing(const JSCallbackInfo& info);

    void JSGetEmpty(const JSCallbackInfo& info)
    {
        return;
    }

    void SetCanvasPattern(const RefPtr<AceType>& canvas) override
    {
        renderingContext2DModel_->SetPattern(canvas);
        if (isInitializeShadow_) {
            return;
        }
        isInitializeShadow_ = true;
        renderingContext2DModel_->SetShadowColor(Color::TRANSPARENT);
    }

    void SetOffscreenPattern(const RefPtr<AceType>& offscreenCanvas)
    {
        offscreenPattern_ = offscreenCanvas;
        renderingContext2DModel_->SetPattern(offscreenCanvas);
        if (isOffscreenInitializeShadow_) {
            return;
        }
        isOffscreenInitializeShadow_ = true;
        renderingContext2DModel_->SetShadowColor(Color::TRANSPARENT);
    }

    void SetAnti(bool anti)
    {
        anti_ = anti;
    }

    bool GetAnti()
    {
        return anti_;
    }

    void SetUnit(CanvasUnit unit)
    {
        unit_ = unit;
    }

    CanvasUnit GetUnit()
    {
        return unit_;
    }

    inline double GetDensity(bool useSystemDensity = false)
    {
        if (useSystemDensity) {
            return !NearZero(density_) ? density_ : 1.0;
        } else {
            return ((GetUnit() == CanvasUnit::DEFAULT) && !NearZero(density_)) ? density_ : 1.0;
        }
    }

    void SetInstanceId(int32_t id) override
    {
        instanceId_ = id;
    }

    void SetTransform(unsigned int id, const TransformParam&);

    void ResetPaintState();
    ACE_DISALLOW_COPY_AND_MOVE(JSCanvasRenderer);

protected:
    void ParseFillGradient(const JSCallbackInfo& info);
    void ParseFillPattern(const JSCallbackInfo& info);
    void ParseStorkeGradient(const JSCallbackInfo& info);
    void ParseStrokePattern(const JSCallbackInfo& info);
    JSRenderImage* UnwrapNapiImage(const JSRef<JSObject> jsObject);

protected:
    bool isJudgeSpecialValue_ = false;
    RefPtr<RenderingContext2DModel> renderingContext2DModel_;
    bool anti_ = false;

    RefPtr<AceType> offscreenPattern_;

    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;

    int32_t apiVersion_ = 0;

private:
    void ExtractInfoToImage(CanvasImage& image, const JSCallbackInfo& info, bool isImage);
    JSRef<JSObject> createGradientObj(const std::shared_ptr<Gradient>& gradient);
    void DrawSvgImage(const JSCallbackInfo& info, JSRenderImage* jsImage);
    void DrawImage(const JSCallbackInfo& info, JSRenderImage* jsImage);
    void DrawPixelMap(const JSCallbackInfo& info);

    PaintState paintState_;
    std::vector<PaintState> savePaintState_;
    bool isInitializeShadow_ = false;
    bool isOffscreenInitializeShadow_ = false;
    Dimension GetDimensionValue(const std::string& str);
    bool IsCustomFont(const std::string& fontName);
    bool IsValidLetterSpacing(const std::string& letterSpacing);
    CanvasUnit unit_ = CanvasUnit::DEFAULT;
    double density_ = 1.0;
    int32_t densityCallbackId_ = 0;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_CANVAS_RENDERER_H
