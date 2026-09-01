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

#include "core/components_ng/pattern/text_field/text_field_foreground_modifier.h"

#include "core/components_ng/pattern/common_text/counter_constants.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {

TextFieldForegroundModifier::TextFieldForegroundModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern)
    : CounterForegroundModifier(pattern) {}

void TextFieldForegroundModifier::onDraw(DrawingContext& context)
{
    auto textFieldPattern = DynamicCast<TextFieldPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(textFieldPattern);
    auto paintProperty = textFieldPattern->GetPaintProperty<TextFieldPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    CHECK_NULL_VOID(paintProperty->HasInnerBorderColor());
    CHECK_NULL_VOID(innerBorderWidth_);

    auto host = textFieldPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = textFieldPattern->GetLayoutProperty<TextFieldLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto& canvas = context.canvas;
    RSPen pen;
    pen.SetColor(paintProperty->GetInnerBorderColorValue(Color()).GetValue());
    auto width = GetInnerBorderWidth();
    pen.SetWidth(width);
    pen.SetAntiAlias(true);
    auto textFrameRect = textFieldPattern->GetFrameRect();
    auto rsRadius = MakeRRadius(renderContext->GetBorderRadius().value_or(BorderRadiusProperty()), width);
    auto offset = width / COUNTER_BORDER_OFFSET;
    RSRoundRect rrect(
        RSRect(offset, offset, textFrameRect.Width() - offset,
            textFrameRect.Height() - offset),
        rsRadius);
    canvas.AttachPen(pen);
    canvas.DrawRoundRect(rrect);
    canvas.DetachPen();
}
} // namespace OHOS::Ace::NG
