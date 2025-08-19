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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_PAINT_PROPERTY_H

#include "core/animation/curve.h"
#include "core/animation/curves.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

struct SwiperAnimationStyle {
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AutoPlay, bool);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(AutoPlayInterval, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Duration, int32_t);
    ACE_DEFINE_PROPERTY_GROUP_ITEM(Curve, RefPtr<Curve>);

    static const int32_t DEFAULT_INTERVAL;
    static const int32_t DEFAULT_DURATION;
};

class SwiperPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(SwiperPaintProperty, PaintProperty);

public:
    SwiperPaintProperty() = default;
    ~SwiperPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<SwiperPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propSwiperAnimationStyle_ = CloneSwiperAnimationStyle();
        paintProperty->propEnabled_ = CloneEnabled();
        paintProperty->propEdgeEffect_ = CloneEdgeEffect();
        paintProperty->propFadeColor_ = CloneFadeColor();
        return paintProperty;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetSwiperAnimationStyle();
        ResetEnabled();
        ResetEdgeEffect();
        ResetFadeColor();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    void FromJson(const std::unique_ptr<JsonValue>& json) override;

    ACE_DEFINE_PROPERTY_GROUP(SwiperAnimationStyle, SwiperAnimationStyle);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwiperAnimationStyle, AutoPlay, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwiperAnimationStyle, AutoPlayInterval, int32_t, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwiperAnimationStyle, Duration, int32_t, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(SwiperAnimationStyle, Curve, RefPtr<Curve>, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Enabled, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EdgeEffect, EdgeEffect, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(FadeColor, Color, PROPERTY_UPDATE_RENDER);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_SWIPER_PAINT_PROPERTY_H
