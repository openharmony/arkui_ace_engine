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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_LAYOUT_PROPERTY_H

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/list/list_item_model.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class ACE_EXPORT ListItemLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(ListItemLayoutProperty, LayoutProperty);

public:
    ListItemLayoutProperty() = default;

    ~ListItemLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<ListItemLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propStartDeleteAreaDistance_ = CloneStartDeleteAreaDistance();
        value->propEndDeleteAreaDistance_ = CloneEndDeleteAreaDistance();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetStartDeleteAreaDistance();
        ResetEndDeleteAreaDistance();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EdgeEffect, V2::SwipeEdgeEffect, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EditMode, uint32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StickyMode, V2::StickyMode, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StartDeleteAreaDistance, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EndDeleteAreaDistance, Dimension, PROPERTY_UPDATE_MEASURE);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_LAYOUT_PROPERTY_H
