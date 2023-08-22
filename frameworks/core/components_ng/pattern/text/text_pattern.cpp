/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/text_pattern.h"

#include <stack>

#include "base/geometry/ng/rect_t.h"
#include "base/geometry/offset.h"
#include "base/log/dump_log.h"
#include "base/utils/utils.h"
#include "base/window/drag_window.h"
#include "core/common/font_manager.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/gestures/gesture_info.h"

#ifdef ENABLE_DRAG_FRAMEWORK
#include "core/common/ace_engine_ext.h"
#include "core/common/udmf/udmf_client.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t API_PROTEXTION_GREATER_NINE = 9;
// uncertainty range when comparing selectedTextBox to contentRect
constexpr float BOX_EPSILON = 0.5f;
}; // namespace

void TextPattern::OnAttachToFrameNode()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID_NOLOG(pipeline);
    auto host = GetHost();
    CHECK_NULL_VOID_NOLOG(host);
    if (pipeline->GetMinPlatformVersion() > API_PROTEXTION_GREATER_NINE) {
        host->GetRenderContext()->UpdateClipEdge(true);
    }
    InitSurfaceChangedCallback();
    auto theme = pipeline->GetTheme<TextTheme>();
    CHECK_NULL_VOID_NOLOG(theme);
    host->SetDraggable(theme->GetDraggable());
    auto textLayoutProperty = GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateTextAlign(TextAlign::START);
    textLayoutProperty->UpdateAlignment(Alignment::CENTER_LEFT);
}

void TextPattern::OnDetachFromFrameNode(FrameNode* node)
{
    CloseSelectOverlay();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (HasSurfaceChangedCallback()) {
        LOGD("Unregister surface change callback with id %{public}d", surfaceChangedCallbackId_.value_or(-1));
        pipeline->UnregisterSurfaceChangedCallback(surfaceChangedCallbackId_.value_or(-1));
    }
    auto frameNode = WeakClaim(node);
    pipeline->RemoveFontNodeNG(frameNode);
    auto fontManager = pipeline->GetFontManager();
    if (fontManager) {
        fontManager->UnRegisterCallbackNG(frameNode);
        fontManager->RemoveVariationNodeNG(frameNode);
    }
}

void TextPattern::CloseSelectOverlay()
{
    CloseSelectOverlay(false);
}

void TextPattern::CloseSelectOverlay(bool animation)
{
    if (selectOverlayProxy_ && !selectOverlayProxy_->IsClosed()) {
        selectOverlayProxy_->Close(animation);
    }
}

void TextPattern::ResetSelection()
{
    showSelectOverlay_ = false;
    if (textSelector_.IsValid()) {
        textSelector_.Update(-1, -1);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

int32_t TextPattern::GetGraphemeClusterLength(int32_t extend) const
{
    auto text = textForDisplay_;
    char16_t aroundChar = 0;

    if (static_cast<size_t>(extend) < (text.length())) {
        aroundChar = text[std::min(static_cast<int32_t>(text.length() - 1), extend)];
    }
    return StringUtils::NotInUtf16Bmp(aroundChar) ? 2 : 1;
}

void TextPattern::InitSelection(const Offset& pos)
{
    CHECK_NULL_VOID(paragraph_);
    int32_t extend = paragraph_->GetHandlePositionForClick(pos);
#ifndef USE_GRAPHIC_TEXT_GINE
    int32_t start = 0;
    int32_t end = 0;
    if (!paragraph_->GetWordBoundary(extend, start, end)) {
        start = extend;
        end = std::min(
            static_cast<int32_t>(GetWideText().length()) + imageCount_, extend + GetGraphemeClusterLength(extend));
    }
    textSelector_.Update(start, end);
#else
    int32_t extendEnd =
        std::min(static_cast<int32_t>(GetWideText().length()) + imageCount_, extend + GetGraphemeClusterLength(extend));
    textSelector_.Update(extend, extendEnd);
#endif
}

OffsetF TextPattern::CalcCursorOffsetByPosition(int32_t position, float& selectLineHeight)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, OffsetF(0.0f, 0.0f));
    auto rect = host->GetGeometryNode()->GetFrameRect();
    CHECK_NULL_RETURN(paragraph_, OffsetF(0.0f, 0.0f));
    CaretMetrics metrics;
    auto computeSuccess = paragraph_->ComputeOffsetForCaretUpstream(position, metrics) ||
                          paragraph_->ComputeOffsetForCaretDownstream(position, metrics);
    if (!computeSuccess) {
        LOGW("Get caret offset failed, set it to text tail");
        return { rect.Width(), 0.0f };
    }
    selectLineHeight = metrics.height;
    return { static_cast<float>(metrics.offset.GetX()), static_cast<float>(metrics.offset.GetY()) };
}

