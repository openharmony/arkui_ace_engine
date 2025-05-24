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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_LAZY_COMPOSE_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_LAZY_COMPOSE_ADAPTER_H
#include <cstdint>
#include <functional>

#include "base/memory/referenced.h"
#include "base/utils/unique_valued_map.h"

namespace OHOS::Ace::NG {
class FrameNode;

/**
 * @brief Adapter to access and manage lazy items in Arkoala frontend
 *
 */
class LazyComposeAdapter {
public:
    using CreateItemCb = std::function<RefPtr<FrameNode>(int32_t)>;
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

    RefPtr<FrameNode> GetChild(int32_t index)
    {
        auto item = items_.Get(index);
        if (item && !item->Invalid()) {
            return item->Upgrade();
        }
        auto newItem = createItem_ ? createItem_(index) : nullptr;
        items_.Put(index, newItem);
        // todo: attach to tree, either here / in FrameNode
        return newItem;
    }

    void SetActiveRange(int32_t start, int32_t end) {
        if (updateRange_) {
            updateRange_(start, end);
        }
    }

private:
    UniqueValuedMap<int32_t, WeakPtr<FrameNode>, WeakPtr<FrameNode>::Hash> items_;
    CreateItemCb createItem_;
    UpdateRangeCb updateRange_;
    int32_t totalCount_ = 0;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_LAZY_COMPOSE_ADAPTER_H
