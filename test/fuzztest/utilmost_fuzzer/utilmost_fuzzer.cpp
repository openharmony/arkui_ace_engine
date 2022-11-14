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

#include <string>

#include "json_util.h"
#include "resource_configuration.h"
#include "string_expression.h"
#include "utilmost_fuzzer.h"

#include "frameworks/base/memory/ace_type.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS {
using namespace OHOS::Ace;
using namespace std;
constexpr uint32_t u16m = 65535;


bool DoSomethingInterestingWithMyAPI(const uint8_t* data, size_t size)
{
    bool result = false;
    auto ri = size % u16m;
    std::string s(reinterpret_cast<const char*>(data), ri);
    if (s.size() == 0 || s[s.size() - 1] != '\0') {
        return result;
    }
    Framework::CreateCurve(s);
    // 111 Framework::CreateClipPath(s);
    // 222 Framework::ParseRadialGradientSize(s);
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
