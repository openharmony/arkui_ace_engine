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
    if (!divider_.strokeWidth.IsValid()) {
        return nullptr;
    }
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    auto frameSize = geometryNode->GetFrameSize();
    struct DividerInfo {
        float constrainStrokeWidth;
        float crossSize;
        float startMargin;
        float endMargin;
        float halfSpaceWidth;
        bool isVertical;
        int32_t lanes;
        Color color;
    } dividerInfo = {
        .constrainStrokeWidth = divider_.strokeWidth.ConvertToPx(),
        .crossSize = vertical_ ? frameSize.Height() : frameSize.Width(),
        .startMargin = divider_.startMargin.ConvertToPx(),
        .endMargin = divider_.endMargin.ConvertToPx(),
        .halfSpaceWidth = (spaceWidth_ + divider_.strokeWidth.ConvertToPx()) / 2.0f, /* 2.0f half */
        .isVertical = vertical_,
        .lanes = lanes_ > 1 ? lanes_ : 1,
        .color = divider_.color
    };

    return [dividerInfo, itemPosition = std::move(itemPosition_)](RSCanvas& canvas) {
        int32_t lanes = dividerInfo.lanes > 1 ? dividerInfo.lanes : 1;
        float laneLen = dividerInfo.crossSize / lanes - dividerInfo.startMargin - dividerInfo.endMargin;
        DividerPainter dividerPainter(dividerInfo.constrainStrokeWidth,
            laneLen, dividerInfo.isVertical, dividerInfo.color, LineCap::SQUARE);
        int32_t laneIdx = 0;
        bool isFirstItem = (itemPosition.begin()->first == 0);
        for (const auto& child : itemPosition) {
            if (!isFirstItem) {
                float mainPos = child.second.first - dividerInfo.halfSpaceWidth;
                float crossPos = dividerInfo.startMargin + laneIdx * dividerInfo.crossSize / lanes;
                OffsetF offset = dividerInfo.isVertical ? OffsetF(mainPos, crossPos) : OffsetF(crossPos, mainPos);
                dividerPainter.DrawLine(canvas, offset);
            }
            laneIdx = (laneIdx + 1) >= lanes ? 0 : laneIdx + 1;
            isFirstItem = isFirstItem ? laneIdx > 0 : false;
        }
    };
}
} // namespace OHOS::Ace::NG