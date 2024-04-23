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
    auto eventHub = parentFrameNode->GetEventHub<SearchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->UpdateSubmitEvent(GetTextValue());
    CloseKeyboard(forceCloseKeyboard);
    FocusHub::LostFocusToViewRoot();
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
} // namespace OHOS::Ace::NG