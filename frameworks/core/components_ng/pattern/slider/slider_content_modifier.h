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
enum class SliderStatus : uint32_t {
    DEFAULT,
    CLICK,
    MOVE,
};
class SliderContentModifier : public ContentModifier {
    DECLARE_ACE_TYPE(SliderContentModifier, ContentModifier);

public:
    struct Parameters {
        float trackThickness = 0.0f;
        SizeF blockSize;
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
        Gradient trackBackgroundColor;
        Color blockColor;
    };

    explicit SliderContentModifier(const Parameters& parameters, std::function<void(float)> updateImageCenterX,
        std::function<void(float)> updateImageCenterY);
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
        blockShadowColor_ = sliderTheme->GetBlockShadowColor();
    }

    void UpdateData(const Parameters& parameters);
    void JudgeNeedAnimate(bool reverse);

    void SetTrackThickness(float trackThickness)
    {
        if (trackThickness_) {
            trackThickness_->Set(trackThickness);
        }
    }

    void SetTrackBackgroundColor(const Gradient& color)
    {
        CHECK_NULL_VOID(trackBackgroundColor_);
        trackBackgroundColor_->Set(GradientArithmetic(color));
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

    void SetStepRatio(float stepRatio)
    {
        if (stepRatio_) {
            stepRatio_->Set(stepRatio);
        }
    }

    void SetAnimatorStatus(SliderStatus status)
    {
        animatorStatus_ = status;
    }

    void SetSliderMode(SliderModelNG::SliderMode sliderMode)
    {
        if (sliderMode_) {
            sliderMode_->Set(static_cast<int>(sliderMode));
        }
    }

    void SetTrackBorderRadius(float trackBorderRadius)
    {
        if (trackBorderRadius_) {
            trackBorderRadius_->Set(trackBorderRadius);
        }
    }

    void SetSelectedBorderRadius(float selectedBorderRadius)
    {
        if (selectedBorderRadius_) {
            selectedBorderRadius_->Set(selectedBorderRadius);
        }
    }

    void SetStepSize(float stepSize)
    {
        if (stepSize_) {
            stepSize_->Set(stepSize);
        }
    }

    void SetStepColor(const Color& stepColor)
    {
        if (stepColor_) {
            stepColor_->Set(LinearColor(stepColor));
        }
    }

    void SetShowSteps(bool showSteps)
    {
        if (isShowStep_) {
            isShowStep_->Set(showSteps);
        }
    }

    void SetSliderInteractionMode(SliderModelNG::SliderInteraction mode)
    {
        if (sliderInteractionMode_) {
            sliderInteractionMode_->Set(static_cast<int>(mode));
        }
    }

    void SetMinResponsiveDistance(float minResponse)
    {
        if (minResponse_) {
            minResponse_->Set(minResponse);
        }
    }

    void SetBlockType(SliderModelNG::BlockStyleType type)
    {
        if (blockType_) {
            blockType_->Set(static_cast<int>(type));
        }
    }

    void SetBlockSize(const SizeF& blockSize)
    {
        if (blockSize_) {
            blockSize_->Set(blockSize);
        }
    }

    void SetBlockBorderColor(const Color& blockBorderColor)
    {
        if (blockBorderColor_) {
            blockBorderColor_->Set(LinearColor(blockBorderColor));
        }
    }

    void SetBlockBorderWidth(float blockBorderWidth)
    {
        if (blockBorderWidth_) {
            blockBorderWidth_->Set(blockBorderWidth);
        }
    }

    void SetBlockShape(const RefPtr<BasicShape>& shape);

    void SetDirection(Axis axis)
    {
        if (directionAxis_) {
            directionAxis_->Set(static_cast<int>(axis));
        }
    }

    PointF GetBlockCenter()
    {
        auto blockCenterX = blockCenterX_->Get();
        auto blockCenterY = blockCenterY_->Get();
        auto backStart = backStart_->Get();
        auto backEnd = backEnd_->Get();
        if (static_cast<Axis>(directionAxis_->Get()) == Axis::HORIZONTAL) {
            blockCenterX = std::clamp(blockCenterX, backStart.GetX(), backEnd.GetX());
        } else {
            blockCenterY = std::clamp(blockCenterY, backStart.GetY(), backEnd.GetY());
        }
        return { blockCenterX, blockCenterY };
    }

    float GetTrackThickness() const
    {
        return trackThickness_->Get();
    }

    SizeF GetBlockSize() const
    {
        return blockSize_->Get();
    }

    void SetVisible(bool isVisible)
    {
        CHECK_NULL_VOID(isVisible_ != isVisible);
        isVisible_ = isVisible;
    }

    bool GetVisible() const
    {
        return isVisible_;
    }

    void UpdateContentDirtyRect(const SizeF& frameSize);

    void SetUseContentModifier(bool useContentModifier)
    {
        if (useContentModifier_) {
            useContentModifier_->Set(useContentModifier);
        }
    }

    const std::vector<PointF>& GetStepPointVec() const
    {
        return stepPointVec_;
    }

private:
    void InitializeShapeProperty();
    RSRect GetTrackRect();
    std::vector<GradientColor> GetTrackBackgroundColor() const;
    Gradient SortGradientColorsByOffset(const Gradient& gradient) const;

    void DrawBlock(DrawingContext& context);
    void DrawBlockShape(DrawingContext& context);
    void DrawBlockShapeCircle(DrawingContext& context, RefPtr<Circle>& circle);
    void DrawBlockShapeEllipse(DrawingContext& context, RefPtr<Ellipse>& ellipse);
    void DrawBlockShapePath(DrawingContext& context, RefPtr<Path>& path);
    void DrawBlockShapeRect(DrawingContext& context, RefPtr<ShapeRect>& rect);
    void SetShapeRectRadius(RSRoundRect& roundRect, float borderWidth);
    void SetBlockClip(DrawingContext& context);
    void StopSelectAnimation();
    void StopCircleCenterAnimation();

private:
    std::function<void(float)> updateImageCenterX_;
    std::function<void(float)> updateImageCenterY_;

    // animatable property
    RefPtr<AnimatablePropertyOffsetF> selectStart_;
    RefPtr<AnimatablePropertyOffsetF> selectEnd_;
    RefPtr<AnimatablePropertyOffsetF> backStart_;
    RefPtr<AnimatablePropertyOffsetF> backEnd_;
    RefPtr<AnimatablePropertyFloat> blockCenterX_;
    RefPtr<AnimatablePropertyFloat> blockCenterY_;
    RefPtr<AnimatablePropertyFloat> trackThickness_;
    RefPtr<AnimatablePropertyVectorColor> trackBackgroundColor_;
    RefPtr<AnimatablePropertyColor> selectColor_;
    RefPtr<AnimatablePropertyColor> blockColor_;
    RefPtr<AnimatablePropertyColor> boardColor_;

    RefPtr<AnimatablePropertyFloat> trackBorderRadius_;
    RefPtr<AnimatablePropertyFloat> selectedBorderRadius_;
    RefPtr<AnimatablePropertyFloat> stepSize_;
    RefPtr<AnimatablePropertyColor> stepColor_;
    RefPtr<AnimatablePropertySizeF> blockSize_;
    RefPtr<AnimatablePropertyColor> blockBorderColor_;
    RefPtr<AnimatablePropertyFloat> blockBorderWidth_;
    RefPtr<AnimatablePropertyFloat> shapeWidth_;
    RefPtr<AnimatablePropertyFloat> shapeHeight_;
    RefPtr<AnimatablePropertyFloat> circleRadius_;
    RefPtr<AnimatablePropertyFloat> ellipseRadiusX_;
    RefPtr<AnimatablePropertyFloat> ellipseRadiusY_;
    RefPtr<AnimatablePropertyFloat> rectTopLeftRadiusX_;
    RefPtr<AnimatablePropertyFloat> rectTopLeftRadiusY_;
    RefPtr<AnimatablePropertyFloat> rectTopRightRadiusX_;
    RefPtr<AnimatablePropertyFloat> rectTopRightRadiusY_;
    RefPtr<AnimatablePropertyFloat> rectBottomLeftRadiusX_;
    RefPtr<AnimatablePropertyFloat> rectBottomLeftRadiusY_;
    RefPtr<AnimatablePropertyFloat> rectBottomRightRadiusX_;
    RefPtr<AnimatablePropertyFloat> rectBottomRightRadiusY_;
    // non-animatable property
    RefPtr<PropertyFloat> stepRatio_;
    RefPtr<PropertyInt> sliderMode_;
    RefPtr<PropertyInt> directionAxis_;
    RefPtr<PropertyBool> isShowStep_;
    RefPtr<PropertyInt> sliderInteractionMode_;
    RefPtr<PropertyFloat> minResponse_;
    RefPtr<PropertyInt> blockType_;
    RefPtr<PropertyBool> useContentModifier_;

    // others
    struct MarkerPenAndPath {
        RSPen pen;
        RSBrush brush;
        RSPath path;
    } markerPenAndPath;

    OffsetF targetSelectEnd_;
    PointF targetCenter_;
    bool isVisible_ = true;
    bool mouseHoverFlag_ = false;
    bool mousePressedFlag_ = false;
    bool reverse_ = false;
    SliderStatus animatorStatus_ = SliderStatus::DEFAULT; // Translate Animation on-off
    float hotCircleShadowWidth_ = 0.0f;
    Color blockOuterEdgeColor_;
    Color blockShadowColor_;
    RefPtr<BasicShape> shape_;
    std::vector<PointF> stepPointVec_;
    ACE_DISALLOW_COPY_AND_MOVE(SliderContentModifier);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SLIDER_SLIDER_CONTENT_MODIFIER_H
