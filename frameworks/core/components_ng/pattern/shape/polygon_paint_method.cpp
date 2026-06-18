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

#include "core/components_ng/pattern/shape/polygon_paint_method.h"

namespace OHOS::Ace::NG {

CanvasDrawFunction PolygonPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    CHECK_NULL_RETURN(paintWrapper, nullptr);
    auto paintProperty = paintWrapper->GetPaintProperty();
    CHECK_NULL_RETURN(paintProperty, nullptr);
    auto shapePaintProperty = DynamicCast<PolygonPaintProperty>(paintProperty->Clone());
    CHECK_NULL_RETURN(shapePaintProperty, nullptr);

    if (propertiesFromAncestor_) {
        if (!shapePaintProperty->HasFill() && propertiesFromAncestor_->HasFill()) {
            auto renderContext = paintWrapper->GetRenderContext();
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
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    const auto& contentSize = geometryNode->GetContentSize();
    CHECK_EQUAL_RETURN(contentSize.IsPositive(), false, nullptr);
    return [shapePaintProperty, isClose = isClose_, paintWrapper](RSCanvas& canvas) {
                PolygonPainter::DrawPolygon(canvas, *shapePaintProperty, isClose);
                paintWrapper->FlushOverlayModifier();
            };
}
} // namespace OHOS::Ace::NG
