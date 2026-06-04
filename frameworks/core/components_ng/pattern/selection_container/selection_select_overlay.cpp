/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/selection_container/selection_select_overlay.h"

#include "base/log/log_wrapper.h"
#include "base/utils/string_utils.h"
#include "base/utils/utf_helper.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/common/clipboard/clipboard_proxy.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/select_content_overlay/select_content_overlay_manager.h"
#include "core/components_ng/pattern/selection_container/selection_container_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float BOX_EPSILON = 0.5f;

OffsetF GetHandleAnchorPoint(const RectF& rect)
{
    auto point = rect.GetOffset();
    point.SetY(point.GetY() + rect.Height() / 2.0f);
    return point;
}

CopyOptions MergeCopyOption(CopyOptions current, CopyOptions next)
{
    return static_cast<int32_t>(current) <= static_cast<int32_t>(next) ? current : next;
}
std::optional<RectF> GetVisualStartHandleRect(const RefPtr<SelectionContainerChild>& child)
{
    auto indexes = child->GetSelectionIndexes();
    return indexes.startIndex > indexes.endIndex
        ? child->GetSecondHandleRect() : child->GetFirstHandleRect();
}

std::optional<RectF> GetVisualEndHandleRect(const RefPtr<SelectionContainerChild>& child)
{
    auto indexes = child->GetSelectionIndexes();
    return indexes.startIndex > indexes.endIndex
        ? child->GetFirstHandleRect() : child->GetSecondHandleRect();
}

int32_t GetVisualStartHandleIndex(const RefPtr<SelectionContainerChild>& child)
{
    auto indexes = child->GetSelectionIndexes();
    return std::min(indexes.startIndex, indexes.endIndex);
}

int32_t GetVisualEndHandleIndex(const RefPtr<SelectionContainerChild>& child)
{
    auto indexes = child->GetSelectionIndexes();
    return std::max(indexes.startIndex, indexes.endIndex);
}
} // namespace

bool SelectionSelectOverlay::CheckHandleVisible(const RectF& paintRect)
{
    return !paintRect.IsEmpty();
}

void SelectionSelectOverlay::CalcHandleLevelMode(const RectF&, const RectF&)
{
    SetHandleLevelMode(HandleLevelMode::OVERLAY);
}

RefPtr<FrameNode> SelectionSelectOverlay::GetOwner()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetHost();
}

bool SelectionSelectOverlay::CheckTouchInHostNode(const PointF& touchPoint)
{
    if (!BaseTextSelectOverlay::CheckTouchInHostNode(touchPoint)) {
        return false;
    }
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto containerNode = pattern->GetHost();
    CHECK_NULL_RETURN(containerNode, false);
    for (const auto& weakChild : pattern->GetChildList()) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        auto childNode = child->GetHostNode();
        CHECK_NULL_CONTINUE(childNode);
        auto geo = childNode->GetGeometryNode();
        CHECK_NULL_CONTINUE(geo);
        auto childOrigin = childNode->ConvertPoint(OffsetF(0.0f, 0.0f), containerNode);
        auto childRect = RectF(childOrigin, geo->GetFrameSize());
        if (childRect.IsInRegion(touchPoint)) {
            return true;
        }
    }
    return false;
}

void SelectionSelectOverlay::OnHandleGlobalTouchEvent(
    SourceType sourceType, TouchType touchType, bool touchInside)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    if (IsMouseClickDown(sourceType, touchType) && !touchInside) {
        pattern->ResetAllSelection();
    }
    BaseTextSelectOverlay::OnHandleGlobalTouchEvent(sourceType, touchType);
    if (IsTouchUp(sourceType, touchType) &&
        GetClearPolicy() == TextSelectionClearPolicy::CLEAR_SELECTED_TEXT_ON_EXTERNAL_TOUCH) {
        pattern->ResetAllSelection();
        CloseOverlay(false, CloseReason::CLOSE_REASON_CLICK_OUTSIDE);
    }
}

bool SelectionSelectOverlay::PreProcessOverlay(const OverlayRequest& request)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    SetUsingMouse(pattern->IsUsingMouse());
    SetEnableHandleLevel(true);
    SetEnableSubWindowMenu(true);
    SetMenuTranslateIsSupport(IsShowTranslate());
    SetIsSupportMenuSearch(IsShowSearch());
    CheckEnableContainerModal();
    return true;
}

