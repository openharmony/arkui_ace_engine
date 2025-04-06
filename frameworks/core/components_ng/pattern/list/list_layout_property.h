/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "core/components_v2/list/list_component.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

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
        value->propLanes_ = CloneLanes();
        value->propLaneMinLength_ = CloneLaneMinLength();
        value->propLaneMaxLength_ = CloneLaneMaxLength();
        value->propLaneGutter_ = CloneLaneGutter();
        value->propListItemAlign_ = CloneListItemAlign();
        value->propCachedCount_ = CloneCachedCount();
        value->propShowCachedItems_ = CloneShowCachedItems();
        value->propStickyStyle_ = CloneStickyStyle();
        value->propContentStartOffset_ = CloneContentStartOffset();
        value->propContentEndOffset_ = CloneContentEndOffset();
        value->propScrollSnapAlign_ = CloneScrollSnapAlign();
        value->propEditMode_ = CloneEditMode();
        value->propScrollEnabled_ = CloneScrollEnabled();
        value->propStackFromEnd_ = CloneStackFromEnd();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetSpace();
        ResetInitialIndex();
        ResetListDirection();
        ResetDivider();
        ResetLanes();
        ResetLaneMinLength();
        ResetLaneMaxLength();
        ResetLaneGutter();
        ResetListItemAlign();
        ResetCachedCount();
        ResetShowCachedItems();
        ResetStickyStyle();
        ResetContentStartOffset();
        ResetContentEndOffset();
        ResetScrollSnapAlign();
        ResetEditMode();
        ResetScrollEnabled();
        ResetStackFromEnd();
    }

    void SetDefaultCachedCount(const int32_t cachedCount)
    {
        defCachedCount_ = cachedCount;
    }

    int32_t GetCachedCountWithDefault() const
    {
        return GetCachedCountValue(defCachedCount_);
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    void FromJson(const std::unique_ptr<JsonValue>& json) override;

    void ScrollSnapPropToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Space, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(InitialIndex, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ListDirection, Axis, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Divider, V2::ItemDivider, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Lanes, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LaneMinLength, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LaneMaxLength, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LaneGutter, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ListItemAlign, V2::ListItemAlign, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CachedCount, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowCachedItems, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StickyStyle, V2::StickyStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollSnapAlign, ScrollSnapAlign, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ChainAnimation, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ContentStartOffset, float, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ContentEndOffset, float, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EditMode, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollEnabled, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StackFromEnd, bool, PROPERTY_UPDATE_MEASURE);

    int defCachedCount_ = 1;
protected:
    void UpdateLayoutProperty(const ListLayoutProperty* layoutProperty);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_LAYOUT_PROPERTY_H
