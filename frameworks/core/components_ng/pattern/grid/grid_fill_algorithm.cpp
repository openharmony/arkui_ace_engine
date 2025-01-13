/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/grid/grid_fill_algorithm.h"

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/grid/grid_layout_property.h"
#include "core/components_ng/pattern/grid/grid_utils.h"
#include "core/components_ng/pattern/grid/irregular/grid_irregular_filler.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {
void GridFillAlgorithm::PreFill(const SizeF& viewport, Axis axis, int32_t totalCnt)
{
    params_.mainGap = GridUtils::GetMainGap(props_, viewport, axis);

    std::string args = (axis == Axis::VERTICAL ? props_.GetColumnsTemplate() : props_.GetRowsTemplate()).value_or("");
    auto res = ParseTemplateArgs(GridUtils::ParseArgs(args), viewport.CrossSize(axis),
        GridUtils::GetCrossGap(props_, viewport, axis), totalCnt);

    params_.crossLens = std::vector<float>(res.first.begin(), res.first.end());
    params_.crossGap = static_cast<float>(res.second);
    if (params_.crossLens.empty()) {
        params_.crossLens.push_back(viewport.CrossSize(axis));
    }

    info_.axis_ = axis;
    info_.childrenCount_ = totalCnt;
}

RectF GridFillAlgorithm::CalcMarkItemRect(
    const SizeF& viewport, Axis axis, FrameNode* node, int32_t index, const std::optional<OffsetF>& slidingOffset)
{
    GridIrregularFiller filler(&info_, props_.GetHost().GetRawPtr());
    filler.FillMatrixOnly(index);
    const auto pos = info_.GetItemPos(index);
    filler.MeasureItem(params_, node, index, pos.first, pos.second);
    auto offset = slidingOffset.has_value() ? node->GetGeometryNode()->GetMarginFrameOffset() + slidingOffset.value()
                                            : node->GetGeometryNode()->GetMarginFrameOffset();
    auto size = node->GetGeometryNode()->GetMarginFrameSize();
    return { offset, size };
}

RectF GridFillAlgorithm::CalcItemRectAfterMarkItem(
    const SizeF& viewport, Axis axis, FrameNode* node, int32_t index, const RectF& markItem)
{
    GridIrregularFiller filler(&info_, props_.GetHost().GetRawPtr());
    filler.FillMatrixOnly(index);
    const auto pos = info_.GetItemPos(index);
    filler.MeasureItem(params_, node, index, pos.first, pos.second);

    auto pivotRow = info_.FindInMatrix(index - 1);
    if (pivotRow == info_.gridMatrix_.end() || pivotRow->first > pos.second) {
        LOGW("grid matrix is corrupted");
        return {};
    }
    if (pivotRow->first < pos.second) {
        OffsetF offset = axis == Axis::VERTICAL ? OffsetF(0.0f, markItem.Bottom() + params_.mainGap)
                                                : OffsetF(markItem.Right() + params_.mainGap, 0.0f);
        return { offset, node->GetGeometryNode()->GetMarginFrameSize() };
    }
    OffsetF offset = axis == Axis::VERTICAL ? OffsetF(markItem.Right() + params_.crossGap, markItem.Top())
                                            : OffsetF(markItem.Left(), markItem.Bottom() + params_.crossGap);
    return { offset, node->GetGeometryNode()->GetMarginFrameSize() };
}

RectF GridFillAlgorithm::CalcItemRectBeforeMarkItem(
    const SizeF& viewport, Axis axis, FrameNode* node, int32_t index, const RectF& markItem)
{
    // matrix is ready
    GridIrregularFiller filler(&info_, props_.GetHost().GetRawPtr());
    const auto pos = info_.GetItemPos(index);
    filler.MeasureItem(params_, node, index, pos.first, pos.second);

    auto pivotRow = info_.FindInMatrix(index + 1);
    if (pivotRow == info_.gridMatrix_.end() || pivotRow->first < pos.second) {
        LOGW("grid matrix is corrupted");
        return {};
    }
    const auto size = node->GetGeometryNode()->GetMarginFrameSize();
    if (pivotRow->first > pos.second) {
        // new line.
        OffsetF offset = axis == Axis::VERTICAL
                             ? OffsetF(viewport.Width() - size.Width(), markItem.Top() - params_.mainGap - size.Height())
                             : OffsetF(markItem.Left() - params_.mainGap - size.Width(), viewport.Height() - size.Height());
        return { offset, size };
    }
    OffsetF offset = axis == Axis::VERTICAL ? OffsetF(markItem.Left() - params_.crossGap - size.Width(), markItem.Top())
                                            : OffsetF(markItem.Left(), markItem.Top() - params_.crossGap - size.Height());
    return { offset, size };
}

bool GridFillAlgorithm::CanFillMore(const SizeF& scrollWindowSize, const RectF& markItemRect, FillDirection direction)
{
    // TODO: Axis::HORIZONTAL
    if (direction == FillDirection::START) {
        return GreatOrEqual(markItemRect.Top(), -scrollWindowSize.Height());
    }
    return LessNotEqual(markItemRect.Bottom(), scrollWindowSize.Height() * 2);
}
} // namespace OHOS::Ace::NG