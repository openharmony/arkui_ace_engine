/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "image_painter_utils.h"

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
} // namespace

namespace OHOS::Ace::NG {
#ifndef USE_ROSEN_DRAWING
std::unique_ptr<SkVector[]> ImagePainterUtils::ToSkRadius(const BorderRadiusArray& radiusXY)
{
    auto radii = std::make_unique<SkVector[]>(RADIUS_POINTS_SIZE);
    if (radiusXY.size() == RADIUS_POINTS_SIZE) {
        radii[SkRRect::kUpperLeft_Corner].set(
            SkFloatToScalar(std::max(radiusXY[SkRRect::kUpperLeft_Corner].GetX(), 0.0f)),
            SkFloatToScalar(std::max(radiusXY[SkRRect::kUpperLeft_Corner].GetY(), 0.0f)));
        radii[SkRRect::kUpperRight_Corner].set(
            SkFloatToScalar(std::max(radiusXY[SkRRect::kUpperRight_Corner].GetX(), 0.0f)),
            SkFloatToScalar(std::max(radiusXY[SkRRect::kUpperRight_Corner].GetY(), 0.0f)));
        radii[SkRRect::kLowerLeft_Corner].set(
            SkFloatToScalar(std::max(radiusXY[SkRRect::kLowerRight_Corner].GetX(), 0.0f)),
            SkFloatToScalar(std::max(radiusXY[SkRRect::kLowerRight_Corner].GetY(), 0.0f)));
        radii[SkRRect::kLowerRight_Corner].set(
            SkFloatToScalar(std::max(radiusXY[SkRRect::kLowerLeft_Corner].GetX(), 0.0f)),
            SkFloatToScalar(std::max(radiusXY[SkRRect::kLowerLeft_Corner].GetY(), 0.0f)));
    }
    return radii;
}
#else
std::unique_ptr<RSPoint[]> ImagePainterUtils::ToRSRadius(const BorderRadiusArray& radiusXY)
{
    auto radii = std::make_unique<RSPoint[]>(RADIUS_POINTS_SIZE);
    if (radiusXY.size() == RADIUS_POINTS_SIZE) {
        radii[RSRoundRect::TOP_LEFT_POS] =
            RSPoint(static_cast<RSScalar>(std::max(radiusXY[RSRoundRect::TOP_LEFT_POS].GetX(), 0.0f)),
                static_cast<RSScalar>(std::max(radiusXY[RSRoundRect::TOP_LEFT_POS].GetY(), 0.0f)));
        radii[RSRoundRect::TOP_RIGHT_POS] =
            RSPoint(static_cast<RSScalar>(std::max(radiusXY[RSRoundRect::TOP_RIGHT_POS].GetX(), 0.0f)),
                static_cast<RSScalar>(std::max(radiusXY[RSRoundRect::TOP_RIGHT_POS].GetY(), 0.0f)));
        radii[RSRoundRect::BOTTOM_LEFT_POS] =
            RSPoint(static_cast<RSScalar>(std::max(radiusXY[RSRoundRect::BOTTOM_RIGHT_POS].GetX(), 0.0f)),
                static_cast<RSScalar>(std::max(radiusXY[RSRoundRect::BOTTOM_RIGHT_POS].GetY(), 0.0f)));
        radii[RSRoundRect::BOTTOM_RIGHT_POS] =
            RSPoint(static_cast<RSScalar>(std::max(radiusXY[RSRoundRect::BOTTOM_LEFT_POS].GetX(), 0.0f)),
                static_cast<RSScalar>(std::max(radiusXY[RSRoundRect::BOTTOM_LEFT_POS].GetY(), 0.0f)));
    }
    return radii;
}
#endif

#ifndef USE_ROSEN_DRAWING

void ImagePainterUtils::AddFilter(SkPaint& paint, SkSamplingOptions& options, const ImagePaintConfig& config)
{
    switch (config.imageInterpolation_) {
        case ImageInterpolation::LOW: {
            options = SkSamplingOptions(SkFilterMode::kLinear, SkMipmapMode::kNone);
            break;
        }
        case ImageInterpolation::MEDIUM: {
            options = SkSamplingOptions(SkFilterMode::kLinear, SkMipmapMode::kLinear);
            break;
        }
        case ImageInterpolation::HIGH: {
            options = SkSamplingOptions(SkCubicResampler::Mitchell());
            break;
        }
        default:
            options = SkSamplingOptions();
            break;
    }

    if (config.colorFilter_.colorFilterMatrix_) {
        paint.setColorFilter(SkColorFilters::Matrix(config.colorFilter_.colorFilterMatrix_->data()));
    } else if (ImageRenderMode::TEMPLATE == config.renderMode_) {
        paint.setColorFilter(SkColorFilters::Matrix(GRAY_COLOR_MATRIX));
    }
}
#else
void ImagePainterUtils::AddFilter(RSBrush& brush, RSSamplingOptions& options, const ImagePaintConfig& config)
{
    switch (config.imageInterpolation_) {
        case ImageInterpolation::LOW: {
            options = RSSamplingOptions(RSFilterMode::LINEAR, RSMipmapMode::NONE);
            break;
        }
        case ImageInterpolation::MEDIUM: {
            options = RSSamplingOptions(RSFilterMode::LINEAR, RSMipmapMode::LINEAR);
            break;
        }
        case ImageInterpolation::HIGH: {
            options = RSSamplingOptions(RSCubicResampler::Mitchell());
            break;
        }
        default:
            options = RSSamplingOptions();
            break;
    }

    auto filter = brush.GetFilter();
    if (config.colorFilter_.colorFilterMatrix_) {
        RSColorMatrix colorMatrix;
        colorMatrix.SetArray(config.colorFilter_.colorFilterMatrix_->data());
        filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix));
    } else if (config.colorFilter_.colorFilterDrawing_) {
        auto colorFilterSptrAddr = static_cast<std::shared_ptr<RSColorFilter>*>(
            config.colorFilter_.colorFilterDrawing_->GetDrawingColorFilterSptrAddr());
        if (colorFilterSptrAddr && (*colorFilterSptrAddr)) {
            filter.SetColorFilter(*colorFilterSptrAddr);
        }
    } else if (ImageRenderMode::TEMPLATE == config.renderMode_) {
        RSColorMatrix colorMatrix;
        colorMatrix.SetArray(GRAY_COLOR_MATRIX);
        filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix));
    }
    brush.SetFilter(filter);
}
#endif

void ImagePainterUtils::ClipRRect(RSCanvas& canvas, const RSRect& dstRect, const BorderRadiusArray& radiusXY)
{
    std::vector<RSPoint> radius(ImagePainterUtils::RADIUS_POINTS_SIZE);
    // Adapt to the graphical interface and adjust the position of the last two parameters
    radius[0] = RSPoint(radiusXY[0].GetX(), radiusXY[0].GetY());
    radius[1] = RSPoint(radiusXY[1].GetX(), radiusXY[1].GetY());
    radius[2] = RSPoint(radiusXY[3].GetX(), radiusXY[3].GetY());
    radius[3] = RSPoint(radiusXY[2].GetX(), radiusXY[2].GetY());
    RSRoundRect rRect(dstRect, radius);
    canvas.ClipRoundRect(rRect, RSClipOp::INTERSECT, true);
}
} // namespace OHOS::Ace::NG
