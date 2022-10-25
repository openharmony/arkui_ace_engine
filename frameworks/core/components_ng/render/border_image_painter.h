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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_BORDER_IMAGE_PAINT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_BORDER_IMAGE_PAINT_H

#include <cmath>

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "core/components/common/properties/border_image.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/render_property.h"

namespace OHOS::Ace::NG {
class BorderImagePainter : public virtual AceType {
    DECLARE_ACE_TYPE(BorderImagePainter, AceType);

public:
    BorderImagePainter(bool hasBorderWidthProperty, const BorderImageProperty& borderImageProperty,
        const BorderWidthProperty& borderWidthProperty, const SizeF& paintSize, const RSImage& image, double dipscale)
        : hasBorderWidthProperty_(hasBorderWidthProperty), borderImageProperty_(borderImageProperty),
          borderWidthProperty_(borderWidthProperty), paintSize_(paintSize), rsImage(image), dipscale_(dipscale)
    {
        imageWidth_ = rsImage.GetWidth();
        imageHeight_ = rsImage.GetHeight();
        InitPainter();
    }
    ~BorderImagePainter() override = default;
    void PaintBorderImage(const OffsetF& offset, RSCanvas& canvas) const;

private:
    void InitPainter();
    void PaintBorderImageCorners(const OffsetF& offset, RSCanvas& canvas) const;
    void PaintBorderImageStretch(const OffsetF& offset, RSCanvas& canvas) const;
    void PaintBorderImageRound(const OffsetF& offset, RSCanvas& canvas) const;
    void PaintBorderImageSpace(const OffsetF& offset, RSCanvas& canvas) const;
    void PaintBorderImageRepeat(const OffsetF& offset, RSCanvas& canvas) const;
    void FillBorderImageCenter(const OffsetF& offset, RSCanvas& canvas) const;

    void InitBorderImageSlice();
    void InitBorderImageWidth();
    void InitBorderImageOutset();
    void ParseNegativeNumberToZeroOrCeil(double& value);

    bool hasBorderWidthProperty_;
    BorderImageProperty borderImageProperty_;
    BorderWidthProperty borderWidthProperty_;
    SizeF paintSize_;
    RSImage rsImage;

    double imageWidth_ = 0.0;
    double imageHeight_ = 0.0;
    double imageCenterWidth_ = 0.0;
    double imageCenterHeight_ = 0.0;
    double borderCenterWidth_ = 0.0;
    double borderCenterHeight_ = 0.0;

    double dipscale_ = 0.0;
    double leftWidth_ = 0.0;
    double topWidth_ = 0.0;
    double rightWidth_ = 0.0;
    double bottomWidth_ = 0.0;

    double leftSlice_ = 0.0;
    double topSlice_ = 0.0;
    double rightSlice_ = 0.0;
    double bottomSlice_ = 0.0;

    double leftOutset_ = 0.0;
    double topOutset_ = 0.0;
    double rightOutset_ = 0.0;
    double bottomOutset_ = 0.0;

    RSRect srcRectLeft_;
    RSRect srcRectRight_;
    RSRect srcRectTop_;
    RSRect srcRectBottom_;

    bool paintCornersOnly_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_BORDER_IMAGE_PAINT_H
