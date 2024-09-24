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
    CHECK_NULL_RETURN(pattern_, -1);
    return pattern_->GetId();
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
    pattern_ = nullptr;
}

void CanvasRenderingContext2DModelNG::SetPattern(RefPtr<AceType> pattern)
{
    auto canvasPattern = AceType::DynamicCast<CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    if (pattern_ == canvasPattern) {
        return;
    }

    if (isAttached_ && pattern_) {
        pattern_->DetachRenderContext();
    }

    pattern_ = canvasPattern;
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
    pattern_->SetOnContext2DAttach(OnAttach);
    pattern_->SetOnContext2DDetach(OnDetach);
    pattern_->AttachRenderContext();
}

void CanvasRenderingContext2DModelNG::Release()
{
    pattern_ = nullptr;
}

void CanvasRenderingContext2DModelNG::SetFillText(const PaintState& state, const FillTextInfo& fillTextInfo)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->FillText(fillTextInfo.text, fillTextInfo.x, fillTextInfo.y, fillTextInfo.maxWidth);
}

void CanvasRenderingContext2DModelNG::SetStrokeText(const PaintState& state, const FillTextInfo& fillTextInfo)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->StrokeText(fillTextInfo.text, fillTextInfo.x, fillTextInfo.y, fillTextInfo.maxWidth);
}

void CanvasRenderingContext2DModelNG::SetAntiAlias(bool anti)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetAntiAlias(anti);
}

void CanvasRenderingContext2DModelNG::SetFontWeight(const FontWeight& weight)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFontWeight(weight);
}

void CanvasRenderingContext2DModelNG::SetFontStyle(const Ace::FontStyle& fontStyle)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFontStyle(fontStyle);
}

void CanvasRenderingContext2DModelNG::SetFontFamilies(const std::vector<std::string>& families)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFontFamilies(families);
}

void CanvasRenderingContext2DModelNG::SetFontSize(const Dimension& size)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFontSize(size);
}

std::vector<double> CanvasRenderingContext2DModelNG::GetLineDash()
{
    return pattern_ ? pattern_->GetLineDash().lineDash : std::vector<double> {};
}

void CanvasRenderingContext2DModelNG::SetFillGradient(const std::shared_ptr<Ace::Gradient>& gradient)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetFillGradient(gradient);
}

void CanvasRenderingContext2DModelNG::SetFillPattern(const std::shared_ptr<Ace::Pattern>& pattern)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFillPattern(pattern);
}

void CanvasRenderingContext2DModelNG::SetFillColor(const Color& color, bool colorFlag)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFillColor(color);
}

void CanvasRenderingContext2DModelNG::SetStrokeGradient(const std::shared_ptr<Ace::Gradient>& gradient)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetStrokeGradient(gradient);
}

void CanvasRenderingContext2DModelNG::SetStrokePattern(const std::shared_ptr<Ace::Pattern>& pattern)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateStrokePattern(pattern);
}

void CanvasRenderingContext2DModelNG::SetStrokeColor(const Color& color, bool colorFlag)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateStrokeColor(color);
}

void CanvasRenderingContext2DModelNG::DrawImage(const ImageInfo& imageInfo)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->DrawImage(imageInfo.image, imageInfo.imgWidth, imageInfo.imgHeight);
}

void CanvasRenderingContext2DModelNG::DrawSvgImage(const ImageInfo& imageInfo)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->DrawSvgImage(imageInfo.svgDom, imageInfo.image, imageInfo.imageFit);
}

void CanvasRenderingContext2DModelNG::PutImageData(const Ace::ImageData& imageData)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->PutImageData(imageData);
}

void CanvasRenderingContext2DModelNG::CloseImageBitmap(const std::string& src)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->CloseImageBitmap(src);
}

std::unique_ptr<Ace::ImageData> CanvasRenderingContext2DModelNG::GetImageData(const ImageSize& imageSize)
{
    std::unique_ptr<Ace::ImageData> data;
    CHECK_NULL_RETURN(pattern_, data);
    return pattern_->GetImageData(imageSize.left, imageSize.top, imageSize.width, imageSize.height);
}

void CanvasRenderingContext2DModelNG::DrawPixelMap(const ImageInfo& imageInfo)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->DrawPixelMap(imageInfo.pixelMap, imageInfo.image);
}

