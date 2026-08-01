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

#include <array>
#include <string>
#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ShapePaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(ShapePaintProperty, PaintProperty);

public:
    static constexpr double FILL_OPACITY_DEFAULT = 1.0f;
    static constexpr double STROKE_MITERLIMIT_DEFAULT = 4.0f;
    static constexpr double STROKE_MITERLIMIT_MIN = 1.0f;
    static constexpr double STROKE_OPACITY_DEFAULT = 1.0f;
    static constexpr Dimension STROKE_WIDTH_DEFAULT = 1.0_vp;
    static constexpr bool ANTIALIAS_DEFAULT = true;
    static constexpr int SQUARE_CAP = 2;
    static constexpr int DEFAULT_LINE_JOIN=0;

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

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("stroke", propStroke_.value_or(Color::BLACK).ColorToString().c_str(), filter);
        json->PutExtAttr("strokeWidth", propStrokeWidth_.value_or(Dimension()).ConvertToPx(), filter);
        json->PutExtAttr("strokeOpacity",
            std::to_string(propStrokeOpacity_.value_or(STROKE_OPACITY_DEFAULT)).c_str(), filter);
        json->PutExtAttr("strokeDashOffset",
            propStrokeDashOffset_.value_or(Dimension()).ToString().c_str(), filter);

        auto jsonDashArray = JsonUtil::CreateArray(true);
        std::vector<Dimension> array = propStrokeDashArray_.value_or(std::vector<Dimension>());
        for (size_t i = 0; i < array.size(); i++) {
            auto index = std::to_string(i);
            auto value = array[i].ToString();
            jsonDashArray->Put(index.c_str(), value.c_str());
        }
        json->PutExtAttr("strokeDashArray", jsonDashArray, filter);

        std::array<std::string, 3> lineCap = { "LineCapStyle.Butt", "LineCapStyle.Round", "LineCapStyle.Square" };
        json->PutExtAttr("strokeLineCap", lineCap.at(propStrokeLineCap_.value_or(0) % 3).c_str(), filter);
        std::array<std::string, 3> lineJoin = { "LineJoinStyle.Miter", "LineJoinStyle.Round", "LineJoinStyle.Bevel" };
        json->PutExtAttr("strokeLineJoin", lineJoin.at(propStrokeLineJoin_.value_or(0) % 3).c_str(), filter);
        json->PutExtAttr("strokeMiterLimit",
            std::to_string(propStrokeMiterLimit_.value_or(STROKE_MITERLIMIT_DEFAULT)).c_str(), filter);
        json->PutExtAttr("fill", propFill_.value_or(Color::BLACK).ColorToString().c_str(), filter);
        json->PutExtAttr("fillOpacity",
            std::to_string(propFillOpacity_.value_or(FILL_OPACITY_DEFAULT)).c_str(), filter);
        json->PutExtAttr("antiAlias", propAntiAlias_.value_or(ANTIALIAS_DEFAULT) ? "true" : "false", filter);
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