void TextPattern::CalculateHandleOffsetAndShowOverlay(bool isUsingMouse)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    auto offset = host->GetPaintRectOffset() + contentRect_.GetOffset();
    auto textPaintOffset = offset - OffsetF(0.0, std::min(baselineOffset_, 0.0f));

    // calculate firstHandleOffset, secondHandleOffset and handlePaintSize
    float startSelectHeight = 0.0f;
    float endSelectHeight = 0.0f;
    auto startOffset = CalcCursorOffsetByPosition(textSelector_.baseOffset, startSelectHeight);
    auto endOffset = CalcCursorOffsetByPosition(textSelector_.destinationOffset, endSelectHeight);
    OffsetF firstHandleOffset = startOffset + textPaintOffset - rootOffset;
    OffsetF secondHandleOffset = endOffset + textPaintOffset - rootOffset;

    textSelector_.selectionBaseOffset = firstHandleOffset;
    textSelector_.selectionDestinationOffset = secondHandleOffset;

    RectF firstHandle;
    firstHandle.SetOffset(firstHandleOffset);
    firstHandle.SetSize({ SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), startSelectHeight });
    textSelector_.firstHandle = firstHandle;

    RectF secondHandle;
    secondHandle.SetOffset(secondHandleOffset);
    secondHandle.SetSize({ SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), endSelectHeight });
    secondHandle.SetHeight(endSelectHeight);
    textSelector_.secondHandle = secondHandle;
}

void TextPattern::HandleLongPress(GestureEvent& info)
{
    if (copyOption_ == CopyOptions::None || isMousePressed_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (IsDraggable(info.GetLocalLocation())) {
        // prevent long press event from being triggered when dragging
#ifdef ENABLE_DRAG_FRAMEWORK
        gestureHub->SetIsTextDraggable(true);
#endif
        return;
    }
#ifdef ENABLE_DRAG_FRAMEWORK
    gestureHub->SetIsTextDraggable(false);
#endif
    auto textPaintOffset = contentRect_.GetOffset() - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
    Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
        info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
    showSelectOverlay_ = true;
    InitSelection(textOffset);
    CalculateHandleOffsetAndShowOverlay();
    CloseSelectOverlay(true);
    ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle, true);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextPattern::OnHandleMove(const RectF& handleRect, bool isFirstHandle)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    auto offset = host->GetPaintRectOffset() + contentRect_.GetOffset() - rootOffset;
    auto textPaintOffset = offset - OffsetF(0.0, std::min(baselineOffset_, 0.0f));

    auto localOffsetX = handleRect.GetX();
    auto localOffsetY = handleRect.GetY();

    if (localOffsetX < offset.GetX()) {
        localOffsetX = offset.GetX();
    } else if (GreatOrEqual(localOffsetX, offset.GetX() + contentRect_.Width())) {
        localOffsetX = offset.GetX() + contentRect_.Width();
    }

    if (localOffsetY < offset.GetY()) {
        localOffsetY = offset.GetY();
    } else if (GreatNotEqual(localOffsetY, offset.GetY() + contentRect_.Height())) {
        localOffsetY = offset.GetY() + contentRect_.Height();
    }

    localOffsetX = localOffsetX - textPaintOffset.GetX();
    localOffsetY = localOffsetY - textPaintOffset.GetY();

    CHECK_NULL_VOID(paragraph_);
    // the handle position is calculated based on the middle of the handle height.
    if (isFirstHandle) {
        auto start =
            paragraph_->GetHandlePositionForClick(Offset(localOffsetX, localOffsetY + handleRect.Height() / 2));
        textSelector_.Update(start, textSelector_.destinationOffset);
    } else {
        auto end = paragraph_->GetHandlePositionForClick(Offset(localOffsetX, localOffsetY + handleRect.Height() / 2));
        textSelector_.Update(textSelector_.baseOffset, end);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    CHECK_NULL_VOID_NOLOG(selectOverlayProxy_);
    auto start = textSelector_.GetTextStart();
    auto end = textSelector_.GetTextEnd();
    selectOverlayProxy_->SetSelectInfo(GetSelectedText(start, end));
}

void TextPattern::OnHandleMoveDone(const RectF& handleRect, bool isFirstHandle)
{
    CalculateHandleOffsetAndShowOverlay();
    if (selectOverlayProxy_) {
        SelectHandleInfo handleInfo;
        if (isFirstHandle) {
            handleInfo.paintRect = textSelector_.firstHandle;
            selectOverlayProxy_->UpdateFirstSelectHandleInfo(handleInfo);
        } else {
            handleInfo.paintRect = textSelector_.secondHandle;
            selectOverlayProxy_->UpdateSecondSelectHandleInfo(handleInfo);
        }
        if (IsSelectAll() && selectMenuInfo_.showCopyAll == true) {
            selectMenuInfo_.showCopyAll = false;
            selectOverlayProxy_->UpdateSelectMenuInfo(selectMenuInfo_);
        } else if (!IsSelectAll() && selectMenuInfo_.showCopyAll == false) {
            selectMenuInfo_.showCopyAll = true;
            selectOverlayProxy_->UpdateSelectMenuInfo(selectMenuInfo_);
        }
        return;
    }
    ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle, true);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool TextPattern::IsSelectAll()
{
    return textSelector_.GetTextStart() == 0 &&
           textSelector_.GetTextEnd() == static_cast<int32_t>(GetWideText().length()) + imageCount_;
}
std::wstring TextPattern::GetWideText() const
{
    return StringUtils::ToWstring(textForDisplay_);
}

std::string TextPattern::GetSelectedText(int32_t start, int32_t end) const
{
    auto wideText = GetWideText();
    auto min = std::clamp(std::max(std::min(start, end), 0), 0, static_cast<int32_t>(wideText.length()));
    auto max = std::clamp(std::min(std::max(start, end), static_cast<int32_t>(wideText.length())), 0,
        static_cast<int32_t>(wideText.length()));
    return StringUtils::ToString(wideText.substr(min, max - min));
}

void TextPattern::HandleOnCopy()
{
    CHECK_NULL_VOID(clipboard_);
    if (textSelector_.IsValid() && textSelector_.GetTextStart() == textSelector_.GetTextEnd()) {
        textSelector_.Update(-1, -1);
        LOGW("Nothing to select");
        return;
    }
    auto value = GetSelectedText(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    if (value.empty()) {
        textSelector_.Update(-1, -1);
        LOGW("Copy value is empty");
        return;
    }
    if (copyOption_ != CopyOptions::None) {
        clipboard_->SetData(value, copyOption_);
    }
    ResetSelection();
}

void TextPattern::ShowSelectOverlay(const RectF& firstHandle, const RectF& secondHandle)
{
    ShowSelectOverlay(firstHandle, secondHandle, false);
}
void TextPattern::ShowSelectOverlay(const RectF& firstHandle, const RectF& secondHandle, bool animation)
{
    SelectOverlayInfo selectInfo;
    selectInfo.firstHandle.paintRect = firstHandle;
    selectInfo.secondHandle.paintRect = secondHandle;
    CheckHandles(selectInfo.secondHandle);
    selectInfo.onHandleMove = [weak = WeakClaim(this)](const RectF& handleRect, bool isFirst) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnHandleMove(handleRect, isFirst);
    };
    selectInfo.onHandleMoveDone = [weak = WeakClaim(this)](const RectF& handleRect, bool isFirst) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnHandleMoveDone(handleRect, isFirst);
    };
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuCallback.onCopy = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleOnCopy();
    };
    selectInfo.menuCallback.onSelectAll = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleOnSelectAll();
    };
    selectInfo.onClose = [weak = WeakClaim(this)](bool closedByGlobalEvent) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (closedByGlobalEvent) {
            pattern->ResetSelection();
        } else {
            pattern->showSelectOverlay_ = false;
        }
    };

    if (!menuOptionItems_.empty()) {
        selectInfo.menuOptionItems = GetMenuOptionItems();
    }
    selectMenuInfo_ = selectInfo.menuInfo;
    UpdateSelectOverlayOrCreate(selectInfo, animation);
}

