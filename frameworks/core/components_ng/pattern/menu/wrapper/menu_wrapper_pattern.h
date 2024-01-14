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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_WRAPPER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_WRAPPER_PATTERN_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/popup_base_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

// has full screen size
// used for detecting clicks outside Menu area
class MenuWrapperPattern : public PopupBasePattern {
    DECLARE_ACE_TYPE(MenuWrapperPattern, Pattern);

public:
    explicit MenuWrapperPattern(int32_t Id) : targetId_(Id) {}
    ~MenuWrapperPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<MenuWrapperLayoutAlgorithm>();
    }

    void HandleMouseEvent(const MouseInfo& info, RefPtr<MenuItemPattern>& menuItem);

    int32_t GetTargetId() const override
    {
        return targetId_;
    }

    void HideMenu();

    bool IsHided() const
    {
        return isHided_;
    }

    void SetMenuHide()
    {
        isHided_ = true;
    }

    bool IsContextMenu() const
    {
        auto menu = GetMenu();
        CHECK_NULL_RETURN(menu, false);
        auto menuPattern = menu->GetPattern<MenuPattern>();
        CHECK_NULL_RETURN(menuPattern, false);
        return menuPattern->IsContextMenu();
    }

    MenuPreviewMode GetPreviewMode() const
    {
        auto menu = GetMenu();
        CHECK_NULL_RETURN(menu, MenuPreviewMode::NONE);
        auto menuPattern = menu->GetPattern<MenuPattern>();
        CHECK_NULL_RETURN(menuPattern, MenuPreviewMode::NONE);
        return menuPattern->GetPreviewMode();
    }

    bool IsSelectMenu() const
    {
        auto menu = GetMenu();
        CHECK_NULL_RETURN(menu, false);
        auto menuPattern = menu->GetPattern<MenuPattern>();
        CHECK_NULL_RETURN(menuPattern, false);
        return menuPattern->IsSelectMenu();
    }

    void HideSubMenu();

    RefPtr<FrameNode> GetMenu() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        auto menu = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(0));
        CHECK_NULL_RETURN(menu, nullptr);
        return menu;
    }

    RefPtr<FrameNode> GetPreview() const
    {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, nullptr);
        auto preview = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(1));
        CHECK_NULL_RETURN(preview, nullptr);
        return preview;
    }

    OffsetT<Dimension> GetAnimationOffset();
    void SetAniamtinOption(const AnimationOption& animationOption);

    void SetMenuPlacementAfterLayout(const Placement& placement)
    {
        menuPlacement_ = placement;
    }

    void SetFirstShow()
    {
        isFirstShow_ = true;
    }

    void RegisterMenuAppearCallback(const std::function<void()>& onAppear)
    {
        onAppearCallback_ = onAppear;
    }

    void RegisterMenuDisappearCallback(const std::function<void()>& onDisappear)
    {
        onDisappearCallback_ = onDisappear;
    }

    void RegisterMenuAboutToAppearCallback(const std::function<void()>& aboutToAppear)
    {
        aboutToAppearCallback_ = aboutToAppear;
    }

    void RegisterMenuAboutToDisappearCallback(const std::function<void()>& aboutToDisappear)
    {
        aboutToDisappearCallback_ = aboutToDisappear;
    }

    void RegisterMenuStateChangeCallback(const std::function<void(const std::string&)>& callback)
    {
        onStateChangeCallback_ = callback;
    }

    void CallMenuAppearCallback()
    {
        if (onAppearCallback_) {
            onAppearCallback_();
        }
    }

    void CallMenuDisappearCallback()
    {
        if (onDisappearCallback_) {
            onDisappearCallback_();
        }
    }

    void CallMenuAboutToAppearCallback()
    {
        if (aboutToAppearCallback_) {
            aboutToAppearCallback_();
        }
    }

    void CallMenuAboutToDisappearCallback()
    {
        if (aboutToDisappearCallback_) {
            aboutToDisappearCallback_();
        }
    }

    void CallMenuStateChangeCallback(const std::string& value)
    {
        if (onStateChangeCallback_) {
            onStateChangeCallback_(value);
        }
    }

    const std::function<void()>& GetMenuDisappearCallback()
    {
        return onDisappearCallback_;
    }

    void SetShow(bool isShow)
    {
        isShow_ = isShow;
    }

    bool GetShow() const
    {
        return isShow_;
    }

protected:
    void OnTouchEvent(const TouchEventInfo& info);
    void CheckAndShowAnimation();

private:
    bool AvoidKeyboard() const override
    {
        return false;
    }
    bool IsSelectOverlayCustomMenu(const RefPtr<FrameNode>& menu) const;
    void OnAttachToFrameNode() override;
    void RegisterOnTouch();
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void SetHotAreas(const RefPtr<LayoutWrapper>& layoutWrapper);
    void StartShowAnimation();

    void HideMenu(const RefPtr<FrameNode>& menu);

    std::function<void()> onAppearCallback_ = nullptr;
    std::function<void()> onDisappearCallback_ = nullptr;
    std::function<void()> aboutToAppearCallback_ = nullptr;
    std::function<void()> aboutToDisappearCallback_ = nullptr;
    std::function<void(const std::string&)> onStateChangeCallback_ = nullptr;
    RefPtr<TouchEventImpl> onTouch_;
    // menuId in OverlayManager's map
    int32_t targetId_ = -1;

    AnimationOption animationOption_;
    Placement menuPlacement_ = Placement::NONE;
    bool isFirstShow_ = true;
    bool isHided_ = false;
    bool isShow_ = false;
    bool isShowInSubWindow_ = true;
    ACE_DISALLOW_COPY_AND_MOVE(MenuWrapperPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_WRAPPER_PATTERN_H
