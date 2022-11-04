/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "res_fuzzer.h"
#include "json_util.h"
#include <string>

namespace OHOS {
    using namespace OHOS::Ace;
    bool DoSomethingInterestingWithMyAPI(const uint8_t* data, size_t size)
    {
        bool result = false;
        auto r = JsonUtil::Create(true);
        auto r1 = JsonUtil::Create(false);
        std::string s= (char*)data;
        JsonUtil::ParseJsonString(s);
        JsonUtil::ParseJsonString(s.c_str());
        JsonUtil::CreateArray(true);
        JsonUtil::CreateArray(false);
        r->Put("123",111); 
        r->Replace("1234", false);
        r->Replace("123", 123);
        return result;
    }
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::DoSomethingInterestingWithMyAPI(data, size);
    return 0;
}

