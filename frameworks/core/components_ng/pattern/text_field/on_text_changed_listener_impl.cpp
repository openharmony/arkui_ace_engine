/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include "base/input_manager/input_manager.h"
#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
const std::string AUTO_FILL_PARAMS_USERNAME = "com.autofill.params.userName";
const std::string AUTO_FILL_PARAMS_NEWPASSWORD = "com.autofill.params.newPassword";
const std::string AUTO_FILL_PARAMS_OTHERACCOUNT = "com.autofill.params.otherAccount";
void OnTextChangedListenerImpl::InsertText(const std::u16string& text)
{
    if (text.empty()) {
        TAG_LOGW(AceLogTag::ACE_TEXT_FIELD, "the text is null");
        return;
    }
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "InsertText length:%{public}d", static_cast<int32_t>(text.length()));
    auto task = [textFieldPattern = pattern_, text] {
        ACE_SCOPED_TRACE("InsertText [length:%d]", static_cast<int32_t>(text.length()));
        auto client = textFieldPattern.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        client->InsertValue(StringUtils::Str16ToStr8(text), true);
    };
    PostTaskToUI(task, "ArkUITextFieldInsertText");
}

void OnTextChangedListenerImpl::DeleteBackward(int32_t length)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "DeleteBackward length: %{public}d", length);
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
    PostTaskToUI(task, "ArkUITextFieldDeleteBackward");
}

void OnTextChangedListenerImpl::DeleteForward(int32_t length)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "DeleteForward length: %{public}d", length);
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
    PostTaskToUI(task, "ArkUITextFieldDeleteForward");
}

void OnTextChangedListenerImpl::SetKeyboardStatus(bool status)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "SetKeyboardStatus status: %{public}d", status);
    auto task = [textField = pattern_, status] {
        auto client = textField.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        client->SetInputMethodStatus(status);
        if (!status) {
            client->NotifyKeyboardHeight(0);
        }
    };
    PostTaskToUI(task, "ArkUITextFieldSetKeyboardStatus");
}

std::u16string OnTextChangedListenerImpl::GetLeftTextOfCursor(int32_t number)
{
    ACE_SCOPED_TRACE("GetLeftTextOfCursor[%d]", number);
    std::u16string leftResult;
    auto task = [textField = pattern_, &leftResult, number] {
        auto client = textField.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        leftResult = client->GetLeftTextOfCursor(number);
    };
    PostSyncTaskToUI(task, "ArkUITextFieldGetLeftTextOfCursor");
    return leftResult;
}

std::u16string OnTextChangedListenerImpl::GetRightTextOfCursor(int32_t number)
{
    ACE_SCOPED_TRACE("GetRightTextOfCursor[%d]", number);
    std::u16string rightResult;
    auto task = [textField = pattern_, &rightResult, number] {
        auto client = textField.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        rightResult = client->GetRightTextOfCursor(number);
    };
    PostSyncTaskToUI(task, "ArkUITextFieldGetRightTextOfCursor");
    return rightResult;
}

int32_t OnTextChangedListenerImpl::GetTextIndexAtCursor()
{
    ACE_SCOPED_TRACE("GetTextIndexAtCursor");
    int32_t index = 0;
    auto task = [textField = pattern_, &index] {
        auto client = textField.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        index = client->GetTextIndexAtCursor();
    };
    PostSyncTaskToUI(task, "ArkUITextFieldGetTextIndexAtCursor");
    return index;
}

void OnTextChangedListenerImpl::SendKeyEventFromInputMethod(const MiscServices::KeyEvent& event) {}

void OnTextChangedListenerImpl::SendKeyboardStatus(const MiscServices::KeyboardStatus& keyboardStatus)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "SendKeyboardStatus status: %{public}d", static_cast<int>(keyboardStatus));
    // this keyboard status means shown or hidden but attachment is not closed, should be distinguished from
    // imeAttached_
    HandleKeyboardStatus(keyboardStatus);
}

