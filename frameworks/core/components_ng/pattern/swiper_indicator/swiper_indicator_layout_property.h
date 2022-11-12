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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_SWIPER_INDICATOR_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_SWIPER_INDICATOR_LAYOUT_PROPERTY_H

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components/declaration/swiper/swiper_declaration.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
struct IndicatorLayoutStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Left, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Top, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Right, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Bottom, Dimension);
};

class ACE_EXPORT SwiperIndicatorLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(SwiperIndicatorLayoutProperty, LayoutProperty);

public:
    SwiperIndicatorLayoutProperty() = default;

    ~SwiperIndicatorLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<SwiperIndicatorLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propIndicatorLayoutStyle_ = CloneIndicatorLayoutStyle();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetIndicatorLayoutStyle();
    }

    ACE_DEFINE_PROPERTY_GROUP(IndicatorLayoutStyle, IndicatorLayoutStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(IndicatorLayoutStyle, Left, Dimension, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(IndicatorLayoutStyle, Top, Dimension, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(IndicatorLayoutStyle, Right, Dimension, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(IndicatorLayoutStyle, Bottom, Dimension, PROPERTY_UPDATE_LAYOUT);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_SWIPER_INDICATOR_LAYOUT_PROPERTY_H
