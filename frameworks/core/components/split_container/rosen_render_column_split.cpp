/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components/split_container/rosen_render_column_split.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkPaint.h"
#else
#include "core/components_ng/render/drawing.h"
#endif

#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {

namespace {

constexpr uint32_t COLUMN_SPLIT_COLOR = 0xFF707B7C;

} // namespace

void RosenRenderColumnSplit::Paint(RenderContext& context, const Offset& offset)
{
    auto children = GetChildren();
    double dividerWidth = GetPaintRect().Width();
    int32_t index = 0;
    for (const auto& item : children) {
        if (!item->GetVisible()) {
            continue;
        }

        if (displayNodes_.find(item) == displayNodes_.end() &&
            disableHideNodes_.find(item) == disableHideNodes_.end()) {
            continue;
        }

        context.PaintChild(item, offset);
        if (index != 0) {
            PaintDivider(context, offset + item->GetPosition(), dividerWidth);
        }
        index++;
    }
}

void RosenRenderColumnSplit::PaintDivider(RenderContext& context, const Offset& offset, double width)
{
    double startPointX = offset.GetX();
    double startPointY = offset.GetY();
    double endPointX = startPointX + width;
    double endPointY = startPointY;
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
    paint.setColor(COLUMN_SPLIT_COLOR);
    paint.setStrokeWidth(DEFAULT_SPLIT_HEIGHT);
    canvas->drawLine(startPointX, startPointY, endPointX, endPointY, paint);
#else
    RSPen pen;
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
    pen.SetColor(COLUMN_SPLIT_COLOR);
    pen.SetWidth(DEFAULT_SPLIT_HEIGHT);
    canvas->AttachPen(pen);
    canvas->DrawLine(RSPoint(startPointX, startPointY), RSPoint(endPointX, endPointY));
    canvas->DetachPen();
#endif
}

} // namespace OHOS::Ace