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

#include "core/components_ng/pattern/text_field/text_field_select_overlay.h"

#include <algorithm>

#include "base/geometry/ng/rect_t.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/manager/select_content_overlay/select_content_overlay_manager.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text_field/text_field_paint_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/event/ace_events.h"
#include "core/event/touch_event.h"

#if not defined(ACE_UNITTEST)
#if defined(ENABLE_STANDARD_INPUT)
#include "input_method_controller.h"
#endif
#endif

namespace OHOS::Ace::NG {
namespace {
// uncertainty range when comparing selectedTextBox to contentRect
constexpr float BOX_EPSILON = 0.5f;
constexpr int32_t REQUEST_SELECT_ALL = 1 << 1;
} // namespace

bool TextFieldSelectOverlay::PreProcessOverlay(const OverlayRequest& request)
{
    auto pattern = GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, false);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    bool isHideRightClickMenu = layoutProperty->GetSelectionMenuHiddenValue(false) && IsUsingMouse();
    bool isFontSizeZero = layoutProperty->HasFontSize() && NearZero(layoutProperty->GetFontSize()->Value());
    if (isHideRightClickMenu || isFontSizeZero) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD,
            "The selection menu is not displayed cause Font size is zero or selectionMenuHidden is true");
        return false;
    }
    UpdatePattern(request);
    CHECK_NULL_RETURN(!pattern->IsTransparent(), false);
    pattern->ShowSelect();
    return true;
}

void TextFieldSelectOverlay::UpdatePattern(const OverlayRequest& request)
{
    auto pattern = GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto isRequestSelectAll = (request.requestCode & REQUEST_SELECT_ALL) == REQUEST_SELECT_ALL;
    auto selectController = pattern->GetTextSelectController();
    selectController->CalculateHandleOffset();
    if (pattern->IsSelected() && selectController->IsHandleSamePosition()) {
        SetIsSingleHandle(true);
        selectController->UpdateCaretIndex(selectController->GetFirstHandleIndex());
        selectController->UpdateCaretOffset();
        selectController->MoveCaretToContentRect(selectController->GetCaretIndex());
    } else if (!IsSingleHandle() && !isRequestSelectAll) {
        auto rects = pattern->GetTextBoxes();
        if (!rects.empty() && NearEqual(rects.size(), 1) && NearZero(rects[0].Width())) {
            SetIsSingleHandle(true);
            selectController->UpdateCaretIndex(selectController->GetFirstHandleIndex());
            selectController->UpdateCaretOffset();
        }
    }
    if (IsSingleHandle()) {
        pattern->StartTwinkling();
    }
}

void TextFieldSelectOverlay::OnAfterSelectOverlayShow(bool isCreate)
{
    CHECK_NULL_VOID(latestReqeust_);
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    if (latestReqeust_->hideHandle) {
        manager->HideHandle();
    }
    manager->MarkInfoChange(DIRTY_SELECT_TEXT);
    latestReqeust_.reset();
}

void TextFieldSelectOverlay::OnCloseOverlay(OptionMenuType menuType, CloseReason reason)
{
    CloseMagnifier();
    if (CloseReason::CLOSE_REASON_BACK_PRESSED == reason) {
        OnResetTextSelection();
    }
}

void TextFieldSelectOverlay::OnHandleGlobalTouchEvent(SourceType sourceType, TouchType touchType)
{
    BaseTextSelectOverlay::OnHandleGlobalTouchEvent(sourceType, touchType);
    SetLastSourceType(sourceType);
}

void TextFieldSelectOverlay::HandleOnShowMenu()
{
    auto selectArea = GetSelectArea();
    if (Negative(selectArea.Width()) || Negative(selectArea.Height())) {
        TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "The selected area is not visible.");
        return;
    }
    if (SelectOverlayIsOn()) {
        auto manager = GetManager<SelectContentOverlayManager>();
        manager->ShowOptionMenu();
        return;
    }
    auto pattern = GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    SetUsingMouse(lastSourceType_ == SourceType::MOUSE);
    if (IsUsingMouse()) {
        auto controller = pattern->GetTextSelectController();
        SetMouseMenuOffset(controller->GetCaretRect().GetOffset() + pattern->GetParentGlobalOffset());
    } else {
        auto isSingleHandle = pattern->GetTextContentController()->IsEmpty() || !pattern->IsSelected();
        SetIsSingleHandle(isSingleHandle);
    }
    ProcessOverlay({ .animation = true });
}

std::optional<SelectHandleInfo> TextFieldSelectOverlay::GetFirstHandleInfo()
{
    return IsSingleHandle() ? std::nullopt : GetHandleInfo(HandleIndex::FIRST);
}

