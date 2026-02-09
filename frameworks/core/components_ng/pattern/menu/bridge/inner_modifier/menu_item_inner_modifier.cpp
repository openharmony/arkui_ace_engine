/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_item_inner_modifier.h"

#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_row_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/select/select_properties.h"
#ifndef ACE_UNITTEST
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_menu_item_theme.h"
#endif
#include "core/components_ng/pattern/menu/menu_tag_constants.h"

namespace OHOS::Ace::NG {
namespace {
bool HasHideTask(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, false);
    return menuItemPattern->HasHideTask();
}

bool IsAtomicNode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, true);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, true);
    return menuItemPattern->IsAtomicNode();
}

bool IsEnableMatchParent(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, true);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, true);
    return menuItemPattern->IsEnableMatchParent();
}

bool IsEnableChildrenMatchParent(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, true);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, true);
    return menuItemPattern->IsEnableChildrenMatchParent();
}

bool IsEnableFix(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, true);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, true);
    return menuItemPattern->IsEnableFix();
}

bool MarkIsSelected(const RefPtr<FrameNode>& node, bool isSelected)
{
    CHECK_NULL_RETURN(node, false);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, false);
    menuItemPattern->MarkIsSelected(isSelected);
    return true;
}

void SetSelectedInt(const RefPtr<FrameNode>& node, int32_t selected)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetSelected(selected);
}

void SetSelectedBool(const RefPtr<FrameNode>& node, bool isSelected)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetSelected(isSelected);
}

bool IsSelected(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, false);
    return menuItemPattern->IsSelected();
}

void SetSubSelectMenuBuilder(const RefPtr<FrameNode>& node, const std::function<RefPtr<UINode>()>& subBuilderFunc)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetSubSelectMenuBuilder(subBuilderFunc);
}

std::function<RefPtr<UINode>()>& GetSubSelectMenuBuilder(const RefPtr<FrameNode>& node)
{
    static std::function<RefPtr<UINode>()> emptyFunc;
    CHECK_NULL_RETURN(node, emptyFunc);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, emptyFunc);
    return menuItemPattern->GetSubSelectMenuBuilder();
}

RefPtr<FrameNode> FindTouchedEmbeddedMenuItem(const RefPtr<UINode>& node, PointF position)
{
    auto frameNode = AceType::DynamicCast<FrameNode>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto itemNode = pattern->FindTouchedEmbeddedMenuItem(position);
    CHECK_NULL_RETURN(itemNode, nullptr);
    return itemNode;
}

bool IsDisabled(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, true);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, true);
    return menuItemPattern->IsDisabled();
}

bool IsStackSubmenuHeader(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, true);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, true);
    return menuItemPattern->IsStackSubmenuHeader();
}

void NotifyPressStatus(const RefPtr<FrameNode>& node, bool isPress)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->NotifyPressStatus(isPress);
}

RefPtr<FrameNode> GetMenu(const RefPtr<FrameNode>& node, bool needTopMenu)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, nullptr);
    return menuItemPattern->GetMenu(needTopMenu);
}

bool SetIsSubMenuShowed(const RefPtr<FrameNode>& node, bool isSubMenuShowed)
{
    CHECK_NULL_RETURN(node, false);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, false);
    menuItemPattern->SetIsSubMenuShowed(isSubMenuShowed);
    return true;
}

bool IsInHoverRegions(const RefPtr<FrameNode>& node, double x, double y)
{
    CHECK_NULL_RETURN(node, false);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, false);
    return menuItemPattern->IsInHoverRegions(x, y);
}

bool IsSubMenuShowed(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, false);
    return menuItemPattern->IsSubMenuShowed();
}

void CancelHideSubMenuTask(const RefPtr<FrameNode>& node, const PointF& mousePoint)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->CancelHideSubMenuTask(mousePoint);
}

void CheckHideSubMenu(
    const RefPtr<FrameNode>& node, std::function<void()> callback, const PointF& mousePoint, const RectF& menuZone)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->CheckHideSubMenu(callback, mousePoint, menuZone);
}