std::optional<SelectHandleInfo> SelectionSelectOverlay::GetFirstHandleInfo()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto startChild = pattern->GetSelectionStartChild();
    CHECK_NULL_RETURN(startChild, std::nullopt);
    auto handleRect = GetVisualStartHandleRect(startChild);
    CHECK_NULL_RETURN(handleRect.has_value(), std::nullopt);

    SelectHandleInfo handleInfo;
    handleInfo.paintRect = handleRect.value();
    handleInfo.isShow = CheckAndAdjustHandle(handleInfo.paintRect);
    auto localPaintRect = handleRect.value();
    localPaintRect.SetOffset(localPaintRect.GetOffset() - GetPaintOffsetWithoutTransform());
    handleInfo.localPaintRect = localPaintRect;
    SetTransformPaintInfo(handleInfo, localPaintRect);
    handleInfo.forceDraw = !CheckSwitchToMode(HandleLevelMode::OVERLAY);
    return handleInfo;
}

void SelectionSelectOverlay::OnHandleLevelModeChanged(HandleLevelMode mode)
{
    if (handleLevelMode_ != mode && mode == HandleLevelMode::OVERLAY) {
        auto pattern = pattern_.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto startChild = pattern->GetSelectionStartChild();
        auto endChild = pattern->GetSelectionEndChild();
        if (startChild) {
            startChild->UpdateSelectionHandleInfo();
        }
        if (endChild) {
            endChild->UpdateSelectionHandleInfo();
        }
        UpdateAllHandlesOffset();
    }
    if (mode == HandleLevelMode::OVERLAY) {
        BaseTextSelectOverlay::OnHandleLevelModeChanged(mode);
    } else {
        BaseTextSelectOverlay::SetHandleLevelMode(mode);
        BaseTextSelectOverlay::UpdateViewPort();
    }
}

void SelectionSelectOverlay::UpdateTransformFlag()
{
    hasTransform_ = CheckHasTransformAttr();
}

bool SelectionSelectOverlay::IsClipHandleWithViewPort()
{
    return !HasRenderTransform();
}

bool SelectionSelectOverlay::CheckAndAdjustHandle(RectF& paintRect)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    if (!GetRenderClipValue()) {
        if (handleLevelMode_ == HandleLevelMode::EMBED) {
            return true;
        }
        auto geoNode = host->GetGeometryNode();
        CHECK_NULL_RETURN(geoNode, false);
        auto frameRect = geoNode->GetFrameRect();
        RectF containerLocalRect(0.0f, 0.0f, frameRect.Width(), frameRect.Height());
        auto localPaintRect = paintRect;
        localPaintRect.SetOffset(localPaintRect.GetOffset() - GetPaintOffsetWithoutTransform());
        localPaintRect.SetOffset(
            OffsetF(localPaintRect.GetX() + localPaintRect.Width() / 2.0f, localPaintRect.GetY()));
        auto visibleContentRect = containerLocalRect.CombineRectT(localPaintRect);
        visibleContentRect.SetOffset(visibleContentRect.GetOffset() + pattern->GetContainerPaintOffsetWithTransform());
        visibleContentRect = GetVisibleRect(host, visibleContentRect);
        return CheckAndAdjustHandleWithContent(visibleContentRect, paintRect);
    }
    auto geoNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geoNode, false);
    auto frameRect = geoNode->GetFrameRect();
    RectF visibleContentRect(pattern->GetContainerPaintOffsetWithTransform(), frameRect.GetSize());
    if (handleLevelMode_ == HandleLevelMode::OVERLAY) {
        visibleContentRect = GetVisibleRect(host, visibleContentRect);
    }
    return CheckAndAdjustHandleWithContent(visibleContentRect, paintRect);
}

bool SelectionSelectOverlay::GetRenderClipValue() const
{
    auto defaultClipValue = false;
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, defaultClipValue);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, defaultClipValue);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, defaultClipValue);
    return renderContext->GetClipEdge().value_or(defaultClipValue);
}

