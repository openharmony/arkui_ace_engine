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

#include "core/components_ng/pattern/custom_paint/custom_paint_paint_method.h"

#include <cmath>

#include "drawing/engine_adapter/skia_adapter/skia_canvas.h"
#include "flutter/lib/ui/text/font_collection.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "third_party/bounds_checking_function/include/securec.h"
#include "third_party/skia/include/core/SkBlendMode.h"
#include "third_party/skia/include/core/SkCanvas.h"
#include "third_party/skia/include/core/SkColor.h"
#include "third_party/skia/include/core/SkImage.h"
#include "third_party/skia/include/core/SkPoint.h"
#include "third_party/skia/include/core/SkSurface.h"
#include "third_party/skia/include/effects/SkDashPathEffect.h"
#include "third_party/skia/include/effects/SkGradientShader.h"
#include "third_party/skia/include/utils/SkParsePath.h"

#include "base/geometry/ng/offset_t.h"
#include "base/json/json_util.h"
#include "base/log/ace_trace.h"
#include "base/utils/linear_map.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/components/calendar/rosen_render_calendar.h"
#include "core/components/common/painter/flutter_decoration_painter.h"
#include "core/components/common/painter/rosen_decoration_painter.h"
#include "core/components_ng/render/drawing.h"
#include "core/image/flutter_image_cache.h"
#include "core/image/image_cache.h"
#include "core/image/image_provider.h"
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double HALF_CIRCLE_ANGLE = 180.0;
constexpr double FULL_CIRCLE_ANGLE = 360.0;

const LinearEnumMapNode<CompositeOperation, SkBlendMode> SK_BLEND_MODE_TABLE[] = {
    { CompositeOperation::SOURCE_OVER, SkBlendMode::kSrcOver },
    { CompositeOperation::SOURCE_ATOP, SkBlendMode::kSrcATop },
    { CompositeOperation::SOURCE_IN, SkBlendMode::kSrcIn },
    { CompositeOperation::SOURCE_OUT, SkBlendMode::kSrcOut },
    { CompositeOperation::DESTINATION_OVER, SkBlendMode::kDstOver },
    { CompositeOperation::DESTINATION_ATOP, SkBlendMode::kDstATop },
    { CompositeOperation::DESTINATION_IN, SkBlendMode::kDstIn },
    { CompositeOperation::DESTINATION_OUT, SkBlendMode::kDstOut },
    { CompositeOperation::LIGHTER, SkBlendMode::kLighten },
    { CompositeOperation::COPY, SkBlendMode::kSrc },
    { CompositeOperation::XOR, SkBlendMode::kXor },
};
constexpr size_t BLEND_MODE_SIZE = ArraySize(SK_BLEND_MODE_TABLE);

template<typename T, typename N>
N ConvertEnumToSkEnum(T key, const LinearEnumMapNode<T, N>* map, size_t length, N defaultValue)
{
    int64_t index = BinarySearchFindIndex(map, length, key);
    return index != -1 ? map[index].value : defaultValue;
}
} // namespace

bool CustomPaintPaintMethod::HasShadow() const
{
    return !(NearZero(shadow_.GetOffset().GetX()) && NearZero(shadow_.GetOffset().GetY()) &&
             NearZero(shadow_.GetBlurRadius()));
}

void CustomPaintPaintMethod::UpdateLineDash(SkPaint& paint)
{
    if (!strokeState_.GetLineDash().lineDash.empty()) {
        auto lineDashState = strokeState_.GetLineDash().lineDash;
        SkScalar intervals[lineDashState.size()];
        for (size_t i = 0; i < lineDashState.size(); ++i) {
            intervals[i] = SkDoubleToScalar(lineDashState[i]);
        }
        SkScalar phase = SkDoubleToScalar(strokeState_.GetLineDash().dashOffset);
        paint.setPathEffect(SkDashPathEffect::Make(intervals, lineDashState.size(), phase));
    }
}

void CustomPaintPaintMethod::UpdatePaintShader(const OffsetF& offset, SkPaint& paint, const Ace::Gradient& gradient)
{
    SkPoint beginPoint = SkPoint::Make(SkDoubleToScalar(gradient.GetBeginOffset().GetX() + offset.GetX()),
        SkDoubleToScalar(gradient.GetBeginOffset().GetY() + offset.GetY()));
    SkPoint endPoint = SkPoint::Make(SkDoubleToScalar(gradient.GetEndOffset().GetX() + offset.GetX()),
        SkDoubleToScalar(gradient.GetEndOffset().GetY() + offset.GetY()));
    SkPoint pts[2] = { beginPoint, endPoint };
    auto gradientColors = gradient.GetColors();
    uint32_t colorsSize = gradientColors.size();
    SkColor colors[gradientColors.size()];
    float pos[gradientColors.size()];
    for (uint32_t i = 0; i < colorsSize; ++i) {
        const auto& gradientColor = gradientColors[i];
        colors[i] = gradientColor.GetColor().GetValue();
        pos[i] = gradientColor.GetDimension().Value();
    }
#ifdef USE_SYSTEM_SKIA
    auto mode = SkShader::kClamp_TileMode;
#else
    auto mode = SkTileMode::kClamp;
#endif
    sk_sp<SkShader> skShader = nullptr;
    if (gradient.GetType() == Ace::GradientType::LINEAR) {
        skShader = SkGradientShader::MakeLinear(pts, colors, pos, gradientColors.size(), mode);
    } else {
        if (gradient.GetInnerRadius() <= 0.0 && beginPoint == endPoint) {
            skShader = SkGradientShader::MakeRadial(
                endPoint, gradient.GetOuterRadius(), colors, pos, gradientColors.size(), mode);
        } else {
            skShader = SkGradientShader::MakeTwoPointConical(beginPoint, gradient.GetInnerRadius(), endPoint,
                gradient.GetOuterRadius(), colors, pos, gradientColors.size(), mode);
        }
    }
    paint.setShader(skShader);
}

