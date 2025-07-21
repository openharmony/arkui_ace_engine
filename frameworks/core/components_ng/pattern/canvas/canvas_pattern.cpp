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

#include "core/components_ng/pattern/canvas/canvas_pattern.h"

#include "interfaces/inner_api/ace/ai/image_analyzer.h"

#include "base/log/dump_log.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/common/ai/image_analyzer_manager.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/canvas/canvas_modifier.h"
#include "core/components_ng/pattern/canvas/canvas_paint_method.h"

namespace OHOS::Ace::NG {
CanvasPattern::~CanvasPattern()
{
    if (IsSupportImageAnalyzerFeature()) {
        ReleaseImageAnalyzer();
    }
}

void CanvasPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    ACE_SCOPED_TRACE("Canvas[%d] CanvasPattern::OnDetachFromFrameNode", frameNode->GetId());
    DetachRenderContext();
}

void CanvasPattern::AttachRenderContext()
{
    isAttached_ = true;
    FireOnContext2DAttach();
}

void CanvasPattern::DetachRenderContext()
{
    if (isAttached_) {
        isAttached_ = false;
        FireOnContext2DDetach();
    }
}

void CanvasPattern::OnAttachToMainTree()
{
    if (paintMethod_) {
        paintMethod_->SetHostCustomNodeName();
    }
}

void CanvasPattern::SetOnContext2DAttach(std::function<void()>&& callback)
{
    onContext2DAttach_ = std::move(callback);
}

void CanvasPattern::SetOnContext2DDetach(std::function<void()>&& callback)
{
    onContext2DDetach_ = std::move(callback);
}

void CanvasPattern::FireOnContext2DAttach()
{
    if (onContext2DAttach_) {
        onContext2DAttach_();
    }
}

void CanvasPattern::FireOnContext2DDetach()
{
    if (onContext2DDetach_) {
        onContext2DDetach_();
    }
}

void CanvasPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    id_ = host->GetId();
    ACE_SCOPED_TRACE("Canvas[%d] CanvasPattern::OnAttachToFrameNode", id_);
#ifndef ACE_UNITTEST
    auto renderCtx = host->GetRenderContext();
    renderCtx->SetClipToBounds(false);
    renderCtx->SetUsingContentRectForRenderFrame(true);
    renderCtx->SetFrameGravity(Rosen::Gravity::RESIZE_ASPECT_FILL);
    renderCtx->SetNeedUseCmdlistDrawRegion(true);
    if (!contentModifier_) {
        contentModifier_ = AceType::MakeRefPtr<CanvasModifier>();
    }
    paintMethod_ = MakeRefPtr<CanvasPaintMethod>(contentModifier_, host);
#endif
}

RefPtr<NodePaintMethod> CanvasPattern::CreateNodePaintMethod()
{
    return paintMethod_;
}

bool CanvasPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    ACE_SCOPED_TRACE("Canvas[%d] CanvasPattern::OnDirtyLayoutWrapperSwap", GetId());
    bool needReset = !(config.skipMeasure || dirty->SkipMeasureContent());
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, false);
    context->AddAfterLayoutTask([weak = WeakClaim(this), config, needReset]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->OnSizeChanged(config, needReset);
    });
    return true;
}

