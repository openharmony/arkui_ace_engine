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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_RICH_EDITOR_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_RICH_EDITOR_MODEL_IMPL_H

#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
namespace OHOS::Ace::Framework {
class ACE_EXPORT RichEditorModelImpl : public RichEditorModel {
    void Create(bool isStyledStringMode = false) override {}
    RefPtr<RichEditorBaseControllerBase> GetRichEditorController() override;
    void SetOnReady(std::function<void()>&& func) override {}
    void SetOnSelect(std::function<void(const BaseEventInfo*)>&& func) override {}
    void SetOnSelectionChange(std::function<void(const BaseEventInfo*)>&& func) override {}
    void SetAboutToIMEInput(std::function<bool(const NG::RichEditorInsertValue&)>&& func) override {}
    void SetOnIMEInputComplete(std::function<void(const NG::RichEditorAbstractSpanResult&)>&& func) override {}
    void SetOnDidIMEInput(std::function<void(const TextRange&)>&& func) override {}
    void SetAboutToDelete(std::function<bool(const NG::RichEditorDeleteValue&)>&& func) override {}
    void SetOnDeleteComplete(std::function<void()>&& func) override {}
    void SetCustomKeyboard(std::function<void()>&& func, bool supportAvoidance = false) override {}
    void SetCopyOption(CopyOptions& copyOptions) override {}
    void BindSelectionMenu(NG::TextSpanType& editorType, NG::TextResponseType& responseType,
        std::function<void()>& buildFunc, NG::SelectMenuParam& menuParam) override {}
    void SetOnPaste(std::function<void(NG::TextCommonEvent&)>&& func) override {}
    void SetPlaceholder(PlaceholderOptions& options) override {}
    void SetTextDetectEnable(bool value) override {}
    void SetSupportPreviewText(bool value) override {}
    void SetTextDetectConfig(const TextDetectConfig& textDetectConfig) override {}
    void SetSelectedBackgroundColor(const Color& selectedColor) override {}
    void SetCaretColor(const Color& color) override {}
    void SetOnEditingChange(std::function<void(const bool&)>&& func) override {}
    void SetOnSubmit(std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& func) override {}
    void SetEnterKeyType(TextInputAction value) override {}
    void SetOnWillChange(std::function<bool(const NG::RichEditorChangeValue&)>&& func) override {}
    void SetOnDidChange(std::function<void(const NG::RichEditorChangeValue&)>&& func) override {}
    void SetOnCut(std::function<void(NG::TextCommonEvent&)>&& func) override {}
    void SetOnCopy(std::function<void(NG::TextCommonEvent&)>&& func) override {}
};
} // namespace OHOS::Ace::Framework

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_RICH_EDITOR_MODEL_IMPL_H
