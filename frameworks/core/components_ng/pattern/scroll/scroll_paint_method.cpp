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
#include "core/components_ng/pattern/scroll/inner/scroll_bar_overlay_modifier.h"
#include "core/components_ng/pattern/scroll/scroll_paint_property.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace::NG {

CanvasDrawFunction ScrollPaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto scroll = weak.Upgrade();
        CHECK_NULL_VOID(scroll);
        scroll->PaintScrollEffect(canvas, paintWrapper);
    };

    return paintFunc;
}

void ScrollPaintMethod::PaintScrollEffect(RSCanvas& canvas, PaintWrapper* paintWrapper) const
{
    auto scrollEdgeEffect = edgeEffect_.Upgrade();
    CHECK_NULL_VOID(scrollEdgeEffect);
    auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    scrollEdgeEffect->Paint(canvas, frameSize, { 0.0f, 0.0f });
}

void ScrollPaintMethod::UpdateOverlayModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto scrollBarOverlayModifier = scrollBarOverlayModifier_.Upgrade();
    CHECK_NULL_VOID(scrollBarOverlayModifier);
    auto scrollBar = scrollBar_.Upgrade();
    if (!scrollBar || !scrollBar->NeedPaint()) {
        return;
    }
    OffsetF fgOffset(scrollBar->GetActiveRect().Left(), scrollBar->GetActiveRect().Top());
    scrollBarOverlayModifier->StartBarAnimation(scrollBar->GetHoverAnimationType(),
        scrollBar->GetOpacityAnimationType(), scrollBar->GetNeedAdaptAnimation(), scrollBar->GetActiveRect());
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    scrollBarOverlayModifier->SetBarColor(scrollBar->GetForegroundColor());
    scrollBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
}
} // namespace OHOS::Ace::NG
