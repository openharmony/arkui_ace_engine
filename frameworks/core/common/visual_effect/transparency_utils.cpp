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

#include "core/common/visual_effect/transparency_utils.h"

#include "errors.h"
#include "ui/properties/ui_material_enums.h"

#include "base/log/log_wrapper.h"
#include "base/utils/system_properties.h"
#include "core/common/setting_data_manager.h"
#include "core/components_ng/base/frame_node.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
namespace {
const std::string SETTING_TRANSPARENCY = "immersive_transparency_level";
constexpr int32_t DEFAULT_USER_ID = 100;
constexpr int32_t INVALID_ID = -1;
constexpr int32_t DIFF = 3;
} // namespace

bool TransparencyUtils::transparencyLevelGet_ = false;
int32_t TransparencyUtils::userId_ = DEFAULT_USER_ID;
bool TransparencyUtils::userIdGet_ = false;
bool TransparencyUtils::listenerSet_ = false;
TransparencyIdMap TransparencyUtils::callbackIdsMap_ {};
std::mutex TransparencyUtils::callbackMutex_;
int32_t TransparencyUtils::callbackId_ = INVALID_ID;

int32_t TransparencyUtils::GetTransparencyLevel(int32_t materialLevel)
{
    if (materialLevel >= static_cast<int32_t>(UiMaterialLevel::SMOOTH) ||
        materialLevel < static_cast<int32_t>(UiMaterialLevel::EXQUISITE)) {
        return static_cast<int32_t>(UiMaterialTransparency::NONE);
    }

    UiMaterialLevel materialLevelValue = static_cast<UiMaterialLevel>(materialLevel);
    int32_t transparency = static_cast<int32_t>(LookupTransparency(materialLevelValue));
    if (transparencyLevelGet_) {
        return transparency;
    }

    SettingDataManager& manager = SettingDataManager::GetInstance();
    if (!manager.IsInitialized()) {
        auto code = manager.Initialize();
        if (code != ERR_OK || manager.IsInitialized() == false) {
            return transparency;
        }
    }
    auto code = manager.GetInt32ValueStrictly(SETTING_TRANSPARENCY, transparency, GetCurrentUserId());
    TAG_LOGD(AceLogTag::ACE_VISUAL_EFFECT, "TransparencyUtils::GetTransparencyLevel from settings: %{public}d",
        transparency);

    AdjustTransparencyForLevel(transparency);
    if (code == ERR_OK || code == ERR_NAME_NOT_FOUND) {
        transparencyLevelGet_ = true;
    }
    return static_cast<int32_t>(LookupTransparency(materialLevelValue));
}

void TransparencyUtils::AdjustTransparencyForLevel(int32_t transparency)
{
    std::unique_lock lock(GetLevelLock());
    auto& levelMap = GetLevelMap();
    if (transparency >= static_cast<int32_t>(UiMaterialTransparency::GENTLE_THIN) &&
        transparency <= static_cast<int32_t>(UiMaterialTransparency::GENTLE_THICK)) {
        levelMap[UiMaterialLevel::GENTLE] = static_cast<UiMaterialTransparency>(transparency);
        levelMap[UiMaterialLevel::EXQUISITE] = static_cast<UiMaterialTransparency>(transparency - DIFF);
    } else if (transparency >= static_cast<int32_t>(UiMaterialTransparency::THIN) &&
               transparency <= static_cast<int32_t>(UiMaterialTransparency::THICK)) {
        levelMap[UiMaterialLevel::EXQUISITE] = static_cast<UiMaterialTransparency>(transparency);
        levelMap[UiMaterialLevel::GENTLE] = static_cast<UiMaterialTransparency>(transparency + DIFF);
    }
}

TransparencyLevelMap& TransparencyUtils::GetLevelMap()
{
    // EXQUISITE->NORMAL, GENTLE->GENTLE_NORMAL, SMOOTH->NONE
    static TransparencyLevelMap levelMap = {
        { UiMaterialLevel::EXQUISITE, UiMaterialTransparency::NORMAL },
        { UiMaterialLevel::GENTLE, UiMaterialTransparency::GENTLE_NORMAL },
        { UiMaterialLevel::SMOOTH, UiMaterialTransparency::NONE }
    };
    return levelMap;
}

std::shared_mutex& TransparencyUtils::GetLevelLock()
{
    static std::shared_mutex mtx;
    return mtx;
}

UiMaterialTransparency TransparencyUtils::LookupTransparency(UiMaterialLevel level)
{
    std::shared_lock lock(GetLevelLock());
    auto& levelMap = GetLevelMap();
    auto iter = levelMap.find(level);
    return iter != levelMap.end() ? iter->second : UiMaterialTransparency::NONE;
}

