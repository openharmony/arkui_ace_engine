/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/scroll/scroll_component.h"
#include "core/components/stepper/stepper_item_component_v2.h"

namespace OHOS::Ace {

StepperItemComponentV2::StepperItemComponentV2(FlexDirection direction, FlexAlign mainAxisAlign,
    FlexAlign crossAxisAlign, const std::list<RefPtr<Component>>& children)
    : FlexComponent(direction, mainAxisAlign, crossAxisAlign, children)
{
    displayComponent_ = AceType::MakeRefPtr<DisplayComponent>();
    stepperItemComponent_ = AceType::MakeRefPtr<StepperItemComponent>(RefPtr<Component>());
}

RefPtr<StepperItemComponent> StepperItemComponentV2::GetStepperItemComponent() const
{
    return stepperItemComponent_;
}

RefPtr<Component> StepperItemComponentV2::AdjustComponentScroll(const RefPtr<Component>& component)
{
    if (component) {
        auto scroll = AceType::MakeRefPtr<ScrollComponent>(component);
        scroll->SetTakeBoundary(false);
        return scroll;
    }
    return nullptr;
}

RefPtr<Component> StepperItemComponentV2::AdjustComponentDisplay(const RefPtr<Component>& component)
{
    if (component) {
        displayComponent_->SetChild(component);
        stepperItemComponent_->SetChild(displayComponent_);
        return stepperItemComponent_;
    }
    return nullptr;
}

} // namespace OHOS::Ace
