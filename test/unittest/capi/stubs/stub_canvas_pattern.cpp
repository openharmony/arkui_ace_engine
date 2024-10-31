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

#include "stub_canvas_pattern.h"

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
}

void CanvasPattern::AttachRenderContext()
{
}

void CanvasPattern::DetachRenderContext()
{
}

void CanvasPattern::SetOnContext2DAttach(std::function<void()>&& callback)
{
}

void CanvasPattern::SetOnContext2DDetach(std::function<void()>&& callback)
{
}

void CanvasPattern::FireOnContext2DAttach()
{
}

void CanvasPattern::FireOnContext2DDetach()
{
}

void CanvasPattern::OnAttachToFrameNode()
{
}

RefPtr<NodePaintMethod> CanvasPattern::CreateNodePaintMethod()
{
    return nullptr;
}

bool CanvasPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    return false;
}

void CanvasPattern::OnSizeChanged(const DirtySwapConfig& config, bool needReset)
{
}

void CanvasPattern::SetAntiAlias(bool isEnabled)
{

}

void CanvasPattern::FillRect(const Rect& rect)
{

}

void CanvasPattern::StrokeRect(const Rect& rect)
{

}

void CanvasPattern::ClearRect(const Rect& rect)
{
}

void CanvasPattern::Fill()
{
}

void CanvasPattern::Fill(const RefPtr<CanvasPath2D>& path)
{
}

void CanvasPattern::Stroke()
{
}

void CanvasPattern::Stroke(const RefPtr<CanvasPath2D>& path)
{
}

void CanvasPattern::Clip()
{
}

void CanvasPattern::Clip(const RefPtr<CanvasPath2D>& path)
{
}

void CanvasPattern::BeginPath()
{
}

void CanvasPattern::ClosePath()
{
}

void CanvasPattern::MoveTo(double x, double y)
{
}

void CanvasPattern::LineTo(double x, double y)
{
}

void CanvasPattern::Arc(const ArcParam& param)
{
}

void CanvasPattern::ArcTo(const ArcToParam& param)
{
}

void CanvasPattern::AddRect(const Rect& rect)
{
}

void CanvasPattern::Ellipse(const EllipseParam& param)
{
}

void CanvasPattern::BezierCurveTo(const BezierCurveParam& param)
{
}

void CanvasPattern::QuadraticCurveTo(const QuadraticCurveParam& param)
{
}

void CanvasPattern::FillText(const std::string& text, double x, double y, std::optional<double> maxWidth)
{
}

void CanvasPattern::StrokeText(const std::string& text, double x, double y, std::optional<double> maxWidth)
{
}

TextMetrics CanvasPattern::MeasureTextMetrics(const std::string& text, const PaintState& state)
{
    return TextMetrics {};
}

void CanvasPattern::DrawImage(const Ace::CanvasImage& image, double width, double height)
{
}

void CanvasPattern::DrawSvgImage(
    RefPtr<SvgDomBase> svgDom, const Ace::CanvasImage& image, const ImageFit& imageFit)
{
}

void CanvasPattern::DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& image)
{
}

std::unique_ptr<Ace::ImageData> CanvasPattern::GetImageData(double left, double top, double width, double height)
{
    return nullptr;
}

void CanvasPattern::GetImageData(const std::shared_ptr<Ace::ImageData>& imageData)
{
}

void CanvasPattern::PutImageData(const Ace::ImageData& imageData)
{
}

#ifdef PIXEL_MAP_SUPPORTED
void CanvasPattern::TransferFromImageBitmap(const RefPtr<PixelMap>& pixelMap)
{
}
#else
void CanvasPattern::TransferFromImageBitmap(const Ace::ImageData& imageData)
{
}
#endif

void CanvasPattern::CloseImageBitmap(const std::string& src)
{
}

void CanvasPattern::UpdateGlobalAlpha(double alpha)
{
}

void CanvasPattern::UpdateCompositeOperation(CompositeOperation type)
{
}

void CanvasPattern::UpdateSmoothingEnabled(bool enabled)
{
}

void CanvasPattern::UpdateSmoothingQuality(const std::string& quality)
{
}

void CanvasPattern::UpdateLineCap(LineCapStyle cap)
{
}

void CanvasPattern::UpdateLineDashOffset(double dash)
{
}

void CanvasPattern::UpdateLineJoin(LineJoinStyle join)
{
}

void CanvasPattern::UpdateLineWidth(double width)
{
}

void CanvasPattern::UpdateMiterLimit(double limit)
{
}

void CanvasPattern::UpdateShadowBlur(double blur)
{
}

void CanvasPattern::UpdateShadowColor(const Color& color)
{
}

