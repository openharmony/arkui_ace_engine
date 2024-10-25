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

#include "core/components_ng/pattern/rich_editor/rich_editor_select_overlay.h"

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components/text_overlay/text_overlay_theme.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float BOX_EPSILON = 0.5f;
constexpr float DOUBLE = 2.0f;
constexpr SelectOverlayDirtyFlag UPDATE_HANDLE_COLOR_FLAG = 101;
}

bool RichEditorSelectOverlay::PreProcessOverlay(const OverlayRequest& request)
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, false);
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(pattern, false);
    SetUsingMouse(pattern->IsUsingMouse());
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    pipeline->AddOnAreaChangeNode(host->GetId());
    SetEnableHandleLevel(true);
    return true;
}

std::optional<SelectHandleInfo> RichEditorSelectOverlay::GetFirstHandleInfo()
{
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    SelectHandleInfo handleInfo;
    handleInfo.paintRect = pattern->textSelector_.firstHandle;
    handleInfo.isShow = CheckHandleVisible(handleInfo.paintRect);

    auto localPaintRect = handleInfo.paintRect;
    localPaintRect.SetOffset(localPaintRect.GetOffset() - GetPaintOffsetWithoutTransform());
    handleInfo.localPaintRect = localPaintRect;
    SetTransformPaintInfo(handleInfo, localPaintRect);
    return handleInfo;
}

std::optional<SelectHandleInfo> RichEditorSelectOverlay::GetSecondHandleInfo()
{
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    SelectHandleInfo handleInfo;
    handleInfo.paintRect = pattern->textSelector_.secondHandle;
    handleInfo.isShow = CheckHandleVisible(handleInfo.paintRect);

    auto localPaintRect = handleInfo.paintRect;
    localPaintRect.SetOffset(localPaintRect.GetOffset() - GetPaintOffsetWithoutTransform());
    handleInfo.localPaintRect = localPaintRect;
    SetTransformPaintInfo(handleInfo, localPaintRect);
    return handleInfo;
}

bool RichEditorSelectOverlay::CheckHandleVisible(const RectF& paintRect)
{
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    if (IsUsingMouse()) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "No need to show handle when using mouse");
        return false;
    }

    auto contentRect = pattern->GetTextContentRect();
    auto parentGlobalOffset = pattern->GetParentGlobalOffset();
    RectF visibleContentRect(contentRect.GetOffset() + parentGlobalOffset, contentRect.GetSize());
    auto parent = host->GetAncestorNodeOfFrame();
    visibleContentRect = GetVisibleContentRect();
    if (visibleContentRect.IsEmpty()) {
        return false;
    }
    auto paintLeft = paintRect.Left() + paintRect.Width() / 2.0f;
    PointF bottomPoint = { paintLeft, paintRect.Bottom() - BOX_EPSILON };
    PointF topPoint = { paintLeft, paintRect.Top() + BOX_EPSILON };
    visibleContentRect.SetLeft(visibleContentRect.GetX() - BOX_EPSILON);
    visibleContentRect.SetWidth(visibleContentRect.Width() + DOUBLE * BOX_EPSILON);
    visibleContentRect.SetTop(visibleContentRect.GetY() - BOX_EPSILON);
    visibleContentRect.SetHeight(visibleContentRect.Height() + DOUBLE * BOX_EPSILON);
    return visibleContentRect.IsInRegion(bottomPoint) && visibleContentRect.IsInRegion(topPoint);
}

void RichEditorSelectOverlay::OnResetTextSelection()
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    textPattern->ResetSelection();
}

void RichEditorSelectOverlay::AfterCloseOverlay()
{
    RemoveAreaChangeInner();
    CloseMagnifier();
}

void RichEditorSelectOverlay::RemoveAreaChangeInner()
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    textPattern->RemoveAreaChangeInner();
}

void RichEditorSelectOverlay::CloseMagnifier()
{
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->magnifierController_->RemoveMagnifierFrameNode();
}

