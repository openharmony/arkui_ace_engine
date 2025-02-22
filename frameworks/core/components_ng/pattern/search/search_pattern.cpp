/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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
#include "base/geometry/dimension.h"
#include "base/utils/utf_helper.h"
#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#include "base/geometry/rect.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components/search/search_theme.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/divider/divider_render_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/search/search_model.h"
#include "core/components_ng/pattern/search/search_text_field.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/event/touch_event.h"
#include "core/components/theme/app_theme.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int32_t TEXTFIELD_INDEX = 0;
constexpr int32_t IMAGE_INDEX = 1;
constexpr int32_t CANCEL_IMAGE_INDEX = 2;
constexpr int32_t CANCEL_BUTTON_INDEX = 3;
constexpr int32_t BUTTON_INDEX = 4;
constexpr int32_t DIVIDER_INDEX = 5;
constexpr int32_t DOUBLE = 2;
constexpr int32_t ERROR = -1;

// The focus state requires an 2vp inner stroke, which should be indented by 1vp when drawn.
constexpr Dimension FOCUS_OFFSET = 1.0_vp;
constexpr Dimension UP_AND_DOWN_PADDING = 8.0_vp;
constexpr Dimension SYMBOL_ICON_HEIGHT = 16.0_fp;
constexpr Dimension ICON_MAX_SIZE = 32.0_vp;
constexpr Dimension SEARCH_TEXTINPUT_BORDER_WIDTH = 0.0_vp;
constexpr float HOVER_OPACITY = 0.05f;
constexpr float TOUCH_OPACITY = 0.1f;
constexpr float MAX_FONT_SCALE = 2.0f;
constexpr int32_t HOVER_TO_TOUCH_DURATION = 100;
constexpr int32_t HOVER_DURATION = 250;
constexpr int32_t TOUCH_DURATION = 250;

const std::string INSPECTOR_PREFIX = "__SearchField__";
const std::vector<std::string> SPECICALIZED_INSPECTOR_INDEXS = { "", "Image__", "CancelImage__", "CancelButton__",
    "Button__" };
} // namespace

void SearchPattern::UpdateChangeEvent(const std::u16string& textValue, int16_t style)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto buttonHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    CHECK_NULL_VOID(buttonHost);
    auto imageHost = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    CHECK_NULL_VOID(imageHost);
    if (style == ERROR) {
        auto layoutProperty = frameNode->GetLayoutProperty<SearchLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        style = static_cast<int16_t>(layoutProperty->GetCancelButtonStyle().value_or(CancelButtonStyle::INPUT));
    }
    UpdateCancelButtonStatus(textValue, style);
    buttonHost->MarkModifyDone();
    imageHost->MarkModifyDone();
    buttonHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    imageHost->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    if (imageHost->GetTag() == V2::SYMBOL_ETS_TAG) {
        auto textLayoutProperty = imageHost->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        auto layoutConstraint = textLayoutProperty->GetLayoutConstraint();
        auto textLayoutWrapper = imageHost->CreateLayoutWrapper();
        CHECK_NULL_VOID(textLayoutWrapper);
        ScopedLayout scope(frameNode->GetContext());
        textLayoutWrapper->Measure(layoutConstraint);
    }
}

void SearchPattern::UpdateCancelButtonStatus(const std::u16string& textValue, int16_t style)
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
    auto cancelButtonEvent = buttonHost->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(cancelButtonEvent);
    auto buttonLayoutProperty = buttonHost->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    auto imageLayoutProperty = imageHost->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    bool isEventEnabled = IsEventEnabled(textValue, style);
    if (isEventEnabled) {
        cancelButtonRenderContext->UpdateOpacity(1.0);
        cancelImageRenderContext->UpdateOpacity(1.0);
        cancelButtonEvent->SetEnabled(true);
        buttonLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        imageLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    } else {
        cancelButtonRenderContext->UpdateOpacity(0.0);
        cancelImageRenderContext->UpdateOpacity(0.0);
        cancelButtonEvent->SetEnabled(false);
        buttonLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
        imageLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    }
    if (imageHost->GetTag() == V2::IMAGE_ETS_TAG) {
        auto imageEvent = imageHost->GetEventHub<ImageEventHub>();
        CHECK_NULL_VOID(imageEvent);
        imageEvent->SetEnabled(isEventEnabled);
    }
}

void SearchPattern::UpdateDisable(const std::u16string& textValue)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto searchButtonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(searchButtonFrameNode);
    auto searchButtonLayoutProperty = searchButtonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(searchButtonLayoutProperty);
    auto needToDisable = searchButtonLayoutProperty->GetAutoDisable().value_or(false);
    if (!needToDisable) {
        return;
    }
    bool isEmptyText = textValue.empty();
    if (isSearchButtonEnabled_ && isEmptyText) {
        UpdateEnable(false);
    } else if (!isSearchButtonEnabled_ && !isEmptyText) {
        UpdateEnable(true);
    }
}

void SearchPattern::UpdateEnable(bool needToenable)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto searchButtonFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(searchButtonFrameNode);
    auto buttonEventHub = searchButtonFrameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);
    if (needToenable) {
        buttonEventHub->SetEnabled(true);
    } else {
        buttonEventHub->SetEnabled(false);
    }
    isSearchButtonEnabled_ = buttonEventHub->IsEnabled();
    searchButtonFrameNode->MarkModifyDone();
    searchButtonFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

bool SearchPattern::IsEventEnabled(const std::u16string& textValue, int16_t style)
{
    return (style == static_cast<int16_t>(CancelButtonStyle::CONSTANT)) ||
           ((style == static_cast<int16_t>(CancelButtonStyle::INPUT)) && !textValue.empty());
}

bool SearchPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& /*config*/)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, true);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_RETURN(textFieldFrameNode, true);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, true);
    UpdateDisable(textFieldPattern->GetTextUtf16Value());
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
    SetAccessibilityClearAction();
    return true;
}

void SearchPattern::SetAccessibilityClearAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto cancelButtonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    CHECK_NULL_VOID(cancelButtonFrameNode);
    auto textAccessibilityProperty = cancelButtonFrameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(textAccessibilityProperty);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    auto layoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto cleanNodeStyle = layoutProperty->GetCleanNodeStyleValue(CleanNodeStyle::INPUT);
    auto hasContent = cleanNodeStyle == CleanNodeStyle::CONSTANT ||
                        (cleanNodeStyle == CleanNodeStyle::INPUT && textFieldPattern->HasText());
    textAccessibilityProperty->SetAccessibilityText(hasContent ? textFieldPattern->GetCancelButton() : "");
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

    InitSearchTheme();
    HandleBackgroundColor();

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
    buttonLayoutProperty->UpdateVisibility(searchButton.has_value() ? VisibleType::VISIBLE : VisibleType::GONE);
    buttonLayoutProperty->UpdateLabel(searchButton_);
    buttonLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    buttonFrameNode->MarkModifyDone();

    auto searchButtonEvent = buttonFrameNode->GetEventHub<ButtonEventHub>();
    isSearchButtonEnabled_ = searchButtonEvent->IsEnabled();

    UpdateCancelButton();
    UpdateDivider();
    InitAllEvent();
}

void SearchPattern::InitAllEvent()
{
    InitButtonAndImageClickEvent();
    InitCancelButtonClickEvent();
    InitTextFieldValueChangeEvent();
    InitTextFieldDragEvent();
    InitTextFieldClickEvent();
    InitButtonMouseAndTouchEvent();
    HandleTouchableAndHitTestMode();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);
    InitFocusEvent(focusHub);
    InitClickEvent();
    HandleEnabled();
    SetAccessibilityAction();
}

void SearchPattern::UpdateCancelButton()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto cancelButtonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(CANCEL_BUTTON_INDEX));
    CHECK_NULL_VOID(cancelButtonFrameNode);
    auto cancelButtonLayoutProperty = cancelButtonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(cancelButtonLayoutProperty);
    cancelButtonLayoutProperty->UpdateLabel("");
    cancelButtonFrameNode->MarkModifyDone();
}

void SearchPattern::UpdateDivider()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<SearchLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto dividerFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(DIVIDER_INDEX));
    CHECK_NULL_VOID(dividerFrameNode);
    auto dividerLayoutProperty = dividerFrameNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_VOID(dividerLayoutProperty);
    auto searchButton = layoutProperty->GetSearchButton();
    dividerLayoutProperty->UpdateVisibility(searchButton.has_value() ? VisibleType::VISIBLE : VisibleType::GONE);
    dividerFrameNode->MarkModifyDone();
}

void SearchPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textAccessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(textAccessibilityProperty);
    textAccessibilityProperty->SetActionSetSelection(
        [weak = WeakClaim(this)](int32_t start, int32_t end, bool isForward) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
        CHECK_NULL_VOID(textFieldFrameNode);
        auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
        CHECK_NULL_VOID(textFieldPattern);
        textFieldPattern->SetSelectionFlag(start, end, std::nullopt, isForward);
    });

    textAccessibilityProperty->SetActionSetIndex([weakPtr = WeakClaim(this)](int32_t index) {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleCaretPosition(index);
    });

    textAccessibilityProperty->SetActionGetIndex([weakPtr = WeakClaim(this)]() -> int32_t {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_RETURN(pattern, -1);
        auto index = pattern->HandleGetCaretIndex();
        return index;
    });
    SetSearchFieldAccessibilityAction();
    SetSearchButtonAccessibilityAction();
}

