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

#include "core/components_ng/pattern/swiper/swiper_paint_method.h"

namespace OHOS::Ace::NG {
class ArcSwiperIndicatorModifyTestNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: SwiperCalculateIndicatorStartIndex001
 * @tc.desc: Test CalculateIndicatorStartIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, SwiperCalculateIndicatorStartIndex001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetItemCount(20);
    paintMethod->SetIsLongPressed(false);
    paintMethod->SetGestureState(GestureState::GESTURE_STATE_RELEASE_RIGHT);
    paintMethod->SetCurrentIndex(14);
    EXPECT_EQ(paintMethod->CalculateIndicatorStartIndex(0), 2);
}

/**
 * @tc.name: SwiperCalculateIndicatorStartIndex002
 * @tc.desc: Test CalculateIndicatorStartIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, SwiperCalculateIndicatorStartIndex002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetItemCount(20);
    paintMethod->SetIsLongPressed(false);
    paintMethod->SetGestureState(GestureState::GESTURE_STATE_RELEASE_RIGHT);
    paintMethod->SetCurrentIndex(19);
    EXPECT_EQ(paintMethod->CalculateIndicatorStartIndex(0), 5);
}

/**
 * @tc.name: SwiperCalculateIndicatorStartIndex003
 * @tc.desc: Test CalculateIndicatorStartIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, SwiperCalculateIndicatorStartIndex003, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetItemCount(20);
    paintMethod->SetIsLongPressed(false);
    paintMethod->SetGestureState(GestureState::GESTURE_STATE_RELEASE_LEFT);
    paintMethod->SetCurrentIndex(1);
    EXPECT_EQ(paintMethod->CalculateIndicatorStartIndex(0), 0);
}

/**
 * @tc.name: SwiperCalculateIndicatorStartIndex004
 * @tc.desc: Test CalculateIndicatorStartIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, SwiperCalculateIndicatorStartIndex004, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetItemCount(20);
    paintMethod->SetIsLongPressed(true);
    paintMethod->SetGestureState(GestureState::GESTURE_STATE_RELEASE_LEFT);
    paintMethod->SetCurrentIndex(1);
    EXPECT_EQ(paintMethod->CalculateIndicatorStartIndex(0), 0);
}

/**
 * @tc.name: SwiperCalculateIndicatorStartIndex005
 * @tc.desc: Test CalculateIndicatorStartIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, SwiperCalculateIndicatorStartIndex005, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetItemCount(20);
    paintMethod->SetIsLongPressed(true);
    paintMethod->SetGestureState(GestureState::GESTURE_STATE_FOLLOW_LEFT);
    paintMethod->SetCurrentIndex(1);
    EXPECT_EQ(paintMethod->CalculateIndicatorStartIndex(0), 0);
}

/**
 * @tc.name: SwiperCalculateIndicatorStartIndex006
 * @tc.desc: Test CalculateIndicatorStartIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, SwiperCalculateIndicatorStartIndex006, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetItemCount(20);
    paintMethod->SetIsLongPressed(false);
    paintMethod->SetGestureState(GestureState::GESTURE_STATE_RELEASE_LEFT);
    paintMethod->SetCurrentIndex(6);
    EXPECT_EQ(paintMethod->CalculateIndicatorStartIndex(5), 4);
}

/**
 * @tc.name: SwiperCalculateIndicatorStartIndex007
 * @tc.desc: Test CalculateIndicatorStartIndex
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, SwiperCalculateIndicatorStartIndex007, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetItemCount(10);
    paintMethod->SetIsLongPressed(true);
    paintMethod->SetGestureState(GestureState::GESTURE_STATE_FOLLOW_RIGHT);
    paintMethod->SetCurrentIndex(6);
    EXPECT_EQ(paintMethod->CalculateIndicatorStartIndex(5), 0);
}

/**
 * @tc.name: CalculatePointRadius001
 * @tc.desc: Test CalculatePointRadius
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculatePointRadius001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    LinearVector<float> lv(20);
    paintMethod->vectorBlackPointAngle_ = lv;
    paintMethod->vectorBlackPointRadius_ = lv;
    paintMethod->SetIsLongPressed(false);
    paintMethod->SetItemCount(20);
    paintMethod->CalculatePointRadius(0, 0);
    EXPECT_EQ(paintMethod->vectorBlackPointRadius_[0], 2.5);
}

/**
 * @tc.name: CalculatePointRadius002
 * @tc.desc: Test CalculatePointRadius
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculatePointRadius002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetIsLongPressed(false);
    paintMethod->SetItemCount(20);
    LinearVector<float> lv(20);
    paintMethod->vectorBlackPointAngle_ = lv;
    paintMethod->vectorBlackPointRadius_ = lv;
    paintMethod->CalculatePointRadius(1, 0);
    EXPECT_EQ(paintMethod->vectorBlackPointRadius_[1], 2.5);
}

/**
 * @tc.name: CalculateStartPointRadius001
 * @tc.desc: Test CalculateStartPointRadius
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculateStartPointRadius001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    LinearVector<float> lv(20);
    paintMethod->vectorBlackPointAngle_ = lv;
    paintMethod->vectorBlackPointRadius_ = lv;
    EXPECT_FALSE(paintMethod->CalculateStartPointRadius(1, 0, 0, 0, 5));
}

/**
 * @tc.name: CalculateStartPointRadius002
 * @tc.desc: Test CalculateStartPointRadius
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculateStartPointRadius002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    LinearVector<float> lv(20);
    paintMethod->vectorBlackPointAngle_ = lv;
    paintMethod->vectorBlackPointRadius_ = lv;
    EXPECT_FALSE(paintMethod->CalculateStartPointRadius(1, 0, 0, 0, 1));
}

/**
 * @tc.name: CalculateStartPointRadius003
 * @tc.desc: Test CalculateStartPointRadius
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculateStartPointRadius003, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    LinearVector<float> lv(20);
    paintMethod->vectorBlackPointAngle_ = lv;
    paintMethod->vectorBlackPointRadius_ = lv;
    EXPECT_FALSE(paintMethod->CalculateStartPointRadius(2, 0, 0, 0, 1));
}

/**
 * @tc.name: CalculateStartPointRadius004
 * @tc.desc: Test CalculateStartPointRadius
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculateStartPointRadius004, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    LinearVector<float> lv(20);
    paintMethod->vectorBlackPointAngle_ = lv;
    paintMethod->vectorBlackPointRadius_ = lv;
    EXPECT_TRUE(paintMethod->CalculateStartPointRadius(3, 0, 0, 0, 1));
}

/**
 * @tc.name: CalculateStartPointRadius005
 * @tc.desc: Test CalculateStartPointRadius
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculateStartPointRadius005, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    LinearVector<float> lv(20);
    paintMethod->vectorBlackPointAngle_ = lv;
    paintMethod->vectorBlackPointRadius_ = lv;
    EXPECT_FALSE(paintMethod->CalculateStartPointRadius(0, 0, 0, 0, 0));
}

/**
 * @tc.name: CalculateStartPointRadius006
 * @tc.desc: Test CalculateStartPointRadius
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculateStartPointRadius006, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    LinearVector<float> lv(20);
    paintMethod->vectorBlackPointAngle_ = lv;
    paintMethod->vectorBlackPointRadius_ = lv;
    EXPECT_TRUE(paintMethod->CalculateStartPointRadius(2, 0, 0, 0, 0));
}

/**
 * @tc.name: CalculateRemainPointRadius001
 * @tc.desc: Test CalculateRemainPointRadius
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculateRemainPointRadius001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetItemCount(20);
    LinearVector<float> lv(20);
    paintMethod->vectorBlackPointAngle_ = lv;
    paintMethod->vectorBlackPointRadius_ = lv;
    paintMethod->CalculateRemainPointRadius(14, 1, 1, 1, 1);
    EXPECT_EQ(paintMethod->vectorBlackPointRadius_[14], 1);
}

/**
 * @tc.name: CalculateRemainPointRadius002
 * @tc.desc: Test CalculateRemainPointRadius
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculateRemainPointRadius002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetItemCount(20);
    LinearVector<float> lv(20);
    paintMethod->vectorBlackPointAngle_ = lv;
    paintMethod->vectorBlackPointRadius_ = lv;
    paintMethod->CalculateRemainPointRadius(15, 1, 1, 1, 1);
    EXPECT_EQ(paintMethod->vectorBlackPointRadius_[15], 1);
}

/**
 * @tc.name: CalculateRemainPointRadius003
 * @tc.desc: Test CalculateRemainPointRadius
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculateRemainPointRadius003, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetItemCount(20);
    LinearVector<float> lv(20);
    paintMethod->vectorBlackPointAngle_ = lv;
    paintMethod->vectorBlackPointRadius_ = lv;
    paintMethod->CalculateRemainPointRadius(16, 1, 1, 1, 1);
    EXPECT_EQ(paintMethod->vectorBlackPointRadius_[16], 0);
}

/**
 * @tc.name: CalculateRemainPointRadius004
 * @tc.desc: Test CalculateRemainPointRadius
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculateRemainPointRadius004, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetItemCount(20);
    LinearVector<float> lv(20);
    paintMethod->vectorBlackPointAngle_ = lv;
    paintMethod->vectorBlackPointRadius_ = lv;
    paintMethod->CalculateRemainPointRadius(1, 1, 1, 1, 1);
    EXPECT_EQ(paintMethod->vectorBlackPointRadius_[1], 1);
}

/**
 * @tc.name: CalculateRemainPointRadius005
 * @tc.desc: Test CalculateRemainPointRadius
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculateRemainPointRadius005, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetItemCount(1);
    LinearVector<float> lv(20);
    paintMethod->vectorBlackPointAngle_ = lv;
    paintMethod->vectorBlackPointRadius_ = lv;
    paintMethod->CalculateRemainPointRadius(1, 1, 1, 1, 1);
    EXPECT_EQ(paintMethod->vectorBlackPointRadius_[1], 1);
}

/**
 * @tc.name: CalculateBlackPointRotateAngle001
 * @tc.desc: Test CalculateBlackPointRotateAngle
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculateBlackPointRotateAngle001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetIsLongPressed(false);
    paintMethod->SetItemCount(21);
    LinearVector<float> lv(20);
    paintMethod->vectorBlackPointAngle_ = lv;
    paintMethod->vectorBlackPointRadius_ = lv;
    EXPECT_EQ(paintMethod->CalculateBlackPointRotateAngle(5, 19), 10);
}

/**
 * @tc.name: CalculateInitIndicatorPosition001
 * @tc.desc: Test CalculateInitIndicatorPosition
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculateInitIndicatorPosition001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetItemCount(20);
    paintMethod->SetCurrentIndex(9);
    EXPECT_EQ(paintMethod->CalculateInitIndicatorPosition(), 2);
    paintMethod->SetCurrentIndex(14);
    EXPECT_EQ(paintMethod->CalculateInitIndicatorPosition(), 5);
    paintMethod->SetCurrentIndex(6);
    EXPECT_EQ(paintMethod->CalculateInitIndicatorPosition(), 0);
    paintMethod->SetItemCount(10);
    paintMethod->SetCurrentIndex(6);
    EXPECT_EQ(paintMethod->CalculateInitIndicatorPosition(), 0);
}

/**
 * @tc.name: SetFadeOutState001
 * @tc.desc: Test SetFadeOutState
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, SetFadeOutState001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetItemCount(20);
    paintMethod->SetFadeOutState(1);
    EXPECT_EQ(paintMethod->fadeOutState_, FadeOutState::FADE_OUT_BILATERAL);
    paintMethod->SetFadeOutState(0);
    EXPECT_EQ(paintMethod->fadeOutState_, FadeOutState::FADE_OUT_RIGHT);
    paintMethod->SetFadeOutState(10);
    EXPECT_EQ(paintMethod->fadeOutState_, FadeOutState::FADE_OUT_LEFT);
    paintMethod->SetItemCount(5);
    paintMethod->SetFadeOutState(10);
    EXPECT_EQ(paintMethod->fadeOutState_, FadeOutState::FADE_OUT_NONE);
}

/**
 * @tc.name: CalculateLongPointCenterAngle001
 * @tc.desc: Test CalculateLongPointCenterAngle
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculateLongPointCenterAngle001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetGestureState(GestureState::GESTURE_STATE_FOLLOW_RIGHT);
    paintMethod->CalculateLongPointCenterAngle(0.0, 0.0);
    EXPECT_EQ(paintMethod->longPointAngle_.first, 0);
    EXPECT_EQ(paintMethod->longPointAngle_.second, 0);
}

/**
 * @tc.name: CalculatePointAngle001
 * @tc.desc: Test CalculatePointAngle
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculatePointAngle001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    LinearVector<float> myVector(10);
    paintMethod->SetGestureState(GestureState::GESTURE_STATE_INIT);
    paintMethod->SetItemCount(0);
    EXPECT_EQ(paintMethod->CalculatePointAngle(myVector, 0).first, 0);
    EXPECT_EQ(paintMethod->CalculatePointAngle(myVector, 0).second, 0);
}

/**
 * @tc.name: CalculatePointAngle002
 * @tc.desc: Test CalculatePointAngle
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculatePointAngle002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetGestureState(GestureState::GESTURE_STATE_FOLLOW_RIGHT);
    LinearVector<float> myVector(10);
    paintMethod->SetItemCount(10);
    EXPECT_EQ(paintMethod->CalculatePointAngle(myVector, 0).first, 90);
    EXPECT_EQ(paintMethod->CalculatePointAngle(myVector, 0).second, 90);
}

/**
 * @tc.name: CalculatePointAngle003
 * @tc.desc: Test CalculatePointAngle
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CalculatePointAngle003, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    LinearVector<float> myVector(10);
    paintMethod->SetGestureState(GestureState::GESTURE_STATE_INIT);
    paintMethod->SetItemCount(10);
    paintMethod->circleDotIndicatorModifier_->SetInitState(false);
    EXPECT_EQ(paintMethod->CalculatePointAngle(myVector, 0).first, 90);
    EXPECT_EQ(paintMethod->CalculatePointAngle(myVector, 0).second, 90);
}

/**
 * @tc.name: GetAllPointArcAngle001
 * @tc.desc: Test GetAllPointArcAngle
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, GetAllPointArcAngle001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetGestureState(GestureState::GESTURE_STATE_INIT);
    auto circleDotIndicator = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    ASSERT_NE(circleDotIndicator, nullptr);
    LinearVector<float> FirstVector(10, 4);
    paintMethod->SetItemCount(1);
    EXPECT_EQ(paintMethod->GetAllPointArcAngle(FirstVector, 0), 4);
    paintMethod->SetItemCount(2);
    EXPECT_EQ(paintMethod->GetAllPointArcAngle(FirstVector, 1), 6);
    LinearVector<float> SecondVector(10, 5);
    paintMethod->SetItemCount(2);
    EXPECT_EQ(paintMethod->GetAllPointArcAngle(SecondVector, 10), 5);
}

/**
 * @tc.name: GetBlackPointAngle001
 * @tc.desc: Test GetBlackPointAngle
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, GetBlackPointAngle001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetGestureState(GestureState::GESTURE_STATE_INIT);
    auto circleDotIndicator = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    ASSERT_NE(circleDotIndicator, nullptr);
    LinearVector<float> myVector(10);
    paintMethod->SetItemCount(10);
    EXPECT_EQ(paintMethod->GetBlackPointAngle(myVector, 0, 0, 0), 0);
    EXPECT_EQ(paintMethod->GetBlackPointAngle(myVector, 1, 1, 2), 2);
    EXPECT_EQ(paintMethod->GetBlackPointAngle(myVector, 2, 1, 3), 3);
    EXPECT_EQ(paintMethod->GetBlackPointAngle(myVector, 1, 2, 5), 5);
    EXPECT_EQ(paintMethod->GetBlackPointAngle(myVector, 10, 10, 4), 4);
    EXPECT_EQ(paintMethod->GetBlackPointAngle(myVector, 10, 11, 3), 3);
}

/**
 * @tc.name: GetFadeOutPadding001
 * @tc.desc: Test GetFadeOutPadding
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, GetFadeOutPadding001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetGestureState(GestureState::GESTURE_STATE_INIT);
    auto circleDotIndicator = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    ASSERT_NE(circleDotIndicator, nullptr);
    LinearVector<float> myVector(10);
    paintMethod->SetItemCount(10);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(0, 0, 0, myVector, 0), 0);
    paintMethod->fadeOutState_ = FadeOutState::FADE_OUT_LEFT;
    EXPECT_EQ(paintMethod->GetFadeOutPadding(1, 0, 0, myVector, 0), 1);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(2, 1, 2, myVector, 0), 2);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(3, -1, 2, myVector, 0), 3);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(4, 1, 3, myVector, 0), 4);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(5, 2, 3, myVector, 0), 5);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(6, 0, 3, myVector, 0), 6);
    paintMethod->fadeOutState_ = FadeOutState::FADE_OUT_BILATERAL;
    EXPECT_EQ(paintMethod->GetFadeOutPadding(1, 0, 0, myVector, 0), 1);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(2, 1, 2, myVector, 0), 2);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(3, -1, 2, myVector, 0), 3);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(4, 1, 3, myVector, 0), 4);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(5, 2, 3, myVector, 0), 5);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(6, 0, 3, myVector, 0), 6);
}

/**
 * @tc.name: GetFadeOutPadding002
 * @tc.desc: Test GetFadeOutPadding
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, GetFadeOutPadding002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    auto paintMethod = AceType::DynamicCast<CircleDotIndicatorPaintMethod>(nodePaintMethod);
    ASSERT_NE(paintMethod, nullptr);
    paintMethod->SetGestureState(GestureState::GESTURE_STATE_INIT);
    auto circleDotIndicator = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    ASSERT_NE(circleDotIndicator, nullptr);
    LinearVector<float> myVector(10);
    paintMethod->SetItemCount(10);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(0, 0, 0, myVector, 0), 0);
    paintMethod->fadeOutState_ = FadeOutState::FADE_OUT_RIGHT;
    EXPECT_EQ(paintMethod->GetFadeOutPadding(0, 15, 12, myVector, 0), 0);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(1, 10, 12, myVector, 0), 1);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(3, 13, 10, myVector, 0), 3);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(5, 15, 10, myVector, 0), 5);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(10, 10, 10, myVector, 0), 10);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(9, 10, 15, myVector, 0), 9);
    paintMethod->fadeOutState_ = FadeOutState::FADE_OUT_BILATERAL;
    EXPECT_EQ(paintMethod->GetFadeOutPadding(0, 15, 12, myVector, 0), 0);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(1, 10, 12, myVector, 0), 1);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(3, 13, 10, myVector, 0), 3);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(5, 15, 10, myVector, 0), 5);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(10, 10, 10, myVector, 0), 10);
    EXPECT_EQ(paintMethod->GetFadeOutPadding(9, 10, 15, myVector, 0), 9);
}

/**
 * @tc.name: CheckIsTouchBottom001
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CheckIsTouchBottom001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorNode_ = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(4));
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();

    GestureEvent info;
    info.mainDelta_ = 1.0f;

    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(info));
}

/**
 * @tc.name: CheckIsTouchBottom002
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CheckIsTouchBottom002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetLoop(false);
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorNode_ = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(4));
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();

    GestureEvent info;
    info.mainDelta_ = 1.0f;

    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(info));
}

/**
 * @tc.name: CheckIsTouchBottom003
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CheckIsTouchBottom003, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorNode_ = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(4));
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();

    GestureEvent info;
    info.mainDelta_ = 1.0f;

    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(info));
}

/**
 * @tc.name: CheckIsTouchBottom004
 * @tc.desc: CheckIsTouchBottom
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CheckIsTouchBottom004, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorNode_ = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(4));
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();

    GestureEvent info;
    info.mainDelta_ = 1.0f;

    EXPECT_TRUE(indicatorPattern->CheckIsTouchBottom(info));
}

/**
 * @tc.name: GetAngleWithPoint001
 * @tc.desc: Test GetAngleWithPoint
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, GetAngleWithPoint001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushLayoutTask(frameNode_);
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    const PointT<float> conter = PointT(float(1.0), float(2.0));
    const PointT<float> point = PointT(float(2.0), float(2.0));
    auto angle = indicatorPattern->GetAngleWithPoint(conter, point);
    EXPECT_EQ(angle, 0);
}

/**
 * @tc.name: CircleIndicatorPaintPressIndicator001
 * @tc.desc: Test CircleDotIndicatorPaintMethod CircleIndicatorPaintPressIndicator
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CircleIndicatorPaintPressIndicator001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintMethod->circleDotIndicatorModifier_, nullptr);
    paintMethod->circleDotIndicatorModifier_->SetIsPressed(true);
    paintMethod->SetIsTouchBottom(TouchBottomType::START);
    /**
     * @tc.steps: step3. call PaintPressIndicator.
     */
    paintMethod->PaintPressIndicator(nullptr);
    paintMethod->PaintPressIndicator(&paintWrapper);
}

