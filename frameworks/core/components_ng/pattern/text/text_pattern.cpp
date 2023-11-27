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
#include "core/common/ai/data_detector_mgr.h"
#include "core/common/font_manager.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/event/long_press_event.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/text_event_hub.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_drag/text_drag_pattern.h"
#include "core/components_ng/property/property.h"

#ifdef ENABLE_DRAG_FRAMEWORK
#include "core/common/ace_engine_ext.h"
#include "core/common/udmf/udmf_client.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t AI_TEXT_MAX_LENGTH = 300;
constexpr int32_t AI_TEXT_GAP = 30;
constexpr int32_t AI_DELAY_TIME = 300;
constexpr const char COPY_ACTION[] = "copy";
constexpr const char SELECT_ACTION[] = "select";
constexpr int32_t API_PROTEXTION_GREATER_NINE = 9;
// uncertainty range when comparing selectedTextBox to contentRect
constexpr float BOX_EPSILON = 0.5f;
constexpr float DOUBLECLICK_INTERVAL_MS = 300.0f;
constexpr uint32_t SECONDS_TO_MILLISECONDS = 1000;
const std::map<TextDataDetectType, std::string> TEXT_DETECT_MAP = {
    {TextDataDetectType::PHONE_NUMBER, "phoneNum"}, {TextDataDetectType::URL, "url"},
    {TextDataDetectType::EMAIL, "email"}, {TextDataDetectType::ADDRESS, "location"} };
}; // namespace

void TextPattern::OnAttachToFrameNode()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (pipeline->GetMinPlatformVersion() > API_PROTEXTION_GREATER_NINE) {
        host->GetRenderContext()->UpdateClipEdge(true);
    }
    InitSurfaceChangedCallback();
    InitSurfacePositionChangedCallback();
    auto textLayoutProperty = GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateTextAlign(TextAlign::START);
    textLayoutProperty->UpdateAlignment(Alignment::CENTER_LEFT);
}

void TextPattern::OnDetachFromFrameNode(FrameNode* node)
{
    aiDetectDelayTask_.Cancel();
    CloseSelectOverlay();
    auto pipeline = PipelineContext::GetCurrentContext();
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
    if (selectOverlayProxy_ && !selectOverlayProxy_->IsClosed()) {
        selectOverlayProxy_->Close(animation);
        RemoveAreaChangeInner();
    }
}

void TextPattern::ResetSelection()
{
    if (textSelector_.IsValid()) {
        textSelector_.Update(-1, -1);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void TextPattern::InitSelection(const Offset& pos)
{
    CHECK_NULL_VOID(paragraph_);
    int32_t extend = paragraph_->GetGlyphIndexByCoordinate(pos);
    int32_t start = 0;
    int32_t end = 0;
    if (!paragraph_->GetWordBoundary(extend, start, end)) {
        start = extend;
        end = std::min(static_cast<int32_t>(GetWideText().length()) + imageCount_,
            extend + GetGraphemeClusterLength(GetWideText(), extend));
    }
    textSelector_.Update(start, end);
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    auto offset = host->GetPaintRectOffset() + contentRect_.GetOffset();
    auto textPaintOffset = offset - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));

    // calculate firstHandleOffset, secondHandleOffset and handlePaintSize
    CaretMetricsF firstHandleMetrics;
    CaretMetricsF secondHandleMetrics;
    CalcCaretMetricsByPosition(textSelector_.baseOffset, firstHandleMetrics, TextAffinity::DOWNSTREAM);
    CalcCaretMetricsByPosition(textSelector_.destinationOffset, secondHandleMetrics, TextAffinity::UPSTREAM);
    OffsetF firstHandleOffset = firstHandleMetrics.offset + textPaintOffset - rootOffset;
    OffsetF secondHandleOffset = secondHandleMetrics.offset + textPaintOffset - rootOffset;

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

OffsetF TextPattern::GetTextPaintOffset() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, OffsetF(0.0f, 0.0f));
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, OffsetF(0.0f, 0.0f));
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    auto offset = host->GetPaintRectOffset() + contentRect_.GetOffset();
    auto textPaintOffset = offset - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));
    return textPaintOffset - rootOffset;
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
        dragBoxes_ = GetTextBoxes();
        // prevent long press event from being triggered when dragging
