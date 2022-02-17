/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "native_interface_xcomponent.h"

#include "frameworks/core/components/xcomponent/native_interface_xcomponent_impl.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t NativeXComponent_GetXComponentId(NativeXComponent* component, char* id, uint64_t* size)
{
    if ((component == nullptr) || (id == nullptr) || (size == nullptr)) {
        return XCOMPONENT_RESULT_BAD_PARAMETER;
    }
    if (((*size) == 0) || ((*size) > (XCOMPONENT_ID_LEN_MAX + 1))) {
        LOGE("The referenced value of 'size' should be in the range (0, XCOMPONENT_ID_LEN_MAX + 1]");
        return XCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetXComponentId(id, size);
}

int32_t OH_NativeXComponent_GetXComponentId(NativeXComponent* component, char* id, uint64_t* size)
    __attribute__((weak, alias("NativeXComponent_GetXComponentId")));

int32_t NativeXComponent_GetNativeWindow(NativeXComponent* component, void** window)
{
    if ((component == nullptr) || (window == nullptr)) {
        return XCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetNativeWindow(window);
}

int32_t OH_NativeXComponent_GetNativeWindow(NativeXComponent* component, void** window)
    __attribute__((weak, alias("NativeXComponent_GetNativeWindow")));

int32_t NativeXComponent_GetXComponentSize(
    NativeXComponent* component, const void* window, uint64_t* width, uint64_t* height)
{
    if ((component == nullptr) || (window == nullptr) || (width == nullptr) || (height == nullptr)) {
        return XCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetXComponentSize(window, width, height);
}

int32_t OH_NativeXComponent_GetXComponentSize(
    NativeXComponent* component, const void* window, uint64_t* width, uint64_t* height)
    __attribute__((weak, alias("NativeXComponent_GetXComponentSize")));

int32_t NativeXComponent_GetXComponentOffset(NativeXComponent* component, const void* window, double* x, double* y)
{
    if ((component == nullptr) || (window == nullptr) || (x == nullptr) || (y == nullptr)) {
        return XCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetXComponentOffset(window, x, y);
}

int32_t OH_NativeXComponent_GetXComponentOffset(NativeXComponent* component, const void* window, double* x, double* y)
    __attribute__((weak, alias("NativeXComponent_GetXComponentOffset")));

int32_t NativeXComponent_GetTouchInfo(NativeXComponent* component, const void* window, TouchInfo* touchInfo)
{
    if ((component == nullptr) || (window == nullptr) || (touchInfo == nullptr)) {
        return XCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->GetTouchInfo(window, touchInfo);
}

int32_t OH_NativeXComponent_GetTouchInfo(NativeXComponent* component, const void* window, TouchInfo* touchInfo)
    __attribute__((weak, alias("NativeXComponent_GetTouchInfo")));

int32_t NativeXComponent_RegisterCallback(NativeXComponent* component, NativeXComponentCallback* callback)
{
    if ((component == nullptr) || (callback == nullptr)) {
        return XCOMPONENT_RESULT_BAD_PARAMETER;
    }
    return component->RegisterCallback(callback);
}

int32_t OH_NativeXComponent_RegisterCallback(NativeXComponent* component, NativeXComponentCallback* callback)
    __attribute__((weak, alias("NativeXComponent_RegisterCallback")));

#ifdef __cplusplus
};
#endif
