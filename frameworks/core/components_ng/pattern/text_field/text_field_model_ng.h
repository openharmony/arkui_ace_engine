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
    void SetOnChangeEvent(std::function<void(const std::string&)>&& func) override;
    void SetBackgroundColor(const Color& color, bool tmp) override;
    void SetHeight(const Dimension& value) override;
    void SetPadding(NG::PaddingProperty& newPadding, Edge oldPadding, bool tmp) override;
    void SetHoverEffect(HoverEffectType hoverEffect) override;
    void SetSelectionMenuHidden(bool contextMenuHidden) override;
    void SetCustomKeyboard(const std::function<void ()> &&buildFunc) override;

private:
    void AddDragFrameNodeToManager() const;
    void SetDraggable(bool draggable);
    void SetTextRectWillChange();
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MODEL_NG_H
