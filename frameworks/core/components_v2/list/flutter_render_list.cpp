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

#include "core/components_v2/list/flutter_render_list.h"

#include "base/utils/utils.h"
#include "core/components/common/painter/flutter_scroll_bar_painter.h"
#include "core/components_v2/list/render_list_item_group.h"
#include "core/pipeline/base/scoped_canvas_state.h"

namespace OHOS::Ace::V2 {

RenderLayer FlutterRenderList::GetRenderLayer()
{
    if (!layer_) {
        layer_ = AceType::MakeRefPtr<Flutter::ClipLayer>(
            0.0, GetLayoutSize().Width(), 0.0, GetLayoutSize().Height(), Flutter::Clip::HARD_EDGE);
    }
    return AceType::RawPtr(layer_);
}

bool FlutterRenderList::IsRepaintBoundary() const
{
    return true;
}

void FlutterRenderList::Paint(RenderContext& context, const Offset& offset)
{
    const auto& layoutSize = GetLayoutSize();
    if (layer_) {
        layer_->SetClip(0, layoutSize.Width(), 0, layoutSize.Height(), Flutter::Clip::HARD_EDGE);
    }

    for (const auto& child : items_) {
        if (child == currentStickyItem_ || child == selectedItem_) {
            continue;
        }
        PaintChild(child, context, offset);
    }
    PaintDivider(context);

    if (currentStickyItem_) {
        PaintChild(currentStickyItem_, context, offset);
    }

    if (selectedItem_) {
        selectedItem_->SetPosition(MakeValue<Offset>(selectedItemMainAxis_, 0.0));
        PaintChild(selectedItem_, context, offset);
    }

    // Notify scroll bar to update.
    if (scrollBarProxy_) {
        scrollBarProxy_->NotifyScrollBar(AceType::WeakClaim(this));
    }

    // paint scrollBar
    if (scrollBar_ && scrollBar_->NeedPaint()) {
        bool needPaint = false;
        if (scrollBar_->GetFirstLoad() || scrollBar_->IsActive() || scrollBar_->GetDisplayMode() == DisplayMode::ON) {
            scrollBarOpacity_ = UINT8_MAX;
            needPaint = true;
        } else {
            if (scrollBarOpacity_ != 0) {
                needPaint = true;
            }
        }
        if (needPaint) {
            scrollBar_->UpdateScrollBarRegion(offset, GetLayoutSize(), GetLastOffset(), GetEstimatedHeight());
            RefPtr<FlutterScrollBarPainter> scrollBarPainter = AceType::MakeRefPtr<FlutterScrollBarPainter>();
            const auto renderContext = static_cast<FlutterRenderContext*>(&context);
            flutter::Canvas* canvas = renderContext->GetCanvas();
            if (!canvas) {
                return;
            }
            scrollBarPainter->PaintBar(
                canvas, offset, GetPaintRect(), scrollBar_, GetGlobalOffset(), scrollBarOpacity_);
            if (scrollBar_->GetFirstLoad()) {
                scrollBar_->SetFirstLoad(false);
                scrollBar_->HandleScrollBarEnd();
            }
        }
    }
}

void FlutterRenderList::PaintDivider(RenderContext& context)
{
    const auto& layoutSize = GetLayoutSize();
    const auto& divider = component_->GetItemDivider();
    if (!divider || divider->color.GetAlpha() <= 0x00 || LessOrEqual(divider->strokeWidth.Value(), 0.0)) {
        return;
    }
    auto canvas = ScopedCanvas::Create(context);
    auto skCanvas = canvas.GetSkCanvas();
    if (skCanvas == nullptr) {
        LOGE("skia canvas is null");
        return;
    }

    const double crossSize = GetCrossSize(layoutSize);
    const double strokeWidth = NormalizePercentToPx(divider->strokeWidth, vertical_);
    const double halfSpaceWidth = std::max(spaceWidth_, strokeWidth) / 2.0;
    const double startMargin = NormalizePercentToPx(divider->startMargin, !IsVertical());
    const double endMargin = NormalizePercentToPx(divider->endMargin, !IsVertical());
    const double topOffset = halfSpaceWidth + (strokeWidth / 2.0);
    const double bottomOffset = topOffset - strokeWidth;

    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(divider->color.GetValue());
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setStrokeWidth(strokeWidth);
    bool isFirstLine = (startIndex_ == 0);
    bool lastIsItemGroup = false;
    int lane = 0;

    for (const auto& child : items_) {
        auto itemGroup = AceType::DynamicCast<RenderListItemGroup>(child);
        double mainAxis = GetMainAxis(child->GetPosition());
        if (itemGroup) {
            mainAxis = GetMainAxis(itemGroup->GetRenderNode()->GetPosition());
        }
        if (GreatOrEqual(mainAxis - topOffset, GetMainSize(layoutSize))) {
            break;
        }
        if (!isFirstLine && child != selectedItem_ && GreatNotEqual(mainAxis - bottomOffset, 0.0)) {
            if (GetLanes() > 1 && !lastIsItemGroup && !itemGroup) {
                double start = crossSize / GetLanes() * lane + startMargin;
                double end = crossSize / GetLanes() * (lane + 1) - endMargin;
                DrawDividerOnNode(skCanvas, paint, vertical_, start, mainAxis, end);
            } else {
                DrawDividerOnNode(skCanvas, paint, vertical_, startMargin, mainAxis, crossSize - endMargin);
            }
        }
        lastIsItemGroup = static_cast<bool>(itemGroup);
        lane = (GetLanes() <= 1 || (lane + 1) >= GetLanes() || itemGroup) ? 0 : lane + 1;
        isFirstLine = isFirstLine ? lane > 0 : false;
    }

    if (selectedItem_) {
        double mainAxis = targetMainAxis_ - halfSpaceWidth;
        DrawDividerOnNode(skCanvas, paint, vertical_, startMargin, mainAxis, crossSize - endMargin);
    }
}

void FlutterRenderList::DrawDividerOnNode(SkCanvas* skCanvas, const SkPaint& paint, bool isVertical,
    double startCrossAxis, double mainAxis, double endCrossAxis)
{
    if (vertical_) {
        skCanvas->drawLine(startCrossAxis, mainAxis, endCrossAxis, mainAxis, paint);
    } else {
        skCanvas->drawLine(mainAxis, startCrossAxis, mainAxis, endCrossAxis, paint);
    }
}

} // namespace OHOS::Ace::V2
