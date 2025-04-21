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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_OVER_INDICATOR_DOT_INDICATOR_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_OVER_INDICATOR_DOT_INDICATOR_PAINT_METHOD_H

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/overlength_dot_indicator_modifier.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_method.h"
namespace OHOS::Ace::NG {
constexpr int32_t DISPLAY_COUNT_MIN = 6;
constexpr int32_t DISPLAY_COUNT_MAX = 9;
constexpr int32_t NUMBER_ONE = 1;
class ACE_EXPORT OverlengthDotIndicatorPaintMethod : public DotIndicatorPaintMethod {
    DECLARE_ACE_TYPE(OverlengthDotIndicatorPaintMethod, DotIndicatorPaintMethod)
public:
    explicit OverlengthDotIndicatorPaintMethod(const RefPtr<OverlengthDotIndicatorModifier>& dotIndicatorModifier)
        : dotIndicatorModifier_(dotIndicatorModifier)
    {}
    ~OverlengthDotIndicatorPaintMethod() override = default;

    RefPtr<Modifier> GetContentModifier(PaintWrapper* paintWrapper) override
    {
        CHECK_NULL_RETURN(dotIndicatorModifier_, nullptr);
        return dotIndicatorModifier_;
    }

    void UpdateContentModifier(PaintWrapper* paintWrapper) override;
    void PaintNormalIndicator(const PaintWrapper* paintWrapper) override;
    std::pair<float, float> CalculatePointCenterX(
        const LinearVector<float>& itemHalfSizes, float margin, float padding, float space, int32_t index) override;

    void CalculateNormalMargin(const LinearVector<float>& itemHalfSizes, const SizeF& frameSize,
        const int32_t displayCount, const Dimension& indicatorDotItemSpace, bool ignoreSize) override;
    void SetMaxDisplayCount(int32_t maxDisplayCount)
    {
        if (maxDisplayCount >= DISPLAY_COUNT_MIN && maxDisplayCount <= DISPLAY_COUNT_MAX) {
            maxDisplayCount_ = maxDisplayCount;
            realItemCount_ = itemCount_;
            itemCount_ = maxDisplayCount_ < itemCount_ ? maxDisplayCount_ + NUMBER_ONE : itemCount_;
        }
    }

    void SetAnimationStartIndex(int32_t animationStartIndex)
    {
        animationStartIndex_ = animationStartIndex;
    }

    void SetAnimationEndIndex(int32_t animationEndIndex)
    {
        animationEndIndex_ = animationEndIndex;
    }

    void SetKeepStatus(bool keepStatus)
    {
        keepStatus_ = keepStatus;
    }

    void SetIsBindIndicator(bool isBindIndicator)
    {
        isBindIndicator_ = isBindIndicator;
    }

private:
    std::pair<float, float> CalculatePointCenterX(const StarAndEndPointCenter& starAndEndPointCenter,
        const LinearVector<float>& startVectorBlackPointCenterX,
        const LinearVector<float>& endVectorBlackPointCenterX) override;
    std::tuple<std::pair<float, float>, LinearVector<float>> CalculateLongPointCenterX(
        const PaintWrapper* paintWrapper) override;
    std::pair<float, float> ForwardCalculation(
        const LinearVector<float>& itemHalfSizes, float startCenterX,
        float endCenterX, float space, int32_t index) override;
    void UpdateNormalIndicator(LinearVector<float>& itemHalfSizes, const PaintWrapper* paintWrapper) override;
    void AnalysisIndexRange(int32_t& nposStation);

    RefPtr<OverlengthDotIndicatorModifier> dotIndicatorModifier_;
    LinearVector<float> vectorBlackPointBegCenterX_ = {};
    LinearVector<float> animationStartCenterX_ = {};
    LinearVector<float> animationEndCenterX_ = {};
    LinearVector<float> animationStartIndicatorWidth_ = {};
    LinearVector<float> animationEndIndicatorWidth_ = {};
    LinearVector<float> animationStartIndicatorHeight_ = {};
    LinearVector<float> animationEndIndicatorHeight_ = {};
    int32_t maxDisplayCount_ = 0;
    int32_t realItemCount_ = 0;
    int32_t animationStartIndex_ = 0;
    int32_t animationEndIndex_ = 0;
    bool keepStatus_ = false;
    bool isBindIndicator_ = false;
    std::pair<float, float> overlongSelectedCenterX_ = { 0.0f, 0.0f};
    ACE_DISALLOW_COPY_AND_MOVE(OverlengthDotIndicatorPaintMethod);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_OVER_INDICATOR_DOT_INDICATOR_PAINT_METHOD_H