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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_GROUP_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_GROUP_LAYOUT_PROPERTY_H

#include "base/geometry/axis.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ListItemGroupLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(ListItemGroupLayoutProperty, LayoutProperty);

public:
    ListItemGroupLayoutProperty() = default;

    ~ListItemGroupLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<ListItemGroupLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propSpace_ = CloneSpace();
        value->propDivider_ = CloneDivider();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetSpace();
        ResetDivider();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("space", propSpace_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        if (propDivider_.has_value()) {
            auto divider = JsonUtil::Create(true);
            divider->Put("strokeWidth", propDivider_.value().strokeWidth.ToString().c_str());
            divider->Put("startMargin", propDivider_.value().startMargin.ToString().c_str());
            divider->Put("endMargin", propDivider_.value().endMargin.ToString().c_str());
            divider->Put("color", propDivider_.value().color.ColorToString().c_str());
            json->PutExtAttr("divider", divider, filter);
        } else {
            auto divider = JsonUtil::Create(true);
            json->PutExtAttr("divider", divider, filter);
        }
    }

    void UpdateListLanes(std::optional<int32_t> lanes,
        std::optional<Dimension> minLength, std::optional<Dimension> maxLength)
    {
        listLanes_ = lanes;
        listLaneMinLength_ = minLength;
        listLaneMaxLength_ = maxLength;
    }

    bool IsListLanesEqual(std::optional<int32_t> lanes,
        std::optional<Dimension> minLength, std::optional<Dimension> maxLength) const
    {
        return (listLanes_ == lanes) && (listLaneMinLength_ == minLength) && (listLaneMaxLength_ == maxLength);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Space, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Divider, V2::ItemDivider, PROPERTY_UPDATE_MEASURE);

private:
    std::optional<int32_t> listLanes_;
    std::optional<Dimension> listLaneMinLength_;
    std::optional<Dimension> listLaneMaxLength_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_LAYOUT_PROPERTY_H