bool SelectionSelectOverlay::CheckAndAdjustHandleWithContent(
    const RectF& visibleContentRect, RectF& paintRect)
{
    if (visibleContentRect.IsEmpty()) {
        return false;
    }
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

std::optional<SelectHandleInfo> SelectionSelectOverlay::GetSecondHandleInfo()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto endChild = pattern->GetSelectionEndChild();
    CHECK_NULL_RETURN(endChild, std::nullopt);
    auto handleRect = GetVisualEndHandleRect(endChild);
    CHECK_NULL_RETURN(handleRect.has_value(), std::nullopt);

    SelectHandleInfo handleInfo;
    handleInfo.paintRect = handleRect.value();
    handleInfo.isShow = CheckAndAdjustHandle(handleInfo.paintRect);
    auto localPaintRect = handleRect.value();
    localPaintRect.SetOffset(localPaintRect.GetOffset() - GetPaintOffsetWithoutTransform());
    handleInfo.localPaintRect = localPaintRect;
    SetTransformPaintInfo(handleInfo, localPaintRect);
    handleInfo.forceDraw = !CheckSwitchToMode(HandleLevelMode::OVERLAY);
    return handleInfo;
}

RectF SelectionSelectOverlay::GetSelectAreaFromRects(SelectRectsType pos)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});

    RectF selectArea;
    bool hasArea = false;
    bool hasClippedOut = false;
    for (const auto& weakChild : pattern->GetChildList()) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        if (child->GetSelectionText().empty()) {
            continue;
        }
        SelectionAreaResultType resultType = SelectionAreaResultType::NONE;
        auto childArea = child->GetSelectionArea(pos, resultType);
        if (pos == SelectRectsType::LEFT_TOP_POINT) {
            selectArea = childArea;
            hasArea = true;
            break;
        }
        if (pos == SelectRectsType::RIGHT_BOTTOM_POINT) {
            selectArea = childArea;
            hasArea = true;
            continue;
        }
        if (resultType == SelectionAreaResultType::CLIPPED_OUT) {
            hasClippedOut = true;
            continue;
        }
        if (childArea.IsEmpty()) {
            continue;
        }
        selectArea = hasArea ? selectArea.CombineRectT(childArea) : childArea;
        hasArea = true;
    }
    if (hasClippedOut && !hasArea) {
        return {};
    }
    if (!hasArea) {
        return GetSelectAreaFromHandleFallback();
    }
    ApplySelectAreaWithKeyboard(selectArea);
    return selectArea;
}

void SelectionSelectOverlay::OnUpdateMenuInfo(SelectMenuInfo& menuInfo, SelectOverlayDirtyFlag dirtyFlag)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto hasSelectedText = HasValidSelectedText();
    menuInfo.showCopyAll = pattern->HasSelectableText() && !pattern->IsSelectAll();
    menuInfo.showCopy = hasSelectedText;
    menuInfo.showTranslate = hasSelectedText && IsShowTranslate() && IsNeedMenuTranslate();
    menuInfo.showSearch = hasSelectedText && IsShowSearch() && IsNeedMenuSearch();
    menuInfo.showShare = hasSelectedText && IsSupportMenuShare() && IsNeedMenuShare();
    menuInfo.aiMenuOptionType = TextDataDetectType::INVALID;
    menuInfo.isAskCeliaEnabled = hasSelectedText && IsAskCeliaSupported();
    menuInfo.isShowAskCeliaInRightClick = menuInfo.isAskCeliaEnabled;
    menuInfo.menuIsShow = IsShowMenu();
    menuInfo.showCut = false;
    menuInfo.showPaste = false;
    menuInfo.hasOnPrepareMenuCallback = onPrepareMenuCallback_ ? true : false;
}

