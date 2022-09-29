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

void CustomPaintPattern::Fill()
{
    auto task = [](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Fill(paintWrapper);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Fill(const RefPtr<CanvasPath2D>& path)
{
    auto task = [path](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Fill(paintWrapper, path);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Stroke()
{
    auto task = [](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Stroke(paintWrapper);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Stroke(const RefPtr<CanvasPath2D>& path)
{
    auto task = [path](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Stroke(paintWrapper, path);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::BeginPath()
{
    auto task = [](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.BeginPath();
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::ClosePath()
{
    auto task = [](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.ClosePath();
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::MoveTo(double x, double y)
{
    auto task = [x, y](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.MoveTo(paintWrapper, x, y);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::LineTo(double x, double y)
{
    auto task = [x, y](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.LineTo(paintWrapper, x, y);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Arc(const ArcParam& param)
{
    auto task = [param](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Arc(paintWrapper, param);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::ArcTo(const ArcToParam& param)
{
    auto task = [param](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.ArcTo(paintWrapper, param);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::AddRect(const Rect& rect)
{
    auto task = [rect](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.AddRect(paintWrapper, rect);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Ellipse(const EllipseParam& param)
{
    auto task = [param](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Ellipse(paintWrapper, param);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::BezierCurveTo(const BezierCurveParam& param)
{
    auto task = [param](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.BezierCurveTo(paintWrapper, param);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::QuadraticCurveTo(const QuadraticCurveParam& param)
{
    auto task = [param](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.QuadraticCurveTo(paintWrapper, param);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::DrawImage(const Ace::CanvasImage& image, double width, double height)
{
    auto task = [image, width, height](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.DrawImage(paintWrapper, image, width, height);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& image)
{
    auto task = [pixelMap, image](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.DrawPixelMap(pixelMap, image);
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

void CustomPaintPattern::PutImageData(const Ace::ImageData& imageData)
{
    auto task = [imageData](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.PutImageData(paintWrapper, imageData);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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

void CustomPaintPattern::UpdateFillRuleForPath(const CanvasFillRule rule)
{
    auto task = [rule](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetFillRuleForPath(rule);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateFillRuleForPath2D(const CanvasFillRule rule)
{
    auto task = [rule](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetFillRuleForPath2D(rule);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}
} // namespace OHOS::Ace::NG
