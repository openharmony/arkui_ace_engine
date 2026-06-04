/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "base/utils/time_util.h"

namespace OHOS::Ace {
int64_t GetSysTimestamp()
{
    static int64_t timestamp = 0;
    return ++timestamp;
}

int64_t GetCurrentTimestampMicroSecond()
{
    static int64_t timestamp = 0;
    return ++timestamp;
}

int64_t GetCurrentTimestamp()
{
    static int64_t timestamp = 0;
    return ++timestamp;
}

int64_t GetMicroTickCount()
{
    static int64_t tick = 0;
    return ++tick;
}
} // namespace OHOS::Ace
