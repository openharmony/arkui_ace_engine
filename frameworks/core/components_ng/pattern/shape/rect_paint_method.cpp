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

#include "core/components_ng/pattern/shape/rect_paint_method.h"

namespace OHOS::Ace::NG {

CanvasDrawFunction RectPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
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
                paintWrapper->FlushOverlayModifier();
            };
}
} // namespace OHOS::Ace::NG