void SearchPattern::SetSearchFieldAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textFieldAccessibilityProperty = textFieldFrameNode->GetAccessibilityProperty<AccessibilityProperty>();
    textFieldAccessibilityProperty->SetActionClick([weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto gesture = host->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gesture);
        auto actuator = gesture->GetUserClickEventActuator();
        CHECK_NULL_VOID(actuator);
        auto callBack = actuator->GetClickEvent();
        CHECK_NULL_VOID(callBack);
        GestureEvent gestureEvent;
        callBack(gestureEvent);
    });

    auto textAccessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    textAccessibilityProperty->SetActionSetText([weak = WeakClaim(this)](const std::string& value) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
        CHECK_NULL_VOID(textFieldFrameNode);
        auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
        CHECK_NULL_VOID(textFieldPattern);
        textFieldPattern->InsertValue(value);
    });
}

void SearchPattern::SetSearchButtonAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto buttonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(buttonFrameNode);
    auto searchButtonAccessibilityProperty = buttonFrameNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(searchButtonAccessibilityProperty);
    searchButtonAccessibilityProperty->SetAccessibilityLevel("yes");
    searchButtonAccessibilityProperty->SetAccessibilityGroup(true);
}

void SearchPattern::HandleBackgroundColor()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(textFieldTheme);
    auto searchLayoutProperty = host->GetLayoutProperty<SearchLayoutProperty>();
    CHECK_NULL_VOID(searchLayoutProperty);
    if (!searchLayoutProperty->HasBackgroundColor()) {
        renderContext->UpdateBackgroundColor(textFieldTheme->GetBgColor());
    }
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
    eventHub->SetEnabled(searchEventHub->IsEnabled() ? true : false);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto searchLayoutProperty = host->GetLayoutProperty<SearchLayoutProperty>();
    CHECK_NULL_VOID(searchLayoutProperty);
    textFieldLayoutProperty->UpdateLayoutDirection(searchLayoutProperty->GetLayoutDirection());
    textFieldFrameNode->MarkModifyDone();
}

void SearchPattern::HandleTouchableAndHitTestMode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto searchEventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(searchEventHub);
    auto searchGestureHub = searchEventHub->GetGestureEventHub();
    CHECK_NULL_VOID(searchGestureHub);
    bool searchTouchable = true;
    HitTestMode searchHitTestMode = HitTestMode::HTMDEFAULT;
    if (searchGestureHub) {
        searchTouchable = searchGestureHub->GetTouchable();
        searchHitTestMode = searchGestureHub->GetHitTestMode();
    }
    for (int32_t childIndex = TEXTFIELD_INDEX; childIndex <= BUTTON_INDEX; childIndex++) {
        auto childFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(childIndex));
        CHECK_NULL_VOID(childFrameNode);
        auto childEventHub = childFrameNode->GetEventHub<EventHub>();
        auto childGestureHub = childEventHub->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(childGestureHub);
        childGestureHub->SetTouchable(searchTouchable);
        childGestureHub->SetHitTestMode(searchHitTestMode);
        childFrameNode->MarkModifyDone();
    }
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
        auto searchChangeFunc = [weak = AceType::WeakClaim(this)]
        (const ChangeValueInfo& info) {
            auto searchPattern = weak.Upgrade();
            searchPattern->UpdateChangeEvent(info.value);
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

    textFieldFrameNode->SetDragPreview(host->GetDragPreview());
    if (host->GetDisallowDropForcedly()) {
        textFieldFrameNode->SetDisallowDropForcedly(true);
        textFieldFrameNode->SetAllowDrop(host->GetAllowDrop());
    } else if (!host->GetAllowDrop().empty()) {
        textFieldFrameNode->SetDisallowDropForcedly(false);
        textFieldFrameNode->SetAllowDrop(host->GetAllowDrop());
    } else {
        textFieldFrameNode->SetDisallowDropForcedly(false);
    }

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
    auto context = frameNode->GetContext();
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
        Recorder::NodeDataCache::Get().PutString(host, inspectorId, text);
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
    textFieldGesture->AddClickAfterEvent(textFieldClickListener_);
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
    if (!textFieldPattern->HasText()) {
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
    auto text = textFieldPattern->GetTextUtf16Value();
    // Enter key type callback
    TextFieldCommonEvent event;
    searchEventHub->FireOnSubmit(text, event);
    // If the developer doesn't want to keep editing, close keyboard and select background color
    if (!event.IsKeepEditable()) {
        textFieldPattern->StopEditing();
    }
    UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "Search.onSubmit");
}

void SearchPattern::OnClickCancelButton()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildren().front());
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    CHECK_NULL_VOID(!textFieldPattern->IsDragging());
    CHECK_NULL_VOID(!textFieldPattern->IsHandleDragging());
    focusChoice_ = FocusChoice::SEARCH;
    textFieldPattern->ClearTextContent();
    textFieldPattern->SetTextChangedAtCreation(true);
    auto textRect = textFieldPattern->GetTextRect();
    textRect.SetLeft(0.0f);
    textFieldPattern->SetTextRect(textRect);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto focusHub = host->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->RequestFocusImmediately();
    textFieldPattern->HandleFocusEvent();
    textFieldFrameNode->OnAccessibilityEvent(AccessibilityEventType::REQUEST_FOCUS);
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
    TAG_LOGI(AceLogTag::ACE_SEARCH, "KeyAction:%{public}d, KeyCode:%{public}d", static_cast<int>(event.action),
        static_cast<int>(event.code));
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_RETURN(textFieldFrameNode, false);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_RETURN(textFieldPattern, false);

    bool isAllTextSelected = textFieldPattern->IsSelectAll();
    bool isCaretVisible = textFieldPattern->GetCursorVisible();
    bool isTextEmpty = textFieldPattern->GetTextUtf16Value().empty();
    bool isOnlyTabPressed = event.pressedCodes.size() == 1 && event.code == KeyCode::KEY_TAB;

    auto parentHub = host->GetOrCreateFocusHub()->GetParentFocusHub();
    auto getMaxFocusableCount = [](auto self, const RefPtr<FocusHub>& focusHub) -> size_t {
        CHECK_NULL_RETURN(focusHub, 0);
        auto parentHub = focusHub->GetParentFocusHub();
        return std::max(focusHub->GetFocusableCount(), self(self, parentHub));
    };
    constexpr int ONE = 1; // Only one focusable component on scene
    bool isOnlyOneFocusableComponent = getMaxFocusableCount(getMaxFocusableCount, parentHub) == ONE;
    auto container = Container::Current();
    if (container && container->IsUIExtensionWindow()) {
        isOnlyOneFocusableComponent = false; // UI Extension Window
    }

    if (event.action != KeyAction::DOWN) {
        if ((event.code == KeyCode::KEY_TAB ||
            event.code == KeyCode::KEY_SHIFT_LEFT ||
            event.code == KeyCode::KEY_SHIFT_RIGHT) &&
            focusChoice_ == FocusChoice::SEARCH) {
            textFieldPattern->OnKeyEvent(event);
        }
        return false;
    }

    if (focusChoice_ == FocusChoice::SEARCH &&
        (event.IsShiftWith(KeyCode::KEY_DPAD_LEFT) ||
        event.IsShiftWith(KeyCode::KEY_DPAD_RIGHT))) {
        return textFieldPattern->OnKeyEvent(event);
    }

    // If the focus is on the search, press Enter to request keyboard.
    if (event.code == KeyCode::KEY_ENTER && focusChoice_ == FocusChoice::SEARCH && !IsSearchAttached()) {
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
            return false;
        }
        if (focusChoice_ == FocusChoice::SEARCH && !isAllTextSelected && !isTextEmpty) {
            return textFieldPattern->OnKeyEvent(event);
        }
        if (focusChoice_ == FocusChoice::SEARCH && isAllTextSelected && !isCaretVisible &&
            event.code == KeyCode::KEY_DPAD_LEFT) {
            return IsConsumeEvent();
        }
    }
    if (event.code == KeyCode::KEY_DPAD_RIGHT || (event.pressedCodes.size() == 1 && event.code == KeyCode::KEY_TAB)) {
        if (focusChoice_ == FocusChoice::SEARCH && (isAllTextSelected || isTextEmpty || isOnlyTabPressed)) {
            if (NearZero(cancelButtonSize_.Height()) && !isSearchButtonEnabled_ &&
                event.code == KeyCode::KEY_DPAD_RIGHT) {
                return IsConsumeEvent();
            } else if (NearZero(cancelButtonSize_.Height()) && !isSearchButtonEnabled_) {
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
            return textFieldPattern->OnKeyEvent(event);
        }
        if (focusChoice_ == FocusChoice::CANCEL_BUTTON) {
            if (!NearZero(cancelButtonSize_.Height()) && (!isSearchButtonEnabled_) &&
                (event.code == KeyCode::KEY_DPAD_RIGHT)) {
                return false; // Go out of Search
            }
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
            return false;
        }
        if (focusChoice_ == FocusChoice::SEARCH_BUTTON && isSearchButtonEnabled_ &&
            (event.code == KeyCode::KEY_DPAD_RIGHT)) {
            return false; // Go out of Search
        }
    }

    if (focusChoice_ == FocusChoice::SEARCH) {
        return textFieldPattern->OnKeyEvent(event);
    } else {
        return true;
    }
}

bool SearchPattern::IsSearchAttached()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    auto textFieldManager = DynamicCast<TextFieldManagerNG>(context->GetTextFieldManager());
    CHECK_NULL_RETURN(textFieldManager, false);
    return textFieldManager->GetIsImeAttached();
}

bool SearchPattern::IsConsumeEvent()
{
    return !directionKeysMoveFocusOut_;
}

