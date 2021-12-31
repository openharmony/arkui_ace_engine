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

#include "core/components/text_field/on_text_changed_listener_impl.h"

namespace OHOS::Ace {

void OnTextChangedListenerImpl::InsertText(const std::u16string& text)
{
    if (text.length() <= 0) {
        LOGE("the text is null");
        return;
    }

    auto renderTextField = field_.Upgrade();
    if (!renderTextField) {
        return;
    }

    auto context = renderTextField->GetContext().Upgrade();
    if (!context) {
        return;
    }

    auto taskExecutor = context->GetTaskExecutor();
    if (!taskExecutor) {
        return;
    }

    taskExecutor->PostTask(
        [renderTextField, text] {
            if (renderTextField) {
                auto value = renderTextField->GetEditingValue();
                auto textEditingValue = std::make_shared<TextEditingValue>();
                textEditingValue->text =
                    value.GetBeforeSelection() + StringUtils::Str16ToStr8(text) + value.GetAfterSelection();
                textEditingValue->UpdateSelection(std::max(value.selection.GetStart(), 0) + text.length());
                renderTextField->UpdateEditingValue(textEditingValue, true);
            }
        },
        TaskExecutor::TaskType::UI);
}

void OnTextChangedListenerImpl::DeleteBackward(int32_t length)
{
    LOGI("[OnTextChangedListenerImpl] DeleteBackward length: %{public}d", length);
    if (length <= 0) {
        LOGE("Delete nothing.");
        return;
    }

    auto renderTextField = field_.Upgrade();
    if (!renderTextField) {
        return;
    }

    auto context = renderTextField->GetContext().Upgrade();
    if (!context) {
        return;
    }

    auto taskExecutor = context->GetTaskExecutor();
    if (!taskExecutor) {
        return;
    }

    taskExecutor->PostTask(
        [renderTextField, length] {
            if (!renderTextField) {
                return;
            }
            auto value = renderTextField->GetEditingValue();
            auto start = value.selection.GetStart();
            auto end = value.selection.GetEnd();

            auto textEditingValue = std::make_shared<TextEditingValue>();
            textEditingValue->text = value.text;
            textEditingValue->UpdateSelection(start, end);
            textEditingValue->Delete(start, start == end ? end + length : end);
            renderTextField->UpdateEditingValue(textEditingValue, true);
        },
        TaskExecutor::TaskType::UI);
}

void OnTextChangedListenerImpl::DeleteForward(int32_t length)
{
    LOGI("[OnTextChangedListenerImpl] DeleteForward length: %{public}d", length);
    if (length <= 0) {
        LOGE("Delete nothing.");
        return;
    }

    auto renderTextField = field_.Upgrade();
    if (!renderTextField) {
        return;
    }

    auto context = renderTextField->GetContext().Upgrade();
    if (!context) {
        return;
    }

    auto taskExecutor = context->GetTaskExecutor();
    if (!taskExecutor) {
        return;
    }

    taskExecutor->PostTask(
        [renderTextField, length] {
            if (renderTextField) {
                auto value = renderTextField->GetEditingValue();
                auto start = value.selection.GetStart();
                auto end = value.selection.GetEnd();
                auto textEditingValue = std::make_shared<TextEditingValue>();
                textEditingValue->text = value.text;
                textEditingValue->UpdateSelection(start, end);
                if (start > 0 && end > 0) {
                    textEditingValue->Delete(start == end ? start - length : start, end);
                }
                renderTextField->UpdateEditingValue(textEditingValue, true);
            }
        },
        TaskExecutor::TaskType::UI);
}

void OnTextChangedListenerImpl::SetKeyboardStatus(bool status)
{
    LOGI("[OnTextChangedListenerImpl] SetKeyboardStatus status: %{public}d", status);
    auto renderTextField = field_.Upgrade();
    if (!renderTextField) {
        return;
    }

    auto context = renderTextField->GetContext().Upgrade();
    if (!context) {
        return;
    }

    auto taskExecutor = context->GetTaskExecutor();
    if (!taskExecutor) {
        return;
    }

    taskExecutor->PostTask(
        [renderTextField, status] {
            if (renderTextField) {
                renderTextField->SetInputMethodStatus(status);
            }
        },
        TaskExecutor::TaskType::UI);
}

void OnTextChangedListenerImpl::SendKeyEventFromInputMethod(const MiscServices::KeyEvent& event) {}

void OnTextChangedListenerImpl::SendKeyboardInfo(const MiscServices::KeyboardInfo& info)
{
    HandleKeyboardStatus(info.GetKeyboardStatus());
    HandleFunctionKey(info.GetFunctionKey());
}

void OnTextChangedListenerImpl::HandleKeyboardStatus(MiscServices::KeyboardStatus status)
{
    LOGI("[OnTextChangedListenerImpl] HandleKeyboardStatus status: %{public}d", status);
    if (status == MiscServices::KeyboardStatus::NONE) {
        return;
    }

    auto renderTextField = field_.Upgrade();
    if (!renderTextField) {
        return;
    }

    auto context = renderTextField->GetContext().Upgrade();
    if (!context) {
        return;
    }

    auto taskExecutor = context->GetTaskExecutor();
    if (!taskExecutor) {
        return;
    }

    bool currentStatus = (status == MiscServices::KeyboardStatus::SHOW);
    taskExecutor->PostTask(
        [renderTextField, currentStatus] {
            if (renderTextField) {
                if (currentStatus) {
                    renderTextField->SetInputMethodStatus(true);
                } else {
                    MiscServices::InputMethodController::GetInstance()->Close();
                    renderTextField->SetInputMethodStatus(false);
                }
            }
        },
        TaskExecutor::TaskType::UI);
}

void OnTextChangedListenerImpl::HandleFunctionKey(MiscServices::FunctionKey functionKey)
{
    LOGI("[OnTextChangedListenerImpl] HandleFunctionKey functionKey: %{public}d", functionKey);
    auto renderTextField = field_.Upgrade();
    if (!renderTextField) {
        return;
    }

    auto context = renderTextField->GetContext().Upgrade();
    if (!context) {
        return;
    }

    auto taskExecutor = context->GetTaskExecutor();
    if (!taskExecutor) {
        return;
    }

    switch (functionKey) {
        case MiscServices::FunctionKey::CONFIRM:
            taskExecutor->PostTask(
                [renderTextField] {
                    if (renderTextField) {
                        renderTextField->PerformDefaultAction();
                    }
                },
                TaskExecutor::TaskType::UI);
            break;
        case MiscServices::FunctionKey::NONE:
        default:
            break;
    }
}

} // namespace OHOS::Ace