void RichEditorSelectOverlay::OnHandleMove(const RectF& handleRect, bool isFirst)
{
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->HasFocus());
    CHECK_NULL_VOID(SelectOverlayIsOn());
    CHECK_NULL_VOID(!pattern->spans_.empty());
    TextSelectOverlay::OnHandleMove(handleRect, isFirst);
    auto parentGlobalOffset = pattern->GetParentGlobalOffset();
    if (hasTransform_) {
        parentGlobalOffset = GetPaintOffsetWithoutTransform();
    }
    auto localOffset = handleRect.GetOffset();
    if (IsOverlayMode()) {
        localOffset = localOffset - parentGlobalOffset; // original offset
    }

    // update moving handle offset
    auto movingHandleOffset = pattern->ConvertTouchOffsetToTextOffset(Offset(localOffset.GetX(), localOffset.GetY()));
    auto movingHandleOffsetF = OffsetF(movingHandleOffset.GetX(), movingHandleOffset.GetY());
    GetLocalPointWithTransform(movingHandleOffsetF); // do affine transformation
    pattern->SetMovingHandleOffset(movingHandleOffsetF);

    float x = localOffset.GetX();
    float handleHeight = IsSingleHandle() ? pattern->CalculateCaretOffsetAndHeight().second : handleRect.Height();
    float y = localOffset.GetY() + handleRect.Height() - handleHeight / 2; // 2: Half the height of the handle
    auto magnifierLocalOffset = OffsetF(x, y);
    GetLocalPointWithTransform(magnifierLocalOffset); // do affine transformation
    pattern->magnifierController_->SetLocalOffset(magnifierLocalOffset);

    if (isFirst) {
        pattern->textSelector_.firstHandle.SetOffset(localOffset);
    } else {
        pattern->textSelector_.secondHandle.SetOffset(localOffset);
    }
    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::HANDLE,
        .handleRect = handleRect,
        .isFirstHandle = isFirst,
        .showScrollbar = true };
    pattern->AutoScrollByEdgeDetection(param, localOffset, EdgeDetectionStrategy::OUT_BOUNDARY);
}

void RichEditorSelectOverlay::GetLocalPointWithTransform(OffsetF& localPoint)
{
    if (!IsOverlayMode()) {
        return;
    }
    BaseTextSelectOverlay::GetLocalPointWithTransform(localPoint);
}

void RichEditorSelectOverlay::UpdateSelectorOnHandleMove(const OffsetF& handleOffset, bool isFirst)
{
    auto pattern = GetPattern<RichEditorPattern>();
    auto& textSelector = pattern->textSelector_;
    auto currentHandleIndex = pattern->GetHandleIndex(Offset(handleOffset.GetX(), handleOffset.GetY()));
    auto preHandleIndex = isFirst ? textSelector.baseOffset : textSelector.destinationOffset;
    pattern->StartVibratorByIndexChange(currentHandleIndex, preHandleIndex);
    pattern->SetCaretPosition(currentHandleIndex);
    if (isFirst) {
        pattern->HandleSelectionChange(currentHandleIndex, initSelector_.second);
    } else {
        if (IsSingleHandle()) {
            auto textOffset = handleOffset + pattern->contentRect_.GetOffset() - pattern->richTextRect_.GetOffset();
            pattern->CalcAndRecordLastClickCaretInfo(Offset(textOffset.GetX(), textOffset.GetY()));
            textSelector.Update(currentHandleIndex);
        } else {
            pattern->HandleSelectionChange(initSelector_.first, currentHandleIndex);
        }
    }
}

void RichEditorSelectOverlay::OnHandleMoveDone(const RectF& handleRect, bool isFirstHandle)
{
    isHandleMoving_ = false;
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "handleRect=%{public}s, isFirstHandle=%{public}d",
        handleRect.ToString().c_str(), isFirstHandle);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto& textSelector = pattern->textSelector_;
    auto selectStart = std::min(textSelector.baseOffset, textSelector.destinationOffset);
    auto selectEnd = std::max(textSelector.baseOffset, textSelector.destinationOffset);
    pattern->FireOnSelect(selectStart, selectEnd);
    if (!IsSingleHandle()) {
        pattern->SetCaretPositionWithAffinity({ selectEnd, TextAffinity::UPSTREAM });
    }
    pattern->StopAutoScroll();
    pattern->magnifierController_->RemoveMagnifierFrameNode();
    if (!IsSingleHandle() && textSelector.StartEqualToDest()) {
        HideMenu();
        CloseOverlay(true, CloseReason::CLOSE_REASON_NORMAL);
        IF_TRUE(pattern->IsEditing(), pattern->StartTwinkling());
        return;
    }
    auto overlayManager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->SetHandleCircleIsShow(isFirstHandle, true);
    if (!isFirstHandle && IsSingleHandle()) {
        overlayManager->SetIsHandleLineShow(true);
    }
    pattern->CalculateHandleOffsetAndShowOverlay();
    overlayManager->MarkInfoChange((isFirstHandle ? DIRTY_FIRST_HANDLE : DIRTY_SECOND_HANDLE) | DIRTY_SELECT_AREA |
                            DIRTY_SELECT_TEXT | DIRTY_COPY_ALL_ITEM);
    ProcessOverlay({ .animation = true });
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