void TextPattern::HandleOnSelectAll()
{
    auto textSize = GetWideText().length() + imageCount_;
    textSelector_.Update(0, textSize);
    CalculateHandleOffsetAndShowOverlay();
    CloseSelectOverlay(true);
    ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle, true);
    selectMenuInfo_.showCopyAll = false;
    selectOverlayProxy_->UpdateSelectMenuInfo(selectMenuInfo_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextPattern::CheckHandles(SelectHandleInfo& handleInfo)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->GetClipEdge().value_or(true) == false) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto offset = host->GetPaintRectOffset() + contentRect_.GetOffset();
    RectF contentGlobalRect(offset, contentRect_.GetSize());
    auto handleOffset = handleInfo.paintRect.GetOffset();
    if (!contentGlobalRect.IsInRegion(PointF(handleOffset.GetX(), handleOffset.GetY() + BOX_EPSILON))) {
        handleInfo.isShow = false;
    }
}

void TextPattern::InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID_NOLOG(!longPressEvent_);
    auto longPressCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleLongPress(info);
    };
    longPressEvent_ = MakeRefPtr<LongPressEvent>(std::move(longPressCallback));

    constexpr int32_t longPressDelay = 600;
    // Default time is 500, used by drag event. Drag event would trigger if text is selected, but we want
    // it to only trigger on the second long press, after selection. Therefore, long press delay of Selection needs to
    // be slightly longer to ensure that order.
    gestureHub->SetLongPressEvent(longPressEvent_, false, false, longPressDelay);

    auto onTextSelectorChange = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        frameNode->OnAccessibilityEvent(AccessibilityEventType::TEXT_SELECTION_UPDATE);
    };
    textSelector_.SetOnAccessibility(std::move(onTextSelectorChange));
}

void TextPattern::OnHandleTouchUp()
{
    CloseSelectOverlay();
    ResetSelection();
}

