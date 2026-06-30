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

#include "interfaces/inner_api/ui_session/ui_session_ipc_util.h"

#include "adapter/ohos/entrance/ui_session/include/large_string_ashmem.h"
#include "adapter/ohos/entrance/ui_session/include/ui_session_log.h"
#include "message_parcel.h"

namespace OHOS::Ace::UiSessionIpcUtil {
bool WriteLargeString(MessageParcel& data, uint32_t transactionCode, const std::string& text, const char* caller)
{
    sptr<LargeStringAshmem> largeStringAshmem(new (std::nothrow) LargeStringAshmem());
    if (largeStringAshmem == nullptr) {
        LOGW("%{public}s alloc shmem failed", caller);
        return false;
    }
    if (!largeStringAshmem->WriteToAshmem(std::to_string(transactionCode), text, static_cast<int32_t>(text.length()))) {
        LOGW("%{public}s write to shmem failed, length=%{public}zu", caller, text.length());
        return false;
    }
    if (!data.WriteParcelable(largeStringAshmem.GetRefPtr())) {
        LOGW("%{public}s write shmem parcel failed", caller);
        return false;
    }
    return true;
}

bool ReadLargeString(MessageParcel& data, std::string& text, const char* caller)
{
    sptr<LargeStringAshmem> largeStringAshmem = data.ReadParcelable<LargeStringAshmem>();
    if (!largeStringAshmem) {
        LOGW("%{public}s read LargeStringAshmem failed", caller);
        return false;
    }
    if (!largeStringAshmem->ReadFromAshmem(text)) {
        LOGW("%{public}s read ashmem text failed", caller);
        return false;
    }
    return true;
}

bool WriteStringWithAshmemFlag(
    MessageParcel& data, uint32_t transactionCode, const std::string& text, const char* caller, size_t threshold)
{
    bool useAshmem = text.length() >= threshold;
    if (!data.WriteBool(useAshmem)) {
        LOGW("%{public}s write ashmem flag failed", caller);
        return false;
    }
    if (useAshmem) {
        return WriteLargeString(data, transactionCode, text, caller);
    }
    if (!data.WriteString(text)) {
        LOGW("%{public}s write text failed, length=%{public}zu", caller, text.length());
        return false;
    }
    return true;
}

bool ReadStringWithAshmemFlag(MessageParcel& data, std::string& text, const char* caller)
{
    bool useAshmem = data.ReadBool();
    if (useAshmem) {
        return ReadLargeString(data, text, caller);
    }
    text = data.ReadString();
    return true;
}
} // namespace OHOS::Ace::UiSessionIpcUtil