std::string RichEditorSelectOverlay::GetSelectedText()
{
    return TextSelectOverlay::GetSelectedText();
}

RectF RichEditorSelectOverlay::GetSelectArea()
{
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(pattern, {});
    auto intersectRect = pattern->GetSelectArea();

    if (hasTransform_) {
        auto textPaintOffset = GetPaintOffsetWithoutTransform();
        intersectRect.SetOffset(intersectRect.GetOffset() - textPaintOffset);
        GetGlobalRectWithTransform(intersectRect);
    }
    return intersectRect;
}

void RichEditorSelectOverlay::OnUpdateMenuInfo(SelectMenuInfo& menuInfo, SelectOverlayDirtyFlag dirtyFlag)
{
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    auto hasValue = pattern->GetTextContentLength() > 0;
    menuInfo.showCopyAll = !pattern->IsSelectAll() && hasValue;
    if (dirtyFlag == DIRTY_COPY_ALL_ITEM) {
        return;
    }
    bool isShowItem = pattern->copyOption_ != CopyOptions::None;
    menuInfo.showCopy = isShowItem && hasValue && !pattern->textSelector_.SelectNothing();
    menuInfo.showCut = isShowItem && hasValue && !pattern->textSelector_.SelectNothing();
    menuInfo.showPaste = IsShowPaste();
    menuInfo.menuIsShow = IsShowMenu();
    menuInfo.showAIWrite = pattern->IsShowAIWrite() && hasValue;
    pattern->UpdateSelectMenuInfo(menuInfo);
}

// param filling except callback
void RichEditorSelectOverlay::OnUpdateSelectOverlayInfo(SelectOverlayInfo& selectInfo, int32_t requestCode)
{
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    BaseTextSelectOverlay::OnUpdateSelectOverlayInfo(selectInfo, requestCode);
    selectInfo.pattern = AceType::WeakClaim(AceType::RawPtr(pattern));
    selectInfo.handlerColor = pattern->GetCaretColor();
    selectInfo.handleReverse = IsHandleReverse();
    OnUpdateOnCreateMenuCallback(selectInfo);
    bool usingMouse = pattern->IsUsingMouse();
    auto responseType = pattern->textResponseType_.value_or(TextResponseType::NONE);
    auto& firstHandle = pattern->textSelector_.firstHandle;
    auto& secondHandle = pattern->textSelector_.secondHandle;
    if (!usingMouse && responseType == TextResponseType::LONG_PRESS && pattern->sourceType_ != SourceType::MOUSE) {
        selectInfo.firstHandle.paintRect = firstHandle;
        selectInfo.secondHandle.paintRect = secondHandle;
    } else {
        if (responseType == TextResponseType::LONG_PRESS) {
            pattern->SetTextResponseType(TextResponseType::RIGHT_CLICK);
            responseType = TextResponseType::RIGHT_CLICK;
        }
        selectInfo.isUsingMouse = true;
        selectInfo.rightClickOffset = pattern->GetSelectionMenuOffset();
        pattern->ResetIsMousePressed();
    }
    selectInfo.menuInfo.responseType = static_cast<int32_t>(responseType);
    selectInfo.menuInfo.editorType = static_cast<int32_t>(pattern->GetEditorType());
    selectInfo.callerFrameNode = pattern->GetHost();
    selectInfo.isNewAvoid = true;
    selectInfo.selectArea = GetSelectArea();
    selectInfo.checkIsTouchInHostArea =
    [weak = AceType::WeakClaim(AceType::RawPtr(pattern))](const PointF& touchPoint) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->IsTouchInFrameArea(touchPoint);
    };
    selectInfo.isSingleHandle = IsSingleHandle();
    selectInfo.recreateOverlay = requestCode == REQUEST_RECREATE;
    CheckMenuParamChange(selectInfo, pattern->GetEditorType(), responseType);
    pattern->CopySelectionMenuParams(selectInfo, responseType);
    if (hasTransform_) {
        selectInfo.callerNodeInfo = {
            .paintFrameRect = GetPaintRectWithTransform(),
            .paintOffset = GetPaintRectOffsetWithTransform()
        };
    }
}
void RichEditorSelectOverlay::CheckMenuParamChange(SelectOverlayInfo& selectInfo,
    TextSpanType selectType, TextResponseType responseType)
{
    auto pattern = GetPattern<RichEditorPattern>();
    auto menuParams = pattern ? pattern->GetMenuParams(selectType, responseType) : nullptr;
    std::pair<TextSpanType, TextResponseType> selectResponseComb = { selectType, responseType };
    selectInfo.recreateOverlay |= (lastMenuParams_ || menuParams) && selectResponseComb != lastSelectResponseComb_;
    lastMenuParams_ = menuParams;
    lastSelectResponseComb_ = selectResponseComb;
}

