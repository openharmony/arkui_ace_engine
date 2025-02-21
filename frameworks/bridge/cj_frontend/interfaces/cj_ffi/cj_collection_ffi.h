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

#ifndef OHOS_ACE_FRAMEWORK_FFI_CJ_COLLECTION_H
#define OHOS_ACE_FRAMEWORK_FFI_CJ_COLLECTION_H

#include <cstdint>
#include <functional>
#include <string>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" struct NavigationItemFFI {
    const char* value;
    const char* icon;
    bool isEnable;
    int64_t action;
    int32_t status;
    const char* activeIcon;
};

struct NavigationItem {
    std::string value;
    std::string icon;
    bool isEnable;
    int64_t actionFFI;
    std::function<void()> action;
    int32_t status;
    std::string activeIcon;
    NavigationItem() = default;
    explicit NavigationItem(const NavigationItemFFI& source);
    NavigationItemFFI ToFFI()
    {
        return NavigationItemFFI { .value = value.c_str(), .icon = icon.c_str(), .isEnable = isEnable,
            .action = actionFFI, .status = status, .activeIcon = activeIcon.c_str() };
    }
};

#define VECTOR_H(typeName)                                                                \
    using Vector##typeName##Handle = void*;                                               \
    extern "C" {                                                                          \
    CJ_EXPORT Vector##typeName##Handle FFICJCommonCreateVector##typeName(int64_t size);   \
    CJ_EXPORT void FFICJCommonVector##typeName##Delete(Vector##typeName##Handle vec);     \
    CJ_EXPORT int64_t FFICJCommonVector##typeName##GetSize(Vector##typeName##Handle vec); \
    }

VECTOR_H(String)
VECTOR_H(Int32)
VECTOR_H(Int64)
VECTOR_H(UInt8)
VECTOR_H(UInt32)
VECTOR_H(Float32)
VECTOR_H(Float64)
VECTOR_H(Bool)
VECTOR_H(NavigationItem)

#undef VECTOR_H

extern "C" {
CJ_EXPORT void FFICJCommonVectorStringSetElement(VectorStringHandle vec, int64_t index, const char* value);
CJ_EXPORT const char* FFICJCommonVectorStringGetElement(VectorStringHandle vec, int64_t index);

CJ_EXPORT void FFICJCommonVectorInt32SetElement(VectorInt32Handle vec, int64_t index, int32_t value);
CJ_EXPORT int32_t FFICJCommonVectorInt32GetElement(VectorInt32Handle vec, int64_t index);

CJ_EXPORT void FFICJCommonVectorInt64SetElement(VectorInt64Handle vec, int64_t index, int64_t value);
CJ_EXPORT int64_t FFICJCommonVectorInt64GetElement(VectorInt64Handle vec, int64_t index);

CJ_EXPORT void FFICJCommonVectorUInt8SetElement(VectorUInt8Handle vec, int64_t index, uint8_t value);
CJ_EXPORT uint8_t FFICJCommonVectorUInt8GetElement(VectorUInt8Handle vec, int64_t index);

CJ_EXPORT void FFICJCommonVectorUInt32SetElement(VectorUInt32Handle vec, int64_t index, uint32_t value);
CJ_EXPORT uint32_t FFICJCommonVectorUInt32GetElement(VectorUInt32Handle vec, int64_t index);

CJ_EXPORT void FFICJCommonVectorFloat32SetElement(VectorFloat32Handle vec, int64_t index, float value);
CJ_EXPORT float FFICJCommonVectorFloat32GetElement(VectorFloat32Handle vec, int64_t index);

CJ_EXPORT void FFICJCommonVectorFloat64SetElement(VectorFloat64Handle vec, int64_t index, double value);
CJ_EXPORT double FFICJCommonVectorFloat64GetElement(VectorFloat64Handle vec, int64_t index);

CJ_EXPORT void FFICJCommonVectorBoolSetElement(VectorBoolHandle vec, int64_t index, bool value);
CJ_EXPORT bool FFICJCommonVectorBoolGetElement(VectorBoolHandle vec, int64_t index);

CJ_EXPORT void FFICJCommonVectorNavigationItemSetElement(
    VectorNavigationItemHandle vec, int64_t index, NavigationItemFFI value);
CJ_EXPORT NavigationItemFFI FFICJCommonVectorNavigationItemGetElement(VectorNavigationItemHandle vec, int64_t index);
};

#endif // OHOS_ACE_FRAMEWORK_FFI_CJ_COLLECTION_H