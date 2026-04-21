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

#ifndef MOCK_OHOS_THIRD_PARTY_NODE_NODE_API_H
#define MOCK_OHOS_THIRD_PARTY_NODE_NODE_API_H

#include "js_native_api.h"

// Minimal node_api types for ace_kit_test
struct uv_loop_s; // Forward declaration

#ifdef __cplusplus
extern "C" {
#endif

// Basic types - keeping minimal for ace_kit_test needs
typedef napi_value (*napi_addon_register_func)(napi_env env, napi_value exports);

typedef struct napi_module {
    int nm_version;
    unsigned int nm_flags;
    const char* nm_filename;
    napi_addon_register_func nm_register_func;
    const char* nm_modname;
    void* nm_priv;
    void* reserved[4];
} napi_module;

#define NODE_MODULE_VERSION 1

#ifdef __cplusplus
}
#endif

#endif // MOCK_OHOS_THIRD_PARTY_NODE_NODE_API_H
