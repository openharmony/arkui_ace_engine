/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/adapter/pixelmap_image.h"

#include "render_service_base/include/pipeline/rs_recording_canvas.h"

#include "base/log/ace_trace.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/image_provider/image_data.h"
#include "core/components_ng/pattern/image/image_dfx.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/render/adapter/image_painter_utils.h"
#include "core/components_ng/render/adapter/drawing_image.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
// The [GRAY_COLOR_MATRIX] is of dimension [4 x 5], which transforms a RGB source color (R, G, B, A) to the
// destination color (R', G', B', A').
//
// A classic color image to grayscale conversion formula is [Gray = R * 0.3 + G * 0.59 + B * 0.11].
// Hence we get the following conversion:
//
// | M11 M12 M13 M14 M15 |   | R |   | R' |
// | M21 M22 M23 M24 M25 |   | G |   | G' |
// | M31 M32 M33 M34 M35 | x | B | = | B' |
// | M41 M42 M43 M44 M45 |   | A |   | A' |
//                           | 1 |
const float GRAY_COLOR_MATRIX[20] = { 0.30f, 0.59f, 0.11f, 0, 0, // red
    0.30f, 0.59f, 0.11f, 0, 0,                                   // green
    0.30f, 0.59f, 0.11f, 0, 0,                                   // blue
    0, 0, 0, 1.0f, 0 };                                          // alpha transparency

constexpr int32_t BORDER_RADIUS_ARRAY_SIZE = 4;
constexpr int32_t DEGREE_NINETY = 90;
constexpr int32_t DEGREE_HUNDRED_EIGHTY = 180;

void PrintDrawingLatticeConfig(const Rosen::Drawing::Lattice& lattice, const RSRect& dstRect)
{
    std::string drawingConfigStr;
    drawingConfigStr.append("dstRect = " + dstRect.ToString());
    drawingConfigStr.append("fXCount = " + std::to_string(lattice.fXCount));
    drawingConfigStr.append("fXDivs = [");
    for (int32_t idx = 0; idx < lattice.fXCount; ++idx) {
        drawingConfigStr.append(std::to_string(lattice.fXDivs[idx]) + " ");
    }
    drawingConfigStr.append("] ");
    drawingConfigStr.append("fYCount = " + std::to_string(lattice.fYCount));
    drawingConfigStr.append("fYDivs = [");
    for (int32_t idx = 0; idx < lattice.fYCount; ++idx) {
        drawingConfigStr.append(std::to_string(lattice.fYDivs[idx]) + " ");
    }
    drawingConfigStr.append("] ");
    TAG_LOGD(AceLogTag::ACE_IMAGE, "Begin to draw image with lattice : %{public}s", drawingConfigStr.c_str());
}

bool ConvertSlice(const ImagePaintConfig& config, RectF& result, float rawImageWidth, float rawImageHeight)
{
    const auto& slice = config.resizableSlice_;
    CHECK_NULL_RETURN(slice.Valid(), false);
    TAG_LOGD(AceLogTag::ACE_IMAGE, "Draw image with slice = %{public}s.", slice.ToString().c_str());
    result.SetLeft(ConvertToPx(slice.left, ScaleProperty::CreateScaleProperty(), rawImageWidth).value_or(0.0f));
    result.SetTop(ConvertToPx(slice.top, ScaleProperty::CreateScaleProperty(), rawImageHeight).value_or(0.0f));
    auto rightSliceValue = ConvertToPx(slice.right, ScaleProperty::CreateScaleProperty(), rawImageWidth).value_or(0.0f);
    auto bottomSliceValue =
        ConvertToPx(slice.bottom, ScaleProperty::CreateScaleProperty(), rawImageHeight).value_or(0.0f);
    // illegal case if left position if larger than right, then rect has negative width
    if (GreatNotEqual(rawImageWidth - rightSliceValue - result.GetX(), 0.0f)) {
        result.SetWidth(rawImageWidth - rightSliceValue - result.GetX());
    } else {
        return false;
    }
    // same illegal case for height
    if (GreatNotEqual(rawImageHeight - bottomSliceValue - result.GetY(), 0.0f)) {
        result.SetHeight(rawImageHeight - bottomSliceValue - result.GetY());
    } else {
        return false;
    }
    return true;
}