void SelectionSelectOverlay::OnUpdateSelectOverlayInfo(SelectOverlayInfo& overlayInfo, int32_t requestCode)
{
    overlayInfo.clipHandleDrawRect = IsClipHandleWithViewPort();
    BaseTextSelectOverlay::OnUpdateSelectOverlayInfo(overlayInfo, requestCode);
    auto overlayPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(overlayPattern);
    overlayPattern->CopySelectionMenuParams(overlayInfo);
    auto handleColor = GetHandleColor();
    if (handleColor.has_value()) {
        overlayInfo.handlerColor = handleColor;
    }
    OnUpdateOnCreateMenuCallback(overlayInfo);
    overlayInfo.onHandlePanMove = [weak = WeakClaim(this)](const GestureEvent& event, bool isFirst) {
        auto overlay = weak.Upgrade();
        CHECK_NULL_VOID(overlay);
        auto pattern = (overlay->pattern_).Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->TriggerScrollableParentToScroll(
            OffsetF(event.GetGlobalLocation().GetX(), event.GetGlobalLocation().GetY()), false);
    };
    overlayInfo.onHandlePanEnd = [weak = WeakClaim(this)](const GestureEvent& event, bool isFirst) {
        auto overlay = weak.Upgrade();
        CHECK_NULL_VOID(overlay);
        auto pattern = (overlay->pattern_).Upgrade();
        CHECK_NULL_VOID(pattern && pattern->IsTriggerParentToScroll());
        pattern->TriggerScrollableParentToScroll(
            OffsetF(event.GetGlobalLocation().GetX(), event.GetGlobalLocation().GetY()), true);
    };
    overlayInfo.getDeltaHandleOffset = [weak = WeakClaim(this)]() {
        auto overlay = weak.Upgrade();
        CHECK_NULL_RETURN(overlay, OffsetF());
        auto hostPaintOffset = overlay->GetHotPaintOffset();
        auto pattern = (overlay->pattern_).Upgrade();
        if (!pattern || !pattern->IsTriggerParentToScroll()) {
            overlay->hostPaintOffset_ = hostPaintOffset;
            return OffsetF();
        }
        auto deltaOffset = overlay->hostPaintOffset_ - hostPaintOffset;
        overlay->hostPaintOffset_ = hostPaintOffset;
        return deltaOffset;
    };
    overlayInfo.menuCallback.showMenuOnMoveDone = [weak = WeakClaim(this)]() {
        auto overlay = weak.Upgrade();
        CHECK_NULL_RETURN(overlay, true);
        auto overlayPattern = (overlay->pattern_).Upgrade();
        CHECK_NULL_RETURN(overlayPattern, true);
        return !overlayPattern->IsSelectedTypeChange();
    };
}

void SelectionSelectOverlay::OnResetTextSelection()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->ResetAllSelection();
}

std::optional<Color> SelectionSelectOverlay::GetHandleColor()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, std::nullopt);
    auto layoutProperty = host->GetLayoutProperty<SelectionContainerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, std::nullopt);
    return layoutProperty->GetCaretColor();
}

void SelectionSelectOverlay::OnMenuItemAction(OptionMenuActionId id, OptionMenuType type)
{
    switch (id) {
        case OptionMenuActionId::COPY: {
            auto pat = pattern_.Upgrade();
            CHECK_NULL_VOID(pat);
            pat->HandleOnCopy();
            break;
        }
        case OptionMenuActionId::SELECT_ALL: {
            auto pat = pattern_.Upgrade();
            CHECK_NULL_VOID(pat);
            pat->HandleOnSelectAll();
            break;
        }
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
            HandleOnAskCelia();
            break;
        default:
            TAG_LOGI(AceLogTag::ACE_TEXT, "Unsupported menu option id %{public}d", id);
            break;
    }
}

void SelectionSelectOverlay::OnMenuItemAction(OptionMenuActionId id, OptionMenuType type, const std::string& labelInfo)
{
    OnMenuItemAction(id, type);
}

void SelectionSelectOverlay::OnAncestorNodeChanged(FrameNodeChangeInfoFlag flag)
{
    auto isDragging = GetIsHandleDragging();
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    if (IsAncestorNodeGeometryChange(flag)) {
        auto startChild = pattern->GetSelectionStartChild();
        auto endChild = pattern->GetSelectionEndChild();
        if (startChild) {
            startChild->UpdateSelectionHandleInfo();
        }
        if (endChild) {
            endChild->UpdateSelectionHandleInfo();
        }
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
        FlushHandleNodeIfNeeded();
    }
    if (!isDragging) {
        BaseTextSelectOverlay::OnAncestorNodeChanged(flag);
    }
}

SelectionSelectOverlay::FlushHandleNodeGuard::FlushHandleNodeGuard(const RefPtr<SelectionSelectOverlay>& overlay)
    : overlay_(overlay)
{
    CHECK_NULL_VOID(overlay_);
    overlay_->isFlushingHandleNode_ = true;
}

SelectionSelectOverlay::FlushHandleNodeGuard::~FlushHandleNodeGuard()
{
    CHECK_NULL_VOID(overlay_);
    overlay_->isFlushingHandleNode_ = false;
}

void SelectionSelectOverlay::FlushHandleNodeIfNeeded()
{
    if (isFlushingHandleNode_) {
        return;
    }
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    auto handleNode = manager->GetHandleOverlayNode();
    CHECK_NULL_VOID(handleNode);
    auto pipeline = handleNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    FlushHandleNodeGuard flushGuard(Claim(this));
    pipeline->FlushUITaskWithSingleDirtyNode(handleNode);
    auto renderTask = handleNode->CreateRenderTask(true);
    if (renderTask) {
        (*renderTask)();
    }
}

