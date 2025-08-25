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

#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"

namespace OHOS::Ace::NG {
void MenuItemModelNG::CreateWithColorResourceObj(const RefPtr<ResourceObject>& resObj, MenuItemFontColorType type)
{
    CHECK_NULL_VOID(resObj);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithColorResourceObj(frameNode, resObj, type);
}

void MenuItemModelNG::CreateWithColorResourceObj(
    FrameNode* frameNode, const RefPtr<ResourceObject>& resObj, MenuItemFontColorType type)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "MenuItem" + ColorTypeToString(type);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [pattern, key, type, weak = AceType::WeakClaim(frameNode)](
                            const RefPtr<ResourceObject>& resObj) {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        std::string colorStr = pattern->GetResCacheMapByKey(key);
        Color color;
        if (colorStr.empty()) {
            CHECK_NE_VOID(ResourceParseUtils::ParseResColor(resObj, color), true);
            pattern->AddResCache(key, color.ToString());
        } else {
            color = Color::ColorFromString(colorStr);
        }
        if (type == MenuItemFontColorType::FONT_COLOR) {
            MenuItemModelNG::SetFontColor(&(*node), color);
        } else if (type == MenuItemFontColorType::LABEL_FONT_COLOR) {
            MenuItemModelNG::SetLabelFontColor(&(*node), color);
        }
        node->MarkModifyDone();
        node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void MenuItemModelNG::CreateWithDimensionFpResourceObj(const RefPtr<ResourceObject>& resObj, MenuItemFontSizeType type)
{
    CHECK_NULL_VOID(resObj);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithDimensionFpResourceObj(frameNode, resObj, type);
}

void MenuItemModelNG::CreateWithDimensionFpResourceObj(
    FrameNode* frameNode, const RefPtr<ResourceObject>& resObj, MenuItemFontSizeType type)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "MenuItem" + DimensionTypeToString(type);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [pattern, key, type, weak = AceType::WeakClaim(frameNode)](
                            const RefPtr<ResourceObject>& resObj) {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        std::string cacheValue = pattern->GetResCacheMapByKey(key);
        CalcDimension result;
        if (cacheValue.empty()) {
            CHECK_NE_VOID(ResourceParseUtils::ParseResDimensionFpNG(resObj, result, false), true);
            pattern->AddResCache(key, result.ToString());
        } else {
            result = CalcDimension::FromString(cacheValue);
        }
        if (type == MenuItemFontSizeType::FONT_SIZE) {
            if (result.Unit() == DimensionUnit::PERCENT) {
                result = CalcDimension();
            }
            MenuItemModelNG::SetFontSize(&(*node), result);
        } else if (type == MenuItemFontSizeType::LABEL_FONT_SIZE) {
            if (result.Unit() == DimensionUnit::PERCENT) {
                result = CalcDimension();
            }
            MenuItemModelNG::SetLabelFontSize(&(*node), result);
        }
        node->MarkModifyDone();
        node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void MenuItemModelNG::CreateWithFontFamilyResourceObj(const RefPtr<ResourceObject>& resObj, MenuItemFontFamilyType type)
{
    CHECK_NULL_VOID(resObj);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithFontFamilyResourceObj(frameNode, resObj, type);
}

void MenuItemModelNG::CreateWithFontFamilyResourceObj(
    FrameNode* frameNode, const RefPtr<ResourceObject>& resObj, MenuItemFontFamilyType type)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "MenuItem" + FamilyTypeToString(type);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [type, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        std::vector<std::string> fontFamilies;
        CHECK_NE_VOID(ResourceParseUtils::ParseResFontFamilies(resObj, fontFamilies), true);
        if (type == MenuItemFontFamilyType::FONT_FAMILY) {
            MenuItemModelNG::SetFontFamily(&(*node), fontFamilies);
        } else if (type == MenuItemFontFamilyType::LABEL_FONT_FAMILY) {
            MenuItemModelNG::SetLabelFontFamily(&(*node), fontFamilies);
        }
        node->MarkModifyDone();
        node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void MenuItemModelNG::CreateWithStringResourceObj(const RefPtr<ResourceObject>& resObj, MenuItemStringType type)
{
    CHECK_NULL_VOID(resObj);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithStringResourceObj(frameNode, resObj, type);
}

void MenuItemModelNG::CreateWithStringResourceObj(
    FrameNode* frameNode, const RefPtr<ResourceObject>& resObj, MenuItemStringType type)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "MenuItem" + StringTypeToString(type);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [key, type, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        auto nodePattern = node->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(nodePattern);
        std::string str = nodePattern->GetResCacheMapByKey(key);
        if (str.empty()) {
            CHECK_NE_VOID(ResourceParseUtils::ParseResString(resObj, str), true);
            nodePattern->AddResCache(key, str);
        }
        if (type == MenuItemStringType::SELECT_ICON) {
            MenuItemModelNG::SetSelectIconSrc(&(*node), str);
        } else if (type == MenuItemStringType::CONTENT) {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, Content, str, &(*node));
        } else if (type == MenuItemStringType::LABEL_INFO) {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, Label, str, &(*node));
        }
        node->MarkModifyDone();
        node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void MenuItemModelNG::CreateWithMediaResourceObj(const RefPtr<ResourceObject>& resObj, const MenuItemIconType type)
{
    CHECK_NULL_VOID(resObj);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithMediaResourceObj(frameNode, resObj, type);
}

void MenuItemModelNG::CreateWithMediaResourceObj(
    FrameNode* frameNode, const RefPtr<ResourceObject>& resObj, const MenuItemIconType type)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "MenuItem" + MediaTypeToString(type);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [key, type, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        auto nodePattern = node->GetPattern<MenuItemPattern>();
        CHECK_NULL_VOID(nodePattern);
        std::string str = nodePattern->GetResCacheMapByKey(key);
        if (str.empty()) {
            nodePattern->AddResCache(key, str);
        }
        CHECK_NE_VOID(ResourceParseUtils::ParseResMedia(resObj, str), true);
        ImageSourceInfo imageSourceInfo(str);
        if (type == MenuItemIconType::START_ICON) {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, StartIcon, imageSourceInfo, &(*node));
        } else if (type == MenuItemIconType::END_ICON) {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, EndIcon, imageSourceInfo, &(*node));
        }
        node->MarkModifyDone();
        node->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

const std::string MenuItemModelNG::ColorTypeToString(const MenuItemFontColorType type)
{
    std::string rst;
    switch (type) {
        case MenuItemFontColorType::FONT_COLOR:
            rst = "FontColor";
            break;
        case MenuItemFontColorType::LABEL_FONT_COLOR:
            rst = "LabelFontColor";
            break;
        default:
            rst = "Unknown";
            break;
    }
    return rst;
}

const std::string MenuItemModelNG::DimensionTypeToString(const MenuItemFontSizeType type)
{
    std::string rst;
    switch (type) {
        case MenuItemFontSizeType::FONT_SIZE:
            rst = "FontSize";
            break;
        case MenuItemFontSizeType::LABEL_FONT_SIZE:
            rst = "LabelFontSize";
            break;
        default:
            rst = "Unknown";
            break;
    }
    return rst;
}

const std::string MenuItemModelNG::StringTypeToString(const MenuItemStringType type)
{
    std::string rst;
    switch (type) {
        case MenuItemStringType::SELECT_ICON:
            rst = "SelectIcon";
            break;
        case MenuItemStringType::CONTENT:
            rst = "Content";
            break;
        case MenuItemStringType::LABEL_INFO:
            rst = "LabelInfo";
            break;
        default:
            rst = "Unknown";
            break;
    }
    return rst;
}

const std::string MenuItemModelNG::FamilyTypeToString(const MenuItemFontFamilyType type)
{
    std::string rst;
    switch (type) {
        case MenuItemFontFamilyType::FONT_FAMILY:
            rst = "FontFamily";
            break;
        case MenuItemFontFamilyType::LABEL_FONT_FAMILY:
            rst = "LabelFontFamily";
            break;
        default:
            rst = "Unknown";
            break;
    }
    return rst;
}

const std::string MenuItemModelNG::MediaTypeToString(const MenuItemIconType type)
{
    std::string rst;
    switch (type) {
        case MenuItemIconType::START_ICON:
            rst = "StartIcon";
            break;
        case MenuItemIconType::END_ICON:
            rst = "EndIcon";
            break;
        default:
            rst = "Unknown";
            break;
    }
    return rst;
}

void MenuItemModelNG::Create(const RefPtr<UINode>& customNode)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::MENU_ITEM_ETS_TAG, nodeId);
    auto menuItem = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CustomMenuItemPattern>(); });
    CHECK_NULL_VOID(menuItem);
    stack->Push(menuItem);

    auto layoutProps = menuItem->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProps);
    layoutProps->UpdateAlignment(Alignment::CENTER_LEFT);
    // set border radius
    auto renderContext = menuItem->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);
    BorderRadiusProperty border;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        border.SetRadius(theme->GetMenuDefaultInnerRadius());
    } else {
        border.SetRadius(theme->GetInnerBorderRadius());
    }
    renderContext->UpdateBorderRadius(border);

    CHECK_NULL_VOID(customNode);
    if (!menuItem->GetChildren().empty()) {
        menuItem->Clean();
    }
    menuItem->AddChild(customNode);
    menuItem->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

