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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_GRAPHIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_GRAPHIC_H

#include "include/core/SkMaskFilter.h"

#include "base/utils/utils.h"
#include "core/components/common/properties/decoration.h"
#include "core/components_ng/render/drawing_forward.h"
#include "core/components_ng/render/drawing.h"

#include "frameworks/core/components_ng/svg/parse/svg_node.h"
#include "frameworks/core/components_ng/svg/parse/svg_pattern.h"

namespace OHOS::Ace::NG {

enum class PaintType {
    COLOR = 0,
    LINEAR_GRADIENT,
    RADIAL_GRADIENT,
    PATTERN,
    NONE
};

struct RsRadialGradient {
    RSPoint center_;
    RSPoint focal_;
    RSTileMode spreadMethod_;
    RSScalar r_;
    std::vector<RSScalar> pos_;
    std::vector<RSColorQuad> colors_;
    std::optional<RSMatrix> matrix_;
};

struct RsLinearGradient {
    RSPoint startPoint_;
    RSPoint endPoint_;
    RSTileMode spreadMethod_;
    std::vector<RSScalar> pos_;
    std::vector<RSColorQuad> colors_;
    std::optional<RSMatrix> matrix_;
};
class SvgGraphic : public SvgNode {
    DECLARE_ACE_TYPE(SvgGraphic, SvgNode);

public:
    SvgGraphic() : SvgNode()
    {
        InitGraphicFlag();
    }
    ~SvgGraphic() override = default;
    void OnDraw(RSCanvas& canvas, const SvgLengthScaleRule& lengthRule) override;
    void OnDraw(RSCanvas& canvas, const Size& layout, const std::optional<Color>& color) override;
protected:
    void OnGraphicFill()
    {
        if (rsCanvas_) {
            auto smoothEdge = GetSmoothEdge();
            if (SystemProperties::GetDebugEnabled()) {
                TAG_LOGD(AceLogTag::ACE_IMAGE, "svg path:%{public}s, smoothEdge = %{public}f",
                    path_->ConvertToSVGString().c_str(), smoothEdge);
            }
            if (!path_->IsValid()) {
                TAG_LOGW(AceLogTag::ACE_IMAGE, "svg path is invalid");
            }
            if (GreatNotEqual(smoothEdge, 0.0f)) {
                RSFilter filter;
                filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(
                    RSBlurType::NORMAL, static_cast<double>(smoothEdge), false
                ));
                auto tmpFillBrush = fillBrush_;
                tmpFillBrush.SetFilter(filter);
                rsCanvas_->AttachBrush(tmpFillBrush);
                rsCanvas_->DrawPath(path_.value());
                rsCanvas_->DetachBrush();
            } else {
                rsCanvas_->AttachBrush(fillBrush_);
                rsCanvas_->DrawPath(path_.value());
                rsCanvas_->DetachBrush();
            }
        }
    }

