/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_LAYOUT_LAZY_GRID_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_LAYOUT_LAZY_GRID_LAYOUT_PROPERTY_H

#include "base/geometry/axis.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT LazyGridLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(LazyGridLayoutProperty, LayoutProperty);

public:
    LazyGridLayoutProperty() = default;

    ~LazyGridLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<LazyGridLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propRowGap_ = CloneRowGap();
        value->propColumnGap_ = CloneColumnGap();
        value->propColumnsTemplate_ = CloneColumnsTemplate();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetRowGap();
        ResetColumnGap();
        ResetColumnsTemplate();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("rowsGap", propRowGap_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("ColumnsGap",
            propColumnGap_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
        json->PutExtAttr("columnsTemplate", propColumnsTemplate_.value_or("").c_str(), filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RowGap, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ColumnGap, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ColumnsTemplate, std::string, PROPERTY_UPDATE_MEASURE);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_LAYOUT_LAZY_GRID_LAYOUT_PROPERTY_H
