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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LAZY_LAYOUT_LAZY_GRID_LAYOUT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LAZY_LAYOUT_LAZY_GRID_LAYOUT_PATTERN_H

#include <functional>
#include <utility>

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_algorithm.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_property.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_info.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT LazyGridLayoutPattern : public LazyLayoutPattern {
    DECLARE_ACE_TYPE(LazyGridLayoutPattern, LazyLayoutPattern);

public:
    explicit LazyGridLayoutPattern()
    {
        layoutInfo_ = AceType::MakeRefPtr<LazyGridLayoutInfo>();
    }
    ~LazyGridLayoutPattern() override = default;

    void DumpAdvanceInfo() override;
    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override;
    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<LazyGridLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    FocusPattern GetFocusPattern() const override;

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override;

    void OnAttachToMainTree() override;
    void OnInActive() override;

    // 判断当前组件是否为 DynamicLayout
    bool IsDynamicLayout() const;

    // DynamicLayout 支持：设置动态布局标志
    void SetDynamicLayoutOptions(bool isDynamic)
    {
        isDynamicLayout_ = isDynamic;
    }

    AdjustOffset GetAdjustOffset() const override
    {
        return layoutInfo_->adjustOffset_;
    }

    AdjustOffset GetAndResetAdjustOffset() override
    {
        AdjustOffset ret = layoutInfo_->adjustOffset_;
        layoutInfo_->adjustOffset_ = AdjustOffset();
        return ret;
    }

    void SetOnVisibleIndexesChange(std::function<void(int32_t, int32_t)>&& onVisibleIndexesChange)
    {
        onVisibleIndexesChange_ = std::move(onVisibleIndexesChange);
    }

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    bool IsVerticalList(const RefPtr<UINode>& node);

    void PostIdleTask();
    void ProcessIdleTask(int64_t deadline);
    std::pair<int32_t, int32_t> GetVisibleIndexesRangeForCallback() const;
    void FireOnVisibleIndexesChange();
    void FireOnVisibleIndexesChange(const std::pair<int32_t, int32_t>& range);

    Axis axis_ = Axis::VERTICAL;
    int32_t itemTotalCount_ = 0;

    RefPtr<LazyGridLayoutInfo> layoutInfo_;

    // DynamicLayout 标识
    bool isDynamicLayout_ = false;
    bool hasVisibleIndexesChangeFired_ = false;
    std::function<void(int32_t, int32_t)> onVisibleIndexesChange_;
    std::pair<int32_t, int32_t> lastVisibleIndexesRange_ = { -1, -1 };

    ACE_DISALLOW_COPY_AND_MOVE(LazyGridLayoutPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LAZY_LAYOUT_LAZY_GRID_LAYOUT_PATTERN_H
