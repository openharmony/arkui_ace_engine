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

namespace OHOS::Ace::NG {

void OnTextChangedListenerImpl::InsertText(const std::u16string& text)
{
    LOGI("[OnTextChangedListenerImpl] insert value %{private}s", StringUtils::Str16ToStr8(text).c_str());
    if (text.empty()) {
        LOGE("the text is null");
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
    LOGI("[OnTextChangedListenerImpl] DeleteBackward length: %{public}d", length);
    if (length <= 0) {
        LOGE("Delete nothing.");
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
    LOGI("[OnTextChangedListenerImpl] DeleteForward length: %{public}d", length);
    if (length <= 0) {
        LOGE("Delete nothing.");
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

void OnTextChangedListenerImpl::SetKeyboardStatus(bool status) {}

void OnTextChangedListenerImpl::SendKeyEventFromInputMethod(const MiscServices::KeyEvent& event) {}

void OnTextChangedListenerImpl::SendKeyboardInfo(const MiscServices::KeyboardInfo& info)
{
    HandleFunctionKey(info.GetFunctionKey());
}

void OnTextChangedListenerImpl::HandleKeyboardStatus(MiscServices::KeyboardStatus status) {}

void OnTextChangedListenerImpl::HandleFunctionKey(MiscServices::FunctionKey functionKey)
{
    auto task = [textField = pattern_, functionKey] {
        auto client = textField.Upgrade();
        if (!client) {
            LOGE("text field is null");
            return;
        }
        ContainerScope scope(client->GetInstanceId());
        TextInputAction action = static_cast<TextInputAction>(functionKey);
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

void OnTextChangedListenerImpl::MoveCursor(MiscServices::Direction direction)
{
    auto task = [textField = pattern_, direction] {
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
    PostTaskToUI(task);
}

void OnTextChangedListenerImpl::PostTaskToUI(const std::function<void()>& task)
{
    CHECK_NULL_VOID(task);
    auto textFieldPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(textFieldPattern);
    auto instanceId = textFieldPattern->GetInstanceId();
    ContainerScope scope(instanceId);
    auto host = textFieldPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);

    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
}

} // namespace OHOS::Ace::NG