void TextPattern::HandleClickEvent(GestureEvent& info)
{
    if (textSelector_.IsValid()) {
        CloseSelectOverlay(true);
        ResetSelection();
    }

    RectF textContentRect = contentRect_;
    textContentRect.SetTop(contentRect_.GetY() - std::min(baselineOffset_, 0.0f));
    textContentRect.SetHeight(contentRect_.Height() - std::max(baselineOffset_, 0.0f));
    bool isClickOnSpan = false;
    if (textContentRect.IsInRegion(PointF(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY())) &&
        !spanItemChildren_.empty() && paragraph_) {
        Offset textOffset = { info.GetLocalLocation().GetX() - textContentRect.GetX(),
            info.GetLocalLocation().GetY() - textContentRect.GetY() };
        auto position = paragraph_->GetHandlePositionForClick(textOffset);
        for (const auto& item : spanItemChildren_) {
            if (item && position < item->position) {
                if (!item->onClick) {
                    break;
                }
                GestureEvent spanClickinfo = info;
                EventTarget target = info.GetTarget();
                target.area.SetWidth(Dimension(0.0f));
                target.area.SetHeight(Dimension(0.0f));
                spanClickinfo.SetTarget(target);
                item->onClick(spanClickinfo);
                isClickOnSpan = true;
                break;
            }
        }
    }
    if (onClick_ && !isClickOnSpan) {
        onClick_(info);
    }
}

void TextPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID_NOLOG(!clickEventInitialized_);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleClickEvent(info);
    };

    auto clickListener = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gestureHub->AddClickEvent(clickListener);
    clickEventInitialized_ = true;
}

void TextPattern::InitMouseEvent()
{
    CHECK_NULL_VOID_NOLOG(!mouseEventInitialized_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);

    auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleMouseEvent(info);
    };
    auto mouseEvent = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnMouseEvent(mouseEvent);
    mouseEventInitialized_ = true;
}

void TextPattern::HandleMouseEvent(const MouseInfo& info)
{
    if (copyOption_ == CopyOptions::None) {
        return;
    }
    if (info.GetButton() == MouseButton::RIGHT_BUTTON && info.GetAction() == MouseAction::PRESS) {
        auto textPaintOffset = contentRect_.GetOffset() - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
        Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
            info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
        InitSelection(textOffset);
        CalculateHandleOffsetAndShowOverlay(true);
        ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle, true);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        return;
    }
    if (info.GetButton() == MouseButton::LEFT_BUTTON) {
        if (info.GetAction() == MouseAction::PRESS) {
            isMousePressed_ = true;
            if (BetweenSelectedPosition(info.GetGlobalLocation())) {
                blockPress_ = true;
                return;
            }
            mouseStatus_ = MouseStatus::PRESSED;
            auto textPaintOffset = contentRect_.GetOffset() - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
            Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
                info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
            CHECK_NULL_VOID(paragraph_);
            auto start = paragraph_->GetHandlePositionForClick(textOffset);
            textSelector_.Update(start, start);
        }

        if (info.GetAction() == MouseAction::MOVE) {
            if (blockPress_) {
                return;
            }
            mouseStatus_ = MouseStatus::MOVE;
            auto textPaintOffset = contentRect_.GetOffset() - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
            Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
                info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
            CHECK_NULL_VOID(paragraph_);
            auto end = paragraph_->GetHandlePositionForClick(textOffset);
            textSelector_.Update(textSelector_.baseOffset, end);
        }

        if (info.GetAction() == MouseAction::RELEASE) {
            if (blockPress_) {
                blockPress_ = false;
            }
            mouseStatus_ = MouseStatus::RELEASED;
            auto textPaintOffset = contentRect_.GetOffset() - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
            Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
                info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
            CHECK_NULL_VOID(paragraph_);
            auto end = paragraph_->GetHandlePositionForClick(textOffset);
            textSelector_.Update(textSelector_.baseOffset, end);
            isMousePressed_ = false;
        }
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextPattern::InitTouchEvent()
{
    CHECK_NULL_VOID_NOLOG(!touchEventInitialized_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);

    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleTouchEvent(info);
    };
    auto touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gesture->AddTouchEvent(touchListener_);
    touchEventInitialized_ = true;
}

void TextPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    return;
}

void TextPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID_NOLOG(!panEventInitialized_);
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandlePanStart(info);
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandlePanUpdate(info);
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandlePanEnd(info);
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {};
    auto panEvent = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));

    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    gestureHub->AddPanEvent(panEvent, panDirection, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
    panEventInitialized_ = true;
}

void TextPattern::HandlePanStart(const GestureEvent& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto offset = info.GetLocalLocation();
    if (!IsDraggable(offset)) {
        return;
    }
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);

#if !defined(PREVIEW)
    if (!dragWindow_) {
        auto rect = pipelineContext->GetCurrentWindowRect();
        auto initTextPattern = AceType::Claim(this);

        // create textdrag window
        dragWindow_ = DragWindow::CreateTextDragWindow("APP_DRAG_WINDOW",
            static_cast<int32_t>(host->GetPaintRectOffset().GetX() + rect.Left()),
            static_cast<int32_t>(host->GetPaintRectOffset().GetY() + rect.Top()),
            static_cast<int32_t>(contentRect_.Width() + contentRect_.GetX()),
            contentRect_.Height() + contentRect_.GetY());
        if (dragWindow_) {
            dragWindow_->SetOffset(static_cast<int32_t>(host->GetPaintRectOffset().GetX() + rect.Left()),
                static_cast<int32_t>(host->GetPaintRectOffset().GetY() + rect.Top()));
            // draw select text on drag window
            dragWindow_->DrawTextNG(paragraph_, initTextPattern);
            // add select data to clipboard
            auto manager = pipelineContext->GetDragDropManager();
            CHECK_NULL_VOID(manager);
            dragDropProxy_ = manager->CreateTextDragDropProxy();
            CHECK_NULL_VOID(dragDropProxy_);
            dragDropProxy_->OnTextDragStart(GetSelectedText(textSelector_.GetTextStart(), textSelector_.GetTextEnd()));
        }
    }
