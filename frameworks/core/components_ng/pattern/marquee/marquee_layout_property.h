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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MARQUEE_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MARQUEE_LAYOUT_PROPERTY_H

#include <string>

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT MarqueeLayoutProperty final : public LayoutProperty {
    DECLARE_ACE_TYPE(MarqueeLayoutProperty, LayoutProperty);

public:
    MarqueeLayoutProperty() = default;

    ~MarqueeLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<MarqueeLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propPlayerStatus_ = ClonePlayerStatus();
        value->propScrollAmount_ = CloneScrollAmount();
        value->propDirection_ = CloneDirection();
        value->propLoop_ = CloneLoop();
        value->propAllowScale_ = CloneAllowScale();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetPlayerStatus();
        ResetScrollAmount();
        ResetDirection();
        ResetLoop();
        ResetAllowScale();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PlayerStatus, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollAmount, double, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Loop, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Direction, MarqueeDirection, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(AllowScale, bool, PROPERTY_UPDATE_MEASURE);

private:
    ACE_DISALLOW_COPY_AND_MOVE(MarqueeLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MARQUEE_LAYOUT_PROPERTY_H
