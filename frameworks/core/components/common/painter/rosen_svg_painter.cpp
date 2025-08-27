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

#if !defined(PREVIEW) && !defined(CROSS_PLATFORM)
const char FONT_TYPE_HWCHINESE[] = "/system/fonts/HwChinese-Medium.ttf";
const char FONT_TYPE_DROIDSANS[] = "/system/fonts/DroidSans.ttf";
std::shared_ptr<RSTypeface> RosenSvgPainter::fontTypeChinese_ = RSTypeface::MakeFromFile(FONT_TYPE_HWCHINESE);
std::shared_ptr<RSTypeface> RosenSvgPainter::fontTypeNormal_ = RSTypeface::MakeFromFile(FONT_TYPE_DROIDSANS);
#else
std::shared_ptr<RSTypeface> RosenSvgPainter::fontTypeChinese_;
std::shared_ptr<RSTypeface> RosenSvgPainter::fontTypeNormal_;
#endif

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

void RosenSvgPainter::CheckFontType()
{
    if (!fontTypeChinese_) {
        LOGW("can't load HwChinese-Medium.ttf");
    }
    if (!fontTypeNormal_) {
        LOGW("can't load DroidSans.ttf");
    }
}

double RosenSvgPainter::GetPathLength(const std::string& path)
{
    RSRecordingPath drawPath;
    drawPath.BuildFromSVGString(path.c_str());
    auto length = drawPath.GetLength(false);
    return length;
}

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

bool RosenSvgPainter::GetMotionPathPosition(const std::string& path, double percent, MotionPathPosition& result)
{
    if (path.empty()) {
        return false;
    }
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
    return true;
}

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

void RosenSvgPainter::StringToPoints(const char str[], std::vector<RSPoint>& points)
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
        points.emplace_back(RSPoint(x, y));
    }
}

void RosenSvgPainter::UpdateMotionMatrix(
    const std::shared_ptr<RSNode>& rsNode, const std::string& path, const std::string& rotate, double percent)
{
    if (path.empty() || rsNode == nullptr) {
        return;
    }
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
}

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

} // namespace OHOS::Ace
