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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_TASK_EXECUTOR_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_TASK_EXECUTOR_H

#include "base/thread/task_executor.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

// Delegate class for form task posting, created by FormPattern and passed to FormManagerDelegate.
// Main responsibility: Post UI/BACKGROUND tasks with consistent priority and ContainerScope handling.
class FormTaskExecutor : public virtual Referenced {
public:
    explicit FormTaskExecutor(const WeakPtr<FrameNode>& host);
    ~FormTaskExecutor() = default;

    // Post task to UI thread with form task priority
    void PostUITask(const TaskExecutor::Task& task, const std::string& name);

    // Post task to BACKGROUND thread with form task priority
    void PostBgTask(const TaskExecutor::Task& task, const std::string& name);

    // Post delayed task to UI thread with form task priority
    void PostDelayedUITask(const TaskExecutor::Task& task, int32_t delayTime, const std::string& name);

    // Post delayed task to specified thread type with form task priority
    void PostDelayedTask(const TaskExecutor::Task& task, TaskExecutor::TaskType type,
        int32_t delayTime, const std::string& name);

    // Post sync task on UI thread (for GetRectRelativeToWindow etc.)
    bool PostSyncUITask(const TaskExecutor::Task& task, const std::string& name);

    // Remove task from UI thread
    void RemoveUITask(const std::string& name);

    // Check if currently running on UI thread
    bool IsRunOnUIThread() const;

private:
    static PriorityType GetFormTaskPriority();
    RefPtr<TaskExecutor> GetTaskExecutor() const;

    WeakPtr<FrameNode> host_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_TASK_EXECUTOR_H
