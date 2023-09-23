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

#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/custom_paint/canvas_paint_method.h"
#include "core/components_ng/pattern/custom_paint/offscreen_canvas_pattern.h"
#include "core/components_ng/pattern/custom_paint/rendering_context2d_modifier.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace {} // namespace

namespace OHOS::Ace::NG {
class RosenRenderContext;
void CustomPaintPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderCtx = host->GetRenderContext();
    renderCtx->SetClipToBounds(false);
    renderCtx->SetUsingContentRectForRenderFrame(true);
    renderCtx->SetFrameGravity(OHOS::Rosen::Gravity::RESIZE_ASPECT_FILL);
    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(context);

    if (!contentModifier_) {
        contentModifier_ =
            AceType::MakeRefPtr<RenderingContext2DModifier>();
    }
    paintMethod_ = MakeRefPtr<CanvasPaintMethod>(context, contentModifier_);
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
    CHECK_NULL_RETURN(customPaintEventHub, false);

    if (config.contentSizeChange || config.frameSizeChange) {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            isCanvasInit_ = !config.frameSizeChange;
        } else {
            isCanvasInit_ = false;
        }
    } else if (config.frameOffsetChange || config.contentOffsetChange) {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            isCanvasInit_ = true;
        } else {
            isCanvasInit_ = false;
        }
    }

    if (!isCanvasInit_) {
        customPaintEventHub->FireReadyEvent();
        isCanvasInit_ = true;
        return true;
    }
    return false;
}

