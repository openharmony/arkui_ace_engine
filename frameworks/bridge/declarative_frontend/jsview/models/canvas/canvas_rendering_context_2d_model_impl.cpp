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

#include "bridge/declarative_frontend/jsview/models/canvas/canvas_rendering_context_2d_model_impl.h"

#include "core/components/custom_paint/custom_paint_component.h"

#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map.h"
#endif

namespace OHOS::Ace::Framework {
void CanvasRenderingContext2DModelImpl::SetPattern(RefPtr<AceType> pattern)
{
    pattern_ = AceType::DynamicCast<CanvasTaskPool>(pattern);
}

void CanvasRenderingContext2DModelImpl::SetFillText(const PaintState& state, const FillTextInfo& fillTextInfo)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->FillText(fillTextInfo.text, Offset(fillTextInfo.x, fillTextInfo.y));
}

void CanvasRenderingContext2DModelImpl::SetStrokeText(const PaintState& state, const FillTextInfo& fillTextInfo)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->StrokeText(fillTextInfo.text, Offset(fillTextInfo.x, fillTextInfo.y));
}

void CanvasRenderingContext2DModelImpl::SetAntiAlias(bool anti)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetAntiAlias(anti);
}

void CanvasRenderingContext2DModelImpl::SetFontWeight(const FontWeight& weight)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFontWeight(weight);
}

void CanvasRenderingContext2DModelImpl::SetFontStyle(const FontStyle& fontStyle)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFontStyle(fontStyle);
}

void CanvasRenderingContext2DModelImpl::SetFontFamilies(const std::vector<std::string>& families)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFontFamilies(families);
}

void CanvasRenderingContext2DModelImpl::SetFontSize(const Dimension& size)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFontSize(size);
}

std::vector<double> CanvasRenderingContext2DModelImpl::GetLineDash()
{
    return pattern_ ? pattern_->GetLineDash().lineDash : std::vector<double> {};
}

void CanvasRenderingContext2DModelImpl::SetFillGradient(const std::shared_ptr<Ace::Gradient>& gradient)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFillGradient(*gradient);
}

void CanvasRenderingContext2DModelImpl::SetFillPattern(const std::shared_ptr<Ace::Pattern>& pattern)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFillPattern(*(pattern.get()));
}

void CanvasRenderingContext2DModelImpl::SetFillColor(const Color& color, bool colorFlag)
{
    if (pattern_ && colorFlag) {
        pattern_->UpdateFillColor(color);
    }
}

void CanvasRenderingContext2DModelImpl::SetStrokeGradient(const std::shared_ptr<Ace::Gradient>& gradient)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateStrokeGradient(*gradient);
}

void CanvasRenderingContext2DModelImpl::SetStrokePattern(const std::shared_ptr<Ace::Pattern>& pattern)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateStrokePattern(*(pattern.get()));
}

void CanvasRenderingContext2DModelImpl::SetStrokeColor(const Color& color, bool colorFlag)
{
    if (pattern_ && colorFlag) {
        pattern_->UpdateStrokeColor(color);
    }
}

void CanvasRenderingContext2DModelImpl::DrawImage(const ImageInfo& imageInfo)
{
    CHECK_NULL_VOID(pattern_);
    if (imageInfo.isImage) {
        pattern_->DrawImage(imageInfo.image, imageInfo.imgWidth, imageInfo.imgHeight);
        return;
    }
    pattern_->DrawPixelMap(imageInfo.pixelMap, imageInfo.image);
}

void CanvasRenderingContext2DModelImpl::PutImageData(const ImageData& imageData)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->PutImageData(imageData);
}

std::unique_ptr<ImageData> CanvasRenderingContext2DModelImpl::GetImageData(const ImageSize& imageSize)
{
    return pattern_ ? pattern_->GetImageData(imageSize.left, imageSize.top, imageSize.width, imageSize.height)
                    : nullptr;
}

void CanvasRenderingContext2DModelImpl::DrawPixelMap(const ImageInfo& imageInfo)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->DrawPixelMap(imageInfo.pixelMap, imageInfo.image);
}

std::string CanvasRenderingContext2DModelImpl::GetJsonData(const std::string& path)
{
    return pattern_ ? pattern_->GetJsonData(path) : "";
}

std::string CanvasRenderingContext2DModelImpl::ToDataURL(const std::string& dataUrl, double quality)
{
    return pattern_ ? pattern_->ToDataURL(dataUrl + "," + std::to_string(quality)) : "";
}

void CanvasRenderingContext2DModelImpl::SetLineCap(const LineCapStyle& lineCap)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateLineCap(lineCap);
}

void CanvasRenderingContext2DModelImpl::SetLineJoin(const LineJoinStyle& lineJoin)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateLineJoin(lineJoin);
}

void CanvasRenderingContext2DModelImpl::SetMiterLimit(double limit)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateMiterLimit(limit);
}

void CanvasRenderingContext2DModelImpl::SetLineWidth(double lineWidth)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateLineWidth(lineWidth);
}

void CanvasRenderingContext2DModelImpl::SetGlobalAlpha(double alpha)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateGlobalAlpha(alpha);
}

