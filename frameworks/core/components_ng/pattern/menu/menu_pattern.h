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

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/menu/menu_accessibility_property.h"
#include "core/components_ng/pattern/menu/menu_layout_algorithm.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_paint_method.h"
#include "core/components_ng/pattern/menu/menu_paint_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select/select_model.h"
#include "core/components_v2/inspector/inspector_constants.h"

constexpr int32_t DEFAULT_CLICK_DISTANCE = 15;
constexpr uint32_t MAX_SEARCH_DEPTH = 5;
namespace OHOS::Ace::NG {
enum class MenuType {
    // ----- Menu Containers ------
    MENU,         // corresponds to .bindMenu attribute
    CONTEXT_MENU, // corresponds to .bindContextMenu attribute, lives in a SubWindow
    SUB_MENU,     // secondary menu container in a multi-level menu

    // ----- innerMenu Node, corersponds to <Menu> tag in the frontend ------
    MULTI_MENU,   // called multi because it's a multi-leveled menu, its MenuItems can trigger subMenus
    DESKTOP_MENU, // menu specialized for desktop UI, enabled when multiple sibiling <Menu> nodes are present

    // ----- special menu used in other components ------
    NAVIGATION_MENU,               // menu used in a Navigation component
    SELECT_OVERLAY_EXTENSION_MENU, // menu used in SelectOverlay Extension of text component
    RICH_EDIT_SELECT_MENU,         // menu used in Rich Editor component
};

class MenuPattern : public Pattern {
    DECLARE_ACE_TYPE(MenuPattern, Pattern);

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

    bool IsNavigationMenu() const
    {
        return type_ == MenuType::NAVIGATION_MENU;
    }

    bool IsMultiMenu() const
    {
        return type_ == MenuType::MULTI_MENU;
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

    bool IsRichEditorSelectMenu() const
    {
        return type_ == MenuType::RICH_EDIT_SELECT_MENU;
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

    void AddOptionNode(const RefPtr<FrameNode>& option)
    {
        CHECK_NULL_VOID(option);
        options_.emplace_back(option);
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

    void RemoveParentHoverStyle();

    void UpdateSelectParam(const std::vector<SelectParam>& params);

    void HideMenu(bool isMenuOnTouch = false) const;

    void MountOption(const RefPtr<FrameNode>& option);

    void RemoveOption();

    RefPtr<FrameNode> GetMenuColumn() const;

    void SetShowedSubMenu(const RefPtr<FrameNode>& subMenu)
    {
        showedSubMenu_ = subMenu;
    }
    const RefPtr<FrameNode>& GetShowedSubMenu() const
    {
        return showedSubMenu_;
    }
    void HideSubMenu();
    void OnModifyDone() override;

    // acquire first menu node in wrapper node by submenu node
    RefPtr<MenuPattern> GetMainMenuPattern() const;
    uint32_t GetInnerMenuCount() const;
    void OnColorConfigurationUpdate() override;

    RefPtr<FrameNode> GetMenuWrapper() const;
    RefPtr<FrameNode> GetFirstInnerMenu() const;

protected:
    void UpdateMenuItemChildren(RefPtr<FrameNode>& host);
    void SetMenuAttribute(RefPtr<FrameNode>& host);
    void SetAccessibilityAction();
    void SetType(MenuType value)
    {
        type_ = value;
    }
    virtual void InitTheme(const RefPtr<FrameNode>& host);

private:
    void OnAttachToFrameNode() override;
    void RegisterOnTouch();
    void OnTouchEvent(const TouchEventInfo& info);
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    // If CustomBuilder is declared with <Menu> and <MenuItem>,
    // reset outer menu container and only apply theme on the inner <Menu> node.
    void ResetTheme(const RefPtr<FrameNode>& host, bool resetForDesktopMenu);
    void CopyMenuAttr(const RefPtr<FrameNode>& menuNode) const;

    void RegisterOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event) const;

    void DisableTabInMenu();

    RefPtr<ClickEvent> onClick_;
    RefPtr<TouchEventImpl> onTouch_;
    std::optional<Offset> lastTouchOffset_;
    const int32_t targetId_ = -1;
    const std::string targetTag_;
    MenuType type_ = MenuType::MENU;

    RefPtr<FrameNode> parentMenuItem_;
    RefPtr<FrameNode> showedSubMenu_;
    std::vector<RefPtr<FrameNode>> options_;

    bool isSelectMenu_ = false;

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

    const std::list<WeakPtr<UINode>>& GetItemsAndGroups() const
    {
        return itemsAndGroups_;
    }

private:
    void InitTheme(const RefPtr<FrameNode>& host) override;
    uint32_t FindSiblingMenuCount();
    void ApplyDesktopMenuTheme();
    void ApplyMultiMenuTheme();

    void RecordItemsAndGroups();

    // Record menu's items and groups at first level,
    // use for group header and footer padding
    std::list<WeakPtr<UINode>> itemsAndGroups_;

    ACE_DISALLOW_COPY_AND_MOVE(InnerMenuPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_PATTERN_H
