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

    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    float crossSize = frameSize.CrossSize(axis);
    float constrainStrokeWidth = divider_.strokeWidth.ConvertToPx();
    float halfSpaceWidth = (spaceWidth_ + divider_.strokeWidth.ConvertToPx()) / 2.0f; /* 2.0f half */
    auto startMargin = std::max(0.0, divider_.startMargin.ConvertToPx());
    auto endMargin = std::max(0.0, divider_.endMargin.ConvertToPx());
    float laneLen = crossSize / lanes - startMargin - endMargin;
    if (NearZero(laneLen)) return;
    if (LessNotEqual(laneLen, 0.0f)) {
        startMargin = 0.0f;
        endMargin = 0.0f;
        laneLen = crossSize / lanes - startMargin - endMargin;
    }
    DividerPainter dividerPainter(constrainStrokeWidth, laneLen, vertical_, divider_.color, LineCap::SQUARE);
    int32_t laneIdx = 0;
    bool isFirstItem = (itemPosition_.begin()->first == 0);
    for (const auto& child : itemPosition_) {
        if (!isFirstItem) {
            float mainPos = child.second.first - halfSpaceWidth;
            float crossPos = startMargin + laneIdx * crossSize / lanes;
            OffsetF offset = vertical_ ? OffsetF(mainPos, crossPos) : OffsetF(crossPos, mainPos);
            dividerPainter.DrawLine(canvas, offset + paddingOffset);
        }
        laneIdx = (laneIdx + 1) >= lanes ? 0 : laneIdx + 1;
        isFirstItem = isFirstItem ? laneIdx > 0 : false;
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