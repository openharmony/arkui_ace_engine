/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
    void SetPlaceholderColor(const Color& value) override;
    void SetPlaceholderFont(const Font& value) override;
    void SetEnterKeyType(TextInputAction value) override;
    void SetTextAlign(TextAlign value) override;
    void SetCaretColor(const Color& value) override;
    void SetCaretStyle(const CaretStyle& value) override;
    void SetCaretPosition(const int32_t& value) override;
    void SetSelectedBackgroundColor(const Color& value) override;
    void SetMaxLength(uint32_t value) override;
    void SetMaxLines(uint32_t value) override;
    void SetFontSize(const Dimension& value) override;
    void SetFontWeight(FontWeight value) override;
    void SetTextColor(const Color& value) override;
    void SetFontStyle(Ace::FontStyle value) override;
    void SetFontFamily(const std::vector<std::string>& value) override;
    void SetInputFilter(const std::string& value, const std::function<void(const std::string&)>& onError) override;
    void SetInputStyle(InputStyle value) override;
    void SetShowPasswordIcon(bool value) override;
    void SetOnEditChanged(std::function<void(bool)>&& func) override;
    void SetOnSubmit(std::function<void(int32_t)>&& func) override;
    void SetOnChange(std::function<void(const std::string&)>&& func) override;
    void SetOnTextSelectionChange(std::function<void(int32_t, int32_t)>&& func) override;
    void SetOnContentScroll(std::function<void(float, float)>&& func) override;
    void SetOnCopy(std::function<void(const std::string&)>&& func) override;
    void SetOnCut(std::function<void(const std::string&)>&& func) override;
    void SetOnPaste(std::function<void(const std::string&)>&& func) override;
    void SetOnPasteWithEvent(std::function<void(const std::string&, NG::TextCommonEvent&)>&& func) override;
    void SetCopyOption(CopyOptions copyOption) override;
    void SetMenuOptionItems(std::vector<MenuOptionsParam>&& menuOptionsItems) override;
    void ProcessDefaultPadding(PaddingProperty& paddings);
    void ResetMaxLength() override;
    void SetForegroundColor(const Color& value) override;
    void SetPasswordIcon(const PasswordIcon& passwordIcon) override;
    void SetShowUnit(std::function<void()>&& unitFunction) override;
    void SetShowError(const std::string& errorText, bool visible) override;
    void SetBarState(OHOS::Ace::DisplayMode value) override;
    void SetMaxViewLines(uint32_t value) override;

    void SetShowUnderline(bool showUnderLine) override;
    void SetShowCounter(bool value) override;
    void SetCounterType(int32_t value) override;
    void SetShowCounterBorder(bool value) override;
    void SetOnChangeEvent(std::function<void(const std::string&)>&& func) override;
    void SetBackgroundColor(const Color& color, bool tmp) override;
    void SetHeight(const Dimension& value) override;
    void SetPadding(NG::PaddingProperty& newPadding, Edge oldPadding, bool tmp) override;
    void SetHoverEffect(HoverEffectType hoverEffect) override;
    void SetSelectionMenuHidden(bool contextMenuHidden) override;
    void SetCustomKeyboard(const std::function<void()>&& buildFunc) override;
    void SetPasswordRules(const std::string& passwordRules) override;
    void SetEnableAutoFill(bool enableAutoFill) override;
    void SetCleanNodeStyle(CleanNodeStyle cleanNodeStyle) override;
    void SetCancelIconSize(const CalcDimension& iconSize) override;
    void SetCanacelIconSrc(const std::string& iconSrc) override;
    void SetCancelIconColor(const Color& iconColor) override;
    void SetIsShowCancelButton(bool isShowCancelButton) override;
    void SetSelectAllValue(bool isSetSelectAllValue) override;

    static void SetInputStyle(FrameNode* frameNode, InputStyle value);
    static void SetSelectionMenuHidden(FrameNode* frameNode, bool contextMenuHidden);
    static void RequestKeyboardOnFocus(FrameNode* frameNode, bool needToRequest);
    static void SetBarState(FrameNode* frameNode, OHOS::Ace::DisplayMode value);
    static void SetPasswordIcon(FrameNode* frameNode, const PasswordIcon& passwordIcon);
    static void SetSelectedBackgroundColor(FrameNode* frameNode, const Color& value);
    static void SetMaxViewLines(FrameNode* frameNode, uint32_t value);
    static void SetType(FrameNode* frameNode, TextInputType value);
    static void SetCopyOption(FrameNode* frameNode, CopyOptions copyOption);
    static void SetShowPasswordIcon(FrameNode* frameNode, bool value);
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
    static void SetFontFamily(FrameNode* frameNode, const std::vector<std::string>& value);
    static void SetMaxLines(FrameNode* frameNode, uint32_t value);
    static void SetPlaceholderFont(FrameNode* frameNode, const Font& value);
    static void SetFontSize(FrameNode* frameNode, const Dimension& value);
    static void SetCaretColor(FrameNode* frameNode, const Color& value);
    static void SetShowCounter(FrameNode* frameNode, bool value);
    static void SetShowError(FrameNode* frameNode, const std::string& errorText, bool visible);
    static void SetCounterType(FrameNode* frameNode, int32_t value);
private:
    void AddDragFrameNodeToManager() const;
    void SetDraggable(bool draggable);
    void SetTextRectWillChange();
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MODEL_NG_H
