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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_SELECT_OVERLAY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_SELECT_OVERLAY_H
#include <optional>

#include "core/components_ng/pattern/text/text_select_overlay.h"

namespace OHOS::Ace::NG {
class RichEditorSelectOverlay : public TextSelectOverlay {
    DECLARE_ACE_TYPE(RichEditorSelectOverlay, TextSelectOverlay);

public:
    explicit RichEditorSelectOverlay(const WeakPtr<TextBase>& textBase) : TextSelectOverlay(textBase) {}
    ~RichEditorSelectOverlay() = default;

    // override TextBaseSelectOverlay
    bool PreProcessOverlay(const OverlayRequest& request) override;
    bool CheckHandleVisible(const RectF& paintRect) override;
    void OnResetTextSelection() override;
    void AfterCloseOverlay() override;
    void OnAncestorNodeChanged(FrameNodeChangeInfoFlag flag) override;

    // override SelectOverlayHolder
    std::optional<SelectHandleInfo> GetFirstHandleInfo() override;
    std::optional<SelectHandleInfo> GetSecondHandleInfo() override;
    void OnUpdateMenuInfo(SelectMenuInfo& menuInfo, SelectOverlayDirtyFlag dirtyFlag) override;
    void OnUpdateSelectOverlayInfo(SelectOverlayInfo& overlayInfo, int32_t requestCode) override;
    RectF GetSelectArea() override;
    std::string GetSelectedText() override;

    // override SelectOverlayCallback
    void OnMenuItemAction(OptionMenuActionId id, OptionMenuType type) override;
    void OnOverlayTouchDown(const TouchEventInfo& event) override;
    void OnHandleMove(const RectF& rect, bool isFirst) override;
    void GetLocalPointWithTransform(OffsetF& localPoint);
    void OnHandleMoveDone(const RectF& rect, bool isFirst) override;
    void OnCloseOverlay(OptionMenuType menuType, CloseReason reason, RefPtr<OverlayInfo> info = nullptr) override;
    void OnHandleGlobalTouchEvent(SourceType sourceType, TouchType touchType, bool touchInside = true) override;
    void OnHandleLevelModeChanged(HandleLevelMode mode) override;
    void OnHandleMarkInfoChange(std::shared_ptr<SelectOverlayInfo> info, SelectOverlayDirtyFlag flag) override;
    void UpdateHandleColor();
    std::optional<SelectOverlayInfo> GetSelectOverlayInfo();
    bool IsSingleHandleShow();
    void UpdateMenuOffset();
    bool IsBothHandlesShow();
    bool IsHandleShow();
    void OnHandleMoveStart(const GestureEvent& event, bool isFirst) override;
    void UpdateHandleOffset();
    void UpdateSelectOverlayOnAreaChanged();
    void ToggleMenu();
    bool GetIsHandleMoving()
    {
        return isHandleMoving_;
    }
    void OnHandleIsHidden() override;
    void OnOverlayClick(const GestureEvent& event, bool isFirst) override;
    void OnHandleMouseEvent(const MouseInfo& event) override;
    void OnAfterSelectOverlayShow(bool isCreate) override;
    bool IsRegisterTouchCallback() override
    {
        return true;
    }
    float GetHandleHotZoneRadius();

private:
    void RemoveAreaChangeInner();
    void CloseMagnifier();
    void UpdateSelectorOnHandleMove(const OffsetF& handleOffset, bool isFirstHandle) override;
    void CheckMenuParamChange(SelectOverlayInfo& selectInfo, TextSpanType selectType, TextResponseType responseType);
    void SwitchCaretState(std::shared_ptr<SelectOverlayInfo> info);
    void ResumeTwinkling();
    std::shared_ptr<SelectionMenuParams> lastMenuParams_ = nullptr;
    std::pair<TextSpanType, TextResponseType> lastSelectResponseComb_;
    bool needRefreshMenu_ = false;
    bool handleIsHidden_ = true;
    std::pair<int32_t, int32_t> initSelector_ = { 0, 0 };

    ACE_DISALLOW_COPY_AND_MOVE(RichEditorSelectOverlay);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_SELECT_OVERLAY_H
