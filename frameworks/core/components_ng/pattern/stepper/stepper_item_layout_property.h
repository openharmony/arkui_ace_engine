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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STEPPER_STEPPER_ITEM_LAYOUT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STEPPER_STEPPER_ITEM_LAYOUT_PROPERTY_H

#include "base/i18n/localization.h"
#include "core/components/stepper/stepper_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT StepperItemLayoutProperty : public LayoutProperty {
    DECLARE_ACE_TYPE(StepperItemLayoutProperty, LayoutProperty);

public:
    StepperItemLayoutProperty() = default;
    ~StepperItemLayoutProperty() override = default;

    RefPtr<LayoutProperty> Clone() const override
    {
        auto value = MakeRefPtr<StepperItemLayoutProperty>();
        value->LayoutProperty::UpdateLayoutProperty(AceType::DynamicCast<LayoutProperty>(this));
        value->propLeftLabel_ = CloneLeftLabel();
        value->propRightLabel_ = CloneRightLabel();
        value->propLabelStatus_ = CloneLabelStatus();
        return value;
    }

    void Reset() override
    {
        LayoutProperty::Reset();
        ResetLeftLabel();
        ResetRightLabel();
        ResetLabelStatus();
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override
    {
        LayoutProperty::ToJsonValue(json, filter);
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto theme = pipeline->GetTheme<StepperTheme>();
        std::string stepperBack = "";
        std::string stepperNext = "";
        if (theme) {
            stepperBack = theme->GetStepperBack();
            stepperNext = theme->GetStepperNext();
        }
        
        json->PutExtAttr("prevLabel",
            GetLeftLabel().value_or(stepperBack).c_str(), filter);
        json->PutExtAttr("nextLabel",
            GetRightLabel().value_or(stepperNext).c_str(), filter);
        static const std::map<std::string, std::string> STATUS_TO_STRING = { { "normal", "ItemState.Normal" },
            { "disabled", "ItemState.Disabled" }, { "waiting", "ItemState.Waiting" }, { "skip", "ItemState.Skip" } };
        json->PutExtAttr("status", STATUS_TO_STRING.at(GetLabelStatus().value_or("normal")).c_str(), filter);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LeftLabel, std::string, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(RightLabel, std::string, PROPERTY_UPDATE_LAYOUT);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(LabelStatus, std::string, PROPERTY_UPDATE_LAYOUT);

private:
    ACE_DISALLOW_COPY_AND_MOVE(StepperItemLayoutProperty);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_STEPPER_STEPPER_ITEM_LAYOUT_PROPERTY_H