void OnTextChangedListenerImpl::NotifyKeyboardHeight(uint32_t height)
{
    auto task = [textField = pattern_, height] {
        ACE_SCOPED_TRACE("NotifyKeyboardHeight");
        auto client = textField.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        client->NotifyKeyboardHeight(height);
    };
    PostTaskToUI(task, "ArkUITextFieldNotifyKeyboardHeight");
}

void OnTextChangedListenerImpl::SendFunctionKey(const MiscServices::FunctionKey& functionKey)
{
    HandleFunctionKey(functionKey);
}

void OnTextChangedListenerImpl::HandleKeyboardStatus(MiscServices::KeyboardStatus status)
{
    SetKeyboardStatus(status == MiscServices::KeyboardStatus::SHOW);
}

void OnTextChangedListenerImpl::HandleFunctionKey(MiscServices::FunctionKey functionKey)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Handle function key %{public}d",
        static_cast<int32_t>(functionKey.GetEnterKeyType()));
    auto task = [textField = pattern_, functionKey] {
        auto client = textField.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        auto action = static_cast<TextInputAction>(functionKey.GetEnterKeyType());
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
    PostTaskToUI(task, "ArkUITextFieldHandleFunctionKey");
}

void OnTextChangedListenerImpl::MoveCursor(MiscServices::Direction direction)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "move cursor direction %{public}d", static_cast<int32_t>(direction));
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
    PostTaskToUI(task, "ArkUITextFieldMoveCursor");
}

void OnTextChangedListenerImpl::HandleSetSelection(int32_t start, int32_t end)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HandleSetSelection, start %{public}d, end %{public}d", start, end);
    auto task = [textField = pattern_, start, end] {
        auto client = textField.Upgrade();
        if (!client) {
            return;
        }
        ContainerScope scope(client->GetInstanceId());
        client->HandleSetSelection(start, end);
    };
    PostTaskToUI(task, "ArkUITextFieldHandleSetSelection");
}

void OnTextChangedListenerImpl::HandleExtendAction(int32_t action)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HandleExtendAction %{public}d", action);
    auto task = [textField = pattern_, action] {
        auto client = textField.Upgrade();
        if (!client) {
            return;
        }
        ContainerScope scope(client->GetInstanceId());
        client->HandleExtendAction(action);
    };
    PostTaskToUI(task, "ArkUITextFieldHandleExtendAction");
}

void OnTextChangedListenerImpl::HandleSelect(int32_t keyCode, int32_t cursorMoveSkip)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "HandleSelect, keycode %{public}d, cursor move skip %{public}d(ignored)",
        keyCode, cursorMoveSkip);
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
    PostTaskToUI(task, "ArkUITextFieldHandleSelect");
}

void OnTextChangedListenerImpl::PostSyncTaskToUI(const std::function<void()>& task, const std::string& name)
{
    CHECK_NULL_VOID(task);
    ContainerScope scope(patternInstanceId_);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(task, TaskExecutor::TaskType::UI, name);
}

void OnTextChangedListenerImpl::PostTaskToUI(const std::function<void()>& task, const std::string& name)
{
    CHECK_NULL_VOID(task);
    ContainerScope scope(patternInstanceId_);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(task, TaskExecutor::TaskType::UI, name);
}

