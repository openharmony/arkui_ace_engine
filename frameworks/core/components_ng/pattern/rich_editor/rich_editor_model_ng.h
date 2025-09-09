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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_NG_H

#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT RichEditorModelNG : public OHOS::Ace::RichEditorModel {
public:
    void Create(bool isStyledStringMode = false) override;
    RefPtr<RichEditorBaseControllerBase> GetRichEditorController() override;
    void SetOnReady(std::function<void()>&& func) override;
    void SetOnSelect(std::function<void(const BaseEventInfo*)>&& func) override;
    void SetOnSelectionChange(std::function<void(const BaseEventInfo*)>&& func) override;
    void SetAboutToIMEInput(std::function<bool(const RichEditorInsertValue&)>&& func) override;
    void SetOnIMEInputComplete(std::function<void(const RichEditorAbstractSpanResult&)>&& func) override;
    void SetOnDidIMEInput(std::function<void(const TextRange&)>&& func) override;
    void SetAboutToDelete(std::function<bool(const RichEditorDeleteValue&)>&& func) override;
    void SetOnDeleteComplete(std::function<void()>&& func) override;
    void SetCustomKeyboard(std::function<void()>&& func, bool supportAvoidance) override;
    void SetCopyOption(CopyOptions& copyOptions) override;
    void BindSelectionMenu(TextSpanType& editorType, TextResponseType& responseType,
        std::function<void()>& buildFunc, SelectMenuParam& menuParam) override;
    void SetOnPaste(std::function<void(NG::TextCommonEvent&)>&& func) override;
    void SetPlaceholder(PlaceholderOptions& options) override;
    void SetTextDetectEnable(bool value) override;
    void SetSupportPreviewText(bool value) override;
    void SetTextDetectConfig(const TextDetectConfig& textDetectConfig) override;
    void SetSelectedBackgroundColor(const Color& selectedColor) override;
    void SetCaretColor(const Color& color) override;
    void SetOnEditingChange(std::function<void(const bool&)>&& func) override;
    void SetOnWillChange(std::function<bool(const RichEditorChangeValue&)>&& func) override;
    void SetOnDidChange(std::function<void(const RichEditorChangeValue&)>&& func) override;
    void SetOnCut(std::function<void(NG::TextCommonEvent&)>&& func) override;
    void SetOnCopy(std::function<void(NG::TextCommonEvent&)>&& func) override;
    void SetOnShare(std::function<void(NG::TextCommonEvent&)>&& func) override;
    void SetSelectionMenuOptions(const OnCreateMenuCallback&& onCreateMenuCallback,
        const OnMenuItemClickCallback&& onMenuItemClick,
        const OnPrepareMenuCallback&& onPrepareMenuCallback) override;
    void SetRequestKeyboardOnFocus(bool needToRequest) override;
    void SetEnableHapticFeedback(bool isEnabled) override;
    void SetPreviewMenuParam(TextSpanType spanType, std::function<void()>& buildFunc,
        const SelectMenuParam& menuParam) override;
    void SetBarState(DisplayMode mode) override;
    void SetMaxLength(std::optional<int32_t> value) override;
    void ResetMaxLength() override;
    void SetMaxLines(uint32_t value) override;
    void SetEnableAutoSpacing(bool enabled) override;
    void SetStopBackPress(bool isStopBackPress) override;
    void SetKeyboardAppearance(KeyboardAppearance value) override;
    void SetSupportStyledUndo(bool enabled) override;
    void SetScrollBarColor(std::optional<Color> value) override;

    static void SetTextDetectEnable(FrameNode* frameNode, bool value);
    static void SetTextDetectConfig(FrameNode* frameNode, const TextDetectConfig& textDetectConfig);
    static void SetOnIMEInputComplete(FrameNode* frameNode,
        std::function<void(const RichEditorAbstractSpanResult&)>&& callback);
    static void SetOnWillChange(FrameNode* frameNode, std::function<bool(const RichEditorChangeValue&)>&& func);
    static void SetOnDidChange(FrameNode* frameNode, std::function<void(const RichEditorChangeValue&)>&& func);
    static void SetPlaceholder(FrameNode* frameNode, PlaceholderOptions& options);
    static void SetAboutToDelete(FrameNode* frameNode, std::function<bool(const RichEditorDeleteValue&)>&& func);
    static void SetOnDidIMEInput(FrameNode* frameNode, std::function<void(const TextRange&)>&& callback);
    static void SetCopyOption(FrameNode* frameNode, CopyOptions& copyOptions);
    static void SetOnSelectionChange(FrameNode* frameNode, std::function<void(const BaseEventInfo*)>&& callback);
    static void SetCaretColor(FrameNode* frameNode, const Color& color);
    static void SetOnSelect(FrameNode* frameNode, std::function<void(const BaseEventInfo*)>&& callback);
    static void SetOnReady(FrameNode* frameNode, std::function<void()>&& callback);
    static void SetOnDeleteComplete(FrameNode* frameNode, std::function<void()>&& callback);
    static void SetOnEditingChange(FrameNode* frameNode, std::function<void(const bool&)>&& callback);
    static void SetSelectedBackgroundColor(FrameNode* frameNode, const Color& selectedColor);
    static void SetOnPaste(FrameNode* frameNode, std::function<void(NG::TextCommonEvent&)>&& func);
    static void SetOnCut(FrameNode* frameNode, std::function<void(NG::TextCommonEvent&)>&& func);
    static void SetOnCopy(FrameNode* frameNode, std::function<void(NG::TextCommonEvent&)>&& func);
    void SetEnterKeyType(TextInputAction value) override;
    static void SetEnterKeyType(FrameNode* frameNode, const TextInputAction& action);
    void SetOnSubmit(std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& func) override;
    static void SetOnSubmit(FrameNode* frameNode, std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& callback);
    static void SetAboutToIMEInput(FrameNode* frameNode, std::function<bool(const RichEditorInsertValue&)>&& callback);
    static void SetRequestKeyboardOnFocus(FrameNode* frameNode, bool needToRequest);
    static void SetSupportPreviewText(FrameNode* frameNode, bool value);
    static void SetSelectionMenuOptions(FrameNode* frameNode,
        const OnCreateMenuCallback&& onCreateMenuCallback, const OnMenuItemClickCallback&& onMenuItemClick,
        const OnPrepareMenuCallback&& onPrepareMenuCallback);
    static void SetPreviewMenuParam(FrameNode* frameNode,
        TextSpanType spanType, std::function<void()>& buildFunc, const SelectMenuParam& menuParam);
    static void SetBarState(FrameNode* frameNode, DisplayMode mode);
    static void SetMaxLength(FrameNode* frameNode, std::optional<int32_t> value);
    static void SetMaxLines(FrameNode* frameNode, uint32_t value);
    static void SetEnableAutoSpacing(FrameNode* frameNode, bool enabled);
    static void SetStopBackPress(FrameNode* frameNode, bool isStopBackPress);
    static void SetKeyboardAppearance(FrameNode* frameNode, KeyboardAppearance value);
    static void SetEnableHapticFeedback(FrameNode* frameNode, bool isEnabled);
    static void SetSupportStyledUndo(FrameNode* frameNode, bool enabled);
    static void SetScrollBarColor(FrameNode* frameNode, std::optional<Color> value);

private:
    void SetDraggable(bool draggable);
    bool isStyledStringMode_ = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_NG_H
