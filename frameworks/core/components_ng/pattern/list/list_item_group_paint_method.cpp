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

#include "core/components_ng/pattern/list/list_item_group_paint_method.h"

namespace OHOS::Ace::NG {
void ListItemGroupPaintMethod::PaintDivider(PaintWrapper* paintWrapper, RSCanvas& canvas)
{
    if (!divider_.strokeWidth.IsValid() || divider_.strokeWidth.Unit() == DimensionUnit::PERCENT) {
        return;
    }
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetPaddingSize();
    OffsetF paddingOffset = geometryNode->GetPaddingOffset() - geometryNode->GetFrameOffset();
    Axis axis = vertical_ ? Axis::HORIZONTAL : Axis::VERTICAL;
    DividerGroupInfo info = {
        .lanes = lanes_ > 1 ? lanes_ : 1,
        .crossSize = frameSize.CrossSize(axis),
        .mainPadding = paddingOffset.GetMainOffset(axis),
        .crossPadding = paddingOffset.GetCrossOffset(axis),
        .constrainStrokeWidth = divider_.strokeWidth.ConvertToPx(),
        .halfSpaceWidth = (spaceWidth_ + divider_.strokeWidth.ConvertToPx()) / 2.0f, /* 2.0f half */
        .startMargin = std::max(0.0, divider_.startMargin.ConvertToPx()),
        .endMargin = std::max(0.0, divider_.endMargin.ConvertToPx())
    };
    fSpacingTotal_ = (info.lanes - 1) * laneGutter_;
    float laneLen = (info.crossSize - fSpacingTotal_) / info.lanes -
        info.startMargin - info.endMargin;
    if (NearZero(laneLen)) return;
    if (LessNotEqual(laneLen, 0.0f)) {
        info.startMargin = 0.0f;
        info.endMargin = 0.0f;
        laneLen = (info.crossSize - fSpacingTotal_) / info.lanes -
            info.startMargin - info.endMargin;
    }
    DividerPainter dividerPainter(
        info.constrainStrokeWidth, laneLen, vertical_, divider_.color, LineCap::SQUARE);
    UpdateDividerList(info, dividerPainter, canvas);
}

void ListItemGroupPaintMethod::UpdateDividerList(const DividerGroupInfo& info,
    const DividerPainter& dividerPainter, RSCanvas& canvas)
{
    int32_t laneIdx = 0;
    bool isFirstItem = (itemPosition_.begin()->first == 0);
    std::list<int32_t> lastLineIndex;
    bool nextIsPressed = false;
    for (const auto& child : itemPosition_) {
        auto nextId = itemPosition_.find(child.first - info.lanes);
        nextIsPressed = (nextId == itemPosition_.end()) ? child.second.isPressed : nextId->second.isPressed;
        if (!isFirstItem && !(child.second.isPressed || nextIsPressed)) {
            DrawDivider(child.first, laneIdx, info, dividerPainter, canvas);
        }
        if (laneIdx == 0) {
            lastLineIndex.clear();
        }
        lastLineIndex.emplace_back(child.first);
        laneIdx = (laneIdx + 1) >= info.lanes ? 0 : laneIdx + 1;
        isFirstItem = isFirstItem ? laneIdx > 0 : false;
    }
    if (!lastLineIndex.empty() && *lastLineIndex.rbegin() < totalItemCount_ - 1) {
        int32_t laneIdx = 0;
        for (auto index : lastLineIndex) {
            if (index + info.lanes >= totalItemCount_) {
                break;
            }
            if (!itemPosition_.at(index).isPressed) {
                DrawLastLineDivider(index, laneIdx, info, dividerPainter, canvas);
            }
            laneIdx++;
        }
    }
}

void ListItemGroupPaintMethod::DrawDivider(int32_t index, int32_t laneIdx, const DividerGroupInfo& info,
    const DividerPainter& dividerPainter, RSCanvas& canvas)
{
    float mainPos = info.mainPadding + itemPosition_.at(index).startPos - info.halfSpaceWidth;
    float crossPos = info.startMargin + info.crossPadding +
        laneIdx * ((info.crossSize - fSpacingTotal_) / info.lanes + laneGutter_);
    if (layoutDirection_ == TextDirection::RTL && vertical_) {
        mainPos = info.mainPadding + mainSize_ - itemPosition_.at(index).startPos +
            info.halfSpaceWidth - info.constrainStrokeWidth;
    } else if (layoutDirection_ == TextDirection::RTL && !vertical_) {
        float dividerLen = (info.crossSize - fSpacingTotal_) / info.lanes - info.startMargin - info.endMargin;
        crossPos = info.crossPadding + info.crossSize - info.startMargin - dividerLen -
            laneIdx * ((info.crossSize - fSpacingTotal_) / info.lanes + laneGutter_);
    }
    OffsetF offset = vertical_ ? OffsetF(mainPos, crossPos) : OffsetF(crossPos, mainPos);
    dividerPainter.DrawLine(canvas, offset);
}

void ListItemGroupPaintMethod::DrawLastLineDivider(int32_t index, int32_t laneIdx, const DividerGroupInfo& info,
    const DividerPainter& dividerPainter, RSCanvas& canvas)
{
    float mainPos = info.mainPadding + itemPosition_.at(index).endPos + spaceWidth_ - info.halfSpaceWidth;
    float crossPos = info.startMargin + info.crossPadding +
        laneIdx * ((info.crossSize - fSpacingTotal_) / info.lanes + laneGutter_);
    if (layoutDirection_ == TextDirection::RTL && vertical_) {
        mainPos = info.mainPadding + mainSize_ - itemPosition_.at(index).endPos - info.halfSpaceWidth;
    } else if (layoutDirection_ == TextDirection::RTL && !vertical_) {
        float dividerLen = (info.crossSize - fSpacingTotal_) / info.lanes - info.startMargin - info.endMargin;
        crossPos = info.crossPadding + info.crossSize - info.startMargin - dividerLen -
            laneIdx * ((info.crossSize - fSpacingTotal_) / info.lanes + laneGutter_);
    }
    OffsetF offset = vertical_ ? OffsetF(mainPos, crossPos) : OffsetF(crossPos, mainPos);
    dividerPainter.DrawLine(canvas, offset);
}

CanvasDrawFunction ListItemGroupPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto painter = weak.Upgrade();
        CHECK_NULL_VOID(painter);
        painter->PaintDivider(paintWrapper, canvas);
    };
    return paintFunc;
}
} // namespace OHOS::Ace::NG