#ifdef ENABLE_DRAG_FRAMEWORK
        gestureHub->SetIsTextDraggable(true);
#endif
        return;
    }
#ifdef ENABLE_DRAG_FRAMEWORK
    gestureHub->SetIsTextDraggable(false);
#endif
    auto textPaintOffset = contentRect_.GetOffset() - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));
    Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
        info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
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
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto rootOffset = pipeline->GetRootRect().GetOffset();
    auto offset = host->GetPaintRectOffset() + contentRect_.GetOffset() - rootOffset;
    auto textPaintOffset = offset - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));

    auto localOffset = handleRect.GetOffset();

    if (localOffset.GetX() < offset.GetX()) {
        localOffset.SetX(offset.GetX());
    } else if (GreatOrEqual(localOffset.GetX(), offset.GetX() + contentRect_.Width())) {
        localOffset.SetX(offset.GetX() + contentRect_.Width());
    }

    if (localOffset.GetY() < offset.GetY()) {
        localOffset.SetY(offset.GetY());
    } else if (GreatNotEqual(localOffset.GetY(), offset.GetY() + contentRect_.Height())) {
        localOffset.SetY(offset.GetY() + contentRect_.Height());
    }

    localOffset -= textPaintOffset;

    CHECK_NULL_VOID(paragraph_);
    // the handle position is calculated based on the middle of the handle height.
    if (isFirstHandle) {
        auto start = GetHandleIndex(Offset(localOffset.GetX(), localOffset.GetY() + handleRect.Height() / 2));
        textSelector_.Update(start, textSelector_.destinationOffset);
    } else {
        auto end = GetHandleIndex(Offset(localOffset.GetX(), localOffset.GetY() + handleRect.Height() / 2));
        textSelector_.Update(textSelector_.baseOffset, end);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);

    CHECK_NULL_VOID(selectOverlayProxy_);
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
        return;
    }
    auto value = GetSelectedText(textSelector_.GetTextStart(), textSelector_.GetTextEnd());
    if (value.empty()) {
        textSelector_.Update(-1, -1);
        return;
    }
    if (copyOption_ != CopyOptions::None || textDetectEnable_) {
        clipboard_->SetData(value, copyOption_);
    }
    ResetSelection();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->FireOnCopy(value);
}

void TextPattern::SetTextSelection(int32_t selectionStart, int32_t selectionEnd)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto context = PipelineContext::GetCurrentContext();
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
                auto selfIdealSize = textLayoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
                if ((selfIdealSize->Width().has_value() && selfIdealSize->Width()->GetDimension().ConvertToPx() <= 0) ||
                    (selfIdealSize->Height().has_value() &&
                        selfIdealSize->Height()->GetDimension().ConvertToPx() <= 0)) {
                    return;
                }
            }
            if (textLayoutProperty->GetCopyOptionValue(CopyOptions::None) == CopyOptions::None ||
                textLayoutProperty->GetTextOverflowValue(TextOverflow::CLIP) == TextOverflow::MARQUEE) {
                return;
            }
            if (!ifHaveObscured && eventHub->IsEnabled()) {
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

void TextPattern::ShowSelectOverlay(const RectF& firstHandle, const RectF& secondHandle)
{
    ShowSelectOverlay(firstHandle, secondHandle, false);
}
void TextPattern::ShowSelectOverlay(const RectF& firstHandle, const RectF& secondHandle, bool animation)
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
    selectInfo.menuInfo.menuIsShow = selectInfo.firstHandle.isShow || selectInfo.secondHandle.isShow;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuInfo.showCopyAll = !IsSelectAll();
    selectInfo.menuCallback.onCopy = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleOnCopy();
        pattern->RemoveAreaChangeInner();
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
            pattern->RemoveAreaChangeInner();
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
    auto textSize = static_cast<int32_t>(GetWideText().length()) + imageCount_;
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
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto offset = host->GetPaintRectOffset() + contentRect_.GetOffset() - pipeline->GetRootRect().GetOffset();
    RectF contentGlobalRect(offset, contentRect_.GetSize());
    contentGlobalRect = GetVisibleContentRect(host->GetAncestorNodeOfFrame(), contentGlobalRect);
    auto handleOffset = handleInfo.paintRect.GetOffset();
    handleInfo.isShow = contentGlobalRect.IsInRegion(PointF(handleOffset.GetX(), handleOffset.GetY() + BOX_EPSILON));
}

