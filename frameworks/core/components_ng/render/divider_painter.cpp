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

#include "core/components_ng/render/divider_painter.h"

#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
void DividerPainter::DrawLine(RSCanvas& canvas, const OffsetF& offset) const
{
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetWidth(constrainStrokeWidth_);
    pen.SetCapStyle(ToRSCapStyle(lineCap_.value_or(LineCap::SQUARE)));
    pen.SetColor(ToRSColor(dividerColor_.value_or(Color::BLACK)));
    canvas.AttachPen(pen);

    auto startPointX = offset.GetX();
    auto startPointY = offset.GetY();
    PointF start = PointF(startPointX, startPointY);
    PointF end = vertical_ ? PointF(startPointX, startPointY + dividerLength_)
                           : PointF(startPointX + dividerLength_, startPointY);
    canvas.DrawLine(ToRSPonit(start) , ToRSPonit(end));
}

void DividerPainter::DrawListLines(RSCanvas& canvas, const int32_t startIndex, const int32_t endIndex,
    const ListLayoutAlgorithm::PositionMap& itemPosition, float startMargin) const
{
    for (int32_t lineIndex = startIndex; lineIndex < endIndex; lineIndex++) {
        if (vertical_) {
            DrawLine(canvas, OffsetF(itemPosition.at(lineIndex).second + constrainStrokeWidth_ / 2.0, startMargin));
        } else {
            DrawLine(canvas, OffsetF(startMargin, itemPosition.at(lineIndex).second + constrainStrokeWidth_ / 2.0));
        }
    }
}
} // namespace OHOS::Ace::NG