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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_PATTERN_H

#include <cstddef>
#include <optional>

#include "base/geometry/ng/rect_t.h"
#include "base/log/log_wrapper.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/shape/container_paint_property.h"
#include "core/components_ng/pattern/shape/shape_layout_algorithm.h"
#include "core/components_ng/pattern/shape/shape_view_box.h"

namespace OHOS::Ace::NG {
class ShapePattern : public Pattern {
    DECLARE_ACE_TYPE(ShapePattern, Pattern);

public:
    ShapePattern() = default;
    ~ShapePattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<ShapeLayoutAlgorithm>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<ContainerPaintProperty>();
    }

    bool GetGeomeryFromRect() override
    {
        auto frameNode = GetHost();
        if (!frameNode) {
            return false;
        }
        auto containerProperty = frameNode->GetPaintProperty<ContainerPaintProperty>();
        if (!containerProperty) {
            return false;
        }
        auto shapeViewBoxOpt = containerProperty->CloneShapeViewBox();
        auto geoNode = frameNode->GetGeometryNode();
        if (!geoNode) {
            return false;
        }
        SizeF rectF = geoNode->GetContentSize();
        if (shapeViewBoxOpt.has_value() && shapeViewBoxOpt->IsValid()) {
            double viewBoxWidth = shapeViewBoxOpt->Width().ConvertToPx();
            double viedwBoxHeight = shapeViewBoxOpt->Height().ConvertToPx();
            double actualWidth = rectF.Width();
            double actualHeight = rectF.Height();
            if (viewBoxWidth < actualWidth || viedwBoxHeight < actualHeight) {
                return true;
            }
        }
        return false;
    }

    std::optional<RectF> GetGeomeryRectData() override
    {
        auto frameNode = GetHost();
        if (!frameNode) {
            return std::nullopt;
        }
        auto containerProperty = frameNode->GetPaintProperty<ContainerPaintProperty>();
        if (!containerProperty) {
            return std::nullopt;
        }
        auto shapeViewBoxOpt = containerProperty->CloneShapeViewBox();
        auto geoNode = frameNode->GetGeometryNode();
        if (!geoNode) {
            return std::nullopt;
        }
        SizeF rectF = geoNode->GetContentSize();
        OffsetF offsetF = geoNode->GetContentOffset();
        if (shapeViewBoxOpt.has_value() && shapeViewBoxOpt->IsValid()) {
            double viewBoxWidth = shapeViewBoxOpt->Width().ConvertToPx();
            double viewBoxHeight = shapeViewBoxOpt->Height().ConvertToPx();
            double actualWidth = rectF.Width();
            double actualHeight = rectF.Height();
            bool compareWithActualSize = false;
            if (Positive(actualWidth) && Positive(actualHeight)) {
                compareWithActualSize = true;
            }
            if (compareWithActualSize) {
                return RectF(offsetF.GetX() + shapeViewBoxOpt->Left().ConvertToPx(),
                    offsetF.GetY() + shapeViewBoxOpt->Top().ConvertToPx(), std::min(viewBoxWidth, actualWidth),
                    std::min(viewBoxHeight, actualHeight));
            } else {
                return RectF(offsetF.GetX() + shapeViewBoxOpt->Left().ConvertToPx(),
                    offsetF.GetY() + shapeViewBoxOpt->Top().ConvertToPx(), viewBoxWidth, viewBoxHeight);
            }
        }
        return std::nullopt;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

private:
    void ViewPortTansfer();
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
    ACE_DISALLOW_COPY_AND_MOVE(ShapePattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_PATTERN_H