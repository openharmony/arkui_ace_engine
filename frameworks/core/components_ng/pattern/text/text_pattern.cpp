/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include <cstdint>
#include <stack>
#include <string>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/offset.h"
#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "base/window/drag_window.h"
#include "core/common/ace_engine_ext.h"
#include "core/common/ai/data_detector_mgr.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/font_manager.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/common/udmf/udmf_client.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_info.h"
#include "core/components_ng/pattern/rich_editor_drag/rich_editor_drag_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/text_event_hub.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/event/ace_events.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double DIMENSION_VALUE = 16.0;
constexpr const char COPY_ACTION[] = "copy";
constexpr const char SELECT_ACTION[] = "select";
constexpr const char SYMBOL_COLOR[] = "BLACK";
constexpr int32_t API_PROTEXTION_GREATER_NINE = 9;
constexpr float DOUBLECLICK_INTERVAL_MS = 300.0f;
constexpr uint32_t SECONDS_TO_MILLISECONDS = 1000;
const std::u16string SYMBOL_TRANS = u"\uF0001";
const std::string NEWLINE = "\n";
const std::wstring WIDE_NEWLINE = StringUtils::ToWstring(NEWLINE);
}; // namespace

void TextPattern::OnAttachToFrameNode()
{
    InitSurfaceChangedCallback();
    InitSurfacePositionChangedCallback();
    auto textLayoutProperty = GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateTextAlign(TextAlign::START);
    textLayoutProperty->UpdateAlignment(Alignment::CENTER_LEFT);
}

void TextPattern::OnDetachFromFrameNode(FrameNode* node)
{
    dataDetectorAdapter_->aiDetectDelayTask_.Cancel();
    CloseSelectOverlay();
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    if (HasSurfaceChangedCallback()) {
        pipeline->UnregisterSurfaceChangedCallback(surfaceChangedCallbackId_.value_or(-1));
    }
    if (HasSurfacePositionChangedCallback()) {
        pipeline->UnregisterSurfacePositionChangedCallback(surfacePositionChangedCallbackId_.value_or(-1));
    }
    auto frameNode = WeakClaim(node);
    pipeline->RemoveFontNodeNG(frameNode);
    auto fontManager = pipeline->GetFontManager();
    if (fontManager) {
        fontManager->UnRegisterCallbackNG(frameNode);
        fontManager->RemoveVariationNodeNG(frameNode);
    }
    pipeline->RemoveOnAreaChangeNode(node->GetId());
}

void TextPattern::CloseSelectOverlay()
{
    CloseSelectOverlay(false);
}

void TextPattern::CloseSelectOverlay(bool animation)
{
    // Deprecated use selectOverlay_ instead.
    if (selectOverlayProxy_ && !selectOverlayProxy_->IsClosed()) {
        selectOverlayProxy_->Close(animation);
        RemoveAreaChangeInner();
    }
    selectOverlay_->CloseOverlay(animation, CloseReason::CLOSE_REASON_NORMAL);
}

void TextPattern::ResetSelection()
{
    if (textSelector_.IsValid()) {
        HandleSelectionChange(-1, -1);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void TextPattern::InitSelection(const Offset& pos)
{
    CHECK_NULL_VOID(paragraph_);
    int32_t extend = paragraph_->GetGlyphIndexByCoordinate(pos, true);
    if (IsLineBreakOrEndOfParagraph(extend)) {
        extend--;
    }
    int32_t start = 0;
    int32_t end = 0;
    if (!paragraph_->GetWordBoundary(extend, start, end)) {
        start = extend;
        end = std::min(static_cast<int32_t>(GetWideText().length()) + placeholderCount_,
            extend + GetGraphemeClusterLength(GetWideText(), extend));
    }
    HandleSelectionChange(start, end);
}

bool TextPattern::IsLineBreakOrEndOfParagraph(int32_t pos) const
{
    CHECK_NULL_RETURN(pos < static_cast<int32_t>(GetWideText().length() + placeholderCount_), true);
    auto data = GetWideText();
    CHECK_NULL_RETURN(data[pos] == WIDE_NEWLINE[0], false);
    return true;
}

void TextPattern::CalcCaretMetricsByPosition(int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto rect = host->GetGeometryNode()->GetFrameRect();
    CHECK_NULL_VOID(paragraph_);
    auto computeSuccess = paragraph_->CalcCaretMetricsByPosition(extent, caretCaretMetric, textAffinity);
    if (!computeSuccess) {
        caretCaretMetric = CaretMetricsF(OffsetF(0.0f, rect.Width()), 0.0f);
    }
}

void TextPattern::CalculateHandleOffsetAndShowOverlay(bool isUsingMouse)
{
    auto textContentGlobalOffset = parentGlobalOffset_ + contentRect_.GetOffset();
    auto paragraphPaintOffset = textContentGlobalOffset - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));

    // calculate firstHandleOffset, secondHandleOffset and handlePaintSize
    CaretMetricsF firstHandleMetrics;
    CaretMetricsF secondHandleMetrics;
    CalcCaretMetricsByPosition(textSelector_.baseOffset, firstHandleMetrics, TextAffinity::DOWNSTREAM);
    CalcCaretMetricsByPosition(textSelector_.destinationOffset, secondHandleMetrics, TextAffinity::UPSTREAM);
    OffsetF firstHandleOffset = firstHandleMetrics.offset + paragraphPaintOffset;
    OffsetF secondHandleOffset = secondHandleMetrics.offset + paragraphPaintOffset;

    textSelector_.selectionBaseOffset = firstHandleOffset;
    textSelector_.selectionDestinationOffset = secondHandleOffset;

    RectF firstHandle;
    firstHandle.SetOffset(firstHandleOffset);
    firstHandle.SetSize({ SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), firstHandleMetrics.height });
    textSelector_.firstHandle = firstHandle;

    RectF secondHandle;
    secondHandle.SetOffset(secondHandleOffset);
    secondHandle.SetSize({ SelectHandleInfo::GetDefaultLineWidth().ConvertToPx(), secondHandleMetrics.height });
    secondHandle.SetHeight(secondHandleMetrics.height);
    textSelector_.secondHandle = secondHandle;
}

SelectionInfo TextPattern::GetSpansInfo(int32_t start, int32_t end, GetSpansMethod method)
{
    int32_t index = 0;
    std::int32_t realEnd = 0;
    std::int32_t realStart = 0;
    SelectionInfo selection;
    std::list<ResultObject> resultObjects;
    auto length = GetTextContentLength();
    if (method == GetSpansMethod::GETSPANS) {
        realStart = (start == -1) ? 0 : start;
        realEnd = (end == -1) ? length : end;
        if (realStart > realEnd) {
            std::swap(realStart, realEnd);
        }
        realStart = std::max(0, realStart);
        realEnd = std::min(length, realEnd);
    } else if (method == GetSpansMethod::ONSELECT) {
        realEnd = std::min(length, end);
        realStart = std::min(length, start);
    }
    selection.SetSelectionEnd(realEnd);
    selection.SetSelectionStart(realStart);
    // Verify that realStart, realEnd, and spans_ are valid
    if (realStart > length || realEnd < 0 || spans_.empty() || (start > length && end > length) ||
        (method == GetSpansMethod::ONSELECT && realStart == realEnd)) {
        selection.SetResultObjectList(resultObjects);
        return selection;
    }
    auto children = GetAllChildren();
    for (const auto& uinode : children) {
        if (uinode->GetTag() == V2::IMAGE_ETS_TAG) {
            ResultObject resultObject = GetImageResultObject(uinode, index, realStart, realEnd);
            if (!resultObject.valueString.empty() || resultObject.valuePixelMap) {
                resultObjects.emplace_back(resultObject);
            }
        } else if (uinode->GetTag() == V2::SPAN_ETS_TAG) {
            ResultObject resultObject = GetTextResultObject(uinode, index, realStart, realEnd);
            if (!resultObject.valueString.empty()) {
                resultObjects.emplace_back(resultObject);
            }
        } else if (uinode->GetTag() == V2::SYMBOL_SPAN_ETS_TAG) {
            ResultObject resultObject = GetSymbolSpanResultObject(uinode, index, realStart, realEnd);
            if (!resultObject.valueString.empty()) {
                resultObjects.emplace_back(resultObject);
            }
        } else if (uinode->GetTag() == V2::PLACEHOLDER_SPAN_ETS_TAG) {
            ResultObject resultObject = GetBuilderResultObject(uinode, index, realStart, realEnd);
            if (!resultObject.valueString.empty()) {
                resultObjects.emplace_back(resultObject);
            }
        }
        index++;
    }
    selection.SetResultObjectList(resultObjects);
    return selection;
}

int32_t TextPattern::GetTextContentLength()
{
    if (!spans_.empty()) {
        return static_cast<int32_t>(GetWideText().length()) + placeholderCount_;
    }
    return 0;
}

void TextPattern::HandleLongPress(GestureEvent& info)
{
    HandleSpanLongPressEvent(info);
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
        dragBoxes_ = GetTextBoxes();
        // prevent long press event from being triggered when dragging
        gestureHub->SetIsTextDraggable(true);
        return;
    }
    gestureHub->SetIsTextDraggable(false);
    auto textPaintOffset = contentRect_.GetOffset() - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));
    Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
        info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
    InitSelection(textOffset);
    textResponseType_ = TextResponseType::LONG_PRESS;
    UpdateSelectionSpanType(std::min(textSelector_.baseOffset, textSelector_.destinationOffset),
        std::max(textSelector_.baseOffset, textSelector_.destinationOffset));
    oldSelectedType_ = selectedType_.value_or(TextSpanType::NONE);
    parentGlobalOffset_ = GetParentGlobalOffset();
    CalculateHandleOffsetAndShowOverlay();
    CloseSelectOverlay(true);
    ShowSelectOverlay({ .animation = true });
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextPattern::HandleSpanLongPressEvent(GestureEvent& info)
{
    RectF textContentRect = contentRect_;
    textContentRect.SetTop(contentRect_.GetY() - std::min(baselineOffset_, 0.0f));
    textContentRect.SetHeight(contentRect_.Height() - std::max(baselineOffset_, 0.0f));

    auto localLocation = info.GetLocalLocation();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(host);
    PointF textOffset = { static_cast<float>(localLocation.GetX()) - textContentRect.GetX(),
        static_cast<float>(localLocation.GetY()) - textContentRect.GetY() };
    if (renderContext->GetClipEdge().has_value() && !renderContext->GetClipEdge().value() && overlayMod_) {
        textContentRect = overlayMod_->GetBoundsRect();
        textContentRect.SetTop(contentRect_.GetY() - std::min(baselineOffset_, 0.0f));
    }
    auto longPressFunc = [](RefPtr<SpanItem> item, GestureEvent& info, const RectF& rect,
                             const PointF& textOffset) -> bool {
        if (rect.IsInRegion(textOffset)) {
            if (item && item->onLongPress) {
                item->onLongPress(info);
            }
            return true;
        }
        return false;
    };

    if (textContentRect.IsInRegion(
        PointF(static_cast<float>(localLocation.GetX()), static_cast<float>(localLocation.GetY()))) &&
        !spans_.empty() && paragraph_) {
        int32_t start = 0;
        for (const auto& item : spans_) {
            if (!item) {
                continue;
            }
            std::vector<RectF> selectedRects;
            paragraph_->GetRectsForRange(start, item->position, selectedRects);
            for (auto && rect : selectedRects) {
                CHECK_NULL_VOID(!longPressFunc(item, info, rect, textOffset));
            }
            start = item->position;
        }
    }
}

