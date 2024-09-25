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

#include "bridge/declarative_frontend/jsview/models/canvas/offscreen_canvas_rendering_context_2d_model_impl.h"

#include "core/common/container.h"
#include "core/components/custom_paint/custom_paint_component.h"

#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map.h"
#endif

namespace OHOS::Ace::Framework {
void OffscreenCanvasRenderingContext2DModelImpl::SetPattern(RefPtr<AceType> pattern)
{
    pattern_ = AceType::DynamicCast<OffscreenCanvas>(pattern);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetFillText(const PaintState& state, const FillTextInfo& fillTextInfo)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->FillText(fillTextInfo.text, fillTextInfo.x, fillTextInfo.y, state);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetStrokeText(
    const PaintState& state, const FillTextInfo& fillTextInfo)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->StrokeText(fillTextInfo.text, fillTextInfo.x, fillTextInfo.y, state);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetAntiAlias(bool anti)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetAntiAlias(anti);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetFontWeight(const FontWeight& weight)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetFontWeight(weight);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetFontStyle(const FontStyle& fontStyle)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetFontStyle(fontStyle);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetFontFamilies(const std::vector<std::string>& families)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetFontFamilies(families);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetFontSize(const Dimension& size)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetFontSize(size);
}

std::vector<double> OffscreenCanvasRenderingContext2DModelImpl::GetLineDash()
{
    return pattern_ ? pattern_->GetLineDash().lineDash : std::vector<double> {};
}

void OffscreenCanvasRenderingContext2DModelImpl::SetFillGradient(const std::shared_ptr<Ace::Gradient>& gradient)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetFillGradient(*gradient);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetFillPattern(const std::shared_ptr<Ace::Pattern>& pattern)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetFillPattern(*(pattern.get()));
}

void OffscreenCanvasRenderingContext2DModelImpl::SetFillColor(const Color& color, bool colorFlag)
{
    if (pattern_ && colorFlag) {
        pattern_->SetFillColor(color);
    }
}

void OffscreenCanvasRenderingContext2DModelImpl::SetStrokeGradient(const std::shared_ptr<Ace::Gradient>& gradient)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetStrokeGradient(*gradient);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetStrokePattern(const std::shared_ptr<Ace::Pattern>& pattern)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetStrokePattern(*(pattern.get()));
}

void OffscreenCanvasRenderingContext2DModelImpl::SetStrokeColor(const Color& color, bool colorFlag)
{
    if (pattern_ && colorFlag) {
        pattern_->SetStrokeColor(color);
    }
}

void OffscreenCanvasRenderingContext2DModelImpl::DrawImage(const ImageInfo& imageInfo)
{
    CHECK_NULL_VOID(pattern_);
    if (imageInfo.isImage) {
        pattern_->DrawImage(imageInfo.image, imageInfo.imgWidth, imageInfo.imgHeight);
        return;
    }
    pattern_->DrawPixelMap(imageInfo.pixelMap, imageInfo.image);
}

void OffscreenCanvasRenderingContext2DModelImpl::PutImageData(const ImageData& imageData)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->PutImageData(imageData);
}

std::unique_ptr<ImageData> OffscreenCanvasRenderingContext2DModelImpl::GetImageData(const ImageSize& imageSize)
{
    return pattern_ ? pattern_->GetImageData(imageSize.left, imageSize.top, imageSize.width, imageSize.height)
                    : nullptr;
}

void OffscreenCanvasRenderingContext2DModelImpl::DrawPixelMap(const ImageInfo& imageInfo)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->DrawPixelMap(imageInfo.pixelMap, imageInfo.image);
}

std::string OffscreenCanvasRenderingContext2DModelImpl::GetJsonData(const std::string& path)
{
    return "";
}

std::string OffscreenCanvasRenderingContext2DModelImpl::ToDataURL(const std::string& dataUrl, double quality)
{
    return pattern_ ? pattern_->ToDataURL(dataUrl, quality) : "";
}

void OffscreenCanvasRenderingContext2DModelImpl::SetLineCap(const LineCapStyle& lineCap)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetLineCap(lineCap);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetLineJoin(const LineJoinStyle& lineJoin)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetLineJoin(lineJoin);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetMiterLimit(double limit)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetMiterLimit(limit);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetLineWidth(double lineWidth)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetLineWidth(lineWidth);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetGlobalAlpha(double alpha)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetAlpha(alpha);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetCompositeType(const CompositeOperation& type)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetCompositeType(type);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetLineDashOffset(double lineDashOffset)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetLineDashOffset(lineDashOffset);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetShadowBlur(double blur)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetShadowBlur(blur);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetShadowColor(const Color& color)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetShadowColor(color);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetShadowOffsetX(double offsetX)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetShadowOffsetX(offsetX);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetShadowOffsetY(double offsetY)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetShadowOffsetY(offsetY);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetSmoothingEnabled(bool enabled)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetSmoothingEnabled(enabled);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetSmoothingQuality(const std::string& quality)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetSmoothingQuality(quality);
}

void OffscreenCanvasRenderingContext2DModelImpl::MoveTo(double x, double y)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->MoveTo(x, y);
}

void OffscreenCanvasRenderingContext2DModelImpl::LineTo(double x, double y)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->LineTo(x, y);
}

void OffscreenCanvasRenderingContext2DModelImpl::BezierCurveTo(const BezierCurveParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->BezierCurveTo(param);
}

void OffscreenCanvasRenderingContext2DModelImpl::QuadraticCurveTo(const QuadraticCurveParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->QuadraticCurveTo(param);
}