/**
 * @tc.name: CircleDotIndicatorUpdateContentModifier002
 * @tc.desc: Test CircleDotIndicatorPaintMethod UpdateContentModifier abnormal
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, CircleDotIndicatorUpdateContentModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto paintMethod1 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(nullptr);
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod2 = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    paintMethod2->SetAxis(Axis::VERTICAL);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper1(renderContext, geometryNode, paintProperty);
    PaintWrapper paintWrapper2(renderContext, geometryNode, paintProperty);
    PaintWrapper paintWrapper3(renderContext, nullptr, paintProperty);
    PaintWrapper paintWrapper4(renderContext, geometryNode, nullptr);

    /**
     * @tc.steps: step2. call UpdateContentModifier.
     */
    paintMethod1->UpdateContentModifier(&paintWrapper1);
    paintMethod2->UpdateContentModifier(nullptr);
    paintMethod2->UpdateContentModifier(&paintWrapper3);
    paintMethod2->UpdateContentModifier(&paintWrapper4);
    paintMethod2->UpdateContentModifier(&paintWrapper2);
    EXPECT_EQ(paintMethod2->GetAxis(), Axis::VERTICAL);
}

/**
 * @tc.name: UpdateNormalIndicator001
 * @tc.desc: Test DotIndicatorPaintMethod UpdateNormalIndicator
 * @tc.type: FUNC
 */
HWTEST_F(ArcSwiperIndicatorModifyTestNg, UpdateNormalIndicator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);

    LinearVector<float> longPointCenterX;
    longPointCenterX.push_back(20.0f);
    longPointCenterX.push_back(20.0f);

    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);

    paintMethod->gestureState_ = GestureState::GESTURE_STATE_INIT;
    paintMethod->UpdateNormalIndicator(longPointCenterX, &paintWrapper);
    EXPECT_TRUE(paintMethod->gestureState_ == GestureState::GESTURE_STATE_INIT);
}
} // namespace OHOS::Ace::NG