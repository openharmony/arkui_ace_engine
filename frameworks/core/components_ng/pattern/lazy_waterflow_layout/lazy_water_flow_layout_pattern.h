/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_PATTERN_H

#include <cstdint>
#include <functional>
#include <memory>
#include <utility>

#include "base/utils/noncopyable.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_pattern.h"

namespace OHOS::Ace::NG {

class FrameNode;
class LazyWaterFlowLayoutInfo;
class LayoutWrapper;
class UINode;

class ACE_FORCE_EXPORT LazyWaterFlowLayoutPattern : public LazyLayoutPattern {
    DECLARE_ACE_TYPE(LazyWaterFlowLayoutPattern, LazyLayoutPattern);

public:
    LazyWaterFlowLayoutPattern();
    ~LazyWaterFlowLayoutPattern() override = default;

    void DumpAdvanceInfo() override;
    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override;
    // Container, not atomic.
    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override;
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
    // SCOPE container, focusable by default.
    FocusPattern GetFocusPattern() const override;
    // UNIVERSAL direction, non-cyclic, wrap allowed.
    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override;
    // Reset idle miss counter and mark dirty so the steady-state estimate refreshes in nested scenarios.
    void OnActive() override;
    void NotifyDataChange(int32_t index, int32_t count) override;
    // LazyLayoutUtils::ValidateLazyLayoutParent walks the ancestor chain: allowed wrappers are tagged
    // needLazyLayout=true; vertical List / WaterFlow / Scroll terminate the walk; anything else aborts.
    void OnAttachToMainTree() override;
    // Emit a final (-1, -1) on the visible callback and reset bookkeeping.
    void OnInActive() override;

    // Read-only peek; parent uses this to inspect without draining.
    AdjustOffset GetAdjustOffset() const override;
    // Read-and-clear; parent consumes once per frame.
    AdjustOffset GetAndResetAdjustOffset() override;

    // Re-arm "first invocation always fires" by resetting the dedupe state.
    void SetOnVisibleIndexesChange(std::function<void(int32_t, int32_t)>&& onVisibleIndexesChange)
    {
        onVisibleIndexesChange_ = std::move(onVisibleIndexesChange);
        ResetVisibleIndexesChangeState();
    }

private:
    // Max consecutive deadline misses inside one idle-task chain before giving up the current predict round.
    static constexpr int32_t MAX_IDLE_DEADLINE_MISS_COUNT = 3;

    // Sync totalItemCount_, fire visible callback, post predict task when NeedPredict.
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    // Clear "fired" bit and seed lastVisibleIndexesRange_ to a value next callback can never equal.
    void ResetVisibleIndexesChangeState();
    void PostIdleTask();
    // Predict body. Bail when NeedPredict false; on missed deadline bump counter and re-post (up to MAX);
    // otherwise inject deadline_ + ProcessOffscreenNode + clear deadline_.
    void ProcessIdleTask(int64_t deadline);
    // (start, end) tuple. Out-of-range / invalid normalized to (-1, -1).
    std::pair<int32_t, int32_t> GetVisibleIndexesRangeForCallback() const;
    void FireOnVisibleIndexesChange();
    // Deduplicated: same range fires at most once in a row.
    void FireOnVisibleIndexesChange(const std::pair<int32_t, int32_t>& range);

    // Cached from Algorithm::GetTotalItemCount; refreshed each OnDirtyLayoutWrapperSwap.
    int32_t itemTotalCount_ = 0;
    RefPtr<LazyWaterFlowLayoutInfo> layoutInfo_;
    // Backs the "first-fire then dedupe" policy.
    bool hasVisibleIndexesFired_ = false;
    // Cleared in OnActive and on a successful predict; NOT cleared by OnModifyDone, so consecutive misses across
    // relayouts in the same idle chain stay visible.
    int32_t idleDeadlineMissCount_ = 0;
    std::function<void(int32_t, int32_t)> onVisibleIndexesChange_;
    std::pair<int32_t, int32_t> lastVisibleIndexesRange_ = { -1, -1 };

    ACE_DISALLOW_COPY_AND_MOVE(LazyWaterFlowLayoutPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_PATTERN_H
