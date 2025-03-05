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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_CONTROLLER_H

#include <functional>
#include <utility>

#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"
#include "core/components_ng/pattern/text_field/text_field_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT TextFieldController : public TextFieldControllerBase {
    DECLARE_ACE_TYPE(TextFieldController, TextFieldControllerBase);

public:
    void SetPattern(const WeakPtr<Pattern>& pattern)
    {
        pattern_ = pattern;
    }

    void Focus(bool focus) override;
    void ShowError(const std::string& errorText) override;
    void Delete() override;
    void Insert(const std::string& args) override;
    void CaretPosition(int32_t caretPosition) override;
    int32_t GetCaretIndex() override;
    NG::OffsetF GetCaretPosition() override;
    void SetTextSelection(int32_t selectionStart, int32_t selectionEnd,
        const std::optional<SelectionOptions>& options = std::nullopt) override;
    Rect GetTextContentRect() override;
    int32_t GetTextContentLinesNum() override;
    void StopEditing() override;

    void SetPasswordState(bool flag) override;

    int32_t AddText(std::u16string text, int32_t offset) override;
    void DeleteText(int32_t start, int32_t end) override;
    void ClearPreviewText() override;
    SelectionInfo GetSelection() override;
private:
    WeakPtr<Pattern> pattern_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TEXT_FIELD_TEXT_FIELD_CONTROLLER_H
