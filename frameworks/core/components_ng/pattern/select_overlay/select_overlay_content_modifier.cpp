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
#include <algorithm>

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
      firstCircleIsShow_(AceType::MakeRefPtr<PropertyBool>(true)),
      secondHandleIsShow_(AceType::MakeRefPtr<PropertyBool>(false)),
      secondCircleIsShow_(AceType::MakeRefPtr<PropertyBool>(true)),
      isHiddenHandle_(AceType::MakeRefPtr<PropertyBool>(false)),
      isHandleLineShow_(AceType::MakeRefPtr<PropertyBool>(false)),
      viewPort_(AceType::MakeRefPtr<PropertyRectF>(RectF(0, 0, 0, 0))),
      firstHandle_(AceType::MakeRefPtr<PropertyRectF>(RectF(0, 0, 0, 0))),
      secondHandle_(AceType::MakeRefPtr<PropertyRectF>(RectF(0, 0, 0, 0))),
      handleColor_(AceType::MakeRefPtr<PropertyColor>(Color::BLACK)),
      innerHandleColor_(AceType::MakeRefPtr<PropertyColor>(Color::BLACK)),
      handleRadius_(AceType::MakeRefPtr<PropertyFloat>(0.0)),
      handleStrokeWidth_(AceType::MakeRefPtr<PropertyFloat>(0.0)),
      innerHandleRadius_(AceType::MakeRefPtr<PropertyFloat>(0.0)),
      handleOpacity_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0))
{
    AttachProperty(inShowArea_);
    AttachProperty(handleReverse_);
    AttachProperty(isSingleHandle_);
    AttachProperty(firstHandleIsShow_);
    AttachProperty(firstCircleIsShow_);
    AttachProperty(secondHandleIsShow_);
    AttachProperty(secondCircleIsShow_);
    AttachProperty(isHiddenHandle_);
    AttachProperty(isHandleLineShow_);
    AttachProperty(viewPort_);
    AttachProperty(firstHandle_);
    AttachProperty(secondHandle_);
    AttachProperty(handleColor_);
    AttachProperty(innerHandleColor_);
    AttachProperty(handleRadius_);
    AttachProperty(handleStrokeWidth_);
    AttachProperty(innerHandleRadius_);
    AttachProperty(handleOpacity_);
}

void SelectOverlayContentModifier::onDraw(DrawingContext& drawingContext)
{
    CHECK_NULL_VOID(!isUsingMouse_);
    if (isHiddenHandle_->Get()) {
        return;
    }

    if (!inShowArea_->Get()) {
        return;
    }

    auto& canvas = drawingContext.canvas;
    canvas.Save();
    ClipViewPort(canvas);

    if (isSingleHandle_->Get()) {
        PaintSingleHandle(canvas);
    } else {
        PaintDoubleHandle(canvas);
    }

    canvas.Restore();
}

void SelectOverlayContentModifier::PaintSingleHandle(RSCanvas& canvas)
{
    if (PaintSingleHandleWithPoints(canvas)) {
        return;
    }
    PaintSingleHandleWithRect(canvas);
}

OffsetF SelectOverlayContentModifier::CalculateCenterPoint(
    const OffsetF& start, const OffsetF& end, float radius, bool handleOnTop)
{
    float vectorX = end.GetX() - start.GetX();
    float vectorY = end.GetY() - start.GetY();
    if (handleOnTop) {
        vectorX = -vectorX;
        vectorY = -vectorY;
    }
    float vectorLen = std::sqrt(vectorX * vectorX + vectorY * vectorY);
    float unitVectorX = NearZero(vectorLen) ? 0.0f : vectorX / vectorLen;
    float unitVectorY = NearZero(vectorLen) ? 0.0f : vectorY / vectorLen;
    float extendedVectorX = unitVectorX * radius;
    float extendedVectorY = unitVectorY * radius;
    float centerX = handleOnTop ? start.GetX() + extendedVectorX : end.GetX() + extendedVectorX;
    float centerY = handleOnTop ? start.GetY() + extendedVectorY : end.GetY() + extendedVectorY;
    return OffsetF(centerX, centerY);
}

