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

#include "include/large_string_ashmem.h"

#include "message_parcel.h"

#include "adapter/ohos/entrance/ui_session/include/ui_session_log.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t MAX_ASHMEM_SIZE = 100 * 1024 * 1024; // 100M


} // namespace

LargeStringAshmem::~LargeStringAshmem()
{
    ClearAshmem();
}

bool LargeStringAshmem::Marshalling(Parcel& parcel) const
{
    MessageParcel* messageParcel = static_cast<MessageParcel*>(&parcel);
    if (!messageParcel->WriteAshmem(ashmem_)) {
        LOGW("LargeString WriteAshmem failed");
        return false;
    }
    return true;
}

bool LargeStringAshmem::ReadFromParcel(Parcel& parcel)
{
    MessageParcel* messageParcel = static_cast<MessageParcel*>(&parcel);
    ashmem_ = messageParcel->ReadAshmem();
    if (ashmem_ == nullptr) {
        LOGW("LargeString ReadFromParcel failed");
        return false;
    }
    return true;
}

LargeStringAshmem* LargeStringAshmem::Unmarshalling(Parcel& parcel)
{
    LargeStringAshmem* largeStringAshmem = new (std::nothrow) LargeStringAshmem();
    if (largeStringAshmem != nullptr && !largeStringAshmem->ReadFromParcel(parcel)) {
        delete largeStringAshmem;
        largeStringAshmem = nullptr;
    }
    return largeStringAshmem;
}

bool LargeStringAshmem::WriteToAshmem(std::string name, std::string content, int32_t size)
{
    if (size < 0 || size > MAX_ASHMEM_SIZE) {
        LOGW("LargeStringAshmem invalid size = %{public}d", size);
        return false;
    }
    ashmem_ = Ashmem::CreateAshmem(name.c_str(), size);
    if (ashmem_ == nullptr) {
        LOGW("LargeStringAshmem create shared memory fail");
        return false;
    }
    if (!ashmem_->MapReadAndWriteAshmem()) {
        LOGW("LargeStringAshmem map shared memory fail");
        ClearAshmem();
        return false;
    }
    int32_t offset = 0;
    if (!ashmem_->WriteToAshmem(content.c_str(), size, offset)) {
        LOGW("LargeStringAshmem write to shared memory fail");
        ClearAshmem();
        return false;
    }
    ashmem_->UnmapAshmem();
    return true;
}

bool LargeStringAshmem::ReadFromAshmem(std::string& content)
{
    if (ashmem_ == nullptr) {
        LOGW("LargeStringAshmem read shared memory fail");
        return false;
    }
    if (!ashmem_->MapReadOnlyAshmem()) {
        LOGW("LargeStringAshmem map readonly shared memory fail");
        ClearAshmem();
        return false;
    }
    int32_t ashmemSize = ashmem_->GetAshmemSize();
    int32_t offset = 0;
    const char* ashDataPtr = reinterpret_cast<const char*>(ashmem_->ReadFromAshmem(ashmemSize, offset));
    if (ashDataPtr == nullptr) {
        LOGW("LargeStringAshmem read ashData fail");
        ClearAshmem();
        return false;
    }
    content.assign(ashDataPtr, ashmemSize);
    ClearAshmem();
    return true;
}

void LargeStringAshmem::ClearAshmem()
{
    if (ashmem_ != nullptr) {
        ashmem_->UnmapAshmem();
        ashmem_->CloseAshmem();
    }
}
} // namespace OHOS::Ace
