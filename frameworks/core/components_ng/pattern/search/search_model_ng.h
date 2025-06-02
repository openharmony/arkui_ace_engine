/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_MODEL_NG_H

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components/search/search_theme.h"
#include "core/components_ng/pattern/search/search_model.h"
#include "core/components_ng/pattern/search/search_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT SearchModelNG : public OHOS::Ace::SearchModel {
public:
    RefPtr<TextFieldControllerBase> Create(const std::optional<std::u16string>& value,
        const std::optional<std::u16string>& placeholder, const std::optional<std::string>& icon) override;
    void RequestKeyboardOnFocus(bool needToRequest) override;
    void SetSearchButton(const std::string& text) override;
    void SetCaretWidth(const Dimension& value) override;
    void SetCaretColor(const Color& color) override;
    void ResetCaretColor() override;
    void SetSearchIconSize(const Dimension& value) override;
    void SetSearchIconColor(const Color& color) override;
    void ResetSearchIconColor() override;
    void SetSearchSrcPath(
        const std::string& src, const std::string& bundleName, const std::string& moduleName) override;
    void SetSearchSymbolIcon(std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol) override;
    void SetSearchDefaultIcon() override;
    void SetSearchImageIcon(NG::IconOptions& iconOptions) override;
    void SetCancelSymbolIcon(std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol) override;
    void SetCancelDefaultIcon() override;
    void SetCancelImageIcon(NG::IconOptions& iconOptions) override;
    void SetRightIconSrcPath(const std::string& src) override;
    void SetCancelButtonStyle(CancelButtonStyle cancelButtonStyle) override;
    void SetCancelIconSize(const Dimension& value) override;
    void SetCancelIconColor(const Color& color) override;
    void ResetCancelIconColor() override;
    void SetSearchButtonFontSize(const Dimension& value) override;
    void SetSearchButtonFontColor(const Color& color) override;
    void ResetSearchButtonFontColor() override;
    void SetSearchButtonAutoDisable(bool needToDisable) override;
    void SetPlaceholderColor(const Color& color) override;
    void ResetPlaceholderColor() override;
    void SetPlaceholderFont(const Font& font) override;
    void SetTextFont(const Font& font) override;
    void SetMinFontScale(const float value) override;
    void SetMaxFontScale(const float value) override;
    void SetTextColor(const Color& color) override;
    void ResetTextColor() override;
    void SetBackgroundColor(const Color& color) override;
    void ResetBackgroundColor() override;
    void SetTextAlign(const TextAlign& textAlign) override;
    void SetCopyOption(const CopyOptions& copyOptions) override;
    void SetHeight(const Dimension& height) override;
    void SetOnSubmit(std::function<void(const std::string&)>&& onSubmit) override {};
    void SetOnSubmit(std::function<void(const std::u16string&, NG::TextFieldCommonEvent&)>&& onSubmit) override;
    void SetOnChange(std::function<void(const ChangeValueInfo&)>&& onChange) override;
    void SetOnTextSelectionChange(std::function<void(int32_t, int32_t)>&& func) override;
    void SetOnScroll(std::function<void(float, float)>&& func) override;
    void SetOnCopy(std::function<void(const std::u16string&)>&& func) override;
    void SetOnCut(std::function<void(const std::u16string&)>&& func) override;
    void SetOnWillInsertValueEvent(std::function<bool(const InsertValueInfo&)>&& func) override;
    void SetOnDidInsertValueEvent(std::function<void(const InsertValueInfo&)>&& func) override;
    void SetOnWillDeleteEvent(std::function<bool(const DeleteValueInfo&)>&& func) override;
    void SetOnDidDeleteEvent(std::function<void(const DeleteValueInfo&)>&& func) override;
    void SetOnPaste(std::function<void(const std::u16string&)>&& func) override;
    void SetOnPasteWithEvent(std::function<void(const std::u16string&, NG::TextCommonEvent&)>&& func) override;
    void SetOnWillChangeEvent(std::function<bool(const ChangeValueInfo&)>&& func) override;
    void SetOnChangeEvent(std::function<void(const std::u16string&)>&& onChangeEvent) override;
    void SetSelectionMenuHidden(bool selectionMenuHidden) override;
    void SetCustomKeyboard(const std::function<void ()> &&buildFunc, bool supportAvoidance = false) override;
    void SetSearchEnterKeyType(TextInputAction value) override;
    void SetSearchCapitalizationMode(AutoCapitalizationMode value) override;
    void SetInputFilter(const std::string& value, const std::function<void(const std::u16string&)>& onError) override;
    void SetOnEditChanged(std::function<void(bool)>&& func) override;
    void SetTextIndent(const Dimension& value) override;
    void SetMaxLength(uint32_t value) override;
    void ResetMaxLength() override;
    void SetType(TextInputType value) override;
    void SetLetterSpacing(const Dimension& value) override;
    void SetLineHeight(const Dimension& value) override;
    void SetHalfLeading(bool value) override;
    void SetAdaptMinFontSize(const Dimension& value) override;
    void SetAdaptMaxFontSize(const Dimension& value) override;
    void SetTextDecoration(Ace::TextDecoration value) override;
    void SetTextDecorationColor(const Color& value) override;
    void SetTextDecorationStyle(Ace::TextDecorationStyle value) override;
    void SetFontFeature(const FONT_FEATURES_LIST& value) override;
    void UpdateInspectorId(const std::string& key) override;
    void SetDragPreviewOptions(const NG::DragPreviewOption option) override;
    void SetSelectedBackgroundColor(const Color& value) override;
    void ResetSelectedBackgroundColor() override;
    void SetSelectionMenuOptions(const NG::OnCreateMenuCallback&& onCreateMenuCallback,
        const NG::OnMenuItemClickCallback&& onMenuItemClick) override;
    void SetEnablePreviewText(bool enablePreviewText) override;
    void SetEnableHapticFeedback(bool state) override;
    void SetBackBorderRadius() override;
    void SetStopBackPress(bool isStopBackPress) override;
    void SetKeyboardAppearance(KeyboardAppearance value) override;
    void SetStrokeWidth(const Dimension& value) override;
    void SetStrokeColor(const Color& value) override;
    void ResetStrokeColor() override;
    static RefPtr<SearchNode> CreateFrameNode(int32_t nodeId);
    static void SetTextValue(FrameNode* frameNode, const std::optional<std::string>& value);
    static void SetPlaceholder(FrameNode* frameNode, const std::optional<std::string>& placeholder);
    static void SetIcon(FrameNode* frameNode, const std::optional<std::string>& icon);
    static void SetCaretPosition(FrameNode* frameNode, const int32_t& value);
    static void SetAdaptMinFontSize(FrameNode* frameNode, const Dimension& value);
    static void SetInputFilter(
        FrameNode* frameNode, const std::string& value, const std::function<void(const std::u16string&)>& onError);
    static void SetAdaptMaxFontSize(FrameNode* frameNode, const Dimension& value);
    static void SetTextIndent(FrameNode* frameNode, const Dimension& value);
    static void RequestKeyboardOnFocus(FrameNode* frameNode, bool needToRequest);
    static void SetPlaceholderFont(FrameNode* frameNode, const Font& font);
    static void SetSearchIconSize(FrameNode* frameNode, const Dimension& value);
    static void SetSearchSrcPath(FrameNode* frameNode, const std::string& src);
    static void SetSearchIconColor(FrameNode* frameNode, const Color& color);
    static void SetSearchImageIcon(FrameNode* frameNode, IconOptions& iconOptions);
    static void SetSearchButton(FrameNode* frameNode, const std::string& text);
    static void SetSearchButtonFontSize(FrameNode* frameNode, const Dimension& value);
    static void SetSearchButtonFontColor(FrameNode* frameNode, const Color& color);
    static void SetSearchButtonAutoDisable(FrameNode* frameNode, bool needToDisable);
    static void SetTextColor(FrameNode* frameNode, const Color& color);
    static void ResetTextColor(FrameNode* frameNode);
    static void SetCopyOption(FrameNode* frameNode, const CopyOptions& copyOptions);
    static void SetTextFont(FrameNode* frameNode, const Font& font);
    static void SetPlaceholderColor(FrameNode* frameNode, const Color& color);
    static void ResetPlaceholderColor(FrameNode* frameNode);
    static void SetSelectionMenuHidden(FrameNode* frameNode, bool selectionMenuHidden);
    static void SetCaretWidth(FrameNode* frameNode, const Dimension& value);
    static void SetCaretColor(FrameNode* frameNode, const Color& color);
    static void ResetCaretColor(FrameNode* frameNode);
    static void SetTextAlign(FrameNode* frameNode, const TextAlign& textAlign);
    static void SetMinFontScale(FrameNode* frameNode, const float value);
    static void SetMaxFontScale(FrameNode* frameNode, const float value);
    static void SetRightIconSrcPath(FrameNode* frameNode, const std::string& src);
    static void SetCancelIconColor(FrameNode* frameNode, const Color& color);
    static void SetCancelIconSize(FrameNode* frameNode, const Dimension& value);
    static void SetCancelButtonStyle(FrameNode* frameNode, CancelButtonStyle style);
    static void SetCancelImageIcon(FrameNode* frameNode, IconOptions& iconOptions);
    static void SetHeight(FrameNode* frameNode, const Dimension& height);
    static void SetSearchEnterKeyType(FrameNode* frameNode, TextInputAction value);
    static void SetAutoCapitalizationMode(FrameNode* frameNode, AutoCapitalizationMode value);
    static void SetId(FrameNode* frameNode, const std::string& key);
    static void SetTextDecoration(FrameNode* frameNode, Ace::TextDecoration value);
    static void SetTextDecorationColor(FrameNode* frameNode, const Color& value);
    static void SetTextDecorationStyle(FrameNode* frameNode, Ace::TextDecorationStyle value);
    static void SetLetterSpacing(FrameNode* frameNode, const Dimension& value);
    static void SetLineHeight(FrameNode* frameNode, const Dimension& value);
    static void SetHalfLeading(FrameNode* frameNode, const bool& value);
    static void SetFontFeature(FrameNode* frameNode, const FONT_FEATURES_LIST& value);
    static void SetSelectedBackgroundColor(FrameNode* frameNode, const Color& value);
    static void ResetSelectedBackgroundColor(FrameNode* frameNode);
    static void SetOnSubmit(FrameNode* frameNode,
        std::function<void(const std::u16string&, NG::TextFieldCommonEvent&)>&& onSubmit);
    static void SetOnWillChangeEvent(FrameNode* frameNode, std::function<bool(const ChangeValueInfo&)>&& func);
    static void SetOnChange(FrameNode* frameNode, std::function<void(const ChangeValueInfo&)>&& onChange);
    static void SetOnCopy(FrameNode* frameNode, std::function<void(const std::u16string&)>&& func);
    static void SetOnCut(FrameNode* frameNode, std::function<void(const std::u16string&)>&& func);
    static void SetOnPasteWithEvent(FrameNode* frameNode,
                                    std::function<void(const std::u16string&, NG::TextCommonEvent&)>&& func);
    static void SetMaxLength(FrameNode* frameNode, uint32_t value);
    static void ResetMaxLength(FrameNode* frameNode);
    static void SetType(FrameNode* frameNode, TextInputType value);
    static void SetOnEditChange(FrameNode* frameNode, std::function<void(bool)>&& func);
    static void SetOnTextSelectionChange(FrameNode* frameNode, std::function<void(int32_t, int32_t)>&& func);
    static void SetOnContentScroll(FrameNode* frameNode, std::function<void(float, float)>&& func);
    static void SetShowCounter(FrameNode* frameNode, bool value);
    static void SetCounterType(FrameNode* frameNode, int32_t value);
    static void SetShowCounterBorder(FrameNode* frameNode, bool value);
    static RefPtr<TextFieldControllerBase> GetSearchController(FrameNode* frameNode);
    static void SetOnWillInsertValueEvent(FrameNode* frameNode, std::function<bool(const InsertValueInfo&)>&& func);
    static void SetOnDidInsertValueEvent(FrameNode* frameNode, std::function<void(const InsertValueInfo&)>&& func);
    static void SetOnWillDeleteEvent(FrameNode* frameNode, std::function<bool(const DeleteValueInfo&)>&& func);
    static void SetOnDidDeleteEvent(FrameNode* frameNode, std::function<void(const DeleteValueInfo&)>&& func);
    static void SetEnablePreviewText(FrameNode* frameNode, bool enablePreviewText);
    static void OnCreateMenuCallbackUpdate(FrameNode* frameNode, const NG::OnCreateMenuCallback&& onCreateMenuCallback);
    static void OnMenuItemClickCallbackUpdate(
        FrameNode* frameNode, const NG::OnMenuItemClickCallback&& onMenuItemClick);
    static void SetEnableHapticFeedback(FrameNode* frameNode, bool state);
    static void SetStopBackPress(FrameNode* frameNode, bool isStopBackPress);
    static void SetKeyboardAppearance(FrameNode* frameNode, KeyboardAppearance value);
    static Dimension GetStrokeWidth(FrameNode* frameNode);
    static Color GetStrokeColor(FrameNode* frameNode);
    static void SetStrokeWidth(FrameNode* frameNode, const Dimension& value);
    static void SetStrokeColor(FrameNode* frameNode, const Color& value);
    static void ResetStrokeColor(FrameNode* frameNode);

