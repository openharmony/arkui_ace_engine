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

#ifndef OHOS_OBSERVER_FFI_H
#define OHOS_OBSERVER_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

extern "C" {
CJ_EXPORT void FfiOHOSObserverRegisterScrollEventCallback(int64_t callbackId);
CJ_EXPORT void FfiOHOSObserverUnRegisterScrollEventCallback(int64_t callbackId);
CJ_EXPORT void FfiOHOSObserverRegisterScrollEventCallbackWithOptions(const char* options, int64_t callbackId);
CJ_EXPORT void FfiOHOSObserverUnRegisterScrollEventCallbackWithOptions(const char* options, int64_t callbackId);
CJ_EXPORT void FfiOHOSObserverRegisterTabContentUpdateCallback(int64_t callbackId);
CJ_EXPORT void FfiOHOSObserverUnRegisterTabContentUpdateCallback(int64_t callbackId);
CJ_EXPORT void FfiOHOSObserverRegisterTabContentUpdateCallbackWithOptions(const char* options, int64_t callbackId);
CJ_EXPORT void FfiOHOSObserverUnRegisterTabContentUpdateCallbackWithOptions(const char* options, int64_t callbackId);
}

#endif // OHOS_OBSERVER_FFI_H
