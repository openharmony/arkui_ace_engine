/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_PAINTER_FLUTTER_DECORATION_PAINTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_PAINTER_FLUTTER_DECORATION_PAINTER_H

#include "flutter/lib/ui/ui_dart_state.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/border_edge.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/edge.h"
#include "core/components/image/render_image.h"
#include "core/pipeline/base/flutter_render_context.h"
#include "core/pipeline/layers/clip_layer.h"

namespace flutter {
class Canvas;
class Paint;
class PaintData;
} // namespace flutter

namespace OHOS::Ace {

class Border;
class Offset;
class Size;

class FlutterDecorationPainter : public virtual AceType {
    DECLARE_ACE_TYPE(FlutterDecorationPainter, AceType);

public:
    FlutterDecorationPainter(
        const RefPtr<Decoration>& decoration, const Rect& paintRect, const Size& paintSize, double dipScale);
    ~FlutterDecorationPainter() override = default;

    static void PaintShadow(const SkPath& path, const Shadow& shadow, SkCanvas* canvas);

    static float ConvertRadiusToSigma(float radius);

    void PaintDecoration(const Offset& offset, SkCanvas* canvas, RenderContext& context);

    void PaintBoxShadows(const SkRRect& rrect, const std::vector<Shadow>& shadows, SkCanvas* canvas);

    void PaintBlur(const flutter::RRect& outerRRect, SkCanvas* canvas, const Dimension& blurRadius);

    flutter::RRect GetBoxOuterRRect(const Offset& offset);

    void SetAlpha(uint8_t opacity)
    {
        opacity_ = opacity;
    }

    void SetMargin(const EdgePx& margin)
    {
        margin_ = margin;
    }

    void SetRenderImage(const RefPtr<RenderImage>& renderImage)
    {
        renderImage_ = renderImage;
    }

    void SetClipLayer(const RefPtr<Flutter::ClipLayer>& clipLayer)
    {
        clipLayer_ = clipLayer;
    }

    void SetDecoration(const RefPtr<Decoration>& decoration)
    {
        decoration_ = decoration;
    }

    flutter::RRect GetBoxRRect(const Offset& offset, const Border& border, double shrinkFactor, bool isRound);

protected:
    void PaintColorAndImage(const Offset& offset, SkCanvas* canvas, SkPaint& paint, RenderContext& context);

    void PaintAllEqualBorder(const flutter::RRect& rrect, const Border& border, SkCanvas* canvas, SkPaint& paint);

    void SetBorderStyle(const BorderEdge& borderEdge, SkPaint& paint, bool useDefaultColor = false);

    void PaintBorder(const Offset& offset, const Border& border, SkCanvas* canvas, SkPaint& paint);

    void PaintImage(const Offset& offset, RenderContext& context);

    void PaintGradient(const Offset& offset, SkCanvas* canvas, SkPaint& paint);

    void GetShaderForRepeat(const Offset& offset, const Gradient& gradient, SkPaint& paint);
    void GetShaderForClamp(const Offset& offset, const Gradient& gradient, SkPaint& paint) const;

    float GetShaderPercent(const Dimension& dimension, const Gradient& gradient) const;
    SkPoint GetShaderStopPoint(const Offset& offset, const Dimension& dimension, const Gradient& gradient) const;

    double GetShaderPercentByDirection(const Dimension& dimension, const Gradient& gradient) const;
    double GetShaderPercentByAngle(const Dimension& dimension, double angle) const;
    SkPoint GetShaderStopPointByAngle(const Offset& offset, const Dimension& dimension, double angle) const;
    SkPoint GetBeginPointByAngle(const Offset& offset, double angle) const;
    SkPoint GetBeginPointByDirection(const Offset& offset, const Gradient& gradient) const;
    SkPoint GetShaderStopPointByDirection(
        const Offset& offset, const Dimension& dimension, const Gradient& gradient) const;
    SkPoint GetShaderStopPointLeftTop(const Offset& offset, const Dimension& dimension) const;
    SkPoint GetShaderStopPointLeftBottom(const Offset& offset, const Dimension& dimension) const;
    SkPoint GetShaderStopPointRightTop(const Offset& offset, const Dimension& dimension) const;
    SkPoint GetShaderStopPointRightBottom(const Offset& offset, const Dimension& dimension) const;

    double GetShaderPercentEq0Degrees(const Dimension& dimension) const;
    double GetDiagonalAngle(double angle) const;
    double GetShaderPercentForAngle(const Dimension& dimension, double diagonalAngle, double angle) const;
    double GetShaderPercentEq90Degrees(const Dimension& dimension) const;

    SkPoint GetShaderStopPointEq0Degrees(const Offset& offset, const Dimension& dimension) const;
    SkPoint GetShaderStopPointEq90Degrees(const Offset& offset, const Dimension& dimension) const;
    SkPoint GetShaderStopPointEq180Degrees(const Offset& offset, const Dimension& dimension) const;
    SkPoint GetShaderStopPointEq270Degrees(const Offset& offset, const Dimension& dimension) const;
    SkPoint GetShaderStopPointLT90Degrees(
        const Offset& offset, const Dimension& dimension, double angle, double diagonalAngle) const;
    SkPoint GetShaderStopPointLT180Degrees(
        const Offset& offset, const Dimension& dimension, double angle, double diagonalAngle) const;
    SkPoint GetShaderStopPointLT270Degrees(
        const Offset& offset, const Dimension& dimension, double angle, double diagonalAngle) const;
    SkPoint GetShaderStopPointLT360Degrees(
        const Offset& offset, const Dimension& dimension, double angle, double diagonalAngle) const;

    double GetLeftOffset(const Offset& offset) const;
    double GetRightOffset(const Offset& offset) const;
    double GetTopOffset(const Offset& offset) const;
    double GetBottomOffset(const Offset& offset) const;

    SkPoint GetGradientBeginPoint(const Offset& offset, const Gradient& gradient) const;
    SkPoint GetGradientEndPoint(const Offset& offset, const Gradient& gradient) const;

    double GetRectHypotenuse() const;
    double GetHypotenuse(const Dimension& dimension, double diagonalAngle, double angle) const;
    double GetHypotenuseAngle(double angle, double diagonalAngle) const;

    void RecalculatePosition(float pos[], int32_t colorsSize) const;

    bool CheckBorderAllEqual(const Border& border);

    bool CheckBorderEdgeForRRect(const Border& border);

    double NormalizeToPx(const Dimension& dimension) const;

    Size GetLayoutSize() const
    {
        return paintRect_.GetSize();
    }

    double dipScale_ = 1.0;
    Rect paintRect_;

    RefPtr<Decoration> decoration_;
    Size paintSize_; // exclude margin
    EdgePx margin_;
    double scale_ = 0.0;
    uint8_t opacity_ = UINT8_MAX;

    RefPtr<RenderImage> renderImage_;
    RefPtr<Flutter::ClipLayer> clipLayer_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_PAINTER_FLUTTER_DECORATION_PAINTER_H
