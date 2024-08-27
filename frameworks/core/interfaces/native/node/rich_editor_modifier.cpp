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
#include "core/interfaces/native/node/rich_editor_modifier.h"

#include "core/pipeline/base/element_register.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"

namespace OHOS::Ace::NG {
constexpr bool DEFAULT_ENABLE_TEXT_DETECTOR = false;

void SetRichEditorDetectEnable(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetTextDetectEnable(frameNode, static_cast<bool>(value));
}

void ResetRichEditorDetectEnable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetTextDetectEnable(frameNode, DEFAULT_ENABLE_TEXT_DETECTOR);
}

void SetRichEditorDataDetectorConfigWithEvent(
    ArkUINodeHandle node, const struct ArkUITextDetectConfigStruct* arkUITextDetectConfig)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextDetectConfig textDetectConfig;
    textDetectConfig.types = arkUITextDetectConfig->types;
    if (arkUITextDetectConfig->onResult) {
        textDetectConfig.onResult =
            std::move(*(reinterpret_cast<std::function<void(const std::string&)>*>(arkUITextDetectConfig->onResult)));
    }
    textDetectConfig.entityColor = Color(arkUITextDetectConfig->entityColor);
    textDetectConfig.entityDecorationType = TextDecoration(arkUITextDetectConfig->entityDecorationType);
    textDetectConfig.entityDecorationColor = Color(arkUITextDetectConfig->entityDecorationColor);
    textDetectConfig.entityDecorationStyle = TextDecorationStyle(arkUITextDetectConfig->entityDecorationStyle);
    RichEditorModelNG::SetTextDetectConfig(frameNode, textDetectConfig);
}

void ResetRichEditorDataDetectorConfigWithEvent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextDetectConfig textDetectConfig;
    RichEditorModelNG::SetTextDetectConfig(frameNode, textDetectConfig);
}

void SetRichEditorOnIMEInputComplete(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onIMEInputComplete = reinterpret_cast<std::function<void(RichEditorAbstractSpanResult)>*>(callback);
        RichEditorModelNG::SetOnIMEInputComplete(frameNode, std::move(*onIMEInputComplete));
    } else {
        RichEditorModelNG::SetOnIMEInputComplete(frameNode, nullptr);
    }
}

void ResetRichEditorOnIMEInputComplete(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnIMEInputComplete(frameNode, nullptr);
}

void SetRichEditorCopyOptions(ArkUINodeHandle node, ArkUI_Int32 copyOptionsValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CopyOptions copyOptions = static_cast<CopyOptions>(copyOptionsValue);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetCopyOption(frameNode, copyOptions);
}

void ResetRichEditorCopyOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CopyOptions defaultCopyOptions = CopyOptions::Distributed;
    RichEditorModelNG::SetCopyOption(frameNode, defaultCopyOptions);
}

void SetRichEditorOnSelectionChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onSelectionChange = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        RichEditorModelNG::SetOnSelectionChange(frameNode, std::move(*onSelectionChange));
    } else {
        RichEditorModelNG::SetOnSelectionChange(frameNode, nullptr);
    }
}

void ResetRichEditorOnSelectionChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnSelectionChange(frameNode, nullptr);
}

void SetRichEditorCaretColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetCaretColor(frameNode, Color(color));
}

void ResetRichEditorCaretColor(ArkUINodeHandle node)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto richEditorTheme = pipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(richEditorTheme);
    auto caretColor = richEditorTheme->GetCaretColor();
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetCaretColor(frameNode, caretColor);
}

void SetRichEditorOnSelect(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onSelect = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        RichEditorModelNG::SetOnSelect(frameNode, std::move(*onSelect));
    } else {
        RichEditorModelNG::SetOnSelect(frameNode, nullptr);
    }
}

void ResetRichEditorOnSelect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnSelect(frameNode, nullptr);
}

void SetRichEditorOnSubmit(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onSubmit = reinterpret_cast<std::function<void(int32_t, NG::TextFieldCommonEvent&)>*>(callback);
        RichEditorModelNG::SetOnSubmit(frameNode, std::move(*onSubmit));
    } else {
        RichEditorModelNG::SetOnSubmit(frameNode, nullptr);
    }
}

