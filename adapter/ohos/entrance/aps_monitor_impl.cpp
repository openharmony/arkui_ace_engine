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

#include <dlfcn.h>
#include "aps_monitor_impl.h"
#include "core/common/ace_application_info.h"
#include "base/perfmonitor/perf_constants.h"

namespace OHOS::Ace {
using namespace std;
namespace {
    const std::string APS_CLIENT_SO = "libaps_client.z.so";
}

const set<string> ApsMonitorImpl::apsScenes = {
    PerfConstants::ABILITY_OR_PAGE_SWITCH,
};

void ApsMonitorImpl::SetApsScene(const string& sceneName, bool onOff)
{
    string bundleName = AceApplicationInfo::GetInstance().GetPackageName();
    if (apsScenes.find(sceneName) == apsScenes.end()) {
        return;
    }
#ifdef APS_ENABLE
    LoadApsFuncOnce();
    if (!setFunc_) {
        LOGE("[ApsMonitorImpl]ApsManager setFunction failed!");
        return;
    }
    uint32_t OnOff = static_cast<uint32_t>(onOff);
    setFunc_(bundleName, sceneName, OnOff);
#endif
    return;
}

void ApsMonitorImpl::LoadApsFuncOnce()
{
    if (isloadapsfunc_) {
        return;
    }

    auto handle = dlopen(APS_CLIENT_SO.c_str(), RTLD_NOW);
    if (!handle) {
        LOGE("[ApsMonitorImpl]ApsManager handle loaded failed!");
        return;
    }

    setFunc_ = reinterpret_cast<SetSceneFunc>(dlsym(handle, "SetApsScene"));
    if (!setFunc_) {
        LOGE("[ApsMonitorImpl]ApsManager Function loaded failed!");
        dlclose(handle);
        return;
    }
    isloadapsfunc_ = true;
}
} // namespace OHOS::Ace