/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scrollable/scrollable_item_pool.h"

#include "core/components_ng/pattern/scrollable/scrollable_item.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
constexpr size_t MAX_SIZE = 10;

ScrollableItemPool& ScrollableItemPool::GetInstance()
{
    static thread_local ScrollableItemPool pool(MAX_SIZE);
    return pool;
}

RefPtr<ScrollableItem> ScrollableItemPool::Allocate(
    const std::string& tag, int32_t nodeId, const PatternCreator& patternCreator)
{
    ACE_SCOPED_TRACE("ScrollableItemPool::Allocate");
    auto it = pool_.find(tag);
    if (it == pool_.end() || it->second.empty()) {
        auto node = ScrollableItem::GetOrCreateScrollableItem(tag, nodeId, patternCreator);
        node->SetCustomDeleter(ObjectPoolDeleter<ScrollableItem> { this });
        node->SetMaybeRelease(false);
        return node;
    }
    auto node = it->second.back();
    it->second.pop_back();
    ElementRegister::GetInstance()->UpdateRecycleElmtId(node->GetId(), nodeId);
    node->UpdateRecycleElmtId(nodeId);
    return Referenced::Claim(node);
}

void ScrollableItemPool::Deallocate(ScrollableItem* obj)
{
    ACE_SCOPED_TRACE("ScrollableItemPool::Deallocate");
    CHECK_NULL_VOID(obj);
    auto tag = obj->GetTag();
    auto it = pool_.find(tag);
    if (it == pool_.end()) {
        pool_[tag] = { obj };
        obj->Clean(true);
        return;
    }
    if (it->second.size() < static_cast<uint32_t>(size_)) {
        it->second.emplace_back(obj);
        obj->Clean(true);
        return;
    }
    delete obj;
}
} // namespace OHOS::Ace::NG
