/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/text/render_text.h"

#include "base/log/dump_log.h"
#include "core/common/ace_engine_ext.h"
#include "core/common/font_manager.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components/text_overlay/text_overlay_component.h"
#include "core/event/ace_event_helper.h"
#include "core/event/ace_events.h"

namespace OHOS::Ace {

namespace {
constexpr Dimension CURSOR_WIDTH = 1.5_vp;
constexpr double HANDLE_HOT_ZONE = 10.0;
} // namespace

RenderText::~RenderText()
{
    auto context = context_.Upgrade();
    if (context) {
        context->RemoveFontNode(AceType::WeakClaim(this));
        auto fontManager = context->GetFontManager();
        if (fontManager) {
            fontManager->UnRegisterCallback(AceType::WeakClaim(this));
            fontManager->RemoveVariationNode(WeakClaim(this));
        }
    }

    auto textOverlayManager = GetTextOverlayManager(context_);
    if (textOverlayManager) {
        auto textOverlayBase = textOverlayManager->GetTextOverlayBase();
        if (textOverlayBase) {
            auto targetNode = textOverlayManager->GetTargetNode();
            if (targetNode == this) {
                textOverlayManager->PopTextOverlay();
                textOverlayBase->ChangeSelection(0, 0);
                textOverlayBase->MarkIsOverlayShowed(false);
                targetNode->MarkNeedRender();
            }
        }
    }
}

void RenderText::Update(const RefPtr<Component>& component)
{
    text_ = AceType::DynamicCast<TextComponent>(component);
    CheckIfNeedMeasure();
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("the context is nullptr in text update");
        return;
    }
    // Register callback for fonts.
    auto callback = [weakText = AceType::WeakClaim(this)] {
        auto text = weakText.Upgrade();
        if (text) {
            text->isCallbackCalled_ = true;
            text->MarkNeedLayout();
        }
    };

    auto fontManager = context->GetFontManager();
    if (fontManager) {
        for (const auto& familyName : textStyle_.GetFontFamilies()) {
            auto isCustomFont = fontManager->RegisterCallback(AceType::WeakClaim(this), familyName, callback);
            if (isCustomFont) {
                isCustomFont_ = true;
            }
        }
        fontManager->AddVariationNode(WeakClaim(this));
    }
    if (isFocus_) {
        textStyle_.SetTextColor(focusColor_);
    }

    if (textStyle_.IsAllowScale() || textStyle_.GetFontSize().Unit() == DimensionUnit::FP) {
        context->AddFontNode(AceType::WeakClaim(this));
    }

    if (!clipboard_ && context) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(context->GetTaskExecutor());
    }

    copyOption_ = text_->GetCopyOption();
    textForDisplay_ = text_->GetData();
    defaultTextDirection_ = TextDirection::LTR;
    realTextDirection_ = defaultTextDirection_;
    textAffinity_ = TextAffinity::UPSTREAM;
    textValue_.text = text_->GetData();
    cursorWidth_ = NormalizeToPx(CURSOR_WIDTH);
    alignment_ = text_->GetAlignment();

    onDragStart_ = text_->GetOnDragStartId();
    onDragEnter_ = text_->GetOnDragEnterId();
    onDragMove_ = text_->GetOnDragMoveId();
    onDragLeave_ = text_->GetOnDragLeaveId();
    onDrop_ = text_->GetOnDropId();
    if (onDragStart_) {
        CreateDragDropRecognizer(context_);
        CreateSelectRecognizer();
    }
}

void RenderText::OnPaintFinish()
{
    UpdateOverlay();
#if !defined(PREVIEW)
    UpdateAccessibilityText();
#endif
}

void RenderText::UpdateAccessibilityText()
{
    const auto& context = context_.Upgrade();
    if (!context) {
        return;
    }
    auto viewScale = context->GetViewScale();
    if (NearZero(viewScale)) {
        return;
    }
    auto accessibilityNode = GetAccessibilityNode().Upgrade();
    if (!accessibilityNode) {
        return;
    }
    if (GetChildren().empty()) {
        if (text_) {
            accessibilityNode->SetText(text_->GetData());
        }
    } else {
        std::string accessibilityText;
        for (const auto& child : GetChildren()) {
            auto renderTextSpan = AceType::DynamicCast<RenderTextSpan>(child);
            if (renderTextSpan) {
                accessibilityText += renderTextSpan->GetSpanData();
            }
        }
        accessibilityNode->SetText(accessibilityText);
    }
    if (!accessibilityNode->GetVisible()) { // Set 0 to item when whole outside of view port.
        accessibilityNode->SetWidth(0.0);
        accessibilityNode->SetHeight(0.0);
        accessibilityNode->SetTop(0.0);
        accessibilityNode->SetLeft(0.0);
        return;
    }
    if (accessibilityNode->IsValidRect()) {
        return; // Rect already clamp by viewport, no need to set again.
    }
    Size size = GetLayoutSize();
    Offset globalOffset = GetGlobalOffsetExternal();
    PositionInfo positionInfo = { (size.Width()) * viewScale, (size.Height()) * viewScale,
        (globalOffset.GetX()) * viewScale, (globalOffset.GetY()) * viewScale };
    accessibilityNode->SetPositionInfo(positionInfo);
    accessibilityNode->SetIsMultiLine(GetTextLines() > 1);
}

bool RenderText::IsDeclarativePara()
{
    auto context = context_.Upgrade();
    if (!context) {
        return false;
    }

    return context->GetIsDeclarative();
}

