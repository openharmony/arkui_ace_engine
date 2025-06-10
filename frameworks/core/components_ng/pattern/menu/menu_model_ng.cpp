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

#include "core/components_ng/pattern/menu/menu_model_ng.h"

#include "core/components_ng/base/view_abstract.h"

namespace OHOS::Ace::NG {

void MenuModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::MENU_ETS_TAG, nodeId);
    auto menuNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<InnerMenuPattern>(-1, V2::MENU_ETS_TAG, MenuType::MULTI_MENU); });
    CHECK_NULL_VOID(menuNode);
    ViewStackProcessor::GetInstance()->Push(menuNode);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        auto layoutProps = menuNode->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProps);
        // default min width
        layoutProps->UpdateCalcMinSize(CalcSize(CalcLength(MIN_MENU_WIDTH), std::nullopt));
    }
}

RefPtr<FrameNode> MenuModelNG::CreateMenu()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    auto menuNode = FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<InnerMenuPattern>(-1, V2::MENU_ETS_TAG, MenuType::MULTI_MENU); });
    CHECK_NULL_RETURN(menuNode, nullptr);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        auto layoutProps = menuNode->GetLayoutProperty();
        CHECK_NULL_RETURN(layoutProps, nullptr);
        layoutProps->UpdateCalcMinSize(CalcSize(CalcLength(MIN_MENU_WIDTH), std::nullopt));
    }
    return menuNode;
}

RefPtr<FrameNode> MenuModelNG::CreateFrameNode(int32_t nodeId)
{
    ACE_LAYOUT_SCOPED_TRACE("MenuModelNG::CreateFrameNode [nodeId = %d]", nodeId);
    const std::function<RefPtr<Pattern>(void)>& patternCreator =
        []() { return AceType::MakeRefPtr<InnerMenuPattern>(-1, V2::MENU_ETS_TAG, MenuType::MULTI_MENU); };
    return FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, nodeId, patternCreator);
}

void MenuModelNG::SetFontSize(const Dimension& fontSize)
{
    if (fontSize.IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(MenuLayoutProperty, FontSize, fontSize);
    } else {
        ACE_RESET_LAYOUT_PROPERTY(MenuLayoutProperty, FontSize);
    }
}

void MenuModelNG::SetFontWeight(FontWeight weight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuLayoutProperty, FontWeight, weight);
}

void MenuModelNG::SetFontStyle(Ace::FontStyle style)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuLayoutProperty, ItalicFontStyle, style);
}

void MenuModelNG::SetFontColor(const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(MenuLayoutProperty, FontColor, color.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY(MenuLayoutProperty, FontColor);
    }
}

void MenuModelNG::SetBorderRadius(const Dimension& radius)
{
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = radius;
    borderRadius.radiusTopRight = radius;
    borderRadius.radiusBottomLeft = radius;
    borderRadius.radiusBottomRight = radius;
    borderRadius.multiValued = true;
    ACE_UPDATE_LAYOUT_PROPERTY(MenuLayoutProperty, BorderRadius, borderRadius);
}

void MenuModelNG::ResetBorderRadius()
{
    ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(MenuLayoutProperty, BorderRadius, PROPERTY_UPDATE_MEASURE);
}

void MenuModelNG::SetBorderRadius(const std::optional<Dimension>& radiusTopLeft,
    const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
    const std::optional<Dimension>& radiusBottomRight)
{
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = radiusTopLeft;
    borderRadius.radiusTopRight = radiusTopRight;
    borderRadius.radiusBottomLeft = radiusBottomLeft;
    borderRadius.radiusBottomRight = radiusBottomRight;
    borderRadius.multiValued = true;
    ACE_UPDATE_LAYOUT_PROPERTY(MenuLayoutProperty, BorderRadius, borderRadius);
}

void MenuModelNG::SetWidth(const Dimension& width)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    MenuModelNG::SetWidth(frameNode, width);
}

void MenuModelNG::SetFontFamily(const std::vector<std::string>& families)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuLayoutProperty, FontFamily, families);
}

void MenuModelNG::ResetFontFamily()
{
    ACE_RESET_LAYOUT_PROPERTY_WITH_FLAG(MenuLayoutProperty, FontFamily, PROPERTY_UPDATE_MEASURE);
}

void MenuModelNG::SetExpandingMode(const SubMenuExpandingMode& expandingMode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuLayoutProperty, ExpandingMode, expandingMode);
}

