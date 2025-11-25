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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_scroll_controller.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorScrollControllerTest : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorScrollControllerTest::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->InitScrollablePattern();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorScrollControllerTest::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorScrollControllerTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: IsReachTop001
 * @tc.desc: test IsReachTop
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, IsReachTop001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->textRect_ = RectF(0, 0, 100, 100);

    scrollController->contentRect_ = RectF(0, 0, 100, 100);
    EXPECT_TRUE(scrollController->IsReachTop());

    scrollController->contentRect_ = RectF(50, 50, 100, 100);
    EXPECT_FALSE(scrollController->IsReachTop());
}

/**
 * @tc.name: IsReachBottom001
 * @tc.desc: test IsReachBottom
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, IsReachBottom001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->textRect_ = RectF(0, 0, 100, 100);

    scrollController->contentRect_ = RectF(0, 0, 100, 100);
    EXPECT_TRUE(scrollController->IsReachBottom());

    scrollController->contentRect_ = RectF(50, 50, 100, 100);
    EXPECT_FALSE(scrollController->IsReachBottom());
}

/**
 * @tc.name: IsReachLeft001
 * @tc.desc: test IsReachLeft
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, IsReachLeft001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->textRect_ = RectF(0, 0, 100, 100);

    scrollController->contentRect_ = RectF(0, 0, 100, 100);
    EXPECT_TRUE(scrollController->IsReachLeft());

    scrollController->contentRect_ = RectF(50, 50, 100, 100);
    EXPECT_FALSE(scrollController->IsReachLeft());
}

/**
 * @tc.name: IsReachRight001
 * @tc.desc: test IsReachRight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, IsReachRight001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->textRect_ = RectF(0, 0, 100, 100);

    scrollController->contentRect_ = RectF(0, 0, 100, 100);
    EXPECT_TRUE(scrollController->IsReachRight());

    scrollController->contentRect_ = RectF(50, 50, 100, 100);
    EXPECT_FALSE(scrollController->IsReachRight());
}

/**
 * @tc.name: IsReachLowerBoundary001
 * @tc.desc: test IsReachBoundary
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, IsReachLowerBoundary001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->textRect_ = RectF(0, 0, 100, 100);
    scrollController->contentRect_ = RectF(0, 0, 100, 100);

    scrollController->isSingleLineMode_ = true;
    EXPECT_TRUE(scrollController->IsReachLowerBoundary());
    EXPECT_TRUE(scrollController->IsReachBoundary());
    scrollController->isSingleLineMode_ = false;
    EXPECT_TRUE(scrollController->IsReachLowerBoundary());
    EXPECT_TRUE(scrollController->IsReachBoundary());

    scrollController->contentRect_ = RectF(50, 50, 100, 100);
    scrollController->isSingleLineMode_ = true;
    EXPECT_FALSE(scrollController->IsReachLowerBoundary());
    EXPECT_FALSE(scrollController->IsReachBoundary());
    scrollController->isSingleLineMode_ = false;
    EXPECT_FALSE(scrollController->IsReachLowerBoundary());
    EXPECT_FALSE(scrollController->IsReachBoundary());
}

/**
 * @tc.name: IsReachUpperBoundary001
 * @tc.desc: test IsReachUpperBoundary
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, IsReachUpperBoundary001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->textRect_ = RectF(0, 0, 100, 100);
    scrollController->contentRect_ = RectF(0, 0, 100, 100);

    scrollController->isSingleLineMode_ = true;
    EXPECT_TRUE(scrollController->IsReachUpperBoundary());
    EXPECT_TRUE(scrollController->IsReachBoundary());
    scrollController->isSingleLineMode_ = false;
    EXPECT_TRUE(scrollController->IsReachUpperBoundary());
    EXPECT_TRUE(scrollController->IsReachBoundary());

    scrollController->contentRect_ = RectF(50, 50, 100, 100);
    scrollController->isSingleLineMode_ = true;
    EXPECT_FALSE(scrollController->IsReachUpperBoundary());
    EXPECT_FALSE(scrollController->IsReachBoundary());
    scrollController->isSingleLineMode_ = false;
    EXPECT_FALSE(scrollController->IsReachUpperBoundary());
    EXPECT_FALSE(scrollController->IsReachBoundary());
}

/**
 * @tc.name: IsReachAvoidBoundary001
 * @tc.desc: test IsReachAvoidBoundary
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, IsReachAvoidBoundary001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->textRect_ = RectF(0, 0, 100, 100);
    scrollController->contentRect_ = RectF(0, 0, 100, 100);

    scrollController->isSingleLineMode_ = true;
    EXPECT_TRUE(scrollController->IsReachAvoidBoundary(1.0f));
    scrollController->isSingleLineMode_ = false;
    EXPECT_TRUE(scrollController->IsReachAvoidBoundary(1.0f));
}

/**
 * @tc.name: CalcDragSpeed001
 * @tc.desc: test CalcDragSpeed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, CalcDragSpeed001, TestSize.Level0)
{
    auto speed = RichEditorScrollController::CalcDragSpeed(0.0f, 5.0f, 1.0f);
    EXPECT_NE(speed, 0.0f);
}

/**
 * @tc.name: CalcDragSpeed002
 * @tc.desc: test CalcDragSpeed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, CalcDragSpeed002, TestSize.Level2)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    float speed = 0.0f;
    float hotAreaStart = 1.1f;
    float hotAreaEnd = 101.1f;
    float point = 50.1f;
    float result = 17.472723f;
    speed = RichEditorScrollController::CalcDragSpeed(hotAreaStart, hotAreaEnd, point);
    EXPECT_EQ(result, speed);
}

/**
 * @tc.name: ScheduleAutoScroll001
 * @tc.desc: test ScheduleAutoScroll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, ScheduleAutoScroll001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->textRect_ = RectF(0, 0, 100, 100);
    scrollController->contentRect_ = RectF(50, 50, 100, 100);

    AutoScrollParam param;
    param.offset = 1.0f;
    param.isFirstRun_ = true;
    scrollController->ScheduleAutoScroll(param);
    EXPECT_TRUE(param.isFirstRun_);
}

/**
 * @tc.name: ScheduleAutoScroll002
 * @tc.desc: test ScheduleAutoScroll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, ScheduleAutoScroll002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->textRect_ = RectF(0, 0, 100, 100);
    scrollController->contentRect_ = RectF(50, 50, 100, 100);

    AutoScrollParam param;
    param.offset = 1.0f;
    param.isFirstRun_ = true;
    scrollController->ScheduleAutoScroll(param);
    EXPECT_TRUE(param.isFirstRun_);
}

/**
 * @tc.name: ScheduleAutoScroll003
 * @tc.desc: test ScheduleAutoScroll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, ScheduleAutoScroll003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    AutoScrollParam param;
    param.isFirstRun_ = true;
    param.offset = 0.0f;
    richEditorPattern->contentRect_.SetRect(0, 1, 1, 1);
    richEditorPattern->richTextRect_.SetRect(0, 2, 1, 1);
    auto& scrollController = richEditorPattern->scrollController_;

    scrollController->isAutoScrollRunning_ = true;
    scrollController->ScheduleAutoScroll(param);
    EXPECT_TRUE(param.isFirstRun_);
}

/**
 * @tc.name: StopAutoScroll001
 * @tc.desc: test StopAutoScroll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, StopAutoScroll001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->isAutoScrollRunning_ = true;
    scrollController->StopAutoScroll();
    EXPECT_FALSE(scrollController->isAutoScrollRunning_);
}

/**
 * @tc.name: GetAutoScrollOffsetDiff001
 * @tc.desc: test GetAutoScrollOffsetDiff
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, GetAutoScrollOffsetDiff001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->prevAutoScrollOffset_ = OffsetF(1.0f, 0.0f);
    scrollController->isSingleLineMode_ = true;
    EXPECT_NE(scrollController->GetAutoScrollOffsetDiff(OffsetF(0.0f, 0.0f)), 0.0f);

    scrollController->prevAutoScrollOffset_ = OffsetF(0.0f, 1.0f);
    scrollController->isSingleLineMode_ = false;
    EXPECT_NE(scrollController->GetAutoScrollOffsetDiff(OffsetF(0.0f, 0.0f)), 0.0f);
}

/**
 * @tc.name: GetHotAreaOverflow001
 * @tc.desc: test GetHotAreaOverflow
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, GetHotAreaOverflow001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->frameRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    scrollController->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);

    scrollController->isSingleLineMode_ = true;
    EXPECT_TRUE(scrollController->GetHotAreaOverflow(true, 100.0f));
    EXPECT_TRUE(scrollController->GetHotAreaOverflow(false, 100.0f));

    scrollController->isSingleLineMode_ = false;
    EXPECT_TRUE(scrollController->GetHotAreaOverflow(true, 100.0f));
    EXPECT_TRUE(scrollController->GetHotAreaOverflow(false, 100.0f));
}

/**
 * @tc.name: AutoScrollByEdgeDetection001
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, AutoScrollByEdgeDetection001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->richTextRect_ = RectF(0, -10, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);
    auto& scrollController = richEditorPattern->scrollController_;

    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::HANDLE };
    Dimension AUTO_SCROLL_EDGE_DISTANCE = 15.0_vp;
    scrollController->prevAutoScrollOffset_ = OffsetF(0, 0);
    auto edgeDistance = AUTO_SCROLL_EDGE_DISTANCE.ConvertToPx();

    param.handleRect = RectF(50, richEditorPattern->contentRect_.GetY() + edgeDistance + 1, 20, 20);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(scrollController->autoScrollTask_) << "handle move up but not reach top edge";
    richEditorPattern->StopAutoScroll();

    scrollController->prevAutoScrollOffset_ = OffsetF(0, 0);
    param.handleRect = RectF(50, richEditorPattern->contentRect_.GetY() + edgeDistance - 1, 20, 20);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(scrollController->IsReachTop()) << "handle reach top edge";
    richEditorPattern->StopAutoScroll();

    auto handleHeight = 20;
    scrollController->prevAutoScrollOffset_ = OffsetF(0, 0);
    param.handleRect =
        RectF(50, richEditorPattern->contentRect_.Bottom() - edgeDistance - 1 - handleHeight, 20, handleHeight);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(scrollController->autoScrollTask_) << "handle move down but not reach bottom edge";
    richEditorPattern->StopAutoScroll();

    scrollController->prevAutoScrollOffset_ = OffsetF(0, 0);
    param.handleRect =
        RectF(50, richEditorPattern->contentRect_.Bottom() - edgeDistance - handleHeight + 1, 20, handleHeight);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(scrollController->IsReachBottom()) << "handle reach bottom edge";
    richEditorPattern->StopAutoScroll();

    pipeline->taskExecutor_.Reset();
}

/**
 * @tc.name: AutoScrollByEdgeDetection002
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, AutoScrollByEdgeDetection002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->richTextRect_ = RectF(0, -10, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);
    auto& scrollController = richEditorPattern->scrollController_;

    scrollController->prevAutoScrollOffset_ = OffsetF(0, 0);
    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::MOUSE };
    Dimension AUTO_SCROLL_EDGE_DISTANCE = 15.0_vp;
    auto edgeDistance = AUTO_SCROLL_EDGE_DISTANCE.ConvertToPx();

    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->contentRect_.GetY() + edgeDistance + 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(scrollController->autoScrollTask_) << "mouse move up but not reach top edge";
    richEditorPattern->StopAutoScroll();

    scrollController->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->contentRect_.GetY() + edgeDistance - 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(scrollController->IsReachTop()) << "mouse reach top edge";
    richEditorPattern->StopAutoScroll();

    scrollController->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->contentRect_.Bottom() - edgeDistance - 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(scrollController->autoScrollTask_) << "mouse move down but not reach bottom edge";
    richEditorPattern->StopAutoScroll();

    scrollController->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->contentRect_.Bottom() - edgeDistance + 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(scrollController->IsReachBottom()) << "mouse reach bottom edge";
    richEditorPattern->StopAutoScroll();

    pipeline->taskExecutor_.Reset();
}

/**
 * @tc.name: AutoScrollByEdgeDetection003
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, AutoScrollByEdgeDetection003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->richTextRect_ = RectF(0, -10, 100, 540);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 500);
    richEditorPattern->frameRect_ = RectF(0, 0, 100, 500);
    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->isSingleLineMode_ = false;

    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::DRAG };
    Dimension AUTO_SCROLL_DRAG_EDGE_DISTANCE = 58.0_vp;
    auto dragDistance = AUTO_SCROLL_DRAG_EDGE_DISTANCE.ConvertToPx();

    scrollController->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, OffsetF(50, dragDistance + 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(scrollController->autoScrollTask_) << "drag move up but not reach top edge";
    richEditorPattern->StopAutoScroll();

    scrollController->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, OffsetF(50, dragDistance - 10), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(scrollController->IsReachTop()) << "drag reach top edge";
    auto speed = scrollController->CalcDragSpeed(dragDistance, 0, dragDistance - 10);
    EXPECT_EQ(scrollController->currentScrollParam_.offset, speed) << "darg speed move up";
    richEditorPattern->StopAutoScroll();

    scrollController->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->frameRect_.Bottom() - dragDistance - 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(scrollController->autoScrollTask_) << "drag move down but not reach bottom edge";
    richEditorPattern->StopAutoScroll();

    scrollController->prevAutoScrollOffset_ = OffsetF(0, 0);
    auto pointY = richEditorPattern->frameRect_.Bottom() - dragDistance + 10;
    richEditorPattern->AutoScrollByEdgeDetection(param, OffsetF(50, pointY), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(scrollController->IsReachBottom()) << "drag reach bottom edge";
    speed = scrollController->CalcDragSpeed(
        richEditorPattern->frameRect_.Bottom() - dragDistance, richEditorPattern->frameRect_.Bottom(), pointY);
    EXPECT_EQ(scrollController->currentScrollParam_.offset, -speed) << "darg speed move down"
        << ", hotAreaStart=" << richEditorPattern->frameRect_.Bottom() - dragDistance
        << ", hotAreaEnd=" << richEditorPattern->frameRect_.Bottom()
        << ", point=" << pointY;
    // hotAreaStart=442, hotAreaEnd=500, point=452
    richEditorPattern->StopAutoScroll();

    pipeline->taskExecutor_.Reset();
}

/**
 * @tc.name: AutoScrollByEdgeDetection004
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, AutoScrollByEdgeDetection004, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);
    auto& scrollController = richEditorPattern->scrollController_;

    Dimension AUTO_SCROLL_EDGE_DISTANCE = 15.0_vp;
    auto edgeDistance = AUTO_SCROLL_EDGE_DISTANCE.ConvertToPx();

    scrollController->prevAutoScrollOffset_ = OffsetF(50, 50);
    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::HANDLE, .handleRect = RectF(50, 50, 20, 20) };
    richEditorPattern->AutoScrollByEdgeDetection(param, OffsetF(50, 50), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(scrollController->autoScrollTask_) << "the touch point is the same as the last time";
    richEditorPattern->StopAutoScroll();

    scrollController->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, edgeDistance - 1);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(scrollController->autoScrollTask_) << "content height is too small.";
    richEditorPattern->StopAutoScroll();

    pipeline->taskExecutor_.Reset();
}

/**
 * @tc.name: GetOffset2d001
 * @tc.desc: test GetOffset2d
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, GetOffset2d001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->frameRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    scrollController->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);

    scrollController->isSingleLineMode_ = true;
    OffsetF offsetX{ 1.0f, 0.0f };
    EXPECT_EQ(scrollController->GetOffset2d(1.0f), offsetX);

    scrollController->isSingleLineMode_ = false;
    OffsetF offsetY{ 0.0f, 1.0f };
    EXPECT_EQ(scrollController->GetOffset2d(1.0f), offsetY);
}

/**
 * @tc.name: MoveHandleOnScroll001
 * @tc.desc: test GetOffset2d
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, MoveHandleOnScroll001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& scrollController = richEditorPattern->scrollController_;
    auto& textSelector = scrollController->textSelector_;
    OffsetF offset{ 0.0f, 0.0f };
    textSelector.selectionBaseOffset = offset;
    textSelector.selectionDestinationOffset = offset;

    AddSpan(INIT_VALUE_1);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    richEditorPattern->textSelector_.Update(0, 2);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    ASSERT_TRUE(richEditorPattern->SelectOverlayIsOn());

    scrollController->MoveHandleOnScroll(1.0f);
    EXPECT_NE(textSelector.selectionBaseOffset, offset);
    EXPECT_NE(textSelector.selectionDestinationOffset, offset);
}

/**
 * @tc.name: MoveHandleOnScroll002
 * @tc.desc: test MoveHandleOnScroll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, MoveHandleOnScroll002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& scrollController = richEditorPattern->scrollController_;
    auto& textSelector = scrollController->textSelector_;
    OffsetF offset{ 0.0f, 0.0f };
    textSelector.selectionBaseOffset = offset;
    textSelector.selectionDestinationOffset = offset;

    AddSpan(INIT_VALUE_1);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    richEditorPattern->textSelector_.Update(0, 2);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    ASSERT_TRUE(richEditorPattern->SelectOverlayIsOn());

    scrollController->MoveHandleOnScroll(1.0f);
    EXPECT_NE(textSelector.selectionBaseOffset, offset);
    EXPECT_NE(textSelector.selectionDestinationOffset, offset);

    textSelector.selectionBaseOffset = offset;
    textSelector.selectionDestinationOffset = offset;
    scrollController->MoveHandleOnScroll(1.0f, true);
    EXPECT_NE(textSelector.selectionBaseOffset, offset);
    EXPECT_EQ(textSelector.selectionDestinationOffset, offset);

    textSelector.selectionBaseOffset = offset;
    textSelector.selectionDestinationOffset = offset;
    scrollController->MoveHandleOnScroll(1.0f, false);
    EXPECT_EQ(textSelector.selectionBaseOffset, offset);
    EXPECT_NE(textSelector.selectionDestinationOffset, offset);
}

/**
 * @tc.name: MoveHandleOnScroll003
 * @tc.desc: test MoveHandleOnScroll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, MoveHandleOnScroll003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& scrollController = richEditorPattern->scrollController_;
    auto& textSelector = scrollController->textSelector_;
    OffsetF offset{ 0.0f, 0.0f };
    textSelector.selectionBaseOffset = offset;
    textSelector.selectionDestinationOffset = offset;

    AddSpan(INIT_VALUE_1);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    richEditorPattern->textSelector_.Update(0, 2);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    ASSERT_TRUE(richEditorPattern->SelectOverlayIsOn());

    scrollController->MoveHandleOnScroll(1.0f);
    EXPECT_NE(textSelector.selectionBaseOffset, offset);
    EXPECT_NE(textSelector.selectionDestinationOffset, offset);
}

/**
 * @tc.name: MoveHandleOnScroll004
 * @tc.desc: test MoveHandleOnScroll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, MoveHandleOnScroll004, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->textRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    scrollController->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    scrollController->isSingleLineMode_ = true;
    EXPECT_EQ(scrollController->MoveTextRect(10.0f), 0.0f);
    EXPECT_EQ(scrollController->MoveTextRect(-10.0f), 0.0f);

    scrollController->isSingleLineMode_ = false;
    EXPECT_EQ(scrollController->MoveTextRect(10.0f), 0.0f);
    EXPECT_EQ(scrollController->MoveTextRect(-10.0f), 0.0f);
}

/**
 * @tc.name: CalCaretToContentRectDistanceVertical001
 * @tc.desc: test CalCaretToContentRectDistanceVertical
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, CalCaretToContentRectDistanceVertical001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->textRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    scrollController->contentRect_ = RectF(0.0f, 0.0f, 10.0f, 10.0f);

    OffsetF caretOffset(-10.0f, -20.0f);
    float caretHeight = 20.0f;
    float keyboardOffset = 0.0f;

    float result = scrollController->CalCaretToContentRectDistanceVertical(caretOffset, caretHeight, keyboardOffset);
    EXPECT_EQ(result, 10.0f);  // contentRect_.GetY() - caretOffset.GetY() + caretHeight
}

/**
 * @tc.name: CalCaretToContentRectDistanceVertical002
 * @tc.desc: test CalCaretToContentRectDistanceVertical
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, CalCaretToContentRectDistanceVertical002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->textRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    scrollController->contentRect_ = RectF(0.0f, 0.0f, 10.0f, 10.0f);

    OffsetF caretOffset(10.0f, 120.0f); // 光标在内容矩形下方
    float caretHeight = 20.0f;
    float keyboardOffset = 0.0f;

    float result = scrollController->CalCaretToContentRectDistanceVertical(caretOffset, caretHeight, keyboardOffset);
    EXPECT_EQ(result, -130.0f); // contentRect_.Bottom() - keyboardOffset - caretOffset.GetY() - caretHeight
}

/**
 * @tc.name: CalCaretToContentRectDistanceVertical003
 * @tc.desc: test CalCaretToContentRectDistanceVertical
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, CalCaretToContentRectDistanceVertical003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->textRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    scrollController->contentRect_ = RectF(0.0f, 0.0f, 10.0f, 10.0f);

    OffsetF caretOffset(10.0f, 50.0f);
    float caretHeight = 20.0f;
    float keyboardOffset = 0.0f;

    float result = scrollController->CalCaretToContentRectDistanceVertical(caretOffset, caretHeight, keyboardOffset);
    EXPECT_EQ(result, -60.0f);
}

/**
 * @tc.name: CalCaretToContentRectDistanceVertical004
 * @tc.desc: test CalCaretToContentRectDistanceVertical
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, CalCaretToContentRectDistanceVertical004, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->textRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    scrollController->contentRect_ = RectF(0.0f, 0.0f, 10.0f, 10.0f);

    OffsetF caretOffset(10.0f, 0.0f);
    float caretHeight = 150.0f;
    float keyboardOffset = 0.0f;

    float result = scrollController->CalCaretToContentRectDistanceVertical(caretOffset, caretHeight, keyboardOffset);
    EXPECT_EQ(result, -140.0f);
}

/**
 * @tc.name: CalCaretToContentRectDistanceVertical005
 * @tc.desc: test CalCaretToContentRectDistanceVertical
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, CalCaretToContentRectDistanceVertical005, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& scrollController = richEditorPattern->scrollController_;
    scrollController->textRect_ = RectF(0.0f, 0.0f, 100.0f, 100.0f);
    scrollController->contentRect_ = RectF(0.0f, 0.0f, 10.0f, 10.0f);

    OffsetF caretOffset(10.0f, 120.0f);
    float caretHeight = 20.0f;
    float keyboardOffset = 30.0f;

    float result = scrollController->CalCaretToContentRectDistanceVertical(caretOffset, caretHeight, keyboardOffset);
    EXPECT_EQ(result, -160.0f);  // contentRect_.Bottom() - keyboardOffset - caretOffset.GetY() - caretHeight
}

/**
 * @tc.name: NeedScroll001
 * @tc.desc: test NeedScroll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, NeedScroll001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& scrollController = richEditorPattern->scrollController_;
    auto& textRect_ = scrollController->textRect_;
    auto& contentRect_ = scrollController->contentRect_;

    scrollController->isSingleLineMode_ = true;
    textRect_.SetSize(SizeF(150.0f, 100.0f));
    contentRect_.SetSize(SizeF(100.0f, 100.0f));
    EXPECT_TRUE(scrollController->NeedScroll());

    textRect_.SetSize(SizeF(50.0f, 100.0f));
    contentRect_.SetSize(SizeF(100.0f, 100.0f));
    EXPECT_FALSE(scrollController->NeedScroll());
}

/**
 * @tc.name: NeedScroll002
 * @tc.desc: test NeedScroll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollControllerTest, NeedScroll002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& scrollController = richEditorPattern->scrollController_;
    auto& textRect_ = scrollController->textRect_;
    auto& contentRect_ = scrollController->contentRect_;

    scrollController->isSingleLineMode_ = false;
    textRect_.SetSize(SizeF(100.0f, 150.0f)); 
    contentRect_.SetSize(SizeF(100.0f, 100.0f));
    EXPECT_TRUE(scrollController->NeedScroll());

    textRect_.SetSize(SizeF(100.0f, 50.0f));
    contentRect_.SetSize(SizeF(100.0f, 100.0f));
    EXPECT_FALSE(scrollController->NeedScroll());
}

}