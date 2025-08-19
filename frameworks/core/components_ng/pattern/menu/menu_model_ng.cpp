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

#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/view_abstract.h"

namespace OHOS::Ace::NG {
void MenuModelNG::CreateWithColorResourceObj(
    const RefPtr<ResourceObject>& resObj, const MenuColorType menuColorType)
{
    CHECK_NULL_VOID(resObj);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithColorResourceObj(frameNode, resObj, menuColorType);
}

void MenuModelNG::CreateWithColorResourceObj(
    FrameNode* frameNode, const RefPtr<ResourceObject>& resObj, const MenuColorType menuColorType)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "Menu" + ColorTypeToString(menuColorType);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [pattern, key, menuColorType, weak = AceType::WeakClaim(frameNode)](
                            const RefPtr<ResourceObject>& resObj) {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        std::string colorStr = pattern->GetResCacheMapByKey(key);
        Color color;
        if (colorStr.empty()) {
            if (ResourceParseUtils::ParseResColor(resObj, color)) {
                pattern->AddResCache(key, color.ToString());
            }
        } else {
            color = Color::ColorFromString(colorStr);
        }
        SetMenuColorValue(menuColorType, node, color);
        node->MarkModifyDone();
        node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void MenuModelNG::SetMenuColorValue(
    MenuColorType type, RefPtr<NG::FrameNode>& node, Color& color)
{
    auto layoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    switch (type) {
        case MenuColorType::FONT_COLOR:
            MenuModelNG::SetFontColor(&(*node), color);
            break;
        case MenuColorType::DIVIDER_COLOR: {
            auto itemDivider = layoutProperty->GetItemDividerValue();
            itemDivider.color = color;
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemDivider, itemDivider, &(*node));
            break;
        }
        case MenuColorType::GROUP_DIVIDER_COLOR: {
            auto itemGroupDivider = layoutProperty->GetItemGroupDividerValue();
            itemGroupDivider.color = color;
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemGroupDivider, itemGroupDivider, &(*node));
            break;
        }
        default:
            break;
    }
}
void MenuModelNG::CreateWithDimensionResourceObj(
    const RefPtr<ResourceObject>& resObj, const MenuDimensionType menuDimensionType)
{
    CHECK_NULL_VOID(resObj);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithDimensionResourceObj(frameNode, resObj, menuDimensionType);
}
void MenuModelNG::CreateWithDimensionResourceObj(
    FrameNode* frameNode, const RefPtr<ResourceObject>& resObj, const MenuDimensionType menuDimensionType)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "Menu" + DimensionTypeToString(menuDimensionType);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [pattern, key, menuDimensionType, weak = AceType::WeakClaim(frameNode)](
                            const RefPtr<ResourceObject>& resObj) {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        std::string cacheValue = pattern->GetResCacheMapByKey(key);
        CalcDimension result;
        if (cacheValue.empty()) {
            if (menuDimensionType == MenuDimensionType::FONT_SIZE) {
                CHECK_NE_VOID(ResourceParseUtils::ParseResDimensionFpNG(resObj, result, false), true);
            } else {
                CHECK_NE_VOID(ResourceParseUtils::ParseResDimensionVpNG(resObj, result, false), true);
            }
            pattern->AddResCache(key, result.ToString());
        } else {
            result = CalcDimension::FromString(cacheValue);
        }
        SetMenuDimensionValue(menuDimensionType, node, result);
        node->MarkModifyDone();
        node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void MenuModelNG::SetMenuDimensionValue(
    MenuDimensionType type, RefPtr<NG::FrameNode>& node, CalcDimension& result)
{
    auto layoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    switch (type) {
        case MenuDimensionType::WIDTH:
            MenuModelNG::SetWidth(&(*node), result);
            break;
        case MenuDimensionType::FONT_SIZE: {
            if (result.Unit() == DimensionUnit::PERCENT) {
                result = CalcDimension();
            }
            MenuModelNG::SetFontSize(&(*node), result);
            break;
        }
        case MenuDimensionType::BORDER_RADIUS:
            SetBorderRadius(&(*node), result);
            break;
        default:
            break;
    }
}

void MenuModelNG::CreateWithFontFamilyResourceObj(const RefPtr<ResourceObject>& resObj, MenuFamilyType type)
{
    CHECK_NULL_VOID(resObj);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithFontFamilyResourceObj(frameNode, resObj, type);
}

void MenuModelNG::CreateWithFontFamilyResourceObj(
    FrameNode* frameNode, const RefPtr<ResourceObject>& resObj, MenuFamilyType type)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "Menu" + FamilyTypeToString(type);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [type, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        std::vector<std::string> fontFamilies;
        CHECK_NE_VOID(ResourceParseUtils::ParseResFontFamilies(resObj, fontFamilies), true);
        if (type == MenuFamilyType::FONT_FAMILY) {
            MenuModelNG::SetFontFamily(&(*node), fontFamilies);
        }
        node->MarkModifyDone();
        node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

std::string MenuModelNG::ColorTypeToString(const MenuColorType menuColorType)
{
    std::string rst;
    switch (menuColorType) {
        case MenuColorType::FONT_COLOR:
            rst = "FontColor";
            break;
        case MenuColorType::GROUP_DIVIDER_COLOR:
            rst = "GroupDividerColor";
            break;
        case MenuColorType::DIVIDER_COLOR:
            rst = "DividerColor";
            break;
        default:
            rst = "Unknown";
            break;
    }
    return rst;
}

std::string MenuModelNG::DimensionTypeToString(const MenuDimensionType menuDimensionType)
{
    std::string rst;
    switch (menuDimensionType) {
        case MenuDimensionType::WIDTH:
            rst = "Width";
            break;
        case MenuDimensionType::FONT_SIZE:
            rst = "FontSize";
            break;
        case MenuDimensionType::RADIUS_TOP_LEFT:
            rst = "RadiusTopLeft";
            break;
        case MenuDimensionType::RADIUS_TOP_RIGHT:
            rst = "RadiusTopRight";
            break;
        case MenuDimensionType::RADIUS_BOTTOM_LEFT:
            rst = "RadiusBottomLeft";
            break;
        case MenuDimensionType::RADIUS_BOTTOM_RIGHT:
            rst = "RadiusBottomRight";
            break;
        case MenuDimensionType::BORDER_RADIUS:
            rst = "BorderRadius";
            break;
        default:
            rst = "Unknown";
            break;
    }
    return rst;
}

std::string MenuModelNG::FamilyTypeToString(const MenuFamilyType type)
{
    std::string rst;
    switch (type) {
        case MenuFamilyType::FONT_FAMILY:
            rst = "FontFamily";
            break;
        default:
            rst = "Unknown";
            break;
    }
    return rst;
}

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
        ACE_UPDATE_LAYOUT_PROPERTY(MenuLayoutProperty, FontColorSetByUser, true);
    } else {
        ACE_RESET_LAYOUT_PROPERTY(MenuLayoutProperty, FontColor);
        ACE_RESET_LAYOUT_PROPERTY(MenuLayoutProperty, FontColorSetByUser);
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

void MenuModelNG::SetBorderRadius(const NG::BorderRadiusProperty& borderRadius)
{
    if (SystemProperties::ConfigChangePerform()) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->RemoveResObj("borderRadius");
        auto&& updateFunc = [borderRadius, weak = AceType::WeakClaim(frameNode)](
                                const RefPtr<ResourceObject>& resObj) {
            auto node = weak.Upgrade();
            if (!node) {
                return;
            }
            NG::BorderRadiusProperty& borderRadiusValue = const_cast<NG::BorderRadiusProperty&>(borderRadius);
            borderRadiusValue.ReloadResources();
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, BorderRadius, borderRadius, node);
            node->MarkModifyDone();
            node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        };
        if (borderRadius.HasResources()) {
            RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
            pattern->AddResObj("borderRadius", resObj, std::move(updateFunc));
        }
    }

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

void MenuModelNG::SetExpandingMode(FrameNode* frameNode, const SubMenuExpandingMode& expandingMode)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ExpandingMode, expandingMode, frameNode);
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

