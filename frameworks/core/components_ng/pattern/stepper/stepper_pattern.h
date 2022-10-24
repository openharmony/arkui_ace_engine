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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_PATTERN_H

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stepper/stepper_event_hub.h"
#include "core/components_ng/pattern/stepper/stepper_layout_algorithm.h"
#include "core/components_ng/pattern/stepper/stepper_layout_property.h"

namespace OHOS::Ace::NG {

class StepperPattern : public Pattern {
    DECLARE_ACE_TYPE(StepperPattern, Pattern);

public:
    StepperPattern() = default;
    ~StepperPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<StepperLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<StepperLayoutAlgorithm>(index_ != 0);
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<StepperEventHub>();
    }

private:
    void OnModifyDone() override;
    int32_t TotalCount() const;

    void InitButtonClickEvent(const RefPtr<GestureEventHub>& leftGestureHub,
        const RefPtr<GestureEventHub>& rightGestureHub, const RefPtr<FrameNode>& swiperNode);
    void HandlingButtonClickEvent(bool isLeft, const RefPtr<FrameNode>& swiperNode);
    void UpdateButtonText();

    int32_t index_ = 0;
    int32_t maxIndex_ = 0;
    RefPtr<ClickEvent> leftClickEvent_;
    RefPtr<ClickEvent> rightClickEvent_;
    ACE_DISALLOW_COPY_AND_MOVE(StepperPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_PATTERN_H