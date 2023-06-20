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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_LAYOUT_PROPERTY_H

#include <type_traits>

#include "base/geometry/axis.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"
// TODO: need to delete it.
#include "core/components_v2/list/list_component.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ListLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(ListLayoutProperty, LayoutProperty);

public:
    ListLayoutProperty() = default;

    ~ListLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<ListLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propSpace_ = CloneSpace();
        value->propInitialIndex_ = CloneInitialIndex();
        value->propListDirection_ = CloneListDirection();
        value->propDivider_ = CloneDivider();
        value->propEdgeEffect_ = CloneEdgeEffect();
        value->propLanes_ = CloneLanes();
        value->propLaneMinLength_ = CloneLaneMinLength();
        value->propLaneMaxLength_ = CloneLaneMaxLength();
        value->propListItemAlign_ = CloneListItemAlign();
        value->propCachedCount_ = CloneCachedCount();
        value->propStickyStyle_ = CloneStickyStyle();
        value->propEditMode_ = CloneEditMode();
        value->propScrollEnabled_ = CloneScrollEnabled();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetSpace();
        ResetInitialIndex();
        ResetListDirection();
        ResetDivider();
        ResetEdgeEffect();
        ResetLanes();
        ResetLaneMinLength();
        ResetLaneMaxLength();
        ResetListItemAlign();
        ResetCachedCount();
        ResetStickyStyle();
        ResetEditMode();
        ResetScrollEnabled();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json) const override;

    void FromJson(const std::unique_ptr<JsonValue>& json) override;

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Space, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(InitialIndex, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ListDirection, Axis, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Divider, V2::ItemDivider, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EdgeEffect, EdgeEffect, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Lanes, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LaneMinLength, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LaneMaxLength, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ListItemAlign, V2::ListItemAlign, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CachedCount, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StickyStyle, V2::StickyStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ChainAnimation, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EditMode, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollEnabled, bool, PROPERTY_UPDATE_MEASURE);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_LAYOUT_PROPERTY_H
