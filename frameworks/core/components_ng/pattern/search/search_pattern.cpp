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

#include "core/components_ng/pattern/search/search_pattern.h"

#include "core/components/search/search_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t TEXTFIELD_INDEX = 0;
constexpr int32_t IMAGE_INDEX = 1;
constexpr int32_t CANCEL_BUTTON_INDEX = 3;
constexpr int32_t BUTTON_INDEX = 4;
// The focus state requires an 2vp inner stroke, which should be indented by 1vp when drawn.
constexpr Dimension FOCUS_OFFSET = 1.0_vp;
constexpr Dimension UP_AND_DOWN_PADDING = 8.0_vp;
constexpr float HOVER_OPACITY = 0.05f;
constexpr float TOUCH_OPACITY = 0.1f;
constexpr int32_t HOVER_TO_TOUCH_DURATION = 100;
constexpr int32_t HOVER_DURATION = 250;
constexpr int32_t TOUCH_DURATION = 250;
} // namespace

bool SearchPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& /*config*/)
{
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, true);
    searchSize_ = geometryNode->GetContentSize();
    searchOffset_ = geometryNode->GetContentOffset();

    auto buttonLayoutWrapper = dirty->GetOrCreateChildByIndex(BUTTON_INDEX);
    CHECK_NULL_RETURN(buttonLayoutWrapper, true);
    auto buttonGeometryNode = buttonLayoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(buttonGeometryNode, true);
    buttonSize_ = buttonGeometryNode->GetFrameSize();
    buttonOffset_ = buttonGeometryNode->GetFrameOffset();

    auto cancelButtonLayoutWrapper = dirty->GetOrCreateChildByIndex(CANCEL_BUTTON_INDEX);
    CHECK_NULL_RETURN(cancelButtonLayoutWrapper, true);
    auto cancelButtonGeometryNode = cancelButtonLayoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(cancelButtonGeometryNode, true);
    cancelButtonSize_ = cancelButtonGeometryNode->GetFrameSize();
    cancelButtonOffset_ = cancelButtonGeometryNode->GetFrameOffset();
    return true;
}

void SearchPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<SearchLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->GetMarginProperty()) {
        MarginProperty margin;
        margin.top = CalcLength(UP_AND_DOWN_PADDING.ConvertToPx());
        margin.bottom = CalcLength(UP_AND_DOWN_PADDING.ConvertToPx());
        layoutProperty->UpdateMargin(margin);
    }
    auto searchButton = layoutProperty->GetSearchButton();
    searchButton_ = searchButton.has_value() ? searchButton->value() : "";
    InitSearchController();
    auto imageFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(IMAGE_INDEX));
    CHECK_NULL_VOID(imageFrameNode);
    imageFrameNode->MarkModifyDone();
    auto buttonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(buttonFrameNode);
    auto buttonLayoutProperty = buttonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    buttonLayoutProperty->UpdateLabel(searchButton_);
    buttonFrameNode->MarkModifyDone();

    auto cancelButtonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    CHECK_NULL_VOID(cancelButtonFrameNode);
    auto cancelButtonLayoutProperty = cancelButtonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(cancelButtonLayoutProperty);
    cancelButtonLayoutProperty->UpdateLabel("");
    cancelButtonFrameNode->MarkModifyDone();

    InitButtonAndImageClickEvent();
    InitCancelButtonClickEvent();
    InitTouchEvent();
    InitMouseEvent();
    InitButtonMouseEvent(searchButtonMouseEvent_, BUTTON_INDEX);
    InitButtonMouseEvent(cancelButtonMouseEvent_, CANCEL_BUTTON_INDEX);
    InitButtonTouchEvent(searchButtonTouchListener_, BUTTON_INDEX);
    InitButtonTouchEvent(cancelButtonTouchListener_, CANCEL_BUTTON_INDEX);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);
}