// Deprecated: Use the TextSelectOverlay::OnHandleMove() instead.
// It is currently used by RichEditorPattern.
void TextPattern::OnHandleMove(const RectF& handleRect, bool isFirstHandle)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textContentGlobalOffset = parentGlobalOffset_ + contentRect_.GetOffset();
    auto textPaintOffset = textContentGlobalOffset - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));

    auto localOffset = handleRect.GetOffset();

    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->GetClipEdge().value_or(false)) {
        if (localOffset.GetX() < textContentGlobalOffset.GetX()) {
            localOffset.SetX(textContentGlobalOffset.GetX());
        } else if (GreatOrEqual(localOffset.GetX(), textContentGlobalOffset.GetX() + contentRect_.Width())) {
            localOffset.SetX(textContentGlobalOffset.GetX() + contentRect_.Width());
        }

        if (localOffset.GetY() < textContentGlobalOffset.GetY()) {
            localOffset.SetY(textContentGlobalOffset.GetY());
        } else if (GreatNotEqual(localOffset.GetY(), textContentGlobalOffset.GetY() + contentRect_.Height())) {
            localOffset.SetY(textContentGlobalOffset.GetY() + contentRect_.Height());
        }
    }

    localOffset -= textPaintOffset;

    CHECK_NULL_VOID(paragraph_);
    // the handle position is calculated based on the middle of the handle height.
    UpdateSelectorOnHandleMove(localOffset, handleRect.Height(), isFirstHandle);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    CHECK_NULL_VOID(selectOverlayProxy_);
    auto start = textSelector_.GetTextStart();
    auto end = textSelector_.GetTextEnd();
    selectOverlayProxy_->SetSelectInfo(GetSelectedText(start, end));
}

void TextPattern::UpdateSelectorOnHandleMove(const OffsetF& localOffset, float handleHeight, bool isFirstHandle)
{
    if (isFirstHandle) {
        auto start = GetHandleIndex(Offset(
            localOffset.GetX(), localOffset.GetY() + (selectOverlayProxy_->IsHandleReverse() ? handleHeight : 0)));
        HandleSelectionChange(start, textSelector_.destinationOffset);
    } else {
        auto end = GetHandleIndex(Offset(localOffset.GetX(),
            localOffset.GetY() +
                (selectOverlayProxy_->IsHandleReverse() || NearEqual(localOffset.GetY(), 0) ? 0 : handleHeight)));
        HandleSelectionChange(textSelector_.baseOffset, end);
    }
}

bool TextPattern::IsSelectAll()
{
    return textSelector_.GetTextStart() == 0 &&
           textSelector_.GetTextEnd() == static_cast<int32_t>(GetWideText().length()) + placeholderCount_;
}
std::wstring TextPattern::GetWideText() const
{
    return StringUtils::ToWstring(textForDisplay_);
}

std::string TextPattern::GetSelectedText(int32_t start, int32_t end) const
{
    if (spans_.empty()) {
        auto wideText = GetWideText();
        auto min = std::clamp(std::max(std::min(start, end), 0), 0, static_cast<int32_t>(wideText.length()));
        auto max = std::clamp(std::min(std::max(start, end), static_cast<int32_t>(wideText.length())), 0,
            static_cast<int32_t>(wideText.length()));
        return StringUtils::ToString(wideText.substr(min, max - min));
    }
    std::string value;
    int32_t tag = 0;
    for (const auto& span : spans_) {
        if (span->GetSymbolUnicode() != 0) {
            tag = span->position == -1 ? tag + 1 : span->position;
            continue;
        }
        if (span->position - 1 >= start && span->placeholderIndex == -1 && span->position != -1) {
            auto wideString = StringUtils::ToWstring(span->GetSpanContent());
            auto max = std::min(span->position, end);
            auto min = std::max(start, tag);
            value += StringUtils::ToString(
                wideString.substr(std::clamp((min - tag), 0, static_cast<int32_t>(wideString.length())),
                    std::clamp((max - min), 0, static_cast<int32_t>(wideString.length()))));
        }
        tag = span->position == -1 ? tag + 1 : span->position;
        if (span->position >= end) {
            break;
        }
    }
    return value;
}

void TextPattern::HandleOnCopy()
{
    CHECK_NULL_VOID(clipboard_);
    if (textSelector_.IsValid() && textSelector_.GetTextStart() == textSelector_.GetTextEnd()) {
        HandleSelectionChange(-1, -1);
        return;
    }
    auto value = GetSelectedText(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    if (value.empty()) {
        HiddenMenu();
        return;
    }
    if (copyOption_ != CopyOptions::None) {
        clipboard_->SetData(value, copyOption_);
    }
    HiddenMenu();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnCopy(value);
}

void TextPattern::HiddenMenu()
{
    if (IsUsingMouse()) {
        CloseSelectOverlay();
    } else {
        selectOverlay_->HideMenu();
    }
}

void TextPattern::SetTextSelection(int32_t selectionStart, int32_t selectionEnd)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto context = PipelineContext::GetCurrentContextSafely();
    if (context) {
        context->AddAfterLayoutTask([weak = WeakClaim(this), selectionStart, selectionEnd, eventHub]() {
            auto textPattern = weak.Upgrade();
            CHECK_NULL_VOID(textPattern);
            auto renderContext = textPattern->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            auto obscuredReasons = renderContext->GetObscured().value_or(std::vector<ObscuredReasons>());
            bool ifHaveObscured = std::any_of(obscuredReasons.begin(), obscuredReasons.end(),
                [](const auto& reason) { return reason == ObscuredReasons::PLACEHOLDER; });
            auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(textLayoutProperty);
            if (textLayoutProperty->GetCalcLayoutConstraint() &&
                textLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize.has_value()) {
                auto selfIdealSizeWidth = textLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize->Width();
                auto selfIdealSizeHeight = textLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize->Height();
                auto constraint = textLayoutProperty->GetLayoutConstraint();
                if ((selfIdealSizeWidth.has_value() && NearZero(selfIdealSizeWidth->GetDimension().ConvertToPxWithSize(
                                                           constraint->percentReference.Width()))) ||
                    (selfIdealSizeHeight.has_value() &&
                        NearZero(selfIdealSizeHeight->GetDimension().ConvertToPxWithSize(
                            constraint->percentReference.Height())))) {
                    return;
                }
            }
            if (textLayoutProperty->GetCopyOptionValue(CopyOptions::None) == CopyOptions::None ||
                textLayoutProperty->GetTextOverflowValue(TextOverflow::CLIP) == TextOverflow::MARQUEE) {
                return;
            }
            if ((!textPattern->GetAllChildren().empty() || !ifHaveObscured) && eventHub->IsEnabled()) {
                textPattern->ActSetSelection(selectionStart, selectionEnd);
            }
        });
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

RefPtr<RenderContext> TextPattern::GetRenderContext()
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetRenderContext();
}

void TextPattern::ShowSelectOverlay(const OverlayRequest& request)
{
    auto textLayoutProperty = GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    if (textLayoutProperty->GetMaxLines() == 0) {
        CloseSelectOverlay();
        ResetSelection();
        return;
    }
    selectOverlay_->ProcessOverlay(request);
}

void TextPattern::HandleOnSelectAll()
{
    auto textSize = static_cast<int32_t>(GetWideText().length()) + placeholderCount_;
    HandleSelectionChange(0, textSize);
    CalculateHandleOffsetAndShowOverlay();
    CloseSelectOverlay(true);
    if (IsUsingMouse()) {
        if (IsSelected()) {
            selectOverlay_->SetSelectionHoldCallback();
        }
    } else {
        ShowSelectOverlay({ .animation = true });
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextPattern::InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    constexpr int32_t longPressDelay = 600;
    if (longPressEvent_) {
        gestureHub->SetLongPressEvent(longPressEvent_, false, false, longPressDelay);
        return;
    }
    auto longPressCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->sourceType_ = info.GetSourceDevice();
        pattern->HandleLongPress(info);
    };
    longPressEvent_ = MakeRefPtr<LongPressEvent>(std::move(longPressCallback));

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
    if (dataDetectorAdapter_->hasClickedAISpan_) {
        dataDetectorAdapter_->hasClickedAISpan_ = false;
    } else if (hasClicked_) {
        hasClicked_ = false;
        TimeStamp clickTimeStamp = info.GetTimeStamp();
        std::chrono::duration<float, std::ratio<1, SECONDS_TO_MILLISECONDS>> timeout =
            clickTimeStamp - lastClickTimeStamp_;
        lastClickTimeStamp_ = info.GetTimeStamp();
        if (timeout.count() < DOUBLECLICK_INTERVAL_MS) {
            HandleDoubleClickEvent(info);
            return;
        }
    }
    HandleSingleClickEvent(info);
}

void TextPattern::HandleSingleClickEvent(GestureEvent& info)
{
    hasClicked_ = true;
    lastClickTimeStamp_ = info.GetTimeStamp();
    if (selectOverlay_->SelectOverlayIsOn() && !selectOverlay_->IsUsingMouse() &&
        BetweenSelectedPosition(info.GetGlobalLocation())) {
        selectOverlay_->ShowMenu();
        return;
    }
    RectF textContentRect = contentRect_;
    textContentRect.SetTop(contentRect_.GetY() - std::min(baselineOffset_, 0.0f));
    textContentRect.SetHeight(contentRect_.Height() - std::max(baselineOffset_, 0.0f));
    PointF textOffset = { info.GetLocalLocation().GetX() - textContentRect.GetX(),
        info.GetLocalLocation().GetY() - textContentRect.GetY() };
    if (!isMousePressed_) {
        HandleClickAISpanEvent(textOffset);
    }
    if (dataDetectorAdapter_->hasClickedAISpan_) {
        selectOverlay_->DisableMenu();
        return;
    }

    if (textSelector_.IsValid() && mouseStatus_ != MouseStatus::MOVE) {
        CloseSelectOverlay(true);
        ResetSelection();
    }
    bool isClickOnSpan = false;
    HandleSpanSingleClickEvent(info, textContentRect, isClickOnSpan);

    if (onClick_ && !isClickOnSpan) {
        auto onClick = onClick_;
        onClick(info);
        if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            auto text = host->GetAccessibilityProperty<NG::AccessibilityProperty>()->GetText();
            Recorder::EventParamsBuilder builder;
            builder.SetId(host->GetInspectorIdValue(""))
                .SetType(host->GetTag())
                .SetText(text)
                .SetDescription(host->GetAutoEventParamValue(""));
            Recorder::EventRecorder::Get().OnClick(std::move(builder));
        }
    }
}

void TextPattern::HandleClickAISpanEvent(const PointF& textOffset)
{
    dataDetectorAdapter_->hasClickedAISpan_ = false;
    if (!NeedShowAIDetect() || mouseStatus_ == MouseStatus::MOVE || IsDragging()) {
        return;
    }

    for (const auto& kv : dataDetectorAdapter_->aiSpanMap_) {
        auto& aiSpan = kv.second;
        ClickAISpan(textOffset, aiSpan);
        if (dataDetectorAdapter_->hasClickedAISpan_) {
            return;
        }
    }
}

bool TextPattern::CheckClickedOnSpanOrText(RectF textContentRect, const Offset& localLocation)
{
    clickedSpanPosition_ = -1;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_RETURN(host, false);
    PointF textOffset = { static_cast<float>(localLocation.GetX()) - textContentRect.GetX(),
        static_cast<float>(localLocation.GetY()) - textContentRect.GetY() };
    if (!renderContext->GetClipEdge().value_or(false) && overlayMod_) {
        textContentRect = overlayMod_->GetBoundsRect();
        textContentRect.SetTop(contentRect_.GetY() - std::min(baselineOffset_, 0.0f));
    }
    if (textContentRect.IsInRegion(
            PointF(static_cast<float>(localLocation.GetX()), static_cast<float>(localLocation.GetY()))) &&
        !spans_.empty() && paragraph_) {
        if (CalculateClickedSpanPosition(textOffset)) {
            return true;
        }
    }
    if (onClick_) {
        return true;
    }
    return false;
}

bool TextPattern::CalculateClickedSpanPosition(const PointF& textOffset)
{
    int32_t start = 0;
    for (const auto& item : spans_) {
        clickedSpanPosition_++;
        if (!item) {
            continue;
        }
        std::vector<RectF> selectedRects;
        paragraph_->GetRectsForRange(start, item->position, selectedRects);
        start = item->position;
        for (auto && rect : selectedRects) {
            if (rect.IsInRegion(textOffset)) {
                CHECK_NULL_RETURN(!item->onClick, true);
                clickedSpanPosition_ = -1;
                return false;
            }
        }
    }
    clickedSpanPosition_ = -1;
    return false;
}