void CanvasRenderingContext2DModelImpl::SetCompositeType(const CompositeOperation& type)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateCompositeOperation(type);
}

void CanvasRenderingContext2DModelImpl::SetLineDashOffset(double lineDashOffset)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateLineDashOffset(lineDashOffset);
}

void CanvasRenderingContext2DModelImpl::SetShadowBlur(double blur)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateShadowBlur(blur);
}

void CanvasRenderingContext2DModelImpl::SetShadowColor(const Color& color)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateShadowColor(color);
}

void CanvasRenderingContext2DModelImpl::SetShadowOffsetX(double offsetX)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateShadowOffsetX(offsetX);
}

void CanvasRenderingContext2DModelImpl::SetShadowOffsetY(double offsetY)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateShadowOffsetY(offsetY);
}

void CanvasRenderingContext2DModelImpl::SetSmoothingEnabled(bool enabled)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateSmoothingEnabled(enabled);
}

void CanvasRenderingContext2DModelImpl::SetSmoothingQuality(const std::string& quality)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateSmoothingQuality(quality);
}

void CanvasRenderingContext2DModelImpl::MoveTo(double x, double y)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->MoveTo(x, y);
}

void CanvasRenderingContext2DModelImpl::LineTo(double x, double y)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->LineTo(x, y);
}

void CanvasRenderingContext2DModelImpl::BezierCurveTo(const BezierCurveParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->BezierCurveTo(param);
}

void CanvasRenderingContext2DModelImpl::QuadraticCurveTo(const QuadraticCurveParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->QuadraticCurveTo(param);
}

void CanvasRenderingContext2DModelImpl::ArcTo(const ArcToParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->ArcTo(param);
}

void CanvasRenderingContext2DModelImpl::Arc(const ArcParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Arc(param);
}

void CanvasRenderingContext2DModelImpl::Ellipse(const EllipseParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Ellipse(param);
}

void CanvasRenderingContext2DModelImpl::SetFillRuleForPath(const CanvasFillRule& fillRule)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFillRuleForPath(fillRule);
    pattern_->Fill();
}

void CanvasRenderingContext2DModelImpl::SetFillRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFillRuleForPath2D(fillRule);
    pattern_->Fill(path);
}

void CanvasRenderingContext2DModelImpl::SetStrokeRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFillRuleForPath2D(fillRule);
    pattern_->Stroke(path);
}

void CanvasRenderingContext2DModelImpl::SetStrokeRuleForPath(const CanvasFillRule& fillRule)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFillRuleForPath(fillRule);
    pattern_->Stroke();
}

void CanvasRenderingContext2DModelImpl::SetClipRuleForPath(const CanvasFillRule& fillRule)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFillRuleForPath(fillRule);
    pattern_->Clip();
}

void CanvasRenderingContext2DModelImpl::SetClipRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateFillRuleForPath2D(fillRule);
    pattern_->Clip(path);
}

void CanvasRenderingContext2DModelImpl::AddRect(const Rect& rect)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->AddRect(rect);
}

void CanvasRenderingContext2DModelImpl::BeginPath()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->BeginPath();
}

void CanvasRenderingContext2DModelImpl::ClosePath()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->ClosePath();
}

void CanvasRenderingContext2DModelImpl::Restore()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Restore();
}

void CanvasRenderingContext2DModelImpl::CanvasRendererSave()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Save();
}

void CanvasRenderingContext2DModelImpl::CanvasRendererRotate(double angle)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Rotate(angle);
}

void CanvasRenderingContext2DModelImpl::CanvasRendererScale(double x, double y)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Scale(x, y);
}

void CanvasRenderingContext2DModelImpl::SetTransform(TransformParam& param, bool lengthFlag)
{
    if (!lengthFlag) {
        return;
    }
    std::swap(param.skewX, param.skewY);

    CHECK_NULL_VOID(pattern_);
    pattern_->SetTransform(param);
}

void CanvasRenderingContext2DModelImpl::ResetTransform()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->ResetTransform();
}

void CanvasRenderingContext2DModelImpl::Transform(const TransformParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Transform(param);
}

void CanvasRenderingContext2DModelImpl::Translate(double x, double y)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Translate(x, y);
}

void CanvasRenderingContext2DModelImpl::SetLineDash(const std::vector<double>& lineDash)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateLineDash(lineDash);
}

void CanvasRenderingContext2DModelImpl::SetTextAlign(const TextAlign& align)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateTextAlign(align);
}

void CanvasRenderingContext2DModelImpl::SetTextBaseline(const TextBaseline& baseline)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->UpdateTextBaseline(baseline);
}

double CanvasRenderingContext2DModelImpl::GetMeasureTextWidth(const PaintState& state, const std::string& text)
{
    return pattern_ ? pattern_->MeasureText(text, state) : 0.0;
}

double CanvasRenderingContext2DModelImpl::GetMeasureTextHeight(const PaintState& state, const std::string& text)
{
    return pattern_ ? pattern_->MeasureTextHeight(text, state) : 0.0;
}

