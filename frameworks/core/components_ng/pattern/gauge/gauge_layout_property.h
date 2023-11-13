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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_LAYOUT_PROPERTY_H

#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT GaugeLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(GaugeLayoutProperty, LayoutProperty);

public:
    GaugeLayoutProperty() = default;
    ~GaugeLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<GaugeLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propIsShowLimitValue_ = CloneIsShowLimitValue();
        value->propIsShowDescription_ = CloneIsShowDescription();
        value->propStrokeWidth_ = CloneStrokeWidth();
        value->propStartAngle_ = CloneStartAngle();
        value->propEndAngle_ = CloneEndAngle();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetIsShowLimitValue();
        ResetIsShowDescription();
        ResetStrokeWidth();
        ResetStartAngle();
        ResetEndAngle();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsShowLimitValue, bool, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsShowDescription, bool, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeWidth, Dimension, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StartAngle, float, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EndAngle, float, PROPERTY_UPDATE_MEASURE_SELF);

private:
    ACE_DISALLOW_COPY_AND_MOVE(GaugeLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GAUGE_GAUGE_LAYOUT_PROPERTY_H