    void OnGraphicFill(RSCanvas& canvas, const SvgCoordinateSystemContext& svgCoordinateSystemContext,
        RSRecordingPath& rsPath, PaintType paintType)
    {
        RSBrush brush;
        brush.SetAntiAlias(true);
        auto smoothEdge = GetSmoothEdge();
        if (GreatNotEqual(smoothEdge, 0.0f)) {
            RSFilter filter;
            filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(
                RSBlurType::NORMAL, static_cast<double>(smoothEdge), false
            ));
            brush.SetFilter(filter);
        }
        InitBrush(canvas, brush, svgCoordinateSystemContext, paintType);
        canvas.AttachBrush(brush);
        canvas.DrawPath(rsPath);
        canvas.DetachBrush();
    }

    void OnGraphicStroke(RSCanvas& canvas, const SvgCoordinateSystemContext& svgCoordinateSystemContext,
        RSRecordingPath& rsPath, PaintType paintType)
    {
        RSPen rsPen;
        auto smoothEdge = GetSmoothEdge();
        if (GreatNotEqual(smoothEdge, 0.0f)) {
            RSFilter filter;
            filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(
                RSBlurType::NORMAL, static_cast<double>(smoothEdge), false
            ));
            rsPen.SetFilter(filter);
        }
        InitPenFill(rsPen, svgCoordinateSystemContext, paintType);
        SetPenStyle(rsPen);
        canvas.AttachPen(rsPen);
        canvas.DrawPath(rsPath);
        canvas.DetachPen();
    }

    void OnGraphicStroke()
    {
        if (rsCanvas_) {
            auto smoothEdge = GetSmoothEdge();
            if (SystemProperties::GetDebugEnabled()) {
                TAG_LOGD(AceLogTag::ACE_IMAGE, "svg path:%{public}s, smoothEdge = %{public}f",
                    path_->ConvertToSVGString().c_str(), smoothEdge);
            }
            if (!path_->IsValid()) {
                TAG_LOGW(AceLogTag::ACE_IMAGE, "svg path is invalid");
            }
            if (GreatNotEqual(smoothEdge, 0.0f)) {
                RSFilter filter;
                filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(
                    RSBlurType::NORMAL, static_cast<double>(smoothEdge), false
                ));
                auto tmpStrokePen = strokePen_;
                tmpStrokePen.SetFilter(filter);
                rsCanvas_->AttachPen(tmpStrokePen);
            } else {
                rsCanvas_->AttachPen(strokePen_);
            }
            rsCanvas_->DrawPath(path_.value());
            rsCanvas_->DetachPen();
        }
    }

    // rect line polygon path circle ellipse
    void InitGraphicFlag()
    {
        hrefFill_ = true;
        hrefRender_ = true;
        passStyle_ = false;
        inheritStyle_ = true;
        drawTraversed_ = true;
    }

    // Update fillStates & strokeStates
    void UpdateFillGradient(const Size& viewPort);
    void UpdateStrokeGradient(const Size& viewPort);
    bool UpdateFillStyle(const std::optional<Color>& color, bool antiAlias = true);
    bool UpdateStrokeStyle(bool antiAlias = true);
    void SetStrokeGradientStyle(double opacity);
    bool SetGradientStyle(double opacity);
    void UpdateLineDash();
    void SetLinearGradient(const Size& viewPort, OHOS::Ace::Gradient& gradient);
    void SetRadialGradient(const Size& viewPort, OHOS::Ace::Gradient& gradient);
    void SetGradientFillStyle(const std::optional<OHOS::Ace::Gradient>& gradient, std::vector<RSScalar> pos,
        std::vector<RSColorQuad> colors);
    uint32_t GetAlpha();

    std::optional<RSRecordingPath> path_;
    RSBrush fillBrush_;
    RSPen strokePen_;
    FillState fillState_;

private:
    PaintType GetHrefType(const std::string& href);
    std::optional<Color> GetFillColor();
    void UpdateColorFilter(RSFilter& filter);
    RsLinearGradient ConvertToRsLinearGradient(const SvgLinearGradientInfo& linearGradientInfo);
    RsRadialGradient ConvertToRsRadialGradient(const SvgRadialGradientInfo& radialGradientInfo);
    PaintType GetFillType();
    void InitBrush(RSCanvas& canvas, RSBrush& brush, const SvgCoordinateSystemContext& svgCoordinateSystemContext,
        PaintType paintType);
    void SetBrushColor(RSBrush& brush);
    void SetBrushLinearGradient(RSBrush& brush, const SvgCoordinateSystemContext& svgCoordinateSystemContext);
    void SetBrushRadialGradient(RSBrush& brush, const SvgCoordinateSystemContext& svgCoordinateSystemContext);
    void SetBrushPattern(RSCanvas& canvas, RSBrush& brush,
        const SvgCoordinateSystemContext& svgCoordinateSystemContext);

    PaintType GetStrokeType();
    void InitPenFill(RSPen& rsPen, const SvgCoordinateSystemContext& svgCoordinateSystemContext, PaintType paintType);
    void SetPenColor(RSPen& rsPen);
    void SetPenStyle(RSPen& rsPen);
    void AddColorFilterEffect(RSPen& rsPen);
    void SetPenLinearGradient(RSPen& rsPen, const SvgCoordinateSystemContext& svgCoordinateSystemContext);
    void SetPenRadialGradient(RSPen& rsPen, const SvgCoordinateSystemContext& svgCoordinateSystemContext);
    bool CheckHrefPattern();
    void RectifyTargetSize(const Rect& bounds, double& width, double& height);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SVG_PARSE_SVG_GRAPHIC_H