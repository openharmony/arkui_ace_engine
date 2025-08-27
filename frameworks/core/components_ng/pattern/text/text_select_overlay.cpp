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

#include "core/components_ng/pattern/text/text_select_overlay.h"

#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float BOX_EPSILON = 0.5f;
}

bool TextSelectOverlay::PreProcessOverlay(const OverlayRequest& request)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, false);
    SetUsingMouse(textPattern->IsUsingMouse());
    SetEnableHandleLevel(true);
    SetEnableSubWindowMenu(true);
    textPattern->CalculateHandleOffsetAndShowOverlay();
    selectTextUseTopHandle = true;
    CheckEnableContainerModal();
    return true;
}

std::optional<SelectHandleInfo> TextSelectOverlay::GetFirstHandleInfo()
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, std::nullopt);
    SelectHandleInfo handleInfo;
    handleInfo.paintRect = textPattern->GetTextSelector().firstHandle;
    handleInfo.isShow = CheckAndAdjustHandle(handleInfo.paintRect);

    auto localPaintRect = textPattern->GetTextSelector().firstHandle;
    localPaintRect.SetOffset(localPaintRect.GetOffset() - GetPaintOffsetWithoutTransform());
    handleInfo.localPaintRect = localPaintRect;
    SetTransformPaintInfo(handleInfo, localPaintRect);
    handleInfo.forceDraw = !CheckSwitchToMode(HandleLevelMode::OVERLAY);
    return handleInfo;
}

std::optional<SelectHandleInfo> TextSelectOverlay::GetSecondHandleInfo()
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, std::nullopt);
    SelectHandleInfo handleInfo;
    handleInfo.paintRect = textPattern->GetTextSelector().secondHandle;
    handleInfo.isShow = CheckAndAdjustHandle(handleInfo.paintRect);

    auto localPaintRect = textPattern->GetTextSelector().secondHandle;
    localPaintRect.SetOffset(localPaintRect.GetOffset() - GetPaintOffsetWithoutTransform());
    handleInfo.localPaintRect = localPaintRect;
    SetTransformPaintInfo(handleInfo, localPaintRect);
    handleInfo.forceDraw = !CheckSwitchToMode(HandleLevelMode::OVERLAY);
    return handleInfo;
}

RectF TextSelectOverlay::GetHandleLocalPaintRect(DragHandleIndex dragHandleIndex)
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, RectF());
    RectF localPaintRect;
    if (dragHandleIndex == DragHandleIndex::FIRST) {
        localPaintRect = textPattern->GetTextSelector().firstHandle;
    } else if (dragHandleIndex == DragHandleIndex::SECOND) {
        localPaintRect = textPattern->GetTextSelector().secondHandle;
    } else { // dragHandleIndex::NONE
        return RectF();
    }
    localPaintRect.SetOffset(localPaintRect.GetOffset() - GetPaintOffsetWithoutTransform());
    return localPaintRect;
}

bool TextSelectOverlay::CheckAndAdjustHandle(RectF& paintRect)
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, false);
    auto host = textPattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    if (!GetRenderClipValue()) {
        if (handleLevelMode_ == HandleLevelMode::EMBED) {
            return true;
        }
        auto contentRect = textPattern->GetTextContentRect();
        auto localPaintRect = paintRect;
        localPaintRect.SetOffset(localPaintRect.GetOffset() - GetPaintOffsetWithoutTransform());
        localPaintRect.SetOffset(OffsetF(localPaintRect.GetX() + localPaintRect.Width() / 2.0f, localPaintRect.GetY()));
        auto visibleContentRect = contentRect.CombineRectT(localPaintRect);
        visibleContentRect.SetOffset(visibleContentRect.GetOffset() + textPattern->GetTextPaintOffset());
        visibleContentRect = GetVisibleRect(host, visibleContentRect);
        return CheckAndAdjustHandleWithContent(visibleContentRect, paintRect);
    }
    auto contentRect = textPattern->GetTextContentRect();
    RectF visibleContentRect(contentRect.GetOffset() + textPattern->GetTextPaintOffset(), contentRect.GetSize());
    if (handleLevelMode_ == HandleLevelMode::OVERLAY) {
        visibleContentRect = GetVisibleRect(host, visibleContentRect);
    }
    return CheckAndAdjustHandleWithContent(visibleContentRect, paintRect);
}