bool SelectOverlayContentModifier::PaintSingleHandleWithPoints(RSCanvas& canvas)
{
    CHECK_NULL_RETURN(isPaintHandleUsePoints_, false);
    if (firstHandleIsShow_->Get()) {
        auto startPoint = firstHandlePaintInfo_.startPoint;
        startPoint.SetY(startPoint.GetY() + 1.0f);
        auto centerOffset = CalculateCenterPoint(
            firstHandlePaintInfo_.startPoint, firstHandlePaintInfo_.endPoint, GetDrawHandleRadius(), false);
        HandleDrawInfo drawInfo = {
            .startPoint = startPoint - centerOffset,
            .endPoint = firstHandlePaintInfo_.endPoint - centerOffset,
            .centerOffset = centerOffset,
            .handleWidth = firstHandlePaintInfo_.width,
            .isHandleLineShow = isHandleLineShow_->Get(),
            .isCircleShow = firstCircleIsShow_->Get()
        };
        PaintHandle(canvas, drawInfo);
    }
    if (secondHandleIsShow_->Get()) {
        auto startPoint = secondHandlePaintInfo_.startPoint;
        startPoint.SetY(startPoint.GetY() + 1.0f);
        auto centerOffset = CalculateCenterPoint(
            secondHandlePaintInfo_.startPoint, secondHandlePaintInfo_.endPoint, GetDrawHandleRadius(), false);
        HandleDrawInfo drawInfo = {
            .startPoint = startPoint - centerOffset,
            .endPoint = secondHandlePaintInfo_.endPoint - centerOffset,
            .centerOffset = centerOffset,
            .handleWidth = secondHandlePaintInfo_.width,
            .isHandleLineShow = isHandleLineShow_->Get(),
            .isCircleShow = secondCircleIsShow_->Get()
        };
        PaintHandle(canvas, drawInfo);
    }
    return true;
}

void SelectOverlayContentModifier::PaintSingleHandleWithRect(RSCanvas& canvas)
{
    if (firstHandleIsShow_->Get()) {
        PaintHandle(canvas, firstHandle_->Get(), false, isHandleLineShow_->Get(), firstCircleIsShow_->Get());
        return;
    }
    if (secondHandleIsShow_->Get()) {
        PaintHandle(canvas, secondHandle_->Get(), false, isHandleLineShow_->Get(), secondCircleIsShow_->Get());
    }
}

void SelectOverlayContentModifier::PaintDoubleHandle(RSCanvas& canvas)
{
    if (PaintDoubleHandleWithPoint(canvas)) {
        return;
    }
    PaintDoubleHandleWithRect(canvas);
}

bool SelectOverlayContentModifier::PaintDoubleHandleWithPoint(RSCanvas& canvas)
{
    CHECK_NULL_RETURN(isPaintHandleUsePoints_, false);
    if (firstHandleIsShow_->Get()) {
        auto handleOnTop = !handleReverse_->Get();
        auto centerOffset = CalculateCenterPoint(
            firstHandlePaintInfo_.startPoint, firstHandlePaintInfo_.endPoint, GetDrawHandleRadius(), handleOnTop);
        auto offsetY = handleOnTop ? -1.0f : 1.0f;
        auto startPoint = firstHandlePaintInfo_.startPoint;
        startPoint.SetY(startPoint.GetY() + offsetY);
        HandleDrawInfo drawInfo = {
            .startPoint = startPoint - centerOffset,
            .endPoint = firstHandlePaintInfo_.endPoint - centerOffset,
            .centerOffset = centerOffset,
            .handleWidth = firstHandlePaintInfo_.width,
            .isCircleShow = firstCircleIsShow_->Get()
        };
        PaintHandle(canvas, drawInfo);
    }
    if (secondHandleIsShow_->Get()) {
        auto handleOnTop = handleReverse_->Get();
        auto centerOffset = CalculateCenterPoint(
            secondHandlePaintInfo_.startPoint, secondHandlePaintInfo_.endPoint, GetDrawHandleRadius(), handleOnTop);
        auto offsetY = handleOnTop ? -1.0f : 1.0f;
        auto startPoint = secondHandlePaintInfo_.startPoint;
        startPoint.SetY(startPoint.GetY() + offsetY);
        HandleDrawInfo drawInfo = {
            .startPoint = startPoint - centerOffset,
            .endPoint = secondHandlePaintInfo_.endPoint - centerOffset,
            .centerOffset = centerOffset,
            .handleWidth = secondHandlePaintInfo_.width,
            .isCircleShow = secondCircleIsShow_->Get()
        };
        PaintHandle(canvas, drawInfo);
    }
    return true;
}

