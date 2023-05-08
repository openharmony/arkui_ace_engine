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

void BarItemLayoutAlgorithm::MeasureIcon(FrameNode* frameNode, const RefPtr<BarItemNode>& hostNode,
    const RefPtr<LayoutProperty>& barItemLayoutProperty)
{
    auto iconNode = hostNode->GetIconNode();
    CHECK_NULL_VOID(iconNode);
    auto index = hostNode->GetChildIndexById(iconNode->GetId());
    auto icon = frameNode->GetFrameNodeByIndex((index));
    CHECK_NULL_VOID(icon);
    auto constraint = barItemLayoutProperty->CreateChildConstraint();

    constraint.selfIdealSize =
        OptionalSizeF(static_cast<float>(iconSize_.ConvertToPx()), static_cast<float>(iconSize_.ConvertToPx()));
    icon->Measure(constraint);
}

void BarItemLayoutAlgorithm::MeasureText(FrameNode* frameNode, const RefPtr<BarItemNode>& hostNode,
    const RefPtr<LayoutProperty>& barItemLayoutProperty)
{
    auto textNode = hostNode->GetTextNode();
    CHECK_NULL_VOID(textNode);
    auto index = hostNode->GetChildIndexById(textNode->GetId());
    auto text = frameNode->GetFrameNodeByIndex((index));
    CHECK_NULL_VOID(text);
    auto constraint = barItemLayoutProperty->CreateChildConstraint();
    text->Measure(constraint);
}

float BarItemLayoutAlgorithm::LayoutIcon(FrameNode* frameNode, const RefPtr<BarItemNode>& hostNode,
    const RefPtr<LayoutProperty>& barItemLayoutProperty, float textHeight)
{
    auto iconNode = hostNode->GetIconNode();
    CHECK_NULL_RETURN(iconNode, 0.0f);
    auto index = hostNode->GetChildIndexById(iconNode->GetId());
    auto icon = frameNode->GetFrameNodeByIndex((index));
    CHECK_NULL_RETURN(icon, 0.0f);
    auto geometryNode = icon->GetGeometryNode();

    auto offset = OffsetF(0.0f, 0.0f);
    geometryNode->SetMarginFrameOffset(offset);
    icon->Layout();
    return 0.0f;
}

void BarItemLayoutAlgorithm::LayoutText(FrameNode* frameNode, const RefPtr<BarItemNode>& hostNode,
    const RefPtr<LayoutProperty>& barItemLayoutProperty, float iconOffsetY)
{
    auto textNode = hostNode->GetTextNode();
    CHECK_NULL_VOID(textNode);
    auto index = hostNode->GetChildIndexById(textNode->GetId());
    auto text = frameNode->GetFrameNodeByIndex((index));
    CHECK_NULL_VOID(text);
    auto geometryNode = text->GetGeometryNode();
    auto textOffsetY = iconSize_ + TEXT_TOP_PADDING;
    auto offset = OffsetF(0.0f, iconOffsetY + static_cast<float>(textOffsetY.ConvertToPx()));
    geometryNode->SetMarginFrameOffset(offset);
    text->Layout();
}

void BarItemLayoutAlgorithm::Measure(FrameNode* frameNode)
{
    auto hostNode = AceType::DynamicCast<BarItemNode>(Claim(frameNode));
    CHECK_NULL_VOID(hostNode);
    auto barItemLayoutProperty = AceType::DynamicCast<LayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(barItemLayoutProperty);
    const auto& constraint = barItemLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);

    // get parameters from theme
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    iconSize_ = theme->GetMenuIconSize();
    auto size = SizeF(static_cast<float>(iconSize_.ConvertToPx()), static_cast<float>(iconSize_.ConvertToPx()));
    MeasureIcon(frameNode, hostNode, barItemLayoutProperty);
    MeasureText(frameNode, hostNode, barItemLayoutProperty);
    frameNode->GetGeometryNode()->SetFrameSize(size);
}

void BarItemLayoutAlgorithm::Layout(FrameNode* frameNode)
{
    auto hostNode = AceType::DynamicCast<BarItemNode>(Claim(frameNode));
    CHECK_NULL_VOID(hostNode);
    auto barItemLayoutProperty = AceType::DynamicCast<LayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(barItemLayoutProperty);

    float textHeight = 0.0f;
    auto textNode = hostNode->GetTextNode();
    if (textNode) {
        auto index = hostNode->GetChildIndexById(textNode->GetId());
        auto text = frameNode->GetFrameNodeByIndex((index));
        CHECK_NULL_VOID(text);
        auto geometryNode = text->GetGeometryNode();
        textHeight = geometryNode->GetFrameSize().Height();
    }

    float iconOffsetY = LayoutIcon(frameNode, hostNode, barItemLayoutProperty, textHeight);
    LayoutText(frameNode, hostNode, barItemLayoutProperty, iconOffsetY);
}

} // namespace OHOS::Ace::NG