void CanvasPattern::OnSizeChanged(const DirtySwapConfig& config, bool needReset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    SizeF currentPixelGridRoundSize = geometryNode->GetPixelGridRoundSize();
    bool pixelGridRoundSizeChange = currentPixelGridRoundSize != dirtyPixelGridRoundSize_;
    lastDirtyPixelGridRoundSize_ = dirtyPixelGridRoundSize_;
    dirtyPixelGridRoundSize_ = currentPixelGridRoundSize;

    // Canvas is first time onReady && Visibility is None
    if (!needReset && (currentPixelGridRoundSize == SizeF { 0, 0 }) &&
        (lastDirtyPixelGridRoundSize_ == SizeF { -1, -1 })) {
        return;
    }
    // Visibility is None
    if (!needReset && (currentPixelGridRoundSize == SizeF { 0, 0 })) {
        CHECK_NULL_VOID(paintMethod_);
        paintMethod_->UpdateRecordingCanvas(currentPixelGridRoundSize.Width(), currentPixelGridRoundSize.Height());
        return;
    }
    // constraint is unchanged
    if (!needReset) {
        return;
    }

    needReset = config.frameSizeChange || config.contentSizeChange;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TEN)) {
        needReset = needReset && pixelGridRoundSizeChange;
    } else {
        needReset = needReset || config.frameOffsetChange || config.contentOffsetChange;
    }

    if (needReset) {
        if (IsSupportImageAnalyzerFeature()) {
            imageAnalyzerManager_->UpdateAnalyzerUIConfig(geometryNode);
        }
        auto renderContext = host->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        CHECK_NULL_VOID(contentModifier_);
        contentModifier_->SetNeedResetSurface();
        contentModifier_->SetRenderContext(renderContext);
        CHECK_NULL_VOID(paintMethod_);
        paintMethod_->UpdateRecordingCanvas(currentPixelGridRoundSize.Width(), currentPixelGridRoundSize.Height());
        auto canvasEventHub = GetOrCreateEventHub<CanvasEventHub>();
        CHECK_NULL_VOID(canvasEventHub);
        canvasEventHub->FireReadyEvent();
    }
}

