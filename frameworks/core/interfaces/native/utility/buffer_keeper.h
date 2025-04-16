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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_BUFFER_KEEPER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_BUFFER_KEEPER_H

#pragma once

#include "base/log/log_wrapper.h"
#include "core/interfaces/native/utility/base_keeper.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

namespace OHOS::Ace::NG {

class BufferKeeper : public BaseKeeper<std::vector<char>> {
public:
    static Ark_Buffer Allocate(size_t size)
    {
        Ark_Buffer result {
            .resource = GetNextResource(),
            .length = size
        };

        // register data
        auto& entry = storage_[result.resource.resourceId];
        entry.counter = 1;
        entry.data.resize(size);
        result.data = entry.data.data();
        return result;
    }
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_BUFFER_KEEPER_H