void OnTextChangedListenerImpl::NotifyPanelStatusInfo(const MiscServices::PanelStatusInfo& info)
{
    bool isHardKeyboardConnected = InputManager::IsKeyboardConnected();
    MiscServices::PanelType panelType = info.panelInfo.panelType;
    bool panelVisible = info.visible;
    MiscServices::Trigger triggerFrom = info.trigger;
    if (!isHardKeyboardConnected && panelType == MiscServices::PanelType::SOFT_KEYBOARD && !panelVisible) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "NotifyPanelStatusInfo soft keyboard is closed by user, trigger=%{public}d",
            triggerFrom);
        auto task = [textField = pattern_, triggerFrom] {
            auto client = textField.Upgrade();
            CHECK_NULL_VOID(client);
            ContainerScope scope(client->GetInstanceId());
            if (triggerFrom == MiscServices::Trigger::IME_APP) {
                client->NotifyKeyboardClosedByUser();
            }
            client->NotifyKeyboardClosed();
        };
        PostTaskToUI(task, "ArkUITextFieldKeyboardClosedByUser");
    }
    KeyBoardInfo keyboardInfo;
    if (info.panelInfo.panelType == MiscServices::PanelType::SOFT_KEYBOARD) {
        keyboardInfo.keyBoardType = KeyBoardType::SOFT_KEYBOARD;
    } else if (info.panelInfo.panelType == MiscServices::PanelType::STATUS_BAR) {
        keyboardInfo.keyBoardType = KeyBoardType::STATUS_BAR;
    }
    keyboardInfo.visible = info.visible;
    auto task = [weak = pattern_, keyboardInfo, id = Container::CurrentId()] {
        auto textClient = weak.Upgrade();
        CHECK_NULL_VOID(textClient);
        auto pattern = AceType::DynamicCast<Pattern>(textClient);
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContextRefPtr();
        CHECK_NULL_VOID(pipeline);
        ContainerScope scope(id);
        auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
        CHECK_NULL_VOID(textFieldManager);
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "NotifyPanelStatusInfo SetImeShow:%{public}d", keyboardInfo.visible);
        textFieldManager->SetImeShow(keyboardInfo.visible);
    };
    PostTaskToUI(task, "ArkUITextFieldSetImeShow");
}

void OnTextChangedListenerImpl::AutoFillReceivePrivateCommand(
    const std::unordered_map<std::string, MiscServices::PrivateDataValue>& privateCommand,
    const WeakPtr<TextInputClient>& pattern)
{
    auto patternPtr = pattern.Upgrade();
    CHECK_NULL_VOID(patternPtr);
    auto textFieldPattern = AceType::DynamicCast<TextFieldPattern>(patternPtr);
    CHECK_NULL_VOID(textFieldPattern);
    bool isPopup = false;
    if (privateCommand.find(AUTO_FILL_PARAMS_USERNAME) != privateCommand.end()) {
        auto userName = privateCommand.find(AUTO_FILL_PARAMS_USERNAME);
        textFieldPattern->SetAutoFillUserName(std::get<std::string>(userName->second));
        textFieldPattern->ProcessAutoFill(isPopup, true);
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "com.autofill.params.userName : %{private}s",
            std::get<std::string>(userName->second).c_str());
    } else if (privateCommand.find(AUTO_FILL_PARAMS_NEWPASSWORD) != privateCommand.end()) {
        auto newPassword = privateCommand.find(AUTO_FILL_PARAMS_NEWPASSWORD);
        textFieldPattern->SetAutoFillNewPassword(std::get<std::string>(newPassword->second));
        textFieldPattern->ProcessAutoFill(isPopup, true, true);
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "com.autofill.params.newPassword : %{private}s",
            std::get<std::string>(newPassword->second).c_str());
    } else if (privateCommand.find(AUTO_FILL_PARAMS_OTHERACCOUNT) != privateCommand.end()) {
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "com.autofill.params.otherAccount");
        textFieldPattern->SetAutoFillOtherAccount(true);
        textFieldPattern->ProcessAutoFill(isPopup, true);
    } else {
        TAG_LOGW(AceLogTag::ACE_AUTO_FILL, "invalid autofill data privateCommand");
    }
}

