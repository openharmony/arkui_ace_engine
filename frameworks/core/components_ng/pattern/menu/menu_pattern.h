/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_PATTERN_H

#include <optional>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/symbol_modifier.h"
#include "core/components_ng/pattern/menu/menu_accessibility_property.h"
#include "core/components_ng/pattern/menu/menu_layout_algorithm.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_paint_method.h"
#include "core/components_ng/pattern/menu/menu_paint_property.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_paint_method.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_paint_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select/select_model.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/menu_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

constexpr int32_t DEFAULT_CLICK_DISTANCE = 15;
constexpr uint32_t MAX_SEARCH_DEPTH = 5;
constexpr double MENU_ANIMATION_MAX_SCALE = 1.0f;
constexpr double MENU_ANIMATION_MIN_OPACITY = 0.0f;
constexpr double MENU_ANIMATION_MAX_OPACITY = 1.0f;
namespace OHOS::Ace::NG {

struct SelectProperties {
    std::string value;
    std::string icon;
    RefPtr<SymbolModifier> symbolModifier;
    int index;
    bool selected = false;
    bool selectEnable = true;
};

struct MenuItemInfo {
    OffsetF originOffset = OffsetF();
    OffsetF endOffset = OffsetF();
    bool isFindTargetId = false;
};

struct PreviewMenuAnimationInfo {
    BorderRadiusProperty borderRadius = BorderRadiusProperty(Dimension(-1.0f));

    // for hoverScale animation
    float clipRate = -1.0f;
};

class MenuPattern : public Pattern, public FocusView {
    DECLARE_ACE_TYPE(MenuPattern, Pattern, FocusView);

public:
    MenuPattern(int32_t targetId, std::string tag, MenuType type)
        : targetId_(targetId), targetTag_(std::move(tag)), type_(type)
    {}
    ~MenuPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    std::list<int32_t> GetRouteOfFirstScope() override
    {
        return { 0, 0 };
    }

    bool IsEnableMatchParent() override
    {
        return IsMultiMenu();
    }

    bool IsEnableChildrenMatchParent() override
    {
        return IsMultiMenu();
    }

    bool IsEnableFix() override
    {
        return IsMultiMenu();
    }

    bool ChildPreMeasureHelperEnabled() override
    {
        return true;
    }

    bool PostponedTaskForIgnoreEnabled() override
    {
        return true;
    }

    bool IsEnabledContentForFixIdeal()
    {
        return IsMultiMenu();
    }

    bool IsFocusViewLegal() override
    {
        return type_ == MenuType::MENU || type_ == MenuType::CONTEXT_MENU || type_ == MenuType::SUB_MENU;
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<MenuLayoutProperty>();
    }

    RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<MenuAccessibilityProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<MenuPaintProperty>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return AceType::MakeRefPtr<MenuPaintMethod>();
    }

    MenuType GetMenuType() const
    {
        return type_;
    }

    bool IsContextMenu() const
    {
        return type_ == MenuType::CONTEXT_MENU;
    }

    void SetPreviewMode(MenuPreviewMode mode)
    {
        previewMode_ = mode;
    }

    MenuPreviewMode GetPreviewMode() const
    {
        return previewMode_;
    }

    void SetPreviewBeforeAnimationScale(float scaleBeforeAnimation)
    {
        previewAnimationOptions_.scaleFrom = scaleBeforeAnimation;
    }

    float GetPreviewBeforeAnimationScale() const
    {
        return previewAnimationOptions_.scaleFrom;
    }

    void SetPreviewAfterAnimationScale(float scaleAfterAnimation)
    {
        previewAnimationOptions_.scaleTo = scaleAfterAnimation;
    }

    float GetPreviewAfterAnimationScale() const
    {
        return previewAnimationOptions_.scaleTo;
    }

    void SetIsShowHoverImage(bool isShow)
    {
        isShowHoverImage_ = isShow;
    }

