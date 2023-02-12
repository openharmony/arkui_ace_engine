/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_PAINT_METHOD_H

#include <utility>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/pattern/slider/slider_tip_modifier.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SliderPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(SliderPaintMethod, NodePaintMethod)

public:
    struct Parameters {
        float trackThickness = 0.0f;
        float blockDiameter = 0.0f;
        float sliderLength = 0.0f;
        float borderBlank = 0.0f;
        float stepRatio = 0.0f;
        float valueRatio = 0.0f;
        float hotCircleShadowWidth = 0.0f;
        bool hotFlag = false;
        bool mouseHoverFlag_ = false;
        bool mousePressedFlag_ = false;
    };
    struct TipParameters {
        SizeF bubbleSize_;
        OffsetF bubbleOffset_;
        OffsetF textOffset_;
        bool isDrawTip_ = false;
    };
    explicit SliderPaintMethod(const RefPtr<SliderTipModifier>& sliderTipModifier, const Parameters& parameters,
        RefPtr<NG::Paragraph> paragraph, const TipParameters& tipParameters)
        : sliderTipModifier_(sliderTipModifier), parameters_(parameters), paragraph_(std::move(paragraph)),
          tipParameters_(tipParameters)
    {}
    ~SliderPaintMethod() override = default;
    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;

    RefPtr<Modifier> GetOverlayModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(sliderTipModifier_, nullptr);
        sliderTipModifier_->SetBoundsRect(UpdateOverlayRect(paintWrapper));
        return sliderTipModifier_;
    }

    void UpdateOverlayModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_VOID(sliderTipModifier_);
        auto paintProperty = DynamicCast<SliderPaintProperty>(paintWrapper->GetPaintProperty());
        if (paintProperty) {
            sliderTipModifier_->SetDirection(paintProperty->GetDirectionValue(Axis::HORIZONTAL));
            sliderTipModifier_->SetTipColor(paintProperty->GetTipColorValue(Color::BLACK));
        }
        sliderTipModifier_->SetTipFlag(tipParameters_.isDrawTip_);
        sliderTipModifier_->SetParagraph(paragraph_);
        sliderTipModifier_->SetContentOffset(paintWrapper->GetContentOffset());
        sliderTipModifier_->SetBubbleSize(tipParameters_.bubbleSize_);
        sliderTipModifier_->SetBubbleOffset(tipParameters_.bubbleOffset_);
        sliderTipModifier_->SetTextOffset(tipParameters_.textOffset_);
    }

    RectF UpdateOverlayRect(PaintWrapper* paintWrapper)
    {
        constexpr float HALF = 0.5;
        auto contentSize = paintWrapper->GetContentSize();
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, RectF());
        auto theme = pipeline->GetTheme<SliderTheme>();
        CHECK_NULL_RETURN(theme, RectF());
        auto distance = static_cast<float>(theme->GetBubbleToCircleCenterDistance().ConvertToPx());
        auto axis =
            DynamicCast<SliderPaintProperty>(paintWrapper->GetPaintProperty())->GetDirectionValue(Axis::HORIZONTAL);
        RectF rect;
        if (axis == Axis::HORIZONTAL) {
            rect.SetOffset(
                OffsetF(-tipParameters_.bubbleSize_.Width(), -tipParameters_.bubbleSize_.Height() - distance));
            rect.SetSize(SizeF(contentSize.Width() + tipParameters_.bubbleSize_.Width() / HALF,
                contentSize.Height() * HALF + tipParameters_.bubbleSize_.Height() + distance));
        } else {
            rect.SetOffset(
                OffsetF(-tipParameters_.bubbleSize_.Width() - distance, -tipParameters_.bubbleSize_.Height()));
            rect.SetSize(SizeF(contentSize.Width() * HALF + tipParameters_.bubbleSize_.Width() + distance,
                contentSize.Height() + tipParameters_.bubbleSize_.Height() / HALF));
        }
        return rect;
    }

private:
    struct LinePenAndSize {
        RSPen pen;
        PointF start;
        PointF end;
    };

    struct MarkerPenAndPath {
        RSPen pen;
        RSPath path;
    };

    struct CirclePenAndSize {
        RSPen pen;
        RSPen shadowPen;
        PointF center;
        float radius;
        float shadowRadius;
    };

    LinePenAndSize GetBackgroundPen(const RefPtr<SliderPaintProperty>& sliderPaintProperty, const OffsetF& offset,
        const RefPtr<SliderTheme>& theme) const;
    MarkerPenAndPath GetMarkerPen(const RefPtr<SliderPaintProperty>& sliderPaintProperty, const OffsetF& offset,
        const RefPtr<SliderTheme>& theme) const;
    LinePenAndSize GetSelectPen(const RefPtr<SliderPaintProperty>& sliderPaintProperty, const OffsetF& offset,
        const RefPtr<SliderTheme>& theme) const;
    CirclePenAndSize GetCirclePen(const RefPtr<SliderPaintProperty>& sliderPaintProperty, const OffsetF& offset,
        const RefPtr<SliderTheme>& theme) const;

    RefPtr<SliderTipModifier> sliderTipModifier_;
    Parameters parameters_;
    RefPtr<NG::Paragraph> paragraph_;
    TipParameters tipParameters_;
    // Distance between slide track and Content boundary
    float centerWidth_ = 0.0f;
    ACE_DISALLOW_COPY_AND_MOVE(SliderPaintMethod);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_PAINT_METHOD_H
