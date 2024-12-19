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

#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {

void BarItemLayoutAlgorithm::MeasureIcon(LayoutWrapper* layoutWrapper, const RefPtr<BarItemNode>& hostNode,
    const RefPtr<LayoutProperty>& barItemLayoutProperty)
{
    auto iconNode = hostNode->GetIconNode();
    CHECK_NULL_VOID(iconNode);
    auto index = hostNode->GetChildIndexById(iconNode->GetId());
    auto iconWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(iconWrapper);
    auto constraint = barItemLayoutProperty->CreateChildConstraint();

    constraint.selfIdealSize =
        OptionalSizeF(static_cast<float>(iconSize_.ConvertToPx()), static_cast<float>(iconSize_.ConvertToPx()));
    iconWrapper->Measure(constraint);
}

void BarItemLayoutAlgorithm::MeasureToolbarItemText(LayoutWrapper* layoutWrapper, const RefPtr<BarItemNode>& hostNode,
    const RefPtr<LayoutProperty>& barItemLayoutProperty)
{
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    auto textNode = hostNode->GetTextNode();
    CHECK_NULL_VOID(textNode);
    auto index = hostNode->GetChildIndexById(textNode->GetId());
    auto textWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(textWrapper);
    auto constraint = barItemLayoutProperty->CreateChildConstraint();

    auto contentConstraint = textWrapper->GetLayoutProperty()->GetContentLayoutConstraint();
    textWrapper->Measure(contentConstraint);
    auto geometryNode = textWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto textWidth = geometryNode->GetContentSize().Width();
    auto textLayoutProperty = DynamicCast<TextLayoutProperty>(textWrapper->GetLayoutProperty());

    if (GreatOrEqual(textWidth, constraint.maxSize.Width())) {
        constraint.maxSize.SetWidth(textWidth);
    }
    auto barItemConstraint = barItemLayoutProperty->GetLayoutConstraint().value();
    auto textHeight = geometryNode->GetContentSize().Height();
    float barItemChildrenTotalHeight = textHeight + (theme->GetToolbarIconSize() + TEXT_TOP_PADDING).ConvertToPx();
    if (GreatOrEqual(barItemChildrenTotalHeight, constraint.maxSize.Height())) {
        constraint.maxSize.SetHeight(barItemChildrenTotalHeight);
    }

    if (GreatNotEqual(constraint.maxSize.Height(), barItemConstraint.maxSize.Height())) {
        barItemConstraint.maxSize.SetHeight(constraint.maxSize.Height());
        barItemLayoutProperty->UpdateLayoutConstraint(barItemConstraint);
    }

    textWrapper->Measure(constraint);
}

void BarItemLayoutAlgorithm::MeasureText(LayoutWrapper* layoutWrapper, const RefPtr<BarItemNode>& hostNode,
    const RefPtr<LayoutProperty>& barItemLayoutProperty)
{
    if (hostNode->IsBarItemUsedInToolbarConfiguration()) {
        MeasureToolbarItemText(layoutWrapper, hostNode, barItemLayoutProperty);
        return;
    }

    auto textNode = hostNode->GetTextNode();
    CHECK_NULL_VOID(textNode);
    auto index = hostNode->GetChildIndexById(textNode->GetId());
    auto textWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(textWrapper);
    auto constraint = barItemLayoutProperty->CreateChildConstraint();
    textWrapper->Measure(constraint);
}

float BarItemLayoutAlgorithm::LayoutIcon(LayoutWrapper* layoutWrapper, const RefPtr<BarItemNode>& hostNode,
    const RefPtr<LayoutProperty>& barItemLayoutProperty, float textHeight)
{
    auto iconNode = hostNode->GetIconNode();
    CHECK_NULL_RETURN(iconNode, 0.0f);
    auto index = hostNode->GetChildIndexById(iconNode->GetId());
    auto iconWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_RETURN(iconWrapper, 0.0f);
    auto geometryNode = iconWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, 0.0f);

    const auto& constraint = barItemLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_RETURN(constraint, 0.0f);
    auto offsetX = (constraint->maxSize.Width() - iconSize_.ConvertToPx()) / 2;

    if (!hostNode->IsBarItemUsedInToolbarConfiguration()) {
        offsetX = 0.0f;
    }

    auto offset = OffsetF(offsetX, 0.0f);
    geometryNode->SetMarginFrameOffset(offset);
    iconWrapper->Layout();
    return 0.0f;
}

void BarItemLayoutAlgorithm::LayoutText(LayoutWrapper* layoutWrapper, const RefPtr<BarItemNode>& hostNode,
    const RefPtr<LayoutProperty>& barItemLayoutProperty, float iconOffsetY)
{
    auto textNode = hostNode->GetTextNode();
    CHECK_NULL_VOID(textNode);
    auto index = hostNode->GetChildIndexById(textNode->GetId());
    auto textWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(textWrapper);
    auto geometryNode = textWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto textOffsetY = iconSize_ + TEXT_TOP_PADDING;

    const auto& constraint = barItemLayoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(constraint);
    auto textWidth = geometryNode->GetFrameSize().Width();
    auto offsetX = (constraint->maxSize.Width() - textWidth) / 2;

    if (!hostNode->IsBarItemUsedInToolbarConfiguration()) {
        offsetX = 0.0f;
    }
    auto offset = OffsetF(offsetX, iconOffsetY + static_cast<float>(textOffsetY.ConvertToPx()));
    geometryNode->SetMarginFrameOffset(offset);
    textWrapper->Layout();
}

void BarItemLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<BarItemNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto barItemLayoutProperty = AceType::DynamicCast<LayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(barItemLayoutProperty);
    bool isUsedInToolbarConfiguratuon = hostNode->IsBarItemUsedInToolbarConfiguration();

    // get parameters from theme
    auto theme = NavigationGetTheme();
    CHECK_NULL_VOID(theme);
    iconSize_ = isUsedInToolbarConfiguratuon ? theme->GetToolbarIconSize() : theme->GetMenuIconSize();
    auto size = SizeF(static_cast<float>(iconSize_.ConvertToPx()), static_cast<float>(iconSize_.ConvertToPx()));
    MeasureIcon(layoutWrapper, hostNode, barItemLayoutProperty);
    MeasureText(layoutWrapper, hostNode, barItemLayoutProperty);

    if (isUsedInToolbarConfiguratuon) {
        const auto& constraint = barItemLayoutProperty->GetLayoutConstraint();
        CHECK_NULL_VOID(constraint);
        size = constraint->maxSize;
    }
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetFrameSize(size);
}

void BarItemLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<BarItemNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto barItemLayoutProperty = AceType::DynamicCast<LayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(barItemLayoutProperty);

    float textHeight = 0.0f;
    auto textNode = hostNode->GetTextNode();
    if (textNode) {
        auto index = hostNode->GetChildIndexById(textNode->GetId());
        auto textWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
        CHECK_NULL_VOID(textWrapper);
        auto geometryNode = textWrapper->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        textHeight = geometryNode->GetFrameSize().Height();
    }

    float iconOffsetY = LayoutIcon(layoutWrapper, hostNode, barItemLayoutProperty, textHeight);
    LayoutText(layoutWrapper, hostNode, barItemLayoutProperty, iconOffsetY);
}

} // namespace OHOS::Ace::NG
