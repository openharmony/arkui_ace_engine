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

#include "base/utils/string_utils.h"
#include "base/memory/ace_type.h"
#include "core/common/ime/constant.h"
#include "core/common/ime/text_selection.h"
#include "core/common/ime/text_editing_value.h"
#include "core/common/ime/text_input_proxy.h"
#include "adapter/preview/entrance/editing/text_input_impl.h"

namespace OHOS::Ace::Platform {

TextInputClientMgr::TextInputClientMgr() : clientId_(IME_CLIENT_ID_NONE), currentConnection_(nullptr)
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
#if defined(PREVIEW)
    return false;
#else
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
        TaskExecutor::TaskType::UI, "ArkUIUpdateTextEditingValue");
    return true;
#endif
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
        TaskExecutor::TaskType::UI, "ArkUIPerformTextInputAction");
    return true;
}

} // namespace OHOS::Ace::Platform
