/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_BASE_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_BASE_CONTROLLER_H

#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/text/layout_info_interface.h"

namespace OHOS::Ace::NG {
class RichEditorPattern;

class ACE_EXPORT RichEditorBaseController : virtual public RichEditorBaseControllerBase {
    DECLARE_ACE_TYPE(RichEditorBaseController, RichEditorBaseControllerBase);

public:
    void SetPattern(const WeakPtr<RichEditorPattern>& pattern);
    int32_t GetCaretOffset() override;
    RectF GetCaretRect() override;
    bool SetCaretOffset(int32_t caretPosition) override;
    void SetTypingStyle(std::optional<struct UpdateSpanStyle> typingStyle, std::optional<TextStyle> textStyle) override;
    void SetTypingParagraphStyle(std::optional<struct UpdateParagraphStyle> typingParagraphStyle) override;
    std::optional<struct UpdateSpanStyle> GetTypingStyle() override;
    void CloseSelectionMenu() override;
    bool IsEditing() override;
    void StopEditing() override;
    void SetSelection(int32_t selectionStart, int32_t selectionEnd,
        const std::optional<SelectionOptions>& options = std::nullopt, bool isForward = false) override;
    WeakPtr<LayoutInfoInterface> GetLayoutInfoInterface() override;
    const PreviewTextInfo GetPreviewTextInfo() const override;
    ColorMode GetColorMode() override;
    RefPtr<NG::RichEditorTheme> GetTheme() override;
protected:
    WeakPtr<RichEditorPattern> pattern_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RICH_EDITOR_RICH_EDITOR_BASE_CONTROLLER_H