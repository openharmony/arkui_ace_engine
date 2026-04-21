/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/common/back_press_handler_manager.h"

#include "base/thread/task_executor.h"

namespace OHOS::Ace::NG {

void BackPressHandlerManager::AddBackPressHandler(const WeakPtr<FrameNode>& frameNode, std::function<bool()>&& callback)
{
    std::lock_guard<std::mutex> lock(handlersMutex_);
    backPressHandlers_[frameNode] = std::move(callback);
}

void BackPressHandlerManager::RemoveBackPressHandler(const WeakPtr<FrameNode>& frameNode)
{
    std::lock_guard<std::mutex> lock(handlersMutex_);
    backPressHandlers_.erase(frameNode);
}

bool BackPressHandlerManager::OnBackPressed(const RefPtr<TaskExecutor>& taskExecutor)
{
    CHECK_NULL_RETURN(taskExecutor, false);
    auto isBackPressedHandledByManager = false;
    taskExecutor->PostSyncTask(
        [weakBackPressHandlerManager = AceType::WeakClaim(this), &isBackPressedHandledByManager]() {
            auto backPressHandlerManager = weakBackPressHandlerManager.Upgrade();
            CHECK_NULL_VOID(backPressHandlerManager);
            isBackPressedHandledByManager = backPressHandlerManager->HandleBackPressed();
        },
        TaskExecutor::TaskType::UI, "ArkUIBackPressedHandleBackPressManager");
    return isBackPressedHandledByManager;
}

bool BackPressHandlerManager::HandleBackPressed()
{
    std::map<WeakPtr<FrameNode>, std::function<bool()>> backPressHandlers;
    {
        std::lock_guard<std::mutex> lock(handlersMutex_);
        backPressHandlers = std::move(backPressHandlers_);
    }
    bool isBackPressedHandled = false;
    for (auto iter = backPressHandlers.rbegin(); iter != backPressHandlers.rend(); ++iter) {
        auto& callback = iter->second;
        if (!callback) {
            continue;
        }
        isBackPressedHandled = callback() || isBackPressedHandled;
    }
    return isBackPressedHandled;
}
} // namespace OHOS::Ace::NG
