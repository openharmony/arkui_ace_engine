/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_CIRCLE_DOT_INDICATOR_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_CIRCLE_DOT_INDICATOR_MODIFIER_H

#include <optional>

#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_modifier.h"
#include "core/components/declaration/swiper/swiper_declaration.h"

namespace OHOS::Ace::NG {
class CircleDotIndicatorModifier : public ContentModifier {
    DECLARE_ACE_TYPE(CircleDotIndicatorModifier, ContentModifier);
public:
    CircleDotIndicatorModifier();
    ~CircleDotIndicatorModifier() override = default;

    struct ContentProperty {
        Color backgroundColor = Color::TRANSPARENT;
        LinearVector<float> vectorBlackPointAngle;
        LinearVector<float> vectorBlackPointRadius;
        float dotPaddingAngle = 0;
        float dotActiveAngle = 0;
        float dotActiveStartAngle = 0;
        float dotActiveEndAngle = 0;

        float dotActivePaddingAngle = 0;
        float containerBorderWidth = 0;
        float itemRadius = 0;
        float itemSelectWidth = 0;
        float backgroundOffset = 0;
    };

    void onDraw(DrawingContext& context) override;
    // paint
    void PaintContent(DrawingContext& context, ContentProperty& contentProperty);
    void PaintUnselectedIndicator(RSCanvas& canvas, float itemAngle, float itemRadius, ContentProperty& contentProperty,
        const LinearColor& indicatorColor);
    void PaintSelectedIndicator(RSCanvas& canvas, ContentProperty& contentProperty);
    void PaintBackground(DrawingContext& context, const ContentProperty& contentProperty);
    void PaintBackgroundSetAngle(int32_t itemSize, float backgroundOffset, float& startAngle);
    float GetAllPointArcAngle(int32_t itemSize, float dotPaddingAngle,
                              float dotActivePaddingAngle, float dotActiveAngle);
    void PaintIndicatorMask(DrawingContext& context, const ContentProperty& contentProperty);
    // Update property
    void UpdateShrinkPaintProperty(const LinearVector<float>& normalItemSizes,
                                   const LinearVector<float>& vectorBlackPointAngle,
                                   const LinearVector<float>& vectorBlackPointRadius,
                                   const std::pair<float, float>& longPointAngle);
    void UpdateDilatePaintProperty(const LinearVector<float>& hoverItemSizes,
                                   const LinearVector<float>& vectorBlackPointAngle,
                                   const LinearVector<float>& vectorBlackPointRadius,
                                   const std::pair<float, float>& longPointAngle);
    void UpdateBackgroundColor(const Color& backgroundColor);

    void UpdateNormalPaintProperty(const LinearVector<float>& normalItemSizes,
                                   const LinearVector<float>& vectorBlackPointAngle,
                                   const LinearVector<float>& vectorBlackPointRadius,
                                   const std::pair<float, float>& longPointAngle);
    void UpdatePressPaintProperty(const LinearVector<float>& hoverItemSizes,
                                  const LinearVector<float>& vectorBlackPointAngle,
                                  const LinearVector<float>& vectorBlackPointRadius,
                                  const std::pair<float, float>& longPointAngle);
    // Update
    void UpdateNormalToPressPaintProperty(const LinearVector<float>& hoverItemSizes,
                                          const LinearVector<float>& vectorBlackPointAngle,
                                          const LinearVector<float>& vectorBlackPointRadius,
                                          const std::pair<float, float>& longPointAngle);
    void UpdatePressToNormalPaintProperty(const LinearVector<float>& normalItemSizes,
                                          const LinearVector<float>& vectorBlackPointAngle,
                                          const LinearVector<float>& vectorBlackPointRadius,
                                          const std::pair<float, float>& longPointAngle);
    void UpdateTouchBottomAnimation(const LinearVector<float> &vectorBlackPointCenterX,
                                    const std::pair<float, float> &longPointCenterX,
                                    float backgroundOffset);

    void SetAxis(Axis axis)
    {
        axis_ = axis;
    }

    void SetUnselectedColor(const Color& unselectedColor)
    {
        if (unselectedColor_) {
            unselectedColor_->Set(unselectedColor);
        }
    }

    void SetSelectedColor(const Color& selectedColor)
    {
        if (selectedColor_) {
            selectedColor_->Set(selectedColor);
        }
    }

    void SetCenterY(const float centerY)
    {
        centerY_ = centerY;
    }

    void SetCenterX(const float centerX)
    {
        centerX_ = centerX;
    }

    void SetCircleRadius(const float circleRadius)
    {
        circleRadius_ = circleRadius;
    }

    void SetIsPressed(bool isPressed)
    {
        isPressed_ = isPressed;
    }

