/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"

namespace OHOS::Ace::NG {
void RichEditorModelNG::Create(bool isStyledStringMode)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::RICH_EDITOR_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    stack->Push(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, TextAlign, TextAlign::START);
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, WordBreak, WordBreak::BREAK_WORD);
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, Alignment::TOP_LEFT);
    CHECK_NULL_VOID(frameNode);
    auto richEditorPattern = frameNode->GetPattern<RichEditorPattern>();
    richEditorPattern->SetSpanStringMode(isStyledStringMode);
    isStyledStringMode_ = isStyledStringMode;
    if (isStyledStringMode) {
        richEditorPattern->SetRichEditorStyledStringController(AceType::MakeRefPtr<RichEditorStyledStringController>());
        richEditorPattern->GetRichEditorStyledStringController()->SetPattern(WeakPtr(richEditorPattern));
    } else {
        richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
        richEditorPattern->GetRichEditorController()->SetPattern(WeakPtr(richEditorPattern));
    }
    richEditorPattern->InitSurfaceChangedCallback();
    richEditorPattern->InitSurfacePositionChangedCallback();
    richEditorPattern->ClearSelectionMenu();
    auto host = richEditorPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    richEditorPattern->SetSupportPreviewText(pipelineContext->GetSupportPreviewText());
    if (frameNode->IsFirstBuilding()) {
        auto draggable = pipelineContext->GetDraggable<RichEditorTheme>();
        SetDraggable(draggable);
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->SetTextDraggable(true);
    }
}

void RichEditorModelNG::SetDraggable(bool draggable)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDraggable(draggable);
}

RefPtr<RichEditorBaseControllerBase> RichEditorModelNG::GetRichEditorController()
{
    auto richEditorPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<RichEditorPattern>();
    CHECK_NULL_RETURN(richEditorPattern, nullptr);
    if (richEditorPattern->GetSpanStringMode()) {
        return richEditorPattern->GetRichEditorStyledStringController();
    }
    return richEditorPattern->GetRichEditorController();
}

void RichEditorModelNG::SetOnReady(std::function<void()>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReady(std::move(func));
}

void RichEditorModelNG::SetOnReady(FrameNode* frameNode, std::function<void()>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReady(std::move(callback));
}

void RichEditorModelNG::SetOnSelect(std::function<void(const BaseEventInfo*)>&& func)
{
    CHECK_NULL_VOID(!isStyledStringMode_);
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelect(std::move(func));
}

void RichEditorModelNG::SetOnSelect(FrameNode* frameNode, std::function<void(const BaseEventInfo*)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelect(std::move(callback));
}

void RichEditorModelNG::SetOnSelectionChange(std::function<void(const BaseEventInfo*)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelectionChange(std::move(func));
}

void RichEditorModelNG::SetAboutToIMEInput(std::function<bool(const RichEditorInsertValue&)>&& func)
{
    CHECK_NULL_VOID(!isStyledStringMode_);
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetAboutToIMEInput(std::move(func));
}

void RichEditorModelNG::SetAboutToIMEInput(FrameNode* frameNode,
    std::function<bool(const RichEditorInsertValue&)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetAboutToIMEInput(std::move(callback));
}

void RichEditorModelNG::SetOnIMEInputComplete(std::function<void(const RichEditorAbstractSpanResult&)>&& func)
{
    CHECK_NULL_VOID(!isStyledStringMode_);
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnIMEInputComplete(std::move(func));
}

void RichEditorModelNG::SetOnDidIMEInput(std::function<void(const TextRange&)>&& func)
{
    CHECK_NULL_VOID(!isStyledStringMode_);
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidIMEInput(std::move(func));
}

void RichEditorModelNG::SetOnIMEInputComplete(FrameNode* frameNode,
    std::function<void(const RichEditorAbstractSpanResult&)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnIMEInputComplete(std::move(callback));
}

void RichEditorModelNG::SetOnDidIMEInput(FrameNode* frameNode, std::function<void(const TextRange&)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidIMEInput(std::move(callback));
}

void RichEditorModelNG::SetAboutToDelete(std::function<bool(const RichEditorDeleteValue&)>&& func)
{
    CHECK_NULL_VOID(!isStyledStringMode_);
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetAboutToDelete(std::move(func));
}

void RichEditorModelNG::SetAboutToDelete(FrameNode* frameNode, std::function<bool(const RichEditorDeleteValue&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetAboutToDelete(std::move(func));
}

void RichEditorModelNG::SetOnDeleteComplete(std::function<void()>&& func)
{
    CHECK_NULL_VOID(!isStyledStringMode_);
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDeleteComplete(std::move(func));
}

void RichEditorModelNG::SetOnDeleteComplete(FrameNode* frameNode, std::function<void()>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDeleteComplete(std::move(callback));
}

void RichEditorModelNG::SetCustomKeyboard(std::function<void()>&& func, bool supportAvoidance)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    if (pattern) {
        pattern->SetCustomKeyboard(std::move(func));
        pattern->SetCustomKeyboardOption(supportAvoidance);
    }
}

