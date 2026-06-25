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
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
LazyDynamicLayoutAlgorithm::LazyDynamicLayoutAlgorithm(const RefPtr<LazyCustomLayoutAlgorithmParam>& param)
    : customParams_(param)
{
}

void LazyDynamicLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto hasCustomMeasured = false;
    if (customParams_) {
        axis_ = customParams_->GetAxis();
        customParams_->SetAdjustedOffset(0);
        auto geometry = layoutWrapper->GetGeometryNode();
        float prevMainSize = geometry ? geometry->GetPaddingSize().MainSize(axis_) : 0.0f;
        hasCustomMeasured = customParams_->FireOnMeasureSize(layoutWrapper);
        float adjustOffset = customParams_->GetAdjustedOffset();
        ProcessAdjustOffset(layoutWrapper, adjustOffset, prevMainSize);
    }
    if (!hasCustomMeasured) {
        BoxLayoutAlgorithm::Measure(layoutWrapper);
    }
}

void LazyDynamicLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto hasCustomLayouted = customParams_ && customParams_->FireOnPlaceChildren(layoutWrapper);
    if (!hasCustomLayouted) {
        StackLayoutAlgorithm::Layout(layoutWrapper);
    } else {
        RecycleOutOfThreshold(layoutWrapper);
    }
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