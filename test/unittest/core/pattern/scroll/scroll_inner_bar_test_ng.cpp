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
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

class ScrollBarTestNg : public TestNG {
public:
};

/**
 * @tc.name: CheckBarDirection
 * @tc.desc: Test ScrollBar CheckBarDirection
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, checkBarDirection, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollBar> scrollBar = AceType::MakeRefPtr<ScrollBar>();

    /**
     * @tc.steps: step2. Set the scrollbar shape to the default mode and set the offset
     */
    scrollBar->SetShapeMode(ShapeMode::DEFAULT);
    Point offset(2.0, 2.0);

    /**
     * @tc.steps: step3. Test When the point is outside the scrollbar area
     * @tc.expected: The checkBarDirection should be called to return a direction of BAR_NONE
     */
    auto result = scrollBar->CheckBarDirection(offset);
    EXPECT_EQ(result, BarDirection::BAR_NONE);
}

/**
 * @tc.name: SetRoundTrickRegion
 * @tc.desc: Test ScrollBar SetRoundTrickRegion
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, SetRoundTrickRegion, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollBar> scrollBar = AceType::MakeRefPtr<ScrollBar>();

    /**
     * @tc.steps: step2. Set the scrollbar position to the left mode
     */
    scrollBar->positionMode_ = PositionMode::LEFT;

    /**
     * @tc.steps: step3. Test When the set estimatedHeight is not equal to the diameter,
     * and the result of calculating trickStartAngle is greater than 0
     * @tc.expected: The scrollbar trickStartAngle is STRAIGHT_ANGLE - calculated trickStartAngle,
     * and trickSweepAngle becomes the opposite number
     */
    Offset offset(60.0, 100.0);
    Size size(100.0, 200.0);
    Offset lastOffset(150.0, 300.0);
    scrollBar->SetRoundTrickRegion(offset, size, lastOffset, 400.0);
    EXPECT_EQ(scrollBar->trickStartAngle_, 165.0);
    EXPECT_EQ(scrollBar->trickSweepAngle_, -15.0);
}

/**
 * @tc.name: CalcPatternOffset001
 * @tc.desc: Test ScrollBar CalcPatternOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, CalcPatternOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollBar> scrollBar = AceType::MakeRefPtr<ScrollBar>();

    /**
     * @tc.steps: step2. Set the scrollbar position to the bottom mode
     * and set the isDriving is false
     */
    scrollBar->positionMode_ = PositionMode::BOTTOM;

    /**
     * @tc.steps: step3. Set the isDriving is false
     * @tc.expected: The scrollbar CalcPatternOffset return current scrollBarOffset
     */
    scrollBar->isDriving_ = false;
    Rect activeRect(40.0, 60.0, 60.0, 100.0);
    scrollBar->activeRect_ = activeRect;
    auto result = scrollBar->CalcPatternOffset(6.0f);
    EXPECT_EQ(result, 6.0f);
}

/**
 * @tc.name: CalcPatternOffset002
 * @tc.desc: Test ScrollBar CalcPatternOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, CalcPatternOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollBar> scrollBar = AceType::MakeRefPtr<ScrollBar>();

    /**
     * @tc.steps: step2. Set the scrollbar position to the right mode
     */
    scrollBar->positionMode_ = PositionMode::RIGHT;

    /**
     * @tc.steps: step3. Set the isDriving is true and set the barRegionSize is close to the activeRectLength
     * @tc.expected: The scrollbar CalcPatternOffset return current scrollBarOffset
     */
    scrollBar->isDriving_ = true;
    scrollBar->barRegionSize_ = 100.0;
    Rect activeRect(40.0, 60.0, 60.0, 100.0);
    scrollBar->activeRect_ = activeRect;
    auto result = scrollBar->CalcPatternOffset(2.0f);
    EXPECT_EQ(result, 2.0f);
}

