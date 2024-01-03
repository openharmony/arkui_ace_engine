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

#include "core/components_ng/pattern/search/search_pattern.h"

#include <cstdint>

#include "base/geometry/rect.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components/search/search_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/search/search_model.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t TEXTFIELD_INDEX = 0;
constexpr int32_t IMAGE_INDEX = 1;
constexpr int32_t CANCEL_IMAGE_INDEX = 2;
constexpr int32_t CANCEL_BUTTON_INDEX = 3;
constexpr int32_t BUTTON_INDEX = 4;
constexpr int32_t DOUBLE = 2;
constexpr int32_t ERROR = -1;

// The focus state requires an 2vp inner stroke, which should be indented by 1vp when drawn.
constexpr Dimension FOCUS_OFFSET = 1.0_vp;
constexpr Dimension UP_AND_DOWN_PADDING = 8.0_vp;
constexpr float HOVER_OPACITY = 0.05f;
constexpr float TOUCH_OPACITY = 0.1f;
constexpr int32_t HOVER_TO_TOUCH_DURATION = 100;
constexpr int32_t HOVER_DURATION = 250;
constexpr int32_t TOUCH_DURATION = 250;
} // namespace

void SearchPattern::UpdateChangeEvent(const std::string& value)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto buttonHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    CHECK_NULL_VOID(buttonHost);
    auto imageHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    CHECK_NULL_VOID(imageHost);
    auto cancelButtonRenderContext = buttonHost->GetRenderContext();
    CHECK_NULL_VOID(cancelButtonRenderContext);
    auto cancelImageRenderContext = imageHost->GetRenderContext();
    CHECK_NULL_VOID(cancelImageRenderContext);
    auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto cancelButtonEvent = buttonHost->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(cancelButtonEvent);
    auto imageEvent = imageHost->GetEventHub<ImageEventHub>();
    CHECK_NULL_VOID(imageEvent);

    auto style = layoutProperty->GetCancelButtonStyle().value_or(CancelButtonStyle::INPUT);
    if ((style == CancelButtonStyle::CONSTANT) || ((style == CancelButtonStyle::INPUT) && !value.empty())) {
        cancelButtonRenderContext->UpdateOpacity(1.0);
        cancelImageRenderContext->UpdateOpacity(1.0);
        cancelButtonEvent->SetEnabled(true);
        imageEvent->SetEnabled(true);
    } else {
        cancelButtonRenderContext->UpdateOpacity(0.0);
        cancelImageRenderContext->UpdateOpacity(0.0);
        cancelButtonEvent->SetEnabled(false);
        imageEvent->SetEnabled(false);
    }
    buttonHost->MarkModifyDone();
    imageHost->MarkModifyDone();
    buttonHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    imageHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

bool SearchPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& /*config*/)
{
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, true);
    searchSize_ = geometryNode->GetContentSize();
    searchOffset_ = geometryNode->GetContentOffset();

    auto textFieldLayoutWrapper = dirty->GetOrCreateChildByIndex(TEXTFIELD_INDEX);
    CHECK_NULL_RETURN(textFieldLayoutWrapper, true);
    auto textFieldGeometryNode = textFieldLayoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(textFieldGeometryNode, true);
    textFieldOffset_ = textFieldGeometryNode->GetFrameOffset();
    textFieldSize_ = textFieldGeometryNode->GetFrameSize();

    auto buttonLayoutWrapper = dirty->GetOrCreateChildByIndex(BUTTON_INDEX);
    CHECK_NULL_RETURN(buttonLayoutWrapper, true);
    auto buttonGeometryNode = buttonLayoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(buttonGeometryNode, true);
    buttonOffset_ = buttonGeometryNode->GetFrameOffset();

    auto buttonNode = buttonLayoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(buttonNode, true);
    auto searchButtonEvent = buttonNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(searchButtonEvent, true);

    if (!searchButtonEvent->IsEnabled()) {
        buttonSize_.Reset();
    } else {
        buttonSize_ = buttonGeometryNode->GetFrameSize();
    }

    auto cancelButtonLayoutWrapper = dirty->GetOrCreateChildByIndex(CANCEL_BUTTON_INDEX);
    CHECK_NULL_RETURN(cancelButtonLayoutWrapper, true);
    auto cancelButtonGeometryNode = cancelButtonLayoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(cancelButtonGeometryNode, true);

    auto cancelButtonNode = cancelButtonLayoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(cancelButtonNode, true);
    auto cancelButtonEvent = cancelButtonNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(cancelButtonEvent, true);
    cancelButtonOffset_ = cancelButtonGeometryNode->GetFrameOffset();
    if (!cancelButtonEvent->IsEnabled()) {
        cancelButtonSize_.Reset();
    } else {
        cancelButtonSize_ = cancelButtonGeometryNode->GetFrameSize();
    }

    return true;
}

void SearchPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
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
    buttonLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    buttonFrameNode->MarkModifyDone();

    auto searchButtonEvent = buttonFrameNode->GetEventHub<ButtonEventHub>();
    isSearchButtonEnabled_ = searchButtonEvent->IsEnabled();

    auto cancelButtonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    CHECK_NULL_VOID(cancelButtonFrameNode);
    auto cancelButtonLayoutProperty = cancelButtonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(cancelButtonLayoutProperty);
    cancelButtonLayoutProperty->UpdateLabel("");
    cancelButtonFrameNode->MarkModifyDone();

    HandleEnabled();

    InitButtonAndImageClickEvent();
    InitCancelButtonClickEvent();
    InitTextFieldValueChangeEvent();
    InitTextFieldDragEvent();
    InitTextFieldClickEvent();
    InitButtonMouseAndTouchEvent();
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);
    InitFocusEvent(focusHub);
    InitClickEvent();
}

void SearchPattern::HandleEnabled()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto searchEventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(searchEventHub);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto eventHub = textFieldFrameNode->GetEventHub<TextFieldEventHub>();
    eventHub->SetEnabled(searchEventHub->IsEnabled()? true : false);
    textFieldFrameNode->MarkModifyDone();
}

void SearchPattern::InitButtonMouseAndTouchEvent()
{
    InitButtonMouseEvent(searchButtonMouseEvent_, BUTTON_INDEX);
    InitButtonMouseEvent(cancelButtonMouseEvent_, CANCEL_BUTTON_INDEX);
    InitButtonTouchEvent(searchButtonTouchListener_, BUTTON_INDEX);
    InitButtonTouchEvent(cancelButtonTouchListener_, CANCEL_BUTTON_INDEX);
}

void SearchPattern::InitTextFieldValueChangeEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_VOID(textFieldFrameNode);
    auto eventHub = textFieldFrameNode->GetEventHub<TextFieldEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (!eventHub->GetOnChange()) {
        auto searchChangeFunc = [weak = AceType::WeakClaim(this)](const std::string& value) {
            auto searchPattern = weak.Upgrade();
            searchPattern->UpdateChangeEvent(value);
        };
        eventHub->SetOnChange(std::move(searchChangeFunc));
    }
}

void SearchPattern::InitTextFieldDragEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto searchEventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(searchEventHub);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldEventHub = textFieldFrameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(textFieldEventHub);

    auto dragStart = searchEventHub->GetOnDragStart();
    if (dragStart != nullptr) {
        textFieldEventHub->SetOnDragStart(std::move(dragStart));
    }

    auto customerDragEnter = searchEventHub->GetCustomerOnDragFunc(DragFuncType::DRAG_ENTER);
    if (customerDragEnter != nullptr) {
        textFieldEventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_ENTER, std::move(customerDragEnter));
    }

    auto customerDragLeave = searchEventHub->GetCustomerOnDragFunc(DragFuncType::DRAG_LEAVE);
    if (customerDragLeave != nullptr) {
        textFieldEventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_LEAVE, std::move(customerDragLeave));
    }

    auto customerDragMove = searchEventHub->GetCustomerOnDragFunc(DragFuncType::DRAG_MOVE);
    if (customerDragMove != nullptr) {
        textFieldEventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_MOVE, std::move(customerDragMove));
    }

    auto customerDragDrop = searchEventHub->GetCustomerOnDragFunc(DragFuncType::DRAG_DROP);
    if (customerDragDrop != nullptr) {
        textFieldEventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_DROP, std::move(customerDragDrop));
    }

    auto customerDragEnd = searchEventHub->GetCustomerOnDragEndFunc();
    if (customerDragEnd != nullptr) {
        textFieldEventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_END, std::move(customerDragEnd));
    }

    searchEventHub->ClearCustomerOnDragFunc();
    RemoveDragFrameNodeFromManager();
}