void RenderText::PerformLayout()
{
    // When the constraint is set, minHeight is reset to 0.0,
    // and the occupied height is controlled by the parent node box
    if (IsDeclarativePara()) {
        LayoutParam layoutParam = GetLayoutParam();
        auto minWidth = layoutParam.GetMinSize().Width();
        auto minHeight = layoutParam.GetMinSize().Height();
        if (GreatNotEqual(minHeight, 0.0f)) {
            layoutParam.SetMinSize(Size(minWidth, 0.0f));
            SetLayoutParam(layoutParam);
        }
    }
    auto pipelineContext = GetContext().Upgrade();
    if ((textStyle_.IsAllowScale() || textStyle_.GetFontSize().Unit() == DimensionUnit::FP) && pipelineContext &&
        !NearEqual(fontScale_, pipelineContext->GetFontScale())) {
        needMeasure_ = true;
        fontScale_ = pipelineContext->GetFontScale();
    }
    if (pipelineContext) {
        UpdateIfChanged(dipScale_, pipelineContext->GetDipScale());
    }
    Size size = Measure();
    SetLayoutSize(GetLayoutParam().Constrain(size));
    for (const auto& spanChild : GetChildren()) {
        if (spanChild) {
            const auto& param = GetLayoutParam();
            spanChild->Layout(param);
        }
    }
    textOverlayPaintRect_ = GetPaintRect();
}

bool RenderText::TouchTest(const Point& globalPoint, const Point& parentLocalPoint, const TouchRestrict& touchRestrict,
    TouchTestResult& result)
{
    if (GetDisableTouchEvent() || disabled_) {
        return false;
    }

    // Since the paintRect is relative to parent, use parent local point to perform touch test.
    if (!InTouchRectList(parentLocalPoint, GetTouchRectList())) {
        return false;
    }

    // Reset flag firstly.
    needClickDetector_ = false;
    needLongPressDetector_ = false;
    needTouchDetector_ = false;
    // Calculates the local point location in this node.
    const auto localPoint = parentLocalPoint - GetPaintRect().GetOffset();
    Offset localOffset = Offset(localPoint.GetX(), localPoint.GetY());
    // If span of touch position has click event, need add click detector.
    if (!GetEventMarker(GetTouchPosition(localOffset), GestureType::CLICK).IsEmpty() ||
        !GetEventMarker(GetTouchPosition(localOffset), GestureType::REMOTE_MESSAGE).IsEmpty()) {
        needClickDetector_ = true;
    }
    // If span of touch position has long press event, need add long press detector.
    if (!GetEventMarker(GetTouchPosition(localOffset), GestureType::LONG_PRESS).IsEmpty()) {
        needLongPressDetector_ = true;
    }
    // If span of touch position has touch event, need add touch detector.
    if (!GetEventMarker(GetTouchPosition(localOffset), GestureType::TOUCH_START).IsEmpty() ||
        !GetEventMarker(GetTouchPosition(localOffset), GestureType::TOUCH_MOVE).IsEmpty() ||
        !GetEventMarker(GetTouchPosition(localOffset), GestureType::TOUCH_END).IsEmpty() ||
        !GetEventMarker(GetTouchPosition(localOffset), GestureType::TOUCH_CANCEL).IsEmpty()) {
        needTouchDetector_ = true;
    }
    if (!needClickDetector_ && !needLongPressDetector_ && !needTouchDetector_ && copyOption_ == CopyOptions::None &&
        !onDragStart_) {
        return false;
    }

    auto beforeSize = result.size();
    if (touchable_) {
        // Calculates the coordinate offset in this node.
        const auto coordinateOffset = globalPoint - localPoint;
        globalPoint_ = globalPoint;
        OnTouchTestHit(coordinateOffset, touchRestrict, result);
    }
    auto endSize = result.size();
    return beforeSize != endSize;
}

