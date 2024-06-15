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
#include "../include/api_policy_adapter.h"

using namespace std;

extern const char _binary_atomicserviceweb_js_start[];
extern const char _binary_atomicserviceweb_js_end[];
extern const char _binary_atomicserviceweb_abc_start[];
extern const char _binary_atomicserviceweb_abc_end[];

namespace HMS::AtomicServiceWeb {
    static napi_value CheckUrl(napi_env env, napi_callback_info info)
    {
        size_t requireArgc = 3;
        size_t argc = 3;
        napi_value args[3] = { nullptr };
        NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
    
        NAPI_ASSERT(env, argc >= requireArgc, "Wrong number of arguments");
    
        napi_valuetype valuetype0;
        NAPI_CALL(env, napi_typeof(env, args[0], &valuetype0));
    
        napi_valuetype valuetype1;
        NAPI_CALL(env, napi_typeof(env, args[1], &valuetype1));
        
        napi_valuetype valuetype2;
        NAPI_CALL(env, napi_typeof(env, args[2], &valuetype2));
    
        NAPI_ASSERT(env, valuetype0 == napi_string && valuetype1 == napi_string && valuetype2 == napi_string, "Wrong argument type. String expected.");
    
        size_t maxValueLen = 1024;
        char value0[maxValueLen];
        size_t length0 = 0;
        napi_get_value_string_utf8(env, args[0], value0, maxValueLen, &length0);
        std::string strValue0 = value0;

        char value1[maxValueLen];
        size_t length1 = 0;
        napi_get_value_string_utf8(env, args[1], value1, maxValueLen, &length1);
        std::string strValue1 = value1;

        char value2[maxValueLen];
        size_t length2 = 0;
        napi_get_value_string_utf8(env, args[2], value2, maxValueLen, &length2);
        std::string strValue2 = value2;

        auto apiPolicyAdapter = new ApiPolicyAdapter();
        int32_t res = apiPolicyAdapter->CheckUrl(strValue0, strValue1, strValue2);
        
        napi_value result;
        NAPI_CALL(env, napi_create_double(env, res, &result));
        return result;
    }

    static napi_value Init(napi_env env, napi_value exports)
    {
        napi_property_descriptor desc[] = {
            DECLARE_NAPI_FUNCTION("checkUrl", CheckUrl),
        };
        NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
        return exports;
    }

    // Napi get js code function
    extern "C" __attribute__((visibility("default")))
    void NAPI_atomicservice_AtomicServiceWeb_GetJSCode(const char **buf, int *buflen)
    {
        if (buf != nullptr) {
            *buf = _binary_atomicserviceweb_js_start;
        }
        if (buflen != nullptr) {
            *buflen = _binary_atomicserviceweb_js_end - _binary_atomicserviceweb_js_start;
        }
    }

    // Napi get abc code function
    extern "C" __attribute__((visibility("default")))
    void NAPI_atomicservice_AtomicServiceWeb_GetABCCode(const char **buf, int *buflen)
    {
        if (buf != nullptr) {
            *buf = _binary_atomicserviceweb_abc_start;
        }
        if (buflen != nullptr) {
            *buflen = _binary_atomicserviceweb_abc_end - _binary_atomicserviceweb_abc_start;
        }
    }
    
    /*
     * Module define
     */
    static napi_module AtomicServiceWebModule = {
        .nm_version = 1,
        .nm_flags = 0,
        .nm_filename = nullptr,
        .nm_register_func = Init,
        .nm_modname = "atomicservice.AtomicServiceWeb",
        .nm_priv = ((void*)0),
        .reserved = { 0 },
    };
    
    /*
     * Module registerfunction
     */
    extern "C" __attribute__((constructor)) void AtomicServiceWebRegisterModule(void)
    {
        napi_module_register(&AtomicServiceWebModule);
    }
}
