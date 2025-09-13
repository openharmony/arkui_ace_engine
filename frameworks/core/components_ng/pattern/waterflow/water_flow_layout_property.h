/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_PROPERTY_H

#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/scrollable/scrollable_layout_property.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class ACE_EXPORT WaterFlowLayoutProperty : public ScrollableLayoutProperty {
    DECLARE_ACE_TYPE(WaterFlowLayoutProperty, ScrollableLayoutProperty);

public:
    WaterFlowLayoutProperty() = default;
    ~WaterFlowLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override;

    void Reset() override
    {
        ScrollableLayoutProperty::Reset();
        ResetColumnsTemplate();
        ResetRowsTemplate();
        ResetColumnsGap();
        ResetRowsGap();
        ResetWaterflowDirection();
        ResetScrollEnabled();
        ResetSyncLoad();
        itemLayoutConstraint_.reset();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    Axis GetAxis() const
    {
        auto axis = propWaterflowDirection_.value_or(FlexDirection::COLUMN);
        return (axis == FlexDirection::COLUMN || axis == FlexDirection::COLUMN_REVERSE) ? Axis::VERTICAL
                                                                                        : Axis::HORIZONTAL;
    }

    bool IsReverse() const
    {
        auto axis = propWaterflowDirection_.value_or(FlexDirection::COLUMN);
        auto isRtl = GetNonAutoLayoutDirection() == TextDirection::RTL;
        return (!isRtl && (axis == FlexDirection::COLUMN_REVERSE || axis == FlexDirection::ROW_REVERSE)) ||
                (isRtl && (axis == FlexDirection::COLUMN_REVERSE || axis == FlexDirection::ROW));
    }

    bool IsVerticalReverse() const
    {
        auto axis = propWaterflowDirection_.value_or(FlexDirection::COLUMN);
        return axis == FlexDirection::COLUMN_REVERSE;
    }

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ColumnsTemplate, std::string);
    void OnColumnsTemplateUpdate(const std::string& /* columnsTemplate */) const
    {
        ResetWaterflowLayoutInfoAndMeasure();
    }

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(RowsTemplate, std::string);
    void OnRowsTemplateUpdate(const std::string& /* rowsTemplate */) const
    {
        ResetWaterflowLayoutInfoAndMeasure();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(ColumnsGap, Dimension, PROPERTY_UPDATE_MEASURE);
    void OnColumnsGapUpdate(Dimension /* columnsGap */) const;

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(RowsGap, Dimension, PROPERTY_UPDATE_MEASURE);
    void OnRowsGapUpdate(Dimension /* rowsGap */) const;

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CachedCount, int32_t, PROPERTY_UPDATE_MEASURE_SELF);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowCachedItems, bool, PROPERTY_UPDATE_MEASURE_SELF);

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(WaterflowDirection, FlexDirection);
    void OnWaterflowDirectionUpdate(FlexDirection /* WaterflowDirection */) const
    {
        ResetWaterflowLayoutInfoAndMeasure();
    }

    void UpdateItemMinSize(const CalcSize& value)
    {
        if (!itemLayoutConstraint_) {
            itemLayoutConstraint_ = std::make_unique<MeasureProperty>();
        }
        if (itemLayoutConstraint_->UpdateMinSizeWithCheck(value)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
    }

    void UpdateItemMaxSize(const CalcSize& value)
    {
        if (!itemLayoutConstraint_) {
            itemLayoutConstraint_ = std::make_unique<MeasureProperty>();
        }
        if (itemLayoutConstraint_->UpdateMaxSizeWithCheck(value)) {
            propertyChangeFlag_ = propertyChangeFlag_ | PROPERTY_UPDATE_MEASURE;
        }
    }

    std::optional<CalcSize> GetItemMinSize() const
    {
        if (itemLayoutConstraint_) {
            return itemLayoutConstraint_->minSize;
        }
        return std::optional<CalcSize>();
    }

    std::optional<CalcSize> GetItemMaxSize() const
    {
        if (itemLayoutConstraint_) {
            return itemLayoutConstraint_->maxSize;
        }
        return std::optional<CalcSize>();
    }

    bool HasItemLayoutConstraint() const
    {
        return itemLayoutConstraint_ != nullptr;
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollEnabled, bool, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(SyncLoad, bool, PROPERTY_UPDATE_NORMAL);

protected:
    void Clone(RefPtr<LayoutProperty> property) const override
    {
        auto value = DynamicCast<WaterFlowLayoutProperty>(property);
        ScrollableLayoutProperty::Clone(value);
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propRowsTemplate_ = CloneRowsTemplate();
        value->propColumnsTemplate_ = CloneColumnsTemplate();
        value->propRowsGap_ = CloneRowsGap();
        value->propColumnsGap_ = CloneColumnsGap();
        value->propWaterflowDirection_ = CloneWaterflowDirection();
        value->propScrollEnabled_ = CloneScrollEnabled();
        value->propSyncLoad_ = CloneSyncLoad();
        if (itemLayoutConstraint_) {
            value->itemLayoutConstraint_ = std::make_unique<MeasureProperty>(*itemLayoutConstraint_);
        }
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(WaterFlowLayoutProperty);

    void ResetWaterflowLayoutInfoAndMeasure() const;
    std::string GetWaterflowDirectionStr() const;
    std::unique_ptr<MeasureProperty> itemLayoutConstraint_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_LAYOUT_PROPERTY_H
