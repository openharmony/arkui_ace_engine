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
#include "core/components_ng/pattern/slider/slider_content_modifier.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/pattern/slider/slider_tip_modifier.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paragraph.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT SliderPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(SliderPaintMethod, NodePaintMethod)

public:
    struct TipParameters {
        SizeF bubbleSize_;
        OffsetF bubbleOffset_;
        OffsetF textOffset_;
        bool isDrawTip_ = false;
    };
    explicit SliderPaintMethod(const RefPtr<SliderContentModifier>& sliderContentModifier,
        const SliderContentModifier::Parameters& parameters, float sliderLength, float borderBlank,
        const RefPtr<SliderTipModifier>& sliderTipModifier, RefPtr<NG::Paragraph> paragraph,
        const TipParameters& tipParameters)
        : sliderContentModifier_(sliderContentModifier), parameters_(parameters), sliderTipModifier_(sliderTipModifier),
          paragraph_(std::move(paragraph)), tipParameters_(tipParameters)
    {}
    ~SliderPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(sliderContentModifier_, nullptr);
        return sliderContentModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_VOID(sliderContentModifier_);
        auto paintProperty = DynamicCast<SliderPaintProperty>(paintWrapper->GetPaintProperty());
        CHECK_NULL_VOID(paintProperty);
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto sliderTheme = pipeline->GetTheme<SliderTheme>();
        CHECK_NULL_VOID(sliderTheme);
        sliderContentModifier_->UpdateData(parameters_);
        sliderContentModifier_->JudgeNeedAimate(paintProperty);
        sliderContentModifier_->SetDirection(paintProperty->GetDirectionValue(Axis::HORIZONTAL));
        sliderContentModifier_->SetBackgroundSize(parameters_.backStart, parameters_.backEnd);
        sliderContentModifier_->SetSelectSize(parameters_.selectStart, parameters_.selectEnd);
        sliderContentModifier_->SetCircleCenter(parameters_.circleCenter);
        sliderContentModifier_->SetSelectColor(parameters_.selectColor);
        sliderContentModifier_->SetTrackBackgroundColor(parameters_.trackBackgroundColor);
        sliderContentModifier_->SetBlockColor(parameters_.blockColor);
        sliderContentModifier_->SetTrackThickness(parameters_.trackThickness);
        sliderContentModifier_->SetBlockDiameter(parameters_.blockDiameter);
        sliderContentModifier_->SetStepRatio(parameters_.stepRatio);
        sliderContentModifier_->SetShowSteps(paintProperty->GetShowStepsValue(false));
        sliderContentModifier_->SetBoardColor();
    }

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

    RectF UpdateOverlayRect(PaintWrapper* paintWrapper) const
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
    RefPtr<SliderContentModifier> sliderContentModifier_;
    SliderContentModifier::Parameters parameters_;

    RefPtr<SliderTipModifier> sliderTipModifier_;
    RefPtr<NG::Paragraph> paragraph_;
    TipParameters tipParameters_;
    ACE_DISALLOW_COPY_AND_MOVE(SliderPaintMethod);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_PAINT_METHOD_H