std::string GetDynamicModeString(DynamicRangeMode dynamicMode)
{
    switch (dynamicMode) {
        case DynamicRangeMode::HIGH:
            return "HIGH";
        case DynamicRangeMode::CONSTRAINT:
            return "CONSTRAINT";
        case DynamicRangeMode::STANDARD:
            return "STANDARD";
        default:
            return "STANDARD";
    }
}

void UpdateRSFilter(const ImagePaintConfig& config, RSFilter& filter)
{
    if (config.colorFilter_.colorFilterMatrix_) {
        RSColorMatrix colorMatrix;
        colorMatrix.SetArray(config.colorFilter_.colorFilterMatrix_->data());
        filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix, RSClamp::NO_CLAMP));
    } else if (config.colorFilter_.colorFilterDrawing_) {
        auto colorFilterSptrAddr = static_cast<std::shared_ptr<RSColorFilter>*>(
            config.colorFilter_.colorFilterDrawing_->GetDrawingColorFilterSptrAddr());
        if (colorFilterSptrAddr && (*colorFilterSptrAddr)) {
            filter.SetColorFilter(*colorFilterSptrAddr);
        }
    } else if (ImageRenderMode::TEMPLATE == config.renderMode_) {
        RSColorMatrix colorMatrix;
        colorMatrix.SetArray(GRAY_COLOR_MATRIX);
        filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix, RSClamp::NO_CLAMP));
    }
}

OrientationFit CalculateFlip(ImageRotateOrientation orientation)
{
    switch (orientation) {
        case ImageRotateOrientation::LEFT_MIRRORED:
        case ImageRotateOrientation::RIGHT_MIRRORED:
        case ImageRotateOrientation::UP_MIRRORED:
            return OrientationFit::HORIZONTAL_FLIP;
        case ImageRotateOrientation::DOWN_MIRRORED:
            return OrientationFit::VERTICAL_FLIP;
        default:
            return OrientationFit::NONE;
    }
}

int32_t CalculateRotateDegree(ImageRotateOrientation orientation)
{
    switch (orientation) {
        case ImageRotateOrientation::LEFT:
        case ImageRotateOrientation::LEFT_MIRRORED:
            return -DEGREE_NINETY;
        case ImageRotateOrientation::RIGHT:
        case ImageRotateOrientation::RIGHT_MIRRORED:
            return DEGREE_NINETY;
        case ImageRotateOrientation::DOWN:
            return DEGREE_HUNDRED_EIGHTY;
        default:
            return 0;
    }
}
} // namespace

RefPtr<CanvasImage> CanvasImage::Create(const RefPtr<PixelMap>& pixelMap)
{
    return AceType::MakeRefPtr<PixelMapImage>(pixelMap);
}

RefPtr<CanvasImage> PixelMapImage::Clone()
{
    return MakeRefPtr<PixelMapImage>(pixelMap_);
}

int32_t PixelMapImage::GetWidth() const
{
    auto pixmap = GetPixelMap();
    if (pixmap) {
        return pixmap->GetWidth();
    }
    TAG_LOGW(AceLogTag::ACE_IMAGE, "pixelMap_ is nullptr, return width 0.");
    return 0;
}

int32_t PixelMapImage::GetHeight() const
{
    auto pixmap = GetPixelMap();
    if (pixmap) {
        return pixmap->GetHeight();
    }
    TAG_LOGW(AceLogTag::ACE_IMAGE, "rsCanvas is nullptr, return height 0.");
    return 0;
}