private:
    static RefPtr<SearchTheme> GetTheme(const RefPtr<SearchNode>& frameNode);
    static RefPtr<SearchNode> CreateSearchNode(int32_t nodeId, const std::optional<std::u16string>& value,
        const std::optional<std::u16string>& placeholder, const std::optional<std::string>& icon);
    static void UpdateSearchNodeBorderProps(const RefPtr<SearchNode>& frameNode,
        const RefPtr<SearchTheme>& searchTheme = nullptr);
    static void CreateTextField(const RefPtr<SearchNode>& parentNode, const std::optional<std::u16string>& placeholder,
        const std::optional<std::u16string>& value, bool hasTextFieldNode,
        const RefPtr<SearchTheme>& searchTheme = nullptr);
    static void CreateButton(const RefPtr<SearchNode>& parentNode, bool hasButtonNode,
        const RefPtr<SearchTheme>& searchTheme = nullptr);
    static void CreateCancelButton(const RefPtr<SearchNode>& parentNode, bool hasCancelButtonNode,
        const  RefPtr<SearchTheme>& searchTheme = nullptr);
    static RefPtr<SearchNode> GetOrCreateSearchNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);
    RefPtr<FrameNode> GetSearchTextFieldFrameNode() const;
    static void TextFieldUpdateContext(const RefPtr<FrameNode>& frameNode);
    static void CreateDivider(const RefPtr<SearchNode>& parentNode, bool hasDividerNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_MODEL_NG_H
