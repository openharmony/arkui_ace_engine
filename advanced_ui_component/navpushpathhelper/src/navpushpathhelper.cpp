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

#include "native_engine/native_engine.h"

#include "napi/native_api.h"
#include "napi/native_node_api.h"
#include "advanced_ui_component/navpushpathhelper/include/hsp_silentinstall_napi.h"

extern const char _binary_navpushpathhelper_abc_start[];
extern const char _binary_navpushpathhelper_abc_end[];

namespace OHOS::NavPushPathHelper {
    /*
    * function for module exports
    */
    static napi_value Init(napi_env env, napi_value exports)
    {
        /*
        * Properties define
        */
        napi_property_descriptor desc[] = {
            DECLARE_NAPI_FUNCTION("silentInstall", HspSilentInstallNapi::SilentInstall),
            DECLARE_NAPI_FUNCTION("isHspExist", HspSilentInstallNapi::IsHspExist),
        };
        NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
        return exports;
    }

    // Napi get abc code function
    extern "C" __attribute__((visibility("default")))
    void NAPI_atomicservice_NavPushPathHelper_GetABCCode(const char **buf, int *buflen)
    {
        if (buf != nullptr) {
            *buf = _binary_navpushpathhelper_abc_start;
        }
        if (buflen != nullptr) {
            *buflen = _binary_navpushpathhelper_abc_end - _binary_navpushpathhelper_abc_start;
        }
    }

    /*
    * Module define
    */
    static napi_module NavPushPathHelperModule = {
        .nm_version = 1,
        .nm_flags = 0,
        .nm_filename = nullptr,
        .nm_register_func = Init,
        .nm_modname = "atomicservice.NavPushPathHelper",
        .nm_priv = ((void*)0),
        .reserved = { 0 },
    };

    /*
    * Module registerfunction
    */
    extern "C" __attribute__((constructor)) void NavPushPathHelperRegisterModule(void)
    {
        napi_module_register(&NavPushPathHelperModule);
    }
}