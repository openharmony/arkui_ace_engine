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

#include "lazy_container.h"

#include "core/components_ng/layout/section/staggered_fill_algorithm.h"

namespace OHOS::Ace::NG {
bool LazyContainer::UpdateOffset(float delta)
{
    if (adapter_) {
        return adapter_->UpdateSlidingOffset(delta);
    }
    return false;
}

void LazyContainer::OnLayoutFinished(Axis axis, bool firstLayout)
{
    if (!adapter_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geo = host->GetGeometryNode();
    CHECK_NULL_VOID(geo);
    auto size = geo->GetFrameSize();
    if (geo->GetContentSize().IsPositive()) {
        size = geo->GetContentSize();
    }
    adapter_->OnLayoutFinished(size, axis);
    if (firstLayout) {
        adapter_->PrepareReset(0);
    }
}

ScrollWindowAdapter* LazyContainer::GetOrCreateScrollWindowAdapter()
{
    return nullptr;
}

ScrollWindowAdapter* LazyContainer::GetScrollWindowAdapter()
{
    return nullptr;
}

RefPtr<FrameNode> LazyContainer::GetOrCreateChildByIndex(uint32_t index)
{
    if (newAdapter_) {
        newAdapter_->GetOrCreateChild(index);
    }
    return nullptr;
}

RefPtr<FillAlgorithm> LinearLazyContainer::CreateFillAlgorithm()
{
    return MakeRefPtr<StaggeredFillAlgorithm>(GetLayoutProperty<LayoutProperty>());
}

void LazyContainer::RequestJump(int32_t idx, ScrollAlign align, float extraOffset)
{
    if (adapter_) {
        adapter_->PrepareJump(idx, align, extraOffset);
    }
}

void LazyContainer::RequestReset(int32_t idx, float extraOffset)
{
    if (adapter_ && idx >= 0) {
        adapter_->PrepareReset(idx, extraOffset);
    }
}

bool LazyContainer::RequestFillToTarget(int32_t idx, ScrollAlign align, float extraOffset)
{
    if (adapter_) {
        return adapter_->PrepareLoadToTarget(idx, align, extraOffset);
    }
    return true;
}
void LazyContainer::Synchronize(
    LazyComposeAdapter::CreateItemCb creator, LazyComposeAdapter::UpdateRangeCb updater, int32_t totalCount)
{
    if (!newAdapter_) {
        newAdapter_ = std::make_unique<LazyComposeAdapter>();
    }
    newAdapter_->SetCallbacks(std::move(creator), std::move(updater));
    newAdapter_->SetTotalCount(totalCount);
}
int32_t LazyContainer::GetTotalChildCount() const
{
    return newAdapter_ ? newAdapter_->GetTotalCount() : -1;
}
LazyComposeAdapter* LazyContainer::GetArkoalaLazyAdapter()
{
    return newAdapter_.get();
}

void LazyContainer::RemoveItemsOnChange(int32_t changeIndex)
{
    CHECK_NULL_VOID(newAdapter_);
    std::vector<RefPtr<UINode>> toRemove;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    for (const auto& child : host->GetChildren()) {
        const int32_t index = static_cast<int32_t>(newAdapter_->GetIndexOfChild(DynamicCast<FrameNode>(child)));
        if (index >= changeIndex) {
            toRemove.push_back(child);
        }
    }
    for (auto&& node : toRemove) {
        host->RemoveChild(node);
    }
    newAdapter_->OnDataChange(changeIndex);
}
} // namespace OHOS::Ace::NG
