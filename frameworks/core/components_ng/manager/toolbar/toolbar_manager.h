/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_TOOLBAR_TOOLBAR_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_TOOLBAR_TOOLBAR_MANAGER_H

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

enum class NavigationMode;
struct ToolbarInfo {
    bool isShow;
    float width;
};

class ToolbarManager : public virtual AceType {
    DECLARE_ACE_TYPE(ToolbarManager, AceType);

public:
    ToolbarManager() = default;
    ~ToolbarManager() override = default;

    void SetHasSideBar(bool hasSideBar)
    {
        hasSideBar_ = hasSideBar;
    }

    bool HasSideBar() const
    {
        return hasSideBar_;
    }

    void SetHasNavBar(bool hasNavBar)
    {
        hasNavBar_ = hasNavBar;
    }

    bool HasNavBar() const
    {
        return hasNavBar_;
    }

    void SetHasNavDest(bool hasNavDest)
    {
        hasNavDest_ = hasNavDest;
    }

    bool HasNavDest() const
    {
        return hasNavDest_;
    }

    ToolbarInfo GetSideBarInfo() const
    {
        return sideBarInfo_;
    }
    void SetSideBarInfo(const ToolbarInfo& info);

    ToolbarInfo GetSideBarDividerInfo() const
    {
        return sideBarDividerInfo_;
    }

    void SetSideBarDividerInfo(const ToolbarInfo& info);

    ToolbarInfo GetNavBarInfo() const
    {
        return navBarInfo_;
    }

    void SetNavBarInfo(const ToolbarInfo& info);

    ToolbarInfo GetNavBarDividerInfo() const
    {
        return navBarDividerInfo_;
    }

    void SetNavBarDividerInfo(const ToolbarInfo& info);

    ToolbarInfo GetNavDestInfo() const
    {
        return navDestInfo_;
    }

    void SetNavDestInfo(const ToolbarInfo& info);

    void SetSideBarColor(const Color& color)
    {
        sideBarBgColor_ = color;
    }

    void SetSideBarContainerColor(const Color& bgColor)
    {
        sideBarContainerBgColor_ = bgColor;
    }

    Color GetSideBarContainerBgColor() const
    {
        return sideBarContainerBgColor_;
    }

    void SetSideBarBlurStyle(const BlurStyle& blurStyle)
    {
        sideBarBlurStyle_ = blurStyle;
    }

    BlurStyle GetSideBarBlurStyle() const
    {
        return sideBarBlurStyle_;
    }

    Color GetSideBarColor() const
    {
        return sideBarBgColor_;
    }

    void SetSideBarColorChangeCallback(
        const std::function<void(const Color&, const Color&, const BlurStyle&)>&& callback);
    void OnChangeSideBarColor();
    void SetToolBarChangeCallback(const std::function<void()>&& callback);
    void OnChange();
    void SetModifyDoneCallback(const std::function<void()>&& callback);
    void OnToolBarManagerModifyDone();
    void SetNavigationModeChangeCallback(const std::function<void()>&& callback);
    void OnNavigationModeChange();

    WeakPtr<FrameNode> GetSiderBar()
    {
        return siderBar_;
    }

    void SetSiderBarNode(WeakPtr<FrameNode> node)
    {
        siderBar_ = node;
    }

    void SetNavigationNode(WeakPtr<FrameNode> node)
    {
        navigation_ = node;
    }

    WeakPtr<FrameNode> GetNavigationNode()
    {
        return navigation_;
    }

    WeakPtr<FrameNode> GetSideBarContainerModel()
    {
        return sideBarContainerModel_;
    }

    void SetSideBarContainerModel(WeakPtr<FrameNode> node)
    {
        sideBarContainerModel_ = node;
    }

    WeakPtr<FrameNode> GetSiderBarDivider()
    {
        return siderBarDivider_;
    }

    void SetSiderBarDividerNode(WeakPtr<FrameNode> node)
    {
        siderBarDivider_ = node;
    }

    WeakPtr<FrameNode> GetNavBar()
    {
        return navBar_;
    }

    void SetNavBarNode(WeakPtr<FrameNode> node)
    {
        navBar_ = node;
    }

    WeakPtr<FrameNode> GetNavBarDivider()
    {
        return navBarDivider_;
    }

    void SetNavBarDividerNode(WeakPtr<FrameNode> node)
    {
        navBarDivider_ = node;
    }

    WeakPtr<FrameNode> GetNavDest()
    {
        return navDest_;
    }

    void SetNavDestNode(WeakPtr<FrameNode> node)
    {
        navDest_ = node;
    }

    void SetTitleHeight(Dimension height)
    {
        titleHeight_ = height;
    }

    Dimension GetTitleHeight()
    {
        return titleHeight_;
    }

    bool GetIsMoveUp()
    {
        return isMoveUp_;
    }

    void SetIsMoveUp(bool isMoveUp)
    {
        isMoveUp_ = isMoveUp;
    }

    NavigationMode GetNavigationMode()
    {
        return navigationMode_;
    }

    void SetNavigationMode(NavigationMode mode)
    {
        navigationMode_ = mode;
        OnNavigationModeChange();
    }

private:
    bool hasSideBar_ = false;
    bool hasNavBar_ = false;
    bool hasNavDest_ = false;
    bool isMoveUp_ = false;
    ToolbarInfo sideBarInfo_;
    Color sideBarBgColor_;
    Color sideBarContainerBgColor_;
    BlurStyle sideBarBlurStyle_ = BlurStyle::NO_MATERIAL;
    Dimension titleHeight_ = Dimension(0.0f);
    ToolbarInfo sideBarDividerInfo_;
    ToolbarInfo navBarInfo_;
    ToolbarInfo navBarDividerInfo_;
    ToolbarInfo navDestInfo_;
    NavigationMode navigationMode_;
    std::function<void(const Color&, const Color&, const BlurStyle&)> sideBarColorChangeCallbackFunc_;
    std::list<std::function<void()>> onChangeCallbackFuncs_;
    std::list<std::function<void()>> modifyDoneCallbackFuncs_;
    std::list<std::function<void()>> navigationModeChangeCallbackFuncs_;

    WeakPtr<FrameNode> navigation_;
    WeakPtr<FrameNode> siderBar_;
    WeakPtr<FrameNode> siderBarDivider_;
    WeakPtr<FrameNode> sideBarContainerModel_;
    WeakPtr<FrameNode> navBar_;
    WeakPtr<FrameNode> navBarDivider_;
    WeakPtr<FrameNode> navDest_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_TOOLBAR_TOOLBAR_MANAGER_H