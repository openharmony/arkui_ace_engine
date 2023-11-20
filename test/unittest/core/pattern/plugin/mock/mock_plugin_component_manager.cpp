/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <memory>

#include "mock_bundle_mgr_interface.h"
#include "refbase.h"

#include "core/components/plugin/plugin_component_manager.h"

namespace OHOS::AppExecFwk {
sptr<AppExecFwk::IBundleMgr> bms = nullptr;

void MOCKIBundleMgr::ReleaseInstance()
{
    bms = nullptr;
}

void MOCKIBundleMgr::CreateInstance()
{
    bms = sptr<AppExecFwk::IBundleMgr>(new (std::nothrow) AppExecFwk::MOCKIBundleMgr());
}

sptr<IBundleMgr> MOCKIBundleMgr::GetInstance()
{
    return bms;
}
} // namespace OHOS::AppExecFwk

namespace OHOS::Ace {
std::shared_ptr<PluginComponentManager> PluginComponentManager::instance_ = nullptr;
std::mutex PluginComponentManager::mutex_;

std::shared_ptr<PluginComponentManager> PluginComponentManager::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_ = std::make_shared<PluginComponentManager>();
        }
    }
    return instance_;
}

void PluginComponentManager::RegisterCallBack(
    const AAFwk::Want& want, const std::shared_ptr<PluginComponentCallBack>& callback, CallBackType callBackType)
{}

void PluginComponentManager::UnregisterCallBack(const AAFwk::Want& want) {}

sptr<AppExecFwk::IBundleMgr> PluginComponentManager::GetBundleManager()
{
    return AppExecFwk::MOCKIBundleMgr::GetInstance();
}

void PluginComponentManager::UIServiceListener::ResgisterListener(
    const std::shared_ptr<PluginComponentCallBack>& callback, CallBackType callBackType)
{}

void PluginComponentManager::UIServiceListener::OnPushCallBack(const AAFwk::Want& want, const std::string& name,
    const std::string& jsonPath, const std::string& data, const std::string& extraData)
{}

void PluginComponentManager::UIServiceListener::OnRequestCallBack(
    const AAFwk::Want& want, const std::string& name, const std::string& data)
{}

void PluginComponentManager::UIServiceListener::OnReturnRequest(
    const AAFwk::Want& want, const std::string& source, const std::string& data, const std::string& extraData)
{}

void PluginComponentManager::UIServiceListener::RequestByJsonPath(
    const PluginComponentTemplate& pluginTemplate, const std::string& data)
{}

bool PluginComponentManager::GetTemplatePathFromJsonFile(
    const std::string& packagePathStr, const std::string& pluginName, const std::string& jsonPath, std::string& jsonStr)
{
    return true;
}

std::string PluginComponentManager::GetPackagePath(const AAFwk::Want& want) const
{
    std::string packagePathStr;
    return packagePathStr;
}
} // namespace OHOS::Ace
