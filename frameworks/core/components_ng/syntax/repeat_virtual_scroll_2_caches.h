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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_2_CACHES_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_2_CACHES_H

#include <cstdint>
#include <functional>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

/**
 * scenario 1: GetFrameChild(index) need to render new UINode
 * 1. GetFrameChild(index)
 * 2. GetL1UINode4Index(index) return nothing
 * 3. CallOnGetRid4Index(index)
 * 4. calls onGetRid4Index_(index) to TS side
 *   a) get key for index, get ttype for index
 *   b) RepeatItem exists for this index/data item and this ttype? - no
 *   c) itemGenFunction(item, index) -> RepeatItem with new rid
 *   d) bracket execution of itemGenFunction with calls to these C++ functions
 *       BeforeChildNodeCreation() - creases 2nd VSP
 *       AddNodeFromVSP(rid) - gets the newly create FrameNode from the VSP
 *          adds it to rid -> CacheItem { valid: true }
 *   e) TS function completed, returns new rid
 * 5. CallOnGetRid4Index continues
 * 6. GetCacheItem4RID(rid) returns cached item with UINode added in step 4d
 * 7. CallOnGetRid4Index returns UINode
 * 8. GetFrameChild returns UINode
 *
 *
 * scenario 2: GetFrameChild(index) need to update existing UINode
 * 1. GetFrameChild(index)
 * 2. GetL1UINode4Index(index) return nothing
 * 3. CallOnGetRid4Index(index)
 * 4. onGetRid4Index_(index) to TS side
 *   a) get key for index, get ttype for index
 *   b) RepeatItem exists for this ttype? - yes, it has rid
 *   c) RepeatItem.updateItem(item), RepeatItem.updateIndex(index)
 *   d) apply updates synchronously
 *   e) TS function completed, returns existing rid
 * 5. CallOnGetRid4Index continues
 * 6. GetCacheItem4RID(rid) returns cached item with updated UINode
 * 7. CallOnGetRid4Index returns UINode
 * 8. GetFrameChild returns UINode
 *
 *
 * scenario 3: GetFrameChild(index) can return value L1 node
 * 1. GetFrameChild(index)
 * 2. GetL1UINode4Index(index) return UINode
 * 3. GetFrameChild completes, returns the UINode
 *
 *
 * scenario 4: Repeat Rerender
 * 1. array items in visible range have changed ? - yes
 * 2. visible range.forEach((index =>
 * 3. has ttype changes ? and  has data item changed?
 * 4.   if yes to either,
 *        get RID for old data item
 *        SetInvalid(rid) on C++ side
 *            request re-layout from container
 * 5. if no, do nothing
 *
 * TS Side has
 *  cache: data item -> RID
 *
 * scenario 5: layout calls RecycleItems(from, to)
 * 1.  [for..to].forEach((index) =>
 * 2.    if index in L1, get rid
 * 3.      setInvalid(rid)
 *
 */

class RepeatVirtualScroll2CacheItem : public virtual AceType {
    DECLARE_ACE_TYPE(RepeatVirtualScroll2CacheItem, AceType);

public:
    static RefPtr<RepeatVirtualScroll2CacheItem> MakeCacheItem(RefPtr<UINode>& node, bool isL1);

    RepeatVirtualScroll2CacheItem(RefPtr<UINode>& node, bool isL1)
        : isL1_(isL1), isActive_(false), isOnRenderTree_(false), node_(node)
    {}
    ~RepeatVirtualScroll2CacheItem() override = default;

    bool isL1_;
    bool isActive_;
    bool isOnRenderTree_;
    RefPtr<UINode> node_;

    ACE_DISALLOW_COPY_AND_MOVE(RepeatVirtualScroll2CacheItem);
};

using IndexType = int32_t;
using RIDType = uint32_t;
using ActiveRangeType = std::pair<IndexType, IndexType>;


// result codes of onGetRid4Index result (2nd 2nd in the pair)
// Note: using #define instead of enum class due to bridging limitations
// between TS and UINode classes: not allowed to import the class definition
// from js_repeat_virtual_scroll.cpp
enum OnGetRid4IndexResult {
    FAILED = 0,
    NO_NODE = 0,
    CREATED_NEW_NODE = 1,
    UPDATED_NODE = 2,
    UNCHANGED_NODE = 3
};

class RepeatVirtualScroll2Caches {
public:
    using CacheItem = RefPtr<RepeatVirtualScroll2CacheItem>;
    using OptCacheItem = std::optional<CacheItem>;
    using GetFrameChildResult = std::pair<uint32_t, CacheItem>;

public:
    RepeatVirtualScroll2Caches(const std::function<std::pair<RIDType, uint32_t>(IndexType)>& onGetRid4Index);

    /**
     * Return a FrameNode child for give index
     */
    GetFrameChildResult GetFrameChild(IndexType index, bool needBuild);

    /**
     * Function called from TS:
     * purge UINode with given id
     * i.e. remove map entry rid -> CacheItem
     */
    void RemoveNode(RIDType rid);

    /**
     * Function called from TS:
     * drop RID from L1
     * mark CacheItem for rid as invalid
     */
    void SetInvalid(RIDType rid);

