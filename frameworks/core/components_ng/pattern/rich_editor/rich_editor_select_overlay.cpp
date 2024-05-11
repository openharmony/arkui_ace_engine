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


#include <algorithm>
#include <optional>

#include "base/utils/utils.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/manager/select_content_overlay/select_content_overlay_manager.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float BOX_EPSILON = 0.5f;
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
    return true;
}

std::optional<SelectHandleInfo> RichEditorSelectOverlay::GetFirstHandleInfo()
{
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    SelectHandleInfo handleInfo;
    handleInfo.paintRect = pattern->textSelector_.firstHandle;
    handleInfo.isShow = CheckHandleVisible(handleInfo.paintRect);
    return handleInfo;
}

std::optional<SelectHandleInfo> RichEditorSelectOverlay::GetSecondHandleInfo()
{
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    SelectHandleInfo handleInfo;
    handleInfo.paintRect = pattern->textSelector_.secondHandle;
    handleInfo.isShow = CheckHandleVisible(handleInfo.paintRect);
    return handleInfo;
}

bool RichEditorSelectOverlay::CheckHandleVisible(const RectF& paintRect)
{
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);

    auto contentRect = pattern->GetTextContentRect();
    auto parentGlobalOffset = pattern->GetParentGlobalOffset();
    RectF visibleContentRect(contentRect.GetOffset() + parentGlobalOffset, contentRect.GetSize());
    auto parent = host->GetAncestorNodeOfFrame();
    visibleContentRect = GetVisibleContentRect();
    PointF bottomPoint = { paintRect.Left(), paintRect.Bottom() - BOX_EPSILON };
    PointF topPoint = { paintRect.Left(), paintRect.Top() + BOX_EPSILON };
    if (IsSingleHandle()) {
        return visibleContentRect.IsInRegion(bottomPoint);
    }
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
}

void RichEditorSelectOverlay::RemoveAreaChangeInner()
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    textPattern->RemoveAreaChangeInner();
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
    auto localOffset = handleRect.GetOffset() - parentGlobalOffset;
    auto contentRect = pattern->GetContentRect();
    auto caretRect = pattern->GetCaretRect();
    float x = std::clamp(localOffset.GetX(), contentRect.Left(), contentRect.Right() - caretRect.Width());
    float y = std::clamp(localOffset.GetY(), contentRect.Top(), contentRect.Bottom() - caretRect.Height());
    localOffset = OffsetF(x, y);
    pattern->magnifierController_->SetLocalOffset(localOffset);
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

void RichEditorSelectOverlay::UpdateSelectorOnHandleMove(const OffsetF& handleOffset, bool isFirst)
{
    auto pattern = GetPattern<RichEditorPattern>();
    auto& textSelector = pattern->textSelector_;
    auto currentHandleIndex = pattern->GetHandleIndex(Offset(handleOffset.GetX(), handleOffset.GetY()));
    pattern->SetCaretPosition(currentHandleIndex);
    if (isFirst) {
        pattern->HandleSelectionChange(currentHandleIndex, textSelector.destinationOffset);
    } else {
        if (IsSingleHandle()) {
            auto textOffset = handleOffset + pattern->contentRect_.GetOffset() - pattern->richTextRect_.GetOffset();
            pattern->CalcAndRecordLastClickCaretInfo(Offset(textOffset.GetX(), textOffset.GetY()));
            textSelector.Update(currentHandleIndex);
        } else {
            pattern->HandleSelectionChange(textSelector.baseOffset, currentHandleIndex);
        }
    }
}

void RichEditorSelectOverlay::OnHandleMoveDone(const RectF& handleRect, bool isFirstHandle)
{
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
        pattern->SetCaretPosition(selectEnd);
    }
    pattern->CalculateHandleOffsetAndShowOverlay();
    pattern->StopAutoScroll();
    pattern->magnifierController_->UpdateShowMagnifier();
    if (!IsSingleHandleShow() && textSelector.StartEqualToDest()) {
        HideMenu();
        CloseOverlay(true, CloseReason::CLOSE_REASON_NORMAL);
        pattern->StartTwinkling();
        return;
    }
    auto overlayManager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(overlayManager);
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
    return pattern->GetSelectArea();
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
    pattern->UpdateSelectMenuInfo(menuInfo);
}

// param filling except callback
void RichEditorSelectOverlay::OnUpdateSelectOverlayInfo(SelectOverlayInfo& selectInfo, int32_t requestCode)
{
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    selectInfo.pattern = AceType::WeakClaim(AceType::RawPtr(pattern));
    selectInfo.handlerColor = pattern->GetCaretColor();
    selectInfo.handleReverse = IsHandleReverse();
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
    selectInfo.selectArea = pattern->GetSelectArea();
    selectInfo.checkIsTouchInHostArea =
    [weak = AceType::WeakClaim(AceType::RawPtr(pattern))](const PointF& touchPoint) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->IsTouchInFrameArea(touchPoint);
    };
    if (IsSingleHandle()) {
        selectInfo.isHandleLineShow = false;
        selectInfo.isSingleHandle = true;
    }
    selectInfo.recreateOverlay = requestCode == REQUEST_RECREATE;
    CheckEditorTypeChange(selectInfo, pattern->GetEditorType());
    pattern->CopySelectionMenuParams(selectInfo, responseType);
}

void RichEditorSelectOverlay::CheckEditorTypeChange(SelectOverlayInfo& selectInfo, TextSpanType selectType)
{
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    CHECK_NULL_VOID(manager);
    CHECK_NULL_VOID(manager->IsOpen());
    auto overlayInfo = manager->GetSelectOverlayInfo();
    CHECK_NULL_VOID(overlayInfo);
    auto lastSelectType = overlayInfo->menuInfo.editorType.value_or(static_cast<int32_t>(TextSpanType::NONE));
    // need to recreate overlay, when overlay is on, but select type changed
    if (lastSelectType != static_cast<int32_t>(selectType)) {
        selectInfo.recreateOverlay = true;
    }
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

void RichEditorSelectOverlay::OnCloseOverlay(OptionMenuType menuType, CloseReason reason, RefPtr<OverlayInfo> info)
{
    TAG_LOGD(AceLogTag::ACE_TEXT, "menuType=%{public}d, closeReason=%{public}d", menuType, reason);
    auto pattern = GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetTextDetectEnable() && !pattern->HasFocus()) {
        pattern->ResetSelection();
    }
    if (reason == CloseReason::CLOSE_REASON_BACK_PRESSED) {
        pattern->ResetSelection();
        pattern->StartTwinkling();
    }
}

void RichEditorSelectOverlay::OnHandleGlobalTouchEvent(SourceType sourceType, TouchType touchType)
{
    BaseTextSelectOverlay::OnHandleGlobalTouchEvent(sourceType, touchType);
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
    CHECK_NULL_RETURN(manager, false);
    return manager->IsSingleHandle();
}

void RichEditorSelectOverlay::UpdateMenuOffset()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->MarkInfoChange(DIRTY_SELECT_AREA | DIRTY_ALL_MENU_ITEM);
}

bool RichEditorSelectOverlay::IsHandlesShow()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_RETURN(manager, false);
    return manager->IsHandlesShow();
}
} // namespace OHOS::Ace::NG
