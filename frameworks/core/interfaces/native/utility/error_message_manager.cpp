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

#include "error_message_manager.h"

namespace OHOS::Ace {
namespace {

struct ThreadLocalErrorInfo {
    ArkUI_Int32 errorCode = 0;
    std::string functionName;
    std::string errorMessage;
    std::string formattedErrorInfo;
    bool needRefresh = true;
};

ThreadLocalErrorInfo& GetThreadLocalErrorInfo()
{
    thread_local ThreadLocalErrorInfo errorInfo;
    return errorInfo;
}

std::string ErrorInfoToString(const ThreadLocalErrorInfo& errorInfo)
{
    std::string formattedErrorInfo = "errorCode: " + std::to_string(errorInfo.errorCode);
    if (!errorInfo.functionName.empty()) {
        formattedErrorInfo.append(", functionName: ");
        formattedErrorInfo.append(errorInfo.functionName);
    }
    if (!errorInfo.errorMessage.empty()) {
        formattedErrorInfo.append(", errorMessage: ");
        formattedErrorInfo.append(errorInfo.errorMessage);
    }
    return formattedErrorInfo;
}
} // namespace

ErrorMessageManager& ErrorMessageManager::GetInstance()
{
    static ErrorMessageManager instance;
    return instance;
}

void ErrorMessageManager::SetErrorCodeAndMessage(ArkUI_Int32 errorCode, const char* errorMessage)
{
    auto& errorInfo = GetThreadLocalErrorInfo();
    errorInfo.errorCode = errorCode;
    errorInfo.errorMessage = (errorMessage != nullptr ? errorMessage : "");
    errorInfo.needRefresh = true;
}

void ErrorMessageManager::SetFunctionName(const char* functionName)
{
    auto& errorInfo = GetThreadLocalErrorInfo();
    errorInfo.functionName = (functionName != nullptr ? functionName : "");
    errorInfo.needRefresh = true;
}

const char* ErrorMessageManager::GetErrorMessage() const
{
    auto& errorInfo = GetThreadLocalErrorInfo();
    if (errorInfo.needRefresh) {
        errorInfo.formattedErrorInfo = ErrorInfoToString(errorInfo);
        errorInfo.needRefresh = false;
    }
    return errorInfo.formattedErrorInfo.c_str();
}
} // namespace OHOS::Ace