bool TextSelectOverlay::CheckAndAdjustHandleWithContent(const RectF& visibleContentRect, RectF& paintRect)
{
    auto paintLeft = paintRect.GetX() + paintRect.Width() / 2.0f;
    PointF bottomPoint = { paintLeft, paintRect.Bottom() - BOX_EPSILON };
    PointF topPoint = { paintLeft, paintRect.Top() + BOX_EPSILON };
    bool bottomInRegion = visibleContentRect.IsInRegion(bottomPoint);
    bool topInRegion = visibleContentRect.IsInRegion(topPoint);
    if (IsClipHandleWithViewPort()) {
        return bottomInRegion || topInRegion;
    }
    if (!bottomInRegion && topInRegion) {
        paintRect.SetHeight(visibleContentRect.Bottom() - paintRect.Top());
    } else if (bottomInRegion && !topInRegion) {
        paintRect.SetHeight(paintRect.Bottom() - visibleContentRect.Top());
        paintRect.SetTop(visibleContentRect.Top());
    }
    return bottomInRegion || topInRegion;
}

bool TextSelectOverlay::CheckHandleVisible(const RectF& paintRect)
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, false);
    auto host = textPattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    if (!GetRenderClipValue()) {
        return true;
    }
    auto contentRect = textPattern->GetTextContentRect();
    RectF visibleContentRect(contentRect.GetOffset() + textPattern->GetTextPaintOffset(), contentRect.GetSize());
    visibleContentRect = GetVisibleRect(host, visibleContentRect);
    PointF bottomPoint = { paintRect.Left(), paintRect.Bottom() - BOX_EPSILON };
    PointF topPoint = { paintRect.Left(), paintRect.Top() + BOX_EPSILON };
    return visibleContentRect.IsInRegion(bottomPoint) && visibleContentRect.IsInRegion(topPoint);
}

void TextSelectOverlay::OnResetTextSelection()
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    textPattern->ResetSelection();
}

void TextSelectOverlay::OnHandleMove(const RectF& handleRect, bool isFirst)
{
    if (!SelectOverlayIsOn()) {
        return;
    }
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    auto host = textPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto localHandleOffset = handleRect.GetOffset();
    if (IsOverlayMode()) {
        localHandleOffset -= GetPaintOffsetWithoutTransform();
    }
    localHandleOffset.SetY(localHandleOffset.GetY() + handleRect.Height() / 2.0f);
    if (textPattern->HasContent() && textPattern->GetOrCreateMagnifier()) {
        textPattern->GetMagnifierController()->SetLocalOffset(localHandleOffset);
    }
    // the handle position is calculated based on the middle of the handle height.
    auto handleOffset = GetHandleReferenceOffset(handleRect);
    UpdateSelectorOnHandleMove(handleOffset, isFirst);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    auto overlayManager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->MarkInfoChange(DIRTY_SELECT_TEXT);
}

OffsetF TextSelectOverlay::GetHandleReferenceOffset(const RectF& handleRect)
{
    auto handleOffset = handleRect.GetOffset();
    handleOffset.SetY(handleOffset.GetY() + handleRect.Height() / 2.0f);
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, handleOffset);
    auto contentRect = textPattern->GetTextContentRect();
    auto contentOffset = contentRect.GetOffset();
    if (IsOverlayMode()) {
        contentOffset = contentOffset + GetPaintOffsetWithoutTransform();
    }
    if (GetRenderClipValue()) {
        handleOffset.SetX(
            std::clamp(handleOffset.GetX(), contentOffset.GetX(), contentOffset.GetX() + contentRect.Width()));
        handleOffset.SetY(
            std::clamp(handleOffset.GetY(), contentOffset.GetY(), contentOffset.GetY() + contentRect.Height()));
    }
    auto textPaintOffset = contentOffset - OffsetF(0.0f, std::min(textPattern->GetBaselineOffset(), 0.0f));
    handleOffset -= textPaintOffset;
    return handleOffset;
}

void TextSelectOverlay::UpdateSelectorOnHandleMove(const OffsetF& handleOffset, bool isFirstHandle)
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    auto currentHandleIndex = textPattern->GetHandleIndex(Offset(handleOffset.GetX(), handleOffset.GetY()));
    if (isFirstHandle) {
        textPattern->StartVibratorByIndexChange(currentHandleIndex, textPattern->GetTextSelector().baseOffset);
        textPattern->HandleSelectionChange(currentHandleIndex, textPattern->GetTextSelector().destinationOffset);
    } else {
        textPattern->StartVibratorByIndexChange(currentHandleIndex, textPattern->GetTextSelector().destinationOffset);
        textPattern->HandleSelectionChange(textPattern->GetTextSelector().baseOffset, currentHandleIndex);
    }
}

