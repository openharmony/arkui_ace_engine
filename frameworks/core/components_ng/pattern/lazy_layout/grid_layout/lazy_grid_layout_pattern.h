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

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_algorithm.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_property.h"
#include "core/components_ng/pattern/lazy_layout/grid_layout/lazy_grid_layout_info.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT LazyGridLayoutPattern : public LazyLayoutPattern {
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

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override
    {
        return ScopeFocusAlgorithm(ScopeFocusDirection::UNIVERSAL, false, true,
            ScopeType::OTHERS);
    }

    void OnAttachToMainTree() override;

    AdjustOffset GetAdjustOffset() const override
    {
        return layoutInfo_->adjustOffset_;
    }
private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void PostIdleTask();
    void ProcessIdleTask(int64_t deadline);

    Axis axis_ = Axis::VERTICAL;
    int32_t itemTotalCount_ = 0;

    RefPtr<LazyGridLayoutInfo> layoutInfo_;

    ACE_DISALLOW_COPY_AND_MOVE(LazyGridLayoutPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LAZY_LAYOUT_LAZY_GRID_LAYOUT_PATTERN_H
