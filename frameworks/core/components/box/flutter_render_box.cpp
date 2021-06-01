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

#include "core/components/box/flutter_render_box.h"

#include <cmath>

#include "flutter/common/task_runners.h"
#include "flutter/lib/ui/ui_dart_state.h"
#include "third_party/skia/include/core/SkMaskFilter.h"
#include "third_party/skia/include/effects/Sk1DPathEffect.h"
#include "third_party/skia/include/effects/SkDashPathEffect.h"
#include "third_party/skia/include/effects/SkGradientShader.h"

#include "core/components/common/painter/flutter_decoration_painter.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/border_edge.h"
#include "core/components/common/properties/color.h"
#include "core/pipeline/base/flutter_render_context.h"
#include "core/pipeline/base/scoped_canvas_state.h"
#include "core/pipeline/layers/picture_layer.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t DOUBLE_WIDTH = 2;

} // namespace

using namespace Flutter;

RefPtr<RenderNode> RenderBox::Create()
{
    return AceType::MakeRefPtr<FlutterRenderBox>();
}

void FlutterRenderBox::Update(const RefPtr<Component>& component)
{
    RenderBox::Update(component);

    // use render image to render background image
    if (backDecoration_) {
        RefPtr<BackgroundImage> backgroundImage = backDecoration_->GetImage();
        UpdateBackgroundImage(backgroundImage);
    }
}

void FlutterRenderBox::UpdateBackgroundImage(const RefPtr<BackgroundImage>& image)
{
    if (!image) {
        renderImage_ = nullptr;
        return;
    }

    if (!renderImage_) {
        renderImage_ = AceType::DynamicCast<RenderImage>(RenderImage::Create());
        if (!renderImage_) {
            return;
        }
        renderImage_->SetBackgroundImageFlag(true);
        renderImage_->Attach(GetContext());
        renderImage_->RegisterImageUpdateFunc([weakRenderBox = AceType::WeakClaim(this)]() {
            auto box = weakRenderBox.Upgrade();
            if (box) {
                box->MarkNeedLayout();
            }
        });
    }

    renderImage_->SetImageSrc(image->GetSrc());
    renderImage_->SetImageRepeat(image->GetImageRepeat());
    // set image size, x direction
    renderImage_->SetBgImageSize(image->GetImageSize().GetSizeTypeX(), image->GetImageSize().GetSizeValueX(), true);
    // set image size, y direction
    renderImage_->SetBgImageSize(image->GetImageSize().GetSizeTypeY(), image->GetImageSize().GetSizeValueY(), false);
    renderImage_->SetBgImagePosition(image->GetImagePosition());
}

void FlutterRenderBox::PerformLayout()
{
    RenderBox::PerformLayout();

    // calculate repeatParam.
    CalculateRepeatParam();
}

