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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RELATIVE_CONTAINER_RELATIVE_CONTAINER_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RELATIVE_CONTAINER_RELATIVE_CONTAINER_LAYOUT_PROPERTY_H

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

using AlignRulesItem = std::map<AlignDirection, AlignRule>;

class ACE_EXPORT RelativeContainerLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(RelativeContainerLayoutProperty, LayoutProperty);

public:
    RelativeContainerLayoutProperty() = default;

    ~RelativeContainerLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<RelativeContainerLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
        value->propBarrier_ = CloneBarrier();
        value->propGuideline_ = CloneGuideline();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetBarrier();
        ResetGuideline();
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Barrier, std::vector<BarrierInfo>, PROPERTY_UPDATE_MEASURE);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Guideline, std::vector<GuidelineInfo>, PROPERTY_UPDATE_MEASURE);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RELATIVE_CONTAINER_RELATIVE_CONTAINER_LAYOUT_PROPERTY_H