void SetFontSize(const RefPtr<FrameNode>& node, const Dimension& value)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetFontSize(value);
}

void SetFontColor(const RefPtr<FrameNode>& node, const Color& color, bool isNeedRecord)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetFontColor(color, isNeedRecord);
}

void SetBgColor(const RefPtr<FrameNode>& node, const Color& color)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetBgColor(color);
}

Color GetBgColor(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, Color());
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, Color());
    return menuItemPattern->GetBgColor();
}

void UpdateNextNodeDivider(const RefPtr<FrameNode>& node, bool needDivider)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->UpdateNextNodeDivider(needDivider);
}

bool IsMenuItemPattern(const RefPtr<Pattern>& pattern)
{
    return AceType::InstanceOf<MenuItemPattern>(pattern);
}

bool HasMenuItemPattern(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    return menuItemPattern != nullptr;
}

RefPtr<FrameNode> GetTopDivider(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, nullptr);
    return menuItemPattern->GetTopDivider();
}

void HideEmbedded(const RefPtr<FrameNode>& node, bool isNeedAnimation)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->HideEmbedded(isNeedAnimation);
}

SubMenuExpandingMode GetExpandingMode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, SubMenuExpandingMode::SIDE);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, SubMenuExpandingMode::SIDE);
    return menuItemPattern->GetExpandingMode();
}

void AddHoverRegions(const RefPtr<FrameNode>& node, const OffsetF& topLeftPoint, const OffsetF& bottomRightPoint)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->AddHoverRegions(topLeftPoint, bottomRightPoint);
}

void SetIsWidthModifiedBySelect(const RefPtr<FrameNode>& node, bool isModified)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetIsWidthModifiedBySelect(isModified);
}

std::string GetText(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, std::string());
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, std::string());
    return menuItemPattern->GetText();
}

void SetItalicFontStyle(const RefPtr<FrameNode>& node, const Ace::FontStyle& value)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetItalicFontStyle(value);
}

void SetFontWeight(const RefPtr<FrameNode>& node, const FontWeight& value)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetFontWeight(value);
}

void SetFontFamily(const RefPtr<FrameNode>& node, const std::vector<std::string>& value)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetFontFamily(value);
}

void SetOptionFontColor(const RefPtr<FrameNode>& node, const Color& color)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetOptionFontColor(color);
}

void SetShowDefaultSelectedIcon(const RefPtr<FrameNode>& node, bool show)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetShowDefaultSelectedIcon(show);
}

void SetTextNode(const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& text)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetTextNode(text);
}

void SetBlockClick(const RefPtr<FrameNode>& node, bool blockClick)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetBlockClick(blockClick);
}

void SetPasteButton(const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& pasteButton)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetPasteButton(pasteButton);
}

RefPtr<FrameNode> GetTextNode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, nullptr);
    return menuItemPattern->GetTextNode();
}

std::function<void(WeakPtr<NG::FrameNode>)>& GetOptionTextModifier(const RefPtr<FrameNode>& node)
{
    static std::function<void(WeakPtr<NG::FrameNode>)> emptyFunc;
    CHECK_NULL_RETURN(node, emptyFunc);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, emptyFunc);
    return menuItemPattern->GetOptionTextModifier();
}

std::function<void(WeakPtr<NG::FrameNode>)>& GetSelectedOptionTextModifier(const RefPtr<FrameNode>& node)
{
    static std::function<void(WeakPtr<NG::FrameNode>)> emptyFunc;
    CHECK_NULL_RETURN(node, emptyFunc);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, emptyFunc);
    return menuItemPattern->GetSelectedOptionTextModifier();
}

void SetOptionTextModifier(const RefPtr<FrameNode>& node, const std::function<void(WeakPtr<NG::FrameNode>)>& modifier)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetOptionTextModifier(modifier);
}

void ResetSelectTextProps(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->ResetSelectTextProps();
}

void ApplyOptionThemeStyles(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->ApplyOptionThemeStyles();
}

