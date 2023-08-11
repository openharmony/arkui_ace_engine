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
#include <list>
#include <map>
#include <set>

#include "base/log/frame_info.h"
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
    using PredictTask = std::function<void(int64_t, bool)>;
    UITaskScheduler() = default;
    ~UITaskScheduler();

    // Called on Main Thread.
    void AddDirtyLayoutNode(const RefPtr<FrameNode>& dirty);
    void AddDirtyRenderNode(const RefPtr<FrameNode>& dirty);
    void AddPredictTask(PredictTask&& task);
    void AddAfterLayoutTask(std::function<void()>&& task);
    void AddAfterRenderTask(std::function<void()>&& task);

    void FlushLayoutTask(bool forceUseMainThread = false);
    void FlushRenderTask(bool forceUseMainThread = false);
    void FlushTask();
    void FlushPredictTask(int64_t deadline, bool canUseLongPredictTask = false);
    void FlushAfterLayoutTask();
    void FlushAfterRenderTask();

    void UpdateCurrentPageId(uint32_t id)
    {
        currentPageId_ = id;
    }

    void CleanUp();

    bool isEmpty();

    void StartRecordFrameInfo(FrameInfo* info)
    {
        frameInfo_ = info;
    }

    void FinishRecordFrameInfo()
    {
        frameInfo_ = nullptr;
    }

    static uint64_t GetFrameId()
    {
        return frameId_;
    }

    bool IsLayouting() const
    {
        return isLayouting_;
    }

private:
    bool NeedAdditionalLayout();

    template<typename T>
    struct NodeCompare {
        bool operator()(const T& nodeLeft, const T& nodeRight) const
        {
            if (!nodeLeft || !nodeRight) {
                return false;
            }
            if (nodeLeft->GetDepth() < nodeRight->GetDepth()) {
                return true;
            }
            if (nodeLeft->GetDepth() == nodeRight->GetDepth()) {
                return nodeLeft < nodeRight;
            }
            return false;
        }
    };

    using PageDirtySet = std::set<RefPtr<FrameNode>, NodeCompare<RefPtr<FrameNode>>>;
    using RootDirtyMap = std::map<uint32_t, PageDirtySet>;

    RootDirtyMap dirtyLayoutNodes_;
    RootDirtyMap dirtyRenderNodes_;
    std::list<PredictTask> predictTask_;
    std::list<std::function<void()>> afterLayoutTasks_;
    std::list<std::function<void()>> afterRenderTasks_;

    uint32_t currentPageId_ = 0;
    bool isLayouting_ = false;

    FrameInfo* frameInfo_ = nullptr;

    static uint64_t frameId_;

    ACE_DISALLOW_COPY_AND_MOVE(UITaskScheduler);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_UI_TASK_SCHEDULER_H
