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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BADGE_BADGE_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BADGE_BADGE_LAYOUT_PROPERTY_H

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT BadgeLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(BadgeLayoutProperty, LayoutProperty);

public:
    BadgeLayoutProperty() = default;
    ~BadgeLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<BadgeLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(AceType::DynamicCast<LayoutProperty>(this));
        value->propBadgeValue_ = CloneBadgeValue();
        value->propBadgeCount_ = CloneBadgeCount();
        value->propBadgeMaxCount_ = CloneBadgeMaxCount();
        value->propBadgePosition_ = propBadgePosition_;

        value->propBadgeColor_ = CloneBadgeColor();
        value->propBadgeTextColor_ = CloneBadgeTextColor();
        value->propBadgeCircleSize_ = CloneBadgeCircleSize();
        value->propBadgeFontSize_ = CloneBadgeFontSize();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetBadgeValue();
        ResetBadgeCount();
        ResetBadgeMaxCount();
        propBadgePosition_ = BadgePosition::RIGHT_TOP;

        ResetBadgeColor();
        ResetBadgeTextColor();
        ResetBadgeCircleSize();
        ResetBadgeFontSize();
    }

    enum class BadgePosition {
        RIGHT_TOP = 0,
        RIGHT,
        LEFT,
    };

    BadgePosition& GetBadgePosition()
    {
        return propBadgePosition_;
    }

    void SetBadgePosition(const BadgePosition& position)
    {
        propBadgePosition_ = position;
    }

    double GetBadgeCircleRadius() const
    {
        return badgeCircleRadius_;
    }

    void SetBadgeCircleRadius(const double& badgeCircleRadius)
    {
        badgeCircleRadius_ = badgeCircleRadius;
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgeValue, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgeCount, int, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgeMaxCount, int, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgeColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgeTextColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgeFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgeCircleSize, Dimension, PROPERTY_UPDATE_MEASURE);

private:
    BadgePosition propBadgePosition_ = BadgePosition::RIGHT_TOP;

    double badgeCircleRadius_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BADGE_BADGE_LAYOUT_PROPERTY_H
