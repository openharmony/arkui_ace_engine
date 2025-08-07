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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_RECT_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_RECT_PAINT_PROPERTY_H

#include <vector>
#include "base/geometry/dimension.h"
#include "base/geometry/ng/radius.h"
#include "base/log/log_wrapper.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
namespace {
// Dimension(0) will update radius, but Dimension(-1) will not.
const Dimension DEFAULT_RADIUS_VALUE(0, DimensionUnit::PX);
const Dimension DEFAULT_RADIUS_INVALID(-1, DimensionUnit::PX);
} // namespace
class ACE_EXPORT RectPaintProperty : public ShapePaintProperty {
    DECLARE_ACE_TYPE(RectPaintProperty, ShapePaintProperty);

public:
    RectPaintProperty() = default;
    ~RectPaintProperty() override = default;
    RefPtr<PaintProperty> Clone() const override
    {
        auto value = MakeRefPtr<RectPaintProperty>();
        value->PaintProperty::UpdatePaintProperty(DynamicCast<PaintProperty>(this));
        value->propTopLeftRadius_ = CloneTopLeftRadius();
        value->propTopRightRadius_ = CloneTopRightRadius();
        value->propBottomLeftRadius_ = CloneBottomLeftRadius();
        value->propBottomRightRadius_ = CloneBottomRightRadius();
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
        value->SetContentOffset(contentOffset_);
        value->SetContentSize(contentSize_);
        return value;
    }

    void Reset() override
    {
        ShapePaintProperty::Reset();
        ResetBottomLeftRadius();
        ResetBottomRightRadius();
        ResetTopLeftRadius();
        ResetTopRightRadius();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        ShapePaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        if (!propTopLeftRadius_.has_value() || !propTopRightRadius_.has_value() || !propBottomLeftRadius_.has_value() ||
            !propBottomRightRadius_.has_value()) {
            return;
        }
        std::vector<std::vector<double>> radiusArray(4);
        radiusArray[0] = { propTopLeftRadius_.value().GetX().ConvertToPx(),
            propTopLeftRadius_.value().GetY().ConvertToPx() };
        radiusArray[1] = { propTopRightRadius_.value().GetX().ConvertToPx(),
            propTopRightRadius_.value().GetY().ConvertToPx() };
        radiusArray[2] = { propBottomRightRadius_.value().GetX().ConvertToPx(),
            propBottomRightRadius_.value().GetY().ConvertToPx() };
        radiusArray[3] = { propBottomLeftRadius_.value().GetX().ConvertToPx(),
            propBottomLeftRadius_.value().GetY().ConvertToPx() };
        json->PutExtAttr("radius", radiusArray.data(), filter);
        if (radiusArray[0][0] == radiusArray[1][0] &&
            radiusArray[0][0] == radiusArray[2][0] &&
            radiusArray[0][0] == radiusArray[3][0]) {
            json->PutExtAttr("radiusWidth", radiusArray[0][0], filter);
        } else {
            json->PutExtAttr("radiusWidth", 0, filter);
        }
        if (radiusArray[0][1] == radiusArray[1][1] &&
            radiusArray[0][1] == radiusArray[2][1] &&
            radiusArray[0][1] == radiusArray[3][1]) {
            json->PutExtAttr("radiusHeight", radiusArray[0][1], filter);
        } else {
            json->PutExtAttr("radiusHeight", 0, filter);
        }
    }

    const std::optional<Radius>& GetTopLeftRadius()
    {
        return propTopLeftRadius_;
    }
    bool HasTopLeftRadius() const
    {
        return propTopLeftRadius_.has_value();
    }
    const Radius& GetTopLeftRadiusValue() const
    {
        return propTopLeftRadius_.value();
    }
    const std::optional<Radius>& CloneTopLeftRadius() const
    {
        return propTopLeftRadius_;
    }
    void ResetTopLeftRadius()
    {
        return propTopLeftRadius_.reset();
    }

    void UpdateTopLeftRadius(const Radius& value)
    {
        UpdateRadius(propTopLeftRadius_, value);
    }