std::optional<SelectHandleInfo> TextFieldSelectOverlay::GetSecondHandleInfo()
{
    return IsSingleHandle() ? GetHandleInfo(HandleIndex::CARET) : GetHandleInfo(HandleIndex::SECOND);
}

std::optional<SelectHandleInfo> TextFieldSelectOverlay::GetHandleInfo(HandleIndex handlIndex)
{
    auto pattern = GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto controller = pattern->GetTextSelectController();
    CHECK_NULL_RETURN(controller, std::nullopt);
    RectF handleRect;
    if (handlIndex == HandleIndex::FIRST) {
        handleRect = controller->GetFirstHandleRect();
    } else if (handlIndex == HandleIndex::SECOND) {
        handleRect = controller->GetSecondHandleRect();
        auto contentHeight = pattern->GetTextContentRect().Height();
        auto handleHeight = std::min(handleRect.Height(), contentHeight);
        handleRect.SetHeight(handleHeight);
    } else {
        handleRect = controller->GetCaretRect();
    }
    auto localHandleRect = handleRect;
    SelectHandleInfo handleInfo;
    handleRect.SetOffset(handleRect.GetOffset() + GetPaintOffsetWithoutTransform());
    handleInfo.paintRect = handleRect;
    handleInfo.isShow = CheckHandleVisible(handleRect);

    SetTransformPaintInfo(handleInfo, localHandleRect);
    return handleInfo;
}

bool TextFieldSelectOverlay::CheckHandleVisible(const RectF& paintRect)
{
    auto pattern = GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, false);
    // use global offset.
    auto contentRect = pattern->GetContentRect();
    auto visibleRect = GetVisibleContentRect();
    if (!pattern->IsTextArea()) {
        auto verticalEpsilon = std::max(0.0f, paintRect.Height() - contentRect.Height());
        return GreatOrEqual(paintRect.Top() + verticalEpsilon, visibleRect.Top()) &&
               LessOrEqual(paintRect.Bottom() - verticalEpsilon, visibleRect.Bottom()) &&
               LessOrEqual(paintRect.Left() - paintRect.Width() - BOX_EPSILON, visibleRect.Right()) &&
               GreatOrEqual(paintRect.Right(), visibleRect.Left());
    }
    PointF bottomPoint = { paintRect.Left(), paintRect.Bottom() - BOX_EPSILON };
    PointF topPoint = { paintRect.Left(), paintRect.Top() + BOX_EPSILON };
    visibleRect.SetLeft(visibleRect.GetX() - BOX_EPSILON);
    visibleRect.SetWidth(visibleRect.Width() + 2.0f * BOX_EPSILON);
    visibleRect.SetTop(visibleRect.GetY() - BOX_EPSILON);
    visibleRect.SetHeight(visibleRect.Height() + 2.0f * BOX_EPSILON);
    return visibleRect.IsInRegion(bottomPoint) && visibleRect.IsInRegion(topPoint);
}

void TextFieldSelectOverlay::OnResetTextSelection()
{
    auto pattern = GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCaretPosition(pattern->GetTextSelectController()->GetEndIndex());
}

void TextFieldSelectOverlay::AfterCloseOverlay()
{
    CloseMagnifier();
}

void TextFieldSelectOverlay::CloseMagnifier()
{
    auto pattern = GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    if (pattern->GetMagnifierController()->GetShowMagnifier()) {
        pattern->GetMagnifierController()->UpdateShowMagnifier();
    }
}

void TextFieldSelectOverlay::OnUpdateMenuInfo(SelectMenuInfo& menuInfo, SelectOverlayDirtyFlag dirtyFlag)
{
    auto pattern = GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto hasText = pattern->IsOperation();
    if ((dirtyFlag & DIRTY_COPY_ALL_ITEM) == DIRTY_COPY_ALL_ITEM) {
        menuInfo.showCopyAll = hasText && !pattern->IsSelectAll();
        return;
    }
    bool isHideSelectionMenu = layoutProperty->GetSelectionMenuHiddenValue(false);
#if defined(ENABLE_STANDARD_INPUT)
    auto inputMethod = MiscServices::InputMethodController::GetInstance();
    auto isSupportCameraInput = inputMethod &&
                                inputMethod->IsInputTypeSupported(MiscServices::InputType::CAMERA_INPUT) &&
                                !pattern->IsInPasswordMode();
#else
    auto isSupportCameraInput = false;
#endif
    menuInfo.showCameraInput = !pattern->IsSelected() && isSupportCameraInput && !pattern->HasCustomKeyboard();
    if (IsUsingMouse()) {
        auto manager = SelectContentOverlayManager::GetOverlayManager();
        CHECK_NULL_VOID(manager);
        menuInfo.menuIsShow = !isHideSelectionMenu || manager->IsOpen();
    } else {
        menuInfo.menuIsShow = (hasText || IsShowPaste() || menuInfo.showCameraInput) &&
            !isHideSelectionMenu && IsShowMenu();
    }
    menuInfo.menuDisable = isHideSelectionMenu;
    menuInfo.showPaste = IsShowPaste();
    menuInfo.menuType = IsUsingMouse() ? OptionMenuType::MOUSE_MENU : OptionMenuType::TOUCH_MENU;
    menuInfo.showCopy = hasText && pattern->AllowCopy() && pattern->IsSelected();
    menuInfo.showCut = menuInfo.showCopy;
    menuInfo.showCopyAll = hasText && !pattern->IsSelectAll();
}

