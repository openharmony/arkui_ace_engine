/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_CIRCLE_DOT_INDICATOR_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_CIRCLE_DOT_INDICATOR_PAINT_PROPERTY_H

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/paint_property.h"
#include "core/components/declaration/swiper/swiper_declaration.h"

namespace OHOS::Ace::NG {
struct CircleDotIndicatorStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ArcDirection, SwiperArcDirection);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Color, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectedColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ContainerColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(MaskColor, Gradient);
};
class CircleDotIndicatorPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(CircleDotIndicatorPaintProperty, PaintProperty);

public:
    CircleDotIndicatorPaintProperty() = default;
    ~CircleDotIndicatorPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<CircleDotIndicatorPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propCircleDotIndicatorStyle_ = CloneCircleDotIndicatorStyle();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetCircleDotIndicatorStyle();
    }
    ACE_DEFINE_PROPERTY_GROUP(CircleDotIndicatorStyle, CircleDotIndicatorStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        CircleDotIndicatorStyle, ArcDirection, SwiperArcDirection, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CircleDotIndicatorStyle, Color, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CircleDotIndicatorStyle, SelectedColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CircleDotIndicatorStyle, ContainerColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(CircleDotIndicatorStyle, MaskColor, Gradient, PROPERTY_UPDATE_RENDER);
    ACE_DISALLOW_COPY_AND_MOVE(CircleDotIndicatorPaintProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_CIRCLE_DOT_INDICATOR_PAINT_PROPERTY_H
