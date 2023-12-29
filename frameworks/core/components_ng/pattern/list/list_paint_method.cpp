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
        listContentModifier_->ResetDividerPainterInfo();
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
    UpdateDividerList(dividerInfo);
}

void ListPaintMethod::UpdateDividerList(const DividerInfo& dividerInfo)
{
    float fSpacingTotal = (dividerInfo.lanes - 1) * dividerInfo.laneGutter;
    float laneLen =
        (dividerInfo.crossSize - fSpacingTotal) / dividerInfo.lanes - dividerInfo.startMargin - dividerInfo.endMargin;
    float crossLen = dividerInfo.crossSize - dividerInfo.startMargin - dividerInfo.endMargin;
    listContentModifier_->SetDividerPainter(
        dividerInfo.constrainStrokeWidth, dividerInfo.isVertical, dividerInfo.color);

    int32_t lanes = dividerInfo.lanes;
    int32_t laneIdx = 0;
    bool lastIsItemGroup = false;
    bool isFirstItem = (itemPosition_.begin()->first == 0);
    std::map<int32_t, int32_t> lastLineIndex;
    ListDividerArithmetic::DividerMap dividerMap;
    ListDivider divider;

    for (const auto& child : itemPosition_) {
        if (!isFirstItem) {
            float divOffset = (dividerInfo.space + dividerInfo.constrainStrokeWidth) / 2; /* 2 half */
            float mainPos = child.second.startPos - divOffset + dividerInfo.mainPadding;
            float crossPos = dividerInfo.startMargin + dividerInfo.crossPadding;
            if (lanes > 1 && !lastIsItemGroup && !child.second.isGroup) {
                crossPos +=
                    laneIdx * ((dividerInfo.crossSize - fSpacingTotal) / dividerInfo.lanes + dividerInfo.laneGutter);
                divider.length = laneLen;
            } else {
                divider.length = crossLen;
            }
            OffsetF offset = dividerInfo.isVertical ? OffsetF(mainPos, crossPos) : OffsetF(crossPos, mainPos);
            divider.offset = offset;
            dividerMap[child.second.id] = divider;
        }
        if (laneIdx == 0 || child.second.isGroup) {
            lastLineIndex.clear();
        }
        lastLineIndex[child.first] = child.second.id;
        lastIsItemGroup = child.second.isGroup;
        laneIdx = (lanes <= 1 || (laneIdx + 1) >= lanes || child.second.isGroup) ? 0 : laneIdx + 1;
        isFirstItem = isFirstItem ? laneIdx > 0 : false;
    }
    if (!lastLineIndex.empty() && lastLineIndex.rbegin()->first < dividerInfo.totalItemCount - 1) {
        int32_t laneIdx = 0;
        for (auto index : lastLineIndex) {
            if (index.first + lanes >= dividerInfo.totalItemCount) {
                break;
            }
            float divOffset = (dividerInfo.space - dividerInfo.constrainStrokeWidth) / 2; /* 2 half */
            float mainPos = itemPosition_.at(index.first).endPos + divOffset + dividerInfo.mainPadding;
            float crossPos = dividerInfo.startMargin + dividerInfo.crossPadding;
            if (lanes > 1 && !itemPosition_.at(index.first).isGroup) {
                crossPos +=
                    laneIdx * ((dividerInfo.crossSize - fSpacingTotal) / dividerInfo.lanes + dividerInfo.laneGutter);
                divider.length = laneLen;
            } else {
                divider.length = crossLen;
            }
            OffsetF offset = dividerInfo.isVertical ? OffsetF(mainPos, crossPos) : OffsetF(crossPos, mainPos);
            divider.offset = offset;
            dividerMap[-index.second] = divider;
            laneIdx++;
        }
    }
    listContentModifier_->SetDividerMap(std::move(dividerMap));
    listContentModifier_->FlushDivider();
}

void ListPaintMethod::UpdateOverlayModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto scrollBarOverlayModifier = scrollBarOverlayModifier_.Upgrade();
    CHECK_NULL_VOID(scrollBarOverlayModifier);
    auto scrollBar = scrollBar_.Upgrade();
    CHECK_NULL_VOID(scrollBar);
    if (scrollBar->GetPositionModeUpdate()) {
        scrollBarOverlayModifier->SetPositionMode(scrollBar->GetPositionMode());
    }
    OffsetF fgOffset(scrollBar->GetActiveRect().Left(), scrollBar->GetActiveRect().Top());
    scrollBarOverlayModifier->StartBarAnimation(scrollBar->GetHoverAnimationType(),
        scrollBar->GetOpacityAnimationType(), scrollBar->GetNeedAdaptAnimation(), scrollBar->GetActiveRect());
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    scrollBarOverlayModifier->SetBarColor(scrollBar->GetForegroundColor());
    scrollBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
}
} // namespace OHOS::Ace::NG
