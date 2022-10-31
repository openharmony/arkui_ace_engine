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
CanvasDrawFunction ListItemGroupPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    auto frameSize = geometryNode->GetFrameSize();
    struct DividerInfo {
        float constrainStrokeWidth;
        float crossSize;
        float startMargin;
        float endMargin;
        bool isVertical;
        int32_t lanes;
        Color color;
    } dividerInfo = {
        .constrainStrokeWidth = divider_.strokeWidth.ConvertToPx(),
        .crossSize = vertical_ ? frameSize.Height() : frameSize.Width(),
        .startMargin = divider_.startMargin.ConvertToPx(),
        .endMargin = divider_.endMargin.ConvertToPx(),
        .isVertical = vertical_,
        .lanes = lanes_ > 1 ? lanes_ : 1,
        .color = divider_.color
    };

    return [dividerInfo, itemPosition = std::move(itemPosition_)](RSCanvas& canvas) {
        DividerPainter dividerPainter(dividerInfo.constrainStrokeWidth,
            dividerInfo.crossSize / dividerInfo.lanes - dividerInfo.startMargin - dividerInfo.endMargin,
            dividerInfo.isVertical, dividerInfo.color, LineCap::SQUARE);
        int32_t laneIdx = 0;
        auto nextItem = itemPosition.begin();
        auto currItem = itemPosition.begin();
        for (int32_t i = 0; i < dividerInfo.lanes && nextItem != itemPosition.end(); nextItem++, i++) {}
        while (nextItem != itemPosition.end()) {
            auto mainPos = (currItem->second.second + nextItem->second.first) / 2; /* 2:average */
            auto crossPos = dividerInfo.startMargin + laneIdx * dividerInfo.crossSize / dividerInfo.lanes;
            OffsetF offset = dividerInfo.isVertical ? OffsetF(mainPos, crossPos) : OffsetF(crossPos, mainPos);
            dividerPainter.DrawLine(canvas, offset);
            currItem++;
            nextItem++;
            laneIdx = (laneIdx + 1) % dividerInfo.lanes;
        }
    };
}
} // namespace OHOS::Ace::NG