void RenderText::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if (copyOption_ != CopyOptions::None) {
        if (!textOverlayRecognizer_) {
            textOverlayRecognizer_ = AceType::MakeRefPtr<LongPressRecognizer>(context_);
            textOverlayRecognizer_->SetOnLongPress([weak = WeakClaim(this)](const LongPressInfo& info) {
                auto client = weak.Upgrade();
                if (client) {
                    client->OnLongPress(info);
                }
            });
        }
        textOverlayRecognizer_->SetCoordinateOffset(coordinateOffset);
        textOverlayRecognizer_->SetTouchRestrict(touchRestrict);
        textOverlayRecognizer_->SetUseCatchMode(false);
        result.emplace_back(textOverlayRecognizer_);
    }

    if (onDragStart_) {
        if (!hideTextOverlayRecognizer_) {
            hideTextOverlayRecognizer_ = AceType::MakeRefPtr<ClickRecognizer>();
            hideTextOverlayRecognizer_->SetOnClick([weak = WeakClaim(this)](const ClickInfo& info) {
                auto text = weak.Upgrade();
                if (text && info.GetSourceDevice() == SourceType::MOUSE) {
                    text->HideTextOverlay();
                }
            });
        }
        hideTextOverlayRecognizer_->SetCoordinateOffset(coordinateOffset);
        hideTextOverlayRecognizer_->SetTouchRestrict(touchRestrict);
        result.emplace_back(hideTextOverlayRecognizer_);

        if (touchRestrict.sourceType == SourceType::MOUSE) {
            Offset offset(globalPoint_.GetX(), globalPoint_.GetY());
            if (IsSelectedText(offset, GetGlobalOffset())) {
                result.emplace_back(dragDropGesture_);
            } else {
                result.emplace_back(selectRecognizer_);
            }
        } else {
            auto renderText = AceType::Claim(this);
            if (renderText) {
                SetStartOffset(GetHandleOffset(0));
                SetEndOffset(GetHandleOffset(textValue_.GetWideText().length()));
                textValue_.UpdateSelection(0, textValue_.GetWideText().length());
            }
            result.emplace_back(dragDropGesture_);
        }
    }

    if (GetChildren().empty()) {
        return;
    }

    auto context = context_.Upgrade();
    if (!context) {
        return;
    }

    if (needTouchDetector_) {
        if (!rawRecognizer_) {
            rawRecognizer_ = AceType::MakeRefPtr<RawRecognizer>();
            rawRecognizer_->SetOnTouchDown([weak = WeakClaim(this)](const TouchEventInfo& info) {
                auto text = weak.Upgrade();
                if (text && !info.GetTouches().empty()) {
                    text->HandleTouchEvent(GestureType::TOUCH_START,
                        info.GetTouches().front().GetLocalLocation() - text->GetGlobalOffset());
                }
            });

            rawRecognizer_->SetOnTouchMove([weak = WeakClaim(this)](const TouchEventInfo& info) {
                auto text = weak.Upgrade();
                if (text && !info.GetTouches().empty()) {
                    text->HandleTouchEvent(GestureType::TOUCH_MOVE,
                        info.GetTouches().front().GetLocalLocation() - text->GetGlobalOffset());
                }
            });

            rawRecognizer_->SetOnTouchUp([weak = WeakClaim(this)](const TouchEventInfo& info) {
                auto text = weak.Upgrade();
                if (text && !info.GetTouches().empty()) {
                    text->HandleTouchEvent(
                        GestureType::TOUCH_END, info.GetTouches().front().GetLocalLocation() - text->GetGlobalOffset());
                }
            });

            rawRecognizer_->SetOnTouchCancel([weak = WeakClaim(this)](const TouchEventInfo& info) {
                auto text = weak.Upgrade();
                if (text && !info.GetTouches().empty()) {
                    text->HandleTouchEvent(GestureType::TOUCH_CANCEL,
                        info.GetTouches().front().GetLocalLocation() - text->GetGlobalOffset());
                }
            });
        }
        rawRecognizer_->SetTouchRestrict(touchRestrict);
        rawRecognizer_->SetCoordinateOffset(coordinateOffset);
        result.emplace_back(rawRecognizer_);
        needTouchDetector_ = false;
    }

    if (needClickDetector_) {
        if (!clickDetector_) {
            clickDetector_ = AceType::MakeRefPtr<ClickRecognizer>();
            clickDetector_->SetOnClick([weak = WeakClaim(this)](const ClickInfo& info) {
                auto text = weak.Upgrade();
                if (text) {
                    text->HandleClick(info);
                }
            });
            clickDetector_->SetRemoteMessage([weak = WeakClaim(this)](const ClickInfo& info) {
                auto text = weak.Upgrade();
                if (text) {
                    text->HandleRemoteMessage(info);
                }
            });
        }
        clickDetector_->SetCoordinateOffset(coordinateOffset);
        clickDetector_->SetTouchRestrict(touchRestrict);
        clickDetector_->SetIsExternalGesture(true);
        result.emplace_back(clickDetector_);
        needClickDetector_ = false;
    }

    if (needLongPressDetector_) {
        if (!longPressRecognizer_) {
            longPressRecognizer_ = AceType::MakeRefPtr<LongPressRecognizer>(context_);
            longPressRecognizer_->SetOnLongPress([weak = WeakClaim(this)](const LongPressInfo& info) {
                auto text = weak.Upgrade();
                if (text) {
                    text->HandleLongPress(info.GetLocalLocation());
                }
            });
        }
        longPressRecognizer_->SetCoordinateOffset(coordinateOffset);
        longPressRecognizer_->SetTouchRestrict(touchRestrict);
        result.emplace_back(longPressRecognizer_);
        needLongPressDetector_ = false;
    }
}

void RenderText::HideTextOverlay()
{
    auto textOverlayManager = GetTextOverlayManager(context_);
    if (!textOverlayManager) {
        return;
    }

    auto textOverlayBase = textOverlayManager->GetTextOverlayBase();
    if (!textOverlayBase) {
        return;
    }

    auto targetNode = textOverlayManager->GetTargetNode();
    if (targetNode == this) {
        textOverlayManager->PopTextOverlay();
        textOverlayBase->ChangeSelection(0, 0);
        textOverlayBase->MarkIsOverlayShowed(false);
        targetNode->MarkNeedRender();
    }
}

void RenderText::UpdateTextOverlay()
{
    auto textOverlayManager = GetTextOverlayManager(context_);
    if (!textOverlayManager) {
        return;
    }

    auto textOverlayBase = textOverlayManager->GetTextOverlayBase();
    if (!textOverlayBase) {
        return;
    }

    auto targetNode = textOverlayManager->GetTargetNode();
    if (targetNode == this) {
        targetNode->MarkNeedRender();
    }
}

void RenderText::OnLongPress(const LongPressInfo& longPressInfo)
{
    if (longPressInfo.GetSourceDevice() == SourceType::MOUSE) {
        return;
    }

    auto textOverlayManager = GetTextOverlayManager(context_);
    if (textOverlayManager) {
        auto textOverlayBase = textOverlayManager->GetTextOverlayBase();
        if (textOverlayBase) {
            auto targetNode = textOverlayManager->GetTargetNode();
            if (targetNode) {
                textOverlayManager->PopTextOverlay();
                textOverlayBase->ChangeSelection(0, 0);
                textOverlayBase->MarkIsOverlayShowed(false);
                targetNode->MarkNeedRender();
            }
        }
        textOverlayManager->SetTextOverlayBase(AceType::WeakClaim(this));
    }

    Offset longPressPosition = longPressInfo.GetGlobalLocation();
    auto context = context_.Upgrade();
    if (context) {
        auto isContainerModal = context->GetWindowModal() == WindowModal::CONTAINER_MODAL &&
                                context->GetWindowManager()->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
        if (isContainerModal) {
            longPressPosition =
                longPressPosition + Offset(-(CONTAINER_BORDER_WIDTH.ConvertToPx() + CONTENT_PADDING.ConvertToPx()),
                                           -CONTAINER_TITLE_HEIGHT.ConvertToPx());
        }
    }

    InitSelection(longPressPosition, GetGlobalOffset());
    ShowTextOverlay(longPressPosition, false);
}