void TextPattern::InitLongPressEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!longPressEvent_);
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
    if (hasClicked_) {
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
    if (textSelector_.IsValid()) {
        CloseSelectOverlay(true);
        ResetSelection();
    }

    RectF textContentRect = contentRect_;
    textContentRect.SetTop(contentRect_.GetY() - std::min(baselineOffset_, 0.0f));
    textContentRect.SetHeight(contentRect_.Height() - std::max(baselineOffset_, 0.0f));
    bool isClickOnSpan = false;
    PointF textOffset = { info.GetLocalLocation().GetX() - textContentRect.GetX(),
        info.GetLocalLocation().GetY() - textContentRect.GetY() };
    HandleSpanSingleClickEvent(info, textContentRect, textOffset, isClickOnSpan);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (textDetectEnable_ && host->GetChildren().empty() && !aiSpanMap_.empty()) {
        ClickAISpan(info, textOffset);
    }
    if (onClick_ && !isClickOnSpan) {
        auto onClick = onClick_;
        onClick(info);
    }
}

void TextPattern::HandleSpanSingleClickEvent(
    GestureEvent& info, RectF textContentRect, PointF textOffset, bool& isClickOnSpan)
{
    if (textContentRect.IsInRegion(PointF(info.GetLocalLocation().GetX(), info.GetLocalLocation().GetY())) &&
        !spans_.empty() && paragraph_) {
        int32_t start = 0;
        bool processed = false;
        for (const auto& item : spans_) {
            if (!item) {
                continue;
            }
            if (textDetectEnable_ && !aiSpanMap_.empty() && !processed) {
                processed = ClickAISpan(info,  textOffset);
            }
            std::vector<RectF> selectedRects;
            paragraph_->GetRectsForRange(start, item->position, selectedRects);
            start = item->position;
            for (auto&& rect : selectedRects) {
                if (rect.IsInRegion(textOffset)) {
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
                    return;
                }
            }
        }
    }
}

bool TextPattern::ClickAISpan(GestureEvent& info, PointF textOffset)
{
    for (const auto& kv : aiSpanMap_) {
        auto aiSpan = kv.second;
        std::vector<RectF> aiRects;
        paragraph_->GetRectsForRange(aiSpan.start, aiSpan.end, aiRects);
        for (auto&& rect : aiRects) {
            if (rect.IsInRegion(textOffset)) {
                ShowUIExtensionMenu(aiSpan);
                return true;
            }
        }
    }
    return false;
}