void SearchPattern::PaintSearchFocusState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto searchTheme = GetTheme();
    CHECK_NULL_VOID(searchTheme);
    auto normalTextColor = searchTheme->GetTextColor();
    // 获焦态反色 可通过分层参数配置不同的色值达到反色的效果
    if (textFieldLayoutProperty->GetTextColorValue(normalTextColor) == normalTextColor) {
        textFieldLayoutProperty->UpdateTextColor(searchTheme->GetFocusTextColor());
        isFocusTextColorSet_ = true;
    }
    auto normalPlaceholderColor = searchTheme->GetPlaceholderColor();
    if (textFieldLayoutProperty->GetPlaceholderTextColorValue(normalPlaceholderColor) == normalPlaceholderColor) {
        textFieldLayoutProperty->UpdatePlaceholderTextColor(searchTheme->GetFocusPlaceholderColor());
        isFocusPlaceholderColorSet_ = true;
    }
}

void SearchPattern::PaintFocusState(bool recoverFlag)
{
    TAG_LOGI(AceLogTag::ACE_SEARCH, "Focus Choice = %{public}d", static_cast<int>(focusChoice_));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto searchTheme = GetTheme();
    CHECK_NULL_VOID(searchTheme);
    if (renderContext->GetBackgroundColor().value_or(searchNormalColor_) == searchNormalColor_) {
        renderContext->UpdateBackgroundColor(searchTheme->GetFocusBgColor());
        isFocusBgColorSet_ = true;
    }
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    auto searchTextFieldPattern = DynamicCast<SearchTextFieldPattern>(textFieldPattern);
    CHECK_NULL_VOID(searchTextFieldPattern);

    if (focusChoice_ == FocusChoice::SEARCH) {
        HandleFocusChoiceSearch(textFieldPattern, recoverFlag, searchTextFieldPattern);
    } else {
        textFieldPattern->CloseKeyboard(true);
        searchTextFieldPattern->SearchRequestStopTwinkling(); // Hide caret
    }

    if (GetDefaultIconColor(IMAGE_INDEX) == searchTheme->GetSymbolIconColor()) {
        SetSymbolSearchIconColor(searchTheme->GetFocusIconColor());
        isFocusIconColorSet_ = true;
    }

    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    RoundRect focusRect;
    GetInnerFocusPaintRect(focusRect);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->PaintInnerFocusState(focusRect, true);
    host->MarkModifyDone();
}

void SearchPattern::HandleFocusChoiceSearch(const RefPtr<TextFieldPattern>& textFieldPattern, bool recoverFlag,
    const RefPtr<SearchTextFieldPattern>& searchTextFieldPattern)
{
    PaintSearchFocusState();
    if (directionKeysMoveFocusOut_ && !recoverFlag && !textFieldPattern->GetTextUtf16Value().empty()) {
        textFieldPattern->HandleFocusEvent();
        searchTextFieldPattern->SearchRequestStartTwinkling();
        return;
    }
    if (!recoverFlag) {
        if (!textFieldPattern->GetTextUtf16Value().empty()) {
            textFieldPattern->NeedRequestKeyboard();
            textFieldPattern->SearchRequestKeyboard();
            textFieldPattern->HandleOnSelectAll(false); // Select all text
            textFieldPattern->HandleFocusEvent(); // Show caret
            searchTextFieldPattern->ResetSearchRequestStopTwinkling(); // reset flag
            textFieldPattern->StopTwinkling(); // Hide caret
        } else {
            textFieldPattern->HandleFocusEvent(); // Show caret
            searchTextFieldPattern->SearchRequestStartTwinkling();
        }
    } else {
        textFieldPattern->HandleFocusEvent();
        searchTextFieldPattern->SearchRequestStartTwinkling();
    }
}

void SearchPattern::GetSearchFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto searchSize = geometryNode->GetFrameSize();
    auto searchTheme = GetTheme();
    CHECK_NULL_VOID(searchTheme);

    // 焦点框与search边框间距
    auto searchFocusPadding = searchTheme->GetSearchFocusPadding().ConvertToPx();
    float width = searchSize.Width() + 2 * searchFocusPadding;
    float height = searchSize.Height() + 2 * searchFocusPadding;
    paintRect.SetRect({ -searchFocusPadding, -searchFocusPadding, width, height });
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto radius = renderContext->GetBorderRadius().value_or(BorderRadiusProperty());
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_LEFT_POS,
        static_cast<float>(radius.radiusTopLeft->ConvertToPx() + searchFocusPadding),
        static_cast<float>(radius.radiusTopLeft->ConvertToPx() + searchFocusPadding));
    paintRect.SetCornerRadius(RoundRect::CornerPos::TOP_RIGHT_POS,
        static_cast<float>(radius.radiusTopRight->ConvertToPx() + searchFocusPadding),
        static_cast<float>(radius.radiusTopRight->ConvertToPx() + searchFocusPadding));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_LEFT_POS,
        static_cast<float>(radius.radiusBottomLeft->ConvertToPx() + searchFocusPadding),
        static_cast<float>(radius.radiusBottomLeft->ConvertToPx() + searchFocusPadding));
    paintRect.SetCornerRadius(RoundRect::CornerPos::BOTTOM_RIGHT_POS,
        static_cast<float>(radius.radiusBottomRight->ConvertToPx() + searchFocusPadding),
        static_cast<float>(radius.radiusBottomRight->ConvertToPx() + searchFocusPadding));
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
        auto searchTheme = GetTheme();
        CHECK_NULL_VOID(searchTheme);
        // 分层参数控制是否需要绘制焦点框
        if (searchTheme->NeedFocusBox()) {
            GetSearchFocusPaintRect(paintRect);
            return;
        }
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
    FocusPattern focusPattern = { FocusType::NODE, true, FocusStyleType::CUSTOM_REGION };
    focusPattern.SetIsFocusActiveWhenFocused(true);
    return focusPattern;
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
        if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
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

void SearchPattern::AnimateSearchTouchAndHover(RefPtr<RenderContext>& renderContext,
    Color& blendColorFrom, Color& blendColorTo, int32_t duration, const RefPtr<Curve>& curve)
{
    Color highlightStart = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT).BlendColor(blendColorFrom);
    Color highlightEnd = renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT).BlendColor(blendColorTo);
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

void SearchPattern::InitSearchTheme()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(textFieldTheme);
    searchNormalColor_ = textFieldTheme->GetBgColor();
    directionKeysMoveFocusOut_ = textFieldTheme->GetDirectionKeysMoveFocusOut();
    searchTheme_ = pipeline->GetTheme<SearchTheme>(host->GetThemeScopeId());

    // 使用分层参数控制是否需要注册相关事件以适配悬浮态、按压态的变化
    auto hoverAndPressBgColorEnabled = textFieldTheme->GetHoverAndPressBgColorEnabled();
    if (hoverAndPressBgColorEnabled) {
        InitHoverEvent();
        InitTouchEvent();
    }
}

RefPtr<SearchTheme> SearchPattern::GetTheme() const
{
    if (searchTheme_.Upgrade()) {
        return searchTheme_.Upgrade();
    }
    auto tmpHost = GetHost();
    CHECK_NULL_RETURN(tmpHost, nullptr);
    auto context = tmpHost->GetContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto theme = context->GetTheme<SearchTheme>(tmpHost->GetThemeScopeId());
    return theme;
}

void SearchPattern::InitHoverEvent()
{
    if (searchHoverListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<SearchEventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();

    auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleHoverEvent(isHover);
    };
    searchHoverListener_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(searchHoverListener_);
}

void SearchPattern::HandleHoverEvent(bool isHover)
{
    isSearchHover_ = isHover;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    auto inputEventHub = host->GetOrCreateInputEventHub();
    auto hoverEffect = inputEventHub->GetHoverEffect();
    if (hoverEffect == HoverEffectType::NONE || hoverEffect == HoverEffectType::SCALE) {
        return;
    }
    if (!isSearchPress_ && (enabled || !isHover)) {
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        auto searchTheme = GetTheme();
        CHECK_NULL_VOID(searchTheme);
        auto searchHoverColor = searchTheme->GetHoverColor();
        AnimateSearchTouchAndHover(renderContext, isHover ? transparentColor_ : searchHoverColor,
            isHover ? searchHoverColor : transparentColor_, HOVER_DURATION, Curves::FRICTION);
    }
}

void SearchPattern::InitTouchEvent()
{
    if (searchTouchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto infoTouches = info.GetTouches();
        CHECK_EQUAL_VOID(infoTouches.empty(), true);
        auto touchType = infoTouches.front().GetTouchType();
        if (touchType == TouchType::MOVE) {
            return;
        }
        pattern->OnTouchDownOrUp(touchType == TouchType::DOWN);
    };
    searchTouchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(searchTouchListener_);
}

void SearchPattern::OnTouchDownOrUp(bool isDown)
{
    isSearchPress_ = isDown;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto searchEventHub = GetEventHub<SearchEventHub>();
    CHECK_NULL_VOID(searchEventHub);
    auto renderContext = host->GetRenderContext();
    auto searchTheme = GetTheme();
    CHECK_NULL_VOID(searchTheme);
    auto searchTouchColor = searchTheme->GetTouchColor();
    AnimateSearchTouchAndHover(renderContext, isDown ? transparentColor_ : searchTouchColor,
        isDown ? searchTouchColor : transparentColor_, TOUCH_DURATION, Curves::FRICTION);
}

void SearchPattern::InitFocusEvent(const RefPtr<FocusHub>& focusHub)
{
    auto focusTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        if (!pattern) {
            return;
        }
        bool backwardFocusMovement = false;
        bool forwardFocusMovement = false;
        auto host = pattern->GetHost();
        if (host) {
            auto rootHub = host->GetOrCreateFocusHub()->GetRootFocusHub();
            backwardFocusMovement = rootHub && rootHub->HasBackwardFocusMovementInChildren();
            forwardFocusMovement = rootHub && rootHub->HasForwardFocusMovementInChildren();
            if (rootHub) {
                rootHub->ClearFocusMovementFlagsInChildren();
            }
        }
        pattern->HandleFocusEvent(forwardFocusMovement, backwardFocusMovement);
    };
    focusHub->SetOnFocusInternal(focusTask);
    auto blurTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleBlurEvent();
    };
    focusHub->SetOnBlurInternal(blurTask);
}