bool PixelMapImage::StretchImageWithLattice(
    RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY)
{
    auto pixmap = GetPixelMap();
    const auto& config = GetPaintConfig();
    auto drawingLattice = config.resizableLattice_;
    CHECK_NULL_RETURN(drawingLattice, false);
    auto latticeSptrAddr =
        static_cast<std::shared_ptr<Rosen::Drawing::Lattice>*>(drawingLattice->GetDrawingLatticeSptrAddr());
    CHECK_NULL_RETURN((latticeSptrAddr && (*latticeSptrAddr)), false);
    RSBrush brush;
    auto filterMode = RSFilterMode::NEAREST;
    switch (config.imageInterpolation_) {
        case ImageInterpolation::LOW:
        case ImageInterpolation::MEDIUM:
            filterMode = RSFilterMode::LINEAR;
            break;
        case ImageInterpolation::HIGH:
        default:
            break;
    }

    auto filter = brush.GetFilter();
    UpdateRSFilter(config, filter);
    brush.SetFilter(filter);
    auto& recordingCanvas = static_cast<Rosen::ExtendRecordingCanvas&>(canvas);
    auto radii = ImagePainterUtils::ToRSRadius(radiusXY);
    std::vector<RSPoint> radius;
    for (size_t ii = 0; ii < BORDER_RADIUS_ARRAY_SIZE; ii++) {
        RSPoint point(radii[ii].GetX(), radii[ii].GetY());
        radius.emplace_back(point);
    }
    recordingCanvas.ClipAdaptiveRoundRect(radius);
    recordingCanvas.Scale(config.scaleX_, config.scaleY_);

    RSPoint pointRadius[BORDER_RADIUS_ARRAY_SIZE] = {};
    for (size_t i = 0; i < BORDER_RADIUS_ARRAY_SIZE; i++) {
        pointRadius[i] = radius[i];
    }
    std::shared_ptr<RSImage> rsImage = DrawingImage::MakeRSImageFromPixmap(pixmap);
    CHECK_NULL_RETURN(rsImage, false);
    auto lattice = *(*latticeSptrAddr);
    if (SystemProperties::GetDebugEnabled()) {
        PrintDrawingLatticeConfig(lattice, dstRect);
    }
    recordingCanvas.AttachBrush(brush);
    recordingCanvas.DrawImageLattice(rsImage.get(), lattice, dstRect, filterMode);
    recordingCanvas.DetachBrush();
    return true;
}

bool PixelMapImage::StretchImageWithSlice(
    RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY)
{
    auto pixmap = GetPixelMap();
    const auto& config = GetPaintConfig();
    const auto& slice = GetPaintConfig().resizableSlice_;
    CHECK_NULL_RETURN(slice.Valid(), false);
    RectF centerRect;
    CHECK_NULL_RETURN(ConvertSlice(config, centerRect, pixmap->GetWidth(), pixmap->GetHeight()), false);
    RSBrush brush;
    auto filterMode = RSFilterMode::NEAREST;
    switch (config.imageInterpolation_) {
        case ImageInterpolation::LOW:
        case ImageInterpolation::MEDIUM:
            filterMode = RSFilterMode::LINEAR;
            break;
        case ImageInterpolation::HIGH:
        default:
            break;
    }

    auto filter = brush.GetFilter();
    UpdateRSFilter(config, filter);
    brush.SetFilter(filter);
    auto& recordingCanvas = static_cast<Rosen::ExtendRecordingCanvas&>(canvas);
    auto radii = ImagePainterUtils::ToRSRadius(radiusXY);
    std::vector<RSPoint> radius;
    for (int ii = 0; ii < BORDER_RADIUS_ARRAY_SIZE; ii++) {
        RSPoint point(radii[ii].GetX(), radii[ii].GetY());
        radius.emplace_back(point);
    }
    recordingCanvas.ClipAdaptiveRoundRect(radius);
    recordingCanvas.Scale(config.scaleX_, config.scaleY_);

    RSPoint pointRadius[BORDER_RADIUS_ARRAY_SIZE] = {};
    for (int i = 0; i < BORDER_RADIUS_ARRAY_SIZE; i++) {
        pointRadius[i] = radius[i];
    }
    RSRectI rsCenterRect(centerRect.GetX(), centerRect.GetY(), centerRect.GetX() + centerRect.Width(),
        centerRect.GetY() + centerRect.Height());
    std::shared_ptr<RSImage> rsImage = DrawingImage::MakeRSImageFromPixmap(pixmap);
    CHECK_NULL_RETURN(rsImage, false);
    recordingCanvas.AttachBrush(brush);
    recordingCanvas.DrawImageNine(rsImage.get(), rsCenterRect, dstRect, filterMode, &brush);
    recordingCanvas.DetachBrush();
    return true;
}