void TextPattern::ShowUIExtensionMenu(AISpan aiSpan)
{
    auto onClickMenu = [aiSpan, weak = WeakClaim(this)](const std::string& action) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (action == std::string(COPY_ACTION)) {
            pattern->textSelector_.Update(aiSpan.start, aiSpan.end);
            pattern->HandleOnCopy();
        } else if (action == std::string(SELECT_ACTION)) {
            pattern->textSelector_.Update(aiSpan.start, aiSpan.end);
            pattern->CalculateHandleOffsetAndShowOverlay();
            pattern->ShowSelectOverlay(pattern->textSelector_.firstHandle, pattern->textSelector_.secondHandle, true);
            auto frameNode = pattern->GetHost();
            CHECK_NULL_VOID(frameNode);
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
    };
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textOverlayTheme = pipeline->GetTheme<TextOverlayTheme>();
    CHECK_NULL_VOID(textOverlayTheme);
    auto menuSpacing =
        textOverlayTheme->GetMenuSpacingWithText().ConvertToPx() + textOverlayTheme->GetHandleDiameter().ConvertToPx();
    auto baseOffset = textSelector_.baseOffset;
    auto destinationOffset = textSelector_.destinationOffset;
    textSelector_.Update(aiSpan.start, aiSpan.end);
    CalculateHandleOffsetAndShowOverlay();
    RectF handleBound = textSelector_.firstHandle.CombineRectT(textSelector_.secondHandle);
    textSelector_.Update(baseOffset, destinationOffset);
    RectF safeArea(handleBound.GetX(), handleBound.GetY() - menuSpacing, handleBound.Width(),
        handleBound.Height() + menuSpacing * 2);
    std::map<std::string, std::string> paramaters;
    paramaters["entityType"] = TEXT_DETECT_MAP.at(aiSpan.type);
    paramaters["entityText"] = aiSpan.content;
    if (TEXT_DETECT_MAP.find(aiSpan.type) == TEXT_DETECT_MAP.end() ||
        aiMenuOptionsMap_.find(TEXT_DETECT_MAP.at(aiSpan.type)) == aiMenuOptionsMap_.end()) {
        TAG_LOGI(AceLogTag::ACE_TEXT, "Error menu options");
    }
    std::vector<std::string> menuOptions = aiMenuOptionsMap_.at(TEXT_DETECT_MAP.at(aiSpan.type));
    if (menuOptions.empty()) {
        TAG_LOGI(AceLogTag::ACE_TEXT, "Menu option is empty");
        return;
    }
    DataDetectorMgr::GetInstance().ShowUIExtensionMenu(paramaters, safeArea, onClickMenu, menuOptions, GetHost());
}

void TextPattern::HandleDoubleClickEvent(GestureEvent& info)
{
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
    CalculateHandleOffsetAndShowOverlay();
    if (!isMousePressed_) {
        ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle, true);
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!clickEventInitialized_);
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
        auto textPaintOffset = contentRect_.GetOffset() - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));
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
            auto textPaintOffset = contentRect_.GetOffset() - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));
            Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
                info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
            CHECK_NULL_VOID(paragraph_);
            auto start = paragraph_->GetGlyphIndexByCoordinate(textOffset);
            textSelector_.Update(start, start);
        }

        if (info.GetAction() == MouseAction::MOVE) {
            if (blockPress_) {
                dragBoxes_ = GetTextBoxes();
                return;
            }
            mouseStatus_ = MouseStatus::MOVE;
            auto textPaintOffset = contentRect_.GetOffset() - OffsetF(0.0f, std::min(baselineOffset_, 0.0f));
            Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
                info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
            CHECK_NULL_VOID(paragraph_);
            auto end = paragraph_->GetGlyphIndexByCoordinate(textOffset);
            textSelector_.Update(textSelector_.baseOffset, end);
        }

        if (info.GetAction() == MouseAction::RELEASE) {
            if (blockPress_) {
                blockPress_ = false;
            }
            mouseStatus_ = MouseStatus::RELEASED;
            if (isDoubleClick_) {
                isDoubleClick_ = false;
            } else {
                auto textPaintOffset = contentRect_.GetOffset() - OffsetF(0.0, std::min(baselineOffset_, 0.0f));
                Offset textOffset = { info.GetLocalLocation().GetX() - textPaintOffset.GetX(),
                    info.GetLocalLocation().GetY() - textPaintOffset.GetY() };
                CHECK_NULL_VOID(paragraph_);
                auto end = paragraph_->GetGlyphIndexByCoordinate(textOffset);
                textSelector_.Update(textSelector_.baseOffset, end);
            }
            isMousePressed_ = false;
        }
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
    auto pipelineContext = PipelineContext::GetCurrentContext();
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

