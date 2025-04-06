/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/text_field/on_text_changed_listener_impl.h"

namespace OHOS::Ace {

void OnTextChangedListenerImpl::InsertText(const std::u16string& text)
{
    LOGI("[OnTextChangedListenerImpl] insert size %{public}zu", StringUtils::Str16ToStr8(text).size());
    if (text.length() <= 0) {
        LOGE("the text is null");
        return;
    }

    auto task = [textField = field_, text] {
        auto client = textField.Upgrade();
        if (!client) {
            LOGE("text field is null");
            return;
        }
        ContainerScope scope(client->GetInstanceId());
        auto value = client->GetEditingValue();
        auto prevLength = value.GetWideText().length();
        if (GreatOrEqual(client->GetMaxLength(), 0) && GreatOrEqual(prevLength, client->GetMaxLength())) {
            LOGW("Cannot insert this text since reaching maximum length already");
            return;
        }
        auto leavingStrLength = static_cast<int32_t>(text.length());
        if (GreatOrEqual(client->GetMaxLength(), 0) &&
            GreatOrEqual(prevLength + static_cast<int32_t>(text.length()), client->GetMaxLength())) {
            leavingStrLength = client->GetMaxLength() - prevLength;
            LOGW("%{public}d characters of this text will be truncated for exceeding maximum length", leavingStrLength);
        }
        client->SetLastInputAction(InputAction::INSERT);
        auto insertText = text.substr(0, leavingStrLength);
        auto textEditingValue = std::make_shared<TextEditingValue>();
        textEditingValue->text =
            value.GetBeforeSelection() + StringUtils::Str16ToStr8(insertText) + value.GetAfterSelection();
        textEditingValue->UpdateSelection(std::max(value.selection.GetStart(), 0) + text.length());
        client->UpdateInsertText(StringUtils::Str16ToStr8(insertText));
        client->UpdateEditingValue(textEditingValue, true);
    };
    PostTaskToUI(task, "ArkUITextFieldInsertText");
}

void OnTextChangedListenerImpl::DeleteForward(int32_t length)
{
    LOGI("[OnTextChangedListenerImpl] DeleteForward length: %{public}d", length);
    if (length <= 0) {
        LOGE("Delete nothing.");
        return;
    }

    auto task = [textField = field_, length] {
        auto client = textField.Upgrade();
        if (!client) {
            LOGE("text field is null");
            return;
        }
        ContainerScope scope(client->GetInstanceId());
        auto value = client->GetEditingValue();
        auto start = value.selection.GetStart();
        auto end = value.selection.GetEnd();
        client->SetLastInputAction(InputAction::DELETE_FORWARD);
        auto textEditingValue = std::make_shared<TextEditingValue>();
        textEditingValue->text = value.text;
        textEditingValue->UpdateSelection(start, end);
        textEditingValue->Delete(start, start == end ? end + length : end);
        client->UpdateEditingValue(textEditingValue, true);
    };
    PostTaskToUI(task, "ArkUITextFieldDeleteForward");
}

std::u16string OnTextChangedListenerImpl::GetLeftTextOfCursor(int32_t number)
{
    LOGI("[OnTextChangedListenerImpl] GetLeftTextOfCursor status: %{public}d", number);
    std::u16string leftResult;
    auto task = [textField = field_, &leftResult, number] {
        auto client = textField.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        leftResult = client->GetLeftTextOfCursor(number);
    };
    PostSyncTaskToUI(task, "ArkUITextFieldGetCursorLeftText");
    return leftResult;
}

std::u16string OnTextChangedListenerImpl::GetRightTextOfCursor(int32_t number)
{
    LOGI("[OnTextChangedListenerImpl] GetRightTextOfCursor status: %{public}d", number);
    std::u16string rightResult;
    auto task = [textField = field_, &rightResult, number] {
        auto client = textField.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        rightResult = client->GetRightTextOfCursor(number);
    };
    PostSyncTaskToUI(task, "ArkUITextFieldGetCursorRightText");
    return rightResult;
}

int32_t OnTextChangedListenerImpl::GetTextIndexAtCursor()
{
    LOGI("[OnTextChangedListenerImpl] GetTextIndexAtCursor");
    int32_t index = 0;
    auto task = [textField = field_, &index] {
        auto client = textField.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        index = client->GetTextIndexAtCursor();
    };
    PostSyncTaskToUI(task, "ArkUITextFieldGetIndexAtCursor");
    return index;
}

void OnTextChangedListenerImpl::DeleteBackward(int32_t length)
{
    LOGI("[OnTextChangedListenerImpl] DeleteBackward length: %{public}d", length);
    if (length <= 0) {
        LOGE("Delete nothing.");
        return;
    }

    auto task = [textField = field_, length] {
        auto client = textField.Upgrade();
        if (!client) {
            LOGE("text field is null");
            return;
        }
        ContainerScope scope(client->GetInstanceId());
        auto value = client->GetEditingValue();
        auto start = value.selection.GetStart();
        auto end = value.selection.GetEnd();
        client->SetLastInputAction(InputAction::DELETE_BACKWARD);
        auto textEditingValue = std::make_shared<TextEditingValue>();
        textEditingValue->text = value.text;
        textEditingValue->UpdateSelection(start, end);
        textEditingValue->Delete(start == end ? start - length : start, end);
        client->UpdateEditingValue(textEditingValue, true);
    };
    PostTaskToUI(task, "ArkUITextFieldDeleteBackward");
}

void OnTextChangedListenerImpl::SetKeyboardStatus(bool status)
{
    LOGI("[OnTextChangedListenerImpl] SetKeyboardStatus status: %{public}d", status);
    auto task = [textField = field_, status] {
        auto client = textField.Upgrade();
        if (client) {
            ContainerScope scope(client->GetInstanceId());
            client->SetInputMethodStatus(status);
        }
    };
    PostTaskToUI(task, "ArkUITextFieldSetKeyboardStatus");
}

void OnTextChangedListenerImpl::SendKeyEventFromInputMethod(const MiscServices::KeyEvent& event) {}

void OnTextChangedListenerImpl::SendKeyboardStatus(const MiscServices::KeyboardStatus& keyboardStatus)
{
    HandleKeyboardStatus(keyboardStatus);
}

void OnTextChangedListenerImpl::SendFunctionKey(const MiscServices::FunctionKey& functionKey)
{
    HandleFunctionKey(functionKey);
}

void OnTextChangedListenerImpl::HandleKeyboardStatus(MiscServices::KeyboardStatus status)
{
    LOGI("[OnTextChangedListenerImpl] HandleKeyboardStatus status: %{public}d", status);
    SetKeyboardStatus(status == MiscServices::KeyboardStatus::SHOW);
}

void OnTextChangedListenerImpl::HandleFunctionKey(MiscServices::FunctionKey functionKey)
{
    auto task = [textField = field_, functionKey] {
        auto client = textField.Upgrade();
        if (!client) {
            LOGE("text field is null");
            return;
        }
        ContainerScope scope(client->GetInstanceId());
        TextInputAction action_ = static_cast<TextInputAction>(functionKey.GetEnterKeyType());
        switch (action_) {
            case TextInputAction::DONE:
            case TextInputAction::NEXT:
            case TextInputAction::SEARCH:
            case TextInputAction::SEND:
            case TextInputAction::GO:
                client->PerformAction(action_);
                break;
            default:
                LOGE("TextInputAction  is not support: %{public}d", action_);
                break;
        }
    };
    PostTaskToUI(task, "ArkUITextFieldHandleFunctionKey");
}

void OnTextChangedListenerImpl::MoveCursor(MiscServices::Direction direction)
{
    auto task = [textField = field_, direction] {
        auto client = textField.Upgrade();
        if (!client) {
            return;
        }
        ContainerScope scope(client->GetInstanceId());
        switch (direction) {
            case MiscServices::Direction::UP:
                client->CursorMoveUp();
                break;
            case MiscServices::Direction::DOWN:
                client->CursorMoveDown();
                break;
            case MiscServices::Direction::LEFT:
                client->CursorMoveLeft();
                break;
            case MiscServices::Direction::RIGHT:
                client->CursorMoveRight();
                break;
            default:
                LOGE("direction is not support: %{public}d", direction);
                break;
        }
    };
    PostTaskToUI(task, "ArkUITextFieldMoveCursor");
}

void OnTextChangedListenerImpl::HandleSetSelection(int32_t start, int32_t end)
{
    auto task = [textField = field_, start, end] {
        auto client = textField.Upgrade();
        if (!client) {
            LOGE("text field is null");
            return;
        }
        ContainerScope scope(client->GetInstanceId());
        client->HandleSetSelection(start, end);
    };
    PostTaskToUI(task, "ArkUITextFieldHandleSetSelection");
}

void OnTextChangedListenerImpl::HandleExtendAction(int32_t action)
{
    auto task = [textField = field_, action] {
        auto client = textField.Upgrade();
        if (!client) {
            LOGE("text field is null");
            return;
        }
        ContainerScope scope(client->GetInstanceId());
        client->HandleExtendAction(action);
    };
    PostTaskToUI(task, "ArkUITextFieldHandleExtendAction");
}

void OnTextChangedListenerImpl::HandleSelect(int32_t keyCode, int32_t cursorMoveSkip)
{
    auto task = [textField = field_, keyCode, cursorMoveSkip] {
        auto client = textField.Upgrade();
        if (!client) {
            LOGE("text field is null");
            return;
        }
        ContainerScope scope(client->GetInstanceId());
        client->HandleOnSelect(static_cast<KeyCode>(keyCode), static_cast<CursorMoveSkip>(cursorMoveSkip));
    };
    PostTaskToUI(task, "ArkUITextFieldHandleSelect");
}

void OnTextChangedListenerImpl::PostTaskToUI(const std::function<void()>& task, const std::string& name)
{
    if (!task) {
        LOGE("task is empty");
        return;
    }

    auto context = context_.Upgrade();
    if (!context) {
        LOGE("context is null");
        return;
    }

    auto taskExecutor = context->GetTaskExecutor();
    if (!taskExecutor) {
        LOGE("task executor is null");
        return;
    }

    taskExecutor->PostTask(task, TaskExecutor::TaskType::UI, name);
}

void OnTextChangedListenerImpl::PostSyncTaskToUI(const std::function<void()>& task, const std::string& name)
{
    if (!task) {
        LOGE("task is empty");
        return;
    }

    auto context = context_.Upgrade();
    if (!context) {
        LOGE("context is null");
        return;
    }

    auto taskExecutor = context->GetTaskExecutor();
    if (!taskExecutor) {
        LOGE("task executor is null");
        return;
    }

    taskExecutor->PostSyncTask(task, TaskExecutor::TaskType::UI, name);
}
} // namespace OHOS::Ace