// set menu callback
void RichEditorSelectOverlay::OnMenuItemAction(OptionMenuActionId id, OptionMenuType type)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "MenuActionId=%{public}d, MenuType=%{public}d", id, type);
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    auto usingMouse = pattern->IsUsingMouse();
    switch (id) {
        case OptionMenuActionId::COPY:
            needRefreshMenu_ = !IsShowPaste() && pattern->copyOption_ != CopyOptions::None;
            pattern->HandleOnCopy();
            break;
        case OptionMenuActionId::CUT:
            pattern->HandleOnCut();
            break;
        case OptionMenuActionId::PASTE:
            pattern->HandleOnPaste();
            CloseOverlay(true, CloseReason::CLOSE_REASON_NORMAL);
            break;
        case OptionMenuActionId::SELECT_ALL:
            pattern->isMousePressed_ = usingMouse;
            pattern->HandleMenuCallbackOnSelectAll();
            break;
        case OptionMenuActionId::CAMERA_INPUT:
            pattern->HandleOnCameraInput();
            break;
        case OptionMenuActionId::AI_WRITE:
            pattern->HandleOnAIWrite();
            break;
        case OptionMenuActionId::DISAPPEAR:
            if (pattern->GetTextDetectEnable() && !pattern->HasFocus()) {
                pattern->ResetSelection();
            }
            break;
        default:
            TAG_LOGI(AceLogTag::ACE_TEXT, "Unsupported menu option id %{public}d", id);
            break;
    }
}

void RichEditorSelectOverlay::ToggleMenu()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    if (manager && !manager->IsMenuShow() && needRefreshMenu_) {
        needRefreshMenu_ = false;
        ProcessOverlay({ .menuIsShow = true, .animation = true, .requestCode = REQUEST_RECREATE });
        return;
    }
    BaseTextSelectOverlay::ToggleMenu();
}

void RichEditorSelectOverlay::OnCloseOverlay(OptionMenuType menuType, CloseReason reason, RefPtr<OverlayInfo> info)
{
    TAG_LOGD(AceLogTag::ACE_TEXT, "menuType=%{public}d, closeReason=%{public}d", menuType, reason);
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    BaseTextSelectOverlay::OnCloseOverlay(menuType, reason, info);
    isHandleMoving_ = false;
    auto needResetSelection = pattern->GetTextDetectEnable() && !pattern->HasFocus() &&
        reason != CloseReason::CLOSE_REASON_DRAG_FLOATING;
    auto isBackPressed = reason == CloseReason::CLOSE_REASON_BACK_PRESSED;
    auto isHoldByOther = reason == CloseReason::CLOSE_REASON_HOLD_BY_OTHER;
    needResetSelection = needResetSelection || isBackPressed || isHoldByOther;
    IF_TRUE(needResetSelection, pattern->ResetSelection());
    IF_TRUE(isHoldByOther, pattern->CloseSelectOverlay());
    if (isBackPressed) {
        IF_TRUE((info && info->isSingleHandle), pattern->OnBackPressed());
        if (!pattern->IsEditing() && pattern->HasFocus()) {
            FocusHub::LostFocusToViewRoot();
        }
        ResumeTwinkling();
    }
}