/*
 * The structure of menu item is designed as follows :
 * |--menu_item
 *   |--left_row
 *     |--icon
 *     |--content
 *   |--right_row
 *     |--label
 *     |--end_icon
 */
void MenuItemModelNG::Create(const MenuItemProperties& menuItemProps)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    auto menuItem = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    CHECK_NULL_VOID(menuItem);
    stack->Push(menuItem);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(theme);

    SetupMenuItemProperties(menuItem, theme);

    auto buildFunc = menuItemProps.buildFunc;
    auto pattern = menuItem->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    if (buildFunc.has_value()) {
        pattern->SetSubBuilder(buildFunc.value_or(nullptr));
    }

    UpdateMenuProperty(menuItem, menuItemProps);
}

RefPtr<FrameNode> MenuItemModelNG::CreateMenuItem(OptionParam&& param, const MenuParam& menuParam)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();

    auto menuItem = FrameNode::GetOrCreateFrameNode(
        V2::MENU_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    CHECK_NULL_RETURN(menuItem, nullptr);

    auto renderContext = menuItem->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);

    auto pipeline = menuItem->GetContext();
    CHECK_NULL_RETURN(pipeline, nullptr);

    auto theme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_RETURN(theme, nullptr);

    SetupMenuItemProperties(menuItem, theme);

    auto menuProperty = menuItem->GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_RETURN(menuProperty, nullptr);
    menuProperty->UpdateContent(param.value);

    auto eventHub = menuItem->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    eventHub->SetEnabled(param.enabled);

    auto focusHub = menuItem->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, nullptr);
    focusHub->SetEnabled(param.enabled);

    GestureEventFunc clickFunc = [action = param.action](GestureEvent& info) { action(); };
    ViewAbstract::SetOnClick(AceType::RawPtr(menuItem), std::move(clickFunc));

    menuItem->MarkModifyDone();
    return menuItem;
}

