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

#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT UiTaskScheduler final {
public:
    ~UiTaskScheduler() = default;

    static UiTaskScheduler* GetInstance();

    // Called on Main Thread.
    void AddDirtyLayoutNode(const RefPtr<FrameNode>& dirty);
    void AddDirtyRenderNode(const RefPtr<FrameNode>& dirty);
    void FlushLayoutTask(bool onCreate = false, bool forceUseMainThread = false);
    void FlushRenderTask(bool forceUseMainThread = false);
    void FlushTask();

    void UpdateCurrentRootId(uint32_t id)
    {
        currentRootId_ = id;
    }

    void UpdateCurrentPageId(uint32_t id)
    {
        currentPageId_ = id;
    }

private:
    UiTaskScheduler() = default;

    template<typename T>
    struct NodeCompare {
        bool operator()(const T& nodeLeft, const T& nodeRight)
        {
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
    using RootDirtyMap = std::unordered_map<uint32_t, PageDirtySet>;

    std::unordered_map<uint32_t, RootDirtyMap> dirtyLayoutNodes_;

    std::unordered_map<uint32_t, RootDirtyMap> dirtyRenderNodes_;

    // Singleton instance
    static std::unique_ptr<UiTaskScheduler> instance_;

    static std::mutex mutex_;

    uint32_t currentRootId_ = 0;
    uint32_t currentPageId_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(UiTaskScheduler);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_UI_TASK_SCHEDULER_H