bool PixelMapImage::CheckIfNeedForStretching(
    RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY)
{
    const auto& config = GetPaintConfig();

    if (config.frameCount_ == 1 && config.resizableLattice_ &&
        StretchImageWithLattice(canvas, srcRect, dstRect, radiusXY)) {
        return true;
    }
    if (config.frameCount_ == 1 && config.resizableSlice_.Valid() &&
        StretchImageWithSlice(canvas, srcRect, dstRect, radiusXY)) {
        return true;
    }
    return false;
}

void PixelMapImage::NotifyDrawCompletion(const std::string& srcInfo, const RefPtr<PixelMap>& pixmap)
{
    FireDrawCompleteCallback(RenderedImageInfo{
        .renderSuccess = true,
        .width = pixmap->GetWidth(),
        .height = pixmap->GetHeight(),
        .rowStride = pixmap->GetRowStride(),
        .rowBytes = pixmap->GetRowBytes(),
        .byteCount = pixmap->GetByteCount(),
        .isHdr = pixmap->IsHdr(),
        .alphaType = pixmap->GetAlphaType(),
        .pixelFormat = pixmap->GetPixelFormat(),
        .allocatorType = pixmap->GetAllocatorType(),
        .pixelMapId = pixmap->GetId(),
        .srcInfo = srcInfo
    });
}

void PixelMapImage::DrawToRSCanvas(
    RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY)
{
    auto pixmap = GetPixelMap();
    auto dfxConfig = GetImageDfxConfig();
    if (!pixmap || !pixmap->GetPixelMapSharedPtr()) {
        TAG_LOGE(AceLogTag::ACE_IMAGE, "pixmap null, %{private}s-%{public}s", dfxConfig.GetImageSrc().c_str(),
            dfxConfig.ToStringWithoutSrc().c_str());
        return;
    }
    if (CheckIfNeedForStretching(canvas, srcRect, dstRect, radiusXY)) {
        return;
    }
    ACE_SCOPED_TRACE("DrawToRSCanvas %s-%f-%f-%d-%d", dfxConfig.ToStringWithSrc().c_str(),
        dfxConfig.GetFrameSizeWidth(), dfxConfig.GetFrameSizeHeight(), pixmap->GetWidth(), pixmap->GetHeight());
    const auto& config = GetPaintConfig();
    RSBrush brush;
    RSSamplingOptions options;
    ImagePainterUtils::AddFilter(brush, options, config);
    auto radii = ImagePainterUtils::ToRSRadius(radiusXY);
    auto& recordingCanvas = static_cast<Rosen::ExtendRecordingCanvas&>(canvas);
    std::vector<RSPoint> radius;
    for (int ii = 0; ii < BORDER_RADIUS_ARRAY_SIZE; ii++) {
        RSPoint point(radii[ii].GetX(), radii[ii].GetY());
        radius.emplace_back(point);
    }
    recordingCanvas.ClipAdaptiveRoundRect(radius);
    recordingCanvas.Scale(config.scaleX_, config.scaleY_);

    RSPoint pointRadius[BORDER_RADIUS_ARRAY_SIZE] = {};
    for (int i = 0; i < BORDER_RADIUS_ARRAY_SIZE; i++) {
        pointRadius[i] = radius[i];
    }
    Rosen::Drawing::AdaptiveImageInfo rsImageInfo = { static_cast<int32_t>(config.imageFit_),
        static_cast<int32_t>(config.imageRepeat_), { pointRadius[0], pointRadius[1], pointRadius[2], pointRadius[3] },
        1.0, 0, 0, 0, static_cast<int32_t>(config.dynamicMode) };
    rsImageInfo.fitMatrix = ToDrawingMatrix(config.imageMatrix_);
    rsImageInfo.rotateDegree = CalculateRotateDegree(config.orientation_);
    rsImageInfo.orientationNum = static_cast<int32_t>(CalculateFlip(config.orientation_));
    recordingCanvas.AttachBrush(brush);
    if (SystemProperties::GetDebugPixelMapSaveEnabled()) {
        TAG_LOGI(AceLogTag::ACE_IMAGE, "pixmap, %{public}s-[%{public}d * %{public}d]-[%{public}s]",
            dfxConfig.ToStringWithSrc().c_str(), pixmap->GetWidth(), pixmap->GetHeight(),
            GetDynamicModeString(config.dynamicMode).c_str());
        pixmap->SavePixelMapToFile(dfxConfig.ToStringWithoutSrc() + "_ToRS_");
    }
    NotifyDrawCompletion(dfxConfig.ToStringWithSrc(), pixmap);
    recordingCanvas.DrawPixelMapWithParm(pixmap->GetPixelMapSharedPtr(), rsImageInfo, options);
    recordingCanvas.DetachBrush();
}

