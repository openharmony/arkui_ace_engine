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
CanvasDrawFunction ListPaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
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
        .halfSpaceWidth = space_ / 2.0f, /* 2.0f half */
        .isVertical = vertical_,
        .lanes = lanes_ > 1 ? lanes_ : 1,
        .color = divider_.color
    };

    return [dividerInfo, itemPosition = std::move(itemPosition_)](RSCanvas& canvas) {
        float laneLen = dividerInfo.crossSize / dividerInfo.lanes - dividerInfo.startMargin - dividerInfo.endMargin;
        float crossLen = dividerInfo.crossSize - dividerInfo.startMargin - dividerInfo.endMargin;
        DividerPainter dividerPainter(dividerInfo.constrainStrokeWidth, crossLen,
            dividerInfo.isVertical, dividerInfo.color, LineCap::SQUARE);

        int32_t lanes = dividerInfo.lanes;
        int32_t laneIdx = 0;
        bool lastIsItemGroup = false;
        bool isFirstItem = (itemPosition.begin()->first == 0);

        for (const auto& child : itemPosition) {
            if (!isFirstItem) {
                float mainPos = child.second.startPos - dividerInfo.halfSpaceWidth;
                float crossPos = dividerInfo.startMargin;
                if (lanes > 1 && !lastIsItemGroup && !child.second.isGroup) {
                    crossPos += laneIdx * dividerInfo.crossSize / dividerInfo.lanes;
                    dividerPainter.SetDividerLength(laneLen);
                } else {
                    dividerPainter.SetDividerLength(crossLen);
                }
                OffsetF offset = dividerInfo.isVertical ? OffsetF(mainPos, crossPos) : OffsetF(crossPos, mainPos);
                dividerPainter.DrawLine(canvas, offset);
            }
            lastIsItemGroup = child.second.isGroup;
            laneIdx = (lanes <= 1 || (laneIdx + 1) >= lanes || child.second.isGroup) ? 0 : laneIdx + 1;
            isFirstItem = isFirstItem ? laneIdx > 0 : false;
        }
    };
}
} // namespace OHOS::Ace::NG