/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

#include <dlfcn.h>
#include "aps_monitor_impl.h"
#include "adapter/ohos/entrance/ace_container.h"
#include "base/perfmonitor/perf_constants.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_resolution_config.h"

namespace OHOS::Ace {
using namespace std;
namespace {
    const std::string APS_CLIENT_SO = "libaps_client.z.so";
}

ApsMonitorImpl& ApsMonitorImpl::GetInstance()
{
    static ApsMonitorImpl apsMonitorImpl;
    return apsMonitorImpl;
}

ApsMonitorImpl::~ApsMonitorImpl()
{
    if (loadfilehandle_ != nullptr) {
        ReSetApsClient();
        dlclose(loadfilehandle_);
        loadfilehandle_ = nullptr;
    }
}

const set<string> ApsMonitorImpl::apsScenes = {
    PerfConstants::ABILITY_OR_PAGE_SWITCH,
};

void ApsMonitorImpl::SetApsScene(const string& sceneName, bool onOff)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto container = Container::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    string bundleName = container->GetBundleName();
    if (apsScenes.find(sceneName) == apsScenes.end()) {
        return;
    }
#ifdef APS_ENABLE
    LoadApsFuncOnce();
    if (setFunc_ == nullptr) {
        LOGE("[ApsMonitorImpl]ApsManager setFunction failed!");
        return;
    }
    uint32_t OnOff = static_cast<uint32_t>(onOff);
    setFunc_(bundleName, sceneName, OnOff);
#endif
    return;
}

float ApsMonitorImpl::GetApsSdrRatio(const std::string& pkgName, int32_t indexForUsingClient)
{
    std::lock_guard<std::mutex> lock(mutex_);
    float sdrRatio = static_cast<float>(NG::RatioValue::RATIO_DEFAULT);
    LoadApsFuncOnce();
    if (getApsSdrRatioFunc_ == nullptr) {
        LOGE("[ApsMonitorImpl]ApsManager GetSdrRatio failed!");
        return static_cast<float>(NG::RatioValue::RATIO_READ_FAIL);
    }
    sdrRatio = getApsSdrRatioFunc_(pkgName, indexForUsingClient);
    return sdrRatio;
}

void ApsMonitorImpl::SetContainerInstanceId(int32_t instanceId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    instanceId_ = instanceId;
}

void ApsMonitorImpl::LoadApsFuncOnce()
{
    if (isloadapsfunc_) {
        return;
    }

    loadfilehandle_ = dlopen(APS_CLIENT_SO.c_str(), RTLD_NOW);
    if (loadfilehandle_ == nullptr) {
        LOGE("[ApsMonitorImpl]ApsManager handle loaded failed!");
        return;
    }

    resetFunc_ = reinterpret_cast<ReSetClientFunc>(dlsym(loadfilehandle_, "ReSetApsClient"));
    if (resetFunc_ == nullptr) {
        LOGE("[ApsMonitorImpl]ApsManager ReSetApsClient Function loaded failed!");
        dlclose(loadfilehandle_);
        return;
    }

    setFunc_ = reinterpret_cast<SetSceneFunc>(dlsym(loadfilehandle_, "SetApsScene"));
    if (setFunc_ == nullptr) {
        LOGE("[ApsMonitorImpl]ApsManager SetApsScene Function loaded failed!");
        dlclose(loadfilehandle_);
        return;
    }

    getApsSdrRatioFunc_ = reinterpret_cast<GetApsSdrRatioFunc>(dlsym(loadfilehandle_, "GetApsSdrRatio"));
    if (getApsSdrRatioFunc_ == nullptr) {
        LOGE("[ApsMonitorImpl]ApsManager GetApsSdrRatio Function loaded failed!");
        dlclose(loadfilehandle_);
        return;
    }

    isloadapsfunc_ = true;
}

void ApsMonitorImpl::ReSetApsClient()
{
    if (resetFunc_ != nullptr) {
        resetFunc_();
    }
}
} // namespace OHOS::Ace