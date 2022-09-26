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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_GROUP_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_GROUP_PAINT_PROPERTY_H

#include <string>

#include "base/geometry/ng/image_mesh.h"
#include "core/components/shape/shape_component.h"
#include "core/components/shape/shape_container_component.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/shape/shape_group_view.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ShapegroupPaintProperty : public ShapePaintProperty {
    DECLARE_ACE_TYPE(ShapegroupPaintProperty, ShapePaintProperty);

public:
    ShapegroupPaintProperty() = default;
    ~ShapegroupPaintProperty() override = default;
    RefPtr<PaintProperty> Clone() const override
    {
        auto value = MakeRefPtr<ShapegroupPaintProperty>();
        value->PaintProperty::UpdatePaintProperty(DynamicCast<PaintProperty>(this));
        value->propFill_ = CloneFill();
        value->propFillOpacity_ = CloneFillOpacity();
        value->propStroke_ = CloneStroke();
        value->propStrokeWidth_ = CloneStrokeWidth();
        value->propStrokeOpacity_ = CloneStrokeOpacity();
        value->propStrokeDashArray_ = CloneStrokeDashArray();
        value->propStrokeDashOffset_ = CloneStrokeDashOffset();
        value->propStrokeLineCap_ = CloneStrokeLineCap();
        value->propStrokeLineJoin_ = CloneStrokeLineJoin();
        value->propStrokeMiterLimit_ = CloneStrokeMiterLimit();
        value->propAntiAlias_ = CloneAntiAlias();
        return value;
    }

    void Reset() override
    {
        ShapePaintProperty::Reset();
    }

    //ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ImageMesh, ImageMesh, PROPERTY_UPDATE_RENDER);
   // ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ViewPort,ShapeViewBox, PROPERTY_UPDATE_RENDER);

private:
    ACE_DISALLOW_COPY_AND_MOVE(ShapegroupPaintProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_GROUP_PAINT_PROPERTY_H