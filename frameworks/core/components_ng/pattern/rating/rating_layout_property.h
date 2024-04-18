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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_LAYOUT_PROPERTY_H

#include <string>

#include "base/geometry/dimension.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/rating/rating_property_group.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class ACE_EXPORT RatingLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(RatingLayoutProperty, LayoutProperty);

public:
    RatingLayoutProperty() = default;

    ~RatingLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<RatingLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propRatingPropertyGroup_ = CloneRatingPropertyGroup();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetRatingPropertyGroup();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        ACE_PROPERTY_TO_JSON_VALUE(propRatingPropertyGroup_, RatingPropertyGroup);
    }

    ACE_DEFINE_PROPERTY_GROUP(RatingPropertyGroup, RatingPropertyGroup);

    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(RatingPropertyGroup, Indicator, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(RatingPropertyGroup, Stars, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        RatingPropertyGroup, ForegroundImageSourceInfo, ImageSourceInfo, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        RatingPropertyGroup, SecondaryImageSourceInfo, ImageSourceInfo, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        RatingPropertyGroup, BackgroundImageSourceInfo, ImageSourceInfo, PROPERTY_UPDATE_MEASURE);

private:
    ACE_DISALLOW_COPY_AND_MOVE(RatingLayoutProperty);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RATING_RATING_LAYOUT_PROPERTY_H
