/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/plugin/plugin_component_manager.h"

#include "iservice_registry.h"
#include "system_ability_definition.h"
#ifdef UI_SERVICE_WITH_IDL
#include "ui_service_mgr_client_idl.h"
#else
#include "ui_service_mgr_client.h"
#endif

#include "core/common/ace_engine.h"

namespace OHOS::Ace {
constexpr int64_t FOO_MAX_LEN = 20 * 1024 * 1024;
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

int PluginComponentManager::Push(const AAFwk::Want& want, const std::string& name, const std::string& jsonPath,
    const std::string& data, const std::string& extraData)
{
#ifdef UI_SERVICE_WITH_IDL
    return Ace::UIServiceMgrClientIdl::GetInstance()->Push(want, name, jsonPath, data, extraData);
#else
    return Ace::UIServiceMgrClient::GetInstance()->Push(want, name, jsonPath, data, extraData);
#endif
}

int PluginComponentManager::Request(
    const AAFwk::Want& want, const std::string& name, const std::string& jsonPath, const std::string& data)
{
    if (jsonPath.empty()) {
#ifdef UI_SERVICE_WITH_IDL
        return Ace::UIServiceMgrClientIdl::GetInstance()->Request(want, name, data);
#else
        return Ace::UIServiceMgrClient::GetInstance()->Request(want, name, data);
#endif
    } else {
        PluginComponentTemplate pluginTemplate;
        // Read external.json(assets\external.json) or jsonPath
        std::string jsonStr;
        auto packagePathStr = GetPackagePath(want);
        GetTemplatePathFromJsonFile(packagePathStr, name, jsonPath, jsonStr);
        pluginTemplate.SetSource(jsonStr);
        pluginTemplate.SetAbility(want.GetElement().GetBundleName() + "/" + want.GetElement().GetAbilityName());
        if (listener_) {
            listener_->RequestByJsonPath(pluginTemplate, data);
        }
        return 0;
    }
}

int PluginComponentManager::ReturnRequest(
    const AAFwk::Want& want, const std::string& pluginName, const std::string& data, const std::string& extraData)
{
#ifdef UI_SERVICE_WITH_IDL
    return Ace::UIServiceMgrClientIdl::GetInstance()->ReturnRequest(want, pluginName, data, extraData);
#else
    return Ace::UIServiceMgrClient::GetInstance()->ReturnRequest(want, pluginName, data, extraData);
#endif
}

void PluginComponentManager::RegisterCallBack(
    const AAFwk::Want& want, const std::shared_ptr<PluginComponentCallBack>& callback, CallBackType callBackType)
{
    if (listener_) {
        listener_->ResgisterListener(callback, callBackType);
#ifdef UI_SERVICE_WITH_IDL
        Ace::UIServiceMgrClientIdl::GetInstance()->RegisterCallBack(want, listener_);
#else
        Ace::UIServiceMgrClient::GetInstance()->RegisterCallBack(want, listener_);
#endif
    }
}

void PluginComponentManager::UnregisterCallBack(const std::shared_ptr<PluginComponentCallBack>& callback)
{
    if (listener_) {
        listener_->UnresgisterListener(callback);
    }
}

void PluginComponentManager::UnregisterCallBack(const AAFwk::Want& want)
{
#ifdef UI_SERVICE_WITH_IDL
    Ace::UIServiceMgrClientIdl::GetInstance()->UnregisterCallBack(want);
#else
    Ace::UIServiceMgrClient::GetInstance()->UnregisterCallBack(want);
#endif
}

sptr<AppExecFwk::IBundleMgr> PluginComponentManager::GetBundleManager()
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (systemAbilityMgr == nullptr) {
        return nullptr;
    }

    auto bundleObj = systemAbilityMgr->GetSystemAbility(BUNDLE_MGR_SERVICE_SYS_ABILITY_ID);
    if (bundleObj == nullptr) {
        return nullptr;
    }

    return iface_cast<AppExecFwk::IBundleMgr>(bundleObj);
}

void PluginComponentManager::UIServiceListener::UnresgisterListener(
    const std::shared_ptr<PluginComponentCallBack>& callback)
{
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    auto iter = callbacks_.find(callback);
    if (iter != callbacks_.end()) {
        callbacks_.erase(iter);
    }
}