void SearchPattern::InitButtonAndImageClickEvent()
{
    // Image click event
    if (imageClickListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto imageFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(IMAGE_INDEX));
    CHECK_NULL_VOID(imageFrameNode);
    CHECK_NULL_VOID_NOLOG(!imageClickListener_);
    auto imageGesture = imageFrameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(imageGesture);
    auto imageClickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto searchPattern = weak.Upgrade();
        CHECK_NULL_VOID(searchPattern);
        searchPattern->OnClickButtonAndImage();
    };
    imageClickListener_ = MakeRefPtr<ClickEvent>(std::move(imageClickCallback));
    imageGesture->AddClickEvent(imageClickListener_);
    // Button click event
    if (buttonClickListener_) {
        return;
    }
    auto buttonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(buttonFrameNode);
    CHECK_NULL_VOID_NOLOG(!buttonClickListener_);
    auto buttonGesture = buttonFrameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(buttonGesture);
    auto buttonClickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto searchPattern = weak.Upgrade();
        CHECK_NULL_VOID(searchPattern);
        searchPattern->OnClickButtonAndImage();
    };
    buttonClickListener_ = MakeRefPtr<ClickEvent>(std::move(buttonClickCallback));
    buttonGesture->AddClickEvent(buttonClickListener_);
}

void SearchPattern::InitCancelButtonClickEvent()
{
    // CancelButton click event
    if (cancelButtonClickListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto cancelButtonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    CHECK_NULL_VOID(cancelButtonFrameNode);
    auto cancelButtonGesture = cancelButtonFrameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(cancelButtonGesture);
    auto cancelButtonClickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto searchPattern = weak.Upgrade();
        CHECK_NULL_VOID(searchPattern);
        searchPattern->OnClickCancelButton();
    };
    cancelButtonClickListener_ = MakeRefPtr<ClickEvent>(std::move(cancelButtonClickCallback));
    cancelButtonGesture->AddClickEvent(cancelButtonClickListener_);
}

void SearchPattern::InitSearchController()
{
    searchController_->SetCaretPosition([weak = WeakClaim(this)](int32_t caretPosition) {
        auto search = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(search);
        search->HandleCaretPosition(caretPosition);
    });
}

void SearchPattern::HandleCaretPosition(int32_t caretPosition)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->SetCaretPosition(caretPosition);
}

void SearchPattern::OnClickButtonAndImage()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto searchEventHub = host->GetEventHub<SearchEventHub>();
    CHECK_NULL_VOID(searchEventHub);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    auto text = textFieldPattern->GetEditingValue();
    searchEventHub->UpdateSubmitEvent(text.text);
    textFieldPattern->CloseKeyboard(true);
}

void SearchPattern::OnClickCancelButton()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->InitEditingValueText("");
    textFieldPattern->InitCaretPosition("");
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateValue("");
    auto eventHub = host->GetEventHub<SearchEventHub>();
    eventHub->UpdateChangeEvent("");
    host->MarkModifyDone();
    textFieldFrameNode->MarkModifyDone();
}

void SearchPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));

    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        if (pattern) {
            pattern->GetInnerFocusPaintRect(paintRect);
        }
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);
}

bool SearchPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }

    // If the focus is on the search, press Enter to request keyboard.
    if (event.code == KeyCode::KEY_ENTER && focusChoice_ == FocusChoice::SEARCH) {
        RequestKeyboard();
        return true;
    }
    // If the focus is on the search button, press Enter to submit the content.
    if (event.code == KeyCode::KEY_ENTER && focusChoice_ == FocusChoice::SEARCH_BUTTON) {
        OnClickButtonAndImage();
        return true;
    }
    // If the focus is on the Delete button, press Enter to delete the content.
    if (event.code == KeyCode::KEY_ENTER && focusChoice_ == FocusChoice::CANCEL_BUTTON) {
        OnClickCancelButton();
        focusChoice_ = FocusChoice::SEARCH;
        PaintFocusState();
        return true;
    }
    // When press '->' or '<-', focus delete button or search button according to whether there is text in the search.
    if (event.code == KeyCode::KEY_DPAD_LEFT || event.IsShiftWith(KeyCode::KEY_TAB)) {
        if (focusChoice_ == FocusChoice::CANCEL_BUTTON) {
            focusChoice_ = FocusChoice::SEARCH;
            PaintFocusState();
            return true;
        }
        if (focusChoice_ == FocusChoice::SEARCH_BUTTON) {
            if (NearZero(cancelButtonSize_.Height())) {
                focusChoice_ = FocusChoice::SEARCH;
            } else {
                focusChoice_ = FocusChoice::CANCEL_BUTTON;
            }
            PaintFocusState();
            return true;
        }
    }
    if (event.code == KeyCode::KEY_DPAD_RIGHT || (event.pressedCodes.size() == 1 && event.code == KeyCode::KEY_TAB)) {
        if (focusChoice_ == FocusChoice::SEARCH) {
            if (NearZero(cancelButtonSize_.Height())) {
                focusChoice_ = FocusChoice::SEARCH_BUTTON;
            } else {
                focusChoice_ = FocusChoice::CANCEL_BUTTON;
            }
            PaintFocusState();
            return true;
        }
        if (focusChoice_ == FocusChoice::CANCEL_BUTTON) {
            focusChoice_ = FocusChoice::SEARCH_BUTTON;
            PaintFocusState();
            return true;
        }
    }

    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_RETURN(textFieldFrameNode, false);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, false);

    return textFieldPattern->OnKeyEvent(event);
}