bool RenderText::HandleMouseEvent(const MouseEvent& event)
{
    if (copyOption_ == CopyOptions::None) {
        return false;
    }
    if (event.button == MouseButton::RIGHT_BUTTON && event.action == MouseAction::PRESS) {
        Offset rightClickOffset = event.GetOffset();

        auto textOverlayManager = GetTextOverlayManager(context_);
        if (textOverlayManager) {
            auto textOverlayBase = textOverlayManager->GetTextOverlayBase();
            if (textOverlayBase) {
                auto targetNode = textOverlayManager->GetTargetNode();
                if (targetNode) {
                    textOverlayManager->PopTextOverlay();
                    textOverlayBase->ChangeSelection(0, 0);
                    textOverlayBase->MarkIsOverlayShowed(false);
                    targetNode->MarkNeedRender();
                }
            }
            textOverlayManager->SetTextOverlayBase(AceType::WeakClaim(this));
        }
        InitSelection(rightClickOffset, GetGlobalOffset());
        ShowTextOverlay(rightClickOffset, true);
        return true;
    }

    return false;
}

void RenderText::ShowTextOverlay(const Offset& showOffset)
{
    ShowTextOverlay(showOffset, false);
}

void RenderText::ShowTextOverlay(const Offset& showOffset, bool isUsingMouse)
{
    auto selStart = textValue_.selection.GetStart();
    auto selEnd = textValue_.selection.GetEnd();

    Offset startHandleOffset = GetHandleOffset(selStart);
    Offset endHandleOffset = GetHandleOffset(selEnd);

    if (isOverlayShowed_ && updateHandlePosition_) {
        Rect caretStart;
        bool visible =
            GetCaretRect(selStart, caretStart, 0.0) ? IsVisible(caretStart + textOffsetForShowCaret_) : false;
        OverlayShowOption option { .showMenu = isOverlayShowed_,
            .showStartHandle = visible,
            .showEndHandle = visible,
            .isSingleHandle = false,
            .updateOverlayType = UpdateOverlayType::LONG_PRESS,
            .startHandleOffset = startHandleOffset,
            .endHandleOffset = endHandleOffset };
        updateHandlePosition_(option);

        // When the textOverlay is showed, restart the animation
        if (!animator_) {
            LOGE("Show textOverlay error, animator is nullptr");
            return;
        }
        if (!animator_->IsStopped()) {
            animator_->Stop();
        }
        animator_->Play();
        return;
    }

    textOverlay_ =
        AceType::MakeRefPtr<TextOverlayComponent>(GetThemeManager(), context_.Upgrade()->GetAccessibilityManager());
    textOverlay_->SetWeakText(WeakClaim(this));
    textOverlay_->SetLineHeight(selectHeight_);
    Rect paintRect = { Offset::Zero(), GetLayoutParam().GetMaxSize() };
    textOverlay_->SetClipRect(paintRect + Size(HANDLE_HOT_ZONE, HANDLE_HOT_ZONE) + GetOffsetToPage() -
                              Offset(HANDLE_HOT_ZONE / 2.0, 0.0));
    textOverlay_->SetTextDirection(defaultTextDirection_);
    textOverlay_->SetStartHandleOffset(startHandleOffset);
    textOverlay_->SetEndHandleOffset(endHandleOffset);
    textOverlay_->SetContext(context_);
    textOverlay_->SetIsUsingMouse(isUsingMouse);
    if (isUsingMouse) {
        textOverlay_->SetMouseOffset(showOffset);
    }
    // Add the Animation
    InitAnimation(context_);
    RegisterCallbacksToOverlay();
    MarkNeedRender();
}

void RenderText::RegisterCallbacksToOverlay()
{
    if (!textOverlay_) {
        return;
    }

    textOverlay_->SetOnCopy([weak = AceType::WeakClaim(this)] {
        auto text = weak.Upgrade();
        if (text) {
            text->HandleOnCopy();
        }
    });

    textOverlay_->SetOnCopyAll(
        [weak = AceType::WeakClaim(this)](const std::function<void(const Offset&, const Offset&)>& callback) {
            auto text = weak.Upgrade();
            if (text) {
                text->HandleOnCopyAll(callback);
            }
        });

    textOverlay_->SetOnStartHandleMove(
        [weak = AceType::WeakClaim(this)](int32_t end, const Offset& startHandleOffset,
            const std::function<void(const Offset&)>& startCallback, bool isSingleHandle) {
            auto text = weak.Upgrade();
            if (text) {
                text->HandleOnStartHandleMove(end, startHandleOffset, startCallback, isSingleHandle);
            }
        });

    textOverlay_->SetOnEndHandleMove([weak = AceType::WeakClaim(this)](int32_t start, const Offset& endHandleOffset,
                                         const std::function<void(const Offset&)>& endCallback) {
        auto text = weak.Upgrade();
        if (text) {
            text->HandleOnEndHandleMove(start, endHandleOffset, endCallback);
        }
    });

    auto callback = [weak = WeakClaim(this), pipelineContext = context_, textOverlay = textOverlay_](
                        const std::string& data) {
        auto context = pipelineContext.Upgrade();
        if (!context) {
            return;
        }
        auto textOverlayManager = context->GetTextOverlayManager();
        if (!textOverlayManager) {
            return;
        }
        textOverlayManager->PushTextOverlayToStack(textOverlay, pipelineContext);

        auto text = weak.Upgrade();
        if (!text) {
            return;
        }
        text->UpdateOverlay();
        text->MarkIsOverlayShowed(true);
    };
    if (clipboard_) {
        clipboard_->GetData(callback);
    }
}