    /**
     * rebuild the L1
     * call cbFunc for each item
     * keep in L1 if function returns true
     * otherwise remove silently
     *
     * return true if any items have been dropped
     * return false only if no changes made
     */
    bool RebuildL1(const std::function<bool(IndexType index, CacheItem& cacheItem)>& cbFunc);

    /**
     * iterate over L1 items and call cbFunc for each
     * cbFunction is NOT allowed to add to or remove items from L1
     */
    void ForEachL1Node(const std::function<void(IndexType index, RIDType rid, const RefPtr<UINode>& node)>& cbFunc);

    /**
     * iterate over L1 items and call cbFunc for each
     * cbFunction is NOT allowed to add to or remove items from L1
     * if moveFromTo_ exists, the original index order needs to be mapped
     */
    void ForEachL1NodeWithOnMove(const std::function<void(const RefPtr<UINode>& node)>& cbFunc);

    /**
     * iterate over all rid -> CacheItems 's
     * cbFunction is NOT allowed to add to or remove CacheItems from cacheItem4Rid_
     */
    void ForEachCacheItem(const std::function<void(RIDType rid, const CacheItem& cacheItem)>& cbFunc);

    std::optional<IndexType> GetL1Index4Node(const RefPtr<FrameNode>& frameNode) const;

    /**
     * Drop rid / index from L1, mark its CacheItem as no in L1
     * do not modify IsActive state, do not remove from renderTree
     * either caller does it, or SetActiveRange will do a little later.
     */
    void DropFromL1ByRid(RIDType rid);
    void DropFromL1ByIndex(IndexType index);

    /**
     * returns index if given rid is in L1Rid4Index
     */
    std::optional<IndexType> GetL1Index4Rid(RIDType rid);

    //  TS call JS to update l1Rid4Index_ following a
    // Repeat.rerender
    void UpdateL1Rid4Index(std::map<int32_t, uint32_t> l1Rd4Index);

    /**
     * for debug purposes, use wisely, performance is slow!
     */
    std::string DumpCacheItem(const CacheItem& cacheItem) const;
    std::string DumpUINode(const RefPtr<UINode>& node) const;
    std::string DumpUINodeCache() const;
    std::string DumpL1Rid4Index() const;

    /**
     * return the index of given RID in L1
     * or NO_L1_INDEX(-1)
     */
    std::optional<IndexType> GetL1Index4RID(RIDType rid) const;

    void UpdateMoveFromTo(IndexType from, IndexType to);
    void ResetMoveFromTo()
    {
        moveFromTo_.reset();
    }

    // convert index by moveFromTo_.
    IndexType ConvertFromToIndex(IndexType index) const
    {
        if (!moveFromTo_) {
            return index;
        }
        if (moveFromTo_.value().second == index) {
            return moveFromTo_.value().first;
        }
        if (moveFromTo_.value().first <= index && index < moveFromTo_.value().second) {
            return index + 1;
        }
        if (moveFromTo_.value().second < index && index <= moveFromTo_.value().first) {
            return index - 1;
        }
        return index;
    }

    // revert converted-index to origin index.
    IndexType ConvertFromToIndexRevert(IndexType index) const
    {
        if (!moveFromTo_) {
            return index;
        }
        if (moveFromTo_.value().first == index) {
            return moveFromTo_.value().second;
        }
        if (moveFromTo_.value().first < index && index <= moveFromTo_.value().second) {
            return index - 1;
        }
        if (moveFromTo_.value().second <= index && index < moveFromTo_.value().first) {
            return index + 1;
        }
        return index;
    }

    bool IsMoveFromToExist() const
    {
        return moveFromTo_.has_value();
    }

private:
    /**
     * TS make new node or update from L1
     * add to L1 but do not SetActive or add to render tree
     * CacheItem has node, isL1=True
     */
    OptCacheItem CallOnGetRid4Index(IndexType index);

    /**
     * return CacheItem for RID, if it exists
     * do not check any CacheItem flags
     */
    OptCacheItem GetCacheItem4RID(RIDType rid) const;

    /**
     * if L1 includes RID for index, return it
     */
    std::optional<RIDType> GetRID4Index(IndexType index) const;

    /**
     * get valid UINode from L1 for given index
     */
    OptCacheItem GetL1CacheItem4Index(IndexType index);
    // std::optional<RefPtr<UINode>>& GetL1UINode4Index(IndexType index);

    // L1 items index -> RID
    std::map<IndexType, RIDType> l1Rid4Index_;

    // all nodes RID -> CacheItem[UINode, isValid]
    std::map<RIDType, CacheItem> cacheItem4Rid_;

    // TS callback function for given index, provides RID
    std::function<std::pair<RIDType, uint32_t>(IndexType)> onGetRid4Index_;

    // TS function to inform new active range from ... to
    std::function<void(IndexType, IndexType)> onSetActiveRange_;

    // TS function to call to purge
    std::function<void()> onPurge_;

    // record (from, to), only valid during dragging item.
    std::optional<std::pair<IndexType, IndexType>> moveFromTo_;
}; // class NodeCache

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_VIRTUAL_SCROLL_2_CACHES_H