void SearchPattern::PaintFocusState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RoundRect focusRect;
    GetInnerFocusPaintRect(focusRect);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->PaintInnerFocusState(focusRect);
    host->MarkModifyDone();
}

void SearchPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    float originX = 0.0f;
    float originY = 0.0f;
    float endX = 0.0f;
    float endY = 0.0f;
    float radius = 0.0f;
    float focusOffset = FOCUS_OFFSET.ConvertToPx();
    if (focusChoice_ == FocusChoice::SEARCH) {
        originX = searchOffset_.GetX() + focusOffset;
        originY = searchOffset_.GetY() + focusOffset;
        endX = searchSize_.Width() + originX - 2 * focusOffset;
        endY = searchSize_.Height() + originY - 2 * focusOffset;
        radius = searchSize_.Height() / 2.0 - focusOffset;
    }
    if (focusChoice_ == FocusChoice::CANCEL_BUTTON) {
        originX = cancelButtonOffset_.GetX() + focusOffset;
        originY = cancelButtonOffset_.GetY() + focusOffset;
        endX = cancelButtonSize_.Width() + originX - 2 * focusOffset;
        endY = cancelButtonSize_.Height() + originY - 2 * focusOffset;
        radius = cancelButtonSize_.Height() / 2.0 - focusOffset;
    }
    if (focusChoice_ == FocusChoice::SEARCH_BUTTON) {
        originX = buttonOffset_.GetX() + focusOffset;
        originY = buttonOffset_.GetY() + focusOffset;
        endX = buttonSize_.Width() + originX - 2 * focusOffset;
        endY = buttonSize_.Height() + originY - 2 * focusOffset;
        radius = buttonSize_.Height() / 2.0 - focusOffset;
    }

    paintRect.SetRect({ originX, originY, endX - originX, endY - originY });
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, radius, radius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, radius, radius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, radius, radius);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, radius, radius);
}

FocusPattern SearchPattern::GetFocusPattern() const
{
    return { FocusType::NODE, true, FocusStyleType::CUSTOM_REGION };
}

void SearchPattern::RequestKeyboard()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    textFieldPattern->SearchRequestKeyboard();
}

