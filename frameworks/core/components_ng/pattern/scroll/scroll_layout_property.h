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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_LAYOUT_PROPERTY_H

#include <memory>
#include <unordered_map>

#include "base/geometry/axis.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ScrollLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(ScrollLayoutProperty, LayoutProperty);

public:
    ScrollLayoutProperty() = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<ScrollLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propAxis_ = CloneAxis();
        value->propBarWidth_ = CloneBarWidth();
        value->propEdgeEffect_ = CloneEdgeEffect();
        value->propScrollEnabled_ = CloneScrollEnabled();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetAxis();
        ResetEdgeEffect();
        ResetScrollEnabled();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override
    {
        LayoutProperty::ToJsonValue(json);
        std::unordered_map<Axis, std::string> scrollableMap { { Axis::VERTICAL, "ScrollDirection.Vertical" },
            { Axis::HORIZONTAL, "ScrollDirection.Horizontal" }, { Axis::FREE, "ScrollDirection.Free" },
            { Axis::NONE, "ScrollDirection.None" } };
        Axis axis = GetAxisValue(Axis::VERTICAL);
        json->Put("scrollable", scrollableMap[axis].c_str());
        std::unordered_map<EdgeEffect, std::string> edgeEffectMap { { EdgeEffect::SPRING, "EdgeEffect.Spring" },
            { EdgeEffect::FADE, "EdgeEffect.Fade" }, { EdgeEffect::NONE, "EdgeEffect.None" } };
        EdgeEffect edgeEffect = propEdgeEffect_.value_or(EdgeEffect::NONE);
        json->Put("edgeEffect", edgeEffectMap[edgeEffect].c_str());
        json->Put("enableScrollInteraction", propScrollEnabled_.value_or(true));
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Axis, Axis, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BarWidth, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EdgeEffect, EdgeEffect, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollEnabled, bool, PROPERTY_UPDATE_MEASURE);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_LAYOUT_PROPERTY_H