void SearchPattern::HandleFocusEvent(bool forwardFocusMovement, bool backwardFocusMovement)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->SetIsFocusedBeforeClick(true);

    focusChoice_ = FocusChoice::SEARCH;
    if (forwardFocusMovement || backwardFocusMovement) { // Don't update focus if no factical focus movement
        focusChoice_ = backwardFocusMovement ? FocusChoice::SEARCH_BUTTON : FocusChoice::SEARCH;
        if (focusChoice_ == FocusChoice::SEARCH_BUTTON && !isSearchButtonEnabled_) {
            bool isCancelHidden = NearZero(cancelButtonSize_.Height());
            focusChoice_ = isCancelHidden ? FocusChoice::SEARCH : FocusChoice::CANCEL_BUTTON;
        }
    }
    PaintFocusState(!(forwardFocusMovement || backwardFocusMovement));
}

void SearchPattern::HandleBlurEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto searchTheme = GetTheme();
    CHECK_NULL_VOID(searchTheme);
    // 失焦时判断是否进行了获焦反色，恢复默认态
    if (isFocusBgColorSet_) {
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateBackgroundColor(searchNormalColor_);
        isFocusBgColorSet_ = false;
    }
    if (isFocusIconColorSet_) {
        SetSymbolSearchIconColor(searchTheme->GetSymbolIconColor());
        isFocusIconColorSet_ = false;
    }
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    if (isFocusTextColorSet_) {
        textFieldLayoutProperty->UpdateTextColor(searchTheme->GetTextColor());
        isFocusTextColorSet_ = false;
    }
    if (isFocusPlaceholderColorSet_) {
        textFieldLayoutProperty->UpdatePlaceholderTextColor(searchTheme->GetPlaceholderColor());
        isFocusPlaceholderColorSet_ = false;
    }
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    textFieldPattern->HandleBlurEvent();
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(SEARCH_TEXTINPUT_BORDER_WIDTH);
    textFieldLayoutProperty->UpdateBorderWidth(borderWidth);
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
    auto textFieldGeometryNode = textFieldFrameNode->GetGeometryNode();
    CHECK_NULL_VOID(textFieldGeometryNode);
    auto textFieldFrameRect = textFieldGeometryNode->GetFrameRect();
    auto relTextFieldLocalLocation = Offset(info.GetLocalLocation().GetX() - textFieldFrameRect.GetX(),
        info.GetLocalLocation().GetY() - textFieldFrameRect.GetY());
    info.SetLocalLocation(relTextFieldLocalLocation);
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

void SearchPattern::ToJsonValueForTextField(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(textFieldLayoutProperty);
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    CHECK_NULL_VOID(textFieldPattern);
    auto searchTheme = GetTheme();
    CHECK_NULL_VOID(searchTheme);

    json->PutExtAttr("value", textFieldPattern->GetTextValue().c_str(), filter);
    json->PutExtAttr("placeholder", UtfUtils::Str16DebugToStr8(textFieldPattern->GetPlaceHolder()).c_str(), filter);
    json->PutExtAttr("placeholderColor", textFieldPattern->GetPlaceholderColor().c_str(), filter);
    json->PutExtAttr("placeholderFont", textFieldPattern->GetPlaceholderFont().c_str(), filter);
    json->PutExtAttr("textAlign", V2::ConvertWrapTextAlignToString(textFieldPattern->GetTextAlign()).c_str(), filter);
    auto textColor = textFieldLayoutProperty->GetTextColor().value_or(searchTheme->GetTextColor());
    json->PutExtAttr("fontColor", textColor.ColorToString().c_str(), filter);
    auto textFontJson = JsonUtil::Create(true);
    textFontJson->Put("fontSize", textFieldPattern->GetFontSize().c_str());
    textFontJson->Put("fontStyle",
        textFieldPattern->GetItalicFontStyle() == Ace::FontStyle::NORMAL ? "FontStyle.Normal" : "FontStyle.Italic");
    textFontJson->Put("fontWeight", V2::ConvertWrapFontWeightToStirng(textFieldPattern->GetFontWeight()).c_str());
    textFontJson->Put("fontFamily", textFieldPattern->GetFontFamily().c_str());
    json->PutExtAttr("textFont", textFontJson->ToString().c_str(), filter);
    json->PutExtAttr("copyOption",
        ConvertCopyOptionsToString(textFieldLayoutProperty->GetCopyOptionsValue(CopyOptions::Local)).c_str(), filter);
    auto maxLength = GetMaxLength();
    json->PutExtAttr(
        "maxLength", GreatOrEqual(maxLength, Infinity<uint32_t>()) ? "INF" : std::to_string(maxLength).c_str(), filter);
    json->PutExtAttr("type", SearchTypeToString().c_str(), filter);
    textFieldLayoutProperty->HasCopyOptions();
    json->PutExtAttr(
        "letterSpacing", textFieldLayoutProperty->GetLetterSpacing().value_or(Dimension()).ToString().c_str(), filter);
    json->PutExtAttr(
        "lineHeight", textFieldLayoutProperty->GetLineHeight().value_or(0.0_vp).ToString().c_str(), filter);
    json->PutExtAttr("halfLeading", textFieldLayoutProperty->GetHalfLeading().value_or(false), filter);
    auto jsonDecoration = JsonUtil::Create(true);
    std::string type = V2::ConvertWrapTextDecorationToStirng(
        textFieldLayoutProperty->GetTextDecoration().value_or(TextDecoration::NONE));
    jsonDecoration->Put("type", type.c_str());
    jsonDecoration->Put(
        "color", textFieldLayoutProperty->GetTextDecorationColor().value_or(Color::BLACK).ColorToString().c_str());
    std::string style = V2::ConvertWrapTextDecorationStyleToString(
        textFieldLayoutProperty->GetTextDecorationStyle().value_or(TextDecorationStyle::SOLID));
    jsonDecoration->Put("style", style.c_str());
    json->PutExtAttr("decoration", jsonDecoration->ToString().c_str(), filter);
    json->PutExtAttr(
        "minFontSize", textFieldLayoutProperty->GetAdaptMinFontSize().value_or(Dimension()).ToString().c_str(), filter);
    json->PutExtAttr(
        "maxFontSize", textFieldLayoutProperty->GetAdaptMaxFontSize().value_or(Dimension()).ToString().c_str(), filter);
    json->PutExtAttr(
        "minFontScale", std::to_string(textFieldLayoutProperty->GetMinFontScale().value_or(0.0f)).c_str(), filter);
    json->PutExtAttr(
        "maxFontScale", std::to_string(textFieldLayoutProperty->GetMaxFontScale().value_or(
		          static_cast<float>(INT32_MAX))).c_str(), filter);
    json->PutExtAttr("inputFilter", textFieldLayoutProperty->GetInputFilterValue("").c_str(), filter);
    json->PutExtAttr(
        "textIndent", textFieldLayoutProperty->GetTextIndent().value_or(0.0_vp).ToString().c_str(), filter);
    json->PutExtAttr("enablePreviewText", textFieldPattern->GetSupportPreviewText(), filter);
    textFieldPattern->ToJsonValueSelectOverlay(json, filter);
    json->PutExtAttr("stopBackPress", textFieldLayoutProperty->GetStopBackPressValue(true), filter);
    json->PutExtAttr("keyboardAppearance", static_cast<int32_t>(textFieldPattern->GetKeyboardAppearance()), filter);
}

std::string SearchPattern::SearchTypeToString() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_RETURN(textFieldFrameNode, "");
    auto layoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    switch (layoutProperty->GetTextInputTypeValue(TextInputType::UNSPECIFIED)) {
        case TextInputType::NUMBER:
            return "SearchType.NUMBER";
        case TextInputType::EMAIL_ADDRESS:
            return "SearchType.EMAIL";
        case TextInputType::PHONE:
            return "SearchType.PHONE_NUMBER";
        case TextInputType::URL:
            return "SearchType.URL";
        default:
            return "SearchType.NORMAL";
    }
}

void SearchPattern::ToJsonValueForSearchIcon(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto searchIconFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(IMAGE_INDEX));
    CHECK_NULL_VOID(searchIconFrameNode);
    auto searchIconJson = JsonUtil::Create(true);

    // icon size
    auto searchIconGeometryNode = searchIconFrameNode->GetGeometryNode();
    CHECK_NULL_VOID(searchIconGeometryNode);
    auto searchIconFrameSize = searchIconGeometryNode->GetFrameSize().Width();
    auto searchLayoutProperty = host->GetLayoutProperty<SearchLayoutProperty>();
    CHECK_NULL_VOID(searchLayoutProperty);
    auto searchIconSize = searchLayoutProperty->GetSearchIconUDSizeValue(Dimension(searchIconFrameSize)).ConvertToPx();
    searchIconJson->Put("size", Dimension(searchIconSize, DimensionUnit::PX).ToString().c_str());

    if (searchIconFrameNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        auto symbolLayoutProperty = searchIconFrameNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolLayoutProperty);
        // icon color
        auto searchIconColor = symbolLayoutProperty->GetSymbolColorList();
        if (searchIconColor.has_value()) {
            searchIconJson->Put("color", SymbolColorToString(searchIconColor.value()).c_str());
        } else {
            searchIconJson->Put("color", std::string("").c_str());
        }

        // icon path
        auto symbolSourceInfo = symbolLayoutProperty->GetSymbolSourceInfo().value_or(SymbolSourceInfo());
        searchIconJson->Put("src", static_cast<int64_t>(symbolSourceInfo.GetUnicode()));
        json->PutExtAttr("icon", static_cast<int64_t>(symbolSourceInfo.GetUnicode()), filter);
        json->PutExtAttr("searchIcon", searchIconJson, filter);
    } else {
        auto imageLayoutProperty = searchIconFrameNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        // icon color
        auto searchIconColor = imageLayoutProperty->GetImageSourceInfo()->GetFillColor().value_or(Color());
        searchIconJson->Put("color", searchIconColor.ColorToString().c_str());

        // icon path
        auto searchIconPath = imageLayoutProperty->GetImageSourceInfo()->GetSrc();
        searchIconJson->Put("src", searchIconPath.c_str());
        json->PutExtAttr("icon", searchIconPath.c_str(), filter);
        json->PutExtAttr("searchIcon", searchIconJson, filter);
    }
}