#ifdef ENABLE_DRAG_FRAMEWORK
DragDropInfo TextPattern::OnDragStart(const RefPtr<Ace::DragEvent>& event, const std::string& extraParams)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, {});

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
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (eventHub->HasOnDragStart()) {
        gestureHub->SetTextDraggable(false);
        return;
    }
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
            FrameNode::ProcessOffscreenNode(pattern->dragNode_);
        }
    };
}
#endif // ENABLE_DRAG_FRAMEWORK

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
        paragraph_.Reset();
    }

    if (!(PipelineContext::GetCurrentContext() &&
            PipelineContext::GetCurrentContext()->GetMinPlatformVersion() > API_PROTEXTION_GREATER_NINE)) {
        bool shouldClipToContent =
            textLayoutProperty->GetTextOverflow().value_or(TextOverflow::CLIP) == TextOverflow::CLIP;
        host->GetRenderContext()->SetClipToFrame(shouldClipToContent);
    }

    if (host->GetChildren().empty()) {
        std::string textCache = textForDisplay_;
        textForDisplay_ = textLayoutProperty->GetContent().value_or("");
        if (textCache != textForDisplay_) {
            host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE, textCache, textForDisplay_);
            if (!textDetectEnable_) {
                aiDetectInitialized_ = false;
            }
        }
        textForAI_ = textForDisplay_;
        if (textDetectEnable_ && (aiDetectTypesChanged_ || !aiDetectInitialized_ || textCache != textForDisplay_)) {
            StartAITask();
        }
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
        auto context = PipelineContext::GetCurrentContext();
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
    if (onClick_ || copyOption_ != CopyOptions::None || textDetectEnable_) {
        InitClickEvent(gestureEventHub);
    }
}

