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
#ifndef ACE_UNITTEST
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderCtx = host->GetRenderContext();
    renderCtx->SetClipToBounds(false);
    renderCtx->SetUsingContentRectForRenderFrame(true);
    renderCtx->SetFrameGravity(Rosen::Gravity::RESIZE_ASPECT_FILL);
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
    ACE_SCOPED_TRACE("CanvasPattern::OnDirtyLayoutWrapperSwap");
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
        auto canvasEventHub = GetEventHub<CanvasEventHub>();
        CHECK_NULL_VOID(canvasEventHub);
        canvasEventHub->FireReadyEvent();
    }
}

void CanvasPattern::SetAntiAlias(bool isEnabled)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [isEnabled](CanvasPaintMethod& paintMethod) {
        paintMethod.SetAntiAlias(isEnabled);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetAntiAliasOp>(isEnabled);
#endif
}

void CanvasPattern::FillRect(const Rect& rect)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [rect](CanvasPaintMethod& paintMethod) {
        paintMethod.FillRect(rect);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<FillRectOp>(rect);
#endif
}

void CanvasPattern::StrokeRect(const Rect& rect)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [rect](CanvasPaintMethod& paintMethod) {
        paintMethod.StrokeRect(rect);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<StrokeRectOp>(rect);
#endif
}

void CanvasPattern::ClearRect(const Rect& rect)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [rect](CanvasPaintMethod& paintMethod) {
        paintMethod.ClearRect(rect);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<ClearRectOp>(rect);
#endif
}

void CanvasPattern::Fill()
{
#ifndef USE_FAST_TASKPOOL
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Fill();
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<FillOp>();
#endif
}

void CanvasPattern::Fill(const RefPtr<CanvasPath2D>& path)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [path](CanvasPaintMethod& paintMethod) {
        paintMethod.Fill(path);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<Fill2DOp>(path);
#endif
}

void CanvasPattern::Stroke()
{
#ifndef USE_FAST_TASKPOOL
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Stroke();
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<StrokeOp>();
#endif
}

void CanvasPattern::Stroke(const RefPtr<CanvasPath2D>& path)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [path](CanvasPaintMethod& paintMethod) {
        paintMethod.Stroke(path);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<Stroke2DOp>(path);
#endif
}

void CanvasPattern::Clip()
{
#ifndef USE_FAST_TASKPOOL
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Clip();
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<ClipOp>();
#endif
}

void CanvasPattern::Clip(const RefPtr<CanvasPath2D>& path)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [path](CanvasPaintMethod& paintMethod) {
        paintMethod.Clip(path);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<Clip2DOp>(path);
#endif
}

void CanvasPattern::BeginPath()
{
#ifndef USE_FAST_TASKPOOL
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.BeginPath();
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<BeginPathOp>();
#endif
}

void CanvasPattern::ClosePath()
{
#ifndef USE_FAST_TASKPOOL
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.ClosePath();
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<ClosePathOp>();
#endif
}

void CanvasPattern::MoveTo(double x, double y)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [x, y](CanvasPaintMethod& paintMethod) {
        paintMethod.MoveTo(x, y);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<MoveToOp>(x, y);
#endif
}

void CanvasPattern::LineTo(double x, double y)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [x, y](CanvasPaintMethod& paintMethod) {
        paintMethod.LineTo(x, y);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<LineToOp>(x, y);
#endif
}

void CanvasPattern::Arc(const ArcParam& param)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [param](CanvasPaintMethod& paintMethod) {
        paintMethod.Arc(param);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<ArcOp>(param);
#endif
}

void CanvasPattern::ArcTo(const ArcToParam& param)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [param](CanvasPaintMethod& paintMethod) {
        paintMethod.ArcTo(param);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<ArcToOp>(param);
#endif
}

void CanvasPattern::AddRect(const Rect& rect)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [rect](CanvasPaintMethod& paintMethod) {
        paintMethod.AddRect(rect);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<AddRectOp>(rect);
#endif
}

void CanvasPattern::Ellipse(const EllipseParam& param)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [param](CanvasPaintMethod& paintMethod) {
        paintMethod.Ellipse(param);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<EllipseOp>(param);
#endif
}

void CanvasPattern::BezierCurveTo(const BezierCurveParam& param)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [param](CanvasPaintMethod& paintMethod) {
        paintMethod.BezierCurveTo(param);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<BezierCurveToOp>(param);
#endif
}

void CanvasPattern::QuadraticCurveTo(const QuadraticCurveParam& param)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [param](CanvasPaintMethod& paintMethod) {
        paintMethod.QuadraticCurveTo(param);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<QuadraticCurveToOp>(param);
#endif
}

