/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/canvas/canvas_rendering_context_2d_model_ng.h"

#include "securec.h"

#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map.h"
#endif

namespace OHOS::Ace::NG {

void CanvasRenderingContext2DModelNG::SetOnAttach(std::function<void()>&& callback)
{
    onContext2DAttach_ = std::move(callback);
}

void CanvasRenderingContext2DModelNG::SetOnDetach(std::function<void()>&& callback)
{
    onContext2DDetach_ = std::move(callback);
}

int32_t CanvasRenderingContext2DModelNG::GetId()
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, -1);
    return pattern->GetId();
}

void CanvasRenderingContext2DModelNG::OnAttachToCanvas()
{
    if (isAttached_) {
        return;
    }
    isAttached_ = true;
    if (onContext2DAttach_) {
        onContext2DAttach_();
    }
}

void CanvasRenderingContext2DModelNG::OnDetachFromCanvas()
{
    if (!isAttached_) {
        return;
    }
    isAttached_ = false;
    if (onContext2DDetach_) {
        onContext2DDetach_();
    }
    if (apiVersion_ > static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN)) {
        weakPattern_ = nullptr;
    }
}

void CanvasRenderingContext2DModelNG::SetPattern(RefPtr<AceType> newPattern)
{
    auto canvasPattern = AceType::DynamicCast<CanvasPattern>(newPattern);
    CHECK_NULL_VOID(canvasPattern);
    auto pattern = weakPattern_.Upgrade();
    if (isAttached_ && pattern == canvasPattern) {
        return;
    }

    // If the canvas has been attached with a context, detach the context first.
    canvasPattern->DetachRenderContext();

    // If the context is attached to a canvas, detach it from previous canvas.
    if (isAttached_ && pattern) {
        pattern->DetachRenderContext();
    }

    weakPattern_ = canvasPattern;
    auto OnAttach = [weakCtx = WeakClaim(this)]() {
        auto ctx = weakCtx.Upgrade();
        CHECK_NULL_VOID(ctx);
        ctx->OnAttachToCanvas();
    };
    auto OnDetach = [weakCtx = WeakClaim(this)]() {
        auto ctx = weakCtx.Upgrade();
        CHECK_NULL_VOID(ctx);
        ctx->OnDetachFromCanvas();
    };
    pattern = weakPattern_.Upgrade();
    pattern->SetOnContext2DAttach(OnAttach);
    pattern->SetOnContext2DDetach(OnDetach);
    pattern->AttachRenderContext();
}

void CanvasRenderingContext2DModelNG::Release()
{
    weakPattern_ = nullptr;
}

void CanvasRenderingContext2DModelNG::SetFillText(const PaintState& state, const FillTextInfo& fillTextInfo)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->FillText(fillTextInfo.text, fillTextInfo.x, fillTextInfo.y, fillTextInfo.maxWidth);
}

void CanvasRenderingContext2DModelNG::SetStrokeText(const PaintState& state, const FillTextInfo& fillTextInfo)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->StrokeText(fillTextInfo.text, fillTextInfo.x, fillTextInfo.y, fillTextInfo.maxWidth);
}

void CanvasRenderingContext2DModelNG::SetAntiAlias(bool anti)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->SetAntiAlias(anti);
}

void CanvasRenderingContext2DModelNG::SetFontWeight(const FontWeight& weight)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateFontWeight(weight);
}

void CanvasRenderingContext2DModelNG::SetFontStyle(const Ace::FontStyle& fontStyle)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateFontStyle(fontStyle);
}

void CanvasRenderingContext2DModelNG::SetFontFamilies(const std::vector<std::string>& families)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateFontFamilies(families);
}

void CanvasRenderingContext2DModelNG::SetFontSize(const Dimension& size)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateFontSize(size);
}

std::vector<double> CanvasRenderingContext2DModelNG::GetLineDash()
{
    auto pattern = weakPattern_.Upgrade();
    return pattern ? pattern->GetLineDash().lineDash : std::vector<double> {};
}

void CanvasRenderingContext2DModelNG::SetFillGradient(const std::shared_ptr<Ace::Gradient>& gradient)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->SetFillGradient(gradient);
}

void CanvasRenderingContext2DModelNG::SetFillPattern(const std::shared_ptr<Ace::Pattern>& acePattern)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateFillPattern(acePattern);
}

void CanvasRenderingContext2DModelNG::SetFillColor(const Color& color, bool colorFlag)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateFillColor(color);
}

void CanvasRenderingContext2DModelNG::SetStrokeGradient(const std::shared_ptr<Ace::Gradient>& gradient)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->SetStrokeGradient(gradient);
}