#endif
}

bool TextPattern::IsDraggable(const Offset& offset)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto eventHub = host->GetEventHub<EventHub>();
    bool draggable = eventHub->HasOnDragStart();
    if (copyOption_ != CopyOptions::None && draggable &&
        GreatNotEqual(textSelector_.GetTextEnd(), textSelector_.GetTextStart())) {
        // Determine if the pan location is in the selected area
        std::vector<Rect> selectedRects;
        paragraph_->GetRectsForRange(textSelector_.GetTextStart(), textSelector_.GetTextEnd(), selectedRects);
        auto panOffset = OffsetF(offset.GetX(), offset.GetY()) - contentRect_.GetOffset() +
                         OffsetF(0.0, std::min(baselineOffset_, 0.0f));
        for (const auto& selectedRect : selectedRects) {
            if (selectedRect.IsInRegion(Point(panOffset.GetX(), panOffset.GetY()))) {
                return true;
            }
        }
    }
    return false;
}

void TextPattern::HandlePanUpdate(const GestureEvent& info)
{
    if (dragWindow_) {
        if (dragWindow_) {
            dragWindow_->TextDragWindowMove(info.GetOffsetX(), info.GetOffsetY());
        }
        return;
    }
}

void TextPattern::HandlePanEnd(const GestureEvent& info)
{
    if (dragWindow_) {
        dragWindow_->Destroy();
        dragWindow_ = nullptr;
        if (dragDropProxy_) {
            dragDropProxy_->OnDragEnd(info, true);
        }
        return;
    }
}

#ifdef ENABLE_DRAG_FRAMEWORK
DragDropInfo TextPattern::OnDragStart(const RefPtr<Ace::DragEvent>& event, const std::string& extraParams)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, {});
    CHECK_NULL_RETURN(dragNodeWk_.Upgrade(), {});

    DragDropInfo itemInfo;
    auto selectedStr = GetSelectedText(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    itemInfo.extraInfo = selectedStr;
    RefPtr<UnifiedData> unifiedData = UdmfClient::GetInstance()->CreateUnifiedData();
    UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);

    AceEngineExt::GetInstance().DragStartExt();

    CloseSelectOverlay();
    ResetSelection();
    return itemInfo;
}

void TextPattern::InitDragEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    if (eventHub->HasOnDragStart()) {
        LOGD("drag event has already been initialized");
        return;
    }

    auto gestureHub = host->GetOrCreateGestureEventHub();
    gestureHub->InitDragDropEvent();
    gestureHub->SetTextDraggable(true);
    gestureHub->SetThumbnailCallback(GetThumbnailCallback());
    auto onDragStart = [weakPtr = WeakClaim(this)](
                           const RefPtr<Ace::DragEvent>& event, const std::string& extraParams) -> DragDropInfo {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_RETURN(pattern, {});
        return pattern->OnDragStart(event, extraParams);
    };
    if (!eventHub->HasOnDragStart()) {
        eventHub->SetOnDragStart(std::move(onDragStart));
    }
}

std::function<void(Offset)> TextPattern::GetThumbnailCallback()
{
    return [wk = WeakClaim(this)](const Offset& point) {
        auto pattern = wk.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->BetweenSelectedPosition(point)) {
            pattern->dragNode_ = TextDragPattern::CreateDragNode(pattern->GetHost());
            pattern->dragNodeWk_ = pattern->dragNode_;
            FrameNode::ProcessOffscreenNode(pattern->dragNode_);
        }
    };
}
#endif // ENABLE_DRAG_FRAMEWORK

// ===========================================================
// TextDragBase implementations
float TextPattern::GetLineHeight() const
{
    std::vector<Rect> selectedRects;
    paragraph_->GetRectsForRange(textSelector_.GetTextStart(), textSelector_.GetTextEnd(), selectedRects);
    CHECK_NULL_RETURN(selectedRects.size(), {});
    return selectedRects.front().Height();
}

#ifndef USE_GRAPHIC_TEXT_GINE
RSTypographyProperties::TextBox TextPattern::ConvertRect(const Rect& rect)
#else
RSTextRect TextPattern::ConvertRect(const Rect& rect)
#endif
{
    return { RSRect(rect.Left(), rect.Top(), rect.Right(), rect.Bottom()), RSTextDirection::LTR };
}

#ifndef USE_GRAPHIC_TEXT_GINE
std::vector<RSTypographyProperties::TextBox> TextPattern::GetTextBoxes()
#else
std::vector<RSTextRect> TextPattern::GetTextBoxes()
#endif
{
    std::vector<Rect> selectedRects;
    paragraph_->GetRectsForRange(textSelector_.GetTextStart(), textSelector_.GetTextEnd(), selectedRects);
#ifndef USE_GRAPHIC_TEXT_GINE
    std::vector<RSTypographyProperties::TextBox> res;
#else
    std::vector<RSTextRect> res;
#endif
    res.reserve(selectedRects.size());
    for (auto&& rect : selectedRects) {
        res.emplace_back(ConvertRect(rect));
    }
    return res;
}

