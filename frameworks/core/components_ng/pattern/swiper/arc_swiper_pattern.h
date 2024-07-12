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

    ~ArcSwiperPattern() {}
    void SaveCircleDotIndicatorProperty(const RefPtr<FrameNode>& indicatorNode) override;
    void SetSwiperArcDotParameters(const SwiperArcDotParameters& swiperArcDotParameters) override;
    std::string GetArcDotIndicatorStyle() const override;
    std::shared_ptr<SwiperArcDotParameters> GetSwiperArcDotParameters() const override;
    bool IsLoop() const override;

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

    enum AnimationFinishType {
        EXIT_SCALE,
        EXIT_OFFSET,
        EXIT_BLUR,
        EXIT_ALPHA,
        EXIT_BACKGROUND,

        ENTRY_SCALE,
        ENTRY_OFFSET,
        ENTRY_BLUR,
        ENTRY_ALPHA,
        ENTRY_BACKGROUND
    };

    void ResetAnimationParam() override;
    void ClearAnimationFinishList() override;
    void InitialFrameNodePropertyAnimation(const OffsetF& offset, RefPtr<FrameNode>& frameNode) override;
    void CancelFrameNodePropertyAnimation(RefPtr<FrameNode>& frameNode) override;
    void PlayPropertyTranslateAnimation(
        float translate, int32_t nextIndex, float velocity = 0.0f, bool stopAutoPlay = false) override;
    void PlayScrollAnimation() override;
    void HorizontalScrollAnimation();
    void PlayHorizontalScrollExitAnimation(float swiperWidth, float startPos, RefPtr<FrameNode>& frameNode);
    void PlayHorizontalScrollEntryAnimation(float swiperWidth, float startPos, RefPtr<FrameNode>& frameNode);
    
    void VerticalScrollAnimation();
    void PlayVerticalScrollExitAnimation(float swiperWidth, float startPos, RefPtr<FrameNode>& frameNode);
    void PlayVerticalScrollEntryAnimation(float swiperWidth, float startPosj, RefPtr<FrameNode>& frameNode);

    void PlayScrollScaleAnimation(float scale, RefPtr<RenderContext>& renderContext);
    void PlayScrollBlurAnimation(float blur, RefPtr<RenderContext>& renderContext);
    void PlayScrollAlpahAnimation(float alpha, RefPtr<RenderContext>& renderContext);
    void PlayScrollBackgroundAnimation(const Color& color, RefPtr<RenderContext>& renderContext);

    void PlayPropertyTranslateFlipAnimation(const OffsetF& offset);

    void PlayHorizontalEntryAnimation(const OffsetF& offset, RefPtr<FrameNode>& frameNode);
    void PlayHorizontalExitAnimation(const OffsetF& offset, RefPtr<FrameNode>& frameNode);
    
    void PlayVerticalExitAnimation(const OffsetF& offset, RefPtr<FrameNode>& frameNode);
    void PlayVerticalEntryAnimation(const OffsetF& offset, RefPtr<FrameNode>& frameNode);
   
    void PlayAnimation(const OffsetF& offset, int32_t index, RefPtr<FrameNode>& frameNode);
    void PlayHorizontalAnimation(const OffsetF& offset, int32_t index, RefPtr<FrameNode>& frameNode);
    void PlayVerticalAnimation(const OffsetF& offset, int32_t index, RefPtr<FrameNode>& frameNode);
   
    void AnimationFinish();
    void BuildAnimationFinishCallback(bool exit, AnimationParam& param, RefPtr<RenderContext>& renderContext,
        FinishCallback& finishCallback);
    void HandlePropertyTranslateCallback(float translate, int32_t nextIndex, float velocity);
    void AddFinishAnimation(const AnimationFinishType& animationFinishType);

    bool IsPreItem(int32_t index, float translate);
    bool IsScrollOverCritical();
    Color GetBackgroundColorValue(const RefPtr<FrameNode>& frameNode);
    std::shared_ptr<AnimationUtils::Animation> Animation(bool exit, AnimationParam& param);
    void ResetBackcolor();

    Color preNodeBackgroundColor_;
    Color entryNodeBackground_;
    Color parentNodeBackground_;
    OffsetF offset_;
    std::vector<std::shared_ptr<AnimationUtils::Animation>> animationVector_;
    std::vector<AnimationFinishType> animationFinishList_;
    std::vector<std::shared_ptr<AnimationUtils::Animation>> scrollAnimationVector_;
    std::map<WeakPtr<FrameNode>, Color> exitNodes_;
    std::map<WeakPtr<FrameNode>, Color> entryNodes_;
    float horizontalExitNodeScale_ = 0;
    float horizontalExitNodeBlur_ = 0;
    float horizontalExitNodeOpacity_ = 0;
    float horizontalEntryNodeScale_ = 0;
    float horizontalEntryNodeBlur_ = 0;
    float horizontalEntryNodeOpacity_ = 0;

    float verticalExitNodeScale_ = 0;
    float verticalExitNodeBlur_ = 0;
    float verticalExitNodeOpacity_ = 0;
    float verticalEntryNodeScale_ = 0;
    float verticalEntryNodeOpacity_ = 0;
    bool hasGetExitColor_ = false;
    bool hasGetEntryColor_ = false;
    bool hasChangeColor_ = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_ARC_SWIPER_PATTERN_H
