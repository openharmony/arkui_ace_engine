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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_CONTAINER_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_CONTAINER_LAYOUT_PROPERTY_H

#include <memory>
#include <vector>

#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/property.h"
#include "frameworks/core/components/common/layout/grid_container_info.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class ACE_EXPORT GridContainerLayoutProperty : public LinearLayoutProperty {
    DECLARE_ACE_TYPE(GridContainerLayoutProperty, LinearLayoutProperty);

public:
    GridContainerLayoutProperty() : LinearLayoutProperty(true)
    {
        reserveProperty_ = WeakClaim(this);
    }

    ~GridContainerLayoutProperty() override = default;

    bool operator==(const GridContainerLayoutProperty& other) const
    {
        return (propContainerInfo_ == other.propContainerInfo_);
    }

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<GridContainerLayoutProperty>();
        LinearLayoutProperty::Clone(value);
        value->propContainerInfo_ = propContainerInfo_;
        value->childrenFramenode_ = childrenFramenode_;
        return value;
    }

    void Reset() override
    {
        childrenFramenode_.clear();
        ResetContainerInfo();
        LinearLayoutProperty::Reset();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    void UpdateChild(RefPtr<GridProperty>& child, const GridContainerInfo& info);
    void RegistGridChild(const RefPtr<FrameNode>& child);
    void BuildWidth(float width);
    void SetReserveObj(const RefPtr<GridContainerLayoutProperty>& obj)
    {
        reserveProperty_ = obj;
    }
    RefPtr<GridContainerLayoutProperty> GetReserveObj()
    {
        auto obj = reserveProperty_.Upgrade();
        return obj ? obj : Claim(this);
    }
    void SetGlobalOffset(const OffsetF& offset)
    {
        globalOffset_ = offset;
    }
    const OffsetF& GetGlobalOffset()
    {
        return globalOffset_;
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(
        ContainerInfo, GridContainerInfo, PROPERTY_UPDATE_MEASURE_SELF);

private:
    void OnContainerInfoUpdate(const GridContainerInfo& info);
    std::vector<WeakPtr<FrameNode>> childrenFramenode_;
    WeakPtr<GridContainerLayoutProperty> reserveProperty_; // the layout property that will be active on next vsync
    OffsetF globalOffset_;
    ACE_DISALLOW_COPY_AND_MOVE(GridContainerLayoutProperty);
};
} // namespace OHOS::Ace::NG
#endif