void MenuModelNG::SetExpandingMode(FrameNode* frameNode, const std::optional<SubMenuExpandingMode>& expandingMode)
{
    CHECK_NULL_VOID(frameNode);
    if (expandingMode.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ExpandingMode, expandingMode.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ExpandingMode, frameNode);
    }
}

void MenuModelNG::SetExpandSymbol(const std::function<void(WeakPtr<NG::FrameNode>)>& expandSymbol)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto menuProperty = frameNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);
    menuProperty->SetExpandSymbol(expandSymbol);
}

void MenuModelNG::SetExpandSymbol(FrameNode* frameNode, const std::function<void(WeakPtr<NG::FrameNode>)>& expandSymbol)
{
    CHECK_NULL_VOID(frameNode);
    auto menuProperty = frameNode->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);
    menuProperty->SetExpandSymbol(expandSymbol);
}

void MenuModelNG::SetItemDivider(const V2::ItemDivider& divider, const DividerMode& mode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemDivider, divider);
    ACE_UPDATE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemDividerMode, mode);
}

void MenuModelNG::SetItemDivider(
    FrameNode* frameNode, const std::optional<V2::ItemDivider>& divider, const DividerMode& mode)
{
    CHECK_NULL_VOID(frameNode);
    if (divider.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemDivider, divider.value(), frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemDividerMode, mode, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemDivider, frameNode);
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemDividerMode, frameNode);
    }
}

void MenuModelNG::SetItemGroupDivider(const V2::ItemDivider& divider, const DividerMode& mode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemGroupDivider, divider);
    ACE_UPDATE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemGroupDividerMode, mode);
}

void MenuModelNG::SetItemGroupDivider(
    FrameNode* frameNode, const std::optional<V2::ItemDivider>& divider, const DividerMode& mode)
{
    CHECK_NULL_VOID(frameNode);
    if (divider.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemGroupDivider, divider.value(), frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemGroupDividerMode, mode, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemGroupDivider, frameNode);
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemGroupDividerMode, frameNode);
    }
}

void MenuModelNG::SetFontColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontColor, color.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontColor, frameNode);
    }
}

void MenuModelNG::SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& fontSize)
{
    CHECK_NULL_VOID(frameNode);
    if (fontSize.has_value() && fontSize.value().IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontSize, fontSize.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontSize, frameNode);
    }
}

void MenuModelNG::SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& weight)
{
    CHECK_NULL_VOID(frameNode);
    if (weight.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontWeight, weight.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontWeight, frameNode);
    }
}

void MenuModelNG::SetFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& style)
{
    CHECK_NULL_VOID(frameNode);
    if (style.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItalicFontStyle, style.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItalicFontStyle, frameNode);
    }
}

void MenuModelNG::SetFontFamily(FrameNode* frameNode,
    const std::optional<std::vector<std::string>>& families)
{
    CHECK_NULL_VOID(frameNode);
    if (families.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontFamily, families.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontFamily, frameNode);
    }
}

void MenuModelNG::SetBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& radius)
{
    CHECK_NULL_VOID(frameNode);
    if (radius.has_value()) {
        NG::BorderRadiusProperty borderRadius;
        borderRadius.radiusTopLeft = radius;
        borderRadius.radiusTopRight = radius;
        borderRadius.radiusBottomLeft = radius;
        borderRadius.radiusBottomRight = radius;
        borderRadius.multiValued = true;
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, BorderRadius, borderRadius, frameNode);
    } else {
        ResetBorderRadius(frameNode);
    }
}

void MenuModelNG::ResetBorderRadius(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(MenuLayoutProperty, BorderRadius, PROPERTY_UPDATE_MEASURE, frameNode);
}

void MenuModelNG::SetBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& radiusTopLeft,
    const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
    const std::optional<Dimension>& radiusBottomRight)
{
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = radiusTopLeft;
    borderRadius.radiusTopRight = radiusTopRight;
    borderRadius.radiusBottomLeft = radiusBottomLeft;
    borderRadius.radiusBottomRight = radiusBottomRight;
    borderRadius.multiValued = true;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, BorderRadius, borderRadius, frameNode);
}

void MenuModelNG::SetWidth(FrameNode* frameNode, const Dimension& width)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, MenuWidth, width, frameNode);
    ViewAbstract::SetWidth(frameNode, NG::CalcLength(width));
}

} // namespace OHOS::Ace::NG
