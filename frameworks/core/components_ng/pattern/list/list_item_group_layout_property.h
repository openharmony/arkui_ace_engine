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
        value->propListDirection_ = CloneListDirection();
        value->propDivider_ = CloneDivider();
        value->propLanes_ = CloneLanes();
        value->propLaneMinLength_ = CloneLaneMinLength();
        value->propLaneMaxLength_ = CloneLaneMaxLength();
        value->propListItemAlign_ = CloneListItemAlign();
        value->propCachedCount_ = CloneCachedCount();
        value->propStickyStyle_ = CloneStickyStyle();
        value->propListMainSize_ = CloneListMainSize();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetSpace();
        ResetListDirection();
        ResetDivider();
        ResetLanes();
        ResetLaneMinLength();
        ResetLaneMaxLength();
        ResetListItemAlign();
        ResetCachedCount();
        ResetStickyStyle();
        ResetListMainSize();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Space, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ListDirection, Axis, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Divider, V2::ItemDivider, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Lanes, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LaneMinLength, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LaneMaxLength, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ListItemAlign, V2::ListItemAlign, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CachedCount, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StickyStyle, V2::StickyStyle, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ListMainSize, float, PROPERTY_UPDATE_LAYOUT);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_LAYOUT_PROPERTY_H