void CustomPaintPaintMethod::UpdatePaintShader(const Ace::Pattern& pattern, SkPaint& paint)
{
    if (!flutter::UIDartState::Current()) {
        return;
    }

    auto width = pattern.GetImageWidth();
    auto height = pattern.GetImageHeight();
    auto image = GreatOrEqual(width, 0) && GreatOrEqual(height, 0)
                     ? ImageProvider::GetSkImage(pattern.GetImgSrc(), context_, Size(width, height))
                     : ImageProvider::GetSkImage(pattern.GetImgSrc(), context_);
    if (!image) {
        LOGE("image is null");
        return;
    }
    static const LinearMapNode<void (*)(sk_sp<SkImage>, SkPaint&)> staticPattern[] = {
        { "no-repeat",
            [](sk_sp<SkImage> image, SkPaint& paint) {
#ifdef USE_SYSTEM_SKIA
                paint.setShader(image->makeShader(SkShader::kDecal_TileMode, SkShader::kDecal_TileMode, nullptr));
#else
                paint.setShader(image->makeShader(SkTileMode::kDecal, SkTileMode::kDecal, nullptr));
#endif
            } },
        { "repeat",
            [](sk_sp<SkImage> image, SkPaint& paint) {
#ifdef USE_SYSTEM_SKIA
                paint.setShader(image->makeShader(SkShader::kRepeat_TileMode, SkShader::kRepeat_TileMode, nullptr));
#else
                paint.setShader(image->makeShader(SkTileMode::kRepeat, SkTileMode::kRepeat, nullptr));
#endif
            } },
        { "repeat-x",
            [](sk_sp<SkImage> image, SkPaint& paint) {
#ifdef USE_SYSTEM_SKIA
                paint.setShader(image->makeShader(SkShader::kRepeat_TileMode, SkShader::kDecal_TileMode, nullptr));
#else
                paint.setShader(image->makeShader(SkTileMode::kRepeat, SkTileMode::kDecal, nullptr));
#endif
            } },
        { "repeat-y",
            [](sk_sp<SkImage> image, SkPaint& paint) {
#ifdef USE_SYSTEM_SKIA
                paint.setShader(image->makeShader(SkShader::kDecal_TileMode, SkShader::kRepeat_TileMode, nullptr));
#else
                paint.setShader(image->makeShader(SkTileMode::kDecal, SkTileMode::kRepeat, nullptr));
#endif
            } },
    };
    auto operatorIter = BinarySearchFindIndex(staticPattern, ArraySize(staticPattern),
        pattern.GetRepetition().c_str());
    if (operatorIter != -1) {
        staticPattern[operatorIter].value(image, paint);
    }
}

void CustomPaintPaintMethod::InitPaintBlend(SkPaint& paint)
{
    paint.setBlendMode(
        ConvertEnumToSkEnum(globalState_.GetType(), SK_BLEND_MODE_TABLE, BLEND_MODE_SIZE, SkBlendMode::kSrcOver));
}

SkPaint CustomPaintPaintMethod::GetStrokePaint()
{
    static const LinearEnumMapNode<LineJoinStyle, SkPaint::Join> skLineJoinTable[] = {
        { LineJoinStyle::MITER, SkPaint::Join::kMiter_Join },
        { LineJoinStyle::ROUND, SkPaint::Join::kRound_Join },
        { LineJoinStyle::BEVEL, SkPaint::Join::kBevel_Join },
    };
    static const LinearEnumMapNode<LineCapStyle, SkPaint::Cap> skLineCapTable[] = {
        { LineCapStyle::BUTT, SkPaint::Cap::kButt_Cap },
        { LineCapStyle::ROUND, SkPaint::Cap::kRound_Cap },
        { LineCapStyle::SQUARE, SkPaint::Cap::kSquare_Cap },
    };
    SkPaint paint;
    paint.setColor(strokeState_.GetColor().GetValue());
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setStrokeJoin(ConvertEnumToSkEnum(
        strokeState_.GetLineJoin(), skLineJoinTable, ArraySize(skLineJoinTable), SkPaint::Join::kMiter_Join));
    paint.setStrokeCap(ConvertEnumToSkEnum(
        strokeState_.GetLineCap(), skLineCapTable, ArraySize(skLineCapTable), SkPaint::Cap::kButt_Cap));
    paint.setStrokeWidth(static_cast<SkScalar>(strokeState_.GetLineWidth()));
    paint.setStrokeMiter(static_cast<SkScalar>(strokeState_.GetMiterLimit()));

    // set line Dash
    UpdateLineDash(paint);

    // set global alpha
    if (globalState_.HasGlobalAlpha()) {
        paint.setAlphaf(globalState_.GetAlpha());
    }
    return paint;
}

void CustomPaintPaintMethod::InitImagePaint()
{
    if (smoothingEnabled_) {
        if (smoothingQuality_ == "low") {
            imagePaint_.setFilterQuality(SkFilterQuality::kLow_SkFilterQuality);
        } else if (smoothingQuality_ == "medium") {
            imagePaint_.setFilterQuality(SkFilterQuality::kMedium_SkFilterQuality);
        } else if (smoothingQuality_ == "high") {
            imagePaint_.setFilterQuality(SkFilterQuality::kHigh_SkFilterQuality);
        } else {
            LOGE("Unsupported Quality type:%{public}s", smoothingQuality_.c_str());
        }
    } else {
        imagePaint_.setFilterQuality(SkFilterQuality::kNone_SkFilterQuality);
    }
    if (isOffscreen_) {
        SetPaintImage();
    }
}

