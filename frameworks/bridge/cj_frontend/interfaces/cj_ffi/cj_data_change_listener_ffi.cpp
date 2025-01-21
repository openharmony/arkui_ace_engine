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

void ParseOperation(OHOS::Ace::V2::Operation& operation, CJNativeOperation nativeOperation)
{
    if (std::string(nativeOperation.type) == "add") {
        operation.type = "add";
        operation.index = nativeOperation.index;
        operation.count = nativeOperation.count;
        if (nativeOperation.keyList.size > 0) {
            for (size_t i = 0; i < static_cast<size_t>(nativeOperation.keyList.size); i++) {
                operation.keyList.push_back(std::string(nativeOperation.keyList.head[i]));
            }
        } else {
            operation.key = nativeOperation.key;
        }
        return;
    }
    if (std::string(nativeOperation.type) == "change") {
        operation.type = "change";
        operation.index = nativeOperation.index;
        operation.key = nativeOperation.key;
        return;
    }

    if (std::string(nativeOperation.type) == "delete") {
        operation.type = "delete";
        operation.index = nativeOperation.index;
        operation.count = nativeOperation.count;
        return;
    }
    if (std::string(nativeOperation.type) == "move") {
        operation.type = "move";
        operation.coupleIndex = std::pair(nativeOperation.coupleFromIndex, nativeOperation.coupleToIndex);
        operation.key = nativeOperation.key;
        return;
    }
    if (std::string(nativeOperation.type) == "exchange") {
        operation.type = "exchange";
        operation.coupleIndex = std::pair(nativeOperation.coupleFromIndex, nativeOperation.coupleToIndex);
        operation.coupleKey = std::pair(nativeOperation.coupleFromKey, nativeOperation.coupleToKey);
        return;
    }
    operation.type = "reload";
    return;
}

void FfiFrameworkDataChangeListenerOnDataSetChanged(int64_t listenerId, NativeOperation operations)
{
    auto listener = FFIData::GetData<CJDataChangeListener>(listenerId);
    if (listener == nullptr) {
        return;
    }

    if (operations.cjNativeOperation == nullptr || operations.size == 0) {
        return;
    }

    std::list<OHOS::Ace::V2::Operation> dataOperations;

    for (int64_t i = 0; i < operations.size; i++) {
        OHOS::Ace::V2::Operation operation;
        CJNativeOperation nativeOperation = operations.cjNativeOperation[i];
        ParseOperation(operation, nativeOperation);
        dataOperations.emplace_back(operation);
    }
    listener->OnDataSetChanged(dataOperations);
    return;
}
}
