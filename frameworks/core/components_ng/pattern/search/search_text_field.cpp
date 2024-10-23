/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/search/search_text_field.h"

#include "core/components_ng/pattern/search/search_event_hub.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float MAX_FONT_SCALE = 2.0f;
} // namespace

RefPtr<FocusHub> SearchTextFieldPattern::GetFocusHub() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, TextFieldPattern::GetFocusHub());
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_RETURN(parentFrameNode, TextFieldPattern::GetFocusHub());
    return parentFrameNode->GetOrCreateFocusHub();
}

void SearchTextFieldPattern::PerformAction(TextInputAction action, bool forceCloseKeyboard)
{
    TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "Search PerformAction %{public}d", static_cast<int32_t>(action));
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
    auto eventHub = parentFrameNode->GetEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->UpdateSubmitEvent(GetTextValue());
    CloseKeyboard(forceCloseKeyboard);
    if (HasFocus()) {
        FocusHub::LostFocusToViewRoot();
    }
}

TextInputAction SearchTextFieldPattern::GetDefaultTextInputAction() const
{
    return TextInputAction::SEARCH;
}

void SearchTextFieldPattern::InitDragEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetDraggable(true);
    TextFieldPattern::InitDragEvent();
}

void SearchTextFieldPattern::ApplyNormalTheme()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto textFieldTheme = GetTheme();
    CHECK_NULL_VOID(textFieldTheme);
    if (!renderContext->HasBackgroundColor()) {
        renderContext->UpdateBackgroundColor(textFieldTheme->GetBgColor());
    }
}

bool SearchTextFieldPattern::IsTextEditableForStylus() const
{
    CHECK_NULL_RETURN(!HasCustomKeyboard(), false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_RETURN(parentFrameNode, false);
    auto focusHub = parentFrameNode->GetFocusHub();
    CHECK_NULL_RETURN(focusHub, false);
    if (!focusHub->IsFocusable() || !parentFrameNode->IsVisible()) {
        return false;
    }
    auto renderContext = parentFrameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto opacity = renderContext->GetOpacity();
    // if opacity is 0.0f, no need to hit frameNode.
    if (NearZero(opacity.value_or(1.0f))) {
        return false;
    }
    return true;
}

void SearchTextFieldPattern::ProcessSelection()
{
    auto textWidth = static_cast<int32_t>(contentController_->GetWideText().length());
    if (SelectOverlayIsOn()) {
        needToRefreshSelectOverlay_ = textWidth > 0;
        UpdateSelection(std::clamp(selectController_->GetStartIndex(), 0, textWidth),
            std::clamp(selectController_->GetEndIndex(), 0, textWidth));
        SetIsSingleHandle(!IsSelected());
        if (isTextChangedAtCreation_ && textWidth == 0) {
            CloseSelectOverlay();
            StartTwinkling();
        }
    } else if (HasFocus() && !IsSelected() && !searchRequestStopTwinkling_) {
        StartTwinkling();
    } else {
        needToRefreshSelectOverlay_ = false;
    }
}

void SearchTextFieldPattern::SearchRequestStartTwinkling()
{
    searchRequestStopTwinkling_ = false;
    StartTwinkling();
}

void SearchTextFieldPattern::SearchRequestStopTwinkling()
{
    searchRequestStopTwinkling_ = true;
    UpdateSelection(0);
    StopTwinkling();
}

void SearchTextFieldPattern::ResetSearchRequestStopTwinkling()
{
    searchRequestStopTwinkling_ = false;
}

bool SearchTextFieldPattern::IsNeedProcessAutoFill()
{
    return false;
}

int32_t SearchTextFieldPattern::GetRequestKeyboardId()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);
    auto searchHost = host->GetAncestorNodeOfFrame();
    CHECK_NULL_RETURN(searchHost, -1);
    return searchHost->GetId();
}

float SearchTextFieldPattern::FontSizeConvertToPx(const Dimension& fontSize)
{
    if (fontSize.Unit() == DimensionUnit::FP) {
        return fontSize.ConvertToPxDistribute(0, MAX_FONT_SCALE);
    } else {
        return fontSize.ConvertToPx();
    }
}
} // namespace OHOS::Ace::NG