void PluginComponentManager::UIServiceListener::ResgisterListener(
    const std::shared_ptr<PluginComponentCallBack>& callback, CallBackType callBackType)
{
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    callbackVec_.try_emplace(callback, callBackType);
}

#ifdef UI_SERVICE_WITH_IDL
ErrCode PluginComponentManager::UIServiceListener::OnPushCallBack(const AAFwk::Want& want, const std::string& name,
    const std::string& jsonPath, const std::string& data, const std::string& extraData)
#else
void PluginComponentManager::UIServiceListener::OnPushCallBack(const AAFwk::Want& want, const std::string& name,
    const std::string& jsonPath, const std::string& data, const std::string& extraData)
#endif
{
    PluginComponentTemplate pluginTemplate;
    if (!jsonPath.empty()) {
        std::string jsonStr;
        auto packagePathStr = PluginComponentManager::GetInstance()->GetPackagePath(want);
        PluginComponentManager::GetInstance()->GetTemplatePathFromJsonFile(packagePathStr, name, jsonPath, jsonStr);
        if (jsonStr.empty()) {
            jsonStr = "{}";
        }
        pluginTemplate.SetSource(jsonStr);
    } else {
        pluginTemplate.SetSource(name);
    }
    pluginTemplate.SetAbility(want.GetElement().GetBundleName() + "/" + want.GetElement().GetAbilityName());

    std::lock_guard<std::recursive_mutex> lock(mutex_);
    for (auto& callback : callbackVec_) {
        if (callback.second == CallBackType::PushEvent && callback.first != nullptr) {
            callback.first->OnPushEvent(want, pluginTemplate, data, extraData);
        }
    }
#ifdef UI_SERVICE_WITH_IDL
    return ERR_NONE;
#endif
}

#ifdef UI_SERVICE_WITH_IDL
ErrCode PluginComponentManager::UIServiceListener::OnRequestCallBack(
    const AAFwk::Want& want, const std::string& name, const std::string& data)
#else
void PluginComponentManager::UIServiceListener::OnRequestCallBack(
    const AAFwk::Want& want, const std::string& name, const std::string& data)
#endif
{
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    for (auto& callback : callbackVec_) {
        if (callback.second == CallBackType::RequestEvent && callback.first != nullptr) {
            callback.first->OnRequestEvent(want, name, data);
        }
    }
#ifdef UI_SERVICE_WITH_IDL
    return ERR_NONE;
#endif
}

#ifdef UI_SERVICE_WITH_IDL
ErrCode PluginComponentManager::UIServiceListener::OnReturnRequest(
    const AAFwk::Want& want, const std::string& source, const std::string& data, const std::string& extraData)
#else
void PluginComponentManager::UIServiceListener::OnReturnRequest(
    const AAFwk::Want& want, const std::string& source, const std::string& data, const std::string& extraData)
#endif
{
    {
        std::lock_guard<std::recursive_mutex> lock(mutex_);
        for (auto iter = callbackVec_.begin(); iter != callbackVec_.end();) {
            if (iter->second == CallBackType::RequestCallBack && iter->first != nullptr) {
                auto container = AceEngine::Get().GetContainer(iter->first->GetContainerId());
                if (!container) {
#ifdef UI_SERVICE_WITH_IDL
                    return ERR_NONE;
#else
                    return;
#endif
                }
                auto taskExecutor = container->GetTaskExecutor();
                if (!taskExecutor) {
#ifdef UI_SERVICE_WITH_IDL
                    return ERR_NONE;
#else
                    return;
#endif
                }
                taskExecutor->PostTask(
                    [callback = iter->first, want, source, data, extraData]() {
                        PluginComponentTemplate pluginTemplate;

                        if (source.empty()) {
                            pluginTemplate.SetSource("{}");
                        } else {
                            pluginTemplate.SetSource(source);
                        }
                        pluginTemplate.SetAbility(
                            want.GetElement().GetBundleName() + "/" + want.GetElement().GetAbilityName());
                        callback->OnRequestCallBack(pluginTemplate, data, extraData);
                        PluginComponentManager::GetInstance()->UnregisterCallBack(callback);
                    },
                    TaskExecutor::TaskType::JS, "ArkUIPluginReturnRequestCallback");
                callbacks_.emplace(iter->first);
                iter = callbackVec_.erase(iter);
            } else {
                iter++;
            }
        }
    }
#ifdef UI_SERVICE_WITH_IDL
    return ERR_NONE;
#endif
}

