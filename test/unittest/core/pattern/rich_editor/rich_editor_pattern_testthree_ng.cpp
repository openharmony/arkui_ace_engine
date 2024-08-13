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
#include "test/mock/core/common/mock_clipboard.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    constexpr uint32_t RECORD_MAX_LENGTH = 20;
    constexpr int32_t SYMBOL_SPAN_LENGTH = 2;
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
 * @tc.desc: test CalcDeleteValueObj delete unicode
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
    spanItem->unicode = 1;

    RichEditorDeleteValue info;
    int32_t currentPosition = INIT_VALUE_1.size() - 2;
    int32_t length = 2;
    richEditorPattern->CalcDeleteValueObj(currentPosition, length, info);
    EXPECT_EQ(info.GetLength(), SYMBOL_SPAN_LENGTH);
}

/**
 * @tc.name: CalcDeleteValueObj001
 * @tc.desc: test CalcDeleteValueObj delete builder span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, CalcDeleteValueObj002, TestSize.Level1)
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
 * @tc.name: HandleTouchEvent001
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestThreeNg, HandleTouchEvent001, TestSize.Level1)
{
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_3);

    Offset touchTargetOffset = { 10.0f, 2.0f };
    TouchEventInfo touchDownInfo("touchDown");
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(touchTargetOffset);
    touchDownInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    richEditorPattern->HandleTouchEvent(touchDownInfo);
    EXPECT_FALSE(richEditorPattern->isMoveCaretAnywhere_);

    richEditorPattern->textSelector_.Update(1, 2);
    TouchEventInfo touchUpInfo("touchUp");
    TouchLocationInfo touchUpLocationInfo(1);
    touchUpLocationInfo.SetTouchType(TouchType::UP);
    touchUpLocationInfo.SetLocalLocation(touchTargetOffset);
    touchUpInfo.AddTouchLocationInfo(std::move(touchUpLocationInfo));
    richEditorPattern->editingLongPress_ = true;
    richEditorPattern->isEditing_ = true;
    int32_t onSelectCallbackInfo = 0;
    auto func = [&onSelectCallbackInfo](const BaseEventInfo* info) { onSelectCallbackInfo = 1; };
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnSelect(std::move(func));
    richEditorPattern->HandleTouchEvent(touchUpInfo);
    EXPECT_EQ(onSelectCallbackInfo, 1);

    TouchEventInfo touchMoveInfo("touchMove");
    TouchLocationInfo touchMoveLocationInfo(2);
    touchMoveLocationInfo.SetTouchType(TouchType::MOVE);
    touchMoveLocationInfo.SetLocalLocation(touchTargetOffset);
    touchMoveInfo.AddTouchLocationInfo(std::move(touchMoveLocationInfo));
    richEditorPattern->isTouchCaret_ = true;
    richEditorPattern->HandleTouchEvent(touchMoveInfo);
    auto magnifierController = richEditorPattern->GetMagnifierController();
    ASSERT_NE(magnifierController, nullptr);
    auto localOffset = OffsetF(touchTargetOffset.GetX(), touchTargetOffset.GetY());
    EXPECT_TRUE(IsEqual(magnifierController->GetLocalOffset(), localOffset));
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
} // namespace OHOS::Ace::NG