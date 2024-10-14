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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_clipboard.h"
#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t RECORD_MAX_LENGTH = 20;
const std::string TEST_INSERT_LINE_SPACE = " ";
} // namespace

class RichEditorPatternTestThreeNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
    RefPtr<RichEditorPattern> GetRichEditorPattern();
};

void RichEditorPatternTestThreeNg::SetUp()
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

void RichEditorPatternTestThreeNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorPatternTestThreeNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

RefPtr<RichEditorPattern> RichEditorPatternTestThreeNg::GetRichEditorPattern()
{
    CHECK_NULL_RETURN(richEditorNode_, nullptr);
    return richEditorNode_->GetPattern<RichEditorPattern>();
}

/**
 * @tc.name: SetInputMethodStatus001
 * @tc.desc: test SetInputMethodStatus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, SetInputMethodStatus001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
#if defined(OHOS_STANDARD_SYSTEM) && !defined(PREVIEW)
    richEditorPattern->SetInputMethodStatus(true);
    EXPECT_TRUE(richEditorPattern->imeShown_);
    richEditorPattern->SetInputMethodStatus(false);
    EXPECT_FALSE(richEditorPattern->imeShown_);
#endif
}

/**
 * @tc.name: BeforeStatusCursorMove001
 * @tc.desc: test BeforeStatusCursorMove
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, BeforeStatusCursorMove001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);

    SelectOverlayInfo overlayInfo;
    auto shareOverlayInfo = std::make_shared<SelectOverlayInfo>(overlayInfo);
    auto overlayNode = SelectOverlayNode::CreateSelectOverlayNode(shareOverlayInfo);
    auto manager = SelectContentOverlayManager::GetOverlayManager();
    ASSERT_NE(manager, nullptr);
    manager->selectOverlayNode_ = overlayNode;
    richEditorPattern->textSelector_.Update(1, 2);
    EXPECT_FALSE(richEditorPattern->BeforeStatusCursorMove(true));
}

/**
 * @tc.name: CursorMoveRight001
 * @tc.desc: test CursorMoveRight
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CursorMoveRight001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->CursorMoveRight();
    EXPECT_TRUE(richEditorPattern->caretVisible_);
}

/**
 * @tc.name: CursorMoveLeftAndRightWord001
 * @tc.desc: test CursorMoveLeftWord and CursorMoveRightWord
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CursorMoveLeftWord001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_FALSE(richEditorPattern->CursorMoveLeftWord());
    EXPECT_FALSE(richEditorPattern->CursorMoveRightWord());
}

/**
 * @tc.name: CursorMoveToParagraphBegin001
 * @tc.desc: test CursorMoveToParagraphBegin
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CursorMoveToParagraphBegin001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_FALSE(richEditorPattern->CursorMoveToParagraphBegin());
    AddSpan(TEST_INSERT_LINE_SEP);
    richEditorPattern->caretPosition_ = 1;
    EXPECT_TRUE(richEditorPattern->CursorMoveToParagraphBegin());
}

/**
 * @tc.name: CursorMoveEnd001
 * @tc.desc: test CursorMoveToParagraphBegin
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CursorMoveEnd001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_FALSE(richEditorPattern->CursorMoveToParagraphBegin());
}

/**
 * @tc.name: GetLeftWordPosition001
 * @tc.desc: test GetLeftWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetLeftWordPosition001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->GetLeftWordPosition(richEditorPattern->caretPosition_), 0);
    AddSpan(INIT_VALUE_1 + TEST_INSERT_LINE_SPACE);
    EXPECT_EQ(richEditorPattern->GetLeftWordPosition(richEditorPattern->GetTextContentLength()), 0);
}

/**
 * @tc.name: GetRightWordPosition001
 * @tc.desc: test GetRightWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetRightWordPosition001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->GetLeftWordPosition(richEditorPattern->caretPosition_), 0);
    AddSpan(INIT_VALUE_1 + TEST_INSERT_LINE_SPACE);
    EXPECT_EQ(richEditorPattern->GetRightWordPosition(richEditorPattern->GetTextContentLength()),
        richEditorPattern->GetTextContentLength());
}

/**
 * @tc.name: HandleSelect001
 * @tc.desc: test HandleSelect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleSelect001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_EQ(richEditorPattern->GetLeftWordPosition(richEditorPattern->caretPosition_), 0);
    AddSpan(INIT_VALUE_1 + TEST_INSERT_LINE_SPACE);
    richEditorPattern->HandleSelect(CaretMoveIntent::Home);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), richEditorPattern->textSelector_.GetStart());
}

/**
 * @tc.name: HandleOnEscape001
 * @tc.desc: test HandleOnEscape
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleOnEscape001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_FALSE(richEditorPattern->HandleOnEscape());
}

/**
 * @tc.name: HandleOnUndoAction001
 * @tc.desc: test HandleOnUndoAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleOnUndoAction001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorPattern::OperationRecord firstRecord;
    firstRecord.addText = "first Record helloWorld";
    firstRecord.deleteText = "helloWorld";
    richEditorPattern->operationRecords_.emplace_back(firstRecord);
    richEditorPattern->redoOperationRecords_.clear();
    for (uint32_t count = 0; count < RECORD_MAX_LENGTH; ++count) {
        RichEditorPattern::OperationRecord emptyRecord;
        richEditorPattern->redoOperationRecords_.emplace_back(emptyRecord);
    }
    richEditorPattern->HandleOnUndoAction();
    EXPECT_TRUE(richEditorPattern->operationRecords_.empty());

    RichEditorPattern::OperationRecord secondRecord;
    secondRecord.addText = "second Record helloWorld";
    secondRecord.deleteCaretPostion = 3;
    richEditorPattern->operationRecords_.clear();
    richEditorPattern->operationRecords_.emplace_back(secondRecord);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_TRUE(richEditorPattern->operationRecords_.empty());
}

/**
 * @tc.name: HandleOnRedoAction001
 * @tc.desc: test HandleOnRedoAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleOnRedoAction001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->HandleOnRedoAction();
    RichEditorPattern::OperationRecord firstRecord;
    firstRecord.addText = "first Record helloWorld";
    firstRecord.deleteCaretPostion = 3;
    richEditorPattern->redoOperationRecords_.emplace_back(firstRecord);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_TRUE(richEditorPattern->redoOperationRecords_.empty());

    RichEditorPattern::OperationRecord secondRecord;
    secondRecord.addText = "second Record helloWorld";
    secondRecord.deleteText = "helloWorld";
    richEditorPattern->redoOperationRecords_.clear();
    richEditorPattern->redoOperationRecords_.emplace_back(secondRecord);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_TRUE(richEditorPattern->redoOperationRecords_.empty());

    RichEditorPattern::OperationRecord thridRecord;
    thridRecord.deleteText = "helloWorld";
    thridRecord.beforeCaretPosition = 10;
    thridRecord.afterCaretPosition = 15;
    richEditorPattern->redoOperationRecords_.clear();
    richEditorPattern->redoOperationRecords_.emplace_back(thridRecord);
    richEditorPattern->HandleOnRedoAction();
    EXPECT_TRUE(richEditorPattern->redoOperationRecords_.empty());
}

/**
 * @tc.name: CalcDeleteValueObj001
 * @tc.desc: test CalcDeleteValueObj delete builder span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CalcDeleteValueObj001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    auto spans = richEditorPattern->GetSpanItemChildren();
    ASSERT_FALSE(spans.empty());
    auto spanItem = spans.back();
    ASSERT_NE(spanItem, nullptr);
    int32_t currentPosition = INIT_VALUE_1.size() - 2;
    spanItem->placeholderIndex = currentPosition;

    RichEditorDeleteValue info;
    int32_t length = 2;
    richEditorPattern->CalcDeleteValueObj(currentPosition, length, info);
    EXPECT_EQ(info.GetRichEditorDeleteSpans().size(), 1);
}

/**
 * @tc.name: GetSpanNodeBySpanItem001
 * @tc.desc: test GetSpanNodeBySpanItem
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetSpanNodeBySpanItem001, TestSize.Level2)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    ASSERT_EQ(richEditorPattern->GetSpanNodeBySpanItem(nullptr), nullptr);
}

/**
 * @tc.name: DeleteValueSetImageSpan001
 * @tc.desc: test DeleteValueSetImageSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, DeleteValueSetImageSpan001, TestSize.Level1)
{
    AddImageSpan();
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto imageNode = AceType::DynamicCast<FrameNode>(richEditorNode_->GetLastChild());
    ASSERT_NE(imageNode, nullptr);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
    imageLayoutProperty->UpdateVerticalAlign(VerticalAlign::CENTER);

    RichEditorAbstractSpanResult spanResult;
    spanResult.SetSpanIndex(richEditorNode_->GetChildIndexById(imageNode->GetId()));

    auto spans = richEditorPattern->GetSpanItemChildren();
    ASSERT_FALSE(spans.empty());
    auto imageSpanItem = AceType::DynamicCast<ImageSpanItem>(spans.back());
    ASSERT_NE(imageSpanItem, nullptr);
    richEditorPattern->DeleteValueSetImageSpan(imageSpanItem, spanResult);
    EXPECT_EQ(spanResult.GetObjectFit(), ImageFit::FILL);
    EXPECT_EQ(spanResult.GetVerticalAlign(), VerticalAlign::CENTER);
}

/**
 * @tc.name: HandleOnCopyStyledString001
 * @tc.desc: test HandleOnCopyStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleOnCopyStyledString001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);

    richEditorPattern->OnModifyDone();
    richEditorPattern->SetSpanStringMode(true);
    richEditorPattern->OnCopyOperation();
    ASSERT_NE(richEditorPattern->GetClipboard(), nullptr);
}

/**
 * @tc.name: OnCopyOperationExt001
 * @tc.desc: test OnCopyOperationExt
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, OnCopyOperationExt001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);

    richEditorPattern->OnModifyDone();
    auto clipboard = richEditorPattern->GetClipboard();
    ASSERT_NE(clipboard, nullptr);
    auto pasteDataMix = clipboard->CreatePasteDataMix();
    richEditorPattern->OnCopyOperationExt(pasteDataMix);
}

/**
 * @tc.name: ClearContent001
 * @tc.desc: test ClearContent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, ClearContent001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto placeholderSpanNode = PlaceholderSpanNode::GetOrCreateSpanNode(V2::PLACEHOLDER_SPAN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<PlaceholderSpanPattern>(); });
    auto placeholderSpanItem = placeholderSpanNode->GetSpanItem();
    ASSERT_NE(placeholderSpanItem, nullptr);
    placeholderSpanItem->content = " ";
    placeholderSpanNode->MountToParent(richEditorNode_);
    richEditorPattern->ClearContent(placeholderSpanNode);
    EXPECT_TRUE(placeholderSpanItem->content.empty());
}

/**
 * @tc.name: UpdateTextFieldManager001
 * @tc.desc: test UpdateTextFieldManager
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, UpdateTextFieldManager001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    textFieldManager->SetHeight(20);
    context->SetTextFieldManager(textFieldManager);

    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    context->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->currentFocus_ = true;
    Offset Offset = { 1, 4 };
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->UpdateTextFieldManager(Offset, 1.0f);
    EXPECT_NE(textFieldManager->GetOnFocusTextField().Upgrade(), nullptr);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto rendenContext = richEditorNode_->GetRenderContext();
    ASSERT_NE(rendenContext, nullptr);
    rendenContext->UpdateClipEdge(false);
    auto geometryNode = richEditorNode_->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto globalOffset = OffsetF(15.0f, 3.0f);
    geometryNode->SetFrameSize(SizeF(20.0f, 5.0f));
    geometryNode->SetFrameOffset(globalOffset);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->parentGlobalOffset_ = globalOffset;
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    DirtySwapConfig config;
    richEditorPattern->baselineOffset_ = 6.0f;
    richEditorPattern->CreateNodePaintMethod();
    auto ret = richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: HandleUserGestureEvent001
 * @tc.desc: test HandleUserGestureEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleUserGestureEvent001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    firstSpanItem->leadingMargin = std::make_optional<NG::LeadingMargin>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 10 });

    std::vector<RectF> rects { RectF(0, 0, 5, 5) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<THIRD_PARAM>(rects));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    GestureEvent info;
    info.SetLocalLocation(Offset(3, 3));
    richEditorPattern->contentRect_ = RectF(0, 0, 20.0, 20.0);
    auto gestureFunc = [](RefPtr<SpanItem> item, GestureEvent& info) -> bool { return true; };
    EXPECT_TRUE(richEditorPattern->HandleUserGestureEvent(info, std::move(gestureFunc)));
}

/**
 * @tc.name: HandleTouchEvent001
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleTouchEvent001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEventInfo touchEventInfo("");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::DOWN;
    touchLocationInfo.localLocation_ = Offset(0.0f, 0.0f);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    richEditorPattern->HandleTouchEvent(touchEventInfo);
    auto touchInfo = touchEventInfo.GetTouches().front();
    auto touchType = touchInfo.GetTouchType();
    EXPECT_EQ(touchType, TouchType::DOWN);
}

/**
 * @tc.name: HandleTouchEvent002
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleTouchEvent002, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEventInfo touchEventInfo("");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::UP;
    touchLocationInfo.localLocation_ = Offset(0.0f, 0.0f);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    richEditorPattern->HandleTouchEvent(touchEventInfo);
    auto touchInfo = touchEventInfo.GetTouches().front();
    auto touchType = touchInfo.GetTouchType();
    EXPECT_EQ(touchType, TouchType::UP);
}

/**
 * @tc.name: HandleTouchEvent003
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleTouchEvent003, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEventInfo touchEventInfo("");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::MOVE;
    touchLocationInfo.localLocation_ = Offset(0.0f, 0.0f);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    richEditorPattern->HandleTouchEvent(touchEventInfo);
    auto touchInfo = touchEventInfo.GetTouches().front();
    auto touchType = touchInfo.GetTouchType();
    EXPECT_EQ(touchType, TouchType::MOVE);
}

/**
 * @tc.name: HandleTouchEvent004
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleTouchEvent004, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEventInfo touchEventInfo("");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::UNKNOWN;
    touchLocationInfo.localLocation_ = Offset(0.0f, 0.0f);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    richEditorPattern->HandleTouchEvent(touchEventInfo);
    auto touchInfo = touchEventInfo.GetTouches().front();
    auto touchType = touchInfo.GetTouchType();
    EXPECT_EQ(touchType, TouchType::UNKNOWN);
}

/**
 * @tc.name: GetRightWordPosition002
 * @tc.desc: test GetRightWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetRightWordPosition002, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    std::string firstText = "text";
    AddSpan(firstText);
    std::string space = " ";
    std::string secondText = "content";
    AddSpan(space + secondText);
    auto initCaretPosition = firstText.size();
    EXPECT_EQ(richEditorPattern->GetRightWordPosition(initCaretPosition), initCaretPosition + space.size());
}

/**
 * @tc.name: GetRightWordPosition003
 * @tc.desc: test GetRightWordPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetRightWordPosition003, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    std::string firstText = "Text ";
    AddSpan(firstText);
    std::string secondText = "Content\n";
    AddSpan(secondText);
    AddSpan(INIT_VALUE_3);

    auto initCaretPosition = firstText.size() + secondText.size() - 1;
    EXPECT_EQ(richEditorPattern->GetRightWordPosition(initCaretPosition), initCaretPosition + 1);
}

/**
 * @tc.name: InitScrollablePattern001
 * @tc.desc: test InitScrollablePattern when update padding property
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, InitScrollablePattern001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto layoutProperty = richEditorPattern->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    PaddingProperty padding;
    padding.top = CalcLength(10);
    padding.left = CalcLength(10);
    padding.right = CalcLength(10);
    padding.bottom = CalcLength(10);
    layoutProperty->UpdatePadding(padding);
    richEditorPattern->InitScrollablePattern();
    EXPECT_TRUE(IsEqual(richEditorPattern->richTextRect_.GetOffset(), OffsetF(10.0f, 10.0f)));
}
} // namespace OHOS::Ace::NG