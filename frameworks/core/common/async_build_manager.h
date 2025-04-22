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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ASYNC_BUILD_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ASYNC_BUILD_MANAGER_H

#include <functional>
#include <mutex>
#include <map>

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace {
struct AfterAttachMainTreeTask {
    int32_t containerId = -1;
    std::function<void()> taskFunc;
};

class ACE_EXPORT AsyncBuildManager {
public:
    static AsyncBuildManager& GetInstance();
    static bool IsOnMainThread();
    static bool CheckOnMainThread();
    static bool CheckOperateValid(NG::UINode* node);
    static bool AllowNotifyToNode(const RefPtr<NG::UINode>& node);
    static void SetBuildingMultiThreadNode(bool isBuildingMultiThreadNode);
    static bool IsBuildingMultiThreadNode();
    static bool IsMultiThreadAPIOnSubThread();
    void TryExecuteUnSafeTask(const RefPtr<NG::UINode>& node, const std::function<void()>& task);
    bool TryPostUnSafeTask(const RefPtr<NG::UINode>& node, const std::function<void()>& task);
    void ExecuteAfterAttachMainTreeTasks(int32_t nodeId);
    void RemoveAfterAttachMainTreeTasks(int32_t nodeId);
    bool PostAsyncUITask(int32_t contextId, const std::function<void()>& asyncUITask,
        const std::function<void()>& onFinishTask);
    bool PostUITask(int32_t contextId, const std::function<void()>& uiTask);
private:
    AsyncBuildManager();
    void InitAysncUITaskQueue();
    static bool NeedPostUnSafeTask(const RefPtr<NG::UINode>& node);
    void PostAfterAttachMainTreeTask(const RefPtr<NG::UINode>& node, const std::function<void()>& task);
    std::mutex taskMutex_;
    std::map<int32_t, std::vector<AfterAttachMainTreeTask>> afterAttachMainTreeTasks_;
    static thread_local bool isBuildingMultiThreadNode_;
    static thread_local bool isMainThread_;
    ACE_DISALLOW_COPY_AND_MOVE(AsyncBuildManager);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ASYNC_BUILD_MANAGER_H
