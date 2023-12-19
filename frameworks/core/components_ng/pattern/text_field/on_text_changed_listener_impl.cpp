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

#include "core/components_ng/pattern/text_field/on_text_changed_listener_impl.h"

#include "core/common/container_scope.h"
#include "core/common/ime/text_input_client.h"
#include "core/event/key_event.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

void OnTextChangedListenerImpl::InsertText(const std::u16string& text)
{
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "[OnTextChangedListenerImpl] insert value %{public}s",
            StringUtils::Str16ToStr8(text).c_str());
    }
    if (text.empty()) {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "the text is null");
        return;
    }
    auto task = [textFieldPattern = pattern_, text] {
        auto client = textFieldPattern.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        client->InsertValue(StringUtils::Str16ToStr8(text));
    };
    PostTaskToUI(task);
}

void OnTextChangedListenerImpl::DeleteBackward(int32_t length)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "[OnTextChangedListenerImpl] DeleteBackward length: %{public}d", length);
    if (length <= 0) {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "Delete nothing.");
        return;
    }

    auto task = [textFieldPattern = pattern_, length] {
        auto client = textFieldPattern.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        client->DeleteBackward(length);
    };
    PostTaskToUI(task);
}

void OnTextChangedListenerImpl::DeleteForward(int32_t length)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "[OnTextChangedListenerImpl] DeleteForward length: %{public}d", length);
    if (length <= 0) {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "Delete nothing.");
        return;
    }

    auto task = [textFieldPattern = pattern_, length] {
        auto client = textFieldPattern.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        client->DeleteForward(length);
    };
    PostTaskToUI(task);
}

void OnTextChangedListenerImpl::SetKeyboardStatus(bool status)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "[OnTextChangedListenerImpl] SetKeyboardStatus status: %{public}d", status);
    auto task = [textField = pattern_, status] {
        auto client = textField.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        client->SetInputMethodStatus(status);
    };
    PostTaskToUI(task);
}

std::u16string OnTextChangedListenerImpl::GetLeftTextOfCursor(int32_t number)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "[OnTextChangedListenerImpl] GetLeftTextOfCursor status: %{public}d", number);
    std::u16string leftResult;
    auto task = [textField = pattern_, &leftResult, number] {
        auto client = textField.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        leftResult = client->GetLeftTextOfCursor(number);
    };
    PostSyncTaskToUI(task);
    return leftResult;
}

std::u16string OnTextChangedListenerImpl::GetRightTextOfCursor(int32_t number)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "[OnTextChangedListenerImpl] GetRightTextOfCursor status: %{public}d", number);
    std::u16string rightResult;
    auto task = [textField = pattern_, &rightResult, number] {
        auto client = textField.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        rightResult = client->GetRightTextOfCursor(number);
    };
    PostSyncTaskToUI(task);
    return rightResult;
}

int32_t OnTextChangedListenerImpl::GetTextIndexAtCursor()
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "[OnTextChangedListenerImpl] GetTextIndexAtCursor");
    int32_t index = 0;
    auto task = [textField = pattern_, &index] {
        auto client = textField.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        index = client->GetTextIndexAtCursor();
    };
    PostSyncTaskToUI(task);
    return index;
}

void OnTextChangedListenerImpl::SendKeyEventFromInputMethod(const MiscServices::KeyEvent& event) {}

void OnTextChangedListenerImpl::SendKeyboardStatus(const MiscServices::KeyboardStatus& keyboardStatus)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "[OnTextChangedListenerImpl] SendKeyboardStatus status: %{public}d",
        static_cast<int>(keyboardStatus));
    // this keyboard status means shown or hidden but attachment is not closed, should be distinguished from
    // imeAttached_
    HandleKeyboardStatus(keyboardStatus);
}

void OnTextChangedListenerImpl::SendFunctionKey(const MiscServices::FunctionKey& functionKey)
{
    HandleFunctionKey(functionKey);
}

void OnTextChangedListenerImpl::HandleKeyboardStatus(MiscServices::KeyboardStatus status)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "[OnTextChangedListenerImpl] HandleKeyboardStatus status: %{public}d", status);
    SetKeyboardStatus(status == MiscServices::KeyboardStatus::SHOW);
}

void OnTextChangedListenerImpl::HandleFunctionKey(MiscServices::FunctionKey functionKey)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "[OnTextChangedListenerImpl] Handle function key %{public}d",
        static_cast<int32_t>(functionKey.GetEnterKeyType()));
    auto task = [textField = pattern_, functionKey] {
        auto client = textField.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        TextInputAction action = static_cast<TextInputAction>(functionKey.GetEnterKeyType());
        switch (action) {
            case TextInputAction::DONE:
            case TextInputAction::NEXT:
            case TextInputAction::SEARCH:
            case TextInputAction::SEND:
            case TextInputAction::GO:
            case TextInputAction::PREVIOUS:
            case TextInputAction::NEW_LINE:
                client->PerformAction(action, true);
                break;
            default:
                TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "TextInputAction  is not support: %{public}d", action);
                break;
        }
    };
    PostTaskToUI(task);
}