int32_t OnTextChangedListenerImpl::SetPreviewText(const std::u16string &text, const MiscServices::Range &range)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "SetPreviewText length :%{public}d in range (%{public}d, %{public}d)",
        static_cast<int32_t>(text.length()), range.start, range.end);
    int32_t ret = CheckPreviewTextParams(text, {range.start, range.end});
    if (ret != MiscServices::ErrorCode::NO_ERROR) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "SetPreviewText result is %{public}d}", ret);
        return ret;
    }
    auto task = [textFieldPattern = pattern_, text, range] {
        ACE_SCOPED_TRACE("SetPreviewText");
        auto client = textFieldPattern.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        client->SetPreviewText(StringUtils::Str16ToStr8(text), {range.start, range.end});
    };
    PostTaskToUI(task, "ArkUITextFieldSetPreviewText");
    return ret;
}

void OnTextChangedListenerImpl::FinishTextPreview()
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "FinishTextPreview");
    auto task = [textFieldPattern = pattern_] {
        ACE_SCOPED_TRACE("FinishTextPreview");
        auto client = textFieldPattern.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        client->FinishTextPreview();
    };
    PostTaskToUI(task, "ArkUITextFieldFinishTextPreview");
}

int32_t OnTextChangedListenerImpl::ReceivePrivateCommand(
    const std::unordered_map<std::string, MiscServices::PrivateDataValue>& privateCommand)
{
    auto uiTask = [textFieldPattern = pattern_, privateCommand] {
        auto textInputClient = textFieldPattern.Upgrade();
        CHECK_NULL_VOID(textInputClient);
        ContainerScope scope(textInputClient->GetInstanceId());
        OnTextChangedListenerImpl::AutoFillReceivePrivateCommand(privateCommand, textFieldPattern);
    };
    PostTaskToUI(uiTask, "ArkUITextFieldAutoFillReceivePrivateCommand");

    int32_t ret = MiscServices::ErrorCode::NO_ERROR;
    if (privateCommand.empty()) {
        return ret;
    }
    for (const auto& item : privateCommand) {
        if (item.first != PRIVATE_DATA_KEY) {
            continue;
        }
        size_t idx = item.second.index();
        if (idx != static_cast<size_t>(MiscServices::PrivateDataValueType::VALUE_TYPE_STRING)) {
            continue;
        }
        auto stringValue = std::get_if<std::string>(&item.second);
        if (stringValue != nullptr) {
            std::string style = *stringValue;
            auto task = [textFieldPattern = pattern_, style] {
                ACE_SCOPED_TRACE("ReceivePrivateCommand");
                auto client = textFieldPattern.Upgrade();
                CHECK_NULL_VOID(client);
                ContainerScope scope(client->GetInstanceId());
                client->ReceivePreviewTextStyle(style);
            };
            PostTaskToUI(task, "ArkUITextFieldReceivePrivateCommand");
            ret = MiscServices::ErrorCode::NO_ERROR;
        }
    }
    return ret;
}

int32_t OnTextChangedListenerImpl::CheckPreviewTextParams(const std::u16string &text, const MiscServices::Range &range)
{
    int32_t ret = MiscServices::ErrorCode::NO_ERROR;
    auto task = [textFieldPattern = pattern_, text, range, &ret] {
        ACE_SCOPED_TRACE("SetPreviewText");
        auto client = textFieldPattern.Upgrade();
        CHECK_NULL_VOID(client);
        ContainerScope scope(client->GetInstanceId());
        ret = client->CheckPreviewTextValidate(StringUtils::Str16ToStr8(text), {range.start, range.end});
    };
    PostSyncTaskToUI(task, "ArkUICheckPreviewTextParams");
    return ret;
}

void OnTextChangedListenerImpl::OnDetach()
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "OnDetach");
    ContainerScope scope(patternInstanceId_);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto textFieldManager = AceType::DynamicCast<TextFieldManagerNG>(pipeline->GetTextFieldManager());
    CHECK_NULL_VOID(textFieldManager);
    textFieldManager->SetIsImeAttached(false);
}
} // namespace OHOS::Ace::NG
