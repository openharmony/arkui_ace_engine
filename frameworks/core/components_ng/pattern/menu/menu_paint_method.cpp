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

#include "core/components_ng/pattern/menu/menu_paint_method.h"

#include "base/utils/utils.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/render/canvas_image.h"

namespace OHOS::Ace::NG {

CanvasDrawFunction MenuPaintMethod::GetOverlayDrawFunction(PaintWrapper* paintWrapper)
{
    return [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto menu = weak.Upgrade();
        if (menu) {
            // paint background
            RSBrush brush;
            Color bgColor(DEFAULT_BACKGROUND_COLOR);
            brush.SetARGB(bgColor.GetRed(), bgColor.GetGreen(), bgColor.GetBlue(), bgColor.GetAlpha());
            canvas.AttachBrush(brush);

            auto size = paintWrapper->GetGeometryNode()->GetContentSize();
            RSRect rect(0.0, 0.0, size.Width(), size.Height());
            canvas.DrawRect(rect);

            // if using scroll, paint top and bottom gradients
        }
    };
}

void MenuPaintMethod::PaintGradient(RSCanvas& canvas, PaintWrapper* paintWrapper, bool isTop)
{
    CHECK_NULL_VOID(paintWrapper);
    auto menuSize = paintWrapper->GetGeometryNode()->GetFrameSize();

    // create gradientRect
    const double outPadding = OUT_PADDING.ConvertToPx();
    const double gradientHeight = GRADIENT_HEIGHT.ConvertToPx();
    LOGI("GRADIENT_HEIGHT = %{public}f px", gradientHeight);
    auto yPos = isTop ? outPadding : menuSize.Height() - gradientHeight;
    RSRect gradientRect(outPadding, yPos, menuSize.Width() - outPadding, gradientHeight);
    LOGI("gradientRect = (%{public}f, %{public}f) - (%{public}f, %{public}f)", gradientRect.GetLeft(),
        gradientRect.GetTop(), gradientRect.GetRight(), gradientRect.GetBottom());

    RSBrush brush;
    RSPoint startPt(gradientRect.GetLeft(), gradientRect.GetTop());
    RSPoint endPt(gradientRect.GetLeft(), gradientRect.GetBottom());
    std::vector<RSColorQuad> colors(2);
    if (isTop) {
        colors[0] = Color::FromRGB(13, 13, 13).ChangeAlpha(GRADIENT_END_GRADIENT).GetValue();
        colors[1] = Color(DEFAULT_BACKGROUND_COLOR).ChangeAlpha(0).GetValue();
    } else {
        colors[0] = Color(DEFAULT_BACKGROUND_COLOR).GetValue();
        colors[1] = Color::FromRGB(13, 13, 13).ChangeAlpha(GRADIENT_END_GRADIENT).GetValue();
    }
    std::vector<float> pos { 0.0f, 0.85f };

    brush.SetShaderEffect(RSShaderEffect::CreateLinearGradient(startPt, endPt, colors, pos, RSTileMode::MIRROR));
    canvas.AttachBrush(brush);
    canvas.DrawRect(gradientRect);
}

} // namespace OHOS::Ace::NG