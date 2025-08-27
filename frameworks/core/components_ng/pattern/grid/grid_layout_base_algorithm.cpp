/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid/grid_layout_base_algorithm.h"

#include "core/components_ng/pattern/grid/grid_pattern.h"

namespace OHOS::Ace::NG {

void GridLayoutBaseAlgorithm::AdjustChildrenHeight(LayoutWrapper* layoutWrapper)
{
    info_.clearStretch_ = false;
    auto gridLayoutProperty = AceType::DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(gridLayoutProperty);
    const int32_t cacheCount = gridLayoutProperty->GetCachedCountValue(info_.defCachedCount_);
    const int32_t startLine = std::max(info_.startMainLineIndex_ - cacheCount, 0);
    const int32_t endLine = info_.endMainLineIndex_ + cacheCount;
    for (int i = startLine; i <= endLine; i++) {
        if (IsIrregularLine(i)) {
            continue;
        }
        const auto& line = info_.gridMatrix_.find(i);
        if (line == info_.gridMatrix_.end() || line->second.empty()) {
            continue;
        }

        auto lineHeightIter = info_.lineHeightMap_.find(i);
        if (lineHeightIter == info_.lineHeightMap_.end()) {
            continue;
        }
        const float lineHeight = lineHeightIter->second;

        for (auto iter = line->second.begin(); iter != line->second.end(); iter++) {
            const int32_t itemIndex = iter->second;
            auto child = layoutWrapper->GetChildByIndex(itemIndex);
            if (!child) {
                break;
            }
            auto childLayoutProperty = AceType::DynamicCast<GridItemLayoutProperty>(child->GetLayoutProperty());
            if (!childLayoutProperty) {
                break;
            }
            auto childConstraint = childLayoutProperty->GetLayoutConstraint();
            if (!childLayoutProperty->GetNeedStretch() &&
                childConstraint->selfIdealSize.MainSize(info_.axis_).has_value()) {
                continue;
            }

            auto childFrameSize = child->GetGeometryNode()->GetFrameSize();
            if (GreatOrEqual(childFrameSize.MainSize(info_.axis_), lineHeight)) {
                continue;
            }
            childConstraint->selfIdealSize.SetMainSize(lineHeight, info_.axis_);
            childLayoutProperty->SetNeedStretch(true);
            childLayoutProperty->SetAxis(info_.axis_);
            child->Measure(childConstraint);
        }
    }
}

void GridLayoutBaseAlgorithm::UpdateOverlay(LayoutWrapper* layoutWrapper)
{
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (!paintProperty->GetFadingEdge().value_or(false)) {
        return;
    }
    auto overlayNode = frameNode->GetOverlayNode();
    CHECK_NULL_VOID(overlayNode);
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto overlayGeometryNode = overlayNode->GetGeometryNode();
    CHECK_NULL_VOID(overlayGeometryNode);
    overlayGeometryNode->SetFrameSize(geometryNode->GetFrameSize(true));
}


void GridLayoutBaseAlgorithm::LostChildFocusToSelf(LayoutWrapper* layoutWrapper, int32_t start, int32_t end)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    CHECK_NULL_VOID(focusHub->IsCurrentFocus());
    auto focusIndex = host->GetPattern<GridPattern>()->GetFocusedIndex();
    CHECK_NULL_VOID(focusIndex.has_value());
    if (focusIndex.value() >= start && focusIndex.value() <= end) {
        return;
    }
    auto childFocusHub = focusHub->GetLastWeakFocusNode().Upgrade();
    CHECK_NULL_VOID(childFocusHub);
    if (childFocusHub->IsCurrentFocus()) {
        focusHub->LostChildFocusToSelf();
    }
}

void GridLayoutBaseAlgorithm::CalcContentOffset(LayoutWrapper* layoutWrapper, float mainSize)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto property = AceType::DynamicCast<GridLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(property);
    auto startOffset = property->GetContentStartOffset();
    if (!startOffset.has_value()) {
        info_.contentStartOffset_ = 0;
    }
    auto endOffset = property->GetContentEndOffset();
    if (!endOffset.has_value()) {
        info_.contentEndOffset_ = 0;
    }
    if (!endOffset && !startOffset) {
        return;
    }
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (startOffset) {
        info_.contentStartOffset_ =
            std::max(pipeline->NormalizeToPx(Dimension(startOffset.value(), DimensionUnit::VP)), 0.0);
    }
    if (endOffset) {
        info_.contentEndOffset_ =
            std::max(pipeline->NormalizeToPx(Dimension(endOffset.value(), DimensionUnit::VP)), 0.0);
    }
    if (GreatOrEqual(info_.contentStartOffset_ + info_.contentEndOffset_, mainSize)) {
        info_.contentStartOffset_ = 0.0f;
        info_.contentEndOffset_ = 0.0f;
    }
}
} // namespace OHOS::Ace::NG
