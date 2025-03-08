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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVDESTINATION_NAVDESTINATION_MODEL_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVDESTINATION_NAVDESTINATION_MODEL_H

#include <mutex>

#include "base/system_bar/system_bar_style.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_options.h"
#include "core/components_ng/pattern/navrouter/navdestination_context.h"
#include "core/components_ng/pattern/navrouter/navdestination_scrollable_processor.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT NavDestinationModel {
public:
    static NavDestinationModel* GetInstance();
    virtual ~NavDestinationModel() = default;

    virtual void Create() = 0;
    virtual void Create(
        std::function<void()>&& deepRenderFunc, RefPtr<NG::NavDestinationContext> context = nullptr) = 0;
    virtual void SetHideTitleBar(bool hideTitleBar, bool animated = false) = 0;
    virtual void SetHideBackButton(bool hideBackButton) = 0;
    virtual void SetTitle(const std::string& title, bool hasSubTitle) = 0;
    virtual void SetTitlebarOptions(NG::NavigationTitlebarOptions&& opt) {};
    virtual void SetBackButtonIcon(const std::function<void(WeakPtr<NG::FrameNode>)>& iconSymbol,
        const std::string& src, const NG::ImageOption& imageOption, RefPtr<PixelMap>& pixMap,
        const std::vector<std::string>& nameList) = 0;
    virtual void SetSubtitle(const std::string& subtitle) = 0;
    virtual void SetCustomTitle(const RefPtr<AceType>& customNode) = 0;
    virtual void SetTitleHeight(const Dimension& titleHeight, bool isValid = true) = 0;
    virtual void SetOnShown(std::function<void()>&& onShow) = 0;
    virtual void SetOnHidden(std::function<void()>&& onHidden) = 0;
    virtual void SetOnWillAppear(std::function<void()>&& willAppear) = 0;
    virtual void SetOnWillShow(std::function<void()>&& willShow) = 0;
    virtual void SetOnWillHide(std::function<void()>&& willHide) = 0;
    virtual void SetOnWillDisAppear(std::function<void()>&& willDisAppear) = 0;
    virtual void SetOnActive(std::function<void(int32_t)>&& onActive) = 0;
    virtual void SetOnInactive(std::function<void(int32_t)>&& onInactive) = 0;
    virtual void SetOnBackPressed(std::function<bool()>&& onBackPressed) = 0;
    virtual void SetOnReady(std::function<void(RefPtr<NG::NavDestinationContext>)>&& onReady) = 0;
    virtual void SetOnPop(std::function<void(const RefPtr<NG::NavPathInfo>&)>&& onPop) = 0;
    virtual void SetHideToolBar(bool hideToolBar, bool animated = false) = 0;
    virtual void SetToolbarConfiguration(std::vector<NG::BarItem>&& toolBarItems) = 0;
    virtual void SetHideItemText(bool isHideItemText) {};
    virtual void SetToolBarOptions(NG::NavigationToolbarOptions&& opt) {}
    virtual void SetToolbarMorebuttonOptions(NG::MoreButtonOptions&& opt) {}
    virtual void SetCustomToolBar(const RefPtr<AceType>& customNode) = 0;
    virtual void SetNavDestinationMode(NG::NavDestinationMode mode);
    virtual void SetRecoverable(bool recoverable) {}
    virtual void SetMenuItems(std::vector<NG::BarItem>&& menuItems) {};
    virtual void SetMenuOptions(NG::NavigationMenuOptions&& opt) {};
    virtual void SetCustomMenu(const RefPtr<AceType>& customNode) = 0;
    virtual void SetBackgroundColor(const Color& color, bool isVaild = true) = 0;
    virtual void SetNavDestinationPathInfo(const std::string& moduleName, const std::string& pagePath) {};
    virtual RefPtr<AceType> CreateEmpty()
    {
        return nullptr;
    }
    virtual bool ParseCommonTitle(
        bool hasSubTitle, bool hasMainTitle, const std::string& subtitle, const std::string& title)
    {
        return false;
    }

    virtual void SetIgnoreLayoutSafeArea(const NG::SafeAreaExpandOpts& opts) {};
    virtual void SetSystemBarStyle(const RefPtr<SystemBarStyle>& style) {};
    virtual void SetSystemTransitionType(NG::NavigationSystemTransitionType type) {};
    virtual void SetScrollableProcessor(
        const std::function<RefPtr<NG::NavDestinationScrollableProcessor>()>& creator) {}
    virtual void UpdateBindingWithScrollable(
        std::function<void(const RefPtr<NG::NavDestinationScrollableProcessor>& processor)>&& callback) {}
    virtual void SetCustomTransition(NG::NavDestinationTransitionDelegate&& transitionDelegate) {}
    virtual void SetOnNewParam(NG::NavDestinationOnNewParamCallback&& onNewParamCallback) {}

private:
    static std::unique_ptr<NavDestinationModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVDESTINATION_NAVDESTINATION_MODEL_H
