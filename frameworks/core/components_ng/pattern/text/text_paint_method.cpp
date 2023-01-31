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

#include "core/components_ng/pattern/text/text_paint_method.h"

#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
void TextPaintMethod::PaintSelection(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto textPattern = DynamicCast<TextPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textPattern);
    CHECK_NULL_VOID(paragraph_);
    const auto& selection = textPattern->GetTextSelector();
    auto textValue = textPattern->GetTextForDisplay();
    if (textValue.empty() || selection.GetStart() == selection.GetEnd()) {
        return;
    }
    std::vector<Rect> selectedRects;
    paragraph_->GetRectsForRange(selection.GetStart(), selection.GetEnd(), selectedRects);
    if (selectedRects.empty()) {
        return;
    }

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<TextTheme>();
    auto selectedColor = theme->GetSelectedColor().GetValue();

    canvas.Save();
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(selectedColor);
    canvas.AttachBrush(brush);

    auto offset = paintWrapper->GetContentOffset();
    auto textPaintOffset = offset - OffsetF(0.0, std::min(baselineOffset_, 0.0f));

    for (const auto& selectedRect : selectedRects) {
        canvas.DrawRect(
            RSRect(textPaintOffset.GetX() + selectedRect.Left(), textPaintOffset.GetY() + selectedRect.Top(),
                textPaintOffset.GetX() + selectedRect.Right(), textPaintOffset.GetY() + selectedRect.Bottom()));
    }
    canvas.DetachBrush();
    canvas.Restore();
}

CanvasDrawFunction TextPaintMethod::GetOverlayDrawFunction(PaintWrapper* paintWrapper)
{
    return [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto textPaint = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(textPaint);
        textPaint->PaintSelection(canvas, paintWrapper);
    };
}
} // namespace OHOS::Ace::NG