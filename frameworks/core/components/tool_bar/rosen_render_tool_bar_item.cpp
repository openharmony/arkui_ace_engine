/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components/tool_bar/rosen_render_tool_bar_item.h"

#include "render_service_client/core/ui/rs_node.h"
#ifndef USE_ROSEN_DRAWING
#include "include/core/SkMaskFilter.h"
#endif

#include "frameworks/core/components/transform/rosen_render_transform.h"

namespace OHOS::Ace {
// for focus
constexpr Dimension TOOL_BAR_FOCUS_DEL_OFFSET = 4.0_vp;
constexpr Dimension TOOL_BAR_FOCUS_DEL_SIZE = 8.0_vp;

void RosenRenderToolBarItem::Update(const RefPtr<Component>& component)
{
    RenderToolBarItem::Update(component);
    auto rsNode = GetRSNode();
    if (rsNode == nullptr) {
        return;
    }
    rsNode->SetClipToFrame(true);
}


void RosenRenderToolBarItem::Paint(RenderContext& context, const Offset& offset)
{
    auto renderContext = AceType::DynamicCast<RosenRenderContext>(&context);
    if (!renderContext) {
        LOGE("Render context is null");
        return;
    }
#ifndef USE_ROSEN_DRAWING
    SkCanvas* canvas = renderContext->GetCanvas();
#else
    RSCanvas* canvas = renderContext->GetCanvas();
#endif
    if (canvas == nullptr) {
        LOGE("Paint canvas is null");
        return;
    }

    DrawShape(*canvas, Rect(offset, GetLayoutSize()), GetEventEffectColor(), NormalizeToPx(rrectRadius_));

    if (onFocus_) {
        DrawFocus();
    }
    if (onHover_) {
        DrawShape(*canvas, Rect(offset, GetLayoutSize()), hoverColor_, NormalizeToPx(rrectRadius_));
    }

    RenderToolBarItem::Paint(context, offset);
}

void RosenRenderToolBarItem::DrawFocus()
{
    Offset offset =
        GetPosition() + Offset(NormalizeToPx(TOOL_BAR_FOCUS_DEL_OFFSET), NormalizeToPx(TOOL_BAR_FOCUS_DEL_OFFSET));
    Size layoutSize =
        GetLayoutSize() - Size(NormalizeToPx(TOOL_BAR_FOCUS_DEL_SIZE), NormalizeToPx(TOOL_BAR_FOCUS_DEL_SIZE));
    Offset globalOffset =
        GetGlobalOffset() + Offset(NormalizeToPx(TOOL_BAR_FOCUS_DEL_OFFSET), NormalizeToPx(TOOL_BAR_FOCUS_DEL_OFFSET));
    RequestFocusAnimation(globalOffset, Rect(offset, layoutSize), Radius(rrectRadius_));
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderToolBarItem::DrawShape(
    SkCanvas& canvas, const Rect& paintRect, const Color& color, double radius)
{
    SkPaint paint;
    SkRRect rRect;

    paint.setColor(color.GetValue());
    rRect.setRectXY(SkRect::MakeIWH(paintRect.Width(), paintRect.Height()), radius, radius);
    rRect.offset(paintRect.GetOffset().GetX(), paintRect.GetOffset().GetY());
    canvas.drawRRect(rRect, paint);
}
#else
void RosenRenderToolBarItem::DrawShape(
    RSCanvas& canvas, const Rect& paintRect, const Color& color, double radius)
{
    RSPen pen;

    pen.SetColor(color.GetValue());
    RSRoundRect rRect(RSRect(0, 0, paintRect.Width(), paintRect.Height()), radius, radius);
    rRect.Offset(paintRect.GetOffset().GetX(), paintRect.GetOffset().GetY());
    canvas.AttachPen(pen);
    canvas.DrawRoundRect(rRect);
    canvas.DetachPen();
}
#endif
} // namespace OHOS::Ace