/**
 * @tc.name: ProcessFrictionMotion001
 * @tc.desc: Test ScrollBar ProcessFrictionMotion
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ProcessFrictionMotion001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollBar> scrollBar = AceType::MakeRefPtr<ScrollBar>();

    /**
     * @tc.steps: step2. Set the scrollbar scrollPositionCallback to return false
     */
    scrollBar->scrollPositionCallback_ = [](double position, int32_t source, bool isMouseWheelScroll) { return false; };

    /**
     * @tc.steps: step3. Set the frictionController and set the frictionController status is running
     * @tc.expected: The frictionController status is stop
     */
    RefPtr<PipelineBase> context = AceType::MakeRefPtr<PipelineContext>();
    auto frictionController = Animator::CreateAnimator(nullptr, context, nullptr);
    frictionController->status_ = Animator::Status::RUNNING;
    scrollBar->frictionController_ = frictionController;
    scrollBar->ProcessFrictionMotion(2.0);
    EXPECT_EQ(scrollBar->frictionController_->status_, Animator::Status::STOPPED);
}

/**
 * @tc.name: ProcessFrictionMotion002
 * @tc.desc: Test ScrollBar ProcessFrictionMotion
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ProcessFrictionMotion002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollBar> scrollBar = AceType::MakeRefPtr<ScrollBar>();

    /**
     * @tc.steps: step2. Set the scrollbar scrollPositionCallback to return false
     */
    scrollBar->scrollPositionCallback_ = [](double position, int32_t source, bool isMouseWheelScroll) { return false; };

    /**
     * @tc.steps: step3. Set the frictionController and set the frictionController IsRunning return false
     * @tc.expected: The scrollBar frictionPosition is passed value
     */
    RefPtr<PipelineBase> context = AceType::MakeRefPtr<PipelineContext>();
    auto frictionController = Animator::CreateAnimator(nullptr, context, nullptr);
    frictionController->status_ = Animator::Status::IDLE;
    scrollBar->frictionController_ = frictionController;
    scrollBar->ProcessFrictionMotion(2.0);
    EXPECT_EQ(scrollBar->frictionPosition_, 2.0f);
}

/**
 * @tc.name: ProcessFrictionMotion003
 * @tc.desc: Test ScrollBar ProcessFrictionMotion
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ProcessFrictionMotion003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollBar> scrollBar = AceType::MakeRefPtr<ScrollBar>();

    /**
     * @tc.steps: step2. Set the scrollbar scrollPositionCallback to return false
     */
    scrollBar->scrollPositionCallback_ = [](double position, int32_t source, bool isMouseWheelScroll) { return false; };

    /**
     * @tc.steps: step3. Set the frictionController is empty
     * @tc.expected: The scrollBar frictionPosition is passed value
     */
    scrollBar->frictionController_ = nullptr;
    scrollBar->ProcessFrictionMotion(4.0);
    EXPECT_EQ(scrollBar->frictionPosition_, 4.0f);
}

/**
 * @tc.name: ProcessFrictionMotion004
 * @tc.desc: Test ScrollBar ProcessFrictionMotion
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ProcessFrictionMotion004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollBar> scrollBar = AceType::MakeRefPtr<ScrollBar>();

    /**
     * @tc.steps: step2. Set the scrollbar scrollPositionCallback to return true
     */
    scrollBar->scrollPositionCallback_ = [](double position, int32_t source, bool isMouseWheelScroll) { return true; };

    /**
     * @tc.steps: step3. Set the frictionController is empty
     * @tc.expected: The scrollBar frictionPosition is passed value
     */
    scrollBar->frictionController_ = nullptr;
    scrollBar->ProcessFrictionMotion(8.0);
    EXPECT_EQ(scrollBar->frictionPosition_, 8.0f);
}

/**
 * @tc.name: ProcessFrictionMotion005
 * @tc.desc: Test ScrollBar ProcessFrictionMotion
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ProcessFrictionMotion005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollBar> scrollBar = AceType::MakeRefPtr<ScrollBar>();

    /**
     * @tc.steps: step2. Set the scrollbar scrollPositionCallback is empty
     */
    scrollBar->scrollPositionCallback_ = nullptr;

    /**
     * @tc.steps: step3. Set the frictionController is empty
     * @tc.expected: The scrollBar frictionPosition is passed value
     */
    scrollBar->frictionController_ = nullptr;
    scrollBar->ProcessFrictionMotion(10.0);
    EXPECT_EQ(scrollBar->frictionPosition_, 10.0f);
}

