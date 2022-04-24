/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "adapter/preview/entrance/editing/text_input_client_mgr.h"

#include <map>

#include "base/utils/string_utils.h"
#include "base/memory/ace_type.h"
#include "core/common/ime/constant.h"
#include "core/common/ime/text_selection.h"
#include "core/common/ime/text_editing_value.h"
#include "core/common/ime/text_input_proxy.h"
#include "adapter/preview/entrance/editing/text_input_impl.h"

namespace OHOS::Ace::Platform {
namespace {

const wchar_t UPPER_CASE_A = L'A';
const wchar_t LOWER_CASE_A = L'a';
const wchar_t CASE_0 = L'0';
const std::wstring NUM_SYMBOLS = L")!@#$%^&*(";
const std::map<KeyCode, wchar_t> PRINTABEL_SYMBOLS = {
    {KeyCode::KEY_GRAVE, L'`'},
    {KeyCode::KEY_MINUS, L'-'},
    {KeyCode::KEY_EQUALS, L'='},
    {KeyCode::KEY_LEFT_BRACKET, L'['},
    {KeyCode::KEY_RIGHT_BRACKET, L']'},
    {KeyCode::KEY_BACKSLASH, L'\\'},
    {KeyCode::KEY_SEMICOLON, L';'},
    {KeyCode::KEY_APOSTROPHE, L'\''},
    {KeyCode::KEY_COMMA, L','},
    {KeyCode::KEY_PERIOD, L'.'},
    {KeyCode::KEY_SLASH, L'/'},
    {KeyCode::KEY_SPACE, L' '},
    {KeyCode::KEY_NUMPAD_DIVIDE, L'/'},
    {KeyCode::KEY_NUMPAD_MULTIPLY, L'*'},
    {KeyCode::KEY_NUMPAD_SUBTRACT, L'-'},
    {KeyCode::KEY_NUMPAD_ADD, L'+'},
    {KeyCode::KEY_NUMPAD_DOT, L'.'},
    {KeyCode::KEY_NUMPAD_COMMA, L','},
    {KeyCode::KEY_NUMPAD_EQUALS, L'='},
};

const std::map<KeyCode, wchar_t> SHIFT_PRINTABEL_SYMBOLS = {
    {KeyCode::KEY_GRAVE, L'~'},
    {KeyCode::KEY_MINUS, L'_'},
    {KeyCode::KEY_EQUALS, L'+'},
    {KeyCode::KEY_LEFT_BRACKET, L'{'},
    {KeyCode::KEY_RIGHT_BRACKET, L'}'},
    {KeyCode::KEY_BACKSLASH, L'|'},
    {KeyCode::KEY_SEMICOLON, L':'},
    {KeyCode::KEY_APOSTROPHE, L'\"'},
    {KeyCode::KEY_COMMA, L'<'},
    {KeyCode::KEY_PERIOD, L'>'},
    {KeyCode::KEY_SLASH, L'?'},
};

}

TextInputClientMgr::TextInputClientMgr() : clientId_(IME_CLIENT_ID_NONE), enableCapsLock_(false),
    enableNumLock_(true), currentConnection_(nullptr)
{}

TextInputClientMgr::~TextInputClientMgr() = default;

void TextInputClientMgr::InitTextInputProxy()
{
    // Initial the proxy of Input method
    TextInputProxy::GetInstance().SetDelegate(std::make_unique<TextInputImpl>());
}

void TextInputClientMgr::SetClientId(const int32_t clientId)
{
    clientId_ = clientId;
}

void TextInputClientMgr::ResetClientId()
{
    SetClientId(IME_CLIENT_ID_NONE);
}

bool TextInputClientMgr::IsValidClientId() const
{
    return clientId_ != IME_CLIENT_ID_NONE;
}

bool TextInputClientMgr::AddCharacter(const wchar_t wideChar)
{
    LOGI("The unicode of inputed character is: %{public}d.", static_cast<int32_t>(wideChar));
    if (!IsValidClientId()) {
        return false;
    }
    std::wstring appendElement(1, wideChar);
    auto textEditingValue = std::make_shared<TextEditingValue>();
    textEditingValue->text = textEditingValue_.GetBeforeSelection() + StringUtils::ToString(appendElement) +
        textEditingValue_.GetAfterSelection();
    textEditingValue->UpdateSelection(std::max(textEditingValue_.selection.GetStart(), 0) + appendElement.length());
    SetTextEditingValue(*textEditingValue);
    return UpdateEditingValue(textEditingValue);
}

bool TextInputClientMgr::HandleTextKeyEvent(const KeyEvent& event)
{
    // Only the keys involved in the input component are processed here, and the other keys will be forwarded.
    if (!IsValidClientId()) {
        return false;
    }

    const static size_t maxKeySizes = 2;
    wchar_t keyChar;
    if (event.pressedCodes.size() == 1) {
        auto iterCode = PRINTABEL_SYMBOLS.find(event.code);
        if (iterCode != PRINTABEL_SYMBOLS.end()) {
            keyChar = iterCode->second;
        } else if (KeyCode::KEY_0 <= event.code && event.code <= KeyCode::KEY_9) {
            keyChar = static_cast<wchar_t>(event.code) - static_cast<wchar_t>(KeyCode::KEY_0) + CASE_0;
        } else if (KeyCode::KEY_NUMPAD_0 <= event.code && event.code <= KeyCode::KEY_NUMPAD_9) {
            if (!enableNumLock_) {
                return true;
            }
            keyChar = static_cast<wchar_t>(event.code) - static_cast<wchar_t>(KeyCode::KEY_NUMPAD_0) + CASE_0;
        } else if (KeyCode::KEY_A <= event.code && event.code <= KeyCode::KEY_Z) {
            keyChar = static_cast<wchar_t>(event.code) - static_cast<wchar_t>(KeyCode::KEY_A);
            keyChar += (enableCapsLock_ ? UPPER_CASE_A : LOWER_CASE_A);
        } else {
            return false;
        }
    } else if (event.pressedCodes.size() == maxKeySizes && event.pressedCodes[0] == KeyCode::KEY_SHIFT_LEFT) {
        auto iterCode = SHIFT_PRINTABEL_SYMBOLS.find(event.code);
        if (iterCode != SHIFT_PRINTABEL_SYMBOLS.end()) {
            keyChar = iterCode->second;
        } else if (KeyCode::KEY_A <= event.code && event.code <= KeyCode::KEY_Z) {
            keyChar = static_cast<wchar_t>(event.code) - static_cast<wchar_t>(KeyCode::KEY_A);
            keyChar += (enableCapsLock_ ? LOWER_CASE_A : UPPER_CASE_A);
        } else if (KeyCode::KEY_0 <= event.code && event.code <= KeyCode::KEY_9) {
            keyChar = NUM_SYMBOLS[static_cast<int32_t>(event.code) - static_cast<int32_t>(KeyCode::KEY_0)];
        } else {
            return false;
        }
    } else {
        return false;
    }

    if (event.action != KeyAction::DOWN) {
        return true;
    }
    return AddCharacter(keyChar);
}

bool TextInputClientMgr::HandleKeyEvent(const KeyEvent& event)
{
    if (event.action == KeyAction::DOWN) {
        if (event.IsKey({ KeyCode::KEY_CAPS_LOCK })) {
            enableCapsLock_ = !enableCapsLock_;
            return true;
        } else if (event.IsKey({ KeyCode::KEY_NUM_LOCK })) {
            enableNumLock_ = !enableNumLock_;
            return true;
        }
    }

    // Process all printable characters.
    return HandleTextKeyEvent(event);
}

void TextInputClientMgr::SetTextEditingValue(const TextEditingValue& textEditingValue)
{
    textEditingValue_ = textEditingValue;
}

void TextInputClientMgr::SetCurrentConnection(const RefPtr<TextInputConnection>& currentConnection)
{
    currentConnection_ = currentConnection;
}

bool TextInputClientMgr::IsCurrentConnection(const TextInputConnection* connection) const
{
    return currentConnection_ == connection;
}

bool TextInputClientMgr::UpdateEditingValue(const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent)
{
    if (!currentConnection_ || currentConnection_->GetClientId() != clientId_) {
        return false;
    }
    auto weak = AceType::WeakClaim(AceType::RawPtr(currentConnection_));
    currentConnection_->GetTaskExecutor()->PostTask(
        [weak, value, needFireChangeEvent]() {
            auto currentConnection = weak.Upgrade();
            if (currentConnection == nullptr) {
                LOGE("currentConnection is nullptr");
                return;
            }
            auto client = currentConnection->GetClient();
            if (client) {
                client->UpdateEditingValue(value, needFireChangeEvent);
            }
        },
        TaskExecutor::TaskType::UI);
    return true;
}

bool TextInputClientMgr::PerformAction(const TextInputAction action)
{
    if (!currentConnection_ || currentConnection_->GetClientId() != clientId_) {
        return false;
    }
    auto weak = AceType::WeakClaim(AceType::RawPtr(currentConnection_));
    currentConnection_->GetTaskExecutor()->PostTask(
        [weak, action]() {
            auto currentConnection = weak.Upgrade();
            if (currentConnection == nullptr) {
                LOGE("currentConnection is nullptr");
                return;
            }
            auto client = currentConnection->GetClient();
            if (client) {
                client->PerformAction(action);
            }
        },
        TaskExecutor::TaskType::UI);
    return true;
}

} // namespace OHOS::Ace::Platform
