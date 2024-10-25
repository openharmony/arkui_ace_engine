/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_SHAPE_CONTAINER_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_SHAPE_CONTAINER_PAINT_PROPERTY_H

#include <string>

#include "base/geometry/ng/image_mesh.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/pattern/shape/shape_view_box.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ShapeContainerPaintProperty : public ShapePaintProperty {
    DECLARE_ACE_TYPE(ShapeContainerPaintProperty, ShapePaintProperty);

public:
    ShapeContainerPaintProperty() = default;
    ~ShapeContainerPaintProperty() override = default;
    RefPtr<PaintProperty> Clone() const override
    {
        auto value = MakeRefPtr<ShapeContainerPaintProperty>();
        value->PaintProperty::UpdatePaintProperty(DynamicCast<PaintProperty>(this));
        value->propImageMesh_ = CloneImageMesh();
        value->propShapeViewBox_ = CloneShapeViewBox();
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
        value->propPixelMapInfo_ = ClonePixelMapInfo();
        return value;
    }

    void Reset() override
    {
        ShapePaintProperty::Reset();
        ResetImageMesh();
        ResetShapeViewBox();
        ResetPixelMapInfo();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        ShapePaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        auto viewBoxJson = JsonUtil::Create(true);
        if (propShapeViewBox_.has_value()) {
            viewBoxJson->Put("x", propShapeViewBox_.value().Left().ToString().c_str());
            viewBoxJson->Put("y", propShapeViewBox_.value().Top().ToString().c_str());
            viewBoxJson->Put("width", propShapeViewBox_.value().Width().ToString().c_str());
            viewBoxJson->Put("height", propShapeViewBox_.value().Height().ToString().c_str());
        }
        json->PutExtAttr("viewPort", viewBoxJson, filter);

        auto meshJson = JsonUtil::Create(true);
        if (propImageMesh_.has_value() && meshJson) {
            auto jsonValueArray = JsonUtil::CreateArray(true);
            std::vector<float> array = propImageMesh_->GetMesh();
            for (size_t i = 0; i < array.size(); i++) {
                auto index = std::to_string(i);
                auto value = std::to_string(array[i]);
                jsonValueArray->Put(index.c_str(), value.c_str());
            }
            meshJson->Put("value", jsonValueArray);
            meshJson->Put("row", propImageMesh_->GetRow());
            meshJson->Put("column", propImageMesh_->GetColumn());
        }
        json->PutExtAttr("mesh", meshJson, filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ImageMesh, ImageMesh, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShapeViewBox, ShapeViewBox, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PixelMapInfo, ImageSourceInfo, PROPERTY_UPDATE_RENDER);

private:
    ACE_DISALLOW_COPY_AND_MOVE(ShapeContainerPaintProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_SHAPE_CONTAINER_PAINT_PROPERTY_H
