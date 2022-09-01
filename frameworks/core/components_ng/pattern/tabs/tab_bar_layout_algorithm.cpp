/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/tabs/tab_bar_layout_algorithm.h"

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/tabs/tab_bar_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void TabBarLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto idealSize = CreateIdealSize(constraint.value(), axis_, layoutProperty->GetMeasureType(), true);
    geometryNode->SetFrameSize(idealSize);

    // Create children layout constraint.
    auto childCount = layoutWrapper->GetTotalChildCount();
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    auto childMainSize = geometryNode->GetFrameSize().MainSize(axis_) / childCount;
    if (axis_ == Axis::HORIZONTAL) {
        childLayoutConstraint.minSize.SetWidth(childMainSize);
        childLayoutConstraint.maxSize.SetWidth(childMainSize);
    } else {
        childLayoutConstraint.minSize.SetHeight(childMainSize);
        childLayoutConstraint.maxSize.SetHeight(childMainSize);
    }

    // Measure children.
    for (int32_t index = 0; index < childCount; ++index) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!childWrapper) {
            LOGI("Child %{public}d is null.", index);
            return;
        }
        childWrapper->Measure(childLayoutConstraint);
    }
}

void TabBarLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    tabItemOffset_.clear();
    CHECK_NULL_VOID(layoutWrapper);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto childCount = layoutWrapper->GetTotalChildCount();

    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();
    auto childMainSize = geometryNode->GetFrameSize().MainSize(axis_) / childCount;
    OffsetF childOffset = OffsetF(0.0f, 0.0f);
    for (int32_t index = 0; index < childCount; ++index) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(childWrapper);
        auto childGeometryNode = childWrapper->GetGeometryNode();
        CHECK_NULL_VOID(childGeometryNode);
        if (axis_ == Axis::HORIZONTAL) {
            childOffset = OffsetF(childMainSize * index, 0.0f);
        } else {
            childOffset = OffsetF(0.0f, childMainSize * index);
        }
        childGeometryNode->SetFrameOffset(childOffset);
        childWrapper->Layout(parentOffset);
        tabItemOffset_.emplace_back(childOffset);
    }
    tabItemOffset_.emplace_back(childOffset +
        (axis_ == Axis::HORIZONTAL ? OffsetF(childMainSize, 0.0f) : OffsetF(0.0f, childMainSize)));
}

} // namespace OHOS::Ace::NG
