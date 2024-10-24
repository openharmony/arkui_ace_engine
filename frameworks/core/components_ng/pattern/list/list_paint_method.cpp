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
    float size = paintWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
    if (padding) {
        frameSize.MinusPadding(*padding->left, *padding->right, *padding->top, *padding->bottom);
    }
    UpdateFadingGradient(renderContext, paintWrapper);

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
    DividerInfo dividerInfo = { .constrainStrokeWidth = divider_.strokeWidth.ConvertToPx(),
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
        .laneGutter = laneGutter_,
        .mainSize = size };
    float checkMargin = dividerInfo.crossSize / dividerInfo.lanes - dividerInfo.startMargin - dividerInfo.endMargin;
    if (NearZero(checkMargin)) {
        return;
    }
    if (LessNotEqual(checkMargin, 0.0f)) {
        dividerInfo.startMargin = 0.0f;
        dividerInfo.endMargin = 0.0f;
    }
    UpdateDividerList(dividerInfo);
}

void ListPaintMethod::UpdateDividerList(const DividerInfo& dividerInfo)
{
    listContentModifier_->SetDividerPainter(
        dividerInfo.constrainStrokeWidth, dividerInfo.isVertical, dividerInfo.color);
    int32_t lanes = dividerInfo.lanes;
    int32_t laneIdx = 0;
    bool lastIsItemGroup = false;
    bool isFirstItem = (itemPosition_.begin()->first == 0);
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
    if (!lastLineIndex.empty() && lastLineIndex.rbegin()->first < dividerInfo.totalItemCount - 1) {
        int32_t laneIdx = 0;
        for (auto index : lastLineIndex) {
            if (index.first + lanes >= dividerInfo.totalItemCount) {
                break;
            }
            if (!itemPosition_.at(index.first).isPressed) {
                dividerMap[-index.second] = HandleLastLineIndex(index.first, laneIdx, dividerInfo);
            }
            laneIdx++;
        }
    }
    listContentModifier_->SetDividerMap(std::move(dividerMap));
}

ListDivider ListPaintMethod::HandleDividerList(
    int32_t index, bool lastIsGroup, int32_t laneIdx, const DividerInfo& dividerInfo)
{
    ListDivider divider;
    float fSpacingTotal = (dividerInfo.lanes - 1) * dividerInfo.laneGutter;
    float laneLen =
        (dividerInfo.crossSize - fSpacingTotal) / dividerInfo.lanes - dividerInfo.startMargin - dividerInfo.endMargin;
    float crossLen = dividerInfo.crossSize - dividerInfo.startMargin - dividerInfo.endMargin;
    float divOffset = (dividerInfo.space + dividerInfo.constrainStrokeWidth) / 2; /* 2 half */
    float mainPos = itemPosition_.at(index).startPos - divOffset + dividerInfo.mainPadding + adjustOffset_;
    float crossPos = dividerInfo.startMargin + dividerInfo.crossPadding;
    if (isReverse_) {
        if (dividerInfo.isVertical) {
            float divOffset = (dividerInfo.space - dividerInfo.constrainStrokeWidth) / 2; /* 2 half */
            mainPos = dividerInfo.mainSize - itemPosition_.at(index).startPos + divOffset - dividerInfo.mainPadding +
                      adjustOffset_;
        } else {
            crossPos = dividerInfo.endMargin + dividerInfo.crossPadding;
        }
    }
    if (dividerInfo.lanes > 1 && !lastIsGroup && !itemPosition_.at(index).isGroup) {
        crossPos += laneIdx * ((dividerInfo.crossSize - fSpacingTotal) / dividerInfo.lanes + dividerInfo.laneGutter);
        divider.length = laneLen;
    } else {
        divider.length = crossLen;
    }
    OffsetF offset = dividerInfo.isVertical ? OffsetF(mainPos, crossPos) : OffsetF(crossPos, mainPos);
    divider.offset = offset;
    return divider;
}

ListDivider ListPaintMethod::HandleLastLineIndex(int32_t index, int32_t laneIdx, const DividerInfo& dividerInfo)
{
    ListDivider divider;
    float fSpacingTotal = (dividerInfo.lanes - 1) * dividerInfo.laneGutter;
    float laneLen =
        (dividerInfo.crossSize - fSpacingTotal) / dividerInfo.lanes - dividerInfo.startMargin - dividerInfo.endMargin;
    float crossLen = dividerInfo.crossSize - dividerInfo.startMargin - dividerInfo.endMargin;
    float divOffset = (dividerInfo.space - dividerInfo.constrainStrokeWidth) / 2; /* 2 half */
    float mainPos = itemPosition_.at(index).endPos + divOffset + dividerInfo.mainPadding;
    float crossPos = dividerInfo.startMargin + dividerInfo.crossPadding;
    if (isReverse_) {
        if (dividerInfo.isVertical) {
            float divOffset = (dividerInfo.space + dividerInfo.constrainStrokeWidth) / 2; /* 2 half */
            mainPos = dividerInfo.mainSize - itemPosition_.at(index).endPos - divOffset - dividerInfo.mainPadding;
        } else {
            crossPos = dividerInfo.endMargin + dividerInfo.crossPadding;
        }
    }
    if (dividerInfo.lanes > 1 && !itemPosition_.at(index).isGroup) {
        crossPos += laneIdx * ((dividerInfo.crossSize - fSpacingTotal) / dividerInfo.lanes + dividerInfo.laneGutter);
        divider.length = laneLen;
    } else {
        divider.length = crossLen;
    }
    OffsetF offset = dividerInfo.isVertical ? OffsetF(mainPos, crossPos) : OffsetF(crossPos, mainPos);
    divider.offset = offset;
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
    OffsetF fgOffset(scrollBar->GetActiveRect().Left(), scrollBar->GetActiveRect().Top());
    scrollBarOverlayModifier->StartBarAnimation(scrollBar->GetHoverAnimationType(),
        scrollBar->GetOpacityAnimationType(), scrollBar->GetNeedAdaptAnimation(), scrollBar->GetActiveRect());
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    scrollBarOverlayModifier->SetBarColor(scrollBar->GetForegroundColor());
    scrollBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
}
} // namespace OHOS::Ace::NG