void CanvasRenderingContext2DModelNG::SetFilterParam(const std::string& src)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetFilterParam(src);
}

void CanvasRenderingContext2DModelNG::SetTextDirection(const TextDirection& direction)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetTextDirection(direction);
}

std::string CanvasRenderingContext2DModelNG::GetJsonData(const std::string& path)
{
    return pattern_ ? pattern_->GetJsonData(path) : "";
}

std::string CanvasRenderingContext2DModelNG::ToDataURL(const std::string& dataUrl, double quality)
{
    return pattern_ ? pattern_->ToDataURL(dataUrl, quality) : "";
}

void CanvasRenderingContext2DModelNG::SetLineCap(const LineCapStyle& lineCap)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateLineCap(lineCap);
}

void CanvasRenderingContext2DModelNG::SetLineJoin(const LineJoinStyle& lineJoin)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateLineJoin(lineJoin);
}

void CanvasRenderingContext2DModelNG::SetMiterLimit(double limit)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateMiterLimit(limit);
}

void CanvasRenderingContext2DModelNG::SetLineWidth(double lineWidth)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateLineWidth(lineWidth);
}

void CanvasRenderingContext2DModelNG::SetGlobalAlpha(double alpha)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateGlobalAlpha(alpha);
}

void CanvasRenderingContext2DModelNG::SetCompositeType(const CompositeOperation& type)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateCompositeOperation(type);
}

void CanvasRenderingContext2DModelNG::SetLineDashOffset(double lineDashOffset)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateLineDashOffset(lineDashOffset);
}

void CanvasRenderingContext2DModelNG::SetShadowBlur(double blur)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateShadowBlur(blur);
}

void CanvasRenderingContext2DModelNG::SetShadowColor(const Color& color)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateShadowColor(color);
}

void CanvasRenderingContext2DModelNG::SetShadowOffsetX(double offsetX)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateShadowOffsetX(offsetX);
}

void CanvasRenderingContext2DModelNG::SetShadowOffsetY(double offsetY)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateShadowOffsetY(offsetY);
}

void CanvasRenderingContext2DModelNG::SetSmoothingEnabled(bool enabled)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateSmoothingEnabled(enabled);
}

void CanvasRenderingContext2DModelNG::SetSmoothingQuality(const std::string& quality)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateSmoothingQuality(quality);
}

void CanvasRenderingContext2DModelNG::MoveTo(double x, double y)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->MoveTo(x, y);
}

void CanvasRenderingContext2DModelNG::LineTo(double x, double y)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->LineTo(x, y);
}

void CanvasRenderingContext2DModelNG::BezierCurveTo(const BezierCurveParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->BezierCurveTo(param);
}

void CanvasRenderingContext2DModelNG::QuadraticCurveTo(const QuadraticCurveParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->QuadraticCurveTo(param);
}

void CanvasRenderingContext2DModelNG::ArcTo(const ArcToParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->ArcTo(param);
}

void CanvasRenderingContext2DModelNG::Arc(const ArcParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Arc(param);
}

void CanvasRenderingContext2DModelNG::Ellipse(const EllipseParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Ellipse(param);
}

void CanvasRenderingContext2DModelNG::SetFillRuleForPath(const CanvasFillRule& fillRule)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFillRuleForPath(fillRule);
    pattern_->Fill();
}

void CanvasRenderingContext2DModelNG::SetFillRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFillRuleForPath2D(fillRule);
    pattern_->Fill(path);
}

void CanvasRenderingContext2DModelNG::SetStrokeRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFillRuleForPath2D(fillRule);
    pattern_->Stroke(path);
}

void CanvasRenderingContext2DModelNG::SetStrokeRuleForPath(const CanvasFillRule& fillRule)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFillRuleForPath(fillRule);
    pattern_->Stroke();
}

void CanvasRenderingContext2DModelNG::SetClipRuleForPath(const CanvasFillRule& fillRule)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFillRuleForPath(fillRule);
    pattern_->Clip();
}

void CanvasRenderingContext2DModelNG::SetClipRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFillRuleForPath2D(fillRule);
    pattern_->Clip(path);
}

void CanvasRenderingContext2DModelNG::AddRect(const Rect& rect)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->AddRect(rect);
}

