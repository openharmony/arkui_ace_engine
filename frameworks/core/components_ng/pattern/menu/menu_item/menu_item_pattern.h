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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_PATTERN_H

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components/slider/render_slider.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_accessibility_property.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_event_hub.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_layout_algorithm.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_layout_property.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_paint_method.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_paint_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {
enum class ShowSubMenuType : int32_t {
    DEFAULT = 0,
    HOVER = 1,
    CLICK = 2,
    LONG_PRESS = 3,
    KEY_DPAD_RIGHT = 4,
    ACTION = 5
};
class ACE_EXPORT MenuItemPattern : public Pattern {
    DECLARE_ACE_TYPE(MenuItemPattern, Pattern);

public:
    MenuItemPattern(bool isOptionPattern = false, int index = -1) : index_(index), isOptionPattern_(isOptionPattern) {}
    ~MenuItemPattern() override = default;

    inline bool IsAtomicNode() const override
    {
        return false;
    }

    inline FocusPattern GetFocusPattern() const override
    {
        FocusPattern focusPattern = { FocusType::NODE, true, FocusStyleType::INNER_BORDER };
        auto host = GetHost();
        CHECK_NULL_RETURN(host, focusPattern);
        auto pipelineContext = host->GetContext();
        CHECK_NULL_RETURN(pipelineContext, focusPattern);
        if (isOptionPattern_) {
            auto selectTheme = pipelineContext->GetTheme<SelectTheme>();
            CHECK_NULL_RETURN(selectTheme, focusPattern);
            auto focusStyleType =
                static_cast<FocusStyleType>(static_cast<int32_t>(selectTheme->GetOptionFocusStyleType_()));
            focusPattern.SetStyleType(focusStyleType);
            return focusPattern;
        } else {
            auto menuTheme = pipelineContext->GetTheme<MenuTheme>();
            CHECK_NULL_RETURN(menuTheme, focusPattern);
            auto focusStyleType =
                static_cast<FocusStyleType>(static_cast<int32_t>(menuTheme->GetFocusStyleType()));
            focusPattern.SetStyleType(focusStyleType);
            return focusPattern;
        }
    }

    inline RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<MenuItemEventHub>();
    }

    inline RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<MenuItemLayoutProperty>();
    }

    inline RefPtr<AccessibilityProperty> CreateAccessibilityProperty() override
    {
        return MakeRefPtr<MenuItemAccessibilityProperty>(isOptionPattern_);
    }

    inline RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<MenuItemLayoutAlgorithm>(isOptionPattern_);
    }

    inline RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<MenuItemPaintMethod>(isOptionPattern_);
    }

    inline RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<MenuItemPaintProperty>(isOptionPattern_);
    }

    void MarkIsSelected(bool isSelected);
    void SetSelected(bool isSelected)
    {
        isSelected_ = isSelected;
        if (!isOptionPattern_) {
            GetHost()->MarkModifyDone();
        }
    }

    bool IsSelected() const
    {
        return isSelected_;
    }

    void SetSubBuilder(const std::function<void()>& subBuilderFunc)
    {
        subBuilderFunc_ = subBuilderFunc;
    }

    std::function<void()>& GetSubBuilder()
    {
        return subBuilderFunc_;
    }

    bool IsSubMenuShowed() const
    {
        return isSubMenuShowed_;
    }

    void SetIsSubMenuShowed(bool isSubMenuShowed)
    {
        isSubMenuShowed_ = isSubMenuShowed;
    }

    bool IsSubMenuHovered() const
    {
        return isSubMenuHovered_;
    }

    void SetIsSubMenuHovered(bool isSubMenuHovered)
    {
        isSubMenuHovered_ = isSubMenuHovered;
    }

    void AddHoverRegions(const OffsetF& topLeftPoint, const OffsetF& bottomRightPoint);

    bool IsInHoverRegions(double x, double y);

    void ClearHoverRegions()
    {
        hoverRegions_.clear();
    }

    void ResetWrapperMouseEvent()
    {
        wrapperMouseEvent_.Reset();
    }

    void SetChange()
    {
        isSelected_ = !isSelected_;
    }

    bool IsChange() const
    {
        return isChanged_;
    }

    void CloseMenu();

    RefPtr<FrameNode> GetContentNode()
    {
        return content_;
    }

    RefPtr<FrameNode> GetLabelNode()
    {
        return label_;
    }

    void PlayBgColorAnimation(bool isHoverChange = true);
    void SetBgBlendColor(const Color& color)
    {
        bgBlendColor_ = color;
    }
    Color GetBgBlendColor() const
    {
        return bgBlendColor_;
    }
    bool IsDisabled();

    RefPtr<FrameNode> GetMenu(bool needTopMenu = false);
    RefPtr<MenuPattern> GetMenuPattern(bool needTopMenu = false);
    void UpdateTextNodes();

    void OnAttachToFrameNode() override;
    void OnModifyDone() override;
    void OnMountToParentDone() override;

    bool HasSelectIcon() const
    {
        return selectIcon_ != nullptr;
    }
    bool HasStartIcon() const
    {
        return startIcon_ != nullptr;
    }

    void SetClickMenuItemId(int32_t id)
    {
        clickMenuItemId_ = id;
    }

    int32_t GetClickMenuItemId() const
    {
        return clickMenuItemId_;
    }

    void SetOnClickAIMenuItem(std::function<void()> onClickAIMenuItem)
    {
        onClickAIMenuItem_ = onClickAIMenuItem;
    }

    void OnVisibleChange(bool isVisible) override;
    void InitLongPressEvent();
    void UpdateNeedDivider(bool need);
    void SetIndex(int32_t index)
    {
        index_ = index;
    }
    float GetDividerStroke();

    SubMenuExpandingMode GetExpandingMode()
    {
        return expandingMode_;
    }
    bool IsSubMenu();
    bool IsEmbedded();
    void SetIsStackSubmenuHeader()
    {
        isStackSubmenuHeader_ = true;
    }
    bool IsStackSubmenuHeader()
    {
        return isStackSubmenuHeader_;
    }
    RefPtr<FrameNode> FindTouchedEmbeddedMenuItem(const OffsetF& position);
    void OnHover(bool isHover);
    void NotifyPressStatus(bool isPress);
    void SetBgColor(const Color& color);
    void SetFontColor(const Color& color);
    void SetFontFamily(const std::vector<std::string>& value);
    void SetFontSize(const Dimension& value);
    void SetFontWeight(const FontWeight& value);
    void SetItalicFontStyle(const Ace::FontStyle& value);
    void SetSelected(int32_t selected)
    {
        rowSelected_ = selected;
    }
    void SetBorderColor(const Color& color);
    Color GetBorderColor() const;
    void SetBorderWidth(const Dimension& value);
    Dimension GetBorderWidth() const;
    void UpdateIcon(const std::string& src, const std::function<void(WeakPtr<NG::FrameNode>)> symbolIcon);
    void UpdateNextNodeDivider(bool needDivider);
    void UpdateText(const std::string& content);
    Color GetBgColor();
    Color GetFontColor();
    Dimension GetFontSize();
    Ace::FontStyle GetItalicFontStyle();
    FontWeight GetFontWeight();
    std::vector<std::string> GetFontFamily();
    std::string GetText();
    // XTS inspector functions
    std::string InspectorGetFont();
    float GetSelectOptionWidth();

    inline void SetIcon(const std::string& src)
    {
        iconSrc_ = src;
    }
    inline const std::string& GetIcon()
    {
        return iconSrc_;
    }
    inline void SetIsHover(bool isHover)
    {
        isHover_ = isHover;
    }
    inline bool IsHover() const
    {
        return isHover_;
    }
    inline void SetMenu(const WeakPtr<FrameNode>& menuWeak)
    {
        menuWeak_ = menuWeak;
    }
    inline const WeakPtr<FrameNode>& GetMenuWeak() const
    {
        return menuWeak_;
    }
    inline void SetIsWidthModifiedBySelect(bool isModified)
    {
        isWidthModifiedBySelect_ = isModified;
    }
    inline bool IsWidthModifiedBySelect() const
    {
        return isWidthModifiedBySelect_;
    }
    inline void SetIsSelectOption(bool isSelect)
    {
        isSelectOption_ = isSelect;
    }
    inline bool IsSelectOption() const
    {
        return isSelectOption_;
    }
    inline void SetHasOptionWidth(bool hasOptionWidth)
    {
        hasOptionWidth_ = hasOptionWidth;
    }
    inline bool GetHasOptionWidth()
    {
        return hasOptionWidth_;
    }
    inline const RefPtr<SelectTheme>& GetSelectTheme() const
    {
        return selectTheme_;
    }
    inline void SetBlockClick(bool blockClick)
    {
        blockClick_ = blockClick;
    }
    inline void SetTextNode(const RefPtr<FrameNode>& text)
    {
        text_ = text;
    }
    inline RefPtr<FrameNode> GetTextNode() const
    {
        return text_;
    }
    inline void SetIconNode(const RefPtr<FrameNode>& icon)
    {
        icon_ = icon;
    }
    inline void SetPasteButton(const RefPtr<FrameNode>& pasteButton)
    {
        pasteButton_ = pasteButton;
    }
    inline void SetIsBGColorSetByUser(bool isSet)
    {
        isBGColorSetByUser_ = isSet;
    }
    inline void SetIsTextColorSetByUser(bool isSet)
    {
        isTextColorSetByUser_ = isSet;
    }
    inline void SetIsOptionFontColorSetByUser(bool isSet)
    {
        isOptionFontColorSetByUser_ = isSet;
    }
    inline void SetSelectFontColor(const Color& color)
    {
        selectFontColor_ = color;
    }
    inline void SetOptionFontColor(const Color& color)
    {
        optionFontColor_ = color;
    }
    inline void SetIsOptionBgColorSetByUser(bool isSet)
    {
        isOptionBgColorSetByUser_ = isSet;
    }
    inline void SetOptionBgColor(const Color& color)
    {
        optionBgColor_ = color;
    }

