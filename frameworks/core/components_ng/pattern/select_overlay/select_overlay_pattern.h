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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_SELECT_OVERLAY_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SELECT_OVERLAY_SELECT_OVERLAY_PATTERN_H

#include <utility>

#include "base/geometry/ng/rect_t.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_content_modifier.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_event_hub.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_layout_algorithm.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_modifier.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_paint_method.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SelectOverlayPattern : public MenuWrapperPattern {
    DECLARE_ACE_TYPE(SelectOverlayPattern, MenuWrapperPattern);

public:
    explicit SelectOverlayPattern(std::shared_ptr<SelectOverlayInfo> info, SelectOverlayMode mode)
        : MenuWrapperPattern(-1), info_(std::move(info)), overlayMode_(mode)
    {
        CheckHandleReverse();
    }
    ~SelectOverlayPattern() override = default;

    bool IsMeasureBoundary() const override
    {
        return true;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<SelectOverlayLayoutAlgorithm>(info_, defaultMenuEndOffset_, menuWidth_, menuHeight_);
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        auto layoutProps = GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_RETURN(layoutProps, nullptr);
        bool isReverse = layoutProps->GetNonAutoLayoutDirection() == TextDirection::RTL;
        if (!selectOverlayModifier_ && CheckIfNeedMenu()) {
            selectOverlayModifier_ = AceType::MakeRefPtr<SelectOverlayModifier>(defaultMenuEndOffset_, isReverse);
        }
        if (!selectOverlayContentModifier_ && CheckIfNeedHandle()) {
            selectOverlayContentModifier_ = AceType::MakeRefPtr<SelectOverlayContentModifier>(WeakClaim(this));
        }
        SetContentModifierBounds(selectOverlayContentModifier_);
        SetSelectMenuHeight();

        if (paintMethodCreated_) {
            return MakeRefPtr<SelectOverlayPaintMethod>(selectOverlayModifier_, selectOverlayContentModifier_, *info_,
                defaultMenuEndOffset_, selectMenuHeight_, hasExtensionMenu_, hasShowAnimation_, true, isHiddenHandle_,
                defaultMenuStartOffset_, isReverse);
        } else {
            paintMethodCreated_ = true;
            return MakeRefPtr<SelectOverlayPaintMethod>(selectOverlayModifier_, selectOverlayContentModifier_, *info_,
                defaultMenuEndOffset_, selectMenuHeight_, hasExtensionMenu_, hasShowAnimation_, false, isHiddenHandle_,
                defaultMenuStartOffset_, isReverse);
        }
    }

    const std::shared_ptr<SelectOverlayInfo>& GetSelectOverlayInfo() const
    {
        return info_;
    }

    void UpdateFirstSelectHandleInfo(const SelectHandleInfo& info);

    void UpdateSecondSelectHandleInfo(const SelectHandleInfo& info);

    void UpdateFirstAndSecondHandleInfo(const SelectHandleInfo& firstInfo, const SelectHandleInfo& secondInfo);

    void UpdateSelectMenuInfo(const SelectMenuInfo& info);

    void UpdateSelectMenuInfo(std::function<void(SelectMenuInfo& menuInfo)> updateAction);

    void UpdateAncestorViewPort(const std::optional<RectF>& ancestorViewPort) const;

    void UpdateShowArea(const RectF& area);

    void SetSelectRegionVisible(bool isSelectRegionVisible);

    void SetHandleReverse(bool reverse);

    void SetSelectInfo(const std::string& selectInfo)
    {
        info_->selectText = selectInfo;
    }

    const std::string& GetSelectInfo() const
    {
        return info_->selectText;
    }

    const RefPtr<SelectOverlayModifier>& GetOverlayModifier()
    {
        return selectOverlayModifier_;
    }

    const RefPtr<SelectOverlayContentModifier>& GetContentModifier()
    {
        return selectOverlayContentModifier_;
    }

    const OffsetF& GetDefaultMenuEndOffset()
    {
        return defaultMenuEndOffset_;
    }

    std::optional<float> GetMenuWidth() const
    {
        return menuWidth_;
    }

    std::optional<float> GetMenuHeight() const
    {
        return menuHeight_;
    }

    const RectF& GetHandleRegion(bool isFirst) const
    {
        if (isFirst) {
            return firstHandleRegion_;
        } else {
            return secondHandleRegion_;
        }
    }

    void ShowOrHiddenMenu(bool isHidden, bool noAnimation = false);
    void DisableMenu(bool isDisabled);

    void SetClosedByGlobalTouchEvent(bool closedByGlobalTouch)
    {
        closedByGlobalTouchEvent_ = closedByGlobalTouch;
    }

    bool IsMenuShow();
    bool IsSingleHandleMenuShow();
    bool IsHandleShow();
    bool IsSingleHandle();

    void SetHasShowAnimation(bool animation)
    {
        hasShowAnimation_ = animation;
    }

    bool IsCustomMenu()
    {
        return info_ && info_->menuInfo.menuBuilder != nullptr;
    }

    bool IsHiddenHandle()
    {
        return isHiddenHandle_;
    }

    void StartHiddenHandleTask(bool isDelay = true);
    virtual void UpdateSelectArea(const RectF& selectArea);

    void SetIsNewAvoid(bool isNewAvoid);

    bool CheckIfNeedMenu();
    bool CheckIfNeedHandle();

    SelectOverlayMode GetMode()
    {
        return overlayMode_;
    }

    void SetGestureEvent();
    void InitMouseEvent();

    static float GetHandleDiameter();
    void OnDpiConfigurationUpdate() override;
    bool IsDraggingHandle(bool isFirst)
    {
        if (isFirst) {
            return firstHandleDrag_;
        } else {
            return secondHandleDrag_;
        }
    }
    void OnColorConfigurationUpdate() override;
    void OnLanguageConfigurationUpdate() override;

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<SelectOverlayEventHub>();
    }
    bool GetIsMenuShowInSubWindow() const
    {
        return isMenuShowInSubWindow_;
    }

    void SetIsMenuShowInSubWindow(bool isMenuShowInSubWindow)
    {
        isMenuShowInSubWindow_ = isMenuShowInSubWindow;
    }

    void DeleteHotAreas();

