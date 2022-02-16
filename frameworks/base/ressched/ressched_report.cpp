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

#include "base/ressched/ressched_report.h"

namespace OHOS::Ace {
namespace {
    const uint32_t RES_TYPE_CLICK_RECOGNIZE = 9;
}

ResSchedReport& ResSchedReport::GetInstance()
{
    static ResSchedReport instance;
    return instance;
}

void ResSchedReport::ResSchedDataReport(const char* name)
{
    if (reportDataFunc == nullptr) {
        reportDataFunc = LoadReportDataFunc();
    }
    if (reportDataFunc != nullptr) {
        if (strcmp(name, "click") == 0) {
            reportDataFunc(RES_TYPE_CLICK_RECOGNIZE, 0, name);
        }
    }
}
} // namespace OHOS::Ace