/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/rich_editor/on_rich_editor_changed_listener_impl.h"

namespace OHOS::Ace::NG {
void OnRichEditorChangedListenerImpl::InsertText(const std::u16string& text)
{
    if (text.empty()) {
        LOGI("the text is null");
        return;
    }
    auto task = [richEditorPattern = pattern_, text] {
        auto client = richEditorPattern.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        if (!StringUtils::Str16ToStr8(text).compare("KEYCODE_DPAD_UP")) {
            client->CursorMoveUp();
            return;
        }
        if (!StringUtils::Str16ToStr8(text).compare("KEYCODE_DPAD_DOWN")) {
            client->CursorMoveDown();
            return;
        }
        if (!StringUtils::Str16ToStr8(text).compare("KEYCODE_DPAD_LEFT")) {
            client->CursorMoveLeft();
            return;
        }
        if (!StringUtils::Str16ToStr8(text).compare("KEYCODE_DPAD_RIGHT")) {
            client->CursorMoveRight();
            return;
        }
        client->InsertValue(StringUtils::Str16ToStr8(text));
    };
    PostTaskToUI(task);
}

void OnRichEditorChangedListenerImpl::DeleteBackward(int32_t length)
{
    if (length <= 0) {
        LOGI("Delete nothing.");
        return;
    }

    auto task = [richEditorPattern = pattern_, length] {
        auto client = richEditorPattern.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        client->DeleteBackward(length);
    };
    PostTaskToUI(task);
}

void OnRichEditorChangedListenerImpl::DeleteForward(int32_t length)
{
    if (length <= 0) {
        LOGI("Delete nothing.");
        return;
    }

    auto task = [richEditorPattern = pattern_, length] {
        auto client = richEditorPattern.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        client->DeleteForward(length);
    };
    PostTaskToUI(task);
}

void OnRichEditorChangedListenerImpl::SendKeyEventFromInputMethod(const MiscServices::KeyEvent& event) {}

void OnRichEditorChangedListenerImpl::SendKeyboardStatus(const MiscServices::KeyboardStatus& keyboardStatus)
{
    HandleKeyboardStatus(keyboardStatus);
}

void OnRichEditorChangedListenerImpl::HandleKeyboardStatus(MiscServices::KeyboardStatus status)
{
    if (status == MiscServices::KeyboardStatus::NONE) {
        return;
    }
    SetKeyboardStatus(status == MiscServices::KeyboardStatus::SHOW);
}

void OnRichEditorChangedListenerImpl::SendFunctionKey(const MiscServices::FunctionKey& functionKey)
{
    HandleFunctionKey(functionKey);
}

void OnRichEditorChangedListenerImpl::SetKeyboardStatus(bool status)
{
    auto task = [richEditorPattern = pattern_, status] {
        auto client = richEditorPattern.Upgrade();
        CHECK_NULL_VOID_NOLOG(client);
        ContainerScope scope(client->GetInstanceId());
        client->SetInputMethodStatus(status);
    };
    PostTaskToUI(task);
}

void OnRichEditorChangedListenerImpl::HandleFunctionKey(MiscServices::FunctionKey functionKey)
{
    auto task = [richEditorPattern = pattern_, functionKey] {
        auto client = richEditorPattern.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        TextInputAction action = static_cast<TextInputAction>(functionKey.GetEnterKeyType());
        switch (action) {
            case TextInputAction::DONE:
            case TextInputAction::NEXT:
            case TextInputAction::SEARCH:
            case TextInputAction::SEND:
            case TextInputAction::GO:
                client->PerformAction(action);
                break;
            default:
                LOGE("TextInputAction  is not support: %{public}d", action);
                break;
        }
    };
    PostTaskToUI(task);
}

void OnRichEditorChangedListenerImpl::MoveCursor(MiscServices::Direction direction)
{
    auto task = [richEditorPattern = pattern_, direction] {
        auto client = richEditorPattern.Upgrade();
        CHECK_NULL_VOID_NOLOG(client);
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
}

void OnRichEditorChangedListenerImpl::HandleSetSelection(int32_t start, int32_t end) {}

void OnRichEditorChangedListenerImpl::HandleExtendAction(int32_t action) {}

void OnRichEditorChangedListenerImpl::HandleSelect(int32_t keyCode, int32_t cursorMoveSkip) {}

void OnRichEditorChangedListenerImpl::PostTaskToUI(const std::function<void()>& task)
{
    CHECK_NULL_VOID(task);
    auto richEditorPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(richEditorPattern);
    auto instanceId = richEditorPattern->GetInstanceId();
    ContainerScope scope(instanceId);
    auto host = richEditorPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
}
} // namespace OHOS::Ace::NG