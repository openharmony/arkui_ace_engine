/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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

#include "core/common/container.h"

#include "core/common/ace_engine.h"
#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/common/plugin_manager.h"
#endif

#include <dirent.h>

#include "core/components_ng/pattern/window_scene/helper/window_scene_helper.h"

namespace OHOS::Ace {

int32_t Container::CurrentId()
{
    return ContainerScope::CurrentId();
}

int32_t Container::SafelyId()
{
    uint32_t containerCount = ContainerScope::ContainerCount();
    if (containerCount == 0) {
        return INSTANCE_ID_UNDEFINED;
    }
    if (containerCount == 1) {
        return ContainerScope::SingletonId();
    }
    int32_t currentId = ContainerScope::RecentActiveId();
    if (currentId >= 0) {
        return currentId;
    }
    currentId = ContainerScope::RecentForegroundId();
    if (currentId >= 0) {
        return currentId;
    }
    return ContainerScope::DefaultId();
}

int32_t Container::CurrentIdSafely()
{
    int32_t currentId = ContainerScope::CurrentId();
    if (currentId >= 0) {
        return currentId;
    }
    return SafelyId();
}

RefPtr<Container> Container::Current()
{
    return AceEngine::Get().GetContainer(ContainerScope::CurrentId());
}

RefPtr<Container> Container::CurrentSafely()
{
    return AceEngine::Get().GetContainer(Container::CurrentIdSafely());
}

RefPtr<Container> Container::CurrentSafelyWithCheck()
{
    int32_t currentId = CurrentId();
    if (currentId >= 0) {
        auto container = GetContainer(currentId);
        if (container) {
            return container;
        }
    }
    currentId = SafelyId();
    return GetContainer(currentId);
}

int32_t Container::CurrentIdSafelyWithCheck()
{
    int32_t currentId = CurrentId();
    if (currentId >= 0) {
        if (AceEngine::Get().HasContainer(currentId)) {
            return currentId;
        }
    }
    return SafelyId();
}

RefPtr<Container> Container::GetContainer(int32_t containerId)
{
    return AceEngine::Get().GetContainer(containerId);
}

RefPtr<Container> Container::GetActive()
{
    RefPtr<Container> activeContainer;
    AceEngine::Get().NotifyContainers([&activeContainer](const RefPtr<Container>& container) {
        auto front = container->GetFrontend();
        if (front && front->IsForeground()) {
            activeContainer = container;
        }
    });
    return activeContainer;
}

RefPtr<Container> Container::GetDefault()
{
    RefPtr<Container> defaultContainer;
    AceEngine::Get().NotifyContainers([&defaultContainer](const RefPtr<Container>& container) {
        auto front = container->GetFrontend();
        if (front) {
            defaultContainer = container;
        }
    });
    return defaultContainer;
}

RefPtr<Container> Container::GetFoucsed()
{
    RefPtr<Container> foucsContainer;
    AceEngine::Get().NotifyContainers([&foucsContainer](const RefPtr<Container>& container) {
        auto pipeline = container->GetPipelineContext();
        if (pipeline && pipeline->IsWindowFocused()) {
            foucsContainer = container;
        }
    });
    return foucsContainer;
}

RefPtr<Container> Container::GetByWindowId(uint32_t windowId)
{
    RefPtr<Container> windowContainer;
    AceEngine::Get().NotifyContainers([&windowContainer, windowId](const RefPtr<Container>& container) {
        if (windowId == container->GetWindowId()) {
            windowContainer = container;
        }
    });
    return windowContainer;
}

RefPtr<TaskExecutor> Container::CurrentTaskExecutor()
{
    auto curContainer = Current();
    CHECK_NULL_RETURN(curContainer, nullptr);
    return curContainer->GetTaskExecutor();
}

RefPtr<TaskExecutor> Container::CurrentTaskExecutorSafely()
{
    auto curContainer = CurrentSafely();
    CHECK_NULL_RETURN(curContainer, nullptr);
    return curContainer->GetTaskExecutor();
}

RefPtr<TaskExecutor> Container::CurrentTaskExecutorSafelyWithCheck()
{
    auto curContainer = CurrentSafelyWithCheck();
    CHECK_NULL_RETURN(curContainer, nullptr);
    return curContainer->GetTaskExecutor();
}

void Container::UpdateCurrent(int32_t id)
{
    ContainerScope::UpdateCurrent(id);
}

bool Container::UpdateState(const Frontend::State& state)
{
    std::lock_guard<std::mutex> lock(stateMutex_);
    if (state_ == state) {
        return false;
    }
    state_ = state;
    return true;
}

bool Container::Dump(const std::vector<std::string>& params, std::vector<std::string>& info)
{
    std::string tip("container not support, type:");
    tip.append(AceType::TypeName(this));
    info.emplace_back(tip);
    return true;
}

bool Container::IsIdAvailable(int32_t id)
{
    return !AceEngine::Get().GetContainer(id);
}

void Container::SetFontScale(int32_t instanceId, float fontScale)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetFontScale(fontScale);
}