/**
 * @tc.name: ProcessFrictionMotionStop001
 * @tc.desc: Test ScrollBar ProcessFrictionMotionStop
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ProcessFrictionMotionStop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollBar> scrollBar = AceType::MakeRefPtr<ScrollBar>();

    /**
     * @tc.steps: step2. Set a verdict value and set scrollPositionCallback
     */
    bool scrollEnd = false;
    scrollBar->scrollEndCallback_ = [&scrollEnd]() { scrollEnd = true; };

    /**
     * @tc.steps: step3. Call the ProcessFrictionMotionStop to trigger scrollPositionCallback
     * @tc.expected: The scrollEnd become true
     */
    scrollBar->ProcessFrictionMotionStop();
    EXPECT_TRUE(scrollEnd);
}

/**
 * @tc.name: ProcessFrictionMotionStop002
 * @tc.desc: Test ScrollBar ProcessFrictionMotionStop
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, ProcessFrictionMotionStop002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollBar> scrollBar = AceType::MakeRefPtr<ScrollBar>();

    /**
     * @tc.steps: step2. Set the scrollPositionCallback to empty and isDriving is true
     */
    scrollBar->scrollEndCallback_ = nullptr;
    scrollBar->isDriving_ = true;

    /**
     * @tc.steps: step3. Call the ProcessFrictionMotionStop
     * @tc.expected: The scrollBar isDriving is false
     */
    scrollBar->ProcessFrictionMotionStop();
    EXPECT_FALSE(scrollBar->isDriving_);
}

/**
 * @tc.name: AddScrollBarLayoutInfo
 * @tc.desc: Test ScrollBar AddScrollBarLayoutInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, AddScrollBarLayoutInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollBar> scrollBar = AceType::MakeRefPtr<ScrollBar>();

    /**
     * @tc.steps: step2. Set the scrollBar needAddLayoutInfo is true
     */
    scrollBar->needAddLayoutInfo = true;
    scrollBar->innerScrollBarLayoutInfos_.clear();
    /**
     * @tc.steps: step3. Add 30 elements to the innerScrollBarLayoutInfos
     * @tc.expected: The first element estimatedHeight is 300.0 and the last element estimatedHeight is 600.0
     */
    InnerScrollBarLayoutInfo info;
    info.estimatedHeight_ = 200.0;
    scrollBar->innerScrollBarLayoutInfos_.push_front(info);
    for (int i = 1; i <= 29; ++i) {
        scrollBar->innerScrollBarLayoutInfos_.push_back(InnerScrollBarLayoutInfo({
            .layoutTime_ = 0,
            .viewPortSize_ = Size(100.0, 200.0),
            .lastOffset_ = Offset(10.0, 20.0),
            .estimatedHeight_ = 300.0,
            .outBoundary_ = 400.0,
            .activeRect_ = Rect(50.0, 60.0, 70.0, 80.0),
        }));
    }
    scrollBar->estimatedHeight_ = 600.0;
    scrollBar->AddScrollBarLayoutInfo();
    EXPECT_EQ(scrollBar->innerScrollBarLayoutInfos_.front().estimatedHeight_, 300.0);
    EXPECT_EQ(scrollBar->innerScrollBarLayoutInfos_.back().estimatedHeight_, 600.0);
}

