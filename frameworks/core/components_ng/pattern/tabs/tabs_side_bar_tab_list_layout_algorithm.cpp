/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/tabs/tabs_side_bar_tab_list_layout_algorithm.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void TabsSideBarTabListLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto constraint = layoutProperty->GetLayoutConstraint();
    auto size = CreateIdealSize(constraint.value(), Axis::VERTICAL, MeasureType::MATCH_PARENT, true);
    // Use CreatePaddingAndBorder(false) to exclude safeAreaPadding from frame size calculation.
    // Frame covers the full area including safeAreaPadding zone.
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder(false);
    MinusPaddingToSize(padding, size);
    geometryNode->SetFrameSize(size);

    // CreateChildConstraint() automatically subtracts safeAreaPadding from content constraint.
    // Scroll gets content area height (frame height - safeAreaPadding.top),
    // but with clipContent(SAFE_AREA) its paint extends into the safeAreaPadding zone.
    auto childConstraint = layoutProperty->CreateChildConstraint();
    // Set selfIdealSize so Scroll fills the content area (width & height),
    // otherwise Scroll only wraps its content and doesn't fill TabList when items are few.
    // size has already been reduced by padding via MinusPaddingToSize above,
    // so use it directly as the Scroll's ideal size.
    childConstraint.selfIdealSize.SetWidth(size.Width());
    childConstraint.selfIdealSize.SetHeight(size.Height());
    auto scrollWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(scrollWrapper);
    scrollWrapper->Measure(childConstraint);
}

void TabsSideBarTabListLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto scrollWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(scrollWrapper);
    auto geometry = scrollWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometry);
    // Scroll starts at content area offset (safeAreaPadding.top + regular padding.top).
    // With clipContent(SAFE_AREA), paint extends into the safeAreaPadding zone.
    const auto& padding = layoutProperty->CreatePaddingAndBorder(true);
    float offsetY = padding.top.value_or(0.0f);
    geometry->SetMarginFrameOffset(OffsetF(0.0f, offsetY));
    scrollWrapper->Layout();
}

} // namespace OHOS::Ace::NG
