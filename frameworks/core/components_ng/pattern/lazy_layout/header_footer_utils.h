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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_LAYOUT_HEADER_FOOTER_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_LAYOUT_HEADER_FOOTER_UTILS_H

#include <algorithm>
#include <cstdint>
#include <optional>

#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/edge.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

class UINode;

// Sticky behavior for header / footer in lazy scrollable containers
// (LazyVGridLayout, LazyColumnLayout, LazyVWaterFlowLayout). Values intentionally match
// V2::StickyStyle so that integer-encoded ArkTS bridge inputs remain interchangeable.
enum class StickyStyle : uint32_t {
    NONE = 0,
    HEADER = 1,
    FOOTER = 2,
    BOTH = 3,
};

struct HeaderFooterStickyMetrics {
    float viewStart = 0.0f;
    float viewEnd = 0.0f;
    float totalMainSize = 0.0f;
    float headerMainSize = 0.0f;
    float footerMainSize = 0.0f;
    // Insets the header pins below / the footer pins above (ancestor sticky edge height or contentStart/EndOffset).
    float stickyTopInset = 0.0f;
    float stickyBottomInset = 0.0f;
};

// Shared helper for header/footer nodes used by scrollable lazy containers. It centralizes ownership,
// assistive traversal flags, measurement, and sticky math so each container keeps only its layout-specific logic.
class ACE_FORCE_EXPORT HeaderFooterUtils {
public:
    static void ReplaceHeaderFooter(const RefPtr<FrameNode>& host, WeakPtr<UINode>& slot, const RefPtr<UINode>& edge,
        std::optional<int32_t> insertIndex = std::nullopt,
        PropertyChangeFlag dirtyFlag = PROPERTY_UPDATE_BY_CHILD_REQUEST);

    static void RemoveHeaderFooter(const RefPtr<FrameNode>& host, WeakPtr<UINode>& slot,
        PropertyChangeFlag dirtyFlag = PROPERTY_UPDATE_BY_CHILD_REQUEST);

    static RefPtr<FrameNode> GetHeaderFooterFrameNode(const WeakPtr<UINode>& slot);
    static RefPtr<FrameNode> GetHeaderFooterFrameNode(const RefPtr<UINode>& edge);

    static void UpdateEdgeAccessibility(const RefPtr<UINode>& edge);

    static float MeasureHeaderFooter(LayoutWrapper* layoutWrapper, int32_t rawIndex,
        const LayoutConstraintF& constraint, Axis axis,
        std::optional<MeasureType> measureType = std::nullopt);

    // Measure one edge (header / footer); 0 when the edge is absent. Delta tracking and layout-info
    // write-back stay with the caller.
    static float MeasureEdgeMainSize(LayoutWrapper* layoutWrapper, const WeakPtr<FrameNode>& edge,
        int32_t rawIndex, const LayoutConstraintF& constraint, Axis axis);

    // Position + layout one edge (header / footer) child. isRtl mirrors the cross offset against crossSize;
    // callers decide RTL applicability themselves (e.g. LazyGrid only mirrors on the vertical axis).
    static void LayoutEdge(LayoutWrapper* layoutWrapper, int32_t rawIndex, const OffsetF& offset,
        bool isSticky, bool isRtl, float crossSize);

    static void EnsureStickyDefaultZIndex(const RefPtr<FrameNode>& edgeNode);

    static bool IsHeaderSticky(StickyStyle style)
    {
        return style == StickyStyle::HEADER || style == StickyStyle::BOTH;
    }

    static bool IsFooterSticky(StickyStyle style)
    {
        return style == StickyStyle::FOOTER || style == StickyStyle::BOTH;
    }

    // Content item count = rawCount - header(0/1) - footer(0/1). hasFooter additionally requires
    // footerIndex != headerIndex so a corner case where a single section edge is held by both header
    // and footer never gets subtracted twice.
    static int32_t CalcContentItemCount(int32_t rawCount, int32_t headerIndex, int32_t footerIndex)
    {
        const bool hasHeader = headerIndex >= 0 && headerIndex < rawCount;
        const bool hasFooter = footerIndex >= 0 && footerIndex < rawCount && footerIndex != headerIndex;
        return std::max(rawCount - (hasHeader ? 1 : 0) - (hasFooter ? 1 : 0), 0);
    }

    // Parent-scroll compensation for a header resize; window coords are body-local. A header resize moves
    // every body item by the same section-level delta (item pos = bodyPos + header), which body-local anchors
    // cannot see: the parent must consume the returned delta via adjustOffset.start, otherwise visible items
    // jump on screen while a pinned header stays put. State gates (forward layout, non-predict pass, had
    // measured items) are the caller's responsibility.
    static float CalcHeaderResizeAdjust(float headerMainSizeDelta, float bodyViewStart, float headerMainSize)
    {
        const float sectionViewStart = bodyViewStart + headerMainSize;
        // At the section top the header legitimately pushes items down; no compensation.
        if (!Positive(sectionViewStart)) {
            return 0.0f;
        }
        // Clamp a shrink so the compensated viewport never lands above the section top.
        return std::max(headerMainSizeDelta, -sectionViewStart);
    }

    // Refresh edge weak-refs from the owner pattern and resolve their raw child indices. Re-resolving every
    // frame matters: a reused algorithm's construction-time weak-ref dangles after the edge nodes are rebuilt
    // (e.g. toggling sticky). SyncHeaderFooter() normalizes header to raw index 0, footer to raw index last.
    template<typename PatternT>
    static void ResolveEdgeIndexes(LayoutWrapper* layoutWrapper, WeakPtr<FrameNode>& header,
        WeakPtr<FrameNode>& footer, int32_t& headerIndex, int32_t& footerIndex)
    {
        if (!layoutWrapper) {
            headerIndex = -1;
            footerIndex = -1;
            return;
        }
        if (auto host = layoutWrapper->GetHostNode()) {
            if (auto pattern = host->GetPattern<PatternT>()) {
                header = pattern->GetHeaderNode();
                footer = pattern->GetFooterNode();
            }
        }
        const auto rawCount = layoutWrapper->GetTotalChildCount();
        const bool hasHeader = header.Upgrade() != nullptr && rawCount > 0;
        const bool hasFooter = footer.Upgrade() != nullptr && rawCount > (hasHeader ? 1 : 0);
        headerIndex = hasHeader ? 0 : -1;
        footerIndex = hasFooter ? rawCount - 1 : -1;
    }

    // Pure-math sticky-position helpers; kept inline so hot-path layout code does not pay call overhead.
    static float CalcStickyHeaderPos(const HeaderFooterStickyMetrics& metrics)
    {
        // +stickyTopInset shifts the pinned header down by the inset (lands just below the ancestor inset).
        return std::max(0.0f, std::min(metrics.viewStart + metrics.stickyTopInset,
            metrics.totalMainSize - metrics.footerMainSize - metrics.headerMainSize));
    }

    static float CalcStickyFooterPos(const HeaderFooterStickyMetrics& metrics)
    {
        const auto minFooterPos = metrics.headerMainSize;
        const auto maxFooterPos = std::max(minFooterPos, metrics.totalMainSize - metrics.footerMainSize);
        // -stickyBottomInset lifts the pinned footer up by the inset (lands above the ancestor inset).
        return std::min(maxFooterPos,
            std::max(minFooterPos, metrics.viewEnd - metrics.stickyBottomInset - metrics.footerMainSize));
    }
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_LAYOUT_HEADER_FOOTER_UTILS_H
