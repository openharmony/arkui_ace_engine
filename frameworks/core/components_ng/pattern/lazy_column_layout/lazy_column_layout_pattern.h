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

class FrameNode;
class UINode;
enum class StickyStyle : uint32_t;

class ACE_FORCE_EXPORT LazyColumnLayoutPattern : public LazyLayoutPattern {
    DECLARE_ACE_TYPE(LazyColumnLayoutPattern, LazyLayoutPattern);

public:
    explicit LazyColumnLayoutPattern()
    {
        layoutInfo_ = AceType::MakeRefPtr<LazyColumnLayoutInfo>();
    }
    ~LazyColumnLayoutPattern() override = default;

    void OnAttachToMainTree() override;
    void OnModifyDone() override;
    void BeforeCreateLayoutWrapper() override;
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

    // Mount the header node (replaces any existing header). Validates via IsValidHeaderFooter first.
    void AddHeader(const RefPtr<UINode>& header);
    // Mount the footer node (replaces any existing footer). Validates via IsValidHeaderFooter first.
    void AddFooter(const RefPtr<UINode>& footer);
    // Remove the current header (if any).
    void RemoveHeader();
    // Remove the current footer (if any).
    void RemoveFooter();

    // Upgrade the header weak ref (may return null; callers must check).
    RefPtr<UINode> GetHeader() const
    {
        return header_.Upgrade();
    }

    // Upgrade the footer weak ref (may return null; callers must check).
    RefPtr<UINode> GetFooter() const
    {
        return footer_.Upgrade();
    }

    // Resolve the FrameNode that actually carries the header (peeling through BuilderProxy and friends).
    RefPtr<FrameNode> GetHeaderNode() const;
    // Resolve the FrameNode that actually carries the footer.
    RefPtr<FrameNode> GetFooterNode() const;

    // Header main-axis size; returns 0 when layoutInfo_ is null.
    float GetHeaderMainSize() const;

    // Footer main-axis size; returns 0 when layoutInfo_ is null.
    float GetFooterMainSize() const;

    // Resolve the active sticky style (NONE / HEADER / FOOTER / BOTH); defaults to NONE.
    StickyStyle GetStickyStyle() const;

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    // Validate a header / footer candidate. isHeader picks which side is the peerEdge.
    bool IsValidHeaderFooter(const RefPtr<UINode>& edge, bool isHeader) const;
    // Sync header/footer positions in the child sequence (header first, footer last). markDirty controls whether to
    // trigger a remeasure when a position move actually happened.
    void SyncHeaderFooter(bool markDirty = true);

    std::pair<int32_t, int32_t> GetVisibleIndexesRangeForCallback() const;
    void FireOnVisibleIndexesChange();
    void PostIdleTask();
    void ProcessIdleTask(int64_t deadline);

    int32_t itemTotalCount_ = 0;
    RefPtr<LazyColumnLayoutInfo> layoutInfo_;
    // Header / footer node weak refs to avoid retain cycles.
    WeakPtr<UINode> header_;
    WeakPtr<UINode> footer_;
    std::function<void(int32_t, int32_t)> onVisibleIndexesChange_;
    std::pair<int32_t, int32_t> lastVisibleIndexesRange_ = { -1, -1 };
    bool hasVisibleIndexesFired_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(LazyColumnLayoutPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_COLUMN_LAYOUT_LAZY_COLUMN_LAYOUT_PATTERN_H
