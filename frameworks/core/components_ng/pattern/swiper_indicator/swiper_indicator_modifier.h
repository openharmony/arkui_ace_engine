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
class SwiperIndicatorModifier : public ContentModifier {
    DECLARE_ACE_TYPE(SwiperIndicatorModifier, ContentModifier);

public:
    SwiperIndicatorModifier()
        : backgroundColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::TRANSPARENT)),
          vectorBlackPointCenterX_(AceType::MakeRefPtr<AnimatablePropertyVectorFloat>(LinearVector<float>(0))),
          longPointLeftCenterX_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          longPointRightCenterX_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          pointRadius_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          normalToHoverPointDilateRatio_(AceType::MakeRefPtr<AnimatablePropertyFloat>(1)),
          hoverToNormalPointDilateRatio_(AceType::MakeRefPtr<AnimatablePropertyFloat>(1)),
          longPointDilateRatio_(AceType::MakeRefPtr<AnimatablePropertyFloat>(1)),
          indicatorPadding_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          indicatorMargin_(AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF(0, 0))),
          isHorizontal_(AceType::MakeRefPtr<PropertyBool>(true))
    {
        AttachProperty(vectorBlackPointCenterX_);
        AttachProperty(longPointLeftCenterX_);
        AttachProperty(longPointRightCenterX_);
        AttachProperty(pointRadius_);
        AttachProperty(normalToHoverPointDilateRatio_);
        AttachProperty(hoverToNormalPointDilateRatio_);
        AttachProperty(longPointDilateRatio_);
        AttachProperty(backgroundColor_);
        AttachProperty(indicatorPadding_);
        AttachProperty(indicatorMargin_);
        AttachProperty(isHorizontal_);
    }
    ~SwiperIndicatorModifier() override = default;

    struct ContentProperty {
        Color backgroundColor = Color::TRANSPARENT;
        LinearVector<float> vectorBlackPointCenterX;
        float longPointLeftCenterX = 0;
        float longPointRightCenterX = 0;
        float pointRadius = 0;
        float normalToHoverPointDilateRatio = 1;
        float hoverToNormalPointDilateRatio = 1;
        float longPointDilateRatio = 0;
        float indicatorPadding = 0;
        OffsetF indicatorMargin = { 0, 0 };
    };

    void onDraw(DrawingContext& context) override;
    // paint
    void PaintContent(DrawingContext& context, ContentProperty& contentProperty);
    void PaintUnselectedIndicator(RSCanvas& canvas, const OffsetF& center, float radius);
    void PaintSelectedIndicator(RSCanvas& canvas, const OffsetF& leftCenter, const OffsetF& rightCenter, float radius);
    void PaintMask(DrawingContext& context);
    void PaintBackground(DrawingContext& context, const ContentProperty& contentProperty);
    float GetRadius(size_t index, ContentProperty& contentProperty);
    // Update property
    void UpdateShrinkPaintProperty(const OffsetF& margin, const float& normalPointRadius,
        const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX);
    void UpdateDilatePaintProperty(const float& hoverPointRadius, const LinearVector<float>& vectorBlackPointCenterX,
        const std::pair<float, float>& longPointCenterX);
    void UpdateBackgroundColor(const Color& backgroundColor);

    void UpdateNormalPaintProperty(const OffsetF& margin, const float& normalPointRadius,
        const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX);
    void UpdateHoverPaintProperty(const float& hoverPointRadius, const LinearVector<float>& vectorBlackPointCenterX,
        const std::pair<float, float>& longPointCenterX);
    void UpdatePressPaintProperty(const float& hoverPointRadius, const LinearVector<float>& vectorBlackPointCenterX,
        const std::pair<float, float>& longPointCenterX);
    // Update
    void UpdateNormalToHoverPaintProperty(const float& hoverPointRadius,
        const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX);
    void UpdateHoverToNormalPaintProperty(const OffsetF& margin, const float& normalPointRadius,
        const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX);
    void UpdateNormalToPressPaintProperty(const float& hoverPointRadius,
        const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX);
    void UpdatePressToNormalPaintProperty(const OffsetF& margin, const float& normalPointRadius,
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

    void SetAxis(Axis axis)
    {
        axis_ = axis;
    }

    void SetUnselectedColor(const Color& unselectedColor)
    {
        unselectedColor_ = unselectedColor;
    }

    void SetSelectedColor(const Color& selectedColor)
    {
        selectedColor_ = selectedColor;
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

    void SetIsHorizontal_(bool isHorizontal)
    {
        if (isHorizontal_) {
            isHorizontal_->Set(isHorizontal);
        }
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
    RefPtr<AnimatablePropertyFloat> pointRadius_;
    RefPtr<AnimatablePropertyFloat> normalToHoverPointDilateRatio_;
    RefPtr<AnimatablePropertyFloat> hoverToNormalPointDilateRatio_;
    RefPtr<AnimatablePropertyFloat> longPointDilateRatio_;
    RefPtr<AnimatablePropertyFloat> indicatorPadding_;
    RefPtr<AnimatablePropertyOffsetF> indicatorMargin_;
    RefPtr<PropertyBool> isHorizontal_;

    float centerY_ = 0;
    Axis axis_ = Axis::HORIZONTAL;
    Color unselectedColor_ = Color::TRANSPARENT;
    Color selectedColor_ = Color::TRANSPARENT;
    std::optional<int32_t> normalToHoverIndex_ = std::nullopt;
    std::optional<int32_t> hoverToNormalIndex_ = std::nullopt;
    bool longPointIsHover_ = false;
    bool isHover_ = false;
    bool isPressed_ = false;

    bool indicatorMask_ = false;
    OffsetF offset_;
    ACE_DISALLOW_COPY_AND_MOVE(SwiperIndicatorModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_MODIFIER_H