void TextSelectOverlay::OnHandleMoveDone(const RectF& rect, bool isFirst)
{
    BaseTextSelectOverlay::OnHandleMoveDone(rect, isFirst);
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    if (textPattern->GetMagnifierController()) {
        textPattern->GetMagnifierController()->RemoveMagnifierFrameNode();
    }
    auto textSelector = textPattern->GetTextSelector();
    textPattern->UpdateSelectionSpanType(textSelector.GetTextStart(), textSelector.GetTextEnd());
    textPattern->CalculateHandleOffsetAndShowOverlay();
    auto overlayManager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(overlayManager);
    if (!textPattern->IsSelectedTypeChange()) {
        overlayManager->ShowOptionMenu();
    }
    textPattern->UpdateAIMenuOptions();
    overlayManager->MarkInfoChange((isFirst ? DIRTY_FIRST_HANDLE : DIRTY_SECOND_HANDLE) | DIRTY_SELECT_AREA |
                                   DIRTY_SELECT_TEXT | DIRTY_COPY_ALL_ITEM | DIRTY_AI_MENU_ITEM | DIRTY_ASK_CELIA);
    if (textPattern->CheckSelectedTypeChange()) {
        CloseOverlay(false, CloseReason::CLOSE_REASON_NORMAL);
        ProcessOverlay({ .animation = true });
    }
    overlayManager->SetHandleCircleIsShow(isFirst, true);
    if (textPattern->GetTextSelector().SelectNothing()) {
        TAG_LOGI(AceLogTag::ACE_TEXT, "Close the selectoverlay when nothing is selected.");
        CloseOverlay(false, CloseReason::CLOSE_REASON_NORMAL);
    }
    auto host = textPattern->GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

std::string TextSelectOverlay::GetSelectedText()
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, "");
    auto start = textPattern->GetTextSelector().GetTextStart();
    auto end = textPattern->GetTextSelector().GetTextEnd();
    return UtfUtils::Str16DebugToStr8(textPattern->GetSelectedText(start, end));
}

RectF TextSelectOverlay::GetSelectAreaFromRects(SelectRectsType pos)
{
    auto pattern = GetPattern<TextPattern>();
    RectF res;
    CHECK_NULL_RETURN(pattern, res);
    auto selectRects = pattern->GetTextBoxes();
    auto textPaintOffset = GetPaintOffsetWithoutTransform();
    if (selectRects.empty()) {
        res.SetOffset(res.GetOffset() + textPaintOffset);
        GetSelectAreaFromHandle(res);
        ApplySelectAreaWithKeyboard(res);
        return res;
    }
    if (pos == SelectRectsType::LEFT_TOP_POINT) {
        selectRects.erase(std::next(selectRects.begin()), selectRects.end());
        selectRects.front().SetSize({0, 0});
    } else if (pos == SelectRectsType::RIGHT_BOTTOM_POINT) {
        selectRects.erase(selectRects.begin(), std::prev(selectRects.end()));
        selectRects.front().SetRect({selectRects.front().Right(), selectRects.front().Bottom()}, {0, 0});
    }
    auto contentRect = pattern->GetTextContentRect();
    auto textRect = pattern->GetTextRect();
    auto textContentRect = pattern->GetTextContentRect(true);
    res = MergeSelectedBoxes(selectRects, contentRect, textRect, textPaintOffset);
    RectF visibleContentRect;
    if (GetRenderClipValue() || LessOrEqual(textContentRect.Height(), contentRect.Height()) ||
        !GetClipHandleViewPort(visibleContentRect)) {
        visibleContentRect = RectF(contentRect.GetOffset() + textPaintOffset, contentRect.GetSize());
        visibleContentRect = GetVisibleRect(pattern->GetHost(), visibleContentRect);
    }
    auto intersectRect = res.IntersectRectT(visibleContentRect);
    intersectRect.SetWidth(std::max(intersectRect.Width(), 0.0f));
    intersectRect.SetHeight(std::max(intersectRect.Height(), 0.0f));
    if (hasTransform_) {
        intersectRect.SetOffset(intersectRect.GetOffset() - textPaintOffset);
        GetGlobalRectWithTransform(intersectRect);
    }
    ApplySelectAreaWithKeyboard(intersectRect);
    return intersectRect;
}

