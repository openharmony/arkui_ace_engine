/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MARQUEE_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MARQUEE_PAINT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
constexpr Dimension DEFAULT_MARQUEE_SCROLL_AMOUNT = 6.0_vp;
class ACE_EXPORT MarqueePaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(MarqueePaintProperty, PaintProperty);

public:
    MarqueePaintProperty() = default;

    ~MarqueePaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto value = MakeRefPtr<MarqueePaintProperty>();
        value->PaintProperty::UpdatePaintProperty(this);
        value->propPlayerStatus_ = ClonePlayerStatus();
        value->propScrollAmount_ = CloneScrollAmount();
        value->propDirection_ = CloneDirection();
        value->propLoop_ = CloneLoop();
        return value;
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetPlayerStatus();
        ResetScrollAmount();
        ResetDirection();
        ResetLoop();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        PaintProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("step",
            std::to_string(propScrollAmount_.value_or(DEFAULT_MARQUEE_SCROLL_AMOUNT.ConvertToPx())).c_str(), filter);
        json->PutExtAttr("loop", std::to_string(propLoop_.value_or(-1)).c_str(), filter);
        json->PutExtAttr("start", propPlayerStatus_.value_or(true) ? "true" : "false", filter);
        json->PutExtAttr("fromStart",
            propDirection_.value_or(MarqueeDirection::RIGHT) == MarqueeDirection::LEFT ? "true" : "false", filter);
    }
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(PlayerStatus, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollAmount, double, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Loop, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Direction, MarqueeDirection, PROPERTY_UPDATE_MEASURE);

private:
    ACE_DISALLOW_COPY_AND_MOVE(MarqueePaintProperty);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MARQUEE_PAINT_PROPERTY_H
