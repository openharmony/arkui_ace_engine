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

#include "core/components_ng/pattern/select_overlay/select_overlay_paint_method.h"

#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_layout_algorithm.h"
#include "core/components_ng/render/drawing.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
CanvasDrawFunction SelectOverlayPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    // paint rect is in global position, need to convert to local position
    auto offset = paintWrapper->GetGeometryNode()->GetFrameOffset();
    info_.firstHandle.paintRect -= offset;
    info_.secondHandle.paintRect -= offset;

    auto rect = paintWrapper->GetGeometryNode()->GetFrameRect();
    return [this, frameRect = rect](RSCanvas& canvas) { DrawHandles(canvas, frameRect); };
}

void SelectOverlayPaintMethod::UpdateOverlayModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);

    const auto& padding = textOverlayTheme->GetMenuPadding();
    auto right = padding.Right().ConvertToPx();
    auto top = padding.Top().ConvertToPx();
    auto sideWidth = textOverlayTheme->GetMenuToolbarHeight().ConvertToPx() - padding.Top().ConvertToPx() -
                     padding.Bottom().ConvertToPx();
    auto buttonRadius = sideWidth / 2.0;

    auto offset = defaultMenuEndOffset_ + OffsetF(-buttonRadius - right, buttonRadius + top);
    selectOverlayModifier_->SetMenuOptionOffset(offset);
    selectOverlayModifier_->SetHasExtensitonMenu(hasExtensionMenu_);
}

void SelectOverlayPaintMethod::DrawHandles(RSCanvas& canvas, const RectF& frameRect)
{
    if (!SelectOverlayLayoutAlgorithm::CheckInShowArea(info_)) {
        LOGD("hide handles due to handle is out of show area");
        return;
    }

    canvas.Save();
    auto frameNode = info_.callerFrameNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto viewPortOption = frameNode->GetViewPort();
    RectF viewPort = frameRect;
    if (viewPortOption.has_value()) {
        viewPort = viewPortOption.value();
    }
    LOGD("select_overlay ClipRect viewPort: %{public}s ", viewPort.ToString().c_str());
    RSRect clipInnerRect = RSRect(
        viewPort.GetX(), viewPort.GetY(), viewPort.Width() + viewPort.GetX(), viewPort.Height() + viewPort.GetY());
    canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
    if (info_.isSingleHandle) {
        // Paint one handle.
        if (info_.firstHandle.isShow) {
            PaintHandle(canvas, info_.firstHandle.paintRect, false);
            return;
        }
        if (info_.secondHandle.isShow) {
            PaintHandle(canvas, info_.secondHandle.paintRect, false);
        }
    } else {
        if (info_.firstHandle.isShow) {
            PaintHandle(canvas, info_.firstHandle.paintRect, !info_.handleReverse);
        }
        if (info_.secondHandle.isShow) {
            PaintHandle(canvas, info_.secondHandle.paintRect, info_.handleReverse);
        }
    }
    canvas.Restore();
}

void SelectOverlayPaintMethod::PaintHandle(RSCanvas& canvas, const RectF& handleRect, bool handleOnTop)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(theme);
    auto handleColor = theme->GetHandleColor();
    auto innerHandleColor = theme->GetHandleColorInner();
    auto handleRadius = theme->GetHandleDiameter().ConvertToPx() / 2.0f;
    auto innerHandleRadius = theme->GetHandleDiameterInner().ConvertToPx() / 2.0f;
    auto rectTopX = (handleRect.Left() + handleRect.Right()) / 2.0f;
    auto centerOffset = OffsetF(rectTopX, 0.0f);
    if (handleOnTop) {
        centerOffset.SetY(handleRect.Top() - handleRadius);
    } else {
        centerOffset.SetY(handleRect.Bottom() + handleRadius);
    }
    canvas.Save();
    RSBrush brush;
    brush.SetAntiAlias(true);
    canvas.Translate(centerOffset.GetX(), centerOffset.GetY());
    // Paint outer circle.
    brush.SetColor(handleColor.GetValue());
    canvas.AttachBrush(brush);
    canvas.DrawCircle({ 0.0, 0.0 }, handleRadius);
    // Paint inner circle.
    brush.SetColor(innerHandleColor.GetValue());
    canvas.AttachBrush(brush);
    canvas.DrawCircle({ 0.0, 0.0 }, innerHandleRadius);
    canvas.DetachBrush();

    RSPen pen;
    pen.SetAntiAlias(true);
    // Paint line of handle.
    pen.SetColor(handleColor.GetValue());
    pen.SetWidth(handleRect.Width());
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    canvas.AttachPen(pen);
    // 1.0 is avoid separation of handle circle and handle line.
    OffsetF startPoint(0.0, -handleRadius + 1.0f);
    // 1.0_dp is designed by UX, handle line is higher than height of select region.
    OffsetF endPoint(0.0, -handleRadius - handleRect.Height());
    if (handleOnTop) {
        startPoint.SetY(handleRadius - 1.0);
        endPoint.SetY(handleRadius + handleRect.Height());
    }
    canvas.DrawLine({ startPoint.GetX(), startPoint.GetY() }, { endPoint.GetX(), endPoint.GetY() });
    canvas.DetachPen();
    canvas.Restore();
}

} // namespace OHOS::Ace::NG