void TextSelectOverlay::GetSelectAreaFromHandle(RectF& rect)
{
    auto firstHandle = GetFirstHandleInfo();
    if (firstHandle) {
        auto firstRect = firstHandle->paintRect;
        if (hasTransform_) {
            firstRect.SetOffset(firstRect.GetOffset() - GetPaintOffsetWithoutTransform());
            GetGlobalRectWithTransform(firstRect);
        }
        rect = firstRect;
        return;
    }
    auto secondHandle = GetSecondHandleInfo();
    if (secondHandle) {
        auto secondRect = secondHandle->paintRect;
        if (hasTransform_) {
            secondRect.SetOffset(secondRect.GetOffset() - GetPaintOffsetWithoutTransform());
            GetGlobalRectWithTransform(secondRect);
        }
        rect = secondRect;
    }
}

void TextSelectOverlay::OnUpdateMenuInfo(SelectMenuInfo& menuInfo, SelectOverlayDirtyFlag dirtyFlag)
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    menuInfo.showCopyAll = !textPattern->IsSelectAll();
    menuInfo.showCopy = !textPattern->GetTextSelector().SelectNothing();
    menuInfo.showTranslate = menuInfo.showCopy && textPattern->IsShowTranslate() && IsNeedMenuTranslate();
    menuInfo.showSearch = menuInfo.showCopy && textPattern->IsShowSearch() && IsNeedMenuSearch();
    menuInfo.showShare = menuInfo.showCopy && IsSupportMenuShare() && IsNeedMenuShare();
    if (textPattern->IsShowAIMenuOption()) {
        // do not support two selected ai entity, hence it's enough to pick first item to determine type
        auto firstSpanItem = textPattern->GetAIItemOption().begin()->second;
        menuInfo.aiMenuOptionType = firstSpanItem.type;
    } else {
        menuInfo.aiMenuOptionType = TextDataDetectType::INVALID;
    }
    menuInfo.isAskCeliaEnabled = textPattern->IsAskCeliaEnabled();
    menuInfo.menuIsShow = IsShowMenu();
    menuInfo.showCut = false;
    menuInfo.showPaste = false;
    menuInfo.hasOnPrepareMenuCallback = onPrepareMenuCallback_ ? true : false;
}

void TextSelectOverlay::OnUpdateSelectOverlayInfo(SelectOverlayInfo& overlayInfo, int32_t requestCode)
{
    overlayInfo.clipHandleDrawRect = IsClipHandleWithViewPort();
    BaseTextSelectOverlay::OnUpdateSelectOverlayInfo(overlayInfo, requestCode);
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    textPattern->CopySelectionMenuParams(overlayInfo);
    auto layoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    overlayInfo.handlerColor = layoutProperty->GetCursorColor();
    OnUpdateOnCreateMenuCallback(overlayInfo);
    auto scrollableParent = FindScrollableParent();
    if (scrollableParent) {
        auto weakParent = WeakClaim(AceType::RawPtr(scrollableParent));
        overlayInfo.onHandlePanMove = [weak = WeakClaim(this), weakParent](const GestureEvent& event, bool isFirst) {
            auto overlay = weak.Upgrade();
            CHECK_NULL_VOID(overlay);
            overlay->TriggerScrollableParentToScroll(weakParent.Upgrade(), event.GetGlobalLocation(), false);
        };
        overlayInfo.onHandlePanEnd = [weak = WeakClaim(this), weakParent](const GestureEvent& event, bool isFirst) {
            auto overlay = weak.Upgrade();
            CHECK_NULL_VOID(overlay);
            overlay->TriggerScrollableParentToScroll(weakParent.Upgrade(), event.GetGlobalLocation(), true);
        };
        overlayInfo.getDeltaHandleOffset = [weak = WeakClaim(this)]() {
            auto overlay = weak.Upgrade();
            CHECK_NULL_RETURN(overlay, OffsetF());
            auto hostPaintOffset = overlay->GetHotPaintOffset();
            auto deltaOffset = overlay->hostPaintOffset_ - hostPaintOffset;
            overlay->hostPaintOffset_ = hostPaintOffset;
            return deltaOffset;
        };
    }
    overlayInfo.menuCallback.showMenuOnMoveDone = [weak = WeakClaim(this)]() {
        auto overlay = weak.Upgrade();
        CHECK_NULL_RETURN(overlay, true);
        auto textPattern = overlay->GetPattern<TextPattern>();
        CHECK_NULL_RETURN(textPattern, true);
        return !textPattern->IsSelectedTypeChange();
    };
}

