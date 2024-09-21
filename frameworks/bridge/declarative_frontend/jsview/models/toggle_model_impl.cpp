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

#include "bridge/declarative_frontend/jsview/models/toggle_model_impl.h"

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/components/toggle/toggle_component.h"
#include "core/components/toggle/toggle_theme.h"

namespace OHOS::Ace::Framework {

void ToggleModelImpl::Create(NG::ToggleType toggleType, bool isOn)
{
    RefPtr<Component> component;
    if (toggleType == NG::ToggleType::CHECKBOX) {
        RefPtr<CheckboxTheme> checkBoxTheme = JSViewAbstract::GetTheme<CheckboxTheme>();
        if (!checkBoxTheme) {
            return;
        }
        RefPtr<CheckboxComponent> checkboxComponent = AceType::MakeRefPtr<OHOS::Ace::CheckboxComponent>(checkBoxTheme);
        checkboxComponent->SetValue(isOn);
        checkboxComponent->SetMouseAnimationType(HoverAnimationType::NONE);
        auto horizontalPadding = checkBoxTheme->GetHotZoneHorizontalPadding();
        auto verticalPadding = checkBoxTheme->GetHotZoneVerticalPadding();
        checkboxComponent->SetWidth(checkBoxTheme->GetWidth() - horizontalPadding * 2);
        checkboxComponent->SetHeight(checkBoxTheme->GetHeight() - verticalPadding * 2);
        component = checkboxComponent;
    } else if (toggleType == NG::ToggleType::SWITCH) {
        RefPtr<SwitchTheme> switchTheme = JSViewAbstract::GetTheme<SwitchTheme>();
        if (!switchTheme) {
            return;
        }
        RefPtr<SwitchComponent> switchComponent = AceType::MakeRefPtr<OHOS::Ace::SwitchComponent>(switchTheme);
        switchComponent->SetValue(isOn);
        switchComponent->SetMouseAnimationType(HoverAnimationType::NONE);
        auto horizontalPadding = switchTheme->GetHotZoneHorizontalPadding();
        auto verticalPadding = switchTheme->GetHotZoneVerticalPadding();
        switchComponent->SetWidth(switchTheme->GetWidth() - horizontalPadding * 2);
        switchComponent->SetHeight(switchTheme->GetHeight() - verticalPadding * 2);
        component = switchComponent;
    } else {
        RefPtr<ToggleTheme> toggleTheme = JSViewAbstract::GetTheme<ToggleTheme>();
        if (!toggleTheme) {
            return;
        }
        RefPtr<ToggleComponent> toggleComponent = AceType::MakeRefPtr<ToggleComponent>();
        toggleComponent->SetBackgroundColor(toggleTheme->GetBackgroundColor());
        toggleComponent->SetCheckedColor(toggleTheme->GetCheckedColor());
        toggleComponent->SetPressedBlendColor(toggleTheme->GetPressedBlendColor());
        toggleComponent->SetCheckedState(isOn);
        component = toggleComponent;
    }

    ViewStackProcessor::GetInstance()->ClaimElementId(component);
    ViewStackProcessor::GetInstance()->Push(component);
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetDeliverMinToChild(true);
    if (toggleType == NG::ToggleType::CHECKBOX) {
        RefPtr<CheckboxTheme> checkBoxTheme = JSViewAbstract::GetTheme<CheckboxTheme>();
        if (!checkBoxTheme) {
            return;
        }
        box->SetWidth(checkBoxTheme->GetWidth());
        box->SetHeight(checkBoxTheme->GetHeight());
    } else if (toggleType == NG::ToggleType::SWITCH) {
        RefPtr<SwitchTheme> switchTheme = JSViewAbstract::GetTheme<SwitchTheme>();
        if (!switchTheme) {
            return;
        }
        box->SetWidth(switchTheme->GetWidth());
        box->SetHeight(switchTheme->GetHeight());
    } else {
        RefPtr<ToggleTheme> toggleTheme = JSViewAbstract::GetTheme<ToggleTheme>();
        if (!toggleTheme) {
            return;
        }
        box->SetHeight(toggleTheme->GetHeight().Value(), toggleTheme->GetHeight().Unit());
    }
}
void ToggleModelImpl::SetSelectedColor(const std::optional<Color>& selectedColor)
{
    if (!selectedColor.has_value()) {
        return;
    }
    Color color = selectedColor.value();
    auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto toggle = AceType::DynamicCast<ToggleComponent>(mainComponent);
    if (toggle) {
        toggle->SetCheckedColor(color);
        return;
    }
    auto checkable = AceType::DynamicCast<CheckableComponent>(mainComponent);
    if (checkable) {
        checkable->SetActiveColor(color);
        return;
    }
}
void ToggleModelImpl::SetSwitchPointColor(const Color& switchPointColor)
{
    auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto switchComponent = AceType::DynamicCast<SwitchComponent>(mainComponent);
    if (!switchComponent) {
        LOGE("pointstyle only support switch");
        return;
    }

    switchComponent->SetPointColor(switchPointColor);
}
void ToggleModelImpl::OnChange(NG::ChangeEvent&& onChange)
{
    auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto toggle = AceType::DynamicCast<ToggleComponent>(mainComponent);
    if (toggle) {
        JSViewSetProperty(&ToggleComponent::SetOnChange, std::move(onChange));
    }
    auto checkable = AceType::DynamicCast<CheckableComponent>(mainComponent);
    if (checkable) {
        JSViewSetProperty(&CheckableComponent::SetOnChange, std::move(onChange));
    }
}

void ToggleModelImpl::SetWidth(const Dimension& width)
{
    auto* stack = ViewStackProcessor::GetInstance();
    Dimension padding;
    auto box = stack->GetBoxComponent();
    auto checkableComponent = AceType::DynamicCast<CheckableComponent>(stack->GetMainComponent());
    if (checkableComponent) {
        padding = checkableComponent->GetHotZoneHorizontalPadding();
        checkableComponent->SetWidth(width);
        box->SetWidth(width + padding * 2);
    }

    auto toggleComponent = AceType::DynamicCast<ToggleComponent>(stack->GetMainComponent());
    if (toggleComponent) {
        toggleComponent->SetWidth(width);
        box->SetWidth(width);
    }
}

void ToggleModelImpl::SetHeight(const Dimension& height)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto box = stack->GetBoxComponent();
    Dimension padding;
    auto checkableComponent = AceType::DynamicCast<CheckableComponent>(stack->GetMainComponent());
    if (checkableComponent) {
        padding = checkableComponent->GetHotZoneVerticalPadding();
        checkableComponent->SetHeight(height);
        box->SetHeight(height + padding * 2);
    }

