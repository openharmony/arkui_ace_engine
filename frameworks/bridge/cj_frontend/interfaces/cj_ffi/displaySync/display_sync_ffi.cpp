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
#include "display_sync_ffi.h"

#include "cj_common_ffi.h"
#include "cj_lambda.h"
#include "core/components_ng/manager/display_sync/ui_display_sync.h"
#include "display_sync_error.h"
#include "display_sync_impl.h"
#include "interfaces/native/native_animate.h"

using namespace OHOS::FFI;
using namespace OHOS::DisplaySync;

namespace OHOS {
namespace DisplaySync {
extern "C" {
int64_t FfiDisplaySyncCreate(int32_t* errCode)
{
    *errCode = ERR_CJ_SUCCESS;
    auto nativeDisplaySync = FFIData::Create<DisplaySyncImpl>();
    if (!nativeDisplaySync) {
        *errCode = ERR_CJ_INNER_EXCEPTION;
        return 0;
    }
    return nativeDisplaySync->GetID();
}

int32_t FfiDisplaySyncSetExpectedFrameRateRange(int64_t id, CFrameRateRange rateRange)
{
    auto instance = FFIData::GetData<DisplaySyncImpl>(id);
    if (!instance) {
        return ERR_CJ_INNER_EXCEPTION;
    }
    return instance->SetExpectedFrameRateRange(rateRange);
}

int32_t FfiDisplaySyncOn(int64_t id, char* type, void (*callback)(CIntervalInfo))
{
    auto instance = FFIData::GetData<DisplaySyncImpl>(id);
    if (!instance) {
        return ERR_CJ_INNER_EXCEPTION;
    }
    return instance->On(type, callback);
}

int32_t FfiDisplaySyncOff(int64_t id, char* type, void (*callback)(CIntervalInfo))
{
    auto instance = FFIData::GetData<DisplaySyncImpl>(id);
    if (!instance) {
        return ERR_CJ_INNER_EXCEPTION;
    }
    return instance->Off(type, callback);
}

int32_t FfiDisplaySyncStart(int64_t id)
{
    auto instance = FFIData::GetData<DisplaySyncImpl>(id);
    if (!instance) {
        return ERR_CJ_INNER_EXCEPTION;
    }
    return instance->Start();
}

int32_t FfiDisplaySyncStop(int64_t id)
{
    auto instance = FFIData::GetData<DisplaySyncImpl>(id);
    if (!instance) {
        return ERR_CJ_INNER_EXCEPTION;
    }
    return instance->Stop();
}
}
}
}