void CustomPaintPaintMethod::InitImageCallbacks()
{
    imageObjSuccessCallback_ = [weak = AceType::WeakClaim(this)](
                                   ImageSourceInfo info, const RefPtr<ImageObject>& imageObj) {
        auto paintMethod = weak.Upgrade();
        if (paintMethod->loadingSource_ == info) {
            paintMethod->ImageObjReady(imageObj);
            return;
        } else {
            LOGE("image sourceInfo_ check error, : %{public}s vs %{public}s",
                paintMethod->loadingSource_.ToString().c_str(), info.ToString().c_str());
        }
    };

    failedCallback_ = [weak = AceType::WeakClaim(this)](ImageSourceInfo info, const std::string& errorMsg = "") {
        auto paintMethod = weak.Upgrade();
        LOGE("tkh failedCallback_");
        paintMethod->ImageObjFailed();
    };

    uploadSuccessCallback_ = [weak = AceType::WeakClaim(this)](
                                 ImageSourceInfo sourceInfo, const fml::RefPtr<flutter::CanvasImage>& image) {};

    onPostBackgroundTask_ = [weak = AceType::WeakClaim(this)](CancelableTask task) {};
}

void CustomPaintPaintMethod::DrawSvgImage(PaintWrapper* paintWrapper, const Ace::CanvasImage& canvasImage)
{
    SkCanvas* skCanvas;
    if (isOffscreen_) {
        skCanvas = globalState_.GetType() == CompositeOperation::SOURCE_OVER ? skCanvas_.get() : cacheCanvas_.get();
    } else {
        skCanvas = skCanvas_.get();
    }
    // Make the ImageSourceInfo
    canvasImage_ = canvasImage;
    loadingSource_ = ImageSourceInfo(canvasImage.src);
    // get the ImageObject
    if (currentSource_ != loadingSource_) {
        ImageProvider::FetchImageObject(loadingSource_, imageObjSuccessCallback_, uploadSuccessCallback_,
            failedCallback_, context_, true, true, true, renderTaskHolder_, onPostBackgroundTask_);
    }

    // draw the svg
    if (skiaDom_) {
        SkRect srcRect;
        SkRect dstRect;
        OffsetF startPoint;
        float scaleX = 1.0f;
        float scaleY = 1.0f;
        switch (canvasImage.flag) {
            case 0:
                srcRect = SkRect::MakeXYWH(0, 0, skiaDom_->containerSize().width(), skiaDom_->containerSize().height());
                dstRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, skiaDom_->containerSize().width(),
                    skiaDom_->containerSize().height());
                break;
            case 1: {
                srcRect = SkRect::MakeXYWH(0, 0, skiaDom_->containerSize().width(), skiaDom_->containerSize().height());
                dstRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
                break;
            }
            case 2: {
                srcRect = SkRect::MakeXYWH(canvasImage.sx, canvasImage.sy, canvasImage.sWidth, canvasImage.sHeight);
                dstRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
                break;
            }
            default:
                break;
        }
        scaleX = dstRect.width() / srcRect.width();
        scaleY = dstRect.height() / srcRect.height();
        OffsetF offset;
        if (isOffscreen_) {
            offset = OffsetF(0.0f, 0.0f);
        } else {
            CHECK_NULL_VOID(paintWrapper);
            offset = paintWrapper->GetContentOffset();
        }
        startPoint = offset + OffsetF(dstRect.left(), dstRect.top()) -
            OffsetF(srcRect.left() * scaleX, srcRect.top() * scaleY);

        skCanvas->save();
        skCanvas->clipRect(dstRect);
        skCanvas->translate(startPoint.GetX(), startPoint.GetY());
        skCanvas->scale(scaleX, scaleY);
        skiaDom_->render(skCanvas);
        skCanvas->restore();
    }
}

void CustomPaintPaintMethod::PutImageData(PaintWrapper* paintWrapper, const Ace::ImageData& imageData)
{
    if (imageData.data.empty()) {
        LOGE("PutImageData failed, image data is empty.");
        return;
    }
    uint32_t* data = new (std::nothrow) uint32_t[imageData.data.size()];
    if (data == nullptr) {
        LOGE("PutImageData failed, new data is null.");
        return;
    }

    for (uint32_t i = 0; i < imageData.data.size(); ++i) {
        data[i] = imageData.data[i].GetValue();
    }
    SkBitmap skBitmap;
    auto imageInfo = SkImageInfo::Make(imageData.dirtyWidth, imageData.dirtyHeight, SkColorType::kBGRA_8888_SkColorType,
        SkAlphaType::kOpaque_SkAlphaType);
    skBitmap.allocPixels(imageInfo);
    skBitmap.setPixels(data);
    skCanvas_->drawBitmap(skBitmap, imageData.x, imageData.y);
    delete[] data;
}

void CustomPaintPaintMethod::FillRect(PaintWrapper* paintWrapper, const Rect& rect)
{
    OffsetF offset;
    if (isOffscreen_) {
        offset = OffsetF(0.0f, 0.0f);
    } else {
        CHECK_NULL_VOID(paintWrapper);
        offset = paintWrapper->GetContentOffset();
    }
    
    SkPaint paint;
    paint.setAntiAlias(antiAlias_);
    paint.setColor(fillState_.GetColor().GetValue());
    paint.setStyle(SkPaint::Style::kFill_Style);
    SkRect skRect = SkRect::MakeLTRB(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(),
        rect.Right() + offset.GetX(), offset.GetY() + rect.Bottom());
    if (HasShadow()) {
        SkPath path;
        path.addRect(skRect);
        if (isOffscreen_) {
            FlutterDecorationPainter::PaintShadow(path, shadow_, skCanvas_.get());
        } else {
#ifdef ENABLE_ROSEN_BACKEND
            RosenDecorationPainter::PaintShadow(path, shadow_, skCanvas_.get());
#endif
        }
    }
    if (fillState_.GetGradient().IsValid()) {
        UpdatePaintShader(offset, paint, fillState_.GetGradient());
    }
    if (fillState_.GetPattern().IsValid()) {
        UpdatePaintShader(fillState_.GetPattern(), paint);
    }
    if (globalState_.HasGlobalAlpha()) {
        paint.setAlphaf(globalState_.GetAlpha()); // update the global alpha after setting the color
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawRect(skRect, paint);
    } else {
        InitPaintBlend(cachePaint_);
        cacheCanvas_->drawRect(skRect, paint);
        skCanvas_->drawBitmap(cacheBitmap_, 0, 0, &cachePaint_);
        cacheBitmap_.eraseColor(0);
    }
}

