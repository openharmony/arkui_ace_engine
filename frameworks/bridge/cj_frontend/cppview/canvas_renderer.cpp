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

#include "bridge/cj_frontend/cppview/canvas_renderer.h"

using namespace OHOS;

namespace OHOS::Ace::Framework {

namespace {
const int EVEN_CHECK = 2;
} // namespace

NativeCanvasRenderer::NativeCanvasRenderer(bool antialias) : FFIData()
{
    renderingContext2DModel_ = AceType::MakeRefPtr<NG::CanvasRenderingContext2DModelNG>();
    antialias_ = antialias;
}

NativeCanvasRenderer::~NativeCanvasRenderer()
{
    LOGI("Native CanvasRenderer Destroyed: %{public}" PRId64, GetID());
}

void NativeCanvasRenderer::SetCanvasPattern(const RefPtr<AceType>& canvas)
{
    canvasPattern_ = canvas;
    renderingContext2DModel_->SetPattern(canvas);
    if (isInitializeShadow_) {
        return;
    }
    isInitializeShadow_ = true;
    renderingContext2DModel_->SetShadowColor(Color::TRANSPARENT);
}

void NativeCanvasRenderer::SetAntiAlias()
{
    renderingContext2DModel_->SetAntiAlias(antialias_);
}

RefPtr<CanvasPath2D> NativeCanvasRenderer::MakePath2D(const std::string& capStr)
{
    return AceType::MakeRefPtr<CanvasPath2D>(capStr);
}

void NativeCanvasRenderer::SetFillStyle(const Color& color)
{
    renderingContext2DModel_->SetFillColor(color, true);
}

void NativeCanvasRenderer::SetFillStyle(const sptr<NativeCanvasGradient>& nativeCanvasGradient)
{
    auto gradient = std::make_shared<Gradient>(nativeCanvasGradient->GetGradient());
    renderingContext2DModel_->SetFillGradient(gradient);
}

void NativeCanvasRenderer::SetLineWidth(const double lineWidth)
{
    renderingContext2DModel_->SetLineWidth(lineWidth);
}

void NativeCanvasRenderer::SetStrokeStyle(const Color& color)
{
    renderingContext2DModel_->SetStrokeColor(color, true);
}

void NativeCanvasRenderer::SetStrokeStyle(const sptr<NativeCanvasGradient>& nativeCanvasGradient)
{
    auto gradient = std::make_shared<Gradient>(nativeCanvasGradient->GetGradient());
    renderingContext2DModel_->SetStrokeGradient(gradient);
}

void NativeCanvasRenderer::SetLineCap(const LineCapStyle lineCap)
{
    renderingContext2DModel_->SetLineCap(lineCap);
}

void NativeCanvasRenderer::SetLineJoin(const LineJoinStyle lineJoin)
{
    renderingContext2DModel_->SetLineJoin(lineJoin);
}

void NativeCanvasRenderer::SetMiterLimit(double limit)
{
    renderingContext2DModel_->SetMiterLimit(limit);
}

void NativeCanvasRenderer::SetFont(
    const FontStyle fontStyle, const std::string& fontWeight, const Dimension& fontSize, const std::string& fontFamily)
{
    auto weight = ConvertStrToFontWeight(fontWeight);
    auto families = ConvertStrToFontFamilies(fontFamily);

    renderingContext2DModel_->SetFontStyle(fontStyle);
    renderingContext2DModel_->SetFontWeight(weight);
    renderingContext2DModel_->SetFontSize(fontSize);
    renderingContext2DModel_->SetFontFamilies(families);

    style_.SetFontStyle(fontStyle);
    style_.SetFontWeight(weight);
    style_.SetFontSize(fontSize);
    style_.SetFontFamilies(families);
}

void NativeCanvasRenderer::SetTextAlign(const TextAlign align)
{
    renderingContext2DModel_->SetTextAlign(align);
    paintState_.SetTextAlign(align);
}

void NativeCanvasRenderer::SetTextBaseline(const TextBaseline baseline)
{
    renderingContext2DModel_->SetTextBaseline(baseline);
    style_.SetTextBaseline(baseline);
}

void NativeCanvasRenderer::SetGlobalAlpha(double alpha)
{
    renderingContext2DModel_->SetGlobalAlpha(alpha);
}

void NativeCanvasRenderer::SetLineDash(std::vector<double>& lineDash)
{
    if (lineDash.size() % EVEN_CHECK != 0) {
        lineDash.insert(lineDash.end(), lineDash.begin(), lineDash.end());
    }

    renderingContext2DModel_->SetLineDash(lineDash);
}

void NativeCanvasRenderer::SetLineDashOffset(const double lineDashOffset)
{
    renderingContext2DModel_->SetLineDashOffset(lineDashOffset);
}

void NativeCanvasRenderer::SetGlobalCompositeOperation(const CompositeOperation type)
{
    renderingContext2DModel_->SetCompositeType(type);
}

void NativeCanvasRenderer::SetShadowBlur(const double blur)
{
    renderingContext2DModel_->SetShadowBlur(blur);
}

void NativeCanvasRenderer::SetShadowColor(const Color& color)
{
    renderingContext2DModel_->SetShadowColor(color);
}

void NativeCanvasRenderer::SetShadowOffsetX(const double offsetX)
{
    renderingContext2DModel_->SetShadowOffsetX(offsetX);
}

void NativeCanvasRenderer::SetShadowOffsetY(const double offsetY)
{
    renderingContext2DModel_->SetShadowOffsetX(offsetY);
}

void NativeCanvasRenderer::SetImageSmoothingEnabled(const bool enabled)
{
    renderingContext2DModel_->SetSmoothingEnabled(enabled);
}

void NativeCanvasRenderer::SetImageSmoothingQuality(const std::string& quality)
{
    LOGE("canvas error: imageSmoothingQuality is not support in new pipeline");
}

void NativeCanvasRenderer::FillRect(const Rect& rect)
{
    renderingContext2DModel_->FillRect(rect);
}

void NativeCanvasRenderer::StrokeRect(const Rect& rect)
{
    renderingContext2DModel_->StrokeRect(rect);
}

void NativeCanvasRenderer::ClearRect(const Rect& rect)
{
    renderingContext2DModel_->ClearRect(rect);
}

void NativeCanvasRenderer::FillText(const double x, const double y, const std::string& text)
{
    FillTextInfo textInfo;
    textInfo.text = text;
    textInfo.x = x;
    textInfo.y = y;
    renderingContext2DModel_->SetFillText(paintState_, textInfo);
}

void NativeCanvasRenderer::StrokeText(const double x, const double y, const std::string& text)
{
    FillTextInfo textInfo;
    textInfo.text = text;
    textInfo.x = x;
    textInfo.y = y;
    renderingContext2DModel_->SetStrokeText(paintState_, textInfo);
}

Metrics NativeCanvasRenderer::MeasureText(const std::string& text)
{
    paintState_.SetTextStyle(style_);
    double width = 0.0;
    double height = 0.0;

    TextMetrics textMetrics = renderingContext2DModel_->GetMeasureTextMetrics(paintState_, text);
    width = textMetrics.width;
    height = textMetrics.height;

    Metrics metrics = { width, height };
    return metrics;
}

void NativeCanvasRenderer::Stroke()
{
    auto fillRule = CanvasFillRule::NONZERO;
    renderingContext2DModel_->SetStrokeRuleForPath(fillRule);
}

void NativeCanvasRenderer::Stroke(const sptr<NativeCanvasPath>& canvasPath)
{
    auto path = canvasPath->GetCanvasPath2d();
    auto fillRule = CanvasFillRule::NONZERO;

    renderingContext2DModel_->SetStrokeRuleForPath2D(fillRule, path);
}

void NativeCanvasRenderer::BeginPath()
{
    renderingContext2DModel_->BeginPath();
}

void NativeCanvasRenderer::MoveTo(const double x, const double y)
{
    renderingContext2DModel_->MoveTo(x, y);
}

void NativeCanvasRenderer::LineTo(const double x, const double y)
{
    renderingContext2DModel_->LineTo(x, y);
}

void NativeCanvasRenderer::ClosePath()
{
    renderingContext2DModel_->ClosePath();
}

void NativeCanvasRenderer::BezierCurveTo(const BezierCurveParam& param)
{
    renderingContext2DModel_->BezierCurveTo(param);
}

void NativeCanvasRenderer::QuadraticCurveTo(const QuadraticCurveParam& param)
{
    renderingContext2DModel_->QuadraticCurveTo(param);
}

void NativeCanvasRenderer::Arc(const ArcParam& param)
{
    renderingContext2DModel_->Arc(param);
}

void NativeCanvasRenderer::ArcTo(const ArcToParam& param)
{
    renderingContext2DModel_->ArcTo(param);
}

void NativeCanvasRenderer::Ellipse(const EllipseParam& param)
{
    renderingContext2DModel_->Ellipse(param);
}

void NativeCanvasRenderer::NormalRect(const Rect& rect)
{
    renderingContext2DModel_->AddRect(rect);
}

void NativeCanvasRenderer::Fill()
{
    auto fillRule = CanvasFillRule::NONZERO;

    renderingContext2DModel_->SetFillRuleForPath(fillRule);
}

void NativeCanvasRenderer::Clip()
{
    auto fillRule = CanvasFillRule::NONZERO;
    renderingContext2DModel_->SetClipRuleForPath(fillRule);
}

void NativeCanvasRenderer::Rotate(const double angle)
{
    renderingContext2DModel_->CanvasRendererRotate(angle);
}

void NativeCanvasRenderer::Scale(const double x, const double y)
{
    renderingContext2DModel_->CanvasRendererScale(x, y);
}

void NativeCanvasRenderer::Transform(const TransformParam& param)
{
    renderingContext2DModel_->Transform(param);
}

void NativeCanvasRenderer::SetTransform(TransformParam param)
{
    renderingContext2DModel_->SetTransform(param, true);
}

void NativeCanvasRenderer::Translate(const double x, const double y)
{
    renderingContext2DModel_->Translate(x, y);
}

void NativeCanvasRenderer::Restore()
{
    renderingContext2DModel_->Restore();
}

void NativeCanvasRenderer::Save()
{
    renderingContext2DModel_->CanvasRendererSave();
}

int64_t NativeCanvasRenderer::CreateLinearGradient(const double x0, const double y0, const double x1, const double y1)
{
    Offset beginOffset = Offset(x0, y0);
    Offset endOffset = Offset(x1, y1);

    Gradient gradient = Gradient();
    gradient.SetType(GradientType::LINEAR);
    gradient.SetBeginOffset(beginOffset);
    gradient.SetEndOffset(endOffset);

    auto nativeCanvasGradient = FFIData::Create<NativeCanvasGradient>(gradient);
    if (nativeCanvasGradient == nullptr) {
        return FFI_ERROR_CODE;
    }
    return nativeCanvasGradient->GetID();
}

int64_t NativeCanvasRenderer::CreateRadialGradient(
    const double x0, const double y0, const double r0, const double x1, const double y1, const double r1)
{
    Offset innerCenter = Offset(x0, y0);
    Offset outerCenter = Offset(x1, y1);

    Gradient gradient = Gradient();
    gradient.SetType(GradientType::RADIAL);
    gradient.SetBeginOffset(innerCenter);
    gradient.SetEndOffset(outerCenter);
    gradient.SetInnerRadius(r0);
    gradient.SetOuterRadius(r1);

    auto nativeCanvasGradient = FFIData::Create<NativeCanvasGradient>(gradient);
    if (nativeCanvasGradient == nullptr) {
        return FFI_ERROR_CODE;
    }
    return nativeCanvasGradient->GetID();
}

void NativeCanvasRenderer::DrawImage(const CanvasImage& image)
{
    ImageInfo imageInfo;
    imageInfo.image = image;
    imageInfo.isImage = true;
    renderingContext2DModel_->DrawImage(imageInfo);
}

void NativeCanvasRenderer::DrawImage(const RefPtr<OHOS::Ace::PixelMap>& pixelMap, const CanvasImage& image)
{
    ImageInfo imageInfo;
    imageInfo.image = image;
    imageInfo.isImage = false;
    imageInfo.pixelMap = pixelMap;
    renderingContext2DModel_->DrawPixelMap(imageInfo);
}

std::unique_ptr<ImageData> NativeCanvasRenderer::GetImageData(
    const double left, const double top, const double width, const double height)
{
    std::unique_ptr<ImageData> canvasData;
    ImageSize imageSize;
    imageSize.left = left;
    imageSize.top = top;
    imageSize.width = width;
    imageSize.height = height;
    canvasData = renderingContext2DModel_->GetImageData(imageSize);
    return canvasData;
}

int64_t NativeCanvasRenderer::GetPixelMap(double left, double top, double width, double height)
{
    auto finalHeight = static_cast<uint32_t>(std::abs(height));
    auto finalWidth = static_cast<uint32_t>(std::abs(width));
    if (finalHeight > 0 && finalWidth > (UINT32_MAX / finalHeight)) {
        return 0;
    }
    ImageSize imageSize;
    imageSize.left = left;
    imageSize.top = top;
    imageSize.width = finalWidth;
    imageSize.height = finalHeight;
    auto pixelmap = renderingContext2DModel_->GetPixelMap(imageSize);
    if (pixelmap) {
        auto ret = FFIData::Create<OHOS::Media::PixelMapImpl>(pixelmap->GetPixelMapSharedPtr());
        if (ret == nullptr) {
            return FFI_ERROR_CODE;
        }
        return ret->GetID();
    } else {
        LOGE("NativeCanvasRenderer GetPixelMap failed");
        return 0;
    }
}
} // namespace OHOS::Ace::Framework