    auto toggleComponent = AceType::DynamicCast<ToggleComponent>(stack->GetMainComponent());
    if (toggleComponent) {
        toggleComponent->SetHeight(height);
        box->SetHeight(height);
    }
}

bool ToggleModelImpl::IsToggle()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto toggleComponent = AceType::DynamicCast<ToggleComponent>(stack->GetMainComponent());
    auto box = stack->GetBoxComponent();
    return toggleComponent;
}

void ToggleModelImpl::SetPadding(const NG::PaddingPropertyF& args, const NG::PaddingProperty& /*newArgs*/)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto box = stack->GetBoxComponent();

    auto checkableComponent = AceType::DynamicCast<CheckableComponent>(stack->GetMainComponent());
    if (checkableComponent) {
        auto width = checkableComponent->GetWidth();
        auto height = checkableComponent->GetHeight();
        checkableComponent->SetHeight(height);
        checkableComponent->SetWidth(width);
        box->SetHeight(height + Dimension(args.top.value(), DimensionUnit::VP) * 2);
        box->SetWidth(width + Dimension(args.left.value(), DimensionUnit::VP) * 2);
        checkableComponent->SetHotZoneVerticalPadding(Dimension(args.top.value(), DimensionUnit::VP));
        checkableComponent->SetHorizontalPadding(Dimension(args.left.value(), DimensionUnit::VP));
    }
}

void ToggleModelImpl::Pop()
{
    ViewStackProcessor::GetInstance()->Pop();
}
} // namespace OHOS::Ace::Framework
