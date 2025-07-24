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

#include "core/components_ng/pattern/menu/menu_model_static.h"

#include "core/components_ng/base/view_abstract.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> MenuModelStatic::CreateFrameNode(int32_t nodeId)
{
    ACE_LAYOUT_SCOPED_TRACE("MenuModelStatic::CreateFrameNode [nodeId = %d]", nodeId);
    const std::function<RefPtr<Pattern>(void)>& patternCreator =
        []() { return AceType::MakeRefPtr<InnerMenuPattern>(-1, V2::MENU_ETS_TAG, MenuType::MULTI_MENU); };
    return FrameNode::GetOrCreateFrameNode(V2::MENU_ETS_TAG, nodeId, patternCreator);
}

void MenuModelStatic::SetExpandingMode(FrameNode* frameNode, const std::optional<SubMenuExpandingMode>& expandingMode)
{
    CHECK_NULL_VOID(frameNode);
    if (expandingMode.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ExpandingMode, expandingMode.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ExpandingMode, frameNode);
    }
}

void MenuModelStatic::SetItemDivider(FrameNode* frameNode, const std::optional<V2::ItemDivider>& divider,
    const std::optional<DividerMode>& mode)
{
    CHECK_NULL_VOID(frameNode);
    if (divider.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemDivider, divider.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemDivider, frameNode);
    }
    if (mode.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemDividerMode, mode.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemDividerMode, frameNode);
    }
}

void MenuModelStatic::SetItemGroupDivider(FrameNode* frameNode, const std::optional<V2::ItemDivider>& divider,
    const std::optional<DividerMode>& mode)
{
    CHECK_NULL_VOID(frameNode);
    if (divider.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemGroupDivider, divider.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemGroupDivider, frameNode);
    }
    if (mode.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemDividerMode, mode.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemDividerMode, frameNode);
    }
}

void MenuModelStatic::SetFontColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    CHECK_NULL_VOID(frameNode);
    if (color.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontColor, color.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontColor, frameNode);
    }
}

void MenuModelStatic::SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& fontSize)
{
    CHECK_NULL_VOID(frameNode);
    if (fontSize.has_value() && fontSize.value().IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontSize, fontSize.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontSize, frameNode);
    }
}

void MenuModelStatic::SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& weight)
{
    CHECK_NULL_VOID(frameNode);
    if (weight.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontWeight, weight.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontWeight, frameNode);
    }
}

void MenuModelStatic::SetFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& style)
{
    CHECK_NULL_VOID(frameNode);
    if (style.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItalicFontStyle, style.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItalicFontStyle, frameNode);
    }
}

void MenuModelStatic::SetFontFamily(FrameNode* frameNode,
    const std::optional<std::vector<std::string>>& families)
{
    CHECK_NULL_VOID(frameNode);
    if (families.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontFamily, families.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontFamily, frameNode);
    }
}

void MenuModelStatic::SetBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& radius)
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

void MenuModelStatic::ResetBorderRadius(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(MenuLayoutProperty, BorderRadius, PROPERTY_UPDATE_MEASURE, frameNode);
}

void MenuModelStatic::SetBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& radiusTopLeft,
    const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
    const std::optional<Dimension>& radiusBottomRight)
{
    CHECK_NULL_VOID(frameNode);
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = radiusTopLeft;
    borderRadius.radiusTopRight = radiusTopRight;
    borderRadius.radiusBottomLeft = radiusBottomLeft;
    borderRadius.radiusBottomRight = radiusBottomRight;
    borderRadius.multiValued = true;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, BorderRadius, borderRadius, frameNode);
}

void MenuModelStatic::SetWidth(FrameNode* frameNode, const Dimension& width)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, MenuWidth, width, frameNode);
    ViewAbstract::SetWidth(frameNode, NG::CalcLength(width));
}

} // namespace OHOS::Ace::NG
