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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_COL_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_COL_LAYOUT_PROPERTY_H

#include <memory>
#include <vector>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_v2/grid_layout/grid_container_util_class.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class ACE_EXPORT GridColLayoutProperty : public LinearLayoutProperty {
    DECLARE_ACE_TYPE(GridColLayoutProperty, LinearLayoutProperty);

public:
    GridColLayoutProperty() : LinearLayoutProperty(true) {}
    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<GridColLayoutProperty>();
        LinearLayoutProperty::Clone(value);
        value->propSpan_ = CloneSpan();
        value->propOffset_ = CloneOffset();
        value->propOrder_ = CloneOrder();
        return value;
    }

    void Reset() override
    {
        ResetSpan();
        ResetOffset();
        ResetOrder();
        LinearLayoutProperty::Reset();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Span, V2::GridContainerSize, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Offset, V2::GridContainerSize, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Order, V2::GridContainerSize, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SizeType, V2::GridSizeType, PROPERTY_UPDATE_NORMAL);

    int32_t GetSpan(V2::GridSizeType sizeType) const
    {
        auto span = GetSpanValue();
        return GetPropValue(span, sizeType);
    }

    int32_t GetOrder(V2::GridSizeType sizeType) const
    {
        auto order = GetOrderValue();
        return GetPropValue(order, sizeType);
    }

    int32_t GetOffset(V2::GridSizeType sizeType) const
    {
        auto offset = GetOffsetValue();
        return GetPropValue(offset, sizeType);
    }

    std::string ToString() const;

private:
    static int32_t GetPropValue(const V2::GridContainerSize& prop, V2::GridSizeType sizeType);
};
} // namespace OHOS::Ace::NG
#endif
