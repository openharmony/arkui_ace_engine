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

#include "core/components_ng/pattern/custom_paint/custom_paint_pattern.h"

#include "drawing/engine_adapter/skia_adapter/skia_canvas.h"

#include "core/components_ng/pattern/custom_paint/canvas_paint_method.h"
#include "core/components_ng/pattern/custom_paint/offscreen_canvas_pattern.h"

namespace OHOS::Ace::NG {
void CustomPaintPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    paintMethod_ = MakeRefPtr<CanvasPaintMethod>(context);
}

RefPtr<NodePaintMethod> CustomPaintPattern::CreateNodePaintMethod()
{
    return paintMethod_;
}

bool CustomPaintPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto customPaintEventHub = GetEventHub<CustomPaintEventHub>();
    CHECK_NULL_RETURN(customPaintEventHub, true);
    customPaintEventHub->FireReadyEvent();
    return true;
}

void CustomPaintPattern::FillRect(const Rect& rect)
{
    auto task = [rect](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.FillRect(paintWrapper, rect);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::StrokeRect(const Rect& rect)
{
    auto task = [rect](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.StrokeRect(paintWrapper, rect);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

std::unique_ptr<Ace::ImageData> CustomPaintPattern::GetImageData(double left, double top, double width, double height)
{
    if (!paintMethod_) {
        std::unique_ptr<Ace::ImageData> data = std::make_unique<Ace::ImageData>();
        data->dirtyWidth = width;
        data->dirtyHeight = height;
        return data;
    }
    return paintMethod_->GetImageData(left, top, width, height);
}

void CustomPaintPattern::TransferFromImageBitmap(const RefPtr<OffscreenCanvasPattern>& offscreenCanvasPattern)
{
    auto task = [offscreenCanvasPattern](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.TransferFromImageBitmap(offscreenCanvasPattern);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateFillColor(const Color& color)
{
    paintMethod_->SetFillColor(color);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}
} // namespace OHOS::Ace::NG