void PixelMapImage::DrawRect(RSCanvas& canvas, const RSRect& dstRect)
{
    auto& recordingCanvas = static_cast<Rosen::ExtendRecordingCanvas&>(canvas);
    RSBrush brush;
    RSSamplingOptions options { RSFilterMode::LINEAR, RSMipmapMode::LINEAR };
    RSRect dst = RSRect(dstRect.GetLeft(), dstRect.GetTop(), dstRect.GetRight(), dstRect.GetBottom());

    auto pixelMap = pixelMap_->GetPixelMapSharedPtr();
    CHECK_NULL_VOID(pixelMap);
    RSRect src = RSRect(0, 0, pixelMap->GetWidth(), pixelMap->GetHeight());
    recordingCanvas.AttachBrush(brush);
    recordingCanvas.DrawPixelMapRect(pixelMap, src, dst, options);
    recordingCanvas.DetachBrush();
}

void PixelMapImage::DrawRect(RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect)
{
    auto pixelMapPtr = GetPixelMap();
    auto& recordingCanvas = static_cast<Rosen::ExtendRecordingCanvas&>(canvas);
    RSBrush brush;
    RSSamplingOptions options;
    RSRect dst = RSRect(dstRect.GetLeft(), dstRect.GetTop(), dstRect.GetRight(), dstRect.GetBottom());

    CHECK_NULL_VOID(pixelMapPtr);
    auto pixelMap = pixelMapPtr->GetPixelMapSharedPtr();
    CHECK_NULL_VOID(pixelMap);
    RSRect src = RSRect(srcRect.GetLeft(), srcRect.GetTop(), srcRect.GetRight(), srcRect.GetBottom());
    recordingCanvas.AttachBrush(brush);
    recordingCanvas.DrawPixelMapRect(pixelMap, src, dst, options);
    recordingCanvas.DetachBrush();
}

void PixelMapImage::Cache(const std::string& key)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto cache = pipeline->GetImageCache();
    CHECK_NULL_VOID(cache);
    cache->CacheImageData(key, MakeRefPtr<PixmapData>(GetPixelMap()));
}

RefPtr<CanvasImage> PixelMapImage::QueryFromCache(const std::string& key)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto cache = pipeline->GetImageCache();
    CHECK_NULL_RETURN(cache, nullptr);
    auto data = DynamicCast<PixmapData>(cache->GetCacheImageData(key));
    CHECK_NULL_RETURN(data, nullptr);
    return MakeRefPtr<PixelMapImage>(data->GetPixmap());
}

RSMatrix PixelMapImage::ToDrawingMatrix(const Matrix4& matrix4)
{
    // Mappings from DrawingMatrix-index to input-index.
    static const int32_t K_DRAWING_MATRIX_INDEX_TO_MATRIX4_INDEX[] = {
        0,
        4,
        12,
        1,
        5,
        13,
        3,
        7,
        15,
    };

    RSMatrix matrix;
    for (std::size_t i = 0; i < ArraySize(K_DRAWING_MATRIX_INDEX_TO_MATRIX4_INDEX); ++i) {
        int32_t matrixIndex = K_DRAWING_MATRIX_INDEX_TO_MATRIX4_INDEX[i];
        if (matrixIndex < matrix4.Count()) {
            matrix.Set(static_cast<RSMatrix::Index>(i), matrix4[matrixIndex]);
        } else {
            matrix.Set(static_cast<RSMatrix::Index>(i), 0.0);
        }
    }
    return matrix;
}
} // namespace OHOS::Ace::NG