    bool GetIsShowHoverImage() const
    {
        return isShowHoverImage_;
    }

    bool IsNavigationMenu() const
    {
        return type_ == MenuType::NAVIGATION_MENU;
    }

    bool IsMultiMenu() const
    {
        return type_ == MenuType::MULTI_MENU;
    }

    bool IsDesktopMenu() const
    {
        return type_ == MenuType::DESKTOP_MENU;
    }

    bool IsMenu() const
    {
        return type_ == MenuType::MENU;
    }

    bool IsSubMenu() const
    {
        return type_ == MenuType::SUB_MENU;
    }

    bool IsSelectOverlayExtensionMenu() const
    {
        return type_ == MenuType::SELECT_OVERLAY_EXTENSION_MENU;
    }

    bool IsSelectOverlayCustomMenu() const
    {
        return type_ == MenuType::SELECT_OVERLAY_CUSTOM_MENU;
    }

    bool IsSelectOverlaySubMenu() const
    {
        return type_ == MenuType::SELECT_OVERLAY_SUB_MENU;
    }

    bool IsSelectOverlayRightClickMenu() const
    {
        return type_ == MenuType::SELECT_OVERLAY_RIGHT_CLICK_MENU;
    }

    void SetParentMenuItem(const RefPtr<FrameNode>& parentMenuItem)
    {
        parentMenuItem_ = parentMenuItem;
    }

    RefPtr<FrameNode> GetParentMenuItem()
    {
        return parentMenuItem_;
    }

    int32_t GetTargetId() const
    {
        return targetId_;
    }

    const std::string& GetTargetTag() const
    {
        return targetTag_;
    }

    void SetIsSelectMenu(bool isSelectMenu)
    {
        isSelectMenu_ = isSelectMenu;
    }
    bool IsSelectMenu() const
    {
        return isSelectMenu_;
    }

    void SetHasOptionWidth(bool hasOptionWidth)
    {
        hasOptionWidth_ = hasOptionWidth;
    }

    bool GetHasOptionWidth()
    {
        return hasOptionWidth_;
    }

    void AddOptionNode(const RefPtr<FrameNode>& option)
    {
        CHECK_NULL_VOID(option);
        options_.emplace_back(option);
    }

    int32_t GetBuilderId()
    {
        auto node = builderNode_.Upgrade();
        CHECK_NULL_RETURN(node, -1);
        return node->GetId();
    }

    void PopOptionNode()
    {
        if (options_.empty()) {
            LOGW("options is empty.");
            return;
        }
        options_.pop_back();
    }

    const std::vector<RefPtr<FrameNode>>& GetOptions() const
    {
        return options_;
    }

    std::vector<RefPtr<FrameNode>>& GetEmbeddedMenuItems()
    {
        return embeddedMenuItems_;
    }

    void AddEmbeddedMenuItem(const RefPtr<FrameNode>& menuItem)
    {
        embeddedMenuItems_.emplace_back(menuItem);
    }

    void RemoveEmbeddedMenuItem(const RefPtr<FrameNode>& menuItem)
    {
        auto iter = std::find(embeddedMenuItems_.begin(), embeddedMenuItems_.end(), menuItem);
        if (iter != embeddedMenuItems_.end()) {
            embeddedMenuItems_.erase(iter);
        }
    }

    void RemoveParentHoverStyle();

    void UpdateSelectParam(const std::vector<SelectParam>& params);

    void SetNeedHideAfterTouch(bool needHideAfterTouch)
    {
        needHideAfterTouch_ = needHideAfterTouch;
    }

    void HideMenu(const HideMenuType& reason)
    {
        HideMenu(false, OffsetF(), reason);
    }

    void HideMenu(bool isMenuOnTouch = false, OffsetF position = OffsetF(),
        const HideMenuType& reason = HideMenuType::NORMAL) const;

    bool HideStackExpandMenu(const OffsetF& position) const;

    void HideStackMenu() const;

