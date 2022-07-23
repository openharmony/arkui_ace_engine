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

#include "core/components_ng/render/adapter/skia_canvas.h"

#include "third_party/skia/include/core/SkCanvas.h"
#include "third_party/skia/include/core/SkMatrix.h"
#include "third_party/skia/include/core/SkRRect.h"
#include "third_party/skia/include/core/SkRect.h"

#include "base/utils/utils.h"
#include "core/components_ng/render/adapter/skia_canvas_image.h"
#include "core/components_ng/render/adapter/skia_paint.h"

namespace OHOS::Ace::NG {

SkMatrix ToSkMatrix(const Matrix3& matrix)
{
    // clang-format off
    return SkMatrix::MakeAll(
        matrix[0][0], matrix[0][1], matrix[0][2],
        matrix[1][0], matrix[1][1], matrix[1][2],
        matrix[2][0], matrix[2][1], matrix[2][2]);
    // clang-format on
}

SkRect ToSkRect(const RectF& rect)
{
    return SkRect::MakeLTRB(rect.GetX(), rect.GetY(), rect.Right(), rect.Bottom());
}

SkRRect ToSkRRect(const RRect& rRect)
{
    auto rect = rRect.GetRect();
    auto corner = rRect.GetCorner();
    SkRect skRect = SkRect::MakeXYWH(rect.Left(), rect.Top(), rect.Width(), rect.Height());
    // TODO: replace with new RRectF
    SkVector fRadii[4] = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
    SkRRect skRRect;
    skRRect.setRectRadii(skRect, fRadii);
    return skRRect;
}

RefPtr<Canvas> Canvas::Create(void* rawCanvas)
{
    return AceType::MakeRefPtr<SkiaCanvas>(reinterpret_cast<SkCanvas*>(rawCanvas));
}

void SkiaCanvas::Save()
{
    CHECK_NULL_VOID(rawCanvas_);
    rawCanvas_->save();
}

void SkiaCanvas::Restore()
{
    CHECK_NULL_VOID(rawCanvas_);
    rawCanvas_->restore();
}

void SkiaCanvas::Translate(float dx, float dy)
{
    CHECK_NULL_VOID(rawCanvas_);
    rawCanvas_->translate(dx, dy);
}

void SkiaCanvas::Scale(float sx, float sy)
{
    CHECK_NULL_VOID(rawCanvas_);
    rawCanvas_->scale(sx, sy);
}

void SkiaCanvas::Rotate(float rad)
{
    CHECK_NULL_VOID(rawCanvas_);
    rawCanvas_->rotate(rad * 180.0 / PI_NUM);
}

void SkiaCanvas::Skew(float sx, float sy)
{
    CHECK_NULL_VOID(rawCanvas_);
    rawCanvas_->skew(sx, sy);
}

void SkiaCanvas::SetMatrix(const Matrix3& matrix)
{
    CHECK_NULL_VOID(rawCanvas_);
    rawCanvas_->setMatrix(ToSkMatrix(matrix));
}

void SkiaCanvas::ConcatMatrix(const Matrix3& matrix)
{
    CHECK_NULL_VOID(rawCanvas_);
    rawCanvas_->concat(ToSkMatrix(matrix));
}

void SkiaCanvas::ClipRect(const RectF& rect, ClipQuality quality)
{
    CHECK_NULL_VOID(rawCanvas_);
    rawCanvas_->clipRect(ToSkRect(rect), quality == ClipQuality::ANTI_ALIAS);
}

void SkiaCanvas::ClipRRect(const RRect& rRect, ClipQuality quality)
{
    CHECK_NULL_VOID(rawCanvas_);
    rawCanvas_->clipRRect(ToSkRRect(rRect), quality == ClipQuality::ANTI_ALIAS);
}

void SkiaCanvas::ClipWithPath(const ClipPath& path, ClipQuality quality)
{
    CHECK_NULL_VOID(rawCanvas_);
    // TODO: convert CilpPath to SkPath
}

void SkiaCanvas::ClearColor(const Color& color)
{
    CHECK_NULL_VOID(rawCanvas_);
    rawCanvas_->clear(color.GetValue());
}

void SkiaCanvas::DrawColor(const Color& color)
{
    CHECK_NULL_VOID(rawCanvas_);
    rawCanvas_->drawColor(color.GetValue());
}

void SkiaCanvas::DrawLine(const PointF& start, const PointF& end, const RefPtr<Paint>& paint)
{
    CHECK_NULL_VOID(rawCanvas_);
    auto skiaPaint = AceType::DynamicCast<SkiaPaint>(paint);
    CHECK_NULL_VOID(skiaPaint);
    rawCanvas_->drawLine(start.GetX(), start.GetY(), end.GetX(), end.GetY(), skiaPaint->GetRawPaint());
}

void SkiaCanvas::DrawRect(const RectF& rect, const RefPtr<Paint>& paint)
{
    CHECK_NULL_VOID(rawCanvas_);
    auto skiaPaint = AceType::DynamicCast<SkiaPaint>(paint);
    CHECK_NULL_VOID(skiaPaint);
    rawCanvas_->drawRect(ToSkRect(rect), skiaPaint->GetRawPaint());
}

void SkiaCanvas::DrawRRect(const RRect& rRect, const RefPtr<Paint>& paint)
{
    CHECK_NULL_VOID(rawCanvas_);
    auto skiaPaint = AceType::DynamicCast<SkiaPaint>(paint);
    CHECK_NULL_VOID(skiaPaint);
    rawCanvas_->drawRRect(ToSkRRect(rRect), skiaPaint->GetRawPaint());
}

void SkiaCanvas::DrawCircle(float centerX, float centerY, float radius, const RefPtr<Paint>& paint)
{
    CHECK_NULL_VOID(rawCanvas_);
    auto skiaPaint = AceType::DynamicCast<SkiaPaint>(paint);
    CHECK_NULL_VOID(skiaPaint);
    rawCanvas_->drawCircle(centerX, centerY, radius, skiaPaint->GetRawPaint());
}

void SkiaCanvas::DrawImage(
    const RefPtr<CanvasImage>& image, const RectF& srcRect, const RectF& dstRect, const RefPtr<Paint>& paint)
{
    CHECK_NULL_VOID(rawCanvas_);
    auto skiaPaint = AceType::DynamicCast<SkiaPaint>(paint);
    CHECK_NULL_VOID(skiaPaint);
    auto skiaImage = AceType::DynamicCast<SkiaCanvasImage>(image);
    CHECK_NULL_VOID(skiaImage);
    auto imageObj = skiaImage->GetCanvasImage();
    CHECK_NULL_VOID(imageObj);
#ifdef NG_BUILD
    rawCanvas_->drawImageRect(imageObj, ToSkRect(srcRect), ToSkRect(dstRect), skiaPaint->GetSamplingOptions(),
        &skiaPaint->GetRawPaint(), SkCanvas::kFast_SrcRectConstraint);
#else
    rawCanvas_->drawImageRect(imageObj, ToSkRect(srcRect), ToSkRect(dstRect), &skiaPaint->GetRawPaint());
#endif
}

} // namespace OHOS::Ace::NG
