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

#include "core/components/piece/rosen_render_piece.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkCanvas.h"
#else
#include "core/components_ng/render/drawing.h"
#endif

#include "core/components/box/render_box.h"

namespace OHOS::Ace {

void RosenRenderPiece::Paint(RenderContext& context, const Offset& offset)
{
    RenderNode::Paint(context, offset);
    if (!pieceComponent_) {
        LOGE("!pieceComponent_");
        return;
    }
    auto margin = pieceComponent_->GetMargin();
    auto parent = GetParent().Upgrade();
    Size pieceSize = GetLayoutSize();
    Offset pieceOffset = GetPosition();
    if (parent && AceType::DynamicCast<RenderBox>(parent)) {
        pieceSize = parent->GetLayoutSize();
        pieceOffset = Offset();
        const auto& context = context_.Upgrade();
        if (context) {
            pieceSize -= margin.GetLayoutSizeInPx(context->GetDipScale());
            pieceOffset += margin.GetOffsetInPx(context->GetDipScale());
        }
    }
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    auto rsNode = static_cast<RosenRenderContext*>(&context)->GetRSNode();
    if (!canvas || !rsNode) {
        LOGE("canvas fetch failed");
        return;
    }
    rsNode->SetPaintOrder(true);
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    canvas->save();

    auto contextColor = context_.Upgrade();
    if (contextColor->GetIsDeclarative()) {
        paint.setColor(pieceComponent_->GetBackGroundColor().GetValue());
    } else {
        paint.setColor(pieceComponent_->GetHoverColor().GetValue());
    }
    Rect pieceRect(pieceOffset + offset - GetPosition(), pieceSize);
    canvas->drawRRect(MakeRRect(pieceRect.GetOffset(), pieceRect.GetSize(), pieceComponent_->GetBorder()), paint);
    canvas->restore();
#else
    RSPen pen;
    canvas->Save();

    auto contextColor = context_.Upgrade();
    if (contextColor->GetIsDeclarative()) {
        pen.SetColor(pieceComponent_->GetBackGroundColor().GetValue());
    } else {
        pen.SetColor(pieceComponent_->GetHoverColor().GetValue());
    }
    Rect pieceRect(pieceOffset + offset - GetPosition(), pieceSize);
    canvas->AttachPen(pen);
    canvas->DrawRoundRect(MakeRRect(pieceRect.GetOffset(), pieceRect.GetSize(), pieceComponent_->GetBorder()));
    canvas->DetachPen();
    canvas->Restore();
#endif
}

#ifndef USE_ROSEN_DRAWING
SkRRect RosenRenderPiece::MakeRRect(const Offset& offset, const Size& size, const Border& border) const
{
    SkRect rect = SkRect::MakeXYWH(offset.GetX(), offset.GetY(), size.Width(), size.Height());
    SkRRect rrect = SkRRect::MakeEmpty();
    SkVector rectRadii[4] = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
    rectRadii[SkRRect::kUpperLeft_Corner] =
        SkPoint::Make(NormalizeToPx(border.TopLeftRadius().GetX()), NormalizeToPx(border.TopLeftRadius().GetY()));
    rectRadii[SkRRect::kUpperRight_Corner] =
        SkPoint::Make(NormalizeToPx(border.TopRightRadius().GetX()), NormalizeToPx(border.TopRightRadius().GetY()));
    rectRadii[SkRRect::kLowerRight_Corner] = SkPoint::Make(
        NormalizeToPx(border.BottomRightRadius().GetX()), NormalizeToPx(border.BottomRightRadius().GetY()));
    rectRadii[SkRRect::kLowerLeft_Corner] =
        SkPoint::Make(NormalizeToPx(border.BottomLeftRadius().GetX()), NormalizeToPx(border.BottomLeftRadius().GetY()));
    rrect.setRectRadii(rect, rectRadii);
    return rrect;
}
#else
RSRoundRect RosenRenderPiece::MakeRRect(
    const Offset& offset, const Size& size, const Border& border) const
{
    RSRect rect =
        RSRect(offset.GetX(), offset.GetY(), size.Width() + offset.GetX(), size.Height() + offset.GetY());

    std::vector<RSPoint> rectRadii(4, RSPoint(0.0, 0.0));
    // kUpperLeft_Corner
    rectRadii.at(0) = RSPoint(
        NormalizeToPx(border.TopLeftRadius().GetX()), NormalizeToPx(border.TopLeftRadius().GetY()));
    // kUpperRight_Corner
    rectRadii.at(1) = RSPoint(
        NormalizeToPx(border.TopRightRadius().GetX()), NormalizeToPx(border.TopRightRadius().GetY()));
    // kLowerRight_Corner
    rectRadii.at(2) = RSPoint(
        NormalizeToPx(border.BottomRightRadius().GetX()), NormalizeToPx(border.BottomRightRadius().GetY()));
    // kLowerLeft_Corner
    rectRadii.at(3) = RSPoint(
        NormalizeToPx(border.BottomLeftRadius().GetX()), NormalizeToPx(border.BottomLeftRadius().GetY()));

    RSRoundRect rrect(rect, rectRadii);
    return rrect;
}
#endif

} // namespace OHOS::Ace