void SearchPattern::RemoveDragFrameNodeFromManager()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto dragDropManager = context->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    dragDropManager->RemoveDragFrameNode(frameNode->GetId());
}

void SearchPattern::OnAfterModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto inspectorId = host->GetInspectorId().value_or("");
    if (!inspectorId.empty()) {
        auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
        CHECK_NULL_VOID(textFieldFrameNode);
        auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
        CHECK_NULL_VOID(textFieldPattern);
        auto text = textFieldPattern->GetTextValue();
        Recorder::NodeDataCache::Get().PutString(inspectorId, text);
    }
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
    CHECK_NULL_VOID(!imageClickListener_);
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
    CHECK_NULL_VOID(!buttonClickListener_);
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

void SearchPattern::InitTextFieldClickEvent()
{
    if (textFieldClickListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldGesture = textFieldFrameNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(textFieldGesture);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto searchPattern = weak.Upgrade();
        CHECK_NULL_VOID(searchPattern);
        searchPattern->OnClickTextField();
    };
    textFieldClickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    textFieldGesture->AddClickEvent(textFieldClickListener_);
}

void SearchPattern::InitSearchController()
{
    searchController_->SetCaretPosition([weak = WeakClaim(this)](int32_t caretPosition) {
        auto search = weak.Upgrade();
        CHECK_NULL_VOID(search);
        search->HandleCaretPosition(caretPosition);
    });

    searchController_->SetGetTextContentRect([weak = WeakClaim(this)]() {
        auto search = weak.Upgrade();
        CHECK_NULL_RETURN(search, Rect(0, 0, 0, 0));
        auto rect = search->searchController_->GetTextContentRect();
        search->HandleTextContentRect(rect);
        return rect;
    });

    searchController_->SetGetTextContentLinesNum([weak = WeakClaim(this)]() {
        auto search = weak.Upgrade();
        CHECK_NULL_RETURN(search, 0);
        return search->HandleTextContentLines();
    });

    searchController_->SetGetCaretIndex([weak = WeakClaim(this)]() {
        auto search = weak.Upgrade();
        CHECK_NULL_RETURN(search, ERROR);
        return search->HandleGetCaretIndex();
    });

    searchController_->SetGetCaretPosition([weak = WeakClaim(this)]() {
        auto search = weak.Upgrade();
        CHECK_NULL_RETURN(search, NG::OffsetF(ERROR, ERROR));
        return search->HandleGetCaretPosition();
    });

    searchController_->SetStopEditing([weak = WeakClaim(this)]() {
        auto search = weak.Upgrade();
        CHECK_NULL_VOID(search);
        search->StopEditing();
    });
}

int32_t SearchPattern::HandleGetCaretIndex()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, ERROR);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_RETURN(textFieldFrameNode, ERROR);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, ERROR);
    return textFieldPattern->GetCaretIndex();
}

NG::OffsetF SearchPattern::HandleGetCaretPosition()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, NG::OffsetF(ERROR, ERROR));
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_RETURN(textFieldFrameNode, NG::OffsetF(ERROR, ERROR));
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, NG::OffsetF(ERROR, ERROR));
    return textFieldPattern->GetCaretOffset();
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

void SearchPattern::HandleTextContentRect(Rect& rect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    RectF frameRect = textFieldPattern->GetFrameRect();
    rect.SetLeft(rect.Left() + frameRect.Left());
    rect.SetTop(rect.Top() + frameRect.Top());
}

int32_t SearchPattern::HandleTextContentLines()
{
    int lines = 0;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, lines);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_RETURN(textFieldFrameNode, lines);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, lines);
    if (!textFieldPattern->IsOperation()) {
        return lines;
    }
    RectF textRect = textFieldPattern->GetTextRect();

    if ((int32_t)textFieldPattern->GetLineHeight() == 0) {
        return lines;
    }
    lines = (int32_t)textRect.Height() / (int32_t)textFieldPattern->GetLineHeight();
    return lines;
}

void SearchPattern::StopEditing()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->StopEditing();
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
    auto text = textFieldPattern->GetTextValue();
    searchEventHub->UpdateSubmitEvent(text);
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
    auto textRect = textFieldPattern->GetTextRect();
    textRect.SetLeft(0.0f);
    textFieldPattern->SetTextRect(textRect);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    textFieldLayoutProperty->UpdateValue("");
    auto eventHub = textFieldFrameNode->GetEventHub<TextFieldEventHub>();
    eventHub->FireOnChange("");
    host->MarkModifyDone();
    textFieldFrameNode->MarkModifyDone();
}

