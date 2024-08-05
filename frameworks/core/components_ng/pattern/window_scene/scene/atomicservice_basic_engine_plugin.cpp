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

#include "core/components_ng/pattern/window_scene/scene/atomicservice_basic_engine_plugin.h"
#include "core/components_ng/pattern/window_scene/scene/window_pattern.h"

namespace OHOS::Ace::NG {
#ifdef ATOMIC_SERVICE_ATTRIBUTION_ENABLE
std::string AtomicserviceIconInfo::GetBundleName() const
{
    return bundleName_;
}

std::string AtomicserviceIconInfo::GetModuleName() const
{
    return moduleName_;
}

std::string AtomicserviceIconInfo::GetAbilityName() const
{
    return abilityName_;
}

std::string AtomicserviceIconInfo::GetCircleIcon() const
{
    return circleIcon_;
}

std::string AtomicserviceIconInfo::GetEyelashRingIcon() const
{
    return eyelashRingIcon_;
}

std::string AtomicserviceIconInfo::GetAppName() const
{
    return appName_;
}

void AtomicserviceIconInfo::SetBundleName(const std::string& val)
{
    bundleName_ = val;
}

void AtomicserviceIconInfo::SetModuleName(const std::string& val)
{
    moduleName_ = val;
}

void AtomicserviceIconInfo::SetAbilityName(const std::string& val)
{
    abilityName_ = val;
}

void AtomicserviceIconInfo::SetCircleIcon(const std::string& val)
{
    circleIcon_ = val;
}

void AtomicserviceIconInfo::SetEyelashRingIcon(const std::string& val)
{
    eyelashRingIcon_ = val;
}

void AtomicserviceIconInfo::SetAppName(const std::string& val)
{
    appName_ = val;
}

bool AtomicserviceIconInfo::Marshalling(Parcel& parcel) const
{
    parcel.WriteString(bundleName_);
    parcel.WriteString(moduleName_);
    parcel.WriteString(abilityName_);
    parcel.WriteString(circleIcon_);
    parcel.WriteString(eyelashRingIcon_);
    parcel.WriteString(appName_);
    return true;
}

AtomicserviceIconInfo *AtomicserviceIconInfo::Unmarshalling(Parcel& parcel)
{
    AtomicserviceIconInfo *data = new AtomicserviceIconInfo();
    data->SetBundleName(parcel.ReadString());
    data->SetModuleName(parcel.ReadString());
    data->SetAbilityName(parcel.ReadString());
    data->SetCircleIcon(parcel.ReadString());
    data->SetEyelashRingIcon(parcel.ReadString());
    data->SetAppName(parcel.ReadString());
    return data;
}

AtomicServiceBasicEnginePlugin::AtomicServiceBasicEnginePlugin()
{
    // if ACE_ENGINE_PLUGIN_PATH is defined, load so pack
#ifdef ACE_ENGINE_PLUGIN_PATH
    atomicServiceBasicEngine_ = dlopen(
        (char*)ACE_ENGINE_PLUGIN_PATH, RTLD_LAZY);
    if (atomicServiceBasicEngine_ == nullptr) {
        TAG_LOGW(AceLogTag::ACE_WINDOW_SCENE,
            "dlopen lib %{public}s false", (char*)ACE_ENGINE_PLUGIN_PATH);
        return;
    }
#else
    TAG_LOGW(AceLogTag::ACE_WINDOW_SCENE, "ACE_ENGINE_PLUGIN_PATH is not defined");
    return;
#endif
    // load function GetAtomicserviceIconInfoPlugin
    getAtomicserviceIconInfoPlugin = (GetAtomicserviceIconInfoPlugin*)(dlsym(
        atomicServiceBasicEngine_, "GetAtomicserviceIconInfoPlugin"));
    if (getAtomicserviceIconInfoPlugin == nullptr) {
        TAG_LOGW(AceLogTag::ACE_WINDOW_SCENE,
            "fail to dlsym GetAtomicserviceIconInfoPlugin, reason: %{public}s", dlerror());
        return;
    }
    // load function FreeData
    freeData = (FreeData*)(dlsym(atomicServiceBasicEngine_, "FreeAtomicserviceIconInfoPlugin"));
    if (freeData == nullptr) {
        TAG_LOGW(AceLogTag::ACE_WINDOW_SCENE,
            "fail to dlsym FreeData, reason: %{public}s", dlerror());
        return;
    }
}

AtomicServiceBasicEnginePlugin::~AtomicServiceBasicEnginePlugin()
{
    // close dlopen so pack
    if (atomicServiceBasicEngine_ != nullptr) {
        dlclose(atomicServiceBasicEngine_);
        atomicServiceBasicEngine_ = nullptr;
    }
    getAtomicserviceIconInfoPlugin = nullptr;
    freeData = nullptr;
}

AtomicServiceBasicEnginePlugin& AtomicServiceBasicEnginePlugin::GetInstance()
{
    static AtomicServiceBasicEnginePlugin instance;
    return instance;
}

std::vector<std::string> AtomicServiceBasicEnginePlugin::getParamsFromAtomicServiceBasicEngine(
    const std::string& bundleName)
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::vector<std::string> atomicServiceBasicInfo;
    if (getAtomicserviceIconInfoPlugin == nullptr) {
        return atomicServiceBasicInfo;
    }
    int32_t ret = getAtomicserviceIconInfoPlugin(bundleName, &atomicserviceIconInfo_);
    if (ret != 0) {
        return atomicServiceBasicInfo;
    }
    if (atomicserviceIconInfo_ != nullptr) {
        atomicServiceBasicInfo.push_back(atomicserviceIconInfo_->GetAppName());
        atomicServiceBasicInfo.push_back(atomicserviceIconInfo_->GetCircleIcon());
        atomicServiceBasicInfo.push_back(atomicserviceIconInfo_->GetEyelashRingIcon());
    }
    return atomicServiceBasicInfo;
}

int32_t AtomicServiceBasicEnginePlugin::releaseData()
{
    std::lock_guard<std::mutex> lock(mutex_);
    // free data
    if (freeData != nullptr && atomicserviceIconInfo_ != nullptr) {
        freeData(atomicserviceIconInfo_);
        atomicserviceIconInfo_ = nullptr;
        return 0;
    }
    TAG_LOGW(AceLogTag::ACE_WINDOW_SCENE, "dlsym FreeData interface failed, can't release data");
    return -1;
}
#endif // ATOMIC_SERVICE_ATTRIBUTION_ENABLE
} //namespace OHOS::Ace::NG