void Container::SetFontWeightScale(int32_t instanceId, float fontWeightScale)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetFontWeightScale(fontWeightScale);
}

RefPtr<DisplayInfo> Container::GetDisplayInfo()
{
    return displayManager_->GetDisplayInfo(currentDisplayId_);
}

void Container::InitIsFoldable()
{
    displayManager_->InitIsFoldable();
}

bool Container::IsFoldable()
{
    return displayManager_->GetIsFoldable();
}

FoldStatus Container::GetCurrentFoldStatus()
{
    return displayManager_->GetCurrentFoldStatus();
}

std::vector<Rect> Container::GetCurrentFoldCreaseRegion()
{
    return displayManager_->GetCurrentFoldCreaseRegion();
}

void Container::DestroyToastSubwindow(int32_t instanceId)
{
    auto subwindow = SubwindowManager::GetInstance()->GetToastSubwindow(instanceId);
    if (subwindow && subwindow->IsToastSubWindow()) {
        subwindow->DestroyWindow();
    }
    auto systemToastWindow = SubwindowManager::GetInstance()->GetSystemToastWindow(instanceId);
    if (systemToastWindow && systemToastWindow->IsToastSubWindow()) {
        systemToastWindow->DestroyWindow();
    }
}

void Container::DestroySelectOverlaySubwindow(int32_t instanceId)
{
    auto subwindow = SubwindowManager::GetInstance()->GetSelectOverlaySubwindow(instanceId);
    if (subwindow && subwindow->GetIsSelectOverlaySubWindow()) {
        subwindow->DestroyWindow();
        TAG_LOGI(AceLogTag::ACE_SUB_WINDOW, "Destroy selectOverlay subwindow, instanceId is %{public}d", instanceId);
    }
}

bool Container::IsFontFileExistInPath(const std::string& path)
{
    DIR* dir;
    struct dirent* ent;
    bool isFlagFileExist = false;
    bool isFontDirExist = false;
    if ((dir = opendir(path.c_str())) == nullptr) {
        if (errno == ENOENT) {
            LOGE("ERROR ENOENT");
        } else if (errno == EACCES) {
            LOGE("ERROR EACCES");
        } else {
            LOGE("ERROR Other");
        }
        return false;
    }
    while ((ent = readdir(dir)) != nullptr) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }
        if (strcmp(ent->d_name, "flag") == 0) {
            isFlagFileExist = true;
        } else if (strcmp(ent->d_name, "fonts") == 0) {
            isFontDirExist = true;
        }
    }
    closedir(dir);
    if (isFlagFileExist && isFontDirExist) {
        LOGI("font path exist");
        return true;
    }
    return false;
}

std::string Container::GetFontFamilyName(std::string path)
{
    std::string fontFamilyName = "";
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(path.c_str())) == nullptr) {
        return fontFamilyName;
    }
    while ((ent = readdir(dir)) != nullptr) {
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }
        if (endsWith(ent->d_name, ".ttf")) {
            fontFamilyName = ent->d_name;
            break;
        }
    }
    closedir(dir);
    return fontFamilyName;
}

bool Container::endsWith(std::string str, std::string suffix)
{
    if (str.length() < suffix.length()) {
        return false;
    }
    return str.substr(str.length() - suffix.length()) == suffix;
}

template<>
int32_t Container::GenerateId<PLUGIN_SUBCONTAINER>()
{
#ifdef PLUGIN_COMPONENT_SUPPORTED
    return PluginManager::GetInstance().GetPluginSubContainerId();
#else
    return INSTANCE_ID_UNDEFINED;
#endif
}

bool Container::IsNodeInKeyGuardWindow(const RefPtr<NG::FrameNode>& node)
{
#ifdef WINDOW_SCENE_SUPPORTED
    return NG::WindowSceneHelper::IsNodeInKeyGuardWindow(node);
#else
    return false;
#endif
}
bool Container::CheckRunOnThreadByThreadId(int32_t currentId, bool defaultRes)
{
    auto container = GetContainer(currentId);
    CHECK_NULL_RETURN(container, defaultRes);
    auto executor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(executor, defaultRes);
    return executor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI);
}
} // namespace OHOS::Ace
