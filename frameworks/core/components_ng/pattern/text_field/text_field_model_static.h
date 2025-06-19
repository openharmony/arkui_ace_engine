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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MODEL_STATIC_H

#include "core/components_ng/pattern/text_field/text_content_type.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT TextFieldModelStatic {
public:
    static void SetTextDecoration(FrameNode* frameNode, const std::optional<TextDecoration>& valueOpt);
    static void SetTextDecorationColor(FrameNode* frameNode, const std::optional<Color>& valueOpt);
    static void SetTextDecorationStyle(FrameNode* frameNode, const std::optional<TextDecorationStyle>& valueOpt);
    static void SetLetterSpacing(FrameNode* frameNode, const std::optional<Dimension>& valueOpt);
    static void SetLineHeight(FrameNode* frameNode, const std::optional<Dimension>& valueOpt);
    static void SetLineSpacing(FrameNode* frameNode, const std::optional<Dimension>& valueOpt);
    static void SetTextOverflow(FrameNode* frameNode, const std::optional<TextOverflow>& valueOpt);
    static void SetTextIndent(FrameNode* frameNode, const std::optional<Dimension>& valueOpt);
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId, const std::optional<std::u16string>& placeholder,
        const std::optional<std::u16string>& value, bool isTextArea);
    static void SetAdaptMinFontSize(FrameNode* frameNode, const std::optional<Dimension>& valueOpt);
    static void SetAdaptMaxFontSize(FrameNode* frameNode, const std::optional<Dimension>& valueOpt);
    static void SetHeightAdaptivePolicy(FrameNode* frameNode, const std::optional<TextHeightAdaptivePolicy>& valueOpt);
    static void SetInputStyle(FrameNode* frameNode, const std::optional<InputStyle>& valueOpt);
    static void SetPasswordRules(FrameNode* frameNode, const std::optional<std::string>& passwordRules);
    static void SetBarState(FrameNode* frameNode, const std::optional<OHOS::Ace::DisplayMode>& valueOpt);
    static void SetPasswordIcon(FrameNode* frameNode, const std::optional<PasswordIcon>& passwordIcon);
    static void SetSelectedBackgroundColor(FrameNode* frameNode, const std::optional<Color>& colorOpt);
    static void SetMaxViewLines(FrameNode* frameNode, const std::optional<uint32_t>& valueOpt);
    static void SetNormalMaxViewLines(FrameNode* frameNode, const std::optional<uint32_t>& valueOpt);
    static void SetType(FrameNode* frameNode, const std::optional<TextInputType>& valueOpt);
    static void SetContentType(const FrameNode* frameNode, const std::optional<TextContentType>& valueOpt);
    static void SetCopyOption(FrameNode* frameNode, const std::optional<CopyOptions>& copyOptionOpt);
    static void SetShowPassword(FrameNode* frameNode, const std::optional<bool>& valueOpt);
    static void SetTextAlign(FrameNode* frameNode, const std::optional<TextAlign>& valueOpt);
    static void SetTextColor(FrameNode* frameNode, const std::optional<Color>& colorOpt);
    static void SetCaretPosition(FrameNode* frameNode, const std::optional<int32_t>& optValue);
    static void SetFontStyle(FrameNode* frameNode, const std::optional<Ace::FontStyle>& valueOpt);
    static void SetCaretStyle(FrameNode* frameNode, const std::optional<CaretStyle>& value);
    static void SetPlaceholderColor(FrameNode* frameNode, const std::optional<Color>& colorOpt);
    static void SetFontWeight(FrameNode* frameNode, const std::optional<FontWeight>& value);
    static void SetEnterKeyType(FrameNode* frameNode, const std::optional<TextInputAction>& valueOpt);
    static void SetNormalUnderlineColor(FrameNode* frameNode, const std::optional<Color>& normalColor);
    static void SetUserUnderlineColor(FrameNode* frameNode, const std::optional<UserUnderlineColor>& userColor);
    static void SetFontFamily(FrameNode* frameNode, const std::optional<std::vector<std::string>>& fontFamilies);
    static void SetPlaceholderFont(FrameNode* frameNode, const std::optional<Font>& valueOpt);
    static void SetFontSize(FrameNode* frameNode, const std::optional<Dimension>& value);
    static void SetCaretColor(FrameNode* frameNode, const std::optional<Color>& colorOpt);
    static void SetCounterType(FrameNode* frameNode, const std::optional<int32_t>& value);
    static void SetShowError(FrameNode* frameNode, const std::optional<std::u16string>& errorText, bool visible);
    static void SetTextFieldText(FrameNode* frameNode, const std::optional<std::u16string>& optValue);
    static void SetTextFieldPlaceHolder(FrameNode* frameNode, const std::optional<std::u16string>& placeholder);
    static void SetOnPaste(FrameNode* frameNode, std::function<void(const std::u16string&)>&& func);
    static void SetShowUnit(FrameNode* frameNode, std::function<RefPtr<UINode>()>&& builder);
    static void SetOnChangeEvent(FrameNode* frameNode, std::function<void(const std::u16string&)>&& func);
    static void SetCleanNodeStyle(FrameNode* frameNode, const std::optional<CleanNodeStyle>& cleanNodeStyle);
    static void SetCancelIconSize(FrameNode* frameNode, const std::optional<CalcDimension>& iconSizeOpt);
    static void SetCanacelIconSrc(FrameNode* frameNode,
        const std::string& iconSrc, const std::string& bundleName, const std::string& moduleName);
    static void SetCancelIconColor(FrameNode* frameNode, const std::optional<Color>& iconColor);
    // static void SetBackgroundColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetShowCounterBorder(FrameNode* frameNode, const std::optional<bool>& value);
    static void SetWordBreak(FrameNode* frameNode, const std::optional<Ace::WordBreak>& valueOpt);
    static void SetLineBreakStrategy(FrameNode* frameNode, const std::optional<LineBreakStrategy>& valueOpt);
    static void SetOnSecurityStateChange(FrameNode* frameNode, std::function<void(bool)>&& func);
    static RefPtr<TextFieldControllerBase> GetController(FrameNode* frameNode,
        const std::optional<std::u16string>& placeholder, const std::optional<std::u16string>& value);
    static void SetStopBackPress(FrameNode* frameNode, const std::optional<bool>& isStopBackPress);
    static void SetKeyboardAppearance(FrameNode* frameNode, const std::optional<KeyboardAppearance>& valueOpt);
    static void RequestKeyboardOnFocus(FrameNode* frameNode, const std::optional<bool>& needToRequest);
    static void SetSelectionMenuHidden(FrameNode* frameNode, const std::optional<bool>& selectionMenuHidden);
    static void SetEnablePreviewText(FrameNode* frameNode, const std::optional<bool>& enablePreviewText);
    static void SetEnableHapticFeedback(FrameNode* frameNode, const std::optional<bool>& state);
    static void SetEnableAutoFill(FrameNode* frameNode, const std::optional<bool>& state);
    static void SetEllipsisMode(FrameNode* frameNode, const std::optional<EllipsisMode>& optValue);
    static void SetMinFontScale(FrameNode* frameNode, const std::optional<float>& optValue);
    static void SetMaxFontScale(FrameNode* frameNode, const std::optional<float>& optValue);
    static void SetHalfLeading(FrameNode* frameNode, const std::optional<bool>& valueOpt);
    static void SetSelectionMenuOptions(FrameNode* frameNode, const NG::OnCreateMenuCallback&& onCreateMenuCallback,
        const NG::OnMenuItemClickCallback&& onMenuItemClick);
    static void SetShowPasswordIcon(FrameNode* frameNode, const std::optional<bool>& value);
    static void SetShowUnderline(FrameNode* frameNode, const std::optional<bool>& showUnderLine);
    static void SetSelectAllValue(FrameNode* frameNode, const std::optional<bool>& isSelectAllValue);

private:

};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_MODEL_STATIC_H
