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

#ifndef FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_DATA_CHANGE_LISTENER_H
#define FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_DATA_CHANGE_LISTENER_H

#include <set>

#include "base/memory/referenced.h"
#include "ffi_remote_data.h"
#include "core/components_v2/foreach/lazy_foreach_component.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT CJDataChangeListener : public OHOS::FFI::FFIData {
DECL_TYPE(CJDataChangeListener, OHOS::FFI::FFIData)
public:
    CJDataChangeListener();
    void AddListener(const WeakPtr<V2::DataChangeListener>& listener);
    void RemoveListener(const WeakPtr<V2::DataChangeListener>& listener);
    void OnDataReloaded();
    void OnDataAdded(size_t index);
    void OnDataDeleted(size_t index);
    void OnDataChanged(size_t index);
    void OnDataMoved(size_t from, size_t to);
    void OnDataSetChanged(const std::list<V2::Operation>& dataOperations);

    template<class... Args>
    void NotifyAll(void (V2::DataChangeListener::*method)(Args...), Args... args)
    {
        ContainerScope scope(instanceId_);
        for (auto it = listeners_.begin(); it != listeners_.end();) {
            auto listener = it->Upgrade();
            if (!listener) {
                it = listeners_.erase(it);
                continue;
            }
            ++it;
            ((*listener).*method)(args...);
        }
    }

    template<class... Args>
    void NotifyAll(void (V2::DataChangeListener::*method)(Args...), const std::list<V2::Operation>& args)
    {
        ContainerScope scope(instanceId_);
        for (auto it = listeners_.begin(); it != listeners_.end();) {
            auto listener = it->Upgrade();
            if (!listener) {
                it = listeners_.erase(it);
                continue;
            }
            ++it;
            ((*listener).*method)(args);
        }
    }

private:
    std::set<WeakPtr<V2::DataChangeListener>> listeners_;
    int32_t instanceId_ = -1;
};
} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_CJ_FRONTEND_CPP_VIEW_DATA_CHANGE_LISTENER_H