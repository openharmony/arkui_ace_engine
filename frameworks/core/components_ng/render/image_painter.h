/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_IMAGE_PAINT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_IMAGE_PAINT_H

#include "core/components/common/properties/background_image.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {

class ImagePainter {
public:
    explicit ImagePainter(const RefPtr<CanvasImage>& canvasImage) : canvasImage_(canvasImage) {}
    ~ImagePainter() = default;

    void DrawObscuration(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const;
    void DrawImage(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const;
    void DrawStaticImage(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const;
    void DrawSVGImage(RSCanvas& canvas, const OffsetF& offset, const SizeF& svgContainerSize) const;
    void DrawImageWithRepeat(RSCanvas& canvas, const RectF& rect) const;

    static void ApplyImageFit(
        ImageFit imageFit, const SizeF& rawPicSize, const SizeF& dstSize, RectF& srcRect, RectF& dstRect);

    static void FlipHorizontal(RSCanvas& canvas, const SizeF& contentSize);

    static SizeF CalculateBgImageSize(
        const SizeF& boxPaintSize_, const SizeF& srcSize, const std::optional<BackgroundImageSize>& bgImageSizeOpt);
    static OffsetF CalculateBgImagePosition(const SizeF& boxPaintSize_, const SizeF& imageRenderSize_,
        const std::optional<BackgroundImagePosition>& bgImgPositionOpt);

private:
    RefPtr<CanvasImage> canvasImage_;

    static void ApplyImageAlignmentFit(
        ImageFit imageFit, const SizeF& rawPicSize, const SizeF& dstSize, RectF& srcRect, RectF& dstRect);
    static const std::unordered_map<ImageFit, std::function<Alignment(bool)>> ALIMENT_OPERATIONS;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_IMAGE_PAINT_H