void CanvasPattern::SetAntiAlias(bool isEnabled)
{
    CHECK_NULL_VOID(paintMethod_);
    auto task = [isEnabled](CanvasPaintMethod& paintMethod) {
        paintMethod.SetAntiAlias(isEnabled);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::FillRect(const Rect& rect)
{
    auto task = [rect](CanvasPaintMethod& paintMethod) {
        paintMethod.FillRect(rect);
    };
    paintMethod_->PushTask(task);
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
    auto task = [rect](CanvasPaintMethod& paintMethod) {
        paintMethod.ClearRect(rect);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::Fill()
{
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Fill();
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::Fill(const RefPtr<CanvasPath2D>& path)
{
    auto task = [path](CanvasPaintMethod& paintMethod) {
        paintMethod.Fill(path);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::Stroke()
{
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Stroke();
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::Stroke(const RefPtr<CanvasPath2D>& path)
{
    auto task = [path](CanvasPaintMethod& paintMethod) {
        paintMethod.Stroke(path);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::Clip()
{
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Clip();
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::Clip(const RefPtr<CanvasPath2D>& path)
{
    auto task = [path](CanvasPaintMethod& paintMethod) {
        paintMethod.Clip(path);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::BeginPath()
{
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.BeginPath();
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::ClosePath()
{
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.ClosePath();
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::MoveTo(double x, double y)
{
    auto task = [x, y](CanvasPaintMethod& paintMethod) {
        paintMethod.MoveTo(x, y);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::LineTo(double x, double y)
{
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

void CanvasPattern::AddRoundRect(const Rect& rect, const std::vector<double>& radii)
{
    auto task = [rect, radii](CanvasPaintMethod& paintMethod) {
        paintMethod.AddRoundRect(rect, radii);
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
    auto task = [param](CanvasPaintMethod& paintMethod) {
        paintMethod.BezierCurveTo(param);
    };
    paintMethod_->PushTask(task);
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
    auto task = [text, x, y, maxWidth](CanvasPaintMethod& paintMethod) {
        paintMethod.FillText(text, x, y, maxWidth);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::StrokeText(const std::string& text, double x, double y, std::optional<double> maxWidth)
{
    auto task = [text, x, y, maxWidth](CanvasPaintMethod& paintMethod) {
        paintMethod.StrokeText(text, x, y, maxWidth);
    };
    paintMethod_->PushTask(task);
}

TextMetrics CanvasPattern::MeasureTextMetrics(const std::string& text, const PaintState& state)
{
    return paintMethod_->MeasureTextMetrics(text, state);
}

void CanvasPattern::DrawImage(const Ace::CanvasImage& image, double width, double height)
{
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
    if (!paintMethod_) {
        std::unique_ptr<Ace::ImageData> data = std::make_unique<Ace::ImageData>();
        data->dirtyWidth = width;
        data->dirtyHeight = height;
        return data;
    }
    // Rely on the single-threaded model. Should guarantee the timing between Render Task of pipeline and GetImageData
    paintMethod_->FlushUITasks();
    return paintMethod_->GetImageData(left, top, width, height);
}

void CanvasPattern::GetImageData(const std::shared_ptr<Ace::ImageData>& imageData)
{
    CHECK_NULL_VOID(paintMethod_);
    paintMethod_->FlushUITasks();
    paintMethod_->GetImageData(imageData);
}

void CanvasPattern::PutImageData(const Ace::ImageData& imageData)
{
    auto task = [imageData](CanvasPaintMethod& paintMethod) {
        paintMethod.PutImageData(imageData);
    };
    paintMethod_->PushTask(task);
}

#ifdef PIXEL_MAP_SUPPORTED
void CanvasPattern::TransferFromImageBitmap(const RefPtr<PixelMap>& pixelMap)
{
    auto task = [pixelMap](CanvasPaintMethod& paintMethod) {
        paintMethod.TransferFromImageBitmap(pixelMap);
    };
    paintMethod_->PushTask(task);
}
#else
void CanvasPattern::TransferFromImageBitmap(const Ace::ImageData& imageData)
{
#ifndef ACE_UNITTEST
    auto task = [imageData](CanvasPaintMethod& paintMethod) {
        paintMethod.PutImageData(imageData);
    };
    paintMethod_->PushTask(task);
#endif
}
#endif

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
    CHECK_NULL_VOID(paintMethod_);
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

void CanvasPattern::SetStrokeGradient(const std::shared_ptr<Ace::Gradient>& gradient)
{
    CHECK_NULL_VOID(gradient);
    auto task = [gradientObj = *gradient](CanvasPaintMethod& paintMethod) {
        paintMethod.SetStrokeGradient(gradientObj);
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

void CanvasPattern::UpdateLetterSpacing(const Dimension& letterSpacing)
{
    auto task = [letterSpacing](CanvasPaintMethod& paintMethod) {
        paintMethod.SetLetterSpacing(letterSpacing);
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

void CanvasPattern::SetFillGradient(const std::shared_ptr<Ace::Gradient>& gradient)
{
    CHECK_NULL_VOID(gradient);
    auto task = [gradientObj = *gradient](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFillGradient(gradientObj);
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
    auto task = [segments](CanvasPaintMethod& paintMethod) {
        paintMethod.SetLineDash(segments);
    };
    paintMethod_->PushTask(task);
    paintMethod_->SetLineDashParam(segments);
}

void CanvasPattern::Save()
{
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Save();
    };
    paintMethod_->PushTask(task);
    paintMethod_->SaveProperties();
}

void CanvasPattern::Restore()
{
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Restore();
    };
    paintMethod_->PushTask(task);
    paintMethod_->RestoreProperties();
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

std::string CanvasPattern::ToDataURL(const std::string& type, double quality)
{
    // Rely on the single-threaded model. Should guarantee the timing between Render Task of pipeline and ToDataURL
    paintMethod_->FlushUITasks();
    return paintMethod_->ToDataURL(type, quality);
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
    CHECK_NULL_VOID(layoutProperty);
    auto directionCommon = layoutProperty->GetLayoutDirection();
    if (directionCommon == TextDirection::AUTO) {
        directionCommon = AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR;
    }
    if (direction == TextDirection::INHERIT) {
        direction = directionCommon;
    }
    CHECK_NULL_VOID(paintMethod_);
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
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.SaveLayer();
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::RestoreLayer()
{
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.RestoreLayer();
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::EnableAnalyzer(bool enable)
{
    isEnableAnalyzer_ = enable;
    if (!isEnableAnalyzer_) {
        DestroyAnalyzerOverlay();
        return;
    }

    CHECK_NULL_VOID(!imageAnalyzerManager_);
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

void CanvasPattern::SetImageAIOptions(void* options)
{
    if (!imageAnalyzerManager_) {
        imageAnalyzerManager_ = std::make_shared<ImageAnalyzerManager>(GetHost(), ImageAnalyzerHolder::CANVAS);
    }
    CHECK_NULL_VOID(imageAnalyzerManager_);
    imageAnalyzerManager_->SetImageAIOptions(options);
}

void CanvasPattern::StartImageAnalyzer(void* config, OnAnalyzedCallback& onAnalyzed)
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
    host->SetOverlayNode(nullptr);
    auto context = host->GetRenderContext();
    CHECK_NULL_VOID(context);
    auto pixelMap = context->GetThumbnailPixelMap();
    CHECK_NULL_VOID(pixelMap);
    if (IsSupportImageAnalyzerFeature()) {
        imageAnalyzerManager_->CreateAnalyzerOverlay(pixelMap);
    }
}

void CanvasPattern::UpdateAnalyzerOverlay()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetRenderContext();
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

void CanvasPattern::DumpInfo()
{
    CHECK_NULL_VOID(paintMethod_);
    DumpLog::GetInstance().AddDesc(paintMethod_->GetDumpInfo());
    CHECK_NULL_VOID(contentModifier_);
    DumpLog::GetInstance().AddDesc(contentModifier_->GetDumpInfo());
}

void CanvasPattern::Reset()
{
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Reset();
    };
    paintMethod_->PushTask(task);
    paintMethod_->ResetTransformMatrix();
    paintMethod_->ResetLineDash();
    SetTextDirection(TextDirection::INHERIT);
}

void CanvasPattern::SetTransform(std::shared_ptr<Ace::Pattern> pattern, const TransformParam& transform)
{
    auto task = [pattern, transform](CanvasPaintMethod& paintMethod) {
        paintMethod.SetTransform(pattern, transform);
    };
    paintMethod_->PushTask(task);
}

void CanvasPattern::OnLanguageConfigurationUpdate()
{
    UpdateTextDefaultDirection();
}

void CanvasPattern::OnModifyDone()
{
    Pattern::CheckLocalized();
    UpdateTextDefaultDirection();
}

void CanvasPattern::UpdateTextDefaultDirection()
{
    if (currentSetTextDirection_ != TextDirection::INHERIT) {
        return;
    }
    SetTextDirection(TextDirection::INHERIT);
}

void CanvasPattern::SetDensity(double density)
{
    paintMethod_->SetDensity(density);
}

int32_t CanvasPattern::GetId()
{
    return id_;
}

void CanvasPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(paintMethod_);
    json->Put("CanvasPaint", paintMethod_->GetDumpInfo().c_str());
    CHECK_NULL_VOID(contentModifier_);
    json->Put("CanvasModifier", contentModifier_->GetDumpInfo().c_str());
}

void CanvasPattern::DumpSimplifyInfo(std::shared_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(paintMethod_);
    auto jsonMethod = JsonUtil::Create();
    paintMethod_->GetSimplifyDumpInfo(jsonMethod);
    json->PutRef("CanvasPaint", std::move(jsonMethod));
    CHECK_NULL_VOID(contentModifier_);
    auto arrayModifier = JsonUtil::Create();
    contentModifier_->GetSimplifyDumpInfo(arrayModifier);
    json->PutRef("CanvasModifier", std::move(arrayModifier));
}
} // namespace OHOS::Ace::NG
