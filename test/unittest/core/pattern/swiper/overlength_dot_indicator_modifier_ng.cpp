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
} // namespace OHOS::Ace::NG