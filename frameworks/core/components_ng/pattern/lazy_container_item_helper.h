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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_CONTAINER_ITEM_HELPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_CONTAINER_ITEM_HELPER_H

#include <cstdint>

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {

class FocusHub;
enum class FocusStep : int32_t;

/**
 * @brief Per-child index carrier for components placed inside a lazy container (List / ListItemGroup).
 *
 * Previously ListItemPattern carried indexInList_ / indexInListItemGroup_ as bare scalar members, and
 * generic children (Text/Row/Button/...) had no index at all, so they could not participate in
 * scrollToIndex / onScrollIndex / focus navigation.
 *
 * This helper centralizes that index state so ANY child component can carry it. Each Pattern holds its
 * own RefPtr<LazyContainerItemHelper> (lazily created by Pattern::GetOrCreateLazyContainerItemHelper when
 * a container indexes the child). Because the helper lives on the child, it is destroyed together with
 * the child — no stale entries accumulate when children are recycled by LazyForEach.
 *
 * ListItemPattern / ListItemGroupPattern forward their GetIndexInList / SetIndexInList /
 * GetIndexInListItemGroup / SetIndexInListItemGroup methods to this helper, keeping their external API
 * unchanged while moving the storage here.
 *
 * Defaults match the previous ListItemPattern members: indexInList_ = 0, indexInListItemGroup_ = -1.
 * The -1 sentinel for indexInListItemGroup_ is load-bearing — ListItemPattern::ClickJudge and
 * HandleFocusEvent rely on it to detect "not inside a group".
 */
class LazyContainerItemHelper : public virtual AceType {
    DECLARE_ACE_TYPE(LazyContainerItemHelper, AceType);

public:
    LazyContainerItemHelper() = default;
    ~LazyContainerItemHelper() override = default;

    int32_t GetIndexInList() const
    {
        return indexInList_;
    }

    void SetIndexInList(int32_t index)
    {
        indexInList_ = index;
    }

    int32_t GetIndexInListItemGroup() const
    {
        return indexInListItemGroup_;
    }

    void SetIndexInListItemGroup(int32_t index)
    {
        indexInListItemGroup_ = index;
    }

    /**
     * @brief Find the head (first) or tail (last) focusable descendant for HOME/END focus jumps.
     *
     * Migrated from ListItemPattern::FindHeadOrTailChild — the logic is purely FocusHub traversal and does
     * not depend on any ListItem-specific state, so it is shared by every child that carries this helper
     * (ListItem + generic children alike). Defined in the .cpp to keep FocusHub out of this header.
     *
     * @param childFocus the focus hub of the child to search within.
     * @param step the focus step (LEFT_END/UP_END => head; RIGHT_END/DOWN_END => tail).
     * @param target [out] receives the found head/tail focus node.
     * @return true if a head/tail node was found.
     */
    static bool FindHeadOrTailChild(
        const RefPtr<FocusHub>& childFocus, FocusStep step, WeakPtr<FocusHub>& target);

private:
    int32_t indexInList_ = 0;
    int32_t indexInListItemGroup_ = -1;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_CONTAINER_ITEM_HELPER_H
