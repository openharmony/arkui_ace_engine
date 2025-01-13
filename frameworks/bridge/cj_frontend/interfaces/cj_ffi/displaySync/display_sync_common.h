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

#ifndef CJFFI_DISPLAY_SYNC_COMMON_H
#define CJFFI_DISPLAY_SYNC_COMMON_H

#include "cj_common_ffi.h"

namespace OHOS::DisplaySync {
typedef struct {
    int64_t timestamp;
    int64_t targetTimestamp;
} CIntervalInfo;

typedef struct {
    int32_t min = 60;
    int32_t max = 60;
    int32_t expected = 60;
} CFrameRateRange;
} // namespace OHOS::DisplaySync
#endif
