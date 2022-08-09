/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components/common/properties/alignment.h"
#include "core/components_ng/render/canvas.h"
#include "core/components_ng/render/canvas_image.h"

namespace OHOS::Ace::NG {

class ImagePainter {
public:
    ImagePainter(RefPtr<CanvasImage> image, const SizeF& imageSize, const SizeF& dstSize)
        : image_(std::move(image)), imageSize_(imageSize), dstSize_(dstSize)
    {}
    ImagePainter(RefPtr<CanvasImage> image, ImageFit imageFit, const SizeF& imageSize, const SizeF& dstSize)
        : image_(std::move(image)), imageFit_(imageFit), imageSize_(imageSize), dstSize_(dstSize)
    {}
    ImagePainter(RefPtr<CanvasImage> image, ImageFit imageFit, const Alignment& alignment, const SizeF& imageSize,
        const SizeF& dstSize)
        : image_(std::move(image)), imageFit_(imageFit), alignment_(alignment), imageSize_(imageSize), dstSize_(dstSize)
    {}
    ~ImagePainter() = default;

    void DrawImage(const RefPtr<Canvas>& canvas, const OffsetF& offset) const;

private:
    RefPtr<CanvasImage> image_;
    ImageFit imageFit_ = ImageFit::COVER;
    Alignment alignment_ = Alignment::CENTER;
    SizeF imageSize_;
    SizeF dstSize_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_IMAGE_PAINT_H