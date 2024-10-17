/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MODEL_NG_H

#include "core/components_ng/pattern/text_field/text_content_type.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TextFieldModelNG : public TextFieldModel {
public:
    TextFieldModelNG() = default;
    ~TextFieldModelNG() override = default;
    void CreateNode(
        const std::optional<std::string>& placeholder, const std::optional<std::string>& value, bool isTextArea);
    RefPtr<TextFieldControllerBase> CreateTextInput(
        const std::optional<std::string>& placeholder, const std::optional<std::string>& value) override;

    RefPtr<TextFieldControllerBase> CreateTextArea(
        const std::optional<std::string>& placeholder, const std::optional<std::string>& value) override;

    void RequestKeyboardOnFocus(bool needToRequest) override;
    void SetWidthAuto(bool isAuto) override;
    void SetType(TextInputType value) override;
    void SetContentType(const TextContentType& value) override;
    void SetPlaceholderColor(const Color& value) override;
    void SetPlaceholderFont(const Font& value) override;
    void SetEnterKeyType(TextInputAction value) override;
    void SetTextAlign(TextAlign value) override;
    void SetLineBreakStrategy(LineBreakStrategy value) override;
    void SetCaretColor(const Color& value) override;
    void SetCaretStyle(const CaretStyle& value) override;
    void SetCaretPosition(const int32_t& value) override;
    void SetSelectedBackgroundColor(const Color& value) override;
    void SetMaxLength(uint32_t value) override;
    void SetMaxLines(uint32_t value) override;
    void SetFontSize(const Dimension& value) override;
    void SetFontWeight(FontWeight value) override;
    void SetTextColor(const Color& value) override;
    void SetWordBreak(Ace::WordBreak value) override;
    void SetFontStyle(Ace::FontStyle value) override;
    void SetFontFamily(const std::vector<std::string>& value) override;
    void SetInputFilter(const std::string& value, const std::function<void(const std::string&)>& onError) override;
    void SetInputStyle(InputStyle value) override;
    void SetShowPasswordIcon(bool value) override;
    void SetShowPasswordText(bool value) override;
    void SetOnEditChanged(std::function<void(bool)>&& func) override;
    void SetOnSubmit(std::function<void(int32_t)>&& func) override {};
    void SetOnSubmit(std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& func) override;
    void SetOnChange(std::function<void(const std::string&, PreviewText&)>&& func) override;
    void SetOnTextSelectionChange(std::function<void(int32_t, int32_t)>&& func) override;
    void SetOnSecurityStateChange(std::function<void(bool)>&& func) override;
    void SetOnContentScroll(std::function<void(float, float)>&& func) override;
    void SetOnCopy(std::function<void(const std::string&)>&& func) override;
    void SetOnCut(std::function<void(const std::string&)>&& func) override;
    void SetOnPaste(std::function<void(const std::string&)>&& func) override;
    void SetOnPasteWithEvent(std::function<void(const std::string&, NG::TextCommonEvent&)>&& func) override;
    void SetCopyOption(CopyOptions copyOption) override;
    static void ProcessDefaultStyleAndBehaviors(const RefPtr<FrameNode>& frameNode);
    void ResetMaxLength() override;
    void SetForegroundColor(const Color& value) override;
    void SetPasswordIcon(const PasswordIcon& passwordIcon) override;
    void SetShowUnit(std::function<void()>&& unitFunction) override;
    void SetShowError(const std::string& errorText, bool visible) override;
    void SetBarState(OHOS::Ace::DisplayMode value) override;
    void SetMaxViewLines(uint32_t value) override;
    void SetNormalMaxViewLines(uint32_t value) override;

    void SetShowUnderline(bool showUnderLine) override;
    void SetNormalUnderlineColor(const Color& normalColor) override;
    void SetUserUnderlineColor(UserUnderlineColor userColor) override;
    void SetShowCounter(bool value) override;
    void SetCounterType(int32_t value) override;
    void SetShowCounterBorder(bool value) override;
    void SetOnChangeEvent(std::function<void(const std::string&)>&& func) override;
    void SetBackgroundColor(const Color& color, bool tmp) override;
    void SetHeight(const Dimension& value) override;
    void SetPadding(const NG::PaddingProperty& newPadding, Edge oldPadding, bool tmp) override;
    void SetMargin() override;
    void SetHoverEffect(HoverEffectType hoverEffect) override;
    void SetSelectionMenuHidden(bool contextMenuHidden) override;
    void SetCustomKeyboard(const std::function<void()>&& buildFunc, bool supportAvoidance = false) override;
    void SetPasswordRules(const std::string& passwordRules) override;
    void SetEnableAutoFill(bool enableAutoFill) override;
    void SetCleanNodeStyle(CleanNodeStyle cleanNodeStyle) override;
    void SetCancelIconSize(const CalcDimension& iconSize) override;
    void SetCanacelIconSrc(
        const std::string& iconSrc, const std::string& bundleName, const std::string& moduleName) override;
    void SetCancelIconColor(const Color& iconColor) override;
    void SetCancelSymbolIcon(const std::function<void(WeakPtr<NG::FrameNode>)>& iconSymbol) override;
    void SetCancelButtonSymbol(bool isShowSymbol) override;
    void SetIsShowCancelButton(bool isShowCancelButton) override;
    void SetSelectAllValue(bool isSetSelectAllValue) override;
    void SetFontFeature(const FONT_FEATURES_LIST& value) override;
    void SetLetterSpacing(const Dimension& value) override;
    void SetLineHeight(const Dimension& value) override;
    void SetLineSpacing(const Dimension& value) override;
    void SetAdaptMinFontSize(const Dimension& value) override;
    void SetAdaptMaxFontSize(const Dimension& value) override;
    void SetHeightAdaptivePolicy(TextHeightAdaptivePolicy value) override;
    void SetTextDecoration(Ace::TextDecoration value) override;
    void SetTextDecorationColor(const Color& value) override;
    void SetTextDecorationStyle(Ace::TextDecorationStyle value) override;
    void SetBackBorder() override;
    void SetOnWillInsertValueEvent(std::function<bool(const InsertValueInfo&)>&& func) override;
    void SetOnDidInsertValueEvent(std::function<void(const InsertValueInfo&)>&& func) override;
    void SetOnWillDeleteEvent(std::function<bool(const DeleteValueInfo&)>&& func) override;
    void SetOnDidDeleteEvent(std::function<void(const DeleteValueInfo&)>&& func) override;
    void SetSelectionMenuOptions(const NG::OnCreateMenuCallback&& onCreateMenuCallback,
        const NG::OnMenuItemClickCallback&& onMenuItemClick) override;
    void SetEnablePreviewText(bool enablePreviewText) override;
    void SetEnableHapticFeedback(bool state) override;

    static void SetTextDecoration(FrameNode* frameNode, TextDecoration value);
    static void SetTextDecorationColor(FrameNode* frameNode, const Color& value);
    static void SetTextDecorationStyle(FrameNode* frameNode, TextDecorationStyle value);
    static void SetLetterSpacing(FrameNode* frameNode, const Dimension& value);
    static void SetLineHeight(FrameNode* frameNode, const Dimension& value);
    static void SetLineSpacing(FrameNode* frameNode, const Dimension& value);
    void SetTextOverflow(Ace::TextOverflow value) override;
    void SetTextIndent(const Dimension& value) override;
    static void SetTextOverflow(FrameNode* frameNode, Ace::TextOverflow value);
    static void SetTextIndent(FrameNode* frameNode, const Dimension& value);
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId, const std::optional<std::string>& placeholder,
        const std::optional<std::string>& value, bool isTextArea);
    static void SetAdaptMinFontSize(FrameNode* frameNode, const Dimension& value);
    static void SetAdaptMaxFontSize(FrameNode* frameNode, const Dimension& value);
    static void SetHeightAdaptivePolicy(FrameNode* frameNode, TextHeightAdaptivePolicy value);
    static void SetInputStyle(FrameNode* frameNode, InputStyle value);
    static void SetSelectionMenuHidden(FrameNode* frameNode, bool contextMenuHidden);
    static bool GetSelectionMenuHidden(FrameNode* frameNode);
    static void SetPasswordRules(FrameNode* frameNode, const std::string& passwordRules);
    static void SetEnableAutoFill(FrameNode* frameNode, bool enableAutoFill);
    static void RequestKeyboardOnFocus(FrameNode* frameNode, bool needToRequest);
    static void SetBarState(FrameNode* frameNode, OHOS::Ace::DisplayMode value);
    static void SetPasswordIcon(FrameNode* frameNode, const PasswordIcon& passwordIcon);
    static void SetSelectedBackgroundColor(FrameNode* frameNode, const Color& value);
    static void SetMaxViewLines(FrameNode* frameNode, uint32_t value);
    static void SetNormalMaxViewLines(FrameNode* frameNode, uint32_t value);
    static void SetType(FrameNode* frameNode, TextInputType value);
    static void SetContentType(const FrameNode* frameNode, const TextContentType& value);
    static void SetCopyOption(FrameNode* frameNode, CopyOptions copyOption);
    static void SetShowPasswordIcon(FrameNode* frameNode, bool value);
    static void SetShowPassword(FrameNode* frameNode, bool value);
    static void SetTextAlign(FrameNode* frameNode, TextAlign value);
    static void SetTextColor(FrameNode* frameNode, const Color& value);
    static void SetCaretPosition(FrameNode* frameNode, const int32_t& value);
    static void SetFontStyle(FrameNode* frameNode, Ace::FontStyle value);
    static void SetMaxLength(FrameNode* frameNode, uint32_t value);
    static void ResetMaxLength(FrameNode* frameNode);
    static void SetCaretStyle(FrameNode* frameNode, const CaretStyle& value);
    static void SetPlaceholderColor(FrameNode* frameNode, const Color& value);
    static void SetFontWeight(FrameNode* frameNode, FontWeight value);
    static void SetEnterKeyType(FrameNode* frameNode, TextInputAction value);
    static void SetShowUnderline(FrameNode* frameNode, bool showUnderLine);
    static void SetNormalUnderlineColor(FrameNode* frameNode, const Color& normalColor);
    static void SetUserUnderlineColor(FrameNode* frameNode, UserUnderlineColor userColor);
    static void SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& value);
    static void SetMaxLines(FrameNode* frameNode, uint32_t value);
    static void SetPlaceholderFont(FrameNode* frameNode, const Font& value);
    static void SetFontSize(FrameNode* frameNode, const Dimension& value);
    static void SetCaretColor(FrameNode* frameNode, const Color& value);
    static void SetShowCounter(FrameNode* frameNode, bool value);
    static void SetCounterType(FrameNode* frameNode, int32_t value);
    static void SetShowError(FrameNode* frameNode, const std::string& errorText, bool visible);
    static void SetOnChange(FrameNode* frameNode, std::function<void(const std::string&, PreviewText&)>&& func);
    static void SetOnContentSizeChange(FrameNode* frameNode, std::function<void(float, float)>&& func);
    static void SetOnTextSelectionChange(FrameNode* frameNode, std::function<void(int32_t, int32_t)>&& func);
    static void SetTextFieldText(FrameNode* frameNode, const std::string& value);
    static void SetTextFieldPlaceHolder(FrameNode* frameNode, const std::string& placeholder);
    static void StopTextFieldEditing(FrameNode* frameNode);
    static void SetOnSubmit(FrameNode* frameNode, std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& func);
    static void SetOnCut(FrameNode* frameNode, std::function<void(const std::string&)>&& func);
    static void SetOnPasteWithEvent(FrameNode* frameNode,
        std::function<void(const std::string&, NG::TextCommonEvent&)>&& func);
    static void SetCleanNodeStyle(FrameNode* frameNode, CleanNodeStyle cleanNodeStyle);
    static void SetIsShowCancelButton(FrameNode* frameNode, bool isShowCancelButton);
    static void SetCancelIconSize(FrameNode* frameNode, const CalcDimension& iconSize);
    static void SetCanacelIconSrc(FrameNode* frameNode, const std::string& iconSrc);
    static void SetCancelIconColor(FrameNode* frameNode, const Color& iconColor);
    static void SetCancelButtonSymbol(FrameNode* frameNode, bool isShowSymbol);
    static void SetCancelSymbolIcon(FrameNode* frameNode,
        const std::function<void(WeakPtr<NG::FrameNode>)>& iconSymbol);
    static void SetBackgroundColor(FrameNode* frameNode, const Color& color);
    static std::string GetPlaceholderText(FrameNode* frameNode);
    static std::string GetTextFieldText(FrameNode* frameNode);
    static Color GetCaretColor(FrameNode* frameNode);
    static Dimension GetCaretStyle(FrameNode* frameNode);
    static bool GetShowUnderline(FrameNode* frameNode);
    static uint32_t GetMaxLength(FrameNode* frameNode);
    static TextInputAction GetEnterKeyType(FrameNode* frameNode);
    static Color GetPlaceholderColor(FrameNode* frameNode);
    static Font GetPlaceholderFont(FrameNode* frameNode);
    static bool GetRequestKeyboardOnFocus(FrameNode* frameNode);
    static TextInputType GetType(FrameNode* frameNode);
    static Color GetSelectedBackgroundColor(FrameNode* frameNode);
    static bool GetShowPasswordIcon(FrameNode* frameNode);
    static bool GetShowPassword(FrameNode* frameNode);
    static bool GetTextFieldEditing(FrameNode* frameNode);
    static bool GetShowCancelButton(FrameNode* frameNode);
    static CalcDimension GetCancelIconSize(FrameNode* frameNode);
    static std::string GetCanacelIconSrc(FrameNode* frameNode);
    static Color GetCancelIconColor(FrameNode* frameNode);
    static TextAlign GetTextAlign(FrameNode* frameNode);
    static Color GetTextColor(FrameNode* frameNode);
    static Ace::FontStyle GetFontStyle(FrameNode* frameNode);
    static FontWeight GetFontWeight(FrameNode* frameNode);
    static Dimension GetFontSize(FrameNode* frameNode);
    static CleanNodeStyle GetCleanNodeStyle(FrameNode* frameNode);
    static void SetShowCounterBorder(FrameNode* frameNode, bool value);
    static bool GetShowCounter(FrameNode* frameNode);
    static int GetCounterType(FrameNode* frameNode);
    static bool GetShowCounterBorder(FrameNode* frameNode);
    static void SetTextSelection(FrameNode* frameNode, int32_t start, int32_t end);
    static int32_t GetTextSelectionIndex(FrameNode* frameNode, bool isEnd);
    static void ResetTextInputPadding(FrameNode* frameNode);
    static void SetFontFeature(FrameNode* frameNode, const FONT_FEATURES_LIST& value);
    static void SetAutoWidth(FrameNode* frameNode);
    static void SetWidth(FrameNode* frameNode, const std::string& value);
    static void ClearWidth(FrameNode* frameNode);
    static void SetWordBreak(FrameNode* frameNode, Ace::WordBreak value);
    static void SetLineBreakStrategy(FrameNode* frameNode, LineBreakStrategy value);
    static void SetSelectAllValue(FrameNode* frameNode, bool isSelectAllValue);
    static void SetBlurOnSubmit(FrameNode* frameNode, bool blurOnSubmit);
    static bool GetBlurOnSubmit(FrameNode* frameNode);
    static void SetOnEditChange(FrameNode* frameNode, std::function<void(bool)>&& func);
    static void SetInputFilter(FrameNode* frameNode, const std::string& value,
        const std::function<void(const std::string&)>& onError);
    static void SetOnContentScroll(FrameNode* frameNode, std::function<void(float, float)>&& func);
    static void SetOnCopy(FrameNode* frameNode, std::function<void(const std::string&)>&& func);
    static void SetOnEditChanged(FrameNode* frameNode, std::function<void(bool)>&& func);
    static void SetCustomKeyboard(FrameNode* frameNode, FrameNode* customKeyboard, bool supportAvoidance = false);
    static void SetInputFilter(FrameNode* frameNode, const std::string& value);
    static void SetInputFilterError(FrameNode* frameNode, const std::function<void(const std::string&)>& onError);
    static Ace::WordBreak GetWordBreak(FrameNode* frameNode);
    static bool GetEnableAutoFill(FrameNode* frameNode);
    static TextContentType GetContentType(FrameNode* frameNode);
    static UserUnderlineColor GetUnderLineColor(FrameNode* frameNode);
    static std::string GetPasswordRules(FrameNode* frameNode);
    static bool GetSelectAllValue(FrameNode* frameNode);
    static std::string GetInputFilter(FrameNode* frameNode);
    static InputStyle GetInputStyle(FrameNode* frameNode);
    static RefPtr<TextFieldControllerBase> GetOrCreateController(FrameNode* frameNode);
    static FONT_FEATURES_LIST GetFontFeature(FrameNode* frameNode);
    static Dimension GetAdaptMinFontSize(FrameNode* frameNode);
    static Dimension GetAdaptMaxFontSize(FrameNode* frameNode);
    static Dimension GetLineHeight(FrameNode* frameNode);
    static uint32_t GetMaxLines(FrameNode* frameNode);
    static void SetPadding(FrameNode* frameNode, NG::PaddingProperty& newPadding);
    static RefPtr<UINode> GetCustomKeyboard(FrameNode* frameNode);
    static bool GetCustomKeyboardOption(FrameNode* frameNode);
    static void SetShowKeyBoardOnFocus(FrameNode* frameNode, bool value);
    static bool GetShowKeyBoardOnFocus(FrameNode* frameNode);
    static void SetNumberOfLines(FrameNode* frameNode, int32_t value);
    static int32_t GetNumberOfLines(FrameNode* frameNode);
    static void ResetNumberOfLines(FrameNode* frameNode);
    static void SetBorderWidth(FrameNode* frameNode, NG::BorderWidthProperty borderWidth);
    static void SetBorderRadius(FrameNode* frameNode, NG::BorderRadiusProperty borderRadius);
    static void SetBorderColor(FrameNode* frameNode, NG::BorderColorProperty borderColors);
    static void SetBorderStyle(FrameNode* frameNode, NG::BorderStyleProperty borderStyles);
    static void SetMargin(FrameNode* frameNode, NG::PaddingProperty& margin);
    static PaddingProperty GetMargin(FrameNode* frameNode);
    static void SetOnWillInsertValueEvent(FrameNode* frameNode, std::function<bool(const InsertValueInfo&)>&& func);
    static void SetOnDidInsertValueEvent(FrameNode* frameNode, std::function<void(const InsertValueInfo&)>&& func);
    static void SetOnWillDeleteEvent(FrameNode* frameNode, std::function<bool(const DeleteValueInfo&)>&& func);
    static void SetOnDidDeleteEvent(FrameNode* frameNode, std::function<void(const DeleteValueInfo&)>&& func);
    static void SetEnablePreviewText(FrameNode* frameNode, bool enablePreviewText);
    static PaddingProperty GetPadding(FrameNode* frameNode);
    static void OnCreateMenuCallbackUpdate(FrameNode* frameNode, const NG::OnCreateMenuCallback&& onCreateMenuCallback);
    static void OnMenuItemClickCallbackUpdate(
        FrameNode* frameNode, const NG::OnMenuItemClickCallback&& onMenuItemClick);
    static void SetJSTextEditableController(FrameNode* frameNode, const RefPtr<Referenced>& controller);
    static RefPtr<Referenced> GetJSTextEditableController(FrameNode* frameNode);

private:
    void AddDragFrameNodeToManager() const;
    void SetDraggable(bool draggable);
    void SetTextRectWillChange();
    void SetDefaultPadding();
    void SetBackBorderRadius();
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MODEL_NG_H
