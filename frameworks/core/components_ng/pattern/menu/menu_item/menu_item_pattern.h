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

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
#include "core/components/slider/render_slider.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_event_hub.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_layout_algorithm.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT MenuItemPattern : public Pattern {
    DECLARE_ACE_TYPE(MenuItemPattern, Pattern);

public:
    explicit MenuItemPattern() = default;
    ~MenuItemPattern() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true, FocusStyleType::INNER_BORDER };
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<MenuItemEventHub>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<MenuItemLayoutAlgorithm>();
    }

    void SetSelected(bool isSelected)
    {
        isSelected_ = isSelected;
        GetHost()->MarkModifyDone();
    }

    bool IsSelected() const
    {
        return isSelected_;
    }

    void SetSelectIcon(bool isShow)
    {
        isSelectIconShow_ = isShow;
        GetHost()->MarkModifyDone();
    }

    bool IsSelectIconShow() const
    {
        return isSelectIconShow_;
    }

    void SetSubBuilder(const std::function<void()>& subBuilderFunc)
    {
        subBuilderFunc_ = subBuilderFunc;
    }

    std::function<void()>& GetSubBuilder()
    {
        return subBuilderFunc_;
    }

    bool IsSubMenuShowed()
    {
        return isSubMenuShowed_;
    }

    void SetIsSubMenuShowed(bool isSubMenuShowed)
    {
        isSubMenuShowed_ = isSubMenuShowed;
    }

    bool IsSubMenuHovered()
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

    void SetContentNode(const RefPtr<FrameNode>& content)
    {
        content_ = content;
    }
    void SetLabelNode(const RefPtr<FrameNode>& label)
    {
        label_ = label;
    }

    void UpdateBackgroundColor(const Color& color);

    RefPtr<FrameNode> GetMenu();

    void ModifyFontSize();

    void ModifyFontSize(const Dimension& fontSize);

protected:
    void OnModifyDone() override;
    void OnMountToParentDone() override;

private:
    // register menu item's callback
    void RegisterOnClick();
    void RegisterOnTouch();
    void RegisterOnHover();
    void RegisterOnKeyEvent(const RefPtr<FocusHub>& focusHub);
    // change menu item paint props on press
    void OnPress(const TouchEventInfo& info);
    void OnHover(bool isHover);
    bool OnKeyEvent(const KeyEvent& event);

    void RegisterWrapperMouseEvent();

    void AddSelectIcon();

    RefPtr<FrameNode> GetMenuWrapper();

    void ShowSubMenu();

    OffsetF GetSubMenuPostion(const RefPtr<FrameNode>& targetNode);

    void AddSelfHoverRegion(const RefPtr<FrameNode>& targetNode);

    std::list<TouchRegion> hoverRegions_;

    RefPtr<InputEvent> wrapperMouseEvent_;

    bool isSelected_ = false;
    bool isSelectIconShow_ = false;

    bool isSubMenuShowed_ = false;
    bool isSubMenuHovered_ = false;

    bool isChanged_ = false;

    std::function<void()> subBuilderFunc_ = nullptr;

    int32_t subMenuId_ = -1;
    RefPtr<FrameNode> subMenu_;
    RefPtr<FrameNode> content_ = nullptr;
    RefPtr<FrameNode> label_ = nullptr;
    RefPtr<FrameNode> selectIcon_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(MenuItemPattern);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_PATTERN_H