void SelectionSelectOverlay::OnHandleMoveStart(const GestureEvent& event, bool isFirst)
{
    BaseTextSelectOverlay::OnHandleMoveStart(event, isFirst);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    auto overlayRoot = manager->GetSelectOverlayRoot();
    CHECK_NULL_VOID(overlayRoot);

    auto fixedChild = isFirst ? pattern->GetSelectionEndChild() : pattern->GetSelectionStartChild();
    CHECK_NULL_VOID(fixedChild);
    auto fixedHandle = isFirst ? GetVisualEndHandleRect(fixedChild) : GetVisualStartHandleRect(fixedChild);
    CHECK_NULL_VOID(fixedHandle);
    auto containerNode = pattern->GetHostNode();
    CHECK_NULL_VOID(containerNode);
    auto fixedPointInContainer = overlayRoot->ConvertPoint(GetHandleAnchorPoint(fixedHandle.value()), containerNode);
    auto fixedIndex = isFirst ? GetVisualEndHandleIndex(fixedChild) : GetVisualStartHandleIndex(fixedChild);
    auto fixedHandleIsTopOnStart = !isFirst;
    pattern->HandleSelectionStart(fixedPointInContainer, fixedChild, fixedIndex, fixedIndex, fixedHandleIsTopOnStart);
    pattern->UpdateMovingChildForHandle(isFirst);
    manager->MarkInfoChange(isFirst ? DIRTY_FIRST_HANDLE : DIRTY_SECOND_HANDLE);
    manager->SetHandleCircleIsShow(isFirst, false);
    hostPaintOffset_ = GetHotPaintOffset();
    isDraggingFirstHandle_ = isFirst;
}

void SelectionSelectOverlay::OnHandleMove(const RectF& rect, bool isFirst)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    auto overlayRoot = manager->GetSelectOverlayRoot();
    CHECK_NULL_VOID(overlayRoot);
    auto containerNode = pattern->GetHostNode();
    CHECK_NULL_VOID(containerNode);
    auto movingPointInContainer = overlayRoot->ConvertPoint(GetHandleAnchorPoint(rect), containerNode);
    pattern->HandleSelectionUpdate(movingPointInContainer);
    manager->MarkInfoChange(DIRTY_SELECT_TEXT);
}

void SelectionSelectOverlay::OnHandleMoveDone(const RectF& rect, bool isFirst)
{
    BaseTextSelectOverlay::OnHandleMoveDone(rect, isFirst);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    auto overlayRoot = manager->GetSelectOverlayRoot();
    CHECK_NULL_VOID(overlayRoot);
    auto containerNode = pattern->GetHostNode();
    CHECK_NULL_VOID(containerNode);
    auto movingPointInContainer = overlayRoot->ConvertPoint(GetHandleAnchorPoint(rect), containerNode);
    pattern->ProcessHandleMoveSelectionEnd(movingPointInContainer);
    if (!pattern->IsSelectedTypeChange()) {
        manager->ShowOptionMenu();
    }
    manager->MarkInfoChange(DIRTY_FIRST_HANDLE | DIRTY_SECOND_HANDLE | DIRTY_SELECT_AREA |
                            DIRTY_SELECT_TEXT | DIRTY_COPY_ALL_ITEM | DIRTY_ASK_CELIA);
    if (pattern->CheckSelectedTypeChange()) {
        CloseOverlay(false, CloseReason::CLOSE_REASON_NORMAL);
        ProcessOverlay({ .animation = true });
    }
    manager->SetHandleCircleIsShow(isFirst, true);
    if (pattern->GetSelectionText().empty()) {
        CloseOverlay(false, CloseReason::CLOSE_REASON_NORMAL);
    }
    containerNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SelectionSelectOverlay::OnCloseOverlay(OptionMenuType menuType, CloseReason reason, RefPtr<OverlayInfo> info)
{
    auto isDragging = GetIsHandleDragging();
    if (isDragging) {
        auto pattern = pattern_.Upgrade();
        if (pattern) {
            pattern->TriggerScrollableParentToScroll(OffsetF(), true);
        }
    }
    BaseTextSelectOverlay::OnCloseOverlay(menuType, reason, info);
    if (reason == CloseReason::CLOSE_REASON_HOLD_BY_OTHER || reason == CloseReason::CLOSE_REASON_TOOL_BAR ||
        reason == CloseReason::CLOSE_REASON_BACK_PRESSED) {
        auto pattern = pattern_.Upgrade();
        if (pattern) {
            pattern->ResetAllSelection();
        }
    }
}

std::string SelectionSelectOverlay::GetSelectedText()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, "");
    return UtfUtils::Str16DebugToStr8(pattern->GetSelectionText());
}