void SearchPattern::OnClickTextField()
{
    focusChoice_ = FocusChoice::SEARCH;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RoundRect focusRect;
    GetInnerFocusPaintRect(focusRect);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->PaintInnerFocusState(focusRect);
    host->MarkModifyDone();
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
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_RETURN(textFieldFrameNode, false);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, false);

    bool isAllTextSelected = textFieldPattern->IsSelectAll();
    bool isCaretVisible = textFieldPattern->GetCursorVisible();
    bool isTextEmpty = textFieldPattern->GetTextValue().empty();
    bool isOnlyTabPressed = event.pressedCodes.size() == 1 && event.code == KeyCode::KEY_TAB;

    auto parentHub = host->GetOrCreateFocusHub()->GetParentFocusHub();
    auto getMaxFocusableCount = [](auto self, const RefPtr<FocusHub>& focusHub) -> size_t {
        CHECK_NULL_RETURN(focusHub, 0);
        auto parentHub = focusHub->GetParentFocusHub();
        return std::max(focusHub->GetFocusableCount(), self(self, parentHub));
    };
    constexpr int ONE = 1; // Only one focusable component on scene
    bool isOnlyOneFocusableComponent = getMaxFocusableCount(getMaxFocusableCount, parentHub) == ONE;

    if (event.action == KeyAction::UP && event.code == KeyCode::KEY_TAB &&
        focusChoice_ != FocusChoice::SEARCH) {
        textFieldPattern->HandleSetSelection(0, 0, false); // Clear selection and caret when tab pressed
    }

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
        if (focusChoice_ == FocusChoice::SEARCH && isOnlyOneFocusableComponent && event.IsShiftWith(KeyCode::KEY_TAB)) {
            if (isSearchButtonEnabled_) {
                focusChoice_ = FocusChoice::SEARCH_BUTTON;
            } else if (!isTextEmpty) {
                focusChoice_ = FocusChoice::CANCEL_BUTTON;
            }
            PaintFocusState();
            return true;
        }
        if (focusChoice_ == FocusChoice::SEARCH && event.IsShiftWith(KeyCode::KEY_TAB)) {
            textFieldPattern->CloseKeyboard(true);
            return false;
        }
        if (focusChoice_ == FocusChoice::SEARCH && !isAllTextSelected && !isTextEmpty) {
            return textFieldPattern->OnKeyEvent(event);
        }
        if (focusChoice_ == FocusChoice::SEARCH && isAllTextSelected && !isCaretVisible &&
            event.code == KeyCode::KEY_DPAD_LEFT) {
            return true; // no action
        }
    }
    if (event.code == KeyCode::KEY_DPAD_RIGHT || (event.pressedCodes.size() == 1 && event.code == KeyCode::KEY_TAB)) {
        if (focusChoice_ == FocusChoice::SEARCH && (isAllTextSelected || isTextEmpty || isOnlyTabPressed)) {
            if (NearZero(cancelButtonSize_.Height()) && !isSearchButtonEnabled_ &&
                event.code == KeyCode::KEY_DPAD_RIGHT) {
                return true;
            } else if (NearZero(cancelButtonSize_.Height()) && !isSearchButtonEnabled_) {
                textFieldPattern->CloseKeyboard(true);
                return false;
            }
            if (NearZero(cancelButtonSize_.Height())) {
                focusChoice_ = FocusChoice::SEARCH_BUTTON;
            } else {
                focusChoice_ = FocusChoice::CANCEL_BUTTON;
            }
            PaintFocusState();
            return true;
        } else if (focusChoice_ == FocusChoice::SEARCH && event.code == KeyCode::KEY_DPAD_RIGHT) {
            textFieldPattern->OnKeyEvent(event);
            return true;
        }
        if (focusChoice_ == FocusChoice::CANCEL_BUTTON) {
            if (isOnlyOneFocusableComponent && isOnlyTabPressed && !isSearchButtonEnabled_) {
                focusChoice_ = FocusChoice::SEARCH;
                PaintFocusState();
                return true;
            }
            if (!isSearchButtonEnabled_) {
                return !isOnlyTabPressed; // go outside if Tab pressed, or no action if arrow pressed
            }
            focusChoice_ = FocusChoice::SEARCH_BUTTON;
            PaintFocusState();
            return true;
        }
        if (focusChoice_ == FocusChoice::SEARCH_BUTTON && isOnlyOneFocusableComponent && isOnlyTabPressed) {
            focusChoice_ = FocusChoice::SEARCH;
            PaintFocusState();
            return true;
        }
        if (focusChoice_ == FocusChoice::SEARCH_BUTTON &&
            (event.pressedCodes.size() == 1 && event.code == KeyCode::KEY_TAB)) {
            textFieldPattern->CloseKeyboard(true);
            return false;
        }
        if (focusChoice_ == FocusChoice::SEARCH_BUTTON && event.code == KeyCode::KEY_DPAD_RIGHT) {
            return true;
        }
    }

    if (focusChoice_ == FocusChoice::SEARCH) {
        return textFieldPattern->OnKeyEvent(event);
    } else {
        return true;
    }
}