void CanvasPattern::UpdateShadowOffsetX(double offsetX)
{
}

void CanvasPattern::UpdateShadowOffsetY(double offsetY)
{
}

void CanvasPattern::UpdateTextAlign(TextAlign align)
{
}

void CanvasPattern::UpdateTextBaseline(TextBaseline baseline)
{
}

void CanvasPattern::UpdateStrokePattern(const std::weak_ptr<Ace::Pattern>& pattern)
{
}

void CanvasPattern::UpdateStrokeColor(const Color& color)
{
}

void CanvasPattern::SetStrokeGradient(const std::shared_ptr<Ace::Gradient>& gradient)
{
}

void CanvasPattern::UpdateFontWeight(FontWeight weight)
{
}

void CanvasPattern::UpdateFontStyle(FontStyle style)
{
}

void CanvasPattern::UpdateFontFamilies(const std::vector<std::string>& families)
{
}

void CanvasPattern::UpdateFontSize(const Dimension& size)
{
}

void CanvasPattern::UpdateFillColor(const Color& color)
{
}

void CanvasPattern::SetFillGradient(const std::shared_ptr<Ace::Gradient>& gradient)
{
}

void CanvasPattern::UpdateFillPattern(const std::weak_ptr<Ace::Pattern>& pattern)
{
}

void CanvasPattern::UpdateFillRuleForPath(const CanvasFillRule rule)
{
}

void CanvasPattern::UpdateFillRuleForPath2D(const CanvasFillRule rule)
{
}

LineDashParam CanvasPattern::GetLineDash() const
{
    return LineDashParam {};
}

void CanvasPattern::UpdateLineDash(const std::vector<double>& segments)
{
}

void CanvasPattern::Save()
{
}

void CanvasPattern::Restore()
{
}

void CanvasPattern::Scale(double x, double y)
{
}

void CanvasPattern::Rotate(double angle)
{
}

void CanvasPattern::SetTransform(const TransformParam& param)
{
}

void CanvasPattern::ResetTransform()
{
}

void CanvasPattern::Transform(const TransformParam& param)
{
}

void CanvasPattern::Translate(double x, double y)
{
}

std::string CanvasPattern::ToDataURL(const std::string& type, double quality)
{
    return nullptr;
}

std::string CanvasPattern::GetJsonData(const std::string& path)
{
    return nullptr;

}

double CanvasPattern::GetWidth()
{
    this->isCalled = true;
    this->counter++;  
    return this->width;
}

double CanvasPattern::GetHeight()
{
    this->isCalled = true;
    this->counter++;
    return this->height;
}

void CanvasPattern::SetRSCanvasCallback(std::function<void(RSCanvas*, double, double)>& callback)
{
}

void CanvasPattern::SetInvalidate()
{
    this->isCalled = true;
    this->counter++;
}

void CanvasPattern::SetTextDirection(TextDirection direction)
{
}

void CanvasPattern::SetFilterParam(const std::string& filterStr)
{
}

TransformParam CanvasPattern::GetTransform() const
{
    return TransformParam {};
}

void CanvasPattern::SaveLayer()
{
}

void CanvasPattern::RestoreLayer()
{
}

void CanvasPattern::EnableAnalyzer(bool enable)
{
}

void CanvasPattern::SetImageAIOptions(void* options)
{
}


void CanvasPattern::StartImageAnalyzer(void* config, OnAnalyzedCallback& onAnalyzed)
{
    this->isCalled =  true;
    this->config = config;
    this->onAnalyzed = onAnalyzed;
}

void CanvasPattern::StopImageAnalyzer()
{
    this->isCalled = true;
    this->counter++;
}

bool CanvasPattern::IsSupportImageAnalyzerFeature()
{
    return false;
}

void CanvasPattern::CreateAnalyzerOverlay()
{
}

void CanvasPattern::UpdateAnalyzerOverlay()
{
}

void CanvasPattern::DestroyAnalyzerOverlay()
{
}

void CanvasPattern::ReleaseImageAnalyzer()
{
}

void CanvasPattern::DumpInfo()
{
}

void CanvasPattern::Reset()
{
}

void CanvasPattern::SetTransform(std::shared_ptr<Ace::Pattern> pattern, const TransformParam& transform)
{
}

void CanvasPattern::OnLanguageConfigurationUpdate()
{
}

void CanvasPattern::OnModifyDone()
{
}

void CanvasPattern::UpdateTextDefaultDirection()
{
}

void CanvasPattern::SetDensity(double density)
{
}

int32_t CanvasPattern::GetId()
{
    return 0;
}

void CanvasPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
}

void CanvasPattern::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
}
} // namespace OHOS::Ace::NG
