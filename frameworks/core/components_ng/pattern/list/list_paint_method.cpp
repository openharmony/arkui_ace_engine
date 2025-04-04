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

#ifdef ARKUI_CIRCLE_FEATURE
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"
#endif // ARKUI_CIRCLE_FEATURE

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
    OffsetF paddingOffset = geometryNode->GetPaddingOffset() - geometryNode->GetFrameOffset();
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto frameSize = renderContext->GetPaintRectWithoutTransform().GetSize();
    auto& padding = geometryNode->GetPadding();
    if (padding) {
        frameSize.MinusPadding(*padding->left, *padding->right, *padding->top, *padding->bottom);
    }
    UpdateFadingGradient(renderContext);

    if (TryContentClip(paintWrapper)) {
        listContentModifier_->SetClip(false);
    } else {
        const bool hasPadding = padding && padding->HasValue();
        bool clip = hasPadding && (!renderContext || renderContext->GetClipEdge().value_or(true));
        listContentModifier_->SetClipOffset(paddingOffset);
        listContentModifier_->SetClipSize(frameSize);
        listContentModifier_->SetClip(clip);
    }

    float contentSize = vertical_ ? frameSize.Width() : frameSize.Height();
    if (!divider_.strokeWidth.IsValid() || totalItemCount_ <= 0 ||
        divider_.strokeWidth.Unit() == DimensionUnit::PERCENT ||
        GreatOrEqual(divider_.strokeWidth.ConvertToPx(), contentSize)) {
        ListDividerMap dividerMap;
        listContentModifier_->SetDividerMap(std::move(dividerMap));
        return;
    }
    Axis axis = vertical_ ? Axis::HORIZONTAL : Axis::VERTICAL;
    DividerInfo dividerInfo = {
        .constrainStrokeWidth = divider_.strokeWidth.ConvertToPx(),
        .mainSize = vertical_ ? frameSize.Width() : frameSize.Height(),
        .crossSize = vertical_ ? frameSize.Height() : frameSize.Width(),
        .mainPadding = paddingOffset.GetMainOffset(axis),
        .crossPadding = paddingOffset.GetCrossOffset(axis),
        .startMargin = std::max(0.0, divider_.startMargin.ConvertToPx()),
        .endMargin = std::max(0.0, divider_.endMargin.ConvertToPx()),
        .space = space_,
        .laneGutter = laneGutter_,
        .lanes = lanes_ > 1 ? lanes_ : 1,
        .totalItemCount = totalItemCount_,
        .color = divider_.color,
        .isVertical = vertical_
    };
    float checkMargin = dividerInfo.crossSize / dividerInfo.lanes - dividerInfo.startMargin - dividerInfo.endMargin;
    if (NearZero(checkMargin)) {
        return;
    }
    if (LessNotEqual(checkMargin, 0.0f)) {
        dividerInfo.startMargin = 0.0f;
        dividerInfo.endMargin = 0.0f;
    }
    bool clip = !renderContext || renderContext->GetClipEdge().value_or(true);
    UpdateDividerList(dividerInfo, clip);
}

void ListPaintMethod::UpdateDividerList(const DividerInfo& dividerInfo, bool clip)
{
    listContentModifier_->SetDividerPainter(
        dividerInfo.constrainStrokeWidth, dividerInfo.isVertical, dividerInfo.color);
    int32_t lanes = dividerInfo.lanes;
    int32_t laneIdx = initLaneIdx_;
    bool lastIsItemGroup = false;
    bool isFirstItem = (itemPosition_.begin()->first == 0) || !clip;
    std::map<int32_t, int32_t> lastLineIndex;
    ListDividerMap dividerMap;
    bool nextIsPressed = false;
    for (const auto& child : itemPosition_) {
        auto nextId = child.first - lanes;
        nextIsPressed = nextId < 0 || lastIsItemGroup || child.second.isGroup ? false : itemPosition_[nextId].isPressed;
        if (!isFirstItem && !(child.second.isPressed || nextIsPressed)) {
            dividerMap[child.second.id] = HandleDividerList(child.first, lastIsItemGroup, laneIdx, dividerInfo);
        }
        if (laneIdx == 0 || child.second.isGroup) {
            lastLineIndex.clear();
        }
        lastLineIndex[child.first] = child.second.id;
        lastIsItemGroup = child.second.isGroup;
        laneIdx = (lanes <= 1 || (laneIdx + 1) >= lanes || child.second.isGroup) ? 0 : laneIdx + 1;
        isFirstItem = isFirstItem ? laneIdx > 0 : false;
    }
    if (clip && !lastLineIndex.empty() && lastLineIndex.rbegin()->first < dividerInfo.totalItemCount - 1) {
        int32_t lastLineLaneIdx = 0;
        for (auto index : lastLineIndex) {
            if (index.first + lanes >= dividerInfo.totalItemCount) {
                break;
            }
            if (!itemPosition_.at(index.first).isPressed) {
                dividerMap[-index.second] = HandleLastLineIndex(index.first, lastLineLaneIdx, dividerInfo);
            }
            lastLineLaneIdx++;
        }
    }
    listContentModifier_->SetDividerMap(std::move(dividerMap));
}

