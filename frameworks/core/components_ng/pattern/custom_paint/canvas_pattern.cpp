/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/custom_paint/canvas_pattern.h"

#include "drawing/engine_adapter/skia_adapter/skia_canvas.h"
#include "interfaces/inner_api/ace/ai/image_analyzer.h"

#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/common/ai/image_analyzer_manager.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/custom_paint/canvas_paint_op.h"
#include "core/components_ng/pattern/custom_paint/canvas_paint_method.h"
#include "core/components_ng/pattern/custom_paint/offscreen_canvas_pattern.h"
#include "core/components_ng/pattern/custom_paint/canvas_modifier.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "base/log/dump_log.h"

namespace {} // namespace

namespace OHOS::Ace::NG {
class RosenRenderContext;
CanvasPattern::~CanvasPattern()
{
    if (IsSupportImageAnalyzerFeature()) {
        ReleaseImageAnalyzer();
    }
}

void CanvasPattern::OnAttachToFrameNode()
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
        contentModifier_ = AceType::MakeRefPtr<CanvasModifier>();
    }
    paintMethod_ = MakeRefPtr<CanvasPaintMethod>(context, contentModifier_, host);
}

RefPtr<NodePaintMethod> CanvasPattern::CreateNodePaintMethod()
{
    return paintMethod_;
}

bool CanvasPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    bool pixelGridRoundSizeChange = false;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    SizeF currentPixelGridRoundSize = geometryNode->GetPixelGridRoundSize();
    pixelGridRoundSizeChange = currentPixelGridRoundSize != dirtyPixelGridRoundSize_;
    dirtyPixelGridRoundSize_ = currentPixelGridRoundSize;
    lastDirtyPixelGridRoundSize_ = dirtyPixelGridRoundSize_;

    if (config.skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }
    auto canvasEventHub = GetEventHub<CanvasEventHub>();
    CHECK_NULL_RETURN(canvasEventHub, false);

    if ((isCanvasInit_ == true) && (config.frameSizeChange || config.contentSizeChange)) {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            isCanvasInit_ = !pixelGridRoundSizeChange;
        } else {
            isCanvasInit_ = false;
        }
    } else if ((isCanvasInit_ == true) && (config.frameOffsetChange || config.contentOffsetChange)) {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            isCanvasInit_ = true;
        } else {
            isCanvasInit_ = false;
        }
    }

    if (IsSupportImageAnalyzerFeature() && imageAnalyzerManager_) {
        imageAnalyzerManager_->UpdateAnalyzerUIConfig(geometryNode);
    }

    if (!isCanvasInit_) {
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, false);
        CHECK_NULL_RETURN(contentModifier_, false);
        contentModifier_->needResetSurface_ = true;
        contentModifier_->renderContext_ = renderContext;

        auto context = PipelineContext::GetCurrentContext();
        if (context) {
            context->AddAfterLayoutTask([canvasEventHub]() {
                    canvasEventHub->FireReadyEvent();
                });
        }
        isCanvasInit_ = true;
        return context != nullptr;
    }
    return false;
}

