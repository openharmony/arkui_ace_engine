/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/jsview/models/checkboxgroup_model_impl.h"

#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
void CheckBoxGroupModelImpl::Create(const std::optional<std::string>& groupName)
{
    RefPtr<CheckboxTheme> checkBoxTheme = JSViewAbstract::GetTheme<CheckboxTheme>();
    auto checkboxComponent = AceType::MakeRefPtr<OHOS::Ace::CheckboxComponent>(checkBoxTheme);

    if (groupName.has_value()) {
        const auto& checkboxGroupName = groupName.value();
        checkboxComponent->SetGroupName(checkboxGroupName);
        auto& checkboxGroupmap = CheckboxComponent::GetCheckboxGroupComponent();
        checkboxGroupmap.emplace(checkboxGroupName, checkboxComponent);
        auto& ungroupedCheckboxs = CheckboxComponent::GetUngroupedCheckboxs();
        auto item = ungroupedCheckboxs.find(checkboxGroupName);
        if (item != ungroupedCheckboxs.end()) {
            for (auto component : item->second) {
                auto chkComponent = component.Upgrade();
                if (chkComponent) {
                    checkboxComponent->AddCheckbox(chkComponent);
                    chkComponent->SetGroup(checkboxComponent);
                }
            }
            ungroupedCheckboxs.erase(item);
        }
    }

    checkboxComponent->SetInspectorTag("CheckboxGroupComponent");
    checkboxComponent->SetMouseAnimationType(HoverAnimationType::NONE);
    ViewStackProcessor::GetInstance()->ClaimElementId(checkboxComponent);
    ViewStackProcessor::GetInstance()->Push(checkboxComponent);

    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    auto horizontalPadding = checkBoxTheme->GetHotZoneHorizontalPadding();
    auto verticalPadding = checkBoxTheme->GetHotZoneVerticalPadding();
    checkboxComponent->SetWidth(checkBoxTheme->GetWidth() - horizontalPadding * 2);
    checkboxComponent->SetHeight(checkBoxTheme->GetHeight() - verticalPadding * 2);
    box->SetWidth(checkBoxTheme->GetWidth());
    box->SetHeight(checkBoxTheme->GetHeight());
}

void CheckBoxGroupModelImpl::SetSelectAll(bool isSelected)
{
    auto *stack = ViewStackProcessor::GetInstance();
    auto checkboxComponent = AceType::DynamicCast<CheckboxComponent>(stack->GetMainComponent());
    checkboxComponent->SetValue(isSelected);
}

void CheckBoxGroupModelImpl::SetSelectedColor(const Color& color)
{
    auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto checkable = AceType::DynamicCast<CheckboxComponent>(mainComponent);
    if (checkable) {
        checkable->SetActiveColor(color);
        return;
    }
}

void CheckBoxGroupModelImpl::SetOnChange(NG::GroupChangeEvent&& onChange)
{
    auto checkbox = AceType::DynamicCast<CheckboxComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    checkbox->SetOnGroupChange(EventMarker(std::move(onChange)));
}

void CheckBoxGroupModelImpl::SetWidth(const Dimension& width)
{
    auto *stack = ViewStackProcessor::GetInstance();
    Dimension padding;
    auto box = stack->GetBoxComponent();
    auto checkboxComponent = AceType::DynamicCast<CheckboxComponent>(stack->GetMainComponent());
    if (checkboxComponent) {
        padding = checkboxComponent->GetHotZoneHorizontalPadding();
        checkboxComponent->SetWidth(width);
        box->SetWidth(width + padding * 2);
    }
}

void CheckBoxGroupModelImpl::SetHeight(const Dimension& height)
{
    auto *stack = ViewStackProcessor::GetInstance();
    auto box = stack->GetBoxComponent();
    Dimension padding;
    auto checkboxComponent = AceType::DynamicCast<CheckboxComponent>(stack->GetMainComponent());
    if (checkboxComponent) {
        padding = checkboxComponent->GetHotZoneVerticalPadding();
        checkboxComponent->SetHeight(height);
        box->SetHeight(height + padding * 2);
    }
}

void CheckBoxGroupModelImpl::SetPadding(const NG::PaddingPropertyF& args, const NG::PaddingProperty& newArgs, bool flag)
{
    if (!flag) {
        return;
    }

    auto* stack = ViewStackProcessor::GetInstance();
    auto box = stack->GetBoxComponent();
    auto checkboxComponent = AceType::DynamicCast<CheckboxComponent>(stack->GetMainComponent());
    if (checkboxComponent) {
        auto width = checkboxComponent->GetWidth();
        auto height = checkboxComponent->GetHeight();
        checkboxComponent->SetHeight(height);
        checkboxComponent->SetWidth(width);
        box->SetHeight(height + Dimension(args.top.value(), DimensionUnit::VP) * 2);
        box->SetWidth(width + Dimension(args.top.value(), DimensionUnit::VP) * 2);
        checkboxComponent->SetHotZoneVerticalPadding(Dimension(args.top.value(), DimensionUnit::VP));
        checkboxComponent->SetHorizontalPadding(Dimension(args.top.value(), DimensionUnit::VP));
    }
}
} // namespace OHOS::Ace::Framework
