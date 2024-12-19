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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ITEM_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ITEM_LAYOUT_PROPERTY_H

#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {
class InspectorFilter;

class ACE_EXPORT GridItemLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(GridItemLayoutProperty, LayoutProperty);

public:
    GridItemLayoutProperty() = default;
    ~GridItemLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<GridItemLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propRowStart_ = CloneRowStart();
        value->propRowEnd_ = CloneRowEnd();
        value->propColumnStart_ = CloneColumnStart();
        value->propColumnEnd_ = CloneColumnEnd();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetRowStart();
        ResetRowEnd();
        ResetColumnStart();
        ResetColumnEnd();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(RowStart, int32_t);
    void OnRowStartUpdate(int32_t /*rowStart*/) const
    {
        ResetGridLayoutInfoAndMeasure();
    }

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(RowEnd, int32_t);
    void OnRowEndUpdate(int32_t /*rowEnd*/) const
    {
        ResetGridLayoutInfoAndMeasure();
    }

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ColumnStart, int32_t);
    void OnColumnStartUpdate(int32_t /*columnStart*/) const
    {
        ResetGridLayoutInfoAndMeasure();
    }

    ACE_DEFINE_PROPERTY_ITEM_FUNC_WITHOUT_GROUP(ColumnEnd, int32_t);
    void OnColumnEndUpdate(int32_t /*columnEnd*/) const
    {
        ResetGridLayoutInfoAndMeasure();
    }

    /** Accessibility info cache */
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(MainIndex, int32_t, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CrossIndex, int32_t, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RealColumnSpan, int32_t, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RealRowSpan, int32_t, PROPERTY_UPDATE_NORMAL);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Index, int32_t, PROPERTY_UPDATE_NORMAL);

    int32_t GetCustomCrossIndex(Axis axis) const;
    int32_t GetMainSpan(Axis axis) const;
    int32_t GetCrossSpan(Axis axis) const;
    int32_t GetMainStart(Axis axis) const;
    int32_t GetCrossStart(Axis axis) const;
    int32_t GetMainEnd(Axis axis) const;
    int32_t GetCrossEnd(Axis axis) const;
    bool CheckWhetherCurrentItemAtExpectedPosition(Axis axis) const;
    int32_t GetRealMainSpan(Axis axis) const;
    int32_t GetRealCrossSpan(Axis axis) const;
    void SetNeedStretch(bool needStretch)
    {
        needStretch_ = needStretch;
    }

    bool GetStretchChild() const
    {
        return stretchChild_;
    }

    void SetStretchChild(bool stretchChild)
    {
        stretchChild_ = stretchChild;
    }

    bool GetNeedStretch() const
    {
        return needStretch_;
    }

    void SetAxis(Axis axis)
    {
        axis_ = axis;
    }

    Axis GetAxis() const
    {
        return axis_;
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(GridItemLayoutProperty);

    void ResetGridLayoutInfoAndMeasure() const;

    bool needStretch_ = false;
    bool stretchChild_ = false;
    Axis axis_ = Axis::NONE;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_GRID_GRID_ITEM_LAYOUT_PROPERTY_H