void TextPattern::HandleSpanSingleClickEvent(GestureEvent& info, RectF textContentRect, bool& isClickOnSpan)
{
    if (copyOption_ != CopyOptions::None) {
        CheckClickedOnSpanOrText(textContentRect, info.GetLocalLocation());
    }
    TAG_LOGD(AceLogTag::ACE_TEXT, "HandleSpanSingleClickEvent clickedSpanPosition_: %{public}d", clickedSpanPosition_);
    CHECK_NULL_VOID(clickedSpanPosition_ != -1);
    isClickOnSpan = true;
    auto iter = spans_.begin();
    std::advance(iter, clickedSpanPosition_);
    RefPtr<SpanItem> span;
    if (iter == spans_.end()) {
        span = spans_.back();
    } else {
        span = *iter;
    }
    CHECK_NULL_VOID(span);
    CHECK_NULL_VOID(span->onClick);
    GestureEvent spanClickinfo = info;
    EventTarget target = info.GetTarget();
    target.area.SetWidth(Dimension(0.0f));
    target.area.SetHeight(Dimension(0.0f));
    spanClickinfo.SetTarget(target);
    span->onClick(spanClickinfo);
    if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
        Recorder::EventParamsBuilder builder;
        builder.SetId(span->inspectId).SetText(span->content).SetDescription(span->description);
        Recorder::EventRecorder::Get().OnClick(std::move(builder));
    }
}

bool TextPattern::ClickAISpan(const PointF& textOffset, const AISpan& aiSpan)
{
    std::vector<RectF> aiRects;
    paragraph_->GetRectsForRange(aiSpan.start, aiSpan.end, aiRects);
    for (auto&& rect : aiRects) {
        if (rect.IsInRegion(textOffset)) {
            dataDetectorAdapter_->hasClickedAISpan_ = true;
            if (leftMousePressed_) {
                dataDetectorAdapter_->ResponseBestMatchItem(aiSpan);
                return true;
            }
            return ShowUIExtensionMenu(aiSpan);
        }
    }
    return false;
}

void TextPattern::SetOnClickMenu(const AISpan& aiSpan, const CalculateHandleFunc& calculateHandleFunc,
    const ShowSelectOverlayFunc& showSelectOverlayFunc)

{
    dataDetectorAdapter_->onClickMenu_ = [aiSpan, weak = WeakClaim(this), calculateHandleFunc, showSelectOverlayFunc](
                                             const std::string& action) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->copyOption_ == CopyOptions::None) {
            return;
        }
        pattern->CloseSelectOverlay();
        if (action == std::string(COPY_ACTION)) {
            pattern->HandleSelectionChange(aiSpan.start, aiSpan.end);
            pattern->HandleOnCopy();
        } else if (action == std::string(SELECT_ACTION)) {
            pattern->HandleSelectionChange(aiSpan.start, aiSpan.end);
            if (calculateHandleFunc == nullptr) {
                pattern->CalculateHandleOffsetAndShowOverlay();
            } else {
                calculateHandleFunc();
            }
            if (showSelectOverlayFunc == nullptr) {
                pattern->ShowSelectOverlay({ .animation = true });
            } else {
                showSelectOverlayFunc(pattern->textSelector_.firstHandle, pattern->textSelector_.secondHandle);
            }
            auto frameNode = pattern->GetHost();
            CHECK_NULL_VOID(frameNode);
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    };
}

bool TextPattern::ShowUIExtensionMenu(const AISpan& aiSpan, const CalculateHandleFunc& calculateHandleFunc,
    const ShowSelectOverlayFunc& showSelectOverlayFunc)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    SetOnClickMenu(aiSpan, calculateHandleFunc, showSelectOverlayFunc);
    auto baseOffset = textSelector_.baseOffset;
    auto destinationOffset = textSelector_.destinationOffset;
    HandleSelectionChange(aiSpan.start, aiSpan.end);
    parentGlobalOffset_ = GetParentGlobalOffset();
    if (calculateHandleFunc == nullptr) {
        CalculateHandleOffsetAndShowOverlay();
    } else {
        calculateHandleFunc();
    }
    HandleSelectionChange(baseOffset, destinationOffset);
    RectF aiRect;
    if (textSelector_.firstHandle.Top() != textSelector_.secondHandle.Top()) {
        auto top = std::min(textSelector_.firstHandle.Top(), textSelector_.secondHandle.Top());
        auto bottom = std::max(textSelector_.firstHandle.Bottom(), textSelector_.secondHandle.Bottom());
        auto paintRect = host->GetPaintRectWithTransform();
        auto left = paintRect.Left();
        auto right = paintRect.Right();
        aiRect = RectT(left, top, right - left, bottom - top);
    } else {
        aiRect = textSelector_.firstHandle.CombineRectT(textSelector_.secondHandle);
    }

    return dataDetectorAdapter_->ShowUIExtensionMenu(aiSpan, aiRect, host);
}

void TextPattern::HandleDoubleClickEvent(GestureEvent& info)
{
    CheckOnClickEvent(info);
    if (copyOption_ == CopyOptions::None || textForDisplay_.empty()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    isDoubleClick_ = true;
    auto textPaintOffset = contentRect_.GetOffset() - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));
    Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
        info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
    InitSelection(textOffset);
    textResponseType_ = TextResponseType::NONE;
    UpdateSelectionSpanType(std::min(textSelector_.baseOffset, textSelector_.destinationOffset),
        std::max(textSelector_.baseOffset, textSelector_.destinationOffset));
    parentGlobalOffset_ = GetParentGlobalOffset();
    CalculateHandleOffsetAndShowOverlay();
    if (!isMousePressed_) {
        ShowSelectOverlay({ .animation = true });
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextPattern::CheckOnClickEvent(GestureEvent& info)
{
    bool isClickOnSpan = false;
    RectF textContentRect = contentRect_;
    textContentRect.SetTop(contentRect_.GetY() - std::min(baselineOffset_, 0.0f));
    textContentRect.SetHeight(contentRect_.Height() - std::max(baselineOffset_, 0.0f));
    PointF textOffset = { info.GetLocalLocation().GetX() - textContentRect.GetX(),
        info.GetLocalLocation().GetY() - textContentRect.GetY() };
    HandleSpanSingleClickEvent(info, textContentRect, isClickOnSpan);
    if (onClick_ && !isClickOnSpan) {
        auto onClick = onClick_;
        onClick(info);
    }
}

void TextPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!clickEventInitialized_);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->sourceType_ = info.GetSourceDevice();
        pattern->HandleClickEvent(info);
    };
    auto clickListener = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    clickListener->SetSysJudge([weak = WeakClaim(this)](const RefPtr<GestureInfo>& gestureInfo,
                                   const std::shared_ptr<BaseGestureEvent>& info) -> GestureJudgeResult {
        auto textPattern = weak.Upgrade();
        CHECK_NULL_RETURN(textPattern, GestureJudgeResult::CONTINUE);
        if (info->GetFingerList().empty()) {
            return GestureJudgeResult::CONTINUE;
        }
        auto localLocation = info->GetFingerList().begin()->localLocation_;
        auto contentRect = textPattern->GetTextContentRect();
        auto baselineOffset = textPattern->GetBaselineOffset();

        RectF textContentRect = contentRect;
        textContentRect.SetTop(contentRect.GetY() - std::min(baselineOffset, 0.0f));
        textContentRect.SetHeight(contentRect.Height() - std::max(baselineOffset, 0.0f));
        if (textPattern->GetCopyOptions() == CopyOptions::None &&
            !textPattern->CheckClickedOnSpanOrText(textContentRect, localLocation)) {
            return GestureJudgeResult::REJECT;
        }
        return GestureJudgeResult::CONTINUE;
    });
    gestureHub->AddClickEvent(clickListener);
    clickEventInitialized_ = true;
}

void TextPattern::InitMouseEvent()
{
    CHECK_NULL_VOID(!mouseEventInitialized_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);

    auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->sourceType_ = info.GetSourceDevice();
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

    auto textPaintOffset = contentRect_.GetOffset() - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));
    Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
        info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
    if (info.GetButton() == MouseButton::LEFT_BUTTON) {
        HandleMouseLeftButton(info, textOffset);
        if (IsSelected()) {
            selectOverlay_->SetSelectionHoldCallback();
        }
    } else if (info.GetButton() == MouseButton::RIGHT_BUTTON) {
        HandleMouseRightButton(info, textOffset);
    }
}

