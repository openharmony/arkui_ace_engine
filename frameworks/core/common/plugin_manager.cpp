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

#include "core/common/plugin_manager.h"

namespace OHOS::Ace {
PluginManager::PluginManager() {}

PluginManager::~PluginManager()
{
    pluginSubContainerMap_.clear();
    nonmatchedContainerMap_.clear();
}

void PluginManager::AddPluginSubContainer(int64_t pluginId, const RefPtr<PluginSubContainer>& pluginSubContainer)
{
    std::lock_guard<std::mutex> lock(mutex_);
    pluginSubContainerMap_.try_emplace(pluginId, pluginSubContainer);
}

void PluginManager::RemovePluginSubContainer(int64_t pluginId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    pluginSubContainerMap_.erase(pluginId);
}

RefPtr<PluginSubContainer> PluginManager::GetPluginSubContainer(int64_t pluginId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto pluginSubContainer = pluginSubContainerMap_.find(pluginId);
    if (pluginSubContainer != pluginSubContainerMap_.end()) {
        return pluginSubContainer->second;
    } else {
        return nullptr;
    }
}

void PluginManager::UpdateConfigurationInPlugin(
    const ResourceConfiguration& resConfig, const RefPtr<TaskExecutor>& taskExecutor)
{
    std::lock_guard<std::mutex> lock(mutex_);
    for (const auto& pluginSubContainerMap : pluginSubContainerMap_) {
        auto pluginSubContainer = pluginSubContainerMap.second;
        auto pluginPipeline = pluginSubContainer->GetPipelineContext();
        if (!pluginPipeline) {
            continue;
        }
        auto pluginThemeManager = pluginPipeline->GetThemeManager();
        pluginThemeManager->UpdateConfig(resConfig);
        pluginThemeManager->LoadResourceThemes();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [instanceId = static_cast<int32_t>(pluginSubContainerMap.first),
                weak = AceType::WeakClaim(AceType::RawPtr(pluginSubContainer))]() {
                ContainerScope scope(instanceId);
                auto pluginSubContainer = weak.Upgrade();
                CHECK_NULL_VOID(pluginSubContainer);
                pluginSubContainer->FlushReload();
            },
            TaskExecutor::TaskType::JS, "ArkUIPluginFlushReload");
    }
}

void PluginManager::AddNonmatchedContainer(
    const std::string& pluginKey, const RefPtr<PluginSubContainer>& pluginSubContainer)
{
    std::lock_guard<std::mutex> lock(nonmatchedContainerMutex_);
    nonmatchedContainerMap_.try_emplace(pluginKey, pluginSubContainer);
}

RefPtr<PluginSubContainer> PluginManager::MatchPluginSubContainerWithPluginId(
    int64_t pluginId, const std::string& pluginKey)
{
    std::lock_guard<std::mutex> lock(nonmatchedContainerMutex_);
    auto iter = nonmatchedContainerMap_.find(pluginKey);
    if (iter == nonmatchedContainerMap_.end()) {
        TAG_LOGI(AceLogTag::ACE_PLUGIN_COMPONENT, "no subcontainer of key: %{private}s", pluginKey.c_str());
        return nullptr;
    }
    auto pluginSubContainer = iter->second;
    AddPluginSubContainer(pluginId, pluginSubContainer);
    nonmatchedContainerMap_.erase(iter);
    return pluginSubContainer;
}

int64_t PluginManager::GetPluginSubContainerId()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pluginSubContainerMap_.empty()) {
        return MIN_PLUGIN_SUBCONTAINER_ID;
    }
    return pluginSubContainerMap_.rbegin()->first + 1;
}

int32_t PluginManager::StartAbility(
    const std::string& bundleName, const std::string& abilityName, const std::string& params)
{
    CHECK_NULL_RETURN(pluginUtils_, -1);
    return pluginUtils_->StartAbility(bundleName, abilityName, params);
}

void PluginManager::AddPluginParentContainer(int64_t pluginId, int32_t pluginParentContainerId)
{
    std::lock_guard<std::mutex> lock(parentContainerMutex_);
    parentContainerMap_.try_emplace(pluginId, pluginParentContainerId);
}

void PluginManager::RemovePluginParentContainer(int64_t pluginId)
{
    std::lock_guard<std::mutex> lock(parentContainerMutex_);
    parentContainerMap_.erase(pluginId);
}

int32_t PluginManager::GetPluginParentContainerId(int64_t pluginId)
{
    std::lock_guard<std::mutex> lock(parentContainerMutex_);
    auto result = parentContainerMap_.find(pluginId);
    if (result != parentContainerMap_.end()) {
        return result->second;
    } else {
        return 0;
    }
}
} // namespace OHOS::Ace
