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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_SWIPER_ARROW_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_SWIPER_ARROW_LAYOUT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SwiperArrowLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(SwiperArrowLayoutProperty, LayoutProperty);

public:
    SwiperArrowLayoutProperty() = default;

    ~SwiperArrowLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<SwiperArrowLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propDirection_ = CloneDirection();
        value->propIndex_ = CloneIndex();
        value->propLoop_ = CloneLoop();
        value->propEnabled_ = CloneEnabled();
        value->propDisplayArrow_ = CloneDisplayArrow();
        value->propHoverShow_ = CloneHoverShow();
        value->propIsShowBackground_ = CloneIsShowBackground();
        value->propIsSidebarMiddle_ = CloneIsSidebarMiddle();
        value->propBackgroundSize_ = CloneBackgroundSize();
        value->propBackgroundColor_ = CloneBackgroundColor();
        value->propArrowSize_ = CloneArrowSize();
        value->propArrowColor_ = CloneArrowColor();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetDirection();
        ResetIndex();
        ResetLoop();
        ResetEnabled();
        ResetDisplayArrow();
        ResetHoverShow();
        ResetIsShowBackground();
        ResetIsSidebarMiddle();
        ResetBackgroundSize();
        ResetBackgroundColor();
        ResetArrowSize();
        ResetArrowColor();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Direction, Axis, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Index, int32_t, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Loop, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Enabled, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DisplayArrow, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(HoverShow, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsShowBackground, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsSidebarMiddle, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BackgroundColor, Color, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ArrowSize, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ArrowColor, Color, PROPERTY_UPDATE_NORMAL);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_SWIPER_INDICATOR_LAYOUT_PROPERTY_H
