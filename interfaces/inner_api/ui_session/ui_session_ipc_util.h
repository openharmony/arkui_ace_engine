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

#ifndef FOUNDATION_ACE_INTERFACE_UI_SESSION_IPC_UTIL_H
#define FOUNDATION_ACE_INTERFACE_UI_SESSION_IPC_UTIL_H

#include <cstddef>
#include <cstdint>
#include <string>

namespace OHOS {
class MessageParcel;
}

namespace OHOS::Ace::UiSessionIpcUtil {
constexpr size_t DEFAULT_ASHMEM_THRESHOLD = 64 * 1024;

bool WriteLargeString(MessageParcel& data, uint32_t transactionCode, const std::string& text, const char* caller);
bool ReadLargeString(MessageParcel& data, std::string& text, const char* caller);
bool WriteStringWithAshmemFlag(MessageParcel& data, uint32_t transactionCode, const std::string& text, const char* caller,
    size_t threshold = DEFAULT_ASHMEM_THRESHOLD);
bool ReadStringWithAshmemFlag(MessageParcel& data, std::string& text, const char* caller);
} // namespace OHOS::Ace::UiSessionIpcUtil

#endif // FOUNDATION_ACE_INTERFACE_UI_SESSION_IPC_UTIL_H
