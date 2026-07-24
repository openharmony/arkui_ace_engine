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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_MULTI_THREAD_BUILD_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_MULTI_THREAD_BUILD_MANAGER_H

#include <functional>
#include <map>
#include <mutex>

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"

namespace OHOS::Ace {
namespace NG {
class UINode;
}
class ACE_EXPORT MultiThreadBuildManager {
public:
    static MultiThreadBuildManager& GetInstance();
    static void InitOnUIThread();
    static bool IsOnUIThread();
    static bool CheckOnUIThread();
    static bool CheckNodeOnValidThread(NG::UINode* node);
    static void SetIsThreadSafeNodeScope(bool isThreadSafeNodeScope);
    static bool IsThreadSafeNodeScope();
    static bool IsParallelScope();
    static void SetNeedMarkNodeTreeFree(bool isNeedMarkNodeTreeFree);
    static bool IsNeedMarkNodeTreeFree();
    bool PostAsyncUITask(int32_t contextId, std::function<void()>&& asyncUITask,
        std::function<void()>&& onFinishTask);
    bool PostUITask(int32_t contextId, std::function<void()>&& uiTask);
    bool PostUITaskAndWait(int32_t contextId, std::function<void()>&& uiTask);

    static void SetIsParallelizeUI(bool isParallelizeUI)
    {
        isParallelizeUI_ = isParallelizeUI;
    }

    static void CheckTag(const std::string& tag);

private:
    MultiThreadBuildManager();
    void InitAsyncUITaskQueue();
    static thread_local bool isThreadSafeNodeScope_;
    static thread_local bool isNeedMarkNodeTreeFree_;
    static thread_local bool isUIThread_;
    static thread_local bool isParallelizeUI_;
    ACE_DISALLOW_COPY_AND_MOVE(MultiThreadBuildManager);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_MULTI_THREAD_BUILD_MANAGER_H