int32_t TransparencyUtils::GetCurrentUserId()
{
    if (userIdGet_) {
        return userId_;
    }
    SettingDataManager& manager = SettingDataManager::GetInstance();
    int32_t currentUserId = manager.GetCurrentUserId();
    if (currentUserId != INVALID_ID) {
        userId_ = currentUserId;
        userIdGet_ = true;
    }
    return userId_;
}

std::optional<int32_t> TransparencyUtils::RegisterTransparencyListener(
    const WeakPtr<NG::FrameNode>& node, TransparencyCallback&& callback)
{
    if (RegisterListenerInner()) {
        auto containerId = Container::CurrentIdSafelyWithCheck();
        if (containerId < 0) {
            TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "invalid container id when register transparency listener");
            return std::nullopt;
        }
        std::lock_guard<std::mutex> lock(callbackMutex_);
        callbackIdsMap_[++callbackId_] = { std::move(callback), node, containerId };
        return callbackId_;
    }
    return std::nullopt;
}

bool TransparencyUtils::RegisterListenerInner()
{
    if (listenerSet_) {
        return true;
    }
    SettingDataManager& manager = SettingDataManager::GetInstance();
    if (!manager.IsInitialized()) {
        auto code = manager.Initialize();
        if (code != ERR_OK || manager.IsInitialized() == false) {
            return false;
        }
    }
    auto code = manager.RegisterObserver(
        SETTING_TRANSPARENCY.c_str(), &TransparencyUtils::OnParameterChanged, GetCurrentUserId());
    if (code != ERR_OK) {
        return false;
    }
    listenerSet_ = true;
    return true;
}

void TransparencyUtils::OnParameterChanged(const std::string& key, int32_t userId)
{
    transparencyLevelGet_ = false;
    ExecuteTransparencyCallback();
}

void TransparencyUtils::ExecuteTransparencyCallback()
{
    decltype(callbackIdsMap_) callbackIdsCopy;
    std::unordered_map<int32_t, std::list<TransparencyMapData>> nodesByContainer;
    {
        std::lock_guard<std::mutex> lock(callbackMutex_);
        for (auto it = callbackIdsMap_.begin(); it != callbackIdsMap_.end();) {
            auto& value = it->second;
            auto frameNode = value.node.Upgrade();
            if (frameNode) {
                nodesByContainer[value.containerId].emplace_back(value);
                ++it;
            } else {
                it = callbackIdsMap_.erase(it);
            }
        }
    }
    int32_t materialLevel = static_cast<int32_t>(SystemProperties::GetUiMaterialLevel());
    int32_t transparencyLevel = GetTransparencyLevel(materialLevel);
    if (transparencyLevel == static_cast<int32_t>(UiMaterialTransparency::NONE)) {
        return;
    }
    for (auto& [containerId, dataList] : nodesByContainer) {
        ContainerScope scope(containerId);
        auto taskExecutor = Container::CurrentTaskExecutorSafelyWithCheck();
        if (!taskExecutor) {
            TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "cannot find taskExecutor of %{public}d", containerId);
            continue;
        }
        taskExecutor->PostTask(
            [dataList = std::move(dataList), transparencyLevel, id = containerId]() {
                ContainerScope scope(id);
                HandleNodesCallback(dataList, transparencyLevel);
            },
            TaskExecutor::TaskType::UI, "ArkUIMaterialTransparencyCallback");
    }
}

void TransparencyUtils::HandleNodesCallback(const std::list<TransparencyMapData>& datas, int32_t transparency)
{
    for (auto& data : datas) {
        auto node = data.node.Upgrade();
        const auto& callback = data.callback;
        if (!node || !callback) {
            continue;
        }
        auto pipeline = node->GetAttachedContext();
        if (pipeline) {
            if (pipeline->GetInstanceId() == data.containerId) {
                // most normal case
                callback(transparency);
                continue;
            }
            auto taskExecutor = pipeline->GetTaskExecutor();
            if (!taskExecutor) {
                TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "pipeline has no taskExecutor");
                continue;
            }
            if (taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
                ContainerScope scope(pipeline->GetInstanceId());
                callback(transparency);
                continue;
            }
            taskExecutor->PostTask([callback, transparency]() { callback(transparency); }, TaskExecutor::TaskType::UI,
                "ArkUIMaterialTransparencyAgainCallback");
            continue;
        }
        TAG_LOGD(AceLogTag::ACE_VISUAL_EFFECT, "execute callback not on tree, node id:%{public}d", node->GetId());
        callback(transparency);
    }
}

void TransparencyUtils::UnRegisterTransparencyListener(int32_t callbackId)
{
    std::lock_guard<std::mutex> lock(callbackMutex_);
    if (callbackIdsMap_.empty()) {
        return;
    }
    auto iter = callbackIdsMap_.find(callbackId);
    if (iter != callbackIdsMap_.end()) {
        callbackIdsMap_.erase(iter);
    }
}
} // namespace OHOS::Ace
