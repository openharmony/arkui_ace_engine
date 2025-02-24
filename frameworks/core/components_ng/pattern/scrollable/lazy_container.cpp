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

void LazyContainer::UpdateLayoutRange(Axis axis, std::optional<int32_t> markIdx, bool firstLayout, bool resetOnJump)
{
    if (adapter_) {
        adapter_->UpdateViewport(GetHost()->GetGeometryNode()->GetFrameSize(), axis);
        if (markIdx && *markIdx >= 0) {
            adapter_->UpdateMarkItem(*markIdx, resetOnJump);
        } else if (firstLayout) {
            adapter_->UpdateMarkItem(0, resetOnJump);
        }
    }
}

ScrollWindowAdapter* LazyContainer::GetOrCreateScrollWindowAdapter()
{
    // initialize ArkUI2.0 scrollWindowAdapter.
    if (!adapter_) {
        auto algo = CreateFillAlgorithm();
        CHECK_NULL_RETURN(algo, nullptr);
        adapter_ = MakeRefPtr<ScrollWindowAdapter>(GetUnsafeHostPtr(), CreateFillAlgorithm());
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
} // namespace OHOS::Ace::NG
