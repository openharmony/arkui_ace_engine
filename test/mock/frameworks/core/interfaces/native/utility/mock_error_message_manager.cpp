/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/utility/error_message_manager.h"

namespace OHOS::Ace {
namespace {
static std::string mockErrorMessage;
} // namespace

ErrorMessageManager& ErrorMessageManager::GetInstance()
{
    static ErrorMessageManager instance;
    return instance;
}

void ErrorMessageManager::SetErrorCodeAndMessage(ArkUI_Int32 errorCode, const char* errorMessage)
{
    mockErrorMessage =
        "error: " + std::string(errorMessage ? errorMessage : "") + " code: " + std::to_string(errorCode);
    return;
}

void ErrorMessageManager::SetFunctionName(const char* functionName)
{
    mockErrorMessage = functionName ? std::string(functionName) + " " + mockErrorMessage : "";
    return;
}

const char* ErrorMessageManager::GetErrorMessage() const
{
    return mockErrorMessage.c_str();
}
} // namespace OHOS::Ace
