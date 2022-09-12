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

#include "core/components_ng/pattern/navigation/bar_item_layout_algorithm.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void BarItemLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<BarItemNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto barItemLayoutProperty = AceType::DynamicCast<LayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(barItemLayoutProperty);
    const auto& constraint = barItemLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    CHECK_NULL_VOID(barItemLayoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    geometryNode->SetFrameSize(SizeF(ICON_SIZE + ICON_PADDING * 2, BAR_ITEM_HEIGHT));
    auto childConstraint = barItemLayoutProperty->CreateChildConstraint();
    if (hostNode->HasIconIndex()) {
        auto iconWrapper = layoutWrapper->GetOrCreateChildByIndex(hostNode->GetIconIndexValue());
        auto iconSize = SizeF(ICON_SIZE, ICON_SIZE);
        auto imageLayoutProperty = iconWrapper->GetLayoutProperty();
        childConstraint.UpdateSelfIdealSizeWithCheck(OptionalSizeF(ICON_SIZE, ICON_SIZE));
        iconWrapper->Measure(childConstraint);
    }
    if (hostNode->HasTextIndex()) {
        auto textWrapper = layoutWrapper->GetOrCreateChildByIndex(hostNode->GetTextIndexValue());
        auto textGeometryNode = textWrapper->GetGeometryNode();
        auto textSize = SizeF(ICON_SIZE, BAR_ITEM_HEIGHT - ICON_SIZE - TEXT_TOP_PADDING);
        textGeometryNode->SetFrameSize(textSize);
        childConstraint.maxSize.SetSizeT(textSize);
        textWrapper->Measure(childConstraint);
    }
}

void BarItemLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<BarItemNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto barItemLayoutProperty = AceType::DynamicCast<LayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(barItemLayoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    auto parentOffset =
        layoutWrapper->GetGeometryNode()->GetParentGlobalOffset() + layoutWrapper->GetGeometryNode()->GetFrameOffset();
    if (hostNode->HasIconIndex()) {
        auto iconWrapper = layoutWrapper->GetOrCreateChildByIndex(hostNode->GetIconIndexValue());
        auto iconGeometryNode = iconWrapper->GetGeometryNode();
        iconGeometryNode->SetFrameOffset(OffsetF(ICON_PADDING, 0.0f));
        iconWrapper->Layout(parentOffset);
    }
    if (hostNode->HasTextIndex()) {
        auto textWrapper = layoutWrapper->GetOrCreateChildByIndex(hostNode->GetTextIndexValue());
        auto textGeometryNode = textWrapper->GetGeometryNode();
        auto textOffsetX = ICON_SIZE + ICON_PADDING * 2 - textGeometryNode->GetContentSize().Width();
        textGeometryNode->SetFrameOffset(OffsetF(textOffsetX / 2.0f, ICON_SIZE + TEXT_TOP_PADDING));
        textWrapper->Layout(parentOffset);
    }
}

} // namespace OHOS::Ace::NG
