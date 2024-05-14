/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

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
        value->propBadgePosition_ = CloneBadgePosition();
        value->propBadgePositionX_ = CloneBadgePositionX();
        value->propBadgePositionY_ = CloneBadgePositionY();
        value->propIsPositionXy_ = CloneIsPositionXy();

        value->propBadgeColor_ = CloneBadgeColor();
        value->propBadgeTextColor_ = CloneBadgeTextColor();
        value->propBadgeTextColor_ = CloneBadgeBorderColor();
        value->propBadgeCircleSize_ = CloneBadgeCircleSize();
        value->propBadgeFontSize_ = CloneBadgeFontSize();
        value->propBadgeFontWeight_ = CloneBadgeFontWeight();
        value->propBadgeBorderWidth_ = CloneBadgeBorderWidth();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetBadgeValue();
        ResetBadgeCount();
        ResetBadgeMaxCount();
        ResetBadgePosition();
        ResetBadgePositionX();
        ResetBadgePositionY();
        ResetIsPositionXy();

        ResetBadgeColor();
        ResetBadgeTextColor();
        ResetBadgeBorderColor();
        ResetBadgeCircleSize();
        ResetBadgeFontSize();
        ResetBadgeFontWeight();
        ResetBadgeBorderWidth();
    }

    double GetBadgeCircleRadius() const
    {
        return badgeCircleRadius_;
    }

    void SetBadgeCircleRadius(const double& badgeCircleRadius)
    {
        badgeCircleRadius_ = badgeCircleRadius;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    std::string GetBadgePositionString(BadgePosition position) const
    {
        switch (position) {
            case BadgePosition::RIGHT_TOP:
                return "BadgePosition.RightTop";
            case BadgePosition::RIGHT:
                return "BadgePosition.Right";
            case BadgePosition::LEFT:
                return "BadgePosition.Left";
            default:
                break;
        }
        return "-";
    }

    void SetIsDefault(bool isDefaultFontSize, bool isDefaultBadgeSize)
    {
        isDefaultFontSize_ = isDefaultFontSize;
        isDefaultBadgeSize_ = isDefaultBadgeSize;
    }
    bool GetFontSizeIsDefault() const
    {
        return isDefaultFontSize_;
    }
    bool GetBadgeSizeIsDefault() const
    {
        return isDefaultBadgeSize_;
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgeValue, std::string, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgeCount, int, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgeMaxCount, int, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgePosition, BadgePosition, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgePositionX, Dimension, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgePositionY, Dimension, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsPositionXy, bool, PROPERTY_UPDATE_MEASURE_SELF);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgeColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgeTextColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgeBorderColor, Color, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgeFontSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgeCircleSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgeFontWeight, FontWeight, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BadgeBorderWidth, Dimension, PROPERTY_UPDATE_MEASURE);

private:
    double badgeCircleRadius_;
    bool isDefaultFontSize_;
    bool isDefaultBadgeSize_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_BADGE_BADGE_LAYOUT_PROPERTY_H
