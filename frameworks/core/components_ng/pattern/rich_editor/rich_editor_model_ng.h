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
    void SetCustomKeyboardWithNode(FrameNode* customKeyboard, bool supportAvoidance = false) override;
    void SetCopyOption(CopyOptions& copyOptions) override;
    void BindSelectionMenu(TextSpanType& editorType, TextResponseType& responseType,
        std::function<void()>& buildFunc, SelectMenuParam& menuParam) override;
    void SetOnPaste(std::function<void(NG::TextCommonEvent&)>&& func) override;
    void SetPlaceholder(PlaceholderOptions& options) override;
    void SetSelectDetectEnable(const bool value) override;
    void ResetSelectDetectEnable() override;
    void SetSelectDetectConfig(std::vector<TextDataDetectType>& types) override;
    void ResetSelectDetectConfig() override;
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
    void SetOnWillAttachIME(IMEAttachCallback&& func) override;
    void SetSelectionMenuOptions(const OnCreateMenuCallback&& onCreateMenuCallback,
        const OnMenuItemClickCallback&& onMenuItemClick,
        const OnPrepareMenuCallback&& onPrepareMenuCallback) override;
    void SetRequestKeyboardOnFocus(bool needToRequest) override;
    void SetEnableHapticFeedback(bool isEnabled) override;
    void SetBarState(DisplayMode mode) override;
    void SetPreviewMenuParam(TextSpanType spanType, std::function<void()>& buildFunc,
        const SelectMenuParam& menuParam) override;
    void SetMaxLength(std::optional<int32_t> value) override;
    void ResetMaxLength() override;
    void SetMaxLines(uint32_t value) override;
    void SetEnableAutoSpacing(bool enabled) override;
    void SetIncludeFontPadding(bool enabled) override;
    void SetFallbackLineSpacing(bool enabled) override;
    void SetCompressLeadingPunctuation(bool enabled) override;
    void SetStopBackPress(bool isStopBackPress) override;
    void SetKeyboardAppearance(KeyboardAppearance value) override;
    void SetSupportStyledUndo(bool enabled) override;
    void SetScrollBarColor(std::optional<Color> value) override;
    void SetSelectedDragPreviewStyle(const Color& value) override;
    void ResetSelectedDragPreviewStyle() override;
    void SetSingleLine(bool enabled) override;
    void ResetSingleLine() override;

    static void SetCaretOffset(FrameNode* frameNode, int32_t caretPosition);
    static int32_t GetCaretOffset(FrameNode* frameNode);
    static void SetSelection(FrameNode* frameNode, int32_t selectionStart, int32_t selectionEnd,
        const std::optional<SelectionOptions>& options);
    static void StopEditing(FrameNode* frameNode);
    static bool IsEditing(FrameNode* frameNode);
    static RectF GetCaretRect(FrameNode* frameNode);
    static void DeleteBackward(FrameNode* frameNode);
    static PreviewTextInfo GetPreviewTextInfo(FrameNode* frameNode);
    static RefPtr<FrameNode> CreateRichEditorStyledStringNode(int32_t nodeId);
    static void SetSelectDetectEnable(FrameNode* frameNode, const bool value);
    static bool GetSelectDetectEnable(FrameNode* frameNode);
    static void ResetSelectDetectEnable(FrameNode* frameNode);
    static void SetSelectDetectConfig(FrameNode* frameNode, std::vector<TextDataDetectType>& types);
    static std::vector<TextDataDetectType> GetSelectDetectConfig(FrameNode* frameNode);
    static void ResetSelectDetectConfig(FrameNode* frameNode);
    static void SetTextDetectEnable(FrameNode* frameNode, bool value);
    static bool GetTextDetectEnable(FrameNode* frameNode);
    static void SetTextDetectConfig(FrameNode* frameNode, const TextDetectConfig& textDetectConfig);
    static void SetOnIMEInputComplete(FrameNode* frameNode,
        std::function<void(const RichEditorAbstractSpanResult&)>&& callback);
    static void SetOnWillChange(FrameNode* frameNode, std::function<bool(const RichEditorChangeValue&)>&& func);
    static void SetOnDidChange(FrameNode* frameNode, std::function<void(const RichEditorChangeValue&)>&& func);
    static void SetPlaceholder(FrameNode* frameNode, PlaceholderOptions& options);
    static void SetAboutToDelete(FrameNode* frameNode, std::function<bool(const RichEditorDeleteValue&)>&& func);
    static void SetOnDidIMEInput(FrameNode* frameNode, std::function<void(const TextRange&)>&& callback);
    static void SetCopyOption(FrameNode* frameNode, CopyOptions& copyOptions);
    static CopyOptions GetCopyOption(FrameNode* frameNode);
    static void SetOnSelectionChange(FrameNode* frameNode, std::function<void(const BaseEventInfo*)>&& callback);
    static void SetCaretColor(FrameNode* frameNode, const Color& color);
    static Color GetCaretColor(FrameNode* frameNode);
    static void SetOnSelect(FrameNode* frameNode, std::function<void(const BaseEventInfo*)>&& callback);
    static void SetOnReady(FrameNode* frameNode, std::function<void()>&& callback);
    static void SetOnDeleteComplete(FrameNode* frameNode, std::function<void()>&& callback);
    static void SetCustomKeyboard(
        FrameNode* frameNode, const std::function<void()>&& buildFunc, bool supportAvoidance = false);
    static void SetCustomKeyboardWithNode(
        FrameNode* frameNode, FrameNode* customKeyboard, bool supportAvoidance = false);
    static RefPtr<UINode> GetCustomKeyboardNode(FrameNode* frameNode);
    static bool GetCustomKeyboardOption(FrameNode* frameNode);
    static void SetOnEditingChange(FrameNode* frameNode, std::function<void(const bool&)>&& callback);
    static void SetSelectedBackgroundColor(FrameNode* frameNode, const Color& selectedColor);
    static Color GetSelectedBackgroundColor(FrameNode* frameNode);
    static void SetOnPaste(FrameNode* frameNode, std::function<void(NG::TextCommonEvent&)>&& func);
    static void SetOnCut(FrameNode* frameNode, std::function<void(NG::TextCommonEvent&)>&& func);
    static void SetOnCopy(FrameNode* frameNode, std::function<void(NG::TextCommonEvent&)>&& func);
    static void SetOnWillAttachIME(FrameNode* frameNode, IMEAttachCallback&& func);
    void SetEnterKeyType(TextInputAction value) override;
    static void SetEnterKeyType(FrameNode* frameNode, const TextInputAction& action);
    static TextInputAction GetEnterKeyType(FrameNode* frameNode);
    void SetOnSubmit(std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& func) override;
    static void SetOnSubmit(FrameNode* frameNode, std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& callback);
    static size_t GetLineCount(FrameNode* frameNode);
    static TextLineMetrics GetLineMetrics(FrameNode* frameNode, int32_t lineNumber);
    static std::vector<ParagraphManager::TextBox> GetRectsForRange(FrameNode* frameNode, int32_t start, int32_t end,
        RectHeightStyle heightStyle, RectWidthStyle widthStyle);
    static PositionWithAffinity GetGlyphPositionAtCoordinate(FrameNode* frameNode, int32_t x, int32_t y);
    static void SetTypingParagraphStyle(FrameNode* frameNode,
        std::optional<struct UpdateParagraphStyle> typingParagraphStyle);
    static void SetTypingStyle(FrameNode* frameNode, std::optional<struct UpdateSpanStyle> typingStyle,
            std::optional<TextStyle> textStyle);
    static std::optional<struct UpdateSpanStyle> GetTypingStyle(FrameNode* frameNode);
    static void SetAboutToIMEInput(FrameNode* frameNode, std::function<bool(const RichEditorInsertValue&)>&& callback);
    static void SetRequestKeyboardOnFocus(FrameNode* frameNode, bool needToRequest);
    static bool GetRequestKeyboardOnFocus(FrameNode* frameNode);
    static void SetSupportPreviewText(FrameNode* frameNode, bool value);
    static bool IsSupportPreviewText(FrameNode* frameNode);
    static void SetSelectionMenuOptions(FrameNode* frameNode,
        const OnCreateMenuCallback&& onCreateMenuCallback, const OnMenuItemClickCallback&& onMenuItemClick,
        const OnPrepareMenuCallback&& onPrepareMenuCallback);
    static void SetBarState(FrameNode* frameNode, DisplayMode mode);
    static OHOS::Ace::DisplayMode GetBarState(FrameNode* frameNode);
    static void SetPreviewMenuParam(FrameNode* frameNode,
        TextSpanType spanType, std::function<void()>& buildFunc, const SelectMenuParam& menuParam);
    static void SetMaxLength(FrameNode* frameNode, std::optional<int32_t> value);
    static int32_t GetMaxLength(FrameNode* frameNode);
    static void SetMaxLines(FrameNode* frameNode, uint32_t value);
    static int32_t GetMaxLines(FrameNode* frameNode);
    static void SetEnableAutoSpacing(FrameNode* frameNode, bool enabled);
    static bool IsEnableAutoSpacing(FrameNode* frameNode);
    static void SetIncludeFontPadding(FrameNode* frameNode, bool enabled);
    static bool IsIncludeFontPadding(FrameNode* frameNode);
    static void SetFallbackLineSpacing(FrameNode* frameNode, bool enabled);
    static bool IsFallbackLineSpacing(FrameNode* frameNode);
    static void SetCompressLeadingPunctuation(FrameNode* frameNode, bool enabled);
    static bool IsCompressLeadingPunctuation(FrameNode* frameNode);
    static void SetStopBackPress(FrameNode* frameNode, bool isStopBackPress);
    static bool IsStopBackPress(FrameNode* frameNode);
    static void SetKeyboardAppearance(FrameNode* frameNode, KeyboardAppearance value);
    static KeyboardAppearance GetKeyboardAppearance(FrameNode* frameNode);
    static void SetEnableHapticFeedback(FrameNode* frameNode, bool isEnabled);
    static bool GetEnableHapticFeedback(FrameNode* frameNode);
    static void SetSupportStyledUndo(FrameNode* frameNode, bool enabled);
    static bool IsSupportStyledUndo(FrameNode* frameNode);
    static void SetScrollBarColor(FrameNode* frameNode, std::optional<Color> value);
    static Color GetSelectedDragPreviewStyle(FrameNode* frameNode);
    static void SetSelectedDragPreviewStyle(FrameNode* frameNode, const Color& value);
    static void ResetSelectedDragPreviewStyle(FrameNode* frameNode);
    static void SetSingleLine(FrameNode* frameNode, bool enabled);
    static void ResetSingleLine(FrameNode* frameNode);
    static bool GetSingleLine(FrameNode* frameNode);
    static Color GetScrollBarColor(FrameNode* frameNode);
    static void BindSelectionMenu(FrameNode* frameNode, TextSpanType& spanType,
        TextResponseType& responseType, std::function<void()>& buildFunc, const SelectMenuParam& menuParam);
    static void ResetBindSelectionMenu(FrameNode* frameNode);

private:
    void SetDraggable(bool draggable);
    static void InitRichEditorModel(bool isStyledStringMode, const RefPtr<FrameNode>& frameNode);
    bool isStyledStringMode_ = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_NG_H