void RichEditorModelNG::SetCopyOption(CopyOptions& copyOptions)
{
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, CopyOption, copyOptions);
}

void RichEditorModelNG::BindSelectionMenu(TextSpanType& editorType, TextResponseType& type,
    std::function<void()>& buildFunc, SelectMenuParam& menuParam)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    if (pattern) {
        pattern->BindSelectionMenu(type, editorType, buildFunc, menuParam.onAppear, menuParam.onDisappear);
    }
}

void RichEditorModelNG::SetOnPaste(std::function<void(NG::TextCommonEvent&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPaste(std::move(func));
}

void RichEditorModelNG::SetOnPaste(FrameNode* frameNode, std::function<void(NG::TextCommonEvent&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnPaste(std::move(func));
}

void RichEditorModelNG::SetPlaceholder(PlaceholderOptions& options)
{
    if (options.value.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, Placeholder, options.value.value());
    }
    if (options.fontSize.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, PlaceholderFontSize, options.fontSize.value());
    }
    if (options.fontStyle.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, PlaceholderItalicFontStyle, options.fontStyle.value());
    }
    if (options.fontWeight.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, PlaceholderFontWeight, options.fontWeight.value());
    }
    if (options.fontColor.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, PlaceholderTextColor, options.fontColor.value());
    }
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, PlaceholderFontFamily, options.fontFamilies);
}

void RichEditorModelNG::SetPlaceholder(FrameNode* frameNode, PlaceholderOptions& options)
{
    if (options.value.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, Placeholder, options.value.value(), frameNode);
    }
    if (options.fontSize.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, PlaceholderFontSize, options.fontSize.value(), frameNode);
    }
    if (options.fontStyle.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextLayoutProperty, PlaceholderItalicFontStyle, options.fontStyle.value(), frameNode);
    }
    if (options.fontWeight.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            TextLayoutProperty, PlaceholderFontWeight, options.fontWeight.value(), frameNode);
    }
    if (options.fontColor.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, PlaceholderTextColor, options.fontColor.value(), frameNode);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, PlaceholderFontFamily, options.fontFamilies, frameNode);
}

void RichEditorModelNG::SetCopyOption(FrameNode* frameNode, CopyOptions& copyOptions)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(TextLayoutProperty, CopyOption, copyOptions, frameNode);
}

void RichEditorModelNG::SetTextDetectEnable(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetTextDetectEnable(value);
}

void RichEditorModelNG::SetSupportPreviewText(bool value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSupportPreviewText(value);
}

void RichEditorModelNG::SetTextDetectConfig(const TextDetectConfig& textDetectConfig)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetTextDetectConfig(textDetectConfig);
}

void RichEditorModelNG::SetTextDetectConfig(FrameNode* frameNode, const TextDetectConfig& textDetectConfig)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetTextDetectConfig(textDetectConfig);
}

void RichEditorModelNG::SetOnSelectionChange(FrameNode* frameNode, std::function<void(const BaseEventInfo*)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSelectionChange(std::move(callback));
}

void RichEditorModelNG::SetTextDetectEnable(FrameNode* frameNode, bool value)
{
    auto richEditorPattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(richEditorPattern);
    richEditorPattern->SetTextDetectEnable(value);
}

void RichEditorModelNG::SetSelectedBackgroundColor(const Color& selectedColor)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedBackgroundColor(selectedColor);
}

void RichEditorModelNG::SetSelectedBackgroundColor(FrameNode* frameNode, const Color& selectedColor)
{
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectedBackgroundColor(selectedColor);
}

void RichEditorModelNG::SetCaretColor(const Color& color)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCaretColor(color);
}

void RichEditorModelNG::SetCaretColor(FrameNode* frameNode, const Color& color)
{
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCaretColor(color);
}

void RichEditorModelNG::SetOnEditingChange(std::function<void(const bool&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnEditingChange(std::move(func));
}

void RichEditorModelNG::SetOnEditingChange(FrameNode* frameNode, std::function<void(const bool&)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnEditingChange(std::move(callback));
}

void RichEditorModelNG ::SetEnterKeyType(TextInputAction action)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "SetEnterKeyType=%{public}d", action);
    auto pattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    if (action == TextInputAction::UNSPECIFIED) {
        action = TextInputAction::NEW_LINE;
    }
    pattern->UpdateTextInputAction(action);
}

void RichEditorModelNG::SetEnterKeyType(FrameNode* frameNode, const TextInputAction& action)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "SetEnterKeyType=%{public}d", action);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateTextInputAction(action);
}

void RichEditorModelNG::SetOnSubmit(std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSubmit(std::move(func));
}

void RichEditorModelNG::SetOnSubmit(FrameNode* frameNode,
    std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& callback)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnSubmit(std::move(callback));
}