void SetSelectedOptionTextModifier(
    const RefPtr<FrameNode>& node, const std::function<void(WeakPtr<NG::FrameNode>)>& optionSelectedApply)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetSelectedOptionTextModifier(optionSelectedApply);
}

void ApplySelectedThemeStyles(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->ApplySelectedThemeStyles();
}

void SetCheckMarkVisibleType(const RefPtr<FrameNode>& node, VisibleType type)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetCheckMarkVisibleType(type);
}

std::string InspectorGetFont(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, std::string());
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, std::string());
    return menuItemPattern->InspectorGetFont();
}

Color GetFontColor(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, Color::TRANSPARENT);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, Color::TRANSPARENT);
    return menuItemPattern->GetFontColor();
}

std::string GetIcon(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, std::string());
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, std::string());
    return menuItemPattern->GetIcon();
}

void UpdateCheckMarkColor(const RefPtr<FrameNode>& node, const Color& color)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->UpdateCheckMarkColor(color);
}

RefPtr<FrameNode> GetBottomDivider(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, nullptr);
    return menuItemPattern->GetBottomDivider();
}

void SetHasOptionWidth(const RefPtr<FrameNode>& node, bool hasOptionWidth)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetHasOptionWidth(hasOptionWidth);
}

RefPtr<FrameNode> GetOrCreateFrameNode(const std::string& nodeName, int32_t nodeId, bool isOptionPattern, int index)
{
    RefPtr<FrameNode> frameNode;
    if (nodeName == "MenuItem") {
        frameNode = FrameNode::GetOrCreateFrameNode(nodeName, nodeId,
            [isOptionPattern, index]() { return AceType::MakeRefPtr<MenuItemPattern>(isOptionPattern, index); });
    } else if (nodeName == "Row") {
        frameNode = FrameNode::GetOrCreateFrameNode(
            nodeName, nodeId, []() { return AceType::MakeRefPtr<MenuItemRowPattern>(); });
    }
    return frameNode;
}

void SetSubBuilder(const RefPtr<FrameNode>& node, const std::function<void()>& subBuilderFunc)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->SetSubBuilder(subBuilderFunc);
}

void AddResObj(const RefPtr<FrameNode>& node, const std::string& key, const RefPtr<ResourceObject>& resObj,
    std::function<void(const RefPtr<ResourceObject>&)>&& updateFunc)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->AddResObj(key, resObj, std::move(updateFunc));
}

void RemoveResObj(const RefPtr<FrameNode>& node, const std::string& key)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->RemoveResObj(key);
}

std::string GetResCacheMapByKey(const RefPtr<FrameNode>& node, const std::string& key)
{
    CHECK_NULL_RETURN(node, std::string());
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_RETURN(menuItemPattern, std::string());
    return menuItemPattern->GetResCacheMapByKey(key);
}

void AddResCache(const RefPtr<FrameNode>& node, const std::string& key, const std::string& value)
{
    CHECK_NULL_VOID(node);
    auto menuItemPattern = node->GetPattern<MenuItemPattern>();
    CHECK_NULL_VOID(menuItemPattern);
    menuItemPattern->AddResCache(key, value);
}

// MenuItemEventHub related functions
bool HasMenuItemEventHub(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto eventHub = node->GetEventHub<MenuItemEventHub>();
    return eventHub != nullptr;
}

void SetSelectOverlayMenuOnClick(const RefPtr<FrameNode>& node, const std::function<void()>& onClickFunc)
{
    CHECK_NULL_VOID(node);
    auto eventHub = node->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetSelectOverlayMenuOnClick(onClickFunc);
}

void SetEnabled(const RefPtr<FrameNode>& node, bool enabled)
{
    CHECK_NULL_VOID(node);
    auto eventHub = node->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetEnabled(enabled);
}

void SetCurrentUIState(const RefPtr<FrameNode>& node, uint64_t state, bool flag)
{
    CHECK_NULL_VOID(node);
    auto eventHub = node->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(state, flag);
}

void SetOnSelect(const RefPtr<FrameNode>& node, const std::function<void(int32_t)>& onSelect)
{
    CHECK_NULL_VOID(node);
    auto eventHub = node->GetEventHub<MenuItemEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelect(onSelect);
}

