/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_scroll_controller.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorFreeScrollTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
};

void RichEditorFreeScrollTestNg::SetUp()
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
    richEditorPattern->GetRichEditorController()->SetPattern(
        AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorFreeScrollTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

/**
 * @tc.name: InitFreeScrollController001
 * @tc.desc: Test InitFreeScrollController
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, InitFreeScrollController001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);

    // Branch: freeScrollController_ null → create new controller
    ASSERT_FALSE(controller->IsFreeScrollEnabled());
    controller->InitFreeScrollController();
    ASSERT_TRUE(controller->IsFreeScrollEnabled());

    // Branch: freeScrollController_ exists + forceRecreate=false → early return
    auto oldFreeCtrl = controller->freeScrollController_;
    controller->InitFreeScrollController(false);
    ASSERT_EQ(controller->freeScrollController_, oldFreeCtrl);

    // Branch: freeScrollController_ exists + forceRecreate=true → reset then recreate
    controller->InitFreeScrollController(true);
    ASSERT_NE(controller->freeScrollController_, oldFreeCtrl);
}

/**
 * @tc.name: SetScrollBar001
 * @tc.desc: Test SetScrollBar
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, SetScrollBar001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);

    // Branch: displayMode==OFF + scrollBar_ null → isScrollBarModifierPropertyAttached_ reset
    controller->SetScrollBar(DisplayMode::OFF);
    ASSERT_EQ(controller->scrollBar_, nullptr);
    ASSERT_FALSE(controller->isScrollBarModifierPropertyAttached_);

    // Branch: displayMode!=OFF + scrollBar_ null + oldMode!=displayMode → create and set mode
    controller->SetScrollBar(DisplayMode::AUTO);
    ASSERT_NE(controller->scrollBar_, nullptr);
    ASSERT_EQ(controller->scrollBar_->GetDisplayMode(), DisplayMode::AUTO);

    // Branch: displayMode!=OFF + scrollBar_ exists + oldMode==displayMode → skip inner block
    controller->SetScrollBar(DisplayMode::AUTO);
    ASSERT_EQ(controller->scrollBar_->GetDisplayMode(), DisplayMode::AUTO);

    // Branch: isSingleLineMode_ true → vertical scrollable disabled
    pattern->isSingleLineMode_ = true;
    controller->SetScrollBar(DisplayMode::ON);
    ASSERT_FALSE(controller->scrollBar_->IsVerticalScrollable());
    pattern->isSingleLineMode_ = false;

    // Branch: displayMode==OFF + scrollBar_ exists → reset scrollBar_
    controller->SetScrollBar(DisplayMode::OFF);
    ASSERT_FALSE(controller->scrollBar_);

    // Branch: isRTL → PositionMode LEFT; isLTR → PositionMode RIGHT
    controller->SetScrollBar(DisplayMode::AUTO);
    auto layoutProperty = pattern->GetLayoutProperty<RichEditorLayoutProperty>();
    layoutProperty->layoutDirection_ = TextDirection::RTL;
    controller->SetScrollBar(DisplayMode::ON);
    ASSERT_NE(controller->scrollBar_->GetVerticalBar(), nullptr);
    ASSERT_EQ(controller->scrollBar_->GetVerticalBar()->GetPositionMode(), PositionMode::LEFT);
    layoutProperty->layoutDirection_ = TextDirection::LTR;
    controller->SetScrollBar(DisplayMode::AUTO);
    ASSERT_EQ(controller->scrollBar_->GetVerticalBar()->GetPositionMode(), PositionMode::RIGHT);
}

/**
 * @tc.name: MoveTextRectWithAxis001
 * @tc.desc: Test MoveTextRectWithAxis
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, MoveTextRectWithAxis001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->InitFreeScrollController();
    controller->SetScrollBar(DisplayMode::ON);

    // Branch: isSingleLineMode_ + Axis::VERTICAL → IsScrollDirectionValid false → return 0.0f
    pattern->isSingleLineMode_ = true;
    ASSERT_EQ(controller->MoveTextRectWithAxis(10.0f, Axis::VERTICAL), 0.0f);

    // Branch: isSingleLineMode_ + Axis::HORIZONTAL → valid direction, MoveTextRectHorizontal
    pattern->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 50.0f);
    pattern->richTextRect_ = RectF(-5.0f, 0.0f, 120.0f, 50.0f);
    auto hOffset = controller->MoveTextRectWithAxis(5.0f, Axis::HORIZONTAL);
    ASSERT_EQ(hOffset, 5.0f);
    ASSERT_EQ(controller->textRect_.GetX(), 0.0f);

    // Branch: !isSingleLineMode_ + Axis::VERTICAL → valid direction, MoveTextRectVertical
    pattern->isSingleLineMode_ = false;
    pattern->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 50.0f);
    pattern->richTextRect_ = RectF(0.0f, -3.0f, 100.0f, 80.0f);
    auto vOffset = controller->MoveTextRectWithAxis(3.0f, Axis::VERTICAL);
    ASSERT_EQ(vOffset, 3.0f);
    ASSERT_EQ(controller->textRect_.GetY(), 0.0f);
}

/**
 * @tc.name: HandleScrollCallback001
 * @tc.desc: Test HandleScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, HandleScrollCallback001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->InitFreeScrollController();

    // Branch: HandleScrollCallback - invalid direction (isVertical + isSingleLineMode) → early return
    pattern->isSingleLineMode_ = true;
    controller->scrollingAxis_ = Axis::VERTICAL;
    controller->HandleScrollCallback(10.0f, SCROLL_FROM_START, true);
    ASSERT_EQ(controller->scrollingAxis_, Axis::VERTICAL);

    // Branch: HandleScrollCallback - valid direction + source=SCROLL_FROM_START → scrollingAxis_ set
    pattern->isSingleLineMode_ = false;
    controller->HandleScrollCallback(10.0f, SCROLL_FROM_START, false);
    ASSERT_EQ(controller->scrollingAxis_, Axis::HORIZONTAL);

    // Branch: HandleScrollCallback - valid direction + source!=SCROLL_FROM_START + !IsReachAvoidBoundary
    controller->HandleScrollCallback(0.0f, SCROLL_FROM_NONE, true);
    ASSERT_EQ(controller->scrollingAxis_, Axis::HORIZONTAL);

    // Branch: HandleScrollCallback - valid direction + source!=SCROLL_FROM_START + IsReachAvoidBoundary → stop
    pattern->contentRect_ = RectF(0.0f, 0.0f, 300.0f, 300.0f);
    pattern->richTextRect_ = RectF(0.0f, 0.0f, 300.0f, 300.0f);
    controller->HandleScrollCallback(5.0f, SCROLL_FROM_NONE, true);
    ASSERT_EQ(controller->scrollingAxis_, Axis::HORIZONTAL);
}

/**
 * @tc.name: UpdateScrollBarOffsetWithAxis001
 * @tc.desc: Test UpdateScrollBarOffsetWithAxis
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorFreeScrollTestNg, UpdateScrollBarOffsetWithAxis001, TestSize.Level1)
{
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto& controller = pattern->scrollController_;
    ASSERT_NE(controller, nullptr);
    controller->InitFreeScrollController();
    controller->SetScrollBar(DisplayMode::ON);

    // Branch: isSingleLineMode_ + Axis::VERTICAL → IsScrollDirectionValid false → early return
    pattern->isSingleLineMode_ = true;
    controller->UpdateScrollBarOffsetWithAxis(Axis::VERTICAL);
    ASSERT_FALSE(controller->scrollBar_->IsVerticalScrollable());
    pattern->isSingleLineMode_ = false;

    pattern->contentRect_ = RectF(0.0f, 0.0f, 100.0f, 50.0f);
    pattern->richTextRect_ = RectF(0.0f, -5.0f, 120.0f, 60.0f);
    pattern->frameRect_ = RectF(0.0f, 0.0f, 100.0f, 50.0f);

    // Branch: Axis::NONE → early return
    controller->UpdateScrollBarOffsetWithAxis(Axis::NONE);
    ASSERT_FALSE(controller->scrollBar_->IsVerticalScrollable());

    // Branch: Axis::VERTICAL + hasText=false → SetVerticalScrollable(false)
    controller->UpdateScrollBarOffsetWithAxis(Axis::VERTICAL, false);
    ASSERT_FALSE(controller->scrollBar_->IsVerticalScrollable());

    // Branch: Axis::HORIZONTAL + hasText=false → SetHorizontalScrollable(false)
    controller->UpdateScrollBarOffsetWithAxis(Axis::HORIZONTAL, false);
    ASSERT_FALSE(controller->scrollBar_->IsHorizontalScrollable());

    AddSpan(TEST_STR);

    // Branch: Axis::VERTICAL + hasText=true + needAnimation=false → SetVerticalScrollable(true)
    controller->UpdateScrollBarOffsetWithAxis(Axis::VERTICAL, false);
    ASSERT_TRUE(controller->scrollBar_->IsVerticalScrollable());

    // Branch: Axis::HORIZONTAL + hasText=true + needAnimation=true → SetHorizontalScrollable(true)
    controller->UpdateScrollBarOffsetWithAxis(Axis::HORIZONTAL, true);
    ASSERT_TRUE(controller->scrollBar_->IsHorizontalScrollable());
}

} // namespace OHOS::Ace::NG
