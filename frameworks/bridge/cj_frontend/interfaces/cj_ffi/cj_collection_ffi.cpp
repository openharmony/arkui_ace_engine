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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_collection_ffi.h"

#include "cj_lambda.h"

NavigationItem::NavigationItem(const NavigationItemFFI& source)
{
    value = source.value;
    icon = source.icon;
    isEnable = source.isEnable;
    actionFFI = source.action;
    action = CJLambda::Create(reinterpret_cast<void (*)()>(actionFFI));
    status = source.status;
    activeIcon = source.activeIcon;
}

extern "C" {
#define VECTOR_FUNC_H(cjType, cType)                                       \
    Vector##cjType##Handle FFICJCommonCreateVector##cjType(int64_t size)   \
    {                                                                      \
        return new std::vector<cType>(size);                               \
    }                                                                      \
                                                                           \
    void FFICJCommonVector##cjType##Delete(Vector##cjType##Handle vec)     \
    {                                                                      \
        if (vec == nullptr) {                                              \
            return;                                                        \
        }                                                                  \
        auto actualVec = reinterpret_cast<std::vector<cType>*>(vec);       \
        delete actualVec;                                                  \
    }                                                                      \
                                                                           \
    int64_t FFICJCommonVector##cjType##GetSize(Vector##cjType##Handle vec) \
    {                                                                      \
        if (vec == nullptr) {                                              \
            return 0;                                                      \
        }                                                                  \
        auto actualVec = reinterpret_cast<std::vector<cType>*>(vec);       \
        return actualVec->size();                                          \
    }

VECTOR_FUNC_H(String, std::string)
VECTOR_FUNC_H(Int32, int32_t)
VECTOR_FUNC_H(Int64, int64_t)
VECTOR_FUNC_H(UInt8, uint8_t)
VECTOR_FUNC_H(UInt32, uint32_t)
VECTOR_FUNC_H(Float32, float)
VECTOR_FUNC_H(Float64, double)
VECTOR_FUNC_H(Bool, bool)
VECTOR_FUNC_H(NavigationItem, NavigationItem)

#undef VECTOR_FUNC_H

// This is for string.
void FFICJCommonVectorStringSetElement(VectorStringHandle vec, int64_t index, const char* value)
{
    if (vec == nullptr || index < 0) {
        return;
    }
    auto actualVec = reinterpret_cast<std::vector<std::string>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return;
    }
    (*actualVec)[index] = value != nullptr ? value : "";
}

// never free return value in cj.
const char* FFICJCommonVectorStringGetElement(VectorStringHandle vec, int64_t index)
{
    if (vec == nullptr || index < 0) {
        return "";
    }
    auto actualVec = reinterpret_cast<std::vector<std::string>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return "";
    }
    return (*actualVec)[index].c_str();
}

// This is for int.
void FFICJCommonVectorInt32SetElement(VectorInt32Handle vec, int64_t index, int32_t value)
{
    if (vec == nullptr || index < 0) {
        return;
    }
    auto actualVec = reinterpret_cast<std::vector<int32_t>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return;
    }
    (*actualVec)[index] = value;
}

int32_t FFICJCommonVectorInt32GetElement(VectorInt32Handle vec, int64_t index)
{
    if (vec == nullptr || index < 0) {
        return 0;
    }
    auto actualVec = reinterpret_cast<std::vector<int32_t>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return 0;
    }
    return (*actualVec)[index];
}

// This is for long long.
void FFICJCommonVectorInt64SetElement(VectorInt64Handle vec, int64_t index, int64_t value)
{
    if (vec == nullptr || index < 0) {
        return;
    }
    auto actualVec = reinterpret_cast<std::vector<int64_t>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return;
    }
    (*actualVec)[index] = value;
}

int64_t FFICJCommonVectorInt64GetElement(VectorInt64Handle vec, int64_t index)
{
    if (vec == nullptr || index < 0) {
        return 0;
    }
    auto actualVec = reinterpret_cast<std::vector<int64_t>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return 0;
    }
    return (*actualVec)[index];
}

