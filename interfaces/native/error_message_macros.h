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

#ifndef ARKUI_ERROR_MESSAGE_MACROS_H
#define ARKUI_ERROR_MESSAGE_MACROS_H

#include <memory>

#include "error_message_manager.h"

#define CHECK_NULL_RETURN_WITH_MESSAGE(ptr, errorCode, functionName, errorMessage) \
    do {                                                                           \
        if (!(ptr)) {                                                              \
            OHOS::Ace::ErrorMessageManager::GetInstance().SetLastError(            \
                ArkUIErrorInfo { errorCode, functionName, errorMessage });         \
            return errorCode;                                                      \
        }                                                                          \
    } while (0)

#define SET_ERROR_MESSAGE(errorCode, functionName, errorMessage)       \
    do {                                                               \
        OHOS::Ace::ErrorMessageManager::GetInstance().SetLastError(    \
            ArkUIErrorInfo { errorCode, functionName, errorMessage }); \
    } while (0)

namespace OHOS::Ace {
inline void SetErrorInfoFromErrorInfoPtr(ArkUI_Int32 errorCode, void* errorInfoPtr, const char* errorMessage)
{
    auto* realPtr = reinterpret_cast<std::shared_ptr<ArkUIErrorInfo>*>(errorInfoPtr);
    if (!realPtr || !(*realPtr)) {
        return;
    }
    auto& errorInfo = *realPtr;
    errorInfo->errorCode = errorCode;
    errorInfo->errorMessage = (errorMessage != nullptr ? errorMessage : "");
}
} // namespace OHOS::Ace

#endif // ARKUI_ERROR_MESSAGE_MACROS_H
