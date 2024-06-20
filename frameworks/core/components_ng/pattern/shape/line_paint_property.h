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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_LINE_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_LINE_PAINT_PROPERTY_H

#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {

using ShapePoint = std::pair<Dimension, Dimension>;

class ACE_EXPORT LinePaintProperty : public ShapePaintProperty {
    DECLARE_ACE_TYPE(LinePaintProperty, ShapePaintProperty);

public:
    LinePaintProperty() = default;
    ~LinePaintProperty() override = default;
    RefPtr<PaintProperty> Clone() const override
    {
        auto value = MakeRefPtr<LinePaintProperty>();
        value->PaintProperty::UpdatePaintProperty(DynamicCast<PaintProperty>(this));
        value->propStartPoint_ = CloneStartPoint();
        value->propEndPoint_ = CloneEndPoint();
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
        ResetStartPoint();
        ResetEndPoint();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        ShapePaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        if (propStartPoint_.has_value()) {
            auto startPointArray = JsonUtil::CreateArray(true);
            startPointArray->Put("0", propStartPoint_.value().first.Value());
            startPointArray->Put("1", propStartPoint_.value().second.Value());
            json->PutExtAttr("startPoint", startPointArray, filter);
        }
        if (propEndPoint_.has_value()) {
            auto endPointArray = JsonUtil::CreateArray(true);
            endPointArray->Put("0", propEndPoint_.value().first.Value());
            endPointArray->Put("1", propEndPoint_.value().second.Value());
            json->PutExtAttr("endPoint", endPointArray, filter);
        }
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StartPoint, ShapePoint, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EndPoint, ShapePoint, PROPERTY_UPDATE_RENDER);

private:
    ACE_DISALLOW_COPY_AND_MOVE(LinePaintProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_LINE_PAINT_PROPERTY_H