bool SelectionSelectOverlay::AllowTranslate()
{
    return HasValidSelectedText();
}

bool SelectionSelectOverlay::AllowSearch()
{
    return HasValidSelectedText();
}

bool SelectionSelectOverlay::AllowShare()
{
    return HasValidSelectedText();
}

bool SelectionSelectOverlay::IsShowTranslate() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto textTheme = context->GetTheme<TextTheme>();
    CHECK_NULL_RETURN(textTheme, false);
    return textTheme->IsShowTranslate();
}

bool SelectionSelectOverlay::IsShowSearch() const
{
    auto container = Container::Current();
    if (container && container->IsSceneBoardWindow()) {
        return false;
    }
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto textTheme = context->GetTheme<TextTheme>();
    CHECK_NULL_RETURN(textTheme, false);
    return textTheme->IsShowSearch();
}

OffsetF SelectionSelectOverlay::GetHotPaintOffset()
{
    auto host = GetOwner();
    CHECK_NULL_RETURN(host, hostPaintOffset_);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, hostPaintOffset_);
    return renderContext->GetPaintRectWithTransform().GetOffset();
}

bool SelectionSelectOverlay::HasValidSelectedText() const
{
    return ResolveCopyOptionForSelectedText().has_value();
}

std::optional<CopyOptions> SelectionSelectOverlay::ResolveCopyOptionForSelectedText() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, std::nullopt);
    auto childList = pattern->GetChildList();
    std::optional<CopyOptions> selectedCopyOption;
    for (const auto& weakChild : childList) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        if (child->GetSelectionText().empty()) {
            continue;
        }
        auto childCopyOption = child->GetCopyOption();
        if (!child->CanSelect() || childCopyOption == CopyOptions::None) {
            // Defensive guard: selected text with CopyOptions::None means state is inconsistent; block copy.
            TAG_LOGW(AceLogTag::ACE_TEXT, "Selected child is not copyable, block container copy.");
            return std::nullopt;
        }
        selectedCopyOption = selectedCopyOption.has_value()
                                 ? MergeCopyOption(selectedCopyOption.value(), childCopyOption)
                                 : childCopyOption;
    }
    return selectedCopyOption;
}

void SelectionSelectOverlay::UpdateAISelectMenu()
{
    auto manager = GetManager<SelectContentOverlayManager>();
    CHECK_NULL_VOID(manager);
    if (!IsUsingMouse()) {
        manager->MarkInfoChange(DIRTY_ALL_MENU_ITEM | DIRTY_SELECT_AI_DETECT);
        manager->FocusFirstFocusableChildInMenu();
    }
}

RectF SelectionSelectOverlay::GetSelectAreaFromHandleFallback()
{
    RectF rect;
    auto firstHandle = GetFirstHandleInfo();
    if (firstHandle) {
        rect = firstHandle->paintRect;
        ApplySelectAreaWithKeyboard(rect);
        return rect;
    }
    auto secondHandle = GetSecondHandleInfo();
    if (secondHandle) {
        rect = secondHandle->paintRect;
    }
    ApplySelectAreaWithKeyboard(rect);
    return rect;
}

bool SelectionSelectOverlay::IsAskCeliaSupported() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    CHECK_NULL_RETURN(!pattern->GetSelectionText().empty(), false);
    for (const auto& weakChild : pattern->GetChildList()) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        if (child->IsAskCeliaSupported()) {
            return true;
        }
    }
    return false;
}

void SelectionSelectOverlay::HandleOnAskCelia()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    HideMenu(true);
    auto selectedContent = pattern->GetSelectionText();
    for (const auto& weakChild : pattern->GetChildList()) {
        auto child = weakChild.Upgrade();
        CHECK_NULL_CONTINUE(child);
        if (child->HandleOnAskCelia(selectedContent)) {
            return;
        }
    }
}

} // namespace OHOS::Ace::NG
