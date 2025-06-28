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

#include <cstdint>
#include <string>
#include <vector>

#include "ffi_remote_data.h"

#include "base/utils/utils.h"
#include "bridge/cj_frontend/cppview/canvas_image_data.h"
#include "bridge/cj_frontend/cppview/canvas_pattern.h"
#include "bridge/cj_frontend/cppview/render_image.h"
#include "core/components/common/properties/paint_state.h"
#include "core/pipeline/base/constants.h"

using namespace OHOS;

namespace OHOS::Ace::Framework {
std::unordered_map<int32_t, std::shared_ptr<Pattern>> NativeCanvasRenderer::pattern_;
unsigned int NativeCanvasRenderer::patternCount_ = 0;
namespace {
const int EVEN_CHECK = 2;
constexpr int32_t ALPHA_INDEX = 3;
constexpr uint32_t PIXEL_SIZE = 4;
constexpr double DIFF = 1e-10;
const std::set<std::string> QUALITY_TYPE = { "low", "medium", "high" }; // Default value is low.
} // namespace

NativeCanvasRenderer::NativeCanvasRenderer(bool antialias) : FFIData()
{
    renderingContext2DModel_ = AceType::MakeRefPtr<NG::CanvasRenderingContext2DModelNG>();
    antialias_ = antialias;
    density_ = PipelineBase::GetCurrentDensity();
}

NativeCanvasRenderer::NativeCanvasRenderer() : FFIData()
{
    renderingContext2DModel_ = AceType::MakeRefPtr<NG::CanvasRenderingContext2DModelNG>();
    density_ = PipelineBase::GetCurrentDensity();
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

void NativeCanvasRenderer::SetFillStyle(const sptr<NativeCanvasPattern>& nativeCanvasPattern)
{
    auto id = nativeCanvasPattern->GetId();
    renderingContext2DModel_->SetFillPattern(GetPatternPtr(id));
}

void NativeCanvasRenderer::SetLineWidth(const double lineWidth)
{
    renderingContext2DModel_->SetLineWidth(lineWidth * GetDensity());
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

void NativeCanvasRenderer::SetStrokeStyle(const sptr<NativeCanvasPattern>& nativeCanvasPattern)
{
    auto id = nativeCanvasPattern->GetId();
    renderingContext2DModel_->SetStrokePattern(GetPatternPtr(id));
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
    renderingContext2DModel_->SetMiterLimit(limit * GetDensity());
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

    paintState_.SetFontWeight(weight);
    paintState_.SetFontStyle(fontStyle);
    paintState_.SetFontFamilies(families);
    paintState_.SetFontSize(fontSize);
    style_.SetFontStyle(fontStyle);
    style_.SetFontWeight(weight);
    style_.SetFontSize(fontSize);
    style_.SetFontFamilies(families);
}

void NativeCanvasRenderer::SetTextAlign(const TextAlign align)
{
    paintState_.SetTextAlign(align);
    renderingContext2DModel_->SetTextAlign(align);
}

void NativeCanvasRenderer::SetTextBaseline(const TextBaseline baseline)
{
    paintState_.SetTextBaseline(baseline);
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
    double density = GetDensity();
    for (auto i = 0U; i < lineDash.size(); i++) {
        lineDash[i] *= density;
    }
    renderingContext2DModel_->SetLineDash(lineDash);
}

std::vector<double> NativeCanvasRenderer::GetLineDash()
{
    std::vector<double> lineDash = renderingContext2DModel_->GetLineDash();
    double density = !NearZero(GetDensity()) ? GetDensity() : 1.0;
    for (auto i = 0U; i < lineDash.size(); i++) {
        lineDash[i] /= density;
    }
    return lineDash;
}

void NativeCanvasRenderer::SetLineDashOffset(const double lineDashOffset)
{
    renderingContext2DModel_->SetLineDashOffset(lineDashOffset * GetDensity());
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
    renderingContext2DModel_->SetShadowOffsetX(offsetX * GetDensity());
}

void NativeCanvasRenderer::SetShadowOffsetY(const double offsetY)
{
    renderingContext2DModel_->SetShadowOffsetX(offsetY * GetDensity());
}

void NativeCanvasRenderer::SetImageSmoothingEnabled(const bool enabled)
{
    renderingContext2DModel_->SetSmoothingEnabled(enabled);
}

void NativeCanvasRenderer::SetImageSmoothingQuality(const std::string& quality)
{
    if ((QUALITY_TYPE.find(quality) != QUALITY_TYPE.end())) {
        renderingContext2DModel_->SetSmoothingQuality(quality);
    } else {
        LOGE("canvas error: Wrong quality");
    }
}

std::string NativeCanvasRenderer::ToDataURL(const std::string& dataUrl, double quality)
{
    std::string result = renderingContext2DModel_->ToDataURL(dataUrl, quality);
    return result;
}

void NativeCanvasRenderer::FillRect(const Rect& rect)
{
    renderingContext2DModel_->FillRect(rect * GetDensity());
}

void NativeCanvasRenderer::StrokeRect(const Rect& rect)
{
    renderingContext2DModel_->StrokeRect(rect * GetDensity());
}

void NativeCanvasRenderer::ClearRect(const Rect& rect)
{
    renderingContext2DModel_->ClearRect(rect * GetDensity());
}

void NativeCanvasRenderer::FillText(const double x, const double y, const std::string& text)
{
    double density = GetDensity();
    FillTextInfo textInfo;
    textInfo.text = text;
    textInfo.x = x * density;
    textInfo.y = y * density;
    renderingContext2DModel_->SetFillText(paintState_, textInfo);
}

void NativeCanvasRenderer::FillText(double x, double y, const std::string& text, double maxWidth)
{
    double density = GetDensity();
    FillTextInfo textInfo;
    textInfo.text = text;
    textInfo.x = x * density;
    textInfo.y = y * density;
    textInfo.maxWidth = maxWidth * density;
    renderingContext2DModel_->SetFillText(paintState_, textInfo);
}

void NativeCanvasRenderer::StrokeText(const double x, const double y, const std::string& text)
{
    FillTextInfo textInfo;
    double density = GetDensity();
    textInfo.text = text;
    textInfo.x = x * density;
    textInfo.y = y * density;
    renderingContext2DModel_->SetStrokeText(paintState_, textInfo);
}

void NativeCanvasRenderer::StrokeText(double x, double y, const std::string& text, double maxWidth)
{
    FillTextInfo textInfo;
    double density = GetDensity();
    textInfo.text = text;
    textInfo.x = x * density;
    textInfo.y = y * density;
    textInfo.maxWidth = maxWidth * density;
    renderingContext2DModel_->SetStrokeText(paintState_, textInfo);
}

Metrics NativeCanvasRenderer::MeasureText(const std::string& text)
{
    paintState_.SetTextStyle(style_);

    double density = Positive(GetDensity()) ? GetDensity() : 1;
    TextMetrics textMetrics = renderingContext2DModel_->GetMeasureTextMetrics(paintState_, text);
    double width = textMetrics.width / density;
    double height = textMetrics.height / density;
    double actualBoundingBoxLeft = textMetrics.actualBoundingBoxLeft / density;
    double actualBoundingBoxRight = textMetrics.actualBoundingBoxRight / density;
    double actualBoundingBoxAscent = textMetrics.actualBoundingBoxAscent / density;
    double actualBoundingBoxDescent = textMetrics.actualBoundingBoxDescent / density;
    double alphabeticBaseline = textMetrics.alphabeticBaseline / density;
    double emHeightAscent = textMetrics.emHeightAscent / density;
    double emHeightDescent = textMetrics.emHeightDescent / density;
    double fontBoundingBoxAscent = textMetrics.fontBoundingBoxAscent / density;
    double fontBoundingBoxDescent = textMetrics.fontBoundingBoxDescent / density;
    double hangingBaseline = textMetrics.hangingBaseline / density;
    double ideographicBaseline = textMetrics.ideographicBaseline / density;

    Metrics metrics = { width, height, actualBoundingBoxLeft, actualBoundingBoxRight, actualBoundingBoxAscent,
        actualBoundingBoxDescent, alphabeticBaseline, emHeightAscent, emHeightDescent, fontBoundingBoxAscent,
        fontBoundingBoxDescent, hangingBaseline, ideographicBaseline };
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
    double density = GetDensity();
    renderingContext2DModel_->MoveTo(x * density, y * density);
}

void NativeCanvasRenderer::LineTo(const double x, const double y)
{
    double density = GetDensity();
    renderingContext2DModel_->LineTo(x * density, y * density);
}

void NativeCanvasRenderer::ClosePath()
{
    renderingContext2DModel_->ClosePath();
}

void NativeCanvasRenderer::BezierCurveTo(const BezierCurveParam& param)
{
    double density = GetDensity();
    BezierCurveParam beParam;
    beParam.cp1x = param.cp1x * density;
    beParam.cp1y = param.cp1y * density;
    beParam.cp2x = param.cp2x * density;
    beParam.cp2y = param.cp2y * density;
    beParam.x = param.x * density;
    beParam.y = param.y * density;
    renderingContext2DModel_->BezierCurveTo(beParam);
}

void NativeCanvasRenderer::QuadraticCurveTo(const QuadraticCurveParam& param)
{
    double density = GetDensity();
    QuadraticCurveParam quParam;
    quParam.cpx = param.cpx * density;
    quParam.cpy = param.cpy * density;
    quParam.x = param.x * density;
    quParam.y = param.y * density;
    renderingContext2DModel_->QuadraticCurveTo(quParam);
}

void NativeCanvasRenderer::Arc(const ArcParam& param)
{
    ArcParam arcParam = param;
    double density = GetDensity();
    arcParam.x = param.x * density;
    arcParam.y = param.y * density;
    arcParam.radius = param.radius * density;
    renderingContext2DModel_->Arc(arcParam);
}

void NativeCanvasRenderer::ArcTo(const ArcToParam& param)
{
    ArcToParam arcToParam;
    double density = GetDensity();
    arcToParam.x1 = param.x1 * density;
    arcToParam.y1 = param.y1 * density;
    arcToParam.x2 = param.x2 * density;
    arcToParam.y2 = param.y2 * density;
    arcToParam.radius = param.radius * density;
    renderingContext2DModel_->ArcTo(arcToParam);
}

void NativeCanvasRenderer::Ellipse(const EllipseParam& param)
{
    EllipseParam elParam = param;
    double density = GetDensity();
    elParam.x = param.x * density;
    elParam.y = param.y * density;
    elParam.radiusX = param.radiusX * density;
    elParam.radiusY = param.radiusY * density;
    renderingContext2DModel_->Ellipse(elParam);
}

void NativeCanvasRenderer::SaveLayer()
{
    renderingContext2DModel_->SaveLayer();
}

void NativeCanvasRenderer::NormalRect(const Rect& rect)
{
    renderingContext2DModel_->AddRect(rect * GetDensity());
}

void NativeCanvasRenderer::Fill()
{
    auto fillRule = CanvasFillRule::NONZERO;

    renderingContext2DModel_->SetFillRuleForPath(fillRule);
}

void NativeCanvasRenderer::Fill(const std::string& ruleStr)
{
    auto fillRule = ruleStr == "evenodd" ? CanvasFillRule::EVENODD : CanvasFillRule::NONZERO;
    renderingContext2DModel_->SetFillRuleForPath(fillRule);
    return;
}

void NativeCanvasRenderer::Fill(const sptr<NativeCanvasPath>& canvasPath, const std::string& ruleStr)
{
    auto fillRule = ruleStr == "evenodd" ? CanvasFillRule::EVENODD : CanvasFillRule::NONZERO;
    auto path = canvasPath->GetCanvasPath2d();
    renderingContext2DModel_->SetFillRuleForPath2D(fillRule, path);
}

void NativeCanvasRenderer::Clip()
{
    auto fillRule = CanvasFillRule::NONZERO;
    renderingContext2DModel_->SetClipRuleForPath(fillRule);
}

void NativeCanvasRenderer::Clip(const std::string& ruleStr)
{
    auto fillRule = ruleStr == "evenodd" ? CanvasFillRule::EVENODD : CanvasFillRule::NONZERO;
    renderingContext2DModel_->SetClipRuleForPath(fillRule);
    return;
}

void NativeCanvasRenderer::Clip(const sptr<NativeCanvasPath>& canvasPath, const std::string& ruleStr)
{
    auto fillRule = ruleStr == "evenodd" ? CanvasFillRule::EVENODD : CanvasFillRule::NONZERO;
    auto path = canvasPath->GetCanvasPath2d();
    renderingContext2DModel_->SetClipRuleForPath2D(fillRule, path);
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
    double density = GetDensity();
    param.translateX *= density;
    param.translateY *= density;
    renderingContext2DModel_->SetTransform(param, true);
}

void NativeCanvasRenderer::SetTransform(unsigned int id, const TransformParam& transform)
{
    if (id >= 0 && id <= patternCount_) {
        renderingContext2DModel_->SetTransform(pattern_[id], transform);
    }
}

void NativeCanvasRenderer::SetTransformByMatrix(const sptr<NativeMatrix2d>& matrix2d)
{
    TransformParam param = matrix2d->GetTransform();
    renderingContext2DModel_->SetTransform(param, false);
}

void NativeCanvasRenderer::ResetTransform()
{
    renderingContext2DModel_->ResetTransform();
}

void NativeCanvasRenderer::Translate(const double x, const double y)
{
    double density = GetDensity();
    renderingContext2DModel_->Translate(x * density, y * density);
}

void NativeCanvasRenderer::Restore()
{
    if (!savePaintState_.empty()) {
        paintState_ = savePaintState_.back();
        savePaintState_.pop_back();
    }
    renderingContext2DModel_->Restore();
}

void NativeCanvasRenderer::Save()
{
    savePaintState_.push_back(paintState_);
    renderingContext2DModel_->CanvasRendererSave();
}

int64_t NativeCanvasRenderer::CreateLinearGradient(const double x0, const double y0, const double x1, const double y1)
{
    double density = GetDensity();
    Offset beginOffset = Offset(x0 * density, y0 * density);
    Offset endOffset = Offset(x1 * density, y1 * density);

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
    double density = GetDensity();
    Offset innerCenter = Offset(x0 * density, y0 * density);
    Offset outerCenter = Offset(x1 * density, y1 * density);

    Gradient gradient = Gradient();
    gradient.SetType(GradientType::RADIAL);
    gradient.SetBeginOffset(innerCenter);
    gradient.SetEndOffset(outerCenter);
    gradient.SetInnerRadius(r0 * density);
    gradient.SetOuterRadius(r1 * density);

    auto nativeCanvasGradient = FFIData::Create<NativeCanvasGradient>(gradient);
    if (nativeCanvasGradient == nullptr) {
        return FFI_ERROR_CODE;
    }
    return nativeCanvasGradient->GetID();
}

int64_t NativeCanvasRenderer::CreateConicGradient(const double startAngle, const double x, const double y)
{
    double density = GetDensity();
    Gradient gradient = Gradient();
    gradient.SetType(GradientType::CONIC);
    gradient.GetConicGradient().startAngle = AnimatableDimension(Dimension(fmod(startAngle, (EVEN_CHECK * ACE_PI))));
    gradient.GetConicGradient().centerX = AnimatableDimension(Dimension(x * density));
    gradient.GetConicGradient().centerY = AnimatableDimension(Dimension(y * density));

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

int64_t NativeCanvasRenderer::GetNativeImageData(
    const double left, const double top, const double width, const double height)
{
    ImageSize imageSize;
    double density = GetDensity();
    imageSize.left = left * density;
    imageSize.top = top * density;
    imageSize.width = width * density + DIFF;
    imageSize.height = height * density + DIFF;

    uint32_t finalWidth = static_cast<uint32_t>(std::abs(imageSize.width));
    uint32_t finalHeight = static_cast<uint32_t>(std::abs(imageSize.height));
    int32_t length = static_cast<int32_t>(finalHeight * finalWidth * 4);
    std::vector<uint8_t> buffer(length, 0xff);
    auto imagdata = FFI::FFIData::Create<NativeImageData>();
    if (finalHeight > 0 && finalWidth > (UINT32_MAX / finalHeight)) {
        imagdata->height_ = 0;
        imagdata->width_ = 0;
        imagdata->data = buffer;
        return imagdata->GetID();
    }
    renderingContext2DModel_->GetImageDataModel(imageSize, buffer.data());
    imagdata->height_ = static_cast<int32_t>(finalHeight);
    imagdata->width_ = static_cast<int32_t>(finalWidth);
    imagdata->data = buffer;
    return imagdata->GetID();
}

int64_t NativeCanvasRenderer::GetPixelMap(double left, double top, double width, double height)
{
    auto finalHeight = static_cast<uint32_t>(std::abs(height));
    auto finalWidth = static_cast<uint32_t>(std::abs(width));
    if (finalHeight > 0 && finalWidth > (UINT32_MAX / finalHeight)) {
        return 0;
    }
    double density = GetDensity();
    ImageSize imageSize;
    imageSize.left = left * density;
    imageSize.top = top * density;
    imageSize.width = finalWidth * density + DIFF;
    imageSize.height = finalHeight * density + DIFF;
    finalHeight = static_cast<uint32_t>(std::abs(imageSize.height));
    finalHeight = static_cast<uint32_t>(std::abs(imageSize.width));
    if (height > 0 && width > (UINT32_MAX / height)) {
        LOGE("NativeCanvasRenderer GetPixelMap failed");
        return 0;
    }
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

void NativeCanvasRenderer::SetFilter(const std::string& filterStr)
{
    renderingContext2DModel_->SetFilterParam(filterStr);
}

void NativeCanvasRenderer::SetDirection(const std::string& directionStr)
{
    auto direction = ConvertStrToTextDirection(directionStr);
    renderingContext2DModel_->SetTextDirection(direction);
}

std::string NativeCanvasRenderer::GetJsonData(const std::string& path)
{
    std::string jsonData = renderingContext2DModel_->GetJsonData(path);
    return jsonData;
}

void NativeCanvasRenderer::RestoreLayer()
{
    renderingContext2DModel_->RestoreLayer();
}

void NativeCanvasRenderer::Reset()
{
    paintState_ = PaintState();
    std::vector<PaintState>().swap(savePaintState_);
    isInitializeShadow_ = false;
    renderingContext2DModel_->Reset();
}

int64_t NativeCanvasRenderer::CreatePattern(int64_t bitMapId, const std::string& repeat)
{
    auto renderImage = FFIData::GetData<CJRenderImage>(bitMapId);
    if (renderImage == nullptr) {
        LOGE("canvas createCanvasPattern error, Cannot get CJRenderImage by id: %{public}" PRId64, bitMapId);
        return 0;
    }
    auto pattern = std::make_shared<Pattern>();
    pattern->SetImgSrc(renderImage->GetSrc());
    pattern->SetImageWidth(renderImage->GetWidth());
    pattern->SetImageHeight(renderImage->GetHeight());
    pattern->SetRepetition(repeat);
#if !defined(PREVIEW)
    auto pixelMap = renderImage->GetPixelMap();
    pattern->SetPixelMap(pixelMap);
#endif

    pattern_[patternCount_] = pattern;
    auto nativeCanvasPattern = FFIData::Create<NativeCanvasPattern>();
    if (nativeCanvasPattern == nullptr) {
        return FFI_ERROR_CODE;
    }
    nativeCanvasPattern->SetCanvasRenderer(this);
    nativeCanvasPattern->SetId(patternCount_);
    nativeCanvasPattern->SetUnit(GetUnit());
    patternCount_++;
    return nativeCanvasPattern->GetID();
}

std::shared_ptr<Pattern> NativeCanvasRenderer::GetPatternPtr(int32_t id)
{
    if (id < 0 || id >= static_cast<int32_t>(pattern_.size())) {
        return std::shared_ptr<Pattern>();
    }
    return pattern_[id];
}

int64_t NativeCanvasRenderer::GetTransform()
{
    TransformParam param = renderingContext2DModel_->GetTransform();
    auto nativeMatrix2d = FFIData::Create<NativeMatrix2d>();
    nativeMatrix2d->SetTransform(param);
    return nativeMatrix2d->GetID();
}

void NativeCanvasRenderer::SetPixelMap(const RefPtr<OHOS::Ace::PixelMap>& pixelMap)
{
#if !defined(PREVIEW)
    ImageInfo imageInfo;
    imageInfo.pixelMap = pixelMap;
    renderingContext2DModel_->DrawPixelMap(imageInfo);
#endif
}

void NativeCanvasRenderer::SetDensity()
{
    double density = GetDensity(true);
    renderingContext2DModel_->SetDensity(density);
}

std::string NativeCanvasRenderer::ToDataUrl(const std::string type, const double quality)
{
    std::string result = renderingContext2DModel_->ToDataURL(type, quality);
    return result;
}

double NativeCanvasRenderer::GetWidth()
{
    double width = 0.0;
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_RETURN(canvasRenderingContext2DModel, -1);
    canvasRenderingContext2DModel->GetWidth(width);
    double density = !NearZero(GetDensity()) ? GetDensity() : 1.0;
    width /= density;
    return width;
}

double NativeCanvasRenderer::GetHeight()
{
    double height = 0.0;
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_RETURN(canvasRenderingContext2DModel, -1);
    canvasRenderingContext2DModel->GetHeight(height);
    double density = !NearZero(GetDensity()) ? GetDensity() : 1.0;
    height /= density;
    return height;
}

void NativeCanvasRenderer::TransferFromImageBitmap(const sptr<CJRenderImage> cjImage)
{
    auto canvasRenderingContext2DModel = AceType::DynamicCast<CanvasRenderingContext2DModel>(renderingContext2DModel_);
    CHECK_NULL_VOID(canvasRenderingContext2DModel);
#ifdef PIXEL_MAP_SUPPORTED
    canvasRenderingContext2DModel->TransferFromImageBitmap(cjImage->GetPixelMap());
#else
    auto imageData = cjImage->imageData;
    CHECK_NULL_VOID(imageData);
    canvasRenderingContext2DModel->TransferFromImageBitmap(imageData);
#endif
}

int64_t NativeCanvasRenderer::CreateImageData(const double height, const double width)
{
    auto imageData = FFIData::Create<NativeImageData>();
    double density = GetDensity();
    int32_t finalWidth = static_cast<int32_t>(std::abs(width * density + DIFF));
    int32_t finalHeight = static_cast<int32_t>(std::abs(height * density + DIFF));
    int32_t result = finalWidth * finalHeight * PIXEL_SIZE;
    std::vector<uint8_t> bufferArray;
    for (int32_t i = 0; i < result; i++) {
        bufferArray.emplace_back(0xff);
    }
    imageData->height_ = finalHeight;
    imageData->width_ = finalHeight;
    imageData->data = bufferArray;
    return imageData->GetID();
}

int64_t NativeCanvasRenderer::CreateImageData(const sptr<NativeImageData> imageData)
{
    auto ret = FFIData::Create<NativeImageData>();
    double density = GetDensity();
    int32_t finalWidth = static_cast<int32_t>(std::abs(imageData->width_ * density + DIFF));
    int32_t finalHeight = static_cast<int32_t>(std::abs(imageData->height_ * density + DIFF));
    int32_t result = finalWidth * finalHeight * PIXEL_SIZE;
    std::vector<uint8_t> bufferArray;
    for (int32_t i = 0; i < result; i++) {
        bufferArray.emplace_back(0xff);
    }
    ret->height_ = finalHeight;
    ret->width_ = finalHeight;
    ret->data = bufferArray;
    return ret->GetID();
}

void NativeCanvasRenderer::PutImageData(const sptr<NativeImageData> imageData, const double dx, const double dy,
    const double dirtyX, const double dirtyY, const double dirtyWidth, const double dirtyHeight)
{
    double density = GetDensity();
    int32_t imgWidth = imageData->GetWidth();
    int32_t imgHeight = imageData->GetHeight();
    ImageData imageData_ = { .dirtyWidth = imgWidth, .dirtyHeight = imgHeight };
    imageData_.x = static_cast<int32_t>(dx * density);
    imageData_.y = static_cast<int32_t>(dy * density);
    imageData_.dirtyX = static_cast<int32_t>(dirtyX * density);
    imageData_.dirtyY = static_cast<int32_t>(dirtyY * density);
    imageData_.dirtyHeight = static_cast<int32_t>(dirtyHeight * density);
    imageData_.dirtyWidth = static_cast<int32_t>(dirtyWidth * density);
    imageData_.dirtyWidth = imageData_.dirtyX < 0 ? std::min(imageData_.dirtyX + imageData_.dirtyWidth, imgWidth)
                                                  : std::min(imgWidth - imageData_.dirtyX, imageData_.dirtyWidth);
    imageData_.dirtyHeight = imageData_.dirtyY < 0 ? std::min(imageData_.dirtyY + imageData_.dirtyHeight, imgHeight)
                                                   : std::min(imgHeight - imageData_.dirtyY, imageData_.dirtyHeight);
    auto buffer = imageData->data;
    int32_t bufferLength = static_cast<int32_t>(buffer.size());
    imageData_.data = std::vector<uint32_t>();
    for (int32_t i = std::max(imageData_.dirtyY, 0); i < imageData_.dirtyY + imageData_.dirtyHeight; ++i) {
        for (int32_t j = std::max(imageData_.dirtyX, 0); j < imageData_.dirtyX + imageData_.dirtyWidth; ++j) {
            uint32_t idx = static_cast<uint32_t>(4 * (j + imgWidth * i));
            if (bufferLength > static_cast<int32_t>(idx + ALPHA_INDEX)) {
                uint8_t alpha = buffer[idx + 3]; // idx + 3: The 4th byte format: alpha
                uint8_t red = buffer[idx];       // idx: the 1st byte format: red
                uint8_t green = buffer[idx + 1]; // idx + 1: The 2nd byte format: green
                uint8_t blue = buffer[idx + 2];  // idx + 2: The 3rd byte format: blue
                imageData_.data.emplace_back(Color::FromARGB(alpha, red, green, blue).GetValue());
            }
        }
    }
    renderingContext2DModel_->PutImageData(imageData_);
}

void NativeCanvasRenderer::PutImageData(const sptr<NativeImageData> imageData, const double dx, const double dy)
{
    double density = GetDensity();
    int32_t imgWidth = imageData->GetWidth();
    int32_t imgHeight = imageData->GetHeight();
    ImageData imageData_ = { .dirtyWidth = imgWidth, .dirtyHeight = imgHeight };
    imageData_.x = static_cast<int32_t>(dx * density);
    imageData_.y = static_cast<int32_t>(dy * density);
    imageData_.dirtyWidth = imageData_.dirtyX < 0 ? std::min(imageData_.dirtyX + imageData_.dirtyWidth, imgWidth)
                                                  : std::min(imgWidth - imageData_.dirtyX, imageData_.dirtyWidth);
    imageData_.dirtyHeight = imageData_.dirtyY < 0 ? std::min(imageData_.dirtyY + imageData_.dirtyHeight, imgHeight)
                                                   : std::min(imgHeight - imageData_.dirtyY, imageData_.dirtyHeight);
    auto buffer = imageData->data;
    int32_t bufferLength = static_cast<int32_t>(buffer.size());
    imageData_.data = std::vector<uint32_t>();
    for (int32_t i = std::max(imageData_.dirtyY, 0); i < imageData_.dirtyY + imageData_.dirtyHeight; ++i) {
        for (int32_t j = std::max(imageData_.dirtyX, 0); j < imageData_.dirtyX + imageData_.dirtyWidth; ++j) {
            uint32_t idx = static_cast<uint32_t>(4 * (j + imgWidth * i));
            if (bufferLength > static_cast<int32_t>(idx + ALPHA_INDEX)) {
                uint8_t alpha = buffer[idx + 3]; // idx + 3: The 4th byte format: alpha
                uint8_t red = buffer[idx];       // idx: the 1st byte format: red
                uint8_t green = buffer[idx + 1]; // idx + 1: The 2nd byte format: green
                uint8_t blue = buffer[idx + 2];  // idx + 2: The 3rd byte format: blue
                imageData_.data.emplace_back(Color::FromARGB(alpha, red, green, blue).GetValue());
            }
        }
    }
    renderingContext2DModel_->PutImageData(imageData_);
}
} // namespace OHOS::Ace::Framework
