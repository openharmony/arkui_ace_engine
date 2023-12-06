/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_ITEM_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_ITEM_LAYOUT_PROPERTY_H

#include "core/components/common/layout/constants.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT WaterFlowItemLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(WaterFlowItemLayoutProperty, LayoutProperty);

public:
    WaterFlowItemLayoutProperty() = default;
    ~WaterFlowItemLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<WaterFlowItemLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        if (originalConstraint_) {
            value->originalConstraint_ = std::make_unique<MeasureProperty>(*originalConstraint_);
        }
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        originalConstraint_.reset();
    }

    void UpdateCalcMinSize(const CalcSize& value) override
    {
        LayoutProperty::UpdateCalcMinSize(value);
        if (!originalConstraint_) {
            originalConstraint_ = std::make_unique<MeasureProperty>();
        }
        originalConstraint_->UpdateMinSizeWithCheck(value);
    }

    void UpdateCalcMaxSize(const CalcSize& value) override
    {
        LayoutProperty::UpdateCalcMaxSize(value);
        if (!originalConstraint_) {
            originalConstraint_ = std::make_unique<MeasureProperty>();
        }
        originalConstraint_->UpdateMaxSizeWithCheck(value);
    }

    void UpdateItemCalcMinSize(const CalcSize& value)
    {
        LayoutProperty::UpdateCalcMinSize(value);
    }

    void UpdateItemCalcMaxSize(const CalcSize& value)
    {
        LayoutProperty::UpdateCalcMaxSize(value);
    }

    std::optional<CalcSize> GetMinSize() const
    {
        if (originalConstraint_) {
            return originalConstraint_->minSize;
        }
        return std::optional<CalcSize>();
    }

    std::optional<CalcSize> GetMaxSize() const
    {
        if (originalConstraint_) {
            return originalConstraint_->maxSize;
        }
        return std::optional<CalcSize>();
    }

    bool HasLayoutConstraint() const
    {
        return originalConstraint_ != nullptr;
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(WaterFlowItemLayoutProperty);
    std::unique_ptr<MeasureProperty> originalConstraint_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WATERFLOW_WATER_FLOW_ITEM_LAYOUT_PROPERTY_H
