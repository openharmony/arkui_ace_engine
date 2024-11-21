/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef ADVANCED_UI_COMPONENT_NAVPUSHPATHHELPER_INCLUDE_HSP_SILENT_INSTALL_NAPI_H
#define ADVANCED_UI_COMPONENT_NAVPUSHPATHHELPER_INCLUDE_HSP_SILENT_INSTALL_NAPI_H

#include "native_engine/native_engine.h"

#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS::NavPushPathHelper {
class HspSilentInstallNapi {
    public:
        static napi_value SilentInstall(napi_env env, napi_callback_info info);
        static napi_value IsHspExist(napi_env env, napi_callback_info info);
        static napi_value InitRouteMap(napi_env env, napi_callback_info info);

    private:
        struct CallbackData {
            napi_env env = nullptr;
            int32_t errCode = 0;
            std::string errorMessage;
            napi_ref successCallback = nullptr;
            napi_ref failCallback = nullptr;

            ~CallbackData()
            {
                if (this->successCallback != nullptr) {
                    napi_delete_reference(this->env, this->successCallback);
                    this->successCallback = nullptr;
                }
                if (this->failCallback != nullptr) {
                    napi_delete_reference(this->env, this->failCallback);
                    this->failCallback = nullptr;
                }
            }
        };

        static void SendSuccessBackWork(uv_work_t *work, int statusIn);
        static void SendFailBackWork(uv_work_t *work, int statusIn);
        static napi_value CreateResultMessage(CallbackData *callbackData);
        static napi_value getModuleName(napi_env env, napi_value args, std::string& moduleName);
};
}

#endif