void TextPattern::SetTextDetectTypes(const std::string& types)
{
    textDetectTypes_ = types;

    std::set<std::string> newTypesSet;
    std::istringstream iss(types);
    std::string type;
    while (std::getline(iss, type, ',')) {
        newTypesSet.insert(type);
    }
    if (newTypesSet != textDetectTypesSet_) {
        textDetectTypesSet_ = newTypesSet;
        aiDetectTypesChanged_ = true;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void TextPattern::InitTextDetect(int32_t startPos, std::string detectText)
{
    if (!textDetectEnable_) {
        return;
    }

    TextDataDetectInfo info;
    info.text = detectText;
    info.module = GetTextDetectTypes();

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    int32_t instanceID = context->GetInstanceId();
    auto textFunc = [weak = WeakClaim(this), instanceID, startPos](const TextDataDetectResult result) {
        ContainerScope scope(instanceID);
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto uiTaskExecutor = SingleTaskExecutor::Make(
            host->GetContext()->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        uiTaskExecutor.PostTask([result, weak, instanceID, startPos] {
            ContainerScope scope(instanceID);
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->SetTextDetectResult(result);
            pattern->FireOnResult(result.entity);
            pattern->ParseAIResult(result, startPos);
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        });
    };

    TAG_LOGI(AceLogTag::ACE_TEXT, "Start entity detect using AI");
    DataDetectorMgr::GetInstance().DataDetect(info, textFunc);
}

void TextPattern::ParseAIResult(const TextDataDetectResult& result, int32_t startPos)
{
    auto entityMenuServiceInfoJson = JsonUtil::ParseJsonString(result.entityMenuServiceInfo);
    CHECK_NULL_VOID(entityMenuServiceInfoJson);
    if (DataDetectorMgr::GetInstance().GetBundleName().empty()) {
        DataDetectorMgr::GetInstance().SetBundleName(entityMenuServiceInfoJson->GetString("bundlename"));
    }
    if (DataDetectorMgr::GetInstance().GetAbilityName().empty()) {
        DataDetectorMgr::GetInstance().SetAbilityName(entityMenuServiceInfoJson->GetString("abilityname"));
    }
    auto entityJson = JsonUtil::ParseJsonString(result.entity);
    CHECK_NULL_VOID(entityJson);
    auto menuOptionsJson = JsonUtil::ParseJsonString(result.menuOption);
    CHECK_NULL_VOID(menuOptionsJson);
    auto aiMenuOptions = aiMenuOptionsMap_;
    for (const auto& type : TEXT_DETECT_MAP) {
        auto jsonValue = entityJson->GetValue(type.second);
        ParseAIJson(jsonValue, type.first, startPos);
        if (aiMenuOptions.empty()) {
            jsonValue = menuOptionsJson->GetValue(type.second);
            ParseAIJson(jsonValue, type.first, startPos, true);
        }
    }

    if (startPos + AI_TEXT_MAX_LENGTH >=
        static_cast<int32_t>(StringUtils::ToWstring(textForAI_).length())) {
        aiDetectInitialized_ = true;
        aiDetectTypesChanged_ = false;
    }
}

void TextPattern::ParseAIJson(const std::unique_ptr<JsonValue>& jsonValue,
    TextDataDetectType type, int32_t startPos, bool isMenuOption)
{
    if (!jsonValue || !jsonValue->IsArray()) {
        TAG_LOGI(AceLogTag::ACE_TEXT, "Error AI Result.");
        return;
    }
    if (isMenuOption) {
        std::vector<std::string> menuOptions;
        for (int32_t i = 0; i < jsonValue->GetArraySize(); ++i) {
            auto item = jsonValue->GetArrayItem(i);
            auto option = item->GetString("option");
            menuOptions.emplace_back(option);
        }
        if (menuOptions.empty()) {
            TAG_LOGI(AceLogTag::ACE_TEXT, "Error menu option is empty.");
        } else {
            aiMenuOptionsMap_[TEXT_DETECT_MAP.at(type)] = menuOptions;
        }
        return;
    }
    for (int32_t i = 0; i < jsonValue->GetArraySize(); ++i) {
        auto item = jsonValue->GetArrayItem(i);
        auto charOffset = item->GetInt("charOffset");
        auto oriText = item->GetString("oriText");
        auto wTextForAI = StringUtils::ToWstring(textForAI_);
        auto wOriText = StringUtils::ToWstring(oriText);
        int32_t end = startPos + charOffset + static_cast<int32_t>(wOriText.length());
        if (charOffset < 0 || startPos + charOffset >= static_cast<int32_t>(wTextForAI.length())
            || end >= startPos + AI_TEXT_MAX_LENGTH || oriText.empty()) {
            LOGW("The result of AI is error");
            continue;
        }
        if (oriText != StringUtils::ToString(
            wTextForAI.substr(startPos + charOffset, static_cast<int32_t>(wOriText.length())))) {
            LOGW("The charOffset is error");
            continue;
        }
        AISpan aiSpan;
        aiSpan.start = startPos + charOffset;
        aiSpan.end = end;
        aiSpan.content = oriText;
        aiSpan.type = type;
        aiSpanMap_[aiSpan.start] = aiSpan;
    }
}

void TextPattern::StartAITask()
{
    aiSpanMap_.clear();

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    aiDetectDelayTask_.Cancel();
    aiDetectDelayTask_.Reset([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern->textForAI_.empty()) {
            return;
        }
        int32_t startPos = 0;
        auto wTextForAI = StringUtils::ToWstring(pattern->textForAI_);
        auto wTextForAILength = static_cast<int32_t>(wTextForAI.length());
        while (startPos < wTextForAILength) {
            std::string detectText = StringUtils::ToString(
                wTextForAI.substr(startPos, AI_TEXT_MAX_LENGTH));
            pattern->InitTextDetect(startPos, detectText);
            startPos += AI_TEXT_MAX_LENGTH - AI_TEXT_GAP;
        }
    });
    taskExecutor->PostDelayedTask(aiDetectDelayTask_, TaskExecutor::TaskType::UI, AI_DELAY_TIME);
}

void TextPattern::ActSetSelection(int32_t start, int32_t end)
{
    int32_t min = 0;
    int32_t textSize = static_cast<int32_t>(GetWideText().length()) + imageCount_;
    start = start < min ? min : start;
    end = end < min ? min : end;
    start = start > textSize ? textSize : start;
    end = end > textSize ? textSize : end;
    if (start >= end) {
        return;
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
        firstHandleInfo.paintRect = textSelector_.firstHandle;
        CheckHandles(firstHandleInfo);

        SelectHandleInfo secondHandleInfo;
        secondHandleInfo.paintRect = textSelector_.secondHandle;
        CheckHandles(secondHandleInfo);

        auto start = textSelector_.GetTextStart();
        auto end = textSelector_.GetTextEnd();
        selectOverlayProxy_->SetSelectInfo(GetSelectedText(start, end));
        selectOverlayProxy_->UpdateFirstAndSecondHandleInfo(firstHandleInfo, secondHandleInfo);
        selectOverlayProxy_->ShowOrHiddenMenu(!firstHandleInfo.isShow && !secondHandleInfo.isShow);
    } else {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        pipeline->AddOnAreaChangeNode(host->GetId());
        selectInfo.callerFrameNode = GetHost();
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
    if (selectOverlayProxy_ && !selectOverlayProxy_->IsClosed()) {
        CalculateHandleOffsetAndShowOverlay();
        ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle);
        selectOverlayProxy_->ShowOrHiddenMenu(true);
    }
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }

    contentRect_ = dirty->GetGeometryNode()->GetContentRect();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    parentGlobalOffset_ = host->GetPaintRectOffset() - context->GetRootRect().GetOffset();

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
    return true;
}

void TextPattern::PreCreateLayoutWrapper()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    // mark content dirty
    if (contentMod_) {
        contentMod_->ContentChange();
    }

    imageCount_ = 0;
    // When dirty areas are marked because of child node changes, the text rendering node tree is reset.
    const auto& children = host->GetChildren();
    if (children.empty()) {
        return;
    }
    spans_.clear();

    // Depth-first iterates through all host's child nodes to collect the SpanNode object, building a text rendering
    // tree.
    std::stack<RefPtr<UINode>> nodes;
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        nodes.push(*iter);
    }

    std::string textCache;
    std::string textForAICache;
    if (!nodes.empty()) {
        textCache = textForDisplay_;
        textForAICache = textForAI_;
        textForDisplay_.clear();
        textForAI_.clear();
    }

    bool isSpanHasClick = false;
    CollectSpanNodes(nodes, isSpanHasClick);

    if (textCache != textForDisplay_) {
        host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE, textCache, textForDisplay_);
        if (!textDetectEnable_) {
            aiDetectInitialized_ = false;
        }
    }
    if (isSpanHasClick) {
        auto gestureEventHub = host->GetOrCreateGestureEventHub();
        InitClickEvent(gestureEventHub);
    }
    if (textDetectEnable_ && (aiDetectTypesChanged_ || !aiDetectInitialized_ || textForAICache != textForAI_)) {
        StartAITask();
    }
}

