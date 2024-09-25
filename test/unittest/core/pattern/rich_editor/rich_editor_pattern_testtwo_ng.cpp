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
 * @tc.name: CalcDragSpeed001
 * @tc.desc: test CalcDragSpeed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, CalcDragSpeed001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    float speed = 0.0f;
    float hotAreaStart = 1.1f;
    float hotAreaEnd = 101.1f;
    float point = 50.1f;
    float result = 17.472723f;
    speed = richEditorPattern->CalcDragSpeed(hotAreaStart, hotAreaEnd, point);
    EXPECT_EQ(result, speed);
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
 * @tc.name: OnSelectionMenuOptionsUpdate001
 * @tc.desc: test OnSelectionMenuOptionsUpdate
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, OnSelectionMenuOptionsUpdate001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    OnCreateMenuCallback onCreateMenuCallback;
    OnMenuItemClickCallback onMenuItemClick;
    richEditorPattern->OnSelectionMenuOptionsUpdate(std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}

/**
 * @tc.name: RequestKeyboardToEdit001
 * @tc.desc: test RequestKeyboardToEdit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, RequestKeyboardToEdit001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->previewLongPress_ = true;
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    richEditorPattern->isEditing_ = false;
    richEditorPattern->RequestKeyboardToEdit();
    EXPECT_FALSE(richEditorPattern->previewLongPress_);
}

/**
 * @tc.name: RequestKeyboardToEdit002
 * @tc.desc: test RequestKeyboardToEdit
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, RequestKeyboardToEdit002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->RequestKeyboardToEdit();
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
 * @tc.name: AdjustWordSelection001
 * @tc.desc: test AdjustWordSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, AdjustWordSelection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start = 100;
    int32_t end = 200;
    bool ret = true;
    ret = richEditorPattern->AdjustWordSelection(start, end);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: InitScrollablePattern003
 * @tc.desc: test InitScrollablePattern.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, InitScrollablePattern003, TestSize.Level1)
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
HWTEST_F(RichEditorPatternTestTwoNg, InitScrollablePattern004, TestSize.Level1)
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
 * @tc.name: OnScrollCallback001
 * @tc.desc: test OnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, OnScrollCallback001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorPattern::OperationRecord record;
    richEditorPattern->DeleteSelectOperation(&record);

    RectF rect(0, 0, 5, 5);
    richEditorPattern->CreateHandles();
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->selectOverlay_->OnHandleMoveDone(rect, true);

    EXPECT_TRUE(richEditorPattern->selectOverlay_->SelectOverlayIsOn());
    bool ret = false;
    ret = richEditorPattern->OnScrollCallback(10, 10);
    EXPECT_TRUE(ret);
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
 * @tc.name: UpdateSelectionByTouchMove001
 * @tc.desc: test UpdateSelectionByTouchMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, UpdateSelectionByTouchMove001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isEditing_ = true;
    Offset touchOffset(11.0f, 11.0f);
    richEditorPattern->UpdateSelectionByTouchMove(touchOffset);
    EXPECT_TRUE(richEditorPattern->isShowMenu_);
}

/**
 * @tc.name: GetSelectedMaxWidth001
 * @tc.desc: test GetSelectedMaxWidth
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, GetSelectedMaxWidth001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto ret = richEditorPattern->GetSelectedMaxWidth();
    EXPECT_EQ(ret, 0.0f);
}

/**
 * @tc.name: GetSelectedMaxWidth002
 * @tc.desc: test GetSelectedMaxWidth
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, GetSelectedMaxWidth002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    std::vector<RectF> rectList;
    rectList.push_back(RectF(1.0f, 1.0f, 5.0f, 10.f));
    auto overlayMod = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    overlayMod->SetSelectedRects(rectList);
    auto ret = richEditorPattern->GetSelectedMaxWidth();
    EXPECT_NE(ret, 0.0f);
}

/**
 * @tc.name: GetSelectedMaxWidth003
 * @tc.desc: test GetSelectedMaxWidth
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, GetSelectedMaxWidth003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    std::vector<RectF> rectList;
    rectList.push_back(RectF(1.0f, 1.0f, 5.0f, 10.f));
    rectList.push_back(RectF(10.0f, 10.0f, 50.0f, 100.f));
    auto overlayMod = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    overlayMod->SetSelectedRects(rectList);
    auto ret = richEditorPattern->GetSelectedMaxWidth();
    EXPECT_NE(ret, 0.0f);
}

/**
 * @tc.name: HandleSelectParagraghPos001
 * @tc.desc: test HandleSelectParagraghPos
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, HandleSelectParagraghPos001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.clear();
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    auto it = richEditorPattern->spans_.front();
    it->content = "test\n123";
    it->position = 4;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->isSpanStringMode_ = true;
    auto ret = richEditorPattern->HandleSelectParagraghPos(true);
    EXPECT_EQ(ret, 0);
    ret = richEditorPattern->HandleSelectParagraghPos(false);
    EXPECT_EQ(ret, 0);
}

/**
 * @tc.name: HandleSelectFontStyle001
 * @tc.desc: test HandleSelectFontStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, HandleSelectFontStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = false;
    KeyCode code = KeyCode::KEY_UNKNOWN;
    richEditorPattern->HandleSelectFontStyle(code);
    EXPECT_EQ(richEditorPattern->isSpanStringMode_, false);
}

/**
 * @tc.name: HandleOnShowMenu001
 * @tc.desc: test HandleOnShowMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, HandleOnShowMenu001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->overlayMod_ = nullptr;
    richEditorPattern->HandleOnShowMenu();
    EXPECT_EQ(richEditorPattern->overlayMod_, nullptr);
}

/**
 * @tc.name: CanStartAITask001
 * @tc.desc: test CanStartAITask
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, CanStartAITask001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textDetectEnable_ = true;
    bool ret = false;
    ret = richEditorPattern->CanStartAITask();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: CanStartAITask002
 * @tc.desc: test CanStartAITask
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, CanStartAITask002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->isEditing_ = true;
    bool ret = true;
    ret = richEditorPattern->CanStartAITask();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: CanStartAITask003
 * @tc.desc: test CanStartAITask
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, CanStartAITask003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->isShowPlaceholder_ = true;
    bool ret = true;
    ret = richEditorPattern->CanStartAITask();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: NeedShowAIDetect001
 * @tc.desc: test NeedShowAIDetect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, NeedShowAIDetect001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::map<int32_t, AISpan> aiSpanMap;
    AISpan aiSpan0;
    aiSpanMap[0] = aiSpan0;
    richEditorPattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;
    richEditorPattern->textDetectEnable_ = true;
    bool ret = false;
    ret = richEditorPattern->NeedShowAIDetect();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: NeedShowAIDetect002
 * @tc.desc: test NeedShowAIDetect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, NeedShowAIDetect002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::map<int32_t, AISpan> aiSpanMap;
    AISpan aiSpan0;
    aiSpanMap[0] = aiSpan0;
    richEditorPattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->isEditing_ = true;
    bool ret = true;
    ret = richEditorPattern->NeedShowAIDetect();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: NeedShowAIDetect003
 * @tc.desc: test NeedShowAIDetect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, NeedShowAIDetect003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::map<int32_t, AISpan> aiSpanMap;
    AISpan aiSpan0;
    aiSpanMap[0] = aiSpan0;
    richEditorPattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->isShowPlaceholder_ = true;
    bool ret = true;
    ret = richEditorPattern->NeedShowAIDetect();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: RefreshSelectOverlay001
 * @tc.desc: test RefreshSelectOverlay
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, RefreshSelectOverlay001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = 100;
    richEditorPattern->UpdateSelectOverlayOrCreate(selectOverlayInfo, true);
    EXPECT_EQ(selectOverlayInfo.hitTestMode, HitTestMode::HTMDEFAULT);
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr, false);
    richEditorPattern->selectOverlayProxy_ = proxy;
    richEditorPattern->RefreshSelectOverlay(false, false);
    EXPECT_NE(proxy, nullptr);
}

/**
 * @tc.name: RefreshSelectOverlay002
 * @tc.desc: test RefreshSelectOverlay
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, RefreshSelectOverlay002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = 100;
    richEditorPattern->UpdateSelectOverlayOrCreate(selectOverlayInfo, true);
    EXPECT_EQ(selectOverlayInfo.hitTestMode, HitTestMode::HTMDEFAULT);
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr, false);
    richEditorPattern->selectOverlayProxy_ = proxy;
    richEditorPattern->RefreshSelectOverlay(true, true);
    EXPECT_NE(proxy, nullptr);
}

/**
 * @tc.name: HideMenu001
 * @tc.desc: test HideMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, HideMenu001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->HideMenu();
    EXPECT_NE(richEditorPattern->selectOverlay_, nullptr);
}

/**
 * @tc.name: ResetKeyboardIfNeed001
 * @tc.desc: test ResetKeyboardIfNeed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, ResetKeyboardIfNeed001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);

    focusHub->currentFocus_ = true;
    richEditorPattern->action_ = TextInputAction::UNSPECIFIED;
    richEditorPattern->ResetKeyboardIfNeed();
    EXPECT_NE(richEditorPattern->action_, TextInputAction::UNSPECIFIED);
}

/**
 * @tc.name: ResetKeyboardIfNeed002
 * @tc.desc: test ResetKeyboardIfNeed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, ResetKeyboardIfNeed002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);

    richEditorPattern->imeShown_ = false;
    richEditorPattern->isCustomKeyboardAttached_ = true;
    focusHub->currentFocus_ = false;
    richEditorPattern->action_ = TextInputAction::SEARCH;
    richEditorPattern->ResetKeyboardIfNeed();
    EXPECT_NE(richEditorPattern->action_, TextInputAction::SEARCH);
}

/**
 * @tc.name: ResetKeyboardIfNeed003
 * @tc.desc: test ResetKeyboardIfNeed
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, ResetKeyboardIfNeed003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);

    richEditorPattern->imeShown_ = false;
    richEditorPattern->isCustomKeyboardAttached_ = false;
    focusHub->currentFocus_ = true;
    richEditorPattern->action_ = TextInputAction::SEARCH;
    richEditorPattern->ResetKeyboardIfNeed();
    EXPECT_NE(richEditorPattern->action_, TextInputAction::SEARCH);
}

/**
 * @tc.name: ScheduleCaretTwinkling001
 * @tc.desc: test ScheduleCaretTwinkling
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, ScheduleCaretTwinkling001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->isCursorAlwaysDisplayed_ = true;
    richEditorPattern->ScheduleCaretTwinkling();
    EXPECT_NE(context->GetCurrentContext(), nullptr);
}

/**
 * @tc.name: ScheduleCaretTwinkling002
 * @tc.desc: test ScheduleCaretTwinkling
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, ScheduleCaretTwinkling002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = nullptr;
    richEditorPattern->ScheduleCaretTwinkling();
    EXPECT_EQ(context->GetTaskExecutor(), nullptr);
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
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto richEditorOverlay = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    richEditorOverlay->caretHeight_->Set(0.0f);
    richEditorPattern->DumpInfo();
    richEditorOverlay->caretHeight_->Set(1.0f);
    richEditorPattern->DumpInfo();
    EXPECT_NE(richEditorPattern->selectOverlay_->HasRenderTransform(), true);
}

/**
 * @tc.name: SetSelection001
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, SetSelection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    richEditorPattern->previewTextRecord_.previewContent = "test";
    richEditorPattern->previewTextRecord_.isPreviewTextInputting = true;
    richEditorPattern->previewTextRecord_.startOffset = 1;
    richEditorPattern->previewTextRecord_.endOffset = 10;

    int32_t start = 1;
    int32_t end = 3;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_NE(richEditorPattern->HasFocus(), false);
}

/**
 * @tc.name: SetSelection002
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, SetSelection002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AccessibilityManager::MakeRefPtr<MutableSpanString>("test123456");
    int32_t start = -1;
    int32_t end = -1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_NE(richEditorPattern->HasFocus(), false);
}

/**
 * @tc.name: SetSelection003
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, SetSelection003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AccessibilityManager::MakeRefPtr<MutableSpanString>("test123456");
    richEditorPattern->textSelector_ = TextSelector(0, 6);

    int32_t start = 1;
    int32_t end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_NE(richEditorPattern->HasFocus(), false);
}

/**
 * @tc.name: SetSelection004
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, SetSelection004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AccessibilityManager::MakeRefPtr<MutableSpanString>("test123456");
    richEditorPattern->textSelector_ = TextSelector(2, 4);
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    pipeline->themeManager_ = theme;

    richEditorPattern->customKeyboardBuilder_ = []() {};
    richEditorPattern->DumpInfo();
    richEditorPattern->isTextChange_ = false;
    EXPECT_EQ(richEditorPattern->IsShowHandle(), true);

    int32_t start = 2;
    int32_t end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_NE(richEditorPattern->HasFocus(), false);
}

/**
 * @tc.name: SetSelection005
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, SetSelection005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AccessibilityManager::MakeRefPtr<MutableSpanString>("test123456");

    richEditorPattern->textSelector_ = TextSelector(2, 4);

    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    pipeline->themeManager_ = theme;

    richEditorPattern->customKeyboardBuilder_ = []() {};
    richEditorPattern->DumpInfo();
    richEditorPattern->isTextChange_ = false;
    EXPECT_EQ(richEditorPattern->IsShowHandle(), true);

    int32_t start = 2;
    int32_t end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_NE(richEditorPattern->HasFocus(), false);
}

/**
 * @tc.name: SetSelection006
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestTwoNg, SetSelection006, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    EXPECT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;

    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AccessibilityManager::MakeRefPtr<MutableSpanString>("test123456");
    richEditorPattern->textSelector_ = TextSelector(2, 4);

    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    pipeline->themeManager_ = theme;

    richEditorPattern->customKeyboardBuilder_ = []() {};
    richEditorPattern->DumpInfo();
    richEditorPattern->isTextChange_ = false;
    EXPECT_EQ(richEditorPattern->IsShowHandle(), true);

    int32_t start = 2;
    int32_t end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    richEditorPattern->SetSelection(start, end, options, false);
    EXPECT_NE(richEditorPattern->HasFocus(), false);
}
} // namespace OHOS::Ace::NG