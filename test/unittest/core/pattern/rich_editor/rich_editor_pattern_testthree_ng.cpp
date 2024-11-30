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
constexpr int32_t CUSTOM_CONTENT_LENGTH = 1;
constexpr int32_t PLACEHOLDER_LENGTH = 6;
constexpr int32_t CALCLINEEND_POSITION = 0;
constexpr int32_t PERFORM_ACTION = 1;
constexpr int32_t SYMBOL_SPAN_LENGTH = 2;
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

/**
 * @tc.name: GetRectsForRange001
 * @tc.desc: test GetRectsForRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetRectsForRange001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    int32_t start = 0;
    int32_t end = 10;
    RectHeightStyle heightStyle = RectHeightStyle::TIGHT;
    RectWidthStyle widthStyle = RectWidthStyle::TIGHT;
    auto result = richEditorPattern->GetRectsForRange(start, end, heightStyle, widthStyle);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetRectsForRange002
 * @tc.desc: test GetRectsForRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetRectsForRange002, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    int32_t start = -5;
    int32_t end = 10;
    RectHeightStyle heightStyle = RectHeightStyle::TIGHT;
    RectWidthStyle widthStyle = RectWidthStyle::TIGHT;
    auto result = richEditorPattern->GetRectsForRange(start, end, heightStyle, widthStyle);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetRectsForRange003
 * @tc.desc: test GetRectsForRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetRectsForRange003, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    int32_t start = 0;
    int32_t end = -5;
    RectHeightStyle heightStyle = RectHeightStyle::TIGHT;
    RectWidthStyle widthStyle = RectWidthStyle::TIGHT;
    auto result = richEditorPattern->GetRectsForRange(start, end, heightStyle, widthStyle);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetRectsForRange004
 * @tc.desc: test GetRectsForRange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetRectsForRange004, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(EXCEPT_VALUE);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    auto firstSpanItem = richEditorPattern->spans_.front();
    ASSERT_NE(firstSpanItem, nullptr);
    int32_t start = 10;
    int32_t end = 0;
    RectHeightStyle heightStyle = RectHeightStyle::TIGHT;
    RectWidthStyle widthStyle = RectWidthStyle::TIGHT;
    auto result = richEditorPattern->GetRectsForRange(start, end, heightStyle, widthStyle);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: HandleDragStart001
 * @tc.desc: test HandleDragStart
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleDragStart001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto dragEvent = AceType::MakeRefPtr<Ace::DragEvent>();
    std::string extraParams = "text";
    richEditorPattern->isDragSponsor_ = true;
    richEditorPattern->isOnlyImageDrag_ = true;
    richEditorPattern->HandleDragStart(dragEvent, extraParams);
    EXPECT_EQ(richEditorPattern->recoverStart_, -1);
    EXPECT_EQ(richEditorPattern->recoverEnd_, -1);
}

/**
 * @tc.name: InitPlaceholderSpansMap001
 * @tc.desc: test InitPlaceholderSpansMap
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, InitPlaceholderSpansMap001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto newSpanItem = AceType::MakeRefPtr<OHOS::Ace::NG::SpanItem>();
    auto spanItem = AceType::MakeRefPtr<OHOS::Ace::NG::SpanItem>();
    size_t index = 0;
    size_t placeholderGains = 0;
    spanItem->spanItemType = SpanItemType::CustomSpan;
    richEditorPattern->InitPlaceholderSpansMap(newSpanItem, spanItem, index, placeholderGains);
    EXPECT_EQ(placeholderGains, placeholderGains += PLACEHOLDER_LENGTH - CUSTOM_CONTENT_LENGTH);
}

/**
 * @tc.name: InitPlaceholderSpansMap002
 * @tc.desc: test InitPlaceholderSpansMap
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, InitPlaceholderSpansMap002, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto newSpanItem = AceType::MakeRefPtr<OHOS::Ace::NG::SpanItem>();
    auto spanItem = AceType::MakeRefPtr<OHOS::Ace::NG::SpanItem>();
    size_t index = 0;
    size_t placeholderGains = 0;
    spanItem->spanItemType = SpanItemType::CustomSpan;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->InitPlaceholderSpansMap(newSpanItem, spanItem, index, placeholderGains);
    EXPECT_EQ(placeholderGains, placeholderGains += PLACEHOLDER_LENGTH - CUSTOM_CONTENT_LENGTH);
}

/**
 * @tc.name: InitPlaceholderSpansMap003
 * @tc.desc: test InitPlaceholderSpansMap
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, InitPlaceholderSpansMap003, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto newSpanItem = AceType::MakeRefPtr<OHOS::Ace::NG::SpanItem>();
    auto spanItem = AceType::MakeRefPtr<OHOS::Ace::NG::SpanItem>();
    size_t index = 0;
    size_t placeholderGains = 0;
    spanItem->spanItemType = SpanItemType::IMAGE;
    richEditorPattern->InitPlaceholderSpansMap(newSpanItem, spanItem, index, placeholderGains);
    EXPECT_EQ(placeholderGains, placeholderGains += PLACEHOLDER_LENGTH - CUSTOM_CONTENT_LENGTH);
}

/**
 * @tc.name: HandleLongPress001
 * @tc.desc: test
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleLongPress001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    FingerInfo fingerInfo1;
    FingerInfo fingerInfo2;
    std::list<FingerInfo> fingerList;
    fingerList.push_back(fingerInfo1);
    fingerList.push_back(fingerInfo2);
    info.SetFingerList(fingerList);
    richEditorPattern->HandleLongPress(info);
    EXPECT_EQ(richEditorPattern->selectionMenuOffsetClick_.GetX(), info.GetOffsetX());
    EXPECT_EQ(richEditorPattern->selectionMenuOffsetClick_.GetY(), info.GetOffsetY());
}

/**
 * @tc.name: HandleLongPress002
 * @tc.desc: test HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleLongPress002, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.SetOffsetX(0.0);
    info.SetOffsetY(0.0);
    richEditorPattern->sourceType_ = SourceType::MOUSE;
    richEditorPattern->hasUrlSpan_ = true;
    richEditorPattern->HandleLongPress(info);
    EXPECT_EQ(richEditorPattern->selectionMenuOffsetClick_.GetX(), info.GetOffsetX());
    EXPECT_EQ(richEditorPattern->selectionMenuOffsetClick_.GetY(), info.GetOffsetY());
}

/**
 * @tc.name: HandleLongPress003
 * @tc.desc: test HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleLongPress003, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.SetOffsetX(0.0);
    info.SetOffsetY(0.0);
    richEditorPattern->sourceType_ = SourceType::MOUSE;
    richEditorPattern->HandleLongPress(info);
    EXPECT_EQ(richEditorPattern->selectionMenuOffsetClick_.GetX(), info.GetOffsetX());
    EXPECT_EQ(richEditorPattern->selectionMenuOffsetClick_.GetY(), info.GetOffsetY());
}

/**
 * @tc.name: CursorMoveEnd002
 * @tc.desc: test CursorMoveEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CursorMoveEnd002, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 2;
    EXPECT_TRUE(richEditorPattern->CursorMoveEnd());
}

/**
 * @tc.name: CursorMoveEnd003
 * @tc.desc: test CursorMoveEnd
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CursorMoveEnd003, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = 2;
    EXPECT_FALSE(richEditorPattern->CursorMoveEnd());
}

/**
 * @tc.name: HandleTouchEvent005
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleTouchEvent005, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEventInfo touchEventInfo("");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::DOWN;
    touchLocationInfo.localLocation_ = Offset(0.0f, 0.0f);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    richEditorPattern->hasUrlSpan_ = true;
    richEditorPattern->isMoveCaretAnywhere_ = true;
    richEditorPattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(richEditorPattern->isMoveCaretAnywhere_);
}

/**
 * @tc.name: HandleTouchEvent006
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleTouchEvent006, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    TouchEventInfo touchEventInfo("");
    TouchLocationInfo touchLocationInfo(0);
    touchLocationInfo.touchType_ = TouchType::UP;
    touchLocationInfo.localLocation_ = Offset(0.0f, 0.0f);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    richEditorPattern->hasUrlSpan_ = true;
    richEditorPattern->isMoveCaretAnywhere_ = true;
    richEditorPattern->HandleTouchEvent(touchEventInfo);
    EXPECT_FALSE(richEditorPattern->isMoveCaretAnywhere_);
}

/**
 * @tc.name: OnColorConfigurationUpdate
 * @tc.desc: test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, OnColorConfigurationUpdate, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipe = richEditorNode_->GetContext();
    auto spanNode = SpanNode::GetOrCreateSpanNode(1);
    richEditorNode_->children_.push_back(spanNode);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    pipe->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    richEditorPattern->OnColorConfigurationUpdate();
    EXPECT_EQ(richEditorPattern->scrollBar_, nullptr);
}

/**
 * @tc.name: ReplacePlaceholderWithCustomSpan001
 * @tc.desc: test ReplacePlaceholderWithCustomSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, ReplacePlaceholderWithCustomSpan001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<CustomSpanItem>();
    EXPECT_NE(spanItem, nullptr);
    size_t index = 1;
    size_t textIndex = 1;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->ReplacePlaceholderWithCustomSpan(spanItem, index, textIndex);
    EXPECT_EQ(richEditorPattern->textSelector_.IsValid(), false);
    EXPECT_EQ(textIndex, PLACEHOLDER_LENGTH + index);
}

/**
 * @tc.name: ReplacePlaceholderWithCustomSpan002
 * @tc.desc: test ReplacePlaceholderWithCustomSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, ReplacePlaceholderWithCustomSpan002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<CustomSpanItem>();
    EXPECT_NE(spanItem, nullptr);
    size_t index = 1;
    size_t textIndex = 1;
    richEditorPattern->isSpanStringMode_ = false;
    spanItem->spanItemType = SpanItemType::CustomSpan;
    auto builderId = ElementRegister::GetInstance()->MakeUniqueId();
    auto builderNode = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, builderId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    spanItem->SetCustomNode(builderNode);
    richEditorPattern->ReplacePlaceholderWithCustomSpan(spanItem, index, textIndex);
    EXPECT_EQ(textIndex, PLACEHOLDER_LENGTH + index);
}

/**
 * @tc.name: ReplacePlaceholderWithCustomSpan003
 * @tc.desc: test ReplacePlaceholderWithCustomSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, ReplacePlaceholderWithCustomSpan003, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<CustomSpanItem>();
    EXPECT_NE(spanItem, nullptr);
    spanItem->GetSameStyleSpanItem();
    size_t index = 1;
    size_t textIndex = 1;
    richEditorPattern->isSpanStringMode_ = true;
    spanItem->onMeasure.emplace();
    spanItem->onDraw.emplace();
    richEditorPattern->ReplacePlaceholderWithCustomSpan(spanItem, index, textIndex);
    EXPECT_EQ(textIndex, PLACEHOLDER_LENGTH + index);
}

/**
 * @tc.name: ReplacePlaceholderWithImageSpan001
 * @tc.desc: test ReplacePlaceholderWithImageSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, ReplacePlaceholderWithImageSpan001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    EXPECT_NE(spanItem, nullptr);
    size_t index = 1;
    size_t textIndex = 1;
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->ReplacePlaceholderWithImageSpan(spanItem, index, textIndex);
    EXPECT_EQ(richEditorPattern->textSelector_.IsValid(), false);
    EXPECT_EQ(textIndex, PLACEHOLDER_LENGTH + index);
}

/**
 * @tc.name: ReplacePlaceholderWithImageSpan002
 * @tc.desc: test ReplacePlaceholderWithImageSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, ReplacePlaceholderWithImageSpan002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    EXPECT_NE(spanItem, nullptr);
    size_t index = 1;
    size_t textIndex = 1;
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->ReplacePlaceholderWithImageSpan(spanItem, index, textIndex);
    EXPECT_EQ(textIndex, PLACEHOLDER_LENGTH + index);
}

/**
 * @tc.name: InsertOrDeleteSpace001
 * @tc.desc: test InsertOrDeleteSpace
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, InsertOrDeleteSpace001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    size_t index = -1;
    bool tag = richEditorPattern->InsertOrDeleteSpace(index);
    EXPECT_FALSE(tag);
}

/**
 * @tc.name: InsertOrDeleteSpace002
 * @tc.desc: test InsertOrDeleteSpace
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, InsertOrDeleteSpace002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    size_t index = 0;
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = "test";
    spanItem->rangeStart = 0;
    spanItem->position = 4;
    richEditorPattern->spans_.push_back(spanItem);
    bool tag = richEditorPattern->InsertOrDeleteSpace(index);
    EXPECT_TRUE(tag);
}

/**
 * @tc.name: InsertOrDeleteSpace003
 * @tc.desc: test InsertOrDeleteSpace
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, InsertOrDeleteSpace003, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    size_t index = 0;
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = " test";
    spanItem->rangeStart = 0;
    spanItem->position = 5;
    richEditorPattern->spans_.push_back(spanItem);
    bool tag = richEditorPattern->InsertOrDeleteSpace(index);
    EXPECT_TRUE(tag);
}

/**
 * @tc.name: IsTextEditableForStylus001
 * @tc.desc: test IsTextEditableForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, IsTextEditableForStylus001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    bool tag = richEditorPattern->IsTextEditableForStylus();
    EXPECT_TRUE(tag);
}

/**
 * @tc.name: IsTextEditableForStylus002
 * @tc.desc: test IsTextEditableForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, IsTextEditableForStylus002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetFocusHub()->focusType_ = FocusType::DISABLE;
    EXPECT_FALSE(richEditorPattern->GetFocusHub()->IsFocusable());
    bool tag = richEditorPattern->IsTextEditableForStylus();
    EXPECT_FALSE(tag);
}

/**
 * @tc.name: IsTextEditableForStylus003
 * @tc.desc: test IsTextEditableForStylus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, IsTextEditableForStylus003, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetFocusHub()->focusType_ = FocusType::DISABLE;
    EXPECT_FALSE(richEditorPattern->GetFocusHub()->IsFocusable());
    EXPECT_TRUE(richEditorNode_->IsVisible());
    richEditorNode_->layoutProperty_->OnVisibilityUpdate(VisibleType::INVISIBLE);
    EXPECT_FALSE(richEditorNode_->IsVisible());
    bool tag = richEditorPattern->IsTextEditableForStylus();
    EXPECT_FALSE(tag);
}

/**
 * @tc.name: PasteStr001
 * @tc.desc: test PasteStr
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, PasteStr001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::string text = "text";
    richEditorPattern->PasteStr(text);
    EXPECT_FALSE(richEditorPattern->previewLongPress_);
}

/**
 * @tc.name: PasteStr002
 * @tc.desc: test PasteStr
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, PasteStr002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::string text = "";
    auto str = richEditorPattern->pasteStr_;
    richEditorPattern->PasteStr(text);
    EXPECT_EQ(str, richEditorPattern->pasteStr_);
}

/**
 * @tc.name: CalcLineEndPosition
 * @tc.desc: test CalcLineEndPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CalcLineEndPosition, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->richTextRect_.y_ = 10.0f;
    richEditorPattern->contentRect_.y_ = 20.0f;
    EXPECT_EQ(richEditorPattern->CalcLineEndPosition(10), CALCLINEEND_POSITION);
}

/**
 * @tc.name: PerformAction
 * @tc.desc: test PerformAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, PerformAction, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;
    richEditorController->AddTextSpan(options2);
    int count = 0;
    TextFieldCommonEvent event2;
    auto callback = [&count, &event2](int32_t key, NG::TextFieldCommonEvent& event) {
        event2 = event;
        if (count > 0) {
            event.SetKeepEditable(true);
        }
        count = count + 1;
    };
    eventHub->SetOnSubmit(std::move(callback));
    TextInputAction action2 = TextInputAction::SEARCH;
    bool forceCloseKeyboard = false;
    richEditorPattern->PerformAction(action2, forceCloseKeyboard);
    EXPECT_EQ(count, PERFORM_ACTION);
}

/**
 * @tc.name: TripleClickSection001
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, TripleClickSection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    auto pipe = richEditorNode_->GetContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    pipe->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    richEditorPattern->TripleClickSection(info, 1, 1, 1);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: TripleClickSection002
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, TripleClickSection002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.SetSourceDevice(SourceType::TOUCH);
    auto pipe = richEditorNode_->GetContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    pipe->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    richEditorPattern->TripleClickSection(info, 1, 1, 1);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: TripleClickSection003
 * @tc.desc: test TripleClickSection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, TripleClickSection003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.SetSourceDevice(SourceType::TOUCH);
    auto pipe = richEditorNode_->GetContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    pipe->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    richEditorPattern->TripleClickSection(info, 1, 5, 1);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: HandleMouseLeftButtonRelease001
 * @tc.desc: test HandleMouseLeftButtonRelease
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleMouseLeftButtonRelease001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    richEditorPattern->showSelect_ = false;
    richEditorPattern->HandleMouseLeftButtonRelease(info);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: HandleMouseLeftButtonRelease002
 * @tc.desc: test HandleMouseLeftButtonRelease
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleMouseLeftButtonRelease002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_ = true;
    richEditorPattern->mouseStatus_ = MouseStatus::MOVE;
    richEditorPattern->status_ = Status::ON_DROP;
    richEditorPattern->HandleMouseLeftButtonRelease(info);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: HandleMouseLeftButtonRelease003
 * @tc.desc: test HandleMouseLeftButtonRelease
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleMouseLeftButtonRelease003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    richEditorPattern->dataDetectorAdapter_->pressedByLeftMouse_ = true;
    richEditorPattern->mouseStatus_ = MouseStatus::MOVE;
    richEditorPattern->status_ = Status::DRAGGING;
    richEditorPattern->HandleMouseLeftButtonRelease(info);
    EXPECT_TRUE(richEditorPattern->showSelect_);
}

/**
 * @tc.name: UpdateSelectionType
 * @tc.desc: test UpdateSelectionType
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, UpdateSelectionType, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SelectionInfo textSelectInfo;
    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN);
    richEditorPattern->UpdateSelectionType(textSelectInfo);
    EXPECT_EQ(richEditorPattern->selectedType_, TextSpanType::NONE);
}

/**
 * @tc.name: AdjustIndexSkipLineSeparator001
 * @tc.desc: test AdjustIndexSkipLineSeparator
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, AdjustIndexSkipLineSeparator001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t currentPosition = 1;
    bool ret = richEditorPattern->AdjustIndexSkipLineSeparator(currentPosition);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AdjustIndexSkipLineSeparator002
 * @tc.desc: test AdjustIndexSkipLineSeparator
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, AdjustIndexSkipLineSeparator002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t currentPosition = 0;
    bool ret = richEditorPattern->AdjustIndexSkipLineSeparator(currentPosition);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AdjustIndexSkipLineSeparator003
 * @tc.desc: test AdjustIndexSkipLineSeparator
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, AdjustIndexSkipLineSeparator003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t currentPosition = 10;
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = "AdjustInd\nxSkipLineSeparator";
    richEditorPattern->spans_.push_back(spanItem);
    EXPECT_TRUE(richEditorPattern->AdjustIndexSkipLineSeparator(currentPosition));
}

/**
 * @tc.name: IsResponseRegionExpandingNeededForStylus001
 * @tc.desc: test testInput text IsResponseRegionExpandingNeededForStylus001
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, IsResponseRegionExpandingNeededForStylus001, TestSize.Level0)
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
 * @tc.name: InsertValueOperation
 * @tc.desc: test InsertValueOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, InsertValueOperation, TestSize.Level2)
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

    struct UpdateSpanStyle typingStyle;
    TextStyle textStyle(5);
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);

    RichEditorPattern::OperationRecord secondRecord;
    secondRecord.addText = "second Record helloWorld";
    secondRecord.deleteCaretPostion = 3;
    richEditorPattern->operationRecords_.clear();
    richEditorPattern->operationRecords_.emplace_back(secondRecord);
    richEditorPattern->HandleOnUndoAction();
    EXPECT_TRUE(richEditorPattern->operationRecords_.empty());
}

/**
 * @tc.name: CursorMoveUp001
 * @tc.desc: test CursorMoveUp
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CursorMoveUp001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("hello1");
    richEditorPattern->caretPosition_ = 1;
    EXPECT_TRUE(richEditorPattern->CursorMoveUp());
}

/**
 * @tc.name: CursorMoveUp002
 * @tc.desc: test CursorMoveUp
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CursorMoveUp002, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("hello1");
    richEditorPattern->caretPosition_ = 1;
    OffsetF paintOffset = { -10, 1 };
    richEditorPattern->richTextRect_.SetOffset(paintOffset);
    EXPECT_TRUE(richEditorPattern->CursorMoveUp());
}

/**
 * @tc.name: CursorMoveDown
 * @tc.desc: test CursorMoveDown
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CursorMoveDown, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("hello1");
    richEditorPattern->caretPosition_ = 1;
    OffsetF paintOffset = { -10, 1 };
    richEditorPattern->richTextRect_.SetOffset(paintOffset);
    EXPECT_TRUE(richEditorPattern->CursorMoveDown());
}

/**
 * @tc.name: HandleBlurEvent
 * @tc.desc: test HandleBlurEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleBlurEvent, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    WeakPtr<Pattern> pattern;
    richEditorPattern->magnifierController_ = nullptr;
    richEditorPattern->textSelector_.Update(3, 4);
    richEditorPattern->HandleBlurEvent();
    EXPECT_FALSE(richEditorPattern->isMoveCaretAnywhere_);
}

/**
 * @tc.name: FireOnSelectionChange001
 * @tc.desc: test FireOnSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, FireOnSelectionChange001, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    bool isForced = true;
    richEditorPattern->caretTwinkling_ = true;
    richEditorPattern->selectOverlay_->isSingleHandle_ = true;
    auto range = richEditorPattern->lastSelectionRange_;
    richEditorPattern->FireOnSelectionChange(start, end, isForced);
    EXPECT_FALSE(richEditorPattern->lastSelectionRange_ == range);
}

/**
 * @tc.name: FireOnSelectionChange002
 * @tc.desc: test FireOnSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, FireOnSelectionChange002, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    bool isForced = true;
    richEditorPattern->caretTwinkling_ = false;
    richEditorPattern->selectOverlay_->isSingleHandle_ = true;
    auto range = richEditorPattern->lastSelectionRange_;
    richEditorPattern->FireOnSelectionChange(start, end, isForced);
    EXPECT_FALSE(richEditorPattern->lastSelectionRange_ == range);
}

/**
 * @tc.name: FireOnSelectionChange003
 * @tc.desc: test FireOnSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, FireOnSelectionChange003, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t start = 1;
    int32_t end = 1;
    bool isForced = true;
    richEditorPattern->caretTwinkling_ = false;
    richEditorPattern->selectOverlay_->isSingleHandle_ = false;
    auto range = richEditorPattern->lastSelectionRange_;
    richEditorPattern->FireOnSelectionChange(start, end, isForced);
    EXPECT_TRUE(richEditorPattern->lastSelectionRange_ == range);
}

/**
 * @tc.name: SetTypingStyle001
 * @tc.desc: test SetTypingStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, SetTypingStyle001, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    UpdateSpanStyle typingStyle;
    TextStyle textStyle;
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    richEditorPattern->spans_.emplace_back(spanItem);
    richEditorPattern->previewTextRecord_.previewContent = "";
    auto layout = richEditorNode_->layoutProperty_;
    richEditorPattern->SetTypingStyle(typingStyle, textStyle);
    EXPECT_TRUE(layout == richEditorNode_->layoutProperty_);
}

/**
 * @tc.name: SetResultObjectText001
 * @tc.desc: test SetResultObjectText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, SetResultObjectText001, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ResultObject resultObject;
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    EXPECT_NE(spanItem, nullptr);
    spanItem->content = "test";
    richEditorPattern->previewTextRecord_.previewContent = "text";
    richEditorPattern->SetResultObjectText(resultObject, spanItem);
    EXPECT_EQ(resultObject.previewText, richEditorPattern->previewTextRecord_.previewContent);
    richEditorPattern->previewTextRecord_.endOffset = 0;
    richEditorPattern->SetResultObjectText(resultObject, spanItem);
    EXPECT_EQ(resultObject.previewText, richEditorPattern->previewTextRecord_.previewContent);
}

/**
 * @tc.name: CalcMoveUpPos001
 * @tc.desc: test CalcMoveUpPos
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CalcMoveUpPos001, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    CaretOffsetInfo caretInfo = richEditorPattern->GetCaretOffsetInfoByPosition();
    float leadingMarginOffset = 1.0;
    OffsetF offset = { 20, 20 };
    float height = 10;
    auto overlayMod = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    overlayMod->SetCaretOffsetAndHeight(offset, height);
    auto caretOffsetOverlay = overlayMod->GetCaretOffset();
    auto minDet =
        richEditorPattern->paragraphs_.minParagraphFontSize.value_or(richEditorPattern->GetTextThemeFontSize());
    float textOffsetY = richEditorPattern->richTextRect_.GetY() + (minDet / 2.0);
    float textOffsetDownY = caretInfo.caretOffsetLine.GetY() + caretInfo.caretHeightLine - textOffsetY;
    Offset textOffset = Offset(caretOffsetOverlay.GetX() - richEditorPattern->richTextRect_.GetX(), textOffsetDownY);
    auto caretPosition = richEditorPattern->CalcMoveUpPos(leadingMarginOffset);
    EXPECT_EQ(caretPosition, richEditorPattern->paragraphs_.GetIndex(textOffset));
}

/**
 * @tc.name: CalcMoveDownPos001
 * @tc.desc: test CalcMoveDownPos
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CalcMoveDownPos001, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    CaretOffsetInfo caretInfo = richEditorPattern->GetCaretOffsetInfoByPosition();
    float leadingMarginOffset = 1;
    richEditorPattern->caretPosition_ = 0;
    OffsetF offset = { 20, 20 };
    float height = 10;
    auto overlayMod = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    overlayMod->SetCaretOffsetAndHeight(offset, height);
    auto caretOffsetOverlay = overlayMod->GetCaretOffset();
    auto minDet =
        richEditorPattern->paragraphs_.minParagraphFontSize.value_or(richEditorPattern->GetTextThemeFontSize());
    float textOffsetY = richEditorPattern->richTextRect_.GetY() + (minDet / 2.0);
    float textOffsetDownY = caretInfo.caretOffsetLine.GetY() + caretInfo.caretHeightLine - textOffsetY;
    Offset textOffset = Offset(caretOffsetOverlay.GetX() - richEditorPattern->richTextRect_.GetX(), textOffsetDownY);
    auto caretPositionEnd = richEditorPattern->CalcMoveDownPos(leadingMarginOffset);
    EXPECT_EQ(caretPositionEnd, richEditorPattern->paragraphs_.GetIndex(textOffset));
}

/**
 * @tc.name: CalcMoveDownPos002
 * @tc.desc: test CalcMoveDownPos
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CalcMoveDownPos002, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    CaretOffsetInfo caretInfo = richEditorPattern->GetCaretOffsetInfoByPosition();
    float leadingMarginOffset = 1;
    richEditorPattern->caretPosition_ = 1;
    OffsetF offset = { 20, 20 };
    float height = 10;
    auto overlayMod = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    overlayMod->SetCaretOffsetAndHeight(offset, height);
    auto caretOffsetOverlay = overlayMod->GetCaretOffset();
    auto minDet =
        richEditorPattern->paragraphs_.minParagraphFontSize.value_or(richEditorPattern->GetTextThemeFontSize());
    float textOffsetY = richEditorPattern->richTextRect_.GetY() + (minDet / 2.0);
    float textOffsetDownY = caretInfo.caretOffsetLine.GetY() + caretInfo.caretHeightLine - textOffsetY;
    Offset textOffset = Offset(caretOffsetOverlay.GetX() - richEditorPattern->richTextRect_.GetX(), textOffsetDownY);
    auto caretPositionEnd = richEditorPattern->CalcMoveDownPos(leadingMarginOffset);
    EXPECT_EQ(caretPositionEnd, richEditorPattern->paragraphs_.GetIndex(textOffset));
}

/**
 * @tc.name: GetParagraphEndPosition001
 * @tc.desc: test GetParagraphEndPosition
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, GetParagraphEndPosition001, TestSize.Level0)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    int32_t caretPosition = 10;
    AddSpan(EXCEPT_VALUE);
    auto iter = richEditorPattern->spans_.cbegin();
    auto span = *iter;
    ASSERT_NE(span, nullptr);
    auto content = StringUtils::ToWstring(span->content);
    int32_t position = span->position - static_cast<int32_t>(content.length());
    richEditorPattern->GetParagraphEndPosition(caretPosition);
    EXPECT_EQ(position, span->position - static_cast<int32_t>(content.length()));
    caretPosition = 1;
    richEditorPattern->GetParagraphEndPosition(caretPosition);
    EXPECT_EQ(position, span->position - static_cast<int32_t>(content.length()));
}

/**
 * @tc.name: HandleFocusEvent
 * @tc.desc: test HandleFocusEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleFocusEvent, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isOnlyRequestFocus_ = true;
    richEditorPattern->HandleFocusEvent();
    EXPECT_FALSE(richEditorPattern->isOnlyRequestFocus_);
}

/**
 * @tc.name: HandleDraggableFlag
 * @tc.desc: test HandleDraggableFlag
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleDraggableFlag, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->HandleDraggableFlag(false);
    EXPECT_EQ(richEditorPattern->JudgeContentDraggable(), false);
}

/**
 * @tc.name: DeleteValueSetSymbolSpan001
 * @tc.desc: test DeleteValueSetSymbolSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, DeleteValueSetSymbolSpan001, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    EXPECT_NE(spanItem, nullptr);
    RichEditorAbstractSpanResult spanResult;
    auto result = richEditorPattern->DeleteValueSetSymbolSpan(spanItem, spanResult);
    EXPECT_TRUE(result == SYMBOL_SPAN_LENGTH);
}
} // namespace OHOS::Ace::NG