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

namespace OHOS::Ace::NG {
void LazyContainer::UpdateOffset(float delta)
{
    if (adapter_) {
        adapter_->UpdateSlidingOffset(delta);
    }
}

void LazyContainer::UpdateLayoutRange(Axis axis, int32_t markIdx)
{
    if (adapter_) {
        adapter_->UpdateSize(GetHost()->GetGeometryNode()->GetFrameSize());
        adapter_->UpdateAxis(axis);
    }
}

void LazyContainer::JumpToItem(int32_t index)
{
    if (adapter_) {
        adapter_->UpdateMarkItem(index, true);
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
} // namespace OHOS::Ace::NG
