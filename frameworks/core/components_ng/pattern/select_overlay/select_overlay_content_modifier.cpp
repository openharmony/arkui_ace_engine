/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/select_overlay/select_overlay_content_modifier.h"

#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_layout_algorithm.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_paint_method.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
SelectOverlayContentModifier::SelectOverlayContentModifier()
    : inShowArea_(AceType::MakeRefPtr<PropertyBool>(false)),
      handleReverse_(AceType::MakeRefPtr<PropertyBool>(false)),
      isSingleHandle_(AceType::MakeRefPtr<PropertyBool>(false)),
      firstHandleIsShow_(AceType::MakeRefPtr<PropertyBool>(false)),
      secondHandleIsShow_(AceType::MakeRefPtr<PropertyBool>(false)),
      viewPort_(AceType::MakeRefPtr<PropertyRectF>(RectF(0, 0, 0, 0))),
      firstHandle_(AceType::MakeRefPtr<PropertyRectF>(RectF(0, 0, 0, 0))),
      secondHandle_(AceType::MakeRefPtr<PropertyRectF>(RectF(0, 0, 0, 0))),
      handleColor_(AceType::MakeRefPtr<PropertyColor>(Color::BLACK)),
      innerHandleColor_(AceType::MakeRefPtr<PropertyColor>(Color::BLACK)),
      handleRadius_(AceType::MakeRefPtr<PropertyFloat>(0.0)),
      innerHandleRadius_(AceType::MakeRefPtr<PropertyFloat>(0.0)),
      handleOpacity_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0))
{
    AttachProperty(inShowArea_);
    AttachProperty(handleReverse_);
    AttachProperty(isSingleHandle_);
    AttachProperty(firstHandleIsShow_);
    AttachProperty(secondHandleIsShow_);
    AttachProperty(viewPort_);
    AttachProperty(firstHandle_);
    AttachProperty(secondHandle_);
    AttachProperty(handleColor_);
    AttachProperty(innerHandleColor_);
    AttachProperty(handleRadius_);
    AttachProperty(innerHandleRadius_);
    AttachProperty(handleOpacity_);
}

void SelectOverlayContentModifier::onDraw(DrawingContext& drawingContext)
{
    if (!inShowArea_->Get()) {
        LOGD("hide handles due to handle is out of show area");
        return;
    }

    auto& canvas = drawingContext.canvas;
    canvas.Save();
    RSRect clipInnerRect = RSRect(viewPort_->Get().GetX(), viewPort_->Get().GetY(),
        viewPort_->Get().Width() + viewPort_->Get().GetX(), viewPort_->Get().Height() + viewPort_->Get().GetY());
    canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);

    if (isSingleHandle_->Get()) {
        // Paint one handle.
        if (firstHandleIsShow_->Get()) {
            PaintHandle(canvas, firstHandle_->Get(), false);
        } else if (secondHandleIsShow_->Get()) {
            PaintHandle(canvas, secondHandle_->Get(), false);
        }
    } else {
        if (firstHandleIsShow_->Get()) {
            PaintHandle(canvas, firstHandle_->Get(), !handleReverse_->Get());
        }
        if (secondHandleIsShow_->Get()) {
            PaintHandle(canvas, secondHandle_->Get(), handleReverse_->Get());
        }
    }
    canvas.Restore();
}

void SelectOverlayContentModifier::PaintHandle(RSCanvas& canvas, const RectF& handleRect, bool handleOnTop)
{
    auto rectTopX = (handleRect.Left() + handleRect.Right()) / 2.0f;
    auto centerOffset = OffsetF(rectTopX, 0.0f);
    OffsetF startPoint(0.0, 0.0);
    OffsetF endPoint(0.0, 0.0);
    if (handleOnTop) {
        centerOffset.SetY(handleRect.Top() - handleRadius_->Get());
        startPoint.SetY(handleRadius_->Get() - 1.0);
        endPoint.SetY(handleRadius_->Get() + handleRect.Height());
    } else {
        centerOffset.SetY(handleRect.Bottom() + handleRadius_->Get());
        startPoint.SetY(-handleRadius_->Get() + 1.0f);
        endPoint.SetY(-handleRadius_->Get() - handleRect.Height());
    }

    canvas.Save();
    RSBrush brush;
    brush.SetAntiAlias(true);
    canvas.Translate(centerOffset.GetX(), centerOffset.GetY());
    // Paint outer circle.
    Color handleColor = handleColor_->Get();
    handleColor = handleColor.BlendOpacity(handleOpacity_->Get());
    brush.SetColor(handleColor.GetValue());
    canvas.AttachBrush(brush);
    canvas.DrawCircle(RSPoint(0.0, 0.0), handleRadius_->Get());
    // Paint inner circle.
    Color innerHandleColor = innerHandleColor_->Get();
    innerHandleColor = innerHandleColor.BlendOpacity(handleOpacity_->Get());
    brush.SetColor(innerHandleColor.GetValue());
    canvas.AttachBrush(brush);
    canvas.DrawCircle(RSPoint(0.0, 0.0), innerHandleRadius_->Get());
    canvas.DetachBrush();

    RSPen pen;
    pen.SetAntiAlias(true);
    // Paint line of handle.
    pen.SetColor(handleColor.GetValue());
    pen.SetWidth(handleRect.Width());
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    canvas.AttachPen(pen);
    canvas.DrawLine(RSPoint(startPoint.GetX(), startPoint.GetY()), RSPoint(endPoint.GetX(), endPoint.GetY()));
    canvas.DetachPen();
    canvas.Restore();
}
} // namespace OHOS::Ace::NG
