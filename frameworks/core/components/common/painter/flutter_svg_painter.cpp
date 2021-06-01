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

#include "core/components/common/painter/flutter_svg_painter.h"

#include "include/core/SkColor.h"
#include "include/core/SkPathMeasure.h"
#include "include/core/SkRSXform.h"
#include "include/core/SkTextBlob.h"
#include "include/effects/SkDashPathEffect.h"
#include "include/utils/SkParsePath.h"

#include "frameworks/core/components/transform/flutter_render_transform.h"

namespace OHOS::Ace {

namespace {

constexpr int32_t COL_INDEX = 2;
constexpr int32_t ROW_INDEX = 3;
constexpr float ROTATE_VALUE = 0.0005f;
constexpr float FLAT_ANGLE = 180.0f;
const char ROTATE_TYPE_AUTO[] = "auto";
const char ROTATE_TYPE_REVERSE[] = "auto-reverse";
const char FONT_TYPE_HWCHINESE[] = "/system/fonts/HwChinese-Medium.ttf";
const char FONT_TYPE_DROIDSANS[] = "/system/fonts/DroidSans.ttf";

} // namespace

sk_sp<SkTypeface> FlutterSvgPainter::fontTypeChinese_ = SkTypeface::MakeFromFile(FONT_TYPE_HWCHINESE);
sk_sp<SkTypeface> FlutterSvgPainter::fontTypeNormal_ = SkTypeface::MakeFromFile(FONT_TYPE_DROIDSANS);

void FlutterSvgPainter::SetFillStyle(SkPaint& skPaint, const FillState& fillState, uint8_t opacity)
{
    skPaint.setStyle(SkPaint::Style::kFill_Style);
    skPaint.setColor(fillState.GetColor().GetValue());
    skPaint.setAlphaf(fillState.GetOpacity() * opacity * (1.0f / UINT8_MAX));
    skPaint.setAntiAlias(true);
}

void FlutterSvgPainter::SetFillStyle(
    SkCanvas* skCanvas, const SkPath& skPath, const FillState& fillState, uint8_t opacity)
{
    SkPaint paint;
    SetFillStyle(paint, fillState, opacity);
    skCanvas->drawPath(skPath, paint);
}

void FlutterSvgPainter::SetStrokeStyle(SkPaint& skPaint, const StrokeState& strokeState, uint8_t opacity)
{
    skPaint.setStyle(SkPaint::Style::kStroke_Style);
    skPaint.setColor(strokeState.GetColor().GetValue());
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
    skPaint.setAlphaf(strokeState.GetOpacity() * opacity * (1.0f / UINT8_MAX));
    skPaint.setAntiAlias(true);
    UpdateLineDash(skPaint, strokeState);
}

void FlutterSvgPainter::SetStrokeStyle(
    SkCanvas* skCanvas, const SkPath& skPath, const StrokeState& strokeState, uint8_t opacity)
{
    SkPaint paint;
    SetStrokeStyle(paint, strokeState, opacity);
    skCanvas->drawPath(skPath, paint);
}

void FlutterSvgPainter::UpdateLineDash(SkPaint& paint, const StrokeState& strokeState)
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

void FlutterSvgPainter::CheckFontType()
{
    if (!fontTypeChinese_) {
        LOGW("can't load HwChinese-Medium.ttf");
    }
    if (!fontTypeNormal_) {
        LOGW("can't load DroidSans.ttf");
    }
}

double FlutterSvgPainter::GetPathLength(const std::string& path)
{
    SkPath skPath;
    SkParsePath::FromSVGString(path.c_str(), &skPath);
    SkPathMeasure pathMeasure(skPath, false);
    SkScalar length = pathMeasure.getLength();
    return length;
}

Offset FlutterSvgPainter::GetPathOffset(const std::string& path, double current)
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

Offset FlutterSvgPainter::UpdateText(SkCanvas* canvas, const SvgTextInfo& svgTextInfo, const TextDrawInfo& textDrawInfo)
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
    FlutterSvgPainter::SetFillStyle(paint, svgTextInfo.fillState, svgTextInfo.opacity);
    FlutterSvgPainter::SetStrokeStyle(strokePaint, svgTextInfo.strokeState, svgTextInfo.opacity);

    for (int i = 0; i < (int)data.size(); i++) {
        wchar_t temp = data[i];
        if (temp >= 0x4e00 && temp <= 0x9fa5) {
            // range of chinese
            font.setTypeface(fontTypeChinese_);
        } else {
            font.setTypeface(fontTypeNormal_);
        }
        auto blob = SkTextBlob::MakeFromText(&temp, sizeof(temp), font, SkTextEncoding::kUTF16);
        auto width = font.measureText(&temp, sizeof(temp), SkTextEncoding::kUTF16);
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

double FlutterSvgPainter::UpdateTextPath(
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
    FlutterSvgPainter::SetFillStyle(paint, svgTextInfo.fillState, svgTextInfo.opacity);
    FlutterSvgPainter::SetStrokeStyle(strokePaint, svgTextInfo.strokeState, svgTextInfo.opacity);

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
        auto width = font.measureText(&temp, sizeof(wchar_t), SkTextEncoding::kUTF16);
        if (length < offset + width + space) {
            LOGD("path length is not enough, length:%{public}lf, next offset:%{public}lf",
                length, offset + width + space);
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

void FlutterSvgPainter::StringToPoints(const char str[], std::vector<SkPoint>& points)
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
        points.emplace_back(SkPoint::Make(x, y));
    }
}

Matrix4 FlutterSvgPainter::CreateMotionMatrix(const std::string& path, const std::string& rotate,
    const Point& startPoint, double percent, bool& isSuccess)
{
    if (path.empty()) {
        isSuccess = false;
        return Matrix4::CreateIdentity();
    }
    SkPath motion;
    SkParsePath::FromSVGString(path.c_str(), &motion);
    SkPathMeasure pathMeasure(motion, false);
    SkPoint position;
    SkVector tangent;
    bool ret = pathMeasure.getPosTan(pathMeasure.getLength() * percent, &position, &tangent);
    if (!ret) {
        isSuccess = false;
        return Matrix4::CreateIdentity();
    }
    float degrees = 0.0f;
    if (rotate == ROTATE_TYPE_AUTO) {
        degrees = SkRadiansToDegrees(std::atan2(tangent.y(), tangent.x()));
    } else if (rotate == ROTATE_TYPE_REVERSE) {
        degrees = SkRadiansToDegrees(std::atan2(tangent.y(), tangent.x())) + FLAT_ANGLE;
    } else {
        degrees = StringUtils::StringToDouble(rotate);
    }
    auto transform = Matrix4::CreateIdentity();
    auto translate = Matrix4::CreateTranslate(position.x() - startPoint.GetX(),
        position.y() - startPoint.GetY(), 0.0);
    transform = translate * transform;
    Matrix4 rotateMatrix;
    rotateMatrix.SetEntry(ROW_INDEX, COL_INDEX, ROTATE_VALUE);
    rotateMatrix.Rotate(degrees, 0.0f, 0.0f, 1.0f);
    transform = rotateMatrix * transform;
    isSuccess = true;
    return FlutterRenderTransform::GetTransformByOffset(transform, Offset(position.x(), position.y()));
}

} // namespace OHOS::Ace