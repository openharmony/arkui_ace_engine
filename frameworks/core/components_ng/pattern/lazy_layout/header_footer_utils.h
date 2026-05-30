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

#include "base/memory/referenced.h"
#include "core/components/common/properties/edge.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::NG {

class FrameNode;
class LayoutWrapper;
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

    static void EnsureStickyDefaultZIndex(const RefPtr<FrameNode>& edgeNode);

    // Pure-math sticky-position helpers; kept inline so hot-path layout code does not pay call overhead.
    static float CalcStickyHeaderPos(const HeaderFooterStickyMetrics& metrics)
    {
        return std::max(0.0f,
            std::min(metrics.viewStart, metrics.totalMainSize - metrics.footerMainSize - metrics.headerMainSize));
    }

    static float CalcStickyFooterPos(const HeaderFooterStickyMetrics& metrics)
    {
        const auto minFooterPos = metrics.headerMainSize;
        const auto maxFooterPos = std::max(minFooterPos, metrics.totalMainSize - metrics.footerMainSize);
        return std::min(maxFooterPos, std::max(minFooterPos, metrics.viewEnd - metrics.footerMainSize));
    }
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LAZY_LAYOUT_HEADER_FOOTER_UTILS_H
