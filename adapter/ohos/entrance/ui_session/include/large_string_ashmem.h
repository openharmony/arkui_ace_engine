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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_LARGE_STRING_ASHMEM_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_LARGE_STRING_ASHMEM_H

#include "ashmem.h"
#include "parcel.h"

namespace OHOS::Ace {
class LargeStringAshmem final : public Parcelable {
public:
    LargeStringAshmem() = default;
    ~LargeStringAshmem() override;

    bool WriteToAshmem(std::string name, std::string content, int32_t size);
    bool ReadFromAshmem(std::string& content);

    bool Marshalling(Parcel& parcel) const override;
    static LargeStringAshmem* Unmarshalling(Parcel& parcel);

private:
    bool ReadFromParcel(Parcel& parcel);
    void ClearAshmem();

    sptr<Ashmem> ashmem_;
    int32_t stringSize_ = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_LARGE_STRING_ASHMEM_H
