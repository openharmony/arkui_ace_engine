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

#include "api_policy_adapter.h"

ApiPolicyAdapter::ApiPolicyAdapter()
{
#ifndef __WIN32
    handle = dlopen("/system/lib64/platformsdk/libapipolicy_client.z.so", RTLD_NOW);
    if (!handle) {
        return;
    }
    func = reinterpret_cast<CheckUrlFunc>(dlsym(handle, "CheckUrl"));
#endif
}

ApiPolicyAdapter::~ApiPolicyAdapter()
{
#ifndef __WIN32
    if (handle) {
        dlclose(handle);
        handle = nullptr;
    }
#endif
}

int32_t ApiPolicyAdapter::CheckUrl(const std::string& bundleName, const std::string& domainType, const std::string& url)
{
    int32_t res = 0;
    if (func == nullptr) {
        return res;
    }
    res = func(bundleName, domainType, url);
    return res;
}
