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
 * @brief Base class of all components that support lazy load in ArkUI 2.0 (Arkoala)
 *
 */
class LazyContainer : virtual public Pattern {
    DECLARE_ACE_TYPE(LazyContainer, Pattern);

public:
    int32_t GetTotalChildCount() const override
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

    bool ArkoalaLazyEnabled() const
    {
        return adapter_;
    }

    /**
     * @brief Pass latest layout viewport to adapter.
     */
    void UpdateLayoutRange(Axis axis, bool firstLayout);

    /**
     * @brief Pass scroll offset to adapter.
     * @return true if adapter requests a recompose
     */
    bool UpdateOffset(float delta);

    void RequestJump(int32_t idx, ScrollAlign align = ScrollAlign::START, float extraOffset = 0.0f);

    /**
     * @return false if a recomposition is required first
     */
    bool RequestFillToTarget(int32_t idx, ScrollAlign align = ScrollAlign::START, float extraOffset = 0.0f);

    /**
     * @brief Should call when layout data needs to be cleared and re-calculated
     * @param idx first item in viewport after reset
     */
    void RequestReset(int32_t idx, float extraOffset = 0.0f);

private:
    virtual RefPtr<FillAlgorithm> CreateFillAlgorithm() = 0;

    RefPtr<ScrollWindowAdapter> adapter_;
};

/**
 * @brief Lazy container with linear layout (List, Swiper, WaterFlow)
 *
 */
class LinearLazyContainer : public LazyContainer {
    DECLARE_ACE_TYPE(LinearLazyContainer, LazyContainer);

private:
    RefPtr<FillAlgorithm> CreateFillAlgorithm() final;
};
} // namespace OHOS::Ace::NG

#endif
