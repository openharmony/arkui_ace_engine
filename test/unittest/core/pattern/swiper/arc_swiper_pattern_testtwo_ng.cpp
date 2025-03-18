/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include "swiper_test_ng.h"

namespace OHOS::Ace::NG {
class ArcSwiperPatternTestNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: UsePropertyAnimation001
 * @tc.desc: Test ArcSwiperPattern UsePropertyAnimation001
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, UsePropertyAnimation001, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    OffsetF offset(20.0f, 30.0f);
    arcSwiperPattern.propertyAnimationIsRunning_ = true;
    arcSwiperPattern.stopIndicatorAnimation_ = false;
    std::map<int32_t, SwiperItemInfo> itemPositionInAnimation;
    SwiperItemInfo info;
    info.startPos = -200.0f;
    info.endPos = 0.0f;
    itemPositionInAnimation[1] = info;
    arcSwiperPattern.itemPositionInAnimation_ = itemPositionInAnimation;
    arcSwiperPattern.UsePropertyAnimation(offset);
    EXPECT_FALSE(arcSwiperPattern.stopIndicatorAnimation_);
}

/**
 * @tc.name: UsePropertyAnimation002
 * @tc.desc: Test ArcSwiperPattern UsePropertyAnimation002
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, UsePropertyAnimation002, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    OffsetF offset(20.0f, 30.0f);
    arcSwiperPattern.propertyAnimationIsRunning_ = false;
    arcSwiperPattern.UsePropertyAnimation(offset);
    EXPECT_TRUE(arcSwiperPattern.stopIndicatorAnimation_);
}

/**
 * @tc.name: UsePropertyAnimation003
 * @tc.desc: Test ArcSwiperPattern UsePropertyAnimation003
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, UsePropertyAnimation003, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    OffsetF offset(20.0f, 30.0f);
    arcSwiperPattern.propertyAnimationIsRunning_ = true;
    arcSwiperPattern.UsePropertyAnimation(offset);
    EXPECT_TRUE(arcSwiperPattern.stopIndicatorAnimation_);
}

/**
 * @tc.name: UsePropertyAnimation004
 * @tc.desc: Test ArcSwiperPattern UsePropertyAnimation004
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, UsePropertyAnimation004, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    OffsetF offset(20.0f, 30.0f);
    arcSwiperPattern.propertyAnimationIsRunning_ = true;
    arcSwiperPattern.targetIndex_ = 2;
    arcSwiperPattern.UsePropertyAnimation(offset);
    EXPECT_EQ(arcSwiperPattern.targetIndex_, 2);
}

/**
 * @tc.name: UsePropertyAnimation005
 * @tc.desc: Test ArcSwiperPattern UsePropertyAnimation005
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, UsePropertyAnimation005, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    OffsetF offset(20.0f, 30.0f);
    arcSwiperPattern.propertyAnimationIsRunning_ = true;
    arcSwiperPattern.UsePropertyAnimation(offset);
    EXPECT_FALSE(arcSwiperPattern.targetIndex_.has_value());
}

/**
 * @tc.name: PlayPropertyTranslateAnimation001
 * @tc.desc: Test ArcSwiperPattern PlayPropertyTranslateAnimation001
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayPropertyTranslateAnimation001, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    arcSwiperPattern.motionVelocity_ = 20.0f;
    arcSwiperPattern.PlayPropertyTranslateAnimation(0.0f, 2, 0.0f, false);
    EXPECT_EQ(arcSwiperPattern.motionVelocity_, 20);
}

/**
 * @tc.name: PlayPropertyTranslateAnimation002
 * @tc.desc: Test ArcSwiperPattern PlayPropertyTranslateAnimation002
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayPropertyTranslateAnimation002, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    arcSwiperPattern.PlayPropertyTranslateAnimation(20.0f, 2, 40.0f, false);
    EXPECT_EQ(arcSwiperPattern.motionVelocity_, 2);
}

/**
 * @tc.name: PlayPropertyTranslateAnimation003
 * @tc.desc: Test ArcSwiperPattern PlayPropertyTranslateAnimation003
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayPropertyTranslateAnimation003, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    arcSwiperPattern.motionVelocity_ = 20.0f;
    arcSwiperPattern.PlayPropertyTranslateAnimation(20.0f, 2, 40.0f, false);
    EXPECT_EQ(arcSwiperPattern.propertyAnimationIndex_, 2);
}

/**
 * @tc.name: PlayPropertyTranslateAnimation004
 * @tc.desc: Test ArcSwiperPattern PlayPropertyTranslateAnimation004
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayPropertyTranslateAnimation004, TestSize.Level1)
{
    RefPtr<ArcSwiperPattern> arcSwiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(arcSwiperPattern, nullptr);
    arcSwiperPattern->motionVelocity_ = 20.0f;
    arcSwiperPattern->direction_ = Axis::FREE;
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, arcSwiperPattern);
    ASSERT_NE(frameNode, nullptr);
    arcSwiperPattern->PlayPropertyTranslateAnimation(20.0f, 2, 40.0f, false);
    EXPECT_EQ(arcSwiperPattern->propertyAnimationIndex_, 2);
}

/**
 * @tc.name: PlayPropertyTranslateAnimation005
 * @tc.desc: Test ArcSwiperPattern PlayPropertyTranslateAnimation005
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayPropertyTranslateAnimation005, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    arcSwiperPattern.motionVelocity_ = 20.0f;
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::FREE);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    std::map<int32_t, SwiperItemInfo> itemPosition;
    SwiperItemInfo info;
    info.startPos = -200.0f;
    info.endPos = 0.0f;
    itemPosition[1] = info;
    arcSwiperPattern.itemPosition_ = itemPosition;
    arcSwiperPattern.PlayPropertyTranslateAnimation(20.0f, 2, 40.0f, false);
    EXPECT_EQ(arcSwiperPattern.propertyAnimationIndex_, 2);
}

/**
 * @tc.name: PlayPropertyTranslateAnimation006
 * @tc.desc: Test ArcSwiperPattern PlayPropertyTranslateAnimation006
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayPropertyTranslateAnimation006, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    arcSwiperPattern.motionVelocity_ = 20.0f;
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::FREE);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    std::map<int32_t, SwiperItemInfo> itemPosition;
    SwiperItemInfo info;
    info.startPos = -200.0f;
    info.endPos = 0.0f;
    info.node = frameNode_;
    itemPosition[1] = info;
    arcSwiperPattern.itemPosition_ = itemPosition;
    arcSwiperPattern.PlayPropertyTranslateAnimation(20.0f, 2, 40.0f, false);
    EXPECT_EQ(arcSwiperPattern.propertyAnimationIndex_, 2);
}

/**
 * @tc.name: PlayPropertyTranslateAnimation007
 * @tc.desc: Test ArcSwiperPattern PlayPropertyTranslateAnimation007
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayPropertyTranslateAnimation007, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    arcSwiperPattern.motionVelocity_ = 20.0f;
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::FREE);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    std::map<int32_t, SwiperItemInfo> itemPosition;
    SwiperItemInfo info;
    info.startPos = -200.0f;
    info.endPos = 0.0f;
    info.node = frameNode_;
    itemPosition[1] = info;
    arcSwiperPattern.itemPosition_ = itemPosition;
    arcSwiperPattern.PlayPropertyTranslateAnimation(20.0f, 2, 40.0f, false);
    EXPECT_FALSE(arcSwiperPattern.itemPositionInAnimation_.empty());
}

/**
 * @tc.name: PlayPropertyTranslateAnimation008
 * @tc.desc: Test ArcSwiperPattern PlayPropertyTranslateAnimation008
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayPropertyTranslateAnimation008, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    arcSwiperPattern.motionVelocity_ = 20.0f;
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::FREE);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(frameNode_, nullptr);
    auto pattern = frameNode_->GetPattern<ArcSwiperPattern>();
    ASSERT_NE(pattern, nullptr);
    std::map<int32_t, SwiperItemInfo> itemPosition;
    SwiperItemInfo info;
    info.startPos = -200.0f;
    info.endPos = 0.0f;
    info.node = frameNode_;
    itemPosition[1] = info;
    arcSwiperPattern.itemPosition_ = itemPosition;
    arcSwiperPattern.disableTransitionAnimation_ = true;
    arcSwiperPattern.PlayPropertyTranslateAnimation(20.0f, 2, 40.0f, false);
    EXPECT_TRUE(arcSwiperPattern.itemPositionInAnimation_.empty());
}

/**
 * @tc.name: HorizontalScrollAnimation001
 * @tc.desc: Test ArcSwiperPattern HorizontalScrollAnimation001
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, HorizontalScrollAnimation001, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::map<int32_t, SwiperItemInfo> itemPosition;
    SwiperItemInfo info;
    info.startPos = -200.0f;
    info.endPos = 0.0f;
    info.node = frameNode;
    itemPosition[1] = info;
    arcSwiperPattern.itemPosition_ = itemPosition;
    arcSwiperPattern.HorizontalScrollAnimation(-20.0f);
    EXPECT_FALSE(arcSwiperPattern.scrollToLeft_);
}

/**
 * @tc.name: HorizontalScrollAnimation002
 * @tc.desc: Test ArcSwiperPattern HorizontalScrollAnimation002
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, HorizontalScrollAnimation002, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    arcSwiperPattern.scrollToLeft_ = true;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::map<int32_t, SwiperItemInfo> itemPosition;
    SwiperItemInfo info;
    info.startPos = -200.0f;
    info.endPos = 0.0f;
    info.node = frameNode;
    itemPosition[1] = info;
    arcSwiperPattern.itemPosition_ = itemPosition;
    arcSwiperPattern.HorizontalScrollAnimation(20.0f);
    EXPECT_EQ(arcSwiperPattern.swiperProportion_, TO_LEFT_ARC_SWIPER_PROPORTION);
}
/**
 * @tc.name: HorizontalScrollAnimation003
 * @tc.desc: Test ArcSwiperPattern HorizontalScrollAnimation003
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, HorizontalScrollAnimation003, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    arcSwiperPattern.scrollToLeft_ = false;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::map<int32_t, SwiperItemInfo> itemPosition;
    SwiperItemInfo info;
    info.startPos = -200.0f;
    info.endPos = 0.0f;
    info.node = frameNode;
    itemPosition[1] = info;
    arcSwiperPattern.itemPosition_ = itemPosition;
    arcSwiperPattern.HorizontalScrollAnimation(20.0f);
    EXPECT_EQ(arcSwiperPattern.horizontalExitNodeOpacity_, 0);
}

/**
 * @tc.name: HorizontalScrollAnimation004
 * @tc.desc: Test ArcSwiperPattern HorizontalScrollAnimation004
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, HorizontalScrollAnimation004, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    arcSwiperPattern.scrollToLeft_ = true;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::map<int32_t, SwiperItemInfo> itemPosition;
    SwiperItemInfo info;
    info.startPos = -200.0f;
    info.endPos = 0.0f;
    info.node = frameNode;
    itemPosition[1] = info;
    arcSwiperPattern.itemPosition_ = itemPosition;
    arcSwiperPattern.HorizontalScrollAnimation(20.0f);
    EXPECT_EQ(arcSwiperPattern.horizontalExitNodeOpacity_, 0);
}

/**
 * @tc.name: VerticalScrollAnimation001
 * @tc.desc: Test ArcSwiperPattern VerticalScrollAnimation001
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, VerticalScrollAnimation001, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    arcSwiperPattern.canChangeDirectionFlag_ = true;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::map<int32_t, SwiperItemInfo> itemPosition;
    SwiperItemInfo info;
    info.startPos = -200.0f;
    info.endPos = 0.0f;
    info.node = frameNode;
    itemPosition[1] = info;
    arcSwiperPattern.itemPosition_ = itemPosition;
    arcSwiperPattern.VerticalScrollAnimation(-20.0f);
    EXPECT_TRUE(arcSwiperPattern.scrollToTop_);
}

/**
 * @tc.name: VerticalScrollAnimation002
 * @tc.desc: Test ArcSwiperPattern VerticalScrollAnimation002
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, VerticalScrollAnimation002, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::map<int32_t, SwiperItemInfo> itemPosition;
    SwiperItemInfo info;
    info.startPos = -200.0f;
    info.endPos = 0.0f;
    info.node = frameNode;
    itemPosition[1] = info;
    arcSwiperPattern.itemPosition_ = itemPosition;
    arcSwiperPattern.VerticalScrollAnimation(-20.0f);
    EXPECT_FALSE(arcSwiperPattern.scrollToTop_);
}

/**
 * @tc.name: VerticalScrollAnimation003
 * @tc.desc: Test ArcSwiperPattern VerticalScrollAnimation003
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, VerticalScrollAnimation003, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    arcSwiperPattern.scrollToTop_ = true;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::map<int32_t, SwiperItemInfo> itemPosition;
    SwiperItemInfo info;
    info.startPos = -200.0f;
    info.endPos = 0.0f;
    info.node = frameNode;
    itemPosition[1] = info;
    arcSwiperPattern.itemPosition_ = itemPosition;
    arcSwiperPattern.VerticalScrollAnimation(20.0f);
    EXPECT_EQ(arcSwiperPattern.swiperProportion_, TO_LEFT_ARC_SWIPER_PROPORTION);
}

/**
 * @tc.name: VerticalScrollAnimation004
 * @tc.desc: Test ArcSwiperPattern VerticalScrollAnimation004
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, VerticalScrollAnimation004, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    arcSwiperPattern.scrollToTop_ = false;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::map<int32_t, SwiperItemInfo> itemPosition;
    SwiperItemInfo info;
    info.startPos = -200.0f;
    info.endPos = 0.0f;
    info.node = frameNode;
    itemPosition[1] = info;
    arcSwiperPattern.itemPosition_ = itemPosition;
    arcSwiperPattern.VerticalScrollAnimation(20.0f);
    EXPECT_EQ(arcSwiperPattern.swiperProportion_, TO_RIGHT_ARC_SWIPER_PROPORTION);
}

/**
 * @tc.name: VerticalScrollAnimation005
 * @tc.desc: Test ArcSwiperPattern VerticalScrollAnimation005
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, VerticalScrollAnimation005, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    arcSwiperPattern.scrollToTop_ = true;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::map<int32_t, SwiperItemInfo> itemPosition;
    SwiperItemInfo info;
    info.startPos = -200.0f;
    info.endPos = 0.0f;
    info.node = frameNode;
    itemPosition[1] = info;
    arcSwiperPattern.itemPosition_ = itemPosition;
    arcSwiperPattern.VerticalScrollAnimation(20.0f);
    EXPECT_EQ(arcSwiperPattern.horizontalExitNodeOpacity_, 0);
}

/**
 * @tc.name: VerticalScrollAnimation006
 * @tc.desc: Test ArcSwiperPattern VerticalScrollAnimation006
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, VerticalScrollAnimation006, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    arcSwiperPattern.scrollToTop_ = false;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    std::map<int32_t, SwiperItemInfo> itemPosition;
    SwiperItemInfo info;
    info.startPos = -200.0f;
    info.endPos = 0.0f;
    info.node = frameNode;
    itemPosition[1] = info;
    arcSwiperPattern.itemPosition_ = itemPosition;
    arcSwiperPattern.VerticalScrollAnimation(20.0f);
    EXPECT_EQ(arcSwiperPattern.horizontalExitNodeOpacity_, 0);
}

/**
 * @tc.name: PlayVerticalScrollEntryAnimation001
 * @tc.desc: Test ArcSwiperPattern PlayVerticalScrollEntryAnimation001
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayVerticalScrollEntryAnimation001, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    arcSwiperPattern.PlayVerticalScrollEntryAnimation(0.0f, 20.0f, frameNode);
    EXPECT_EQ(arcSwiperPattern.verticalEntryNodeScale_, 0);
}

/**
 * @tc.name: PlayVerticalScrollEntryAnimation002
 * @tc.desc: Test ArcSwiperPattern PlayVerticalScrollEntryAnimation002
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayVerticalScrollEntryAnimation002, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    arcSwiperPattern.PlayVerticalScrollEntryAnimation(100.0f, -20.0f, frameNode);
    EXPECT_NE(arcSwiperPattern.verticalEntryNodeScale_, 1);
}

/**
 * @tc.name: PlayVerticalScrollEntryAnimation003
 * @tc.desc: Test ArcSwiperPattern PlayVerticalScrollEntryAnimation003
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayVerticalScrollEntryAnimation003, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    arcSwiperPattern.PlayVerticalScrollEntryAnimation(100.0f, 50.0f, frameNode);
    EXPECT_EQ(arcSwiperPattern.verticalEntryNodeScale_, 0);
}

/**
 * @tc.name: PlayVerticalScrollEntryAnimation004
 * @tc.desc: Test ArcSwiperPattern PlayVerticalScrollEntryAnimation004
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayVerticalScrollEntryAnimation004, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    arcSwiperPattern.PlayVerticalScrollEntryAnimation(100.0f, -20.0f, frameNode);
    EXPECT_NE(arcSwiperPattern.verticalEntryNodeBlur_, 0);
}

/**
 * @tc.name: PlayVerticalScrollEntryAnimation005
 * @tc.desc: Test ArcSwiperPattern PlayVerticalScrollEntryAnimation005
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayVerticalScrollEntryAnimation005, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    arcSwiperPattern.PlayVerticalScrollEntryAnimation(100.0f, -20.0f, frameNode);
    EXPECT_NE(arcSwiperPattern.verticalEntryNodeOpacity_, 1);
}

/**
 * @tc.name: PlayVerticalScrollEntryAnimation006
 * @tc.desc: Test ArcSwiperPattern PlayVerticalScrollEntryAnimation006
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayVerticalScrollEntryAnimation006, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    arcSwiperPattern.PlayVerticalScrollEntryAnimation(-10.0f, 5.0f, frameNode);
    EXPECT_EQ(arcSwiperPattern.verticalEntryNodeScale_, 1);
}

/**
 * @tc.name: PlayVerticalScrollEntryAnimation007
 * @tc.desc: Test ArcSwiperPattern PlayVerticalScrollEntryAnimation007
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayVerticalScrollEntryAnimation007, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    arcSwiperPattern.PlayVerticalScrollEntryAnimation(-10.0f, 5.0f, frameNode);
    EXPECT_EQ(arcSwiperPattern.verticalEntryNodeBlur_, 0);
}

/**
 * @tc.name: PlayVerticalScrollEntryAnimation008
 * @tc.desc: Test ArcSwiperPattern PlayVerticalScrollEntryAnimation008
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayVerticalScrollEntryAnimation008, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    RefPtr<ArcSwiperPattern> swiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, swiperPattern);
    ASSERT_NE(frameNode, nullptr);
    arcSwiperPattern.PlayVerticalScrollEntryAnimation(-10.0f, 5.0f, frameNode);
    EXPECT_EQ(arcSwiperPattern.verticalEntryNodeOpacity_, 1);
}

/**
 * @tc.name: ArcSwiperPattern_PlayScrollAnimation001
 * @tc.desc: Test ArcSwiperPattern PlayScrollAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, ArcSwiperPattern_PlayScrollAnimation001, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    arcSwiperPattern.disableTransitionAnimation_ = true;
    arcSwiperPattern.canChangeDirectionFlag_ = true;
    arcSwiperPattern.PlayScrollAnimation(10.0f, 5.0f);
    EXPECT_TRUE(arcSwiperPattern.canChangeDirectionFlag_);
}

/**
 * @tc.name: ArcSwiperPattern_PlayScrollAnimation002
 * @tc.desc: Test ArcSwiperPattern PlayScrollAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, ArcSwiperPattern_PlayScrollAnimation002, TestSize.Level1)
{
    ArcSwiperPattern arcSwiperPattern;
    arcSwiperPattern.PlayScrollAnimation(10.0f, 5.0f);
    EXPECT_FALSE(arcSwiperPattern.canChangeDirectionFlag_);
}

/**
 * @tc.name: PlayPropertyTranslateFlipAnimation001
 * @tc.desc: Test ArcSwiperPattern PlayPropertyTranslateFlipAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayPropertyTranslateFlipAnimation001, TestSize.Level1)
{
    RefPtr<ArcSwiperPattern> arcSwiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, arcSwiperPattern);
    RefPtr<LayoutProperty> layoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    layoutProperty->layoutDirection_ = TextDirection::RTL;
    frameNode->layoutProperty_ = layoutProperty;
    arcSwiperPattern->frameNode_ = frameNode;
    arcSwiperPattern->hasTabsAncestor_ = true;
    OffsetF offset(20.0f, 30.0f);
    arcSwiperPattern->PlayPropertyTranslateFlipAnimation(offset);
    EXPECT_TRUE(arcSwiperPattern->itemPositionInAnimation_.empty());
}

/**
 * @tc.name: PlayPropertyTranslateFlipAnimation002
 * @tc.desc: Test ArcSwiperPattern PlayPropertyTranslateFlipAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayPropertyTranslateFlipAnimation002, TestSize.Level1)
{
    RefPtr<ArcSwiperPattern> arcSwiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, arcSwiperPattern);
    RefPtr<LayoutProperty> layoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    layoutProperty->layoutDirection_ = TextDirection::RTL;
    frameNode->layoutProperty_ = layoutProperty;
    arcSwiperPattern->frameNode_ = frameNode;
    arcSwiperPattern->hasTabsAncestor_ = true;
    OffsetF offset(20.0f, 30.0f);
    arcSwiperPattern->PlayPropertyTranslateFlipAnimation(offset);
    EXPECT_TRUE(arcSwiperPattern->itemPositionInAnimation_.empty());
}

/**
 * @tc.name: PlayPropertyTranslateFlipAnimation003
 * @tc.desc: Test ArcSwiperPattern PlayPropertyTranslateFlipAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayPropertyTranslateFlipAnimation003, TestSize.Level1)
{
    RefPtr<ArcSwiperPattern> arcSwiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, arcSwiperPattern);
    RefPtr<LayoutProperty> layoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    frameNode->layoutProperty_ = layoutProperty;
    arcSwiperPattern->frameNode_ = frameNode;
    arcSwiperPattern->hasTabsAncestor_ = true;
    OffsetF offset(20.0f, 30.0f);
    arcSwiperPattern->PlayPropertyTranslateFlipAnimation(offset);
    EXPECT_TRUE(arcSwiperPattern->itemPositionInAnimation_.empty());
}

/**
 * @tc.name: PlayPropertyTranslateFlipAnimation004
 * @tc.desc: Test ArcSwiperPattern PlayPropertyTranslateFlipAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayPropertyTranslateFlipAnimation004, TestSize.Level1)
{
    RefPtr<ArcSwiperPattern> arcSwiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, arcSwiperPattern);
    RefPtr<LayoutProperty> layoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    layoutProperty->layoutDirection_ = TextDirection::RTL;
    frameNode->layoutProperty_ = layoutProperty;
    arcSwiperPattern->frameNode_ = frameNode;
    arcSwiperPattern->hasTabsAncestor_ = false;
    OffsetF offset(20.0f, 30.0f);
    arcSwiperPattern->PlayPropertyTranslateFlipAnimation(offset);
    EXPECT_TRUE(arcSwiperPattern->itemPositionInAnimation_.empty());
}

/**
 * @tc.name: PlayPropertyTranslateFlipAnimation005
 * @tc.desc: Test ArcSwiperPattern PlayPropertyTranslateFlipAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperPatternTestNg, PlayPropertyTranslateFlipAnimation005, TestSize.Level1)
{
    RefPtr<ArcSwiperPattern> arcSwiperPattern = AceType::MakeRefPtr<ArcSwiperPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, -1, arcSwiperPattern);
    RefPtr<LayoutProperty> layoutProperty = AceType::MakeRefPtr<SwiperLayoutProperty>();
    layoutProperty->layoutDirection_ = TextDirection::RTL;
    frameNode->layoutProperty_ = layoutProperty;
    arcSwiperPattern->frameNode_ = frameNode;
    arcSwiperPattern->hasTabsAncestor_ = false;
    OffsetF offset(20.0f, 30.0f);
    std::map<int32_t, SwiperItemInfo> itemPosition;
    SwiperItemInfo info;
    info.startPos = -200.0f;
    info.endPos = 0.0f;
    info.node = frameNode;
    itemPosition[1] = info;
    arcSwiperPattern->itemPosition_ = itemPosition;
    arcSwiperPattern->PlayPropertyTranslateFlipAnimation(offset);
    EXPECT_FALSE(arcSwiperPattern->itemPositionInAnimation_.empty());
}
} // namespace OHOS::Ace::NG