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

#include "core/components/checkable/checkable_element.h"

#include "core/components/checkable/render_checkable.h"

namespace OHOS::Ace {

namespace {
const std::string checkboxGroupTag("CheckboxGroupComponent");
}

void CheckableElement::Update()
{
    RenderElement::Update();
    customComponent_ = component_;
    auto labelTarget = AceType::DynamicCast<LabelTarget>(component_);
    if (!labelTarget) {
        // switch is not label target, radio and checkbox are label target
        return;
    }
    auto trigger = labelTarget->GetTrigger();
    if (!trigger) {
        // component not set label trigger
        LOGE("get label trigger failed");
        return;
    }
    auto weak = AceType::WeakClaim(this);
    trigger->clickHandler_ = [weak]() {
        auto checkable = weak.Upgrade();
        if (checkable) {
            checkable->OnClick();
        }
    };
}

void CheckableElement::OnClick()
{
    auto renderCheckable = AceType::DynamicCast<RenderCheckable>(renderNode_);
    if (!renderCheckable || renderCheckable->IsDisable()) {
        return;
    }
    renderCheckable->HandleClick();
}

void CheckableElement::OnFocus()
{
    auto context = context_.Upgrade();
    if (context && context->GetIsTabKeyPressed() && renderNode_) {
        renderNode_->ChangeStatus(RenderStatus::FOCUS);
    }
}

void CheckableElement::OnBlur()
{
    auto context = context_.Upgrade();
    if (context && context->GetIsTabKeyPressed() && renderNode_) {
        renderNode_->ChangeStatus(RenderStatus::BLUR);
    }
}

bool CheckableElement::OnKeyEvent(const KeyEvent& keyEvent)
{
    auto renderCheckable = AceType::DynamicCast<RenderCheckable>(renderNode_);
    if (!renderCheckable || renderCheckable->IsDisable()) {
        return false;
    }

    if (keyEvent.action != KeyAction::DOWN) {
        return false;
    }

    switch (keyEvent.code) {
        case KeyCode::KEY_ENTER:
        case KeyCode::KEY_NUMPAD_ENTER:
        case KeyCode::KEY_DPAD_CENTER:
        case KeyCode::KEY_SPACE:
            renderCheckable->HandleClick();
            return true;
        default:
            return false;
    }
}

void CheckableElement::SetNewComponent(const RefPtr<Component>& newComponent)
{
    Element::SetNewComponent(newComponent);
    auto selfComponent = AceType::DynamicCast<CheckboxComponent>(customComponent_.Upgrade());
    CHECK_NULL_VOID(selfComponent);
    auto newCheckboxComponent = AceType::DynamicCast<CheckboxComponent>(newComponent);
    CHECK_NULL_VOID(newCheckboxComponent);

    auto& ungroupedCheckboxs = CheckboxComponent::GetUngroupedCheckboxs();
    if (selfComponent->GetInspectorTag() == checkboxGroupTag) {
        auto checkboxList = selfComponent->GetCheckboxList();
        if (!checkboxList.empty()) {
            auto groupName = selfComponent->GetGroupName();
            auto retPair = ungroupedCheckboxs.try_emplace(groupName, std::list<WeakPtr<CheckboxComponent>>());
            for (auto item : checkboxList) {
                retPair.first->second.push_back(item);
            }
        }
    }

    if (newCheckboxComponent->GetInspectorTag() == checkboxGroupTag) {
        auto item = ungroupedCheckboxs.find(newCheckboxComponent->GetGroupName());
        if (item == ungroupedCheckboxs.end()) {
            return;
        }
        for (auto component : item->second) {
            auto checkboxComponent = component.Upgrade();
            if (checkboxComponent) {
                newCheckboxComponent->AddCheckbox(checkboxComponent);
                checkboxComponent->SetGroup(newCheckboxComponent);
            }
        }
        ungroupedCheckboxs.erase(item);
    }
}

void CheckableElement::Deactivate()
{
    RenderElement::Deactivate();
    auto selfComponent = AceType::DynamicCast<CheckboxComponent>(customComponent_.Upgrade());
    CHECK_NULL_VOID(selfComponent);
    auto& ungroupedCheckboxs = CheckboxComponent::GetUngroupedCheckboxs();
    if (selfComponent->GetInspectorTag() == checkboxGroupTag) {
        auto checkboxList = selfComponent->GetCheckboxList();
        if (!checkboxList.empty()) {
            auto groupName = selfComponent->GetGroupName();
            auto retPair = ungroupedCheckboxs.try_emplace(groupName, std::list<WeakPtr<CheckboxComponent>>());
            for (auto item : checkboxList) {
                retPair.first->second.push_back(item);
            }
        }
        auto& checkboxGroupmap = CheckboxComponent::GetCheckboxGroupComponent();
        auto item = checkboxGroupmap.find(selfComponent->GetGroupName());
        if (item != checkboxGroupmap.end() && item->second == selfComponent) {
            checkboxGroupmap.erase(item);
        }
    }
}

} // namespace OHOS::Ace
