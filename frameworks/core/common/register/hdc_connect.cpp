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

#include "base/log/log.h"
#include "frameworks/core/common/register/hdc_connect.h"
#include "frameworks/core/common/register/hdc_jdwp.h"

namespace OHOS::Ace {

std::unique_ptr<ConnectManagement> g_connectManagement = nullptr;
static HdcJdwpSimulator *clsHdcJdwpSimulator = nullptr;

void ConnectManagement::SetPkgName(const std::string &pkgName)
{
    pkgName_ = pkgName;
}

std::string ConnectManagement::GetPkgName()
{
    return pkgName_;
}

void FreeInstance()
{
    if (clsHdcJdwpSimulator == nullptr) {
        return; // if clsHdcJdwpSimulator is nullptr, should return immediately.
    }
    clsHdcJdwpSimulator->FreeContext();
    delete clsHdcJdwpSimulator;
    clsHdcJdwpSimulator = nullptr;
}

void StopConnect()
{
#ifdef JS_JDWP_CONNECT
    FreeInstance();
#endif // JS_JDWP_CONNECT
}

void* HdcConnectRun(void* pkgContent)
{
    std::string pkgName = static_cast<ConnectManagement*>(pkgContent)->GetPkgName();
    clsHdcJdwpSimulator = new (std::nothrow) HdcJdwpSimulator(pkgName);
    if (!clsHdcJdwpSimulator->Connect()) {
        LOGE("Connect fail.");
        return nullptr;
    }
    return nullptr;
}

void StartConnect(const std::string& pkgName)
{
    if (clsHdcJdwpSimulator != nullptr) {
        return;
    }
    pthread_t tid;
    g_connectManagement = std::make_unique<ConnectManagement>();
    g_connectManagement->SetPkgName(pkgName);
    if (pthread_create(&tid, nullptr, &HdcConnectRun, static_cast<void*>(g_connectManagement.get())) != 0) {
        LOGE("pthread_create fail!");
        return;
    }
}
} // namespace OHOS::Ace