void CustomPaintPaintMethod::StrokeRect(PaintWrapper* paintWrapper, const Rect& rect)
{
    OffsetF offset;
    if (isOffscreen_) {
        offset = OffsetF(0.0f, 0.0f);
    } else {
        CHECK_NULL_VOID(paintWrapper);
        offset = paintWrapper->GetContentOffset();
    }

    SkPaint paint = GetStrokePaint();
    paint.setAntiAlias(antiAlias_);
    SkRect skRect = SkRect::MakeLTRB(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(),
        rect.Right() + offset.GetX(), offset.GetY() + rect.Bottom());
    if (HasShadow()) {
        SkPath path;
        path.addRect(skRect);
        if (isOffscreen_) {
            FlutterDecorationPainter::PaintShadow(path, shadow_, skCanvas_.get());
        } else {
#ifdef ENABLE_ROSEN_BACKEND
            RosenDecorationPainter::PaintShadow(path, shadow_, skCanvas_.get());
#endif
        }
    }
    if (strokeState_.GetGradient().IsValid()) {
        UpdatePaintShader(offset, paint, strokeState_.GetGradient());
    }
    if (strokeState_.GetPattern().IsValid()) {
        UpdatePaintShader(strokeState_.GetPattern(), paint);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawRect(skRect, paint);
    } else {
        InitPaintBlend(cachePaint_);
        cacheCanvas_->drawRect(skRect, paint);
        skCanvas_->drawBitmap(cacheBitmap_, 0, 0, &cachePaint_);
        cacheBitmap_.eraseColor(0);
    }
}

void CustomPaintPaintMethod::ClearRect(PaintWrapper* paintWrapper, const Rect& rect)
{
    OffsetF offset;
    if (isOffscreen_) {
        offset = OffsetF(0.0f, 0.0f);
    } else {
        CHECK_NULL_VOID(paintWrapper);
        offset = paintWrapper->GetContentOffset();
    }

    SkPaint paint;
    paint.setAntiAlias(antiAlias_);
    paint.setBlendMode(SkBlendMode::kClear);
    auto skRect = SkRect::MakeLTRB(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(),
        rect.Right() + offset.GetX(), rect.Bottom() + offset.GetY());
    skCanvas_->drawRect(skRect, paint);
}

void CustomPaintPaintMethod::SetFillRuleForPath(const CanvasFillRule& rule)
{
    if (rule == CanvasFillRule::NONZERO) {
        skPath_.setFillType(SkPath::FillType::kWinding_FillType);
    } else if (rule == CanvasFillRule::EVENODD) {
        skPath_.setFillType(SkPath::FillType::kEvenOdd_FillType);
    }
}

void CustomPaintPaintMethod::SetFillRuleForPath2D(const CanvasFillRule& rule)
{
    if (rule == CanvasFillRule::NONZERO) {
        skPath2d_.setFillType(SkPath::FillType::kWinding_FillType);
    } else if (rule == CanvasFillRule::EVENODD) {
        skPath2d_.setFillType(SkPath::FillType::kEvenOdd_FillType);
    }
}

void CustomPaintPaintMethod::Fill(PaintWrapper* paintWrapper)
{
    OffsetF offset;
    if (isOffscreen_) {
        offset = OffsetF(0.0f, 0.0f);
    } else {
        CHECK_NULL_VOID(paintWrapper);
        offset = paintWrapper->GetContentOffset();
    }

    SkPaint paint;
    paint.setAntiAlias(antiAlias_);
    paint.setColor(fillState_.GetColor().GetValue());
    paint.setStyle(SkPaint::Style::kFill_Style);
    if (HasShadow()) {
        if (isOffscreen_) {
            FlutterDecorationPainter::PaintShadow(skPath_, shadow_, skCanvas_.get());
        } else {
#ifdef ENABLE_ROSEN_BACKEND
            RosenDecorationPainter::PaintShadow(skPath_, shadow_, skCanvas_.get());
#endif
        }
    }
    if (fillState_.GetGradient().IsValid()) {
        UpdatePaintShader(offset, paint, fillState_.GetGradient());
    }
    if (fillState_.GetPattern().IsValid()) {
        UpdatePaintShader(fillState_.GetPattern(), paint);
    }
    if (globalState_.HasGlobalAlpha()) {
        paint.setAlphaf(globalState_.GetAlpha());
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawPath(skPath_, paint);
    } else {
        InitPaintBlend(cachePaint_);
        cacheCanvas_->drawPath(skPath_, paint);
        skCanvas_->drawBitmap(cacheBitmap_, 0.0f, 0.0f, &cachePaint_);
        cacheBitmap_.eraseColor(0);
    }
}

void CustomPaintPaintMethod::Fill(PaintWrapper* paintWrapper, const RefPtr<CanvasPath2D>& path)
{
    OffsetF offset;
    if (isOffscreen_) {
        offset = OffsetF(0.0f, 0.0f);
    } else {
        CHECK_NULL_VOID(paintWrapper);
        offset = paintWrapper->GetContentOffset();
    }

    if (path == nullptr) {
        LOGE("Fill failed, target path is null.");
        return;
    }
    ParsePath2D(offset, path);
    Path2DFill(offset);
    skPath2d_.reset();
}