    void MountOption(const RefPtr<FrameNode>& option);

    void RemoveOption();
    RefPtr<FrameNode> DuplicateMenuNode(const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam);

    RefPtr<FrameNode> GetMenuColumn() const;

    void SetShowedSubMenu(const RefPtr<FrameNode>& subMenu)
    {
        showedSubMenu_ = subMenu;
    }
    const RefPtr<FrameNode>& GetShowedSubMenu() const
    {
        return showedSubMenu_;
    }

    void SetIsWidthModifiedBySelect(bool isModified)
    {
        isWidthModifiedBySelect_ = isModified;
    }

    bool IsWidthModifiedBySelect() const
    {
        return isWidthModifiedBySelect_;
    }

    float GetSelectMenuWidth();
    void HideSubMenu();
    void OnModifyDone() override;

    // acquire first menu node in wrapper node by submenu node
    RefPtr<MenuPattern> GetMainMenuPattern() const;
    uint32_t GetInnerMenuCount() const;
    void OnColorConfigurationUpdate() override;

    RefPtr<FrameNode> GetMenuWrapper() const;
    RefPtr<FrameNode> GetFirstInnerMenu() const;
    void DumpInfo() override;
    void DumpInfo(std::unique_ptr<JsonValue>& json) override;
    void DumpSimplifyInfo(std::shared_ptr<JsonValue>& json) override {}
    void SetFirstShow()
    {
        isFirstShow_ = true;
    }

    bool GetIsFirstShow() const
    {
        return isFirstShow_;
    }

    void SetOriginOffset(const OffsetF& offset)
    {
        originOffset_ = offset;
    }

    void SetEndOffset(const OffsetF& offset)
    {
        endOffset_ = offset;
    }

    OffsetF GetEndOffset() const
    {
        return endOffset_;
    }

    void SetSelectOverlayExtensionMenuShow()
    {
        isExtensionMenuShow_ = true;
    }

    void SetDisappearAnimation(bool hasAnimation)
    {
        // false：exit from BOTTOM to TOP
        // true：exit from LEFT_BOTTOM to RIGHT_TOP
        hasAnimation_ = hasAnimation;
    }

    bool GetDisappearAnimation() const
    {
        return hasAnimation_;
    }

    void SetSubMenuShow(bool subMenuShowed)
    {
        isSubMenuShow_ = subMenuShowed;
    }

    void SetMenuShow()
    {
        isMenuShow_ = true;
    }

    void SetPreviewOriginOffset(const OffsetF& offset)
    {
        previewOriginOffset_ = offset;
    }

    OffsetF GetPreviewOriginOffset() const
    {
        return previewOriginOffset_;
    }

    void SetPreviewRect(RectF rect)
    {
        previewRect_ = rect;
    }

    RectF GetPreviewRect() const
    {
        return previewRect_;
    }

    void SetPreviewIdealSize(SizeF size)
    {
        previewIdealSize_ = size;
    }

    SizeF GetPreviewIdealSize() const
    {
        return previewIdealSize_;
    }

    void SetHasLaid(bool hasLaid)
    {
        hasLaid_ = hasLaid;
    }

    bool HasLaid() const
    {
        return hasLaid_;
    }

    void SetTargetSize(const SizeF& size)
    {
        targetSize_ = size;
    }

    SizeF GetTargetSize() const
    {
        return targetSize_;
    }

    void SetTargetOffset(const OffsetF& offset)
    {
        targetOffset_ = offset;
    }

    OffsetF GetTargetOffset() const
    {
        return targetOffset_;
    }

    void SetIsHeightModifiedBySelect(bool isModified)
    {
        isHeightModifiedBySelect_ = isModified;
    }

    bool IsHeightModifiedBySelect() const
    {
        return isHeightModifiedBySelect_;
    }

    bool GetMenuExpandDisplay() const
    {
        return expandDisplay_;
    }

