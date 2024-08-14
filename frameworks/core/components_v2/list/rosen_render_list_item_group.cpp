/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_v2/list/rosen_render_list_item_group.h"

#ifdef USE_ROSEN_DRAWING
#include "core/components_ng/render/drawing.h"
#endif
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace::V2 {

void RosenRenderListItemGroup::PaintDivider(RenderContext& context)
{
    const auto& layoutSize = GetLayoutSize();
    auto *const renderContext = static_cast<RosenRenderContext*>(&context);
    auto *canvas = renderContext->GetCanvas();
    auto rsNode = renderContext->GetRSNode();
    if (!canvas || !rsNode) {
        LOGE("canvas is null");
        return;
    }

    const auto& divider = GetItemDivider();
    if (!divider || divider->color.GetAlpha() <= 0x00 || LessOrEqual(divider->strokeWidth.Value(), 0.0)) {
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

#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(divider->color.GetValue());
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setStrokeWidth(strokeWidth);
#else
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetColor(divider->color.GetValue());
    pen.SetWidth(strokeWidth);
#endif
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
#ifndef USE_ROSEN_DRAWING
            if (IsVertical()) {
                canvas->drawLine(start, mainAxis, end, mainAxis, paint);
            } else {
                canvas->drawLine(mainAxis, start, mainAxis, end, paint);
            }
#else
            canvas->AttachPen(pen);
            if (IsVertical()) {
                canvas->DrawLine(RSPoint(start, mainAxis), RSPoint(end, mainAxis));
            } else {
                canvas->DrawLine(RSPoint(mainAxis, start), RSPoint(mainAxis, end));
            }
            canvas->DetachPen();
#endif
        }
        lane = (GetLanes() <= 1 || (lane + 1) >= GetLanes()) ? 0 : lane + 1;
        isFirstItem = isFirstItem ? lane > 0 : false;
    }
}

} // namespace OHOS::Ace::V2