void SelectOverlayContentModifier::PaintDoubleHandleWithRect(RSCanvas& canvas)
{
    if (firstHandleIsShow_->Get()) {
        PaintHandle(canvas, firstHandle_->Get(), !handleReverse_->Get(), true, firstCircleIsShow_->Get());
    }
    if (secondHandleIsShow_->Get()) {
        PaintHandle(canvas, secondHandle_->Get(), handleReverse_->Get(), true, secondCircleIsShow_->Get());
    }
}

void SelectOverlayContentModifier::ClipViewPort(RSCanvas& canvas)
{
    if (!isOverlayMode_) {
        return;
    }
    auto left = viewPort_->Get().Left();
    auto top = viewPort_->Get().Top();
    auto right = viewPort_->Get().Right();
    auto bottom = viewPort_->Get().Bottom();
    auto upHandle = GetFirstPaintRect();
    auto upHandleIsShow = firstHandleIsShow_->Get();
    auto downHandle = GetSecondPaintRect();
    auto downHandleIsShow = secondHandleIsShow_->Get();
    if (isSingleHandle_->Get()) {
        upHandleIsShow = false;
        downHandleIsShow = firstHandleIsShow_->Get() || secondHandleIsShow_->Get();
        downHandle = firstHandleIsShow_->Get() ? GetFirstPaintRect()
                                               : (secondHandleIsShow_->Get() ? GetSecondPaintRect() : downHandle);
    } else if (handleReverse_->Get()) {
        upHandle = GetSecondPaintRect();
        upHandleIsShow = secondHandleIsShow_->Get();
        downHandle = GetFirstPaintRect();
        downHandleIsShow = firstHandleIsShow_->Get();
    }
    auto handleDiameter = handleRadius_->Get() * 2;
    auto handleRadius = isPaintHandleUsePoints_ ? 0.0f : handleRadius_->Get();
    if (upHandleIsShow) {
        auto halfWidth = isPaintHandleUsePoints_ ? 0.0f : upHandle.Width() / 2.0f;
        left = std::min(upHandle.Left() + halfWidth - handleRadius, left);
        right = std::max(upHandle.Right() - halfWidth + handleRadius, right);
        top = std::min(upHandle.Top() - handleDiameter, top);
        bottom = std::max(upHandle.Bottom(), bottom);
    }
    if (downHandleIsShow) {
        auto halfWidth = isPaintHandleUsePoints_ ? 0 : downHandle.Width() / 2.0f;
        left = std::min(downHandle.Left() + halfWidth - handleRadius, left);
        right = std::max(downHandle.Right() - halfWidth + handleRadius, right);
        top = std::min(downHandle.Top(), top);
        bottom = std::max(downHandle.Bottom() + handleDiameter, bottom);
    }
    auto strokeWidth = handleStrokeWidth_->Get();
    RSRect clipInnerRect = RSRect(left - strokeWidth, top - strokeWidth, right + strokeWidth, bottom + strokeWidth);
    canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
}

RectF SelectOverlayContentModifier::ConvertPointsToRect(const SelectHandlePaintInfo& paintInfo) const
{
    auto handleDiameter = handleRadius_->Get() * 2;
    auto left = std::min(paintInfo.startPoint.GetX(), paintInfo.endPoint.GetX()) - handleDiameter;
    auto right = std::max(paintInfo.startPoint.GetX(), paintInfo.endPoint.GetX()) + handleDiameter;
    auto top = std::min(paintInfo.startPoint.GetY(), paintInfo.endPoint.GetY()) - handleDiameter;
    auto bottom = std::max(paintInfo.startPoint.GetY(), paintInfo.endPoint.GetY()) + handleDiameter;
    auto width = std::max(right - left, paintInfo.width);
    auto height = std::max(bottom - top, paintInfo.width);
    return RectF(OffsetF(left, top), SizeF(width, height));
}

