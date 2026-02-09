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

#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_inner_modifier.h"

#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_model_ng.h"
#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "core/components_ng/pattern/menu/menu_tag_constants.h"
namespace OHOS::Ace::NG {
namespace {
// ------------------------ menu modifier ------------------------
// MenuPattern
bool IsMenuPattern(const RefPtr<NG::Pattern>& pattern)
{
    return AceType::InstanceOf<OHOS::Ace::NG::MenuPattern>(pattern);
}

bool IsContextMenu(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, false);
    return menuPattern->IsContextMenu();
}

MenuPreviewMode GetPreviewMode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, MenuPreviewMode::NONE);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, MenuPreviewMode::NONE);
    return menuPattern->GetPreviewMode();
}

bool IsSelectMenu(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, false);
    return menuPattern->IsSelectMenu();
}

void HideMenu(const RefPtr<FrameNode>& node, const HideMenuType& reason)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->HideMenu(reason);
}

bool GetDisappearAnimation(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, false);
    return menuPattern->GetDisappearAnimation();
}

std::string GetTargetTag(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, std::string());
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, std::string());
    return menuPattern->GetTargetTag();
}

int32_t GetTargetId(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, -1);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, -1);
    return menuPattern->GetTargetId();
}

RefPtr<FrameNode> GetShowedSubMenu(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, nullptr);
    return menuPattern->GetShowedSubMenu();
}

RefPtr<FrameNode> GetFirstInnerMenu(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, nullptr);
    return menuPattern->GetFirstInnerMenu();
}

int32_t GetSubMenuDepth(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, 0);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, 0);
    return menuPattern->GetSubMenuDepth();
}

RefPtr<FrameNode> GetParentMenuItem(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, nullptr);
    return menuPattern->GetParentMenuItem();
}

void RemoveParentHoverStyle(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->RemoveParentHoverStyle();
}

void SetShowedSubMenu(const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& subMenu)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetShowedSubMenu(subMenu);
}

bool IsSubMenu(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, false);
    return menuPattern->IsSubMenu();
}

bool IsSelectOverlaySubmenu(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, false);
    return menuPattern->IsSelectOverlaySubMenu();
}

void SetDisappearAnimation(const RefPtr<FrameNode>& node, bool hasAnimation)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetDisappearAnimation(hasAnimation);
}

bool IsSelectOverlayCustomMenu(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, false);
    return menuPattern->IsSelectOverlayCustomMenu();
}

bool IsSelectOverlayRightClickMenu(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, false);
    return menuPattern->IsSelectOverlayRightClickMenu();
}

RefPtr<MenuLayoutProperty> GetLayoutProperty(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, nullptr);
    return menuPattern->GetLayoutProperty<MenuLayoutProperty>();
}

void FocusViewShow(const RefPtr<FrameNode>& node, bool isTriggerByStep)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->FocusViewShow(isTriggerByStep);
}

void ShowStackMenuDisappearAnimation(
    const RefPtr<FrameNode>& menuNode, const RefPtr<FrameNode>& subMenuNode, AnimationOption& option)
{
    CHECK_NULL_VOID(menuNode);
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->ShowStackMenuDisappearAnimation(menuNode, subMenuNode, option);
}

void SetSubMenuShow(const RefPtr<FrameNode>& node, bool subMenuShowed)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetSubMenuShow(subMenuShowed);
}

void SetCustomNode(const RefPtr<FrameNode>& node, WeakPtr<UINode> customNode)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetCustomNode(customNode);
}

std::vector<RefPtr<FrameNode>>& GetEmbeddedMenuItems(const RefPtr<FrameNode>& node)
{
    static std::vector<RefPtr<FrameNode>> embeddedMenuItems = {};
    CHECK_NULL_RETURN(node, embeddedMenuItems);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, embeddedMenuItems);
    return menuPattern->GetEmbeddedMenuItems();
}

bool GetIsShowHoverImage(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, false);
    return menuPattern->GetIsShowHoverImage();
}

float GetPreviewBeforeAnimationScale(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, -1.0f);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, -1.0f);
    return menuPattern->GetPreviewBeforeAnimationScale();
}

float GetPreviewAfterAnimationScale(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, -1.0f);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, -1.0f);
    return menuPattern->GetPreviewAfterAnimationScale();
}

std::optional<Placement> GetLastPlacement(const RefPtr<FrameNode>& node)
{
    std::optional<Placement> lastPlacement;
    CHECK_NULL_RETURN(node, lastPlacement);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, lastPlacement);
    return menuPattern->GetLastPlacement();
}

