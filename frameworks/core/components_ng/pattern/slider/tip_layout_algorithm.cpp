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

#include "core/components_ng/pattern/slider/tip_layout_algorithm.h"

#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/slider/tip_layout_property.h"
namespace OHOS::Ace::NG {
namespace {
constexpr float HALF = 0.5;
constexpr Dimension ARROW_WIDTH = 32.0_vp;
constexpr Dimension ARROW_HEIGHT = 8.0_vp;
} // namespace

void TipLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<TipLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    SizeF childSize = { 0, 0 };
    if (childWrapper) {
        childWrapper->Measure(childLayoutConstraint);
        childSize = childWrapper->GetGeometryNode()->GetFrameSize();
    }
    auto padding = static_cast<float>(layoutProperty->GetPadding().value_or(0.0_vp).ConvertToPx());
    float frameSizeHeight = childSize.Height() + padding + padding;
    float frameSizeWidth = childSize.Width();
    if (layoutProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL) {
        frameSizeWidth = std::max(static_cast<float>(ARROW_WIDTH.ConvertToPx()), frameSizeWidth);
        geometryNode->SetFrameSize(
            { frameSizeWidth + frameSizeHeight, frameSizeHeight + static_cast<float>(ARROW_HEIGHT.ConvertToPx()) });
    } else {
        frameSizeHeight = std::max(static_cast<float>(ARROW_WIDTH.ConvertToPx()), frameSizeHeight);
        geometryNode->SetFrameSize(
            { frameSizeWidth + static_cast<float>(ARROW_HEIGHT.ConvertToPx()), frameSizeHeight + frameSizeWidth });
    }
}

void TipLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<TipLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    auto padding = static_cast<float>(layoutProperty->GetPadding().value_or(0.0_vp).ConvertToPx());
    auto childWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(childWrapper);
    auto childSize = childWrapper->GetGeometryNode()->GetFrameSize();
    OffsetF childOffset = { 0, 0 };
    if (layoutProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL) {
        childOffset.SetX((frameSize.Width() - childSize.Width()) * HALF);
        childOffset.SetY(padding);
    } else {
        childOffset.SetY((frameSize.Height() - childSize.Height()) * HALF);
    }
    childWrapper->GetGeometryNode()->SetMarginFrameOffset(childOffset);
}
} // namespace OHOS::Ace::NG