    void ShowMenuDisappearAnimation();
    void ShowStackMenuDisappearAnimation(const RefPtr<FrameNode>& menuNode,
        const RefPtr<FrameNode>& subMenuNode, AnimationOption& option) const;

    void SetBuilderFunc(SelectMakeCallback&& makeFunc)
    {
        makeFunc_ = std::move(makeFunc);
    }

    void ResetBuilderFunc()
    {
        makeFunc_ = std::nullopt;
    }

    void UpdateSelectIndex(int32_t index);

    void SetSelectProperties(const std::vector<SelectParam>& params)
    {
        auto list = selectProperties_;
        selectParams_ = params;
        selectProperties_.clear();
        for (size_t i = 0; i < params.size(); i++) {
            SelectProperties selectProperty;
            selectProperty.value = params[i].text;
            selectProperty.icon = params[i].icon;
            selectProperty.symbolModifier = params[i].symbolModifier;
            selectProperty.index = static_cast<int>(i);
            if (i < list.size()) {
                selectProperty.selected = list[i].selected;
                selectProperty.selectEnable = list[i].selectEnable;
            }
            selectProperties_.push_back(selectProperty);
        }
    }

    ShadowStyle GetMenuDefaultShadowStyle()
    {
        auto shadowStyle = ShadowStyle::OuterDefaultMD;

        auto host = GetHost();
        CHECK_NULL_RETURN(host, shadowStyle);
        auto pipeline = host->GetContextRefPtr();
        CHECK_NULL_RETURN(pipeline, shadowStyle);
        auto menuTheme = pipeline->GetTheme<MenuTheme>();
        CHECK_NULL_RETURN(menuTheme, shadowStyle);
        shadowStyle = menuTheme->GetMenuShadowStyle();
        return shadowStyle;
    }

    bool GetShadowFromTheme(ShadowStyle shadowStyle, Shadow& shadow);

    bool UseContentModifier()
    {
        return builderNode_.Upgrade() != nullptr;
    }

    void FireBuilder();

    BorderRadiusProperty CalcIdealBorderRadius(const BorderRadiusProperty& borderRadius, const SizeF& menuSize);

    void OnItemPressed(const RefPtr<UINode>& parent, int32_t index, bool press, bool hover = false);

    RefPtr<FrameNode> GetLastSelectedItem()
    {
        return lastSelectedItem_;
    }

    void SetLastSelectedItem(const RefPtr<FrameNode>& lastSelectedItem)
    {
        lastSelectedItem_ = lastSelectedItem;
    }
    void UpdateLastPosition(std::optional<OffsetF> lastPosition)
    {
        lastPosition_ = lastPosition;
    }

    void UpdateLastPlacement(std::optional<Placement> lastPlacement)
    {
        lastPlacement_ = lastPlacement;
    }

    std::optional<Placement> GetLastPlacement()
    {
        return lastPlacement_;
    }

    void SetIsEmbedded()
    {
        isEmbedded_ = true;
    }
    bool IsEmbedded()
    {
        return isEmbedded_;
    }
    void SetIsStackSubmenu()
    {
        isStackSubmenu_ = true;
    }
    bool IsStackSubmenu()
    {
        return isStackSubmenu_;
    }
    void SetMenuWindowRect(const Rect& menuWindowRect)
    {
        menuWindowRect_ = menuWindowRect;
    }
    Rect GetMenuWindowRect() const
    {
        return menuWindowRect_;
    }

    void SetMenuLayoutParam(const PreviewMenuParam& layoutParam)
    {
        layoutParam_ = layoutParam;
    }

    PreviewMenuParam GetMenuLayoutParam() const
    {
        return layoutParam_;
    }

    OffsetF GetPreviewMenuDisappearPosition()
    {
        return disappearOffset_;
    }

    void UpdateMenuPathParams(std::optional<MenuPathParams> pathParams);

    std::optional<MenuPathParams> GetMenuPathParams()
    {
        return pathParams_;
    }