void RichEditorModelNG::SetOnWillChange(std::function<bool(const RichEditorChangeValue&)>&& func)
{
    CHECK_NULL_VOID(!isStyledStringMode_);
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillChange(std::move(func));
}


void RichEditorModelNG::SetOnWillChange(FrameNode* frameNode, std::function<bool(const RichEditorChangeValue&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillChange(std::move(func));
}

void RichEditorModelNG::SetOnDidChange(std::function<void(const RichEditorChangeValue&)>&& func)
{
    CHECK_NULL_VOID(!isStyledStringMode_);
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidChange(std::move(func));
}

void RichEditorModelNG::SetOnDidChange(FrameNode* frameNode, std::function<void(const RichEditorChangeValue&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidChange(std::move(func));
}

void RichEditorModelNG::SetOnCut(std::function<void(NG::TextCommonEvent&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCut(std::move(func));
}

void RichEditorModelNG::SetOnCut(FrameNode* frameNode, std::function<void(NG::TextCommonEvent&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCut(std::move(func));
}

void RichEditorModelNG::SetOnCopy(std::function<void(NG::TextCommonEvent&)>&& func)
{
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCopy(std::move(func));
}

void RichEditorModelNG::SetOnCopy(FrameNode* frameNode, std::function<void(NG::TextCommonEvent&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCopy(std::move(func));
}

void RichEditorModelNG::SetSelectionMenuOptions(
    const OnCreateMenuCallback&& onCreateMenuCallback, const OnMenuItemClickCallback&& onMenuItemClick)
{
    auto richEditorPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<RichEditorPattern>();
    CHECK_NULL_VOID(richEditorPattern);
    richEditorPattern->OnSelectionMenuOptionsUpdate(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

void RichEditorModelNG::SetRequestKeyboardOnFocus(bool needToRequest)
{
    auto richEditorPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<RichEditorPattern>();
    CHECK_NULL_VOID(richEditorPattern);
    richEditorPattern->SetRequestKeyboardOnFocus(needToRequest);
}

void RichEditorModelNG::SetRequestKeyboardOnFocus(FrameNode* frameNode, bool needToRequest)
{
    CHECK_NULL_VOID(frameNode);
    auto richEditorPattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(richEditorPattern);
    richEditorPattern->SetRequestKeyboardOnFocus(needToRequest);
}

void RichEditorModelNG::SetEnableHapticFeedback(bool isEnabled)
{
    auto richEditorPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<RichEditorPattern>();
    CHECK_NULL_VOID(richEditorPattern);
    richEditorPattern->SetEnableHapticFeedback(isEnabled);
}
void RichEditorModelNG::SetSupportPreviewText(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSupportPreviewText(value);
}

void RichEditorModelNG::SetSelectionMenuOptions(FrameNode* frameNode, const OnCreateMenuCallback&& onCreateMenuCallback,
    const OnMenuItemClickCallback&& onMenuItemClick)
{
    CHECK_NULL_VOID(frameNode);
    auto richEditorPattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(richEditorPattern);
    richEditorPattern->OnSelectionMenuOptionsUpdate(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

void RichEditorModelNG::SetPreviewMenuParam(TextSpanType spanType, std::function<void()>& buildFunc,
    const SelectMenuParam& menuParam)
{
    auto richEditorPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<RichEditorPattern>();
    CHECK_NULL_VOID(richEditorPattern);
    richEditorPattern->SetPreviewMenuParam(spanType, buildFunc, menuParam);
}

void RichEditorModelNG::SetPreviewMenuParam(FrameNode* frameNode, TextSpanType spanType,
    std::function<void()>& buildFunc, const SelectMenuParam& menuParam)
{
    CHECK_NULL_VOID(frameNode);
    auto richEditorPattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(richEditorPattern);
    richEditorPattern->SetPreviewMenuParam(spanType, buildFunc, menuParam);
}

void RichEditorModelNG::SetBarState(DisplayMode mode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RichEditorLayoutProperty, DisplayMode, mode);
}

void RichEditorModelNG::SetBarState(FrameNode* frameNode, DisplayMode mode)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(RichEditorLayoutProperty, DisplayMode, mode, frameNode);
}

void RichEditorModelNG::SetMaxLength(std::optional<int32_t> value)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMaxLength(value);
}

void RichEditorModelNG::ResetMaxLength()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMaxLength(INT_MAX);
}

void RichEditorModelNG::SetMaxLines(uint32_t value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(RichEditorLayoutProperty, MaxLines, value);
}

void RichEditorModelNG::SetMaxLength(FrameNode* frameNode, std::optional<int32_t> value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<RichEditorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMaxLength(value);
}

void RichEditorModelNG::SetMaxLines(FrameNode* frameNode, uint32_t value)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(RichEditorLayoutProperty, MaxLines, value, frameNode);
}
} // namespace OHOS::Ace::NG