void TextPattern::HandleMouseLeftButton(const MouseInfo& info, const Offset& textOffset)
{
    if (info.GetAction() == MouseAction::PRESS) {
        HandleMouseLeftPressAction(info, textOffset);
    } else if (info.GetAction() == MouseAction::MOVE) {
        HandleMouseLeftMoveAction(info, textOffset);
    } else if (info.GetAction() == MouseAction::RELEASE) {
        HandleMouseLeftReleaseAction(info, textOffset);
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextPattern::HandleMouseLeftPressAction(const MouseInfo& info, const Offset& textOffset)
{
    isMousePressed_ = true;
    leftMousePressed_ = true;
    if (BetweenSelectedPosition(info.GetGlobalLocation())) {
        blockPress_ = true;
        return;
    }
    mouseStatus_ = MouseStatus::PRESSED;
    CHECK_NULL_VOID(paragraph_);
    auto start = paragraph_->GetGlyphIndexByCoordinate(textOffset);
    textSelector_.Update(start, start);
}

void TextPattern::HandleMouseLeftReleaseAction(const MouseInfo& info, const Offset& textOffset)
{
    if (blockPress_) {
        blockPress_ = false;
    }
    auto oldMouseStatus = mouseStatus_;
    mouseStatus_ = MouseStatus::RELEASED;
    if (isDoubleClick_) {
        isDoubleClick_ = false;
        isMousePressed_ = false;
        leftMousePressed_ = false;
        return;
    }
    if (oldMouseStatus != MouseStatus::MOVE && !IsDragging()) {
        HandleClickAISpanEvent(PointF(textOffset.GetX(), textOffset.GetY()));
        if (dataDetectorAdapter_->hasClickedAISpan_) {
            selectOverlay_->DisableMenu();
            isMousePressed_ = false;
            leftMousePressed_ = false;
            return;
        }
    }

    CHECK_NULL_VOID(paragraph_);
    auto start = textSelector_.baseOffset;
    auto end = textSelector_.destinationOffset;
    if (!IsSelected()) {
        start = -1;
        end = -1;
    }
    if (isMousePressed_ || oldMouseStatus == MouseStatus::MOVE) {
        HandleSelectionChange(start, end);
    }

    if (IsSelected() && oldMouseStatus == MouseStatus::MOVE && IsSelectedBindSelectionMenu()) {
        selectOverlay_->SetMouseMenuOffset(OffsetF(
            static_cast<float>(info.GetGlobalLocation().GetX()), static_cast<float>(info.GetGlobalLocation().GetY())));
        textResponseType_ = TextResponseType::SELECTED_BY_MOUSE;
        ShowSelectOverlay({ .animation = true });
    }
    isMousePressed_ = false;
    leftMousePressed_ = false;
}

void TextPattern::HandleMouseLeftMoveAction(const MouseInfo& info, const Offset& textOffset)
{
    if (blockPress_) {
        dragBoxes_ = GetTextBoxes();
        return;
    }
    if (isMousePressed_) {
        mouseStatus_ = MouseStatus::MOVE;
        CHECK_NULL_VOID(paragraph_);
        auto end = paragraph_->GetGlyphIndexByCoordinate(textOffset);
        HandleSelectionChange(textSelector_.baseOffset, end);
    }
}

void TextPattern::HandleMouseRightButton(const MouseInfo& info, const Offset& textOffset)
{
    if (info.GetAction() == MouseAction::RELEASE) {
        selectOverlay_->SetMouseMenuOffset(OffsetF(
            static_cast<float>(info.GetGlobalLocation().GetX()), static_cast<float>(info.GetGlobalLocation().GetY())));
        if (!BetweenSelectedPosition(info.GetGlobalLocation())) {
            HandleClickAISpanEvent(PointF(textOffset.GetX(), textOffset.GetY()));
            if (dataDetectorAdapter_->hasClickedAISpan_) {
                isMousePressed_ = false;
                return;
            }
        }

        CalculateHandleOffsetAndShowOverlay(true);
        if (selectOverlay_->SelectOverlayIsOn()) {
            CloseSelectOverlay(true);
        }
        textResponseType_ = TextResponseType::RIGHT_CLICK;
        if (!IsSelected()) {
            auto spanNode = DynamicCast<FrameNode>(GetChildByIndex(GetSelectionSpanItemIndex(info)));
            if (spanNode && spanNode->GetTag() == V2::IMAGE_ETS_TAG) {
                selectedType_ = TextSpanType::IMAGE;
            } else {
                selectedType_ = TextSpanType::TEXT;
            }
        }
        ShowSelectOverlay({ .animation = true });
        isMousePressed_ = false;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    } else if (info.GetAction() == MouseAction::PRESS) {
        isMousePressed_ = true;
        CloseSelectOverlay(true);
    }
}

void TextPattern::InitTouchEvent()
{
    CHECK_NULL_VOID(!touchEventInitialized_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);

    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->sourceType_ = info.GetSourceDevice();
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
    CHECK_NULL_VOID(!panEventInitialized_);
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandlePanStart(info);
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandlePanUpdate(info);
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
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
    auto pipelineContext = PipelineContext::GetCurrentContextSafely();
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
        std::vector<RectF> selectedRects;
        paragraph_->GetRectsForRange(textSelector_.GetTextStart(), textSelector_.GetTextEnd(), selectedRects);
        auto panOffset = OffsetF(offset.GetX(), offset.GetY()) - contentRect_.GetOffset() +
                         OffsetF(0.0f, std::min(baselineOffset_, 0.0f));
        for (const auto& selectedRect : selectedRects) {
            if (selectedRect.IsInRegion(PointF(panOffset.GetX(), panOffset.GetY()))) {
                return true;
            }
        }
    }
    return false;
}

void TextPattern::HandlePanUpdate(const GestureEvent& info)
{
    if (dragWindow_) {
        dragWindow_->TextDragWindowMove(info.GetOffsetX(), info.GetOffsetY());
    }
    return;
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

NG::DragDropInfo TextPattern::OnDragStart(const RefPtr<Ace::DragEvent>& event, const std::string& extraParams)
{
    DragDropInfo itemInfo;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, itemInfo);
    auto hub = host->GetEventHub<EventHub>();
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    auto selectStart = textSelector_.GetTextStart();
    auto selectEnd = textSelector_.GetTextEnd();
    recoverStart_ = selectStart;
    recoverEnd_ = selectEnd;
    auto textSelectInfo = GetSpansInfo(selectStart, selectEnd, GetSpansMethod::ONSELECT);
    dragResultObjects_ = textSelectInfo.GetSelection().resultObjects;
    ResetDragRecordSize(dragResultObjects_.empty() ? -1 : 1);
    status_ = Status::DRAGGING;
    if (dragResultObjects_.empty() || !gestureHub->GetIsTextDraggable()) {
        return itemInfo;
    }
    auto data = event->GetData();
    if (!data) {
        AddUdmfData(event);
    }
    CloseOperate();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    return itemInfo;
}

void TextPattern::AddUdmfTxtPreProcessor(const ResultObject src, ResultObject& result, bool isAppend)
{
    auto valueString = GetSelectedSpanText(StringUtils::ToWstring(src.valueString),
        src.offsetInSpan[RichEditorSpanRange::RANGESTART], src.offsetInSpan[RichEditorSpanRange::RANGEEND]);
    if (isAppend) {
        result.valueString = result.valueString + valueString;
    } else {
        result.valueString = valueString;
    }
}

void TextPattern::AddUdmfData(const RefPtr<Ace::DragEvent>& event)
{
    RefPtr<UnifiedData> unifiedData = UdmfClient::GetInstance()->CreateUnifiedData();
    std::list<ResultObject> finalResult;
    auto type = SelectSpanType::TYPESPAN;
    for (const auto& resultObj : dragResultObjects_) {
        if (finalResult.empty() || resultObj.type != SelectSpanType::TYPESPAN || type != SelectSpanType::TYPESPAN) {
            type = resultObj.type;
            finalResult.emplace_back(resultObj);
            if (resultObj.type == SelectSpanType::TYPESPAN) {
                AddUdmfTxtPreProcessor(resultObj, finalResult.back(), false);
            }
        } else {
            AddUdmfTxtPreProcessor(resultObj, finalResult.back(), true);
        }
    }
    auto resultProcessor = [unifiedData, weak = WeakClaim(this)](const ResultObject& result) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (result.type == SelectSpanType::TYPESPAN) {
            UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, result.valueString);
            return;
        }
        if (result.type == SelectSpanType::TYPEIMAGE) {
            if (result.valuePixelMap) {
                const uint8_t* pixels = result.valuePixelMap->GetPixels();
                CHECK_NULL_VOID(pixels);
                int32_t length = result.valuePixelMap->GetByteCount();
                std::vector<uint8_t> data(pixels, pixels + length);
                PixelMapRecordDetails details = { result.valuePixelMap->GetWidth(), result.valuePixelMap->GetHeight(),
                    result.valuePixelMap->GetPixelFormat(), result.valuePixelMap->GetAlphaType() };
                UdmfClient::GetInstance()->AddPixelMapRecord(unifiedData, data, details);
            } else {
                UdmfClient::GetInstance()->AddImageRecord(unifiedData, result.valueString);
            }
        }
    };
    for (const auto& resultObj : finalResult) {
        resultProcessor(resultObj);
    }
    event->SetData(unifiedData);
}

void TextPattern::CloseOperate()
{
    UpdateSpanItemDragStatus(dragResultObjects_, true);
    recoverDragResultObjects_ = dragResultObjects_;
    AceEngineExt::GetInstance().DragStartExt();
    CloseKeyboard(true);
    CloseSelectOverlay();
    ResetSelection();
}

DragDropInfo TextPattern::OnDragStartNoChild(const RefPtr<Ace::DragEvent>& event, const std::string& extraParams)
{
    auto weakPtr = WeakClaim(this);
    DragDropInfo itemInfo;
    auto pattern = weakPtr.Upgrade();
    auto host = pattern->GetHost();
    auto hub = host->GetEventHub<EventHub>();
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, itemInfo);
    if (!gestureHub->GetIsTextDraggable()) {
        return itemInfo;
    }
    auto layoutProperty = host->GetLayoutProperty<TextLayoutProperty>();
    pattern->status_ = Status::DRAGGING;
    pattern->contentMod_->ChangeDragStatus();
    pattern->showSelect_ = false;
    auto start = textSelector_.GetTextStart();
    pattern->recoverStart_ = start;
    auto end = textSelector_.GetTextEnd();
    pattern->recoverEnd_ = end;
    auto beforeStr = GetSelectedText(0, start);
    auto selectedStr = GetSelectedText(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    auto afterStr = GetSelectedText(end, GetWideText().length());
    pattern->dragContents_ = { beforeStr, selectedStr, afterStr };

    itemInfo.extraInfo = selectedStr;
    RefPtr<UnifiedData> unifiedData = UdmfClient::GetInstance()->CreateUnifiedData();
    UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);
    host->MarkDirtyNode(layoutProperty->GetMaxLinesValue(Infinity<float>()) <= 1 ? PROPERTY_UPDATE_MEASURE_SELF
                                                                                 : PROPERTY_UPDATE_MEASURE);

    CloseSelectOverlay();
    ResetSelection();
    return itemInfo;
}

void TextPattern::UpdateSpanItemDragStatus(const std::list<ResultObject>& resultObjects, bool isDragging)
{
    if (resultObjects.empty()) {
        return;
    }
    auto dragStatusUpdateAction = [weakPtr = WeakClaim(this), isDragging](const ResultObject& resultObj) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->spans_.empty()) {
            return;
        }
        auto it = pattern->spans_.begin();
        if (resultObj.spanPosition.spanIndex >= static_cast<int32_t>(pattern->spans_.size())) {
            std::advance(it, pattern->spans_.size() - 1);
            TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "resultObj.spanPosition.spanIndex is larger than spans size.");
        } else {
            std::advance(it, resultObj.spanPosition.spanIndex);
        }
        auto spanItem = *it;
        CHECK_NULL_VOID(spanItem);
        if (resultObj.type == SelectSpanType::TYPESPAN) {
            if (isDragging) {
                spanItem->StartDrag(resultObj.offsetInSpan[RichEditorSpanRange::RANGESTART],
                    resultObj.offsetInSpan[RichEditorSpanRange::RANGEEND]);
                pattern->dragSpanItems_.emplace_back(spanItem);
            } else {
                spanItem->EndDrag();
            }
            return;
        }

        if (resultObj.type == SelectSpanType::TYPEIMAGE) {
            auto imageNode = DynamicCast<FrameNode>(pattern->GetChildByIndex(resultObj.spanPosition.spanIndex));
            CHECK_NULL_VOID(imageNode);
            auto renderContext = imageNode->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateOpacity(isDragging ? (double)DRAGGED_TEXT_OPACITY / 255 : 1);
            imageNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    };
    for (const auto& resultObj : resultObjects) {
        dragStatusUpdateAction(resultObj);
    }
}

