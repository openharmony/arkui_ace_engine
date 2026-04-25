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

#include "error_message_manager.h"

#define SET_ERROR_CODE_AND_MESSAGE_IN_BACKEND(errorCode, errorMessage)                      \
    do {                                                                                    \
        ErrorMessageManager::GetInstance().SetErrorCodeAndMessage(errorCode, errorMessage); \
    } while (0)

#endif // ARKUI_ERROR_MESSAGE_MACROS_H
