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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_SWIPER_INDICATOR_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_SWIPER_INDICATOR_PAINT_PROPERTY_H

#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
struct IndicatorStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Size, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(IndicatorMask, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Color, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectedColor, Color);
};
class SwiperIndicatorPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(SwiperIndicatorPaintProperty, PaintProperty)

public:
    SwiperIndicatorPaintProperty() = default;
    ~SwiperIndicatorPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<SwiperIndicatorPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propIndicatorStyle_ = CloneIndicatorStyle();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetIndicatorStyle();
    }

    ACE_DEFINE_PROPERTY_GROUP(IndicatorStyle, IndicatorStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(IndicatorStyle, Size, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(IndicatorStyle, IndicatorMask, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(IndicatorStyle, Color, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(IndicatorStyle, SelectedColor, Color, PROPERTY_UPDATE_RENDER);

    ACE_DISALLOW_COPY_AND_MOVE(SwiperIndicatorPaintProperty);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_SWIPER_INDICATOR_PAINT_PROPERTY_H
