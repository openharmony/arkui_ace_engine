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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_OFFSCREEN_CANVAS_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_OFFSCREEN_CANVAS_PATTERN_H

#include "base/memory/referenced.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class OffscreenCanvasPaintMethod;
// OffscreenCanvasPattern is the base class for custom paint render node to perform paint canvas.
class ACE_EXPORT OffscreenCanvasPattern : public Pattern {
    DECLARE_ACE_TYPE(OffscreenCanvasPattern, Pattern);

public:
    OffscreenCanvasPattern(int32_t width, int32_t height);
    ~OffscreenCanvasPattern() override = default;

    void FillRect(const Rect& rect);
    void StrokeRect(const Rect& rect);
    void ClearRect(const Rect& rect);
    void Fill();
    void Fill(const RefPtr<CanvasPath2D>& path);
    void Stroke();
    void Stroke(const RefPtr<CanvasPath2D>& path);
    void BeginPath();
    void ClosePath();
    void MoveTo(double x, double y);
    void LineTo(double x, double y);
    void Arc(const ArcParam& param);
    void ArcTo(const ArcToParam& param);
    void AddRect(const Rect& rect);
    void Ellipse(const EllipseParam& param);
    void BezierCurveTo(const BezierCurveParam& param);
    void QuadraticCurveTo(const QuadraticCurveParam& param);

    void FillText(const std::string& text, double x, double y, const PaintState& state);
    void StrokeText(const std::string& text, double x, double y, const PaintState& state);
    double MeasureText(const std::string& text, const PaintState& state);
    double MeasureTextHeight(const std::string& text, const PaintState& state);
    TextMetrics MeasureTextMetrics(const std::string& text, const PaintState& state);
    
    void DrawImage(const Ace::CanvasImage& image, double width, double height);
    void DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& image);
    std::unique_ptr<Ace::ImageData> GetImageData(double left, double top, double width, double height);
    void PutImageData(const Ace::ImageData& imageData);

    void UpdateFillColor(const Color& color);
    void SetFillRuleForPath(const CanvasFillRule rule);
    void SetFillRuleForPath2D(const CanvasFillRule rule);
    int32_t GetWidth();
    int32_t GetHeight();

    const LineDashParam& GetLineDash() const;
    void SetLineDash(const std::vector<double>& segments);

    void Save();
    void Restore();
    void Scale(double x, double y);
    void Rotate(double angle);
    void SetTransform(const TransformParam& param);
    void Transform(const TransformParam& param);
    void Translate(double x, double y);
    std::string ToDataURL(const std::string& type, const double quality);
private:
    RefPtr<OffscreenCanvasPaintMethod> offscreenPaintMethod_;

    ACE_DISALLOW_COPY_AND_MOVE(OffscreenCanvasPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CUSTOM_PAINT_OFFSCREEN_CANVAS_PATTERN_H
