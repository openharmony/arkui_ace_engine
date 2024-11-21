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

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/render/drawing_forward.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t OFFESET_VALUE = 2;
}
TextFieldForegroundModifier::TextFieldForegroundModifier(const WeakPtr<OHOS::Ace::NG::Pattern>& pattern)
    : pattern_(pattern)
{
    innerBorderWidth_ = AceType::MakeRefPtr<PropertyFloat>(0.0f);
    AttachProperty(innerBorderWidth_);
}

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
    auto width = innerBorderWidth_->Get();
    pen.SetWidth(width);
    pen.SetAntiAlias(true);
    auto textFrameRect = textFieldPattern->GetFrameRect();
    auto rsRadius = MakeRRadius(renderContext->GetBorderRadius().value_or(BorderRadiusProperty()), width);
    RSRoundRect rrect(
        RSRect(width / OFFESET_VALUE, width / OFFESET_VALUE, textFrameRect.Width() - width / OFFESET_VALUE,
            textFrameRect.Height() - width / OFFESET_VALUE),
        rsRadius);
    canvas.AttachPen(pen);
    canvas.DrawRoundRect(rrect);
    canvas.DetachPen();
}

std::vector<RSPoint> TextFieldForegroundModifier::MakeRRadius(
    const BorderRadiusProperty& border, float borderWidth) const
{
    std::vector<RSPoint> rectRadii;
    rectRadii.resize(RSRoundRect::CORNER_NUMBER);
    auto topLeft = static_cast<float>(border.radiusTopLeft.value_or(Dimension()).ConvertToPx()) - borderWidth;
    rectRadii[RSRoundRect::TOP_LEFT_POS] = RSPoint(topLeft, topLeft);
    auto topRight = static_cast<float>(border.radiusTopRight.value_or(Dimension()).ConvertToPx()) - borderWidth;
    rectRadii[RSRoundRect::TOP_RIGHT_POS] = RSPoint(topRight, topRight);
    auto bottomRight = static_cast<float>(border.radiusBottomRight.value_or(Dimension()).ConvertToPx()) - borderWidth;
    rectRadii[RSRoundRect::BOTTOM_RIGHT_POS] = RSPoint(bottomRight, bottomRight);
    auto bottomLeft = static_cast<float>(border.radiusBottomLeft.value_or(Dimension()).ConvertToPx()) - borderWidth;
    rectRadii[RSRoundRect::BOTTOM_LEFT_POS] = RSPoint(bottomLeft, bottomLeft);
    return rectRadii;
}
} // namespace OHOS::Ace::NG