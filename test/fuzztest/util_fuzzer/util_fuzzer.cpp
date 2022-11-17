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

#include "json_util.h"
#include "resource_configuration.h"
#include "string_expression.h"

namespace OHOS {

using namespace OHOS::Ace;

bool DoSomethingInterestingWithMyAPI(const uint8_t* data, size_t size)
{
    bool result = false;
    ResourceConfiguration r;
    uint32_t update = 0;
    std::string s;
    r.UpdateFromJsonString(s, update);
    return result;
}

void calc(const uint8_t* data, size_t size)
{
    double vpScale = 1;
    double fpScale = 1;
    double lpxScale = 1;
    double parentLength = 1;
    std::string s;
    StringExpression::CalculateExp(s, [vpScale, fpScale, lpxScale, parentLength](const Dimension& dim) -> double {
        double result = -1.0;
        dim.NormalizeToPx(vpScale, fpScale, lpxScale, parentLength, result);
        return result;
    });
}

} // namespace OHOS

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::DoSomethingInterestingWithMyAPI(data, size);
    OHOS::calc(data, size);
    return 0;
}
