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
    auto frameSize = geometryNode->GetPaddingSize();
    OffsetF paddingOffset = geometryNode->GetPaddingOffset() - geometryNode->GetFrameOffset();
    Axis axis = vertical_ ? Axis::HORIZONTAL : Axis::VERTICAL;
    DividerGroupInfo dgInfo = {
        .lanes = lanes_ > 1 ? lanes_ : 1,
        .crossSize = frameSize.CrossSize(axis),
        .constrainStrokeWidth = divider_.strokeWidth.ConvertToPx(),
        .halfSpaceWidth = (spaceWidth_ + divider_.strokeWidth.ConvertToPx()) / 2.0f, /* 2.0f half */
        .startMargin = std::max(0.0, divider_.startMargin.ConvertToPx()),
        .endMargin = std::max(0.0, divider_.endMargin.ConvertToPx())
    };
    fSpacingTotal_ = (dgInfo.lanes - 1) * laneGutter_;
    float laneLen = (dgInfo.crossSize - fSpacingTotal_) / dgInfo.lanes -
        dgInfo.startMargin - dgInfo.endMargin;
    if (NearZero(laneLen)) return;
    if (LessNotEqual(laneLen, 0.0f)) {
        dgInfo.startMargin = 0.0f;
        dgInfo.endMargin = 0.0f;
        laneLen = (dgInfo.crossSize - fSpacingTotal_) / dgInfo.lanes -
            dgInfo.startMargin - dgInfo.endMargin;
    }
    DividerPainter dividerPainter(
        dgInfo.constrainStrokeWidth, laneLen, vertical_, divider_.color, LineCap::SQUARE);
    UpdateDividerList(dgInfo, dividerPainter, paddingOffset, canvas);
}

void ListItemGroupPaintMethod::UpdateDividerList(const DividerGroupInfo& dgInfo,
    DividerPainter dividerPainter, OffsetF paddingOffset, RSCanvas& canvas)
{
    int32_t laneIdx = 0;
    bool isFirstItem = (itemPosition_.begin()->first == 0);
    std::list<int32_t> lastLineIndex;
    bool nextIsPressed = false;
    for (const auto& child : itemPosition_) {
        auto nextId = child.first - dgInfo.lanes;
        nextIsPressed = nextId < 0 ? child.second.isPressed : itemPosition_[nextId].isPressed;
        if (!isFirstItem && !(child.second.isPressed || nextIsPressed)) {
            float mainPos = child.second.startPos - dgInfo.halfSpaceWidth;
            float crossPos = dgInfo.startMargin +
                laneIdx * ((dgInfo.crossSize - fSpacingTotal_) / dgInfo.lanes + laneGutter_);
            float verticalX = (layoutDirection_ == TextDirection::RTL) ?
                (mainSize_ - mainPos - dgInfo.constrainStrokeWidth) : mainPos;
            if (layoutDirection_ == TextDirection::RTL) {
                crossPos = dgInfo.endMargin +
                    laneIdx * ((dgInfo.crossSize - fSpacingTotal_) / dgInfo.lanes + laneGutter_);
            }
            OffsetF offset = vertical_ ? OffsetF(verticalX, crossPos) : OffsetF(crossPos, mainPos);
            dividerPainter.DrawLine(canvas, offset + paddingOffset);
        }
        if (laneIdx == 0) {
            lastLineIndex.clear();
        }
        lastLineIndex.emplace_back(child.first);
        laneIdx = (laneIdx + 1) >= dgInfo.lanes ? 0 : laneIdx + 1;
        isFirstItem = isFirstItem ? laneIdx > 0 : false;
    }
    if (!lastLineIndex.empty() && *lastLineIndex.rbegin() < totalItemCount_ - 1) {
        int32_t laneIdx = 0;
        for (auto index : lastLineIndex) {
            if (index + dgInfo.lanes >= totalItemCount_) {
                break;
            }
            if (!itemPosition_.at(index).isPressed) {
                float mainPos = itemPosition_.at(index).endPos + spaceWidth_ - dgInfo.halfSpaceWidth;
                float crossPos = dgInfo.startMargin +
                    laneIdx * ((dgInfo.crossSize - fSpacingTotal_) / dgInfo.lanes + laneGutter_);
                float verticalX = (layoutDirection_ == TextDirection::RTL) ?
                    (mainSize_ - mainPos - dgInfo.constrainStrokeWidth) : mainPos;
                OffsetF offset = vertical_ ? OffsetF(verticalX, crossPos) : OffsetF(crossPos, mainPos);
                dividerPainter.DrawLine(canvas, offset + paddingOffset);
            }
            laneIdx++;
        }
    }
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