void SearchPattern::ToJsonValueForCancelButton(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<SearchLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto cancelImageFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    CHECK_NULL_VOID(cancelImageFrameNode);
    auto cancelButtonJson = JsonUtil::Create(true);
    ToJsonValueForCancelButtonStyle(
        cancelButtonJson, layoutProperty->GetCancelButtonStyle().value_or(CancelButtonStyle::INPUT));
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
    if (cancelImageFrameNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        auto symbolLayoutProperty = cancelImageFrameNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolLayoutProperty);
        // icon color & right icon src path
        auto searchIconColor = symbolLayoutProperty->GetSymbolColorList();
        if (searchIconColor.has_value()) {
            cancelIconJson->Put("color", SymbolColorToString(searchIconColor.value()).c_str());
        } else {
            cancelIconJson->Put("color", std::string("").c_str());
        }
        auto symbolSourceInfo = symbolLayoutProperty->GetSymbolSourceInfo().value_or(SymbolSourceInfo());
        cancelIconJson->Put("src", static_cast<int64_t>(symbolSourceInfo.GetUnicode()));
        cancelButtonJson->Put("icon", cancelIconJson);
        json->PutExtAttr("cancelButton", cancelButtonJson, filter);
    } else {
        auto cancelImageLayoutProperty = cancelImageFrameNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(cancelImageLayoutProperty);
        // icon color
        auto cancelImageRenderProperty = cancelImageFrameNode->GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_VOID(cancelImageRenderProperty);
        auto cancelIconColor = cancelImageRenderProperty->GetSvgFillColor().value_or(Color());
        cancelIconJson->Put("color", cancelIconColor.ColorToString().c_str());
        // right icon src path
        auto cancelImageSrc = cancelImageLayoutProperty->GetImageSourceInfo()->GetSrc();
        cancelIconJson->Put("src", cancelImageSrc.c_str());
        cancelButtonJson->Put("icon", cancelIconJson);
        json->PutExtAttr("cancelButton", cancelButtonJson, filter);
    }
}

void SearchPattern::ToJsonValueForSearchButtonOption(
    std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto searchButtonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(BUTTON_INDEX));
    CHECK_NULL_VOID(searchButtonFrameNode);
    auto searchButtonLayoutProperty = searchButtonFrameNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(searchButtonLayoutProperty);
    auto searchTheme = GetTheme();
    CHECK_NULL_VOID(searchTheme);
    auto searchButtonJson = JsonUtil::Create(true);

    // font size
    auto searchButtonFontSize = searchButtonLayoutProperty->GetFontSize().value_or(Dimension(0, DimensionUnit::VP));
    searchButtonJson->Put("fontSize", searchButtonFontSize.ToString().c_str());

    // font color
    auto searchButtonFontColor = searchButtonLayoutProperty->GetFontColor().value_or(
        searchTheme->GetSearchButtonTextColor());
    searchButtonJson->Put("fontColor", searchButtonFontColor.ColorToString().c_str());
    auto searchButtonAutoDisable = searchButtonLayoutProperty->GetAutoDisable().value_or(false);
    searchButtonJson->Put("autoDisable", searchButtonAutoDisable);
    json->PutExtAttr("searchButtonOption", searchButtonJson, filter);
}

void SearchPattern::ToJsonValueForCursor(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_VOID(textFieldFrameNode);
    auto textFieldPaintProperty = textFieldFrameNode->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(textFieldPaintProperty);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(textFieldTheme);
    auto cursorJson = JsonUtil::Create(true);

    // color
    auto caretColor = textFieldPaintProperty->GetCursorColor().value_or(textFieldTheme->GetCursorColor());
    cursorJson->Put("color", caretColor.ColorToString().c_str());
    auto caretWidth = textFieldPaintProperty->GetCursorWidth().value_or(Dimension(0, DimensionUnit::VP));
    cursorJson->Put("width", caretWidth.ToString().c_str());
    json->PutExtAttr("caretStyle", cursorJson, filter);
    auto selectedBackgroundColor = textFieldPaintProperty->GetSelectedBackgroundColor().value_or(Color());
    json->PutExtAttr("selectedBackgroundColor", selectedBackgroundColor.ColorToString().c_str(), filter);
}

void SearchPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    Pattern::ToJsonValue(json, filter);

    ToJsonValueForTextField(json, filter);
    ToJsonValueForSearchIcon(json, filter);
    ToJsonValueForCancelButton(json, filter);
    ToJsonValueForCursor(json, filter);
    ToJsonValueForSearchButtonOption(json, filter);
}

void SearchPattern::UpdateDividerColorMode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto dividerFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(DIVIDER_INDEX));
    CHECK_NULL_VOID(dividerFrameNode);
    auto searchTheme = GetTheme();
    CHECK_NULL_VOID(searchTheme);
    auto searchDividerColor = searchTheme->GetSearchDividerColor();
    auto dividerRenderProperty = dividerFrameNode->GetPaintProperty<DividerRenderProperty>();
    CHECK_NULL_VOID(dividerRenderProperty);
    dividerRenderProperty->UpdateDividerColor(searchDividerColor);
    dividerFrameNode->MarkModifyDone();
    dividerFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void SearchPattern::UpdateCancelButtonColorMode()
{
    auto cancelButtonNode = cancelButtonNode_.Upgrade();
    CHECK_NULL_VOID(cancelButtonNode);
    auto searchTheme = GetTheme();
    CHECK_NULL_VOID(searchTheme);
    auto cancelButtonRenderContext = cancelButtonNode->GetRenderContext();
    CHECK_NULL_VOID(cancelButtonRenderContext);
    cancelButtonRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(cancelButtonNode->GetChildren().front());
    CHECK_NULL_VOID(textFrameNode);
    auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto buttonLayoutProperty = cancelButtonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    if (!buttonLayoutProperty->HasFontColor()) {
        textLayoutProperty->UpdateTextColor(searchTheme->GetSearchButtonTextColor());
    }
    cancelButtonNode->MarkModifyDone();
    cancelButtonNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void SearchPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetNeedCallChildrenUpdate(false);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(textFieldTheme);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto searchTheme = GetTheme();
    CHECK_NULL_VOID(searchTheme);
    UpdateCancelButtonColorMode();
    auto buttonNode = buttonNode_.Upgrade();
    if (buttonNode) {
        auto buttonRenderContext = buttonNode->GetRenderContext();
        CHECK_NULL_VOID(buttonRenderContext);
        buttonRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
        auto textFrameNode = AceType::DynamicCast<FrameNode>(buttonNode->GetChildren().front());
        CHECK_NULL_VOID(textFrameNode);
        auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_VOID(buttonLayoutProperty);
        if (!buttonLayoutProperty->HasFontColor()) {
            textLayoutProperty->UpdateTextColor(searchTheme->GetSearchButtonTextColor());
        }
        buttonNode->MarkModifyDone();
        buttonNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    auto textField = textField_.Upgrade();
    if (textField) {
        auto textFieldLayoutProperty = textField->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_VOID(textFieldLayoutProperty);
        textFieldLayoutProperty->UpdateTextColor(searchTheme->GetTextColor());
        textFieldLayoutProperty->UpdatePlaceholderTextColor(searchTheme->GetPlaceholderColor());
        textField->MarkModifyDone();
        textField->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    UpdateDividerColorMode();
}

bool SearchPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    auto result = false;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, result);

    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, result);
    // need to get theme according to theme scope id to update searchTheme_ and searchNormalColor_
    auto searchTheme = pipeline->GetTheme<SearchTheme>(themeScopeId);
    CHECK_NULL_RETURN(searchTheme, result);
    auto textFieldTheme = pipeline->GetTheme<TextFieldTheme>(themeScopeId);
    CHECK_NULL_RETURN(textFieldTheme, result);
    searchTheme_ = searchTheme; // update searchTheme_
    searchNormalColor_ = textFieldTheme->GetBgColor(); // update searchNormalColor_

    if (!ButtonNodeOnThemeScopeUpdate(searchTheme)) {
        return result;
    }

    if (!IconNodeOnThemeScopeUpdate(searchTheme)) {
        return result;
    }

    HandleBackgroundColor();
    UpdateDividerColorMode();

    TextNodeOnThemeScopeUpdate(searchTheme, textFieldTheme);

    return result;
}

