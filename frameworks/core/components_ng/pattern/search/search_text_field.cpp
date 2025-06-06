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

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "core/components/search/search_theme.h"
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
    auto eventHub = parentFrameNode->GetOrCreateEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    // Enter key type callback
    TextFieldCommonEvent event;
    eventHub->FireOnSubmit(GetTextUtf16Value(), event);
    UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "Search.onSubmit");
    TAG_LOGI(
        AceLogTag::ACE_TEXT_FIELD, "nodeId:[%{public}d] Search reportComponentChangeEvent onSubmit", host->GetId());
    // If the developer wants to keep editing, editing will not stop
    if (host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY)) {
        if (event.IsKeepEditable()) {
            return;
        }
    } else {
        if (event.IsKeepEditable() || action == TextInputAction::NEW_LINE) {
            return;
        }
    }
    HandleCloseKeyboard(forceCloseKeyboard);
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
    auto textWidth = static_cast<int32_t>(contentController_->GetTextUtf16Value().length());
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
    auto searchHost = host->GetAncestorNodeOfFrame(true);
    CHECK_NULL_RETURN(searchHost, -1);
    return searchHost->GetId();
}

float SearchTextFieldPattern::FontSizeConvertToPx(const Dimension& fontSize)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, fontSize.ConvertToPx());
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, fontSize.ConvertToPx());
    auto textFieldLayoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(textFieldLayoutProperty, fontSize.ConvertToPx());

    if (fontSize.Unit() == DimensionUnit::FP) {
        auto maxFontScale = MAX_FONT_SCALE;
        if (textFieldLayoutProperty->HasMaxFontScale()) {
            maxFontScale = std::min(textFieldLayoutProperty->GetMaxFontScale().value(), maxFontScale);
        } else {
            maxFontScale = std::min(pipeline->GetMaxAppFontScale(), maxFontScale);
        }
        return fontSize.ConvertToPxDistribute(0, maxFontScale);
    } else {
        return fontSize.ConvertToPx();
    }
}

std::string SearchTextFieldPattern::GetPlaceholderFont() const
{
    auto layoutProperty = GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, "");
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, "");
    auto searchTheme = pipeline->GetTheme<SearchTheme>();
    CHECK_NULL_RETURN(searchTheme, "");
    auto jsonString = TextFieldPattern::GetPlaceholderFont();
    auto jsonValue = JsonUtil::ParseJsonString(jsonString);
    jsonValue->Replace(
        "size", layoutProperty->GetPlaceholderFontSizeValue(searchTheme->GetFontSize()).ToString().c_str());
    return jsonValue->ToString();
}

IMEClient SearchTextFieldPattern::GetIMEClientInfo()
{
    IMEClient clientInfo;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, clientInfo);
    auto parentFrameNode = AceType::DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_RETURN(parentFrameNode, clientInfo);
    clientInfo.nodeId = parentFrameNode->GetId();
    return clientInfo;
}
} // namespace OHOS::Ace::NG
