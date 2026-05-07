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
    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override;
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
    FocusPattern GetFocusPattern() const override;
    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override;
    void OnActive() override;
    void NotifyDataChange(int32_t index, int32_t count) override;
    void OnAttachToMainTree() override;
    void OnInActive() override;

    AdjustOffset GetAdjustOffset() const override;
    AdjustOffset GetAndResetAdjustOffset() override;

    void SetOnVisibleIndexesChange(std::function<void(int32_t, int32_t)>&& onVisibleIndexesChange)
    {
        onVisibleIndexesChange_ = std::move(onVisibleIndexesChange);
        ResetVisibleIndexesChangeState();
    }

private:
    static constexpr int32_t MAX_IDLE_DEADLINE_MISS_COUNT = 3;

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void ResetVisibleIndexesChangeState();
    void PostIdleTask();
    void ProcessIdleTask(int64_t deadline);
    std::pair<int32_t, int32_t> GetVisibleIndexesRangeForCallback() const;
    void FireOnVisibleIndexesChange();
    void FireOnVisibleIndexesChange(const std::pair<int32_t, int32_t>& range);

    int32_t itemTotalCount_ = 0;
    RefPtr<LazyWaterFlowLayoutInfo> layoutInfo_;
    bool hasVisibleIndexesChangeFired_ = false;
    int32_t idleDeadlineMissCount_ = 0;
    std::function<void(int32_t, int32_t)> onVisibleIndexesChange_;
    std::pair<int32_t, int32_t> lastVisibleIndexesRange_ = { -1, -1 };

    ACE_DISALLOW_COPY_AND_MOVE(LazyWaterFlowLayoutPattern);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_WATERFLOW_LAYOUT_PATTERN_H
