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

#ifndef API_POLICY_ADAPTER_H
#define API_POLICY_ADAPTER_H

#include "string"
#ifndef __WIN32
#include <dlfcn.h>
#endif

class ApiPolicyAdapter {
public:
    ApiPolicyAdapter();
    ~ApiPolicyAdapter();

    int32_t CheckUrl(const std::string& bundleName, const std::string& domainType, const std::string& url);

    using CheckUrlFunc = int32_t (*)(const std::string&, const std::string&, const std::string&);
    void SetCheckUrlFunc(CheckUrlFunc& func);

private:
    void *handle = nullptr;
    CheckUrlFunc func = nullptr;
};

#endif
