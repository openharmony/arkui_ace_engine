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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ARC_LIST_ARC_LIST_ITEM_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ARC_LIST_ARC_LIST_ITEM_LAYOUT_PROPERTY_H

#include "core/components_ng/pattern/list/list_item_layout_property.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class ACE_EXPORT ArcListItemLayoutProperty : public ListItemLayoutProperty {
    DECLARE_ACE_TYPE(ArcListItemLayoutProperty, ListItemLayoutProperty);

public:
    ArcListItemLayoutProperty()
    {
        propEditMode_ = V2::EditMode::NONE;
    }

    ~ArcListItemLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<ArcListItemLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propStartDeleteAreaDistance_ = CloneStartDeleteAreaDistance();
        value->propEndDeleteAreaDistance_ = CloneEndDeleteAreaDistance();
        value->propAutoScale_ = CloneAutoScale();
        return value;
    }

    void Reset() override
    {
        ListItemLayoutProperty::Reset();
        ResetAutoScale();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        if (propEdgeEffect_.has_value()) {
            auto swipeAction = JsonUtil::Create(true);
            swipeAction->Put("edgeEffect", propEdgeEffect_.value() == V2::SwipeEdgeEffect::Spring ?
                "SwipeEdgeEffect.Spring" : "SwipeEdgeEffect.Node");
            json->PutExtAttr("swipeAction", swipeAction, filter);
        } else {
            auto swipeAction = JsonUtil::Create(true);
            json->PutExtAttr("swipeAction", swipeAction, filter);
        }
        json->PutExtAttr("startDeleteAreaDistance",
            propStartDeleteAreaDistance_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("endDeleteAreaDistance",
            propEndDeleteAreaDistance_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("autoScale", propAutoScale_.value_or(true), filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(AutoScale, bool, PROPERTY_UPDATE_MEASURE);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_ARC_LIST_ARC_LIST_ITEM_LAYOUT_PROPERTY_H
