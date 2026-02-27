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

#include "native_api.h"

#ifdef __cplusplus
extern "C" {
#endif

napi_status napi_create_ark_context(napi_env env, napi_env* newEnv)
{
    if (newEnv == nullptr) {
        return napi_invalid_arg;
    }
    *newEnv = env;
    return napi_ok;
}

napi_status napi_switch_ark_context(napi_env env)
{
    return napi_ok;
}

napi_status napi_destroy_ark_context(napi_env env)
{
    return napi_ok;
}

napi_status napi_create_external_string_utf16(napi_env env, const char16_t* str, size_t length,
    napi_finalize_callback finalize_callback, void* finalize_hint, napi_value* result)
{
    if (result == nullptr) {
        return napi_invalid_arg;
    }
    return napi_ok;
}

#ifdef __cplusplus
}
#endif