void CustomPaintPaintMethod::Path2DFill(const OffsetF& offset)
{
    SkPaint paint;
    paint.setAntiAlias(antiAlias_);
    paint.setColor(fillState_.GetColor().GetValue());
    paint.setStyle(SkPaint::Style::kFill_Style);
    if (HasShadow()) {
        if (isOffscreen_) {
            FlutterDecorationPainter::PaintShadow(skPath2d_, shadow_, skCanvas_.get());
        } else {
#ifdef ENABLE_ROSEN_BACKEND
            RosenDecorationPainter::PaintShadow(skPath2d_, shadow_, skCanvas_.get());
#endif
        }
    }
    if (fillState_.GetGradient().IsValid()) {
        UpdatePaintShader(offset, paint, fillState_.GetGradient());
    }
    if (fillState_.GetPattern().IsValid()) {
        UpdatePaintShader(fillState_.GetPattern(), paint);
    }
    if (globalState_.HasGlobalAlpha()) {
        paint.setAlphaf(globalState_.GetAlpha());
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawPath(skPath2d_, paint);
    } else {
        InitPaintBlend(cachePaint_);
        cacheCanvas_->drawPath(skPath2d_, paint);
        skCanvas_->drawBitmap(cacheBitmap_, 0, 0, &cachePaint_);
        cacheBitmap_.eraseColor(0);
    }
}

void CustomPaintPaintMethod::Stroke(PaintWrapper* paintWrapper)
{
    OffsetF offset;
    if (isOffscreen_) {
        offset = OffsetF(0.0f, 0.0f);
    } else {
        CHECK_NULL_VOID(paintWrapper);
        offset = paintWrapper->GetContentOffset();
    }

    SkPaint paint = GetStrokePaint();
    paint.setAntiAlias(antiAlias_);
    if (HasShadow()) {
        if (isOffscreen_) {
            FlutterDecorationPainter::PaintShadow(skPath_, shadow_, skCanvas_.get());
        } else {
#ifdef ENABLE_ROSEN_BACKEND
            RosenDecorationPainter::PaintShadow(skPath_, shadow_, skCanvas_.get());
#endif
        }
    }
    if (strokeState_.GetGradient().IsValid()) {
        UpdatePaintShader(offset, paint, strokeState_.GetGradient());
    }
    if (strokeState_.GetPattern().IsValid()) {
        UpdatePaintShader(strokeState_.GetPattern(), paint);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawPath(skPath_, paint);
    } else {
        InitPaintBlend(cachePaint_);
        cacheCanvas_->drawPath(skPath_, paint);
        skCanvas_->drawBitmap(cacheBitmap_, 0, 0, &cachePaint_);
        cacheBitmap_.eraseColor(0);
    }
}

void CustomPaintPaintMethod::Stroke(PaintWrapper* paintWrapper, const RefPtr<CanvasPath2D>& path)
{
    OffsetF offset;
    if (isOffscreen_) {
        offset = OffsetF(0.0f, 0.0f);
    } else {
        CHECK_NULL_VOID(paintWrapper);
        offset = paintWrapper->GetContentOffset();
    }

    if (path == nullptr) {
        LOGE("Stroke failed, target path is null.");
        return;
    }
    ParsePath2D(offset, path);
    Path2DStroke(offset);
    skPath2d_.reset();
}

void CustomPaintPaintMethod::Path2DStroke(const OffsetF& offset)
{
    SkPaint paint = GetStrokePaint();
    paint.setAntiAlias(antiAlias_);
    if (HasShadow()) {
        if (isOffscreen_) {
            FlutterDecorationPainter::PaintShadow(skPath2d_, shadow_, skCanvas_.get());
        } else {
#ifdef ENABLE_ROSEN_BACKEND
            RosenDecorationPainter::PaintShadow(skPath2d_, shadow_, skCanvas_.get());
#endif
        }
    }
    if (strokeState_.GetGradient().IsValid()) {
        UpdatePaintShader(offset, paint, strokeState_.GetGradient());
    }
    if (strokeState_.GetPattern().IsValid()) {
        UpdatePaintShader(strokeState_.GetPattern(), paint);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawPath(skPath2d_, paint);
    } else {
        InitPaintBlend(cachePaint_);
        cacheCanvas_->drawPath(skPath2d_, paint);
        skCanvas_->drawBitmap(cacheBitmap_, 0, 0, &cachePaint_);
        cacheBitmap_.eraseColor(0);
    }
}

void CustomPaintPaintMethod::Clip()
{
    skCanvas_->clipPath(skPath_);
}

void CustomPaintPaintMethod::Clip(const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(path);
    auto offset = OffsetF(0, 0);
    ParsePath2D(offset, path);
    Path2DClip();
    skPath2d_.reset();
}

void CustomPaintPaintMethod::Path2DClip()
{
    skCanvas_->clipPath(skPath2d_);
}

void CustomPaintPaintMethod::BeginPath()
{
    skPath_.reset();
}

void CustomPaintPaintMethod::ClosePath()
{
    skPath_.close();
}

void CustomPaintPaintMethod::MoveTo(PaintWrapper* paintWrapper, double x, double y)
{
    OffsetF offset;
    if (isOffscreen_) {
        offset = OffsetF(0.0f, 0.0f);
    } else {
        CHECK_NULL_VOID(paintWrapper);
        offset = paintWrapper->GetContentOffset();
    }

    skPath_.moveTo(SkDoubleToScalar(x + offset.GetX()), SkDoubleToScalar(y + offset.GetY()));
}

void CustomPaintPaintMethod::LineTo(PaintWrapper* paintWrapper, double x, double y)
{
    OffsetF offset;
    if (isOffscreen_) {
        offset = OffsetF(0.0f, 0.0f);
    } else {
        CHECK_NULL_VOID(paintWrapper);
        offset = paintWrapper->GetContentOffset();
    }

    skPath_.lineTo(SkDoubleToScalar(x + offset.GetX()), SkDoubleToScalar(y + offset.GetY()));
}

