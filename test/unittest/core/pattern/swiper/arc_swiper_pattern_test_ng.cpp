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

#include "swiper_test_ng.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float EXIT_SCALE_VALUE = 0.6f;
constexpr int32_t EXIT_SCALE_DURATION = 750;
constexpr int32_t EXIT_OFFSET_DURATION = 750;
constexpr int32_t EXIT_BLUR_VALUE = 30;
constexpr int32_t EXIT_BLUR_DELAY = 150;
constexpr int32_t EXIT_BLUR_DURATION = 250;
constexpr int32_t EXIT_ALPHA_DURATION = 750;
constexpr int32_t ENTRY_COLOR_DURATION = 40;
constexpr int32_t NO_ANIMAION_DEFAULT_DURATION = 400;
constexpr int32_t VERTICAL_ANIMAION_DEFAULT_DURATION = 330;
constexpr int32_t HORIZONTAL_ANIMAION_DEFAULT_DURATION = 750;
}

class ArcSwiperPatternTestNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: IsPreItem001
 * @tc.desc: Test for method of IsPreItem.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, IsPreItem001, TestSize.Level1)
{
    CreateWithItem(
        [](SwiperModelNG model) {
            model.Create(true);
            model.SetDirection(Axis::HORIZONTAL);
            model.SetPreviousMargin(Dimension(20), false);
            model.SetNextMargin(Dimension(20), false);
        });
    EXPECT_EQ(pattern_->itemPosition_.size(), 2);
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    int32_t index = 0;
    float translate = -1.0f;
    EXPECT_TRUE(pattern->IsPreItem(index, translate));
}

