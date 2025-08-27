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
#include "ui/base/ace_type.h"

#include "core/components_ng/pattern/swiper_indicator/circle_dot_indicator/circle_dot_indicator_paint_method.h"

namespace OHOS::Ace::NG {
class SwiperIndicatorTestNg : public SwiperTestNg {
public:
};

/**
 * @tc.name: UpdateContentModifier001
 * @tc.desc: Test CircleDotIndicatorPaintMethod UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, UpdateContentModifier001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 3;
    paintMethod->itemCount_ = 6;
    paintMethod->UpdateContentModifier(&paintWrapper);
    EXPECT_EQ(paintMethod->currentIndex_, 2);
}

/**
 * @tc.name: CalculateBlackPointRotateAngle001
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculateBlackPointRotateAngle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculateBlackPointRotateAngle001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 3;
    paintMethod->itemCount_ = 20;
    paintMethod->isLongPressed_ = true;
    auto result = paintMethod->CalculateBlackPointRotateAngle(4, 3);
    EXPECT_EQ(result, 11);
}

/**
 * @tc.name: CalculateIndicatorStartIndex001
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculateIndicatorStartIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculateIndicatorStartIndex001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 3;
    paintMethod->itemCount_ = 20;
    paintMethod->isLongPressed_ = true;
    auto result = paintMethod->CalculateIndicatorStartIndex(4);
    EXPECT_EQ(result, 4);
}

/**
 * @tc.name: CalculateIndicatorStartIndex002
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculateIndicatorStartIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculateIndicatorStartIndex002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 19;
    paintMethod->itemCount_ = 20;
    paintMethod->isLongPressed_ = false;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    auto result = paintMethod->CalculateIndicatorStartIndex(4);
    EXPECT_EQ(result, 5);
}

/**
 * @tc.name: CalculateIndicatorStartIndex003
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculateIndicatorStartIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculateIndicatorStartIndex003, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 3;
    paintMethod->itemCount_ = 20;
    paintMethod->isLongPressed_ = false;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    auto result = paintMethod->CalculateIndicatorStartIndex(4);
    EXPECT_EQ(result, 4);
}

/**
 * @tc.name: CalculateIndicatorStartIndex004
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculateIndicatorStartIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculateIndicatorStartIndex004, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 6;
    paintMethod->itemCount_ = 20;
    paintMethod->isLongPressed_ = false;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    auto result = paintMethod->CalculateIndicatorStartIndex(4);
    EXPECT_EQ(result, 4);
}

/**
 * @tc.name: CalculatePointCenterAngle001
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculatePointCenterAngle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculatePointCenterAngle001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 0;
    paintMethod->itemCount_ = 1;
    paintMethod->isLongPressed_ = false;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    paintMethod->turnPageRate_ = 4.0f;
    paintMethod->vectorBlackPointAngle_.clear();
    for (int32_t i = 0; i < 10; ++i) {
        paintMethod->vectorBlackPointAngle_.push_back(0);
    }
    paintMethod->CalculatePointCenterAngle();
    EXPECT_EQ(paintMethod->vectorBlackPointAngle_[1], 0);
}

/**
 * @tc.name: CalculatePointCenterAngle002
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculatePointCenterAngle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculatePointCenterAngle002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 0;
    paintMethod->itemCount_ = 2;
    paintMethod->isLongPressed_ = false;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    paintMethod->turnPageRate_ = 4.0f;
    paintMethod->vectorBlackPointAngle_.clear();
    for (int32_t i = 0; i < 10; ++i) {
        paintMethod->vectorBlackPointAngle_.push_back(0);
    }
    paintMethod->CalculatePointCenterAngle();
    EXPECT_EQ(paintMethod->vectorBlackPointAngle_[1], 0);
}

/**
 * @tc.name: CalculatePointCenterAngle003
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculatePointCenterAngle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculatePointCenterAngle003, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 2;
    paintMethod->itemCount_ = 2;
    paintMethod->isLongPressed_ = false;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    paintMethod->turnPageRate_ = 4.0f;
    paintMethod->vectorBlackPointAngle_.clear();
    for (int32_t i = 0; i < 10; ++i) {
        paintMethod->vectorBlackPointAngle_.push_back(0);
    }
    paintMethod->CalculatePointCenterAngle();
    EXPECT_EQ(paintMethod->vectorBlackPointAngle_[1], 0);
}

/**
 * @tc.name: CalculatePointCenterAngle004
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculatePointCenterAngle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculatePointCenterAngle004, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 0;
    paintMethod->itemCount_ = 3;
    paintMethod->isLongPressed_ = false;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    paintMethod->turnPageRate_ = 4.0f;
    paintMethod->vectorBlackPointAngle_.clear();
    for (int32_t i = 0; i < 10; ++i) {
        paintMethod->vectorBlackPointAngle_.push_back(0);
    }
    paintMethod->CalculatePointCenterAngle();
    EXPECT_EQ(paintMethod->vectorBlackPointAngle_[1], 0);
}

/**
 * @tc.name: CalculatePointCenterAngle005
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculatePointCenterAngle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculatePointCenterAngle005, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 1;
    paintMethod->itemCount_ = 3;
    paintMethod->isLongPressed_ = false;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    paintMethod->turnPageRate_ = 4.0f;
    paintMethod->vectorBlackPointAngle_.clear();
    for (int32_t i = 0; i < 10; ++i) {
        paintMethod->vectorBlackPointAngle_.push_back(0);
    }
    paintMethod->CalculatePointCenterAngle();
    EXPECT_EQ(paintMethod->vectorBlackPointAngle_[1], 2);
}

/**
 * @tc.name: CalculatePointCenterAngle006
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculatePointCenterAngle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculatePointCenterAngle006, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 1;
    paintMethod->itemCount_ = 3;
    paintMethod->isLongPressed_ = false;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    paintMethod->turnPageRate_ = 4.0f;
    paintMethod->vectorBlackPointAngle_.clear();
    for (int32_t i = 0; i < 10; ++i) {
        paintMethod->vectorBlackPointAngle_.push_back(0);
    }
    paintMethod->CalculatePointCenterAngle();
    EXPECT_EQ(paintMethod->vectorBlackPointAngle_[1], -2);
}

/**
 * @tc.name: CalculatePointCenterAngle007
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculatePointCenterAngle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculatePointCenterAngle007, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 1;
    paintMethod->itemCount_ = 2;
    paintMethod->isLongPressed_ = false;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    paintMethod->turnPageRate_ = 4.0f;
    paintMethod->vectorBlackPointAngle_.clear();
    for (int32_t i = 0; i < 10; ++i) {
        paintMethod->vectorBlackPointAngle_.push_back(0);
    }
    paintMethod->CalculatePointCenterAngle();
    EXPECT_EQ(paintMethod->vectorBlackPointAngle_[1], -2);
}

/**
 * @tc.name: CalculatePointCenterAngle008
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculatePointCenterAngle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculatePointCenterAngle008, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 1;
    paintMethod->itemCount_ = 3;
    paintMethod->isLongPressed_ = false;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    paintMethod->turnPageRate_ = 4.0f;
    paintMethod->vectorBlackPointAngle_.clear();
    for (int32_t i = 0; i < 10; ++i) {
        paintMethod->vectorBlackPointAngle_.push_back(0);
    }
    paintMethod->CalculatePointCenterAngle();
    EXPECT_EQ(paintMethod->vectorBlackPointAngle_[1], -2);
}

/**
 * @tc.name: CalculatePointCenterAngle009
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculatePointCenterAngle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculatePointCenterAngle009, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 2;
    paintMethod->itemCount_ = 3;
    paintMethod->isLongPressed_ = false;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    paintMethod->turnPageRate_ = 4.0f;
    paintMethod->vectorBlackPointAngle_.clear();
    for (int32_t i = 0; i < 10; ++i) {
        paintMethod->vectorBlackPointAngle_.push_back(0);
    }
    paintMethod->CalculatePointCenterAngle();
    EXPECT_EQ(paintMethod->vectorBlackPointAngle_[1], 0);
}

/**
 * @tc.name: CalculatePointCenterAngle010
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculatePointCenterAngle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculatePointCenterAngle010, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 1;
    paintMethod->itemCount_ = 3;
    paintMethod->isLongPressed_ = false;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    paintMethod->turnPageRate_ = 4.0f;
    paintMethod->vectorBlackPointAngle_.clear();
    for (int32_t i = 0; i < 10; ++i) {
        paintMethod->vectorBlackPointAngle_.push_back(0);
    }
    paintMethod->CalculatePointCenterAngle();
    EXPECT_EQ(paintMethod->vectorBlackPointAngle_[1], -2);
}

/**
 * @tc.name: CalculatePointCenterAngle011
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculatePointCenterAngle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculatePointCenterAngle011, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 2;
    paintMethod->itemCount_ = 4;
    paintMethod->isLongPressed_ = false;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    paintMethod->turnPageRate_ = 4.0f;
    paintMethod->vectorBlackPointAngle_.clear();
    for (int32_t i = 0; i < 10; ++i) {
        paintMethod->vectorBlackPointAngle_.push_back(0);
    }
    paintMethod->CalculatePointCenterAngle();
    EXPECT_EQ(paintMethod->vectorBlackPointAngle_[1], 0);
}

/**
 * @tc.name: CalculatePointCenterAngle012
 * @tc.desc: Test CircleDotIndicatorPaintMethod CalculatePointCenterAngle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, CalculatePointCenterAngle012, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->currentIndex_ = 3;
    paintMethod->itemCount_ = 4;
    paintMethod->isLongPressed_ = false;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_LEFT;
    paintMethod->turnPageRate_ = 4.0f;
    paintMethod->vectorBlackPointAngle_.clear();
    for (int32_t i = 0; i < 10; ++i) {
        paintMethod->vectorBlackPointAngle_.push_back(0);
    }
    paintMethod->CalculatePointCenterAngle();
    EXPECT_EQ(paintMethod->vectorBlackPointAngle_[1], 2);
}

/**
 * @tc.name: GetIndexOnRTL001
 * @tc.desc: Test CircleDotIndicatorPaintMethod GetIndexOnRTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetIndexOnRTL001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->turnPageRate_ = 0.5f;
    auto result = paintMethod->GetIndexOnRTL(2);
    EXPECT_EQ(result.first, 3);
}

/**
 * @tc.name: GetIndexOnRTL002
 * @tc.desc: Test CircleDotIndicatorPaintMethod GetIndexOnRTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetIndexOnRTL002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->turnPageRate_ = 0.0f;
    auto result = paintMethod->GetIndexOnRTL(2);
    EXPECT_NE(result.first, 1);
}

/**
 * @tc.name: GetIndexOnRTL003
 * @tc.desc: Test CircleDotIndicatorPaintMethod GetIndexOnRTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetIndexOnRTL003, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->turnPageRate_ = 0.0f;
    paintMethod->itemCount_ = 2;
    auto result = paintMethod->GetIndexOnRTL(-1);
    EXPECT_EQ(result.first, 1);
}

/**
 * @tc.name: GetIndexOnRTL004
 * @tc.desc: Test CircleDotIndicatorPaintMethod GetIndexOnRTL
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetIndexOnRTL004, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->turnPageRate_ = 0.0f;
    paintMethod->itemCount_ = 2;
    auto result = paintMethod->GetIndexOnRTL(2);
    EXPECT_NE(result.first, 1);
}

/**
 * @tc.name: GetIndex001
 * @tc.desc: Test CircleDotIndicatorPaintMethod GetIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetIndex001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->turnPageRate_ = 0.5f;
    paintMethod->isHorizontalAndRightToLeft_ = true;
    paintMethod->GetIndex(2);
    EXPECT_NE(paintMethod->turnPageRate_, 0);
}

/**
 * @tc.name: GetIndex002
 * @tc.desc: Test CircleDotIndicatorPaintMethod GetIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetIndex002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->turnPageRate_ = 0.5f;
    paintMethod->isHorizontalAndRightToLeft_ = true;
    auto result = paintMethod->GetIndex(2);
    EXPECT_EQ(result.first, 3);
}

/**
 * @tc.name: GetIndex003
 * @tc.desc: Test CircleDotIndicatorPaintMethod GetIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetIndex003, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->turnPageRate_ = 0.5f;
    paintMethod->isHorizontalAndRightToLeft_ = false;
    paintMethod->itemCount_ = 2;
    auto result = paintMethod->GetIndex(2);
    EXPECT_EQ(result.second, 0);
}

/**
 * @tc.name: GetStartAndEndIndex001
 * @tc.desc: Test CircleDotIndicatorPaintMethod GetStartAndEndIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetStartAndEndIndex001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->turnPageRate_ = 0.5f;
    paintMethod->isHorizontalAndRightToLeft_ = false;
    paintMethod->itemCount_ = 2;
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_LEFT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    auto result = paintMethod->GetStartAndEndIndex(2);
    EXPECT_EQ(result.second, 2);
}

/**
 * @tc.name: GetStartAndEndIndex002
 * @tc.desc: Test CircleDotIndicatorPaintMethod GetStartAndEndIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetStartAndEndIndex002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->turnPageRate_ = 0.5f;
    paintMethod->isHorizontalAndRightToLeft_ = false;
    paintMethod->itemCount_ = 2;
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_EXPAND_TO_LONG_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    auto result = paintMethod->GetStartAndEndIndex(2);
    EXPECT_EQ(result.second, 2);
}

/**
 * @tc.name: GetStartAndEndIndex003
 * @tc.desc: Test CircleDotIndicatorPaintMethod GetStartAndEndIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetStartAndEndIndex003, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->turnPageRate_ = 0.5f;
    paintMethod->isHorizontalAndRightToLeft_ = false;
    paintMethod->itemCount_ = 2;
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_EXPAND_TO_LONG_POINT;
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    auto result = paintMethod->GetStartAndEndIndex(2);
    EXPECT_EQ(result.second, 0);
}

/**
 * @tc.name: GetStartAndEndIndex004
 * @tc.desc: Test CircleDotIndicatorPaintMethod GetStartAndEndIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, GetStartAndEndIndex004, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->turnPageRate_ = 0.5f;
    paintMethod->isHorizontalAndRightToLeft_ = false;
    paintMethod->itemCount_ = 2;
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    auto result = paintMethod->GetStartAndEndIndex(2);
    EXPECT_EQ(result.second, 0);
}

/**
 * @tc.name: UpdateBackground001
 * @tc.desc: Test CircleDotIndicatorPaintMethod UpdateBackground
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, UpdateBackground001, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->turnPageRate_ = 0.5f;
    paintMethod->isHorizontalAndRightToLeft_ = false;
    paintMethod->itemCount_ = 16;
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    paintMethod->longPointAngle_ = { 6, 6 };
    LinearVector<float> itemHalfSizes(16, 0.0f);
    itemHalfSizes[0] = 10.0f;
    paintMethod->vectorBlackPointAngle_ = itemHalfSizes;
    paintMethod->touchBottomRate_ = 2.0f;
    paintMethod->touchBottomType_ = TouchBottomType::END;
    paintMethod->UpdateBackground(&paintWrapper);
    EXPECT_EQ(paintMethod->circleDotIndicatorModifier_->dotActiveStartAngle_->value_, -36);
}

/**
 * @tc.name: UpdateBackground002
 * @tc.desc: Test CircleDotIndicatorPaintMethod UpdateBackground
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, UpdateBackground002, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->turnPageRate_ = 0.5f;
    paintMethod->isHorizontalAndRightToLeft_ = false;
    paintMethod->itemCount_ = 16;
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    paintMethod->longPointAngle_ = { 6, 6 };
    LinearVector<float> itemHalfSizes(16, 0.0f);
    itemHalfSizes[0] = 10.0f;
    paintMethod->vectorBlackPointAngle_ = itemHalfSizes;
    paintMethod->touchBottomRate_ = 2.0f;
    paintMethod->touchBottomType_ = TouchBottomType::END;
    paintMethod->UpdateBackground(&paintWrapper);
    EXPECT_EQ(paintMethod->circleDotIndicatorModifier_->vectorBlackPointAngle_->value_[0], 10);
}

/**
 * @tc.name: UpdateBackground003
 * @tc.desc: Test CircleDotIndicatorPaintMethod UpdateBackground
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, UpdateBackground003, TestSize.Level1)
{
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<CircleDotIndicatorModifier> modifier = AceType::MakeRefPtr<CircleDotIndicatorModifier>();
    auto paintMethod = AceType::MakeRefPtr<CircleDotIndicatorPaintMethod>(modifier);
    auto geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto paintProperty = AceType::MakeRefPtr<CircleDotIndicatorPaintProperty>();
    auto renderContext = frameNode_->GetRenderContext();
    PaintWrapper paintWrapper(renderContext, geometryNode, paintProperty);
    paintMethod->SetAxis(Axis::VERTICAL);
    paintMethod->turnPageRate_ = 0.5f;
    paintMethod->isHorizontalAndRightToLeft_ = false;
    paintMethod->itemCount_ = 16;
    paintMethod->pointAnimationStage_ = PointAnimationStage::STATE_SHRINKT_TO_BLACK_POINT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    paintMethod->longPointAngle_ = { 6, 6 };
    LinearVector<float> itemHalfSizes(16, 0.0f);
    itemHalfSizes[0] = 10.0f;
    paintMethod->vectorBlackPointAngle_ = itemHalfSizes;
    paintMethod->touchBottomRate_ = 2.0f;
    paintMethod->touchBottomType_ = TouchBottomType::START;
    paintMethod->UpdateBackground(&paintWrapper);
    EXPECT_EQ(paintMethod->circleDotIndicatorModifier_->vectorBlackPointAngle_->value_[0], 52);
}

/**
 * @tc.name: NeedBottomAnimation001
 * @tc.desc: Test NeedBottomAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestNg, NeedBottomAnimation001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    RefPtr<DotIndicatorModifier> modifier = AceType::MakeRefPtr<DotIndicatorModifier>();
    RefPtr<DotIndicatorPaintMethod> paintMethod = AceType::MakeRefPtr<DotIndicatorPaintMethod>(modifier);
    paintMethod->gestureState_ = GestureState::GESTURE_STATE_RELEASE_RIGHT;
    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    paintMethod->targetIndex_ = 0;
    paintMethod->touchBottomPageRate_ = 0.2;
    paintMethod->currentIndexActual_ = 0;
    EXPECT_TRUE(paintMethod->NeedBottomAnimation());

    paintMethod->targetIndex_ = 3;
    EXPECT_FALSE(paintMethod->NeedBottomAnimation());

    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_RIGHT;
    paintMethod->touchBottomPageRate_ = 0;
    paintMethod->currentIndexActual_ = 0;
    paintMethod->firstIndex_ = 0;
    EXPECT_TRUE(paintMethod->NeedBottomAnimation());

    paintMethod->touchBottomPageRate_ = 0.6;
    EXPECT_FALSE(paintMethod->NeedBottomAnimation());

    paintMethod->touchBottomPageRate_ = 0;
    EXPECT_TRUE(paintMethod->NeedBottomAnimation());

    paintMethod->itemCount_ = 4;
    paintMethod->currentIndexActual_ = 3;
    paintMethod->firstIndex_ = 0;
    EXPECT_FALSE(paintMethod->NeedBottomAnimation());

    paintMethod->touchBottomTypeLoop_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    paintMethod->touchBottomPageRate_ = 0;
    paintMethod->currentIndexActual_ = 0;
    paintMethod->firstIndex_ = 3;
    paintMethod->itemCount_ = 4;
    EXPECT_TRUE(paintMethod->NeedBottomAnimation());
}
} // namespace OHOS::Ace::NG