void RenderText::UpdateOverlay()
{
    // When textfield PerformLayout, update overlay.
    if (isOverlayShowed_ && updateHandlePosition_) {
        auto selStart = textValue_.selection.GetStart();
        auto selEnd = textValue_.selection.GetEnd();
        Rect caretStart;
        Rect caretEnd;
        bool startHandleVisible =
            GetCaretRect(selStart, caretStart, 0.0) ? IsVisible(caretStart + textOffsetForShowCaret_) : false;
        bool endHandleVisible =
            (selStart == selEnd)
                ? startHandleVisible
                : (GetCaretRect(selEnd, caretEnd, 0.0) ? IsVisible(caretEnd + textOffsetForShowCaret_) : false);

        OverlayShowOption option { .showMenu = isOverlayShowed_,
            .showStartHandle = startHandleVisible,
            .showEndHandle = endHandleVisible,
            .isSingleHandle = false,
            .updateOverlayType = UpdateOverlayType::SCROLL,
            .startHandleOffset = GetPositionForExtend(selStart),
            .endHandleOffset = GetPositionForExtend(selEnd) };
        updateHandlePosition_(option);
        if (onClipRectChanged_) {
            Rect paintRect = { Offset::Zero(), GetLayoutParam().GetMaxSize() };
            onClipRectChanged_(paintRect + Size(HANDLE_HOT_ZONE, HANDLE_HOT_ZONE) + GetOffsetToPage() -
                               Offset(HANDLE_HOT_ZONE / 2.0, 0.0));
        }
    }
}

Offset RenderText::GetPositionForExtend(int32_t extend)
{
    if (extend < 0) {
        extend = 0;
    }
    if (static_cast<size_t>(extend) > StringUtils::ToWstring(textValue_.text).length()) {
        extend = static_cast<int32_t>(StringUtils::ToWstring(textValue_.text).length());
    }
    return GetHandleOffset(extend);
}

void RenderText::HandleOnCopy()
{
    if (!clipboard_) {
        return;
    }
    if (textValue_.GetSelectedText().empty()) {
        return;
    }
    clipboard_->SetData(textValue_.GetSelectedText(), copyOption_);

    auto textOverlayManager = GetTextOverlayManager(context_);
    if (textOverlayManager) {
        textOverlayManager->PopTextOverlay();
    }
    isOverlayShowed_ = false;
    textValue_.UpdateSelection(0, 0);
    MarkNeedRender();
}

void RenderText::HandleOnCopyAll(const std::function<void(const Offset&, const Offset&)>& callback)
{
    auto textSize = textValue_.GetWideText().length();
    textValue_.UpdateSelection(0, textSize);
    if (callback) {
        callback(GetPositionForExtend(0), GetPositionForExtend(textValue_.GetWideText().length()));
    }
    MarkNeedRender();
}

void RenderText::HandleOnStartHandleMove(int32_t end, const Offset& startHandleOffset,
    const std::function<void(const Offset&)>& startCallback, bool isSingleHandle)
{
    Offset realOffset = startHandleOffset;
    if (startCallback) {
        UpdateStartSelection(end, realOffset, GetGlobalOffset());
        startCallback(GetHandleOffset(textValue_.selection.GetStart()));
    }
    MarkNeedRender();
}

void RenderText::HandleOnEndHandleMove(
    int32_t start, const Offset& endHandleOffset, const std::function<void(const Offset&)>& endCallback)
{
    Offset realOffset = endHandleOffset;
    if (endCallback) {
        UpdateEndSelection(start, realOffset, GetGlobalOffset());
        endCallback(GetHandleOffset(textValue_.selection.GetEnd()));
    }
    MarkNeedRender();
}

void RenderText::FireEvent(const EventMarker& marker)
{
    if (marker.IsEmpty()) {
        return;
    }

    auto func = AceAsyncEvent<void()>::Create(marker, context_);
    if (func) {
        func();
    }
}

void RenderText::HandleTouchEvent(GestureType type, const Offset& touchPosition)
{
    if (type == GestureType::TOUCH_START) {
        touchStartPosition_ = GetTouchPosition(touchPosition);
    }

    auto eventMarker = GetEventMarker(touchStartPosition_, type);
    if (!eventMarker.IsEmpty()) {
        FireEvent(eventMarker);
        return;
    }

    // If span has not touch event, use touch event of text.
    if (!text_) {
        return;
    }
    auto declaration = text_->GetDeclaration();
    if (!declaration) {
        return;
    }
    auto& rawEvent = static_cast<CommonRawEvent&>(declaration->GetEvent(EventTag::COMMON_RAW_EVENT));
    if (!rawEvent.IsValid()) {
        return;
    }

    switch (type) {
        case GestureType::TOUCH_START:
            eventMarker = rawEvent.touchStart.eventMarker;
            break;
        case GestureType::TOUCH_MOVE:
            eventMarker = rawEvent.touchMove.eventMarker;
            break;
        case GestureType::TOUCH_END:
            eventMarker = rawEvent.touchEnd.eventMarker;
            break;
        case GestureType::TOUCH_CANCEL:
            eventMarker = rawEvent.touchCancel.eventMarker;
            break;
        default:
            break;
    }
    FireEvent(eventMarker);
}

