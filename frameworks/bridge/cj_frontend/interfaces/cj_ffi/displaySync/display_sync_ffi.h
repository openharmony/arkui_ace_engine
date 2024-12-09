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
#ifndef CJFFI_DISPLAY_SYNC_FFI_H
#define CJFFI_DISPLAY_SYNC_FFI_H

#include <cstdint>

#include "cj_common_ffi.h"
#include "display_sync_common.h"
#include "ffi_remote_data.h"

namespace OHOS {
namespace DisplaySync {

extern "C" {
    FFI_EXPORT int64_t FfiDisplaySyncCreate(int32_t* errCode);
    FFI_EXPORT int32_t FfiDisplaySyncSetExpectedFrameRateRange(int64_t id, CFrameRateRange rateRange);
    FFI_EXPORT int32_t FfiDisplaySyncOn(int64_t id, char* type, void (*callback)(CIntervalInfo));
    FFI_EXPORT int32_t FfiDisplaySyncOff(int64_t id, char* type, void (*callback)(CIntervalInfo));
    FFI_EXPORT int32_t FfiDisplaySyncStart(int64_t id);
    FFI_EXPORT int32_t FfiDisplaySyncStop(int64_t id);
}
} // namespace DisplaySync
} // namespace OHOS

#endif