OffsetF TextPattern::GetParentGlobalOffset() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, {});
    return host->GetPaintRectOffset();
}

void TextPattern::CreateHandles()
{
    ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle);
}

bool TextPattern::BetweenSelectedPosition(const Offset& globalOffset)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto offset = host->GetPaintRectOffset();
    auto localOffset = globalOffset - Offset(offset.GetX(), offset.GetY());
    return IsDraggable(localOffset);
}

// end of TextDragBase implementations
// ===========================================================

void TextPattern::OnModifyDone()
{
    auto textLayoutProperty = GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    if (CheckNeedMeasure(textLayoutProperty->GetPropertyChangeFlag())) {
        // measure flag changed, reset paragraph.
        LOGD("reset on modify done!");
        paragraph_.Reset();
    }

    if (!(PipelineContext::GetCurrentContext() &&
            PipelineContext::GetCurrentContext()->GetMinPlatformVersion() > API_PROTEXTION_GREATER_NINE)) {
        bool shouldClipToContent =
            textLayoutProperty->GetTextOverflow().value_or(TextOverflow::CLIP) == TextOverflow::CLIP;
        host->GetRenderContext()->SetClipToFrame(shouldClipToContent);
    }
    std::string textCache = textForDisplay_;
    textForDisplay_ = textLayoutProperty->GetContent().value_or("");
    if (textCache != textForDisplay_) {
        host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE, textCache, textForDisplay_);
    }

    auto obscuredReasons = renderContext->GetObscured().value_or(std::vector<ObscuredReasons>());
    bool ifHaveObscured = std::any_of(obscuredReasons.begin(), obscuredReasons.end(),
        [](const auto& reason) { return reason == ObscuredReasons::PLACEHOLDER; });
    if (textLayoutProperty->GetTextOverflowValue(TextOverflow::CLIP) == TextOverflow::MARQUEE || ifHaveObscured) {
        CloseSelectOverlay();
        ResetSelection();
        copyOption_ = CopyOptions::None;
        return;
    }
    copyOption_ = textLayoutProperty->GetCopyOption().value_or(CopyOptions::None);
    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    if (copyOption_ != CopyOptions::None) {
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        if (!clipboard_ && context) {
            clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(context->GetTaskExecutor());
        }
        InitLongPressEvent(gestureEventHub);
        if (host->IsDraggable()) {
#ifdef ENABLE_DRAG_FRAMEWORK
            InitDragEvent();
#else
            InitPanEvent(gestureEventHub);
#endif
        }
        InitMouseEvent();
        InitTouchEvent();
        SetAccessibilityAction();
    }
    if (onClick_ || copyOption_ != CopyOptions::None) {
        InitClickEvent(gestureEventHub);
    }
}

void TextPattern::ActSetSelection(int32_t start, int32_t end)
{
    if (start < 0) {
        start = GetWideText().length();
    }
    if (end < 0) {
        end = GetWideText().length();
    }
    textSelector_.Update(start, end);
    CalculateHandleOffsetAndShowOverlay();
    ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextPattern::UpdateSelectOverlayOrCreate(SelectOverlayInfo selectInfo, bool animation)
{
    if (selectOverlayProxy_ && !selectOverlayProxy_->IsClosed()) {
        SelectHandleInfo firstHandleInfo;
        SelectHandleInfo secondHandleInfo;
        firstHandleInfo.paintRect = textSelector_.firstHandle;
        secondHandleInfo.paintRect = textSelector_.secondHandle;
        auto start = textSelector_.GetTextStart();
        auto end = textSelector_.GetTextEnd();
        selectOverlayProxy_->SetSelectInfo(GetSelectedText(start, end));
        selectOverlayProxy_->UpdateFirstAndSecondHandleInfo(firstHandleInfo, secondHandleInfo);
    } else {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        selectInfo.callerFrameNode = GetHost();
        selectOverlayProxy_ =
            pipeline->GetSelectOverlayManager()->CreateAndShowSelectOverlay(selectInfo, WeakClaim(this), animation);
        CHECK_NULL_VOID_NOLOG(selectOverlayProxy_);
        auto start = textSelector_.GetTextStart();
        auto end = textSelector_.GetTextEnd();
        selectOverlayProxy_->SetSelectInfo(GetSelectedText(start, end));
    }
}

bool TextPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (showSelectOverlay_) {
        CalculateHandleOffsetAndShowOverlay();
        ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle);
    }
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto textLayoutAlgorithm = DynamicCast<TextLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(textLayoutAlgorithm, false);
    auto paragraph = textLayoutAlgorithm->GetParagraph();
    if (!paragraph) {
        LOGD("on layout process, just return");
        return false;
    }
    LOGD("on layout process, continue");
    paragraph_ = textLayoutAlgorithm->GetParagraph();
    baselineOffset_ = textLayoutAlgorithm->GetBaselineOffset();
    contentRect_ = dirty->GetGeometryNode()->GetContentRect();
    contentOffset_ = dirty->GetGeometryNode()->GetContentOffset();
    textStyle_ = textLayoutAlgorithm->GetTextStyle();
    return true;
}

