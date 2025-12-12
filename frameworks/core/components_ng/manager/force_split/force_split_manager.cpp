/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/force_split/force_split_manager.h"

#include "base/log/dump_log.h"
#include "base/utils/system_properties.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/common/force_split/force_split_utils.h"

namespace OHOS::Ace::NG {
void ForceSplitManager::SetForceSplitEnable(bool isForceSplit)
{
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "%{public}s forceSplit", (isForceSplit ? "enable" : "disable"));
    /**
     * As long as the application supports force split, regardless of whether it is enabled or not,
     * the SetForceSplitEnable interface will be called.
     */
    isForceSplitSupported_ = true;
    if (isForceSplitEnable_ == isForceSplit) {
        return;
    }
    isForceSplitEnable_ = isForceSplit;
    auto context = pipeline_.Upgrade();
    CHECK_NULL_VOID(context);
    UpdateIsInForceSplitMode();
    auto width = context->GetWindowOriginalWidth();
    if (width > 0) {
        context->ForceUpdateDesignWidthScale(width);
        auto rootNode = context->GetRootElement();
        CHECK_NULL_VOID(rootNode);
        const auto& geometryNode = rootNode->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        geometryNode->ResetParentLayoutConstraint();
        rootNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    NotifyForceSplitStateChange();
}
 
void ForceSplitManager::NotifyForceFullScreenChange(bool isForceFullScreen)
{
    auto context = pipeline_.Upgrade();
    CHECK_NULL_VOID(context);
    auto windowManager = context->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    windowManager->NotifyForceFullScreenChange(isForceFullScreen);
}

void ForceSplitManager::UpdateIsInForceSplitMode()
{
    if (!isForceSplitSupported_) {
        return;
    }
 
    auto context = pipeline_.Upgrade();
    CHECK_NULL_VOID(context);
    auto container = Container::GetContainer(context->GetInstanceId());
    CHECK_NULL_VOID(container);
    auto windowManager = context->GetWindowManager();
    CHECK_NULL_VOID(windowManager);
    bool forceSplitSuccess = false;
    if (isForceSplitEnable_) {
        /**
         * The force split mode must meet the following conditions to take effect:
         *   1. Belonging to the main window of the application
         *   2. The application is not in split screen mode
         */
        bool isMainWindow = container->IsMainWindow();
        auto windowMode = windowManager->GetWindowMode();
        bool isInSplitScreenMode = windowMode == WindowMode::WINDOW_MODE_SPLIT_PRIMARY ||
            windowMode == WindowMode::WINDOW_MODE_SPLIT_SECONDARY;
        forceSplitSuccess = isMainWindow && !isInSplitScreenMode;
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "ForceSplitManager calc splitMode, isMainWindow:%{public}d, "
            "isInSplitScreenMode:%{public}d, forceSplitSuccess:%{public}d",
            isMainWindow, isInSplitScreenMode, forceSplitSuccess);
    }
    context->SetIsCurrentInForceSplitMode(forceSplitSuccess);
}

void ForceSplitManager::AddForceSplitStateListener(int32_t nodeId, std::function<void()>&& listener)
{
    forceSplitListeners_[nodeId] = std::move(listener);
}

void ForceSplitManager::RemoveForceSplitStateListener(int32_t nodeId)
{
    auto it = forceSplitListeners_.find(nodeId);
    if (it != forceSplitListeners_.end()) {
        forceSplitListeners_.erase(it);
    }
}

void ForceSplitManager::NotifyForceSplitStateChange()
{
    auto listeners = forceSplitListeners_;
    for (auto& pair : listeners) {
        if (pair.second) {
            pair.second();
        }
    }
}
} // namespace OHOS::Ace::NG