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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_ARC_SWIPER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_ARC_SWIPER_PATTERN_H

#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {
constexpr int32_t ARC_SWIPER_PROPORTION = 4;    //The critical point of arc_swiper is 1/4 screen
class ArcSwiperPattern : public SwiperPattern {
    DECLARE_ACE_TYPE(ArcSwiperPattern, SwiperPattern);
public:
    ArcSwiperPattern()
    {
        swiperProportion_ = ARC_SWIPER_PROPORTION;
    }
    void SaveCircleDotIndicatorProperty(const RefPtr<FrameNode>& indicatorNode) override;
    void SetSwiperArcDotParameters(const SwiperArcDotParameters& swiperArcDotParameters) override;
    std::string GetArcDotIndicatorStyle() const override;
    std::shared_ptr<SwiperArcDotParameters> GetSwiperArcDotParameters() const override;

private:
    std::string GradientToJson(Gradient colors) const;
    mutable std::shared_ptr<SwiperArcDotParameters> swiperArcDotParameters_;
    enum AnimationType {
        TYPE_SCALE,
        TYPE_OFFSET,
        TYPE_BLUR,
        TYPE_COLOR,
        TYPE_ALPHA
    };

    struct AnimationParam {
        AnimationOption option;
        RefPtr<FrameNode> frameNode;
        AnimationType type;
        float scaleValue;
        float opacityValue;
        float blurValue;
        Color backColor;
        OffsetF offset;
    };
    
    void PlayDisplacementAnimation(SwiperLayoutAlgorithm::PositionMap &positionMap, const OffsetF& offset) override;
    void PlayHorizontalEntryAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode);
    void PlayHorizontalExitAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode);
    
    void PlayVerticalExitAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode);
    void PlayVerticalEntryAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode);
   
    void PlayAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode, int32_t index);
    void PlayHorizontalAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode, int32_t index);
    void PlayVerticalAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode, int32_t index);

    std::shared_ptr<AnimationUtils::Animation> Animation(const AnimationParam &param);
    bool IsPreItem(int32_t index);
    bool IsScrollOverCritical();
    
    Color GetBackgroundColorValue(const RefPtr<FrameNode>& frameNode);

    Color preNodeBackgroundColor_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_ARC_SWIPER_PATTERN_H