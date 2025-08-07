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
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const auto BUILDER_NODE_1 = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG,
    ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
} // namespace
class RichEditorScrollTestOneNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
    RefPtr<RichEditorPattern> GetRichEditorPattern();
};

RefPtr<RichEditorPattern> RichEditorScrollTestOneNg::GetRichEditorPattern()
{
    CHECK_NULL_RETURN(richEditorNode_, nullptr);
    return richEditorNode_->GetPattern<RichEditorPattern>();
}

void RichEditorScrollTestOneNg::SetUp()
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

void RichEditorScrollTestOneNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorScrollTestOneNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: OnScrollCallback001
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, OnScrollCallback001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    int32_t SCROLL_FROM_START = 10;
    EXPECT_TRUE(richEditorPattern->OnScrollCallback(0, SCROLL_FROM_START));

    int32_t SCROLL_FROM_UPDATE = 1;
    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);
    EXPECT_FALSE(richEditorPattern->OnScrollCallback(10, SCROLL_FROM_UPDATE)) << "Reach Top Boundary";

    richEditorPattern->richTextRect_ = RectF(0, -40, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);
    EXPECT_FALSE(richEditorPattern->OnScrollCallback(-10, SCROLL_FROM_UPDATE)) << "Reach Bottom Boundary";

    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);
    EXPECT_TRUE(richEditorPattern->OnScrollCallback(-10, SCROLL_FROM_UPDATE)) << "Scroll Up 10";
    EXPECT_EQ(richEditorPattern->scrollOffset_, -10);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetY(), -10);

    EXPECT_TRUE(richEditorPattern->OnScrollCallback(-50, SCROLL_FROM_UPDATE)) << "Scroll Up 50";
    EXPECT_EQ(richEditorPattern->scrollOffset_, -40);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetY(), -40);

    EXPECT_TRUE(richEditorPattern->OnScrollCallback(10, SCROLL_FROM_UPDATE)) << "Scroll Down 10";
    EXPECT_EQ(richEditorPattern->scrollOffset_, -30);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetY(), -30);

    EXPECT_TRUE(richEditorPattern->OnScrollCallback(50, SCROLL_FROM_UPDATE)) << "Scroll Down 50";
    EXPECT_EQ(richEditorPattern->scrollOffset_, 0);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetY(), 0);
}

