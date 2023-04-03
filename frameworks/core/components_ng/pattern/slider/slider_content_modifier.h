/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_CONTENT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_CONTENT_MODIFIER_H

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components/slider/slider_theme.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
class SliderContentModifier : public ContentModifier {
    DECLARE_ACE_TYPE(SliderContentModifier, ContentModifier);

public:
    struct Parameters {
        float trackThickness = 0.0f;
        float blockDiameter = 0.0f;
        float stepRatio = 0.0f;
        float hotCircleShadowWidth = 0.0f;
        bool mouseHoverFlag_ = false;
        bool mousePressedFlag_ = false;
        PointF selectStart;
        PointF selectEnd;
        PointF backStart;
        PointF backEnd;
        PointF circleCenter;
        Color selectColor;
        Color trackBackgroundColor;
        Color blockColor;
    };

    explicit SliderContentModifier(const Parameters& parameters);
    ~SliderContentModifier() override = default;

    void onDraw(DrawingContext& context) override;

    void DrawBackground(DrawingContext& context);
    void DrawStep(DrawingContext& context);
    void DrawSelect(DrawingContext& context);
    void DrawDefaultBlock(DrawingContext& context);
    void DrawHoverOrPress(DrawingContext& context);
    void DrawShadow(DrawingContext& context);

    void UpdateThemeColor()
    {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto sliderTheme = pipeline->GetTheme<SliderTheme>();
        CHECK_NULL_VOID(sliderTheme);
        blockOuterEdgeColor_ = sliderTheme->GetBlockOuterEdgeColor();
        stepSize_ = static_cast<float>(sliderTheme->GetMarkerSize().ConvertToPx());
        stepColor_ = sliderTheme->GetMarkerColor();
    }

    void UpdateData(const Parameters& parameters);
    void JudgeNeedAimate(const RefPtr<SliderPaintProperty>& property);

    void SetTrackThickness(float trackThickness)
    {
        if (trackThickness_) {
            trackThickness_->Set(trackThickness);
        }
    }

    void SetTrackBackgroundColor(Color color)
    {
        if (trackBackgroundColor_) {
            trackBackgroundColor_->Set(LinearColor(color));
        }
    }

    void SetSelectColor(Color color)
    {
        if (selectColor_) {
            selectColor_->Set(LinearColor(color));
        }
    }

    void SetBlockColor(Color color)
    {
        if (blockColor_) {
            blockColor_->Set(LinearColor(color));
        }
    }

    void SetBoardColor();

    void SetBackgroundSize(const PointF& start, const PointF& end)
    {
        if (backStart_) {
            backStart_->Set(start - PointF());
        }
        if (backEnd_) {
            backEnd_->Set(end - PointF());
        }
    }

    void SetSelectSize(const PointF& start, const PointF& end);

    void SetCircleCenter(const PointF& center);

    void SetBlockDiameter(float blockDiameter)
    {
        if (blockDiameter_) {
            blockDiameter_->Set(blockDiameter);
        }
    }

    void SetStepRatio(float stepRatio)
    {
        if (stepRatio_) {
            stepRatio_->Set(stepRatio);
        }
    }

    void SetNotAnimated()
    {
        needAnimate_ = false;
    }

    void SetAnimated()
    {
        needAnimate_ = true;
    }

    void SetShowSteps(bool showSteps)
    {
        if (isShowStep_) {
            isShowStep_->Set(showSteps);
        }
    }

    void SetDirection(Axis axis)
    {
        directionAxis_ = axis;
    }

private:
    // animatable property
    RefPtr<AnimatablePropertyOffsetF> selectStart_;
    RefPtr<AnimatablePropertyOffsetF> selectEnd_;
    RefPtr<AnimatablePropertyOffsetF> backStart_;
    RefPtr<AnimatablePropertyOffsetF> backEnd_;
    RefPtr<AnimatablePropertyOffsetF> circleCenter_;
    RefPtr<AnimatablePropertyFloat> trackThickness_;
    RefPtr<AnimatablePropertyColor> trackBackgroundColor_;
    RefPtr<AnimatablePropertyColor> selectColor_;
    RefPtr<AnimatablePropertyColor> blockColor_;
    RefPtr<AnimatablePropertyColor> boardColor_;
    // non-animatable property
    RefPtr<PropertyFloat> blockDiameter_;
    RefPtr<PropertyFloat> stepRatio_;
    RefPtr<PropertyBool> isShowStep_;
    // others
    bool mouseHoverFlag_ = false;
    bool mousePressedFlag_ = false;
    bool reverse_ = false;
    Axis directionAxis_ = Axis::HORIZONTAL;
    bool needAnimate_ = false; // Translate Animation on-off
    float hotCircleShadowWidth_ = 0.0f;
    Color blockOuterEdgeColor_;
    float stepSize_ = 0.0f;
    Color stepColor_;
    ACE_DISALLOW_COPY_AND_MOVE(SliderContentModifier);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_CONTENT_MODIFIER_H