void TextPattern::BeforeCreateLayoutWrapper()
{
    PreCreateLayoutWrapper();
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
        if (spanNode && current->GetTag() != V2::PLACEHOLDER_SPAN_ETS_TAG) {
            spanNode->CleanSpanItemChildren();
            UpdateChildProperty(spanNode);
            spanNode->MountToParagraph();
            textForDisplay_.append(spanNode->GetSpanItem()->content);
            textForAI_.append(spanNode->GetSpanItem()->content);
            if (spanNode->GetSpanItem()->onClick) {
                isSpanHasClick = true;
            }
        } else if (current->GetTag() == V2::IMAGE_ETS_TAG || current->GetTag() == V2::PLACEHOLDER_SPAN_ETS_TAG) {
            imageCount_++;
            AddChildSpanItem(current);
            textForAI_.append("\n");
        }
        if (current->GetTag() == V2::PLACEHOLDER_SPAN_ETS_TAG) {
            continue;
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
    auto pipeline = PipelineContext::GetCurrentContext();
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
            aiDetectDelayTask_.Cancel();
        }
    } else {
        if (textDetectEnable_) {
            StartAITask();
        }
    }
}

void TextPattern::InitSurfaceChangedCallback()
{
    auto pipeline = PipelineContext::GetCurrentContext();
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
}