/**
 * @tc.name: OnScrollCallback002
 * @tc.desc: test OnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, OnScrollCallback002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.Update(0, 1);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());

    RectF rect(0, 0, 5, 5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->selectOverlay_->OnHandleMoveDone(rect, true);

    EXPECT_TRUE(richEditorPattern->selectOverlay_->SelectOverlayIsOn());
    bool ret = false;
    int32_t SCROLL_FROM_START = 10;
    ret = richEditorPattern->OnScrollCallback(10, SCROLL_FROM_START);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: AutoScrollByEdgeDetection001
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, AutoScrollByEdgeDetection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->richTextRect_ = RectF(0, -10, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);

    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::HANDLE };
    Dimension AUTO_SCROLL_EDGE_DISTANCE = 15.0_vp;
    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    auto edgeDistance = AUTO_SCROLL_EDGE_DISTANCE.ConvertToPx();

    param.handleRect = RectF(50, richEditorPattern->contentRect_.GetY() + edgeDistance + 1, 20, 20);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "handle move up but not reach top edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    param.handleRect = RectF(50, richEditorPattern->contentRect_.GetY() + edgeDistance - 1, 20, 20);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachTop()) << "handle reach top edge";
    richEditorPattern->StopAutoScroll();

    auto handleHeight = 20;
    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    param.handleRect =
        RectF(50, richEditorPattern->contentRect_.Bottom() - edgeDistance - 1 - handleHeight, 20, handleHeight);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "handle move down but not reach bottom edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    param.handleRect =
        RectF(50, richEditorPattern->contentRect_.Bottom() - edgeDistance - handleHeight + 1, 20, handleHeight);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachBottom()) << "handle reach bottom edge";
    richEditorPattern->StopAutoScroll();

    pipeline->taskExecutor_.Reset();
}

/**
 * @tc.name: AutoScrollByEdgeDetection002
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, AutoScrollByEdgeDetection002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->richTextRect_ = RectF(0, -10, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::MOUSE };
    Dimension AUTO_SCROLL_EDGE_DISTANCE = 15.0_vp;
    auto edgeDistance = AUTO_SCROLL_EDGE_DISTANCE.ConvertToPx();

    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->contentRect_.GetY() + edgeDistance + 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "mouse move up but not reach top edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->contentRect_.GetY() + edgeDistance - 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachTop()) << "mouse reach top edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->contentRect_.Bottom() - edgeDistance - 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "mouse move down but not reach bottom edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->contentRect_.Bottom() - edgeDistance + 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachBottom()) << "mouse reach bottom edge";
    richEditorPattern->StopAutoScroll();

    pipeline->taskExecutor_.Reset();
}

/**
 * @tc.name: AutoScrollByEdgeDetection003
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, AutoScrollByEdgeDetection003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->richTextRect_ = RectF(0, -10, 100, 540);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 500);
    richEditorPattern->frameRect_ = RectF(0, 0, 100, 500);

    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::DRAG };
    Dimension AUTO_SCROLL_DRAG_EDGE_DISTANCE = 58.0_vp;
    auto dragDistance = AUTO_SCROLL_DRAG_EDGE_DISTANCE.ConvertToPx();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, OffsetF(50, dragDistance + 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "drag move up but not reach top edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, OffsetF(50, dragDistance - 10), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachTop()) << "drag reach top edge";
    auto speed = richEditorPattern->CalcDragSpeed(dragDistance, 0, dragDistance - 10);
    EXPECT_EQ(richEditorPattern->currentScrollParam_.offset, speed) << "darg speed move up";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->frameRect_.Bottom() - dragDistance - 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "drag move down but not reach bottom edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    auto pointY = richEditorPattern->frameRect_.Bottom() - dragDistance + 10;
    richEditorPattern->AutoScrollByEdgeDetection(param, OffsetF(50, pointY), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachBottom()) << "drag reach bottom edge";
    speed = richEditorPattern->CalcDragSpeed(
        richEditorPattern->frameRect_.Bottom() - dragDistance, richEditorPattern->frameRect_.Bottom(), pointY);
    EXPECT_EQ(richEditorPattern->currentScrollParam_.offset, -speed) << "darg speed move down";
    richEditorPattern->StopAutoScroll();

    pipeline->taskExecutor_.Reset();
}

/**
 * @tc.name: AutoScrollByEdgeDetection004
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, AutoScrollByEdgeDetection004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);

    Dimension AUTO_SCROLL_EDGE_DISTANCE = 15.0_vp;
    auto edgeDistance = AUTO_SCROLL_EDGE_DISTANCE.ConvertToPx();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(50, 50);
    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::HANDLE, .handleRect = RectF(50, 50, 20, 20) };
    richEditorPattern->AutoScrollByEdgeDetection(param, OffsetF(50, 50), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "the touch point is the same as the last time";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, edgeDistance - 1);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "content height is too small.";
    richEditorPattern->StopAutoScroll();

    pipeline->taskExecutor_.Reset();
}

/**
 * @tc.name: CheckScrollable
 * @tc.desc: test CheckScrollable.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, CheckScrollable, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);

    richEditorPattern->CheckScrollable();
    EXPECT_FALSE(richEditorPattern->scrollable_);

    AddSpan(TEST_INSERT_VALUE);
    richEditorPattern->CheckScrollable();
    EXPECT_TRUE(richEditorPattern->scrollable_);

    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 80);
    richEditorPattern->CheckScrollable();
    EXPECT_FALSE(richEditorPattern->scrollable_);

    ClearSpan();
}

/**
 * @tc.name: InitScrollablePattern001
 * @tc.desc: test InitScrollablePattern
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, InitScrollablePattern001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    pipeline->SetThemeManager(theme);

    richEditorPattern->scrollBar_ = nullptr;
    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), false);

    richEditorPattern->overlayMod_ = AceType::MakeRefPtr<TextOverlayModifier>();
    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), false);

    Offset Offset = { 1, 4 };
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);

    richEditorPattern->isTextChange_ = false;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);
}

/**
 * @tc.name: InitScrollablePattern002
 * @tc.desc: test InitScrollablePattern and more.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, InitScrollablePattern002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));

    richEditorPattern->overlayMod_ = AceType::MakeRefPtr<TextOverlayModifier>();
    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), true);

    Offset Offset = { 1, 4 };
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);

    richEditorPattern->isTextChange_ = false;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_EQ(richEditorPattern->HasFocus(), false);

    int32_t scroll_from_update = 1;
    richEditorPattern->scrollBar_ = nullptr;
    richEditorPattern->richTextRect_ = RectF(0, 4, 100, 61);
    richEditorPattern->contentRect_ = RectF(0, 7, 100, 60);
    richEditorPattern->UpdateScrollStateAfterLayout(true);
    EXPECT_TRUE(richEditorPattern->OnScrollCallback(10, scroll_from_update));

    auto offsetF = OffsetF(5.0f, 30.0f);
    richEditorPattern->isShowPlaceholder_ = false;
    richEditorPattern->MoveCaretToContentRect(offsetF, 40.0f);
    EXPECT_EQ(richEditorPattern->GetTextRect(), richEditorPattern->richTextRect_);

    auto offsetFtemp = OffsetF(5.0f, 6.0f);
    richEditorPattern->MoveCaretToContentRect(offsetFtemp, 40.0f);
    EXPECT_EQ(richEditorPattern->GetTextRect(), richEditorPattern->richTextRect_);
}

/**
 * @tc.name: InitScrollablePattern003
 * @tc.desc: test InitScrollablePattern.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, InitScrollablePattern003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    richEditorPattern->overlayMod_ = nullptr;
    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), true);
}

/**
 * @tc.name: InitScrollablePattern004
 * @tc.desc: test InitScrollablePattern.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, InitScrollablePattern004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    ASSERT_NE(richEditorPattern->overlayMod_, nullptr);
    richEditorPattern->InitScrollablePattern();
    EXPECT_EQ(richEditorPattern->GetScrollBar(), true);
}

/**
 * @tc.name: OnAutoScroll001
 * @tc.desc: test OnAutoScroll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, OnAutoScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    AutoScrollParam param;
    param.showScrollbar = true;
    param.offset = 0.0f;
    richEditorPattern->contentChange_ = false;
    richEditorPattern->contentRect_.SetRect(0, 0, 1, 1);
    richEditorPattern->richTextRect_.SetRect(0, 0, 1, 1);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    param.isFirstHandle = true;
    param.autoScrollEvent = AutoScrollEvent::HANDLE;
    richEditorPattern->OnAutoScroll(param);
    EXPECT_TRUE(param.showScrollbar);
    /**
     * @tc.steps: step3. change parameter and call function.
     */
    param.autoScrollEvent = AutoScrollEvent::DRAG;
    richEditorPattern->OnAutoScroll(param);
    EXPECT_TRUE(param.showScrollbar);
    /**
     * @tc.steps: step4. change parameter and call function.
     */
    param.autoScrollEvent = AutoScrollEvent::MOUSE;
    richEditorPattern->OnAutoScroll(param);
    EXPECT_TRUE(param.showScrollbar);
}

