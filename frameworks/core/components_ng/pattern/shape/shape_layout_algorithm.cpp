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
    if (!host->IsAtomicNode()) {
        return std::nullopt;
    }
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, std::nullopt);
    auto measureType = layoutProperty->GetMeasureType(MeasureType::MATCH_CONTENT);
    OptionalSizeF contentSize;
    do {
        // Use idea size first if it is valid.
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

        // if width or height is matchParent
        auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
        if (layoutPolicy.has_value()) {
            if (layoutPolicy->IsWidthMatch()) {
                contentSize.SetWidth(contentConstraint.parentIdealSize.Width());
            }
            if (layoutPolicy->IsHeightMatch()) {
                contentSize.SetHeight(contentConstraint.parentIdealSize.Height());
            }
        }
    } while (false);
    return contentSize.ConvertToSizeT();
}
} // namespace OHOS::Ace::NG
