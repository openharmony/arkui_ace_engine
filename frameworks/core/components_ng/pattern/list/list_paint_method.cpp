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
    double constrainStrokeWidth = divider_.strokeWidth.ConvertToPx();
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    auto frameSize = geometryNode->GetFrameSize();
    double dividerLength = 0.0;
    if (vertical_) {
        dividerLength = frameSize.Height() - divider_.startMargin.ConvertToPx() - divider_.endMargin.ConvertToPx();
    } else {
        dividerLength = frameSize.Width() - divider_.startMargin.ConvertToPx() - divider_.endMargin.ConvertToPx();
    }
    DividerPainter dividerPainter(constrainStrokeWidth, dividerLength, vertical_, divider_.color, LineCap::SQUARE);

    int32_t startIndex = startIndex_;
    int32_t endIndex = endIndex_;
    float startMargin = divider_.startMargin.ConvertToPx();

    return [dividerPainter, startIndex, endIndex, itemPosition = std::move(itemPosition_), startMargin](RSCanvas& canvas)
        { dividerPainter.DrawListLines(canvas, startIndex, endIndex, itemPosition, startMargin); };
}
} // namespace OHOS::Ace::NG