RefPtr<FrameNode> DuplicateMenuNode(
    const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, nullptr);
    return menuPattern->DuplicateMenuNode(menuNode, menuParam);
}

void RemoveResObj(const RefPtr<FrameNode>& node, const std::string& key)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->RemoveResObj(key);
}

std::string GetResCacheMapByKey(const RefPtr<FrameNode>& node, const std::string& key)
{
    CHECK_NULL_RETURN(node, "");
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, "");
    return menuPattern->GetResCacheMapByKey(key);
}

void AddResCache(const RefPtr<FrameNode>& node, const std::string& key, const std::string& value)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->AddResCache(key, value);
}

void AddResObj(const RefPtr<FrameNode>& node, const std::string& key, const RefPtr<ResourceObject>& resObj,
    std::function<void(const RefPtr<ResourceObject>&)>&& updateFunc)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->AddResObj(key, resObj, std::move(updateFunc));
}

std::optional<MenuPathParams> GetMenuPathParams(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, std::nullopt);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, std::nullopt);
    return menuPattern->GetMenuPathParams();
}

void SetIsSelectMenu(const RefPtr<FrameNode>& node, bool isSelectMenu)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetIsSelectMenu(isSelectMenu);
}

void SetDisableMenuBgColorByUser(const RefPtr<FrameNode>& node, bool ret)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetDisableMenuBgColorByUser(ret);
}

void UpdateSelectParam(const RefPtr<FrameNode>& node, const std::vector<SelectParam>& params)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->UpdateSelectParam(params);
}

const std::vector<RefPtr<FrameNode>>& GetOptions(const RefPtr<FrameNode>& node)
{
    static std::vector<RefPtr<FrameNode>> options = {};
    CHECK_NULL_RETURN(node, options);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, options);
    return menuPattern->GetOptions();
}

void SetSelectProperties(const RefPtr<FrameNode>& node, const std::vector<SelectParam>& params)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetSelectProperties(params);
}

void SetBuilderFunc(const RefPtr<FrameNode>& node, SelectMakeCallback&& makeFunc)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetBuilderFunc(std::move(makeFunc));
}

void ResetBuilderFunc(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->ResetBuilderFunc();
}

void UpdateSelectIndex(const RefPtr<FrameNode>& node, int32_t index)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->UpdateSelectIndex(index);
}

void UpdateSelectOptionTextByIndex(const RefPtr<FrameNode>& node, int32_t index, const std::string& text)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->UpdateSelectOptionTextByIndex(index, text);
}

void UpdateSelectOptionIconByIndex(const RefPtr<FrameNode>& node, int32_t index, const std::string& icon)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->UpdateSelectOptionIconByIndex(index, icon);
}

void SetIsWidthModifiedBySelect(const RefPtr<FrameNode>& node, bool isModified)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetIsWidthModifiedBySelect(isModified);
}

void SetHasOptionWidth(const RefPtr<FrameNode>& node, bool hasOptionWidth)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetHasOptionWidth(hasOptionWidth);
}

void SetIsHeightModifiedBySelect(const RefPtr<FrameNode>& node, bool isModified)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetIsHeightModifiedBySelect(isModified);
}

void UpdateMenuItemDivider(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->UpdateMenuItemDivider();
}

void AddMenuItemNode(const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& menuItem)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->AddMenuItemNode(menuItem);
}

void HideAllEmbeddedMenuItems(const RefPtr<FrameNode>& node, bool isNeedAnimation)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->HideAllEmbeddedMenuItems(isNeedAnimation);
}

void SetMenuShow(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetMenuShow();
}

void ShowMenuDisappearAnimation(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->ShowMenuDisappearAnimation();
}

const std::vector<RefPtr<FrameNode>>& GetMenuItems(const RefPtr<FrameNode>& node)
{
    static std::vector<RefPtr<FrameNode>> menuItems = {};
    CHECK_NULL_RETURN(node, menuItems);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_RETURN(menuPattern, menuItems);
    return menuPattern->GetMenuItems();
}

void SetSelectOverlayExtensionMenuShow(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetSelectOverlayExtensionMenuShow();
}

RefPtr<FrameNode> GetOrCreateMenuNode(
    const std::string& nodeTag, int32_t nodeId, const std::string& patternTag, int32_t patternId, MenuType menuType)
{
    return FrameNode::GetOrCreateFrameNode(nodeTag, nodeId, [&patternTag, patternId, menuType]() {
        return AceType::MakeRefPtr<MenuPattern>(patternId, patternTag, menuType);
    });
}

