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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_LAYOUT_PROPERTY_H

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components/declaration/swiper/swiper_declaration.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SwiperLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(SwiperLayoutProperty, LayoutProperty);

public:
    SwiperLayoutProperty() = default;

    ~SwiperLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<SwiperLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propDirection_ = CloneDirection();
        value->propIndex_ = CloneIndex();
        value->propItemSpace_ = CloneItemSpace();
        value->propCachedCount_ = CloneCachedCount();
        value->propDisplayMode_ = CloneDisplayMode();
        value->propDisplayCount_ = CloneDisplayCount();
        value->propShowIndicator_ = CloneShowIndicator();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetDirection();
        ResetIndex();
        ResetItemSpace();
        ResetCachedCount();
        ResetDisplayMode();
        ResetDisplayCount();
        ResetShowIndicator();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        LayoutProperty::ToJsonValue(json);
        json->Put("index", std::to_string(propIndex_.value_or(0)).c_str());
        json->Put("vertical", propDirection_.value_or(Axis::HORIZONTAL) == Axis::VERTICAL ? "true" : "false");
        json->Put("indicator", propShowIndicator_.value_or(true) ? "true" : "false");
        json->Put("itemSpace", propItemSpace_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str());
        json->Put("cachedCount", propCachedCount_.value_or(1));
        json->Put("displayMode", propDisplayMode_.value_or(SwiperDisplayMode::STRETCH) == SwiperDisplayMode::AUTO_LINEAR
                                     ? "SwiperDisplayMode.AutoLinear"
                                     : "SwiperDisplayMode.Stretch");
        json->Put("displayCount", propDisplayCount_.value_or(1));
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Direction, Axis, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Index, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ItemSpace, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CachedCount, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DisplayMode, SwiperDisplayMode, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DisplayCount, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowIndicator, bool, PROPERTY_UPDATE_MEASURE);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_LAYOUT_PROPERTY_H
