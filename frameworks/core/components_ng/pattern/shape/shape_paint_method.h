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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_PAINT_METHOD_H

#include "base/geometry/ng/size_t.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/pattern/shape/shape_overlay_modifier.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/render/node_paint_method.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ShapePaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(ShapePaintMethod, NodePaintMethod);
public:
    ShapePaintMethod() = default;
    ShapePaintMethod(
        const RefPtr<ShapePaintProperty>& shapePaintProperty,
        const RefPtr<ShapeOverlayModifier>& shapeOverlayModifier)
        : propertiesFromAncestor_(shapePaintProperty), shapeOverlayModifier_(shapeOverlayModifier)
    {}
    ~ShapePaintMethod() override = default;

    RefPtr<Modifier> GetOverlayModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(paintWrapper, nullptr);
        CHECK_NULL_RETURN(shapeOverlayModifier_, nullptr);
        auto shapePaintProperty = DynamicCast<ShapePaintProperty>(paintWrapper->GetPaintProperty()->Clone());
        CHECK_NULL_RETURN(shapePaintProperty, nullptr);
        auto renderContext = paintWrapper->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, nullptr);

        auto offset = paintWrapper->GetContentOffset();
        float width = paintWrapper->GetContentSize().Width();
        float height = paintWrapper->GetContentSize().Height();
        float deltaWidth = shapePaintProperty->HasStrokeWidth()
                               ? ShapeOverlayModifier::SHAPE_OVERLAY_SIZE_FACTOR *
                                     shapePaintProperty->GetStrokeWidthValue().ConvertToPx()
                               : ShapeOverlayModifier::SHAPE_OVERLAY_SIZE_DEFAULT;
        auto scale = renderContext->GetTransformScaleValue({ 1.0f, 1.0f });
        RectF rect { 0.0f, 0.0f, 0.0f, 0.0f };
        static const double diff = 1e-10;
        if (!NearZero(scale.x, diff) && !NearZero(scale.y, diff)) {
            rect = { offset.GetX() - deltaWidth, offset.GetY() - deltaWidth, (width + deltaWidth * 2) / scale.x,
                (height + deltaWidth * 2) / scale.y };
        }
        shapeOverlayModifier_->SetBoundsRect(rect);
        return shapeOverlayModifier_;
    }

protected:
    RefPtr<ShapePaintProperty> propertiesFromAncestor_;
    RefPtr<ShapeOverlayModifier> shapeOverlayModifier_;
    ACE_DISALLOW_COPY_AND_MOVE(ShapePaintMethod);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_PAINT_METHOD_H