void TextFieldSelectOverlay::OnUpdateSelectOverlayInfo(SelectOverlayInfo& overlayInfo, int32_t requestCode)
{
    BaseTextSelectOverlay::OnUpdateSelectOverlayInfo(overlayInfo, requestCode);
    auto textFieldPattern = GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    auto paintProperty = textFieldPattern->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    overlayInfo.handlerColor = paintProperty->GetCursorColor();
    overlayInfo.menuOptionItems = textFieldPattern->GetMenuOptionItems();
}

RectF TextFieldSelectOverlay::GetSelectArea()
{
    auto pattern = GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, {});
    auto selectRects = pattern->GetTextBoxes();
    RectF res(pattern->GetCaretRect());
    auto textPaintOffset = GetPaintOffsetWithoutTransform();
    if (selectRects.empty()) {
        if (hasTransform_) {
            GetGlobalRectWithTransform(res);
        } else {
            res.SetOffset(res.GetOffset() + textPaintOffset);
        }
        return res;
    }
    auto contentRect = pattern->GetContentRect();
    auto textRect = pattern->GetTextRect();
    res = MergeSelectedBoxes(selectRects, contentRect, textRect, textPaintOffset);
    auto globalContentRect = GetVisibleContentRect();
    auto intersectRect = res.IntersectRectT(globalContentRect);
    if (hasTransform_) {
        intersectRect.SetOffset(intersectRect.GetOffset() - textPaintOffset);
        GetGlobalRectWithTransform(intersectRect);
    }
    return intersectRect;
}

std::string TextFieldSelectOverlay::GetSelectedText()
{
    auto pattern = GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, "");
    auto start = pattern->GetTextSelectController()->GetStartIndex();
    auto end = pattern->GetTextSelectController()->GetEndIndex();
    return pattern->GetTextContentController()->GetSelectedValue(start, end);
}

void TextFieldSelectOverlay::OnMenuItemAction(OptionMenuActionId id, OptionMenuType type)
{
    auto pattern = GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Handle overlay menu, men id %{public}d, menu type %{public}d", id, type);
    switch (id) {
        case OptionMenuActionId::COPY:
            pattern->HandleOnCopy();
            return;
        case OptionMenuActionId::CUT:
            pattern->HandleOnCut();
            return;
        case OptionMenuActionId::SELECT_ALL:
            pattern->HandleOnSelectAll(type == OptionMenuType::MOUSE_MENU, false, true);
            return;
        case OptionMenuActionId::PASTE:
            pattern->HandleOnPaste();
            return;
        case OptionMenuActionId::CAMERA_INPUT:
            pattern->HandleOnCameraInput();
            return;
        default:
            return;
    }
}

int32_t TextFieldSelectOverlay::GetTextAreaCaretPosition(const OffsetF& localOffset)
{
    auto pattern = GetPattern<TextFieldPattern>();
    auto contentRect = pattern->GetContentRect();
    auto paddingLeft = pattern->GetPaddingLeft();
    auto textRect = pattern->GetTextRect();
    auto lineHeight = pattern->PreferredLineHeight();
    Offset offset;
    if (LessNotEqual(localOffset.GetY(), contentRect.GetY())) {
        offset = Offset(localOffset.GetX() - paddingLeft, localOffset.GetY() - textRect.GetY() - lineHeight);
    } else if (GreatOrEqual(localOffset.GetY(), contentRect.GetY() + contentRect.Height())) {
        offset = Offset(localOffset.GetX() - paddingLeft, localOffset.GetY() - textRect.GetY() + lineHeight);
    } else {
        offset = Offset(localOffset.GetX() - paddingLeft, localOffset.GetY() - textRect.GetY());
    }
    return pattern->ConvertTouchOffsetToCaretPosition(offset);
}