void TextSelectOverlay::OnMenuItemAction(OptionMenuActionId id, OptionMenuType type)
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    switch (id) {
        case OptionMenuActionId::COPY:
            textPattern->HandleOnCopy();
            break;
        case OptionMenuActionId::SELECT_ALL:
            textPattern->HandleOnSelectAll();
            break;
        case OptionMenuActionId::TRANSLATE:
            HandleOnTranslate();
            break;
        case OptionMenuActionId::SEARCH:
            HandleOnSearch();
            break;
        case OptionMenuActionId::SHARE:
            HandleOnShare();
            break;
        case OptionMenuActionId::ASK_CELIA:
            textPattern->HandleOnAskCelia();
            break;
        default:
            TAG_LOGI(AceLogTag::ACE_TEXT, "Unsupported menu option id %{public}d", id);
            break;
    }
}

void TextSelectOverlay::OnMenuItemAction(OptionMenuActionId id, OptionMenuType type, const std::string& labelInfo)
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    if (labelInfo == "") {
        OnMenuItemAction(id, type);
        return;
    }
    switch (id) {
        case OptionMenuActionId::AI_MENU_OPTION:
            textPattern->HandleAIMenuOption(labelInfo);
            break;
        default:
            TAG_LOGI(AceLogTag::ACE_TEXT, "Unsupported menu option id %{public}d", id);
            break;
    }
}

void TextSelectOverlay::IsAIMenuOptionChanged(SelectMenuInfo& menuInfo)
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);

    auto oldIsShowAIMenuOption = textPattern->IsShowAIMenuOption();
    auto oldIsShowAskCelia = textPattern->IsAskCeliaEnabled();
    textPattern->UpdateAIMenuOptions();
    menuInfo.isShowAIMenuOptionChanged =
        oldIsShowAIMenuOption != textPattern->IsShowAIMenuOption() ||
        oldIsShowAskCelia != textPattern->IsAskCeliaEnabled();

    if (textPattern->IsShowAIMenuOption()) {
        // do not support two selected ai entity, hence it's enough to pick first item to determine type
        auto firstSpanItem = textPattern->GetAIItemOption().begin()->second; // null check
        menuInfo.aiMenuOptionType = firstSpanItem.type;
    } else {
        menuInfo.aiMenuOptionType = TextDataDetectType::INVALID;
    }
    menuInfo.isAskCeliaEnabled = textPattern->IsAskCeliaEnabled();
}

void TextSelectOverlay::OnCloseOverlay(OptionMenuType menuType, CloseReason reason, RefPtr<OverlayInfo> info)
{
    auto isDragging = GetIsHandleDragging();
    if (isDragging) {
        TriggerScrollableParentToScroll(FindScrollableParent(), Offset(), true);
    }
    BaseTextSelectOverlay::OnCloseOverlay(menuType, reason, info);
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    if (reason == CloseReason::CLOSE_REASON_HOLD_BY_OTHER || reason == CloseReason::CLOSE_REASON_TOOL_BAR ||
        reason == CloseReason::CLOSE_REASON_BACK_PRESSED) {
        textPattern->ResetSelection();
    }
    if (textPattern->GetMagnifierController()) {
        textPattern->GetMagnifierController()->RemoveMagnifierFrameNode();
    }
}

void TextSelectOverlay::OnHandleGlobalTouchEvent(SourceType sourceType, TouchType touchType, bool touchInside)
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    if (IsMouseClickDown(sourceType, touchType) && !touchInside) {
        textPattern->ResetSelection();
    }
    BaseTextSelectOverlay::OnHandleGlobalTouchEvent(sourceType, touchType);
}

void TextSelectOverlay::OnAncestorNodeChanged(FrameNodeChangeInfoFlag flag)
{
    auto isDragging = GetIsHandleDragging();
    if (IsAncestorNodeGeometryChange(flag)) {
        auto textPattern = GetPattern<TextPattern>();
        CHECK_NULL_VOID(textPattern);
        textPattern->UpdateParentGlobalOffset();
        textPattern->CalculateHandleOffsetAndShowOverlay();
        UpdateViewPort();
        if (isDragging && isDraggingFirstHandle_) {
            UpdateSecondHandleOffset();
            return;
        }
        if (isDragging && !isDraggingFirstHandle_) {
            UpdateFirstHandleOffset();
            return;
        }
        UpdateAllHandlesOffset();
    }
    if (!isDragging) {
        BaseTextSelectOverlay::OnAncestorNodeChanged(flag);
    }
}