void TextPattern::OnDragEnd(const RefPtr<Ace::DragEvent>& event)
{
    ResetDragRecordSize(-1);
    auto wk = WeakClaim(this);
    auto pattern = wk.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (status_ == Status::DRAGGING) {
        status_ = Status::NONE;
    }
    dragSpanItems_.clear();
    if (dragResultObjects_.empty()) {
        return;
    }
    UpdateSpanItemDragStatus(dragResultObjects_, false);
    dragResultObjects_.clear();
    if (event && event->GetResult() != DragRet::DRAG_SUCCESS) {
        HandleSelectionChange(recoverStart_, recoverEnd_);
        isShowMenu_ = false;
        if (GetCurrentDragTool() == SourceTool::FINGER) {
            CalculateHandleOffsetAndShowOverlay();
            ShowSelectOverlay({ .menuIsShow = false });
        }
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TextPattern::OnDragEndNoChild(const RefPtr<Ace::DragEvent>& event)
{
    auto wk = WeakClaim(this);
    auto pattern = wk.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    if (pattern->status_ == Status::DRAGGING) {
        pattern->status_ = Status::NONE;
        pattern->MarkContentChange();
        pattern->contentMod_->ChangeDragStatus();
        if (event && event->GetResult() != DragRet::DRAG_SUCCESS) {
            HandleSelectionChange(recoverStart_, recoverEnd_);
            isShowMenu_ = false;
            if (GetCurrentDragTool() == SourceTool::FINGER) {
                CalculateHandleOffsetAndShowOverlay();
                ShowSelectOverlay({ .menuIsShow = false });
            }
        }
        auto layoutProperty = host->GetLayoutProperty<TextLayoutProperty>();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void TextPattern::OnDragMove(const RefPtr<Ace::DragEvent>& event)
{
    auto weakPtr = WeakClaim(this);
    auto pattern = weakPtr.Upgrade();
    if (pattern->status_ == Status::DRAGGING) {
        CloseSelectOverlay();
        pattern->showSelect_ = false;
    }
}

void TextPattern::InitDragEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->InitDragDropEvent();
    gestureHub->SetTextDraggable(true);
    gestureHub->SetThumbnailCallback(GetThumbnailCallback());
    auto onDragStart = [weakPtr = WeakClaim(this)](
                           const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) -> DragDropInfo {
        NG::DragDropInfo itemInfo;
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_RETURN(pattern, itemInfo);
        auto eventHub = pattern->GetEventHub<EventHub>();
        CHECK_NULL_RETURN(eventHub, itemInfo);
        pattern->SetCurrentDragTool(event->GetSourceTool());
        if (pattern->spans_.empty() || pattern->isSpanStringMode_) {
            return pattern->OnDragStartNoChild(event, extraParams);
        }
        return pattern->OnDragStart(event, extraParams);
    };
    eventHub->SetDefaultOnDragStart(std::move(onDragStart));
    auto onDragMove = [weakPtr = WeakClaim(this)](
                          const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) {
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnDragMove(event);
    };
    eventHub->SetOnDragMove(std::move(onDragMove));
    auto onDragEnd = [weakPtr = WeakClaim(this), scopeId = Container::CurrentId()](
                         const RefPtr<OHOS::Ace::DragEvent>& event) {
        ContainerScope scope(scopeId);
        auto pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->showSelect_ = true;
        if (pattern->spans_.empty()) {
            pattern->OnDragEndNoChild(event);
        } else {
            pattern->OnDragEnd(event);
        }
    };
    eventHub->SetOnDragEnd(std::move(onDragEnd));
}

std::function<void(Offset)> TextPattern::GetThumbnailCallback()
{
    return [wk = WeakClaim(this)](const Offset& point) {
        auto pattern = wk.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->BetweenSelectedPosition(point)) {
            auto children = pattern->GetAllChildren();
            std::list<RefPtr<FrameNode>> imageChildren;
            for (const auto& child : children) {
                auto node = DynamicCast<FrameNode>(child);
                if (!node) {
                    continue;
                }
                auto image = node->GetPattern<ImagePattern>();
                if (image) {
                    imageChildren.emplace_back(node);
                }
            }
            RichEditorDragInfo info;
            info.firstHandle = pattern->textSelector_.firstHandle;
            info.secondHandle = pattern->textSelector_.secondHandle;
            pattern->dragNode_ = RichEditorDragPattern::CreateDragNode(pattern->GetHost(), imageChildren, info);
            FrameNode::ProcessOffscreenNode(pattern->dragNode_);
        }
    };
}

const std::list<RefPtr<UINode>>& TextPattern::GetAllChildren() const
{
    childNodes_.clear();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, childNodes_);
    const auto& children = host->GetChildren();
    for (const auto& child : children) {
        if (child->GetTag() == V2::CONTAINER_SPAN_ETS_TAG) {
            auto spanChildren = child->GetChildren();
            childNodes_.insert(childNodes_.end(), spanChildren.begin(), spanChildren.end());
        } else if (!child->GetChildren().empty()) {
            std::vector<RefPtr<UINode>> res;
            UINode::DFSAllChild(child, res);
            childNodes_.insert(childNodes_.end(), res.begin(), res.end());
        } else {
            childNodes_.push_back(child);
        }
    }
    return childNodes_;
}

std::string TextPattern::GetSelectedSpanText(std::wstring value, int32_t start, int32_t end) const
{
    if (start < 0 || end > static_cast<int32_t>(value.length()) || start >= end) {
        return "";
    }
    auto min = std::min(start, end);
    auto max = std::max(start, end);

    return StringUtils::ToString(value.substr(min, max - min));
}

TextStyleResult TextPattern::GetTextStyleObject(const RefPtr<SpanNode>& node)
{
    TextStyleResult textStyle;
    textStyle.fontColor = node->GetTextColorValue(Color::BLACK).ColorToString();
    textStyle.fontSize = node->GetFontSizeValue(Dimension(16.0f, DimensionUnit::VP)).ConvertToVp();
    textStyle.fontStyle = static_cast<int32_t>(node->GetItalicFontStyleValue(OHOS::Ace::FontStyle::NORMAL));
    textStyle.fontWeight = static_cast<int32_t>(node->GetFontWeightValue(FontWeight::NORMAL));
    std::string fontFamilyValue;
    const std::vector<std::string> defaultFontFamily = { "HarmonyOS Sans" };
    auto fontFamily = node->GetFontFamilyValue(defaultFontFamily);
    for (const auto& str : fontFamily) {
        fontFamilyValue += str;
        fontFamilyValue += ",";
    }
    fontFamilyValue = fontFamilyValue.substr(0, fontFamilyValue.size() - 1);
    textStyle.fontFamily = !fontFamilyValue.empty() ? fontFamilyValue : defaultFontFamily.front();
    textStyle.decorationType = static_cast<int32_t>(node->GetTextDecorationValue(TextDecoration::NONE));
    textStyle.decorationColor = node->GetTextDecorationColorValue(Color::BLACK).ColorToString();
    textStyle.textAlign = static_cast<int32_t>(node->GetTextAlignValue(TextAlign::START));
    auto lm = node->GetLeadingMarginValue({});
    textStyle.lineHeight = node->GetLineHeightValue(Dimension()).ConvertToVp();
    textStyle.letterSpacing = node->GetLetterSpacingValue(Dimension()).ConvertToVp();
    textStyle.fontFeature = node->GetFontFeatureValue(ParseFontFeatureSettings("\"pnum\" 1"));
    textStyle.leadingMarginSize[RichEditorLeadingRange::LEADING_START] = Dimension(lm.size.Width()).ConvertToVp();
    textStyle.leadingMarginSize[RichEditorLeadingRange::LEADING_END] = Dimension(lm.size.Height()).ConvertToVp();
    textStyle.wordBreak = static_cast<int32_t>(node->GetWordBreakValue(WordBreak::BREAK_WORD));
    return textStyle;
}

RefPtr<UINode> TextPattern::GetChildByIndex(int32_t index) const
{
    const auto& children = GetAllChildren();
    int32_t size = static_cast<int32_t>(children.size());
    if (index < 0 || index >= size) {
        return nullptr;
    }
    auto pos = children.begin();
    std::advance(pos, index);
    return *pos;
}

RefPtr<SpanItem> TextPattern::GetSpanItemByIndex(int32_t index) const
{
    int32_t size = static_cast<int32_t>(spans_.size());
    if (index < 0 || index >= size) {
        return nullptr;
    }
    auto pos = spans_.begin();
    std::advance(pos, index);
    return *pos;
}

ResultObject TextPattern::GetTextResultObject(RefPtr<UINode> uinode, int32_t index, int32_t start, int32_t end)
{
    bool selectFlag = false;
    ResultObject resultObject;
    if (!DynamicCast<SpanNode>(uinode)) {
        return resultObject;
    }
    auto spanItem = DynamicCast<SpanNode>(uinode)->GetSpanItem();
    int32_t itemLength = static_cast<int32_t>(StringUtils::ToWstring(spanItem->content).length());
    int32_t endPosition = std::min(GetTextContentLength(), spanItem->position);
    int32_t startPosition = endPosition - itemLength;

    if (startPosition >= start && endPosition <= end) {
        selectFlag = true;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGESTART] = 0;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGEEND] = itemLength;
    } else if (startPosition < start && endPosition <= end && endPosition > start) {
        selectFlag = true;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGESTART] = start - startPosition;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGEEND] = itemLength;
    } else if (startPosition >= start && startPosition < end && endPosition >= end) {
        selectFlag = true;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGESTART] = 0;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGEEND] = end - startPosition;
    } else if (startPosition <= start && endPosition >= end) {
        selectFlag = true;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGESTART] = start - startPosition;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGEEND] = end - startPosition;
    }
    if (selectFlag) {
        resultObject.spanPosition.spanIndex = index;
        resultObject.spanPosition.spanRange[RichEditorSpanRange::RANGESTART] = startPosition;
        resultObject.spanPosition.spanRange[RichEditorSpanRange::RANGEEND] = endPosition;
        resultObject.type = SelectSpanType::TYPESPAN;
        resultObject.valueString = spanItem->content;
        auto spanNode = DynamicCast<SpanNode>(uinode);
        resultObject.textStyle = GetTextStyleObject(spanNode);
    }
    return resultObject;
}

ResultObject TextPattern::GetSymbolSpanResultObject(RefPtr<UINode> uinode, int32_t index, int32_t start, int32_t end)
{
    bool selectFlag = false;
    ResultObject resultObject;
    resultObject.isDraggable = false;
    if (!DynamicCast<SpanNode>(uinode)) {
        return resultObject;
    }
    auto spanItem = DynamicCast<SpanNode>(uinode)->GetSpanItem();
    int32_t itemLength = static_cast<int32_t>(StringUtils::ToWstring(spanItem->content).length());
    int32_t endPosition = std::min(GetTextContentLength(), spanItem->position);
    int32_t startPosition = endPosition - itemLength;

    if (startPosition >= start && endPosition <= end) {
        selectFlag = true;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGESTART] = 0;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGEEND] = itemLength;
    } else if (startPosition < start && endPosition <= end && endPosition > start) {
        selectFlag = true;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGESTART] = start - startPosition;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGEEND] = itemLength;
    } else if (startPosition >= start && startPosition < end && endPosition >= end) {
        selectFlag = true;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGESTART] = 0;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGEEND] = end - startPosition;
    } else if (startPosition <= start && endPosition >= end) {
        selectFlag = true;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGESTART] = start - startPosition;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGEEND] = end - startPosition;
    }
    if (selectFlag) {
        resultObject.valueResource = spanItem->GetResourceObject();
        resultObject.spanPosition.spanIndex = index;
        resultObject.spanPosition.spanRange[RichEditorSpanRange::RANGESTART] = startPosition;
        resultObject.spanPosition.spanRange[RichEditorSpanRange::RANGEEND] = endPosition;
        resultObject.type = SelectSpanType::TYPESYMBOLSPAN;
        resultObject.valueString = std::to_string(spanItem->unicode);
        auto spanNode = DynamicCast<SpanNode>(uinode);
        resultObject.symbolSpanStyle = GetSymbolSpanStyleObject(spanNode);
    }
    return resultObject;
}

SymbolSpanStyle TextPattern::GetSymbolSpanStyleObject(const RefPtr<SpanNode>& node)
{
    SymbolSpanStyle symbolSpanStyle;
    std::string symbolColorValue;
    auto symbolColors = node->GetSymbolColorList();
    for (const auto& color : *symbolColors) {
        symbolColorValue += color.ColorToString() + ",";
    }
    symbolColorValue = symbolColorValue.substr(0, symbolColorValue.size() - 1);
    symbolSpanStyle.symbolColor = !symbolColorValue.empty() ? symbolColorValue : SYMBOL_COLOR;
    symbolSpanStyle.fontSize = node->GetFontSizeValue(Dimension(DIMENSION_VALUE, DimensionUnit::VP)).ConvertToVp();
    symbolSpanStyle.fontWeight = static_cast<int32_t>(node->GetFontWeightValue(FontWeight::NORMAL));
    symbolSpanStyle.renderingStrategy = node->GetSymbolRenderingStrategyValue(0);
    symbolSpanStyle.effectStrategy = node->GetSymbolEffectStrategyValue(0);
    return symbolSpanStyle;
}

ResultObject TextPattern::GetImageResultObject(RefPtr<UINode> uinode, int32_t index, int32_t start, int32_t end)
{
    int32_t itemLength = 1;
    ResultObject resultObject;
    if (!DynamicCast<FrameNode>(uinode) || !GetSpanItemByIndex(index)) {
        return resultObject;
    }
    int32_t endPosition = std::min(GetTextContentLength(), GetSpanItemByIndex(index)->position);
    int32_t startPosition = endPosition - itemLength;
    if ((start <= startPosition) && (end >= endPosition)) {
        auto imageNode = DynamicCast<FrameNode>(uinode);
        auto imageLayoutProperty = DynamicCast<ImageLayoutProperty>(imageNode->GetLayoutProperty());
        resultObject.spanPosition.spanIndex = index;
        resultObject.spanPosition.spanRange[RichEditorSpanRange::RANGESTART] = startPosition;
        resultObject.spanPosition.spanRange[RichEditorSpanRange::RANGEEND] = endPosition;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGESTART] = 0;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGEEND] = itemLength;
        resultObject.type = SelectSpanType::TYPEIMAGE;
        if (!imageLayoutProperty->GetImageSourceInfo()->GetPixmap()) {
            resultObject.valueString = imageLayoutProperty->GetImageSourceInfo()->GetSrc();
        } else {
            resultObject.valuePixelMap = imageLayoutProperty->GetImageSourceInfo()->GetPixmap();
        }
        auto geometryNode = imageNode->GetGeometryNode();
        resultObject.imageStyle.size[RichEditorImageSize::SIZEWIDTH] = geometryNode->GetMarginFrameSize().Width();
        resultObject.imageStyle.size[RichEditorImageSize::SIZEHEIGHT] = geometryNode->GetMarginFrameSize().Height();
        if (imageLayoutProperty->HasImageFit()) {
            resultObject.imageStyle.objectFit = static_cast<int32_t>(imageLayoutProperty->GetImageFitValue());
        }
        if (imageLayoutProperty->HasVerticalAlign()) {
            resultObject.imageStyle.verticalAlign = static_cast<int32_t>(imageLayoutProperty->GetVerticalAlignValue());
        }
        if (imageLayoutProperty->GetMarginProperty()) {
            resultObject.imageStyle.margin = imageLayoutProperty->GetMarginProperty()->ToString();
        }
        auto imageRenderCtx = imageNode->GetRenderContext();
        if (imageRenderCtx->GetBorderRadius()) {
            BorderRadiusProperty brp;
            auto jsonObject = JsonUtil::Create(true);
            auto jsonBorder = JsonUtil::Create(true);
            InspectorFilter emptyFilter;
            imageRenderCtx->GetBorderRadiusValue(brp).ToJsonValue(jsonObject, jsonBorder, emptyFilter);
            resultObject.imageStyle.borderRadius = jsonObject->GetValue("borderRadius")->IsObject()
                                                       ? jsonObject->GetValue("borderRadius")->ToString()
                                                       : jsonObject->GetString("borderRadius");
        }
    }
    return resultObject;
}

