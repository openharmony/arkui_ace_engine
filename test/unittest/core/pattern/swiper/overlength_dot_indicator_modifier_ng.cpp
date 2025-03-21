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

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/overlength_dot_indicator_modifier.h"

namespace OHOS::Ace::NG {
class SwiperIndicatorTestNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: RevertOverlongType001
 * @tc.desc: Test OverlengthDotIndicatorModifier RevertOverlongType
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, RevertOverlongType001, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    auto result = modifier.RevertOverlongType(OverlongType::LEFT_NORMAL_RIGHT_FADEOUT);
    EXPECT_EQ(result, OverlongType::LEFT_FADEOUT_RIGHT_NORMAL);
}

/**
 * @tc.name: RevertOverlongType002
 * @tc.desc: Test OverlengthDotIndicatorModifier RevertOverlongType
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, RevertOverlongType002, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    auto result = modifier.RevertOverlongType(OverlongType::LEFT_FADEOUT_RIGHT_NORMAL);
    EXPECT_EQ(result, OverlongType::LEFT_NORMAL_RIGHT_FADEOUT);
}

/**
 * @tc.name: RevertOverlongType003
 * @tc.desc: Test OverlengthDotIndicatorModifier RevertOverlongType
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, RevertOverlongType003, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    auto result = modifier.RevertOverlongType(OverlongType::NONE);
    EXPECT_EQ(result, OverlongType::NONE);
}

/**
 * @tc.name: UpdateSelectedCenterXOnDrag001
 * @tc.desc: Test OverlengthDotIndicatorModifier UpdateSelectedCenterXOnDrag
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, UpdateSelectedCenterXOnDrag001, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.overlongSelectedEndCenterX_.first = 5.0f;
    modifier.overlongSelectedEndCenterX_.second = 2.0f;
    modifier.UpdateSelectedCenterXOnDrag(itemHalfSizes);
    EXPECT_EQ(modifier.overlongSelectedEndCenterX_.first, 5.0f);
}

/**
 * @tc.name: UpdateSelectedCenterXOnDrag002
 * @tc.desc: Test OverlengthDotIndicatorModifier UpdateSelectedCenterXOnDrag
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, UpdateSelectedCenterXOnDrag002, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.overlongSelectedEndCenterX_.first = 5.0f;
    modifier.overlongSelectedEndCenterX_.second = 2.0f;
    modifier.UpdateSelectedCenterXOnDrag(itemHalfSizes);
    EXPECT_NE(modifier.overlongSelectedEndCenterX_.first, 5.0f);
}

/**
 * @tc.name: UpdateSelectedCenterXOnDrag003
 * @tc.desc: Test OverlengthDotIndicatorModifier UpdateSelectedCenterXOnDrag
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, UpdateSelectedCenterXOnDrag003, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.overlongSelectedEndCenterX_.first = 5.0f;
    modifier.overlongSelectedEndCenterX_.second = 2.0f;
    modifier.UpdateSelectedCenterXOnDrag(itemHalfSizes);
    EXPECT_NE(modifier.overlongSelectedEndCenterX_.first, 5.0f);
}

/**
 * @tc.name: UpdateSelectedCenterXOnDrag004
 * @tc.desc: Test OverlengthDotIndicatorModifier UpdateSelectedCenterXOnDrag
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, UpdateSelectedCenterXOnDrag004, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    modifier.overlongSelectedEndCenterX_.first = 5.0f;
    modifier.overlongSelectedEndCenterX_.second = 2.0f;
    modifier.targetSelectedIndex_ = 1;
    modifier.UpdateSelectedCenterXOnDrag(itemHalfSizes);
    EXPECT_EQ(modifier.overlongSelectedEndCenterX_.first, 0.0f);
}

/**
 * @tc.name: UpdateSelectedCenterXOnDrag005
 * @tc.desc: Test OverlengthDotIndicatorModifier UpdateSelectedCenterXOnDrag
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, UpdateSelectedCenterXOnDrag005, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    modifier.overlongSelectedEndCenterX_.first = 5.0f;
    modifier.overlongSelectedEndCenterX_.second = 2.0f;
    modifier.UpdateSelectedCenterXOnDrag(itemHalfSizes);
    EXPECT_EQ(modifier.overlongSelectedEndCenterX_.first, 0.0f);
}

/**
 * @tc.name: UpdateSelectedCenterXOnDrag006
 * @tc.desc: Test OverlengthDotIndicatorModifier UpdateSelectedCenterXOnDrag
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, UpdateSelectedCenterXOnDrag006, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    modifier.overlongSelectedEndCenterX_.first = 5.0f;
    modifier.overlongSelectedEndCenterX_.second = 2.0f;
    modifier.isSwiperTouchDown_ = true;
    modifier.UpdateSelectedCenterXOnDrag(itemHalfSizes);
    EXPECT_EQ(modifier.overlongSelectedEndCenterX_.first, 0.0f);
}

/**
 * @tc.name: UpdateSelectedCenterXOnDrag007
 * @tc.desc: Test OverlengthDotIndicatorModifier UpdateSelectedCenterXOnDrag
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, UpdateSelectedCenterXOnDrag007, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    modifier.overlongSelectedEndCenterX_.first = 5.0f;
    modifier.overlongSelectedEndCenterX_.second = 2.0f;
    modifier.isSwiperTouchDown_ = true;
    modifier.targetSelectedIndex_ = 1;
    modifier.UpdateSelectedCenterXOnDrag(itemHalfSizes);
    EXPECT_EQ(modifier.overlongSelectedEndCenterX_.first, 0.0f);
}

/**
 * @tc.name: GetMoveRateOnAllMove001
 * @tc.desc: Test OverlengthDotIndicatorModifier GetMoveRateOnAllMove
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetMoveRateOnAllMove001, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    auto result = modifier.GetMoveRateOnAllMove();
    EXPECT_EQ(result, 1.0f);
}

/**
 * @tc.name: GetMoveRateOnAllMove002
 * @tc.desc: Test OverlengthDotIndicatorModifier GetMoveRateOnAllMove
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetMoveRateOnAllMove002, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    auto result = modifier.GetMoveRateOnAllMove();
    EXPECT_EQ(result, 1.0f);
}

/**
 * @tc.name: GetMoveRateOnAllMove003
 * @tc.desc: Test OverlengthDotIndicatorModifier GetMoveRateOnAllMove
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetMoveRateOnAllMove003, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    auto result = modifier.GetMoveRateOnAllMove();
    EXPECT_NE(result, 1.0f);
}

/**
 * @tc.name: CalcTargetStatusOnLongPointMove001
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnLongPointMove
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnLongPointMove001, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 4;
    modifier.CalcTargetStatusOnLongPointMove(itemHalfSizes);
    EXPECT_EQ(modifier.animationEndIndicatorHeight_.size(), 4);
}

/**
 * @tc.name: CalcTargetStatusOnLongPointMove002
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnLongPointMove
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnLongPointMove002, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 4;
    modifier.isSwiperTouchDown_ = true;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    modifier.currentSelectedIndex_ = 2;
    modifier.turnPageRate_ = 2.0f;
    modifier.CalcTargetStatusOnLongPointMove(itemHalfSizes);
    EXPECT_EQ(modifier.targetSelectedIndex_, 2);
}

/**
 * @tc.name: CalcTargetStatusOnLongPointMove003
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnLongPointMove
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnLongPointMove003, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 4;
    modifier.isSwiperTouchDown_ = true;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    modifier.currentSelectedIndex_ = 2;
    modifier.turnPageRate_ = 2.0f;
    modifier.CalcTargetStatusOnLongPointMove(itemHalfSizes);
    EXPECT_EQ(modifier.targetSelectedIndex_, 2);
}
/**
 * @tc.name: CalcTargetStatusOnLongPointMove004
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnLongPointMove
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnLongPointMove004, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 4;
    modifier.isSwiperTouchDown_ = true;
    modifier.gestureState_ = GestureState::GESTURE_STATE_NONE;
    modifier.currentSelectedIndex_ = 2;
    modifier.CalcTargetStatusOnLongPointMove(itemHalfSizes);
    EXPECT_NE(modifier.targetSelectedIndex_, 2);
}

/**
 * @tc.name: CalcTargetStatusOnLongPointMove005
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnLongPointMove
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnLongPointMove005, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 4;
    modifier.isSwiperTouchDown_ = false;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    modifier.currentSelectedIndex_ = 2;
    modifier.CalcTargetStatusOnLongPointMove(itemHalfSizes);
    EXPECT_NE(modifier.targetSelectedIndex_, 2);
}

/**
 * @tc.name: CalcTargetStatusOnLongPointMove006
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnLongPointMove
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnLongPointMove006, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 4;
    modifier.isSwiperTouchDown_ = false;
    modifier.gestureState_ = GestureState::GESTURE_STATE_NONE;
    modifier.currentSelectedIndex_ = 2;
    modifier.CalcTargetStatusOnLongPointMove(itemHalfSizes);
    EXPECT_NE(modifier.targetSelectedIndex_, 2);
}

/**
 * @tc.name: CalcTargetStatusOnLongPointMove007
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnLongPointMove
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnLongPointMove007, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 4;
    modifier.isSwiperTouchDown_ = true;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    modifier.currentSelectedIndex_ = 2;
    modifier.turnPageRate_ = 0.0f;
    modifier.CalcTargetStatusOnLongPointMove(itemHalfSizes);
    EXPECT_NE(modifier.targetSelectedIndex_, 2);
}

/**
 * @tc.name: CalcTargetStatusOnLongPointMove008
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnLongPointMove
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnLongPointMove008, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 4;
    modifier.isSwiperTouchDown_ = true;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    modifier.currentSelectedIndex_ = 2;
    modifier.turnPageRate_ = 0.0f;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.CalcTargetStatusOnLongPointMove(itemHalfSizes);
    EXPECT_EQ(modifier.targetSelectedIndex_, 2);
}

/**
 * @tc.name: CalcTargetStatusOnLongPointMove009
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnLongPointMove
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnLongPointMove009, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 4;
    modifier.isSwiperTouchDown_ = true;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    modifier.currentSelectedIndex_ = 2;
    modifier.turnPageRate_ = 2.0f;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.CalcTargetStatusOnLongPointMove(itemHalfSizes);
    EXPECT_EQ(modifier.targetSelectedIndex_, 2);
}

/**
 * @tc.name: CalcTargetStatusOnLongPointMove010
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnLongPointMove
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnLongPointMove010, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 4;
    modifier.isSwiperTouchDown_ = true;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    modifier.currentSelectedIndex_ = 2;
    modifier.turnPageRate_ = 2.0f;
    modifier.CalcTargetStatusOnLongPointMove(itemHalfSizes);
    EXPECT_EQ(modifier.targetSelectedIndex_, 2);
}

/**
 * @tc.name: CalcTargetStatusOnAllPointMoveForward001
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnAllPointMoveForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnAllPointMoveForward001, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.isSwiperTouchDown_ = true;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    modifier.currentSelectedIndex_ = 2;
    modifier.targetSelectedIndex_ = 4;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f};
    modifier.maxDisplayCount_ = 2;
    modifier.animationStartIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndCenterX_ = { 10.0f, 10.0f, 10.0f};
    modifier.animationEndIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.CalcTargetStatusOnAllPointMoveForward(itemHalfSizes);
    EXPECT_EQ(modifier.targetSelectedIndex_, 2);
}

/**
 * @tc.name: CalcTargetStatusOnAllPointMoveForward002
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnAllPointMoveForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnAllPointMoveForward002, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 2;
    modifier.isSwiperTouchDown_ = true;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    modifier.currentSelectedIndex_ = 2;
    modifier.turnPageRate_ = 2.0f;
    modifier.targetSelectedIndex_ = 4;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.CalcTargetStatusOnAllPointMoveForward(itemHalfSizes);
    EXPECT_EQ(modifier.targetSelectedIndex_, 2);
}
/**
 * @tc.name: CalcTargetStatusOnAllPointMoveForward003
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnAllPointMoveForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnAllPointMoveForward003, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 2;
    modifier.isSwiperTouchDown_ = true;
    modifier.gestureState_ = GestureState::GESTURE_STATE_NONE;
    modifier.currentSelectedIndex_ = 2;
    modifier.targetSelectedIndex_ = 4;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.CalcTargetStatusOnAllPointMoveForward(itemHalfSizes);
    EXPECT_NE(modifier.targetSelectedIndex_, 2);
}

/**
 * @tc.name: CalcTargetStatusOnAllPointMoveForward004
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnAllPointMoveForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnAllPointMoveForward004, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 2;
    modifier.isSwiperTouchDown_ = false;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    modifier.currentSelectedIndex_ = 2;
    modifier.targetSelectedIndex_ = 4;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.CalcTargetStatusOnAllPointMoveForward(itemHalfSizes);
    EXPECT_NE(modifier.targetSelectedIndex_, 2);
}

/**
 * @tc.name: CalcTargetStatusOnAllPointMoveForward005
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnAllPointMoveForward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnAllPointMoveForward005, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 2;
    modifier.isSwiperTouchDown_ = false;
    modifier.gestureState_ = GestureState::GESTURE_STATE_NONE;
    modifier.currentSelectedIndex_ = 2;
    modifier.targetSelectedIndex_ = 4;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.CalcTargetStatusOnAllPointMoveForward(itemHalfSizes);
    EXPECT_NE(modifier.targetSelectedIndex_, 2);
}

/**
 * @tc.name: CalcTargetStatusOnAllPointMoveBackward001
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnAllPointMoveBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnAllPointMoveBackward001, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.isSwiperTouchDown_ = true;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    modifier.currentSelectedIndex_ = 2;
    modifier.targetSelectedIndex_ = 4;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 2;
    modifier.animationStartIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndCenterX_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.CalcTargetStatusOnAllPointMoveBackward(itemHalfSizes);
    EXPECT_EQ(modifier.targetSelectedIndex_, 2);
}

/**
 * @tc.name: CalcTargetStatusOnAllPointMoveBackward002
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnAllPointMoveBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnAllPointMoveBackward002, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 2;
    modifier.isSwiperTouchDown_ = true;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    modifier.currentSelectedIndex_ = 2;
    modifier.turnPageRate_ = 2.0f;
    modifier.targetSelectedIndex_ = 4;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.CalcTargetStatusOnAllPointMoveBackward(itemHalfSizes);
    EXPECT_EQ(modifier.targetSelectedIndex_, 2);
}
/**
 * @tc.name: CalcTargetStatusOnAllPointMoveBackward003
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnAllPointMoveBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnAllPointMoveBackward003, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 2;
    modifier.isSwiperTouchDown_ = true;
    modifier.gestureState_ = GestureState::GESTURE_STATE_NONE;
    modifier.currentSelectedIndex_ = 2;
    modifier.targetSelectedIndex_ = 4;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.CalcTargetStatusOnAllPointMoveBackward(itemHalfSizes);
    EXPECT_NE(modifier.targetSelectedIndex_, 2);
}

/**
 * @tc.name: CalcTargetStatusOnAllPointMoveBackward004
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnAllPointMoveBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnAllPointMoveBackward004, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 2;
    modifier.isSwiperTouchDown_ = false;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    modifier.currentSelectedIndex_ = 2;
    modifier.targetSelectedIndex_ = 4;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.CalcTargetStatusOnAllPointMoveBackward(itemHalfSizes);
    EXPECT_NE(modifier.targetSelectedIndex_, 2);
}

/**
 * @tc.name: CalcTargetStatusOnAllPointMoveBackward005
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetStatusOnAllPointMoveBackward
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetStatusOnAllPointMoveBackward005, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 2;
    modifier.isSwiperTouchDown_ = false;
    modifier.gestureState_ = GestureState::GESTURE_STATE_NONE;
    modifier.currentSelectedIndex_ = 2;
    modifier.targetSelectedIndex_ = 4;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.CalcTargetStatusOnAllPointMoveBackward(itemHalfSizes);
    EXPECT_NE(modifier.targetSelectedIndex_, 2);
}

/**
 * @tc.name: CalcAnimationEndCenterX001
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcAnimationEndCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcAnimationEndCenterX001, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.isSwiperTouchDown_ = true;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    modifier.currentSelectedIndex_ = 3;
    modifier.targetSelectedIndex_ = 4;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 2;
    modifier.animationStartIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndCenterX_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.turnPageRate_ = 2.0f;
    modifier.animationStartIndex_ = 4;
    modifier.animationEndIndex_ = 4;
    modifier.realItemCount_ = 6;
    modifier.CalcAnimationEndCenterX(itemHalfSizes);
    EXPECT_EQ(modifier.animationStartIndex_, 4);
}

/**
 * @tc.name: CalcAnimationEndCenterX002
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcAnimationEndCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcAnimationEndCenterX002, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 2;
    modifier.isSwiperTouchDown_ = true;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    modifier.currentSelectedIndex_ = 3;
    modifier.turnPageRate_ = 2.0f;
    modifier.targetSelectedIndex_ = 4;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndex_ = 4;
    modifier.animationEndIndex_ = 4;
    modifier.realItemCount_ = 6;
    modifier.CalcAnimationEndCenterX(itemHalfSizes);
    EXPECT_EQ(modifier.animationStartIndex_, 4);
}
/**
 * @tc.name: CalcAnimationEndCenterX003
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcAnimationEndCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcAnimationEndCenterX003, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 2;
    modifier.isSwiperTouchDown_ = true;
    modifier.gestureState_ = GestureState::GESTURE_STATE_NONE;
    modifier.currentSelectedIndex_ = 2;
    modifier.targetSelectedIndex_ = 4;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndex_ = 4;
    modifier.animationEndIndex_ = 4;
    modifier.realItemCount_ = 6;
    modifier.CalcAnimationEndCenterX(itemHalfSizes);
    EXPECT_EQ(modifier.animationStartIndex_, 4);
}

/**
 * @tc.name: CalcAnimationEndCenterX004
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcAnimationEndCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcAnimationEndCenterX004, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 2;
    modifier.isSwiperTouchDown_ = false;
    modifier.gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    modifier.currentSelectedIndex_ = 2;
    modifier.targetSelectedIndex_ = 4;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndex_ = 4;
    modifier.animationEndIndex_ = 4;
    modifier.realItemCount_ = 6;
    modifier.CalcAnimationEndCenterX(itemHalfSizes);
    EXPECT_EQ(modifier.animationStartIndex_, 4);
}

/**
 * @tc.name: CalcAnimationEndCenterX005
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcAnimationEndCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcAnimationEndCenterX005, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 2;
    modifier.isSwiperTouchDown_ = false;
    modifier.gestureState_ = GestureState::GESTURE_STATE_NONE;
    modifier.currentSelectedIndex_ = 2;
    modifier.targetSelectedIndex_ = 4;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndex_ = 4;
    modifier.animationEndIndex_ = 4;
    modifier.realItemCount_ = 6;
    modifier.CalcAnimationEndCenterX(itemHalfSizes);
    EXPECT_EQ(modifier.animationStartIndex_, 4);
}

/**
 * @tc.name: CalcAnimationEndCenterX006
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcAnimationEndCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcAnimationEndCenterX006, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 2;
    modifier.isSwiperTouchDown_ = false;
    modifier.gestureState_ = GestureState::GESTURE_STATE_NONE;
    modifier.currentSelectedIndex_ = 4;
    modifier.targetSelectedIndex_ = 4;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndex_ = 4;
    modifier.animationEndIndex_ = 5;
    modifier.realItemCount_ = 6;
    modifier.moveDirection_ = OverlongIndicatorMove::MOVE_FORWARD;
    modifier.CalcAnimationEndCenterX(itemHalfSizes);
    EXPECT_EQ(modifier.moveDirection_, OverlongIndicatorMove::NONE);
}

/**
 * @tc.name: CalcAnimationEndCenterX007
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcAnimationEndCenterX
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcAnimationEndCenterX007, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    LinearVector<float> itemHalfSizes(3, 0.0f);
    itemHalfSizes[0] = 10.0f;
    modifier.touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.maxDisplayCount_ = 2;
    modifier.isSwiperTouchDown_ = false;
    modifier.gestureState_ = GestureState::GESTURE_STATE_NONE;
    modifier.currentSelectedIndex_ = 4;
    modifier.targetSelectedIndex_ = 4;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.animationStartCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndCenterX_ = { 10.0f, 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorWidth_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationEndIndicatorHeight_ = { 10.0f, 10.0f, 10.0f };
    modifier.animationStartIndex_ = 5;
    modifier.animationEndIndex_ = 4;
    modifier.realItemCount_ = 6;
    modifier.CalcAnimationEndCenterX(itemHalfSizes);
    EXPECT_NE(modifier.moveDirection_, OverlongIndicatorMove::MOVE_BACKWARD);
}

/**
 * @tc.name: InitOverlongSelectedIndex001
 * @tc.desc: Test OverlengthDotIndicatorModifier InitOverlongSelectedIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, InitOverlongSelectedIndex001, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.maxDisplayCount_ = 6;
    modifier.realItemCount_ = 8;
    modifier.InitOverlongSelectedIndex(4);
    EXPECT_EQ(modifier.targetSelectedIndex_, 3);
}

/**
 * @tc.name: InitOverlongSelectedIndex002
 * @tc.desc: Test OverlengthDotIndicatorModifier InitOverlongSelectedIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, InitOverlongSelectedIndex002, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.maxDisplayCount_ = 8;
    modifier.realItemCount_ = 6;
    modifier.InitOverlongSelectedIndex(4);
    EXPECT_EQ(modifier.targetSelectedIndex_, 4);
}

/**
 * @tc.name: InitOverlongSelectedIndex003
 * @tc.desc: Test OverlengthDotIndicatorModifier InitOverlongSelectedIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, InitOverlongSelectedIndex003, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.maxDisplayCount_ = 6;
    modifier.realItemCount_ = 5;
    modifier.InitOverlongSelectedIndex(4);
    EXPECT_EQ(modifier.targetSelectedIndex_, 5);
}

/**
 * @tc.name: InitOverlongSelectedIndex004
 * @tc.desc: Test OverlengthDotIndicatorModifier InitOverlongSelectedIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, InitOverlongSelectedIndex004, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.maxDisplayCount_ = 8;
    modifier.realItemCount_ = 8;
    modifier.InitOverlongSelectedIndex(4);
    EXPECT_EQ(modifier.targetSelectedIndex_, 4);
}

/**
 * @tc.name: InitOverlongSelectedIndex005
 * @tc.desc: Test OverlengthDotIndicatorModifier InitOverlongSelectedIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, InitOverlongSelectedIndex005, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.maxDisplayCount_ = 10;
    modifier.realItemCount_ = 15;
    modifier.InitOverlongSelectedIndex(13);
    EXPECT_EQ(modifier.targetSelectedIndex_, 8);
}

/**
 * @tc.name: InitOverlongSelectedIndex006
 * @tc.desc: Test OverlengthDotIndicatorModifier InitOverlongSelectedIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, InitOverlongSelectedIndex006, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.maxDisplayCount_ = 10;
    modifier.realItemCount_ = 12;
    modifier.InitOverlongSelectedIndex(11);
    EXPECT_EQ(modifier.targetSelectedIndex_, 9);
}

/**
 * @tc.name: InitOverlongStatus001
 * @tc.desc: Test OverlengthDotIndicatorModifier InitOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, InitOverlongStatus001, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.maxDisplayCount_ = 6;
    modifier.realItemCount_ = 8;
    modifier.InitOverlongStatus(4);
    EXPECT_EQ(modifier.targetSelectedIndex_, 3);
}

/**
 * @tc.name: InitOverlongStatus002
 * @tc.desc: Test OverlengthDotIndicatorModifier InitOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, InitOverlongStatus002, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.maxDisplayCount_ = 8;
    modifier.realItemCount_ = 6;
    modifier.InitOverlongStatus(4);
    EXPECT_EQ(modifier.targetSelectedIndex_, 4);
}

/**
 * @tc.name: InitOverlongStatus003
 * @tc.desc: Test OverlengthDotIndicatorModifier InitOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, InitOverlongStatus003, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.maxDisplayCount_ = 6;
    modifier.realItemCount_ = 5;
    modifier.InitOverlongStatus(4);
    EXPECT_EQ(modifier.targetSelectedIndex_, 5);
}

/**
 * @tc.name: InitOverlongStatus004
 * @tc.desc: Test OverlengthDotIndicatorModifier InitOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, InitOverlongStatus004, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.maxDisplayCount_ = 8;
    modifier.realItemCount_ = 8;
    modifier.InitOverlongStatus(4);
    EXPECT_EQ(modifier.targetSelectedIndex_, 4);
}

/**
 * @tc.name: InitOverlongStatus005
 * @tc.desc: Test OverlengthDotIndicatorModifier InitOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, InitOverlongStatus005, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.maxDisplayCount_ = 10;
    modifier.realItemCount_ = 15;
    modifier.InitOverlongStatus(13);
    EXPECT_EQ(modifier.targetSelectedIndex_, 8);
}

/**
 * @tc.name: InitOverlongStatus006
 * @tc.desc: Test OverlengthDotIndicatorModifier InitOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, InitOverlongStatus006, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.maxDisplayCount_ = 10;
    modifier.realItemCount_ = 12;
    modifier.InitOverlongStatus(11);
    EXPECT_EQ(modifier.targetSelectedIndex_, 9);
}

/**
 * @tc.name: CalcTargetOverlongStatus001
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetOverlongStatus001, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    modifier.realItemCount_ = 12;
    modifier.CalcTargetOverlongStatus(11, 0);
    EXPECT_EQ(modifier.targetOverlongType_, OverlongType::LEFT_NORMAL_RIGHT_FADEOUT);
}

/**
 * @tc.name: CalcTargetOverlongStatus002
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetOverlongStatus002, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    modifier.targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    modifier.targetSelectedIndex_ = 3;
    modifier.realItemCount_ = 1;
    modifier.maxDisplayCount_ = 10;
    modifier.CalcTargetOverlongStatus(0, 2);
    EXPECT_NE(modifier.targetSelectedIndex_, 0);
}

/**
 * @tc.name: CalcTargetOverlongStatus003
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetOverlongStatus003, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.realItemCount_ = 12;
    modifier.maxDisplayCount_ = 10;
    modifier.CalcTargetOverlongStatus(5, 0);
    EXPECT_EQ(modifier.targetOverlongType_, OverlongType::LEFT_NORMAL_RIGHT_FADEOUT);
}

/**
 * @tc.name: CalcTargetOverlongStatus004
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetOverlongStatus004, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.realItemCount_ = 12;
    modifier.maxDisplayCount_ = 10;
    modifier.CalcTargetOverlongStatus(5, 2);
    EXPECT_NE(modifier.targetOverlongType_, OverlongType::LEFT_FADEOUT_RIGHT_NORMAL);
}

/**
 * @tc.name: CalcTargetOverlongStatus005
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetOverlongStatus005, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.currentOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.targetSelectedIndex_ = 3;
    modifier.realItemCount_ = 1;
    modifier.maxDisplayCount_ = 10;
    modifier.CalcTargetOverlongStatus(0, 2);
    EXPECT_NE(modifier.targetOverlongType_, OverlongType::LEFT_FADEOUT_RIGHT_NORMAL);
}

/**
 * @tc.name: CalcTargetOverlongStatus006
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetOverlongStatus006, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.currentOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    modifier.targetSelectedIndex_ = 3;
    modifier.realItemCount_ = 1;
    modifier.maxDisplayCount_ = 10;
    modifier.CalcTargetOverlongStatus(0, 2);
    EXPECT_EQ(modifier.targetOverlongType_, OverlongType::LEFT_NORMAL_RIGHT_FADEOUT);
}

/**
 * @tc.name: CalcTargetOverlongStatus007
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetOverlongStatus007, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.currentOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    modifier.targetSelectedIndex_ = 7;
    modifier.realItemCount_ = 1;
    modifier.maxDisplayCount_ = 5;
    modifier.CalcTargetOverlongStatus(0, 2);
    EXPECT_EQ(modifier.targetOverlongType_, OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT);
}

/**
 * @tc.name: CalcTargetOverlongStatus008
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetOverlongStatus008, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT;
    modifier.targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    modifier.targetSelectedIndex_ = 7;
    modifier.realItemCount_ = 4;
    modifier.maxDisplayCount_ = 10;
    modifier.CalcTargetOverlongStatus(0, 2);
    EXPECT_EQ(modifier.targetOverlongType_, OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT);
}

/**
 * @tc.name: CalcTargetOverlongStatus009
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetOverlongStatus009, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT;
    modifier.targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    modifier.targetSelectedIndex_ = 7;
    modifier.realItemCount_ = 3;
    modifier.maxDisplayCount_ = 10;
    modifier.CalcTargetOverlongStatus(2, 3);
    EXPECT_EQ(modifier.targetOverlongType_, OverlongType::LEFT_FADEOUT_RIGHT_NORMAL);
}

/**
 * @tc.name: CalcTargetOverlongStatus010
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetOverlongStatus010, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.currentOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    modifier.targetSelectedIndex_ = 7;
    modifier.realItemCount_ = 3;
    modifier.maxDisplayCount_ = 10;
    modifier.CalcTargetOverlongStatus(3, 2);
    EXPECT_EQ(modifier.targetOverlongType_, OverlongType::LEFT_NORMAL_RIGHT_FADEOUT);
}

/**
 * @tc.name: CalcTargetOverlongStatus011
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetOverlongStatus011, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    modifier.targetOverlongType_ = OverlongType::LEFT_NORMAL_RIGHT_FADEOUT;
    modifier.targetSelectedIndex_ = 8;
    modifier.realItemCount_ = 3;
    modifier.maxDisplayCount_ = 10;
    modifier.CalcTargetOverlongStatus(3, 2);
    EXPECT_EQ(modifier.targetOverlongType_, OverlongType::LEFT_NORMAL_RIGHT_FADEOUT);
}

/**
 * @tc.name: CalcTargetOverlongStatus012
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetOverlongStatus012, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    modifier.targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    modifier.targetSelectedIndex_ = 7;
    modifier.realItemCount_ = 3;
    modifier.maxDisplayCount_ = 10;
    modifier.CalcTargetOverlongStatus(3, 2);
    EXPECT_EQ(modifier.targetOverlongType_, OverlongType::LEFT_NORMAL_RIGHT_FADEOUT);
}

/**
 * @tc.name: CalcTargetOverlongStatus013
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetOverlongStatus013, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT;
    modifier.targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    modifier.targetSelectedIndex_ = 8;
    modifier.realItemCount_ = 3;
    modifier.maxDisplayCount_ = 10;
    modifier.CalcTargetOverlongStatus(3, 2);
    EXPECT_EQ(modifier.targetOverlongType_, OverlongType::LEFT_NORMAL_RIGHT_FADEOUT);
}

/**
 * @tc.name: CalcTargetOverlongStatus014
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetOverlongStatus014, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT;
    modifier.targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    modifier.targetSelectedIndex_ = 7;
    modifier.realItemCount_ = 4;
    modifier.maxDisplayCount_ = 10;
    modifier.CalcTargetOverlongStatus(4, 3);
    EXPECT_EQ(modifier.targetOverlongType_, OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT);
}

/**
 * @tc.name: CalcTargetOverlongStatus015
 * @tc.desc: Test OverlengthDotIndicatorModifier CalcTargetOverlongStatus
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalcTargetOverlongStatus015, TestSize.Level1)
{
    OverlengthDotIndicatorModifier modifier;
    modifier.currentOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_FADEOUT;
    modifier.targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    modifier.targetSelectedIndex_ = 7;
    modifier.realItemCount_ = 3;
    modifier.maxDisplayCount_ = 10;
    modifier.CalcTargetOverlongStatus(3, 2);
    EXPECT_EQ(modifier.targetOverlongType_, OverlongType::LEFT_NORMAL_RIGHT_FADEOUT);
}
} // namespace OHOS::Ace::NG