/**
 * @tc.name: OnCollectLongPressTarget
 * @tc.desc: Test ScrollBar OnCollectLongPressTarget
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, OnCollectLongPressTarget, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ScrollBar> scrollBar = AceType::MakeRefPtr<ScrollBar>();
    RefPtr<ScrollablePattern> scrollablePattern = AceType::MakeRefPtr<ListPattern>();

    /**
     * @tc.steps: step2. Set scrollBar longPressRecognizer and the isScrollable_ is true
     */
    RefPtr<LongPressRecognizer> longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(true, true);
    scrollBar->longPressRecognizer_ = longPressRecognizer;
    scrollBar->isScrollable_ = true;

    /**
     * @tc.steps: step3. Set the OnCollectLongPressTarget parameters
     * @tc.expected: The coordinateOffset value of longPressRecognizer is updated
     */
    OffsetF coordinateOffset(4.0f, 5.0f);
    GetEventTargetImpl getEventTargetImpl = []() -> std::optional<EventTarget> {
        EventTarget target;
        target.id = "";
        target.type = "";
        target.area = DimensionRect(Dimension(10.0), Dimension(20.0), DimensionOffset(Offset(10.0, 20.0)));
        target.origin = DimensionOffset(Dimension(5.0), Dimension(5.0));
        return target;
    };
    std::list<RefPtr<TouchEventTarget>> result;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollablePattern);
    ASSERT_NE(frameNode, nullptr);
    auto targetComponent = AceType::MakeRefPtr<TargetComponent>();
    std::list<RefPtr<NG::NGGestureRecognizer>> responseLinkResult;
    scrollBar->OnCollectLongPressTarget(
        coordinateOffset, getEventTargetImpl, result, frameNode, targetComponent, responseLinkResult);
    EXPECT_EQ(scrollBar->longPressRecognizer_->coordinateOffset_.GetX(), 4.0f);
    EXPECT_EQ(scrollBar->longPressRecognizer_->coordinateOffset_.GetY(), 5.0f);
}

/**
 * @tc.name: GetHoverOffset001
 * @tc.desc: Test ScrollBarOverlayModifier GetHoverOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetHoverOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    OffsetF barOffset(10.0f, 12.0f);
    SizeF barSize(20.0f, 30.0f);
    auto modifier = AceType::MakeRefPtr<ScrollBarOverlayModifier>(barOffset, barSize);

    /**
     * @tc.steps: step2. Set the position to the bottom mode and set the barHeight
     */
    modifier->positionMode_ = PositionMode::BOTTOM;
    RefPtr<AnimatablePropertyFloat> barHeight = AceType::MakeRefPtr<AnimatablePropertyFloat>(barOffset.GetY());
    modifier->barHeight_ = barHeight;

    /**
     * @tc.steps: step3. Set the size
     * @tc.expected: return the hover offset Y value is size.Height() - barHeight_->Get()
     */
    Size size(10.0f, 20.0f);
    auto result = modifier->GetHoverOffset(size);
    EXPECT_EQ(result.GetY(), 8.0f);
}

/**
 * @tc.name: GetHoverOffset002
 * @tc.desc: Test ScrollBarOverlayModifier GetHoverOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, GetHoverOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    OffsetF barOffset(10.0f, 12.0f);
    SizeF barSize(20.0f, 30.0f);
    auto modifier = AceType::MakeRefPtr<ScrollBarOverlayModifier>(barOffset, barSize);

    /**
     * @tc.steps: step2. Set the position to the left mode
     */
    modifier->positionMode_ = PositionMode::LEFT;

    /**
     * @tc.steps: step3. Set the size
     * @tc.expected: return the hover offset value is Offset::Zero()
     */
    Size size(10.0f, 20.0f);
    auto result = modifier->GetHoverOffset(size);
    EXPECT_EQ(result.GetY(), 0.0f);
}

/**
 * @tc.name: CheckMainModeNearEqual001
 * @tc.desc: Test ScrollBarOverlayModifier CheckMainModeNearEqual
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarTestNg, CheckMainModeNearEqual001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    OffsetF barOffset(10.0f, 12.0f);
    SizeF barSize(20.0f, 30.0f);
    auto modifier = AceType::MakeRefPtr<ScrollBarOverlayModifier>(barOffset, barSize);

    /**
     * @tc.steps: step2. Set isAdaptAnimationStop is false and the position to bottom mode
     */
    modifier->isAdaptAnimationStop_ = false;
    modifier->positionMode_ = PositionMode::BOTTOM;

    /**
     * @tc.steps: step3. Set the barWidth, barX, lastMainModeHeight, lastMainModeOffset
     * @tc.expected: The lastMainModeHeight and lastMainModeOffset value is changed
     */
    modifier->barWidth_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(barOffset.GetY());
    modifier->barX_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(barOffset.GetX());
    modifier->lastMainModeHeight_ = 12.3f;
    modifier->lastMainModeOffset_ = 15.0f;
    modifier->CheckMainModeNearEqual();
    EXPECT_EQ(modifier->lastMainModeHeight_, 12.0f);
    EXPECT_EQ(modifier->lastMainModeOffset_, 10.0f);
}
} // namespace OHOS::Ace::NG