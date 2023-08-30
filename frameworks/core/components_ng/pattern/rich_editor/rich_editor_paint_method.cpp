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

#include "core/components_ng/pattern/rich_editor/rich_editor_paint_method.h"

#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_overlay_modifier.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/text/text_content_modifier.h"
#include "core/components_ng/pattern/text/text_overlay_modifier.h"

namespace OHOS::Ace::NG {
RichEditorPaintMethod::RichEditorPaintMethod(const WeakPtr<Pattern>& pattern, const ParagraphManager* pManager,
    float baselineOffset, const RefPtr<TextContentModifier>& cModifier,
    const RefPtr<TextOverlayModifier>& oModifier)
    : TextPaintMethod(pattern, pManager->GetParagraphs().begin()->paragraph, baselineOffset, cModifier, oModifier),
      pManager_(pManager)
{}

void RichEditorPaintMethod::UpdateOverlayModifier(PaintWrapper* paintWrapper)
{
    TextPaintMethod::UpdateOverlayModifier(paintWrapper);
    auto richEditorPattern = DynamicCast<RichEditorPattern>(GetPattern().Upgrade());
    CHECK_NULL_VOID(richEditorPattern);
    auto oModifier = DynamicCast<RichEditorOverlayModifier>(GetOverlayModifier(paintWrapper));
    if (!richEditorPattern->HasFocus()) {
        oModifier->SetCaretVisible(false);
        return;
    }
    auto caretVisible = richEditorPattern->GetCaretVisible();
    oModifier->SetCaretVisible(caretVisible);
    oModifier->SetCaretColor(Color::BLUE.GetValue());
    oModifier->SetCaretWidth(static_cast<float>(Dimension(CARET_WIDTH, DimensionUnit::VP).ConvertToPx()));
    if (richEditorPattern->GetTextContentLength() > 0) {
        float caretHeight = 0;
        OffsetF caretOffset =
            richEditorPattern->CalcCursorOffsetByPosition(richEditorPattern->GetCaretPosition(), caretHeight);
        oModifier->SetCaretOffsetAndHeight(caretOffset, caretHeight);
    } else {
        auto rect = richEditorPattern->GetTextContentRect();
        oModifier->SetCaretOffsetAndHeight(
            OffsetF(rect.GetX(), rect.GetY()), Dimension(DEFAULT_CARET_HEIGHT, DimensionUnit::VP).ConvertToPx());
    }
    std::vector<Rect> selectedRects;
    const auto& selection = richEditorPattern->GetTextSelector();
    if (richEditorPattern->GetTextContentLength() > 0 && selection.GetTextStart() != selection.GetTextEnd()) {
        selectedRects = pManager_->GetRects(selection.GetTextStart(), selection.GetTextEnd());
    }
    auto contentRect = richEditorPattern->GetTextContentRect();
    oModifier->SetContentRect(contentRect);
    oModifier->SetSelectedRects(selectedRects);
}

void RichEditorPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    auto cModifier = DynamicCast<RichEditorContentModifier>(GetContentModifier(paintWrapper));
    CHECK_NULL_VOID(cModifier);
    TextPaintMethod::UpdateContentModifier(paintWrapper);
}
} // namespace OHOS::Ace::NG
