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

#include "customizeview_content_modifier.h"

#include "2d_graphics/include/draw/canvas.h"
#include "2d_graphics/include/draw/color.h"
#include "2d_graphics/include/draw/pen.h"

#include "hilog/log.h"
#include "hilog/log_c.h"
constexpr uint32_t ACE_DOMAIN = 0xD003900;

namespace OHOS::Customize {
using RSPen = Rosen::Drawing::Pen;
using RSCanvas = Rosen::Drawing::Canvas;
using RSColor = Rosen::Drawing::Color;

void CustomizeViewContentModifier::OnDraw(Ace::Kit::DrawingContext* context)
{
    HiLogPrint(LOG_CORE, LOG_INFO, ACE_DOMAIN, "Custimize", "CustomizeViewContentModifier::OnDraw %{public}f %{public}f", context->width, context->height);
    RSCanvas* canvas = context->canvas;
    RSPen pen;
    pen.SetWidth(5);
    pen.SetColor(RSColor::COLOR_CYAN);
    canvas->AttachPen(pen);
    canvas->DrawCircle({ context->width / 2, context->height / 2 }, context->width < context->height ? context->width / 2 - 10 : context->height / 2 - 10);
    canvas->DetachPen();
}
} // namespace OHOS::Customize