// MenuItemPaintProperty related functions
void UpdateSelectModifiedWidth(const RefPtr<FrameNode>& node, const float& value)
{
    CHECK_NULL_VOID(node);
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateSelectModifiedWidth(value);
}

void UpdateOptionBgColor(const RefPtr<FrameNode>& node, const Color& color)
{
    CHECK_NULL_VOID(node);
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateOptionBgColor(color);
}

void UpdateOptionFontColor(const RefPtr<FrameNode>& node, const Color& color)
{
    CHECK_NULL_VOID(node);
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateOptionFontColor(color);
}

void UpdateSelectedOptionBgColor(const RefPtr<FrameNode>& node, const Color& color)
{
    CHECK_NULL_VOID(node);
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateSelectedOptionBgColor(color);
}

void UpdateSelectedOptionFontColor(const RefPtr<FrameNode>& node, const Color& color)
{
    CHECK_NULL_VOID(node);
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateSelectedOptionFontColor(color);
}

void UpdateNeedDivider(const RefPtr<FrameNode>& node, bool needDivider)
{
    CHECK_NULL_VOID(node);
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateNeedDivider(needDivider);
}

float GetSelectModifiedWidthValue(const RefPtr<FrameNode>& node, const float& value)
{
    CHECK_NULL_RETURN(node, 0.0f);
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, 0.0f);
    return paintProperty->GetSelectModifiedWidthValue(value);
}

bool HasDivider(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, false);
    return paintProperty->HasDivider();
}

SelectDivider GetDividerValue(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, SelectDivider());
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, SelectDivider());
    return paintProperty->GetDividerValue();
}

void UpdateDivider(const RefPtr<FrameNode>& node, const SelectDivider& divider)
{
    CHECK_NULL_VOID(node);
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateDivider(divider);
}

void SetIdealWidthForWeb(const RefPtr<FrameNode>& node, int32_t width)
{
    CHECK_NULL_VOID(node);
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->SetIdealWidthForWeb(width);
}

void UpdateStartMargin(const RefPtr<FrameNode>& node, const Dimension& value)
{
    CHECK_NULL_VOID(node);
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateStartMargin(value);
}

void UpdateEndMargin(const RefPtr<FrameNode>& node, const Dimension& value)
{
    CHECK_NULL_VOID(node);
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateEndMargin(value);
}

void UpdateDividerColor(const RefPtr<FrameNode>& node, const Color& color)
{
    CHECK_NULL_VOID(node);
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateDividerColor(color);
}

// MenuItemLayoutProperty
void UpdateStartIcon(const RefPtr<FrameNode>& node, const ImageSourceInfo& value)
{
    CHECK_NULL_VOID(node);
    auto menuProperty = node->GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);
    menuProperty->UpdateStartIcon(value);
}

void UpdateEndIcon(const RefPtr<FrameNode>& node, const ImageSourceInfo& value)
{
    CHECK_NULL_VOID(node);
    auto menuProperty = node->GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);
    menuProperty->UpdateEndIcon(value);
}

void UpdateContent(const RefPtr<FrameNode>& node, const std::string& value)
{
    CHECK_NULL_VOID(node);
    auto menuProperty = node->GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);
    menuProperty->UpdateContent(value);
}

void UpdateLabel(const RefPtr<FrameNode>& node, const std::string& value)
{
    CHECK_NULL_VOID(node);
    auto menuProperty = node->GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);
    menuProperty->UpdateLabel(value);
}

void SetStartSymbol(const RefPtr<FrameNode>& node, const std::function<void(WeakPtr<NG::FrameNode>)>& symbol)
{
    CHECK_NULL_VOID(node);
    auto menuProperty = node->GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);
    menuProperty->SetStartSymbol(symbol);
}

void SetEndSymbol(const RefPtr<FrameNode>& node, const std::function<void(WeakPtr<NG::FrameNode>)>& symbol)
{
    CHECK_NULL_VOID(node);
    auto menuProperty = node->GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);
    menuProperty->SetEndSymbol(symbol);
}

