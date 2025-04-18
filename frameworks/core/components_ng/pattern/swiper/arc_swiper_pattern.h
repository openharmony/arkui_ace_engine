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
constexpr float TO_LEFT_ARC_SWIPER_PROPORTION = 5.0f / 2.0f;    //The critical point of arc_swiper is 2/5 screen
constexpr float TO_RIGHT_ARC_SWIPER_PROPORTION = 5.0f / 3.0f;
constexpr int32_t MIN_PAGE_VELOCITY = 520;
class ArcSwiperPattern : public SwiperPattern {
    DECLARE_ACE_TYPE(ArcSwiperPattern, SwiperPattern);
public:
    ArcSwiperPattern()
    {
        swiperProportion_ = TO_LEFT_ARC_SWIPER_PROPORTION;
        newMinTurnPageVelocity_ = MIN_PAGE_VELOCITY;
    }

    ~ArcSwiperPattern() {}
    void SaveCircleDotIndicatorProperty(const RefPtr<FrameNode>& indicatorNode) override;
    void SetSwiperArcDotParameters(const SwiperArcDotParameters& swiperArcDotParameters) override;
    std::string GetArcDotIndicatorStyle() const override;
    std::shared_ptr<SwiperArcDotParameters> GetSwiperArcDotParameters() const override;
    bool IsLoop() const override;
    void SetDisableTransitionAnimation(bool isDisable) override;

#ifdef SUPPORT_DIGITAL_CROWN
    void InitOnCrownEventInternal(const RefPtr<FocusHub>& focusHub) override;
    bool IsCrownSpring() const override;
    void SetIsCrownSpring(bool isCrownSpring) override;
    void HandleCrownEvent(const CrownEvent& event, const OffsetF& center, const OffsetF& offset);
#endif
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
    void InitialFrameNodePropertyAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode);
    void UsePropertyAnimation(const OffsetF& offset);
    void PlayPropertyTranslateAnimation(float translate, int32_t nextIndex, float velocity = 0.0f,
        bool stopAutoPlay = false, std::optional<float> pixelRoundTargetPos = std::nullopt) override;
    void PlayScrollAnimation(float currentDelta, float currentIndexOffset) override;
    void ResetCurrentFrameNodeAnimation() override;
    void ResetParentNodeColor() override;
    RefPtr<Curve> GetCurve() const override;
    int32_t GetDuration() const override;

    int32_t CalcTime(int32_t time);
    void ResetFrameNodeAnimation(const RefPtr<FrameNode>& frameNode, bool resetBackgroundcolor);
    void ClearAnimationFinishList();
    void HorizontalScrollAnimation(float offset);
    void PlayHorizontalScrollExitAnimation(float swiperWidth, float startPos, const RefPtr<FrameNode>& frameNode);
    void PlayHorizontalScrollEntryAnimation(float swiperWidth, float startPos, const RefPtr<FrameNode>& frameNode);
    std::shared_ptr<Color> GetEntryNodeBackgroundColor(const RefPtr<FrameNode>& frameNode);

    void VerticalScrollAnimation(float offset);
    void PlayVerticalScrollExitAnimation(float swiperWidth, float startPos, const RefPtr<FrameNode>& frameNode);
    void PlayVerticalScrollEntryAnimation(float swiperWidth, float startPosj, const RefPtr<FrameNode>& frameNode);

    void PlayScrollBackgroundAnimation(const std::shared_ptr<Color>& color, const std::shared_ptr<Color>& parentColor,
        const RefPtr<RenderContext>& parentRenderContext, bool exitNodeNeedTransparent);
    void PlayPropertyTranslateFlipAnimation(const OffsetF& offset);

    void PlayHorizontalEntryAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode, bool rollback);
    void PlayHorizontalExitAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode, bool rollBack);

    void PlayVerticalExitAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode, bool rollBack);
    void PlayVerticalEntryAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode, bool rollBack);

    void PlayAnimation(const OffsetF& offset, int32_t index, const RefPtr<FrameNode>& frameNode);
    void PlayHorizontalAnimation(const OffsetF& offset, int32_t index, const RefPtr<FrameNode>& frameNode,
        bool rollBack);
    void PlayVerticalAnimation(const OffsetF& offset, int32_t index, const RefPtr<FrameNode>& frameNode, bool rollBack);

    void AnimationFinish();
    void BuildAnimationFinishCallback(bool exit, AnimationParam& param, const RefPtr<RenderContext>& renderContext,
        FinishCallback& finishCallback);
    void HandlePropertyTranslateCallback(float translate, int32_t nextIndex, float velocity);
    void AddFinishAnimation(const AnimationFinishType& animationFinishType, bool vertical = false,
        bool rollBack = false);
    void BuildDefaultTranslateAnimationOption(AnimationOption& option, float translate);
    void PlayPropertyTranslateDefaultAnimation(const OffsetF& offset, float translate);
    bool IsPreItem(int32_t index, float translate, bool rollback = false);
    bool IsScrollOverCritical();
    bool EnableTransitionAnimation() const;
    std::shared_ptr<Color> GetBackgroundColorValue(const RefPtr<FrameNode>& frameNode);
    std::shared_ptr<AnimationUtils::Animation> Animation(bool exit, AnimationParam& param, bool vertical = false,
        bool rollback = false);
    bool IsDisableTransitionAnimation() const;
    void SetBackgroundColor(const RefPtr<RenderContext>& renderContext, const std::shared_ptr<Color>& color);
    std::shared_ptr<Color> CalcBackgroundByPercent(const std::shared_ptr<Color>& colorA,
        const std::shared_ptr<Color>& colorB, float percent);
    
    Color GetVerticalEntryBackgroundValue(bool rollBack);
    void PlayVerticalExitOffsetAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode, bool rollBack);
    void PlayVerticalEntryOffsetAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode, bool rollBack);
    void PlayVerticalScrollEntryBackgroundAnimation(float percent, const RefPtr<FrameNode>& frameNode);
    void PlayVerticalEntryBlurAnimation(const RefPtr<FrameNode>& frameNode, bool rollBack);
    void ResetBackgroundColor(const RefPtr<FrameNode>& frameNode);
    std::shared_ptr<Color> preNodeBackgroundColor_;
    std::shared_ptr<Color> entryNodeBackgroundColor_;
    std::shared_ptr<Color> parentNodeBackgroundColor_;
    OffsetF offset_;
    std::vector<std::shared_ptr<AnimationUtils::Animation>> animationVector_;
    std::vector<AnimationFinishType> animationFinishList_;
    WeakPtr<FrameNode> exitFrameNode_;
    float horizontalExitNodeScale_ = 0.0f;
    float horizontalExitNodeBlur_ = 0.0f;
    float horizontalExitNodeOpacity_ = 0.0f;
    float horizontalEntryNodeScale_ = 0.0f;
    float horizontalEntryNodeBlur_ = 0.0f;
    float horizontalEntryNodeOpacity_ = 0.0f;

    float verticalExitNodeScale_ = 0.0f;
    float verticalExitNodeBlur_ = 0.0f;
    float verticalExitNodeOpacity_ = 0.0f;
    float verticalEntryNodeScale_ = 0.0f;
    float verticalEntryNodeOpacity_ = 0.0f;
    float verticalEntryNodeBlur_ = 0.0f;
    Axis axis_ = Axis::HORIZONTAL;
    bool disableTransitionAnimation_ = false;
#ifdef SUPPORT_DIGITAL_CROWN
    void HandleCrownActionBegin(double degree, double mainDelta, GestureEvent& info);
    void HandleCrownActionUpdate(double degree, double mainDelta, GestureEvent& info, const OffsetF& offset);
    void HandleCrownActionEnd(double degree, double mainDelta, GestureEvent& info, const OffsetF& offset);
    void HandleCrownActionCancel();
    void UpdateCrownVelocity(double degree, double mainDelta, bool isEnd = false);
    void StartVibrator(bool isLeft);
#endif

#ifdef SUPPORT_DIGITAL_CROWN
    Offset accumulativeCrownPx_;
    bool isCrownSpring_ = false;
    double crownVelocity_ = 0.0;
    double crownTurnVelocity_ = 0.0;
    bool isHandleCrownActionEnd_ = false;
#endif
    bool canChangeDirectionFlag_ = false;
    bool scrollToLeft_ = false;
    bool scrollToTop_ = false;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_ARC_SWIPER_PATTERN_H