void RichEditorSelectOverlay::OnHandleGlobalTouchEvent(SourceType sourceType, TouchType touchType, bool touchInside)
{
    BaseTextSelectOverlay::OnHandleGlobalTouchEvent(sourceType, touchType);
    CHECK_NULL_VOID(IsMouseClickDown(sourceType, touchType) || IsTouchUp(sourceType, touchType));
    if (IsSingleHandle()) {
        CloseOverlay(false, CloseReason::CLOSE_REASON_CLICK_OUTSIDE);
        ResumeTwinkling();
    } else {
        HideMenu();
    }
}

void RichEditorSelectOverlay::OnHandleLevelModeChanged(HandleLevelMode mode)
{
    if (handleLevelMode_ != mode && mode == HandleLevelMode::OVERLAY) {
        auto pattern = GetPattern<RichEditorPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->CalculateHandleOffsetAndShowOverlay();
    }
    BaseTextSelectOverlay::OnHandleLevelModeChanged(mode);
}

std::optional<SelectOverlayInfo> RichEditorSelectOverlay::GetSelectOverlayInfo()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_RETURN(manager, std::optional<SelectOverlayInfo>());
    return manager->GetSelectOverlayInfo();
}

bool RichEditorSelectOverlay::IsSingleHandleShow()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_RETURN(manager && manager->IsSingleHandle(), false);
    auto overlayInfo = manager->GetSelectOverlayInfo();
    CHECK_NULL_RETURN(overlayInfo, false);
    return overlayInfo->secondHandle.isShow;
}

void RichEditorSelectOverlay::UpdateMenuOffset()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->MarkInfoChange(DIRTY_SELECT_AREA | DIRTY_ALL_MENU_ITEM);
}

bool RichEditorSelectOverlay::IsBothHandlesShow()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_RETURN(manager && manager->IsHandlesShow(), false);
    auto overlayInfo = manager->GetSelectOverlayInfo();
    CHECK_NULL_RETURN(overlayInfo, false);
    return overlayInfo->firstHandle.isShow && overlayInfo->secondHandle.isShow;
}

bool RichEditorSelectOverlay::IsHandleShow()
{
    return IsBothHandlesShow() || IsSingleHandleShow();
}

void RichEditorSelectOverlay::OnAncestorNodeChanged(FrameNodeChangeInfoFlag flag)
{
    if (IsAncestorNodeGeometryChange(flag)) {
        UpdateAllHandlesOffset();
    }
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    FrameNodeChangeInfoFlag changeFlag = flag;
    if (IsAncestorNodeStartScroll(host->GetChangeInfoFlag()) || IsAncestorNodeEndScroll(host->GetChangeInfoFlag())) {
        auto parent = host->GetAncestorNodeOfFrame(true);
        changeFlag = FRAME_NODE_CHANGE_INFO_NONE;
        while (parent) {
            if (parent->GetChangeInfoFlag() != FRAME_NODE_CHANGE_INFO_NONE) {
                changeFlag = changeFlag | parent->GetChangeInfoFlag();
            }
            parent = parent->GetAncestorNodeOfFrame(true);
        }
    }
    BaseTextSelectOverlay::OnAncestorNodeChanged(changeFlag);
}

void RichEditorSelectOverlay::OnHandleMoveStart(const GestureEvent& event, bool isFirst)
{
    isHandleMoving_ = true;
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    initSelector_ = { pattern->textSelector_.GetTextStart(), pattern->textSelector_.GetTextEnd() };
    pattern->ChangeHandleHeight(event, isFirst, IsOverlayMode());
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->MarkInfoChange(isFirst ? DIRTY_FIRST_HANDLE : DIRTY_SECOND_HANDLE);
    manager->SetHandleCircleIsShow(isFirst, false);
    if (IsSingleHandle()) {
        pattern->ShowCaretWithoutTwinkling();
        manager->SetIsHandleLineShow(false);
    }
}

void RichEditorSelectOverlay::OnOverlayTouchDown(const TouchEventInfo& event)
{
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    if (event.GetSourceTool() == SourceTool::MOUSE && IsHandleShow()) {
        pattern->CloseSelectOverlay();
    }
    pattern->RequestFocusWhenSelected();
}

