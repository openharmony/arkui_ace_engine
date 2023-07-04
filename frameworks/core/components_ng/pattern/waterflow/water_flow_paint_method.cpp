/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/waterflow/water_flow_paint_method.h"

#include "core/components_ng/pattern/scroll/inner/scroll_bar_painter.h"

namespace OHOS::Ace::NG {
void WaterFlowPaintMethod::PaintScrollBar(RSCanvas& canvas)
{
    auto scrollBar = scrollBar_.Upgrade();
    CHECK_NULL_VOID_NOLOG(scrollBar);
    if (scrollBar->NeedPaint()) {
        ScrollBarPainter::PaintRectBar(canvas, scrollBar);
    }
}

void WaterFlowPaintMethod::PaintEdgeEffect(PaintWrapper* paintWrapper, RSCanvas& canvas)
{
    auto edgeEffect = edgeEffect_.Upgrade();
    CHECK_NULL_VOID_NOLOG(edgeEffect);
    CHECK_NULL_VOID(paintWrapper);
    auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    edgeEffect->Paint(canvas, frameSize, { 0.0f, 0.0f });
}

CanvasDrawFunction WaterFlowPaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto painter = weak.Upgrade();
        CHECK_NULL_VOID(painter);
        painter->PaintScrollBar(canvas);
        painter->PaintEdgeEffect(paintWrapper, canvas);
    };
    return paintFunc;
}

void WaterFlowPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(contentModifier_);
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    auto frameSize = geometryNode->GetPaddingSize();
    OffsetF paddingOffset = geometryNode->GetPaddingOffset() - geometryNode->GetFrameOffset();
    auto renderContext = paintWrapper->GetRenderContext();
    bool clip = !renderContext || renderContext->GetClipEdge().value_or(true);
    contentModifier_->SetClipOffset(paddingOffset);
    contentModifier_->SetClipSize(frameSize);
    contentModifier_->SetClip(clip);
}
} // namespace OHOS::Ace::NG