void CanvasRenderingContext2DModelNG::SetStrokePattern(const std::shared_ptr<Ace::Pattern>& acePattern)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateStrokePattern(acePattern);
}

void CanvasRenderingContext2DModelNG::SetStrokeColor(const Color& color, bool colorFlag)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateStrokeColor(color);
}

void CanvasRenderingContext2DModelNG::DrawImage(const ImageInfo& imageInfo)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->DrawImage(imageInfo.image, imageInfo.imgWidth, imageInfo.imgHeight);
}

void CanvasRenderingContext2DModelNG::DrawSvgImage(const ImageInfo& imageInfo)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->DrawSvgImage(imageInfo.svgDom, imageInfo.image, imageInfo.imageFit);
}

void CanvasRenderingContext2DModelNG::PutImageData(const Ace::ImageData& imageData)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->PutImageData(imageData);
}

void CanvasRenderingContext2DModelNG::CloseImageBitmap(const std::string& src)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->CloseImageBitmap(src);
}

std::unique_ptr<Ace::ImageData> CanvasRenderingContext2DModelNG::GetImageData(const ImageSize& imageSize)
{
    std::unique_ptr<Ace::ImageData> data;
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, data);
    return pattern->GetImageData(imageSize.left, imageSize.top, imageSize.width, imageSize.height);
}

void CanvasRenderingContext2DModelNG::DrawPixelMap(const ImageInfo& imageInfo)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->DrawPixelMap(imageInfo.pixelMap, imageInfo.image);
}

void CanvasRenderingContext2DModelNG::SetFilterParam(const std::string& src)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->SetFilterParam(src);
}

void CanvasRenderingContext2DModelNG::SetTextDirection(const TextDirection& direction)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->SetTextDirection(direction);
}

std::string CanvasRenderingContext2DModelNG::GetJsonData(const std::string& path)
{
    auto pattern = weakPattern_.Upgrade();
    return pattern ? pattern->GetJsonData(path) : "";
}

std::string CanvasRenderingContext2DModelNG::ToDataURL(const std::string& dataUrl, double quality)
{
    auto pattern = weakPattern_.Upgrade();
    return pattern ? pattern->ToDataURL(dataUrl, quality) : "";
}

void CanvasRenderingContext2DModelNG::SetLineCap(const LineCapStyle& lineCap)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateLineCap(lineCap);
}

void CanvasRenderingContext2DModelNG::SetLineJoin(const LineJoinStyle& lineJoin)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateLineJoin(lineJoin);
}

void CanvasRenderingContext2DModelNG::SetMiterLimit(double limit)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateMiterLimit(limit);
}

void CanvasRenderingContext2DModelNG::SetLineWidth(double lineWidth)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateLineWidth(lineWidth);
}

void CanvasRenderingContext2DModelNG::SetGlobalAlpha(double alpha)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateGlobalAlpha(alpha);
}

void CanvasRenderingContext2DModelNG::SetCompositeType(const CompositeOperation& type)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateCompositeOperation(type);
}

void CanvasRenderingContext2DModelNG::SetLineDashOffset(double lineDashOffset)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateLineDashOffset(lineDashOffset);
}

void CanvasRenderingContext2DModelNG::SetShadowBlur(double blur)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateShadowBlur(blur);
}

void CanvasRenderingContext2DModelNG::SetShadowColor(const Color& color)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateShadowColor(color);
}

void CanvasRenderingContext2DModelNG::SetShadowOffsetX(double offsetX)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateShadowOffsetX(offsetX);
}

void CanvasRenderingContext2DModelNG::SetShadowOffsetY(double offsetY)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateShadowOffsetY(offsetY);
}

void CanvasRenderingContext2DModelNG::SetSmoothingEnabled(bool enabled)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateSmoothingEnabled(enabled);
}

void CanvasRenderingContext2DModelNG::SetSmoothingQuality(const std::string& quality)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateSmoothingQuality(quality);
}

void CanvasRenderingContext2DModelNG::MoveTo(double x, double y)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->MoveTo(x, y);
}

void CanvasRenderingContext2DModelNG::LineTo(double x, double y)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->LineTo(x, y);
}

void CanvasRenderingContext2DModelNG::BezierCurveTo(const BezierCurveParam& param)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->BezierCurveTo(param);
}

void CanvasRenderingContext2DModelNG::QuadraticCurveTo(const QuadraticCurveParam& param)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->QuadraticCurveTo(param);
}

void CanvasRenderingContext2DModelNG::ArcTo(const ArcToParam& param)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->ArcTo(param);
}

void CanvasRenderingContext2DModelNG::Arc(const ArcParam& param)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->Arc(param);
}

