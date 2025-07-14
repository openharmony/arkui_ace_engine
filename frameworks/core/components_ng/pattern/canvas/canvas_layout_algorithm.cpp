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

#include "core/components_ng/pattern/canvas/canvas_layout_algorithm.h"

#include "core/components_ng/pattern/canvas/canvas_pattern.h"

namespace OHOS::Ace::NG {
std::optional<SizeF> CanvasLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    SizeF canvasSize = contentConstraint.maxSize;
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, canvasSize);
    auto pattern = host->GetPattern<CanvasPattern>();
    CHECK_NULL_RETURN(pattern, canvasSize);
    if (contentConstraint.selfIdealSize.IsValid()) {
        canvasSize = contentConstraint.selfIdealSize.ConvertToSizeT();
    }
    MeasureLayoutPolicySize(contentConstraint, layoutWrapper, canvasSize);
    pattern->SetCanvasSize(canvasSize);
    return canvasSize;
}

void CanvasLayoutAlgorithm::MeasureLayoutPolicySize(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper, SizeF& size)
{
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_VOID(layoutPolicy.has_value());

    if (layoutPolicy->IsWidthMatch() && contentConstraint.parentIdealSize.Width().has_value()) {
        // if width is matchParent
        size.SetWidth(contentConstraint.parentIdealSize.Width().value());
    } else if (layoutPolicy->IsWidthAdaptive()) {
        // if width is wrapContent or fixAtIdealSize set width 0.0
        size.SetWidth(0.0);
    }

    if (layoutPolicy->IsHeightMatch() && contentConstraint.parentIdealSize.Height().has_value()) {
        // if height is matchParent
        size.SetHeight(contentConstraint.parentIdealSize.Height().value());
    } else if (layoutPolicy->IsHeightAdaptive()) {
        // if height is wrapContent or fixAtIdealSize set height 0.0
        size.SetHeight(0.0);
    }
}

void CanvasLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    BoxLayoutAlgorithm::Layout(layoutWrapper);
}
} // namespace OHOS::Ace::NG
