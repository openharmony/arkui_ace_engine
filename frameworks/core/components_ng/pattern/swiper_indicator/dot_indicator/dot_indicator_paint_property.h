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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_DOT_INDICATOR_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_DOT_INDICATOR_PAINT_PROPERTY_H

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
struct DotIndicatorStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Size, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ItemWidth, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(ItemHeight, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectedItemWidth, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectedItemHeight, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Space, Dimension);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(IndicatorMask, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Color, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(SelectedColor, Color);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(IsCustomSize, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(IgnoreSize, bool);
};
class DotIndicatorPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(DotIndicatorPaintProperty, PaintProperty);

public:
    DotIndicatorPaintProperty() = default;
    ~DotIndicatorPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<DotIndicatorPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propDotIndicatorStyle_ = CloneDotIndicatorStyle();
        paintProperty->propIsCustomSize_ = CloneIsCustomSize();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetDotIndicatorStyle();
        ResetIsCustomSize();
    }
    ACE_DEFINE_PROPERTY_GROUP(DotIndicatorStyle, DotIndicatorStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(DotIndicatorStyle, Size, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(DotIndicatorStyle, ItemWidth, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(DotIndicatorStyle, ItemHeight, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(DotIndicatorStyle, SelectedItemWidth, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(DotIndicatorStyle, SelectedItemHeight, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(DotIndicatorStyle, Space, Dimension, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(DotIndicatorStyle, IndicatorMask, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(DotIndicatorStyle, Color, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(DotIndicatorStyle, SelectedColor, Color, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(DotIndicatorStyle, IgnoreSize, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(IsCustomSize, bool, PROPERTY_UPDATE_RENDER);
  
    ACE_DISALLOW_COPY_AND_MOVE(DotIndicatorPaintProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_DOT_INDICATOR_PAINT_PROPERTY_H
