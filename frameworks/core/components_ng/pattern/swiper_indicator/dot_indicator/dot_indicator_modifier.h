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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_MODIFIER_H

#include <optional>

#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_property.h"
#include "core/components_ng/render/animation_utils.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/paint_wrapper.h"

namespace OHOS::Ace::NG {
constexpr int32_t ITEM_SIZE = 4;
constexpr float INIT_SIZE_RATE = 1.0f;

enum class TouchBottomType {
    NONE = 0,
    START,
    END,
};

enum class TouchBottomAnimationStage {
    STAGE_NONE,
    STAGE_SHRINKT_TO_BLACK_POINT,
    STAGE_EXPAND_TO_LONG_POINT,
};

class DotIndicatorModifier : public ContentModifier {
    DECLARE_ACE_TYPE(DotIndicatorModifier, ContentModifier);
public:
    DotIndicatorModifier()
        : backgroundColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::TRANSPARENT)),
          vectorBlackPointCenterX_(AceType::MakeRefPtr<AnimatablePropertyVectorFloat>(LinearVector<float>(0))),
          longPointLeftCenterX_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          longPointRightCenterX_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          normalToHoverPointDilateRatio_(AceType::MakeRefPtr<AnimatablePropertyFloat>(1)),
          hoverToNormalPointDilateRatio_(AceType::MakeRefPtr<AnimatablePropertyFloat>(1)),
          longPointDilateRatio_(AceType::MakeRefPtr<AnimatablePropertyFloat>(1)),
          indicatorPadding_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          indicatorMargin_(AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF(0, 0))),
          itemHalfSizes_(AceType::MakeRefPtr<AnimatablePropertyVectorFloat>(LinearVector<float>(ITEM_SIZE))),
          backgroundWidthDilateRatio_(AceType::MakeRefPtr<AnimatablePropertyFloat>(1)),
          backgroundHeightDilateRatio_(AceType::MakeRefPtr<AnimatablePropertyFloat>(1)),
          isFocused_(AceType::MakeRefPtr<PropertyBool>(false)),
          unselectedColor_(AceType::MakeRefPtr<PropertyColor>(Color::TRANSPARENT)),
          selectedColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::TRANSPARENT)),
          touchBottomPointColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::TRANSPARENT))
    {
        AttachProperty(vectorBlackPointCenterX_);
        AttachProperty(longPointLeftCenterX_);
        AttachProperty(longPointRightCenterX_);
        AttachProperty(normalToHoverPointDilateRatio_);
        AttachProperty(hoverToNormalPointDilateRatio_);
        AttachProperty(longPointDilateRatio_);
        AttachProperty(backgroundColor_);
        AttachProperty(indicatorPadding_);
        AttachProperty(indicatorMargin_);
        AttachProperty(itemHalfSizes_);
        AttachProperty(isFocused_);
        AttachProperty(unselectedColor_);
        AttachProperty(selectedColor_);
        AttachProperty(backgroundWidthDilateRatio_);
        AttachProperty(backgroundHeightDilateRatio_);
        AttachProperty(touchBottomPointColor_);
    }
    ~DotIndicatorModifier() override = default;

    struct ContentProperty {
        Color backgroundColor = Color::TRANSPARENT;
        LinearVector<float> vectorBlackPointCenterX;
        LinearVector<float> unselectedIndicatorWidth;
        LinearVector<float> unselectedIndicatorHeight;
        LinearVector<float> itemHalfSizes = {};
        float longPointLeftCenterX = 0;
        float longPointRightCenterX = 0;
        float normalToHoverPointDilateRatio = 1;
        float hoverToNormalPointDilateRatio = 1;
        float longPointDilateRatio = 0;
        float indicatorPadding = 0;
        OffsetF indicatorMargin = { 0, 0 };
        float theFirstPointMove = 0;
        float theSecondPointMove = 0;
        float theThirdPointMove = 0;
        float fourthPointMove = 0;
        float fifthPointMove = 0;
        float sixthPointMove = 0;
        float seventhPointMove = 0;
        float eighthPointMove = 0;
        float ninthPointMove = 0;
        float newPointMove = 0;
        float leftSecondPointSizeRate = INIT_SIZE_RATE;
        float leftThirdPointSizeRate = INIT_SIZE_RATE;
        float rightSecondPointSizeRate = INIT_SIZE_RATE;
        float rightFirstPointSizeRate = INIT_SIZE_RATE;
        uint8_t firstPointOpacity = 0;
        uint8_t newPointOpacity = 0;
    };

    std::tuple<float, float, float, float> CalCBoundsRect();
    void onDraw(DrawingContext& context) override;
    // paint
    virtual void PaintContent(DrawingContext& context, ContentProperty& contentProperty);
    void PaintUnselectedIndicator(RSCanvas& canvas, const OffsetF& center,
        const LinearVector<float>& itemHalfSizes,
        bool currentIndexFlag, const LinearColor& indicatorColor);
    void PaintSelectedIndicator(RSCanvas& canvas, const OffsetF& leftCenter, const OffsetF& rightCenter,
        const LinearVector<float>& itemHalfSizes, bool isOverlong = false);
    void PaintMask(DrawingContext& context);
    void PaintBackground(DrawingContext& context, ContentProperty& contentProperty);
    void CalCBackground(ContentProperty& contentProperty);
    virtual LinearVector<float> GetItemHalfSizes(size_t index, ContentProperty& contentProperty);
    void SetFocusedAndSelectedColor(ContentProperty& contentProperty);
    // Update property
    void UpdateShrinkPaintProperty(const OffsetF& margin, const LinearVector<float>& normalItemHalfSizes,
        const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX);
    void UpdateDilatePaintProperty(const LinearVector<float>& hoverItemHalfSizes,
        const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX);
    void UpdateBackgroundColor(const Color& backgroundColor);

    void UpdateNormalPaintProperty(const OffsetF& margin, const LinearVector<float>& normalItemHalfSizes,
        const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX);
    void UpdateHoverPaintProperty(const LinearVector<float>& hoverItemHalfSizes,
        const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX);
    void UpdatePressPaintProperty(const LinearVector<float>& hoverItemHalfSizes,
        const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX);
    // Update
    void UpdateNormalToHoverPaintProperty(const LinearVector<float>& hoverItemHalfSizes,
        const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX);
    void UpdateHoverToNormalPaintProperty(const OffsetF& margin, const LinearVector<float>& normalItemHalfSizes,
        const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX);
    void UpdateNormalToPressPaintProperty(const LinearVector<float>& hoverItemHalfSizes,
        const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX);
    void UpdatePressToNormalPaintProperty(const OffsetF& margin, const LinearVector<float>& normalItemHalfSizes,
        const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX);
    void UpdateHoverAndPressConversionPaintProperty();

    // Point dilate ratio
    void UpdateNormalToHoverPointDilateRatio();
    void UpdateHoverToNormalPointDilateRatio();
    void UpdateLongPointDilateRatio();

    void UpdateAllPointCenterXAnimation(GestureState gestureState, const LinearVector<float>& vectorBlackPointCenterX,
        const std::pair<float, float>& longPointCenterX);

    // Touch bottom animation
    void UpdateTouchBottomAnimation(TouchBottomType touchBottomType, const LinearVector<float>& vectorBlackPointCenterX,
        const std::pair<float, float>& longPointCenterX, float touchBottomRate);

    void SetAxis(Axis axis)
    {
        axis_ = axis;
    }

    void SetUnselectedColor(const Color& unselectedColor)
    {
        if (unselectedColor_) {
            unselectedColor_->Set(unselectedColor);
            originalUnselectColor_ = unselectedColor_->Get();
        }
    }

    void SetSelectedColor(const Color& selectedColor)
    {
        if (selectedColor_ && isSelectedColorAnimEnd_) {
            selectedColor_->Set(LinearColor(selectedColor));
            originalSelectColor_ = selectedColor_->Get().ToColor();
        }
        if (touchBottomPointColor_ && isSelectedColorAnimEnd_) {
            touchBottomPointColor_->Set(LinearColor(selectedColor));
        }
    }

    void SetCurrentIndex(int32_t index)
    {
        currentIndex_ = index;
    }

    void SetCurrentIndexActual(int32_t currentIndexActual)
    {
        currentIndexActual_ = currentIndexActual;
    }

    void SetNormalToHoverIndex(const std::optional<int32_t>& normalToHoverIndex)
    {
        normalToHoverIndex_ = normalToHoverIndex;
    }

    void SetIsFocused(bool isFocused)
    {
        if (isFocused_) {
            isFocused_->Set(isFocused);
        }
    }

    void SetHoverToNormalIndex(const std::optional<int32_t>& hoverToNormalIndex)
    {
        hoverToNormalIndex_ = hoverToNormalIndex;
    }

    std::optional<int32_t> GetNormalToHoverIndex()
    {
        return normalToHoverIndex_;
    }

    std::optional<int32_t> GetHoverToNormalIndex()
    {
        return hoverToNormalIndex_;
    }

    void SetIndicatorMask(bool indicatorMask)
    {
        indicatorMask_ = indicatorMask;
    }

    void SetOffset(const OffsetF& offset)
    {
        offset_ = offset;
    }

    void SetCenterY(const float& centerY)
    {
        centerY_ = centerY;
    }

    void SetIsHover(bool isHover)
    {
        isHover_ = isHover;
    }

    bool GetIsHover() const
    {
        return isHover_;
    }

    void SetIsPressed(bool isPressed)
    {
        isPressed_ = isPressed;
    }

    bool GetIsPressed() const
    {
        return isPressed_;
    }

    void SetLongPointIsHover(bool isHover)
    {
        longPointIsHover_ = isHover;
    }

    bool GetLongPointIsHover() const
    {
        return longPointIsHover_;
    }

    void SetItemWidth(const float itemWidth)
    {
        itemWidth_ = itemWidth;
    }

    void SetItemHeight(const float itemHeight)
    {
        itemHeight_ = itemHeight;
    }

    void SetSelectedItemWidth(const float selectedItemWidth)
    {
        selectedItemWidth_ = selectedItemWidth;
    }

    void SetSelectedItemHeight(const float selectedItemHeight)
    {
        selectedItemHeight_ = selectedItemHeight;
    }

    void SetIsIndicatorCustomSize(bool isCustomSize)
    {
        isCustomSize_ = isCustomSize;
    }

    void SetAnimationDuration(int32_t duration)
    {
        animationDuration_ = duration;
    }

    inline void UpdateVectorBlackPointCenterX(const LinearVector<float>& value)
    {
        vectorBlackPointCenterX_->Set(value);
    }

    std::pair<float, float> GetLongPointCenterX()
    {
        return { longPointLeftCenterX_->Get(), longPointRightCenterX_->Get() };
    }

    void PlayIndicatorAnimation(const LinearVector<float>& vectorBlackPointCenterX,
        const std::vector<std::pair<float, float>>& longPointCenterX, GestureState gestureState,
        TouchBottomTypeLoop touchBottomTypeLoop);
    virtual void StopAnimation(bool ifImmediately = false);
    void SetLongPointHeadCurve(RefPtr<Curve> curve, float motionVelocity)
    {
        headCurve_ = curve;
        motionVelocity_ = motionVelocity;
    }

    void SetUserSetSwiperCurve(RefPtr<Curve> userSetSwiperCurve)
    {
        userSetSwiperCurve_ = userSetSwiperCurve;
    }

    void SetIndicatorDotItemSpace(const Dimension& indicatorDotItemSpace)
    {
        indicatorDotItemSpace_ = indicatorDotItemSpace;
    }

    const Dimension& GetIndicatorDotItemSpace() const
    {
        return indicatorDotItemSpace_;
    }

    std::pair<float, float> GetTargetCenter() const
    {
        return bottomCenterX_;
    }

    bool GetIsBottomAnimationFinished() const
    {
        return isBottomAnimationFinished_;
    }

    RectF GetBoundsRect() const
    {
        return boundsRectF_;
    }
    void FinishAnimationToTargetImmediately(std::pair<float, float> centerX);
