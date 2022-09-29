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
constexpr Dimension CURSOR_PADDING = 4.0_vp;
} // namespace

CanvasDrawFunction TextFieldPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_RETURN(textFieldPattern, nullptr);
    CHECK_NULL_RETURN(textFieldPattern->GetParagraph(), nullptr);
    auto offset = paintWrapper->GetContentOffset();
    auto paintOffset = offset - OffsetF(-static_cast<float>(textFieldPattern->GetBasicPadding()),
                                    textFieldPattern->GetBaseLineOffset());
    return [paragraph = textFieldPattern->GetParagraph(), paintOffset](
               RSCanvas& canvas) { paragraph->Paint(&canvas, paintOffset.GetX(), paintOffset.GetY()); };
}

CanvasDrawFunction TextFieldPaintMethod::GetOverlayDrawFunction(PaintWrapper* paintWrapper)
{
    return [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto textField = weak.Upgrade();
        if (textField) {
            textField->PaintCursor(canvas, paintWrapper);
        }
    };
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
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto cursorColor = paintProperty->GetCursorColorValue();
    canvas.Save();
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(cursorColor.GetValue());
    canvas.AttachBrush(brush);
    auto top = static_cast<float>(paintWrapper->GetContentOffset().GetY() + CURSOR_PADDING.ConvertToPx());
    if (textFieldPattern->DisplayPlaceHolder()) {
        canvas.DrawRect(RSRect(textFieldPattern->GetBasicPadding(), paintWrapper->GetContentOffset().GetY(),
            textFieldPattern->GetBasicPadding() + CURSOR_WIDTH.ConvertToPx(),
            top + paragraph->GetHeight() + CURSOR_PADDING.ConvertToPx()));
    } else {
        auto cursorOffsetX = textFieldPattern->GetCaretOffsetX() + textFieldPattern->GetBasicPadding();
        canvas.DrawRect(RSRect(cursorOffsetX, CURSOR_PADDING.ConvertToPx(), cursorOffsetX + CURSOR_WIDTH.ConvertToPx(),
            paragraph->GetHeight() + top));
    }
    canvas.Restore();
}

} // namespace OHOS::Ace::NG
