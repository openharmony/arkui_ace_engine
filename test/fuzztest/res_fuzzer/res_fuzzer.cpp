/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <string>

#include "cJSON.h"
#include "base/json/json_util.h"
#include "bridge/common/dom/dom_type.h"

const uint32_t u16m = 65535;

namespace OHOS {
using namespace OHOS::Ace;
using namespace std;
void vfi(std::string& s);
string jack = "jack";
string tom = "tom";
string kal = "kal";
string kel = "kel";
string kol = "kol";
constexpr int32_t vol1 = 0;
constexpr int32_t vol2 = 1;
bool DoSomethingInterestingWithMyAPI(const uint8_t* data, size_t size)
{
    bool result = false;
    auto r = JsonUtil::Create(true);
    double point = 2.0;
    int64_t i64 = 0;
    size_t li = 0;
    auto ri = size % u16m;
    std::string s (reinterpret_cast<const char*>(data), ri);
    vfi(s);
    JsonUtil::ParseJsonString(s);
    JsonUtil::ParseJsonString(s.c_str());
    r->Put(jack.c_str(), vol1);
    r->Replace(jack.c_str(), false);
    r->Replace(jack.c_str(), vol2);
    r->GetString(jack);
    r->GetUInt(jack);
    r->GetDouble(jack);
    r->Replace(jack.c_str(), tom.c_str());
    r->Replace(kel.c_str(), point);
    r->Put(kal.c_str(), i64);
    r->Put(kal.c_str(), li);
    r->Delete(jack.c_str());
    r->GetObject(kal);
    r->GetBool(kal);
    r->Replace(kal.c_str(), false);
    r->Delete(kal.c_str());
    return result;
}

void vfi(std::string& s)
{
    s = "{ key:123 }";
}
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::DoSomethingInterestingWithMyAPI(data, size);
    return 0;
}