    bool GetIsPressed() const
    {
        return isPressed_;
    }

    void PlayIndicatorAnimation(const LinearVector<float>& vectorBlackPointAngle,
        const LinearVector<float>& vectorBlackPointRadius, const std::pair<float, float>& longPointAngle,
        GestureState gestureState);
    void StopAnimation(bool ifImmediately = false);

    std::pair<float, float> GetLongPointAngle()
    {
        return { dotActiveStartAngle_->Get(), dotActiveEndAngle_->Get() };
    }

    void SetArcDirection(SwiperArcDirection arcDirection)
    {
        arcDirection_ = arcDirection;
    }

    void SetCurrentIndex(int32_t currentIndex)
    {
        currentIndex_ = currentIndex;
    }

    void SetMaskColor(const NG::Gradient& maskColor)
    {
        maskColor_ = maskColor;
        if (updateMaskColor_) {
            updateMaskColor_->Set(!updateMaskColor_->Get());
        }
    }

    void SetBackgroundColor(const Color& backgroundColor)
    {
        containerColor_ = backgroundColor;
    }

    void SetLongPointHeadCurve(RefPtr<Curve> curve)
    {
        headCurve_ = curve;
    }

    void SetIndicatorStartIndex(int32_t indicatorIndex)
    {
        indicatorStartIndex_ = indicatorIndex;
    }

    int32_t GetIndicatorStartIndex()
    {
        return indicatorStartIndex_;
    }

    void SetInitState(bool initState)
    {
        initState_ = initState;
    }

    bool GetInitState()
    {
        return initState_;
    }

    void SetTouchBottomRate(float touchBottomRate)
    {
        touchBottomRate_ = touchBottomRate;
    }

    void SetTouchBottomType(TouchBottomType touchBottomType)
    {
        touchBottomType_ = touchBottomType;
    }

private:
    void PlayBlackPointsAnimation(const LinearVector<float>& vectorBlackPointAngle,
                                  const LinearVector<float>& vectorBlackPointRadius);
    void PlayLongPointAnimation(const std::pair<float, float>& longPointAngle,
        GestureState gestureState, const LinearVector<float>& vectorBlackPointAngle);
    std::vector<GradientColor> GetMaskColor() const;
    Gradient SortGradientColorsByOffset(const Gradient& gradient) const;
    std::pair<PointF, PointF> GetArcPoint(const ContentProperty& contentProperty) const;

    RefPtr<AnimatablePropertyColor> backgroundColor_;
    RefPtr<AnimatablePropertyVectorFloat> vectorBlackPointAngle_;
    RefPtr<AnimatablePropertyVectorFloat> vectorBlackPointRadius_;
    RefPtr<PropertyColor> unselectedColor_;
    RefPtr<PropertyColor> selectedColor_;
    RefPtr<AnimatablePropertyFloat> dotPaddingAngle_;
    RefPtr<AnimatablePropertyFloat> dotActiveAngle_;
    
    RefPtr<AnimatablePropertyFloat> dotActiveStartAngle_;
    RefPtr<AnimatablePropertyFloat> dotActiveEndAngle_;
    RefPtr<AnimatablePropertyFloat> dotActivePaddingAngle_;
    RefPtr<AnimatablePropertyFloat> containerBorderWidth_;
    RefPtr<AnimatablePropertyFloat> itemRadius_;
    RefPtr<AnimatablePropertyFloat> itemSelectWidth_;
    RefPtr<AnimatablePropertyFloat> backgroundOffset_;
    RefPtr<PropertyBool> updateMaskColor_;
    Gradient maskColor_;

    std::shared_ptr<AnimationUtils::Animation> blackPointsAnimation_;

    Color containerColor_ = Color::TRANSPARENT;

    float centerX_ = 0.0;
    float centerY_ = 0.0;
    float circleRadius_ = 0.0;
    float touchBottomRate_ = 0.0f;
    int32_t indicatorStartIndex_ = 0;
    bool initState_ = true;

    SwiperArcDirection arcDirection_ = SwiperArcDirection::SIX_CLOCK_DIRECTION;

    Axis axis_ = Axis::HORIZONTAL;
    bool isPressed_ = false;
    bool longPointLeftAnimEnd_ = true;
    bool longPointRightAnimEnd_ = true;

    bool isFirstPaintLongPoint_ = true;
    float firstDotActiveStartAngle_ = 0.0f;
    float firstDotActiveEndAngle_ = 0.0f;

    int32_t currentIndex_ = 0;
    ACE_DISALLOW_COPY_AND_MOVE(CircleDotIndicatorModifier);
    RefPtr<Curve> headCurve_;
    TouchBottomType touchBottomType_ = TouchBottomType::NONE;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_CIRCLE_DOT_INDICATOR_MODIFIER_H