void SetParentMenuItem(const RefPtr<FrameNode>& node, const RefPtr<FrameNode>& parentMenuItem)
{
    CHECK_NULL_VOID(node);
    auto menuPattern = node->GetPattern<MenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetParentMenuItem(parentMenuItem);
}

// MenuPreviewPattern
float GetHoverImageAfterScaleWidth(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, 0.0f);
    auto menuPreviewPattern = node->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_RETURN(menuPreviewPattern, 0.0f);
    return menuPreviewPattern->GetHoverImageAfterScaleWidth();
}

float GetHoverImageAfterScaleHeight(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, 0.0f);
    auto menuPreviewPattern = node->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_RETURN(menuPreviewPattern, 0.0f);
    return menuPreviewPattern->GetHoverImageAfterScaleHeight();
}

float GetStackAfterScaleActualWidth(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, 0.0f);
    auto menuPreviewPattern = node->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_RETURN(menuPreviewPattern, 0.0f);
    return menuPreviewPattern->GetStackAfterScaleActualWidth();
}

float GetStackAfterScaleActualHeight(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, 0.0f);
    auto menuPreviewPattern = node->GetPattern<MenuPreviewPattern>();
    CHECK_NULL_RETURN(menuPreviewPattern, 0.0f);
    return menuPreviewPattern->GetStackAfterScaleActualHeight();
}

// MenuLayoutProperty
void UpdateMenuOffset(const RefPtr<FrameNode>& node, const OHOS::Ace::NG::OffsetF& value)
{
    CHECK_NULL_VOID(node);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    menuLayoutProperty->UpdateMenuOffset(value);
}

void ResetMenuPlacement(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    menuLayoutProperty->ResetMenuPlacement();
}

std::optional<SubMenuExpandingMode> GetExpandingMode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, SubMenuExpandingMode::SIDE);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(menuLayoutProperty, SubMenuExpandingMode::SIDE);
    return menuLayoutProperty->GetExpandingMode().value_or(SubMenuExpandingMode::SIDE);
}

void UpdateTargetSize(const RefPtr<FrameNode>& node, const OHOS::Ace::NG::SizeF& value)
{
    CHECK_NULL_VOID(node);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    menuLayoutProperty->UpdateTargetSize(value);
}

void UpdateShowInSubWindow(const RefPtr<FrameNode>& node, const bool& value)
{
    CHECK_NULL_VOID(node);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    menuLayoutProperty->UpdateShowInSubWindow(value);
}

void UpdateShowDefaultSelectedIcon(const RefPtr<FrameNode>& node, const bool& value)
{
    CHECK_NULL_VOID(node);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    menuLayoutProperty->UpdateShowDefaultSelectedIcon(value);
}

void ResetShowDefaultSelectedIcon(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    menuLayoutProperty->ResetShowDefaultSelectedIcon();
}

float GetSelectModifiedHeightValue(const RefPtr<FrameNode>& node, const float& value)
{
    CHECK_NULL_RETURN(node, value);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(menuLayoutProperty, value);
    return menuLayoutProperty->GetSelectModifiedHeightValue(value);
}

std::optional<DividerMode> GetItemDividerMode(const RefPtr<FrameNode>& node)
{
    std::optional<DividerMode> dividerMode;
    CHECK_NULL_RETURN(node, dividerMode);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_RETURN(menuLayoutProperty, dividerMode);
    return menuLayoutProperty->GetItemDividerMode();
}

void UpdateSelectMenuModifiedWidth(const RefPtr<FrameNode>& node, const float& value)
{
    CHECK_NULL_VOID(node);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    menuLayoutProperty->UpdateSelectMenuModifiedWidth(value);
}

void UpdateAlignType(const RefPtr<FrameNode>& node, const MenuAlignType& value)
{
    CHECK_NULL_VOID(node);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    menuLayoutProperty->UpdateAlignType(value);
}

void UpdateOffset(const RefPtr<FrameNode>& node, const DimensionOffset& value)
{
    CHECK_NULL_VOID(node);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    menuLayoutProperty->UpdateOffset(value);
}

void UpdateSelectAvoidanceMode(const RefPtr<FrameNode>& node, const AvoidanceMode& value)
{
    CHECK_NULL_VOID(node);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    menuLayoutProperty->UpdateSelectAvoidanceMode(value);
}