void FlutterRenderBox::Paint(RenderContext& context, const Offset& offset)
{
    if (opacity_ == 0) {
        RenderNode::Paint(context, offset);
        return;
    }
    auto pipeline = context_.Upgrade();
    if (!pipeline) {
        return;
    }
    Rect paintSize = GetPaintRect() + offset;
    if (useLiteStyle_) {
        paintSize.SetSize(paintSize_);
    }
    flutter::RRect outerRRect;
    outerRRect.sk_rrect =
        SkRRect::MakeRect(SkRect::MakeLTRB(paintSize.Left(), paintSize.Top(), paintSize.Right(), paintSize.Bottom()));
    UpdateBlurRRect(outerRRect, offset);

    RefPtr<FlutterDecorationPainter> decorationPainter;
    if (backDecoration_ || frontDecoration_) {
        if (!useLiteStyle_) {
            decorationPainter = AceType::MakeRefPtr<FlutterDecorationPainter>(
                backDecoration_, GetPaintRect(), paintSize_, pipeline->GetDipScale());
        } else {
            decorationPainter = AceType::MakeRefPtr<FlutterDecorationPainter>(
                backDecoration_, paintSize, paintSize_, pipeline->GetDipScale());
        }
        decorationPainter->SetAlpha(opacity_);
        decorationPainter->SetMargin(margin_);
        decorationPainter->SetRenderImage(renderImage_);
    }
    const auto renderContext = static_cast<FlutterRenderContext*>(&context);
    if (backDecoration_) {
        flutter::Canvas* canvas = renderContext->GetCanvas();
        if (canvas == nullptr) {
            LOGE("Paint canvas is null.");
            return;
        }
        outerRRect = decorationPainter->GetBoxOuterRRect(offset);
        UpdateBlurRRect(outerRRect, offset);

        if (GreatNotEqual(backDecoration_->GetWindowBlurProgress(), 0.0)) {
            SetWindowBlurProgress(backDecoration_->GetWindowBlurProgress());
            SetWindowBlurStyle(backDecoration_->GetWindowBlurStyle());
            MarkNeedWindowBlur(true);
        }
        decorationPainter->PaintBlur(outerRRect, canvas->canvas(), backDecoration_->GetBlurRadius());
        decorationPainter->PaintDecoration(offset, canvas->canvas(), context);
    }

    RenderNode::Paint(context, offset);
    if (frontDecoration_) {
        flutter::Canvas* canvas = renderContext->GetCanvas();
        if (canvas == nullptr) {
            LOGE("Paint canvas is null.");
            return;
        }

        decorationPainter->SetDecoration(frontDecoration_);
        decorationPainter->PaintDecoration(offset, canvas->canvas(), context);
        decorationPainter->PaintBlur(outerRRect, canvas->canvas(), frontDecoration_->GetBlurRadius());
    }
}

void FlutterRenderBox::CalculateRepeatParam()
{
    if (backDecoration_) {
        RefPtr<BackgroundImage> backgroundImage = backDecoration_->GetImage();
        if (backgroundImage && renderImage_) {
            renderImage_->SetBgImageBoxPaintSize(paintSize_);
            renderImage_->SetBgImageBoxMarginOffset(margin_.GetOffset());
            LayoutParam param;
            param.SetFixedSize(paintSize_);
            renderImage_->Layout(param);
        }
    }
}

void FlutterRenderBox::DrawLayerForBlur(SkCanvas* canvas, Flutter::ContainerLayer* containerLayer)
{
    if (!canvas || !containerLayer) {
        return;
    }
    for (const auto& layer : containerLayer->GetChildren()) {
        if (!layer) {
            continue;
        }
        auto pictureLayer = AceType::DynamicCast<Flutter::PictureLayer>(layer);
        if (pictureLayer) {
            auto picture = pictureLayer->GetPicture();
            auto offset = pictureLayer->GetOffset();
            if (offset.GetX() >= 0.0 && picture && picture->picture() && picture->picture().get()) {
                canvas->save();
                canvas->translate(offset.GetX(), offset.GetY());
                canvas->drawPicture(picture->picture().get());
                canvas->restore();
                pictureLayer->SetNeedAddToScene(false);
            }
            continue;
        }
        auto container = AceType::DynamicCast<Flutter::ContainerLayer>(layer);
        if (container) {
            DrawLayerForBlur(canvas, AceType::RawPtr(container));
        }
    }
}

SkVector FlutterRenderBox::GetSkRadii(const Radius& radius, double shrinkFactor, double borderWidth)
{
    SkVector fRadii;
    fRadii.set(SkDoubleToScalar(std::max(NormalizeToPx(radius.GetX()) - shrinkFactor * borderWidth, 0.0)),
        SkDoubleToScalar(std::max(NormalizeToPx(radius.GetY()) - shrinkFactor * borderWidth, 0.0)));
    return fRadii;
}

bool FlutterRenderBox::CheckBorderEdgeForRRect(const Border& border)
{
    double leftWidth = NormalizeToPx(border.Left().GetWidth());
    if (NearEqual(leftWidth, NormalizeToPx(border.Top().GetWidth())) &&
        NearEqual(leftWidth, NormalizeToPx(border.Right().GetWidth())) &&
        NearEqual(leftWidth, NormalizeToPx(border.Bottom().GetWidth()))) {
        BorderStyle leftStyle = border.Left().GetBorderStyle();
        return leftStyle == border.Top().GetBorderStyle() && leftStyle == border.Right().GetBorderStyle() &&
               leftStyle == border.Bottom().GetBorderStyle();
    }
    return false;
}

