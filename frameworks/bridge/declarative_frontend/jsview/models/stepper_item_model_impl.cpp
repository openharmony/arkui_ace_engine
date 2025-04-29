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

#include "bridge/declarative_frontend/jsview/models/stepper_item_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/focus_animation/focus_animation_theme.h"
#include "core/components/stepper/stepper_item_component_v2.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/core/components/stepper/stepper_theme.h"

namespace OHOS::Ace::Framework {

void StepperItemModelImpl::Create()
{
    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;
    auto stepperItemComponentV2 = AceType::MakeRefPtr<StepperItemComponentV2>(
        FlexDirection::ROW, FlexAlign::FLEX_START, FlexAlign::FLEX_START, componentChildren);
    ViewStackProcessor::GetInstance()->Push(stepperItemComponentV2);

    RefPtr<StepperItemComponent> stepperItemComponent = ViewStackProcessor::GetInstance()->GetStepperItemComponent();
    RefPtr<StepperTheme> stepperTheme = JSViewAbstract::GetTheme<StepperTheme>();
    if (stepperTheme) {
        TextStyle textStyle_ = stepperTheme->GetTextStyle();
        textStyle_.SetAdaptTextSize(stepperTheme->GetTextStyle().GetFontSize(), stepperTheme->GetMinFontSize());
        textStyle_.SetMaxLines(stepperTheme->GetTextMaxLines());
        textStyle_.SetTextOverflow(TextOverflow::ELLIPSIS);
        stepperItemComponent->SetTextStyle(textStyle_);
    }
    auto focusAnimationTheme = JSViewAbstract::GetTheme<FocusAnimationTheme>();
    if (focusAnimationTheme) {
        stepperItemComponent->SetFocusAnimationColor(focusAnimationTheme->GetColor());
    }
    ViewStackProcessor::GetInstance()->GetStepperDisplayComponent();
    ViewStackProcessor::GetInstance()->GetStepperScrollComponent();
}

void StepperItemModelImpl::SetPrevLabel(const std::string& leftLabel)
{
    RefPtr<StepperItemComponent> stepperItem = ViewStackProcessor::GetInstance()->GetStepperItemComponent();
    if (!stepperItem) {
        LOGE("StepperItemComponent.");
        return;
    }
    StepperLabels label = stepperItem->GetLabel();
    label.leftLabel = leftLabel;
    stepperItem->SetLabel(label);
}

void StepperItemModelImpl::SetNextLabel(const std::string& rightLabel)
{
    RefPtr<StepperItemComponent> stepperItem = ViewStackProcessor::GetInstance()->GetStepperItemComponent();
    if (!stepperItem) {
        LOGE("StepperItemComponent.");
        return;
    }
    StepperLabels label = stepperItem->GetLabel();
    label.rightLabel = rightLabel;
    stepperItem->SetLabel(label);
}

void StepperItemModelImpl::SetStatus(const std::string& labelStatus)
{
    RefPtr<StepperItemComponent> stepperItem = ViewStackProcessor::GetInstance()->GetStepperItemComponent();
    if (!stepperItem) {
        LOGE("StepperItemComponent is NULL");
        return;
    }
    StepperLabels label = stepperItem->GetLabel();
    label.initialStatus = labelStatus;
    stepperItem->SetLabel(label);
}

} // namespace OHOS::Ace::Framework