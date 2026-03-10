/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "adapter/ohos/entrance/event_compatible/compatible_interface.h"

#include "iservice_registry.h"

#include "base/log/log_wrapper.h"
#include "adapter/ohos/entrance/event_compatible/compatible_manager_ext.h"

using namespace OHOS::AppExecFwk;

namespace OHOS::Ace::NG {

const int32_t BUNDLE_MGR_SERVICE_SYS_ABILITY_ID = 401;
const int32_t COMPATIBLE_INPUT_MODE = 1;
constexpr const char* DEVICE_TYPE_PC = "2in1";

void CompatibleInterface::LoadBundleInfo()
{
    if (!isQueryBundleInfo_) {
        std::lock_guard<std::mutex> lock(compatibleBundleInfoMutex_);
        if (!isQueryBundleInfo_ && QueryBundleInfo()) {
            isQueryBundleInfo_ = true;
        }
    }
}

bool CompatibleInterface::MatchCompatibleCondition()
{
    LoadBundleInfo();
    auto manager = DelayedSingleton<CompatibleManagerExt>::GetInstance();
    if (manager == nullptr) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "fail to get manager instance.");
        return false;
    }
    int32_t inputMode = manager->GetCompatibleinputMode(bundleName_);
    if (inputMode == COMPATIBLE_INPUT_MODE) {
        return true;
    }
    return false;
}

CompatibleInfo CompatibleInterface::MatchMouseTransformState()
{
    LoadBundleInfo();
    auto manager = DelayedSingleton<CompatibleManagerExt>::GetInstance();
    if (manager == nullptr) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "fail to get manager instance.");
        return CompatibleInfo(false);
    }
    return manager->GetCompatibleMouseTransform(bundleName_);
}

bool CompatibleInterface::IsAppDevelopedForPC()
{
    LoadBundleInfo();
    return isAppDevelopedForPC_;
}

bool CompatibleInterface::QueryBundleInfo()
{
    auto systemAbilityManager = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (!systemAbilityManager) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "fail to get system ability mgr.");
        return false;
    }
    auto remoteObject = systemAbilityManager->CheckSystemAbility(BUNDLE_MGR_SERVICE_SYS_ABILITY_ID);
    if (!remoteObject) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "fail to valid system ability mgr.");
        return false;
    }
    sptr<AppExecFwk::IBundleMgr> bundleMgrProxy = iface_cast<IBundleMgr>(remoteObject);
    if (!bundleMgrProxy) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "fail to get bundle manager proxy.");
        return false;
    }
    AppExecFwk::BundleInfo bundleInfo;
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "get bundle manager proxy success.");
    auto getInfoResult = bundleMgrProxy->GetBundleInfoForSelf(
        static_cast<int32_t>(AppExecFwk::GetBundleInfoFlag::GET_BUNDLE_INFO_WITH_HAP_MODULE), bundleInfo);
    if (getInfoResult != 0) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "fail to get bundle info.");
        return false;
    }
    std::string bundleName = bundleInfo.name;
    if (bundleName.empty()) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "fail to get bundle name.");
        return false;
    }
    bundleName_ = bundleName;
    PrepareSupportPCInfo(bundleInfo);
    return true;
}

void CompatibleInterface::PrepareSupportPCInfo(const AppExecFwk::BundleInfo& bundleInfo)
{
    if (bundleInfo.hapModuleInfos.empty()) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "hapModuleInfos is empty");
        isAppDevelopedForPC_ = false;
        return;
    }
    for (const auto& hapModuleInfo : bundleInfo.hapModuleInfos) {
        auto deviceTypes = hapModuleInfo.deviceTypes;
        if (deviceTypes.empty()) {
            TAG_LOGD(AceLogTag::ACE_XCOMPONENT, "bundle deviceTypes is empty, treat as 2in1.");
            continue;
        }
        if (std::find(deviceTypes.begin(), deviceTypes.end(), DEVICE_TYPE_PC) == deviceTypes.end()) {
            isAppDevelopedForPC_ = false;
            return;
        }
    }
    isAppDevelopedForPC_ = true;
    return;
}
} // namespace OHOS::Ace::NG