void RenderText::HandleClick(const ClickInfo& info)
{
    auto clickPosition = info.GetLocalLocation();
    auto clickMarker = GetEventMarker(GetTouchPosition(clickPosition), GestureType::CLICK);
    // If span has not click event, use click event of text.
    if (text_ && clickMarker.IsEmpty()) {
        auto declaration = text_->GetDeclaration();
        if (declaration) {
            auto& gestureEvent =
                static_cast<CommonGestureEvent&>(declaration->GetEvent(EventTag::COMMON_GESTURE_EVENT));
            if (gestureEvent.IsValid() && !gestureEvent.click.eventMarker.IsEmpty()) {
                clickMarker = gestureEvent.click.eventMarker;
            }
        }
    }

    auto onClick = AceAsyncEvent<void(const ClickInfo&)>::Create(clickMarker, context_);
    if (onClick) {
        onClick(info);
    }
}

void RenderText::HandleRemoteMessage(const ClickInfo& info)
{
    auto clickPosition = info.GetLocalLocation();
    auto clickMarker = GetEventMarker(GetTouchPosition(clickPosition), GestureType::REMOTE_MESSAGE);
    // If span has not click event, use click event of text.
    if (text_ && clickMarker.IsEmpty()) {
        auto declaration = text_->GetDeclaration();
        if (declaration) {
            auto& gestureEvent =
                static_cast<CommonGestureEvent&>(declaration->GetEvent(EventTag::COMMON_REMOTE_MESSAGE_GESTURE_EVENT));
            if (gestureEvent.IsValid() && !gestureEvent.click.eventMarker.IsEmpty()) {
                clickMarker = gestureEvent.click.eventMarker;
            }
        }
    }

    auto remoteMessage = AceAsyncEvent<void(const ClickInfo&)>::Create(clickMarker, context_);
    if (remoteMessage) {
        remoteMessage(info);
    }
}

void RenderText::HandleLongPress(const Offset& longPressPosition)
{
    auto longPressMarker = GetEventMarker(GetTouchPosition(longPressPosition), GestureType::LONG_PRESS);
    // If span has not long press event, use long press event of text.
    if (text_ && longPressMarker.IsEmpty()) {
        auto declaration = text_->GetDeclaration();
        if (declaration) {
            auto& gestureEvent =
                static_cast<CommonGestureEvent&>(declaration->GetEvent(EventTag::COMMON_GESTURE_EVENT));
            if (gestureEvent.IsValid() && !gestureEvent.longPress.eventMarker.IsEmpty()) {
                longPressMarker = gestureEvent.longPress.eventMarker;
            }
        }
    }

    FireEvent(longPressMarker);
}

EventMarker RenderText::GetEventMarker(int32_t position, GestureType type)
{
    if (touchRegions_.empty()) {
        return EventMarker();
    }
    for (const auto& region : touchRegions_) {
        if (position < region.first) {
            auto markerIter = region.second.find(type);
            if (markerIter != region.second.end()) {
                return markerIter->second;
            }
            return EventMarker();
        }
    }
    return EventMarker();
}

void RenderText::OnStatusChanged(OHOS::Ace::RenderStatus renderStatus)
{
    auto context = context_.Upgrade();
    if (context && context->GetIsDeclarative()) {
        return;
    }

    if (renderStatus == RenderStatus::FOCUS) {
        textStyle_.SetTextColor(focusColor_);
        isFocus_ = true;
    } else {
        textStyle_.SetTextColor(lostFocusColor_);
        isFocus_ = false;
    }
    needMeasure_ = true;
    Measure();
    MarkNeedRender();
}

void RenderText::CheckIfNeedMeasure()
{
    if (!text_) {
        return;
    }

    if (text_->IsChanged()) {
        needMeasure_ = true;
    }
    UpdateIfChanged(defaultTextDirection_, text_->GetTextDirection());
    realTextDirection_ = defaultTextDirection_;
    UpdateIfChanged(textStyle_, text_->GetTextStyle());
    UpdateIfChanged(focusColor_, text_->GetFocusColor());
    UpdateIfChanged(lostFocusColor_, textStyle_.GetTextColor());
    UpdateIfChanged(maxLines_, textStyle_.GetMaxLines());
    if (needMeasure_) {
        MarkNeedLayout();
    }
}

std::string RenderText::GetTextData() const
{
    return text_ ? text_->GetData() : "";
}

void RenderText::SetTextData(const std::string& textData)
{
    if (text_) {
        text_->SetData(textData);
    }
}

void RenderText::ClearRenderObject()
{
    RenderNode::ClearRenderObject();
    text_.Reset();
    textStyle_ = TextStyle();
    defaultTextDirection_ = TextDirection::LTR;
    focusColor_ = Color();
    lostFocusColor_ = Color();
    fontScale_ = 1.0;
    dipScale_ = 1.0;
    isFocus_ = false;
    needMeasure_ = true;
    isCallbackCalled_ = false;
}

Size RenderText::GetContentSize()
{
    if (textStyle_.GetAdaptTextSize()) {
        return Size();
    }
    // Make sure text's height is not clipped, width is not guard.
    auto measuredSize = Measure();
    if (textStyle_.GetTextOverflow() != TextOverflow::NONE || maxLines_ > 1) {
        measuredSize.SetWidth(0.0);
    }
    return measuredSize;
}

RefPtr<Component> RenderText::GetComponent()
{
    return text_;
}

std::string RenderText::GetSelectedContent() const
{
    return textValue_.GetSelectedText();
}

