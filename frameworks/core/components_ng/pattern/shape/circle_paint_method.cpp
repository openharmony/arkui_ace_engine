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

#include "core/components_ng/pattern/shape/circle_paint_method.h"

namespace OHOS::Ace::NG {

void CirclePaintMethod::UpdateFillHDRColorHeadRoom(
    PaintWrapper* paintWrapper, const ShapePaintProperty& shapePaintProperty) const
{
    CHECK_NULL_VOID(paintWrapper);
    constexpr float DEFAULT_SDR_HEADROOM = 1.0f;
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto fillColor = shapePaintProperty.HasFill() ? shapePaintProperty.GetFillValue() : Color::BLACK;
    auto headRoomColor = fillColor.GetHeadRoomColor();
    renderContext->SetHDRColorHeadRoom(
        headRoomColor.has_value() ? headRoomColor.value().headRoom : DEFAULT_SDR_HEADROOM);
}

void CirclePaintMethod::UpdateStrokeHDRColorHeadRoom(
    PaintWrapper* paintWrapper, const ShapePaintProperty& shapePaintProperty) const
{
    CHECK_NULL_VOID(paintWrapper);
    if (!shapePaintProperty.HasStroke()) {
        return;
    }
    auto headRoomColor = shapePaintProperty.GetStrokeValue().GetHeadRoomColor();
    if (!headRoomColor.has_value()) {
        return;
    }
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetHDRColorHeadRoom(headRoomColor.value().headRoom);
}

CanvasDrawFunction CirclePaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    CHECK_NULL_RETURN(paintWrapper, nullptr);
    auto paintProperty = paintWrapper->GetPaintProperty();
    CHECK_NULL_RETURN(paintProperty, nullptr);
    auto shapePaintProperty = DynamicCast<ShapePaintProperty>(paintProperty->Clone());
    CHECK_NULL_RETURN(shapePaintProperty, nullptr);

    if (propertiesFromAncestor_) {
        if (!shapePaintProperty->HasFill() && propertiesFromAncestor_->HasFill()) {
            auto renderContext = paintWrapper->GetRenderContext();
            CHECK_NULL_RETURN(renderContext, nullptr);
            renderContext->UpdateForegroundColor(propertiesFromAncestor_->GetFillValue());
            renderContext->ResetForegroundColorStrategy();
        }
        shapePaintProperty->UpdateShapeProperty(propertiesFromAncestor_);
    }
    if (paintWrapper->HasForegroundColor()) {
        shapePaintProperty->UpdateFill(paintWrapper->GetForegroundColor());
    } else if (paintWrapper->HasForegroundColorStrategy()) {
        shapePaintProperty->UpdateFill(Color::FOREGROUND);
        shapePaintProperty->ResetFillOpacity();
    }
    UpdateFillHDRColorHeadRoom(paintWrapper, *shapePaintProperty);
    float height = paintWrapper->GetContentSize().Height();
    float width = paintWrapper->GetContentSize().Width();
    float radius = (width > height ? height : width) * 0.5;
    UpdateStrokeHDRColorHeadRoom(paintWrapper, *shapePaintProperty);
    return
        [radiusValue = radius, offsetValue = paintWrapper->GetContentOffset(), shapePaintProperty, paintWrapper](
            RSCanvas& canvas) {
                CirclePainter::DrawCircle(canvas, radiusValue, offsetValue, *shapePaintProperty);
                paintWrapper->FlushOverlayModifier();
            };
}

RefPtr<Modifier> CirclePaintMethod::GetOverlayModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_RETURN(paintWrapper, nullptr);
    CHECK_NULL_RETURN(shapeOverlayModifier_, nullptr);
    auto paintProperty = paintWrapper->GetPaintProperty();
    CHECK_NULL_RETURN(paintProperty, nullptr);
    auto shapePaintProperty = DynamicCast<ShapePaintProperty>(paintProperty->Clone());
    CHECK_NULL_RETURN(shapePaintProperty, nullptr);

    if (propertiesFromAncestor_) {
        shapePaintProperty->UpdateShapeProperty(propertiesFromAncestor_);
    }
    float height = paintWrapper->GetContentSize().Height();
    float width = paintWrapper->GetContentSize().Width();
    auto offset = paintWrapper->GetContentOffset();
    float strokeWidth =
        shapePaintProperty->GetStrokeWidthValue(ShapePaintProperty::STROKE_WIDTH_DEFAULT).ConvertToPx();
    RectF boundsRect = { (offset.GetX() - strokeWidth), (offset.GetY() - strokeWidth), (width + strokeWidth * 2),
        (height + strokeWidth * 2) };
    shapeOverlayModifier_->SetBoundsRect(boundsRect);
    return shapeOverlayModifier_;
}
} // namespace OHOS::Ace::NG