// ===========================================================
// TextDragBase implementations
float TextPattern::GetLineHeight() const
{
    std::vector<RectF> selectedRects;
    paragraph_->GetRectsForRange(textSelector_.GetTextStart(), textSelector_.GetTextEnd(), selectedRects);
    CHECK_NULL_RETURN(selectedRects.size(), {});
    return selectedRects.front().Height();
}

std::vector<RectF> TextPattern::GetTextBoxes()
{
    std::vector<RectF> selectedRects;
    paragraph_->GetRectsForRange(textSelector_.GetTextStart(), textSelector_.GetTextEnd(), selectedRects);
    return selectedRects;
}

OffsetF TextPattern::GetParentGlobalOffset() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, {});
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipeline, {});
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    return host->GetPaintRectOffset() - rootOffset;
}

void TextPattern::CreateHandles()
{
    if (IsDragging()) {
        TAG_LOGI(AceLogTag::ACE_TEXT, "do not show handles when dragging");
        return;
    }
    ShowSelectOverlay();
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
        paragraph_.Reset();
    }

    if (!(PipelineContext::GetCurrentContextSafely() &&
            PipelineContext::GetCurrentContextSafely()->GetMinPlatformVersion() > API_PROTEXTION_GREATER_NINE)) {
        bool shouldClipToContent =
            textLayoutProperty->GetTextOverflow().value_or(TextOverflow::CLIP) == TextOverflow::CLIP;
        host->GetRenderContext()->SetClipToFrame(shouldClipToContent);
    }

    if (textLayoutProperty->GetTextOverflowValue(TextOverflow::CLIP) == TextOverflow::MARQUEE) {
        if (!renderContext->GetClipEdge().has_value()) {
            renderContext->UpdateClipEdge(true);
        }
        CloseSelectOverlay();
        ResetSelection();
        copyOption_ = CopyOptions::None;
    } else {
        copyOption_ = textLayoutProperty->GetCopyOption().value_or(CopyOptions::None);
    }
    if (GetAllChildren().empty()) {
        auto obscuredReasons = renderContext->GetObscured().value_or(std::vector<ObscuredReasons>());
        bool ifHaveObscured = std::any_of(obscuredReasons.begin(), obscuredReasons.end(),
            [](const auto& reason) { return reason == ObscuredReasons::PLACEHOLDER; });
        if (ifHaveObscured && !isSpanStringMode_) {
            CloseSelectOverlay();
            ResetSelection();
            copyOption_ = CopyOptions::None;
        }

        std::string textCache = textForDisplay_;
        textForDisplay_ = textLayoutProperty->GetContent().value_or("");
        if (textCache != textForDisplay_) {
            host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE, textCache, textForDisplay_);
            dataDetectorAdapter_->aiDetectInitialized_ = false;
            CloseSelectOverlay();
            ResetSelection();
        }
        if (CanStartAITask() && !dataDetectorAdapter_->aiDetectInitialized_) {
            dataDetectorAdapter_->textForAI_ = textForDisplay_;
            dataDetectorAdapter_->StartAITask();
        }
    }

    auto gestureEventHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    if (copyOption_ != CopyOptions::None) {
        auto context = PipelineContext::GetCurrentContextSafely();
        CHECK_NULL_VOID(context);
        if (!clipboard_ && context) {
            clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(context->GetTaskExecutor());
        }
        InitLongPressEvent(gestureEventHub);
        if (host->IsDraggable()) {
            InitDragEvent();
        }
        InitMouseEvent();
        InitTouchEvent();
        SetAccessibilityAction();
    } else {
        if (host->IsDraggable() || gestureEventHub->GetTextDraggable()) {
            gestureEventHub->SetTextDraggable(false);
        }
    }
    if (onClick_ || copyOption_ != CopyOptions::None) {
        InitClickEvent(gestureEventHub);
    }
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    bool enabledCache = eventHub->IsEnabled();
    if (textDetectEnable_ && enabledCache != enabled_) {
        enabled_ = enabledCache;
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void TextPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    json->PutExtAttr("enableDataDetector", textDetectEnable_ ? "true" : "false", filter);
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("types", "");
    json->PutExtAttr("dataDetectorConfig", jsonValue->ToString().c_str(), filter);
    const auto& selector = GetTextSelector();
    auto result = "[" + std::to_string(selector.GetTextStart()) + "," + std::to_string(selector.GetTextEnd()) + "]";
    json->PutExtAttr("selection", result.c_str(), filter);
}

void TextPattern::OnAfterModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inspectorId = host->GetInspectorId().value_or("");
    if (!inspectorId.empty()) {
        auto prop = host->GetAccessibilityProperty<NG::AccessibilityProperty>();
        Recorder::NodeDataCache::Get().PutString(host, inspectorId, prop->GetText());
    }
}

void TextPattern::ActSetSelection(int32_t start, int32_t end)
{
    if (start == -1 && end == -1) {
        ResetSelection();
        CloseSelectOverlay();
        return;
    }
    int32_t min = 0;
    int32_t textSize = static_cast<int32_t>(GetWideText().length()) + placeholderCount_;
    start = start < min ? min : start;
    end = end < min ? min : end;
    start = start > textSize ? textSize : start;
    end = end > textSize ? textSize : end;
    if (start >= end) {
        FireOnSelectionChange(-1, -1);
        return;
    }
    HandleSelectionChange(start, end);
    parentGlobalOffset_ = GetParentGlobalOffset();
    CalculateHandleOffsetAndShowOverlay();
    if (textSelector_.firstHandle == textSelector_.secondHandle) {
        ResetSelection();
        CloseSelectOverlay();
        return;
    }
    ShowSelectOverlay();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

// Deprecated: Use the TextSelectOverlay::ProcessOverlay() instead.
// It is currently used by RichEditorPattern.
void TextPattern::UpdateSelectOverlayOrCreate(SelectOverlayInfo& selectInfo, bool animation)
{
    if (selectOverlayProxy_ && !selectOverlayProxy_->IsClosed()) {
        SelectHandleInfo firstHandleInfo;
        firstHandleInfo.paintRect = textSelector_.firstHandle;
        CheckHandles(firstHandleInfo);

        SelectHandleInfo secondHandleInfo;
        secondHandleInfo.paintRect = textSelector_.secondHandle;
        CheckHandles(secondHandleInfo);

        auto start = textSelector_.GetTextStart();
        auto end = textSelector_.GetTextEnd();
        selectOverlayProxy_->SetSelectInfo(GetSelectedText(start, end));
        if (selectInfo.isNewAvoid) {
            selectOverlayProxy_->UpdateSelectArea(selectInfo.selectArea);
        }
        selectOverlayProxy_->UpdateFirstAndSecondHandleInfo(firstHandleInfo, secondHandleInfo);
        selectOverlayProxy_->ShowOrHiddenMenu(!firstHandleInfo.isShow && !secondHandleInfo.isShow);
    } else {
        auto pipeline = PipelineContext::GetCurrentContextSafely();
        CHECK_NULL_VOID(pipeline);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        pipeline->AddOnAreaChangeNode(host->GetId());
        selectInfo.callerFrameNode = GetHost();
        selectInfo.hitTestMode = HitTestMode::HTMDEFAULT;
        if (!selectInfo.isUsingMouse) {
            CheckHandles(selectInfo.firstHandle);
            CheckHandles(selectInfo.secondHandle);
        }
        selectOverlayProxy_ =
            pipeline->GetSelectOverlayManager()->CreateAndShowSelectOverlay(selectInfo, WeakClaim(this), animation);
        CHECK_NULL_VOID(selectOverlayProxy_);
        auto start = textSelector_.GetTextStart();
        auto end = textSelector_.GetTextEnd();
        selectOverlayProxy_->SetSelectInfo(GetSelectedText(start, end));
    }
}

bool TextPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }

    contentRect_ = dirty->GetGeometryNode()->GetContentRect();

    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto textLayoutAlgorithm = DynamicCast<TextLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(textLayoutAlgorithm, false);
    auto&& paragraph = textLayoutAlgorithm->GetParagraph();
    if (!paragraph) {
        return false;
    }
    paragraph_ = paragraph;
    baselineOffset_ = textLayoutAlgorithm->GetBaselineOffset();
    contentOffset_ = dirty->GetGeometryNode()->GetContentOffset();
    textStyle_ = textLayoutAlgorithm->GetTextStyle();
    ProcessOverlayAfterLayout();
    return true;
}

void TextPattern::ProcessOverlayAfterLayout()
{
    if (selectOverlay_->SelectOverlayIsOn()) {
        CalculateHandleOffsetAndShowOverlay();
        selectOverlay_->UpdateAllHandlesOffset();
    }
}

void TextPattern::PreCreateLayoutWrapper()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    // mark content dirty
    if (contentMod_) {
        contentMod_->ContentChange();
    }

    auto paintProperty = GetPaintProperty<PaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto flag = paintProperty->GetPropertyChangeFlag();
    auto textLayoutProperty = GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto layoutFlag = textLayoutProperty->GetPropertyChangeFlag();
    if (!CheckNeedMeasure(flag) && !CheckNeedMeasure(layoutFlag)) {
        return;
    }

    spans_.clear();

    // When dirty areas are marked because of child node changes, the text rendering node tree is reset.
    const auto& children = host->GetChildren();
    if (children.empty()) {
        placeholderCount_ = 0;
        return;
    }

    // Depth-first iterates through all host's child nodes to collect the SpanNode object, building a text rendering
    // tree.
    std::stack<SpanNodeInfo> nodes;
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        nodes.push({ .node = *iter });
    }

    InitSpanItem(nodes);
}

void TextPattern::InitSpanItem(std::stack<SpanNodeInfo> nodes)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::string textCache;
    std::string textForAICache;
    int32_t oldPlaceholderCount = placeholderCount_;
    placeholderCount_ = 0;
    if (!nodes.empty()) {
        textCache = textForDisplay_;
        textForAICache = dataDetectorAdapter_->textForAI_;
        textForDisplay_.clear();
        dataDetectorAdapter_->textForAI_.clear();
    }

    bool isSpanHasClick = false;
    CollectSpanNodes(nodes, isSpanHasClick);
    if (oldPlaceholderCount != placeholderCount_) {
        CloseSelectOverlay();
        ResetSelection();
    }

    if (textCache != textForDisplay_) {
        host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE, textCache, textForDisplay_);
        dataDetectorAdapter_->aiDetectInitialized_ = false;
        OnAfterModifyDone();
        for (const auto& item : spans_) {
            if (item->inspectId.empty()) {
                continue;
            }
            Recorder::NodeDataCache::Get().PutString(host, item->inspectId, item->content);
        }
        CloseSelectOverlay();
        ResetSelection();
    }
    if (isSpanHasClick) {
        auto gestureEventHub = host->GetOrCreateGestureEventHub();
        InitClickEvent(gestureEventHub);
    }
    if (CanStartAITask() && !dataDetectorAdapter_->aiDetectInitialized_) {
        dataDetectorAdapter_->StartAITask();
    }
}

void TextPattern::BeforeCreateLayoutWrapper()
{
    if (!isSpanStringMode_) {
        PreCreateLayoutWrapper();
    } else {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        textForDisplay_.clear();
        host->Clean();
        for (const auto& span : spans_) {
            textForDisplay_ += span->content;
            if (span->onClick) {
                auto gestureEventHub = host->GetOrCreateGestureEventHub();
                InitClickEvent(gestureEventHub);
            }
            if (span->onLongPress) {
                auto gestureEventHub = host->GetOrCreateGestureEventHub();
                InitLongPressEvent(gestureEventHub);
            }
        }
        if (dataDetectorAdapter_->textForAI_ != textForDisplay_) {
            dataDetectorAdapter_->textForAI_ = textForDisplay_;
            dataDetectorAdapter_->aiDetectInitialized_ = false;
        }
        if (CanStartAITask() && !dataDetectorAdapter_->aiDetectInitialized_) {
            dataDetectorAdapter_->StartAITask();
        }
        // mark content dirty
        if (contentMod_) {
            contentMod_->ContentChange();
        }
    }
}