void MenuModelNG::SetItemDivider(FrameNode* frameNode, const V2::ItemDivider& divider, const DividerMode& mode)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemDivider, divider, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemDividerMode, mode, frameNode);
}

void MenuModelNG::SetItemGroupDivider(const V2::ItemDivider& divider, const DividerMode& mode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemGroupDivider, divider);
    ACE_UPDATE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemGroupDividerMode, mode);
}

void MenuModelNG::SetItemGroupDivider(FrameNode* frameNode, const V2::ItemDivider& divider, const DividerMode& mode)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemGroupDivider, divider, frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItemGroupDividerMode, mode, frameNode);
}

void MenuModelNG::SetFontColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    CHECK_NULL_VOID(frameNode);
    if (color.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontColor, color.value(), frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontColorSetByUser, true, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontColor, frameNode);
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontColorSetByUser, frameNode);
    }
}

void MenuModelNG::SetFontSize(FrameNode* frameNode, const Dimension& fontSize)
{
    if (fontSize.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontSize, fontSize, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontSize, frameNode);
    }
}

void MenuModelNG::SetFontWeight(FrameNode* frameNode, FontWeight weight)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontWeight, weight, frameNode);
}

void MenuModelNG::SetFontStyle(FrameNode* frameNode, Ace::FontStyle style)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, ItalicFontStyle, style, frameNode);
}

