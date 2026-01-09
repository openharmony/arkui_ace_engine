/*
 * Copyright (c) 2022-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/checkbox/checkbox_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
RefPtr<CheckboxTheme> GetCheckboxTheme()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    auto node = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto checkBoxTheme =
        node ? themeManager->GetTheme<CheckboxTheme>(node->GetThemeScopeId()) : themeManager->GetTheme<CheckboxTheme>();
    return checkBoxTheme;
}
void CheckBoxModelImpl::Create(
    const std::optional<std::string>& name, const std::optional<std::string>& groupName, const std::string& tagName)
{
    auto checkBoxTheme = GetCheckboxTheme();
    auto checkboxComponent = AceType::MakeRefPtr<OHOS::Ace::CheckboxComponent>(checkBoxTheme);

    if (name.has_value()) {
        const auto& checkboxName = name.value();
        checkboxComponent->SetCheckboxName(checkboxName);
    }
    if (groupName.has_value()) {
        const auto& checkboxGroup = groupName.value();
        checkboxComponent->SetBelongGroup(checkboxGroup);
        auto& checkboxGroupmap = CheckboxComponent::GetCheckboxGroupComponent();
        auto item = checkboxGroupmap.find(checkboxGroup);
        if (item != checkboxGroupmap.end()) {
            item->second->AddCheckbox(checkboxComponent);
            checkboxComponent->SetGroup(item->second);
        } else {
            auto& ungroupedCheckboxs = CheckboxComponent::GetUngroupedCheckboxs();
            auto retPair = ungroupedCheckboxs.try_emplace(checkboxGroup, std::list<WeakPtr<CheckboxComponent>>());
            retPair.first->second.push_back(checkboxComponent);
        }
    }

    checkboxComponent->SetInspectorTag("Checkbox");
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

void CheckBoxModelImpl::SetSelect(bool isSelected)
{
    auto *stack = ViewStackProcessor::GetInstance();
    auto checkboxComponent = AceType::DynamicCast<CheckboxComponent>(stack->GetMainComponent());
    checkboxComponent->SetValue(isSelected);
}

void CheckBoxModelImpl::SetSelectedColor(const Color& color)
{
    auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto checkable = AceType::DynamicCast<CheckboxComponent>(mainComponent);
    if (checkable) {
        checkable->SetActiveColor(color);
        return;
    }
}

void CheckBoxModelImpl::SetOnChange(NG::ChangeEvent&& onChange)
{
#ifndef NG_BUILD
    auto component = AceType::DynamicCast<CheckboxComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<CheckboxComponent>());
        return;
    }
    component->SetOnChange(std::move(onChange));
#else
    LOGE("do not support JSViewSetProperty in new pipeline");
#endif
}

void CheckBoxModelImpl::SetWidth(const Dimension& width)
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
    
void CheckBoxModelImpl::SetHeight(const Dimension& height)
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

void CheckBoxModelImpl::SetPadding(const NG::PaddingPropertyF& args, const NG::PaddingProperty& newArgs, bool flag)
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
