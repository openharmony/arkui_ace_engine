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

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float CARET_WIDTH = 1.5f;
constexpr float DEFAULT_CARET_HEIGHT = 18.5f;
} // namespace
RichEditorPaintMethod::RichEditorPaintMethod(const WeakPtr<Pattern>& pattern, RefPtr<Paragraph> paragraph,
    float baselineOffset, RefPtr<RichEditorContentModifier> richEditorContentModifier,
    RefPtr<RichEditorOverlayModifier> richEditorOverlayModifier)
    : TextPaintMethod(pattern, paragraph, baselineOffset, richEditorContentModifier, richEditorOverlayModifier),
      pattern_(pattern), paragraph_(std::move(paragraph)), richEditorOverlayModifier_(richEditorOverlayModifier)
{}
RichEditorPaintMethod::~RichEditorPaintMethod() = default;

void RichEditorPaintMethod::UpdateOverlayModifier(PaintWrapper* paintWrapper)
{
    TextPaintMethod::UpdateOverlayModifier(paintWrapper);
    auto richEditorPattern = DynamicCast<RichEditorPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(richEditorPattern);
    auto caretVisible = richEditorPattern->GetCaretVisible();
    richEditorOverlayModifier_->SetCaretVisible(caretVisible);
    richEditorOverlayModifier_->SetCaretColor(Color::BLUE.GetValue());
    richEditorOverlayModifier_->SetCaretWidth(
        static_cast<float>(Dimension(CARET_WIDTH, DimensionUnit::VP).ConvertToPx()));
    if (richEditorPattern->GetTextContentLength() > 0) {
        float caretHeight = 0;
        OffsetF caretOffset =
            richEditorPattern->CalcCursorOffsetByPosition(richEditorPattern->GetCaretPosition(), caretHeight);
        richEditorOverlayModifier_->SetCaretOffsetAndHeight(caretOffset, caretHeight);
    } else {
        auto rect = richEditorPattern->GetTextContentRect();
        richEditorOverlayModifier_->SetCaretOffsetAndHeight(
            OffsetF(rect.GetX(), rect.GetY()), Dimension(DEFAULT_CARET_HEIGHT, DimensionUnit::VP).ConvertToPx());
    }
    std::vector<Rect> selectedRects;
    const auto& selection = richEditorPattern->GetTextSelector();
    if (richEditorPattern->GetTextContentLength() > 0 && selection.GetTextStart() != selection.GetTextEnd()) {
        paragraph_->GetRectsForRange(selection.GetTextStart(), selection.GetTextEnd(), selectedRects);
    }
    auto contentRect = richEditorPattern->GetTextContentRect();
    richEditorOverlayModifier_->SetContentRect(contentRect);
    richEditorOverlayModifier_->SetSelectedRects(selectedRects);
}
} // namespace OHOS::Ace::NG
