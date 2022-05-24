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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_EDITING_TEXT_INPUT_CLIENT_MGR_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_EDITING_TEXT_INPUT_CLIENT_MGR_H

#include "base/memory/referenced.h"
#include "base/utils/singleton.h"
#include "core/event/key_event.h"
#include "core/common/clipboard/clipboard_proxy.h"
#include "core/common/ime/text_input_connection.h"

namespace OHOS::Ace::Platform {

class TextInputClientMgr : public Singleton<TextInputClientMgr> {
    DECLARE_SINGLETON(TextInputClientMgr);
public:
    void InitTextInputProxy();
    void SetClientId(const int32_t clientId);
    // Set the current client id to invalid value.
    void ResetClientId();
    bool IsValidClientId() const;
    void SetTextEditingValue(const TextEditingValue& textEditingValue);
    void SetCurrentConnection(const RefPtr<TextInputConnection>& currentConnection);
    bool IsCurrentConnection(const TextInputConnection* connection) const;
    bool AddCharacter(const wchar_t wideChar);

private:
    bool PerformAction(const TextInputAction action);
    bool UpdateEditingValue(const std::shared_ptr<TextEditingValue>& value, bool needFireChangeEvent = true);
    int32_t clientId_;
    TextEditingValue textEditingValue_;
    RefPtr<TextInputConnection> currentConnection_;
};

} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_EDITING_TEXT_INPUT_CLIENT_MGR_H
