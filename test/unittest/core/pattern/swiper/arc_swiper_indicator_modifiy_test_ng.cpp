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
    CreateWithItem([](SwiperModelNG model) {
        model.Create(true);
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::ARC_DOT);
    });
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
    CreateWithItem([](SwiperModelNG model) {
        model.Create(true);
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::ARC_DOT);
    });
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
    CreateWithItem([](SwiperModelNG model) {
        model.Create(true);
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::ARC_DOT);
    });
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
    CreateWithItem([](SwiperModelNG model) {
        model.Create(true);
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::ARC_DOT);
    });
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
    CreateWithItem([](SwiperModelNG model) {
        model.Create(true);
        model.SetDirection(Axis::VERTICAL);
        model.SetIndicatorType(SwiperIndicatorType::ARC_DOT);
    });
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
} // namespace OHOS::Ace::NG