void CanvasPattern::FillText(const std::string& text, double x, double y, std::optional<double> maxWidth)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [text, x, y, maxWidth](CanvasPaintMethod& paintMethod) {
        paintMethod.FillText(text, x, y, maxWidth);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<FillTextOp>(text, x, y, maxWidth);
#endif
}

void CanvasPattern::StrokeText(const std::string& text, double x, double y, std::optional<double> maxWidth)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [text, x, y, maxWidth](CanvasPaintMethod& paintMethod) {
        paintMethod.StrokeText(text, x, y, maxWidth);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<StrokeTextOp>(text, x, y, maxWidth);
#endif
}

TextMetrics CanvasPattern::MeasureTextMetrics(const std::string& text, const PaintState& state)
{
    return paintMethod_->MeasureTextMetrics(text, state);
}

void CanvasPattern::DrawImage(const Ace::CanvasImage& image, double width, double height)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [image, width, height](CanvasPaintMethod& paintMethod) {
        paintMethod.DrawImage(image, width, height);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<DrawImageOp>(image, width, height);
#endif
}

void CanvasPattern::DrawSvgImage(
    RefPtr<SvgDomBase> svgDom, const Ace::CanvasImage& image, const ImageFit& imageFit)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [svgDom, image, imageFit](CanvasPaintMethod& paintMethod) {
        paintMethod.DrawSvgImage(svgDom, image, imageFit);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<DrawSvgImageOp>(svgDom, image, imageFit);
#endif
}