void CanvasRenderingContext2DModelNG::Ellipse(const EllipseParam& param)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->Ellipse(param);
}

void CanvasRenderingContext2DModelNG::SetFillRuleForPath(const CanvasFillRule& fillRule)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateFillRuleForPath(fillRule);
    pattern->Fill();
}

void CanvasRenderingContext2DModelNG::SetFillRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateFillRuleForPath2D(fillRule);
    pattern->Fill(path);
}

void CanvasRenderingContext2DModelNG::SetStrokeRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateFillRuleForPath2D(fillRule);
    pattern->Stroke(path);
}

void CanvasRenderingContext2DModelNG::SetStrokeRuleForPath(const CanvasFillRule& fillRule)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateFillRuleForPath(fillRule);
    pattern->Stroke();
}

void CanvasRenderingContext2DModelNG::SetClipRuleForPath(const CanvasFillRule& fillRule)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateFillRuleForPath(fillRule);
    pattern->Clip();
}

void CanvasRenderingContext2DModelNG::SetClipRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateFillRuleForPath2D(fillRule);
    pattern->Clip(path);
}

void CanvasRenderingContext2DModelNG::AddRect(const Rect& rect)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->AddRect(rect);
}

void CanvasRenderingContext2DModelNG::BeginPath()
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->BeginPath();
}

void CanvasRenderingContext2DModelNG::ClosePath()
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->ClosePath();
}

void CanvasRenderingContext2DModelNG::Restore()
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->Restore();
}

void CanvasRenderingContext2DModelNG::CanvasRendererSave()
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->Save();
}

void CanvasRenderingContext2DModelNG::CanvasRendererRotate(double angle)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->Rotate(angle);
}

void CanvasRenderingContext2DModelNG::CanvasRendererScale(double x, double y)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->Scale(x, y);
}

void CanvasRenderingContext2DModelNG::SetTransform(TransformParam& param, bool lengthFlag)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->SetTransform(param);
}

void CanvasRenderingContext2DModelNG::ResetTransform()
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->ResetTransform();
}

void CanvasRenderingContext2DModelNG::Transform(const TransformParam& param)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->Transform(param);
}

void CanvasRenderingContext2DModelNG::Translate(double x, double y)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->Translate(x, y);
}

void CanvasRenderingContext2DModelNG::SetLineDash(const std::vector<double>& lineDash)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateLineDash(lineDash);
}

void CanvasRenderingContext2DModelNG::SetTextAlign(const TextAlign& align)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateTextAlign(align);
}

void CanvasRenderingContext2DModelNG::SetTextBaseline(const TextBaseline& baseline)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateTextBaseline(baseline);
}

void CanvasRenderingContext2DModelNG::FillRect(const Rect& rect)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->FillRect(rect);
}

void CanvasRenderingContext2DModelNG::StrokeRect(const Rect& rect)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->StrokeRect(rect);
}

void CanvasRenderingContext2DModelNG::ClearRect(const Rect& rect)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->ClearRect(rect);
}

TransformParam CanvasRenderingContext2DModelNG::GetTransform()
{
    auto pattern = weakPattern_.Upgrade();
    return pattern ? pattern->GetTransform() : TransformParam {};
}

RefPtr<Ace::PixelMap> CanvasRenderingContext2DModelNG::GetPixelMap(const ImageSize& imageSize)
{
#ifdef PIXEL_MAP_SUPPORTED
    // Create pixelmap
    OHOS::Media::InitializationOptions options;
    options.alphaType = OHOS::Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL;
    options.pixelFormat = OHOS::Media::PixelFormat::RGBA_8888;
    options.scaleMode = OHOS::Media::ScaleMode::CENTER_CROP;
    options.size.width = static_cast<int32_t>(std::abs(imageSize.width));
    options.size.height = static_cast<int32_t>(std::abs(imageSize.height));
    options.editable = true;
    auto pixelMap = Ace::PixelMap::Create(OHOS::Media::PixelMap::Create(options));
    CHECK_NULL_RETURN(pixelMap, nullptr);
    std::shared_ptr<Ace::ImageData> imageData = std::make_shared<Ace::ImageData>();
    imageData->pixelMap = pixelMap;
    imageData->dirtyX = static_cast<int32_t>(imageSize.left);
    imageData->dirtyY = static_cast<int32_t>(imageSize.top);
    imageData->dirtyWidth = static_cast<int32_t>(imageSize.width);
    imageData->dirtyHeight = static_cast<int32_t>(imageSize.height);
    GetImageData(imageData);
    return pixelMap;
#else
    return nullptr;
#endif
}

