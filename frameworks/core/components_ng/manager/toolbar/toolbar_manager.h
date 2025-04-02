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
        sideBarColor_ = color;
        OnChangeSideBarColor();
    }

    Color GetSideBarColor() const
    {
        return sideBarColor_;
    }

    void SetSideBarColorChangeCallback(const std::function<void()>&& callback);
    void OnChangeSideBarColor();
    void SetToolBarChangeCallback(const std::function<void()>&& callback);
    void OnChange();
    void SetModifyDoneCallback(const std::function<void()>&& callback);
    void OnNavigationModifyDone();
    void OnSideBarModifyDone();

private:
    bool hasSideBar_ = false;
    bool hasNavBar_ = false;
    bool hasNavDest_ = false;
    ToolbarInfo sideBarInfo_;
    Color sideBarColor_;
    ToolbarInfo sideBarDividerInfo_;
    ToolbarInfo navBarInfo_;
    ToolbarInfo navBarDividerInfo_;
    ToolbarInfo navDestInfo_;
    std::function<void()> sideBarColorChangeCallbackFunc_;
    std::function<void()> onChangeCallbackFunc_;
    std::function<void()> modifyDoneCallbackFunc_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_TOOLBAR_TOOLBAR_MANAGER_H