void SetSelectSymbol(const RefPtr<FrameNode>& node, const std::function<void(WeakPtr<NG::FrameNode>)>& symbol)
{
    CHECK_NULL_VOID(node);
    auto menuProperty = node->GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(menuProperty);
    menuProperty->SetSelectSymbol(symbol);
}

RefPtr<FrameNode> CreateWithParam(OptionParam&& param, const MenuParam& menuParam)
{
    return MenuItemModelNG::CreateMenuItem(std::move(param), menuParam);
}

RefPtr<FrameNode> CreateWithOnClickEventSet(bool isClickSet)
{
    auto menuItemPattern = AceType::MakeRefPtr<MenuItemPattern>();
    menuItemPattern->SetOnClickEventSet(true);
    return FrameNode::CreateFrameNode(
        MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), menuItemPattern);
}

RefPtr<FrameNode> CreateFrameNode()
{
    return FrameNode::CreateFrameNode(
        MENU_ITEM_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MenuItemPattern>());
}

void MenuItemUpdatePadding(const RefPtr<FrameNode>& node, const PaddingProperty& value)
{
    auto menuItemProperty = node->GetLayoutProperty<MenuItemLayoutProperty>();
    CHECK_NULL_VOID(menuItemProperty);
    menuItemProperty->UpdatePadding(value);
}

void MenuItemUpdateStrokeWidth(const RefPtr<FrameNode>& node, const Dimension& value)
{
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateStrokeWidth(value);
}

void MenuItemUpdateStartMargin(const RefPtr<FrameNode>& node, const Dimension& value)
{
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateStartMargin(value);
}

void MenuItemUpdateEndMargin(const RefPtr<FrameNode>& node, const Dimension& value)
{
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateEndMargin(value);
}

void MenuItemUpdateDividerColor(const RefPtr<FrameNode>& node, const Color& value)
{
    auto paintProperty = node->GetPaintProperty<MenuItemPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateDividerColor(value);
}

void JSMenuItemThemeApplyTheme()
{
#ifndef ACE_UNITTEST
    Framework::JSMenuItemTheme::ApplyTheme();
#endif
}
} // namespace