void RenderText::Dump()
{
    DumpLog::GetInstance().AddDesc(std::string("Data: ").append(text_->GetData()));
    DumpLog::GetInstance().AddDesc(std::string("FontColor: ").append(textStyle_.GetTextColor().ColorToString()));
    DumpLog::GetInstance().AddDesc(std::string("FontSize: ").append(textStyle_.GetFontSize().ToString()));
    DumpLog::GetInstance().AddDesc(
        std::string("FontStyle: ").append(V2::ConvertWrapFontStyleToStirng(textStyle_.GetFontStyle())));
    DumpLog::GetInstance().AddDesc(
        std::string("FontWeight: ").append(V2::ConvertWrapFontWeightToStirng(textStyle_.GetFontWeight())));
    std::string fontFamilies;
    for (const auto& family : textStyle_.GetFontFamilies()) {
        fontFamilies += family;
        fontFamilies += ",";
    }
    DumpLog::GetInstance().AddDesc(std::string("FontFamily: ").append(fontFamilies));
    DumpLog::GetInstance().AddDesc(std::string("CopyOptions: ").append(V2::ConvertWrapCopyOptionToString(copyOption_)));
}

DragItemInfo RenderText::GenerateDragItemInfo(const RefPtr<PipelineContext>& context, const GestureEvent& info)
{
    RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
    event->SetX(context->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
    event->SetY(context->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));
    selectedItemSize_ = GetLayoutSize();
    auto extraParams = JsonUtil::Create(true);

    return onDragStart_(event, extraParams->ToString());
}

void RenderText::PanOnActionStart(const GestureEvent& info)
{
    if (!onDragStart_) {
        return;
    }
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Context is null.");
        return;
    }

    GestureEvent newInfo = info;
    Point newPoint = UpdatePoint(pipelineContext, startPoint_);
    newInfo.SetGlobalPoint(newPoint);
    auto dragItemInfo = GenerateDragItemInfo(pipelineContext, newInfo);
#if !defined(PREVIEW)
    if (!dragItemInfo.pixelMap && !dragItemInfo.customComponent) {
        auto initRenderNode = AceType::Claim(this);
        isDragDropNode_ = true;
        pipelineContext->SetInitRenderNode(initRenderNode);

        AddDataToClipboard(pipelineContext, dragItemInfo.extraInfo, textValue_.GetSelectedText(), "");
        if (!dragWindow_) {
            auto rect = pipelineContext->GetCurrentWindowRect();
            dragWindow_ = DragWindow::CreateDragWindow("APP_DRAG_WINDOW",
                static_cast<int32_t>(info.GetGlobalPoint().GetX() + rect.Left()),
                static_cast<int32_t>(info.GetGlobalPoint().GetY() + rect.Top()),
                static_cast<int32_t>(GetPaintRect().Width()),
                static_cast<int32_t>(GetPaintRect().Height()));
            dragWindow_->SetOffset(static_cast<int32_t>(rect.Left()), static_cast<int32_t>(rect.Top()));
            dragWindow_->DrawText(paragraph_, GetPaintRect().GetOffset(), initRenderNode);
        }
        if (dragWindow_) {
            AceEngineExt::GetInstance().DragStartExt();
        }
        return;
    }

    if (dragItemInfo.pixelMap) {
        auto initRenderNode = AceType::Claim(this);
        isDragDropNode_ = true;
        pipelineContext->SetInitRenderNode(initRenderNode);

        AddDataToClipboard(pipelineContext, dragItemInfo.extraInfo, textValue_.GetSelectedText(), "");
        if (!dragWindow_) {
            auto rect = pipelineContext->GetCurrentWindowRect();
            dragWindow_ = DragWindow::CreateDragWindow("APP_DRAG_WINDOW",
                static_cast<int32_t>(info.GetGlobalPoint().GetX()) + rect.Left(),
                static_cast<int32_t>(info.GetGlobalPoint().GetY()) + rect.Top(), dragItemInfo.pixelMap->GetWidth(),
                dragItemInfo.pixelMap->GetHeight());
            dragWindow_->SetOffset(rect.Left(), rect.Top());
            dragWindow_->DrawPixelMap(dragItemInfo.pixelMap);
        }
        if (dragWindow_) {
            AceEngineExt::GetInstance().DragStartExt();
        }
        return;
    }
#endif
    if (!dragItemInfo.customComponent) {
        LOGW("the drag custom component is null");
        return;
    }

    hasDragItem_ = true;
    auto positionedComponent = AceType::MakeRefPtr<PositionedComponent>(dragItemInfo.customComponent);
    positionedComponent->SetTop(Dimension(GetGlobalOffset().GetY()));
    positionedComponent->SetLeft(Dimension(GetGlobalOffset().GetX()));
    SetLocalPoint(startPoint_ - GetGlobalOffset());
    auto updatePosition = [renderBox = AceType::Claim(this)](
                              const std::function<void(const Dimension&, const Dimension&)>& func) {
        if (!renderBox) {
            return;
        }
        renderBox->SetUpdateBuilderFuncId(func);
    };
    positionedComponent->SetUpdatePositionFuncId(updatePosition);
    auto stackElement = pipelineContext->GetLastStack();
    stackElement->PushComponent(positionedComponent);
}

void RenderText::PanOnActionUpdate(const GestureEvent& info)
{
#if !defined(PREVIEW)
    if (isDragDropNode_ && dragWindow_) {
        int32_t x = static_cast<int32_t>(info.GetGlobalPoint().GetX());
        int32_t y = static_cast<int32_t>(info.GetGlobalPoint().GetY());
        if (lastDragMoveOffset_ == Offset(x, y)) {
            return;
        }
        lastDragMoveOffset_ = Offset(x, y);
        if (dragWindow_) {
            dragWindow_->MoveTo(x, y);
        }
        return;
    }
#endif
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Context is null.");
        return;
    }

    RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
    event->SetX(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
    event->SetY(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));

    Offset offset = info.GetGlobalPoint() - GetLocalPoint();
    if (GetUpdateBuilderFuncId()) {
        GetUpdateBuilderFuncId()(Dimension(offset.GetX()), Dimension(offset.GetY()));
    }

    auto extraParams = JsonUtil::Create(true);
    auto targetDragDropNode = FindDragDropNode(pipelineContext, info);
    auto preDragDropNode = GetPreDragDropNode();
    if (preDragDropNode == targetDragDropNode) {
        if (targetDragDropNode && targetDragDropNode->GetOnDragMove()) {
            (targetDragDropNode->GetOnDragMove())(event, extraParams->ToString());
        }
        return;
    }
    if (preDragDropNode && preDragDropNode->GetOnDragLeave()) {
        (preDragDropNode->GetOnDragLeave())(event, extraParams->ToString());
    }
    if (targetDragDropNode && targetDragDropNode->GetOnDragEnter()) {
        (targetDragDropNode->GetOnDragEnter())(event, extraParams->ToString());
    }
    SetPreDragDropNode(targetDragDropNode);
}

