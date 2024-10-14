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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_INDICATOR_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_INDICATOR_LAYOUT_PROPERTY_H

#include "base/geometry/dimension.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT LinearIndicatorLayoutProperty : public LinearLayoutProperty {
    DECLARE_ACE_TYPE(LinearIndicatorLayoutProperty, LinearLayoutProperty);

public:
    LinearIndicatorLayoutProperty();

    ~LinearIndicatorLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto copy = MakeRefPtr<LinearIndicatorLayoutProperty>();
        copy->LinearLayoutProperty::UpdateLayoutProperty(DynamicCast<LinearLayoutProperty>(this));
        copy->propStrokeWidth_ = CloneStrokeWidth();
        copy->propStrokeRadius_ = CloneStrokeRadius();
        copy->propTrackBackgroundColor_ = CloneTrackBackgroundColor();
        copy->propTrackColor_ = CloneTrackColor();
        copy->propLoop_ = CloneLoop();
        copy->propProgressCount_ = CloneProgressCount();
        return copy;
    }

    void Reset() override
    {
        LinearLayoutProperty::Reset();
        ResetStrokeWidth();
        ResetStrokeRadius();
        ResetTrackBackgroundColor();
        ResetTrackColor();
        ResetLoop();
        ResetProgressCount();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeWidth, Dimension, PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StrokeRadius, Dimension, PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TrackBackgroundColor, Color, PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(TrackColor, Color, PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Loop, bool, PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ProgressCount, std::size_t, PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    ACE_DISALLOW_COPY_AND_MOVE(LinearIndicatorLayoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LINEAR_INDICATOR_LAYOUT_PROPERTY_H
