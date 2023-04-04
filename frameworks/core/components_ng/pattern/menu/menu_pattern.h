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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_PATTERN_H

#include <optional>

#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/menu/menu_layout_algorithm.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_paint_method.h"
#include "core/components_ng/pattern/menu/navigation_menu_layout_algorithm.h"
#include "core/components_ng/pattern/option/option_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
enum class MenuType { MENU, CONTEXT_MENU, NAVIGATION_MENU, MULTI_MENU, SUB_MENU };

class MenuPattern : public Pattern {
    DECLARE_ACE_TYPE(MenuPattern, Pattern);

public:
    explicit MenuPattern(int32_t targetId, MenuType type) : targetId_(targetId), type_(type) {}
    ~MenuPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<MenuPaintMethod>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<MenuLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        RefPtr<MenuLayoutAlgorithm> navigationMenu = MakeRefPtr<NavigationMenuLayoutAlgorithm>();
        return (type_ == MenuType::NAVIGATION_MENU) ? navigationMenu : MakeRefPtr<MenuLayoutAlgorithm>();
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

    bool IsSubMenu() const
    {
        return type_ == MenuType::SUB_MENU;
    }

    void SetFontSize(const Dimension& value)
    {
        fontSize_ = value;
    }

    Dimension FontSize() const
    {
        auto context = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(context, Dimension());
        auto theme = context->GetTheme<SelectTheme>();
        CHECK_NULL_RETURN(theme, Dimension());
        return fontSize_.value_or(theme->GetMenuFontSize());
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

    void HideMenu() const;

    void MountOption(const RefPtr<FrameNode>& option);

    void RemoveOption();

    RefPtr<FrameNode> GetMenuColumn() const;

private:
    void OnModifyDone() override;
    void RegisterOnTouch();
    void OnTouchEvent(const TouchEventInfo& info);
    bool IsMultiMenuOutside() const;

    void RegisterOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    bool OnKeyEvent(const KeyEvent& event) const;

    void DisableTabInMenu();

    RefPtr<FrameNode> GetMenuWrapper() const;

    RefPtr<ClickEvent> onClick_;
    RefPtr<TouchEventImpl> onTouch_;
    std::optional<Offset> lastTouchOffset_;
    int32_t targetId_ = -1;
    MenuType type_ = MenuType::MENU;

    RefPtr<FrameNode> parentMenuItem_;
    std::vector<RefPtr<FrameNode>> options_;

    std::optional<Dimension> fontSize_;

    bool isSelectMenu_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(MenuPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_PATTERN_H