RenderLayer FlutterRenderBox::GetRenderLayer()
{
    if (overflow_ != Overflow::CLIP) {
        LOGD("do not need to create clipLayer.");
        return nullptr;
    }
    Border border;
    if (backDecoration_) {
        border = backDecoration_->GetBorder();
    }
    if (!clipLayer_) {
        clipLayer_ = AceType::MakeRefPtr<ClipLayer>(
            0.0, GetLayoutSize().Width(), 0.0, GetLayoutSize().Height(), Clip::HARD_EDGE);
    }
    flutter::RRect outerRRect = GetBoxRRect(margin_.GetOffset(), border, 0.0, true);
    clipLayer_->SetClipRRect(outerRRect);
    return AceType::RawPtr(clipLayer_);
}

flutter::RRect FlutterRenderBox::GetBoxRRect(
    const Offset& offset, const Border& border, double shrinkFactor, bool isRound)
{
    flutter::RRect rRect = flutter::RRect();
    SkRect skRect {};
    SkVector fRadii[4] = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
    if (CheckBorderEdgeForRRect(border)) {
        BorderEdge borderEdge = border.Left();
        double borderWidth = NormalizeToPx(borderEdge.GetWidth());
        skRect.setXYWH(SkDoubleToScalar(offset.GetX() + shrinkFactor * borderWidth),
            SkDoubleToScalar(offset.GetY() + shrinkFactor * borderWidth),
            SkDoubleToScalar(paintSize_.Width() - shrinkFactor * DOUBLE_WIDTH * borderWidth),
            SkDoubleToScalar(paintSize_.Height() - shrinkFactor * DOUBLE_WIDTH * borderWidth));
        if (isRound) {
            fRadii[SkRRect::kUpperLeft_Corner] = GetSkRadii(border.TopLeftRadius(), shrinkFactor, borderWidth);
            fRadii[SkRRect::kUpperRight_Corner] = GetSkRadii(border.TopRightRadius(), shrinkFactor, borderWidth);
            fRadii[SkRRect::kLowerRight_Corner] = GetSkRadii(border.BottomRightRadius(), shrinkFactor, borderWidth);
            fRadii[SkRRect::kLowerLeft_Corner] = GetSkRadii(border.BottomLeftRadius(), shrinkFactor, borderWidth);
        }
    } else {
        float offsetX = SkDoubleToScalar(offset.GetX() + shrinkFactor * NormalizeToPx(border.Left().GetWidth()));
        float offsetY = SkDoubleToScalar(offset.GetY() + shrinkFactor * NormalizeToPx(border.Top().GetWidth()));
        float width = SkDoubleToScalar(
            paintSize_.Width() - shrinkFactor * DOUBLE_WIDTH * NormalizeToPx(border.Right().GetWidth()));
        float height = SkDoubleToScalar(
            paintSize_.Height() - shrinkFactor * DOUBLE_WIDTH * NormalizeToPx(border.Bottom().GetWidth()));
        skRect.setXYWH(offsetX, offsetY, width, height);
    }
    rRect.sk_rrect.setRectRadii(skRect, fRadii);
    return rRect;
}

bool FlutterRenderBox::MaybeRelease()
{
    auto context = GetContext().Upgrade();
    if (context && context->GetRenderFactory()->GetRenderBoxFactory()->Recycle(this)) {
        ClearRenderObject();
        return false;
    }
    return true;
}

void FlutterRenderBox::UpdateBlurRRect(const flutter::RRect& rRect, const Offset& offset)
{
    //  radius of four edge should be same
    SkVector radius = rRect.sk_rrect.radii(SkRRect::kUpperLeft_Corner);
    const SkRect& rect = rRect.sk_rrect.rect();
    windowBlurRRect_.SetRectWithSimpleRadius(
        Rect(rect.left(), rect.top(), rect.width(), rect.height()), radius.fX, radius.fY);
    // this is relative offset
    Rect innerRect = windowBlurRRect_.GetRect();
    innerRect -= offset;
    windowBlurRRect_.SetRect(innerRect);
}

} // namespace OHOS::Ace