void RichEditorSelectOverlay::UpdateHandleOffset()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->MarkInfoChange(DIRTY_FIRST_HANDLE | DIRTY_SECOND_HANDLE);
}

void RichEditorSelectOverlay::UpdateSelectOverlayOnAreaChanged()
{
    CHECK_NULL_VOID(SelectOverlayIsOn() || SelectOverlayIsCreating());
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->CalculateHandleOffsetAndShowOverlay();
    UpdateHandleOffset();
}

void RichEditorSelectOverlay::SwitchCaretState(std::shared_ptr<SelectOverlayInfo> info)
{
    CHECK_NULL_VOID(info && IsSingleHandle() && !isHandleMoving_);
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    bool isSingleHandleShow = !handleIsHidden_ && info->secondHandle.isShow;
    bool isCaretTwinkling = pattern->caretTwinkling_ && !pattern->isCursorAlwaysDisplayed_;
    CHECK_NULL_VOID(isSingleHandleShow == isCaretTwinkling);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "Switch caret state singleHandleShow=%{public}d", isSingleHandleShow);
    if (isSingleHandleShow) {
        pattern->StopTwinkling();
    } else {
        ResumeTwinkling();
    }
}

void RichEditorSelectOverlay::ResumeTwinkling()
{
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern && pattern->IsEditing());
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "only show caret for edit state");
    pattern->isCursorAlwaysDisplayed_ = false;
    pattern->StartTwinkling();
}

void RichEditorSelectOverlay::OnHandleIsHidden()
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "Start twinking when singleHandle hide");
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->isCursorAlwaysDisplayed_ = false;
    pattern->StartTwinkling();
    handleIsHidden_ = true;
}

void RichEditorSelectOverlay::OnOverlayClick(const GestureEvent& event, bool isFirst)
{
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    if (!pattern->IsEditing() && !IsSingleHandle()) {
        ToggleMenu();
    }
    auto globalOffset = pattern->GetGlobalOffset();
    auto overlayEvent = event;
    auto localLocation = Offset(overlayEvent.GetGlobalLocation().GetX() - globalOffset.GetX(),
        overlayEvent.GetGlobalLocation().GetY() - globalOffset.GetY());
    overlayEvent.SetLocalLocation(localLocation);
    pattern->HandleClickEvent(overlayEvent);
}

void RichEditorSelectOverlay::OnHandleMouseEvent(const MouseInfo& event)
{
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    if (event.GetAction() == MouseAction::PRESS && IsHandleShow()) {
        pattern->CloseSelectOverlay();
    }
}

void RichEditorSelectOverlay::OnAfterSelectOverlayShow(bool isCreate)
{
    handleIsHidden_ = false;
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->MarkInfoChange(DIRTY_SELECT_AREA);
    if (IsSingleHandleShow()) {
        auto pattern = GetPattern<RichEditorPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->StopTwinkling();
    }
}

float RichEditorSelectOverlay::GetHandleHotZoneRadius()
{
    auto hotZoneRadius = 0.0f;
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(pattern, hotZoneRadius);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, hotZoneRadius);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, hotZoneRadius);
    auto theme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_RETURN(theme, hotZoneRadius);
    hotZoneRadius = theme->GetHandleHotZoneRadius().ConvertToPx();
    return hotZoneRadius;
}

void RichEditorSelectOverlay::OnHandleMarkInfoChange(
    std::shared_ptr<SelectOverlayInfo> info, SelectOverlayDirtyFlag flag)
{
    IF_TRUE((flag & DIRTY_SECOND_HANDLE) == DIRTY_SECOND_HANDLE, SwitchCaretState(info));
    CHECK_NULL_VOID((flag & UPDATE_HANDLE_COLOR_FLAG) == UPDATE_HANDLE_COLOR_FLAG);
    CHECK_NULL_VOID(info);

    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    info->handlerColor = pattern->caretColor_;
    manager->MarkHandleDirtyNode(PROPERTY_UPDATE_RENDER);
}

void RichEditorSelectOverlay::UpdateHandleColor()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->MarkInfoChange(UPDATE_HANDLE_COLOR_FLAG);
}

} // namespace OHOS::Ace::NG
