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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_COLUMN_LAYOUT_LAZY_COLUMN_LAYOUT_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_COLUMN_LAYOUT_LAZY_COLUMN_LAYOUT_PATTERN_H

#include <functional>

#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_algorithm.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_property.h"
#include "core/components_ng/pattern/lazy_column_layout/lazy_column_layout_info.h"

namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT LazyColumnLayoutPattern : public LazyLayoutPattern {
    DECLARE_ACE_TYPE(LazyColumnLayoutPattern, LazyLayoutPattern);

public:
    explicit LazyColumnLayoutPattern()
    {
        layoutInfo_ = AceType::MakeRefPtr<LazyColumnLayoutInfo>();
    }
    ~LazyColumnLayoutPattern() override = default;

    void OnAttachToMainTree() override;
    void DumpAdvanceInfo() override;
    void DumpAdvanceInfo(std::unique_ptr<JsonValue>& json) override;
    bool IsAtomicNode() const override;
    RefPtr<LayoutProperty> CreateLayoutProperty() override;
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;
    FocusPattern GetFocusPattern() const override;
    ScopeFocusAlgorithm GetScopeFocusAlgorithm() override;
    AdjustOffset GetAdjustOffset() const override;
    AdjustOffset GetAndResetAdjustOffset() override;

    void SetOnVisibleIndexesChange(std::function<void(int32_t, int32_t)>&& onVisibleIndexesChange);

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    std::pair<int32_t, int32_t> GetVisibleIndexesRangeForCallback() const;
    void FireOnVisibleIndexesChange();
    void PostIdleTask();
    void ProcessIdleTask(int64_t deadline);

    int32_t itemTotalCount_ = 0;
    RefPtr<LazyColumnLayoutInfo> layoutInfo_;
    std::function<void(int32_t, int32_t)> onVisibleIndexesChange_;
    std::pair<int32_t, int32_t> lastVisibleIndexesRange_ = { -1, -1 };
    bool hasVisibleIndexesFired_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(LazyColumnLayoutPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_COLUMN_LAYOUT_LAZY_COLUMN_LAYOUT_PATTERN_H