void CanvasRenderingContext2DModelNG::BeginPath()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->BeginPath();
}

void CanvasRenderingContext2DModelNG::ClosePath()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->ClosePath();
}

void CanvasRenderingContext2DModelNG::Restore()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Restore();
}

void CanvasRenderingContext2DModelNG::CanvasRendererSave()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Save();
}

void CanvasRenderingContext2DModelNG::CanvasRendererRotate(double angle)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Rotate(angle);
}

void CanvasRenderingContext2DModelNG::CanvasRendererScale(double x, double y)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Scale(x, y);
}

void CanvasRenderingContext2DModelNG::SetTransform(TransformParam& param, bool lengthFlag)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetTransform(param);
}

void CanvasRenderingContext2DModelNG::ResetTransform()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->ResetTransform();
}

void CanvasRenderingContext2DModelNG::Transform(const TransformParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Transform(param);
}

void CanvasRenderingContext2DModelNG::Translate(double x, double y)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Translate(x, y);
}

void CanvasRenderingContext2DModelNG::SetLineDash(const std::vector<double>& lineDash)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateLineDash(lineDash);
}

void CanvasRenderingContext2DModelNG::SetTextAlign(const TextAlign& align)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateTextAlign(align);
}

void CanvasRenderingContext2DModelNG::SetTextBaseline(const TextBaseline& baseline)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateTextBaseline(baseline);
}

void CanvasRenderingContext2DModelNG::FillRect(const Rect& rect)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->FillRect(rect);
}

void CanvasRenderingContext2DModelNG::StrokeRect(const Rect& rect)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->StrokeRect(rect);
}

void CanvasRenderingContext2DModelNG::ClearRect(const Rect& rect)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->ClearRect(rect);
}

TransformParam CanvasRenderingContext2DModelNG::GetTransform()
{
    return pattern_ ? pattern_->GetTransform() : TransformParam {};
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
    return pattern_ ? pattern_->MeasureTextMetrics(text, state) : TextMetrics {};
}

void CanvasRenderingContext2DModelNG::GetImageData(const std::shared_ptr<Ace::ImageData>& imageData)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->GetImageData(imageData);
}

void CanvasRenderingContext2DModelNG::SaveLayer()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SaveLayer();
}

void CanvasRenderingContext2DModelNG::RestoreLayer()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->RestoreLayer();
}

void CanvasRenderingContext2DModelNG::Reset()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Reset();
}

void CanvasRenderingContext2DModelNG::SetTransform(
    std::shared_ptr<Ace::Pattern> pattern, const TransformParam& transform)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetTransform(pattern, transform);
}

// All interfaces that only the 'CanvasRenderingContext2D' has.
void CanvasRenderingContext2DModelNG::GetWidth(double& width)
{
    CHECK_NULL_VOID(pattern_);
    width = pattern_->GetWidth();
}

void CanvasRenderingContext2DModelNG::GetHeight(double& height)
{
    CHECK_NULL_VOID(pattern_);
    height = pattern_->GetHeight();
}

void CanvasRenderingContext2DModelNG::SetDensity(double density)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetDensity(density);
}

#ifdef PIXEL_MAP_SUPPORTED
void CanvasRenderingContext2DModelNG::TransferFromImageBitmap(const RefPtr<AceType>& pixelMap)
{
    CHECK_NULL_VOID(pattern_);
    auto imagePixelMap = AceType::DynamicCast<PixelMap>(pixelMap);
    CHECK_NULL_VOID(imagePixelMap);
    pattern_->TransferFromImageBitmap(imagePixelMap);
}
#else
void CanvasRenderingContext2DModelNG::TransferFromImageBitmap(const std::shared_ptr<Ace::ImageData>& imageData)
{
    CHECK_NULL_VOID(pattern_);
    CHECK_NULL_VOID(imageData);
    pattern_->TransferFromImageBitmap(*imageData);
}
#endif

void CanvasRenderingContext2DModelNG::StartImageAnalyzer(void* config, OnAnalyzedCallback& onAnalyzed)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->StartImageAnalyzer(config, onAnalyzed);
}

void CanvasRenderingContext2DModelNG::StopImageAnalyzer()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->StopImageAnalyzer();
}
} // namespace OHOS::Ace::NG
