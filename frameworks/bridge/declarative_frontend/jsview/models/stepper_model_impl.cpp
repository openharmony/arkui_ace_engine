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

#include "bridge/declarative_frontend/jsview/models/stepper_model_impl.h"

#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/core/components/stepper/stepper_theme.h"

namespace OHOS::Ace::Framework {

void StepperModelImpl::Create(uint32_t index)
{
    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;
    auto stepperComponent = AceType::MakeRefPtr<OHOS::Ace::StepperComponent>(componentChildren);
    stepperComponent->SetIndex(static_cast<int32_t>(index));
    RefPtr<StepperTheme> theme = JSViewAbstract::GetTheme<StepperTheme>();
    if (theme) {
        stepperComponent->SetDefaultPaddingStart(theme->GetDefaultPaddingStart());
        stepperComponent->SetDefaultPaddingEnd(theme->GetDefaultPaddingEnd());
        stepperComponent->SetProgressColor(theme->GetProgressColor());
        stepperComponent->SetProgressDiameter(theme->GetProgressDiameter());
        stepperComponent->SetArrowWidth(theme->GetArrowWidth());
        stepperComponent->SetArrowHeight(theme->GetArrowHeight());
        stepperComponent->SetArrowColor(theme->GetArrowColor());
        stepperComponent->SetDisabledColor(theme->GetDisabledColor());
        stepperComponent->SetRadius(theme->GetRadius());
        stepperComponent->SetButtonPressedColor(theme->GetButtonPressedColor());
        stepperComponent->SetButtonPressedHeight(theme->GetButtonPressedHeight());
        stepperComponent->SetControlHeight(theme->GetControlHeight());
        stepperComponent->SetControlMargin(theme->GetControlMargin());
        stepperComponent->SetControlPadding(theme->GetControlPadding());
        stepperComponent->SetFocusColor(theme->GetFocusColor());
        stepperComponent->SetFocusBorderWidth(theme->GetFocusBorderWidth());
        stepperComponent->SetMouseHoverColor(theme->GetMouseHoverColor());
        stepperComponent->SetDisabledAlpha(theme->GetDisabledAlpha());
    }
    ViewStackProcessor::GetInstance()->ClaimElementId(stepperComponent);
    ViewStackProcessor::GetInstance()->Push(stepperComponent);
}
void StepperModelImpl::SetOnFinish(RoutineCallbackEvent&& eventOnFinish)
{
    auto component = AceType::DynamicCast<StepperComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<StepperComponent>());
        return;
    }
    component->SetOnFinish(std::move(eventOnFinish));
}

void StepperModelImpl::SetOnSkip(RoutineCallbackEvent&& eventOnSkip)
{
    auto component = AceType::DynamicCast<StepperComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<StepperComponent>());
        return;
    }
    component->SetOnSkip(std::move(eventOnSkip));
}

void StepperModelImpl::SetOnChange(IndexCallbackEvent&& eventOnChange)
{
    auto component = AceType::DynamicCast<StepperComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<StepperComponent>());
        return;
    }
    component->SetOnChange(std::move(eventOnChange));
}

void StepperModelImpl::SetOnNext(IndexCallbackEvent&& eventOnNext)
{
    auto component = AceType::DynamicCast<StepperComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<StepperComponent>());
        return;
    }
    component->SetOnNext(std::move(eventOnNext));
}

void StepperModelImpl::SetOnPrevious(IndexCallbackEvent&& eventOnPrevious)
{
    auto component = AceType::DynamicCast<StepperComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<StepperComponent>());
        return;
    }
    component->SetOnPrevious(std::move(eventOnPrevious));
}

} // namespace OHOS::Ace::Framework