void MenuItemModelNG::SetupMenuItemProperties(const RefPtr<FrameNode>& menuItem, const RefPtr<SelectTheme>& theme)
{
    auto renderContext = menuItem->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    BorderRadiusProperty border;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        border.SetRadius(theme->GetMenuDefaultInnerRadius());
    } else {
        border.SetRadius(theme->GetInnerBorderRadius());
    }
    renderContext->UpdateBorderRadius(border);

    if (menuItem->GetChildren().empty()) {
        auto leftRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(false));
        CHECK_NULL_VOID(leftRow);
        auto leftRowLayoutProps = leftRow->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_VOID(leftRowLayoutProps);
        leftRowLayoutProps->UpdateMainAxisAlign(FlexAlign::FLEX_START);
        leftRowLayoutProps->UpdateCrossAxisAlign(FlexAlign::CENTER);
        leftRowLayoutProps->UpdateSpace(theme->GetIconContentPadding());

        leftRow->MountToParent(menuItem);
        auto rightRow = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(false));
        CHECK_NULL_VOID(rightRow);
        auto rightRowLayoutProps = rightRow->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_VOID(rightRowLayoutProps);
        rightRowLayoutProps->UpdateMainAxisAlign(FlexAlign::CENTER);
        rightRowLayoutProps->UpdateCrossAxisAlign(FlexAlign::CENTER);
        rightRowLayoutProps->UpdateSpace(theme->GetIconContentPadding());

        rightRow->MountToParent(menuItem);
    }
}