void SearchPattern::PaintFocusState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);

    if (focusChoice_ == SearchPattern::FocusChoice::SEARCH) {
        if (!textFieldPattern->GetTextValue().empty()) {
            textFieldPattern->HandleOnSelectAll(true); // Select all text
            textFieldPattern->StopTwinkling(); // Hide caret
        } else {
            textFieldPattern->HandleFocusEvent(); // Show caret
        }
    } else {
        if (textFieldPattern->IsSelected() || textFieldPattern->GetCursorVisible()) {
            textFieldPattern->HandleSetSelection(0, 0, false); // Clear text selection & caret if focus has gone
        }
        textFieldPattern->CloseKeyboard(true);
    }

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    context->SetIsFocusActive(true);
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
    float radiusTopLeft = 0.0f;
    float radiusTopRight = 0.0f;
    float radiusBottomLeft = 0.0f;
    float radiusBottomRight = 0.0f;
    float focusOffset = FOCUS_OFFSET.ConvertToPx();
    if (focusChoice_ == FocusChoice::SEARCH) {
        return;
    }
    if (focusChoice_ == FocusChoice::CANCEL_BUTTON) {
        originX = cancelButtonOffset_.GetX() + focusOffset;
        originY = cancelButtonOffset_.GetY() + focusOffset;
        endX = cancelButtonSize_.Width() + originX - DOUBLE * focusOffset;
        endY = cancelButtonSize_.Height() + originY - DOUBLE * focusOffset;
        radiusTopLeft = cancelButtonSize_.Height() / DOUBLE - focusOffset;
        radiusTopRight = cancelButtonSize_.Height() / DOUBLE - focusOffset;
        radiusBottomLeft = cancelButtonSize_.Height() / DOUBLE - focusOffset;
        radiusBottomRight = cancelButtonSize_.Height() / DOUBLE - focusOffset;
    }
    if (focusChoice_ == FocusChoice::SEARCH_BUTTON) {
        originX = buttonOffset_.GetX() + focusOffset;
        originY = buttonOffset_.GetY() + focusOffset;
        endX = buttonSize_.Width() + originX - DOUBLE * focusOffset;
        endY = buttonSize_.Height() + originY - DOUBLE * focusOffset;
        radiusTopLeft = buttonSize_.Height() / DOUBLE - focusOffset;
        radiusTopRight = buttonSize_.Height() / DOUBLE - focusOffset;
        radiusBottomLeft = buttonSize_.Height() / DOUBLE - focusOffset;
        radiusBottomRight = buttonSize_.Height() / DOUBLE - focusOffset;
    }

    paintRect.SetRect({ originX, originY, endX - originX, endY - originY });
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS, radiusTopLeft, radiusTopLeft);
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS, radiusTopRight, radiusTopRight);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS, radiusBottomLeft, radiusBottomLeft);
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS, radiusBottomRight, radiusBottomRight);
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
    auto buttonPattern = buttonFrameNode->GetPattern<ButtonPattern>();
    CHECK_NULL_VOID(buttonPattern);
    auto buttonHoverListener = buttonPattern->GetHoverListener();
    inputHub->RemoveOnHoverEvent(buttonHoverListener);
    auto mouseTask = [weak = WeakClaim(this), childId](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleButtonMouseEvent(isHover, childId);
        }
    };
    inputEvent = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(inputEvent);
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