void CustomPaintPaintMethod::Arc(PaintWrapper* paintWrapper, const ArcParam& param)
{
    OffsetF offset;
    if (isOffscreen_) {
        offset = OffsetF(0.0f, 0.0f);
    } else {
        CHECK_NULL_VOID(paintWrapper);
        offset = paintWrapper->GetContentOffset();
    }

    double left = param.x - param.radius + offset.GetX();
    double top = param.y - param.radius + offset.GetY();
    double right = param.x + param.radius + offset.GetX();
    double bottom = param.y + param.radius + offset.GetY();
    double startAngle = param.startAngle * HALF_CIRCLE_ANGLE / M_PI;
    double endAngle = param.endAngle * HALF_CIRCLE_ANGLE / M_PI;
    double sweepAngle = endAngle - startAngle;
    if (param.anticlockwise) {
        sweepAngle =
            endAngle > startAngle ? (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) - FULL_CIRCLE_ANGLE) : sweepAngle;
    } else {
        sweepAngle =
            endAngle > startAngle ? sweepAngle : (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) + FULL_CIRCLE_ANGLE);
    }
    auto rect = SkRect::MakeLTRB(left, top, right, bottom);
    if (NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && !NearEqual(startAngle, endAngle)) {
        // draw circle
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        skPath_.arcTo(rect, SkDoubleToScalar(startAngle), SkDoubleToScalar(half), false);
        skPath_.arcTo(rect, SkDoubleToScalar(half + startAngle), SkDoubleToScalar(half), false);
    } else {
        skPath_.arcTo(rect, SkDoubleToScalar(startAngle), SkDoubleToScalar(sweepAngle), false);
    }
}

void CustomPaintPaintMethod::ArcTo(PaintWrapper* paintWrapper, const ArcToParam& param)
{
    OffsetF offset;
    if (isOffscreen_) {
        offset = OffsetF(0.0f, 0.0f);
    } else {
        CHECK_NULL_VOID(paintWrapper);
        offset = paintWrapper->GetContentOffset();
    }

    double x1 = param.x1 + offset.GetX();
    double y1 = param.y1 + offset.GetY();
    double x2 = param.x2 + offset.GetX();
    double y2 = param.y2 + offset.GetY();
    double radius = param.radius;
    skPath_.arcTo(SkDoubleToScalar(x1), SkDoubleToScalar(y1), SkDoubleToScalar(x2), SkDoubleToScalar(y2),
        SkDoubleToScalar(radius));
}

void CustomPaintPaintMethod::AddRect(PaintWrapper* paintWrapper, const Rect& rect)
{
    OffsetF offset;
    if (isOffscreen_) {
        offset = OffsetF(0.0f, 0.0f);
    } else {
        CHECK_NULL_VOID(paintWrapper);
        offset = paintWrapper->GetContentOffset();
    }

    SkRect skRect = SkRect::MakeLTRB(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(),
        rect.Right() + offset.GetX(), offset.GetY() + rect.Bottom());
    skPath_.addRect(skRect);
}

void CustomPaintPaintMethod::Ellipse(PaintWrapper* paintWrapper, const EllipseParam& param)
{
    OffsetF offset;
    if (isOffscreen_) {
        offset = OffsetF(0.0f, 0.0f);
    } else {
        CHECK_NULL_VOID(paintWrapper);
        offset = paintWrapper->GetContentOffset();
    }
    // Init the start and end angle, then calculated the sweepAngle.
    double startAngle = std::fmod(param.startAngle, M_PI * 2.0);
    double endAngle = std::fmod(param.endAngle, M_PI * 2.0);
    startAngle = (startAngle < 0.0 ? startAngle + M_PI * 2.0 : startAngle) * HALF_CIRCLE_ANGLE / M_PI;
    endAngle = (endAngle < 0.0 ? endAngle + M_PI * 2.0 : endAngle) * HALF_CIRCLE_ANGLE / M_PI;
    if (NearEqual(param.startAngle, param.endAngle)) {
        return; // Just return when startAngle is same as endAngle.
    }
    double rotation = param.rotation * HALF_CIRCLE_ANGLE / M_PI;
    double sweepAngle = endAngle - startAngle;
    if (param.anticlockwise) {
        if (sweepAngle > 0.0) { // Make sure the sweepAngle is negative when anticlockwise.
            sweepAngle -= FULL_CIRCLE_ANGLE;
        }
    } else {
        if (sweepAngle < 0.0) { // Make sure the sweepAngle is positive when clockwise.
            sweepAngle += FULL_CIRCLE_ANGLE;
        }
    }

    // Init the oval Rect(left, top, right, bottom).
    double left = param.x - param.radiusX + offset.GetX();
    double top = param.y - param.radiusY + offset.GetY();
    double right = param.x + param.radiusX + offset.GetX();
    double bottom = param.y + param.radiusY + offset.GetY();
    auto rect = SkRect::MakeLTRB(left, top, right, bottom);
    if (!NearZero(rotation)) {
        SkMatrix matrix;
        matrix.setRotate(-rotation, param.x + offset.GetX(), param.y + offset.GetY());
        skPath_.transform(matrix);
    }
    if (NearZero(sweepAngle) && !NearZero(param.endAngle - param.startAngle)) {
        // The entire ellipse needs to be drawn with two arcTo.
        skPath_.arcTo(rect, startAngle, HALF_CIRCLE_ANGLE, false);
        skPath_.arcTo(rect, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE, false);
    } else {
        skPath_.arcTo(rect, startAngle, sweepAngle, false);
    }
    if (!NearZero(rotation)) {
        SkMatrix matrix;
        matrix.setRotate(rotation, param.x + offset.GetX(), param.y + offset.GetY());
        skPath_.transform(matrix);
    }
}

