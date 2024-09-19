/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVDESTINATION_PATTERN_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVDESTINATION_PATTERN_BASE_H

#include <vector>
#include <optional>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/manager/focus/focus_view.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_options.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {

class NavDestinationPatternBase : public Pattern, public FocusView {
    DECLARE_ACE_TYPE(NavDestinationPatternBase, Pattern, FocusView);
public:
    NavDestinationPatternBase() = default;
    ~NavDestinationPatternBase() override = default;

    void SetTitleBarStyle(const std::optional<BarStyle>& barStyle);

    std::optional<BarStyle> GetTitleBarStyle() const
    {
        return titleBarStyle_;
    }

    void SetToolBarStyle(const std::optional<BarStyle>& barStyle);

    std::optional<BarStyle> GetToolBarStyle() const
    {
        return toolBarStyle_;
    }

    virtual Dimension GetTitleBarHeightBeforeMeasure()
    {
        return 0.0_vp;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    bool CheckCustomAvoidKeyboard() const override
    {
        return !NearZero(avoidKeyboardOffset_);
    }
    void SetAvoidKeyboardOffset(float avoidKeyboardOffset)
    {
        avoidKeyboardOffset_ = avoidKeyboardOffset;
    }
    float GetAvoidKeyboardOffset()
    {
        return avoidKeyboardOffset_;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    std::list<int32_t> GetRouteOfFirstScope() override
    {
        return {};
    }

    bool IsEntryFocusView() override
    {
        return false;
    }

    void SetTitleBarMenuItems(const std::vector<BarItem>& menuItems)
    {
        titleBarMenuItems_ = menuItems;
    }

    const std::vector<BarItem>& GetTitleBarMenuItems() const
    {
        return titleBarMenuItems_;
    }

    void SetToolBarMenuItems(const std::vector<BarItem>& menuItems)
    {
        toolBarMenuItems_ = menuItems;
    }

    const std::vector<BarItem>& GetToolBarMenuItems() const
    {
        return toolBarMenuItems_;
    }

    int32_t GetMenuNodeId() const
    {
        return menuNodeId_.value();
    }

    int32_t GetLandscapeMenuNodeId()
    {
        if (!landscapeMenuNodeId_.has_value()) {
            landscapeMenuNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return landscapeMenuNodeId_.value();
    }

    void SetMenuNodeId(const int32_t menuNodeId)
    {
        menuNodeId_ = menuNodeId;
    }

    void SetLandscapeMenuNodeId(const int32_t landscapeMenuNodeId)
    {
        landscapeMenuNodeId_ = landscapeMenuNodeId;
    }

    bool HasMenuNodeId() const
    {
        return menuNodeId_.has_value();
    }

    bool HasLandscapeMenuNodeId() const
    {
        return landscapeMenuNodeId_.has_value();
    }

    bool GetToolbarHideStatus()
    {
        return isHideToolbar_;
    }

    int32_t GetMaxMenuNum() const
    {
        return maxMenuNums_;
    }

    void SetMaxMenuNum(int32_t maxMenu)
    {
        maxMenuNums_ = maxMenu;
    }

protected:
    bool UpdateBarSafeAreaPadding();

    bool isHideToolbar_ = false;
    bool isHideTitlebar_ = false;
    std::optional<BarStyle> titleBarStyle_;
    std::optional<BarStyle> toolBarStyle_;
    bool safeAreaPaddingChanged_ = false;
    float avoidKeyboardOffset_ = 0.0f;
    std::vector<BarItem> titleBarMenuItems_;
    std::vector<BarItem> toolBarMenuItems_;
    std::optional<int32_t> menuNodeId_;
    std::optional<int32_t> landscapeMenuNodeId_;
    int32_t maxMenuNums_ = -1;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVDESTINATION_PATTERN_BASE_H