void OnTextChangedListenerImpl::MoveCursor(MiscServices::Direction direction)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "[OnTextChangedListenerImpl] move cursor direction %{public}d",
        static_cast<int32_t>(direction));
    auto task = [textField = pattern_, direction] {
        auto client = textField.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        client->ResetTouchAtLeftOffsetFlag();
        switch (direction) {
            case MiscServices::Direction::UP:
                client->CursorMove(CaretMoveIntent::Up);
                break;
            case MiscServices::Direction::DOWN:
                client->CursorMove(CaretMoveIntent::Down);
                break;
            case MiscServices::Direction::LEFT:
                client->CursorMove(CaretMoveIntent::Left);
                break;
            case MiscServices::Direction::RIGHT:
                client->CursorMove(CaretMoveIntent::Right);
                break;
            default:
                TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "direction is not support: %{public}d", direction);
                break;
        }
    };
    PostTaskToUI(task);
}

void OnTextChangedListenerImpl::HandleSetSelection(int32_t start, int32_t end)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
        "[OnTextChangedListenerImpl] HandleSetSelection, start %{public}d, end %{public}d", start, end);
    auto task = [textField = pattern_, start, end] {
        auto client = textField.Upgrade();
        if (!client) {
            return;
        }
        ContainerScope scope(client->GetInstanceId());
        client->HandleSetSelection(start, end);
    };
    PostTaskToUI(task);
}

void OnTextChangedListenerImpl::HandleExtendAction(int32_t action)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "[OnTextChangedListenerImpl] HandleExtendAction %{public}d", action);
    auto task = [textField = pattern_, action] {
        auto client = textField.Upgrade();
        if (!client) {
            return;
        }
        ContainerScope scope(client->GetInstanceId());
        client->HandleExtendAction(action);
    };
    PostTaskToUI(task);
}

void OnTextChangedListenerImpl::HandleSelect(int32_t keyCode, int32_t cursorMoveSkip)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
        "[OnTextChangedListenerImpl] HandleSelect, keycode %{public}d, cursor move skip %{public}d(ignored)", keyCode,
        cursorMoveSkip);
    auto task = [textField = pattern_, keyCode, cursorMoveSkip] {
        auto client = textField.Upgrade();
        if (!client) {
            return;
        }
        CaretMoveIntent direction;
        switch (static_cast<KeyCode>(keyCode)) {
            case KeyCode::KEY_DPAD_LEFT:
                direction = CaretMoveIntent::Left;
                break;
            case KeyCode::KEY_DPAD_RIGHT:
                direction = CaretMoveIntent::Right;
                break;
            case KeyCode::KEY_DPAD_UP:
                direction = CaretMoveIntent::Up;
                break;
            case KeyCode::KEY_DPAD_DOWN:
                direction = CaretMoveIntent::Down;
                break;
            default:
                TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "keyCode is not support: %{public}d", keyCode);
                return;
        }
        ContainerScope scope(client->GetInstanceId());
        client->HandleSelect(direction);
    };
    PostTaskToUI(task);
}

void OnTextChangedListenerImpl::PostSyncTaskToUI(const std::function<void()>& task)
{
    CHECK_NULL_VOID(task);
    auto textFieldPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(textFieldPattern);
    auto instanceId = textFieldPattern->GetInstanceId();
    ContainerScope scope(instanceId);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(task, TaskExecutor::TaskType::UI);
}

void OnTextChangedListenerImpl::PostTaskToUI(const std::function<void()>& task)
{
    CHECK_NULL_VOID(task);
    auto textFieldPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(textFieldPattern);
    auto instanceId = textFieldPattern->GetInstanceId();
    ContainerScope scope(instanceId);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
}

void OnTextChangedListenerImpl::NotifyPanelStatusInfo(const MiscServices::PanelStatusInfo& info)
{
    bool isHardKeyboardConnected = false;
    MiscServices::PanelType panelType = info.panelInfo.panelType;
    bool panelVisible = info.visible;
    MiscServices::Trigger triggerFrom = info.trigger;
    if (!isHardKeyboardConnected && panelType == MiscServices::PanelType::SOFT_KEYBOARD && !panelVisible &&
        triggerFrom == MiscServices::Trigger::IME_APP) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
            "[OnTextChangedListenerImpl] NotifyPanelStatusInfo soft keyboard is closed by user.");
        auto task = [textField = pattern_] {
            auto client = textField.Upgrade();
            CHECK_NULL_VOID(client);
            ContainerScope scope(client->GetInstanceId());
            client->NotifyKeyboardClosedByUser();
        };
        PostTaskToUI(task);
    }
}
} // namespace OHOS::Ace::NG
