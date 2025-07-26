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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_STATIC_H

#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT RichEditorModelStatic : public OHOS::Ace::RichEditorModel {
public:
    static RefPtr<NG::FrameNode> CreateFrameNode(int32_t nodeId);
    static RefPtr<RichEditorBaseControllerBase> GetRichEditorController(FrameNode* frameNode);
    static RefPtr<RichEditorBaseControllerBase> GetRichEditorStyledStringController(FrameNode* frameNode);
    static void SetStyledStringMode(FrameNode* frameNode, bool isStyledStringMode);
    static void SetOnCut(FrameNode* frameNode, std::function<void(NG::TextCommonEvent&)>&& func);
    static void SetOnCopy(FrameNode* frameNode, std::function<void(NG::TextCommonEvent&)>&& func);
    static void SetOnPaste(FrameNode* frameNode, std::function<void(NG::TextCommonEvent&)>&& func);
    static void SetEnterKeyType(FrameNode* frameNode, const std::optional<TextInputAction>& action);
    static void SetSelectedBackgroundColor(FrameNode* frameNode, const std::optional<Color>& selectedColor);
    static void SetCaretColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetAboutToDelete(FrameNode* frameNode, std::function<bool(const RichEditorDeleteValue&)>&& func);
    static void SetEnableHapticFeedback(FrameNode* frameNode, bool isEnabled);
    static void SetCustomKeyboard(FrameNode* frameNode, std::function<void()>&& func,
        const std::optional<bool>& supportAvoidance);
    static void BindSelectionMenu(FrameNode* frameNode, TextSpanType& editorType, TextResponseType& type,
        std::function<void()>& buildFunc, SelectMenuParam& menuParam);
    void SetDraggable(bool draggable);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_STATIC_H