void TextPattern::InitSurfacePositionChangedCallback()
{
    auto pipeline = PipelineContext::GetCurrentContext();
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

    if (child->GetTag() == V2::SPAN_ETS_TAG) {
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
            spans_.emplace_back(MakeRefPtr<ImageSpanItem>());
            spans_.back()->imageNodeId = imageNode->GetId();
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
    auto context = PipelineContext::GetCurrentContext();
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
        if (LessNotEqual(shadow.GetOffset().GetX(), 0.0f) && LessNotEqual(shadow.GetOffset().GetX(), leftOffsetX)) {
            leftOffsetX = shadow.GetOffset().GetX() - shadowBlurRadius;
        }

        if (GreatNotEqual(shadow.GetOffset().GetX(), 0.0f) &&
            GreatNotEqual(shadow.GetOffset().GetX() + shadowBlurRadius, rightOffsetX)) {
            rightOffsetX = shadow.GetOffset().GetX() + shadowBlurRadius;
        }

        if (LessNotEqual(shadow.GetOffset().GetY(), 0.0f) && LessNotEqual(shadow.GetOffset().GetY(), upOffsetY)) {
            upOffsetY = shadow.GetOffset().GetY() - shadowBlurRadius;
        }

        if (GreatNotEqual(shadow.GetOffset().GetY(), 0.0f) &&
            GreatNotEqual(shadow.GetOffset().GetY() + shadowBlurRadius, downOffsetY)) {
            downOffsetY = shadow.GetOffset().GetY() + shadowBlurRadius;
        }
    }
    rect.SetRect(
        leftOffsetX, upOffsetY, rect.Width() + rightOffsetX - leftOffsetX, rect.Height() + downOffsetY - upOffsetY);
}

RefPtr<NodePaintMethod> TextPattern::CreateNodePaintMethod()
{
    if (!contentMod_) {
        contentMod_ = MakeRefPtr<TextContentModifier>(textStyle_);
    }
    if (!overlayMod_) {
        overlayMod_ = MakeRefPtr<TextOverlayModifier>();
    }
    if (isCustomFont_) {
        contentMod_->SetIsCustomFont(true);
    }
    auto paintMethod = MakeRefPtr<TextPaintMethod>(WeakClaim(this), baselineOffset_, contentMod_, overlayMod_);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, paintMethod);
    auto context = host->GetRenderContext();
    CHECK_NULL_RETURN(context, paintMethod);
    if (context->GetClipEdge().has_value()) {
        auto geometryNode = host->GetGeometryNode();
        auto frameSize = geometryNode->GetFrameSize();
        CHECK_NULL_RETURN(paragraph_, paintMethod);
        RectF boundsRect = overlayMod_->GetBoundsRect();
        auto boundsWidth = contentRect_.GetX() + static_cast<float>(paragraph_->GetLongestLine());
        auto boundsHeight =
            contentRect_.GetY() + static_cast<float>(paragraph_->GetHeight() + std::fabs(baselineOffset_));
        boundsRect.SetWidth(boundsWidth);
        boundsRect.SetHeight(boundsHeight);
        ProcessBoundRectByTextShadow(boundsRect);
        if (!context->GetClipEdge().value() && (LessNotEqual(frameSize.Width(), boundsRect.Width()) ||
                                                   LessNotEqual(frameSize.Height(), boundsRect.Height()))) {
            boundsWidth = std::max(frameSize.Width(), boundsRect.Width());
            boundsHeight = std::max(frameSize.Height(), boundsRect.Height());
            boundsRect.SetWidth(boundsWidth);
            boundsRect.SetHeight(boundsHeight);
            overlayMod_->SetBoundsRect(boundsRect);
        }
    }
    return paintMethod;
}

int32_t TextPattern::GetHandleIndex(const Offset& offset) const
{
    return paragraph_->GetGlyphIndexByCoordinate(offset);
}

void TextPattern::OnAreaChangedInner()
{
    if (selectOverlayProxy_ && !selectOverlayProxy_->IsClosed()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto parentGlobalOffset = host->GetPaintRectOffset() - context->GetRootRect().GetOffset();
        if (parentGlobalOffset != parentGlobalOffset_) {
            parentGlobalOffset_ = parentGlobalOffset;
            CalculateHandleOffsetAndShowOverlay();
            ShowSelectOverlay(textSelector_.firstHandle, textSelector_.secondHandle, true);
        }
    }
}

void TextPattern::RemoveAreaChangeInner()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<TextEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (eventHub->HasOnAreaChanged()) {
        LOGD("RemoveAreaChangeInner do not remove external area change callback");
        return;
    }
    pipeline->RemoveOnAreaChangeNode(host->GetId());
}
} // namespace OHOS::Ace::NG
