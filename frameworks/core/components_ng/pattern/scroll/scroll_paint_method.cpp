/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/node_arc_scroll_bar_modifier.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "core/components_ng/render/render_context.h"

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

void ScrollPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    UpdateFadingGradient(renderContext);
    TryContentClip(paintWrapper);
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
    if (scrollBar2d_.Upgrade()) {
        UpdateOverlayModifier2d(paintWrapper);
        return;
    }
    CHECK_NULL_VOID(paintWrapper);
    auto scrollBarOverlayModifier = scrollBarOverlayModifier_.Upgrade();
    CHECK_NULL_VOID(scrollBarOverlayModifier);
    auto scrollBar = scrollBar_.Upgrade();
    CHECK_NULL_VOID(scrollBar);
    if (scrollBar->GetPositionModeUpdate()) {
        scrollBarOverlayModifier->SetPositionMode(scrollBar->GetPositionMode());
    }
    auto shapeMode = scrollBar->GetShapeMode();
    if (shapeMode == ShapeMode::ROUND) {
        bool updated = false;
        auto* mod = NodeModifier::GetArcScrollBarCustomModifier();
        CHECK_NULL_VOID(mod);
        CHECK_NULL_VOID(mod->updateArcScrollBarOverlay);
        mod->updateArcScrollBarOverlay(AceType::RawPtr(scrollBarOverlayModifier), AceType::RawPtr(scrollBar), updated);
        if (!updated) {
            return;
        }
    } else {
        scrollBarOverlayModifier->SetNeedPaintTrack(scrollBar->GetUseInnerScrollBar());
        scrollBarOverlayModifier->SetTrackRect(scrollBar->GetTrackRect());
        scrollBarOverlayModifier->SetTrackColor(scrollBar->GetBackgroundColor());
        scrollBarOverlayModifier->SetBarColor(scrollBar->GetForegroundColor());
        scrollBarOverlayModifier->StartBarAnimation(scrollBar->GetHoverAnimationType(),
            scrollBar->GetOpacityAnimationType(), scrollBar->GetNeedAdaptAnimation(), scrollBar->GetActiveRect());
    }
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    scrollBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
}

void ScrollPaintMethod::UpdateOverlayModifier2d(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    const auto scrollBar = scrollBar2d_.Upgrade();
    CHECK_NULL_VOID(scrollBar);
    auto&& overlay = scrollBar->GetPainter();
    CHECK_NULL_VOID(overlay);
    overlay->UpdateFrom(*scrollBar);
    scrollBar->ResetAnimationSignals();
}
} // namespace OHOS::Ace::NG