    void SetCustomNode(WeakPtr<UINode> customNode)
    {
        customNode_ = customNode;
    }

    RefPtr<UINode> GetCustomNode() const
    {
        return customNode_.Upgrade();
    }

    void UpdateSelectOptionTextByIndex(int32_t index, const std::string& text);
    void UpdateSelectOptionIconByIndex(int32_t index, const std::string& icon);

    void InitPreviewMenuAnimationInfo(const RefPtr<MenuTheme>& menuTheme);

    float GetSelectMenuWidthFromTheme() const;

    bool IsSelectOverlayDefaultModeRightClickMenu();
    void RemoveLastNodeDivider(const RefPtr<UINode>& lastNode);
    void UpdateMenuItemDivider();
    void UpdateDividerProperty(const RefPtr<FrameNode>& dividerNode, const std::optional<V2::ItemDivider>& divider);
    RefPtr<FrameNode> GetFirstMenuItem();
    RefPtr<FrameNode> GetLastMenuItem();
    std::pair<float, float> GetPreviewPositionY();

    float GetTranslateYForStack()
    {
        return translateYForStack_;
    }

    void SetTranslateYForStack(float tmp)
    {
        translateYForStack_ = tmp;
    }

    float GetOriginMenuYForStack()
    {
        return originMenuYForStack_;
    }

    void SetOriginMenuYForStack(float tmp)
    {
        originMenuYForStack_ = tmp;
    }

    float GetOriginPreviewYForStack()
    {
        return originPreviewYForStack_;
    }

    void SetOriginPreviewYForStack(float tmp)
    {
        originPreviewYForStack_ = tmp;
    }

    void SetDisableMenuBgColorByUser(bool isSetByUser = false)
    {
        isDisableMenuBgColorByUser_ = isSetByUser;
    }

    void SetSubMenuDepth(int32_t depth)
    {
        subMenuDepth_ = depth;
    }

    int32_t GetSubMenuDepth() const
    {
        return subMenuDepth_;
    }

protected:
    void UpdateMenuItemChildren(const RefPtr<UINode>& host, RefPtr<UINode>& previousNode);
    void SetMenuAttribute(RefPtr<FrameNode>& host);
    void SetAccessibilityAction();
    void SetType(MenuType value)
    {
        type_ = value;
    }
    void ResetNeedDivider()
    {
        isNeedDivider_ = false;
    }
    virtual void InitTheme(const RefPtr<FrameNode>& host);
    virtual void UpdateBorderRadius(const RefPtr<FrameNode>& menuNode, const BorderRadiusProperty& borderRadius);

private:
    void UpdateMenuDividerWithMode(const RefPtr<UINode>& previousNode, const RefPtr<UINode>& currentNode,
        const RefPtr<MenuLayoutProperty>& property, int32_t& index);
    void AddGroupHeaderDivider(RefPtr<UINode>& previousNode, const RefPtr<UINode>& currentNode,
        const RefPtr<MenuLayoutProperty>& property, int32_t& index);
    void AddGroupFooterDivider(RefPtr<UINode>& previousNode, const RefPtr<UINode>& currentNode,
        const RefPtr<MenuLayoutProperty>& property, int32_t& index);
    void OnAttachToFrameNode() override;
    int32_t RegisterHalfFoldHover(const RefPtr<FrameNode>& menuNode);
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnDetachFromMainTree() override;

    void RegisterOnTouch();
    void OnTouchEvent(const TouchEventInfo& info);
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    // If CustomBuilder is declared with <Menu> and <MenuItem>,
    // reset outer menu container and only apply theme on the inner <Menu> node.
    void ResetTheme(const RefPtr<FrameNode>& host, bool resetForDesktopMenu);
    void ResetScrollTheme(const RefPtr<FrameNode>& host);
    void ResetThemeByInnerMenuCount();
    void CopyMenuAttr(const RefPtr<FrameNode>& menuNode) const;

