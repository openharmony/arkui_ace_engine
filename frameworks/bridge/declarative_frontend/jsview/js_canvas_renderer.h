/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/bindings_defines.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_canvas_gradient.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_canvas_image_data.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_canvas_path.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_container_base.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_matrix2d.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_path2d.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_render_image.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components_ng/pattern/canvas_renderer/canvas_renderer_model.h"

namespace OHOS::Ace::Framework {

class JSCanvasRenderer : public Referenced {
public:
    JSCanvasRenderer();
    ~JSCanvasRenderer() override = default;

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
    void SetAntiAlias();

    void ParseImageData(const JSCallbackInfo& info, ImageData& imageData, std::vector<uint8_t>& array);
    void ParseImageDataAsStr(const JSCallbackInfo& info, ImageData& imageData);
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
    void JsToDataUrl(const JSCallbackInfo& info);
    void JsCreateLinearGradient(const JSCallbackInfo& info);
    void JsCreateRadialGradient(const JSCallbackInfo& info);
    void JsCreateConicGradient(const JSCallbackInfo& info);

    void JsGetFillStyle(const JSCallbackInfo& info);
    void JsGetStrokeStyle(const JSCallbackInfo& info);
    void JsGetLineCap(const JSCallbackInfo& info);
    void JsGetLineDash(const JSCallbackInfo& info);
    void JsGetLineJoin(const JSCallbackInfo& info);
    void JsGetMiterLimit(const JSCallbackInfo& info);
    void JsGetLineWidth(const JSCallbackInfo& info);
    void JsGetTextAlign(const JSCallbackInfo& info);
    void JsGetTextBaseline(const JSCallbackInfo& info);
    void JsGetGlobalAlpha(const JSCallbackInfo& info);
    void JsGetGlobalCompositeOperation(const JSCallbackInfo& info);
    void JsGetLineDashOffset(const JSCallbackInfo& info);
    void JsGetShadowBlur(const JSCallbackInfo& info);
    void JsGetShadowColor(const JSCallbackInfo& info);
    void JsGetShadowOffsetX(const JSCallbackInfo& info);
    void JsGetShadowOffsetY(const JSCallbackInfo& info);
    void JsGetImageSmoothingEnabled(const JSCallbackInfo& info);
    void JsGetImageSmoothingQuality(const JSCallbackInfo& info);
    void JsGetFont(const JSCallbackInfo& info);
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
    void JsGetFilter(const JSCallbackInfo& info);
    void JsSetFilter(const JSCallbackInfo& info);
    void JsGetDirection(const JSCallbackInfo& info);
    void JsSetDirection(const JSCallbackInfo& info);

    void SetCanvasPattern(const RefPtr<AceType>& canvas)
    {
        canvasPattern_ = canvas;
        isOffscreen_ = false;
        BaseInfo baseInfo;
        baseInfo.canvasPattern = canvasPattern_;
        baseInfo.offscreenPattern = offscreenPattern_;
        baseInfo.isOffscreen = isOffscreen_;
        CanvasRendererModel::GetInstance()->SetShadowColor(baseInfo, Color::TRANSPARENT);
    }

    void SetOffscreenPattern(const RefPtr<AceType>& offscreenCanvas)
    {
        offscreenPattern_ = offscreenCanvas;
        isOffscreen_ = true;
        BaseInfo baseInfo;
        baseInfo.canvasPattern = canvasPattern_;
        baseInfo.offscreenPattern = offscreenPattern_;
        baseInfo.isOffscreen = isOffscreen_;
        CanvasRendererModel::GetInstance()->SetShadowColor(baseInfo, Color::TRANSPARENT);
    }

    std::vector<uint32_t> GetLineDash() const
    {
        return lineDash_;
    }

    void SetLineDash(const std::vector<uint32_t> lineDash)
    {
        lineDash_ = lineDash;
    }

    void SetAnti(bool anti)
    {
        anti_ = anti;
    }

    bool GetAnti()
    {
        return anti_;
    }

    void SetTransform(unsigned int id, const TransformParam&);
    
    ACE_DISALLOW_COPY_AND_MOVE(JSCanvasRenderer);

protected:
    void ParseFillGradient(const JSCallbackInfo& info);
    void ParseFillPattern(const JSCallbackInfo& info);
    void ParseStorkeGradient(const JSCallbackInfo& info);
    void ParseStrokePattern(const JSCallbackInfo& info);

protected:
    bool anti_ = false;

    RefPtr<AceType> canvasPattern_;
    RefPtr<AceType> offscreenPattern_;

private:
    void ExtractInfoToImage(CanvasImage& image, const JSCallbackInfo& info, bool isImage);
    std::unique_ptr<ImageData> GetImageDataFromCanvas(
        const double& left, const double& top, const double& width, const double& height);
    PaintState paintState_;
    TextStyle style_;
    static std::unordered_map<int32_t, std::shared_ptr<Pattern>> pattern_;
    static unsigned int patternCount_;
    std::weak_ptr<Ace::Pattern> GetPatternNG(int32_t id);
    Pattern GetPattern(unsigned int id);
    std::vector<uint32_t> lineDash_;
    ImageData imageData_;
    bool isOffscreen_ = false;
    std::shared_ptr<Pattern> GetPatternPtr(int32_t id);
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORK_JAVASCRIPT_BRIDGE_JS_VIEW_JS_CANVAS_RENDERER_H
