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

#include "core/components/web/web_event.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

namespace {
constexpr float SCROLL_PAGING_SPEED_THRESHOLD = 1200.0f;
} // namespace

class ScrollPatternTwoTestNg : public TestNG {
public:
    void SetUp() {};
    void TearDown() {};
};

/**
 * @tc.name: GetScrollSnapPagination001
 * @tc.desc: Test ScrollPattern GetScrollSnapPagination
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, GetScrollSnapPagination001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->snapPaginations_.clear();
    scrollPattern->intervalSize_ = Dimension(2.0);
    auto result = scrollPattern->GetScrollSnapPagination();
    EXPECT_EQ(result, "2.00px");
}

/**
 * @tc.name: GetScrollSnapPagination002
 * @tc.desc: Test ScrollPattern GetScrollSnapPagination
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, GetScrollSnapPagination002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->snapPaginations_ = { Dimension(4.0), Dimension(5.0) };
    scrollPattern->intervalSize_ = Dimension(6.0);
    auto result = scrollPattern->GetScrollSnapPagination();
    EXPECT_EQ(result, "[4.00px 5.00px ]");
}

/**
 * @tc.name: StartSnapAnimation
 * @tc.desc: Test ScrollPattern StartSnapAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, StartSnapAnimation, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    RefPtr<ScrollBar> scrollBar = AceType::MakeRefPtr<ScrollBar>(DisplayMode::OFF);
    scrollBar->isDriving_ = true;
    scrollPattern->scrollBar_ = scrollBar;
    scrollPattern->scrollBarProxy_ = AceType::MakeRefPtr<NG::ScrollBarProxy>();
    SnapAnimationOptions options;
    options.fromScrollBar = false;
    auto result = scrollPattern->StartSnapAnimation(options);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Test ScrollPattern ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, ToJsonValue001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    filter.filterFixed = 3;
    filter.filterExt.clear();
    scrollPattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("initialOffset"), "");
}

/**
 * @tc.name: ToJsonValue002
 * @tc.desc: Test ScrollPattern ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, ToJsonValue002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    filter.filterFixed = 0;
    filter.filterExt.clear();
    scrollPattern->intervalSize_ = Dimension(8.0);
    scrollPattern->initialOffset_ = OffsetT<CalcDimension>(CalcDimension("1.0"), CalcDimension("2.0"));
    scrollPattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetValue("initialOffset")->GetString("xOffset"), "1.0calc");
    EXPECT_EQ(json->GetValue("initialOffset")->GetString("yOffset"), "2.0calc");
    EXPECT_EQ(json->GetString("enablePaging"), "");
    EXPECT_EQ(json->GetValue("scrollSnap")->GetString("snapPagination"), "8.00px");
}

/**
 * @tc.name: ToJsonValue003
 * @tc.desc: Test ScrollPattern ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, ToJsonValue003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    filter.filterFixed = 0;
    filter.filterExt.clear();
    scrollPattern->enablePagingStatus_ = ScrollPagingStatus::VALID;
    scrollPattern->snapPaginations_ = { Dimension(4.0), Dimension(5.0) };
    scrollPattern->enableSnapToSide_ = { true, false };
    scrollPattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetValue("scrollSnap")->GetValue("snapPagination")->GetString("0"), "4.00px");
    EXPECT_EQ(json->GetValue("scrollSnap")->GetValue("snapPagination")->GetString("1"), "5.00px");
}

/**
 * @tc.name: AddScrollMeasureInfo001
 * @tc.desc: Test ScrollPattern AddScrollMeasureInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, AddScrollMeasureInfo001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ScrollMeasureInfo info;
    info.selfSize_ = SizeF(100.0, 200.0);
    scrollPattern->scrollMeasureInfos_.clear();
    scrollPattern->scrollMeasureInfos_.push_front(info);
    std::optional<LayoutConstraintF> parentConstraint;
    std::optional<LayoutConstraintF> childConstraint;
    SizeF selfSize(10.0, 20.0);
    SizeF childSize(50.0, 100.0);
    for (int i = 1; i <= 29; ++i) {
        scrollPattern->scrollMeasureInfos_.push_back(ScrollMeasureInfo({
            .changedTime_ = 0,
            .parentConstraint_ = parentConstraint,
            .childConstraint_ = childConstraint,
            .selfSize_ = SizeF(20.0, 40.0),
            .childSize_ = childSize,
        }));
    }
    scrollPattern->AddScrollMeasureInfo(parentConstraint, childConstraint, selfSize, childSize);
    EXPECT_EQ(scrollPattern->scrollMeasureInfos_.front().selfSize_.Width(), 20.0);
    EXPECT_EQ(scrollPattern->scrollMeasureInfos_.back().selfSize_.Width(), 10.0);
}

/**
 * @tc.name: AddScrollLayoutInfo001
 * @tc.desc: Test ScrollPattern AddScrollLayoutInfo
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, AddScrollLayoutInfo001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ScrollLayoutInfo info;
    info.scrollableDistance_ = 2.0f;
    scrollPattern->scrollLayoutInfos_.clear();
    scrollPattern->scrollLayoutInfos_.push_front(info);
    for (int i = 1; i <= 29; ++i) {
        scrollPattern->scrollLayoutInfos_.push_back(ScrollLayoutInfo({
            .changedTime_ = 0,
            .scrollableDistance_ = 4.0f,
            .scrollSize_ = SizeF(10.0, 20.0),
            .viewPort_ = SizeF(30.0, 40.0),
            .childSize_ = SizeF(50.0, 60.0),
        }));
    }
    scrollPattern->scrollableDistance_ = 8.0f;
    scrollPattern->viewSize_ = SizeF(10.0, 20.0);
    scrollPattern->viewPort_ = SizeF(30.0, 40.0);
    scrollPattern->viewPortExtent_ = SizeF(50.0, 60.0);
    scrollPattern->AddScrollLayoutInfo();
    EXPECT_EQ(scrollPattern->scrollLayoutInfos_.front().scrollableDistance_, 4.0f);
    EXPECT_EQ(scrollPattern->scrollLayoutInfos_.back().scrollableDistance_, 8.0f);
}

/**
 * @tc.name: GetPagingDelta001
 * @tc.desc: Test ScrollPattern GetPagingDelta
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, GetPagingDelta001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto result = scrollPattern->GetPagingDelta(3.f, 4.f, 6.f);
    EXPECT_EQ(result, 6.0f);
}

/**
 * @tc.name: GetPagingDelta002
 * @tc.desc: Test ScrollPattern GetPagingDelta
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, GetPagingDelta002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto result = scrollPattern->GetPagingDelta(3.f, -4.f, 6.f);
    EXPECT_EQ(result, 6.0f);
}

/**
 * @tc.name: GetPagingDelta003
 * @tc.desc: Test ScrollPattern GetPagingDelta
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, GetPagingDelta003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto result = scrollPattern->GetPagingDelta(3.f, -SCROLL_PAGING_SPEED_THRESHOLD, -6.f);
    EXPECT_EQ(result, 0.f);
}

/**
 * @tc.name: GetPagingDelta004
 * @tc.desc: Test ScrollPattern GetPagingDelta
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, GetPagingDelta004, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto result = scrollPattern->GetPagingDelta(4.f, -SCROLL_PAGING_SPEED_THRESHOLD, -6.f);
    EXPECT_EQ(result, 0.f);
}

/**
 * @tc.name: GetPagingOffset001
 * @tc.desc: Test ScrollPattern GetPagingOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, GetPagingOffset001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->currentOffset_ = 4.f;
    scrollPattern->scrollableDistance_ = 2.f;
    scrollPattern->viewPortLength_ = 3.f;
    auto result = scrollPattern->GetPagingOffset(2.f, 4.f, 6.f);
    EXPECT_EQ(result, 3.f);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test ScrollPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    layoutWrapper->layoutAlgorithm_ = nullptr;
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipLayout = true;
    dirtySwapConfig.skipMeasure = false;
    auto result = scrollPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnScrollCallback001
 * @tc.desc: Test ScrollPattern OnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, OnScrollCallback001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->axis_ = Axis::NONE;
    auto result = scrollPattern->OnScrollCallback(2.0f, SCROLL_FROM_AXIS);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnScrollCallback002
 * @tc.desc: Test ScrollPattern OnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, OnScrollCallback002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->axis_ = Axis::HORIZONTAL;
    scrollPattern->isAnimationStop_ = false;
    auto result = scrollPattern->OnScrollCallback(2.0f, SCROLL_FROM_AXIS);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnScrollCallback003
 * @tc.desc: Test ScrollPattern OnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, OnScrollCallback003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->axis_ = Axis::HORIZONTAL;
    scrollPattern->isAnimationStop_ = false;
    scrollPattern->snapOffsets_ = { 2.0f };
    scrollPattern->enablePagingStatus_ = ScrollPagingStatus::VALID;
    scrollPattern->currentOffset_ = 1.0f;
    scrollPattern->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::HORIZONTAL);
    scrollPattern->scrollableEvent_->scrollable_ =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    auto result = scrollPattern->OnScrollCallback(2.0f, SCROLL_FROM_START);
    EXPECT_EQ(scrollPattern->scrollableEvent_->scrollable_->currentPos_, 1.0f);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ScrollPageCheck001
 * @tc.desc: Test ScrollPattern ScrollPageCheck
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, ScrollPageCheck001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto result = scrollPattern->ScrollPageCheck(2.0f, SCROLL_FROM_START);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: OnAnimateStop001
 * @tc.desc: Test ScrollPattern OnAnimateStop
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, OnAnimateStop001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    scrollPattern->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::HORIZONTAL);
    scrollPattern->scrollableEvent_->scrollable_ =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    scrollPattern->scrollableEvent_->scrollable_->isDragging_ = true;
    scrollPattern->scrollAbort_ = true;
    scrollPattern->frameNode_ = frameNode;
    scrollPattern->OnAnimateStop();
    EXPECT_TRUE(scrollPattern->scrollStop_);
}

/**
 * @tc.name: OnAnimateStop002
 * @tc.desc: Test ScrollPattern OnAnimateStop
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, OnAnimateStop002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    scrollPattern->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::HORIZONTAL);
    scrollPattern->scrollableEvent_->scrollable_ =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    scrollPattern->scrollableEvent_->scrollable_->isDragging_ = true;
    scrollPattern->scrollAbort_ = false;
    scrollPattern->frameNode_ = frameNode;
    scrollPattern->OnAnimateStop();
    EXPECT_FALSE(scrollPattern->scrollStop_);
}

/**
 * @tc.name: OnAnimateStop003
 * @tc.desc: Test ScrollPattern OnAnimateStop
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, OnAnimateStop003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    scrollPattern->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(Axis::HORIZONTAL);
    scrollPattern->scrollableEvent_->scrollable_ =
        AceType::MakeRefPtr<Scrollable>([](double position, int32_t source) { return true; }, Axis::VERTICAL);
    scrollPattern->scrollableEvent_->scrollable_->isDragging_ = false;
    scrollPattern->scrollAbort_ = true;
    scrollPattern->frameNode_ = frameNode;
    scrollPattern->OnAnimateStop();
    EXPECT_TRUE(scrollPattern->scrollStop_);
}

/**
 * @tc.name: ScrollToEdge001
 * @tc.desc: Test ScrollPattern ScrollToEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, ScrollToEdge001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->ScrollToEdge(ScrollEdgeType::SCROLL_NONE, false);
    EXPECT_EQ(scrollPattern->scrollEdgeType_, ScrollEdgeType::SCROLL_NONE);
}

/**
 * @tc.name: ScrollToEdge002
 * @tc.desc: Test ScrollPattern ScrollToEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, ScrollToEdge002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->accessibilityId_ = 2;
    scrollPattern->frameNode_ = frameNode;
    scrollPattern->scrollableDistance_ = 100.0f;
    scrollPattern->currentOffset_ = -50.0f;
    scrollPattern->ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    EXPECT_EQ(scrollPattern->scrollEdgeType_, ScrollEdgeType::SCROLL_TOP);
}

/**
 * @tc.name: CheckScrollToEdge
 * @tc.desc: Test ScrollPattern CheckScrollToEdge
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, CheckScrollToEdge, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->accessibilityId_ = 2;
    scrollPattern->frameNode_ = frameNode;
    scrollPattern->scrollableDistance_ = 20.0f;
    scrollPattern->currentOffset_ = 80.0f;
    scrollPattern->isAnimationStop_ = false;
    scrollPattern->scrollAbort_ = false;
    scrollPattern->finalPosition_ = 0.0f;
    scrollPattern->scrollEdgeType_ = ScrollEdgeType::SCROLL_BOTTOM;
    scrollPattern->CheckScrollToEdge();
    EXPECT_NE(scrollPattern->scrollEdgeType_, ScrollEdgeType::SCROLL_NONE);
    EXPECT_TRUE(scrollPattern->scrollAbort_);
    EXPECT_EQ(scrollPattern->finalPosition_, 20.0f);
}

/**
 * @tc.name: GetOffsetToScroll001
 * @tc.desc: Test ScrollPattern GetOffsetToScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, GetOffsetToScroll001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    scrollPattern->frameNode_ = frameNode;
    auto childFrame = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 3, scrollPattern);
    ASSERT_NE(childFrame, nullptr);
    childFrame->geometryNode_->frame_.rect_.SetRect(20.0f, 40.0f, 100.0f, 200.0f);
    childFrame->parent_ = nullptr;
    auto result = scrollPattern->GetOffsetToScroll(childFrame);
    EXPECT_EQ(result.GetX(), 0.0);
}

/**
 * @tc.name: GetOffsetToScroll002
 * @tc.desc: Test ScrollPattern GetOffsetToScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, GetOffsetToScroll002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    scrollPattern->frameNode_ = frameNode;
    auto childFrame = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 3, scrollPattern);
    ASSERT_NE(childFrame, nullptr);
    RectF rect(10.0f, 20.0f, 100.0f, 200.0f);
    GeometryProperty childGeometryProperty;
    childGeometryProperty.rect_ = rect;
    childFrame->geometryNode_->frame_ = childGeometryProperty;
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    lazyForEachNode->parent_ = frameNode;
    childFrame->parent_ = lazyForEachNode;
    auto result = scrollPattern->GetOffsetToScroll(childFrame);
    EXPECT_EQ(result.GetX(), 0.0);
}

/**
 * @tc.name: GetOffsetToScroll003
 * @tc.desc: Test ScrollPattern GetOffsetToScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, GetOffsetToScroll003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    scrollPattern->frameNode_ = frameNode;
    auto childFrame = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 3, scrollPattern);
    ASSERT_NE(childFrame, nullptr);
    RectF rect(10.0f, 20.0f, 100.0f, 200.0f);
    GeometryProperty childGeometryProperty;
    childGeometryProperty.rect_ = rect;
    childFrame->geometryNode_->frame_ = childGeometryProperty;
    auto node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, scrollPattern);
    node->parent_ = frameNode;
    node->geometryNode_ = nullptr;
    childFrame->parent_ = node;
    auto result = scrollPattern->GetOffsetToScroll(childFrame);
    EXPECT_EQ(result.GetX(), 10.0);
}

/**
 * @tc.name: GetOffsetToScroll004
 * @tc.desc: Test ScrollPattern GetOffsetToScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, GetOffsetToScroll004, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = nullptr;
    scrollPattern->frameNode_ = frameNode;
    auto childFrame = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 3, scrollPattern);
    ASSERT_NE(childFrame, nullptr);
    RectF rect(10.0f, 20.0f, 100.0f, 200.0f);
    GeometryProperty childGeometryProperty;
    childGeometryProperty.rect_ = rect;
    childFrame->geometryNode_->frame_ = childGeometryProperty;
    auto lazyForEachNode = LazyForEachNode::CreateLazyForEachNode(2, nullptr);
    lazyForEachNode->parent_ = frameNode;
    childFrame->parent_ = lazyForEachNode;
    auto result = scrollPattern->GetOffsetToScroll(childFrame);
    EXPECT_EQ(result.GetX(), 0.0);
}

/**
 * @tc.name: ScrollBy
 * @tc.desc: Test ScrollPattern ScrollBy
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, ScrollBy, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->axis_ = Axis::VERTICAL;
    scrollPattern->currentOffset_ = 5.0f;
    std::function<void()> onFinish = [](void) {};
    RefPtr<PipelineBase> context = AceType::MakeRefPtr<PipelineContext>();
    auto animator = Animator::CreateAnimator(nullptr, context, nullptr);
    animator->status_ = Animator::Status::RUNNING;
    scrollPattern->animator_ = animator;
    scrollPattern->ScrollBy(1.0f, 2.0f, false, onFinish);
    EXPECT_EQ(scrollPattern->animator_->status_, Animator::Status::STOPPED);
}

/**
 * @tc.name: ScrollPage
 * @tc.desc: Test ScrollPattern ScrollPage
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, ScrollPage, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->accessibilityId_ = 1;
    scrollPattern->frameNode_ = frameNode;
    scrollPattern->axis_ = Axis::VERTICAL;
    scrollPattern->currentOffset_ = 5.0f;
    scrollPattern->viewPortLength_ = 10.0f;
    RefPtr<PipelineBase> context = AceType::MakeRefPtr<PipelineContext>();
    auto animator = Animator::CreateAnimator(nullptr, context, nullptr);
    animator->status_ = Animator::Status::RUNNING;
    animator->isBothBackwards = true;
    scrollPattern->animator_ = animator;
    scrollPattern->ScrollPage(true, false, AccessibilityScrollType::SCROLL_HALF);
    EXPECT_FALSE(scrollPattern->animator_->isBothBackwards);
}

/**
 * @tc.name: JumpToPosition
 * @tc.desc: Test ScrollPattern JumpToPosition
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, JumpToPosition, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->accessibilityId_ = 1;
    scrollPattern->frameNode_ = frameNode;
    RefPtr<PipelineBase> context = AceType::MakeRefPtr<PipelineContext>();
    auto animator = Animator::CreateAnimator(nullptr, context, nullptr);
    animator->status_ = Animator::Status::RUNNING;
    animator->isBothBackwards = true;
    scrollPattern->animator_ = animator;
    scrollPattern->isAnimationStop_ = false;
    scrollPattern->scrollAbort_ = true;
    scrollPattern->JumpToPosition(4.0f, SCROLL_FROM_START);
    EXPECT_FALSE(scrollPattern->scrollAbort_);
}

/**
 * @tc.name: AdjustOffset001
 * @tc.desc: Test ScrollPattern AdjustOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, AdjustOffset001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->viewPortLength_ = 4.0f;
    scrollPattern->currentOffset_ = 12.0f;
    scrollPattern->scrollableDistance_ = -8.0f;
    scrollPattern->ratio_ = -9.0f;
    float delta = 10.0f;
    scrollPattern->AdjustOffset(delta, SCROLL_FROM_START);
    EXPECT_NE(delta, 10.0);
}

/**
 * @tc.name: ValidateOffset001
 * @tc.desc: Test ScrollPattern ValidateOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, ValidateOffset001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->scrollableDistance_ = 10.0f;
    auto result = scrollPattern->ValidateOffset(SCROLL_FROM_JUMP, 2.0f);
    EXPECT_EQ(result, 2.0f);
}

/**
 * @tc.name: ValidateOffset002
 * @tc.desc: Test ScrollPattern ValidateOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, ValidateOffset002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>();
    scrollPattern->scrollEffect_->edgeEffect_ = EdgeEffect::SPRING;
    scrollPattern->axis_ = Axis::HORIZONTAL;
    scrollPattern->direction_ = FlexDirection::ROW_REVERSE;
    scrollPattern->scrollableDistance_ = 8.0f;
    auto result = scrollPattern->ValidateOffset(SCROLL_FROM_AXIS, 4.0f);
    EXPECT_EQ(result, 4.0f);
}

/**
 * @tc.name: ValidateOffset003
 * @tc.desc: Test ScrollPattern ValidateOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, ValidateOffset003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    scrollPattern->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>();
    scrollPattern->scrollEffect_->edgeEffect_ = EdgeEffect::SPRING;
    scrollPattern->axis_ = Axis::HORIZONTAL;
    scrollPattern->currentOffset_ = 20.0f;
    scrollPattern->direction_ = FlexDirection::ROW_REVERSE;
    scrollPattern->scrollableDistance_ = 8.0f;
    scrollPattern->ValidateOffset(SCROLL_FROM_AXIS);
    EXPECT_EQ(scrollPattern->currentOffset_, 8.0f);
}

/**
 * @tc.name: HandleCrashTop001
 * @tc.desc: Test ScrollPattern HandleCrashTop
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, HandleCrashTop001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    ScrollEdge type = ScrollEdge::RIGHT;
    scrollEventHub->onScrollEdge_ = [&type](ScrollEdge) { type = ScrollEdge::LEFT; };
    frameNode->eventHub_ = scrollEventHub;
    scrollPattern->axis_ = Axis::HORIZONTAL;
    scrollPattern->HandleCrashTop();
    EXPECT_EQ(scrollPattern->eventsFiredInfos_.back().eventType_, ScrollableEventType::ON_SCROLL_EDGE);
    EXPECT_EQ(type, ScrollEdge::LEFT);
}

/**
 * @tc.name: HandleCrashTop002
 * @tc.desc: Test ScrollPattern HandleCrashTop
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, HandleCrashTop002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    ScrollEdge type = ScrollEdge::RIGHT;
    scrollEventHub->onScrollEdge_ = [&type](ScrollEdge) { type = ScrollEdge::TOP; };
    frameNode->eventHub_ = scrollEventHub;
    scrollPattern->axis_ = Axis::FREE;
    scrollPattern->HandleCrashTop();
    EXPECT_EQ(scrollPattern->eventsFiredInfos_.back().eventType_, ScrollableEventType::ON_SCROLL_EDGE);
    EXPECT_EQ(type, ScrollEdge::TOP);
}

/**
 * @tc.name: HandleCrashBottom001
 * @tc.desc: Test ScrollPattern HandleCrashBottom
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, HandleCrashBottom001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    ScrollEdge type = ScrollEdge::LEFT;
    scrollEventHub->onScrollEdge_ = [&type](ScrollEdge) { type = ScrollEdge::RIGHT; };
    frameNode->eventHub_ = scrollEventHub;
    scrollPattern->axis_ = Axis::HORIZONTAL;
    scrollPattern->HandleCrashBottom();
    EXPECT_EQ(scrollPattern->eventsFiredInfos_.back().eventType_, ScrollableEventType::ON_SCROLL_EDGE);
    EXPECT_EQ(type, ScrollEdge::RIGHT);
}

/**
 * @tc.name: HandleCrashBottom002
 * @tc.desc: Test ScrollPattern HandleCrashBottom
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, HandleCrashBottom002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    ScrollEdge type = ScrollEdge::TOP;
    scrollEventHub->onScrollEdge_ = [&type](ScrollEdge) { type = ScrollEdge::BOTTOM; };
    frameNode->eventHub_ = scrollEventHub;
    scrollPattern->axis_ = Axis::FREE;
    scrollPattern->HandleCrashBottom();
    EXPECT_EQ(scrollPattern->eventsFiredInfos_.back().eventType_, ScrollableEventType::ON_SCROLL_EDGE);
    EXPECT_EQ(type, ScrollEdge::BOTTOM);
}

/**
 * @tc.name: FireOnDidScroll001
 * @tc.desc: Test ScrollPattern FireOnDidScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, FireOnDidScroll001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    bool isCallBack = false;
    scrollEventHub->onDidScroll_ = [&isCallBack](Dimension, Dimension, ScrollState) { isCallBack = true; };
    frameNode->eventHub_ = scrollEventHub;
    scrollPattern->axis_ = Axis::HORIZONTAL;
    scrollPattern->scrollStop_ = true;
    scrollPattern->scrollAbort_ = true;
    scrollPattern->FireOnDidScroll(10.0f);
    EXPECT_TRUE(isCallBack);
}

/**
 * @tc.name: FireOnDidScroll002
 * @tc.desc: Test ScrollPattern FireOnDidScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, FireOnDidScroll002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    bool isCallBack = true;
    scrollEventHub->onJSFrameNodeDidScroll_ = [&isCallBack](Dimension, Dimension, ScrollState) { isCallBack = false; };
    frameNode->eventHub_ = scrollEventHub;
    scrollPattern->axis_ = Axis::FREE;
    scrollPattern->scrollStop_ = false;
    scrollPattern->scrollAbort_ = false;
    scrollPattern->FireOnDidScroll(8.0f);
    EXPECT_FALSE(isCallBack);
}

/**
 * @tc.name: FireOnDidScroll003
 * @tc.desc: Test ScrollPattern FireOnDidScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, FireOnDidScroll003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    bool isCallBack = false;
    scrollEventHub->onDidScroll_ = [&isCallBack](Dimension, Dimension, ScrollState) { isCallBack = true; };
    frameNode->eventHub_ = scrollEventHub;
    scrollPattern->axis_ = Axis::HORIZONTAL;
    scrollPattern->scrollSource_ = SCROLL_FROM_UPDATE;
    scrollPattern->scrollStop_ = true;
    scrollPattern->scrollAbort_ = false;
    scrollPattern->FireOnDidScroll(0.0f);
    EXPECT_TRUE(isCallBack);
}

/**
 * @tc.name: FireOnDidScroll004
 * @tc.desc: Test ScrollPattern FireOnDidScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, FireOnDidScroll004, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    bool isCallBack = true;
    scrollEventHub->onJSFrameNodeDidScroll_ = [&isCallBack](Dimension, Dimension, ScrollState) { isCallBack = false; };
    frameNode->eventHub_ = scrollEventHub;
    scrollPattern->axis_ = Axis::FREE;
    scrollPattern->scrollSource_ = SCROLL_FROM_UPDATE;
    scrollPattern->scrollStop_ = true;
    scrollPattern->scrollAbort_ = false;
    scrollPattern->FireOnDidScroll(0.0f);
    EXPECT_FALSE(isCallBack);
}

/**
 * @tc.name: FireOnDidScroll005
 * @tc.desc: Test ScrollPattern FireOnDidScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, FireOnDidScroll005, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    bool isCallBack = false;
    scrollEventHub->onDidScroll_ = [&isCallBack](Dimension, Dimension, ScrollState) { isCallBack = true; };
    frameNode->eventHub_ = scrollEventHub;
    scrollPattern->axis_ = Axis::HORIZONTAL;
    scrollPattern->scrollSource_ = SCROLL_FROM_NONE;
    scrollPattern->scrollStop_ = true;
    scrollPattern->scrollAbort_ = false;
    scrollPattern->FireOnDidScroll(6.0f);
    EXPECT_TRUE(isCallBack);
}

/**
 * @tc.name: HandleScrollPosition001
 * @tc.desc: Test ScrollPattern HandleScrollPosition
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, HandleScrollPosition001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    bool isScrollEventHub = false;
    scrollEventHub->onScroll_ = [&isScrollEventHub](Dimension, Dimension) { isScrollEventHub = true; };
    frameNode->eventHub_ = scrollEventHub;
    scrollPattern->axis_ = Axis::HORIZONTAL;
    scrollPattern->HandleScrollPosition(10.0f);
    EXPECT_TRUE(isScrollEventHub);
}

/**
 * @tc.name: HandleScrollPosition002
 * @tc.desc: Test ScrollPattern HandleScrollPosition
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, HandleScrollPosition002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    bool isScrollEventHub = true;
    scrollEventHub->onScroll_ = [&isScrollEventHub](Dimension, Dimension) { isScrollEventHub = false; };
    frameNode->eventHub_ = scrollEventHub;
    scrollPattern->axis_ = Axis::FREE;
    scrollPattern->HandleScrollPosition(8.0f);
    EXPECT_FALSE(isScrollEventHub);
}

/**
 * @tc.name: FireTwoDimensionOnWillScroll001
 * @tc.desc: Test ScrollPattern FireTwoDimensionOnWillScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, FireTwoDimensionOnWillScroll001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    bool isCallBack = false;
    scrollEventHub->onWillScroll_ = [&isCallBack](Dimension, Dimension, ScrollState, ScrollSource) {
        isCallBack = true;
        Dimension scrollX(2.0, DimensionUnit::VP);
        Dimension scrollY(4.0, DimensionUnit::PX);
        TwoDimensionScrollResult scrollRes { .xOffset = scrollX, .yOffset = scrollY };
        return scrollRes;
    };
    frameNode->eventHub_ = scrollEventHub;
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->dipScale_ = 4.0;
    frameNode->context_ = AceType::RawPtr(context);
    scrollPattern->axis_ = Axis::HORIZONTAL;
    auto result = scrollPattern->FireTwoDimensionOnWillScroll(10.0f);
    frameNode->context_ = nullptr;
    EXPECT_TRUE(isCallBack);
    EXPECT_EQ(result, 8.0);
}

/**
 * @tc.name: FireTwoDimensionOnWillScroll002
 * @tc.desc: Test ScrollPattern FireTwoDimensionOnWillScroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, FireTwoDimensionOnWillScroll002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto scrollEventHub = AceType::MakeRefPtr<ScrollEventHub>();
    bool isCallBack = true;
    scrollEventHub->onJSFrameNodeWillScroll_ = [&isCallBack](Dimension, Dimension, ScrollState, ScrollSource) {
        isCallBack = false;
        Dimension scrollX(5.0, DimensionUnit::VP);
        Dimension scrollY(10.0, DimensionUnit::PX);
        TwoDimensionScrollResult scrollRes { .xOffset = scrollX, .yOffset = scrollY };
        return scrollRes;
    };
    frameNode->eventHub_ = scrollEventHub;
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->dipScale_ = 2.0;
    frameNode->context_ = AceType::RawPtr(context);
    scrollPattern->axis_ = Axis::FREE;
    auto result = scrollPattern->FireTwoDimensionOnWillScroll(10.0f);
    frameNode->context_ = nullptr;
    EXPECT_FALSE(isCallBack);
    EXPECT_EQ(result, 10.0);
}

/**
 * @tc.name: FireOnReachStart001
 * @tc.desc: Test ScrollPattern FireOnReachStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, FireOnReachStart001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->accessibilityId_ = 1;
    bool isCallBack = false;
    OnReachEvent onReachStart = [&isCallBack] { isCallBack = true; };
    OnReachEvent onJSFrameNodeReachStart = nullptr;
    scrollPattern->currentOffset_ = 2.0f;
    scrollPattern->FireOnReachStart(onReachStart, onJSFrameNodeReachStart);
    EXPECT_EQ(scrollPattern->eventsFiredInfos_.back().eventType_, ScrollableEventType::ON_REACH_START);
    EXPECT_TRUE(isCallBack);
}

/**
 * @tc.name: FireOnReachStart002
 * @tc.desc: Test ScrollPattern FireOnReachStart
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, FireOnReachStart002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->accessibilityId_ = 2;
    bool isCallBack = true;
    OnReachEvent onReachStart = nullptr;
    OnReachEvent onJSFrameNodeReachStart = [&isCallBack] { isCallBack = false; };
    scrollPattern->currentOffset_ = 2.0f;
    scrollPattern->FireOnReachStart(onReachStart, onJSFrameNodeReachStart);
    EXPECT_EQ(scrollPattern->eventsFiredInfos_.back().eventType_, ScrollableEventType::ON_REACH_START);
    EXPECT_FALSE(isCallBack);
}

/**
 * @tc.name: FireOnReachEnd001
 * @tc.desc: Test ScrollPattern FireOnReachEnd
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, FireOnReachEnd001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->accessibilityId_ = 4;
    bool isCallBack = false;
    OnReachEvent onReachEnd = [&isCallBack] { isCallBack = true; };
    OnReachEvent onJSFrameNodeReachEnd = nullptr;
    scrollPattern->currentOffset_ = 1.0f;
    scrollPattern->prevOffset_ = 5.0f;
    scrollPattern->scrollableDistance_ = -3.0f;
    scrollPattern->FireOnReachEnd(onReachEnd, onJSFrameNodeReachEnd);
    EXPECT_EQ(scrollPattern->eventsFiredInfos_.back().eventType_, ScrollableEventType::ON_REACH_END);
    EXPECT_TRUE(isCallBack);
}

/**
 * @tc.name: FireOnReachEnd002
 * @tc.desc: Test ScrollPattern FireOnReachEnd
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, FireOnReachEnd002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->accessibilityId_ = 3;
    bool isCallBack = true;
    OnReachEvent onReachEnd = nullptr;
    OnReachEvent onJSFrameNodeReachEnd = [&isCallBack] { isCallBack = false; };
    scrollPattern->currentOffset_ = 1.0f;
    scrollPattern->prevOffset_ = 5.0f;
    scrollPattern->scrollableDistance_ = -3.0f;
    scrollPattern->FireOnReachEnd(onReachEnd, onJSFrameNodeReachEnd);
    EXPECT_EQ(scrollPattern->eventsFiredInfos_.back().eventType_, ScrollableEventType::ON_REACH_END);
    EXPECT_FALSE(isCallBack);
}

/**
 * @tc.name: UpdateCurrentOffset001
 * @tc.desc: Test ScrollPattern UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternTwoTestNg, UpdateCurrentOffset001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    scrollPattern->scrollableDistance_ = 8.0f;
    scrollPattern->currentOffset_ = 1.0f;
    scrollPattern->scrollEffect_ = nullptr;
    scrollPattern->viewSize_ = SizeF(100.0f, 200.0f);
    auto result = scrollPattern->UpdateCurrentOffset(2.0f, SCROLL_FROM_NONE);
    EXPECT_FALSE(result);
}
} // namespace OHOS::Ace::NG