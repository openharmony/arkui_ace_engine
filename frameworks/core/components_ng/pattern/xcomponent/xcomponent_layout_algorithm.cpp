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

#include "base/utils/utils.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_layout_algorithm.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_utils.h"

namespace OHOS::Ace::NG {
std::optional<SizeF> XComponentLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = DynamicCast<XComponentLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, SizeF(0, 0));
    auto xcomponentType = layoutProperty->GetXComponentType().value_or(XComponentType::SURFACE);
    if (xcomponentType == XComponentType::COMPONENT) {
        return LayoutAlgorithm::MeasureContent(contentConstraint, layoutWrapper);
    }
    SizeF layoutSize = contentConstraint.maxSize;
    if (contentConstraint.selfIdealSize.IsValid()) {
        layoutSize = contentConstraint.selfIdealSize.ConvertToSizeT();
    }
    MeasureLayoutPolicySize(contentConstraint, layoutProperty, layoutSize);
    return layoutSize;
}

void XComponentLayoutAlgorithm::MeasureLayoutPolicySize(
    const LayoutConstraintF& contentConstraint, RefPtr<XComponentLayoutProperty> layoutProperty, SizeF& size)
{
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

void XComponentLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = DynamicCast<XComponentLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto xcomponentType = layoutProperty->GetXComponentType().value_or(XComponentType::SURFACE);
    if (xcomponentType == XComponentType::COMPONENT) {
        LinearLayoutUtils::Measure(layoutWrapper, true);
    } else {
        BoxLayoutAlgorithm::Measure(layoutWrapper);
    }
}

void XComponentLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = DynamicCast<XComponentLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto xcomponentType = layoutProperty->GetXComponentType().value_or(XComponentType::SURFACE);
    if (xcomponentType == XComponentType::COMPONENT) {
        LinearLayoutUtils::Layout(layoutWrapper, true, FlexAlign::CENTER, FlexAlign::FLEX_START);
        auto children = layoutWrapper->GetAllChildrenWithBuild();
        for (auto&& child : children) {
            child->Layout();
        }
    } else {
        BoxLayoutAlgorithm::Layout(layoutWrapper);
    }
}

} // namespace OHOS::Ace::NG
