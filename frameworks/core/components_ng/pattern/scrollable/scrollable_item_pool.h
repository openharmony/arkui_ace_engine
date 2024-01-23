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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_ITEM_POOL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_ITEM_POOL_H

#include <functional>
#include <unordered_map>
#include <vector>

#include "base/memory/referenced.h"

namespace OHOS::Ace::NG {
class ScrollableItem;
class Pattern;
using PatternCreator = std::function<RefPtr<Pattern>(void)>;
class ScrollableItemPool {
public:
    static ScrollableItemPool& GetInstance();
    RefPtr<ScrollableItem> Allocate(const std::string& tag, int32_t nodeId, const PatternCreator& patternCreator);

    void Deallocate(ScrollableItem* obj);

private:
    explicit ScrollableItemPool(size_t size) : size_(size) {}
    std::unordered_map<std::string, std::vector<ScrollableItem*>> pool_;
    size_t size_;
};

template<class T>
struct ObjectPoolDeleter {
    ScrollableItemPool* allocator = nullptr;

    void operator()(T* obj) const
    {
        if (allocator) {
            allocator->Deallocate(obj);
        }
    }
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SCROLLABLE_ITEM_POOL_H
