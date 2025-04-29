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

#include "observer_ffi.h"

#include "cj_observer.h"
#include "observer.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;
using namespace OHOS::Ace::NG;

namespace OHOS {
namespace Rosen {
extern "C" {

void FfiOHOSObserverRegisterScrollEventCallback(int64_t callbackId)
{
    LOGI("FfiOHOSObserverRegisterScrollEventCallback start");
    return ObserverProcess::GetInstance().ProcessScrollEventRegister(callbackId);
}

void FfiOHOSObserverUnRegisterScrollEventCallback(int64_t callbackId)
{
    LOGI("FfiOHOSObserverUnRegisterScrollEventCallback start");
    return ObserverProcess::GetInstance().ProcessScrollEventUnRegister(callbackId);
}

void FfiOHOSObserverRegisterScrollEventCallbackWithOptions(const char* options, int64_t callbackId)
{
    LOGI("FfiOHOSObserverRegisterScrollEventCallbackWithOptions start");
    return ObserverProcess::GetInstance().ProcessScrollEventRegisterWithOptions(options, callbackId);
}

void FfiOHOSObserverUnRegisterScrollEventCallbackWithOptions(const char* options, int64_t callbackId)
{
    LOGI("FfiOHOSObserverUnRegisterScrollEventCallbackWithOptions start");
    return ObserverProcess::GetInstance().ProcessScrollEventUnRegisterWithOptions(options, callbackId);
}

void FfiOHOSObserverRegisterTabContentUpdateCallback(int64_t callbackId)
{
    LOGI("FfiOHOSObserverRegisterTabContentUpdateCallback start");
    return ObserverProcess::GetInstance().ProcessTabContentUpdateRegister(callbackId);
}

void FfiOHOSObserverUnRegisterTabContentUpdateCallback(int64_t callbackId)
{
    LOGI("FfiOHOSObserverUnRegisterTabContentUpdateCallback start");
    return ObserverProcess::GetInstance().ProcessTabContentUpdateUnRegister(callbackId);
}

void FfiOHOSObserverRegisterTabContentUpdateCallbackWithOptions(const char* options, int64_t callbackId)
{
    LOGI("FfiOHOSObserverRegisterTabContentUpdateCallbackWithOptions start");
    return ObserverProcess::GetInstance().ProcessTabContentUpdateRegisterWithOptions(options, callbackId);
}

void FfiOHOSObserverUnRegisterTabContentUpdateCallbackWithOptions(const char* options, int64_t callbackId)
{
    LOGI("FfiOHOSObserverUnRegisterTabContentUpdateCallbackWithOptions start");
    return ObserverProcess::GetInstance().ProcessTabContentUpdateUnRegisterWithOptions(options, callbackId);
}
}
} // namespace Rosen
} // namespace OHOS
