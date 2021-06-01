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

#include "core/components/piece/flutter_render_piece.h"

#include "third_party/skia/include/core/SkCanvas.h"

#include "core/components/box/render_box.h"
#include "core/pipeline/base/scoped_canvas_state.h"

namespace OHOS::Ace {

RefPtr<RenderNode> RenderPiece::Create()
{
    return AceType::MakeRefPtr<FlutterRenderPiece>();
}

void FlutterRenderPiece::Paint(RenderContext& context, const Offset& offset)
{
    RenderNode::Paint(context, offset);

    // Paint overlay when hover.
    if (mouseState_ != MouseState::HOVER) {
        return;
    }
    auto parent = GetParent().Upgrade();
    Size pieceSize = GetLayoutSize();
    Offset pieceOffset = GetPosition();
    if (parent && AceType::DynamicCast<RenderBox>(parent)) {
        pieceSize = parent->GetLayoutSize();
        pieceOffset = Offset();
        const auto& context = context_.Upgrade();
        if (context) {
            pieceSize -= margin_.GetLayoutSizeInPx(context->GetDipScale());
            pieceOffset += margin_.GetOffsetInPx(context->GetDipScale());
        }
    }
    auto canvas = ScopedCanvas::Create(context);
    if (!canvas) {
        LOGE("canvas fetch failed");
        return;
    }
    SkCanvas* skCanvas = canvas->canvas();
    if (skCanvas == nullptr) {
        return;
    }
    SkPaint paint;
    skCanvas->save();
    paint.setColor(hoverColor_.GetValue());
    Rect pieceRect(pieceOffset + offset - GetPosition(), pieceSize);
    skCanvas->drawRRect(MakeRRect(pieceRect.GetOffset(), pieceRect.GetSize(), border_), paint);
    skCanvas->restore();
}

SkRRect FlutterRenderPiece::MakeRRect(const Offset& offset, const Size& size, const Border& border) const
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

} // namespace OHOS::Ace