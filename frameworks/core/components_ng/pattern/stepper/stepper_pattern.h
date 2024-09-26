/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components/stepper/stepper_theme.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stepper/stepper_accessibility_property.h"
#include "core/components_ng/pattern/stepper/stepper_event_hub.h"
#include "core/components_ng/pattern/stepper/stepper_layout_algorithm.h"
#include "core/components_ng/pattern/stepper/stepper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_event_hub.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

class StepperPattern : public Pattern {
    DECLARE_ACE_TYPE(StepperPattern, Pattern);

public:
    using ChangeEvent = std::function<void(int32_t)>;

    StepperPattern() = default;
    ~StepperPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    bool UsResRegion() override
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

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<StepperAccessibilityProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<StepperEventHub>();
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    static RefPtr<StepperTheme> GetTheme()
    {
        static RefPtr<StepperTheme> stepperTheme;
        if (!stepperTheme) {
            auto pipeline = PipelineContext::GetCurrentContext();
            CHECK_NULL_RETURN(pipeline, nullptr);
            stepperTheme = pipeline->GetTheme<StepperTheme>();
            CHECK_NULL_RETURN(stepperTheme, nullptr);
        }
        return stepperTheme;
    }

    bool GetIsLoadingButton() const
    {
        return isLoadingButton_;
    }

    int32_t GetCurrentIndex() const
    {
        return index_;
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override
    {
        return ScopeFocusAlgorithm(true, true, ScopeType::OTHERS,
            [wp = WeakClaim(this)](
                FocusStep step, const WeakPtr<FocusHub>& currFocusNode, WeakPtr<FocusHub>& nextFocusNode) {
                auto stepper = wp.Upgrade();
                if (stepper) {
                    nextFocusNode = stepper->GetFocusNode(step, currFocusNode);
                }
            });
    }

    void OnModifyDone() override;

    void OnColorConfigurationUpdate() override;
    void OnLanguageConfigurationUpdate() override;
  
private:
    void OnAttachToFrameNode() override;
    int32_t TotalCount() const;

    void InitSwiperChangeEvent(const RefPtr<SwiperEventHub>& swiperEventHub);
    void UpdateIndexWithoutMeasure(int32_t index);
    void UpdateOrCreateLeftButtonNode(int32_t index);
    void CreateLeftButtonNode();
    void UpdateLeftButtonNode(int32_t index);
    void UpdateOrCreateRightButtonNode(int32_t index);
    void CreateRightButtonNode(int32_t index);
    void CreateArrowRightButtonNode(int32_t index, bool isDisabled);
    void CreateArrowlessRightButtonNode(int32_t index, bool isDisabled, const std::string& defaultContent);
    void CreateWaitingRightButtonNode();
    void InitButtonClickEvent();
    void HandlingLeftButtonClickEvent();
    void HandlingRightButtonClickEvent();
    void SetAccessibilityAction();
    static void ButtonSkipColorConfigurationUpdate(const RefPtr<FrameNode>& buttonNode);
    WeakPtr<FocusHub> GetFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode);
    bool isRightToLeft_ = false;
    RefPtr<FrameNode> leftImage_;
    RefPtr<FrameNode> rightImage_;
    int32_t index_ = 0;
    int32_t maxIndex_ = 0;
    std::shared_ptr<ChangeEvent> swiperChangeEvent_;
    ACE_DISALLOW_COPY_AND_MOVE(StepperPattern);
    bool isLoadingButton_ = false;
    RefPtr<FocusHub> leftFocusHub_ = nullptr;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_PATTERN_H
