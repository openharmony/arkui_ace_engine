/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components/common/painter/rosen_svg_painter.h"

#include "include/utils/SkParsePath.h"
#include "frameworks/core/components/svg/rosen_render_svg_pattern.h"

namespace OHOS::Ace {

namespace {

constexpr float FLAT_ANGLE = 180.0f;
const char ROTATE_TYPE_AUTO[] = "auto";
const char ROTATE_TYPE_REVERSE[] = "auto-reverse";

} // namespace

#ifndef USE_ROSEN_DRAWING
#if !defined(PREVIEW)
const char FONT_TYPE_HWCHINESE[] = "/system/fonts/HwChinese-Medium.ttf";
const char FONT_TYPE_DROIDSANS[] = "/system/fonts/DroidSans.ttf";
sk_sp<SkTypeface> RosenSvgPainter::fontTypeChinese_ = SkTypeface::MakeFromFile(FONT_TYPE_HWCHINESE);
sk_sp<SkTypeface> RosenSvgPainter::fontTypeNormal_ = SkTypeface::MakeFromFile(FONT_TYPE_DROIDSANS);
#else
sk_sp<SkTypeface> RosenSvgPainter::fontTypeChinese_;
sk_sp<SkTypeface> RosenSvgPainter::fontTypeNormal_;
#endif
#else
#if !defined(PREVIEW)
const char FONT_TYPE_HWCHINESE[] = "/system/fonts/HwChinese-Medium.ttf";
const char FONT_TYPE_DROIDSANS[] = "/system/fonts/DroidSans.ttf";
std::shared_ptr<RSTypeface> RosenSvgPainter::fontTypeChinese_ = RSTypeface::MakeFromFile(FONT_TYPE_HWCHINESE);
std::shared_ptr<RSTypeface> RosenSvgPainter::fontTypeNormal_ = RSTypeface::MakeFromFile(FONT_TYPE_DROIDSANS);
#else
std::shared_ptr<RSTypeface> RosenSvgPainter::fontTypeChinese_;
std::shared_ptr<RSTypeface> RosenSvgPainter::fontTypeNormal_;
#endif
#endif

#ifndef USE_ROSEN_DRAWING
void RosenSvgPainter::SetMask(SkCanvas* canvas)
{
    SkPaint mask_filter;

    auto outerFilter = SkLumaColorFilter::Make();
    auto innerFilter = SkColorFilters::SRGBToLinearGamma();
    auto filter = SkColorFilters::Compose(outerFilter, std::move(innerFilter));
    mask_filter.setColorFilter(filter);
    canvas->saveLayer(nullptr, &mask_filter);
}
#else
void RosenSvgPainter::SetMask(RSCanvas* canvas)
{
    auto outerFilter = RSRecordingColorFilter::CreateLumaColorFilter();
    auto innerFilter = RSRecordingColorFilter::CreateSrgbGammaToLinear();
    auto colorFilter = RSRecordingColorFilter::CreateComposeColorFilter(*outerFilter, *innerFilter);
    RSFilter filter;
    filter.SetColorFilter(colorFilter);
    RSBrush mask_filter;
    mask_filter.SetFilter(filter);
    RSSaveLayerOps saveLayerRec(nullptr, &mask_filter);
    canvas->SaveLayer(saveLayerRec);
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenSvgPainter::SetFillStyle(SkPaint& skPaint, const FillState& fillState, uint8_t opacity, bool antiAlias)
{
    double curOpacity = fillState.GetOpacity().GetValue() * opacity * (1.0f / UINT8_MAX);
    skPaint.setStyle(SkPaint::Style::kFill_Style);
    skPaint.setAntiAlias(antiAlias);
    if (fillState.GetGradient()) {
        SetGradientStyle(skPaint, fillState, curOpacity);
    } else {
        skPaint.setColor(fillState.GetColor().BlendOpacity(curOpacity).GetValue());
    }
}
#else
void RosenSvgPainter::SetFillStyle(RSBrush& brush,
    const FillState& fillState, uint8_t opacity, bool antiAlias)
{
    double curOpacity = fillState.GetOpacity().GetValue() * opacity * (1.0f / UINT8_MAX);
    brush.SetAntiAlias(antiAlias);
    if (fillState.GetGradient()) {
        SetGradientStyle(brush, fillState, curOpacity);
    } else {
        brush.SetColor(fillState.GetColor().BlendOpacity(curOpacity).GetValue());
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenSvgPainter::SetFillStyle(
    SkCanvas* skCanvas, const SkPath& skPath, const FillState& fillState, uint8_t opacity, bool antiAlias)
{
    if (fillState.GetColor() == Color::TRANSPARENT && !fillState.GetGradient()) {
        return;
    }
    SkPaint paint;
    SetFillStyle(paint, fillState, opacity, antiAlias);
    skCanvas->drawPath(skPath, paint);
}
#else
void RosenSvgPainter::SetFillStyle(RSCanvas* canvas, const RSPath& path,
    const FillState& fillState, uint8_t opacity, bool antiAlias)
{
    if (fillState.GetColor() == Color::TRANSPARENT && !fillState.GetGradient()) {
        return;
    }
    RSBrush brush;
    SetFillStyle(brush, fillState, opacity, antiAlias);
    canvas->AttachBrush(brush);
    canvas->DrawPath(path);
    canvas->DetachBrush();
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenSvgPainter::SetGradientStyle(SkPaint& skPaint, const FillState& fillState, double opacity)
{
    auto gradient = fillState.GetGradient();
    if (!gradient) {
        return;
    }
    auto gradientColors = gradient->GetColors();
    if (gradientColors.empty()) {
        return;
    }
    std::vector<SkScalar> pos;
    std::vector<SkColor> colors;
    for (const auto& gradientColor : gradientColors) {
        pos.push_back(gradientColor.GetDimension().Value());
        colors.push_back(
            gradientColor.GetColor().BlendOpacity(gradientColor.GetOpacity()).BlendOpacity(opacity).GetValue());
    }
    if (gradient->GetType() == GradientType::LINEAR) {
        auto info = gradient->GetLinearGradientInfo();
        SkPoint pts[2] = { SkPoint::Make(info.x1, info.y1), SkPoint::Make(info.x2, info.y2) };

        skPaint.setShader(SkGradientShader::MakeLinear(pts, &colors[0], &pos[0], gradientColors.size(),
            static_cast<SkTileMode>(gradient->GetSpreadMethod()), 0, nullptr));
    }
    if (gradient->GetType() == GradientType::RADIAL) {
        auto info = gradient->GetRadialGradientInfo();
        auto center = SkPoint::Make(info.cx, info.cy);
        auto focal = SkPoint::Make(info.fx, info.fx);

        return center == focal
                   ? skPaint.setShader(SkGradientShader::MakeRadial(center, info.r, &colors[0], &pos[0],
                        gradientColors.size(), static_cast<SkTileMode>(gradient->GetSpreadMethod()), 0, nullptr))
                   : skPaint.setShader(
                        SkGradientShader::MakeTwoPointConical(focal, 0, center, info.r, &colors[0], &pos[0],
                            gradientColors.size(), static_cast<SkTileMode>(gradient->GetSpreadMethod()), 0, nullptr));
    }
}
#else
void RosenSvgPainter::SetGradientStyle(RSBrush& brush, const FillState& fillState, double opacity)
{
    auto gradient = fillState.GetGradient();
    if (!gradient) {
        return;
    }
    auto gradientColors = gradient->GetColors();
    if (gradientColors.empty()) {
        return;
    }
    std::vector<RSScalar> pos;
    std::vector<RSColorQuad> colors;
    for (const auto& gradientColor : gradientColors) {
        pos.push_back(gradientColor.GetDimension().Value());
        colors.push_back(
            gradientColor.GetColor().BlendOpacity(gradientColor.GetOpacity()).BlendOpacity(opacity).GetValue());
    }
    if (gradient->GetType() == GradientType::LINEAR) {
        auto info = gradient->GetLinearGradientInfo();
        RSPoint startPt = RSPoint(info.x1, info.y1);
        RSPoint endPt = RSPoint(info.x2, info.y2);
        brush.SetShaderEffect(RSRecordingShaderEffect::CreateLinearGradient(
            startPt, endPt, colors, pos, static_cast<RSTileMode>(gradient->GetSpreadMethod())));
    }
    if (gradient->GetType() == GradientType::RADIAL) {
        auto info = gradient->GetRadialGradientInfo();
        auto center = RSPoint(info.cx, info.cy);
        auto focal = RSPoint(info.fx, info.fx);
        RSMatrix matrix;
        return center == focal ? brush.SetShaderEffect(RSRecordingShaderEffect::CreateRadialGradient(center,
            info.r, colors, pos, static_cast<RSTileMode>(gradient->GetSpreadMethod())))
            : brush.SetShaderEffect(RSRecordingShaderEffect::CreateTwoPointConical(focal, 0, center,
            info.r, colors, pos, static_cast<RSTileMode>(gradient->GetSpreadMethod()), &matrix));
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenSvgPainter::SetFillStyle(
    SkCanvas* canvas, const SkPath& skPath, const FillState& fillState, RenderInfo& renderInfo)
{
    const auto& fillHref = fillState.GetHref();
    if (fillHref.empty() || fillState.GetGradient() || !renderInfo.node) {
        return SetFillStyle(canvas, skPath, fillState, renderInfo.opacity, renderInfo.antiAlias);
    }

    SkPaint skPaint;
    skPaint.reset();
    auto pattern = AceType::DynamicCast<RosenRenderSvgPattern>(renderInfo.node->GetPatternFromRoot(fillHref));
    if (!pattern) {
        return;
    }
    if (!pattern->OnAsPaint(renderInfo.offset, renderInfo.node->GetPaintBounds(renderInfo.offset), skPaint)) {
        return;
    }
    skPaint.setAlphaf(fillState.GetOpacity().GetValue() * renderInfo.opacity * (1.0f / UINT8_MAX));
    skPaint.setAntiAlias(renderInfo.antiAlias);
    canvas->drawPath(skPath, skPaint);
}
#else
void RosenSvgPainter::SetFillStyle(RSCanvas* canvas,
    const RSPath& path, const FillState& fillState, RenderInfo& renderInfo)
{
    const auto& fillHref = fillState.GetHref();
    if (fillHref.empty() || fillState.GetGradient() || !renderInfo.node) {
        return SetFillStyle(canvas, path, fillState, renderInfo.opacity, renderInfo.antiAlias);
    }

    RSBrush brush;
    brush.Reset();
    auto pattern = AceType::DynamicCast<RosenRenderSvgPattern>(renderInfo.node->GetPatternFromRoot(fillHref));
    if (!pattern) {
        return;
    }
    if (!pattern->OnAsPaint(renderInfo.offset, renderInfo.node->GetPaintBounds(renderInfo.offset), nullptr, &brush)) {
        return;
    }
    brush.SetAlphaF(fillState.GetOpacity().GetValue() * renderInfo.opacity * (1.0f / UINT8_MAX));
    brush.SetAntiAlias(renderInfo.antiAlias);
    canvas->AttachBrush(brush);
    canvas->DrawPath(path);
    canvas->DetachBrush();
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenSvgPainter::SetStrokeStyle(SkPaint& skPaint, const StrokeState& strokeState, uint8_t opacity, bool antiAlias)
{
    skPaint.setStyle(SkPaint::Style::kStroke_Style);
    double curOpacity = strokeState.GetOpacity().GetValue() * opacity * (1.0f / UINT8_MAX);
    skPaint.setColor(strokeState.GetColor().BlendOpacity(curOpacity).GetValue());
    if (strokeState.GetLineCap() == LineCapStyle::ROUND) {
        skPaint.setStrokeCap(SkPaint::Cap::kRound_Cap);
    } else if (strokeState.GetLineCap() == LineCapStyle::SQUARE) {
        skPaint.setStrokeCap(SkPaint::Cap::kSquare_Cap);
    } else {
        skPaint.setStrokeCap(SkPaint::Cap::kButt_Cap);
    }
    if (strokeState.GetLineJoin() == LineJoinStyle::ROUND) {
        skPaint.setStrokeJoin(SkPaint::Join::kRound_Join);
    } else if (strokeState.GetLineJoin() == LineJoinStyle::BEVEL) {
        skPaint.setStrokeJoin(SkPaint::Join::kBevel_Join);
    } else {
        skPaint.setStrokeJoin(SkPaint::Join::kMiter_Join);
    }
    skPaint.setStrokeWidth(static_cast<SkScalar>(strokeState.GetLineWidth().Value()));
    skPaint.setStrokeMiter(static_cast<SkScalar>(strokeState.GetMiterLimit()));
    skPaint.setAntiAlias(antiAlias);
    UpdateLineDash(skPaint, strokeState);
}
#else
void RosenSvgPainter::SetStrokeStyle(RSPen& pen,
    const StrokeState& strokeState, uint8_t opacity, bool antiAlias)
{
    double curOpacity = strokeState.GetOpacity().GetValue() * opacity * (1.0f / UINT8_MAX);
    pen.SetColor(strokeState.GetColor().BlendOpacity(curOpacity).GetValue());
    if (strokeState.GetLineCap() == LineCapStyle::ROUND) {
        pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    } else if (strokeState.GetLineCap() == LineCapStyle::SQUARE) {
        pen.SetCapStyle(RSPen::CapStyle::SQUARE_CAP);
    } else {
        pen.SetCapStyle(RSPen::CapStyle::FLAT_CAP);
    }
    if (strokeState.GetLineJoin() == LineJoinStyle::ROUND) {
        pen.SetJoinStyle(RSPen::JoinStyle::ROUND_JOIN);
    } else if (strokeState.GetLineJoin() == LineJoinStyle::BEVEL) {
        pen.SetJoinStyle(RSPen::JoinStyle::BEVEL_JOIN);
    } else {
        pen.SetJoinStyle(RSPen::JoinStyle::MITER_JOIN);
    }
    pen.SetWidth(static_cast<RSScalar>(strokeState.GetLineWidth().Value()));
    pen.SetMiterLimit(static_cast<RSScalar>(strokeState.GetMiterLimit()));
    pen.SetAntiAlias(antiAlias);
    UpdateLineDash(pen, strokeState);
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenSvgPainter::SetStrokeStyle(
    SkCanvas* skCanvas, const SkPath& skPath, const StrokeState& strokeState, uint8_t opacity, bool antiAlias)
{
    if (strokeState.GetColor() == Color::TRANSPARENT) {
        return;
    }
    if (GreatNotEqual(strokeState.GetLineWidth().Value(), 0.0)) {
        SkPaint paint;
        SetStrokeStyle(paint, strokeState, opacity, antiAlias);
        skCanvas->drawPath(skPath, paint);
    }
}
#else
void RosenSvgPainter::SetStrokeStyle(RSCanvas* canvas,
    const RSPath& path, const StrokeState& strokeState, uint8_t opacity, bool antiAlias)
{
    if (strokeState.GetColor() == Color::TRANSPARENT) {
        return;
    }
    if (GreatNotEqual(strokeState.GetLineWidth().Value(), 0.0)) {
        RSPen pen;
        SetStrokeStyle(pen, strokeState, opacity, antiAlias);
        canvas->AttachPen(pen);
        canvas->DrawPath(path);
        canvas->DetachPen();
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenSvgPainter::SetStrokeStyle(
    SkCanvas* skCanvas, const SkPath& skPath, const StrokeState& strokeState, RenderInfo& renderInfo)
{
    const auto& strokeHref = strokeState.GetHref();
    if (strokeHref.empty() || !renderInfo.node) {
        return SetStrokeStyle(skCanvas, skPath, strokeState, renderInfo.opacity, renderInfo.antiAlias);
    }

    if (GreatNotEqual(strokeState.GetLineWidth().Value(), 0.0)) {
        SkPaint paint;
        SetStrokeStyle(paint, strokeState, renderInfo.opacity, renderInfo.antiAlias);
        auto pattern = AceType::DynamicCast<RosenRenderSvgPattern>(renderInfo.node->GetPatternFromRoot(strokeHref));
        if (!pattern) {
            return;
        }
        if (!pattern->OnAsPaint(renderInfo.offset, renderInfo.node->GetPaintBounds(renderInfo.offset), paint)) {
            return;
        }
        skCanvas->drawPath(skPath, paint);
    }
}
#else
void RosenSvgPainter::SetStrokeStyle(RSCanvas* canvas,
    const RSPath& path, const StrokeState& strokeState, RenderInfo& renderInfo)
{
    const auto& strokeHref = strokeState.GetHref();
    if (strokeHref.empty() || !renderInfo.node) {
        return SetStrokeStyle(canvas, path, strokeState, renderInfo.opacity, renderInfo.antiAlias);
    }

    if (GreatNotEqual(strokeState.GetLineWidth().Value(), 0.0)) {
        RSPen pen;
        SetStrokeStyle(pen, strokeState, renderInfo.opacity, renderInfo.antiAlias);
        auto pattern = AceType::DynamicCast<RosenRenderSvgPattern>(renderInfo.node->GetPatternFromRoot(strokeHref));
        if (!pattern) {
            return;
        }
        if (!pattern->OnAsPaint(renderInfo.offset, renderInfo.node->GetPaintBounds(renderInfo.offset), &pen, nullptr)) {
            return;
        }
        canvas->AttachPen(pen);
        canvas->DrawPath(path);
        canvas->DetachPen();
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenSvgPainter::UpdateLineDash(SkPaint& paint, const StrokeState& strokeState)
{
    if (!strokeState.GetLineDash().lineDash.empty()) {
        auto lineDashState = strokeState.GetLineDash().lineDash;
        SkScalar intervals[lineDashState.size()];
        for (size_t i = 0; i < lineDashState.size(); ++i) {
            intervals[i] = SkDoubleToScalar(lineDashState[i]);
        }
        SkScalar phase = SkDoubleToScalar(strokeState.GetLineDash().dashOffset);
        paint.setPathEffect(SkDashPathEffect::Make(intervals, lineDashState.size(), phase));
    }
}
#else
void RosenSvgPainter::UpdateLineDash(RSPen& pen, const StrokeState& strokeState)
{
    if (!strokeState.GetLineDash().lineDash.empty()) {
        auto lineDashState = strokeState.GetLineDash().lineDash;
        RSScalar intervals[lineDashState.size()];
        for (size_t i = 0; i < lineDashState.size(); ++i) {
            intervals[i] = static_cast<RSScalar>(lineDashState[i]);
        }
        RSScalar phase = static_cast<RSScalar>(strokeState.GetLineDash().dashOffset);
        pen.SetPathEffect(RSRecordingPathEffect::CreateDashPathEffect(intervals, lineDashState.size(), phase));
    }
}
#endif

void RosenSvgPainter::CheckFontType()
{
    if (!fontTypeChinese_) {
        LOGW("can't load HwChinese-Medium.ttf");
    }
    if (!fontTypeNormal_) {
        LOGW("can't load DroidSans.ttf");
    }
}

#ifndef USE_ROSEN_DRAWING
double RosenSvgPainter::GetPathLength(const std::string& path)
{
    SkPath skPath;
    SkParsePath::FromSVGString(path.c_str(), &skPath);
    SkPathMeasure pathMeasure(skPath, false);
    SkScalar length = pathMeasure.getLength();
    return length;
}
#else
double RosenSvgPainter::GetPathLength(const std::string& path)
{
    RSRecordingPath drawPath;
    drawPath.BuildFromSVGString(path.c_str());
    auto length = drawPath.GetLength(false);
    return length;
}
#endif

#ifndef USE_ROSEN_DRAWING
Offset RosenSvgPainter::GetPathOffset(const std::string& path, double current)
{
    SkPath skPath;
    SkParsePath::FromSVGString(path.c_str(), &skPath);
    SkPathMeasure pathMeasure(skPath, false);
    SkPoint position;
    if (!pathMeasure.getPosTan(current, &position, nullptr)) {
        return Offset(0.0, 0.0);
    }
    return Offset(position.fX, position.fY);
}
#else
Offset RosenSvgPainter::GetPathOffset(const std::string& path, double current)
{
    RSRecordingPath drawPath;
    drawPath.BuildFromSVGString(path.c_str());
    RSPoint position;
    RSPoint tangent;
    if (!drawPath.GetPositionAndTangent(current, position, tangent, false)) {
        return Offset(0.0, 0.0);
    }
    return Offset(position.GetX(), position.GetY());
}
#endif

bool RosenSvgPainter::GetMotionPathPosition(const std::string& path, double percent, MotionPathPosition& result)
{
    if (path.empty()) {
        return false;
    }
#ifndef USE_ROSEN_DRAWING
    SkPath motion;
    SkParsePath::FromSVGString(path.c_str(), &motion);
    SkPathMeasure pathMeasure(motion, false);
    SkPoint position;
    SkVector tangent;
    bool ret = pathMeasure.getPosTan(pathMeasure.getLength() * percent, &position, &tangent);
    if (!ret) {
        return false;
    }
    result.rotate = SkRadiansToDegrees(std::atan2(tangent.y(), tangent.x()));
    result.offset.SetX(position.x());
    result.offset.SetY(position.y());
#else
    RSRecordingPath motion;
    motion.BuildFromSVGString(path.c_str());
    RSPoint position;
    RSPoint tangent;
    bool ret = motion.GetPositionAndTangent(motion.GetLength(false) * percent, position, tangent, false);
    if (!ret) {
        return false;
    }
    result.rotate = Rosen::Drawing::ConvertRadiansToDegrees(std::atan2(tangent.GetY(), tangent.GetX()));
    result.offset.SetX(position.GetX());
    result.offset.SetY(position.GetY());
#endif
    return true;
}

#ifndef USE_ROSEN_DRAWING
Offset RosenSvgPainter::UpdateText(SkCanvas* canvas, const SvgTextInfo& svgTextInfo, const TextDrawInfo& textDrawInfo)
{
    Offset offset = textDrawInfo.offset;
    if (!canvas) {
        LOGE("Paint skCanvas is null");
        return offset;
    }

    SkFont font;
    font.setSize(svgTextInfo.textStyle.GetFontSize().Value());
    font.setScaleX(1.0);

    double space = 0.0;
    SkScalar x = SkDoubleToScalar(offset.GetX());
    SkScalar y = SkDoubleToScalar(offset.GetY());
    std::wstring data = StringUtils::ToWstring(svgTextInfo.data);

    SkPaint paint;
    SkPaint strokePaint;
    RosenSvgPainter::SetFillStyle(paint, svgTextInfo.fillState, svgTextInfo.opacity);
    RosenSvgPainter::SetStrokeStyle(strokePaint, svgTextInfo.strokeState, svgTextInfo.opacity);

    for (int i = 0; i < (int)data.size(); i++) {
        wchar_t temp = data[i];
        if (temp >= 0x4e00 && temp <= 0x9fa5) {
            // range of chinese
            font.setTypeface(fontTypeChinese_);
        } else {
            font.setTypeface(fontTypeNormal_);
        }
        auto blob = SkTextBlob::MakeFromText(&temp, sizeof(temp), font, SkTextEncoding::kUTF16);
#ifdef WINDOWS_PLATFORM
        auto width = font.measureText(&temp, 4, SkTextEncoding::kUTF16);
#else
        auto width = font.measureText(&temp, sizeof(temp), SkTextEncoding::kUTF16);
#endif

        canvas->save();
        canvas->rotate(textDrawInfo.rotate, x, y);
        canvas->drawTextBlob(blob.get(), x, y, paint);
        if (svgTextInfo.strokeState.HasStroke() && !NearZero(svgTextInfo.strokeState.GetLineWidth().Value())) {
            canvas->drawTextBlob(blob.get(), x, y, strokePaint);
        }
        canvas->restore();
        x = x + width + space;
    }

    return Offset(x, y);
}
#else
Offset RosenSvgPainter::UpdateText(RSCanvas* canvas, const SvgTextInfo& svgTextInfo, const TextDrawInfo& textDrawInfo)
{
    Offset offset = textDrawInfo.offset;
    if (!canvas) {
        LOGE("Paint skCanvas is null");
        return offset;
    }

    RSFont font;
    font.SetSize(svgTextInfo.textStyle.GetFontSize().Value());
    font.SetScaleX(1.0);

    double space = 0.0;
    SkScalar x = SkDoubleToScalar(offset.GetX());
    SkScalar y = SkDoubleToScalar(offset.GetY());
    std::wstring data = StringUtils::ToWstring(svgTextInfo.data);

    RSBrush brush;
    RSPen strokePen;
    RosenSvgPainter::SetFillStyle(brush, svgTextInfo.fillState, svgTextInfo.opacity);
    RosenSvgPainter::SetStrokeStyle(strokePen, svgTextInfo.strokeState, svgTextInfo.opacity);

    for (int i = 0; i < (int)data.size(); i++) {
        wchar_t temp = data[i];
        if (temp >= 0x4e00 && temp <= 0x9fa5) {
            // range of chinese
            font.SetTypeface(fontTypeChinese_);
        } else {
            font.SetTypeface(fontTypeNormal_);
        }
        auto blob = RSTextBlob::MakeFromText(&temp, sizeof(temp), font, RSTextEncoding::UTF16);
#ifdef WINDOWS_PLATFORM
        auto width = font.MeasureText(&temp, 4, RSTextEncoding::UTF16);
#else
        auto width = font.MeasureText(&temp, sizeof(temp), RSTextEncoding::UTF16);
#endif

        canvas->Save();
        canvas->Rotate(textDrawInfo.rotate, x, y);
        canvas->AttachBrush(brush);
        canvas->DrawTextBlob(blob.get(), x, y);
        canvas->DetachBrush();
        if (svgTextInfo.strokeState.HasStroke() && !NearZero(svgTextInfo.strokeState.GetLineWidth().Value())) {
            canvas->AttachPen(strokePen);
            canvas->DrawTextBlob(blob.get(), x, y);
            canvas->DetachPen();
        }
        canvas->Restore();
        x = x + width + space;
    }

    return Offset(x, y);
}
#endif

#ifndef USE_ROSEN_DRAWING
double RosenSvgPainter::UpdateTextPath(
    SkCanvas* canvas, const SvgTextInfo& svgTextInfo, const PathDrawInfo& pathDrawInfo)
{
    double offset = pathDrawInfo.offset;
    if (!canvas) {
        LOGE("Paint skCanvas is null");
        return offset;
    }

    SkFont font;
    font.setSize(svgTextInfo.textStyle.GetFontSize().Value());
    font.setScaleX(1.0);
    double space = 0.0;
    std::wstring data = StringUtils::ToWstring(svgTextInfo.data);

    SkPaint paint;
    SkPaint strokePaint;
    RosenSvgPainter::SetFillStyle(paint, svgTextInfo.fillState, svgTextInfo.opacity);
    RosenSvgPainter::SetStrokeStyle(strokePaint, svgTextInfo.strokeState, svgTextInfo.opacity);

    SkPath path;
    SkParsePath::FromSVGString(pathDrawInfo.path.c_str(), &path);
    SkPathMeasure pathMeasure(path, false);
    SkScalar length = pathMeasure.getLength();

    for (int i = 0; i < (int)data.size(); i++) {
        wchar_t temp = data[i];
        if (temp >= 0x4e00 && temp <= 0x9fa5) {
            font.setTypeface(fontTypeChinese_);
        } else {
            font.setTypeface(fontTypeNormal_);
        }
#ifdef WINDOWS_PLATFORM
        auto width = font.measureText(&temp, 4, SkTextEncoding::kUTF16);
#else
        auto width = font.measureText(&temp, sizeof(wchar_t), SkTextEncoding::kUTF16);
#endif
        if (length < offset + width + space) {
            break;
        }
        if (offset < 0) {
            offset += (width + space);
            continue;
        }

        SkPoint position;
        SkVector tangent;
        if (!pathMeasure.getPosTan(offset + width / 2.0, &position, &tangent)) {
            break;
        }
        if (!pathMeasure.getPosTan(offset, &position, nullptr)) {
            break;
        }
        SkRSXform rsxForm = SkRSXform::Make(tangent.fX, tangent.fY, position.fX, position.fY);
        auto blob = SkTextBlob::MakeFromRSXform(&temp, sizeof(wchar_t), &rsxForm, font, SkTextEncoding::kUTF16);

        canvas->save();
        canvas->rotate(pathDrawInfo.rotate, position.fX, position.fY);
        canvas->drawTextBlob(blob.get(), 0.0, 0.0, paint);
        if (svgTextInfo.strokeState.HasStroke() && !NearZero(svgTextInfo.strokeState.GetLineWidth().Value())) {
            canvas->drawTextBlob(blob.get(), 0.0, 0.0, strokePaint);
        }
        canvas->restore();
        offset = offset + width + space;
    }

    return offset;
}
#else
double RosenSvgPainter::UpdateTextPath(
    RSCanvas* canvas, const SvgTextInfo& svgTextInfo, const PathDrawInfo& pathDrawInfo)
{
    double offset = pathDrawInfo.offset;
    if (!canvas) {
        LOGE("Paint skCanvas is null");
        return offset;
    }

    RSFont font;
    font.SetSize(svgTextInfo.textStyle.GetFontSize().Value());
    font.SetScaleX(1.0);
    double space = 0.0;
    std::wstring data = StringUtils::ToWstring(svgTextInfo.data);

    RSBrush brush;
    RSPen strokePen;
    RosenSvgPainter::SetFillStyle(brush, svgTextInfo.fillState, svgTextInfo.opacity);
    RosenSvgPainter::SetStrokeStyle(strokePen, svgTextInfo.strokeState, svgTextInfo.opacity);

    RSPath path;
    path.BuildFromSVGString(pathDrawInfo.path);
    RSScalar length = path.GetLength(false);

    for (int i = 0; i < (int)data.size(); i++) {
        wchar_t temp = data[i];
        if (temp >= 0x4e00 && temp <= 0x9fa5) {
            font.SetTypeface(fontTypeChinese_);
        } else {
            font.SetTypeface(fontTypeNormal_);
        }
#ifdef WINDOWS_PLATFORM
        auto width = font.MeasureText(&temp, 4, RSTextEncoding::UTF16);
#else
        auto width = font.MeasureText(&temp, sizeof(wchar_t), RSTextEncoding::UTF16);
#endif
        if (length < offset + width + space) {
            break;
        }
        if (offset < 0) {
            offset += (width + space);
            continue;
        }

        RSPoint position;
        RSPoint tangent;
        if (!path.GetPositionAndTangent(offset + width / 2.0, position, tangent, false)) {
            break;
        }
        RSPoint tempTangent;
        if (!path.GetPositionAndTangent(offset, position, tempTangent, false)) {
            break;
        }
        RSXform rsxForm = RSXform::Make(tangent.GetX(), tangent.GetY(), position.GetX(), position.GetY());
        auto blob = RSTextBlob::MakeFromRSXform(&temp, sizeof(wchar_t), &rsxForm, font, RSTextEncoding::UTF16);

        canvas->Save();
        canvas->Rotate(pathDrawInfo.rotate, position.GetX(), position.GetY());
        canvas->AttachBrush(brush);
        canvas->DrawTextBlob(blob.get(), 0.0, 0.0);
        canvas->DetachBrush();
        if (svgTextInfo.strokeState.HasStroke() && !NearZero(svgTextInfo.strokeState.GetLineWidth().Value())) {
            canvas->AttachPen(strokePen);
            canvas->DrawTextBlob(blob.get(), 0.0, 0.0);
            canvas->DetachPen();
        }
        canvas->Restore();
        offset = offset + width + space;
    }

    return offset;
}
#endif

#ifndef USE_ROSEN_DRAWING
Offset RosenSvgPainter::MeasureTextBounds(
    const SvgTextInfo& svgTextInfo, const TextDrawInfo& textDrawInfo, Rect& bounds)
{
    Offset offset = textDrawInfo.offset;
    SkFont font;

    font.setSize(svgTextInfo.textStyle.GetFontSize().Value());
    font.setScaleX(1.0);
    double space = 0.0;
    SkScalar x = SkDoubleToScalar(offset.GetX());
    SkScalar y = SkDoubleToScalar(offset.GetY());
    std::wstring data = StringUtils::ToWstring(svgTextInfo.data);

    for (int i = 0; i < (int)data.size(); i++) {
        wchar_t temp = data[i];
        if (temp >= 0x4e00 && temp <= 0x9fa5) {
            // range of chinese
            font.setTypeface(fontTypeChinese_);
        } else {
            font.setTypeface(fontTypeNormal_);
        }
        auto width = font.measureText(&temp, sizeof(temp), SkTextEncoding::kUTF16);
        x = x + width + space;
    }
    bounds.SetWidth(fmax(x, bounds.Width()));
    bounds.SetHeight(fmax(y, bounds.Height()));

    return Offset(x, y);
}
#else
Offset RosenSvgPainter::MeasureTextBounds(
    const SvgTextInfo& svgTextInfo, const TextDrawInfo& textDrawInfo, Rect& bounds)
{
    Offset offset = textDrawInfo.offset;
    RSFont font;

    font.SetSize(svgTextInfo.textStyle.GetFontSize().Value());
    font.SetScaleX(1.0);
    double space = 0.0;
    SkScalar x = SkDoubleToScalar(offset.GetX());
    SkScalar y = SkDoubleToScalar(offset.GetY());
    std::wstring data = StringUtils::ToWstring(svgTextInfo.data);

    for (int i = 0; i < (int)data.size(); i++) {
        wchar_t temp = data[i];
        if (temp >= 0x4e00 && temp <= 0x9fa5) {
            // range of chinese
            font.SetTypeface(fontTypeChinese_);
        } else {
            font.SetTypeface(fontTypeNormal_);
        }
        auto width = font.MeasureText(&temp, sizeof(temp), RSTextEncoding::UTF16);
        x = x + width + space;
    }
    bounds.SetWidth(fmax(x, bounds.Width()));
    bounds.SetHeight(fmax(y, bounds.Height()));

    return Offset(x, y);
}
#endif

#ifndef USE_ROSEN_DRAWING
double RosenSvgPainter::MeasureTextPathBounds(
    const SvgTextInfo& svgTextInfo, const PathDrawInfo& pathDrawInfo, Rect& bounds)
{
    double offset = pathDrawInfo.offset;

    SkFont font;
    font.setSize(svgTextInfo.textStyle.GetFontSize().Value());
    font.setScaleX(1.0);
    double space = 0.0;
    std::wstring data = StringUtils::ToWstring(svgTextInfo.data);

    SkPath path;
    SkParsePath::FromSVGString(pathDrawInfo.path.c_str(), &path);
    SkPathMeasure pathMeasure(path, false);
    SkScalar length = pathMeasure.getLength();

    for (int i = 0; i < (int)data.size(); i++) {
        wchar_t temp = data[i];
        if (temp >= 0x4e00 && temp <= 0x9fa5) {
            font.setTypeface(fontTypeChinese_);
        } else {
            font.setTypeface(fontTypeNormal_);
        }
        auto width = font.measureText(&temp, sizeof(temp), SkTextEncoding::kUTF16);
        if (length < offset + width + space) {
            break;
        }
        offset = offset + width + space;
    }

    auto& pathBounds = path.getBounds();
    bounds.SetWidth(fmax(pathBounds.right(), bounds.Width()));
    bounds.SetHeight(fmax(pathBounds.bottom(), bounds.Height()));
    return offset;
}
#else
double RosenSvgPainter::MeasureTextPathBounds(
    const SvgTextInfo& svgTextInfo, const PathDrawInfo& pathDrawInfo, Rect& bounds)
{
    double offset = pathDrawInfo.offset;

    RSFont font;
    font.SetSize(svgTextInfo.textStyle.GetFontSize().Value());
    font.SetScaleX(1.0);
    double space = 0.0;
    std::wstring data = StringUtils::ToWstring(svgTextInfo.data);

    SkPath path;
    SkParsePath::FromSVGString(pathDrawInfo.path.c_str(), &path);
    SkPathMeasure pathMeasure(path, false);
    SkScalar length = pathMeasure.getLength();

    for (int i = 0; i < (int)data.size(); i++) {
        wchar_t temp = data[i];
        if (temp >= 0x4e00 && temp <= 0x9fa5) {
            font.SetTypeface(fontTypeChinese_);
        } else {
            font.SetTypeface(fontTypeNormal_);
        }
        auto width = font.MeasureText(&temp, sizeof(temp), RSTextEncoding::UTF16);
        if (length < offset + width + space) {
            break;
        }
        offset = offset + width + space;
    }

    auto& pathBounds = path.getBounds();
    bounds.SetWidth(fmax(pathBounds.right(), bounds.Width()));
    bounds.SetHeight(fmax(pathBounds.bottom(), bounds.Height()));
    return offset;
}
#endif

static const char* SkipSpace(const char str[])
{
    if (!str) {
        return nullptr;
    }
    while (isspace(*str)) {
        str++;
    }
    return str;
}

static const char* SkipSep(const char str[])
{
    if (!str) {
        return nullptr;
    }
    while (isspace(*str) || *str == ',') {
        str++;
    }
    return str;
}

static const char* FindDoubleValue(const char str[], double& value)
{
    str = SkipSpace(str);
    if (!str) {
        return nullptr;
    }
    char* stop = nullptr;
    float v = std::strtod(str, &stop);
    if (str == stop || errno == ERANGE) {
        return nullptr;
    }
    value = v;
    return stop;
}

#ifndef USE_ROSEN_DRAWING
void RosenSvgPainter::StringToPoints(const char str[], std::vector<SkPoint>& points)
#else
void RosenSvgPainter::StringToPoints(const char str[], std::vector<RSPoint>& points)
#endif
{
    for (;;) {
        double x = 0.0;
        str = FindDoubleValue(str, x);
        if (str == nullptr) {
            break;
        }
        str = SkipSep(str);
        double y = 0.0;
        str = FindDoubleValue(str, y);
        if (str == nullptr) {
            break;
        }
#ifndef USE_ROSEN_DRAWING
        points.emplace_back(SkPoint::Make(x, y));
#else
        points.emplace_back(RSPoint(x, y));
#endif
    }
}

void RosenSvgPainter::UpdateMotionMatrix(
    const std::shared_ptr<RSNode>& rsNode, const std::string& path, const std::string& rotate, double percent)
{
    if (path.empty() || rsNode == nullptr) {
        return;
    }
#ifndef USE_ROSEN_DRAWING
    SkPath motion;
    SkParsePath::FromSVGString(path.c_str(), &motion);
    SkPathMeasure pathMeasure(motion, false);
    SkPoint position;
    SkVector tangent;
    bool ret = pathMeasure.getPosTan(pathMeasure.getLength() * percent, &position, &tangent);
    if (!ret) {
        return;
    }
    float degrees = 0.0f;
    if (rotate == ROTATE_TYPE_AUTO) {
        degrees = SkRadiansToDegrees(std::atan2(tangent.y(), tangent.x()));
    } else if (rotate == ROTATE_TYPE_REVERSE) {
        degrees = SkRadiansToDegrees(std::atan2(tangent.y(), tangent.x())) + FLAT_ANGLE;
    } else {
        degrees = StringUtils::StringToDouble(rotate);
    }
    // reset quaternion
    rsNode->SetRotation({ 0., 0., 0., 1. });
    rsNode->SetRotation(degrees, 0., 0.);
    auto frame = rsNode->GetStagingProperties().GetFrame();
    rsNode->SetPivot(position.x() / frame.x_, position.y() / frame.y_);
#else
    RSRecordingPath motion;
    motion.BuildFromSVGString(path.c_str());
    RSPoint position;
    RSPoint tangent;
    bool ret = motion.GetPositionAndTangent(motion.GetLength(false) * percent, position, tangent, false);
    if (!ret) {
        return;
    }
    float degrees = 0.0f;
    if (rotate == ROTATE_TYPE_AUTO) {
        degrees = Rosen::Drawing::ConvertRadiansToDegrees(std::atan2(tangent.GetY(), tangent.GetX()));
    } else if (rotate == ROTATE_TYPE_REVERSE) {
        degrees = Rosen::Drawing::ConvertRadiansToDegrees(std::atan2(tangent.GetY(), tangent.GetX())) + FLAT_ANGLE;
    } else {
        degrees = StringUtils::StringToDouble(rotate);
    }
    // reset quaternion
    rsNode->SetRotation({ 0., 0., 0., 1. });
    rsNode->SetRotation(degrees, 0., 0.);
    auto frame = rsNode->GetStagingProperties().GetFrame();
    rsNode->SetPivot(position.GetX() / frame.x_, position.GetY() / frame.y_);
#endif
}

#ifndef USE_ROSEN_DRAWING
SkMatrix RosenSvgPainter::ToSkMatrix(const Matrix4& matrix4)
{
    // Mappings from SkMatrix-index to input-index.
    static const int32_t K_SK_MATRIX_INDEX_TO_MATRIX4_INDEX[] = {
        0,
        4,
        12,
        1,
        5,
        13,
        3,
        7,
        15,
    };

    SkMatrix skMatrix;
    for (std::size_t i = 0; i < ArraySize(K_SK_MATRIX_INDEX_TO_MATRIX4_INDEX); ++i) {
        int32_t matrixIndex = K_SK_MATRIX_INDEX_TO_MATRIX4_INDEX[i];
        if (matrixIndex < matrix4.Count())
            skMatrix[i] = matrix4[matrixIndex];
        else
            skMatrix[i] = 0.0;
    }
    return skMatrix;
}
#else
RSMatrix RosenSvgPainter::ToDrawingMatrix(const Matrix4& matrix4)
{
    // Mappings from DrawingMatrix-index to input-index.
    static const int32_t K_DRAWING_MATRIX_INDEX_TO_MATRIX4_INDEX[] = {
        0,
        4,
        12,
        1,
        5,
        13,
        3,
        7,
        15,
    };

    RSMatrix matrix;
    for (std::size_t i = 0; i < ArraySize(K_DRAWING_MATRIX_INDEX_TO_MATRIX4_INDEX); ++i) {
        int32_t matrixIndex = K_DRAWING_MATRIX_INDEX_TO_MATRIX4_INDEX[i];
        if (matrixIndex < matrix4.Count())
            matrix.Set(static_cast<RSMatrix::Index>(i), matrix4[matrixIndex]);
        else
            matrix.Set(static_cast<RSMatrix::Index>(i), 0.0);
    }
    return matrix;
}
#endif

} // namespace OHOS::Ace