void SearchPattern::SetMouseStyle(MouseFormat format)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto windowId = pipeline->GetWindowId();
    auto mouseStyle = MouseStyle::CreateMouseStyle();
    CHECK_NULL_VOID(mouseStyle);

    int32_t currentPointerStyle = 0;
    mouseStyle->GetPointerStyle(windowId, currentPointerStyle);
    if (currentPointerStyle != static_cast<int32_t>(format)) {
        mouseStyle->SetPointerStyle(windowId, format);
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
    auto colorMode = SystemProperties::GetColorMode();
    Color touchColorFrom = Color::FromRGBO(0, 0, 0, startOpacity);
    Color touchColorTo = Color::FromRGBO(0, 0, 0, endOpacity);
    if (colorMode == ColorMode::DARK) {
        touchColorFrom = Color::FromRGBO(255, 255, 255, startOpacity);
        touchColorTo = Color::FromRGBO(255, 255, 255, endOpacity);
    }
    Color highlightStart = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT).BlendColor(touchColorFrom);
    Color highlightEnd = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT).BlendColor(touchColorTo);
    renderContext->OnBackgroundColorUpdate(highlightStart);
    AnimationOption option = AnimationOption();
    option.SetDuration(duration);
    option.SetCurve(curve);
    AnimationUtils::Animate(
        option, [renderContext, highlightEnd]() { renderContext->OnBackgroundColorUpdate(highlightEnd); });
}

void SearchPattern::ResetDragOption()
{
    ClearButtonStyle(BUTTON_INDEX);
    ClearButtonStyle(CANCEL_BUTTON_INDEX);
}

void SearchPattern::ClearButtonStyle(int32_t childId)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(childId));
    CHECK_NULL_VOID(buttonFrameNode);
    auto renderContext = buttonFrameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimateTouchAndHover(renderContext, TOUCH_OPACITY, 0.0f, HOVER_TO_TOUCH_DURATION, Curves::SHARP);
}

void SearchPattern::InitFocusEvent(const RefPtr<FocusHub>& focusHub)
{
    auto focusTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (pattern) {
            bool backwardFocusMovement = false;
            auto host = pattern->GetHost();
            if (host) {
                auto rootHub = host->GetOrCreateFocusHub()->GetRootFocusHub();
                backwardFocusMovement = rootHub && rootHub->HasBackwardFocusMovementInChildren();
                rootHub->ClearBackwardFocusMovementFlagInChildren();
            }
            pattern->HandleFocusEvent(backwardFocusMovement);
        }
    };
    focusHub->SetOnFocusInternal(focusTask);
    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurEvent();
    };
    focusHub->SetOnBlurInternal(blurTask);
}

void SearchPattern::HandleFocusEvent(bool backwardFocusMovement)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);

    focusChoice_ = backwardFocusMovement ? FocusChoice::SEARCH_BUTTON : FocusChoice::SEARCH;
    if (focusChoice_ == FocusChoice::SEARCH_BUTTON && !isSearchButtonEnabled_) {
        bool isCancelHidden = NearZero(cancelButtonSize_.Height());
        focusChoice_ = isCancelHidden ? FocusChoice::SEARCH : FocusChoice::CANCEL_BUTTON;
    }
    PaintFocusState();
}

void SearchPattern::HandleBlurEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->HandleBlurEvent();
}

void SearchPattern::InitClickEvent()
{
    if (clickListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleClickEvent(info);
    };
    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void SearchPattern::HandleClickEvent(GestureEvent& info)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->HandleClickEvent(info);
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

void SearchPattern::ToJsonValueForTextField(std::unique_ptr<JsonValue>& json) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);

    json->Put("value", textFieldPattern->GetTextValue().c_str());
    json->Put("placeholder", textFieldPattern->GetPlaceHolder().c_str());
    json->Put("placeholderColor", textFieldPattern->GetPlaceholderColor().c_str());
    json->Put("placeholderFont", textFieldPattern->GetPlaceholderFont().c_str());
    json->Put("textAlign", V2::ConvertWrapTextAlignToString(textFieldPattern->GetTextAlign()).c_str());
    auto textColor = textFieldLayoutProperty->GetTextColor().value_or(Color());
    json->Put("fontColor", textColor.ColorToString().c_str());
    auto textFontJson = JsonUtil::Create(true);
    textFontJson->Put("fontSize", textFieldPattern->GetFontSize().c_str());
    textFontJson->Put("fontStyle",
        textFieldPattern->GetItalicFontStyle() == Ace::FontStyle::NORMAL ? "FontStyle.Normal" : "FontStyle.Italic");
    textFontJson->Put("fontWeight", V2::ConvertWrapFontWeightToStirng(textFieldPattern->GetFontWeight()).c_str());
    textFontJson->Put("fontFamily", textFieldPattern->GetFontFamily().c_str());
    json->Put("textFont", textFontJson->ToString().c_str());
    json->Put("copyOption",
        ConvertCopyOptionsToString(textFieldLayoutProperty->GetCopyOptionsValue(CopyOptions::None)).c_str());
    auto maxLength = GetMaxLength();
    json->Put("maxLength", GreatOrEqual(maxLength, Infinity<uint32_t>()) ? "INF" : std::to_string(maxLength).c_str());
    json->Put("type", textFieldPattern->TextInputTypeToString().c_str());
    textFieldLayoutProperty->HasCopyOptions();
}

