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

#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_layout_algorithm.h"

#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"

namespace OHOS::Ace::NG {
void CheckLayoutConstraint(LayoutConstraintF& constraint, const RefPtr<FrameNode>& menuWrapper)
{
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    menuWrapperPattern->SetChildLayoutConstraint(constraint);

    CHECK_NULL_VOID(menuWrapperPattern->GetIsFirstShow());
    auto pipeline = menuWrapper->GetContextRefPtr();
    auto currentId = pipeline ? pipeline->GetInstanceId() : Container::CurrentId();
    auto subWindow = SubwindowManager::GetInstance()->GetSubwindow(currentId);
    CHECK_NULL_VOID(subWindow);
    auto subwindowRect = subWindow->GetRect();
    // after the size of subwindow is changed, flush layout before updating windowSize to root node will result in an
    // incorrect constraint, and the constraint needs to be updated to the size of subwindow
    // 1. first measure after new subWindow is created, the constraint is empty and maxSize is zero
    // 2. first measure after windowSize is changed, the constraint has not been updated and is old value
    if (subwindowRect.GetSize() != constraint.maxSize) {
        constraint.maxSize.SetSizeT(subwindowRect.GetSize());
        constraint.percentReference.SetSizeT(constraint.maxSize);
        TAG_LOGW(AceLogTag::ACE_MENU, "update menuWrapper childConstraint because constraint doesn't match windowSize");
    }

    menuWrapperPattern->SetChildLayoutConstraint(constraint);
}

// set wrapper to full screen size
void MenuWrapperLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto idealSize = CreateIdealSize(
        constraint.value(), Axis::FREE, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT), true);
    auto layoutWrapperGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(layoutWrapperGeometryNode);
    layoutWrapperGeometryNode->SetFrameSize(idealSize);

    auto layoutConstraint = layoutProperty->CreateChildConstraint();
    // first layout after created subwindow, constraint is zero
    CheckLayoutConstraint(layoutConstraint, layoutWrapper->GetHostNode());
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        if (child->CheckNeedForceMeasureAndLayout()) {
            child->Measure(layoutConstraint);
        }
    }
}

void MenuWrapperLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        if (child->CheckNeedForceMeasureAndLayout()) {
            child->Layout();
        }
    }
}

} // namespace OHOS::Ace::NG
