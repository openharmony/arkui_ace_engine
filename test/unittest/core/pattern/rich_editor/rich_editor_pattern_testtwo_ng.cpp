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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_clipboard.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
} // namespace

class RichEditorPatternTestTwoNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorPatternTestTwoNg::SetUp()
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
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorPatternTestTwoNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorPatternTestTwoNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: CalcMoveDownPos001
 * @tc.desc: test CalcMoveDownPos
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, CalcMoveDownPos001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->overlayMod_ = nullptr;
    int32_t result = 1;
    float leadingMarginOffset = 10.0f;
    result = richEditorPattern->CalcMoveDownPos(leadingMarginOffset);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: CalcMoveDownPos002
 * @tc.desc: test CalcMoveDownPos
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, CalcMoveDownPos002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ASSERT_NE(richEditorPattern->overlayMod_, nullptr);
    int32_t result = 1;
    float leadingMarginOffset = 10.0f;
    result = richEditorPattern->CalcMoveDownPos(leadingMarginOffset);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: CalcLineBeginPosition001
 * @tc.desc: test CalcLineBeginPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, CalcLineBeginPosition001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t result = 1;
    result = richEditorPattern->CalcLineBeginPosition();
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: IsResponseRegionExpandingNeededForStylus001
 * @tc.desc: test IsResponseRegionExpandingNeededForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, IsResponseRegionExpandingNeededForStylus001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::UNKNOWN;
    bool ret = true;
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: TripleClickSection001
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, TripleClickSection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetHost()->GetFocusHub()->SetFocusType(FocusType::DISABLE);
    GestureEvent info = GestureEvent();
    info.sourceTool_ = SourceTool::FINGER;
    richEditorPattern->TripleClickSection(info, 1, 10, 2);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: TripleClickSection002
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, TripleClickSection002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetHost()->GetFocusHub()->SetFocusType(FocusType::DISABLE);
    GestureEvent info = GestureEvent();
    info.sourceTool_ = SourceTool::FINGER;
    richEditorPattern->TripleClickSection(info, 10, 10, 2);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: DumpInfo001
 * @tc.desc: test DumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, DumpInfo001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto richEditorOverlay = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    richEditorOverlay->caretHeight_->Set(0.0f);
    richEditorPattern->DumpInfo();
    richEditorOverlay->caretHeight_->Set(1.0f);
    richEditorPattern->DumpInfo();
    EXPECT_NE(richEditorPattern->selectOverlay_->HasRenderTransform(), true);
}

