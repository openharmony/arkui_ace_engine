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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_PAINTER_SKIA_DECORATION_PAINTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_PAINTER_SKIA_DECORATION_PAINTER_H

#include "include/core/SkCanvas.h"
#include "include/core/SkMaskFilter.h"
#include "include/core/SkPaint.h"
#include "include/core/SkPath.h"
#include "include/core/SkRRect.h"
#include "include/core/SkShader.h"

#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components/common/properties/clip_path.h"
#include "core/components_ng/property/gradient_property.h"

namespace OHOS::Rosen::Drawing {
class Image;
} // namespace OHOS::Rosen::Drawing

namespace OHOS::Ace::NG {
using RSImage = Rosen::Drawing::Image;
class SkiaDecorationPainter : public virtual AceType {
    DECLARE_ACE_TYPE(SkiaDecorationPainter, AceType);

public:
    SkiaDecorationPainter() = default;
    ~SkiaDecorationPainter() override = default;
    static float ConvertRadiusToSigma(float radius)
    {
        constexpr float BlurSigmaScale = 0.57735f;
        return radius > 0.0f ? BlurSigmaScale * radius + SK_ScalarHalf : 0.0f;
    }

    static sk_sp<SkShader> CreateGradientShader(const NG::Gradient& gradient, const SizeF& size);
    static SkPath SkiaCreateSkPath(const RefPtr<BasicShape>& basicShape, const SizeF& size);
    static void SkiaCreateInset(
        const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, SkPath& skPath);
    static void SkiaCreateCircle(
        const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, SkPath& skPath);
    static void SkiaCreateEllipse(
        const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, SkPath& skPath);
    static void SkiaCreatePolygon(
        const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, SkPath& skPath);
    static void SkiaCreatePath(
        const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, SkPath& skPath);
    static void SkiaCreateRect(
        const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, SkPath& skPath);
    static float SkiaDimensionToPx(const Dimension& value, const SizeF& size, LengthMode type);
    static float SkiaGetFloatRadiusValue(
        const Dimension& src, const Dimension& dest, const SizeF& size, LengthMode type);

    static void PaintGrayScale(const SkRRect& rRect, SkCanvas* canvas, float grayscale);
    static void PaintBrightness(const SkRRect& rRect, SkCanvas* canvas, float brightness);
    static void PaintContrast(const SkRRect& rRect, SkCanvas* canvas, float contrast);
    static void PaintColorBlend(
        const SkRRect& rRect, SkCanvas* canvas, const Color& colorBlend);
    static void PaintSaturate(const SkRRect& rRect, SkCanvas* canvas, float saturate);
    static void PaintSepia(const SkRRect& rRect, SkCanvas* canvas, float sepia);
    static void PaintInvert(const SkRRect& rRect, SkCanvas* canvas, float invert);
    static void PaintHueRotate(const SkRRect& rRect, SkCanvas* canvas, float hueRotate);
    static SkPaint CreateMaskSkPaint(const RefPtr<BasicShape>& basicShape);
    static RSImage CreateBorderImageGradient(const NG::Gradient& gradients, const SizeF& paintSize);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_PAINTER_DECORATION_PAINTER_H