void TextPattern::BeforeCreateLayoutWrapper()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    const auto& layoutProperty = host->GetLayoutProperty();
    auto flag = layoutProperty ? layoutProperty->GetPropertyChangeFlag() : PROPERTY_UPDATE_NORMAL;
    // When updating the scenario, needs to determine whether the SpanNode node is refreshed.
    if (paragraph_ && (flag & PROPERTY_UPDATE_BY_CHILD_REQUEST) != PROPERTY_UPDATE_BY_CHILD_REQUEST) {
        LOGD("no need to refresh span node");
        return;
    }
    imageCount_ = 0;
    // When dirty areas are marked because of child node changes, the text rendering node tree is reset.
    const auto& children = host->GetChildren();
    if (children.empty()) {
        return;
    }

    if (paragraph_) {
        LOGD("reset before create layoutwrapper");
        paragraph_.Reset();
    }
    spanItemChildren_.clear();

    // Depth-first iterates through all host's child nodes to collect the SpanNode object, building a text rendering
    // tree.
    std::stack<RefPtr<UINode>> nodes;
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        nodes.push(*iter);
    }

    std::string textCache;
    if (!nodes.empty()) {
        textCache = textForDisplay_;
        textForDisplay_.clear();
    }

    bool isSpanHasClick = false;
    CollectSpanNodes(nodes, isSpanHasClick);

    if (textCache != textForDisplay_) {
        host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE, textCache, textForDisplay_);
    }
    if (isSpanHasClick) {
        auto gestureEventHub = host->GetOrCreateGestureEventHub();
        InitClickEvent(gestureEventHub);
    }
}

void TextPattern::CollectSpanNodes(std::stack<RefPtr<UINode>> nodes, bool& isSpanHasClick)
{
    while (!nodes.empty()) {
        auto current = nodes.top();
        nodes.pop();
        // TODO: Add the judgment of display.
        if (!current) {
            continue;
        }
        auto spanNode = DynamicCast<SpanNode>(current);
        if (spanNode) {
            spanNode->CleanSpanItemChildren();
            UpdateChildProperty(spanNode);
            spanNode->MountToParagraph();
            textForDisplay_.append(spanNode->GetSpanItem()->content);
            if (spanNode->GetSpanItem()->onClick) {
                isSpanHasClick = true;
            }

            // Register callback for fonts.
            FontRegisterCallback(spanNode);
        } else if (current->GetTag() == V2::IMAGE_ETS_TAG) {
            imageCount_++;
            AddChildSpanItem(current);
        }
        const auto& nextChildren = current->GetChildren();
        for (auto iter = nextChildren.rbegin(); iter != nextChildren.rend(); ++iter) {
            nodes.push(*iter);
        }
    }
}

void TextPattern::FontRegisterCallback(RefPtr<SpanNode> spanNode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto callback = [span = AceType::WeakClaim(AceType::RawPtr(spanNode))] {
        auto node = span.Upgrade();
        if (node) {
            node->RequestTextFlushDirty();
        }
    };
    auto fontManager = pipelineContext->GetFontManager();
    auto fontFamilies = spanNode->GetFontFamily();
    if (fontManager && fontFamilies.has_value()) {
        for (const auto& familyName : fontFamilies.value()) {
            fontManager->RegisterCallbackNG(spanNode, familyName, callback);
        }
    }
}

void TextPattern::GetGlobalOffset(Offset& offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    auto globalOffset = host->GetPaintRectOffset() - rootOffset;
    offset = Offset(globalOffset.GetX(), globalOffset.GetY());
}

void TextPattern::OnVisibleChange(bool isVisible)
{
    if (!isVisible) {
        if (textSelector_.IsValid()) {
            CloseSelectOverlay();
            ResetSelection();
        }
    }
}

void TextPattern::InitSurfaceChangedCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (!HasSurfaceChangedCallback()) {
        auto callbackId = pipeline->RegisterSurfaceChangedCallback(
            [weak = WeakClaim(this)](int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight,
                WindowSizeChangeReason type) {
                auto pattern = weak.Upgrade();
                if (pattern) {
                    pattern->HandleSurfaceChanged(newWidth, newHeight, prevWidth, prevHeight);
                }
            });
        LOGD("Add surface changed callback id %{public}d", callbackId);
        UpdateSurfaceChangedCallbackId(callbackId);
    }
}

void TextPattern::HandleSurfaceChanged(int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight)
{
    LOGD("TextPattern handle surface change, new width %{public}d, new height %{public}d, prev width %{public}d, prev "
         "height %{public}d",
        newWidth, newHeight, prevWidth, prevHeight);
    CloseSelectOverlay();
    ResetSelection();
}