/**
 * @tc.name: CalcCursorOffsetByPosition002
 * @tc.desc: test CalcCursorOffsetByPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, CalcCursorOffsetByPosition002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    float selectLineHeight = 0;
    ClearSpan();
    AddSpan("test");
    auto host = richEditorPattern->GetHost();
    EXPECT_NE(host, nullptr);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<SpanNode>(V2::IMAGE_ETS_TAG, -1);
    std::list<RefPtr<UINode>> child = { customNode };
    host->ModifyChildren() = child;
    int32_t position = 2;
    bool downStreamFirst = true;
    bool needLineHighest = true;
    auto startOffset = richEditorPattern->paragraphs_.ComputeCursorOffset(
        position, selectLineHeight, downStreamFirst, needLineHighest);
    auto offset =
        richEditorPattern->CalcCursorOffsetByPosition(position, selectLineHeight, downStreamFirst, needLineHighest);
    EXPECT_EQ(startOffset, offset);
}

/**
 * @tc.name: IsResponseRegionExpandingNeededForStylus002
 * @tc.desc: test IsResponseRegionExpandingNeededForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, IsResponseRegionExpandingNeededForStylus002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEvent touchEvent;
    touchEvent.type = TouchType::UNKNOWN;
    bool ret = true;
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: IsResponseRegionExpandingNeededForStylus003
 * @tc.desc: test IsResponseRegionExpandingNeededForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, IsResponseRegionExpandingNeededForStylus003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::PEN;
    touchEvent.type = TouchType::DOWN;
    bool ret = false;
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: ExpandDefaultResponseRegion001
 * @tc.desc: test ExpandDefaultResponseRegion
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, ExpandDefaultResponseRegion001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RectF rect(0, 0, 5, 5);
    RectF retRect;
    retRect = richEditorPattern->ExpandDefaultResponseRegion(rect);
    EXPECT_EQ(rect.Width(), retRect.Width());
}

/**
 * @tc.name: GetCrossOverHeight001
 * @tc.desc: test GetCrossOverHeight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, GetCrossOverHeight001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->status_ = Status::DRAGGING;
    richEditorPattern->CreateHandles();
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = true;
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
}

/**
 * @tc.name: GetCrossOverHeight002
 * @tc.desc: test GetCrossOverHeight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, GetCrossOverHeight002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->status_ = Status::DRAGGING;
    richEditorPattern->CreateHandles();
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = true;
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->rootHeight_ = 80.0;
    SafeAreaInsets::Inset insetBottom;
    insetBottom.start = 70;
    insetBottom.end = 80;
    pipeline->GetSafeAreaManager()->keyboardInset_ = SafeAreaInsets::Inset(insetBottom);
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 0.0f);
}

/**
 * @tc.name: GetCrossOverHeight003
 * @tc.desc: test GetCrossOverHeight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, GetCrossOverHeight003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->status_ = Status::DRAGGING;
    richEditorPattern->CreateHandles();
    richEditorPattern->contentChange_ = true;
    richEditorPattern->keyboardAvoidance_ = true;
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->rootHeight_ = 80.0;
    SafeAreaInsets::Inset insetBottom;
    insetBottom.start = 1;
    insetBottom.end = 86;
    pipeline->GetSafeAreaManager()->keyboardInset_ = SafeAreaInsets::Inset(insetBottom);
    EXPECT_EQ(richEditorPattern->GetCrossOverHeight(), 5.0f);
}

/**
 * @tc.name: MoveTextRect001
 * @tc.desc: test MoveTextRect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, MoveTextRect001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->richTextRect_ = RectF(0, 5, 100, 160);
    richEditorPattern->contentRect_ = RectF(0, 10, 100, 140);
    richEditorPattern->UpdateScrollStateAfterLayout(true);
    EXPECT_EQ(richEditorPattern->MoveTextRect(0.0f), 0.0f);
}

/**
 * @tc.name: IsResponseRegionExpandingNeededForStylus004
 * @tc.desc: test IsResponseRegionExpandingNeededForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, IsResponseRegionExpandingNeededForStylus004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::PEN;
    touchEvent.type = TouchType::UNKNOWN;
    bool ret = true;
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: IsResponseRegionExpandingNeededForStylus005
 * @tc.desc: test IsResponseRegionExpandingNeededForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, IsResponseRegionExpandingNeededForStylus005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetHost()->GetFocusHub()->SetFocusType(FocusType::DISABLE);
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::PEN;
    touchEvent.type = TouchType::DOWN;
    bool ret = true;
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: IsResponseRegionExpandingNeededForStylus006
 * @tc.desc: test testInput text IsResponseRegionExpandingNeededForStylus001
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, IsResponseRegionExpandingNeededForStylus006, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.x = 10;
    touchEvent.y = 10;
    auto ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
    touchEvent.sourceTool = SourceTool::PEN;
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_TRUE(ret);
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.type = TouchType::MOVE;
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
    touchEvent.sourceTool = SourceTool::PEN;
    touchEvent.type = TouchType::MOVE;
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
    touchEvent.type = TouchType::DOWN;
    touchEvent.sourceTool = SourceTool::PEN;
    EXPECT_TRUE(richEditorNode_->IsVisible());
    richEditorNode_->layoutProperty_->OnVisibilityUpdate(VisibleType::INVISIBLE);
    EXPECT_FALSE(richEditorNode_->IsVisible());
    ret = richEditorPattern->IsResponseRegionExpandingNeededForStylus(touchEvent);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto rendenContext = richEditorNode_->GetRenderContext();
    ASSERT_NE(rendenContext, nullptr);
    rendenContext->ResetClipEdge();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    DirtySwapConfig config;
    richEditorPattern->isModifyingContent_ = true;
    auto ret = richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);
}

} // namespace OHOS::Ace::NG