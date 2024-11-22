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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_foreach_ffi.h"

#include "cj_lambda.h"

#include "core/components_ng/syntax/for_each_model.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

extern "C" {
void FfiOHOSAceFrameworkForEachCreateFU(
    char* viewId, int64_t parentViewID, int64_t dataSize, ViewCallBack callbackView, IdCallBack callbackKey)
{
    std::function<void(int64_t)> ffiViewCallback = CJLambda::Create(callbackView);
    std::function<std::string(int64_t)> ffiKeyCallback = [callback = CJLambda::Create(callbackKey)](
                                                             int64_t info) -> std::string {
        auto ffiStr = callback(info);
        std::string res = ffiStr.value;
        ffiStr.free(ffiStr.value);
        return res;
    };
    auto* model = ForEachModel::GetInstance();
    model->Create();
    for (int64_t i = 0; i < dataSize; i++) {
        auto key = ffiKeyCallback(i);
        model->CreateNewChildStart(key);
        ffiViewCallback(i);
        model->CreateNewChildFinish(key);
    }
}

void FfiOHOSAceFrameworkForEachCreate()
{
    auto* model = ForEachModel::GetInstance();
    model->Create();
}

void FfiOHOSAceFrameworkForEachPop()
{
    ForEachModel::GetInstance()->Pop();
}

static void FfiOHOSAceFrameworkDeleteIdArray(VectorToCFFIArrayString* src)
{
    for (size_t i = 0; i < src->size; ++i) {
        free(src->buffer[i]);
    }
    free(src->buffer);
}

VectorToCFFIArrayString FfiOHOSAceFrameworkViewGetIdArray(int64_t elmtId)
{
    std::list<std::string> result = ForEachModel::GetInstance()->GetCurrentIdList(elmtId);

    auto buffer = (char**)malloc(sizeof(const char*) * result.size());
    if (!buffer) {
        return { .size = 0, .buffer = nullptr, .free = FfiOHOSAceFrameworkDeleteIdArray };
    }

    size_t i = 0;
    for (const auto& element : result) {
        auto data = (char*)malloc(element.size() * sizeof(char));
        if (data == nullptr) {
            for (size_t j = 0; j < result.size(); j++) {
                free(buffer[j]);
            }
            free(buffer);
            return { .size = 0, .buffer = nullptr, .free = FfiOHOSAceFrameworkDeleteIdArray };
        }
        std::char_traits<char>::copy(data, element.c_str(), element.size());
        buffer[i++] = data;
    }

    return { .size = result.size(), .buffer = buffer, .free = FfiOHOSAceFrameworkDeleteIdArray };
}

VectorToCFFIArray FfiOHOSAceFrameworkViewSetIdArray(int64_t elmtId, VectorCJStringHandle vecHandle)
{
    std::list<std::string> newIdArr;
    auto cjRectangleVec = reinterpret_cast<std::vector<std::string>*>(vecHandle);

    for (const auto& value : *cjRectangleVec) {
        newIdArr.emplace_back(value);
    }
    // Get old IDs. New ID are set in the end of this function.
    const std::list<std::string>& previousIDList = ForEachModel::GetInstance()->GetCurrentIdList(elmtId);
    std::unordered_set<std::string> oldIdsSet(previousIDList.begin(), previousIDList.end());
    // Get reference to output diff index array.
    std::vector<size_t> diffIndexArray;
    size_t index = 0;
    for (const auto& newId : newIdArr) {
        if (oldIdsSet.find(newId) == oldIdsSet.end()) {
            // Populate output diff array with this index that was not in old array.
            diffIndexArray.push_back(index);
        }
        index++;
    }

    ForEachModel::GetInstance()->SetNewIds(std::move(newIdArr));

    int64_t* temp = nullptr;
    temp = (int64_t*)malloc(sizeof(int64_t) * diffIndexArray.size());
    if (!temp) {
        VectorToCFFIArray faultData {
            .size = 0, .buffer = nullptr, .free = reinterpret_cast<void (*)(int64_t*)>(free)
        };
        return faultData;
    }

    VectorToCFFIArray res {
        .size = diffIndexArray.size(), .buffer = temp, .free = reinterpret_cast<void (*)(int64_t*)>(free)
    };

    for (size_t i = 0; i < diffIndexArray.size(); i++) {
        res.buffer[i] = static_cast<int64_t>(diffIndexArray[i]);
    }

    return res;
}

VectorToCFFIArray HandleFFIArray(const std::vector<size_t>& vec)
{
    VectorToCFFIArray ffiArray;
    ffiArray.size = vec.size();
    ffiArray.buffer = new int64_t[ffiArray.size];
    for (size_t i = 0; i < vec.size(); ++i) {
        ffiArray.buffer[i] = static_cast<int64_t>(vec[i]);
    }
    ffiArray.free = reinterpret_cast<void (*)(int64_t*)>(free);
    return ffiArray;
}

SetIdResultFFI AssambleSetIdResult(
    const std::vector<size_t>& diffIds, const std::vector<size_t>& dupIds, const std::vector<size_t>& remIds)
{
    VectorToCFFIArray diffArray = HandleFFIArray(diffIds);
    VectorToCFFIArray dupArray = HandleFFIArray(dupIds);
    VectorToCFFIArray remArray = HandleFFIArray(remIds);
    SetIdResultFFI result {
        .diffIndexArrayPtr = diffArray, .duplicateIdsPtr = dupArray, .removedChildElmtIdsPtr = remArray
    };
    return result;
}

SetIdResultFFI FfiOHOSAceFrameworkViewSetIdArrayReturnStruct(int64_t elmtId, VectorCJStringHandle newIdArray)
{
    std::list<std::string> cjArr;
    std::vector<size_t> diffIds;
    std::vector<size_t> dupIds;
    std::vector<size_t> remIds;
    std::list<std::string> newIdArr;

    auto cjRectangleVec = reinterpret_cast<std::vector<std::string>*>(newIdArray);
    for (const auto& value : *cjRectangleVec) {
        cjArr.emplace_back(value);
    }
    // Get old IDs. New ID are set in the end of this function.
    const std::list<std::string>& previousIDList = ForEachModel::GetInstance()->GetCurrentIdList(elmtId);
    std::unordered_set<std::string> oldIdsSet(previousIDList.begin(), previousIDList.end());
    std::unordered_set<std::string> newIds;

    size_t index = 0;
    for (const auto& strId : cjArr) {
        // Save return value of insert to know was it duplicate...
        std::pair<std::unordered_set<std::string>::iterator, bool> ret = newIds.insert(strId);
        // Duplicate Id detected. Will return index of those to caller.
        if (!ret.second) {
            dupIds.push_back(index);
        } else {
            // ID was not duplicate. Accept it.
            newIdArr.emplace_back(*ret.first);
            // Check was ID previously available or totally new one.
            if (oldIdsSet.find(*ret.first) == oldIdsSet.end()) {
                // Populate output diff array with this index that was not in old array.
                diffIds.push_back(index);
            }
        }
        index++;
    }

    ForEachModel::GetInstance()->SetNewIds(std::move(newIdArr));
    std::list<int32_t> removedElmtIds;
    ForEachModel::GetInstance()->SetRemovedElmtIds(removedElmtIds);
    if (removedElmtIds.size()) {
        for (const auto& rmElmtId : removedElmtIds) {
            remIds.emplace_back(rmElmtId);
        }
    }
    return AssambleSetIdResult(diffIds, dupIds, remIds);
}

void FfiOHOSAceFrameworkViewCreateNewChildStart(char* elmtId)
{
    LOGD("Start create child with array id %{public}s.", elmtId);

    auto* model = ForEachModel::GetInstance();
    model->CreateNewChildStart(elmtId);
}

void FfiOHOSAceFrameworkViewCreateNewChildFinish(char* elmtId)
{
    LOGD("Finish create child with array id %{public}s.", elmtId);

    auto* model = ForEachModel::GetInstance();
    model->CreateNewChildFinish(elmtId);
}
}