void CanvasRenderingContext2DModelNG::GetImageDataModel(const ImageSize& imageSize, uint8_t* buffer)
{
#ifdef PIXEL_MAP_SUPPORTED
    OHOS::Media::InitializationOptions options;
    options.alphaType = OHOS::Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL;
    options.pixelFormat = OHOS::Media::PixelFormat::RGBA_8888;
    options.scaleMode = OHOS::Media::ScaleMode::CENTER_CROP;
    options.size.width = static_cast<int32_t>(std::abs(imageSize.width));
    options.size.height = static_cast<int32_t>(std::abs(imageSize.height));
    options.editable = true;
    auto pixelMap = Ace::PixelMap::Create(OHOS::Media::PixelMap::Create(options));
    CHECK_NULL_VOID(pixelMap);
    std::shared_ptr<Ace::ImageData> imageData = std::make_shared<Ace::ImageData>();
    imageData->pixelMap = pixelMap;
    imageData->dirtyX = static_cast<int32_t>(imageSize.left);
    imageData->dirtyY = static_cast<int32_t>(imageSize.top);
    imageData->dirtyWidth = static_cast<int32_t>(imageSize.width);
    imageData->dirtyHeight = static_cast<int32_t>(imageSize.height);
    GetImageData(imageData);
    auto pixelsSize = pixelMap->GetRowBytes() * pixelMap->GetHeight();
    memcpy_s(buffer, pixelsSize, pixelMap->GetWritablePixels(), pixelsSize);
#else
    auto finalHeight = static_cast<uint32_t>(std::abs(imageSize.height));
    auto finalWidth = static_cast<uint32_t>(std::abs(imageSize.width));
    std::unique_ptr<Ace::ImageData> data = GetImageData(imageSize);
    CHECK_NULL_VOID(data);
    for (uint32_t idx = 0; idx < finalHeight * finalWidth; ++idx) {
        Color color = Color(data->data[idx]);
        buffer[4 * idx] = color.GetRed(); // 4 * idx: the 1st byte format: red.
        buffer[4 * idx + 1] = color.GetGreen(); // 4 * idx + 1: the 2nd byte format: green.
        buffer[4 * idx + 2] = color.GetBlue(); // 4 * idx + 2: the 3rd byte format: blue.
        buffer[4 * idx + 3] = color.GetAlpha(); // 4 * idx + 3: the 4th byte format: alpha.
    }
#endif
}

TextMetrics CanvasRenderingContext2DModelNG::GetMeasureTextMetrics(const PaintState& state, const std::string& text)
{
    auto pattern = weakPattern_.Upgrade();
    return pattern ? pattern->MeasureTextMetrics(text, state) : TextMetrics {};
}

void CanvasRenderingContext2DModelNG::GetImageData(const std::shared_ptr<Ace::ImageData>& imageData)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->GetImageData(imageData);
}

void CanvasRenderingContext2DModelNG::SaveLayer()
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->SaveLayer();
}

void CanvasRenderingContext2DModelNG::RestoreLayer()
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->RestoreLayer();
}

void CanvasRenderingContext2DModelNG::Reset()
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->Reset();
}

void CanvasRenderingContext2DModelNG::SetTransform(
    std::shared_ptr<Ace::Pattern> acePattern, const TransformParam& transform)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->SetTransform(acePattern, transform);
}

// All interfaces that only the 'CanvasRenderingContext2D' has.
void CanvasRenderingContext2DModelNG::GetWidth(double& width)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    width = pattern->GetWidth();
}

void CanvasRenderingContext2DModelNG::GetHeight(double& height)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    height = pattern->GetHeight();
}

void CanvasRenderingContext2DModelNG::SetDensity(double density)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->SetDensity(density);
}

#ifdef PIXEL_MAP_SUPPORTED
void CanvasRenderingContext2DModelNG::TransferFromImageBitmap(const RefPtr<AceType>& pixelMap)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto imagePixelMap = AceType::DynamicCast<PixelMap>(pixelMap);
    CHECK_NULL_VOID(imagePixelMap);
    pattern->TransferFromImageBitmap(imagePixelMap);
}
#else
void CanvasRenderingContext2DModelNG::TransferFromImageBitmap(const std::shared_ptr<Ace::ImageData>& imageData)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(imageData);
    pattern->TransferFromImageBitmap(*imageData);
}
#endif

void CanvasRenderingContext2DModelNG::StartImageAnalyzer(void* config, OnAnalyzedCallback& onAnalyzed)
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->StartImageAnalyzer(config, onAnalyzed);
}

void CanvasRenderingContext2DModelNG::StopImageAnalyzer()
{
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->StopImageAnalyzer();
}
} // namespace OHOS::Ace::NG
