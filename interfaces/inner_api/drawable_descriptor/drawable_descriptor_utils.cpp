/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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

#include "drawable_descriptor_utils.h"
#include "image_loader/file_image_loader.h"
namespace OHOS::Ace::Napi {
std::unique_ptr<RSPoint[]> DrawableDescriptorUtils::ToRSRadius(const BorderRadiusArray& radiusXY)
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
            RSPoint(static_cast<RSScalar>(std::max(radiusXY[RSRoundRect::BOTTOM_LEFT_POS].GetX(), 0.0f)),
                static_cast<RSScalar>(std::max(radiusXY[RSRoundRect::BOTTOM_LEFT_POS].GetY(), 0.0f)));
        radii[RSRoundRect::BOTTOM_RIGHT_POS] =
            RSPoint(static_cast<RSScalar>(std::max(radiusXY[RSRoundRect::BOTTOM_RIGHT_POS].GetX(), 0.0f)),
                static_cast<RSScalar>(std::max(radiusXY[RSRoundRect::BOTTOM_RIGHT_POS].GetY(), 0.0f)));
    }
    return radii;
}
void DrawableDescriptorUtils::AddFilter(RSBrush& brush, RSSamplingOptions& options, const PaintConfig& config)
{
    switch (config.imageInterpolation) {
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
        default: {
            options = RSSamplingOptions();
            break;
        }
    }
    auto filter = brush.GetFilter();
    if (config.colorFilter) {
        filter.SetColorFilter(config.colorFilter);
    } else if (ImageRenderMode::TEMPLATE == config.renderMode) {
        RSColorMatrix colorMatrix;
        colorMatrix.SetArray(GRAY_COLOR_MATRIX);
        filter.SetColorFilter(RSRecordingColorFiler::CreateMatrixColorFilter(colorMatrix));
    }
    brush.SetFilter(filter);
}
std::shared_ptr<ImageLoader> DrawableDescriptorUtils::CreateImageLoader(const SourceInfo& src)
{
    SrcType srcType = src.GetSrcType();
    switch (srcType) {
        case SrcType::INTERNAL:
        case SrcType::FILE: {
            return std::make_unique<FileImageLoader>();
        }
        default: {
            return nullptr;
        }
    }
}
} // namespace OHOS::Ace::Napi