void TextPattern::CollectSpanNodes(std::stack<SpanNodeInfo> nodes, bool& isSpanHasClick)
{
    while (!nodes.empty()) {
        auto current = nodes.top();
        nodes.pop();
        // TODO: Add the judgment of display.
        if (!current.node) {
            continue;
        }
        UpdateContainerChildren(current.containerSpanNode, current.node);
        auto spanNode = DynamicCast<SpanNode>(current.node);
        auto tag = current.node->GetTag();
        if (spanNode && tag == V2::SYMBOL_SPAN_ETS_TAG) {
            spanNode->CleanSpanItemChildren();
            UpdateChildProperty(spanNode);
            spanNode->MountToParagraph();
            textForDisplay_.append(StringUtils::Str16ToStr8(SYMBOL_TRANS));
        } else if (spanNode && tag != V2::PLACEHOLDER_SPAN_ETS_TAG) {
            spanNode->CleanSpanItemChildren();
            UpdateChildProperty(spanNode);
            spanNode->MountToParagraph();
            textForDisplay_.append(spanNode->GetSpanItem()->content);
            dataDetectorAdapter_->textForAI_.append(spanNode->GetSpanItem()->content);
            if (spanNode->GetSpanItem()->onClick) {
                isSpanHasClick = true;
            }
        } else if (tag == V2::IMAGE_ETS_TAG || tag == V2::PLACEHOLDER_SPAN_ETS_TAG) {
            placeholderCount_++;
            AddChildSpanItem(current.node);
            dataDetectorAdapter_->textForAI_.append("\n");
            auto imageNode = DynamicCast<FrameNode>(current.node);
            if (!imageNode) {
                continue;
            }
            auto focus_hub = imageNode->GetOrCreateFocusHub();
            if (focus_hub && focus_hub->GetOnClickCallback()) {
                isSpanHasClick = true;
            }
        }
        if (tag == V2::PLACEHOLDER_SPAN_ETS_TAG) {
            continue;
        }
        auto containerSpanNode = tag == V2::CONTAINER_SPAN_ETS_TAG ? current.node : current.containerSpanNode;
        const auto& nextChildren = current.node->GetChildren();
        for (auto iter = nextChildren.rbegin(); iter != nextChildren.rend(); ++iter) {
            nodes.push({ .node = *iter, .containerSpanNode = containerSpanNode });
        }
    }
}

void TextPattern::UpdateContainerChildren(const RefPtr<UINode>& parentNode, const RefPtr<UINode>& child)
{
    CHECK_NULL_VOID(child);
    auto parent = DynamicCast<ContainerSpanNode>(parentNode);
    CHECK_NULL_VOID(parent);
    auto baseSpan = DynamicCast<BaseSpan>(child);
    if (baseSpan) {
        if (baseSpan->HasTextBackgroundStyle()) {
            return;
        }
        baseSpan->UpdateTextBackgroundFromParent(parent->GetTextBackgroundStyle());
        return;
    }
    if (child->GetTag() == V2::IMAGE_ETS_TAG) {
        auto imageNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(imageNode);
        auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        if (imageLayoutProperty->GetHasPlaceHolderStyleValue(false)) {
            return;
        }
        if (parent->GetTextBackgroundStyle().has_value()) {
            imageLayoutProperty->UpdatePlaceHolderStyle(parent->GetTextBackgroundStyle().value());
        }
    }
}

void TextPattern::GetGlobalOffset(Offset& offset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContextSafely();
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
        if (textDetectEnable_) {
            dataDetectorAdapter_->aiDetectDelayTask_.Cancel();
        }
    } else {
        if (CanStartAITask()) {
            dataDetectorAdapter_->StartAITask();
        }
    }
}

void TextPattern::InitSurfaceChangedCallback()
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
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
        UpdateSurfaceChangedCallbackId(callbackId);
    }
}

void TextPattern::HandleSurfaceChanged(int32_t newWidth, int32_t newHeight, int32_t prevWidth, int32_t prevHeight)
{
    if (newWidth == prevWidth && newHeight == prevHeight) {
        return;
    }
    CHECK_NULL_VOID(selectOverlay_->SelectOverlayIsOn());
    if (selectOverlay_->IsShowMouseMenu()) {
        CloseSelectOverlay();
    } else {
        auto context = PipelineContext::GetCurrentContextSafely();
        if (context) {
            context->AddAfterLayoutTask([weak = WeakClaim(this)]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->CalculateHandleOffsetAndShowOverlay();
                pattern->ShowSelectOverlay({ .menuIsShow = false });
            });
        }
    }
}

void TextPattern::InitSurfacePositionChangedCallback()
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    if (!HasSurfacePositionChangedCallback()) {
        auto callbackId =
            pipeline->RegisterSurfacePositionChangedCallback([weak = WeakClaim(this)](int32_t posX, int32_t posY) {
                auto pattern = weak.Upgrade();
                if (pattern) {
                    pattern->HandleSurfacePositionChanged(posX, posY);
                }
            });
        UpdateSurfacePositionChangedCallbackId(callbackId);
    }
}

void TextPattern::AddChildSpanItem(const RefPtr<UINode>& child)
{
    CHECK_NULL_VOID(child);
    auto chidNode = DynamicCast<FrameNode>(child);
    if (chidNode && chidNode->GetLayoutProperty() && chidNode->GetLayoutProperty()->IsOverlayNode()) {
        return;
    }

    if (child->GetTag() == V2::SPAN_ETS_TAG || child->GetTag() == V2::SYMBOL_SPAN_ETS_TAG) {
        auto spanNode = DynamicCast<SpanNode>(child);
        if (spanNode) {
            spans_.emplace_back(spanNode->GetSpanItem());
        }
    } else if (child->GetTag() == V2::IMAGE_ETS_TAG) {
        auto imageSpanNode = DynamicCast<ImageSpanNode>(child);
        if (imageSpanNode) {
            spans_.emplace_back(imageSpanNode->GetSpanItem());
            spans_.back()->imageNodeId = imageSpanNode->GetId();
            return;
        }
        auto imageNode = DynamicCast<FrameNode>(child);
        if (imageNode) {
            auto imageSpanItem = MakeRefPtr<ImageSpanItem>();
            imageSpanItem->imageNodeId = imageNode->GetId();
            imageSpanItem->UpdatePlaceholderBackgroundStyle(imageNode);
            auto focus_hub = imageNode->GetOrCreateFocusHub();
            CHECK_NULL_VOID(focus_hub);
            auto clickCall = focus_hub->GetOnClickCallback();
            if (clickCall) {
                imageSpanItem->SetOnClickEvent(std::move(clickCall));
            }
            spans_.emplace_back(imageSpanItem);
            auto gesture = imageNode->GetOrCreateGestureEventHub();
            CHECK_NULL_VOID(gesture);
            gesture->SetHitTestMode(HitTestMode::HTMNONE);

            return;
        }
    } else if (child->GetTag() == V2::PLACEHOLDER_SPAN_ETS_TAG) {
        auto placeholderSpanNode = DynamicCast<PlaceholderSpanNode>(child);
        if (placeholderSpanNode) {
            auto placeholderSpan = placeholderSpanNode->GetSpanItem();
            placeholderSpan->placeholderSpanNodeId = placeholderSpanNode->GetId();
            spans_.emplace_back(placeholderSpan);
        }
    }
}

void TextPattern::DumpAdvanceInfo()
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
    DumpLog::GetInstance().AddDesc(std::string("contentRect-->x:")
                                       .append(std::to_string(contentRect_.GetX()))
                                       .append(" y:")
                                       .append(std::to_string(contentRect_.GetY())));
    DumpLog::GetInstance().AddDesc(std::string("Selection: ").append("(").append(textSelector_.ToString()).append(")"));
    if (SystemProperties::GetDebugEnabled() && paragraph_) {
        DumpLog::GetInstance().AddDesc(std::string("from TextEngine paragraph_ info :"));
        DumpLog::GetInstance().AddDesc(
            std::string("DidExceedMaxLinesx:").append(std::to_string(paragraph_->DidExceedMaxLines())));

        DumpLog::GetInstance().AddDesc(std::string("GetTextWidth:")
                                           .append(std::to_string(paragraph_->GetTextWidth()))
                                           .append(" GetHeight:")
                                           .append(std::to_string(paragraph_->GetHeight()))
                                           .append(" GetMaxWidth:")
                                           .append(std::to_string(paragraph_->GetMaxWidth()))
                                           .append(" GetMaxIntrinsicWidth:")
                                           .append(std::to_string(paragraph_->GetMaxIntrinsicWidth())));
        DumpLog::GetInstance().AddDesc(std::string("GetLineCount:")
                                           .append(std::to_string(paragraph_->GetLineCount()))
                                           .append(" GetLongestLine:")
                                           .append(std::to_string(paragraph_->GetLongestLine()))
                                           .append(" GetAlphabeticBaseline:")
                                           .append(std::to_string(paragraph_->GetAlphabeticBaseline())));
    }

    DumpLog::GetInstance().AddDesc(
        std::string("BindSelectionMenu: ").append(std::to_string(selectionMenuMap_.empty())));
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
    DumpLog::GetInstance().AddDesc(std::string("Selection: ").append("(").append(textSelector_.ToString()).append(")"));
}

void TextPattern::UpdateChildProperty(const RefPtr<SpanNode>& child) const
{
    CHECK_NULL_VOID(child);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textLayoutProp = host->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProp);

    auto inheritPropertyInfo = child->CalculateInheritPropertyInfo();
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
                    if (textLayoutProp->HasTextDecorationStyle()) {
                        child->UpdateTextDecorationStyleWithoutFlushDirty(
                            textLayoutProp->GetTextDecorationStyle().value());
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
            case PropertyInfo::TEXTSHADOW:
                if (textLayoutProp->HasTextShadow()) {
                    child->UpdateTextShadowWithoutFlushDirty(textLayoutProp->GetTextShadow().value());
                }
                break;
            default:
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
    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    auto textLayoutProperty = GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateTextColor(theme->GetTextStyle().GetTextColor());
}

OffsetF TextPattern::GetDragUpperLeftCoordinates()
{
    if (dragBoxes_.empty()) {
        return { 0.0f, 0.0f };
    }
    auto startY = dragBoxes_.front().Top();
    auto startX = dragBoxes_.front().Left();

    auto endY = dragBoxes_.back().Top();
    OffsetF offset;
    if (NearEqual(startY, endY)) {
        offset = { contentRect_.GetX() + startX, startY + contentRect_.GetY() };
    } else {
        offset = { contentRect_.GetX(), startY + contentRect_.GetY() };
    }

    return GetParentGlobalOffset() + offset;
}

void TextPattern::ProcessBoundRectByTextShadow(RectF& rect)
{
    auto property = GetHost()->GetLayoutProperty<TextLayoutProperty>();
    auto shadows = property->GetTextShadow();
    if (!shadows.has_value()) {
        return;
    }
    float leftOffsetX = 0.0f;
    float rightOffsetX = 0.0f;
    float upOffsetY = 0.0f;
    float downOffsetY = 0.0f;
    for (const auto& shadow : shadows.value()) {
        auto shadowBlurRadius = shadow.GetBlurRadius() * 2.0f;
        if (LessNotEqual(shadow.GetOffset().GetX() - shadowBlurRadius, leftOffsetX)) {
            leftOffsetX = shadow.GetOffset().GetX() - shadowBlurRadius;
        }

        if (GreatNotEqual(shadow.GetOffset().GetX() + shadowBlurRadius, rightOffsetX)) {
            rightOffsetX = shadow.GetOffset().GetX() + shadowBlurRadius;
        }

        if (LessNotEqual(shadow.GetOffset().GetY() - shadowBlurRadius, upOffsetY)) {
            upOffsetY = shadow.GetOffset().GetY() - shadowBlurRadius;
        }

        if (GreatNotEqual(shadow.GetOffset().GetY() + shadowBlurRadius, downOffsetY)) {
            downOffsetY = shadow.GetOffset().GetY() + shadowBlurRadius;
        }
    }
    rect.SetRect(
        leftOffsetX, upOffsetY, rect.Width() + rightOffsetX - leftOffsetX, rect.Height() + downOffsetY - upOffsetY);
}

