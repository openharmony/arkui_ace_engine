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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_data_change_listener_ffi.h"

#include "bridge/cj_frontend/cppview/data_change_listener.h"

using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkDataChangeListenerOnDataReloaded(int64_t listenerId)
{
    auto listener = FFIData::GetData<CJDataChangeListener>(listenerId);
    if (listener == nullptr) {
        return;
    }
    listener->OnDataReloaded();
}

void FfiOHOSAceFrameworkDataChangeListenerOnDataAdded(int64_t listenerId, int64_t index)
{
    auto listener = FFIData::GetData<CJDataChangeListener>(listenerId);
    if (listener == nullptr) {
        return;
    }
    listener->OnDataAdded(static_cast<size_t>(index));
}

void FfiOHOSAceFrameworkDataChangeListenerOnDataDeleted(int64_t listenerId, int64_t index)
{
    auto listener = FFIData::GetData<CJDataChangeListener>(listenerId);
    if (listener == nullptr) {
        return;
    }
    listener->OnDataDeleted(static_cast<size_t>(index));
}

void FfiOHOSAceFrameworkDataChangeListenerOnDataChanged(int64_t listenerId, int64_t index)
{
    auto listener = FFIData::GetData<CJDataChangeListener>(listenerId);
    if (listener == nullptr) {
        return;
    }
    listener->OnDataChanged(static_cast<size_t>(index));
}

void FfiOHOSAceFrameworkDataChangeListenerOnDataMoved(int64_t listenerId, int64_t from, int64_t to)
{
    auto listener = FFIData::GetData<CJDataChangeListener>(listenerId);
    if (listener == nullptr) {
        return;
    }
    listener->OnDataMoved(static_cast<size_t>(from), static_cast<size_t>(to));
}
}