protected:
    static RefPtr<OHOS::Ace::SwiperIndicatorTheme> GetSwiperIndicatorTheme()
    {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, nullptr);
        auto swiperTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
        CHECK_NULL_RETURN(swiperTheme, nullptr);
        return swiperTheme;
    }

    void PlayBlackPointsAnimation(const LinearVector<float>& vectorBlackPointCenterX);
    void PlayLongPointAnimation(const std::vector<std::pair<float, float>>& longPointCenterX, GestureState gestureState,
        TouchBottomTypeLoop touchBottomTypeLoop, const LinearVector<float>& vectorBlackPointCenterX,
        bool isNormal = true);
    void PlayTouchBottomAnimation(const std::vector<std::pair<float, float>>& longPointCenterX,
        TouchBottomTypeLoop touchBottomTypeLoop, const LinearVector<float>& vectorBlackPointCenterX);
    void PlayOpacityAnimation();
    std::pair<float, float> GetTouchBottomCenterX(ContentProperty& contentProperty);
    int32_t GetLoopTranslateDuration() const;
    int32_t GetLoopOpacityDuration() const;
    float CalculateMinimumAmplitudeRatio(
        const std::vector<std::pair<float, float>>& longPointCenterX, GestureState gestureState) const;
    RefPtr<InterpolatingSpring> GetTailCurve();
    AnimationOption CreateTailOption(
        const std::vector<std::pair<float, float>>& longPointCenterX, GestureState gestureState, bool isNormal);
    std::tuple<float, float, float, float> CalcAndAdjustIndicatorPaintRect(
        const ContentProperty& contentProperty, float& rectWidth, float& rectHeight);

    RefPtr<AnimatablePropertyColor> backgroundColor_;
    RefPtr<AnimatablePropertyVectorFloat> vectorBlackPointCenterX_;
    RefPtr<AnimatablePropertyFloat> longPointLeftCenterX_;
    RefPtr<AnimatablePropertyFloat> longPointRightCenterX_;
    RefPtr<AnimatablePropertyFloat> normalToHoverPointDilateRatio_;
    RefPtr<AnimatablePropertyFloat> hoverToNormalPointDilateRatio_;
    RefPtr<AnimatablePropertyFloat> longPointDilateRatio_;
    RefPtr<AnimatablePropertyFloat> indicatorPadding_;
    RefPtr<AnimatablePropertyOffsetF> indicatorMargin_;
    RefPtr<AnimatablePropertyVectorFloat> itemHalfSizes_;
    RefPtr<AnimatablePropertyFloat> backgroundWidthDilateRatio_;
    RefPtr<AnimatablePropertyFloat> backgroundHeightDilateRatio_;
    RefPtr<PropertyBool> isFocused_;

    RefPtr<Curve> headCurve_;
    RefPtr<Curve> userSetSwiperCurve_;
    float motionVelocity_ = 0;

    float centerY_ = 0;
    Axis axis_ = Axis::HORIZONTAL;
    RefPtr<PropertyColor> unselectedColor_;
    RefPtr<AnimatablePropertyColor> selectedColor_;
    bool isSelectedColorAnimEnd_ = true;
    RefPtr<AnimatablePropertyColor> touchBottomPointColor_;
    bool isTouchBottomLoop_ = false;
    bool ifNeedFinishCallback_ = false;
    bool isBottomAnimationFinished_ = true;
    std::pair<float, float> bottomCenterX_;
    TouchBottomAnimationStage animationState_ = TouchBottomAnimationStage::STAGE_NONE;
    std::optional<int32_t> normalToHoverIndex_ = std::nullopt;
    std::optional<int32_t> hoverToNormalIndex_ = std::nullopt;
    bool longPointIsHover_ = false;
    bool isHover_ = false;
    bool isPressed_ = false;
    bool longPointLeftAnimEnd_ = true;
    bool longPointRightAnimEnd_ = true;

    bool indicatorMask_ = false;
    bool isCustomSize_ = false;
    int32_t currentIndex_ = 0;
    int32_t currentIndexActual_ = 0;
    int32_t animationDuration_ = 0;
    OffsetF offset_;
    float itemWidth_ = 0.0f;
    float itemHeight_ = 0.0f;
    float selectedItemWidth_ = 0.0f;
    float selectedItemHeight_ = 0.0f;
    Color originalUnselectColor_;
    Color originalSelectColor_;
    Dimension paddingSide_;
    Dimension indicatorDotItemSpace_ = 8.0_vp;
    float scaleIndicator_ = 1.33f;
    RectF boundsRectF_;
    TouchBottomType touchBottomType_ = TouchBottomType::NONE;
    float rectLeft_ = 0.0f;
    float rectRight_ = 0.0f;
    float rectTop_ = 0.0f;
    float rectBottom_ = 0.0f;
    float rectWidth_ = 0.0f;
    float rectHeight_ = 0.0f;
    LinearVector<float> targetVectorBlackPointCenterX_;
    ACE_DISALLOW_COPY_AND_MOVE(DotIndicatorModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_MODIFIER_H
