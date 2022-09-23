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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_PAINT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ShapePaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(ShapePaintProperty, PaintProperty);

public:
    const double FILL_OPACITY_DEFAULT = 1.0f;
    const double STOKE_MITERLIMIT_DEFAULT = 4.0f;
    const double STOKE_OPACITY_DEFAULT = 1.0f;
    const Dimension STOKE_WIDTH_DEFAULT = Dimension(1.0f);
    const bool ANTIALIAS_DEFAULT = true;
    const int SQUARE_CAP = 2;

    ShapePaintProperty() = default;
    ~ShapePaintProperty() override = default;
    RefPtr<PaintProperty> Clone() const override
    {
        auto value = MakeRefPtr<ShapePaintProperty>();
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
        PaintProperty::Reset();
        ResetAntiAlias();
        ResetFill();
        ResetFillOpacity();
        ResetStroke();
        ResetStrokeWidth();
        ResetStrokeDashArray();
        ResetStrokeDashOffset();
        ResetStrokeLineCap();
        ResetStrokeLineJoin();
        ResetStrokeMiterLimit();
        ResetStrokeOpacity();
    }

    void UpdateShapeProperty(const RefPtr<ShapePaintProperty>& target);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Fill, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FillOpacity, double, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Stroke, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeDashArray, std::vector<Ace::Dimension>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeDashOffset, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeLineCap, int, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeLineJoin, int, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeMiterLimit, double, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeOpacity, double, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeWidth, Ace::Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(AntiAlias, bool, PROPERTY_UPDATE_RENDER);

private:
    ACE_DISALLOW_COPY_AND_MOVE(ShapePaintProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_PAINT_PROPERTY_H