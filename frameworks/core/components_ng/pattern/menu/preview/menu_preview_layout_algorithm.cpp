/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/menu/preview/menu_preview_layout_algorithm.h"

#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"

namespace OHOS::Ace::NG {
void MenuPreviewLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(layoutConstraint);
    }

    LinearLayoutAlgorithm::Measure(layoutWrapper);
}

void MenuPreviewLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto preview = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(preview);
    auto previewPattern = preview->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_VOID(previewPattern);
    auto menuWrapper = previewPattern->GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto menuNode = menuWrapperPattern->GetMenu();
    CHECK_NULL_VOID(menuNode);
    auto menuLayoutAlgorithmWrapper = menuNode->GetLayoutAlgorithm();
    CHECK_NULL_VOID(menuLayoutAlgorithmWrapper);
    auto menuLayoutAlgorithm = DynamicCast<MenuLayoutAlgorithm>(menuLayoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(menuLayoutAlgorithm);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    if (!menuPattern->HasLaid()) {
        menuLayoutAlgorithm->Measure(AceType::RawPtr(menuNode));
        menuLayoutAlgorithm->Layout(AceType::RawPtr(menuNode));
    }
    menuPattern->SetHasLaid(false);
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Layout();
    }
    LinearLayoutAlgorithm::Layout(layoutWrapper);
}
} // namespace OHOS::Ace::NG