void PluginComponentManager::UIServiceListener::RequestByJsonPath(
    const PluginComponentTemplate& pluginTemplate, const std::string& data)
{
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    for (auto iter = callbackVec_.begin(); iter != callbackVec_.end();) {
        if (iter->second == CallBackType::RequestCallBack && iter->first != nullptr) {
            iter->first->OnRequestCallBack(pluginTemplate, data, "{}");
            iter = callbackVec_.erase(iter);
        } else {
            iter++;
        }
    }
}

bool PluginComponentManager::GetTemplatePathFromJsonFile(
    const std::string& packagePathStr, const std::string& pluginName, const std::string& jsonPath, std::string& jsonStr)
{
    std::string external = std::string("/external.json");
    auto externalPath = packagePathStr + external;
    if (!jsonPath.empty()) {
        externalPath = jsonPath;
    }
    char realPath[PATH_MAX] = { 0x00 };
    if (realpath(externalPath.c_str(), realPath) == nullptr) {
        TAG_LOGW(AceLogTag::ACE_PLUGIN_COMPONENT,
            "Get path from Json fail! FilePath is: %{private}s, fail reason: %{public}s", externalPath.c_str(),
            strerror(errno));
        return false;
    }
    std::unique_ptr<FILE, decltype(&std::fclose)> file(std::fopen(realPath, "rb"), std::fclose);
    if (!file) {
        TAG_LOGW(AceLogTag::ACE_PLUGIN_COMPONENT, "Open file failed, filePath: %{private}s, fail reason: %{public}s",
            externalPath.c_str(), strerror(errno));
        return false;
    }
    if (std::fseek(file.get(), 0, SEEK_END) != 0) {
        return false;
    }

    int64_t size = std::ftell(file.get());
    if (size == -1L || size == 0L || size > FOO_MAX_LEN) {
        return false;
    }
    char* fileData = new (std::nothrow) char[size];
    if (fileData == nullptr) {
        return false;
    }
    rewind(file.get());
    std::unique_ptr<char[]> jsonStream(fileData);
    size_t result = std::fread(jsonStream.get(), 1, size, file.get());
    if (result != (size_t)size) {
        return false;
    }

    std::string jsonString(jsonStream.get(), jsonStream.get() + size);
    if (pluginName.empty()) {
        jsonStr = jsonString;
    } else {
        auto rootJson = JsonUtil::ParseJsonString(jsonString);
        if (rootJson) {
            jsonStr = rootJson->GetString(pluginName);
        }
    }

    return true;
}

std::string PluginComponentManager::GetPackagePath(const AAFwk::Want& want) const
{
    std::string packagePathStr;

    if (want.GetElement().GetBundleName().empty()) {
        return packagePathStr;
    }
    auto bms = PluginComponentManager::GetInstance()->GetBundleManager();
    if (!bms) {
        return packagePathStr;
    }

    if (want.GetElement().GetAbilityName().empty()) {
        AppExecFwk::BundleInfo bundleInfo;
        bool ret = bms->GetBundleInfo(
            want.GetElement().GetBundleName(), AppExecFwk::BundleFlag::GET_BUNDLE_DEFAULT, bundleInfo);
        if (!ret) {
            return packagePathStr;
        }
        packagePathStr = bundleInfo.applicationInfo.entryDir + "/";
    } else {
        AppExecFwk::AbilityInfo abilityInfo;
        bool ret = bms->QueryAbilityInfo(want, abilityInfo);
        if (!ret) {
            return packagePathStr;
        }
        packagePathStr = abilityInfo.applicationInfo.codePath + "/" + abilityInfo.package + "/";
    }
    return packagePathStr;
}
} // namespace OHOS::Ace
