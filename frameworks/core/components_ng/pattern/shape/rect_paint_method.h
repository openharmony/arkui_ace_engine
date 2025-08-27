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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SHAPE_RECT_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SHAPE_RECT_PAINT_METHOD_H

#include "base/geometry/ng/radius.h"
#include "core/components_ng/pattern/shape/shape_paint_method.h"
#include "core/components_ng/pattern/shape/shape_overlay_modifier.h"
#include "core/components_ng/pattern/shape/rect_paint_property.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/rect_painter.h"
namespace OHOS::Ace::NG {

class ACE_EXPORT RectPaintMethod : public ShapePaintMethod {
    DECLARE_ACE_TYPE(RectPaintMethod, ShapePaintMethod);
public:
    RectPaintMethod() = default;
    RectPaintMethod(
        const RefPtr<ShapePaintProperty>& shapePaintProperty,
        const RefPtr<ShapeOverlayModifier>& shapeOverlayModifier)
        : ShapePaintMethod(shapePaintProperty, shapeOverlayModifier)
    {}
    ~RectPaintMethod() override = default;
    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(paintWrapper, nullptr);
        auto rectPaintProperty = DynamicCast<RectPaintProperty>(paintWrapper->GetPaintProperty()->Clone());
        CHECK_NULL_RETURN(rectPaintProperty, nullptr);

        if (propertiesFromAncestor_) {
            if (!rectPaintProperty->HasFill() && propertiesFromAncestor_->HasFill()) {
                auto renderContext = paintWrapper->GetRenderContext();
                renderContext->UpdateForegroundColor(propertiesFromAncestor_->GetFillValue());
                renderContext->ResetForegroundColorStrategy();
            }
            rectPaintProperty->UpdateShapeProperty(propertiesFromAncestor_);
        }
        if (paintWrapper->HasForegroundColor()) {
            rectPaintProperty->UpdateFill(paintWrapper->GetForegroundColor());
        } else if (paintWrapper->HasForegroundColorStrategy()) {
            rectPaintProperty->UpdateFill(Color::FOREGROUND);
            rectPaintProperty->ResetFillOpacity();
        }
        rect_.SetSize(rectPaintProperty->GetContentSize());
        rect_.SetOffset(rectPaintProperty->GetContentOffset());

        return [rect = rect_, rectPaintProperty, paintWrapper](RSCanvas& canvas) {
                    RectPainter::DrawRect(canvas, rect, *rectPaintProperty);
                    if (paintWrapper) {
                        paintWrapper->FlushOverlayModifier();
                    }
                };
    }

private:
    RectF rect_;
    Radius topLeftRadius_;
    Radius topRightRadius_;
    Radius bottomLeftRadius_;
    Radius bottomRightRadius_;
    ACE_DISALLOW_COPY_AND_MOVE(RectPaintMethod);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SHAPE_RECT_PAINT_METHOD_H
