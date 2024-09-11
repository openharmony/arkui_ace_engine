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

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/manager/focus/focus_view.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"

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

protected:
    bool UpdateBarSafeAreaPadding();

    bool isHideToolbar_ = false;
    bool isHideTitlebar_ = false;
    std::optional<BarStyle> titleBarStyle_;
    std::optional<BarStyle> toolBarStyle_;
    bool safeAreaPaddingChanged_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVDESTINATION_PATTERN_BASE_H