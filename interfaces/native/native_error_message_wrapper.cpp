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
#include "native_error_message_wrapper.h"
#include "interfaces/native/node/node_model.h"

namespace OHOS::Ace {

void SetErrorCodeAndMessageByModifier(ArkUI_Int32 errorCode, const char* errorMessage)
{
    auto* impl = NodeModel::GetFullImplForErrorMessage();
    if (impl == nullptr) {
        return;
    }
    impl->getBasicAPI()->setErrorCodeAndMessage(
        errorCode, const_cast<char*>(errorMessage != nullptr ? errorMessage : ""));
}

void SetErrorFunctionNameByModifier(const char* functionName)
{
    auto* impl = NodeModel::GetFullImplForErrorMessage();
    if (impl == nullptr) {
        return;
    }
    impl->getBasicAPI()->setErrorFunctionName(const_cast<char*>(functionName != nullptr ? functionName : ""));
}

void SetErrorMessageByModifier(ArkUI_Int32 errorCode, const char* functionName, const char* errorMessage)
{
    SetErrorCodeAndMessageByModifier(errorCode, errorMessage);
    SetErrorFunctionNameByModifier(functionName);
}
} // namespace OHOS::Ace