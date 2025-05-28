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
#include "lazy_compose_adapter.h"

#include "core/components_ng/base/frame_node.h"
namespace OHOS::Ace::NG {

RefPtr<FrameNode> LazyComposeAdapter::GetOrCreateChild(uint32_t index)
{
    auto item = GetChild(index);
    if (item) {
        return item;
    }
    auto newItem = createItem_ ? createItem_(index) : nullptr;
    items_.Put(index, newItem);
    return newItem;
}

RefPtr<FrameNode> LazyComposeAdapter::GetChild(uint32_t index)
{
    auto item = items_.Get(index);
    return item ? item->Upgrade() : nullptr;
}

void LazyComposeAdapter::SetActiveRange(int32_t start, int32_t end)
{
    if (updateRange_) {
        updateRange_(start, end);
    }

    items_.RemoveIf([start, end](const uint32_t& k, const auto& _) {
        const auto idx = static_cast<int32_t>(k);
        return idx < start || idx > end;
    });
}
void LazyComposeAdapter::SetCallbacks(CreateItemCb create, UpdateRangeCb update)
{
    createItem_ = std::move(create);
    updateRange_ = std::move(update);
}
int32_t LazyComposeAdapter::GetTotalCount() const
{
    return totalCount_;
}
void LazyComposeAdapter::SetTotalCount(int32_t value)
{
    totalCount_ = value;
}
uint32_t LazyComposeAdapter::GetIndexOfChild(const RefPtr<FrameNode>& child)
{
    return items_.GetKey(child).value_or(0);
}
} // namespace OHOS::Ace::NG