void RenderText::PanOnActionEnd(const GestureEvent& info)
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Context is null.");
        return;
    }
#if !defined(PREVIEW)
    if (isDragDropNode_) {
        isDragDropNode_ = false;

        if (GetOnDrop()) {
            RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
            RefPtr<PasteData> pasteData = AceType::MakeRefPtr<PasteData>();
            event->SetPasteData(pasteData);
            event->SetX(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
            event->SetY(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));

            auto extraParams = JsonUtil::Create(true);
            (GetOnDrop())(event, extraParams->ToString());
            pipelineContext->SetInitRenderNode(nullptr);
        }

        auto textfield = FindTargetRenderNode<RenderTextField>(context_.Upgrade(), info);
        if (textfield) {
            auto value = textfield->GetEditingValue();
            value.Append(textValue_.GetSelectedText());
            textfield->SetEditingValue(std::move(value));
        }
        if (info.GetSourceDevice() == SourceType::TOUCH) {
            textValue_.UpdateSelection(0, 0);
        }
        RestoreCilpboardData(pipelineContext);
    }
    
    if (dragWindow_) {
        dragWindow_->Destroy();
        dragWindow_ = nullptr;
        return;
    }
#endif
    RefPtr<DragEvent> event = AceType::MakeRefPtr<DragEvent>();
    RefPtr<PasteData> pasteData = AceType::MakeRefPtr<PasteData>();
    event->SetPasteData(pasteData);
    event->SetX(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetX(), DimensionUnit::PX)));
    event->SetY(pipelineContext->ConvertPxToVp(Dimension(info.GetGlobalPoint().GetY(), DimensionUnit::PX)));

    Offset offset = info.GetGlobalPoint() - GetLocalPoint();
    if (GetUpdateBuilderFuncId()) {
        GetUpdateBuilderFuncId()(Dimension(offset.GetX()), Dimension(offset.GetY()));
    }
    if (hasDragItem_) {
        auto stackElement = pipelineContext->GetLastStack();
        stackElement->PopComponent();
    }
    hasDragItem_ = false;

    ACE_DCHECK(GetPreDragDropNode() == FindTargetRenderNode<DragDropEvent>(pipelineContext, info));
    auto targetDragDropNode = GetPreDragDropNode();
    if (!targetDragDropNode) {
        return;
    }
    if (targetDragDropNode->GetOnDrop()) {
        auto extraParams = JsonUtil::Create(true);
        (targetDragDropNode->GetOnDrop())(event, extraParams->ToString());
    }
    SetPreDragDropNode(nullptr);
}

void RenderText::PanOnActionCancel()
{
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        LOGE("Context is null.");
        return;
    }

#if !defined(PREVIEW)
    if (isDragDropNode_) {
        isDragDropNode_ = false;
        RestoreCilpboardData(pipelineContext);
    }

    if (dragWindow_) {
        dragWindow_->Destroy();
        dragWindow_ = nullptr;
    }
#endif
    if (hasDragItem_) {
        auto stackElement = pipelineContext->GetLastStack();
        stackElement->PopComponent();
        hasDragItem_ = false;
    }
    SetPreDragDropNode(nullptr);
}

void RenderText::CreateSelectRecognizer()
{
    if (selectRecognizer_) {
        return;
    }

    auto context = context_.Upgrade();
    if (!context) {
        return;
    }

    PanDirection panDirection;
    selectRecognizer_ = AceType::MakeRefPtr<OHOS::Ace::PanRecognizer>(context, 1, panDirection, 0);
    selectRecognizer_->SetOnActionStart([weak = WeakClaim(this), context = context_](const GestureEvent& info) {
        if (info.GetSourceDevice() != SourceType::MOUSE) {
            return;
        }

        auto text = weak.Upgrade();
        if (text) {
            text->HideTextOverlay();
            auto textOverlayManager = text->GetTextOverlayManager(context);
            if (textOverlayManager) {
                textOverlayManager->SetTextOverlayBase(weak);
            }
            Offset offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY());
            text->InitSelection(offset, text->GetGlobalOffset());
        }
    });
    selectRecognizer_->SetOnActionUpdate([weak = WeakClaim(this), context = context_](const GestureEvent& info) {
        if (info.GetSourceDevice() != SourceType::MOUSE) {
            return;
        }

        auto text = weak.Upgrade();
        if (text) {
            Offset offset(info.GetGlobalPoint().GetX(), info.GetGlobalPoint().GetY());
            text->UpdateEndSelection(text->GetTextSelect().baseOffset, offset, text->GetGlobalOffset());
            text->SetStartOffset(text->GetHandleOffset(text->GetTextSelect().GetStart()));
            text->SetEndOffset(text->GetHandleOffset(text->GetTextSelect().GetEnd()));
            text->UpdateTextOverlay();
        }
    });
}

} // namespace OHOS::Ace