void CustomPaintPattern::SetAntiAlias(bool isEnabled)
{
    auto task = [isEnabled](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetAntiAlias(isEnabled);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::FillRect(const Rect& rect)
{
    auto task = [rect](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.FillRect(paintWrapper, rect);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::StrokeRect(const Rect& rect)
{
    auto task = [rect](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.StrokeRect(paintWrapper, rect);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::ClearRect(const Rect& rect)
{
    auto task = [rect](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.ClearRect(paintWrapper, rect);
    };
    paintMethod_->PushTask(task);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Fill()
{
    auto task = [](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Fill(paintWrapper);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Fill(const RefPtr<CanvasPath2D>& path)
{
    auto task = [path](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Fill(paintWrapper, path);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Stroke()
{
    auto task = [](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Stroke(paintWrapper);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Stroke(const RefPtr<CanvasPath2D>& path)
{
    auto task = [path](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Stroke(paintWrapper, path);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Clip()
{
    auto task = [](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Clip();
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Clip(const RefPtr<CanvasPath2D>& path)
{
    auto task = [path](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Clip(path);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::BeginPath()
{
    auto task = [](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.BeginPath();
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::ClosePath()
{
    auto task = [](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.ClosePath();
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::MoveTo(double x, double y)
{
    auto task = [x, y](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.MoveTo(paintWrapper, x, y);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::LineTo(double x, double y)
{
    auto task = [x, y](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.LineTo(paintWrapper, x, y);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Arc(const ArcParam& param)
{
    auto task = [param](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Arc(paintWrapper, param);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::ArcTo(const ArcToParam& param)
{
    auto task = [param](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.ArcTo(paintWrapper, param);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::AddRect(const Rect& rect)
{
    auto task = [rect](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.AddRect(paintWrapper, rect);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Ellipse(const EllipseParam& param)
{
    auto task = [param](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Ellipse(paintWrapper, param);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::BezierCurveTo(const BezierCurveParam& param)
{
    auto task = [param](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.BezierCurveTo(paintWrapper, param);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::QuadraticCurveTo(const QuadraticCurveParam& param)
{
    auto task = [param](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.QuadraticCurveTo(paintWrapper, param);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::FillText(const std::string& text, double x, double y, std::optional<double> maxWidth)
{
    auto task = [text, x, y, maxWidth](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.FillText(paintWrapper, text, x, y, maxWidth);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::StrokeText(const std::string& text, double x, double y, std::optional<double> maxWidth)
{
    auto task = [text, x, y, maxWidth](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.StrokeText(paintWrapper, text, x, y, maxWidth);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

double CustomPaintPattern::MeasureText(const std::string& text, const PaintState& state)
{
    return paintMethod_->MeasureText(text, state);
}

double CustomPaintPattern::MeasureTextHeight(const std::string& text, const PaintState& state)
{
    return paintMethod_->MeasureTextHeight(text, state);
}

TextMetrics CustomPaintPattern::MeasureTextMetrics(const std::string& text, const PaintState& state)
{
    return paintMethod_->MeasureTextMetrics(text, state);
}

void CustomPaintPattern::DrawImage(const Ace::CanvasImage& image, double width, double height)
{
    auto task = [image, width, height](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.DrawImage(paintWrapper, image, width, height);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& image)
{
    auto task = [pixelMap, image](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.DrawPixelMap(pixelMap, image);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
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
    // Rely on the single-threaded model. Should guarantee the timing between Render Task of pipeline and GetImageData
    if (paintMethod_->HasTask()) {
        paintMethod_->FlushPipelineImmediately();
    }
    auto host = GetHost();
    if (!host) {
        return paintMethod_->GetImageData(nullptr, left, top, width, height);
    }
    auto rosenRenderContext = AceType::DynamicCast<RosenRenderContext>(host->GetRenderContext());
    return paintMethod_->GetImageData(rosenRenderContext, left, top, width, height);
}

void CustomPaintPattern::GetImageData(const std::shared_ptr<Ace::ImageData>& imageData)
{
    CHECK_NULL_VOID(paintMethod_);
    if (paintMethod_->HasTask()) {
        paintMethod_->FlushPipelineImmediately();
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    paintMethod_->GetImageData(renderContext, imageData);
}

void CustomPaintPattern::PutImageData(const Ace::ImageData& imageData)
{
    auto task = [imageData](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.PutImageData(paintWrapper, imageData);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::TransferFromImageBitmap(const RefPtr<OffscreenCanvasPattern>& offscreenCanvasPattern)
{
    auto task = [offscreenCanvasPattern](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.TransferFromImageBitmap(paintWrapper, offscreenCanvasPattern);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::CloseImageBitmap(const std::string& src)
{
    paintMethod_->CloseImageBitmap(src);
}

void CustomPaintPattern::UpdateGlobalAlpha(double alpha)
{
    auto task = [alpha](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetAlpha(alpha);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateCompositeOperation(CompositeOperation type)
{
    auto task = [type](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetCompositeType(type);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateSmoothingEnabled(bool enabled)
{
    auto task = [enabled](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetSmoothingEnabled(enabled);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateSmoothingQuality(const std::string& quality)
{
    auto task = [quality](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetSmoothingQuality(quality);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateLineCap(LineCapStyle cap)
{
    auto task = [cap](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetLineCap(cap);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateLineDashOffset(double dash)
{
    auto task = [dash](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetLineDashOffset(dash);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateLineJoin(LineJoinStyle join)
{
    auto task = [join](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetLineJoin(join);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateLineWidth(double width)
{
    auto task = [width](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetLineWidth(width);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateMiterLimit(double limit)
{
    auto task = [limit](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetMiterLimit(limit);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateShadowBlur(double blur)
{
    auto task = [blur](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetShadowBlur(blur);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateShadowColor(const Color& color)
{
    auto task = [color](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetShadowColor(color);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateShadowOffsetX(double offsetX)
{
    auto task = [offsetX](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetShadowOffsetX(offsetX);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateShadowOffsetY(double offsetY)
{
    auto task = [offsetY](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetShadowOffsetY(offsetY);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateTextAlign(TextAlign align)
{
    auto task = [align](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetTextAlign(align);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateTextBaseline(TextBaseline baseline)
{
    auto task = [baseline](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetTextBaseline(baseline);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateStrokePattern(const std::weak_ptr<Ace::Pattern>& pattern)
{
    auto task = [pattern](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetStrokePatternNG(pattern);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateStrokeColor(const Color& color)
{
    auto task = [color](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetStrokeColor(color);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateStrokeGradient(const Ace::Gradient& grad)
{
    auto task = [grad](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetStrokeGradient(grad);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateFontWeight(FontWeight weight)
{
    auto task = [weight](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetFontWeight(weight);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateFontStyle(FontStyle style)
{
    auto task = [style](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetFontStyle(style);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateFontFamilies(const std::vector<std::string>& families)
{
    auto task = [families](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetFontFamilies(families);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateFontSize(const Dimension& size)
{
    auto task = [size](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetFontSize(size);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateFillColor(const Color& color)
{
    auto task = [color](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetFillColor(color);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateFillGradient(const Ace::Gradient& gradient)
{
    auto task = [gradient](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetFillGradient(gradient);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateFillPattern(const std::weak_ptr<Ace::Pattern>& pattern)
{
    auto task = [pattern](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetFillPatternNG(pattern);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateFillRuleForPath(const CanvasFillRule rule)
{
    auto task = [rule](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetFillRuleForPath(rule);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::UpdateFillRuleForPath2D(const CanvasFillRule rule)
{
    auto task = [rule](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetFillRuleForPath2D(rule);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

LineDashParam CustomPaintPattern::GetLineDash() const
{
    return paintMethod_->GetLineDash();
}

void CustomPaintPattern::UpdateLineDash(const std::vector<double>& segments)
{
    auto task = [segments](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetLineDash(segments);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Save()
{
    auto task = [](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Save();
    };
    paintMethod_->PushTask(task);
    paintMethod_->SaveMatrix();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Restore()
{
    auto task = [](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Restore();
    };
    paintMethod_->PushTask(task);
    paintMethod_->RestoreMatrix();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Scale(double x, double y)
{
    auto task = [x, y](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Scale(x, y);
    };
    paintMethod_->PushTask(task);
    paintMethod_->ScaleMatrix(x, y);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Rotate(double angle)
{
    auto task = [angle](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Rotate(angle);
    };
    paintMethod_->PushTask(task);
    paintMethod_->RotateMatrix(angle);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::SetTransform(const TransformParam& param)
{
    auto task = [param](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetTransform(param);
    };
    paintMethod_->PushTask(task);
    paintMethod_->SetTransformMatrix(param);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::ResetTransform()
{
    auto task = [](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.ResetTransform();
    };
    paintMethod_->PushTask(task);
    paintMethod_->ResetTransformMatrix();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Transform(const TransformParam& param)
{
    auto task = [param](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Transform(param);
    };
    paintMethod_->PushTask(task);
    paintMethod_->TransformMatrix(param);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::Translate(double x, double y)
{
    auto task = [x, y](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.Translate(x, y);
    };
    paintMethod_->PushTask(task);
    paintMethod_->TranslateMatrix(x, y);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

std::string CustomPaintPattern::ToDataURL(const std::string& args)
{
    // Rely on the single-threaded model. Should guarantee the timing between Render Task of pipeline and ToDataURL
    if (paintMethod_->HasTask()) {
        paintMethod_->FlushPipelineImmediately();
    }
    auto host = GetHost();
    if (!host) {
        return paintMethod_->ToDataURL(nullptr, args);
    }
    auto rosenRenderContext = AceType::DynamicCast<RosenRenderContext>(host->GetRenderContext());
    return paintMethod_->ToDataURL(rosenRenderContext, args);
}

std::string CustomPaintPattern::GetJsonData(const std::string& path)
{
    return paintMethod_->GetJsonData(path);
}

double CustomPaintPattern::GetWidth()
{
    CHECK_NULL_RETURN(canvasSize_, 0.0);
    return canvasSize_->Width();
}

double CustomPaintPattern::GetHeight()
{
    CHECK_NULL_RETURN(canvasSize_, 0.0);
    return canvasSize_->Height();
}

void CustomPaintPattern::SetTextDirection(TextDirection direction)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<LayoutProperty>();
    auto directionCommon = layoutProperty->GetLayoutDirection();
    if (directionCommon == TextDirection::AUTO) {
        directionCommon = AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR;
    }
    if (direction == TextDirection::INHERIT) {
        direction = directionCommon;
    }
    auto task = [direction](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetTextDirection(direction);
    };
    paintMethod_->PushTask(task);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CustomPaintPattern::SetFilterParam(const std::string& filterStr)
{
    auto task = [filterStr](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.SetFilterParam(filterStr);
    };
    paintMethod_->PushTask(task);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

TransformParam CustomPaintPattern::GetTransform() const
{
    return paintMethod_->GetTransform();
}
} // namespace OHOS::Ace::NG
