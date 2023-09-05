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

#include "base/utils/utils.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/declaration/common/declaration_constants.h"
#include "core/components_ng/pattern/menu/menu_paint_property.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
void MenuPreviewLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    PaddingProperty padding;
    padding.left = CalcLength(PREVIEW_INNER_SECURITY);
    padding.right = CalcLength(PREVIEW_INNER_SECURITY);
    padding.top = CalcLength(PREVIEW_INNER_SECURITY);
    padding.bottom = CalcLength(PREVIEW_INNER_SECURITY);
    layoutProperty->UpdatePadding(padding);
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(layoutConstraint);
    }
    LinearLayoutAlgorithm::Measure(layoutWrapper);
}

void MenuPreviewLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Layout();
    }
    LinearLayoutAlgorithm::Layout(layoutWrapper);
}
} // namespace OHOS::Ace::NG
