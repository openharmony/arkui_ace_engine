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
    void SetAboutToDelete(std::function<bool(const RichEditorDeleteValue&)>&& func) override;
    void SetOnDeleteComplete(std::function<void()>&& func) override;
    void SetCustomKeyboard(std::function<void()>&& func, bool supportAvoidance) override;
    void SetCopyOption(CopyOptions& copyOptions) override;
    void BindSelectionMenu(TextSpanType& editorType, TextResponseType& responseType,
        std::function<void()>& buildFunc, SelectMenuParam& menuParam) override;
    void SetOnPaste(std::function<void(NG::TextCommonEvent&)>&& func) override;
    void SetPlaceholder(PlaceholderOptions& options) override;
    void SetTextDetectEnable(bool value) override;
    void SetTextDetectConfig(const std::string& value, std::function<void(const std::string&)>&& onResult) override;
    void SetSelectedBackgroundColor(const Color& selectedColor) override;
    void SetCaretColor(const Color& color) override;
    void SetOnEditingChange(std::function<void(const bool&)>&& func) override;
    void SetOnWillChange(std::function<bool(const RichEditorChangeValue&)>&& func) override;
    void SetOnDidChange(std::function<void(const std::list<RichEditorAbstractSpanResult>&)>&& func) override;
    void SetOnCut(std::function<void(NG::TextCommonEvent&)>&& func) override;
    void SetOnCopy(std::function<void(NG::TextCommonEvent&)>&& func) override;

    static void SetTextDetectEnable(FrameNode* frameNode, bool value);
    static void SetCopyOption(FrameNode* frameNode, CopyOptions& copyOptions);
    static void SetCaretColor(FrameNode* frameNode, const Color& color);
    static void SetSelectedBackgroundColor(FrameNode* frameNode, const Color& selectedColor);
    void SetEnterKeyType(TextInputAction value) override;
    void SetOnSubmit(std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& func) override;

private:
    void SetDraggable(bool draggable);
    bool isStyledStringMode_ = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_MODEL_NG_H
