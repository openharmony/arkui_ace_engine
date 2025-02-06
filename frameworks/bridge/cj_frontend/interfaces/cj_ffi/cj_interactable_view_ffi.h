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

#ifndef OHOS_ACE_FRAMEWORK_CJ_TEXT_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_TEXT_FFI_H

#include <cstdint>
#include <string>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"

using VectorFloat64Handle = void*;
using VectorTouchTestInfoHandle = void*;

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkInteractableViewOnClick(void (*callback)(CJClickInfo clickInfo));
CJ_EXPORT void FfiOHOSAceFrameworkInteractableViewOnTouch(bool (*callback)(CJTouchEvent touchInfo));
CJ_EXPORT void FfiOHOSAceFrameworkInteractableViewOnAppear(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkInteractableViewOnDisAppear(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkInteractableViewOnHover(void (*callback)(bool));
CJ_EXPORT void FfiOHOSAceFrameworkInteractableViewOnAreaChanged(void (*callback)(CJArea, CJArea));
CJ_EXPORT void FfiOHOSAceFrameworkInteractableViewOnVisibleAreaChange(
    VectorFloat64Handle raitosValsHandle, void (*callback)(bool isVisible, double currentRatio));
CJ_EXPORT void FfiOHOSAceFrameworkInteractableViewOnKey(bool (*callback)(CJKeyEvent info));
CJ_EXPORT void FfiOHOSAceFrameworkInteractableViewOnDelete(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkInteractableViewOnFocus(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkInteractableViewOnBlur(void (*callback)());
CJ_EXPORT void FfiOHOSAceFrameworkInteractableViewOnMouse(void (*callback)(CJMouseEvent));
CJ_EXPORT VectorTouchTestInfoHandle FFICJCreateVectorTouchTestInfo(int64_t size);
CJ_EXPORT void FFICJVectorTouchTestInfoSetElement(
    VectorTouchTestInfoHandle vec, int64_t index, CJTouchTestInfo touchTestInfo);
CJ_EXPORT CJTouchTestInfo FFICJVectorTouchTestInfoGetElement(VectorTouchTestInfoHandle vec, int64_t index);
CJ_EXPORT void FFICJVectorTouchTestInfoDelete(VectorTouchTestInfoHandle vec);
CJ_EXPORT int64_t FFICJVectorTouchTestInfoGetSize(VectorTouchTestInfoHandle vec);
CJ_EXPORT void FfiOHOSAceFrameworkInteractableOnChildTouchTest(
    CJTouchResult (*callback)(VectorTouchTestInfoHandle handle));
CJ_EXPORT void FfiOHOSAceFrameworkInteractableViewOnDragStart(
    CJDragItemInfo (*callback)(CJDragInfo info), uint32_t componentName);
CJ_EXPORT void FfiOHOSAceFrameworkInteractableViewOnDragEnter(
    void (*callback)(CJDragInfo info), uint32_t componentName);
CJ_EXPORT void FfiOHOSAceFrameworkInteractableViewOnDragMove(void (*callback)(CJDragInfo info), uint32_t componentName);
CJ_EXPORT void FfiOHOSAceFrameworkInteractableViewOnDragLeave(
    void (*callback)(CJDragInfo info), uint32_t componentName);
CJ_EXPORT void FfiOHOSAceFrameworkInteractableViewOnDrop(void (*callback)(CJDragInfo info), uint32_t componentName);
CJ_EXPORT void FfiInteractableViewOnDragStart(CJDragItemInfo (*callback)(CJDragEvent event, const char* extraParams));
CJ_EXPORT void FfiDragEventSetResult(void* ptr, int32_t result);
CJ_EXPORT int32_t FfiDragEventGetResult(void* ptr);
CJ_EXPORT NativeRectangle FfiDragEventGetPreviewRect(void* ptr);
CJ_EXPORT double FfiDragEventGetVelocityX(void* ptr);
CJ_EXPORT double FfiDragEventGetVelocityY(void* ptr);
CJ_EXPORT double FfiDragEventGetVelocity(void* ptr);
CJ_EXPORT double FfiDragEventGetWindowX(void* ptr);
CJ_EXPORT double FfiDragEventGetWindowY(void* ptr);
CJ_EXPORT double FfiDragEventGetDisplayX(void* ptr);
CJ_EXPORT double FfiDragEventGetDisplayY(void* ptr);
CJ_EXPORT void FfiDragEventFree(void* ptr);
CJ_EXPORT bool FfiDragEventGetModifierKeyState(void* ptr, VectorStringHandle keys);
CJ_EXPORT void FfiInteractableViewOnDragEnter(void (*callback)(CJDragEvent event, const char* extraParams));
CJ_EXPORT void FfiInteractableViewOnDragMove(void (*callback)(CJDragEvent event, const char* extraParams));
CJ_EXPORT void FfiInteractableViewOnDragLeave(void (*callback)(CJDragEvent event, const char* extraParams));
CJ_EXPORT void FfiInteractableViewOnDrop(void (*callback)(CJDragEvent event, const char* extraParams));
CJ_EXPORT void FfiInteractableViewOnDragEnd(void (*callback)(CJDragEvent event, const char* extraParams));
CJ_EXPORT void FfiInteractableViewOnPreDrag(void (*callback)(int32_t status));
}

#endif // OHOS_ACE_FRAMEWORK_CJ_TEXT_FFI_H
