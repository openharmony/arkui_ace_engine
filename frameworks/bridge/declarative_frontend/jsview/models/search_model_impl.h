/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_SEARCH_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_SEARCH_MODEL_IMPL_H

#include "core/components/image/image_component.h"
#include "core/components/search/search_component.h"
#include "core/components/search/search_theme.h"
#include "core/components/text_field/text_field_component.h"
#include "core/components_ng/pattern/search/search_model.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT SearchModelImpl : public OHOS::Ace::SearchModel {
public:
    RefPtr<TextFieldControllerBase> Create(const std::optional<std::string>& value,
        const std::optional<std::string>& placeholder, const std::optional<std::string>& icon) override;
    void RequestKeyboardOnFocus(bool needToRequest) override {};
    void SetSearchButton(const std::string& text) override;
    void SetCaretWidth(const Dimension& value) override {}
    void SetCaretColor(const Color& color) override {}
    void SetSearchIconSize(const Dimension& value) override {}
    void SetSearchIconColor(const Color& color) override {}
    void SetSearchSrcPath(const std::string& src) override {}
    void SetRightIconSrcPath(const std::string& src) override {}
    void SetCancelButtonStyle(OHOS::Ace::CancelButtonStyle cancelButtonStyle) override {}
    void SetCancelIconSize(const Dimension& value) override {}
    void SetCancelIconColor(const Color& color) override {}
    void SetSearchButtonFontSize(const Dimension& value) override {}
    void SetSearchButtonFontColor(const Color& color) override {}
    void SetPlaceholderColor(const Color& color) override;
    void SetPlaceholderFont(const Font& font) override;
    void SetTextFont(const Font& font) override;
    void SetTextColor(const Color& color) override {}
    void SetTextAlign(const TextAlign& textAlign) override;
    void SetCopyOption(const CopyOptions& copyOptions) override;
    void SetMenuOptionItems(std::vector<NG::MenuOptionsParam>&& menuOptionsItems) override;
    void SetFocusable(bool focusable) override;
    void SetFocusNode(bool isFocusNode) override;
    void SetHeight(const Dimension& value) override;
    void SetBackBorder() override;
    void SetOnSubmit(std::function<void(const std::string&)>&& onSubmit) override;
    void SetOnChange(std::function<void(const std::string&)>&& onChange) override;
    void SetOnTextSelectionChange(std::function<void(int32_t, int32_t)>&& func) override {};
    void SetOnScroll(std::function<void(float, float)>&& func) override {};
    void SetOnCopy(std::function<void(const std::string&)>&& func) override;
    void SetOnCut(std::function<void(const std::string&)>&& func) override;
    void SetOnPaste(std::function<void(const std::string&)>&& func) override;
    void SetOnChangeEvent(std::function<void(const std::string&)>&& onChangeEvent) override {};
    void SetSelectionMenuHidden(bool selectionMenuHidden) override {};
    void SetCustomKeyboard(const std::function<void ()> &&buildFunc) override {};
    void SetMaxLength(uint32_t value) override {};
    void ResetMaxLength() override {};
private:
    void InitializeDefaultValue(const RefPtr<BoxComponent>& boxComponent, const RefPtr<TextFieldComponent>& component,
        const RefPtr<TextFieldTheme>& theme);
    void UpdateDecorationStyle(const RefPtr<BoxComponent>& boxComponent, const RefPtr<TextFieldComponent>& component,
        const Border& boxBorder, bool hasBoxRadius);
    void InitializeComponent(OHOS::Ace::RefPtr<OHOS::Ace::SearchComponent>& searchComponent,
        OHOS::Ace::RefPtr<OHOS::Ace::TextFieldComponent>& textFieldComponent,
        const OHOS::Ace::RefPtr<OHOS::Ace::SearchTheme>& searchTheme,
        const OHOS::Ace::RefPtr<OHOS::Ace::TextFieldTheme>& textFieldTheme);
    void PrepareSpecializedComponent(OHOS::Ace::RefPtr<OHOS::Ace::SearchComponent>& searchComponent,
        OHOS::Ace::RefPtr<OHOS::Ace::TextFieldComponent>& textFieldComponent);
};

} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_SEARCH_MODEL_IMPL_H