void TextSelectOverlay::OnHandleLevelModeChanged(HandleLevelMode mode)
{
    if (handleLevelMode_ != mode && mode == HandleLevelMode::OVERLAY) {
        auto textPattern = GetPattern<TextPattern>();
        CHECK_NULL_VOID(textPattern);
        textPattern->UpdateParentGlobalOffset();
        textPattern->CalculateHandleOffsetAndShowOverlay();
        UpdateAllHandlesOffset();
    }
    if (mode == HandleLevelMode::OVERLAY) {
        BaseTextSelectOverlay::OnHandleLevelModeChanged(mode);
    } else {
        BaseTextSelectOverlay::SetHandleLevelMode(mode);
        BaseTextSelectOverlay::UpdateViewPort();
    }
}

void TextSelectOverlay::OnHandleMoveStart(const GestureEvent& event, bool isFirst)
{
    BaseTextSelectOverlay::OnHandleMoveStart(event, isFirst);
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    textPattern->ChangeHandleHeight(event, isFirst, IsOverlayMode());
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    manager->MarkInfoChange(isFirst ? DIRTY_FIRST_HANDLE : DIRTY_SECOND_HANDLE);
    manager->SetHandleCircleIsShow(isFirst, false);
    isDraggingFirstHandle_ = isFirst;
    hostPaintOffset_ = GetHotPaintOffset();
    textPattern->SetupMagnifier();
}

void TextSelectOverlay::OnOverlayClick(const GestureEvent& event, bool isFirst)
{
    if (!IsSingleHandle()) {
        ToggleMenu();
    }
}

void TextSelectOverlay::UpdateClipHandleViewPort(RectF& rect)
{
    auto host = GetOwner();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (GetRenderClipValue()) {
        return;
    }
    auto clipNode = host->GetAncestorNodeOfFrame(true);
    RefPtr<FrameNode> prevNode;
    while (clipNode) {
        renderContext = clipNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        if (renderContext->GetClipEdge().value_or(false)) {
            break;
        }
        prevNode = clipNode;
        clipNode = clipNode->GetAncestorNodeOfFrame(true);
    }
    if (clipNode) {
        RectF visibleRect;
        RectF frameRect;
        clipNode->GetVisibleRect(visibleRect, frameRect);
        if (GreatNotEqual(rect.Top(), visibleRect.Bottom()) || GreatNotEqual(rect.Left(), visibleRect.Right())) {
            return;
        }
        rect.SetHeight(visibleRect.Bottom() - rect.Top());
        rect.SetWidth(visibleRect.Right() - rect.Left());
        return;
    }
    // root node.
    if (prevNode) {
        auto geoNode = prevNode->GetGeometryNode();
        CHECK_NULL_VOID(geoNode);
        RectF visibleRect = geoNode->GetFrameRect();
        if (GreatNotEqual(rect.Top(), visibleRect.Height()) || GreatNotEqual(rect.Left(), visibleRect.Width())) {
            return;
        }
        rect.SetHeight(visibleRect.Height() - rect.Top());
        rect.SetWidth(visibleRect.Width() - rect.Left());
    }
}

void TextSelectOverlay::TriggerScrollableParentToScroll(
    const RefPtr<ScrollablePattern> scrollablePattern, const Offset& globalOffset, bool isStopAutoScroll)
{
    CHECK_NULL_VOID(scrollablePattern);
    auto scrollAxis = scrollablePattern->GetAxis();
    if (!scrollablePattern->IsScrollable() || (scrollAxis != Axis::VERTICAL && scrollAxis != Axis::HORIZONTAL)) {
        return;
    }
    auto scrollableHost = scrollablePattern->GetHost();
    CHECK_NULL_VOID(scrollableHost);
    auto scrollableFrameRect = scrollableHost->GetPaintRectWithTransform();
    auto host = GetOwner();
    CHECK_NULL_VOID(host);
    auto hostRect = host->GetPaintRectWithTransform();
    auto hostSize = hostRect.Height();
    auto scrollableParentSize = scrollableFrameRect.Height();
    if (scrollAxis == Axis::HORIZONTAL) {
        hostSize = hostRect.Width();
        scrollableParentSize = scrollableFrameRect.Width();
    }
    if (LessOrEqual(hostSize, scrollableParentSize)) {
        return;
    }
    RefPtr<NotifyDragEvent> notifyDragEvent = AceType::MakeRefPtr<NotifyDragEvent>();
    notifyDragEvent->SetX(globalOffset.GetX());
    notifyDragEvent->SetY(globalOffset.GetY());
    scrollablePattern->HandleOnDragStatusCallback(
        isStopAutoScroll ? DragEventType::DROP : DragEventType::MOVE, notifyDragEvent);
}

