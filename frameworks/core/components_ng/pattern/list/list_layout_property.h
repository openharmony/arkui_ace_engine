/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/scrollable/scrollable_layout_property.h"
#include "core/components_ng/property/property.h"
#include "compatible/components/list_v2/list_component.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

struct CacheRange {
    int32_t min;
    int32_t max;
    bool operator==(const CacheRange& other) const
    {
        return min == other.min && max == other.max;
    }
};

class ACE_EXPORT ListLayoutProperty : public ScrollableLayoutProperty {
    DECLARE_ACE_TYPE(ListLayoutProperty, ScrollableLayoutProperty);

public:
    ListLayoutProperty() = default;

    ~ListLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<ListLayoutProperty>();
        Clone(value);
        return value;
    }

    void Reset() override;

    void SetDefaultCachedCount(const int32_t cachedCount)
    {
        defCachedCount_ = cachedCount;
    }

    int32_t GetCachedCountWithDefault() const
    {
        if (propCacheRange_.has_value()) {
            auto& range = propCacheRange_.value();
            return std::max(range.min, range.max);
        }
        return GetCachedCountValue(defCachedCount_);
    }

    int32_t GetMinCacheCount() const
    {
        if (propCacheRange_.has_value()) {
            return propCacheRange_.value().min;
        }
        return GetCachedCountValue(defCachedCount_);
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    void FromJson(const std::unique_ptr<JsonValue>& json) override;

    void ScrollSnapPropToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    void SetListItemFillPolicy(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const;
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Space, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(InitialIndex, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ListDirection, Axis, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Divider, V2::ItemDivider, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Lanes, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LaneMinLength, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LaneMaxLength, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ItemFillPolicy, PresetFillType, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LaneGutter, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ListItemAlign, V2::ListItemAlign, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CachedCount, int32_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowCachedItems, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StickyStyle, V2::StickyStyle, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollSnapAlign, ScrollSnapAlign, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ChainAnimation, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(EditMode, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollEnabled, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(StackFromEnd, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SyncLoad, bool, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(DividerColorSetByUser, bool, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CacheRange, CacheRange, PROPERTY_UPDATE_MEASURE_SELF);

    int32_t defCachedCount_ = 1;
protected:
    void Clone(RefPtr<LayoutProperty> layoutProperty) const override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_LAYOUT_PROPERTY_H
