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

#ifndef FRAMEWORKS_BRIDGE_COMMON_MODULE_BUFFER_READER_H
#define FRAMEWORKS_BRIDGE_COMMON_MODULE_BUFFER_READER_H

#include <functional>
#include <string>

#include "base/utils/singleton.h"

namespace OHOS::Ace::Framework {

class ModuleBufferReader : public Singleton<ModuleBufferReader> {
    DECLARE_SINGLETON(ModuleBufferReader);
    ACE_DISALLOW_MOVE(ModuleBufferReader);

public:
    void SetBufferReaderImpl(
        const std::function<bool(const std::string& request, uint8_t** buffer, size_t* bufferSize)>& impl)
    {
        impl_ = impl;
    }

    bool ReadModuleBuffer(const std::string& request, uint8_t** buffer, size_t* bufferSize)
    {
        if (impl_) {
            return impl_(request, buffer, bufferSize);
        }
        return false;
    }

private:
    std::function<bool(const std::string& request, uint8_t** buffer, size_t* bufferSize)> impl_;
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_COMMON_MODULE_BUFFER_READER_H
