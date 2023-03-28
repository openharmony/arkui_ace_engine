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

#include "core/components_ng/pattern/scroll/inner/scroll_bar_painter.h"
#include "core/components_ng/render/divider_painter.h"

namespace OHOS::Ace::NG {
void ListPaintMethod::PaintDivider(const DividerInfo& dividerInfo, const PositionMap& itemPosition, RSCanvas& canvas)
{
    float laneLen = dividerInfo.crossSize / dividerInfo.lanes - dividerInfo.startMargin - dividerInfo.endMargin;
    float crossLen = dividerInfo.crossSize - dividerInfo.startMargin - dividerInfo.endMargin;
    DividerPainter dividerPainter(dividerInfo.constrainStrokeWidth, crossLen,
        dividerInfo.isVertical, dividerInfo.color, LineCap::SQUARE);

    int32_t lanes = dividerInfo.lanes;
    int32_t laneIdx = 0;
    bool lastIsItemGroup = false;
    bool isFirstItem = (itemPosition.begin()->first == 0);
    std::list<int32_t> lastLineIndex;

    for (const auto& child : itemPosition) {
        if (!isFirstItem) {
            float divOffset = (dividerInfo.space + dividerInfo.constrainStrokeWidth) / 2; /* 2 half */
            float mainPos = child.second.startPos - divOffset + dividerInfo.mainPadding;
            float crossPos = dividerInfo.startMargin + dividerInfo.crossPadding;
            if (lanes > 1 && !lastIsItemGroup && !child.second.isGroup) {
                crossPos += laneIdx * dividerInfo.crossSize / dividerInfo.lanes;
                dividerPainter.SetDividerLength(laneLen);
            } else {
                dividerPainter.SetDividerLength(crossLen);
            }
            OffsetF offset = dividerInfo.isVertical ? OffsetF(mainPos, crossPos) : OffsetF(crossPos, mainPos);
            dividerPainter.DrawLine(canvas, offset);
        }
        if (laneIdx == 0 || child.second.isGroup) {
            lastLineIndex.clear();
        }
        lastLineIndex.emplace_back(child.first);
        lastIsItemGroup = child.second.isGroup;
        laneIdx = (lanes <= 1 || (laneIdx + 1) >= lanes || child.second.isGroup) ? 0 : laneIdx + 1;
        isFirstItem = isFirstItem ? laneIdx > 0 : false;
    }
    if (!lastLineIndex.empty() && *lastLineIndex.rbegin() < dividerInfo.totalItemCount - 1) {
        int32_t laneIdx = 0;
        for (auto index : lastLineIndex) {
            float divOffset = (dividerInfo.space - dividerInfo.constrainStrokeWidth) / 2; /* 2 half */
            float mainPos = itemPosition.at(index).endPos + divOffset + dividerInfo.mainPadding;
            float crossPos = dividerInfo.startMargin + dividerInfo.crossPadding;
            if (lanes > 1 && !itemPosition.at(index).isGroup) {
                crossPos += laneIdx * dividerInfo.crossSize / dividerInfo.lanes;
                dividerPainter.SetDividerLength(laneLen);
            } else {
                dividerPainter.SetDividerLength(crossLen);
            }
            OffsetF offset = dividerInfo.isVertical ? OffsetF(mainPos, crossPos) : OffsetF(crossPos, mainPos);
            dividerPainter.DrawLine(canvas, offset);
            laneIdx++;
        }
    }
}

void ListPaintMethod::PaintDivider(PaintWrapper* paintWrapper, RSCanvas& canvas)
{
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    auto frameSize = geometryNode->GetPaddingSize();
    OffsetF paddingOffset = geometryNode->GetPaddingOffset() - geometryNode->GetFrameOffset();
    auto renderContext = paintWrapper->GetRenderContext();
    if (!renderContext || renderContext->GetClipEdge().value_or(true)) {
        auto clipRect = RSRect(paddingOffset.GetX(), paddingOffset.GetY(), frameSize.Width() + paddingOffset.GetX(),
                    paddingOffset.GetY() + frameSize.Height());
        canvas.ClipRect(clipRect, RSClipOp::INTERSECT);
    }

    if (!divider_.strokeWidth.IsValid() || totalItemCount_ <= 0) {
        return;
    }
    Axis axis = vertical_ ? Axis::HORIZONTAL : Axis::VERTICAL;
    DividerInfo dividerInfo = {
        .constrainStrokeWidth = divider_.strokeWidth.ConvertToPx(),
        .crossSize = vertical_ ? frameSize.Height() : frameSize.Width(),
        .startMargin = divider_.startMargin.ConvertToPx(),
        .endMargin = divider_.endMargin.ConvertToPx(),
        .space = space_,
        .mainPadding = paddingOffset.GetMainOffset(axis),
        .crossPadding = paddingOffset.GetCrossOffset(axis),
        .isVertical = vertical_,
        .lanes = lanes_ > 1 ? lanes_ : 1,
        .totalItemCount = totalItemCount_,
        .color = divider_.color
    };
    PaintDivider(dividerInfo, itemPosition_, canvas);
}

void ListPaintMethod::PaintScrollBar(RSCanvas& canvas)
{
    auto scrollBar = scrollBar_.Upgrade();
    CHECK_NULL_VOID_NOLOG(scrollBar);
    if (scrollBar->NeedPaint()) {
        ScrollBarPainter::PaintRectBar(canvas, scrollBar);
    }
}

void ListPaintMethod::PaintEdgeEffect(PaintWrapper* paintWrapper, RSCanvas& canvas)
{
    auto edgeEffect = edgeEffect_.Upgrade();
    CHECK_NULL_VOID_NOLOG(edgeEffect);
    CHECK_NULL_VOID(paintWrapper);
    auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    edgeEffect->Paint(canvas, frameSize, { 0.0f, 0.0f });
}

CanvasDrawFunction ListPaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto painter = weak.Upgrade();
        CHECK_NULL_VOID(painter);
        painter->PaintScrollBar(canvas);
        painter->PaintEdgeEffect(paintWrapper, canvas);
    };
    return paintFunc;
}

CanvasDrawFunction ListPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto painter = weak.Upgrade();
        CHECK_NULL_VOID(painter);
        painter->PaintDivider(paintWrapper, canvas);
    };
    return paintFunc;
}
} // namespace OHOS::Ace::NG