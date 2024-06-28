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

namespace NodeModifier {
const ArkUIRichEditorModifier* GetRichEditorModifier()
{
    static const ArkUIRichEditorModifier modifier = { SetRichEditorDetectEnable, ResetRichEditorDetectEnable,
        SetRichEditorCopyOptions, ResetRichEditorCopyOptions, SetRichEditorCaretColor, ResetRichEditorCaretColor,
        SetRichEditorOnReady, ResetRichEditorOnReady, SetRichEditorOnDeleteComplete, ResetRichEditorOnDeleteComplete,
        SetRichEditorOnEditingChange, ResetRichEditorOnEditingChange,
        SetRichEditorSelectedBackgroundColor, ResetRichEditorSelectedBackgroundColor, SetRichEditorEnterKeyType,
        ResetRichEditorEnterKeyType };
    return &modifier;
}
}
}