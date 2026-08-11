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

#include "core/components_ng/pattern/dynamiclayout/lazy_dynamic_layout_algorithm.h"
#include "core/components_ng/pattern/dynamiclayout/active_range_updater.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#include "core/components_ng/pattern/lazy_layout/lazy_layout_utils.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
namespace {
// The frontend LazyLayoutHelper treats this range as an empty detached estimate pass: invoke custom measure so the
// host can publish an estimate, but do not materialize any child until a parent supplies a real viewport reference.
constexpr float DETACHED_ESTIMATE_VIEW_POS = -1.0f;
} // namespace

LazyDynamicLayoutAlgorithm::LazyDynamicLayoutAlgorithm(const RefPtr<LazyCustomLayoutAlgorithmParam>& param)
    : customParams_(param)
{
}

void LazyDynamicLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    needSkipLayout_ = false;
    isEstimatePass_ = false;
    if (customParams_) {
        axis_ = customParams_->GetAxis();
    }
    const auto measureMode = ResolveMeasureMode(layoutWrapper);
    needSkipLayout_ = measureMode == LazyLayoutMeasureMode::SKIP;
    isEstimatePass_ = measureMode == LazyLayoutMeasureMode::ESTIMATE;
    if (needSkipLayout_) {
        // Keep the persistent geometry untouched. Measuring with an empty child list can collapse a reused host.
        return;
    }
    const auto originalConstraint = PrepareEstimateConstraint(layoutWrapper);
    const bool hasCustomMeasured = MeasureWithCustomAlgorithm(layoutWrapper);
    RestoreEstimateConstraint(layoutWrapper, originalConstraint);
    if (hasCustomMeasured) {
        return;
    }
    if (!isEstimatePass_) {
        BoxLayoutAlgorithm::Measure(layoutWrapper);
        return;
    }
    std::list<RefPtr<LayoutWrapper>> emptyChildren;
    BoxLayoutAlgorithm::PerformMeasureSelfWithChildList(layoutWrapper, emptyChildren);
}

void LazyDynamicLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    if (isEstimatePass_ || needSkipLayout_) {
        return;
    }
    auto hasCustomLayouted = customParams_ && customParams_->FireOnPlaceChildren(layoutWrapper);
    if (!hasCustomLayouted) {
        StackLayoutAlgorithm::Layout(layoutWrapper);
    } else {
        RecycleOutOfThreshold(layoutWrapper);
    }
}

LazyLayoutMeasureMode LazyDynamicLayoutAlgorithm::ResolveMeasureMode(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, LazyLayoutMeasureMode::NORMAL);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, LazyLayoutMeasureMode::NORMAL);
    const auto& contentConstraint = layoutProperty->GetContentLayoutConstraint();
    auto host = layoutWrapper->GetHostNode();
    const auto totalChildCount = layoutWrapper->GetTotalChildCount();
    auto geometry = layoutWrapper->GetGeometryNode();
    const bool hasMeasuredBaseline = geometry && Positive(geometry->GetPaddingSize().MainSize(axis_));
    const std::optional<ViewPosReference> viewPosRef = contentConstraint.has_value()
        ? contentConstraint->viewPosRef : std::nullopt;
    // A tiny synthetic range makes the frontend dispatch __onMeasure__ with LazyLayoutHelper. The custom
    // algorithm still reports its full size while materializing only children intersecting that estimate range.
    return LazyLayoutUtils::ResolveMeasureMode(
        host, axis_, viewPosRef, totalChildCount, 1, hasMeasuredBaseline);
}

std::optional<LayoutConstraintF> LazyDynamicLayoutAlgorithm::PrepareEstimateConstraint(LayoutWrapper* layoutWrapper)
{
    if (!isEstimatePass_) {
        return std::nullopt;
    }
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, std::nullopt);
    auto originalConstraint = layoutProperty->GetLayoutConstraint();
    if (!originalConstraint.has_value()) {
        return std::nullopt;
    }
    auto estimateConstraint = originalConstraint.value();
    auto estimateReference = LazyLayoutUtils::CreateEstimateViewPosReference(axis_);
    if (!originalConstraint->viewPosRef.has_value()) {
        // Invoke custom measure for a detached cache host without materializing children before a real range arrives.
        estimateReference.viewPosStart = DETACHED_ESTIMATE_VIEW_POS;
        estimateReference.viewPosEnd = DETACHED_ESTIMATE_VIEW_POS;
    }
    estimateConstraint.viewPosRef = estimateReference;
    layoutProperty->UpdateLayoutConstraint(estimateConstraint);
    layoutProperty->UpdateContentConstraint();
    return originalConstraint;
}

void LazyDynamicLayoutAlgorithm::RestoreEstimateConstraint(
    LayoutWrapper* layoutWrapper, const std::optional<LayoutConstraintF>& originalConstraint)
{
    if (!originalConstraint.has_value()) {
        return;
    }
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateLayoutConstraint(originalConstraint.value());
    layoutProperty->UpdateContentConstraint();
}

bool LazyDynamicLayoutAlgorithm::MeasureWithCustomAlgorithm(LayoutWrapper* layoutWrapper)
{
    if (!customParams_) {
        return false;
    }
    customParams_->SetAdjustedOffset(0);
    auto geometry = layoutWrapper->GetGeometryNode();
    const float prevMainSize = geometry ? geometry->GetPaddingSize().MainSize(axis_) : 0.0f;
    const bool hasCustomMeasured = customParams_->FireOnMeasureSize(layoutWrapper);
    ProcessAdjustOffset(layoutWrapper, customParams_->GetAdjustedOffset(), prevMainSize);
    return hasCustomMeasured;
}

void LazyDynamicLayoutAlgorithm::ProcessAdjustOffset(
    LayoutWrapper* layoutWrapper, float adjustOffset, float prevMainSize)
{
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);

    auto contentLayoutConstraint = layoutProperty->GetContentLayoutConstraint();
    CHECK_NULL_VOID(contentLayoutConstraint);

    auto posRef = contentLayoutConstraint->viewPosRef;
    if (!posRef.has_value() || posRef.value().axis != axis_) {
        return;
    }
    auto geometry = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometry);
    AdjustOffset offset;
    auto mainSize = geometry->GetPaddingSize().MainSize(axis_);
    if (posRef.value().referenceEdge == ReferenceEdge::START) {
        offset.start = -adjustOffset;
        offset.end = mainSize - prevMainSize + adjustOffset;
    } else {
        offset.start = mainSize - prevMainSize - adjustOffset;
        offset.end = adjustOffset;
    }
    customParams_->SetAdjustOffset(offset);
}

void LazyDynamicLayoutAlgorithm::RecycleOutOfThreshold(LayoutWrapper* layoutWrapper)
{
    float adjustOffset = customParams_ ? customParams_->GetAdjustedOffset() : 0;
    auto inActiveChildren = customParams_ ? customParams_->GetInActiveChildren() : std::vector<int32_t>();
    ActiveRangeUpdater updater;
    updater.UpdateActiveRange(layoutWrapper, axis_, adjustOffset, inActiveChildren);
    visibleIndexes_ = updater.GetVisibleIndexes();
}

} // namespace OHOS::Ace::NG