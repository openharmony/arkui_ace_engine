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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_POLYGON_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_POLYGON_PATTERN_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/shape/polygon_paint_method.h"
#include "core/components_ng/pattern/shape/shape_layout_algorithm.h"

namespace OHOS::Ace::NG {
class PolygonPattern : public Pattern {
    DECLARE_ACE_TYPE(PolygonPattern, Pattern);

public:
    PolygonPattern() = default;
    PolygonPattern(bool isPolygon):isPolygon_(isPolygon)
    {

    }
    ~PolygonPattern() override = default;

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto curFrameNode = GetHost();
        CHECK_NULL_RETURN(curFrameNode, nullptr);
        ShapePaintProperty propertiesFromAncestor;
        auto parentFrameNode = AceType::DynamicCast<FrameNode>(curFrameNode->GetAncestorNodeOfFrame());
        while (parentFrameNode) {
            auto parentPaintProperty = parentFrameNode->GetPaintProperty<ShapePaintProperty>();
            if (parentPaintProperty) {
                propertiesFromAncestor.UpdateShapeProperty(parentPaintProperty);
            }
            curFrameNode = parentFrameNode;
            parentFrameNode = AceType::DynamicCast<FrameNode>(curFrameNode->GetAncestorNodeOfFrame());
        }
        return MakeRefPtr<PolygonPaintMethod>(DynamicCast<ShapePaintProperty>(propertiesFromAncestor.Clone()), isPolygon_);
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<ShapeLayoutAlgorithm>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<PolygonPaintProperty>();
    }

private:
    bool isPolygon_;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout) override;
    ACE_DISALLOW_COPY_AND_MOVE(PolygonPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SHAPE_ELLIPSE_PATTERN_H