// This is for uint8_t.
void FFICJCommonVectorUInt8SetElement(VectorUInt8Handle vec, int64_t index, uint8_t value)
{
    if (vec == nullptr || index < 0) {
        return;
    }
    auto actualVec = reinterpret_cast<std::vector<uint8_t>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return;
    }
    (*actualVec)[index] = value;
}

uint8_t FFICJCommonVectorUInt8GetElement(VectorUInt8Handle vec, int64_t index)
{
    if (vec == nullptr || index < 0) {
        return 0;
    }
    auto actualVec = reinterpret_cast<std::vector<uint8_t>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return 0;
    }
    return (*actualVec)[index];
}

// This is for uint32_t.
void FFICJCommonVectorUInt32SetElement(VectorUInt32Handle vec, int64_t index, uint32_t value)
{
    if (vec == nullptr || index < 0) {
        return;
    }
    auto actualVec = reinterpret_cast<std::vector<uint32_t>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return;
    }
    (*actualVec)[index] = value;
}

uint32_t FFICJCommonVectorUInt32GetElement(VectorUInt32Handle vec, int64_t index)
{
    if (vec == nullptr || index < 0) {
        return 0;
    }
    auto actualVec = reinterpret_cast<std::vector<uint32_t>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return 0;
    }
    return (*actualVec)[index];
}

// This is for float.
void FFICJCommonVectorFloat32SetElement(VectorFloat32Handle vec, int64_t index, float value)
{
    if (vec == nullptr || index < 0) {
        return;
    }
    auto actualVec = reinterpret_cast<std::vector<float>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return;
    }
    (*actualVec)[index] = value;
}

float FFICJCommonVectorFloat32GetElement(VectorFloat32Handle vec, int64_t index)
{
    if (vec == nullptr || index < 0) {
        return 0.0f;
    }
    auto actualVec = reinterpret_cast<std::vector<float>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return 0.0f;
    }
    return (*actualVec)[index];
}

// This is for double.
void FFICJCommonVectorFloat64SetElement(VectorFloat64Handle vec, int64_t index, double value)
{
    if (vec == nullptr || index < 0) {
        return;
    }
    auto actualVec = reinterpret_cast<std::vector<double>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return;
    }
    (*actualVec)[index] = value;
}

double FFICJCommonVectorFloat64GetElement(VectorFloat64Handle vec, int64_t index)
{
    if (vec == nullptr || index < 0) {
        return 0.0;
    }
    auto actualVec = reinterpret_cast<std::vector<double>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return 0.0;
    }
    return (*actualVec)[index];
}

// This is for bool.
void FFICJCommonVectorBoolSetElement(VectorBoolHandle vec, int64_t index, bool value)
{
    if (vec == nullptr || index < 0) {
        return;
    }
    auto actualVec = reinterpret_cast<std::vector<bool>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return;
    }
    (*actualVec)[index] = value;
}

bool FFICJCommonVectorBoolGetElement(VectorBoolHandle vec, int64_t index)
{
    if (vec == nullptr || index < 0) {
        return false;
    }
    auto actualVec = reinterpret_cast<std::vector<bool>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return false;
    }
    return (*actualVec)[index];
}

// This is for NavigationItem.
void FFICJCommonVectorNavigationItemSetElement(VectorNavigationItemHandle vec, int64_t index, NavigationItemFFI value)
{
    if (vec == nullptr || index < 0) {
        return;
    }
    auto actualVec = reinterpret_cast<std::vector<NavigationItem>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return;
    }
    (*actualVec)[index] = NavigationItem(value);
}

NavigationItemFFI FFICJCommonVectorNavigationItemGetElement(VectorNavigationItemHandle vec, int64_t index)
{
    if (vec == nullptr || index < 0) {
        return NavigationItemFFI();
    }
    auto actualVec = reinterpret_cast<std::vector<NavigationItem>*>(vec);
    if (static_cast<size_t>(index) >= actualVec->size()) {
        return NavigationItemFFI();
    }
    return (*actualVec)[index].ToFFI();
}
}