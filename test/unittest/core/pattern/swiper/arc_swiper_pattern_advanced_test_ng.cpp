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

class ArcSwiperPatternAdvancedTestNg : public SwiperTestNg {
private:
    RefPtr<FrameNode> CreateFrameNode();
    SwiperItemInfo CreateSwiperItemInfo(float startPos, float endPos, const RefPtr<FrameNode>& node);
};

RefPtr<FrameNode> ArcSwiperPatternAdvancedTestNg::CreateFrameNode()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    return FrameNode::CreateFrameNode("node", nodeId, AceType::MakeRefPtr<ArcSwiperPattern>());
}

SwiperItemInfo ArcSwiperPatternAdvancedTestNg::CreateSwiperItemInfo(float startPos, float endPos,
    const RefPtr<FrameNode>& node)
{
    SwiperItemInfo item;
    item.startPos = startPos;
    item.endPos = endPos;
    item.node = node;
    return item;
}

/**
 * @tc.name: PlayVerticalAnimation001
 * @tc.desc: Test for method of PlayVerticalAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, PlayVerticalAnimation001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->itemPosition_.size(), 2);
    OffsetF offset(0.0f, 0.0f);
    auto frameNode = CreateFrameNode();
    bool rollBack = true;
    pattern->PlayVerticalAnimation(offset, 1, frameNode, rollBack);
    EXPECT_EQ(pattern->animationVector_.size(), 5);
    pattern->animationVector_.clear();
    EXPECT_EQ(pattern->animationVector_.size(), 0);
    pattern->PlayVerticalAnimation(offset, 0, frameNode, rollBack);
    EXPECT_EQ(pattern->animationVector_.size(), 4);
}

/**
 * @tc.name: AnimationFinish001
 * @tc.desc: Test for method of AnimationFinish.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, AnimationFinish001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->itemPosition_.size(), 2);
    pattern->propertyAnimationIsRunning_ = false;
    pattern->targetIndex_ = std::make_optional<int>(2);
    EXPECT_EQ(pattern->targetIndex_, 2);
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    pattern->AnimationFinish();
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_TRUE(pattern->targetIndex_);

    pattern->propertyAnimationIsRunning_ = true;
    pattern->AnimationFinish();
    EXPECT_FALSE(pattern->targetIndex_.has_value());
    EXPECT_FALSE(pattern->targetIndex_);
}

/**
 * @tc.name: AnimationFinish002
 * @tc.desc: Test for method of AnimationFinish.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, AnimationFinish002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->itemPosition_.size(), 2);
    pattern->targetIndex_ = std::make_optional<int>(2);
    EXPECT_EQ(pattern->targetIndex_, 2);
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    pattern->SetHasTabsAncestor(true);
    pattern->propertyAnimationIsRunning_ = false;
    pattern->AnimationFinish();
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_TRUE(pattern->targetIndex_);

    pattern->propertyAnimationIsRunning_ = true;
    pattern->AnimationFinish();
    EXPECT_FALSE(pattern->targetIndex_.has_value());
    EXPECT_FALSE(pattern->targetIndex_);
}

/**
 * @tc.name: AnimationFinish003
 * @tc.desc: Test for method of AnimationFinish.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, AnimationFinish003, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->itemPosition_.size(), 2);
    pattern->targetIndex_ = std::make_optional<int>(2);
    EXPECT_EQ(pattern->targetIndex_, 2);
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    pattern->itemPosition_.clear();
    EXPECT_EQ(pattern->itemPosition_.size(), 0);
    pattern->propertyAnimationIsRunning_ = false;
    pattern->AnimationFinish();
    EXPECT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_TRUE(pattern->targetIndex_);

    pattern->propertyAnimationIsRunning_ = true;
    pattern->AnimationFinish();
    EXPECT_FALSE(pattern->targetIndex_.has_value());
    EXPECT_FALSE(pattern->targetIndex_);
}

/**
 * @tc.name: PlayPropertyTranslateDefaultAnimation001
 * @tc.desc: Test for method of PlayPropertyTranslateDefaultAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, PlayPropertyTranslateDefaultAnimation001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->targetIndex_ = std::make_optional<int>(2);
    EXPECT_EQ(pattern->targetIndex_, 2);
    OffsetF offset(0.0f, 0.0f);
    float translate = 0;
    pattern->PlayPropertyTranslateDefaultAnimation(offset, translate);
    EXPECT_FALSE(pattern->targetIndex_);
}

/**
 * @tc.name: PlayVerticalExitOffsetAnimation
 * @tc.desc: Test for method of PlayVerticalExitOffsetAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, PlayVerticalExitOffsetAnimation, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    OffsetF offset(0.0f, 0.0f);
    auto frameNode = CreateFrameNode();
    bool rollBack = true;
    EXPECT_EQ(pattern->animationVector_.size(), 0);
    pattern->PlayVerticalExitOffsetAnimation(offset, frameNode, rollBack);
    EXPECT_EQ(pattern->animationVector_.size(), 1);
}

/**
 * @tc.name: PlayVerticalEntryOffsetAnimation001
 * @tc.desc: Test for method of PlayVerticalEntryOffsetAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, PlayVerticalEntryOffsetAnimation001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetPreviousMargin(Dimension(20), false);
    model.SetNextMargin(Dimension(20), false);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    OffsetF offset(0.0f, 0.0f);
    auto frameNode = CreateFrameNode();
    bool rollBack = true;
    EXPECT_EQ(pattern->animationVector_.size(), 0);
    pattern->PlayVerticalEntryOffsetAnimation(offset, frameNode, rollBack);
    EXPECT_EQ(pattern->animationVector_.size(), 1);
    rollBack = false;
    pattern->animationVector_.clear();
    EXPECT_EQ(pattern->animationVector_.size(), 0);
    pattern->PlayVerticalEntryOffsetAnimation(offset, frameNode, rollBack);
    EXPECT_EQ(pattern->animationVector_.size(), 2);
}

/**
 * @tc.name: GetCurve
 * @tc.desc: Test for method of GetCurve.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, GetCurve, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->disableTransitionAnimation_ = true;
    EXPECT_EQ(pattern->GetCurve(), nullptr);
    pattern->disableTransitionAnimation_ = false;
    EXPECT_EQ(pattern->GetCurve(), Curves::FRICTION);
}

/**
 * @tc.name: GetDuration
 * @tc.desc: Test for method of GetDuration.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, GetDuration, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->disableTransitionAnimation_ = false;
    EXPECT_EQ(pattern->GetDuration(), 330);

    SwiperModelNG model1 = CreateArcSwiper();
    model1.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern->GetDuration(), 750);

    pattern->disableTransitionAnimation_ = true;
    EXPECT_EQ(pattern->GetDuration(), 400);
}

/**
 * @tc.name: CalcTime
 * @tc.desc: Test for method of CalcTime.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, CalcTime, TestSize.Level1)
{
    SwiperModelNG model;
    model.Create(true);
    model.SetDirection(Axis::VERTICAL);
    model.SetDuration(300);
    ViewAbstract::SetWidth(CalcLength(SWIPER_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    GetSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->CalcTime(660), 600);

    SwiperModelNG model1 = CreateArcSwiper();
    model1.SetDirection(Axis::HORIZONTAL);
    model1.SetDuration(300);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern->CalcTime(660), 660);
}

/**
 * @tc.name: ResetFrameNodeAnimation
 * @tc.desc: Test for method of ResetFrameNodeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, ResetFrameNodeAnimation, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    RefPtr<FrameNode> frameNode = nullptr;
    pattern->ResetFrameNodeAnimation(frameNode, false);

    frameNode = CreateFrameNode();
    pattern->ResetFrameNodeAnimation(frameNode, false);

    pattern->ResetFrameNodeAnimation(frameNode, true);
    auto color = pattern->GetBackgroundColorValue(frameNode);
    ASSERT_EQ(color, nullptr);

    frameNode->GetRenderContext()->UpdateBackgroundColor(Color::BLUE);
    pattern->ResetFrameNodeAnimation(frameNode, true);
    color = pattern->GetBackgroundColorValue(frameNode);
    ASSERT_NE(color, nullptr);
    EXPECT_EQ(*color, Color::BLUE);
}

/**
 * @tc.name: ClearAnimationFinishList
 * @tc.desc: Test for method of ClearAnimationFinishList.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, ClearAnimationFinishList, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    pattern->animationFinishList_.clear();
    pattern->animationFinishList_.emplace_back(ArcSwiperPattern::AnimationFinishType::EXIT_SCALE);
    pattern->animationFinishList_.emplace_back(ArcSwiperPattern::AnimationFinishType::ENTRY_SCALE);
    EXPECT_EQ(pattern->animationFinishList_.size(), 2);
    pattern->ClearAnimationFinishList();
    EXPECT_EQ(pattern->animationFinishList_.size(), 0);
}

/**
 * @tc.name: GetEntryNodeBackgroundColor
 * @tc.desc: Test for method of GetEntryNodeBackgroundColor.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, GetEntryNodeBackgroundColor, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    RefPtr<FrameNode> frameNode = nullptr;
    auto color = pattern->GetEntryNodeBackgroundColor(frameNode);
    ASSERT_EQ(color, nullptr);

    pattern->parentNodeBackgroundColor_ = std::make_shared<Color>(Color::RED);
    frameNode = CreateFrameNode();
    color = pattern->GetEntryNodeBackgroundColor(frameNode);
    ASSERT_NE(color, nullptr);
    EXPECT_EQ(*color, Color::RED);

    frameNode->GetRenderContext()->UpdateBackgroundColor(Color::BLUE);
    color = pattern->GetEntryNodeBackgroundColor(frameNode);
    ASSERT_NE(color, nullptr);
    EXPECT_EQ(*color, Color::BLUE);

    pattern->parentNodeBackgroundColor_ = nullptr;
    frameNode->renderContext_ = nullptr;
    color = pattern->GetEntryNodeBackgroundColor(frameNode);
    ASSERT_NE(color, nullptr);
    EXPECT_EQ(*color, Color::TRANSPARENT);
}

/**
 * @tc.name: ResetCurrentFrameNodeAnimation
 * @tc.desc: Test for method of ResetCurrentFrameNodeAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, ResetCurrentFrameNodeAnimation, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<FrameNode> frameNode = nullptr;
    SwiperItemInfo item = CreateSwiperItemInfo(0, 20, nullptr);
    pattern->itemPosition_.clear();
    pattern->itemPosition_.insert(std::make_pair(0, item));
    auto item1 = CreateSwiperItemInfo(0, 20, CreateFrameNode());
    pattern->itemPosition_.insert(std::make_pair(1, item1));
    EXPECT_EQ(pattern->itemPosition_.size(), 2);
    pattern->currentIndex_ = 0;
    pattern->ResetCurrentFrameNodeAnimation();

    auto item2 = CreateSwiperItemInfo(0, 20, CreateFrameNode());
    pattern->itemPosition_.insert(std::make_pair(2, item2));
    EXPECT_EQ(pattern->itemPosition_.size(), 3);
    pattern->currentIndex_ = 1;
    pattern->ResetCurrentFrameNodeAnimation();
}

/**
 * @tc.name: ResetParentNodeColor
 * @tc.desc: Test for method of ResetParentNodeColor.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, ResetParentNodeColor, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();

    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    RefPtr<FrameNode> frameNode = nullptr;
    SwiperItemInfo item = CreateSwiperItemInfo(0, 20, frameNode);
    pattern->itemPosition_.clear();
    pattern->itemPosition_.insert(std::make_pair(0, item));
    pattern->currentIndex_ = 0;
    pattern->ResetParentNodeColor();

    auto item1 = CreateSwiperItemInfo(0, 20, CreateFrameNode());
    pattern->itemPosition_.insert(std::make_pair(1, item1));
    EXPECT_EQ(pattern->itemPosition_.size(), 2);
    pattern->currentIndex_ = 0;
    pattern->ResetParentNodeColor();

    auto parentNode = CreateFrameNode();
    auto childNode = CreateFrameNode();
    childNode->MountToParent(parentNode);
    auto item3 = CreateSwiperItemInfo(21, 40, childNode);
    pattern->itemPosition_.insert(std::make_pair(2, item3));
    EXPECT_EQ(pattern->itemPosition_.size(), 3);
    pattern->currentIndex_ = 2;
    pattern->ResetParentNodeColor();

    parentNode->GetRenderContext()->UpdateBackgroundColor(Color::BLUE);
    EXPECT_EQ(parentNode->GetRenderContext()->GetBackgroundColorValue(), Color::BLUE);
    childNode->MountToParent(parentNode);
    auto item4 = CreateSwiperItemInfo(21, 40, childNode);
    pattern->itemPosition_.insert(std::make_pair(3, item4));
    EXPECT_EQ(pattern->itemPosition_.size(), 4);
    pattern->currentIndex_ = 3;
    pattern->ResetParentNodeColor();
}

/**
 * @tc.name: PlayPropertyTranslateFlipAnimation
 * @tc.desc: Test for method of PlayPropertyTranslateFlipAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, PlayPropertyTranslateFlipAnimation, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    OffsetF offset;
    RefPtr<FrameNode> frameNode = nullptr;
    SwiperItemInfo item = CreateSwiperItemInfo(0, 20, frameNode);
    pattern->itemPosition_.insert(std::make_pair(0, item));
    pattern->PlayPropertyTranslateFlipAnimation(offset);
    EXPECT_EQ(pattern->itemPositionInAnimation_.size(), 1);

    RefPtr<FrameNode> frameNode1 = nullptr;
    offset.SetX(50);
    SwiperItemInfo item1 = CreateSwiperItemInfo(21, 40, frameNode1);
    pattern->hasTabsAncestor_ = true;
    pattern->itemPosition_.insert(std::make_pair(1, item1));
    pattern->targetIndex_ = std::make_optional<int>(2);
    pattern->currentIndex_ = 2;
    pattern->PlayPropertyTranslateFlipAnimation(offset);
    EXPECT_EQ(pattern->itemPositionInAnimation_.size(), 2);
    pattern->itemPosition_.clear();
}

/**
 * @tc.name: PlayAnimation
 * @tc.desc: Test for method of PlayAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, PlayAnimation, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    model.SetDuration(300);
    CreateSwiperItems();
    CreateSwiperDone();

    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    OffsetF offset;
    RefPtr<FrameNode> frameNode = nullptr;
    int32_t index = 0;
    pattern->targetIndex_ = std::make_optional<int>(2);
    pattern->PlayAnimation(offset, index, frameNode);
    EXPECT_EQ(pattern->animationVector_.size(), 0);

    SwiperModelNG model1 = CreateArcSwiper();
    model1.SetDirection(Axis::HORIZONTAL);
    model1.SetDuration(300);
    CreateSwiperItems();
    CreateSwiperDone();
    pattern->PlayAnimation(offset, index, frameNode);
    EXPECT_EQ(pattern->animationVector_.size(), 0);
}

/**
 * @tc.name: PlayHorizontalEntryAnimation
 * @tc.desc: Test for method of PlayHorizontalEntryAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, PlayHorizontalEntryAnimation, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    OffsetF offset;
    RefPtr<FrameNode> frameNode = nullptr;
    pattern->PlayHorizontalEntryAnimation(offset, frameNode, true);
    EXPECT_EQ(pattern->animationVector_.size(), 0);
    frameNode = CreateFrameNode();
    frameNode->GetRenderContext();
    pattern->PlayHorizontalEntryAnimation(offset, frameNode, true);
    EXPECT_EQ(pattern->animationVector_.size(), 4);
}

/**
 * @tc.name: PlayHorizontalExitAnimation
 * @tc.desc: Test for method of PlayHorizontalExitAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, PlayHorizontalExitAnimation, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    OffsetF offset;
    RefPtr<FrameNode> frameNode = nullptr;
    pattern->PlayHorizontalExitAnimation(offset, frameNode, true);
    EXPECT_EQ(pattern->animationVector_.size(), 0);
    frameNode = CreateFrameNode();
    frameNode->GetRenderContext();
    pattern->PlayHorizontalExitAnimation(offset, frameNode, true);
    EXPECT_EQ(pattern->animationVector_.size(), 4);
}

/**
 * @tc.name: PlayHorizontalAnimation
 * @tc.desc: Test for method of PlayHorizontalAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, PlayHorizontalAnimation, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<FrameNode> frameNode = nullptr;
    OffsetF offset(0.0f, 0.0f);
    int32_t index = 0;
    bool rollBack = true;
    pattern->PlayHorizontalAnimation(offset, index, frameNode, rollBack);
    EXPECT_EQ(pattern->animationVector_.size(), 0);
    rollBack = false;
    pattern->PlayHorizontalAnimation(offset, index, frameNode, rollBack);
    EXPECT_EQ(pattern->animationVector_.size(), 0);
}

/**
 * @tc.name: AddFinishAnimation
 * @tc.desc: Test for method of AddFinishAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, AddFinishAnimation, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->animationFinishList_.clear();
    auto animationType = ArcSwiperPattern::AnimationFinishType::EXIT_BACKGROUND;
    for (int i = 0; i < 8; i++) {
        pattern->animationFinishList_.push_back(animationType);
    }
    pattern->propertyAnimationIsRunning_ = false;
    pattern->targetIndex_ = std::make_optional<int>(2);
    pattern->AddFinishAnimation(animationType, true, false);
    EXPECT_TRUE(pattern->targetIndex_.has_value());

    pattern->propertyAnimationIsRunning_ = true;
    pattern->animationFinishList_.clear();
    for (int i = 0; i < 7; i++) {
        pattern->animationFinishList_.push_back(animationType);
    }
    pattern->targetIndex_ = std::make_optional<int>(2);
    pattern->AddFinishAnimation(animationType, false, false);
    EXPECT_FALSE(pattern->targetIndex_.has_value());

    pattern->targetIndex_ = std::make_optional<int>(2);
    pattern->animationFinishList_.pop_back();
    ASSERT_TRUE(pattern->targetIndex_.has_value());
    EXPECT_EQ(pattern->targetIndex_.value(), 2);
}

/**
 * @tc.name: BuildDefaultTranslateAnimationOption
 * @tc.desc: Test for method of BuildDefaultTranslateAnimationOption.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, BuildDefaultTranslateAnimationOption, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    auto frameRateRange = AceType::MakeRefPtr<FrameRateRange>(0, 120, 60);
    auto sceneType = SwiperDynamicSyncSceneType::ANIMATE;
    pattern->frameRateRange_.insert(std::make_pair(sceneType, frameRateRange));

    auto frameRateRange1 = AceType::MakeRefPtr<FrameRateRange>(0, 120, 120);
    auto sceneType1 = SwiperDynamicSyncSceneType::GESTURE;
    pattern->frameRateRange_.insert(std::make_pair(sceneType1, frameRateRange1));
    AnimationOption animationOption;
    pattern->BuildDefaultTranslateAnimationOption(animationOption, 1.1f);
    auto curve = pattern->GetCurveIncludeMotion();
    EXPECT_EQ(animationOption.GetCurve(), curve);
    EXPECT_EQ(animationOption.GetFrameRateRange(), frameRateRange);
}

/**
 * @tc.name: PlayPropertyTranslateAnimation01
 * @tc.desc: Test for method of PlayPropertyTranslateAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternAdvancedTestNg, PlayPropertyTranslateAnimation01, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);

    RefPtr<FrameNode> frameNode = CreateFrameNode();
    SwiperItemInfo item = CreateSwiperItemInfo(0, 20, frameNode);
    pattern->itemPosition_.clear();
    pattern->itemPosition_.insert(std::make_pair(0, item));
    pattern->PlayPropertyTranslateAnimation(1.0f, 11, 1.0f, true);
    EXPECT_FALSE(pattern->usePropertyAnimation_);
}
} // namespace OHOS::Ace::NG
