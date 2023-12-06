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

#include "util_fuzzer.h"

#include <stddef.h>
#include <stdint.h>
#include <string>

#include "base/json/json_util.h"

#include "frameworks/base/memory/ace_type.h"
#include "frameworks/bridge/common/utils/source_map.h"

namespace OHOS {
using namespace OHOS::Ace;
using namespace std;
constexpr uint32_t u16m = 65535;
string appjsmap = "{\"version\":3,"
                             "\"file\":\"./pages/dfxtest.js\","
                             "\"mappings\":\";\","
                             "\"sources\":[],"
                             "\"names\":[\"_ohos_router_1\",\"router\",\"_ohos_process_1\",\"process\"]}";

bool DoSomethingInterestingWithMyAPI(const uint8_t* data, size_t size)
{
    bool result = false;
    uint32_t errorPos = 0;
    string s(reinterpret_cast<const char*>(data), size % u16m);
    std::vector<std::string> sourceKeyInfo;
    OHOS::Ace::Framework::RevSourceMap::ExtractKeyInfo(s, sourceKeyInfo);
    RefPtr<Framework::RevSourceMap> RevSourceMap = AceType::MakeRefPtr<Framework::RevSourceMap>();
    RevSourceMap->Init(appjsmap);
    RevSourceMap->GetOriginalNames(s, errorPos);
    return result;
}


} // namespace OHOS

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::DoSomethingInterestingWithMyAPI(data, size);
    return 0;
}
