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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STEPPER_STEPPER_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STEPPER_STEPPER_LAYOUT_PROPERTY_H

#include <string>
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT StepperLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(StepperLayoutProperty, LayoutProperty);

public:
    StepperLayoutProperty() = default;
    ~StepperLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<StepperLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(AceType::DynamicCast<LayoutProperty>(this));
        value->propIndex_ = CloneIndex();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetIndex();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        json->PutExtAttr("index", std::to_string(GetIndex().value_or(0)).c_str(), filter);
    }

    void UpdateIndexWithoutMeasure(int32_t index)
    {
        if (propIndex_ != index) {
            propIndex_ = index;
        }
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(Index, uint32_t, PROPERTY_UPDATE_LAYOUT);
private:
    ACE_DISALLOW_COPY_AND_MOVE(StepperLayoutProperty);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STEPPER_STEPPER_LAYOUT_PROPERTY_H
