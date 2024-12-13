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
#include "core/components_ng/base/inspector_filter.h"
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
        value->propScrollEnabled_ = CloneScrollEnabled();
        value->propScrollSnapAlign_ = CloneScrollSnapAlign();
        value->propScrollContentEndOffset_ = CloneScrollContentEndOffset();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetAxis();
        ResetScrollEnabled();
        ResetScrollContentEndOffset();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        std::unordered_map<Axis, std::string> scrollableMap { { Axis::VERTICAL, "ScrollDirection.Vertical" },
            { Axis::HORIZONTAL, "ScrollDirection.Horizontal" }, { Axis::FREE, "ScrollDirection.Free" },
            { Axis::NONE, "ScrollDirection.None" } };
        Axis axis = GetAxisValue(Axis::VERTICAL);
        json->PutFixedAttr("scrollable", scrollableMap[axis].c_str(), filter, FIXED_ATTR_SCROLLABLE);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("enableScrollInteraction", propScrollEnabled_.value_or(true), filter);
        std::unordered_map<ScrollSnapAlign, std::string> scrollSnapAlignMap {
            { ScrollSnapAlign::NONE, "ScrollSnapAlign.NONE" }, { ScrollSnapAlign::START, "ScrollSnapAlign.START" },
            { ScrollSnapAlign::CENTER, "ScrollSnapAlign::CENTER" }, { ScrollSnapAlign::END, "ScrollSnapAlign::END" }
        };
        ScrollSnapAlign scrollSnapAlign = propScrollSnapAlign_.value_or(ScrollSnapAlign::NONE);
        json->PutExtAttr("scrollSnapAlign", scrollSnapAlignMap[scrollSnapAlign].c_str(), filter);
    }

    void ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const override
    {
        LayoutProperty::ToTreeJson(json, config);
        if (config.contentOnly) {
            return;
        }
        Axis axis = GetAxisValue(Axis::VERTICAL);
        json->Put(TreeKey::SCROLLABLE, axis == Axis::VERTICAL || axis == Axis::HORIZONTAL);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Axis, Axis, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollEnabled, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollSnapAlign, ScrollSnapAlign, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollWidth, float, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollContentEndOffset, float, PROPERTY_UPDATE_MEASURE);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_LAYOUT_PROPERTY_H
