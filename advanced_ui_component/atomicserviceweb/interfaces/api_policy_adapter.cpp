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

#include "../include/api_policy_adapter.h"
#include <dlfcn.h>

ApiPolicyAdapter::ApiPolicyAdapter()
{
    handle = dlopen("/system/lib64/platformsdk/libapipolicy_client.z.so", RTLD_NOW);
    if (!handle) {
        return;
    }
}

ApiPolicyAdapter::~ApiPolicyAdapter()
{
    if (handle) {
        dlclose(handle);
        handle = nullptr;
    }
}

int32_t ApiPolicyAdapter::CheckUrl(std::string bundleName, std::string domainType, std::string url)
{
    int32_t res = -1;
    using CheckUrl = int32_t (*)(std::string, std::string, std::string);
    auto func = reinterpret_cast<CheckUrl>(dlsym(handle, "CheckUrl"));
    if (func == nullptr) {
        return res;
    }
    res = func(bundleName, domainType, url);
    return res;
}