/**
 * @tc.name: ScheduleAutoScroll001
 * @tc.desc: test ScheduleAutoScroll
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, ScheduleAutoScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
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
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    richEditorPattern->isAutoScrollRunning_ = true;
    richEditorPattern->ScheduleAutoScroll(param);
    EXPECT_TRUE(param.isFirstRun_);
}

/**
 * @tc.name: OnScrollEndCallback001
 * @tc.desc: test OnScrollEndCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, OnScrollEndCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 6;
    richEditorPattern->contentRect_ = { -500.0, -500.0, 500.0, 500.0 };
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    richEditorPattern->OnScrollEndCallback();
    auto res = richEditorPattern->IsSelectAreaVisible();
    EXPECT_TRUE(res);
}

/**
 * @tc.name: OnScrollEndCallback002
 * @tc.desc: test OnScrollEndCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, OnScrollEndCallback002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 6;
    richEditorPattern->contentRect_ = { -500.0, -500.0, 500.0, 500.0 };

    auto pipeline = richEditorNode_->GetContext();
    pipeline->safeAreaManager_ = nullptr;
    richEditorPattern->OnScrollEndCallback();
    auto res = richEditorPattern->IsSelectAreaVisible();
    EXPECT_FALSE(res);
}

/**
 * @tc.name: OnScrollEndCallback003
 * @tc.desc: test OnScrollEndCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, OnScrollEndCallback003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 6;
    richEditorPattern->contentRect_ = { -500.0, -500.0, 500.0, 500.0 };
    richEditorPattern->isAnimationStop_ = false;
    richEditorPattern->OnScrollEndCallback();
    auto res = richEditorPattern->IsSelectAreaVisible();
    EXPECT_TRUE(res);
}

/**
 * @tc.name: UpdateScrollBarOffset001
 * @tc.desc: test UpdateScrollBarOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, UpdateScrollBarOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto tmpHost = richEditorPattern->GetHost();
    ASSERT_NE(tmpHost, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    richEditorPattern->scrollBar_ = nullptr;
    richEditorPattern->scrollBarProxy_ = nullptr;
    richEditorPattern->UpdateScrollBarOffset();
    EXPECT_FALSE(tmpHost->isPropertyDiffMarked_);
}


/**
 * @tc.name: RichEditorAddSpanAutoScroll001
 * @tc.desc: Test auto scroll when adding a span after the richEditor is ready.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, RichEditorAddSpanAutoScroll001, TestSize.Level1)
{
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isRichEditorInit_ = true;

    // 0: AddTextSpan
    richEditorPattern->needMoveCaretToContentRect_ = false;
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
    EXPECT_TRUE(richEditorPattern->needMoveCaretToContentRect_);

    // 1: AddImageSpan
    richEditorPattern->needMoveCaretToContentRect_ = false;
    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 7);
    EXPECT_TRUE(richEditorPattern->needMoveCaretToContentRect_);

    // 2: AddSymbolSpan
    richEditorPattern->needMoveCaretToContentRect_ = false;
    richEditorPattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 9);
    EXPECT_TRUE(richEditorPattern->needMoveCaretToContentRect_);

    // 3: AddPlaceholderSpan
    richEditorPattern->needMoveCaretToContentRect_ = false;
    richEditorPattern->AddPlaceholderSpan(BUILDER_NODE_1, {});
    EXPECT_EQ(richEditorPattern->caretPosition_, 10);
    EXPECT_TRUE(richEditorPattern->needMoveCaretToContentRect_);
}

/**
 * @tc.name: RichEditorAddSpanAutoScroll002
 * @tc.desc: Test no auto scroll when adding a span before the richEditor is ready.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, RichEditorAddSpanAutoScroll002, TestSize.Level1)
{
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isRichEditorInit_ = false;

    // 0: AddTextSpan
    richEditorPattern->needMoveCaretToContentRect_ = false;
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    EXPECT_FALSE(richEditorPattern->needMoveCaretToContentRect_);

    // 1: AddImageSpan
    richEditorPattern->needMoveCaretToContentRect_ = false;
    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);
    EXPECT_FALSE(richEditorPattern->needMoveCaretToContentRect_);

    // 2: AddSymbolSpan
    richEditorPattern->needMoveCaretToContentRect_ = false;
    richEditorPattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);
    EXPECT_FALSE(richEditorPattern->needMoveCaretToContentRect_);

    // 3: AddPlaceholderSpan
    richEditorPattern->needMoveCaretToContentRect_ = false;
    richEditorPattern->AddPlaceholderSpan(BUILDER_NODE_1, {});
    EXPECT_FALSE(richEditorPattern->needMoveCaretToContentRect_);
}


/**
 * @tc.name: PageScrollTest001
 * @tc.desc: test richEditor pageup and pagedown function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorScrollTestOneNg, PageScrollTest001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto geometryNode = richEditorNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(150.0f, 150.0f));
    richEditorPattern->richTextRect_ = RectF(0, 0, 150.0f, 400.0f);
    richEditorPattern->contentRect_ = RectF(0, 0, 150.0f, 150.0f);

    richEditorPattern->HandleOnPageDown();
    EXPECT_EQ(richEditorPattern->scrollOffset_, -150.0f);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetY(), -150.0f);
    richEditorPattern->HandleOnPageUp();
    EXPECT_EQ(richEditorPattern->scrollOffset_, 0);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetY(), 0);
}

}