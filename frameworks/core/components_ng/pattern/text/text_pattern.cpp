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

#include "core/components_ng/pattern/text/text_pattern.h"

#include <stack>

#include "base/geometry/ng/rect_t.h"
#include "base/geometry/offset.h"
#include "base/log/dump_log.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/canvas.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline/base/render_context.h"
#include "frameworks/base/window/drag_window.h"

namespace OHOS::Ace::NG {

void TextPattern::OnDetachFromFrameNode(FrameNode* node)
{
    if (selectOverlayProxy_ && !selectOverlayProxy_->IsClosed()) {
        selectOverlayProxy_->Close();
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
    int32_t extendEnd = extend + GetGraphemeClusterLength(extend);
    textSelector_.Update(extend, extendEnd);
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
        return OffsetF(rect.Width(), 0.0f);
    }
    selectLineHeight = metrics.height;
    return OffsetF(static_cast<float>(metrics.offset.GetX()), static_cast<float>(metrics.offset.GetY()));
}

void TextPattern::CalcuateHandleOffsetAndShowOverlay(bool isUsingMouse)
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
    float selectLineHeight = std::max(startSelectHeight, endSelectHeight);
    SizeF handlePaintSize = { SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), selectLineHeight };
    OffsetF firstHandleOffset = startOffset + textPaintOffset - rootOffset;
    OffsetF secondHandleOffset = endOffset + textPaintOffset - rootOffset;

    textSelector_.selectionBaseOffset = firstHandleOffset;
    textSelector_.selectionDestinationOffset = secondHandleOffset;

    RectF firstHandle;
    firstHandle.SetOffset(firstHandleOffset);
    firstHandle.SetSize(handlePaintSize);
    textSelector_.firstHandle = firstHandle;

    RectF secondHandle;
    secondHandle.SetOffset(secondHandleOffset);
    secondHandle.SetSize(handlePaintSize);
    textSelector_.secondHandle = secondHandle;
}

void TextPattern::HandleLongPress(GestureEvent& info)
{
    if (copyOption_ == CopyOptions::None) {
        return;
    }
    auto textPaintOffset = contentRect_.GetOffset() - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
    Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
        info.GetLocalLocation().GetY() - textPaintOffset.GetY() };

    InitSelection(textOffset);
    CalcuateHandleOffsetAndShowOverlay();
    ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
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
    CalcuateHandleOffsetAndShowOverlay();
    if (selectOverlayProxy_) {
        SelectHandleInfo handleInfo;
        if (isFirstHandle) {
            handleInfo.paintRect = textSelector_.firstHandle;
            selectOverlayProxy_->UpdateFirstSelectHandleInfo(handleInfo);
        } else {
            handleInfo.paintRect = textSelector_.secondHandle;
            selectOverlayProxy_->UpdateSecondSelectHandleInfo(handleInfo);
        }
        return;
    }
    ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

std::wstring TextPattern::GetWideText() const
{
    return StringUtils::ToWstring(textForDisplay_);
}

std::string TextPattern::GetSelectedText(int32_t start, int32_t end) const
{
    auto wideText = GetWideText();
    if (start < 0 || end > static_cast<int32_t>(wideText.length()) || start >= end) {
        LOGI("Get selected boundary is invalid");
        return "";
    }
    auto min = std::min(start, end);
    auto max = std::max(start, end);
    return StringUtils::ToString(wideText.substr(min, max - min));
}

