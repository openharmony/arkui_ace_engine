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
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
enum class TouchBottomType {
    NONE = 0,
    START,
    END,
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
          itemHalfSizes_(AceType::MakeRefPtr<AnimatablePropertyVectorFloat>(LinearVector<float>(4))),
          backgroundWidthDilateRatio_(AceType::MakeRefPtr<AnimatablePropertyFloat>(1)),
          backgroundHeightDilateRatio_(AceType::MakeRefPtr<AnimatablePropertyFloat>(1)),
          unselectedColor_(AceType::MakeRefPtr<PropertyColor>(Color::TRANSPARENT)),
          selectedColor_(AceType::MakeRefPtr<PropertyColor>(Color::TRANSPARENT))
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
        AttachProperty(unselectedColor_);
        AttachProperty(selectedColor_);
        AttachProperty(backgroundWidthDilateRatio_);
        AttachProperty(backgroundHeightDilateRatio_);
    }
    ~DotIndicatorModifier() override = default;

    struct ContentProperty {
        Color backgroundColor = Color::TRANSPARENT;
        LinearVector<float> vectorBlackPointCenterX;
        LinearVector<float> itemHalfSizes = {};
        float longPointLeftCenterX = 0;
        float longPointRightCenterX = 0;
        float normalToHoverPointDilateRatio = 1;
        float hoverToNormalPointDilateRatio = 1;
        float longPointDilateRatio = 0;
        float indicatorPadding = 0;
        OffsetF indicatorMargin = { 0, 0 };
    };

    void onDraw(DrawingContext& context) override;
    // paint
    void PaintContent(DrawingContext& context, ContentProperty& contentProperty);
    void PaintUnselectedIndicator(
        RSCanvas& canvas, const OffsetF& center, const LinearVector<float>& itemHalfSizes, bool currentIndexFlag);
    void PaintSelectedIndicator(RSCanvas& canvas, const OffsetF& center, const OffsetF& leftCenter,
        const OffsetF& rightCenter, const LinearVector<float>& itemHalfSizes);
    void PaintMask(DrawingContext& context);
    void PaintBackground(DrawingContext& context, const ContentProperty& contentProperty);
    LinearVector<float> GetItemHalfSizes(size_t index, ContentProperty& contentProperty);
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

    void UpdateAllPointCenterXAnimation(bool isForward, const LinearVector<float>& vectorBlackPointCenterX,
        const std::pair<float, float>& longPointCenterX);

    void UpdateLongPointLeftCenterX(float longPointLeftCenterX, bool isAnimation);
    void UpdateLongPointRightCenterX(float longPointRightCenterX, bool isAnimation);

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
        }
    }

    void SetSelectedColor(const Color& selectedColor)
    {
        if (selectedColor_) {
            selectedColor_->Set(selectedColor);
        }
    }

    void SetCurrentIndex(int32_t index)
    {
        currentIndex_ = index;
    }

    void SetNormalToHoverIndex(const std::optional<int32_t>& normalToHoverIndex)
    {
        normalToHoverIndex_ = normalToHoverIndex;
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

private:
    static RefPtr<OHOS::Ace::SwiperIndicatorTheme> GetSwiperIndicatorTheme()
    {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipelineContext, nullptr);
        auto swiperTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
        CHECK_NULL_RETURN(swiperTheme, nullptr);
        return swiperTheme;
    }

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

    float centerY_ = 0;
    Axis axis_ = Axis::HORIZONTAL;
    RefPtr<PropertyColor> unselectedColor_;
    RefPtr<PropertyColor> selectedColor_;
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
    OffsetF offset_;
    float itemWidth_ = 0.0f;
    float itemHeight_ = 0.0f;
    float selectedItemWidth_ = 0.0f;
    float selectedItemHeight_ = 0.0f;
    TouchBottomType touchBottomType_ = TouchBottomType::NONE;
    ACE_DISALLOW_COPY_AND_MOVE(DotIndicatorModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_MODIFIER_H
