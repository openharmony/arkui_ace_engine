/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "frameworks/core/components_ng/pattern/shape/shape_layout_algorithm.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

std::optional<SizeF> ShapeLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, std::nullopt);
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, std::nullopt);
    auto measureType = layoutProperty->GetMeasureType(MeasureType::MATCH_CONTENT);
    OptionalSizeF contentSize;
    do {
        // Use idealSize first if it is valid.
        contentSize.UpdateSizeWithCheck(contentConstraint.selfIdealSize);
        if (contentSize.IsValid()) {
            break;
        }

        if (measureType == MeasureType::MATCH_PARENT) {
            contentSize.UpdateIllegalSizeWithCheck(contentConstraint.parentIdealSize);
            // use max is parent ideal size is invalid.
            contentSize.UpdateIllegalSizeWithCheck(contentConstraint.percentReference);
            break;
        }

        // wrap content case use min size default.
        contentSize.UpdateIllegalSizeWithCheck(contentConstraint.minSize);

        MeasureLayoutPolicySize(contentConstraint, layoutProperty, contentSize);
    } while (false);
    return contentSize.ConvertToSizeT();
}

void ShapeLayoutAlgorithm::MeasureLayoutPolicySize(
    const LayoutConstraintF& contentConstraint, const RefPtr<LayoutProperty> layoutProperty, OptionalSizeF& size)
{
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    CHECK_NULL_VOID(layoutPolicy.has_value());

    if (layoutPolicy->IsWidthMatch() && contentConstraint.parentIdealSize.Width().has_value()) {
        // if width is matchParent
        size.SetWidth(contentConstraint.parentIdealSize.Width());
    } else if (layoutPolicy->IsWidthAdaptive()) {
        // if width is wrapContent or fixAtIdealSize set width 0.0
        size.SetWidth(0.0);
    }

    if (layoutPolicy->IsHeightMatch() && contentConstraint.parentIdealSize.Height().has_value()) {
        // if height is matchParent
        size.SetHeight(contentConstraint.parentIdealSize.Height());
    } else if (layoutPolicy->IsHeightAdaptive()) {
        // if height is wrapContent or fixAtIdealSize set height 0.0
        size.SetHeight(0.0);
    }
}
} // namespace OHOS::Ace::NG
