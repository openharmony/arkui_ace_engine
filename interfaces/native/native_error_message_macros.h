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

#ifndef NATIVE_ARKUI_ERROR_MESSAGE_MACROS_H
#define NATIVE_ARKUI_ERROR_MESSAGE_MACROS_H

#include "native_error_message_wrapper.h"

namespace OHOS::Ace {

} // namespace OHOS::Ace

#define CHECK_NULL_RETURN_WITH_MESSAGE(ptr, errorCode, functionName, errorMessage) \
    do {                                                                           \
        if (!(ptr)) {                                                              \
            OHOS::Ace::SetErrorMessageByModifier(errorCode, functionName, errorMessage); \
            return errorCode;                                                      \
        }                                                                          \
    } while (0)

#define SET_ERROR_MESSAGE(errorCode, functionName, errorMessage)                      \
    do {                                                                              \
        OHOS::Ace::SetErrorMessageByModifier(errorCode, functionName, errorMessage); \
    } while (0)

#define SET_ERROR_CODE_AND_MESSAGE(errorCode, errorMessage)                  \
    do {                                                                     \
        OHOS::Ace::SetErrorCodeAndMessageByModifier(errorCode, errorMessage); \
    } while (0)

#define SET_ERROR_FUNCTION_NAME(functionName)                       \
    do {                                                            \
        OHOS::Ace::SetErrorFunctionNameByModifier(functionName);    \
    } while (0)

#endif // NATIVE_ARKUI_ERROR_MESSAGE_MACROS_H