void OffscreenCanvasRenderingContext2DModelImpl::ArcTo(const ArcToParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->ArcTo(param);
}

void OffscreenCanvasRenderingContext2DModelImpl::Arc(const ArcParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Arc(param);
}

void OffscreenCanvasRenderingContext2DModelImpl::Ellipse(const EllipseParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Ellipse(param);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetFillRuleForPath(const CanvasFillRule& fillRule)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetFillRuleForPath(fillRule);
    pattern_->Fill();
}

void OffscreenCanvasRenderingContext2DModelImpl::SetFillRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetFillRuleForPath2D(fillRule);
    pattern_->Fill(path);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetStrokeRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetFillRuleForPath(fillRule);
    pattern_->Stroke(path);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetStrokeRuleForPath(const CanvasFillRule& fillRule)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetFillRuleForPath2D(fillRule);
    pattern_->Stroke();
}

void OffscreenCanvasRenderingContext2DModelImpl::SetClipRuleForPath(const CanvasFillRule& fillRule)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetFillRuleForPath(fillRule);
    pattern_->Clip();
}

void OffscreenCanvasRenderingContext2DModelImpl::SetClipRuleForPath2D(
    const CanvasFillRule& fillRule, const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetFillRuleForPath2D(fillRule);
    pattern_->Clip(path);
}

void OffscreenCanvasRenderingContext2DModelImpl::AddRect(const Rect& rect)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->AddRect(rect);
}

void OffscreenCanvasRenderingContext2DModelImpl::BeginPath()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->BeginPath();
}

void OffscreenCanvasRenderingContext2DModelImpl::ClosePath()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->ClosePath();
}

void OffscreenCanvasRenderingContext2DModelImpl::Restore()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Restore();
}

void OffscreenCanvasRenderingContext2DModelImpl::CanvasRendererSave()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Save();
}

void OffscreenCanvasRenderingContext2DModelImpl::CanvasRendererRotate(double angle)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Rotate(angle);
}

void OffscreenCanvasRenderingContext2DModelImpl::CanvasRendererScale(double x, double y)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Scale(x, y);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetTransform(TransformParam& param, bool lengthFlag)
{
    if (pattern_ && lengthFlag) {
        std::swap(param.skewX, param.skewY);
        pattern_->SetTransform(param);
    }
}

void OffscreenCanvasRenderingContext2DModelImpl::ResetTransform()
{
    CHECK_NULL_VOID(pattern_);
    pattern_->ResetTransform();
}

void OffscreenCanvasRenderingContext2DModelImpl::Transform(const TransformParam& param)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Transform(param);
}

void OffscreenCanvasRenderingContext2DModelImpl::Translate(double x, double y)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->Translate(x, y);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetLineDash(const std::vector<double>& lineDash)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetLineDash(lineDash);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetTextAlign(const TextAlign& align)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetTextAlign(align);
}

void OffscreenCanvasRenderingContext2DModelImpl::SetTextBaseline(const TextBaseline& baseline)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->SetTextBaseline(baseline);
}

double OffscreenCanvasRenderingContext2DModelImpl::GetMeasureTextWidth(const PaintState& state, const std::string& text)
{
    return pattern_ ? pattern_->MeasureText(text, state) : 0.0;
}

double OffscreenCanvasRenderingContext2DModelImpl::GetMeasureTextHeight(
    const PaintState& state, const std::string& text)
{
    return pattern_ ? pattern_->MeasureTextHeight(text, state) : 0.0;
}

void OffscreenCanvasRenderingContext2DModelImpl::FillRect(const Rect& rect)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->FillRect(rect);
}

void OffscreenCanvasRenderingContext2DModelImpl::StrokeRect(const Rect& rect)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->StrokeRect(rect);
}

void OffscreenCanvasRenderingContext2DModelImpl::ClearRect(const Rect& rect)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->ClearRect(rect);
}

void OffscreenCanvasRenderingContext2DModelImpl::DrawBitmapMesh(const BitmapMeshInfo& bitmapMeshInfo)
{
    CHECK_NULL_VOID(bitmapMeshInfo.pool);
    auto pool = AceType::DynamicCast<CanvasTaskPool>(bitmapMeshInfo.pool);
    CHECK_NULL_VOID(pool);
    CHECK_NULL_VOID(bitmapMeshInfo.offscreenPattern);
    auto offscreenPattern = AceType::DynamicCast<OffscreenCanvas>(bitmapMeshInfo.offscreenPattern);
    CHECK_NULL_VOID(offscreenPattern);
    pool->DrawBitmapMesh(offscreenPattern, bitmapMeshInfo.mesh, bitmapMeshInfo.column, bitmapMeshInfo.row);
}

RefPtr<Ace::PixelMap> OffscreenCanvasRenderingContext2DModelImpl::GetPixelMap(const ImageSize& imageSize)
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

void OffscreenCanvasRenderingContext2DModelImpl::GetImageDataModel(const ImageSize& imageSize, uint8_t* buffer)
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

TextMetrics OffscreenCanvasRenderingContext2DModelImpl::GetMeasureTextMetrics(
    const PaintState& state, const std::string& text)
{
    return pattern_ ? pattern_->MeasureTextMetrics(text, state) : TextMetrics {};
}

// All interfaces that only the 'OffscreenCanvasRenderingContext2D' has.
RefPtr<AceType> OffscreenCanvasRenderingContext2DModelImpl::CreateOffscreenPattern(int width, int height)
{
    auto container = Ace::Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto context = AceType::DynamicCast<Ace::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(context, nullptr);
    return context->CreateOffscreenCanvas(width, height);
}
} // namespace OHOS::Ace::Framework
