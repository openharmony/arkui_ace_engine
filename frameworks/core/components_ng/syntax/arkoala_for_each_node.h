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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_SYNTAX_ARKOALA_FOR_EACH_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_SYNTAX_ARKOALA_FOR_EACH_NODE_H
#include <cstdint>
#include <functional>

#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/syntax/for_each_base_node.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

class ArkoalaForEachNode : public ForEachBaseNode {
    DECLARE_ACE_TYPE(ArkoalaForEachNode, ForEachBaseNode);

public:
    struct ActiveRangeParam {
        int32_t start;
        int32_t end;
        int32_t cacheStart;
        int32_t cacheEnd;

        bool operator==(const ActiveRangeParam& other) const
        {
            return start == other.start && end == other.end &&
                cacheStart == other.cacheStart && cacheEnd == other.cacheEnd;
        }
    };

    using UpdateRangeCb = std::function<void(int32_t, int32_t, int32_t, int32_t, bool)>;

    explicit ArkoalaForEachNode(int32_t id, bool isRepeat = false);
    ~ArkoalaForEachNode() override = default;

    bool IsAtomicNode() const final
    {
        return false;
    }

    void FinishRender();
    void FlushUpdateAndMarkDirty() override;
    bool AddOrMoveChildBefore(const RefPtr<UINode>& child, const RefPtr<UINode>& siblingNode);

    // used for drag move operation.
    RefPtr<FrameNode> GetFrameNode(int32_t index) final;
    void MoveData(int32_t from, int32_t to, bool isNeedUpdate = false) final;
    void SetOnMove(std::function<void(int32_t, int32_t)>&& onMove);
    void SetItemDragEvent(std::function<void(int32_t)>&& onLongPress, std::function<void(int32_t)>&& onDragStart,
        std::function<void(int32_t, int32_t)>&& onMoveThrough, std::function<void(int32_t)>&& onDrop);
    void SetUpdateRange(UpdateRangeCb&& update)
    {
        updateRange_ = std::move(update);
    }
    void FireOnMove(int32_t from, int32_t to) override;
    void InitDragManager(const RefPtr<FrameNode>& childNode);
    void InitAllChildrenDragManager(bool init);
    void DoSetActiveChildRange(int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache) final;

    void DumpInfo() override;

private:
    ACE_DISALLOW_COPY_AND_MOVE(ArkoalaForEachNode);

    bool isRepeat_ = false;
    ActiveRangeParam activeRangeParam_ = { -1, -1, -1, -1 };
    UpdateRangeCb updateRange_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_SYNTAX_ARKOALA_FOR_EACH_NODE_H
