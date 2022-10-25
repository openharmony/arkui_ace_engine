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

#include "core/components_ng/pattern/scroll/scroll_paint_method.h"

#include "base/utils/utils.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar_painter.h"
#include "core/components_ng/pattern/scroll/scroll_paint_property.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace::NG {

CanvasDrawFunction ScrollPaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto scroll = weak.Upgrade();
        if (scroll) {
            scroll->PaintScrollBar(canvas, paintWrapper);
        }
    };

    return paintFunc;
}

void ScrollPaintMethod::PaintScrollBar(RSCanvas& canvas, PaintWrapper* paintWrapper) const
{
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<ScrollPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);

    auto scrollBar = paintProperty->GetScrollBar();
    CHECK_NULL_VOID(scrollBar);
    if (!scrollBar->NeedScrollBar()) {
        return;
    }

    auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    paintProperty->UpdateScrollBarRegion(frameSize);
    ScrollBarPainter::PaintRectBar(canvas, scrollBar, UINT8_MAX);
    if (scrollBar->GetFirstLoad()) {
        scrollBar->SetFirstLoad(false);
    }
}

} // namespace OHOS::Ace::NG