    const std::optional<Radius>& GetTopRightRadius()
    {
        return propTopRightRadius_;
    }
    bool HasTopRightRadius() const
    {
        return propTopRightRadius_.has_value();
    }
    const Radius& GetTopRightRadiusValue() const
    {
        return propTopRightRadius_.value();
    }
    const std::optional<Radius>& CloneTopRightRadius() const
    {
        return propTopRightRadius_;
    }
    void ResetTopRightRadius()
    {
        return propTopRightRadius_.reset();
    }

    void UpdateTopRightRadius(const Radius& value)
    {
        UpdateRadius(propTopRightRadius_, value);
    }

    const std::optional<Radius>& GetBottomRightRadius()
    {
        return propBottomRightRadius_;
    }
    bool HasBottomRightRadius() const
    {
        return propBottomRightRadius_.has_value();
    }
    const Radius& GetBottomRightRadiusValue() const
    {
        return propBottomRightRadius_.value();
    }
    const std::optional<Radius>& CloneBottomRightRadius() const
    {
        return propBottomRightRadius_;
    }
    void ResetBottomRightRadius()
    {
        return propBottomRightRadius_.reset();
    }

    void UpdateBottomRightRadius(const Radius& value)
    {
        UpdateRadius(propBottomRightRadius_, value);
    }

    const std::optional<Radius>& GetBottomLeftRadius()
    {
        return propBottomLeftRadius_;
    }
    bool HasBottomLeftRadius() const
    {
        return propBottomLeftRadius_.has_value();
    }
    const Radius& GetBottomLeftRadiusValue() const
    {
        return propBottomLeftRadius_.value();
    }
    const std::optional<Radius>& CloneBottomLeftRadius() const
    {
        return propBottomLeftRadius_;
    }
    void ResetBottomLeftRadius()
    {
        return propBottomLeftRadius_.reset();
    }
    void UpdateBottomLeftRadius(const Radius& value)
    {
        UpdateRadius(propBottomLeftRadius_, value);
    }

    void UpdateRadius(const Radius& value)
    {
        UpdateRadius(propTopLeftRadius_, value);
        UpdateRadius(propTopRightRadius_, value);
        UpdateRadius(propBottomLeftRadius_, value);
        UpdateRadius(propBottomRightRadius_, value);
    }

    void UpdateRadius(std::optional<Radius>& radiusOpt, const Radius& value)
    {
        // Dimension(0) is a valid value in radius.
        if (!value.GetX().IsNonNegative() && !value.GetY().IsNonNegative()) {
            return;
        }
        bool update = false;
        if (!radiusOpt.has_value()) {
            radiusOpt = value; // value
            update = true;
        } else {
            if (value.GetX().IsNonNegative() && !NearEqual(radiusOpt.value_or(Radius()).GetX(), value.GetX())) {
                radiusOpt->SetX(value.GetX());
                update = true;
            }
            if (value.GetY().IsNonNegative() && !NearEqual(radiusOpt.value_or(Radius()).GetY(), value.GetY())) {
                radiusOpt->SetY(value.GetY());
                update = true;
            }
        }
        if (update) {
            UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);
        }
    }

    OffsetF GetContentOffset()
    {
        return contentOffset_;
    }

    SizeF GetContentSize()
    {
        return contentSize_;
    }

    void SetContentOffset(const OffsetF& contentOffset)
    {
        contentOffset_.SetX(contentOffset.GetX());
        contentOffset_.SetY(contentOffset.GetY());
    }

    void SetContentSize(const SizeF& contentSize)
    {
        contentSize_.SetSizeT(contentSize);
    }

private:
    std::optional<Radius> propTopLeftRadius_;
    std::optional<Radius> propTopRightRadius_;
    std::optional<Radius> propBottomLeftRadius_;
    std::optional<Radius> propBottomRightRadius_;
    SizeF contentSize_;
    OffsetF contentOffset_;

    ACE_DISALLOW_COPY_AND_MOVE(RectPaintProperty);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_RECT_PAINT_PROPERTY_H