/**
 * @tc.name: IsPreItem002
 * @tc.desc: Test for method of IsPreItem.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, IsPreItem002, TestSize.Level1)
{
    CreateWithItem(
        [](SwiperModelNG model) {
            model.Create(true);
            model.SetDirection(Axis::HORIZONTAL);
            model.SetPreviousMargin(Dimension(20), false);
            model.SetNextMargin(Dimension(20), false);
        });
    EXPECT_EQ(pattern_->itemPosition_.size(), 2);
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    int32_t index = 0;
    float translate = 1.0f;
    bool isPreItem = pattern->IsPreItem(index, translate);
    EXPECT_EQ(isPreItem, false);
}

/**
 * @tc.name: IsPreItem003
 * @tc.desc: Test for method of IsPreItem.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, IsPreItem003, TestSize.Level1)
{
    CreateWithItem(
        [](SwiperModelNG model) {
            model.Create(true);
            model.SetDirection(Axis::HORIZONTAL);
            model.SetPreviousMargin(Dimension(20), false);
            model.SetNextMargin(Dimension(20), false);
        });
    EXPECT_EQ(pattern_->itemPosition_.size(), 2);
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    int32_t index = 1;
    float translate = -1.0f;
    bool isPreItem = pattern->IsPreItem(index, translate);
    EXPECT_EQ(isPreItem, false);
}

/**
 * @tc.name: IsPreItem004
 * @tc.desc: Test for method of IsPreItem.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, IsPreItem004, TestSize.Level1)
{
    CreateWithItem(
        [](SwiperModelNG model) {
            model.Create(true);
            model.SetDirection(Axis::HORIZONTAL);
            model.SetPreviousMargin(Dimension(20), false);
            model.SetNextMargin(Dimension(20), false);
        });
    EXPECT_EQ(pattern_->itemPosition_.size(), 2);
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    int32_t index = 1;
    float translate = 1.0f;
    EXPECT_TRUE(pattern->IsPreItem(index, translate));
}

/**
 * @tc.name: Animation001
 * @tc.desc: Test for animation of scale.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, Animation001, TestSize.Level1)
{
    CreateWithItem(
        [](SwiperModelNG model) {
            model.Create(true);
            model.SetDirection(Axis::HORIZONTAL);
            model.SetPreviousMargin(Dimension(20), false);
            model.SetNextMargin(Dimension(20), false);
        });

    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    // scale
    renderContext->UpdateTransformScale({ 1.0f, 1.0f });
    ArcSwiperPattern::AnimationParam scaleParam;
    scaleParam.type = ArcSwiperPattern::AnimationType::TYPE_SCALE;
    scaleParam.frameNode = frameNode_;
    scaleParam.scaleValue = EXIT_SCALE_VALUE;

    AnimationOption scaleOption;
    scaleOption.SetDuration(EXIT_SCALE_DURATION);
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;

    pattern->animationFinishList_.clear();
    auto animation = pattern->Animation(true, scaleParam);
    ASSERT_NE(animation, nullptr);

    auto list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 1);

    auto animationType = list.at(0);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::EXIT_SCALE);

    animation = pattern->Animation(false, scaleParam);
    ASSERT_NE(animation, nullptr);

    list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 2);

    animationType = list.at(1);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::ENTRY_SCALE);
}

/**
 * @tc.name: Animation002
 * @tc.desc: Test for animation of offset.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, Animation002, TestSize.Level1)
{
    CreateWithItem(
        [](SwiperModelNG model) {
            model.Create(true);
            model.SetDirection(Axis::HORIZONTAL);
            model.SetPreviousMargin(Dimension(20), false);
            model.SetNextMargin(Dimension(20), false);
        });

    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    //Offset
    ArcSwiperPattern::AnimationParam offsetParam;
    offsetParam.type = ArcSwiperPattern::AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode_;

    AnimationOption offsetOption;
    offsetOption.SetDuration(EXIT_OFFSET_DURATION);
    offsetOption.SetCurve(Curves::FRICTION);
    offsetParam.option = offsetOption;

    pattern->animationFinishList_.clear();
    auto animation = pattern->Animation(true, offsetParam);
    ASSERT_NE(animation, nullptr);

    auto list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 1);

    auto animationType = list.at(0);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::EXIT_OFFSET);

    animation = pattern->Animation(false, offsetParam);
    ASSERT_NE(animation, nullptr);

    list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 2);

    animationType = list.at(1);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::ENTRY_OFFSET);
}

/**
 * @tc.name: Animation003
 * @tc.desc: Test for animation of blur.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, Animation003, TestSize.Level1)
{
    CreateWithItem(
        [](SwiperModelNG model) {
            model.Create(true);
            model.SetDirection(Axis::HORIZONTAL);
            model.SetPreviousMargin(Dimension(20), false);
            model.SetNextMargin(Dimension(20), false);
        });

    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    //blur
    BlurOption blurOption;
    renderContext->UpdateBackBlur(Dimension(0, DimensionUnit::PERCENT), blurOption);
    ArcSwiperPattern::AnimationParam blurParam;
    blurParam.type = ArcSwiperPattern::AnimationType::TYPE_BLUR;
    blurParam.frameNode = frameNode_;
    blurParam.blurValue = EXIT_BLUR_VALUE;

    AnimationOption blurAnimationOption;
    blurAnimationOption.SetDelay(EXIT_BLUR_DELAY);
    blurAnimationOption.SetDuration(EXIT_BLUR_DURATION);
    blurAnimationOption.SetCurve(Curves::LINEAR);
    blurParam.option = blurAnimationOption;

    pattern->animationFinishList_.clear();
    auto animation = pattern->Animation(true, blurParam);
    ASSERT_NE(animation, nullptr);

    auto list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 1);

    auto animationType = list.at(0);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::EXIT_BLUR);

    animation = pattern->Animation(false, blurParam);
    ASSERT_NE(animation, nullptr);

    list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 2);

    animationType = list.at(1);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::ENTRY_BLUR);
}

/**
 * @tc.name: Animation004
 * @tc.desc: Test for animation of alpha.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, Animation004, TestSize.Level1)
{
    CreateWithItem(
        [](SwiperModelNG model) {
            model.Create(true);
            model.SetDirection(Axis::HORIZONTAL);
            model.SetPreviousMargin(Dimension(20), false);
            model.SetNextMargin(Dimension(20), false);
        });

    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    //alpha
    renderContext->UpdateOpacity(1);
    ArcSwiperPattern::AnimationParam alphaParam;
    alphaParam.type = ArcSwiperPattern::AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode_;
    alphaParam.opacityValue = 0;

    AnimationOption alphaOption;
    alphaOption.SetDuration(EXIT_ALPHA_DURATION);
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;

    pattern->animationFinishList_.clear();
    auto animation = pattern->Animation(true, alphaParam);
    ASSERT_NE(animation, nullptr);

    auto list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 1);

    auto animationType = list.at(0);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::EXIT_ALPHA);

    animation = pattern->Animation(false, alphaParam);
    ASSERT_NE(animation, nullptr);

    list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 2);

    animationType = list.at(1);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::ENTRY_ALPHA);
}

/**
 * @tc.name: Animation005
 * @tc.desc: Test for animation of color.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, Animation005, TestSize.Level1)
{
    CreateWithItem(
        [](SwiperModelNG model) {
            model.Create(true);
            model.SetDirection(Axis::HORIZONTAL);
            model.SetPreviousMargin(Dimension(20), false);
            model.SetNextMargin(Dimension(20), false);
        });

    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    //background
    renderContext->OnBackgroundColorUpdate(Color::RED);
    ArcSwiperPattern::AnimationParam colorParam;
    colorParam.type = ArcSwiperPattern::AnimationType::TYPE_COLOR;
    colorParam.frameNode = frameNode_;
    colorParam.backColor = Color::BLUE;

    AnimationOption colorOption;
    colorOption.SetDuration(ENTRY_COLOR_DURATION);
    colorOption.SetCurve(Curves::LINEAR);
    colorParam.option = colorOption;

    pattern->animationFinishList_.clear();
    auto animation = pattern->Animation(true, colorParam);
    ASSERT_NE(animation, nullptr);

    auto list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 1);

    auto animationType = list.at(0);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::EXIT_BACKGROUND);

    animation = pattern->Animation(false, colorParam);
    ASSERT_NE(animation, nullptr);

    list = pattern->animationFinishList_;
    EXPECT_EQ(list.size(), 2);

    animationType = list.at(1);
    EXPECT_EQ(animationType, ArcSwiperPattern::AnimationFinishType::ENTRY_BACKGROUND);
}

/**
 * @tc.name: IsScrollOverCritical001
 * @tc.desc: Test for IsScrollOverCritical
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, IsScrollOverCritical001, TestSize.Level1)
{
    CreateWithItem(
        [](SwiperModelNG model) {
            model.Create(true);
            model.SetDirection(Axis::HORIZONTAL);
            model.SetPreviousMargin(Dimension(20), false);
            model.SetNextMargin(Dimension(20), false);
        });

    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    auto targetIndex = std::make_optional<int>(2);
    pattern->targetIndex_ = targetIndex;
    pattern->currentIndex_ = 2;
    auto iScrollOverCritical = pattern->IsScrollOverCritical();
    EXPECT_FALSE(iScrollOverCritical);
}

/**
 * @tc.name: IsScrollOverCritical002
 * @tc.desc: Test for IsScrollOverCritical
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, IsScrollOverCritical002, TestSize.Level1)
{
    CreateWithItem(
        [](SwiperModelNG model) {
            model.Create(true);
            model.SetDirection(Axis::HORIZONTAL);
            model.SetPreviousMargin(Dimension(20), false);
            model.SetNextMargin(Dimension(20), false);
        });

    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    auto targetIndex = std::make_optional<int>(2);
    pattern->targetIndex_ = targetIndex;
    pattern->currentIndex_ = 3;
    auto iScrollOverCritical = pattern->IsScrollOverCritical();
    EXPECT_TRUE(iScrollOverCritical);
}

/**
 * @tc.name: IsDisableTransitionAnimation
 * @tc.desc: Test for IsDisableTransitionAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, IsDisableTransitionAnimation, TestSize.Level1)
{
    CreateWithItem(
        [](SwiperModelNG model) {
            model.Create(true);
            model.SetDirection(Axis::HORIZONTAL);
            model.SetPreviousMargin(Dimension(20), false);
            model.SetNextMargin(Dimension(20), false);
        });

    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->SetDisableTransitionAnimation(true);
    EXPECT_TRUE(pattern->IsDisableTransitionAnimation());

    pattern->SetDisableTransitionAnimation(false);
    EXPECT_FALSE(pattern->IsDisableTransitionAnimation());
}

/**
 * @tc.name: EnableTransitionAnimation
 * @tc.desc: Test for EnableTransitionAnimation when IsDisableTransitionAnimation is true
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, EnableTransitionAnimation001, TestSize.Level1)
{
    CreateWithItem(
        [](SwiperModelNG model) {
            model.Create(true);
            model.SetDirection(Axis::HORIZONTAL);
            model.SetPreviousMargin(Dimension(20), false);
            model.SetNextMargin(Dimension(20), false);
        });

    ASSERT_NE(frameNode_, nullptr);
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->EnableTransitionAnimation());

    pattern->SetDisableTransitionAnimation(true);
    EXPECT_TRUE(pattern->IsDisableTransitionAnimation());
    EXPECT_FALSE(pattern->EnableTransitionAnimation());
}

/**
 * @tc.name: GetCurve001
 * @tc.desc: Test for GetCurve when disableTransitionAnimation is false
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetCurve001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) { \
        model.Create(true);
        model.SetCurve(Curves::SMOOTH);
    });
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(false);
    EXPECT_EQ(pattern->GetCurve(), Curves::FRICTION);
}

/**
 * @tc.name: GetCurve002
 * @tc.desc: Test for GetCurve when disableTransitionAnimation is false
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetCurve002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.Create(true);
    });
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(false);
    EXPECT_EQ(pattern->GetCurve(), Curves::FRICTION);
}

/**
 * @tc.name: GetCurve003
 * @tc.desc: Test for GetCurve when disableTransitionAnimation is true
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetCurve003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.Create(true);
    });
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(true);
    EXPECT_EQ(pattern->GetCurve(), nullptr);
}

/**
 * @tc.name: GetCurve004
 * @tc.desc: Test for GetCurve when disableTransitionAnimation is true
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetCurve004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.Create(true);
        model.SetCurve(Curves::SMOOTH);
    });
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(true);
    EXPECT_EQ(pattern->GetCurve(), Curves::SMOOTH);
}

/**
 * @tc.name: GetDuraion001
 * @tc.desc: Test for GetDuraion when disableTransitionAnimation is false and axis is horizontal
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetDuraion001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.Create(true);
        model.SetDirection(Axis::HORIZONTAL);
    });
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(false);
    EXPECT_EQ(pattern->GetDuration(), HORIZONTAL_ANIMAION_DEFAULT_DURATION);
}

/**
 * @tc.name: GetDuraion002
 * @tc.desc: Test for GetDuraion when disableTransitionAnimation is false and axis is vertical
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetDuraion002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.Create(true);
        model.SetDirection(Axis::VERTICAL);
    });
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(false);
    EXPECT_EQ(pattern->GetDuration(), VERTICAL_ANIMAION_DEFAULT_DURATION);
}

/**
 * @tc.name: GetDuraion003
 * @tc.desc: Test for GetDuraion when disableTransitionAnimation is false and set duration
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetDuraion003, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.Create(true);
        model.SetDuration(1000);
        model.SetDirection(Axis::VERTICAL);
    });
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(false);
    EXPECT_EQ(pattern->GetDuration(), 1000);
}

/**
 * @tc.name: GetDuraion004
 * @tc.desc: Test for GetDuraion when disableTransitionAnimation is true and axis is horizontal
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetDuraion004, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.Create(true);
        model.SetDirection(Axis::HORIZONTAL);
    });
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(true);
    EXPECT_EQ(pattern->GetDuration(), NO_ANIMAION_DEFAULT_DURATION);
}

/**
 * @tc.name: GetDuraion005
 * @tc.desc: Test for GetDuraion when disableTransitionAnimation is true and axis is vertical
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, GetDuraion005, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.Create(true);
        model.SetDirection(Axis::VERTICAL);
    });
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(true);
    EXPECT_EQ(pattern->GetDuration(), NO_ANIMAION_DEFAULT_DURATION);
}

/**
 * @tc.name: ClacTime001
 * @tc.desc: Test for ClacTime when disableTransitionAnimation is false and axis is vertical
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, ClacTime001, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.Create(true);
        model.SetDirection(Axis::VERTICAL);
        model.SetDuration(300);
    });
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(false);
    auto time = pattern->CalcTime(660);
    EXPECT_EQ(time, 600);
}

/**
 * @tc.name: ClacTime002
 * @tc.desc: Test for ClacTime when disableTransitionAnimation is false and axis is horizontal
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, ClacTime002, TestSize.Level1)
{
    CreateWithItem([](SwiperModelNG model) {
        model.Create(true);
        model.SetDirection(Axis::HORIZONTAL);
        model.SetDuration(300);
    });
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetDisableTransitionAnimation(false);
    auto time = pattern->CalcTime(800);
    EXPECT_EQ(time, 320);
}
} // namespace OHOS::Ace::NG
