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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_BASE_KEEPER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_BASE_KEEPER_H

#pragma once

#include <unordered_map>
#include "base/log/log_wrapper.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

namespace OHOS::Ace::NG {

template<typename ResourceDataT>
class BaseKeeper {
protected:
    struct ResourceData {
        int counter;
        ResourceDataT data;
    };
    typedef typename std::unordered_map<Ark_Int32, ResourceData> ResourceMapType;
    typedef typename ResourceMapType::iterator ResourceMapIteratorType;

    static void Hold(Ark_Int32 resourceId)
    {
        storage_[resourceId].counter++;
    }
    static inline void Hold(ResourceMapIteratorType it)
    {
        ++(it->second.counter);
    }

    static void Release(Ark_Int32 resourceId)
    {
        if (auto it = storage_.find(resourceId); it != storage_.end()) {
            Release(it);
        }
    }
    static inline void Release(ResourceMapIteratorType it)
    {
        if (--(it->second.counter) == 0) {
            storage_.erase(it);
        }
    }

    static Ark_CallbackResource GetNextResource()
    {
        return {
            .resourceId = ++currentId_,
            .hold = &Hold,
            .release = &Release
        };
    }
    inline static Ark_Int32 currentId_ = 0;
    inline static ResourceMapType storage_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_BASE_KEEPER_H