void TextPattern::AddChildSpanItem(const RefPtr<UINode>& child)
{
    CHECK_NULL_VOID(child);
    auto chidNode = DynamicCast<FrameNode>(child);
    if (chidNode && chidNode->GetLayoutProperty() && chidNode->GetLayoutProperty()->IsOverlayNode()) {
        return;
    }

    if (child->GetTag() == V2::SPAN_ETS_TAG) {
        auto spanNode = DynamicCast<SpanNode>(child);
        if (spanNode) {
            spanItemChildren_.emplace_back(spanNode->GetSpanItem());
        }
    } else if (child->GetTag() == V2::IMAGE_ETS_TAG) {
        auto imageNode = DynamicCast<FrameNode>(child);
        if (imageNode) {
            spanItemChildren_.emplace_back(MakeRefPtr<ImageSpanItem>());
        }
    }
}

void TextPattern::DumpInfo()
{
    auto textLayoutProp = GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProp);
    DumpLog::GetInstance().AddDesc(std::string("Content: ").append(textLayoutProp->GetContent().value_or(" ")));
    DumpLog::GetInstance().AddDesc(
        std::string("FontColor: ").append(textLayoutProp->GetTextColor().value_or(Color::BLACK).ColorToString()));
    DumpLog::GetInstance().AddDesc(
        std::string("FontSize: ")
            .append(
                (textStyle_.has_value() ? textStyle_->GetFontSize() : Dimension(16.0, DimensionUnit::FP)).ToString()));
}

void TextPattern::UpdateChildProperty(const RefPtr<SpanNode>& child) const
{
    CHECK_NULL_VOID(child);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textLayoutProp = host->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProp);

    auto inheritPropertyInfo = child->CaculateInheritPropertyInfo();
    for (const PropertyInfo& info : inheritPropertyInfo) {
        switch (info) {
            case PropertyInfo::FONTSIZE:
                if (textLayoutProp->HasFontSize()) {
                    child->UpdateFontSizeWithoutFlushDirty(textLayoutProp->GetFontSize().value());
                }
                break;
            case PropertyInfo::FONTCOLOR:
                if (textLayoutProp->HasTextColor()) {
                    child->UpdateTextColorWithoutFlushDirty(textLayoutProp->GetTextColor().value());
                }
                break;
            case PropertyInfo::FONTSTYLE:
                if (textLayoutProp->HasItalicFontStyle()) {
                    child->UpdateItalicFontStyleWithoutFlushDirty(textLayoutProp->GetItalicFontStyle().value());
                }
                break;
            case PropertyInfo::FONTWEIGHT:
                if (textLayoutProp->HasFontWeight()) {
                    child->UpdateFontWeightWithoutFlushDirty(textLayoutProp->GetFontWeight().value());
                }
                break;
            case PropertyInfo::FONTFAMILY:
                if (textLayoutProp->HasFontFamily()) {
                    child->UpdateFontFamilyWithoutFlushDirty(textLayoutProp->GetFontFamily().value());
                }
                break;
            case PropertyInfo::TEXTDECORATION:
                if (textLayoutProp->HasTextDecoration()) {
                    child->UpdateTextDecorationWithoutFlushDirty(textLayoutProp->GetTextDecoration().value());
                    if (textLayoutProp->HasTextDecorationColor()) {
                        child->UpdateTextDecorationColorWithoutFlushDirty(
                            textLayoutProp->GetTextDecorationColor().value());
                    }
                }
                break;
            case PropertyInfo::TEXTCASE:
                if (textLayoutProp->HasTextCase()) {
                    child->UpdateTextCaseWithoutFlushDirty(textLayoutProp->GetTextCase().value());
                }
                break;
            case PropertyInfo::LETTERSPACE:
                if (textLayoutProp->HasLetterSpacing()) {
                    child->UpdateLetterSpacingWithoutFlushDirty(textLayoutProp->GetLetterSpacing().value());
                }
                break;
            case PropertyInfo::LINEHEIGHT:
                if (textLayoutProp->HasLineHeight()) {
                    child->UpdateLineHeightWithoutFlushDirty(textLayoutProp->GetLineHeight().value());
                }
                break;
            default:
                LOGW("Inherited properties are not supported.");
                break;
        }
    }
}

void TextPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textAccessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(textAccessibilityProperty);
    textAccessibilityProperty->SetActionSetSelection([weakPtr = WeakClaim(this)](int32_t start, int32_t end) {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto textLayoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        if (textLayoutProperty->GetCopyOptionValue(CopyOptions::None) != CopyOptions::None) {
            pattern->ActSetSelection(start, end);
        }
    });

    textAccessibilityProperty->SetActionClearSelection([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto textLayoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        if (textLayoutProperty->GetCopyOptionValue(CopyOptions::None) != CopyOptions::None) {
            pattern->CloseSelectOverlay(true);
            pattern->ResetSelection();
        }
    });

    textAccessibilityProperty->SetActionCopy([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto textLayoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        if (textLayoutProperty->GetCopyOptionValue(CopyOptions::None) != CopyOptions::None) {
            pattern->HandleOnCopy();
            pattern->CloseSelectOverlay(true);
            pattern->ResetSelection();
        }
    });
}

void TextPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    auto textLayoutProperty = GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateTextColor(theme->GetTextStyle().GetTextColor());
}
} // namespace OHOS::Ace::NG
