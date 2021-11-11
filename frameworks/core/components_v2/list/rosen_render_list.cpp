/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components_v2/list/rosen_render_list.h"

#include "include/core/SkCanvas.h"

#include "base/utils/utils.h"
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace::V2 {

void RosenRenderList::Update(const RefPtr<Component>& component)
{
    RenderList::Update(component);
    auto rsNode = GetRSNode();
    if (rsNode == nullptr) {
        LOGE("rsNode is null");
        return;
    }
    rsNode->SetClipToFrame(true);
}

void RosenRenderList::Paint(RenderContext& context, const Offset& offset)
{
    const auto& layoutSize = GetLayoutSize();

    for (const auto& child : items_) {
        if (child == currentStickyItem_ || child == selectedItem_) {
            continue;
        }
        PaintChild(child, context, offset);
    }

    const auto& divider = component_->GetItemDivider();
    if (divider && divider->color.GetAlpha() > 0x00 && GreatNotEqual(divider->strokeWidth.Value(), 0.0)) {
        auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
        if (canvas == nullptr) {
            LOGE("skia canvas is null");
            return;
        }

        const double mainSize = GetMainSize(layoutSize);
        const double strokeWidth = NormalizePercentToPx(divider->strokeWidth, vertical_);
        const double halfSpaceWidth = std::max(spaceWidth_, strokeWidth) / 2.0;
        const double startCrossAxis = NormalizePercentToPx(divider->startMargin, !vertical_);
        const double endCrossAxis = GetCrossSize(layoutSize) - NormalizePercentToPx(divider->endMargin, !vertical_);
        const double topOffset = halfSpaceWidth + (strokeWidth / 2.0);
        const double bottomOffset = topOffset - strokeWidth;

        SkPaint paint;
        paint.setAntiAlias(true);
        paint.setColor(divider->color.GetValue());
        paint.setStyle(SkPaint::Style::kStroke_Style);
        paint.setStrokeWidth(strokeWidth);

        for (const auto& child : items_) {
            if (child == selectedItem_) {
                continue;
            }

            double mainAxis = GetMainAxis(child->GetPosition());
            if (GreatOrEqual(mainAxis - topOffset, mainSize)) {
                break;
            }
            if (LessOrEqual(mainAxis - bottomOffset, 0.0)) {
                continue;
            }
            mainAxis -= halfSpaceWidth;
            if (vertical_) {
                canvas->drawLine(startCrossAxis, mainAxis, endCrossAxis, mainAxis, paint);
            } else {
                canvas->drawLine(mainAxis, startCrossAxis, mainAxis, endCrossAxis, paint);
            }
        }

        if (selectedItem_) {
            double mainAxis = targetMainAxis_ - halfSpaceWidth;
            if (vertical_) {
                canvas->drawLine(startCrossAxis, mainAxis, endCrossAxis, mainAxis, paint);
            } else {
                canvas->drawLine(mainAxis, startCrossAxis, mainAxis, endCrossAxis, paint);
            }
        }
    }

    if (currentStickyItem_) {
        PaintChild(currentStickyItem_, context, offset);
    }

    if (selectedItem_) {
        selectedItem_->SetPosition(MakeValue<Offset>(selectedItemMainAxis_, 0.0));
        PaintChild(selectedItem_, context, offset);
    }
}

} // namespace OHOS::Ace::V2