void CanvasRenderingContext2DModelImpl::FillRect(const Rect& rect)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->FillRect(rect);
}

void CanvasRenderingContext2DModelImpl::StrokeRect(const Rect& rect)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->StrokeRect(rect);
}

void CanvasRenderingContext2DModelImpl::ClearRect(const Rect& rect)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->ClearRect(rect);
}

void CanvasRenderingContext2DModelImpl::DrawBitmapMesh(const BitmapMeshInfo& bitmapMeshInfo)
{
    CHECK_NULL_VOID(bitmapMeshInfo.pool);
    auto pool = AceType::DynamicCast<CanvasTaskPool>(bitmapMeshInfo.pool);
    CHECK_NULL_VOID(pool);
    CHECK_NULL_VOID(bitmapMeshInfo.offscreenPattern);
    auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(bitmapMeshInfo.offscreenPattern);
    CHECK_NULL_VOID(offscreenPattern);
    pool->DrawBitmapMesh(offscreenPattern, bitmapMeshInfo.mesh, bitmapMeshInfo.column, bitmapMeshInfo.row);
}

RefPtr<Ace::PixelMap> CanvasRenderingContext2DModelImpl::GetPixelMap(const ImageSize& imageSize)
{
#ifdef PIXEL_MAP_SUPPORTED
    // 1 Get data from canvas
    std::unique_ptr<ImageData> canvasData = GetImageData(imageSize);
    CHECK_NULL_RETURN(canvasData, nullptr);

    uint32_t finalHeight = static_cast<uint32_t>(std::abs(imageSize.height));
    uint32_t finalWidth = static_cast<uint32_t>(std::abs(imageSize.width));
    if (finalHeight > 0 && finalWidth > (UINT32_MAX / finalHeight)) {
        LOGE("Integer Overflow!!!the product of finalHeight and finalWidth is too big.");
        return nullptr;
    }
    uint32_t length = finalHeight * finalWidth;
    uint32_t* data = new uint32_t[length];
    for (uint32_t i = 0; i < finalHeight; i++) {
        for (uint32_t j = 0; j < finalWidth; j++) {
            uint32_t idx = i * finalWidth + j;
            data[idx] = canvasData->data[idx];
        }
    }

    // 2 Create pixelmap
    OHOS::Media::InitializationOptions options;
    options.alphaType = OHOS::Media::AlphaType::IMAGE_ALPHA_TYPE_OPAQUE;
    options.pixelFormat = OHOS::Media::PixelFormat::RGBA_8888;
    options.scaleMode = OHOS::Media::ScaleMode::CENTER_CROP;
    options.size.width = static_cast<int32_t>(finalWidth);
    options.size.height = static_cast<int32_t>(finalHeight);
    options.editable = true;
    auto pixelmap = Ace::PixelMap::Create(OHOS::Media::PixelMap::Create(data, length, options));
    delete[] data;
    return pixelmap;
#else
    return nullptr;
#endif
}

void CanvasRenderingContext2DModelImpl::GetImageDataModel(const ImageSize& imageSize, uint8_t* buffer)
{
    auto finalHeight = static_cast<uint32_t>(std::abs(imageSize.height));
    auto finalWidth = static_cast<uint32_t>(std::abs(imageSize.width));
    std::unique_ptr<Ace::ImageData> data = GetImageData(imageSize);
    if (data != nullptr) {
        for (uint32_t idx = 0; idx < finalHeight * finalWidth; ++idx) {
            Color color = Color(data->data[idx]);
            buffer[4 * idx] = color.GetRed(); // 4 * idx: the 1st byte format: red.
            buffer[4 * idx + 1] = color.GetGreen(); // 4 * idx + 1: the 2nd byte format: green.
            buffer[4 * idx + 2] = color.GetBlue(); // 4 * idx + 2: the 3rd byte format: blue.
            buffer[4 * idx + 3] = color.GetAlpha(); // 4 * idx + 3: the 4th byte format: alpha.
        }
    }
}

TextMetrics CanvasRenderingContext2DModelImpl::GetMeasureTextMetrics(const PaintState& state, const std::string& text)
{
    return pattern_ ? pattern_->MeasureTextMetrics(text, state) : TextMetrics {};
}

// All interfaces that only the 'CanvasRenderingContext2D' has.
void CanvasRenderingContext2DModelImpl::GetWidth(double& width)
{
    CHECK_NULL_VOID(pattern_);
    width = pattern_->GetWidth();
}

void CanvasRenderingContext2DModelImpl::GetHeight(double& height)
{
    CHECK_NULL_VOID(pattern_);
    height = pattern_->GetHeight();
}

void CanvasRenderingContext2DModelImpl::SetTransferFromImageBitmap(RefPtr<AceType> offscreenCPattern)
{
    CHECK_NULL_VOID(pattern_);
    auto offscreenCanvas = AceType::DynamicCast<OffscreenCanvas>(offscreenCPattern);
    CHECK_NULL_VOID(offscreenCanvas);
    pattern_->TransferFromImageBitmap(offscreenCanvas);
}
} // namespace OHOS::Ace::Framework
