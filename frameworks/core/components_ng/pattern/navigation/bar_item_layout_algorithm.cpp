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
namespace {
void MeasureIcon(LayoutWrapper* layoutWrapper, const RefPtr<BarItemNode>& hostNode,
    const RefPtr<LayoutProperty>& barItemLayoutProperty)
{
    auto iconNode = hostNode->GetIconNode();
    CHECK_NULL_VOID(iconNode);
    auto index = hostNode->GetChildIndexById(iconNode->GetId());
    auto iconWrapper = layoutWrapper->GetOrCreateChildByIndex((index));
    CHECK_NULL_VOID(iconWrapper);
    auto constraint = barItemLayoutProperty->CreateChildConstraint();
    constraint.selfIdealSize = OptionalSizeF(
        static_cast<float>(ICON_SIZE.ConvertToPx()), static_cast<float>(ICON_SIZE.ConvertToPx()));
    iconWrapper->Measure(constraint);
}

void MeasureText(LayoutWrapper* layoutWrapper, const RefPtr<BarItemNode>& hostNode,
    const RefPtr<LayoutProperty>& barItemLayoutProperty)
{
    auto textNode = hostNode->GetTextNode();
    CHECK_NULL_VOID(textNode);
    auto index = hostNode->GetChildIndexById(textNode->GetId());
    auto textWrapper = layoutWrapper->GetOrCreateChildByIndex((index));
    CHECK_NULL_VOID(textWrapper);
    auto constraint = barItemLayoutProperty->CreateChildConstraint();
    auto textHeight = TOOLBAR_HEIGHT - ICON_SIZE - TEXT_TOP_PADDING;
    constraint.selfIdealSize = OptionalSizeF(
        static_cast<float>(ICON_SIZE.ConvertToPx()), static_cast<float>(textHeight.ConvertToPx()));
    textWrapper->Measure(constraint);
}

float LayoutIcon(LayoutWrapper* layoutWrapper, const RefPtr<BarItemNode>& hostNode,
    const RefPtr<LayoutProperty>& barItemLayoutProperty, float barItemHeight)
{
    auto iconNode = hostNode->GetIconNode();
    CHECK_NULL_RETURN(iconNode, 0.0f);
    auto index = hostNode->GetChildIndexById(iconNode->GetId());
    auto iconWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(iconWrapper, 0.0f);
    auto geometryNode = iconWrapper->GetGeometryNode();

    if (!hostNode->GetTextNode()) {
        auto iconOffsetY = (MENU_HEIGHT - ICON_SIZE) / 2;
        auto offset = OffsetF(0.0f, static_cast<float>(iconOffsetY.ConvertToPx()));
        geometryNode->SetMarginFrameOffset(offset);
        iconWrapper->Layout();
        return static_cast<float>(iconOffsetY.ConvertToPx());
    }

    auto offset = OffsetF(0.0f, barItemHeight);
    geometryNode->SetMarginFrameOffset(offset);
    iconWrapper->Layout();
    return barItemHeight;
}

void LayoutText(LayoutWrapper* layoutWrapper, const RefPtr<BarItemNode>& hostNode,
    const RefPtr<LayoutProperty>& barItemLayoutProperty, float iconOffsetY)
{
    auto textNode = hostNode->GetTextNode();
    CHECK_NULL_VOID(textNode);
    auto index = hostNode->GetChildIndexById(textNode->GetId());
    auto textWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(textWrapper);
    auto geometryNode = textWrapper->GetGeometryNode();
    auto textOffsetY = ICON_SIZE + TEXT_TOP_PADDING;
    auto offset = OffsetF(0.0f, iconOffsetY + static_cast<float>(textOffsetY.ConvertToPx()));
    geometryNode->SetMarginFrameOffset(offset);
    textWrapper->Layout();
}

} // namespace

void BarItemLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<BarItemNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto barItemLayoutProperty = AceType::DynamicCast<LayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(barItemLayoutProperty);
    const auto& constraint = barItemLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto width = HORIZONTAL_MARGIN / 2 + ICON_SIZE;
    auto size = SizeF(static_cast<float>(width.ConvertToPx()), static_cast<float>(MENU_HEIGHT.ConvertToPx()));
    MeasureIcon(layoutWrapper, hostNode, barItemLayoutProperty);
    MeasureText(layoutWrapper, hostNode, barItemLayoutProperty);
    layoutWrapper->GetGeometryNode()->SetFrameSize(size);
}

void BarItemLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<BarItemNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto barItemLayoutProperty = AceType::DynamicCast<LayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(barItemLayoutProperty);
    float barItemHeight = layoutWrapper->GetGeometryNode()->GetFrameOffset().GetY();
    float iconOffsetY = LayoutIcon(layoutWrapper, hostNode, barItemLayoutProperty, barItemHeight);
    LayoutText(layoutWrapper, hostNode, barItemLayoutProperty, iconOffsetY);
}

} // namespace OHOS::Ace::NG
