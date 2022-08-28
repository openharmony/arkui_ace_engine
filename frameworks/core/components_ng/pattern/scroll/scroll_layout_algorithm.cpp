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

#include "core/components_ng/pattern/scroll/scroll_layout_algorithm.h"
#include <algorithm>

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {

void UpdateChildConstraint(Axis axis, const SizeF& selfIdealSize, LayoutConstraintF& contentConstraint)
{
    contentConstraint.parentIdealSize = OptionalSizeF(selfIdealSize);
    if (axis == Axis::VERTICAL) {
        contentConstraint.maxSize.SetHeight(Infinity<float>());
    } else {
        contentConstraint.maxSize.SetWidth(Infinity<float>());
    }
}

} // namespace

void ScrollLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    auto axis = layoutProperty->GetAxis().value_or(Axis::VERTICAL);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto idealSize = CreateIdealSize(constraint.value(), axis, layoutProperty->GetMeasureType(), true);
    if (GetMainAxisSize(idealSize, axis) == Infinity<float>()) {
        LOGE("the scroll is infinity, error");
        return;
    }

    // calculate child layout constraint.
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    UpdateChildConstraint(axis, idealSize, childLayoutConstraint);

    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    if (!childWrapper) {
        return;
    }
    {
        ACE_SCOPED_TRACE("ScrollLayoutAlgorithm::Measure child");
        childWrapper->Measure(childLayoutConstraint);
    }

    auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
    if (!constraint->selfIdealSize.Width().has_value()) {
        idealSize.SetWidth(childSize.Width());
    }
    if (!constraint->selfIdealSize.Height().has_value()) {
        idealSize.SetHeight(childSize.Height());
    }

    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(idealSize);
}

void ScrollLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<ScrollLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto axis = layoutProperty->GetAxis().value_or(Axis::VERTICAL);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto size = geometryNode->GetFrameSize();
    auto padding = layoutProperty->CreatePaddingPropertyF();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0.0f);
    auto top = padding.top.value_or(0.0f);
    auto paddingOffset = OffsetF(left, top);

    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();

    // layout child.
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(childWrapper);
    auto childGeometryNode = childWrapper->GetGeometryNode();
    CHECK_NULL_VOID(childGeometryNode);
    auto childSize = childGeometryNode->GetFrameSize();

    auto scrollableDistance = GetMainAxisSize(childSize, axis) - GetMainAxisSize(size, axis);
    currentOffset_ = std::clamp(currentOffset_, -scrollableDistance, 0.0f);
    auto currentOffset = axis == Axis::VERTICAL ? OffsetF(0.0f, currentOffset_) : OffsetF(currentOffset_, 0.0f);
    auto offset = paddingOffset + currentOffset;
    childGeometryNode->SetFrameOffset(offset);
    childWrapper->Layout(parentOffset);
}

} // namespace OHOS::Ace::NG