void UpdateSelectModifiedHeight(const RefPtr<FrameNode>& node, const float& value)
{
    CHECK_NULL_VOID(node);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    menuLayoutProperty->UpdateSelectModifiedHeight(value);
}

void UpdateItemDividerMode(const RefPtr<FrameNode>& node, const DividerMode& value)
{
    CHECK_NULL_VOID(node);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    menuLayoutProperty->UpdateItemDividerMode(value);
}

void ResetItemDividerMode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    menuLayoutProperty->ResetItemDividerMode();
}

void UpdateExpandingMode(const RefPtr<FrameNode>& node, const SubMenuExpandingMode& value)
{
    CHECK_NULL_VOID(node);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    menuLayoutProperty->UpdateExpandingMode(value);
}

void UpdateMenuWidth(const RefPtr<FrameNode>& node, const Dimension& value)
{
    CHECK_NULL_VOID(node);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    menuLayoutProperty->UpdateMenuWidth(value);
}

void UpdateAlignment(const RefPtr<FrameNode>& node, const OHOS::Ace::Alignment& value)
{
    CHECK_NULL_VOID(node);
    auto menuLayoutProperty = node->GetLayoutProperty<MenuLayoutProperty>();
    CHECK_NULL_VOID(menuLayoutProperty);
    menuLayoutProperty->UpdateAlignment(value);
}

void SetAccessibilityIsShow(const RefPtr<FrameNode>& node, bool isShow)
{
    CHECK_NULL_VOID(node);
    auto menuAccessibilityProperty = node->GetAccessibilityProperty<MenuAccessibilityProperty>();
    CHECK_NULL_VOID(menuAccessibilityProperty);
    menuAccessibilityProperty->SetAccessibilityIsShow(isShow);
}

// MenuModelNG
void SetWidth(FrameNode* frameNode, const Dimension& width)
{
    MenuModelNG::SetWidth(frameNode, width);
}

void SetExpandingMode(FrameNode* frameNode, const SubMenuExpandingMode& expandingMode)
{
    MenuModelNG::SetExpandingMode(frameNode, expandingMode);
}

void SetItemDivider(FrameNode* frameNode, const V2::ItemDivider& divider, const DividerMode& mode)
{
    MenuModelNG::SetItemDivider(frameNode, divider, mode);
}

RefPtr<FrameNode> CreateFrameNode(int32_t innerMenuId, int32_t nodeId)
{
    return FrameNode::CreateFrameNode(
        MENU_ETS_TAG, nodeId, AceType::MakeRefPtr<InnerMenuPattern>(innerMenuId, MENU_ETS_TAG, MenuType::MULTI_MENU));
}

void SetNeedDivider(const RefPtr<FrameNode>& node)
{
    auto menuPattern = node->GetPattern<InnerMenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->SetNeedDivider();
}

