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

#include "core/components_ng/pattern/arc_scroll_bar/arc_scroll_bar_layout_algorithm.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_layout_property.h"

namespace OHOS::Ace::NG {
namespace {

void UpdateIdealSize(const SizeF& childSize, const OptionalSizeF& parentSize, OptionalSizeF& idealSize)
{
    if (!idealSize.Width() && parentSize.Height().has_value()) {
        idealSize.SetWidth(parentSize.Width().value());
    }
    if (!idealSize.Height() && parentSize.Height().has_value()) {
        idealSize.SetHeight(parentSize.Height().value());
    }
}

} // namespace

void ArcScrollBarLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    auto constraint = layoutProperty->GetLayoutConstraint();
    auto idealSize = CreateIdealSize(constraint.value(), Axis::VERTICAL, MeasureType::MATCH_CONTENT);
    auto parentSize = CreateIdealSize(constraint.value(), Axis::VERTICAL, MeasureType::MATCH_PARENT);
    auto padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, idealSize);
    MinusPaddingToSize(padding, parentSize);

    auto size = layoutWrapper->GetGeometryNode()->GetMarginFrameSize();
    UpdateIdealSize(size, parentSize, idealSize);

    AddPaddingToSize(padding, idealSize);
    auto selfSize = idealSize.ConvertToSizeT();
    selfSize.Constrain(constraint->minSize, constraint->maxSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(selfSize);
}

void ArcScrollBarLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
}

} // namespace OHOS::Ace::NG