protected:
    virtual void CheckHandleReverse();
    virtual void UpdateHandleHotZone();
    RectF GetHandlePaintRect(const SelectHandleInfo& handleInfo);
    void AddMenuResponseRegion(std::vector<DimensionRect>& responseRegion);
    std::shared_ptr<SelectOverlayInfo> info_;
    RefPtr<ClickEvent> clickEvent_;
    RefPtr<PanEvent> panEvent_;
    CancelableCallback<void()> hiddenHandleTask_;
    bool isHiddenHandle_ = false;
    RectF firstHandleRegion_;
    RectF secondHandleRegion_;

private:
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;

    void HandleOnClick(GestureEvent& info);
    void HandleTouchEvent(const TouchEventInfo& info);
    void HandleTouchDownEvent(const TouchEventInfo& info);
    void HandleOnTouch(GestureEvent& info);
    void HandlePanStart(GestureEvent& info);
    void HandlePanMove(GestureEvent& info);
    void HandlePanEnd(GestureEvent& info);
    void HandlePanCancel();
    void HandleMouseEvent(const MouseInfo& info);

    bool IsHandlesInSameLine();
    bool IsFirstHandleMoveStart(const Offset& touchOffset);
    void StopHiddenHandleTask();
    void HiddenHandle();
    void UpdateOffsetOnMove(RectF& region, SelectHandleInfo& handleInfo, const OffsetF& offset, bool isFirst);
    void SetSelectMenuHeight();
    void SetContentModifierBounds(const RefPtr<SelectOverlayContentModifier>& modifier);
    void SwitchHandleToOverlayMode(bool afterRender);
    void SetHotAreas(const RefPtr<LayoutWrapper>& layoutWrapper);

    RefPtr<TouchEventImpl> touchEvent_;

    bool firstHandleDrag_ = false;
    bool secondHandleDrag_ = false;
    bool isFirstHandleTouchDown_ = false;
    bool isSecondHandleTouchDown_ = false;
    // Used to record the original menu display status when the handle is moved.
    bool orignMenuIsShow_ = false;
    bool hasExtensionMenu_ = false;
    bool hasShowAnimation_ = false;

    int32_t greatThanMaxWidthIndex_ = -1;
    std::optional<float> menuWidth_;
    std::optional<float> menuHeight_;

    OffsetF defaultMenuStartOffset_;
    OffsetF defaultMenuEndOffset_;

    float selectMenuHeight_ = 0.0f;

    RefPtr<SelectOverlayModifier> selectOverlayModifier_;

    RefPtr<SelectOverlayContentModifier> selectOverlayContentModifier_;

    bool paintMethodCreated_ = false;

    bool closedByGlobalTouchEvent_ = false;
    SelectOverlayMode overlayMode_ = SelectOverlayMode::ALL;
    // Used to identify whether the menu is actually displayed in the subwindow.
    bool isMenuShowInSubWindow_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(SelectOverlayPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PAGE_PATTERN_H
