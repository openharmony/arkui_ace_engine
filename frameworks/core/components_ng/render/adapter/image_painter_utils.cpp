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

#include "third_party/skia/include/core/SkColorFilter.h"
#include "third_party/skia/include/core/SkRRect.h"

#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"

namespace {
const float GRAY_COLOR_MATRIX[20] = { 0.30f, 0.59f, 0.11f, 0, 0, // red
    0.30f, 0.59f, 0.11f, 0, 0,                                   // green
    0.30f, 0.59f, 0.11f, 0, 0,                                   // blue
    0, 0, 0, 1.0f, 0 };                                          // alpha transparency
} // namespace

namespace OHOS::Ace::NG {
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

void ImagePainterUtils::AddFilter(SkPaint& paint, const ImagePaintConfig& config)
{
    paint.setFilterQuality(SkFilterQuality(config.imageInterpolation_));
    if (config.colorFilter_) {
        paint.setColorFilter(SkColorFilters::Matrix(config.colorFilter_->data()));
    } else if (ImageRenderMode::TEMPLATE == config.renderMode_) {
        paint.setColorFilter(SkColorFilters::Matrix(GRAY_COLOR_MATRIX));
    }
}
} // namespace OHOS::Ace::NG