void SearchPattern::InitTouchEvent()
{
    if (touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto searchPattern = weak.Upgrade();
        CHECK_NULL_VOID(searchPattern);
        auto touchType = info.GetTouches().front().GetTouchType();
        auto touchLocalPosition = info.GetTouches().front().GetLocalLocation();
        auto touchPoint = PointF(touchLocalPosition.GetX(), touchLocalPosition.GetY());
        RectF cancelRect(searchPattern->cancelButtonOffset_, searchPattern->cancelButtonSize_);
        RectF searchRect(searchPattern->buttonOffset_, searchPattern->buttonSize_);
        if (touchType == TouchType::DOWN && !cancelRect.IsInRegion(touchPoint) && !searchRect.IsInRegion(touchPoint)) {
            searchPattern->OnTouchDown();
        }
        if (touchType == TouchType::UP && !cancelRect.IsInRegion(touchPoint) && !searchRect.IsInRegion(touchPoint)) {
            searchPattern->OnTouchUp();
        }
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void SearchPattern::InitButtonTouchEvent(RefPtr<TouchEventImpl>& touchEvent, int32_t childId)
{
    if (touchEvent) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(childId));
    CHECK_NULL_VOID(buttonFrameNode);
    auto gesture = buttonFrameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto eventHub = buttonFrameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetStateEffect(false);
    auto touchTask = [weak = WeakClaim(this), childId](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto touchType = info.GetTouches().front().GetTouchType();
        if (touchType == TouchType::DOWN) {
            pattern->OnButtonTouchDown(childId);
        }
        if (touchType == TouchType::UP) {
            pattern->OnButtonTouchUp(childId);
        }
    };
    touchEvent = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gesture->AddTouchEvent(touchEvent);
}

void SearchPattern::InitMouseEvent()
{
    if (mouseEvent_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<SearchEventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    auto hoverTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleHoverEvent(isHover);
        }
    };

    auto mouseTask = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(info);
        }
    };

    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverTask));
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(hoverEvent_);
    inputHub->AddOnMouseEvent(mouseEvent_);
}

void SearchPattern::InitButtonMouseEvent(RefPtr<InputEvent>& inputEvent, int32_t childId)
{
    if (inputEvent) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(childId));
    CHECK_NULL_VOID(buttonFrameNode);
    auto eventHub = buttonFrameNode->GetEventHub<ButtonEventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();

    auto mouseTask = [weak = WeakClaim(this), childId](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleButtonMouseEvent(isHover, childId);
        }
    };
    inputEvent = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(inputEvent);
}

void SearchPattern::OnTouchDown()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (isHover_) {
        AnimateTouchAndHover(renderContext, HOVER_OPACITY, TOUCH_OPACITY, HOVER_TO_TOUCH_DURATION, Curves::SHARP);
    } else {
        AnimateTouchAndHover(renderContext, 0.0f, TOUCH_OPACITY, TOUCH_DURATION, Curves::FRICTION);
    }
}

void SearchPattern::OnTouchUp()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (isHover_) {
        AnimateTouchAndHover(renderContext, TOUCH_OPACITY, HOVER_OPACITY, HOVER_TO_TOUCH_DURATION, Curves::SHARP);
    } else {
        AnimateTouchAndHover(renderContext, TOUCH_OPACITY, 0.0f, TOUCH_DURATION, Curves::FRICTION);
    }
}

void SearchPattern::OnButtonTouchDown(int32_t childId)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(childId));
    CHECK_NULL_VOID(buttonFrameNode);
    auto renderContext = buttonFrameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (childId == CANCEL_BUTTON_INDEX ? isCancelButtonHover_ : isSearchButtonHover_) {
        AnimateTouchAndHover(renderContext, HOVER_OPACITY, TOUCH_OPACITY, HOVER_TO_TOUCH_DURATION, Curves::SHARP);
    } else {
        AnimateTouchAndHover(renderContext, 0.0f, TOUCH_OPACITY, TOUCH_DURATION, Curves::FRICTION);
    }
}

void SearchPattern::OnButtonTouchUp(int32_t childId)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(childId));
    CHECK_NULL_VOID(buttonFrameNode);
    auto renderContext = buttonFrameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (childId == CANCEL_BUTTON_INDEX ? isCancelButtonHover_ : isSearchButtonHover_) {
        AnimateTouchAndHover(renderContext, TOUCH_OPACITY, HOVER_OPACITY, HOVER_TO_TOUCH_DURATION, Curves::SHARP);
    } else {
        AnimateTouchAndHover(renderContext, TOUCH_OPACITY, 0.0f, TOUCH_DURATION, Curves::FRICTION);
    }
}

void SearchPattern::HandleHoverEvent(bool isHover)
{
    isHover_ = isHover;
    if (!isHover) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->AnimateHoverEffectBoard(false);
    }
}