void TextPattern::HandleOnCopy()
{
    CHECK_NULL_VOID(clipboard_);
    if (textSelector_.IsValid() && textSelector_.GetTextStart() == textSelector_.GetTextEnd()) {
        LOGW("Nothing to select");
        return;
    }
    auto value = GetSelectedText(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    if (value.empty()) {
        LOGW("Copy value is empty");
        return;
    }
    if (copyOption_ != CopyOptions::None) {
        clipboard_->SetData(value, copyOption_);
    }
    textSelector_.Update(-1, -1);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextPattern::ShowSelectOverlay(const RectF& firstHandle, const RectF& secondHandle)
{
    SelectOverlayInfo selectInfo;
    selectInfo.firstHandle.paintRect = firstHandle;
    selectInfo.secondHandle.paintRect = secondHandle;
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

    if (!menuOptionItems_.empty()) {
        selectInfo.menuOptionItems = GetMenuOptionItems();
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (selectOverlayProxy_ && !selectOverlayProxy_->IsClosed()) {
        selectOverlayProxy_->Close();
    }
    selectOverlayProxy_ = pipeline->GetSelectOverlayManager()->CreateAndShowSelectOverlay(selectInfo);
    CHECK_NULL_VOID_NOLOG(selectOverlayProxy_);
    auto start = textSelector_.GetTextStart();
    auto end = textSelector_.GetTextEnd();
    selectOverlayProxy_->SetSelectInfo(GetSelectedText(start, end));
}

void TextPattern::HandleOnSelectAll()
{
    auto textSize = GetWideText().length();
    textSelector_.Update(0, textSize);
    CalcuateHandleOffsetAndShowOverlay();
    if (selectOverlayProxy_) {
        SelectHandleInfo firstHandleInfo;
        SelectHandleInfo secondHandleInfo;
        firstHandleInfo.paintRect = textSelector_.firstHandle;
        secondHandleInfo.paintRect = textSelector_.secondHandle;
        auto start = textSelector_.GetTextStart();
        auto end = textSelector_.GetTextEnd();
        selectOverlayProxy_->SetSelectInfo(GetSelectedText(start, end));
        selectOverlayProxy_->UpdateFirstAndSecondHandleInfo(firstHandleInfo, secondHandleInfo);
    } else {
        ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle);
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
    gestureHub->SetLongPressEvent(longPressEvent_);
}

void TextPattern::OnHandleTouchUp()
{
    if (selectOverlayProxy_ && !selectOverlayProxy_->IsClosed()) {
        selectOverlayProxy_->Close();
    }
    textSelector_.Update(-1, -1);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextPattern::HandleClickEvent(GestureEvent& info)
{
    if (textSelector_.IsValid()) {
        textSelector_.Update(-1, -1);
        if (selectOverlayProxy_ && !selectOverlayProxy_->IsClosed()) {
            selectOverlayProxy_->Close();
        }
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }

    RectF textContentRect = contentRect_;
    textContentRect.SetTop(contentRect_.GetY() - std::min(baselineOffset_, 0.0f));
    textContentRect.SetHeight(contentRect_.Height() - std::max(baselineOffset_, 0.0f));

    if (textContentRect.IsInRegion(PointF(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY()))) {
        CHECK_NULL_VOID_NOLOG(!spanItemChildren_.empty());
        Offset textOffset = { info.GetLocalLocation().GetX() - textContentRect.GetX(),
            info.GetLocalLocation().GetY() - textContentRect.GetY() };
        CHECK_NULL_VOID(paragraph_);
        auto position = paragraph_->GetHandlePositionForClick(textOffset);
        for (const auto& item : spanItemChildren_) {
            if (item && position < item->positon) {
                CHECK_NULL_VOID_NOLOG(item->onClick);
                GestureEvent spanClickinfo = info;
                EventTarget target = info.GetTarget();
                target.area.SetWidth(Dimension(0.0f));
                target.area.SetHeight(Dimension(0.0f));
                spanClickinfo.SetTarget(target);
                item->onClick(spanClickinfo);
                break;
            }
        }
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
    if (info.GetButton() == MouseButton::RIGHT_BUTTON && info.GetAction() == MouseAction::PRESS) {
        auto textPaintOffset = contentRect_.GetOffset() - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
        Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
            info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
        InitSelection(textOffset);
        CalcuateHandleOffsetAndShowOverlay(true);
        ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
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
    if (copyOption_ != CopyOptions::None && draggable_ &&
        GreatNotEqual(textSelector_.GetTextEnd(), textSelector_.GetTextStart())) {
        // Determine if the pan location is in the selected area
        std::vector<Rect> selectedRects;
        paragraph_->GetRectsForRange(textSelector_.GetTextStart(), textSelector_.GetTextEnd(), selectedRects);
        if (selectedRects.empty()) {
            return false;
        } else {
            auto panOffset = OffsetF(offset.GetX(), offset.GetY()) - contentRect_.GetOffset() +
                             OffsetF(0.0, std::min(baselineOffset_, 0.0f));
            for (const auto& selectedRect : selectedRects) {
                if (selectedRect.IsInRegion(Point(panOffset.GetX(), panOffset.GetY()))) {
                    return true;
                }
            }
            return false;
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

void TextPattern::OnModifyDone()
{
    auto textLayoutProperty = GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    if (CheckNeedMeasure(textLayoutProperty->GetPropertyChangeFlag())) {
        // measure flag changed, reset paragraph.
        paragraph_.Reset();
    }

    bool shouldClipToContent = textLayoutProperty->GetTextOverflow().value_or(TextOverflow::CLIP) == TextOverflow::CLIP;
    host->GetRenderContext()->SetClipToFrame(shouldClipToContent);

    textForDisplay_ = textLayoutProperty->GetContent().value_or("");
    copyOption_ = textLayoutProperty->GetCopyOption().value_or(CopyOptions::None);
    draggable_ = textLayoutProperty->GetDraggable().value_or(false);
    if (copyOption_ != CopyOptions::None) {
        auto context = host->GetContext();
        CHECK_NULL_VOID(context);
        if (!clipboard_ && context) {
            clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(context->GetTaskExecutor());
        }
        auto gestureEventHub = host->GetOrCreateGestureEventHub();
        InitLongPressEvent(gestureEventHub);
        if (draggable_) {
            InitPanEvent(gestureEventHub);
        }
        InitClickEvent(gestureEventHub);
        InitMouseEvent();
    }
}

bool TextPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
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
    if (paragraph_) {
        // When updating the scenario, needs to determine whether the SpanNode node is refreshed.
        if ((flag & PROPERTY_UPDATE_BY_CHILD_REQUEST) != PROPERTY_UPDATE_BY_CHILD_REQUEST) {
            LOGD("no need to refresh span node");
            return;
        }
    }

    // When dirty areas are marked because of child node changes, the text rendering node tree is reset.
    const auto& children = host->GetChildren();
    if (children.empty()) {
        return;
    }

    if (paragraph_) {
        paragraph_.Reset();
    }
    spanItemChildren_.clear();

    // Depth-first iterates through all host's child nodes to collect the SpanNode object, building a text rendering
    // tree.
    std::stack<RefPtr<UINode>> nodes;
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        nodes.push(*iter);
    }

    if (!nodes.empty()) {
        textForDisplay_.clear();
        auto gestureEventHub = host->GetOrCreateGestureEventHub();
        InitClickEvent(gestureEventHub);
    }

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
            spanNode->MountToParagraph();
            textForDisplay_.append(spanNode->GetSpanItem()->content);
        }
        const auto& nextChildren = current->GetChildren();
        for (auto iter = nextChildren.rbegin(); iter != nextChildren.rend(); ++iter) {
            nodes.push(*iter);
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
            textSelector_.Update(-1, -1);
            if (selectOverlayProxy_ && !selectOverlayProxy_->IsClosed()) {
                selectOverlayProxy_->Close();
            }
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    }
}

void TextPattern::DumpInfo()
{
    auto textLayoutProp = GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProp);
    DumpLog::GetInstance().AddDesc(std::string("Content: ").append(textLayoutProp->GetContent().value_or(" ")));
}

} // namespace OHOS::Ace::NG
