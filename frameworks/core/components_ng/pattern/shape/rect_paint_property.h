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

#include "base/geometry/dimension.h"
#include "base/geometry/ng/radius.h"
#include "base/log/log_wrapper.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
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

    void UpdateRadius(std ::optional<Radius>& radiusOpt, const Radius& value)
    {
        if (!value.GetX().IsValid() && !value.GetY().IsValid()) {
            return;
        }
        bool update = false;
        if (!radiusOpt.has_value()) {
            radiusOpt = value; // value
            update = true;
        } else {
            if (value.GetX().IsValid() && !NearEqual(radiusOpt.value_or(Radius()).GetX(), value.GetX())) {
                radiusOpt->SetX(value.GetX());
                update = true;
            }
            if (value.GetY().IsValid() && !NearEqual(radiusOpt.value_or(Radius()).GetY(), value.GetY())) {
                radiusOpt->SetY(value.GetY());
                update = true;
            }
        }
        if (update) {
            UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);
        }
    }

private:
    std::optional<Radius> propTopLeftRadius_;
    std::optional<Radius> propTopRightRadius_;
    std::optional<Radius> propBottomLeftRadius_;
    std::optional<Radius> propBottomRightRadius_;

    ACE_DISALLOW_COPY_AND_MOVE(RectPaintProperty);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_RECT_PAINT_PROPERTY_H