void OnModifyDone(const RefPtr<FrameNode>& node)
{
    auto menuPattern = node->GetPattern<InnerMenuPattern>();
    CHECK_NULL_VOID(menuPattern);
    menuPattern->OnModifyDone();
}

} // namespace
namespace InnerModifier {

const ArkUIMenuInnerModifier* GetMenuInnerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIMenuInnerModifier modifier = {
        .isMenuPattern = IsMenuPattern,
        .isContextMenu = IsContextMenu,
        .getPreviewMode = GetPreviewMode,
        .isSelectMenu = IsSelectMenu,
        .hideMenu = HideMenu,
        .getDisappearAnimation = GetDisappearAnimation,
        .getTargetTag = GetTargetTag,
        .getTargetId = GetTargetId,
        .getShowedSubMenu = GetShowedSubMenu,
        .getFirstInnerMenu = GetFirstInnerMenu,
        .getSubMenuDepth = GetSubMenuDepth,
        .getParentMenuItem = GetParentMenuItem,
        .removeParentHoverStyle = RemoveParentHoverStyle,
        .setShowedSubMenu = SetShowedSubMenu,
        .isSubMenu = IsSubMenu,
        .isSelectOverlaySubMenu = IsSelectOverlaySubmenu,
        .setDisappearAnimation = SetDisappearAnimation,
        .isSelectOverlayCustomMenu = IsSelectOverlayCustomMenu,
        .isSelectOverlayRightClickMenu = IsSelectOverlayRightClickMenu,
        .getLayoutProperty = GetLayoutProperty,
        .focusViewShow = FocusViewShow,
        .showStackMenuDisappearAnimation = ShowStackMenuDisappearAnimation,
        .setSubMenuShow = SetSubMenuShow,
        .setCustomNode = SetCustomNode,
        .getEmbeddedMenuItems = GetEmbeddedMenuItems,
        .getIsShowHoverImage = GetIsShowHoverImage,
        .getPreviewBeforeAnimationScale = GetPreviewBeforeAnimationScale,
        .getPreviewAfterAnimationScale = GetPreviewAfterAnimationScale,
        .getLastPlacement = GetLastPlacement,
        .duplicateMenuNode = DuplicateMenuNode,
        .removeResObj = RemoveResObj,
        .getResCacheMapByKey = GetResCacheMapByKey,
        .addResCache = AddResCache,
        .addResObj = AddResObj,
        .getMenuPathParams = GetMenuPathParams,
        .setIsSelectMenu = SetIsSelectMenu,
        .setDisableMenuBgColorByUser = SetDisableMenuBgColorByUser,
        .updateSelectParam = UpdateSelectParam,
        .getOptions = GetOptions,
        .setSelectProperties = SetSelectProperties,
        .setBuilderFunc = SetBuilderFunc,
        .resetBuilderFunc = ResetBuilderFunc,
        .updateSelectIndex = UpdateSelectIndex,
        .updateSelectOptionTextByIndex = UpdateSelectOptionTextByIndex,
        .updateSelectOptionIconByIndex = UpdateSelectOptionIconByIndex,
        .setIsWidthModifiedBySelect = SetIsWidthModifiedBySelect,
        .setHasOptionWidth = SetHasOptionWidth,
        .setIsHeightModifiedBySelect = SetIsHeightModifiedBySelect,
        .updateMenuItemDivider = UpdateMenuItemDivider,
        .addMenuItemNode = AddMenuItemNode,
        .hideAllEmbeddedMenuItems = HideAllEmbeddedMenuItems,
        .setMenuShow = SetMenuShow,
        .showMenuDisappearAnimation = ShowMenuDisappearAnimation,
        .getMenuItems = GetMenuItems,
        .setSelectOverlayExtensionMenuShow = SetSelectOverlayExtensionMenuShow,
        .getOrCreateMenuNode = GetOrCreateMenuNode,
        .setParentMenuItem = SetParentMenuItem,
        .getHoverImageAfterScaleWidth = GetHoverImageAfterScaleWidth,
        .getHoverImageAfterScaleHeight = GetHoverImageAfterScaleHeight,
        .getStackAfterScaleActualWidth = GetStackAfterScaleActualWidth,
        .getStackAfterScaleActualHeight = GetStackAfterScaleActualHeight,
        .updateMenuOffset = UpdateMenuOffset,
        .resetMenuPlacement = ResetMenuPlacement,
        .getExpandingMode = GetExpandingMode,
        .updateTargetSize = UpdateTargetSize,
        .updateShowInSubWindow = UpdateShowInSubWindow,
        .updateShowDefaultSelectedIcon = UpdateShowDefaultSelectedIcon,
        .resetShowDefaultSelectedIcon = ResetShowDefaultSelectedIcon,
        .getSelectModifiedHeightValue = GetSelectModifiedHeightValue,
        .getItemDividerMode = GetItemDividerMode,
        .updateSelectMenuModifiedWidth = UpdateSelectMenuModifiedWidth,
        .updateAlignType = UpdateAlignType,
        .updateOffset = UpdateOffset,
        .updateSelectAvoidanceMode = UpdateSelectAvoidanceMode,
        .updateSelectModifiedHeight = UpdateSelectModifiedHeight,
        .updateItemDividerMode = UpdateItemDividerMode,
        .resetItemDividerMode = ResetItemDividerMode,
        .updateExpandingMode = UpdateExpandingMode,
        .updateMenuWidth = UpdateMenuWidth,
        .updateAlignment = UpdateAlignment,
        .setAccessibilityIsShow = SetAccessibilityIsShow,
        .setWidth = SetWidth,
        .setExpandingMode = SetExpandingMode,
        .setItemDivider = SetItemDivider,
        .createMenu = NG::MenuModelNG::CreateMenu,
        .menuCreateFrameNode = CreateFrameNode,
        .menuSetNeedDivider = SetNeedDivider,
        .menuOnModifyDone = OnModifyDone,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace InnerModifier
} // namespace OHOS::Ace::NG