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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_ROW_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_ROW_LAYOUT_PROPERTY_H

#include <memory>
#include <vector>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_v2/grid_layout/grid_container_util_class.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class ACE_EXPORT GridRowLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(GridRowLayoutProperty, LayoutProperty);

public:
    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<GridRowLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(this);

        value->propColumns_ = CloneColumns();
        value->propGutter_ = CloneGutter();
        value->propBreakPoints_ = CloneBreakPoints();
        value->propDirection_ = CloneDirection();
        value->propSizeType_ = CloneSizeType();
        value->propAlignItems_ = CloneAlignItems();
        return value;
    }

    void Reset() override
    {
        ResetColumns();
        ResetGutter();
        ResetBreakPoints();
        ResetDirection();
        ResetSizeType();
        ResetAlignItems();
        LayoutProperty::Reset();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Columns, V2::GridContainerSize, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Gutter, V2::Gutter, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(BreakPoints, V2::BreakPoints, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Direction, V2::GridRowDirection, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SizeType, V2::GridSizeType, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(AlignItems, FlexAlign, PROPERTY_UPDATE_MEASURE);
};
} // namespace OHOS::Ace::NG
#endif