void SearchPattern::ToJsonValueForSearchIcon(std::unique_ptr<JsonValue>& json) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto imageFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(IMAGE_INDEX));
    CHECK_NULL_VOID(imageFrameNode);
    auto imageLayoutProperty = imageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    auto searchIconJson = JsonUtil::Create(true);

    // icon size
    auto searchIconGeometryNode = imageFrameNode->GetGeometryNode();
    CHECK_NULL_VOID(searchIconGeometryNode);
    auto searchIconFrameSize = searchIconGeometryNode->GetFrameSize().Width();
    auto searchLayoutProperty = host->GetLayoutProperty<SearchLayoutProperty>();
    CHECK_NULL_VOID(searchLayoutProperty);
    auto searchIconSize = searchLayoutProperty->GetSearchIconUDSizeValue(Dimension(searchIconFrameSize)).ConvertToPx();
    searchIconJson->Put("size", Dimension(searchIconSize, DimensionUnit::PX).ToString().c_str());

    // icon color
    auto searchIconColor = imageLayoutProperty->GetImageSourceInfo()->GetFillColor().value_or(Color());
    searchIconJson->Put("color", searchIconColor.ColorToString().c_str());

    // icon path
    auto searchIconPath = imageLayoutProperty->GetImageSourceInfo()->GetSrc();
    searchIconJson->Put("src", searchIconPath.c_str());
    json->Put("icon", searchIconPath.c_str());
    json->Put("searchIcon", searchIconJson);
}

void SearchPattern::ToJsonValueForCancelButton(std::unique_ptr<JsonValue>& json) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<SearchLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto cancelImageFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    CHECK_NULL_VOID(cancelImageFrameNode);
    auto cancelImageLayoutProperty = cancelImageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(cancelImageLayoutProperty);
    auto cancelButtonJson = JsonUtil::Create(true);

    // style
    if (layoutProperty->GetCancelButtonStyle() == CancelButtonStyle::CONSTANT) {
        cancelButtonJson->Put("style", "CancelButtonStyle.CONSTANT");
    } else if (layoutProperty->GetCancelButtonStyle() == CancelButtonStyle::INVISIBLE) {
        cancelButtonJson->Put("style", "CancelButtonStyle.INVISIBLE");
    } else {
        cancelButtonJson->Put("style", "CancelButtonStyle.INPUT");
    }

    auto cancelIconJson = JsonUtil::Create(true);

    // icon size
    auto cancelIconGeometryNode = cancelImageFrameNode->GetGeometryNode();
    CHECK_NULL_VOID(cancelIconGeometryNode);
    auto cancelIconFrameSize = cancelIconGeometryNode->GetFrameSize().Width();
    auto searchLayoutProperty = host->GetLayoutProperty<SearchLayoutProperty>();
    CHECK_NULL_VOID(searchLayoutProperty);
    auto cancelIconSize =
        searchLayoutProperty->GetCancelButtonUDSizeValue(Dimension(cancelIconFrameSize)).ConvertToPx();
    cancelIconJson->Put("size", Dimension(cancelIconSize, DimensionUnit::PX).ToString().c_str());

    // icon color
    auto cancelImageRenderProperty = cancelImageFrameNode->GetPaintProperty<ImageRenderProperty>();
    CHECK_NULL_VOID(cancelImageRenderProperty);
    auto cancelIconColor = cancelImageRenderProperty->GetSvgFillColor().value_or(Color());
    cancelIconJson->Put("color", cancelIconColor.ColorToString().c_str());

    // right icon src path
    auto cancelImageSrc = cancelImageLayoutProperty->GetImageSourceInfo()->GetSrc();
    cancelIconJson->Put("src", cancelImageSrc.c_str());
    cancelButtonJson->Put("icon", cancelIconJson);
    json->Put("cancelButton", cancelButtonJson);
}

