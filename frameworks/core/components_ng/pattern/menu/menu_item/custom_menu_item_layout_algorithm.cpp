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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/menu/menu_item/custom_menu_item_layout_algorithm.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
void CustomMenuItemLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutConstraint = layoutProperty->CreateChildConstraint();
    auto layoutPolicyProperty = layoutProperty->GetLayoutPolicyProperty();
    if (layoutPolicyProperty.has_value()) {
        auto& layoutPolicy = layoutPolicyProperty.value();
        if (layoutPolicy.IsWidthFix()) {
            layoutConstraint.maxSize.SetWidth(std::numeric_limits<float>::infinity());
        }
        if (layoutPolicy.IsHeightFix()) {
            layoutConstraint.maxSize.SetHeight(std::numeric_limits<float>::infinity());
        }
    }
    bool isEnableChildrenMatchParent = pattern->IsEnableChildrenMatchParent();
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        auto childLayoutProperty = child->GetLayoutProperty();
        CHECK_NULL_CONTINUE(childLayoutProperty);
        auto childLayoutPolicyProperty = childLayoutProperty->GetLayoutPolicyProperty();
        if (isEnableChildrenMatchParent && childLayoutPolicyProperty.has_value()) {
            auto& childLayoutPolicy = childLayoutPolicyProperty.value();
            if (childLayoutPolicy.IsMatch()) {
                layoutPolicyChildren_.emplace_back(child);
                continue;
            }
        }
        child->Measure(layoutConstraint);
    }
    PerformMeasureSelf(layoutWrapper);
    auto frameGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(frameGeometryNode);
    if (isEnableChildrenMatchParent) {
        auto frameSize = frameGeometryNode->GetFrameSize();
        MeasureAdaptiveLayoutChildren(layoutWrapper, frameSize);
    }
}
} // namespace OHOS::Ace::NG