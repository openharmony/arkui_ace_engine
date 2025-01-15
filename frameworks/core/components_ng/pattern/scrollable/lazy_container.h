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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_LAZY_CONTAINER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCROLL_LAZY_CONTAINER_H
#include "core/components_ng/base/scroll_window_adapter.h"
#include "core/components_ng/pattern/pattern.h"
namespace OHOS::Ace::NG {
/**
 * @brief Base class of all components that support lazy load in ArkUI 2.0
 *
 */
class LazyContainer : virtual public Pattern {
public:
    int32_t GetTotalChildCount() override
    {
        return adapter_ ? adapter_->GetTotalCount() : -1;
    }

    RefPtr<FrameNode> GetOrCreateChildByIndex(uint32_t index) override;

    ScrollWindowAdapter* GetScrollWindowAdapter() final;

    ScrollWindowAdapter* GetOrCreateScrollWindowAdapter() final;

protected:
    void ResetAdapter()
    {
        adapter_.Reset();
    }
    void JumpToItem(int32_t index);

    /**
     * @brief Pass latest layout range info to adapter.
     */
    void UpdateLayoutRange(Axis axis, int32_t markIdx);

    /**
     * @brief Pass scroll offset to adapter.
     */
    void UpdateOffset(float delta, Axis axis);

private:
    virtual RefPtr<FillAlgorithm> CreateFillAlgorithm() = 0;

    RefPtr<ScrollWindowAdapter> adapter_;
};
} // namespace OHOS::Ace::NG

#endif