void MenuItemModelNG::UpdateMenuProperty(const RefPtr<NG::FrameNode>& menuItem, const MenuItemProperties& menuItemProps)
{
    auto menuProperty = menuItem->GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);

    if (SystemProperties::ConfigChangePerform() && menuItemProps.HasResources()) {
        auto pattern = menuItem->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->RemoveResObj("menuItem");
        auto&& updateFunc = [menuItemProps, weak = AceType::WeakClaim(AceType::RawPtr(menuItem))](
                                const RefPtr<ResourceObject>& resObj) {
            auto frameNode = weak.Upgrade();
            if (!frameNode) {
                return;
            }
            auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
            CHECK_NULL_VOID(menuProperty);
            MenuItemProperties& menuItemPropsValue = const_cast<MenuItemProperties&>(menuItemProps);
            menuItemPropsValue.ReloadResources(menuItemPropsValue);
            menuProperty->UpdateContent(menuItemPropsValue.content);
            menuProperty->UpdateLabel(menuItemPropsValue.labelInfo.value_or(""));
            frameNode->MarkModifyDone();
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        };
        if (menuItemProps.HasResources()) {
            RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>();
            pattern->AddResObj("menuItem", resObj, std::move(updateFunc));
        }
    }

    menuProperty->UpdateStartIcon(menuItemProps.startIcon.value_or(ImageSourceInfo("")));
    menuProperty->UpdateContent(menuItemProps.content);
    menuProperty->UpdateEndIcon(menuItemProps.endIcon.value_or(ImageSourceInfo("")));
    menuProperty->UpdateLabel(menuItemProps.labelInfo.value_or(""));
    menuProperty->SetStartSymbol(menuItemProps.startApply);
    menuProperty->SetEndSymbol(menuItemProps.endApply);
}

void MenuItemModelNG::SetSelected(bool isSelected)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelected(isSelected);
    auto eventHub = frameNode->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, isSelected);
}

void MenuItemModelNG::SetSelectIcon(bool isShow)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, SelectIcon, isShow);
}

void MenuItemModelNG::SetSelectIconSrc(const std::string& src)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, SelectIconSrc, src);
}

void MenuItemModelNG::SetSelectIconSymbol(std::function<void(WeakPtr<NG::FrameNode>)>&& symbolApply)
{
    if (symbolApply != nullptr) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
        menuProperty->SetSelectSymbol(symbolApply);
    }
}

void MenuItemModelNG::SetOnChange(std::function<void(bool)>&& onChange)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(onChange);
}

void MenuItemModelNG::SetOnChange(FrameNode* frameNode, std::function<void(bool)>&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void MenuItemModelNG::SetFontSize(const Dimension& fontSize)
{
    if (fontSize.IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontSize, fontSize);
    } else {
        ACE_RESET_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontSize);
    }
}

void MenuItemModelNG::SetFontWeight(FontWeight weight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontWeight, weight);
}

void MenuItemModelNG::SetFontStyle(Ace::FontStyle style)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, ItalicFontStyle, style);
}

