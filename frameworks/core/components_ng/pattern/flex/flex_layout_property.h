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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_LAYOUT_PROPERTY_H

#include "base/utils/macros.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/flex/flex_layout_styles.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {
struct FlexMeasureResult {
    float allocatedSize = 0.0f;
    int32_t validSizeCount = 0;
};

struct FlexLayoutResult {
    float frontSpace = 0.0f;
    float betweenSpace = 0.0f;
};

enum class FlexOperatorType {
    RESTORE_MEASURE_RESULT,
    UPDATE_MEASURE_RESULT,
    UPDATE_LAYOUT_RESULT,
};

class ACE_EXPORT FlexLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(FlexLayoutProperty, LayoutProperty);

public:
    FlexLayoutProperty() = default;

    ~FlexLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<FlexLayoutProperty>();
        Clone(value);
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetFlexLayoutAttribute();
        ResetWrapLayoutAttribute();
    }

    std::pair<bool, bool> GetPercentSensitive() override
    {
        auto flexDirection = GetFlexDirection().value_or(FlexDirection::ROW);
        auto res = LayoutProperty::GetPercentSensitive();
        if (flexDirection == FlexDirection::ROW || flexDirection == FlexDirection::ROW_REVERSE) {
            res.first = true;
        } else if (flexDirection == FlexDirection::COLUMN || flexDirection == FlexDirection::COLUMN_REVERSE) {
            res.second = true;
        }
        return res;
    }

    ACE_DEFINE_PROPERTY_GROUP(FlexLayoutAttribute, FlexLayoutAttribute);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FlexLayoutAttribute, FlexDirection, FlexDirection, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FlexLayoutAttribute, MainAxisAlign, FlexAlign, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FlexLayoutAttribute, CrossAxisAlign, FlexAlign, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FlexLayoutAttribute, Space, Dimension, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FlexLayoutAttribute, IsReverse, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(FlexLayoutAttribute, WidthLayoutPolicy, uint8_t, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(
        FlexLayoutAttribute, HeightLayoutPolicy, uint8_t, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_GROUP(WrapLayoutAttribute, WrapLayoutAttribute);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(WrapLayoutAttribute, WrapDirection, WrapDirection, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(WrapLayoutAttribute, Alignment, WrapAlignment, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(WrapLayoutAttribute, MainAlignment, WrapAlignment, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(WrapLayoutAttribute, CrossAlignment, WrapAlignment, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITH_GROUP(WrapLayoutAttribute, CrossSpace, Dimension, PROPERTY_UPDATE_MEASURE);

protected:
    void Clone(RefPtr<LayoutProperty> property) const override
    {
        auto value = DynamicCast<FlexLayoutProperty>(property);
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propFlexLayoutAttribute_ = CloneFlexLayoutAttribute();
        value->propWrapLayoutAttribute_ = CloneWrapLayoutAttribute();
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(FlexLayoutProperty);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_LAYOUT_PROPERTY_H
