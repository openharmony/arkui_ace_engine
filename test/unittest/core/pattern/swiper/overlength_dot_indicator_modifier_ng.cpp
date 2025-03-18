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
    std::cout << "999" << std::endl;
    EXPECT_EQ(modifier.targetSelectedIndex_, 2);
    std::cout << "789" << std::endl;
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
} // namespace OHOS::Ace::NG