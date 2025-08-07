/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "base/utils/cpu_boost.h"

#ifdef FFRT_CPUBOOST_EN
#include "c/ffrt_cpu_boost.h"
#endif

namespace OHOS::Ace {
void FlushDirtyNodeCpuBoostOperate(bool flag)
{
#ifdef FFRT_CPUBOOST_EN
    if (flag == true) {
        ffrt_cpu_boost_start(CPUBOOST_START_POINT);
    } else {
        ffrt_cpu_boost_end(CPUBOOST_START_POINT);
    }
#endif
}

void DisplaysyncCpuBoostOperate(bool flag)
{
#ifdef FFRT_CPUBOOST_EN
    if (flag == true) {
        ffrt_cpu_boost_start(CPUBOOST_START_POINT + 1);
    } else {
        ffrt_cpu_boost_end(CPUBOOST_START_POINT + 1);
    }
#endif
}
}
