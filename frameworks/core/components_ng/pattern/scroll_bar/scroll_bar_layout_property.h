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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_BAR_SCROLL_BAR_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_BAR_SCROLL_BAR_LAYOUT_PROPERTY_H

#include "base/geometry/axis.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ScrollBarLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(ScrollBarLayoutProperty, LayoutProperty);

public:
    ScrollBarLayoutProperty() = default;
    ~ScrollBarLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<ScrollBarLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propAxis_ = CloneAxis();
        value->propDisplayMode_ = CloneDisplayMode();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetAxis();
        ResetDisplayMode();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        std::unordered_map<Axis, std::string> directionMap = {
            { Axis::VERTICAL, "ScrollBarDirection.Vertical" },
            { Axis::HORIZONTAL, "ScrollBarDirection.Horizontal" }
            };
        std::unordered_map<DisplayMode, std::string> stateMap = {
            { DisplayMode::OFF, "BarState.Off" },
            { DisplayMode::AUTO, "BarState.Auto" },
            { DisplayMode::ON, "BarState.On" }
            };
        json->PutExtAttr("direction", directionMap[GetAxisValue(Axis::VERTICAL)].c_str(), filter);
        json->PutExtAttr("state", stateMap[GetDisplayModeValue(DisplayMode::AUTO)].c_str(), filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Axis, Axis, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DisplayMode, DisplayMode, PROPERTY_UPDATE_MEASURE);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_BAR_SCROLL_BAR_LAYOUT_PROPERTY_H
