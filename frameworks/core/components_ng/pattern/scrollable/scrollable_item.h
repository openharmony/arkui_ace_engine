/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_ITEM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_ITEM_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/scrollable/scrollable_item_pool.h"

namespace OHOS::Ace::NG {
using MyDeleter = ObjectPoolDeleter<ScrollableItem>;
class ScrollableItem : public FrameNode {
    DECLARE_ACE_TYPE(ScrollableItem, FrameNode);
public:
    static RefPtr<ScrollableItem> GetOrCreateScrollableItem(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

    ScrollableItem(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
        : FrameNode(tag, nodeId, pattern, isRoot)
    {}

    bool MaybeRelease() override;

    void SetMaybeRelease(bool state)
    {
        maybeRelease_ = state;
    }

    void SetCustomDeleter(MyDeleter&& deleter)
    {
        deleter_ = std::forward<MyDeleter>(deleter);
    }
private:
    bool maybeRelease_ = true;
    MyDeleter deleter_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_ITEM_POOL_H