void MenuItemModelNG::SetFontColor(const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontColor, color.value());
    } else {
        ACE_RESET_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontColor);
    }
}

void MenuItemModelNG::SetFontFamily(const std::vector<std::string> &families)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontFamily, families);
}

void MenuItemModelNG::SetLabelFontSize(const Dimension& fontSize)
{
    if (fontSize.IsValid()) {
        ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontSize, fontSize);
    } else {
        ACE_RESET_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontSize);
    }
}

void MenuItemModelNG::SetLabelFontWeight(FontWeight weight)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontWeight, weight);
}

void MenuItemModelNG::SetLabelFontStyle(Ace::FontStyle style)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelItalicFontStyle, style);
}

void MenuItemModelNG::SetLabelFontColor(const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontColor, color.value());
        ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontColorSetByUser, true);
    } else {
        ACE_RESET_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontColor);
        ACE_RESET_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontColorSetByUser);
    }
}

void MenuItemModelNG::SetLabelFontFamily(const std::vector<std::string> &families)
{
    ACE_UPDATE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontFamily, families);
}

void MenuItemModelNG::SetSelectedChangeEvent(std::function<void(bool)>&& selectedChangeEvent)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetSelectedChangeEvent(selectedChangeEvent);
}

void MenuItemModelNG::SetSelected(FrameNode* frameNode, bool isSelected)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelected(isSelected);
    auto eventHub = frameNode->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, isSelected);
}

void MenuItemModelNG::SetLabelFontColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontColor, color.value(), frameNode);
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontColorSetByUser, true, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontColor, frameNode);
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontColorSetByUser, frameNode);
    }
}

void MenuItemModelNG::SetFontColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    if (color.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontColor, color.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontColor, frameNode);
    }
}

void MenuItemModelNG::SetLabelFontSize(FrameNode* frameNode, const Dimension& fontSize)
{
    if (fontSize.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontSize, fontSize, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontSize, frameNode);
    }
}

void MenuItemModelNG::SetLabelFontWeight(FrameNode* frameNode, FontWeight weight)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontWeight, weight, frameNode);
}

void MenuItemModelNG::SetLabelFontFamily(FrameNode* frameNode, const std::vector<std::string> &families)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelFontFamily, families, frameNode);
}

void MenuItemModelNG::SetLabelFontStyle(FrameNode* frameNode, Ace::FontStyle style)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, LabelItalicFontStyle, style, frameNode);
}

void MenuItemModelNG::SetFontSize(FrameNode* frameNode, const Dimension& fontSize)
{
    if (fontSize.IsValid()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontSize, fontSize, frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontSize, frameNode);
    }
}

void MenuItemModelNG::SetFontWeight(FrameNode* frameNode, FontWeight weight)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontWeight, weight, frameNode);
}

void MenuItemModelNG::SetFontFamily(FrameNode* frameNode, const std::vector<std::string> &families)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, FontFamily, families, frameNode);
}

void MenuItemModelNG::SetFontStyle(FrameNode* frameNode, Ace::FontStyle style)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, ItalicFontStyle, style, frameNode);
}

void MenuItemModelNG::SetSelectIcon(FrameNode* frameNode, bool isShow)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, SelectIcon, isShow, frameNode);
}

void MenuItemModelNG::SetSelectIconSrc(FrameNode* frameNode, const std::string& src)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(MenuItemLayoutProperty, SelectIconSrc, src, frameNode);
}

void MenuItemModelNG::SetSelectIconSymbol(FrameNode* frameNode,
    std::function<void(WeakPtr<NG::FrameNode>)>&& symbolApply)
{
    if (symbolApply != nullptr) {
        auto menuProperty = frameNode->GetLayoutProperty<MenuItemLayoutProperty>();
        CHECK_NULL_VOID(menuProperty);
        menuProperty->SetSelectSymbol(symbolApply);
    }
}
} // namespace OHOS::Ace::NG