void MenuModelNG::SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& families)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, FontFamily, families, frameNode);
}

void MenuModelNG::SetBorderRadius(FrameNode* frameNode, const Dimension& radius)
{
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = radius;
    borderRadius.radiusTopRight = radius;
    borderRadius.radiusBottomLeft = radius;
    borderRadius.radiusBottomRight = radius;
    borderRadius.multiValued = true;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, BorderRadius, borderRadius, frameNode);
}

void MenuModelNG::ResetBorderRadius(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY_WITH_FLAG(MenuLayoutProperty, BorderRadius, PROPERTY_UPDATE_MEASURE, frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        CHECK_NULL_VOID(frameNode);
        auto layoutProperty = frameNode->GetLayoutPropertyPtr<MenuLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        auto borderRadius = layoutProperty->GetBorderRadius();
        CHECK_NULL_VOID(borderRadius);
        borderRadius->ClearResources();
    }
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

void MenuModelNG::SetBorderRadius(FrameNode* frameNode, const NG::BorderRadiusProperty& borderRadius)
{
    if (SystemProperties::ConfigChangePerform()) {
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->RemoveResObj("borderRadius");
        auto&& updateFunc = [borderRadius, weak = AceType::WeakClaim(frameNode)](
                                const RefPtr<ResourceObject>& resObj) {
            auto node = weak.Upgrade();
            if (!node) {
                return;
            }
            NG::BorderRadiusProperty& borderRadiusValue = const_cast<NG::BorderRadiusProperty&>(borderRadius);
            borderRadiusValue.ReloadResources();
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, BorderRadius, borderRadius, node);
            node->MarkModifyDone();
            node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        };
        if (borderRadius.HasResources()) {
            RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
            pattern->AddResObj("borderRadius", resObj, std::move(updateFunc));
        }
    }

    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, BorderRadius, borderRadius, frameNode);
}

void MenuModelNG::SetWidth(FrameNode* frameNode, const Dimension& width)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuLayoutProperty, MenuWidth, width, frameNode);
    ViewAbstract::SetWidth(frameNode, NG::CalcLength(width));
}
} // namespace OHOS::Ace::NG
