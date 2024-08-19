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

#include <memory>

#include "napi/native_node_api.h"
#include "api_policy_adapter.h"

using namespace std;

extern const char _binary_atomicserviceweb_abc_start[];
extern const char _binary_atomicserviceweb_abc_end[];

namespace HMS::AtomicServiceWeb {
    static napi_value CheckUrl(napi_env env, napi_callback_info info)
    {
        const int indexTwo = 2;
        size_t requireArgc = 3;
        size_t argc = 3;
        napi_value args[3] = { nullptr };
        NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
    
        NAPI_ASSERT(env, argc >= requireArgc, "Wrong number of arguments");
    
        napi_valuetype bundleNameType;
        NAPI_CALL(env, napi_typeof(env, args[0], &bundleNameType));
    
        napi_valuetype domainTypeType;
        NAPI_CALL(env, napi_typeof(env, args[1], &domainTypeType));
        
        napi_valuetype urlType;
        NAPI_CALL(env, napi_typeof(env, args[indexTwo], &urlType));
    
        NAPI_ASSERT(env, bundleNameType == napi_string && domainTypeType == napi_string && urlType == napi_string,
            "Wrong argument type. String expected.");
    
        size_t maxValueLen = 1024;
        char bundleNameValue[maxValueLen];
        size_t bundleNameLength = 0;
        napi_get_value_string_utf8(env, args[0], bundleNameValue, maxValueLen, &bundleNameLength);
        std::string bundleName = bundleNameValue;

        char domainTypeValue[maxValueLen];
        size_t domainTypeLength = 0;
        napi_get_value_string_utf8(env, args[1], domainTypeValue, maxValueLen, &domainTypeLength);
        std::string domainType = domainTypeValue;

        char urlValue[maxValueLen];
        size_t urlLength = 0;
        napi_get_value_string_utf8(env, args[indexTwo], urlValue, maxValueLen, &urlLength);
        std::string url = urlValue;

        std::shared_ptr<ApiPolicyAdapter> apiPolicyAdapter = std::make_shared<ApiPolicyAdapter>();
        int32_t res = apiPolicyAdapter->CheckUrl(bundleName, domainType, url);
        
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
