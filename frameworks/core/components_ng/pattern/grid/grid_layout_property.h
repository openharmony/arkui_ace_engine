/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_PROPERTY_H

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/grid/grid_constants.h"
#include "core/components_ng/pattern/grid/grid_layout_options.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class ACE_EXPORT GridLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(GridLayoutProperty, LayoutProperty);

public:
    GridLayoutProperty() = default;
    ~GridLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<GridLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propRowsTemplate_ = CloneRowsTemplate();
        value->propColumnsTemplate_ = CloneColumnsTemplate();
        value->propRowsGap_ = CloneRowsGap();
        value->propColumnsGap_ = CloneColumnsGap();
        value->propCachedCount_ = CloneCachedCount();
        value->propShowCachedItems_ = CloneShowCachedItems();
        value->propGridDirection_ = CloneGridDirection();
        value->propMaxCount_ = CloneMaxCount();
        value->propMinCount_ = CloneMinCount();
        value->propCellLength_ = CloneCellLength();
        value->propScrollEnabled_ = CloneScrollEnabled();
        value->propLayoutOptions_ = CloneLayoutOptions();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetColumnsTemplate();
        ResetRowsTemplate();
        ResetColumnsGap();
        ResetRowsGap();
        ResetCachedCount();
        ResetShowCachedItems();
        ResetGridDirection();
        ResetMaxCount();
        ResetMinCount();
        ResetCellLength();
        ResetScrollEnabled();
        ResetLayoutOptions();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    bool IsVertical() const
    {
        bool columnsTemplateValid = propColumnsTemplate_.has_value() && !propColumnsTemplate_.value().empty();
        bool rowsTemplateValid = propRowsTemplate_.has_value() && !propRowsTemplate_.value().empty();
        return columnsTemplateValid ||
               (!columnsTemplateValid && !rowsTemplateValid);
    }

    bool IsConfiguredScrollable() const
    {
        bool columnsTemplateSet = !propColumnsTemplate_.value_or("").empty();
        bool rowsTemplateSet = !propRowsTemplate_.value_or("").empty();
        bool verticalScrollable = (columnsTemplateSet && !rowsTemplateSet);
        bool horizontalScrollable = (!columnsTemplateSet && rowsTemplateSet);
        return verticalScrollable || horizontalScrollable;
    }

    bool IsReverse() const
    {
        bool columnsTemplateSet = !propColumnsTemplate_.value_or("").empty();
        bool rowsTemplateSet = !propRowsTemplate_.value_or("").empty();
        auto isRtl = GetNonAutoLayoutDirection() == TextDirection::RTL;
        return isRtl && !columnsTemplateSet && rowsTemplateSet;
    }

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ColumnsTemplate, std::string);
    void OnColumnsTemplateUpdate(const std::string& /* columnsTemplate */) const
    {
        ResetGridLayoutInfoAndMeasure();
    }

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(RowsTemplate, std::string);
    void OnRowsTemplateUpdate(const std::string& /* rowsTemplate */) const
    {
        ResetGridLayoutInfoAndMeasure();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(ColumnsGap, Dimension, PROPERTY_UPDATE_MEASURE);
    void OnColumnsGapUpdate(const Dimension& /* columnsGap */) const;

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(RowsGap, Dimension, PROPERTY_UPDATE_MEASURE);
    void OnRowsGapUpdate(const Dimension& /* rowsGap */) const;

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(CachedCount, int32_t);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ShowCachedItems, bool, PROPERTY_UPDATE_MEASURE);
    void OnCachedCountUpdate(int32_t /* cachedCount */) const {}

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(GridDirection, FlexDirection);
    void OnGridDirectionUpdate(FlexDirection /* gridDirection */) const
    {
        ResetGridLayoutInfoAndMeasure();
    }

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(MaxCount, int32_t);
    void OnMaxCountUpdate(int32_t /* maxCount */) const
    {
        ResetGridLayoutInfoAndMeasure();
    }

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(MinCount, int32_t);
    void OnMinCountUpdate(int32_t /* minCount */) const
    {
        ResetGridLayoutInfoAndMeasure();
    }

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(CellLength, int32_t);
    void OnCellLengthUpdate(int32_t /* cellLength */) const
    {
        ResetGridLayoutInfoAndMeasure();
    }

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(LayoutOptions, GridLayoutOptions);
    void OnLayoutOptionsUpdate(const GridLayoutOptions& layoutOptions) const;

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Editable, bool, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ScrollEnabled, bool, PROPERTY_UPDATE_MEASURE);

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(AlignItems, GridItemAlignment);
    void OnAlignItemsUpdate(GridItemAlignment /* alignItems */) const
    {
        ResetGridLayoutInfoAndMeasure();
    }

    std::pair<bool, bool> GetPercentSensitive() override
    {
        return {true, true};
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(GridLayoutProperty);

    void ResetGridLayoutInfoAndMeasure() const;
    void ResetPositionFlags() const;
    std::string GetBarStateString() const;
    std::string GetGridDirectionStr() const;
    Color GetBarColor() const;
    Dimension GetBarWidth() const;

    void UpdateIrregularFlag(const GridLayoutOptions& layoutOptions) const;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_LAYOUT_PROPERTY_H
