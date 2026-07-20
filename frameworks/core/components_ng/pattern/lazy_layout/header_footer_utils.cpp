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

#include "core/components_ng/pattern/lazy_layout/header_footer_utils.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_pattern.h"
#include "core/components_ng/property/accessibility_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {

void HeaderFooterUtils::ReplaceHeaderFooter(const RefPtr<FrameNode>& host, WeakPtr<UINode>& slot,
    const RefPtr<UINode>& edge, std::optional<int32_t> insertIndex, PropertyChangeFlag dirtyFlag)
{
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(edge);
    auto prevEdge = slot.Upgrade();
    if (prevEdge == edge) {
        UpdateEdgeAccessibility(edge);
        return;
    }
    if (!prevEdge) {
        if (insertIndex.has_value()) {
            host->AddChild(edge, insertIndex.value());
        } else {
            host->AddChild(edge);
        }
    } else {
        // Replacement keeps the previous edge position. insertIndex only applies to first mount.
        host->ReplaceChild(prevEdge, edge);
    }
    host->MarkDirtyNode(dirtyFlag);
    slot = edge;
    UpdateEdgeAccessibility(edge);
}

void HeaderFooterUtils::RemoveHeaderFooter(
    const RefPtr<FrameNode>& host, WeakPtr<UINode>& slot, PropertyChangeFlag dirtyFlag)
{
    CHECK_NULL_VOID(host);
    auto prevEdge = slot.Upgrade();
    if (!prevEdge) {
        return;
    }
    host->RemoveChild(prevEdge);
    host->MarkDirtyNode(dirtyFlag);
    slot.Reset();
}

RefPtr<FrameNode> HeaderFooterUtils::GetHeaderFooterFrameNode(const WeakPtr<UINode>& slot)
{
    return GetHeaderFooterFrameNode(slot.Upgrade());
}

RefPtr<FrameNode> HeaderFooterUtils::GetHeaderFooterFrameNode(const RefPtr<UINode>& edge)
{
    CHECK_NULL_RETURN(edge, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(edge);
    if (frameNode) {
        return frameNode;
    }
    return AceType::DynamicCast<FrameNode>(edge->GetFrameChildByIndex(0, false));
}

void HeaderFooterUtils::UpdateEdgeAccessibility(const RefPtr<UINode>& edge)
{
    auto edgeNode = GetHeaderFooterFrameNode(edge);
    CHECK_NULL_VOID(edgeNode);
    auto accessibilityProperty = edgeNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetIsHeaderOrFooter(true);
}

float HeaderFooterUtils::MeasureHeaderFooter(LayoutWrapper* layoutWrapper, int32_t rawIndex,
    const LayoutConstraintF& constraint, Axis axis, std::optional<MeasureType> measureType)
{
    CHECK_NULL_RETURN(layoutWrapper, 0.0f);
    if (rawIndex < 0) {
        return 0.0f;
    }
    auto child = layoutWrapper->GetOrCreateChildByIndex(rawIndex);
    CHECK_NULL_RETURN(child, 0.0f);
    if (measureType.has_value()) {
        auto childLayoutProperty = child->GetLayoutProperty();
        CHECK_NULL_RETURN(childLayoutProperty, 0.0f);
        childLayoutProperty->UpdateMeasureType(measureType.value());
    }
    child->Measure(constraint);
    auto geometryNode = child->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);
    return std::max(GetMainAxisSize(geometryNode->GetMarginFrameSize(), axis), 0.0f);
}

float HeaderFooterUtils::MeasureEdgeMainSize(LayoutWrapper* layoutWrapper, const WeakPtr<FrameNode>& edge,
    int32_t rawIndex, const LayoutConstraintF& constraint, Axis axis)
{
    if (!edge.Upgrade() || rawIndex < 0) {
        return 0.0f;
    }
    return MeasureHeaderFooter(layoutWrapper, rawIndex, constraint, axis);
}

void HeaderFooterUtils::LayoutEdge(LayoutWrapper* layoutWrapper, int32_t rawIndex, const OffsetF& offset,
    bool isSticky, bool isRtl, float crossSize, int32_t stickyZIndex)
{
    if (rawIndex < 0) {
        return;
    }
    CHECK_NULL_VOID(layoutWrapper);
    auto child = layoutWrapper->GetChildByIndex(rawIndex);
    if (!child) {
        child = layoutWrapper->GetOrCreateChildByIndex(rawIndex);
    }
    CHECK_NULL_VOID(child);
    auto hostNode = child->GetHostNode();
    if (isSticky) {
        EnsureStickyDefaultZIndex(hostNode, stickyZIndex);
    }
    auto geometryNode = child->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto finalOffset = offset;
    if (isRtl) {
        finalOffset.SetX(offset.GetX() + crossSize - geometryNode->GetMarginFrameSize().Width());
    }
    geometryNode->SetMarginFrameOffset(finalOffset);
    // Always active + laid out: a stale inactive edge would skip geometry sync and freeze at its old position.
    child->SetActive(true);
    child->Layout();
}

void HeaderFooterUtils::EnsureStickyDefaultZIndex(const RefPtr<FrameNode>& edgeNode, int32_t stickyZIndex)
{
    CHECK_NULL_VOID(edgeNode);
    auto renderContext = edgeNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto zIndex = renderContext->GetZIndex();
    // Promote only default (unset/0) nodes; explicit user zIndex wins. The value is not restored when sticky
    // toggles off — framework-assigned and identical user-assigned values are indistinguishable.
    if (!zIndex.has_value() || zIndex.value() == 0) {
        renderContext->UpdateZIndex(stickyZIndex);
    }
}

std::optional<float> HeaderFooterUtils::GetNextStickyHeaderGap(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, std::nullopt);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto pattern = host->GetPattern<LazyLayoutPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    return pattern->GetNextStickyHeaderGap();
}

} // namespace OHOS::Ace::NG
