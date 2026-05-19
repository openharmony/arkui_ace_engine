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

#include "interfaces/native/native_error_message_wrapper.h"
#include "core/interfaces/native/utility/error_message_manager.h"

namespace OHOS::Ace {
void SetErrorCodeAndMessageByModifier(ArkUI_Int32 errorCode, const char* errorMessage)
{
    (void)errorCode;
    (void)errorMessage;
    return;
}
void SetErrorFunctionNameByModifier(const char* functionName)
{
    (void)functionName;
    return;
}

void SetErrorMessageByModifier(ArkUI_Int32 errorCode, const char* functionName, const char* errorMessage)
{
    OHOS::Ace::ErrorMessageManager::GetInstance().SetErrorCodeAndMessage(errorCode, errorMessage);
    OHOS::Ace::ErrorMessageManager::GetInstance().SetFunctionName(functionName);
    return;
}
} // namespace OHOS::Ace
