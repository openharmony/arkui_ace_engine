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

#include "core/components/text_field/text_field_element.h"

#include "core/components/text_field/text_field_component.h"
#include "core/components/text_field/text_field_controller.h"

namespace OHOS::Ace {

void TextFieldElement::Update()
{
    RenderElement::Update();

    auto labelTarget = AceType::DynamicCast<LabelTarget>(component_);
    if (labelTarget) {
        auto trigger = labelTarget->GetTrigger();
        if (trigger) {
            auto weak = AceType::WeakClaim(this);
            trigger->clickHandler_ = [weak]() {
                auto textField = weak.Upgrade();
                if (textField) {
                    textField->RequestKeyboard();
                }
            };
        }
    }

    auto textField = AceType::DynamicCast<TextFieldComponent>(component_);
    if (textField) {
        if (textField->GetTextFieldController()) {
            textField->GetTextFieldController()->SetHandler(AceType::WeakClaim(this));
        }
        enabled_ = textField->IsEnabled();
    }
}

RefPtr<RenderNode> TextFieldElement::CreateRenderNode()
{
    RefPtr<RenderNode> node = RenderElement::CreateRenderNode();

    auto renderNode = AceType::DynamicCast<RenderTextField>(node);
    if (renderNode) {
        renderNode->RegisterTapCallback([wp = AceType::WeakClaim(this)]() {
            auto sp = wp.Upgrade();
            if (sp) {
                return sp->RequestKeyboard();
            }
            return false;
        });
        renderNode->SetNextFocusEvent([wp = AceType::WeakClaim(this)]() {
            auto sp = wp.Upgrade();
            if (sp) {
                auto pipeline = sp->context_.Upgrade();
                if (!pipeline) {
                    LOGW("pipeline is null.");
                    return;
                }
                sp->isNextAction_ = true;

                KeyEvent keyEvent(KeyCode::KEYBOARD_DOWN, KeyAction::UP, 0, 0, 0);
                if (!pipeline->OnKeyEvent(keyEvent)) {
                    sp->CloseKeyboard();
                } else {
                    // below textfield will auto open keyboard
                    KeyEvent keyEventEnter(KeyCode::KEYBOARD_ENTER, KeyAction::UP, 0, 0, 0);
                    pipeline->OnKeyEvent(keyEventEnter);
                }
            }
        });

        renderNode->SetOnOverlayFocusChange([wp = AceType::WeakClaim(this)](bool isFocus) {
            auto sp = wp.Upgrade();
            if (sp) {
                if (!isFocus && !sp->isRequestFocus_) {
                    sp->CloseKeyboard();
                }
            }
        });
    }
    return node;
}

bool TextFieldElement::OnKeyEvent(const KeyEvent& keyEvent)
{
    if (!enabled_) {
        return false;
    }

    if (editingMode_ && FocusNode::OnKeyEvent(keyEvent)) {
        return true;
    }

    if (editingMode_) {
        auto textField = DynamicCast<RenderTextField>(renderNode_);
        if (textField && textField->OnKeyEvent(keyEvent)) {
            return true;
        }
    }

    if (keyEvent.action != KeyAction::UP) {
        return false;
    }

    switch (keyEvent.code) {
        case KeyCode::KEYBOARD_BACK:
        case KeyCode::KEYBOARD_ESCAPE: {
            bool editingMode = editingMode_;
            CloseKeyboard();
            // If not editingMode, mark the keyevent unhandled to let navigator pop page..
            return editingMode;
        }
        case KeyCode::KEYBOARD_ENTER:
        case KeyCode::KEYBOARD_NUMBER_ENTER:
        case KeyCode::KEYBOARD_CENTER:
            RequestKeyboard(true);
            return true;
        case KeyCode::KEYBOARD_LEFT:
        case KeyCode::KEYBOARD_RIGHT:
        case KeyCode::KEYBOARD_UP:
        case KeyCode::KEYBOARD_DOWN: {
            bool result = editingMode_ && !isNextAction_;
            isNextAction_ = false;
            return result;
        }
        default:
            return false;
    }
}

void TextFieldElement::OnFocus()
{
    if (!enabled_) {
        return;
    }
    FocusNode::OnFocus();
    renderNode_->ChangeStatus(RenderStatus::FOCUS);
}

void TextFieldElement::OnBlur()
{
    if (!enabled_) {
        return;
    }
    if (renderNode_) {
        renderNode_->ChangeStatus(RenderStatus::BLUR);
    }
    CloseKeyboard();
    FocusNode::OnBlur();
}

void TextFieldElement::CloseKeyboard()
{
    isRequestFocus_ = false;
    auto textField = DynamicCast<RenderTextField>(renderNode_);
    if (textField) {
        if (textField->CloseKeyboard()) {
            editingMode_ = false;
        }
    }
}

bool TextFieldElement::RequestKeyboard(bool needStartTwinkling)
{
    if (!enabled_) {
        return false;
    }
    isRequestFocus_ = true;
    if (RequestFocusImmediately()) {
        auto textField = DynamicCast<RenderTextField>(renderNode_);
        if (textField) {
            if (textField->RequestKeyboard(!editingMode_, needStartTwinkling)) {
                editingMode_ = true;
            }
        }
        return true;
    } else {
        isRequestFocus_ = false;
        return false;
    }
}

void TextFieldElement::ShowError(const std::string& errorText)
{
    auto textField = DynamicCast<RenderTextField>(renderNode_);
    if (textField) {
        textField->ShowError(errorText);
    }
}

void TextFieldElement::Delete()
{
    auto textField = DynamicCast<RenderTextField>(renderNode_);
    if (!textField) {
        return;
    }
    auto value = textField->GetEditingValue();
    if (value.text.empty()) {
        RequestKeyboard(true);
        return;
    }
    if (editingMode_) {
        auto start = value.selection.GetStart();
        auto end = value.selection.GetEnd();
        if (start > 0 && end > 0) {
            textField->Delete(start == end ? start - 1 : start, end);
        }
    } else {
        textField->Delete(value.GetWideText().size() - 1, value.GetWideText().size());
    }
    RequestKeyboard(true);
}

} // namespace OHOS::Ace
