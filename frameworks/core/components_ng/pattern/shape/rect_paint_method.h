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
#include "core/components_ng/pattern/shape/rect_paint_property.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/rect_painter.h"
namespace OHOS::Ace::NG {

class ACE_EXPORT RectPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(RectPaintMethod, NodePaintMethod)
public:
    RectPaintMethod() = default;
    ~RectPaintMethod() override = default;
    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override
    {
        auto rectPaintProperty = DynamicCast<RectPaintProperty>(paintWrapper->GetPaintProperty());
        rect_.SetSize(paintWrapper->GetContentSize());
        rect_.SetOffset(paintWrapper->GetContentOffset());
        if(rectPaintProperty->GetTopLeftRadius()){
            topLeftRadius_ = rectPaintProperty->GetTopLeftRadiusValue();
        }

        if(rectPaintProperty->GetTopRightRadius()){
            topRightRadius_ = rectPaintProperty->GetTopRightRadiusValue();
        }

        if(rectPaintProperty->GetBottomLeftRadius()){
            bottomLeftRadius_ = rectPaintProperty->GetBottomLeftRadiusValue();
        }

        if(rectPaintProperty->GetBottomRightRadius()){
            bottomRightRadius_ = rectPaintProperty->GetBottomRightRadiusValue();
        }
        return [rect = rect_, topLeftRadius = topLeftRadius_, topRightRadius = topRightRadius_,
                   bottomLeftRadius = bottomLeftRadius_, bottomRightRadius = bottomRightRadius_](RSCanvas& canvas) {
            RectPainter::DrawRect(canvas, rect, topLeftRadius, topRightRadius, bottomLeftRadius, bottomRightRadius);
        };
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(RectPaintMethod);
    Radius topLeftRadius_;
    Radius topRightRadius_;
    Radius bottomLeftRadius_;
    Radius bottomRightRadius_;
    RectF rect_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SHAPE_RECT_PAINT_METHOD_H