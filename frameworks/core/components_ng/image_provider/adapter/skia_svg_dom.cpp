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

#include "core/components_ng/image_provider/adapter/skia_svg_dom.h"

#include "skia_adapter/skia_canvas.h"

namespace OHOS::Ace::NG {

union SkColorEx {
    struct {
        SkColor color : 32;
        bool valid : 1;
        uint32_t reserved : 31; // reserved
    };
    uint64_t value = 0;
};

RefPtr<SkiaSvgDom> SkiaSvgDom::CreateSkiaSvgDom(SkStream& svgStream, const std::optional<Color>& svgFillColor)
{
    SkColorEx skColor;
    if (svgFillColor.has_value()) {
        skColor.color = svgFillColor.value().GetValue();
        skColor.valid = 1;
    }
    auto skiaDom = SkSVGDOM::MakeFromStream(svgStream, skColor.value);
    CHECK_NULL_RETURN(skiaDom, nullptr);
    return AceType::MakeRefPtr<SkiaSvgDom>(skiaDom);
}

void SkiaSvgDom::FitImage(SkCanvas* canvas, const ImageFit& imageFit, const Size& layout)
{
    double scaleX = 1.0;
    double scaleY = 1.0;
    float tx = 0.0;
    float ty = 0.0;
    constexpr float HALF = 0.5;
    const size_t RADII_SIZE = 4; // 4 corners for round rectangle

    if (!layout.IsEmpty()) {
        layout_ = layout;
    }
    if (!layout_.IsEmpty() && (svgSize_.IsValid() && !svgSize_.IsInfinite())) {
        ApplyImageFit(imageFit, scaleX, scaleY);
    }

    auto rect = SkRect::MakeWH(layout_.Width(), layout_.Height());
    if (radius_) {
        SkRRect rrect;
        SkVector radii[RADII_SIZE];
        for (size_t i = 0; i < RADII_SIZE; ++i) {
            radii[i] = SkPoint::Make((*radius_)[i].GetX(), (*radius_)[i].GetY());
        }
        rrect.setRectRadii(rect, radii);
        canvas->clipRRect(rrect, SkClipOp::kIntersect, true);
    } else {
        canvas->clipRect(rect, SkClipOp::kIntersect, true);
    }

    // Move the svg viewport to center of the container.
    if (svgSize_.IsValid() && !svgSize_.IsInfinite() && !layout_.IsEmpty()) {
        tx = (layout_.Width() - svgSize_.Width() * scaleX) * HALF;
        ty = (layout_.Height() - svgSize_.Height() * scaleY) * HALF;
    }

    canvas->translate(tx, ty);

    if (NearZero(scaleX) || NearZero(scaleY)) {
        return;
    }

    canvas->scale(scaleX, scaleY);
}

void SkiaSvgDom::FitViewPort(const Size& layout)
{
    if (!svgSize_.IsValid() || svgSize_.IsInfinite()) {
        svgSize_ = layout;
        skiaDom_->setContainerSize(SkSize::Make(layout.Width(), layout.Height()));
    }
}

void SkiaSvgDom::OffScreenDraw(
    RSCanvas& canvas, const ImageFit& imageFit, const Size& layout)
{
    // Create bitmap and bitmapCanvas
    RSBitmap bitmap;
    auto imageInfo = RSImageInfo::MakeN32Premul(layout.Width(), layout.Height());
    bitmap.Build(imageInfo);
    RSCanvas bitmapCanvas;
    bitmapCanvas.Bind(bitmap);
    bitmapCanvas.Clear(SK_ColorTRANSPARENT);

    // draw svg offScreen
    CHECK_NULL_VOID(skiaDom_);
    auto rsCanvas = bitmapCanvas.GetImpl<Rosen::Drawing::SkiaCanvas>();
    CHECK_NULL_VOID(rsCanvas);
    auto* skCanvas = rsCanvas->ExportSkCanvas();

    skCanvas->save();
    FitViewPort(layout);
    FitImage(skCanvas, imageFit, layout);
    Render(skCanvas);
    skCanvas->restore();

    // transform bitmap to image
    RSImage image;
    image.BuildFromBitmap(bitmap);
    canvas.DrawImage(image, 0, 0, Rosen::Drawing::SamplingOptions());
}

void SkiaSvgDom::DrawImage(
    RSCanvas& canvas, const ImageFit& imageFit, const Size& layout)
{
    OffScreenDraw(canvas, imageFit, layout);
}

const sk_sp<SkSVGDOM>& SkiaSvgDom::GetSkiaSvgDom() const
{
    return skiaDom_;
}

void SkiaSvgDom::Render(SkCanvas* skCanvas)
{
    skiaDom_->render(skCanvas);
}

SizeF SkiaSvgDom::GetContainerSize() const
{
    return SizeF(skiaDom_->containerSize().width(), skiaDom_->containerSize().height());
}

void SkiaSvgDom::SetContainerSize(const SizeF& containerSize)
{
    skiaDom_->setContainerSize({ containerSize.Width(), containerSize.Height() });
}

} // namespace OHOS::Ace::NG
