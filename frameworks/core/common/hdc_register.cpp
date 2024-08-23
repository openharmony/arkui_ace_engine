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

#include "core/common/hdc_register.h"

#include <dlfcn.h>

#include "core/common/ace_application_info.h"
#include "core/common/container_consts.h"

namespace OHOS::Ace {
namespace {
using StartRegister = void (*)(
    const std::string& processName, const std::string& pkgName, bool debugApp, Callback callback);
using StopRegister = void (*)();
} // namespace

HdcRegister::HdcRegister(): registerHandler_(nullptr)
{
    isDebugVersion_ = AceApplicationInfo::GetInstance().IsDebugVersion();
    if (!isDebugVersion_) {
        return;
    }
    pkgName_ = AceApplicationInfo::GetInstance().GetPackageName();
    LoadRegisterSo();
}

HdcRegister& HdcRegister::Get()
{
    static HdcRegister hdcRegister;
    return hdcRegister;
}

void HdcRegister::LoadRegisterSo()
{
    registerHandler_ = dlopen("libhdc_register.z.so", RTLD_LAZY);
    CHECK_NULL_VOID(registerHandler_);
}

void HdcRegister::StartHdcRegister(int32_t instanceId, Callback callback)
{
    LOGI("Start Hdc Register, instance id:%{public}d", instanceId);
    CHECK_NULL_VOID(registerHandler_);
    if (instanceId % CONTAINER_ID_DIVIDE_SIZE != 0) {
        return; // Applications and abilities should only call this function once, especially in multi-instance.
    }
    StartRegister startRegister = (StartRegister)dlsym(registerHandler_, "StartConnect");
    CHECK_NULL_VOID(startRegister);
    startRegister("", pkgName_, isDebugVersion_, callback);
}

void HdcRegister::StopHdcRegister(int32_t instanceId)
{
    if (!isDebugVersion_ || instanceId != 0) {
        return;
    }
    LOGI("Stop Hdc Register");
    CHECK_NULL_VOID(registerHandler_);
    StopRegister stopRegister = (StopRegister)dlsym(registerHandler_, "StopConnect");
    CHECK_NULL_VOID(stopRegister);
    stopRegister();
    dlclose(registerHandler_);
    registerHandler_ = nullptr;
}

} // namespace OHOS::Ace
