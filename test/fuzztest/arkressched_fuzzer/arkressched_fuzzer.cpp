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

#include "arkressched_fuzzer.h"

#include "base/ressched/ressched_report.h"

namespace OHOS::Ace {
constexpr uint32_t u16m = 65535;
using namespace std;
    void veryfi(string& s, const uint8_t* data, size_t size)
    {
        bool ok = true;
        auto ri = size % u16m;
        for (size_t i = 0; i < ri; i++) {
            if ((data[i] < '0' || data[i] > '9') && (data[i] < 'a' || data[i] > 'z')) {
                ok = false;
                break;
            }
        }
        if (ri == 0 || ok == false) {
            s = "123";
            return;
        }
        s = string(reinterpret_cast<const char*>(data), ri);
    }
    
    bool DoSomethingInterestingWithMyAPI(const uint8_t* data, size_t size)
    {
        bool result = false;
        string s;
        auto& resch = ResSchedReport::GetInstance();
        veryfi(s, data, size);
        resch.ResSchedDataReport(s.c_str());
        resch.ResSchedDataReport(1);
        ResSchedReportScope(s.c_str());
        resch.OnTouchEvent(TouchType::DOWN);
        return result;
    }
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::Ace::DoSomethingInterestingWithMyAPI(data, size);
    return 0;
}

