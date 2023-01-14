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

const Color DEFAULT_PLACEHOLD_COLOR = Color::GRAY;
constexpr int32_t TEXTFIELD_INDEX = 0;
constexpr int32_t IMAGE_INDEX = 1;
constexpr int32_t CANCEL_BUTTON_INDEX = 3;
constexpr int32_t BUTTON_INDEX = 4;
// The focus state requires an 2vp inner stroke, which should be indented by 1vp when drawn.
constexpr Dimension FOCUS_OFFSET = 1.0_vp;
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
        } else if (focusChoice_ == FocusChoice::SEARCH_BUTTON) {
            if (NearZero(cancelButtonSize_.Height())) {
                focusChoice_ = FocusChoice::SEARCH;
            } else {
                focusChoice_ = FocusChoice::CANCEL_BUTTON;
            }
        }
        PaintFocusState();
        return true;
    }
    if (event.code == KeyCode::KEY_DPAD_RIGHT || event.code == KeyCode::KEY_TAB) {
        if (focusChoice_ == FocusChoice::SEARCH) {
            if (NearZero(cancelButtonSize_.Height())) {
                focusChoice_ = FocusChoice::SEARCH_BUTTON;
            } else {
                focusChoice_ = FocusChoice::CANCEL_BUTTON;
            }
        } else if (focusChoice_ == FocusChoice::CANCEL_BUTTON) {
            focusChoice_ = FocusChoice::SEARCH_BUTTON;
        }
        PaintFocusState();
        return true;
    }
    return false;
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
        originX = searchOffset_.GetX();
        originY = searchOffset_.GetY();
        endX = searchSize_.Width() + originX;
        endY = searchSize_.Height() + originY;
        radius = searchSize_.Height() / 2.0;
    }
    if (focusChoice_ == FocusChoice::CANCEL_BUTTON) {
        originX = cancelButtonOffset_.GetX() + focusOffset;
        originY = cancelButtonOffset_.GetY() + focusOffset;
        endX = cancelButtonSize_.Width() + originX - 2 * focusOffset;
        endY = cancelButtonSize_.Height() + originY - 2 * focusOffset;
        radius = cancelButtonSize_.Height() / 2.0;
    }
    if (focusChoice_ == FocusChoice::SEARCH_BUTTON) {
        originX = buttonOffset_.GetX() + focusOffset;
        originY = buttonOffset_.GetY() + focusOffset;
        endX = buttonSize_.Width() + originX - 2 * focusOffset;
        endY = buttonSize_.Height() + originY - 2 * focusOffset;
        radius = buttonSize_.Height() / 2.0;
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
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            searchPattern->OnTouchDown();
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
            searchPattern->OnTouchUp();
        }
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
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
    auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(isHover);
        }
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(mouseEvent_);
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
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);
    auto touchColor = theme->GetTouchColor();
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->BlendBgColor(touchColor);
}

void SearchPattern::OnTouchUp()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->ResetBlendBgColor();
}

void SearchPattern::HandleMouseEvent(bool isHover)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);
    auto hoverColor = theme->GetHoverColor();
    if (isHover) {
        renderContext->BlendBgColor(hoverColor);
    } else {
        renderContext->ResetBlendBgColor();
    }
}

void SearchPattern::HandleButtonMouseEvent(bool isHover, int32_t childId)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(childId));
    CHECK_NULL_VOID(buttonFrameNode);
    auto renderContext = buttonFrameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(theme);
    auto hoverColor = theme->GetHoverColor();
    if (isHover) {
        renderContext->BlendBgColor(hoverColor);
    } else {
        renderContext->ResetBlendBgColor();
    }
}

void SearchPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    Pattern::ToJsonValue(json);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto placeHoldColor = textFieldLayoutProperty->GetPlaceholderTextColor();
    json->Put("placeholderColor", placeHoldColor.value_or(DEFAULT_PLACEHOLD_COLOR).ColorToString().c_str());

    auto imageFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(IMAGE_INDEX));
    CHECK_NULL_VOID(imageFrameNode);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto icon = imageLayoutProperty->GetImageSourceInfo()->GetSrc();
    json->Put("icon", icon.c_str());
}

} // namespace OHOS::Ace::NG
