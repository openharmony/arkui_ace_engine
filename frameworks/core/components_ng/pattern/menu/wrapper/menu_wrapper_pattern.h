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

    int32_t GetTargetId() const
    {
        return targetId_;
    }

    void HideMenu();

    void AddSubMenuId(int32_t subMenuId)
    {
        subMenuIds_.emplace_back(subMenuId);
    }

    bool IsHided() const
    {
        return isHided_;
    }

    bool IsContextMenu() const
    {
        auto menu = GetMenu();
        CHECK_NULL_RETURN(menu, false);
        auto menuPattern = menu->GetPattern<MenuPattern>();
        CHECK_NULL_RETURN(menuPattern, false);
        return menuPattern->IsContextMenu();
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

private:
    bool ShouldAvoidKeyboard() const override
    {
        return false;
    }
    void OnAttachToFrameNode() override;
    void RegisterOnTouch();
    void OnTouchEvent(const TouchEventInfo& info);
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void SetHotAreas(const RefPtr<LayoutWrapper>& layoutWrapper);
    void StartShowAnimation();

    void HideMenu(const RefPtr<FrameNode>& menu);

    RefPtr<TouchEventImpl> onTouch_;
    // menuId in OverlayManager's map
    int32_t targetId_ = -1;

    AnimationOption animationOption_;
    Placement menuPlacement_ = Placement::NONE;
    bool isFirstShow_ = true;
    bool isHided_ = false;

    std::list<int32_t> subMenuIds_;

    ACE_DISALLOW_COPY_AND_MOVE(MenuWrapperPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_WRAPPER_PATTERN_H