void CanvasPattern::SetAntiAlias(bool isEnabled)
{
    auto task = [isEnabled](CanvasPaintMethod& paintMethod) {
        paintMethod.SetAntiAlias(isEnabled);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::FillRect(const Rect& rect)
{
#ifndef USE_FAST_TASKPOOL
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'fillRect(%{public}s)' is being executed.", rect.ToString().c_str());
    auto task = [rect](CanvasPaintMethod& paintMethod) {
        paintMethod.FillRect(rect);
    };
    paintMethod_->PushTask(task);
#else
    CHECK_NULL_VOID(paintMethod_->fastTaskPool_);
    paintMethod_->fastTaskPool_->FillRect(rect);
#endif
}

void CanvasPattern::StrokeRect(const Rect& rect)
{
    auto task = [rect](CanvasPaintMethod& paintMethod) {
        paintMethod.StrokeRect(rect);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::ClearRect(const Rect& rect)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'clearRect(%{public}s)' is being executed.", rect.ToString().c_str());
    auto task = [rect](CanvasPaintMethod& paintMethod) {
        paintMethod.ClearRect(rect);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::Fill()
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'fill' is pending execution.");
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Fill();
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::Fill(const RefPtr<CanvasPath2D>& path)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'fill' whit path is pending execution.");
    auto task = [path](CanvasPaintMethod& paintMethod) {
        paintMethod.Fill(path);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::Stroke()
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'stroke' is pending execution.");
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Stroke();
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::Stroke(const RefPtr<CanvasPath2D>& path)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'stroke' whit path is pending execution.");
    auto task = [path](CanvasPaintMethod& paintMethod) {
        paintMethod.Stroke(path);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::Clip()
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'clip' is pending execution.");
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Clip();
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::Clip(const RefPtr<CanvasPath2D>& path)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'clip' whit path is pending execution.");
    auto task = [path](CanvasPaintMethod& paintMethod) {
        paintMethod.Clip(path);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::BeginPath()
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'beginPath' is pending execution.");
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.BeginPath();
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::ClosePath()
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'closePath' is pending execution.");
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.ClosePath();
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::MoveTo(double x, double y)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'moveTo(%{public}lf, %{public}lf)' is pending execution.", x, y);
    auto task = [x, y](CanvasPaintMethod& paintMethod) {
        paintMethod.MoveTo(x, y);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::LineTo(double x, double y)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'lineTo(%{public}lf, %{public}lf)' is pending execution.", x, y);
    auto task = [x, y](CanvasPaintMethod& paintMethod) {
        paintMethod.LineTo(x, y);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::Arc(const ArcParam& param)
{
    auto task = [param](CanvasPaintMethod& paintMethod) {
        paintMethod.Arc(param);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::ArcTo(const ArcToParam& param)
{
    auto task = [param](CanvasPaintMethod& paintMethod) {
        paintMethod.ArcTo(param);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::AddRect(const Rect& rect)
{
    auto task = [rect](CanvasPaintMethod& paintMethod) {
        paintMethod.AddRect(rect);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::Ellipse(const EllipseParam& param)
{
    auto task = [param](CanvasPaintMethod& paintMethod) {
        paintMethod.Ellipse(param);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::BezierCurveTo(const BezierCurveParam& param)
{
#ifndef USE_FAST_TASKPOOL
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'bezierCurveTo' is pending execution.");
    auto task = [param](CanvasPaintMethod& paintMethod) {
        paintMethod.BezierCurveTo(param);
    };
    paintMethod_->PushTask(task);
#else
    CHECK_NULL_VOID(paintMethod_->fastTaskPool_);
    paintMethod_->fastTaskPool_->BezierCurveTo(param);
#endif
}

void CanvasPattern::QuadraticCurveTo(const QuadraticCurveParam& param)
{
    auto task = [param](CanvasPaintMethod& paintMethod) {
        paintMethod.QuadraticCurveTo(param);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::FillText(const std::string& text, double x, double y, std::optional<double> maxWidth)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [text, x, y, maxWidth](CanvasPaintMethod& paintMethod) {
        paintMethod.FillText(text, x, y, maxWidth);
    };
    paintMethod_->PushTask(task);
#else
    CHECK_NULL_VOID(paintMethod_->fastTaskPool_);
    paintMethod_->fastTaskPool_->FillText(text, x, y, maxWidth);
#endif
}

void CanvasPattern::StrokeText(const std::string& text, double x, double y, std::optional<double> maxWidth)
{
    auto task = [text, x, y, maxWidth](CanvasPaintMethod& paintMethod) {
        paintMethod.StrokeText(text, x, y, maxWidth);
    };
    paintMethod_->PushTask(task);
}

double CanvasPattern::MeasureText(const std::string& text, const PaintState& state)
{
    return paintMethod_->MeasureText(text, state);
}

double CanvasPattern::MeasureTextHeight(const std::string& text, const PaintState& state)
{
    return paintMethod_->MeasureTextHeight(text, state);
}

TextMetrics CanvasPattern::MeasureTextMetrics(const std::string& text, const PaintState& state)
{
    return paintMethod_->MeasureTextMetrics(text, state);
}

void CanvasPattern::DrawImage(const Ace::CanvasImage& image, double width, double height)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'drawImage(%{public}f, %{public}f)' is being executed.", width, height);
    auto task = [image, width, height](CanvasPaintMethod& paintMethod) {
        paintMethod.DrawImage(image, width, height);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::DrawSvgImage(
    RefPtr<SvgDomBase> svgDom, const Ace::CanvasImage& image, const ImageFit& imageFit)
{
    auto task = [svgDom, image, imageFit](CanvasPaintMethod& paintMethod) {
        paintMethod.DrawSvgImage(svgDom, image, imageFit);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& image)
{
    auto task = [pixelMap, image](CanvasPaintMethod& paintMethod) {
        paintMethod.DrawPixelMap(pixelMap, image);
    };
    paintMethod_->PushTask(task);
}

std::unique_ptr<Ace::ImageData> CanvasPattern::GetImageData(double left, double top, double width, double height)
{
    TAG_LOGD(
        AceLogTag::ACE_CANVAS, "Area: [%{public}lf, %{public}lf, %{public}lf, %{public}lf].", left, top, width, height);
    if (!paintMethod_) {
        std::unique_ptr<Ace::ImageData> data = std::make_unique<Ace::ImageData>();
        data->dirtyWidth = width;
        data->dirtyHeight = height;
        return data;
    }
    // Rely on the single-threaded model. Should guarantee the timing between Render Task of pipeline and GetImageData
    if (paintMethod_->HasTask()) {
        paintMethod_->FlushUITasks();
    }
    auto host = GetHost();
    if (!host) {
        return paintMethod_->GetImageData(nullptr, left, top, width, height);
    }
    auto rosenRenderContext = AceType::DynamicCast<RosenRenderContext>(host->GetRenderContext());
    return paintMethod_->GetImageData(rosenRenderContext, left, top, width, height);
}

void CanvasPattern::GetImageData(const std::shared_ptr<Ace::ImageData>& imageData)
{
    CHECK_NULL_VOID(paintMethod_);
    if (paintMethod_->HasTask()) {
        paintMethod_->FlushUITasks();
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    paintMethod_->GetImageData(renderContext, imageData);
}

void CanvasPattern::PutImageData(const Ace::ImageData& imageData)
{
    auto task = [imageData](CanvasPaintMethod& paintMethod) {
        paintMethod.PutImageData(imageData);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::TransferFromImageBitmap(const RefPtr<OffscreenCanvasPattern>& offscreenCanvasPattern)
{
    auto task = [offscreenCanvasPattern](CanvasPaintMethod& paintMethod) {
        paintMethod.TransferFromImageBitmap(offscreenCanvasPattern);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::CloseImageBitmap(const std::string& src)
{
    paintMethod_->CloseImageBitmap(src);
}

void CanvasPattern::UpdateGlobalAlpha(double alpha)
{
    auto task = [alpha](CanvasPaintMethod& paintMethod) {
        paintMethod.SetAlpha(alpha);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateCompositeOperation(CompositeOperation type)
{
    auto task = [type](CanvasPaintMethod& paintMethod) {
        paintMethod.SetCompositeType(type);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateSmoothingEnabled(bool enabled)
{
    auto task = [enabled](CanvasPaintMethod& paintMethod) {
        paintMethod.SetSmoothingEnabled(enabled);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateSmoothingQuality(const std::string& quality)
{
    auto task = [quality](CanvasPaintMethod& paintMethod) {
        paintMethod.SetSmoothingQuality(quality);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateLineCap(LineCapStyle cap)
{
    auto task = [cap](CanvasPaintMethod& paintMethod) {
        paintMethod.SetLineCap(cap);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateLineDashOffset(double dash)
{
    auto task = [dash](CanvasPaintMethod& paintMethod) {
        paintMethod.SetLineDashOffset(dash);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateLineJoin(LineJoinStyle join)
{
    auto task = [join](CanvasPaintMethod& paintMethod) {
        paintMethod.SetLineJoin(join);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateLineWidth(double width)
{
    auto task = [width](CanvasPaintMethod& paintMethod) {
        paintMethod.SetLineWidth(width);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateMiterLimit(double limit)
{
    auto task = [limit](CanvasPaintMethod& paintMethod) {
        paintMethod.SetMiterLimit(limit);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateShadowBlur(double blur)
{
    auto task = [blur](CanvasPaintMethod& paintMethod) {
        paintMethod.SetShadowBlur(blur);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateShadowColor(const Color& color)
{
    auto task = [color](CanvasPaintMethod& paintMethod) {
        paintMethod.SetShadowColor(color);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateShadowOffsetX(double offsetX)
{
    auto task = [offsetX](CanvasPaintMethod& paintMethod) {
        paintMethod.SetShadowOffsetX(offsetX);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateShadowOffsetY(double offsetY)
{
    auto task = [offsetY](CanvasPaintMethod& paintMethod) {
        paintMethod.SetShadowOffsetY(offsetY);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateTextAlign(TextAlign align)
{
    auto task = [align](CanvasPaintMethod& paintMethod) {
        paintMethod.SetTextAlign(align);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateTextBaseline(TextBaseline baseline)
{
    auto task = [baseline](CanvasPaintMethod& paintMethod) {
        paintMethod.SetTextBaseline(baseline);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateStrokePattern(const std::weak_ptr<Ace::Pattern>& pattern)
{
    auto task = [pattern](CanvasPaintMethod& paintMethod) {
        paintMethod.SetStrokePatternNG(pattern);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateStrokeColor(const Color& color)
{
    auto task = [color](CanvasPaintMethod& paintMethod) {
        paintMethod.SetStrokeColor(color);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateStrokeGradient(const Ace::Gradient& grad)
{
    auto task = [grad](CanvasPaintMethod& paintMethod) {
        paintMethod.SetStrokeGradient(grad);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateFontWeight(FontWeight weight)
{
    auto task = [weight](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFontWeight(weight);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateFontStyle(FontStyle style)
{
    auto task = [style](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFontStyle(style);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateFontFamilies(const std::vector<std::string>& families)
{
    auto task = [families](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFontFamilies(families);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateFontSize(const Dimension& size)
{
    auto task = [size](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFontSize(size);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateFillColor(const Color& color)
{
    auto task = [color](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFillColor(color);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateFillGradient(const Ace::Gradient& gradient)
{
    auto task = [gradient](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFillGradient(gradient);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateFillPattern(const std::weak_ptr<Ace::Pattern>& pattern)
{
    auto task = [pattern](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFillPatternNG(pattern);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateFillRuleForPath(const CanvasFillRule rule)
{
    auto task = [rule](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFillRuleForPath(rule);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::UpdateFillRuleForPath2D(const CanvasFillRule rule)
{
    auto task = [rule](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFillRuleForPath2D(rule);
    };
    paintMethod_->PushTask(task);
}

LineDashParam CanvasPattern::GetLineDash() const
{
    return paintMethod_->GetLineDash();
}

void CanvasPattern::UpdateLineDash(const std::vector<double>& segments)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'setLineDash' with %{public}zu parameters is executed.", segments.size());
    auto task = [segments](CanvasPaintMethod& paintMethod) {
        paintMethod.SetLineDash(segments);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::Save()
{
#ifndef USE_FAST_TASKPOOL
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'save' is pending execution.");
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Save();
    };
    paintMethod_->PushTask(task);
#else
    CHECK_NULL_VOID(paintMethod_->fastTaskPool_);
    paintMethod_->fastTaskPool_->Save();
#endif
    paintMethod_->SaveMatrix();
}

void CanvasPattern::Restore()
{
#ifndef USE_FAST_TASKPOOL
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'restore' is pending execution.");
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Restore();
    };
    paintMethod_->PushTask(task);
#else
    CHECK_NULL_VOID(paintMethod_->fastTaskPool_);
    paintMethod_->fastTaskPool_->Restore();
#endif

    paintMethod_->RestoreMatrix();
}

void CanvasPattern::Scale(double x, double y)
{
    auto task = [x, y](CanvasPaintMethod& paintMethod) {
        paintMethod.Scale(x, y);
    };
    paintMethod_->PushTask(task);
    paintMethod_->ScaleMatrix(x, y);
}

void CanvasPattern::Rotate(double angle)
{
    auto task = [angle](CanvasPaintMethod& paintMethod) {
        paintMethod.Rotate(angle);
    };
    paintMethod_->PushTask(task);
    paintMethod_->RotateMatrix(angle);
}

void CanvasPattern::SetTransform(const TransformParam& param)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'setTransform' is pending execution.");
    auto task = [param](CanvasPaintMethod& paintMethod) {
        paintMethod.SetTransform(param);
    };
    paintMethod_->PushTask(task);
    paintMethod_->SetTransformMatrix(param);
}

void CanvasPattern::ResetTransform()
{
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.ResetTransform();
    };
    paintMethod_->PushTask(task);
    paintMethod_->ResetTransformMatrix();
}

void CanvasPattern::Transform(const TransformParam& param)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'transform' is pending execution.");
    auto task = [param](CanvasPaintMethod& paintMethod) {
        paintMethod.Transform(param);
    };
    paintMethod_->PushTask(task);
    paintMethod_->TransformMatrix(param);
}

void CanvasPattern::Translate(double x, double y)
{
    auto task = [x, y](CanvasPaintMethod& paintMethod) {
        paintMethod.Translate(x, y);
    };
    paintMethod_->PushTask(task);
    paintMethod_->TranslateMatrix(x, y);
}

std::string CanvasPattern::ToDataURL(const std::string& args)
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

std::string CanvasPattern::GetJsonData(const std::string& path)
{
    return paintMethod_->GetJsonData(path);
}

double CanvasPattern::GetWidth()
{
    CHECK_NULL_RETURN(canvasSize_, 0.0);
    return canvasSize_->Width();
}

double CanvasPattern::GetHeight()
{
    CHECK_NULL_RETURN(canvasSize_, 0.0);
    return canvasSize_->Height();
}

void CanvasPattern::SetRSCanvasCallback(std::function<void(RSCanvas*, double, double)>& callback)
{
    paintMethod_->SetRSCanvasCallback(callback);
}

void CanvasPattern::SetInvalidate()
{
    auto task = [](CanvasPaintMethod& paintMethod) {};
    paintMethod_->PushTask(task);
}

void CanvasPattern::SetTextDirection(TextDirection direction)
{
    currentSetTextDirection_ = direction;
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
    auto task = [direction](CanvasPaintMethod& paintMethod) {
        paintMethod.SetTextDirection(direction);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::SetFilterParam(const std::string& filterStr)
{
    auto task = [filterStr](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFilterParam(filterStr);
    };
    paintMethod_->PushTask(task);
}

TransformParam CanvasPattern::GetTransform() const
{
    return paintMethod_->GetTransform();
}

void CanvasPattern::SaveLayer()
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'SaveLayer' is being executed.");
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.SaveLayer();
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::RestoreLayer()
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "The 'RestoreLayer' is being executed.");
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.RestoreLayer();
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::OnPixelRoundFinish(const SizeF& pixelGridRoundSize)
{
    CHECK_NULL_VOID(paintMethod_);
    paintMethod_->UpdateRecordingCanvas(pixelGridRoundSize.Width(), pixelGridRoundSize.Height());
}

void CanvasPattern::EnableAnalyzer(bool enable)
{
    isEnableAnalyzer_ = enable;
    if (!isEnableAnalyzer_) {
        DestroyAnalyzerOverlay();
        return;
    }

    if (imageAnalyzerManager_) {
        return;
    }

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    imageAnalyzerManager_ = std::make_shared<ImageAnalyzerManager>(host, ImageAnalyzerHolder::CANVAS);
    CHECK_NULL_VOID(imageAnalyzerManager_);

    CHECK_NULL_VOID(paintMethod_);
    paintMethod_->SetOnModifierUpdateFunc([weak = WeakClaim(this)] () -> void {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->DestroyAnalyzerOverlay();
    });
}

void CanvasPattern::StartImageAnalyzer(void* config, onAnalyzedCallback& onAnalyzed)
{
    if (!IsSupportImageAnalyzerFeature()) {
        CHECK_NULL_VOID(onAnalyzed);
        (onAnalyzed.value())(ImageAnalyzerState::UNSUPPORTED);
        return;
    }

    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->SetImageAnalyzerConfig(config);
    imageAnalyzerManager_->SetImageAnalyzerCallback(onAnalyzed);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask([weak = WeakClaim(this)] {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->CreateAnalyzerOverlay();
    }, "ArkUICanvasStartImageAnalyzer");
}

void CanvasPattern::StopImageAnalyzer()
{
    DestroyAnalyzerOverlay();
}

bool CanvasPattern::IsSupportImageAnalyzerFeature()
{
    return isEnableAnalyzer_ && imageAnalyzerManager_ && imageAnalyzerManager_->IsSupportImageAnalyzerFeature();
}

void CanvasPattern::CreateAnalyzerOverlay()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto pixelMap = context->GetThumbnailPixelMap();
    CHECK_NULL_VOID(pixelMap);
    if (IsSupportImageAnalyzerFeature()) {
        CHECK_NULL_VOID(imageAnalyzerManager_);
        imageAnalyzerManager_->CreateAnalyzerOverlay(pixelMap);
    }
}

void CanvasPattern::UpdateAnalyzerOverlay()
{
    auto context = GetHost()->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto pixelMap = context->GetThumbnailPixelMap();
    CHECK_NULL_VOID(pixelMap);
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->UpdateAnalyzerOverlay(pixelMap);
}

void CanvasPattern::DestroyAnalyzerOverlay()
{
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->DestroyAnalyzerOverlay();
}

void CanvasPattern::ReleaseImageAnalyzer()
{
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->ReleaseImageAnalyzer();
}

void CanvasPattern::DumpAdvanceInfo()
{
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        DumpLog::GetInstance().AddDesc(
            std::string("PixelGridRoundSize: ")
                .append(dirtyPixelGridRoundSize_.ToString())
                .append(", lase PixelGridRoundSize: ")
                .append(lastDirtyPixelGridRoundSize_.ToString()));
    } else {
        DumpLog::GetInstance().AddDesc(
            std::string("contentSizeChange: ").append(recordConfig_.contentSizeChange ? "true" : "false"));
        DumpLog::GetInstance().AddDesc(
            std::string("frameSizeChange: ").append(recordConfig_.frameSizeChange ? "true" : "false"));
        DumpLog::GetInstance().AddDesc(
            std::string("frameOffsetChange: ").append(recordConfig_.frameOffsetChange ? "true" : "false"));
        DumpLog::GetInstance().AddDesc(
            std::string("contentOffsetChange: ").append(recordConfig_.contentOffsetChange ? "true" : "false"));
    }
    DumpLog::GetInstance().AddDesc(contentModifier_->GetDumpInfo());
}

void CanvasPattern::Reset()
{
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Reset();
    };
    paintMethod_->PushTask(task);
    paintMethod_->ResetTransformMatrix();
}

void CanvasPattern::OnLanguageConfigurationUpdate()
{
    UpdateTextDefaultDirection();
}

void CanvasPattern::OnModifyDone()
{
    UpdateTextDefaultDirection();
}

void CanvasPattern::UpdateTextDefaultDirection()
{
    if (currentSetTextDirection_ != TextDirection::INHERIT) {
        return;
    }
    SetTextDirection(TextDirection::INHERIT);
}
} // namespace OHOS::Ace::NG
