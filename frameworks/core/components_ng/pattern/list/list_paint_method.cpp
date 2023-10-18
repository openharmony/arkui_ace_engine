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

#include "core/components_ng/pattern/list/list_paint_method.h"

#include "core/components_ng/pattern/scroll/inner/scroll_bar_overlay_modifier.h"
#include "core/components_ng/render/divider_painter.h"

namespace OHOS::Ace::NG {
void ListPaintMethod::PaintEdgeEffect(PaintWrapper* paintWrapper, RSCanvas& canvas)
{
    auto edgeEffect = edgeEffect_.Upgrade();
    CHECK_NULL_VOID(edgeEffect);
    CHECK_NULL_VOID(paintWrapper);
    auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    edgeEffect->Paint(canvas, frameSize, { 0.0f, 0.0f });
}

CanvasDrawFunction ListPaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto painter = weak.Upgrade();
        CHECK_NULL_VOID(painter);
        painter->PaintEdgeEffect(paintWrapper, canvas);
    };
    return paintFunc;
}

void ListPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(listContentModifier_);
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    auto frameSize = geometryNode->GetPaddingSize();
    OffsetF paddingOffset = geometryNode->GetPaddingOffset() - geometryNode->GetFrameOffset();
    auto renderContext = paintWrapper->GetRenderContext();
    bool clip = !renderContext || renderContext->GetClipEdge().value_or(true);
    listContentModifier_->SetClipOffset(paddingOffset);
    listContentModifier_->SetClipSize(frameSize);
    listContentModifier_->SetClip(clip);
    float contentSize = vertical_ ? frameSize.Width() : frameSize.Height();
    if (!divider_.strokeWidth.IsValid() || totalItemCount_ <= 0 ||
        divider_.strokeWidth.Unit() == DimensionUnit::PERCENT ||
        GreatOrEqual(divider_.strokeWidth.ConvertToPx(), contentSize)) {
        listContentModifier_->ResetDividerInfo();
        return;
    }
    Axis axis = vertical_ ? Axis::HORIZONTAL : Axis::VERTICAL;
    DividerInfo dividerInfo = {
        .constrainStrokeWidth = divider_.strokeWidth.ConvertToPx(),
        .crossSize = vertical_ ? frameSize.Height() : frameSize.Width(),
        .startMargin = std::max(0.0, divider_.startMargin.ConvertToPx()),
        .endMargin = std::max(0.0, divider_.endMargin.ConvertToPx()),
        .space = space_,
        .mainPadding = paddingOffset.GetMainOffset(axis),
        .crossPadding = paddingOffset.GetCrossOffset(axis),
        .isVertical = vertical_,
        .lanes = lanes_ > 1 ? lanes_ : 1,
        .totalItemCount = totalItemCount_,
        .color = divider_.color,
        .laneGutter = laneGutter_
    };
    float checkMargin = dividerInfo.crossSize / dividerInfo.lanes - dividerInfo.startMargin - dividerInfo.endMargin;
    if (NearZero(checkMargin)) return;
    if (LessNotEqual(checkMargin, 0.0f)) {
        dividerInfo.startMargin = 0.0f;
        dividerInfo.endMargin = 0.0f;
    }
    listContentModifier_->SetDividerInfo(std::move(dividerInfo));
    listContentModifier_->FlushDivider();
}

void ListPaintMethod::UpdateOverlayModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto scrollBarOverlayModifier = scrollBarOverlayModifier_.Upgrade();
    CHECK_NULL_VOID(scrollBarOverlayModifier);
    auto scrollBar = scrollBar_.Upgrade();
    if (!scrollBar || !scrollBar->NeedPaint()) {
        LOGD("no need paint scroll bar.");
        return;
    }
    OffsetF fgOffset(scrollBar->GetActiveRect().Left(), scrollBar->GetActiveRect().Top());
    scrollBarOverlayModifier->StartBarAnimation(scrollBar->GetHoverAnimationType(),
        scrollBar->GetOpacityAnimationType(), scrollBar->GetNeedAdaptAnimation(), scrollBar->GetActiveRect());
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    scrollBarOverlayModifier->SetBarColor(scrollBar->GetForegroundColor());
    scrollBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
}
} // namespace OHOS::Ace::NG