namespace InnerModifier {
const ArkUIMenuItemInnerModifier* GetMenuItemInnerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIMenuItemInnerModifier modifier = {
        .hasHideTask = HasHideTask,
        .isAtomicNode = IsAtomicNode,
        .isEnableMatchParent = IsEnableMatchParent,
        .isEnableChildrenMatchParent = IsEnableChildrenMatchParent,
        .isEnableFix = IsEnableFix,
        .markIsSelected = MarkIsSelected,
        .setSelectedInt = SetSelectedInt,
        .setSelectedBool = SetSelectedBool,
        .isSelected = IsSelected,
        .setSubSelectMenuBuilder = SetSubSelectMenuBuilder,
        .getSubSelectMenuBuilder = GetSubSelectMenuBuilder,
        .findTouchedEmbeddedMenuItem = FindTouchedEmbeddedMenuItem,
        .isDisabled = IsDisabled,
        .isStackSubmenuHeader = IsStackSubmenuHeader,
        .notifyPressStatus = NotifyPressStatus,
        .getMenu = GetMenu,
        .setIsSubMenuShowed = SetIsSubMenuShowed,
        .isInHoverRegions = IsInHoverRegions,
        .isSubMenuShowed = IsSubMenuShowed,
        .checkHideSubMenu = CheckHideSubMenu,
        .cancelHideSubMenuTask = CancelHideSubMenuTask,
        .setFontSize = SetFontSize,
        .setFontColor = SetFontColor,
        .setBgColor = SetBgColor,
        .getBgColor = GetBgColor,
        .updateNextNodeDivider = UpdateNextNodeDivider,
        .isMenuItemPattern = IsMenuItemPattern,
        .hasMenuItemPattern = HasMenuItemPattern,
        .getTopDivider = GetTopDivider,
        .hideEmbedded = HideEmbedded,
        .getExpandingMode = GetExpandingMode,
        .addHoverRegions = AddHoverRegions,
        .setIsWidthModifiedBySelect = SetIsWidthModifiedBySelect,
        .getText = GetText,
        .setItalicFontStyle = SetItalicFontStyle,
        .setFontWeight = SetFontWeight,
        .setFontFamily = SetFontFamily,
        .setOptionFontColor = SetOptionFontColor,
        .setShowDefaultSelectedIcon = SetShowDefaultSelectedIcon,
        .setTextNode = SetTextNode,
        .setBlockClick = SetBlockClick,
        .setPasteButton = SetPasteButton,
        .getTextNode = GetTextNode,
        .getOptionTextModifier = GetOptionTextModifier,
        .getSelectedOptionTextModifier = GetSelectedOptionTextModifier,
        .setOptionTextModifier = SetOptionTextModifier,
        .resetSelectTextProps = ResetSelectTextProps,
        .applyOptionThemeStyles = ApplyOptionThemeStyles,
        .setSelectedOptionTextModifier = SetSelectedOptionTextModifier,
        .applySelectedThemeStyles = ApplySelectedThemeStyles,
        .setCheckMarkVisibleType = SetCheckMarkVisibleType,
        .inspectorGetFont = InspectorGetFont,
        .getFontColor = GetFontColor,
        .getIcon = GetIcon,
        .updateCheckMarkColor = UpdateCheckMarkColor,
        .getBottomDivider = GetBottomDivider,
        .setHasOptionWidth = SetHasOptionWidth,
        .getOrCreateFrameNode = GetOrCreateFrameNode,
        .setSubBuilder = SetSubBuilder,
        .addResObj = AddResObj,
        .removeResObj = RemoveResObj,
        .getResCacheMapByKey = GetResCacheMapByKey,
        .addResCache = AddResCache,
        .hasMenuItemEventHub = HasMenuItemEventHub,
        .setSelectOverlayMenuOnClick = SetSelectOverlayMenuOnClick,
        .setEnabled = SetEnabled,
        .setCurrentUIState = SetCurrentUIState,
        .setOnSelect = SetOnSelect,
        .updateSelectModifiedWidth = UpdateSelectModifiedWidth,
        .updateOptionBgColor = UpdateOptionBgColor,
        .updateOptionFontColor = UpdateOptionFontColor,
        .updateSelectedOptionBgColor = UpdateSelectedOptionBgColor,
        .updateSelectedOptionFontColor = UpdateSelectedOptionFontColor,
        .updateNeedDivider = UpdateNeedDivider,
        .getSelectModifiedWidthValue = GetSelectModifiedWidthValue,
        .hasDivider = HasDivider,
        .getDividerValue = GetDividerValue,
        .updateDivider = UpdateDivider,
        .setIdealWidthForWeb = SetIdealWidthForWeb,
        .updateStartMargin = UpdateStartMargin,
        .updateEndMargin = UpdateEndMargin,
        .updateDividerColor = UpdateDividerColor,
        .updateStartIcon = UpdateStartIcon,
        .updateEndIcon = UpdateEndIcon,
        .updateContent = UpdateContent,
        .updateLabel = UpdateLabel,
        .setStartSymbol = SetStartSymbol,
        .setEndSymbol = SetEndSymbol,
        .setSelectSymbol = SetSelectSymbol,
        .createWithParam = CreateWithParam,
        .createWithOnClickEventSet = CreateWithOnClickEventSet,
        .menuItemUpdatePadding = MenuItemUpdatePadding,
        .menuItemUpdateStrokeWidth = MenuItemUpdateStrokeWidth,
        .menuItemUpdateStartMargin = MenuItemUpdateStartMargin,
        .menuItemUpdateEndMargin = MenuItemUpdateEndMargin,
        .menuItemUpdateDividerColor = MenuItemUpdateDividerColor,
        .menuItemCreateFrameNode = CreateFrameNode,
        .menuItemApplyTheme = JSMenuItemThemeApplyTheme,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace InnerModifier
} // namespace OHOS::Ace::NG