bool SearchPattern::ButtonNodeOnThemeScopeUpdate(const RefPtr<SearchTheme>& searchTheme)
{
    CHECK_NULL_RETURN(searchTheme, false);
    auto buttonNode = buttonNode_.Upgrade();
    if (buttonNode) {
        auto textFrameNode = AceType::DynamicCast<FrameNode>(buttonNode->GetChildren().front());
        CHECK_NULL_RETURN(textFrameNode, false);
        auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_RETURN(textLayoutProperty, false);
        auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_RETURN(buttonLayoutProperty, false);

        if (!buttonLayoutProperty->HasFontColor()) {
            textLayoutProperty->UpdateTextColor(searchTheme->GetSearchButtonTextColor());
            buttonNode->MarkModifyDone();
            buttonNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    }
    return true;
}

bool SearchPattern::IconNodeOnThemeScopeUpdate(const RefPtr<SearchTheme>& searchTheme)
{
    CHECK_NULL_RETURN(searchTheme, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto iconFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(IMAGE_INDEX));
    CHECK_NULL_RETURN(iconFrameNode, false);
    auto cancelIconFrameNode = AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    CHECK_NULL_RETURN(cancelIconFrameNode, false);
    auto searchLayoutProperty = host->GetLayoutProperty<SearchLayoutProperty>();
    CHECK_NULL_RETURN(searchLayoutProperty, false);

    auto iconColor = Color(iconFrameNode->GetTag() == V2::SYMBOL_ETS_TAG ?
        searchTheme->GetSymbolIconColor() : searchTheme->GetSearchIconColor());
    if (!searchLayoutProperty->HasSearchIconColor()) {
        SetSearchIconColor(iconColor);
    }
    auto cancelIconColor = Color(cancelIconFrameNode->GetTag() == V2::SYMBOL_ETS_TAG ?
        searchTheme->GetSymbolIconColor() : searchTheme->GetSearchIconColor());
    if (!searchLayoutProperty->HasCancelIconColor()) {
        SetCancelIconColor(cancelIconColor);
    }
    return true;
}

bool SearchPattern::TextNodeOnThemeScopeUpdate(const RefPtr<SearchTheme>& searchTheme,
    const RefPtr<TextFieldTheme>& textFieldTheme)
{
    CHECK_NULL_RETURN(searchTheme, false);
    CHECK_NULL_RETURN(textFieldTheme, false);
    auto textField = textField_.Upgrade();
    if (textField) {
        auto needUpdateNode = false;
        auto textFieldLayoutProperty = textField->GetLayoutProperty<TextFieldLayoutProperty>();
        CHECK_NULL_RETURN(textFieldLayoutProperty, false);
        auto textPaintProperty = textField->GetPaintProperty<TextFieldPaintProperty>();
        CHECK_NULL_RETURN(textPaintProperty, false);
 
        if (!textPaintProperty->HasTextColorFlagByUser()) {
            textFieldLayoutProperty->UpdateTextColor(searchTheme->GetTextColor());
            needUpdateNode = true;
        }

        if (!textPaintProperty->HasPlaceholderColorFlagByUser()) {
            textFieldLayoutProperty->UpdatePlaceholderTextColor(searchTheme->GetPlaceholderColor());
            needUpdateNode = true;
        }
 
        if (!textPaintProperty->HasCaretColorFlagByUser()) {
            textPaintProperty->UpdateCursorColor(textFieldTheme->GetCursorColor());
            textField->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
 
        if (needUpdateNode) {
            textField->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    }
    return true;
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

void SearchPattern::ToJsonValueForCancelButtonStyle(
    std::unique_ptr<JsonValue>& cancelButtonJson, const CancelButtonStyle& cancelButtonStyle) const
{
    if (cancelButtonStyle == CancelButtonStyle::CONSTANT) {
        cancelButtonJson->Put("style", "CancelButtonStyle.CONSTANT");
    } else if (cancelButtonStyle == CancelButtonStyle::INVISIBLE) {
        cancelButtonJson->Put("style", "CancelButtonStyle.INVISIBLE");
    } else {
        cancelButtonJson->Put("style", "CancelButtonStyle.INPUT");
    }
}

std::string SearchPattern::SymbolColorToString(std::vector<Color>& colors) const
{
    if (colors.size() <= 0) {
        return "";
    }
    auto colorStr = std::string("[");
    for (auto color : colors) {
        colorStr.append(color.ColorToString());
        colorStr.append(",");
    }
    colorStr.append("]");
    return colorStr;
}

void SearchPattern::InitIconColorSize()
{
    InitSearchIconColorSize();
    InitCancelIconColorSize();
}

void SearchPattern::InitSearchIconColorSize()
{
    auto searchTheme = GetTheme();
    CHECK_NULL_VOID(searchTheme);
    GetSearchNode()->SetSearchSymbolIconColor(Color(searchTheme->GetSymbolIconColor()));
    GetSearchNode()->SetSearchSymbolIconSize(searchTheme->GetSymbolIconHeight());
    GetSearchNode()->SetSearchImageIconColor(Color(searchTheme->GetSearchIconColor()));
    GetSearchNode()->SetSearchImageIconSize(searchTheme->GetIconHeight());
}

void SearchPattern::InitCancelIconColorSize()
{
    auto searchTheme = GetTheme();
    CHECK_NULL_VOID(searchTheme);
    GetSearchNode()->SetCancelSymbolIconColor(Color(searchTheme->GetSymbolIconColor()));
    GetSearchNode()->SetCancelSymbolIconSize(SYMBOL_ICON_HEIGHT);
    GetSearchNode()->SetCancelImageIconColor(Color(searchTheme->GetSearchIconColor()));
    GetSearchNode()->SetCancelImageIconSize(searchTheme->GetIconHeight());
}

void SearchPattern::CreateSearchIcon(const std::string& src, bool forceUpdate)
{
    CHECK_NULL_VOID(GetSearchNode());
    if (GetSearchNode()->HasSearchIconNodeCreated() && !forceUpdate) {
        UpdateSearchSymbolIconColor();
        return;
    }
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) &&
        src.empty() && SystemProperties::IsNeedSymbol()) {
        CreateOrUpdateSymbol(IMAGE_INDEX, !GetSearchNode()->HasSearchIconNodeCreated(), false);
    } else {
        GetSearchNode()->SetSearchImageIconOptions(IconOptions(src));
        CreateOrUpdateImage(IMAGE_INDEX, !GetSearchNode()->HasSearchIconNodeCreated());
    }
    GetSearchNode()->UpdateHasSearchIconNodeCreated(true);
}

void SearchPattern::UpdateSearchSymbolIconColor()
{
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(GetSearchNode());
    auto searchButtonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(IMAGE_INDEX));
    CHECK_NULL_VOID(searchButtonFrameNode);
    auto layoutProperty = searchButtonFrameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateSymbolColorList({ GetSearchNode()->GetSearchSymbolIconColor() });
    auto searchTheme = GetTheme();
    CHECK_NULL_VOID(searchTheme);
    if (isFocusIconColorSet_ && GetDefaultIconColor(IMAGE_INDEX) == searchTheme->GetSymbolIconColor()) {
        SetSymbolSearchIconColor(searchTheme->GetFocusIconColor());
    }
}

void SearchPattern::CreateCancelIcon()
{
    CHECK_NULL_VOID(GetSearchNode());
    if (GetSearchNode()->HasCancelIconNodeCreated()) {
        UpdateCancelSymbolIconColor();
        return;
    }
    if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) &&
        SystemProperties::IsNeedSymbol()) {
        CreateOrUpdateSymbol(CANCEL_IMAGE_INDEX, !GetSearchNode()->HasCancelIconNodeCreated(), false);
    } else {
        GetSearchNode()->SetCancelImageIconOptions(IconOptions());
        CreateOrUpdateImage(CANCEL_IMAGE_INDEX, !GetSearchNode()->HasCancelIconNodeCreated());
    }
    GetSearchNode()->UpdateHasCancelIconNodeCreated(true);
}

void SearchPattern::UpdateCancelSymbolIconColor()
{
    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(GetSearchNode());
    auto cancelButtonFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    auto layoutProperty = cancelButtonFrameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateSymbolColorList({ GetSearchNode()->GetCancelSymbolIconColor() });
}