protected:
    void RegisterOnKeyEvent();
    void RegisterOnTouch();
    void OnAfterModifyDone() override;
    RefPtr<FrameNode> GetMenuWrapper();
    void InitFocusPadding();
    Dimension focusPadding_ = 0.0_vp;

private:
    friend class ServiceCollaborationMenuAceHelper;
    // register menu item's callback
    void RegisterOnClick();
    void RegisterOnHover();
    void CleanParentMenuItemBgColor();
    void SendSubMenuOpenToAccessibility(RefPtr<FrameNode>& subMenu, ShowSubMenuType type);
    virtual void OnTouch(const TouchEventInfo& info);
    virtual bool OnKeyEvent(const KeyEvent& event);
    virtual bool IsCustomMenuItem()
    {
        return false;
    }
    bool OnClick();

    void RegisterWrapperMouseEvent();

    void AddSelectIcon(RefPtr<FrameNode>& row);
    void UpdateIcon(RefPtr<FrameNode>& row, bool isStart);
    void AddExpandIcon(RefPtr<FrameNode>& row);
    void AddClickableArea();
    void UpdateText(RefPtr<FrameNode>& row, RefPtr<MenuLayoutProperty>& menuProperty, bool isLabel);
    void UpdateTextMarquee(bool isMarqueeStart);
    void UpdateTextOverflow(RefPtr<TextLayoutProperty>& textProperty, RefPtr<SelectTheme>& theme);
    void InitTextFadeOut();
    void UpdateFont(RefPtr<MenuLayoutProperty>& menuProperty, RefPtr<SelectTheme>& theme, bool isLabel);
    void SetThemeProps(const RefPtr<FrameNode>& host);
    void UpdateMaxLinesFromTheme(RefPtr<TextLayoutProperty>& textProperty);
    void AddStackSubMenuHeader(RefPtr<FrameNode>& menuNode);
    RefPtr<FrameNode> GetClickableArea();
    void UpdateDisabledStyle();

    void ShowSubMenu(ShowSubMenuType type = ShowSubMenuType::DEFAULT);
    RefPtr<UINode> BuildSubMenuCustomNode();
    RefPtr<FrameNode> GetSubMenu(RefPtr<UINode>& customNode);
    void UpdateSubmenuExpandingMode(RefPtr<UINode>& customNode);
    void ShowSubMenuHelper(const RefPtr<FrameNode>& subMenu);
    void HideSubMenu();
    void OnExpandChanged(const RefPtr<FrameNode>& expandableNode);
    void HideEmbeddedExpandMenu(const RefPtr<FrameNode>& expandableNode);
    void ShowEmbeddedExpandMenu(const RefPtr<FrameNode>& expandableNode);
    void SetShowEmbeddedMenuParams(const RefPtr<FrameNode>& expandableNode);
    void UpdatePreviewPosition(SizeF oldMenuSize, SizeF menuSize);

    OffsetF GetSubMenuPosition(const RefPtr<FrameNode>& targetNode);

    void AddSelfHoverRegion(const RefPtr<FrameNode>& targetNode);
    void SetAccessibilityAction();
    bool IsSelectOverlayMenu();
    void RecordChangeEvent() const;
    void ParseMenuRadius(MenuParam& param);
    void ModifyDivider();

    void NeedFocusEvent();
    void InitFocusEvent();
    void HandleFocusEvent();
    void HandleBlurEvent();
    bool GetShadowFromTheme(ShadowStyle shadowStyle, Shadow& shadow);

    void UpdateSymbolNode(RefPtr<FrameNode>& row, RefPtr<FrameNode>& selectIcon);
    void UpdateImageNode(RefPtr<FrameNode>& row, RefPtr<FrameNode>& selectIcon);
    void UpdateSymbolIcon(RefPtr<FrameNode>& row, RefPtr<FrameNode>& iconNode, ImageSourceInfo& iconSrc,
        std::function<void(WeakPtr<NG::FrameNode>)>& symbol, bool isStart);
    void UpdateImageIcon(RefPtr<FrameNode>& row, RefPtr<FrameNode>& iconNode, ImageSourceInfo& iconSrc,
        std::function<void(WeakPtr<NG::FrameNode>)>& symbol, bool isStart);
    bool UseDefaultThemeIcon(const ImageSourceInfo& imageSourceInfo);

    void OnPress(const TouchEventInfo& info);
    bool OnSelectProcess();
    void OptionOnModifyDone(const RefPtr<FrameNode>& host);
    void UpdateIconSrc();
    bool UpdateOptionFocus(KeyCode code);
    void UpdatePasteFontColor(const Color& fontColor);
    void UpdatePasteDisabledOpacity(const double disabledColorAlpha);
    void OptionHandleFocusEvent();
    void OptionHandleBlurEvent();
    void SetFocusStyle();
    void ClearFocusStyle();
    inline bool IsOptionPattern()
    {
        return isOptionPattern_;
    }
    // make render after measure and layout
    inline bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override
    {
        return !(config.skipMeasure && config.skipLayout);
    }

    std::list<TouchRegion> hoverRegions_;

    RefPtr<InputEvent> wrapperMouseEvent_;

    bool isSelected_ = false;
    bool isSubMenuShowed_ = false;
    bool isSubMenuHovered_ = false;

    bool isChanged_ = false;
    bool isHovered_ = false;
    bool isExpanded_ = false;
    int32_t clickMenuItemId_ = -1;
    std::function<void()> onClickAIMenuItem_ = nullptr;
    int32_t index_ = 0;

    std::function<void()> subBuilderFunc_ = nullptr;

    int32_t subMenuId_ = -1;
    RefPtr<FrameNode> subMenu_;
    RefPtr<FrameNode> content_ = nullptr;
    RefPtr<FrameNode> label_ = nullptr;
    RefPtr<FrameNode> startIcon_ = nullptr;
    RefPtr<FrameNode> endIcon_ = nullptr;
    RefPtr<FrameNode> selectIcon_ = nullptr;
    RefPtr<FrameNode> expandIcon_ = nullptr;
    RefPtr<FrameNode> embeddedMenu_ = nullptr;
    RefPtr<FrameNode> clickableArea_ = nullptr;
    RefPtr<LongPressEvent> longPressEvent_;
    RefPtr<TouchEventImpl> onTouchEvent_;
    RefPtr<InputEvent> onHoverEvent_;
    RefPtr<ClickEvent> onClickEvent_;
    bool onTouchEventSet_ = false;
    bool onHoverEventSet_ = false;
    bool onKeyEventSet_ = false;
    bool onClickEventSet_ = false;
    SubMenuExpandingMode expandingMode_ = SubMenuExpandingMode::SIDE;
    bool isStackSubmenuHeader_ = false;
    bool expandingModeSet_ = false;

    Color bgBlendColor_ = Color::TRANSPARENT;
    std::optional<Color> bgColor_;
    std::optional<Color> selectFontColor_;
    std::optional<Color> optionFontColor_;
    std::optional<Color> optionBgColor_;
    std::function<void(bool)> isFocusActiveUpdateEvent_;
    // src of icon image, used in XTS inspector
    std::string iconSrc_;
    WeakPtr<FrameNode> menuWeak_;
    RefPtr<FrameNode> text_;
    RefPtr<FrameNode> icon_;
    RefPtr<FrameNode> pasteButton_;
    RefPtr<TextTheme> textTheme_;
    RefPtr<SelectTheme> selectTheme_;

    bool blockClick_ = false;
    bool hasOptionWidth_ = false;
    bool isHover_ = false;
    bool isOptionPattern_ = false;  // if it is OptionPattern
    bool isSelectOption_ = false;
    bool isWidthModifiedBySelect_ = false;

    bool isFocused_ = false;
    bool isFocusShadowSet_ = false;
    bool isFocusBGColorSet_ = false;
    bool isTextFadeOut_ = false;
    bool isBGColorSetByUser_ = false;
    bool isTextColorSetByUser_ = false;
    bool isOptionFontColorSetByUser_ = false;
    bool isOptionBgColorSetByUser_ = false;
    int32_t rowSelected_ = -1;

    ACE_DISALLOW_COPY_AND_MOVE(MenuItemPattern);
};

class CustomMenuItemPattern : public MenuItemPattern {
    DECLARE_ACE_TYPE(CustomMenuItemPattern, MenuItemPattern);

public:
    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<BoxLayoutAlgorithm>();
    }
    void OnAttachToFrameNode() override;

private:
    void OnTouch(const TouchEventInfo& info) override;
    void HandleOnChange();
    bool OnKeyEvent(const KeyEvent& event) override;
    bool IsCustomMenuItem() override
    {
        return true;
    }
    std::unique_ptr<Offset> lastTouchOffset_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_PATTERN_H
