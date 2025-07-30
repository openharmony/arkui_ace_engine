/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/rich_editor/rich_editor_model_static.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> RichEditorModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto richEditorPattern = AceType::MakeRefPtr<RichEditorPattern>();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(WeakPtr(richEditorPattern));
    return FrameNode::CreateFrameNode(V2::RICH_EDITOR_ETS_TAG, nodeId, richEditorPattern);
}

RefPtr<RichEditorBaseControllerBase> RichEditorModelStatic::GetRichEditorController(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetRichEditorController();
}

RefPtr<RichEditorBaseControllerBase> RichEditorModelStatic::GetRichEditorStyledStringController(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetRichEditorStyledStringController();
}

void RichEditorModelStatic::SetStyledStringMode(FrameNode* frameNode, bool isStyledStringMode)
{
    auto richEditorPattern = frameNode->GetPattern<RichEditorPattern>();
    richEditorPattern->SetSpanStringMode(isStyledStringMode);
    if (isStyledStringMode) {
        richEditorPattern->SetRichEditorStyledStringController(AceType::MakeRefPtr<RichEditorStyledStringController>());
        richEditorPattern->GetRichEditorStyledStringController()->SetPattern(WeakPtr(richEditorPattern));
    } else {
        richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
        richEditorPattern->GetRichEditorController()->SetPattern(WeakPtr(richEditorPattern));
    }
}

void RichEditorModelStatic::SetOnCut(FrameNode* frameNode, std::function<void(NG::TextCommonEvent&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCut(std::move(func));
}

void RichEditorModelStatic::SetOnCopy(FrameNode* frameNode, std::function<void(NG::TextCommonEvent&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCopy(std::move(func));
}

void RichEditorModelStatic::SetOnPaste(FrameNode* frameNode, std::function<void(NG::TextCommonEvent&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPaste(std::move(func));
}

void RichEditorModelStatic::SetEnterKeyType(FrameNode* frameNode, const std::optional<TextInputAction>& action)
{
    if (action) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "SetEnterKeyType=%{public}d", action.value());
    }
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    if (action) {
        pattern->UpdateTextInputAction(action.value());
    } else {
        pattern->ResetTextInputAction();
    }
}

void RichEditorModelStatic::SetSelectedBackgroundColor(FrameNode* frameNode, const std::optional<Color>& selectedColor)
{
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedBackgroundColor(selectedColor);
}

void RichEditorModelStatic::SetCaretColor(FrameNode* frameNode, const std::optional<Color>& color)
{
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCaretColor(color);
}

void RichEditorModelStatic::SetAboutToDelete(
    FrameNode* frameNode, std::function<bool(const RichEditorDeleteValue&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetAboutToDelete(std::move(func));
}

void RichEditorModelStatic::SetEnableHapticFeedback(FrameNode* frameNode, bool isEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetEnableHapticFeedback(isEnabled);
}

void RichEditorModelStatic::SetCustomKeyboard(FrameNode* frameNode, std::function<void()>&& func,
    const std::optional<bool>& supportAvoidance)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    if (pattern) {
        pattern->SetCustomKeyboard(std::move(func));
        pattern->SetCustomKeyboardOption(supportAvoidance.value_or(false));
    }
}

void RichEditorModelStatic::BindSelectionMenu(FrameNode* frameNode, TextSpanType& editorType, TextResponseType& type,
    std::function<void()>& buildFunc, SelectMenuParam& menuParam)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    if (pattern) {
        pattern->BindSelectionMenu(type, editorType, buildFunc, menuParam);
    }
}
} // namespace OHOS::Ace::NG
