/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_UI_TASK_SCHEDULER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_UI_TASK_SCHEDULER_H

#include <cstdint>
#include <functional>
#include <mutex>
#include <set>
#include <memory>
#include <unordered_map>

#include "base/memory/referenced.h"
#include "base/utils/macros.h"

namespace OHOS::Ace::NG {

class FrameNode;

using TaskThread = uint32_t;
constexpr TaskThread PLATFORM_TASK = 0;
constexpr TaskThread MAIN_TASK = 1;
constexpr TaskThread BACKGROUND_TASK = 1 << 1;
constexpr TaskThread UNDEFINED_TASK = 1 << 2;

class UITask {
public:
    explicit UITask(std::function<void()>&& task) : task_(std::move(task)) {}

    UITask(std::function<void()>&& task, TaskThread taskThread) : task_(std::move(task)), taskThread_(taskThread) {}

    ~UITask() = default;

    void SetTaskThreadType(TaskThread taskThread)
    {
        taskThread_ = taskThread;
    }

    TaskThread GetTaskThreadType() const
    {
        return taskThread_;
    }

    void operator()() const
    {
        if (task_) {
            task_();
        }
    }

private:
    std::function<void()> task_;
    TaskThread taskThread_ = MAIN_TASK;
};

class ACE_EXPORT UITaskScheduler final {
public:
    UITaskScheduler() = default;
    ~UITaskScheduler() = default;

    // Called on Main Thread.
    void AddDirtyLayoutNode(const RefPtr<FrameNode>& dirty);
    void AddDirtyRenderNode(const RefPtr<FrameNode>& dirty);

    void FlushLayoutTask(bool forceUseMainThread = false);
    void FlushRenderTask(bool forceUseMainThread = false);
    void FlushTask();

    void UpdateCurrentPageId(uint32_t id)
    {
        currentPageId_ = id;
    }

    void CleanUp()
    {
        dirtyLayoutNodes_.clear();
        dirtyRenderNodes_.clear();
    }

private:
    template<typename T>
    struct NodeCompare {
        bool operator()(const T& nodeLeft, const T& nodeRight)
        {
            auto left = nodeLeft.Upgrade();
            auto right = nodeRight.Upgrade();
            if (!left || !right) {
                return false;
            }
            if (left->GetDepth() < right->GetDepth()) {
                return true;
            }
            if (left->GetDepth() == right->GetDepth()) {
                return left < right;
            }
            return false;
        }
    };

    using PageDirtySet = std::set<WeakPtr<FrameNode>, NodeCompare<WeakPtr<FrameNode>>>;
    using RootDirtyMap = std::unordered_map<uint32_t, PageDirtySet>;

    RootDirtyMap dirtyLayoutNodes_;
    RootDirtyMap dirtyRenderNodes_;

    uint32_t currentPageId_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(UITaskScheduler);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_UI_TASK_SCHEDULER_H