ListDivider ListPaintMethod::HandleDividerList(
    int32_t index, bool lastIsGroup, int32_t laneIdx, const DividerInfo& dividerInfo)
{
    ListDivider divider;
    bool laneIdxValid = dividerInfo.lanes > 1 && !lastIsGroup && !itemPosition_.at(index).isGroup;
    float avgCrossSize = (dividerInfo.crossSize + dividerInfo.laneGutter) / dividerInfo.lanes - dividerInfo.laneGutter;
    float dividerLen = laneIdxValid ? avgCrossSize : dividerInfo.crossSize;
    dividerLen = dividerLen - dividerInfo.startMargin - dividerInfo.endMargin;
    float mainPos = dividerInfo.mainPadding + itemPosition_.at(index).startPos -
        (dividerInfo.space + dividerInfo.constrainStrokeWidth) / 2; /* 2 half */
    float crossPos = dividerInfo.startMargin + dividerInfo.crossPadding;
    if (isRTL_ && dividerInfo.isVertical) {
        mainPos = dividerInfo.mainPadding + dividerInfo.mainSize - itemPosition_.at(index).startPos +
            (dividerInfo.space - dividerInfo.constrainStrokeWidth) / 2; /* 2 half */
        crossPos += (int)laneIdxValid * laneIdx * (avgCrossSize + dividerInfo.laneGutter);
    } else if (isRTL_ && !dividerInfo.isVertical) {
        crossPos = dividerInfo.crossPadding + dividerInfo.crossSize - dividerInfo.startMargin - dividerLen;
        crossPos -= (int)laneIdxValid * laneIdx * (avgCrossSize + dividerInfo.laneGutter);
    } else {
        crossPos += (int)laneIdxValid * laneIdx * (avgCrossSize + dividerInfo.laneGutter);
    }
    divider.length = dividerLen;
    divider.offset = dividerInfo.isVertical ?
        OffsetF(mainPos, crossPos + adjustOffset_) : OffsetF(crossPos, mainPos + adjustOffset_);
    return divider;
}

ListDivider ListPaintMethod::HandleLastLineIndex(int32_t index, int32_t laneIdx, const DividerInfo& dividerInfo)
{
    ListDivider divider;
    bool laneIdxValid = dividerInfo.lanes > 1 && !itemPosition_.at(index).isGroup;
    float avgCrossSize = (dividerInfo.crossSize + dividerInfo.laneGutter) / dividerInfo.lanes - dividerInfo.laneGutter;
    float dividerLen = laneIdxValid ? avgCrossSize : dividerInfo.crossSize;
    dividerLen = dividerLen - dividerInfo.startMargin - dividerInfo.endMargin;
    float mainPos = dividerInfo.mainPadding + itemPosition_.at(index).endPos +
        (dividerInfo.space - dividerInfo.constrainStrokeWidth) / 2; /* 2 half */
    float crossPos = dividerInfo.startMargin + dividerInfo.crossPadding;
    if (isRTL_ && dividerInfo.isVertical) {
        mainPos = dividerInfo.mainPadding + dividerInfo.mainSize - itemPosition_.at(index).endPos -
            (dividerInfo.space + dividerInfo.constrainStrokeWidth) / 2; /* 2 half */
        crossPos += (int)laneIdxValid * laneIdx * (avgCrossSize + dividerInfo.laneGutter);
    } else if (isRTL_ && !dividerInfo.isVertical) {
        crossPos = dividerInfo.crossPadding + dividerInfo.crossSize - dividerInfo.startMargin - dividerLen;
        crossPos -= (int)laneIdxValid * laneIdx * (avgCrossSize + dividerInfo.laneGutter);
    } else {
        crossPos += (int)laneIdxValid * laneIdx * (avgCrossSize + dividerInfo.laneGutter);
    }
    divider.length = dividerLen;
    divider.offset = dividerInfo.isVertical ?
        OffsetF(mainPos, crossPos + adjustOffset_) : OffsetF(crossPos, mainPos + adjustOffset_);
    return divider;
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

#ifdef ARKUI_CIRCLE_FEATURE
    auto shapeMode = scrollBar->GetShapeMode();
    if (shapeMode == ShapeMode::ROUND) {
        auto arcScrollBarOverlayModifier = AceType::DynamicCast<ArcScrollBarOverlayModifier>(scrollBarOverlayModifier);
        CHECK_NULL_VOID(arcScrollBarOverlayModifier);
        auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
        CHECK_NULL_VOID(arcScrollBar);
        scrollBarOverlayModifier->SetBarColor(arcScrollBar->GetArcForegroundColor());
        arcScrollBarOverlayModifier->SetBackgroundBarColor(arcScrollBar->GetArcBackgroundColor());
        arcScrollBarOverlayModifier->StartArcBarAnimation(arcScrollBar->GetHoverAnimationType(),
            arcScrollBar->GetOpacityAnimationType(), arcScrollBar->GetNeedAdaptAnimation(),
            arcScrollBar->GetArcActiveRect(), arcScrollBar->GetArcBarRect());
    } else {
        scrollBarOverlayModifier->SetBarColor(scrollBar->GetForegroundColor());
        scrollBarOverlayModifier->StartBarAnimation(scrollBar->GetHoverAnimationType(),
            scrollBar->GetOpacityAnimationType(), scrollBar->GetNeedAdaptAnimation(), scrollBar->GetActiveRect());
    }
#else
    scrollBarOverlayModifier->SetBarColor(scrollBar->GetForegroundColor());
    scrollBarOverlayModifier->StartBarAnimation(scrollBar->GetHoverAnimationType(),
        scrollBar->GetOpacityAnimationType(), scrollBar->GetNeedAdaptAnimation(), scrollBar->GetActiveRect());
#endif // ARKUI_CIRCLE_FEATURE
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    scrollBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
}
} // namespace OHOS::Ace::NG
