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

#include "core/components_v2/list/flutter_render_list_item_group.h"

#include "base/utils/utils.h"
#include "core/components/common/painter/flutter_scroll_bar_painter.h"
#include "core/pipeline/base/scoped_canvas_state.h"

namespace OHOS::Ace::V2 {

void FlutterRenderListItemGroup::PaintDivider(RenderContext& context)
{
    const auto& layoutSize = GetLayoutSize();
    const auto& divider = GetItemDivider();
    if (!divider || divider->color.GetAlpha() <= 0x00 || LessOrEqual(divider->strokeWidth.Value(), 0.0)) {
        return;
    }
    auto canvas = ScopedCanvas::Create(context);
    auto *skCanvas = canvas.GetSkCanvas();
    if (skCanvas == nullptr) {
        LOGE("skia canvas is null");
        return;
    }

    const double mainSize = GetMainSize(layoutSize);
    const double crossSize = GetCrossSize(layoutSize);
    const double strokeWidth = NormalizePercentToPx(divider->strokeWidth, IsVertical());
    const double halfSpaceWidth = std::max(GetSpace(), strokeWidth) / 2.0;
    const double startMargin = NormalizePercentToPx(divider->startMargin, !IsVertical());
    const double endMargin = NormalizePercentToPx(divider->endMargin, !IsVertical());
    const double topOffset = halfSpaceWidth + (strokeWidth / 2.0);
    const double bottomOffset = topOffset - strokeWidth;
    const double mainOffset = GetMainAxis(GetRenderNode()->GetPosition());

    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(divider->color.GetValue());
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setStrokeWidth(strokeWidth);
    bool isFirstItem = (GetStartIndex() == 0);
    size_t lane = 0;

    for (const auto& child : GetItems()) {
        double mainAxis = GetMainAxis(child->GetPosition());
        if (GreatOrEqual(mainAxis - topOffset, mainSize)) {
            break;
        }
        if (!isFirstItem && GreatNotEqual(mainAxis - bottomOffset, 0.0)) {
            double start = GetLanes() > 1 ? crossSize / GetLanes() * lane + startMargin : startMargin;
            double end = GetLanes() > 1 ? crossSize / GetLanes() * (lane + 1) - endMargin : crossSize - endMargin;
            mainAxis -= halfSpaceWidth;
            mainAxis += mainOffset;
            if (IsVertical()) {
                skCanvas->drawLine(start, mainAxis, end, mainAxis, paint);
            } else {
                skCanvas->drawLine(mainAxis, start, mainAxis, end, paint);
            }
        }
        lane = (GetLanes() <= 1 || (lane + 1) >= GetLanes()) ? 0 : lane + 1;
        isFirstItem = isFirstItem ? lane > 0 : false;
    }
}

} // namespace OHOS::Ace::V2