void SearchPattern::ToJsonValueForSearchButtonOption(std::unique_ptr<JsonValue>& json) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto searchButtonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(searchButtonFrameNode);
    auto searchButtonLayoutProperty = searchButtonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(searchButtonLayoutProperty);
    auto searchButtonJson = JsonUtil::Create(true);

    // font size
    auto searchButtonFontSize = searchButtonLayoutProperty->GetFontSize().value_or(Dimension(0, DimensionUnit::VP));
    searchButtonJson->Put("fontSize", searchButtonFontSize.ToString().c_str());

    // font color
    auto searchButtonFontColor = searchButtonLayoutProperty->GetFontColor().value_or(Color());
    searchButtonJson->Put("fontColor", searchButtonFontColor.ColorToString().c_str());
    json->Put("searchButtonOption", searchButtonJson);
}

void SearchPattern::ToJsonValueForCursor(std::unique_ptr<JsonValue>& json) const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldPaintProperty = textFieldFrameNode->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textFieldPaintProperty);
    auto cursorJson = JsonUtil::Create(true);

    // color
    auto caretColor = textFieldPaintProperty->GetCursorColor().value_or(Color());
    cursorJson->Put("color", caretColor.ColorToString().c_str());
    auto caretWidth = textFieldPaintProperty->GetCursorWidth().value_or(Dimension(0, DimensionUnit::VP));
    cursorJson->Put("width", caretWidth.ToString().c_str());
    json->Put("caretStyle", cursorJson);
}

void SearchPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    Pattern::ToJsonValue(json);

    ToJsonValueForTextField(json);
    ToJsonValueForSearchIcon(json);
    ToJsonValueForCancelButton(json);
    ToJsonValueForCursor(json);
    ToJsonValueForSearchButtonOption(json);
}

void SearchPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetNeedCallChildrenUpdate(false);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>();
    CHECK_NULL_VOID(textFieldTheme);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateBackgroundColor(textFieldTheme->GetBgColor());
    CHECK_NULL_VOID(pipeline);
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_VOID(searchTheme);
    if (cancelButtonNode_) {
        auto cancelButtonRenderContext = cancelButtonNode_->GetRenderContext();
        CHECK_NULL_VOID(cancelButtonRenderContext);
        cancelButtonRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        auto textFrameNode = AceType::DynamicCast<FrameNode>(cancelButtonNode_->GetChildren().front());
        CHECK_NULL_VOID(textFrameNode);
        auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateTextColor(searchTheme->GetSearchButtonTextColor());
        cancelButtonNode_->MarkModifyDone();
        cancelButtonNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    if (buttonNode_) {
        auto buttonRenderContext = buttonNode_->GetRenderContext();
        CHECK_NULL_VOID(buttonRenderContext);
        buttonRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        auto textFrameNode = AceType::DynamicCast<FrameNode>(buttonNode_->GetChildren().front());
        CHECK_NULL_VOID(textFrameNode);
        auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateTextColor(searchTheme->GetSearchButtonTextColor());
        buttonNode_->MarkModifyDone();
        buttonNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    if (textField_) {
        auto textFieldLayoutProperty = textField_->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(textFieldLayoutProperty);
        textFieldLayoutProperty->UpdateTextColor(searchTheme->GetTextColor());
        textFieldLayoutProperty->UpdatePlaceholderTextColor(searchTheme->GetPlaceholderColor());
        textField_->MarkModifyDone();
        textField_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

uint32_t SearchPattern::GetMaxLength() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, Infinity<uint32_t>());
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_RETURN(textFieldFrameNode, Infinity<uint32_t>());
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, Infinity<uint32_t>());
    return textFieldLayoutProperty->HasMaxLength() ? textFieldLayoutProperty->GetMaxLengthValue(Infinity<uint32_t>())
                                                   : Infinity<uint32_t>();
}

} // namespace OHOS::Ace::NG