const RefPtr<ScrollablePattern> TextSelectOverlay::FindScrollableParent()
{
    auto host = GetOwner();
    CHECK_NULL_RETURN(host, nullptr);
    auto parent = host->GetAncestorNodeOfFrame(true);
    while (parent) {
        auto scrollablePattern = parent->GetPattern<ScrollablePattern>();
        if (scrollablePattern && scrollablePattern->IsScrollable()) {
            return scrollablePattern;
        }
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return nullptr;
}

OffsetF TextSelectOverlay::GetHotPaintOffset()
{
    auto host = GetOwner();
    CHECK_NULL_RETURN(host, hostPaintOffset_);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, hostPaintOffset_);
    return renderContext->GetPaintRectWithTransform().GetOffset();
}

std::optional<Color> TextSelectOverlay::GetHandleColor()
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, std::nullopt);
    auto layoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, std::nullopt);
    return layoutProperty->GetCursorColor();
}

bool TextSelectOverlay::AllowTranslate()
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, false);
    return !textPattern->GetTextSelector().SelectNothing();
}

bool TextSelectOverlay::AllowSearch()
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, false);
    return !textPattern->GetTextSelector().SelectNothing();
}

bool TextSelectOverlay::AllowShare()
{
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, false);
    return !textPattern->GetTextSelector().SelectNothing();
}

bool TextSelectOverlay::GetRenderClipValue() const
{
    auto defaultClipValue = Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE);
    auto pattern = GetPattern<Pattern>();
    CHECK_NULL_RETURN(pattern, defaultClipValue);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, defaultClipValue);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, defaultClipValue);
    return renderContext->GetClipEdge().value_or(defaultClipValue);
}

std::optional<SelectOverlayInfo> TextSelectOverlay::GetSelectOverlayInfo()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_RETURN(manager, std::optional<SelectOverlayInfo>());
    return manager->GetSelectOverlayInfo();
}

bool TextSelectOverlay::ChangeSecondHandleHeight(const GestureEvent& event, bool isOverlayMode)
{
    if (isOverlayMode || CheckSwitchToMode(HandleLevelMode::OVERLAY)) {
        return false;
    }
    auto secondHandleInfo = GetSecondHandleInfo();
    CHECK_NULL_RETURN(secondHandleInfo, false);
    auto handleRect = secondHandleInfo->localPaintRect;
    auto height = handleRect.Height();
    auto textPattern = GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, false);
    textPattern->CalculateDefaultHandleHeight(height);
    auto touchOffset = event.GetLocalLocation();
    bool isTouchHandleCircle = GreatNotEqual(touchOffset.GetY(), handleRect.Bottom());
    auto handleOffsetY =
        isTouchHandleCircle ? handleRect.Bottom() - height : static_cast<float>(touchOffset.GetY()) - height / 2.0f;
    auto secondHandle = textPattern->GetTextSelector().secondHandle;
    secondHandle.SetTop(handleOffsetY + handleGlobalOffset_.GetY());
    secondHandle.SetHeight(height);
    textPattern->UpdateTextSelectorSecondHandle(secondHandle);
    return true;
}

void TextSelectOverlay::GetVisibleDragViewHandles(RectF& first, RectF& second)
{
    auto selectOverlayInfo = GetSelectOverlayInfos();
    CHECK_NULL_VOID(selectOverlayInfo);
    RectF firstHandle;
    RectF secondHandle;
    if (!GetDragViewHandleRects(firstHandle, secondHandle)) {
        return;
    }
    if (selectOverlayInfo->firstHandle.isShow) {
        first = firstHandle;
    }
    if (selectOverlayInfo->secondHandle.isShow) {
        second = secondHandle;
    }
}
} // namespace OHOS::Ace::NG