void CustomPaintPaintMethod::BezierCurveTo(PaintWrapper* paintWrapper, const BezierCurveParam& param)
{
    OffsetF offset;
    if (isOffscreen_) {
        offset = OffsetF(0.0f, 0.0f);
    } else {
        CHECK_NULL_VOID(paintWrapper);
        offset = paintWrapper->GetContentOffset();
    }

    skPath_.cubicTo(SkDoubleToScalar(param.cp1x + offset.GetX()), SkDoubleToScalar(param.cp1y + offset.GetY()),
        SkDoubleToScalar(param.cp2x + offset.GetX()), SkDoubleToScalar(param.cp2y + offset.GetY()),
        SkDoubleToScalar(param.x + offset.GetX()), SkDoubleToScalar(param.y + offset.GetY()));
}

void CustomPaintPaintMethod::QuadraticCurveTo(PaintWrapper* paintWrapper, const QuadraticCurveParam& param)
{
    OffsetF offset;
    if (isOffscreen_) {
        offset = OffsetF(0.0f, 0.0f);
    } else {
        CHECK_NULL_VOID(paintWrapper);
        offset = paintWrapper->GetContentOffset();
    }

    skPath_.quadTo(SkDoubleToScalar(param.cpx + offset.GetX()), SkDoubleToScalar(param.cpy + offset.GetY()),
        SkDoubleToScalar(param.x + offset.GetX()), SkDoubleToScalar(param.y + offset.GetY()));
}

void CustomPaintPaintMethod::ParsePath2D(const OffsetF& offset, const RefPtr<CanvasPath2D>& path)
{
    for (const auto& [cmd, args] : path->GetCaches()) {
        switch (cmd) {
            case PathCmd::CMDS: {
                Path2DAddPath(offset, args);
                break;
            }
            case PathCmd::TRANSFORM: {
                Path2DSetTransform(offset, args);
                break;
            }
            case PathCmd::MOVE_TO: {
                Path2DMoveTo(offset, args);
                break;
            }
            case PathCmd::LINE_TO: {
                Path2DLineTo(offset, args);
                break;
            }
            case PathCmd::ARC: {
                Path2DArc(offset, args);
                break;
            }
            case PathCmd::ARC_TO: {
                Path2DArcTo(offset, args);
                break;
            }
            case PathCmd::QUADRATIC_CURVE_TO: {
                Path2DQuadraticCurveTo(offset, args);
                break;
            }
            case PathCmd::BEZIER_CURVE_TO: {
                Path2DBezierCurveTo(offset, args);
                break;
            }
            case PathCmd::ELLIPSE: {
                Path2DEllipse(offset, args);
                break;
            }
            case PathCmd::RECT: {
                Path2DRect(offset, args);
                break;
            }
            case PathCmd::CLOSE_PATH: {
                Path2DClosePath(offset, args);
                break;
            }
            default: {
                break;
            }
        }
    }
}

void CustomPaintPaintMethod::Path2DAddPath(const OffsetF& offset, const PathArgs& args)
{
    SkPath out;
    SkParsePath::FromSVGString(args.cmds.c_str(), &out);
    skPath2d_.addPath(out);
}

void CustomPaintPaintMethod::Path2DClosePath(const OffsetF& offset, const PathArgs& args)
{
    skPath2d_.close();
}

void CustomPaintPaintMethod::Path2DMoveTo(const OffsetF& offset, const PathArgs& args)
{
    double x = args.para1 + offset.GetX();
    double y = args.para2 + offset.GetY();
    skPath2d_.moveTo(x, y);
}

void CustomPaintPaintMethod::Path2DLineTo(const OffsetF& offset, const PathArgs& args)
{
    double x = args.para1 + offset.GetX();
    double y = args.para2 + offset.GetY();
    skPath2d_.lineTo(x, y);
}

void CustomPaintPaintMethod::Path2DArc(const OffsetF& offset, const PathArgs& args)
{
    double x = args.para1;
    double y = args.para2;
    double r = args.para3;
    auto rect =
        SkRect::MakeLTRB(x - r + offset.GetX(), y - r + offset.GetY(), x + r + offset.GetX(), y + r + offset.GetY());
    double startAngle = args.para4 * HALF_CIRCLE_ANGLE / M_PI;
    double endAngle = args.para5 * HALF_CIRCLE_ANGLE / M_PI;
    double sweepAngle = endAngle - startAngle;
    if (!NearZero(args.para6)) {
        sweepAngle =
            endAngle > startAngle ? (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) - FULL_CIRCLE_ANGLE) : sweepAngle;
    } else {
        sweepAngle =
            endAngle > startAngle ? sweepAngle : (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) + FULL_CIRCLE_ANGLE);
    }
    if (NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && !NearEqual(startAngle, endAngle)) {
        skPath2d_.arcTo(rect, startAngle, HALF_CIRCLE_ANGLE, false);
        skPath2d_.arcTo(rect, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE, false);
    } else {
        skPath2d_.arcTo(rect, startAngle, sweepAngle, false);
    }
}

void CustomPaintPaintMethod::Path2DArcTo(const OffsetF& offset, const PathArgs& args)
{
    double x1 = args.para1 + offset.GetX();
    double y1 = args.para2 + offset.GetY();
    double x2 = args.para3 + offset.GetX();
    double y2 = args.para4 + offset.GetY();
    double r = args.para5;
    skPath2d_.arcTo(x1, y1, x2, y2, r);
}

void CustomPaintPaintMethod::Path2DRect(const OffsetF& offset, const PathArgs& args)
{
    double left = args.para1 + offset.GetX();
    double top = args.para2 + offset.GetY();
    double right = 0.0;
    double bottom = 0.0;
    if (isOffscreen_) {
        right = args.para3;
        bottom = args.para4;
    } else {
        right = args.para3 + args.para1 + offset.GetX();
        bottom = args.para4 + args.para2 + offset.GetY();
    }

    skPath2d_.addRect(SkRect::MakeLTRB(left, top, right, bottom));
}

