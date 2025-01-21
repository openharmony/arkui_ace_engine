/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_MEMORY_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_MEMORY_MANAGER_H

#include <cstdint>
#include <functional>
#include <map>
#include <list>

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class MemoryManager : public virtual AceType {
    DECLARE_ACE_TYPE(MemoryManager, AceType);
public:
    using RecycleImageByPageCallback = std::function<RefPtr<FrameNode>()>;
    MemoryManager();
    ~MemoryManager() = default;

    void AddRecyclePageNode(const RefPtr<FrameNode>& node);
    void RemoveRecyclePageNode(int32_t nodeId);
    void Reset();

    void RebuildImageByPage(const RefPtr<FrameNode>& node);
    void PostMemRecycleTask();

private:
    void RebuildImage(const RefPtr<UINode>& node);
    void RecycleImage(const RefPtr<UINode>& node, int& recycleNum);

    void TrimMemRecycle();
    void RecycleImageByPage(const RefPtr<FrameNode>& node);

    std::list<WeakPtr<FrameNode>> pageNodes_;
    bool isTrimMemWork_ = true;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_MEMORY_MANAGER_H
