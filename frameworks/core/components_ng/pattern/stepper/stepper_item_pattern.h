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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_ITEM_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_ITEM_PATTERN_H

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stepper/stepper_item_layout_property.h"
#include "core/components_ng/pattern/stepper/stepper_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT StepperItemPattern : public Pattern {
    DECLARE_ACE_TYPE(StepperItemPattern, Pattern);

public:
    StepperItemPattern() = default;
    ~StepperItemPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<StepperItemLayoutProperty>();
    }

    bool IsAtomicNode() const override
    {
        return false;
    }
    
    bool IsEnableMatchParent() override
    {
        return true;
    }

    bool IsEnableFix() override
    {
        return true;
    }

    bool IsEnableChildrenMatchParent() override
    {
        return true;
    }

    void OnModifyDone() override
    {
        Pattern::OnModifyDone();
        if (isFirstCreate) {
            isFirstCreate = false;
        } else {
            auto hostNode = DynamicCast<FrameNode>(GetHost());
            CHECK_NULL_VOID(hostNode);
            auto swiperNode = DynamicCast<FrameNode>(hostNode->GetParent());
            auto stepperNode = DynamicCast<StepperNode>(swiperNode->GetParent());
            stepperNode->MarkModifyDone();
        }
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    // This function is now for fast previews
    void OnMountToParentDone() override
    {
        auto hostNode = DynamicCast<FrameNode>(GetHost());
        CHECK_NULL_VOID(hostNode);
        auto swiperNode = DynamicCast<FrameNode>(hostNode->GetParent());
        CHECK_NULL_VOID(swiperNode);
        auto stepperNode = DynamicCast<StepperNode>(swiperNode->GetParent());
        CHECK_NULL_VOID(stepperNode);
        auto stepperPattern = stepperNode->GetPattern<StepperPattern>();
        CHECK_NULL_VOID(stepperPattern);
        stepperPattern->OnModifyDone();
    }

private:
    bool isFirstCreate = true;
    ACE_DISALLOW_COPY_AND_MOVE(StepperItemPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_ITEM_PATTERN_H