void TextPattern::ProcessBoundRectByTextMarquee(RectF& rect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textLayoutProperty = host->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    if (!(textLayoutProperty->GetTextOverflowValue(TextOverflow::CLIP) == TextOverflow::MARQUEE)) {
        return;
    }
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    CHECK_NULL_VOID(paragraph_);
    if (paragraph_->GetTextWidth() < frameSize.Width()) {
        return;
    }
    auto relativeSelfLeftOffsetX =
        std::max(-1 * host->GetOffsetRelativeToWindow().GetX(), rect.GetOffset().GetX() - paragraph_->GetTextWidth());
    rect.SetLeft(relativeSelfLeftOffsetX);
    rect.SetWidth(frameSize.Width() + paragraph_->GetTextWidth() - relativeSelfLeftOffsetX);
}

RefPtr<NodePaintMethod> TextPattern::CreateNodePaintMethod()
{
    CreateModifier();
    auto paintMethod = MakeRefPtr<TextPaintMethod>(WeakClaim(this), baselineOffset_, contentMod_, overlayMod_);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, paintMethod);
    auto context = host->GetRenderContext();
    CHECK_NULL_RETURN(context, paintMethod);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, paintMethod);
    auto frameSize = geometryNode->GetFrameSize();

    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, paintMethod);
    std::vector<DimensionRect> hotZoneRegions;
    DimensionRect hotZoneRegion;
    if (!context->GetClipEdge().value_or(false)) {
        CHECK_NULL_RETURN(paragraph_, paintMethod);
        RectF boundsRect = overlayMod_->GetBoundsRect();
        auto boundsWidth = contentRect_.GetX() + std::ceil(static_cast<float>(paragraph_->GetLongestLine()));
        auto boundsHeight =
            contentRect_.GetY() + static_cast<float>(paragraph_->GetHeight() + std::fabs(baselineOffset_));
        boundsRect.SetWidth(boundsWidth);
        boundsRect.SetHeight(boundsHeight);

        hotZoneRegion.SetSize(DimensionSize(Dimension(std::max(boundsWidth, frameSize.Width())),
            Dimension(std::max(frameSize.Height(), boundsRect.Height()))));

        ProcessBoundRectByTextShadow(boundsRect);
        ProcessBoundRectByTextMarquee(boundsRect);
        if ((LessNotEqual(frameSize.Width(), boundsRect.Width()) ||
                LessNotEqual(frameSize.Height(), boundsRect.Height()))) {
            boundsWidth = std::max(frameSize.Width(), boundsRect.Width());
            boundsHeight = std::max(frameSize.Height(), boundsRect.Height());
            boundsRect.SetWidth(boundsWidth);
            boundsRect.SetHeight(boundsHeight);
        } else {
            boundsRect.SetWidth(frameSize.Width());
            boundsRect.SetHeight(frameSize.Height());
        }
        overlayMod_->SetBoundsRect(boundsRect);
    } else {
        hotZoneRegion.SetSize(DimensionSize(Dimension(frameSize.Width()), Dimension(frameSize.Height())));
    }
    hotZoneRegions.emplace_back(hotZoneRegion);
    gestureHub->SetResponseRegion(hotZoneRegions);
    return paintMethod;
}

void TextPattern::CreateModifier()
{
    if (!contentMod_) {
        contentMod_ = MakeRefPtr<TextContentModifier>(textStyle_, WeakClaim(this));
    }
    if (!overlayMod_) {
        overlayMod_ = MakeRefPtr<TextOverlayModifier>();
    }
    if (isCustomFont_) {
        contentMod_->SetIsCustomFont(true);
    }
}

int32_t TextPattern::GetHandleIndex(const Offset& offset) const
{
    return paragraph_->GetGlyphIndexByCoordinate(offset);
}

void TextPattern::OnAreaChangedInner()
{
    if (selectOverlay_->SelectOverlayIsOn()) {
        auto parentGlobalOffset = GetParentGlobalOffset();
        if (parentGlobalOffset != parentGlobalOffset_) {
            parentGlobalOffset_ = parentGlobalOffset;
            CalculateHandleOffsetAndShowOverlay();
            ShowSelectOverlay({ .menuIsShow = false, .animation = true });
        }
    }
}

void TextPattern::RemoveAreaChangeInner()
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (eventHub->HasOnAreaChanged()) {
        return;
    }
    pipeline->RemoveOnAreaChangeNode(host->GetId());
}

bool TextPattern::NeedShowAIDetect()
{
    return textDetectEnable_ && copyOption_ != CopyOptions::None && enabled_ &&
           !dataDetectorAdapter_->aiSpanMap_.empty();
}

void TextPattern::BindSelectionMenu(TextSpanType spanType, TextResponseType responseType,
    std::function<void()>& menuBuilder, std::function<void(int32_t, int32_t)>& onAppear,
    std::function<void()>& onDisappear)
{
    auto key = std::make_pair(spanType, responseType);
    auto it = selectionMenuMap_.find(key);
    if (it != selectionMenuMap_.end()) {
        if (menuBuilder == nullptr) {
            selectionMenuMap_.erase(it);
            return;
        }
        it->second->buildFunc = menuBuilder;
        it->second->onAppear = onAppear;
        it->second->onDisappear = onDisappear;
        return;
    }

    auto selectionMenuParams =
        std::make_shared<SelectionMenuParams>(spanType, menuBuilder, onAppear, onDisappear, responseType);
    selectionMenuMap_[key] = selectionMenuParams;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TextPattern::CloseSelectionMenu()
{
    textResponseType_ = TextResponseType::NONE;
    CloseSelectOverlay(true);
}

std::shared_ptr<SelectionMenuParams> TextPattern::GetMenuParams(TextSpanType spanType, TextResponseType responseType)
{
    auto key = std::make_pair(spanType, responseType);
    auto it = selectionMenuMap_.find(key);
    if (it != selectionMenuMap_.end()) {
        return it->second;
    }

    TAG_LOGD(AceLogTag::ACE_TEXT, "The key not in selectionMenuMap_");
    return nullptr;
}

void TextPattern::CopySelectionMenuParams(SelectOverlayInfo& selectInfo, TextResponseType responseType)
{
    auto currentSpanType = selectedType_.value_or(TextSpanType::NONE);
    std::shared_ptr<SelectionMenuParams> menuParams = nullptr;
    menuParams = GetMenuParams(currentSpanType, responseType);
    if (menuParams == nullptr) {
        return;
    }

    selectInfo.menuInfo.menuIsShow = true;
    CopyBindSelectionMenuParams(selectInfo, menuParams);
}

void TextPattern::CopyBindSelectionMenuParams(
    SelectOverlayInfo& selectInfo, std::shared_ptr<SelectionMenuParams> menuParams)
{
    selectInfo.menuInfo.menuBuilder = menuParams->buildFunc;
    if (menuParams->onAppear) {
        auto weak = AceType::WeakClaim(this);
        auto callback = [weak, menuParams]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            CHECK_NULL_VOID(menuParams->onAppear);

            auto& textSelector = pattern->textSelector_;
            auto selectStart = std::min(textSelector.baseOffset, textSelector.destinationOffset);
            auto selectEnd = std::max(textSelector.baseOffset, textSelector.destinationOffset);
            menuParams->onAppear(selectStart, selectEnd);
        };
        selectInfo.menuCallback.onAppear = std::move(callback);
    }
    selectInfo.menuCallback.onDisappear = menuParams->onDisappear;
}

void TextPattern::FireOnSelectionChange(int32_t start, int32_t end)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnSelectionChange(start, end);
}

void TextPattern::FireOnMarqueeStateChange(const TextMarqueeState& state)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnMarqueeStateChange(static_cast<int32_t>(state));
}

void TextPattern::HandleSelectionChange(int32_t start, int32_t end)
{
    if (textSelector_.GetStart() == start && textSelector_.GetEnd() == end) {
        return;
    }

    UpdateSelectionSpanType(std::min(start, end), std::max(start, end));
    textSelector_.Update(start, end);
    FireOnSelectionChange(std::min(start, end), std::max(start, end));
}

bool TextPattern::IsSelectedBindSelectionMenu()
{
    auto currentSpanType = selectedType_.value_or(TextSpanType::TEXT);
    return GetMenuParams(currentSpanType, TextResponseType::SELECTED_BY_MOUSE) != nullptr;
}

void TextPattern::UpdateSelectionSpanType(int32_t selectStart, int32_t selectEnd)
{
    UpdateSelectionType(GetSpansInfo(selectStart, selectEnd, GetSpansMethod::ONSELECT));
    if ((selectedType_ == TextSpanType::NONE && !textSelector_.StartEqualToDest()) ||
        textSelector_.StartEqualToDest()) {
        selectedType_ = TextSpanType::TEXT;
    }
}

void TextPattern::UpdateSelectionType(const SelectionInfo& selection)
{
    selectedType_ = TextSpanType::NONE;
    auto list = selection.GetSelection().resultObjects;
    bool imageSelected = false;
    bool textSelected = false;
    for (const auto& obj : list) {
        if (obj.type == SelectSpanType::TYPEIMAGE) {
            imageSelected = true;
        } else if (obj.type == SelectSpanType::TYPESPAN) {
            textSelected = true;
        }
        if (imageSelected && textSelected) {
            selectedType_ = TextSpanType::MIXED;
            return;
        }
    }
    if (imageSelected) {
        selectedType_ = TextSpanType::IMAGE;
    } else if (textSelected) {
        selectedType_ = TextSpanType::TEXT;
    }

    TAG_LOGD(AceLogTag::ACE_TEXT, "UpdateSelectionSpanType, selectedType_: %{public}d", selectedType_.value());
}

int32_t TextPattern::GetSelectionSpanItemIndex(const MouseInfo& info)
{
    RectF textContentRect = contentRect_;
    textContentRect.SetTop(contentRect_.GetY() - std::min(baselineOffset_, 0.0f));
    textContentRect.SetHeight(contentRect_.Height() - std::max(baselineOffset_, 0.0f));
    PointF textOffset = { info.GetLocalLocation().GetX() - textContentRect.GetX(),
        info.GetLocalLocation().GetY() - textContentRect.GetY() };
    if (!textContentRect.IsInRegion(PointF(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY())) ||
        spans_.empty() || !paragraph_) {
        return -1;
    }
    int32_t start = 0;
    bool isFind = false;
    int32_t index = -1;
    for (const auto& item : spans_) {
        index++;
        if (!item) {
            continue;
        }
        std::vector<RectF> selectedRects;
        paragraph_->GetRectsForRange(start, item->position, selectedRects);
        start = item->position;
        for (auto&& rect : selectedRects) {
            if (rect.IsInRegion(textOffset)) {
                isFind = true;
                break;
            }
        }
        if (isFind) {
            TAG_LOGD(AceLogTag::ACE_TEXT, "GetSelectionSpanItemIndex index: %{public}d", index);
            return index;
        }
    }
    return -1;
}

ResultObject TextPattern::GetBuilderResultObject(RefPtr<UINode> uiNode, int32_t index, int32_t start, int32_t end)
{
    int32_t itemLength = 1;
    ResultObject resultObject;
    resultObject.isDraggable = false;
    if (!DynamicCast<FrameNode>(uiNode) || !GetSpanItemByIndex(index)) {
        return resultObject;
    }
    int32_t endPosition = std::min(GetTextContentLength(), GetSpanItemByIndex(index)->position);
    int32_t startPosition = endPosition - itemLength;
    if ((start <= startPosition) && (end >= endPosition)) {
        auto builderNode = DynamicCast<FrameNode>(uiNode);
        CHECK_NULL_RETURN(builderNode, resultObject);
        resultObject.spanPosition.spanIndex = index;
        resultObject.spanPosition.spanRange[RichEditorSpanRange::RANGESTART] = startPosition;
        resultObject.spanPosition.spanRange[RichEditorSpanRange::RANGEEND] = endPosition;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGESTART] = 0;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGEEND] = itemLength;
        resultObject.type = SelectSpanType::TYPEIMAGE;
        auto geometryNode = builderNode->GetGeometryNode();
        CHECK_NULL_RETURN(geometryNode, resultObject);
        resultObject.imageStyle.size[RichEditorImageSize::SIZEWIDTH] = geometryNode->GetMarginFrameSize().Width();
        resultObject.imageStyle.size[RichEditorImageSize::SIZEHEIGHT] = geometryNode->GetMarginFrameSize().Height();
        resultObject.valueString = " ";
    }
    return resultObject;
}

void TextPattern::SetStyledString(const RefPtr<SpanString>& value)
{
    spans_ = value->GetSpanItems();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}
} // namespace OHOS::Ace::NG
