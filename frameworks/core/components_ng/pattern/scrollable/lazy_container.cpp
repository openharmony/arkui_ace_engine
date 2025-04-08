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

void LazyContainer::UpdateLayoutRange(Axis axis, bool firstLayout)
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
    adapter_->UpdateViewport(size, axis);
    if (firstLayout) {
        adapter_->PrepareReset(0);
    }
}

ScrollWindowAdapter* LazyContainer::GetOrCreateScrollWindowAdapter()
{
    // initialize ArkUI2.0 scrollWindowAdapter.
    if (!adapter_) {
        auto algo = CreateFillAlgorithm();
        CHECK_NULL_RETURN(algo, nullptr);
        adapter_ = MakeRefPtr<ScrollWindowAdapter>(GetHost().GetRawPtr(), CreateFillAlgorithm());
    }
    return adapter_.GetRawPtr();
}

ScrollWindowAdapter* LazyContainer::GetScrollWindowAdapter()
{
    if (adapter_) {
        return adapter_.GetRawPtr();
    }
    return nullptr;
}

RefPtr<FrameNode> LazyContainer::GetOrCreateChildByIndex(uint32_t index)
{
    if (adapter_) {
        return adapter_->GetChildByIndex(index);
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
} // namespace OHOS::Ace::NG