void ResetRichEditorOnSubmit(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnSubmit(frameNode, nullptr);
}

void SetRichEditorAboutToIMEInput(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto aboutToIMEInput = reinterpret_cast<std::function<bool(const RichEditorInsertValue&)>*>(callback);
        RichEditorModelNG::SetAboutToIMEInput(frameNode, std::move(*aboutToIMEInput));
    } else {
        RichEditorModelNG::SetAboutToIMEInput(frameNode, nullptr);
    }
}

void ResetRichEditorAboutToIMEInput(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetAboutToIMEInput(frameNode, nullptr);
}

void SetRichEditorOnReady(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onReady = reinterpret_cast<std::function<void(void)>*>(callback);
        RichEditorModelNG::SetOnReady(frameNode, std::move(*onReady));
    } else {
        RichEditorModelNG::SetOnReady(frameNode, nullptr);
    }
}

void ResetRichEditorOnReady(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnReady(frameNode, nullptr);
}

void SetRichEditorOnDeleteComplete(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onDeleteComplete = reinterpret_cast<std::function<void(void)>*>(callback);
        RichEditorModelNG::SetOnDeleteComplete(frameNode, std::move(*onDeleteComplete));
    } else {
        RichEditorModelNG::SetOnDeleteComplete(frameNode, nullptr);
    }
}

void ResetRichEditorOnDeleteComplete(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnDeleteComplete(frameNode, nullptr);
}

void SetRichEditorOnEditingChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEditingChange = reinterpret_cast<std::function<void(bool)>*>(callback);
        RichEditorModelNG::SetOnEditingChange(frameNode, std::move(*onEditingChange));
    } else {
        RichEditorModelNG::SetOnEditingChange(frameNode, nullptr);
    }
}

void ResetRichEditorOnEditingChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnEditingChange(frameNode, nullptr);
}

void SetRichEditorSelectedBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetSelectedBackgroundColor(frameNode, Color(color));
}

void ResetRichEditorSelectedBackgroundColor(ArkUINodeHandle node)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto richEditorTheme = pipeline->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(richEditorTheme);
    auto selectedBackgroundColor = richEditorTheme->GetSelectedBackgroundColor();
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetSelectedBackgroundColor(frameNode, selectedBackgroundColor);
}

void SetRichEditorOnPaste(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onPaste = reinterpret_cast<std::function<void(NG::TextCommonEvent&)>*>(callback);
        RichEditorModelNG::SetOnPaste(frameNode, std::move(*onPaste));
    } else {
        RichEditorModelNG::SetOnPaste(frameNode, nullptr);
    }
}

void ResetRichEditorOnPaste(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnPaste(frameNode, nullptr);
}

void SetRichEditorOnCut(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onCut = reinterpret_cast<std::function<void(NG::TextCommonEvent&)>*>(callback);
        RichEditorModelNG::SetOnCut(frameNode, std::move(*onCut));
    } else {
        RichEditorModelNG::SetOnCut(frameNode, nullptr);
    }
}

void ResetRichEditorOnCut(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnCut(frameNode, nullptr);
}

void SetRichEditorOnCopy(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onCopy = reinterpret_cast<std::function<void(NG::TextCommonEvent&)>*>(callback);
        RichEditorModelNG::SetOnCopy(frameNode, std::move(*onCopy));
    } else {
        RichEditorModelNG::SetOnCopy(frameNode, nullptr);
    }
}

void ResetRichEditorOnCopy(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetOnCopy(frameNode, nullptr);
}

void SetRichEditorEnterKeyType(ArkUINodeHandle node, ArkUI_Uint32 enterKeyType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetEnterKeyType(frameNode, TextInputAction(enterKeyType));
}

void ResetRichEditorEnterKeyType(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto defaultEnterKeyType = TextInputAction::NEW_LINE;
    RichEditorModelNG::SetEnterKeyType(frameNode, defaultEnterKeyType);
}

