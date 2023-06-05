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

#include "core/components_ng/pattern/scroll/inner/scroll_bar_painter.h"

#include <cmath>

#include "base/utils/utils.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {

constexpr double FULL_ALPHA = 255.0;
constexpr float HALF = 0.5f;

} // namespace

void ScrollBarPainter::PaintRectBar(RSCanvas& canvas, const RefPtr<ScrollBar>& scrollBar)
{
    Rect activeRect = scrollBar->GetActiveRect();
    Rect barRect = scrollBar->GetBarRect();
    uint8_t opacity = scrollBar->GetOpacity();
    if (!NearZero(activeRect.Height()) && !NearZero(barRect.Height())) {
        RSBrush brush;
        brush.SetBlendMode(RSBlendMode::SRC_OVER);
        brush.SetAntiAlias(true);

        RSRect bgRect(barRect.Left(), barRect.Top(), barRect.Right(), barRect.Bottom());
        RSColor bgColor = ToRSColor(scrollBar->GetBackgroundColor());
        brush.SetColor(bgColor);
        double filletRadius = bgRect.GetWidth() * HALF;
        canvas.AttachBrush(brush);
        canvas.DrawRoundRect({ bgRect, filletRadius, filletRadius });
        canvas.DetachBrush();

        RSRect fgRect(activeRect.Left(), activeRect.Top(), activeRect.Right(), activeRect.Bottom());
        RSColor fgColor = ToRSColor(scrollBar->GetForegroundColor().BlendOpacity(opacity / FULL_ALPHA));
        brush.SetColor(fgColor);
        canvas.AttachBrush(brush);
        canvas.DrawRoundRect({ fgRect, filletRadius, filletRadius });
    }
}

} // namespace OHOS::Ace::NG