    void RegisterOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event);

    void DisableTabInMenu();

    Offset GetTransformCenter() const;
    OffsetF GetPreviewMenuAnimationOffset(const OffsetF& previewCenter, const SizeF& previewSize, float scale) const;
    void ShowPreviewMenuAnimation();
    void ShowPreviewPositionAnimation(AnimationOption& option, int32_t delay);
    void ShowPreviewMenuScaleAnimation(const RefPtr<MenuTheme>& menuTheme, AnimationOption& option, int32_t delay);
    void ShowMenuAppearAnimation();
    void ShowStackMenuAppearAnimation();
    std::pair<OffsetF, OffsetF> GetMenuOffset(const RefPtr<FrameNode>& mainMenu,
        const RefPtr<FrameNode>& subMenu, bool isNeedRestoreNodeId = false) const;
    MenuItemInfo GetInnerMenuOffset(const RefPtr<UINode>& child, const RefPtr<FrameNode>& subMenu,
        bool isNeedRestoreNodeId) const;
    MenuItemInfo GetMenuItemInfo(const RefPtr<UINode>& child, const RefPtr<FrameNode>& subMenu,
        bool isNeedRestoreNodeId) const;
    std::vector<RefPtr<RenderContext>> GetOtherMenuItemContext(const RefPtr<FrameNode>& subMenuNode) const;
    void ShowArrowRotateAnimation() const;
    void ShowArrowReverseRotateAnimation() const;
    RefPtr<FrameNode> GetArrowNode(const RefPtr<FrameNode>& host) const; // arrowNode in subMenu

    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void HandleDragEnd(float offsetX, float offsetY, float velocity);
    void HandleScrollDragEnd(float offsetX, float offsetY, float velocity);
    RefPtr<UINode> GetSyntaxNode(const RefPtr<UINode>& parent);
    RefPtr<UINode> GetForEachMenuItem(const RefPtr<UINode>& parent, bool next);
    RefPtr<UINode> GetOutsideForEachMenuItem(const RefPtr<UINode>& forEachNode, bool next);
    RefPtr<UINode> GetIfElseMenuItem(const RefPtr<UINode>& parent, bool next);
    void HandleNextPressed(const RefPtr<UINode>& parent, int32_t index, bool press, bool hover);
    void HandlePrevPressed(const RefPtr<UINode>& parent, int32_t index, bool press);
    void SetMenuBackGroundStyle(const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam);
    void UpdateMenuBorderAndBackgroundBlur();

    RefPtr<FrameNode> BuildContentModifierNode(int index);
    bool IsMenuScrollable() const;
    void UpdateClipPath(const RefPtr<LayoutWrapper>& dirty);
    RefPtr<FrameNode> GetTitleContentNode(const RefPtr<FrameNode>& subMenuNode) const;
    void ShowStackSubMenuAnimation(const RefPtr<FrameNode>& mainMenu, const RefPtr<FrameNode>& subMenuNode);
    void ShowStackMainMenuAnimation(const RefPtr<FrameNode>& mainMenu, const RefPtr<FrameNode>& subMenuNode,
        const RefPtr<FrameNode>& menuWrapper);
    void ShowStackMainMenuOpacityAnimation(const RefPtr<FrameNode>& mainMenu);
    void ShowStackSubMenuDisappearAnimation(const RefPtr<FrameNode>& menuNode,
        const RefPtr<FrameNode>& subMenuNode) const;
    void ShowStackMainMenuDisappearOpacityAnimation(const RefPtr<FrameNode>& menuNode,
        AnimationOption& option) const;
    void ShowStackMainMenuDisappearAnimation(const RefPtr<FrameNode>& menuNode,
        const RefPtr<FrameNode>& subMenuNode, AnimationOption& option) const;

    RefPtr<ClickEvent> onClick_;
    RefPtr<TouchEventImpl> onTouch_;
    std::optional<Offset> lastTouchOffset_;
    const int32_t targetId_ = -1;
    const std::string targetTag_;
    MenuType type_ = MenuType::MENU;
    std::vector<SelectProperties> selectProperties_;
    std::vector<SelectParam> selectParams_;
    std::optional<SelectMakeCallback> makeFunc_;

    RefPtr<FrameNode> parentMenuItem_;
    RefPtr<FrameNode> showedSubMenu_;
    std::vector<RefPtr<FrameNode>> options_;
    std::optional<int32_t> foldStatusChangedCallbackId_;
    std::optional<int32_t> halfFoldHoverCallbackId_;

    bool isSelectMenu_ = false;
    MenuPreviewMode previewMode_ = MenuPreviewMode::NONE;
    MenuPreviewAnimationOptions previewAnimationOptions_;
    bool isShowHoverImage_ = false;
    bool isFirstShow_ = false;
    bool isExtensionMenuShow_ = false;
    bool isSubMenuShow_ = false;
    bool isMenuShow_ = false;
    bool hasAnimation_ = true;
    bool needHideAfterTouch_ = true;

    std::optional<OffsetF> lastPosition_;
    std::optional<Placement> lastPlacement_;
    OffsetF originOffset_;
    OffsetF endOffset_;
    OffsetF disappearOffset_;
    OffsetF previewOriginOffset_;
    RectF previewRect_;
    SizeF previewIdealSize_;
    OffsetF statusOriginOffset_;

    WeakPtr<FrameNode> builderNode_;
    bool isWidthModifiedBySelect_ = false;
    bool isHeightModifiedBySelect_ = false;
    bool hasLaid_ = false;
    bool hasOptionWidth_ = false;
    OffsetF targetOffset_;
    SizeF targetSize_;
    bool expandDisplay_ = false;
    RefPtr<FrameNode> lastSelectedItem_ = nullptr;
    bool isEmbedded_ = false;
    std::vector<RefPtr<FrameNode>> embeddedMenuItems_;
    bool isStackSubmenu_ = false;
    bool isNeedDivider_ = false;
    Rect menuWindowRect_;
    PreviewMenuParam layoutParam_;
    WeakPtr<UINode> customNode_ = nullptr;
    std::optional<MenuPathParams> pathParams_ = std::nullopt;
    float translateYForStack_ = 0.0f;
    float originMenuYForStack_ = 0.0f;
    float originPreviewYForStack_ = 0.0f;
    bool isDisableMenuBgColorByUser_ = false;

    // only used for Side sub menu
    int32_t subMenuDepth_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(MenuPattern);
};