void CustomPaintPaintMethod::Path2DEllipse(const OffsetF& offset, const PathArgs& args)
{
    if (NearEqual(args.para6, args.para7)) {
        return; // Just return when startAngle is same as endAngle.
    }

    double x = args.para1;
    double y = args.para2;
    double rx = args.para3;
    double ry = args.para4;
    double rotation = args.para5 * HALF_CIRCLE_ANGLE / M_PI;
    double startAngle = std::fmod(args.para6, M_PI * 2.0);
    double endAngle = std::fmod(args.para7, M_PI * 2.0);
    bool anticlockwise = NearZero(args.para8) ? false : true;
    startAngle = (startAngle < 0.0 ? startAngle + M_PI * 2.0 : startAngle) * HALF_CIRCLE_ANGLE / M_PI;
    endAngle = (endAngle < 0.0 ? endAngle + M_PI * 2.0 : endAngle) * HALF_CIRCLE_ANGLE / M_PI;
    double sweepAngle = endAngle - startAngle;
    if (anticlockwise) {
        if (sweepAngle > 0.0) { // Make sure the sweepAngle is negative when anticlockwise.
            sweepAngle -= FULL_CIRCLE_ANGLE;
        }
    } else {
        if (sweepAngle < 0.0) { // Make sure the sweepAngle is positive when clockwise.
            sweepAngle += FULL_CIRCLE_ANGLE;
        }
    }
    auto rect = SkRect::MakeLTRB(
        x - rx + offset.GetX(), y - ry + offset.GetY(), x + rx + offset.GetX(), y + ry + offset.GetY());

    if (!NearZero(rotation)) {
        SkMatrix matrix;
        matrix.setRotate(-rotation, x + offset.GetX(), y + offset.GetY());
        skPath2d_.transform(matrix);
    }
    if (NearZero(sweepAngle) && !NearZero(args.para6 - args.para7)) {
        // The entire ellipse needs to be drawn with two arcTo.
        skPath2d_.arcTo(rect, startAngle, HALF_CIRCLE_ANGLE, false);
        skPath2d_.arcTo(rect, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE, false);
    } else {
        skPath2d_.arcTo(rect, startAngle, sweepAngle, false);
    }
    if (!NearZero(rotation)) {
        SkMatrix matrix;
        matrix.setRotate(rotation, x + offset.GetX(), y + offset.GetY());
        skPath2d_.transform(matrix);
    }
}

void CustomPaintPaintMethod::Path2DBezierCurveTo(const OffsetF& offset, const PathArgs& args)
{
    double cp1x = args.para1 + offset.GetX();
    double cp1y = args.para2 + offset.GetY();
    double cp2x = args.para3 + offset.GetX();
    double cp2y = args.para4 + offset.GetY();
    double x = args.para5 + offset.GetX();
    double y = args.para6 + offset.GetY();
    skPath2d_.cubicTo(cp1x, cp1y, cp2x, cp2y, x, y);
}

void CustomPaintPaintMethod::Path2DQuadraticCurveTo(const OffsetF& offset, const PathArgs& args)
{
    double cpx = args.para1 + offset.GetX();
    double cpy = args.para2 + offset.GetY();
    double x = args.para3 + offset.GetX();
    double y = args.para4 + offset.GetY();
    skPath2d_.quadTo(cpx, cpy, x, y);
}

void CustomPaintPaintMethod::Path2DSetTransform(const OffsetF& offset, const PathArgs& args)
{
    SkMatrix skMatrix;
    double scaleX = args.para1;
    double skewX = args.para2;
    double skewY = args.para3;
    double scaleY = args.para4;
    double translateX = args.para5;
    double translateY = args.para6;
    skMatrix.setAll(scaleX, skewY, translateX, skewX, scaleY, translateY, 0.0f, 0.0f, 1.0f);
    skPath2d_.transform(skMatrix);
}

void CustomPaintPaintMethod::Save()
{
    SaveStates();
    skCanvas_->save();
}

void CustomPaintPaintMethod::Restore()
{
    RestoreStates();
    skCanvas_->restore();
}

void CustomPaintPaintMethod::Scale(double x, double y)
{
    skCanvas_->scale(x, y);
}

void CustomPaintPaintMethod::Rotate(double angle)
{
    skCanvas_->rotate(angle * 180 / M_PI);
}

void CustomPaintPaintMethod::SetTransform(const TransformParam& param)
{
    double viewScale = context_->GetViewScale();
    SkMatrix skMatrix;
    if (isOffscreen_) {
        skMatrix.setAll(param.scaleX * viewScale, param.skewY * viewScale, param.translateX, param.skewX * viewScale,
            param.scaleY * viewScale, param.translateY, 0, 0, 1);
    } else {
        skMatrix.setAll(param.scaleX * viewScale, param.skewY * viewScale, param.translateX * viewScale,
            param.skewX * viewScale, param.scaleY * viewScale, param.translateY * viewScale, 0, 0, 1);
    }
    skCanvas_->setMatrix(skMatrix);
}

void CustomPaintPaintMethod::ResetTransform()
{
    skCanvas_->resetMatrix();
}

void CustomPaintPaintMethod::Transform(const TransformParam& param)
{
    SkMatrix skMatrix;
    skMatrix.setAll(param.scaleX, param.skewY, param.translateX, param.skewX, param.scaleY, param.translateY, 0, 0, 1);
    skCanvas_->concat(skMatrix);
}

void CustomPaintPaintMethod::Translate(double x, double y)
{
    skCanvas_->translate(x, y);
}

} // namespace OHOS::Ace::NG