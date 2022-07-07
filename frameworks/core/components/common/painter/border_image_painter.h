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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_PAINTER_BORDER_IMAGE_PAINTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_PAINTER_BORDER_IMAGE_PAINTER_H

#include <cmath>

#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/edge.h"

namespace OHOS::Ace {
class BorderImagePainter : public virtual AceType {
    DECLARE_ACE_TYPE(BorderImagePainter, AceType);
public:
    BorderImagePainter(const Size& paintSize, const RefPtr<Decoration>& decoration, const sk_sp<SkImage>& image,
        double dipscale);
    ~BorderImagePainter() = default;
    void InitPainter();
    void UpdateExtraOffsetToPaintSize(const Offset& offset);
    void PaintBorderImage(const Offset& offset, SkCanvas* canvas, SkPaint& paint);
    static sk_sp<SkShader> CreateGradientShader(const Gradient& gradient, const SkSize& size, double dipScale);
private:
    void PaintBorderImageCorners(const Offset& offset, SkCanvas* canvas, SkPaint& paint);
    void PaintBorderImageStretch(const Offset& offset, SkCanvas* canvas, SkPaint& paint);
    void PaintBorderImageRound(const Offset& offset, SkCanvas* canvas, SkPaint& paint);
    void PaintBorderImageSpace(const Offset& offset, SkCanvas* canvas, SkPaint& paint);
    void PaintBorderImageRepeat(const Offset& offset, SkCanvas* canvas, SkPaint& paint);
    void FillBorderImageCenter(const Offset& offset, SkCanvas* canvas, SkPaint& paint);

    void InitBorderImageWidth(Border& border, RefPtr<BorderImage>& borderImage);
    void InitBorderImageSlice(RefPtr<BorderImage>& borderImage);
    void InitBorderImageOutset(Border& border, RefPtr<BorderImage>& borderImage);
    void ParseNegativeNumberToZeroOrCeil(double& value);

    Size paintSize_;
    RefPtr<Decoration> decoration_;
    sk_sp<SkImage> image_;
    
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

    SkRect srcRectLeft_;
    SkRect srcRectRight_;
    SkRect srcRectTop_;
    SkRect srcRectBottom_;

    bool paintCornersOnly_ = false;
};
}

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_PAINTER_ROSEN_DEBUG_BOUNDARY_PAINTER_H