void SearchPattern::CreateOrUpdateSymbol(int32_t index, bool isCreateNode, bool isFromModifier)
{
    CHECK_NULL_VOID(GetSearchNode());
    imageClickListener_ = nullptr;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto searchTheme = GetTheme();
    CHECK_NULL_VOID(searchTheme);
    auto iconFrameNode = FrameNode::GetOrCreateFrameNode(
        V2::SYMBOL_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto layoutProperty = iconFrameNode->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->UpdateSymbolSourceInfo(index == IMAGE_INDEX ? SymbolSourceInfo(searchTheme->GetSearchSymbolId())
                                                                : SymbolSourceInfo(searchTheme->GetCancelSymbolId()));
    layoutProperty->UpdateFontSize(
        index == IMAGE_INDEX ? GetSearchNode()->GetSearchSymbolIconSize() : GetSearchNode()->GetCancelSymbolIconSize());
    layoutProperty->UpdateSymbolColorList({index == IMAGE_INDEX ? GetSearchNode()->GetSearchSymbolIconColor()
                                                                : GetSearchNode()->GetCancelSymbolIconColor()});
    float maxFontScale = MAX_FONT_SCALE;
    if (layoutProperty->GetFontSize()->Unit() != DimensionUnit::VP) {
        maxFontScale = std::min(pipeline->GetMaxAppFontScale(), MAX_FONT_SCALE);
    }
    layoutProperty->UpdateMaxFontScale(maxFontScale);
    auto parentInspector = GetSearchNode()->GetInspectorIdValue("");
    iconFrameNode->UpdateInspectorId(INSPECTOR_PREFIX + SPECICALIZED_INSPECTOR_INDEXS[index] + parentInspector);

    if (isFromModifier) {
        UpdateSymbolIconProperties(iconFrameNode, index);
    }

    if (isCreateNode) {
        iconFrameNode->MountToParent(GetSearchNode());
        if (index == CANCEL_IMAGE_INDEX) {
            auto cancelButtonEvent = iconFrameNode->GetEventHub<ButtonEventHub>();
            CHECK_NULL_VOID(cancelButtonEvent);
            cancelButtonEvent->SetEnabled(false);
        }
        iconFrameNode->MarkModifyDone();
    } else {
        auto oldFrameNode = AceType::DynamicCast<FrameNode>(GetSearchNode()->GetChildAtIndex(index));
        CHECK_NULL_VOID(oldFrameNode);
        GetSearchNode()->ReplaceChild(oldFrameNode, iconFrameNode);
        if (index == CANCEL_IMAGE_INDEX) {
            UpdateIconChangeEvent();
        }
        iconFrameNode->MarkModifyDone();
        iconFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void SearchPattern::CreateOrUpdateImage(int32_t index, bool isCreateNode)
{
    CHECK_NULL_VOID(GetSearchNode());
    imageClickListener_ = nullptr;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto iconFrameNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    UpdateImageIconProperties(iconFrameNode, index);
    if (isCreateNode) {
        iconFrameNode->MountToParent(GetSearchNode());
        if (index == CANCEL_IMAGE_INDEX) {
            auto cancelButtonEvent = iconFrameNode->GetEventHub<ButtonEventHub>();
            CHECK_NULL_VOID(cancelButtonEvent);
            cancelButtonEvent->SetEnabled(false);
        }
        iconFrameNode->MarkModifyDone();
    } else {
        auto oldFrameNode = AceType::DynamicCast<FrameNode>(GetSearchNode()->GetChildAtIndex(index));
        CHECK_NULL_VOID(oldFrameNode);
        GetSearchNode()->ReplaceChild(oldFrameNode, iconFrameNode);
        if (index == CANCEL_IMAGE_INDEX) {
            UpdateIconChangeEvent();
        }
        iconFrameNode->MarkModifyDone();
        iconFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void SearchPattern::SetSearchSrcPath(
    const std::string& src, const std::string& bundleName, const std::string& moduleName)
{
    CHECK_NULL_VOID(GetSearchNode());
    auto &imageIconOptions = GetSearchNode()->GetSearchImageIconOptions();
    imageIconOptions.UpdateSrc(std::string(src), std::string(bundleName), std::string(moduleName));
    UpdateImageIconNode(IMAGE_INDEX);
}

void SearchPattern::SetSearchIconSize(const Dimension& value)
{
    CHECK_NULL_VOID(GetSearchNode());
    auto& imageIconOptions = GetSearchNode()->GetSearchImageIconOptions();
    imageIconOptions.UpdateSize(Dimension(value));
    UpdateImageIconNode(IMAGE_INDEX);
}

void SearchPattern::SetSearchIconColor(const Color& color)
{
    CHECK_NULL_VOID(GetSearchNode());
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto iconFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(IMAGE_INDEX));
    CHECK_NULL_VOID(iconFrameNode);
    if (iconFrameNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        GetSearchNode()->SetSearchSymbolIconColor(Color(color));
        auto symbolLayoutProperty = iconFrameNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolLayoutProperty);
        symbolLayoutProperty->UpdateSymbolColorList({color});
        iconFrameNode->MarkModifyDone();
        iconFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    } else {
        auto &imageIconOptions = GetSearchNode()->GetSearchImageIconOptions();
        imageIconOptions.UpdateColor(Color(color));
        auto imageLayoutProperty = iconFrameNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value();
        if (imageSourceInfo.IsSvg()) {
            imageSourceInfo.SetFillColor(color);
            imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
            auto imageRenderProperty = iconFrameNode->GetPaintProperty<ImageRenderProperty>();
            CHECK_NULL_VOID(imageRenderProperty);
            imageRenderProperty->UpdateSvgFillColor(color);
            iconFrameNode->MarkModifyDone();
            iconFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    }
}

void SearchPattern::SetSymbolSearchIconColor(const Color& color)
{
    bool isCurSymbolNode = IsSymbolIcon(IMAGE_INDEX);
    if (isCurSymbolNode) {
        CHECK_NULL_VOID(GetSearchNode());
        GetSearchNode()->SetSearchSymbolIconColor(Color(color));
        UpdateSymbolIconNode(IMAGE_INDEX);
    }
}

void SearchPattern::SetSearchImageIcon(IconOptions& iconOptions)
{
    CHECK_NULL_VOID(GetSearchNode());
    auto& imageIconOptions = GetSearchNode()->GetSearchImageIconOptions();
    if (iconOptions.GetColor().has_value()) {
        imageIconOptions.UpdateColor(iconOptions.GetColor().value());
    }
    if (iconOptions.GetSize().has_value()) {
        imageIconOptions.UpdateSize(ConvertImageIconSizeValue(iconOptions.GetSize().value()));
    }
    if (iconOptions.GetSrc().has_value()) {
        imageIconOptions.UpdateSrc(iconOptions.GetSrc().value_or(""),
            iconOptions.GetBundleName().value_or(""),
            iconOptions.GetModuleName().value_or(""));
    }
    UpdateImageIconNode(IMAGE_INDEX);
}

void SearchPattern::SetSearchSymbolIcon()
{
    UpdateSymbolIconNode(IMAGE_INDEX);
}

void SearchPattern::SetCancelIconSize(const Dimension& value)
{
    CHECK_NULL_VOID(GetSearchNode());
    auto& imageIconOptions = GetSearchNode()->GetCancelImageIconOptions();
    imageIconOptions.UpdateSize(Dimension(value));
    UpdateImageIconNode(CANCEL_IMAGE_INDEX);
}

void SearchPattern::SetCancelIconColor(const Color& color)
{
    CHECK_NULL_VOID(GetSearchNode());
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto cancelIconFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(CANCEL_IMAGE_INDEX));
    CHECK_NULL_VOID(cancelIconFrameNode);
    if (cancelIconFrameNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        GetSearchNode()->SetCancelSymbolIconColor(Color(color));
        auto symbolLayoutProperty = cancelIconFrameNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(symbolLayoutProperty);
        symbolLayoutProperty->UpdateSymbolColorList({color});
        cancelIconFrameNode->MarkModifyDone();
        cancelIconFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    } else {
        auto &imageIconOptions = GetSearchNode()->GetCancelImageIconOptions();
        imageIconOptions.UpdateColor(Color(color));
        auto imageLayoutProperty = cancelIconFrameNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value();
        if (imageSourceInfo.IsSvg()) {
            imageSourceInfo.SetFillColor(color);
            imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
            auto imageRenderProperty = cancelIconFrameNode->GetPaintProperty<ImageRenderProperty>();
            CHECK_NULL_VOID(imageRenderProperty);
            imageRenderProperty->UpdateSvgFillColor(color);
            cancelIconFrameNode->MarkModifyDone();
            cancelIconFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    }
}

void SearchPattern::SetRightIconSrcPath(const std::string& src)
{
    CHECK_NULL_VOID(GetSearchNode());
    auto &imageIconOptions = GetSearchNode()->GetCancelImageIconOptions();
    imageIconOptions.UpdateSrc(std::string(src), "", "");
    UpdateImageIconNode(CANCEL_IMAGE_INDEX);
}

void SearchPattern::SetCancelButtonStyle(const CancelButtonStyle& style)
{
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(GetSearchNode()->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    UpdateChangeEvent(textFieldPattern->GetTextUtf16Value(), static_cast<int16_t>(style));
}

Color SearchPattern::GetDefaultIconColor(int32_t index)
{
    Color defaultIconColor;
    auto searchTheme = GetTheme();
    CHECK_NULL_RETURN(searchTheme, defaultIconColor);
    auto normalIconColor = searchTheme->GetSymbolIconColor();
    defaultIconColor = normalIconColor;
    CHECK_NULL_RETURN(GetSearchNode(), defaultIconColor);
    auto iconFrameNode = AceType::DynamicCast<FrameNode>(GetSearchNode()->GetChildAtIndex(index));
    CHECK_NULL_RETURN(iconFrameNode, defaultIconColor);
    if (iconFrameNode->GetTag() == V2::SYMBOL_ETS_TAG) {
        auto symbolLayoutProperty = iconFrameNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_RETURN(symbolLayoutProperty, defaultIconColor);
        std::vector<Color> symbolColorList = symbolLayoutProperty->GetSymbolColorListValue({ normalIconColor });
        if (symbolColorList.size() >= 1) {
            defaultIconColor = symbolColorList[0];
        }
    } else {
        auto imageLayoutProperty = iconFrameNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_RETURN(imageLayoutProperty, defaultIconColor);
        auto imageSourceInfo = imageLayoutProperty->GetImageSourceInfo().value();
        if (imageSourceInfo.IsSvg()) {
            auto imageRenderProperty = iconFrameNode->GetPaintProperty<ImageRenderProperty>();
            CHECK_NULL_RETURN(imageRenderProperty, defaultIconColor);
            defaultIconColor = imageRenderProperty->GetSvgFillColorValue(normalIconColor);
        }
    }
    return defaultIconColor;
}

void SearchPattern::SetCancelImageIcon(IconOptions& iconOptions)
{
    CHECK_NULL_VOID(GetSearchNode());
    auto& imageIconOptions = GetSearchNode()->GetCancelImageIconOptions();
    if (iconOptions.GetColor().has_value()) {
        imageIconOptions.UpdateColor(iconOptions.GetColor().value());
    }
    if (iconOptions.GetSize().has_value()) {
        imageIconOptions.UpdateSize(ConvertImageIconSizeValue(iconOptions.GetSize().value()));
    }
    if (iconOptions.GetSrc().has_value()) {
        imageIconOptions.UpdateSrc(iconOptions.GetSrc().value(),
            iconOptions.GetBundleName().value_or(""),
            iconOptions.GetModuleName().value_or(""));
    }
    UpdateImageIconNode(CANCEL_IMAGE_INDEX);
}

void SearchPattern::SetCancelSymbolIcon()
{
    UpdateSymbolIconNode(CANCEL_IMAGE_INDEX);
}

void SearchPattern::UpdateImageIconNode(int32_t index)
{
    bool isCurSymbolNode = IsSymbolIcon(index);
    if (isCurSymbolNode) {
        CreateOrUpdateImage(index, false);
    } else {
        auto frameNode = GetHost();
        CHECK_NULL_VOID(frameNode);
        auto iconFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(index));
        UpdateImageIconProperties(iconFrameNode, index);
        iconFrameNode->MarkModifyDone();
        iconFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void SearchPattern::UpdateSymbolIconNode(int32_t index)
{
    bool isCurSymbolNode = IsSymbolIcon(index);
    if (!isCurSymbolNode) {
        CreateOrUpdateSymbol(index, false, true);
    } else {
        auto frameNode = GetHost();
        CHECK_NULL_VOID(frameNode);
        auto iconFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(index));
        UpdateSymbolIconProperties(iconFrameNode, index);
        iconFrameNode->MarkModifyDone();
        iconFrameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void SearchPattern::UpdateImageIconProperties(RefPtr<FrameNode>& iconFrameNode, int32_t index)
{
    CHECK_NULL_VOID(iconFrameNode);
    if (iconFrameNode->GetTag() == V2::IMAGE_ETS_TAG) {
        auto iconOptions = index == IMAGE_INDEX ? GetSearchNode()->GetSearchImageIconOptions()
                                                : GetSearchNode()->GetCancelImageIconOptions();
        auto imageLayoutProperty = iconFrameNode->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(imageLayoutProperty);
        ImageSourceInfo imageSourceInfo("");
        auto imageSourceInfoOp = imageLayoutProperty->GetImageSourceInfo();
        if (imageSourceInfoOp.has_value()) {
            imageSourceInfo = imageSourceInfoOp.value();
        }
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        auto searchTheme = GetTheme();
        CHECK_NULL_VOID(searchTheme);
        auto iconTheme = pipeline->GetTheme<IconTheme>(host->GetThemeScopeId());
        CHECK_NULL_VOID(iconTheme);
        if (iconOptions.GetSrc().value_or("").empty()) {
            imageSourceInfo.SetResourceId(index == IMAGE_INDEX ? InternalResource::ResourceId::SEARCH_SVG
                                                               : InternalResource::ResourceId::CLOSE_SVG);
            auto iconPath = iconTheme->GetIconPath(index == IMAGE_INDEX ? InternalResource::ResourceId::SEARCH_SVG
                                                                        : InternalResource::ResourceId::CLOSE_SVG);
            imageSourceInfo.SetSrc(iconPath, iconOptions.GetColor().value_or(searchTheme->GetSearchIconColor()));
        } else {
            imageSourceInfo.SetSrc(iconOptions.GetSrc().value());
        }
        imageSourceInfo.SetBundleName(iconOptions.GetBundleName().value_or(""));
        imageSourceInfo.SetModuleName(iconOptions.GetModuleName().value_or(""));
        imageSourceInfo.SetFillColor(iconOptions.GetColor().value_or(searchTheme->GetSearchIconColor()));
        imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
        CalcSize imageCalcSize(CalcLength(iconOptions.GetSize().value_or(searchTheme->GetIconHeight())),
            CalcLength(iconOptions.GetSize().value_or(searchTheme->GetIconHeight())));

        imageLayoutProperty->UpdateUserDefinedIdealSize(imageCalcSize);
        auto parentInspector = GetSearchNode()->GetInspectorIdValue("");
        iconFrameNode->UpdateInspectorId(INSPECTOR_PREFIX + SPECICALIZED_INSPECTOR_INDEXS[index] + parentInspector);
        auto imageRenderProperty = iconFrameNode->GetPaintProperty<ImageRenderProperty>();
        CHECK_NULL_VOID(imageRenderProperty);
        imageSourceInfo.SetFillColor(iconOptions.GetColor().value_or(searchTheme->GetSearchIconColor()));
        imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
        imageRenderProperty->UpdateSvgFillColor(iconOptions.GetColor().value_or(searchTheme->GetSearchIconColor()));
    }
}

void SearchPattern::UpdateSymbolIconProperties(RefPtr<FrameNode>& iconFrameNode, int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(iconFrameNode);
    auto searchTheme = GetTheme();
    CHECK_NULL_VOID(searchTheme);
    auto layoutProperty = host->GetLayoutProperty<SearchLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto symbolLayoutProperty = iconFrameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(symbolLayoutProperty);
    symbolLayoutProperty->UpdateSymbolSourceInfo(index == IMAGE_INDEX
                                                     ? SymbolSourceInfo(searchTheme->GetSearchSymbolId())
                                                     : SymbolSourceInfo(searchTheme->GetCancelSymbolId()));
    auto defaultSymbolIconSize = (index == IMAGE_INDEX ? GetSearchNode()->GetSearchSymbolIconSize()
                                                       : GetSearchNode()->GetCancelSymbolIconSize());
    symbolLayoutProperty->UpdateFontSize(defaultSymbolIconSize);
    symbolLayoutProperty->UpdateSymbolColorList({ index == IMAGE_INDEX ? GetSearchNode()->GetSearchSymbolIconColor()
                                                                       : GetSearchNode()->GetCancelSymbolIconColor() });
    auto parentInspector = GetSearchNode()->GetInspectorIdValue("");
    iconFrameNode->UpdateInspectorId(INSPECTOR_PREFIX + SPECICALIZED_INSPECTOR_INDEXS[index] + parentInspector);
    if (index == IMAGE_INDEX) {
        auto iconSymbol = layoutProperty->GetSearchIconSymbol();
        if (iconSymbol != nullptr) {
            iconSymbol(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(iconFrameNode)));
        }
    } else {
        auto iconSymbol = layoutProperty->GetCancelIconSymbol();
        if (iconSymbol != nullptr) {
            iconSymbol(AccessibilityManager::WeakClaim(AccessibilityManager::RawPtr(iconFrameNode)));
        }
    }
    // reset symbol effect
    auto symbolEffectOptions = symbolLayoutProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
    symbolEffectOptions.SetIsTxtActive(false);
    symbolLayoutProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
    auto fontSize = symbolLayoutProperty->GetFontSize().value_or(defaultSymbolIconSize);
    if (GreatOrEqualCustomPrecision(fontSize.ConvertToPxDistribute(GetMinFontScale(), GetMaxFontScale()),
        ICON_MAX_SIZE.ConvertToPx())) {
        symbolLayoutProperty->UpdateFontSize(ICON_MAX_SIZE);
    }
}

bool SearchPattern::IsSymbolIcon(int32_t index)
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, false);
    auto iconFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildAtIndex(index));
    CHECK_NULL_RETURN(iconFrameNode, false);
    return iconFrameNode->GetTag() == V2::SYMBOL_ETS_TAG;
}

void SearchPattern::UpdateIconChangeEvent()
{
    CHECK_NULL_VOID(GetSearchNode());
    auto textFieldFrameNode = AceType::DynamicCast<FrameNode>(GetSearchNode()->GetChildAtIndex(TEXTFIELD_INDEX));
    auto textFieldPattern = textFieldFrameNode->GetPattern<TextFieldPattern>();
    UpdateChangeEvent(textFieldPattern->GetTextUtf16Value());
}

const Dimension SearchPattern::ConvertImageIconSizeValue(const Dimension& iconSizeValue)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, iconSizeValue);
    auto maxFontScale = GetMaxFontScale();
    auto minFontScale = GetMinFontScale();
    if (GreatOrEqualCustomPrecision(iconSizeValue.ConvertToPxDistribute(minFontScale, maxFontScale),
        ICON_MAX_SIZE.ConvertToPx())) {
        return ICON_MAX_SIZE;
    }
    if (iconSizeValue.Unit() != DimensionUnit::VP) {
        return Dimension(iconSizeValue.ConvertToPxDistribute(minFontScale, maxFontScale));
    } else {
        return iconSizeValue;
    }
}

float SearchPattern::GetMaxFontScale()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, MAX_FONT_SCALE);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, MAX_FONT_SCALE);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_RETURN(textFieldFrameNode, MAX_FONT_SCALE);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, MAX_FONT_SCALE);

    auto maxFontScale = MAX_FONT_SCALE;
    if (textFieldLayoutProperty->HasMaxFontScale()) {
        maxFontScale = std::min(textFieldLayoutProperty->GetMaxFontScale().value(), maxFontScale);
    } else if (pipeline->GetMaxAppFontScale()) {
        maxFontScale = std::min(pipeline->GetMaxAppFontScale(), maxFontScale);
    }
    return maxFontScale;
}

float SearchPattern::GetMinFontScale()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0.0f);
    auto textFieldFrameNode = DynamicCast<FrameNode>(host->GetChildAtIndex(TEXTFIELD_INDEX));
    CHECK_NULL_RETURN(textFieldFrameNode, 0.0f);
    auto textFieldLayoutProperty = textFieldFrameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, 0.0f);
    auto minFontScale = 0.0f;
    if (textFieldLayoutProperty->HasMinFontScale()) {
        minFontScale = textFieldLayoutProperty->GetMinFontScale().value();
    }
    return minFontScale;
}

} // namespace OHOS::Ace::NG