// pattern of inner menu, corersponds to <Menu> tag in the frontend
class InnerMenuPattern : public MenuPattern {
    DECLARE_ACE_TYPE(InnerMenuPattern, MenuPattern);

public:
    InnerMenuPattern(int32_t targetId, std::string tag, MenuType type) : MenuPattern(targetId, std::move(tag), type) {}
    ~InnerMenuPattern() override = default;
    void OnModifyDone() override;
    void BeforeCreateLayoutWrapper() override;
    bool isHalfFoldStatus_ = false;

    void RecordItemsAndGroups();

    const std::list<WeakPtr<UINode>>& GetItemsAndGroups() const
    {
        return itemsAndGroups_;
    }

private:
    void InitTheme(const RefPtr<FrameNode>& host) override;
    void UpdateBorderRadius(const RefPtr<FrameNode>& menuNode, const BorderRadiusProperty& borderRadius) override;
    uint32_t FindSiblingMenuCount();
    void ApplyDesktopMenuTheme();
    void ApplyMultiMenuTheme();

    void InitDefaultBorder(const RefPtr<FrameNode>& host);

    // Record menu's items and groups at first level,
    // use for group header and footer padding
    std::list<WeakPtr<UINode>> itemsAndGroups_;

    ACE_DISALLOW_COPY_AND_MOVE(InnerMenuPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_PATTERN_H
