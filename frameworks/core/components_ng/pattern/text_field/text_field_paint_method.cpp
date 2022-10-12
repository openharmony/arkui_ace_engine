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
#include "core/components_ng/pattern/text_field/text_field_paint_method.h"

#include <cmath>
#include <vector>

#include "foundation/graphic/graphic_2d/rosen/modules/2d_graphics/include/draw/path.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/rect.h"
#include "base/geometry/rrect.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/placement.h"
#include "core/components/popup/popup_theme.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension CURSOR_WIDTH = 1.5_vp;
constexpr Dimension CURSOR_PADDING = 2.0_vp;
} // namespace

CanvasDrawFunction TextFieldPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_RETURN(textFieldPattern, nullptr);
    CHECK_NULL_RETURN(textFieldPattern->GetParagraph(), nullptr);
    auto offset = paintWrapper->GetContentOffset();
    auto paintOffset = offset - OffsetF(-static_cast<float>(textFieldPattern->GetBasicPadding()),
                                    textFieldPattern->GetBaseLineOffset());
    auto drawFunction = [paragraph = textFieldPattern->GetParagraph(), paintOffset, textFieldPattern,
                            contentSize = paintWrapper->GetContentSize(),
                            contentOffset = paintWrapper->GetContentOffset()](RSCanvas& canvas) {
        RSRect clipInnerRect(paintOffset.GetX(), contentOffset.GetY(),
            paintOffset.GetX() + contentSize.Width() - textFieldPattern->GetBasicPadding() * 2.0f,
            contentOffset.GetY() + contentSize.Height());
        canvas.ClipRect(clipInnerRect, RSClipOp::INTERSECT);
        paragraph->Paint(&canvas, paintOffset.GetX(), paintOffset.GetY());
    };
    return drawFunction;
}

CanvasDrawFunction TextFieldPaintMethod::GetOverlayDrawFunction(PaintWrapper* paintWrapper)
{
    return [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto textField = weak.Upgrade();
        if (textField) {
            textField->PaintCursor(canvas, paintWrapper);
            textField->PaintSelection(canvas, paintWrapper);
        }
    };
}

void TextFieldPaintMethod::PaintSelection(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    if (!textFieldPattern->InSelectMode()) {
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<TextFieldTheme>();
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(theme->GetSelectedColor().GetValue());
    canvas.AttachBrush(brush);
    auto startOffset =
        std::min(textFieldPattern->GetSelectionBaseOffsetX(), textFieldPattern->GetSelectionDestinationOffsetX());
    auto endOffset =
        std::max(textFieldPattern->GetSelectionBaseOffsetX(), textFieldPattern->GetSelectionDestinationOffsetX());
    startOffset += textFieldPattern->GetBasicPadding();
    endOffset += textFieldPattern->GetBasicPadding();
    canvas.DrawRect(RSRect(startOffset, paintWrapper->GetContentOffset().GetY(), endOffset,
        paintWrapper->GetContentOffset().GetY() + paintWrapper->GetContentSize().Height()));
    canvas.Restore();
}

void TextFieldPaintMethod::PaintCursor(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    if (!textFieldPattern->GetCursorVisible()) {
        return;
    }
    auto paragraph = textFieldPattern->GetParagraph();
    CHECK_NULL_VOID(paragraph);
    auto paintProperty = DynamicCast<TextFieldPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);

    auto cursorColor = paintProperty->GetCursorColorValue();
    canvas.Save();
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(cursorColor.GetValue());
    canvas.AttachBrush(brush);
    float caretHeight = textFieldPattern->GetTextOrPlaceHolderFontSize();
    caretHeight += static_cast<float>(CURSOR_PADDING.ConvertToPx()) * 2.0f;
    auto top = static_cast<float>(
        paintWrapper->GetContentOffset().GetY() + (paintWrapper->GetContentSize().Height() - caretHeight) / 2);
    auto textRectF = textFieldPattern->GetTextRect();
    auto textRect = RSRect(textRectF.GetX(), textRectF.GetY(), textRectF.GetX() + textRectF.Width(),
        textRectF.GetY() + textRectF.Height());
    auto cursorOffsetX = textFieldPattern->GetCaretOffsetX() + textFieldPattern->GetBasicPadding();
    canvas.DrawRect(
        RSRect(cursorOffsetX, top, cursorOffsetX + static_cast<float>(CURSOR_WIDTH.ConvertToPx()), top + caretHeight));
    canvas.Restore();
}

} // namespace OHOS::Ace::NG
