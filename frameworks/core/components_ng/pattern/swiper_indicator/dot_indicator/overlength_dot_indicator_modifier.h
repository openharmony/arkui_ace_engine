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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_OVER_INDICATOR_SWIPER_INDICATOR_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_OVER_INDICATOR_SWIPER_INDICATOR_MODIFIER_H

#include <optional>

#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_modifier.h"
namespace OHOS::Ace::NG {
constexpr float ONE_IN_TWO = 0.5f;
constexpr float THREE_QUARTERS = 0.75f;
class OverlengthDotIndicatorModifier : public DotIndicatorModifier {
    DECLARE_ACE_TYPE(OverlengthDotIndicatorModifier, DotIndicatorModifier);

public:
    OverlengthDotIndicatorModifier()
        : DotIndicatorModifier(),
          theFirstPointMove_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          theSecondPointMove_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          theThirdPointMove_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          fourthPointMove_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          fifthPointMove_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          sixthPointMove_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          seventhPointMove_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          eighthPointMove_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          ninthPointMove_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          newPointMove_(AceType::MakeRefPtr<AnimatablePropertyFloat>(0)),
          leftSecondPointSizeRate_(AceType::MakeRefPtr<AnimatablePropertyFloat>(ONE_IN_TWO)),
          leftThirdPointSizeRate_(AceType::MakeRefPtr<AnimatablePropertyFloat>(THREE_QUARTERS)),
          rightSecondPointSizeRate_(AceType::MakeRefPtr<AnimatablePropertyFloat>(THREE_QUARTERS)),
          rightFirstPointSizeRate_(AceType::MakeRefPtr<AnimatablePropertyFloat>(ONE_IN_TWO)),
          firstPointColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::TRANSPARENT)),
          newPointColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::TRANSPARENT))
    {
        AttachProperty(theFirstPointMove_);
        AttachProperty(theSecondPointMove_);
        AttachProperty(theThirdPointMove_);
        AttachProperty(fourthPointMove_);
        AttachProperty(fifthPointMove_);
        AttachProperty(sixthPointMove_);
        AttachProperty(seventhPointMove_);
        AttachProperty(eighthPointMove_);
        AttachProperty(ninthPointMove_);
        AttachProperty(newPointMove_);
        AttachProperty(leftSecondPointSizeRate_);
        AttachProperty(leftThirdPointSizeRate_);
        AttachProperty(rightFirstPointSizeRate_);
        AttachProperty(rightSecondPointSizeRate_);
        AttachProperty(firstPointColor_);
        AttachProperty(newPointColor_);
    }
    ~OverlengthDotIndicatorModifier() override = default;

    void onDraw(DrawingContext& context) override;
    // paint
    void PaintContent(DrawingContext& context, ContentProperty& contentProperty) override;
    void PaintBlackPoint(DrawingContext& context, ContentProperty& contentProperty);
    void PaintUnselectedIndicator(RSCanvas& canvas, const OffsetF& center, const LinearVector<float>& itemHalfSizes,
        bool currentIndexFlag, const LinearColor& indicatorColor) override;
    LinearVector<float> GetItemHalfSizes(size_t index, ContentProperty& contentProperty) override;
    // Update property
    void UpdateShrinkPaintProperty(const OffsetF& margin, const LinearVector<float>& normalItemHalfSizes,
        const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX) override;
    void UpdateMaxDisplayProperty(const LinearVector<float>& vectorBlackPointCenterX);

    void UpdateNormalPaintProperty(const OffsetF& margin, const LinearVector<float>& normalItemHalfSizes,
        const LinearVector<float>& vectorBlackPointCenterX, const std::pair<float, float>& longPointCenterX) override;
    void SetRealItemCount(int32_t realItemCount)
    {
        realItemCount_ = realItemCount;
    }
   
    void SetMaxDisplayCount(int32_t maxDisplayCount)
    {
        maxDisplayCount_ = maxDisplayCount;
    }
    void PlayIndicatorAnimation(const LinearVector<float>& vectorBlackPointCenterX,
        const std::vector<std::pair<float, float>>& longPointCenterX, GestureState gestureState,
        TouchBottomTypeLoop touchBottomTypeLoop) override;
private:
    void PlayBlackPointsAnimation(const LinearVector<float>& vectorBlackPointCenterX) override;
    void PlayPointOpacityAnimation();
    void UpdateDisplayProperty(const LinearVector<float>& vectorBlackPointCenterX,
        const float variableOffset);
    void StopAnimation(bool ifImmediately) override;
    RefPtr<AnimatablePropertyFloat> theFirstPointMove_;
    RefPtr<AnimatablePropertyFloat> theSecondPointMove_;
    RefPtr<AnimatablePropertyFloat> theThirdPointMove_;
    RefPtr<AnimatablePropertyFloat> fourthPointMove_;
    RefPtr<AnimatablePropertyFloat> fifthPointMove_;
    RefPtr<AnimatablePropertyFloat> sixthPointMove_;
    RefPtr<AnimatablePropertyFloat> seventhPointMove_;
    RefPtr<AnimatablePropertyFloat> eighthPointMove_;
    RefPtr<AnimatablePropertyFloat> ninthPointMove_;
    RefPtr<AnimatablePropertyFloat> newPointMove_;
    RefPtr<AnimatablePropertyFloat> leftSecondPointSizeRate_;
    RefPtr<AnimatablePropertyFloat> leftThirdPointSizeRate_;
    RefPtr<AnimatablePropertyFloat> rightSecondPointSizeRate_;
    RefPtr<AnimatablePropertyFloat> rightFirstPointSizeRate_;
    RefPtr<AnimatablePropertyColor> firstPointColor_;
    RefPtr<AnimatablePropertyColor> newPointColor_;
    int32_t maxDisplayCount_ = 0;
    int32_t realItemCount_ = 0;
    ACE_DISALLOW_COPY_AND_MOVE(OverlengthDotIndicatorModifier);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_OVER_INDICATOR_SWIPER_INDICATOR_MODIFIER_H