void SetRichEditorEnableKeyboardOnFocus(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetRequestKeyboardOnFocus(frameNode, value);
}

void ResetRichEditorEnableKeyboardOnFocus(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetRequestKeyboardOnFocus(frameNode, true);
}

void SetRichEditorEnablePreviewText(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetSupportPreviewText(frameNode, value);
}

void ResetRichEditorEnablePreviewText(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RichEditorModelNG::SetSupportPreviewText(frameNode, true);
}


void SetRichEditorEditMenuOptions(ArkUINodeHandle node, void* onCreateMenuCallback, void* onMenuItemClickCallback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::OnCreateMenuCallback* onCreateMenu = nullptr;
    NG::OnMenuItemClickCallback* onMenuItemClick = nullptr;
    if (onCreateMenuCallback) {
        onCreateMenu = reinterpret_cast<NG::OnCreateMenuCallback*>(onCreateMenuCallback);
    }
    if (onMenuItemClickCallback) {
        onMenuItemClick = reinterpret_cast<NG::OnMenuItemClickCallback*>(onMenuItemClickCallback);
    }
    RichEditorModelNG::SetSelectionMenuOptions(frameNode, std::move(*onCreateMenu), std::move(*onMenuItemClick));
}

void ResetRichEditorEditMenuOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClick;
    RichEditorModelNG::SetSelectionMenuOptions(frameNode, std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

namespace NodeModifier {
const ArkUIRichEditorModifier* GetRichEditorModifier()
{
    static const ArkUIRichEditorModifier modifier = { SetRichEditorDetectEnable, ResetRichEditorDetectEnable,
        SetRichEditorDataDetectorConfigWithEvent, ResetRichEditorDataDetectorConfigWithEvent,
        SetRichEditorOnIMEInputComplete, ResetRichEditorOnIMEInputComplete,
        SetRichEditorCopyOptions, ResetRichEditorCopyOptions, SetRichEditorOnSelectionChange,
        ResetRichEditorOnSelectionChange, SetRichEditorCaretColor, ResetRichEditorCaretColor,
        SetRichEditorOnSelect, ResetRichEditorOnSelect,
        SetRichEditorOnSubmit, ResetRichEditorOnSubmit, SetRichEditorAboutToIMEInput, ResetRichEditorAboutToIMEInput,
        SetRichEditorOnReady, ResetRichEditorOnReady, SetRichEditorOnDeleteComplete, ResetRichEditorOnDeleteComplete,
        SetRichEditorOnEditingChange, ResetRichEditorOnEditingChange,
        SetRichEditorSelectedBackgroundColor, ResetRichEditorSelectedBackgroundColor, SetRichEditorOnPaste,
        ResetRichEditorOnPaste, SetRichEditorOnCut, ResetRichEditorOnCut, SetRichEditorOnCopy, ResetRichEditorOnCopy,
        SetRichEditorEnterKeyType, ResetRichEditorEnterKeyType,
        SetRichEditorEnableKeyboardOnFocus, ResetRichEditorEnableKeyboardOnFocus,
        SetRichEditorEnablePreviewText, ResetRichEditorEnablePreviewText,
        SetRichEditorEditMenuOptions, ResetRichEditorEditMenuOptions };
    return &modifier;
}

const CJUIRichEditorModifier* GetCJUIRichEditorModifier()
{
    static const CJUIRichEditorModifier modifier = { SetRichEditorDetectEnable, ResetRichEditorDetectEnable,
        SetRichEditorCopyOptions, ResetRichEditorCopyOptions, SetRichEditorCaretColor, ResetRichEditorCaretColor,
        SetRichEditorOnReady, ResetRichEditorOnReady, SetRichEditorOnDeleteComplete, ResetRichEditorOnDeleteComplete,
        SetRichEditorOnEditingChange, ResetRichEditorOnEditingChange,
        SetRichEditorSelectedBackgroundColor, ResetRichEditorSelectedBackgroundColor, SetRichEditorEnterKeyType,
        ResetRichEditorEnterKeyType };
    return &modifier;
}
}
}