void CanvasPattern::DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& image)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [pixelMap, image](CanvasPaintMethod& paintMethod) {
        paintMethod.DrawPixelMap(pixelMap, image);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<DrawPixelMapOp>(pixelMap, image);
#endif
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
#ifndef USE_FAST_TASKPOOL
    auto task = [imageData](CanvasPaintMethod& paintMethod) {
        paintMethod.PutImageData(imageData);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<PutImageDataOp>(imageData);
#endif
}

#ifdef PIXEL_MAP_SUPPORTED
void CanvasPattern::TransferFromImageBitmap(const RefPtr<PixelMap>& pixelMap)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [pixelMap](CanvasPaintMethod& paintMethod) {
        paintMethod.TransferFromImageBitmap(pixelMap);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<TransferFromImageBitmapOp>(pixelMap);
#endif
}
#else
void CanvasPattern::TransferFromImageBitmap(const Ace::ImageData& imageData)
{
#ifndef ACE_UNITTEST
#ifndef USE_FAST_TASKPOOL
    auto task = [imageData](CanvasPaintMethod& paintMethod) {
        paintMethod.PutImageData(imageData);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<PutImageDataOp>(imageData);
#endif
#endif
}
#endif

void CanvasPattern::CloseImageBitmap(const std::string& src)
{
    paintMethod_->CloseImageBitmap(src);
}

void CanvasPattern::UpdateGlobalAlpha(double alpha)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [alpha](CanvasPaintMethod& paintMethod) {
        paintMethod.SetAlpha(alpha);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetAlphaOp>(alpha);
#endif
}

void CanvasPattern::UpdateCompositeOperation(CompositeOperation type)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [type](CanvasPaintMethod& paintMethod) {
        paintMethod.SetCompositeType(type);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetCompositeTypeOp>(type);
#endif
}

void CanvasPattern::UpdateSmoothingEnabled(bool enabled)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [enabled](CanvasPaintMethod& paintMethod) {
        paintMethod.SetSmoothingEnabled(enabled);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetSmoothingEnabledOp>(enabled);
#endif
}

void CanvasPattern::UpdateSmoothingQuality(const std::string& quality)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [quality](CanvasPaintMethod& paintMethod) {
        paintMethod.SetSmoothingQuality(quality);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetSmoothingQualityOp>(quality);
#endif
}

void CanvasPattern::UpdateLineCap(LineCapStyle cap)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [cap](CanvasPaintMethod& paintMethod) {
        paintMethod.SetLineCap(cap);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetLineCapOp>(cap);
#endif
}

void CanvasPattern::UpdateLineDashOffset(double dash)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [dash](CanvasPaintMethod& paintMethod) {
        paintMethod.SetLineDashOffset(dash);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetLineDashOffsetOp>(dash);
#endif
}

void CanvasPattern::UpdateLineJoin(LineJoinStyle join)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [join](CanvasPaintMethod& paintMethod) {
        paintMethod.SetLineJoin(join);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetLineJoinOp>(join);
#endif
}

void CanvasPattern::UpdateLineWidth(double width)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [width](CanvasPaintMethod& paintMethod) {
        paintMethod.SetLineWidth(width);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetLineWidthOp>(width);
#endif
}

void CanvasPattern::UpdateMiterLimit(double limit)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [limit](CanvasPaintMethod& paintMethod) {
        paintMethod.SetMiterLimit(limit);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetMiterLimitOp>(limit);
#endif
}

void CanvasPattern::UpdateShadowBlur(double blur)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [blur](CanvasPaintMethod& paintMethod) {
        paintMethod.SetShadowBlur(blur);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetShadowBlurOp>(blur);
#endif
}

void CanvasPattern::UpdateShadowColor(const Color& color)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [color](CanvasPaintMethod& paintMethod) {
        paintMethod.SetShadowColor(color);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetShadowColorOp>(color);
#endif
}

void CanvasPattern::UpdateShadowOffsetX(double offsetX)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [offsetX](CanvasPaintMethod& paintMethod) {
        paintMethod.SetShadowOffsetX(offsetX);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetShadowOffsetXOp>(offsetX);
#endif
}

void CanvasPattern::UpdateShadowOffsetY(double offsetY)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [offsetY](CanvasPaintMethod& paintMethod) {
        paintMethod.SetShadowOffsetY(offsetY);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetShadowOffsetYOp>(offsetY);
#endif
}

void CanvasPattern::UpdateTextAlign(TextAlign align)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [align](CanvasPaintMethod& paintMethod) {
        paintMethod.SetTextAlign(align);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetTextAlignOp>(align);
#endif
    paintMethod_->SetMeasureTextAlign(align);
}

void CanvasPattern::UpdateTextBaseline(TextBaseline baseline)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [baseline](CanvasPaintMethod& paintMethod) {
        paintMethod.SetTextBaseline(baseline);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetTextBaselineOp>(baseline);
#endif
    paintMethod_->SetMeasureTextBaseline(baseline);
}

void CanvasPattern::UpdateStrokePattern(const std::weak_ptr<Ace::Pattern>& pattern)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [pattern](CanvasPaintMethod& paintMethod) {
        paintMethod.SetStrokePatternNG(pattern);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetStrokePatternNGOp>(pattern);
#endif
}

void CanvasPattern::UpdateStrokeColor(const Color& color)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [color](CanvasPaintMethod& paintMethod) {
        paintMethod.SetStrokeColor(color);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetStrokeColorOp>(color);
#endif
}

void CanvasPattern::SetStrokeGradient(const std::shared_ptr<Ace::Gradient>& gradient)
{
    CHECK_NULL_VOID(gradient);
#ifndef USE_FAST_TASKPOOL
    auto task = [gradientObj = *gradient](CanvasPaintMethod& paintMethod) {
        paintMethod.SetStrokeGradient(gradientObj);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetStrokeGradientOp>(gradient);
#endif
}

void CanvasPattern::UpdateFontWeight(FontWeight weight)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [weight](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFontWeight(weight);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetFontWeightOp>(weight);
#endif
    paintMethod_->SetMeasureFontWeight(weight);
}

void CanvasPattern::UpdateFontStyle(FontStyle style)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [style](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFontStyle(style);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetFontStyleOp>(style);
#endif
    paintMethod_->SetMeasureFontStyle(style);
}

void CanvasPattern::UpdateFontFamilies(const std::vector<std::string>& families)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [families](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFontFamilies(families);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetFontFamiliesOp>(families);
#endif
    paintMethod_->SetMeasureFontFamilies(families);
}

void CanvasPattern::UpdateFontSize(const Dimension& size)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [size](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFontSize(size);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetFontSizeOp>(size);
#endif
    paintMethod_->SetMeasureFontSize(size);
}

void CanvasPattern::UpdateLetterSpacing(const Dimension& letterSpacing)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [letterSpacing](CanvasPaintMethod& paintMethod) {
        paintMethod.SetLetterSpacing(letterSpacing);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetLetterSpacingOp>(letterSpacing);
#endif
    paintMethod_->SetMeasureLetterSpacing(letterSpacing);
}

void CanvasPattern::UpdateFillColor(const Color& color)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [color](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFillColor(color);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetFillColorOp>(color);
#endif
}

void CanvasPattern::SetFillGradient(const std::shared_ptr<Ace::Gradient>& gradient)
{
    CHECK_NULL_VOID(gradient);
#ifndef USE_FAST_TASKPOOL
    auto task = [gradientObj = *gradient](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFillGradient(gradientObj);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetFillGradientOp>(gradient);
#endif
}

void CanvasPattern::UpdateFillPattern(const std::weak_ptr<Ace::Pattern>& pattern)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [pattern](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFillPatternNG(pattern);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetFillPatternNGOp>(pattern);
#endif
}

void CanvasPattern::UpdateFillRuleForPath(const CanvasFillRule rule)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [rule](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFillRuleForPath(rule);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetFillRuleForPathOp>(rule);
#endif
}

void CanvasPattern::UpdateFillRuleForPath2D(const CanvasFillRule rule)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [rule](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFillRuleForPath2D(rule);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetFillRuleForPath2DOp>(rule);
#endif
}

LineDashParam CanvasPattern::GetLineDash() const
{
    return paintMethod_->GetLineDash();
}

void CanvasPattern::UpdateLineDash(const std::vector<double>& segments)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [segments](CanvasPaintMethod& paintMethod) {
        paintMethod.SetLineDash(segments);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetLineDashOp>(segments);
#endif
    paintMethod_->SetLineDashParam(segments);
}

void CanvasPattern::Save()
{
#ifndef USE_FAST_TASKPOOL
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Save();
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SaveOp>();
#endif
    paintMethod_->SaveProperties();
}

void CanvasPattern::Restore()
{
#ifndef USE_FAST_TASKPOOL
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Restore();
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<RestoreOp>();
#endif
    paintMethod_->RestoreProperties();
}

void CanvasPattern::Scale(double x, double y)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [x, y](CanvasPaintMethod& paintMethod) {
        paintMethod.Scale(x, y);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<ScaleOp>(x, y);
#endif
    paintMethod_->ScaleMatrix(x, y);
}

void CanvasPattern::Rotate(double angle)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [angle](CanvasPaintMethod& paintMethod) {
        paintMethod.Rotate(angle);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<RotateOp>(angle);
#endif
    paintMethod_->RotateMatrix(angle);
}

void CanvasPattern::SetTransform(const TransformParam& param)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [param](CanvasPaintMethod& paintMethod) {
        paintMethod.SetTransform(param);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetTransformOp>(param);
#endif
    paintMethod_->SetTransformMatrix(param);
}

void CanvasPattern::ResetTransform()
{
#ifndef USE_FAST_TASKPOOL
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.ResetTransform();
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<ResetTransformOp>();
#endif
    paintMethod_->ResetTransformMatrix();
}

void CanvasPattern::Transform(const TransformParam& param)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [param](CanvasPaintMethod& paintMethod) {
        paintMethod.Transform(param);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<TransformOp>(param);
#endif
    paintMethod_->TransformMatrix(param);
}

void CanvasPattern::Translate(double x, double y)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [x, y](CanvasPaintMethod& paintMethod) {
        paintMethod.Translate(x, y);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<TranslateOp>(x, y);
#endif
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
#ifndef USE_FAST_TASKPOOL
    auto task = [](CanvasPaintMethod& paintMethod) {};
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetInvalidateOp>();
#endif
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
#ifndef USE_FAST_TASKPOOL
    auto task = [direction](CanvasPaintMethod& paintMethod) {
        paintMethod.SetTextDirection(direction);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetTextDirectionOp>(direction);
#endif
}

void CanvasPattern::SetFilterParam(const std::string& filterStr)
{
#ifndef USE_FAST_TASKPOOL
    auto task = [filterStr](CanvasPaintMethod& paintMethod) {
        paintMethod.SetFilterParam(filterStr);
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SetFilterParamOp>(filterStr);
#endif
}

TransformParam CanvasPattern::GetTransform() const
{
    return paintMethod_->GetTransform();
}

void CanvasPattern::SaveLayer()
{
#ifndef USE_FAST_TASKPOOL
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.SaveLayer();
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<SaveLayerOp>();
#endif
}

void CanvasPattern::RestoreLayer()
{
#ifndef USE_FAST_TASKPOOL
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.RestoreLayer();
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<RestoreLayerOp>();
#endif
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

void CanvasPattern::DumpInfo()
{
    CHECK_NULL_VOID(paintMethod_);
    DumpLog::GetInstance().AddDesc(paintMethod_->GetDumpInfo());
    CHECK_NULL_VOID(contentModifier_);
    DumpLog::GetInstance().AddDesc(contentModifier_->GetDumpInfo());
}

void CanvasPattern::Reset()
{
#ifndef USE_FAST_TASKPOOL
    auto task = [](CanvasPaintMethod& paintMethod) {
        paintMethod.Reset();
    };
    paintMethod_->PushTask(task);
#else
    paintMethod_->PushTask<ResetCanvasOp>();
#endif
    paintMethod_->ResetTransformMatrix();
    paintMethod_->ResetLineDash();
    paintMethod_->ResetMeasureTextState();
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
    auto host = GetHost();
    CHECK_NULL_RETURN(host, -1);
    return host->GetId();
}

void CanvasPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(paintMethod_);
    json->Put("CanvasPaint", paintMethod_->GetDumpInfo().c_str());
    CHECK_NULL_VOID(contentModifier_);
    json->Put("CanvasModifier", contentModifier_->GetDumpInfo().c_str());
}

void CanvasPattern::DumpSimplifyInfo(std::unique_ptr<JsonValue>& json)
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
