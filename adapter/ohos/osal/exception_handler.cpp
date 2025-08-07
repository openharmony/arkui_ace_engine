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

#include "base/log/exception_handler.h"

#include "app_mgr_client.h"
#include "application_data_manager.h"

#include "core/common/ace_application_info.h"

namespace OHOS::Ace {
static void KillApplicationByUid()
{
    auto appMgrClient = std::make_unique<AppExecFwk::AppMgrClient>();
    CHECK_NULL_VOID(appMgrClient);
    auto result = appMgrClient->ConnectAppMgrService();
    if (result != AppExecFwk::AppMgrResultCode::RESULT_OK) {
        LOGE("failed to ConnectAppMgrService %{public}d", result);
        return;
    }
    auto ret = appMgrClient->KillApplicationSelf();
    if (ret != AppExecFwk::AppMgrResultCode::RESULT_OK) {
        LOGE("Fail to kill application by uid. %{public}d", ret);
        return;
    }
}

void ExceptionHandler::HandleJsException(
    const std::string& exceptionMsg, const JsErrorObject& errorInfo)
{
    AppExecFwk::ErrorObject errorObject = {
        .name = errorInfo.name,
        .message = errorInfo.message,
        .stack = errorInfo.stack
    };
    auto hasErrorObserver = AppExecFwk::ApplicationDataManager::GetInstance().NotifyUnhandledException(exceptionMsg);
    auto isNotifySuccess = AppExecFwk::ApplicationDataManager::GetInstance().NotifyExceptionObject(errorObject);
    if (!hasErrorObserver && !isNotifySuccess) {
        KillApplicationByUid();
    }
}
} // namespace OHOS::Ace
