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

#ifndef ARKUI_ERROR_MESSAGE_MANAGER_H
#define ARKUI_ERROR_MESSAGE_MANAGER_H

#include <cstdint>
#include <string>

#include "ui/base/macros.h"
#include "core/interfaces/arkoala/arkoala_api.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT ErrorMessageManager {
public:
    static ErrorMessageManager& GetInstance();

    void SetLastError(ArkUIErrorInfo lastErrorInfo);

    const char* GetLastError() const;

private:
    ErrorMessageManager() = default;
    ~ErrorMessageManager() = default;
    ErrorMessageManager(const ErrorMessageManager&) = delete;
    ErrorMessageManager& operator=(const ErrorMessageManager&) = delete;
};


} // namespace OHOS::Ace

#endif // ARKUI_ERROR_MESSAGE_MANAGER_H