void SearchPattern::HandleMouseEvent(const MouseInfo& info)
{
    const auto& mousePosition = info.GetLocalLocation();
    PointF mousePoint(mousePosition.GetX(), mousePosition.GetY());
    RectF cancelRect(cancelButtonOffset_, cancelButtonSize_);
    RectF searchRect(buttonOffset_, buttonSize_);
    auto isMouseInCancelButton = cancelRect.IsInRegion(mousePoint);
    auto isMouseInSearchButton = searchRect.IsInRegion(mousePoint);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (isHover_ && !isMouseInCancelButton && !isMouseInSearchButton) {
        renderContext->AnimateHoverEffectBoard(true);
    } else {
        renderContext->AnimateHoverEffectBoard(false);
    }
}

void SearchPattern::HandleButtonMouseEvent(bool isHover, int32_t childId)
{
    if (childId == CANCEL_BUTTON_INDEX) {
        isCancelButtonHover_ = isHover;
    } else {
        isSearchButtonHover_ = isHover;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(childId));
    CHECK_NULL_VOID(buttonFrameNode);
    auto renderContext = buttonFrameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (isHover) {
        AnimateTouchAndHover(renderContext, 0.0f, HOVER_OPACITY, HOVER_DURATION, Curves::FRICTION);
    } else {
        AnimateTouchAndHover(renderContext, HOVER_OPACITY, 0.0f, HOVER_DURATION, Curves::FRICTION);
    }
}

void SearchPattern::AnimateTouchAndHover(RefPtr<RenderContext>& renderContext, float startOpacity, float endOpacity,
    int32_t duration, const RefPtr<Curve>& curve)
{
    Color touchColorFrom = Color::FromRGBO(0, 0, 0, startOpacity);
    Color touchColorTo = Color::FromRGBO(0, 0, 0, endOpacity);
    Color highlightStart = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT).BlendColor(touchColorFrom);
    Color highlightEnd = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT).BlendColor(touchColorTo);
    renderContext->OnBackgroundColorUpdate(highlightStart);
    AnimationOption option = AnimationOption();
    option.SetDuration(duration);
    option.SetCurve(curve);
    AnimationUtils::Animate(
        option, [renderContext, highlightEnd]() { renderContext->OnBackgroundColorUpdate(highlightEnd); });
}

bool SearchPattern::HandleInputChildOnFocus() const
{
#if !defined(PREVIEW)
    return false;
#endif
    auto focusHub = GetHost()->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();
    return true;
}

void SearchPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    Pattern::ToJsonValue(json);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    json->Put("value", textFieldPattern->GetTextEditingValue().text.c_str());
    json->Put("placeholderColor", textFieldPattern->GetPlaceholderColor().c_str());
    json->Put("placeholderFont", textFieldPattern->GetPlaceholderFont().c_str());
    json->Put("textAlign", V2::ConvertWrapTextAlignToString(textFieldPattern->GetTextAlign()).c_str());
    auto textFontJson = JsonUtil::Create(true);
    textFontJson->Put("fontSize", textFieldPattern->GetFontSize().c_str());
    textFontJson->Put("fontStyle",
        textFieldPattern->GetItalicFontStyle() == Ace::FontStyle::NORMAL ? "FontStyle.Normal" : "FontStyle.Italic");
    textFontJson->Put("fontWeight", V2::ConvertWrapFontWeightToStirng(textFieldPattern->GetFontWeight()).c_str());
    textFontJson->Put("fontFamily", textFieldPattern->GetFontFamily().c_str());
    json->Put("textFont", textFontJson->ToString().c_str());
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    json->Put("copyOption",
        ConvertCopyOptionsToString(textFieldLayoutProperty->GetCopyOptionsValue(CopyOptions::None)).c_str());
    textFieldLayoutProperty->HasCopyOptions();

    auto imageFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(IMAGE_INDEX));
    CHECK_NULL_VOID(imageFrameNode);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto icon = imageLayoutProperty->GetImageSourceInfo()->GetSrc();
    json->Put("icon", icon.c_str());
}

} // namespace OHOS::Ace::NG