RectF SelectOverlayContentModifier::GetFirstPaintRect() const
{
    if (isPaintHandleUsePoints_) {
        return ConvertPointsToRect(firstHandlePaintInfo_);
    }
    return firstHandle_->Get();
}

RectF SelectOverlayContentModifier::GetSecondPaintRect() const
{
    if (isPaintHandleUsePoints_) {
        return ConvertPointsToRect(secondHandlePaintInfo_);
    }
    return secondHandle_->Get();
}

void SelectOverlayContentModifier::PaintHandle(
    RSCanvas& canvas, const RectF& handleRect, bool handleOnTop, bool isHandleLineShow, bool isCircleShow)
{
    auto rectTopX = (handleRect.Left() + handleRect.Right()) / 2.0f;
    auto centerOffset = OffsetF(rectTopX, 0.0f);
    OffsetF startPoint(0.0, 0.0);
    OffsetF endPoint(0.0, 0.0);
    auto scaleY = isOverlayMode_ ? 1.0f : scale_.y;
    auto handleRadius = handleRadius_->Get() * scaleY;
    auto gap = NearEqual(scaleY, 1.0f) ? 0.0f : handleStrokeWidth_->Get() * scaleY;
    if (handleOnTop) {
        centerOffset.SetY(handleRect.Top() - handleRadius);
        startPoint.SetY(handleRadius + gap);
        endPoint.SetY(handleRadius + handleRect.Height() + gap);
    } else {
        centerOffset.SetY(handleRect.Bottom() + handleRadius);
        startPoint.SetY(-handleRadius - gap);
        endPoint.SetY(-handleRadius - handleRect.Height() - gap);
    }
    HandleDrawInfo drawInfo = { .startPoint = startPoint,
        .endPoint = endPoint,
        .centerOffset = centerOffset,
        .handleWidth = handleRect.Width(),
        .isHandleLineShow = isHandleLineShow,
        .isCircleShow = isCircleShow };
    PaintHandle(canvas, drawInfo);
}

void SelectOverlayContentModifier::PaintHandle(RSCanvas& canvas, const HandleDrawInfo& handleInfo)
{
    auto scaleX = isOverlayMode_ ? 1.0f : scale_.x;
    auto scaleY = isOverlayMode_ ? 1.0f : scale_.y;
    canvas.Save();
    canvas.Translate(handleInfo.centerOffset.GetX(), handleInfo.centerOffset.GetY());
    Color handleColor = handleColor_->Get();
    handleColor = handleColor.BlendOpacity(handleOpacity_->Get());
    if (handleInfo.isCircleShow) {
        canvas.Save();
        canvas.Scale(scaleX, scaleY);
        // Paint inner circle.
        Color innerHandleColor = innerHandleColor_->Get();
        innerHandleColor = innerHandleColor.BlendOpacity(handleOpacity_->Get());
        RSBrush brush;
        brush.SetAntiAlias(true);
        brush.SetColor(innerHandleColor.GetValue());
        canvas.AttachBrush(brush);
        canvas.DrawCircle(RSPoint(0.0, 0.0), innerHandleRadius_->Get());
        canvas.DetachBrush();
        // Paint outer hollow circle.
        float strokeWidth = handleStrokeWidth_->Get();
        RSPen strokePen;
        strokePen.SetAntiAlias(true);
        strokePen.SetColor(handleColor.GetValue());
        strokePen.SetWidth(strokeWidth);
        canvas.AttachPen(strokePen);
        canvas.DrawCircle(RSPoint(0.0, 0.0), handleRadius_->Get());
        canvas.DetachPen();
        canvas.Restore();
    }
    if (handleInfo.isHandleLineShow) {
        canvas.Save();
        canvas.Scale(scaleX, 1.0f);
        RSPen pen;
        pen.SetAntiAlias(true);
        // Paint line of handle.
        pen.SetColor(handleColor.GetValue());
        pen.SetWidth(handleInfo.handleWidth);
        pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
        canvas.AttachPen(pen);
        canvas.DrawLine(RSPoint(handleInfo.startPoint.GetX(), handleInfo.startPoint.GetY()),
            RSPoint(handleInfo.endPoint.GetX(), handleInfo.endPoint.GetY()));
        canvas.DetachPen();
        canvas.Restore();
    }
    canvas.Restore();
}
} // namespace OHOS::Ace::NG