int32_t TextFieldSelectOverlay::GetTextInputCaretPosition(const OffsetF& localOffset)
{
    auto pattern = GetPattern<TextFieldPattern>();
    auto contentRect = pattern->GetContentRect();
    auto selectController = pattern->GetTextSelectController();
    auto wideText = pattern->GetWideText();
    if (LessNotEqual(localOffset.GetX(), contentRect.GetX())) {
        auto startIndex = selectController->GetStartIndex();
        auto len = pattern->GetGraphemeClusterLength(wideText, startIndex, true);
        return std::max(startIndex - len, 0);
    }
    if (GreatOrEqual(localOffset.GetX(), contentRect.GetX() + contentRect.Width())) {
        auto endIndex = selectController->GetEndIndex();
        auto len = pattern->GetGraphemeClusterLength(wideText, endIndex);
        return std::min(endIndex + len, pattern->GetContentWideTextLength());
    }
    Offset offset(localOffset.GetX() - pattern->GetTextRect().GetX(), 0.0f);
    return pattern->ConvertTouchOffsetToCaretPosition(offset);
}

int32_t TextFieldSelectOverlay::GetCaretPositionOnHandleMove(const OffsetF& localOffset)
{
    auto pattern = GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(pattern, 0);
    if (pattern->IsTextArea()) {
        return GetTextAreaCaretPosition(localOffset);
    }
    return GetTextInputCaretPosition(localOffset);
}

void TextFieldSelectOverlay::OnHandleMove(const RectF& handleRect, bool isFirst)
{
    auto pattern = GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->IsOperation());
    auto localOffset = handleRect.GetOffset() - GetPaintOffsetWithoutTransform();
    auto selectController = pattern->GetTextSelectController();
    if (pattern->GetMagnifierController()) {
        auto movingCaretOffset =
            selectController->CalcCaretOffsetByOffset(Offset(localOffset.GetX(), localOffset.GetY()));
        GetLocalPointWithTransform(movingCaretOffset);
        pattern->SetMovingCaretOffset(movingCaretOffset);
        auto magnifierLocalOffset = localOffset;
        GetLocalPointWithTransform(magnifierLocalOffset);
        pattern->GetMagnifierController()->SetLocalOffset(magnifierLocalOffset);
    }
    if (IsSingleHandle()) {
        selectController->UpdateCaretInfoByOffset(Offset(localOffset.GetX(), localOffset.GetY()));
    } else {
        auto position = GetCaretPositionOnHandleMove(localOffset);
        if (isFirst) {
            selectController->MoveFirstHandleToContentRect(position);
            UpdateSecondHandleOffset();
        } else {
            selectController->MoveSecondHandleToContentRect(position);
            UpdateFirstHandleOffset();
        }
    }
    auto tmpHost = pattern->GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldSelectOverlay::OnHandleMoveDone(const RectF& rect, bool isFirst)
{
    auto pattern = GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto overlayManager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(overlayManager);
    if (!layoutProperty->GetSelectionMenuHiddenValue(false)) {
        overlayManager->MarkInfoChange(DIRTY_COPY_ALL_ITEM);
    }
    if (pattern->GetMagnifierController()) {
        pattern->GetMagnifierController()->UpdateShowMagnifier();
    }
    auto selectController = pattern->GetTextSelectController();
    if (!IsSingleHandle()) {
        if (selectController->GetFirstHandleIndex() == selectController->GetSecondHandleIndex()) {
            CloseOverlay(true, CloseReason::CLOSE_REASON_NORMAL);
            pattern->StartTwinkling();
            selectController->MoveCaretToContentRect(pattern->GetCaretIndex());
        } else {
            overlayManager->MarkInfoChange(DIRTY_DOUBLE_HANDLE | DIRTY_SELECT_AREA | DIRTY_SELECT_TEXT);
        }
    } else {
        overlayManager->MarkInfoChange(DIRTY_SECOND_HANDLE);
    }
    overlayManager->ShowOptionMenu();
    auto tmpHost = pattern->GetHost();
    CHECK_NULL_VOID(tmpHost);
    tmpHost->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextFieldSelectOverlay::ProcessSelectAllOverlay(const OverlayRequest& request)
{
    OverlayRequest newRequest = request;
    newRequest.requestCode = newRequest.requestCode | REQUEST_SELECT_ALL;
    ProcessOverlay(newRequest);
}
} // namespace OHOS::Ace::NG
