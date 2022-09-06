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
#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {

constexpr Dimension TAB_BAR_DEFAULT_SIZE = 56.0_vp;

} // namespace

void TabBarLayoutAlgorithm::UpdateChildConstraint(LayoutConstraintF& childConstraint,
    const RefPtr<TabBarLayoutProperty>& layoutProperty, const SizeF& ideaSize, int32_t childCount, Axis axis)
{
    childConstraint.parentIdealSize = OptionalSizeF(ideaSize);
    auto barMode = layoutProperty->GetTabBarMode().value_or(TabBarMode::FIXED);
    if (barMode == TabBarMode::FIXED) {
        auto childIdeaSize = ideaSize;
        if (axis == Axis::HORIZONTAL) {
            childIdeaSize.SetWidth(ideaSize.Width() / childCount);
        } else if (axis == Axis::VERTICAL) {
            childIdeaSize.SetHeight(ideaSize.Height() / childCount);
        }
        childConstraint.selfIdealSize = OptionalSizeF(childIdeaSize);
    } else {
        if (axis == Axis::HORIZONTAL) {
            childConstraint.maxSize.SetWidth(Infinity<float>());
        } else if (axis == Axis::VERTICAL) {
            childConstraint.maxSize.SetHeight(Infinity<float>());
        }
    }
}

void TabBarLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto axis = GetAxis(layoutWrapper);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto idealSize = CreateIdealSize(constraint.value(), axis, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT));
    auto scale = layoutProperty->GetLayoutConstraint()->scaleProperty;
    auto defaultSize = ConvertToPx(TAB_BAR_DEFAULT_SIZE, scale, 0.0).value_or(0);
    if (!constraint->selfIdealSize.Width().has_value() && axis == Axis::VERTICAL) {
        idealSize.SetWidth(defaultSize);
    }
    if (!constraint->selfIdealSize.Height().has_value() && axis == Axis::HORIZONTAL) {
        idealSize.SetHeight(defaultSize);
    }
    geometryNode->SetFrameSize(idealSize.ConvertToSizeT());

    // Create layout constraint of children .
    auto childCount = layoutWrapper->GetTotalChildCount();
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    UpdateChildConstraint(childLayoutConstraint, layoutProperty, idealSize.ConvertToSizeT(), childCount, axis);
    LOGE("CCCC Measure idealSize: %{public}s, childConstraint: %{public}s", idealSize.ConvertToSizeT().ToString().c_str(), childLayoutConstraint.ToString().c_str());

    // Measure children.
    childrenMainSize_ = 0.0f;
    for (int32_t index = 0; index < childCount; ++index) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        if (!childWrapper) {
            LOGI("Child %{public}d is null.", index);
            return;
        }
        childWrapper->Measure(childLayoutConstraint);

        auto childGeometryNode = childWrapper->GetGeometryNode();
        if (childGeometryNode) {
            childrenMainSize_ += childGeometryNode->GetFrameSize().MainSize(axis);
        }
        LOGE("CCCC Measure childSize: %{public}s - %{public}d", childWrapper->GetGeometryNode()->GetFrameSize().ToString().c_str(), index);
    }
}

void TabBarLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    tabItemOffset_.clear();
    CHECK_NULL_VOID(layoutWrapper);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto childCount = layoutWrapper->GetTotalChildCount();
    auto axis = GetAxis(layoutWrapper);

    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();
    auto scrollableDistance = std::max(childrenMainSize_ - geometryNode->GetFrameSize().MainSize(axis), 0.0f);
    currentOffset_ = std::clamp(currentOffset_, -scrollableDistance, 0.0f);
    OffsetF childOffset = (axis == Axis::HORIZONTAL ?
        OffsetF(currentOffset_, 0.0f) : OffsetF(0.0f, currentOffset_));
    for (int32_t index = 0; index < childCount; ++index) {
        auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(childWrapper);
        auto childGeometryNode = childWrapper->GetGeometryNode();
        CHECK_NULL_VOID(childGeometryNode);
        childGeometryNode->SetFrameOffset(childOffset);
        childWrapper->Layout(parentOffset);
        tabItemOffset_.emplace_back(childOffset);

        LOGE("CCCC Layout childOffset: %{public}s, parentOffset: %{public}s, currentOffset: %{public}lf",
            childOffset.ToString().c_str(), parentOffset.ToString().c_str(), currentOffset_);

        if (axis == Axis::HORIZONTAL) {
            childOffset += OffsetF(childGeometryNode->GetFrameSize().Width(), 0.0f);
        } else {
            childOffset += OffsetF(0.0f, childGeometryNode->GetFrameSize().Height());
        }
    }
    tabItemOffset_.emplace_back(childOffset);
}

Axis TabBarLayoutAlgorithm::GetAxis(LayoutWrapper* layoutWrapper) const
{
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, Axis::HORIZONTAL);
    return layoutProperty->GetAxis().value_or(Axis::HORIZONTAL);
}

} // namespace OHOS::Ace::NG
