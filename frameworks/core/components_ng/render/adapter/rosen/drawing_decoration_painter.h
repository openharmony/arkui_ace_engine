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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_ROSEN_DRAWING_DECORATION_PAINTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_ROSEN_DRAWING_DECORATION_PAINTER_H

#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components/common/properties/clip_path.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
class DrawingDecorationPainter : public virtual AceType {
    DECLARE_ACE_TYPE(DrawingDecorationPainter, AceType);

public:
    DrawingDecorationPainter() = default;
    ~DrawingDecorationPainter() override = default;
    static float ConvertRadiusToSigma(float radius)
    {
        constexpr float BLUR_SIGMA_SCALE = 0.57735f;
        constexpr float SCALE_HALF = 0.5f;
        return radius > 0.0f ? BLUR_SIGMA_SCALE * radius + SCALE_HALF : 0.0f;
    }

    static std::shared_ptr<RSShaderEffect> CreateGradientShader(const NG::Gradient& gradient, const SizeF& size);
    static RSRecordingPath DrawingCreatePath(const RefPtr<BasicShape>& basicShape, const SizeF& size);
    static void DrawingCreateInset(
        const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, RSPath& rsPath);
    static void DrawingCreateCircle(
        const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, RSPath& rsPath);
    static void DrawingCreateEllipse(
        const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, RSPath& rsPath);
    static void DrawingCreatePolygon(
        const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, RSPath& rsPath);
    static void DrawingCreatePath(
        const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, RSPath& rsPath);
    static void DrawingCreateRect(
        const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, RSPath& rsPath);
    static float DrawingDimensionToPx(const Dimension& value, const SizeF& size, LengthMode type);
    static float DrawingGetFloatRadiusValue(
        const Dimension& src, const Dimension& dest, const SizeF& size, LengthMode type);

    static void PaintGrayScale(const RSRoundRect& frameSize, RSCanvas* canvas, float grayscale);
    static void PaintBrightness(const RSRoundRect& frameSize, RSCanvas* canvas, float brightness);
    static void PaintContrast(const RSRoundRect& frameSize, RSCanvas* canvas, float contrast);
    static void PaintColorBlend(const RSRoundRect& frameSize, RSCanvas* canvas, const Color& colorBlend);
    static void PaintSaturate(const RSRoundRect& frameSize, RSCanvas* canvas, float saturate);
    static void PaintSepia(const RSRoundRect& frameSize, RSCanvas* canvas, float sepia);
    static void PaintInvert(const RSRoundRect& frameSize, RSCanvas* canvas, float invert);
    static void PaintHueRotate(const RSRoundRect& frameSize, RSCanvas* canvas, float hueRotate);
    static RSBrush CreateMaskDrawingBrush(const RefPtr<BasicShape>& basicShape);
    static RSImage CreateBorderImageGradient(const NG::Gradient& gradients, const SizeF& paintSize);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_ROSEN_DRAWING_DECORATION_PAINTER_H
