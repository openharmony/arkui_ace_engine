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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_SYNTAX_ARKOALA_LAZY_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_SYNTAX_ARKOALA_LAZY_NODE_H
#include <cstdint>
#include <functional>

#include "base/utils/unique_valued_map.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/syntax/for_each_base_node.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

using RangeType = std::pair<int32_t, int32_t>;

/**
 * @brief Backend node representation to access and manage lazy items in Arkoala frontend
 *
 */
class ArkoalaLazyNode : public ForEachBaseNode {
    DECLARE_ACE_TYPE(ArkoalaLazyNode, ForEachBaseNode);

public:
    explicit ArkoalaLazyNode(int32_t id, bool isRepeat = false);
    ~ArkoalaLazyNode() override = default;

    using CreateItemCb = std::function<RefPtr<UINode>(int32_t)>;
    using UpdateRangeCb = std::function<void(int32_t, int32_t)>;

    void SetTotalCount(int32_t value)
    {
        totalCount_ = value;
    }

    void SetCallbacks(CreateItemCb create, UpdateRangeCb update)
    {
        createItem_ = std::move(create);
        updateRange_ = std::move(update);
    }

    void MoveData(int32_t from, int32_t to) final;

    RefPtr<FrameNode> GetFrameNode(int32_t index) final;

    RefPtr<UINode> GetChildByIndex(int32_t index);

    RefPtr<UINode> GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache, bool addToRenderTree) override;

    void DoRemoveChildInRenderTree(uint32_t index, bool isAll) final
    {
        LOGI("Koala lazyForEach: doRemove called %u. Not implemented", index);
    }
    void DoSetActiveChildRange(int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache) final;

    bool IsAtomicNode() const final
    {
        return false;
    }

    int32_t FrameCount() const final
    {
        return totalCount_;
    }

    void RecycleItems(int32_t from, int32_t to) final
    {
        /* not implemented yet */
    }

    void OnDataChange(int32_t changeIndex, int32_t count, NotificationType type);

    void SetJSViewActive(bool active = true, bool isLazyForEachNode = false, bool isReuse = false) override;

    // used for drag move operation.
    void SetOnMove(std::function<void(int32_t, int32_t)>&& onMove);
    void SetOnMoveFromTo(std::function<void(int32_t, int32_t)>&& onMoveFromTo);
    void SetItemDragEvent(std::function<void(int32_t)>&& onLongPress, std::function<void(int32_t)>&& onDragStart,
        std::function<void(int32_t, int32_t)>&& onMoveThrough, std::function<void(int32_t)>&& onDrop);
    void FireOnMove(int32_t from, int32_t to) override;
    void InitDragManager(const RefPtr<FrameNode>& childNode);
    void InitAllChildrenDragManager(bool init);
    int32_t GetFrameNodeIndex(const RefPtr<FrameNode>& node, bool isExpanded = true) override;

    void DumpInfo() override;

private:
    bool IsNodeInRange(int32_t index, const RangeType range)
    {
        return index >= range.first && index <= range.second;
    }
    void UpdateIsCache(const RefPtr<UINode>& node, bool isCache, bool shouldTrigger = true);

    void UpdateMoveFromTo(int32_t from, int32_t to);
    void UpdateItemsForOnMove();
    void ResetMoveFromTo()
    {
        moveFromTo_.reset();
    }

    // convert index by moveFromTo_.
    int32_t ConvertFromToIndex(int32_t index) const;
    // revert converted-index to origin index.
    int32_t ConvertFromToIndexRevert(int32_t index) const;

    bool isRepeat_ = false;
    // ArkoalaLazyNode is not instance of FrameNode, needs to propagate active state to all items inside
    bool isActive_ = false;

    UniqueValuedMap<int32_t, WeakPtr<UINode>, WeakPtr<UINode>::Hash> node4Index_;
    CreateItemCb createItem_;
    UpdateRangeCb updateRange_;
    int32_t totalCount_ = 0;

    // for tracking reused/recycled nodes
    std::unordered_set<int32_t> recycleNodeIds_;

    std::function<void(int32_t, int32_t)> onMoveFromTo_;
    // record (from, to), only valid during dragging item.
    std::optional<std::pair<int32_t, int32_t>> moveFromTo_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_SYNTAX_ARKOALA_LAZY_NODE_H
